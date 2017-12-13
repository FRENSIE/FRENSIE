//---------------------------------------------------------------------------//
//!
//! \file   Utility_HistogramTabularBasicBivariateDistributionImplBase.cpp
//! \author Alex Robinson
//! \brief  The histogram tabular basic bivariate dist. helper class template
//!         explicit instantiation
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
#include "Utility_HistogramTabularBasicBivariateDistributionImplBase.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"

namespace Utility{

EXPLICIT_DISTRIBUTION_INST( UnitAwareHistogramTabularBasicBivariateDistributionImplBase<UnitAwareFullyTabularBasicBivariateDistribution<void,void,void> > );
EXPLICIT_DISTRIBUTION_INST( UnitAwareHistogramTabularBasicBivariateDistributionImplBase<UnitAwarePartiallyTabularBasicBivariateDistribution<void,void,void> > );

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_HistogramTabularBasicBivariateDistributionImplBase.cpp
//---------------------------------------------------------------------------//

