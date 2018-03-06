//---------------------------------------------------------------------------//
//!
//! \file   Utility_TabularCDFDistribution.cpp
//! \author Luke Kersting
//! \brief  The tabular CDF distribution class template instantiations
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>

// FRENSIE Includes
#include "Utility_TabularCDFDistribution.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"

namespace Utility{

  // Explicit instantiation
  EXPLICIT_DISTRIBUTION_INST( UnitAwareTabularCDFDistribution<LinLin,void,void> );
  EXPLICIT_DISTRIBUTION_INST( UnitAwareTabularCDFDistribution<LogLog,void,void> );
  EXPLICIT_DISTRIBUTION_INST( UnitAwareTabularCDFDistribution<LinLog,void,void> );
  EXPLICIT_DISTRIBUTION_INST( UnitAwareTabularCDFDistribution<LogLin,void,void> );

  // Explicit cosine instantiation
  EXPLICIT_DISTRIBUTION_INST( UnitAwareTabularCDFDistribution<LogLogCos,void,void> );
  EXPLICIT_DISTRIBUTION_INST( UnitAwareTabularCDFDistribution<LinLogCos,void,void> );

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_TabularCDFDistribution.cpp
//---------------------------------------------------------------------------//
