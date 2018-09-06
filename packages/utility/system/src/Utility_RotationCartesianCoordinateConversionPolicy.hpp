//---------------------------------------------------------------------------//
//!
//! \file   Utility_RotationCartesianCoordinateConversionPolicy.hpp
//! \author Alex Robinson
//! \brief  Rotation Cartesian coordinate conversion policy declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ROTATION_CARTESIAN_COORDINATE_CONVERSION_POLICY_HPP
#define UTILITY_ROTATION_CARTESIAN_COORDINATE_CONVERSION_POLICY_HPP

// Boost Includes
#include <boost/serialization/array_wrapper.hpp>

// FRENSIE Includes
#include "Utility_CartesianSpatialCoordinateConversionPolicy.hpp"
#include "Utility_CartesianDirectionalCoordinateConversionPolicy.hpp"

namespace Utility{

//! The rotation Cartesian coordinate conversion policy class
class RotationCartesianCoordinateConversionPolicy : public CartesianSpatialCoordinateConversionPolicy,
                                                    public CartesianDirectionalCoordinateConversionPolicy
{

public:

  //! Constructor
  RotationCartesianCoordinateConversionPolicy( const double axis[3] );

  //! Destructor
  ~RotationCartesianCoordinateConversionPolicy()
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

  //! Convert the directional coordinates to cartesian coordinates
  void convertToCartesianDirectionalCoordinates(
                                  const double primary_directional_coord,
                                  const double secondary_directional_coord,
                                  const double tertiary_directional_coord,
                                  double& x_directional_coord,
                                  double& y_directional_coord,
                                  double& z_directional_coord ) const override;

  //! Convert the cartesian coordinates to the directional coordinate system
  void convertFromCartesianDirectionalCoordinates(
                           const double x_directional_coord,
                           const double y_directional_coord,
                           const double z_directional_coord,
                           double& primary_directional_coord,
                           double& secondary_directional_coord,
                           double& tertiary_directional_coord ) const override;

  //! Convert the spatial coordinates to cartesian coordinates
  using CartesianSpatialCoordinateConversionPolicy::convertToCartesianSpatialCoordinates;

  //! Convert the cartesian coordinates to the spatial coordinate system
  using CartesianSpatialCoordinateConversionPolicy::convertFromCartesianSpatialCoordinates;

  //! Convert the directional coordinates to cartesian coordinates
  using CartesianDirectionalCoordinateConversionPolicy::convertToCartesianDirectionalCoordinates;

  //! Convert the cartesian coordinates to the directional coordinate system
  using CartesianDirectionalCoordinateConversionPolicy::convertFromCartesianDirectionalCoordinates;

private:

  // The default constructor should not be used - if the z-axis of the local
  // coordinate system w.r.t. the global coordinate system aligns with the
  // z-axis of the global coordinate system use the basic conversion policy
  RotationCartesianCoordinateConversionPolicy()
  { /* ... */ }

  // We have C-arrays as members - hide the copy constructor and assignment
  // operator
  RotationCartesianCoordinateConversionPolicy( const RotationCartesianCoordinateConversionPolicy& that );
  RotationCartesianCoordinateConversionPolicy& operator=( const RotationCartesianCoordinateConversionPolicy& that );

  // Save the policy to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the policy from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The z-axis (unit vector) of the local Cartesian coordinate system w.r.t.
  // the global Cartesian coordinate system
  double d_axis[3];
};

// Save the policy to an archive
template<typename Archive>
void RotationCartesianCoordinateConversionPolicy::save( Archive& ar, const unsigned version ) const
{
  // Save the base classes
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( CartesianSpatialCoordinateConversionPolicy );
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( CartesianDirectionalCoordinateConversionPolicy );

  // Save the local data
  ar & boost::serialization::make_nvp( "d_axis", boost::serialization::make_array( d_axis, 3 ) );
}

// Load the policy from an archive
template<typename Archive>
void RotationCartesianCoordinateConversionPolicy::load( Archive& ar, const unsigned version )
{
  // Load the base class
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( CartesianSpatialCoordinateConversionPolicy );
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( CartesianDirectionalCoordinateConversionPolicy );

  // Load the local data
  ar & boost::serialization::make_nvp( "d_axis", boost::serialization::make_array( d_axis, 3 ) );
}

} // end Utility namespace

BOOST_SERIALIZATION_CLASS_VERSION( RotationCartesianCoordinateConversionPolicy, Utility, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( RotationCartesianCoordinateConversionPolicy, Utility );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Utility, RotationCartesianCoordinateConversionPolicy );

#endif // end UTILITY_ROTATION_CARTESIAN_COORDINATE_CONVERSION_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_RotationCartesianCoordinateConversionPolicy.hpp
//---------------------------------------------------------------------------//
