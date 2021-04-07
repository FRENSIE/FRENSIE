//---------------------------------------------------------------------------//
//!
//! \file   tstAtomicExcitationAdjointElectronScatteringDistributionNativeFactory.cpp
//! \author Luke Kersting
//! \brief  Atomic Excitation adjoint electron scattering distribution native factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_AtomicExcitationAdjointElectronScatteringDistributionNativeFactory.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

typedef MonteCarlo::AtomicExcitationAdjointElectronScatteringDistributionNativeFactory
            AtomicNativeFactory;

std::shared_ptr<MonteCarlo::AtomicExcitationAdjointElectronScatteringDistribution>
  native_ae_distribution;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the sample() function
FRENSIE_UNIT_TEST( AtomicExcitationAdjointElectronScatteringDistributionNativeFactory,
                   sample )
{
  MonteCarlo::AdjointElectronState electron( 0 );
  electron.setEnergy( 1.99999789891999988e+01 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double outgoing_energy,scattering_angle_cosine;

  // sample distribution
  native_ae_distribution->sample( electron.getEnergy(),
                                  outgoing_energy,
                                  scattering_angle_cosine );

  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 20.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( scattering_angle_cosine, 1.0 );

}

//---------------------------------------------------------------------------//
// Check that the sampleAndRecordTrials() function
FRENSIE_UNIT_TEST( AtomicExcitationAdjointElectronScatteringDistributionNativeFactory,
                   sampleAndRecordTrials )
{
  MonteCarlo::AdjointElectronState electron( 0 );
  electron.setEnergy( 1.99999789891999988e+01 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double outgoing_energy,scattering_angle_cosine;
  MonteCarlo::AdjointElectronScatteringDistribution::Counter trials = 10;

  // sample distribution
  native_ae_distribution->sampleAndRecordTrials( electron.getEnergy(),
                                                 outgoing_energy,
                                                 scattering_angle_cosine,
                                                 trials );

  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 20.0, 1e-12 );
  FRENSIE_CHECK_EQUAL( scattering_angle_cosine, 1.0 );
  FRENSIE_CHECK_EQUAL( trials, 11 );
}

//---------------------------------------------------------------------------//
// Check that the scattering angle can be evaluated
FRENSIE_UNIT_TEST( AtomicExcitationAdjointElectronScatteringDistributionNativeFactory,
                   scatterAdjointElectron )
{
  MonteCarlo::ParticleBank bank;

  MonteCarlo::AdjointElectronState adjoint_electron( 0 );
  adjoint_electron.setEnergy( 1.99999789891999988e+01 );
  adjoint_electron.setDirection( 0.0, 0.0, 1.0 );

  Data::SubshellType shell_of_interaction;

  // Scatter the adjoint electron
  native_ae_distribution->scatterAdjointElectron( adjoint_electron,
                                                  bank,
                                                  shell_of_interaction );

  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_electron.getEnergy(), 20.0, 1e-12 );
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

  // Create the distribution
  AtomicNativeFactory::createAtomicExcitationDistribution(
    *data_container,
    native_ae_distribution );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstAtomicExcitationAdjointElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
