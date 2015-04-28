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
#include "MonteCarlo_PhotonScatteringDistribution.hpp"

namespace MonteCarlo{

//! The Klein-Nishina photon scattering distribution class
class KleinNishinaPhotonScatteringDistribution : public PhotonScatteringDistribution
{

public:
  
  //! Default Constructor
  KleinNishinaPhotonScatteringDistribution();

  //! Constructor
  KleinNishinaPhotonScatteringDistribution( 
				    const double kahn_sampling_cutoff_energy );

  //! Evaluate the distribution
  virtual double evaluate( const double incoming_energy,
			   const double scattering_angle_cosine ) const;

  //! Evaluate the PDF
  virtual double evaluatePDF( const double incoming_energy,
			      const double scattering_angle_cosine ) const;

  //! ample an outgoing energy and direction from the distribution
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

  //! Randomly scatter the photon and return the shell that was interacted with
  virtual void scatterPhoton( PhotonState& photon,
			      ParticleBank& bank,
			      SubshellType& shell_of_interaction ) const;

private:

  // The min cutoff energy
  static const double s_min_kahn_sampling_cutoff_energy;

  // The Kahn rejection sampling cutoff energy
  double d_kahn_sampling_cutoff_energy;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_KLEIN_NISHINA_PHOTON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_KleinNishinaPhotonScatteringDistribution.hpp
//---------------------------------------------------------------------------//
