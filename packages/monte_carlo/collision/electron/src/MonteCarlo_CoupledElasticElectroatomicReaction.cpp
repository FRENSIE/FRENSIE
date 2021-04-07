//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CoupledElasticElectroatomicReaction.cpp
//! \author Alex Robinson
//! \brief  The coupled scattering elastic electroatomic reaction class
//!         instantiation
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_CoupledElasticElectroatomicReaction.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( CoupledElasticElectroatomicReaction<Utility::LinLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( CoupledElasticElectroatomicReaction<Utility::LinLin,true> );

EXPLICIT_TEMPLATE_CLASS_INST( CoupledElasticElectroatomicReaction<Utility::LinLog,false> );
EXPLICIT_TEMPLATE_CLASS_INST( CoupledElasticElectroatomicReaction<Utility::LinLog,true> );

EXPLICIT_TEMPLATE_CLASS_INST( CoupledElasticElectroatomicReaction<Utility::LogLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( CoupledElasticElectroatomicReaction<Utility::LogLin,true> );

EXPLICIT_TEMPLATE_CLASS_INST( CoupledElasticElectroatomicReaction<Utility::LogLog,false> );
EXPLICIT_TEMPLATE_CLASS_INST( CoupledElasticElectroatomicReaction<Utility::LogLog,true> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_CoupledElasticElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
