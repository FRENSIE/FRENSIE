//---------------------------------------------------------------------------//
//!
//! \file   tstEnergySpaceResponseFunction.cpp
//! \author Alex Robinson
//! \brief  Energy space response function unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Facemc_EnergySpaceResponseFunction.hpp"
#include "Facemc_PhotonState.hpp"
#include "Utility_UniformDistribution.hpp"

Teuchos::RCP<Utility::OneDDistribution> energy_distribution(
			   new Utility::UniformDistribution( 0.0, 1e6, 1.0 ) );

Teuchos::RCP<Facemc::EnergySpaceResponseFunction> response_function(
	      new Facemc::EnergySpaceResponseFunction( "uniform_energy",
						       energy_distribution ) );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the name of the response function can be returned
TEUCHOS_UNIT_TEST( ResponseFunction, getName )
{
  TEST_EQUALITY( response_function->getName(), "uniform_energy" );
}

//---------------------------------------------------------------------------//
// Check that the response function can be evaluated
TEUCHOS_UNIT_TEST( ResponseFunction, evaluate )
{
  Facemc::PhotonState particle( 0ull );
  particle.setEnergy( 1e-11 );

  TEST_EQUALITY_CONST( response_function->evaluate( particle ), 1.0 );

  particle.setEnergy( 1e3 );

  TEST_EQUALITY_CONST( response_function->evaluate( particle ), 1.0 );

  particle.setEnergy( 1e6 );

  TEST_EQUALITY_CONST( response_function->evaluate( particle ), 1.0 );

  particle.setEnergy( 2e6 );

  TEST_EQUALITY_CONST( response_function->evaluate( particle), 0.0 );
}

//---------------------------------------------------------------------------//
// Check if the response function is spatially uniform
TEUCHOS_UNIT_TEST( ResponseFunction, isSpatiallyUniform )
{
  TEST_ASSERT( response_function->isSpatiallyUniform() );
}

//---------------------------------------------------------------------------//
// end tstEnergySpaceResponseFunction.cpp
//---------------------------------------------------------------------------//
