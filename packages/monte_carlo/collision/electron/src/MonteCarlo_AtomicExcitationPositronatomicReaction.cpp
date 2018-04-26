//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AtomicExcitationPositronatomicReaction.cpp
//! \author Alex Robinson
//! \brief  The atomic excitation positron-atomic reaction class instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AtomicExcitationPositronatomicReaction.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( AtomicExcitationPositronatomicReaction<Utility::LinLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( AtomicExcitationPositronatomicReaction<Utility::LinLin,true> );

EXPLICIT_TEMPLATE_CLASS_INST( AtomicExcitationPositronatomicReaction<Utility::LinLog,false> );
EXPLICIT_TEMPLATE_CLASS_INST( AtomicExcitationPositronatomicReaction<Utility::LinLog,true> );

EXPLICIT_TEMPLATE_CLASS_INST( AtomicExcitationPositronatomicReaction<Utility::LogLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( AtomicExcitationPositronatomicReaction<Utility::LogLin,true> );

EXPLICIT_TEMPLATE_CLASS_INST( AtomicExcitationPositronatomicReaction<Utility::LogLog,false> );
EXPLICIT_TEMPLATE_CLASS_INST( AtomicExcitationPositronatomicReaction<Utility::LogLog,true> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AtomicExcitationPositronatomicReaction.cpp
//---------------------------------------------------------------------------//
