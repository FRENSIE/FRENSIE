//---------------------------------------------------------------------------//
//!
//! \file   NeutronScatteringDistributionFactory.cpp
//! \author Alex Robinson
//! \brief  Neutron scattering distribution factory class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <sstream>
#include <stdexcept>

// Trilinos Includes
#include "Teuchos_ArrayView.hpp"

// FRENSIE Includes
#include "Facemc_NeutronScatteringDistributionFactory.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_ThirtyTwoEquiprobableBinDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace Facemc{

// Initialize the static member data
Teuchos::RCP<Utility::OneDDistribution> 
NeutronScatteringDistributionFactory::isotropic_angle_cosine_dist(
			  new Utility::UniformDistribution( -1.0, 1.0, 1.0 ) );

// Constructor
NeutronScatteringDistributionFactory::NeutronScatteringDistributionFactory( 
			   const std::string& table_name,
			   const double atomic_weight_ratio,
			   const Teuchos::ArrayView<const double>& mtr_block,
			   const Teuchos::ArrayView<const double>& tyr_block,
			   const Teuchos::ArrayView<const double>& land_block,
			   const Teuchos::ArrayView<const double>& and_block,
			   const Teuchos::ArrayView<const double>& ldlw_block,
			   const Teuchos::ArrayView<const double>& dlw_block )
  : d_table_name( table_name ),
    d_atomic_weight_ratio( atomic_weight_ratio )
{ 
  // Make sure there is at least one MT # present
  testPrecondition( mtr_block.size() > 0 );
  // Make sure there is a multiplicity value for every reaction type
  testPrecondition( tyr_block.size() == mtr_block.size() );
  // Make sure there is an angular distribution index for every reaction type
  // with outgoing neutrons (plus elastic)
  testPrecondition( land_block.size() <= mtr_block.size()+1 );
  // Make sure there is an energy distribution index for every reaction type
  // with outgoing neutrons
  testPrecondition( ldlw_block.size() <= mtr_block.size() );

  initializeReactionOrderingMap( mtr_block, tyr_block );
  initializeReactionRefFrameMap( mtr_block, tyr_block );
  initializeReactionAngularDistStartIndexMap( land_block );
  initializeReactionAngularDistMap( land_block, and_block );
  initializeReactionEnergyDistMap( ldlw_block, dlw_block );
}

// Create a scattering distribution
void NeutronScatteringDistributionFactory::createElasticScatteringDistribution(
                            Teuchos::RCP<NeutronScatteringDistribution>&
			    elastic_distribution ) const
{
  const Teuchos::ArrayView<const double>& raw_angular_dist = 
    d_reaction_angular_dist.find( N__N_ELASTIC_REACTION )->second;
  
  // Get the number of energies at which the angular distribution is tabulated
  unsigned num_tabulated_energies = static_cast<unsigned>(raw_angular_dist[0]);
  
  // Get the energy grid
  Teuchos::ArrayView<const double> energy_grid = 
    raw_angular_dist( 1, num_tabulated_energies);
  
  // Get the location of the angular distribution for each energy
  Teuchos::ArrayView<const double> distribution_indices = 
    raw_angular_dist( num_tabulated_energies + 1,
		      num_tabulated_energies );
  
  // Initialize the angular distribution array
  Teuchos::Array<Utility::Pair<double,
			       Teuchos::RCP<Utility::OneDDistribution> > >
    angular_distribution( num_tabulated_energies );

  for( unsigned i = 0u; i < energy_grid.size(); ++i )
  {
    angular_distribution[i].first = energy_grid[i];

    int distribution_index = 
      static_cast<int>( distribution_indices[i] );

    // Thirty two equiprobable bin distribution
    if( distribution_index > 0 )
    {
      Teuchos::ArrayView<const double> bin_boundaries = 
	raw_angular_dist( distribution_index, 33 );

      angular_distribution[i].second.reset( 
	 new Utility::ThirtyTwoEquiprobableBinDistribution( bin_boundaries ) );
    }

    // Tabular distribution
    else if( distribution_index < 0 )
    {
      // Distribution index is relative to beginning of AND block - subtract
      // off start index of portion of and block for given MT #.
      distribution_index = abs(distribution_index) - 1 -
	d_reaction_angular_dist_start_index.find(
						N__N_ELASTIC_REACTION)->second;
      
      unsigned interpolation_flag = 
	raw_angular_dist[distribution_index];
      
      unsigned number_of_points_in_dist = 
	raw_angular_dist[distribution_index + 1];
      
      Teuchos::ArrayView<const double> scattering_angle_cosine_grid = 
	raw_angular_dist( distribution_index + 2,
			  number_of_points_in_dist );

      // Ignore the last evaluated point in the PDF
      Teuchos::ArrayView<const double> pdf;

      switch( interpolation_flag )
      {
      case 1u: // histogram interpolation
	pdf = raw_angular_dist( 
			     distribution_index + 2 + number_of_points_in_dist,
			     number_of_points_in_dist - 1u );
	
	angular_distribution[i].second.reset( 
	      new Utility::HistogramDistribution( scattering_angle_cosine_grid,
						  pdf ) );
	break;
	
      case 2u: // Linear-Linear interpolation
	pdf = raw_angular_dist( 
			     distribution_index + 2 + number_of_points_in_dist,
			     number_of_points_in_dist );
	
	angular_distribution[i].second.reset( 
	                 new Utility::TabularDistribution<Utility::LinLin>(
						  scattering_angle_cosine_grid,
						  pdf ) );
						 
	break;
	
      default:
	std::stringstream ss;
	ss << "Unknown interpolation flag found in table " << d_table_name
	   << " for angular distribution of MT = 2: " << interpolation_flag;
	
	throw std::runtime_error( ss.str() );
      }
    }
    
    // Isotropic distribution
    else
    {
      angular_distribution[i].second = 
	NeutronScatteringDistributionFactory::isotropic_angle_cosine_dist;
    }
  }

  // Create the elastic scattering distribution
  elastic_distribution.reset(
	    new ElasticNeutronScatteringDistribution( d_atomic_weight_ratio,
						      angular_distribution ) );
}

// Create a scattering distribution
void NeutronScatteringDistributionFactory::createScatteringDistribution(
	      const NuclearReactionType reaction_type,
	      Teuchos::RCP<NeutronScatteringDistribution>& distribution ) const
{
  switch( reaction_type )
  {
  case N__N_ELASTIC_REACTION:
    this->createElasticScatteringDistribution( distribution );
    break;
  default:
    distribution.reset();
    break;
  }
}

// Initialize the reaction type ordering map
void 
NeutronScatteringDistributionFactory::initializeReactionOrderingMap( 
			    const Teuchos::ArrayView<const double>& mtr_block,
			    const Teuchos::ArrayView<const double>& tyr_block )
{
  NuclearReactionType reaction;

  for( unsigned i = 0; i < mtr_block.size(); ++i )
  {
    reaction = convertUnsignedToNuclearReactionType( 
				       static_cast<unsigned>( mtr_block[i] ) );

    if( tyr_block[i] != 0 )
      d_reaction_ordering[reaction] = i;
  }
}

// Initialize the reaction type scattering ref. frame map
void 
NeutronScatteringDistributionFactory::initializeReactionRefFrameMap( 
			    const Teuchos::ArrayView<const double>& mtr_block,
			    const Teuchos::ArrayView<const double>& tyr_block )
{
  boost::unordered_map<NuclearReactionType,unsigned>::const_iterator
    reaction, end_reaction;
  reaction = d_reaction_ordering.begin();
  end_reaction = d_reaction_ordering.end();

  while( reaction != end_reaction )
  {
    if( tyr_block[reaction->second] < 0 )
      d_reaction_cm_scattering[reaction->first] = true;
    else
      d_reaction_cm_scattering[reaction->first] = false;
  }
}

// Initialize the reaction type angular distribution start index map
void 
NeutronScatteringDistributionFactory::initializeReactionAngularDistStartIndexMap(
											const Teuchos::ArrayView<const double>& land_block )
{
  // Add elastic scattering separately (always first in LAND block)
  d_reaction_angular_dist_start_index[N__N_ELASTIC_REACTION] = 0;
  
  // Add all other reactions
  boost::unordered_map<NuclearReactionType,unsigned>::const_iterator
    reaction_order, end_reaction_order;
  reaction_order = d_reaction_ordering.begin();
  end_reaction_order = d_reaction_ordering.end();
  
  while( reaction_order != end_reaction_order )
  {
    // Subtract by one to get C-array index
    d_reaction_angular_dist_start_index[reaction_order->first] = 
      static_cast<int>( land_block[reaction_order->second] ) - 1;
  }
}

// Initialize the reaction type angular distribution map
// NOTE: All LAND block indices correspond to FORTRAN arrays. Subtract 1 from
// the value to get the index in a C/C++ array.
void
NeutronScatteringDistributionFactory::initializeReactionAngularDistMap(
			    const Teuchos::ArrayView<const double>& land_block,
			    const Teuchos::ArrayView<const double>& and_block )
{
  // Calculate the size of each angular distribution array
  Teuchos::Array<unsigned> angular_dist_array_sizes;
  calculateAngularDistArraySizes( land_block, 
				  and_block, 
				  angular_dist_array_sizes );

  // An elastic scattering distribution will always exist but must be 
  // handled separately
  d_reaction_angular_dist[N__N_ELASTIC_REACTION] = 
    and_block( 0u, angular_dist_array_sizes[0] );

  // Handle all other distributions
  boost::unordered_map<NuclearReactionType,unsigned>::const_iterator
    reaction_order, end_reaction_order;
  reaction_order = d_reaction_ordering.begin();
  end_reaction_order = d_reaction_ordering.end();

  int dist_index; // index may be negative to signify special cases
  int dist_array_size;
  
  // Elastic scattering will always be the first entry in the land block -
  // increment all indices by 1 to account for this
  while( reaction_order != end_reaction_order )
  {
    dist_index = static_cast<int>( land_block[reaction_order->second+1u] );

    // An angular distribution is present
    if( dist_index > 0 )
    {      
      dist_array_size = angular_dist_array_sizes[reaction_order->second+1u];
      
      d_reaction_angular_dist[reaction_order->first] =
	    and_block( dist_index - 1u, dist_array_size );
    }
    
    // The angular distribution is coupled to the energy distribution
    else if( dist_index == -1 )
      d_reactions_with_coupled_energy_angle_dist.insert(reaction_order->first);
  
    // The angular distribution is isotropic
    else if( dist_index == 0 )
      d_reactions_with_isotropic_scattering_only.insert(reaction_order->first);
    
    // An unknown index has been found
    else
    {
      std::stringstream ss;
      ss << "Unknown angular distribution index (" 
	 << dist_index << ") found in table "
	 << d_table_name << " for MT = " << reaction_order->first;
      
      throw std::runtime_error( ss.str() );
    }
    
    ++reaction_order;
  }

  // Check that every reaction has been found
  testPostcondition( d_reaction_angular_dist.size() +
		     d_reactions_with_isotropic_scattering_only.size() +
		     d_reactions_with_coupled_energy_angle_dist.size() ==
		     d_reaction_ordering.size() + 1 );
}

// Initialize the reaction type energy distribution map
void 
NeutronScatteringDistributionFactory::initializeReactionEnergyDistMap(
			    const Teuchos::ArrayView<const double>& ldlw_block,
			    const Teuchos::ArrayView<const double>& dlw_block )
{

}

// Calculate the AND block angular distribution array sizes
void 
NeutronScatteringDistributionFactory::calculateAngularDistArraySizes( 
                     const Teuchos::ArrayView<const double>& land_block,
		     const Teuchos::ArrayView<const double>& and_block,
                     Teuchos::Array<unsigned>& angular_dist_array_sizes ) const
{
  int dist_index;
  
  // Strip the LAND block of index values <= 0
  Teuchos::Array<int> simplified_land_block;
  for( unsigned i = 0u; i < land_block.size(); ++i )
  {
    dist_index = static_cast<int>( land_block[i] );
    
    if( dist_index > 0 )
      simplified_land_block.push_back( dist_index );
    else
      simplified_land_block.push_back( simplified_land_block.back() );
  }
  
  unsigned array_size;
  
  // resize the array sizes array
  angular_dist_array_sizes.resize( simplified_land_block.size() );
  
  // Calculate the angular distribution array sizes
  for( unsigned i = 0u; i < simplified_land_block.size(); ++i )
  {
    if( i < simplified_land_block.size() - 1u )
      array_size = simplified_land_block[i+1u] - simplified_land_block[i];
    else
      array_size = and_block.size() + 1 - simplified_land_block[i];
    
    angular_dist_array_sizes[i] = array_size;
  }
  
  // Make sure every index in the land block has a corresponding array size
  testPostcondition( angular_dist_array_sizes.size() ==
		     land_block.size() );
}								   

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_NeutronScatteringDistributionFactory.cpp
//---------------------------------------------------------------------------//
