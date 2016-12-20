//---------------------------------------------------------------------------//
//!
//! \file   Utility_TranslationSphericalSpatialCoordinateConversionPolicy.hpp
//! \author Alex Robinson
//! \brief  Translation spherical spatial coordinate conversion policy decl.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TRANSLATION_SPHERICAL_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP
#define UTILITY_TRANSLATION_SPHERICAL_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP

// FRENSIE Includes
#include "Utility_SphericalSpatialCoordinateConversionPolicy.hpp"

namespace Utility{

//! The translation spherical coordinate conversion policy class
class TranslationSphericalSpatialCoordinateConversionPolicy : public SphericalSpatialCoordinateConversionPolicy
{

public:

  //! Constructor
  TranslationSphericalSpatialCoordinateConversionPolicy(
                                                      const double origin[3] );

  //! Destructor
  ~TranslationSphericalSpatialCoordinateConversionPolicy()
  { /* ... */ }

  //! Convert the spatial coordinates to cartesian coordinates
  void convertToCartesianSpatialCoordinates(
                                      const double primary_spatial_coord,
                                      const double secondary_spatial_coord,
                                      const double tertiary_spatial_coord,
                                      double& x_spatial_coord,
                                      double& y_spatial_coord,
                                      double& z_spatial_coord ) const override;

  //! Convert the cartesian coordinates to the spatial coordinate system
  void convertFromCartesianSpatialCoordinates(
                               const double x_spatial_coord,
                               const double y_spatial_coord,
                               const double z_spatial_coord,
                               double& primary_spatial_coord,
                               double& secondary_spatial_coord,
                               double& tertiary_spatial_coord ) const override;

private:

  // The default constructor should not be used - if the origin corresponds to
  // the global coordinate system (0,0,0) use the basic conversion policy
  TranslationSphericalSpatialCoordinateConversionPolicy();

  // We have C-arrays as members - hide the copy constructor and assignment
  // operator
  TranslationSphericalSpatialCoordinateConversionPolicy( const TranslationSphericalSpatialCoordinateConversionPolicy& that );
  TranslationSphericalSpatialCoordinateConversionPolicy& operator=( const TranslationSphericalSpatialCoordinateConversionPolicy& that );

  // The origin of the local spherical coordinate system w.r.t. the global
  // Cartesian coordinate system
  double d_origin[3];
};
  
} // end Utility namespace

#endif // end UTILITY_TRANSLATION_SPHERICAL_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_TranslationSphericalSpatialCoordinateConversionPolicy.hpp
//---------------------------------------------------------------------------//
