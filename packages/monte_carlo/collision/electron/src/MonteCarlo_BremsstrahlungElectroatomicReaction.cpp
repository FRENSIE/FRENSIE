//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BremsstrahlungElectroatomicReaction.cpp
//! \author Luke Kersting
//! \brief  The bremsstrahlung Electroatomic reaction class instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_BremsstrahlungElectroatomicReaction.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( BremsstrahlungElectroatomicReaction<Utility::LinLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( BremsstrahlungElectroatomicReaction<Utility::LinLin,true> );

EXPLICIT_TEMPLATE_CLASS_INST( BremsstrahlungElectroatomicReaction<Utility::LinLog,false> );
EXPLICIT_TEMPLATE_CLASS_INST( BremsstrahlungElectroatomicReaction<Utility::LinLog,true> );

EXPLICIT_TEMPLATE_CLASS_INST( BremsstrahlungElectroatomicReaction<Utility::LogLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( BremsstrahlungElectroatomicReaction<Utility::LogLin,true> );

EXPLICIT_TEMPLATE_CLASS_INST( BremsstrahlungElectroatomicReaction<Utility::LogLog,false> );
EXPLICIT_TEMPLATE_CLASS_INST( BremsstrahlungElectroatomicReaction<Utility::LogLog,true> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_BremsstrahlungElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
