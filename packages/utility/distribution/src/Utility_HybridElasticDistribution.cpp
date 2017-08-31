//---------------------------------------------------------------------------//
//!
//! \file   Utility_HybridElasticDistribution.cpp
//! \author Luke Kersting
//! \brief  The hybrid elastic distribution class template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_HybridElasticDistribution.hpp"

namespace Utility{

// Explicit instantiation
EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareHybridElasticDistribution<LinLin,void,void> );
EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareHybridElasticDistribution<LogLin,void,void> );

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_HybridElasticDistribution.cpp
//---------------------------------------------------------------------------//
