//---------------------------------------------------------------------------//
//!
//! \file   Utility_ODESolver.hpp
//! \author Alex Bennett
//! \brief  ODE Solver Wrapper
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ODE_SOLVER_HPP
#define UTILITY_ODE_SOLVER_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_SerialDenseMatrix.hpp>

namespace Utility {

class ODESolver
{
public:
   // Default Constructor
   ODESolver();

   // Constructor
   ODESolver(const double relative_tol,const double absolute_tol,const int length_working_array);

   // Set the relative tolerance
   void setRelativeTol(const double relative_tol);

   // Set the absolute tolerance
   void setAbsoluteTol(const double absolute_tol);

   // Set the length of the working array
   void setLengthWorkingArray(const int length_working_array);

   // get the relative tolerance
   double getRelativeTol() const;

   // get the absolute tolerance
   double getAbsoluteTol() const;

   // get the length of the working array
   int getLengthWorkingArray() const;

   // solves the ODE
   void solve(const Teuchos::RCP<Teuchos::SerialDenseMatrix<int,double> >& matrix,
              Teuchos::Array<double>& y,
              const double time) const;

private:
   double d_relative_tol;
   double d_absolute_tol;
   int d_length_working_array;
};

} // end namespace utility

#endif // end UTILITY_ODE_SOLVER_HPP

//---------------------------------------------------------------------------//
// end Utility_ODESolver.hpp
//---------------------------------------------------------------------------//

