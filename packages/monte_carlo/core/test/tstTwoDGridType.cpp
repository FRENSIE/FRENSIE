//---------------------------------------------------------------------------//
//!
//! \file   tstTwoDGridType.cpp
//! \author Luke Kersting
//! \brief  TwoDGrid type helper unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "MonteCarlo_TwoDGridType.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the 2D grid types can be converted to int
TEUCHOS_UNIT_TEST( TwoDGridType, convert_to_int )
{
  TEST_EQUALITY_CONST( (unsigned)MonteCarlo::CORRELATED_GRID, 1 );
  TEST_EQUALITY_CONST( (unsigned)MonteCarlo::UNIT_BASE_CORRELATED_GRID, 2 );
  TEST_EQUALITY_CONST( (unsigned)MonteCarlo::DIRECT_GRID, 3 );
  TEST_EQUALITY_CONST( (unsigned)MonteCarlo::UNIT_BASE_GRID, 4 );
  TEST_EQUALITY_CONST( (unsigned)MonteCarlo::CUMULATIVE_POINTS_GRID, 5 );
}

//---------------------------------------------------------------------------//
// Check that an 2D grid type can be converted to a string
TEUCHOS_UNIT_TEST( TwoDGridType, convertTwoDGridTypeToString )
{
  std::string type_string =
    MonteCarlo::convertTwoDGridTypeToString( MonteCarlo::CORRELATED_GRID );
  TEST_EQUALITY_CONST( type_string, "Correlated" );

  type_string =
    MonteCarlo::convertTwoDGridTypeToString( MonteCarlo::UNIT_BASE_CORRELATED_GRID );
  TEST_EQUALITY_CONST( type_string, "Unit-base Correlated" );

  type_string =
    MonteCarlo::convertTwoDGridTypeToString( MonteCarlo::DIRECT_GRID );
  TEST_EQUALITY_CONST( type_string, "Direct" );

  type_string =
    MonteCarlo::convertTwoDGridTypeToString( MonteCarlo::UNIT_BASE_GRID );
  TEST_EQUALITY_CONST( type_string, "Unit-base" );

  type_string =
    MonteCarlo::convertTwoDGridTypeToString( MonteCarlo::CUMULATIVE_POINTS_GRID );
  TEST_EQUALITY_CONST( type_string, "Cumulative Points" );
}

//---------------------------------------------------------------------------//
// Check that a 2D grid type can be sent to a stream
TEUCHOS_UNIT_TEST( TwoDGridType, stream_operator )
{
  std::stringstream ss;

  ss << MonteCarlo::CORRELATED_GRID;
  TEST_EQUALITY_CONST( ss.str(), "Correlated" );

  ss.str( "" );
  ss << MonteCarlo::UNIT_BASE_CORRELATED_GRID;
  TEST_EQUALITY_CONST( ss.str(), "Unit-base Correlated" );

  ss.str( "" );
  ss << MonteCarlo::DIRECT_GRID;
  TEST_EQUALITY_CONST( ss.str(), "Direct" );

  ss.str( "" );
  ss << MonteCarlo::UNIT_BASE_GRID;
  TEST_EQUALITY_CONST( ss.str(), "Unit-base" );

  ss.str( "" );
  ss << MonteCarlo::CUMULATIVE_POINTS_GRID;
  TEST_EQUALITY_CONST( ss.str(), "Cumulative Points" );
}

//---------------------------------------------------------------------------//
// Check that a string can be converted to a TwoDGridType
TEUCHOS_UNIT_TEST( TwoDGridType,
                   convertStringToTwoDGridType_Correlated )
{
  MonteCarlo::TwoDGridType interp =
    MonteCarlo::convertStringToTwoDGridType( "Correlated" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::CORRELATED_GRID );

  interp =
    MonteCarlo::convertStringToTwoDGridType( "correlated" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::CORRELATED_GRID );

  interp =
    MonteCarlo::convertStringToTwoDGridType( "CORRELATED" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::CORRELATED_GRID );
}

//---------------------------------------------------------------------------//
// Check that a string can be converted to a TwoDGridType
TEUCHOS_UNIT_TEST( TwoDGridType,
                   convertStringToTwoDGridType_UnitBaseCorrelated )
{
  MonteCarlo::TwoDGridType interp =
    MonteCarlo::convertStringToTwoDGridType( "Unit-base Correlated" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::UNIT_BASE_CORRELATED_GRID );

  interp =
    MonteCarlo::convertStringToTwoDGridType( "unit-base correlated" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::UNIT_BASE_CORRELATED_GRID );

  interp =
    MonteCarlo::convertStringToTwoDGridType( "UNIT-BASE CORRELATED" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::UNIT_BASE_CORRELATED_GRID );
}

//---------------------------------------------------------------------------//
// Check that a string can be converted to a TwoDGridType
TEUCHOS_UNIT_TEST( TwoDGridType,
                   convertStringToTwoDGridType_Direct )
{
  MonteCarlo::TwoDGridType interp =
    MonteCarlo::convertStringToTwoDGridType( "Direct" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::DIRECT_GRID );

  interp =
    MonteCarlo::convertStringToTwoDGridType( "direct" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::DIRECT_GRID );

  interp =
    MonteCarlo::convertStringToTwoDGridType( "DIRECT" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::DIRECT_GRID );
}

//---------------------------------------------------------------------------//
// Check that a string can be converted to a TwoDGridType
TEUCHOS_UNIT_TEST( TwoDGridType,
                   convertStringToTwoDGridType_UnitBase )
{
  MonteCarlo::TwoDGridType interp =
    MonteCarlo::convertStringToTwoDGridType( "Unit-base" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::UNIT_BASE_GRID );

  interp =
    MonteCarlo::convertStringToTwoDGridType( "unit-base" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::UNIT_BASE_GRID );

  interp =
    MonteCarlo::convertStringToTwoDGridType( "UNIT-BASE" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::UNIT_BASE_GRID );
}

//---------------------------------------------------------------------------//
// Check that a string can be converted to a TwoDGridType
TEUCHOS_UNIT_TEST( TwoDGridType,
                   convertStringToTwoDGridType_CumulativePoints )
{
  MonteCarlo::TwoDGridType interp =
    MonteCarlo::convertStringToTwoDGridType( "Cumulative Points" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::CUMULATIVE_POINTS_GRID );

  interp =
    MonteCarlo::convertStringToTwoDGridType( "cumulative points" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::CUMULATIVE_POINTS_GRID );

  interp =
    MonteCarlo::convertStringToTwoDGridType( "CUMULATIVE POINTS" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::CUMULATIVE_POINTS_GRID );
}

//---------------------------------------------------------------------------//
// end tstTwoDGridType.cpp
//---------------------------------------------------------------------------//