//---------------------------------------------------------------------------//
//!
//! \file   tstFreeGasElasticMarginalAlphaFunction.cpp
//! \author Alex Robinson
//! \brief  Free gas elastic marginal alpha function unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_FreeGasElasticMarginalAlphaFunction.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::FreeGasElasticMarginalAlphaFunction> alpha_function;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the alpha bounds can be returned
TEUCHOS_UNIT_TEST( FreeGasElasticMarginalAlphaFunction, getAlphaMin_Max )
{
  alpha_function->setIndependentVariables( -9.9e-7/2.53010e-8, 1e-6 );

  TEST_FLOATING_EQUALITY( alpha_function->getAlphaMin(),
			  32.041235228594,
			  1e-12 );

  TEST_FLOATING_EQUALITY( alpha_function->getAlphaMax(),
			  47.864067440246,
			  1e-12 );
  
  alpha_function->setIndependentVariables( 0.0, 1e-6 );

  TEST_FLOATING_EQUALITY( alpha_function->getAlphaMin(),
			  0.0,
			  1e-12 );

  TEST_FLOATING_EQUALITY( alpha_function->getAlphaMax(),
			  158.22832211652,
			  1e-12 );

  alpha_function->setIndependentVariables( 1e-6/2.53010e-8, 1e-6 );

  TEST_FLOATING_EQUALITY( alpha_function->getAlphaMin(),
			  6.7869220430292,
			  1e-12 );

  TEST_FLOATING_EQUALITY( alpha_function->getAlphaMax(),
			  230.55556113174,
			  1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( FreeGasElasticMarginalAlphaFunction, evaulatePDF )
{
  alpha_function->setIndependentVariables( -9.9e-7/2.53010e-8, 1e-6 );

  double pdf_value = (*alpha_function)( alpha_function->getAlphaMin() );
  
  TEST_ASSERT( pdf_value > 0.0 );
  
  pdf_value = (*alpha_function)( (alpha_function->getAlphaMin()+
				  alpha_function->getAlphaMax())/2 );
  
  TEST_ASSERT( pdf_value > 0.0 );

  pdf_value = (*alpha_function)( alpha_function->getAlphaMax() );
  
  TEST_ASSERT( pdf_value > 0.0 );
  
  alpha_function->setIndependentVariables( 0.0, 1e-6 );

  pdf_value = (*alpha_function)( alpha_function->getAlphaMin() );
  
  // alpha = 0.0 is the only value that will result in a pdf value of 0.0
  TEST_EQUALITY_CONST( pdf_value, 0.0 );
  
  pdf_value = (*alpha_function)( (alpha_function->getAlphaMin()+
				  alpha_function->getAlphaMax())/2 );
  
  TEST_ASSERT( pdf_value > 0.0 );

  pdf_value = (*alpha_function)( alpha_function->getAlphaMax() );
  
  TEST_ASSERT( pdf_value > 0.0 );

  alpha_function->setIndependentVariables( 1e-6/2.53010e-8, 1e-6 );

  pdf_value = (*alpha_function)( alpha_function->getAlphaMin() );
  
  TEST_ASSERT( pdf_value > 0.0 );
  
  pdf_value = (*alpha_function)( (alpha_function->getAlphaMin()+
				  alpha_function->getAlphaMax())/2 );
  
  TEST_ASSERT( pdf_value > 0.0 );

  pdf_value = (*alpha_function)( alpha_function->getAlphaMax() );
  
  TEST_ASSERT( pdf_value > 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the CDF can be evaluated
TEUCHOS_UNIT_TEST( FreeGasElasticMarginalAlphaFunction, evaluateCDF )
{
  alpha_function->setIndependentVariables( -9.9e-7/2.53010e-8, 1e-6 );

  double cdf_value = alpha_function->evaluateCDF( 
					       alpha_function->getAlphaMin() );
  
  TEST_EQUALITY_CONST( cdf_value, 0.0 );
 
  cdf_value = alpha_function->evaluateCDF( (alpha_function->getAlphaMin()+
					    alpha_function->getAlphaMax())/2 );
  
  TEST_ASSERT( cdf_value > 0.0 );
  TEST_ASSERT( cdf_value < 1.0 );

  cdf_value = alpha_function->evaluateCDF( alpha_function->getAlphaMax()-1e-6);

  TEST_FLOATING_EQUALITY( cdf_value, 1.0, 1e-6 );

  cdf_value = alpha_function->evaluateCDF( alpha_function->getAlphaMax() );
  
  TEST_EQUALITY_CONST( cdf_value, 1.0 );

  alpha_function->setIndependentVariables( 0.0, 1e-6 );

  cdf_value = alpha_function->evaluateCDF( alpha_function->getAlphaMin() );
  
  TEST_EQUALITY_CONST( cdf_value, 0.0 );
 
  cdf_value = alpha_function->evaluateCDF( (alpha_function->getAlphaMin()+
					    alpha_function->getAlphaMax())/2 );
  
  TEST_ASSERT( cdf_value > 0.0 );
  TEST_ASSERT( cdf_value < 1.0 );

  cdf_value = alpha_function->evaluateCDF( alpha_function->getAlphaMax()-1e-6);

  TEST_FLOATING_EQUALITY( cdf_value, 1.0, 1e-6 );

  cdf_value = alpha_function->evaluateCDF( alpha_function->getAlphaMax() );
  
  TEST_EQUALITY_CONST( cdf_value, 1.0 );

  alpha_function->setIndependentVariables( 1e-6/2.53010e-8, 1e-6 );

  cdf_value = alpha_function->evaluateCDF( alpha_function->getAlphaMin() );
  
  TEST_EQUALITY_CONST( cdf_value, 0.0 );
 
  cdf_value = alpha_function->evaluateCDF( (alpha_function->getAlphaMin()+
					    alpha_function->getAlphaMax())/2 );
  
  TEST_ASSERT( cdf_value > 0.0 );
  TEST_ASSERT( cdf_value < 1.0 );

  cdf_value = alpha_function->evaluateCDF( alpha_function->getAlphaMax()-1e-6);

  TEST_FLOATING_EQUALITY( cdf_value, 1.0, 1e-6 );

  cdf_value = alpha_function->evaluateCDF( alpha_function->getAlphaMax() );
  
  TEST_EQUALITY_CONST( cdf_value, 1.0 );
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

  // Initialize the zero temperature cross section
  Teuchos::RCP<Utility::OneDDistribution> cross_section(
			  new Utility::UniformDistribution( 0.0, 20.0, 1.0 ) );

  // Initialize the scattering probability distribution
  Teuchos::RCP<Utility::OneDDistribution> isotropic_distribution(
			  new Utility::UniformDistribution( -1.0, 1.0, 0.5 ) );

  // Initialize the scattering distribution
  MonteCarlo::NeutronScatteringAngularDistribution::AngularDistribution
    distribution( 2 );

  distribution[0].first = 0.0;
  distribution[0].second = isotropic_distribution;
  
  distribution[1].first = 20.0;
  distribution[1].second = isotropic_distribution;

  Teuchos::RCP<MonteCarlo::NeutronScatteringAngularDistribution> 
    scattering_distribution( new MonteCarlo::NeutronScatteringAngularDistribution(
							      distribution ) );

  // Initialize the kernel factor
  alpha_function.reset( new MonteCarlo::FreeGasElasticMarginalAlphaFunction(
						    cross_section, 
						    scattering_distribution,
						    0.999167,
						    2.53010e-8,
						    0.0,
						    1.0e-06 ) );

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
// end tstFreeGasElasticMarginalAlphaFunction.cpp
//---------------------------------------------------------------------------//
