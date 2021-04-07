//---------------------------------------------------------------------------//
//!
//! \file   Utility_ExponentialDistribution.cpp
//! \author Alex Robinson
//! \brief  The exponential distribution class template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp" // Must be included first
#include "Utility_ExponentialDistribution.hpp"

EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareExponentialDistribution<void,void> );
EXPLICIT_CLASS_SAVE_LOAD_INST( Utility::UnitAwareExponentialDistribution<void,void> );

//---------------------------------------------------------------------------//
// end Utility_ExponentialDistribution.cpp
//---------------------------------------------------------------------------//
