//---------------------------------------------------------------------------//
//!
//! \file   tstBremsstrahlungAdjointElectronScatteringDistributionNativeFactory.cpp
//! \author Luke Kersting
//! \brief  bremsstrahlung scattering distribution native factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_BremsstrahlungAdjointElectronScatteringDistributionNativeFactory.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

typedef MonteCarlo::BremsstrahlungAdjointElectronScatteringDistributionNativeFactory
    BremFactory;

std::unique_ptr<Data::AdjointElectronPhotonRelaxationDataContainer> data_container;

std::shared_ptr<MonteCarlo::BremsstrahlungAdjointElectronScatteringDistribution>
  brem_distribution;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check the sample() function
FRENSIE_UNIT_TEST( BremsstrahlungAdjointElectronScatteringDistributionNativeFactory,
                   sample )
{
  // Set up the random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // Correlated sample the 1e-5 MeV and 1.1192e-5 MeV distributions
  fake_stream[1] = 0.5; // Sample an E_out of 1.552488576879764695e-05

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double outgoing_energy, scattering_angle, incoming_energy = 1.1e-5;

  brem_distribution->sample( incoming_energy, outgoing_energy, scattering_angle );

  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 1.552488576879764695e-05, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check the sampleAndRecordTrials() function
FRENSIE_UNIT_TEST( BremsstrahlungAdjointElectronScatteringDistributionNativeFactory,
                   sampleAndRecordTrials )
{
  // Set up the random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // Correlated sample the 1e-5 MeV and 1.1192e-5 MeV distributions
  fake_stream[1] = 0.5; // Sample an E_out of 1.552488576879764695e-05

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::AdjointElectronScatteringDistribution::Counter trials = 0.0;

  double outgoing_energy, scattering_angle, incoming_energy = 1.1e-5;

  brem_distribution->sampleAndRecordTrials( incoming_energy,
                                          outgoing_energy,
                                          scattering_angle,
                                          trials );

  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 1.552488576879764695e-05, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle, 1.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 1.0 );
}

//---------------------------------------------------------------------------//
// Check the scatterAdjointElectron() function
FRENSIE_UNIT_TEST( BremsstrahlungAdjointElectronScatteringDistributionNativeFactory,
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
  fake_stream[1] = 0.5; // Sample an E_out of 1.552488576879764695e-05

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  brem_distribution->scatterAdjointElectron( electron,
                                             bank,
                                             shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getEnergy(), 1.552488576879764695e-05, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getXDirection(), 0.0, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getYDirection(), 0.0, 1e-12 );
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
  data_container.reset( new Data::AdjointElectronPhotonRelaxationDataContainer(
                             test_native_file_name ) );

  // Get the energy grid
  std::vector<double> energy_grid;

  if ( data_container->separateAdjointBremsstrahlungEnergyGrid() )
    energy_grid = data_container->getAdjointElectronBremsstrahlungEnergyGrid();
  else
    energy_grid = data_container->getAdjointElectronEnergyGrid();

  BremFactory::createBremsstrahlungDistribution<Utility::LogLogLog,Utility::UnitBaseCorrelated>(
            *data_container,
            energy_grid,
            brem_distribution );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstBremsstrahlungAdjointElectronScatteringDistributionNativeFactory.cpp
//---------------------------------------------------------------------------//
