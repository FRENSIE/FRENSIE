//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_MomentPreservingElasticAdjointElectroatomicReaction.cpp
//! \author Luke Kersting
//! \brief  The single scattering elastic adjoint electroatomic reaction class decl.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_MomentPreservingElasticAdjointElectroatomicReaction.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( MomentPreservingElasticAdjointElectroatomicReaction<Utility::LinLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( MomentPreservingElasticAdjointElectroatomicReaction<Utility::LinLin,true> );

EXPLICIT_TEMPLATE_CLASS_INST( MomentPreservingElasticAdjointElectroatomicReaction<Utility::LogLog,false> );
EXPLICIT_TEMPLATE_CLASS_INST( MomentPreservingElasticAdjointElectroatomicReaction<Utility::LogLog,true> );

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_MomentPreservingElasticAdjointElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
