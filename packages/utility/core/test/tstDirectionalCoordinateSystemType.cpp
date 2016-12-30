//---------------------------------------------------------------------------//
//!
//! \file   tstDirectionalCoordinateSystemType.cpp
//! \author Alex Robinson
//! \brief  Directional coordinate system type unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <string>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_DirectionalCoordinateSystemType.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the directional coordinate system enums can be converted to
// strings
TEUCHOS_UNIT_TEST( DirectionalCoordinateSystemType,
                   convertDirectionalCoordinateSystemTypeEnumToString )
{
  std::string coord_system_name =
    Utility::convertDirectionalCoordinateSystemTypeEnumToString(
                            Utility::CARTESIAN_DIRECTIONAL_COORDINATE_SYSTEM );

  TEST_EQUALITY_CONST( coord_system_name,
                       "Cartesian Directional Coordinate System" );

  coord_system_name =
    Utility::convertDirectionalCoordinateSystemTypeEnumToString(
                            Utility::SPHERICAL_DIRECTIONAL_COORDINATE_SYSTEM );

  TEST_EQUALITY_CONST( coord_system_name,
                       "Spherical Directional Coordinate System" );
}

//---------------------------------------------------------------------------//
// Check that the directional coordinate system enums can be placed in a stream
TEUCHOS_UNIT_TEST( DirectionalCoordinateSystemType,
                   stream_operator )
{
  std::ostringstream oss;

  oss << Utility::CARTESIAN_DIRECTIONAL_COORDINATE_SYSTEM;
  
  TEST_EQUALITY_CONST( oss.str(), "Cartesian Directional Coordinate System" );

  oss.str( "" );
  oss.clear();
  
  oss << Utility::SPHERICAL_DIRECTIONAL_COORDINATE_SYSTEM;

  TEST_EQUALITY_CONST( oss.str(), "Spherical Directional Coordinate System" );
}

//---------------------------------------------------------------------------//
// end tstDirectionalCoordinateSystemType.cpp
//---------------------------------------------------------------------------//
