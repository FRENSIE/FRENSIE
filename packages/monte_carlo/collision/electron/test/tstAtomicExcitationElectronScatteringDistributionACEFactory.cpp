//---------------------------------------------------------------------------//
//!
//! \file   tstAtomicExcitationElectronScatteringDistributionACEFactory.cpp
//! \author Luke Kersting
//! \brief  Atomic Excitation scattering distribution ACE factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_AtomicExcitationElectronScatteringDistributionACEFactory.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<const MonteCarlo::AtomicExcitationElectronScatteringDistribution>
   epr12_distribution, epr14_distribution;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the sample() function
FRENSIE_UNIT_TEST( AtomicExcitationElectronScatteringDistributionACEFactory,
                   sample )
{
  double incoming_energy = 1e-3;
  double outgoing_energy,scattering_angle_cosine;

  // sample epr12_distribution
  epr12_distribution->sample( incoming_energy,
                              outgoing_energy,
                              scattering_angle_cosine );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 1e-3 - 9.32298E-06, 1e-12 );
  FRENSIE_CHECK_EQUAL( scattering_angle_cosine, 1.0 );

  incoming_energy = 1.05;
  epr12_distribution->sample( incoming_energy,
                              outgoing_energy,
                              scattering_angle_cosine );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 1.04998928662, 1e-12 );
  FRENSIE_CHECK_EQUAL( scattering_angle_cosine, 1.0 );
std::cout << std::setprecision(16) << std::scientific << "outgoing_energy = \t" << outgoing_energy << std::endl;

  // sample epr14_distribution
  incoming_energy = 1e-3;
  epr14_distribution->sample( incoming_energy,
                              outgoing_energy,
                              scattering_angle_cosine );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 1e-3 - 9.32298E-06, 1e-12 );
  FRENSIE_CHECK_EQUAL( scattering_angle_cosine, 1.0 );

  incoming_energy = 1.05;
  epr14_distribution->sample( incoming_energy,
                              outgoing_energy,
                              scattering_angle_cosine );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 1.0499892862612037, 1e-12 );
  FRENSIE_CHECK_EQUAL( scattering_angle_cosine, 1.0 );
std::cout << std::setprecision(16) << std::scientific << "outgoing_energy = \t" << outgoing_energy << std::endl;
}

//---------------------------------------------------------------------------//
// Check that the sampleAndRecordTrials() function
FRENSIE_UNIT_TEST( AtomicExcitationElectronScatteringDistributionACEFactory,
                   sampleAndRecordTrials )
{
  MonteCarlo::ElectronScatteringDistribution::Counter trials = 10;
  double incoming_energy = 1e-3;
  double outgoing_energy,scattering_angle_cosine;

  // sample epr12_distribution
  epr12_distribution->sampleAndRecordTrials( incoming_energy,
                                             outgoing_energy,
                                             scattering_angle_cosine,
                                             trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 1e-3 - 9.32298E-06, 1e-12 );
  FRENSIE_CHECK_EQUAL( scattering_angle_cosine, 1.0 );
  FRENSIE_CHECK_EQUAL( trials, 11 );

  incoming_energy = 1.05;
  epr12_distribution->sampleAndRecordTrials( incoming_energy,
                                             outgoing_energy,
                                             scattering_angle_cosine,
                                             trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 1.04998928662, 1e-12 );
  FRENSIE_CHECK_EQUAL( scattering_angle_cosine, 1.0 );
  FRENSIE_CHECK_EQUAL( trials, 12 );

  // sample epr14_distribution
  incoming_energy = 1e-3;
  epr14_distribution->sampleAndRecordTrials( incoming_energy,
                                             outgoing_energy,
                                             scattering_angle_cosine,
                                             trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 1e-3 - 9.32298E-06, 1e-12 );
  FRENSIE_CHECK_EQUAL( scattering_angle_cosine, 1.0 );
  FRENSIE_CHECK_EQUAL( trials, 13 );

  incoming_energy = 1.05;
  epr14_distribution->sampleAndRecordTrials( incoming_energy,
                                             outgoing_energy,
                                             scattering_angle_cosine,
                                             trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 1.0499892862612037, 1e-12 );
  FRENSIE_CHECK_EQUAL( scattering_angle_cosine, 1.0 );
  FRENSIE_CHECK_EQUAL( trials, 14 );
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
  // Create the distribution using the eprdata12 file
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

  MonteCarlo::AtomicExcitationElectronScatteringDistributionACEFactory::createAtomicExcitationDistribution(
                                                 *xss_data_extractor,
                                                 epr12_distribution );
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

  MonteCarlo::AtomicExcitationElectronScatteringDistributionACEFactory::createAtomicExcitationDistribution(
                                                 *xss_data_extractor,
                                                 epr14_distribution );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstAtomicExcitationElectronScatteringDistributionACEFactory.cpp
//---------------------------------------------------------------------------//
