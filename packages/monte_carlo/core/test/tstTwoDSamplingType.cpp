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
  TEST_EQUALITY_CONST( (unsigned)MonteCarlo::UNIT_BASE_CORRELATED_SAMPLING, 2 );
  TEST_EQUALITY_CONST( (unsigned)MonteCarlo::DIRECT_SAMPLING, 3 );
  TEST_EQUALITY_CONST( (unsigned)MonteCarlo::UNIT_BASE_SAMPLING, 4 );
  TEST_EQUALITY_CONST( (unsigned)MonteCarlo::CUMULATIVE_POINTS_SAMPLING, 5 );
}

//---------------------------------------------------------------------------//
// Check that an 2D sampling type can be converted to a string
TEUCHOS_UNIT_TEST( TwoDSamplingType, convertTwoDSamplingTypeToString )
{
  std::string type_string =
    MonteCarlo::convertTwoDSamplingTypeToString( MonteCarlo::CORRELATED_SAMPLING );
  TEST_EQUALITY_CONST( type_string, "Correlated" );

  type_string =
    MonteCarlo::convertTwoDSamplingTypeToString( MonteCarlo::UNIT_BASE_CORRELATED_SAMPLING );
  TEST_EQUALITY_CONST( type_string, "Unit-base Correlated" );

  type_string =
    MonteCarlo::convertTwoDSamplingTypeToString( MonteCarlo::DIRECT_SAMPLING );
  TEST_EQUALITY_CONST( type_string, "Direct" );

  type_string =
    MonteCarlo::convertTwoDSamplingTypeToString( MonteCarlo::UNIT_BASE_SAMPLING );
  TEST_EQUALITY_CONST( type_string, "Unit-base" );

  type_string =
    MonteCarlo::convertTwoDSamplingTypeToString( MonteCarlo::CUMULATIVE_POINTS_SAMPLING );
  TEST_EQUALITY_CONST( type_string, "Cumulative Points" );
}

//---------------------------------------------------------------------------//
// Check that a 2D Sampling type can be sent to a stream
TEUCHOS_UNIT_TEST( TwoDSamplingType, stream_operator )
{
  std::stringstream ss;

  ss << MonteCarlo::CORRELATED_SAMPLING;
  TEST_EQUALITY_CONST( ss.str(), "Correlated" );

  ss.str( "" );
  ss << MonteCarlo::UNIT_BASE_CORRELATED_SAMPLING;
  TEST_EQUALITY_CONST( ss.str(), "Unit-base Correlated" );

  ss.str( "" );
  ss << MonteCarlo::DIRECT_SAMPLING;
  TEST_EQUALITY_CONST( ss.str(), "Direct" );

  ss.str( "" );
  ss << MonteCarlo::UNIT_BASE_SAMPLING;
  TEST_EQUALITY_CONST( ss.str(), "Unit-base" );

  ss.str( "" );
  ss << MonteCarlo::CUMULATIVE_POINTS_SAMPLING;
  TEST_EQUALITY_CONST( ss.str(), "Cumulative Points" );
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
                   convertStringToTwoDSamplingType_UnitBaseCorrelated )
{
  MonteCarlo::TwoDSamplingType interp =
    MonteCarlo::convertStringToTwoDSamplingType( "Unit-base Correlated" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::UNIT_BASE_CORRELATED_SAMPLING );

  interp =
    MonteCarlo::convertStringToTwoDSamplingType( "unit-base correlated" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::UNIT_BASE_CORRELATED_SAMPLING );

  interp =
    MonteCarlo::convertStringToTwoDSamplingType( "UNIT-BASE CORRELATED" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::UNIT_BASE_CORRELATED_SAMPLING );
}

//---------------------------------------------------------------------------//
// Check that a string can be converted to a TwoDSamplingType
TEUCHOS_UNIT_TEST( TwoDSamplingType,
                   convertStringToTwoDSamplingType_Direct )
{
  MonteCarlo::TwoDSamplingType interp =
    MonteCarlo::convertStringToTwoDSamplingType( "Direct" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::DIRECT_SAMPLING );

  interp =
    MonteCarlo::convertStringToTwoDSamplingType( "direct" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::DIRECT_SAMPLING );

  interp =
    MonteCarlo::convertStringToTwoDSamplingType( "DIRECT" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::DIRECT_SAMPLING );
}

//---------------------------------------------------------------------------//
// Check that a string can be converted to a TwoDSamplingType
TEUCHOS_UNIT_TEST( TwoDSamplingType,
                   convertStringToTwoDSamplingType_UnitBase )
{
  MonteCarlo::TwoDSamplingType interp =
    MonteCarlo::convertStringToTwoDSamplingType( "Unit-base" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::UNIT_BASE_SAMPLING );

  interp =
    MonteCarlo::convertStringToTwoDSamplingType( "unit-base" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::UNIT_BASE_SAMPLING );

  interp =
    MonteCarlo::convertStringToTwoDSamplingType( "UNIT-BASE" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::UNIT_BASE_SAMPLING );
}

//---------------------------------------------------------------------------//
// Check that a string can be converted to a TwoDSamplingType
TEUCHOS_UNIT_TEST( TwoDSamplingType,
                   convertStringToTwoDSamplingType_CumulativePoints )
{
  MonteCarlo::TwoDSamplingType interp =
    MonteCarlo::convertStringToTwoDSamplingType( "Cumulative Points" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::CUMULATIVE_POINTS_SAMPLING );

  interp =
    MonteCarlo::convertStringToTwoDSamplingType( "cumulative points" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::CUMULATIVE_POINTS_SAMPLING );

  interp =
    MonteCarlo::convertStringToTwoDSamplingType( "CUMULATIVE POINTS" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::CUMULATIVE_POINTS_SAMPLING );
}

//---------------------------------------------------------------------------//
// end tstTwoDSamplingType.cpp
//---------------------------------------------------------------------------//