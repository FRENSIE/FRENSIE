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

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "DataGen_ScatteringFunctionEvaluator.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_InverseAngstromUnit.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<DataGen::ScatteringFunctionEvaluator> evaluator;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the scattering function can be evaluated
TEUCHOS_UNIT_TEST( ScatteringFunctionEvaluator, evaluateScatteringFunction )
{
  TEST_EQUALITY_CONST( evaluator->evaluateScatteringFunction( 0.0 ), 0.0 );

  TEST_FLOATING_EQUALITY( evaluator->evaluateScatteringFunction( 1e9 ),
                          79.7669999999999959, 
                          1e-15 );
    
  TEST_EQUALITY_CONST( evaluator->evaluateScatteringFunction( 1e17 ), 82.0 );
  TEST_EQUALITY_CONST( evaluator->evaluateScatteringFunction( 1e18 ), 82.0 );
}

//---------------------------------------------------------------------------//
// Check that the scattering function evaluation wrapper can be generated
TEUCHOS_UNIT_TEST( ScatteringFunctionEvaluator,
                   getScatteringFunctionEvaluationWrapper )
{
  std::function<double(double)> evaluation_wrapper =
    evaluator->getScatteringFunctionEvaluationWrapper();
  
  TEST_EQUALITY_CONST( evaluation_wrapper( 0.0 ), 0.0 );

  TEST_FLOATING_EQUALITY( evaluation_wrapper( 1e9 ),
                          79.7669999999999959, 
                          1e-15 );
    
  TEST_EQUALITY_CONST( evaluation_wrapper( 1e17 ), 82.0 );
  TEST_EQUALITY_CONST( evaluation_wrapper( 1e18 ), 82.0 );
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

    Teuchos::ArrayView<const double> jince_block =
    xss_data_extractor->extractJINCEBlock();

    unsigned scatt_func_size = jince_block.size()/2;

    Teuchos::ArrayView<const double> recoil_momentum(
					 jince_block( 0, scatt_func_size ) );

    Teuchos::ArrayView<const double> scattering_function(
			 jince_block( scatt_func_size, scatt_func_size ) );
    
    evaluator = DataGen::ScatteringFunctionEvaluator::createEvaluator<Utility::LinLin,Utility::Units::InverseAngstrom>(
                                                         recoil_momentum,
                                                         scattering_function );
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
// end tstScatteringFunctionEvaluator.cpp
//---------------------------------------------------------------------------//
