//---------------------------------------------------------------------------//
//!
//! \file   tstElectroionizationSubshellAdjointElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  adjoint electroionization subshell scattering distribution Native factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_ElectroionizationSubshellAdjointElectronScatteringDistribution.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<Data::AdjointElectronPhotonRelaxationDataContainer> data_container;

std::shared_ptr<const MonteCarlo::ElectroionizationSubshellAdjointElectronScatteringDistribution>
  native_distribution, linlinlog_native_distribution;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the subshell binding energy
FRENSIE_UNIT_TEST( ElectroionizationSubshellAdjointElectronScatteringDistribution,
                   getBindingEnergy )
{
  double binding_energy = native_distribution->getBindingEnergy();
  FRENSIE_CHECK_EQUAL( binding_energy, 1.361E-05 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated for a given incoming and knock-on energy
FRENSIE_UNIT_TEST( ElectroionizationSubshellAdjointElectronScatteringDistribution,
                   evaluate )
{
  double pdf;

  // Check below the first bin
  pdf = native_distribution->evaluate( 9.99e-6, 2.3711E-5 );
  FRENSIE_CHECK_SMALL( pdf, 1e-12 );

  // Check the first bin
  pdf = native_distribution->evaluate( 1e-5, 2.3711E-5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 2.8832537324008945e+02, 1e-12 );

  // Check between two bins
  pdf = native_distribution->evaluate( 1.1e-5, 0.2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 8.3791683509363488e-02, 1e-6 );

  // Check the last bin
  pdf = native_distribution->evaluate( 20.0, 20.00002722 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 2.2513643748184764e+04, 1e-12 );

  // Check above the last bin
  pdf = native_distribution->evaluate( 20.01, 22.1 );
  FRENSIE_CHECK_SMALL( pdf, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated for a given incoming and knock-on energy
FRENSIE_UNIT_TEST( ElectroionizationSubshellAdjointElectronScatteringDistribution,
                   evaluatePDF )
{
  double pdf;

  // Check below the first bin
  pdf = native_distribution->evaluatePDF( 9.99e-6, 2.3711E-5 );
  FRENSIE_CHECK_SMALL( pdf, 1e-12 );

  // Check the first bin
  pdf = native_distribution->evaluatePDF( 1e-5, 2.3711E-5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 2.8680303543353426e+02, 1e-12 );

  // Check between two bins
  pdf = native_distribution->evaluatePDF( 1.1e-5, 0.2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 8.3342708113886652e-02, 1e-6 );

  // Check the last bin
  pdf = native_distribution->evaluatePDF( 20.0, 20.00002722 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.8947470957884732e+04, 1e-12 );

  // Check above the last bin
  pdf = native_distribution->evaluatePDF( 20.01, 22.1 );
  FRENSIE_CHECK_SMALL( pdf, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated for a given incoming and knock-on energy
FRENSIE_UNIT_TEST( ElectroionizationSubshellAdjointElectronScatteringDistribution,
                   evaluateCDF )
{
  double cdf;

  // Check below the first bin
  cdf = native_distribution->evaluateCDF( 9.99e-6, 1.361e-5 );
  FRENSIE_CHECK_SMALL( cdf, 1e-12 );

  // Check the first bin
  cdf = native_distribution->evaluateCDF( 1e-5, 0.2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 6.1534014457547345e-02, 1e-12 );

  // Check between two bins
  cdf = native_distribution->evaluateCDF( 1.1e-5, 0.2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 6.2286304045260414e-02, 1e-6 );

  // Check the last bin
  cdf = native_distribution->evaluateCDF( 20.0, 20.00002722 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cdf, 1.0, 1e-12 );

  // Check above the last bin
  cdf = native_distribution->evaluateCDF( 20.01, 22.1 );
  FRENSIE_CHECK_SMALL( cdf, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
FRENSIE_UNIT_TEST( ElectroionizationSubshellAdjointElectronScatteringDistribution,
                   sample )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.1;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double scattering_angle_cosine, outgoing_energy, incoming_energy = 1e-5;

  // sample the electron
  native_distribution->sample( incoming_energy,
                               outgoing_energy,
                               scattering_angle_cosine );

  // Test scattered electron
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 4.6479758057486557e-03, 1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 8.4608569226157793e-01, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
FRENSIE_UNIT_TEST( ElectroionizationSubshellAdjointElectronScatteringDistribution,
                   sampleAndRecordTrials )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.1;

  MonteCarlo::AdjointElectronScatteringDistribution::Counter trials = 0;
  double incoming_energy = 1e-5;
  double outgoing_energy, scattering_angle_cosine;

  // sample the electron
  native_distribution->sampleAndRecordTrials( incoming_energy,
                                              outgoing_energy,
                                              scattering_angle_cosine,
                                              trials );

  // Test trials
  FRENSIE_CHECK_EQUAL( trials, 1.0 );

  // Test scattered electron
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 4.6479758057486557e-03, 1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 8.4608569226157793e-01, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
FRENSIE_UNIT_TEST( ElectroionizationSubshellAdjointElectronScatteringDistribution,
                   scatterAdjointElectron )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.1;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType shell_of_interaction;

  MonteCarlo::AdjointElectronState electron( 0 );
  electron.setEnergy( 1e-5 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter electron
  native_distribution->scatterAdjointElectron( electron,
                                               bank,
                                               shell_of_interaction );

  // Test original electron
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getZDirection(), 4.6479758057486557e-03, 1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getEnergy(), 8.4608569226157793e-01, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
FRENSIE_UNIT_TEST( ElectroionizationSubshellAdjointElectronScatteringDistribution,
                   sample_LinLinLog )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.0;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double scattering_angle_cosine, outgoing_energy, incoming_energy = 1e-3;

  // sample the electron
  linlinlog_native_distribution->sample( incoming_energy,
                                         outgoing_energy,
                                         scattering_angle_cosine );

  // Test scattered electron
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9179984831038948e-01, 1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 1.0166207761683570e-03, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
FRENSIE_UNIT_TEST( ElectroionizationSubshellAdjointElectronScatteringDistribution,
                   sampleAndRecordTrials_LinLinLog )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.0;

  MonteCarlo::AdjointElectronScatteringDistribution::Counter trials = 0.0;
  double incoming_energy = 1e-3;
  double outgoing_energy, scattering_angle_cosine;

  // sample the electron
  linlinlog_native_distribution->sampleAndRecordTrials( incoming_energy,
                                                        outgoing_energy,
                                                        scattering_angle_cosine,
                                                        trials );

  // Test trials
  FRENSIE_CHECK_EQUAL( trials, 1.0 );

  // Test scattered electron
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.9179984831038948e-01, 1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 1.0166207761683570e-03, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
FRENSIE_UNIT_TEST( ElectroionizationSubshellAdjointElectronScatteringDistribution,
                   scatterAdjointElectron_LinLinLog )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.0;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType shell_of_interaction;

  MonteCarlo::AdjointElectronState electron( 0 );
  electron.setEnergy( 1e-3 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  // Analytically scatter electron
  linlinlog_native_distribution->scatterAdjointElectron( electron,
                                                         bank,
                                                         shell_of_interaction );

  // Test original electron
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getZDirection(), 9.9179984831038948e-01, 1e-10 );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getEnergy(), 1.0166207761683570e-03, 1e-12 );
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
  data_container.reset( new Data::AdjointElectronPhotonRelaxationDataContainer(
                             test_native_file_name ) );

  // Set binding energy
  double binding_energy = 1.361E-05;

  std::vector<double> energy_grid =
    data_container->getAdjointElectronEnergyGrid();

  // Create the scattering function
  std::vector<double> primary_grid( energy_grid.size() );
  std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
    secondary_dists( energy_grid.size() );

  std::set<unsigned> subshells = data_container->getSubshells();

  for( unsigned n = 0; n < energy_grid.size(); ++n )
  {
    primary_grid[n] = energy_grid[n];

    // Get the recoil energy distribution at the incoming energy
    std::vector<double> recoil_energy(
      data_container->getAdjointElectroionizationRecoilEnergy(
        *subshells.begin(),
        energy_grid[n] ) );

    // Get the recoil energy pdf at the incoming energy
    std::vector<double> pdf(
      data_container->getAdjointElectroionizationRecoilPDF(
        *subshells.begin(),
        energy_grid[n] ) );
    
    secondary_dists[n].reset(
      new const Utility::TabularDistribution<Utility::LinLin>( recoil_energy,
                                                               pdf ) );
  }

  double evaluation_tol = 1e-10;

  { // Create the LinLinLog scattering function
  std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution> subshell_distribution(
     new Utility::InterpolatedFullyTabularBasicBivariateDistribution<Utility::UnitBaseCorrelated<Utility::LinLinLog> >(
                                                            primary_grid,
                                                            secondary_dists,
                                                            1e-6,
                                                            evaluation_tol ) );

  linlinlog_native_distribution.reset(
     new MonteCarlo::ElectroionizationSubshellAdjointElectronScatteringDistribution(
            subshell_distribution,
            binding_energy ) );

  }

  { // Create the LogLogLog scattering function
  std::shared_ptr<Utility::FullyTabularBasicBivariateDistribution> subshell_distribution(
     new Utility::InterpolatedFullyTabularBasicBivariateDistribution<Utility::UnitBaseCorrelated<Utility::LogLogLog> >(
                                                            primary_grid,
                                                            secondary_dists,
                                                            1e-6,
                                                            evaluation_tol ) );

  native_distribution.reset(
     new MonteCarlo::ElectroionizationSubshellAdjointElectronScatteringDistribution(
            subshell_distribution,
            binding_energy ) );

  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstElectroionizationSubshellAdjointElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
