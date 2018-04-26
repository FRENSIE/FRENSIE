//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_HybridElasticPositronatomicReaction.cpp
//! \author Alex Robinson
//! \brief  The hybrid scattering elastic positron-atomic reaction class
//!         instantiation
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_HybridElasticPositronatomicReaction.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( HybridElasticPositronatomicReaction<Utility::LinLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( HybridElasticPositronatomicReaction<Utility::LinLin,true> );

EXPLICIT_TEMPLATE_CLASS_INST( HybridElasticPositronatomicReaction<Utility::LinLog,false> );
EXPLICIT_TEMPLATE_CLASS_INST( HybridElasticPositronatomicReaction<Utility::LinLog,true> );

EXPLICIT_TEMPLATE_CLASS_INST( HybridElasticPositronatomicReaction<Utility::LogLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( HybridElasticPositronatomicReaction<Utility::LogLin,true> );

EXPLICIT_TEMPLATE_CLASS_INST( HybridElasticPositronatomicReaction<Utility::LogLog,false> );
EXPLICIT_TEMPLATE_CLASS_INST( HybridElasticPositronatomicReaction<Utility::LogLog,true> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_HybridElasticPositronatomicReaction.cpp
//---------------------------------------------------------------------------//
