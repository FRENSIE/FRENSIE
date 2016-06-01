//---------------------------------------------------------------------------//
//!
//! \file   tstGaussKronrodIntegrator.cpp
//! \author Luke Kersting
//! \brief  Gauss-Kronrod quadrature integrator unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <limits>

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/math/tools/precision.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Utility_GaussKronrodIntegrator.hpp"

typedef boost::multiprecision::cpp_dec_float_50 long_float;

//---------------------------------------------------------------------------//
// Testing Functors
//---------------------------------------------------------------------------//
struct X2Functor
{
  double operator()( const double x ) const
  {
    if( x >= 0.0 && x <= 1.0 )
      return x*x;
    else
      return 0.0;
  }
  
  static double getIntegratedValue()
  {
    return 1.0/3.0;
  }

  static double getLowerIntegratedValue()
  {
    return 1.0/24.0;
  }

  static double getUpperIntegratedValue()
  {
    return 7.0/24.0;
  }
};

struct X2FunctorLong
{
  long double operator()( const long double x ) const
  {
    if( x >= 0.0L && x <= 1.0L )
      return x*x;
    else
      return 0.0L;
  }
  
  static long double getIntegratedValue()
  {
    return 1.0L/3.0L;
  }

  static long double getLowerIntegratedValue()
  {
    return 1.0L/24.0L;
  }

  static long double getUpperIntegratedValue()
  {
    return 7.0L/24.0L;
  }
};

struct X2FunctorBoost
{
  long_float operator()( const long_float x ) const
  {
    if( x >= 0.0L && x <= 1.0L )
      return x*x;
    else
      return 0.0L;
  }
  
  static long_float getIntegratedValue()
  {
    return 1.0L/3.0L;
  }

  static long_float getLowerIntegratedValue()
  {
    return 1.0L/24.0L;
  }

  static long_float getUpperIntegratedValue()
  {
    return 7.0L/24.0L;
  }
};

struct X3Functor
{
  double operator()( const double x ) const
  {
    if( x >= 0.0 && x <= 1.0 )
      return x*x*x;
    else
      return 0.0;
  }

  static double getIntegratedValue()
  {
    return 0.25;
  }

  static double getLowerIntegratedValue()
  {
    return 1.0/64.0;
  }

  static double getUpperIntegratedValue()
  {
    return 15.0/64.0;
  }
};

struct X3FunctorLong
{
  long double operator()( const long double x ) const
  {
    if( x >= 0.0L && x <= 1.0L )
      return x*x*x;
    else
      return 0.0L;
  }

  static long double getIntegratedValue()
  {
    return 0.25L;
  }

  static long double getLowerIntegratedValue()
  {
    return 1.0L/64.0L;
  }

  static long double getUpperIntegratedValue()
  {
    return 15.0L/64.0L;
  }
};

struct X3FunctorBoost
{
  long_float operator()( const long_float x ) const
  {
    if( x >= 0.0L && x <= 1.0L )
      return x*x*x;
    else
      return 0.0L;
  }

  static long_float getIntegratedValue()
  {
    return 0.25L;
  }

  static long_float getLowerIntegratedValue()
  {
    return 1.0L/64.0L;
  }

  static long_float getUpperIntegratedValue()
  {
    return 15.0L/64.0L;
  }
};

double exp_neg_x( const double x )
{
  return exp( -x );
}

double exp_neg_abs_x( const double x, const double a )
{
  return exp( -a*fabs(x) );
}

double inv_sqrt_abs_x( const double x )
{
  return 1/sqrt(fabs(x));
}

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestGaussKronrodIntegrator : public Utility::GaussKronrodIntegrator<double>
{
public:
  TestGaussKronrodIntegrator( const double relative_error_tol )
    : Utility::GaussKronrodIntegrator<double>( relative_error_tol )
  { /* ... */ }

  ~TestGaussKronrodIntegrator()
  { /* ... */ }

  // Allow public access to the GaussKronrodIntegrator protected member functions
  using Utility::GaussKronrodIntegrator<double>::calculateQuadratureIntegrandValuesAtAbscissa;
  using Utility::GaussKronrodIntegrator<double>::bisectAndIntegrateBinInterval;
  using Utility::GaussKronrodIntegrator<double>::rescaleAbsoluteError;
  using Utility::GaussKronrodIntegrator<double>::subintervalTooSmall;
  using Utility::GaussKronrodIntegrator<double>::checkRoundoffError;
  using Utility::GaussKronrodIntegrator<double>::sortBins;
  using Utility::GaussKronrodIntegrator<double>::getWynnEpsilonAlgorithmExtrapolation;
};

//---------------------------------------------------------------------------//
// Instantiation macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, X2Functor ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, X3Functor )

#define UNIT_TEST_INSTANTIATION_2( type, name ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, X2FunctorLong ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, X3FunctorLong )

#define UNIT_TEST_INSTANTIATION_3( type, name ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, X2FunctorBoost ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, X3FunctorBoost )

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that functions can be integrated over [0,1]
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( GaussKronrodIntegrator,
				                   integrateWithPointRule,
                                   Functor )
{
  Utility::GaussKronrodIntegrator<double> gk_integrator( 1e-12 );
  
  double absolute_error, result_abs, result_asc, test_result, tol;
  double result;

  Functor functor_instance;

  gk_integrator.integrateWithPointRule<15>( functor_instance, 
                                        0.0,  
                                        1.0,  
                                        result,  
                                        absolute_error,  
                                        result_abs, 
                                        result_asc );

  tol = absolute_error/result;
  test_result = result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), test_result, tol );

  gk_integrator.integrateWithPointRule<21>( functor_instance, 
                                        0.0,  
                                        1.0,  
                                        result,  
                                        absolute_error,  
                                        result_abs, 
                                        result_asc );

  tol = absolute_error/result;
  test_result = result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), test_result, tol );

  gk_integrator.integrateWithPointRule<31>( functor_instance, 
                                        0.0,  
                                        1.0,  
                                        result,  
                                        absolute_error,  
                                        result_abs, 
                                        result_asc );

  tol = absolute_error/result;
  test_result = result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), test_result, tol );

  gk_integrator.integrateWithPointRule<41>( functor_instance, 
                                        0.0,  
                                        1.0,  
                                        result,  
                                        absolute_error,  
                                        result_abs, 
                                        result_asc );

  tol = absolute_error/result;
  test_result = result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), test_result, tol );

  gk_integrator.integrateWithPointRule<51>( functor_instance, 
                                        0.0,  
                                        1.0,  
                                        result,  
                                        absolute_error,  
                                        result_abs, 
                                        result_asc );

  tol = absolute_error/result;
  test_result = result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), test_result, tol );

  gk_integrator.integrateWithPointRule<61>( functor_instance, 
                                        0.0,  
                                        1.0,  
                                        result,  
                                        absolute_error,  
                                        result_abs, 
                                        result_asc );

  tol = absolute_error/result;
  test_result = result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), test_result, tol );
}

UNIT_TEST_INSTANTIATION( GaussKronrodIntegrator, integrateWithPointRule );

//---------------------------------------------------------------------------//
// Check that quadrature integrand values can be evaulated at abscissa
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( GaussKronrodIntegrator,
				                   calculateQuadratureIntegrandValuesAtAbscissa,
                                   Functor )
{
  TestGaussKronrodIntegrator test_integrator( 1e-12 );
  
  double half_length = 0.5;
  double midpoint = 0.5;
  double abscissa = 0.5;

  double integrand_value_lower, integrand_value_upper ;

  Functor functor_instance;

  test_integrator.calculateQuadratureIntegrandValuesAtAbscissa( 
                functor_instance, 
                abscissa,
                half_length,
                midpoint,
                integrand_value_lower,
                integrand_value_upper );  


  double tol = 1e-12;

  TEST_FLOATING_EQUALITY( functor_instance( 0.25 ), integrand_value_lower, tol );
  TEST_FLOATING_EQUALITY( functor_instance( 0.75 ), integrand_value_upper, tol );
}

UNIT_TEST_INSTANTIATION( GaussKronrodIntegrator, calculateQuadratureIntegrandValuesAtAbscissa );

//---------------------------------------------------------------------------//
// Check that quadrature integrand can be bisected and integrated
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( GaussKronrodIntegrator,
				                   bisectAndIntegrateBinInterval,
                                   Functor )
{
  TestGaussKronrodIntegrator test_integrator( 1e-12 );
  
  Utility::BinTraits<double> bin, bin_1, bin_2;

  double bin_1_asc, bin_2_asc, tol_1, tol_2;

  bin.lower_limit = 0.0;
  bin.upper_limit = 1.0;
  

  Functor functor_instance;

  test_integrator.bisectAndIntegrateBinInterval<15>( 
                functor_instance, 
                bin,
                bin_1,
                bin_2,
                bin_1_asc,
                bin_2_asc );  

  tol_1 = bin_1.error/bin_1.result;
  tol_2 = bin_2.error/bin_2.result;

  TEST_FLOATING_EQUALITY( Functor::getLowerIntegratedValue(), 
                          static_cast<double>( bin_1.result ), 
                          tol_1 );
  TEST_FLOATING_EQUALITY( Functor::getUpperIntegratedValue(),
                          static_cast<double>( bin_2.result ), 
                          tol_2 );

  TEST_EQUALITY( bin_1.lower_limit, bin.lower_limit );
  TEST_FLOATING_EQUALITY( bin_1.upper_limit, 0.5, 1e-15);
  TEST_FLOATING_EQUALITY( bin_2.lower_limit, 0.5, 1e-15 );
  TEST_EQUALITY( bin_2.upper_limit, bin.upper_limit );


  test_integrator.bisectAndIntegrateBinInterval<21>( 
                functor_instance, 
                bin,
                bin_1,
                bin_2,
                bin_1_asc,
                bin_2_asc );  

  tol_1 = bin_1.error/bin_1.result;
  tol_2 = bin_2.error/bin_2.result;

  TEST_FLOATING_EQUALITY( Functor::getLowerIntegratedValue(), 
                          static_cast<double>( bin_1.result ), 
                          tol_1 );
  TEST_FLOATING_EQUALITY( Functor::getUpperIntegratedValue(),
                          static_cast<double>( bin_2.result ), 
                          tol_2 );


  test_integrator.bisectAndIntegrateBinInterval<31>( 
                functor_instance, 
                bin,
                bin_1,
                bin_2,
                bin_1_asc,
                bin_2_asc );  

  tol_1 = bin_1.error/bin_1.result;
  tol_2 = bin_2.error/bin_2.result;

  TEST_FLOATING_EQUALITY( Functor::getLowerIntegratedValue(), 
                          static_cast<double>( bin_1.result ), 
                          tol_1 );
  TEST_FLOATING_EQUALITY( Functor::getUpperIntegratedValue(),
                          static_cast<double>( bin_2.result ), 
                          tol_2 );


  test_integrator.bisectAndIntegrateBinInterval<41>( 
                functor_instance, 
                bin,
                bin_1,
                bin_2,
                bin_1_asc,
                bin_2_asc );  

  tol_1 = bin_1.error/bin_1.result;
  tol_2 = bin_2.error/bin_2.result;

  TEST_FLOATING_EQUALITY( Functor::getLowerIntegratedValue(), 
                          static_cast<double>( bin_1.result ), 
                          tol_1 );
  TEST_FLOATING_EQUALITY( Functor::getUpperIntegratedValue(),
                          static_cast<double>( bin_2.result ), 
                          tol_2 );


  test_integrator.bisectAndIntegrateBinInterval<51>( 
                functor_instance, 
                bin,
                bin_1,
                bin_2,
                bin_1_asc,
                bin_2_asc );  

  tol_1 = bin_1.error/bin_1.result;
  tol_2 = bin_2.error/bin_2.result;

  TEST_FLOATING_EQUALITY( Functor::getLowerIntegratedValue(), 
                          static_cast<double>( bin_1.result ), 
                          tol_1 );
  TEST_FLOATING_EQUALITY( Functor::getUpperIntegratedValue(),
                          static_cast<double>( bin_2.result ), 
                          tol_2 );


  test_integrator.bisectAndIntegrateBinInterval<61>( 
                functor_instance, 
                bin,
                bin_1,
                bin_2,
                bin_1_asc,
                bin_2_asc );  

  tol_1 = bin_1.error/bin_1.result;
  tol_2 = bin_2.error/bin_2.result;

  TEST_FLOATING_EQUALITY( Functor::getLowerIntegratedValue(), 
                          static_cast<double>( bin_1.result ), 
                          tol_1 );
  TEST_FLOATING_EQUALITY( Functor::getUpperIntegratedValue(),
                          static_cast<double>( bin_2.result ), 
                          tol_2 );
}

UNIT_TEST_INSTANTIATION( GaussKronrodIntegrator, bisectAndIntegrateBinInterval );

//---------------------------------------------------------------------------//
// Check that the error can be rescaled
TEUCHOS_UNIT_TEST( GaussKronrodIntegrator, 
                   rescaleAbsoluteError )
{
  TestGaussKronrodIntegrator test_integrator( 1e-12 );
  
  double absolute_error = 0.0;
  double result_abs = 0.0;
  double result_asc = 0.0;
  double tol = 1e-12;
  double limit = std::numeric_limits<double>::min() / ( 50.0 *
                   std::numeric_limits<double>::epsilon() );

  absolute_error = limit/2.0;

  test_integrator.rescaleAbsoluteError( 
                absolute_error, 
                result_abs,
                result_asc );  

  TEST_FLOATING_EQUALITY( limit/2.0, absolute_error, tol );


  absolute_error = 1.0;
  result_asc = 2.0;

  test_integrator.rescaleAbsoluteError( 
                absolute_error, 
                result_abs,
                result_asc );  

  TEST_FLOATING_EQUALITY( 2.0, absolute_error, tol );


  absolute_error = 1.0;
  result_asc = 800.0;

  test_integrator.rescaleAbsoluteError( 
                absolute_error, 
                result_abs,
                result_asc );  

  TEST_FLOATING_EQUALITY( 100.0, absolute_error, tol );


  absolute_error = 50.0*std::numeric_limits<double>::epsilon();
  result_asc = 0.0;
  result_abs = 2.0;
  double min_error = 50.0*std::numeric_limits<double>::epsilon() * result_abs;

  test_integrator.rescaleAbsoluteError( 
                absolute_error, 
                result_abs,
                result_asc );  

  TEST_FLOATING_EQUALITY( min_error, absolute_error, tol );
}

//---------------------------------------------------------------------------//
// Check the roundoff error
TEUCHOS_UNIT_TEST( GaussKronrodIntegrator, 
                   checkRoundoffError )
{
  TestGaussKronrodIntegrator test_integrator( 1e-12 );
  
  Utility::BinTraits<double> bin, bin_1, bin_2;
  int round_off_1 = 0;
  int round_off_2 = 0;
  int number_of_interactions = 0;
  double error_12 = 0.0, bin_1_asc = 0.0, bin_2_asc = 0.0;
  double tol = 1e-12;

  bin.result = 9.9999;
  bin_1.result = 5.0;
  bin_2.result = 5.0;

  bin.error = 1.0;
  bin_1.error = 0.5;
  bin_2.error = 0.49;

  bin_1_asc = bin_1.error;
  bin_2_asc = bin_2.error;


  test_integrator.checkRoundoffError( 
                bin, 
                bin_1,
                bin_2,
                bin_1_asc,
                bin_2_asc,
                round_off_1,
                round_off_2,
                number_of_interactions );  

  TEST_EQUALITY_CONST( 0, round_off_1 );
  TEST_EQUALITY_CONST( 0, round_off_2 );

  bin_1_asc = 0.0;
  bin_2_asc = 0.0;


  test_integrator.checkRoundoffError( 
                bin, 
                bin_1,
                bin_2,
                bin_1_asc,
                bin_2_asc,
                round_off_1,
                round_off_2,
                number_of_interactions );  

  TEST_EQUALITY_CONST( 1, round_off_1 );
  TEST_EQUALITY_CONST( 0, round_off_2 );


  bin_2.error = 0.501;
  number_of_interactions = 10;

  test_integrator.checkRoundoffError( 
                bin, 
                bin_1,
                bin_2,
                bin_1_asc,
                bin_2_asc,
                round_off_1,
                round_off_2,
                number_of_interactions );  

  TEST_EQUALITY_CONST( 2, round_off_1 );
  TEST_EQUALITY_CONST( 1, round_off_2 );


  bin.result = 9.9;

  test_integrator.checkRoundoffError( 
                bin, 
                bin_1,
                bin_2,
                bin_1_asc,
                bin_2_asc,
                round_off_1,
                round_off_2,
                number_of_interactions );  

  TEST_EQUALITY_CONST( 2, round_off_1 );
  TEST_EQUALITY_CONST( 2, round_off_2 );
}

//---------------------------------------------------------------------------//
// Check the roundoff error
TEUCHOS_UNIT_TEST( GaussKronrodIntegrator, 
                   checkRoundoffError2 )
{
  TestGaussKronrodIntegrator test_integrator( 1e-12 );
  
  Utility::ExtrpolatedBinTraits<double> bin, bin_1, bin_2;
  int round_off_1 = 0;
  int round_off_2 = 0;
  int round_off_3 = 0;
  int number_of_interactions = 0;
  bool extrapolate = false;
  double error_12 = 0.0, bin_1_asc = 0.0, bin_2_asc = 0.0;
  double tol = 1e-12;

  bin.result = 9.9999;
  bin_1.result = 5.0;
  bin_2.result = 5.0;

  bin.error = 1.0;
  bin_1.error = 0.5;
  bin_2.error = 0.49;

  bin_1_asc = bin_1.error;
  bin_2_asc = bin_2.error;


  test_integrator.checkRoundoffError( 
                bin, 
                bin_1,
                bin_2,
                bin_1_asc,
                bin_2_asc,
                round_off_1,
                round_off_2,
                round_off_3,
                extrapolate,
                number_of_interactions );  

  TEST_EQUALITY_CONST( 0, round_off_1 );
  TEST_EQUALITY_CONST( 0, round_off_2 );
  TEST_EQUALITY_CONST( 0, round_off_3 );

  bin_1_asc = 0.0;
  bin_2_asc = 0.0;


  test_integrator.checkRoundoffError( 
                bin, 
                bin_1,
                bin_2,
                bin_1_asc,
                bin_2_asc,
                round_off_1,
                round_off_2,
                round_off_3,
                extrapolate,
                number_of_interactions );  

  TEST_EQUALITY_CONST( 1, round_off_1 );
  TEST_EQUALITY_CONST( 0, round_off_2 );
  TEST_EQUALITY_CONST( 0, round_off_3 );

  extrapolate = true;

  test_integrator.checkRoundoffError( 
                bin, 
                bin_1,
                bin_2,
                bin_1_asc,
                bin_2_asc,
                round_off_1,
                round_off_2,
                round_off_3,
                extrapolate,
                number_of_interactions );  

  TEST_EQUALITY_CONST( 1, round_off_1 );
  TEST_EQUALITY_CONST( 1, round_off_2 );
  TEST_EQUALITY_CONST( 0, round_off_3 );

  bin_2.error = 0.501;
  number_of_interactions = 10;

  test_integrator.checkRoundoffError( 
                bin, 
                bin_1,
                bin_2,
                bin_1_asc,
                bin_2_asc,
                round_off_1,
                round_off_2,
                round_off_3,
                extrapolate,
                number_of_interactions );   

  TEST_EQUALITY_CONST( 1, round_off_1 );
  TEST_EQUALITY_CONST( 2, round_off_2 );
  TEST_EQUALITY_CONST( 1, round_off_3 );


  bin.result = 9.9;

  test_integrator.checkRoundoffError( 
                bin, 
                bin_1,
                bin_2,
                bin_1_asc,
                bin_2_asc,
                round_off_1,
                round_off_2,
                round_off_3,
                extrapolate,
                number_of_interactions );   

  TEST_EQUALITY_CONST( 1, round_off_1 );
  TEST_EQUALITY_CONST( 2, round_off_2 );
  TEST_EQUALITY_CONST( 2, round_off_3 );
}

//---------------------------------------------------------------------------//
// Check that the error list can be sorted
TEUCHOS_UNIT_TEST( GaussKronrodIntegrator, 
                   sortBins )
{
  TestGaussKronrodIntegrator test_integrator( 1e-12 );
  
  Utility::ExtrpolatedBinTraits<double> bin, bin_1, bin_2;
  
  int nr_max = 0;
  int number_of_intervals = 3;

  // Set up bin order array
  Teuchos::Array<int> bin_order(3);
  bin_order[0] = 0;
  bin_order[1] = 1;
  bin_order[2] = 2;

  // Set bin array
  Utility::GaussKronrodIntegrator<double>::BinArray bin_array(1000);
  bin.error = 10.0;
  bin_array[0] = bin;
  bin.error = 8.0;
  bin_array[1] = bin;
  bin.error = 1.0;
  bin_array[2] = bin;

  // Set bin_1 and bin_2
  bin_1.error = 5.0;
  bin_2.error = 2.0;
 
  test_integrator.sortBins( 
                bin_order, 
                bin_array,
                bin_1,
                bin_2,
                number_of_intervals,
                nr_max );  

  TEST_EQUALITY_CONST( 1, bin_order[0] );
  TEST_EQUALITY_CONST( 0, bin_order[1] );
  TEST_EQUALITY_CONST( 3, bin_order[2] );
  TEST_EQUALITY_CONST( 2, bin_order[3] );
  TEST_EQUALITY_CONST( 0, nr_max );

  // Test with nr_max != 0
  nr_max = 1;
  number_of_intervals = 3;

  // Set up bin order array
  bin_order.resize(3);
  bin_order[0] = 0;
  bin_order[1] = 1;
  bin_order[2] = 2;

  // Set bin array
  bin.error = 10.0;
  bin_array[0] = bin;
  bin.error = 8.0;
  bin_array[1] = bin;
  bin.error = 1.0;
  bin_array[2] = bin;

  // Set bin_1 and bin_2
  bin_1.error = 11.0;
  bin_2.error = 2.0;
 
  test_integrator.sortBins( 
                bin_order, 
                bin_array,
                bin_1,
                bin_2,
                number_of_intervals,
                nr_max ); 

  TEST_EQUALITY_CONST( 1, bin_order[0] );
  TEST_EQUALITY_CONST( 0, bin_order[1] );
  TEST_EQUALITY_CONST( 3, bin_order[2] );
  TEST_EQUALITY_CONST( 2, bin_order[3] );
  TEST_EQUALITY_CONST( 0, nr_max );


  // Test 3
  nr_max = 0;
  number_of_intervals = 3;

  // Set up bin order array
  bin_order.resize(3);
  bin_order[0] = 1;
  bin_order[1] = 0;
  bin_order[2] = 2;

  bin_array.clear();

  // Set bin array
  bin.error = 0.673651;
  bin_array[0] = bin;
  bin.error = 1.90537;
  bin_array[1] = bin;
  bin.error = 6.50354e-15;
  bin_array[2] = bin;

  // Set bin_1 and bin_2
  bin_1.error = 0.673652;
  bin_2.error = 6.50353e-15;

  test_integrator.sortBins( 
                bin_order, 
                bin_array,
                bin_1,
                bin_2,
                number_of_intervals,
                nr_max ); 

  TEST_EQUALITY_CONST( 1, bin_order[0] );
  TEST_EQUALITY_CONST( 0, bin_order[1] );
  TEST_EQUALITY_CONST( 2, bin_order[2] );
  TEST_EQUALITY_CONST( 3, bin_order[3] );
  TEST_EQUALITY_CONST( 0, nr_max );

  // Test 4
  nr_max = 3;
  number_of_intervals = 6;

  // Set up bin order array
  bin_order.resize(6);
  bin_order[0] = 3;
  bin_order[1] = 4;
  bin_order[2] = 0;
  bin_order[3] = 2;
  bin_order[4] = 1;
  bin_order[5] = 5;

  bin_array.clear();

  // Set bin array
  bin.error = 4.0;
  bin_array[0] = bin;
  bin.error = 2.0;
  bin_array[1] = bin;
  bin.error = 3.0;
  bin_array[2] = bin;
  bin.error = 6.0;
  bin_array[3] = bin;
  bin.error = 5.0;
  bin_array[4] = bin;
  bin.error = 1.0;
  bin_array[5] = bin;

  // Set bin_1 and bin_2
  bin_1.error = 2.5;
  bin_2.error = 0.5;

  test_integrator.sortBins( 
                bin_order, 
                bin_array,
                bin_1,
                bin_2,
                number_of_intervals,
                nr_max ); 

  TEST_EQUALITY_CONST( 3, bin_order[0] );
  TEST_EQUALITY_CONST( 4, bin_order[1] );
  TEST_EQUALITY_CONST( 0, bin_order[2] );
  TEST_EQUALITY_CONST( 2, bin_order[3] );
  TEST_EQUALITY_CONST( 1, bin_order[4] );
  TEST_EQUALITY_CONST( 5, bin_order[5] );
  TEST_EQUALITY_CONST( 6, bin_order[6] );
  TEST_EQUALITY_CONST( 3, nr_max );

  // Test 5
  nr_max = 3;
  number_of_intervals = 6;

  // Set up bin order array
  bin_order.resize(6);
  bin_order[0] = 3;
  bin_order[1] = 4;
  bin_order[2] = 0;
  bin_order[3] = 2;
  bin_order[4] = 1;
  bin_order[5] = 5;

  bin_array.clear();

  // Set bin array
  bin.error = 4.0;
  bin_array[0] = bin;
  bin.error = 2.0;
  bin_array[1] = bin;
  bin.error = 3.0;
  bin_array[2] = bin;
  bin.error = 6.0;
  bin_array[3] = bin;
  bin.error = 5.0;
  bin_array[4] = bin;
  bin.error = 1.0;
  bin_array[5] = bin;

  // Set bin_1 and bin_2
  bin_1.error = 4.5;
  bin_2.error = 0.5;

  test_integrator.sortBins( 
                bin_order, 
                bin_array,
                bin_1,
                bin_2,
                number_of_intervals,
                nr_max ); 

  TEST_EQUALITY_CONST( 3, bin_order[0] );
  TEST_EQUALITY_CONST( 4, bin_order[1] );
  TEST_EQUALITY_CONST( 2, bin_order[2] );
  TEST_EQUALITY_CONST( 0, bin_order[3] );
  TEST_EQUALITY_CONST( 1, bin_order[4] );
  TEST_EQUALITY_CONST( 5, bin_order[5] );
  TEST_EQUALITY_CONST( 6, bin_order[6] );
  TEST_EQUALITY_CONST( 2, nr_max );
}

//---------------------------------------------------------------------------//
// Check that the Wynn Epsilon-Algorithm extrapolated value can be calculated
TEUCHOS_UNIT_TEST( GaussKronrodIntegrator, 
                   getWynnEpsilonAlgorithmExtrapolation )
{
  TestGaussKronrodIntegrator test_integrator( 1e-12 );
  
  Teuchos::Array<double> bin_extrapolated_result(52);
  Teuchos::Array<double> last_three_results(3);
  double extrapolated_result, extrapolated_error;
  int number_of_extrapolated_intervals, number_of_extrapolated_calls;
  double tol = 1e-16;
  number_of_extrapolated_calls = 0;

  // test 1
  number_of_extrapolated_intervals = 2;
  bin_extrapolated_result[0] = 3.93505142975913369L;
  bin_extrapolated_result[1] = 3.95407442555431254L;
  bin_extrapolated_result[2] = 3.96752571487956640L;
 
  test_integrator.getWynnEpsilonAlgorithmExtrapolation( 
                bin_extrapolated_result, 
                last_three_results,
                extrapolated_result,
                extrapolated_error,
                number_of_extrapolated_intervals,
                number_of_extrapolated_calls ); 

  TEST_EQUALITY_CONST( number_of_extrapolated_intervals, 2 );
  TEST_EQUALITY_CONST( number_of_extrapolated_calls, 1 ); 
  TEST_FLOATING_EQUALITY( extrapolated_error, 
                          std::numeric_limits<double>::max(), 
                          tol );
  TEST_FLOATING_EQUALITY( extrapolated_result, 
                          3.99999999999999645, 
                          tol );
  TEST_FLOATING_EQUALITY( last_three_results[0], 
                          3.99999999999999645, 
                          tol );
  TEST_FLOATING_EQUALITY( last_three_results[1], 
                          0.0, 
                          tol );
  TEST_FLOATING_EQUALITY( last_three_results[2], 
                          0.0, 
                          tol );

  // test 2
  number_of_extrapolated_intervals = 3;
  bin_extrapolated_result[0] = 3.99999999999999645L;
  bin_extrapolated_result[1] = 3.95407442555431254L;
  bin_extrapolated_result[2] = 3.96752571487956640L;
  bin_extrapolated_result[3] = 3.97703721277715605L;
  bin_extrapolated_result[4] = 3.96752571487956640L;
 
  test_integrator.getWynnEpsilonAlgorithmExtrapolation( 
                bin_extrapolated_result, 
                last_three_results,
                extrapolated_result,
                extrapolated_error,
                number_of_extrapolated_intervals,
                number_of_extrapolated_calls ); 

  TEST_EQUALITY_CONST( number_of_extrapolated_intervals, 3 );
  TEST_EQUALITY_CONST( number_of_extrapolated_calls, 2 ); 
  TEST_FLOATING_EQUALITY( extrapolated_error, 
                          std::numeric_limits<double>::max(), 
                          tol );
  TEST_FLOATING_EQUALITY( extrapolated_result, 
                          4.00000000000000355, 
                          tol );
  TEST_FLOATING_EQUALITY( last_three_results[0], 
                          3.99999999999999645, 
                          tol );
  TEST_FLOATING_EQUALITY( last_three_results[1], 
                          4.00000000000000355, 
                          tol );
  TEST_FLOATING_EQUALITY( last_three_results[2], 
                          0.0, 
                          tol );


  // test 3
  number_of_extrapolated_intervals = 4;
  bin_extrapolated_result[0] = 3.99999999999999645L;
  bin_extrapolated_result[1] = 4.00000000000000355L;
  bin_extrapolated_result[2] = 3.96752571487956640L;
  bin_extrapolated_result[3] = 3.97703721277715605L;
  bin_extrapolated_result[4] = 3.98376285743978320L;
  bin_extrapolated_result[5] = 3.97703721277715605L;
 
  test_integrator.getWynnEpsilonAlgorithmExtrapolation( 
                bin_extrapolated_result, 
                last_three_results,
                extrapolated_result,
                extrapolated_error,
                number_of_extrapolated_intervals,
                number_of_extrapolated_calls ); 

  TEST_EQUALITY_CONST( number_of_extrapolated_intervals, 4 );
  TEST_EQUALITY_CONST( number_of_extrapolated_calls, 3 ); 
  TEST_FLOATING_EQUALITY( extrapolated_error, 
                          std::numeric_limits<double>::max(), 
                          tol );
  TEST_FLOATING_EQUALITY( extrapolated_result, 
                          4.00000000000000089, 
                          tol );
  TEST_FLOATING_EQUALITY( last_three_results[0], 
                          3.99999999999999645, 
                          tol );
  TEST_FLOATING_EQUALITY( last_three_results[1], 
                          4.00000000000000355, 
                          tol );
  TEST_FLOATING_EQUALITY( last_three_results[2], 
                          4.00000000000000089, 
                          tol );


  // test 4
  number_of_extrapolated_intervals = 5;
  bin_extrapolated_result[0] = 4.00000000000000089L;
  bin_extrapolated_result[1] = 4.00000000000000355L;
  bin_extrapolated_result[2] = 3.99999999999999911L;
  bin_extrapolated_result[3] = 3.97703721277715605L;
  bin_extrapolated_result[4] = 3.98376285743978320L;
  bin_extrapolated_result[5] = 3.98851860638857758L;
  bin_extrapolated_result[6] = 3.98376285743978320L;

 
  test_integrator.getWynnEpsilonAlgorithmExtrapolation( 
                bin_extrapolated_result, 
                last_three_results,
                extrapolated_result,
                extrapolated_error,
                number_of_extrapolated_intervals,
                number_of_extrapolated_calls ); 

  TEST_EQUALITY_CONST( number_of_extrapolated_intervals, 5 );
  TEST_EQUALITY_CONST( number_of_extrapolated_calls, 4 ); 
  TEST_FLOATING_EQUALITY( extrapolated_error, 
                          5.68434188608080149e-14, 
                          tol );
  TEST_FLOATING_EQUALITY( extrapolated_result, 
                          3.99999999999998135, 
                          tol );
  TEST_FLOATING_EQUALITY( last_three_results[0], 
                          4.00000000000000355, 
                          tol );
  TEST_FLOATING_EQUALITY( last_three_results[1], 
                          4.00000000000000089, 
                          tol );
  TEST_FLOATING_EQUALITY( last_three_results[2], 
                          3.99999999999998135, 
                          tol );

}

//---------------------------------------------------------------------------//
// Check that functions can be integrated over [0,1] adaptively
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( GaussKronrodIntegrator,
				   integrateAdaptively,
				   Functor )
{
  Utility::GaussKronrodIntegrator<double> gk_integrator( 1e-12 );

  double result, absolute_error, tol;

  Functor functor_instance;

  // Test the 15-point rule
  gk_integrator.integrateAdaptively<15>( functor_instance, 
				  0.0, 
				  1.0, 
				  result, 
				  absolute_error );

  tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), result, tol );


  // Test the 21-point rule
  gk_integrator.integrateAdaptively<21>( functor_instance, 
				  0.0, 
				  1.0, 
				  result, 
				  absolute_error );

  tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), result, tol );


  // Test the 31-point rule
  gk_integrator.integrateAdaptively<31>( functor_instance, 
				  0.0, 
				  1.0, 
				  result, 
				  absolute_error );

  tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), result, tol );


  // Test the 41-point rule
  gk_integrator.integrateAdaptively<41>( functor_instance, 
				  0.0, 
				  1.0, 
				  result, 
				  absolute_error );

  tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), result, tol );


  // Test the 51-point rule
  gk_integrator.integrateAdaptively<51>( functor_instance, 
				  0.0, 
				  1.0, 
				  result, 
				  absolute_error );

  tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), result, tol );


  // Test the 61-point rule
  gk_integrator.integrateAdaptively<61>( functor_instance, 
				  0.0, 
				  1.0, 
				  result, 
				  absolute_error );

  tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), result, tol );
}

UNIT_TEST_INSTANTIATION( GaussKronrodIntegrator, integrateAdaptively );

//---------------------------------------------------------------------------//
// Check that functions can be integrated over [0,1] adaptively
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( GaussKronrodIntegrator,
				   integrateAdaptively_long_double,
				   Functor )
{
  Utility::GaussKronrodIntegrator<long double> gk_integrator( 1e-12 );

  long double result, absolute_error, tol;

  Functor functor_instance;

  // Test the 15-point rule
  gk_integrator.integrateAdaptively<15>( functor_instance, 
				  0.0L, 
				  1.0L, 
				  result, 
				  absolute_error );

  tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( (double)Functor::getIntegratedValue(), 
                          (double)result, 
                          (double)tol );


  // Test the 21-point rule
  gk_integrator.integrateAdaptively<21>( functor_instance, 
				  0.0L, 
				  1.0L, 
				  result, 
				  absolute_error );

  tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( (double)Functor::getIntegratedValue(), 
                          (double)result, 
                          (double)tol );


  // Test the 31-point rule
  gk_integrator.integrateAdaptively<31>( functor_instance, 
				  0.0L, 
				  1.0L, 
				  result, 
				  absolute_error );

  tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( (double)Functor::getIntegratedValue(), 
                          (double)result, 
                          (double)tol );


  // Test the 41-point rule
  gk_integrator.integrateAdaptively<41>( functor_instance, 
				  0.0L, 
				  1.0L, 
				  result, 
				  absolute_error );

  tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( (double)Functor::getIntegratedValue(), 
                          (double)result, 
                          (double)tol );


  // Test the 51-point rule
  gk_integrator.integrateAdaptively<51>( functor_instance, 
				  0.0L, 
				  1.0L, 
				  result, 
				  absolute_error );

  tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( (double)Functor::getIntegratedValue(), 
                          (double)result, 
                          (double)tol );


  // Test the 61-point rule
  gk_integrator.integrateAdaptively<61>( functor_instance, 
				  0.0L, 
				  1.0L, 
				  result, 
				  absolute_error );

  tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( (double)Functor::getIntegratedValue(), 
                          (double)result, 
                          (double)tol );

}

UNIT_TEST_INSTANTIATION_2( GaussKronrodIntegrator, integrateAdaptively_long_double );

//---------------------------------------------------------------------------//
// Check that functions can be integrated over [0,1] adaptively
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( GaussKronrodIntegrator,
				   integrateAdaptively_long_float,
				   Functor )
{
  Utility::GaussKronrodIntegrator<long_float> gk_integrator( 1e-12 );

  long_float result, absolute_error, tol;

  Functor functor_instance;

  // Test the 15-point rule
  gk_integrator.integrateAdaptively<15>( functor_instance, 
				  (long_float)0, 
				  (long_float)1, 
				  result, 
				  absolute_error );
/*
  tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( (double)Functor::getIntegratedValue(), 
                          (double)result, 
                          (double)tol );


  // Test the 21-point rule
  gk_integrator.integrateAdaptively<21>( functor_instance, 
				  (long_float)0, 
				  (long_float)1, 
				  result, 
				  absolute_error );

  tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( (double)Functor::getIntegratedValue(), 
                          (double)result, 
                          (double)tol );


  // Test the 31-point rule
  gk_integrator.integrateAdaptively<31>( functor_instance, 
				  (long_float)0, 
				  (long_float)1,  
				  result, 
				  absolute_error );

  tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( (double)Functor::getIntegratedValue(), 
                          (double)result, 
                          (double)tol );


  // Test the 41-point rule
  gk_integrator.integrateAdaptively<41>( functor_instance, 
				  (long_float)0, 
				  (long_float)1, 
				  result, 
				  absolute_error );

  tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( (double)Functor::getIntegratedValue(), 
                          (double)result, 
                          (double)tol );


  // Test the 51-point rule
  gk_integrator.integrateAdaptively<51>( functor_instance, 
				  (long_float)0, 
				  (long_float)1, 
				  result, 
				  absolute_error );

  tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( (double)Functor::getIntegratedValue(), 
                          (double)result, 
                          (double)tol );


  // Test the 61-point rule
  gk_integrator.integrateAdaptively<61>( functor_instance, 
				  (long_float)0, 
				  (long_float)1, 
				  result, 
				  absolute_error );

  tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( (double)Functor::getIntegratedValue(), 
                          (double)result, 
                          (double)tol );*/
}

UNIT_TEST_INSTANTIATION_3( GaussKronrodIntegrator, integrateAdaptively_long_float );

//---------------------------------------------------------------------------//
// Check that a function with integrable singularities can be integrated
TEUCHOS_UNIT_TEST( GaussKronrodIntegrator,
		   integrateAdaptivelyWynnEpsilon )
{
  boost::function<double (double x)> function_wrapper = inv_sqrt_abs_x;

  Teuchos::Array<double> points_of_interest( 3 );
  points_of_interest[0] = -1.0;
  points_of_interest[1] = 0.0; // integrable singularity
  points_of_interest[2] = 1.0;

  Utility::GaussKronrodIntegrator<double> gk_int( 1e-12, 0.0, 100000 );

  double result, absolute_error;

  gk_int.integrateAdaptivelyWynnEpsilon( function_wrapper,
					 points_of_interest(),
					 result,
					 absolute_error );

  
  double tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( result, 4.0, tol );
}

//---------------------------------------------------------------------------//
// Check that a function with no singularities can be integrated using Wynn Epsilon
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( GaussKronrodIntegrator,
                                   integrateAdaptivelyWynnEpsilon_no_singularities,
                                   Functor )
{
  Functor functor_instance;

  Teuchos::Array<double> points_of_interest( 3 );
  points_of_interest[0] = 0.0;
  points_of_interest[1] = 0.5;
  points_of_interest[2] = 1.0;

  Utility::GaussKronrodIntegrator<double> gkq_set( 1e-12, 0.0, 100000 );

  double result, absolute_error;

  gkq_set.integrateAdaptivelyWynnEpsilon( 
            functor_instance,
    		points_of_interest(),
			result,
			absolute_error );
  
  double tol = absolute_error/result;

  TEST_FLOATING_EQUALITY( Functor::getIntegratedValue(), result, tol );
}

UNIT_TEST_INSTANTIATION( GaussKronrodIntegrator, integrateAdaptivelyWynnEpsilon_no_singularities );

//---------------------------------------------------------------------------//
// end tstGaussKronrodIntegrator.cpp
//---------------------------------------------------------------------------//
