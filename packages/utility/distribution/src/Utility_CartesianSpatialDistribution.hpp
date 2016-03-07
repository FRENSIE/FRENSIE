//---------------------------------------------------------------------------//
//!
//! \file   Utility_CartesianSpatialDistribution.hpp
//! \author Alex Robinson
//! \brief  Cartesian spatial distribution declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_CARTESIAN_SPATIAL_DISTRIBUTION_HPP
#define UTILITY_CARTESIAN_SPATIAL_DISTRIBUTION_HPP

// Std Lib Includes
#include <memory>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"
#include "Utility_SpatialDistribution.hpp"

namespace Utility{

/*! Cartesian spatial distribution.
 * \details The x, y and z variables are assumed to be independent
 */
class CartesianSpatialDistribution : public SpatialDistribution
{

private:
  
  // Typedef for Teuchos::ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Constructor
  CartesianSpatialDistribution( 
		      const std::shared_ptr<OneDDistribution>& x_distribution,
                      const std::shared_ptr<OneDDistribution>& y_distribution,
                      const std::shared_ptr<OneDDistribution>& z_distribution );

  //! Destructor
  ~CartesianSpatialDistribution()
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

  // X dimension distribution
  std::shared_ptr<OneDDistribution> d_x_distribution;

  // Y dimension distribution
  std::shared_ptr<OneDDistribution> d_y_distribution;

  // Z dimension distribution
  std::shared_ptr<OneDDistribution> d_z_distribution;

  // Records whether the distribution is uniform
  bool d_uniform;
};

} // end Utility namespace

#endif // end UTILITY_CARTESIAN_SPATIAL_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_CartesianSpatialDistribution.hpp
//---------------------------------------------------------------------------//
