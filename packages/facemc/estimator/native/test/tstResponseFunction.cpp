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
#include "Facemc_ResponseFunction.hpp"
#include "Facemc_PhotonState.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the name of the response function can be returned
TEUCHOS_UNIT_TEST( ResponseFunction, getName )
{
  Teuchos::RCP<Facemc::ResponseFunction> response_function= 
    Facemc::ResponseFunction::default_response_function;

  TEST_EQUALITY( response_function->getName(), "default" );
}

//---------------------------------------------------------------------------//
// Check that the response function can be evaluated
TEUCHOS_UNIT_TEST( ResponseFunction, evaluate )
{
  Teuchos::RCP<Facemc::ResponseFunction> response_function= 
    Facemc::ResponseFunction::default_response_function;

  Facemc::PhotonState particle( 0ull );
  
  TEST_EQUALITY_CONST( response_function->evaluate( particle ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check if the response function is spatially uniform
TEUCHOS_UNIT_TEST( ResponseFunction, isSpatiallyUniform )
{
  Teuchos::RCP<Facemc::ResponseFunction> response_function= 
    Facemc::ResponseFunction::default_response_function;

  TEST_ASSERT( response_function->isSpatiallyUniform() );
}

//---------------------------------------------------------------------------//
// end tstResponseFunction.cpp
//---------------------------------------------------------------------------//
