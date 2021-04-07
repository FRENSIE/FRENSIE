//---------------------------------------------------------------------------//
//!
//! \file   Utility_WattDistribution.cpp
//! \author Alex Robinson
//! \brief  The Watt distribution class template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp" // Must include first
#include "Utility_WattDistribution.hpp"

EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareWattDistribution<void,void> );
EXPLICIT_CLASS_SAVE_LOAD_INST( Utility::UnitAwareWattDistribution<void,void> );
  
//---------------------------------------------------------------------------//
// end Utility_WattDistribution.cpp
//---------------------------------------------------------------------------//
