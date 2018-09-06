//---------------------------------------------------------------------------//
//!
//! \file   Utility_DirectionalCoordinateConversionPolicy.hpp
//! \author Alex Robinson
//! \brief  Directional coordinate conversion policy declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_DIRECTIONAL_COORDINATE_CONVERSION_POLICY_HPP
#define UTILITY_DIRECTIONAL_COORDINATE_CONVERSION_POLICY_HPP

// Boost Includes
#include <boost/serialization/split_member.hpp>

// FRENSIE Includes
#include "Utility_DirectionalCoordinateSystemType.hpp"
#include "Utility_DirectionalCoordinateSystemTraits.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_SerializationHelpers.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"

namespace Utility{

//! The directional coordinate conversion policy class
class DirectionalCoordinateConversionPolicy
{

protected:

  //! The global coordinate system traits
  typedef DirectionalCoordinateSystemTraits<CARTESIAN_DIRECTIONAL_COORDINATE_SYSTEM> GlobalCSTraits;

public:

  //! Constructor
  DirectionalCoordinateConversionPolicy()
  { /* ... */ }

  //! Destructor
  virtual ~DirectionalCoordinateConversionPolicy()
  { /* ... */ }

  //! Get the local coordinate system type
  virtual DirectionalCoordinateSystemType getLocalDirectionalCoordinateSystemType() const = 0;

  //! Check if the primary directional coordinate is valid
  virtual bool isPrimaryDirectionalCoordinateValid( const double coordinate ) const = 0;

  //! Check if the secondary directional coordinate is valid
  virtual bool isSecondaryDirectionalCoordinateValid( const double coordinate ) const = 0;

  //! Check if the tertiary directional coordinate is valid
  virtual bool isTertiaryDirectionalCoordinateValid( const double coordinate ) const = 0;

  //! Normalize the local directional coordinates
  virtual void normalizeLocalDirectionalCoordinates(
                                double& primary_directional_coord,
                                double& secondary_directional_coord,
                                double& tertiary_directional_coord ) const = 0;

  //! Normalize the local directional coordinates
  void normalizeLocalDirectionalCoordinates( double coordinates[3] ) const;

  //! Normalize the Cartesian directional coordinates
  void normalizeCartesianDirectionalCoordinates(
                                           double& x_directional_coord,
                                           double& y_directional_coord,
                                           double& z_directional_coord ) const;

  //! Normalize the Cartesian directional coordinates
  void normalizeCartesianDirectionalCoordinates( double coordinates[3] ) const;

  //! Convert the directional coordinates to Cartesian coordinates
  virtual void convertToCartesianDirectionalCoordinates(
                                      const double primary_directional_coord,
                                      const double secondary_directional_coord,
                                      const double tertiary_directional_coord,
                                      double& x_directional_coord,
                                      double& y_directional_coord,
                                      double& z_directional_coord ) const = 0;

  //! Convert the directional coordinates to Cartesian coordinates
  void convertToCartesianDirectionalCoordinates(
                                       const double coordinates[3],
                                       double cartesian_coordinates[3] ) const;

  //! Convert the cartesian coordinates to the directional coordinate system
  virtual void convertFromCartesianDirectionalCoordinates(
                                const double x_directional_coord,
                                const double y_directional_coord,
                                const double z_directional_coord,
                                double& primary_directional_coord,
                                double& secondary_directional_coord,
                                double& tertiary_directional_coord ) const = 0;

  //! Convert the cartesian coordinates to the directional coordinate system
  void convertFromCartesianDirectionalCoordinates(
                                         const double cartesian_coordinates[3],
                                         double coordinates[3] ) const;

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

// Normalize the local directional coordinates
inline void DirectionalCoordinateConversionPolicy::normalizeLocalDirectionalCoordinates(
                                                  double coordinates[3] ) const
{
  this->normalizeLocalDirectionalCoordinates( coordinates[0],
                                              coordinates[1],
                                              coordinates[2] );
}

// Normalize the Cartesian directional coordinates
inline void DirectionalCoordinateConversionPolicy::normalizeCartesianDirectionalCoordinates(
                                            double& x_directional_coord,
                                            double& y_directional_coord,
                                            double& z_directional_coord ) const
{
  normalizeVector( x_directional_coord,
                   y_directional_coord,
                   z_directional_coord );
}

// Normalize the Cartesian directional coordinates
inline void DirectionalCoordinateConversionPolicy::normalizeCartesianDirectionalCoordinates(
                                                  double coordinates[3] ) const
{
  this->normalizeCartesianDirectionalCoordinates( coordinates[0],
                                                  coordinates[1],
                                                  coordinates[2] );
}

// Convert the directional coordinates to cartesian coordinates
inline void DirectionalCoordinateConversionPolicy::convertToCartesianDirectionalCoordinates(
                                        const double coordinates[3],
                                        double cartesian_coordinates[3] ) const
{
  this->convertToCartesianDirectionalCoordinates( coordinates[0],
                                                  coordinates[1],
                                                  coordinates[2],
                                                  cartesian_coordinates[0],
                                                  cartesian_coordinates[1],
                                                  cartesian_coordinates[2] );
}

// Convert the cartesian coordinates to the directional coordinate system
inline void DirectionalCoordinateConversionPolicy::convertFromCartesianDirectionalCoordinates(
                                         const double cartesian_coordinates[3],
                                         double coordinates[3] ) const
{
  this->convertFromCartesianDirectionalCoordinates( cartesian_coordinates[0],
                                                    cartesian_coordinates[1],
                                                    cartesian_coordinates[2],
                                                    coordinates[0],
                                                    coordinates[1],
                                                    coordinates[2] );
}

} // end Utility namespace

BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS( DirectionalCoordinateConversionPolicy, Utility );
BOOST_SERIALIZATION_CLASS_VERSION( DirectionalCoordinateConversionPolicy, Utility, 0 );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( Utility, DirectionalCoordinateConversionPolicy );

#endif // end UTILITY_DIRECTIONAL_COORDINATE_CONVERSION_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_DirectionalCoordinateConversionPolicy.hpp
//---------------------------------------------------------------------------//
