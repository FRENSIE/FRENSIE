//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ScreenedRutherfordElasticElectroatomicReaction.cpp
//! \author Alex Robinson
//! \brief  The screened rutherford scattering elastic electroatomic reaction
//!         class instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ScreenedRutherfordElasticElectroatomicReaction.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( ScreenedRutherfordElasticElectroatomicReaction<Utility::LinLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( ScreenedRutherfordElasticElectroatomicReaction<Utility::LinLin,true> );

EXPLICIT_TEMPLATE_CLASS_INST( ScreenedRutherfordElasticElectroatomicReaction<Utility::LinLog,false> );
EXPLICIT_TEMPLATE_CLASS_INST( ScreenedRutherfordElasticElectroatomicReaction<Utility::LinLog,true> );

EXPLICIT_TEMPLATE_CLASS_INST( ScreenedRutherfordElasticElectroatomicReaction<Utility::LogLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( ScreenedRutherfordElasticElectroatomicReaction<Utility::LogLin,true> );

EXPLICIT_TEMPLATE_CLASS_INST( ScreenedRutherfordElasticElectroatomicReaction<Utility::LogLog,false> );
EXPLICIT_TEMPLATE_CLASS_INST( ScreenedRutherfordElasticElectroatomicReaction<Utility::LogLog,true> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ScreenedRutherfordElasticElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
