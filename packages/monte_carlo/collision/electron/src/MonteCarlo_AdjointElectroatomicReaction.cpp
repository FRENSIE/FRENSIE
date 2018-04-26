//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectroatomicReaction.cpp
//! \author Alex Robinson
//! \brief  The electron reaction base class instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatomicReaction.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<AdjointElectroatomicReaction,Utility::LinLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<AdjointElectroatomicReaction,Utility::LinLin,true> );

EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<AdjointElectroatomicReaction,Utility::LinLog,false> );
EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<AdjointElectroatomicReaction,Utility::LinLog,true> );

EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<AdjointElectroatomicReaction,Utility::LogLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<AdjointElectroatomicReaction,Utility::LogLin,true> );

EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<AdjointElectroatomicReaction,Utility::LogLog,false> );
EXPLICIT_TEMPLATE_CLASS_INST( StandardReactionBaseImpl<AdjointElectroatomicReaction,Utility::LogLog,true> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
