//---------------------------------------------------------------------------//
//!
//! \file   Utility_HistogramTabularBasicBivariateDistributionImplBase.cpp
//! \author Alex Robinson
//! \brief  The histogram tabular basic bivariate dist. helper class template
//!         explicit instantiation
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp" // Must include first
#include "Utility_HistogramTabularBasicBivariateDistributionImplBase.hpp"

EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareHistogramTabularBasicBivariateDistributionImplBase<Utility::UnitAwareFullyTabularBasicBivariateDistribution<void,void,void> > );
EXPLICIT_CLASS_SAVE_LOAD_INST( Utility::UnitAwareHistogramTabularBasicBivariateDistributionImplBase<Utility::UnitAwareFullyTabularBasicBivariateDistribution<void,void,void> > );

EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareHistogramTabularBasicBivariateDistributionImplBase<Utility::UnitAwarePartiallyTabularBasicBivariateDistribution<void,void,void> > );
EXPLICIT_CLASS_SAVE_LOAD_INST( Utility::UnitAwareHistogramTabularBasicBivariateDistributionImplBase<Utility::UnitAwarePartiallyTabularBasicBivariateDistribution<void,void,void> > );

//---------------------------------------------------------------------------//
// end Utility_HistogramTabularBasicBivariateDistributionImplBase.cpp
//---------------------------------------------------------------------------//

