//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroatomicReaction.cpp
//! \author Alex Robinson
//! \brief  The Electron reaction base class instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ElectroatomicReaction.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<ElectroatomicReaction,Utility::LinLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<ElectroatomicReaction,Utility::LinLin,true> );

EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<ElectroatomicReaction,Utility::LinLog,false> );
EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<ElectroatomicReaction,Utility::LinLog,true> );

EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<ElectroatomicReaction,Utility::LogLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<ElectroatomicReaction,Utility::LogLin,true> );

EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<ElectroatomicReaction,Utility::LogLog,false> );
EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<ElectroatomicReaction,Utility::LogLog,true> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
