//---------------------------------------------------------------------------//
// \file   BooleanCellFunctor_def.hpp
// \author Alex Robinson
// \brief  BooleanCellFunctor template operator definition
//---------------------------------------------------------------------------//

#ifndef BOOLEAN_CELL_FUNCTOR_DEF_HPP
#define BOOLEAN_CELL_FUNCTOR_DEF_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayView.hpp>

// FACEMC Includes
#include "SetOperationFunctor.hpp"
#include "ContractException.hpp"

namespace FACEMC{

//! Function evaluation operator
template<typename Bool, template<typename> class Array>
bool BooleanCellFunctor::operator()( const Array<Bool> &arguments ) const
{
  // The argument list must have the expected number of arguments
  testPrecondition( d_number_of_variables == arguments.size() );

  // Child cell functors
  Teuchos::Array<BooleanCellFunctor>::const_iterator
    child = d_child_functors.begin();

  // Child variables
  Teuchos::Array<Pair<unsigned,unsigned> >::const_iterator
    child_variables = d_child_functor_variables.begin();

  // Binary set operation functor for evaluation cell function
  Teuchos::Array<Teuchos::RCP<SetOperationFunctor> >::const_iterator 
    set_operation = d_function_definition.begin();
  
  // Function evaluation return value
  bool success;

  // Index of the current argument to be used
  unsigned argument_index;

  // Initialize the function evaluation
  if( d_child_functors.size() > 0 )
  {
    if( child_variables->first == 0 )
    {
	
      success = (*child)( arguments( child_variables->first,
				     child_variables->second -
				     child_variables->first + 1 ) );
      argument_index = child_variables->second + 1;
      ++child;
      ++child_variables;
    }
    else
    {
      success = arguments[0];
      argument_index = 1;
    }
  }
  else
  {
    success = arguments[0];
    argument_index = 1;
  }
  
  // Evaluate the cell function with the provided arguments
  while( argument_index < arguments.size() )
  {
    if( child != d_child_functors.end() )
    {
      if( argument_index == child_variables->first )
      {
	bool child_success = (*child)( arguments( child_variables->first,
						  child_variables->second -
						  child_variables->first + 1 ) );
	success = (**set_operation)( success, child_success );
    
	argument_index = child_variables->second + 1;
	++child;
	++child_variables;
	++set_operation;
	continue;
      }
    }
    // Default process
    success = (**set_operation)( success, arguments[argument_index] );
    
    ++argument_index;
    ++set_operation;
  }

  return success;
}

} // end FACEMC namespace

#endif // end BOOLEAN_CELL_FUNCTOR_DEF_HPP

//---------------------------------------------------------------------------//
// end BooleanCellFunctor_def.hpp
//---------------------------------------------------------------------------//

