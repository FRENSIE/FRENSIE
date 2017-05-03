//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ImportanceSampledPartiallyTabularDependentPhaseSpaceDimensionDistribution.hpp
//! \author Alex Robinson
//! \brief  Importance sampled partially-tabular dependent phase space dimension
//!         distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_IMPORTANCE_SAMPLED_PARTIALLY_TABULAR_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_HPP
#define MONTE_CARLO_IMPORTANCE_SAMPLED_PARTIALLY_TABULAR_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_StandardImportanceSampledDependentPhaseSpaceDimensionDistribution.hpp"
#include "Utility_PartiallyTabularTwoDDistribution.hpp"

namespace MonteCarlo{

//! The importance sampled partially-tabular dependent phase space dimension dist.
template<PhaseSpaceDimension parent_dimension,PhaseSpaceDimension dimension> using ImportanceSampledPartiallyTabularDependentPhaseSpaceDimensionDistribution =
  StandardImportanceSampledDependentPhaseSpaceDimensionDistribution<parent_dimension,dimension,Utility::PartiallyTabularTwoDDistribution>;
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_IMPORTANCE_SAMPLED_PARTIALLY_TABULAR_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ImportanceSampledPartiallyTabularDependentPhaseSpaceDimensionDistribution.hpp
//---------------------------------------------------------------------------//
