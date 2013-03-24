//---------------------------------------------------------------------------//
// \file   tstBooleanCellFunctor.cpp
// \author Alex Robinson
// \brief  BooleanCellFunctor unit tests
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <string>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FACEMC Includes
#include "BooleanCellFunctor.hpp"
#include "FACEMC_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Info
//---------------------------------------------------------------------------//
#define CELL_DEFINITION_1 "10 n -11 n -5 u 200 n 2 u 3 u 4 n -1000 u 50"
#define COMPRESSED_CELL_DEFINITION_1 "10n-11n-5u200n2u3u4n-1000u50"
#define RENAMED_CELL_DEFINITION_1 "0n1n2u3n4u5u6n7u8"
#define REDUCED_CELL_DEFINITION_1 "0n1n2u3n4u5u6n7u8" 
#define CELL_DEFINITION_2 "(4 u -3 u   -10) n (5 n 6 u -100 ) u -1 n -2"
#define COMPRESSED_CELL_DEFINITION_2 "(4u-3u-10)n(5n6u-100)u-1n-2"
#define RENAMED_CELL_DEFINITION_2 "(0u1u2)n(3n4u5)u6n7"
#define REDUCED_CELL_DEFINITION_2 "d0nd1u6n7"
#define CELL_DEFINITION_3 "-2 n -5 n 3 n ( 4 n 5 n (8 u 9) u (10 u -11) n 6 )"
#define COMPRESSED_CELL_DEFINITION_3 "-2n-5n3n(4n5n(8u9)u(10u-11)n6)"
#define RENAMED_CELL_DEFINITION_3 "0n1n2n(3n4n(5u6)u(7u8)n9)"
#define REDUCED_CELL_DEFINITION_3 "0n1n2nd0"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//

class TestBooleanCellFunctor : public FACEMC::BooleanCellFunctor
{
public:
  TestBooleanCellFunctor()
    : FACEMC::BooleanCellFunctor()
  { /* ... */ }

  TestBooleanCellFunctor( std::string &cell_definition )
    : FACEMC::BooleanCellFunctor( cell_definition )
  { /* ... */ }

  virtual ~TestBooleanCellFunctor()
  { /* ... */ }

  // Allow public access to the BooleanCellFunctor protected member functions
  using FACEMC::BooleanCellFunctor::removeWhiteSpace;
  using FACEMC::BooleanCellFunctor::renameVariables;
  using FACEMC::BooleanCellFunctor::getNumberOfVariables;
  using FACEMC::BooleanCellFunctor::getVariableRange;
  using FACEMC::BooleanCellFunctor::constructChildFunctors;
  using FACEMC::BooleanCellFunctor::reduceDefinition;
  using FACEMC::BooleanCellFunctor::assignSetOperationFunctors;
  using FACEMC::BooleanCellFunctor::getNumChildFunctors;
  using FACEMC::BooleanCellFunctor::getNumSetOperationFunctors;
  using FACEMC::BooleanCellFunctor::getChildFunctorVariableRanges;
};

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the BooleanCellFunctor can remove white space from the cell
// definition string
TEUCHOS_UNIT_TEST( BooleanCellFunctor, removeWhiteSpace )
{
  TestBooleanCellFunctor cell_functor;

  std::string cell_definition = CELL_DEFINITION_1;
  
  cell_functor.removeWhiteSpace( cell_definition );

  TEST_ASSERT( cell_definition.compare( 0, 
					std::string::npos,
					COMPRESSED_CELL_DEFINITION_1 ) == 0 );

  cell_definition = CELL_DEFINITION_2;
  
  cell_functor.removeWhiteSpace( cell_definition );

  TEST_ASSERT( cell_definition.compare( 0, 
					std::string::npos,
					COMPRESSED_CELL_DEFINITION_2 ) == 0 );

  cell_definition = CELL_DEFINITION_3;

  cell_functor.removeWhiteSpace( cell_definition );
  
  TEST_ASSERT( cell_definition.compare( 0,
					std::string::npos,
					COMPRESSED_CELL_DEFINITION_3 ) == 0 );
}

//---------------------------------------------------------------------------//
// Check that the BooleanCellFunctor can rename the variables in the cell
// definition string
TEUCHOS_UNIT_TEST( BooleanCellFunctor, renameVariables )
{
  TestBooleanCellFunctor cell_functor;

  std::string cell_definition = CELL_DEFINITION_1;
  
  cell_functor.removeWhiteSpace( cell_definition );
  cell_functor.renameVariables( cell_definition );

  TEST_ASSERT( cell_definition.compare( 0,
					std::string::npos,
					RENAMED_CELL_DEFINITION_1 ) == 0 );

  cell_definition = CELL_DEFINITION_2;

  cell_functor.removeWhiteSpace( cell_definition );
  cell_functor.renameVariables( cell_definition );

  TEST_ASSERT( cell_definition.compare( 0,
					std::string::npos,
					RENAMED_CELL_DEFINITION_2 ) == 0 );

  cell_definition = CELL_DEFINITION_3;

  cell_functor.removeWhiteSpace( cell_definition );
  cell_functor.renameVariables( cell_definition );

  TEST_ASSERT( cell_definition.compare( 0,
					std::string::npos,
					RENAMED_CELL_DEFINITION_3 ) == 0 );
}

//---------------------------------------------------------------------------//
// Check that the BooleanCellFunctor can determine the number of variables in 
// the cell definition string
TEUCHOS_UNIT_TEST( BooleanCellFunctor, getNumberOfVariables )
{
  TestBooleanCellFunctor cell_functor;

  std::string cell_definition = CELL_DEFINITION_1;
  unsigned number_of_variables, ref_number_of_variables;
  ref_number_of_variables = 9;  
  
  cell_functor.removeWhiteSpace( cell_definition );
  cell_functor.renameVariables( cell_definition );
  number_of_variables = cell_functor.getNumberOfVariables( cell_definition );

  TEST_EQUALITY( number_of_variables, ref_number_of_variables );

  cell_definition = CELL_DEFINITION_2;
  ref_number_of_variables = 8;

  cell_functor.removeWhiteSpace( cell_definition );
  cell_functor.renameVariables( cell_definition );
  number_of_variables = cell_functor.getNumberOfVariables( cell_definition );

  TEST_EQUALITY( number_of_variables, ref_number_of_variables );

  cell_definition = CELL_DEFINITION_3;
  ref_number_of_variables = 10;

  cell_functor.removeWhiteSpace( cell_definition );
  cell_functor.renameVariables( cell_definition );
  number_of_variables = cell_functor.getNumberOfVariables( cell_definition );

  TEST_EQUALITY( number_of_variables, ref_number_of_variables );
}

//---------------------------------------------------------------------------//
// Check that the BooleanCellFunctor can determine the range of variables
// in a renamed cell definition string
TEUCHOS_UNIT_TEST( BooleanCellFunctor, getVariableRange )
{
  TestBooleanCellFunctor cell_functor;

  std::string cell_definition = CELL_DEFINITION_1;
  FACEMC::Pair<unsigned,unsigned> range, ref_range( 0u, 8u );

  cell_functor.removeWhiteSpace( cell_definition );
  cell_functor.renameVariables( cell_definition );
  range = cell_functor.getVariableRange( cell_definition );

  FACEMC_TEST_EQUALITY( range, ref_range );

  cell_definition = CELL_DEFINITION_2;
  ref_range( 0u, 7u );

  cell_functor.removeWhiteSpace( cell_definition );
  cell_functor.renameVariables( cell_definition );
  range = cell_functor.getVariableRange( cell_definition );

  FACEMC_TEST_EQUALITY( range, ref_range );

  cell_definition = CELL_DEFINITION_3;
  ref_range( 0u, 9u );

  cell_functor.removeWhiteSpace( cell_definition );
  cell_functor.renameVariables( cell_definition );
  range = cell_functor.getVariableRange( cell_definition );

  FACEMC_TEST_EQUALITY( range, ref_range );
}

//---------------------------------------------------------------------------//
// Check that the BooleanCellFunctor can construct child functors
TEUCHOS_UNIT_TEST( BooleanCellFunctor, constructChildFunctors )
{
  TestBooleanCellFunctor cell_functor;

  std::string cell_definition = CELL_DEFINITION_1;
  unsigned number_of_children;
  Teuchos::Array<FACEMC::Pair<unsigned,unsigned> > 
    variable_ranges, ref_variable_ranges;

  cell_functor.removeWhiteSpace( cell_definition );
  cell_functor.renameVariables( cell_definition );
  cell_functor.constructChildFunctors( cell_definition );
  number_of_children = cell_functor.getNumChildFunctors();
  
  TEST_EQUALITY_CONST( number_of_children, 0 );

  cell_definition = CELL_DEFINITION_2;
  ref_variable_ranges.resize( 2 );
  ref_variable_ranges[0]( 0u, 2u );
  ref_variable_ranges[1]( 3u, 5u );

  cell_functor.removeWhiteSpace( cell_definition );
  cell_functor.renameVariables( cell_definition );
  cell_functor.constructChildFunctors( cell_definition );
  number_of_children = cell_functor.getNumChildFunctors();
  variable_ranges = cell_functor.getChildFunctorVariableRanges();

  TEST_EQUALITY_CONST( number_of_children, 2 );
  FACEMC_TEST_COMPARE_ARRAYS( variable_ranges, ref_variable_ranges );

  cell_definition = CELL_DEFINITION_3;
  ref_variable_ranges.resize( 1 );
  ref_variable_ranges[0]( 3u, 9u );

  cell_functor.removeWhiteSpace( cell_definition );
  cell_functor.renameVariables( cell_definition );
  cell_functor.constructChildFunctors( cell_definition );
  number_of_children = cell_functor.getNumChildFunctors();
  variable_ranges = cell_functor.getChildFunctorVariableRanges();

  TEST_EQUALITY_CONST( number_of_children, 1 );
  FACEMC_TEST_COMPARE_ARRAYS( variable_ranges, ref_variable_ranges );

}

//---------------------------------------------------------------------------//
// Check that the BooleanCellFunctor can reduce the cell definition after
// the child functors have been constructed
TEUCHOS_UNIT_TEST( BooleanCellFunctor, reduceDefinition )
{
  TestBooleanCellFunctor cell_functor;

  std::string cell_definition = CELL_DEFINITION_1;

  cell_functor.removeWhiteSpace( cell_definition );
  cell_functor.renameVariables( cell_definition );
  cell_functor.constructChildFunctors( cell_definition );
  cell_functor.reduceDefinition( cell_definition );
  
  TEST_ASSERT( cell_definition.compare( 0, 
					std::string::npos,
					REDUCED_CELL_DEFINITION_1 ) == 0 );
  
  cell_definition = CELL_DEFINITION_2;

  cell_functor.removeWhiteSpace( cell_definition );
  cell_functor.renameVariables( cell_definition );
  cell_functor.constructChildFunctors( cell_definition );
  cell_functor.reduceDefinition( cell_definition );
  
  TEST_ASSERT( cell_definition.compare( 0, 
					std::string::npos,
					REDUCED_CELL_DEFINITION_2 ) == 0 );

  cell_definition = CELL_DEFINITION_3;

  cell_functor.removeWhiteSpace( cell_definition );
  cell_functor.renameVariables( cell_definition );
  cell_functor.constructChildFunctors( cell_definition );
  cell_functor.reduceDefinition( cell_definition );

  TEST_ASSERT( cell_definition.compare( 0, 
					std::string::npos,
					REDUCED_CELL_DEFINITION_3 ) == 0 ); 
}

//---------------------------------------------------------------------------//
// Check that the BooleanCellFunctor can assign the SetOperationFunctors
// after the cell definition has been reduced
TEUCHOS_UNIT_TEST( BooleanCellFunctor, assignSetOperationFunctors )
{
  TestBooleanCellFunctor cell_functor;

  std::string cell_definition = CELL_DEFINITION_1;
  unsigned number_of_set_op_functors;

  cell_functor.removeWhiteSpace( cell_definition );
  cell_functor.renameVariables( cell_definition );
  cell_functor.constructChildFunctors( cell_definition );
  cell_functor.reduceDefinition( cell_definition );
  cell_functor.assignSetOperationFunctors( cell_definition );
  number_of_set_op_functors = cell_functor.getNumSetOperationFunctors();

  TEST_EQUALITY_CONST( number_of_set_op_functors, 8 );

  cell_definition = CELL_DEFINITION_2;

  cell_functor.removeWhiteSpace( cell_definition );
  cell_functor.renameVariables( cell_definition );
  cell_functor.constructChildFunctors( cell_definition );
  cell_functor.reduceDefinition( cell_definition );
  cell_functor.assignSetOperationFunctors( cell_definition );
  number_of_set_op_functors = cell_functor.getNumSetOperationFunctors();

  TEST_EQUALITY_CONST( number_of_set_op_functors, 3 );

  cell_definition = CELL_DEFINITION_3;

  cell_functor.removeWhiteSpace( cell_definition );
  cell_functor.renameVariables( cell_definition );
  cell_functor.constructChildFunctors( cell_definition );
  cell_functor.reduceDefinition( cell_definition );
  cell_functor.assignSetOperationFunctors( cell_definition );
  number_of_set_op_functors = cell_functor.getNumSetOperationFunctors();

  TEST_EQUALITY_CONST( number_of_set_op_functors, 3 );
}
  
//---------------------------------------------------------------------------//
// Check that the BooleanCellFunctor evaluates the cell function correctly
TEUCHOS_UNIT_TEST( BooleanCellFunctor, operator )
{
  std::string cell_definition( CELL_DEFINITION_1 );
  
  Teuchos::RCP<FACEMC::BooleanCellFunctor> 
    cell_functor( new FACEMC::BooleanCellFunctor( cell_definition ) );

  std::list<bool> argument_list;
  argument_list.push_back( true );
  argument_list.push_back( true );
  argument_list.push_back( true );
  argument_list.push_back( true );
  argument_list.push_back( true );
  argument_list.push_back( true );
  argument_list.push_back( true );
  argument_list.push_back( true );
  argument_list.push_back( true );

  TEST_ASSERT( (*cell_functor)( argument_list ) );
  
  argument_list.clear();
  argument_list.push_back( true );
  argument_list.push_back( true );
  argument_list.push_back( true );
  argument_list.push_back( false );
  argument_list.push_back( true );
  argument_list.push_back( false );
  argument_list.push_back( false );
  argument_list.push_back( true );
  argument_list.push_back( false );

  TEST_ASSERT( (*cell_functor)( argument_list ) );

  argument_list.clear();
  argument_list.push_back( false );
  argument_list.push_back( true );
  argument_list.push_back( true );
  argument_list.push_back( false );
  argument_list.push_back( true );
  argument_list.push_back( false );
  argument_list.push_back( false );
  argument_list.push_back( true );
  argument_list.push_back( false );

  TEST_ASSERT( !(*cell_functor)( argument_list ) );

  cell_definition = CELL_DEFINITION_2;
  
  cell_functor.reset( new FACEMC::BooleanCellFunctor( cell_definition ) );

  argument_list.clear();
  argument_list.push_back( true );
  argument_list.push_back( true );
  argument_list.push_back( true );
  argument_list.push_back( true );
  argument_list.push_back( true );
  argument_list.push_back( true );
  argument_list.push_back( true );
  argument_list.push_back( true );

  TEST_ASSERT( (*cell_functor)( argument_list ) );

  argument_list.clear();
  argument_list.push_back( true );
  argument_list.push_back( false );
  argument_list.push_back( false );
  argument_list.push_back( true );
  argument_list.push_back( true );
  argument_list.push_back( false );
  argument_list.push_back( false );
  argument_list.push_back( true );

  TEST_ASSERT( (*cell_functor)( argument_list ) );

  argument_list.clear();
  argument_list.push_back( false );
  argument_list.push_back( false );
  argument_list.push_back( false );
  argument_list.push_back( true );
  argument_list.push_back( true );
  argument_list.push_back( false );
  argument_list.push_back( false );
  argument_list.push_back( true );

  TEST_ASSERT( !(*cell_functor)( argument_list ) );

  cell_definition = CELL_DEFINITION_3;
  
  cell_functor.reset( new FACEMC::BooleanCellFunctor( cell_definition ) );

  argument_list.clear();
  argument_list.push_back( true );
  argument_list.push_back( true );
  argument_list.push_back( true );
  argument_list.push_back( true );
  argument_list.push_back( true );
  argument_list.push_back( true );
  argument_list.push_back( true );
  argument_list.push_back( true );
  argument_list.push_back( true );
  argument_list.push_back( true );

  TEST_ASSERT( (*cell_functor)( argument_list ) );

  argument_list.clear();
  argument_list.push_back( true );
  argument_list.push_back( true );
  argument_list.push_back( true );
  argument_list.push_back( true );
  argument_list.push_back( true );
  argument_list.push_back( false );
  argument_list.push_back( true );
  argument_list.push_back( false );
  argument_list.push_back( true );
  argument_list.push_back( true );

  TEST_ASSERT( (*cell_functor)( argument_list ) );

  argument_list.clear();
  argument_list.push_back( false );
  argument_list.push_back( true );
  argument_list.push_back( true );
  argument_list.push_back( true );
  argument_list.push_back( true );
  argument_list.push_back( false );
  argument_list.push_back( true );
  argument_list.push_back( false );
  argument_list.push_back( true );
  argument_list.push_back( true );

  TEST_ASSERT( !(*cell_functor)( argument_list ) );
}
  

//---------------------------------------------------------------------------//
// end tstBooleanCellFunctor.cpp
//---------------------------------------------------------------------------//

