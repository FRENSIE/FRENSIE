//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ThompsonScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The Thompson scattering distribution class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_THOMPSON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_THOMPSON_SCATTERING_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_CoherentScatteringDistribution.hpp"

namespace MonteCarlo{

//! The Thompson scattering distribution class
class ThompsonScatteringDistribution : public CoherentScatteringDistribution
{

public:

  //! The trials counter type
  typedef CoherentScatteringDistribution::Counter Counter;

  //! Default constructor
  ThompsonScatteringDistribution();

  //! Destructor
  virtual ~ThompsonScatteringDistribution()
  { /* ... */ }

  //! Evaluate the integrated cross section (b)
  double evaluateIntegratedCrossSection( const double incoming_energy,
					 const double precision ) const;

private:

  // Return a dummy form factor squared distribution
  static std::shared_ptr<const FormFactorSquared>
  getDummyFormFactorSquaredDistribution();

  // Sample an outgoing direction from the distribution
  void sampleAndRecordTrialsImpl( const double incoming_energy,
				  double& scattering_angle_cosine,
				  Counter& trials ) const;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_THOMPSON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ThompsonScatteringDistribution.hpp
//---------------------------------------------------------------------------//
