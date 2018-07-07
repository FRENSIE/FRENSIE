//---------------------------------------------------------------------------//
//!
//! \file   Utility_HybridElasticDistribution.cpp
//! \author Luke Kersting
//! \brief  The hybrid elastic distribution class template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp" // Must be included first
#include "MonteCarlo_HybridElasticDistribution.hpp"

EXPLICIT_CLASS_INST( MonteCarlo::UnitAwareHybridElasticDistribution<LinLin,void,void> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, UnitAwareHybridElasticDistribution<LinLin,void,void> );

EXPLICIT_CLASS_INST( MonteCarlo::UnitAwareHybridElasticDistribution<LogLin,void,void> );
EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, UnitAwareHybridElasticDistribution<LogLin,void,void> );

//---------------------------------------------------------------------------//
// end Utility_HybridElasticDistribution.cpp
//---------------------------------------------------------------------------//
