//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CutoffElasticAdjointElectroatomicReaction.cpp
//! \author Alex Robinson
//! \brief  The cutoff scattering elastic electroatomic reaction class
//!         instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_CutoffElasticAdjointElectroatomicReaction.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( CutoffElasticAdjointElectroatomicReaction<Utility::LinLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( CutoffElasticAdjointElectroatomicReaction<Utility::LinLin,true> );

EXPLICIT_TEMPLATE_CLASS_INST( CutoffElasticAdjointElectroatomicReaction<Utility::LinLog,false> );
EXPLICIT_TEMPLATE_CLASS_INST( CutoffElasticAdjointElectroatomicReaction<Utility::LinLog,true> );

EXPLICIT_TEMPLATE_CLASS_INST( CutoffElasticAdjointElectroatomicReaction<Utility::LogLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( CutoffElasticAdjointElectroatomicReaction<Utility::LogLin,true> );

EXPLICIT_TEMPLATE_CLASS_INST( CutoffElasticAdjointElectroatomicReaction<Utility::LogLog,false> );
EXPLICIT_TEMPLATE_CLASS_INST( CutoffElasticAdjointElectroatomicReaction<Utility::LogLog,true> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_CutoffElasticAdjointElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
