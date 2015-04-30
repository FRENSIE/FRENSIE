//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ThompsonPhotonScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The Thompson photon scattering distribution class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_THOMPSON_PHOTON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_THOMPSON_PHOTON_SCATTERING_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_PhotonScatteringDistribution.hpp"

namespace MonteCarlo{

//! The Thompson scattering distribution class
class ThompsonPhotonScatteringDistribution : public PhotonScatteringDistribution
{

public:

  //! Default constructor
  ThompsonPhotonScatteringDistribution();

  //! Destructor
  virtual ~ThompsonPhotonScatteringDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  virtual double evaluate( const double incoming_energy,
			   const double scattering_angle_cosine ) const;

  //! Evaluate the PDF
  virtual double evaluatePDF( const double incoming_energy,
			      const double scattering_angle_cosine ) const;

  //! Evaluate the integrated cross section (cm^2)
  virtual double evaluateIntegratedCrossSection(const double incoming_energy,
						const double precision ) const;

  //! Sample an outgoing energy and direction from the distribution
  virtual void sample( const double incoming_energy,
		       double& outgoing_energy,
		       double& scattering_angle_cosine,
		       SubshellType& shell_of_interaction ) const;

  //! Sample an outgoing energy and direction and record the number of trials
  virtual void sampleAndRecordTrials( const double incoming_energy,
				      double& outgoing_energy,
				      double& scattering_angle_cosine,
				      SubshellType& shell_of_interaction,
				      unsigned& trials ) const;

  //! Randomly scatter the photon
  virtual void scatterPhoton( PhotonState& photon,
			      ParticleBank& bank,
			      SubshellType& shell_of_interaction ) const;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_THOMPSON_PHOTON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ThompsonPhotonScatteringDistribution.hpp
//---------------------------------------------------------------------------//
