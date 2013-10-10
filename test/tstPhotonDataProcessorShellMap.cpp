//---------------------------------------------------------------------------//
// \file   tstPhotonDataProcessorShellMap.cpp
// \author Alex Robinson
// \brief  PhotonDataProcessor class electron shell map unit tests.
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_TwoDArray.hpp>

// FACEMC Includes
#include "FACEMC_UnitTestHarnessExtensions.hpp"
#include "PhotonDataProcessor.hpp"
#include "HDF5FileHandler.hpp"
#include "Tuple.hpp"
#include "HDF5DataFileNames.hpp"

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
			      const double energy_min = MIN_ENERGY_DEFAULT,
			      const double energy_max = MAX_ENERGY_DEFAULT)
    : FACEMC::PhotonDataProcessor( epdl_file_name,
				   eadl_file_name,
				   compton_file_prefix,
				   output_directory,
				   energy_min,
				   energy_max )
  { /* ... */ }

  virtual ~TestingPhotonDataProcessor()
  { /* ... */ }

  using FACEMC::PhotonDataProcessor::createShellIndexMap;
  
};

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=1
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_1 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX,
						    "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 1,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=2
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_2 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 2,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=3
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_3 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 3,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=4
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_4 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 4,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=5
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_5 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 5,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 2;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=6
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_6 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 6,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 2;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=7
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_7 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 7,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 2;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=8
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_8 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 8,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 2;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=9
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_9 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 9,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 2;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=10
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_10 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 10,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 2;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=11
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_11 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 11,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 3;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=12
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_12 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 12,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 3;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=13
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_13 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 13,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 4;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=14
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_14 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 14,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 4;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=15
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_15 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 15,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 4;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=16
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_16 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 16,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 4;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=17
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_17 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 17,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 4;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=18
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_18 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 18,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 4;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=19
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_19 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 19,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 5;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=20
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_20 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 20,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 5;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=21
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_21 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 21,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 6;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=22
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_22 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 22,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 6;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=23
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_23 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 23,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 6;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=24
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_24 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 24,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 6;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=25
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_25 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 25,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 6;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=26
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_26 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 26,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 6;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=27
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_27 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 27,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 6;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=28
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_28 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 28,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 6;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=29
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_29 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 29,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 6;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=30
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_30 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 30,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 6;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=31
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_31 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 31,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 7;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=32
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_32 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 32,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 7;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=34
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_34 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 34,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 7;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=35
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_35 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 35,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 7;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=36
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_36 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 36,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=37
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_37 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 37,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 12;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=38
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_38 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 38,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 12;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=39
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_39 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 39,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 13;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=40
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_40 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 40,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 13;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=41
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_41 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 41,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 13;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=42
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_42 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 42,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 14;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=43
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_43 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 43,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 14;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=44
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_44 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 44,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 14;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=45
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_45 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 45,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 14;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=46
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_46 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 46,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=47
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_47 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 47,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 14;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=48
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_48 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 48,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 14;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=49
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_49 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 49,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 15;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=50
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_50 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 50,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 15;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=51
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_51 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 51,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 16;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=52
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_52 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 52,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 16;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=53
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_53 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 53,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 16;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=54
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_54 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 54,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 16;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=55
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_55 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 55,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 41;
  data_point.second = 17;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=56
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_56 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 56,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 41;
  data_point.second = 17;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=57
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_57 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 57,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 32;
  data_point.second = 17;
  map_true.push_back( data_point );

  data_point.first = 33;
  data_point.second = 17;
  map_true.push_back( data_point );

  data_point.first = 41;
  data_point.second = 18;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=58
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_58 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 58,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 24;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 25;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 17;
  map_true.push_back( data_point );

  data_point.first = 41;
  data_point.second = 19;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=59
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_59 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 59,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 24;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 25;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 17;
  map_true.push_back( data_point );

  data_point.first = 41;
  data_point.second = 18;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=60
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_60 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 60,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 24;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 25;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 17;
  map_true.push_back( data_point );

  data_point.first = 41;
  data_point.second = 18;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=61
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_61 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 61,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 24;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 25;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 17;
  map_true.push_back( data_point );

  data_point.first = 41;
  data_point.second = 18;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=62
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_62 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 62,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 24;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 25;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 17;
  map_true.push_back( data_point );

  data_point.first = 41;
  data_point.second = 18;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=63
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_63 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 63,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 24;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 25;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 17;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 18;
  map_true.push_back( data_point );

  data_point.first = 41;
  data_point.second = 19;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=64
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_64 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 64,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 24;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 25;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 17;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 18;
  map_true.push_back( data_point );

  data_point.first = 32;
  data_point.second = 19;
  map_true.push_back( data_point );

  data_point.first = 33;
  data_point.second = 19;
  map_true.push_back( data_point );

  data_point.first = 41;
  data_point.second = 20;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=65
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_65 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 65,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 24;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 25;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 17;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 18;
  map_true.push_back( data_point );

  data_point.first = 41;
  data_point.second = 19;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=66
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_66 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 66,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 24;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 25;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 17;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 18;
  map_true.push_back( data_point );

  data_point.first = 41;
  data_point.second = 19;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=67
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_67 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 67,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 24;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 25;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 17;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 18;
  map_true.push_back( data_point );

  data_point.first = 41;
  data_point.second = 19;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=68
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_68 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 68,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 24;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 25;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 17;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 18;
  map_true.push_back( data_point );

  data_point.first = 41;
  data_point.second = 19;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=69
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_69 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 69,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 24;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 25;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 17;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 18;
  map_true.push_back( data_point );

  data_point.first = 41;
  data_point.second = 19;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=70
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_70 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 70,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 24;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 25;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 17;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 18;
  map_true.push_back( data_point );

  data_point.first = 41;
  data_point.second = 19;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=71
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_71 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 71,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 24;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 25;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 17;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 18;
  map_true.push_back( data_point );

  data_point.first = 32;
  data_point.second = 19;
  map_true.push_back( data_point );

  data_point.first = 33;
  data_point.second = 19;
  map_true.push_back( data_point );

  data_point.first = 41;
  data_point.second = 20;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=72
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_72 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 72,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 24;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 25;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 17;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 18;
  map_true.push_back( data_point );

  data_point.first = 32;
  data_point.second = 19;
  map_true.push_back( data_point );

  data_point.first = 33;
  data_point.second = 19;
  map_true.push_back( data_point );

  data_point.first = 41;
  data_point.second = 20;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=73
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_73 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 73,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 24;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 25;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 17;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 18;
  map_true.push_back( data_point );

  data_point.first = 32;
  data_point.second = 19;
  map_true.push_back( data_point );

  data_point.first = 33;
  data_point.second = 19;
  map_true.push_back( data_point );

  data_point.first = 41;
  data_point.second = 20;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=74
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_74 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 74,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 24;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 25;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 17;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 18;
  map_true.push_back( data_point );

  data_point.first = 32;
  data_point.second = 19;
  map_true.push_back( data_point );

  data_point.first = 33;
  data_point.second = 19;
  map_true.push_back( data_point );

  data_point.first = 41;
  data_point.second = 20;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=75
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_75 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 75,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 24;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 25;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 17;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 18;
  map_true.push_back( data_point );

  data_point.first = 32;
  data_point.second = 19;
  map_true.push_back( data_point );

  data_point.first = 33;
  data_point.second = 20;
  map_true.push_back( data_point );

  data_point.first = 41;
  data_point.second = 21;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=76
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_76 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 76,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 24;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 25;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 17;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 18;
  map_true.push_back( data_point );

  data_point.first = 32;
  data_point.second = 19;
  map_true.push_back( data_point );

  data_point.first = 33;
  data_point.second = 20;
  map_true.push_back( data_point );

  data_point.first = 41;
  data_point.second = 21;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=77
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_77 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 77,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 24;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 25;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 17;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 18;
  map_true.push_back( data_point );

  data_point.first = 32;
  data_point.second = 19;
  map_true.push_back( data_point );

  data_point.first = 33;
  data_point.second = 20;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=78
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_78 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 78,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 24;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 25;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 17;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 18;
  map_true.push_back( data_point );

  data_point.first = 32;
  data_point.second = 19;
  map_true.push_back( data_point );

  data_point.first = 33;
  data_point.second = 20;
  map_true.push_back( data_point );

  data_point.first = 41;
  data_point.second = 21;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=79
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_79 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 79,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 24;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 25;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 17;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 18;
  map_true.push_back( data_point );

  data_point.first = 32;
  data_point.second = 19;
  map_true.push_back( data_point );

  data_point.first = 33;
  data_point.second = 20;
  map_true.push_back( data_point );

  data_point.first = 41;
  data_point.second = 21;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=80
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_80 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 80,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 24;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 25;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 17;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 18;
  map_true.push_back( data_point );

  data_point.first = 32;
  data_point.second = 19;
  map_true.push_back( data_point );

  data_point.first = 33;
  data_point.second = 20;
  map_true.push_back( data_point );

  data_point.first = 41;
  data_point.second = 21;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=81
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_81 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 81,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 24;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 25;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 17;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 18;
  map_true.push_back( data_point );

  data_point.first = 32;
  data_point.second = 19;
  map_true.push_back( data_point );

  data_point.first = 33;
  data_point.second = 20;
  map_true.push_back( data_point );

  data_point.first = 41;
  data_point.second = 21;
  map_true.push_back( data_point );

  data_point.first = 43;
  data_point.second = 22;
  map_true.push_back( data_point );

  data_point.first = 44;
  data_point.second = 22;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=82
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_82 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 82,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 24;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 25;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 17;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 18;
  map_true.push_back( data_point );

  data_point.first = 32;
  data_point.second = 19;
  map_true.push_back( data_point );

  data_point.first = 33;
  data_point.second = 20;
  map_true.push_back( data_point );

  data_point.first = 41;
  data_point.second = 21;
  map_true.push_back( data_point );

  data_point.first = 43;
  data_point.second = 22;
  map_true.push_back( data_point );

  data_point.first = 44;
  data_point.second = 22;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=83
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_83 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 83,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 24;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 25;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 17;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 18;
  map_true.push_back( data_point );

  data_point.first = 32;
  data_point.second = 19;
  map_true.push_back( data_point );

  data_point.first = 33;
  data_point.second = 20;
  map_true.push_back( data_point );

  data_point.first = 41;
  data_point.second = 21;
  map_true.push_back( data_point );

  data_point.first = 43;
  data_point.second = 22;
  map_true.push_back( data_point );

  data_point.first = 44;
  data_point.second = 23;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=84
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_84 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 84,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 24;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 25;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 17;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 18;
  map_true.push_back( data_point );

  data_point.first = 32;
  data_point.second = 19;
  map_true.push_back( data_point );

  data_point.first = 33;
  data_point.second = 20;
  map_true.push_back( data_point );

  data_point.first = 41;
  data_point.second = 21;
  map_true.push_back( data_point );

  data_point.first = 43;
  data_point.second = 22;
  map_true.push_back( data_point );

  data_point.first = 44;
  data_point.second = 23;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=85
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_85 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 85,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 24;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 25;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 17;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 18;
  map_true.push_back( data_point );

  data_point.first = 32;
  data_point.second = 19;
  map_true.push_back( data_point );

  data_point.first = 33;
  data_point.second = 20;
  map_true.push_back( data_point );

  data_point.first = 41;
  data_point.second = 21;
  map_true.push_back( data_point );

  data_point.first = 43;
  data_point.second = 22;
  map_true.push_back( data_point );

  data_point.first = 44;
  data_point.second = 23;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=86
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_86 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 86,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 24;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 25;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 17;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 18;
  map_true.push_back( data_point );

  data_point.first = 32;
  data_point.second = 19;
  map_true.push_back( data_point );

  data_point.first = 33;
  data_point.second = 20;
  map_true.push_back( data_point );

  data_point.first = 41;
  data_point.second = 21;
  map_true.push_back( data_point );

  data_point.first = 43;
  data_point.second = 22;
  map_true.push_back( data_point );

  data_point.first = 44;
  data_point.second = 23;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=87
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_87 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 87,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 24;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 25;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 17;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 18;
  map_true.push_back( data_point );

  data_point.first = 32;
  data_point.second = 19;
  map_true.push_back( data_point );

  data_point.first = 33;
  data_point.second = 20;
  map_true.push_back( data_point );

  data_point.first = 41;
  data_point.second = 21;
  map_true.push_back( data_point );

  data_point.first = 43;
  data_point.second = 22;
  map_true.push_back( data_point );

  data_point.first = 44;
  data_point.second = 23;
  map_true.push_back( data_point );
  
  data_point.first = 58;
  data_point.second = 24;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=88
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_88 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 88,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 24;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 25;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 17;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 18;
  map_true.push_back( data_point );

  data_point.first = 32;
  data_point.second = 19;
  map_true.push_back( data_point );

  data_point.first = 33;
  data_point.second = 20;
  map_true.push_back( data_point );

  data_point.first = 41;
  data_point.second = 21;
  map_true.push_back( data_point );

  data_point.first = 43;
  data_point.second = 22;
  map_true.push_back( data_point );

  data_point.first = 44;
  data_point.second = 23;
  map_true.push_back( data_point );
  
  data_point.first = 58;
  data_point.second = 24;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=89
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_89 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 89,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 24;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 25;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 17;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 18;
  map_true.push_back( data_point );

  data_point.first = 32;
  data_point.second = 19;
  map_true.push_back( data_point );

  data_point.first = 33;
  data_point.second = 20;
  map_true.push_back( data_point );

  data_point.first = 41;
  data_point.second = 21;
  map_true.push_back( data_point );

  data_point.first = 43;
  data_point.second = 22;
  map_true.push_back( data_point );

  data_point.first = 44;
  data_point.second = 23;
  map_true.push_back( data_point );

  data_point.first = 46;
  data_point.second = 24;
  map_true.push_back( data_point );

  data_point.first = 47;
  data_point.second = 24;
  map_true.push_back( data_point );
  
  data_point.first = 58;
  data_point.second = 25;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=90
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_90 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 90,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 24;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 25;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 17;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 18;
  map_true.push_back( data_point );

  data_point.first = 32;
  data_point.second = 19;
  map_true.push_back( data_point );

  data_point.first = 33;
  data_point.second = 20;
  map_true.push_back( data_point );

  data_point.first = 41;
  data_point.second = 21;
  map_true.push_back( data_point );

  data_point.first = 43;
  data_point.second = 22;
  map_true.push_back( data_point );

  data_point.first = 44;
  data_point.second = 23;
  map_true.push_back( data_point );

  data_point.first = 46;
  data_point.second = 24;
  map_true.push_back( data_point );

  data_point.first = 47;
  data_point.second = 24;
  map_true.push_back( data_point );
  
  data_point.first = 58;
  data_point.second = 25;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=91
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_91 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 91,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 24;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 25;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 17;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 18;
  map_true.push_back( data_point );

  data_point.first = 32;
  data_point.second = 19;
  map_true.push_back( data_point );

  data_point.first = 33;
  data_point.second = 20;
  map_true.push_back( data_point );

  data_point.first = 35;
  data_point.second = 21;
  map_true.push_back( data_point );

  data_point.first = 36;
  data_point.second = 21;
  map_true.push_back( data_point );

  data_point.first = 41;
  data_point.second = 22;
  map_true.push_back( data_point );

  data_point.first = 43;
  data_point.second = 23;
  map_true.push_back( data_point );

  data_point.first = 44;
  data_point.second = 24;
  map_true.push_back( data_point );

  data_point.first = 46;
  data_point.second = 25;
  map_true.push_back( data_point );

  data_point.first = 47;
  data_point.second = 25;
  map_true.push_back( data_point );
  
  data_point.first = 58;
  data_point.second = 26;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=92
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_92 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 92,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 24;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 25;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 17;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 18;
  map_true.push_back( data_point );

  data_point.first = 32;
  data_point.second = 19;
  map_true.push_back( data_point );

  data_point.first = 33;
  data_point.second = 20;
  map_true.push_back( data_point );

  data_point.first = 35;
  data_point.second = 21;
  map_true.push_back( data_point );

  data_point.first = 36;
  data_point.second = 21;
  map_true.push_back( data_point );

  data_point.first = 41;
  data_point.second = 22;
  map_true.push_back( data_point );

  data_point.first = 43;
  data_point.second = 23;
  map_true.push_back( data_point );

  data_point.first = 44;
  data_point.second = 24;
  map_true.push_back( data_point );

  data_point.first = 46;
  data_point.second = 25;
  map_true.push_back( data_point );

  data_point.first = 47;
  data_point.second = 25;
  map_true.push_back( data_point );
  
  data_point.first = 58;
  data_point.second = 26;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=93
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_93 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 93,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 24;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 25;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 17;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 18;
  map_true.push_back( data_point );

  data_point.first = 32;
  data_point.second = 19;
  map_true.push_back( data_point );

  data_point.first = 33;
  data_point.second = 20;
  map_true.push_back( data_point );

  data_point.first = 35;
  data_point.second = 21;
  map_true.push_back( data_point );

  data_point.first = 36;
  data_point.second = 21;
  map_true.push_back( data_point );

  data_point.first = 41;
  data_point.second = 22;
  map_true.push_back( data_point );

  data_point.first = 43;
  data_point.second = 23;
  map_true.push_back( data_point );

  data_point.first = 44;
  data_point.second = 24;
  map_true.push_back( data_point );

  data_point.first = 46;
  data_point.second = 25;
  map_true.push_back( data_point );

  data_point.first = 47;
  data_point.second = 25;
  map_true.push_back( data_point );
  
  data_point.first = 58;
  data_point.second = 26;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=94
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_94 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 94,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 24;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 25;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 17;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 18;
  map_true.push_back( data_point );

  data_point.first = 32;
  data_point.second = 19;
  map_true.push_back( data_point );

  data_point.first = 33;
  data_point.second = 20;
  map_true.push_back( data_point );

  data_point.first = 35;
  data_point.second = 21;
  map_true.push_back( data_point );

  data_point.first = 36;
  data_point.second = 21;
  map_true.push_back( data_point );

  data_point.first = 41;
  data_point.second = 22;
  map_true.push_back( data_point );

  data_point.first = 43;
  data_point.second = 23;
  map_true.push_back( data_point );

  data_point.first = 44;
  data_point.second = 24;
  map_true.push_back( data_point );
  
  data_point.first = 58;
  data_point.second = 25;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=95
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_95 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 95,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 24;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 25;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 17;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 18;
  map_true.push_back( data_point );

  data_point.first = 32;
  data_point.second = 19;
  map_true.push_back( data_point );

  data_point.first = 33;
  data_point.second = 20;
  map_true.push_back( data_point );

  data_point.first = 35;
  data_point.second = 21;
  map_true.push_back( data_point );

  data_point.first = 36;
  data_point.second = 22;
  map_true.push_back( data_point );

  data_point.first = 41;
  data_point.second = 23;
  map_true.push_back( data_point );

  data_point.first = 43;
  data_point.second = 24;
  map_true.push_back( data_point );

  data_point.first = 44;
  data_point.second = 25;
  map_true.push_back( data_point );
  
  data_point.first = 58;
  data_point.second = 26;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=96
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_96 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 96,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 24;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 25;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 17;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 18;
  map_true.push_back( data_point );

  data_point.first = 32;
  data_point.second = 19;
  map_true.push_back( data_point );

  data_point.first = 33;
  data_point.second = 20;
  map_true.push_back( data_point );

  data_point.first = 35;
  data_point.second = 21;
  map_true.push_back( data_point );

  data_point.first = 36;
  data_point.second = 22;
  map_true.push_back( data_point );

  data_point.first = 41;
  data_point.second = 23;
  map_true.push_back( data_point );

  data_point.first = 43;
  data_point.second = 24;
  map_true.push_back( data_point );

  data_point.first = 44;
  data_point.second = 25;
  map_true.push_back( data_point );

  data_point.first = 46;
  data_point.second = 26;
  map_true.push_back( data_point );

  data_point.first = 47;
  data_point.second = 26;
  map_true.push_back( data_point );
  
  data_point.first = 58;
  data_point.second = 27;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=97
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_97 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 97,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 24;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 25;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 17;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 18;
  map_true.push_back( data_point );

  data_point.first = 32;
  data_point.second = 19;
  map_true.push_back( data_point );

  data_point.first = 33;
  data_point.second = 20;
  map_true.push_back( data_point );

  data_point.first = 35;
  data_point.second = 21;
  map_true.push_back( data_point );

  data_point.first = 36;
  data_point.second = 22;
  map_true.push_back( data_point );

  data_point.first = 41;
  data_point.second = 23;
  map_true.push_back( data_point );

  data_point.first = 43;
  data_point.second = 24;
  map_true.push_back( data_point );

  data_point.first = 44;
  data_point.second = 25;
  map_true.push_back( data_point );

  data_point.first = 46;
  data_point.second = 25;
  map_true.push_back( data_point );

  data_point.first = 47;
  data_point.second = 25;
  map_true.push_back( data_point );
  
  data_point.first = 58;
  data_point.second = 26;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=98
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_98 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 98,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 24;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 25;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 17;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 18;
  map_true.push_back( data_point );

  data_point.first = 32;
  data_point.second = 19;
  map_true.push_back( data_point );

  data_point.first = 33;
  data_point.second = 20;
  map_true.push_back( data_point );

  data_point.first = 35;
  data_point.second = 21;
  map_true.push_back( data_point );

  data_point.first = 36;
  data_point.second = 22;
  map_true.push_back( data_point );

  data_point.first = 41;
  data_point.second = 23;
  map_true.push_back( data_point );

  data_point.first = 43;
  data_point.second = 24;
  map_true.push_back( data_point );

  data_point.first = 44;
  data_point.second = 25;
  map_true.push_back( data_point );
  
  data_point.first = 58;
  data_point.second = 26;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=99
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_99 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 99,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 24;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 25;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 17;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 18;
  map_true.push_back( data_point );

  data_point.first = 32;
  data_point.second = 19;
  map_true.push_back( data_point );

  data_point.first = 33;
  data_point.second = 20;
  map_true.push_back( data_point );

  data_point.first = 35;
  data_point.second = 21;
  map_true.push_back( data_point );

  data_point.first = 36;
  data_point.second = 22;
  map_true.push_back( data_point );

  data_point.first = 41;
  data_point.second = 23;
  map_true.push_back( data_point );

  data_point.first = 43;
  data_point.second = 24;
  map_true.push_back( data_point );

  data_point.first = 44;
  data_point.second = 25;
  map_true.push_back( data_point );
  
  data_point.first = 58;
  data_point.second = 26;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// check that the PhotonDataProcessor can create the correct electron shell 
// index map for Z=100
TEUCHOS_UNIT_TEST( PhotonDataProcessor, electron_shell_index_map_z_100 )
{
  TestingPhotonDataProcessor photon_data_processor( EPDL_TEST_FILE,
						    EADL_TEST_FILE,
						    COMPTON_TEST_FILE_PREFIX, "" );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map;

  photon_data_processor.createShellIndexMap( 100,
						     map );

  Teuchos::Array<FACEMC::Pair<unsigned int, unsigned int> > map_true;
  FACEMC::Pair<unsigned int,unsigned int> data_point;

  data_point.first = 1;
  data_point.second = 0;
  map_true.push_back( data_point );

  data_point.first = 3;
  data_point.second = 1;
  map_true.push_back( data_point );

  data_point.first = 5;
  data_point.second = 2;
  map_true.push_back( data_point );

  data_point.first = 6;
  data_point.second = 3;
  map_true.push_back( data_point );

  data_point.first = 8;
  data_point.second = 4;
  map_true.push_back( data_point );

  data_point.first = 10;
  data_point.second = 5;
  map_true.push_back( data_point );

  data_point.first = 11;
  data_point.second = 6;
  map_true.push_back( data_point );

  data_point.first = 13;
  data_point.second = 7;
  map_true.push_back( data_point );

  data_point.first = 14;
  data_point.second = 8;
  map_true.push_back( data_point );

  data_point.first = 16;
  data_point.second = 9;
  map_true.push_back( data_point );

  data_point.first = 18;
  data_point.second = 10;
  map_true.push_back( data_point );

  data_point.first = 19;
  data_point.second = 11;
  map_true.push_back( data_point );
  
  data_point.first = 21;
  data_point.second = 12;
  map_true.push_back( data_point );

  data_point.first = 22;
  data_point.second = 13;
  map_true.push_back( data_point );

  data_point.first = 24;
  data_point.second = 14;
  map_true.push_back( data_point );

  data_point.first = 25;
  data_point.second = 15;
  map_true.push_back( data_point );

  data_point.first = 27;
  data_point.second = 16;
  map_true.push_back( data_point );

  data_point.first = 29;
  data_point.second = 17;
  map_true.push_back( data_point );

  data_point.first = 30;
  data_point.second = 18;
  map_true.push_back( data_point );

  data_point.first = 32;
  data_point.second = 19;
  map_true.push_back( data_point );

  data_point.first = 33;
  data_point.second = 20;
  map_true.push_back( data_point );

  data_point.first = 35;
  data_point.second = 21;
  map_true.push_back( data_point );

  data_point.first = 36;
  data_point.second = 22;
  map_true.push_back( data_point );

  data_point.first = 41;
  data_point.second = 23;
  map_true.push_back( data_point );

  data_point.first = 43;
  data_point.second = 24;
  map_true.push_back( data_point );

  data_point.first = 44;
  data_point.second = 25;
  map_true.push_back( data_point );
  
  data_point.first = 58;
  data_point.second = 26;
  map_true.push_back( data_point );

  FACEMC_TEST_COMPARE_ARRAYS( map, map_true );
}

//---------------------------------------------------------------------------//
// end tstPhotonDataProcessorShellMap.cpp
//---------------------------------------------------------------------------//

