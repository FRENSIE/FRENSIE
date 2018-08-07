//---------------------------------------------------------------------------//
//!
//! \file   tstFreeGasElasticMarginalAlphaFunction.cpp
//! \author Alex Robinson
//! \brief  Free gas elastic marginal alpha function unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "DataGen_FreeGasElasticMarginalAlphaFunction.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<DataGen::FreeGasElasticMarginalAlphaFunction> alpha_function;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the alpha bounds can be returned
FRENSIE_UNIT_TEST( FreeGasElasticMarginalAlphaFunction, getAlphaMin_Max )
{
  alpha_function->setIndependentVariables( -9.9e-7/2.53010e-8, 1e-6 );

  FRENSIE_CHECK_FLOATING_EQUALITY( alpha_function->getAlphaMin(),
                          32.041235228594,
                          1e-12 );

  FRENSIE_CHECK_FLOATING_EQUALITY( alpha_function->getAlphaMax(),
                          47.864067440246,
                          1e-12 );

  alpha_function->setIndependentVariables( 0.0, 1e-6 );

  FRENSIE_CHECK_FLOATING_EQUALITY( alpha_function->getAlphaMin(),
                          0.0,
                          1e-12 );

  FRENSIE_CHECK_FLOATING_EQUALITY( alpha_function->getAlphaMax(),
                          158.22832211652,
                          1e-12 );

  alpha_function->setIndependentVariables( 1e-6/2.53010e-8, 1e-6 );

  FRENSIE_CHECK_FLOATING_EQUALITY( alpha_function->getAlphaMin(),
                          6.7869220430292,
                          1e-12 );

  FRENSIE_CHECK_FLOATING_EQUALITY( alpha_function->getAlphaMax(),
                          230.55556113174,
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
FRENSIE_UNIT_TEST( FreeGasElasticMarginalAlphaFunction, evaluatePDF )
{
  alpha_function->setIndependentVariables( -9.9e-7/2.53010e-8, 1e-6 );

  double pdf_value = (*alpha_function)( alpha_function->getAlphaMin() );

  FRENSIE_CHECK( pdf_value > 0.0 );

  pdf_value = (*alpha_function)( (alpha_function->getAlphaMin()+
                                  alpha_function->getAlphaMax())/2 );

  FRENSIE_CHECK( pdf_value > 0.0 );

  pdf_value = (*alpha_function)( alpha_function->getAlphaMax() );

  FRENSIE_CHECK( pdf_value > 0.0 );

  alpha_function->setIndependentVariables( 0.0, 1e-6 );

  pdf_value = (*alpha_function)( alpha_function->getAlphaMin() );

  // alpha = 0.0 is the only value that will result in a pdf value of inf
  FRENSIE_CHECK_EQUAL( pdf_value,
                       std::numeric_limits<double>::infinity() );

  pdf_value = (*alpha_function)( (alpha_function->getAlphaMin()+
                                  alpha_function->getAlphaMax())/2 );

  FRENSIE_CHECK( pdf_value > 0.0 );

  pdf_value = (*alpha_function)( alpha_function->getAlphaMax() );

  FRENSIE_CHECK( pdf_value > 0.0 );

  alpha_function->setIndependentVariables( 1e-6/2.53010e-8, 1e-6 );

  pdf_value = (*alpha_function)( alpha_function->getAlphaMin() );

  FRENSIE_CHECK( pdf_value > 0.0 );

  pdf_value = (*alpha_function)( (alpha_function->getAlphaMin()+
                                  alpha_function->getAlphaMax())/2 );

  FRENSIE_CHECK( pdf_value > 0.0 );

  pdf_value = (*alpha_function)( alpha_function->getAlphaMax() );

  FRENSIE_CHECK( pdf_value > 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the CDF can be evaluated
FRENSIE_UNIT_TEST( FreeGasElasticMarginalAlphaFunction, evaluateCDF )
{
  alpha_function->setIndependentVariables( -9.9e-7/2.53010e-8, 1e-6 );

  double cdf_value = alpha_function->evaluateCDF(
                                               alpha_function->getAlphaMin() );

  FRENSIE_CHECK_EQUAL( cdf_value, 0.0 );

  cdf_value = alpha_function->evaluateCDF( (alpha_function->getAlphaMin()+
                                            alpha_function->getAlphaMax())/2 );

  FRENSIE_CHECK( cdf_value > 0.0 );
  FRENSIE_CHECK( cdf_value < 1.0 );

  cdf_value = alpha_function->evaluateCDF( alpha_function->getAlphaMax()-1e-6);

  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 1.0, 1e-6 );

  cdf_value = alpha_function->evaluateCDF( alpha_function->getAlphaMax() );

  FRENSIE_CHECK_EQUAL( cdf_value, 1.0 );

  alpha_function->setIndependentVariables( 0.0, 1e-6 );

  cdf_value = alpha_function->evaluateCDF( alpha_function->getAlphaMin() );

  FRENSIE_CHECK_EQUAL( cdf_value, 0.0 );

  cdf_value = alpha_function->evaluateCDF( (alpha_function->getAlphaMin()+
                                            alpha_function->getAlphaMax())/2 );

  FRENSIE_CHECK( cdf_value > 0.0 );
  FRENSIE_CHECK( cdf_value < 1.0 );

  cdf_value = alpha_function->evaluateCDF( alpha_function->getAlphaMax()-1e-6);

  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 1.0, 1e-6 );

  cdf_value = alpha_function->evaluateCDF( alpha_function->getAlphaMax() );

  FRENSIE_CHECK_EQUAL( cdf_value, 1.0 );

  alpha_function->setIndependentVariables( 1e-6/2.53010e-8, 1e-6 );

  cdf_value = alpha_function->evaluateCDF( alpha_function->getAlphaMin() );

  FRENSIE_CHECK_EQUAL( cdf_value, 0.0 );

  cdf_value = alpha_function->evaluateCDF( (alpha_function->getAlphaMin()+
                                            alpha_function->getAlphaMax())/2 );

  FRENSIE_CHECK( cdf_value > 0.0 );
  FRENSIE_CHECK( cdf_value < 1.0 );

  cdf_value = alpha_function->evaluateCDF( alpha_function->getAlphaMax()-1e-6);

  FRENSIE_CHECK_FLOATING_EQUALITY( cdf_value, 1.0, 1e-6 );

  cdf_value = alpha_function->evaluateCDF( alpha_function->getAlphaMax() );

  FRENSIE_CHECK_EQUAL( cdf_value, 1.0 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Initialize the zero temperature cross section
  std::shared_ptr<Utility::UnivariateDistribution> cross_section(
                          new Utility::UniformDistribution( 0.0, 20.0, 1.0 ) );

  // Initialize the scattering probability distribution
  std::shared_ptr<Utility::TabularUnivariateDistribution> isotropic_distribution(
                          new Utility::UniformDistribution( -1.0, 1.0, 0.5 ) );

  // Initialize the scattering distribution
  MonteCarlo::NuclearScatteringAngularDistribution::AngularDistribution
    distribution( 2 );

  distribution[0].first = 0.0;
  distribution[0].second = isotropic_distribution;

  distribution[1].first = 20.0;
  distribution[1].second = isotropic_distribution;

  std::shared_ptr<MonteCarlo::NuclearScatteringAngularDistribution>
    scattering_distribution(
                         new MonteCarlo::NuclearScatteringAngularDistribution(
                                                              distribution ) );

  // Initialize the gkq_set factor
  alpha_function.reset( new DataGen::FreeGasElasticMarginalAlphaFunction(
                                                    cross_section,
                                                    scattering_distribution,
                                                    0.999167,
                                                    2.53010e-8,
                                                    0.0,
                                                    1.0e-06 ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstFreeGasElasticMarginalAlphaFunction.cpp
//---------------------------------------------------------------------------//
