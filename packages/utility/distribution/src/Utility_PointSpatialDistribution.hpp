//---------------------------------------------------------------------------//
//!
//! \file   Utility_PointSpatialDistribution.hpp
//! \author Alex Robinson
//! \brief  Point spatial distribution declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_POINT_SPATIAL_DISTRIBUTION_HPP
#define UTILITY_POINT_SPATIAL_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_SpatialDistribution.hpp"

namespace Utility{
  
//! Point spatial distribution
class PointSpatialDistribution : public SpatialDistribution
{

private:
  
  // Typedef for Teuchos::ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Constructor
  PointSpatialDistribution( const double x_position,
			    const double y_position,
			    const double z_position );

  //! Destructor
  ~PointSpatialDistribution()
  { /* ... */ }

  //! Evaluate the spatial distribution
  double evaluate( const double cartesian_point[3] ) const;

  //! Evaluate the spatial distribution PDF
  double evaluatePDF( const double cartesian_point[3] ) const;

  //! Return a random (cartesian) sample from the distribution (x, y, z)
  void sample( double sampled_point[3] ) const;

  //! Return the distribution type
  SpatialDistributionType getDistributionType() const;
  
  //! Check if the distribution is uniform
  bool isUniform() const;

  //! Check if the distribution has the same bounds
  bool hasSameBounds( const SpatialDistribution& distribution ) const;

private:

  // The x position
  double d_x_position;

  // The y position
  double d_y_position;

  // The z position
  double d_z_position;
};

} // end Utility namespace

#endif // end UTILITY_POINT_SPATIAL_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_PointSpatialDistribution.hpp
//---------------------------------------------------------------------------//
