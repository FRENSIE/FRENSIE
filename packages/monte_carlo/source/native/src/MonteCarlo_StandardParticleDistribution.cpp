//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardParticleDistribution.cpp
//! \author Alex Robinson
//! \brief  Standard particle distribution definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <functional>

// FRENSIE Includes
#include "MonteCarlo_StandardParticleDistribution.hpp"
#include "MonteCarlo_IndependentPhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_PhaseSpacePoint.hpp"
#include "Utility_DeltaDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
StandardParticleDistribution::StandardParticleDistribution(
   const ModuleTraits::InternalROIHandle id,
   const std::string& name,
   const std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>&
   spatial_coord_conversion_policy,
   const std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>&
   directional_coord_conversion_policy )
  : ParticleDistribution( id, name ),
    d_spatial_coord_conversion_policy( spatial_coord_conversion_policy ),
    d_directional_coord_conversion_policy( directional_coord_conversion_policy ),
    d_independent_dimensions(),
    d_dimension_distributions(),
    d_ready( false )
{
  // Make sure that the spatial coordinate conversion policy is valid
  testPrecondition( spatial_coord_conversion_policy.get() );
  // Make sure that the directional coordinate conversion policy is valid
  testPrecondition( directional_coord_conversion_policy.get() );

  // Initialize the distribution
  this->reset();
}

// Set a dimension distribution
void StandardParticleDistribution::setDimensionDistribution(
                        const std::shared_ptr<PhaseSpaceDimensionDistribution>&
                        dimension_distribution )
{
  // Make sure that the distribution is valid
  testPrecondition( dimension_distribution.get() );
  
  if( !d_ready )
  {
    // Add the distribution to the dimension distribution map
    d_dimension_distributions[dimension_distribution->getDimension()] =
      dimension_distribution;
    
    // Check if the distribution is independent
    if( dimension_distribution->isIndependent() )
      d_independent_dimensions.insert( dimension_distribution->getDimension() );
  }
  else
  {
    FRENSIE_LOG_WARNING( "Unable to add distribution for "
                         << dimension_distribution->getDimension() <<
                         " because the particle distribution "
                         << this->getName() << " has already been "
                         "initialized!" );
  }
}

// Construct the dimension distribution dependency tree
void StandardParticleDistribution::constructDimensionDistributionDependencyTree()
{
  if( !d_ready )
  {
    DimensionDistributionMap::iterator parent_distribution_it,
      parent_distribution_end;

    parent_distribution_it = d_dimension_distributions.begin();
    parent_distribution_end = d_dimension_distributions.end();

    // Loop over all distributions and check for dependent distributions
    while( parent_distribution_it != parent_distribution_end )
    {
      DimensionDistributionMap::iterator potential_child_distribution_it,
      potential_child_distribution_end;

      potential_child_distribution_it = d_dimension_distributions.begin();
      potential_child_distribution_end = d_dimension_distributions.end();

      // Check if any distributions are dependent on the current parent
      // distribution
      while( potential_child_distribution_it != potential_child_distribution_end )
      {
        // Add the child distribution to the parent
        if( potential_child_distribution_it->second->isDependentOnDimension(
                             parent_distribution_it->second->getDimension() ) )
        {
          parent_distribution_it->second->addDependentDistribution(
                                     potential_child_distribution_it->second );
        }

        ++potential_child_distribution_it;
      }

      ++parent_distribution_it;
    }

    // Indicate that the distribution is ready for use
    d_ready = true;
  }
  else
  {
    FRENSIE_LOG_WARNING( "Unable to construct the dependency tree for "
                         "particle distribution " << this->getName() <<
                         " because it has already been constructed!" );
  }
}

// Reset the distribution
void StandardParticleDistribution::reset()
{
  // Clear the dimension distribution data
  d_independent_dimensions.clear();
  d_dimension_distributions.clear();

  // Initialize the default dimension distributions
  // The spatial distribution will be model a point at the origin by default
  {
    std::shared_ptr<const Utility::OneDDistribution> raw_spatial_distribution( 
                                       new Utility::DeltaDistribution( 0.0 ) );
    
    d_dimension_distributions[PRIMARY_SPATIAL_DIMENSION].reset(
     new IndependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION>(
                                                  raw_spatial_distribution ) );
                                   
  
    d_dimension_distributions[SECONDARY_SPATIAL_DIMENSION].reset(
     new IndependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION>(
                                                  raw_spatial_distribution ) );
  
    d_dimension_distributions[TERTIARY_SPATIAL_DIMENSION].reset(
     new IndependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION>(
                                                  raw_spatial_distribution ) );
  }
  
  if( d_directional_coord_conversion_policy->getLocalDirectionalCoordinateSystemType() ==
      Utility::CARTESIAN_DIRECTIONAL_COORDINATE_SYSTEM )
  {
    std::shared_ptr<const Utility::OneDDistribution>
      raw_directional_distribution( 
                          new Utility::UniformDistribution( -1.0, 1.0, 1.0 ) );
  
    d_dimension_distributions[PRIMARY_DIRECTIONAL_DIMENSION].reset(
     new IndependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION>(
                                              raw_directional_distribution ) );
    
    d_dimension_distributions[SECONDARY_DIRECTIONAL_DIMENSION].reset(
     new IndependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION>(
                                              raw_directional_distribution ) );
    d_dimension_distributions[TERTIARY_DIRECTIONAL_DIMENSION].reset(
     new IndependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION>(
                                              raw_directional_distribution ) );
  }
  // If the local directional coordinate system is spherical an isotropic
  // distribution will be created by default
  else 
  {
    d_dimension_distributions[PRIMARY_DIRECTIONAL_DIMENSION].reset(
     new IndependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION>(
                 std::shared_ptr<const Utility::OneDDistribution>(
                                   new Utility::DeltaDistribution( 1.0 ) ) ) );
    d_dimension_distributions[SECONDARY_DIRECTIONAL_DIMENSION].reset(
     new IndependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION>(
                 std::shared_ptr<const Utility::OneDDistribution>(
                      new Utility::UniformDistribution(
                            0.0, 2*Utility::PhysicalConstants::pi, 1.0 ) ) ) );
    
    d_dimension_distributions[TERTIARY_DIRECTIONAL_DIMENSION].reset(
     new IndependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION>(
                 std::shared_ptr<const Utility::OneDDistribution>(
                      new Utility::UniformDistribution( -1.0, 1.0, 1.0 ) ) ) );
  }

  // The default energy is 1.0
  d_dimension_distributions[ENERGY_DIMENSION].reset(
   new IndependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION>(
                 std::shared_ptr<const Utility::OneDDistribution>(
                                   new Utility::DeltaDistribution( 1.0 ) ) ) );

  // The default time is 0.0
  d_dimension_distributions[TIME_DIMENSION].reset(
   new IndependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION>(
                 std::shared_ptr<const Utility::OneDDistribution>(
                                   new Utility::DeltaDistribution( 0.0 ) ) ) );

  // The default weight is 1.0
  d_dimension_distributions[WEIGHT_DIMENSION].reset(
   new IndependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION>(
                 std::shared_ptr<const Utility::OneDDistribution>(
                                   new Utility::DeltaDistribution( 1.0 ) ) ) );

  // Indicate that the distribution is not ready for use - the dimension
  // dependency tree must still be created
  d_ready = false;
}

// Return the dimension distribution type name
std::string StandardParticleDistribution::getDimensionDistributionTypeName(
                                    const PhaseSpaceDimension dimension ) const
{
  // Make sure that the dimension has a distribution defined
  testPrecondition( this->doesDimensionHaveDistributionDefined( dimension ) );

  return d_dimension_distributions.find(dimension)->second->getDistributionTypeName();
}

// Check if the distribution is spatially uniform (somewhere)
/*! \details This method will simply check if the region where the
 * spatial distributions are defined correspond to uniform spatial 
 * distribution of particles. 
 */
bool StandardParticleDistribution::isSpatiallyUniform() const
{
  // Check the primary spatial dimension distribution
  if( d_spatial_coord_conversion_policy->getLocalSpatialCoordinateSystemType() ==
      Utility::CARTESIAN_SPATIAL_COORDINATE_SYSTEM )
  {
    if( !d_dimension_distributions.find( PRIMARY_SPATIAL_DIMENSION )->second->isUniform() )
      return false;
  }
  else if( d_spatial_coord_conversion_policy->getLocalSpatialCoordinateSystemType() ==
           Utility::CYLINDRICAL_SPATIAL_COORDINATE_SYSTEM )
  {
    if( !d_dimension_distributions.find( PRIMARY_SPATIAL_DIMENSION )->second->hasForm( Utility::POWER_1_DISTRIBUTION ) )
      return false;
  }
  else
  {
    if( !d_dimension_distributions.find( PRIMARY_SPATIAL_DIMENSION )->second->hasForm( Utility::POWER_2_DISTRIBUTION ) )
      return false;
  }
  
  // Check the secondary spatial dimension distribution
  if( !d_dimension_distributions.find( SECONDARY_SPATIAL_DIMENSION )->second->isUniform() )
    return false;

  // Check the tertiary spatial dimension distribution
  if( !d_dimension_distributions.find( TERTIARY_SPATIAL_DIMENSION )->second->isUniform() )
    return false;

  return true;
}

// Check if the distribution is directionally uniform (isotropic)
/*! \details This method will simply check if the solid angle where
 * the directional distributions are defined correspond to an isotropic 
 * distribution of particle directions.
 */
bool StandardParticleDistribution::isDirectionallyUniform() const
{
  // Directional dimension distributions defined in the Cartesian coordinate
  // system cannot be isotropic
  if( d_directional_coord_conversion_policy->getLocalDirectionalCoordinateSystemType() ==
      Utility::SPHERICAL_DIRECTIONAL_COORDINATE_SYSTEM )
  {
    if( !d_dimension_distributions.find( SECONDARY_DIRECTIONAL_DIMENSION )->second->isUniform() )
      return false;

    if( !d_dimension_distributions.find( TERTIARY_DIRECTIONAL_DIMENSION )->second->isUniform() )
      return false;

    return true;
  }
  else
    return false;
}

// Evaluate the distribution at the desired phase space point
double StandardParticleDistribution::evaluate(
                                          const ParticleState& particle ) const
{
  if( d_ready )
  {
    // Convert the particle to a phase space point
    PhaseSpacePoint phase_space_point( particle,
                                       d_spatial_coord_conversion_policy,
                                       d_directional_coord_conversion_policy );

    double distribution_value = 1.0;

    // Evaluate the distribution at the phase space point
    DimensionDistributionMap::const_iterator
      dimension_dist_it = d_dimension_distributions.begin();
    
    // Each dimension distribution will be evaluated individually (without
    // cascading to dependent distributions)
    while( dimension_dist_it != d_dimension_distributions.end() )
    {
      distribution_value *=
        dimension_dist_it->second->evaluateWithoutCascade( phase_space_point );
      
      ++dimension_dist_it;
    }

    return distribution_value;
  }
  else
  {
    FRENSIE_LOG_WARNING( "Unable to evaluate particle distribution "
                         << this->getName() << " because it is not ready!" );
    return 0.0;
  }
}

// Sample a particle state from the distribution
void StandardParticleDistribution::sample( ParticleState& particle ) const
{
  if( d_ready )
  {
    // Create the dimension sampling functor
    DimensionSamplingFunction dimension_sample_functor =
      std::bind<void>( &PhaseSpaceDimensionDistribution::sampleWithCascade,
                       std::placeholders::_1,
                       std::placeholders::_2 );

    this->sampleImpl( dimension_sample_functor, particle );
  }
  else
  {
    FRENSIE_LOG_WARNING( "Unable to sample a particle state with particle "
                         "distribution " << this->getName() << " becuase the "
                         "distribution is not ready!" );
  }
}

// Sample a particle state from the dist. and record the number of trials
void StandardParticleDistribution::sampleAndRecordTrials(
                                       ParticleState& particle,
                                       DimensionCounterMap& trials ) const
{
  if( d_ready )
  {
    // Create the dimension sampling functor
    DimensionSamplingFunction dimension_sample_functor =
      std::bind<void>(
            &PhaseSpaceDimensionDistribution::sampleAndRecordTrialsWithCascade,
            std::placeholders::_1,
            std::placeholders::_2,
            std::ref( trials ) );

    this->sampleImpl( dimension_sample_functor, particle );
  }
  else
  {
    FRENSIE_LOG_WARNING( "Unable to sample a particle state with particle "
                         "distribution " << this->getName() << " becuase the "
                         "distribution is not ready!" );
  }
}

// Sample a particle state with the desired dimension value
void StandardParticleDistribution::sampleWithDimensionValue(
                                           ParticleState& particle,
                                           const PhaseSpaceDimension dimension,
                                           const double dimension_value ) const
{
  if( d_ready )
  {
    // Create the dimension sampling functor
    DimensionSamplingFunction dimension_sample_functor =
      std::bind<void>(
       &PhaseSpaceDimensionDistribution::sampleWithCascadeUsingDimensionValue,
       std::placeholders::_1,
       std::placeholders::_2,
       dimension,
       dimension_value );

    this->sampleImpl( dimension_sample_functor, particle );
  }
  else
  {
    FRENSIE_LOG_WARNING( "Unable to sample a particle state with particle "
                         "distribution " << this->getName() << " becuase the "
                         "distribution is not ready!" );
  }
}

// Sample a particle state with the desired dim. value and record trials
void StandardParticleDistribution::sampleWithDimensionValueAndRecordTrials(
                                           ParticleState& particle,
                                           DimensionCounterMap& trials,
                                           const PhaseSpaceDimension dimension,
                                           const double dimension_value ) const
{
  if( d_ready )
  {
    // Create the dimension sampling functor
    DimensionSamplingFunction dimension_sample_functor =
      std::bind<void>(
       &PhaseSpaceDimensionDistribution::sampleAndRecordTrialsWithCascadeUsingDimensionValue,
       std::placeholders::_1,
       std::placeholders::_2,
       std::ref( trials ),
       dimension,
       dimension_value );

    this->sampleImpl( dimension_sample_functor, particle );
  }
  else
  {
    FRENSIE_LOG_WARNING( "Unable to sample a particle state with particle "
                         "distribution " << this->getName() << " becuase the "
                         "distribution is not ready!" );
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardParticleDistribution.cpp
//---------------------------------------------------------------------------//
