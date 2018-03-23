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

// FRENSIE Includes
#include "Utility_InterpolationType.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the interpolation types can be converted to ENDF interpolation
// types
FRENSIE_UNIT_TEST( InterpolationType, convert_to_endf )
{
  FRENSIE_CHECK_EQUAL( (unsigned)Utility::HISTOGRAM_INTERPOLATION, 1u );
  FRENSIE_CHECK_EQUAL( (unsigned)Utility::LINLIN_INTERPOLATION, 2u );
  FRENSIE_CHECK_EQUAL( (unsigned)Utility::LINLOG_INTERPOLATION, 3u );
  FRENSIE_CHECK_EQUAL( (unsigned)Utility::LOGLIN_INTERPOLATION, 4u );
  FRENSIE_CHECK_EQUAL( (unsigned)Utility::LOGLOG_INTERPOLATION, 5u );
  FRENSIE_CHECK_EQUAL( (unsigned)Utility::GAMOW_INTERPOLATION, 6u );
}

//---------------------------------------------------------------------------//
// Check that an ENDF interpolation type can be converted to an interpolation
// type
FRENSIE_UNIT_TEST( InterpolationType,
                   convertENDFInterpolationTypeToInterpolationType )
{
  Utility::InterpolationType type =
    Utility::convertENDFInterpolationTypeToInterpolationType( 1u );

  FRENSIE_CHECK_EQUAL( type, Utility::HISTOGRAM_INTERPOLATION );

  type = Utility::convertENDFInterpolationTypeToInterpolationType( 2u );

  FRENSIE_CHECK_EQUAL( type, Utility::LINLIN_INTERPOLATION );

  type = Utility::convertENDFInterpolationTypeToInterpolationType( 3u );

  FRENSIE_CHECK_EQUAL( type, Utility::LINLOG_INTERPOLATION );

  type = Utility::convertENDFInterpolationTypeToInterpolationType( 4u );

  FRENSIE_CHECK_EQUAL( type, Utility::LOGLIN_INTERPOLATION );

  type = Utility::convertENDFInterpolationTypeToInterpolationType( 5u );

  FRENSIE_CHECK_EQUAL( type, Utility::LOGLOG_INTERPOLATION );

  type = Utility::convertENDFInterpolationTypeToInterpolationType( 6u );

  FRENSIE_CHECK_EQUAL( type, Utility::GAMOW_INTERPOLATION );

  FRENSIE_CHECK_THROW( Utility::convertENDFInterpolationTypeToInterpolationType( 0u ),
                       std::runtime_error );
}

//---------------------------------------------------------------------------//
// Check that an interpolation type can be converted to a string
FRENSIE_UNIT_TEST( InterpolationType, toString )
{
  std::string type_string =
    Utility::toString( Utility::HISTOGRAM_INTERPOLATION );

  FRENSIE_CHECK_EQUAL( type_string, "Histogram" );

  type_string = Utility::toString( Utility::LINLIN_INTERPOLATION );

  FRENSIE_CHECK_EQUAL( type_string, "Lin-Lin" );

  type_string = Utility::toString( Utility::LINLOG_INTERPOLATION );

  FRENSIE_CHECK_EQUAL( type_string, "Lin-Log" );

  type_string = Utility::toString( Utility::LOGLIN_INTERPOLATION );

  FRENSIE_CHECK_EQUAL( type_string, "Log-Lin" );

  type_string = Utility::toString( Utility::LOGLOG_INTERPOLATION );

  FRENSIE_CHECK_EQUAL( type_string, "Log-Log" );

  type_string = Utility::toString( Utility::GAMOW_INTERPOLATION );

  FRENSIE_CHECK_EQUAL( type_string, "Gamow" );
}

//---------------------------------------------------------------------------//
// Check that an interpolation type can be sent to a stream
FRENSIE_UNIT_TEST( InterpolationType, stream_operator )
{
  std::stringstream ss;

  ss << Utility::HISTOGRAM_INTERPOLATION;

  FRENSIE_CHECK_EQUAL( ss.str(), "Histogram" );

  ss.str( "" );
  ss << Utility::LINLIN_INTERPOLATION;

  FRENSIE_CHECK_EQUAL( ss.str(), "Lin-Lin" );

  ss.str( "" );
  ss << Utility::LINLOG_INTERPOLATION;

  FRENSIE_CHECK_EQUAL( ss.str(), "Lin-Log" );

  ss.str( "" );
  ss << Utility::LOGLIN_INTERPOLATION;

  FRENSIE_CHECK_EQUAL( ss.str(), "Log-Lin" );

  ss.str( "" );
  ss << Utility::LOGLOG_INTERPOLATION;

  FRENSIE_CHECK_EQUAL( ss.str(), "Log-Log" );

  ss.str( "" );
  ss << Utility::GAMOW_INTERPOLATION;

  FRENSIE_CHECK_EQUAL( ss.str(), "Gamow" );
}

//---------------------------------------------------------------------------//
// end tstInterpolationType.cpp
//---------------------------------------------------------------------------//
