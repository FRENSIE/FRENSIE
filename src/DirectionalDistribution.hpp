//---------------------------------------------------------------------------//
//!
//! \file   DirectionalDistribution.hpp
//! \author Alex Robinson
//! \brief  Directional distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef DIRECTIONAL_DISTRIBUTION_HPP
#define DIRECTIONAL_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FACEMC Includes
#include "OneDDistribution.hpp"

namespace FACEMC{

//! Directional distribution class
class DirectionalDistribution
{

public:

  //! Constructor
  DirectionalDistribution( 
		      const Teuchos::RCP<OneDDistribution>& theta_distribution,
		      const Teuchos::RCP<OneDDistribution>& mu_distribution,
		      const Axis axis = Z_AXIS );

  //! Destructor
  ~DirectionalDistribution()
  { /* ... */ } 

  //! Return a random (cartesian) sample from the distribution (u, v, w)
  void sample( double sampled_direction[3] );

private:

  // The theta distribution
  Teuchos::RCP<OneDDistribution> d_theta_distribution;

  // The mu distribution
  Teuchos::RCP<OneDDistribution> d_mu_distribution;

  // The spherical axis (direction of the mu distribution)
  Axis d_axis;
};

} // end FACEMC namespace

#endif // end DIRECTIONAL_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end DirectionalDistribution.hpp
//---------------------------------------------------------------------------//
