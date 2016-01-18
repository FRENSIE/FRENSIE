//---------------------------------------------------------------------------//
//!
//! \file   Utility_GaussKronrodIntegration.cpp
//! \author Luke Kersting
//! \brief  Gauss-Kronrod integration
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_GaussKronrodIntegration.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Constructor
GaussKronrodIntegration::GaussKronrodIntegration( 
    const double relative_error_tol,
    const double absolute_error_tol )
  : d_relative_error_tol( relative_error_tol ),
    d_absolute_error_tol( absolute_error_tol )
{
  // Make sure the error tolerances are valid
  testPrecondition( relative_error_tol >= 0.0 );
  testPrecondition( absolute_error_tol >= 0.0 );
}

// Destructor
GaussKronrodIntegration::~GaussKronrodIntegration()
{ /* ... */ }

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_GaussKronrodIntegration.cpp
//---------------------------------------------------------------------------//
