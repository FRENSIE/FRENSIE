//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotonuclearReaction.cpp
//! \author Alex Robinson
//! \brief  The photonuclear reaction base class instantiation
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_PhotonuclearReaction.hpp"
#include "MonteCarlo_NeutronState.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( PhotonuclearReaction<NeutronState> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonuclearReaction.cpp
//---------------------------------------------------------------------------//
