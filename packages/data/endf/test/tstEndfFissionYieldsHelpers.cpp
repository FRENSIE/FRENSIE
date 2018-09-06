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
#include <memory>

// FRENSIE Includes
#include "Data_ENDFFissionYieldsHelperWrappers.hpp"
#include "Utility_FortranFileHelperWrappers.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::string test_endf_file_name;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check read ENDF Fission Yields Header
FRENSIE_UNIT_TEST( EndfFissionYields, readEndfFissionYieldsHeader )
{
   int file_id = 1;

   openFileUsingFortran( test_endf_file_name.c_str(), test_endf_file_name.size(), file_id );

   skipEndfFissionYieldsFirstHeader( file_id );

   int zaid;               //92235
   int number_energies;    //3

   readEndfFissionYieldsHeader( file_id, &zaid, &number_energies );

   closeFileUsingFortran( file_id );

   FRENSIE_CHECK_EQUAL( zaid, 92235 );
   FRENSIE_CHECK_EQUAL( number_energies, 3 );

}

// Check read ENDF Fission Yields Data Header
FRENSIE_UNIT_TEST( EndfFissionYields, readEndfFissionYieldsDataHeader )
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

   FRENSIE_CHECK_EQUAL( number_data_sets, 1247 );
   FRENSIE_CHECK_FLOATING_EQUALITY( energy, 0.0253, 1e-15 )
}

// Check read ENDF Fission Yields Data
FRENSIE_UNIT_TEST( EndfFissionYields, readEndfFissionYieldsData )
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

   std::vector<int> yield_zaid( number_data_sets );
   std::vector<int> yield_meta_state( number_data_sets );
   std::vector<double> yield( number_data_sets );
   std::vector<double> yield_std( number_data_sets );

   readEndfFissionYieldsData( file_id,
                              &number_data_sets,
                              yield_zaid.data(),
                              yield_meta_state.data(),
                              yield.data(),
                              yield_std.data() );

   closeFileUsingFortran( file_id );

   FRENSIE_CHECK_EQUAL( yield_zaid.front(), 23066 );
   FRENSIE_CHECK_EQUAL( yield_zaid.back(), 72172 );
   FRENSIE_CHECK_EQUAL( yield_meta_state.front(), 0 );
   FRENSIE_CHECK_EQUAL( yield_meta_state.back(), 0 );
   FRENSIE_CHECK_FLOATING_EQUALITY( yield.front(), 2.05032e-19, 1e-15 );
   FRENSIE_CHECK_FLOATING_EQUALITY( yield.back(), 0.0, 1e-15 );
   FRENSIE_CHECK_FLOATING_EQUALITY( yield_std.front(), 1.3122e-19, 1e-15);
   FRENSIE_CHECK_SMALL( yield_std.back(), 1e-15);
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_endf_file",
                                        test_endf_file_name, "",
                                        "Test file for checking ENDF fission yields helpers." );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstEndfFissionYieldsHelpers.cpp
//---------------------------------------------------------------------------//
