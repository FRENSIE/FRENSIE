//---------------------------------------------------------------------------//
//!
//! \file   CylindricalSpatialDistribution.hpp
//! \author Alex Robinson
//! \brief  Cylindrical spatial distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef CYLINDRICAL_SPATIAL_DISTRIBUTION_HPP
#define CYLINDRICAL_SPATIAL_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FACEMC Includes
#include "OneDDistribution.hpp"
#include "SpatialDistribution.hpp"
#include "Axis.hpp"

namespace FACEMC{

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
	              const Teuchos::RCP<OneDDistribution>& r_distribution,
	              const Teuchos::RCP<OneDDistribution>& theta_distribution,
		      const Teuchos::RCP<OneDDistribution>& axis_distribution,
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

  //! Check if the distribution is uniform
  bool isUniform() const;

protected:

  //! Convert a cartesian coordinate to a cylindrical coordinate
  void convertCartesianCoordsToCylindrical(const double cartesian_point[3],
					   double cylindrical_point[3]) const;

private:

  // r dimension distribution
  Teuchos::RCP<OneDDistribution> d_r_distribution;

  // theta dimension distribution
  Teuchos::RCP<OneDDistribution> d_theta_distribution;

  // axis dimension distribution
  Teuchos::RCP<OneDDistribution> d_axis_distribution;

  // The start position of the cylindrical axis
  double d_center_x_position;
  double d_center_y_position;
  double d_center_z_position;

  // The cylindrical axis
  Axis d_axis;

  // Records whether the distribution is uniform
  bool d_uniform;
};

} // end FACEMC namespace

#endif // end CYLINDRICAL_SPATIAL_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end CylindricalSpatialDistribution.hpp
//---------------------------------------------------------------------------//
