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
  epr12_distribution;

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
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_ace12_file_name;
unsigned test_ace12_file_start_line;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_ace12_file",
                                        test_ace12_file_name, "",
                                        "Test ACE12 file name" );

  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_ace12_file_start_line",
                                        test_ace12_file_start_line, 1,
                                        "Test ACE12 file start line" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create a file handler and data extractor
  std::unique_ptr<Data::ACEFileHandler> ace_file_handler(
        new Data::ACEFileHandler( test_ace12_file_name,
                                  "82000.12p",
                                  test_ace12_file_start_line ) );
  
  std::unique_ptr<Data::XSSEPRDataExtractor> xss_data_extractor(
        new Data::XSSEPRDataExtractor( ace_file_handler->getTableNXSArray(),
                                       ace_file_handler->getTableJXSArray(),
                                       ace_file_handler->getTableXSSArray() ) );

  MonteCarlo::AtomicExcitationElectronScatteringDistributionACEFactory::createAtomicExcitationDistribution(
                                                 *xss_data_extractor,
                                                 epr12_distribution );
  
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstAtomicExcitationElectronScatteringDistributionACEFactory.cpp
//---------------------------------------------------------------------------//
