//---------------------------------------------------------------------------//
//!
//! \file   tstEnergySpaceResponseFunction.cpp
//! \author Alex Robinson
//! \brief  Energy space response function unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_EnergySpaceResponseFunction.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Utility_UniformDistribution.hpp"

std::shared_ptr<Utility::OneDDistribution> energy_distribution(
			   new Utility::UniformDistribution( 0.0, 1e6, 1.0 ) );

std::shared_ptr<MonteCarlo::EnergySpaceResponseFunction> response_function(
	  new MonteCarlo::EnergySpaceResponseFunction( 0, 
						       "uniform_energy",
						       energy_distribution ) );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the name of the response function can be returned
TEUCHOS_UNIT_TEST( EnergySpaceResponseFunction, getName )
{
  TEST_EQUALITY( response_function->getName(), "uniform_energy" );
}

//---------------------------------------------------------------------------//
// Check that the response function id can be returned
TEUCHOS_UNIT_TEST( EnergySpaceResponseFunction, getId )
{
  TEST_EQUALITY_CONST( response_function->getId(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the response function can be evaluated
TEUCHOS_UNIT_TEST( EnergySpaceResponseFunction, evaluate )
{
  MonteCarlo::PhotonState particle( 0ull );
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
TEUCHOS_UNIT_TEST( EnergySpaceResponseFunction, isSpatiallyUniform )
{
  TEST_ASSERT( response_function->isSpatiallyUniform() );
}

//---------------------------------------------------------------------------//
// end tstEnergySpaceResponseFunction.cpp
//---------------------------------------------------------------------------//
