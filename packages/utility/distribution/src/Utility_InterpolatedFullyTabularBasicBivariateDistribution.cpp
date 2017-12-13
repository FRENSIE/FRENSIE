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
#include "Utility_UniformDistribution.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"

namespace Utility{

EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedFullyTabularBivariateDistribution<Utility::LinLinLin,void,void,void> );
EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedFullyTabularBivariateDistribution<Utility::LinLogLin,void,void,void> );
EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedFullyTabularBivariateDistribution<Utility::LinLinLog,void,void,void> );
EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedFullyTabularBivariateDistribution<Utility::LinLogLog,void,void,void> );
EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedFullyTabularBivariateDistribution<Utility::LogLinLin,void,void,void> );
EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedFullyTabularBivariateDistribution<Utility::LogLogLin,void,void,void> );
EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedFullyTabularBivariateDistribution<Utility::LogLinLog,void,void,void> );
EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedFullyTabularBivariateDistribution<Utility::LogLogLog,void,void,void> );
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_InterpolatedFullyTabularBasicBivariateDistribution.cpp
//---------------------------------------------------------------------------//
