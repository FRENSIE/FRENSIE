//---------------------------------------------------------------------------//
//!
//! \file   Utility_NormalDistribution.cpp
//! \author Alex Robinson
//! \brief  The normal distribution class template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp" // Must include first
#include "Utility_NormalDistribution.hpp"

EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareNormalDistribution<void,void> );
EXPLICIT_CLASS_SAVE_LOAD_INST( Utility::UnitAwareNormalDistribution<void,void> );

//---------------------------------------------------------------------------//
// end Utility_NormalDistribution.cpp
//---------------------------------------------------------------------------//
