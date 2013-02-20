//---------------------------------------------------------------------------//
// \file   tstEPDL97DataProcessor.cpp
// \author Alex Robinson
// \brief  EPDL97DataProcessor base class unit tests.
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <stdio.h>
#include <fstream>
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FACEMC Includes
#include "EPDL97DataProcessor.hpp"

//---------------------------------------------------------------------------//
// Testing Stucts.
//---------------------------------------------------------------------------//
class TestDataProcessor : public FACEMC::EPDL97DataProcessor
{
public:
  TestDataProcessor()
    : EPDL97DataProcessor()
  { /* ... */ }
  
  void processDataFiles()
  { /* ... */ }
  
  // Allow public access to EPDL97DataProcessor protected member functions
  using FACEMC::EPDL97DataProcessor::readFirstTableHeader;
  using FACEMC::EPDL97DataProcessor::readSecondTableHeader;
  using FACEMC::EPDL97DataProcessor::skipTwoColumnTable;
  using FACEMC::EPDL97DataProcessor::readTwoColumnTableInRange;
  using FACEMC::EPDL97DataProcessor::readTwoColumnTable;
  using FACEMC::EPDL97DataProcessor::skipThreeColumnTable;
  using FACEMC::EPDL97DataProcessor::readThreeColumnTable;
  using FACEMC::EPDL97DataProcessor::skipFourColumnTable;
  using FACEMC::EPDL97DataProcessor::readFourColumnTable;
  using FACEMC::EPDL97DataProcessor::extractValue;
  using FACEMC::EPDL97DataProcessor::uintToShellStr;
  using FACEMC::EPDL97DataProcessor::LogLogDataProcessingPolicy;
  using FACEMC::EPDL97DataProcessor::LinearLogDataProcessingPolicy;
  using FACEMC::EPDL97DataProcessor::LogLinearDataProcessingPolicy;
  using FACEMC::EPDL97DataProcessor::LinearLinearDataProcessingPolicy;
};  

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the EPDL97DataProcessor can extract a double from a FORTRAN
// fixed field float
TEUCHOS_UNIT_TEST( EPDL97DataProcessor, extract_double_test )
{
  std::string mantissa_with_pos(" 1.00000+");
  std::string mantissa_with_neg(" 1.00000-");
  std::string exponent("10");

  std::string mantissa(" 1.000000");
  std::string exponent_with_pos("+2");
  std::string exponent_with_neg("-2");
  
  TestDataProcessor data_processor;
  
  // test all possible mantissa, exponent combinations
  double combination_1;
  double combination_2;
  double combination_3;
  double combination_4;
  
  combination_1 = data_processor.extractValue<double>( mantissa_with_pos,
						       exponent );
  combination_2 = data_processor.extractValue<double>( mantissa_with_neg,
						       exponent );
  combination_3 = data_processor.extractValue<double>( mantissa,
						       exponent_with_pos );
  combination_4 = data_processor.extractValue<double>( mantissa,
						       exponent_with_neg );

  double true_value_1 = 1e10;
  double true_value_2 = 1e-10;
  double true_value_3 = 1e2;
  double true_value_4 = 1e-2;
  
  TEST_FLOATING_EQUALITY( combination_1, true_value_1, 1e-12 );
  TEST_FLOATING_EQUALITY( combination_2, true_value_2, 1e-12 );
  TEST_FLOATING_EQUALITY( combination_3, true_value_3, 1e-12 );
  TEST_FLOATING_EQUALITY( combination_4, true_value_4, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the EPDL97DataProcessor can extract an int from a FORTRAN
// fixed field float
TEUCHOS_UNIT_TEST( EPDL97DataProcessor, extract_int_test )
{
  std::string mantissa_with_pos(" 1.00000+");
  std::string exponent(" 0");

  std::string mantissa(" 1.100000");
  std::string exponent_with_pos("+1");
  
  TestDataProcessor data_processor;
  
  // test all possible mantissa, exponent combinations
  double combination_1;
  double combination_2;
  
  combination_1 = data_processor.extractValue<int>( mantissa_with_pos,
						    exponent );
  combination_2 = data_processor.extractValue<int>( mantissa,
						    exponent_with_pos );

  int true_value_1 = 1;
  int true_value_2 = 11;
  
  TEST_EQUALITY( combination_1, true_value_1 );
  TEST_EQUALITY( combination_2, true_value_2 );
}

//---------------------------------------------------------------------------//
// Check that the EPDL97DataProcessor can extract an unsigned int from a FORTRAN
// fixed field float
TEUCHOS_UNIT_TEST( EPDL97DataProcessor, extract_uint_test )
{
  std::string mantissa_with_pos(" 1.00000+");
  std::string exponent(" 0");

  std::string mantissa(" 1.100000");
  std::string exponent_with_pos("+1");
  
  TestDataProcessor data_processor;
  
  // test all possible mantissa, exponent combinations
  double combination_1;
  double combination_2;
  
  combination_1 = data_processor.extractValue<unsigned int>( mantissa_with_pos,
							     exponent );
  combination_2 = data_processor.extractValue<unsigned int>( mantissa,
							     exponent_with_pos );

  unsigned int true_value_1 = 1;
  unsigned int true_value_2 = 11;
  
  TEST_EQUALITY( combination_1, true_value_1 );
  TEST_EQUALITY( combination_2, true_value_2 );
}

//---------------------------------------------------------------------------//
// Check that the EPDL97DataProcessor can read the first header of a table
TEUCHOS_UNIT_TEST( EPDL97DataProcessor, first_table_header_read_test )
{
  
  std::ifstream test_headerfile;
  test_headerfile.open( "test_first_header.txt", std::fstream::in );
  TEST_ASSERT( test_headerfile.is_open() );

  TestDataProcessor data_processor;

  // Values to read from the header
  unsigned int atomic_number, atomic_number_true = 99;
  unsigned int outgoing_particle_designator,
    outgoing_particle_designator_true = 0;
  double atomic_weight, atomic_weight_true = 252.0;
  unsigned int interpolation_flag, interpolation_flag_true = 5;

  // Read the test header file containing an typical first header
  data_processor.readFirstTableHeader( test_headerfile,
				       atomic_number,
				       outgoing_particle_designator,
				       atomic_weight,
				       interpolation_flag );
  
  // Test that the values read from the header match their expected values
  TEST_EQUALITY( atomic_number, atomic_number_true );

  TEST_EQUALITY( outgoing_particle_designator,
		 outgoing_particle_designator_true );

  TEST_FLOATING_EQUALITY( atomic_weight, atomic_weight_true, 1e-12 );

  TEST_EQUALITY( interpolation_flag, interpolation_flag_true );

  // Test that the entire header was read
  //  the EOF bit doesn't seem to be getting set so try reading from the stream
  std::string eof;
  std::getline( test_headerfile, eof );

  TEST_EQUALITY_CONST( eof.size(), 0 );

  // Close the test header file
  test_headerfile.close();

  // Close the test header file
  test_headerfile.close();
}

//---------------------------------------------------------------------------//
// Check that the EPDL97DataProcessor can read the second header of a table
TEUCHOS_UNIT_TEST( EPDL97DataProcessor, second_table_header_read_test )
{

  std::ifstream test_headerfile;
  test_headerfile.open( "test_second_header.txt", std::fstream::in );
  TEST_ASSERT( test_headerfile.is_open() );

  TestDataProcessor data_processor;

  // Values to read from the header
  unsigned int reaction_type, reaction_type_true = 73000;
  unsigned int electron_shell, electron_shell_true = 11;

  // Read the test header file containing an typical second header
  data_processor.readSecondTableHeader( test_headerfile,
					reaction_type,
					electron_shell );
  
  // Test that the values read from the header match their expected values
  TEST_EQUALITY( reaction_type, reaction_type_true );

  TEST_EQUALITY( electron_shell, electron_shell_true );

  // Test that the entire header was read
  //  the EOF bit doesn't seem to be getting set so try reading from the stream
  std::string eof;
  std::getline( test_headerfile, eof );

  TEST_EQUALITY_CONST( eof.size(), 0 );

  // Close the test header file
  test_headerfile.close();

  // Close the test header file
  test_headerfile.close();
}

//---------------------------------------------------------------------------//
// Check that the EPDL97DataProcessor can read the first header and
// second header of a table consecutively
TEUCHOS_UNIT_TEST( EPDL97DataProcessor, full_table_header_read_test )
{
  
  std::ifstream test_headerfile;
  test_headerfile.open( "test_full_header.txt", std::fstream::in );
  TEST_ASSERT( test_headerfile.is_open() );

  TestDataProcessor data_processor;

  // Values to read from the header
  unsigned int atomic_number, atomic_number_true = 70;
  unsigned int outgoing_particle_designator,
    outgoing_particle_designator_true = 0;
  double atomic_weight, atomic_weight_true = 173.04;
  unsigned int interpolation_flag, interpolation_flag_true = 5;
  unsigned int reaction_type, reaction_type_true = 73000;
  unsigned int electron_shell, electron_shell_true = 8;

  // Read the first header of the test header file
  data_processor.readFirstTableHeader( test_headerfile,
				       atomic_number,
				       outgoing_particle_designator,
				       atomic_weight,
				       interpolation_flag );

  // Read the second header of the test header file
  data_processor.readSecondTableHeader( test_headerfile,
					reaction_type,
					electron_shell );
  
  // Test that the values read from the header match their expected values
  TEST_EQUALITY( atomic_number, atomic_number_true );

  TEST_EQUALITY( outgoing_particle_designator,
		 outgoing_particle_designator_true );

  TEST_FLOATING_EQUALITY( atomic_weight, atomic_weight_true, 1e-12 );

  TEST_EQUALITY( interpolation_flag, interpolation_flag_true );

  TEST_EQUALITY( reaction_type, reaction_type_true );

  TEST_EQUALITY( electron_shell, electron_shell_true );

  // Test that the entire header was read
  //  the EOF bit doesn't seem to be getting set so try reading from the stream
  std::string eof;
  std::getline( test_headerfile, eof );

  TEST_EQUALITY_CONST( eof.size(), 0 );

  // Close the test header file
  test_headerfile.close();
}

//---------------------------------------------------------------------------//
// Check that the EPDL97DataProcessor can skip a two column table
TEUCHOS_UNIT_TEST( EPDL97DataProcessor, two_column_table_skip_test )
{
  std::ifstream test_tablefile;
  test_tablefile.open( "test_two_column_table.txt", std::fstream::in );
  TEST_ASSERT( test_tablefile.is_open() );

  TestDataProcessor data_processor;

  unsigned int atomic_number;
  unsigned int outgoing_particle_designator;
  double atomic_weight;
  unsigned int interpolation_flag;
  unsigned int reaction_type;
  unsigned int electron_shell;

  data_processor.readFirstTableHeader( test_tablefile,
				       atomic_number,
				       outgoing_particle_designator,
				       atomic_weight,
				       interpolation_flag );

  data_processor.readSecondTableHeader( test_tablefile,
					reaction_type,
					electron_shell );

  data_processor.skipTwoColumnTable( test_tablefile );
  
  // Test that the entire table was read
  //  the EOF bit doesn't seem to be getting set so try reading from the stream
  std::string eof;
  std::getline( test_tablefile, eof );

  TEST_EQUALITY_CONST( eof.size(), 0 );

  // Close the test table file
  test_tablefile.close();
}

//---------------------------------------------------------------------------//
// Check that the EPDL97DataProcessor can skip a three column table
TEUCHOS_UNIT_TEST( EPDL97DataProcessor, three_column_table_skip_test )
{
  std::ifstream test_tablefile;
  test_tablefile.open( "test_three_column_table.txt", std::fstream::in );
  TEST_ASSERT( test_tablefile.is_open() );

  TestDataProcessor data_processor;

  unsigned int atomic_number;
  unsigned int outgoing_particle_designator;
  double atomic_weight;
  unsigned int interpolation_flag;
  unsigned int reaction_type;
  unsigned int electron_shell;

  data_processor.readFirstTableHeader( test_tablefile,
				       atomic_number,
				       outgoing_particle_designator,
				       atomic_weight,
				       interpolation_flag );

  data_processor.readSecondTableHeader( test_tablefile,
					reaction_type,
					electron_shell );


  data_processor.skipThreeColumnTable( test_tablefile );

  // Test that the entire table was read
  //  the EOF bit doesn't seem to be getting set so try reading from the stream
  std::string eof;
  std::getline( test_tablefile, eof );

  TEST_EQUALITY_CONST( eof.size(), 0 );

  // Close the test table file
  test_tablefile.close();
}

//---------------------------------------------------------------------------//
// Check that the EPDL97DataProcessor can skip a four column table
TEUCHOS_UNIT_TEST( EPDL97DataProcessor, four_column_table_skip_test )
{
  std::ifstream test_tablefile;
  test_tablefile.open( "test_four_column_table.txt", std::fstream::in );
  TEST_ASSERT( test_tablefile.is_open() );

  TestDataProcessor data_processor;

  unsigned int atomic_number;
  unsigned int outgoing_particle_designator;
  double atomic_weight;
  unsigned int interpolation_flag;
  unsigned int reaction_type;
  unsigned int electron_shell;

  data_processor.readFirstTableHeader( test_tablefile,
				       atomic_number,
				       outgoing_particle_designator,
				       atomic_weight,
				       interpolation_flag );

  data_processor.readSecondTableHeader( test_tablefile,
					reaction_type,
					electron_shell );


  data_processor.skipFourColumnTable( test_tablefile );

  // Test that the entire table was read
  //  the EOF bit doesn't seem to be getting set so try reading from the stream
  std::string eof;
  std::getline( test_tablefile, eof );

  TEST_EQUALITY_CONST( eof.size(), 0 );

  // Close the test table file
  test_tablefile.close();
}

//---------------------------------------------------------------------------//
// Check that the EPDL97DataProcessor can read a two column table in 
// linear-linear format
//TEUCHOS_UNIT_TEST( EPDL97DataProcessor, two_column_table_log_log_read_test )
//{
//  std::ifstream test_tablefile;
//  test_tablefile.open( "test_full_two_column_table.txt", std::fstream::in );
//  TEST_ASSERT( test_tablefile.is_open() );
//
//  TestDataProcessor data_processor;
//
//  unsigned int atomic_number;
//  unsigned int outgoing_particle_designator;
//  double atomic_weight;
//  unsigned int interpolation_flag;
//  unsigned int reaction_type;
//  unsigned int electron_shell;
//
//  data_processor.readFirstTableHeader( test_tablefile,
//				       atomic_number,
//				       outgoint_particle_designator,
//				       atomic_weight,
//				       interpolation_flag );
//
//  data_processor.readSecondTableHeader( test_tablefile,
//					reaction_type,
//					electron_shell );
//  
//  Teuchos::Array<Pair<double,double> > data, data_true;
//
//  data_processor.readTwoColumnTable<FACEMC::EPDL97DataProcessor::LinearLinearProcessingPolicy>( test_tablefile,
//		data );
//}

