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
#include "MonteCarlo_PhaseSpacePoint.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
StandardParticleDistribution::StandardParticleDistribution(
   const ModuleTraits::InternalROIHandle id,
   const std::string& name,
   const DimensionSet& independent_dimensions,
   const DimensionDistributionMap& dimension_distributions,
   const std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>&
   spatial_coord_conversion_policy,
   const std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>&
   directional_coord_conversion_policy )
  : ParticleDistribution( id, name ),
    d_independent_dimensions( independent_dimensions ),
    d_dimension_distributions( dimension_distributions ),
    d_spatial_coord_conversion_policy( spatial_coord_conversion_policy ),
    d_directional_coord_conversion_policy( directional_coord_conversion_policy )
{
  // Make sure that the dimension data is valid
  testPrecondition( this->isDimensionDataValid() );
  // Make sure that the spatial coordinate conversion policy is valid
  testPrecondition( spatial_coord_conversion_policy.get() );
  // Make sure that the directional coordinate conversion policy is valid
  testPrecondition( directional_coord_conversion_policy.get() );
}

// Check if the dimension data is valid
bool StandardParticleDistribution::isDimensionDataValid() const
{
  bool valid_data = true;
  
  // Check that the independent dimensions can be found in the dimension
  // distribution map
  DimensionSet::const_iterator indep_dimension_it = 
    d_independent_dimensions.begin();

  while( indep_dimension_it != d_independent_dimensions.end() )
  {
    if( !d_dimension_distributions.count( *indep_dimension_it ) )
    {
      valid_data = false;

      break;
    }
    
    ++indep_dimension_it;
  }

  return valid_data;
}

// Check if a dimension has a distribution defined
bool StandardParticleDistribution::doesDimensionHaveDistributionDefined(
                                    const PhaseSpaceDimension dimension ) const
{
  return d_dimension_distributions.find( dimension ) !=
    d_dimension_distributions.end();
}

// Return the dimensions with distributions defined
void StandardParticleDistribution::getDimensionsWithDistributionsDefined(
                                               DimensionSet& dimensions ) const
{
  DimensionDistributionMap::const_iterator dimension_dist_map_it =
    d_dimension_distributions.begin();

  while( dimension_dist_map_it != d_dimension_distributions.end() )
  {
    dimensions.insert( dimension_dist_map_it->first );

    ++dimension_dist_map_it;
  }
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

// Sample a particle state from the distribution
void StandardParticleDistribution::sample( ParticleState& particle ) const
{
  // Create the dimension sampling functor
  DimensionSamplingFunction dimension_sample_functor =
    std::bind<void>( &PhaseSpaceDimensionDistribution::sampleWithCascade,
                     std::placeholders::_1,
                     std::placeholders::_2 );

  this->sampleImpl( dimension_sample_functor, particle );
}

// Sample a particle state from the dist. and record the number of trials
void StandardParticleDistribution::sampleAndRecordTrials(
                                       ParticleState& particle,
                                       DimensionCounterMap& trials ) const
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

// Sample a particle state with the desired dimension value
void StandardParticleDistribution::sampleWithDimensionValue(
                                           ParticleState& particle,
                                           const PhaseSpaceDimension dimension,
                                           const double dimension_value ) const
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

// Sample a particle state with the desired dim. value and record trials
void StandardParticleDistribution::sampleWithDimensionValueAndRecordTrials(
                                           ParticleState& particle,
                                           DimensionCounterMap& trials,
                                           const PhaseSpaceDimension dimension,
                                           const double dimension_value ) const
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

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardParticleDistribution.cpp
//---------------------------------------------------------------------------//
