//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PartiallyTabularDependentPhaseSpaceDimensionDistribution.hpp
//! \author Alex Robinson
//! \brief  Partially tabular depedent phase space dimension dist. class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTIALLY_TABULAR_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_HPP
#define MONTE_CARLO_PARTIALLY_TABULAR_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_StandardDependentPhaseSpaceDimensionDistribution.hpp"
#include "Utility_PartiallyTabularTwoDDistribution.hpp"

namespace MonteCarlo{

//! The fully-tabular dependent phase space dimension distribution
template<PhaseSpaceDimension parent_dimension,PhaseSpaceDimension dimension> using PartiallyTabularDependentPhaseSpaceDimensionDistribution =
  StandardDependentPhaseSpaceDimensionDistribution<parent_dimension,dimension,Utility::PartiallyTabularTwoDDistribution>;
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTIALLY_TABULAR_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PartiallyTabularDependentPhaseSpaceDimensionDistribution.hpp
//---------------------------------------------------------------------------//
