//---------------------------------------------------------------------------//
//!
//! \file   Utility_DeltaDistribution.cpp
//! \author Alex Robinson
//! \brief  The delta distribution class template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp" // Must include first
#include "Utility_DeltaDistribution.hpp"

EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareDeltaDistribution<void,void> );
EXPLICIT_CLASS_SAVE_LOAD_INST( Utility::UnitAwareDeltaDistribution<void,void> );

//---------------------------------------------------------------------------//
// end Utility_DeltaDistribution.cpp
//---------------------------------------------------------------------------//
