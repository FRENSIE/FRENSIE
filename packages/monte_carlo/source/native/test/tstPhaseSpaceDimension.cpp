//---------------------------------------------------------------------------//
//!
//! \file   tstPhaseSpaceDimension.cpp
//! \author Alex Robinson
//! \brief  Phase space dimension unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <string>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhaseSpaceDimension.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check if dimension names are valid
TEUCHOS_UNIT_TEST( PhaseSpaceDimension, isValidPhaseSpaceDimensionName )
{
  TEST_ASSERT( MonteCarlo::isValidPhaseSpaceDimensionName( "Primary Spatial Dimension" ) );
  TEST_ASSERT( MonteCarlo::isValidPhaseSpaceDimensionName( "Secondary Spatial Dimension" ) );
  TEST_ASSERT( MonteCarlo::isValidPhaseSpaceDimensionName( "Tertiary Spatial Dimension" ) );
  TEST_ASSERT( MonteCarlo::isValidPhaseSpaceDimensionName( "Primary Directional Dimension" ) );
  TEST_ASSERT( MonteCarlo::isValidPhaseSpaceDimensionName( "Secondary Directional Dimension" ) );
  TEST_ASSERT( MonteCarlo::isValidPhaseSpaceDimensionName( "Tertiary Directional Dimension" ) );
  TEST_ASSERT( MonteCarlo::isValidPhaseSpaceDimensionName( "Energy Dimension" ) );
  TEST_ASSERT( MonteCarlo::isValidPhaseSpaceDimensionName( "Time Dimension" ) );
  TEST_ASSERT( MonteCarlo::isValidPhaseSpaceDimensionName( "Weight Dimension" ) );
  TEST_ASSERT( !MonteCarlo::isValidPhaseSpaceDimensionName( "Dummy Dimension" ) );
}

//---------------------------------------------------------------------------//
// Check if a name can be converted to a dimension enum
TEUCHOS_UNIT_TEST( PhaseSpaceDimension, convertPhaseSpaceDimensionNameToEnum )
{
  MonteCarlo::PhaseSpaceDimension dimension =
    MonteCarlo::convertPhaseSpaceDimensionNameToEnum( "Primary Spatial Dimension" );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::PRIMARY_SPATIAL_DIMENSION );

  dimension = MonteCarlo::convertPhaseSpaceDimensionNameToEnum( "Secondary Spatial Dimension" );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::SECONDARY_SPATIAL_DIMENSION );

  dimension = MonteCarlo::convertPhaseSpaceDimensionNameToEnum( "Tertiary Spatial Dimension" );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::TERTIARY_SPATIAL_DIMENSION );

  dimension = MonteCarlo::convertPhaseSpaceDimensionNameToEnum( "Primary Directional Dimension" );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION );

  dimension = MonteCarlo::convertPhaseSpaceDimensionNameToEnum( "Secondary Directional Dimension" );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION );
  dimension = MonteCarlo::convertPhaseSpaceDimensionNameToEnum( "Tertiary Directional Dimension" );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION );

  dimension = MonteCarlo::convertPhaseSpaceDimensionNameToEnum( "Energy Dimension" );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::ENERGY_DIMENSION );

  dimension = MonteCarlo::convertPhaseSpaceDimensionNameToEnum( "Time Dimension" );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::TIME_DIMENSION );

  dimension = MonteCarlo::convertPhaseSpaceDimensionNameToEnum( "Weight Dimension" );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::WEIGHT_DIMENSION );
}

//---------------------------------------------------------------------------//
// Check if an unsigned int can be converted to a dimension enum
TEUCHOS_UNIT_TEST( PhaseSpaceDimension,
                   convertUnsignedToPhaseSpaceDimensionEnum )
{
  MonteCarlo::PhaseSpaceDimension dimension =
    MonteCarlo::convertUnsignedToPhaseSpaceDimensionEnum( 0 );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::PRIMARY_SPATIAL_DIMENSION );

  dimension = MonteCarlo::convertUnsignedToPhaseSpaceDimensionEnum( 1 );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::SECONDARY_SPATIAL_DIMENSION );
  
  dimension = MonteCarlo::convertUnsignedToPhaseSpaceDimensionEnum( 2 );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::TERTIARY_SPATIAL_DIMENSION );

  dimension = MonteCarlo::convertUnsignedToPhaseSpaceDimensionEnum( 3 );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION );

  dimension = MonteCarlo::convertUnsignedToPhaseSpaceDimensionEnum( 4 );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION );
  
  dimension = MonteCarlo::convertUnsignedToPhaseSpaceDimensionEnum( 5 );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION );

  dimension = MonteCarlo::convertUnsignedToPhaseSpaceDimensionEnum( 6 );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::ENERGY_DIMENSION );

  dimension = MonteCarlo::convertUnsignedToPhaseSpaceDimensionEnum( 7 );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::TIME_DIMENSION );

  dimension = MonteCarlo::convertUnsignedToPhaseSpaceDimensionEnum( 8 );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::WEIGHT_DIMENSION );
}

//---------------------------------------------------------------------------//
// Check if the dimension enum can be converted to a name
TEUCHOS_UNIT_TEST( PhaseSpaceDimension,
                   convertPhaseSpaceDimensionEnumToString )
{
  std::string dimension_name =
    MonteCarlo::convertPhaseSpaceDimensionEnumToString( MonteCarlo::PRIMARY_SPATIAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension_name, "Primary Spatial Dimension" );

  dimension_name = MonteCarlo::convertPhaseSpaceDimensionEnumToString( MonteCarlo::SECONDARY_SPATIAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension_name, "Secondary Spatial Dimension" );

  dimension_name = MonteCarlo::convertPhaseSpaceDimensionEnumToString( MonteCarlo::TERTIARY_SPATIAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension_name, "Tertiary Spatial Dimension" );

  dimension_name = MonteCarlo::convertPhaseSpaceDimensionEnumToString( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension_name, "Primary Directional Dimension" );

  dimension_name = MonteCarlo::convertPhaseSpaceDimensionEnumToString( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension_name, "Secondary Directional Dimension" );

  dimension_name = MonteCarlo::convertPhaseSpaceDimensionEnumToString( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension_name, "Tertiary Directional Dimension" );

  dimension_name = MonteCarlo::convertPhaseSpaceDimensionEnumToString( MonteCarlo::ENERGY_DIMENSION );

  TEST_EQUALITY_CONST( dimension_name, "Energy Dimension" );

  dimension_name = MonteCarlo::convertPhaseSpaceDimensionEnumToString( MonteCarlo::TIME_DIMENSION );

  TEST_EQUALITY_CONST( dimension_name, "Time Dimension" );
  
  dimension_name = MonteCarlo::convertPhaseSpaceDimensionEnumToString( MonteCarlo::WEIGHT_DIMENSION );

  TEST_EQUALITY_CONST( dimension_name, "Weight Dimension" );
}

//---------------------------------------------------------------------------//
// Check if the dimension enum can be converted to a basic name
TEUCHOS_UNIT_TEST( PhaseSpaceDimenion,
                   convertPhaseSpaceDimensionEnumToBasicString )
{
  std::string dimension_name =
    MonteCarlo::convertPhaseSpaceDimensionEnumToBasicString( MonteCarlo::PRIMARY_SPATIAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension_name, "PRIMARY_SPATIAL_DIMENSION" );

  dimension_name = MonteCarlo::convertPhaseSpaceDimensionEnumToBasicString( MonteCarlo::SECONDARY_SPATIAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension_name, "SECONDARY_SPATIAL_DIMENSION" );

  dimension_name = MonteCarlo::convertPhaseSpaceDimensionEnumToBasicString( MonteCarlo::TERTIARY_SPATIAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension_name, "TERTIARY_SPATIAL_DIMENSION" );

  dimension_name = MonteCarlo::convertPhaseSpaceDimensionEnumToBasicString( MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension_name, "PRIMARY_DIRECTIONAL_DIMENSION" );

  dimension_name = MonteCarlo::convertPhaseSpaceDimensionEnumToBasicString( MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension_name, "SECONDARY_DIRECTIONAL_DIMENSION" );

  dimension_name = MonteCarlo::convertPhaseSpaceDimensionEnumToBasicString( MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension_name, "TERTIARY_DIRECTIONAL_DIMENSION" );

  dimension_name = MonteCarlo::convertPhaseSpaceDimensionEnumToBasicString( MonteCarlo::ENERGY_DIMENSION );

  TEST_EQUALITY_CONST( dimension_name, "ENERGY_DIMENSION" );

  dimension_name = MonteCarlo::convertPhaseSpaceDimensionEnumToBasicString( MonteCarlo::TIME_DIMENSION );

  TEST_EQUALITY_CONST( dimension_name, "TIME_DIMENSION" );
  
  dimension_name = MonteCarlo::convertPhaseSpaceDimensionEnumToBasicString( MonteCarlo::WEIGHT_DIMENSION );

  TEST_EQUALITY_CONST( dimension_name, "WEIGHT_DIMENSION" );
}

//---------------------------------------------------------------------------//
// Check if the spatial dimension enum can be converted to a phase space
// dimension enum
TEUCHOS_UNIT_TEST( PhaseSpaceDimension,
                   convertSpatialDimensionToPhaseSpaceDimension )
{
  MonteCarlo::PhaseSpaceDimension dimension =
    MonteCarlo::convertSpatialDimensionToPhaseSpaceDimension( Utility::X_SPATIAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::PRIMARY_SPATIAL_DIMENSION );

  dimension = MonteCarlo::convertSpatialDimensionToPhaseSpaceDimension( Utility::Y_SPATIAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::SECONDARY_SPATIAL_DIMENSION );

  dimension = MonteCarlo::convertSpatialDimensionToPhaseSpaceDimension( Utility::Z_SPATIAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::TERTIARY_SPATIAL_DIMENSION );

  dimension = MonteCarlo::convertSpatialDimensionToPhaseSpaceDimension( Utility::R_SPATIAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::PRIMARY_SPATIAL_DIMENSION );

  dimension = MonteCarlo::convertSpatialDimensionToPhaseSpaceDimension( Utility::AZIMUTHAL_ANGLE_SPATIAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::SECONDARY_SPATIAL_DIMENSION );

  dimension = MonteCarlo::convertSpatialDimensionToPhaseSpaceDimension( Utility::POLAR_ANGLE_COSINE_SPATIAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::TERTIARY_SPATIAL_DIMENSION );
}

//---------------------------------------------------------------------------//
// Check if a directional dimension enum can be converted to a phase space
// dimension enum
TEUCHOS_UNIT_TEST( PhaseSpaceDimension,
                   convertDirectionalDimensionToPhaseSpaceDimension )
{
  MonteCarlo::PhaseSpaceDimension dimension =
    MonteCarlo::convertDirectionalDimensionToPhaseSpaceDimension( Utility::U_DIRECTIONAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION );

  dimension = MonteCarlo::convertDirectionalDimensionToPhaseSpaceDimension( Utility::V_DIRECTIONAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION );

  dimension = MonteCarlo::convertDirectionalDimensionToPhaseSpaceDimension( Utility::W_DIRECTIONAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION );

  dimension = MonteCarlo::convertDirectionalDimensionToPhaseSpaceDimension( Utility::R_DIRECTIONAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION );

  dimension = MonteCarlo::convertDirectionalDimensionToPhaseSpaceDimension( Utility::AZIMUTHAL_ANGLE_DIRECTIONAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION );

  dimension = MonteCarlo::convertDirectionalDimensionToPhaseSpaceDimension( Utility::POLAR_ANGLE_COSINE_DIRECTIONAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION );
}

//---------------------------------------------------------------------------//
// Check if a dimension enum can be placed in a stream
TEUCHOS_UNIT_TEST( PhaseSpaceDimension, stream_operator )
{
  std::ostringstream oss;

  oss << MonteCarlo::PRIMARY_SPATIAL_DIMENSION;

  TEST_EQUALITY_CONST( oss.str(), "Primary Spatial Dimension" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::SECONDARY_SPATIAL_DIMENSION;

  TEST_EQUALITY_CONST( oss.str(), "Secondary Spatial Dimension" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::TERTIARY_SPATIAL_DIMENSION;

  TEST_EQUALITY_CONST( oss.str(), "Tertiary Spatial Dimension" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION;

  TEST_EQUALITY_CONST( oss.str(), "Primary Directional Dimension" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION;

  TEST_EQUALITY_CONST( oss.str(), "Secondary Directional Dimension" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION;

  TEST_EQUALITY_CONST( oss.str(), "Tertiary Directional Dimension" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::ENERGY_DIMENSION;

  TEST_EQUALITY_CONST( oss.str(), "Energy Dimension" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::TIME_DIMENSION;

  TEST_EQUALITY_CONST( oss.str(), "Time Dimension" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::WEIGHT_DIMENSION;

  TEST_EQUALITY_CONST( oss.str(), "Weight Dimension" );
}                   

//---------------------------------------------------------------------------//
// end tstPhaseSpaceDimension.cpp
//---------------------------------------------------------------------------//
