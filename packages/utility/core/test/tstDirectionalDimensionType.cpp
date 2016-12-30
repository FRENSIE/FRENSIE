//---------------------------------------------------------------------------//
//!
//! \file   tstDirectionalDimensionType.cpp
//! \author Alex Robinson
//! \brief  Directional dimension type enum unit tests.
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
#include "Utility_DirectionalDimensionType.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check if a directional dimension name is valid
TEUCHOS_UNIT_TEST( DirectionalDimensionType, isValidDirectionalDimensionName )
{
  std::string dimension_name = "U Directional Dimension";

  TEST_ASSERT( Utility::isValidDirectionalDimensionName( dimension_name ) );

  dimension_name = "U Dimension";

  TEST_ASSERT( Utility::isValidDirectionalDimensionName( dimension_name ) );

  dimension_name = "V Directional Dimension";

  TEST_ASSERT( Utility::isValidDirectionalDimensionName( dimension_name ) );

  dimension_name = "V Dimension";

  TEST_ASSERT( Utility::isValidDirectionalDimensionName( dimension_name ) );

  dimension_name = "W Directional Dimension";

  TEST_ASSERT( Utility::isValidDirectionalDimensionName( dimension_name ) );

  dimension_name = "W Dimension";

  TEST_ASSERT( Utility::isValidDirectionalDimensionName( dimension_name ) );

  dimension_name = "R Directional Dimension";

  TEST_ASSERT( Utility::isValidDirectionalDimensionName( dimension_name ) );

  dimension_name = "Azimuthal Angle Directional Dimension";

  TEST_ASSERT( Utility::isValidDirectionalDimensionName( dimension_name ) );

  dimension_name = "Polar Angle Cosine Directional Dimension";

  TEST_ASSERT( Utility::isValidDirectionalDimensionName( dimension_name ) );

  dimension_name = "Dummy Dimension";

  TEST_ASSERT( !Utility::isValidDirectionalDimensionName( dimension_name ) );
}

//---------------------------------------------------------------------------//
// Check if a directional dimension name can be converted to a directional
// dimension type enum
TEUCHOS_UNIT_TEST( DirectionalDimensionType,
                   convertDirectionalDimensionNameToEnum )
{
  Utility::DirectionalDimensionType dimension =
    Utility::convertDirectionalDimensionNameToEnum( "U Directional Dimension" );

  TEST_EQUALITY_CONST( dimension, Utility::U_DIRECTIONAL_DIMENSION );

  dimension = Utility::convertDirectionalDimensionNameToEnum( "U Dimension" );

  TEST_EQUALITY_CONST( dimension, Utility::U_DIRECTIONAL_DIMENSION );

  dimension = Utility::convertDirectionalDimensionNameToEnum( "V Directional Dimension" );

  TEST_EQUALITY_CONST( dimension, Utility::V_DIRECTIONAL_DIMENSION );

  dimension = Utility::convertDirectionalDimensionNameToEnum( "V Dimension" );

  TEST_EQUALITY_CONST( dimension, Utility::V_DIRECTIONAL_DIMENSION );

  dimension = Utility::convertDirectionalDimensionNameToEnum( "W Directional Dimension" );

  TEST_EQUALITY_CONST( dimension, Utility::W_DIRECTIONAL_DIMENSION );

  dimension = Utility::convertDirectionalDimensionNameToEnum( "W Dimension" );

  TEST_EQUALITY_CONST( dimension, Utility::W_DIRECTIONAL_DIMENSION );

  dimension = Utility::convertDirectionalDimensionNameToEnum( "R Directional Dimension" );

  TEST_EQUALITY_CONST( dimension, Utility::R_DIRECTIONAL_DIMENSION );

  dimension = Utility::convertDirectionalDimensionNameToEnum( "Azimuthal Angle Directional Dimension" );

  TEST_EQUALITY_CONST( dimension, Utility::AZIMUTHAL_ANGLE_DIRECTIONAL_DIMENSION );

  dimension = Utility::convertDirectionalDimensionNameToEnum( "Polar Angle Cosine Directional Dimension" );

  TEST_EQUALITY_CONST( dimension, Utility::POLAR_ANGLE_COSINE_DIRECTIONAL_DIMENSION );

  TEST_THROW( Utility::convertDirectionalDimensionNameToEnum( "Dummy Dimension" ),
              std::runtime_error );       
}

//---------------------------------------------------------------------------//
// Check if a directional dimension type enum can be converted to a name
TEUCHOS_UNIT_TEST( DirectionalDimensionType,
                   convertDirectionalDimensionTypeEnumToString )
{
  std::string dimension_name =
    Utility::convertDirectionalDimensionTypeEnumToString( Utility::U_DIRECTIONAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension_name, "U Directional Dimension" );

  dimension_name =
    Utility::convertDirectionalDimensionTypeEnumToString( Utility::V_DIRECTIONAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension_name, "V Directional Dimension" );

  dimension_name =
    Utility::convertDirectionalDimensionTypeEnumToString( Utility::W_DIRECTIONAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension_name, "W Directional Dimension" );

  dimension_name =
    Utility::convertDirectionalDimensionTypeEnumToString( Utility::R_DIRECTIONAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension_name, "R Directional Dimension" );

  dimension_name =
    Utility::convertDirectionalDimensionTypeEnumToString( Utility::AZIMUTHAL_ANGLE_DIRECTIONAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension_name, "Azimuthal Angle Directional Dimension" );

  dimension_name =
    Utility::convertDirectionalDimensionTypeEnumToString( Utility::POLAR_ANGLE_COSINE_DIRECTIONAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension_name, "Polar Angle Cosine Directional Dimension" );
}

//---------------------------------------------------------------------------//
// Check if the directional dimension type enum can be placed in a stream
TEUCHOS_UNIT_TEST( DirectionalDimensionType, stream_operator )
{
  std::ostringstream oss;

  oss << Utility::U_DIRECTIONAL_DIMENSION;

  TEST_EQUALITY_CONST( oss.str(), "U Directional Dimension" );

  oss.str( "" );
  oss.clear();

  oss << Utility::V_DIRECTIONAL_DIMENSION;

  TEST_EQUALITY_CONST( oss.str(), "V Directional Dimension" );

  oss.str( "" );
  oss.clear();

  oss << Utility::W_DIRECTIONAL_DIMENSION;

  TEST_EQUALITY_CONST( oss.str(), "W Directional Dimension" );

  oss.str( "" );
  oss.clear();

  oss << Utility::R_DIRECTIONAL_DIMENSION;

  TEST_EQUALITY_CONST( oss.str(), "R Directional Dimension" );

  oss.str( "" );
  oss.clear();

  oss << Utility::AZIMUTHAL_ANGLE_DIRECTIONAL_DIMENSION;

  TEST_EQUALITY_CONST( oss.str(), "Azimuthal Angle Directional Dimension" );

  oss.str( "" );
  oss.clear();

  oss << Utility::POLAR_ANGLE_COSINE_DIRECTIONAL_DIMENSION;

  TEST_EQUALITY_CONST( oss.str(), "Polar Angle Cosine Directional Dimension" );
}

//---------------------------------------------------------------------------//
// end tstDirectionalDimensionType.cpp
//---------------------------------------------------------------------------//
