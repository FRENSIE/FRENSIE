//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CoupledElasticAdjointElectroatomicReaction.cpp
//! \author Alex Robinson
//! \brief  The coupled scattering elastic adjoint electroatomic reaction class
//!         instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_CoupledElasticAdjointElectroatomicReaction.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( CoupledElasticAdjointElectroatomicReaction<Utility::LinLin,false> );
EXPLICIT_TEMPLATE_CLASS_INST( CoupledElasticAdjointElectroatomicReaction<Utility::LinLin,true> );

EXPLICIT_TEMPLATE_CLASS_INST( CoupledElasticAdjointElectroatomicReaction<Utility::LogLog,false> );
EXPLICIT_TEMPLATE_CLASS_INST( CoupledElasticAdjointElectroatomicReaction<Utility::LogLog,true> );

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_CoupledElasticAdjointElectroatomicReaction.cpp
//---------------------------------------------------------------------------//
