//---------------------------------------------------------------------------//
//!
//! \file   Utility_TabularBasicBivariateDistribution.cpp
//! \author Alex Robinson
//! \brief  The tabular basic bivariate distribution class template inst.
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
#include "Utility_TabularBasicBivariateDistribution.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"

namespace Utility{

// Explicit instantiation
EXPLICIT_DISTRIBUTION_INST( UnitAwareTabularBasicBivariateDistribution<void,void,void,UnitAwareUnivariateDistribution> );
EXPLICIT_DISTRIBUTION_INST( UnitAwareTabularBasicBivariateDistribution<void,void,void,UnitAwareTabularUnivariateDistribution> );
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_TabularBasicBivariateDistribution.cpp
//---------------------------------------------------------------------------//
