//---------------------------------------------------------------------------//
//!
//! \file   Utility_SphericalSpatialDistribution.hpp
//! \author Alex Robinson
//! \brief  Spherical spatial distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_SPHERICAL_SPATIAL_DISTRIBUTION_HPP
#define UTILITY_SPHERICAL_SPATIAL_DISTRIBUTION_HPP

// Std Lib Includes
#include <memory>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"
#include "Utility_SpatialDistribution.hpp"
#include "Utility_Axis.hpp"

namespace Utility{

/*! Spherical spatial distribution
 * \details the r, theta, and mu variables are assumed to be independent
 */
class SphericalSpatialDistribution : public SpatialDistribution
{

private:

  // Typedef for Teuchos::ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Constructor
  SphericalSpatialDistribution(
		   const std::shared_ptr<OneDDistribution>& r_distribution,
		   const std::shared_ptr<OneDDistribution>& theta_distribution,
                   const std::shared_ptr<OneDDistribution>& mu_distribution,
                   const double center_x_position,
                   const double center_y_position,
                   const double center_z_position,
                   const Axis axis = Z_AXIS );

  //! Destructor
  ~SphericalSpatialDistribution()
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

protected:

  //! Convert a cartesian coordinate to a spherical coordinate
  void convertCartesianCoordsToSpherical( const double cartesian_point[3],
					  double spherical_point[3] ) const;

private:

  // r dimension distribution
  std::shared_ptr<OneDDistribution> d_r_distribution;

  // theta dimension distribution
  std::shared_ptr<OneDDistribution> d_theta_distribution;

  // mu dimension distribution
  std::shared_ptr<OneDDistribution> d_mu_distribution;

  // The center position of the sphere
  double d_center_x_position;
  double d_center_y_position;
  double d_center_z_position;

  // The spherical axis (direction of the mu distribution)
  Axis d_axis;

  // Records whether the distribution is uniform
  bool d_uniform;
};

} // end Utility namespace

#endif // end UTILITY_SPHERICAL_SPATIAL_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_SphericalSpatialDistribution.cpp
//---------------------------------------------------------------------------//
