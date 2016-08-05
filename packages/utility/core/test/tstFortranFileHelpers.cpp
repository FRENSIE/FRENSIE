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

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Utils.hpp>

// FRENSIE Includes
#include "Utility_FortranFileHelperWrappers.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::string test_file_name;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
//Checks that the file exists.
TEUCHOS_UNIT_TEST( FortranFileHelpers, fileExistsUsingFortran )
{
  TEST_ASSERT( fileExistsUsingFortran( test_file_name.c_str(), test_file_name.size() ) );

  std::string file_name = "dummy_file.txt" ;

  TEST_ASSERT( !fileExistsUsingFortran( file_name.c_str(), file_name.size() ) );

}

//---------------------------------------------------------------------------//
//Checks that the file is readable.
TEUCHOS_UNIT_TEST( FortranFileHelpers, fileIsReadableUsingFortran )
{
  TEST_ASSERT( fileIsReadableUsingFortran( test_file_name.c_str(), test_file_name.size() ) );

  std::string file_name = "dummy_file.txt" ;

  TEST_ASSERT( !fileIsReadableUsingFortran( file_name.c_str(), file_name.size() ) );

}

//---------------------------------------------------------------------------//
//Opens file and then checks if file is open.
TEUCHOS_UNIT_TEST( FortranFileHelpers, fileIsOpenUsingFortran )
{

  int file_id = 1;

  openFileUsingFortran(test_file_name.c_str(), test_file_name.size(), file_id);

  TEST_ASSERT( fileIsOpenUsingFortran( file_id ) );

}

//---------------------------------------------------------------------------//
//This file should be open from the previous test.
//Closes the file and checks that it is closed.
TEUCHOS_UNIT_TEST( FortranFileHelpers, closeFileUsingFortran )
{
  int file_id = 1;

  closeFileUsingFortran( file_id );

  TEST_ASSERT( !fileIsOpenUsingFortran( file_id ) );
}

//---------------------------------------------------------------------------//
//This test reads a line in.
TEUCHOS_UNIT_TEST( FortranFileHelpers, readLineUsingFortran )
{
  int file_id = 1;

  openFileUsingFortran(test_file_name.c_str(), test_file_name.size(), file_id);

  std::string line( 100, ' ' );

  readLineUsingFortran( file_id, &line[0], line.size() );

  line = Teuchos::Utils::trimWhiteSpace( line );

  TEST_ASSERT( line.compare( "This is a test file. Line 1" ) == 0 );

  closeFileUsingFortran( file_id );
}

//---------------------------------------------------------------------------//
//This test moves to a specified line.
TEUCHOS_UNIT_TEST( FortranFileHelpers, moveToLineUsingFortran )
{
  int file_id = 1;

  openFileUsingFortran(test_file_name.c_str(), test_file_name.size(), file_id);

  moveToLineUsingFortran(file_id, 3 );

  std::string line( 100, ' ' );

  readLineUsingFortran( file_id, &line[0], line.size() );

  line = Teuchos::Utils::trimWhiteSpace( line );

  TEST_ASSERT( line.compare( "This is a test file. Line 3" ) == 0 );

  closeFileUsingFortran( file_id );
}

//---------------------------------------------------------------------------//
//This test moves to a specified line and tests the rewind function.
TEUCHOS_UNIT_TEST( FortranFileHelpers, rewindFileUsingFortran )
{
  int file_id = 1;

  openFileUsingFortran(test_file_name.c_str(), test_file_name.size(), file_id);

  moveToLineUsingFortran(file_id, 3 );

  rewindFileUsingFortran( file_id );

  std::string line( 100, ' ' );

  readLineUsingFortran( file_id, &line[0], line.size() );

  line = Teuchos::Utils::trimWhiteSpace( line );

  TEST_ASSERT( line.compare( "This is a test file. Line 1" ) == 0 );

  closeFileUsingFortran( file_id );
}
//---------------------------------------------------------------------------//
// Custom Main Function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
   Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

   clp.setOption( "test_file",
                  &test_file_name,
                  "Test file for checking FORTRAN file helpers." );

   Teuchos::GlobalMPISession mpiSession( &argc, &argv );
   return Teuchos::UnitTestRepository::runUnitTestsFromMain( argc, argv );
}



//---------------------------------------------------------------------------//
// end tstFortranFileHelpers.cpp
//---------------------------------------------------------------------------//

