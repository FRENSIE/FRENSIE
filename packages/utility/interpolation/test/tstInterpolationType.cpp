//---------------------------------------------------------------------------//
//!
//! \file   tstInterpolationType.cpp
//! \author Alex Robinson
//! \brief  Interpolation type helper unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_InterpolationType.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the interpolation types can be converted to ENDF interpolation
// types
TEUCHOS_UNIT_TEST( InterpolationType, convert_to_endf )
{
  TEST_EQUALITY_CONST( (unsigned)Utility::HISTOGRAM_INTERPOLATION, 1u );
  TEST_EQUALITY_CONST( (unsigned)Utility::LINLIN_INTERPOLATION, 2u );
  TEST_EQUALITY_CONST( (unsigned)Utility::LINLOG_INTERPOLATION, 3u );
  TEST_EQUALITY_CONST( (unsigned)Utility::LOGLIN_INTERPOLATION, 4u );
  TEST_EQUALITY_CONST( (unsigned)Utility::LOGLOG_INTERPOLATION, 5u );
  TEST_EQUALITY_CONST( (unsigned)Utility::GAMOW_INTERPOLATION, 6u );
}

//---------------------------------------------------------------------------//
// Check that an ENDF interpolation type can be converted to an interpolation
// type
TEUCHOS_UNIT_TEST( InterpolationType,
                   convertENDFInterpolationTypeToInterpolationType )
{
  Utility::InterpolationType type =
    Utility::convertENDFInterpolationTypeToInterpolationType( 1u );
  
  TEST_EQUALITY_CONST( type, Utility::HISTOGRAM_INTERPOLATION );

  type = Utility::convertENDFInterpolationTypeToInterpolationType( 2u );

  TEST_EQUALITY_CONST( type, Utility::LINLIN_INTERPOLATION );

  type = Utility::convertENDFInterpolationTypeToInterpolationType( 3u );

  TEST_EQUALITY_CONST( type, Utility::LINLOG_INTERPOLATION );

  type = Utility::convertENDFInterpolationTypeToInterpolationType( 4u );

  TEST_EQUALITY_CONST( type, Utility::LOGLIN_INTERPOLATION );

  type = Utility::convertENDFInterpolationTypeToInterpolationType( 5u );

  TEST_EQUALITY_CONST( type, Utility::LOGLOG_INTERPOLATION );

  type = Utility::convertENDFInterpolationTypeToInterpolationType( 6u );

  TEST_EQUALITY_CONST( type, Utility::GAMOW_INTERPOLATION );

  TEST_THROW( Utility::convertENDFInterpolationTypeToInterpolationType( 0u ),
              std::runtime_error );
}

//---------------------------------------------------------------------------//
// Check that an interpolation type can be converted to a string
TEUCHOS_UNIT_TEST( InterpolationType, convertInterpolationTypeToString )
{
  std::string type_string =
    Utility::convertInterpolationTypeToString( Utility::HISTOGRAM_INTERPOLATION );
  
  TEST_EQUALITY_CONST( type_string, "Histogram" );

  type_string =
    Utility::convertInterpolationTypeToString( Utility::LINLIN_INTERPOLATION );

  TEST_EQUALITY_CONST( type_string, "Lin-Lin" );

  type_string =
    Utility::convertInterpolationTypeToString( Utility::LINLOG_INTERPOLATION );

  TEST_EQUALITY_CONST( type_string, "Lin-Log" );

  type_string =
    Utility::convertInterpolationTypeToString( Utility::LOGLIN_INTERPOLATION );

  TEST_EQUALITY_CONST( type_string, "Log-Lin" );

  type_string =
    Utility::convertInterpolationTypeToString( Utility::LOGLOG_INTERPOLATION );

  TEST_EQUALITY_CONST( type_string, "Log-Log" );

  type_string =
    Utility::convertInterpolationTypeToString( Utility::GAMOW_INTERPOLATION );

  TEST_EQUALITY_CONST( type_string, "Gamow" );
}

//---------------------------------------------------------------------------//
// Check that an interpolation type can be sent to a stream
TEUCHOS_UNIT_TEST( InterpolationType, stream_operator )
{
  std::stringstream ss;

  ss << Utility::HISTOGRAM_INTERPOLATION;

  TEST_EQUALITY_CONST( ss.str(), "Histogram" );

  ss.str( "" );
  ss << Utility::LINLIN_INTERPOLATION;

  TEST_EQUALITY_CONST( ss.str(), "Lin-Lin" );

  ss.str( "" );
  ss << Utility::LINLOG_INTERPOLATION;

  TEST_EQUALITY_CONST( ss.str(), "Lin-Log" );

  ss.str( "" );
  ss << Utility::LOGLIN_INTERPOLATION;

  TEST_EQUALITY_CONST( ss.str(), "Log-Lin" );

  ss.str( "" );
  ss << Utility::LOGLOG_INTERPOLATION;

  TEST_EQUALITY_CONST( ss.str(), "Log-Log" );

  ss.str( "" );
  ss << Utility::GAMOW_INTERPOLATION;

  TEST_EQUALITY_CONST( ss.str(), "Gamow" );
}

//---------------------------------------------------------------------------//
// end tstInterpolationType.cpp
//---------------------------------------------------------------------------//
