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

// FACEMC Includes
#include "PhaseSpaceResponseFunction.hpp"
#include "SphericalSpatialDistribution.hpp"
#include "CylindricalSpatialDistribution.hpp"
#include "CartesianSpatialDistribution.hpp"
#include "DirectionalDistribution.hpp"
#include "PowerDistribution.hpp"
#include "UniformDistribution.hpp"
#include "DeltaDistribution.hpp"
#include "HistogramDistribution.hpp"
#include "NormalDistribution.hpp"
#include "PhysicalConstants.hpp"

Teuchos::RCP<FACEMC::ResponseFunction> response_function;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Initialize the time and energy distributions
void initializeEnergyAndTimeDists( 
		   Teuchos::RCP<FACEMC::OneDDistribution>& energy_distribution,
		   Teuchos::RCP<FACEMC::OneDDistribution>& time_distribution )
{
  energy_distribution.reset( new FACEMC::UniformDistribution( 
				       0.0, 
				       std::numeric_limits<double>::max(),
				       1.0 ) );
  time_distribution.reset( new FACEMC::UniformDistribution( 
				       0.0, 
				       std::numeric_limits<double>::max(),
				       1.0 ) );
}

// Initialize the directional distribution
void initializeDirectionalDistribution(
      Teuchos::RCP<FACEMC::DirectionalDistribution>& directional_distribution )
{
  // Uniform distribution in theta dimension
  Teuchos::RCP<FACEMC::OneDDistribution>
    theta_distribution( new FACEMC::UniformDistribution( 
					       0.0,
					       2*FACEMC::PhysicalConstants::pi,
					       1.0 ) );
  // Uniform distribution in mu dimension
  Teuchos::RCP<FACEMC::OneDDistribution>
    mu_distribution( new FACEMC::UniformDistribution( -1.0, 1.0, 1.0 ) );
  
  directional_distribution.reset( new FACEMC::DirectionalDistribution( 
							   theta_distribution,
							   mu_distribution ) );
}

// Initialize a cartesian response function
void initializeCartesianResponseFunction( const bool uniform )
{
  Teuchos::RCP<FACEMC::OneDDistribution> x_distribution, y_distribution,
    z_distribution;

  if( uniform )
  {
    x_distribution.reset( new FACEMC::UniformDistribution( 
					   -std::numeric_limits<double>::max(),
					   std::numeric_limits<double>::max(),
					   1.0 ) );
    y_distribution = x_distribution;
    z_distribution = x_distribution;
  }
  else
  {
    x_distribution.reset( new FACEMC::NormalDistribution );
    y_distribution = x_distribution;
    z_distribution = x_distribution;
  }

  Teuchos::RCP<FACEMC::SpatialDistribution>
    spatial_distribution( new FACEMC::CartesianSpatialDistribution( 
							    x_distribution,
							    y_distribution,
							    z_distribution ) );

  Teuchos::RCP<FACEMC::DirectionalDistribution> directional_distribution;

  initializeDirectionalDistribution( directional_distribution );

  Teuchos::RCP<FACEMC::OneDDistribution> energy_distribution, 
    time_distribution;

  initializeEnergyAndTimeDists( energy_distribution, time_distribution );

  response_function.reset( new FACEMC::PhaseSpaceResponseFunction(
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
  Teuchos::RCP<FACEMC::OneDDistribution>
    theta_distribution( new FACEMC::UniformDistribution( 
					       0.0,
					       2*FACEMC::PhysicalConstants::pi,
					       1.0 ) );
  // Uniform distribution in mu dimension
  Teuchos::RCP<FACEMC::OneDDistribution>
    axis_distribution( new FACEMC::UniformDistribution( 0.0, 10.0, 1.0 ) );
  
  Teuchos::RCP<FACEMC::OneDDistribution> r_distribution;
  
  if( uniform )
    r_distribution.reset( new FACEMC::PowerDistribution<1u>( 
				   1.0, 
				   0.0, 
				   std::numeric_limits<double>::max() ) );
  else
  {
    r_distribution.reset( new FACEMC::UniformDistribution( 
				       0.0, 
				       std::numeric_limits<double>::max(),
				       1.0 ) );
  }

  Teuchos::RCP<FACEMC::SpatialDistribution>
    spatial_distribution( new FACEMC::CylindricalSpatialDistribution( 
							 r_distribution,
							 theta_distribution,
							 axis_distribution,
							 0.0,
							 0.0,
							 0.0 ) );

  Teuchos::RCP<FACEMC::DirectionalDistribution> directional_distribution;

  initializeDirectionalDistribution( directional_distribution );

  Teuchos::RCP<FACEMC::OneDDistribution> energy_distribution, 
    time_distribution;

  initializeEnergyAndTimeDists( energy_distribution, time_distribution );

  response_function.reset( new FACEMC::PhaseSpaceResponseFunction(
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
  Teuchos::RCP<FACEMC::OneDDistribution>
    theta_distribution( new FACEMC::UniformDistribution( 
					       0.0,
					       2*FACEMC::PhysicalConstants::pi,
					       1.0 ) );
  // Uniform distribution in mu dimension
  Teuchos::RCP<FACEMC::OneDDistribution>
    mu_distribution( new FACEMC::UniformDistribution( -1.0, 1.0, 1.0 ) );

  Teuchos::RCP<FACEMC::OneDDistribution> r_distribution;
  
  if( uniform )
    r_distribution.reset( new FACEMC::PowerDistribution<2u>( 
					1.0, 
					0.0, 
				        std::numeric_limits<double>::max() ) );
  else
  {
    r_distribution.reset( new FACEMC::UniformDistribution( 
					    0.0, 
					    std::numeric_limits<double>::max(),
					    1.0 ) );
  }

  Teuchos::RCP<FACEMC::SpatialDistribution>
    spatial_distribution( new FACEMC::SphericalSpatialDistribution( 
							   r_distribution,
							   theta_distribution,
							   mu_distribution,
							   0.0,
							   0.0,
							   0.0 ) );

  Teuchos::RCP<FACEMC::DirectionalDistribution> directional_distribution;

  initializeDirectionalDistribution( directional_distribution );

  Teuchos::RCP<FACEMC::OneDDistribution> energy_distribution, 
    time_distribution;

  initializeEnergyAndTimeDists( energy_distribution, time_distribution );

  response_function.reset( new FACEMC::PhaseSpaceResponseFunction(
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
// Check that the response function can be evaluated
TEUCHOS_UNIT_TEST( PhaseSpaceResponseFunction, evaluate )
{
  double position[3] = {0.0, 0.0, 0.0};
  double direction[3] = {1.0, 0.0, 0.0};
  
  FACEMC::BasicParticleState particle( FACEMC::PHOTON,
				       position,
				       direction,
				       1.0,
				       0.0,
				       1.0 );

  initializeCartesianResponseFunction( true );

  TEST_EQUALITY_CONST( response_function->evaluate( particle ), 1.0 );

  initializeCylindricalResponseFunction( true );

  TEST_EQUALITY_CONST( response_function->evaluate( particle ), 1.0 );

  initializeSphericalResponseFunction( true );

  TEST_EQUALITY_CONST( response_function->evaluate( particle ), 1.0 );

  initializeCartesianResponseFunction( false );
  
  TEST_FLOATING_EQUALITY( response_function->evaluate( particle ), 
			  pow( 2*FACEMC::PhysicalConstants::pi, -1.5 ),
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
