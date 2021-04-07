//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotonuclearReaction.cpp
//! \author Alex Robinson
//! \brief  The photonuclear reaction base class instantiation
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_PhotonuclearReaction.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<PhotonuclearReaction,Utility::LinLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<PhotonuclearReaction,Utility::LinLin,true> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonuclearReaction.cpp
//---------------------------------------------------------------------------//
