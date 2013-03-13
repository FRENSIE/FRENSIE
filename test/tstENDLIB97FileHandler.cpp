//---------------------------------------------------------------------------//
// \file   tstENDLIB97FileHandler.cpp
// \author Alex Robinson
// \brief  ENLIB97FileHandler class unit tests.
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayView.hpp>

// FACEMC Includes
#include "ENDLIB97FileHandler.hpp"
#include "TestingHelperFunctions.hpp"

//---------------------------------------------------------------------------//
// Test File Names.
//---------------------------------------------------------------------------//
#define FIRST_HEADER_TEST_FILE "test_first_header.txt"
#define SECOND_HEADER_TEST_FILE "test_second_header.txt"
#define FULL_HEADER_TEST_FILE "test_full_header.txt"
#define TWO_COLUMN_TABLE_TEST_FILE "test_two_column_table.txt"
#define THREE_COLUMN_TABLE_TEST_FILE "test_three_column_table.txt"
#define FOUR_COLUMN_TABLE_TEST_FILE "test_four_column_table.txt"
#define TWO_TWO_COLUMN_TABLES_TEST_FILE "test_two_two_column_tables.txt"
#define TWO_THREE_COLUMN_TABLES_TEST_FILE "test_two_three_column_tables.txt"
#define TWO_FOUR_COLUMN_TABLES_TEST_FILE "test_two_four_column_tables.txt"

//---------------------------------------------------------------------------//
// Testing Parameters
//---------------------------------------------------------------------------//
#define TOL 1e-12

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
template<typename Tuple, template<typename> class Array>
void fillTwoColumnTestingArray( Array<Tuple> &data )
{
  data.resize( 12 );

  Tuple data_point;
  data_point.first = static_cast<typename Tuple::firstType>( 1 );
  data_point.second = static_cast<typename Tuple::secondType>( 2 );
  data[0] = data_point;

  data_point.first = static_cast<typename Tuple::firstType>( 3 );
  data_point.second = static_cast<typename Tuple::secondType>( 2 );
  data[1] = data_point;

  data_point.first = static_cast<typename Tuple::firstType>( 5 );
  data_point.second = static_cast<typename Tuple::secondType>( 2 );
  data[2] = data_point;

  data_point.first = static_cast<typename Tuple::firstType>( 6 );
  data_point.second = static_cast<typename Tuple::firstType>( 4 );
  data[3] = data_point;
  
  data_point.first = static_cast<typename Tuple::firstType>( 8 );
  data_point.second = static_cast<typename Tuple::secondType>( 2 );
  data[4] = data_point;

  data_point.first = static_cast<typename Tuple::firstType>( 10 );
  data_point.second = static_cast<typename Tuple::secondType>( 2 );
  data[5] = data_point;

  data_point.first = static_cast<typename Tuple::firstType>( 11 );
  data_point.second = static_cast<typename Tuple::secondType>( 4 );
  data[6] = data_point;

  data_point.first = static_cast<typename Tuple::firstType>( 13 );
  data_point.second = static_cast<typename Tuple::secondType>( 4 );
  data[7] = data_point;

  data_point.first = static_cast<typename Tuple::firstType>( 14 );
  data_point.second = static_cast<typename Tuple::secondType>( 6 );
  data[8] = data_point;

  data_point.first = static_cast<typename Tuple::firstType>( 16 );
  data_point.second = static_cast<typename Tuple::secondType>( 2 );
  data[9] = data_point;

  data_point.first = static_cast<typename Tuple::firstType>( 18 );
  data_point.second = static_cast<typename Tuple::secondType>( 2 );
  data[10] = data_point;

  data_point.first = static_cast<typename Tuple::firstType>( 19 );
  data_point.second = static_cast<typename Tuple::secondType>( 4 );
  data[11] = data_point;
}

template<typename Tuple, template<typename> class Array>
void fillThreeColumnTestingArray( Array<Tuple> &data )
{
  data.resize( 8 );

  Tuple data_point;
  
  data_point.first = static_cast<typename Tuple::firstType>( 5 );
  data_point.second = static_cast<typename Tuple::secondType>( 2.96149e-1 );
  data_point.third = static_cast<typename Tuple::thirdType>( 1.13103e-1 );
  data[0] = data_point;

  data_point.first = static_cast<typename Tuple::firstType>( 6 );
  data_point.second = static_cast<typename Tuple::secondType>( 4.55508e-1 );
  data_point.third = static_cast<typename Tuple::thirdType>( 1.18701e-1 );
  data[1] = data_point;

  data_point.first = static_cast<typename Tuple::firstType>( 10 );
  data_point.second = static_cast<typename Tuple::secondType>( 5.34468e-2 );
  data_point.third = static_cast<typename Tuple::thirdType>( 1.32545e-1 );
  data[2] = data_point;

  data_point.first = static_cast<typename Tuple::firstType>( 11 );
  data_point.second = static_cast<typename Tuple::secondType>( 1.05850e-1 );
  data_point.third = static_cast<typename Tuple::thirdType>( 1.33863e-1 );
  data[3] = data_point;

  data_point.first = static_cast<typename Tuple::firstType>( 13 );
  data_point.second = static_cast<typename Tuple::secondType>( 2.18629e-3 );
  data_point.third = static_cast<typename Tuple::thirdType>( 1.34485e-1 );
  data[4] = data_point;

  data_point.first = static_cast<typename Tuple::firstType>( 14 );
  data_point.second = static_cast<typename Tuple::secondType>( 2.37699e-3 );
  data_point.third = static_cast<typename Tuple::thirdType>( 1.34740e-1 );
  data[5] = data_point;

  data_point.first = static_cast<typename Tuple::firstType>( 18 );
  data_point.second = static_cast<typename Tuple::secondType>( 1.36579e-2 );
  data_point.third = static_cast<typename Tuple::thirdType>( 1.37436e-1 );
  data[6] = data_point;

  data_point.first = static_cast<typename Tuple::firstType>( 19 );
  data_point.second = static_cast<typename Tuple::secondType>( 2.84889e-2 );
  data_point.third = static_cast<typename Tuple::thirdType>( 1.37794e-1 );
  data[7] = data_point;
}

template<typename Tuple, template<typename> class Array>
void fillFourColumnTestingArray( Array<Tuple> &data )
{
  data.resize( 5 );

  Tuple data_point;
  
  data_point.first = static_cast<typename Tuple::firstType>( 27 );
  data_point.second = static_cast<typename Tuple::secondType>( 27 );
  data_point.third = static_cast<typename Tuple::thirdType>( 3.80318e-1 );
  data_point.fourth = static_cast<typename Tuple::fourthType>( 6.710e-6 );
  data[0] = data_point;

  data_point.first = static_cast<typename Tuple::firstType>( 27 );
  data_point.second = static_cast<typename Tuple::secondType>( 29 );
  data_point.third = static_cast<typename Tuple::thirdType>( 2.81669e-1 );
  data_point.fourth = static_cast<typename Tuple::fourthType>( 1.3820e-5 );
  data[1] = data_point;

  data_point.first = static_cast<typename Tuple::firstType>( 27 );
  data_point.second = static_cast<typename Tuple::secondType>( 30 );
  data_point.third = static_cast<typename Tuple::thirdType>( 2.44679e-1 );
  data_point.fourth = static_cast<typename Tuple::fourthType>( 1.4330e-5 );
  data[2] = data_point;

  data_point.first = static_cast<typename Tuple::firstType>( 29 );
  data_point.second = static_cast<typename Tuple::secondType>( 30 );
  data_point.third = static_cast<typename Tuple::thirdType>( 8.83536e-2 );
  data_point.fourth = static_cast<typename Tuple::fourthType>( 2.1440e-5 );
  data[3] = data_point;

  data_point.first = static_cast<typename Tuple::firstType>( 30 );
  data_point.second = static_cast<typename Tuple::secondType>( 30 );
  data_point.third = static_cast<typename Tuple::thirdType>( 4.98008e-3 );
  data_point.fourth = static_cast<typename Tuple::fourthType>( 2.19500e-5 );
  data[4] = data_point;
}

//---------------------------------------------------------------------------//
// Testing Stucts.
//---------------------------------------------------------------------------//
class TestENDLIB97FileHandler : public FACEMC::ENDLIB97FileHandler
{
public:
  TestENDLIB97FileHandler()
    : ENDLIB97FileHandler()
  { /* ... */ }
  
  TestENDLIB97FileHandler( const std::string &file_name )
    : ENDLIB97FileHandler( file_name )
  { /* ... */ }

  virtual ~TestENDLIB97FileHandler()
  { /* ... */ }
  
  // Allow public access to ENDLIB97FileHandler protected member functions
  using FACEMC::ENDLIB97FileHandler::extractValue;
};  

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the ENDLIB97FileHandler can open a file when constructed
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, constructor_open_file_test )
{
  // If DBC is turned on, the constructor will throw an exception and exit
  // if this file does not exist. No Testing Macro is needed.
  FACEMC::ENDLIB97FileHandler endlib_file_handler( FIRST_HEADER_TEST_FILE );
}

//---------------------------------------------------------------------------//
// Check that the ENDLIB97FileHandler can open a file after being contructed
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, open_file_test )
{
  FACEMC::ENDLIB97FileHandler endlib_file_handler;
  
  // If DBC is turned on, the constructor will throw an exception and exit
  // if this file does not exist. No Testing Macro is needed.
  endlib_file_handler.openENDLIB97File( FIRST_HEADER_TEST_FILE );
}

//---------------------------------------------------------------------------//
// Check that the ENDLIB97FileHandler can indicate that a file is valid
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, valid_file_test )
{
  FACEMC::ENDLIB97FileHandler endlib_file_handler;

  endlib_file_handler.openENDLIB97File( FIRST_HEADER_TEST_FILE );
  
  TEST_ASSERT( endlib_file_handler.validFile() );
}

//---------------------------------------------------------------------------//
// Check that the ENDLIB97FileHandler can extract a double from a FORTRAN
// fixed width float
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, extract_double_test )
{
  std::string mantissa_with_pos(" 1.00000+");
  std::string mantissa_with_neg(" 1.00000-");
  std::string exponent("10");

  std::string mantissa(" 1.000000");
  std::string exponent_with_pos("+2");
  std::string exponent_with_neg("-2");
  
  TestENDLIB97FileHandler test_file_handler;
  
  // test all possible mantissa, exponent combinations
  double combination_1;
  double combination_2;
  double combination_3;
  double combination_4;
  
  combination_1 = test_file_handler.extractValue<double>( mantissa_with_pos,
							  exponent );
  combination_2 = test_file_handler.extractValue<double>( mantissa_with_neg,
							  exponent );
  combination_3 = test_file_handler.extractValue<double>( mantissa,
							  exponent_with_pos );
  combination_4 = test_file_handler.extractValue<double>( mantissa,
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
// Check that the ENDLIB97FileHandler can extract an int from a FORTRAN
// fixed width float
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, extract_int_test )
{
  std::string mantissa_with_pos(" 1.00000+");
  std::string exponent(" 0");

  std::string mantissa(" 1.100000");
  std::string exponent_with_pos("+1");
  
  TestENDLIB97FileHandler test_file_handler;
  
  // test all possible mantissa, exponent combinations
  double combination_1;
  double combination_2;
  
  combination_1 = test_file_handler.extractValue<int>( mantissa_with_pos,
						       exponent );
  combination_2 = test_file_handler.extractValue<int>( mantissa,
						       exponent_with_pos );

  int true_value_1 = 1;
  int true_value_2 = 11;
  
  TEST_EQUALITY( combination_1, true_value_1 );
  TEST_EQUALITY( combination_2, true_value_2 );
}

//---------------------------------------------------------------------------//
// Check that the ENDLIB97FileHandler can extract an unsigned int from a FORTRAN
// fixed width float
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, extract_uint_test )
{
  std::string mantissa_with_pos(" 1.00000+");
  std::string exponent(" 0");

  std::string mantissa(" 1.100000");
  std::string exponent_with_pos("+1");
  
  TestENDLIB97FileHandler test_file_handler;
  
  // test all possible mantissa, exponent combinations
  double combination_1;
  double combination_2;
  
  combination_1 = test_file_handler.extractValue<unsigned int>( mantissa_with_pos,
								exponent );
  combination_2 = test_file_handler.extractValue<unsigned int>( mantissa,
								exponent_with_pos );

  unsigned int true_value_1 = 1;
  unsigned int true_value_2 = 11;
  
  TEST_EQUALITY( combination_1, true_value_1 );
  TEST_EQUALITY( combination_2, true_value_2 );
}

//---------------------------------------------------------------------------//
// Check that the ENDLIB97FileHandler can read the first header of a table
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, first_table_header_read_test )
{
  FACEMC::ENDLIB97FileHandler endlib_file_handler( FIRST_HEADER_TEST_FILE );

  // Values to read from the header
  unsigned int atomic_number, atomic_number_true = 99;
  unsigned int outgoing_particle_designator,
    outgoing_particle_designator_true = 0;
  double atomic_weight, atomic_weight_true = 252.0;
  unsigned int interpolation_flag, interpolation_flag_true = 5;

  // Read the test header file containing an typical first header
  endlib_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_weight,
					    interpolation_flag );
  
  // Test that the values read from the header match their expected values
  TEST_EQUALITY( atomic_number, atomic_number_true );

  TEST_EQUALITY( outgoing_particle_designator,
		 outgoing_particle_designator_true );

  TEST_FLOATING_EQUALITY( atomic_weight, atomic_weight_true, 1e-12 );

  TEST_EQUALITY( interpolation_flag, interpolation_flag_true );

  // Close the test header file
  endlib_file_handler.closeENDLIB97File();
}

//---------------------------------------------------------------------------//
// Check that the ENDLIB97FileHandler can read the second header of a table
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, second_table_header_read_test )
{
  FACEMC::ENDLIB97FileHandler endlib_file_handler( SECOND_HEADER_TEST_FILE );

  // Values to read from the header
  unsigned int reaction_type, reaction_type_true = 73000;
  unsigned int electron_shell, electron_shell_true = 11;

  // Read the test header file containing an typical second header
  endlib_file_handler.readSecondTableHeader( reaction_type,
					     electron_shell );
  
  // Test that the values read from the header match their expected values
  TEST_EQUALITY( reaction_type, reaction_type_true );

  TEST_EQUALITY( electron_shell, electron_shell_true );

  // Close the test header file
  endlib_file_handler.closeENDLIB97File();
}

//---------------------------------------------------------------------------//
// Check that the ENDLIB97FileHandler can read the first header and
// second header of a table consecutively
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, full_table_header_read_test )
{
  FACEMC::ENDLIB97FileHandler endlib_file_handler( FULL_HEADER_TEST_FILE );
  
  // Values to read from the header
  unsigned int atomic_number, atomic_number_true = 70;
  unsigned int outgoing_particle_designator,
    outgoing_particle_designator_true = 0;
  double atomic_weight, atomic_weight_true = 173.04;
  unsigned int interpolation_flag, interpolation_flag_true = 5;
  unsigned int reaction_type, reaction_type_true = 73000;
  unsigned int electron_shell, electron_shell_true = 8;

  // Read the first header of the test header file
  endlib_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_weight,
					    interpolation_flag );

  // Read the second header of the test header file
  endlib_file_handler.readSecondTableHeader( reaction_type,
					     electron_shell );
  
  // Test that the values read from the header match their expected values
  TEST_EQUALITY( atomic_number, atomic_number_true );

  TEST_EQUALITY( outgoing_particle_designator,
		 outgoing_particle_designator_true );

  TEST_FLOATING_EQUALITY( atomic_weight, atomic_weight_true, 1e-12 );

  TEST_EQUALITY( interpolation_flag, interpolation_flag_true );

  TEST_EQUALITY( reaction_type, reaction_type_true );

  TEST_EQUALITY( electron_shell, electron_shell_true );

  // Close the test header file
  endlib_file_handler.closeENDLIB97File();
}

//---------------------------------------------------------------------------//
// Check that the ENDLIB97FileHandler can skip a two column table
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, two_column_table_skip_test )
{
  FACEMC::ENDLIB97FileHandler endlib_file_handler( TWO_COLUMN_TABLE_TEST_FILE );
  
  unsigned int atomic_number;
  unsigned int outgoing_particle_designator;
  double atomic_weight;
  unsigned int interpolation_flag;
  unsigned int reaction_type;
  unsigned int electron_shell;

  endlib_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_weight,
					    interpolation_flag );

  endlib_file_handler.readSecondTableHeader( reaction_type,
					     electron_shell );

  endlib_file_handler.skipTwoColumnTable();

  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endlib_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_weight,
					    interpolation_flag );
  TEST_ASSERT( endlib_file_handler.endOfFile() );
  
  // Close the test table file
  endlib_file_handler.closeENDLIB97File();
}

//---------------------------------------------------------------------------//
// Check that the ENDLIB97FileHandler can skip a three column table
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, three_column_table_skip_test )
{
  FACEMC::ENDLIB97FileHandler endlib_file_handler( THREE_COLUMN_TABLE_TEST_FILE );
  
  unsigned int atomic_number;
  unsigned int outgoing_particle_designator;
  double atomic_weight;
  unsigned int interpolation_flag;
  unsigned int reaction_type;
  unsigned int electron_shell;

  endlib_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_weight,
					    interpolation_flag );

  endlib_file_handler.readSecondTableHeader( reaction_type,
					     electron_shell );


  endlib_file_handler.skipThreeColumnTable();

  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endlib_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_weight,
					    interpolation_flag );
  TEST_ASSERT( endlib_file_handler.endOfFile() );
  
  // Close the test table file
  endlib_file_handler.closeENDLIB97File();
}

//---------------------------------------------------------------------------//
// Check that the ENDLIB97FileHandler can skip a four column table
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, four_column_table_skip_test )
{
  FACEMC::ENDLIB97FileHandler endlib_file_handler( FOUR_COLUMN_TABLE_TEST_FILE );
  
  unsigned int atomic_number;
  unsigned int outgoing_particle_designator;
  double atomic_weight;
  unsigned int interpolation_flag;
  unsigned int reaction_type;
  unsigned int electron_shell;

  endlib_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_weight,
					    interpolation_flag );

  endlib_file_handler.readSecondTableHeader( reaction_type,
					     electron_shell );

  endlib_file_handler.skipFourColumnTable();

  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endlib_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_weight,
					    interpolation_flag );
  TEST_ASSERT( endlib_file_handler.endOfFile() );

  // Close the test table file
  endlib_file_handler.closeENDLIB97File();
}

//---------------------------------------------------------------------------//
// Check that the ENDLIB97FileHandler can read a two column table of double
// and double 
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, two_column_table_double_double_read_test )
{
  FACEMC::ENDLIB97FileHandler endlib_file_handler( TWO_COLUMN_TABLE_TEST_FILE );
  
  unsigned int atomic_number;
  unsigned int outgoing_particle_designator;
  double atomic_weight;
  unsigned int interpolation_flag;
  unsigned int reaction_type;
  unsigned int electron_shell;

  endlib_file_handler.readFirstTableHeader( atomic_number,
				       outgoing_particle_designator,
				       atomic_weight,
				       interpolation_flag );

  endlib_file_handler.readSecondTableHeader( reaction_type,
					electron_shell );
  
  Teuchos::Array<FACEMC::Pair<double,double> > data, data_true;

  endlib_file_handler.readTwoColumnTable( data );
  
  fillTwoColumnTestingArray( data_true );

  FACEMC_TEST_COMPARE_ARRAYS( data, data_true );

  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endlib_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_weight,
					    interpolation_flag );
  TEST_ASSERT( endlib_file_handler.endOfFile() );

  // Close the test table file
  endlib_file_handler.closeENDLIB97File();
}

//---------------------------------------------------------------------------//
// Check that the ENDLIB97FileHandler can read a two column table in of 
// unsigned int and double
//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, two_column_table_uint_double_read_test )
{
  FACEMC::ENDLIB97FileHandler endlib_file_handler( TWO_COLUMN_TABLE_TEST_FILE );
  
  unsigned int atomic_number;
  unsigned int outgoing_particle_designator;
  double atomic_weight;
  unsigned int interpolation_flag;
  unsigned int reaction_type;
  unsigned int electron_shell;

  endlib_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_weight,
					    interpolation_flag );

  endlib_file_handler.readSecondTableHeader( reaction_type,
					     electron_shell );
  
  Teuchos::Array<FACEMC::Pair<unsigned int,double> > data, data_true;
  
  endlib_file_handler.readTwoColumnTable( data );
  
  fillTwoColumnTestingArray( data_true );

  FACEMC_TEST_COMPARE_ARRAYS( data, data_true );
  
  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endlib_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_weight,
					    interpolation_flag );
  TEST_ASSERT( endlib_file_handler.endOfFile() );

  // Close the test table file
  endlib_file_handler.closeENDLIB97File();
}

//---------------------------------------------------------------------------//
// Check that the ENDLIB97FileHandler can read a two column table in the 
// given independent variable range
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, two_column_table_range_eq_eq_read_test )
{
  FACEMC::ENDLIB97FileHandler endlib_file_handler( TWO_COLUMN_TABLE_TEST_FILE );
  
  unsigned int atomic_number;
  unsigned int outgoing_particle_designator;
  double atomic_weight;
  unsigned int interpolation_flag;
  unsigned int reaction_type;
  unsigned int electron_shell;

  endlib_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_weight,
					    interpolation_flag );

  endlib_file_handler.readSecondTableHeader( reaction_type,
					     electron_shell );
  
  Teuchos::Array<FACEMC::Pair<double,double> > data, data_true;

  endlib_file_handler.readTwoColumnTableInRange( data,
						 1.0,
						 19.0 );
  
  fillTwoColumnTestingArray( data_true );

  FACEMC_TEST_COMPARE_ARRAYS( data, data_true );
  
  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endlib_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_weight,
					    interpolation_flag );
  TEST_ASSERT( endlib_file_handler.endOfFile() );

  // Close the test table file
  endlib_file_handler.closeENDLIB97File();
}

//---------------------------------------------------------------------------//
// Check that the ENDLIB97FileHandler can read a two column table in the 
// given independent variable range
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, two_column_table_range_lt_gt_read_test )
{
  FACEMC::ENDLIB97FileHandler endlib_file_handler( TWO_COLUMN_TABLE_TEST_FILE );
  
  unsigned int atomic_number;
  unsigned int outgoing_particle_designator;
  double atomic_weight;
  unsigned int interpolation_flag;
  unsigned int reaction_type;
  unsigned int electron_shell;

  endlib_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_weight,
					    interpolation_flag );

  endlib_file_handler.readSecondTableHeader( reaction_type,
					     electron_shell );
  
  Teuchos::Array<FACEMC::Pair<double,double> > data, data_true;

  endlib_file_handler.readTwoColumnTableInRange( data,
						 0.0,
						 20.0 );
  
  fillTwoColumnTestingArray( data_true );

  FACEMC_TEST_COMPARE_ARRAYS( data, data_true );
  
  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endlib_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_weight,
					    interpolation_flag );
  TEST_ASSERT( endlib_file_handler.endOfFile() );

  // Close the test table file
  endlib_file_handler.closeENDLIB97File();
}

//---------------------------------------------------------------------------//
// Check that the ENDLIB97FileHandler can read a two column table in the 
// given independent variable range
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, two_column_table_range_eq_gt_read_test )
{
  FACEMC::ENDLIB97FileHandler endlib_file_handler( TWO_COLUMN_TABLE_TEST_FILE );
  
  unsigned int atomic_number;
  unsigned int outgoing_particle_designator;
  double atomic_weight;
  unsigned int interpolation_flag;
  unsigned int reaction_type;
  unsigned int electron_shell;

  endlib_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_weight,
					    interpolation_flag );

  endlib_file_handler.readSecondTableHeader( reaction_type,
					     electron_shell );
  
  Teuchos::Array<FACEMC::Pair<double,double> > data, data_true;

  endlib_file_handler.readTwoColumnTableInRange( data,
						 1.0,
						 20.0 );
  
  fillTwoColumnTestingArray( data_true );

  FACEMC_TEST_COMPARE_ARRAYS( data, data_true );
  
  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endlib_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_weight,
					    interpolation_flag );
  TEST_ASSERT( endlib_file_handler.endOfFile() );

  // Close the test table file
  endlib_file_handler.closeENDLIB97File();
}

//---------------------------------------------------------------------------//
// Check that the ENDLIB97FileHandler can read a two column table in the 
// given independent variable range
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, two_column_table_range_lt_eq_read_test )
{
  FACEMC::ENDLIB97FileHandler endlib_file_handler( TWO_COLUMN_TABLE_TEST_FILE );
  
  unsigned int atomic_number;
  unsigned int outgoing_particle_designator;
  double atomic_weight;
  unsigned int interpolation_flag;
  unsigned int reaction_type;
  unsigned int electron_shell;

  endlib_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_weight,
					    interpolation_flag );

  endlib_file_handler.readSecondTableHeader( reaction_type,
					     electron_shell );
  
  Teuchos::Array<FACEMC::Pair<double,double> > data, data_true;

  endlib_file_handler.readTwoColumnTableInRange( data,
						 0.0,
						 19.0 );
  
  fillTwoColumnTestingArray( data_true );

  FACEMC_TEST_COMPARE_ARRAYS( data, data_true );
  
  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endlib_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_weight,
					    interpolation_flag );
  TEST_ASSERT( endlib_file_handler.endOfFile() );

  // Close the test table file
  endlib_file_handler.closeENDLIB97File();
}

//---------------------------------------------------------------------------//
// Check that the ENDLIB97FileHandler can read a two column table in the 
// given independent variable range
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, two_column_table_range_gt_lt_read_test )
{
  FACEMC::ENDLIB97FileHandler endlib_file_handler( TWO_COLUMN_TABLE_TEST_FILE );
  
  unsigned int atomic_number;
  unsigned int outgoing_particle_designator;
  double atomic_weight;
  unsigned int interpolation_flag;
  unsigned int reaction_type;
  unsigned int electron_shell;

  endlib_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_weight,
					    interpolation_flag );

  endlib_file_handler.readSecondTableHeader( reaction_type,
					     electron_shell );
  
  Teuchos::Array<FACEMC::Pair<double,double> > data, data_true;

  endlib_file_handler.readTwoColumnTableInRange( data,
						 5.5,
						 13.5 );
  
  fillTwoColumnTestingArray( data_true );

  FACEMC_TEST_COMPARE_ARRAYS( data, data_true( 2, 7 ) );
  
  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endlib_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_weight,
					    interpolation_flag );
  TEST_ASSERT( endlib_file_handler.endOfFile() );

  // Close the test table file
  endlib_file_handler.closeENDLIB97File();
}

//---------------------------------------------------------------------------//
// Check that the ENDLIB97FileHandler can read a two column table in the 
// given independent variable range
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, two_column_table_range_eq_lt_read_test )
{
  FACEMC::ENDLIB97FileHandler endlib_file_handler( TWO_COLUMN_TABLE_TEST_FILE );
  
  unsigned int atomic_number;
  unsigned int outgoing_particle_designator;
  double atomic_weight;
  unsigned int interpolation_flag;
  unsigned int reaction_type;
  unsigned int electron_shell;

  endlib_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_weight,
					    interpolation_flag );

  endlib_file_handler.readSecondTableHeader( reaction_type,
					     electron_shell );
  
  Teuchos::Array<FACEMC::Pair<double,double> > data, data_true;

  endlib_file_handler.readTwoColumnTableInRange( data,
						 1.0,
						 13.0 );
  
  fillTwoColumnTestingArray( data_true );

  FACEMC_TEST_COMPARE_ARRAYS( data, data_true( 0, 8 ) );
  
  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endlib_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_weight,
					    interpolation_flag );
  TEST_ASSERT( endlib_file_handler.endOfFile() );

  // Close the test table file
  endlib_file_handler.closeENDLIB97File();
}

//---------------------------------------------------------------------------//
// Check that the ENDLIB97FileHandler can read a two column table in the 
// given independent variable range
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, two_column_table_range_lt_lt_read_test )
{
  FACEMC::ENDLIB97FileHandler endlib_file_handler( TWO_COLUMN_TABLE_TEST_FILE );
  
  unsigned int atomic_number;
  unsigned int outgoing_particle_designator;
  double atomic_weight;
  unsigned int interpolation_flag;
  unsigned int reaction_type;
  unsigned int electron_shell;

  endlib_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_weight,
					    interpolation_flag );

  endlib_file_handler.readSecondTableHeader( reaction_type,
					     electron_shell );
  
  Teuchos::Array<FACEMC::Pair<double,double> > data, data_true;

  endlib_file_handler.readTwoColumnTableInRange( data,
						 0.0,
						 13.0 );
  
  fillTwoColumnTestingArray( data_true );

  FACEMC_TEST_COMPARE_ARRAYS( data, data_true( 0, 8 ) );
  
  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endlib_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_weight,
					    interpolation_flag );
  TEST_ASSERT( endlib_file_handler.endOfFile() );

  // Close the test table file
  endlib_file_handler.closeENDLIB97File();
}

//---------------------------------------------------------------------------//
// Check that the ENDLIB97FileHandler can read a two column table in the 
// given independent variable range
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, two_column_table_range_gt_eq_read_test )
{
  FACEMC::ENDLIB97FileHandler endlib_file_handler( TWO_COLUMN_TABLE_TEST_FILE );
  
  unsigned int atomic_number;
  unsigned int outgoing_particle_designator;
  double atomic_weight;
  unsigned int interpolation_flag;
  unsigned int reaction_type;
  unsigned int electron_shell;

  endlib_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_weight,
					    interpolation_flag );

  endlib_file_handler.readSecondTableHeader( reaction_type,
					     electron_shell );
  
  Teuchos::Array<FACEMC::Pair<double,double> > data, data_true;

  endlib_file_handler.readTwoColumnTableInRange( data,
						 5.0,
						 19.0 );
  
  fillTwoColumnTestingArray( data_true );

  FACEMC_TEST_COMPARE_ARRAYS( data, data_true( 2, 10 ) );
  
  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endlib_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_weight,
					    interpolation_flag );
  TEST_ASSERT( endlib_file_handler.endOfFile() );

  // Close the test table file
  endlib_file_handler.closeENDLIB97File();
}

//---------------------------------------------------------------------------//
// Check that the ENDLIB97FileHandler can read a two column table in the 
// given independent variable range
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, two_column_table_range_gt_gt_read_test )
{
  FACEMC::ENDLIB97FileHandler endlib_file_handler( TWO_COLUMN_TABLE_TEST_FILE );
  
  unsigned int atomic_number;
  unsigned int outgoing_particle_designator;
  double atomic_weight;
  unsigned int interpolation_flag;
  unsigned int reaction_type;
  unsigned int electron_shell;

  endlib_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_weight,
					    interpolation_flag );

  endlib_file_handler.readSecondTableHeader( reaction_type,
					     electron_shell );
  
  Teuchos::Array<FACEMC::Pair<double,double> > data, data_true;

  endlib_file_handler.readTwoColumnTableInRange( data,
						 5.5,
						 20.0 );
  
  fillTwoColumnTestingArray( data_true );

  FACEMC_TEST_COMPARE_ARRAYS( data, data_true( 2, 10 ) );
  
  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endlib_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_weight,
					    interpolation_flag );
  TEST_ASSERT( endlib_file_handler.endOfFile() );

  // Close the test table file
  endlib_file_handler.closeENDLIB97File();
}

//---------------------------------------------------------------------------//
// Check that the ENDLIB97FileHandler can read a three column table 
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, three_column_table_read_test )
{
  FACEMC::ENDLIB97FileHandler endlib_file_handler( THREE_COLUMN_TABLE_TEST_FILE );
  
  unsigned int atomic_number;
  unsigned int outgoing_particle_designator;
  double atomic_weight;
  unsigned int interpolation_flag;
  unsigned int reaction_type;
  unsigned int electron_shell;

  endlib_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_weight,
					    interpolation_flag );

  endlib_file_handler.readSecondTableHeader( reaction_type,
					     electron_shell );
  
  Teuchos::Array<FACEMC::Trip<unsigned int,double,double> > data, data_true;

  endlib_file_handler.readThreeColumnTable( data );

  fillThreeColumnTestingArray( data_true );

  FACEMC_TEST_COMPARE_FLOATING_ARRAYS( data, data_true, TOL );

  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endlib_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_weight,
					    interpolation_flag );
  TEST_ASSERT( endlib_file_handler.endOfFile() );

  // Close the test table file
  endlib_file_handler.closeENDLIB97File();
}

//---------------------------------------------------------------------------//
// Check that the ENDLIB97FileHandler can read a four column table 
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, four_column_table_read_test )
{
  FACEMC::ENDLIB97FileHandler endlib_file_handler( FOUR_COLUMN_TABLE_TEST_FILE );
  
  unsigned int atomic_number;
  unsigned int outgoing_particle_designator;
  double atomic_weight;
  unsigned int interpolation_flag;
  unsigned int reaction_type;
  unsigned int electron_shell;

  endlib_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_weight,
					    interpolation_flag );

  endlib_file_handler.readSecondTableHeader( reaction_type,
					     electron_shell );
  
  Teuchos::Array<FACEMC::Quad<unsigned int,unsigned int,double,double> > data, 
    data_true;

  endlib_file_handler.readFourColumnTable( data );

  fillFourColumnTestingArray( data_true );

  FACEMC_TEST_COMPARE_FLOATING_ARRAYS( data, data_true, TOL );

  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endlib_file_handler.readFirstTableHeader( atomic_number,
					    outgoing_particle_designator,
					    atomic_weight,
					    interpolation_flag );
  TEST_ASSERT( endlib_file_handler.endOfFile() );

  // Close the test table file
  endlib_file_handler.closeENDLIB97File();
}

//---------------------------------------------------------------------------//
// Check that the ENDLIB97FileHandler can skip a two column table and then
// skip a two column table
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, two_column_table_skip_skip_test )
{
  FACEMC::ENDLIB97FileHandler endlib_file_handler( TWO_TWO_COLUMN_TABLES_TEST_FILE );
  
  unsigned int atomic_number_1, atomic_number_2;
  unsigned int outgoing_particle_designator_1, outgoing_particle_designator_2;
  double atomic_weight_1, atomic_weight_2;
  unsigned int interpolation_flag_1, interpolation_flag_2;
  unsigned int reaction_type_1, reaction_type_2;
  unsigned int electron_shell_1, electron_shell_2;

  endlib_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_weight_1,
					    interpolation_flag_1 );

  endlib_file_handler.readSecondTableHeader( reaction_type_1,
					     electron_shell_1 );

  // Skip the first table
  endlib_file_handler.skipTwoColumnTable();
  
  endlib_file_handler.readFirstTableHeader( atomic_number_2,
					    outgoing_particle_designator_2,
					    atomic_weight_2,
					    interpolation_flag_2 );

  endlib_file_handler.readSecondTableHeader( reaction_type_2,
					     electron_shell_2 );
  // Check that the header info from both tables matches
  TEST_EQUALITY( atomic_number_1, atomic_number_2 );
  TEST_EQUALITY( outgoing_particle_designator_1,
		 outgoing_particle_designator_2 );
  TEST_EQUALITY( atomic_weight_1, atomic_weight_2 );
  TEST_EQUALITY( interpolation_flag_1, interpolation_flag_2 );
  TEST_EQUALITY( reaction_type_1, reaction_type_2 );
  TEST_EQUALITY( electron_shell_1, electron_shell_2 );
  
  // Skip the second table
  endlib_file_handler.skipTwoColumnTable();

  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endlib_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_weight_1,
					    interpolation_flag_1 );
  TEST_ASSERT( endlib_file_handler.endOfFile() );

  // Close the test table file
  endlib_file_handler.closeENDLIB97File();
}

//---------------------------------------------------------------------------//
// Check that the ENDLIB97FileHandler can skip a two column table and then
// read a two column table
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, two_column_table_skip_read_test )
{
  FACEMC::ENDLIB97FileHandler endlib_file_handler( TWO_TWO_COLUMN_TABLES_TEST_FILE );
  
  unsigned int atomic_number_1, atomic_number_2;
  unsigned int outgoing_particle_designator_1, outgoing_particle_designator_2;
  double atomic_weight_1, atomic_weight_2;
  unsigned int interpolation_flag_1, interpolation_flag_2;
  unsigned int reaction_type_1, reaction_type_2;
  unsigned int electron_shell_1, electron_shell_2;

  endlib_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_weight_1,
					    interpolation_flag_1 );

  endlib_file_handler.readSecondTableHeader( reaction_type_1,
					     electron_shell_1 );

  // Skip the first table
  endlib_file_handler.skipTwoColumnTable();
  
  endlib_file_handler.readFirstTableHeader( atomic_number_2,
					    outgoing_particle_designator_2,
					    atomic_weight_2,
					    interpolation_flag_2 );

  endlib_file_handler.readSecondTableHeader( reaction_type_2,
					     electron_shell_2 );
  
  // Check that the header info from both tables matches
  TEST_EQUALITY( atomic_number_1, atomic_number_2 );
  TEST_EQUALITY( outgoing_particle_designator_1,
		 outgoing_particle_designator_2 );
  TEST_EQUALITY( atomic_weight_1, atomic_weight_2 );
  TEST_EQUALITY( interpolation_flag_1, interpolation_flag_2 );
  TEST_EQUALITY( reaction_type_1, reaction_type_2 );
  TEST_EQUALITY( electron_shell_1, electron_shell_2 );
  
  Teuchos::Array<FACEMC::Pair<double,double> > data;
  
  // Read the second table
  endlib_file_handler.readTwoColumnTable( data );

  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endlib_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_weight_1,
					    interpolation_flag_1 );
  TEST_ASSERT( endlib_file_handler.endOfFile() );

  // Close the test table file
  endlib_file_handler.closeENDLIB97File();
}

//---------------------------------------------------------------------------//
// Check that the ENDLIB97FileHandler can read a two column table and then
// skip a two column table
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, two_column_table_read_skip_test )
{
  FACEMC::ENDLIB97FileHandler endlib_file_handler( TWO_TWO_COLUMN_TABLES_TEST_FILE );
  
  unsigned int atomic_number_1, atomic_number_2;
  unsigned int outgoing_particle_designator_1, outgoing_particle_designator_2;
  double atomic_weight_1, atomic_weight_2;
  unsigned int interpolation_flag_1, interpolation_flag_2;
  unsigned int reaction_type_1, reaction_type_2;
  unsigned int electron_shell_1, electron_shell_2;

  endlib_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_weight_1,
					    interpolation_flag_1 );

  endlib_file_handler.readSecondTableHeader( reaction_type_1,
					     electron_shell_1 );

  // Read the first table
  Teuchos::Array<FACEMC::Pair<double,double> > data;
  
  endlib_file_handler.readTwoColumnTable( data );
  
  endlib_file_handler.readFirstTableHeader( atomic_number_2,
					    outgoing_particle_designator_2,
					    atomic_weight_2,
					    interpolation_flag_2 );

  endlib_file_handler.readSecondTableHeader( reaction_type_2,
					     electron_shell_2 );

  // Skip the second table
  endlib_file_handler.skipTwoColumnTable();
  
  // Check that the header info from both tables matches
  TEST_EQUALITY( atomic_number_1, atomic_number_2 );
  TEST_EQUALITY( outgoing_particle_designator_1,
		 outgoing_particle_designator_2 );
  TEST_EQUALITY( atomic_weight_1, atomic_weight_2 );
  TEST_EQUALITY( interpolation_flag_1, interpolation_flag_2 );
  TEST_EQUALITY( reaction_type_1, reaction_type_2 );
  TEST_EQUALITY( electron_shell_1, electron_shell_2 );

  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endlib_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_weight_1,
					    interpolation_flag_1 );
  TEST_ASSERT( endlib_file_handler.endOfFile() );

  // Close the test table file
  endlib_file_handler.closeENDLIB97File();
}

//---------------------------------------------------------------------------//
// Check that the ENDLIB97FileHandler can read a two column table and then
// read a two column table
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, two_column_table_read_read_test )
{
  FACEMC::ENDLIB97FileHandler endlib_file_handler( TWO_TWO_COLUMN_TABLES_TEST_FILE );
  
  unsigned int atomic_number_1, atomic_number_2;
  unsigned int outgoing_particle_designator_1, outgoing_particle_designator_2;
  double atomic_weight_1, atomic_weight_2;
  unsigned int interpolation_flag_1, interpolation_flag_2;
  unsigned int reaction_type_1, reaction_type_2;
  unsigned int electron_shell_1, electron_shell_2;
  Teuchos::Array<FACEMC::Pair<double,double> > data_1, data_2;

  endlib_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_weight_1,
					    interpolation_flag_1 );

  endlib_file_handler.readSecondTableHeader( reaction_type_1,
					     electron_shell_1 );

  // Read the first table
  endlib_file_handler.readTwoColumnTable( data_1 );
  
  endlib_file_handler.readFirstTableHeader( atomic_number_2,
					    outgoing_particle_designator_2,
					    atomic_weight_2,
					    interpolation_flag_2 );

  endlib_file_handler.readSecondTableHeader( reaction_type_2,
					     electron_shell_2 );

  // Read the second table
  endlib_file_handler.readTwoColumnTable( data_2 );
  
  // Check that the header info from both tables matches
  TEST_EQUALITY( atomic_number_1, atomic_number_2 );
  TEST_EQUALITY( outgoing_particle_designator_1,
		 outgoing_particle_designator_2 );
  TEST_EQUALITY( atomic_weight_1, atomic_weight_2 );
  TEST_EQUALITY( interpolation_flag_1, interpolation_flag_2 );
  TEST_EQUALITY( reaction_type_1, reaction_type_2 );
  TEST_EQUALITY( electron_shell_1, electron_shell_2 );
  FACEMC_TEST_COMPARE_ARRAYS( data_1, data_2 );

  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endlib_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_weight_1,
					    interpolation_flag_1 );
  TEST_ASSERT( endlib_file_handler.endOfFile() );

  // Close the test table file
  endlib_file_handler.closeENDLIB97File();
}

//---------------------------------------------------------------------------//
// Check that the ENDLIB97FileHandler can skip a three column table and then
// skip a three column table
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, three_column_table_skip_skip_test )
{
  FACEMC::ENDLIB97FileHandler endlib_file_handler( TWO_THREE_COLUMN_TABLES_TEST_FILE );
  
  unsigned int atomic_number_1, atomic_number_2;
  unsigned int outgoing_particle_designator_1, outgoing_particle_designator_2;
  double atomic_weight_1, atomic_weight_2;
  unsigned int interpolation_flag_1, interpolation_flag_2;
  unsigned int reaction_type_1, reaction_type_2;
  unsigned int electron_shell_1, electron_shell_2;
  
  endlib_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_weight_1,
					    interpolation_flag_1 );
  
  endlib_file_handler.readSecondTableHeader( reaction_type_1,
					     electron_shell_1 );
  
  // Skip the first table
  endlib_file_handler.skipThreeColumnTable();
  
  endlib_file_handler.readFirstTableHeader( atomic_number_2,
					    outgoing_particle_designator_2,
					    atomic_weight_2,
					    interpolation_flag_2 );
  
  endlib_file_handler.readSecondTableHeader( reaction_type_2,
					     electron_shell_2 );
  
  // Skip the second table
  endlib_file_handler.skipThreeColumnTable();
  
  // Check that the header info from both tables matches
  TEST_EQUALITY( atomic_number_1, atomic_number_2 );
  TEST_EQUALITY( outgoing_particle_designator_1,
		 outgoing_particle_designator_2 );
  TEST_EQUALITY( atomic_weight_1, atomic_weight_2 );
  TEST_EQUALITY( interpolation_flag_1, interpolation_flag_2 );
  TEST_EQUALITY( reaction_type_1, reaction_type_2 );
  TEST_EQUALITY( electron_shell_1, electron_shell_2 );  

  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endlib_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_weight_1,
					    interpolation_flag_1 );
  TEST_ASSERT( endlib_file_handler.endOfFile() );

  // Close the test table file
  endlib_file_handler.closeENDLIB97File();
}

//---------------------------------------------------------------------------//
// Check that the ENDLIB97FileHandler can skip a three column table and then
// read a three column table
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, three_column_table_skip_read_test )
{
  FACEMC::ENDLIB97FileHandler endlib_file_handler( TWO_THREE_COLUMN_TABLES_TEST_FILE );
  
  unsigned int atomic_number_1, atomic_number_2;
  unsigned int outgoing_particle_designator_1, outgoing_particle_designator_2;
  double atomic_weight_1, atomic_weight_2;
  unsigned int interpolation_flag_1, interpolation_flag_2;
  unsigned int reaction_type_1, reaction_type_2;
  unsigned int electron_shell_1, electron_shell_2;
  
  endlib_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_weight_1,
					    interpolation_flag_1 );
  
  endlib_file_handler.readSecondTableHeader( reaction_type_1,
					     electron_shell_1 );
  
  // Skip the first table
  endlib_file_handler.skipThreeColumnTable();
  
  endlib_file_handler.readFirstTableHeader( atomic_number_2,
					    outgoing_particle_designator_2,
					    atomic_weight_2,
					    interpolation_flag_2 );
  
  endlib_file_handler.readSecondTableHeader( reaction_type_2,
					     electron_shell_2 );
  
  // Read the second table
  Teuchos::Array<FACEMC::Trip<unsigned int,double,double> > data;

  endlib_file_handler.readThreeColumnTable( data );

  // Check that the header info from both tables matches
  TEST_EQUALITY( atomic_number_1, atomic_number_2 );
  TEST_EQUALITY( outgoing_particle_designator_1,
		 outgoing_particle_designator_2 );
  TEST_EQUALITY( atomic_weight_1, atomic_weight_2 );
  TEST_EQUALITY( interpolation_flag_1, interpolation_flag_2 );
  TEST_EQUALITY( reaction_type_1, reaction_type_2 );
  TEST_EQUALITY( electron_shell_1, electron_shell_2 );  

  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endlib_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_weight_1,
					    interpolation_flag_1 );
  TEST_ASSERT( endlib_file_handler.endOfFile() );

  // Close the test table file
  endlib_file_handler.closeENDLIB97File();
}

//---------------------------------------------------------------------------//
// Check that the ENDLIB97FileHandler can read a three column table and then
// skip a three column table
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, three_column_table_read_skip_test )
{
  FACEMC::ENDLIB97FileHandler endlib_file_handler( TWO_THREE_COLUMN_TABLES_TEST_FILE );
  
  unsigned int atomic_number_1, atomic_number_2;
  unsigned int outgoing_particle_designator_1, outgoing_particle_designator_2;
  double atomic_weight_1, atomic_weight_2;
  unsigned int interpolation_flag_1, interpolation_flag_2;
  unsigned int reaction_type_1, reaction_type_2;
  unsigned int electron_shell_1, electron_shell_2;
  
  endlib_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_weight_1,
					    interpolation_flag_1 );
  
  endlib_file_handler.readSecondTableHeader( reaction_type_1,
					     electron_shell_1 );
  
  // Read the first table
  Teuchos::Array<FACEMC::Trip<unsigned int,double,double> > data;

  endlib_file_handler.readThreeColumnTable( data );

  endlib_file_handler.readFirstTableHeader( atomic_number_2,
					    outgoing_particle_designator_2,
					    atomic_weight_2,
					    interpolation_flag_2 );
  
  endlib_file_handler.readSecondTableHeader( reaction_type_2,
					     electron_shell_2 );
  
  // Skip the second table
  endlib_file_handler.skipThreeColumnTable();
  
  // Check that the header info from both tables matches
  TEST_EQUALITY( atomic_number_1, atomic_number_2 );
  TEST_EQUALITY( outgoing_particle_designator_1,
		 outgoing_particle_designator_2 );
  TEST_EQUALITY( atomic_weight_1, atomic_weight_2 );
  TEST_EQUALITY( interpolation_flag_1, interpolation_flag_2 );
  TEST_EQUALITY( reaction_type_1, reaction_type_2 );
  TEST_EQUALITY( electron_shell_1, electron_shell_2 );  

  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endlib_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_weight_1,
					    interpolation_flag_1 );
  TEST_ASSERT( endlib_file_handler.endOfFile() );

  // Close the test table file
  endlib_file_handler.closeENDLIB97File();
}

//---------------------------------------------------------------------------//
// Check that the ENDLIB97FileHandler can read a three column table and then
// read a three column table
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, three_column_table_read_read_test )
{
  FACEMC::ENDLIB97FileHandler endlib_file_handler( TWO_THREE_COLUMN_TABLES_TEST_FILE );
  
  unsigned int atomic_number_1, atomic_number_2;
  unsigned int outgoing_particle_designator_1, outgoing_particle_designator_2;
  double atomic_weight_1, atomic_weight_2;
  unsigned int interpolation_flag_1, interpolation_flag_2;
  unsigned int reaction_type_1, reaction_type_2;
  unsigned int electron_shell_1, electron_shell_2;
  Teuchos::Array<FACEMC::Trip<unsigned int,double,double> > data_1, data_2;
  
  endlib_file_handler.readFirstTableHeader( atomic_number_1,
				       outgoing_particle_designator_1,
				       atomic_weight_1,
				       interpolation_flag_1 );
  
  endlib_file_handler.readSecondTableHeader( reaction_type_1,
					electron_shell_1 );
  
  // Read the first table
  endlib_file_handler.readThreeColumnTable( data_1 );

  endlib_file_handler.readFirstTableHeader( atomic_number_2,
					    outgoing_particle_designator_2,
					    atomic_weight_2,
					    interpolation_flag_2 );
  
  endlib_file_handler.readSecondTableHeader( reaction_type_2,
					     electron_shell_2 );
  
  // Read the second table
  endlib_file_handler.readThreeColumnTable( data_2 );
  
  // Check that the header info from both tables matches
  TEST_EQUALITY( atomic_number_1, atomic_number_2 );
  TEST_EQUALITY( outgoing_particle_designator_1,
		 outgoing_particle_designator_2 );
  TEST_EQUALITY( atomic_weight_1, atomic_weight_2 );
  TEST_EQUALITY( interpolation_flag_1, interpolation_flag_2 );
  TEST_EQUALITY( reaction_type_1, reaction_type_2 );
  TEST_EQUALITY( electron_shell_1, electron_shell_2 );  
  FACEMC_TEST_COMPARE_ARRAYS( data_1, data_2 );
  
  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endlib_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_weight_1,
					    interpolation_flag_1 );
  TEST_ASSERT( endlib_file_handler.endOfFile() );

  // Close the test table file
  endlib_file_handler.closeENDLIB97File();
}

//---------------------------------------------------------------------------//
// Check that the ENDLIB97FileHandler can skip a four column table and then 
// skip a four column table
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, four_column_table_skip_skip_test )
{ 
  FACEMC::ENDLIB97FileHandler endlib_file_handler( TWO_FOUR_COLUMN_TABLES_TEST_FILE );
  
  unsigned int atomic_number_1, atomic_number_2;
  unsigned int outgoing_particle_designator_1, outgoing_particle_designator_2;
  double atomic_weight_1, atomic_weight_2;
  unsigned int interpolation_flag_1, interpolation_flag_2;
  unsigned int reaction_type_1, reaction_type_2;
  unsigned int electron_shell_1, electron_shell_2;

  endlib_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_weight_1,
					    interpolation_flag_1 );

  endlib_file_handler.readSecondTableHeader( reaction_type_1,
					     electron_shell_1 );
  
  // Skip the first table
  endlib_file_handler.skipFourColumnTable();

  endlib_file_handler.readFirstTableHeader( atomic_number_2,
					    outgoing_particle_designator_2,
					    atomic_weight_2,
					    interpolation_flag_2 );

  endlib_file_handler.readSecondTableHeader( reaction_type_2,
					     electron_shell_2 );
 
  // Skip the second table
  endlib_file_handler.skipFourColumnTable();

  // Check that the header info from both tables matches
  TEST_EQUALITY( atomic_number_1, atomic_number_2 );
  TEST_EQUALITY( outgoing_particle_designator_1,
		 outgoing_particle_designator_2 );
  TEST_EQUALITY( atomic_weight_1, atomic_weight_2 );
  TEST_EQUALITY( interpolation_flag_1, interpolation_flag_2 );
  TEST_EQUALITY( reaction_type_1, reaction_type_2 );
  TEST_EQUALITY( electron_shell_1, electron_shell_2 ); 

  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endlib_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_weight_1,
					    interpolation_flag_1 );
  TEST_ASSERT( endlib_file_handler.endOfFile() );

  // Close the test table file
  endlib_file_handler.closeENDLIB97File();
}

//---------------------------------------------------------------------------//
// Check that the ENDLIB97FileHandler can skip a four column table and then 
// read a four column table
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, four_column_table_skip_read_test )
{
  FACEMC::ENDLIB97FileHandler endlib_file_handler( TWO_FOUR_COLUMN_TABLES_TEST_FILE );
  
  unsigned int atomic_number_1, atomic_number_2;
  unsigned int outgoing_particle_designator_1, outgoing_particle_designator_2;
  double atomic_weight_1, atomic_weight_2;
  unsigned int interpolation_flag_1, interpolation_flag_2;
  unsigned int reaction_type_1, reaction_type_2;
  unsigned int electron_shell_1, electron_shell_2;

  endlib_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_weight_1,
					    interpolation_flag_1 );

  endlib_file_handler.readSecondTableHeader( reaction_type_1,
					     electron_shell_1 );
  
  // Skip the first table
  endlib_file_handler.skipFourColumnTable();

  endlib_file_handler.readFirstTableHeader( atomic_number_2,
					    outgoing_particle_designator_2,
					    atomic_weight_2,
					    interpolation_flag_2 );

  endlib_file_handler.readSecondTableHeader( reaction_type_2,
					     electron_shell_2 );
  
  Teuchos::Array<FACEMC::Quad<unsigned int,unsigned int,double,double> > data;
  
  // Read the second table
  endlib_file_handler.readFourColumnTable( data );

  // Check that the header info from both tables matches
  TEST_EQUALITY( atomic_number_1, atomic_number_2 );
  TEST_EQUALITY( outgoing_particle_designator_1,
		 outgoing_particle_designator_2 );
  TEST_EQUALITY( atomic_weight_1, atomic_weight_2 );
  TEST_EQUALITY( interpolation_flag_1, interpolation_flag_2 );
  TEST_EQUALITY( reaction_type_1, reaction_type_2 );
  TEST_EQUALITY( electron_shell_1, electron_shell_2 );  

  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endlib_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_weight_1,
					    interpolation_flag_1 );
  TEST_ASSERT( endlib_file_handler.endOfFile() );

  // Close the test table file
  endlib_file_handler.closeENDLIB97File();
}

//---------------------------------------------------------------------------//
// Check that the ENDLIB97FileHandler can read a four column table and then 
// skip a four column table
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, four_column_table_read_skip_test )
{
  FACEMC::ENDLIB97FileHandler endlib_file_handler( TWO_FOUR_COLUMN_TABLES_TEST_FILE );
  
  unsigned int atomic_number_1, atomic_number_2;
  unsigned int outgoing_particle_designator_1, outgoing_particle_designator_2;
  double atomic_weight_1, atomic_weight_2;
  unsigned int interpolation_flag_1, interpolation_flag_2;
  unsigned int reaction_type_1, reaction_type_2;
  unsigned int electron_shell_1, electron_shell_2;

  endlib_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_weight_1,
					    interpolation_flag_1 );

  endlib_file_handler.readSecondTableHeader( reaction_type_1,
					     electron_shell_1 );
  
  // Read the first table
  Teuchos::Array<FACEMC::Quad<unsigned int,unsigned int,double,double> > data;
  
  endlib_file_handler.readFourColumnTable( data );

  endlib_file_handler.readFirstTableHeader( atomic_number_2,
					    outgoing_particle_designator_2,
					    atomic_weight_2,
					    interpolation_flag_2 );

  endlib_file_handler.readSecondTableHeader( reaction_type_2,
					     electron_shell_2 );
  
  // Skip the second table
  endlib_file_handler.skipFourColumnTable();

  // Check that the header info from both tables matches
  TEST_EQUALITY( atomic_number_1, atomic_number_2 );
  TEST_EQUALITY( outgoing_particle_designator_1,
		 outgoing_particle_designator_2 );
  TEST_EQUALITY( atomic_weight_1, atomic_weight_2 );
  TEST_EQUALITY( interpolation_flag_1, interpolation_flag_2 );
  TEST_EQUALITY( reaction_type_1, reaction_type_2 );
  TEST_EQUALITY( electron_shell_1, electron_shell_2 );  

  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endlib_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_weight_1,
					    interpolation_flag_1 );
  TEST_ASSERT( endlib_file_handler.endOfFile() );

  // Close the test table file
  endlib_file_handler.closeENDLIB97File();
}

//---------------------------------------------------------------------------//
// Check that the ENDLIB97FileHandler can read a four column table and then 
// read a four column table
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, four_column_table_read_read_test )
{
  FACEMC::ENDLIB97FileHandler endlib_file_handler( TWO_FOUR_COLUMN_TABLES_TEST_FILE );
  
  unsigned int atomic_number_1, atomic_number_2;
  unsigned int outgoing_particle_designator_1, outgoing_particle_designator_2;
  double atomic_weight_1, atomic_weight_2;
  unsigned int interpolation_flag_1, interpolation_flag_2;
  unsigned int reaction_type_1, reaction_type_2;
  unsigned int electron_shell_1, electron_shell_2;
  Teuchos::Array<FACEMC::Quad<unsigned int,unsigned int,double,double> > 
    data_1, data_2;

  endlib_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_weight_1,
					    interpolation_flag_1 );

  endlib_file_handler.readSecondTableHeader( reaction_type_1,
					     electron_shell_1 );
  
  // Read the first table
  endlib_file_handler.readFourColumnTable( data_1 );

  endlib_file_handler.readFirstTableHeader( atomic_number_2,
					    outgoing_particle_designator_2,
					    atomic_weight_2,
					    interpolation_flag_2 );

  endlib_file_handler.readSecondTableHeader( reaction_type_2,
					     electron_shell_2 );
  
  // Read the second table
  endlib_file_handler.readFourColumnTable( data_2 );

  // Check that the header info from both tables matches
  TEST_EQUALITY( atomic_number_1, atomic_number_2 );
  TEST_EQUALITY( outgoing_particle_designator_1,
		 outgoing_particle_designator_2 );
  TEST_EQUALITY( atomic_weight_1, atomic_weight_2 );
  TEST_EQUALITY( interpolation_flag_1, interpolation_flag_2 );
  TEST_EQUALITY( reaction_type_1, reaction_type_2 );
  TEST_EQUALITY( electron_shell_1, electron_shell_2 );  
  FACEMC_TEST_COMPARE_ARRAYS( data_1, data_2 );

  // Check that the entire table was read - attempting to read the first
  // header again will set the eof bit
  endlib_file_handler.readFirstTableHeader( atomic_number_1,
					    outgoing_particle_designator_1,
					    atomic_weight_1,
					    interpolation_flag_1 );
  TEST_ASSERT( endlib_file_handler.endOfFile() );

  // Close the test table file
  endlib_file_handler.closeENDLIB97File();
}
  
//---------------------------------------------------------------------------//
// end tstENDLIB97FileHandler.cpp
//---------------------------------------------------------------------------//

