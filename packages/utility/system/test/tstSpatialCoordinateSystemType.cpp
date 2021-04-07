//---------------------------------------------------------------------------//
//!
//! \file   tstSpatialCoordinateSystemType.cpp
//! \author Alex Robinson
//! \brief  Spatial coordinate system type unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <string>

// FRENSIE Includes
#include "Utility_SpatialCoordinateSystemType.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the spatial coordinate system enums can be converted to strings
FRENSIE_UNIT_TEST( SpatialCoordinateSystemType, toString )
{
  std::string coord_system_name = 
    Utility::toString( Utility::CARTESIAN_SPATIAL_COORDINATE_SYSTEM );

  FRENSIE_CHECK_EQUAL( coord_system_name,
                       "Cartesian Spatial Coordinate System" );

  coord_system_name =
    Utility::toString( Utility::CYLINDRICAL_SPATIAL_COORDINATE_SYSTEM );

  FRENSIE_CHECK_EQUAL( coord_system_name,
                       "Cylindrical Spatial Coordinate System" );

  coord_system_name =
    Utility::toString( Utility::SPHERICAL_SPATIAL_COORDINATE_SYSTEM );

  FRENSIE_CHECK_EQUAL( coord_system_name,
                       "Spherical Spatial Coordinate System" );
}

//---------------------------------------------------------------------------//
// Check that the spatial coordinate system enums can be placed in a stream
FRENSIE_UNIT_TEST( SpatialCoordinateSystemType, toStream )
{
  std::ostringstream oss;
  
  Utility::toStream( oss, Utility::CARTESIAN_SPATIAL_COORDINATE_SYSTEM );

  FRENSIE_CHECK_EQUAL( oss.str(), "Cartesian Spatial Coordinate System" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::CYLINDRICAL_SPATIAL_COORDINATE_SYSTEM );

  FRENSIE_CHECK_EQUAL( oss.str(), "Cylindrical Spatial Coordinate System" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::SPHERICAL_SPATIAL_COORDINATE_SYSTEM );

  FRENSIE_CHECK_EQUAL( oss.str(), "Spherical Spatial Coordinate System" );
}

//---------------------------------------------------------------------------//
// Check that the spatial coordinate system enums can be placed in a stream
FRENSIE_UNIT_TEST( SpatialCoordinateSystemType, ostream_operator )
{
  std::ostringstream oss;
  oss << Utility::CARTESIAN_SPATIAL_COORDINATE_SYSTEM;

  FRENSIE_CHECK_EQUAL( oss.str(), "Cartesian Spatial Coordinate System" );

  oss.str( "" );
  oss.clear();

  oss << Utility::CYLINDRICAL_SPATIAL_COORDINATE_SYSTEM;

  FRENSIE_CHECK_EQUAL( oss.str(), "Cylindrical Spatial Coordinate System" );

  oss.str( "" );
  oss.clear();

  oss << Utility::SPHERICAL_SPATIAL_COORDINATE_SYSTEM;

  FRENSIE_CHECK_EQUAL( oss.str(), "Spherical Spatial Coordinate System" );
}

//---------------------------------------------------------------------------//
// end tstSpatialCoordinateSystemType.cpp
//---------------------------------------------------------------------------//
