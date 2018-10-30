//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardParticleDistribution.cpp
//! \author Alex Robinson
//! \brief  Standard particle distribution definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_StandardParticleDistribution.hpp"
#include "MonteCarlo_IndependentPhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_PhaseSpacePoint.hpp"
#include "Utility_BasicCartesianCoordinateConversionPolicy.hpp"
#include "Utility_BasicSphericalCoordinateConversionPolicy.hpp"
#include "Utility_DeltaDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_ToStringTraits.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Default Constructor
StandardParticleDistribution::StandardParticleDistribution()
  : StandardParticleDistribution( "standard particle distribution" )
{ /* ... */ }

// Basic Constructor
StandardParticleDistribution::StandardParticleDistribution(
                                                      const std::string& name )
  : ParticleDistribution( name ),
    d_spatial_coord_conversion_policy( new Utility::BasicCartesianCoordinateConversionPolicy ),
    d_directional_coord_conversion_policy( new Utility::BasicSphericalCoordinateConversionPolicy ),
    d_independent_dimensions(),
    d_dimension_distributions(),
    d_ready( false )
{
  // Initialize the distribution
  this->reset();
}

// Constructor
StandardParticleDistribution::StandardParticleDistribution(
   const std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>&
   spatial_coord_conversion_policy,
   const std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>&
   directional_coord_conversion_policy )
  : StandardParticleDistribution( "standard particle distribution",
                                  spatial_coord_conversion_policy,
                                  directional_coord_conversion_policy )
{ /* ... */ }

// Constructor
StandardParticleDistribution::StandardParticleDistribution(
   const std::string& name,
   const std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>&
   spatial_coord_conversion_policy,
   const std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>&
   directional_coord_conversion_policy )
  : ParticleDistribution( name ),
    d_spatial_coord_conversion_policy( spatial_coord_conversion_policy ),
    d_directional_coord_conversion_policy( directional_coord_conversion_policy ),
    d_independent_dimensions(),
    d_dimension_distributions(),
    d_ready( false )
{
  // Make sure that the conversion policies are valid
  testPrecondition( spatial_coord_conversion_policy.get() );
  testPrecondition( directional_coord_conversion_policy.get() );

  // Initialize the distribution
  this->reset();
}

// Set a dimension distribution
/*! \details This will destroy the current dependency tree. You will not be
 * able to evaluate or sample from the particle distribution until the
 * dependency tree has been constructed again. If multiple dimension
 * distributions must be set, construct the tree after setting all of them
 * so that the tree isn't constructed multiple times.
 */
void StandardParticleDistribution::setDimensionDistribution(
                        const std::shared_ptr<PhaseSpaceDimensionDistribution>&
                        dimension_distribution )
{
  // Make sure that the distribution is valid
  testPrecondition( dimension_distribution.get() );

  // Add the distribution to the dimension distribution map
  d_dimension_distributions[dimension_distribution->getDimension()] =
    dimension_distribution;

  // The dependency tree needs to be constructed again.
  if( d_ready )
    d_ready = false;
}

// Set the energy that will be sampled by the distribution
/*! \details This method can be used to quickly set up a mono-energetic source
 * distribution. This will destroy the current dependency tree. You will not
 * be able to evaluate or sample from the particle distribution until the
 * dependency tree has been constructed again.
 */
void StandardParticleDistribution::setEnergy( const double energy )
{
  std::shared_ptr<const Utility::UnivariateDistribution>
    raw_energy_distribution( new Utility::DeltaDistribution( energy ) );

  this->setDimensionDistribution( std::shared_ptr<PhaseSpaceDimensionDistribution>( new IndependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION>( raw_energy_distribution ) ) );
}

// Set the time that will be sampled by the distribution
/*! \details This method can be used to quickly set up the delta-time source
 * distribution. This will destroy the current dependency tree. You will not
 * be able to evaluate or sample from the particle distribution until the
 * dependency tree has been constructed again.
 */
void StandardParticleDistribution::setTime( const double time )
{
  std::shared_ptr<const Utility::UnivariateDistribution>
    raw_time_distribution( new Utility::DeltaDistribution( time ) );

  this->setDimensionDistribution( std::shared_ptr<PhaseSpaceDimensionDistribution>( new IndependentPhaseSpaceDimensionDistribution<TIME_DIMENSION>( raw_time_distribution ) ) );
}

// Set the position of the distribution
/*! \details This method can be used to quickly set up a point distribution
 * (in the spatial dimensions). The position specified must be in global
 * coordinates. This will destroy the current dependency
 * tree. You will not be able to evaluate or sample from the particle
 * distribution until the dependency tree has been constructed again.
 */
void StandardParticleDistribution::setPosition( const double x_position,
                                                const double y_position,
                                                const double z_position )
{
  double primary_spatial_coord,
    secondary_spatial_coord,
    tertiary_spatial_coord;

  d_spatial_coord_conversion_policy->convertFromCartesianSpatialCoordinates(
      x_position, y_position, z_position,
      primary_spatial_coord, secondary_spatial_coord, tertiary_spatial_coord );

  std::shared_ptr<const Utility::UnivariateDistribution>
    raw_spatial_distribution(
                     new Utility::DeltaDistribution( primary_spatial_coord ) );

  d_dimension_distributions[PRIMARY_SPATIAL_DIMENSION].reset(
     new IndependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION>(
                                                  raw_spatial_distribution ) );

  raw_spatial_distribution.reset(
                   new Utility::DeltaDistribution( secondary_spatial_coord ) );

  d_dimension_distributions[SECONDARY_SPATIAL_DIMENSION].reset(
   new IndependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION>(
                                                  raw_spatial_distribution ) );

  raw_spatial_distribution.reset(
                    new Utility::DeltaDistribution( tertiary_spatial_coord ) );

  d_dimension_distributions[TERTIARY_SPATIAL_DIMENSION].reset(
    new IndependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION>(
                                                  raw_spatial_distribution ) );

  // The dependency tree must still be created
  d_ready = false;
}

// Set the position of the distribution
/*! \details This method can be used to quickly set up a point distribution
 * (in the spatial dimensions). The position specified must be in global
 * coordinates. This will destroy the current dependency
 * tree. You will not be able to evaluate or sample from the particle
 * distribution until the dependency tree has been constructed again.
 */
void StandardParticleDistribution::setPosition( const double position[3] )
{
  this->setPosition( position[0], position[1], position[2] );
}

// Set the direction of the distribution
/*! \details This method can be used to quickly set up a mono-directional
 * distribution (in the directional dimensions). The direction must be in
 * cartesian coordinates. This will destroy the current
 * dependency tree. You will not be able to evaluate or sample from the
 * particle distribution until the dependency tree has been constructed again.
 */
void StandardParticleDistribution::setDirection( const double x_direction,
                                                 const double y_direction,
                                                 const double z_direction )
{
  // Normalize the direction
  double normalized_x_direction = x_direction,
    normalized_y_direction = y_direction,
    normalized_z_direction = z_direction;

  Utility::normalizeVector( normalized_x_direction,
                            normalized_y_direction,
                            normalized_z_direction );

  double primary_directional_coord,
    secondary_directional_coord,
    tertiary_directional_coord;

  d_directional_coord_conversion_policy->convertFromCartesianDirectionalCoordinates(
                                        normalized_x_direction,
                                        normalized_y_direction,
                                        normalized_z_direction,
                                        primary_directional_coord,
                                        secondary_directional_coord,
                                        tertiary_directional_coord );

  std::shared_ptr<const Utility::UnivariateDistribution>
    raw_directional_distribution(
                 new Utility::DeltaDistribution( primary_directional_coord ) );

  d_dimension_distributions[PRIMARY_DIRECTIONAL_DIMENSION].reset(
     new IndependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION>(
                                              raw_directional_distribution ) );

  raw_directional_distribution.reset(
               new Utility::DeltaDistribution( secondary_directional_coord ) );

  d_dimension_distributions[SECONDARY_DIRECTIONAL_DIMENSION].reset(
   new IndependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION>(
                                              raw_directional_distribution ) );

  raw_directional_distribution.reset(
                new Utility::DeltaDistribution( tertiary_directional_coord ) );

  d_dimension_distributions[TERTIARY_DIRECTIONAL_DIMENSION].reset(
    new IndependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION>(
                                              raw_directional_distribution ) );

  // The dependency tree must still be created
  d_ready = false;
}

// Set the direction of the distribution
/*! \details This method can be used to quickly set up a mono-directional
 * distribution (in the directional dimensions). The direction must be in
 * cartesian coordinates. This will destroy the current
 * dependency tree. You will not be able to evaluate or sample from the
 * particle distribution until the dependency tree has been constructed again.
 */
void StandardParticleDistribution::setDirection( const double direction[3] )
{
  this->setDirection( direction[0], direction[1], direction[2] );
}

// Construct the dimension distribution dependency tree
/*! \details This method assigns dependent dimension distributions to the
 * required parent dimension distribution, which forms a tree. This tree is
 * primarily used for sampling from dimension distributions in the correct
 * order (parent first, then children i.e. top-down tree traversal). The
 * independent dimensions are also identified since they are considered the top
 * of the tree. If the dependency tree has already been constructed this
 * method will do nothing.
 */
void StandardParticleDistribution::constructDimensionDistributionDependencyTree()
{
  if( !d_ready )
  {
    // Clear the independent dimensions set - it will be created along with
    // the tree
    d_independent_dimensions.clear();

    DimensionDistributionMap::iterator parent_distribution_it,
      parent_distribution_end;

    parent_distribution_it = d_dimension_distributions.begin();
    parent_distribution_end = d_dimension_distributions.end();

    // Loop over all distributions and check for dependent distributions
    while( parent_distribution_it != parent_distribution_end )
    {
      // Check if the distribution is independent
      if( parent_distribution_it->second->isIndependent() )
      {
        d_independent_dimensions.insert(
                              parent_distribution_it->second->getDimension() );
      }

      // Purge any dependendent distributions from the parent
      parent_distribution_it->second->removeDependentDistributions();

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

    try{
      this->checkDependencyTreeForOrphans();
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "Invalid dependencies in particle distribution "
                             "dimensions!" );

    // Indicate that the distribution is ready for use
    d_ready = true;
  }
  else
  {
    FRENSIE_LOG_WARNING( "The dependency tree for particle distribution "
                         << this->getName() << "has already been "
                         "constructed!" );
  }
}

// Check the dependency tree for orphans
void StandardParticleDistribution::checkDependencyTreeForOrphans()
{
  DimensionDistributionMap::iterator distribution_it,
    distribution_end;

  distribution_it = d_dimension_distributions.begin();
  distribution_end = d_dimension_distributions.end();

  // Loop over all distributions and check for orphans
  while( distribution_it != distribution_end )
  {
    // Only dependent distributions can be orphans
    if( !distribution_it->second->isIndependent() )
    {
      TEST_FOR_EXCEPTION(
                   !distribution_it->second->hasParentDistribution(),
                   std::runtime_error,
                   "Invalid particle distribution! The dependent distribution "
                   "defined for the "
                   << distribution_it->second->getDimension() << " was "
                   "not adopted by the required parent dimension "
                   "distribution." );
    }

    ++distribution_it;
  }
}

// Reset the distribution
/*! \details Each dimension will use its default distribution. The
 * default distribution for a dimension is dependent on the coordinate
 * conversion policy that has been set for the particle distribution.
 */
void StandardParticleDistribution::reset()
{
  // Clear the dimension distribution data
  d_dimension_distributions.clear();

  this->resetSpatialDistributions();
  this->resetDirectionalDistributions();

  // The default energy is 1.0
  d_dimension_distributions[ENERGY_DIMENSION].reset(
   new IndependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION>(
                 std::shared_ptr<const Utility::UnivariateDistribution>(
                                   new Utility::DeltaDistribution( 1.0 ) ) ) );

  // The default time is 0.0
  d_dimension_distributions[TIME_DIMENSION].reset(
   new IndependentPhaseSpaceDimensionDistribution<TIME_DIMENSION>(
                 std::shared_ptr<const Utility::UnivariateDistribution>(
                                   new Utility::DeltaDistribution( 0.0 ) ) ) );

  // The default weight is 1.0
  d_dimension_distributions[WEIGHT_DIMENSION].reset(
   new IndependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION>(
                 std::shared_ptr<const Utility::UnivariateDistribution>(
                                   new Utility::DeltaDistribution( 1.0 ) ) ) );

  // Construct the dependency tree
  this->constructDimensionDistributionDependencyTree();
}

// Reset the spatial distributions
void StandardParticleDistribution::resetSpatialDistributions()
{
  // The spatial distribution will model a point at the origin by default
  std::shared_ptr<const Utility::UnivariateDistribution> raw_spatial_distribution(
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

  // The dependency tree must still be created
  d_ready = false;
}

// Reset the directional distributions
void StandardParticleDistribution::resetDirectionalDistributions()
{
  if( d_directional_coord_conversion_policy->getLocalDirectionalCoordinateSystemType() ==
      Utility::CARTESIAN_DIRECTIONAL_COORDINATE_SYSTEM )
  {
    std::shared_ptr<const Utility::UnivariateDistribution>
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
                 std::shared_ptr<const Utility::UnivariateDistribution>(
                                   new Utility::DeltaDistribution( 1.0 ) ) ) );
    d_dimension_distributions[SECONDARY_DIRECTIONAL_DIMENSION].reset(
     new IndependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION>(
                 std::shared_ptr<const Utility::UnivariateDistribution>(
                      new Utility::UniformDistribution(
                            0.0, 2*Utility::PhysicalConstants::pi, 1.0 ) ) ) );

    d_dimension_distributions[TERTIARY_DIRECTIONAL_DIMENSION].reset(
     new IndependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION>(
                 std::shared_ptr<const Utility::UnivariateDistribution>(
                      new Utility::UniformDistribution( -1.0, 1.0, 1.0 ) ) ) );
  }

  // The dependency tree must still be created
  d_ready = false;
}

// Return the dimension distribution type name
std::string StandardParticleDistribution::getDimensionDistributionTypeName(
                                    const PhaseSpaceDimension dimension ) const
{
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
    // Note: we really need to check that this distribution has a form of
    //       f(x) ~ x
    // \todo add more accurate check for a uniform spatial particle distribution in cylindrical coordinates
    if( !d_dimension_distributions.find( PRIMARY_SPATIAL_DIMENSION )->second->hasForm( Utility::POWER_DISTRIBUTION ) )
      return false;
  }
  else
  {
    // Note: we really need to check that this distribution has a form of
    //       f(x) ~ x^2
    // \todo add more accurate check for a uniform spatial particle distribution in spherical coordinates
    if( !d_dimension_distributions.find( PRIMARY_SPATIAL_DIMENSION )->second->hasForm( Utility::POWER_DISTRIBUTION ) )
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

// Initialize dimension counter map
/*! \details A counter for each dimension will be created and set to 0.
 */
void StandardParticleDistribution::initializeDimensionCounters(
                                            DimensionCounterMap& trials ) const
{
  trials[PRIMARY_SPATIAL_DIMENSION] = 0;
  trials[SECONDARY_SPATIAL_DIMENSION] = 0;
  trials[TERTIARY_SPATIAL_DIMENSION] = 0;

  trials[PRIMARY_DIRECTIONAL_DIMENSION] = 0;
  trials[SECONDARY_DIRECTIONAL_DIMENSION] = 0;
  trials[TERTIARY_DIRECTIONAL_DIMENSION] = 0;

  trials[ENERGY_DIMENSION] = 0;
  trials[TIME_DIMENSION] = 0;
  trials[WEIGHT_DIMENSION] = 0;
}

// Evaluate the distribution at the desired phase space point
/*! \details The dimension distribution dependency tree must be constructed
 * before the particle distribution can be evaluated. All dimensions except
 * for the weight dimension will be used.
 */
double StandardParticleDistribution::evaluate(
                                          const ParticleState& particle ) const
{
  // Make sure that the distribution is ready
  testPrecondition( d_ready );

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
    if( dimension_dist_it->second->getDimension() != WEIGHT_DIMENSION )
    {
      distribution_value *=
        dimension_dist_it->second->evaluateWithoutCascade( phase_space_point );
    }

    ++dimension_dist_it;
  }

  return distribution_value;
}

// Sample a particle state from the distribution
/*! \details The dimension distribution dependency tree must be constructed
 * before the particle distribution can be evaluated.
 */
void StandardParticleDistribution::sample( ParticleState& particle ) const
{
  // Make sure that the distribution is ready
  testPrecondition( d_ready );

  // Create the dimension sampling functor
  DimensionSamplingFunction dimension_sample_functor =
    std::bind<void>( &PhaseSpaceDimensionDistribution::sampleWithCascade,
                     std::placeholders::_1,
                     std::placeholders::_2 );

  this->sampleImpl( dimension_sample_functor, particle );
}

// Sample a particle state from the dist. and record the number of trials
/*! \details The dimension distribution dependency tree must be constructed
 * before the particle distribution can be evaluated.
 */
void StandardParticleDistribution::sampleAndRecordTrials(
                                       ParticleState& particle,
                                       DimensionCounterMap& trials ) const
{
  // Make sure that the distribution is ready
  testPrecondition( d_ready );

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
/*! \details The dimension distribution dependency tree must be constructed
 * before the particle distribution can be evaluated.
 */
void StandardParticleDistribution::sampleWithDimensionValue(
                                           ParticleState& particle,
                                           const PhaseSpaceDimension dimension,
                                           const double dimension_value ) const
{
  // Make sure that the distribution is ready
  testPrecondition( d_ready );

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
/*! \details The dimension distribution dependency tree must be constructed
 * before the particle distribution can be evaluated.
 */
void StandardParticleDistribution::sampleWithDimensionValueAndRecordTrials(
                                           ParticleState& particle,
                                           DimensionCounterMap& trials,
                                           const PhaseSpaceDimension dimension,
                                           const double dimension_value ) const
{
  // Make sure that the distribution is ready
  testPrecondition( d_ready );

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

EXPLICIT_CLASS_SAVE_LOAD_INST( StandardParticleDistribution );

} // end MonteCarlo namespace

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::StandardParticleDistribution );

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardParticleDistribution.cpp
//---------------------------------------------------------------------------//
