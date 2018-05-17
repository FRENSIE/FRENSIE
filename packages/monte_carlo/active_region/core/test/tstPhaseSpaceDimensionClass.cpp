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

// FRENSIE Includes
#include "MonteCarlo_PhaseSpaceDimensionClass.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Convert the dimension class to a string
FRENSIE_UNIT_TEST( PhaseSpaceDimensionClass, toString )
{
  std::string dimension_class_name = 
    Utility::toString( MonteCarlo::SPATIAL_DIMENSION_CLASS );

  FRENSIE_CHECK_EQUAL( dimension_class_name, "Spatial Dimension Class" );

  dimension_class_name = Utility::toString( MonteCarlo::DIRECTIONAL_DIMENSION_CLASS );

  FRENSIE_CHECK_EQUAL( dimension_class_name, "Directional Dimension Class" );

  dimension_class_name = Utility::toString( MonteCarlo::ENERGY_DIMENSION_CLASS );

  FRENSIE_CHECK_EQUAL( dimension_class_name, "Energy Dimension Class" );

  dimension_class_name = Utility::toString( MonteCarlo::TIME_DIMENSION_CLASS );

  FRENSIE_CHECK_EQUAL( dimension_class_name, "Time Dimension Class" );

  dimension_class_name = Utility::toString( MonteCarlo::WEIGHT_DIMENSION_CLASS );

  FRENSIE_CHECK_EQUAL( dimension_class_name, "Weight Dimension Class" );
}

//---------------------------------------------------------------------------//
// Place the dimension class in a stream
FRENSIE_UNIT_TEST( PhaseSpaceDimensionClass, stream_operator )
{
  std::ostringstream oss;
  oss << MonteCarlo::SPATIAL_DIMENSION_CLASS;

  FRENSIE_CHECK_EQUAL( oss.str(), "Spatial Dimension Class" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::DIRECTIONAL_DIMENSION_CLASS;

  FRENSIE_CHECK_EQUAL( oss.str(), "Directional Dimension Class" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::ENERGY_DIMENSION_CLASS;

  FRENSIE_CHECK_EQUAL( oss.str(), "Energy Dimension Class" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::TIME_DIMENSION_CLASS;

  FRENSIE_CHECK_EQUAL( oss.str(), "Time Dimension Class" );

  oss.str( "" );
  oss.clear();

  oss << MonteCarlo::WEIGHT_DIMENSION_CLASS;

  FRENSIE_CHECK_EQUAL( oss.str(), "Weight Dimension Class" );
}

//---------------------------------------------------------------------------//
// end tstPhaseSpaceDimensionClass.cpp
//---------------------------------------------------------------------------//
