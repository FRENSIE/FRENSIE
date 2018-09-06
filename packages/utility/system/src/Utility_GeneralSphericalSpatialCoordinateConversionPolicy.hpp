//---------------------------------------------------------------------------//
//!
//! \file   Utility_GeneralSphericalSpatialCoordinateConversionPolicy.hpp
//! \author Alex Robinson
//! \brief  General spherical spatial coordinate conversion policy declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_GENERAL_SPHERICAL_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP
#define UTILITY_GENERAL_SPHERICAL_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP

// Boost Includes
#include <boost/serialization/array_wrapper.hpp>

// FRENSIE Includes
#include "Utility_SphericalSpatialCoordinateConversionPolicy.hpp"

namespace Utility{

//! The general spherical spatial coordinate conversion policy class
class GeneralSphericalSpatialCoordinateConversionPolicy : public SphericalSpatialCoordinateConversionPolicy
{

public:

  //! Constructor
  GeneralSphericalSpatialCoordinateConversionPolicy( const double origin[3],
                                                     const double axis[3] );

  //! Destructor
  ~GeneralSphericalSpatialCoordinateConversionPolicy()
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
  using SphericalSpatialCoordinateConversionPolicy::convertToCartesianSpatialCoordinates;

  //! Convert the cartesian coordinates to the spatial coordinate system
  using SphericalSpatialCoordinateConversionPolicy::convertFromCartesianSpatialCoordinates;

private:

  // The default constructor should not be used - if the axis and origin
  // correspond to the global coordinate system use the basic conversion
  // policy
  GeneralSphericalSpatialCoordinateConversionPolicy()
  { /* ... */ }

  // We have C-arrays as members - hide the copy constructor and assignment
  // operator
  GeneralSphericalSpatialCoordinateConversionPolicy( const GeneralSphericalSpatialCoordinateConversionPolicy& that );
  GeneralSphericalSpatialCoordinateConversionPolicy& operator=( const GeneralSphericalSpatialCoordinateConversionPolicy& that );

  // Save the policy to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the policy from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The origin of the spherical coordinate system w.r.t. the global Cartesian
  // coordinate system
  double d_origin[3];

  // The z-axis (unit vector) of the spherical coordinate system w.r.t. the
  // global Cartesian coordinate system
  double d_axis[3];
};

// Save the policy to an archive
template<typename Archive>
void GeneralSphericalSpatialCoordinateConversionPolicy::save( Archive& ar, const unsigned version ) const
{
  // Save the base class
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( SphericalSpatialCoordinateConversionPolicy );

  // Save the local data
  ar & boost::serialization::make_nvp( "d_origin", boost::serialization::make_array( d_origin, 3 ) );
  ar & boost::serialization::make_nvp( "d_axis", boost::serialization::make_array( d_axis, 3 ) );
}

// Load the policy from an archive
template<typename Archive>
void GeneralSphericalSpatialCoordinateConversionPolicy::load( Archive& ar, const unsigned version )
{
  // Load the base class
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( SphericalSpatialCoordinateConversionPolicy );

  // Load the local data
  ar & boost::serialization::make_nvp( "d_origin", boost::serialization::make_array( d_origin, 3 ) );
  ar & boost::serialization::make_nvp( "d_axis", boost::serialization::make_array( d_axis, 3 ) );
}

} // end Utility namespace

BOOST_SERIALIZATION_CLASS_VERSION( GeneralSphericalSpatialCoordinateConversionPolicy, Utility, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( GeneralSphericalSpatialCoordinateConversionPolicy, Utility );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Utility, GeneralSphericalSpatialCoordinateConversionPolicy );

#endif // end UTILITY_GENERAL_SPHERICAL_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_GeneralSphericalSpatialCoordinateConversionPolicy.hpp
//---------------------------------------------------------------------------//
