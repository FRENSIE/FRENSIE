//---------------------------------------------------------------------------//
//!
//! \file   CartesianSpatialDistribution.hpp
//! \author Alex Robinson
//! \brief  Cartesian spatial distribution declaration.
//!
//---------------------------------------------------------------------------//

#ifndef CARTESIAN_SPATIAL_DISTRIBUTION_HPP
#define CARTESIAN_SPATIAL_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FACEMC Includes
#include "OneDDistribution.hpp"
#include "SpatialDistribution.hpp"

namespace FACEMC{

/*! Cartesian spatial distribution.
 * \details The x, y and z variables are assumed to be independent
 */
class CartesianSpatialDistribution : public SpatialDistribution
{

public:

  //! Constructor
  CartesianSpatialDistribution( 
			const Teuchos::RCP<OneDDistribution>& x_distribution,
			const Teuchos::RCP<OneDDistribution>& y_distribution,
			const Teuchos::RCP<OneDDistribution>& z_distribution );

  //! Destructor
  ~CartesianSpatialDistribution()
  { /* ... */ }

  //! Return a random (cartesian) sample from the distribution (x, y, z)
  void sample( double sampled_point[3] );

private:

  // X dimension distribution
  Teuchos::RCP<OneDDistribution> d_x_distribution;

  // Y dimension distribution
  Teuchos::RCP<OneDDistribution> d_y_distribution;

  // Z dimension distribution
  Teuchos::RCP<OneDDistribution> d_z_distribution;
};

} // end FACEMC namespace

#endif // end CARTESIAN_SPATIAL_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end CartesianSpatialDistribution.hpp
//---------------------------------------------------------------------------//
