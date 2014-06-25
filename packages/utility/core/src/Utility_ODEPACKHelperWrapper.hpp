//---------------------------------------------------------------------------//
//!
//! \file   Utility_ODEPACKHelperWrapper.hpp
//! \author Alex Bennett
//! \brief  ODEPACK Helper Wrapper
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ODEPACK_HELPER_WRAPPERS_HPP
#define UTILITY_ODEPACK_HELPER_WRAPPERS_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>

extern "C" {
  void lsodesSolver(const double* matrix,
                    double* number_densities,
                    const int matrix_dimension,
                    const double* time,
                    const double* relative_tol,
                    const double* absolute_tol,
                    const int* length_working_array);
} 


#endif // end UTILITY_ODEPACK_HELPER_WRAPPERS_HPP

//---------------------------------------------------------------------------//
// end Utility_ODEPACKHelperWrappers.hpp
//---------------------------------------------------------------------------//

