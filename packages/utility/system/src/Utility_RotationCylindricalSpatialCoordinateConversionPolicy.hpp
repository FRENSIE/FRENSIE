//---------------------------------------------------------------------------//
//!
//! \file   Utility_RotationCylindricalSpatialCoordinateConversionPolicy.hpp
//! \author Alex Robinson
//! \brief  Rotation cylindrical spatial coordinate conversion policy decl.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ROTATION_CYLINDRICAL_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP
#define UTILITY_ROTATION_CYLINDRICAL_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP

// Boost Includes
#include <boost/serialization/array_wrapper.hpp>

// FRENSIE Includes
#include "Utility_CylindricalSpatialCoordinateConversionPolicy.hpp"

namespace Utility{

//! The rotation cylindrical spatial coordinate conversion policy class
class RotationCylindricalSpatialCoordinateConversionPolicy : public CylindricalSpatialCoordinateConversionPolicy
{

public:

  //! Constructor
  RotationCylindricalSpatialCoordinateConversionPolicy( const double axis[3] );

  //! Destructor
  ~RotationCylindricalSpatialCoordinateConversionPolicy()
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

  // The default constructor should not be used - if the z-axis of the local
  // coordinate system w.r.t. the global Cartesian coordinate system aligns
  // with the z-axis of the Cartesian coordinate system use the basic
  // conversion policy
  RotationCylindricalSpatialCoordinateConversionPolicy()
  { /* ... */ }

  // We have C-arrays as members - hide the copy constructor and assignment
  // operator
  RotationCylindricalSpatialCoordinateConversionPolicy( const RotationCylindricalSpatialCoordinateConversionPolicy& that );
  RotationCylindricalSpatialCoordinateConversionPolicy& operator=( const RotationCylindricalSpatialCoordinateConversionPolicy& that );

  // Save the policy to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the policy from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The z-axis (unit vector) of the local cylindrical coordinate system w.r.t.
  // the global Cartesian coordinate system
  double d_axis[3];
};

// Save the policy to an archive
template<typename Archive>
void RotationCylindricalSpatialCoordinateConversionPolicy::save( Archive& ar, const unsigned version ) const
{
  // Save the base class
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( CylindricalSpatialCoordinateConversionPolicy );

  // Save the local data
  ar & boost::serialization::make_nvp( "d_axis", boost::serialization::make_array( d_axis, 3 ) );
}

// Load the policy from an archive
template<typename Archive>
void RotationCylindricalSpatialCoordinateConversionPolicy::load( Archive& ar, const unsigned version )
{
  // Load the base class
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( CylindricalSpatialCoordinateConversionPolicy );

  // Load the local data
  ar & boost::serialization::make_nvp( "d_axis", boost::serialization::make_array( d_axis, 3 ) );
}

} // end Utility namespace

BOOST_SERIALIZATION_CLASS_VERSION( RotationCylindricalSpatialCoordinateConversionPolicy, Utility, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( RotationCylindricalSpatialCoordinateConversionPolicy, Utility );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Utility, RotationCylindricalSpatialCoordinateConversionPolicy );

#endif // end UTILITY_ROTATION_CYLINDRICAL_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_RotationCylindricalSpatialCoordinateConversionPolicy.hpp
//---------------------------------------------------------------------------//
