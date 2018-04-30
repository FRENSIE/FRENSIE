//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AbsorptionPositronatomicReaction.cpp
//! \author Alex Robinson
//! \brief  The absorption positron-atomic reaction class instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AbsorptionPositronatomicReaction.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionPositronatomicReaction<Utility::LinLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionPositronatomicReaction<Utility::LinLin,true> );

EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionPositronatomicReaction<Utility::LinLog,false> );
EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionPositronatomicReaction<Utility::LinLog,true> );

EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionPositronatomicReaction<Utility::LogLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionPositronatomicReaction<Utility::LogLin,true> );

EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionPositronatomicReaction<Utility::LogLog,false> );
EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionPositronatomicReaction<Utility::LogLog,true> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AbsorptionPositronatomicReaction.cpp
//---------------------------------------------------------------------------//
