//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CoupledElasticPositronatomicReaction.cpp
//! \author Alex Robinson
//! \brief  The coupled scattering elastic positron-atomic reaction class
//!         instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_CoupledElasticPositronatomicReaction.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( CoupledElasticPositronatomicReaction<Utility::LinLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( CoupledElasticPositronatomicReaction<Utility::LinLin,true> );

EXPLICIT_TEMPLATE_CLASS_INST( CoupledElasticPositronatomicReaction<Utility::LinLog,false> );
EXPLICIT_TEMPLATE_CLASS_INST( CoupledElasticPositronatomicReaction<Utility::LinLog,true> );

EXPLICIT_TEMPLATE_CLASS_INST( CoupledElasticPositronatomicReaction<Utility::LogLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( CoupledElasticPositronatomicReaction<Utility::LogLin,true> );

EXPLICIT_TEMPLATE_CLASS_INST( CoupledElasticPositronatomicReaction<Utility::LogLog,false> );
EXPLICIT_TEMPLATE_CLASS_INST( CoupledElasticPositronatomicReaction<Utility::LogLog,true> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_CoupledElasticPositronatomicReaction.cpp
//---------------------------------------------------------------------------//
