//---------------------------------------------------------------------------//
//!
//! \file   Utility_DirectionalCoordinateConversionPolicy.hpp
//! \author Alex Robinson
//! \brief  Directional coordinate conversion policy declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_DIRECTIONAL_COORDINATE_CONVERSION_POLICY_HPP
#define UTILITY_DIRECTIONAL_COORDINATE_CONVERSION_POLICY_HPP

namespace Utility{

//! The directional coordinate conversion policy class
class DirectionalCoordinateConversionPolicy
{

public:

  //! Constructor
  DirectionalCoordinateConversionPolicy()
  { /* ... */ }

  //! Destructor
  virtual ~DirectionalCoordinateConversionPolicy()
  { /* ... */ }

  //! Convert the directional coordinates to cartesian coordinates
  virtual void convertToCartesianDirectionalCoordinates(
                                      const double primary_directional_coord,
                                      const double secondary_directional_coord,
                                      const double tertiary_directional_coord,
                                      double& x_directional_coord,
                                      double& y_directional_coord,
                                      double& z_directional_coord ) const = 0;

  //! Convert the directional coordinates to cartesian coordinates
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
};

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
};
  
} // end Utility namespace

#endif // end UTILITY_DIRECTIONAL_COORDINATE_CONVERSION_POLICY_HPP

//---------------------------------------------------------------------------//
// end Uitlity_DirectionalCoordinateConversionPolicy.hpp
//---------------------------------------------------------------------------//
