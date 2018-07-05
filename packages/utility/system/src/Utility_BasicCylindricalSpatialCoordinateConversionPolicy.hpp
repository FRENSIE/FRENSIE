//---------------------------------------------------------------------------//
//!
//! \file   Utility_BasicCylindricalSpatialCoordinateConversionPolicy.hpp
//! \author Alex Robinson
//! \brief  Basic cylindrical spatial coordinate conversion policy declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_BASIC_CYLINDRICAL_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP
#define UTILITY_BASIC_CYLINDRICAL_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP

// FRENSIE Includes
#include "Utility_CylindricalSpatialCoordinateConversionPolicy.hpp"

namespace Utility{

//! The basic cylindrical coordinate conversion policy class
class BasicCylindricalSpatialCoordinateConversionPolicy : public CylindricalSpatialCoordinateConversionPolicy
{

public:

  // Constructor
  BasicCylindricalSpatialCoordinateConversionPolicy()
  { /* ... */ }

  //! Destructor
  ~BasicCylindricalSpatialCoordinateConversionPolicy()
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

  //! Convert the spatial coordinates to cartesian coordinates
  using CylindricalSpatialCoordinateConversionPolicy::convertToCartesianSpatialCoordinates;

  //! Convert the cartesian coordinates to the spatial coordinate system
  using CylindricalSpatialCoordinateConversionPolicy::convertFromCartesianSpatialCoordinates;

private:

  // Save the policy to an archive
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  {
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( CylindricalSpatialCoordinateConversionPolicy );
  }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

} // end Utility namespace

BOOST_SERIALIZATION_CLASS_VERSION( BasicCylindricalSpatialCoordinateConversionPolicy, Utility, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( BasicCylindricalSpatialCoordinateConversionPolicy, Utility );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( Utility, BasicCylindricalSpatialCoordinateConversionPolicy );

#endif // end UTILITY_BASIC_CYLINDRICAL_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_BasicCylindricalSpatialCoordinateConversionPolicy.hpp
//---------------------------------------------------------------------------//
