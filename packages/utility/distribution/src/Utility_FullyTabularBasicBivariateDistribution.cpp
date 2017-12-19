//---------------------------------------------------------------------------//
//!
//! \file   Utility_FullyTabularBasicBivariateDistribution.cpp
//! \author Alex Robinson
//! \brief  The fully tabular basic bivariate distribution class template inst.
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
#include "Utility_FullyTabularBasicBivariateDistribution.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"

namespace Utility{

// Explicit instantiation
EXPLICIT_DISTRIBUTION_INST( UnitAwareFullyTabularBasicBivariateDistribution<void,void,void> );
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_TabularBasicBivariateDistribution.cpp
//---------------------------------------------------------------------------//
