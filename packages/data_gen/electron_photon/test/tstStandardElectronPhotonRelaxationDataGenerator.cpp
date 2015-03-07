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
#include "Data_ElectronPhotonRelaxationVolatileDataContainer.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<const DataGen::StandardElectronPhotonRelaxationDataGenerator>
  data_generator_h, data_generator_pb;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a data container can be populated
TEUCHOS_UNIT_TEST( StandardElectronPhotonRelaxationDataGenerator,
		   populateEPRDataContainer_h )
{
  Data::ElectronPhotonRelaxationVolatileDataContainer data_container;

  data_generator_h->populateEPRDataContainer( data_container );

  TEST_EQUALITY_CONST( data_container.getAtomicNumber(), 1 );
  TEST_EQUALITY_CONST( data_container.getSubshells().size(), 1 );
  TEST_ASSERT( data_container.getSubshells().count( 1 ) );
  TEST_EQUALITY_CONST( data_container.getSubshellOccupancy( 1 ), 1 );
  TEST_EQUALITY_CONST( data_container.getSubshellBindingEnergy( 1 ),
		       1.361000000000E-05 );
  TEST_ASSERT( !data_container.hasRelaxationData() );
  TEST_EQUALITY_CONST( data_container.getComptonProfileMomentumGrid(1).size(),
		       63 );
  TEST_EQUALITY_CONST( data_container.getComptonProfileMomentumGrid(1).front(),
		       -1.0 );
  TEST_EQUALITY_CONST( data_container.getComptonProfileMomentumGrid(1).back(),
		       1.0 );
  TEST_EQUALITY_CONST( data_container.getComptonProfile(1).size(), 63 );
  TEST_EQUALITY_CONST( data_container.getComptonProfile(1).front(),
		       2.22639294755138069e-09 );
  TEST_EQUALITY_CONST( data_container.getComptonProfile(1).back(),
		       2.22639294755138069e-09 );
  TEST_EQUALITY_CONST(data_container.getOccupationNumberMomentumGrid(1).size(),
		      409 );
  TEST_EQUALITY_CONST(
		     data_container.getOccupationNumberMomentumGrid(1).front(),
		     -1.00000000000000000e+00 );
  TEST_EQUALITY_CONST(data_container.getOccupationNumberMomentumGrid(1).back(),
		      1.00000000000000000e+00 );
  TEST_EQUALITY_CONST( data_container.getOccupationNumber(1).size(), 409 );
  TEST_EQUALITY_CONST( data_container.getOccupationNumber(1).front(), 
		       0.00000000000000000e+00 );
  TEST_EQUALITY_CONST( data_container.getOccupationNumber(1).back(),
		       1.00000000000000000e+00 );
  TEST_EQUALITY_CONST( 
	data_container.getWallerHartreeScatteringFunctionMomentumGrid().size(),
	94 );
  TEST_EQUALITY_CONST(
       data_container.getWallerHartreeScatteringFunctionMomentumGrid().front(),
       std::numeric_limits<double>::min() );
  TEST_EQUALITY_CONST(
	data_container.getWallerHartreeScatteringFunctionMomentumGrid().back(),
	1.00000000000000000e+17 );
  TEST_EQUALITY_CONST(
		    data_container.getWallerHartreeScatteringFunction().size(),
		    94 );
  TEST_EQUALITY_CONST( 
		   data_container.getWallerHartreeScatteringFunction().front(),
		   std::numeric_limits<double>::min() );
  TEST_EQUALITY_CONST(
		    data_container.getWallerHartreeScatteringFunction().back(),
		    1.00000000000000000e+00 );
  TEST_EQUALITY_CONST( 
	  data_container.getWallerHartreeAtomicFormFactorMomentumGrid().size(),
	  90 );
  TEST_EQUALITY_CONST(
	 data_container.getWallerHartreeAtomicFormFactorMomentumGrid().front(),
	 std::numeric_limits<double>::min() );
  TEST_EQUALITY_CONST(
	  data_container.getWallerHartreeAtomicFormFactorMomentumGrid().back(),
	  1.00000000000000000e+17 );
  TEST_EQUALITY_CONST(data_container.getWallerHartreeAtomicFormFactor().size(),
		      90 );
  TEST_EQUALITY_CONST(
		     data_container.getWallerHartreeAtomicFormFactor().front(),
		     1.00000000000000000e+00 );
  TEST_EQUALITY_CONST(data_container.getWallerHartreeAtomicFormFactor().back(),
		      8.18290000000000004e-39 );
  TEST_EQUALITY_CONST( data_container.getPhotonEnergyGrid().size(), 727 );
  TEST_EQUALITY_CONST( data_container.getPhotonEnergyGrid().front(),
		       1.00000000000000002e-03 );
  TEST_EQUALITY_CONST( data_container.getPhotonEnergyGrid().back(), 
		       2.00000000000000000e+01 );
  TEST_EQUALITY_CONST( data_container.getAveragePhotonHeatingNumbers().size(), 
		       727 );
  TEST_EQUALITY_CONST( data_container.getAveragePhotonHeatingNumbers().front(),
		       9.44850385307779940e-04 );
  TEST_EQUALITY_CONST( data_container.getAveragePhotonHeatingNumbers().back(),
		       1.52602263568998424e+01 );
  TEST_EQUALITY_CONST( 
		data_container.getWallerHartreeIncoherentCrossSection().size(),
		727 );
  TEST_EQUALITY_CONST(
	       data_container.getWallerHartreeIncoherentCrossSection().front(),
	       8.43429999999524560e-02 );
  TEST_EQUALITY_CONST(
	       data_container.getWallerHartreeIncoherentCrossSection().back(),
	       3.02353826681303964e-02 );
  TEST_EQUALITY_CONST(
   data_container.getWallerHartreeIncoherentCrossSectionThresholdEnergyIndex(),
   0 );
  TEST_EQUALITY_CONST(
		data_container.getImpulseApproxIncoherentCrossSection().size(),
		727 );
  TEST_EQUALITY_CONST(
	       data_container.getImpulseApproxIncoherentCrossSection().front(),
	       2.31128632327596700e-02 );
  TEST_EQUALITY_CONST(
	        data_container.getImpulseApproxIncoherentCrossSection().back(),
		3.02498575770965249e-02 );
  TEST_EQUALITY_CONST(
   data_container.getImpulseApproxIncoherentCrossSectionThresholdEnergyIndex(),
   0 );
  TEST_EQUALITY_CONST(
       data_container.getImpulseApproxSubshellIncoherentCrossSection(1).size(),
       727 );
  TEST_EQUALITY_CONST(
      data_container.getImpulseApproxSubshellIncoherentCrossSection(1).front(),
      2.31128632327596700e-02 );
  TEST_EQUALITY_CONST(
       data_container.getImpulseApproxSubshellIncoherentCrossSection(1).back(),
       3.02498575770965249e-02 );
  TEST_EQUALITY_CONST( data_container.getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex(1),
		       0 );
  TEST_EQUALITY_CONST( 
		  data_container.getWallerHartreeCoherentCrossSection().size(),
		  727 );
  TEST_EQUALITY_CONST(
		 data_container.getWallerHartreeCoherentCrossSection().front(),
		 5.81790484064093394e-01 );
  TEST_EQUALITY_CONST(
		 data_container.getWallerHartreeCoherentCrossSection().back(),
		 1.15654029975768264e-08 );
  TEST_EQUALITY_CONST(
     data_container.getWallerHartreeCoherentCrossSectionThresholdEnergyIndex(),
     0 );
  TEST_EQUALITY_CONST( data_container.getPairProductionCrossSection().size(),
		       296 );
  TEST_EQUALITY_CONST( data_container.getPairProductionCrossSection().front(),
		       1.00971567358274950e-10 );
  TEST_EQUALITY_CONST( data_container.getPairProductionCrossSection().back(),
		       5.65100000000240063e-03 );
  TEST_EQUALITY_CONST( 
	    data_container.getPairProductionCrossSectionThresholdEnergyIndex(),
	    431 );
  TEST_EQUALITY_CONST( data_container.getPhotoelectricCrossSection().size(),
		       727 );
  TEST_EQUALITY_CONST( data_container.getPhotoelectricCrossSection().front(),
		       1.14084154957847943e+01 );
  TEST_EQUALITY_CONST( data_container.getPhotoelectricCrossSection().back(),
		       4.05895811339709049e-11 );
  TEST_EQUALITY_CONST( 
	     data_container.getPhotoelectricCrossSectionThresholdEnergyIndex(),
	     0 );
  TEST_EQUALITY_CONST( 
		 data_container.getSubshellPhotoelectricCrossSection(1).size(),
		 727 );
  TEST_EQUALITY_CONST( 
		data_container.getSubshellPhotoelectricCrossSection(1).front(),
		1.14084154957847943e+01 );
  TEST_EQUALITY_CONST( 
		 data_container.getSubshellPhotoelectricCrossSection(1).back(),
		 4.05895811339709049e-11 );
  TEST_EQUALITY_CONST( 
    data_container.getSubshellPhotoelectricCrossSectionThresholdEnergyIndex(1),
    0 );
  TEST_EQUALITY_CONST( 
		     data_container.getWallerHartreeTotalCrossSection().size(),
		     727 );
  TEST_EQUALITY_CONST(
		    data_container.getWallerHartreeTotalCrossSection().front(),
		    1.20745489798488403e+01 );
  TEST_EQUALITY_CONST(
		     data_container.getWallerHartreeTotalCrossSection().back(),
		     3.58863942741253703e-02 );
  TEST_EQUALITY_CONST( 
		     data_container.getImpulseApproxTotalCrossSection().size(),
		     727 );
  TEST_EQUALITY_CONST(
		    data_container.getImpulseApproxTotalCrossSection().front(),
		    1.20133188430816471e+01 );
  TEST_EQUALITY_CONST(
		     data_container.getImpulseApproxTotalCrossSection().back(),
		     3.59008691830915022e-02 );

  data_container.exportData( "test_h_epr.xml",
			     Utility::ArchivableObject::XML_ARCHIVE );
  
  // Teuchos::Array<double> grid_wrapper( data_container.getWallerHartreeAtomicFormFactorMomentumGrid() );
  // Teuchos::Array<double> data_wrapper( data_container.getImpulseApproxTotalCrossSection() );
  // std::cout << grid_wrapper.size() << std::endl;
  // std::cout << grid_wrapper << std::endl;
  // std::cout << data_wrapper.size() << std::endl;
  // std::cout << data_wrapper << std::endl;
}

//---------------------------------------------------------------------------//
// Check that a data container can be populated
TEUCHOS_UNIT_TEST( StandardElectronPhotonRelaxationDataGenerator,
		   populateEPRDataContainer_pb )
{
  // Data::ElectronPhotonRelaxationVolatileDataContainer data_container;

  // data_generator_pb->populateEPRDataContainer( data_container );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_h_ace_file_name, test_h_ace_table_name;
  std::string test_pb_ace_file_name, test_pb_ace_table_name;
  
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_h_ace_file",
		 &test_h_ace_file_name,
		 "Test ACE file name" );
  clp.setOption( "test_h_ace_table",
		 &test_h_ace_table_name,
		 "Test ACE table name" );
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
				     20.0,
				     1e-4,
				     1e-4,
				     0.001,
				     1e-15,
				     1e-15 ) );
  }

  {
    // Create the file handler and data extractor for boron
    Teuchos::RCP<Data::ACEFileHandler> ace_file_handler(
			      new Data::ACEFileHandler( test_pb_ace_file_name,
							test_pb_ace_table_name,
							1u ) );

    Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor(
				new Data::XSSEPRDataExtractor( 
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );
    
    data_generator_pb.reset( 
		   new DataGen::StandardElectronPhotonRelaxationDataGenerator(
				     xss_data_extractor->extractAtomicNumber(),
				     xss_data_extractor,
				     0.001,
				     20.0,
				     1e-4,
				     1e-4,
				     0.001,
				     1e-14,
				     1e-14 ) );
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
// end tstStandardElectronPhotonRelaxationDataGenerator.cpp
//---------------------------------------------------------------------------//
