//---------------------------------------------------------------------------//
//!
//! \file   Utility_AnalogElasticDistribution.cpp
//! \author Luke Kersting
//! \brief  The analog elastic distribution class template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_AnalogElasticDistribution.hpp"

namespace Utility{

// Explicit instantiation
EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareAnalogElasticDistribution<LinLin,void,void> );
EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareAnalogElasticDistribution<LinLog,void,void> );
EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareAnalogElasticDistribution<LogLin,void,void> );
EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareAnalogElasticDistribution<LogLog,void,void> );
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_AnalogElasticDistribution.cpp
//---------------------------------------------------------------------------//
