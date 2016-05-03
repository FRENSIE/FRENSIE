//---------------------------------------------------------------------------//
//!
//! \file   Utility_CylindricalSpatialDistribution.hpp
//! \author Alex Robinson
//! \brief  Cylindrical spatial distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_CYLINDRICAL_SPATIAL_DISTRIBUTION_HPP
#define UTILITY_CYLINDRICAL_SPATIAL_DISTRIBUTION_HPP

// Std Lib Includes
#include <memory>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"
#include "Utility_SpatialDistribution.hpp"
#include "Utility_Axis.hpp"

namespace Utility{

/*! Cylindrical spatial distribution
 * \details The r, theta, and axis variables are assumed to be independent
 */
class CylindricalSpatialDistribution : public SpatialDistribution
{

private:
  
  // Typedef for Teuchos::ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Constructor
  CylindricalSpatialDistribution(
	           const std::shared_ptr<OneDDistribution>& r_distribution,
	           const std::shared_ptr<OneDDistribution>& theta_distribution,
                   const std::shared_ptr<OneDDistribution>& axis_distribution,
                   const double center_x_position,
                   const double center_y_position,
                   const double center_z_position,
                   const Axis axis = Z_AXIS );
  
  //! Destructor
  ~CylindricalSpatialDistribution()
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

  //! Convert a cartesian coordinate to a cylindrical coordinate
  void convertCartesianCoordsToCylindrical(const double cartesian_point[3],
					   double cylindrical_point[3]) const;

private:

  // r dimension distribution
  std::shared_ptr<OneDDistribution> d_r_distribution;

  // theta dimension distribution
  std::shared_ptr<OneDDistribution> d_theta_distribution;

  // axis dimension distribution
  std::shared_ptr<OneDDistribution> d_axis_distribution;

  // The start position of the cylindrical axis
  double d_center_x_position;
  double d_center_y_position;
  double d_center_z_position;

  // The cylindrical axis
  Axis d_axis;

  // Records whether the distribution is uniform
  bool d_uniform;
};

} // end Utility namespace

#endif // end UTILITY_CYLINDRICAL_SPATIAL_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_CylindricalSpatialDistribution.hpp
//---------------------------------------------------------------------------//
