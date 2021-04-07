//---------------------------------------------------------------------------//
//!
//! \file   Utility_CartesianDirectionalCoordinateConversionPolicy.hpp
//! \author Alex Robinson
//! \brief  Cartesian directional coordinate conversion policy declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_CARTESIAN_DIRECTIONAL_COORDINATE_CONVERSION_POLICY_HPP
#define UTILITY_CARTESIAN_DIRECTIONAL_COORDINATE_CONVERSION_POLICY_HPP

// FRENSIE Includes
#include "Utility_DirectionalCoordinateConversionPolicy.hpp"
#include "Utility_DirectionalCoordinateSystemTraits.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_DesignByContract.hpp"

namespace Utility{

//! The Cartesian directional coordinate conversion policy
class CartesianDirectionalCoordinateConversionPolicy : public DirectionalCoordinateConversionPolicy
{

protected:

  //! The local coordinate system traits
  typedef DirectionalCoordinateSystemTraits<CARTESIAN_DIRECTIONAL_COORDINATE_SYSTEM> LocalCSTraits;

public:

  //! Convert the Cartesian direction to Cartesian direction
  static void convertFromCartesianDirection(
                                           const double input_direction[3],
                                           double output_direction[3] );

  //! Convert the Cartesian direction to Cartesian direction
  static void convertFromCartesianDirection( const double input_x_direction,
                                             const double input_y_direction,
                                             const double input_z_direction,
                                             double& output_x_direction,
                                             double& outout_y_direction,
                                             double& output_z_direction );

  //! Convert the Cartesian direction to a Cartesian direction
  static void convertToCartesianDirection( const double input_direction[3],
                                           double output_direction[3] );

  //! Convert the Cartesian direction to a Cartesian direction
  static void convertToCartesianDirection( const double input_x_direction,
                                           const double input_y_direction,
                                           const double input_z_direction,
                                           double& output_x_direction,
                                           double& outout_y_direction,
                                           double& output_z_direction );


  //! Constructor
  CartesianDirectionalCoordinateConversionPolicy()
  { /* ... */ }

  //! Destructor
  virtual ~CartesianDirectionalCoordinateConversionPolicy()
  { /* ... */ }

  //! Get the local coordinate system type
  DirectionalCoordinateSystemType getLocalDirectionalCoordinateSystemType() const override;

  //! Check if the primary directional coordinate is valid
  bool isPrimaryDirectionalCoordinateValid( const double coordinate ) const override;

  //! Check if the secondary directional coordinate is valid
  bool isSecondaryDirectionalCoordinateValid( const double coordinate ) const override;

  //! Check if the tertiary directional coordinate is valid
  bool isTertiaryDirectionalCoordinateValid( const double coordinate ) const override;

  //! Normalize the local directional coordinates
  void normalizeLocalDirectionalCoordinates(
                           double& primary_directional_coord,
                           double& secondary_directional_coord,
                           double& tertiary_directional_coord ) const override;

private:

  // Save the policy to an archive
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  {
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( DirectionalCoordinateConversionPolicy );
  }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

//---------------------------------------------------------------------------//
// Inline Definitions
//---------------------------------------------------------------------------//

// Convert the Cartesian direction to Cartesian direction
/*! \details This method will simply copy the input direction to the output
 * direction. It can be used as the default policy method when no conversion
 * is required.
 */
inline void CartesianDirectionalCoordinateConversionPolicy::convertFromCartesianDirection(
                                           const double input_direction[3],
                                           double output_direction[3] )
{
  // Make sure that the input direction is valid
  testPrecondition( isUnitVector( input_direction ) );

  output_direction[0] = input_direction[0];
  output_direction[1] = input_direction[1];
  output_direction[2] = input_direction[2];
}

// Convert the Cartesian direction to Cartesian direction
/*! \details This method will simply copy the input direction to the output
 * direction. It can be used as the default policy method when no conversion
 * is required.
 */
inline void CartesianDirectionalCoordinateConversionPolicy::convertFromCartesianDirection(
                                                const double input_x_direction,
                                                const double input_y_direction,
                                                const double input_z_direction,
                                                double& output_x_direction,
                                                double& output_y_direction,
                                                double& output_z_direction )
{
  // Make sure that the input direction is valid
  testPrecondition( isUnitVector( input_x_direction, input_y_direction, input_z_direction ) );

  output_x_direction = input_x_direction;
  output_y_direction = input_y_direction;
  output_z_direction = input_z_direction;
}

// Convert the Cartesian direction to a Cartesian direction
/*! \details This method will simply copy the input direction to the output
 * direction. It can be used as the default policy method when no conversion
 * is required.
 */
inline void CartesianDirectionalCoordinateConversionPolicy::convertToCartesianDirection(
                                               const double input_direction[3],
                                               double output_direction[3] )
{
  // Make sure that the input direction is valid
  testPrecondition( isUnitVector( input_direction ) );

  output_direction[0] = input_direction[0];
  output_direction[1] = input_direction[1];
  output_direction[2] = input_direction[2];
}

// Convert the Cartesian direction to a Cartesian direction
/*! \details This method will simply copy the input direction to the output
 * direction. It can be used as the default policy method when no conversion
 * is required.
 */
inline void CartesianDirectionalCoordinateConversionPolicy::convertToCartesianDirection(
                                                const double input_x_direction,
                                                const double input_y_direction,
                                                const double input_z_direction,
                                                double& output_x_direction,
                                                double& output_y_direction,
                                                double& output_z_direction )
{
  // Make sure that the input direction is valid
  testPrecondition( isUnitVector( input_x_direction, input_y_direction, input_z_direction ) );

  output_x_direction = input_x_direction;
  output_y_direction = input_y_direction;
  output_z_direction = input_z_direction;
}

// Get the local coordinate system type
inline DirectionalCoordinateSystemType CartesianDirectionalCoordinateConversionPolicy::getLocalDirectionalCoordinateSystemType() const
{
  return CARTESIAN_DIRECTIONAL_COORDINATE_SYSTEM;
}

// Check if the primary directional coordinate is valid
inline bool CartesianDirectionalCoordinateConversionPolicy::isPrimaryDirectionalCoordinateValid(
                                                const double coordinate ) const
{
  return coordinate >= LocalCSTraits::primaryDirectionalDimensionLowerBound() &&
    coordinate <= LocalCSTraits::primaryDirectionalDimensionUpperBound();
}

// Check if the secondary directional coordinate is valid
inline bool CartesianDirectionalCoordinateConversionPolicy::isSecondaryDirectionalCoordinateValid(
                                                const double coordinate ) const
{
  return coordinate >= LocalCSTraits::secondaryDirectionalDimensionLowerBound() &&
    coordinate <= LocalCSTraits::secondaryDirectionalDimensionUpperBound();
}

// Check if the tertiary directional coordinate is valid
inline bool CartesianDirectionalCoordinateConversionPolicy::isTertiaryDirectionalCoordinateValid(
                                                const double coordinate ) const
{
  return coordinate >= LocalCSTraits::tertiaryDirectionalDimensionLowerBound() &&
    coordinate <= LocalCSTraits::tertiaryDirectionalDimensionUpperBound();
}

// Normalize the local directional coordinates
inline void CartesianDirectionalCoordinateConversionPolicy::normalizeLocalDirectionalCoordinates(
                                     double& primary_directional_coord,
                                     double& secondary_directional_coord,
                                     double& tertiary_directional_coord ) const
{
  normalizeVector( primary_directional_coord,
                   secondary_directional_coord,
                   tertiary_directional_coord );
}

} // end Utility namespace

BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS( CartesianDirectionalCoordinateConversionPolicy, Utility );
BOOST_SERIALIZATION_CLASS_VERSION( CartesianDirectionalCoordinateConversionPolicy, Utility, 0 );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( Utility, CartesianDirectionalCoordinateConversionPolicy );

#endif // end UTILITY_CARTESIAN_DIRECTIONAL_COORDINATE_CONVERSION_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_CartesianDirectionalCoordinateConversionPolicy.hpp
//---------------------------------------------------------------------------//
