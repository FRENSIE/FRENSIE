//---------------------------------------------------------------------------//
//!
//! \file   Utility_MaxwellFissionDistribution.cpp
//! \author Alex Robinson
//! \brief  The Maxwell fission distribution class template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp" // Must include first
#include "Utility_MaxwellFissionDistribution.hpp"

EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareMaxwellFissionDistribution<void,void> );
EXPLICIT_CLASS_SAVE_LOAD_INST( Utility::UnitAwareMaxwellFissionDistribution<void,void> );

//---------------------------------------------------------------------------//
// end Utility_MaxwellFissionDistribution.cpp
//---------------------------------------------------------------------------//
