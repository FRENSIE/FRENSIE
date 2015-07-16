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
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Utility_GaussLegendreQuadratureKernel.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

Teuchos::Array<double> legendre_moments_8( 9 );

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

  number_of_moments = 9;
  gauss_moments.resize( number_of_moments );

  Utility::getGaussMoments( legendre_moments_8, gauss_moments );

  TEST_FLOATING_EQUALITY( gauss_moments[0], 1.000000000000000E+00, 1e-12);
  TEST_FLOATING_EQUALITY( gauss_moments[1], 9.999999955948290E-01, 1e-12);
  TEST_FLOATING_EQUALITY( gauss_moments[2], 9.999999915896570E-01, 1e-12);
  TEST_FLOATING_EQUALITY( gauss_moments[3], 9.999999875844880E-01, 1e-12);
  TEST_FLOATING_EQUALITY( gauss_moments[4], 9.999999837126500E-01, 1e-12);
  TEST_FLOATING_EQUALITY( gauss_moments[5], 9.999999798408140E-01, 1e-12);
  TEST_FLOATING_EQUALITY( gauss_moments[6], 9.999999760489760E-01, 1e-12);
  TEST_FLOATING_EQUALITY( gauss_moments[7], 9.999999722571400E-01, 1e-12);
  TEST_FLOATING_EQUALITY( gauss_moments[8], 9.999999685224460E-01, 1e-12);
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
  TEST_FLOATING_EQUALITY( coef[1], 3315.0/12155.0, 1e-15);
  TEST_EQUALITY_CONST( coef[2], 0.0);
  TEST_FLOATING_EQUALITY( coef[3], 4760.0/12155.0, 1e-15);
  TEST_EQUALITY_CONST( coef[4], 0.0);
  TEST_FLOATING_EQUALITY( coef[5], 2992.0/12155.0, 1e-15);
  TEST_EQUALITY_CONST( coef[6], 0.0);
  TEST_FLOATING_EQUALITY( coef[7], 960.0/12155.0, 1e-15);
  TEST_EQUALITY_CONST( coef[8], 0.0);
  TEST_FLOATING_EQUALITY( coef[9], 128.0/12155.0, 1e-15);
}
//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{  
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  legendre_moments_8[0] = 2.597000000000000E+05/2.597000000000000E+05;
  legendre_moments_8[1] = 2.596999988559773E+05/2.597000000000000E+05;
  legendre_moments_8[2] = 2.596999967237519E+05/2.597000000000000E+05;
  legendre_moments_8[3] = 2.596999936552638E+05/2.597000000000000E+05;
  legendre_moments_8[4] = 2.596999896851397E+05/2.597000000000000E+05;
  legendre_moments_8[5] = 2.596999848393495E+05/2.597000000000000E+05;
  legendre_moments_8[6] = 2.596999791386693E+05/2.597000000000000E+05;
  legendre_moments_8[7] = 2.596999726004124E+05/2.597000000000000E+05;
  legendre_moments_8[8] = 2.596999652394188E+05/2.597000000000000E+05;
   
  // Run the unit tests
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  const bool success = Teuchos::UnitTestRepository::runUnitTests( *out );

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);  
}
//---------------------------------------------------------------------------//
// end tstGaussLegendreQuadratureKernel.cpp
//---------------------------------------------------------------------------//
