//---------------------------------------------------------------------------//
//!
//! \file   tstAtomicExcitationAdjointElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  Atomic Excitation adjoint electron scattering distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_AtomicExcitationAdjointElectronScatteringDistribution.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::AtomicExcitationAdjointElectronScatteringDistribution>
  ace_ae_distribution;

std::shared_ptr<MonteCarlo::AtomicExcitationAdjointElectronScatteringDistribution>
  native_ae_distribution;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the sample() function
TEUCHOS_UNIT_TEST( AtomicExcitationAdjointElectronScatteringDistribution,
                   sample_ace )
{
  MonteCarlo::AdjointElectronState electron( 0 );
  electron.setEnergy( 1e-3 - 9.32298E-6 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double outgoing_energy, scattering_angle_cosine;

  // sample distribution
  ace_ae_distribution->sample( electron.getEnergy(),
                               outgoing_energy,
                               scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( outgoing_energy, 1e-3, 1e-12 );
  TEST_EQUALITY_CONST( scattering_angle_cosine, 1.0 );

}

//---------------------------------------------------------------------------//
// Check that the sample() function
TEUCHOS_UNIT_TEST( AtomicExcitationAdjointElectronScatteringDistribution,
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
  TEST_FLOATING_EQUALITY( outgoing_energy, final_energy, 1e-12 );
  TEST_EQUALITY_CONST( scattering_angle_cosine, 1.0 );

}

//---------------------------------------------------------------------------//
// Check that the sampleAndRecordTrials() function
TEUCHOS_UNIT_TEST( AtomicExcitationAdjointElectronScatteringDistribution,
                   sampleAndRecordTrials_ace )
{
  MonteCarlo::AdjointElectronState electron( 0 );
  electron.setEnergy( 1e-3 - 9.322980E-6 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double outgoing_energy,scattering_angle_cosine;
  unsigned trials = 10;

  // sample distribution
  ace_ae_distribution->sampleAndRecordTrials( electron.getEnergy(),
                                              outgoing_energy,
                                              scattering_angle_cosine,
                                              trials );

  // Test
  TEST_FLOATING_EQUALITY( outgoing_energy, 1e-3, 1e-12 );
  TEST_EQUALITY_CONST( scattering_angle_cosine, 1.0 );
  TEST_EQUALITY_CONST( trials, 11 );
}

//---------------------------------------------------------------------------//
// Check that the sampleAndRecordTrials() function
TEUCHOS_UNIT_TEST( AtomicExcitationAdjointElectronScatteringDistribution,
                   sampleAndRecordTrials_native )
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
TEUCHOS_UNIT_TEST( AtomicExcitationAdjointElectronScatteringDistribution,
                   scatterAdjointElectron_ace )
{
  MonteCarlo::ParticleBank bank;

  MonteCarlo::AdjointElectronState adjoint_electron( 0 );
  adjoint_electron.setEnergy( 1e-3 - 9.32298E-6 );
  adjoint_electron.setDirection( 0.0, 0.0, 1.0 );

  Data::SubshellType shell_of_interaction;

  // Scatter the adjoint electron
  ace_ae_distribution->scatterAdjointElectron( adjoint_electron,
                                               bank,
                                               shell_of_interaction );

  // Test
  TEST_FLOATING_EQUALITY( adjoint_electron.getEnergy(), 1e-3, 1e-12 );
  TEST_EQUALITY_CONST( adjoint_electron.getZDirection(), 1.0 );

}

//---------------------------------------------------------------------------//
// Check that the scattering angle can be evaluated
TEUCHOS_UNIT_TEST( AtomicExcitationAdjointElectronScatteringDistribution,
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
  TEST_FLOATING_EQUALITY( adjoint_electron.getEnergy(), final_energy, 1e-12 );
  TEST_EQUALITY_CONST( adjoint_electron.getZDirection(), 1.0 );

}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_ace_file_name, test_ace_table_name, test_native_file_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_ace_file",
                   &test_ace_file_name,
                   "Test ACE file name" );
  clp().setOption( "test_ace_table",
                   &test_ace_table_name,
                   "Test ACE table name" );
  clp().setOption( "test_native_file",
                   &test_native_file_name,
                   "Test Native file name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Create the ACE distribution
  {
    // Create a file handler and data extractor
    Teuchos::RCP<Data::ACEFileHandler> ace_file_handler(
      new Data::ACEFileHandler( test_ace_file_name,
                                test_ace_table_name,
                                1u ) );
    Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor(
        new Data::XSSEPRDataExtractor(
            ace_file_handler->getTableNXSArray(),
            ace_file_handler->getTableJXSArray(),
            ace_file_handler->getTableXSSArray() ) );

    // Extract the atomic excitation information data block (EXCIT)
    Teuchos::ArrayView<const double> excit_block(
            xss_data_extractor->extractEXCITBlock() );

    // Extract the number of tabulated energies
    int size = excit_block.size()/2;

    // Extract the energy grid for atomic excitation energy loss
    Teuchos::Array<double> energy_grid(excit_block(0,size));

    // Extract the energy loss for atomic excitation
    Teuchos::Array<double> energy_loss(excit_block(size,size));

    // Evaluate the adjoint energy grid for atomic excitation energy gain
    Teuchos::Array<double> adjoint_energy_grid( size );

    // Loop through the energy grid
    for ( unsigned n = 0; n < size; ++n )
    {
      adjoint_energy_grid[n] = energy_grid[n] - energy_loss[n];
    }

    // Create the energy gain distributions
    std::shared_ptr<Utility::OneDDistribution> energy_gain_function(
      new Utility::TabularDistribution<Utility::LinLin>( adjoint_energy_grid,
                                                         energy_loss ) );

    // Create the distribution
    ace_ae_distribution.reset(
      new MonteCarlo::AtomicExcitationAdjointElectronScatteringDistribution(
           energy_gain_function ) );

    // Clear setup data
    ace_file_handler.reset();
    xss_data_extractor.reset();
  }

  // Create the Native distribution
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
    std::shared_ptr<Utility::OneDDistribution> energy_gain_function(
      new Utility::TabularDistribution<Utility::LinLin>( energy_grid,
                                                         energy_gain ) );

    // Create the distribution
    native_ae_distribution.reset(
      new MonteCarlo::AtomicExcitationAdjointElectronScatteringDistribution(
           energy_gain_function ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END(); 

//---------------------------------------------------------------------------//
// end tstAtomicExcitationAdjointElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
