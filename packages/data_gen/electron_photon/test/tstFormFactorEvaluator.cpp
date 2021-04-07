//---------------------------------------------------------------------------//
//!
//! \file   tstFormFactorEvaluator.cpp
//! \author Alex Robinson
//! \brief  The form factor squared evaluator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "DataGen_FormFactorEvaluator.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_InverseAngstromUnit.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<DataGen::FormFactorEvaluator> evaluator;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the form factor can be evaluated
FRENSIE_UNIT_TEST( FormFactorEvaluator, evaluateFormFactor )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( evaluator->evaluateFormFactor( 0.0 ),
                          82.0,
                          1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( evaluator->evaluateFormFactor( 1e8 ),
                          29.741,
                          1e-15 );

  FRENSIE_CHECK_SMALL( evaluator->evaluateFormFactor( 1e17 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the form factor evaluation wrapper can be generated
FRENSIE_UNIT_TEST( FormFactorEvaluator, getFormFactorEvaluationWrapper )
{
  std::function<double(double)> evaluation_wrapper =
    evaluator->getFormFactorEvaluationWrapper();

  FRENSIE_CHECK_FLOATING_EQUALITY( evaluation_wrapper( 0.0 ),
                          82.0,
                          1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( evaluation_wrapper( 1e8 ),
                          29.741,
                          1e-15 );

  FRENSIE_CHECK_SMALL( evaluation_wrapper( 1e17 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the form factor squared can be evaluated
FRENSIE_UNIT_TEST( FormFactorEvaluator, evaluateFormFactorSquared )
{
  FRENSIE_CHECK_FLOATING_EQUALITY( evaluator->evaluateFormFactorSquared( 0.0 ),
                          82.0*82.0,
                          1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( evaluator->evaluateFormFactorSquared( 1e8*1e8 ),
                          884.527080999999953,
                          1e-15 );

  FRENSIE_CHECK_SMALL( evaluator->evaluateFormFactorSquared( 1e17*1e17 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the form factor squared evaluation wrapper can be generated
FRENSIE_UNIT_TEST( FormFactorEvaluator,
                   getFormFactorSquaredEvaluationWrapper )
{
  std::function<double(double)> evaluation_wrapper =
    evaluator->getFormFactorSquaredEvaluationWrapper();

  FRENSIE_CHECK_FLOATING_EQUALITY( evaluation_wrapper( 0.0 ),
                          82.0*82.0,
                          1e-15 );

  FRENSIE_CHECK_FLOATING_EQUALITY( evaluation_wrapper( 1e8*1e8 ),
                          884.527080999999953,
                          1e-15 );

  FRENSIE_CHECK_SMALL( evaluation_wrapper( 1e17*1e17 ), 1e-15 );
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

    Utility::ArrayView<const double> jcohe_block =
      xss_data_extractor->extractJCOHEBlock();

    unsigned form_factor_size = jcohe_block.size()/3;

    std::vector<double> recoil_momentum( jcohe_block( 0, form_factor_size ) );

    std::vector<double> form_factor_values(
                         jcohe_block( 2*form_factor_size, form_factor_size ) );

    evaluator = DataGen::FormFactorEvaluator::createEvaluator<Utility::LinLin,Utility::Units::InverseAngstrom>(
                                                          recoil_momentum,
                                                          form_factor_values );
  }
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstFormFactorEvaluator.cpp
//---------------------------------------------------------------------------//
