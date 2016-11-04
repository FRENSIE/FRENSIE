//---------------------------------------------------------------------------//
//!
//! \file   Utility_DirectionalDistribution.hpp
//! \author Alex Robinson
//! \brief  Directional distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_DIRECTIONAL_DISTRIBUTION_HPP
#define UTILITY_DIRECTIONAL_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Utility_DirectionalDistributionType.hpp"

namespace Utility{

//! Directional distribution class
class DirectionalDistribution
{

public:

  //! Constructor
  DirectionalDistribution()
  { /* ... */ }

  //! Destructor
  virtual ~DirectionalDistribution()
  { /* ... */ }

  //! Evaluate the directional distribution
  virtual double evaluate( const double cartesian_point[3] ) const = 0;

  //! Evaluate the directional distribution PDF
  virtual double evaluatePDF( const double cartesian_point[3] ) const = 0;

  //! Return a random (cartesian) sample from the distribution (u, v, w)
  virtual void sample( double sampled_direction[3] ) const = 0;

  //! Return the distribution type
  virtual DirectionalDistributionType getDistributionType() const = 0;

  //! Check if the distribution has the same bounds
  virtual bool hasSameBounds(
		       const DirectionalDistribution& distribution ) const = 0;
};

} // end Utility namespace

#endif // end UTILITY_DIRECTIONAL_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_DirectionalDistribution.hpp
//---------------------------------------------------------------------------//
