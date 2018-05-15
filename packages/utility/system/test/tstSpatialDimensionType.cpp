//---------------------------------------------------------------------------//
//!
//! \file   tstSpatialDimensionType.cpp
//! \author Alex Robinson
//! \brief  Spatial dimension type enum unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <string>

// FRENSIE Includes
#include "Utility_SpatialDimensionType.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the spatial dimension type can be converted to a string
FRENSIE_UNIT_TEST( SpatialDimensionType, toString )
{
  std::string dimension_name = 
    Utility::toString( Utility::X_SPATIAL_DIMENSION );

  FRENSIE_CHECK_EQUAL( dimension_name, "X" );

  dimension_name = Utility::toString( Utility::Y_SPATIAL_DIMENSION );

  FRENSIE_CHECK_EQUAL( dimension_name, "Y" );

  dimension_name = Utility::toString( Utility::Z_SPATIAL_DIMENSION );

  FRENSIE_CHECK_EQUAL( dimension_name, "Z" );

  dimension_name = Utility::toString( Utility::R_SPATIAL_DIMENSION );

  FRENSIE_CHECK_EQUAL( dimension_name, "R" );

  dimension_name =
    Utility::toString( Utility::AZIMUTHAL_ANGLE_SPATIAL_DIMENSION );

  FRENSIE_CHECK_EQUAL( dimension_name, "Theta" );

  dimension_name =
    Utility::toString( Utility::POLAR_ANGLE_COSINE_SPATIAL_DIMENSION );

  FRENSIE_CHECK_EQUAL( dimension_name, "Mu" );
}

//---------------------------------------------------------------------------//
// Check that the spatial dimension type can be placed in a stream
FRENSIE_UNIT_TEST( SpatialDimensionType, toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, Utility::X_SPATIAL_DIMENSION );

  FRENSIE_CHECK_EQUAL( oss.str(), "X" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::Y_SPATIAL_DIMENSION );

  FRENSIE_CHECK_EQUAL( oss.str(), "Y" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::Z_SPATIAL_DIMENSION );

  FRENSIE_CHECK_EQUAL( oss.str(), "Z" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::R_SPATIAL_DIMENSION );

  FRENSIE_CHECK_EQUAL( oss.str(), "R" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::AZIMUTHAL_ANGLE_SPATIAL_DIMENSION );

  FRENSIE_CHECK_EQUAL( oss.str(), "Theta" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::POLAR_ANGLE_COSINE_SPATIAL_DIMENSION );

  FRENSIE_CHECK_EQUAL( oss.str(), "Mu" );
}

//---------------------------------------------------------------------------//
// Check that the spatial dimension type can be placed in a stream
FRENSIE_UNIT_TEST( SpatialDimensionType, ostream_operator )
{
  std::ostringstream oss;

  oss << Utility::X_SPATIAL_DIMENSION;

  FRENSIE_CHECK_EQUAL( oss.str(), "X" );

  oss.str( "" );
  oss.clear();

  oss << Utility::Y_SPATIAL_DIMENSION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Y" );

  oss.str( "" );
  oss.clear();

  oss << Utility::Z_SPATIAL_DIMENSION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Z" );

  oss.str( "" );
  oss.clear();

  oss << Utility::R_SPATIAL_DIMENSION;

  FRENSIE_CHECK_EQUAL( oss.str(), "R" );

  oss.str( "" );
  oss.clear();

  oss << Utility::AZIMUTHAL_ANGLE_SPATIAL_DIMENSION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Theta" );

  oss.str( "" );
  oss.clear();

  oss << Utility::POLAR_ANGLE_COSINE_SPATIAL_DIMENSION;

  FRENSIE_CHECK_EQUAL( oss.str(), "Mu" );
}

//---------------------------------------------------------------------------//
// Check that a spatial dimension name can be converted to a spatial dimension
// type enum
FRENSIE_UNIT_TEST( SpatialDimensionType, fromString )
{
  Utility::SpatialDimensionType dimension =
    Utility::fromString<Utility::SpatialDimensionType>( "X" );

  FRENSIE_CHECK_EQUAL( dimension, Utility::X_SPATIAL_DIMENSION );

  dimension = Utility::fromString<Utility::SpatialDimensionType>( "Y" );

  FRENSIE_CHECK_EQUAL( dimension, Utility::Y_SPATIAL_DIMENSION );

  dimension = Utility::fromString<Utility::SpatialDimensionType>( "Z" );

  FRENSIE_CHECK_EQUAL( dimension, Utility::Z_SPATIAL_DIMENSION );

  dimension = Utility::fromString<Utility::SpatialDimensionType>( "R" );

  FRENSIE_CHECK_EQUAL( dimension, Utility::R_SPATIAL_DIMENSION );

  dimension = Utility::fromString<Utility::SpatialDimensionType>( "Theta" );

  FRENSIE_CHECK_EQUAL( dimension, Utility::AZIMUTHAL_ANGLE_SPATIAL_DIMENSION );

  dimension = Utility::fromString<Utility::SpatialDimensionType>( "Mu" );

  FRENSIE_CHECK_EQUAL( dimension, Utility::POLAR_ANGLE_COSINE_SPATIAL_DIMENSION );

  FRENSIE_CHECK_THROW( Utility::fromString<Utility::SpatialDimensionType>( "Dummy Dimension" ),
                       std::runtime_error );              
}

//---------------------------------------------------------------------------//
// Check if a spatial dimension type can be extracted from a stream
FRENSIE_UNIT_TEST( SpatialDimensionType, fromStream )
{
  std::istringstream iss( "X" );
  
  Utility::SpatialDimensionType dimension;
  
  Utility::fromStream( iss, dimension );

  FRENSIE_CHECK_EQUAL( dimension, Utility::X_SPATIAL_DIMENSION );

  iss.str( "Y" );
  iss.clear();

  Utility::fromStream( iss, dimension );

  FRENSIE_CHECK_EQUAL( dimension, Utility::Y_SPATIAL_DIMENSION );

  iss.str( "Z" );
  iss.clear();

  Utility::fromStream( iss, dimension );

  FRENSIE_CHECK_EQUAL( dimension, Utility::Z_SPATIAL_DIMENSION );

  iss.str( "R" );
  iss.clear();

  Utility::fromStream( iss, dimension );

  FRENSIE_CHECK_EQUAL( dimension, Utility::R_SPATIAL_DIMENSION );

  iss.str( "Theta" );
  iss.clear();

  Utility::fromStream( iss, dimension );

  FRENSIE_CHECK_EQUAL( dimension, Utility::AZIMUTHAL_ANGLE_SPATIAL_DIMENSION );

  iss.str( "Mu" );
  iss.clear();

  Utility::fromStream( iss, dimension );

  FRENSIE_CHECK_EQUAL( dimension, Utility::POLAR_ANGLE_COSINE_SPATIAL_DIMENSION );

  iss.str( "Dummy Dimension" );
  iss.clear();
  
  FRENSIE_CHECK_THROW( Utility::fromStream( iss, dimension ),
                       std::runtime_error );              
}

//---------------------------------------------------------------------------//
// Check if a spatial dimension type can be extracted from a stream
FRENSIE_UNIT_TEST( SpatialDimensionType, istream_operator )
{
  std::istringstream iss( "X" );
  
  Utility::SpatialDimensionType dimension;
  
  iss >> dimension;

  FRENSIE_CHECK_EQUAL( dimension, Utility::X_SPATIAL_DIMENSION );

  iss.str( "Y" );
  iss.clear();

  iss >> dimension;

  FRENSIE_CHECK_EQUAL( dimension, Utility::Y_SPATIAL_DIMENSION );

  iss.str( "Z" );
  iss.clear();

  iss >> dimension;

  FRENSIE_CHECK_EQUAL( dimension, Utility::Z_SPATIAL_DIMENSION );

  iss.str( "R" );
  iss.clear();

  iss >> dimension;

  FRENSIE_CHECK_EQUAL( dimension, Utility::R_SPATIAL_DIMENSION );

  iss.str( "Theta" );
  iss.clear();

  iss >> dimension;

  FRENSIE_CHECK_EQUAL( dimension, Utility::AZIMUTHAL_ANGLE_SPATIAL_DIMENSION );

  iss.str( "Mu" );
  iss.clear();

  iss >> dimension;

  FRENSIE_CHECK_EQUAL( dimension, Utility::POLAR_ANGLE_COSINE_SPATIAL_DIMENSION );

  iss.str( "Dummy Dimension" );
  iss.clear();
  
  FRENSIE_CHECK_THROW( Utility::fromStream( iss, dimension ),
                       std::runtime_error );
}

//---------------------------------------------------------------------------//
// end tstSpatialDimensionType.cpp
//---------------------------------------------------------------------------//
