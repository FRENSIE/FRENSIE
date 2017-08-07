//---------------------------------------------------------------------------//
//!
//! \file   Utility_AnalogElasticOneDDistribution.cpp
//! \author Luke Kersting
//! \brief  The analog elastic distribution class template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_AnalogElasticOneDDistribution.hpp"

namespace Utility{

// Explicit instantiation
EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareAnalogElasticOneDDistribution<LinLin,void,void> );
EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareAnalogElasticOneDDistribution<LogLin,void,void> );

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_AnalogElasticOneDDistribution.cpp
//---------------------------------------------------------------------------//
