//---------------------------------------------------------------------------//
//!
//! \file   tstStandardElectronPhotonRelaxationDataGenerator.cpp
//! \author Alex Robinson
//! \brief  Standard electron-photon-relaxation data generator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/unordered_map.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "DataGen_StandardElectronPhotonRelaxationDataGenerator.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<const DataGen::StandardElectronPhotonRelaxationDataGenerator>
  data_generator_h, data_generator_b;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a data container can be populated
TEUCHOS_UNIT_TEST( StandardElectronPhotonRelaxationDataGenerator,
		   populateEPRDataContainer )
{
  
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_h_ace_file_name, test_h_ace_table_name;
  std::string test_b_ace_file_name, test_b_ace_table_name;
  
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_h_ace_file",
		 &test_h_ace_file_name,
		 "Test ACE file name" );
  clp.setOption( "test_h_ace_table",
		 &test_h_ace_table_name,
		 "Test ACE table name" );
  clp.setOption( "test_b_ace_file",
		 &test_b_ace_file_name,
		 "Test ACE file name" );
  clp.setOption( "test_b_ace_table",
		 &test_b_ace_table_name,
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
    // Create the file handler and data extractor for hydrogen
    Teuchos::RCP<Data::ACEFileHandler> ace_file_handler(
			       new Data::ACEFileHandler( test_h_ace_file_name,
							 test_h_ace_table_name,
							 1u ) );

    Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor(
				new Data::XSSEPRDataExtractor( 
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );

    data_generator_h.reset( 
		   new DataGen::StandardElectronPhotonRelaxationDataGenerator(
				     xss_data_extractor->extractAtomicNumber(),
				     xss_data_extractor,
				     0.001,
				     1e-4,
				     1e-4,
				     0.001 ) );
  }

  {
    // Create the file handler and data extractor for boron
    Teuchos::RCP<Data::ACEFileHandler> ace_file_handler(
			       new Data::ACEFileHandler( test_b_ace_file_name,
							 test_b_ace_table_name,
							 1u ) );

    Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor(
				new Data::XSSEPRDataExtractor( 
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );
    
    data_generator_b.reset( 
		   new DataGen::StandardElectronPhotonRelaxationDataGenerator(
				     xss_data_extractor->extractAtomicNumber(),
				     xss_data_extractor,
				     0.001,
				     1e-4,
				     1e-4,
				     0.001 ) );
  }
}

//---------------------------------------------------------------------------//
// end tstStandardElectronPhotonRelaxationDataGenerator.cpp
//---------------------------------------------------------------------------//
