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

// FRENSIE Includes
#include "Utility_InterpolatedTabularBasicBivariateDistribution.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"

namespace Utility{

EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LinLinLin,Utility::FullyTabularBasicBivariateDistribution<void,void,void> > );
EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LinLogLin,Utility::FullyTabularBasicBivariateDistribution<void,void,void> > );
EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LinLinLog,Utility::FullyTabularBasicBivariateDistribution<void,void,void> > );
EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LinLogLog,Utility::FullyTabularBasicBivariateDistribution<void,void,void> > );
EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LogLinLin,Utility::FullyTabularBasicBivariateDistribution<void,void,void> > );
EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LogLogLin,Utility::FullyTabularBasicBivariateDistribution<void,void,void> > );
EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LogLinLog,Utility::FullyTabularBasicBivariateDistribution<void,void,void> > );
EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LogLogLog,Utility::FullyTabularBasicBivariateDistribution<void,void,void> > );

EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LinLinLin,Utility::PartiallyTabularBasicBivariateDistribution<void,void,void> > );
EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LinLogLin,Utility::PartiallyTabularBasicBivariateDistribution<void,void,void> > );
EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LinLinLog,Utility::PartiallyTabularBasicBivariateDistribution<void,void,void> > );
EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LinLogLog,Utility::PartiallyTabularBasicBivariateDistribution<void,void,void> > );
EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LogLinLin,Utility::PartiallyTabularBasicBivariateDistribution<void,void,void> > );
EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LogLogLin,Utility::PartiallyTabularBasicBivariateDistribution<void,void,void> > );
EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LogLinLog,Utility::PartiallyTabularBasicBivariateDistribution<void,void,void> > );
EXPLICIT_DISTRIBUTION_INST( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase<Utility::LogLogLog,Utility::PartiallyTabularBasicBivariateDistribution<void,void,void> > );

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_InterpolatedTabularBasicBivariateDistributionImplBase.cpp
//---------------------------------------------------------------------------//
