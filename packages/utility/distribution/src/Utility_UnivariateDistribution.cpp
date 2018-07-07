//---------------------------------------------------------------------------//
//!
//! \file   Utility_UnivariateDistribution.cpp
//! \author Alex Robinson
//! \brief  The univariate distribution class template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp" // Must include first
#include "Utility_UnivariateDistribution.hpp"

EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareUnivariateDistribution<void,void> );
EXPLICIT_CLASS_SAVE_LOAD_INST( Utility::UnitAwareUnivariateDistribution<void,void> );

//---------------------------------------------------------------------------//
// end Utility_UnivariateDistribution.cpp
//---------------------------------------------------------------------------//
