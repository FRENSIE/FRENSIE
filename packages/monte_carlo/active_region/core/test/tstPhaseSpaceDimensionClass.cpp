//---------------------------------------------------------------------------//
//!
//! \file   tstPhaseSpaceDimensionClass.cpp
//! \author Alex Robinson
//! \brief  Phase space dimension class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <string>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhaseSpaceDimensionClass.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Convert the dimension class to a string
TEUCHOS_UNIT_TEST( PhaseSpaceDimensionClass,
                   convertPhaseSpaceDimensionClassEnumToString )
{
  std::string dimension_class_name = 
    MonteCarlo::convertPhaseSpaceDimensionClassEnumToString( MonteCarlo::SPATIAL_DIMENSION_CLASS );

  TEST_EQUALITY_CONST( dimension_class_name, "Spatial Dimension Class" );

  dimension_class_name = MonteCarlo::convertPhaseSpaceDimensionClassEnumToString( MonteCarlo::DIRECTIONAL_DIMENSION_CLASS );

  TEST_EQUALITY_CONST( dimension_class_name, "Directional Dimension Class" );

  dimension_class_name = MonteCarlo::convertPhaseSpaceDimensionClassEnumToString( MonteCarlo::ENERGY_DIMENSION_CLASS );

  TEST_EQUALITY_CONST( dimension_class_name, "Energy Dimension Class" );

  dimension_class_name = MonteCarlo::convertPhaseSpaceDimensionClassEnumToString( MonteCarlo::TIME_DIMENSION_CLASS );

  TEST_EQUALITY_CONST( dimension_class_name, "Time Dimension Class" );

  dimension_class_name = MonteCarlo::convertPhaseSpaceDimensionClassEnumToString( MonteCarlo::WEIGHT_DIMENSION_CLASS );

  TEST_EQUALITY_CONST( dimension_class_name, "Weight Dimension Class" );
}

//---------------------------------------------------------------------------//
// Place the dimension class in a stream
TEUCHOS_UNIT_TEST( PhaseSpaceDimensionClass, stream_operator )
{
  std::ostringstream oss;
  oss << MonteCarlo::SPATIAL_DIMENSION_CLASS;

  TEST_EQUALITY_CONST( oss.str(), "Spatial Dimension Class" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::DIRECTIONAL_DIMENSION_CLASS;

  TEST_EQUALITY_CONST( oss.str(), "Directional Dimension Class" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::ENERGY_DIMENSION_CLASS;

  TEST_EQUALITY_CONST( oss.str(), "Energy Dimension Class" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::TIME_DIMENSION_CLASS;

  TEST_EQUALITY_CONST( oss.str(), "Time Dimension Class" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::WEIGHT_DIMENSION_CLASS;

  TEST_EQUALITY_CONST( oss.str(), "Weight Dimension Class" );
}

//---------------------------------------------------------------------------//
// end tstPhaseSpaceDimensionClass.cpp
//---------------------------------------------------------------------------//
