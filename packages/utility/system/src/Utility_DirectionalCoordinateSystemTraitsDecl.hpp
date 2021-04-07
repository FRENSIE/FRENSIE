//---------------------------------------------------------------------------//
//!
//! \file   Utility_DirectionalCoordinateSystemTraitsDecl.hpp
//! \author Alex Robinson
//! \brief  Directional coordinate system traits declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_DIRECTIONAL_COORDINATE_SYSTEM_TRAITS_DECL_HPP
#define UTILITY_DIRECTIONAL_COORDINATE_SYSTEM_TRAITS_DECL_HPP

// FRENSIE Includes
#include "Utility_DirectionalCoordinateSystemType.hpp"
#include "Utility_DirectionalDimensionType.hpp"

/*! \defgroup directional_coordinate_system_traits Directional Coordinate System Traits
 * \ingroup traits
 */

namespace Utility{

/*! Class used to prevent the default traits class from compiling
 * \ingroup directional_coordinate_system_traits
 */
template<typename T, DirectionalCoordinateSystemType coord_system>
struct UndefinedDirectionalCoordinateSystemTraits
{
  //! This function should not compile if there is any attempt to instantiate
  static inline void notDefined() { return T::desired_coordinate_system_is_missing_specialization(); }
};

/*! This class defines the properties of a directional coordinate system
 * \ingroup directional_coordinate_system_traits
 */
template<DirectionalCoordinateSystemType coord_system>
struct DirectionalCoordinateSystemTraits
{
  //! The primary spatial dimension
  static inline DirectionalDimensionType primaryDirectionalDimension()
  {
    (void)UndefinedDirectionalCoordinateSystemTraits<double,coord_system>::notDefined();
  }

  //! The lower bound of the primary spatial dimension
  static inline double primaryDirectionalDimensionLowerBound()
  {
    (void)UndefinedDirectionalCoordinateSystemTraits<double,coord_system>::notDefined();
  }

  //! The upper bound of the primary spatial dimension
  static inline double primaryDirectionalDimensionUpperBound()
  {
    (void)UndefinedDirectionalCoordinateSystemTraits<double,coord_system>::notDefined();
  }

  //! The secondary spatial dimension
  static inline DirectionalDimensionType secondaryDirectionalDimension()
  {
    (void)UndefinedDirectionalCoordinateSystemTraits<double,coord_system>::notDefined();
  }

  //! The lower bound of the secondary spatial dimension
  static inline double secondaryDirectionalDimensionLowerBound()
  {
    (void)UndefinedDirectionalCoordinateSystemTraits<double,coord_system>::notDefined();
  }

  //! The upper bound of the secondary spatial dimension
  static inline double secondaryDirectionalDimensionUpperBound()
  {
    (void)UndefinedDirectionalCoordinateSystemTraits<double,coord_system>::notDefined();
  }

  //! The tertiary spatial dimension
  static inline DirectionalDimensionType tertiaryDirectionalDimension()
  {
    (void)UndefinedDirectionalCoordinateSystemTraits<double,coord_system>::notDefined();
  }

  //! The lower bound of the tertiary spatial dimension
  static inline double tertiaryDirectionalDimensionLowerBound()
  {
    (void)UndefinedDirectionalCoordinateSystemTraits<double,coord_system>::notDefined();
  }

  //! The upper bound of the tertiary spatial dimension
  static inline double tertiaryDirectionalDimensionUpperBound()
  {
    (void)UndefinedDirectionalCoordinateSystemTraits<double,coord_system>::notDefined();
  }
};

} // end Utility namespace

#endif // end UTILITY_DIRECTIONAL_COORDINATE_SYSTEM_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end Utility_DirectionalCoordinateSystemTraitsDecl.hpp
//---------------------------------------------------------------------------//
