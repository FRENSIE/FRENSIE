//---------------------------------------------------------------------------//
//!
//! \file   Utility_TabularDistribution.cpp
//! \author Alex Robinson
//! \brief  The tabular distribution class template instantiations
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

// FRENSIE Includes
#include "Utility_TabularDistribution.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"

namespace Utility{

// Explicit instantiation
EXPLICIT_DISTRIBUTION_INST( UnitAwareTabularDistribution<LinLin,void,void> );
EXPLICIT_DISTRIBUTION_INST( UnitAwareTabularDistribution<LinLog,void,void> );
EXPLICIT_DISTRIBUTION_INST( UnitAwareTabularDistribution<LogLin,void,void> );
EXPLICIT_DISTRIBUTION_INST( UnitAwareTabularDistribution<LogLog,void,void> );
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_TabularDistribution.cpp
//---------------------------------------------------------------------------//
