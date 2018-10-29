//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroionizationAdjointElectroatomicReaction.cpp
//! \author Alex Robinson
//! \brief  The electroionization adjoint electrotomic reaction class
//!         instantiation
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ElectroionizationAdjointElectroatomicReaction.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( ElectroionizationAdjointElectroatomicReaction<Utility::LinLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( ElectroionizationAdjointElectroatomicReaction<Utility::LinLin,true> );

EXPLICIT_TEMPLATE_CLASS_INST( ElectroionizationAdjointElectroatomicReaction<Utility::LogLog,false> );
EXPLICIT_TEMPLATE_CLASS_INST( ElectroionizationAdjointElectroatomicReaction<Utility::LogLog,true> );

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationAdjointElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
