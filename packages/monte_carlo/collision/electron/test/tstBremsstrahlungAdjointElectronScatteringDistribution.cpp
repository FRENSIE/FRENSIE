//---------------------------------------------------------------------------//
//!
//! \file   tstBremsstrahlungAdjointElectronScatteringScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  Bremsstrahlung electron scattering distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <limits>

// FRENSIE Includes
#include "MonteCarlo_BremsstrahlungAdjointElectronScatteringDistribution.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::BremsstrahlungAdjointElectronScatteringDistribution>
  adjoint_brem_dist;

double max_energy = 2.00100001000000027e+01;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the min incoming electron energy
FRENSIE_UNIT_TEST( BremsstrahlungAdjointElectronScatteringDistribution,
                   getMinEnergy )
{
  FRENSIE_CHECK_EQUAL( adjoint_brem_dist->getMinEnergy(), 1E-5 );
}

//---------------------------------------------------------------------------//
// Check that the max incoming electron energy
FRENSIE_UNIT_TEST( BremsstrahlungAdjointElectronScatteringDistribution,
                   getMaxEnergy )
{
  FRENSIE_CHECK_EQUAL( adjoint_brem_dist->getMaxEnergy(), 20.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated for a given incoming and knock-on energy
FRENSIE_UNIT_TEST( BremsstrahlungAdjointElectronScatteringDistribution,
                   evaluate )
{
  double pdf;

  // Check below lowest bin
  pdf = adjoint_brem_dist->evaluate( 1.0e-6, 2.0e-5 );
  FRENSIE_CHECK_SMALL( pdf, 1e-12 );

  // Check on lowest bin
  pdf = adjoint_brem_dist->evaluate( 1.0e-5, max_energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 2.17623452967737336e-10, 1e-12 );

  // Check between bins
  pdf = adjoint_brem_dist->evaluate( 1.1e-5, 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 2.571378268628855476e-06, 1e-12 );

  // Check on highest bin
  pdf = adjoint_brem_dist->evaluate( 20.0, max_energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 2.966315777350755911e-01, 1e-12 );

  // Check above highest bin
  pdf = adjoint_brem_dist->evaluate( 21.0, 22.0 );
  FRENSIE_CHECK_SMALL( pdf, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated for a given incoming and knock-on energy
FRENSIE_UNIT_TEST( BremsstrahlungAdjointElectronScatteringDistribution,
                   evaluatePDF )
{
  double pdf;

  // Check below lowest bin
  pdf = adjoint_brem_dist->evaluatePDF( 1.0e-6, 2.0e-5 );
  FRENSIE_CHECK_SMALL( pdf, 1e-12 );

  // Check on lowest bin
  pdf = adjoint_brem_dist->evaluatePDF( 1.0e-5, max_energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.208637156398267522e-10, 1e-12 );

  // Check between bins
  pdf = adjoint_brem_dist->evaluatePDF( 1.1e-5, 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.603435651317428790e-06, 1e-6 );

  // Check on highest bin
  pdf = adjoint_brem_dist->evaluatePDF( 20.0, max_energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.611274024020572793e-01, 1e-12 );

  // Check above highest bin
  pdf = adjoint_brem_dist->evaluatePDF( 21.0, 22.0 );
  FRENSIE_CHECK_SMALL( pdf, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the CDF can be evaluated for a given incoming and knock-on energy
FRENSIE_UNIT_TEST( BremsstrahlungAdjointElectronScatteringDistribution,
                   evaluateCDF )
{
  double cdf;

  // Check below lowest bin
  cdf = adjoint_brem_dist->evaluateCDF( 1.0e-6, 2.0e-5 );
  FRENSIE_CHECK_SMALL( cdf, 1e-12 );

  // Check on lowest bin
  cdf = adjoint_brem_dist->evaluateCDF( 1.0e-5, 10.1000050505 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 9.999999421083678453e-01, 1e-12 );

  // Check in between bins
  cdf = adjoint_brem_dist->evaluateCDF( 1.1e-5, 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 9.9999767762830605e-01, 1e-6 );

  // Check on highest bin
  cdf = adjoint_brem_dist->evaluateCDF( 20.0, max_energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 1.0, 1e-12 );

  // Check above highest bin
  cdf = adjoint_brem_dist->evaluateCDF( 21.0, 22.0 );
  FRENSIE_CHECK_SMALL( cdf, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a bremsstrahlung photon can be sampled using detailed 2BS
FRENSIE_UNIT_TEST( BremsstrahlungAdjointElectronScatteringDistribution,
                   sample )
{
  // Set up the random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // Correlated sample the 1e-5 MeV and 1.1192e-5 MeV distributions
  fake_stream[1] = 0.5; // Sample an E_out of 1.292134711932079911e-05

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double outgoing_energy, scattering_angle, incoming_energy = 1.1e-5;

  adjoint_brem_dist->sample( incoming_energy, outgoing_energy, scattering_angle );

  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 1.292134711932079911e-05, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
/* Check that a bremsstrahlung photon can be sampled and the trial number
 * recorded using detailed 2BS
 */
FRENSIE_UNIT_TEST( BremsstrahlungAdjointElectronScatteringDistribution,
                   sampleAndRecordTrials )
{
  // Set up the random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // Correlated sample the 1e-5 MeV and 1.1192e-5 MeV distributions
  fake_stream[1] = 0.5; // Sample an E_out of 1.292134711932079911e-05

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::AdjointElectronScatteringDistribution::Counter trials = 0;

  double outgoing_energy, scattering_angle, incoming_energy = 1.1e-5;

  adjoint_brem_dist->sampleAndRecordTrials( incoming_energy,
                                          outgoing_energy,
                                          scattering_angle,
                                          trials );

  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 1.292134711932079911e-05, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle, 1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that an electron can undergo adjoint bremsstrahlung scattering
FRENSIE_UNIT_TEST( BremsstrahlungAdjointElectronScatteringDistribution,
                   scatterAdjointElectron )
{
  MonteCarlo::ParticleBank bank;

  MonteCarlo::AdjointElectronState electron( 1 );
  electron.setEnergy( 1.1e-5 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  Data::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // Correlated sample the 1e-5 MeV and 1.1192e-5 MeV distributions
  fake_stream[1] = 0.5; // Sample an E_out of 1.292134711932079911e-05

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  adjoint_brem_dist->scatterAdjointElectron( electron,
                                             bank,
                                             shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getEnergy(), 1.292134711932079911e-05, 1e-12 );
  FRENSIE_CHECK_SMALL( electron.getXDirection(), 1e-12 );
  FRENSIE_CHECK_SMALL( electron.getYDirection(), 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getZDirection(), 1.0, 1e-12 );
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
  std::shared_ptr<Data::AdjointElectronPhotonRelaxationDataContainer>
    data_container( new Data::AdjointElectronPhotonRelaxationDataContainer(
        test_native_file_name ) );

  // Get the energy grid
  std::vector<double> energy_grid;

  if ( data_container->separateAdjointBremsstrahlungEnergyGrid() )
    energy_grid = data_container->getAdjointElectronBremsstrahlungEnergyGrid();
  else
    energy_grid = data_container->getAdjointElectronEnergyGrid();

  // Get the function data
  std::vector<double> primary_grid( energy_grid.size() );
  std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
    secondary_dists( energy_grid.size() );

  for( unsigned n = 0; n < energy_grid.size(); ++n )
  {
    primary_grid[n] = energy_grid[n];

    // Get the outgoing energy of the adjoint bremsstrahlung electron at the incoming energy
    std::vector<double> outgoing_energy(
      data_container->getAdjointElectronBremsstrahlungEnergy( energy_grid[n] ) );

    // Get the adjoint bremsstrahlung pdf at the incoming energy
    std::vector<double> pdf(
      data_container->getAdjointElectronBremsstrahlungPDF( energy_grid[n] ) );

    secondary_dists[n].reset(
      new const Utility::TabularDistribution<Utility::LinLin>( outgoing_energy,
                                                               pdf ) );
  }

  double evaluation_tol = 1e-7;

  // Create the energy gain function
  std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution> energy_gain_function(
     new Utility::InterpolatedFullyTabularBasicBivariateDistribution<Utility::UnitBaseCorrelated<Utility::LogLogLog> >(
                                                            primary_grid,
                                                            secondary_dists,
                                                            1e-6,
                                                            evaluation_tol ) );

  // Create the scattering distribution
  adjoint_brem_dist.reset(
    new MonteCarlo::BremsstrahlungAdjointElectronScatteringDistribution(
        energy_gain_function ) );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstBremsstrahlungAdjointElectronScatteringScatteringDistribution.cpp
//---------------------------------------------------------------------------//
