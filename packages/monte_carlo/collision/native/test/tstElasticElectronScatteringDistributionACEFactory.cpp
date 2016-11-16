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
#include "Utility_ElasticElectronDistribution.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"


//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor;
std::shared_ptr< const MonteCarlo::CutoffElasticElectronScatteringDistribution>
  ace_cutoff_elastic_distribution;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check sample can be evaluated
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionACEFactory,
                   sample )
{
  MonteCarlo::ElasticElectronScatteringDistributionACEFactory::createCutoffElasticDistribution(
                                                ace_cutoff_elastic_distribution,
                                                *xss_data_extractor );
  // Set fake random number stream
  std::vector<double> fake_stream( 1 );
  fake_stream[0] = 0.5; // sample mu = 0.9874366113907

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0e-3;
  double scattering_angle_cosine, outgoing_energy;

  // sampleAndRecordTrialsImpl cutoff
  ace_cutoff_elastic_distribution->sample( incoming_energy,
                                           outgoing_energy,
                                           scattering_angle_cosine );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.9874366113907, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check sampleAndRecordTrials can be evaluated
TEUCHOS_UNIT_TEST( ElasticElectronScatteringDistributionACEFactory,
                   sampleAndRecordTrials )
{
  MonteCarlo::ElasticElectronScatteringDistributionACEFactory::createCutoffElasticDistribution(
                                                ace_cutoff_elastic_distribution,
                                                *xss_data_extractor );

  // Set fake random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // sample mu = 0.9874366113907
  fake_stream[1] = 0.5; // sample mu = 9.99999500000093E-01

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incoming_energy = 1.0e-3;
  double scattering_angle_cosine, outgoing_energy;
  unsigned trials = 10;

  // sampleAndRecordTrialsImpl from distribution
  ace_cutoff_elastic_distribution->sampleAndRecordTrials(
                                          incoming_energy,
                                          outgoing_energy,
                                          scattering_angle_cosine,
                                          trials );

  // Test
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.9874366113907, 1e-12 );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1.0e-3, 1e-12 );
  TEST_EQUALITY_CONST( trials, 11 );
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
// end tstElasticElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
