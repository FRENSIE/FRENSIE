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

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_SpatialDimensionType.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check if a spatial dimension name is valid
TEUCHOS_UNIT_TEST( SpatialDimensionType, isValidSpatialDimensionName )
{
  std::string dimension_name = "X Spatial Dimension";

  TEST_ASSERT( Utility::isValidSpatialDimensionName( dimension_name ) );

  dimension_name = "X Dimension";

  TEST_ASSERT( Utility::isValidSpatialDimensionName( dimension_name ) );

  dimension_name = "Y Spatial Dimension";

  TEST_ASSERT( Utility::isValidSpatialDimensionName( dimension_name ) );

  dimension_name = "Y Dimension";

  TEST_ASSERT( Utility::isValidSpatialDimensionName( dimension_name ) );

  dimension_name = "Z Spatial Dimension";

  TEST_ASSERT( Utility::isValidSpatialDimensionName( dimension_name ) );

  dimension_name = "Z Dimension";

  TEST_ASSERT( Utility::isValidSpatialDimensionName( dimension_name ) );

  dimension_name = "R Spatial Dimension";

  TEST_ASSERT( Utility::isValidSpatialDimensionName( dimension_name ) );

  dimension_name = "R Dimension";

  TEST_ASSERT( Utility::isValidSpatialDimensionName( dimension_name ) );

  dimension_name = "Azimuthal Angle Spatial Dimension";

  TEST_ASSERT( Utility::isValidSpatialDimensionName( dimension_name ) );

  dimension_name = "Polar Angle Cosine Spatial Dimension";

  TEST_ASSERT( Utility::isValidSpatialDimensionName( dimension_name ) );

  dimension_name = "Dummy Dimension";

  TEST_ASSERT( !Utility::isValidSpatialDimensionName( dimension_name ) );
}

//---------------------------------------------------------------------------//
// Check if a spatial dimension name can be converted to a spatial dimension
// type enum
TEUCHOS_UNIT_TEST( SpatialDimensionType, convertSpatialDimensionNameToEnum )
{
  Utility::SpatialDimensionType dimension =
    Utility::convertSpatialDimensionNameToEnum( "X Spatial Dimension" );

  TEST_EQUALITY_CONST( dimension, Utility::X_SPATIAL_DIMENSION );

  dimension = Utility::convertSpatialDimensionNameToEnum( "X Dimension" );

  TEST_EQUALITY_CONST( dimension, Utility::X_SPATIAL_DIMENSION );

  dimension =
    Utility::convertSpatialDimensionNameToEnum( "Y Spatial Dimension" );

  TEST_EQUALITY_CONST( dimension, Utility::Y_SPATIAL_DIMENSION );

  dimension = Utility::convertSpatialDimensionNameToEnum( "Y Dimension" );

  TEST_EQUALITY_CONST( dimension, Utility::Y_SPATIAL_DIMENSION );

  dimension =
    Utility::convertSpatialDimensionNameToEnum( "Z Spatial Dimension" );

  TEST_EQUALITY_CONST( dimension, Utility::Z_SPATIAL_DIMENSION );

  dimension = Utility::convertSpatialDimensionNameToEnum( "Z Dimension" );

  TEST_EQUALITY_CONST( dimension, Utility::Z_SPATIAL_DIMENSION );

  dimension =
    Utility::convertSpatialDimensionNameToEnum( "R Spatial Dimension" );

  TEST_EQUALITY_CONST( dimension, Utility::R_SPATIAL_DIMENSION );

  dimension = Utility::convertSpatialDimensionNameToEnum( "R Dimension" );

  TEST_EQUALITY_CONST( dimension, Utility::R_SPATIAL_DIMENSION );

  dimension = Utility::convertSpatialDimensionNameToEnum( "Azimuthal Angle Spatial Dimension" );

  TEST_EQUALITY_CONST( dimension, Utility::AZIMUTHAL_ANGLE_SPATIAL_DIMENSION );

  dimension = Utility::convertSpatialDimensionNameToEnum( "Polar Angle Cosine Spatial Dimension" );

  TEST_EQUALITY_CONST( dimension, Utility::POLAR_ANGLE_COSINE_SPATIAL_DIMENSION );

  TEST_THROW( Utility::convertSpatialDimensionNameToEnum( "Dummy Dimension" ),
              std::runtime_error );              
}

//---------------------------------------------------------------------------//
// Check if the spatial dimension type enum can be converted to a name
TEUCHOS_UNIT_TEST( SpatialDimensionType,
                   convertSpatialDimensionTypeEnumToString )
{
  std::string dimension_name =
    Utility::convertSpatialDimensionTypeEnumToString( Utility::X_SPATIAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension_name, "X Spatial Dimension" );

  dimension_name =
    Utility::convertSpatialDimensionTypeEnumToString( Utility::Y_SPATIAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension_name, "Y Spatial Dimension" );

  dimension_name =
    Utility::convertSpatialDimensionTypeEnumToString( Utility::Z_SPATIAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension_name, "Z Spatial Dimension" );

  dimension_name =
    Utility::convertSpatialDimensionTypeEnumToString( Utility::R_SPATIAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension_name, "R Spatial Dimension" );

  dimension_name =
    Utility::convertSpatialDimensionTypeEnumToString( Utility::AZIMUTHAL_ANGLE_SPATIAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension_name, "Azimuthal Angle Spatial Dimension" );

  dimension_name =
    Utility::convertSpatialDimensionTypeEnumToString( Utility::POLAR_ANGLE_COSINE_SPATIAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension_name, "Polar Angle Cosine Spatial Dimension" );
}

//---------------------------------------------------------------------------//
// Check if the spatial dimension type enum can be placed in a stream
TEUCHOS_UNIT_TEST( SpatialDimensionType, stream_operator )
{
  std::ostringstream oss;

  oss << Utility::X_SPATIAL_DIMENSION;

  TEST_EQUALITY_CONST( oss.str(), "X Spatial Dimension" );

  oss.str( "" );
  oss.clear();

  oss << Utility::Y_SPATIAL_DIMENSION;

  TEST_EQUALITY_CONST( oss.str(), "Y Spatial Dimension" );

  oss.str( "" );
  oss.clear();

  oss << Utility::Z_SPATIAL_DIMENSION;

  TEST_EQUALITY_CONST( oss.str(), "Z Spatial Dimension" );

  oss.str( "" );
  oss.clear();

  oss << Utility::R_SPATIAL_DIMENSION;

  TEST_EQUALITY_CONST( oss.str(), "R Spatial Dimension" );

  oss.str( "" );
  oss.clear();

  oss << Utility::AZIMUTHAL_ANGLE_SPATIAL_DIMENSION;

  TEST_EQUALITY_CONST( oss.str(), "Azimuthal Angle Spatial Dimension" );

  oss.str( "" );
  oss.clear();

  oss << Utility::POLAR_ANGLE_COSINE_SPATIAL_DIMENSION;

  TEST_EQUALITY_CONST( oss.str(), "Polar Angle Cosine Spatial Dimension" );
}

//---------------------------------------------------------------------------//
// end tstSpatialDimensionType.cpp
//---------------------------------------------------------------------------//
