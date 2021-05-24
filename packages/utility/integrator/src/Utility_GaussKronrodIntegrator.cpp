//---------------------------------------------------------------------------//
//!
//! \file   Utility_GaussKronrodIntegrator.cpp
//! \author Alex Robinson
//! \brief  Gauss-Kronrod integrator explicit instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_GaussKronrodIntegrator.hpp"

namespace Utility{

EXPLICIT_TEMPLATE_CLASS_INST( GaussKronrodIntegrator<double> );
EXPLICIT_TEMPLATE_CLASS_INST( GaussKronrodIntegrator<long double> );
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_GaussKronrodIntegrator.cpp
//---------------------------------------------------------------------------//
