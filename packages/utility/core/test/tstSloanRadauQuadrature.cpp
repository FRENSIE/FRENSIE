//---------------------------------------------------------------------------//
//!
//! \file   tstSloanRadauquadrature->cpp
//! \author Luke Kersting
//! \brief  Sloan implentation of Gauss-Radau quadrature unit tests.
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
#include "Utility_SloanRadauQuadrature.hpp"
#include "Utility_LegendrePolynomial.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

// P_4 expansion test variables
Teuchos::Array<long double> legendre_moments( 5 ), radau_moments( 4 ),
  normalization_factors_N( 3 ), normalization_ratios( 3 ), 
  variances( 3 ), mean_coefficients( 3 );//, weights_4( 3 );
Teuchos::Array<double> weights_4( 3 );

Teuchos::TwoDArray<double> orthogonal_coefficients( 3, 3 );
Teuchos::TwoDArray<double> roots( 3, 2 );

// P_8 expansion test variables
Teuchos::Array<long double> legendre_moments_8( 9 ), radau_moments_8( 8 ),  
  normalization_factors_N_8( 5 ), normalization_ratios_8( 5 ), 
  variances_8( 5 ), mean_coefficients_8( 5 );//, weights_8( 5 );
Teuchos::Array<double> weights_8( 5 );

Teuchos::TwoDArray<double> roots_8( 5, 4 );

// Moments from nodes and weights
Teuchos::Array<double> test_roots( 8 );
Teuchos::Array<long double> test_legendre( 17 );
double test_weight;


Teuchos::RCP<Utility::SloanRadauQuadrature> quadrature, 
                                            quadrature_8,
                                            test_quadrature;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
/*
// Check that the Radau moments can be returned
TEUCHOS_UNIT_TEST( SloanRadauQuadrature,
		           getRadauMoments )
{
  double number_of_moments = 4;
  Teuchos::Array<long double> legendre_moment( number_of_moments+1 );
  Teuchos::Array<double> radau_moment( number_of_moments );

  legendre_moment[0] = 1.00000000000000;
  legendre_moment[1] = 19.0/20.0;
  legendre_moment[2] = 18.0/20.0;
  legendre_moment[3] = 17.0/20.0;
  legendre_moment[4] = 16.0/20.0;

  Utility::SloanRadauQuadrature quadrature2( legendre_moment );

  quadrature2.getRadauMoments( radau_moment );

  TEST_FLOATING_EQUALITY( radau_moment[0], .05, 1e-14);
  TEST_FLOATING_EQUALITY( radau_moment[1], 1.0/60.0, 1e-14);
  TEST_FLOATING_EQUALITY( radau_moment[2], 14.0/15.0 - 91.0/100.0, 1e-14);
  TEST_FLOATING_EQUALITY( radau_moment[3], 91.0/100.0 - 157.0/175.0, 1e-14);

  number_of_moments = 8;
  radau_moment.resize( number_of_moments );

  quadrature_8->getRadauMoments( radau_moment );

  TEST_FLOATING_EQUALITY( radau_moment[0], radau_moments_8[0], 1e-14);
  TEST_FLOATING_EQUALITY( radau_moment[1], radau_moments_8[1], 1e-14);
  TEST_FLOATING_EQUALITY( radau_moment[2], radau_moments_8[2], 1e-14);
  TEST_FLOATING_EQUALITY( radau_moment[3], radau_moments_8[3], 1e-14);
  TEST_FLOATING_EQUALITY( radau_moment[4], radau_moments_8[4], 1e-14);
  TEST_FLOATING_EQUALITY( radau_moment[5], radau_moments_8[5], 1e-14);
  TEST_FLOATING_EQUALITY( radau_moment[6], radau_moments_8[6], 1e-14);
  TEST_FLOATING_EQUALITY( radau_moment[7], radau_moments_8[7], 1e-14);

}

//---------------------------------------------------------------------------//
// Check that the Long Radau moments can be returned
TEUCHOS_UNIT_TEST( SloanRadauQuadrature,
		           getLongRadauMoments )
{
  int number_of_radau_moments = 8;
  Teuchos::Array<double> radau_moment( number_of_radau_moments );
  Teuchos::Array<long double> long_radau_moment( number_of_radau_moments );

  quadrature_8->getRadauMoments( radau_moment );
  quadrature_8->getLongRadauMoments( long_radau_moment );

  Teuchos::Array<double> moments( number_of_radau_moments );
  for ( int i = 0; i < number_of_radau_moments; i++ )
  {
    moments[i] = long_radau_moment[i];
  }
std::cout << std::endl << " rel err 0 = " << (long_radau_moment[0]-moments_8[0])/ moments_8[0] << std::endl;
std::cout << " rel err 1 = " << (long_radau_moment[1]-moments_8[1])/ moments_8[1] << std::endl;
std::cout << " rel err 2 = " << (long_radau_moment[2]-moments_8[2])/ moments_8[2] << std::endl;
std::cout << " rel err 3 = " << (long_radau_moment[3]-moments_8[3])/ moments_8[3] << std::endl;
std::cout << " rel err 4 = " << (long_radau_moment[4]-moments_8[4])/ moments_8[4] << std::endl;
std::cout << " rel err 5 = " << (long_radau_moment[5]-moments_8[5])/ moments_8[5] << std::endl;
std::cout << " rel err 6 = " << (long_radau_moment[6]-moments_8[6])/ moments_8[6] << std::endl;
std::cout << " rel err 7 = " << (long_radau_moment[7]-moments_8[7])/ moments_8[7] << std::endl;
  TEST_FLOATING_EQUALITY( moments[0], radau_moments_8[0], 1e-14);
  TEST_FLOATING_EQUALITY( moments[1], radau_moments_8[1], 1e-14);
  TEST_FLOATING_EQUALITY( moments[2], radau_moments_8[2], 1e-14);
  TEST_FLOATING_EQUALITY( moments[3], radau_moments_8[3], 1e-14);
  TEST_FLOATING_EQUALITY( moments[4], radau_moments_8[4], 1e-14);
  TEST_FLOATING_EQUALITY( moments[5], radau_moments_8[5], 1e-14);
  TEST_FLOATING_EQUALITY( moments[6], radau_moments_8[6], 1e-14);
  TEST_FLOATING_EQUALITY( moments[7], radau_moments_8[7], 1e-14);

  TEST_FLOATING_EQUALITY( long_radau_moment[0], moments_8[0], 1e-14);
  TEST_FLOATING_EQUALITY( long_radau_moment[1], moments_8[1], 1e-14);
  TEST_FLOATING_EQUALITY( long_radau_moment[2], moments_8[2], 1e-14);
  TEST_FLOATING_EQUALITY( long_radau_moment[3], moments_8[3], 1e-14);
  TEST_FLOATING_EQUALITY( long_radau_moment[4], moments_8[4], 1e-14);
  TEST_FLOATING_EQUALITY( long_radau_moment[5], moments_8[5], 1e-14);
  TEST_FLOATING_EQUALITY( long_radau_moment[6], moments_8[6], 1e-14);
  TEST_FLOATING_EQUALITY( long_radau_moment[7], moments_8[7], 1e-14);
}

//---------------------------------------------------------------------------//
// Check that the mean coefficients for orthogonal polynomial recursion relation can be evaluated
TEUCHOS_UNIT_TEST( SloanRadauQuadrature,
		           evaluateOrthogonalNormalizationRatio )
{
  int i = 1;
  Teuchos::Array<double> ratios( 3 );

  quadrature->evaluateOrthogonalNormalizationRatio( ratios,
                                                    orthogonal_coefficients,
                                                    normalization_factors_N,
                                                    radau_moments,
                                                    i );

  TEST_FLOATING_EQUALITY( ratios[i], normalization_ratios[i], 1e-12);

  i = 2;
  quadrature->evaluateOrthogonalNormalizationRatio( ratios,
                                                    orthogonal_coefficients,
                                                    normalization_factors_N,
                                                    radau_moments,
                                                    i );

  TEST_FLOATING_EQUALITY( ratios[i], normalization_ratios[i], 1e-12);

}

//---------------------------------------------------------------------------//
// Check that the mean coefficients for orthogonal polynomial recursion relation can be evaluated
TEUCHOS_UNIT_TEST( SloanRadauQuadrature,
		           evaluateMeanCoefficient )
{
  int i = 1;
  double result =
    quadrature->evaluateMeanCoefficient( normalization_ratios, 
                                         i );

  TEST_FLOATING_EQUALITY( result, mean_coefficients[i], 1e-12);

  i = 2;
  result =
    quadrature->evaluateMeanCoefficient( normalization_ratios, 
                                         i );

  TEST_FLOATING_EQUALITY( result, mean_coefficients[i], 1e-12);

}

//---------------------------------------------------------------------------//
// Check that the coefficients of the orthogonal polynomial can be evaluated
TEUCHOS_UNIT_TEST( SloanRadauQuadrature,
		           evaluateOrthogonalCoefficients )
{
  Teuchos::TwoDArray<double> coefficients( 3, 3 );

  coefficients[0][0] = 1.0;

  int i = 1;

  quadrature->evaluateOrthogonalCoefficients( coefficients, 
                                              variances[i-1],
                                              mean_coefficients[i],
                                              i );

  TEST_FLOATING_EQUALITY( coefficients[i][0], 
                          orthogonal_coefficients[i][0], 
                          1e-12);

  TEST_FLOATING_EQUALITY( coefficients[i][1], 
                          orthogonal_coefficients[i][1], 
                          1e-12);


  i = 2;
  quadrature->evaluateOrthogonalCoefficients( coefficients, 
                                              variances[i-1],
                                              mean_coefficients[i],
                                              i );

  TEST_FLOATING_EQUALITY( coefficients[i][0], 
                          orthogonal_coefficients[i][0], 
                          1e-12);

  TEST_FLOATING_EQUALITY( coefficients[i][1], 
                          orthogonal_coefficients[i][1], 
                          1e-12);

  TEST_FLOATING_EQUALITY( coefficients[i][2], 
                          orthogonal_coefficients[i][2], 
                          1e-12);

}

//---------------------------------------------------------------------------//
// Check that the normalization factors of the orthogonal polynomial can be evaluated
TEUCHOS_UNIT_TEST( SloanRadauQuadrature,
		           evaluateOrthogonalNormalizationFactor )
{
  Teuchos::Array<double> N( 3 );
  int i = 0;

  quadrature->evaluateOrthogonalNormalizationFactor( N,
                                                       orthogonal_coefficients, 
                                                       radau_moments,
                                                       i );

  TEST_FLOATING_EQUALITY( N[0], 
                          normalization_factors_N[i], 
                          1e-12);

  i = 1;
  quadrature->evaluateOrthogonalNormalizationFactor( N,
                                                     orthogonal_coefficients, 
                                                     radau_moments,
                                                     i );

  TEST_FLOATING_EQUALITY( N[1], 
                          normalization_factors_N[i], 
                          1e-12);
}

//---------------------------------------------------------------------------//
// Check that the Variance of the orthogonal polynomial can be evaluated
TEUCHOS_UNIT_TEST( SloanRadauQuadrature,
		           evaluateVariance )
{

  int i = 1;

  double result = 
    quadrature->evaluateVariance( normalization_factors_N,
                                  i );

  TEST_FLOATING_EQUALITY( result, 
                          variances[i], 
                          1e-12);
}

//---------------------------------------------------------------------------//
// Check that the Orthogonal Polynomial can be evaluated
TEUCHOS_UNIT_TEST( SloanRadauQuadrature,
		           evaluateOrthogonalPolynomial )
{
  double result =
    quadrature->evaluateOrthogonalPolynomial( variances, 
                                             mean_coefficients, 
                                             -1.0, 
                                             2 );

  TEST_FLOATING_EQUALITY( result, 1.30003428811616E+00, 1e-12);

  result =
    quadrature->evaluateOrthogonalPolynomial( variances, 
                                             mean_coefficients, 
                                             1.0, 
                                             2 );

  TEST_FLOATING_EQUALITY( result, 3.32904776851917E-02, 1e-12);

}

//---------------------------------------------------------------------------//
// Check that the roots of the Orthogonal Polynomial can be evaluated
TEUCHOS_UNIT_TEST( SloanRadauQuadrature,
		           evaluateOrthogonalRoots )
{
  Teuchos::TwoDArray<double> test_roots( 3, 2 );

  test_roots[1][0] = 9.0919706753240400E-01;

  int i = 2;
  double root_found =
    quadrature->evaluateOrthogonalRoots( test_roots, 
                                         variances,
                                         mean_coefficients, 
                                         i );

  TEST_EQUALITY_CONST( root_found, 1 ); 
  TEST_FLOATING_EQUALITY( test_roots[2][0], roots[2][0], 1e-12);
  TEST_FLOATING_EQUALITY( test_roots[2][1], roots[2][1], 1e-12);

}
*/
//---------------------------------------------------------------------------//
// Check that the roots of the Orthogonal Polynomial can be evaluated
TEUCHOS_UNIT_TEST( SloanRadauQuadrature,
		           getRadauNodesAndWeights )
{
  Teuchos::Array<long double> nodes, weights;
  Teuchos::Array<double> node( 5 ), weight( 5 );
  int number_of_angles_wanted = 3;

  quadrature->getRadauNodesAndWeights( nodes, weights, number_of_angles_wanted );

  for ( int i = 0; i < number_of_angles_wanted; i++ )
  {
    node[i] = nodes[i];
    weight[i] = weights[i];
  }

  TEST_FLOATING_EQUALITY( weight[0], weights_4[0], 1e-12);
  TEST_FLOATING_EQUALITY( weight[1], weights_4[1], 1e-12);
  TEST_FLOATING_EQUALITY( weight[2], weights_4[2], 1e-12);

  TEST_FLOATING_EQUALITY( node[0], roots[2][0], 1e-12);
  TEST_FLOATING_EQUALITY( node[1], roots[2][1], 1e-12);
  TEST_EQUALITY_CONST( node[2], 1.0 );


  number_of_angles_wanted = 5;
  quadrature_8->getRadauNodesAndWeights( nodes, weights, number_of_angles_wanted );

  for ( int i = 0; i < number_of_angles_wanted; i++ )
  {
    node[i] = nodes[i];
    weight[i] = weights[i];
  }

  TEST_FLOATING_EQUALITY( weight[0], weights_8[0], 1e-12);
  TEST_FLOATING_EQUALITY( weight[1], weights_8[1], 1e-12);
  TEST_FLOATING_EQUALITY( weight[2], weights_8[2], 1e-12);
  TEST_FLOATING_EQUALITY( weight[3], weights_8[3], 1e-12);
  TEST_FLOATING_EQUALITY( weight[4], weights_8[4], 1e-12);

  TEST_FLOATING_EQUALITY( node[0], roots_8[4][0], 1e-12);
  TEST_FLOATING_EQUALITY( node[1], roots_8[4][1], 1e-12);
  TEST_FLOATING_EQUALITY( node[2], roots_8[4][2], 1e-12);
  TEST_FLOATING_EQUALITY( node[3], roots_8[4][3], 1e-12);
  TEST_EQUALITY_CONST( node[4], 1.0 );

  number_of_angles_wanted = 7;
  test_quadrature->getRadauNodesAndWeights( nodes, weights, number_of_angles_wanted );

  double nodes_preserved = nodes.size();

  Teuchos::Array<double> legendre( test_legendre.size() ), test( test_legendre.size() );
  legendre[0] = 1.0;
  for ( int i = 0; i < nodes_preserved; i++ )
  {
    for ( int m = 1; m < test_legendre.size(); m++ )
    {
      legendre[m] +=
        Utility::getLegendrePolynomial( nodes[i], m )*weights[i];
    }
  }

  for ( int m = 0; m < test_legendre.size(); m++ )
  {
      test[m] = test_legendre[m];
  }

  TEST_FLOATING_EQUALITY( legendre[0], test[0], 1e-12);
  TEST_FLOATING_EQUALITY( legendre[1], test[1], 1e-12);
  TEST_FLOATING_EQUALITY( legendre[2], test[2], 1e-12);
  TEST_FLOATING_EQUALITY( legendre[3], test[3], 1e-12);
  TEST_FLOATING_EQUALITY( legendre[4], test[4], 1e-12);
  TEST_FLOATING_EQUALITY( legendre[5], test[5], 1e-12);
  TEST_FLOATING_EQUALITY( legendre[6], test[6], 1e-12);
  TEST_FLOATING_EQUALITY( legendre[7], test[7], 1e-12);
  TEST_FLOATING_EQUALITY( legendre[8], test[8], 1e-12);
  TEST_FLOATING_EQUALITY( legendre[9], test[9], 1e-12);
  TEST_FLOATING_EQUALITY( legendre[10], test[10], 1e-12);
  TEST_FLOATING_EQUALITY( legendre[11], test[11], 1e-12);
  TEST_FLOATING_EQUALITY( legendre[12], test[12], 1e-12);
  TEST_FLOATING_EQUALITY( legendre[13], test[13], 1e-12);
  TEST_FLOATING_EQUALITY( legendre[14], test[14], 1e-12);
  TEST_FLOATING_EQUALITY( legendre[15], test[15], 1e-12);
  TEST_FLOATING_EQUALITY( legendre[16], test[16], 1e-12);


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

  legendre_moments[0] =    2.597000000000000E+05/2.597000000000000E+05;
  legendre_moments[1] =    2.596999988559773E+05/2.597000000000000E+05;
  legendre_moments[2] =    2.596999967237519E+05/2.597000000000000E+05;
  legendre_moments[3] =    2.596999936552638E+05/2.597000000000000E+05;
  legendre_moments[4] =    2.596999896851397E+05/2.597000000000000E+05;

  radau_moments[0] = 4.4051713388171300E-09;
  radau_moments[1] = 4.0051688632303200E-09;
  radau_moments[2] = 4.0051707506094700E-09;
  radau_moments[3] = 3.8718360739764500E-09;

  roots[0][0] = 0.0;
  roots[1][0] = 9.0919706753240400E-01;
  roots[1][1] = 0.0;
  roots[2][0] = -3.418139372240581E-01;
  roots[2][1] = 9.751900698798918E-01;
  
  variances[0] = 0.0;  
  variances[1] = 8.2558188369131800E-02;
  variances[2] = 0.0;

  mean_coefficients[0] = 0.0;
  mean_coefficients[1] = 9.09197067532404E-01;
  mean_coefficients[2] = -2.75825162316919E-01;

  normalization_factors_N[0] = 4.4051713388171300E-09;  
  normalization_factors_N[1] = 3.6368296518836500E-10;
  normalization_factors_N[2] = 0.0;

  normalization_ratios[0] =  0.0;  
  normalization_ratios[1] =  9.0919706753240400E-01;
  normalization_ratios[2] =  6.3337190521548500E-01;

  orthogonal_coefficients[0][0] = 1.0;
  orthogonal_coefficients[1][0] = -9.09197067532404E-01;
  orthogonal_coefficients[1][1] = 1.0;
  orthogonal_coefficients[2][0] = -3.33337617099324E-01;
  orthogonal_coefficients[2][1] = -6.33371905215485E-01;
  orthogonal_coefficients[2][2] = 1.0;

  weights_4[2] = 9.999998311757786E-01;
  weights_4[1] = 1.686597168412245E-07;
  weights_4[0] = 1.645045065955549E-10;

  quadrature.reset(
    new Utility::SloanRadauQuadrature( legendre_moments ) );

  legendre_moments_8[0] = 2.597000000000000E+05;
  legendre_moments_8[1] = 2.596999988559773E+05;
  legendre_moments_8[2] = 2.596999967237519E+05;
  legendre_moments_8[3] = 2.596999936552638E+05;
  legendre_moments_8[4] = 2.596999896851397E+05;
  legendre_moments_8[5] = 2.596999848393495E+05;
  legendre_moments_8[6] = 2.596999791386693E+05;
  legendre_moments_8[7] = 2.596999726004124E+05;
  legendre_moments_8[8] = 2.596999652394188E+05;

  radau_moments_8[0] = 1.14402270000000E-03;
  radau_moments_8[1] = 1.04014270000000E-03;
  radau_moments_8[2] = 1.04014270000000E-03;
  radau_moments_8[3] = 1.0055160257142857142857E-03;
  radau_moments_8[4] = 1.00551604095238095238095E-03;
  radau_moments_8[5] = 9.847400229437229437229437E-04;
  radau_moments_8[6] = 9.8474004372294372294372E-04;
  radau_moments_8[7] = 9.699000221445221445221445E-04;
/*
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
  radau_moments_8[0] = 1.14402270000000E-03;
  radau_moments_8[1] = 1.04014270000000E-03;
  radau_moments_8[2] = 1.04014270000000E-03;
  radau_moments_8[3] = 1.00551618379541E-03;
  radau_moments_8[4] = 1.00551592186093E-03;
  radau_moments_8[5] = 9.84740123385564E-04;
  radau_moments_8[6] = 9.84739948762581E-04;
  radau_moments_8[7] = 9.69900109339505E-04;

  roots_8[4][0] = -8.234344561502381E-01;
  roots_8[4][1] = -1.838878312824176E-01;
  roots_8[4][2] = 5.698926378972536E-01;
  roots_8[4][3] = 9.932955818658158E-01;

  weights_8[4] = 9.999994142425495E-01;
  weights_8[3] = 5.849120168521541E-07;
  weights_8[2] = 7.085976107890621E-10;
  weights_8[1] = 1.104049253744378E-10;
  weights_8[0] = 2.643111130891782E-11;

  quadrature_8.reset(
    new Utility::SloanRadauQuadrature( legendre_moments_8 ) );

  // Create legendre moments from nodes and weights
  int num_roots = 8, num_moments = 17;

  test_roots[0] = 0.999;
  test_roots[1] = 0.998;
  test_roots[2] = 0.997;
  test_roots[3] = 0.996;
  test_roots[4] = 0.994;
  test_roots[5] = 0.992;
  test_roots[6] = 0.990;
  test_roots[7] = 0.900;

  test_weight = 1.0/num_roots;

  test_legendre[0] = 1.0;
  for ( int i = 0; i < num_roots; i++ )
  {
    for ( int m = 1; m < num_moments; m++ )
    {
      test_legendre[m] +=
        Utility::getLegendrePolynomial( test_roots[i], m )*test_weight;
    }    
  }

  test_quadrature.reset(
    new Utility::SloanRadauQuadrature( test_legendre ) );
   
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
// end tstSloanRadauquadrature->cpp
//---------------------------------------------------------------------------//
