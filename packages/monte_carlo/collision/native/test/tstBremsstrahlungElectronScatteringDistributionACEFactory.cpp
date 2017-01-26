//---------------------------------------------------------------------------//
//!
//! \file   tstBremsstrahlungElectronScatteringDistributionACEFactory.cpp
//! \author Luke Kersting
//! \brief  bremsstrahlung scattering distribution ACE factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_BremsstrahlungElectronScatteringDistributionACEFactory.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor;

std::shared_ptr<const MonteCarlo::BremsstrahlungElectronScatteringDistribution>
  dipole_distribution;

std::shared_ptr<const MonteCarlo::BremsstrahlungElectronScatteringDistribution>
  twobs_distribution;


//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the sample() function for a dipole distribution
TEUCHOS_UNIT_TEST( BremsstrahlungElectronScatteringDistributionACEFactory,
                   sample_DipoleBremsstrahlung )
{
  MonteCarlo::BremsstrahlungElectronScatteringDistributionACEFactory::createBremsstrahlungDistribution(
                                                 *xss_data_extractor,
                                                 dipole_distribution );

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

  Utility::RandomNumberGenerator::unsetFakeStream();

  // Test
  TEST_FLOATING_EQUALITY( photon_energy, 1.51612969835718E-05 , 1e-12 );
  TEST_FLOATING_EQUALITY( photon_angle_cosine, 0.0592724905908 , 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the sampleAndRecordTrials() function for a dipole distribution
TEUCHOS_UNIT_TEST( BremsstrahlungElectronScatteringDistributionACEFactory,
                   sampleAndRecordTrials_DipoleBremsstrahlung )
{
  MonteCarlo::BremsstrahlungElectronScatteringDistributionACEFactory::createBremsstrahlungDistribution(
                                                 *xss_data_extractor,
                                                 dipole_distribution );

  // Set up the random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // Correlated sample the 7.94968E-04 MeV and 1.18921E-02 MeV distributions
  fake_stream[1] = 0.5; // Sample angle 0.0557151835328 from analytical function

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned trials = 10;
  double incoming_energy = 0.0009;
  double photon_energy, photon_angle_cosine;

  dipole_distribution->sampleAndRecordTrials( incoming_energy,
                                              photon_energy,
                                              photon_angle_cosine,
                                              trials );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( photon_energy, 1.51612969835718E-05 , 1e-12 );
  TEST_FLOATING_EQUALITY( photon_angle_cosine, 0.0592724905908 , 1e-12 );
  TEST_EQUALITY_CONST( trials, 11 );
}

//---------------------------------------------------------------------------//
// Check that the sample() function using detailed 2BS
TEUCHOS_UNIT_TEST( BremsstrahlungElectronScatteringDistributionACEFactory,
                   sample_TwoBSBremsstrahlung )
{
  MonteCarlo::BremsstrahlungElectronScatteringDistributionACEFactory::createBremsstrahlungDistribution(
                                    *xss_data_extractor,
                                    twobs_distribution,
                                    xss_data_extractor->extractAtomicNumber() );

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

  TEST_FLOATING_EQUALITY( photon_energy, 1.65383677217787E-04, 1e-12 );
  TEST_FLOATING_EQUALITY( photon_angle_cosine, 0.612270260118, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the sampleAndRecordTrials() function using detailed 2BS
TEUCHOS_UNIT_TEST( BremsstrahlungElectronScatteringDistributionACEFactory,
                   sampleAndRecordTrials_TwoBSBremsstrahlung )
{
  MonteCarlo::BremsstrahlungElectronScatteringDistributionACEFactory::createBremsstrahlungDistribution(
                                    *xss_data_extractor,
                                    twobs_distribution,
                                    xss_data_extractor->extractAtomicNumber() );

  // Set up the random number stream
  std::vector<double> fake_stream( 5 );
  fake_stream[0] = 0.5; // Correlated sample the 3.1622800E-01 MeV and 2.0 MeV distributions
  fake_stream[1] = 0.5; // Sample a photon angle of 0.9118675275
  fake_stream[2] = 0.49; // Reject the angle
  fake_stream[3] = 0.5; // Sample a photon angle of 0.9118675275
  fake_stream[4] = 0.48; // Accept the angle


  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned trials = 0.0;
  double incoming_energy = 1.0;
  double photon_energy, photon_angle_cosine;

  twobs_distribution->sampleAndRecordTrials( incoming_energy,
                                             photon_energy,
                                             photon_angle_cosine,
                                             trials );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( photon_energy, 1.65383677217787E-04, 1e-12 );
  TEST_FLOATING_EQUALITY( photon_angle_cosine, 0.612270260118, 1e-12 );
  TEST_EQUALITY_CONST( trials, 1.0 );
}


//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_ace_file_name, test_ace_table_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_ace_file",
                   &test_ace_file_name,
                   "Test ACE file name" );
  clp().setOption( "test_ace_table",
                   &test_ace_table_name,
                   "Test ACE table name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Create a file handler and data extractor
  Teuchos::RCP<Data::ACEFileHandler> ace_file_handler(
        new Data::ACEFileHandler( test_ace_file_name,
                                  test_ace_table_name,
                                  1u ) );
  xss_data_extractor.reset(
        new Data::XSSEPRDataExtractor( ace_file_handler->getTableNXSArray(),
                                       ace_file_handler->getTableJXSArray(),
                                       ace_file_handler->getTableXSSArray() ) );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstBremsstrahlungElectronScatteringDistributionACEFactory.cpp
//---------------------------------------------------------------------------//
