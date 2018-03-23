//---------------------------------------------------------------------------//
//!
//! \file   tstSloanRadauQuadrature.cpp
//! \author Luke Kersting
//! \brief  Sloan implentation of Gauss-Radau quadrature unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <iomanip>
#include <limits>
#include <memory>

// FRENSIE Includes
#include "Utility_SloanRadauQuadrature.hpp"
#include "Utility_LegendrePolynomial.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

// P_4 expansion test variables
std::vector<Utility::long_float> legendre_moments( 5 ),
  radau_moments( 4 ), weights_4( 3 ),
  normalization_factors_N( 3 ), normalization_ratios( 3 ),
  variances( 3 ), mean_coefficients( 3 );

std::vector<std::vector<Utility::long_float> > orthogonal_coefficients( 3, std::vector<Utility::long_float>( 3 ) );
std::vector<std::vector<Utility::long_float> > roots( 3, std::vector<Utility::long_float>( 2 ) );

// P_8 expansion test variables
std::vector<Utility::long_float> legendre_moments_8( 9 ),
  radau_moments_8( 8 ), weights_8( 5 ),
  normalization_factors_N_8( 5 ), normalization_ratios_8( 5 ),
  variances_8( 5 ), mean_coefficients_8( 5 );

std::vector<std::vector<Utility::long_float> > roots_8( 5, std::vector<Utility::long_float>( 4 ) );

// Moments from nodes and weights
std::vector<Utility::long_float> test_roots( 8 );
std::vector<Utility::long_float> test_legendre( 17 );
Utility::long_float test_weight;

std::shared_ptr<Utility::SloanRadauQuadrature> quadrature,
                                            quadrature_8,
                                            test_quadrature;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the Radau moments can be returned
FRENSIE_UNIT_TEST( SloanRadauQuadrature, getRadauMoments )
{
  int number_of_moments = 4;
  std::vector<Utility::long_float> legendre_moment( number_of_moments+1 );
  std::vector<Utility::long_float> radau_moment( number_of_moments );

  legendre_moment[0] = Utility::long_float(1);
  legendre_moment[1] = Utility::long_float(19)/20;
  legendre_moment[2] = Utility::long_float(18)/20;
  legendre_moment[3] = Utility::long_float(17)/20;
  legendre_moment[4] = Utility::long_float(16)/20;

  Utility::SloanRadauQuadrature quadrature2( legendre_moment );

  quadrature2.getRadauMoments( radau_moment );

  FRENSIE_CHECK_FLOATING_EQUALITY( radau_moment[0].convert_to<double>(),
                          .05,
                          1e-14);
  FRENSIE_CHECK_FLOATING_EQUALITY( radau_moment[1].convert_to<double>(),
                          1.0/60.0,
                          1e-14);
  FRENSIE_CHECK_FLOATING_EQUALITY( radau_moment[2].convert_to<double>(),
                          14.0/15.0 - 91.0/100.0,
                          1e-14);
  FRENSIE_CHECK_FLOATING_EQUALITY( radau_moment[3].convert_to<double>(),
                          91.0/100.0 - 157.0/175.0, 1e-14);

  number_of_moments = 8;
  radau_moment.resize( number_of_moments );

  quadrature_8->getRadauMoments( radau_moment );

  FRENSIE_CHECK_FLOATING_EQUALITY( radau_moment[0].convert_to<double>(),
                          radau_moments_8[0].convert_to<double>(),
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( radau_moment[1].convert_to<double>(),
                          radau_moments_8[1].convert_to<double>(),
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( radau_moment[2].convert_to<double>(),
                          radau_moments_8[2].convert_to<double>(),
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( radau_moment[3].convert_to<double>(),
                          radau_moments_8[3].convert_to<double>(),
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( radau_moment[4].convert_to<double>(),
                          radau_moments_8[4].convert_to<double>(),
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( radau_moment[5].convert_to<double>(),
                          radau_moments_8[5].convert_to<double>(),
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( radau_moment[6].convert_to<double>(),
                          radau_moments_8[6].convert_to<double>(),
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( radau_moment[7].convert_to<double>(),
                          radau_moments_8[7].convert_to<double>(),
                          1e-14 );

}

//---------------------------------------------------------------------------//
// Check that the Long Radau moments can be returned
FRENSIE_UNIT_TEST( SloanRadauQuadrature, getLongRadauMoments )
{
  int number_of_radau_moments = 8;
  std::vector<Utility::long_float> radau_moment( number_of_radau_moments );

  quadrature_8->getLongRadauMoments( radau_moment );

  FRENSIE_CHECK_FLOATING_EQUALITY( radau_moment[0].convert_to<double>(),
                          radau_moments_8[0].convert_to<double>(),
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( radau_moment[1].convert_to<double>(),
                          radau_moments_8[1].convert_to<double>(),
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( radau_moment[2].convert_to<double>(),
                          radau_moments_8[2].convert_to<double>(),
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( radau_moment[3].convert_to<double>(),
                          radau_moments_8[3].convert_to<double>(),
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( radau_moment[4].convert_to<double>(),
                          radau_moments_8[4].convert_to<double>(),
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( radau_moment[5].convert_to<double>(),
                          radau_moments_8[5].convert_to<double>(),
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( radau_moment[6].convert_to<double>(),
                          radau_moments_8[6].convert_to<double>(),
                          1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( radau_moment[7].convert_to<double>(),
                          radau_moments_8[7].convert_to<double>(),
                          1e-14 );

}

//---------------------------------------------------------------------------//
// Check that the mean coefficients for orthogonal polynomial recursion relation can be evaluated
FRENSIE_UNIT_TEST( SloanRadauQuadrature, evaluateOrthogonalNormalizationRatio )
{
  int i = 1;
  std::vector<Utility::long_float> ratios( 3 );

  quadrature->evaluateOrthogonalNormalizationRatio( ratios,
                                                    orthogonal_coefficients,
                                                    normalization_factors_N,
                                                    radau_moments,
                                                    i );

  FRENSIE_CHECK_FLOATING_EQUALITY( ratios[i].convert_to<double>(),
                          normalization_ratios[i].convert_to<double>(),
                          1e-12);

  i = 2;
  quadrature->evaluateOrthogonalNormalizationRatio( ratios,
                                                    orthogonal_coefficients,
                                                    normalization_factors_N,
                                                    radau_moments,
                                                    i );

  FRENSIE_CHECK_FLOATING_EQUALITY( ratios[i].convert_to<double>(),
                          normalization_ratios[i].convert_to<double>(),
                          1e-12);

}

//---------------------------------------------------------------------------//
// Check that the mean coefficients for orthogonal polynomial recursion relation can be evaluated
FRENSIE_UNIT_TEST( SloanRadauQuadrature, evaluateMeanCoefficient )
{
  int i = 1;
  Utility::long_float result1 =
    quadrature->evaluateMeanCoefficient( normalization_ratios,
                                         i );

  FRENSIE_CHECK_FLOATING_EQUALITY( result1.convert_to<double>(),
                          mean_coefficients[i].convert_to<double>(),
                          1e-12);

  i = 2;
  Utility::long_float result2 =
    quadrature->evaluateMeanCoefficient( normalization_ratios,
                                         i );

  FRENSIE_CHECK_FLOATING_EQUALITY( result2.convert_to<double>(),
                          mean_coefficients[i].convert_to<double>(),
                          1e-12);

}

//---------------------------------------------------------------------------//
// Check that the coefficients of the orthogonal polynomial can be evaluated
FRENSIE_UNIT_TEST( SloanRadauQuadrature, evaluateOrthogonalCoefficients )
{
  std::vector<std::vector<Utility::long_float> > coefficients( 3, std::vector<Utility::long_float>( 3 ) );

  coefficients[0][0] = Utility::long_float(1);

  int i = 1;

  quadrature->evaluateOrthogonalCoefficients( coefficients,
                                              variances,
                                              mean_coefficients,
                                              i );

  FRENSIE_CHECK_FLOATING_EQUALITY( coefficients[i][0].convert_to<double>(),
                          orthogonal_coefficients[i][0].convert_to<double>(),
                          1e-12);

  FRENSIE_CHECK_FLOATING_EQUALITY( coefficients[i][1].convert_to<double>(),
                          orthogonal_coefficients[i][1].convert_to<double>(),
                          1e-12);


  i = 2;
  quadrature->evaluateOrthogonalCoefficients( coefficients,
                                              variances,
                                              mean_coefficients,
                                              i );

  FRENSIE_CHECK_FLOATING_EQUALITY( coefficients[i][0].convert_to<double>(),
                          orthogonal_coefficients[i][0].convert_to<double>(),
                          1e-12);

  FRENSIE_CHECK_FLOATING_EQUALITY( coefficients[i][1].convert_to<double>(),
                          orthogonal_coefficients[i][1].convert_to<double>(),
                          1e-12);

  FRENSIE_CHECK_FLOATING_EQUALITY( coefficients[i][2].convert_to<double>(),
                          orthogonal_coefficients[i][2].convert_to<double>(),
                          1e-12);

}

//---------------------------------------------------------------------------//
// Check that the normalization factors of the orthogonal polynomial can be evaluated
FRENSIE_UNIT_TEST( SloanRadauQuadrature,
                   evaluateOrthogonalNormalizationFactor )
{
  std::vector<Utility::long_float> N( 3 );
  int i = 0;

  quadrature->evaluateOrthogonalNormalizationFactor( N,
                                                     orthogonal_coefficients,
                                                     radau_moments,
                                                     i );

  FRENSIE_CHECK_FLOATING_EQUALITY( N[0].convert_to<double>(),
                          normalization_factors_N[i].convert_to<double>(),
                          1e-12);

  i = 1;
  quadrature->evaluateOrthogonalNormalizationFactor( N,
                                                     orthogonal_coefficients,
                                                     radau_moments,
                                                     i );

  FRENSIE_CHECK_FLOATING_EQUALITY( N[1].convert_to<double>(),
                          normalization_factors_N[i].convert_to<double>(),
                          1e-12);
}

//---------------------------------------------------------------------------//
// Check that the Variance of the orthogonal polynomial can be evaluated
FRENSIE_UNIT_TEST( SloanRadauQuadrature, evaluateVariance )
{

  int i = 1;

  Utility::long_float result =
    quadrature->evaluateVariance( normalization_factors_N,
                                  i );

  FRENSIE_CHECK_FLOATING_EQUALITY( result.convert_to<double>(),
                          variances[i].convert_to<double>(),
                          1e-12);
}

//---------------------------------------------------------------------------//
// Check that the Orthogonal Polynomial can be evaluated
FRENSIE_UNIT_TEST( SloanRadauQuadrature, evaluateOrthogonalPolynomial )
{
  Utility::long_float result1 =
    quadrature->evaluateOrthogonalPolynomial( variances,
                                              mean_coefficients,
                                              -Utility::long_float(1),
                                              2 );

  FRENSIE_CHECK_FLOATING_EQUALITY( result1.convert_to<double>(),
                          1.30003428811616E+00,
                          1e-12);

  Utility::long_float result2 =
    quadrature->evaluateOrthogonalPolynomial( variances,
                                              mean_coefficients,
                                              Utility::long_float(1),
                                              2 );

  FRENSIE_CHECK_FLOATING_EQUALITY( result2.convert_to<double>(),
                          3.32904776851917E-02,
                          1e-12);

}
/*
//---------------------------------------------------------------------------//
// Check that the roots of the Orthogonal Polynomial can be evaluated
FRENSIE_UNIT_TEST( SloanRadauQuadrature,
		           evaluateOrthogonalRoots )
{
  Teuchos::TwoDArray<Utility::long_float> test_roots( 3, 2 );

  test_roots[1][0] = 9.0919706753240400E-01L;

  int i = 2;
  bool root_found =
    quadrature->evaluateOrthogonalRoots( test_roots,
                                         variances,
                                         mean_coefficients,
                                         i );

  TEST_EQUALITY_CONST( root_found, 1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( test_roots[2][0].convert_to<double>(),
                          roots[2][0].convert_to<double>(),
                          1e-12);
  FRENSIE_CHECK_FLOATING_EQUALITY( test_roots[2][1].convert_to<double>(),
                          roots[2][1].convert_to<double>(),
                          1e-12);

}
*/
//---------------------------------------------------------------------------//
// Check that the roots of the Orthogonal Polynomial can be evaluated
FRENSIE_UNIT_TEST( SloanRadauQuadrature, getRadauNodesAndWeights )
{
  double tol = 1e-15;
  std::vector<Utility::long_float> nodes, weights;
  int number_of_angles_wanted = 3;

  quadrature->getRadauNodesAndWeights( nodes, weights, number_of_angles_wanted );

  std::vector<Utility::long_float> legendres_4( 5 );

  legendres_4[0] = Utility::long_float(259700);
  for ( int i = 0; i < number_of_angles_wanted; ++i )
  {
    for ( int m = 1; m < 5; ++m )
    {
      legendres_4[m] +=
        Utility::getLegendrePolynomial( nodes[i].convert_to<long double>(), m )
        *weights[i]*Utility::long_float(259700);
    }
  }

  FRENSIE_CHECK_FLOATING_EQUALITY( legendres_4[0].convert_to<double>(),
                          legendre_moments[0].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( legendres_4[1].convert_to<double>(),
                          legendre_moments[1].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( legendres_4[2].convert_to<double>(),
                          legendre_moments[2].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( legendres_4[3].convert_to<double>(),
                          legendre_moments[3].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( legendres_4[4].convert_to<double>(),
                          legendre_moments[4].convert_to<double>(),
                          tol);

/*
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[0].convert_to<double>(),
                          weights_4[0].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[1].convert_to<double>(),
                          weights_4[1].convert_to<double>(),
                           tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[2].convert_to<double>(),
                          weights_4[2].convert_to<double>(),
                           tol);

  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[0].convert_to<double>(),
                          roots[2][0].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[1].convert_to<double>(),
                          roots[2][1].convert_to<double>(),
                          tol);
  TEST_EQUALITY_CONST( nodes[2].convert_to<double>(), 1.0 );
*/

  number_of_angles_wanted = 5;
  quadrature_8->getRadauNodesAndWeights( nodes, weights, number_of_angles_wanted );

  std::vector<Utility::long_float>  legendres_8( 9 );

  legendres_8[0] = Utility::long_float(1)*Utility::long_float(259700);
  for ( int i = 0; i < number_of_angles_wanted; ++i )
  {
    for ( int m = 1; m < 9; ++m )
    {
      legendres_8[m] +=
        Utility::getLegendrePolynomial( nodes[i].convert_to<long double>(), m )
        *weights[i]*Utility::long_float(259700);
    }
  }

  FRENSIE_CHECK_FLOATING_EQUALITY( legendres_8[0].convert_to<double>(),
                          legendre_moments_8[0].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( legendres_8[1].convert_to<double>(),
                          legendre_moments_8[1].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( legendres_8[2].convert_to<double>(),
                          legendre_moments_8[2].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( legendres_8[3].convert_to<double>(),
                          legendre_moments_8[3].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( legendres_8[4].convert_to<double>(),
                          legendre_moments_8[4].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( legendres_8[5].convert_to<double>(),
                          legendre_moments_8[5].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( legendres_8[6].convert_to<double>(),
                          legendre_moments_8[6].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( legendres_8[7].convert_to<double>(),
                          legendre_moments_8[7].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( legendres_8[8].convert_to<double>(),
                          legendre_moments_8[8].convert_to<double>(),
                          tol);
/*
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[0].convert_to<double>(),
                          weights_8[0].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[1].convert_to<double>(),
                          weights_8[1].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[2].convert_to<double>(),
                          weights_8[2].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[3].convert_to<double>(),
                          weights_8[3].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[4].convert_to<double>(),
                          weights_8[4].convert_to<double>(),
                          tol);

  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[0].convert_to<double>(),
                          roots_8[4][0].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[1].convert_to<double>(),
                          roots_8[4][1].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[2].convert_to<double>(),
                          roots_8[4][2].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[3].convert_to<double>(),
                          roots_8[4][3].convert_to<double>(),
                          tol);
  TEST_EQUALITY_CONST( nodes[4].convert_to<double>(), 1.0 );
*/

  std::vector<double> node, weight;
  number_of_angles_wanted = 5;
  quadrature_8->getRadauNodesAndWeights( node, weight, number_of_angles_wanted );

  std::vector<Utility::long_float>  legendres_double( 9 );

  legendres_double[0] = Utility::long_float(1)*Utility::long_float(259700);
  for ( int i = 0; i < number_of_angles_wanted; ++i )
  {
    for ( int m = 1; m < 9; ++m )
    {
      legendres_double[m] +=
        Utility::getLegendrePolynomial( node[i], m )
        *weight[i]*Utility::long_float(259700);
    }
  }

  FRENSIE_CHECK_FLOATING_EQUALITY( legendres_double[0].convert_to<double>(),
                          legendre_moments_8[0].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( legendres_double[1].convert_to<double>(),
                          legendre_moments_8[1].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( legendres_double[2].convert_to<double>(),
                          legendre_moments_8[2].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( legendres_double[3].convert_to<double>(),
                          legendre_moments_8[3].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( legendres_double[4].convert_to<double>(),
                          legendre_moments_8[4].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( legendres_double[5].convert_to<double>(),
                          legendre_moments_8[5].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( legendres_double[6].convert_to<double>(),
                          legendre_moments_8[6].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( legendres_double[7].convert_to<double>(),
                          legendre_moments_8[7].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( legendres_double[8].convert_to<double>(),
                          legendre_moments_8[8].convert_to<double>(),
                          tol);

  std::vector<long double> node_ld, weight_ld;
  number_of_angles_wanted = 5;
  quadrature_8->getRadauNodesAndWeights( node_ld,
                                         weight_ld,
                                         number_of_angles_wanted );

  std::vector<Utility::long_float>  legendres_ld( 9 );

  legendres_ld[0] = Utility::long_float(1)*Utility::long_float(259700);
  for ( int i = 0; i < number_of_angles_wanted; ++i )
  {
    for ( int m = 1; m < 9; ++m )
    {
      legendres_ld[m] +=
        Utility::getLegendrePolynomial( node_ld[i], m )
        *weight_ld[i]*Utility::long_float(259700);
    }
  }

  FRENSIE_CHECK_FLOATING_EQUALITY( legendres_ld[0].convert_to<double>(),
                          legendre_moments_8[0].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( legendres_ld[1].convert_to<double>(),
                          legendre_moments_8[1].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( legendres_ld[2].convert_to<double>(),
                          legendre_moments_8[2].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( legendres_ld[3].convert_to<double>(),
                          legendre_moments_8[3].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( legendres_ld[4].convert_to<double>(),
                          legendre_moments_8[4].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( legendres_ld[5].convert_to<double>(),
                          legendre_moments_8[5].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( legendres_ld[6].convert_to<double>(),
                          legendre_moments_8[6].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( legendres_ld[7].convert_to<double>(),
                          legendre_moments_8[7].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( legendres_ld[8].convert_to<double>(),
                          legendre_moments_8[8].convert_to<double>(),
                          tol);

  number_of_angles_wanted = 7;
  test_quadrature->getRadauNodesAndWeights( nodes, weights, number_of_angles_wanted );

  int nodes_preserved = nodes.size();

  std::vector<Utility::long_float> legendres( test_legendre.size() );

  legendres[0] = Utility::long_float(1);
  for ( int i = 0; i < nodes_preserved; ++i )
  {
    for ( int m = 1; m < test_legendre.size(); ++m )
    {
      legendres[m] +=
        Utility::getLegendrePolynomial( nodes[i].convert_to<long double>(), m )
        *weights[i];
    }
  }

  FRENSIE_CHECK_FLOATING_EQUALITY( legendres[0].convert_to<double>(), test_legendre[0].convert_to<double>(), tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( legendres[1].convert_to<double>(), test_legendre[1].convert_to<double>(), tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( legendres[2].convert_to<double>(), test_legendre[2].convert_to<double>(), tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( legendres[3].convert_to<double>(), test_legendre[3].convert_to<double>(), tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( legendres[4].convert_to<double>(), test_legendre[4].convert_to<double>(), tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( legendres[5].convert_to<double>(), test_legendre[5].convert_to<double>(), tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( legendres[6].convert_to<double>(), test_legendre[6].convert_to<double>(), tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( legendres[7].convert_to<double>(), test_legendre[7].convert_to<double>(), tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( legendres[8].convert_to<double>(), test_legendre[8].convert_to<double>(), tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( legendres[9].convert_to<double>(), test_legendre[9].convert_to<double>(), tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( legendres[10].convert_to<double>(), test_legendre[10].convert_to<double>(), tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( legendres[11].convert_to<double>(), test_legendre[11].convert_to<double>(), 1e-10);
  FRENSIE_CHECK_FLOATING_EQUALITY( legendres[12].convert_to<double>(), test_legendre[12].convert_to<double>(), 1e-10);
  FRENSIE_CHECK_FLOATING_EQUALITY( legendres[13].convert_to<double>(), test_legendre[13].convert_to<double>(), 1e-10);
  FRENSIE_CHECK_FLOATING_EQUALITY( legendres[14].convert_to<double>(), test_legendre[14].convert_to<double>(), 1e-10);
  FRENSIE_CHECK_FLOATING_EQUALITY( legendres[15].convert_to<double>(), test_legendre[15].convert_to<double>(), 1e-10);
  FRENSIE_CHECK_FLOATING_EQUALITY( legendres[16].convert_to<double>(), test_legendre[16].convert_to<double>(), 1e-10);


}

//---------------------------------------------------------------------------//
// Verify function matches original algorithm
FRENSIE_UNIT_TEST( SloanRadauQuadrature, AlgorithmMatch)
{
  double tol = 1e-15;
  std::vector<Utility::long_float> nodes, weights, node, weight;
  int number_of_angles_wanted = 2;
  node.resize(number_of_angles_wanted);
  weight.resize(number_of_angles_wanted);

  std::vector<Utility::long_float> l_moments(3);
  std::shared_ptr<Utility::SloanRadauQuadrature> test;

  l_moments[0] =    Utility::long_float(1);
  l_moments[1] =    Utility::long_float(0);
  l_moments[2] =    Utility::long_float(0);

  test.reset(
    new Utility::SloanRadauQuadrature( l_moments ) );

  test->getRadauNodesAndWeights( nodes, weights, number_of_angles_wanted );

  node[0] = -Utility::long_float(1)/Utility::long_float(3);
  node[1] = Utility::long_float(1);

  weight[0] = Utility::long_float(3)/Utility::long_float(4);
  weight[1] = Utility::long_float(1)/Utility::long_float(4);

  FRENSIE_CHECK_FLOATING_EQUALITY( weights[0].convert_to<double>(),
                          weight[0].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[1].convert_to<double>(),
                          weight[1].convert_to<double>(),
                          tol);


  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[0].convert_to<double>(),
                          node[0].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[1].convert_to<double>(),
                          node[1].convert_to<double>(),
                          tol);


  number_of_angles_wanted = 4;
  node.resize(number_of_angles_wanted);
  weight.resize(number_of_angles_wanted);
  l_moments.resize(7);

  l_moments[0] =    Utility::long_float(1);
  l_moments[1] =    Utility::long_float(0);
  l_moments[2] =    Utility::long_float(0);
  l_moments[3] =    Utility::long_float(0);
  l_moments[4] =    Utility::long_float(0);
  l_moments[5] =    Utility::long_float(0);
  l_moments[6] =    Utility::long_float(0);

  test.reset(
    new Utility::SloanRadauQuadrature( l_moments ) );

  test->getRadauNodesAndWeights( nodes, weights, number_of_angles_wanted );

  node[1] = -1.810662711185306E-01L;
  node[2] = 5.753189235216941E-01L;
  node[0] = -8.228240809745921E-01L;
  node[3] = 1.000000000000000E+00L;

  weight[1] =  3.881934688431719E-01L;
  weight[2] = 3.288443199800598E-01L;
  weight[0] = 2.204622111767684E-01L;
  weight[3] = 6.250000000000000E-02L;

  FRENSIE_CHECK_FLOATING_EQUALITY( weights[0].convert_to<double>(),
                          weight[0].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[1].convert_to<double>(),
                          weight[1].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[2].convert_to<double>(),
                          weight[2].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[3].convert_to<double>(),
                          weight[3].convert_to<double>(),
                          tol);


  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[0].convert_to<double>(),
                          node[0].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[1].convert_to<double>(),
                          node[1].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[2].convert_to<double>(),
                          node[2].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[3].convert_to<double>(),
                          node[3].convert_to<double>(),
                          tol);

  number_of_angles_wanted = 4;
  node.resize(number_of_angles_wanted);
  weight.resize(number_of_angles_wanted);
  l_moments.resize(6);

  l_moments[0] =    Utility::long_float(2);
  l_moments[1] =    Utility::long_float(0);
  l_moments[2] =    Utility::long_float(0);
  l_moments[3] =    Utility::long_float(0);
  l_moments[4] =    Utility::long_float(0);
  l_moments[5] =    Utility::long_float(0);

  test.reset(
    new Utility::SloanRadauQuadrature( l_moments ) );

  test->getRadauNodesAndWeights( nodes, weights, number_of_angles_wanted );

  node[1] = -1.762533480739568E-01L;
  node[2] = 5.786796265405898E-01L;
  node[0] = -8.212296972700518E-01L;
  node[3] = 1.000000000000000E+00L;

  weight[1] = 3.889162116284768E-01L;
  weight[2] = 3.269574973959520E-01L;
  weight[0] = 2.222576041068843E-01L;
  weight[3] = 6.186868686868687E-02L;

  FRENSIE_CHECK_FLOATING_EQUALITY( weights[0].convert_to<double>(),
                          weight[0].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[1].convert_to<double>(),
                          weight[1].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[2].convert_to<double>(),
                          weight[2].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[3].convert_to<double>(),
                          weight[3].convert_to<double>(),
                          tol);


  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[0].convert_to<double>(),
                          node[0].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[1].convert_to<double>(),
                          node[1].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[2].convert_to<double>(),
                          node[2].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[3].convert_to<double>(),
                          node[3].convert_to<double>(),
                          tol);
/*
  number_of_angles_wanted = 2;
  node.resize(number_of_angles_wanted);
  weight.resize(number_of_angles_wanted);
  l_moments.resize(3);

  l_moments[0] =    Utility::long_float(1)*1000;
  l_moments[1] =    9.999998463039E-01L*1000;
  l_moments[2] =    9.999994981590E-01L*1000;

  test.reset(
    new Utility::SloanRadauQuadrature( l_moments ) );

  test->getRadauNodesAndWeights( nodes, weights, number_of_angles_wanted );

  node[0] = -7.684804997909467E-08L;
  node[1] = 1.000000000000000E+00L;

  weight[0] = 1.536960881469447E-07L;
  weight[1] = 9.999998463039118E-01L;

  FRENSIE_CHECK_FLOATING_EQUALITY( weights[0].convert_to<double>(),
                          weight[0].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[1].convert_to<double>(),
                          weight[1].convert_to<double>(),
                          tol);


  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[0].convert_to<double>(),
                          node[0].convert_to<double>(),
                          tol);
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[1].convert_to<double>(),
                          node[1].convert_to<double>(),
                          tol);
*/
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  legendre_moments[0] =    Utility::long_float(259700);
  legendre_moments[1] =    Utility::long_float(2596999988559773)/10000000000;
  legendre_moments[2] =    Utility::long_float(2596999967237519)/10000000000;
  legendre_moments[3] =    Utility::long_float(2596999936552638)/10000000000;
  legendre_moments[4] =    Utility::long_float(2596999896851397)/10000000000;

  radau_moments[0] = 4.405171300E-09L;
  radau_moments[0] += 3.88171300E-17L;
  radau_moments[1] = 4.005168800E-09L;
  radau_moments[1] += 6.32303200E-17L;
  radau_moments[2] = 4.005170700E-09L;
  radau_moments[2] += 5.06094700E-17L;
  radau_moments[3] = 3.871836000E-09L;
  radau_moments[3] += 7.39764500E-17L;

  roots[0][0] = Utility::long_float(0);
  roots[1][0] = Utility::long_float(909197067)/10000000000L;
  roots[1][0] += 5.3240400E-10L;
  roots[1][1] = Utility::long_float(0);
  roots[2][0] = -Utility::long_float(3418139372)/10000000000L;
  roots[2][0] -= 2.4058100E-10L;
  roots[2][1] = Utility::long_float(9751900690)/10000000000;
  roots[2][1] += 8.79891800E-10L;
/*
  roots[0][0] = Utility::long_float(0);
  roots[1][0] = 9.0919706700E-01L;
  roots[1][0] += 5.3240400E-10L;
  roots[1][1] = Utility::long_float(0);
  roots[2][0] = -3.41813937200E-01L;
  roots[2][0] -= 2.4058100E-10L;
  roots[2][1] = 9.7519006900E-01L;
  roots[2][1] += 8.79891800E-10L;
  */
  variances[0] = Utility::long_float(0);
  variances[1] = 8.2558188369131800E-02L;
  variances[2] = Utility::long_float(0);

  mean_coefficients[0] = Utility::long_float(0);
  mean_coefficients[1] = 9.09197067532404E-01L;
  mean_coefficients[2] = -2.75825162316919E-01L;

  normalization_factors_N[0] = 4.4051713388171300E-09L;
  normalization_factors_N[1] = 3.6368296518836500E-10L;
  normalization_factors_N[2] = Utility::long_float(0);

  normalization_ratios[0] =  Utility::long_float(0);
  normalization_ratios[1] =  9.0919706753240400E-01L;
  normalization_ratios[2] =  6.3337190521548500E-01L;

  orthogonal_coefficients[0][0] = Utility::long_float(1);
  orthogonal_coefficients[1][0] = -9.09197067532404E-01L;
  orthogonal_coefficients[1][1] = Utility::long_float(1);
  orthogonal_coefficients[2][0] = -3.33337617099324E-01L;
  orthogonal_coefficients[2][1] = -6.33371905215485E-01L;
  orthogonal_coefficients[2][2] = Utility::long_float(1);

  weights_4[0] = 1.645045000E-10L;
  weights_4[0] += 6.59555490E-18L;
  weights_4[1] = 1.686597100E-07L;
  weights_4[1] += 6.84122450E-15L;
  weights_4[2] = 9.999998300E-01L;
  weights_4[2] += 1.17577860E-09L;

  quadrature.reset(
    new Utility::SloanRadauQuadrature( legendre_moments ) );

  legendre_moments_8[0] = Utility::long_float(259700);
  legendre_moments_8[1] = Utility::long_float(2596999988559773)/10000000000;
  legendre_moments_8[2] = Utility::long_float(2596999967237519)/10000000000;
  legendre_moments_8[3] = Utility::long_float(2596999936552638)/10000000000;
  legendre_moments_8[4] = Utility::long_float(2596999896851397)/10000000000;
  legendre_moments_8[5] = Utility::long_float(2596999848393495)/10000000000;
  legendre_moments_8[6] = Utility::long_float(2596999791386693)/10000000000;
  legendre_moments_8[7] = Utility::long_float(2596999726004124)/10000000000;
  legendre_moments_8[8] = Utility::long_float(2596999652394188)/10000000000;

  radau_moments_8[0] = Utility::long_float(11440227)/10000000000;
  radau_moments_8[1] = Utility::long_float(10401427)/10000000000;
  radau_moments_8[2] = Utility::long_float(10401427)/10000000000;
  radau_moments_8[3] = 1.005516025000E-03L;
  radau_moments_8[3] += 7.142857142857E-13L;
  radau_moments_8[4] = 1.00551604095238095238095E-03L;
  radau_moments_8[5] = 9.847400229437229437229437E-04L;
  radau_moments_8[6] = 9.8474004372294372294372E-04L;
  radau_moments_8[7] = 9.699000221445221445221445E-04L;


/*
  radau_moments_8[0] = 1.14402270000000E-03L;
  radau_moments_8[1] = 1.04014270000000E-03L;
  radau_moments_8[2] = 1.04014270000000E-03L;
  radau_moments_8[3] = 1.0055160257142857142857E-03L;
  radau_moments_8[4] = 1.00551604095238095238095E-03L;
  radau_moments_8[5] = 9.847400229437229437229437E-04L;
  radau_moments_8[6] = 9.8474004372294372294372E-04L;
  radau_moments_8[7] = 9.699000221445221445221445E-04L;

  legendre_moments_8[0] = 1.0;
  legendre_moments_8[1] = 0.99999999559482980361956103195;
  legendre_moments_8[2] = 0.99999998738448941085868309587;
  legendre_moments_8[3] = 0.99999997556897882171736619175;
  legendre_moments_8[4] = 0.99999996028163149788217173661;
  legendre_moments_8[5] = 0.99999994162244705429341547939;
  legendre_moments_8[6] = 0.99999991967142587601078167115;
  legendre_moments_8[7] = 0.99999989449523450134770889487;
  legendre_moments_8[8] = 0.99999986615101578744705429341;

  radau_moments_8[0] = 4.405170196380430E-09;
  radau_moments_8[1] = 4.005171312861970E-09;
  radau_moments_8[2] = 4.005169855989440E-09;
  radau_moments_8[3] = 3.871837442415890E-09;
  radau_moments_8[4] = 3.871836433811830E-09;
  radau_moments_8[5] = 3.791837209801940E-09;
  radau_moments_8[6] = 3.791836537399230E-09;
  radau_moments_8[7] = 3.734694298573380E-09;
*/

  roots_8[4][0] = -8.234344561502381E-01L;
  roots_8[4][1] = -1.838878312824176E-01L;
  roots_8[4][2] = 5.698926378972536E-01L;
  roots_8[4][3] = 9.932955818658158E-01L;

  weights_8[4] = 9.999994142425495E-01L;
  weights_8[3] = 5.849120168521541E-07L;
  weights_8[2] = 7.085976107890621E-10L;
  weights_8[1] = 1.104049253744378E-10L;
  weights_8[0] = 2.643111130891782E-11L;

  quadrature_8.reset(
    new Utility::SloanRadauQuadrature( legendre_moments_8 ) );

  // Create legendre moments from nodes and weights
  int num_roots = 8, num_moments = 17;

  test_roots[0] = Utility::long_float(999)/1000;
  test_roots[1] = Utility::long_float(998)/1000;
  test_roots[2] = Utility::long_float(997)/1000;
  test_roots[3] = Utility::long_float(996)/1000;
  test_roots[4] = Utility::long_float(994)/1000;
  test_roots[5] = Utility::long_float(992)/1000;
  test_roots[6] = Utility::long_float(990)/1000;
  test_roots[7] = Utility::long_float(900)/1000;

  test_weight = 1.0L/num_roots;

  test_legendre[0] = Utility::long_float(1);
  for ( int i = 0; i < num_roots; ++i )
  {
    for ( int m = 1; m < num_moments; ++m )
    {
      test_legendre[m] +=
        Utility::getLegendrePolynomial( test_roots[i].convert_to<long double>(),
                                        m )*test_weight;
    }
  }

  test_quadrature.reset(
    new Utility::SloanRadauQuadrature( test_legendre ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstSloanRadauQuadrature.cpp
//---------------------------------------------------------------------------//
