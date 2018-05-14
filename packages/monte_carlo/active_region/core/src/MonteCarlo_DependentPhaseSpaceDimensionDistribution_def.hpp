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
template<PhaseSpaceDimension parent_dimension,PhaseSpaceDimension dimension>
PhaseSpaceDimension DependentPhaseSpaceDimensionDistribution<parent_dimension,dimension,typename std::enable_if<parent_dimension!=dimension>::type>::getDimension() const
{
  return dimension;
}

// Return the phase space dimension class
template<PhaseSpaceDimension parent_dimension,PhaseSpaceDimension dimension>
PhaseSpaceDimensionClass DependentPhaseSpaceDimensionDistribution<parent_dimension,dimension,typename std::enable_if<parent_dimension!=dimension>::type>::getDimensionClass() const
{
  return PhaseSpaceDimensionTraits<dimension>::getClass();
}

// Return the independent phase space dimension
template<PhaseSpaceDimension parent_dimension,PhaseSpaceDimension dimension>
PhaseSpaceDimension DependentPhaseSpaceDimensionDistribution<parent_dimension,dimension,typename std::enable_if<parent_dimension!=dimension>::type>::getParentDimension() const
{
  return parent_dimension;
}

// Return the independent phase space dimension class
template<PhaseSpaceDimension parent_dimension,PhaseSpaceDimension dimension>
PhaseSpaceDimensionClass DependentPhaseSpaceDimensionDistribution<parent_dimension,dimension,typename std::enable_if<parent_dimension!=dimension>::type>::getParentDimensionClass() const
{
  return PhaseSpaceDimensionTraits<parent_dimension>::getClass();
}

// Check if the dimension distribution is independent
template<PhaseSpaceDimension parent_dimension,PhaseSpaceDimension dimension>
bool DependentPhaseSpaceDimensionDistribution<parent_dimension,dimension,typename std::enable_if<parent_dimension!=dimension>::type>::isIndependent() const
{
  return false;
}

// Check if the dimension is dependent on the dimension of interest
template<PhaseSpaceDimension parent_dimension,PhaseSpaceDimension dimension>
bool DependentPhaseSpaceDimensionDistribution<parent_dimension,dimension,typename std::enable_if<parent_dimension!=dimension>::type>::isDependentOnDimension(
                              const PhaseSpaceDimension other_dimension ) const
{
  return parent_dimension == other_dimension;
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DependentPhaseSpaceDimensionDistribution_def.hpp
//---------------------------------------------------------------------------//
