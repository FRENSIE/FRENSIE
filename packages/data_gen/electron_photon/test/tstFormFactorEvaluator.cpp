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

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "DataGen_FormFactorEvaluator.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_InverseAngstromUnit.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<DataGen::FormFactorEvaluator> evaluator;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the form factor can be evaluated
TEUCHOS_UNIT_TEST( FormFactorEvaluator, evaluateFormFactor )
{
  TEST_FLOATING_EQUALITY( evaluator->evaluateFormFactor( 0.0 ),
                          82.0,
                          1e-15 );
    
  TEST_FLOATING_EQUALITY( evaluator->evaluateFormFactor( 1e8 ),
                          29.741,
                          1e-15 );

  UTILITY_TEST_FLOATING_EQUALITY( evaluator->evaluateFormFactor( 1e17 ),
                                  0.0,
                                  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the form factor evaluation wrapper can be generated
TEUCHOS_UNIT_TEST( FormFactorEvaluator, getFormFactorEvaluationWrapper )
{
  std::function<double(double)> evaluation_wrapper =
    evaluator->getFormFactorEvaluationWrapper();

  TEST_FLOATING_EQUALITY( evaluation_wrapper( 0.0 ),
                          82.0,
                          1e-15 );
    
  TEST_FLOATING_EQUALITY( evaluation_wrapper( 1e8 ),
                          29.741,
                          1e-15 );

  UTILITY_TEST_FLOATING_EQUALITY( evaluation_wrapper( 1e17 ),
                                  0.0,
                                  1e-15 );
}
                   
//---------------------------------------------------------------------------//
// Check that the form factor squared can be evaluated
TEUCHOS_UNIT_TEST( FormFactorEvaluator, evaluateFormFactorSquared )
{
  TEST_FLOATING_EQUALITY( evaluator->evaluateFormFactorSquared( 0.0 ),
                          82.0*82.0,
                          1e-15 );
    
  TEST_FLOATING_EQUALITY( evaluator->evaluateFormFactorSquared( 1e8*1e8 ),
                          884.527080999999953,
                          1e-15 );

  TEST_FLOATING_EQUALITY( evaluator->evaluateFormFactorSquared( 1e17*1e17 ),
                          0.0,
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the form factor squared evaluation wrapper can be generated
TEUCHOS_UNIT_TEST( FormFactorEvaluator,
                   getFormFactorSquaredEvaluationWrapper )
{
  std::function<double(double)> evaluation_wrapper =
    evaluator->getFormFactorSquaredEvalutionWrapper();
  
  TEST_FLOATING_EQUALITY( evaluation_wrapper( 0.0 ),
                          82.0*82.0,
                          1e-15 );
    
  TEST_FLOATING_EQUALITY( evaluation_wrapper( 1e8*1e8 ),
                          884.527080999999953,
                          1e-15 );

  TEST_FLOATING_EQUALITY( evaluation_wrapper( 1e17*1e17 ),
                          0.0,
                          1e-15 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_pb_ace_file_name, test_pb_ace_table_name;

  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_pb_ace_file",
		 &test_pb_ace_file_name,
		 "Test ACE file name" );
  clp.setOption( "test_pb_ace_table",
		 &test_pb_ace_table_name,
		 "Test ACE table name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out =
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return =
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  {
    // Create the file handler and data extractor for lead
    std::shared_ptr<Data::ACEFileHandler> ace_file_handler(
			      new Data::ACEFileHandler( test_pb_ace_file_name,
							test_pb_ace_table_name,
							1u ) );

    std::shared_ptr<Data::XSSEPRDataExtractor> xss_data_extractor(
				new Data::XSSEPRDataExtractor(
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );

    Teuchos::ArrayView<const double> jcohe_block =
      xss_data_extractor->extractJCOHEBlock();

    unsigned form_factor_size = jcohe_block.size()/3;

    Teuchos::Array<double> recoil_momentum(
					  jcohe_block( 0, form_factor_size ) );

    Teuchos::Array<double> form_factor_values(
			 jcohe_block( 2*form_factor_size, form_factor_size ) );

    evaluator = DataGen::FormFactorEvaluator::createEvaluator<Utility::LinLin,Utility::Units::InverseAngstrom>(
                                                          recoil_momentum,
                                                          form_factor_values );
  }

  // Run the unit tests
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  const bool success = Teuchos::UnitTestRepository::runUnitTests( *out );

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstFormFactorEvaluator.cpp
//---------------------------------------------------------------------------//
