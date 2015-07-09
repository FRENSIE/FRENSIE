//---------------------------------------------------------------------------//
//!
//! \file   tstGaussLegendreQuadratureKernel.cpp
//! \author Luke Kersting
//! \brief  Gauss-Legendre quadrature kernel unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Utility_GaussLegendreQuadratureKernel.hpp"

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the Gauss moments can be returned
TEUCHOS_UNIT_TEST( GaussLegendreQuadratureKernel,
		           getGaussMoments )
{

  int number_of_moments = 2;
  Teuchos::Array<double> legendre_moments( number_of_moments );
  Teuchos::Array<double> gauss_moments( number_of_moments );

  legendre_moments[0] = 1.0;
  legendre_moments[1] = 5.0;

  Utility::getGaussMoments( legendre_moments, gauss_moments );

  TEST_EQUALITY_CONST( gauss_moments[0], 1.0);
  TEST_EQUALITY_CONST( gauss_moments[1], 5.0);

  number_of_moments = 4;
  legendre_moments.resize( number_of_moments );
  gauss_moments.resize( number_of_moments );

  legendre_moments[0] = 1.0;
  legendre_moments[1] = 2.0;
  legendre_moments[2] = 4.0;
  legendre_moments[3] = 8.0;

  Utility::getGaussMoments( legendre_moments, gauss_moments );

  TEST_FLOATING_EQUALITY( gauss_moments[0], 1.0, 1e-12);
  TEST_FLOATING_EQUALITY( gauss_moments[1], 2.0, 1e-12);
  TEST_FLOATING_EQUALITY( gauss_moments[2], 3.0, 1e-12);
  TEST_FLOATING_EQUALITY( gauss_moments[3], 22.0/5.0, 1e-12);
}

//---------------------------------------------------------------------------//
// Check that the coefficients of the legendre expansion of x^n can be returned
TEUCHOS_UNIT_TEST( GaussLegendreQuadratureKernel,
		           getLegendrePowerExpansionCoefficients )
{
  int power = 1;
  Teuchos::Array<double> coef( power+1 );

  Utility::getLegendrePowerExpansionCoefficients( coef, power );

  TEST_EQUALITY_CONST( coef[0], 0.0);
  TEST_EQUALITY_CONST( coef[1], 1.0);

  power = 9;
  coef.resize( power+1 );

  Utility::getLegendrePowerExpansionCoefficients( coef, power );

  TEST_EQUALITY_CONST( coef[0], 0.0);
  TEST_FLOATING_EQUALITY( coef[1], 3315.0/12155.0, 1e-12);
  TEST_EQUALITY_CONST( coef[2], 0.0);
  TEST_FLOATING_EQUALITY( coef[3], 4760.0/12155.0, 1e-12);
  TEST_EQUALITY_CONST( coef[4], 0.0);
  TEST_FLOATING_EQUALITY( coef[5], 2992.0/12155.0, 1e-12);
  TEST_EQUALITY_CONST( coef[6], 0.0);
  TEST_FLOATING_EQUALITY( coef[7], 960.0/12155.0, 1e-12);
  TEST_EQUALITY_CONST( coef[8], 0.0);
  TEST_FLOATING_EQUALITY( coef[9], 128.0/12155.0, 1e-12);
}

//---------------------------------------------------------------------------//
// end tstGaussLegendreQuadratureKernel.cpp
//---------------------------------------------------------------------------//
