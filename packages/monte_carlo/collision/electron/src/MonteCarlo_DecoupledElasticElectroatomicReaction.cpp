//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DecoupledElasticElectroatomicReaction.cpp
//! \author Alex Robinson
//! \brief  The decoupled scattering elastic electroatomic reaction class
//!         instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_DecoupledElasticElectroatomicReaction.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( DecoupledElasticElectroatomicReaction<Utility::LinLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( DecoupledElasticElectroatomicReaction<Utility::LinLin,true> );

EXPLICIT_TEMPLATE_CLASS_INST( DecoupledElasticElectroatomicReaction<Utility::LinLog,false> );
EXPLICIT_TEMPLATE_CLASS_INST( DecoupledElasticElectroatomicReaction<Utility::LinLog,true> );

EXPLICIT_TEMPLATE_CLASS_INST( DecoupledElasticElectroatomicReaction<Utility::LogLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( DecoupledElasticElectroatomicReaction<Utility::LogLin,true> );

EXPLICIT_TEMPLATE_CLASS_INST( DecoupledElasticElectroatomicReaction<Utility::LogLog,false> );
EXPLICIT_TEMPLATE_CLASS_INST( DecoupledElasticElectroatomicReaction<Utility::LogLog,true> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_DecoupledElasticElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
