//---------------------------------------------------------------------------//
//!
//! \file   tstAtomicExcitationElectronScatteringDistributionACEFactory.cpp
//! \author Luke Kersting
//! \brief  Atomic Excitation scattering distribution ACE factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_AtomicExcitationElectronScatteringDistributionACEFactory.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<const MonteCarlo::AtomicExcitationElectronScatteringDistribution>
   epr12_distribution, epr14_distribution;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the sample() function
TEUCHOS_UNIT_TEST( AtomicExcitationElectronScatteringDistributionACEFactory,
                   sample )
{
  double incoming_energy = 1e-3;
  double outgoing_energy,scattering_angle_cosine;

  // sample epr12_distribution
  epr12_distribution->sample( incoming_energy,
                        outgoing_energy,
                        scattering_angle_cosine );

  TEST_FLOATING_EQUALITY( outgoing_energy, 1e-3- 9.32298E-06, 1e-12 );
  TEST_EQUALITY_CONST( scattering_angle_cosine, 1.0 );

  // sample epr14_distribution
  epr14_distribution->sample( incoming_energy,
                        outgoing_energy,
                        scattering_angle_cosine );

  TEST_FLOATING_EQUALITY( outgoing_energy, 1e-3- 9.32298E-06, 1e-12 );
  TEST_EQUALITY_CONST( scattering_angle_cosine, 1.0 );

}

//---------------------------------------------------------------------------//
// Check that the sampleAndRecordTrials() function
TEUCHOS_UNIT_TEST( AtomicExcitationElectronScatteringDistributionACEFactory,
                   sampleAndRecordTrials )
{
  unsigned trials = 10;
  double incoming_energy = 1e-3;
  double outgoing_energy,scattering_angle_cosine;

  // sample epr12_distribution
  epr12_distribution->sampleAndRecordTrials( incoming_energy,
                                       outgoing_energy,
                                       scattering_angle_cosine,
                                       trials );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1e-3- 9.32298E-06, 1e-12 );
  TEST_EQUALITY_CONST( scattering_angle_cosine, 1.0 );
  TEST_EQUALITY_CONST( trials, 11 );

  // sample epr14_distribution
  epr14_distribution->sampleAndRecordTrials( incoming_energy,
                                       outgoing_energy,
                                       scattering_angle_cosine,
                                       trials );
  TEST_FLOATING_EQUALITY( outgoing_energy, 1e-3- 9.32298E-06, 1e-12 );
  TEST_EQUALITY_CONST( scattering_angle_cosine, 1.0 );
  TEST_EQUALITY_CONST( trials, 12 );

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
  // Create the distribution using the eprdata12 file
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

  MonteCarlo::AtomicExcitationElectronScatteringDistributionACEFactory::createAtomicExcitationDistribution(
                                                 *xss_data_extractor,
                                                 epr12_distribution );
  }

  // Create the distribution using the eprdata14 file
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

  MonteCarlo::AtomicExcitationElectronScatteringDistributionACEFactory::createAtomicExcitationDistribution(
                                                 *xss_data_extractor,
                                                 epr14_distribution );
  }
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstAtomicExcitationElectronScatteringDistributionACEFactory.cpp
//---------------------------------------------------------------------------//
