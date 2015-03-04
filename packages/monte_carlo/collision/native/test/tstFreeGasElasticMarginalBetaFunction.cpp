//---------------------------------------------------------------------------//
//!
//! \file   tstFreeGasElasticMarginalBetaFunction.cpp
//! \author Alex Robinson
//! \brief  Free gas elastic marginal beta function unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_FreeGasElasticMarginalBetaFunction.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::FreeGasElasticMarginalBetaFunction> beta_function;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the beta min bound can be returned
TEUCHOS_UNIT_TEST( FreeGasElasticMarginalBetaFunction, getBetaMin )
{
  //beta_function->setIndependentVariables( 1e-6 );

  // TEST_FLOATING_EQUALITY( beta_function->getBetaMin(),
  // 			  -39.524129481048,
  // 			  1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( FreeGasElasticMarginalBetaFunction, evaluatePDF )
{
  //beta_function->setIndependentVariables( 1e-6 );
  std::cout << "norm: " << beta_function->getNormalizationConstant()
	    << std::endl;
  double pdf_value = (*beta_function)( beta_function->getBetaMin() );
  
  TEST_EQUALITY_CONST( pdf_value, 0.0 );
  
  pdf_value = (*beta_function)( 0.0 );
  //std::cout << pdf_value << std::endl;
  TEST_ASSERT( pdf_value > 0.0 );

  pdf_value = (*beta_function)( 401.30 );
  std::cout << pdf_value << std::endl;
  TEST_ASSERT( pdf_value > 0.0 );

  pdf_value = (*beta_function)( -beta_function->getBetaMin() );
  //std::cout << pdf_value << std::endl;
  TEST_ASSERT( pdf_value > 0.0 );

  // beta_function->setIndependentVariables( 1e-3 );

  // pdf_value = (*beta_function)( beta_function->getBetaMin() );
  // //std::cout << beta_function->getNormalizationConstant() << std::endl;
  // TEST_EQUALITY_CONST( pdf_value, 0.0 );
  
  // pdf_value = (*beta_function)( 0.0 );
  // //std::cout << pdf_value << std::endl;
  // TEST_ASSERT( pdf_value > 0.0 );

  // pdf_value = (*beta_function)( -beta_function->getBetaMin() );
  // //std::cout << pdf_value << std::endl;
  // TEST_ASSERT( pdf_value > 0.0 );
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
  MonteCarlo::ParticleScatteringAngularDistribution::AngularDistribution
    distribution( 2 );

  distribution[0].first = 0.0;
  distribution[0].second = isotropic_distribution;
  
  distribution[1].first = 20.0;
  distribution[1].second = isotropic_distribution;

  Teuchos::RCP<MonteCarlo::ParticleScatteringAngularDistribution> 
    scattering_distribution( 
			 new MonteCarlo::ParticleScatteringAngularDistribution(
							      distribution ) );

  // Initialize the kernel factor
  beta_function.reset( new MonteCarlo::FreeGasElasticMarginalBetaFunction(
						    cross_section, 
						    scattering_distribution,
						    0.999167,
						    2.53010e-8,
						    1.0e-03 ) );

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
// end tstFreeGasElasticMarginalBetaFunction.cpp
//---------------------------------------------------------------------------//
