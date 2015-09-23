//---------------------------------------------------------------------------//
//!
//! \file   Utility_GaussKronrodQuadratureSet.cpp
//! \author Alex Robinson
//! \brief  Gauss-Kronrod quadrature gkq_set
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_GaussKronrodQuadratureSet.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Initialize static member data
gsl_error_handler_t* GaussKronrodQuadratureSet::default_gsl_error_handler =
  NULL;

// Allow the gkq_set to throw exceptions
void GaussKronrodQuadratureSet::throwExceptions( const bool allow_throw )
{
  if( allow_throw )
  {
    GaussKronrodQuadratureSet::default_gsl_error_handler = 
      gsl_set_error_handler_off();
  }
  else if( default_gsl_error_handler )
    gsl_set_error_handler( default_gsl_error_handler );
  // else - default is already being used
}

// Constructor
GaussKronrodQuadratureSet::GaussKronrodQuadratureSet( 
				              const double relative_error_tol,
					      const double absolute_error_tol,
				              const size_t subinterval_limit,
					      const size_t workspace_size )
  : d_relative_error_tol( relative_error_tol ),
    d_absolute_error_tol( absolute_error_tol ),
    d_subinterval_limit( subinterval_limit ),
    d_workspace_size( workspace_size )
{
  // Make sure the error tolerances are valid
  testPrecondition( relative_error_tol >= 0.0 );
  testPrecondition( absolute_error_tol >= 0.0 );
  // Make sure the work space size is valid
  testPrecondition( workspace_size > 0 );
  // Make sure the subinterval limit is valid
  testPrecondition( subinterval_limit > 0 );
  testPrecondition( subinterval_limit <= workspace_size );
}

// Destructor
GaussKronrodQuadratureSet::~GaussKronrodQuadratureSet()
{ /* ... */ }

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_GaussKronrodQuadratureSet.cpp
//---------------------------------------------------------------------------//
