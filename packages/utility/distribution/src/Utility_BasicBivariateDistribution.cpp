//---------------------------------------------------------------------------//
//!
//! \file   Utility_BasicBivariateDistribution.cpp
//! \author Alex Robinson
//! \brief  The basic bivariate distribution class template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp" // Must be included first
#include "Utility_BasicBivariateDistribution.hpp"

EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareBasicBivariateDistribution<void,void,void> );
EXPLICIT_CLASS_SAVE_LOAD_INST( Utility::UnitAwareBasicBivariateDistribution<void,void,void> );

//---------------------------------------------------------------------------//
// end Utility_BasicBivariateDistribution.cpp
//---------------------------------------------------------------------------//
