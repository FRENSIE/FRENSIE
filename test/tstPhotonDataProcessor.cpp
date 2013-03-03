//---------------------------------------------------------------------------//
// \file   tstPhotonDataProcessor.cpp
// \author Alex Robinson
// \brief  PhotonDataProcessor class unit tests.
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_TwoDArray.hpp>

// FACEMC Includes
#include "PhotonDataProcessor.hpp"
#include "HDF5FileHandler.hpp"
#include "Tuple.hpp"
#include "HDF5DataFileNames.hpp"
#include "TestingHelperFunctions.hpp"

//---------------------------------------------------------------------------//
// Test File Names.
//---------------------------------------------------------------------------//
#define EPDL_TEST_FILE "test_epdl_file.txt"
#define EADL_TEST_FILE "test_eadl_file.txt"
#define COMPTON_TEST_FILE_PREFIX "test_compton_profile-"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestingPhotonDataProcessor : public FACEMC::PhotonDataProcessor
{
public:
  TestingPhotonDataProcessor( const std::string epdl_file_name,
			      const std::string eadl_file_name,
			      const std::string compton_file_prefix,
			      const std::string output_directory,
			      const double energy_min,
			      const double energy_max)
    : FACEMC::PhotonDataProcessor( epdl_file_name,
				   eadl_file_name,
				   compton_file_prefix,
				   output_directory,
				   energy_min,
				   energy_max )
  { /* ... */ }

  virtual ~TestingPhotonDataProcessor()
  { /* ... */ }

  using FACEMC::PhotonDataProcessor::processEPDLFile;
  using FACEMC::PhotonDataProcessor::processEADLFile;
  using FACEMC::PhotonDataProcessor::processComptonFiles;
};

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the PhotonDataProcessor can process an EPDL data file
TEUCHOS_UNIT_TEST( PhotonDataProcessor, process_epdl_file_test )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX,
						    "",
						    1e-7,
						    1e5 );

  // This member function will throw an exception and exit if an error occurs
  // so no TEST macro is needed.
  photon_data_processor.processEPDLFile();

}

//---------------------------------------------------------------------------//
// Check that the PhotonDataProcessor can process an EADL data file
TEUCHOS_UNIT_TEST( PhotonDataProcessor, process_eadl_file_test )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX,
						    "",
						    1e-7,
						    1e5 );

  // This member function will throw an exception and exit if an error occurs
  // so no TEST macro is needed.
  photon_data_processor.processEADLFile();

}

//---------------------------------------------------------------------------//
// Check that the PhotonDataProcessor can process a Compton Profile data file
TEUCHOS_UNIT_TEST( PhotonDataProcessor, process_compton_file_test )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX,
						    "",
						    1e-7,
						    1e5 );

  // This member function will throw an exception and exit if an error occurs
  // so no TEST macro is needed.
  photon_data_processor.processComptonFiles( 5, 6 );

}


//---------------------------------------------------------------------------//
// end tstPhotonDataProcessor.cpp
//---------------------------------------------------------------------------//
