//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SubshellIncoherentAdjointPhotoatomicReaction.cpp
//! \author Alex Robinson
//! \brief  The subshell incoherent adjoint photoatomic reaction class inst.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_SubshellIncoherentAdjointPhotoatomicReaction.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( SubshellIncoherentAdjointPhotoatomicReaction<Utility::LinLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( SubshellIncoherentAdjointPhotoatomicReaction<Utility::LinLin,true> );

EXPLICIT_TEMPLATE_CLASS_INST( SubshellIncoherentAdjointPhotoatomicReaction<Utility::LinLog,false> );
EXPLICIT_TEMPLATE_CLASS_INST( SubshellIncoherentAdjointPhotoatomicReaction<Utility::LinLog,true> );

EXPLICIT_TEMPLATE_CLASS_INST( SubshellIncoherentAdjointPhotoatomicReaction<Utility::LogLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( SubshellIncoherentAdjointPhotoatomicReaction<Utility::LogLin,true> );

EXPLICIT_TEMPLATE_CLASS_INST( SubshellIncoherentAdjointPhotoatomicReaction<Utility::LogLog,false> );
EXPLICIT_TEMPLATE_CLASS_INST( SubshellIncoherentAdjointPhotoatomicReaction<Utility::LogLog,true> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_SubshellIncoherentAdjointPhotoatomicReaction.cpp
//---------------------------------------------------------------------------//
