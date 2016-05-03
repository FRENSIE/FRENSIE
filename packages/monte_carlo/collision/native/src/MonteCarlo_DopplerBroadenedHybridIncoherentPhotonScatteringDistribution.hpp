//---------------------------------------------------------------------------//
//!
//! \file MonteCarlo_DopplerBroadenedHybridIncoherentPhotonScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The Doppler broadened hybrid incoherent photon scat. dist. decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DOPPLER_BROADENED_HYBRID_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_DOPPLER_BROADENED_HYBRID_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_ArrayRCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_WHIncoherentPhotonScatteringDistribution.hpp"
#include "MonteCarlo_CompleteDopplerBroadenedPhotonEnergyDistribution.hpp"

namespace MonteCarlo{

/*! The Doppler broadenend hybrid incoherent photon scattering dist. class
 * \details Waller-Hartree theory is used for sampling a scattering angle
 * cosine while the impulse approximation is used for sampling a Doppler
 * broadened outgoing energy.
 */
class DopplerBroadenedHybridIncoherentPhotonScatteringDistribution : public WHIncoherentPhotonScatteringDistribution
{

public:

  //! Constructor
  DopplerBroadenedHybridIncoherentPhotonScatteringDistribution( 
	  const std::shared_ptr<const ScatteringFunction>& scattering_function,
	  const std::shared_ptr<const CompleteDopplerBroadenedPhotonEnergyDistribution>&
	  doppler_broadened_energy_dist,
	  const double kahn_sampling_cutoff_energy = 3.0 );

  //! Destructor
  ~DopplerBroadenedHybridIncoherentPhotonScatteringDistribution()
  { /* ... */ }

  //! Randomly scatter the photon and return the shell that was interacted with
  void scatterPhoton( PhotonState& photon,
		      ParticleBank& bank,
		      SubshellType& shell_of_interaction ) const;

private:

  // The Doppler broadened photon energy distribution
  std::shared_ptr<const CompleteDopplerBroadenedPhotonEnergyDistribution>
  d_doppler_broadened_energy_dist;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_DOPPLER_BROADENED_HYBRID_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DopplerBroadenedHybridIncoherentPhotonScatteringDistribution.hpp
//---------------------------------------------------------------------------//
