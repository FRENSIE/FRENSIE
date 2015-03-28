//---------------------------------------------------------------------------//
//!
//! \file   tstArrayString.cpp
//! \author Alex Robinson
//! \brief  Array string unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_ArrayRCP.hpp>

// FRENSIE Includes
#include "Utility_ArrayString.hpp"

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the pi keyword can be replaced with the actual value
TEUCHOS_UNIT_TEST( ArrayString, locateAndReplacePi )
{
  std::string array_string( "{0.0, pi}" );

  Utility::ArrayString::locateAndReplacePi( array_string );

  TEST_EQUALITY_CONST( array_string, "{0.0,3.14159265358979312}" );

  array_string = "{0.0, 1*pi}";
  
  Utility::ArrayString::locateAndReplacePi( array_string );

  TEST_EQUALITY_CONST( array_string, "{0.0,3.14159265358979312}" );

  array_string = "{0.0, 2pi}";

  Utility::ArrayString::locateAndReplacePi( array_string );

  TEST_EQUALITY_CONST( array_string, "{0.0,6.28318530717958623}" );
  
  array_string = "{0.0, pi/2, 3pi / 4, pi, 2*pi}";

  Utility::ArrayString::locateAndReplacePi( array_string );

  TEST_EQUALITY_CONST( array_string, "{0.0,1.57079632679489656,2.35619449019234484,3.14159265358979312,6.28318530717958623}" );
}

//---------------------------------------------------------------------------//
// Check that the interval operator can be parsed
TEUCHOS_UNIT_TEST( ArrayString, locateAndReplaceIntervalOperator )
{
  std::string array_string( "{0.0, 2i, 1.0}" );

  Utility::ArrayString::locateAndReplaceIntervalOperator( array_string );

  TEST_EQUALITY_CONST( array_string, "{0.0,0.333333333333333315,0.66666666666666663, 1.0}" );

  array_string = "{-1.0, 3i, 1.0}";

  Utility::ArrayString::locateAndReplaceIntervalOperator( array_string );

  TEST_EQUALITY_CONST( array_string, "{-1.0,-0.5,0,0.5, 1.0}" );
}

//---------------------------------------------------------------------------//
// end tstArrayString.cpp
//---------------------------------------------------------------------------//
