//---------------------------------------------------------------------------//
// \file   BooleanCellFunctor.hpp
// \author Alex Robinson
// \brief  Functor that takes a boolean array and returns true/false
//---------------------------------------------------------------------------//

#ifndef BOOLEAN_CELL_FUNCTOR_HPP
#define BOOLEAN_CELL_FUNCTOR_HPP

// Std Lib Includes
#include <string>
#include <list>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FACEMC Includes
#include "Tuple.hpp"
#include "SetOperationFunctor.hpp"

namespace FACEMC{
  
class BooleanCellFunctor
{
  
public:
  
  //! Constructor
  BooleanCellFunctor( std::string &cell_definition );

  //! Destructor
  ~BooleanCellFunctor()
  { /* ... */ }
  
  //! Function evaluation operator
  bool operator()( const std::list<bool> &argument_list );

protected:

  //! Default Constructor
  BooleanCellFunctor()
  { /* ... */ }

  //! Remove white space from the cell definition string
  void removeWhiteSpace( std::string &cell_definition ) const;

  //! Rename the cell definition variables
  void renameVariables( std::string &cell_definition ) const;
  
  //! Determine the number of variables present in the cell definition
  unsigned getNumberOfVariables( const std::string &cell_definition );

  //! Determine the variable range in the string
  // \brief The string is not passed by reference so that a copy will be made
  //        which will be manipulated.
  Pair<unsigned,unsigned> getVariableRange( std::string sub_string ) const;

  //! Construct the child functors
  void constructChildFunctors( const std::string &cell_definition );

  //! Reduce the cell definition so that it contains no parentheses
  void reduceDefinition( std::string &cell_definition ) const;

  //! Assign the set operation functors based on the cell definition
  void assignSetOperationFunctors( const std::string &cell_definition );

  //! Get the number of child functors
  unsigned getNumChildFunctors() const;

  //! Get the number of SetOperationFunctors
  unsigned getNumSetOperationFunctors() const;

  //! Get the variable ranges for the child functors
  Teuchos::Array<Pair<unsigned,unsigned> > getChildFunctorVariableRanges() const;

private:

  // Child BooleanCellFunctors for evaluation of terms in parentheses
  Teuchos::Array<BooleanCellFunctor> d_child_functors;
  
  // Indices of boolean variables found in parentheses
  Teuchos::Array<Pair<unsigned,unsigned> > d_child_functor_variables;

  // SetOperationFunctors for evaluating the cell function
  Teuchos::Array<Teuchos::RCP<SetOperationFunctor> > 
  d_function_definition;
  
  // Number of boolean variables to expect in boolean array
  unsigned d_number_of_variables;

};

} // end FACEMC namespace

#endif // end BOOLEAN_CELL_FUNCTOR_HPP

//---------------------------------------------------------------------------//
// end BooleanCellFunctor.hpp
//---------------------------------------------------------------------------//

