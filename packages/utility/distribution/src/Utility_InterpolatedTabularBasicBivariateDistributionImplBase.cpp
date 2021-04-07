//---------------------------------------------------------------------------//
//!
//! \file   Utility_InterpolatedTabularBasicBivariateDistributionImplBase.cpp
//! \author Alex Robinson
//! \brief  The interpolated tabular basic bivariate dist. helper class
//!         template explicit instantiation
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp" // Must include first
#include "Utility_InterpolatedTabularBasicBivariateDistributionImplBase.hpp"

EXPLICIT_INTERPOLATED_TABULAR_BASIC_BIVARIATE_DIST_FULL( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase, Utility::UnitAwareFullyTabularBasicBivariateDistribution<void,void,void> );
EXPLICIT_INTERPOLATED_TABULAR_BASIC_BIVARIATE_DIST_PARTIAL( UnitAwareInterpolatedTabularBasicBivariateDistributionImplBase, Utility::UnitAwarePartiallyTabularBasicBivariateDistribution<void,void,void> );

//---------------------------------------------------------------------------//
// end Utility_InterpolatedTabularBasicBivariateDistributionImplBase.cpp
//---------------------------------------------------------------------------//
