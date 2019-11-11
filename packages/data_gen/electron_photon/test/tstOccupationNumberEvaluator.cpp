//---------------------------------------------------------------------------//
//!
//! \file   tstOccupationNumberEvaluator.cpp
//! \author Alex Robinson
//! \brief  Occupation number evaluator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "DataGen_OccupationNumberEvaluator.hpp"
#include "MonteCarlo_ComptonProfileHelpers.hpp"
#include "MonteCarlo_ComptonProfileSubshellConverterFactory.hpp"
#include "Data_SubshellType.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_AtomicMomentumUnit.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<DataGen::OccupationNumberEvaluator>
  occupation_number_h_k;

std::shared_ptr<DataGen::OccupationNumberEvaluator>
  occupation_number_pb_k;

std::shared_ptr<DataGen::OccupationNumberEvaluator>
  occupation_number_pb_p3;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the Compton profile can be evaluated
FRENSIE_UNIT_TEST( OccupationNumberEvaluator, evaluateComptonProfile_h )
{
  double norm_constant =
    occupation_number_h_k->getComptonProfileNormConstant();

  double compton_profile_value =
    occupation_number_h_k->evaluateComptonProfile( -1.1 );

  FRENSIE_CHECK_EQUAL( compton_profile_value, 0.0 );

  compton_profile_value =
    occupation_number_h_k->evaluateComptonProfile( -1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( compton_profile_value,
                                  2.24058571809771121e-09,
                                  1e-12 );

  compton_profile_value =
    occupation_number_h_k->evaluateComptonProfile( -0.5837882030079395 );

  FRENSIE_CHECK_FLOATING_EQUALITY( compton_profile_value,
                                  4.59106809380969272e-09,
                                  1e-12 );

  compton_profile_value =
    occupation_number_h_k->evaluateComptonProfile( 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( compton_profile_value,
                          116.573683816875374,
                          1e-12 );

  compton_profile_value =
    occupation_number_h_k->evaluateComptonProfile( 0.5837882030079395 );

  FRENSIE_CHECK_FLOATING_EQUALITY( compton_profile_value,
                                  4.59106809380969272e-09,
                                  1e-12 );

  compton_profile_value =
    occupation_number_h_k->evaluateComptonProfile( 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( compton_profile_value,
                                  2.24058571809771121e-09,
                                  1e-12 );

  compton_profile_value =
    occupation_number_h_k->evaluateComptonProfile( 1.1 );

  FRENSIE_CHECK_EQUAL( compton_profile_value, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile can be evaluated
FRENSIE_UNIT_TEST( OccupationNumberEvaluator, evaluateComptonProfile_pb )
{
  double norm_constant =
    occupation_number_pb_k->getComptonProfileNormConstant();

  // K-shell
  double compton_profile_value =
    occupation_number_pb_k->evaluateComptonProfile( -1.1 );

  FRENSIE_CHECK_EQUAL( compton_profile_value, 0.0 );

  compton_profile_value =
    occupation_number_pb_k->evaluateComptonProfile( -1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( compton_profile_value,
                                  0.0506148938250740796,
                                  1e-12 );

  compton_profile_value =
    occupation_number_pb_k->evaluateComptonProfile( -0.5837882030079395 );

  FRENSIE_CHECK_FLOATING_EQUALITY( compton_profile_value,
                                  0.254045181704302958,
                                  1e-12 );

  compton_profile_value =
    occupation_number_pb_k->evaluateComptonProfile( 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( compton_profile_value,
                          1.2726198595992575,
                          1e-12 );

  compton_profile_value =
    occupation_number_pb_k->evaluateComptonProfile( 0.5837882030079395 );

  FRENSIE_CHECK_FLOATING_EQUALITY( compton_profile_value,
                                  0.254045181704303014,
                                  1e-12 );

  compton_profile_value =
    occupation_number_pb_k->evaluateComptonProfile( 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( compton_profile_value,
                                  0.0506148938250740796,
                                  1e-12 );

  compton_profile_value =
    occupation_number_pb_k->evaluateComptonProfile( 1.1 );

  FRENSIE_CHECK_EQUAL( compton_profile_value, 0.0 );

  // P3-shell
  norm_constant = occupation_number_pb_p3->getComptonProfileNormConstant();

  compton_profile_value =
    occupation_number_pb_p3->evaluateComptonProfile( -1.1 );

  FRENSIE_CHECK_EQUAL( compton_profile_value, 0.0 );

  compton_profile_value =
    occupation_number_pb_p3->evaluateComptonProfile( -1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( compton_profile_value,
                                  1.56879966373411526e-06,
                                  1e-12 );

  compton_profile_value =
    occupation_number_pb_p3->evaluateComptonProfile( -0.5837882030079395 );

  FRENSIE_CHECK_FLOATING_EQUALITY( compton_profile_value,
                                  4.3050501185942021e-05,
                                  1e-12 );

  compton_profile_value =
    occupation_number_pb_p3->evaluateComptonProfile( 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( compton_profile_value,
                          111.115981250606566,
                          1e-12 );

  compton_profile_value =
    occupation_number_pb_p3->evaluateComptonProfile( 0.5837882030079395 );

  FRENSIE_CHECK_FLOATING_EQUALITY( compton_profile_value,
                                  4.3050501185942021e-05,
                                  1e-12 );

  compton_profile_value =
    occupation_number_pb_p3->evaluateComptonProfile( 1.0 );
  std::cout.precision( 18 );
  std::cout << compton_profile_value << std::endl;
  FRENSIE_CHECK_FLOATING_EQUALITY( compton_profile_value,
                                  1.56879966373411526e-06,
                                  1e-12 );

  compton_profile_value =
    occupation_number_pb_p3->evaluateComptonProfile( 1.1 );

  FRENSIE_CHECK_EQUAL( compton_profile_value, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the occupation number can be evaluated
FRENSIE_UNIT_TEST( OccupationNumberEvaluator, evaluateOccupationNumber_h )
{
  double occupation_number =
    occupation_number_h_k->evaluateOccupationNumber( -1.1 );

  FRENSIE_CHECK_EQUAL( occupation_number, 0.0 );

  occupation_number =
    occupation_number_h_k->evaluateOccupationNumber( -1.0 );

  FRENSIE_CHECK_EQUAL( occupation_number, 0.0 );

  occupation_number =
    occupation_number_h_k->evaluateOccupationNumber( 0.0, 1e-5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( occupation_number, 0.5, 1e-6 );

  occupation_number =
    occupation_number_h_k->evaluateOccupationNumber( 1.0, 1e-4 );

  FRENSIE_CHECK_FLOATING_EQUALITY( occupation_number, 1.0, 1e-12 );

  occupation_number =
    occupation_number_h_k->evaluateOccupationNumber( 1.1, 1e-4 );

  FRENSIE_CHECK_FLOATING_EQUALITY( occupation_number, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the occupation number can be evaluated
FRENSIE_UNIT_TEST( OccupationNumberEvaluator, evaluateOccupationNumber_pb )
{
  // K-shell
  double occupation_number =
    occupation_number_pb_k->evaluateOccupationNumber( -1.1 );

  FRENSIE_CHECK_EQUAL( occupation_number, 0.0 );

  occupation_number =
    occupation_number_pb_k->evaluateOccupationNumber( -1.0 );

  FRENSIE_CHECK_EQUAL( occupation_number, 0.0 );

  occupation_number =
    occupation_number_pb_k->evaluateOccupationNumber( 0.0, 1e-6 );

  FRENSIE_CHECK_FLOATING_EQUALITY( occupation_number, 0.5, 1e-5 );

  occupation_number =
    occupation_number_pb_k->evaluateOccupationNumber( 1.0, 1e-4 );

  FRENSIE_CHECK_FLOATING_EQUALITY( occupation_number, 1.0, 1e-12 );

  occupation_number =
    occupation_number_pb_k->evaluateOccupationNumber( 1.1, 1e-4 );

  FRENSIE_CHECK_FLOATING_EQUALITY( occupation_number, 1.0, 1e-12 );

  // P3-shell
  occupation_number =
    occupation_number_pb_p3->evaluateOccupationNumber( -1.1 );

  FRENSIE_CHECK_EQUAL( occupation_number, 0.0 );

  occupation_number =
    occupation_number_pb_p3->evaluateOccupationNumber( -1.0 );

  FRENSIE_CHECK_EQUAL( occupation_number, 0.0 );

  occupation_number =
    occupation_number_pb_p3->evaluateOccupationNumber( 0.0, 1e-5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( occupation_number, 0.5, 1e-6 );

  occupation_number =
    occupation_number_pb_p3->evaluateOccupationNumber( 1.0, 1e-4 );

  FRENSIE_CHECK_FLOATING_EQUALITY( occupation_number, 1.0, 1e-12 );

  occupation_number =
    occupation_number_pb_p3->evaluateOccupationNumber( 1.1, 1e-4 );

  FRENSIE_CHECK_FLOATING_EQUALITY( occupation_number, 1.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_h_ace_file_name, test_pb_ace_file_name;
unsigned test_h_ace_file_start_line, test_pb_ace_file_start_line;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_h_ace_file",
                                        test_h_ace_file_name, "",
                                        "Test ACE file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_h_ace_file_start_line",
                                        test_h_ace_file_start_line, 1,
                                        "Test ACE file start line" );

  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_pb_ace_file",
                                        test_pb_ace_file_name, "",
                                        "Test ACE file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_pb_ace_file_start_line",
                                        test_pb_ace_file_start_line, 1,
                                        "Test ACE file start line" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  {
    // Create the file handler and data extractor for hydrogen
    std::shared_ptr<Data::ACEFileHandler> ace_file_handler(
                      new Data::ACEFileHandler( test_h_ace_file_name,
                                                "1000.12p",
                                                test_h_ace_file_start_line ) );

    std::shared_ptr<Data::XSSEPRDataExtractor> xss_data_extractor(
                                new Data::XSSEPRDataExtractor(
                                      ace_file_handler->getTableNXSArray(),
                                      ace_file_handler->getTableJXSArray(),
                                      ace_file_handler->getTableXSSArray() ) );

    // Create the Compton profile subshell converter
    std::shared_ptr<const MonteCarlo::ComptonProfileSubshellConverter> converter;

    MonteCarlo::ComptonProfileSubshellConverterFactory::createConverter(
                                   converter,
                                   xss_data_extractor->extractAtomicNumber() );

    unsigned k_shell_index = converter->convertSubshellToIndex(
                                                      Data::K_SUBSHELL );

    // Pull out the k-shell compton profile for hydrogen
    Utility::ArrayView<const double> lswd_block =
      xss_data_extractor->extractLSWDBlock();

    Utility::ArrayView<const double> swd_block =
      xss_data_extractor->extractSWDBlock();

    unsigned profile_index = lswd_block[k_shell_index]; // ignore interp param

    unsigned num_mom_vals = swd_block[profile_index];

    Utility::ArrayView<const double> raw_momentum_grid =
      swd_block( profile_index + 1, num_mom_vals );

    Utility::ArrayView<const double> raw_compton_profile =
      swd_block( profile_index + 1 + num_mom_vals, num_mom_vals );

    std::vector<double> full_momentum_grid, full_compton_profile;

    MonteCarlo::createFullProfileFromHalfProfile( raw_momentum_grid.begin(),
                                                  raw_momentum_grid.end(),
                                                  raw_compton_profile.begin(),
                                                  raw_compton_profile.end(),
                                                  full_momentum_grid,
                                                  full_compton_profile,
                                                  true );

    occupation_number_h_k =
      DataGen::OccupationNumberEvaluator::createEvaluator<Utility::LogLin,Utility::Units::AtomicMomentum>(
                                                          full_momentum_grid,
                                                          full_compton_profile,
                                                          1e-4 );
  }

  {
    // Create the file handler and data extractor for lead
    std::shared_ptr<Data::ACEFileHandler> ace_file_handler(
                     new Data::ACEFileHandler( test_pb_ace_file_name,
                                               "82000.12p",
                                               test_pb_ace_file_start_line ) );

    std::shared_ptr<Data::XSSEPRDataExtractor> xss_data_extractor(
                                new Data::XSSEPRDataExtractor(
                                      ace_file_handler->getTableNXSArray(),
                                      ace_file_handler->getTableJXSArray(),
                                      ace_file_handler->getTableXSSArray() ) );

    // Create the Compton profile subshell converter
    std::shared_ptr<const MonteCarlo::ComptonProfileSubshellConverter> converter;

    MonteCarlo::ComptonProfileSubshellConverterFactory::createConverter(
                                   converter,
                                   xss_data_extractor->extractAtomicNumber() );

    unsigned k_shell_index = converter->convertSubshellToIndex(
                                                      Data::K_SUBSHELL );

    unsigned p3_shell_index = converter->convertSubshellToIndex(
                                                     Data::P3_SUBSHELL );

    // Pull out the k-shell and p3-shell compton profiles for lead
    Utility::ArrayView<const double> lswd_block =
      xss_data_extractor->extractLSWDBlock();

    Utility::ArrayView<const double> swd_block =
      xss_data_extractor->extractSWDBlock();

    unsigned profile_index = lswd_block[k_shell_index]; // ignore interp param

    unsigned num_mom_vals = swd_block[profile_index];

    Utility::ArrayView<const double> raw_momentum_grid =
      swd_block( profile_index + 1, num_mom_vals );

    Utility::ArrayView<const double> raw_compton_profile =
      swd_block( profile_index + 1 + num_mom_vals, num_mom_vals );

    std::vector<double> full_momentum_grid, full_compton_profile;

    MonteCarlo::createFullProfileFromHalfProfile( raw_momentum_grid.begin(),
                                                  raw_momentum_grid.end(),
                                                  raw_compton_profile.begin(),
                                                  raw_compton_profile.end(),
                                                  full_momentum_grid,
                                                  full_compton_profile,
                                                  true );

    occupation_number_pb_k =
      DataGen::OccupationNumberEvaluator::createEvaluator<Utility::LogLin,Utility::Units::AtomicMomentum>(
                                                          full_momentum_grid,
                                                          full_compton_profile,
                                                          1e-4 );

    profile_index = lswd_block[p3_shell_index];

    num_mom_vals = swd_block[profile_index];

    raw_momentum_grid = swd_block( profile_index + 1, num_mom_vals );

    raw_compton_profile =
      swd_block( profile_index + 1 + num_mom_vals, num_mom_vals );

    MonteCarlo::createFullProfileFromHalfProfile( raw_momentum_grid.begin(),
                                                  raw_momentum_grid.end(),
                                                  raw_compton_profile.begin(),
                                                  raw_compton_profile.end(),
                                                  full_momentum_grid,
                                                  full_compton_profile,
                                                  true );

    occupation_number_pb_p3 =
      DataGen::OccupationNumberEvaluator::createEvaluator<Utility::LogLin,Utility::Units::AtomicMomentum>(
                                                          full_momentum_grid,
                                                          full_compton_profile,
                                                          1e-4 );
  }
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstOccupationNumberEvaluator.cpp
//---------------------------------------------------------------------------//
