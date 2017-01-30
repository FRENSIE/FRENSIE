//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_GeneralEstimatorDimensionDiscretizationHelper.hpp
//! \author Alex Robinson
//! \brief  General estimator dimension discretization helper class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_GENERAL_ESTIMATOR_DIMENSION_DISCRETIZATION_HELPER_HPP
#define MONTE_CARLO_GENERAL_ESTIMATOR_DIMENSION_DISCRETIZATION_HELPER_HPP

// FRENSIE Includes
#include "MonteCarlo_StandardOrderedEstimatorDimensionDiscretization.hpp"
#include "MonteCarlo_UnorderedEstimatorDimensionDiscretization.hpp"
#include "MonteCarlo_ObserverPhaseSpaceDimensionTraits.hpp"

namespace MonteCarlo{

//! The general estimator dimension discretization helper base class
template<PhaseSpaceDimension dimension,bool is_ordered>
struct GeneralEstimatorDimensionDiscretizationHelperBase
{
  //! The base class distribution that should be inherited from
  typedef BaseEstimatorDimensionDiscretization StandardOrderedEstimatorDimensionDiscretization<typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType>;

  //! The input array type
  typedef typename BaseEstimatorDimensionDiscretization::BinBoundaryArray InputArray;

  //! Check if the input array bounds are valid
  bool areInputArrayBoundsValid( const InputArray& input_array )
  {
    return input_array.front() >= ObserverPhaseSpaceDimensionTraits<dimension>::lowerBound() &&
      input_array.back() <= ObserverPhaseSpaceDimensionTraits<dimension>::upperBound();
  }
};

//! The general estimator dimension discretization helper base class
template<PhaseSpaceDimension dimension>
struct GeneralEstimatorDimensionDiscretizationHelperBase<dimension,false>
{
  //! The base class distribution that should be inherited from
  typedef BaseEstimatorDimensionDiscretization UnorderedEstimatorDimensionDiscretization<typename PhaseSpaceDimensionTraits<dimension>::dimensionType>;

  //! The input array type
  typedef typename BaseEstimatorDimensionDiscretization::BinSetArray InputArray;

  //! Check if the input array bounds are valid
  bool areInputArrayBoundsValid( const InputArray& input_array )
  {
    return true;
  }
};

/*! The general estimator dimension discretization helper class
 * \details This class is used by the general estimator dimension 
 * discretization to select the correct base class.
 */
template<PhaseSpaceDimension dimension>
struct GeneralEstimatorDimensionDiscretizationHelper : public GeneralEstimatorDimensionDiscretizationHelperBase<dimension,ObserverPhaseSpaceDimensionTraits<dimension>::is_ordered>{};
  
} // end MonteCarlo namespace

#define MONTE_CARLO_GENERAL_ESTIMATOR_DIMENSION_DISCRETIZATION_HELPER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_GeneralEstimatorDimensionDiscretizationHelper.hpp
//---------------------------------------------------------------------------//
