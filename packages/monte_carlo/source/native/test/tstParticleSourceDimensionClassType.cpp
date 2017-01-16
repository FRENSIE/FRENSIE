//---------------------------------------------------------------------------//
//!
//! \file   tstParticleSourceDimensionClassType.cpp
//! \author Alex Robinson
//! \brief  Particle source dimension class type enum unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <string>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleSourceDimensionClassType.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check if the dimension class type enum can be converted to a string
TEUCHOS_UNIT_TEST( ParticleSourceDimensionClassType,
                   convertParticleSourceDimensionClassTypeEnumToString )
{
  std::string dimension_class_name =
    MonteCarlo::convertParticleSourceDimensionClassTypeEnumToString(
                                      MonteCarlo::SPATIAL_PS_DIMENSION_CLASS );

  TEST_EQUALITY_CONST( dimension_class_name, "Spatial Dimension Class" );

  dimension_class_name =
    MonteCarlo::convertParticleSourceDimensionClassTypeEnumToString(
                                  MonteCarlo::DIRECTIONAL_PS_DIMENSION_CLASS );

  TEST_EQUALITY_CONST( dimension_class_name, "Directional Dimension Class" );

  dimension_class_name =
    MonteCarlo::convertParticleSourceDimensionClassTypeEnumToString(
                                       MonteCarlo::ENERGY_PS_DIMENSION_CLASS );

  TEST_EQUALITY_CONST( dimension_class_name, "Energy Dimension Class" );

  dimension_class_name =
    MonteCarlo::convertParticleSourceDimensionClassTypeEnumToString(
                                         MonteCarlo::TIME_PS_DIMENSION_CLASS );

  TEST_EQUALITY_CONST( dimension_class_name, "Time Dimension Class" );

  dimension_class_name =
    MonteCarlo::convertParticleSourceDimensionClassTypeEnumToString(
                                       MonteCarlo::WEIGHT_PS_DIMENSION_CLASS );

  TEST_EQUALITY_CONST( dimension_class_name, "Weight Dimension Class" );
}

//---------------------------------------------------------------------------//
// Check if the dimension class type enum can be placed in a stream
TEUCHOS_UNIT_TEST( ParticleSourceDimensionClassType, stream_operator )
{
  std::ostringstream oss;

  oss << MonteCarlo::SPATIAL_PS_DIMENSION_CLASS;

  TEST_EQUALITY_CONST( oss.str(), "Spatial Dimension Class" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::DIRECTIONAL_PS_DIMENSION_CLASS;

  TEST_EQUALITY_CONST( oss.str(), "Directional Dimension Class" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::ENERGY_PS_DIMENSION_CLASS;

  TEST_EQUALITY_CONST( oss.str(), "Energy Dimension Class" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::TIME_PS_DIMENSION_CLASS;

  TEST_EQUALITY_CONST( oss.str(), "Time Dimension Class" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::WEIGHT_PS_DIMENSION_CLASS;

  TEST_EQUALITY_CONST( oss.str(), "Weight Dimension Class" );
}

//---------------------------------------------------------------------------//
// end tstParticleSourceDimensionClassType.cpp
//---------------------------------------------------------------------------//
