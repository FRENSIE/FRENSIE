//---------------------------------------------------------------------------//
//!
//! \file   Utility_TabularCDFDistribution.cpp
//! \author Luke Kersting
//! \brief  The tabular CDF distribution class template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_TabularCDFDistribution.hpp"

namespace Utility{

  // Explicit instantiation
  EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareTabularCDFDistribution<LinLin,void,void> );
  EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareTabularCDFDistribution<LinLog,void,void> );
  EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareTabularCDFDistribution<LogLin,void,void> );
  EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareTabularCDFDistribution<LogLog,void,void> );
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_TabularCDFDistribution.cpp
//---------------------------------------------------------------------------//
