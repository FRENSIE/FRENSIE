//---------------------------------------------------------------------------//
//!
//! \file   Utility_EvaporationDistribution.cpp
//! \author Alex Robinson
//! \brief  The evaporation distribution class template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp" // Must include first
#include "Utility_EvaporationDistribution.hpp"

EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareEvaporationDistribution<void,void> );
EXPLICIT_CLASS_SAVE_LOAD_INST( Utility::UnitAwareEvaporationDistribution<void,void> );

//---------------------------------------------------------------------------//
// end Utility_EvaporationDistribution.cpp
//---------------------------------------------------------------------------//
