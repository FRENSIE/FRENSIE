//---------------------------------------------------------------------------//
// \file   BooleanCellFunctor.hpp
// \author Alex Robinson
// \brief  BooleanCellFunctor class declaration
//----------------------------------------------------------------------------//

#ifndef BOOLEAN_CELL_FUNCTOR_HPP
#define BOOLEAN_CELL_FUNCTOR_HPP

// Std Lib Includes
#include <string>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FACEMC Includes
#include "Tuple.hpp"
#include "SetOperationFunctor.hpp"

namespace FACEMC{

/*! \brief Functor that takes an array of bools and returns true of false.
 *
 * This object is designed to represent the logical representation of a 
 * geometric cell defined by the logical combination of second order surface. 
 * Its constructor takes a string which contains the logical combination of 
 * second order surfaces. Only the logical operators that define the cell are
 * are recorded during object construction. The surface numbers and senses
 * are ignored. Upon creation, this object can be used as a function which 
 * takes an array of bools and returns either true or false. The array of bools
 * represent whether a point is on the side of each surface corresponding
 * to the sense that defines the cell. This object allows the evaluation of
 * very complicated cell definitions that contain unions (if only intersections
 * were allowed, this object might not be necessary). A return value of true
 * indicates that the point is indeed in or on the surface (whether its in
 * or on depends on the Boolean array that is passed as an argument).
 */
class BooleanCellFunctor
{
  
public:
  
  //! Constructor
  BooleanCellFunctor( std::string cell_definition );

  //! Destructor
  ~BooleanCellFunctor()
  { /* ... */ }
  
  //! Function evaluation operator
  template<typename Bool, template<typename> class Array>
  bool operator()( const Array<Bool> &arguments ) const;

protected:

  //! Default Constructor
  BooleanCellFunctor()
  { /* ... */ }

  //! Remove white space from the cell definition string
  void removeWhiteSpace( std::string &cell_definition ) const;

  //! Rename the cell definition variables
  void renameVariables( std::string &cell_definition ) const;
  
  //! Determine the number of variables present in the cell definition
  unsigned getNumVariables( const std::string &cell_definition );

  //! Determine the variable range in the string
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
  
  // Indices of Boolean variables found in parentheses
  Teuchos::Array<Pair<unsigned,unsigned> > d_child_functor_variables;

  // SetOperationFunctors for evaluating the cell function
  Teuchos::Array<Teuchos::RCP<SetOperationFunctor> > 
  d_function_definition;
  
  // Number of Boolean variables to expect in Boolean array
  unsigned d_number_of_variables;

};

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "BooleanCellFunctor_def.hpp"

//---------------------------------------------------------------------------//

#endif // end BOOLEAN_CELL_FUNCTOR_HPP

//---------------------------------------------------------------------------//
// end BooleanCellFunctor.hpp
//---------------------------------------------------------------------------//

