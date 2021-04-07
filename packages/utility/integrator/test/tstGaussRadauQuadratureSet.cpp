//---------------------------------------------------------------------------//
//!
//! \file   tstGaussRadauQuadratureSet.cpp
//! \author Luke Kersting
//! \brief  Gauss-Radau quadrature set unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// FRENSIE Includes
#include "Utility_GaussRadauQuadratureSet.hpp"
#include "Utility_TypeNameTraits.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

struct X2Functor
{
  double operator()( const double x ) const
  {
    if( x >= -1.0 && x <= 1.0 )
      return x*x;
    else
      return 0.0;
  }

  static double getIntegratedValue()
  {
    return 2.0/3.0;
  }
};

struct X3Functor
{
  double operator()( const double x ) const
  {
    if( x >= -1.0 && x <= 1.0 )
      return x*x*x;
    else
      return 0.0;
  }

  static double getIntegratedValue()
  {
    return 0.0;
  }
};

struct X_1_Functor
{
  double operator()( const double x ) const
  {
    if( x >= -1.0 && x <= 1.0 )
      return (1.0 + x);
    else
      return 0.0;
  }

  static double getIntegratedValue()
  {
    return 2;
  }
};

namespace Utility{

TYPE_NAME_TRAITS_QUICK_DECL( X2Functor );
TYPE_NAME_TRAITS_QUICK_DECL( X3Functor );
TYPE_NAME_TRAITS_QUICK_DECL( X_1_Functor );
  
} // end Utility namespace

typedef std::tuple<X2Functor,X3Functor,X_1_Functor> TestFunctors;

//---------------------------------------------------------------------------//
// Testing Functions
//---------------------------------------------------------------------------//

double f_x( const double x, int n )
{
  return 1.0;
}

double P_n( const double x, int n )
{
  // Calculate the first two polynomials
  double P_0 = 1.0;
  double P_1 = x;

  if (n==0)
  {
    return P_0;
  }
  if (n==1)
  {
    return P_1;
  }
  else
  {
    double p_i_minus_2 = P_0;
    double p_i_minus_1 = P_1;
    double p_i;

    // Use recursion relation to calculate higher order Jacobi polynomials
    for (int i = 1; i < n; ++i)
    {
      int two_i = 2*i;

      // Calculate the Jacobi coefficients
      double a1_i = 1.0/i;
      double a2_i = 2.0*i - 1.0;
      double a3_i = i - 1.0;

      // Calculate new P_n value
      p_i = a1_i*( a2_i*x*p_i_minus_1 + a3_i*p_i_minus_2 );

      // Update P_n_minus_1 and P_n_minus_2 for next value on n
      p_i_minus_2 = p_i_minus_1;
      p_i_minus_1 = p_i;
    }

  return p_i;
  }
}

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the functions can be integrated over [-1,1] for n=4
FRENSIE_UNIT_TEST_TEMPLATE( GaussRadauQuadratureSet,
                            integrate,
                            TestFunctors )
{
  FETCH_TEMPLATE_PARAM( 0, Functor );
  
  double result;
  double tol = 1e-12;
  int n = 4;

  boost::function<double (double, int)> function_wrapper = f_x;
  Utility::GaussRadauQuadratureSet set( f_x, tol, n );

  Functor functor_instance;


  double end_point = -1.0;
  set.integrate( functor_instance, end_point, -1.0, 1.0, result );

  FRENSIE_CHECK_FLOATING_EQUALITY( Functor::getIntegratedValue(), result, tol );

  end_point = 1.0;
  set.integrate( functor_instance, end_point, -1.0, 1.0, result );

  FRENSIE_CHECK_FLOATING_EQUALITY( Functor::getIntegratedValue(), result, tol );
}

//---------------------------------------------------------------------------//
// Check that nodes and weights can be found for n=4 p(x) = 1
FRENSIE_UNIT_TEST( GaussRadauQuadratureSet,
                   findNodesAndWeights_4 )
{
  double tol = 1e-12;
  int n = 4;

  boost::function<double (double, int)> function_wrapper = f_x;
  Utility::GaussRadauQuadratureSet set( f_x, tol, n );

  std::vector<double> nodes( n+1 );
  std::vector<double> weights( n+1 );

  double end_point = -1.0;
  set.findNodesAndWeights( end_point, nodes, weights );

  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[0], -1.0, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[1], -0.720480271312439, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[2], -0.167180864737834, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[3], 0.446313972723752, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[4], 0.885791607770965, tol );

  FRENSIE_CHECK_FLOATING_EQUALITY( weights[0], 0.080000000000000, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[1], 0.446207802167143, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[2], 0.623653045951483, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[3], 0.562712030298924, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[4], 0.287427121582452, tol );

  end_point = 1.0;
  set.findNodesAndWeights( end_point, nodes, weights );

  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[0], -0.720480271312439, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[1], -0.167180864737834, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[2], 0.446313972723752, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[3], 0.885791607770965, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[4], 1.0, tol );

  FRENSIE_CHECK_FLOATING_EQUALITY( weights[0], 0.649913756106238, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[1], 0.331263099487567, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[2], 0.965959182898273, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[3], -0.347136038492079, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[4], 2.0/5.0, tol );
}

//---------------------------------------------------------------------------//
// Check that nodes and weights can be found for n=4 p(x) = P_n(x)
FRENSIE_UNIT_TEST( GaussRadauQuadratureSet,
                   findNodesAndWeights_4_Legendre )
{
  double tol = 1e-12;
  int n = 4;

  boost::function<double (double, int)> function_wrapper = P_n;

  Utility::GaussRadauQuadratureSet set( P_n, tol, n );

  std::vector<double> nodes( n+1 );
  std::vector<double> weights( n+1 );

  double end_point = -1.0;
  set.findNodesAndWeights( end_point, nodes, weights );

  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[0], -1.0, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[1], -0.720480271312439, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[2], -0.167180864737834, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[3], 0.446313972723752, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[4], 0.885791607770965, tol );

  FRENSIE_CHECK_FLOATING_EQUALITY( weights[0], 0.32, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[1], 0.648018010786282, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[2], 0.027364081142154, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[3], 0.223954898184731, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[4], 0.780663009886833, tol );

  end_point = 1.0;
  set.findNodesAndWeights( end_point, nodes, weights );

  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[0], -0.720480271312439, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[1], -0.167180864737834, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[2], 0.446313972723752, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[3], 0.885791607770965, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[4], 1.0, tol );

  FRENSIE_CHECK_FLOATING_EQUALITY( weights[0], 1.462841826542670, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[1],-1.142195704713504, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[2], 1.836943508582128, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[3],-1.757589630411290, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[4], 1.6, tol );
}

//---------------------------------------------------------------------------//
// Check that nodes and weights can be found for n=4 p(x) = 1
FRENSIE_UNIT_TEST( GaussRadauQuadratureSet,
                   findNodesAndPositiveWeights_4 )
{
  double tol = 1e-12;
  int n = 4;

  boost::function<double (double, int)> function_wrapper = f_x;
  Utility::GaussRadauQuadratureSet set( f_x, tol, n );

  std::vector<double> nodes( n+1 );
  std::vector<double> weights( n+1 );

  double end_point = -1.0;
  set.findNodesAndPositiveWeights( end_point, nodes, weights );

  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[0], -1.0, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[1], -0.720480271312439, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[2], -0.167180864737834, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[3], 0.446313972723752, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[4], 0.885791607770965, tol );

  FRENSIE_CHECK_FLOATING_EQUALITY( weights[0], 0.080000000000000, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[1], 0.446207802167143, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[2], 0.623653045951483, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[3], 0.562712030298924, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[4], 0.287427121582452, tol );

  end_point = 1.0;
  set.findNodesAndPositiveWeights( end_point, nodes, weights );

  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[0], -0.885791607770965, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[1], -0.446313972723752, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[2], 0.167180864737834, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[3], 0.720480271312439, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[4], 1.0, tol );

  FRENSIE_CHECK_FLOATING_EQUALITY( weights[0], 0.287427121582452, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[1], 0.562712030298924, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[2], 0.623653045951483, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[3], 0.446207802167143, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[4], 0.080000000000000, tol );
}

//---------------------------------------------------------------------------//
// Check that nodes and weights can be found for n=4 p(x) = P_n(x)
FRENSIE_UNIT_TEST( GaussRadauQuadratureSet,
                   findNodesAndPositiveWeights_4_Legendre )
{
  double tol = 1e-12;
  int n = 4;

  boost::function<double (double, int)> function_wrapper = P_n;

  Utility::GaussRadauQuadratureSet set( P_n, tol, n );

  std::vector<double> nodes( n+1 );
  std::vector<double> weights( n+1 );

  double end_point = -1.0;
  set.findNodesAndPositiveWeights( end_point, nodes, weights );

  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[0], -1.0, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[1], -0.720480271312439, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[2], -0.167180864737834, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[3], 0.446313972723752, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[4], 0.885791607770965, tol );

  FRENSIE_CHECK_FLOATING_EQUALITY( weights[0], 0.32, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[1], 0.648018010786282, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[2], 0.027364081142154, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[3], 0.223954898184731, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[4], 0.780663009886833, tol );

  end_point = 1.0;
  set.findNodesAndPositiveWeights( end_point, nodes, weights );

  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[0], -0.885791607770965, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[1], -0.446313972723752, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[2], 0.167180864737834, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[3], 0.720480271312439, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[4], 1.0, tol );

  FRENSIE_CHECK_FLOATING_EQUALITY( weights[0], 0.780663009886833, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[1], 0.223954898184731, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[2], 0.027364081142154, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[3], 0.648018010786282, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[4], 0.32, tol );
}

//---------------------------------------------------------------------------//
// Check that nodes and weights can be found for n=16
FRENSIE_UNIT_TEST( GaussRadauQuadratureSet,
		   findNodesAndWeights_16 )
{
  double tol = 1e-12;
  int n = 16;

  boost::function<double (double, int)> function_wrapper = f_x;
  Utility::GaussRadauQuadratureSet set( f_x, tol, n );

  std::vector<double> nodes( n+1 );
  std::vector<double> weights( n+1 );

  double end_point = -1.0;
  set.findNodesAndWeights( end_point, nodes, weights );

   FRENSIE_CHECK_FLOATING_EQUALITY( nodes[0], -1.0, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[1], -0.97470604125208323606, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[2], -0.91604883538095090909, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[3], -0.82621675307428254926, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[4], -0.70827629555042126733, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[5], -0.56624510792973616770, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[6], -0.40496027585008208891, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[7], -0.22991430375297903498, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[8], -0.047068232050336641035, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[9 ], 0.13735131280874924983, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[10], 0.31706414490435386275, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[11], 0.48595038430965828015, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[12], 0.63825888068423266750, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[13], 0.76880312484036811964, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[14], 0.87313810883232650901, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[15], 0.94771297263721189604, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[16], 0.99000540067245615791, tol );

  FRENSIE_CHECK_FLOATING_EQUALITY( weights[0], 0.0069204152249135, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[1], 0.0423015895172990, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[2], 0.0746714345516182, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[3], 0.1044803216981890, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[4], 0.1307287373531040, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[5], 0.1525247060771500, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[6], 0.1691264101227050, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[7], 0.1799686281573100, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[8], 0.1846821930762530, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[9], 0.1831066171286380, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[10], 0.1752955764002200, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[11], 0.1615150963899480, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[12], 0.1422345171369390, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[13], 0.1181105882740290, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[14], 0.0899654562763470, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[15], 0.0587611275215839, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[16], 0.0256065850937466, tol );
}

//---------------------------------------------------------------------------//
// Check that Jacobi Polynomial can be found at a point
FRENSIE_UNIT_TEST( GaussRadauQuadratureSet,
		   getJacobiPolynomial )
{
  double tol = 1e-12;
  int n = 4;

  boost::function<double (double, int)> function_wrapper = f_x;
  Utility::GaussRadauQuadratureSet set( f_x, tol, n );

  // For n = 1, alpha = 0, beta = 1
  double jacobi =
    set.getJacobiPolynomial( 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( jacobi, 1.0, tol );

  jacobi =
    set.getJacobiPolynomial( 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( jacobi, -0.5, tol );


  jacobi =
    set.getJacobiPolynomial( -1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( jacobi, -2.0, tol );

  // For n = 2, alpha = 1, beta = 2
  jacobi =
    set.getJacobiPolynomial( 1.0, 2, 1, 2 );

  FRENSIE_CHECK_FLOATING_EQUALITY( jacobi, 3.0, tol );

  jacobi =
    set.getJacobiPolynomial( 0.0, 2, 1, 2 );

  FRENSIE_CHECK_FLOATING_EQUALITY( jacobi, -0.75, tol );


  jacobi =
    set.getJacobiPolynomial( -1.0, 2, 1, 2 );

  FRENSIE_CHECK_FLOATING_EQUALITY( jacobi, 6.0, tol );

  // For n = 4, alpha = 2, beta = 3
  jacobi =
    set.getJacobiPolynomial( 1.0, 4, 2, 3 );

  FRENSIE_CHECK_FLOATING_EQUALITY( jacobi, 15.0, tol );

  jacobi =
    set.getJacobiPolynomial( 0.0, 4, 2, 3 );

  FRENSIE_CHECK_FLOATING_EQUALITY( jacobi, 0.9375, tol );


  jacobi =
    set.getJacobiPolynomial( -1.0, 4, 2, 3 );

  FRENSIE_CHECK_FLOATING_EQUALITY( jacobi, 35.0, tol );

}

//---------------------------------------------------------------------------//
// Check that Jacobi Polynomial can be found at a point
FRENSIE_UNIT_TEST( GaussRadauQuadratureSet,
		   getJacobiPolynomialDerivative )
{
  double tol = 1e-12;
  int n = 4;

  boost::function<double (double, int)> function_wrapper = f_x;
  Utility::GaussRadauQuadratureSet set( f_x, tol, n );

  // n = 2
  double jacobi =
    set.getJacobiPolynomialDerivative( 1.0, 2 );

  FRENSIE_CHECK_FLOATING_EQUALITY( jacobi, 4.0, tol );

  jacobi =
    set.getJacobiPolynomialDerivative( 0.0, 2 );

  FRENSIE_CHECK_FLOATING_EQUALITY( jacobi, -1.0, tol );


  jacobi =
    set.getJacobiPolynomialDerivative( -1.0, 2 );

  FRENSIE_CHECK_FLOATING_EQUALITY( jacobi, -6.0, tol );

  // n = 4
  jacobi =
    set.getJacobiPolynomialDerivative( 1.0, n );

  FRENSIE_CHECK_FLOATING_EQUALITY( jacobi, 12.0, tol );

  jacobi =
    set.getJacobiPolynomialDerivative( 0.0, n );

  FRENSIE_CHECK_FLOATING_EQUALITY( jacobi, 1.5, tol );


  jacobi =
    set.getJacobiPolynomialDerivative( -1.0, n );

  FRENSIE_CHECK_FLOATING_EQUALITY( jacobi, -30.0, tol );

}
/*
//---------------------------------------------------------------------------//
// Check that nodes and weights can be found for n=4
FRENSIE_UNIT_TEST( GaussRadauQuadratureSet,
		   findWeightPositiveOne )
{
  double tol = 1e-12;
  int n = 4;

  boost::function<double (double, int)> function_wrapper = f_x;
  Utility::GaussRadauQuadratureSet set( f_x, tol, n );

  double answer = set.findWeightPositiveOne( n );
  FRENSIE_CHECK_FLOATING_EQUALITY( answer, 2.0/5.0, tol );

  answer = set.findWeightPositiveOne( 3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( answer, 1.0/2.0, tol );

  answer = set.findWeightPositiveOne( 2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( answer, 2.0/3.0, tol );

  answer = set.findWeightPositiveOne( 1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( answer, 1.0, tol );
}

//---------------------------------------------------------------------------//
// Check that nodes and weights can be found for n=4
FRENSIE_UNIT_TEST( GaussRadauQuadratureSet,
		   findNodesAndWeights_4 )
{
  double tol = 1e-12;
  int n = 4;
  double end_point = -1.0;

  boost::function<double (double, int)> function_wrapper = f_x;
  Utility::GaussRadauQuadratureSet set( f_x, tol, n );

  std::vector<double> nodes( n+1 );
  std::vector<double> weights( n+1 );

  set.findNodesAndWeights( end_point, nodes, weights );

  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[0], -1.0, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[1], -0.720480271312439, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[2], -0.167180864737834, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[3], 0.446313972723752, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( nodes[4], 0.885791607770965, tol );

  FRENSIE_CHECK_FLOATING_EQUALITY( weights[0], 0.080000000000000, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[1], 0.446207802167143, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[2], 0.623653045951483, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[3], 0.562712030298924, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( weights[4], 0.287427121582452, tol );
}
*/
//---------------------------------------------------------------------------//
// end tstGaussRadauQuadratureSet.cpp
//---------------------------------------------------------------------------//
