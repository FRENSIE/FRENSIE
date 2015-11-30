//---------------------------------------------------------------------------//
//!
//! \file   tstGaussLegendreQuadratureSet.cpp
//! \author Luke Kersting
//! \brief  Gauss-Legendre quadrature set unit tests.
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

// Boost Includes
#include <boost/multiprecision/cpp_dec_float.hpp>

// FRENSIE Includes
#include "Utility_GaussLegendreQuadratureSet.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

Teuchos::Array<Utility::long_float> legendre_moments_8( 9 );

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the Gauss moments can be returned
TEUCHOS_UNIT_TEST( GaussLegendreQuadratureSet,
		           getGaussMoments )
{

  //typedef boost::multiprecision::cpp_dec_float_100 long_float;

  int number_of_moments = 2;
  Teuchos::Array<Utility::long_float> legendre_moments( number_of_moments );
  Teuchos::Array<Utility::long_float> gauss_moments( number_of_moments );

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

  TEST_FLOATING_EQUALITY( gauss_moments[0].convert_to<double>(), 
                          1.0, 1e-15);
  TEST_FLOATING_EQUALITY( gauss_moments[1].convert_to<double>(),  
                          19.0/20.0, 1e-15);
  TEST_FLOATING_EQUALITY( gauss_moments[2].convert_to<double>(),  
                          14.0/15.0, 1e-15);
  TEST_FLOATING_EQUALITY( gauss_moments[3].convert_to<double>(),  
                          91.0/100.0, 1e-15);
  TEST_FLOATING_EQUALITY( gauss_moments[4].convert_to<double>(),  
                          157.0/175.0, 1e-15);
  TEST_FLOATING_EQUALITY( gauss_moments[5].convert_to<double>(),  
                          1109.0/1260.0, 1e-15);
  TEST_FLOATING_EQUALITY( gauss_moments[6].convert_to<double>(),  
                          1004.0/1155.0, 1e-15);
  TEST_FLOATING_EQUALITY( gauss_moments[7].convert_to<double>(),  
                          7339.0/8580.0, 1e-15);
  TEST_FLOATING_EQUALITY( gauss_moments[8].convert_to<double>(),  
                          27211.0/32175.0, 1e-15);
  TEST_FLOATING_EQUALITY( gauss_moments[9].convert_to<double>(),  
                          202673.0/243100.0, 1e-15);
  TEST_FLOATING_EQUALITY( gauss_moments[10].convert_to<double>(),  
                          190518.0/230945.0, 1e-15);
  TEST_FLOATING_EQUALITY( gauss_moments[11].convert_to<double>(),  
                          95731.0/117572.0, 1e-15);
  TEST_FLOATING_EQUALITY( gauss_moments[12].convert_to<double>(),  
                          544993.0/676039.0, 1e-15);

  number_of_moments = 9;
  gauss_moments.resize( number_of_moments );

  Utility::getGaussMoments( legendre_moments_8, gauss_moments );

  TEST_FLOATING_EQUALITY( gauss_moments[0].convert_to<double>(), 
                          2.597000000000000E+05, 1e-15);
  TEST_FLOATING_EQUALITY( gauss_moments[1].convert_to<double>(),  
                          2.596999988559773E+05, 1e-15);
  TEST_FLOATING_EQUALITY( gauss_moments[2].convert_to<double>(),  
                          2.596999978158346E+05, 1e-15);
  TEST_FLOATING_EQUALITY( gauss_moments[3].convert_to<double>(),  
                          2.596999967756919E+05, 1e-15);
  TEST_FLOATING_EQUALITY( gauss_moments[4].convert_to<double>(),  
                          2.596999957701758742857142857E+05, 1e-15);
  TEST_FLOATING_EQUALITY( gauss_moments[5].convert_to<double>(),  
                          2.596999947646598333333333333E+05, 1e-15);
  TEST_FLOATING_EQUALITY( gauss_moments[6].convert_to<double>(),  
                          2.596999937799198103896103896E+05, 1e-15);
  TEST_FLOATING_EQUALITY( gauss_moments[7].convert_to<double>(),  
                          2.596999927951797666666666667E+05, 1e-15);
  TEST_FLOATING_EQUALITY( gauss_moments[8].convert_to<double>(),  
                          2.596999918252797445221445221E+05, 1e-15);
}

//---------------------------------------------------------------------------//
// Check that the coefficients of the legendre expansion of x^n can be returned
TEUCHOS_UNIT_TEST( GaussLegendreQuadratureSet,
		           getLegendrePowerExpansionCoefficients )
{
  int power = 9;
  Teuchos::TwoDArray<Utility::long_float> coefs( power+1, power+1 );

  Utility::getLegendrePowerExpansionCoefficients( coefs, power );

  TEST_EQUALITY_CONST( coefs[power][0].convert_to<double>(), 0.0);
  TEST_FLOATING_EQUALITY( coefs[power][1].convert_to<double>(), 
                          3315.0/12155.0, 1e-15);
  TEST_EQUALITY_CONST( coefs[power][2].convert_to<double>(), 0.0);
  TEST_FLOATING_EQUALITY( coefs[power][3].convert_to<double>(),  
                          4760.0/12155.0, 1e-15);
  TEST_EQUALITY_CONST( coefs[power][4].convert_to<double>(), 0.0);
  TEST_FLOATING_EQUALITY( coefs[power][5].convert_to<double>(),  
                          2992.0/12155.0, 1e-15);
  TEST_EQUALITY_CONST( coefs[power][6].convert_to<double>(), 0.0);
  TEST_FLOATING_EQUALITY( coefs[power][7].convert_to<double>(),  
                          960.0/12155.0, 1e-15);
  TEST_EQUALITY_CONST( coefs[power][8].convert_to<double>(), 0.0);
  TEST_FLOATING_EQUALITY( coefs[power][9].convert_to<double>(),  
                          128.0/12155.0, 1e-15);
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

  legendre_moments_8[0] = 2.597000000000000E+05L;//2.597000000000000E+05;
  legendre_moments_8[1] = 2.596999988559773E+05L;//2.597000000000000E+05;
  legendre_moments_8[2] = 2.596999967237519E+05L;//2.597000000000000E+05;
  legendre_moments_8[3] = 2.596999936552638E+05L;//2.597000000000000E+05;
  legendre_moments_8[4] = 2.596999896851397E+05L;//2.597000000000000E+05;
  legendre_moments_8[5] = 2.596999848393495E+05L;//2.597000000000000E+05;
  legendre_moments_8[6] = 2.596999791386693E+05L;//2.597000000000000E+05;
  legendre_moments_8[7] = 2.596999726004124E+05L;//2.597000000000000E+05;
  legendre_moments_8[8] = 2.596999652394188E+05L;//2.597000000000000E+05;
   
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
// end tstGaussLegendreQuadratureSet.cpp
//---------------------------------------------------------------------------//
