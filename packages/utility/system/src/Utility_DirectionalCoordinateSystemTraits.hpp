//---------------------------------------------------------------------------//
//!
//! \file   Utility_DirectionalCoordinateSystemTraits.hpp
//! \author Alex Robinson
//! \brief  Directional coordinate system traits class specializations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_DIRECTIONAL_COORDINATE_SYSTEM_TRAITS_HPP
#define UTILITY_DIRECTIONAL_COORDINATE_SYSTEM_TRAITS_HPP

// FRENSIE Includes
#include "Utility_DirectionalCoordinateSystemTraitsDecl.hpp"
#include "Utility_PhysicalConstants.hpp"

namespace Utility{

/*! The specialization of the DirectionalCoordinateSystemTraits for 
 * Utility::CARTESIAN_DIRECTIONAL_COORDINATE_SYSTEM
 * \ingroup directional_coordinate_system_traits
 */
template<>
struct DirectionalCoordinateSystemTraits<CARTESIAN_DIRECTIONAL_COORDINATE_SYSTEM>
{
  //! The primary directional dimension
  static inline DirectionalDimensionType primaryDirectionalDimension()
  { return U_DIRECTIONAL_DIMENSION; }

  //! The lower bound of the primary directional dimension
  static inline double primaryDirectionalDimensionLowerBound()
  { return -1.0; }

  //! The upper bound of the primary directional dimension
  static inline double primaryDirectionalDimensionUpperBound()
  { return 1.0; }

  //! The secondary directional dimension
  static inline DirectionalDimensionType secondaryDirectionalDimension()
  { return V_DIRECTIONAL_DIMENSION; }

  //! The lower bound of the secondary directional dimension
  static inline double secondaryDirectionalDimensionLowerBound()
  { return -1.0; }

  //! The upper bound of the secondary directional dimension
  static inline double secondaryDirectionalDimensionUpperBound()
  { return 1.0; }

  //! The tertiary directional dimension
  static inline DirectionalDimensionType tertiaryDirectionalDimension()
  { return W_DIRECTIONAL_DIMENSION; }

  //! The lower bound of the tertiary directional dimension
  static inline double tertiaryDirectionalDimensionLowerBound()
  { return -1.0; }

  //! The upper bound of the tertiary directional dimension
  static inline double tertiaryDirectionalDimensionUpperBound()
  { return 1.0; }
};

/*! The specialization of the DirectionalCoordinateSystemTraits for 
 * Utility::SPHERICAL_DIRECTIONAL_COORDINATE_SYSTEM
 * \ingroup directional_coordinate_system_traits
 */
template<>
struct DirectionalCoordinateSystemTraits<SPHERICAL_DIRECTIONAL_COORDINATE_SYSTEM>
{
  //! The primary directional dimension
  static inline DirectionalDimensionType primaryDirectionalDimension()
  { return R_DIRECTIONAL_DIMENSION; }

  //! The lower bound of the primary directional dimension
  static inline double primaryDirectionalDimensionLowerBound()
  { return 1.0; }

  //! The upper bound of the primary directional dimension
  static inline double primaryDirectionalDimensionUpperBound()
  { return 1.0; }

  //! The secondary directional dimension
  static inline DirectionalDimensionType secondaryDirectionalDimension()
  { return AZIMUTHAL_ANGLE_DIRECTIONAL_DIMENSION; }

  //! The lower bound of the secondary directional dimension
  static inline double secondaryDirectionalDimensionLowerBound()
  { return 0.0; }

  //! The upper bound of the secondary directional dimension
  static inline double secondaryDirectionalDimensionUpperBound()
  { return 2*PhysicalConstants::pi; }

  //! The tertiary directional dimension
  static inline DirectionalDimensionType tertiaryDirectionalDimension()
  { return POLAR_ANGLE_COSINE_DIRECTIONAL_DIMENSION; }

  //! The lower bound of the tertiary directional dimension
  static inline double tertiaryDirectionalDimensionLowerBound()
  { return -1.0; }

  //! The upper bound of the tertiary directional dimension
  static inline double tertiaryDirectionalDimensionUpperBound()
  { return 1.0; }
};
  
} // end Utility namespace

#endif // end UTILITY_DIRECTIONAL_COORDINATE_SYSTEM_TRAITS_HPP

//---------------------------------------------------------------------------//
// end Utility_DirectionalCoordinateSystemTraits.hpp
//---------------------------------------------------------------------------//
