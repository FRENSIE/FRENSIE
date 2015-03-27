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

  TEST_EQUALITY_CONST( array_string, "{0.0, 3.14159265358979312}" );

  array_string = "{0.0, 2pi}";

  Utility::ArrayString::locateAndReplacePi( array_string );

  TEST_EQUALITY_CONST( array_string, "{0.0, 6.28318530717958623}" );

  array_string = "{0.0, pi, 2pi}";

  Utility::ArrayString::locateAndReplacePi( array_string );

  TEST_EQUALITY_CONST( array_string, 
		       "{0.0, 3.14159265358979312, 6.28318530717958623}" );
}

//---------------------------------------------------------------------------//
// Check 

//---------------------------------------------------------------------------//
// end tstArrayString.cpp
//---------------------------------------------------------------------------//
