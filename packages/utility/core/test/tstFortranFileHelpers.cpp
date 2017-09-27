//---------------------------------------------------------------------------//
//!
//! \file   tstFortranFileHelpers.cpp
//! \author Alex Robinson, Alex Bennett
//! \brief  File Helpers unit test
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <string>

// Boost Includes
#include <boost/algorithm/string.hpp>

// FRENSIE Includes
#include "Utility_FortranFileHelperWrappers.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::string test_file_name;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
//Checks that the file exists.
FRENSIE_UNIT_TEST( FortranFileHelpers, fileExistsUsingFortran )
{
  FRENSIE_CHECK( fileExistsUsingFortran( test_file_name.c_str(), test_file_name.size() ) );
  
  std::string file_name = "dummy_file.txt" ;

  FRENSIE_CHECK( !fileExistsUsingFortran( file_name.c_str(), file_name.size() ) );

}

//---------------------------------------------------------------------------//
//Checks that the file is readable.
FRENSIE_UNIT_TEST( FortranFileHelpers, fileIsReadableUsingFortran )
{
  FRENSIE_CHECK( fileIsReadableUsingFortran( test_file_name.c_str(), test_file_name.size() ) );

  std::string file_name = "dummy_file.txt" ;

  FRENSIE_CHECK( !fileIsReadableUsingFortran( file_name.c_str(), file_name.size() ) );

}

//---------------------------------------------------------------------------//
//Opens file and then checks if file is open.
FRENSIE_UNIT_TEST( FortranFileHelpers, fileIsOpenUsingFortran )
{

  int file_id = 1;

  openFileUsingFortran(test_file_name.c_str(), test_file_name.size(), file_id);

  FRENSIE_CHECK( fileIsOpenUsingFortran( file_id ) );

}

//---------------------------------------------------------------------------//
//This file should be open from the previous test.
//Closes the file and checks that it is closed.
FRENSIE_UNIT_TEST( FortranFileHelpers, closeFileUsingFortran )
{
  int file_id = 1;

  closeFileUsingFortran( file_id );

  FRENSIE_CHECK( !fileIsOpenUsingFortran( file_id ) );
}

//---------------------------------------------------------------------------//
//This test reads a line in.
FRENSIE_UNIT_TEST( FortranFileHelpers, readLineUsingFortran )
{
  int file_id = 1;

  openFileUsingFortran(test_file_name.c_str(), test_file_name.size(), file_id);

  std::string line( 100, ' ' );

  readLineUsingFortran( file_id, &line[0], line.size() );

  boost::algorithm::trim( line );

  FRENSIE_CHECK( line.compare( "This is a test file. Line 1" ) == 0 );

  closeFileUsingFortran( file_id );
}

//---------------------------------------------------------------------------//
//This test moves to a specified line.
FRENSIE_UNIT_TEST( FortranFileHelpers, moveToLineUsingFortran )
{
  int file_id = 1;

  openFileUsingFortran(test_file_name.c_str(), test_file_name.size(), file_id);

  moveToLineUsingFortran(file_id, 3 );

  std::string line( 100, ' ' );

  readLineUsingFortran( file_id, &line[0], line.size() );

  boost::algorithm::trim( line );

  FRENSIE_CHECK( line.compare( "This is a test file. Line 3" ) == 0 );

  closeFileUsingFortran( file_id );
}

//---------------------------------------------------------------------------//
//This test moves to a specified line and tests the rewind function.
FRENSIE_UNIT_TEST( FortranFileHelpers, rewindFileUsingFortran )
{
  int file_id = 1;

  openFileUsingFortran(test_file_name.c_str(), test_file_name.size(), file_id);

  moveToLineUsingFortran(file_id, 3 );

  rewindFileUsingFortran( file_id );

  std::string line( 100, ' ' );

  readLineUsingFortran( file_id, &line[0], line.size() );

  boost::algorithm::trim( line );

  FRENSIE_CHECK( line.compare( "This is a test file. Line 1" ) == 0 );

  closeFileUsingFortran( file_id );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_OPTION( "test_file",
              boost::program_options::value<std::string>(&test_file_name)->default_value( "" ),
              "Test file for checking FORTRAN file helpers." );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstFortranFileHelpers.cpp
//---------------------------------------------------------------------------//

