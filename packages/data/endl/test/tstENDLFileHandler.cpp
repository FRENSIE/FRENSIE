//---------------------------------------------------------------------------//
//!
//! \file   tstENDLFileHandler.cpp
//! \author Luke Kersting
//! \brief  ENLIB97FileHandler class unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Data_ENDLFileHandler.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Test File Names.
//---------------------------------------------------------------------------//
std::string first_header_test_file;
std::string second_header_test_file;
std::string full_header_test_file;
std::string two_column_table_test_file;
std::string three_column_table_test_file;
std::string four_column_table_test_file;
std::string two_two_column_tables_test_file;
std::string two_three_column_tables_test_file;
std::string two_four_column_tables_test_file;

//---------------------------------------------------------------------------//
// Testing Parameters
//---------------------------------------------------------------------------//
double tol = 1e-12;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
void processTwoColumnTestingArray( std::vector<double>& two_col_indep, 
                                   std::vector<double>& two_col_dep )
{
two_col_indep.resize(12);
two_col_dep.resize(12);

two_col_indep[0] = 1.0;
two_col_indep[1] = 3.0;
two_col_indep[2] = 5.0;
two_col_indep[3] = 6.0;
two_col_indep[4] = 8.0;
two_col_indep[5] = 10.0;
two_col_indep[6] = 11.0;
two_col_indep[7] = 13.0;
two_col_indep[8] = 14.0;
two_col_indep[9] = 16.0;
two_col_indep[10] = 18.0;
two_col_indep[11] = 19.0;
two_col_dep[0] = 2.0;
two_col_dep[1] = 2.0;
two_col_dep[2] = 2.0;
two_col_dep[3] = 4.0;
two_col_dep[4] = 2.0;
two_col_dep[5] = 2.0;
two_col_dep[6] = 4.0;
two_col_dep[7] = 4.0;
two_col_dep[8] = 6.0;
two_col_dep[9] = 2.0;
two_col_dep[10] = 2.0;
two_col_dep[11] = 4.0;
}

void processThreeColumnTestingArray( 
        std::vector<double>& energy_bin, 
        std::map<double,std::vector<double> >& indep_true,
        std::map<double,std::vector<double> >& dep_true )
{
std::pair<double,std::vector<double> > indep_point, dep_point;

  energy_bin.push_back( 5.0 );
  indep_point.first = ( 5.0 );
  dep_point.first = ( 5.0 );
  indep_point.second.push_back( 2.96149e-1 );
  dep_point.second.push_back( 1.13103e-1 );
  indep_true.insert( indep_point );
  dep_true.insert( dep_point );
  indep_point.second.clear(); 
  dep_point.second.clear();

  energy_bin.push_back( 6.0 );
  indep_point.first = ( 6.0 );
  dep_point.first = ( 6.0 );
  indep_point.second.push_back( 4.55508e-1 );
  dep_point.second.push_back( 1.18701e-1 );
  indep_true.insert( indep_point );
  dep_true.insert( dep_point );
  indep_point.second.clear(); 
  dep_point.second.clear();

  energy_bin.push_back( 10.0 );
  indep_point.first = ( 10.0 );
  dep_point.first = ( 10.0 );
  indep_point.second.push_back( 5.34468e-2 );
  dep_point.second.push_back( 1.32545e-1 );
  indep_true.insert( indep_point );
  dep_true.insert( dep_point );
  indep_point.second.clear(); 
  dep_point.second.clear();

  energy_bin.push_back( 11.0 );
  indep_point.first = ( 11.0 );
  dep_point.first = ( 11.0 );
  indep_point.second.push_back( 1.05850e-1 );
  dep_point.second.push_back( 1.33863e-1 );
  indep_true.insert( indep_point );
  dep_true.insert( dep_point );
  indep_point.second.clear(); 
  dep_point.second.clear();

  energy_bin.push_back( 13.0 );
  indep_point.first = ( 13.0 );
  dep_point.first = ( 13.0 );
  indep_point.second.push_back( 2.18629e-3 );
  dep_point.second.push_back( 1.34485e-1 );
  indep_true.insert( indep_point );
  dep_true.insert( dep_point );
  indep_point.second.clear(); 
  dep_point.second.clear();

  energy_bin.push_back( 14.0 );
  indep_point.first = ( 14.0 );
  dep_point.first = ( 14.0 );
  indep_point.second.push_back( 2.37699e-3 );
  dep_point.second.push_back( 1.34740e-1 );
  indep_true.insert( indep_point );
  dep_true.insert( dep_point );
  indep_point.second.clear(); 
  dep_point.second.clear();

  energy_bin.push_back( 18.0 );
  indep_point.first = ( 18.0 );
  dep_point.first = ( 18.0 );
  indep_point.second.push_back( 1.36579e-2 );
  dep_point.second.push_back( 1.37436e-1 );
  indep_true.insert( indep_point );
  dep_true.insert( dep_point );
  indep_point.second.clear(); 
  dep_point.second.clear();

  energy_bin.push_back( 19.0 );
  indep_point.first = ( 19.0 );
  dep_point.first = ( 19.0 );
  indep_point.second.push_back( 2.84889e-2 );
  dep_point.second.push_back( 1.37794e-1 );
  indep_true.insert( indep_point );
  dep_true.insert( dep_point );
  indep_point.second.clear(); 
  dep_point.second.clear();
}

//---------------------------------------------------------------------------//
// Testing Stucts.
//---------------------------------------------------------------------------//
class TestENDLFileHandler : public Data::ENDLFileHandler
{
public:
  TestENDLFileHandler()
    : ENDLFileHandler()
  { /* ... */ }
  
  TestENDLFileHandler( const std::string &file_name )
    : ENDLFileHandler( file_name )
  { /* ... */ }

  virtual ~TestENDLFileHandler()
  { /* ... */ }

};  

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the ENDLFileHandler can open a file when constructed
TEUCHOS_UNIT_TEST( ENDLFileHandler, constructor )
{
  // If DBC is turned on, the constructor will throw an exception and exit
  // if this file does not exist. No Testing Macro is needed.
  Data::ENDLFileHandler endlib_file_handler( first_header_test_file );

  endlib_file_handler.closeENDLFile();
}

//---------------------------------------------------------------------------//
// Check that the ENDLFileHandler can open a file after being contructed
TEUCHOS_UNIT_TEST( ENDLFileHandler, openENDLFile )
{
  Data::ENDLFileHandler endlib_file_handler;
  
  // If DBC is turned on, the constructor will throw an exception and exit
  // if this file does not exist. No Testing Macro is needed.
  endlib_file_handler.openENDLFile( first_header_test_file );

  endlib_file_handler.closeENDLFile();
}

//---------------------------------------------------------------------------//
// Check that the ENDLFileHandler can read the first header of a table
TEUCHOS_UNIT_TEST( ENDLFileHandler, readFirstTableHeader )
{
  Data::ENDLFileHandler endlib_file_handler( first_header_test_file );
  
  // Values to read from the header
  int atomic_number, atomic_number_true = 99;
  int outgoing_particle_designator,
    outgoing_particle_designator_true = 0;
  double atomic_mass, atomic_mass_true = 252.0;
  int interpolation_flag, interpolation_flag_true = 5;

  // Read the test header file containing an typical first header
  endlib_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_mass,
					    interpolation_flag );
  
  // Test that the values read from the header match their expected values
  TEST_ASSERT( endlib_file_handler.validFile() );

  TEST_EQUALITY( atomic_number, atomic_number_true );

  TEST_EQUALITY( outgoing_particle_designator,
		 outgoing_particle_designator_true );

  TEST_FLOATING_EQUALITY( atomic_mass, atomic_mass_true, 1e-12 );

  TEST_EQUALITY( interpolation_flag, interpolation_flag_true );

  // Close the test header file
  endlib_file_handler.closeENDLFile();
}

//---------------------------------------------------------------------------//
// Check that the ENDLFileHandler can read the second header of a table
TEUCHOS_UNIT_TEST( ENDLFileHandler, readSecondTableHeader )
{
  Data::ENDLFileHandler endlib_file_handler( second_header_test_file );

  // Values to read from the header
  int reaction_type, reaction_type_true = 73000;
  int electron_shell, electron_shell_true = 11;

  // Read the test header file containing an typical second header
  endlib_file_handler.readSecondTableHeader( reaction_type,
					     electron_shell );
  
  // Test that the values read from the header match their expected values
  TEST_EQUALITY( reaction_type, reaction_type_true );

  TEST_EQUALITY( electron_shell, electron_shell_true );

  // Close the test header file
  endlib_file_handler.closeENDLFile();
}

//---------------------------------------------------------------------------//
// Check that the ENDLFileHandler can read the first header and
// second header of a table consecutively
TEUCHOS_UNIT_TEST( ENDLFileHandler, read_full_header_test )
{
  Data::ENDLFileHandler endlib_file_handler( full_header_test_file );
  
  // Values to read from the header
  int atomic_number, atomic_number_true = 70;
  int outgoing_particle_designator,
    outgoing_particle_designator_true = 0;
  double atomic_mass, atomic_mass_true = 173.04;
  int interpolation_flag, interpolation_flag_true = 5;
  int reaction_type, reaction_type_true = 73000;
  int electron_shell, electron_shell_true = 8;

  // Read the first header of the test header file
  endlib_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_mass,
					    interpolation_flag );

  // Read the second header of the test header file
  endlib_file_handler.readSecondTableHeader( reaction_type,
					     electron_shell );
  
  // Test that the values read from the header match their expected values
  TEST_EQUALITY( atomic_number, atomic_number_true );

  TEST_EQUALITY( outgoing_particle_designator,
		 outgoing_particle_designator_true );

  TEST_FLOATING_EQUALITY( atomic_mass, atomic_mass_true, 1e-12 );

  TEST_EQUALITY( interpolation_flag, interpolation_flag_true );

  TEST_EQUALITY( reaction_type, reaction_type_true );

  TEST_EQUALITY( electron_shell, electron_shell_true );

  // Close the test header file
  endlib_file_handler.closeENDLFile();
}

//---------------------------------------------------------------------------//
// Check that the ENDLFileHandler can skip a table
TEUCHOS_UNIT_TEST( ENDLFileHandler, skipTable )
{
  Data::ENDLFileHandler endlib_file_handler( two_column_table_test_file );
  
  int atomic_number;
  int outgoing_particle_designator;
  double atomic_mass;
  int interpolation_flag;
  int reaction_type;
  int electron_shell;

  endlib_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_mass,
					    interpolation_flag );

  endlib_file_handler.readSecondTableHeader( reaction_type,
					     electron_shell );

  endlib_file_handler.skipTable();

  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endlib_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_mass,
					    interpolation_flag );
  TEST_ASSERT( endlib_file_handler.endOfFile() );
  
  // Close the test table file
  endlib_file_handler.closeENDLFile();
}

//---------------------------------------------------------------------------//
// Check that the ENDLFileHandler can process a two column table
TEUCHOS_UNIT_TEST( ENDLFileHandler, processTwoColumnTable )
{
  Data::ENDLFileHandler endlib_file_handler( two_column_table_test_file );
  
  int atomic_number;
  int outgoing_particle_designator;
  double atomic_mass;
  int interpolation_flag;
  int reaction_type;
  int electron_shell;

  endlib_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_mass,
					    interpolation_flag );
  
  endlib_file_handler.readSecondTableHeader( reaction_type,
					     electron_shell );

  std::vector<double> indep, dep, indep_true, dep_true;

  endlib_file_handler.processTwoColumnTable( indep, dep );

  processTwoColumnTestingArray( indep_true, dep_true );

  UTILITY_TEST_COMPARE_ARRAYS( indep, indep_true );
  UTILITY_TEST_COMPARE_ARRAYS( dep, dep_true );

  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endlib_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_mass,
					    interpolation_flag );
  TEST_ASSERT( endlib_file_handler.endOfFile() );

  // Close the test table file
  endlib_file_handler.closeENDLFile();
}

//---------------------------------------------------------------------------//
// Check that the ENDLFileHandler can process a two column table
TEUCHOS_UNIT_TEST( ENDLFileHandler, processThreeColumnTable )
{
  Data::ENDLFileHandler endlib_file_handler( three_column_table_test_file );
  
  int atomic_number;
  int outgoing_particle_designator;
  double atomic_mass;
  int interpolation_flag;
  int reaction_type;
  int electron_shell;

  endlib_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_mass,
					    interpolation_flag );

  endlib_file_handler.readSecondTableHeader( reaction_type,
					     electron_shell );

  std::vector<double> energy_bin, energy_bin_true;
  std::map<double,std::vector<double> > indep, dep, indep_true, dep_true;

  endlib_file_handler.processThreeColumnTable( energy_bin, indep, dep );
 
  processThreeColumnTestingArray( energy_bin_true, indep_true, dep_true );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( energy_bin, energy_bin_true, tol );

  std::vector<double>::iterator i = energy_bin.begin();

  for ( i; i != energy_bin.end(); ++i )
  {
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( indep[*i], indep_true[*i], tol );
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( dep[*i], dep_true[*i], tol );
  }

  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endlib_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_mass,
					    interpolation_flag );
  TEST_ASSERT( endlib_file_handler.endOfFile() );

  // Close the test table file
  endlib_file_handler.closeENDLFile();
}

//---------------------------------------------------------------------------//
// Check that the ENDLFileHandler can skip a table and then skip a second table
TEUCHOS_UNIT_TEST( ENDLFileHandler, skip_skip_test )
{
  Data::ENDLFileHandler endlib_file_handler( two_two_column_tables_test_file );
  
  int atomic_number_1, atomic_number_2;
  int outgoing_particle_designator_1, outgoing_particle_designator_2;
  double atomic_mass_1, atomic_mass_2;
  int interpolation_flag_1, interpolation_flag_2;
  int reaction_type_1, reaction_type_2;
  int electron_shell_1, electron_shell_2;

  endlib_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_mass_1,
					    interpolation_flag_1 );

  endlib_file_handler.readSecondTableHeader( reaction_type_1,
					     electron_shell_1 );

  // Skip the first table
  endlib_file_handler.skipTable();
  
  endlib_file_handler.readFirstTableHeader( atomic_number_2,
					    outgoing_particle_designator_2,
					    atomic_mass_2,
					    interpolation_flag_2 );

  endlib_file_handler.readSecondTableHeader( reaction_type_2,
					     electron_shell_2 );
  // Check that the header info from both tables matches
  TEST_EQUALITY( atomic_number_1, atomic_number_2 );
  TEST_EQUALITY( outgoing_particle_designator_1,
		 outgoing_particle_designator_2 );
  TEST_EQUALITY( atomic_mass_1, atomic_mass_2 );
  TEST_EQUALITY( interpolation_flag_1, interpolation_flag_2 );
  TEST_EQUALITY( reaction_type_1, reaction_type_2 );
  TEST_EQUALITY( electron_shell_1, electron_shell_2 );
  
  // Skip the second table
  endlib_file_handler.skipTable();

  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endlib_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_mass_1,
					    interpolation_flag_1 );
  TEST_ASSERT( endlib_file_handler.endOfFile() );

  // Close the test table file
  endlib_file_handler.closeENDLFile();
}

//---------------------------------------------------------------------------//
// Check that the ENDLFileHandler can skip a table and then
// process a two column table
TEUCHOS_UNIT_TEST( ENDLFileHandler, two_column_table_skip_process_test )
{
  Data::ENDLFileHandler endlib_file_handler( two_two_column_tables_test_file );
  
  int atomic_number_1, atomic_number_2;
  int outgoing_particle_designator_1, outgoing_particle_designator_2;
  double atomic_mass_1, atomic_mass_2;
  int interpolation_flag_1, interpolation_flag_2;
  int reaction_type_1, reaction_type_2;
  int electron_shell_1, electron_shell_2;

  endlib_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_mass_1,
					    interpolation_flag_1 );

  endlib_file_handler.readSecondTableHeader( reaction_type_1,
					     electron_shell_1 );

  // Skip the first table
  endlib_file_handler.skipTable();
  
  endlib_file_handler.readFirstTableHeader( atomic_number_2,
					    outgoing_particle_designator_2,
					    atomic_mass_2,
					    interpolation_flag_2 );

  endlib_file_handler.readSecondTableHeader( reaction_type_2,
					     electron_shell_2 );
  
  // Check that the header info from both tables matches
  TEST_EQUALITY( atomic_number_1, atomic_number_2 );
  TEST_EQUALITY( outgoing_particle_designator_1,
		 outgoing_particle_designator_2 );
  TEST_EQUALITY( atomic_mass_1, atomic_mass_2 );
  TEST_EQUALITY( interpolation_flag_1, interpolation_flag_2 );
  TEST_EQUALITY( reaction_type_1, reaction_type_2 );
  TEST_EQUALITY( electron_shell_1, electron_shell_2 );
  
  std::vector<double> column_1, column_2;
  
  // process the second table
  endlib_file_handler.processTwoColumnTable( column_1, column_2 );

  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endlib_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_mass_1,
					    interpolation_flag_1 );
  TEST_ASSERT( endlib_file_handler.endOfFile() );

  // Close the test table file
  endlib_file_handler.closeENDLFile();
}

//---------------------------------------------------------------------------//
// Check that the ENDLFileHandler can process a two column table and then
// skip a table
TEUCHOS_UNIT_TEST( ENDLFileHandler, two_column_table_process_skip_test )
{
  Data::ENDLFileHandler endlib_file_handler( two_two_column_tables_test_file );
  
  int atomic_number_1, atomic_number_2;
  int outgoing_particle_designator_1, outgoing_particle_designator_2;
  double atomic_mass_1, atomic_mass_2;
  int interpolation_flag_1, interpolation_flag_2;
  int reaction_type_1, reaction_type_2;
  int electron_shell_1, electron_shell_2;

  endlib_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_mass_1,
					    interpolation_flag_1 );

  endlib_file_handler.readSecondTableHeader( reaction_type_1,
					     electron_shell_1 );

  std::vector<double> column_1, column_2;
  
  // process the second table
  endlib_file_handler.processTwoColumnTable( column_1, column_2 );
  
  endlib_file_handler.readFirstTableHeader( atomic_number_2,
					    outgoing_particle_designator_2,
					    atomic_mass_2,
					    interpolation_flag_2 );

  endlib_file_handler.readSecondTableHeader( reaction_type_2,
					     electron_shell_2 );

  // Skip the second table
  endlib_file_handler.skipTable();
  
  // Check that the header info from both tables matches
  TEST_EQUALITY( atomic_number_1, atomic_number_2 );
  TEST_EQUALITY( outgoing_particle_designator_1,
		 outgoing_particle_designator_2 );
  TEST_EQUALITY( atomic_mass_1, atomic_mass_2 );
  TEST_EQUALITY( interpolation_flag_1, interpolation_flag_2 );
  TEST_EQUALITY( reaction_type_1, reaction_type_2 );
  TEST_EQUALITY( electron_shell_1, electron_shell_2 );

  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endlib_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_mass_1,
					    interpolation_flag_1 );
  TEST_ASSERT( endlib_file_handler.endOfFile() );

  // Close the test table file
  endlib_file_handler.closeENDLFile();
}

//---------------------------------------------------------------------------//
// Check that the ENDLFileHandler can process a two column table and then
// process a two column table
TEUCHOS_UNIT_TEST( ENDLFileHandler, two_column_table_process_process_test )
{
  Data::ENDLFileHandler endlib_file_handler( two_two_column_tables_test_file );
  
  int atomic_number_1, atomic_number_2;
  int outgoing_particle_designator_1, outgoing_particle_designator_2;
  double atomic_mass_1, atomic_mass_2;
  int interpolation_flag_1, interpolation_flag_2;
  int reaction_type_1, reaction_type_2;
  int electron_shell_1, electron_shell_2;
  std::vector<double> column_11, column_12, column_21, column_22;
  

  endlib_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_mass_1,
					    interpolation_flag_1 );

  endlib_file_handler.readSecondTableHeader( reaction_type_1,
					     electron_shell_1 );

  // process the second table
  endlib_file_handler.processTwoColumnTable( column_11, column_12 );
  
  endlib_file_handler.readFirstTableHeader( atomic_number_2,
					    outgoing_particle_designator_2,
					    atomic_mass_2,
					    interpolation_flag_2 );

  endlib_file_handler.readSecondTableHeader( reaction_type_2,
					     electron_shell_2 );

  // process the second table
  endlib_file_handler.processTwoColumnTable( column_21, column_22 );
  
  // Check that the header info from both tables matches
  TEST_EQUALITY( atomic_number_1, atomic_number_2 );
  TEST_EQUALITY( outgoing_particle_designator_1,
		 outgoing_particle_designator_2 );
  TEST_EQUALITY( atomic_mass_1, atomic_mass_2 );
  TEST_EQUALITY( interpolation_flag_1, interpolation_flag_2 );
  TEST_EQUALITY( reaction_type_1, reaction_type_2 );
  TEST_EQUALITY( electron_shell_1, electron_shell_2 );
  UTILITY_TEST_COMPARE_ARRAYS( column_21, column_11 );
  UTILITY_TEST_COMPARE_ARRAYS( column_22, column_12 );

  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endlib_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_mass_1,
					    interpolation_flag_1 );
  TEST_ASSERT( endlib_file_handler.endOfFile() );

  // Close the test table file
  endlib_file_handler.closeENDLFile();
}

//---------------------------------------------------------------------------//
// Check that the ENDLFileHandler can skip a three column table and then
// process a three column table
TEUCHOS_UNIT_TEST( ENDLFileHandler, three_column_table_skip_process_test )
{
  Data::ENDLFileHandler endlib_file_handler( two_three_column_tables_test_file );
  
  int atomic_number_1, atomic_number_2;
  int outgoing_particle_designator_1, outgoing_particle_designator_2;
  double atomic_mass_1, atomic_mass_2;
  int interpolation_flag_1, interpolation_flag_2;
  int reaction_type_1, reaction_type_2;
  int electron_shell_1, electron_shell_2;
  
  endlib_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_mass_1,
					    interpolation_flag_1 );
  
  endlib_file_handler.readSecondTableHeader( reaction_type_1,
					     electron_shell_1 );
  
  // Skip the first table
  endlib_file_handler.skipTable();
  
  endlib_file_handler.readFirstTableHeader( atomic_number_2,
					    outgoing_particle_designator_2,
					    atomic_mass_2,
					    interpolation_flag_2 );
  
  endlib_file_handler.readSecondTableHeader( reaction_type_2,
					     electron_shell_2 );
  
  std::vector<double> column_1;
  std::map<double,std::vector<double> > column_2, column_3;
  
  // process the second table
  endlib_file_handler.processThreeColumnTable( column_1, column_2, column_3 );


  // Check that the header info from both tables matches
  TEST_EQUALITY( atomic_number_1, atomic_number_2 );
  TEST_EQUALITY( outgoing_particle_designator_1,
		 outgoing_particle_designator_2 );
  TEST_EQUALITY( atomic_mass_1, atomic_mass_2 );
  TEST_EQUALITY( interpolation_flag_1, interpolation_flag_2 );
  TEST_EQUALITY( reaction_type_1, reaction_type_2 );
  TEST_EQUALITY( electron_shell_1, electron_shell_2 );  

  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endlib_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_mass_1,
					    interpolation_flag_1 );
  TEST_ASSERT( endlib_file_handler.endOfFile() );

  // Close the test table file
  endlib_file_handler.closeENDLFile();
}

//---------------------------------------------------------------------------//
// Check that the ENDLFileHandler can process a three column table and then
// skip a three column table
TEUCHOS_UNIT_TEST( ENDLFileHandler, three_column_table_process_skip_test )
{
  Data::ENDLFileHandler endlib_file_handler( two_three_column_tables_test_file );
  
  int atomic_number_1, atomic_number_2;
  int outgoing_particle_designator_1, outgoing_particle_designator_2;
  double atomic_mass_1, atomic_mass_2;
  int interpolation_flag_1, interpolation_flag_2;
  int reaction_type_1, reaction_type_2;
  int electron_shell_1, electron_shell_2;
  
  endlib_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_mass_1,
					    interpolation_flag_1 );
  
  endlib_file_handler.readSecondTableHeader( reaction_type_1,
					     electron_shell_1 );
  
  std::vector<double> column_1;
  std::map<double,std::vector<double> > column_2, column_3;
  
  // process the second table
  endlib_file_handler.processThreeColumnTable( column_1, column_2, column_3 );

  endlib_file_handler.readFirstTableHeader( atomic_number_2,
					    outgoing_particle_designator_2,
					    atomic_mass_2,
					    interpolation_flag_2 );
  
  endlib_file_handler.readSecondTableHeader( reaction_type_2,
					     electron_shell_2 );
  
  // Skip the second table
  endlib_file_handler.skipTable();
  
  // Check that the header info from both tables matches
  TEST_EQUALITY( atomic_number_1, atomic_number_2 );
  TEST_EQUALITY( outgoing_particle_designator_1,
		 outgoing_particle_designator_2 );
  TEST_EQUALITY( atomic_mass_1, atomic_mass_2 );
  TEST_EQUALITY( interpolation_flag_1, interpolation_flag_2 );
  TEST_EQUALITY( reaction_type_1, reaction_type_2 );
  TEST_EQUALITY( electron_shell_1, electron_shell_2 );  

  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endlib_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_mass_1,
					    interpolation_flag_1 );
  TEST_ASSERT( endlib_file_handler.endOfFile() );

  // Close the test table file
  endlib_file_handler.closeENDLFile();
}

//---------------------------------------------------------------------------//
// Check that the ENDLFileHandler can process a three column table and then
// process a three column table
TEUCHOS_UNIT_TEST( ENDLFileHandler, three_column_table_process_process_test )
{
  Data::ENDLFileHandler endlib_file_handler( two_three_column_tables_test_file );
  
  int atomic_number_1, atomic_number_2;
  int outgoing_particle_designator_1, outgoing_particle_designator_2;
  double atomic_mass_1, atomic_mass_2;
  int interpolation_flag_1, interpolation_flag_2;
  int reaction_type_1, reaction_type_2;
  int electron_shell_1, electron_shell_2;
  
  endlib_file_handler.readFirstTableHeader( atomic_number_1,
				       outgoing_particle_designator_1,
				       atomic_mass_1,
				       interpolation_flag_1 );
  
  endlib_file_handler.readSecondTableHeader( reaction_type_1,
					electron_shell_1 );
  
  std::vector<double> column_11;
  std::map<double,std::vector<double> > column_12, column_13;
  
  // process the second table
  endlib_file_handler.processThreeColumnTable( column_11, column_12, column_13 );

  endlib_file_handler.readFirstTableHeader( atomic_number_2,
					    outgoing_particle_designator_2,
					    atomic_mass_2,
					    interpolation_flag_2 );
  
  endlib_file_handler.readSecondTableHeader( reaction_type_2,
					     electron_shell_2 );
  
  std::vector<double> column_21;
  std::map<double,std::vector<double> > column_22, column_23;
  
  // process the second table
  endlib_file_handler.processThreeColumnTable( column_21, column_22, column_23 );
  
  // Check that the header info from both tables matches
  TEST_EQUALITY( atomic_number_1, atomic_number_2 );
  TEST_EQUALITY( outgoing_particle_designator_1,
		 outgoing_particle_designator_2 );
  TEST_EQUALITY( atomic_mass_1, atomic_mass_2 );
  TEST_EQUALITY( interpolation_flag_1, interpolation_flag_2 );
  TEST_EQUALITY( reaction_type_1, reaction_type_2 );
  TEST_EQUALITY( electron_shell_1, electron_shell_2 );  
  UTILITY_TEST_COMPARE_ARRAYS( column_21, column_11 );
  
  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endlib_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_mass_1,
					    interpolation_flag_1 );
  TEST_ASSERT( endlib_file_handler.endOfFile() );

  // Close the test table file
  endlib_file_handler.closeENDLFile();
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char* argv[] )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();
  
  clp.setOption( "first_header_test_file",
		 &first_header_test_file,
		 "First header test file name" );
  clp.setOption( "second_header_test_file",
		 &second_header_test_file,
		 "Second header test file name" );
  clp.setOption( "full_header_test_file",
		 &full_header_test_file,
		 "Full header test file name" );
  clp.setOption( "two_column_table_test_file",
		 &two_column_table_test_file,
		 "Two column table test file name" );
  clp.setOption( "three_column_table_test_file",
		 &three_column_table_test_file,
		 "Three column table test file name" );
  clp.setOption( "four_column_table_test_file",
		 &four_column_table_test_file,
		 "Four column table test file name" );
  clp.setOption( "two_two_column_tables_test_file",
		 &two_two_column_tables_test_file,
		 "Two two column tables test file name" );
  clp.setOption( "two_three_column_tables_test_file",
		 &two_three_column_tables_test_file,
		 "Two three column tables test file name" );
  clp.setOption( "two_four_column_tables_test_file",
		 &two_four_column_tables_test_file,
		 "Two four column tables test file name" );

  Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  return Teuchos::UnitTestRepository::runUnitTestsFromMain( argc, argv );
}
  
//---------------------------------------------------------------------------//
// end tstENDLFileHandler.cpp
//---------------------------------------------------------------------------//

