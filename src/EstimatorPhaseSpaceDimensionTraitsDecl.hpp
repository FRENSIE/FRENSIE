//---------------------------------------------------------------------------//
//!
//! \file   EstimatorPhaseSpaceDimensionTraits.hpp
//! \author Alex Robinson
//! \brief  Estimator phase space dimension traits class declaration
//!
//---------------------------------------------------------------------------//

#ifndef ESTIMATOR_PHASE_SPACE_DIMENSION_TRAITS_DECL_HPP
#define ESTIMATOR_PHASE_SPACE_DIMENSION_TRAITS_DECL_HPP

// Std Lib Includes
#include <string>

// Trilinos Includes
#include <Teuchos_any.hpp>

// FACEMC Includes
#include "EstimatorPhaseSpaceDimension.hpp"
#include "Tuple.hpp"

/*! \defgroup estimator_phase_space_dim_traits Estimator Phase Space Dimension
 * Traits
 */

namespace FACEMC{

namespace Traits{

template<typename DimensionType, EstimatorPhaseSpaceDimension dimension>
struct UndefinedEstimatorPhaseSpaceDimensionTraits
{
  //! This function should not compile if there is any attempt to instantiate
  static inline void notDefined() { return DimensionType::desired_dimension_is_misssing_specialization(); }
};

/*! This structure defines the properties of an estimator phase space 
 * dimension.
 *
 * \ingroup estimator_phase_space_dim_traits
 */
template<EstimatorPhaseSpaceDimension dimension>
struct EstimatorPhaseSpaceDimensionTraits
{
  //! The value type associated with the dimension
  typedef double dimensionType;

  //! The name of the dimension
  static inline std::string name()
  { 
    (void)UndefinedEstimatorPhaseSpaceDimensionTraits<dimensionType,dimension>::notDefined();
    return std::string();
  }

  //! Extract a value from a Teuchos::any object associated with the dimension
  static inline dimensionType& getValue( Teuchos::any& any_container )
  {
    (void)UndefinedEstimatorPhaseSpaceDimensionTraits<dimensionType,dimension>::notDefined();
    return 0;
  }

  //! Extract a value from a Teuchos::any object associated with the dimension
  static inline const dimensionType& getValue( const Teuchos::any& any_container )
  {
    (void)UndefinedEstimatorPhaseSpaceDimensionTraits<dimensionType,dimension>::notDefined();
    return 0;
  }
};

} // end Traits namespace

/*! This function allows access to the getValue 
 * EstimatorPhaseSpaceDimensionTraits function.
 *
 * This function is simply a more concise way to access the get static member
 * function associated with the EstimatorPhaseSpaceDimensionTraits class.
 * \ingroup estimator_phase_space_dim_traits
 */
template<EstimatorPhaseSpaceDimension dimension>
inline 
typename Traits::EstimatorPhaseSpaceDimensionTraits<dimension>::dimensionType&
getValue( Teuchos::any& dimension_value )
{ return Traits::EstimatorPhaseSpaceDimensionTraits<dimension>::getValue( dimension_value ); }

/*! This function allows access to the getValue 
 * EstimatorPhaseSpaceDimensionTraits function.
 *
 * This function is simply a more concise way to access the get static member
 * function associated with the EstimatorPhaseSpaceDimensionTraits class.
 * \ingroup estimator_phase_space_dim_traits
 */
template<EstimatorPhaseSpaceDimension dimension>
inline const 
typename Traits::EstimatorPhaseSpaceDimensionTraits<dimension>::dimensionType&
getValue( const Teuchos::any& dimension_value )
{ return Traits::EstimatorPhaseSpaceDimensionTraits<dimension>::getValue( dimension_value ); }

} // end FACEMC namespace

#endif // end ESTIMATOR_PHASE_SPACE_DIMENSION_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end EstimatorPhaseSpaceDimensionTraits.hpp
//---------------------------------------------------------------------------//
