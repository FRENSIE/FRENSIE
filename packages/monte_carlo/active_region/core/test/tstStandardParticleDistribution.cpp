//---------------------------------------------------------------------------//
//!
//! \file   tstStandardParticleDistribution.cpp
//! \author Alex Robinson
//! \brief  Standard particle distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_StandardParticleDistribution.hpp"
#include "MonteCarlo_IndependentPhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_DependentPhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Utility_BasicCartesianCoordinateConversionPolicy.hpp"
#include "Utility_BasicSphericalCoordinateConversionPolicy.hpp"
#include "Utility_BasicCylindricalSpatialCoordinateConversionPolicy.hpp"
#include "Utility_HistogramFullyTabularBasicBivariateDistribution.hpp"
#include "Utility_HistogramPartiallyTabularBasicBivariateDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_DeltaDistribution.hpp"
#include "Utility_PowerDistribution.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_ExponentialDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

using namespace MonteCarlo;

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Testing Functions
//---------------------------------------------------------------------------//
void initializeCartesianSpatialDimensionDists(
         std::shared_ptr<StandardParticleDistribution>& particle_distribution )
{
  std::shared_ptr<const Utility::UnivariateDistribution> raw_uniform_dist_a(
                          new Utility::UniformDistribution( -1.0, 1.0, 0.5 ) );

  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    x_dimension_dist( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_uniform_dist_a ) );
  particle_distribution->setDimensionDistribution( x_dimension_dist );

  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    y_dimension_dist( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_uniform_dist_a ) );
  particle_distribution->setDimensionDistribution( y_dimension_dist );

  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    z_dimension_dist( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_uniform_dist_a ) );
  particle_distribution->setDimensionDistribution( z_dimension_dist );
}

void initializeCylindricalSpatialDimensionDists(
         std::shared_ptr<StandardParticleDistribution>& particle_distribution )
{
  std::shared_ptr<const Utility::UnivariateDistribution> raw_power_dist(
                          new Utility::PowerDistribution<1>( 0.5, 0.0, 1.0 ) );

  std::shared_ptr<const Utility::UnivariateDistribution> raw_uniform_dist_a(
          new Utility::UniformDistribution( 0.0, 2*Utility::PhysicalConstants::pi, 0.1 ) );

  std::shared_ptr<const Utility::UnivariateDistribution> raw_uniform_dist_b(
                          new Utility::UniformDistribution( -1.0, 1.0, 2.0 ) );

  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    r_dimension_dist( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_power_dist ) );
  particle_distribution->setDimensionDistribution( r_dimension_dist );

  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    theta_dimension_dist( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_uniform_dist_a ) );
  particle_distribution->setDimensionDistribution( theta_dimension_dist );

  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    z_dimension_dist( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_uniform_dist_b ) );
  particle_distribution->setDimensionDistribution( z_dimension_dist );
}

void initializeSphericalSpatialDimensionDists(
         std::shared_ptr<StandardParticleDistribution>& particle_distribution )
{
  std::shared_ptr<const Utility::UnivariateDistribution> raw_power_dist(
                          new Utility::PowerDistribution<2>( 0.5, 0.0, 1.0 ) );

  std::shared_ptr<const Utility::UnivariateDistribution> raw_uniform_dist_a(
          new Utility::UniformDistribution( 0.0, 2*Utility::PhysicalConstants::pi, 0.1 ) );

  std::shared_ptr<const Utility::UnivariateDistribution> raw_uniform_dist_b(
                          new Utility::UniformDistribution( -1.0, 1.0, 2.0 ) );

  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    r_dimension_dist( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_power_dist ) );
  particle_distribution->setDimensionDistribution( r_dimension_dist );

  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    theta_dimension_dist( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_uniform_dist_a ) );
  particle_distribution->setDimensionDistribution( theta_dimension_dist );

  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    mu_dimension_dist( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_uniform_dist_b ) );
  particle_distribution->setDimensionDistribution( mu_dimension_dist );
}

void initializeCartesianDirectionalDimensionDists(
         std::shared_ptr<StandardParticleDistribution>& particle_distribution )
{
  std::shared_ptr<const Utility::UnivariateDistribution> raw_uniform_dist_a(
                          new Utility::UniformDistribution( -1.0, 1.0, 0.5 ) );

  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    u_dimension_dist(new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION>( raw_uniform_dist_a ) );
  particle_distribution->setDimensionDistribution( u_dimension_dist );

  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    v_dimension_dist(new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION>( raw_uniform_dist_a ) );
  particle_distribution->setDimensionDistribution( v_dimension_dist );

  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    w_dimension_dist(new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION>( raw_uniform_dist_a ) );
  particle_distribution->setDimensionDistribution( w_dimension_dist );
}

template<MonteCarlo::PhaseSpaceDimension parent_energy_dimension>
void initializeMiscDimensionDists(
          std::shared_ptr<StandardParticleDistribution>& particle_distribution,
          const bool mono_energy = false,
          const bool mono_time = false )
{
  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    time_dimension_dist;

  if( mono_time )
  {
    std::shared_ptr<const Utility::UnivariateDistribution> raw_delta_dist(
                                       new Utility::DeltaDistribution( 1.0 ) );

    time_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION>( raw_delta_dist ) );
  }
  else
  {
    std::shared_ptr<const Utility::UnivariateDistribution> raw_uniform_dist(
                           new Utility::UniformDistribution( 0.0, 1.0, 1.0 ) );

    time_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION>( raw_uniform_dist ) );
  }

  particle_distribution->setDimensionDistribution( time_dimension_dist );

  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    energy_dimension_dist;

  if( mono_energy )
  {
    std::shared_ptr<const Utility::UnivariateDistribution> raw_delta_dist(
                                      new Utility::DeltaDistribution( 10.0 ) );

    energy_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION>( raw_delta_dist ) );
  }
  else
  {
    // Create the fully tabular distribution
    std::vector<double> primary_grid( {-1.0, 0.0, 1.0} );
    std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
      secondary_dists( 3 );

    // Create the secondary distribution in the first bin
    secondary_dists[0].reset( new Utility::UniformDistribution( 0.0, 10.0, 0.5 ) );

    // Create the secondary distribution in the second bin
    secondary_dists[1].reset( new Utility::UniformDistribution( 0.0, 20.0, 0.25 ) );

    // Create the secondary distribution in the third bin
    secondary_dists[2] = secondary_dists[1];

    std::shared_ptr<Utility::HistogramFullyTabularBasicBivariateDistribution>
      raw_dependent_distribution( new Utility::HistogramFullyTabularBasicBivariateDistribution( primary_grid, secondary_dists ) );

    raw_dependent_distribution->limitToPrimaryIndepLimits();

    energy_dimension_dist.reset( new MonteCarlo::DependentPhaseSpaceDimensionDistribution<parent_energy_dimension,MonteCarlo::ENERGY_DIMENSION>( raw_dependent_distribution ) );
  }
  
  particle_distribution->setDimensionDistribution( energy_dimension_dist );

  std::shared_ptr<const Utility::UnivariateDistribution> raw_delta_dist(
                                       new Utility::DeltaDistribution( 0.5 ) );

  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    weight_dimension_dist( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION>( raw_delta_dist ) );
  
  particle_distribution->setDimensionDistribution( weight_dimension_dist );
}

std::shared_ptr<const ParticleDistribution>
createCartesianSpatialCartesianDirectionalDist()
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
    spatial_coord_conversion_policy( new Utility::BasicCartesianCoordinateConversionPolicy );

  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
    directional_coord_conversion_policy( new Utility::BasicCartesianCoordinateConversionPolicy );

  std::shared_ptr<MonteCarlo::StandardParticleDistribution>
    particle_distribution( new MonteCarlo::StandardParticleDistribution(
                                       "test dist",
                                       spatial_coord_conversion_policy,
                                       directional_coord_conversion_policy ) );

  // Create the dimension distributions
  initializeCartesianSpatialDimensionDists( particle_distribution );
  initializeCartesianDirectionalDimensionDists( particle_distribution );
  initializeMiscDimensionDists<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( particle_distribution );

  particle_distribution->constructDimensionDistributionDependencyTree();

  return particle_distribution;
}

std::shared_ptr<const ParticleDistribution>
createCartesianSpatialSphericalDirectionalDist( const bool mono_energy = false,
                                                const bool mono_time = false )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
    spatial_coord_conversion_policy( new Utility::BasicCartesianCoordinateConversionPolicy );

  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
    directional_coord_conversion_policy( new Utility::BasicSphericalCoordinateConversionPolicy );

  std::shared_ptr<MonteCarlo::StandardParticleDistribution>
    particle_distribution( new MonteCarlo::StandardParticleDistribution(
                                       "test dist",
                                       spatial_coord_conversion_policy,
                                       directional_coord_conversion_policy ) );

  // Create the dimension distributions
  initializeCartesianSpatialDimensionDists( particle_distribution );
  initializeMiscDimensionDists<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( particle_distribution,
                                                                       mono_energy,
                                                                       mono_time );

  particle_distribution->constructDimensionDistributionDependencyTree();

  return particle_distribution;
}

std::shared_ptr<const ParticleDistribution>
createCylindricalSpatialCartesianDirectionalDist()
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
    spatial_coord_conversion_policy( new Utility::BasicCylindricalSpatialCoordinateConversionPolicy );

  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
    directional_coord_conversion_policy( new Utility::BasicCartesianCoordinateConversionPolicy );

  std::shared_ptr<MonteCarlo::StandardParticleDistribution>
    particle_distribution( new MonteCarlo::StandardParticleDistribution(
                                       "test dist",
                                       spatial_coord_conversion_policy,
                                       directional_coord_conversion_policy ) );

  // Create the dimension distributions
  initializeCylindricalSpatialDimensionDists( particle_distribution );
  initializeCartesianDirectionalDimensionDists( particle_distribution );
  initializeMiscDimensionDists<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( particle_distribution );

  particle_distribution->constructDimensionDistributionDependencyTree();

  return particle_distribution;
}

std::shared_ptr<const ParticleDistribution>
createCylindricalSpatialSphericalDirectionalDist()
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
    spatial_coord_conversion_policy( new Utility::BasicCylindricalSpatialCoordinateConversionPolicy );

  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
    directional_coord_conversion_policy( new Utility::BasicSphericalCoordinateConversionPolicy );

  std::shared_ptr<MonteCarlo::StandardParticleDistribution>
    particle_distribution( new MonteCarlo::StandardParticleDistribution(
                                       "test dist",
                                       spatial_coord_conversion_policy,
                                       directional_coord_conversion_policy ) );

  // Create the dimension distributions
  initializeCylindricalSpatialDimensionDists( particle_distribution );
  initializeMiscDimensionDists<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( particle_distribution );

  particle_distribution->constructDimensionDistributionDependencyTree();

  return particle_distribution;
}

std::shared_ptr<const ParticleDistribution>
createSphericalSpatialCartesianDirectionalDist()
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
    spatial_coord_conversion_policy( new Utility::BasicSphericalCoordinateConversionPolicy );

  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
    directional_coord_conversion_policy( new Utility::BasicCartesianCoordinateConversionPolicy );

  std::shared_ptr<MonteCarlo::StandardParticleDistribution>
    particle_distribution( new MonteCarlo::StandardParticleDistribution(
                                       "test dist",
                                       spatial_coord_conversion_policy,
                                       directional_coord_conversion_policy ) );

  // Create the dimension distributions
  initializeSphericalSpatialDimensionDists( particle_distribution );
  initializeCartesianDirectionalDimensionDists( particle_distribution );
  initializeMiscDimensionDists<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( particle_distribution );

  particle_distribution->constructDimensionDistributionDependencyTree();

  return particle_distribution;
}

std::shared_ptr<const ParticleDistribution>
createSphericalSpatialSphericalDirectionalDist()
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
    spatial_coord_conversion_policy( new Utility::BasicSphericalCoordinateConversionPolicy );

  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
    directional_coord_conversion_policy( new Utility::BasicSphericalCoordinateConversionPolicy );

  std::shared_ptr<MonteCarlo::StandardParticleDistribution>
    particle_distribution( new MonteCarlo::StandardParticleDistribution(
                                       "test dist",
                                       spatial_coord_conversion_policy,
                                       directional_coord_conversion_policy ) );

  // Create the dimension distributions
  initializeSphericalSpatialDimensionDists( particle_distribution );
  initializeMiscDimensionDists<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( particle_distribution );

  particle_distribution->constructDimensionDistributionDependencyTree();

  return particle_distribution;
}

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the distribution name can be returned
FRENSIE_UNIT_TEST( StandardParticleDistribution, getName )
{
  MonteCarlo::StandardParticleDistribution
    particle_distribution( "test dist" );

  FRENSIE_CHECK_EQUAL( particle_distribution.getName(), "test dist" );
}

//---------------------------------------------------------------------------//
// Check that a dimension's distribution type name can be returned
FRENSIE_UNIT_TEST( StandardParticleDistribution,
                   getDimensionDistributionTypeName )
{
  MonteCarlo::StandardParticleDistribution
    particle_distribution( "test dist" );

  std::shared_ptr<const Utility::UnivariateDistribution> raw_dist(
                           new Utility::UniformDistribution( 0.5, 1.5, 0.5 ) );

  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    energy_dimension_dist(new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION>( raw_dist ) );

  particle_distribution.setDimensionDistribution( energy_dimension_dist );

  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::ENERGY_DIMENSION ),
                       "Uniform Distribution" );
}

//---------------------------------------------------------------------------//
// Check if the distribution is spatially uniform
FRENSIE_UNIT_TEST( StandardParticleDistribution,
                   isSpatiallyUniform_cartesian )
{
  MonteCarlo::StandardParticleDistribution
    particle_distribution( "test dist" );

  std::shared_ptr<const Utility::UnivariateDistribution> raw_uniform_dist(
                           new Utility::UniformDistribution( 0.5, 1.5, 0.5 ) );

  std::shared_ptr<const Utility::UnivariateDistribution> raw_delta_dist(
                                       new Utility::DeltaDistribution( 1.0 ) );

  // Create a uniform Cartesian spatial distribution
  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    x_dimension_dist(new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );

  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    y_dimension_dist(new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );

  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    z_dimension_dist(new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );

  particle_distribution.setDimensionDistribution( x_dimension_dist );
  particle_distribution.setDimensionDistribution( y_dimension_dist );
  particle_distribution.setDimensionDistribution( z_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  FRENSIE_CHECK( particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform Cartesian spatial distribution
  x_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_delta_dist ) );
  y_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );
  z_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );

  particle_distribution.setDimensionDistribution( x_dimension_dist );
  particle_distribution.setDimensionDistribution( y_dimension_dist );
  particle_distribution.setDimensionDistribution( z_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  FRENSIE_CHECK( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform Cartesian spatial distribution
  x_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );
  y_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_delta_dist ) );
  z_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );

  particle_distribution.setDimensionDistribution( x_dimension_dist );
  particle_distribution.setDimensionDistribution( y_dimension_dist );
  particle_distribution.setDimensionDistribution( z_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  FRENSIE_CHECK( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform Cartesian spatial distribution
  x_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );
  y_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );
  z_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_delta_dist ) );

  particle_distribution.setDimensionDistribution( x_dimension_dist );
  particle_distribution.setDimensionDistribution( y_dimension_dist );
  particle_distribution.setDimensionDistribution( z_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  FRENSIE_CHECK( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform Cartesian spatial distribution
  x_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_delta_dist ) );
  y_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_delta_dist ) );
  z_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );

  particle_distribution.setDimensionDistribution( x_dimension_dist );
  particle_distribution.setDimensionDistribution( y_dimension_dist );
  particle_distribution.setDimensionDistribution( z_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  FRENSIE_CHECK( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform Cartesian spatial distribution
  x_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_delta_dist ) );
  y_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );
  z_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_delta_dist ) );

  particle_distribution.setDimensionDistribution( x_dimension_dist );
  particle_distribution.setDimensionDistribution( y_dimension_dist );
  particle_distribution.setDimensionDistribution( z_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  FRENSIE_CHECK( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform Cartesian spatial distribution
  x_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );
  y_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_delta_dist ) );
  z_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_delta_dist ) );

  particle_distribution.setDimensionDistribution( x_dimension_dist );
  particle_distribution.setDimensionDistribution( y_dimension_dist );
  particle_distribution.setDimensionDistribution( z_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  FRENSIE_CHECK( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform Cartesian spatial distribution
  x_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_delta_dist ) );
  y_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_delta_dist ) );
  z_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_delta_dist ) );

  particle_distribution.setDimensionDistribution( x_dimension_dist );
  particle_distribution.setDimensionDistribution( y_dimension_dist );
  particle_distribution.setDimensionDistribution( z_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  FRENSIE_CHECK( !particle_distribution.isSpatiallyUniform() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is spatially uniform
FRENSIE_UNIT_TEST( StandardParticleDistribution,
                   isSpatiallyUniform_cylindrical )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
    spatial_coord_conversion_policy( new Utility::BasicCylindricalSpatialCoordinateConversionPolicy );

  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
    directional_coord_conversion_policy( new Utility::BasicSphericalCoordinateConversionPolicy );

  MonteCarlo::StandardParticleDistribution
    particle_distribution( "test dist",
                           spatial_coord_conversion_policy,
                           directional_coord_conversion_policy );

  std::shared_ptr<const Utility::UnivariateDistribution> raw_power_dist(
                          new Utility::PowerDistribution<1>( 1.0, 0.0, 1.0 ) );

  std::shared_ptr<const Utility::UnivariateDistribution> raw_uniform_dist(
     new Utility::UniformDistribution( 0.0, 2*Utility::PhysicalConstants::pi, 1.0 ) );

  // Create a uniform cylindrical spatial distribution
  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    r_dimension_dist(new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_power_dist ) );

  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    theta_dimension_dist(new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );

  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    z_dimension_dist(new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( z_dimension_dist );

  FRENSIE_CHECK( particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform cylindrical spatial distribution
  particle_distribution.reset();

  r_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );
  theta_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );
  z_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( z_dimension_dist );

  FRENSIE_CHECK( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform cylindrical spatial distribution
  particle_distribution.reset();

  r_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_power_dist ) );
  theta_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_power_dist ) );
  z_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( z_dimension_dist );

  FRENSIE_CHECK( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform cylindrical spatial distribution
  particle_distribution.reset();

  r_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_power_dist ) );
  theta_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );
  z_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_power_dist ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( z_dimension_dist );

  FRENSIE_CHECK( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform cylindrical spatial distribution
  particle_distribution.reset();

  r_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );
  theta_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_power_dist ) );
  z_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( z_dimension_dist );

  FRENSIE_CHECK( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform cylindrical spatial distribution
  particle_distribution.reset();

  r_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );
  theta_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );
  z_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_power_dist ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( z_dimension_dist );

  FRENSIE_CHECK( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform cylindrical spatial distribution
  particle_distribution.reset();

  r_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );
  theta_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_power_dist ) );
  z_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_power_dist ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( z_dimension_dist );

  FRENSIE_CHECK( !particle_distribution.isSpatiallyUniform() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is spatially uniform
FRENSIE_UNIT_TEST( StandardParticleDistribution,
                   isSpatiallyUniform_spherical )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
    spatial_coord_conversion_policy( new Utility::BasicSphericalCoordinateConversionPolicy );

  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
    directional_coord_conversion_policy( new Utility::BasicSphericalCoordinateConversionPolicy );

  MonteCarlo::StandardParticleDistribution
    particle_distribution( "test dist",
                           spatial_coord_conversion_policy,
                           directional_coord_conversion_policy );

  std::shared_ptr<const Utility::UnivariateDistribution> raw_power_dist(
                          new Utility::PowerDistribution<2>( 1.0, 0.0, 1.0 ) );

  std::shared_ptr<const Utility::UnivariateDistribution> raw_uniform_dist_a(
      new Utility::UniformDistribution( 0.0, 2*Utility::PhysicalConstants::pi, 1.0 ) );

  std::shared_ptr<const Utility::UnivariateDistribution> raw_uniform_dist_b(
                          new Utility::UniformDistribution( -1.0, 1.0, 1.0 ) );

  // Create a uniform spherical spatial distribution
  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    r_dimension_dist(new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_power_dist ) );

  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    theta_dimension_dist(new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_uniform_dist_a ) );

  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    mu_dimension_dist(new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_uniform_dist_b ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( mu_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  FRENSIE_CHECK( particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform spherical spatial distribution
  r_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_uniform_dist_a ) );
  theta_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_uniform_dist_a ) );
  mu_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_uniform_dist_b ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( mu_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  FRENSIE_CHECK( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform spherical spatial distribution
  r_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_power_dist ) );
  theta_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_power_dist ) );
  mu_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_uniform_dist_b ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( mu_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  FRENSIE_CHECK( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform spherical spatial distribution
  r_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_power_dist ) );
  theta_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_uniform_dist_a ) );
  mu_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_power_dist ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( mu_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  FRENSIE_CHECK( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform spherical spatial distribution
  r_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_uniform_dist_a ) );
  theta_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_power_dist ) );
  mu_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_uniform_dist_b ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( mu_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  FRENSIE_CHECK( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform spherical spatial distribution
  r_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_uniform_dist_a ) );
  theta_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_uniform_dist_a ) );
  mu_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_power_dist ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( mu_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  FRENSIE_CHECK( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform spherical spatial distribution
  r_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_power_dist ) );
  theta_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_power_dist ) );
  mu_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_power_dist ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( mu_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  FRENSIE_CHECK( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform spherical spatial distribution
  r_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_uniform_dist_a ) );
  theta_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_power_dist ) );
  mu_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_power_dist ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( mu_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  FRENSIE_CHECK( !particle_distribution.isSpatiallyUniform() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is directionally uniform (isotropic)
FRENSIE_UNIT_TEST( StandardParticleDistribution,
                   isDirectionallyUniform_cartesian )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
    spatial_coord_conversion_policy( new Utility::BasicCartesianCoordinateConversionPolicy );

  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
    directional_coord_conversion_policy( new Utility::BasicCartesianCoordinateConversionPolicy );

  MonteCarlo::StandardParticleDistribution
    particle_distribution( "test dist",
                           spatial_coord_conversion_policy,
                           directional_coord_conversion_policy );

  std::shared_ptr<const Utility::UnivariateDistribution> raw_uniform_dist(
                          new Utility::UniformDistribution( -1.0, 1.0, 1.0 ) );

  std::shared_ptr<const Utility::UnivariateDistribution> raw_delta_dist(
                                       new Utility::DeltaDistribution( 1.0 ) );

  // Create a non-uniform Cartesian directional distribution
  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    u_dimension_dist(new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION>( raw_uniform_dist ) );

  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    v_dimension_dist(new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION>( raw_uniform_dist ) );

  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    w_dimension_dist(new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION>( raw_uniform_dist ) );

  particle_distribution.setDimensionDistribution( u_dimension_dist );
  particle_distribution.setDimensionDistribution( v_dimension_dist );
  particle_distribution.setDimensionDistribution( w_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  FRENSIE_CHECK( !particle_distribution.isDirectionallyUniform() );

  // Create a non-uniform Cartesian directional distribution
  u_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION>( raw_delta_dist ) );
  v_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION>( raw_uniform_dist ) );
  w_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION>( raw_uniform_dist ) );

  particle_distribution.setDimensionDistribution( u_dimension_dist );
  particle_distribution.setDimensionDistribution( v_dimension_dist );
  particle_distribution.setDimensionDistribution( w_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  FRENSIE_CHECK( !particle_distribution.isDirectionallyUniform() );

  // Create a non-uniform Cartesian directional distribution
  u_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION>( raw_uniform_dist ) );
  v_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION>( raw_delta_dist ) );
  w_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION>( raw_uniform_dist ) );

  particle_distribution.setDimensionDistribution( u_dimension_dist );
  particle_distribution.setDimensionDistribution( v_dimension_dist );
  particle_distribution.setDimensionDistribution( w_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  FRENSIE_CHECK( !particle_distribution.isDirectionallyUniform() );

  // Create a non-uniform Cartesian directional distribution
  u_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION>( raw_uniform_dist ) );
  v_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION>( raw_uniform_dist ) );
  w_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION>( raw_delta_dist ) );

  particle_distribution.setDimensionDistribution( u_dimension_dist );
  particle_distribution.setDimensionDistribution( v_dimension_dist );
  particle_distribution.setDimensionDistribution( w_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  FRENSIE_CHECK( !particle_distribution.isDirectionallyUniform() );

  // Create a non-uniform Cartesian directional distribution
  u_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION>( raw_delta_dist ) );
  v_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION>( raw_delta_dist ) );
  w_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION>( raw_delta_dist ) );

  particle_distribution.setDimensionDistribution( u_dimension_dist );
  particle_distribution.setDimensionDistribution( v_dimension_dist );
  particle_distribution.setDimensionDistribution( w_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  FRENSIE_CHECK( !particle_distribution.isDirectionallyUniform() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is directionally uniform (isotropic)
FRENSIE_UNIT_TEST( StandardParticleDistribution,
                   isDirectionallyUniform_spherical )
{
  MonteCarlo::StandardParticleDistribution
    particle_distribution( "test dist" );

  std::shared_ptr<const Utility::UnivariateDistribution> raw_delta_dist(
                                       new Utility::DeltaDistribution( 1.0 ) );

  std::shared_ptr<const Utility::UnivariateDistribution> raw_uniform_dist_a(
       new Utility::UniformDistribution( 0.0, 2*Utility::PhysicalConstants::pi, 1.0 ) );

  std::shared_ptr<const Utility::UnivariateDistribution> raw_uniform_dist_b(
                          new Utility::UniformDistribution( -1.0, 1.0, 1.0 ) );

  // Create a non-uniform spherical directional distribution
  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    r_dimension_dist(new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION>( raw_delta_dist ) );

  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    theta_dimension_dist(new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION>( raw_uniform_dist_a ) );

  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    mu_dimension_dist(new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION>( raw_uniform_dist_b ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( mu_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  FRENSIE_CHECK( particle_distribution.isDirectionallyUniform() );

  // Create a uniform spherical directional distribution
  r_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION>( raw_uniform_dist_a ) );
  theta_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION>( raw_uniform_dist_a ) );
  mu_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION>( raw_uniform_dist_b ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( mu_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  FRENSIE_CHECK( particle_distribution.isDirectionallyUniform() );

  // Create a non-uniform spherical directional distribution
  r_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION>( raw_delta_dist ) );
  theta_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION>( raw_delta_dist ) );
  mu_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION>( raw_uniform_dist_b ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( mu_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  FRENSIE_CHECK( !particle_distribution.isDirectionallyUniform() );

  // Create a non-uniform spherical directional distribution
  r_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION>( raw_delta_dist ) );
  theta_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION>( raw_uniform_dist_a ) );
  mu_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION>( raw_delta_dist ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( mu_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  FRENSIE_CHECK( !particle_distribution.isDirectionallyUniform() );

  // Create a non-uniform spherical directional distribution
  r_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION>( raw_delta_dist ) );
  theta_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION>( raw_delta_dist ) );
  mu_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION>( raw_delta_dist ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( mu_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  FRENSIE_CHECK( !particle_distribution.isDirectionallyUniform() );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST( StandardParticleDistribution,
                   evaluate_cartesian_spatial_cartesian_directional )
{
  std::shared_ptr<const ParticleDistribution> particle_distribution =
    createCartesianSpatialCartesianDirectionalDist();

  MonteCarlo::PhotonState photon( 0 );
  photon.setPosition( -1.1, -0.5, -0.5 );
  photon.setDirection( 1.0, 0.0, 0.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  FRENSIE_CHECK_EQUAL( particle_distribution->evaluate( photon ), 0.0 );

  photon.setPosition( -1.0, -0.5, -0.5 );
  photon.setDirection( 0.0, 1.0, 0.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  FRENSIE_CHECK_EQUAL( particle_distribution->evaluate( photon ), 0.0078125 );

  photon.setPosition( -0.5, -0.5, -0.5 );
  photon.setDirection( 0.0, 0.0, 1.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  FRENSIE_CHECK_EQUAL( particle_distribution->evaluate( photon ), 0.0078125 );

  photon.setPosition( 0.0, -0.5, -0.5 );
  photon.setDirection( -1.0, 0.0, 0.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  FRENSIE_CHECK_EQUAL( particle_distribution->evaluate( photon ), 0.00390625 );

  photon.setPosition( 0.5, -0.5, -0.5 );
  photon.setDirection( 0.0, -1.0, 0.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  FRENSIE_CHECK_EQUAL( particle_distribution->evaluate( photon ), 0.00390625 );

  photon.setPosition( 1.0, -0.5, -0.5 );
  photon.setDirection( 0.0, 0.0, -1.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  FRENSIE_CHECK_EQUAL( particle_distribution->evaluate( photon ), 0.00390625 );

  photon.setPosition( 1.1, -0.5, -0.5 );
  photon.setDirection( 1.0/sqrt(3.0), 1.0/sqrt(3.0), 1.0/sqrt(3.0) );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  FRENSIE_CHECK_EQUAL( particle_distribution->evaluate( photon ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST( StandardParticleDistribution,
                   evaluate_cartesian_spatial_spherical_directional )
{
  std::shared_ptr<const ParticleDistribution> particle_distribution =
    createCartesianSpatialSphericalDirectionalDist();

  MonteCarlo::PhotonState photon( 0 );
  photon.setPosition( -1.1, -0.5, -0.5 );
  photon.setDirection( 1.0, 0.0, 0.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  FRENSIE_CHECK_EQUAL( particle_distribution->evaluate( photon ), 0.0 );

  photon.setPosition( -1.0, -0.5, -0.5 );
  photon.setDirection( 0.0, 1.0, 0.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  FRENSIE_CHECK_EQUAL( particle_distribution->evaluate( photon ), 0.0625 );

  photon.setPosition( -0.5, -0.5, -0.5 );
  photon.setDirection( 0.0, 0.0, 1.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  FRENSIE_CHECK_EQUAL( particle_distribution->evaluate( photon ), 0.0625 );

  photon.setPosition( 0.0, -0.5, -0.5 );
  photon.setDirection( -1.0, 0.0, 0.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  FRENSIE_CHECK_EQUAL( particle_distribution->evaluate( photon ), 0.03125 );

  photon.setPosition( 0.5, -0.5, -0.5 );
  photon.setDirection( 0.0, -1.0, 0.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  FRENSIE_CHECK_EQUAL( particle_distribution->evaluate( photon ), 0.03125 );

  photon.setPosition( 1.0, -0.5, -0.5 );
  photon.setDirection( 0.0, 0.0, -1.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  FRENSIE_CHECK_EQUAL( particle_distribution->evaluate( photon ), 0.03125 );

  photon.setPosition( 1.1, -0.5, -0.5 );
  photon.setDirection( 1.0/sqrt(3.0), 1.0/sqrt(3.0), 1.0/sqrt(3.0) );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  FRENSIE_CHECK_EQUAL( particle_distribution->evaluate( photon ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST( StandardParticleDistribution,
                   evaluate_cylindrical_spatial_cartesian_directional )
{
  std::shared_ptr<const ParticleDistribution> particle_distribution =
    createCylindricalSpatialCartesianDirectionalDist();

  MonteCarlo::PhotonState photon( 0 );
  photon.setPosition( 0.0, 0.0, -1.1 );
  photon.setDirection( 1.0, 0.0, 0.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  FRENSIE_CHECK_EQUAL( particle_distribution->evaluate( photon ), 0.0 );

  photon.setPosition( 0.0, 0.0, -1.0 );
  photon.setDirection( 1.0, 0.0, 0.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  FRENSIE_CHECK_EQUAL( particle_distribution->evaluate( photon ), 0.0 );

  photon.setPosition( 0.1, 0.1, -1.0 );
  photon.setDirection( 1.0, 0.0, 0.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( particle_distribution->evaluate( photon ),
                          0.0008838834764831846,
                          1e-15 );

  photon.setPosition( 0.1, -0.1, 0.0 );
  photon.setDirection( 0.0, 1.0, 0.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( particle_distribution->evaluate( photon ),
                          0.0004419417382415923,
                          1e-15 );

  photon.setPosition( -0.1, 0.1, 1.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( particle_distribution->evaluate( photon ),
                          0.0004419417382415923,
                          1e-15 );

  photon.setPosition( 0.1, 0.1, 1.1 );
  photon.setDirection( 0.0, 0.0, 1.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  FRENSIE_CHECK_EQUAL( particle_distribution->evaluate( photon ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST( StandardParticleDistribution,
                   evaluate_cylindrical_spatial_spherical_directional )
{
  std::shared_ptr<const ParticleDistribution> particle_distribution =
    createCylindricalSpatialSphericalDirectionalDist();

  MonteCarlo::PhotonState photon( 0 );
  photon.setPosition( 0.0, 0.0, -1.1 );
  photon.setDirection( 1.0, 0.0, 0.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  FRENSIE_CHECK_EQUAL( particle_distribution->evaluate( photon ), 0.0 );

  photon.setPosition( 0.0, 0.0, -1.0 );
  photon.setDirection( 1.0, 0.0, 0.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  FRENSIE_CHECK_EQUAL( particle_distribution->evaluate( photon ), 0.0 );

  photon.setPosition( 0.1, 0.1, -1.0 );
  photon.setDirection( 1.0, 0.0, 0.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( particle_distribution->evaluate( photon ),
                          0.007071067811865477,
                          1e-15 );

  photon.setPosition( 0.1, -0.1, 0.0 );
  photon.setDirection( 0.0, 1.0, 0.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( particle_distribution->evaluate( photon ),
                          0.0035355339059327385,
                          1e-15 );

  photon.setPosition( -0.1, 0.1, 1.0 );
  photon.setDirection( 1.0/sqrt(3.0), 1.0/sqrt(3.0), 1.0/sqrt(3.0) );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( particle_distribution->evaluate( photon ),
                          0.0035355339059327385,
                          1e-15 );

  photon.setPosition( 0.1, 0.1, 1.1 );
  photon.setDirection( 0.0, 0.0, 1.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  FRENSIE_CHECK_EQUAL( particle_distribution->evaluate( photon ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST( StandardParticleDistribution,
                   evaluate_spherical_spatial_cartesian_directional )
{
  std::shared_ptr<const ParticleDistribution> particle_distribution =
    createSphericalSpatialCartesianDirectionalDist();

  MonteCarlo::PhotonState photon( 0 );
  photon.setPosition( 0.0, 0.0, -1.1 );
  photon.setDirection( 1.0, 0.0, 0.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  FRENSIE_CHECK_EQUAL( particle_distribution->evaluate( photon ), 0.0 );

  photon.setPosition( 0.0, 0.0, -1.0 );
  photon.setDirection( 1.0, 0.0, 0.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  FRENSIE_CHECK_EQUAL( particle_distribution->evaluate( photon ), 0.00625 );

  photon.setPosition( -1.0/sqrt(3.0), -1.0/sqrt(3.0), -1.0/sqrt(3.0) );
  photon.setDirection( -1.0, 0.0, 0.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( particle_distribution->evaluate( photon ),
                          0.00625,
                          1e-15 );

  photon.setPosition( 0.0, 0.0, 0.0 );
  photon.setDirection( 1.0, 0.0, 0.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  FRENSIE_CHECK_EQUAL( particle_distribution->evaluate( photon ), 0.0 );

  photon.setPosition( 0.1, 0.1, 0.0 );
  photon.setDirection( 1.0, 0.0, 0.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( particle_distribution->evaluate( photon ),
                          6.25e-5,
                          1e-15 );

  photon.setPosition( 1.0/sqrt(3.0), 1.0/sqrt(3.0), 1.0/sqrt(3.0) );
  photon.setDirection( 0.0, 1.0, 0.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( particle_distribution->evaluate( photon ),
                          0.003125,
                          1e-15 );

  photon.setPosition( 0.0, 0.0, 1.0 );
  photon.setDirection( 1.0, 0.0, 0.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  FRENSIE_CHECK_EQUAL( particle_distribution->evaluate( photon ), 0.003125 );

  photon.setPosition( 0.0, 0.0, 1.1 );
  photon.setDirection( 1.0, 0.0, 0.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  FRENSIE_CHECK_EQUAL( particle_distribution->evaluate( photon ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST( StandardParticleDistribution,
                   evaluate_spherical_spatial_spherical_directional )
{
  std::shared_ptr<const ParticleDistribution> particle_distribution =
    createSphericalSpatialSphericalDirectionalDist();

  MonteCarlo::PhotonState photon( 0 );
  photon.setPosition( 0.0, 0.0, -1.1 );
  photon.setDirection( 1.0, 0.0, 0.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  FRENSIE_CHECK_EQUAL( particle_distribution->evaluate( photon ), 0.0 );

  photon.setPosition( 0.0, 0.0, -1.0 );
  photon.setDirection( 1.0, 0.0, 0.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  FRENSIE_CHECK_EQUAL( particle_distribution->evaluate( photon ), 0.05 );

  photon.setPosition( -1.0/sqrt(3.0), -1.0/sqrt(3.0), -1.0/sqrt(3.0) );
  photon.setDirection( -1.0, 0.0, 0.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( particle_distribution->evaluate( photon ),
                          0.05,
                          1e-15 );

  photon.setPosition( 0.0, 0.0, 0.0 );
  photon.setDirection( 1.0, 0.0, 0.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  FRENSIE_CHECK_EQUAL( particle_distribution->evaluate( photon ), 0.0 );

  photon.setPosition( 0.1, 0.1, 0.0 );
  photon.setDirection( 1.0, 0.0, 0.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( particle_distribution->evaluate( photon ),
                          5.0e-4,
                          1e-15 );

  photon.setPosition( 1.0/sqrt(3.0), 1.0/sqrt(3.0), 1.0/sqrt(3.0) );
  photon.setDirection( 0.0, 1.0, 0.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( particle_distribution->evaluate( photon ),
                          0.025,
                          1e-15 );

  photon.setPosition( 0.0, 0.0, 1.0 );
  photon.setDirection( 1.0, 0.0, 0.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  FRENSIE_CHECK_EQUAL( particle_distribution->evaluate( photon ), 0.025 );

  photon.setPosition( 0.0, 0.0, 1.1 );
  photon.setDirection( 1.0, 0.0, 0.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  FRENSIE_CHECK_EQUAL( particle_distribution->evaluate( photon ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the distrubtion can be sampled
FRENSIE_UNIT_TEST( StandardParticleDistribution,
                   sample_cartesian_spatial_cartesian_directional )
{
  std::shared_ptr<const ParticleDistribution> particle_distribution =
    createCartesianSpatialCartesianDirectionalDist();

  // Set the random number generator stream
  std::vector<double> fake_stream( 8 );
  fake_stream[0] = 0.0; // x
  fake_stream[1] = 0.5; // energy
  fake_stream[2] = 0.5; // y
  fake_stream[3] = 1.0-1e-15; // z
  fake_stream[4] = 0.5; // u
  fake_stream[5] = 0.5; // v
  fake_stream[6] = 1.0-1e-15; // w
  fake_stream[7] = 0.0; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::PhotonState photon( 0 );

  particle_distribution->sample( photon );

  FRENSIE_CHECK_EQUAL( photon.getXPosition(), -1.0 );
  FRENSIE_CHECK_EQUAL( photon.getYPosition(), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZPosition(), 1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getXDirection(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZDirection(), 1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getSourceEnergy(), 5.0 );
  FRENSIE_CHECK_EQUAL( photon.getEnergy(), 5.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceWeight(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getWeight(), 0.5 );

  // Set the random number generator stream
  fake_stream[0] = 0.5; // x
  fake_stream[1] = 0.5; // energy
  fake_stream[2] = 1.0-1e-15; // y
  fake_stream[3] = 0.5; // z
  fake_stream[4] = 0.5; // u
  fake_stream[5] = 0.0; // v
  fake_stream[6] = 0.5; // w
  fake_stream[7] = 0.5; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  particle_distribution->sample( photon );

  FRENSIE_CHECK_EQUAL( photon.getXPosition(), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getYPosition(), 1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getZPosition(), 0.0 );
  FRENSIE_CHECK_SMALL( photon.getXDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getYDirection(), -1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getZDirection(), 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getSourceEnergy(), 10.0 );
  FRENSIE_CHECK_EQUAL( photon.getEnergy(), 10.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceTime(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getTime(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getSourceWeight(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getWeight(), 0.5 );

  // Set the random number generator stream
  fake_stream[0] = 1.0-1e-15; // x
  fake_stream[1] = 1.0-1e-15; // energy
  fake_stream[2] = 0.0; // y
  fake_stream[3] = 0.0; // z
  fake_stream[4] = 1.0-1e-15; // u
  fake_stream[5] = 0.5; // v
  fake_stream[6] = 0.5; // w
  fake_stream[7] = 1.0-1e-15; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  particle_distribution->sample( photon );

  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getXPosition(), 1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getYPosition(), -1.0 );
  FRENSIE_CHECK_EQUAL( photon.getZPosition(), -1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getXDirection(), 1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getZDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getSourceEnergy(), 20.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getEnergy(), 20.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getSourceTime(), 1.0, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getTime(), 1.0, 1e-15 );
  FRENSIE_CHECK_EQUAL( photon.getSourceWeight(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getWeight(), 0.5 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distrubtion can be sampled
FRENSIE_UNIT_TEST( StandardParticleDistribution,
                   sample_cartesian_spatial_spherical_directional )
{
  std::shared_ptr<const ParticleDistribution> particle_distribution =
    createCartesianSpatialSphericalDirectionalDist();

  // Set the random number generator stream
  std::vector<double> fake_stream( 7 );
  fake_stream[0] = 0.0; // x
  fake_stream[1] = 0.5; // energy
  fake_stream[2] = 0.5; // y
  fake_stream[3] = 1.0-1e-15; // z
  fake_stream[4] = 0.0; // theta
  fake_stream[5] = 1.0-1e-15; // mu
  fake_stream[6] = 0.0; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::PhotonState photon( 0 );

  particle_distribution->sample( photon );

  FRENSIE_CHECK_EQUAL( photon.getXPosition(), -1.0 );
  FRENSIE_CHECK_EQUAL( photon.getYPosition(), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZPosition(), 1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getXDirection(), 1e-7 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZDirection(), 1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getSourceEnergy(), 5.0 );
  FRENSIE_CHECK_EQUAL( photon.getEnergy(), 5.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceWeight(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getWeight(), 0.5 );

  // Set the random number generator stream
  fake_stream[0] = 0.5; // x
  fake_stream[1] = 0.5; // energy
  fake_stream[2] = 0.0; // y
  fake_stream[3] = 0.5; // z
  fake_stream[4] = 0.0; // theta
  fake_stream[5] = 0.0; // mu
  fake_stream[6] = 0.5; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  particle_distribution->sample( photon );

  FRENSIE_CHECK_EQUAL( photon.getXPosition(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getYPosition(), -1.0 );
  FRENSIE_CHECK_EQUAL( photon.getZPosition(), 0.0 );
  FRENSIE_CHECK_SMALL( photon.getXDirection(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZDirection(), -1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getSourceEnergy(), 10.0 );
  FRENSIE_CHECK_EQUAL( photon.getEnergy(), 10.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceTime(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getTime(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getSourceWeight(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getWeight(), 0.5 );

  // Set the random number generator stream
  fake_stream[0] = 1.0-1e-15; // x
  fake_stream[1] = 1.0-1e-15; // energy
  fake_stream[2] = 1.0-1e-15; // y
  fake_stream[3] = 0.0; // z
  fake_stream[4] = 0.5; // theta
  fake_stream[5] = 0.5; // mu
  fake_stream[6] = 1.0-1e-15; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  particle_distribution->sample( photon );

  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getXPosition(), 1.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getYPosition(), 1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getZPosition(), -1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getXDirection(), -1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getZDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getSourceEnergy(), 20.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getEnergy(), 20.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getSourceTime(), 1.0, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getTime(), 1.0, 1e-15 );
  FRENSIE_CHECK_EQUAL( photon.getSourceWeight(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getWeight(), 0.5 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distrubtion can be sampled
FRENSIE_UNIT_TEST( StandardParticleDistribution,
                   sample_cartesian_spatial_spherical_directional_mono_energy_mono_time )
{
  std::shared_ptr<const ParticleDistribution> particle_distribution =
    createCartesianSpatialSphericalDirectionalDist( true, true );

  // Set the random number generator stream
  std::vector<double> fake_stream( 7 );
  fake_stream[0] = 0.0; // x
  fake_stream[1] = 0.5; // y
  fake_stream[2] = 1.0-1e-15; // z
  fake_stream[3] = 0.0; // theta
  fake_stream[4] = 1.0-1e-15; // mu

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::PhotonState photon( 0 );

  particle_distribution->sample( photon );

  FRENSIE_CHECK_EQUAL( photon.getXPosition(), -1.0 );
  FRENSIE_CHECK_EQUAL( photon.getYPosition(), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZPosition(), 1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getXDirection(), 1e-7 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZDirection(), 1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getSourceEnergy(), 10.0 );
  FRENSIE_CHECK_EQUAL( photon.getEnergy(), 10.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceTime(), 1.0 );
  FRENSIE_CHECK_EQUAL( photon.getTime(), 1.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceWeight(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getWeight(), 0.5 );

  // Set the random number generator stream
  fake_stream[0] = 0.5; // x
  fake_stream[1] = 0.0; // y
  fake_stream[2] = 0.5; // z
  fake_stream[3] = 0.0; // theta
  fake_stream[4] = 0.0; // mu

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  particle_distribution->sample( photon );

  FRENSIE_CHECK_EQUAL( photon.getXPosition(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getYPosition(), -1.0 );
  FRENSIE_CHECK_EQUAL( photon.getZPosition(), 0.0 );
  FRENSIE_CHECK_SMALL( photon.getXDirection(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZDirection(), -1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getSourceEnergy(), 10.0 );
  FRENSIE_CHECK_EQUAL( photon.getEnergy(), 10.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceTime(), 1.0 );
  FRENSIE_CHECK_EQUAL( photon.getTime(), 1.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceWeight(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getWeight(), 0.5 );

  // Set the random number generator stream
  fake_stream[0] = 1.0-1e-15; // x
  fake_stream[1] = 1.0-1e-15; // y
  fake_stream[2] = 0.0; // z
  fake_stream[3] = 0.5; // theta
  fake_stream[4] = 0.5; // mu

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  particle_distribution->sample( photon );

  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getXPosition(), 1.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getYPosition(), 1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getZPosition(), -1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getXDirection(), -1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getZDirection(), 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getSourceEnergy(), 10.0 );
  FRENSIE_CHECK_EQUAL( photon.getEnergy(), 10.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceTime(), 1.0 );
  FRENSIE_CHECK_EQUAL( photon.getTime(), 1.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceWeight(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getWeight(), 0.5 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distrubtion can be sampled
FRENSIE_UNIT_TEST( StandardParticleDistribution,
                   sample_cylindrical_spatial_cartesian_directional )
{
  std::shared_ptr<const ParticleDistribution> particle_distribution =
    createCylindricalSpatialCartesianDirectionalDist();

  // Set the random number generator stream
  std::vector<double> fake_stream( 8 );
  fake_stream[0] = 0.0; // r
  fake_stream[1] = 0.5; // theta
  fake_stream[2] = 0.0; // z
  fake_stream[3] = 0.5; // energy
  fake_stream[4] = 0.5; // u
  fake_stream[5] = 0.5; // v
  fake_stream[6] = 1.0-1e-15; // w
  fake_stream[7] = 0.0; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::PhotonState photon( 0 );

  particle_distribution->sample( photon );

  FRENSIE_CHECK_EQUAL( photon.getXPosition(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getYPosition(), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZPosition(), -1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getXDirection(), 1e-7 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZDirection(), 1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getSourceEnergy(), 5.0 );
  FRENSIE_CHECK_EQUAL( photon.getEnergy(), 5.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceWeight(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getWeight(), 0.5 );

  // Set the random number generator stream
  fake_stream[0] = 0.5; // r
  fake_stream[1] = 0.5; // theta
  fake_stream[2] = 0.5; // z
  fake_stream[3] = 0.5; // energy
  fake_stream[4] = 0.5; // u
  fake_stream[5] = 1.0-1e-15; // v
  fake_stream[6] = 0.5; // w
  fake_stream[7] = 0.5; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  particle_distribution->sample( photon );

  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getXPosition(), -0.7071067811865476, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getYPosition(), 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getZPosition(), 0.0 );
  FRENSIE_CHECK_SMALL( photon.getXDirection(), 1e-7 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getYDirection(), 1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getZDirection(), 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getSourceEnergy(), 10.0 );
  FRENSIE_CHECK_EQUAL( photon.getEnergy(), 10.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceTime(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getTime(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getSourceWeight(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getWeight(), 0.5 );

  // Set the random number generator stream
  fake_stream[0] = 1.0-1e-15; // r
  fake_stream[1] = 0.25; // theta
  fake_stream[2] = 1.0-1e-15; // z
  fake_stream[3] = 1.0-1e-15; // energy
  fake_stream[4] = 1.0-1e-15; // u
  fake_stream[5] = 0.5; // v
  fake_stream[6] = 0.5; // w
  fake_stream[7] = 1.0-1e-15; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  particle_distribution->sample( photon );

  FRENSIE_CHECK_SMALL( photon.getXPosition(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getYPosition(), 1.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZPosition(), 1.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getXDirection(), 1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getZDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getSourceEnergy(), 20.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getEnergy(), 20.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getSourceTime(), 1.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getTime(), 1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getSourceWeight(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getWeight(), 0.5 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distrubtion can be sampled
FRENSIE_UNIT_TEST( StandardParticleDistribution,
                   sample_cylindrical_spatial_spherical_directional )
{
  std::shared_ptr<const ParticleDistribution> particle_distribution =
    createCylindricalSpatialSphericalDirectionalDist();

  // Set the random number generator stream
  std::vector<double> fake_stream( 7 );
  fake_stream[0] = 0.0; // r
  fake_stream[1] = 0.5; // theta
  fake_stream[2] = 0.0; // z
  fake_stream[3] = 0.5; // energy
  fake_stream[4] = 0.0; // theta
  fake_stream[5] = 0.0; // mu
  fake_stream[6] = 0.0; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::PhotonState photon( 0 );

  particle_distribution->sample( photon );

  FRENSIE_CHECK_EQUAL( photon.getXPosition(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getYPosition(), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZPosition(), -1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getXDirection(), 1e-7 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZDirection(), -1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getSourceEnergy(), 5.0 );
  FRENSIE_CHECK_EQUAL( photon.getEnergy(), 5.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceWeight(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getWeight(), 0.5 );

  // Set the random number generator stream
  fake_stream[0] = 0.5; // r
  fake_stream[1] = 0.5; // theta
  fake_stream[2] = 0.5; // z
  fake_stream[3] = 0.5; // energy
  fake_stream[4] = 0.0; // theta
  fake_stream[5] = 1.0-1e-15; // mu
  fake_stream[6] = 0.5; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  particle_distribution->sample( photon );

  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getXPosition(), -0.7071067811865476, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getYPosition(), 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getZPosition(), 0.0 );
  FRENSIE_CHECK_SMALL( photon.getXDirection(), 1e-7 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZDirection(), 1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getSourceEnergy(), 10.0 );
  FRENSIE_CHECK_EQUAL( photon.getEnergy(), 10.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceTime(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getTime(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getSourceWeight(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getWeight(), 0.5 );

  // Set the random number generator stream
  fake_stream[0] = 1.0-1e-15; // r
  fake_stream[1] = 0.25; // theta
  fake_stream[2] = 1.0-1e-15; // z
  fake_stream[3] = 1.0-1e-15; // energy
  fake_stream[4] = 1.0-1e-15; // theta
  fake_stream[5] = 0.5; // mu
  fake_stream[6] = 1.0-1e-15; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  particle_distribution->sample( photon );

  FRENSIE_CHECK_SMALL( photon.getXPosition(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getYPosition(), 1.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZPosition(), 1.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getXDirection(), 1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getZDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getSourceEnergy(), 20.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getEnergy(), 20.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getSourceTime(), 1.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getTime(), 1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getSourceWeight(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getWeight(), 0.5 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distrubtion can be sampled
FRENSIE_UNIT_TEST( StandardParticleDistribution,
                   sample_spherical_spatial_cartesian_directional )
{
  std::shared_ptr<const ParticleDistribution> particle_distribution =
    createSphericalSpatialCartesianDirectionalDist();

  // Set the random number generator stream
  std::vector<double> fake_stream( 8 );
  fake_stream[0] = 1.0-1e-12; // r
  fake_stream[1] = 0.0; // theta
  fake_stream[2] = 0.0; // mu
  fake_stream[3] = 0.5; // energy
  fake_stream[4] = 0.5; // u
  fake_stream[5] = 0.5; // v
  fake_stream[6] = 1.0-1e-15; // w
  fake_stream[7] = 0.0; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::PhotonState photon( 0 );

  particle_distribution->sample( photon );

  FRENSIE_CHECK_SMALL( photon.getXPosition(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getYPosition(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZPosition(), -1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getXDirection(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZDirection(), 1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getSourceEnergy(), 5.0 );
  FRENSIE_CHECK_EQUAL( photon.getEnergy(), 5.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceWeight(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getWeight(), 0.5 );

  // Set the random number generator stream
  fake_stream[0] = 0.0; // r
  fake_stream[1] = 0.0; // theta
  fake_stream[2] = 0.0; // mu
  fake_stream[3] = 0.5; // energy
  fake_stream[4] = 0.5; // u
  fake_stream[5] = 1.0-1e-15; // v
  fake_stream[6] = 0.5; // w
  fake_stream[7] = 0.0; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  particle_distribution->sample( photon );

  FRENSIE_CHECK_SMALL( photon.getXPosition(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getYPosition(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getZPosition(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getXDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getYDirection(), 1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getZDirection(), 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getSourceEnergy(), 5.0 );
  FRENSIE_CHECK_EQUAL( photon.getEnergy(), 5.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceWeight(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getWeight(), 0.5 );

  // Set the random number generator stream
  fake_stream[0] = 1.0-1e-15; // r
  fake_stream[1] = 0.5; // theta
  fake_stream[2] = 0.5; // mu
  fake_stream[3] = 0.5; // energy
  fake_stream[4] = 1.0-1e-15; // u
  fake_stream[5] = 0.5; // v
  fake_stream[6] = 0.5; // w
  fake_stream[7] = 0.5; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  particle_distribution->sample( photon );

  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getXPosition(), -1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getYPosition(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getZPosition(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getXDirection(), 1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getZDirection(), 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getSourceEnergy(), 10.0 );
  FRENSIE_CHECK_EQUAL( photon.getEnergy(), 10.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceTime(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getTime(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getSourceWeight(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getWeight(), 0.5 );

  // Set the random number generator stream
  fake_stream[0] = 1.0-1e-15; // r
  fake_stream[1] = 0.0; // theta
  fake_stream[2] = 1.0-1e-15; // mu
  fake_stream[3] = 1.0-1e-15; // energy
  fake_stream[4] = 1.0-1e-15; // u
  fake_stream[5] = 1.0-1e-15; // v
  fake_stream[6] = 0.5; // w
  fake_stream[7] = 1.0-1e-15; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  particle_distribution->sample( photon );

  FRENSIE_CHECK_SMALL( photon.getXPosition(), 1e-7 );
  FRENSIE_CHECK_SMALL( photon.getYPosition(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZPosition(), 1.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getXDirection(), 1.0/sqrt(2.0), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getYDirection(), 1.0/sqrt(2.0), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getZDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getSourceEnergy(), 20.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getEnergy(), 20.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getSourceTime(), 1.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getTime(), 1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getSourceWeight(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getWeight(), 0.5 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distrubtion can be sampled
FRENSIE_UNIT_TEST( StandardParticleDistribution,
                   sample_spherical_spatial_spherical_directional )
{
  std::shared_ptr<const ParticleDistribution> particle_distribution =
    createSphericalSpatialSphericalDirectionalDist();

  // Set the random number generator stream
  std::vector<double> fake_stream( 7 );
  fake_stream[0] = 1.0-1e-12; // r
  fake_stream[1] = 0.0; // theta
  fake_stream[2] = 0.0; // mu
  fake_stream[3] = 0.5; // energy
  fake_stream[4] = 0.0; // theta
  fake_stream[5] = 0.0; // mu
  fake_stream[6] = 0.0; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::PhotonState photon( 0 );

  particle_distribution->sample( photon );

  FRENSIE_CHECK_SMALL( photon.getXPosition(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getYPosition(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZPosition(), -1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getXDirection(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZDirection(), -1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getSourceEnergy(), 5.0 );
  FRENSIE_CHECK_EQUAL( photon.getEnergy(), 5.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceWeight(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getWeight(), 0.5 );

  // Set the random number generator stream
  fake_stream[0] = 0.0; // r
  fake_stream[1] = 0.0; // theta
  fake_stream[2] = 0.0; // mu
  fake_stream[3] = 0.5; // energy
  fake_stream[4] = 0.0; // theta
  fake_stream[5] = 0.5; // mu
  fake_stream[6] = 0.0; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  particle_distribution->sample( photon );

  FRENSIE_CHECK_SMALL( photon.getXPosition(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getYPosition(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getZPosition(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getXDirection(), 1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getZDirection(), 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getSourceEnergy(), 5.0 );
  FRENSIE_CHECK_EQUAL( photon.getEnergy(), 5.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceWeight(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getWeight(), 0.5 );

  // Set the random number generator stream
  fake_stream[0] = 1.0-1e-15; // r
  fake_stream[1] = 0.5; // theta
  fake_stream[2] = 0.5; // mu
  fake_stream[3] = 0.5; // energy
  fake_stream[4] = 0.75; // theta
  fake_stream[5] = 0.5; // mu
  fake_stream[6] = 0.5; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  particle_distribution->sample( photon );

  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getXPosition(), -1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getYPosition(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getZPosition(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getXDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getYDirection(), -1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getZDirection(), 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getSourceEnergy(), 10.0 );
  FRENSIE_CHECK_EQUAL( photon.getEnergy(), 10.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceTime(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getTime(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getSourceWeight(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getWeight(), 0.5 );

  // Set the random number generator stream
  fake_stream[0] = 1.0-1e-15; // r
  fake_stream[1] = 0.0; // theta
  fake_stream[2] = 1.0-1e-15; // mu
  fake_stream[3] = 1.0-1e-15; // energy
  fake_stream[4] = 0.0; // theta
  fake_stream[5] = 1.0-1e-15; // mu
  fake_stream[6] = 1.0-1e-15; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  particle_distribution->sample( photon );

  FRENSIE_CHECK_SMALL( photon.getXPosition(), 1e-7 );
  FRENSIE_CHECK_SMALL( photon.getYPosition(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZPosition(), 1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getXDirection(), 1e-7 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZDirection(), 1.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getSourceEnergy(), 20.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getEnergy(), 20.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getSourceTime(), 1.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getTime(), 1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getSourceWeight(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getWeight(), 0.5 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
FRENSIE_UNIT_TEST( StandardParticleDistribution,
                   sample_point_spatial_mono_directional )
{
  std::shared_ptr<const ParticleDistribution> particle_distribution;

  {
    std::shared_ptr<StandardParticleDistribution>
      tmp_particle_distribution( new StandardParticleDistribution( "test dist" ) );

    std::vector<double> position({1.0, 2.0, 3.0});
    std::vector<double> direction({0.0, -1/std::sqrt(2.0), 1/std::sqrt(2.0)});

    tmp_particle_distribution->setPosition( position.data() );
    tmp_particle_distribution->setDirection( direction.data() );

    std::shared_ptr<const Utility::UnivariateDistribution> raw_uniform_dist(
                           new Utility::UniformDistribution( 0.0, 1.0, 1.0 ) );

    std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
      energy_dimension_dist( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION>( raw_uniform_dist ) );
    tmp_particle_distribution->setDimensionDistribution( energy_dimension_dist );

    std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
      time_dimension_dist( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION>( raw_uniform_dist ) );
    tmp_particle_distribution->setDimensionDistribution( time_dimension_dist );

    std::shared_ptr<const Utility::UnivariateDistribution> raw_delta_dist(
                                       new Utility::DeltaDistribution( 0.5 ) );

    std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
      weight_dimension_dist( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::WEIGHT_DIMENSION>( raw_delta_dist ) );
    tmp_particle_distribution->setDimensionDistribution( weight_dimension_dist );

    tmp_particle_distribution->constructDimensionDistributionDependencyTree();

    particle_distribution = tmp_particle_distribution;
  }

  // Set the random number generator stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.25; // energy
  fake_stream[1] = 0.5; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::PhotonState photon( 0 );

  particle_distribution->sample( photon );

  FRENSIE_CHECK_EQUAL( photon.getXPosition(), 1.0 );
  FRENSIE_CHECK_EQUAL( photon.getYPosition(), 2.0 );
  FRENSIE_CHECK_EQUAL( photon.getZPosition(), 3.0 );
  FRENSIE_CHECK_SMALL( photon.getXDirection(), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getYDirection(),
                                   -1/std::sqrt(2.0),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZDirection(),
                                   1/std::sqrt(2.0),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getEnergy(), 0.25, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getTime(), 0.5, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getWeight(), 0.5, 1e-15 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distrubtion can be sampled and the trials can be recorded
FRENSIE_UNIT_TEST( StandardParticleDistribution, sampleAndRecordTrials )
{
  std::shared_ptr<const ParticleDistribution> particle_distribution =
    createSphericalSpatialSphericalDirectionalDist();

  ParticleDistribution::DimensionCounterMap trials;

  particle_distribution->initializeDimensionCounters( trials );

  // Set the random number generator stream
  std::vector<double> fake_stream( 7 );
  fake_stream[0] = 1.0-1e-12; // r
  fake_stream[1] = 0.0; // theta
  fake_stream[2] = 0.0; // mu
  fake_stream[3] = 0.5; // energy
  fake_stream[4] = 0.0; // theta
  fake_stream[5] = 0.0; // mu
  fake_stream[6] = 0.0; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::PhotonState photon( 0 );

  particle_distribution->sampleAndRecordTrials( photon, trials );

  FRENSIE_CHECK_SMALL( photon.getXPosition(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getYPosition(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZPosition(), -1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getXDirection(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZDirection(), -1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getSourceEnergy(), 5.0 );
  FRENSIE_CHECK_EQUAL( photon.getEnergy(), 5.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceWeight(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getWeight(), 0.5 );
  FRENSIE_CHECK_EQUAL( trials[PRIMARY_SPATIAL_DIMENSION], 1 );
  FRENSIE_CHECK_EQUAL( trials[SECONDARY_SPATIAL_DIMENSION], 1 );
  FRENSIE_CHECK_EQUAL( trials[TERTIARY_SPATIAL_DIMENSION], 1 );
  FRENSIE_CHECK_EQUAL( trials[PRIMARY_DIRECTIONAL_DIMENSION], 1 );
  FRENSIE_CHECK_EQUAL( trials[SECONDARY_DIRECTIONAL_DIMENSION], 1 );
  FRENSIE_CHECK_EQUAL( trials[TERTIARY_DIRECTIONAL_DIMENSION], 1 );
  FRENSIE_CHECK_EQUAL( trials[ENERGY_DIMENSION], 1 );
  FRENSIE_CHECK_EQUAL( trials[TIME_DIMENSION], 1 );
  FRENSIE_CHECK_EQUAL( trials[WEIGHT_DIMENSION], 1 );

  // Set the random number generator stream
  fake_stream[0] = 0.0; // r
  fake_stream[1] = 0.0; // theta
  fake_stream[2] = 0.0; // mu
  fake_stream[3] = 0.5; // energy
  fake_stream[4] = 0.0; // theta
  fake_stream[5] = 0.5; // mu
  fake_stream[6] = 0.0; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  particle_distribution->sampleAndRecordTrials( photon, trials );

  FRENSIE_CHECK_SMALL( photon.getXPosition(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getYPosition(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getZPosition(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getXDirection(), 1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getZDirection(), 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getSourceEnergy(), 5.0 );
  FRENSIE_CHECK_EQUAL( photon.getEnergy(), 5.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceWeight(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getWeight(), 0.5 );
  FRENSIE_CHECK_EQUAL( trials[PRIMARY_SPATIAL_DIMENSION], 2 );
  FRENSIE_CHECK_EQUAL( trials[SECONDARY_SPATIAL_DIMENSION], 2 );
  FRENSIE_CHECK_EQUAL( trials[TERTIARY_SPATIAL_DIMENSION], 2 );
  FRENSIE_CHECK_EQUAL( trials[PRIMARY_DIRECTIONAL_DIMENSION], 2 );
  FRENSIE_CHECK_EQUAL( trials[SECONDARY_DIRECTIONAL_DIMENSION], 2 );
  FRENSIE_CHECK_EQUAL( trials[TERTIARY_DIRECTIONAL_DIMENSION], 2 );
  FRENSIE_CHECK_EQUAL( trials[ENERGY_DIMENSION], 2 );
  FRENSIE_CHECK_EQUAL( trials[TIME_DIMENSION], 2 );
  FRENSIE_CHECK_EQUAL( trials[WEIGHT_DIMENSION], 2 );

  // Set the random number generator stream
  fake_stream[0] = 1.0-1e-15; // r
  fake_stream[1] = 0.5; // theta
  fake_stream[2] = 0.5; // mu
  fake_stream[3] = 0.5; // energy
  fake_stream[4] = 0.75; // theta
  fake_stream[5] = 0.5; // mu
  fake_stream[6] = 0.5; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  particle_distribution->sampleAndRecordTrials( photon, trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getXPosition(), -1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getYPosition(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getZPosition(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getXDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getYDirection(), -1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getZDirection(), 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getSourceEnergy(), 10.0 );
  FRENSIE_CHECK_EQUAL( photon.getEnergy(), 10.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceTime(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getTime(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getSourceWeight(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getWeight(), 0.5 );
  FRENSIE_CHECK_EQUAL( trials[PRIMARY_SPATIAL_DIMENSION], 3 );
  FRENSIE_CHECK_EQUAL( trials[SECONDARY_SPATIAL_DIMENSION], 3 );
  FRENSIE_CHECK_EQUAL( trials[TERTIARY_SPATIAL_DIMENSION], 3 );
  FRENSIE_CHECK_EQUAL( trials[PRIMARY_DIRECTIONAL_DIMENSION], 3 );
  FRENSIE_CHECK_EQUAL( trials[SECONDARY_DIRECTIONAL_DIMENSION], 3 );
  FRENSIE_CHECK_EQUAL( trials[TERTIARY_DIRECTIONAL_DIMENSION], 3 );
  FRENSIE_CHECK_EQUAL( trials[ENERGY_DIMENSION], 3 );
  FRENSIE_CHECK_EQUAL( trials[TIME_DIMENSION], 3 );
  FRENSIE_CHECK_EQUAL( trials[WEIGHT_DIMENSION], 3 );

  // Set the random number generator stream
  fake_stream[0] = 1.0-1e-15; // r
  fake_stream[1] = 0.0; // theta
  fake_stream[2] = 1.0-1e-15; // mu
  fake_stream[3] = 1.0-1e-15; // energy
  fake_stream[4] = 0.0; // theta
  fake_stream[5] = 1.0-1e-15; // mu
  fake_stream[6] = 1.0-1e-15; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  particle_distribution->sampleAndRecordTrials( photon, trials );

  FRENSIE_CHECK_SMALL( photon.getXPosition(), 1e-7 );
  FRENSIE_CHECK_SMALL( photon.getYPosition(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZPosition(), 1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getXDirection(), 1e-7 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZDirection(), 1.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getSourceEnergy(), 20.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getEnergy(), 20.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getSourceTime(), 1.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getTime(), 1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getSourceWeight(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getWeight(), 0.5 );
  FRENSIE_CHECK_EQUAL( trials[PRIMARY_SPATIAL_DIMENSION], 4 );
  FRENSIE_CHECK_EQUAL( trials[SECONDARY_SPATIAL_DIMENSION], 4 );
  FRENSIE_CHECK_EQUAL( trials[TERTIARY_SPATIAL_DIMENSION], 4 );
  FRENSIE_CHECK_EQUAL( trials[PRIMARY_DIRECTIONAL_DIMENSION], 4 );
  FRENSIE_CHECK_EQUAL( trials[SECONDARY_DIRECTIONAL_DIMENSION], 4 );
  FRENSIE_CHECK_EQUAL( trials[TERTIARY_DIRECTIONAL_DIMENSION], 4 );
  FRENSIE_CHECK_EQUAL( trials[ENERGY_DIMENSION], 4 );
  FRENSIE_CHECK_EQUAL( trials[TIME_DIMENSION], 4 );
  FRENSIE_CHECK_EQUAL( trials[WEIGHT_DIMENSION], 4 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distrubtion can be sampled
FRENSIE_UNIT_TEST( StandardParticleDistribution, sampleWithDimensionValue )
{
  std::shared_ptr<const ParticleDistribution> particle_distribution =
    createSphericalSpatialSphericalDirectionalDist();

  // Set the random number generator stream
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.0; // theta
  fake_stream[1] = 1.0-1e-15; // mu
  fake_stream[2] = 1.0-1e-15; // energy
  fake_stream[3] = 0.0; // theta
  fake_stream[4] = 1.0-1e-15; // mu
  fake_stream[5] = 1.0-1e-15; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::PhotonState photon( 0 );

  particle_distribution->sampleWithDimensionValue( photon, PRIMARY_SPATIAL_DIMENSION, 0.5 );

  FRENSIE_CHECK_SMALL( photon.getXPosition(), 1e-7 );
  FRENSIE_CHECK_SMALL( photon.getYPosition(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZPosition(), 0.5, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getXDirection(), 1e-7 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZDirection(), 1.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getSourceEnergy(), 20.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getEnergy(), 20.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getSourceTime(), 1.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getTime(), 1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getSourceWeight(), 0.375 );
  FRENSIE_CHECK_EQUAL( photon.getWeight(), 0.375 );

  // Set the random number generator stream
  fake_stream[0] = 1.0-1e-12; // r
  fake_stream[1] = 0.5; // mu
  fake_stream[2] = 0.5; // energy
  fake_stream[3] = 0.0; // theta
  fake_stream[4] = 1.0-1e-15; // mu
  fake_stream[5] = 0.0; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  particle_distribution->sampleWithDimensionValue( photon, SECONDARY_SPATIAL_DIMENSION, Utility::PhysicalConstants::pi/2 );

  FRENSIE_CHECK_SMALL( photon.getXPosition(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getYPosition(), 1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getZPosition(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getXDirection(), 1e-7 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZDirection(), 1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getSourceEnergy(), 10.0 );
  FRENSIE_CHECK_EQUAL( photon.getEnergy(), 10.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getTime(), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getSourceWeight(), 0.07957747154594767, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getWeight(), 0.07957747154594767, 1e-12 );

  // Set the random number generator stream
  fake_stream[0] = 1.0-1e-12; // r
  fake_stream[1] = 0.75; // theta
  fake_stream[2] = 0.5; // energy
  fake_stream[3] = 0.0; // theta
  fake_stream[4] = 1.0-1e-15; // mu
  fake_stream[5] = 0.0; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  particle_distribution->sampleWithDimensionValue( photon, TERTIARY_SPATIAL_DIMENSION, 0.0 );

  FRENSIE_CHECK_SMALL( photon.getXPosition(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getYPosition(), -1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getZPosition(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getXDirection(), 1e-7 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZDirection(), 1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getSourceEnergy(), 10.0 );
  FRENSIE_CHECK_EQUAL( photon.getEnergy(), 10.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceWeight(), 0.25 );
  FRENSIE_CHECK_EQUAL( photon.getWeight(), 0.25 );

  // Set the random number generator stream
  fake_stream[0] = 1.0-1e-12; // r
  fake_stream[1] = 0.75; // theta
  fake_stream[2] = 0.5; // mu
  fake_stream[3] = 0.5; // energy
  fake_stream[4] = 0.5; // mu
  fake_stream[5] = 0.0; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  particle_distribution->sampleWithDimensionValue( photon, SECONDARY_DIRECTIONAL_DIMENSION, 0.0 );

  FRENSIE_CHECK_SMALL( photon.getXPosition(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getYPosition(), -1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getZPosition(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getXDirection(), 1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getZDirection(), 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getSourceEnergy(), 10.0 );
  FRENSIE_CHECK_EQUAL( photon.getEnergy(), 10.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getTime(), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getSourceWeight(), 0.07957747154594767, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getWeight(), 0.07957747154594767, 1e-12 );

  // Set the random number generator stream
  fake_stream[0] = 1.0-1e-12; // r
  fake_stream[1] = 0.75; // theta
  fake_stream[2] = 0.5; // mu
  fake_stream[3] = 0.5; // energy
  fake_stream[4] = 0.0; // theta
  fake_stream[5] = 0.0; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  particle_distribution->sampleWithDimensionValue( photon, TERTIARY_DIRECTIONAL_DIMENSION, 1.0 );

  FRENSIE_CHECK_SMALL( photon.getXPosition(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getYPosition(), -1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getZPosition(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getXDirection(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZDirection(), 1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getSourceEnergy(), 10.0 );
  FRENSIE_CHECK_EQUAL( photon.getEnergy(), 10.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceWeight(), 0.25 );
  FRENSIE_CHECK_EQUAL( photon.getWeight(), 0.25 );

  // Set the random number generator stream
  fake_stream[0] = 1.0-1e-12; // r
  fake_stream[1] = 0.0; // theta
  fake_stream[2] = 0.0; // mu
  fake_stream[3] = 0.0; // theta
  fake_stream[4] = 0.0; // mu
  fake_stream[5] = 0.0; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  particle_distribution->sampleWithDimensionValue( photon, ENERGY_DIMENSION, 1.0 );

  FRENSIE_CHECK_SMALL( photon.getXPosition(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getYPosition(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZPosition(), -1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getXDirection(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZDirection(), -1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getSourceEnergy(), 1.0 );
  FRENSIE_CHECK_EQUAL( photon.getEnergy(), 1.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceWeight(), 0.05 );
  FRENSIE_CHECK_EQUAL( photon.getWeight(), 0.05 );

  // Set the random number generator stream
  fake_stream[0] = 0.0; // r
  fake_stream[1] = 0.0; // theta
  fake_stream[2] = 0.0; // mu
  fake_stream[3] = 0.0; // theta
  fake_stream[4] = 0.5; // mu
  fake_stream[5] = 0.0; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  particle_distribution->sampleWithDimensionValue( photon, ENERGY_DIMENSION, 2.0 );

  FRENSIE_CHECK_SMALL( photon.getXPosition(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getYPosition(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getZPosition(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getXDirection(), 1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getZDirection(), 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getSourceEnergy(), 2.0 );
  FRENSIE_CHECK_EQUAL( photon.getEnergy(), 2.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceWeight(), 0.05 );
  FRENSIE_CHECK_EQUAL( photon.getWeight(), 0.05 );

  // Set the random number generator stream
  fake_stream[0] = 1.0-1e-15; // r
  fake_stream[1] = 0.5; // theta
  fake_stream[2] = 0.5; // mu
  fake_stream[3] = 0.75; // theta
  fake_stream[4] = 0.5; // mu
  fake_stream[5] = 0.5; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  particle_distribution->sampleWithDimensionValue( photon, ENERGY_DIMENSION, 15.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getXPosition(), -1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getYPosition(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getZPosition(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getXDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getYDirection(), -1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getZDirection(), 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getSourceEnergy(), 15.0 );
  FRENSIE_CHECK_EQUAL( photon.getEnergy(), 15.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceTime(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getTime(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getSourceWeight(), 0.025 );
  FRENSIE_CHECK_EQUAL( photon.getWeight(), 0.025 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distrubtion can be sampled
FRENSIE_UNIT_TEST( StandardParticleDistribution,
                   sampleWithDimensionValueAndRecordTrials )
{
  std::shared_ptr<const ParticleDistribution> particle_distribution =
    createSphericalSpatialSphericalDirectionalDist();

  ParticleDistribution::DimensionCounterMap trials;

  particle_distribution->initializeDimensionCounters( trials );

  // Set the random number generator stream
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.0; // theta
  fake_stream[1] = 1.0-1e-15; // mu
  fake_stream[2] = 1.0-1e-15; // energy
  fake_stream[3] = 0.0; // theta
  fake_stream[4] = 1.0-1e-15; // mu
  fake_stream[5] = 1.0-1e-15; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::PhotonState photon( 0 );

  particle_distribution->sampleWithDimensionValueAndRecordTrials( photon, trials, PRIMARY_SPATIAL_DIMENSION, 0.5 );

  FRENSIE_CHECK_SMALL( photon.getXPosition(), 1e-7 );
  FRENSIE_CHECK_SMALL( photon.getYPosition(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZPosition(), 0.5, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getXDirection(), 1e-7 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZDirection(), 1.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getSourceEnergy(), 20.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getEnergy(), 20.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getSourceTime(), 1.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getTime(), 1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getSourceWeight(), 0.375 );
  FRENSIE_CHECK_EQUAL( photon.getWeight(), 0.375 );
  FRENSIE_CHECK_EQUAL( trials[PRIMARY_SPATIAL_DIMENSION], 0 );
  FRENSIE_CHECK_EQUAL( trials[SECONDARY_SPATIAL_DIMENSION], 1 );
  FRENSIE_CHECK_EQUAL( trials[TERTIARY_SPATIAL_DIMENSION], 1 );
  FRENSIE_CHECK_EQUAL( trials[PRIMARY_DIRECTIONAL_DIMENSION], 1 );
  FRENSIE_CHECK_EQUAL( trials[SECONDARY_DIRECTIONAL_DIMENSION], 1 );
  FRENSIE_CHECK_EQUAL( trials[TERTIARY_DIRECTIONAL_DIMENSION], 1 );
  FRENSIE_CHECK_EQUAL( trials[ENERGY_DIMENSION], 1 );
  FRENSIE_CHECK_EQUAL( trials[TIME_DIMENSION], 1 );
  FRENSIE_CHECK_EQUAL( trials[WEIGHT_DIMENSION], 1 );

  // Set the random number generator stream
  fake_stream[0] = 1.0-1e-12; // r
  fake_stream[1] = 0.5; // mu
  fake_stream[2] = 0.5; // energy
  fake_stream[3] = 0.0; // theta
  fake_stream[4] = 1.0-1e-15; // mu
  fake_stream[5] = 0.0; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  particle_distribution->sampleWithDimensionValueAndRecordTrials( photon, trials, SECONDARY_SPATIAL_DIMENSION, Utility::PhysicalConstants::pi/2 );

  FRENSIE_CHECK_SMALL( photon.getXPosition(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getYPosition(), 1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getZPosition(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getXDirection(), 1e-7 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZDirection(), 1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getSourceEnergy(), 10.0 );
  FRENSIE_CHECK_EQUAL( photon.getEnergy(), 10.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getTime(), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getSourceWeight(), 0.07957747154594767, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getWeight(), 0.07957747154594767, 1e-12 );
  FRENSIE_CHECK_EQUAL( trials[PRIMARY_SPATIAL_DIMENSION], 1 );
  FRENSIE_CHECK_EQUAL( trials[SECONDARY_SPATIAL_DIMENSION], 1 );
  FRENSIE_CHECK_EQUAL( trials[TERTIARY_SPATIAL_DIMENSION], 2 );
  FRENSIE_CHECK_EQUAL( trials[PRIMARY_DIRECTIONAL_DIMENSION], 2 );
  FRENSIE_CHECK_EQUAL( trials[SECONDARY_DIRECTIONAL_DIMENSION], 2 );
  FRENSIE_CHECK_EQUAL( trials[TERTIARY_DIRECTIONAL_DIMENSION], 2 );
  FRENSIE_CHECK_EQUAL( trials[ENERGY_DIMENSION], 2 );
  FRENSIE_CHECK_EQUAL( trials[TIME_DIMENSION], 2 );
  FRENSIE_CHECK_EQUAL( trials[WEIGHT_DIMENSION], 2 );

  // Set the random number generator stream
  fake_stream[0] = 1.0-1e-12; // r
  fake_stream[1] = 0.75; // theta
  fake_stream[2] = 0.5; // energy
  fake_stream[3] = 0.0; // theta
  fake_stream[4] = 1.0-1e-15; // mu
  fake_stream[5] = 0.0; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  particle_distribution->sampleWithDimensionValueAndRecordTrials( photon, trials, TERTIARY_SPATIAL_DIMENSION, 0.0 );

  FRENSIE_CHECK_SMALL( photon.getXPosition(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getYPosition(), -1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getZPosition(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getXDirection(), 1e-7 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZDirection(), 1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getSourceEnergy(), 10.0 );
  FRENSIE_CHECK_EQUAL( photon.getEnergy(), 10.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceWeight(), 0.25 );
  FRENSIE_CHECK_EQUAL( photon.getWeight(), 0.25 );
  FRENSIE_CHECK_EQUAL( trials[PRIMARY_SPATIAL_DIMENSION], 2 );
  FRENSIE_CHECK_EQUAL( trials[SECONDARY_SPATIAL_DIMENSION], 2 );
  FRENSIE_CHECK_EQUAL( trials[TERTIARY_SPATIAL_DIMENSION], 2 );
  FRENSIE_CHECK_EQUAL( trials[PRIMARY_DIRECTIONAL_DIMENSION], 3 );
  FRENSIE_CHECK_EQUAL( trials[SECONDARY_DIRECTIONAL_DIMENSION], 3 );
  FRENSIE_CHECK_EQUAL( trials[TERTIARY_DIRECTIONAL_DIMENSION], 3 );
  FRENSIE_CHECK_EQUAL( trials[ENERGY_DIMENSION], 3 );
  FRENSIE_CHECK_EQUAL( trials[TIME_DIMENSION], 3 );
  FRENSIE_CHECK_EQUAL( trials[WEIGHT_DIMENSION], 3 );

  // Set the random number generator stream
  fake_stream[0] = 1.0-1e-12; // r
  fake_stream[1] = 0.75; // theta
  fake_stream[2] = 0.5; // mu
  fake_stream[3] = 0.5; // energy
  fake_stream[4] = 0.5; // mu
  fake_stream[5] = 0.0; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  particle_distribution->sampleWithDimensionValueAndRecordTrials( photon, trials, SECONDARY_DIRECTIONAL_DIMENSION, 0.0 );

  FRENSIE_CHECK_SMALL( photon.getXPosition(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getYPosition(), -1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getZPosition(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getXDirection(), 1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getZDirection(), 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getSourceEnergy(), 10.0 );
  FRENSIE_CHECK_EQUAL( photon.getEnergy(), 10.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getTime(), 0.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getSourceWeight(), 0.07957747154594767, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getWeight(), 0.07957747154594767, 1e-12 );
  FRENSIE_CHECK_EQUAL( trials[PRIMARY_SPATIAL_DIMENSION], 3 );
  FRENSIE_CHECK_EQUAL( trials[SECONDARY_SPATIAL_DIMENSION], 3 );
  FRENSIE_CHECK_EQUAL( trials[TERTIARY_SPATIAL_DIMENSION], 3 );
  FRENSIE_CHECK_EQUAL( trials[PRIMARY_DIRECTIONAL_DIMENSION], 4 );
  FRENSIE_CHECK_EQUAL( trials[SECONDARY_DIRECTIONAL_DIMENSION], 3 );
  FRENSIE_CHECK_EQUAL( trials[TERTIARY_DIRECTIONAL_DIMENSION], 4 );
  FRENSIE_CHECK_EQUAL( trials[ENERGY_DIMENSION], 4 );
  FRENSIE_CHECK_EQUAL( trials[TIME_DIMENSION], 4 );
  FRENSIE_CHECK_EQUAL( trials[WEIGHT_DIMENSION], 4 );

  // Set the random number generator stream
  fake_stream[0] = 1.0-1e-12; // r
  fake_stream[1] = 0.75; // theta
  fake_stream[2] = 0.5; // mu
  fake_stream[3] = 0.5; // energy
  fake_stream[4] = 0.0; // theta
  fake_stream[5] = 0.0; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  particle_distribution->sampleWithDimensionValueAndRecordTrials( photon, trials, TERTIARY_DIRECTIONAL_DIMENSION, 1.0 );

  FRENSIE_CHECK_SMALL( photon.getXPosition(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getYPosition(), -1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getZPosition(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getXDirection(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZDirection(), 1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getSourceEnergy(), 10.0 );
  FRENSIE_CHECK_EQUAL( photon.getEnergy(), 10.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceWeight(), 0.25 );
  FRENSIE_CHECK_EQUAL( photon.getWeight(), 0.25 );
  FRENSIE_CHECK_EQUAL( trials[PRIMARY_SPATIAL_DIMENSION], 4 );
  FRENSIE_CHECK_EQUAL( trials[SECONDARY_SPATIAL_DIMENSION], 4 );
  FRENSIE_CHECK_EQUAL( trials[TERTIARY_SPATIAL_DIMENSION], 4 );
  FRENSIE_CHECK_EQUAL( trials[PRIMARY_DIRECTIONAL_DIMENSION], 5 );
  FRENSIE_CHECK_EQUAL( trials[SECONDARY_DIRECTIONAL_DIMENSION], 4 );
  FRENSIE_CHECK_EQUAL( trials[TERTIARY_DIRECTIONAL_DIMENSION], 4 );
  FRENSIE_CHECK_EQUAL( trials[ENERGY_DIMENSION], 5 );
  FRENSIE_CHECK_EQUAL( trials[TIME_DIMENSION], 5 );
  FRENSIE_CHECK_EQUAL( trials[WEIGHT_DIMENSION], 5 );

  // Set the random number generator stream
  fake_stream[0] = 1.0-1e-12; // r
  fake_stream[1] = 0.0; // theta
  fake_stream[2] = 0.0; // mu
  fake_stream[3] = 0.0; // theta
  fake_stream[4] = 0.0; // mu
  fake_stream[5] = 0.0; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  particle_distribution->sampleWithDimensionValueAndRecordTrials( photon, trials, ENERGY_DIMENSION, 1.0 );

  FRENSIE_CHECK_SMALL( photon.getXPosition(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getYPosition(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZPosition(), -1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getXDirection(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZDirection(), -1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getSourceEnergy(), 1.0 );
  FRENSIE_CHECK_EQUAL( photon.getEnergy(), 1.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceWeight(), 0.05 );
  FRENSIE_CHECK_EQUAL( photon.getWeight(), 0.05 );
  FRENSIE_CHECK_EQUAL( trials[PRIMARY_SPATIAL_DIMENSION], 5 );
  FRENSIE_CHECK_EQUAL( trials[SECONDARY_SPATIAL_DIMENSION], 5 );
  FRENSIE_CHECK_EQUAL( trials[TERTIARY_SPATIAL_DIMENSION], 5 );
  FRENSIE_CHECK_EQUAL( trials[PRIMARY_DIRECTIONAL_DIMENSION], 6 );
  FRENSIE_CHECK_EQUAL( trials[SECONDARY_DIRECTIONAL_DIMENSION], 5 );
  FRENSIE_CHECK_EQUAL( trials[TERTIARY_DIRECTIONAL_DIMENSION], 5 );
  FRENSIE_CHECK_EQUAL( trials[ENERGY_DIMENSION], 5 );
  FRENSIE_CHECK_EQUAL( trials[TIME_DIMENSION], 6 );
  FRENSIE_CHECK_EQUAL( trials[WEIGHT_DIMENSION], 6 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the default dimension distributions are correct
FRENSIE_UNIT_TEST( StandardParticleDistribution,
                   default_dists_cartesian_spatial_cartesian_directional )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
    spatial_coord_conversion_policy( new Utility::BasicCartesianCoordinateConversionPolicy );

  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
    directional_coord_conversion_policy( new Utility::BasicCartesianCoordinateConversionPolicy );

  MonteCarlo::StandardParticleDistribution
    particle_distribution( "test dist",
                           spatial_coord_conversion_policy,
                           directional_coord_conversion_policy );

  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ),
                       "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::SECONDARY_SPATIAL_DIMENSION),
                       "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::TERTIARY_SPATIAL_DIMENSION),
                       "Delta Distribution" );

  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ),
                       "Uniform Distribution" );
  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION),
                       "Uniform Distribution" );
  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION),
                       "Uniform Distribution" );

  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::ENERGY_DIMENSION),
                       "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::TIME_DIMENSION),
                       "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::WEIGHT_DIMENSION),
                       "Delta Distribution" );
}

//---------------------------------------------------------------------------//
// CHeck that the default dimension distributions are correct
FRENSIE_UNIT_TEST( StandardParticleDistribution,
                   default_dists_cartesian_spatial_spherical_directional )
{
  MonteCarlo::StandardParticleDistribution
    particle_distribution( "test dist" );

  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ),
                       "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::SECONDARY_SPATIAL_DIMENSION),
                       "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::TERTIARY_SPATIAL_DIMENSION),
                       "Delta Distribution" );

  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ),
                       "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION),
                       "Uniform Distribution" );
  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION),
                       "Uniform Distribution" );

  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::ENERGY_DIMENSION),
                       "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::TIME_DIMENSION),
                       "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::WEIGHT_DIMENSION),
                       "Delta Distribution" );
}

//---------------------------------------------------------------------------//
// Check that the default dimension distributions are correct
FRENSIE_UNIT_TEST( StandardParticleDistribution,
                   default_dists_cylindrical_spatial_cartesian_directional )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
    spatial_coord_conversion_policy( new Utility::BasicCylindricalSpatialCoordinateConversionPolicy );

  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
    directional_coord_conversion_policy( new Utility::BasicCartesianCoordinateConversionPolicy );

  MonteCarlo::StandardParticleDistribution
    particle_distribution( "test dist",
                           spatial_coord_conversion_policy,
                           directional_coord_conversion_policy );

  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ),
                       "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::SECONDARY_SPATIAL_DIMENSION),
                       "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::TERTIARY_SPATIAL_DIMENSION),
                       "Delta Distribution" );

  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ),
                       "Uniform Distribution" );
  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION),
                       "Uniform Distribution" );
  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION),
                       "Uniform Distribution" );

  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::ENERGY_DIMENSION),
                       "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::TIME_DIMENSION),
                       "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::WEIGHT_DIMENSION),
                       "Delta Distribution" );
}

//---------------------------------------------------------------------------//
// Check that the default dimension distributions are correct
FRENSIE_UNIT_TEST( StandardParticleDistribution,
                   default_dists_cylindrical_spatial_spherical_directional )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
    spatial_coord_conversion_policy( new Utility::BasicCylindricalSpatialCoordinateConversionPolicy );

  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
    directional_coord_conversion_policy( new Utility::BasicSphericalCoordinateConversionPolicy );

  MonteCarlo::StandardParticleDistribution
    particle_distribution( "test dist",
                           spatial_coord_conversion_policy,
                           directional_coord_conversion_policy );

  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ),
                       "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::SECONDARY_SPATIAL_DIMENSION),
                       "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::TERTIARY_SPATIAL_DIMENSION),
                       "Delta Distribution" );

  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ),
                       "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION),
                       "Uniform Distribution" );
  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION),
                       "Uniform Distribution" );

  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::ENERGY_DIMENSION),
                       "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::TIME_DIMENSION),
                       "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::WEIGHT_DIMENSION),
                       "Delta Distribution" );
}

//---------------------------------------------------------------------------//
// Check that the default dimension distributions are correct
FRENSIE_UNIT_TEST( StandardParticleDistribution,
                   default_dists_spherical_spatial_cartesian_directional )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
    spatial_coord_conversion_policy( new Utility::BasicSphericalCoordinateConversionPolicy );

  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
    directional_coord_conversion_policy( new Utility::BasicCartesianCoordinateConversionPolicy );

  MonteCarlo::StandardParticleDistribution
    particle_distribution( "test dist",
                           spatial_coord_conversion_policy,
                           directional_coord_conversion_policy );

  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ),
                       "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::SECONDARY_SPATIAL_DIMENSION),
                       "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::TERTIARY_SPATIAL_DIMENSION),
                       "Delta Distribution" );

  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ),
                       "Uniform Distribution" );
  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION),
                       "Uniform Distribution" );
  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION),
                       "Uniform Distribution" );

  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::ENERGY_DIMENSION),
                       "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::TIME_DIMENSION),
                       "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::WEIGHT_DIMENSION),
                       "Delta Distribution" );
}

//---------------------------------------------------------------------------//
// Check that the default dimension distributions are correct
FRENSIE_UNIT_TEST( StandardParticleDistribution,
                   default_dists_spherical_spatial_spherical_directional )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
    spatial_coord_conversion_policy( new Utility::BasicSphericalCoordinateConversionPolicy );

  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
    directional_coord_conversion_policy( new Utility::BasicSphericalCoordinateConversionPolicy );

  MonteCarlo::StandardParticleDistribution
    particle_distribution( "test dist",
                           spatial_coord_conversion_policy,
                           directional_coord_conversion_policy );

  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ),
                       "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::SECONDARY_SPATIAL_DIMENSION),
                       "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::TERTIARY_SPATIAL_DIMENSION),
                       "Delta Distribution" );

  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ),
                       "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION),
                       "Uniform Distribution" );
  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION),
                       "Uniform Distribution" );

  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::ENERGY_DIMENSION),
                       "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::TIME_DIMENSION),
                       "Delta Distribution" );
  FRENSIE_CHECK_EQUAL( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::WEIGHT_DIMENSION),
                       "Delta Distribution" );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( StandardParticleDistribution,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_standard_particle_distribution" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::shared_ptr<const ParticleDistribution> particle_distribution =
      createSphericalSpatialSphericalDirectionalDist();

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(particle_distribution) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::shared_ptr<const ParticleDistribution> particle_distribution;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(particle_distribution) );

  iarchive.reset();

  // Set the random number generator stream
  std::vector<double> fake_stream( 7 );
  fake_stream[0] = 1.0-1e-12; // r
  fake_stream[1] = 0.0; // theta
  fake_stream[2] = 0.0; // mu
  fake_stream[3] = 0.5; // energy
  fake_stream[4] = 0.0; // theta
  fake_stream[5] = 0.0; // mu
  fake_stream[6] = 0.0; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::PhotonState photon( 0 );

  particle_distribution->sample( photon );

  FRENSIE_CHECK_SMALL( photon.getXPosition(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getYPosition(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZPosition(), -1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getXDirection(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZDirection(), -1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getSourceEnergy(), 5.0 );
  FRENSIE_CHECK_EQUAL( photon.getEnergy(), 5.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceWeight(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getWeight(), 0.5 );

  // Set the random number generator stream
  fake_stream[0] = 0.0; // r
  fake_stream[1] = 0.0; // theta
  fake_stream[2] = 0.0; // mu
  fake_stream[3] = 0.5; // energy
  fake_stream[4] = 0.0; // theta
  fake_stream[5] = 0.5; // mu
  fake_stream[6] = 0.0; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  particle_distribution->sample( photon );

  FRENSIE_CHECK_SMALL( photon.getXPosition(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getYPosition(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getZPosition(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getXDirection(), 1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getZDirection(), 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getSourceEnergy(), 5.0 );
  FRENSIE_CHECK_EQUAL( photon.getEnergy(), 5.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getTime(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceWeight(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getWeight(), 0.5 );

  // Set the random number generator stream
  fake_stream[0] = 1.0-1e-15; // r
  fake_stream[1] = 0.5; // theta
  fake_stream[2] = 0.5; // mu
  fake_stream[3] = 0.5; // energy
  fake_stream[4] = 0.75; // theta
  fake_stream[5] = 0.5; // mu
  fake_stream[6] = 0.5; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  particle_distribution->sample( photon );

  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getXPosition(), -1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getYPosition(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getZPosition(), 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getXDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getYDirection(), -1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getZDirection(), 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getSourceEnergy(), 10.0 );
  FRENSIE_CHECK_EQUAL( photon.getEnergy(), 10.0 );
  FRENSIE_CHECK_EQUAL( photon.getSourceTime(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getTime(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getSourceWeight(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getWeight(), 0.5 );

  // Set the random number generator stream
  fake_stream[0] = 1.0-1e-15; // r
  fake_stream[1] = 0.0; // theta
  fake_stream[2] = 1.0-1e-15; // mu
  fake_stream[3] = 1.0-1e-15; // energy
  fake_stream[4] = 0.0; // theta
  fake_stream[5] = 1.0-1e-15; // mu
  fake_stream[6] = 1.0-1e-15; // time

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  particle_distribution->sample( photon );

  FRENSIE_CHECK_SMALL( photon.getXPosition(), 1e-7 );
  FRENSIE_CHECK_SMALL( photon.getYPosition(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZPosition(), 1.0, 1e-12 );
  FRENSIE_CHECK_SMALL( photon.getXDirection(), 1e-7 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZDirection(), 1.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getSourceEnergy(), 20.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getEnergy(), 20.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getSourceTime(), 1.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getTime(), 1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( photon.getSourceWeight(), 0.5 );
  FRENSIE_CHECK_EQUAL( photon.getWeight(), 0.5 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstStandardParticleDistribution.cpp
//---------------------------------------------------------------------------//
