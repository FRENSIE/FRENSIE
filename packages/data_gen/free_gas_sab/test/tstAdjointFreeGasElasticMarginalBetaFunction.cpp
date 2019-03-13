//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointFreeGasElasticMarginalBetaFunction.cpp
//! \author Eli
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
#include "DataGen_AdjointFreeGasElasticMarginalBetaFunction.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<DataGen::AdjointFreeGasElasticMarginalBetaFunction> beta_function;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the beta min bound can be returned
TEUCHOS_UNIT_TEST( AdjointFreeGasElasticMarginalBetaFunction, getBetaMin )
{
  beta_function->setIndependentVariables( 2.53010e-8 );

  TEST_FLOATING_EQUALITY( beta_function->getBetaMax(),
  			  1.00,
     		  1e-12 );

  TEST_FLOATING_EQUALITY( beta_function->getBetaMin(),
  			  -500*0.999167,
     		  1e-12 );           
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( AdjointFreeGasElasticMarginalBetaFunction, evaluatePDF )
{
  beta_function->setIndependentVariables( 2.53010e-8 );
  double pdf_value = (*beta_function)( beta_function->getBetaMin() );
  
  TEST_EQUALITY_CONST( pdf_value, 0.0 );
  
  pdf_value = (*beta_function)( 0.0 );
  TEST_ASSERT( pdf_value > 0.0 );

  pdf_value = (*beta_function)( 0.3 );
  TEST_ASSERT( pdf_value > 0.0 );

  pdf_value = (*beta_function)( beta_function->getBetaMax() );
  TEST_EQUALITY_CONST( pdf_value, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( AdjointFreeGasElasticMarginalBetaFunction, outputPDF )
{
  beta_function->setIndependentVariables( 2.53010e-8 );

  double beta_max = beta_function->getBetaMax();
  double beta_min = -10*beta_max;

  double beta_space = (beta_max - beta_min)/(1000);
  std::cout << " " << std::endl;
  std::cout << " " << std::endl;

  for (int i = 0; i < 1001; ++i)
  {
    const double beta_value = beta_min + i*beta_space;
    double pdf_value = (*beta_function)( beta_value );

    std::cout << beta_value << " " << pdf_value << std::endl;
  }

  std::cout << " " << std::endl;
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
  Teuchos::RCP<Utility::TabularOneDDistribution> isotropic_distribution(
			  new Utility::UniformDistribution( -1.0, 1.0, 0.5 ) );

  // Initialize the scattering distribution
  MonteCarlo::NuclearScatteringAngularDistribution::AngularDistribution
    distribution( 2 );

  distribution[0].first = 0.0;
  distribution[0].second = isotropic_distribution;
  
  distribution[1].first = 20.0;
  distribution[1].second = isotropic_distribution;

  Teuchos::RCP<MonteCarlo::NuclearScatteringAngularDistribution> 
    scattering_distribution( 
			 new MonteCarlo::NuclearScatteringAngularDistribution(
							      distribution ) );

  // Initialize the gkq_set factor
  beta_function.reset( new DataGen::AdjointFreeGasElasticMarginalBetaFunction(
						    cross_section, 
						    scattering_distribution,
						    0.999167,
						    2.53010e-8,
						    2.53010e-8 ) );

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
