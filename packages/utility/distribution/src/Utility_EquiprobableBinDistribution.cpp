//---------------------------------------------------------------------------//
//!
//! \file   Utility_EquiprobableBinDistribution.cpp
//! \author Alex Robinson
//! \brief  The equiprobable bin distribution class template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp" // Must include first
#include "Utility_EquiprobableBinDistribution.hpp"

EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareEquiprobableBinDistribution<void,void> );
EXPLICIT_CLASS_SAVE_LOAD_INST( Utility::UnitAwareEquiprobableBinDistribution<void,void> );

//---------------------------------------------------------------------------//
// end Utility_EquiprobableBinDistribution.cpp
//---------------------------------------------------------------------------//
