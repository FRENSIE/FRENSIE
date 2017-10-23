//---------------------------------------------------------------------------//
//!
//! \file   tstTwoDSamplingType.cpp
//! \author Luke Kersting
//! \brief  TwoDSampling type helper unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "MonteCarlo_TwoDSamplingType.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the 2D sampling types can be converted to int
TEUCHOS_UNIT_TEST( TwoDSamplingType, convert_to_int )
{
  TEST_EQUALITY_CONST( (unsigned)MonteCarlo::CORRELATED_SAMPLING, 1 );
  TEST_EQUALITY_CONST( (unsigned)MonteCarlo::EXACT_SAMPLING, 2 );
  TEST_EQUALITY_CONST( (unsigned)MonteCarlo::STOCHASTIC_SAMPLING, 3 );
}

//---------------------------------------------------------------------------//
// Check that an 2D sampling type can be converted to a string
TEUCHOS_UNIT_TEST( TwoDSamplingType, convertTwoDSamplingTypeToString )
{
  std::string type_string =
    MonteCarlo::convertTwoDSamplingTypeToString( MonteCarlo::CORRELATED_SAMPLING );
  TEST_EQUALITY_CONST( type_string, "Correlated" );

  type_string =
    MonteCarlo::convertTwoDSamplingTypeToString( MonteCarlo::EXACT_SAMPLING );
  TEST_EQUALITY_CONST( type_string, "Exact" );

  type_string =
    MonteCarlo::convertTwoDSamplingTypeToString( MonteCarlo::STOCHASTIC_SAMPLING );
  TEST_EQUALITY_CONST( type_string, "Stochastic" );
}

//---------------------------------------------------------------------------//
// Check that a 2D Sampling type can be sent to a stream
TEUCHOS_UNIT_TEST( TwoDSamplingType, stream_operator )
{
  std::stringstream ss;

  ss << MonteCarlo::CORRELATED_SAMPLING;
  TEST_EQUALITY_CONST( ss.str(), "Correlated" );

  ss.str( "" );
  ss << MonteCarlo::EXACT_SAMPLING;
  TEST_EQUALITY_CONST( ss.str(), "Exact" );

  ss.str( "" );
  ss << MonteCarlo::STOCHASTIC_SAMPLING;
  TEST_EQUALITY_CONST( ss.str(), "Stochastic" );
}

//---------------------------------------------------------------------------//
// Check that a string can be converted to a TwoDSamplingType
TEUCHOS_UNIT_TEST( TwoDSamplingType,
                   convertStringToTwoDSamplingType_Correlated )
{
  MonteCarlo::TwoDSamplingType interp =
    MonteCarlo::convertStringToTwoDSamplingType( "Correlated" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::CORRELATED_SAMPLING );

  interp =
    MonteCarlo::convertStringToTwoDSamplingType( "correlated" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::CORRELATED_SAMPLING );

  interp =
    MonteCarlo::convertStringToTwoDSamplingType( "CORRELATED" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::CORRELATED_SAMPLING );
}

//---------------------------------------------------------------------------//
// Check that a string can be converted to a TwoDSamplingType
TEUCHOS_UNIT_TEST( TwoDSamplingType,
                   convertStringToTwoDSamplingType_Exact )
{
  MonteCarlo::TwoDSamplingType interp =
    MonteCarlo::convertStringToTwoDSamplingType( "Exact" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::EXACT_SAMPLING );

  interp =
    MonteCarlo::convertStringToTwoDSamplingType( "exact" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::EXACT_SAMPLING );

  interp =
    MonteCarlo::convertStringToTwoDSamplingType( "EXACT" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::EXACT_SAMPLING );
}

//---------------------------------------------------------------------------//
// Check that a string can be converted to a TwoDSamplingType
TEUCHOS_UNIT_TEST( TwoDSamplingType,
                   convertStringToTwoDSamplingType_Stochastic )
{
  MonteCarlo::TwoDSamplingType interp =
    MonteCarlo::convertStringToTwoDSamplingType( "Stochastic" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::STOCHASTIC_SAMPLING );

  interp =
    MonteCarlo::convertStringToTwoDSamplingType( "stochastic" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::STOCHASTIC_SAMPLING );

  interp =
    MonteCarlo::convertStringToTwoDSamplingType( "STOCHASTIC" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::STOCHASTIC_SAMPLING );
}

//---------------------------------------------------------------------------//
// end tstTwoDSamplingType.cpp
//---------------------------------------------------------------------------//