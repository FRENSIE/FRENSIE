//---------------------------------------------------------------------------//
//!
//! \file   Utility_SpatialCoordinateSystemTraits.hpp
//! \author Alex Robinson
//! \brief  Spatial coordinate system traits class specializations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_SPATIAL_COORDINATE_SYSTEM_TRAITS_HPP
#define UTILITY_SPATIAL_COORDINATE_SYSTEM_TRAITS_HPP

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "Utility_SpatialCoordinateSystemTraitsDecl.hpp"
#include "Utility_PhysicalConstants.hpp"

namespace Utility{

/*! The specialization of the SpatialCoordinateSystemTraits for 
 * Utility::CARTESIAN_SPATIAL_COORDINATE_SYSTEM
 * \ingroup spatial_coordinate_system_traits
 */
template<>
struct SpatialCoordinateSystemTraits<CARTESIAN_SPATIAL_COORDINATE_SYSTEM>
{
  //! The primary spatial dimension
  static inline SpatialDimensionType primarySpatialDimension()
  { return X_SPATIAL_DIMENSION; }

  //! The lower bound of the primary spatial dimension
  static inline double primarySpatialDimensionLowerBound()
  { return -std::numeric_limits<double>::infinity(); }

  //! The upper bound of the primary spatial dimension
  static inline double primarySpatialDimensionUpperBound()
  { return std::numeric_limits<double>::infinity(); }

  //! The secondary spatial dimension
  static inline SpatialDimensionType secondarySpatialDimension()
  { return Y_SPATIAL_DIMENSION; }

  //! The lower bound of the secondary spatial dimension
  static inline double secondarySpatialDimensionLowerBound()
  { return -std::numeric_limits<double>::infinity(); }

  //! The upper bound of the secondary spatial dimension
  static inline double secondarySpatialDimensionUpperBound()
  { return std::numeric_limits<double>::infinity(); }

  //! The tertiary spatial dimension
  static inline SpatialDimensionType tertiarySpatialDimension()
  { return Z_SPATIAL_DIMENSION; }

  //! The lower bound of the tertiary spatial dimension
  static inline double tertiarySpatialDimensionLowerBound()
  { return -std::numeric_limits<double>::infinity(); }

  //! The upper bound of the tertiary spatial dimension
  static inline double tertiarySpatialDimensionUpperBound()
  { return std::numeric_limits<double>::infinity(); }
};

/*! The specialization of the SpatialCoordinateSystemTraits for 
 * Utility::CYLINDRICAL_SPATIAL_COORDINATE_SYSTEM
 * \ingroup spatial_coordinate_system_traits
 */
template<>
struct SpatialCoordinateSystemTraits<CYLINDRICAL_SPATIAL_COORDINATE_SYSTEM>
{
  //! The primary spatial dimension
  static inline SpatialDimensionType primarySpatialDimension()
  { return R_SPATIAL_DIMENSION; }

  //! The lower bound of the primary spatial dimension
  static inline double primarySpatialDimensionLowerBound()
  { return 0.0; }

  //! The upper bound of the primary spatial dimension
  static inline double primarySpatialDimensionUpperBound()
  { return std::numeric_limits<double>::infinity(); }

  //! The secondary spatial dimension
  static inline SpatialDimensionType secondarySpatialDimension()
  { return AZIMUTHAL_ANGLE_SPATIAL_DIMENSION; }

  //! The lower bound of the secondary spatial dimension
  static inline double secondarySpatialDimensionLowerBound()
  { return 0.0; }

  //! The upper bound of the secondary spatial dimension
  static inline double secondarySpatialDimensionUpperBound()
  { return 2*Utility::PhysicalConstants::pi; }

  //! The tertiary spatial dimension
  static inline SpatialDimensionType tertiarySpatialDimension()
  { return Z_SPATIAL_DIMENSION; }

  //! The lower bound of the tertiary spatial dimension
  static inline double tertiarySpatialDimensionLowerBound()
  { return -std::numeric_limits<double>::infinity(); }

  //! The upper bound of the tertiary spatial dimension
  static inline double tertiarySpatialDimensionUpperBound()
  { return std::numeric_limits<double>::infinity(); }
};

/*! The specialization of the SpatialCoordinateSystemTraits for 
 * Utility::SPHERICAL_SPATIAL_COORDINATE_SYSTEM
 * \ingroup spatial_coordinate_system_traits
 */
template<>
struct SpatialCoordinateSystemTraits<SPHERICAL_SPATIAL_COORDINATE_SYSTEM>
{
  //! The primary spatial dimension
  static inline SpatialDimensionType primarySpatialDimension()
  { return R_SPATIAL_DIMENSION; }

  //! The lower bound of the primary spatial dimension
  static inline double primarySpatialDimensionLowerBound()
  { return 0.0; }

  //! The upper bound of the primary spatial dimension
  static inline double primarySpatialDimensionUpperBound()
  { return std::numeric_limits<double>::infinity(); }

  //! The secondary spatial dimension
  static inline SpatialDimensionType secondarySpatialDimension()
  { return AZIMUTHAL_ANGLE_SPATIAL_DIMENSION; }

  //! The lower bound of the secondary spatial dimension
  static inline double secondarySpatialDimensionLowerBound()
  { return 0.0; }

  //! The upper bound of the secondary spatial dimension
  static inline double secondarySpatialDimensionUpperBound()
  { return 2*Utility::PhysicalConstants::pi; }

  //! The tertiary spatial dimension
  static inline SpatialDimensionType tertiarySpatialDimension()
  { return POLAR_ANGLE_COSINE_SPATIAL_DIMENSION; }

  //! The lower bound of the tertiary spatial dimension
  static inline double tertiarySpatialDimensionLowerBound()
  { return -1.0; }

  //! The upper bound of the tertiary spatial dimension
  static inline double tertiarySpatialDimensionUpperBound()
  { return 1.0; }
};
  
} // end Utility namespace

#endif // end UTILITY_SPATIAL_COORDINATE_SYSTEM_TRAITS_HPP

//---------------------------------------------------------------------------//
// end Utility_SpatialCoordinateSystemTraits.hpp
//---------------------------------------------------------------------------//
