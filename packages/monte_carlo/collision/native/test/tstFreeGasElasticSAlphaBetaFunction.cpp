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
#include "MonteCarlo_FreeGasElasticSAlphaBetaFunction.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_KinematicHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::FreeGasElasticSAlphaBetaFunction> sab_function;

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

  if( alpha > 0.0 || beta > 0.0 )
  {
    return (kT*(A+1)*(A+1)/(16*sqrt(pi3)*A*E*sqrt(alpha)))*
      exp( -(alpha + beta)*(alpha + beta)/(4*alpha) );
  }
  else
    return std::numeric_limits<double>::infinity();
}

double integratedCrossSectionValue( const double A,
				    const double kT,
				    const double alpha,
				    const double beta,
				    const double E,
				    const double sab_value )
{
  double pi3 = Utility::PhysicalConstants::pi*
    Utility::PhysicalConstants::pi*
    Utility::PhysicalConstants::pi;

  if( sab_value < std::numeric_limits<double>::infinity() )
    return ((A+1)*(A+1)*(A+1)*(A+1)*kT/(16*sqrt(pi3)*A*E))*sab_value;
  else
    return std::numeric_limits<double>::infinity();
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the integrated value can be returned
TEUCHOS_UNIT_TEST( FreeGasElasticSAlphaBetaFunction,
		   getIntegratedValue_energy_range )
{
  // Calculate the integral value at energy 1e-6 MeV
  double sab_value = (*sab_function)( 39.5, 1.0, 1e-6 );

  double value = integratedCrossSectionValue( 0.999167,
					      2.53010e-8,
					      39.5,
					      1.0,
					      1.0e-06,
					      sab_value );

  double analytic_value = analyticCrossSectionValue( 0.999167,
						     2.53010e-8,
						     39.5,
						     1.0,
						     1.0e-06 );

  // Test against analytic integral
  TEST_FLOATING_EQUALITY( value, analytic_value, 1e-9 );

  // Calculate the integral value at energy 1e-5 MeV
  sab_value = (*sab_function)( 39.5, 1.0, 1e-5 );

  value = integratedCrossSectionValue( 0.999167,
				       2.53010e-8,
				       39.5,
				       1.0,
				       1.0e-05,
				       sab_value );

  analytic_value = analyticCrossSectionValue( 0.999167,
					      2.53010e-8,
					      39.5,
					      1.0,
					      1.0e-05 );

  // Test against the analytic integral
  TEST_FLOATING_EQUALITY( value, analytic_value, 1e-3 );

  // Calculate the integral value at energy 1e-4 MeV
  sab_value = (*sab_function)( 39.5, 1.0, 1e-4 );

  value = integratedCrossSectionValue( 0.999167,
				       2.53010e-8,
				       39.5,
				       1.0,
				       1.0e-04,
				       sab_value );

  analytic_value = analyticCrossSectionValue( 0.999167,
					      2.53010e-8,
					      39.5,
					      1.0,
					      1.0e-04 );

  // Test against the analytic integral
  TEST_FLOATING_EQUALITY( value, analytic_value, 1e-4 );

  // Calculate the integral value at energy 1e-3 MeV
  sab_value = (*sab_function)( 39.5, 1.0, 1e-3 );

  value = integratedCrossSectionValue( 0.999167,
				       2.53010e-8,
				       39.5,
				       1.0,
				       1.0e-03,
				       sab_value );

  analytic_value = analyticCrossSectionValue( 0.999167,
					      2.53010e-8,
					      39.5,
					      1.0,
					      1.0e-03 );

  // Test against the analytic integral
  TEST_FLOATING_EQUALITY( value, analytic_value, 1e-5 );

  // Calculate the integral value at energy 1e-2 MeV
  sab_value = (*sab_function)( 39.5, 1.0, 1e-2 );

  value = integratedCrossSectionValue( 0.999167,
				       2.53010e-8,
				       39.5,
				       1.0,
				       1.0e-02,
				       sab_value );

  analytic_value = analyticCrossSectionValue( 0.999167,
					      2.53010e-8,
					      39.5,
					      1.0,
					      1.0e-02 );

  // Test against the analytic integral
  TEST_FLOATING_EQUALITY( value, analytic_value, 1e-6 );

  // Calculate the integral value at energy 0.1 MeV
  sab_value = (*sab_function)( 39.5, 1.0, 1e-1 );

  value = integratedCrossSectionValue( 0.999167,
				       2.53010e-8,
				       39.5,
				       1.0,
				       1.0e-01,
				       sab_value );

  analytic_value = analyticCrossSectionValue( 0.999167,
					      2.53010e-8,
					      39.5,
					      1.0,
					      1.0e-01 );

  // Test against the analytic integral
  TEST_FLOATING_EQUALITY( value, analytic_value, 1e-7 );

  // Calculate the integral value at energy 1.0 MeV
  sab_value = (*sab_function)( 39.5, 1.0, 1.0 );

  value = integratedCrossSectionValue( 0.999167,
				       2.53010e-8,
				       39.5,
				       1.0,
				       1.0,
				       sab_value );

  analytic_value = analyticCrossSectionValue( 0.999167,
					      2.53010e-8,
					      39.5,
					      1.0,
					      1.0 );

  // Test against the analytic integral
  TEST_FLOATING_EQUALITY( value, analytic_value, 1e-7 );

  // Calculate the integral value at energy 10.0 MeV
  sab_value = (*sab_function)( 39.5, 1.0, 10.0 );

  value = integratedCrossSectionValue( 0.999167,
				       2.53010e-8,
				       39.5,
				       1.0,
				       10.0,
				       sab_value );

  analytic_value = analyticCrossSectionValue( 0.999167,
					      2.53010e-8,
					      39.5,
					      1.0,
					      10.0 );

  // Test against the analytic integral
  TEST_FLOATING_EQUALITY( value, analytic_value, 1e-5 );

  // Calculate the integral value at energy 19.99 MeV
  sab_value = (*sab_function)( 39.5, 1.0, 19.99 );

  value = integratedCrossSectionValue( 0.999167,
				       2.53010e-8,
				       39.5,
				       1.0,
				       19.99,
				       sab_value );

  analytic_value = analyticCrossSectionValue( 0.999167,
					      2.53010e-8,
					      39.5,
					      1.0,
					      19.99 );

  // Test against the analytic integral
  TEST_FLOATING_EQUALITY( value, analytic_value, 1e-5 );
}

//---------------------------------------------------------------------------//
// Check that the integrated value can be returned
TEUCHOS_UNIT_TEST( FreeGasElasticScatteringKernelFactor,
		   getIntegratedValue_alpha_beta_range )
{
  // Calculate the integral value at energy 1e-6 MeV
  double beta_min = Utility::calculateBetaMin( 1e-6, 
					       sab_function->getTemperature());
  double alpha_min = Utility::calculateAlphaMin( 
					  1e-6,
					  beta_min,
					  sab_function->getAtomicWeightRatio(),
					  sab_function->getTemperature() );
  
  double alpha_max = Utility::calculateAlphaMax( 
					  1e-6,
					  beta_min,
					  sab_function->getAtomicWeightRatio(),
					  sab_function->getTemperature() );
  
  double sab_value = (*sab_function)( alpha_min, beta_min, 1e-6 );
  std::cout << sab_value << std::endl;
  
  double value = integratedCrossSectionValue( 0.999167,
					      2.53010e-8,
					      alpha_min,
					      beta_min,
					      1.0e-06,
					      sab_value );
  
  double analytic_value = analyticCrossSectionValue( 0.999167,
						     2.53010e-8,
						     alpha_min,
						     beta_min,
						     1.0e-06 );

  // Test against analytic integral
  TEST_FLOATING_EQUALITY( value, analytic_value, 1e-9 );

  // Calculate the integral value at energy 1e-6 MeV
  sab_value = (*sab_function)( alpha_max, beta_min, 1e-6 );
  std::cout << sab_value << std::endl;
  
  value = integratedCrossSectionValue( 0.999167,
				       2.53010e-8,
				       alpha_max,
				       beta_min,
				       1.0e-06,
				       sab_value );
  
  analytic_value = analyticCrossSectionValue( 0.999167,
					      2.53010e-8,
					      alpha_max,
					      beta_min,
					      1.0e-06 );

  // Test against analytic integral
  TEST_FLOATING_EQUALITY( value, analytic_value, 1e-9 );

  // Calculate the integral value at energy 1e-6 MeV
  alpha_min = Utility::calculateAlphaMin( 1e-6,
					  -15.0,
					  sab_function->getAtomicWeightRatio(),
					  sab_function->getTemperature() );
  
  alpha_max = Utility::calculateAlphaMax( 1e-6,
					  -15.0,
					  sab_function->getAtomicWeightRatio(),
					  sab_function->getTemperature() );

  sab_value = (*sab_function)( alpha_min, -15.0, 1e-6 );
  std::cout << sab_value << std::endl;
  
  value = integratedCrossSectionValue( 0.999167,
				       2.53010e-8,
				       alpha_min,
				       -15.0,
				       1.0e-06,
				       sab_value );
  
  analytic_value = analyticCrossSectionValue( 0.999167,
					      2.53010e-8,
					      alpha_min,
					      -15.0,
					      1.0e-06 );

  // Test against analytic integral
  TEST_FLOATING_EQUALITY( value, analytic_value, 1e-9 );

  // Calculate the integral value at energy 1e-6 MeV
  sab_value = (*sab_function)( alpha_max, -15.0, 1e-6 );
  std::cout << sab_value << std::endl;
  
  value = integratedCrossSectionValue( 0.999167,
				       2.53010e-8,
				       alpha_max,
				       -15.0,
				       1.0e-06,
				       sab_value );
  
  analytic_value = analyticCrossSectionValue( 0.999167,
					      2.53010e-8,
					      alpha_max,
					      -15.0,
					      1.0e-06 );

  // Calculate the integral value at energy 1e-6 MeV
  sab_value = (*sab_function)( 15.0, -15.0, 1e-6 );
  std::cout << sab_value << std::endl;
  
  value = integratedCrossSectionValue( 0.999167,
				       2.53010e-8,
				       15.0,
				       -15.0,
				       1.0e-06,
				       sab_value );
  
  analytic_value = analyticCrossSectionValue( 0.999167,
					      2.53010e-8,
					      15.0,
					      -15.0,
					      1.0e-06 );

  // Test against analytic integral
  TEST_FLOATING_EQUALITY( value, analytic_value, 1e-9 );

  // Calculate the integral value at energy 1e-6 MeV
  sab_value = (*sab_function)( 1e-9, 0.0, 1e-6 );
  std::cout << sab_value << std::endl;
  
  value = integratedCrossSectionValue( 0.999167,
				       2.53010e-8,
				       1e-9,
				       0.0,
				       1.0e-06,
				       sab_value );
  
  analytic_value = analyticCrossSectionValue( 0.999167,
					      2.53010e-8,
					      1e-9,
					      0.0,
					      1.0e-06 );

  // Test against analytic integral
  TEST_FLOATING_EQUALITY( value, analytic_value, 1e-7 );

  // Calculate the integral value at energy 1e-6 MeV
  sab_value = (*sab_function)( 1e-12, 0.0, 1e-6 );
  std::cout << sab_value << std::endl;
  
  value = integratedCrossSectionValue( 0.999167,
				       2.53010e-8,
				       1e-12,
				       0.0,
				       1.0e-06,
				       sab_value );
  
  analytic_value = analyticCrossSectionValue( 0.999167,
					      2.53010e-8,
					      1e-12,
					      0.0,
					      1.0e-06 );

  // Test against analytic integral
  TEST_FLOATING_EQUALITY( value, analytic_value, 1e-7 );

  // Calculate the integral value at energy 1e-6 MeV
  sab_value = (*sab_function)( 0.0, 0.0, 1e-6 );
  std::cout << sab_value << std::endl;
  
  value = integratedCrossSectionValue( 0.999167,
				       2.53010e-8,
				       0.0,
				       0.0,
				       1.0e-06,
				       sab_value );
  
  analytic_value = analyticCrossSectionValue( 0.999167,
					      2.53010e-8,
					      0.0,
					      0.0,
					      1.0e-06 );

  // Test against analytic integral
  TEST_EQUALITY_CONST( value, analytic_value );

  // Calculate the integral value at energy 1e-6 MeV
  sab_value = (*sab_function)( 450, 700, 1e-6 );
  std::cout << sab_value << std::endl;
  
  value = integratedCrossSectionValue( 0.999167,
				       2.53010e-8,
				       450,
				       700,
				       1.0e-06,
				       sab_value );
  
  analytic_value = analyticCrossSectionValue( 0.999167,
					      2.53010e-8,
					      450,
					      700,
					      1.0e-06 );

  // Test against analytic integral
  TEST_FLOATING_EQUALITY( value, analytic_value, 1e-9 );

  // Calculate the integral value at energy 1e-6 MeV
  sab_value = (*sab_function)( 1000, 700, 1e-6 );

  std::cout << value << std::endl;
  value = integratedCrossSectionValue( 0.999167,
				       2.53010e-8,
				       1000,
				       700,
				       1.0e-06,
				       sab_value );
  
  analytic_value = analyticCrossSectionValue( 0.999167,
					      2.53010e-8,
					      1000,
					      700,
					      1.0e-06 );

  // Test against analytic integral
  TEST_FLOATING_EQUALITY( value, analytic_value, 1e-9 );
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

  // Initialize the S(alpha,beta) function
  sab_function.reset( new MonteCarlo::FreeGasElasticSAlphaBetaFunction(
						    cross_section, 
						    scattering_distribution,
						    0.999167,
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
// end tstFreeGasElasticScatteringKernelFactor.cpp
//---------------------------------------------------------------------------//
