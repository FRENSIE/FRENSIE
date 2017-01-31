//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DefaultTypedObserverPhaseSpaceDimensionDiscretizationDecl.hpp
//! \author Alex Robinson
//! \brief  General estimator dimension discretization class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DEFAULT_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_DECL_HPP
#define MONTE_CARLO_DEFAULT_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_DECL_HPP

// FRENSIE Includes
#include "MonteCarlo_ObserverPhaseSpaceDimension.hpp"

namespace MonteCarlo{

/*! \brief The default typed observer phase space dimension discretization 
 * class
 *
 * If the dimension is not compatible with the floating point ordered,
 * integral ordered or unordered discretization treatments provided then
 * a specialization of this class for the dimension must be made. The layout
 * that has been given for this class should be used for all specializations.
 * Note that specializations of this class are only meant to provide a 
 * convenient and homogenized interface for creating dimension discretizations.
 */
template<ObserverPhaseSpaceDimension dimension, typename Enabled = void>
class DefaultTypedObserverPhaseSpaceDimensionDiscretization
{ 

public:

  //! Typedef for the dimension value type
  typedef void DimensionValueType;

  //! Typedef for the input data type
  typedef void InputDataType;

  //! Constructor
  DefaultTypedObserverPhaseSpaceDimensionDiscretization(
                                    const InputDataType& discretization_data );

  //! Destructor
  ~DefaultTypedObserverPhaseSpaceDimensionDiscretization();
};
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_DEFAULT_TYPED_OBSERVER_PHASE_SPACE_DIMENSION_DISCRETIZATION_DECL_HPP

//---------------------------------------------------------------------------//
// MonteCarlo_DefaultTypedObserverPhaseSpaceDimensionDiscretizationDecl.hpp
//---------------------------------------------------------------------------//
