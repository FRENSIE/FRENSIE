//---------------------------------------------------------------------------//
//!
//! \file   Utility_TranslationCylindricalSpatialCoordinateConversionPolicy.hpp
//! \author Alex Robinson
//! \brief  Translation cylindrical spatial coordinate conversion policy decl.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TRANSLATION_CYLINDRICAL_COORDINATE_CONVERSION_POLICY_HPP
#define UTILITY_TRANSLATION_CYLINDRICAL_COORDINATE_CONVERSION_POLICY_HPP

// FRENSIE Includes
#include "Utility_CylindricalSpatialCoordinateConversionPolicy.hpp"

namespace Utility{

//! The translation cylindrical coordinate conversion policy class
class TranslationCylindricalSpatialCoordinateConversionPolicy : public CylindricalSpatialCoordinateConversionPolicy
{

public:

  //! Constructor
  TranslationCylindricalSpatialCoordinateConversionPolicy(
                                                      const double origin[3] );

  //! Destructor
  ~TranslationCylindricalSpatialCoordinateConversionPolicy()
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
  TranslationCylindricalSpatialCoordinateConversionPolicy();

  // We have C-arrays as members - hide the copy constructor and assignment
  // operator
  TranslationCylindricalSpatialCoordinateConversionPolicy( const TranslationCylindricalSpatialCoordinateConversionPolicy& that );
  TranslationCylindricalSpatialCoordinateConversionPolicy& operator=( const TranslationCylindricalSpatialCoordinateConversionPolicy& that );

  // The origin of the local cylindrical coordinate system w.r.t. the global
  // Cartesian coordinate system
  double d_origin[3];
};
  
} // end Utility namespace

#endif // end UTILITY_TRANSLATION_CYLINDRICAL_COORDINATE_CONVERSION_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_TranslationCylindricalSpatialCoordinateConversionPolicy.hpp
//---------------------------------------------------------------------------//

