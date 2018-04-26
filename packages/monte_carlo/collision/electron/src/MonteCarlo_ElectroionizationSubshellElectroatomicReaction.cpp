//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroionizationSubshellElectroatomicReaction.cpp
//! \author Alex Robinson
//! \brief  The electroionization subshell electroatomic reaction class
//!         instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ElectroionizationSubshellElectroatomicReaction.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( ElectroionizationSubshellElectroatomicReaction<Utility::LinLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( ElectroionizationSubshellElectroatomicReaction<Utility::LinLin,true> );

EXPLICIT_TEMPLATE_CLASS_INST( ElectroionizationSubshellElectroatomicReaction<Utility::LinLog,false> );
EXPLICIT_TEMPLATE_CLASS_INST( ElectroionizationSubshellElectroatomicReaction<Utility::LinLog,true> );

EXPLICIT_TEMPLATE_CLASS_INST( ElectroionizationSubshellElectroatomicReaction<Utility::LogLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( ElectroionizationSubshellElectroatomicReaction<Utility::LogLin,true> );

EXPLICIT_TEMPLATE_CLASS_INST( ElectroionizationSubshellElectroatomicReaction<Utility::LogLog,false> );
EXPLICIT_TEMPLATE_CLASS_INST( ElectroionizationSubshellElectroatomicReaction<Utility::LogLog,true> );

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationSubshellElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
