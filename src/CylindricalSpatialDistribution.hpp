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
		      const double start_x_position,
		      const double start_y_position,
		      const double start_z_position,
		      const Axis axis = Z_AXIS );
  
  //! Destructor
  ~CylindricalSpatialDistribution()
  { /* ... */ }
  
  //! Return a random (cartesian) sample from the distribution (x, y, z)
  void sample( double sampled_point[3] );

private:

  // r dimension distribution
  Teuchos::RCP<OneDDistribution> d_r_distribution;

  // theta dimension distribution
  Teuchos::RCP<OneDDistribution> d_theta_distribution;

  // axis dimension distribution
  Teuchos::RCP<OneDDistribution> d_axis_distribution;

  // the start position of the cylindrical axis
  double d_start_x_position;
  double d_start_y_position;
  double d_start_z_position;

  // the cylindrical axis
  Axis d_axis;
};

} // end FACEMC namespace

#endif // end CYLINDRICAL_SPATIAL_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end CylindricalSpatialDistribution.hpp
//---------------------------------------------------------------------------//
