//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ImportanceSampledFullyTabularDependentPhaseSpaceDimensionDistribution.hpp
//! \author Alex Robinson
//! \brief  Importance sampled fully-tabular dependent phase space dimension
//!         distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_IMPORTANCE_SAMPLED_FULLY_TABULAR_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_HPP
#define MONTE_CARLO_IMPORTANCE_SAMPLED_FULLY_TABULAR_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_StandardImportanceSampledDependentPhaseSpaceDimensionDistribution.hpp"
#include "Utility_FullyTabularTwoDDistribution.hpp"

namespace MonteCarlo{

//! The importance sampled fully-tabular dependent phase space dimension dist.
template<PhaseSpaceDimension parent_dimension,PhaseSpaceDimension dimension> using ImportanceSampledFullyTabularDependentPhaseSpaceDimensionDistribution =
  StandardImportanceSampledDependentPhaseSpaceDimensionDistribution<parent_dimension,dimension,Utility::FullyTabularTwoDDistribution>;
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_IMPORTANCE_SAMPLED_FULLY_TABULAR_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ImportanceSampledFullyTabularDependentPhaseSpaceDimensionDistribution.hpp
//---------------------------------------------------------------------------//

