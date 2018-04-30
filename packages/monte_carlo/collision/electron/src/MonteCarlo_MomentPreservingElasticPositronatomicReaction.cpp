//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_MomentPreservingElasticPositronatomicReaction.cpp
//! \author Luke Kersting
//! \brief  The single scattering elastic positron-atomic reaction class decl.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_MomentPreservingElasticPositronatomicReaction.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( MomentPreservingElasticPositronatomicReaction<Utility::LinLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( MomentPreservingElasticPositronatomicReaction<Utility::LinLin,true> );

EXPLICIT_TEMPLATE_CLASS_INST( MomentPreservingElasticPositronatomicReaction<Utility::LinLog,false> );
EXPLICIT_TEMPLATE_CLASS_INST( MomentPreservingElasticPositronatomicReaction<Utility::LinLog,true> );

EXPLICIT_TEMPLATE_CLASS_INST( MomentPreservingElasticPositronatomicReaction<Utility::LogLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( MomentPreservingElasticPositronatomicReaction<Utility::LogLin,true> );

EXPLICIT_TEMPLATE_CLASS_INST( MomentPreservingElasticPositronatomicReaction<Utility::LogLog,false> );
EXPLICIT_TEMPLATE_CLASS_INST( MomentPreservingElasticPositronatomicReaction<Utility::LogLog,true> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_MomentPreservingElasticPositronatomicReaction.cpp
//---------------------------------------------------------------------------//
