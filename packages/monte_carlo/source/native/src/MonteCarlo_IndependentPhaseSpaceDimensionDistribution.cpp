//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_IndependentPhaseSpaceDimensionDistribution.cpp
//! \author Alex Robinson
//! \brief  Independent phase space dimension distribution class template
//!         instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_IndependentPhaseSpaceDimensionDistribution.hpp"

namespace MonteCarlo{

// Explicit instantiation
EXPLICIT_TEMPLATE_CLASS_INST( IndependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION> );
EXPLICIT_TEMPLATE_CLASS_INST( IndependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION> );
EXPLICIT_TEMPLATE_CLASS_INST( IndependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION> );
EXPLICIT_TEMPLATE_CLASS_INST( IndependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_TEMPLATE_CLASS_INST( IndependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_TEMPLATE_CLASS_INST( IndependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_TEMPLATE_CLASS_INST( IndependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION> );
EXPLICIT_TEMPLATE_CLASS_INST( IndependentPhaseSpaceDimensionDistribution<TIME_DIMENSION> );
EXPLICIT_TEMPLATE_CLASS_INST( IndependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_IndependentPhaseSpaceDimensionDistribution.cpp
//---------------------------------------------------------------------------//
