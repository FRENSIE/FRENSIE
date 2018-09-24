//---------------------------------------------------------------------------//
//!
//! \file   Utility_TabularCDFDistribution.cpp
//! \author Luke Kersting
//! \brief  The tabular CDF distribution class template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp" // Must include first
#include "Utility_TabularCDFDistribution.hpp"

EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareTabularCDFDistribution<Utility::LinLin,void,void> );
EXPLICIT_CLASS_SAVE_LOAD_INST( Utility::UnitAwareTabularCDFDistribution<Utility::LinLin,void,void> );

EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareTabularCDFDistribution<Utility::LogLog,void,void> );
EXPLICIT_CLASS_SAVE_LOAD_INST( Utility::UnitAwareTabularCDFDistribution<Utility::LogLog,void,void> );

EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareTabularCDFDistribution<Utility::LinLog,void,void> );
EXPLICIT_CLASS_SAVE_LOAD_INST( Utility::UnitAwareTabularCDFDistribution<Utility::LinLog,void,void> );

EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareTabularCDFDistribution<Utility::LogLin,void,void> );
EXPLICIT_CLASS_SAVE_LOAD_INST( Utility::UnitAwareTabularCDFDistribution<Utility::LogLin,void,void> );

// Explicit cosine instantiation
EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareTabularCDFDistribution<Utility::LogLogCos,void,void> );
EXPLICIT_CLASS_SAVE_LOAD_INST( Utility::UnitAwareTabularCDFDistribution<Utility::LogLogCos,void,void> );

EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareTabularCDFDistribution<Utility::LinLogCos,void,void> );
EXPLICIT_CLASS_SAVE_LOAD_INST( Utility::UnitAwareTabularCDFDistribution<Utility::LinLogCos,void,void> );

EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareTabularCDFDistribution<Utility::LogNudgedLogCos,void,void> );
EXPLICIT_CLASS_SAVE_LOAD_INST( Utility::UnitAwareTabularCDFDistribution<Utility::LogNudgedLogCos,void,void> );

EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareTabularCDFDistribution<Utility::LinNudgedLogCos,void,void> );
EXPLICIT_CLASS_SAVE_LOAD_INST( Utility::UnitAwareTabularCDFDistribution<Utility::LinNudgedLogCos,void,void> );

//---------------------------------------------------------------------------//
// end Utility_TabularCDFDistribution.cpp
//---------------------------------------------------------------------------//
