//---------------------------------------------------------------------------//
//!
//! \file   tstAtomicExcitationAdjointElectronScatteringDistributionNative.cpp
//! \author Luke Kersting
//! \brief  Atomic Excitation adjoint electron scattering distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_AtomicExcitationAdjointElectronScatteringDistribution.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::AtomicExcitationAdjointElectronScatteringDistribution>
  native_ae_distribution;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the sample() function
FRENSIE_UNIT_TEST( AtomicExcitationAdjointElectronScatteringDistribution,
                   sample_native )
{
  MonteCarlo::AdjointElectronState electron( 0 );
  electron.setEnergy( 1.74999789912e1 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double outgoing_energy,scattering_angle_cosine;
  double final_energy = electron.getEnergy() + 2.10088e-5;

  // sample distribution
  native_ae_distribution->sample( electron.getEnergy(),
                                  outgoing_energy,
                                  scattering_angle_cosine );

  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, final_energy, 1e-12 );
  FRENSIE_CHECK_EQUAL( scattering_angle_cosine, 1.0 );

}

//---------------------------------------------------------------------------//
// Check that the sampleAndRecordTrials() function
FRENSIE_UNIT_TEST( AtomicExcitationAdjointElectronScatteringDistribution,
                   sampleAndRecordTrials_native )
{
  MonteCarlo::AdjointElectronState electron( 0 );
  electron.setEnergy( 1.74999789912e1 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double outgoing_energy,scattering_angle_cosine;
  double final_energy = electron.getEnergy() + 2.10088e-5;
  MonteCarlo::AdjointElectronScatteringDistribution::Counter trials = 10;

  // sample distribution
  native_ae_distribution->sampleAndRecordTrials( electron.getEnergy(),
                                                 outgoing_energy,
                                                 scattering_angle_cosine,
                                                 trials );

  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, final_energy, 1e-12 );
  FRENSIE_CHECK_EQUAL( scattering_angle_cosine, 1.0 );
  FRENSIE_CHECK_EQUAL( trials, 11 );
}

//---------------------------------------------------------------------------//
// Check that the scattering angle can be evaluated
FRENSIE_UNIT_TEST( AtomicExcitationAdjointElectronScatteringDistribution,
                   scatterAdjointElectron_native )
{
  MonteCarlo::ParticleBank bank;

  MonteCarlo::AdjointElectronState adjoint_electron( 0 );
  adjoint_electron.setEnergy( 1.74999789912e1 );
  adjoint_electron.setDirection( 0.0, 0.0, 1.0 );

  Data::SubshellType shell_of_interaction;
  double final_energy = adjoint_electron.getEnergy() + 2.10088e-5;

  // Scatter the adjoint electron
  native_ae_distribution->scatterAdjointElectron( adjoint_electron,
                                                  bank,
                                                  shell_of_interaction );

  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_electron.getEnergy(), final_energy, 1e-12 );
  FRENSIE_CHECK_EQUAL( adjoint_electron.getZDirection(), 1.0 );

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

  // Get the adjoint atomic excitation energy grid
  std::vector<double> energy_grid(
      data_container->getAdjointAtomicExcitationEnergyGrid() );

  // Get the adjoint atomic excitation energy gain
  std::vector<double> energy_gain(
      data_container->getAdjointAtomicExcitationEnergyGain() );

  // Create the energy gain distribution
  std::shared_ptr<Utility::UnivariateDistribution> energy_gain_function(
      new Utility::TabularDistribution<Utility::LinLin>( energy_grid,
                                                         energy_gain ) );

  // Create the distribution
  native_ae_distribution.reset(
      new MonteCarlo::AtomicExcitationAdjointElectronScatteringDistribution(
           energy_gain_function ) );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstAtomicExcitationAdjointElectronScatteringDistributionNative.cpp
//---------------------------------------------------------------------------//
