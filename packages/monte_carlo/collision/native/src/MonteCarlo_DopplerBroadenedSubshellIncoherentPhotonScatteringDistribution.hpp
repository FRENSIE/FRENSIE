//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DopplerBroadenedSubshellIncoherentPhotonScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The Doppler broadened subshell incoherent photon scat. dist. decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DOPPLER_BROADENED_SUBSHELL_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_DOPPLER_BROADENED_SUBSHELL_INCOHERENT_PHOTON_SCATTEIRNG_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_SubshellIncoherentPhotonScatteringDistribution.hpp"
#include "MonteCarlo_SubshellDopplerBroadenedPhotonEnergyDistribution.hpp"
#include "Utility_TabularOneDDistribution.hpp"

namespace MonteCarlo{

/*! The Doppler broadened subshell incoherent photon scattering distribution 
 * class
 */
class DopplerBroadenedSubshellIncoherentPhotonScatteringDistribution : public SubshellIncoherentPhotonScatteringDistribution
{

public:

  //! Constructor
  DopplerBroadenedSubshellIncoherentPhotonScatteringDistribution(
    const SubshellType interaction_subshell,
    const double num_electrons_in_subshell,
    const double binding_energy,
    const Teuchos::RCP<const Utility::OneDDistribution>& occupation_number,
    const Teuchos::RCP<const SubshellDopplerBroadenedPhotonEnergyDistribution>&
    doppler_broadened_energy_dist,
    const double kahn_sampling_cutoff_energy = 3.0 );

  //! Destructor
  ~DopplerBroadenedSubshellIncoherentPhotonScatteringDistribution()
  { /* ... */ }

  //! Randomly scatter the photon and return the shell that was interacted with
  void scatterPhoton( PhotonState& photon,
		      ParticleBank& bank,
		      SubshellType& shell_of_interaction ) const;

private:

  // The compton profile for the subshell
  Teuchos::RCP<const SubshellDopplerBroadenedPhotonEnergyDistribution> 
  d_doppler_broadened_energy_dist;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_DOPPLER_BROADENED_SUBSHELL_INCOHERENT_PHOTON_SCATTEIRNG_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DopplerBroadenedSubshellIncoherentPhotonScatteringDistribution.hpp
//---------------------------------------------------------------------------//
