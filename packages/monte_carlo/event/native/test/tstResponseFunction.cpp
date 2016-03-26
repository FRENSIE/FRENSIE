//---------------------------------------------------------------------------//
//!
//! \file   tstResponseFunction.cpp
//! \author Alex Robinson
//! \brief  Response function unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ResponseFunction.hpp"
#include "MonteCarlo_PhotonState.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the name of the response function can be returned
TEUCHOS_UNIT_TEST( ResponseFunction, getName )
{
  std::shared_ptr<MonteCarlo::ResponseFunction> response_function= 
    MonteCarlo::ResponseFunction::default_response_function;

  TEST_EQUALITY( response_function->getName(), "default" );
}

//---------------------------------------------------------------------------//
// Check that the response function id can be returned
TEUCHOS_UNIT_TEST( ResponseFunction, getId )
{
  std::shared_ptr<MonteCarlo::ResponseFunction> response_function= 
    MonteCarlo::ResponseFunction::default_response_function;

  TEST_EQUALITY_CONST( response_function->getId(), 
		       std::numeric_limits<unsigned>::max() );
}

//---------------------------------------------------------------------------//
// Check that the response function can be evaluated
TEUCHOS_UNIT_TEST( ResponseFunction, evaluate )
{
  std::shared_ptr<MonteCarlo::ResponseFunction> response_function= 
    MonteCarlo::ResponseFunction::default_response_function;

  MonteCarlo::PhotonState particle( 0ull );
  
  TEST_EQUALITY_CONST( response_function->evaluate( particle ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check if the response function is spatially uniform
TEUCHOS_UNIT_TEST( ResponseFunction, isSpatiallyUniform )
{
  std::shared_ptr<MonteCarlo::ResponseFunction> response_function= 
    MonteCarlo::ResponseFunction::default_response_function;

  TEST_ASSERT( response_function->isSpatiallyUniform() );
}

//---------------------------------------------------------------------------//
// end tstResponseFunction.cpp
//---------------------------------------------------------------------------//
