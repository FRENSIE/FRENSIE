//---------------------------------------------------------------------------//
//!
//! \file   Utility_PowerDistribution.cpp
//! \author Alex Robinson
//! \brief  The power distribution class template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "Utility_PowerDistribution.hpp"

EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwarePowerDistribution<1,void,void> );
EXPLICIT_CLASS_SAVE_LOAD_INST( Utility::UnitAwarePowerDistribution<1,void,void> );

EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwarePowerDistribution<2,void,void> );
EXPLICIT_CLASS_SAVE_LOAD_INST( Utility::UnitAwarePowerDistribution<2,void,void> );

//---------------------------------------------------------------------------//
// end Utility_PowerDistribution.cpp
//---------------------------------------------------------------------------//
