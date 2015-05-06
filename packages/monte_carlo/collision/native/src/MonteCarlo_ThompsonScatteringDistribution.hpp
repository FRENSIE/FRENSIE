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

  //! Default constructor
  ThompsonScatteringDistribution();

  //! Destructor
  virtual ~ThompsonScatteringDistribution()
  { /* ... */ }

  //! Evaluate the integrated cross section (b)
  double evaluateIntegratedCrossSection( const double incoming_energy,
					 const double precision ) const;

  //! Sample an outgoing energy and direction from the distribution
  void sample( const double incoming_energy,
	       double& outgoing_energy,
	       double& scattering_angle_cosine,
	       SubshellType& shell_of_interaction ) const;

  //! Sample an outgoing energy and direction and record the number of trials
  void sampleAndRecordTrials( const double incoming_energy,
			      double& outgoing_energy,
			      double& scattering_angle_cosine,
			      SubshellType& shell_of_interaction,
			      unsigned& trials ) const;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_THOMPSON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ThompsonScatteringDistribution.hpp
//---------------------------------------------------------------------------//
