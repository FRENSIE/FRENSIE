//---------------------------------------------------------------------------//
//!
//! \file   tstPhaseSpaceResponseFunction.cpp
//! \author Alex Robinson
//! \brief  Response function unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <limits>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhaseSpaceResponseFunction.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Utility_SphericalSpatialDistribution.hpp"
#include "Utility_CylindricalSpatialDistribution.hpp"
#include "Utility_CartesianSpatialDistribution.hpp"
#include "Utility_SphericalDirectionalDistribution.hpp"
#include "Utility_PowerDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_DeltaDistribution.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_NormalDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"

std::shared_ptr<MonteCarlo::ResponseFunction> response_function;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Initialize the time and energy distributions
void initializeEnergyAndTimeDists( 
	       std::shared_ptr<Utility::OneDDistribution>& energy_distribution,
	       std::shared_ptr<Utility::OneDDistribution>& time_distribution )
{
  energy_distribution.reset( new Utility::UniformDistribution( 
				       0.0, 
				       std::numeric_limits<double>::max(),
				       1.0 ) );
  time_distribution.reset( new Utility::UniformDistribution( 
				       0.0, 
				       std::numeric_limits<double>::max(),
				       1.0 ) );
}

// Initialize the directional distribution
void initializeDirectionalDistribution(
  std::shared_ptr<Utility::DirectionalDistribution>& directional_distribution )
{
  // Uniform distribution in theta dimension
  std::shared_ptr<Utility::OneDDistribution>
    theta_distribution( new Utility::UniformDistribution( 
					      0.0,
					      2*Utility::PhysicalConstants::pi,
					      1.0 ) );
  // Uniform distribution in mu dimension
  std::shared_ptr<Utility::OneDDistribution>
    mu_distribution( new Utility::UniformDistribution( -1.0, 1.0, 1.0 ) );
  
  directional_distribution.reset( new Utility::SphericalDirectionalDistribution( 
							   theta_distribution,
							   mu_distribution ) );
}

// Initialize a cartesian response function
void initializeCartesianResponseFunction( const bool uniform )
{
  std::shared_ptr<Utility::OneDDistribution> x_distribution, y_distribution,
    z_distribution;

  if( uniform )
  {
    x_distribution.reset( new Utility::UniformDistribution( 
					   -std::numeric_limits<double>::max(),
					   std::numeric_limits<double>::max(),
					   1.0 ) );
    y_distribution = x_distribution;
    z_distribution = x_distribution;
  }
  else
  {
    x_distribution.reset( new Utility::NormalDistribution );
    y_distribution = x_distribution;
    z_distribution = x_distribution;
  }

  std::shared_ptr<Utility::SpatialDistribution>
    spatial_distribution( new Utility::CartesianSpatialDistribution( 
							    x_distribution,
							    y_distribution,
							    z_distribution ) );

  std::shared_ptr<Utility::DirectionalDistribution> directional_distribution;

  initializeDirectionalDistribution( directional_distribution );

  std::shared_ptr<Utility::OneDDistribution> energy_distribution, 
    time_distribution;

  initializeEnergyAndTimeDists( energy_distribution, time_distribution );

  response_function.reset( new MonteCarlo::PhaseSpaceResponseFunction(
						      0,
						      "cartesian_response",
						      spatial_distribution,
						      directional_distribution,
						      energy_distribution,
						      time_distribution ) );
}

// Initialize a cylindrical response function
void initializeCylindricalResponseFunction( const bool uniform )
{
  // Uniform distribution in theta dimension
  std::shared_ptr<Utility::OneDDistribution>
    theta_distribution( new Utility::UniformDistribution( 
					      0.0,
					      2*Utility::PhysicalConstants::pi,
					      1.0 ) );
  // Uniform distribution in mu dimension
  std::shared_ptr<Utility::OneDDistribution>
    axis_distribution( new Utility::UniformDistribution( 0.0, 10.0, 1.0 ) );
  
  std::shared_ptr<Utility::OneDDistribution> r_distribution;
  
  if( uniform )
    r_distribution.reset( new Utility::PowerDistribution<1u>( 
				   1.0, 
				   0.0, 
				   std::numeric_limits<double>::max() ) );
  else
  {
    r_distribution.reset( new Utility::UniformDistribution( 
				       0.0, 
				       std::numeric_limits<double>::max(),
				       1.0 ) );
  }

  std::shared_ptr<Utility::SpatialDistribution>
    spatial_distribution( new Utility::CylindricalSpatialDistribution( 
							 r_distribution,
							 theta_distribution,
							 axis_distribution,
							 0.0,
							 0.0,
							 0.0 ) );

  std::shared_ptr<Utility::DirectionalDistribution> directional_distribution;

  initializeDirectionalDistribution( directional_distribution );

  std::shared_ptr<Utility::OneDDistribution> energy_distribution, 
    time_distribution;

  initializeEnergyAndTimeDists( energy_distribution, time_distribution );

  response_function.reset( new MonteCarlo::PhaseSpaceResponseFunction(
						      1,
						      "cylindrical_response",
						      spatial_distribution,
						      directional_distribution,
						      energy_distribution,
						      time_distribution ) );
}

// Initialize a spherical response function
void initializeSphericalResponseFunction( const bool uniform )
{
  // Uniform distribution in theta dimension
  std::shared_ptr<Utility::OneDDistribution>
    theta_distribution( new Utility::UniformDistribution( 
					      0.0,
					      2*Utility::PhysicalConstants::pi,
					      1.0 ) );
  // Uniform distribution in mu dimension
  std::shared_ptr<Utility::OneDDistribution>
    mu_distribution( new Utility::UniformDistribution( -1.0, 1.0, 1.0 ) );

  std::shared_ptr<Utility::OneDDistribution> r_distribution;
  
  if( uniform )
    r_distribution.reset( new Utility::PowerDistribution<2u>( 
					1.0, 
					0.0, 
				        std::numeric_limits<double>::max() ) );
  else
  {
    r_distribution.reset( new Utility::UniformDistribution( 
					    0.0, 
					    std::numeric_limits<double>::max(),
					    1.0 ) );
  }

  std::shared_ptr<Utility::SpatialDistribution>
    spatial_distribution( new Utility::SphericalSpatialDistribution( 
							   r_distribution,
							   theta_distribution,
							   mu_distribution,
							   0.0,
							   0.0,
							   0.0 ) );

  std::shared_ptr<Utility::DirectionalDistribution> directional_distribution;

  initializeDirectionalDistribution( directional_distribution );

  std::shared_ptr<Utility::OneDDistribution> energy_distribution, 
    time_distribution;

  initializeEnergyAndTimeDists( energy_distribution, time_distribution );

  response_function.reset( new MonteCarlo::PhaseSpaceResponseFunction(
						      2,
						      "spherical_response",
						      spatial_distribution,
						      directional_distribution,
						      energy_distribution,
						      time_distribution ) );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the name of the response function can be returned
TEUCHOS_UNIT_TEST( PhaseSpaceResponseFunction, getName )
{
  initializeCartesianResponseFunction( true );

  TEST_EQUALITY( response_function->getName(), "cartesian_response" );

  initializeCylindricalResponseFunction( true );

  TEST_EQUALITY( response_function->getName(), "cylindrical_response" );

  initializeSphericalResponseFunction( true );
  
  TEST_EQUALITY( response_function->getName(), "spherical_response" );
}

//---------------------------------------------------------------------------//
// Check that the response function id can be returned
TEUCHOS_UNIT_TEST( PhaseSpaceResponseFunction, getId )
{
  initializeCartesianResponseFunction( true );

  TEST_EQUALITY( response_function->getId(), 0 );

  initializeCylindricalResponseFunction( true );

  TEST_EQUALITY( response_function->getId(), 1 );

  initializeSphericalResponseFunction( true );
  
  TEST_EQUALITY( response_function->getId(), 2 );
}

//---------------------------------------------------------------------------//
// Check that the response function can be evaluated
TEUCHOS_UNIT_TEST( PhaseSpaceResponseFunction, evaluate )
{
  double position[3] = {0.0, 0.0, 0.0};
  double direction[3] = {1.0, 0.0, 0.0};
  
  MonteCarlo::PhotonState particle( 0ull );
  particle.setPosition( position );
  particle.setDirection( direction );
  particle.setEnergy( 1.0 );
  particle.setTime( 0.0 );
  particle.setWeight( 1.0 );
  
  initializeCartesianResponseFunction( true );

  TEST_EQUALITY_CONST( response_function->evaluate( particle ), 1.0 );

  initializeCylindricalResponseFunction( true );

  TEST_EQUALITY_CONST( response_function->evaluate( particle ), 1.0 );

  initializeSphericalResponseFunction( true );

  TEST_EQUALITY_CONST( response_function->evaluate( particle ), 1.0 );

  initializeCartesianResponseFunction( false );
  
  TEST_FLOATING_EQUALITY( response_function->evaluate( particle ),
			  1.0,
			  1e-15 );
  
  initializeCylindricalResponseFunction( false );

  TEST_EQUALITY_CONST( response_function->evaluate( particle ),
		       1/std::numeric_limits<double>::min() );

  initializeSphericalResponseFunction( false );

  TEST_EQUALITY_CONST( response_function->evaluate( particle ),
		       1/std::numeric_limits<double>::min() );
}

//---------------------------------------------------------------------------//
// Check if the response function is spatially uniform
TEUCHOS_UNIT_TEST( PhaseSpaceResponseFunction, isSpatiallyUniform )
{
  initializeCartesianResponseFunction( true );
  
  TEST_ASSERT( response_function->isSpatiallyUniform() );

  initializeCartesianResponseFunction( false );
  
  TEST_ASSERT( !response_function->isSpatiallyUniform() );

  initializeCylindricalResponseFunction( true );

  TEST_ASSERT( response_function->isSpatiallyUniform() );

  initializeCylindricalResponseFunction( false );

  TEST_ASSERT( !response_function->isSpatiallyUniform() );

  initializeSphericalResponseFunction( true );

  TEST_ASSERT( response_function->isSpatiallyUniform() );

  initializeSphericalResponseFunction( false );

  TEST_ASSERT( !response_function->isSpatiallyUniform() );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
