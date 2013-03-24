//---------------------------------------------------------------------------//
// \file   BooleanCellFunctor.cpp
// \author Alex Robinson
// \brief  BooleanCellFunctor definition
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <sstream>
#include <list>
#include <iterator>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FACEMC Includes
#include "BooleanCellFunctor.hpp"
#include "Tuple.hpp"
#include "SetOperationFunctor.hpp"
#include "ContractException.hpp"
#include "FACEMC_Assertion.hpp"

namespace FACEMC{

//! Constructor
BooleanCellFunctor::BooleanCellFunctor( std::string &cell_definition )
{
  removeWhiteSpace( cell_definition );
  renameVariables( cell_definition );
  d_number_of_variables = getNumberOfVariables( cell_definition );
  constructChildFunctors( cell_definition );
  reduceDefinition( cell_definition );
  assignSetOperationFunctors( cell_definition );
}

//! Function evaluation operator
bool BooleanCellFunctor::operator()( const std::list<bool> &argument_list )
{
  // The argument list must have the expected number of arguments
  testPrecondition( d_number_of_variables == argument_list.size() );
  
  std::list<bool>::const_iterator range_start, range_end;
  range_start = argument_list.begin();
  
  std::list<bool> reduced_argument_list;
  std::list<bool>::iterator reduced_argument_list_pos = 
    reduced_argument_list.end();

  unsigned advance_distance;
  
  // Call the child functors and reduce the argument list
  for( unsigned i = 0; i < d_child_functors.size(); ++i )
  {
    // Add the non-child variable arguments to the reduced argument list
    if( i > 0 )
    {
      advance_distance = d_child_functor_variables[i].first -
	d_child_functor_variables[i-1].second - 1;
      
      std::advance( range_end, 
		    advance_distance);
    }
    else
    {
      range_end = argument_list.begin();
      advance_distance = d_child_functor_variables[i].first;
      std::advance( range_end,
		    advance_distance );
    }
  
    reduced_argument_list.insert( reduced_argument_list_pos,
				  range_start,
				  range_end );
    
    // Create a sublist to pass to the child functor
    range_start = range_end;
    
    std::advance( range_end,
		  d_child_functor_variables[i].second+1 - 
		  d_child_functor_variables[i].first );

    std::list<bool> sub_list( range_start, range_end );
    bool child_argument = d_child_functors[i]( sub_list );
    
    // Add the result from the child functor to the reduced argument list
    reduced_argument_list.push_back( child_argument );

    range_start = range_end;
    
    reduced_argument_list_pos = reduced_argument_list.end();
  }

  // Add the rest of the non-child variable arguments to the reduced argument 
  // list
  range_end = argument_list.end();
  
  reduced_argument_list.insert( reduced_argument_list_pos,
				range_start,
				range_end );

  // Evaluate the cell function  
  bool success = reduced_argument_list.front();
  reduced_argument_list.pop_front();
  
  for( unsigned i = 0; i < d_function_definition.size(); ++i )
  {
    success = (*d_function_definition[i])( success, 
					   reduced_argument_list.front() );
    reduced_argument_list.pop_front(); 
  }  

  return success;
}  

void BooleanCellFunctor::removeWhiteSpace( std::string &cell_definition ) const
{
  unsigned white_space_loc = cell_definition.find( " " );

  while( white_space_loc < cell_definition.size() )
  {
    cell_definition.erase( white_space_loc, 1 );

    white_space_loc = cell_definition.find( " ", white_space_loc );
  }
}

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

//! Determine the number of variables present in the cell definition
unsigned 
BooleanCellFunctor::getNumberOfVariables( const std::string &cell_definition )
{
  // The cell definition must be free of white space
  testPrecondition( cell_definition.find( " " ) > cell_definition.size() );
  
  std::string operation_characters( "nu()" );
  
  unsigned operation_loc, start_loc = 0; 
  operation_loc = cell_definition.find_first_of( operation_characters );
  
  unsigned number_of_variables = 0;

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
  
  return number_of_variables;
}

//! Determine the variable range in the string
Pair<unsigned,unsigned> 
BooleanCellFunctor::getVariableRange( std::string sub_string ) const
{
  // The substring must be free of white space
  testPrecondition( sub_string.find( " " ) > sub_string.size() );
  
  std::string operation_characters( "nu()" );

  unsigned operation_loc = sub_string.find_first_of( operation_characters );

  while( operation_loc < sub_string.size() )
  {
    sub_string[operation_loc] = ' ';

    operation_loc = sub_string.find_first_of( operation_characters,
					      operation_loc+1 );
  }

  std::stringstream processed_sub_string;
  processed_sub_string << sub_string;

  unsigned start_variable, end_variable;
  processed_sub_string >> start_variable;
  end_variable = start_variable;

  while( processed_sub_string )
    processed_sub_string >> end_variable;
  

  Pair<unsigned,unsigned> range( start_variable, end_variable );
  
  return range;  
}
  
//! Construct the child functors
void BooleanCellFunctor::constructChildFunctors( const std::string &cell_definition )
{
  // The substring must be free of white space
  testPrecondition( cell_definition.find( " " ) > cell_definition.size() );
  
  unsigned sub_string_start, next_sub_string_start, sub_string_end;
  sub_string_start = cell_definition.find( "(" );
  next_sub_string_start = cell_definition.find( "(", sub_string_start+1 );
  sub_string_end = cell_definition.find( ")" );
  
  Teuchos::Array<BooleanCellFunctor> child_functors;
  Teuchos::Array<Pair<unsigned,unsigned> > child_functor_variables;

  while( sub_string_start < cell_definition.size() )
  {
    // Ignore nested parentheses (they will be handled by the children)
    while( sub_string_end > next_sub_string_start )
    {
      next_sub_string_start = 
	cell_definition.find( "(", next_sub_string_start+1 );
      sub_string_end = cell_definition.find( ")", sub_string_end+1 );
    }

    // Substring will not contain the outer parentheses
    unsigned sub_string_size = sub_string_end - sub_string_start - 1;
    std::string sub_string = cell_definition.substr( sub_string_start+1,
						     sub_string_size );

    // Record which variables should be used with this child
    Pair<unsigned,unsigned> sub_string_variable_range = 
      getVariableRange( sub_string );
    child_functor_variables.push_back( sub_string_variable_range );

    // Create a new child functor from the substring
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

//! Reduce the cell definition so that it contains no parentheses
void BooleanCellFunctor::reduceDefinition( std::string &cell_definition ) const
{
  // The substring must be free of white space
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
    
    // Remove the substring and add a dummy variable
    unsigned sub_string_size = sub_string_end - sub_string_start + 1;
    
    cell_definition.erase( sub_string_start, sub_string_size );
    
    std::stringstream dummy_variable;
    dummy_variable << "d" << dummy_variable_index;
    
    cell_definition.insert( sub_string_start, dummy_variable.str() );

    // Find the next substring if one exists
    sub_string_start = cell_definition.find( "(", sub_string_start );
    next_sub_string_start = cell_definition.find( "(", sub_string_start+1 );
    sub_string_end = cell_definition.find( ")", sub_string_start );
    
    ++dummy_variable_index;
  }
}    

//! Assign the set operation functors based on the cell definition
void BooleanCellFunctor::assignSetOperationFunctors( const std::string &cell_definition )
{
  // The cell definition must be free of white space
  testPrecondition( cell_definition.find( " " ) > cell_definition.size() );
  // The cell definition cannot start with an operation
  testPrecondition( cell_definition.find_first_of( "nu" ) != 0 );
  // The cell definition cannot end with an operation
  testPrecondition( cell_definition.find_last_of( "nu" ) != cell_definition.size()-1 );
  // The cell definition must contain at least one operation
  testPrecondition( cell_definition.find_first_of( "nu" ) < cell_definition.size() );
  // The cell definition must be reduced
  testPrecondition( cell_definition.find_first_of( "()" ) > cell_definition.size() );

  std::string operation_characters( "nu" );

  unsigned operation_loc = 
    cell_definition.find_first_of( operation_characters );

  Teuchos::Array<Teuchos::RCP<SetOperationFunctor> > function_definition;

  while( operation_loc < cell_definition.size() )
  {
    if( cell_definition.compare( operation_loc, 1, "n" ) == 0 )
    {
      Teuchos::RCP<SetOperationFunctor> new_op( new IntersectionFunctor );
      function_definition.push_back( new_op );
    }
    else
    {
      Teuchos::RCP<SetOperationFunctor> new_op( new UnionFunctor );
      function_definition.push_back( new_op );
    }

    operation_loc = cell_definition.find_first_of( operation_characters,
						   operation_loc+1 );
  }
  
  d_function_definition = function_definition;
}
      
//! Get the number of child functors
unsigned BooleanCellFunctor::getNumChildFunctors() const
{
  return d_child_functors.size();
}

//! Get the number of SetOperationFunctors
unsigned BooleanCellFunctor::getNumSetOperationFunctors() const
{
  return d_function_definition.size();
}

//! Get the variable ranges for child functors
Teuchos::Array<Pair<unsigned,unsigned> > 
BooleanCellFunctor::getChildFunctorVariableRanges() const
{
  return d_child_functor_variables;
}


} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end BooleanCellFunctor.cpp
//---------------------------------------------------------------------------//

