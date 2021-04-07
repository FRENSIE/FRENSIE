//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_KleinNishinaPhotonScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The Klein-Nishina photon scattering distribution declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_KLEIN_NISHINA_PHOTON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_KLEIN_NISHINA_PHOTON_SCATTERING_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_IncoherentPhotonScatteringDistribution.hpp"

namespace MonteCarlo{

//! The Klein-Nishina photon scattering distribution class
class KleinNishinaPhotonScatteringDistribution : public IncoherentPhotonScatteringDistribution
{

public:

  //! The trials counter type
  typedef IncoherentPhotonScatteringDistribution::Counter Counter;

  //! Default Constructor
  KleinNishinaPhotonScatteringDistribution();

  //! Constructor
  KleinNishinaPhotonScatteringDistribution(
				    const double kahn_sampling_cutoff_energy );

  //! Destructor
  ~KleinNishinaPhotonScatteringDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  double evaluate( const double incoming_energy,
		   const double scattering_angle_cosine ) const;

  //! Evaluate the integrated cross section (b)
  double evaluateIntegratedCrossSection( const double incoming_energy,
					 const double precision ) const;

  //! Sample an outgoing energy and direction from the distribution
  void sample( const double incoming_energy,
	       double& outgoing_energy,
	       double& scattering_angle_cosine ) const;

  //! Sample an outgoing energy and direction and record the number of trials
  void sampleAndRecordTrials( const double incoming_energy,
			      double& outgoing_energy,
			      double& scattering_angle_cosine,
			      Counter& trials ) const;

  //! Randomly scatter the photon and return the shell that was interacted with
  void scatterPhoton( PhotonState& photon,
		      ParticleBank& bank,
		      Data::SubshellType& shell_of_interaction ) const;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_KLEIN_NISHINA_PHOTON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_KleinNishinaPhotonScatteringDistribution.hpp
//---------------------------------------------------------------------------//
