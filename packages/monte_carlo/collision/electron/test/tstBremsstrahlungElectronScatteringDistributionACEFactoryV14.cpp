//---------------------------------------------------------------------------//
//!
//! \file   tstBremsstrahlungElectronScatteringDistributionACEFactoryV14.cpp
//! \author Luke Kersting
//! \brief  bremsstrahlung scattering distribution ACE factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_BremsstrahlungElectronScatteringDistributionACEFactory.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<const MonteCarlo::BremsstrahlungElectronScatteringDistribution>
  epr14_distribution;


//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the sample() function for a dipole distribution
FRENSIE_UNIT_TEST( BremsstrahlungElectronScatteringDistributionACEFactory,
                   sample_DipoleBremsstrahlung )
{
  // Set up the random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // Correlated sample the 7.94968E-04 MeV and 1.18921E-02 MeV distributions
  fake_stream[1] = 0.5; // Sample angle 0.0557151835328 from analytical function

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 0.0009;
  double photon_energy, photon_angle_cosine;

  epr14_distribution->sample( incoming_energy,
                              photon_energy,
                              photon_angle_cosine );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( photon_energy, 1.5615223131747785e-05, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon_angle_cosine, 5.9272490590767779e-02, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the sampleAndRecordTrials() function for a dipole distribution
FRENSIE_UNIT_TEST( BremsstrahlungElectronScatteringDistributionACEFactory,
                   sampleAndRecordTrials_DipoleBremsstrahlung )
{
  // Set up the random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // Correlated sample the 7.94968E-04 MeV and 1.18921E-02 MeV distributions
  fake_stream[1] = 0.5; // Sample mu = 0.0592724905908 from analytical function

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronScatteringDistribution::Counter trials = 10;
  double incoming_energy = 0.0009;
  double photon_energy, photon_angle_cosine;

  epr14_distribution->sampleAndRecordTrials( incoming_energy,
                                             photon_energy,
                                             photon_angle_cosine,
                                             trials );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( photon_energy, 1.5615223131747785e-05, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon_angle_cosine, 5.92724905907677790e-02, 1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 11 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_ace14_file_name;
unsigned test_ace14_file_start_line;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_ace14_file",
                                        test_ace14_file_name, "",
                                        "Test ACE14 file name" );

  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_ace14_file_start_line",
                                        test_ace14_file_start_line, 1,
                                        "Test ACE14 file start line" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create a file handler and data extractor
  std::unique_ptr<Data::ACEFileHandler> ace_file_handler(
        new Data::ACEFileHandler( test_ace14_file_name,
                                  "82000.14p",
                                  test_ace14_file_start_line ) );

  std::unique_ptr<Data::XSSEPRDataExtractor> xss_data_extractor(
        new Data::XSSEPRDataExtractor( ace_file_handler->getTableNXSArray(),
                                       ace_file_handler->getTableJXSArray(),
                                       ace_file_handler->getTableXSSArray() ) );

  MonteCarlo::BremsstrahlungElectronScatteringDistributionACEFactory::createBremsstrahlungDistribution(
                                    *xss_data_extractor,
                                    epr14_distribution );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstBremsstrahlungElectronScatteringDistributionACEFactoryV14.cpp
//---------------------------------------------------------------------------//
