//---------------------------------------------------------------------------//
//!
//! \file   Geometry_BooleanCellFunctor.cpp
//! \author Alex Robinson
//! \brief  BooleanCellFunctor definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <sstream>
#include <list>
#include <iterator>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Geometry_BooleanCellFunctor.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_SetOperationFunctor.hpp"
#include "Utility_DesignByContract.hpp"

namespace Geometry{

// Constructor
/*! \details The cell definition string contains the logical combination
 * of second order surfaces which define the cell. Only the logical operators
 * that define the cell will be recorded during object construction. All
 * surface numbers and senses will be ignored. During construction, all white
 * space is first removed from the string. Next, all surface numbers in the
 * string are renumbered according to the order in which they appear (even
 * duplicates are given new numbers). For every parentheses present in the
 * cell definition string, a new child BooleanCellFunctor will be created.
 * The parentheses will then be reduced to a single new variable. Finally,
 * the logical operators in the cell definition are recorded in an array
 * of SetOperationFunctors.
 * \param[in] cell_definition A cell definition string which contains the
 * logical combination of second order surfaces which define the cell. The
 * string is not passed by reference so that a copy is made.
 */
BooleanCellFunctor::BooleanCellFunctor( std::string cell_definition )
{
  removeWhiteSpace( cell_definition );
  renameVariables( cell_definition );
  d_number_of_variables = getNumVariables( cell_definition );
  if( d_number_of_variables > 1 )
  {
    constructChildFunctors( cell_definition );
    reduceDefinition( cell_definition );
    assignSetOperationFunctors( cell_definition );
  }

  // At least one variable must be assigned to this BooleanCellFunctor
  testPostcondition( d_number_of_variables > 0 );
}

// Remove white space from the cell definition string
/*! \details This function removes white space from the cell definition string.
 * It is only called by the constructor. It is a protected member and not a
 * private member to allow for "white-box" unit testing.
 * \param[in,out] cell_definition a cell definition string which contains the
 * logical combination of second order surfaces which define the cell. The
 * string is passed by reference so that is can be modified.
 * \pre The cell definition string must not contain any characters except the
 * ones in the following string: "0123456789-nu() ".
 * \note Developers: It might be useful to change the DBC precondition to a
 * ASSERT_ALWAYS since the failure of this precondition could cause a
 * program crash during program execution.
 */
void BooleanCellFunctor::removeWhiteSpace( std::string &cell_definition ) const
{
  // The cell definition must be valid
  testPrecondition( cell_definition.find_first_not_of( "0123456789-nu() ", 0 )
		    == std::string::npos );

  unsigned white_space_loc = cell_definition.find( " " );

  while( white_space_loc < cell_definition.size() )
  {
    cell_definition.erase( white_space_loc, 1 );

    white_space_loc = cell_definition.find( " ", white_space_loc );
  }
}

// Rename the cell definition variables
/*! \details This function renames all of the surface IDs (variables) in the
 * cell definition string based on the order in which they appear. This allows
 * variables to be referenced based on their index in an array. This function
 * is only called by the constructor. It is a protected member and not a
 * private member to allow for "white-box" unit testing.
 * \param[in,out] cell_definition a cell definition string which contains the
 * logical combination of second order surfaces which define the cell. The
 * string is passed by reference so that it can be modified.
 * \pre The cell definition string must not contain any white space characters
 * (the BooleanCellFunctor::removeWhiteSpace member function must be called
 * before this function).
 */
void BooleanCellFunctor::renameVariables( std::string &cell_definition ) const
{
  // The cell definition must be free of white space
  testPrecondition( cell_definition.find( " " ) > cell_definition.size() );

  std::string operation_characters( "nu()" );

  unsigned variable_start_loc, variable_end_loc;
  variable_start_loc =
    cell_definition.find_first_not_of( operation_characters );
  variable_end_loc = cell_definition.find_first_of( operation_characters,
						    variable_start_loc+1 ) - 1;
  unsigned variable_name_size;

  unsigned variable_index = 0;

  while( variable_start_loc < cell_definition.size() )
  {
    variable_name_size = variable_end_loc - variable_start_loc + 1;
    cell_definition.erase( variable_start_loc, variable_name_size );

    std::stringstream new_variable_name;
    new_variable_name << variable_index;

    cell_definition.insert( variable_start_loc, new_variable_name.str() );

    // Move past the current variable
    variable_start_loc = cell_definition.find_first_of( operation_characters,
							variable_start_loc );
    // Look for the next variable
    variable_start_loc =
      cell_definition.find_first_not_of( operation_characters,
					 variable_start_loc );
    variable_end_loc =
      cell_definition.find_first_of( operation_characters,
				     variable_start_loc+1 ) - 1;
    ++variable_index;
  }
}

// Determine the number of variables present in the cell definition
/*! \details This function determines the number of variables (surface IDs
 * include duplicates) present in the cell definition string. It is only called
 * by the constructor. It is a protected member and not a private member to
 * allow for "white-box" unit testing.
 * \param[in] cell_definition a cell definition string which contains the
 * logical combination of second order surfaces which define the cell. The
 * string is passed by reference to avoid copy overhead though it is not
 * modified.
 * \pre The cell definition string must not contain any white space characters
 * (the BooleanCellFunctor::removeWhiteSpace member function must be called
 * before this function).
 */
unsigned
BooleanCellFunctor::getNumVariables( const std::string &cell_definition )
{
  // The cell definition must not be empty
  testPrecondition( cell_definition.size() > 0 );
  // The cell definition must be free of white space
  testPrecondition( cell_definition.find( " " ) > cell_definition.size() );

  std::string operation_characters( "nu()" );

  unsigned operation_loc, start_loc = 0;
  operation_loc = cell_definition.find_first_of( operation_characters );

  unsigned number_of_variables = 0;

  if( operation_loc < cell_definition.size() )
  {
    // Check if the cell definition starts with a variable
    if( operation_loc == 1 )
      ++number_of_variables;

    while( operation_loc < cell_definition.size() )
    {
      if( operation_loc - start_loc > 1 )
	++number_of_variables;

      start_loc = operation_loc;
      operation_loc =
	cell_definition.find_first_of( operation_characters, operation_loc+1 );
    }

    // Check if the cell definition ends with a variable
    if( start_loc < cell_definition.size()-1 )
      ++number_of_variables;
  }
  // Check for the special case of only one variable (e.g. sphere)
  else
    number_of_variables = 1;

  return number_of_variables;
}

// Determine the variable range in the string
/*! \details This function determines the range of variable indices that are
 * present in a sub-string. It is a protected member and not a private member
 * to allow for "white-box" unit testing.
 * \param[in] sub_string A sub-string from the original cell_definition (usually
 * the part of the string inside of parentheses). The sub_string will be
 * modified in a way that will only be useful inside of this function, which is
 * why it is not passed by reference.
 * \return A Utility::Pair<unsigned,unsigned> object is returned. The first
 * member of this tuple will contain the lowest variable index of the
 * sub_string. The second member of this tuple will contain the largest
 * variable index of the sub_string.
 * \pre The sub_string must not contain any white space characters (the
 * BooleanCellFunctor::removeWhiteSpace member function must be called before
 * this function).
 */
Utility::Pair<unsigned,unsigned>
BooleanCellFunctor::getVariableRange( std::string sub_string ) const
{
  // The sub-string must be free of white space
  testPrecondition( sub_string.find( " " ) > sub_string.size() );

  std::string operation_characters( "nu()" );

  unsigned operation_loc = sub_string.find_first_of( operation_characters );

  while( operation_loc < sub_string.size() )
  {
    sub_string[operation_loc] = ' ';

    operation_loc = sub_string.find_first_of( operation_characters,
					      operation_loc+1 );
  }

  std::stringstream processed_sub_string( sub_string );

  unsigned start_variable, end_variable;
  processed_sub_string >> start_variable;
  end_variable = start_variable;

  while( processed_sub_string )
    processed_sub_string >> end_variable;


  Utility::Pair<unsigned,unsigned> range( start_variable, end_variable );

  return range;
}

// Construct the child functors
/*! \details This function constructs child BooleanCellFunctors from the
 * cell_definition. Every time a parentheses is encountered a new child will
 * be created. It is a protected member and not a private member to allow for
 * "white-box" unit testing.
 * \param[in] cell_definition A cell definition string which contains the
 * logical combination of second order surfaces which define the cell. The
 * string is passed by reference to avoid copy overhead though it is not
 * modified.
 * \pre The cell definition string must not contain any white space
 * characters (the BooleanCellFunctor::removeWhiteSpace member function must
 * be called before this function).
 */
void BooleanCellFunctor::constructChildFunctors(
					   const std::string &cell_definition )
{
  // The sub-string must be free of white space
  testPrecondition( cell_definition.find( " " ) > cell_definition.size() );

  unsigned sub_string_start, next_sub_string_start, sub_string_end;
  sub_string_start = cell_definition.find( "(" );
  next_sub_string_start = cell_definition.find( "(", sub_string_start+1 );
  sub_string_end = cell_definition.find( ")" );

  Teuchos::Array<BooleanCellFunctor> child_functors;
  Teuchos::Array<Utility::Pair<unsigned,unsigned> > child_functor_variables;

  while( sub_string_start < cell_definition.size() )
  {
    // Ignore nested parentheses (they will be handled by the children)
    while( sub_string_end > next_sub_string_start )
    {
      next_sub_string_start =
	cell_definition.find( "(", next_sub_string_start+1 );
      sub_string_end = cell_definition.find( ")", sub_string_end+1 );
    }

    // Sub-string will not contain the outer parentheses
    unsigned sub_string_size = sub_string_end - sub_string_start - 1;
    std::string sub_string = cell_definition.substr( sub_string_start+1,
						     sub_string_size );

    // Record which variables should be used with this child
    Utility::Pair<unsigned,unsigned> sub_string_variable_range =
      getVariableRange( sub_string );
    child_functor_variables.push_back( sub_string_variable_range );

    // Create a new child functor from the sub-string
    BooleanCellFunctor child_functor( sub_string );
    child_functors.push_back( child_functor );

    // Process the next child if one exists
    sub_string_start = cell_definition.find( "(", sub_string_end );
    next_sub_string_start = cell_definition.find( "(", sub_string_start+1 );
    sub_string_end = cell_definition.find( ")", sub_string_start );
  }

  d_child_functors = child_functors;
  d_child_functor_variables = child_functor_variables;
}

// Reduce the cell definition so that it contains no parentheses
/*! \details This function reduces the cell definition string to one in which
 * there are no parentheses. All of the variables in parentheses are combined
 * into a single variable. This member function is protected and not private
 * to allow for "white-box" unit testing.
 * /param[in,out] cell_definition A cell definition string which contains the
 * logical combination of second order surfaces which define the cell.
 * /pre The cell definition string must not contain any white space characters
 * (the BooleanCellFunctor::removeWhiteSpace member function must be called
 * before this function).
 */
void BooleanCellFunctor::reduceDefinition( std::string &cell_definition ) const
{
  // The sub-string must be free of white space
  testPrecondition( cell_definition.find( " " ) > cell_definition.size() );

  unsigned sub_string_start, next_sub_string_start, sub_string_end;
  sub_string_start = cell_definition.find( "(" );
  next_sub_string_start = cell_definition.find( "(", sub_string_start+1 );
  sub_string_end = cell_definition.find( ")" );

  unsigned dummy_variable_index = 0;

  while( sub_string_start < cell_definition.size() )
  {
    // Ignore nested parentheses (they will be handled by the children)
    while( sub_string_end > next_sub_string_start )
    {
      next_sub_string_start =
	cell_definition.find( "(", next_sub_string_start+1 );
      sub_string_end = cell_definition.find( ")", sub_string_end+1 );
    }

    // Remove the sub-string and add a dummy variable
    unsigned sub_string_size = sub_string_end - sub_string_start + 1;

    cell_definition.erase( sub_string_start, sub_string_size );

    std::stringstream dummy_variable;
    dummy_variable << "d" << dummy_variable_index;

    cell_definition.insert( sub_string_start, dummy_variable.str() );

    // Find the next sub-string if one exists
    sub_string_start = cell_definition.find( "(", sub_string_start );
    next_sub_string_start = cell_definition.find( "(", sub_string_start+1 );
    sub_string_end = cell_definition.find( ")", sub_string_start );

    ++dummy_variable_index;
  }
}

// Assign the set operation functors based on the cell definition
/*! \details This function creates an array of Utility::SetOperatorFunctors
 * from the cell definition string. It is a protected member and not a private
 * member to allow for "white-box" unit testing.
 * \param[in] cell_definition A cell definition string which contains the
 * logical combination of second order surfaces which define the cell. The
 * string is passed by reference to avoid copy overhead.
 * \pre
 * <ul>
 *  <li> The cell definition string must not contain any white space characters
 *       (the BooleanCellFunctor::removeWhiteSpace member function must be
 *       called before this function).
 *  <li> The cell definition string cannot start with an operation character.
 *  <li> The cell definition string cannot end with an operation character.
 *  <li> The cell definition string must contain at least one operation
 *       character.
 *  <li> The cell definition string must be a reduced definition (there must
 *       not be any parentheses present in the string).
 * </ul>
 * \note Developers: It might be useful to create a new function that test the
 * cell definition before any of the other member functions are called in the
 * constructor. This function will always do the tests unlike the DBC tests.
 */
void BooleanCellFunctor::assignSetOperationFunctors( const std::string &cell_definition )
{
  // The cell definition must be free of white space
  testPrecondition( cell_definition.find( " " ) > cell_definition.size() );
  // The cell definition cannot start with an operation
  testPrecondition( cell_definition.find_first_of( "nu" ) != 0 );
  // The cell definition cannot end with an operation
  testPrecondition( cell_definition.find_last_of( "nu" ) !=
		    cell_definition.size()-1 );
  // The cell definition must be reduced
  testPrecondition( cell_definition.find_first_of( "()" ) >
		    cell_definition.size() );

  std::string operation_characters( "nu" );

  unsigned operation_loc =
    cell_definition.find_first_of( operation_characters );

  Teuchos::Array<Teuchos::RCP<Utility::SetOperationFunctor> > function_definition;

  while( operation_loc < cell_definition.size() )
  {
    if( cell_definition.compare( operation_loc, 1, "n" ) == 0 )
    {
      Teuchos::RCP<Utility::SetOperationFunctor>
	new_op( new Utility::IntersectionFunctor );
      function_definition.push_back( new_op );
    }
    else
    {
      Teuchos::RCP<Utility::SetOperationFunctor>
	new_op( new Utility::UnionFunctor );
      function_definition.push_back( new_op );
    }

    operation_loc = cell_definition.find_first_of( operation_characters,
						   operation_loc+1 );
  }

  d_function_definition = function_definition;
}

// Get the number of child functors
unsigned BooleanCellFunctor::getNumChildFunctors() const
{
  return d_child_functors.size();
}

// Get the number of SetOperationFunctors
unsigned BooleanCellFunctor::getNumSetOperationFunctors() const
{
  return d_function_definition.size();
}

// Get the variable ranges for child functors
Teuchos::Array<Utility::Pair<unsigned,unsigned> >
BooleanCellFunctor::getChildFunctorVariableRanges() const
{
  return d_child_functor_variables;
}


} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_BooleanCellFunctor.cpp
//---------------------------------------------------------------------------//

