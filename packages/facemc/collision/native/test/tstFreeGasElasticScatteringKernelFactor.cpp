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
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<Facemc::FreeGasElasticScatteringKernelFactor> kernel_factor;

//---------------------------------------------------------------------------//
// Testing Functions
//---------------------------------------------------------------------------//
double analyticCrossSectionValue( const double A,
				  const double kT,
				  const double alpha,
				  const double beta,
				  const double E )
{
  double pi3 = Utility::PhysicalConstants::pi*
    Utility::PhysicalConstants::pi*
    Utility::PhysicalConstants::pi;

  return (kT*(A+1)*(A+1)/(16*sqrt(pi3)*A*E*sqrt(alpha)))*
	  exp( -(alpha + beta)*(alpha + beta)/(4*alpha) );
}

double integratedCrossSectionValue( const double A,
				    const double kT,
				    const double alpha,
				    const double beta,
				    const double E,
				    const double integral_value )
{
  double pi3 = Utility::PhysicalConstants::pi*
    Utility::PhysicalConstants::pi*
    Utility::PhysicalConstants::pi;

  return ((A+1)*(A+1)*(A+1)*(A+1)*sqrt(alpha)*kT/(16*sqrt(pi3)*A*E))*
    exp( -(A+1)/2*(beta - A*alpha) )*integral_value;
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( FreeGasElasticScatteringKernelFactor,
		   getIntegratedValue )
{
  // Calculate the integral value at energy 1e-6 MeV
  kernel_factor->setIndependentVariables( 39.5, 1.0, 1e-6 );

  double value, error;
  value = kernel_factor->getIntegratedValue( error );
 
  value = integratedCrossSectionValue( 0.999167,
				       2.53010e-8,
				       39.5,
				       1.0,
				       1.0e-06,
				       value );

  double analytic_value = analyticCrossSectionValue( 0.999167,
						     2.53010e-8,
						     39.5,
						     1.0,
						     1.0e-06 );

  // Test against analytic integral
  TEST_FLOATING_EQUALITY( value, analytic_value, 1e-9 );

  // Calculate the integral value at energy 1e-5 MeV
  kernel_factor->setIndependentVariables( 39.5, 1.0, 1e-5 );

  value = kernel_factor->getIntegratedValue( error );

  value = integratedCrossSectionValue( 0.999167,
				       2.53010e-8,
				       39.5,
				       1.0,
				       1.0e-05,
				       value );

  analytic_value = analyticCrossSectionValue( 0.999167,
					      2.53010e-8,
					      39.5,
					      1.0,
					      1.0e-05 );

  // Test against the analyticl integral
  TEST_FLOATING_EQUALITY( value, analytic_value, 1e-3 );

  // Calculate the integral value at energy 1e-4 MeV
  kernel_factor->setIndependentVariables( 39.5, 1.0, 1e-4 );

  value = kernel_factor->getIntegratedValue( error );

  value = integratedCrossSectionValue( 0.999167,
				       2.53010e-8,
				       39.5,
				       1.0,
				       1.0e-04,
				       value );

  analytic_value = analyticCrossSectionValue( 0.999167,
					      2.53010e-8,
					      39.5,
					      1.0,
					      1.0e-04 );

  // Test against the analyticl integral
  TEST_FLOATING_EQUALITY( value, analytic_value, 1e-4 );

  // Calculate the integral value at energy 1e-3 MeV
  kernel_factor->setIndependentVariables( 39.5, 1.0, 1e-3 );

  value = kernel_factor->getIntegratedValue( error );

  value = integratedCrossSectionValue( 0.999167,
				       2.53010e-8,
				       39.5,
				       1.0,
				       1.0e-03,
				       value );

  analytic_value = analyticCrossSectionValue( 0.999167,
					      2.53010e-8,
					      39.5,
					      1.0,
					      1.0e-03 );

  // Test against the analyticl integral
  TEST_FLOATING_EQUALITY( value, analytic_value, 1e-5 );

  // Calculate the integral value at energy 1e-2 MeV
  kernel_factor->setIndependentVariables( 39.5, 1.0, 1e-2 );

  value = kernel_factor->getIntegratedValue( error );

  value = integratedCrossSectionValue( 0.999167,
				       2.53010e-8,
				       39.5,
				       1.0,
				       1.0e-02,
				       value );

  analytic_value = analyticCrossSectionValue( 0.999167,
					      2.53010e-8,
					      39.5,
					      1.0,
					      1.0e-02 );

  // Test against the analyticl integral
  TEST_FLOATING_EQUALITY( value, analytic_value, 1e-6 );

  // Calculate the integral value at energy 0.1 MeV
  kernel_factor->setIndependentVariables( 39.5, 1.0, 1e-1 );

  value = kernel_factor->getIntegratedValue( error );

  value = integratedCrossSectionValue( 0.999167,
				       2.53010e-8,
				       39.5,
				       1.0,
				       1.0e-01,
				       value );

  analytic_value = analyticCrossSectionValue( 0.999167,
					      2.53010e-8,
					      39.5,
					      1.0,
					      1.0e-01 );

  // Test against the analyticl integral
  TEST_FLOATING_EQUALITY( value, analytic_value, 1e-7 );

  // Calculate the integral value at energy 1.0 MeV
  kernel_factor->setIndependentVariables( 39.5, 1.0, 1.0 );

  value = kernel_factor->getIntegratedValue( error );

  value = integratedCrossSectionValue( 0.999167,
				       2.53010e-8,
				       39.5,
				       1.0,
				       1.0,
				       value );

  analytic_value = analyticCrossSectionValue( 0.999167,
					      2.53010e-8,
					      39.5,
					      1.0,
					      1.0 );

  // Test against the analyticl integral
  TEST_FLOATING_EQUALITY( value, analytic_value, 1e-7 );

  // Calculate the integral value at energy 10.0 MeV
  kernel_factor->setIndependentVariables( 39.5, 1.0, 10.0 );

  value = kernel_factor->getIntegratedValue( error );

  value = integratedCrossSectionValue( 0.999167,
				       2.53010e-8,
				       39.5,
				       1.0,
				       10.0,
				       value );

  analytic_value = analyticCrossSectionValue( 0.999167,
					      2.53010e-8,
					      39.5,
					      1.0,
					      10.0 );

  // Test against the analyticl integral
  TEST_FLOATING_EQUALITY( value, analytic_value, 1e-6 );

  // Calculate the integral value at energy 19.99 MeV
  kernel_factor->setIndependentVariables( 39.5, 1.0, 19.99 );

  value = kernel_factor->getIntegratedValue( error );

  value = integratedCrossSectionValue( 0.999167,
				       2.53010e-8,
				       39.5,
				       1.0,
				       19.99,
				       value );

  analytic_value = analyticCrossSectionValue( 0.999167,
					      2.53010e-8,
					      39.5,
					      1.0,
					      19.99 );

  // Test against the analyticl integral
  TEST_FLOATING_EQUALITY( value, analytic_value, 1e-5 );
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
