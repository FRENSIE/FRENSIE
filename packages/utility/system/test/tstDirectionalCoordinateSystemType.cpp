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

// FRENSIE Includes
#include "Utility_DirectionalCoordinateSystemType.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the directional coordinate system enums can be converted to
// strings
FRENSIE_UNIT_TEST( DirectionalCoordinateSystemType, toString )
{
  std::string coord_system_name =
    Utility::toString( Utility::CARTESIAN_DIRECTIONAL_COORDINATE_SYSTEM );

  FRENSIE_CHECK_EQUAL( coord_system_name,
                       "Cartesian Directional Coordinate System" );

  coord_system_name =
    Utility::toString( Utility::SPHERICAL_DIRECTIONAL_COORDINATE_SYSTEM );

  FRENSIE_CHECK_EQUAL( coord_system_name,
                       "Spherical Directional Coordinate System" );
}

//---------------------------------------------------------------------------//
// Check that the directional coordinate system enums can be placed in a stream
FRENSIE_UNIT_TEST( DirectionalCoordinateSystemType, toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, Utility::CARTESIAN_DIRECTIONAL_COORDINATE_SYSTEM );
  
  FRENSIE_CHECK_EQUAL( oss.str(), "Cartesian Directional Coordinate System" );

  oss.str( "" );
  oss.clear();
  
  Utility::toStream( oss, Utility::SPHERICAL_DIRECTIONAL_COORDINATE_SYSTEM );

  FRENSIE_CHECK_EQUAL( oss.str(), "Spherical Directional Coordinate System" );
}

//---------------------------------------------------------------------------//
// Check that the directional coordinate system enums can be placed in a stream
FRENSIE_UNIT_TEST( DirectionalCoordinateSystemType, ostream_operator )
{
  std::ostringstream oss;

  oss << Utility::CARTESIAN_DIRECTIONAL_COORDINATE_SYSTEM;
  
  FRENSIE_CHECK_EQUAL( oss.str(), "Cartesian Directional Coordinate System" );

  oss.str( "" );
  oss.clear();
  
  oss << Utility::SPHERICAL_DIRECTIONAL_COORDINATE_SYSTEM;

  FRENSIE_CHECK_EQUAL( oss.str(), "Spherical Directional Coordinate System" );
}

//---------------------------------------------------------------------------//
// end tstDirectionalCoordinateSystemType.cpp
//---------------------------------------------------------------------------//
