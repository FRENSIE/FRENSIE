//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ObserverPhaseSpaceDimensionTraits.hpp
//! \author Alex Robinson
//! \brief  Observer phase space dimension traits class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_OBSERVER_PHASE_SPACE_DIMENSION_TRAITS_DECL_HPP
#define MONTE_CARLO_OBSERVER_PHASE_SPACE_DIMENSION_TRAITS_DECL_HPP

// Std Lib Includes
#include <string>

// Boost Includes
#include <boost/unordered_map.hpp>

// Trilinos Includes
#include <Teuchos_any.hpp>

// FRENSIE Includes
#include "MonteCarlo_EstimatorParticleStateWrapper.hpp"
#include "MonteCarlo_ObserverPhaseSpaceDimension.hpp"
#include "Utility_Tuple.hpp"

/*! \defgroup observer_phase_space_dim_traits Observer Phase Space Dimension Traits
 * \ingroup traits
 */

namespace MonteCarlo{

template<typename DimensionType, ObserverPhaseSpaceDimension dimension>
struct UndefinedObserverPhaseSpaceDimensionTraits
{
  //! This function should not compile if there is any attempt to instantiate
  static inline void notDefined() { return DimensionType::desired_dimension_is_missing_specialization(); }
};

/*! This structure defines the properties of an observer phase space dimension.
 * \ingroup observer_phase_space_dim_traits
 */
template<ObserverPhaseSpaceDimension dimension>
struct ObserverPhaseSpaceDimensionTraits
{
  //! The value type associated with the dimension
  typedef double dimensionType;

  //! The value associated with a bin of the dimension
  typedef double dimensionBinType;

  //! The name of the dimension
  static inline std::string name()
  {
    (void)UndefinedObserverPhaseSpaceDimensionTraits<dimensionType,dimension>::notDefined();
    return std::string();
  }

  //! The lower bound of the dimension
  static inline dimensionType lowerBound()
  {
    (void)UndefinedObserverPhaseSpaceDimensionTraits<dimensionType,dimension>::notDefined();
    return 0;
  }

  //! The upper bound of the dimension
  static inline dimensionType upperBound()
  {
    (void)UndefinedObserverPhaseSpaceDimensionTraits<dimensionType,dimension>::notDefined();
    return 0;
  }

  //! Extract a value from an estimator particle state wrapper
  static inline const dimensionType& getDimensionValue( const EstimatorParticleStateWrapper& particle_wrapper )
  {
    (void)UndefinedObserverPhaseSpaceDimensionTraits<dimensionType,dimension>::notDefined();
    return 0;
  }

  //! Extract a value from an Teuchos::any container
  static inline const dimensionType& getDimensionValue( const Teuchos::any& any_value )
  {
    (void)UndefinedObserverPhaseSpaceDimensionTraits<dimensionType,dimension>::notDefined();
    return 0;
  }
};

/*! This function allows access to the getDimensionValue ObserserPhaseSpaceDimension
 * traits function
 * \ingrouop observer_phase_space_dim_traits
 */
template<ObserverPhaseSpaceDimension dimension>
inline typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType
getDimensionValue( const EstimatorParticleStateWrapper& particle_wrapper )
{
  return ObserverPhaseSpaceDimensionTraits<dimension>::getDimensionValue(
                                                            particle_wrapper );
}

/*! This function allows access to the getDimensionvalue ObserverPhaseSpaceDimension
 * traits function
 * \ingroup observer_phase_space_dim_traits
 */
template<ObserverPhaseSpaceDimension dimension>
inline typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType
getDimensionValue( const Teuchos::any& any_value )
{
  return ObserverPhaseSpaceDimensionTraits<dimension>::getDimensionValue( any_value );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_OBSERVER_PHASE_SPACE_DIMENSION_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ObserverPhaseSpaceDimensionTraits.hpp
//---------------------------------------------------------------------------//
