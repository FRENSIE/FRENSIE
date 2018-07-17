//---------------------------------------------------------------------------//
//!
//! \file   Utility_HistogramDistribution.cpp
//! \author Alex Robinson
//! \brief  The histogram distribution class template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "Utility_HistogramDistribution.hpp"

EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareHistogramDistribution<void,void> );
EXPLICIT_CLASS_SAVE_LOAD_INST( Utility::UnitAwareHistogramDistribution<void,void> );

//---------------------------------------------------------------------------//
// end Utility_HistogramDistribution.cpp
//---------------------------------------------------------------------------//
