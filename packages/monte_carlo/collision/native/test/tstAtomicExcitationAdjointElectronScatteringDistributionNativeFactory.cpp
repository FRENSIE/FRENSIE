//---------------------------------------------------------------------------//
//!
//! \file   tstAtomicExcitationAdjointElectronScatteringDistributionNativeFactory.cpp
//! \author Luke Kersting
//! \brief  Atomic Excitation adjoint electron scattering distribution native factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_AtomicExcitationAdjointElectronScatteringDistributionNativeFactory.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

typedef MonteCarlo::AtomicExcitationAdjointElectronScatteringDistributionNativeFactory
            AtomicNativeFactory;

std::shared_ptr<const MonteCarlo::AtomicExcitationAdjointElectronScatteringDistribution>
  native_ae_distribution;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the sample() function
TEUCHOS_UNIT_TEST( AtomicExcitationAdjointElectronScatteringDistributionNativeFactory,
                   sample )
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
  TEST_FLOATING_EQUALITY( outgoing_energy, final_energy, 1e-12 );
  TEST_EQUALITY_CONST( scattering_angle_cosine, 1.0 );

}

//---------------------------------------------------------------------------//
// Check that the sampleAndRecordTrials() function
TEUCHOS_UNIT_TEST( AtomicExcitationAdjointElectronScatteringDistributionNativeFactory,
                   sampleAndRecordTrials )
{
  MonteCarlo::AdjointElectronState electron( 0 );
  electron.setEnergy( 1.74999789912e1 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double outgoing_energy,scattering_angle_cosine;
  double final_energy = electron.getEnergy() + 2.10088e-5;
  unsigned trials = 10;

  // sample distribution
  native_ae_distribution->sampleAndRecordTrials( electron.getEnergy(),
                                                 outgoing_energy,
                                                 scattering_angle_cosine,
                                                 trials );

  // Test
  TEST_FLOATING_EQUALITY( outgoing_energy, final_energy, 1e-12 );
  TEST_EQUALITY_CONST( scattering_angle_cosine, 1.0 );
  TEST_EQUALITY_CONST( trials, 11 );
}

//---------------------------------------------------------------------------//
// Check that the scattering angle can be evaluated
TEUCHOS_UNIT_TEST( AtomicExcitationAdjointElectronScatteringDistributionNativeFactory,
                   scatterAdjointElectron )
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
  TEST_FLOATING_EQUALITY( adjoint_electron.getEnergy(), final_energy, 1e-12 );
  TEST_EQUALITY_CONST( adjoint_electron.getZDirection(), 1.0 );

}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_native_file_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_native_file",
                   &test_native_file_name,
                   "Test Native file name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Create the native data file container
  std::shared_ptr<Data::AdjointElectronPhotonRelaxationDataContainer>
    data_container( new Data::AdjointElectronPhotonRelaxationDataContainer(
      test_native_file_name ) );

  // Create the distribution
  AtomicNativeFactory::createAtomicExcitationAdjointDistribution(
    *data_container,
    native_ae_distribution );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstAtomicExcitationAdjointElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
