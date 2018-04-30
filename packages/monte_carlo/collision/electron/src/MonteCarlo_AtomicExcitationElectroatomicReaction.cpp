//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AtomicExcitationElectroatomicReaction.cpp
//! \author Alex Robinson
//! \brief  The atomic excitation electroatomic reaction class instantiation
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AtomicExcitationElectroatomicReaction.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( AtomicExcitationElectroatomicReaction<Utility::LinLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( AtomicExcitationElectroatomicReaction<Utility::LinLin,true> );

EXPLICIT_TEMPLATE_CLASS_INST( AtomicExcitationElectroatomicReaction<Utility::LinLog,false> );
EXPLICIT_TEMPLATE_CLASS_INST( AtomicExcitationElectroatomicReaction<Utility::LinLog,true> );

EXPLICIT_TEMPLATE_CLASS_INST( AtomicExcitationElectroatomicReaction<Utility::LogLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( AtomicExcitationElectroatomicReaction<Utility::LogLin,true> );

EXPLICIT_TEMPLATE_CLASS_INST( AtomicExcitationElectroatomicReaction<Utility::LogLog,false> );
EXPLICIT_TEMPLATE_CLASS_INST( AtomicExcitationElectroatomicReaction<Utility::LogLog,true> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AtomicExcitationElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
