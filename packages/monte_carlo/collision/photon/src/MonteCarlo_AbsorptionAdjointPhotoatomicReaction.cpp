//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AbsorptionAdjointPhotoatomicReaction.cpp
//! \author Alex Robinson
//! \brief  The absorption adjoint photoatomic reaction class instantiation
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AbsorptionAdjointPhotoatomicReaction.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionAdjointPhotoatomicReaction<Utility::LinLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionAdjointPhotoatomicReaction<Utility::LinLin,true> );

EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionAdjointPhotoatomicReaction<Utility::LinLog,false> );
EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionAdjointPhotoatomicReaction<Utility::LinLog,true> );

EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionAdjointPhotoatomicReaction<Utility::LogLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionAdjointPhotoatomicReaction<Utility::LogLin,true> );

EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionAdjointPhotoatomicReaction<Utility::LogLog,false> );
EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionAdjointPhotoatomicReaction<Utility::LogLog,true> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AbsorptionAdjointPhotoatomicReaction.cpp
//---------------------------------------------------------------------------//
