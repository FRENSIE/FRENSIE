//---------------------------------------------------------------------------//
//!
//! \file   tstElasticElectronScatteringDistributionACEFactory.cpp
//! \author Luke Kersting
//! \brief  Elastic electron scattering distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElasticElectronScatteringDistributionACEFactory.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"


//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr< const MonteCarlo::CutoffElasticElectronScatteringDistribution>
  epr12_cutoff_distribution, epr14_cutoff_distribution;
std::shared_ptr< const MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution>
  epr14_rutherford_distribution;
//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the cutoff distribution can be created
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionACEFactory,
                   createCutoffElasticDistribution_epr12 )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // sample mu = 0.9874366113907
  fake_stream[1] = 0.5; // sample mu = 9.9999621617094148e-01

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0e-3;
  double scattering_angle_cosine, outgoing_energy;

  // sample
  epr12_cutoff_distribution->sample( incoming_energy,
                                     outgoing_energy,
                                     scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.9874366113907, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

  // Sample
  incoming_energy = 12.45;
  epr12_cutoff_distribution->sample( incoming_energy,
                                     outgoing_energy,
                                     scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999621617094148e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 12.45, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the cutoff distribution can be created
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionACEFactory,
                   createCutoffElasticDistribution_epr14 )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // sample mu = 9.8786332385681019e-01
  fake_stream[1] = 0.5; // sample mu = 9.9999529365431461e-01

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0e-3;
  double scattering_angle_cosine, outgoing_energy;

  // sample
  epr14_cutoff_distribution->sample( incoming_energy,
                                     outgoing_energy,
                                     scattering_angle_cosine );
  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.8750450783598187e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );

  // Sample
  incoming_energy = 12.45;
  epr14_cutoff_distribution->sample( incoming_energy,
                                     outgoing_energy,
                                     scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.9999513901893400e-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 12.45, 1e-12 );
}


//---------------------------------------------------------------------------//
// Check that the screened Rutherford distribution can be created
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionACEFactory,
                   createScreenedRutherfordElasticDistribution_epr14 )
{
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 9.99999500000093E-01

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0e-3;
  double scattering_angle_cosine, outgoing_energy;

  // samplefrom distribution
  epr14_rutherford_distribution->sample( incoming_energy,
                                         outgoing_energy,
                                         scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 9.99999500000093E-01, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
}


//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_ace12_file_name, test_ace12_table_name,
            test_ace14_file_name, test_ace14_table_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_ace12_file",
                   &test_ace12_file_name,
                   "Test ACE12 file name" );
  clp().setOption( "test_ace12_table",
                   &test_ace12_table_name,
                   "Test ACE12 table name" );
  clp().setOption( "test_ace14_file",
                   &test_ace14_file_name,
                   "Test ACE14 file name" );
  clp().setOption( "test_ace14_table",
                   &test_ace14_table_name,
                   "Test ACE14 table name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Create eprdata12 distributions
  {
  // Create a file handler and data extractor
  Teuchos::RCP<Data::ACEFileHandler> ace_file_handler(
        new Data::ACEFileHandler( test_ace12_file_name,
                                  test_ace12_table_name,
                                  1u ) );

  Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor(
        new Data::XSSEPRDataExtractor( ace_file_handler->getTableNXSArray(),
                                       ace_file_handler->getTableJXSArray(),
                                       ace_file_handler->getTableXSSArray() ) );

  MonteCarlo::ElasticElectronScatteringDistributionACEFactory::createCutoffElasticDistribution(
                                                epr12_cutoff_distribution,
                                                *xss_data_extractor );
  }

  // Create eprdata14 distributions
  {
  // Create a file handler and data extractor
  Teuchos::RCP<Data::ACEFileHandler> ace_file_handler(
        new Data::ACEFileHandler( test_ace14_file_name,
                                  test_ace14_table_name,
                                  1u ) );

  Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor(
        new Data::XSSEPRDataExtractor( ace_file_handler->getTableNXSArray(),
                                       ace_file_handler->getTableJXSArray(),
                                       ace_file_handler->getTableXSSArray() ) );

  MonteCarlo::ElasticElectronScatteringDistributionACEFactory::createCutoffElasticDistribution(
                                                epr14_cutoff_distribution,
                                                *xss_data_extractor );


  MonteCarlo::ElasticElectronScatteringDistributionACEFactory::createScreenedRutherfordElasticDistribution(
                                    epr14_rutherford_distribution,
                                    xss_data_extractor->extractAtomicNumber() );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstElasticElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
