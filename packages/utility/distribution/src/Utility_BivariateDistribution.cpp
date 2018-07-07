//---------------------------------------------------------------------------//
//!
//! \file   Utility_BivariateDistribution.cpp
//! \author Alex Robinson
//! \brief  The bivariate distribution class template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_Archives.hpp" // Must include first
#include "Utility_BivariateDistribution.hpp"

EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareBivariateDistribution<void,void,void> );
EXPLICIT_CLASS_SAVE_LOAD_INST( Utility::UnitAwareBivariateDistribution<void,void,void> );

//---------------------------------------------------------------------------//
// end Utility_BivariateDistribution.cpp
//---------------------------------------------------------------------------//
