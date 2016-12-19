//---------------------------------------------------------------------------//
//!
//! \file   Utility_BasicCartesianDirectionalCoordinateConversionPolicy.hpp
//! \author Alex Robinson
//! \brief  Basic Cartesian directional coordinate conversion policy decl.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_BASIC_CARTESIAN_DIRECTIONAL_COORDINATE_CONVERSION_POLICY_HPP
#define UTILITY_BASIC_CARTESIAN_DIRECTIONAL_COORDINATE_CONVERSION_POLICY_HPP

// FRENSIE Includes
#include "Utility_CartesianDirectionalCoordinateConversionPolicy.hpp"

namespace Utility{

//! The basic Cartesian directional coordinate conversion policy class
class BasicCartesianDirectionalCoordinateConversionPolicy : public CartesianDirectionalCoordinateConversionPolicy
{

public:

  //! Constructor
  BasicCartesianDirectionalCoordinateConversionPolicy()
  { /* ... */ }

  //! Destructor
  ~BasicCartesianDirectionalCoordinateConversionPolicy()
  { /* ... */ }

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
};

} // end Utility namespace

#endif // end UTILITY_BASIC_CARTESIAN_DIRECTIONAL_COORDINATE_CONVERSION_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_BasicCartesianDirectionalCoordinateConversionPolicy.hpp
//---------------------------------------------------------------------------//
