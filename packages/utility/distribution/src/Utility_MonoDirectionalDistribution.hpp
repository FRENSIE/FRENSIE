//---------------------------------------------------------------------------//
//!
//! \file   Utility_MonoDirectionalDistribution.hpp
//! \author Alex Robinson
//! \brief  Mono-directional distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_MONO_DIRECTIONAL_DISTRIBUTION_HPP
#define UTILITY_MONO_DIRECTIONAL_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_DirectionalDistribution.hpp"

namespace Utility{

//! The mono-directional distribution class
class MonoDirectionalDistribution : public DirectionalDistribution
{

private:

  // Typedef for Teuchos::ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Constructor
  MonoDirectionalDistribution( const double x_direction,
			       const double y_direction,
			       const double z_direction );

  //! Destructor
  ~MonoDirectionalDistribution()
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

private:

  // The x-direction
  double d_x_direction;

  // The y-direction
  double d_y_direction;

  // The z-direction
  double d_z_direction;
};

} // end Utility namespace

#endif // end UTILITY_MONO_DIRECTIONAL_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_MonoDirectionalDistribution.hpp
//---------------------------------------------------------------------------//
