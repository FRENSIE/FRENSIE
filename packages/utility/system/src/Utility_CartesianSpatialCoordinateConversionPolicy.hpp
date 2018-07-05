//---------------------------------------------------------------------------//
//!
//! \file   Utility_CartesianSpatialCoordinateConversionPolicy.hpp
//! \author Alex Robinson
//! \brief  Cartesian spatial coordinate conversion policy declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_CARTESIAN_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP
#define UTILITY_CARTESIAN_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP

// FRENSIE Includes
#include "Utility_SpatialCoordinateConversionPolicy.hpp"
#include "Utility_SpatialCoordinateSystemTraits.hpp"

namespace Utility{

//! The Cartesian spatial coordinate conversion policy
class CartesianSpatialCoordinateConversionPolicy : public SpatialCoordinateConversionPolicy
{

protected:

  //! The local coordinate system traits
  typedef SpatialCoordinateSystemTraits<CARTESIAN_SPATIAL_COORDINATE_SYSTEM> LocalCSTraits;

public:

  //! Convert the Cartesian coordinates to Cartesian coordinates
  static void convertFromCartesianPosition( const double input_coords[3],
                                            double output_coords[3] );

  //! Convert the Cartesian coordinates to Cartesian coordinates
  static void convertFromCartesianPosition( const double input_x_spatial_coord,
                                            const double input_y_spatial_coord,
                                            const double input_z_spatial_coord,
                                            double& output_x_spatial_coord,
                                            double& output_y_spatial_coord,
                                            double& output_z_spatial_coord );

  //! Convert the Cartesian coordinates to Cartesian coordinates
  static void convertToCartesianPosition( const double input_coords[3],
                                          double output_coords[3] );

  //! Convert the Cartesian coordinates to Cartesian coordinates
  static void convertToCartesianPosition( const double input_x_spatial_coord,
                                          const double input_y_spatial_coord,
                                          const double input_z_spatial_coord,
                                          double& output_x_spatial_coord,
                                          double& output_y_spatial_coord,
                                          double& output_z_spatial_coord );

  //! Constructor
  CartesianSpatialCoordinateConversionPolicy()
  { /* ... */ }

  //! Destructor
  virtual ~CartesianSpatialCoordinateConversionPolicy()
  { /* ... */ }

  //! Get the local coordinate system type
  SpatialCoordinateSystemType getLocalSpatialCoordinateSystemType() const override;

  //! Check if the primary spatial coordinate is valid
  bool isPrimarySpatialCoordinateValid( const double coordinate ) const override;

  //! Check if the secondary spatial coordinate is valid
  bool isSecondarySpatialCoordinateValid( const double coordinate ) const override;

  //! Check if the tertiary spatial coordinate is valid
  bool isTertiarySpatialCoordinateValid( const double coordinate ) const override;

private:

  // Save the policy to an archive
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  {
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( SpatialCoordinateConversionPolicy );
  }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

//---------------------------------------------------------------------------//
// Inline Definitions
//---------------------------------------------------------------------------//

// Convert the Cartesian coordinates to Cartesian coordinates
/*! \details This method will simply copy the input coordinates to the output
 * coordinates. It can be used as the default policy method when no conversion
 * is required.
 */
inline void CartesianSpatialCoordinateConversionPolicy::convertFromCartesianPosition(
                                                  const double input_coords[3],
                                                  double output_coords[3] )
{
  output_coords[0] = input_coords[0];
  output_coords[1] = input_coords[1];
  output_coords[2] = input_coords[2];
}

// Convert the Cartesian coordinates to Cartesian coordinates
/*! \details This method will simply copy the input coordinates to the output
 * coordinates. It can be used as the default policy method when no conversion
 * is required.
 */
inline void CartesianSpatialCoordinateConversionPolicy::convertFromCartesianPosition(
                                            const double input_x_spatial_coord,
                                            const double input_y_spatial_coord,
                                            const double input_z_spatial_coord,
                                            double& output_x_spatial_coord,
                                            double& output_y_spatial_coord,
                                            double& output_z_spatial_coord )
{
  output_x_spatial_coord = input_x_spatial_coord;
  output_y_spatial_coord = input_y_spatial_coord;
  output_z_spatial_coord = input_z_spatial_coord;
}

// Convert the Cartesian coordinates to Cartesian coordinates
/*! \details This method will simply copy the input coordinates to the output
 * coordinates. It can be used as the default policy method when no conversion
 * is required.
 */
inline void CartesianSpatialCoordinateConversionPolicy::convertToCartesianPosition(
                                                  const double input_coords[3],
                                                  double output_coords[3] )
{
  output_coords[0] = input_coords[0];
  output_coords[1] = input_coords[1];
  output_coords[2] = input_coords[2];
}

// Convert the Cartesian coordinates to Cartesian coordinates
/*! \details This method will simply copy the input coordinates to the output
 * coordinates. It can be used as the default policy method when no conversion
 * is required.
 */
inline void CartesianSpatialCoordinateConversionPolicy::convertToCartesianPosition(
                                          const double input_x_spatial_coord,
                                          const double input_y_spatial_coord,
                                          const double input_z_spatial_coord,
                                          double& output_x_spatial_coord,
                                          double& output_y_spatial_coord,
                                          double& output_z_spatial_coord )
{
  output_x_spatial_coord = input_x_spatial_coord;
  output_y_spatial_coord = input_y_spatial_coord;
  output_z_spatial_coord = input_z_spatial_coord;
}

// Get the local coordinate system type
inline SpatialCoordinateSystemType CartesianSpatialCoordinateConversionPolicy::getLocalSpatialCoordinateSystemType() const
{
  return CARTESIAN_SPATIAL_COORDINATE_SYSTEM;
}

// Check if the primary spatial coordinate is valid
inline bool CartesianSpatialCoordinateConversionPolicy::isPrimarySpatialCoordinateValid(
                                                const double coordinate ) const
{
  return coordinate >= LocalCSTraits::primarySpatialDimensionLowerBound() &&
    coordinate <= LocalCSTraits::primarySpatialDimensionUpperBound();
}

// Check if the secondary spatial coordinate is valid
inline bool CartesianSpatialCoordinateConversionPolicy::isSecondarySpatialCoordinateValid(
                                                const double coordinate ) const
{
  return coordinate >= LocalCSTraits::secondarySpatialDimensionLowerBound() &&
    coordinate <= LocalCSTraits::secondarySpatialDimensionUpperBound();
}

// Check if the tertiary spatial coordinate is valid
inline bool CartesianSpatialCoordinateConversionPolicy::isTertiarySpatialCoordinateValid(
                                                const double coordinate ) const
{
  return coordinate >= LocalCSTraits::tertiarySpatialDimensionLowerBound() &&
    coordinate <= LocalCSTraits::tertiarySpatialDimensionUpperBound();
}

} // end Utility namespace

BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS( CartesianSpatialCoordinateConversionPolicy, Utility );
BOOST_SERIALIZATION_CLASS_VERSION( CartesianSpatialCoordinateConversionPolicy, Utility, 0 );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( Utility, CartesianSpatialCoordinateConversionPolicy );

#endif // end UTILITY_CARTESIAN_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_CartesianSpatialCoordinateConversionPolicy.hpp
//---------------------------------------------------------------------------//
