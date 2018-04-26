//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DecoupledElasticAdjointElectroatomicReaction.cpp
//! \author Alex Robinson
//! \brief  The decoupled scattering elastic AdjointElectroatomic reaction
//!         class instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_DecoupledElasticAdjointElectroatomicReaction.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( DecoupledElasticAdjointElectroatomicReaction<Utility::LinLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( DecoupledElasticAdjointElectroatomicReaction<Utility::LinLin,true> );

EXPLICIT_TEMPLATE_CLASS_INST( DecoupledElasticAdjointElectroatomicReaction<Utility::LinLog,false> );
EXPLICIT_TEMPLATE_CLASS_INST( DecoupledElasticAdjointElectroatomicReaction<Utility::LinLog,true> );

EXPLICIT_TEMPLATE_CLASS_INST( DecoupledElasticAdjointElectroatomicReaction<Utility::LogLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( DecoupledElasticAdjointElectroatomicReaction<Utility::LogLin,true> );

EXPLICIT_TEMPLATE_CLASS_INST( DecoupledElasticAdjointElectroatomicReaction<Utility::LogLog,false> );
EXPLICIT_TEMPLATE_CLASS_INST( DecoupledElasticAdjointElectroatomicReaction<Utility::LogLog,true> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_DecoupledElasticAdjointElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
