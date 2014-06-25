//---------------------------------------------------------------------------//
//!
//! \file   Utility_ODESolver.cpp
//! \author Alex Bennett
//! \brief  ODE Solver Wrapper
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_SerialDenseMatrix.hpp>

// FRENSIE Includes
#include "Utility_ODEPACKHelperWrapper.hpp"
#include "Utility_ODESolver.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Utility{

// Default Constructor
ODESolver::ODESolver()
 : d_relative_tol(1e-4),
   d_absolute_tol(1e-6),
   d_length_working_array(10000)
{ /* ... */ }

// Constructor
ODESolver::ODESolver(const double relative_tol,
                     const double absolute_tol,
                     const int length_working_array)
  : d_relative_tol(relative_tol),
    d_absolute_tol(absolute_tol),
    d_length_working_array(length_working_array)
{
    // Check if values are valid
    testPrecondition( relative_tol > 0.0 );
    testPrecondition( relative_tol < 1.0 );
    testPrecondition( absolute_tol > 0.0 );
    testPrecondition( absolute_tol < 1.0 );
    testPrecondition( length_working_array > 0 );
}

// Set the relative tolerance
void ODESolver::setRelativeTol(const double relative_tol)
{
    // Check if values are valid
    testPrecondition( relative_tol > 0.0 );
    testPrecondition( relative_tol < 1.0 );

    d_relative_tol = relative_tol;
}

// Set the absolute tolerance
void ODESolver::setAbsoluteTol(const double absolute_tol)
{
     // Check if values are valid
     testPrecondition( absolute_tol > 0.0 );
     testPrecondition( absolute_tol < 1.0 );

     d_absolute_tol = absolute_tol;
}

// Set the length of the working array
void ODESolver::setLengthWorkingArray(const int length_working_array)
{
      // Check if values are valid
      testPrecondition( length_working_array > 0 );

      d_length_working_array = length_working_array;
}

// Get the relative tolerance
double ODESolver::getRelativeTol() const
{
    return d_relative_tol;
}

// Get the absolute tolerance
double ODESolver::getAbsoluteTol() const
{
     return d_absolute_tol;
}

// Get the length of the working array
int ODESolver::getLengthWorkingArray() const
{
     return d_length_working_array;
}

// Solve the matrix
void ODESolver::solve(const Teuchos::SerialDenseMatrix<int,double>& matrix,
                      Teuchos::Array<double>& y,
                      const double time) const
{
     // Check if values are valid
     testPrecondition( matrix.numRows() > 1 );
     testPrecondition( matrix.numRows() == matrix.numCols() );
     testPrecondition( matrix.numRows() == y.length() );
     testPrecondition( time > 0.0 );

     lsodesSolver(matrix.values(), y.getRawPtr(), matrix.numRows(), &time, 
                  &d_relative_tol, &d_absolute_tol, &d_length_working_array);

}

} // End Utility Namespace

//---------------------------------------------------------------------------//
// end Utility_ODESolver.cpp
//---------------------------------------------------------------------------//

