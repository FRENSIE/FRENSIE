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

EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::UnitAwareCoupledElasticDistribution<Utility::LinLin,void,void> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::UnitAwareCoupledElasticDistribution<Utility::LinLin,void,void> );

EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::UnitAwareCoupledElasticDistribution<Utility::LogLin,void,void> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::UnitAwareCoupledElasticDistribution<Utility::LogLin,void,void> );

EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::UnitAwareCoupledElasticDistribution<Utility::LinNudgedLogCos,void,void> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::UnitAwareCoupledElasticDistribution<Utility::LinNudgedLogCos,void,void> );

EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::UnitAwareCoupledElasticDistribution<Utility::LogNudgedLogCos,void,void> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo::UnitAwareCoupledElasticDistribution<Utility::LogNudgedLogCos,void,void> );

//---------------------------------------------------------------------------//
// end Utility_CoupledElasticDistribution.cpp
//---------------------------------------------------------------------------//
