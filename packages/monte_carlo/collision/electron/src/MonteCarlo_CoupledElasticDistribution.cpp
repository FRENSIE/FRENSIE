//---------------------------------------------------------------------------//
//!
//! \file   Utility_CoupledElasticDistribution.cpp
//! \author Luke Kersting
//! \brief  The coupled elastic distribution class template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp" // Must be included first
#include "MonteCarlo_CoupledElasticDistribution.hpp"

EXPLICIT_CLASS_INST( MonteCarlo::UnitAwareCoupledElasticDistribution<LinLin,void,void> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::UnitAwareCoupledElasticDistribution<LinLin,void,void> );

EXPLICIT_CLASS_INST( MonteCarlo::UnitAwareCoupledElasticDistribution<LogLin,void,void> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::UnitAwareCoupledElasticDistribution<LogLin,void,void> );

EXPLICIT_CLASS_INST( MonteCarlo::UnitAwareCoupledElasticDistribution<LinLogCos,void,void> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::UnitAwareCoupledElasticDistribution<LinLogCos,void,void> );

EXPLICIT_CLASS_INST( MonteCarlo::UnitAwareCoupledElasticDistribution<LogLogCos,void,void> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::UnitAwareCoupledElasticDistribution<LogLogCos,void,void> );

//---------------------------------------------------------------------------//
// end Utility_CoupledElasticDistribution.cpp
//---------------------------------------------------------------------------//
