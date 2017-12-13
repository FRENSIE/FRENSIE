//---------------------------------------------------------------------------//
//!
//! \file   Utility_InterpolatedFullyTabularBasicBivariateDistribution.cpp
//! \author Alex Robinson
//! \brief  The interpolated fully tabular basic bivariate dist. class template
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

// FRENSIE Includes
#include "Utility_InterpolatedFullyTabularBasicBivariateDistribution.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"

namespace Utility{

EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<Utility::LinLinLin,void,void,void> );
EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<Utility::LinLogLin,void,void,void> );
EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<Utility::LinLinLog,void,void,void> );
EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<Utility::LinLogLog,void,void,void> );
EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<Utility::LogLinLin,void,void,void> );
EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<Utility::LogLogLin,void,void,void> );
EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<Utility::LogLinLog,void,void,void> );
EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedFullyTabularBasicBivariateDistribution<Utility::LogLogLog,void,void,void> );
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_InterpolatedFullyTabularBasicBivariateDistribution.cpp
//---------------------------------------------------------------------------//
