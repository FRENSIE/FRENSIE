//---------------------------------------------------------------------------//
//!
//! \file   tstUnitBaseInterpolationPolicy.cpp
//! \author Alex Robinson
//! \brief  Unit Base interpolation policy unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_DataProcessingPolicy.hpp"
#include "Utility_UnitBaseInterpolationPolicy.hpp"

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the linear-linear-linear unit base interpolation policy between
// four points can be done
TEUCHOS_UNIT_TEST( UnitBaseLinLinLin, interpolate_raw )
{
  double x0 = 1.0, x1 = 10.0, x = 2.0;
  double y00 = 0.1, y01 = 1.0, y10 = 0.5, y11 = 10.0, y = 0.75;
  double z00 = 1e-25, z01 = 2e-25, z10 = 3e-25, z11 = 9e-25;
  double L0 = 5.0, L1 = 15.0;

  
}

//---------------------------------------------------------------------------//
// end tstUnitBaseInterpolationPolicy.cpp
//---------------------------------------------------------------------------//
