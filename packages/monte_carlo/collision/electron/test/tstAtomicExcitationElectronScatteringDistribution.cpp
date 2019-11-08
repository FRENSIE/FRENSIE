//---------------------------------------------------------------------------//
//!
//! \file   tstAtomicExcitationElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  Atomic Excitation electron scattering distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_AtomicExcitationElectronScatteringDistribution.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::AtomicExcitationElectronScatteringDistribution>
  ace_atomic_excitation_distribution;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the sample() function
FRENSIE_UNIT_TEST( AtomicExcitationElectronScatteringDistribution,
                   sample )
{
  MonteCarlo::ParticleBank bank;

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.000000000000e-03 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double outgoing_energy,scattering_angle_cosine;
  double final_energy = (electron.getEnergy() - 9.32298000000E-06);

  // sample distribution
  ace_atomic_excitation_distribution->sample( electron.getEnergy(),
                                              outgoing_energy,
                                              scattering_angle_cosine );

  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy,final_energy, 1e-12 );
  FRENSIE_CHECK_EQUAL( scattering_angle_cosine, 1.0 );

}

//---------------------------------------------------------------------------//
// Check that the sampleAndRecordTrials() function
FRENSIE_UNIT_TEST( AtomicExcitationElectronScatteringDistribution,
                   sampleAndRecordTrials )
{
  MonteCarlo::ParticleBank bank;

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.000000000000e-03 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double outgoing_energy,scattering_angle_cosine;
  double final_energy = (electron.getEnergy() - 9.32298000000E-06);
  MonteCarlo::ElectronScatteringDistribution::Counter trials = 10;

  // sample distribution
  ace_atomic_excitation_distribution->sampleAndRecordTrials(
                                           electron.getEnergy(),
                                           outgoing_energy,
                                           scattering_angle_cosine,
                                           trials );

  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy,final_energy, 1e-12 );
  FRENSIE_CHECK_EQUAL( scattering_angle_cosine, 1.0 );
  FRENSIE_CHECK_EQUAL( trials, 11 );

}
//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
FRENSIE_UNIT_TEST( AtomicExcitationElectronScatteringDistribution,
                   scatterElectron )
{
  MonteCarlo::ParticleBank bank;

  MonteCarlo::ElectronState electron( 0 );
  electron.setEnergy( 1.000000000000e-03 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  Data::SubshellType shell_of_interaction;
  double final_energy = (electron.getEnergy() - 9.32298000000E-06);

  // Scatter the electron
  ace_atomic_excitation_distribution->scatterElectron( electron,
                                                       bank,
                                                       shell_of_interaction );

  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getEnergy(), final_energy, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( electron.getZDirection(), 1.0, 1e-12 );

}

//---------------------------------------------------------------------------//
// Check that the screening angle can be evaluated
FRENSIE_UNIT_TEST( AtomicExcitationElectronScatteringDistribution,
                   scatterPositron )
{
  MonteCarlo::ParticleBank bank;

  MonteCarlo::PositronState positron( 0 );
  positron.setEnergy( 1e-03 );
  positron.setDirection( 0.0, 0.0, 1.0 );

  Data::SubshellType shell_of_interaction;
  double final_energy = (positron.getEnergy() - 9.32298E-06);

  // Scatter the positron
  ace_atomic_excitation_distribution->scatterPositron( positron,
                                                       bank,
                                                       shell_of_interaction );

  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( positron.getEnergy(), final_energy, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( positron.getZDirection(), 1.0, 1e-12 );

}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_ace_file_name;
unsigned test_ace_file_start_line;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_ace_file",
                                        test_ace_file_name, "",
                                        "Test ACE file name" );

  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_ace_file_start_line",
                                        test_ace_file_start_line, 1,
                                        "Test ACE file start line" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create a file handler and data extractor
  std::unique_ptr<Data::ACEFileHandler> ace_file_handler(
     new Data::ACEFileHandler( test_ace_file_name,
                               "82000.12p",
                               test_ace_file_start_line ) );
  
  std::unique_ptr<Data::XSSEPRDataExtractor> xss_data_extractor(
    new Data::XSSEPRDataExtractor( ace_file_handler->getTableNXSArray(),
                                   ace_file_handler->getTableJXSArray(),
                                   ace_file_handler->getTableXSSArray() ) );

  // Extract the atomic excitation information data block (EXCIT)
  Utility::ArrayView<const double> excit_block(
                  xss_data_extractor->extractEXCITBlock() );

  // Extract the number of tabulated energies
  int size = excit_block.size()/2;

  // Extract the energy grid for atomic excitation energy loss
  std::vector<double> energy_grid(excit_block(0,size));

  // Extract the energy loss for atomic excitation
  std::vector<double> energy_loss(excit_block(size,size));

  // Create the energy loss distributions
  std::shared_ptr<Utility::UnivariateDistribution> energy_loss_function;

  energy_loss_function.reset(
    new Utility::TabularDistribution<Utility::LinLin>( energy_grid,
                                                       energy_loss ) );

  // Create the distribution
  ace_atomic_excitation_distribution.reset(
    new MonteCarlo::AtomicExcitationElectronScatteringDistribution(
           energy_loss_function ) );

  // Clear setup data
  ace_file_handler.reset();
  xss_data_extractor.reset();

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstAtomicExcitationElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
