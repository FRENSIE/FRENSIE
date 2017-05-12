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
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<const ParticleDistribution> particle_distribution;

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

  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
    spatial_coord_conversion_policy( new Utility::BasicCartesianCoordinateConversionPolicy );

  particle_distribution.setSpatialCoordinateConversionPolicy(
                                             spatial_coord_conversion_policy );

  TEST_ASSERT( particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform Cartesian spatial distribution
  particle_distribution.reset();
  
  x_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_delta_dist ) );
  y_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );
  z_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );

  particle_distribution.setDimensionDistribution( x_dimension_dist );
  particle_distribution.setDimensionDistribution( y_dimension_dist );
  particle_distribution.setDimensionDistribution( z_dimension_dist );

  TEST_ASSERT( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform Cartesian spatial distribution
  particle_distribution.reset();
  
  x_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );
  y_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_delta_dist ) );
  z_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );

  particle_distribution.setDimensionDistribution( x_dimension_dist );
  particle_distribution.setDimensionDistribution( y_dimension_dist );
  particle_distribution.setDimensionDistribution( z_dimension_dist );

  TEST_ASSERT( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform Cartesian spatial distribution
  particle_distribution.reset();
  
  x_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );
  y_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );
  z_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_delta_dist ) );

  particle_distribution.setDimensionDistribution( x_dimension_dist );
  particle_distribution.setDimensionDistribution( y_dimension_dist );
  particle_distribution.setDimensionDistribution( z_dimension_dist );

  TEST_ASSERT( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform Cartesian spatial distribution
  particle_distribution.reset();
  
  x_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_delta_dist ) );
  y_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_delta_dist ) );
  z_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );

  particle_distribution.setDimensionDistribution( x_dimension_dist );
  particle_distribution.setDimensionDistribution( y_dimension_dist );
  particle_distribution.setDimensionDistribution( z_dimension_dist );

  TEST_ASSERT( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform Cartesian spatial distribution
  particle_distribution.reset();
  
  x_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_delta_dist ) );
  y_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );
  z_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_delta_dist ) );

  particle_distribution.setDimensionDistribution( x_dimension_dist );
  particle_distribution.setDimensionDistribution( y_dimension_dist );
  particle_distribution.setDimensionDistribution( z_dimension_dist );

  TEST_ASSERT( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform Cartesian spatial distribution
  particle_distribution.reset();
  
  x_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_uniform_dist ) );
  y_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_delta_dist ) );
  z_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_delta_dist ) );

  particle_distribution.setDimensionDistribution( x_dimension_dist );
  particle_distribution.setDimensionDistribution( y_dimension_dist );
  particle_distribution.setDimensionDistribution( z_dimension_dist );

  TEST_ASSERT( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform Cartesian spatial distribution
  particle_distribution.reset();
  
  x_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_delta_dist ) );
  y_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_delta_dist ) );
  z_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_delta_dist ) );

  particle_distribution.setDimensionDistribution( x_dimension_dist );
  particle_distribution.setDimensionDistribution( y_dimension_dist );
  particle_distribution.setDimensionDistribution( z_dimension_dist );

  TEST_ASSERT( !particle_distribution.isSpatiallyUniform() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is spatially uniform
TEUCHOS_UNIT_TEST( StandardParticleDistribution,
                   isSpatiallyUniform_cylindrical )
{
  MonteCarlo::StandardParticleDistribution
    particle_distribution( 0, "test dist" );

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

  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
    spatial_coord_conversion_policy( new Utility::BasicCylindricalSpatialCoordinateConversionPolicy );

  particle_distribution.setSpatialCoordinateConversionPolicy(
                                             spatial_coord_conversion_policy );

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
  MonteCarlo::StandardParticleDistribution
    particle_distribution( 0, "test dist" );

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

  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
    spatial_coord_conversion_policy( new Utility::BasicSphericalCoordinateConversionPolicy );

  particle_distribution.setSpatialCoordinateConversionPolicy(
                                             spatial_coord_conversion_policy );

  TEST_ASSERT( particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform spherical spatial distribution
  particle_distribution.reset();
  
  r_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_uniform_dist_a ) );
  theta_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_uniform_dist_a ) );
  mu_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_uniform_dist_b ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( mu_dimension_dist );

  TEST_ASSERT( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform spherical spatial distribution
  particle_distribution.reset();
  
  r_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_power_dist ) );
  theta_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_power_dist ) );
  mu_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_uniform_dist_b ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( mu_dimension_dist );

  TEST_ASSERT( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform spherical spatial distribution
  particle_distribution.reset();
  
  r_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_power_dist ) );
  theta_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_uniform_dist_a ) );
  mu_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_power_dist ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( mu_dimension_dist );

  TEST_ASSERT( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform spherical spatial distribution
  particle_distribution.reset();
  
  r_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_uniform_dist_a ) );
  theta_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_power_dist ) );
  mu_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_uniform_dist_b ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( mu_dimension_dist );

  TEST_ASSERT( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform spherical spatial distribution
  particle_distribution.reset();
  
  r_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_uniform_dist_a ) );
  theta_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_uniform_dist_a ) );
  mu_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_power_dist ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( mu_dimension_dist );

  TEST_ASSERT( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform spherical spatial distribution
  particle_distribution.reset();
  
  r_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_power_dist ) );
  theta_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_power_dist ) );
  mu_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_power_dist ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( mu_dimension_dist );

  TEST_ASSERT( !particle_distribution.isSpatiallyUniform() );

  // Create a non-uniform spherical spatial distribution
  particle_distribution.reset();
  
  r_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_uniform_dist_a ) );
  theta_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_power_dist ) );
  mu_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_SPATIAL_DIMENSION>( raw_power_dist ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( mu_dimension_dist );

  TEST_ASSERT( !particle_distribution.isSpatiallyUniform() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is directionally uniform (isotropic)
TEUCHOS_UNIT_TEST( StandardParticleDistribution,
                   isDirectionallyUniform_cartesian )
{
  MonteCarlo::StandardParticleDistribution
    particle_distribution( 0, "test dist" );

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

  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
    directional_coord_conversion_policy( new Utility::BasicCartesianCoordinateConversionPolicy );

  particle_distribution.setDirectionalCoordinateConversionPolicy(
                                         directional_coord_conversion_policy );

  TEST_ASSERT( !particle_distribution.isDirectionallyUniform() );

  // Create a non-uniform Cartesian directional distribution
  particle_distribution.reset();
  
  u_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION>( raw_delta_dist ) );
  v_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION>( raw_uniform_dist ) );
  w_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION>( raw_uniform_dist ) );

  particle_distribution.setDimensionDistribution( u_dimension_dist );
  particle_distribution.setDimensionDistribution( v_dimension_dist );
  particle_distribution.setDimensionDistribution( w_dimension_dist );

  TEST_ASSERT( !particle_distribution.isDirectionallyUniform() );

  // Create a non-uniform Cartesian directional distribution
  particle_distribution.reset();
  
  u_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION>( raw_uniform_dist ) );
  v_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION>( raw_delta_dist ) );
  w_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION>( raw_uniform_dist ) );

  particle_distribution.setDimensionDistribution( u_dimension_dist );
  particle_distribution.setDimensionDistribution( v_dimension_dist );
  particle_distribution.setDimensionDistribution( w_dimension_dist );

  TEST_ASSERT( !particle_distribution.isDirectionallyUniform() );

  // Create a non-uniform Cartesian directional distribution
  particle_distribution.reset();
  
  u_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION>( raw_uniform_dist ) );
  v_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION>( raw_uniform_dist ) );
  w_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION>( raw_delta_dist ) );

  particle_distribution.setDimensionDistribution( u_dimension_dist );
  particle_distribution.setDimensionDistribution( v_dimension_dist );
  particle_distribution.setDimensionDistribution( w_dimension_dist );

  TEST_ASSERT( !particle_distribution.isDirectionallyUniform() );

  // Create a non-uniform Cartesian directional distribution
  particle_distribution.reset();
  
  u_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION>( raw_delta_dist ) );
  v_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION>( raw_delta_dist ) );
  w_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION>( raw_delta_dist ) );

  particle_distribution.setDimensionDistribution( u_dimension_dist );
  particle_distribution.setDimensionDistribution( v_dimension_dist );
  particle_distribution.setDimensionDistribution( w_dimension_dist );

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

  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
    directional_coord_conversion_policy( new Utility::BasicSphericalCoordinateConversionPolicy );

  particle_distribution.setDirectionalCoordinateConversionPolicy(
                                         directional_coord_conversion_policy );

  TEST_ASSERT( particle_distribution.isDirectionallyUniform() );

  // Create a uniform spherical directional distribution
  particle_distribution.reset();
  
  r_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION>( raw_uniform_dist_a ) );
  theta_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION>( raw_uniform_dist_a ) );
  mu_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION>( raw_uniform_dist_b ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( mu_dimension_dist );

  TEST_ASSERT( particle_distribution.isDirectionallyUniform() );

  // Create a non-uniform spherical directional distribution
  particle_distribution.reset();
  
  r_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION>( raw_delta_dist ) );
  theta_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION>( raw_delta_dist ) );
  mu_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION>( raw_uniform_dist_b ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( mu_dimension_dist );

  TEST_ASSERT( !particle_distribution.isDirectionallyUniform() );

  // Create a non-uniform spherical directional distribution
  particle_distribution.reset();
  
  r_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION>( raw_delta_dist ) );
  theta_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION>( raw_uniform_dist_a ) );
  mu_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION>( raw_delta_dist ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( mu_dimension_dist );

  TEST_ASSERT( !particle_distribution.isDirectionallyUniform() );

  // Create a non-uniform spherical directional distribution
  particle_distribution.reset();
  
  r_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION>( raw_delta_dist ) );
  theta_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION>( raw_delta_dist ) );
  mu_dimension_dist.reset( new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION>( raw_delta_dist ) );

  particle_distribution.setDimensionDistribution( r_dimension_dist );
  particle_distribution.setDimensionDistribution( theta_dimension_dist );
  particle_distribution.setDimensionDistribution( mu_dimension_dist );

  TEST_ASSERT( !particle_distribution.isDirectionallyUniform() );
}

//---------------------------------------------------------------------------//
// Check that the default dimension distributions are correct
TEUCHOS_UNIT_TEST( StandardParticleDistribution,
                   default_dists_cartesian_spatial_cartesian_directional )
{
  MonteCarlo::StandardParticleDistribution
    particle_distribution( 0, "test dist" );
  
  particle_distribution.constructDimensionDistributionDependencyTree();

  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::PRIMARY_SPATIAL_DIMENSION ),
                       "Delta Distribution" );
  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::SECONDARY_SPATIAL_DIMENSION),
                       "Delta Distribution" );
  TEST_EQUALITY_CONST( particle_distribution.getDimensionDistributionTypeName( MonteCarlo::TERTIARY_SPATIAL_DIMENSION),
                       "Delta Distribution" );
}

//---------------------------------------------------------------------------//
// CHeck that the default dimension distributions are correct
TEUCHOS_UNIT_TEST( StandardParticleDistribution,
                   default_dists_cartesian_spatial_spherical_directional )
{
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
    spatial_coord_conversion_policy( new Utility::BasicCartesianCoordinateConversionPolicy );

  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
    directional_coord_conversion_policy( new Utility::BasicCartesianCoordinateConversionPolicy );
}

//---------------------------------------------------------------------------//
// Check that the default dimension distributions are correct
TEUCHOS_UNIT_TEST( StandardParticleDistribution,
                   default_dists_cylindrical_spatial_cartesian_directional )
{
  
}

//---------------------------------------------------------------------------//
// Check that the default dimension distributions are correct
TEUCHOS_UNIT_TEST( StandardParticleDistribution,
                   default_dists_cylindrical_spatial_spherical_directional )
{
  
}

//---------------------------------------------------------------------------//
// Check that the default dimension distributions are correct
TEUCHOS_UNIT_TEST( StandardParticleDistribution,
                   default_dists_spherical_spatial_cartesian_directional )
{
  
}

//---------------------------------------------------------------------------//
// Check that the default dimension distributions are correct
TEUCHOS_UNIT_TEST( StandardParticleDistribution,
                   default_dists_spherical_spatial_spherical_directional )
{
  
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // MonteCarlo::StandardParticleDistribution::DimensionDistributionMap
  //   dimension_distributions;

  // MonteCarlo::StandardParticleDistribution::DimensionSet indep_dimensions;
  
  // // Create the primary spatial dimension distribution
  // {
  //   std::shared_ptr<const Utility::OneDDistribution> raw_distribution(
  //                         new Utility::UniformDistribution( -1.0, 1.0, 1.0 ) );

  //   dimension_distribution[MonteCarlo::PRIMARY_SPATIAL_DIMENSION].reset(
  //     new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::PRIMARY_SPATIAL_DIMENSION>( raw_distribution ) );
  // }

  // // Create the secondary spatial dimension distribution
  // {
  //   std::shared_ptr<const Utility::OneDDistribution> raw_distribution(
  //                         new Utility::UniformDistribution( -2.0, 2.0, 1.0 ) );

  //   dimension_distribution[MonteCarlo::SECONDARY_SPATIAL_DIMENSION].reset(
  //      new MonteCarlo::IndependentPhaseSpaceDimensionDistribution<MonteCarlo::SECONDARY_SPATIAL_DIMENSION>( raw_distribution ) );  
  // }
  
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstStandardParticleDistribution.cpp
//---------------------------------------------------------------------------//
