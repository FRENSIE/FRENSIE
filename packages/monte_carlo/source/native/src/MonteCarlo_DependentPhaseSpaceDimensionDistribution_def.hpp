//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DependentPhaseSpaceDimensionDistribution_def.hpp
//! \author Alex Robinson
//! \brief  Dependent phase space dimension distribution class template def.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_DEF_HPP
#define MONTE_CARLO_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_DEF_HPP

// FRENSIE Includes
#include "MonteCarlo_PhaseSpaceDimensionTraits.hpp"

namespace MonteCarlo{

// Return the phase space dimension
template<PhaseSpaceDimension indep_dimension,PhaseSpaceDimension dep_dimension>
PhaseSpaceDimension DependentPhaseSpaceDimensionDistribution<indep_dimension,dep_dimension>::getDimension() const
{
  return dep_dimension;
}

// Return the phase space dimension class
template<PhaseSpaceDimension indep_dimension,PhaseSpaceDimension dep_dimension>
PhaseSpaceDimensionClass DependentPhaseSpaceDimensionDistribution<indep_dimension,dep_dimension>::getDimensionClass() const
{
  return PhaseSpaceDimensionTraits<dep_dimension>::getClass();
}

// Return the independent phase space dimension
template<PhaseSpaceDimension indep_dimension,PhaseSpaceDimension dep_dimension>
PhaseSpaceDimension DependentPhaseSpaceDimensionDistribution<indep_dimension,dep_dimension>::getIndepDimension() const
{
  return indep_dimension;
}

// Return the independent phase space dimension class
template<PhaseSpaceDimension indep_dimension,PhaseSpaceDimension dep_dimension>
PhaseSpaceDimensionClass DependentPhaseSpaceDimensionDistribution<indep_dimension,dep_dimension>::getIndepDimensionClass() const
{
  return PhaseSpaceDimensionTraits<indep_dimension>::getClass();
}

// Check if the dimension distribution is independent
template<PhaseSpaceDimension indep_dimension,PhaseSpaceDimension dep_dimension>
bool DependentPhaseSpaceDimensionDistribution<indep_dimension,dep_dimension>::isIndependent() const
{
  return false;
}

// Check if the dimension is dependent on the dimension of interest
template<PhaseSpaceDimension indep_dimension,PhaseSpaceDimension dep_dimension>
bool DependentPhaseSpaceDimensionDistribution<indep_dimension,dep_dimension>::isDependentOnDimension(
                                    const PhaseSpaceDimension dimension ) const
{
  return indep_dimension == dimension;
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DependentPhaseSpaceDimensionDistribution_def.hpp
//---------------------------------------------------------------------------//
