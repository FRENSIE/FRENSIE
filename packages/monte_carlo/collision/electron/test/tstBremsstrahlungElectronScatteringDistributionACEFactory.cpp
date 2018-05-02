//---------------------------------------------------------------------------//
//!
//! \file   tstBremsstrahlungElectronScatteringDistributionACEFactory.cpp
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
  dipole_distribution, twobs_distribution, epr14_distribution;


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

  // sample dipole_distribution
  dipole_distribution->sample( incoming_energy,
                               photon_energy,
                               photon_angle_cosine );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon_energy, 1.5161296983571827e-05, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon_angle_cosine, 0.0592724905908, 1e-12 );

  // sample using the eprdata14 file
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

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

  dipole_distribution->sampleAndRecordTrials( incoming_energy,
                                              photon_energy,
                                              photon_angle_cosine,
                                              trials );

  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_FLOATING_EQUALITY( photon_energy, 1.5161296983571827e-05, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon_angle_cosine, 0.0592724905908, 1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 11 );

  // sample using the eprdata14 file
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  epr14_distribution->sampleAndRecordTrials( incoming_energy,
                                             photon_energy,
                                             photon_angle_cosine,
                                             trials );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // Test
  FRENSIE_CHECK_FLOATING_EQUALITY( photon_energy, 1.5615223131747785e-05, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon_angle_cosine, 5.92724905907677790e-02, 1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 12 );
}

//---------------------------------------------------------------------------//
// Check that the sample() function using detailed 2BS
FRENSIE_UNIT_TEST( BremsstrahlungElectronScatteringDistributionACEFactory,
                   sample_TwoBSBremsstrahlung )
{
  // Set up the random number stream
  std::vector<double> fake_stream( 5 );
  fake_stream[0] = 0.5; // Correlated sample the 3.1622800E-01 MeV and 2.0 MeV distributions
  fake_stream[1] = 0.5; // Sample a photon angle of 0.9118675275
  fake_stream[2] = 0.49; // Reject the angle
  fake_stream[3] = 0.5; // Sample a photon angle of 0.9118675275
  fake_stream[4] = 0.48; // Accept the angle


  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0;
  double photon_energy, photon_angle_cosine;

  twobs_distribution->sample( incoming_energy,
                              photon_energy,
                              photon_angle_cosine );

  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_FLOATING_EQUALITY( photon_energy, 1.65383677217787E-04, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon_angle_cosine, 0.612270260118, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the sampleAndRecordTrials() function using detailed 2BS
FRENSIE_UNIT_TEST( BremsstrahlungElectronScatteringDistributionACEFactory,
                   sampleAndRecordTrials_TwoBSBremsstrahlung )
{
  // Set up the random number stream
  std::vector<double> fake_stream( 5 );
  fake_stream[0] = 0.5; // Correlated sample the 3.1622800E-01 MeV and 2.0 MeV distributions
  fake_stream[1] = 0.5; // Sample a photon angle of 0.9118675275
  fake_stream[2] = 0.49; // Reject the angle
  fake_stream[3] = 0.5; // Sample a photon angle of 0.9118675275
  fake_stream[4] = 0.48; // Accept the angle


  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ElectronScatteringDistribution::Counter trials = 0;
  double incoming_energy = 1.0;
  double photon_energy, photon_angle_cosine;

  twobs_distribution->sampleAndRecordTrials( incoming_energy,
                                             photon_energy,
                                             photon_angle_cosine,
                                             trials );

  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_FLOATING_EQUALITY( photon_energy, 1.65383677217787E-04, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon_angle_cosine, 0.612270260118, 1e-12 );
  FRENSIE_CHECK_EQUAL( trials, 1 );
}


//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_ace12_file_name, test_ace12_table_name,
            test_ace14_file_name, test_ace14_table_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_ace12_file",
                                        test_ace12_file_name, "",
                                        "Test ACE12 file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_ace12_table",
                                        test_ace12_table_name, "",
                                        "Test ACE12 table name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_ace14_file",
                                        test_ace14_file_name, "",
                                        "Test ACE14 file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_ace14_table",
                                        test_ace14_table_name, "",
                                        "Test ACE14 table name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create the distributions using the eprdata14 file
  {
  // Create a file handler and data extractor
  std::unique_ptr<Data::ACEFileHandler> ace_file_handler(
        new Data::ACEFileHandler( test_ace12_file_name,
                                  test_ace12_table_name,
                                  1u ) );

  std::unique_ptr<Data::XSSEPRDataExtractor> xss_data_extractor(
        new Data::XSSEPRDataExtractor( ace_file_handler->getTableNXSArray(),
                                       ace_file_handler->getTableJXSArray(),
                                       ace_file_handler->getTableXSSArray() ) );

  MonteCarlo::BremsstrahlungElectronScatteringDistributionACEFactory::createBremsstrahlungDistribution(
                                                 *xss_data_extractor,
                                                 dipole_distribution );

  MonteCarlo::BremsstrahlungElectronScatteringDistributionACEFactory::createBremsstrahlungDistribution(
                                    xss_data_extractor->extractAtomicNumber(),
                                    *xss_data_extractor,
                                    twobs_distribution );
  }

  // Create the distribution using the eprdata14 file
  {
  // Create a file handler and data extractor
  std::unique_ptr<Data::ACEFileHandler> ace_file_handler(
        new Data::ACEFileHandler( test_ace14_file_name,
                                  test_ace14_table_name,
                                  1u ) );

  std::unique_ptr<Data::XSSEPRDataExtractor> xss_data_extractor(
        new Data::XSSEPRDataExtractor( ace_file_handler->getTableNXSArray(),
                                       ace_file_handler->getTableJXSArray(),
                                       ace_file_handler->getTableXSSArray() ) );

  MonteCarlo::BremsstrahlungElectronScatteringDistributionACEFactory::createBremsstrahlungDistribution(
                                    *xss_data_extractor,
                                    epr14_distribution );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstBremsstrahlungElectronScatteringDistributionACEFactory.cpp
//---------------------------------------------------------------------------//
