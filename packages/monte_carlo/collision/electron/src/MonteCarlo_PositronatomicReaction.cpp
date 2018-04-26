//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PositronatomicReaction.cpp
//! \author Alex Robinson
//! \brief  The positron reaction base class instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_PositronatomicReaction.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<PositronatomicReaction,Utility::LinLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<PositronatomicReaction,Utility::LinLin,true> );

EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<PositronatomicReaction,Utility::LinLog,false> );
EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<PositronatomicReaction,Utility::LinLog,true> );

EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<PositronatomicReaction,Utility::LogLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<PositronatomicReaction,Utility::LogLin,true> );

EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<PositronatomicReaction,Utility::LogLog,false> );
EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<PositronatomicReaction,Utility::LogLog,true> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PositronatomicReaction.cpp
//---------------------------------------------------------------------------//
