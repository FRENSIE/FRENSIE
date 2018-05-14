//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ImportanceSampledIndependentPhaseSpaceDimensionDistribution.cpp
//! \author Alex Robinson
//! \brief  Importance sampled independent phase space dimension distribution
//!         class template instantiations
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ImportanceSampledIndependentPhaseSpaceDimensionDistribution.hpp"

namespace MonteCarlo{

// Explicit instantiation 
EXPLICIT_TEMPLATE_CLASS_INST( ImportanceSampledIndependentPhaseSpaceDimensionDistribution<PRIMARY_SPATIAL_DIMENSION> );
EXPLICIT_TEMPLATE_CLASS_INST( ImportanceSampledIndependentPhaseSpaceDimensionDistribution<SECONDARY_SPATIAL_DIMENSION> );
EXPLICIT_TEMPLATE_CLASS_INST( ImportanceSampledIndependentPhaseSpaceDimensionDistribution<TERTIARY_SPATIAL_DIMENSION> );
EXPLICIT_TEMPLATE_CLASS_INST( ImportanceSampledIndependentPhaseSpaceDimensionDistribution<PRIMARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_TEMPLATE_CLASS_INST( ImportanceSampledIndependentPhaseSpaceDimensionDistribution<SECONDARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_TEMPLATE_CLASS_INST( ImportanceSampledIndependentPhaseSpaceDimensionDistribution<TERTIARY_DIRECTIONAL_DIMENSION> );
EXPLICIT_TEMPLATE_CLASS_INST( ImportanceSampledIndependentPhaseSpaceDimensionDistribution<ENERGY_DIMENSION> );
EXPLICIT_TEMPLATE_CLASS_INST( ImportanceSampledIndependentPhaseSpaceDimensionDistribution<TIME_DIMENSION> );
EXPLICIT_TEMPLATE_CLASS_INST( ImportanceSampledIndependentPhaseSpaceDimensionDistribution<WEIGHT_DIMENSION> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ImportanceSampledIndependentPhaseSpaceDimensionDistribution.cpp
//---------------------------------------------------------------------------//
