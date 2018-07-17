//---------------------------------------------------------------------------//
//!
//! \file   Utility_TabularDistribution.cpp
//! \author Alex Robinson
//! \brief  The tabular distribution class template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp" // Must include first
#include "Utility_TabularDistribution.hpp"

EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareTabularDistribution<Utility::LinLin,void,void> );
EXPLICIT_CLASS_SAVE_LOAD_INST( Utility::UnitAwareTabularDistribution<Utility::LinLin,void,void> );

EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareTabularDistribution<Utility::LinLog,void,void> );
EXPLICIT_CLASS_SAVE_LOAD_INST( Utility::UnitAwareTabularDistribution<Utility::LinLog,void,void> );

EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareTabularDistribution<Utility::LogLin,void,void> );
EXPLICIT_CLASS_SAVE_LOAD_INST( Utility::UnitAwareTabularDistribution<Utility::LogLin,void,void> );

EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareTabularDistribution<Utility::LogLog,void,void> );
EXPLICIT_CLASS_SAVE_LOAD_INST( Utility::UnitAwareTabularDistribution<Utility::LogLog,void,void> );

//---------------------------------------------------------------------------//
// end Utility_TabularDistribution.cpp
//---------------------------------------------------------------------------//
