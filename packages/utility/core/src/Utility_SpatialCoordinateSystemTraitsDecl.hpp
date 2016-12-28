//---------------------------------------------------------------------------//
//!
//! \file   Utility_SpatialCoordinateSystemTraitsDecl.hpp
//! \author Alex Robinson
//! \brief  Spatial coordinate system traits declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_SPATIAL_COORDINATE_SYSTEM_TRAITS_DECL_HPP
#define UTILITY_SPATIAL_COORDINATE_SYSTEM_TRAITS_DECL_HPP

// FRENSIE Includes
#include "Utility_SpatialCoordinateSystemType.hpp"
#include "Utility_SpatialDimensionType.hpp"

/*! \defgroup spatial_coordinate_system_traits Spatial Coordinate System Traits
 * \ingroup traits
 */

namespace Utility{

/*! Class used to prevent the default traits class from compiling
 * \ingroup spatial_coordinate_system_traits
 */
template<typename T, SpatialCoordinateSystemType coord_system>
struct UndefinedSpatialCoordinateSystemTraits
{
  //! This function should not compile if there is any attempt to instantiate
  static inline void notDefined() { return T::desired_coordinate_system_is_missing_specialization(); }
};

/*! This class defines the properties of a spatial coordinate system
 * \ingroup spatial_coordinate_system_traits
 */
template<SpatialCoordinateSystemType coord_system>
struct SpatialCoordinateSystemTraits
{
  //! The primary spatial dimension
  static inline SpatialDimensionType primarySpatialDimension()
  {
    (void)UndefinedSpatialCoordinateSystemTraits<double,coord_system>::notDefined();
  }

  //! The lower bound of the primary spatial dimension
  static inline double primarySpatialDimensionLowerBound()
  {
    (void)UndefinedSpatialCoordinateSystemTraits<double,coord_system>::notDefined();
  }

  //! The upper bound of the primary spatial dimension
  static inline double primarySpatialDimensionUpperBound()
  {
    (void)UndefinedSpatialCoordinateSystemTraits<double,coord_system>::notDefined();
  }

  //! The secondary spatial dimension
  static inline SpatialDimensionType secondarySpatialDimension()
  {
    (void)UndefinedSpatialCoordinateSystemTraits<double,coord_system>::notDefined();
  }

  //! The lower bound of the secondary spatial dimension
  static inline double secondarySpatialDimensionLowerBound()
  {
    (void)UndefinedSpatialCoordinateSystemTraits<double,coord_system>::notDefined();
  }

  //! The upper bound of the secondary spatial dimension
  static inline double secondarySpatialDimensionUpperBound()
  {
    (void)UndefinedSpatialCoordinateSystemTraits<double,coord_system>::notDefined();
  }

  //! The tertiary spatial dimension
  static inline SpatialDimensionType tertiarySpatialDimension()
  {
    (void)UndefinedSpatialCoordinateSystemTraits<double,coord_system>::notDefined();
  }

  //! The lower bound of the tertiary spatial dimension
  static inline double tertiarySpatialDimensionLowerBound()
  {
    (void)UndefinedSpatialCoordinateSystemTraits<double,coord_system>::notDefined();
  }

  //! The upper bound of the tertiary spatial dimension
  static inline double tertiarySpatialDimensionUpperBound()
  {
    (void)UndefinedSpatialCoordinateSystemTraits<double,coord_system>::notDefined();
  }
};
  
} // end Utility namespace

#endif // end UTILITY_SPATIAL_COORDINATE_SYSTEM_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end Utility_SpatialCoordinateSystemTraitsDecl.hpp
//---------------------------------------------------------------------------//
