//---------------------------------------------------------------------------//
//!
//! \file   tstParticleSourceDimensionType.cpp
//! \author Alex Robinson
//! \brief  Particle source dimension type enum unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <string>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleSourceDimensionType.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check if a particle source dimension name is valid
TEUCHOS_UNIT_TEST( ParticleSourceDimensionType,
                   isValidParticleSourceDimensionName )
{
  TEST_ASSERT( MonteCarlo::isValidParticleSourceDimensionName(
                                               "Primary Spatial Dimension" ) );
  TEST_ASSERT( MonteCarlo::isValidParticleSourceDimensionName(
                                             "Secondary Spatial Dimension" ) );
  TEST_ASSERT( MonteCarlo::isValidParticleSourceDimensionName(
                                              "Tertiary Spatial Dimension" ) );
  TEST_ASSERT( MonteCarlo::isValidParticleSourceDimensionName(
                                           "Primary Directional Dimension" ) );
  TEST_ASSERT( MonteCarlo::isValidParticleSourceDimensionName(
                                         "Secondary Directional Dimension" ) );
  TEST_ASSERT( MonteCarlo::isValidParticleSourceDimensionName(
                                          "Tertiary Directional Dimension" ) );
  TEST_ASSERT( MonteCarlo::isValidParticleSourceDimensionName(
                                                        "Energy Dimension" ) );
  TEST_ASSERT( MonteCarlo::isValidParticleSourceDimensionName(
                                                          "Time Dimension" ) );
  TEST_ASSERT( MonteCarlo::isValidParticleSourceDimensionName(
                                                        "Weight Dimension" ) );
  TEST_ASSERT( !MonteCarlo::isValidParticleSourceDimensionName(
                                                         "Dummy Dimension" ) );
}

//---------------------------------------------------------------------------//
// Check if a particle source dimension name can be converted to an enum
TEUCHOS_UNIT_TEST( ParticleSourceDimensionType,
                   convertParticleSourceDimensionNameToEnum )
{
  MonteCarlo::ParticleSourceDimensionType dimension =
    MonteCarlo::convertParticleSourceDimensionNameToEnum( "Primary Spatial Dimension" );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::PRIMARY_SPATIAL_PS_DIMENSION );

  dimension = MonteCarlo::convertParticleSourceDimensionNameToEnum( "Secondary Spatial Dimension" );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::SECONDARY_SPATIAL_PS_DIMENSION );

  dimension = MonteCarlo::convertParticleSourceDimensionNameToEnum( "Tertiary Spatial Dimension" );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::TERTIARY_SPATIAL_PS_DIMENSION );

  dimension = MonteCarlo::convertParticleSourceDimensionNameToEnum( "Primary Directional Dimension" );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::PRIMARY_DIRECTIONAL_PS_DIMENSION );

  dimension = MonteCarlo::convertParticleSourceDimensionNameToEnum( "Secondary Directional Dimension" );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::SECONDARY_DIRECTIONAL_PS_DIMENSION );

  dimension = MonteCarlo::convertParticleSourceDimensionNameToEnum( "Tertiary Directional Dimension" );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::TERTIARY_DIRECTIONAL_PS_DIMENSION );

  dimension = MonteCarlo::convertParticleSourceDimensionNameToEnum( "Energy Dimension" );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::ENERGY_PS_DIMENSION );

  dimension = MonteCarlo::convertParticleSourceDimensionNameToEnum( "Time Dimension" );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::TIME_PS_DIMENSION );

  dimension = MonteCarlo::convertParticleSourceDimensionNameToEnum( "Weight Dimension" );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::WEIGHT_PS_DIMENSION );

  TEST_THROW( MonteCarlo::convertParticleSourceDimensionNameToEnum( "Dummy Dimension" ),
              std::runtime_error );
}

//---------------------------------------------------------------------------//
// Check if a particle source dimension type enum can be converted to a string
TEUCHOS_UNIT_TEST( ParticleSourceDimensionType,
                   convertParticleSourceDimensionTypeEnumToString )
{
  std::string dimension_name =
    MonteCarlo::convertParticleSourceDimensionTypeEnumToString( MonteCarlo::PRIMARY_SPATIAL_PS_DIMENSION );

  TEST_EQUALITY_CONST( dimension_name, "Primary Spatial Dimension" );

  dimension_name = MonteCarlo::convertParticleSourceDimensionTypeEnumToString( MonteCarlo::SECONDARY_SPATIAL_PS_DIMENSION );

  TEST_EQUALITY_CONST( dimension_name, "Secondary Spatial Dimension" );

  dimension_name = MonteCarlo::convertParticleSourceDimensionTypeEnumToString( MonteCarlo::TERTIARY_SPATIAL_PS_DIMENSION );

  TEST_EQUALITY_CONST( dimension_name, "Tertiary Spatial Dimension" );

  dimension_name = MonteCarlo::convertParticleSourceDimensionTypeEnumToString( MonteCarlo::PRIMARY_DIRECTIONAL_PS_DIMENSION );

  TEST_EQUALITY_CONST( dimension_name, "Primary Directional Dimension" );

  dimension_name = MonteCarlo::convertParticleSourceDimensionTypeEnumToString( MonteCarlo::SECONDARY_DIRECTIONAL_PS_DIMENSION );

  TEST_EQUALITY_CONST( dimension_name, "Secondary Directional Dimension" );

  dimension_name = MonteCarlo::convertParticleSourceDimensionTypeEnumToString( MonteCarlo::TERTIARY_DIRECTIONAL_PS_DIMENSION );

  TEST_EQUALITY_CONST( dimension_name, "Tertiary Directional Dimension" );

  dimension_name = MonteCarlo::convertParticleSourceDimensionTypeEnumToString( MonteCarlo::ENERGY_PS_DIMENSION );

  TEST_EQUALITY_CONST( dimension_name, "Energy Dimension" );

  dimension_name = MonteCarlo::convertParticleSourceDimensionTypeEnumToString( MonteCarlo::TIME_PS_DIMENSION );

  TEST_EQUALITY_CONST( dimension_name, "Time Dimension" );

  dimension_name = MonteCarlo::convertParticleSourceDimensionTypeEnumToString( MonteCarlo::WEIGHT_PS_DIMENSION );

  TEST_EQUALITY_CONST( dimension_name, "Weight Dimension" );
}

//---------------------------------------------------------------------------//
// Check if the spatial dimension type enum can be converted to the
// equivalent particle source dimension enum
TEUCHOS_UNIT_TEST( ParticleSourceDimensionType,
                   convertSpatialDimensionToParticleSourceDimensionType )
{
  MonteCarlo::ParticleSourceDimensionType dimension =
    MonteCarlo::convertSpatialDimensionToParticleSourceDimensionType( Utility::X_SPATIAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::PRIMARY_SPATIAL_PS_DIMENSION );

  dimension = MonteCarlo::convertSpatialDimensionToParticleSourceDimensionType( Utility::Y_SPATIAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::SECONDARY_SPATIAL_PS_DIMENSION );

  dimension = MonteCarlo::convertSpatialDimensionToParticleSourceDimensionType( Utility::Z_SPATIAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::TERTIARY_SPATIAL_PS_DIMENSION );

  dimension = MonteCarlo::convertSpatialDimensionToParticleSourceDimensionType( Utility::R_SPATIAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::PRIMARY_SPATIAL_PS_DIMENSION );

  dimension = MonteCarlo::convertSpatialDimensionToParticleSourceDimensionType( Utility::AZIMUTHAL_ANGLE_SPATIAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::SECONDARY_SPATIAL_PS_DIMENSION );

  dimension = MonteCarlo::convertSpatialDimensionToParticleSourceDimensionType( Utility::POLAR_ANGLE_COSINE_SPATIAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::TERTIARY_SPATIAL_PS_DIMENSION );
}

//---------------------------------------------------------------------------//
// Check if the directional dimension type enum can be converted to the
// equivalent particle source dimension type enum
TEUCHOS_UNIT_TEST( ParticleSourceDimensionType,
                   convertDirectionalDimensionToParticleSourceDimensionType )
{
  MonteCarlo::ParticleSourceDimensionType dimension =
    MonteCarlo::convertDirectionalDimensionToParticleSourceDimensionType( Utility::U_DIRECTIONAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::PRIMARY_DIRECTIONAL_PS_DIMENSION );

  dimension = MonteCarlo::convertDirectionalDimensionToParticleSourceDimensionType( Utility::V_DIRECTIONAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::SECONDARY_DIRECTIONAL_PS_DIMENSION );

  dimension = MonteCarlo::convertDirectionalDimensionToParticleSourceDimensionType( Utility::W_DIRECTIONAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::TERTIARY_DIRECTIONAL_PS_DIMENSION );

  dimension = MonteCarlo::convertDirectionalDimensionToParticleSourceDimensionType( Utility::R_DIRECTIONAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::PRIMARY_DIRECTIONAL_PS_DIMENSION );

  dimension = MonteCarlo::convertDirectionalDimensionToParticleSourceDimensionType( Utility::AZIMUTHAL_ANGLE_DIRECTIONAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::SECONDARY_DIRECTIONAL_PS_DIMENSION );

  dimension = MonteCarlo::convertDirectionalDimensionToParticleSourceDimensionType( Utility::POLAR_ANGLE_COSINE_DIRECTIONAL_DIMENSION );

  TEST_EQUALITY_CONST( dimension, MonteCarlo::TERTIARY_DIRECTIONAL_PS_DIMENSION );
}

//---------------------------------------------------------------------------//
// Check if the particle source dimension type enum can be placed in a stream
TEUCHOS_UNIT_TEST( ParticleSourceDimensionType,
                   stream_operator )
{
  std::ostringstream oss;

  oss << MonteCarlo::PRIMARY_SPATIAL_PS_DIMENSION;

  TEST_EQUALITY_CONST( oss.str(), "Primary Spatial Dimension" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::SECONDARY_SPATIAL_PS_DIMENSION;

  TEST_EQUALITY_CONST( oss.str(), "Secondary Spatial Dimension" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::TERTIARY_SPATIAL_PS_DIMENSION;

  TEST_EQUALITY_CONST( oss.str(), "Tertiary Spatial Dimension" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::PRIMARY_DIRECTIONAL_PS_DIMENSION;

  TEST_EQUALITY_CONST( oss.str(), "Primary Directional Dimension" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::SECONDARY_DIRECTIONAL_PS_DIMENSION;

  TEST_EQUALITY_CONST( oss.str(), "Secondary Directional Dimension" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::TERTIARY_DIRECTIONAL_PS_DIMENSION;

  TEST_EQUALITY_CONST( oss.str(), "Tertiary Directional Dimension" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::ENERGY_PS_DIMENSION;

  TEST_EQUALITY_CONST( oss.str(), "Energy Dimension" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::TIME_PS_DIMENSION;

  TEST_EQUALITY_CONST( oss.str(), "Time Dimension" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::WEIGHT_PS_DIMENSION;

  TEST_EQUALITY_CONST( oss.str(), "Weight Dimension" );
}

//---------------------------------------------------------------------------//
// end tstParticleStateDimensionType.cpp
//---------------------------------------------------------------------------//
