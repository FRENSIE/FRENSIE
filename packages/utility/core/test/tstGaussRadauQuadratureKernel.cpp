//---------------------------------------------------------------------------//
//!
//! \file   tstGaussRadauQuadratureKernel.cpp
//! \author Luke Kersting
//! \brief  Gauss-Radau quadrature kernel unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Utility_GaussRadauQuadratureKernel.hpp"

//---------------------------------------------------------------------------//
// Testing Functors
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
// Instantiation macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, X2Functor ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, X3Functor ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, X_1_Functor )

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the functions can be integrated over [-1,1] for n=4
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( GaussRadauQuadratureKernel,
                                   integrate,
                                   Functor )
{
  double result;
  double tol = 1e-12;
  int n = 4;
 
  boost::function<double (double, int)> function_wrapper = f_x;
  Utility::GaussRadauQuadratureKernel kernel( f_x, tol, n );

  Functor functor_instance;


  double end_point = -1.0;
  kernel.integrate( functor_instance, end_point, -1.0, 1.0, result );

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), result, tol );

  end_point = 1.0;
  kernel.integrate( functor_instance, end_point, -1.0, 1.0, result );

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), result, tol );
}

UNIT_TEST_INSTANTIATION( GaussRadauQuadratureKernel, integrate );

//---------------------------------------------------------------------------//
// Check that nodes and weights can be found for n=4 p(x) = 1
TEUCHOS_UNIT_TEST( GaussRadauQuadratureKernel,
                   findNodesAndWeights_4 )
{
  double tol = 1e-12;
  int n = 4;
 
  boost::function<double (double, int)> function_wrapper = f_x;
  Utility::GaussRadauQuadratureKernel kernel( f_x, tol, n );

  Teuchos::Array<double> nodes( n+1 );
  Teuchos::Array<double> weights( n+1 );

  double end_point = -1.0;
  kernel.findNodesAndWeights( end_point, nodes, weights );

  TEST_FLOATING_EQUALITY( nodes[0], -1.0, tol );
  TEST_FLOATING_EQUALITY( nodes[1], -0.720480271312439, tol );
  TEST_FLOATING_EQUALITY( nodes[2], -0.167180864737834, tol );
  TEST_FLOATING_EQUALITY( nodes[3], 0.446313972723752, tol );
  TEST_FLOATING_EQUALITY( nodes[4], 0.885791607770965, tol );

  TEST_FLOATING_EQUALITY( weights[0], 0.080000000000000, tol );
  TEST_FLOATING_EQUALITY( weights[1], 0.446207802167143, tol );
  TEST_FLOATING_EQUALITY( weights[2], 0.623653045951483, tol );
  TEST_FLOATING_EQUALITY( weights[3], 0.562712030298924, tol );
  TEST_FLOATING_EQUALITY( weights[4], 0.287427121582452, tol );

  end_point = 1.0;
  kernel.findNodesAndWeights( end_point, nodes, weights );

  TEST_FLOATING_EQUALITY( nodes[0], -0.720480271312439, tol );
  TEST_FLOATING_EQUALITY( nodes[1], -0.167180864737834, tol );
  TEST_FLOATING_EQUALITY( nodes[2], 0.446313972723752, tol );
  TEST_FLOATING_EQUALITY( nodes[3], 0.885791607770965, tol );
  TEST_FLOATING_EQUALITY( nodes[4], 1.0, tol );

  TEST_FLOATING_EQUALITY( weights[0], 0.649913756106238, tol );
  TEST_FLOATING_EQUALITY( weights[1], 0.331263099487567, tol );
  TEST_FLOATING_EQUALITY( weights[2], 0.965959182898273, tol );
  TEST_FLOATING_EQUALITY( weights[3], -0.347136038492079, tol );
  TEST_FLOATING_EQUALITY( weights[4], 2.0/5.0, tol );
}

//---------------------------------------------------------------------------//
// Check that nodes and weights can be found for n=4 p(x) = P_n(x)
TEUCHOS_UNIT_TEST( GaussRadauQuadratureKernel,
		           findNodesAndWeights_4_Legendre )
{
  double tol = 1e-12;
  int n = 4;
 
  boost::function<double (double, int)> function_wrapper = P_n;

  Utility::GaussRadauQuadratureKernel kernel( P_n, tol, n );

  Teuchos::Array<double> nodes( n+1 );
  Teuchos::Array<double> weights( n+1 );

  double end_point = -1.0;
  kernel.findNodesAndWeights( end_point, nodes, weights );

  TEST_FLOATING_EQUALITY( nodes[0], -1.0, tol );
  TEST_FLOATING_EQUALITY( nodes[1], -0.720480271312439, tol );
  TEST_FLOATING_EQUALITY( nodes[2], -0.167180864737834, tol );
  TEST_FLOATING_EQUALITY( nodes[3], 0.446313972723752, tol );
  TEST_FLOATING_EQUALITY( nodes[4], 0.885791607770965, tol );

  TEST_FLOATING_EQUALITY( weights[0], 0.32, tol );
  TEST_FLOATING_EQUALITY( weights[1], 0.648018010786282, tol );
  TEST_FLOATING_EQUALITY( weights[2], 0.027364081142154, tol );
  TEST_FLOATING_EQUALITY( weights[3], 0.223954898184731, tol );
  TEST_FLOATING_EQUALITY( weights[4], 0.780663009886833, tol );

  end_point = 1.0;
  kernel.findNodesAndWeights( end_point, nodes, weights );

  TEST_FLOATING_EQUALITY( nodes[0], -0.720480271312439, tol );
  TEST_FLOATING_EQUALITY( nodes[1], -0.167180864737834, tol );
  TEST_FLOATING_EQUALITY( nodes[2], 0.446313972723752, tol );
  TEST_FLOATING_EQUALITY( nodes[3], 0.885791607770965, tol );
  TEST_FLOATING_EQUALITY( nodes[4], 1.0, tol );

  TEST_FLOATING_EQUALITY( weights[0], 1.462841826542670, tol );
  TEST_FLOATING_EQUALITY( weights[1],-1.142195704713504, tol );
  TEST_FLOATING_EQUALITY( weights[2], 1.836943508582128, tol );
  TEST_FLOATING_EQUALITY( weights[3],-1.757589630411290, tol );
  TEST_FLOATING_EQUALITY( weights[4], 1.6, tol );
}

//---------------------------------------------------------------------------//
// Check that nodes and weights can be found for n=4 p(x) = 1
TEUCHOS_UNIT_TEST( GaussRadauQuadratureKernel,
                   findNodesAndPositiveWeights_4 )
{
  double tol = 1e-12;
  int n = 4;
 
  boost::function<double (double, int)> function_wrapper = f_x;
  Utility::GaussRadauQuadratureKernel kernel( f_x, tol, n );

  Teuchos::Array<double> nodes( n+1 );
  Teuchos::Array<double> weights( n+1 );

  double end_point = -1.0;
  kernel.findNodesAndPositiveWeights( end_point, nodes, weights );

  TEST_FLOATING_EQUALITY( nodes[0], -1.0, tol );
  TEST_FLOATING_EQUALITY( nodes[1], -0.720480271312439, tol );
  TEST_FLOATING_EQUALITY( nodes[2], -0.167180864737834, tol );
  TEST_FLOATING_EQUALITY( nodes[3], 0.446313972723752, tol );
  TEST_FLOATING_EQUALITY( nodes[4], 0.885791607770965, tol );

  TEST_FLOATING_EQUALITY( weights[0], 0.080000000000000, tol );
  TEST_FLOATING_EQUALITY( weights[1], 0.446207802167143, tol );
  TEST_FLOATING_EQUALITY( weights[2], 0.623653045951483, tol );
  TEST_FLOATING_EQUALITY( weights[3], 0.562712030298924, tol );
  TEST_FLOATING_EQUALITY( weights[4], 0.287427121582452, tol );

  end_point = 1.0;
  kernel.findNodesAndPositiveWeights( end_point, nodes, weights );

  TEST_FLOATING_EQUALITY( nodes[0], -0.885791607770965, tol );
  TEST_FLOATING_EQUALITY( nodes[1], -0.446313972723752, tol );
  TEST_FLOATING_EQUALITY( nodes[2], 0.167180864737834, tol );
  TEST_FLOATING_EQUALITY( nodes[3], 0.720480271312439, tol );
  TEST_FLOATING_EQUALITY( nodes[4], 1.0, tol );

  TEST_FLOATING_EQUALITY( weights[0], 0.287427121582452, tol );
  TEST_FLOATING_EQUALITY( weights[1], 0.562712030298924, tol );
  TEST_FLOATING_EQUALITY( weights[2], 0.623653045951483, tol );
  TEST_FLOATING_EQUALITY( weights[3], 0.446207802167143, tol );
  TEST_FLOATING_EQUALITY( weights[4], 0.080000000000000, tol );
}

//---------------------------------------------------------------------------//
// Check that nodes and weights can be found for n=4 p(x) = P_n(x)
TEUCHOS_UNIT_TEST( GaussRadauQuadratureKernel,
		           findNodesAndPositiveWeights_4_Legendre )
{
  double tol = 1e-12;
  int n = 4;
 
  boost::function<double (double, int)> function_wrapper = P_n;

  Utility::GaussRadauQuadratureKernel kernel( P_n, tol, n );

  Teuchos::Array<double> nodes( n+1 );
  Teuchos::Array<double> weights( n+1 );

  double end_point = -1.0;
  kernel.findNodesAndPositiveWeights( end_point, nodes, weights );

  TEST_FLOATING_EQUALITY( nodes[0], -1.0, tol );
  TEST_FLOATING_EQUALITY( nodes[1], -0.720480271312439, tol );
  TEST_FLOATING_EQUALITY( nodes[2], -0.167180864737834, tol );
  TEST_FLOATING_EQUALITY( nodes[3], 0.446313972723752, tol );
  TEST_FLOATING_EQUALITY( nodes[4], 0.885791607770965, tol );

  TEST_FLOATING_EQUALITY( weights[0], 0.32, tol );
  TEST_FLOATING_EQUALITY( weights[1], 0.648018010786282, tol );
  TEST_FLOATING_EQUALITY( weights[2], 0.027364081142154, tol );
  TEST_FLOATING_EQUALITY( weights[3], 0.223954898184731, tol );
  TEST_FLOATING_EQUALITY( weights[4], 0.780663009886833, tol );

  end_point = 1.0;
  kernel.findNodesAndPositiveWeights( end_point, nodes, weights );

  TEST_FLOATING_EQUALITY( nodes[0], -0.885791607770965, tol );
  TEST_FLOATING_EQUALITY( nodes[1], -0.446313972723752, tol );
  TEST_FLOATING_EQUALITY( nodes[2], 0.167180864737834, tol );
  TEST_FLOATING_EQUALITY( nodes[3], 0.720480271312439, tol );
  TEST_FLOATING_EQUALITY( nodes[4], 1.0, tol );

  TEST_FLOATING_EQUALITY( weights[0], 0.780663009886833, tol );
  TEST_FLOATING_EQUALITY( weights[1], 0.223954898184731, tol );
  TEST_FLOATING_EQUALITY( weights[2], 0.027364081142154, tol );
  TEST_FLOATING_EQUALITY( weights[3], 0.648018010786282, tol );
  TEST_FLOATING_EQUALITY( weights[4], 0.32, tol );
}

//---------------------------------------------------------------------------//
// Check that nodes and weights can be found for n=16
TEUCHOS_UNIT_TEST( GaussRadauQuadratureKernel,
		   findNodesAndWeights_16 )
{
  double tol = 1e-12;
  int n = 16;
 
  boost::function<double (double, int)> function_wrapper = f_x;
  Utility::GaussRadauQuadratureKernel kernel( f_x, tol, n );

  Teuchos::Array<double> nodes( n+1 );
  Teuchos::Array<double> weights( n+1 );

  double end_point = -1.0;
  kernel.findNodesAndWeights( end_point, nodes, weights );

   TEST_FLOATING_EQUALITY( nodes[0], -1.0, tol );
  TEST_FLOATING_EQUALITY( nodes[1], -0.97470604125208323606, tol );
  TEST_FLOATING_EQUALITY( nodes[2], -0.91604883538095090909, tol );
  TEST_FLOATING_EQUALITY( nodes[3], -0.82621675307428254926, tol );
  TEST_FLOATING_EQUALITY( nodes[4], -0.70827629555042126733, tol );
  TEST_FLOATING_EQUALITY( nodes[5], -0.56624510792973616770, tol );
  TEST_FLOATING_EQUALITY( nodes[6], -0.40496027585008208891, tol );
  TEST_FLOATING_EQUALITY( nodes[7], -0.22991430375297903498, tol );
  TEST_FLOATING_EQUALITY( nodes[8], -0.047068232050336641035, tol );
  TEST_FLOATING_EQUALITY( nodes[9 ], 0.13735131280874924983, tol );
  TEST_FLOATING_EQUALITY( nodes[10], 0.31706414490435386275, tol );
  TEST_FLOATING_EQUALITY( nodes[11], 0.48595038430965828015, tol );
  TEST_FLOATING_EQUALITY( nodes[12], 0.63825888068423266750, tol );
  TEST_FLOATING_EQUALITY( nodes[13], 0.76880312484036811964, tol );
  TEST_FLOATING_EQUALITY( nodes[14], 0.87313810883232650901, tol );
  TEST_FLOATING_EQUALITY( nodes[15], 0.94771297263721189604, tol );
  TEST_FLOATING_EQUALITY( nodes[16], 0.99000540067245615791, tol );

  TEST_FLOATING_EQUALITY( weights[0], 0.0069204152249135, tol );
  TEST_FLOATING_EQUALITY( weights[1], 0.0423015895172990, tol );
  TEST_FLOATING_EQUALITY( weights[2], 0.0746714345516182, tol );
  TEST_FLOATING_EQUALITY( weights[3], 0.1044803216981890, tol );
  TEST_FLOATING_EQUALITY( weights[4], 0.1307287373531040, tol );
  TEST_FLOATING_EQUALITY( weights[5], 0.1525247060771500, tol );
  TEST_FLOATING_EQUALITY( weights[6], 0.1691264101227050, tol );
  TEST_FLOATING_EQUALITY( weights[7], 0.1799686281573100, tol );
  TEST_FLOATING_EQUALITY( weights[8], 0.1846821930762530, tol );
  TEST_FLOATING_EQUALITY( weights[9], 0.1831066171286380, tol );
  TEST_FLOATING_EQUALITY( weights[10], 0.1752955764002200, tol );
  TEST_FLOATING_EQUALITY( weights[11], 0.1615150963899480, tol );
  TEST_FLOATING_EQUALITY( weights[12], 0.1422345171369390, tol );
  TEST_FLOATING_EQUALITY( weights[13], 0.1181105882740290, tol );
  TEST_FLOATING_EQUALITY( weights[14], 0.0899654562763470, tol );
  TEST_FLOATING_EQUALITY( weights[15], 0.0587611275215839, tol );
  TEST_FLOATING_EQUALITY( weights[16], 0.0256065850937466, tol );
}

//---------------------------------------------------------------------------//
// Check that Jacobi Polynomial can be found at a point
TEUCHOS_UNIT_TEST( GaussRadauQuadratureKernel,
		   getJacobiPolynomial )
{
  double tol = 1e-12;
  int n = 4;
 
  boost::function<double (double, int)> function_wrapper = f_x;
  Utility::GaussRadauQuadratureKernel kernel( f_x, tol, n );

  // For n = 1, alpha = 0, beta = 1
  double jacobi =
    kernel.getJacobiPolynomial( 1.0 );

  TEST_FLOATING_EQUALITY( jacobi, 1.0, tol );

  jacobi =
    kernel.getJacobiPolynomial( 0.0 );

  TEST_FLOATING_EQUALITY( jacobi, -0.5, tol );


  jacobi =
    kernel.getJacobiPolynomial( -1.0 );

  TEST_FLOATING_EQUALITY( jacobi, -2.0, tol );

  // For n = 2, alpha = 1, beta = 2
  jacobi =
    kernel.getJacobiPolynomial( 1.0, 2, 1, 2 );

  TEST_FLOATING_EQUALITY( jacobi, 3.0, tol );

  jacobi =
    kernel.getJacobiPolynomial( 0.0, 2, 1, 2 );

  TEST_FLOATING_EQUALITY( jacobi, -0.75, tol );


  jacobi =
    kernel.getJacobiPolynomial( -1.0, 2, 1, 2 );

  TEST_FLOATING_EQUALITY( jacobi, 6.0, tol );

  // For n = 4, alpha = 2, beta = 3
  jacobi =
    kernel.getJacobiPolynomial( 1.0, 4, 2, 3 );

  TEST_FLOATING_EQUALITY( jacobi, 15.0, tol );

  jacobi =
    kernel.getJacobiPolynomial( 0.0, 4, 2, 3 );

  TEST_FLOATING_EQUALITY( jacobi, 0.9375, tol );


  jacobi =
    kernel.getJacobiPolynomial( -1.0, 4, 2, 3 );

  TEST_FLOATING_EQUALITY( jacobi, 35.0, tol );

}

//---------------------------------------------------------------------------//
// Check that Jacobi Polynomial can be found at a point
TEUCHOS_UNIT_TEST( GaussRadauQuadratureKernel,
		   getJacobiPolynomialDerivative )
{
  double tol = 1e-12;
  int n = 4;

  boost::function<double (double, int)> function_wrapper = f_x;
  Utility::GaussRadauQuadratureKernel kernel( f_x, tol, n );

  // n = 2 
  double jacobi =
    kernel.getJacobiPolynomialDerivative( 1.0, 2 );

  TEST_FLOATING_EQUALITY( jacobi, 4.0, tol );

  jacobi =
    kernel.getJacobiPolynomialDerivative( 0.0, 2 );

  TEST_FLOATING_EQUALITY( jacobi, -1.0, tol );


  jacobi =
    kernel.getJacobiPolynomialDerivative( -1.0, 2 );

  TEST_FLOATING_EQUALITY( jacobi, -6.0, tol );

  // n = 4 
  jacobi =
    kernel.getJacobiPolynomialDerivative( 1.0, n );

  TEST_FLOATING_EQUALITY( jacobi, 12.0, tol );

  jacobi =
    kernel.getJacobiPolynomialDerivative( 0.0, n );

  TEST_FLOATING_EQUALITY( jacobi, 1.5, tol );


  jacobi =
    kernel.getJacobiPolynomialDerivative( -1.0, n );

  TEST_FLOATING_EQUALITY( jacobi, -30.0, tol );

}
/*
//---------------------------------------------------------------------------//
// Check that nodes and weights can be found for n=4
TEUCHOS_UNIT_TEST( GaussRadauQuadratureKernel,
		   findWeightPositiveOne )
{
  double tol = 1e-12;
  int n = 4;
 
  boost::function<double (double, int)> function_wrapper = f_x;
  Utility::GaussRadauQuadratureKernel kernel( f_x, tol, n );

  double answer = kernel.findWeightPositiveOne( n );
  TEST_FLOATING_EQUALITY( answer, 2.0/5.0, tol );

  answer = kernel.findWeightPositiveOne( 3 );
  TEST_FLOATING_EQUALITY( answer, 1.0/2.0, tol );

  answer = kernel.findWeightPositiveOne( 2 );
  TEST_FLOATING_EQUALITY( answer, 2.0/3.0, tol );

  answer = kernel.findWeightPositiveOne( 1 );
  TEST_FLOATING_EQUALITY( answer, 1.0, tol );
}

//---------------------------------------------------------------------------//
// Check that nodes and weights can be found for n=4
TEUCHOS_UNIT_TEST( GaussRadauQuadratureKernel,
		   findNodesAndWeights_4 )
{
  double tol = 1e-12;
  int n = 4;
  double end_point = -1.0;
 
  boost::function<double (double, int)> function_wrapper = f_x;
  Utility::GaussRadauQuadratureKernel kernel( f_x, tol, n );

  Teuchos::Array<double> nodes( n+1 );
  Teuchos::Array<double> weights( n+1 );

  kernel.findNodesAndWeights( end_point, nodes, weights );

  TEST_FLOATING_EQUALITY( nodes[0], -1.0, tol );
  TEST_FLOATING_EQUALITY( nodes[1], -0.720480271312439, tol );
  TEST_FLOATING_EQUALITY( nodes[2], -0.167180864737834, tol );
  TEST_FLOATING_EQUALITY( nodes[3], 0.446313972723752, tol );
  TEST_FLOATING_EQUALITY( nodes[4], 0.885791607770965, tol );

  TEST_FLOATING_EQUALITY( weights[0], 0.080000000000000, tol );
  TEST_FLOATING_EQUALITY( weights[1], 0.446207802167143, tol );
  TEST_FLOATING_EQUALITY( weights[2], 0.623653045951483, tol );
  TEST_FLOATING_EQUALITY( weights[3], 0.562712030298924, tol );
  TEST_FLOATING_EQUALITY( weights[4], 0.287427121582452, tol );
}
*/
//---------------------------------------------------------------------------//
// end tstGaussRadauQuadratureKernel.cpp
//---------------------------------------------------------------------------//
