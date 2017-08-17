//---------------------------------------------------------------------------//
//!
//! \file   Utility_CutoffElasticDistribution.cpp
//! \author Luke Kersting
//! \brief  The cutoff elastic distribution class template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_CutoffElasticDistribution.hpp"

namespace Utility{

// Explicit instantiation
EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareCutoffElasticDistribution<LinLin,void,void> );
EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareCutoffElasticDistribution<LogLin,void,void> );

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_CutoffElasticDistribution.cpp
//---------------------------------------------------------------------------//
