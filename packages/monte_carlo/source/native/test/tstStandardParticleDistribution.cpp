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

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "MonteCarlo_StandardParticleDistribution.hpp"
#include "MonteCarlo_IndependentPhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_FullyTabularDependentPhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_PartiallyTabularDependentPhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_SourceUnitTestHarnessExtensions.hpp"
#include "Utility_BasicCartesianCoordinateConversionPolicy.hpp"
#include "Utility_BasicSphericalCoordinateConversionPolicy.hpp"
#include "Utility_BasicCylindricalSpatialCoordinateConversionPolicy.hpp"
#include "Utility_HistogramFullyTabularTwoDDistribution.hpp"
#include "Utility_HistogramPartiallyTabularTwoDDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_DeltaDistribution.hpp"
#include "Utility_PowerDistribution.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_ExponentialDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

using namespace MonteCarlo;

//---------------------------------------------------------------------------//
// Testing Functions
//---------------------------------------------------------------------------//
void initializeCartesianSpatialDimensionDists(
         std::shared_ptr<StandardParticleDistribution>& particle_distribution )
{
  std::shared_ptr<const Utility::OneDDistribution> raw_uniform_dist_a(
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

void initializeCartesianDirectionalDimensionDists(
         std::shared_ptr<StandardParticleDistribution>& particle_distribution )
{
  std::shared_ptr<const Utility::OneDDistribution> raw_uniform_dist_a(
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

void initializeMiscDimensionDists(
         std::shared_ptr<StandardParticleDistribution>& particle_distribution )
{
  std::shared_ptr<const Utility::OneDDistribution> raw_uniform_dist_b(
                           new Utility::UniformDistribution( 0.0, 1.0, 1.0 ) );

  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    time_dimension_dist( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TIME_DIMENSION>( raw_uniform_dist_b ) );
  particle_distribution->setDimensionDistribution( time_dimension_dist );
  
  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    energy_dimension_dist;
  
  {
    // Create the fully tabular distribution
    Utility::HistogramFullyTabularTwoDDistribution::DistributionType
      distribution_data( 3 );

    // Create the secondary distribution in the first bin
    Utility::get<0>( distribution_data[0] ) = -1.0;
    Utility::get<1>( distribution_data[0] ).reset( new Utility::UniformDistribution( 1e-3, 10.0, 0.5 ) );

    
    // Create the secondary distribution in the second bin
    Utility::get<0>( distribution_data[1] ) = 0.0;
    Utility::get<1>( distribution_data[1] ).reset( new Utility::UniformDistribution( 1e-3, 20.0, 0.25 ) );

    // Create the secondary distribution in the third bin
    Utility::get<0>( distribution_data[2] ) = 1.0;
    Utility::get<1>( distribution_data[2] ) =
      Utility::get<1>( distribution_data[1] );

    std::shared_ptr<Utility::HistogramFullyTabularTwoDDistribution>
      raw_dependent_distribution( new Utility::HistogramFullyTabularTwoDDistribution( distribution_data ) );

    raw_dependent_distribution->limitToPrimaryIndepLimits();
  
    energy_dimension_dist.reset( new MonteCarlo::FullyTabularDependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION,MonteCarlo::ENERGY_DIMENSION>( raw_dependent_distribution ) );
  }
  particle_distribution->setDimensionDistribution( energy_dimension_dist );
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
                                       0,
                                       "test dist",
                                       spatial_coord_conversion_policy,
                                       directional_coord_conversion_policy ) );

  // Create the dimension distributions
  initializeCartesianSpatialDimensionDists( particle_distribution );
  initializeCartesianDirectionalDimensionDists( particle_distribution );
  initializeMiscDimensionDists( particle_distribution );

  particle_distribution->constructDimensionDistributionDependencyTree();
  
  return particle_distribution;
}

std::shared_ptr<const ParticleDistribution>
createCartesianSpatialSphericalDirectionalDist()
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
    spatial_coord_conversion_policy( new Utility::BasicCartesianCoordinateConversionPolicy );

  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
    directional_coord_conversion_policy( new Utility::BasicCartesianCoordinateConversionPolicy );
  
  std::shared_ptr<MonteCarlo::StandardParticleDistribution>
    particle_distribution( new MonteCarlo::StandardParticleDistribution(
                                       0,
                                       "test dist",
                                       spatial_coord_conversion_policy,
                                       directional_coord_conversion_policy ) );

  // Create the dimension distributions
  initializeCartesianSpatialDimensionDists( particle_distribution );
  initializeMiscDimensionDists( particle_distribution );

  particle_distribution->constructDimensionDistributionDependencyTree();
  
  return particle_distribution;
}

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the distribution id can be returned
TEUCHOS_UNIT_TEST( StandardParticleDistribution, getId )
{
  MonteCarlo::StandardParticleDistribution
    particle_distribution( 2, "test dist" );

  TEST_EQUALITY_CONST( particle_distribution.getId(), 2 );
}

//---------------------------------------------------------------------------//
// Check that the distribution name can be returned
TEUCHOS_UNIT_TEST( StandardParticleDistribution, getName )
{
  MonteCarlo::StandardParticleDistribution
    particle_distribution( 2, "test dist" );

  TEST_EQUALITY_CONST( particle_distribution.getName(), "test dist" );
}

//---------------------------------------------------------------------------//
// Check that a dimension's distribution type name can be returned
TEUCHOS_UNIT_TEST( StandardParticleDistribution,
                   getDimensionDistributionTypeName )
{
  MonteCarlo::StandardParticleDistribution
    particle_distribution( 2, "test dist" );

  std::shared_ptr<const Utility::OneDDistribution> raw_dist(
                           new Utility::UniformDistribution( 0.5, 1.5, 0.5 ) );

  std::shared_ptr<MonteCarlo::PhaseSpaceDimensionDistribution>
    energy_dimension_dist(new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::ENERGY_DIMENSION>( raw_dist ) );

  particle_distribution.setDimensionDistribution( energy_dimension_dist );

  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::ENERGY_DIMENSION ),
                       "Uniform Distribution" );
}

//---------------------------------------------------------------------------//
// Check if the distribution is spatially uniform
TEUCHOS_UNIT_TEST( StandardParticleDistribution,
                   isSpatiallyUniform_cartesian )
{
  MonteCarlo::StandardParticleDistribution
    particle_distribution( 0, "test dist" );

  std::shared_ptr<const Utility::OneDDistribution> raw_uniform_dist(
                           new Utility::UniformDistribution( 0.5, 1.5, 0.5 ) );

  std::shared_ptr<const Utility::OneDDistribution> raw_delta_dist(
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

  TEST_ASSERT( particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform Cartesian spatial distribution
  x_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_delta_dist ) );
  y_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );
  z_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );

  particle_distribution.setDimensionDistribution( x_dimension_dist );
  particle_distribution.setDimensionDistribution( y_dimension_dist );
  particle_distribution.setDimensionDistribution( z_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  TEST_ASSERT( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform Cartesian spatial distribution
  x_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );
  y_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_delta_dist ) );
  z_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );

  particle_distribution.setDimensionDistribution( x_dimension_dist );
  particle_distribution.setDimensionDistribution( y_dimension_dist );
  particle_distribution.setDimensionDistribution( z_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  TEST_ASSERT( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform Cartesian spatial distribution
  x_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );
  y_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );
  z_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_delta_dist ) );

  particle_distribution.setDimensionDistribution( x_dimension_dist );
  particle_distribution.setDimensionDistribution( y_dimension_dist );
  particle_distribution.setDimensionDistribution( z_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  TEST_ASSERT( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform Cartesian spatial distribution
  x_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_delta_dist ) );
  y_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_delta_dist ) );
  z_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );

  particle_distribution.setDimensionDistribution( x_dimension_dist );
  particle_distribution.setDimensionDistribution( y_dimension_dist );
  particle_distribution.setDimensionDistribution( z_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  TEST_ASSERT( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform Cartesian spatial distribution
  x_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_delta_dist ) );
  y_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );
  z_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_delta_dist ) );

  particle_distribution.setDimensionDistribution( x_dimension_dist );
  particle_distribution.setDimensionDistribution( y_dimension_dist );
  particle_distribution.setDimensionDistribution( z_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  TEST_ASSERT( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform Cartesian spatial distribution
  x_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );
  y_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_delta_dist ) );
  z_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_delta_dist ) );

  particle_distribution.setDimensionDistribution( x_dimension_dist );
  particle_distribution.setDimensionDistribution( y_dimension_dist );
  particle_distribution.setDimensionDistribution( z_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  TEST_ASSERT( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform Cartesian spatial distribution
  x_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_delta_dist ) );
  y_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_delta_dist ) );
  z_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_delta_dist ) );

  particle_distribution.setDimensionDistribution( x_dimension_dist );
  particle_distribution.setDimensionDistribution( y_dimension_dist );
  particle_distribution.setDimensionDistribution( z_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  TEST_ASSERT( !particle_distribution.isSpatiallyUniform() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is spatially uniform
TEUCHOS_UNIT_TEST( StandardParticleDistribution,
                   isSpatiallyUniform_cylindrical )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
    spatial_coord_conversion_policy( new Utility::BasicCylindricalSpatialCoordinateConversionPolicy );

  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
    directional_coord_conversion_policy( new Utility::BasicSphericalCoordinateConversionPolicy );
  
  MonteCarlo::StandardParticleDistribution
    particle_distribution( 0,
                           "test dist",
                           spatial_coord_conversion_policy,
                           directional_coord_conversion_policy );

  std::shared_ptr<const Utility::OneDDistribution> raw_power_dist(
                          new Utility::PowerDistribution<1>( 1.0, 0.0, 1.0 ) );

  std::shared_ptr<const Utility::OneDDistribution> raw_uniform_dist(
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

  TEST_ASSERT( particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform cylindrical spatial distribution
  particle_distribution.reset();
  
  r_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );
  theta_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );
  z_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( z_dimension_dist );

  TEST_ASSERT( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform cylindrical spatial distribution
  particle_distribution.reset();
  
  r_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_power_dist ) );
  theta_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_power_dist ) );
  z_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( z_dimension_dist );

  TEST_ASSERT( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform cylindrical spatial distribution
  particle_distribution.reset();
  
  r_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_power_dist ) );
  theta_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );
  z_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_power_dist ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( z_dimension_dist );

  TEST_ASSERT( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform cylindrical spatial distribution
  particle_distribution.reset();
  
  r_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );
  theta_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_power_dist ) );
  z_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( z_dimension_dist );

  TEST_ASSERT( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform cylindrical spatial distribution
  particle_distribution.reset();
  
  r_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );
  theta_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );
  z_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_power_dist ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( z_dimension_dist );

  TEST_ASSERT( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform cylindrical spatial distribution
  particle_distribution.reset();
  
  r_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );
  theta_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_power_dist ) );
  z_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_power_dist ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( z_dimension_dist );

  TEST_ASSERT( !particle_distribution.isSpatiallyUniform() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is spatially uniform
TEUCHOS_UNIT_TEST( StandardParticleDistribution,
                   isSpatiallyUniform_spherical )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
    spatial_coord_conversion_policy( new Utility::BasicSphericalCoordinateConversionPolicy );

  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
    directional_coord_conversion_policy( new Utility::BasicSphericalCoordinateConversionPolicy );
  
  MonteCarlo::StandardParticleDistribution
    particle_distribution( 0,
                           "test dist",
                           spatial_coord_conversion_policy,
                           directional_coord_conversion_policy );

  std::shared_ptr<const Utility::OneDDistribution> raw_power_dist(
                          new Utility::PowerDistribution<2>( 1.0, 0.0, 1.0 ) );

  std::shared_ptr<const Utility::OneDDistribution> raw_uniform_dist_a(
      new Utility::UniformDistribution( 0.0, 2*Utility::PhysicalConstants::pi, 1.0 ) );

  std::shared_ptr<const Utility::OneDDistribution> raw_uniform_dist_b(
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

  TEST_ASSERT( particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform spherical spatial distribution
  r_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_uniform_dist_a ) );
  theta_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_uniform_dist_a ) );
  mu_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_uniform_dist_b ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( mu_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  TEST_ASSERT( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform spherical spatial distribution
  r_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_power_dist ) );
  theta_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_power_dist ) );
  mu_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_uniform_dist_b ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( mu_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  TEST_ASSERT( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform spherical spatial distribution
  r_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_power_dist ) );
  theta_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_uniform_dist_a ) );
  mu_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_power_dist ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( mu_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  TEST_ASSERT( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform spherical spatial distribution
  r_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_uniform_dist_a ) );
  theta_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_power_dist ) );
  mu_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_uniform_dist_b ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( mu_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  TEST_ASSERT( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform spherical spatial distribution
  r_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_uniform_dist_a ) );
  theta_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_uniform_dist_a ) );
  mu_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_power_dist ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( mu_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  TEST_ASSERT( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform spherical spatial distribution
  r_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_power_dist ) );
  theta_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_power_dist ) );
  mu_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_power_dist ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( mu_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  TEST_ASSERT( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform spherical spatial distribution
  r_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_uniform_dist_a ) );
  theta_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_power_dist ) );
  mu_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_power_dist ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( mu_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  TEST_ASSERT( !particle_distribution.isSpatiallyUniform() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is directionally uniform (isotropic)
TEUCHOS_UNIT_TEST( StandardParticleDistribution,
                   isDirectionallyUniform_cartesian )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
    spatial_coord_conversion_policy( new Utility::BasicCartesianCoordinateConversionPolicy );

  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
    directional_coord_conversion_policy( new Utility::BasicCartesianCoordinateConversionPolicy );
  
  MonteCarlo::StandardParticleDistribution
    particle_distribution( 0,
                           "test dist",
                           spatial_coord_conversion_policy,
                           directional_coord_conversion_policy );

  std::shared_ptr<const Utility::OneDDistribution> raw_uniform_dist(
                          new Utility::UniformDistribution( -1.0, 1.0, 1.0 ) );

  std::shared_ptr<const Utility::OneDDistribution> raw_delta_dist(
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

  TEST_ASSERT( !particle_distribution.isDirectionallyUniform() );

  // Create a non-uniform Cartesian directional distribution
  u_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION>( raw_delta_dist ) );
  v_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION>( raw_uniform_dist ) );
  w_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION>( raw_uniform_dist ) );

  particle_distribution.setDimensionDistribution( u_dimension_dist );
  particle_distribution.setDimensionDistribution( v_dimension_dist );
  particle_distribution.setDimensionDistribution( w_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  TEST_ASSERT( !particle_distribution.isDirectionallyUniform() );

  // Create a non-uniform Cartesian directional distribution
  u_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION>( raw_uniform_dist ) );
  v_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION>( raw_delta_dist ) );
  w_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION>( raw_uniform_dist ) );

  particle_distribution.setDimensionDistribution( u_dimension_dist );
  particle_distribution.setDimensionDistribution( v_dimension_dist );
  particle_distribution.setDimensionDistribution( w_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  TEST_ASSERT( !particle_distribution.isDirectionallyUniform() );

  // Create a non-uniform Cartesian directional distribution
  u_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION>( raw_uniform_dist ) );
  v_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION>( raw_uniform_dist ) );
  w_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION>( raw_delta_dist ) );

  particle_distribution.setDimensionDistribution( u_dimension_dist );
  particle_distribution.setDimensionDistribution( v_dimension_dist );
  particle_distribution.setDimensionDistribution( w_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  TEST_ASSERT( !particle_distribution.isDirectionallyUniform() );

  // Create a non-uniform Cartesian directional distribution
  u_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION>( raw_delta_dist ) );
  v_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION>( raw_delta_dist ) );
  w_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION>( raw_delta_dist ) );

  particle_distribution.setDimensionDistribution( u_dimension_dist );
  particle_distribution.setDimensionDistribution( v_dimension_dist );
  particle_distribution.setDimensionDistribution( w_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  TEST_ASSERT( !particle_distribution.isDirectionallyUniform() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is directionally uniform (isotropic)
TEUCHOS_UNIT_TEST( StandardParticleDistribution,
                   isDirectionallyUniform_spherical )
{
  MonteCarlo::StandardParticleDistribution
    particle_distribution( 0, "test dist" );

  std::shared_ptr<const Utility::OneDDistribution> raw_delta_dist(
                                       new Utility::DeltaDistribution( 1.0 ) );

  std::shared_ptr<const Utility::OneDDistribution> raw_uniform_dist_a(
       new Utility::UniformDistribution( 0.0, 2*Utility::PhysicalConstants::pi, 1.0 ) );
  
  std::shared_ptr<const Utility::OneDDistribution> raw_uniform_dist_b(
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

  TEST_ASSERT( particle_distribution.isDirectionallyUniform() );

  // Create a uniform spherical directional distribution
  r_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION>( raw_uniform_dist_a ) );
  theta_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION>( raw_uniform_dist_a ) );
  mu_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION>( raw_uniform_dist_b ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( mu_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  TEST_ASSERT( particle_distribution.isDirectionallyUniform() );

  // Create a non-uniform spherical directional distribution
  r_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION>( raw_delta_dist ) );
  theta_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION>( raw_delta_dist ) );
  mu_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION>( raw_uniform_dist_b ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( mu_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  TEST_ASSERT( !particle_distribution.isDirectionallyUniform() );

  // Create a non-uniform spherical directional distribution
  r_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION>( raw_delta_dist ) );
  theta_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION>( raw_uniform_dist_a ) );
  mu_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION>( raw_delta_dist ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( mu_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  TEST_ASSERT( !particle_distribution.isDirectionallyUniform() );

  // Create a non-uniform spherical directional distribution
  r_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION>( raw_delta_dist ) );
  theta_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION>( raw_delta_dist ) );
  mu_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION>( raw_delta_dist ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( mu_dimension_dist );

  particle_distribution.constructDimensionDistributionDependencyTree();

  TEST_ASSERT( !particle_distribution.isDirectionallyUniform() );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( StandardParticleDistribution,
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

  TEST_EQUALITY_CONST( particle_distribution->evaluate( photon ), 0.0 );
  
  photon.setPosition( -1.0, -0.5, -0.5 );
  photon.setDirection( 0.0, 1.0, 0.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  TEST_EQUALITY_CONST( particle_distribution->evaluate( photon ), 0.0078125 );
  
  photon.setPosition( -0.5, -0.5, -0.5 );
  photon.setDirection( 0.0, 0.0, 1.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  TEST_EQUALITY_CONST( particle_distribution->evaluate( photon ), 0.0078125 );

  photon.setPosition( 0.0, -0.5, -0.5 );
  photon.setDirection( -1.0, 0.0, 0.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  TEST_EQUALITY_CONST( particle_distribution->evaluate( photon ), 0.00390625 );

  photon.setPosition( 0.5, -0.5, -0.5 );
  photon.setDirection( 0.0, -1.0, 0.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  TEST_EQUALITY_CONST( particle_distribution->evaluate( photon ), 0.00390625 );

  photon.setPosition( 1.0, -0.5, -0.5 );
  photon.setDirection( 0.0, 0.0, -1.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  TEST_EQUALITY_CONST( particle_distribution->evaluate( photon ), 0.00390625 );

  photon.setPosition( 1.1, -0.5, -0.5 );
  photon.setDirection( 1.0/sqrt(3.0), 1.0/sqrt(3.0), 1.0/sqrt(3.0) );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  TEST_EQUALITY_CONST( particle_distribution->evaluate( photon ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( StandardParticleDistribution,
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

  TEST_EQUALITY_CONST( particle_distribution->evaluate( photon ), 0.0 );
  
  photon.setPosition( -1.0, -0.5, -0.5 );
  photon.setDirection( 0.0, 1.0, 0.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  TEST_EQUALITY_CONST( particle_distribution->evaluate( photon ), 0.0625 );
  
  photon.setPosition( -0.5, -0.5, -0.5 );
  photon.setDirection( 0.0, 0.0, 1.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  TEST_EQUALITY_CONST( particle_distribution->evaluate( photon ), 0.0625 );

  photon.setPosition( 0.0, -0.5, -0.5 );
  photon.setDirection( -1.0, 0.0, 0.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  TEST_EQUALITY_CONST( particle_distribution->evaluate( photon ), 0.03125 );

  photon.setPosition( 0.5, -0.5, -0.5 );
  photon.setDirection( 0.0, -1.0, 0.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  TEST_EQUALITY_CONST( particle_distribution->evaluate( photon ), 0.03125 );

  photon.setPosition( 1.0, -0.5, -0.5 );
  photon.setDirection( 0.0, 0.0, -1.0 );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  TEST_EQUALITY_CONST( particle_distribution->evaluate( photon ), 0.03125 );

  photon.setPosition( 1.1, -0.5, -0.5 );
  photon.setDirection( 1.0/sqrt(3.0), 1.0/sqrt(3.0), 1.0/sqrt(3.0) );
  photon.setEnergy( 1.0 );
  photon.setTime( 1.0 );
  photon.setWeight( 1.0 );

  TEST_EQUALITY_CONST( particle_distribution->evaluate( photon ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( StandardParticleDistribution,
                   evaluate_cylindrical_spatial_cartesian_directional )
{
  
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( StandardParticleDistribution,
                   evaluate_cylindrical_spatial_spherical_directional )
{
  
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( StandardParticleDistribution,
                   evaluate_spherical_spatial_cartesian_directional )
{
  
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( StandardParticleDistribution,
                   evaluate_spherical_spatial_spherical_directional )
{
  
}

//---------------------------------------------------------------------------//
// Check that the default dimension distributions are correct
TEUCHOS_UNIT_TEST( StandardParticleDistribution,
                   default_dists_cartesian_spatial_cartesian_directional )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
    spatial_coord_conversion_policy( new Utility::BasicCartesianCoordinateConversionPolicy );

  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
    directional_coord_conversion_policy( new Utility::BasicCartesianCoordinateConversionPolicy );
  
  MonteCarlo::StandardParticleDistribution
    particle_distribution( 0,
                           "test dist",
                           spatial_coord_conversion_policy,
                           directional_coord_conversion_policy );

  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ),
                       "Delta Distribution" );
  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::SECONDARY_SPATIAL_DIMENSION),
                       "Delta Distribution" );
  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::TERTIARY_SPATIAL_DIMENSION),
                       "Delta Distribution" );
  
  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ),
                       "Uniform Distribution" );
  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION),
                       "Uniform Distribution" );
  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION),
                       "Uniform Distribution" );
  
  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::ENERGY_DIMENSION),
                       "Delta Distribution" );
  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::TIME_DIMENSION),
                       "Delta Distribution" );
  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::WEIGHT_DIMENSION),
                       "Delta Distribution" );
}

//---------------------------------------------------------------------------//
// CHeck that the default dimension distributions are correct
TEUCHOS_UNIT_TEST( StandardParticleDistribution,
                   default_dists_cartesian_spatial_spherical_directional )
{
  MonteCarlo::StandardParticleDistribution
    particle_distribution( 0, "test dist" );

  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ),
                       "Delta Distribution" );
  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::SECONDARY_SPATIAL_DIMENSION),
                       "Delta Distribution" );
  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::TERTIARY_SPATIAL_DIMENSION),
                       "Delta Distribution" );

  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ),
                       "Delta Distribution" );
  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION),
                       "Uniform Distribution" );
  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION),
                       "Uniform Distribution" );

  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::ENERGY_DIMENSION),
                       "Delta Distribution" );
  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::TIME_DIMENSION),
                       "Delta Distribution" );
  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::WEIGHT_DIMENSION),
                       "Delta Distribution" );
}

//---------------------------------------------------------------------------//
// Check that the default dimension distributions are correct
TEUCHOS_UNIT_TEST( StandardParticleDistribution,
                   default_dists_cylindrical_spatial_cartesian_directional )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
    spatial_coord_conversion_policy( new Utility::BasicCylindricalSpatialCoordinateConversionPolicy );

  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
    directional_coord_conversion_policy( new Utility::BasicCartesianCoordinateConversionPolicy );
  
  MonteCarlo::StandardParticleDistribution
    particle_distribution( 0,
                           "test dist",
                           spatial_coord_conversion_policy,
                           directional_coord_conversion_policy );

  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ),
                       "Delta Distribution" );
  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::SECONDARY_SPATIAL_DIMENSION),
                       "Delta Distribution" );
  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::TERTIARY_SPATIAL_DIMENSION),
                       "Delta Distribution" );
  
  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ),
                       "Uniform Distribution" );
  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION),
                       "Uniform Distribution" );
  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION),
                       "Uniform Distribution" );

  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::ENERGY_DIMENSION),
                       "Delta Distribution" );
  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::TIME_DIMENSION),
                       "Delta Distribution" );
  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::WEIGHT_DIMENSION),
                       "Delta Distribution" );
}

//---------------------------------------------------------------------------//
// Check that the default dimension distributions are correct
TEUCHOS_UNIT_TEST( StandardParticleDistribution,
                   default_dists_cylindrical_spatial_spherical_directional )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
    spatial_coord_conversion_policy( new Utility::BasicCylindricalSpatialCoordinateConversionPolicy );

  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
    directional_coord_conversion_policy( new Utility::BasicSphericalCoordinateConversionPolicy );
  
  MonteCarlo::StandardParticleDistribution
    particle_distribution( 0,
                           "test dist",
                           spatial_coord_conversion_policy,
                           directional_coord_conversion_policy );

  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ),
                       "Delta Distribution" );
  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::SECONDARY_SPATIAL_DIMENSION),
                       "Delta Distribution" );
  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::TERTIARY_SPATIAL_DIMENSION),
                       "Delta Distribution" );
  
  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ),
                       "Delta Distribution" );
  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION),
                       "Uniform Distribution" );
  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION),
                       "Uniform Distribution" );

  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::ENERGY_DIMENSION),
                       "Delta Distribution" );
  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::TIME_DIMENSION),
                       "Delta Distribution" );
  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::WEIGHT_DIMENSION),
                       "Delta Distribution" );
}

//---------------------------------------------------------------------------//
// Check that the default dimension distributions are correct
TEUCHOS_UNIT_TEST( StandardParticleDistribution,
                   default_dists_spherical_spatial_cartesian_directional )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
    spatial_coord_conversion_policy( new Utility::BasicSphericalCoordinateConversionPolicy );

  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
    directional_coord_conversion_policy( new Utility::BasicCartesianCoordinateConversionPolicy );
  
  MonteCarlo::StandardParticleDistribution
    particle_distribution( 0,
                           "test dist",
                           spatial_coord_conversion_policy,
                           directional_coord_conversion_policy );

  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ),
                       "Delta Distribution" );
  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::SECONDARY_SPATIAL_DIMENSION),
                       "Delta Distribution" );
  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::TERTIARY_SPATIAL_DIMENSION),
                       "Delta Distribution" );
  
  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ),
                       "Uniform Distribution" );
  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION),
                       "Uniform Distribution" );
  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION),
                       "Uniform Distribution" );

  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::ENERGY_DIMENSION),
                       "Delta Distribution" );
  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::TIME_DIMENSION),
                       "Delta Distribution" );
  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::WEIGHT_DIMENSION),
                       "Delta Distribution" );
}

//---------------------------------------------------------------------------//
// Check that the default dimension distributions are correct
TEUCHOS_UNIT_TEST( StandardParticleDistribution,
                   default_dists_spherical_spatial_spherical_directional )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
    spatial_coord_conversion_policy( new Utility::BasicSphericalCoordinateConversionPolicy );

  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
    directional_coord_conversion_policy( new Utility::BasicSphericalCoordinateConversionPolicy );
  
  MonteCarlo::StandardParticleDistribution
    particle_distribution( 0,
                           "test dist",
                           spatial_coord_conversion_policy,
                           directional_coord_conversion_policy );

  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ),
                       "Delta Distribution" );
  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::SECONDARY_SPATIAL_DIMENSION),
                       "Delta Distribution" );
  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::TERTIARY_SPATIAL_DIMENSION),
                       "Delta Distribution" );
  
  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ),
                       "Delta Distribution" );
  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION),
                       "Uniform Distribution" );
  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION),
                       "Uniform Distribution" );

  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::ENERGY_DIMENSION),
                       "Delta Distribution" );
  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::TIME_DIMENSION),
                       "Delta Distribution" );
  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::WEIGHT_DIMENSION),
                       "Delta Distribution" );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstStandardParticleDistribution.cpp
//---------------------------------------------------------------------------//
