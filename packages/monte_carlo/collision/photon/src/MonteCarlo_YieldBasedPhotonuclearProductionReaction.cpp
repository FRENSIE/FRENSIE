//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_YieldBasedPhotonuclearProductionReaction.cpp
//! \author Alex Robinson
//! \brief  The yield-based photonuclear reaction class instantiation
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_YieldBasedPhotonuclearProductionReaction.hpp"
#include "MonteCarlo_NeutronState.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( YieldBasedPhotonuclearProductionReaction<NeutronState> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_YieldBasedPhotonuclearProductionReaction.cpp
//---------------------------------------------------------------------------//
