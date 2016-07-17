//---------------------------------------------------------------------------//
//!
//! \file   Utility_TabularDistribution.cpp
//! \author Alex Robinson
//! \brief  The tabular distribution class template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_TabularDistribution.hpp"

namespace Utility{

// Explicit instantiation
EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareTabularDistribution<LinLin,void,void> );
EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareTabularDistribution<LinLog,void,void> );
EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareTabularDistribution<LogLin,void,void> );
EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareTabularDistribution<LogLog,void,void> );
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_TabularDistribution.cpp
//---------------------------------------------------------------------------//
