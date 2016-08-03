//---------------------------------------------------------------------------//
//!
//! \file   tstEndfFissionYieldsHelpers.cpp
//! \author Alex Bennett
//! \brief  ENDF Fission Yields Helpers unit test
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <string>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Utils.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Utility_FortranFileHelperWrappers.hpp"
#include "Data_ENDFFissionYieldsHelperWrappers.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::string test_endf_file_name;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check read ENDF Fission Yields Header
TEUCHOS_UNIT_TEST( EndfFissionYields, readEndfFissionYieldsHeader )
{
   int file_id = 1;

   openFileUsingFortran( test_endf_file_name.c_str(), test_endf_file_name.size(), file_id );

   skipEndfFissionYieldsFirstHeader( file_id );

   int zaid;               //92235
   int number_energies;    //3

   readEndfFissionYieldsHeader( file_id, &zaid, &number_energies );

   closeFileUsingFortran( file_id );

   TEST_COMPARE( zaid, ==, 92235 );
   TEST_COMPARE( number_energies, ==, 3 );

}

// Check read ENDF Fission Yields Data Header
TEUCHOS_UNIT_TEST( EndfFissionYields, readEndfFissionYieldsDataHeader )
{
   int file_id = 1;

   openFileUsingFortran( test_endf_file_name.c_str(), test_endf_file_name.size(), file_id );

//   rewindFileUsingFortran( file_id );

   skipEndfFissionYieldsFirstHeader( file_id );

   int zaid;
   int number_energies;

   readEndfFissionYieldsHeader( file_id, &zaid, &number_energies );

   int number_data_sets;
   double energy;

   readEndfFissionYieldsDataHeader( file_id, &number_data_sets, &energy );

   closeFileUsingFortran( file_id );

   TEST_COMPARE( number_data_sets, ==, 1247 );
   TEST_FLOATING_EQUALITY( energy, 0.0253, 1e-15 )
}

// Check read ENDF Fission Yields Data
TEUCHOS_UNIT_TEST( EndfFissionYields, readEndfFissionYieldsData )
{
   int file_id = 1;

   openFileUsingFortran( test_endf_file_name.c_str(), test_endf_file_name.size(), file_id );

   skipEndfFissionYieldsFirstHeader( file_id );

   int zaid;
   int number_energies;

   readEndfFissionYieldsHeader( file_id, &zaid, &number_energies );

   int number_data_sets;
   double energy;

   readEndfFissionYieldsDataHeader( file_id, &number_data_sets, &energy );

   Teuchos::Array<int> yield_zaid( number_data_sets );
   Teuchos::Array<int> yield_meta_state( number_data_sets );
   Teuchos::Array<double> yield( number_data_sets );
   Teuchos::Array<double> yield_std( number_data_sets );

   readEndfFissionYieldsData( file_id, &number_data_sets, yield_zaid.getRawPtr(),
           yield_meta_state.getRawPtr(), yield.getRawPtr(), yield_std.getRawPtr() );

   closeFileUsingFortran( file_id );

   TEST_COMPARE( yield_zaid.front(), ==, 23066 );
   TEST_COMPARE( yield_zaid.back(), ==, 72172 );
   TEST_COMPARE( yield_meta_state.front(), ==, 0 );
   TEST_COMPARE( yield_meta_state.back(), ==, 0 );
   TEST_FLOATING_EQUALITY( yield.front(), 2.05032e-19, 1e-15 );
   TEST_FLOATING_EQUALITY( yield.back(), 0.0, 1e-15 );
   TEST_FLOATING_EQUALITY( yield_std.front(), 1.3122e-19, 1e-15);
   TEST_FLOATING_EQUALITY( yield_std.back(), 0.0, 1e-15);
}

//---------------------------------------------------------------------------//
// Custom Main Function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
   Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

   clp.setOption( "test_endf_file",
                  &test_endf_file_name,
                  "Test file for checking ENDF fission yields helpers." );

   Teuchos::GlobalMPISession mpiSession( &argc, &argv );
   return Teuchos::UnitTestRepository::runUnitTestsFromMain( argc, argv );
}


//---------------------------------------------------------------------------//
// end tstEndfFissionYieldsHelpers.cpp
//---------------------------------------------------------------------------//
