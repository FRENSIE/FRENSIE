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
#include "Facemc_NeutronScatteringDistributionFactoryHelpers.hpp"
#include "Facemc_NeutronScatteringAngularDistributionFactory.hpp"
#include "Facemc_NeutronScatteringEnergyDistributionFactory.hpp"
#include "Facemc_ElasticNeutronScatteringDistribution.hpp"
#include "Facemc_IndependentEnergyAngleNeutronScatteringDistribution.hpp"
#include "Facemc_LabSystemConversionPolicy.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

namespace Facemc{

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
  initializeReactionEnergyDistStartIndexMap( ldlw_block );
  initializeReactionEnergyDistMap( ldlw_block, dlw_block );
}

// Create a scattering distribution
void NeutronScatteringDistributionFactory::createScatteringDistribution(
	      const NuclearReactionType reaction_type,
	      Teuchos::RCP<NeutronScatteringDistribution>& distribution ) const
{
  // Make sure the reaction type has a scattering distribution (mult > 0)
  remember( bool valid_reaction_type = 
	    (reaction_type == N__N_ELASTIC_REACTION) ||
	    (d_reaction_energy_dist.find( reaction_type ) !=
	     d_reaction_energy_dist.end()) );
  testPrecondition( valid_reaction_type );
  
  // Create an angular distribution if scattering law 44 is not used
  if( !d_reactions_with_coupled_energy_angle_dist.count( reaction_type ) )
  {
    Teuchos::RCP<NeutronScatteringAngularDistribution> angular_distribution;

    if( !d_reactions_with_isotropic_scattering_only.count( reaction_type ) )
    {
      NeutronScatteringAngularDistributionFactory::createDistribution(
       d_reaction_angular_dist.find( reaction_type )->second,
       d_reaction_angular_dist_start_index.find( reaction_type )->second,
       d_table_name,
       reaction_type,
       angular_distribution ); 
    }
    // Create a purely isotropic scattering angle distribution
    else
    {
      NeutronScatteringAngularDistributionFactory::createIsotropicDistribution(
							angular_distribution );
    }

    // Special Case: elastic scattering will have no energy distribution
    if( reaction_type == N__N_ELASTIC_REACTION )
    {
      TEST_FOR_EXCEPTION( !(d_reaction_cm_scattering.find( 
						      reaction_type )->second),
			  std::runtime_error,
			  "Error: elastic scattering in ACE table "
			  << d_table_name << " is specified in the Lab "
			  "system. Elastic scattering must always be in the "
			  "CM system, which indicates that there is a problem "
			  "in the ACE table!" );
      distribution.reset( 
	  new ElasticNeutronScatteringDistribution( d_atomic_weight_ratio,
						    angular_distribution ) );
    }
    // Create all other scattering distributions using the energy dist factory
    else
    {
      Teuchos::RCP<NeutronScatteringEnergyDistribution> energy_distribution;
     
      NeutronScatteringEnergyDistributionFactory::createDistribution(
       	      d_reaction_energy_dist.find( reaction_type )->second,
       	      d_reaction_energy_dist_start_index.find( reaction_type )->second,
       	      d_table_name,
       	      reaction_type,
	      energy_distribution );
  
      // Test that law 3 distributions are always in the CM system
      if( energy_distribution->getLaw() == 3 )
      {
	TEST_FOR_EXCEPTION( !(d_reaction_cm_scattering.find( 
						      reaction_type )->second),
			    std::runtime_error,
			    "Error: MT# " << reaction_type << " in ACE table "
			    << d_table_name << " uses ACE Law 3, which must "
			    "be in the CM system. The ref. frame specified is "
			    "the lab indicating that there is an error in the "
			    "ACE table!" );
      }
      
      if( d_reaction_cm_scattering.find( reaction_type )->second )
      {
	distribution.reset(
	     new IndependentEnergyAngleNeutronScatteringDistribution<CMSystemConversionPolicy>( 
						      d_atomic_weight_ratio,
						      energy_distribution,
						      angular_distribution ) );
      }
      else
      {
	distribution.reset(
	     new IndependentEnergyAngleNeutronScatteringDistribution<LabSystemConversionPolicy>( 
						      d_atomic_weight_ratio,
						      energy_distribution,
						      angular_distribution ) );
      }
    }
  }
  // Create a coupled angular-energy distribution (law 44)
  else
  {
    NeutronScatteringEnergyDistributionFactory::createAceLaw44Distribution(
              d_atomic_weight_ratio,
     	      d_reaction_energy_dist.find( reaction_type )->second,
     	      d_reaction_energy_dist_start_index.find( reaction_type )->second,
	      d_table_name,
     	      reaction_type,
	      d_reaction_cm_scattering.find( reaction_type )->second,
     	      distribution );
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
    try{
      reaction = convertUnsignedToNuclearReactionType( 
				       static_cast<unsigned>( mtr_block[i] ) );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			     "Error: unsuppported MT # found while parsing "
			     "MTR block in table " << d_table_name << "\n." );

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
    
    ++reaction;
  }

  // Add the elastic scattering case (always CM)
  d_reaction_cm_scattering[N__N_ELASTIC_REACTION] = true;
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
    if( land_block[reaction_order->second + 1] > 0 )
    {
      // Subtract by one to get C-array index
      d_reaction_angular_dist_start_index[reaction_order->first] = 
        static_cast<unsigned>( land_block[reaction_order->second + 1] ) - 1;
    }
    ++reaction_order;
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
  calculateDistArraySizes( land_block, 
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

// Initialize the reaction type energy distribution start index map
void 
NeutronScatteringDistributionFactory::initializeReactionEnergyDistStartIndexMap(
											const Teuchos::ArrayView<const double>& ldlw_block )
{
  // Add all other reactions
  boost::unordered_map<NuclearReactionType,unsigned>::const_iterator
    reaction_order, end_reaction_order;
  reaction_order = d_reaction_ordering.begin();
  end_reaction_order = d_reaction_ordering.end();
  
  while( reaction_order != end_reaction_order )
  {
    // Subtract by one to get C-array index
    d_reaction_energy_dist_start_index[reaction_order->first] = 
      static_cast<unsigned>( ldlw_block[reaction_order->second] ) - 1;

    ++reaction_order;
  }
}


// Initialize the reaction type energy distribution map
void 
NeutronScatteringDistributionFactory::initializeReactionEnergyDistMap(
			    const Teuchos::ArrayView<const double>& ldlw_block,
			    const Teuchos::ArrayView<const double>& dlw_block )
{
  // Calculate the size of each energy distribution array
  Teuchos::Array<unsigned> energy_dist_array_sizes;
  calculateDistArraySizes( ldlw_block, 
			   dlw_block, 
			   energy_dist_array_sizes );

  // Handle all other distributions
  boost::unordered_map<NuclearReactionType,unsigned>::const_iterator
    reaction_order, end_reaction_order;
  reaction_order = d_reaction_ordering.begin();
  end_reaction_order = d_reaction_ordering.end();

  int dist_index;
  int dist_array_size;
  
  // Elastic scattering will always be the first entry in the land block -
  // increment all indices by 1 to account for this
  while( reaction_order != end_reaction_order )
  {
    dist_index = static_cast<int>( ldlw_block[reaction_order->second] );

    dist_array_size = energy_dist_array_sizes[reaction_order->second];
    
    d_reaction_energy_dist[reaction_order->first] =
	    dlw_block( dist_index - 1u, dist_array_size );
    
    ++reaction_order;
  }

  // Check that every reaction has been found
  testPostcondition( d_reaction_energy_dist.size() == d_reaction_ordering.size() );

}

// Returns a map of the reaction types (MT #s) and their AND block ordering
const boost::unordered_map<NuclearReactionType,unsigned>& 
NeutronScatteringDistributionFactory::getReactionOrdering() const
{
  return NeutronScatteringDistributionFactory::d_reaction_ordering;
}

// Returns a map of the reaction types (MT #s) and the scattering reference frame
// Note: True = center-of-mass, False = lab
const boost::unordered_map<NuclearReactionType,bool>& 
NeutronScatteringDistributionFactory::getReactionCMScattering() const
{
  return NeutronScatteringDistributionFactory::d_reaction_cm_scattering;
}

// Returns a set of the reaction types (MT #s) with isotropic scattering only
const boost::unordered_set<NuclearReactionType>& 
NeutronScatteringDistributionFactory::getReactionsWithIsotropicScatteringOnly() const
{
  return NeutronScatteringDistributionFactory::d_reactions_with_isotropic_scattering_only;
}

// Returns a set of the reaction types (MT #s) with coupled energy-angle dist
const boost::unordered_set<NuclearReactionType>& 
NeutronScatteringDistributionFactory::getReactionsWithCoupledEnergyAngleDist() const
{
  return NeutronScatteringDistributionFactory::d_reactions_with_coupled_energy_angle_dist;
}

// Returns a map of the reaction types (MT #s) and the corresponding angular dist
const boost::unordered_map<NuclearReactionType,Teuchos::ArrayView<const double> >&
NeutronScatteringDistributionFactory::getReactionAngularDist() const
{
  return NeutronScatteringDistributionFactory::d_reaction_angular_dist;
}

// Returns a map of the reaction types (MT #s) and the angular dist start index
const boost::unordered_map<NuclearReactionType,unsigned>& 
NeutronScatteringDistributionFactory::getReactionAngularDistStartIndex() const
{
  return NeutronScatteringDistributionFactory::d_reaction_angular_dist_start_index;
}

// Returns a map of the reaction types (MT #s) and the corresponding energy dist
const boost::unordered_map<NuclearReactionType,Teuchos::ArrayView<const double> >&
NeutronScatteringDistributionFactory::getReactionEnergyDist() const
{
  return NeutronScatteringDistributionFactory::d_reaction_energy_dist;
}

// Returns a map of the reaction types (MT #s) and the energy dist start index
const boost::unordered_map<NuclearReactionType,unsigned>& 
NeutronScatteringDistributionFactory::getReactionEnergyDistStartIndex() const
{
  return NeutronScatteringDistributionFactory::d_reaction_energy_dist_start_index;
}


} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_NeutronScatteringDistributionFactory.cpp
//---------------------------------------------------------------------------//
