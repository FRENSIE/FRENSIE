//---------------------------------------------------------------------------//
//!
//! \file   Utility_DirectionalDistribution.hpp
//! \author Alex Robinson
//! \brief  Directional distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_DIRECTIONAL_DISTRIBUTION_HPP
#define UTILITY_DIRECTIONAL_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"
#include "Utility_Axis.hpp"
#include "Utility_ComparePolicy.hpp"

namespace Utility{

//! Directional distribution class
class DirectionalDistribution
{

private:

  // Typedef for Teuchos::ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Constructor
  DirectionalDistribution( 
		      const Teuchos::RCP<OneDDistribution>& theta_distribution,
		      const Teuchos::RCP<OneDDistribution>& mu_distribution,
		      const Axis axis = Z_AXIS );

  //! Destructor
  ~DirectionalDistribution()
  { /* ... */ } 

  //! Evaluate the directional distribution
  double evaluate( const double cartesian_point[3] ) const;

  //! Evaluate the directional distribution PDF
  double evaluatePDF( const double cartesian_point[3] ) const;

  //! Return a random (cartesian) sample from the distribution (u, v, w)
  void sample( double sampled_direction[3] ) const;

  //! Check if the distribution has the same bounds
  bool hasSameBounds( const DirectionalDistribution& distribution ) const;

protected:
  
  //! Convert a cartesian coordinate to a spherical coordinate
  void convertCartesianCoordsToSpherical( const double cartesian_point[3],
					  double spherical_point[3] ) const; 

private:

  // The theta distribution
  Teuchos::RCP<OneDDistribution> d_theta_distribution;

  // The mu distribution
  Teuchos::RCP<OneDDistribution> d_mu_distribution;

  // The spherical axis (direction of the mu distribution)
  Axis d_axis;
};

// Check if the distribution has the same bounds
inline bool DirectionalDistribution::hasSameBounds( 
			    const DirectionalDistribution& distribution ) const
{
  if( d_axis == distribution.d_axis )
  {
    return 
      Policy::relError(d_theta_distribution->getLowerBoundOfIndepVar(),
		  distribution.d_theta_distribution->getLowerBoundOfIndepVar())
      < 1e-9 &&
      Policy::relError(d_theta_distribution->getUpperBoundOfIndepVar(),
		  distribution.d_theta_distribution->getUpperBoundOfIndepVar())
      < 1e-9 &&
      Policy::relError(d_mu_distribution->getLowerBoundOfIndepVar(),
		     distribution.d_mu_distribution->getLowerBoundOfIndepVar())
      < 1e-9 &&
      Policy::relError(d_mu_distribution->getUpperBoundOfIndepVar(),
		     distribution.d_mu_distribution->getUpperBoundOfIndepVar())
      < 1e-9;
  }
  else
    return false;
}

} // end Utility namespace

#endif // end UTILITY_DIRECTIONAL_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_DirectionalDistribution.hpp
//---------------------------------------------------------------------------//
