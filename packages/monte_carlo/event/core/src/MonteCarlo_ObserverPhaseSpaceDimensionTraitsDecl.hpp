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
#include <type_traits>

// Boost Includes
#include <boost/any.hpp>

// FRENSIE Includes
#include "MonteCarlo_ObserverParticleStateWrapper.hpp"
#include "MonteCarlo_ObserverPhaseSpaceDimension.hpp"
#include "Utility_Tuple.hpp"

/*! \defgroup observer_phase_space_dim_traits Observer Phase Space Dimension Traits
 * \ingroup traits
 */

namespace MonteCarlo{

/*! The undefined observer phase space dimension traits
 * \ingroup observer_phase_space_dim_traits
 */
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

  //! Indicates that the dimension is ordered if true (ranges must be sorted)
  typedef std::true_type isOrdered;

  //! Indicates that the dimension is continuous if true
  typedef std::true_type isContinuous;

  //! The name of the dimension
  static inline std::string name()
  {
    (void)UndefinedObserverPhaseSpaceDimensionTraits<dimensionType,dimension>::notDefined();
    return std::string();
  }

  //! The name of the dimension (no white space)
  static inline std::string basicName()
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
  static inline const dimensionType& getDimensionValue(
                        const ObserverParticleStateWrapper& particle_wrapper )
  {
    (void)UndefinedObserverPhaseSpaceDimensionTraits<dimensionType,dimension>::notDefined();
    return 0;
  }

  //! Extract a value from an boost::any container
  static inline const dimensionType& getDimensionValue(
                                                  const boost::any& any_value )
  {
    (void)UndefinedObserverPhaseSpaceDimensionTraits<dimensionType,dimension>::notDefined();
    return 0;
  }

  //! Extract a value range from an estimator particle state wrapper
  static inline void getDimensionRange(
                         const ObserverParticleStateWrapper& particle_wrapper,
                         dimensionType& range_start,
                         dimensionType& range_end )
  {
    (void)UndefinedObserverPhaseSpaceDimensionTraits<dimensionType,dimension>::notDefined();
  }
};

/*! \brief This function allows access to the getDimensionValue 
 * ObserserPhaseSpaceDimension traits function
 * \ingrouop observer_phase_space_dim_traits
 */
template<ObserverPhaseSpaceDimension dimension>
inline typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType
getDimensionValue( const ObserverParticleStateWrapper& particle_wrapper )
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
getDimensionValue( const boost::any& any_value )
{
  return ObserverPhaseSpaceDimensionTraits<dimension>::getDimensionValue( any_value );
}

/*! \brief This function allows access to the getDimensionRange 
 * ObserverPhaseSpaceDimension traits function
 * \ingroup observer_phase_space_dim_traits
 */
template<ObserverPhaseSpaceDimension dimension>
inline void getDimensionRange(
      const ObserverParticleStateWrapper& particle_wrapper,
      typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType& range_start,
      typename ObserverPhaseSpaceDimensionTraits<dimension>::dimensionType& range_end )
{
  ObserverPhaseSpaceDimensionTraits<dimension>::getDimensionRange(
                                                              particle_wrapper,
                                                              range_start,
                                                              range_end );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_OBSERVER_PHASE_SPACE_DIMENSION_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ObserverPhaseSpaceDimensionTraits.hpp
//---------------------------------------------------------------------------//
