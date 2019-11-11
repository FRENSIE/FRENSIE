//---------------------------------------------------------------------------//
//!
//! \file   tstBremsstrahlungElectronScatteringDistributionNative.cpp
//! \author Luke Kersting
//! \brief  Bremsstrahlung electron scattering distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <limits>

// FRENSIE Includes
#include "MonteCarlo_BremsstrahlungElectronScatteringDistribution.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::BremsstrahlungElectronScatteringDistribution>
  native_brem_dist;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated for a given incoming and knock-on energy
FRENSIE_UNIT_TEST( BremsstrahlungElectronScatteringDistribution, evaluate_native )
{
  double pdf = native_brem_dist->evaluate( 0.02, 1.0e-7 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 8.4075092621554539e+05, 1e-12 );

  pdf = native_brem_dist->evaluate( 9.0e-4, 9.0e-4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 6.6884672502034462e+01, 1e-12 );

  pdf = native_brem_dist->evaluate( 1.0e5, 2.0e4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.50132e-06, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated for a given incoming and knock-on energy
FRENSIE_UNIT_TEST( BremsstrahlungElectronScatteringDistribution,
                   evaluatePDF_native )
{
  double pdf = native_brem_dist->evaluatePDF( 0.02, 1.0e-7 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 8.4075092855101428e+05, 1e-12 );

  pdf = native_brem_dist->evaluatePDF( 9.0e-4, 9.0e-4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 6.6884671036581750e+01, 1e-12 );

  pdf = native_brem_dist->evaluatePDF( 1.0e5, 2.0e4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.5013204641704462e-06, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the CDF can be evaluated for a given incoming and knock-on energy
FRENSIE_UNIT_TEST( BremsstrahlungElectronScatteringDistribution,
                   evaluateCDF_native )
{
  double cdf = native_brem_dist->evaluateCDF( 0.02, 1.0e-7 );
  FRENSIE_CHECK_SMALL( cdf, 1e-12 );

  cdf = native_brem_dist->evaluateCDF( 9.0e-4, 9.0e-4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 1.0, 1e-12 );

  cdf = native_brem_dist->evaluateCDF( 1.0e5, 2.0e4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 9.5771054298946046e-01, 1e-12 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_native_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_native_file",
                                        test_native_file_name, "",
                                        "Test Native file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create the native data file container
  std::shared_ptr<Data::ElectronPhotonRelaxationDataContainer> data_container(
        new Data::ElectronPhotonRelaxationDataContainer(
              test_native_file_name ) );

  // Get the energy grid for bremsstrahlung energy distributions
  std::vector<double> energy_grid =
    data_container->getBremsstrahlungEnergyGrid();

  // Get the function data
  std::vector<double> primary_grid( energy_grid.size() );
  std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
    secondary_dists( energy_grid.size() );

  for( unsigned n = 0; n < energy_grid.size(); ++n )
  {
    primary_grid[n] = energy_grid[n];

    // Get the energy of the bremsstrahlung photon at the incoming energy
    std::vector<double> photon_energy(
          data_container->getBremsstrahlungPhotonEnergy( energy_grid[n] ) );

    // Get the bremsstrahlung photon pdf at the incoming energy
    std::vector<double> pdf(
          data_container->getBremsstrahlungPhotonPDF( energy_grid[n] ) );

    secondary_dists[n].reset(
        new const Utility::TabularDistribution<Utility::LinLin>( photon_energy,
                                                                 pdf ) );
  }

  double eval_tol = 1e-12;
  
  // Create the scattering function
  std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution> energy_loss_function(
       new Utility::InterpolatedFullyTabularBasicBivariateDistribution<Utility::UnitBaseCorrelated<Utility::LogLogLog> >(
                                                            primary_grid,
                                                            secondary_dists,
                                                            1e-6,
                                                            eval_tol ) );

  native_brem_dist.reset(
        new MonteCarlo::BremsstrahlungElectronScatteringDistribution(
              energy_loss_function ) );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstBremsstrahlungElectronScatteringDistributionNative.cpp
//---------------------------------------------------------------------------//
