//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NeutronNuclearReaction.cpp
//! \author Alex Robinson
//! \brief  The neutron nuclear reaction base class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_NeutronNuclearReaction.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<NeutronNuclearReaction,Utility::LinLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<NeutronNuclearReaction,Utility::LinLin,true> );

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_NeutronNuclearReaction.cpp
//---------------------------------------------------------------------------//
