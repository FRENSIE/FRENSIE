//---------------------------------------------------------------------------//
//!
//! \file   Utility_CoupledElasticDistribution.cpp
//! \author Luke Kersting
//! \brief  The coupled elastic distribution class template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_CoupledElasticDistribution.hpp"

namespace Utility{

// Explicit instantiation
EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareCoupledElasticDistribution<LinLin,void,void> );
EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareCoupledElasticDistribution<LogLin,void,void> );

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_CoupledElasticDistribution.cpp
//---------------------------------------------------------------------------//
