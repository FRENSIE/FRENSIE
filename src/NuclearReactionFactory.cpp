//---------------------------------------------------------------------------//
//!
//! \file   NuclearReactionFactory.cpp
//! \author Alex Robinson
//! \brief  Nuclear reaction factory class declaration
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FACEMC Includes
#include "NuclearReactionFactory.hpp"
#include "ScatteringDistributionFactory.hpp"
#include "ContractException.hpp"

namespace FACEMC{

// Constructor
/*! \details All blocks from the ACE file will be stored. 
 * \param[in] mtr_block The MTR block stores the ENDF reactions available for 
 * the nuclide.
 * \param[in] lqr_block The LQR block stores the Q-values for each ENDF 
 * reaction. 
 * \param[in] tyr_block The TYR block stores the number of neutrons released 
 * for each ENDF reaction. If the value is negative, scattering takes place in 
 * the CM system. If the value is positive, scattering takes place in the LAB 
 * system. A value of 19 indicates fission. A value of 0 indicates absorption. 
 * A value > 100 indicates non-fission reactions with energy-dependent neutron 
 * multiplicities. 
 * \param[in] lsig_block The LSIG block stores the location of the cross 
 * section for each ENDF reaction in the SIG block. 
 * \param[in] sig_block The SIG block stores the cross section for each ENDF 
 * reaction. 
 * \param[in] land_block The LAND block stores the location of the angular 
 * distribution in the AND block for each ENDF reaction. 
 * \param[in] and_block The AND block stores the angular distribution for each 
 * ENDF reaction. 
 * \param[in] ldlw_block The LDLW block stores the location of the energy 
 * distribution for each ENDF reaction.
 * \param[in] dlw_block The DLW block stores the energy distribution for each 
 * ENDF reaction.
 */
NuclearReactionFactory::NuclearReactionFactory( 
		       const std::string& table_name,
		       const double atomic_weight_ratio,
		       const Teuchos::ArrayView<double>& energy_grid,
		       const Teuchos::ArrayView<double>& elastic_cross_section,
		       const Teuchos::ArrayView<double>& mtr_block, 
		       const Teuchos::ArrayView<double>& lqr_block,
		       const Teuchos::ArrayView<double>& tyr_block,
		       const Teuchos::ArrayView<double>& lsig_block,
		       const Teuchos::ArrayView<double>& sig_block,
		       const Teuchos::ArrayView<double>& land_block,
		       const Teuchos::ArrayView<double>& and_block,
		       const Teuchos::ArrayView<double>& ldlw_block,
		       const Teuchos::ArrayView<double>& dlw_block )
  : d_table_name( table_name ),
    d_atomic_weight_ratio( atomic_weight_ratio ),
    d_energy_grid( energy_grid ),
    d_scattering_dist_factory( table_name, atomic_weight_ratio )
{ 
  // Make sure there is at least one MT # present
  testPrecondition( mtr_block.size() > 0 );
  // Make sure there is a Q-value for every reaction type
  testPrecondition( lqr_block.size() == mtr_block.size() );
  // Make sure there is a multiplicity value for every reaction type
  testPrecondition( tyr_block.size() == mtr_block.size() );
  // Make sure there is a cross section array index for every reaction type
  testPrecondition( lsig_block.size() == mtr_block.size() );
  // Make sure there is an energy distribution index for every reaction type
  testPrecondition( ldlw_block.size() == mtr_block.size() );
  
  initializeReactionTypeOrderingMap( mtr_block );
  initializeReactionTypeQValueMap( lqr_block );
  initializeReactionTypeMultiplicityAndRefFrameMap( tyr_block );
  initializeReactionTypeThresholdAndCrossSectionMap( lsig_block, 
						     sig_block,
						     elastic_cross_section );
  initializeReactionTypeANDBlockOrdering( land_block );
  initializeReactionTypeAngularDistMap( land_block, and_block );
  initializeReactionTypeEnergyDistMap( ldlw_block, dlw_block );
}

// Create the elastic reaction
Teuchos::RCP<NuclearReaction> 
NuclearReactionFactory::createElasticReaction() const
{
  Teuchos::RCP<ScatteringDistribution> elastic_scattering_dist = 
    d_scattering_dist_factory.createElasticScatteringDistribution(
			      d_reaction_angular_dist[N__N_ELASTIC_REACTION] );

  return Teuchos::RCP<NuclearReaction>( new NuclearReaction( 
			     N__N_ELASTIC_REACTION,
			     d_reaction_q_value[N__N_ELASTIC_REACTION],
			     d_reaction_multiplicity[N__N_ELASTIC_REACTION],
			     d_reaction_threshold_index[N__N_ELASTIC_REACTION],
			     d_energy_grid,
			     d_reaction_cross_section[N__N_ELASTIC_REACTION],
			     elastic_scattering_dist ) );
}

// Create the non-elastic reactions (any reaction with multiplicity > 0 )
Teuchos::Array<Teuchos::RCP<NuclearReaction> >
NuclearReactionFactory::createNonElasticReactions() const
{
  return Teuchos::Array<Teuchos::RCP<NuclearReaction> >;
}

// Initialize the reaction type ordering map
void NuclearReactionFactory::initializeReactionTypeOrderingMap( 
				  const Teuchos::ArrayView<double>& mtr_block )
{  
  NuclearReactionType reaction;
  
  for( unsigned i = 0; i < mtr_block.size(); ++i )
  {
    reaction = convertUnsignedToNuclearReactionType( 
				       static_cast<unsigned>( mtr_block[i] ) );
    
    d_reaction_type_ordering[reaction] = i;
  }

  // Elastic scattering must be handled separately: it never appears in block
  d_reaction_type_ordering[N__ELASTIC_REACTION] = 
    std::numeric_limits<unsigned>::max();
}

// Initialize the reaction type Q-value map
void NuclearReactionFactory::initializeReactionTypeQValueMap(
				  const Teuchos::ArrayView<double>& lqr_block )
{
  boost::unordered_map<NuclearReactionType,unsigned>::const_iterator
    reaction, end_reaction;
  reaction = d_reaction_type_ordering.begin();
  end_reaction = d_reaction_type_ordering.end();

  while( reaction != end_reaction )
  {
    if( reaction->first != N__N_ELASTIC_REACTION )
    {
      d_reaction_type_q_value[reaction->first] = 
	lqr_block[reaction->second];
    }
    // Elastic scattering must be handled separately: it never appears in block
    else 
      d_reaction_type_q_value[reaction->first] = 0.0;
    
    ++reaction;
  }
}

// Initialize the reaction type multiplicity and scattering ref. frame map
void NuclearReactionFactory::initializeReactionTypeMultiplicityAndRefFrameMap(
				  const Teuchos::ArrayView<double>& tyr_block )
{
  boost::unordered_map<NuclearReactionType,unsigned>::const_iterator
    reaction, end_reaction;
  reaction = d_reaction_type_ordering.begin();
  end_reaction = d_reaction_type_ordering.end();

  double multiplicity;
  
  while( reaction != end_reaction )
  {
    if( reaction->first != N__N_ELASTIC_REACTION )
    {
      multiplicity = tyr_block[reaction->second];
      
      d_reaction_type_multiplicity[reaction->first] = 
	static_cast<unsigned>( 
		    Teuchos::ScalarTraits<double>::magnitude( multiplicity ) );

      if( multiplicity < 0.0 )
	d_reaction_type_cm_sattering[reaction->first] = true;
      else
	d_reaction_type_cm_scattering[reaction->first] = false;
    }
    // Elastic scattering must be handled separately: it never appears in block
    else
    {
      d_reaction_type_multiplicity[reaction->first] = 1u;
      d_reaction_type_cm_scattering[reaction->first] = true;
    }

    ++reaction;
  }
}

// Initialize the reaction type threshold and cross section map
// NOTE: All LSIG block indices correspond to FORTRAN arrays. Subtract 1 from
// the value to get the index in a C/C++ array.
void NuclearReactionFactory::initializeReactionTypeThresholdAndCrossSectionMap(
		      const Teuchos::ArrayView<double>& lsig_block,
		      const Teuchos::ArrayView<double>& sig_block,
		      const Teuchos::ArrayView<double>& elastic_cross_section )
{
  boost::unordered_map<NuclearReactionType,unsigned>::const_iterator
    reaction, end_reaction;
  reaction = d_reaction_type_ordering.begin();
  end_reaction = d_reaction_type_ordering.end();

  unsigned cs_index;
  unsigned cs_array_size;
  
  while( reaction != end_reaction )
  {
    if( reaction->first != N__N_ELASTIC_REACTION )
    {
      cs_index = static_cast<unsigned>( lsig_block[reaction->second] ) - 1u;
      
      d_reaction_type_threshold_index[reaction->first] = 
	static_cast<unsigned>( sig_block[cs_index] ) - 1u;

      cs_array_size = static_cast<unsigned>( sig_block[cs_index+1u] );

      d_reaction_type_cross_section[reaction->first] = 
	sig_block( cs_index+2u, cs_array_size );	
    }
    // Elastic scattering must be handled separately: it never appears in block
    else
    {
      d_reaction_type_threshold_index[reaction->first] = 0;
      d_reaction_type_cross_section[reaction->first] = elastic_cross_section;
    }

    ++reaction;
  }
}

// Initialize the reaction type and block ordering map
// NOTE: All LAND block indices correspond to FORTRAN arrays. Subtract 1 from
// the value to get the index in a C/C++ array.
void NuclearReactionFactory::initializeReactionTypeANDBlockOrdering(
				 const Teuchos::ArrayView<double>& mtr_block,
				 const Teuchos::ArrayView<double>& tyr_block,
				 const Teuchos::ArrayView<double>& land_block )
{
  // Inelastic scattering is always appears first in the land block
  d_reaction_and_block_ordering[N__N_ELASTIC_REACTION] = 
    static_cast<unsigned>( land_block[0] ) - 1u;

  unsigned land_block_index = 1u;
  NuclearReactionType reaction;

  for( unsigned i = 0; i < mtr_block.size(); ++i )
  {
    reaction = convertUnsignedToNuclearReactionType( 
				       static_cast<unsigned>( mtr_block[i] ) );
    
    // The reaction will only have an angular distribution if the multiplicity
    // is non-zero
    if( tyr_block[i] != 0.0 )
    {
      d_reaction_and_block_ordering[reaction] = land_block_index;

      ++land_block_index;
    }
  }
}

// Initialize the reaction type angular distribution map
// NOTE: All LAND block indices correspond to FORTRAN arrays. Subtract 1 from
// the value to get the index in a C/C++ array.
void NuclearReactionFactory::initializeReactionTypeAngularDistMap(
				  const Teuchos::ArrayView<double>& land_block,
				  const Teuchos::ArrayView<double>& and_block )
{
  // Calculate the size of each angular distribution array
  Teuchos::Array<unsigned> angular_dist_array_sizes;
  calculateAngularDistArraySizes( land_block, 
				  and_block, 
				  angular_dist_array_sizes );
  
  boost::unordered_map<NuclearReactionType,unsigned>::const_iterator
    reaction, end_reaction;
  reaction = d_reaction_type_and_block_ordering.begin();
  end_reaction = d_reaction_type_and_block_ordering.end();

  int dist_index; // index may be negative to signify special cases
  int dist_array_size;

  while( reaction != end_reaction )
  {
    dist_index = static_cast<int>( land_block[reaction->second] );

    // An angular distribution is present
    if( dist_index > 0 )
    {      
      dist_array_size = angular_dist_array_sizes[reaction->second];
      
      d_reaction_angular_dist[reaction->first] =
	    and_block( dist_index - 1u, dist_array_size );
    }
    
    // The angular distribution is coupled to the energy distribution
    else if( dist_index == -1 )
      d_reactions_with_coupled_energy_angle_dist.insert( reaction );
  
    // The angular distribution is isotropic
    else if( dist_index == 0 )
      d_reactions_with_isotropic_scattering_only.insert( reaction );
    
    // An unknown index has been found
    else
    {
      std::stringsteam ss;
      ss << "Unknown angular distribution index found in table "
	 << d_table_name << " for MT = " << reaction->first;
      
      throw std::runtime_error( ss.str() );
    }
    
    ++reaction;
  }
}

// Initialize the reaction type energy distribution map
void NuclearReactionFactory::initializeReactionTypeEnergyDistMap(
				  const Teuchos::ArrayView<double>& ldlw_block,
				  const Teuchos::ArrayView<double>& dlw_block )
{
  
}

// Calculate the AND block angular distribution array sizes
void NuclearReactionFactor::calculateAngularDistArraySizes( 
                     const Teuchos::ArrayView<double>& land_block,
		     const Teuchos::ArrayView<double>& and_block,
                     Teuchos::Array<unsigned>& angular_dist_array_sizes ) const
{
  // Make sure the multiplicity map has been initialized
  testPrecondition( d_reaction_type_multiplicity.size() > 0 );
  
  int dist_index;
  
  // Strip the LAND block of index values <= 0
  Teuchos::Array<int> simplified_land_block;
  for( unsigned i = 0u; i < land_block.size(); ++i )
  {
    dist_index = static_cast<int>( land_bock[i] );
    
    if( dist_index > 0 )
      simplified_land_block.push_back( dist_index );
    else
      simplified_land_block.push_back( simplified_land_block.back() );
  }
  
  unsigned array_size;
  
  angular_distribution_array_sizes.resize( simplified_land_block.size() );
  
  // Calculate the angular distribution array sizes
  for( unsigned i = 0u; i < simplified_land_block.size(); ++i )
  {
    if( i < simplified_land_block.size() - 1u )
      array_size = simplified_land_block[i+1u] - simplified_land_block[i];
    else
      array_size = land_block.size() + 1 - simplified_land_block[i];
    
    angular_distribution_array_sizes[i] = array_size;
  }

  // Make sure every index in the land block has a corresponding array size
  testPostcondition( angular_distribution_array_sizes.size() ==
		     land_block.size() );
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end NuclearReactionFactory.cpp
//---------------------------------------------------------------------------//
