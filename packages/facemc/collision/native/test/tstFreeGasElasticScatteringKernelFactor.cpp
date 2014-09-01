//---------------------------------------------------------------------------//
//!
//! \file   tstFreeGasElasticScatteringKernelFactor.cpp
//! \author Alex Robinson
//! \brief  Free gas elastic scattering kernel factor unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Facemc_FreeGasElasticScatteringKernelFactor.cpp"
#include "Utility_UniformDistribution.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<Facemc::FreeGasElasticScatteringKernelFactor> kernel_factor;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( FreeGasElasticScatteringKernelFactor,
		   getIntegratedValue )
{
  double value, error;
  value = kernel_factor->getIntegratedValue( error );
 
  // Test against analytic integral

  std::cout.precision( 10 );
  std::cout << value << " " << error << std::endl;
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
  Facemc::NeutronScatteringAngularDistribution::AngularDistribution
    distribution( 2 );

  distribution[0].first = 0.0;
  distribution[0].second = isotropic_distribution;
  
  distribution[1].first = 20.0;
  distribution[1].second = isotropic_distribution;

  Teuchos::RCP<Facemc::NeutronScatteringAngularDistribution> 
    scattering_distribution( new Facemc::NeutronScatteringAngularDistribution(
							      distribution ) );

  // Initialize the kernel factor
  kernel_factor.reset( new Facemc::FreeGasElasticScatteringKernelFactor(
						    cross_section, 
						    scattering_distribution,
						    0.999167,
						    2.53010e-8,
						    39.5,
						    1.0,
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
// end tstFreeGasElasticScatteringKernelFactor.cpp
//---------------------------------------------------------------------------//
