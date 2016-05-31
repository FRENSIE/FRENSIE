//---------------------------------------------------------------------------//
//!
//! \file   tstStandardSoftElasticElectronDataGenerator.cpp
//! \author Luke Kersting
//! \brief  Standard soft elastic electron data generator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <stdio.h>

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
#include "DataGen_StandardSoftElasticElectronDataGenerator.hpp"
#include "Data_SoftElasticElectronVolatileDataContainer.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<Data::ElectronPhotonRelaxationDataContainer> 
  native_h_data, native_pb_data;
Teuchos::RCP<const DataGen::StandardSoftElasticElectronDataGenerator>
  data_generator_h, data_generator_pb;
/*
//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a data container can be populated
TEUCHOS_UNIT_TEST( StandardSoftElasticElectronDataGenerator,
                   populateSoftElasticDataContainer_h )
{
  Data::SoftElasticElectronVolatileDataContainer data_container;

  data_generator_h->populateSoftElasticDataContainer( data_container );

  std::vector<double> angular_grid = 
    data_container.getElasticAngularEnergyGrid();

  TEST_EQUALITY_CONST( data_container.getAtomicNumber(), 1 );
  TEST_EQUALITY_CONST( angular_grid[0], 1.0e-5 );
  TEST_EQUALITY_CONST( angular_grid[1], 1.0e-3 );
  TEST_EQUALITY_CONST( angular_grid[2], 2.0e-3 );
  TEST_EQUALITY_CONST( angular_grid[3], 4.0e-3 );
  TEST_EQUALITY_CONST( angular_grid[4], 8.0e-3 );
  TEST_EQUALITY_CONST( angular_grid[5], 1.6e-2 );
  TEST_EQUALITY_CONST( angular_grid[6], 3.2e-2 );
  TEST_EQUALITY_CONST( angular_grid[7], 6.4e-2 );
  TEST_EQUALITY_CONST( angular_grid[8], 1.28e-1 );
  TEST_EQUALITY_CONST( angular_grid[9], 2.56e-1 );
  TEST_EQUALITY_CONST( angular_grid[10], 1.0e+1 );
  TEST_EQUALITY_CONST( angular_grid[11], 2.13e+1 );
  TEST_EQUALITY_CONST( angular_grid[12], 3.25e+1 );
  TEST_EQUALITY_CONST( angular_grid[13], 4.38e+1 );
  TEST_EQUALITY_CONST( angular_grid[14], 6.63e+1 );
  TEST_EQUALITY_CONST( angular_grid[15], 1.0e+5 );
  TEST_EQUALITY_CONST( data_container.getNumberOfDiscreteAngles( 1 ), 1 );
  TEST_EQUALITY_CONST( 
    data_container.getSoftElasticDiscreteAngles(1).size(), 2 );
  TEST_EQUALITY_CONST( data_container.getSoftElasticWeights(1).size(), 2 );

  data_container.exportData( "test_h_epr.xml",
			     Utility::ArchivableObject::XML_ARCHIVE );
}

//---------------------------------------------------------------------------//
// Check that a data container can be populated
TEUCHOS_UNIT_TEST( StandardSoftElasticElectronDataGenerator,
                   populateSoftElasticDataContainer_pb )
{
  Data::SoftElasticElectronVolatileDataContainer data_container;

  data_generator_pb->populateSoftElasticDataContainer( data_container );

  std::vector<double> angular_grid = 
    data_container.getElasticAngularEnergyGrid();

  TEST_EQUALITY_CONST( data_container.getAtomicNumber(), 6 );
  TEST_EQUALITY_CONST( angular_grid[0], 1.0e-5 );
  TEST_EQUALITY_CONST( angular_grid[1], 1.0e-3 );
  TEST_EQUALITY_CONST( angular_grid[2], 2.0e-3 );
  TEST_EQUALITY_CONST( angular_grid[3], 4.0e-3 );
  TEST_EQUALITY_CONST( angular_grid[4], 8.0e-3 );
  TEST_EQUALITY_CONST( angular_grid[5], 1.6e-2 );
  TEST_EQUALITY_CONST( angular_grid[6], 3.2e-2 );
  TEST_EQUALITY_CONST( angular_grid[7], 6.4e-2 );
  TEST_EQUALITY_CONST( angular_grid[8], 1.28e-1 );
  TEST_EQUALITY_CONST( angular_grid[9], 2.56e-1 );
  TEST_EQUALITY_CONST( angular_grid[10], 1.0e+1 );
  TEST_EQUALITY_CONST( angular_grid[11], 3.25e+1 );
  TEST_EQUALITY_CONST( angular_grid[12], 5.5e+1 );
  TEST_EQUALITY_CONST( angular_grid[13], 1.0e+5 );
  TEST_EQUALITY_CONST( data_container.getNumberOfDiscreteAngles( 1 ), 1 );
  TEST_EQUALITY_CONST( 
    data_container.getSoftElasticDiscreteAngles(1).size(), 2 );
  TEST_EQUALITY_CONST( data_container.getSoftElasticWeights(1).size(), 2 );
		       
  data_container.exportData( "test_pb_epr.xml",
			     Utility::ArchivableObject::XML_ARCHIVE );
}
*/
//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_h_native_file_name, test_pb_native_file_name;
  
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_h_native_file",
		 &test_h_native_file_name,
		 "Test NATIVE file name" );
  clp.setOption( "test_pb_native_file",
		 &test_pb_native_file_name,
		 "Test NATIVE file name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }
  /*
  {
    // Create the native data file container
    native_h_data.reset( new Data::ElectronPhotonRelaxationDataContainer( 
						     test_h_native_file_name ) );

    data_generator_h.reset( 
		   new DataGen::StandardSoftElasticElectronDataGenerator(
				     native_h_data->getAtomicNumber(),
				     native_h_data,
				     0.00001,
				     20.0,
				     0.9,
                     3 ) );
  }
*/
  {
    // Create the native data file container
    native_pb_data.reset( new Data::ElectronPhotonRelaxationDataContainer( 
						     test_pb_native_file_name ) );

    data_generator_pb.reset( 
		   new DataGen::StandardSoftElasticElectronDataGenerator(
				     native_pb_data->getAtomicNumber(),
				     native_pb_data,
				     0.00001,
				     20.0,
				     0.9,
                     3 ) );
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
// end tstStandardSoftElasticElectronDataGenerator.cpp
//---------------------------------------------------------------------------//
