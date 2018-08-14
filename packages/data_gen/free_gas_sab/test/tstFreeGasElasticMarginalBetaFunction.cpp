//---------------------------------------------------------------------------//
//!
//! \file   tstFreeGasElasticMarginalBetaFunction.cpp
//! \author Alex Robinson
//! \brief  Free gas elastic marginal beta function unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "DataGen_FreeGasElasticMarginalBetaFunction.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<DataGen::FreeGasElasticMarginalBetaFunction> beta_function;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the beta min bound can be returned
FRENSIE_UNIT_TEST( FreeGasElasticMarginalBetaFunction, getBetaMin )
{
  //beta_function->setIndependentVariables( 1e-6 );

  // FRENSIE_CHECK_FLOATING_EQUALITY( beta_function->getBetaMin(),
  //                           -39.524129481048,
  //                           1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
FRENSIE_UNIT_TEST( FreeGasElasticMarginalBetaFunction, evaluatePDF )
{
  //beta_function->setIndependentVariables( 1e-6 );
  std::cout << "norm: " << beta_function->getNormalizationConstant()
            << std::endl;
  double pdf_value = (*beta_function)( beta_function->getBetaMin() );

  FRENSIE_CHECK_EQUAL( pdf_value, 0.0 );

  pdf_value = (*beta_function)( 0.0 );
  //std::cout << pdf_value << std::endl;
  FRENSIE_CHECK( pdf_value > 0.0 );

  pdf_value = (*beta_function)( 401.30 );
  std::cout << pdf_value << std::endl;
  FRENSIE_CHECK( pdf_value > 0.0 );

  pdf_value = (*beta_function)( -beta_function->getBetaMin() );
  //std::cout << pdf_value << std::endl;
  FRENSIE_CHECK( pdf_value > 0.0 );

  // beta_function->setIndependentVariables( 1e-3 );

  // pdf_value = (*beta_function)( beta_function->getBetaMin() );
  // //std::cout << beta_function->getNormalizationConstant() << std::endl;
  // FRENSIE_CHECK_EQUAL( pdf_value, 0.0 );

  // pdf_value = (*beta_function)( 0.0 );
  // //std::cout << pdf_value << std::endl;
  // FRENSIE_CHECK( pdf_value > 0.0 );

  // pdf_value = (*beta_function)( -beta_function->getBetaMin() );
  // //std::cout << pdf_value << std::endl;
  // FRENSIE_CHECK( pdf_value > 0.0 );
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
  std::shared_ptr<Utility::UnivariateDistribution> isotropic_distribution(
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
  beta_function.reset( new DataGen::FreeGasElasticMarginalBetaFunction(
                                                    cross_section,
                                                    scattering_distribution,
                                                    0.999167,
                                                    2.53010e-8,
                                                    1.0e-03 ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstFreeGasElasticMarginalBetaFunction.cpp
//---------------------------------------------------------------------------//
