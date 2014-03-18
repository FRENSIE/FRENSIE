//---------------------------------------------------------------------------//
//!
//! \file   PhaseSpaceDimensionTraits.hpp
//! \author Alex Robinson
//! \brief  Phase space dimension traits class declaration
//!
//---------------------------------------------------------------------------//

#ifndef PHASE_SPACE_DIMENSION_TRAITS_DECL_HPP
#define PHASE_SPACE_DIMENSION_TRAITS_DECL_HPP

// Std Lib Includes
#include <string>

// Trilinos Includes
#include <Teuchos_any.hpp>

// FACEMC Includes
#include "PhaseSpaceDimension.hpp"
#include "Tuple.hpp"

/*! \defgroup phase_space_dim_traits Phase Space Dimension Traits
 * \ingroup traits
 */

namespace FACEMC{

namespace Traits{

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

  //! Extract a value from a Teuchos::any object associated with the dimension
  static inline dimensionType& getValue( Teuchos::any& any_container )
  {
    (void)UndefinedPhaseSpaceDimensionTraits<dimensionType,dimension>::notDefined();
    return 0;
  }

  //! Extract a value from a Teuchos::any object associated with the dimension
  static inline const dimensionType& getValue( const Teuchos::any& any_container )
  {
    (void)UndefinedPhaseSpaceDimensionTraits<dimensionType,dimension>::notDefined();
    return 0;
  }
};

} // end Traits namespace

/*! This function allows access to the getValue PhaseSpaceDimensionTraits 
 * function.
 *
 * This function is simply a more concise way to access the get static member
 * function associated with the PhaseSpaceDimensionTraits class.
 * \ingroup phase_space_dim_traits
 */
template<PhaseSpaceDimension dimension>
inline 
typename Traits::PhaseSpaceDimensionTraits<dimension>::dimensionType&
getValue( Teuchos::any& dimension_value )
{ 
  return Traits::PhaseSpaceDimensionTraits<dimension>::getValue( 
							     dimension_value );
}

/*! This function allows access to the getValue PhaseSpaceDimensionTraits 
 * function.
 *
 * This function is simply a more concise way to access the get static member
 * function associated with the PhaseSpaceDimensionTraits class.
 * \ingroup phase_space_dim_traits
 */
template<PhaseSpaceDimension dimension>
inline const 
typename Traits::PhaseSpaceDimensionTraits<dimension>::dimensionType&
getValue( const Teuchos::any& dimension_value )
{ 
  return Traits::PhaseSpaceDimensionTraits<dimension>::getValue( 
							     dimension_value );
}

} // end FACEMC namespace

#endif // end PHASE_SPACE_DIMENSION_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end PhaseSpaceDimensionTraits.hpp
//---------------------------------------------------------------------------//
