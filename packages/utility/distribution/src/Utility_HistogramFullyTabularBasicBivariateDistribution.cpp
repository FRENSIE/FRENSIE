//---------------------------------------------------------------------------//
//!
//! \file   Utility_HistogramFullyTabularBasicBivariateDistribution.cpp
//! \author Alex Robinson
//! \brief  The histogram fully tabular basic bivariate dist. class template
//!         instantiation
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
#include "Utility_HistogramFullyTabularBasicBivariateDistribution.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"

namespace Utility{

EXPLICIT_DISTRIBUTION_INST( UnitAwareHistogramFullyTabularBasicBivariateDistribution<void,void,void> );
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_HistogramFullyTabularBasicBivariateDistribution.cpp
//---------------------------------------------------------------------------//
