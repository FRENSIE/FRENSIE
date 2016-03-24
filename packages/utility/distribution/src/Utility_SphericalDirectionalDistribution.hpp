//---------------------------------------------------------------------------//
//!
//! \file   Utility_SphericalDirectionalDistribution.hpp
//! \author Alex Robinson
//! \brief  Directional distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_SPHERICAL_DIRECTIONAL_DISTRIBUTION_HPP
#define UTILITY_SPHERICAL_DIRECTIONAL_DISTRIBUTION_HPP

// Std Lib Includes
#include <memory>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_DirectionalDistribution.hpp"
#include "Utility_OneDDistribution.hpp"
#include "Utility_Axis.hpp"
#include "Utility_ComparePolicy.hpp"

namespace Utility{

//! The spherical directional distribution class
class SphericalDirectionalDistribution : public DirectionalDistribution
{

private:
  
  // Typedef for Teuchos::ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Constructor
  SphericalDirectionalDistribution( 
		   const std::shared_ptr<OneDDistribution>& theta_distribution,
                   const std::shared_ptr<OneDDistribution>& mu_distribution,
                   const Axis axis = Z_AXIS );

  //! Destructor
  ~SphericalDirectionalDistribution()
  { /* ... */ } 

  //! Evaluate the directional distribution
  double evaluate( const double cartesian_point[3] ) const;

  //! Evaluate the directional distribution PDF
  double evaluatePDF( const double cartesian_point[3] ) const;

  //! Return a random (cartesian) sample from the distribution (u, v, w)
  void sample( double sampled_direction[3] ) const;

  //! Return the distribution type
  DirectionalDistributionType getDistributionType() const;

  //! Check if the distribution has the same bounds
  bool hasSameBounds( const DirectionalDistribution& distribution ) const;

protected:
  
  //! Convert a cartesian coordinate to a spherical coordinate
  void convertCartesianCoordsToSpherical( const double cartesian_point[3],
					  double spherical_point[3] ) const; 

private:

  // The theta distribution
  std::shared_ptr<OneDDistribution> d_theta_distribution;

  // The mu distribution
  std::shared_ptr<OneDDistribution> d_mu_distribution;

  // The spherical axis (direction of the mu distribution)
  Axis d_axis;
};

} // end Utility namespace

#endif // end UTILITY_SPHERICAL_DIRECTIONAL_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_SphericalDirectionalDistribution.hpp
//---------------------------------------------------------------------------//
