//---------------------------------------------------------------------------//
//!
//! \file   tstEPICSFileHandler.cpp
//! \author Luke Kersting
//! \brief  ENDLFileHandler EPICS2014 class unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>

// FRENSIE Includes
#include "Data_ENDLFileHandler.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Test File Names.
//---------------------------------------------------------------------------//
std::string first_header_test_file;
std::string second_header_test_file;
std::string full_header_test_file;
std::string two_column_table_test_file;
std::string three_column_table_test_file;
std::string three_column_table_test_file_vector;
std::string four_column_table_test_file;
std::string two_two_column_tables_test_file;
std::string two_three_column_tables_test_file;
std::string two_four_column_tables_test_file;

bool epics_file_type = true;

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
        std::vector<double>& indep_true,
        std::vector<double>& dep_true )
{
  energy_bin.resize(8);
  indep_true.resize(8);
  dep_true.resize(8);

  energy_bin[0] = 5.0;
  indep_true[0] = 2.96149e-1;
  dep_true[0] = 1.13103e-1;

  energy_bin[1] = 6.0;
  indep_true[1] = 4.55508e-1;
  dep_true[1] = 1.18701e-1;

  energy_bin[2] = 10.0;
  indep_true[2] = 5.34468e-2;
  dep_true[2] = 1.32545e-1;

  energy_bin[3] = 11.0;
  indep_true[3] = 1.05850e-1;
  dep_true[3] = 1.33863e-1;

  energy_bin[4] = 13.0;
  indep_true[4] = 2.18629e-3;
  dep_true[4] = 1.34485e-1;

  energy_bin[5] = 14.0;
  indep_true[5] = 2.37699e-3;
  dep_true[5] = 1.34740e-1;

  energy_bin[6] = 18.0;
  indep_true[6] = 1.36579e-2;
  dep_true[6] = 1.37436e-1;

  energy_bin[7] = 19.0;
  indep_true[7] = 2.84889e-2;
  dep_true[7] = 1.37794e-1;
}

void processThreeColumnTestingVector(
        std::vector<double>& energy_bin,
        std::vector<double>& indep_true,
        std::vector<double>& dep_true )
{
  energy_bin.resize(8);
  indep_true.resize(8);
  dep_true.resize(8);

  energy_bin[0] = 1.000000000E-05;
  indep_true[0] = 1.000000000E-06;
  dep_true[0] = 5.000000000E-01;

  energy_bin[1] = 1.000000000E-05;
  indep_true[1] = 2.000000000E+00;
  dep_true[1] = 5.000000000E-01;

  energy_bin[2] = 1.000000000E-03;
  indep_true[2] = 1.000000000E-06;
  dep_true[2] = 6.211020000E+01;

  energy_bin[3] = 1.000000000E-03;
  indep_true[3] = 3.799900000E-03;
  dep_true[3] = 4.235800000E+01;

  energy_bin[4] = 1.000000000E-03;
  indep_true[4] = 7.999900000E-03;
  dep_true[4] = 2.921990000E+01;

  energy_bin[5] = 1.000000000E-03;
  indep_true[5] = 1.200000000E-02;
  dep_true[5] = 2.146350000E+01;

  energy_bin[6] = 1.000000000E-03;
  indep_true[6] = 1.700000000E-02;
  dep_true[6] = 1.533800000E+01;

  energy_bin[7] = 1.000000000E-03;
  indep_true[7] = 2.300000000E-02;
  dep_true[7] = 1.084120000E+01;
}

void processFourColumnTestingArray(
        std::vector<double>& column_one,
        std::vector<double>& column_two,
        std::vector<double>& column_three,
        std::vector<double>& column_four )
{
  column_one.resize(5);
  column_two.resize(5);
  column_three.resize(5);
  column_four.resize(5);

  column_one[0] = 2.70000e+1;
  column_two[0] = 2.70000e+1;
  column_three[0] = 3.80318e-1;
  column_four[0] = 6.71000e-6;

  column_one[1] = 2.70000e+1;
  column_two[1] = 2.90000e+1;
  column_three[1] = 2.81669e-1;
  column_four[1] = 1.38200e-5;

  column_one[2] = 2.70000e+1;
  column_two[2] = 3.00000e+1;
  column_three[2] = 2.44679e-1;
  column_four[2] = 1.43300e-5;

  column_one[3] = 2.90000e+1;
  column_two[3] = 3.00000e+1;
  column_three[3] = 8.83536e-2;
  column_four[3] = 2.14400e-5;

  column_one[4] = 3.00000e+1;
  column_two[4] = 3.00000e+1;
  column_three[4] = 4.98008e-3;
  column_four[4] = 2.19500e-5;

}

void mapTwoColumnTestingArray(
    std::vector<unsigned>& subshells,
    std::map<unsigned,unsigned>& subshell_data )
{
  std::vector<double> shell, data;
  subshells.resize(12);

  processTwoColumnTestingArray( shell, data );

  for( int i = 0; i < shell.size(); ++i )
  {
    subshells[i] = shell[i];
    subshell_data.emplace( shell[i], data[i] );
  }
}

void mapThreeColumnTestingArray(
        std::vector<unsigned>& bin,
        std::map<unsigned,double>& indep_true,
        std::map<unsigned,double>& dep_true )
{
  std::vector<double> indep(8), dep(8), data_bin(8);
  bin.resize(8);

  processThreeColumnTestingArray( data_bin, indep, dep );

  for( int i = 0; i < data_bin.size(); ++i )
  {
    bin[i] = data_bin[i];
    indep_true.emplace( bin[i], indep[i] );
    dep_true.emplace( bin[i], dep[i] );
  }
}

void mapThreeColumnTestingArray(
        std::vector<double>& energy_bin,
        std::map<double,std::vector<double> >& indep_true,
        std::map<double,std::vector<double> >& dep_true )
{
  std::vector<double> indep_point, dep_point, bin;
  std::vector<double> indep(8), dep(8);
  energy_bin.clear();

  processThreeColumnTestingVector( bin, indep, dep );

  for( int i = 0; i < 2; ++i )
  {
    indep_point.push_back( indep[i] );
    dep_point.push_back( dep[i] );
  }

  energy_bin.push_back( bin[0] );
  indep_true.emplace( energy_bin.back(), indep_point );
  dep_true.emplace( energy_bin.back(), dep_point );
  indep_point.clear();
  dep_point.clear();

  for( int i = 2; i < bin.size(); ++i )
  {
    indep_point.push_back( indep[i] );
    dep_point.push_back( dep[i] );
  }

  energy_bin.push_back( bin[2] );
  indep_true.emplace( energy_bin.back(), indep_point );
  dep_true.emplace( energy_bin.back(), dep_point );
}
/*
void mapFourColumnTestingArray(
        std::vector<unsigned>& bin,
        std::map<unsigned,std::vector<unsigned> >& secondary_bin,
        std::map<unsigned,std::map<unsigned,double> >& indep_true,
        std::map<unsigned,std::map<unsigned,double> >& dep_true )
{
  std::vector<double> bin_1, bin_2, indep_point, dep_point;
  bin.clear();
  secondary_bin.clear();

  std::map<unsigned,double> indep, dep;
  std::vector<double> sec_bin;

  processFourColumnTestingArray( bin_1, bin_2, indep_point, dep_point );

  for( int i = 0; i < 3; ++i )
  {
    sec_bin.push_pack( bin_2[i] );

    indep.emplace( secondary_bin[i], indep_point[i] );
    dep.emplace( secondary_bin[i], dep_point[i] );
  }

    bin.push_back( bin_1[2] );
    secondary_bin.emplace( bin.back(), sec_bin );
    indep_true.emplace( bin.back(), indep );
    dep_true.emplace( bin.back(), dep );

    sec_bin.clear();
    indep.clear();
    dep.clear();

  for( int i = 3; i < bin.size(); ++i )
  {
    bin.push_back( bin_1[i] );
    secondary_bin.emplace( bin.back(), bin_2[i] );
    indep.emplace( secondary_bin[i], indep_point[i] );
    dep.emplace( secondary_bin[i], dep_point[i] );

    indep_true.emplace( bin.back(), indep );
    dep_true.emplace( bin.back(), dep );

    sec_bin.clear();
    indep.clear();
    dep.clear();
  }
}
*/
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
FRENSIE_UNIT_TEST( ENDLFileHandler, constructor )
{
  // If DBC is turned on, the constructor will throw an exception and exit
  // if this file does not exist. No Testing Macro is needed.
  Data::ENDLFileHandler endl_file_handler( first_header_test_file, epics_file_type );

  endl_file_handler.closeENDLFile();
}

//---------------------------------------------------------------------------//
// Check that the ENDLFileHandler can open a file after being constructed
FRENSIE_UNIT_TEST( ENDLFileHandler, openENDLFile )
{
  Data::ENDLFileHandler endl_file_handler;

  // If DBC is turned on, the constructor will throw an exception and exit
  // if this file does not exist. No Testing Macro is needed.
  endl_file_handler.openENDLFile( first_header_test_file );

  endl_file_handler.closeENDLFile();
}

//---------------------------------------------------------------------------//
// Check that the ENDLFileHandler can read the first header of a table
FRENSIE_UNIT_TEST( ENDLFileHandler, readFirstTableHeader )
{
  Data::ENDLFileHandler endl_file_handler( first_header_test_file, epics_file_type );

  // Values to read from the header
  int atomic_number, atomic_number_true = 99;
  int outgoing_particle_designator,
    outgoing_particle_designator_true = 0;
  double atomic_mass, atomic_mass_true = 252.0;
  int interpolation_flag, interpolation_flag_true = 5;

  // Read the test header file containing an typical first header
  endl_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_mass,
					    interpolation_flag );

  // Test that the values read from the header match their expected values
  FRENSIE_CHECK( endl_file_handler.validFile() );

  FRENSIE_CHECK_EQUAL( atomic_number, atomic_number_true );

  FRENSIE_CHECK_EQUAL( outgoing_particle_designator,
		 outgoing_particle_designator_true );

  FRENSIE_CHECK_FLOATING_EQUALITY( atomic_mass, atomic_mass_true, 1e-12 );

  FRENSIE_CHECK_EQUAL( interpolation_flag, interpolation_flag_true );

  // Close the test header file
  endl_file_handler.closeENDLFile();
}

//---------------------------------------------------------------------------//
// Check that the ENDLFileHandler can read the second header of a table
FRENSIE_UNIT_TEST( ENDLFileHandler, readSecondTableHeader )
{
  Data::ENDLFileHandler endl_file_handler( second_header_test_file, epics_file_type );

  // Values to read from the header
  int reaction_type, reaction_type_true = 73000;
  int electron_shell, electron_shell_true = 11;

  // Read the test header file containing an typical second header
  endl_file_handler.readSecondTableHeader( reaction_type,
					     electron_shell );

  // Test that the values read from the header match their expected values
  FRENSIE_CHECK_EQUAL( reaction_type, reaction_type_true );

  FRENSIE_CHECK_EQUAL( electron_shell, electron_shell_true );

  // Close the test header file
  endl_file_handler.closeENDLFile();
}

//---------------------------------------------------------------------------//
// Check that the ENDLFileHandler can read the first header and
// second header of a table consecutively
FRENSIE_UNIT_TEST( ENDLFileHandler, read_full_header_test )
{
  Data::ENDLFileHandler endl_file_handler( full_header_test_file, epics_file_type );

  // Values to read from the header
  int atomic_number, atomic_number_true = 70;
  int outgoing_particle_designator,
    outgoing_particle_designator_true = 0;
  double atomic_mass, atomic_mass_true = 173.04;
  int interpolation_flag, interpolation_flag_true = 5;
  int reaction_type, reaction_type_true = 73000;
  int electron_shell, electron_shell_true = 8;

  // Read the first header of the test header file
  endl_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_mass,
					    interpolation_flag );

  // Read the second header of the test header file
  endl_file_handler.readSecondTableHeader( reaction_type,
					     electron_shell );

  // Test that the values read from the header match their expected values
  FRENSIE_CHECK_EQUAL( atomic_number, atomic_number_true );

  FRENSIE_CHECK_EQUAL( outgoing_particle_designator,
		 outgoing_particle_designator_true );

  FRENSIE_CHECK_FLOATING_EQUALITY( atomic_mass, atomic_mass_true, 1e-12 );

  FRENSIE_CHECK_EQUAL( interpolation_flag, interpolation_flag_true );

  FRENSIE_CHECK_EQUAL( reaction_type, reaction_type_true );

  FRENSIE_CHECK_EQUAL( electron_shell, electron_shell_true );

  // Close the test header file
  endl_file_handler.closeENDLFile();
}

//---------------------------------------------------------------------------//
// Check that the ENDLFileHandler can skip a table
FRENSIE_UNIT_TEST( ENDLFileHandler, skipTable )
{
  Data::ENDLFileHandler endl_file_handler( two_column_table_test_file, epics_file_type );

  int atomic_number;
  int outgoing_particle_designator;
  double atomic_mass;
  int interpolation_flag;
  int reaction_type;
  int electron_shell;

  endl_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_mass,
					    interpolation_flag );

  endl_file_handler.readSecondTableHeader( reaction_type,
					     electron_shell );

  endl_file_handler.skipTable();

  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endl_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_mass,
					    interpolation_flag );
  FRENSIE_CHECK( endl_file_handler.endOfFile() );

  // Close the test table file
  endl_file_handler.closeENDLFile();
}

//---------------------------------------------------------------------------//
// Check that the ENDLFileHandler can process a two column table
FRENSIE_UNIT_TEST( ENDLFileHandler, processTwoColumnTable )
{
  Data::ENDLFileHandler endl_file_handler( two_column_table_test_file, epics_file_type );

  int atomic_number;
  int outgoing_particle_designator;
  double atomic_mass;
  int interpolation_flag;
  int reaction_type;
  int electron_shell;

  endl_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_mass,
					    interpolation_flag );

  endl_file_handler.readSecondTableHeader( reaction_type,
					     electron_shell );

  std::vector<double> indep, dep, indep_true, dep_true;

  endl_file_handler.processTwoColumnTable( indep, dep );

  processTwoColumnTestingArray( indep_true, dep_true );

  FRENSIE_CHECK_EQUAL( indep, indep_true );
  FRENSIE_CHECK_EQUAL( dep, dep_true );

  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endl_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_mass,
					    interpolation_flag );
  FRENSIE_CHECK( endl_file_handler.endOfFile() );

  // Close the test table file
  endl_file_handler.closeENDLFile();
}

//---------------------------------------------------------------------------//
// Check that the ENDLFileHandler can process a three column table
FRENSIE_UNIT_TEST( ENDLFileHandler, processThreeColumnTable )
{
  Data::ENDLFileHandler endl_file_handler( three_column_table_test_file, epics_file_type );

  int atomic_number;
  int outgoing_particle_designator;
  double atomic_mass;
  int interpolation_flag;
  int reaction_type;
  int electron_shell;

  endl_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_mass,
					    interpolation_flag );

  endl_file_handler.readSecondTableHeader( reaction_type,
					     electron_shell );

  std::vector<double> column_one, column_two, column_three;
  std::vector<double> column_one_true, column_two_true, column_three_true;

  endl_file_handler.processThreeColumnTable(
                        column_one,
                        column_two,
                        column_three );

  processThreeColumnTestingArray(
    column_one_true,
    column_two_true,
    column_three_true );

  FRENSIE_CHECK_FLOATING_EQUALITY( column_one, column_one_true, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( column_two, column_two_true, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( column_three, column_three_true, tol );

  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endl_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_mass,
					    interpolation_flag );
  FRENSIE_CHECK( endl_file_handler.endOfFile() );

  // Close the test table file
  endl_file_handler.closeENDLFile();
}

//---------------------------------------------------------------------------//
// Check that the ENDLFileHandler can process a four column table
FRENSIE_UNIT_TEST( ENDLFileHandler, processFourColumnTable )
{
  Data::ENDLFileHandler endl_file_handler( four_column_table_test_file, epics_file_type );

  int atomic_number;
  int outgoing_particle_designator;
  double atomic_mass;
  int interpolation_flag;
  int reaction_type;
  int electron_shell;

  endl_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_mass,
					    interpolation_flag );

  endl_file_handler.readSecondTableHeader( reaction_type,
					     electron_shell );

  std::vector<double> column_one, column_two, column_three, column_four;
  std::vector<double> column_one_true, column_two_true, column_three_true, column_four_true;

  endl_file_handler.processFourColumnTable(
                        column_one,
                        column_two,
                        column_three,
                        column_four );

  processFourColumnTestingArray(
    column_one_true,
    column_two_true,
    column_three_true,
    column_four_true );

  FRENSIE_CHECK_FLOATING_EQUALITY( column_one, column_one_true, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( column_two, column_two_true, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( column_three, column_three_true, tol );
  FRENSIE_CHECK_FLOATING_EQUALITY( column_four, column_four_true, tol );

  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endl_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_mass,
					    interpolation_flag );
  FRENSIE_CHECK( endl_file_handler.endOfFile() );

  // Close the test table file
  endl_file_handler.closeENDLFile();
}

//---------------------------------------------------------------------------//
// Check that the ENDLFileHandler can map a two column table
FRENSIE_UNIT_TEST( ENDLFileHandler, mapTwoColumnTable )
{
  Data::ENDLFileHandler endl_file_handler( two_column_table_test_file, epics_file_type );

  int atomic_number;
  int outgoing_particle_designator;
  double atomic_mass;
  int interpolation_flag;
  int reaction_type;
  int electron_shell;

  endl_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_mass,
					    interpolation_flag );

  endl_file_handler.readSecondTableHeader( reaction_type,
					     electron_shell );

  std::vector<unsigned> indep(2), indep_true;
  std::map<unsigned,unsigned> dep, dep_true;

  endl_file_handler.mapTwoColumnTable( indep, dep );

  mapTwoColumnTestingArray( indep_true, dep_true );

  FRENSIE_CHECK_EQUAL( indep, indep_true );

  std::vector<unsigned>::iterator i = indep.begin();

  for ( i; i != indep.end(); ++i )
  {
    FRENSIE_CHECK_EQUAL( dep[*i], dep_true[*i] );
  }

  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endl_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_mass,
					    interpolation_flag );
  FRENSIE_CHECK( endl_file_handler.endOfFile() );

  // Close the test table file
  endl_file_handler.closeENDLFile();
}

//---------------------------------------------------------------------------//
// Check that the ENDLFileHandler can map a three column table
FRENSIE_UNIT_TEST( ENDLFileHandler, mapThreeColumnTable )
{
  Data::ENDLFileHandler endl_file_handler( three_column_table_test_file, epics_file_type );

  int atomic_number;
  int outgoing_particle_designator;
  double atomic_mass;
  int interpolation_flag;
  int reaction_type;
  int electron_shell;

  endl_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_mass,
					    interpolation_flag );

  endl_file_handler.readSecondTableHeader( reaction_type,
					     electron_shell );

  std::vector<unsigned> bin, bin_true;
  std::map<unsigned,double> indep, dep, indep_true, dep_true;

  endl_file_handler.mapThreeColumnTable( bin, indep, dep );

  mapThreeColumnTestingArray( bin_true, indep_true, dep_true );

  FRENSIE_CHECK_FLOATING_EQUALITY( bin, bin_true, tol );

  std::vector<unsigned>::iterator i = bin.begin();

  for ( i; i != bin.end(); ++i )
  {
    FRENSIE_CHECK_EQUAL( indep[*i], indep_true[*i] );
    FRENSIE_CHECK_EQUAL( dep[*i], dep_true[*i] );
  }

  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endl_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_mass,
					    interpolation_flag );
  FRENSIE_CHECK( endl_file_handler.endOfFile() );

  // Close the test table file
  endl_file_handler.closeENDLFile();
}

//---------------------------------------------------------------------------//
// Check that the ENDLFileHandler can map a three column table of vectors
FRENSIE_UNIT_TEST( ENDLFileHandler, mapThreeColumnTable_vector )
{
  Data::ENDLFileHandler endl_file_handler(
    three_column_table_test_file_vector,
    epics_file_type );

  int atomic_number;
  int outgoing_particle_designator;
  double atomic_mass;
  int interpolation_flag;
  int reaction_type;
  int electron_shell;

  endl_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_mass,
					    interpolation_flag );

  endl_file_handler.readSecondTableHeader( reaction_type,
					     electron_shell );

  std::vector<double> bin, bin_true;
  std::map<double,std::vector<double> > indep, dep, indep_true, dep_true;

  endl_file_handler.mapThreeColumnTable( bin, indep, dep );

  mapThreeColumnTestingArray( bin_true, indep_true, dep_true );

  FRENSIE_CHECK_FLOATING_EQUALITY( bin, bin_true, tol );

  std::vector<double>::iterator i = bin.begin();

  for ( i; i != bin.end(); ++i )
  {
    FRENSIE_CHECK_FLOATING_EQUALITY( indep[*i], indep_true[*i], tol );
    FRENSIE_CHECK_FLOATING_EQUALITY( dep[*i], dep_true[*i], tol );
  }

  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endl_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_mass,
					    interpolation_flag );
  FRENSIE_CHECK( endl_file_handler.endOfFile() );

  // Close the test table file
  endl_file_handler.closeENDLFile();
}
/*
//---------------------------------------------------------------------------//
// Check that the ENDLFileHandler can map a four column table
FRENSIE_UNIT_TEST( ENDLFileHandler, mapFourColumnTable )
{
  Data::ENDLFileHandler endl_file_handler( four_column_table_test_file, epics_file_type );

  int atomic_number;
  int outgoing_particle_designator;
  double atomic_mass;
  int interpolation_flag;
  int reaction_type;
  int electron_shell;

  endl_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_mass,
					    interpolation_flag );

  endl_file_handler.readSecondTableHeader( reaction_type,
					     electron_shell );

  std::vector<unsigned> bin, bin_true;
  std::map<unsigned,vector<unsigned> > secondary_bin, secondary_bin_true;
  std::map<unsigned,std::map<unsigned,double> > indep, dep, indep_true, dep_true;

  endl_file_handler.mapFourColumnTable( bin, secondary_bin, indep, dep );

  mapFourColumnTestingArray( bin_true, secondary_bin_true, indep_true, dep_true );


  FRENSIE_CHECK_EQUAL( bin, bin_true );

  for ( int i = 0; i < bin.size(); ++i )
  {
    double indep_result, true_indep_result;
    indep_result = indep.find(bin[i])->second.find(secondary_bin[i])->second;
    true_indep_result = indep_true.find(bin[i])->second.find(secondary_bin[i])->second;

    FRENSIE_CHECK_EQUAL( indep_result, true_indep_result );
  }

  FRENSIE_CHECK_EQUAL( secondary_bin, secondary_bin_true );

  for ( int i = 0; i < bin.size(); ++i )
  {
    double dep_result, true_dep_result;
    dep_result = dep.find(bin[i])->second.find(secondary_bin[i])->second;
    true_dep_result = dep_true.find(bin[i])->second.find(secondary_bin[i])->second;

    FRENSIE_CHECK_EQUAL( dep_result, true_dep_result );
  }

  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endl_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_mass,
					    interpolation_flag );
  FRENSIE_CHECK( endl_file_handler.endOfFile() );

  // Close the test table file
  endl_file_handler.closeENDLFile();
}
*/
//---------------------------------------------------------------------------//
// Check that the ENDLFileHandler can skip a table and then skip a second table
FRENSIE_UNIT_TEST( ENDLFileHandler, skip_skip_test )
{
  Data::ENDLFileHandler endl_file_handler( two_two_column_tables_test_file, epics_file_type );

  int atomic_number_1, atomic_number_2;
  int outgoing_particle_designator_1, outgoing_particle_designator_2;
  double atomic_mass_1, atomic_mass_2;
  int interpolation_flag_1, interpolation_flag_2;
  int reaction_type_1, reaction_type_2;
  int electron_shell_1, electron_shell_2;

  endl_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_mass_1,
					    interpolation_flag_1 );

  endl_file_handler.readSecondTableHeader( reaction_type_1,
					     electron_shell_1 );

  // Skip the first table
  endl_file_handler.skipTable();

  endl_file_handler.readFirstTableHeader( atomic_number_2,
					    outgoing_particle_designator_2,
					    atomic_mass_2,
					    interpolation_flag_2 );

  endl_file_handler.readSecondTableHeader( reaction_type_2,
					     electron_shell_2 );
  // Check that the header info from both tables matches
  FRENSIE_CHECK_EQUAL( atomic_number_1, atomic_number_2 );
  FRENSIE_CHECK_EQUAL( outgoing_particle_designator_1,
		 outgoing_particle_designator_2 );
  FRENSIE_CHECK_EQUAL( atomic_mass_1, atomic_mass_2 );
  FRENSIE_CHECK_EQUAL( interpolation_flag_1, interpolation_flag_2 );
  FRENSIE_CHECK_EQUAL( reaction_type_1, reaction_type_2 );
  FRENSIE_CHECK_EQUAL( electron_shell_1, electron_shell_2 );

  // Skip the second table
  endl_file_handler.skipTable();

  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endl_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_mass_1,
					    interpolation_flag_1 );
  FRENSIE_CHECK( endl_file_handler.endOfFile() );

  // Close the test table file
  endl_file_handler.closeENDLFile();
}

//---------------------------------------------------------------------------//
// Check that the ENDLFileHandler can skip a table and then
// process a two column table
FRENSIE_UNIT_TEST( ENDLFileHandler, two_column_table_skip_process_test )
{
  Data::ENDLFileHandler endl_file_handler( two_two_column_tables_test_file, epics_file_type );

  int atomic_number_1, atomic_number_2;
  int outgoing_particle_designator_1, outgoing_particle_designator_2;
  double atomic_mass_1, atomic_mass_2;
  int interpolation_flag_1, interpolation_flag_2;
  int reaction_type_1, reaction_type_2;
  int electron_shell_1, electron_shell_2;

  endl_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_mass_1,
					    interpolation_flag_1 );

  endl_file_handler.readSecondTableHeader( reaction_type_1,
					     electron_shell_1 );

  // Skip the first table
  endl_file_handler.skipTable();

  endl_file_handler.readFirstTableHeader( atomic_number_2,
					    outgoing_particle_designator_2,
					    atomic_mass_2,
					    interpolation_flag_2 );

  endl_file_handler.readSecondTableHeader( reaction_type_2,
					     electron_shell_2 );

  // Check that the header info from both tables matches
  FRENSIE_CHECK_EQUAL( atomic_number_1, atomic_number_2 );
  FRENSIE_CHECK_EQUAL( outgoing_particle_designator_1,
		 outgoing_particle_designator_2 );
  FRENSIE_CHECK_EQUAL( atomic_mass_1, atomic_mass_2 );
  FRENSIE_CHECK_EQUAL( interpolation_flag_1, interpolation_flag_2 );
  FRENSIE_CHECK_EQUAL( reaction_type_1, reaction_type_2 );
  FRENSIE_CHECK_EQUAL( electron_shell_1, electron_shell_2 );

  std::vector<double> column_1, column_2;

  // process the second table
  endl_file_handler.processTwoColumnTable( column_1, column_2 );

  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endl_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_mass_1,
					    interpolation_flag_1 );
  FRENSIE_CHECK( endl_file_handler.endOfFile() );

  // Close the test table file
  endl_file_handler.closeENDLFile();
}

//---------------------------------------------------------------------------//
// Check that the ENDLFileHandler can process a two column table and then
// skip a table
FRENSIE_UNIT_TEST( ENDLFileHandler, two_column_table_process_skip_test )
{
  Data::ENDLFileHandler endl_file_handler( two_two_column_tables_test_file, epics_file_type );

  int atomic_number_1, atomic_number_2;
  int outgoing_particle_designator_1, outgoing_particle_designator_2;
  double atomic_mass_1, atomic_mass_2;
  int interpolation_flag_1, interpolation_flag_2;
  int reaction_type_1, reaction_type_2;
  int electron_shell_1, electron_shell_2;

  endl_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_mass_1,
					    interpolation_flag_1 );

  endl_file_handler.readSecondTableHeader( reaction_type_1,
					     electron_shell_1 );

  std::vector<double> column_1, column_2;

  // process the second table
  endl_file_handler.processTwoColumnTable( column_1, column_2 );

  endl_file_handler.readFirstTableHeader( atomic_number_2,
					    outgoing_particle_designator_2,
					    atomic_mass_2,
					    interpolation_flag_2 );

  endl_file_handler.readSecondTableHeader( reaction_type_2,
					     electron_shell_2 );

  // Skip the second table
  endl_file_handler.skipTable();

  // Check that the header info from both tables matches
  FRENSIE_CHECK_EQUAL( atomic_number_1, atomic_number_2 );
  FRENSIE_CHECK_EQUAL( outgoing_particle_designator_1,
		 outgoing_particle_designator_2 );
  FRENSIE_CHECK_EQUAL( atomic_mass_1, atomic_mass_2 );
  FRENSIE_CHECK_EQUAL( interpolation_flag_1, interpolation_flag_2 );
  FRENSIE_CHECK_EQUAL( reaction_type_1, reaction_type_2 );
  FRENSIE_CHECK_EQUAL( electron_shell_1, electron_shell_2 );

  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endl_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_mass_1,
					    interpolation_flag_1 );
  FRENSIE_CHECK( endl_file_handler.endOfFile() );

  // Close the test table file
  endl_file_handler.closeENDLFile();
}

//---------------------------------------------------------------------------//
// Check that the ENDLFileHandler can process a two column table and then
// process a two column table
FRENSIE_UNIT_TEST( ENDLFileHandler, two_column_table_process_process_test )
{
  Data::ENDLFileHandler endl_file_handler( two_two_column_tables_test_file, epics_file_type );

  int atomic_number_1, atomic_number_2;
  int outgoing_particle_designator_1, outgoing_particle_designator_2;
  double atomic_mass_1, atomic_mass_2;
  int interpolation_flag_1, interpolation_flag_2;
  int reaction_type_1, reaction_type_2;
  int electron_shell_1, electron_shell_2;
  std::vector<double> column_11, column_12, column_21, column_22;


  endl_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_mass_1,
					    interpolation_flag_1 );

  endl_file_handler.readSecondTableHeader( reaction_type_1,
					     electron_shell_1 );

  // process the second table
  endl_file_handler.processTwoColumnTable( column_11, column_12 );

  endl_file_handler.readFirstTableHeader( atomic_number_2,
					    outgoing_particle_designator_2,
					    atomic_mass_2,
					    interpolation_flag_2 );

  endl_file_handler.readSecondTableHeader( reaction_type_2,
					     electron_shell_2 );

  // process the second table
  endl_file_handler.processTwoColumnTable( column_21, column_22 );

  // Check that the header info from both tables matches
  FRENSIE_CHECK_EQUAL( atomic_number_1, atomic_number_2 );
  FRENSIE_CHECK_EQUAL( outgoing_particle_designator_1,
		 outgoing_particle_designator_2 );
  FRENSIE_CHECK_EQUAL( atomic_mass_1, atomic_mass_2 );
  FRENSIE_CHECK_EQUAL( interpolation_flag_1, interpolation_flag_2 );
  FRENSIE_CHECK_EQUAL( reaction_type_1, reaction_type_2 );
  FRENSIE_CHECK_EQUAL( electron_shell_1, electron_shell_2 );
  FRENSIE_CHECK_EQUAL( column_21, column_11 );
  FRENSIE_CHECK_EQUAL( column_22, column_12 );

  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endl_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_mass_1,
					    interpolation_flag_1 );
  FRENSIE_CHECK( endl_file_handler.endOfFile() );

  // Close the test table file
  endl_file_handler.closeENDLFile();
}

//---------------------------------------------------------------------------//
// Check that the ENDLFileHandler can skip a three column table and then
// process a three column table
FRENSIE_UNIT_TEST( ENDLFileHandler, three_column_table_skip_process_test )
{
  Data::ENDLFileHandler endl_file_handler( two_three_column_tables_test_file, epics_file_type );

  int atomic_number_1, atomic_number_2;
  int outgoing_particle_designator_1, outgoing_particle_designator_2;
  double atomic_mass_1, atomic_mass_2;
  int interpolation_flag_1, interpolation_flag_2;
  int reaction_type_1, reaction_type_2;
  int electron_shell_1, electron_shell_2;

  endl_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_mass_1,
					    interpolation_flag_1 );

  endl_file_handler.readSecondTableHeader( reaction_type_1,
					     electron_shell_1 );

  // Skip the first table
  endl_file_handler.skipTable();

  endl_file_handler.readFirstTableHeader( atomic_number_2,
					    outgoing_particle_designator_2,
					    atomic_mass_2,
					    interpolation_flag_2 );

  endl_file_handler.readSecondTableHeader( reaction_type_2,
					     electron_shell_2 );

  std::vector<double> column_1;
  std::map<double,std::vector<double> > column_2, column_3;

  // process the second table
  endl_file_handler.mapThreeColumnTable( column_1, column_2, column_3 );


  // Check that the header info from both tables matches
  FRENSIE_CHECK_EQUAL( atomic_number_1, atomic_number_2 );
  FRENSIE_CHECK_EQUAL( outgoing_particle_designator_1,
		 outgoing_particle_designator_2 );
  FRENSIE_CHECK_EQUAL( atomic_mass_1, atomic_mass_2 );
  FRENSIE_CHECK_EQUAL( interpolation_flag_1, interpolation_flag_2 );
  FRENSIE_CHECK_EQUAL( reaction_type_1, reaction_type_2 );
  FRENSIE_CHECK_EQUAL( electron_shell_1, electron_shell_2 );

  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endl_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_mass_1,
					    interpolation_flag_1 );
  FRENSIE_CHECK( endl_file_handler.endOfFile() );

  // Close the test table file
  endl_file_handler.closeENDLFile();
}

//---------------------------------------------------------------------------//
// Check that the ENDLFileHandler can process a three column table and then
// skip a three column table
FRENSIE_UNIT_TEST( ENDLFileHandler, three_column_table_process_skip_test )
{
  Data::ENDLFileHandler endl_file_handler( two_three_column_tables_test_file, epics_file_type );

  int atomic_number_1, atomic_number_2;
  int outgoing_particle_designator_1, outgoing_particle_designator_2;
  double atomic_mass_1, atomic_mass_2;
  int interpolation_flag_1, interpolation_flag_2;
  int reaction_type_1, reaction_type_2;
  int electron_shell_1, electron_shell_2;

  endl_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_mass_1,
					    interpolation_flag_1 );

  endl_file_handler.readSecondTableHeader( reaction_type_1,
					     electron_shell_1 );

  std::vector<double> column_1;
  std::map<double,std::vector<double> > column_2, column_3;

  // process the second table
  endl_file_handler.mapThreeColumnTable( column_1, column_2, column_3 );

  endl_file_handler.readFirstTableHeader( atomic_number_2,
					    outgoing_particle_designator_2,
					    atomic_mass_2,
					    interpolation_flag_2 );

  endl_file_handler.readSecondTableHeader( reaction_type_2,
					     electron_shell_2 );

  // Skip the second table
  endl_file_handler.skipTable();

  // Check that the header info from both tables matches
  FRENSIE_CHECK_EQUAL( atomic_number_1, atomic_number_2 );
  FRENSIE_CHECK_EQUAL( outgoing_particle_designator_1,
		 outgoing_particle_designator_2 );
  FRENSIE_CHECK_EQUAL( atomic_mass_1, atomic_mass_2 );
  FRENSIE_CHECK_EQUAL( interpolation_flag_1, interpolation_flag_2 );
  FRENSIE_CHECK_EQUAL( reaction_type_1, reaction_type_2 );
  FRENSIE_CHECK_EQUAL( electron_shell_1, electron_shell_2 );

  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endl_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_mass_1,
					    interpolation_flag_1 );
  FRENSIE_CHECK( endl_file_handler.endOfFile() );

  // Close the test table file
  endl_file_handler.closeENDLFile();
}

//---------------------------------------------------------------------------//
// Check that the ENDLFileHandler can process a three column table and then
// process a three column table
FRENSIE_UNIT_TEST( ENDLFileHandler, three_column_table_process_process_test )
{
  Data::ENDLFileHandler endl_file_handler( two_three_column_tables_test_file, epics_file_type );

  int atomic_number_1, atomic_number_2;
  int outgoing_particle_designator_1, outgoing_particle_designator_2;
  double atomic_mass_1, atomic_mass_2;
  int interpolation_flag_1, interpolation_flag_2;
  int reaction_type_1, reaction_type_2;
  int electron_shell_1, electron_shell_2;

  endl_file_handler.readFirstTableHeader( atomic_number_1,
				       outgoing_particle_designator_1,
				       atomic_mass_1,
				       interpolation_flag_1 );

  endl_file_handler.readSecondTableHeader( reaction_type_1,
					electron_shell_1 );

  std::vector<double> column_11;
  std::map<double,std::vector<double> > column_12, column_13;

  // process the second table
  endl_file_handler.mapThreeColumnTable( column_11, column_12, column_13 );

  endl_file_handler.readFirstTableHeader( atomic_number_2,
					    outgoing_particle_designator_2,
					    atomic_mass_2,
					    interpolation_flag_2 );

  endl_file_handler.readSecondTableHeader( reaction_type_2,
					     electron_shell_2 );

  std::vector<double> column_21;
  std::map<double,std::vector<double> > column_22, column_23;

  // process the second table
  endl_file_handler.mapThreeColumnTable( column_21, column_22, column_23 );

  // Check that the header info from both tables matches
  FRENSIE_CHECK_EQUAL( atomic_number_1, atomic_number_2 );
  FRENSIE_CHECK_EQUAL( outgoing_particle_designator_1,
		 outgoing_particle_designator_2 );
  FRENSIE_CHECK_EQUAL( atomic_mass_1, atomic_mass_2 );
  FRENSIE_CHECK_EQUAL( interpolation_flag_1, interpolation_flag_2 );
  FRENSIE_CHECK_EQUAL( reaction_type_1, reaction_type_2 );
  FRENSIE_CHECK_EQUAL( electron_shell_1, electron_shell_2 );
  FRENSIE_CHECK_EQUAL( column_21, column_11 );

  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endl_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_mass_1,
					    interpolation_flag_1 );
  FRENSIE_CHECK( endl_file_handler.endOfFile() );

  // Close the test table file
  endl_file_handler.closeENDLFile();
}

//---------------------------------------------------------------------------//
// Check that the ENDLFileHandler can skip a four column table and then
// process a four column table
FRENSIE_UNIT_TEST( ENDLFileHandler, four_column_table_skip_process_test )
{
  Data::ENDLFileHandler endl_file_handler( two_four_column_tables_test_file, epics_file_type );

  int atomic_number_1, atomic_number_2;
  int outgoing_particle_designator_1, outgoing_particle_designator_2;
  double atomic_mass_1, atomic_mass_2;
  int interpolation_flag_1, interpolation_flag_2;
  int reaction_type_1, reaction_type_2;
  int electron_shell_1, electron_shell_2;

  endl_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_mass_1,
					    interpolation_flag_1 );

  endl_file_handler.readSecondTableHeader( reaction_type_1,
					     electron_shell_1 );

  // Skip the first table
  endl_file_handler.skipTable();

  endl_file_handler.readFirstTableHeader( atomic_number_2,
					    outgoing_particle_designator_2,
					    atomic_mass_2,
					    interpolation_flag_2 );

  endl_file_handler.readSecondTableHeader( reaction_type_2,
					     electron_shell_2 );

  std::vector<double> column_1, column_2, column_3, column_4;

  // process the second table
  endl_file_handler.processFourColumnTable( column_1, column_2, column_3, column_4 );


  // Check that the header info from both tables matches
  FRENSIE_CHECK_EQUAL( atomic_number_1, atomic_number_2 );
  FRENSIE_CHECK_EQUAL( outgoing_particle_designator_1,
		 outgoing_particle_designator_2 );
  FRENSIE_CHECK_EQUAL( atomic_mass_1, atomic_mass_2 );
  FRENSIE_CHECK_EQUAL( interpolation_flag_1, interpolation_flag_2 );
  FRENSIE_CHECK_EQUAL( reaction_type_1, reaction_type_2 );
  FRENSIE_CHECK_EQUAL( electron_shell_1, electron_shell_2 );

  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endl_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_mass_1,
					    interpolation_flag_1 );
  FRENSIE_CHECK( endl_file_handler.endOfFile() );

  // Close the test table file
  endl_file_handler.closeENDLFile();
}

//---------------------------------------------------------------------------//
// Check that the ENDLFileHandler can process a four column table and then
// skip a four column table
FRENSIE_UNIT_TEST( ENDLFileHandler, four_column_table_process_skip_test )
{
  Data::ENDLFileHandler endl_file_handler( two_four_column_tables_test_file, epics_file_type );

  int atomic_number_1, atomic_number_2;
  int outgoing_particle_designator_1, outgoing_particle_designator_2;
  double atomic_mass_1, atomic_mass_2;
  int interpolation_flag_1, interpolation_flag_2;
  int reaction_type_1, reaction_type_2;
  int electron_shell_1, electron_shell_2;

  endl_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_mass_1,
					    interpolation_flag_1 );

  endl_file_handler.readSecondTableHeader( reaction_type_1,
					     electron_shell_1 );

  std::vector<double> column_1, column_2, column_3, column_4;

  // process the second table
  endl_file_handler.processFourColumnTable( column_1, column_2, column_3, column_4 );

  endl_file_handler.readFirstTableHeader( atomic_number_2,
					    outgoing_particle_designator_2,
					    atomic_mass_2,
					    interpolation_flag_2 );

  endl_file_handler.readSecondTableHeader( reaction_type_2,
					     electron_shell_2 );

  // Skip the second table
  endl_file_handler.skipTable();

  // Check that the header info from both tables matches
  FRENSIE_CHECK_EQUAL( atomic_number_1, atomic_number_2 );
  FRENSIE_CHECK_EQUAL( outgoing_particle_designator_1,
		 outgoing_particle_designator_2 );
  FRENSIE_CHECK_EQUAL( atomic_mass_1, atomic_mass_2 );
  FRENSIE_CHECK_EQUAL( interpolation_flag_1, interpolation_flag_2 );
  FRENSIE_CHECK_EQUAL( reaction_type_1, reaction_type_2 );
  FRENSIE_CHECK_EQUAL( electron_shell_1, electron_shell_2 );

  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endl_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_mass_1,
					    interpolation_flag_1 );
  FRENSIE_CHECK( endl_file_handler.endOfFile() );

  // Close the test table file
  endl_file_handler.closeENDLFile();
}

//---------------------------------------------------------------------------//
// Check that the ENDLFileHandler can process a four column table and then
// process a four column table
FRENSIE_UNIT_TEST( ENDLFileHandler, four_column_table_process_process_test )
{
  Data::ENDLFileHandler endl_file_handler( two_four_column_tables_test_file, epics_file_type );

  int atomic_number_1, atomic_number_2;
  int outgoing_particle_designator_1, outgoing_particle_designator_2;
  double atomic_mass_1, atomic_mass_2;
  int interpolation_flag_1, interpolation_flag_2;
  int reaction_type_1, reaction_type_2;
  int electron_shell_1, electron_shell_2;

  endl_file_handler.readFirstTableHeader( atomic_number_1,
				       outgoing_particle_designator_1,
				       atomic_mass_1,
				       interpolation_flag_1 );

  endl_file_handler.readSecondTableHeader( reaction_type_1,
					electron_shell_1 );

  std::vector<double> column_11, column_12, column_13, column_14;

  // process the second table
  endl_file_handler.processFourColumnTable( column_11, column_12, column_13, column_14 );

  endl_file_handler.readFirstTableHeader( atomic_number_2,
					    outgoing_particle_designator_2,
					    atomic_mass_2,
					    interpolation_flag_2 );

  endl_file_handler.readSecondTableHeader( reaction_type_2,
					     electron_shell_2 );

  std::vector<double> column_21, column_22, column_23, column_24;

  // process the second table
  endl_file_handler.processFourColumnTable( column_21, column_22, column_23, column_24 );

  // Check that the header info from both tables matches
  FRENSIE_CHECK_EQUAL( atomic_number_1, atomic_number_2 );
  FRENSIE_CHECK_EQUAL( outgoing_particle_designator_1,
		 outgoing_particle_designator_2 );
  FRENSIE_CHECK_EQUAL( atomic_mass_1, atomic_mass_2 );
  FRENSIE_CHECK_EQUAL( interpolation_flag_1, interpolation_flag_2 );
  FRENSIE_CHECK_EQUAL( reaction_type_1, reaction_type_2 );
  FRENSIE_CHECK_EQUAL( electron_shell_1, electron_shell_2 );
  FRENSIE_CHECK_EQUAL( column_21, column_11 );

  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endl_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_mass_1,
					    interpolation_flag_1 );
  FRENSIE_CHECK( endl_file_handler.endOfFile() );

  // Close the test table file
  endl_file_handler.closeENDLFile();
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "first_header_test_file",
                                        first_header_test_file, "",
                                        "First header test file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "second_header_test_file",
                                        second_header_test_file, "",
                                        "Second header test file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "full_header_test_file",
                                        full_header_test_file, "",
                                        "Full header test file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "two_column_table_test_file",
                                        two_column_table_test_file, "",
                                        "Two column table test file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "three_column_table_test_file",
                                        three_column_table_test_file, "",
                                        "Three column table test file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "three_column_table_test_file_vector",
                                        three_column_table_test_file_vector, "",
                                        "Three column table test file name vector" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "four_column_table_test_file",
                                        four_column_table_test_file, "",
                                        "Four column table test file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "two_two_column_tables_test_file",
                                        two_two_column_tables_test_file, "",
                                        "Two two column tables test file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "two_three_column_tables_test_file",
                                        two_three_column_tables_test_file, "",
                                        "Two three column tables test file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "two_four_column_tables_test_file",
                                        two_four_column_tables_test_file, "",
                                        "Two four column tables test file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstEPICSFileHandler.cpp
//---------------------------------------------------------------------------//

