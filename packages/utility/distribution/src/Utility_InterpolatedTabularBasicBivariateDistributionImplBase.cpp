//---------------------------------------------------------------------------//
//!
//! \file   Utility_InterpolatedTabularBasicBivariateDistributionImplBase.cpp
//! \author Alex Robinson
//! \brief  The interpolated tabular basic bivariate dist. helper class
//!         template explicit instantiation
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
#include "Utility_InterpolatedTabularBasicBivariateDistributionImplBase.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"

namespace Utility{

EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LinLinLin,UnitAwareFullyTabularBasicBivariateDistribution<void,void,void> > );
EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LinLogLin,UnitAwareFullyTabularBasicBivariateDistribution<void,void,void> > );
EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LinLinLog,UnitAwareFullyTabularBasicBivariateDistribution<void,void,void> > );
EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LinLogLog,UnitAwareFullyTabularBasicBivariateDistribution<void,void,void> > );
EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LogLinLin,UnitAwareFullyTabularBasicBivariateDistribution<void,void,void> > );
EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LogLogLin,UnitAwareFullyTabularBasicBivariateDistribution<void,void,void> > );
EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LogLinLog,UnitAwareFullyTabularBasicBivariateDistribution<void,void,void> > );
EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LogLogLog,UnitAwareFullyTabularBasicBivariateDistribution<void,void,void> > );

EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LinLinLin,UnitAwarePartiallyTabularBasicBivariateDistribution<void,void,void> > );
EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LinLogLin,UnitAwarePartiallyTabularBasicBivariateDistribution<void,void,void> > );
EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LinLinLog,UnitAwarePartiallyTabularBasicBivariateDistribution<void,void,void> > );
EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LinLogLog,UnitAwarePartiallyTabularBasicBivariateDistribution<void,void,void> > );
EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LogLinLin,UnitAwarePartiallyTabularBasicBivariateDistribution<void,void,void> > );
EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LogLogLin,UnitAwarePartiallyTabularBasicBivariateDistribution<void,void,void> > );
EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LogLinLog,UnitAwarePartiallyTabularBasicBivariateDistribution<void,void,void> > );
EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LogLogLog,UnitAwarePartiallyTabularBasicBivariateDistribution<void,void,void> > );

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_InterpolatedTabularBasicBivariateDistributionImplBase.cpp
//---------------------------------------------------------------------------//
