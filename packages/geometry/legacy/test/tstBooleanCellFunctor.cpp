//---------------------------------------------------------------------------//
//!
//! \file   tstBooleanCellFunctor.cpp
//! \author Alex Robinson
//! \brief  BooleanCellFunctor unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <string>
#include <vector>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayRCP.hpp>

// FRENSIE Includes
#include "Geometry_BooleanCellFunctor.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

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
#define CELL_DEFINITION_4 "(-1n2n-3n4n-7n8)u(-1n2n-5n6n-7n8)"
#define COMPRESSED_CELL_DEFINITION_4 "(-1n2n-3n4n-7n8)u(-1n2n-5n6n-7n8)"
#define RENAMED_CELL_DEFINITION_4 "(0n1n2n3n4n5)u(6n7n8n9n10n11)"
#define REDUCED_CELL_DEFINITION_4 "d0ud1"

//---------------------------------------------------------------------------//
// Instantiation Macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name )			\
  typedef Teuchos::ArrayRCP<bool> ArrayRCP;			\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, ArrayRCP )	\
  // typedef std::vector<bool> vector;				\
  // TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, vector )	\


//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestBooleanCellFunctor : public Geometry::BooleanCellFunctor
{
public:
  TestBooleanCellFunctor()
    : Geometry::BooleanCellFunctor()
  { /* ... */ }

  TestBooleanCellFunctor( std::string &cell_definition )
    : Geometry::BooleanCellFunctor( cell_definition )
  { /* ... */ }

  virtual ~TestBooleanCellFunctor()
  { /* ... */ }

  // Allow public access to the BooleanCellFunctor protected member functions
  using Geometry::BooleanCellFunctor::removeWhiteSpace;
  using Geometry::BooleanCellFunctor::renameVariables;
  using Geometry::BooleanCellFunctor::getNumVariables;
  using Geometry::BooleanCellFunctor::getVariableRange;
  using Geometry::BooleanCellFunctor::constructChildFunctors;
  using Geometry::BooleanCellFunctor::reduceDefinition;
  using Geometry::BooleanCellFunctor::assignSetOperationFunctors;
  using Geometry::BooleanCellFunctor::getNumChildFunctors;
  using Geometry::BooleanCellFunctor::getNumSetOperationFunctors;
  using Geometry::BooleanCellFunctor::getChildFunctorVariableRanges;
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

  cell_definition = CELL_DEFINITION_4;

  cell_functor.removeWhiteSpace( cell_definition );

  std::cout << cell_definition << std::endl;

  TEST_ASSERT( cell_definition.compare( 0,
					std::string::npos,
					COMPRESSED_CELL_DEFINITION_4 ) == 0 );
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

  cell_definition = CELL_DEFINITION_4;

  cell_functor.removeWhiteSpace( cell_definition );
  cell_functor.renameVariables( cell_definition );

  TEST_ASSERT( cell_definition.compare( 0,
					std::string::npos,
					RENAMED_CELL_DEFINITION_4 ) == 0 );
}

//---------------------------------------------------------------------------//
// Check that the BooleanCellFunctor can determine the number of variables in
// the cell definition string
TEUCHOS_UNIT_TEST( BooleanCellFunctor, getNumVariables )
{
  TestBooleanCellFunctor cell_functor;

  std::string cell_definition = CELL_DEFINITION_1;
  unsigned number_of_variables, ref_number_of_variables;
  ref_number_of_variables = 9;

  cell_functor.removeWhiteSpace( cell_definition );
  cell_functor.renameVariables( cell_definition );
  number_of_variables = cell_functor.getNumVariables( cell_definition );

  TEST_EQUALITY( number_of_variables, ref_number_of_variables );

  cell_definition = CELL_DEFINITION_2;
  ref_number_of_variables = 8;

  cell_functor.removeWhiteSpace( cell_definition );
  cell_functor.renameVariables( cell_definition );
  number_of_variables = cell_functor.getNumVariables( cell_definition );

  TEST_EQUALITY( number_of_variables, ref_number_of_variables );

  cell_definition = CELL_DEFINITION_3;
  ref_number_of_variables = 10;

  cell_functor.removeWhiteSpace( cell_definition );
  cell_functor.renameVariables( cell_definition );
  number_of_variables = cell_functor.getNumVariables( cell_definition );

  TEST_EQUALITY( number_of_variables, ref_number_of_variables );

  cell_definition = CELL_DEFINITION_4;
  ref_number_of_variables = 12;

  cell_functor.removeWhiteSpace( cell_definition );
  cell_functor.renameVariables( cell_definition );
  number_of_variables = cell_functor.getNumVariables( cell_definition );

  TEST_EQUALITY( number_of_variables, ref_number_of_variables );
}

//---------------------------------------------------------------------------//
// Check that the BooleanCellFunctor can determine the range of variables
// in a renamed cell definition string
TEUCHOS_UNIT_TEST( BooleanCellFunctor, getVariableRange )
{
  TestBooleanCellFunctor cell_functor;

  std::string cell_definition = CELL_DEFINITION_1;
  Utility::Pair<unsigned,unsigned> range, ref_range( 0u, 8u );

  cell_functor.removeWhiteSpace( cell_definition );
  cell_functor.renameVariables( cell_definition );
  range = cell_functor.getVariableRange( cell_definition );

  UTILITY_TEST_EQUALITY( range, ref_range );

  cell_definition = CELL_DEFINITION_2;
  ref_range( 0u, 7u );

  cell_functor.removeWhiteSpace( cell_definition );
  cell_functor.renameVariables( cell_definition );
  range = cell_functor.getVariableRange( cell_definition );

  UTILITY_TEST_EQUALITY( range, ref_range );

  cell_definition = CELL_DEFINITION_3;
  ref_range( 0u, 9u );

  cell_functor.removeWhiteSpace( cell_definition );
  cell_functor.renameVariables( cell_definition );
  range = cell_functor.getVariableRange( cell_definition );

  UTILITY_TEST_EQUALITY( range, ref_range );

  cell_definition = CELL_DEFINITION_4;
  ref_range( 0u, 11u );

  cell_functor.removeWhiteSpace( cell_definition );
  cell_functor.renameVariables( cell_definition );
  range = cell_functor.getVariableRange( cell_definition );

  UTILITY_TEST_EQUALITY( range, ref_range );
}

//---------------------------------------------------------------------------//
// Check that the BooleanCellFunctor can construct child functors
TEUCHOS_UNIT_TEST( BooleanCellFunctor, constructChildFunctors )
{
  TestBooleanCellFunctor cell_functor;

  std::string cell_definition = CELL_DEFINITION_1;
  unsigned number_of_children;
  Teuchos::Array<Utility::Pair<unsigned,unsigned> >
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
  UTILITY_TEST_COMPARE_ARRAYS( variable_ranges, ref_variable_ranges );

  cell_definition = CELL_DEFINITION_3;
  ref_variable_ranges.resize( 1 );
  ref_variable_ranges[0]( 3u, 9u );

  cell_functor.removeWhiteSpace( cell_definition );
  cell_functor.renameVariables( cell_definition );
  cell_functor.constructChildFunctors( cell_definition );
  number_of_children = cell_functor.getNumChildFunctors();
  variable_ranges = cell_functor.getChildFunctorVariableRanges();

  TEST_EQUALITY_CONST( number_of_children, 1 );
  UTILITY_TEST_COMPARE_ARRAYS( variable_ranges, ref_variable_ranges );

  cell_definition = CELL_DEFINITION_4;
  ref_variable_ranges.resize( 2 );
  ref_variable_ranges[0]( 0u, 5u );
  ref_variable_ranges[1]( 6u, 11u );

  cell_functor.removeWhiteSpace( cell_definition );
  cell_functor.renameVariables( cell_definition );
  cell_functor.constructChildFunctors( cell_definition );
  number_of_children = cell_functor.getNumChildFunctors();
  variable_ranges = cell_functor.getChildFunctorVariableRanges();

  TEST_EQUALITY_CONST( number_of_children, 2 );
  UTILITY_TEST_COMPARE_ARRAYS( variable_ranges, ref_variable_ranges );
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

  cell_definition = CELL_DEFINITION_4;

  cell_functor.removeWhiteSpace( cell_definition );
  cell_functor.renameVariables( cell_definition );
  cell_functor.constructChildFunctors( cell_definition );
  cell_functor.reduceDefinition( cell_definition );

  TEST_ASSERT( cell_definition.compare( 0,
					std::string::npos,
					REDUCED_CELL_DEFINITION_4 ) == 0 );
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

  cell_definition = CELL_DEFINITION_4;

  cell_functor.removeWhiteSpace( cell_definition );
  cell_functor.renameVariables( cell_definition );
  cell_functor.constructChildFunctors( cell_definition );
  cell_functor.reduceDefinition( cell_definition );
  cell_functor.assignSetOperationFunctors( cell_definition );
  number_of_set_op_functors = cell_functor.getNumSetOperationFunctors();

  TEST_EQUALITY_CONST( number_of_set_op_functors, 1 );
}

//---------------------------------------------------------------------------//
// Check that the BooleanCellFunctor evaluates the cell function correctly
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( BooleanCellFunctor,
				   operator,
				   BooleanArray )
{
  std::string cell_definition( CELL_DEFINITION_1 );

  Teuchos::RCP<Geometry::BooleanCellFunctor>
    cell_functor( new Geometry::BooleanCellFunctor( cell_definition ) );

  BooleanArray arguments( 9 );
  arguments[0] = true;
  arguments[1] = true;
  arguments[2] = true;
  arguments[3] = true;
  arguments[4] = true;
  arguments[5] = true;
  arguments[6] = true;
  arguments[7] = true;
  arguments[8] = true;

  TEST_ASSERT( (*cell_functor)( arguments ) );

  arguments[0] = true;
  arguments[1] = true;
  arguments[2] = true;
  arguments[3] = false;
  arguments[4] = true;
  arguments[5] = false;
  arguments[6] = false;
  arguments[7] = true;
  arguments[8] = false;

  TEST_ASSERT( (*cell_functor)( arguments ) );

  arguments[0] = false;
  arguments[1] = true;
  arguments[2] = true;
  arguments[3] = false;
  arguments[4] = true;
  arguments[5] = false;
  arguments[6] = false;
  arguments[7] = true;
  arguments[8] = false;

  TEST_ASSERT( !(*cell_functor)( arguments ) );

  cell_definition = CELL_DEFINITION_2;

  cell_functor.reset( new Geometry::BooleanCellFunctor( cell_definition ) );

  arguments.resize( 8 );
  arguments[0] = true;
  arguments[1] = true;
  arguments[2] = true;
  arguments[3] = true;
  arguments[4] = true;
  arguments[5] = true;
  arguments[6] = true;
  arguments[7] = true;

  TEST_ASSERT( (*cell_functor)( arguments ) );

  arguments[0] = true;
  arguments[1] = false;
  arguments[2] = false;
  arguments[3] = true;
  arguments[4] = true;
  arguments[5] = false;
  arguments[6] = false;
  arguments[7] = true;

  TEST_ASSERT( (*cell_functor)( arguments ) );

  arguments[0] = false;
  arguments[1] = false;
  arguments[2] = false;
  arguments[3] = true;
  arguments[4] = true;
  arguments[5] = false;
  arguments[6] = false;
  arguments[7] = true;

  TEST_ASSERT( !(*cell_functor)( arguments ) );

  cell_definition = CELL_DEFINITION_3;

  cell_functor.reset( new Geometry::BooleanCellFunctor( cell_definition ) );

  arguments.resize( 10 );
  arguments[0] = true;
  arguments[1] = true;
  arguments[2] = true;
  arguments[3] = true;
  arguments[4] = true;
  arguments[5] = true;
  arguments[6] = true;
  arguments[7] = true;
  arguments[8] = true;
  arguments[9] = true;

  TEST_ASSERT( (*cell_functor)( arguments ) );

  arguments[0] = true;
  arguments[1] = true;
  arguments[2] = true;
  arguments[3] = true;
  arguments[4] = true;
  arguments[5] = false;
  arguments[6] = true;
  arguments[7] = false;
  arguments[8] = true;
  arguments[9] = true;

  TEST_ASSERT( (*cell_functor)( arguments ) );

  arguments[0] = false;
  arguments[1] = true;
  arguments[2] = true;
  arguments[3] = true;
  arguments[4] = true;
  arguments[5] = false;
  arguments[6] = true;
  arguments[7] = false;
  arguments[8] = true;
  arguments[9] = true;

  TEST_ASSERT( !(*cell_functor)( arguments ) );

  cell_definition = CELL_DEFINITION_4;

  cell_functor.reset( new Geometry::BooleanCellFunctor( cell_definition ) );

  arguments.resize( 12 );
  arguments[0] = true;
  arguments[1] = true;
  arguments[2] = true;
  arguments[3] = true;
  arguments[4] = true;
  arguments[5] = true;
  arguments[6] = true;
  arguments[7] = true;
  arguments[8] = true;
  arguments[9] = true;
  arguments[10] = true;
  arguments[11] = true;

  TEST_ASSERT( (*cell_functor)( arguments ) );

  arguments[0] = false;
  arguments[1] = true;
  arguments[2] = true;
  arguments[3] = true;
  arguments[4] = true;
  arguments[5] = true;
  arguments[6] = true;
  arguments[7] = true;
  arguments[8] = true;
  arguments[9] = true;
  arguments[10] = true;
  arguments[11] = true;

  TEST_ASSERT( (*cell_functor)( arguments ) );

  arguments[0] = false;
  arguments[1] = true;
  arguments[2] = true;
  arguments[3] = true;
  arguments[4] = true;
  arguments[5] = true;
  arguments[6] = false;
  arguments[7] = true;
  arguments[8] = true;
  arguments[9] = true;
  arguments[10] = true;
  arguments[11] = true;

  TEST_ASSERT( !(*cell_functor)( arguments ) );
}

UNIT_TEST_INSTANTIATION( BooleanCellFunctor, operator );


//---------------------------------------------------------------------------//
// end tstBooleanCellFunctor.cpp
//---------------------------------------------------------------------------//

