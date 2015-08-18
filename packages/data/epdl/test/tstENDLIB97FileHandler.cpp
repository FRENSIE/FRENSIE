//---------------------------------------------------------------------------//
//!
//! \file   tstENDLIB97FileHandler.cpp
//! \author Alex Robinson
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
#include "Data_ENDLIB97FileHandler.hpp"
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
#define TOL 1e-12

//---------------------------------------------------------------------------//
// Instantiation Macros.
//---------------------------------------------------------------------------//
#define TUPLE_TYPEDEFS()						\
  typedef Utility::Pair<double,double> pair_d_d;			\
  typedef Utility::Pair<unsigned,double> pair_u_d;			\
  typedef Utility::Trip<double,double,double> trip_d_d_d;		\
  typedef Utility::Trip<unsigned,double,double> trip_u_d_d;		\
  typedef Utility::Quad<double,double,double,double> quad_d_d_d_d;	\
  typedef Utility::Quad<unsigned,unsigned,double,double> quad_u_u_d_d;	\

#define UNIT_TEST_INSTANTIATION( type, name )			\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, double )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, unsigned )	\

#define UNIT_TEST_INSTANTIATION_PAIR( type, name )			\
  TUPLE_TYPEDEFS()							\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, pair_d_d )		\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, pair_u_d )		\

#define UNIT_TEST_INSTANTIATION_TRIP( type, name )			\
  TUPLE_TYPEDEFS()							\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, trip_d_d_d )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, trip_u_d_d )	\

#define UNIT_TEST_INSTANTIATION_QUAD( type, name )			\
  TUPLE_TYPEDEFS()							\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, quad_d_d_d_d )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, quad_u_u_d_d )	\

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
class TestENDLIB97FileHandler : public Data::ENDLIB97FileHandler
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
  using Data::ENDLIB97FileHandler::extractValue;
};  

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the ENDLIB97FileHandler can open a file when constructed
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, constructor )
{
  // If DBC is turned on, the constructor will throw an exception and exit
  // if this file does not exist. No Testing Macro is needed.
  Data::ENDLIB97FileHandler endlib_file_handler( first_header_test_file );
}

//---------------------------------------------------------------------------//
// Check that the ENDLIB97FileHandler can open a file after being contructed
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, openENDLIB97File )
{
  Data::ENDLIB97FileHandler endlib_file_handler;
  
  // If DBC is turned on, the constructor will throw an exception and exit
  // if this file does not exist. No Testing Macro is needed.
  endlib_file_handler.openENDLIB97File( first_header_test_file );
}

//---------------------------------------------------------------------------//
// Check that the ENDLIB97FileHandler can indicate that a file is valid
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, validFile )
{
  Data::ENDLIB97FileHandler endlib_file_handler;

  endlib_file_handler.openENDLIB97File( first_header_test_file );
  
  TEST_ASSERT( endlib_file_handler.validFile() );
}

//---------------------------------------------------------------------------//
// Check that the ENDLIB97FileHandler can extract a double from a FORTRAN 
// fixed width float
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ENDLIB97FileHandler, extractValue, Type )
{
  std::string mantissa_with_pos(" 1.00000+");
  std::string mantissa_with_neg(" 1.00000-");
  std::string exponent("10");

  std::string mantissa(" 1.00000");
  std::string exponent_with_pos("+2");
  std::string exponent_with_neg("-2");
  std::string exponent_zero(" 0");
  
  TestENDLIB97FileHandler test_file_handler;
  
  // test all possible mantissa, exponent combinations
  Type combination_1;
  Type combination_2;
  Type combination_3;
  Type combination_4;
  Type combination_5;
  
  combination_1 = test_file_handler.extractValue<Type>( mantissa_with_pos,
							exponent );
  combination_2 = test_file_handler.extractValue<Type>( mantissa_with_neg,
							exponent );
  combination_3 = test_file_handler.extractValue<Type>( mantissa,
							exponent_with_pos );
  combination_4 = test_file_handler.extractValue<Type>( mantissa,
							exponent_with_neg );
  combination_5 = test_file_handler.extractValue<Type>( mantissa,
							exponent_zero );

  Type true_value_1 = static_cast<Type>( 1.0e10 );
  Type true_value_2 = static_cast<Type>( 1.0e-10 );
  Type true_value_3 = static_cast<Type>( 1.0e2 );
  Type true_value_4 = static_cast<Type>( 1.0e-2 );
  Type true_value_5 = static_cast<Type>( 1.0 );
  
  // The first combination will be too large for an ordinal type
  if( !Teuchos::ScalarTraits<Type>::isOrdinal )
    TEST_EQUALITY( combination_1, true_value_1 );

  TEST_EQUALITY( combination_2, true_value_2 );
  TEST_EQUALITY( combination_3, true_value_3 );
  TEST_EQUALITY( combination_4, true_value_4 );
  TEST_EQUALITY( combination_5, true_value_5 );
}

UNIT_TEST_INSTANTIATION( ENDLIB97FileHandler, extractValue );

//---------------------------------------------------------------------------//
// Check that the ENDLIB97FileHandler can read the first header of a table
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, readFirstTableHeader )
{
  Data::ENDLIB97FileHandler endlib_file_handler( first_header_test_file );
  
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
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, readSecondTableHeader )
{
  std::cout << second_header_test_file << std::endl;
  Data::ENDLIB97FileHandler endlib_file_handler( second_header_test_file );
  
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
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, read_full_header_test )
{
  Data::ENDLIB97FileHandler endlib_file_handler( full_header_test_file );
  
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
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, skipTwoColumnTable )
{
  Data::ENDLIB97FileHandler endlib_file_handler( two_column_table_test_file );
  
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
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, skipThreeColumnTable )
{
  Data::ENDLIB97FileHandler endlib_file_handler( three_column_table_test_file );
  
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
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, skipFourColumnTable )
{
  Data::ENDLIB97FileHandler endlib_file_handler( four_column_table_test_file );
  
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
// Check that the ENDLIB97FileHandler can read a two column table
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ENDLIB97FileHandler,
				   readTwoColumnTable,
				   Tuple )
{
  Data::ENDLIB97FileHandler endlib_file_handler( two_column_table_test_file );
  
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

  Teuchos::Array<Tuple> data, data_true;

  endlib_file_handler.readTwoColumnTable( data );

  fillTwoColumnTestingArray( data_true );

  UTILITY_TEST_COMPARE_ARRAYS( data, data_true );

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

UNIT_TEST_INSTANTIATION_PAIR( ENDLIB97FileHandler, readTwoColumnTable );
UNIT_TEST_INSTANTIATION_TRIP( ENDLIB97FileHandler, readTwoColumnTable );
UNIT_TEST_INSTANTIATION_QUAD( ENDLIB97FileHandler, readTwoColumnTable );

//---------------------------------------------------------------------------//
// Check that the ENDLIB97FileHandler can process a two column table
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, processTwoColumnTable )
{
  Data::ENDLIB97FileHandler endlib_file_handler( two_column_table_test_file );
  
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

  std::vector<double> indep, dep, indep_true, dep_true;

  endlib_file_handler.processTwoColumnTable( indep, dep );

  processTwoColumnTestingArray( indep_true, dep_true );

  UTILITY_TEST_COMPARE_ARRAYS( indep, indep_true );
  UTILITY_TEST_COMPARE_ARRAYS( dep, dep_true );

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
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ENDLIB97FileHandler, 
				   readThreeColumnTable,
				   Tuple )
{
  Data::ENDLIB97FileHandler endlib_file_handler( three_column_table_test_file );
  
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
  
  Teuchos::Array<Tuple> data, data_true;

  endlib_file_handler.readThreeColumnTable( data );

  fillThreeColumnTestingArray( data_true );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( data, data_true, TOL );

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

UNIT_TEST_INSTANTIATION_TRIP( ENDLIB97FileHandler, readThreeColumnTable );
UNIT_TEST_INSTANTIATION_QUAD( ENDLIB97FileHandler, readThreeColumnTable );

//---------------------------------------------------------------------------//
// Check that the ENDLIB97FileHandler can process a two column table
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, processThreeColumnTable )
{
  Data::ENDLIB97FileHandler endlib_file_handler( three_column_table_test_file );
  
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

  std::vector<double> energy_bin, energy_bin_true;
  std::map<double,std::vector<double> > indep, dep, indep_true, dep_true;

  endlib_file_handler.processThreeColumnTable( energy_bin, indep, dep );

  processThreeColumnTestingArray( energy_bin_true, indep_true, dep_true );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( energy_bin, energy_bin_true, TOL );

  std::vector<double>::iterator i = energy_bin.begin();

  for ( i; i != energy_bin.end(); ++i )
  {
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( indep[*i], indep_true[*i], TOL );
  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( dep[*i], dep_true[*i], TOL );
  }

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
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ENDLIB97FileHandler, 
				   readFourColumnTable,
				   Tuple )
{
  Data::ENDLIB97FileHandler endlib_file_handler( four_column_table_test_file );
  
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
  
  Teuchos::Array<Tuple> data, data_true;

  endlib_file_handler.readFourColumnTable( data );

  fillFourColumnTestingArray( data_true );

  UTILITY_TEST_COMPARE_FLOATING_ARRAYS( data, data_true, TOL );

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

UNIT_TEST_INSTANTIATION_QUAD( ENDLIB97FileHandler, readFourColumnTable );

//---------------------------------------------------------------------------//
// Check that the ENDLIB97FileHandler can skip a two column table and then
// skip a two column table
TEUCHOS_UNIT_TEST( ENDLIB97FileHandler, two_column_table_skip_skip_test )
{
  Data::ENDLIB97FileHandler endlib_file_handler( two_two_column_tables_test_file );
  
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
  Data::ENDLIB97FileHandler endlib_file_handler( two_two_column_tables_test_file );
  
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
  
  Teuchos::Array<Utility::Pair<double,double> > data;
  
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
  Data::ENDLIB97FileHandler endlib_file_handler( two_two_column_tables_test_file );
  
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
  Teuchos::Array<Utility::Pair<double,double> > data;
  
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
  Data::ENDLIB97FileHandler endlib_file_handler( two_two_column_tables_test_file );
  
  unsigned int atomic_number_1, atomic_number_2;
  unsigned int outgoing_particle_designator_1, outgoing_particle_designator_2;
  double atomic_weight_1, atomic_weight_2;
  unsigned int interpolation_flag_1, interpolation_flag_2;
  unsigned int reaction_type_1, reaction_type_2;
  unsigned int electron_shell_1, electron_shell_2;
  Teuchos::Array<Utility::Pair<double,double> > data_1, data_2;

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
  UTILITY_TEST_COMPARE_ARRAYS( data_1, data_2 );

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
  Data::ENDLIB97FileHandler endlib_file_handler( two_three_column_tables_test_file );
  
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
  Data::ENDLIB97FileHandler endlib_file_handler( two_three_column_tables_test_file );
  
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
  Teuchos::Array<Utility::Trip<unsigned int,double,double> > data;

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
  Data::ENDLIB97FileHandler endlib_file_handler( two_three_column_tables_test_file );
  
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
  Teuchos::Array<Utility::Trip<unsigned int,double,double> > data;

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
  Data::ENDLIB97FileHandler endlib_file_handler( two_three_column_tables_test_file );
  
  unsigned int atomic_number_1, atomic_number_2;
  unsigned int outgoing_particle_designator_1, outgoing_particle_designator_2;
  double atomic_weight_1, atomic_weight_2;
  unsigned int interpolation_flag_1, interpolation_flag_2;
  unsigned int reaction_type_1, reaction_type_2;
  unsigned int electron_shell_1, electron_shell_2;
  Teuchos::Array<Utility::Trip<unsigned int,double,double> > data_1, data_2;
  
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
  UTILITY_TEST_COMPARE_ARRAYS( data_1, data_2 );
  
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
  Data::ENDLIB97FileHandler endlib_file_handler( two_four_column_tables_test_file );
  
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
  Data::ENDLIB97FileHandler endlib_file_handler( two_four_column_tables_test_file );
  
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
  
  Teuchos::Array<Utility::Quad<unsigned int,unsigned int,double,double> > data;
  
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
  Data::ENDLIB97FileHandler endlib_file_handler( two_four_column_tables_test_file );
  
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
  Teuchos::Array<Utility::Quad<unsigned int,unsigned int,double,double> > data;
  
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
  Data::ENDLIB97FileHandler endlib_file_handler( two_four_column_tables_test_file );
  
  unsigned int atomic_number_1, atomic_number_2;
  unsigned int outgoing_particle_designator_1, outgoing_particle_designator_2;
  double atomic_weight_1, atomic_weight_2;
  unsigned int interpolation_flag_1, interpolation_flag_2;
  unsigned int reaction_type_1, reaction_type_2;
  unsigned int electron_shell_1, electron_shell_2;
  Teuchos::Array<Utility::Quad<unsigned int,unsigned int,double,double> > 
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
  UTILITY_TEST_COMPARE_ARRAYS( data_1, data_2 );

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
// end tstENDLIB97FileHandler.cpp
//---------------------------------------------------------------------------//

