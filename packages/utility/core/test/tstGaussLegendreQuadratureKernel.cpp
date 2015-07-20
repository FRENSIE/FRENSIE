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
#include <Teuchos_TwoDArray.hpp>

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

  number_of_moments = 13;
  legendre_moments.resize( number_of_moments );
  gauss_moments.resize( number_of_moments );

  legendre_moments[0] = 20.0/20.0;
  legendre_moments[1] = 19.0/20.0;
  legendre_moments[2] = 18.0/20.0;
  legendre_moments[3] = 17.0/20.0;
  legendre_moments[4] = 16.0/20.0;
  legendre_moments[5] = 15.0/20.0;
  legendre_moments[6] = 14.0/20.0;
  legendre_moments[7] = 13.0/20.0;
  legendre_moments[8] = 12.0/20.0;
  legendre_moments[9] = 11.0/20.0;
  legendre_moments[10] = 10.0/20.0;
  legendre_moments[11] = 9.0/20.0;
  legendre_moments[12] = 8.0/20.0;

  Utility::getGaussMoments( legendre_moments, gauss_moments );

  TEST_FLOATING_EQUALITY( gauss_moments[0], 1.0, 1e-15);
  TEST_FLOATING_EQUALITY( gauss_moments[1], 19.0/20.0, 1e-15);
  TEST_FLOATING_EQUALITY( gauss_moments[2], 14.0/15.0, 1e-15);
  TEST_FLOATING_EQUALITY( gauss_moments[3], 91.0/100.0, 1e-15);
  TEST_FLOATING_EQUALITY( gauss_moments[4], 157.0/175.0, 1e-15);
  TEST_FLOATING_EQUALITY( gauss_moments[5], 1109.0/1260.0, 1e-15);
  TEST_FLOATING_EQUALITY( gauss_moments[6], 1004.0/1155.0, 1e-15);
  TEST_FLOATING_EQUALITY( gauss_moments[7], 7339.0/8580.0, 1e-15);
  TEST_FLOATING_EQUALITY( gauss_moments[8], 27211.0/32175.0, 1e-15);
  TEST_FLOATING_EQUALITY( gauss_moments[9], 202673.0/243100.0, 1e-15);
  TEST_FLOATING_EQUALITY( gauss_moments[10], 190518.0/230945.0, 1e-15);
  TEST_FLOATING_EQUALITY( gauss_moments[11], 95731.0/117572.0, 1e-15);
  TEST_FLOATING_EQUALITY( gauss_moments[12], 544993.0/676039.0, 1e-15);

  number_of_moments = 9;
  gauss_moments.resize( number_of_moments );

  Utility::getGaussMoments( legendre_moments_8, gauss_moments );

  TEST_FLOATING_EQUALITY( gauss_moments[0], 1.000000000000000E+00, 1e-15);
  TEST_FLOATING_EQUALITY( gauss_moments[1], 9.999999955948290E-01, 1e-15);
  TEST_FLOATING_EQUALITY( gauss_moments[2], 9.999999915896570E-01, 1e-15);
  TEST_FLOATING_EQUALITY( gauss_moments[3], 9.999999875844880E-01, 1e-15);
  TEST_FLOATING_EQUALITY( gauss_moments[4], 9.999999837126500E-01, 1e-15);
  TEST_FLOATING_EQUALITY( gauss_moments[5], 9.999999798408140E-01, 1e-15);
  TEST_FLOATING_EQUALITY( gauss_moments[6], 9.999999760489760E-01, 1e-15);
  TEST_FLOATING_EQUALITY( gauss_moments[7], 9.999999722571400E-01, 1e-15);
  TEST_FLOATING_EQUALITY( gauss_moments[8], 9.999999685224460E-01, 1e-15);
}

//---------------------------------------------------------------------------//
// Check that the coefficients of the legendre expansion of x^n can be returned
TEUCHOS_UNIT_TEST( GaussLegendreQuadratureKernel,
		           getLegendrePowerExpansionCoefficients )
{
  int power = 9;
  Teuchos::TwoDArray<long double> coef( power+1, power+1 );

  Utility::getLegendrePowerExpansionCoefficients( coef, power );

  Teuchos::Array<double> coefs( power+1 );
  for ( int i = 0; i < power+1; i++ )
  {
    coefs[i] = coef[power][i];
  }

std::printf( "\n coef[0][0] =\t %.10e", coef[0][0]);
std::printf( "\n coef[1][0] =\t %.10e", coef[1][0]);
std::printf( "\n coef[1][1] =\t %.10e", coef[1][1]);
std::printf( "\n coef[power][1] =\t %.10e", coef[power][1]);
std::printf( "\n coef[power][3] =\t %.10e", coef[power][3]);
std::printf( "\n coef[power][5] =\t %.10e", coef[power][5]);
std::printf( "\n coef[power][7] =\t %.10e", coef[power][7]);


std::printf( "\n coefs[1] =\t %.10e", coefs[1]);
std::printf( "\n coefs[3] =\t %.10e", coefs[3]);
std::printf( "\n coefs[5] =\t %.10e", coefs[5]);
std::printf( "\n coefs[7] =\t %.10e", coefs[7]);

  TEST_EQUALITY_CONST( coefs[0], 0.0);
  TEST_FLOATING_EQUALITY( coefs[1], 3315.0/12155.0, 1e-15);
  TEST_EQUALITY_CONST( coefs[2], 0.0);
  TEST_FLOATING_EQUALITY( coefs[3], 4760.0/12155.0, 1e-15);
  TEST_EQUALITY_CONST( coefs[4], 0.0);
  TEST_FLOATING_EQUALITY( coefs[5], 2992.0/12155.0, 1e-15);
  TEST_EQUALITY_CONST( coefs[6], 0.0);
  TEST_FLOATING_EQUALITY( coefs[7], 960.0/12155.0, 1e-15);
  TEST_EQUALITY_CONST( coefs[8], 0.0);
  TEST_FLOATING_EQUALITY( coefs[9], 128.0/12155.0, 1e-15);
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
