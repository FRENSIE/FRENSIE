//---------------------------------------------------------------------------//
//!
//! \file   tstTwoDInterpolationType.cpp
//! \author Luke Kersting
//! \brief  TwoDInterpolation type helper unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "MonteCarlo_TwoDInterpolationType.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the 2D interpolation types can be converted to int
TEUCHOS_UNIT_TEST( TwoDInterpolationType, convert_to_int )
{
  TEST_EQUALITY_CONST( (unsigned)MonteCarlo::LINLINLIN_INTERPOLATION, 1 );
  TEST_EQUALITY_CONST( (unsigned)MonteCarlo::LINLINLOG_INTERPOLATION, 2 );
  TEST_EQUALITY_CONST( (unsigned)MonteCarlo::LINLOGLIN_INTERPOLATION, 3 );
  TEST_EQUALITY_CONST( (unsigned)MonteCarlo::LOGLINLIN_INTERPOLATION, 4 );
  TEST_EQUALITY_CONST( (unsigned)MonteCarlo::LOGLOGLIN_INTERPOLATION, 5 );
  TEST_EQUALITY_CONST( (unsigned)MonteCarlo::LOGLINLOG_INTERPOLATION, 6 );
  TEST_EQUALITY_CONST( (unsigned)MonteCarlo::LINLOGLOG_INTERPOLATION, 7 );
  TEST_EQUALITY_CONST( (unsigned)MonteCarlo::LOGLOGLOG_INTERPOLATION, 8 );
}

//---------------------------------------------------------------------------//
// Check that an 2D interpolation type can be converted to a string
TEUCHOS_UNIT_TEST( TwoDInterpolationType, convertTwoDInterpolationTypeToString )
{
  std::string type_string =
    MonteCarlo::convertTwoDInterpolationTypeToString( MonteCarlo::LINLINLIN_INTERPOLATION );
  TEST_EQUALITY_CONST( type_string, "Lin-Lin-Lin" );

  type_string =
    MonteCarlo::convertTwoDInterpolationTypeToString( MonteCarlo::LINLINLOG_INTERPOLATION );
  TEST_EQUALITY_CONST( type_string, "Lin-Lin-Log" );

  type_string =
    MonteCarlo::convertTwoDInterpolationTypeToString( MonteCarlo::LINLOGLIN_INTERPOLATION );
  TEST_EQUALITY_CONST( type_string, "Lin-Log-Lin" );

  type_string =
    MonteCarlo::convertTwoDInterpolationTypeToString( MonteCarlo::LOGLINLIN_INTERPOLATION );
  TEST_EQUALITY_CONST( type_string, "Log-Lin-Lin" );

  type_string =
    MonteCarlo::convertTwoDInterpolationTypeToString( MonteCarlo::LOGLOGLIN_INTERPOLATION );
  TEST_EQUALITY_CONST( type_string, "Log-Log-Lin" );

  type_string =
    MonteCarlo::convertTwoDInterpolationTypeToString( MonteCarlo::LOGLINLOG_INTERPOLATION );
  TEST_EQUALITY_CONST( type_string, "Log-Lin-Log" );

  type_string =
    MonteCarlo::convertTwoDInterpolationTypeToString( MonteCarlo::LINLOGLOG_INTERPOLATION );
  TEST_EQUALITY_CONST( type_string, "Lin-Log-Log" );

  type_string =
    MonteCarlo::convertTwoDInterpolationTypeToString( MonteCarlo::LOGLOGLOG_INTERPOLATION );
  TEST_EQUALITY_CONST( type_string, "Log-Log-Log" );
}

//---------------------------------------------------------------------------//
// Check that a 2D interpolation type can be sent to a stream
TEUCHOS_UNIT_TEST( TwoDInterpolationType, stream_operator )
{
  std::stringstream ss;

  ss << MonteCarlo::LINLINLIN_INTERPOLATION;
  TEST_EQUALITY_CONST( ss.str(), "Lin-Lin-Lin" );

  ss.str( "" );
  ss << MonteCarlo::LINLINLOG_INTERPOLATION;
  TEST_EQUALITY_CONST( ss.str(), "Lin-Lin-Log" );

  ss.str( "" );
  ss << MonteCarlo::LINLOGLIN_INTERPOLATION;
  TEST_EQUALITY_CONST( ss.str(), "Lin-Log-Lin" );

  ss.str( "" );
  ss << MonteCarlo::LOGLINLIN_INTERPOLATION;
  TEST_EQUALITY_CONST( ss.str(), "Log-Lin-Lin" );

  ss.str( "" );
  ss << MonteCarlo::LOGLOGLIN_INTERPOLATION;
  TEST_EQUALITY_CONST( ss.str(), "Log-Log-Lin" );

  ss.str( "" );
  ss << MonteCarlo::LOGLINLOG_INTERPOLATION;
  TEST_EQUALITY_CONST( ss.str(), "Log-Lin-Log" );

  ss.str( "" );
  ss << MonteCarlo::LINLOGLOG_INTERPOLATION;
  TEST_EQUALITY_CONST( ss.str(), "Lin-Log-Log" );

  ss.str( "" );
  ss << MonteCarlo::LOGLOGLOG_INTERPOLATION;
  TEST_EQUALITY_CONST( ss.str(), "Log-Log-Log" );
}

//---------------------------------------------------------------------------//
// Check that a string can be converted to a TwoDInterpolationType
TEUCHOS_UNIT_TEST( TwoDInterpolationType,
                   convertStringToTwoDInterpolationType_LinLinLin )
{
  MonteCarlo::TwoDInterpolationType interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "LinLinLin" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LINLINLIN_INTERPOLATION );

  interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "linlinlin" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LINLINLIN_INTERPOLATION );

  interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "LINLINLIN" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LINLINLIN_INTERPOLATION );

  interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "Lin-Lin-Lin" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LINLINLIN_INTERPOLATION );

  interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "lin-lin-lin" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LINLINLIN_INTERPOLATION );

  interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "LIN-LIN-LIN" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LINLINLIN_INTERPOLATION );
}

//---------------------------------------------------------------------------//
// Check that a string can be converted to a TwoDInterpolationType
TEUCHOS_UNIT_TEST( TwoDInterpolationType,
                   convertStringToTwoDInterpolationType_LinLinLog )
{
  MonteCarlo::TwoDInterpolationType interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "LinLinLog" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LINLINLOG_INTERPOLATION );

  interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "linlinlog" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LINLINLOG_INTERPOLATION );

  interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "LINLINLOG" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LINLINLOG_INTERPOLATION );

  interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "Lin-Lin-Log" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LINLINLOG_INTERPOLATION );

  interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "lin-lin-log" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LINLINLOG_INTERPOLATION );

  interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "LIN-LIN-LOG" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LINLINLOG_INTERPOLATION );
}

//---------------------------------------------------------------------------//
// Check that a string can be converted to a TwoDInterpolationType
TEUCHOS_UNIT_TEST( TwoDInterpolationType,
                   convertStringToTwoDInterpolationType_LinLogLin )
{
  MonteCarlo::TwoDInterpolationType interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "LinLogLin" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LINLOGLIN_INTERPOLATION );

  interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "linloglin" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LINLOGLIN_INTERPOLATION );

  interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "LINLOGLIN" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LINLOGLIN_INTERPOLATION );

  interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "Lin-Log-Lin" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LINLOGLIN_INTERPOLATION );

  interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "lin-log-lin" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LINLOGLIN_INTERPOLATION );

  interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "LIN-LOG-LIN" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LINLOGLIN_INTERPOLATION );
}

//---------------------------------------------------------------------------//
// Check that a string can be converted to a TwoDInterpolationType
TEUCHOS_UNIT_TEST( TwoDInterpolationType,
                   convertStringToTwoDInterpolationType_LogLinLin )
{
  MonteCarlo::TwoDInterpolationType interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "LogLinLin" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LOGLINLIN_INTERPOLATION );

  interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "loglinlin" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LOGLINLIN_INTERPOLATION );

  interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "LOGLINLIN" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LOGLINLIN_INTERPOLATION );

  interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "Log-Lin-Lin" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LOGLINLIN_INTERPOLATION );

  interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "log-lin-lin" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LOGLINLIN_INTERPOLATION );

  interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "LOG-LIN-LIN" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LOGLINLIN_INTERPOLATION );
}

//---------------------------------------------------------------------------//
// Check that a string can be converted to a TwoDInterpolationType
TEUCHOS_UNIT_TEST( TwoDInterpolationType,
                   convertStringToTwoDInterpolationType_LogLogLin )
{
  MonteCarlo::TwoDInterpolationType interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "LogLogLin" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LOGLOGLIN_INTERPOLATION );

  interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "logloglin" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LOGLOGLIN_INTERPOLATION );

  interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "LOGLOGLIN" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LOGLOGLIN_INTERPOLATION );

  interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "Log-Log-Lin" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LOGLOGLIN_INTERPOLATION );

  interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "log-log-lin" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LOGLOGLIN_INTERPOLATION );

  interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "LOG-LOG-LIN" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LOGLOGLIN_INTERPOLATION );
}

//---------------------------------------------------------------------------//
// Check that a string can be converted to a TwoDInterpolationType
TEUCHOS_UNIT_TEST( TwoDInterpolationType,
                   convertStringToTwoDInterpolationType_LogLinLog )
{
  MonteCarlo::TwoDInterpolationType interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "LogLinLog" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LOGLINLOG_INTERPOLATION );

  interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "loglinlog" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LOGLINLOG_INTERPOLATION );

  interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "LOGLINLOG" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LOGLINLOG_INTERPOLATION );

  interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "Log-Lin-Log" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LOGLINLOG_INTERPOLATION );

  interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "log-lin-log" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LOGLINLOG_INTERPOLATION );

  interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "LOG-LIN-LOG" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LOGLINLOG_INTERPOLATION );
}

//---------------------------------------------------------------------------//
// Check that a string can be converted to a TwoDInterpolationType
TEUCHOS_UNIT_TEST( TwoDInterpolationType,
                   convertStringToTwoDInterpolationType_LinLogLog )
{
  MonteCarlo::TwoDInterpolationType interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "LinLogLog" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LINLOGLOG_INTERPOLATION );

  interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "linloglog" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LINLOGLOG_INTERPOLATION );

  interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "LINLOGLOG" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LINLOGLOG_INTERPOLATION );

  interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "Lin-Log-Log" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LINLOGLOG_INTERPOLATION );

  interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "lin-log-log" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LINLOGLOG_INTERPOLATION );

  interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "LIN-LOG-LOG" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LINLOGLOG_INTERPOLATION );
}

//---------------------------------------------------------------------------//
// Check that a string can be converted to a TwoDInterpolationType
TEUCHOS_UNIT_TEST( TwoDInterpolationType,
                   convertStringToTwoDInterpolationType_LogLogLog )
{
  MonteCarlo::TwoDInterpolationType interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "LogLogLog" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LOGLOGLOG_INTERPOLATION );

  interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "logloglog" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LOGLOGLOG_INTERPOLATION );

  interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "LOGLOGLOG" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LOGLOGLOG_INTERPOLATION );

  interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "Log-Log-Log" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LOGLOGLOG_INTERPOLATION );

  interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "log-log-log" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LOGLOGLOG_INTERPOLATION );

  interp =
    MonteCarlo::convertStringToTwoDInterpolationType( "LOG-LOG-LOG" );
  TEST_EQUALITY_CONST( interp, MonteCarlo::LOGLOGLOG_INTERPOLATION );
}
//---------------------------------------------------------------------------//
// end tstTwoDInterpolationType.cpp
//---------------------------------------------------------------------------//
