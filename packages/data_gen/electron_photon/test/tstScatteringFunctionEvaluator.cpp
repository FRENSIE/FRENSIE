//---------------------------------------------------------------------------//
//!
//! \file   tstScatteringFunctionEvaluator.cpp
//! \author Alex Robinson
//! \brief  The scattering function evaluator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "DataGen_ScatteringFunctionEvaluator.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_InverseAngstromUnit.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<DataGen::ScatteringFunctionEvaluator> evaluator;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the scattering function can be evaluated
FRENSIE_UNIT_TEST( ScatteringFunctionEvaluator, evaluateScatteringFunction )
{
  FRENSIE_CHECK_EQUAL( evaluator->evaluateScatteringFunction( 0.0 ), 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( evaluator->evaluateScatteringFunction( 1e9 ),
                          79.7669999999999959,
                          1e-15 );

  FRENSIE_CHECK_EQUAL( evaluator->evaluateScatteringFunction( 1e17 ), 82.0 );
  FRENSIE_CHECK_EQUAL( evaluator->evaluateScatteringFunction( 1e18 ), 82.0 );
}

//---------------------------------------------------------------------------//
// Check that the scattering function evaluation wrapper can be generated
FRENSIE_UNIT_TEST( ScatteringFunctionEvaluator,
                   getScatteringFunctionEvaluationWrapper )
{
  std::function<double(double)> evaluation_wrapper =
    evaluator->getScatteringFunctionEvaluationWrapper();

  FRENSIE_CHECK_EQUAL( evaluation_wrapper( 0.0 ), 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( evaluation_wrapper( 1e9 ),
                          79.7669999999999959,
                          1e-15 );

  FRENSIE_CHECK_EQUAL( evaluation_wrapper( 1e17 ), 82.0 );
  FRENSIE_CHECK_EQUAL( evaluation_wrapper( 1e18 ), 82.0 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_pb_ace_file_name;
unsigned test_pb_ace_file_start_line;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_pb_ace_file",
                                        test_pb_ace_file_name, "",
                                        "Test ACE file name" );

  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_pb_ace_file_start_line",
                                        test_pb_ace_file_start_line, 1,
                                        "Test ACE file start line" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
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

  Utility::ArrayView<const double> jince_block =
  xss_data_extractor->extractJINCEBlock();

  unsigned scatt_func_size = jince_block.size()/2;

  Utility::ArrayView<const double> recoil_momentum(
          jince_block( 0, scatt_func_size ) );

  Utility::ArrayView<const double> scattering_function(
      jince_block( scatt_func_size, scatt_func_size ) );

  evaluator = DataGen::ScatteringFunctionEvaluator::createEvaluator<Utility::LinLin,Utility::Units::InverseAngstrom>(
                                                        recoil_momentum,
                                                        scattering_function );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstScatteringFunctionEvaluator.cpp
//---------------------------------------------------------------------------//
