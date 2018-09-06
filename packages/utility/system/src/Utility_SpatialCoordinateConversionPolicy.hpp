//---------------------------------------------------------------------------//
//!
//! \file   Utility_SpatialCoordinateConversionPolicy.hpp
//! \author Alex Robinson
//! \brief  Spatial coordinate conversion policy declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP
#define UTILITY_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP

// Boost Includes
#include <boost/serialization/split_member.hpp>

// FRENSIE Includes
#include "Utility_SpatialCoordinateSystemType.hpp"
#include "Utility_SpatialCoordinateSystemTraits.hpp"
#include "Utility_SerializationHelpers.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"

namespace Utility{

//! The spatial coordinate conversion policy class
class SpatialCoordinateConversionPolicy
{

protected:

  //! The global coordinate system traits
  typedef SpatialCoordinateSystemTraits<CARTESIAN_SPATIAL_COORDINATE_SYSTEM> GlobalCSTraits;

public:

  //! Constructor
  SpatialCoordinateConversionPolicy()
  { /* ... */ }

  //! Destructor
  virtual ~SpatialCoordinateConversionPolicy()
  { /* ... */ }

  //! Get the local coordinate system type
  virtual SpatialCoordinateSystemType getLocalSpatialCoordinateSystemType() const = 0;

  //! Check if the primary spatial coordinate is valid
  virtual bool isPrimarySpatialCoordinateValid( const double coordinate ) const = 0;

  //! Check if the secondary spatial coordinate is valid
  virtual bool isSecondarySpatialCoordinateValid( const double coordinate ) const = 0;

  //! Check if the tertiary spatial coordinate is valid
  virtual bool isTertiarySpatialCoordinateValid( const double coordinate ) const = 0;

  //! Convert the spatial coordinates to cartesian coordinates
  virtual void convertToCartesianSpatialCoordinates(
                                          const double primary_spatial_coord,
                                          const double secondary_spatial_coord,
                                          const double tertiary_spatial_coord,
                                          double& x_spatial_coord,
                                          double& y_spatial_coord,
                                          double& z_spatial_coord ) const = 0;

  //! Convert the spatial coordinates to cartesian coordinates
  void convertToCartesianSpatialCoordinates(
                                       const double coordinates[3],
                                       double cartesian_coordinates[3] ) const;

  //! Convert the cartesian coordinates to the spatial coordinate system
  virtual void convertFromCartesianSpatialCoordinates(
                                    const double x_spatial_coord,
                                    const double y_spatial_coord,
                                    const double z_spatial_coord,
                                    double& primary_spatial_coord,
                                    double& secondary_spatial_coord,
                                    double& tertiary_spatial_coord ) const = 0;

  //! Convert the cartesian coordinates to the spatial coordinate system
  void convertFromCartesianSpatialCoordinates(
                                         const double cartesian_coordinates[3],
                                         double coordinates[3] ) const;

protected:

  //! Translate a global Cartesian position to a local Cartesian position
  static void translateGlobalCartesianPositionToLocalCartesianPosition(
                          const double global_x_position,
                          const double global_y_position,
                          const double global_z_position,
                          const double local_origin_wrt_global_coord_system[3],
                          double& local_x_position,
                          double& local_y_position,
                          double& local_z_position );

  //! Translate a local Cartesian position to a global Cartesian position
  static void translateLocalCartesianPositionToGlobalCartesianPosition(
                          const double local_x_position,
                          const double local_y_position,
                          const double local_z_position,
                          const double local_origin_wrt_global_coord_system[3],
                          double& global_x_position,
                          double& global_y_position,
                          double& global_z_position );

private:

  // Save the policy to an archive
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { /* ... */ }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

//---------------------------------------------------------------------------//
// Inline Definitions
//---------------------------------------------------------------------------//

// Convert the spatial coordinates to cartesian coordinates
inline void SpatialCoordinateConversionPolicy::convertToCartesianSpatialCoordinates(
                                        const double coordinates[3],
                                        double cartesian_coordinates[3] ) const
{
  this->convertToCartesianSpatialCoordinates( coordinates[0],
                                              coordinates[1],
                                              coordinates[2],
                                              cartesian_coordinates[0],
                                              cartesian_coordinates[1],
                                              cartesian_coordinates[2] );
}

// Convert the cartesian coordinates to the spatial coordinate system
inline void SpatialCoordinateConversionPolicy::convertFromCartesianSpatialCoordinates(
                                         const double cartesian_coordinates[3],
                                         double coordinates[3] ) const
{
  this->convertFromCartesianSpatialCoordinates( cartesian_coordinates[0],
                                                cartesian_coordinates[1],
                                                cartesian_coordinates[2],
                                                coordinates[0],
                                                coordinates[1],
                                                coordinates[2] );
}

// Translate a global Cartesian position to a local Cartesian position
inline void SpatialCoordinateConversionPolicy::translateGlobalCartesianPositionToLocalCartesianPosition(
                          const double global_x_position,
                          const double global_y_position,
                          const double global_z_position,
                          const double local_origin_wrt_global_coord_system[3],
                          double& local_x_position,
                          double& local_y_position,
                          double& local_z_position )
{
  local_x_position =
    global_x_position - local_origin_wrt_global_coord_system[0];

  local_y_position =
    global_y_position - local_origin_wrt_global_coord_system[1];

  local_z_position =
    global_z_position - local_origin_wrt_global_coord_system[2];
}

// Translate a local Cartesian position to a global Cartesian position
inline void SpatialCoordinateConversionPolicy::translateLocalCartesianPositionToGlobalCartesianPosition(
                          const double local_x_position,
                          const double local_y_position,
                          const double local_z_position,
                          const double local_origin_wrt_global_coord_system[3],
                          double& global_x_position,
                          double& global_y_position,
                          double& global_z_position )
{
  global_x_position =
    local_x_position + local_origin_wrt_global_coord_system[0];

  global_y_position =
    local_y_position + local_origin_wrt_global_coord_system[1];

  global_z_position =
    local_z_position + local_origin_wrt_global_coord_system[2];
}

} // end Utility namespace

BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS( SpatialCoordinateConversionPolicy, Utility )
BOOST_SERIALIZATION_CLASS_VERSION( SpatialCoordinateConversionPolicy, Utility, 0 );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( Utility, SpatialCoordinateConversionPolicy );

#endif // end UTILITY_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_SpatialCoordinateConversionPolicy.hpp
//---------------------------------------------------------------------------//
