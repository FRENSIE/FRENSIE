//---------------------------------------------------------------------------//
//!
//! \file   tstAtomicExcitationAdjointElectronScatteringDistribution.cpp
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
// Testing Structs
//---------------------------------------------------------------------------//
class TestAtomicExcitationAdjointElectronScatteringDistribution : public MonteCarlo::AtomicExcitationAdjointElectronScatteringDistribution
{
public:

  // Constructor
  TestAtomicExcitationAdjointElectronScatteringDistribution(
    const std::shared_ptr<const Utility::UnivariateDistribution>& dist )
    : MonteCarlo::AtomicExcitationAdjointElectronScatteringDistribution( dist )
  { /* ... */ }

  // Destructor
  ~TestAtomicExcitationAdjointElectronScatteringDistribution()
  { /* ... */ }

  using MonteCarlo::AtomicExcitationAdjointElectronScatteringDistribution::isEnergyInNudgeWindow;
  using MonteCarlo::AtomicExcitationAdjointElectronScatteringDistribution::nudgeEnergyToLineEnergy;
};

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::AtomicExcitationAdjointElectronScatteringDistribution>
  ace_ae_distribution;

std::shared_ptr<TestAtomicExcitationAdjointElectronScatteringDistribution>
  native_ae_distribution;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the sample() function
FRENSIE_UNIT_TEST( AtomicExcitationAdjointElectronScatteringDistribution,
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
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 1e-3, 1e-12 );
  FRENSIE_CHECK_EQUAL( scattering_angle_cosine, 1.0 );

}

//---------------------------------------------------------------------------//
// Check that the sample() function
FRENSIE_UNIT_TEST( AtomicExcitationAdjointElectronScatteringDistribution,
                   sample_native )
{
  MonteCarlo::AdjointElectronState electron( 0 );
  electron.setEnergy( 1.52422504085124348e+01 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double outgoing_energy,scattering_angle_cosine;
  double final_energy = electron.getEnergy() + 2.10069182636912224e-05;

  // sample distribution
  native_ae_distribution->sample( electron.getEnergy(),
                                  outgoing_energy,
                                  scattering_angle_cosine );

  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, final_energy, 1e-12 );
  FRENSIE_CHECK_EQUAL( scattering_angle_cosine, 1.0 );

  // Sample at the max energy
  electron.setEnergy( 20.0 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  final_energy = electron.getEnergy() + 2.10108000193005457e-05;

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
                   sampleAndRecordTrials_ace )
{
  MonteCarlo::AdjointElectronState electron( 0 );
  electron.setEnergy( 1e-3 - 9.322980E-6 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double outgoing_energy,scattering_angle_cosine;
  MonteCarlo::AdjointElectronScatteringDistribution::Counter trials = 10;

  // sample distribution
  ace_ae_distribution->sampleAndRecordTrials( electron.getEnergy(),
                                              outgoing_energy,
                                              scattering_angle_cosine,
                                              trials );

  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 1e-3, 1e-12 );
  FRENSIE_CHECK_EQUAL( scattering_angle_cosine, 1.0 );
  FRENSIE_CHECK_EQUAL( trials, 11 );
}

//---------------------------------------------------------------------------//
// Check that the sampleAndRecordTrials() function
FRENSIE_UNIT_TEST( AtomicExcitationAdjointElectronScatteringDistribution,
                   sampleAndRecordTrials_native )
{
  MonteCarlo::AdjointElectronState electron( 0 );
  electron.setEnergy( 1.52422504085124348e+01 );
  electron.setDirection( 0.0, 0.0, 1.0 );

  double outgoing_energy,scattering_angle_cosine;
  double final_energy = electron.getEnergy() + 2.10069182636912224e-05;
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
  FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_electron.getEnergy(), 1e-3, 1e-12 );
  FRENSIE_CHECK_EQUAL( adjoint_electron.getZDirection(), 1.0 );

}

//---------------------------------------------------------------------------//
// Check that the scattering angle can be evaluated
FRENSIE_UNIT_TEST( AtomicExcitationAdjointElectronScatteringDistribution,
                   scatterAdjointElectron_native )
{
  MonteCarlo::ParticleBank bank;

  MonteCarlo::AdjointElectronState adjoint_electron( 0 );
  adjoint_electron.setEnergy( 1.52422504085124348e+01 );
  adjoint_electron.setDirection( 0.0, 0.0, 1.0 );

  Data::SubshellType shell_of_interaction;
  double final_energy = adjoint_electron.getEnergy() + 2.10069182636912224e-05;

  // Scatter the adjoint electron
  native_ae_distribution->scatterAdjointElectron( adjoint_electron,
                                                  bank,
                                                  shell_of_interaction );

  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_electron.getEnergy(), final_energy, 1e-12 );
  FRENSIE_CHECK_EQUAL( adjoint_electron.getZDirection(), 1.0 );

  // Scatter into line energy at 1.0 MeV
  adjoint_electron.setEnergy( 9.99979472645e-01 );

  // Scatter the adjoint electron
  native_ae_distribution->scatterAdjointElectron( adjoint_electron,
                                                  bank,
                                                  shell_of_interaction );

  // Test
  FRENSIE_CHECK_EQUAL( adjoint_electron.getEnergy(), 1.0 );
  FRENSIE_CHECK_EQUAL( adjoint_electron.getZDirection(), 1.0 );

  // Scatter just below line energy at 1.0 MeV
  adjoint_electron.setEnergy( 9.99979472640e-01 );

  // Scatter the adjoint electron
  native_ae_distribution->scatterAdjointElectron( adjoint_electron,
                                                  bank,
                                                  shell_of_interaction );

  // Test
  FRENSIE_CHECK_EQUAL( adjoint_electron.getEnergy(), 9.999999899996029340e-01 );
  FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_electron.getEnergy(), 1.0, 1e-7 );
  FRENSIE_CHECK_EQUAL( adjoint_electron.getZDirection(), 1.0 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_ace_file_name, test_ace_table_name, test_native_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_ace_file",
                                        test_ace_file_name, "",
                                        "Test ACE file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_ace_table",
                                        test_ace_table_name, "",
                                        "Test ACE table name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_native_file",
                                        test_native_file_name, "",
                                        "Test Native file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create the ACE distribution
  {
    // Create a file handler and data extractor
    std::unique_ptr<Data::ACEFileHandler> ace_file_handler(
      new Data::ACEFileHandler( test_ace_file_name,
                                test_ace_table_name,
                                1u ) );
    std::unique_ptr<Data::XSSEPRDataExtractor> xss_data_extractor(
        new Data::XSSEPRDataExtractor(
            ace_file_handler->getTableNXSArray(),
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

    // Evaluate the adjoint energy grid for atomic excitation energy gain
    std::vector<double> adjoint_energy_grid( size );

    // Loop through the energy grid
    for ( unsigned n = 0; n < size; ++n )
    {
      adjoint_energy_grid[n] = energy_grid[n] - energy_loss[n];
    }

    // Create the energy gain distributions
    std::shared_ptr<Utility::UnivariateDistribution> energy_gain_function(
      new Utility::TabularDistribution<Utility::LogLog>( adjoint_energy_grid,
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
    auto data_container =
      std::make_shared<Data::AdjointElectronPhotonRelaxationDataContainer>(
        test_native_file_name );

    // Get the adjoint atomic excitation energy grid
    std::vector<double> energy_grid(
      data_container->getAdjointAtomicExcitationEnergyGrid() );

    // Get the adjoint atomic excitation energy gain
    std::vector<double> energy_gain(
      data_container->getAdjointAtomicExcitationEnergyGain() );

    // Create the energy gain distribution
    std::shared_ptr<Utility::UnivariateDistribution> energy_gain_function =
      std::make_shared<Utility::TabularDistribution<Utility::LogLog> >( energy_grid,
                                                         energy_gain );

    // Create the distribution
    native_ae_distribution.reset(
      new TestAtomicExcitationAdjointElectronScatteringDistribution(
           energy_gain_function ) );

    // Create the scattering distribution
    auto critical_line_energies = std::make_shared<std::vector<double> >( 1 );

    (*critical_line_energies)[0] = 1.0;

    native_ae_distribution->setCriticalLineEnergies( critical_line_energies );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstAtomicExcitationAdjointElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
