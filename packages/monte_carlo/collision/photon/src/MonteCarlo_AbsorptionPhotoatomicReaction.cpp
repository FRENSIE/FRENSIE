//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AbsorptionPhotoatomicReaction.cpp
//! \author Alex Robinson
//! \brief  The absorption photoatomic reaction class instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AbsorptionPhotoatomicReaction.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionPhotoatomicReaction<Utility::LinLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionPhotoatomicReaction<Utility::LinLin,true> );

EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionPhotoatomicReaction<Utility::LinLog,false> );
EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionPhotoatomicReaction<Utility::LinLog,true> );

EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionPhotoatomicReaction<Utility::LogLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionPhotoatomicReaction<Utility::LogLin,true> );

EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionPhotoatomicReaction<Utility::LogLog,false> );
EXPLICIT_TEMPLATE_CLASS_INST( AbsorptionPhotoatomicReaction<Utility::LogLog,true> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AbsorptionPhotoatomicReaction.cpp
//---------------------------------------------------------------------------//
