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
#include "DataGen_FreeGasElasticMarginalBetaFunction.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<DataGen::FreeGasElasticMarginalBetaFunction> beta_function;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the beta min bound can be returned

/*
TEUCHOS_UNIT_TEST( FreeGasElasticMarginalBetaFunction, getBetaMin )
{
  beta_function->setIndependentVariables( 1e-7 );

  TEST_FLOATING_EQUALITY( beta_function->getBetaMin(),
  			 -3.95241294810482,
     		  1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( FreeGasElasticMarginalBetaFunction, evaluatePDF )
{
  
  beta_function->setIndependentVariables( 1e-7 );
  double pdf_value = (*beta_function)( beta_function->getBetaMin() );
  
  TEST_EQUALITY_CONST( pdf_value, 0.0 );
  
  pdf_value = (*beta_function)( 0.0 );
  TEST_ASSERT( pdf_value > 0.0 );

  pdf_value = (*beta_function)( -1*(beta_function->getBetaMin()) );
  TEST_ASSERT( pdf_value > 0.0 );

  beta_function->setIndependentVariables( 1e-5 );

  pdf_value = (*beta_function)( beta_function->getBetaMin() );
  TEST_EQUALITY_CONST( pdf_value, 0.0 );
  
  pdf_value = (*beta_function)( 0.0 );
  TEST_ASSERT( pdf_value > 0.0 );

  pdf_value = (*beta_function)( -1*(beta_function->getBetaMin()) );
  TEST_ASSERT( pdf_value > 0.0 );
}
*/ 

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( FreeGasElasticMarginalBetaFunction, outputPDF )
{
  beta_function->setIndependentVariables( 2.53010e-8 );
  std::vector<double> energy_vector{1e-11, 2e-11, 5e-11, 1e-10, 2e-10, 5e-10, 1e-9, 2e-9, 5e-9, 1e-8, 2e-8, 5e-8, 1e-7, 2e-7, 5e-7, 1e-6};
  Teuchos::Array<double> energy_array( energy_vector );

  beta_function->populatePDF( energy_array );

  Teuchos::Array<double> pdf_array;
  beta_function->getPDF( pdf_array );

  std::cout << " " << std::endl;

  for( int i = 0; i < pdf_array.size(); ++i )
  {
    std::cout << energy_array[i] << " " << pdf_array[i] << std::endl;
  }

}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( FreeGasElasticMarginalBetaFunction, outputCDF )
{
  beta_function->setIndependentVariables( 2.53010e-8 );
  std::vector<double> energy_vector{1e-11, 2e-11, 5e-11, 1e-10, 2e-10, 5e-10, 1e-9, 2e-9, 5e-9, 1e-8, 2e-8, 5e-8, 1e-7, 2e-7, 5e-7, 1e-6};
  Teuchos::Array<double> energy_array( energy_vector );

  beta_function->populateCDF( energy_array );

  Teuchos::Array<double> cdf_array;
  beta_function->getCDF( cdf_array );

  std::cout << " " << std::endl;

  for( int i = 0; i < cdf_array.size(); ++i )
  {
    std::cout << energy_array[i] << " " << cdf_array[i] << std::endl;
  }

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
  beta_function.reset( new DataGen::FreeGasElasticMarginalBetaFunction(
						    cross_section, 
						    scattering_distribution,
						    0.999167,
						    2.53010e-8,
						    1.0e-07 ) );

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
