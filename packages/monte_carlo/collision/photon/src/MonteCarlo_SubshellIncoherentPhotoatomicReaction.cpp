//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SubshellIncoherentPhotoatomicReaction.cpp
//! \author Alex Robinson
//! \brief  The subshell incoherent photoatomic reaction class instantiation
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_SubshellIncoherentPhotoatomicReaction.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( SubshellIncoherentPhotoatomicReaction<Utility::LinLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( SubshellIncoherentPhotoatomicReaction<Utility::LinLin,true> );

EXPLICIT_TEMPLATE_CLASS_INST( SubshellIncoherentPhotoatomicReaction<Utility::LinLog,false> );
EXPLICIT_TEMPLATE_CLASS_INST( SubshellIncoherentPhotoatomicReaction<Utility::LinLog,true> );

EXPLICIT_TEMPLATE_CLASS_INST( SubshellIncoherentPhotoatomicReaction<Utility::LogLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( SubshellIncoherentPhotoatomicReaction<Utility::LogLin,true> );

EXPLICIT_TEMPLATE_CLASS_INST( SubshellIncoherentPhotoatomicReaction<Utility::LogLog,false> );
EXPLICIT_TEMPLATE_CLASS_INST( SubshellIncoherentPhotoatomicReaction<Utility::LogLog,true> );

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_SubshellIncoherentPhotoatomicReaction.cpp
//---------------------------------------------------------------------------//
