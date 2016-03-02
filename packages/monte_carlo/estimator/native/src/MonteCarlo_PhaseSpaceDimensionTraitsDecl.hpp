//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhaseSpaceDimensionTraits.hpp
//! \author Alex Robinson
//! \brief  Phase space dimension traits class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHASE_SPACE_DIMENSION_TRAITS_DECL_HPP
#define MONTE_CARLO_PHASE_SPACE_DIMENSION_TRAITS_DECL_HPP

// Std Lib Includes
#include <string>

// Boost Includes
#include <boost/unordered_map.hpp>

// Trilinos Includes
#include <Teuchos_any.hpp>

// FRENSIE Includes
#include "MonteCarlo_EstimatorParticleStateWrapper.hpp"
#include "MonteCarlo_PhaseSpaceDimension.hpp"
#include "Utility_Tuple.hpp"

/*! \defgroup phase_space_dim_traits Phase Space Dimension Traits
 * \ingroup traits
 */

namespace MonteCarlo{

template<typename DimensionType, PhaseSpaceDimension dimension>
struct UndefinedPhaseSpaceDimensionTraits
{
  //! This function should not compile if there is any attempt to instantiate
  static inline void notDefined() { return DimensionType::desired_dimension_is_misssing_specialization(); }
};

/*! This structure defines the properties of a phase space dimension.
 * \ingroup phase_space_dim_traits
 */
template<PhaseSpaceDimension dimension>
struct PhaseSpaceDimensionTraits
{
  //! The value type associated with the dimension
  typedef double dimensionType;

  //! The name of the dimension
  static inline std::string name()
  { 
    (void)UndefinedPhaseSpaceDimensionTraits<dimensionType,dimension>::notDefined();
    return std::string();
  }

  //! The lower bound of the dimension
  static inline dimensionType lowerBound()
  {
    (void)UndefinedPhaseSpaceDimensionTraits<dimensionType,dimension>::notDefined();
    return 0;
  }

  //! The upper bound of the dimension
  static inline dimensionType upperBound()
  {
    (void)UndefinedPhaseSpaceDimensionTraits<dimensionType,dimension>::notDefined();
    return 0;
  }

  //! Extract a value from an estimator particle state wrapper
  static inline const dimensionType& getDimensionValue( const EstimatorParticleStateWrapper& particle_wrapper )
  {
    (void)UndefinedPhaseSpaceDimensionTraits<dimensionType,dimension>::notDefined();
    return 0;
  }

  //! Extract a value from an Teuchos::any container
  static inline const dimensionType& getDimensionValue( const Teuchos::any& any_value )
  {
    (void)UndefinedPhaseSpaceDimensionTraits<dimensionType,dimension>::notDefined();
    return 0;
  }
};

/*! This function allows access to the getDimensionValue PhaseSpaceDimension
 * traits function
 * \ingrouop phase_space_dim_traits
 */
template<PhaseSpaceDimension dimension>
inline typename PhaseSpaceDimensionTraits<dimension>::dimensionType 
getDimensionValue( const EstimatorParticleStateWrapper& particle_wrapper )
{
  return PhaseSpaceDimensionTraits<dimension>::getDimensionValue( 
                                                            particle_wrapper );
}

/*! This function allows access to the getDimensionvalue PhaseSpaceDimension
 * traits function
 * \ingroup phase_space_dim_traits
 */
template<PhaseSpaceDimension dimension>
inline typename PhaseSpaceDimensionTraits<dimension>::dimensionType
getDimensionValue( const Teuchos::any& any_value )
{
  return PhaseSpaceDimensionTraits<dimension>::getDimensionValue( any_value );
}
								    
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHASE_SPACE_DIMENSION_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhaseSpaceDimensionTraits.hpp
//---------------------------------------------------------------------------//
