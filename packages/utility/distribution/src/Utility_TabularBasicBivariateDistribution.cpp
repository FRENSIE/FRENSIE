//---------------------------------------------------------------------------//
//!
//! \file   Utility_TabularBasicBivariateDistribution.cpp
//! \author Alex Robinson
//! \brief  The tabular basic bivariate distribution class template inst.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp" // Must include first
#include "Utility_TabularBasicBivariateDistribution.hpp"

EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareTabularBasicBivariateDistribution<void,void,void,Utility::UnitAwareUnivariateDistribution> );
EXPLICIT_CLASS_SAVE_LOAD_INST( Utility::UnitAwareTabularBasicBivariateDistribution<void,void,void,Utility::UnitAwareUnivariateDistribution> );

EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareTabularBasicBivariateDistribution<void,void,void,Utility::UnitAwareTabularUnivariateDistribution> );
EXPLICIT_CLASS_SAVE_LOAD_INST( Utility::UnitAwareTabularBasicBivariateDistribution<void,void,void,Utility::UnitAwareTabularUnivariateDistribution> );

//---------------------------------------------------------------------------//
// end Utility_TabularBasicBivariateDistribution.cpp
//---------------------------------------------------------------------------//
