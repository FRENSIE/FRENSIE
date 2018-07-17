//---------------------------------------------------------------------------//
//!
//! \file   tstGaussLegendreQuadratureSet.cpp
//! \author Luke Kersting
//! \brief  Gauss-Legendre quadrature set unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/multiprecision/cpp_dec_float.hpp>

// FRENSIE Includes
#include "Utility_GaussLegendreQuadratureSet.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::vector<Utility::long_float> legendre_moments_8( 9 );

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the Gauss moments can be returned
FRENSIE_UNIT_TEST( GaussLegendreQuadratureSet, getGaussMoments )
{

  //typedef boost::multiprecision::cpp_dec_float_100 long_float;

  int number_of_moments = 2;
  std::vector<Utility::long_float> legendre_moments( number_of_moments );
  std::vector<Utility::long_float> gauss_moments( number_of_moments );

  legendre_moments[0] = 1.0;
  legendre_moments[1] = 5.0;

  Utility::getGaussMoments( legendre_moments, gauss_moments );

  FRENSIE_CHECK_EQUAL( (double)gauss_moments[0], 1.0);
  FRENSIE_CHECK_EQUAL( (double)gauss_moments[1], 5.0);

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

  FRENSIE_CHECK_FLOATING_EQUALITY( gauss_moments[0].convert_to<double>(),
                          1.0, 1e-15);
  FRENSIE_CHECK_FLOATING_EQUALITY( gauss_moments[1].convert_to<double>(),
                          19.0/20.0, 1e-15);
  FRENSIE_CHECK_FLOATING_EQUALITY( gauss_moments[2].convert_to<double>(),
                          14.0/15.0, 1e-15);
  FRENSIE_CHECK_FLOATING_EQUALITY( gauss_moments[3].convert_to<double>(),
                          91.0/100.0, 1e-15);
  FRENSIE_CHECK_FLOATING_EQUALITY( gauss_moments[4].convert_to<double>(),
                          157.0/175.0, 1e-15);
  FRENSIE_CHECK_FLOATING_EQUALITY( gauss_moments[5].convert_to<double>(),
                          1109.0/1260.0, 1e-15);
  FRENSIE_CHECK_FLOATING_EQUALITY( gauss_moments[6].convert_to<double>(),
                          1004.0/1155.0, 1e-15);
  FRENSIE_CHECK_FLOATING_EQUALITY( gauss_moments[7].convert_to<double>(),
                          7339.0/8580.0, 1e-15);
  FRENSIE_CHECK_FLOATING_EQUALITY( gauss_moments[8].convert_to<double>(),
                          27211.0/32175.0, 1e-15);
  FRENSIE_CHECK_FLOATING_EQUALITY( gauss_moments[9].convert_to<double>(),
                          202673.0/243100.0, 1e-15);
  FRENSIE_CHECK_FLOATING_EQUALITY( gauss_moments[10].convert_to<double>(),
                          190518.0/230945.0, 1e-15);
  FRENSIE_CHECK_FLOATING_EQUALITY( gauss_moments[11].convert_to<double>(),
                          95731.0/117572.0, 1e-15);
  FRENSIE_CHECK_FLOATING_EQUALITY( gauss_moments[12].convert_to<double>(),
                          544993.0/676039.0, 1e-15);

  number_of_moments = 9;
  gauss_moments.resize( number_of_moments );

  Utility::getGaussMoments( legendre_moments_8, gauss_moments );

  FRENSIE_CHECK_FLOATING_EQUALITY( gauss_moments[0].convert_to<double>(),
                          2.597000000000000E+05, 1e-15);
  FRENSIE_CHECK_FLOATING_EQUALITY( gauss_moments[1].convert_to<double>(),
                          2.596999988559773E+05, 1e-15);
  FRENSIE_CHECK_FLOATING_EQUALITY( gauss_moments[2].convert_to<double>(),
                          2.596999978158346E+05, 1e-15);
  FRENSIE_CHECK_FLOATING_EQUALITY( gauss_moments[3].convert_to<double>(),
                          2.596999967756919E+05, 1e-15);
  FRENSIE_CHECK_FLOATING_EQUALITY( gauss_moments[4].convert_to<double>(),
                          2.596999957701758742857142857E+05, 1e-15);
  FRENSIE_CHECK_FLOATING_EQUALITY( gauss_moments[5].convert_to<double>(),
                          2.596999947646598333333333333E+05, 1e-15);
  FRENSIE_CHECK_FLOATING_EQUALITY( gauss_moments[6].convert_to<double>(),
                          2.596999937799198103896103896E+05, 1e-15);
  FRENSIE_CHECK_FLOATING_EQUALITY( gauss_moments[7].convert_to<double>(),
                          2.596999927951797666666666667E+05, 1e-15);
  FRENSIE_CHECK_FLOATING_EQUALITY( gauss_moments[8].convert_to<double>(),
                          2.596999918252797445221445221E+05, 1e-15);
}

//---------------------------------------------------------------------------//
// Check that the coefficients of the legendre expansion of x^n can be returned
FRENSIE_UNIT_TEST( GaussLegendreQuadratureSet,
                   getLegendrePowerExpansionCoefficients )
{
  int power = 9;
  std::vector<std::vector<Utility::long_float> > coeffs( power+1 );

  for( int i = 0; i <= power; ++i )
    coeffs[i].resize( power+1 );

  Utility::getLegendrePowerExpansionCoefficients( coeffs, power );

  FRENSIE_CHECK_EQUAL( coeffs[power][0].convert_to<double>(), 0.0);
  FRENSIE_CHECK_FLOATING_EQUALITY( coeffs[power][1].convert_to<double>(),
                          3315.0/12155.0, 1e-15);
  FRENSIE_CHECK_EQUAL( coeffs[power][2].convert_to<double>(), 0.0);
  FRENSIE_CHECK_FLOATING_EQUALITY( coeffs[power][3].convert_to<double>(),
                          4760.0/12155.0, 1e-15);
  FRENSIE_CHECK_EQUAL( coeffs[power][4].convert_to<double>(), 0.0);
  FRENSIE_CHECK_FLOATING_EQUALITY( coeffs[power][5].convert_to<double>(),
                          2992.0/12155.0, 1e-15);
  FRENSIE_CHECK_EQUAL( coeffs[power][6].convert_to<double>(), 0.0);
  FRENSIE_CHECK_FLOATING_EQUALITY( coeffs[power][7].convert_to<double>(),
                          960.0/12155.0, 1e-15);
  FRENSIE_CHECK_EQUAL( coeffs[power][8].convert_to<double>(), 0.0);
  FRENSIE_CHECK_FLOATING_EQUALITY( coeffs[power][9].convert_to<double>(),
                          128.0/12155.0, 1e-15);
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  legendre_moments_8[0] = 2.597000000000000E+05L;//2.597000000000000E+05;
  legendre_moments_8[1] = 2.596999988559773E+05L;//2.597000000000000E+05;
  legendre_moments_8[2] = 2.596999967237519E+05L;//2.597000000000000E+05;
  legendre_moments_8[3] = 2.596999936552638E+05L;//2.597000000000000E+05;
  legendre_moments_8[4] = 2.596999896851397E+05L;//2.597000000000000E+05;
  legendre_moments_8[5] = 2.596999848393495E+05L;//2.597000000000000E+05;
  legendre_moments_8[6] = 2.596999791386693E+05L;//2.597000000000000E+05;
  legendre_moments_8[7] = 2.596999726004124E+05L;//2.597000000000000E+05;
  legendre_moments_8[8] = 2.596999652394188E+05L;//2.597000000000000E+05;
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstGaussLegendreQuadratureSet.cpp
//---------------------------------------------------------------------------//
