//---------------------------------------------------------------------------//
//!
//! \file   fges_sab_gen.cpp
//! \author Alex Robinson
//! \brief  Free gas elastic scattering S(alpha,beta) table generator
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/bind.hpp>

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_CommandLineProcessor.hpp>
#include <Teuchos_FancyOStream.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Utility_BilinearGridGenerator.hpp"
#include "Utility_OneDDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "MonteCarlo_KinematicHelpers.hpp"
#include "MonteCarlo_NuclearScatteringAngularDistribution.hpp"
#include "DataGen_FreeGasElasticSAlphaBetaFunction.hpp"

int main( int argc, char** argv )
{
  Teuchos::RCP<Teuchos::FancyOStream> out =
    Teuchos::VerboseObjectBase::getDefaultOStream();

  double energy = 2.5e-8; // MeV
  double atomic_weight_ratio = 0.999167;
  double temperature = 2.5301e-8; // MeV
  double convergence_tol = 0.0001;

  // Set up the command line options
  Teuchos::CommandLineProcessor sab_clp;

  sab_clp.setDocString( "Free gas elastic scattering S(alpha,beta,E) table "
			"generator\n" );
  sab_clp.setOption( "energy",
		     &energy,
		     "Energy at which table will be generated (MeV)",
		     true );
  sab_clp.setOption( "atomic_weight_ratio",
		     &atomic_weight_ratio,
		     "Atomic weight ratio of scatterer",
		     true );
  sab_clp.setOption( "temperature",
		     &temperature,
		     "Temperature at which the table will be generated (MeV)",
		     true );
  sab_clp.setOption( "convergence_tol",
		     &convergence_tol,
		     "Tolerance used to refine grid points" );

  sab_clp.throwExceptions( false );

  // Parse the command line
  Teuchos::CommandLineProcessor::EParseCommandLineReturn
    parse_return = sab_clp.parse( argc, argv );

  if( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL )
  {
    sab_clp.printHelpMessage( argv[0], *out );

    return parse_return;
  }

  // Create the S(alpha,beta,E) function
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

  Teuchos::RCP<MonteCarlo::NuclearScatteringAngularDistribution>
    scattering_distribution(
			 new MonteCarlo::NuclearScatteringAngularDistribution(
							      distribution ) );

  // Create the S(alpha,beta,E) function object
  DataGen::FreeGasElasticSAlphaBetaFunction sab_function(
						       cross_section,
						       scattering_distribution,
						       atomic_weight_ratio,
						       temperature );

  // Create the function wrappers
  boost::function<double (double beta, double alpha)> sab_function_wrapper =
    boost::bind<double>( boost::ref(sab_function), _2, _1, energy );

  boost::function<double (double beta)> alpha_min_wrapper =
    boost::bind<double>( MonteCarlo::calculateAlphaMin,
			 energy,
			 _1,
			 atomic_weight_ratio,
			 temperature );

  boost::function<double (double beta)> alpha_max_wrapper =
    boost::bind<double>( MonteCarlo::calculateAlphaMax,
			 energy,
			 _1,
			 atomic_weight_ratio,
			 temperature );

  // Create the bilinear grid generator
  Utility::BilinearGridGenerator sab_grid_generator( sab_function_wrapper,
						     alpha_min_wrapper,
						     alpha_max_wrapper );

  double beta_min = MonteCarlo::calculateBetaMin( energy, temperature );

  Teuchos::Array<double> initial_beta_grid( 2 );
  initial_beta_grid[0] = beta_min;
  initial_beta_grid[1] = -beta_min;

  Teuchos::Array<double> linear_beta_grid;
  Teuchos::Array<Teuchos::Array<double> > linear_alpha_grids;

  // Generate the alpha and beta grids
  *out << "Generating alpha and beta grids...";
  out->flush();

  sab_grid_generator.generate( linear_beta_grid,
			       linear_alpha_grids,
			       initial_beta_grid,
			       convergence_tol,
			       1e-21,
			       1e-10 );

  *out << "done!" << std::endl << std::endl;

  out->precision( 20 );

  // Print out the beta grid
  *out << "Beta Grid: ";

  for( unsigned i = 0; i < linear_beta_grid.size(); ++i )
    *out << linear_beta_grid[i] << " ";
  *out << std::endl;

  // Print out the alpha grids and the S(alpha,beta,E) function values
  for( unsigned i = 0; i < linear_beta_grid.size(); ++i )
  {
    *out << "Alpha Grid For Beta Index: " << i << std::endl;
    for( unsigned j = 0; j < linear_alpha_grids[i].size(); ++j )
      *out << linear_alpha_grids[i][j] << " ";
    *out << std::endl;

    for( unsigned j = 0; j < linear_alpha_grids[i].size(); ++j )
    {
      *out << sab_function( linear_alpha_grids[i][j],
			    linear_beta_grid[i],
			    energy )
	   << " ";
    }
    *out << std::endl;
  }
}

//---------------------------------------------------------------------------//
// end fges_sab_gen.cpp
//---------------------------------------------------------------------------//
