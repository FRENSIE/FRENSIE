//---------------------------------------------------------------------------//
//!
//! \file   tstFreeGasElasticScatteringKernelFactor.cpp
//! \author Alex Robinson
//! \brief  Free gas elastic scattering gkq_set factor unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>
#include <math.h>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "DataGen_FreeGasElasticSAlphaBetaFunction.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_KinematicHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<DataGen::FreeGasElasticSAlphaBetaFunction> sab_function;
std::vector<double> plot_energies{2e-11};
int  beta_num = 100;
int alpha_num = 100;
double beta_spread = 1;
double tol = 1e-6;

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
  std::cout << " " << std::endl;

  for( int i = 0; i < plot_energies.size(); i++)
  {
    double beta_min = Utility::calculateBetaMin( plot_energies[i], 
        sab_function->getTemperature());

    double beta_max    = -beta_spread*beta_min;
    double beta_spread = (beta_max - beta_min)/(beta_num - 1.0);

    double beta_vals[beta_num];
    double alpha_vals[alpha_num];
    
    std::cout << "Energy     Beta     Alpha     sigma_c(E->E',mu)     sigma_a(E->E',mu)     E'     mu" << std::endl;

    for( int j = 0; j < beta_num; j++)
    {
        beta_vals[j] = beta_min + j*beta_spread;
    }
    
    for(int j = 0; j < beta_num; j++)
    {
        double beta_val = beta_vals[j];

            if ( beta_val > -1.0*tol && beta_val < 1.0*tol )
            {
              beta_val = tol;
            }

        double alpha_min = Utility::calculateAlphaMin(  plot_energies[i],
                                                        beta_val,
                                                        sab_function->getAtomicWeightRatio(),
                                                        sab_function->getTemperature() );

        double alpha_max = Utility::calculateAlphaMax(  plot_energies[i],
                                                        beta_val,
                                                        sab_function->getAtomicWeightRatio(),
                                                        sab_function->getTemperature() );

        double alpha_spread = (alpha_max - alpha_min)/(alpha_num - 1.0);

        for( int k = 0; k < alpha_num; k++)
        {
            alpha_vals[k] = alpha_min + k*alpha_spread;
        }
                                                
        for( int k = 0; k < alpha_num; k++)
        {
            double alpha_val = alpha_vals[k];

            double sab_value = (*sab_function)( alpha_val, beta_val, plot_energies[i] );
            
            double value = integratedCrossSectionValue( 0.999167,
                                        2.53010e-8,
                                        alpha_val,
                                        beta_val,
                                        plot_energies[i] ,
                                        sab_value );
            
            double analytic_value = analyticCrossSectionValue( 0.999167,
                                        2.53010e-8,
                                        alpha_val,
                                        beta_val,
                                        plot_energies[i]  );

            double E_out = plot_energies[i] + (2.53010e-8)*beta_val;
            
            // double mu    = (plot_energies[i] + E_out - 0.999167*(2.53010e-8)*alpha_val)/( 2.0*sqrt( plot_energies[i]*E_out ) );
            double mu = (2.0/99)*k - 1;

            std::cout << plot_energies[i]  << " " << beta_val << " " << alpha_val << " " << value << " " << analytic_value << " " << E_out << " " << mu << std::endl;
        }

    }
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

  // Initialize the S(alpha,beta) function
  sab_function.reset( new DataGen::FreeGasElasticSAlphaBetaFunction(
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
