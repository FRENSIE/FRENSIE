//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NuclearScatteringDistributionACEFactory_def.hpp
//! \author Alex Robinson, Eli Moll
//! \brief  Nuclear scattering distribution factor base class template defs.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_NUCLEAR_SCATTERING_DISTRIBUTION_ACE_FACTORY_DEF_HPP
#define MONTE_CARLO_NUCLEAR_SCATTERING_DISTRIBUTION_ACE_FACTORY_DEF_HPP

// Std Lib Includes
#include <sstream>
#include <stdexcept>

// FRENSIE Includes
#include "MonteCarlo_NuclearScatteringDistributionFactoryHelpers.hpp"
#include "MonteCarlo_NuclearScatteringDistributionACEFactoryHelper.hpp"
#include "MonteCarlo_NuclearScatteringAngularDistributionACEFactory.hpp"
#include "MonteCarlo_NuclearScatteringEnergyDistributionACEFactory.hpp"
#include "MonteCarlo_IndependentEnergyAngleNuclearScatteringDistribution.hpp"
#include "MonteCarlo_NuclearScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_LabSystemConversionPolicy.hpp"
#include "Utility_Vector.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Basic Constructor
template<typename IncomingParticleType, typename OutgoingParticleType>
NuclearScatteringDistributionACEFactory<IncomingParticleType,
					OutgoingParticleType>::NuclearScatteringDistributionACEFactory(
                                          const std::string& table_name,
					  const double atomic_weight_ratio )
  : d_table_name( table_name ),
    d_atomic_weight_ratio( atomic_weight_ratio )
{ /* ... */ }

// Constructor
/*! \details The ArrayView objects are based by value so that data extractor
 * class extract member functions can be used directly in the constructor.
 * Passing by reference would not allow this to be done.
 */
template<typename IncomingParticleType, typename OutgoingParticleType>
NuclearScatteringDistributionACEFactory<IncomingParticleType,
					OutgoingParticleType>::NuclearScatteringDistributionACEFactory(
			    const std::string& table_name,
			    const double atomic_weight_ratio,
			    const Utility::ArrayView<const double> mtr_block,
			    const Utility::ArrayView<const double> tyr_block,
			    const Utility::ArrayView<const double> land_block,
			    const Utility::ArrayView<const double> and_block,
			    const Utility::ArrayView<const double> ldlw_block,
			    const Utility::ArrayView<const double> dlw_block )
  : d_table_name( table_name ),
    d_atomic_weight_ratio( atomic_weight_ratio )
{
  this->initialize( mtr_block,
		    tyr_block,
		    land_block,
		    and_block,
		    ldlw_block,
		    dlw_block );
}

// Constructor (no TYR block)
/*! \details The ArrayView objects are based by value so that data extractor
 * class extract member functions can be used directly in the constructor.
 * Passing by reference would not allow this to be done. If the tyr block is
 * not given, all reactions are assumed to take place in the lab system and
 * the multiplicities are assumed to be one.
 */
template<typename IncomingParticleType, typename OutgoingParticleType>
NuclearScatteringDistributionACEFactory<IncomingParticleType,
					OutgoingParticleType>::NuclearScatteringDistributionACEFactory(
			    const std::string& table_name,
			    const double atomic_weight_ratio,
			    const Utility::ArrayView<const double> mtr_block,
			    const Utility::ArrayView<const double> land_block,
			    const Utility::ArrayView<const double> and_block,
			    const Utility::ArrayView<const double> ldlw_block,
			    const Utility::ArrayView<const double> dlw_block )
  : d_table_name( table_name ),
    d_atomic_weight_ratio( atomic_weight_ratio )
{
  this->initialize( mtr_block,
		    land_block,
		    and_block,
		    ldlw_block,
		    dlw_block );
}

// Initialize the factory
template<typename IncomingParticleType, typename OutgoingParticleType>
void NuclearScatteringDistributionACEFactory<IncomingParticleType,
					     OutgoingParticleType>::initialize(
		   const Utility::ArrayView<const double> mtr_block,
		   const Utility::ArrayView<const double> tyr_block,
		   const Utility::ArrayView<const double> land_block,
		   const Utility::ArrayView<const double> and_block,
		   const Utility::ArrayView<const double> ldlw_block,
		   const Utility::ArrayView<const double> dlw_block )
{
  initializeReactionOrderingMap( mtr_block, tyr_block );
  initializeReactionRefFrameMap( mtr_block, tyr_block );
  initializeReactionAngularDistStartIndexMap( land_block );
  initializeReactionAngularDistMap( land_block, and_block );
  initializeReactionEnergyDistStartIndexMap( ldlw_block );
  initializeReactionEnergyDistMap( ldlw_block, dlw_block );
}

// Initialize the factory (no TYR block)
template<typename IncomingParticleType, typename OutgoingParticleType>
void NuclearScatteringDistributionACEFactory<IncomingParticleType,
					     OutgoingParticleType>::initialize(
		   const Utility::ArrayView<const double> mtr_block,
		   const Utility::ArrayView<const double> land_block,
		   const Utility::ArrayView<const double> and_block,
		   const Utility::ArrayView<const double> ldlw_block,
		   const Utility::ArrayView<const double> dlw_block )
{
  // Create a fictitious TYR block (all multiplicity 1 in lab system)
  std::vector<double> dummy_tyr_block( mtr_block.size(), 1.0 );

  initializeReactionOrderingMap( mtr_block,
                                 Utility::arrayViewOfConst(dummy_tyr_block) );
  initializeReactionRefFrameMap( mtr_block,
                                 Utility::arrayViewOfConst(dummy_tyr_block) );
  initializeReactionAngularDistStartIndexMap( land_block );
  initializeReactionAngularDistMap( land_block, and_block );
  initializeReactionEnergyDistStartIndexMap( ldlw_block );
  initializeReactionEnergyDistMap( ldlw_block, dlw_block );
}

// Create the scattering distribution
template<typename IncomingParticleType, typename OutgoingParticleType>
void NuclearScatteringDistributionACEFactory<IncomingParticleType,OutgoingParticleType>::getReactionsWithScatteringDistributions(
			      std::unordered_set<unsigned>& reactions ) const
{
  std::unordered_map<unsigned,unsigned>::const_iterator reaction =
    d_reaction_energy_dist_start_index.begin();

  while( reaction != d_reaction_energy_dist_start_index.end() )
  {
    reactions.insert( reaction->first );

    ++reaction;
  }

  // Check if elastic scattering must be added
  if( this->isElasticScatteringImplicit() )
    reactions.insert( 2 );
}

// Check if a reaction has a scattering distribution
template<typename IncomingParticleType, typename OutgoingParticleType>
bool NuclearScatteringDistributionACEFactory<IncomingParticleType,
					     OutgoingParticleType>::doesReactionHaveScatteringDistribution(
						const unsigned reaction ) const
{
  bool valid_reaction = false;

  // If elastic reaction and elastic is treated implicitly - true
  if( this->isElasticScatteringImplicit() && reaction == 2 )
    valid_reaction = true;
  else
  {
    if( d_reaction_energy_dist_start_index.find( reaction ) !=
	d_reaction_energy_dist_start_index.end() )
      valid_reaction = true;
  }

  return valid_reaction;
}

// Create the scattering distribution
template<typename IncomingParticleType, typename OutgoingParticleType>
void NuclearScatteringDistributionACEFactory<IncomingParticleType,
					OutgoingParticleType>::createScatteringDistribution(
                  const unsigned reaction_type,
                  const SimulationProperties& properties,
		  std::shared_ptr<const DistributionType>& distribution ) const
{
  // Make sure the reaction type has a scattering distribution (mult > 0)
  testPrecondition( this->doesReactionHaveScatteringDistribution( 
					         reaction_type ) );

  // Create an angular distribution if scattering laws 44/61/67 are not used
  if( !d_reactions_with_coupled_energy_angle_dist.count( reaction_type ) )
  {
    std::shared_ptr<const NuclearScatteringAngularDistribution>
      angular_distribution;

    if( !d_reactions_with_isotropic_scattering_only.count( reaction_type ) )
    {
      NuclearScatteringAngularDistributionACEFactory::createDistribution(
       d_reaction_angular_dist.find( reaction_type )->second,
       d_reaction_angular_dist_start_index.find( reaction_type )->second,
       d_table_name,
       reaction_type,
       angular_distribution );
    }
    // Create a purely isotropic scattering angle distribution
    else
    {
      NuclearScatteringAngularDistributionACEFactory::createIsotropicDistribution(
					    angular_distribution );
    }

    // Special Case: elastic scattering will have no energy distribution
    if( this->isElasticScatteringImplicit() && reaction_type == 2 )
    {
      this->createElasticScatteringDistribution(
		                    distribution,
                        d_table_name,
		                    d_reaction_cm_scattering.find( reaction_type )->second,
                        d_atomic_weight_ratio,
                        properties.getFreeGasThreshold(),
                        angular_distribution );

    }
    // Create all other scattering distributions using the energy dist factory
    else
    {
      std::shared_ptr<const NuclearScatteringEnergyDistribution>
        energy_distribution;

      NuclearScatteringEnergyDistributionACEFactory::createDistribution(
       	      d_reaction_energy_dist.find( reaction_type )->second,
       	      d_reaction_energy_dist_start_index.find( reaction_type )->second,
       	      d_table_name,
       	      reaction_type,
              energy_distribution,
              d_atomic_weight_ratio );

      // Test that law 3 distributions are always in the CM system
      if( energy_distribution->getLaw() == 3 )
      {
	TEST_FOR_EXCEPTION( !(d_reaction_cm_scattering.find(
						      reaction_type )->second),
			    std::runtime_error,
			    "MT# " << reaction_type << " in ACE table "
			    << d_table_name << " uses ACE Law 3, which must "
			    "be in the CM system. The ref. frame specified is "
			    "the lab indicating that there is an error in the "
			    "ACE table!" );
      }

      if( d_reaction_cm_scattering.find( reaction_type )->second )
      {
	distribution.reset(
			   new IndependentEnergyAngleNuclearScatteringDistribution<IncomingParticleType,OutgoingParticleType,CMSystemConversionPolicy>(
						      d_atomic_weight_ratio,
						      energy_distribution,
						      angular_distribution ) );
      }
      else
      {
	distribution.reset(
			   new IndependentEnergyAngleNuclearScatteringDistribution<IncomingParticleType,OutgoingParticleType,LabSystemConversionPolicy>(
						      d_atomic_weight_ratio,
						      energy_distribution,
						      angular_distribution ) );
      }
    }
  }
  // Create a coupled angular-energy distribution (law 44)
  else
  {
    unsigned acelaw =
      NuclearScatteringEnergyDistributionACEFactory::determineCoupledDistribution(
              d_atomic_weight_ratio,
     	        d_reaction_energy_dist.find( reaction_type )->second,
     	        d_reaction_energy_dist_start_index.find( reaction_type )->second,
	            d_table_name );

    if( acelaw == 44 )
    {
      NuclearScatteringEnergyDistributionACEFactory::createAceLaw44Distribution(
              d_atomic_weight_ratio,
              d_reaction_energy_dist.find( reaction_type )->second,
              d_reaction_energy_dist_start_index.find( reaction_type )->second,
              d_table_name,
              reaction_type,
              d_reaction_cm_scattering.find( reaction_type )->second,
              distribution );
    }
    else if( acelaw == 61 )
    {
      NuclearScatteringEnergyDistributionACEFactory::createAceLaw61Distribution(
              d_atomic_weight_ratio,
              d_reaction_energy_dist.find( reaction_type )->second,
              d_reaction_energy_dist_start_index.find( reaction_type )->second,
              d_table_name,
              reaction_type,
              d_reaction_cm_scattering.find( reaction_type )->second,
              distribution );
    }
    else
    {
      THROW_EXCEPTION( std::runtime_error, "The coupled angle-energy "
        "distribution ace law " << acelaw << " was found. Currently ace laws"
        " 44 and 61 are the only supported coupled angle-energy laws." );
    }
  }
}

// Returns a map of the reaction types (MT #s) and their AND block ordering
template<typename IncomingParticleType, typename OutgoingParticleType>
const std::unordered_map<unsigned,unsigned>&
NuclearScatteringDistributionACEFactory<IncomingParticleType,
					OutgoingParticleType>::getReactionOrdering() const
{
  return d_reaction_ordering;
}

// Returns a map of the reaction types (MT #s) and the scattering ref. frame
// Note: True = center-of-mass, False = lab
template<typename IncomingParticleType, typename OutgoingParticleType>
const std::unordered_map<unsigned,bool>&
NuclearScatteringDistributionACEFactory<IncomingParticleType,
					OutgoingParticleType>::getReactionCMScattering() const
{
  return d_reaction_cm_scattering;
}

// Returns a set of the reaction types (MT #s) with isotropic scattering only
template<typename IncomingParticleType, typename OutgoingParticleType>
const std::unordered_set<unsigned>&
NuclearScatteringDistributionACEFactory<IncomingParticleType,
					OutgoingParticleType>::getReactionsWithIsotropicScatteringOnly() const
{
  return d_reactions_with_isotropic_scattering_only;
}

// Returns a set of the reaction types (MT #s) with coupled energy-angle dist
template<typename IncomingParticleType, typename OutgoingParticleType>
const std::unordered_set<unsigned>&
NuclearScatteringDistributionACEFactory<IncomingParticleType,
					OutgoingParticleType>::getReactionsWithCoupledEnergyAngleDist() const
{
  return d_reactions_with_coupled_energy_angle_dist;
}

// Returns a map of the reaction types (MT #s) and the corresp. angular dist
template<typename IncomingParticleType, typename OutgoingParticleType>
const std::unordered_map<unsigned,Utility::ArrayView<const double> >&
NuclearScatteringDistributionACEFactory<IncomingParticleType,
					OutgoingParticleType>::getReactionAngularDist() const
{
  return d_reaction_angular_dist;
}

// Returns a map of the reaction types (MT #s) and angular dist start index
template<typename IncomingParticleType, typename OutgoingParticleType>
const std::unordered_map<unsigned,unsigned>&
NuclearScatteringDistributionACEFactory<IncomingParticleType,
					OutgoingParticleType>::getReactionAngularDistStartIndex() const
{
  return d_reaction_angular_dist_start_index;
}

// Returns a map of the reaction types (MT #s) and the corresp. energy dist
template<typename IncomingParticleType, typename OutgoingParticleType>
const std::unordered_map<unsigned,Utility::ArrayView<const double> >&
NuclearScatteringDistributionACEFactory<IncomingParticleType,
					OutgoingParticleType>::getReactionEnergyDist() const
{
  return d_reaction_energy_dist;
}

// Returns a map of the reaction types (MT #s) and energy dist start index
template<typename IncomingParticleType, typename OutgoingParticleType>
const std::unordered_map<unsigned,unsigned>&
NuclearScatteringDistributionACEFactory<IncomingParticleType,
					OutgoingParticleType>::getReactionEnergyDistStartIndex() const
{
  return d_reaction_energy_dist_start_index;
}

// Initialize the reaction type ordering map
template<typename IncomingParticleType, typename OutgoingParticleType>
void NuclearScatteringDistributionACEFactory<IncomingParticleType,
					     OutgoingParticleType>::initializeReactionOrderingMap(
			   const Utility::ArrayView<const double>& mtr_block,
			   const Utility::ArrayView<const double>& tyr_block )
{
  for( unsigned i = 0; i < mtr_block.size(); ++i )
  {
    unsigned reaction = static_cast<unsigned>( mtr_block[i] );

    if( tyr_block[i] != 0 )
      d_reaction_ordering[reaction] = i;
  }
}

// Initialize the reaction type scattering ref. frame map
template<typename IncomingParticleType, typename OutgoingParticleType>
void NuclearScatteringDistributionACEFactory<IncomingParticleType,
					     OutgoingParticleType>::initializeReactionRefFrameMap(
			   const Utility::ArrayView<const double>& mtr_block,
			   const Utility::ArrayView<const double>& tyr_block )
{
  std::unordered_map<unsigned,unsigned>::const_iterator
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

  // Add the elastic scattering case (always CM) if elastic is implicit
  if( this->isElasticScatteringImplicit() )
    d_reaction_cm_scattering[2u] = true;
}

// Initialize the reaction type angular distribution start index map
template<typename IncomingParticleType, typename OutgoingParticleType>
void NuclearScatteringDistributionACEFactory<IncomingParticleType,
					     OutgoingParticleType>::initializeReactionAngularDistStartIndexMap(
			  const Utility::ArrayView<const double>& land_block )
{
  unsigned elastic_increment;

  // Add elastic scattering separately (always first in LAND block if
  // elastic scattering is implicit)
  if( this->isElasticScatteringImplicit() )
  {
    d_reaction_angular_dist_start_index[2u] = 0;

    elastic_increment = 1u;
  }
  else
    elastic_increment = 0u;

  // Add all other reactions
  std::unordered_map<unsigned,unsigned>::const_iterator
    reaction_order, end_reaction_order;
  reaction_order = d_reaction_ordering.begin();
  end_reaction_order = d_reaction_ordering.end();

  while( reaction_order != end_reaction_order )
  {
    int land_block_value = static_cast<int>(
		      land_block[reaction_order->second + elastic_increment] );

    // Only positive values represent an index: 0, -1 have special meaning
    if( land_block_value > 0 )
    {
      // Subtract by one to get C-array index
      d_reaction_angular_dist_start_index[reaction_order->first] =
        static_cast<unsigned>( land_block_value ) - 1u;
    }

    ++reaction_order;
  }
}

// Initialize the reaction type angular distribution map
template<typename IncomingParticleType, typename OutgoingParticleType>
void NuclearScatteringDistributionACEFactory<IncomingParticleType,
					     OutgoingParticleType>::initializeReactionAngularDistMap(
			   const Utility::ArrayView<const double>& land_block,
			   const Utility::ArrayView<const double>& and_block )
{
  // Calculate the size of each angular distribution array
  std::vector<unsigned> angular_dist_array_sizes;
  calculateDistArraySizes( land_block,
			   and_block,
			   angular_dist_array_sizes );

  unsigned elastic_increment;

  // If elastic scattering is implicit, handle it separately
  if( this->isElasticScatteringImplicit() )
  {
    d_reaction_angular_dist[2u] =
      and_block( 0u, angular_dist_array_sizes[0] );

    elastic_increment = 1u;
  }
  else
    elastic_increment = 0u;

  // Handle all other distributions
  std::unordered_map<unsigned,unsigned>::const_iterator
    reaction_order, end_reaction_order;
  reaction_order = d_reaction_ordering.begin();
  end_reaction_order = d_reaction_ordering.end();

  // Elastic scattering will always be the first entry in the land block -
  // increment all indices by 1 to account for this
  while( reaction_order != end_reaction_order )
  {
    // index may be negative to signify special cases
    int dist_index = static_cast<int>(
			land_block[reaction_order->second+elastic_increment] );

    // An angular distribution is present
    if( dist_index > 0 )
    {
      int dist_array_size =
	angular_dist_array_sizes[reaction_order->second+elastic_increment];

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
      THROW_EXCEPTION( std::runtime_error,
		       "Unknown angular distribution index ("
		       << dist_index << ") found in table "
		       << d_table_name << " for MT = "
		       << reaction_order->first );
    }

    ++reaction_order;
  }

  // Check that every reaction has been found
  testPostcondition( d_reaction_angular_dist.size() +
		     d_reactions_with_isotropic_scattering_only.size() +
		     d_reactions_with_coupled_energy_angle_dist.size() ==
		     d_reaction_ordering.size() + elastic_increment );
}

// Initialize the reaction type energy distribution start index map
template<typename IncomingParticleType, typename OutgoingParticleType>
void NuclearScatteringDistributionACEFactory<IncomingParticleType,
					     OutgoingParticleType>::initializeReactionEnergyDistStartIndexMap(
			  const Utility::ArrayView<const double>& ldlw_block )
{
  // Add all other reactions
  std::unordered_map<unsigned,unsigned>::const_iterator
    reaction_order, end_reaction_order;
  reaction_order = d_reaction_ordering.begin();
  end_reaction_order = d_reaction_ordering.end();

  while( reaction_order != end_reaction_order )
  {
    // Subtract by one to get C-array index
    d_reaction_energy_dist_start_index[reaction_order->first] =
      static_cast<unsigned>( ldlw_block[reaction_order->second] ) - 1u;

    ++reaction_order;
  }
}

// Initialize the reaction type energy distribution map
template<typename IncomingParticleType, typename OutgoingParticleType>
void NuclearScatteringDistributionACEFactory<IncomingParticleType,
					     OutgoingParticleType>::initializeReactionEnergyDistMap(
			   const Utility::ArrayView<const double>& ldlw_block,
			   const Utility::ArrayView<const double>& dlw_block )
{
  // Calculate the size of each energy distribution array
  std::vector<unsigned> energy_dist_array_sizes;
  calculateDistArraySizes( ldlw_block,
			   dlw_block,
			   energy_dist_array_sizes );

  // Handle all other distributions
  std::unordered_map<unsigned,unsigned>::const_iterator
    reaction_order, end_reaction_order;
  reaction_order = d_reaction_ordering.begin();
  end_reaction_order = d_reaction_ordering.end();

  while( reaction_order != end_reaction_order )
  {
    int dist_index = static_cast<int>( ldlw_block[reaction_order->second] );

    int dist_array_size = energy_dist_array_sizes[reaction_order->second];

    d_reaction_energy_dist[reaction_order->first] =
      dlw_block( dist_index - 1u, dist_array_size );

    ++reaction_order;
  }

  // Check that every reaction has been found
  testPostcondition( d_reaction_energy_dist.size() ==
		     d_reaction_ordering.size() );
}

class NeutronState;
class PhotonState;

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( NuclearScatteringDistributionACEFactory<NeutronState,PhotonState> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( NuclearScatteringDistributionACEFactory<PhotonState,NeutronState> );

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_NUCLEAR_SCATTERING_DISTRIBUTION_ACE_FACTORY_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclearScatteringDistributionACEFactory_def.hpp
//---------------------------------------------------------------------------//
