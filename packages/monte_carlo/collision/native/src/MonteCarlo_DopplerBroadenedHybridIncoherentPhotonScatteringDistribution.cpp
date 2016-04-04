//---------------------------------------------------------------------------//
//!
//! \file MonteCarlo_DopplerBroadenedHybridIncoherentPhotonScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  The Doppler broadened Waller-Hartree incoherent photon scattering dist. def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_DopplerBroadenedHybridIncoherentPhotonScatteringDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor  
DopplerBroadenedHybridIncoherentPhotonScatteringDistribution::DopplerBroadenedHybridIncoherentPhotonScatteringDistribution( 
      const std::shared_ptr<const ScatteringFunction>& scattering_function,
      const std::shared_ptr<const MonteCarlo::CompleteDopplerBroadenedPhotonEnergyDistribution>& 
      doppler_broadened_energy_dist,
      const double kahn_sampling_cutoff_energy )
  : WHIncoherentPhotonScatteringDistribution( scattering_function,
					      kahn_sampling_cutoff_energy ),
    d_doppler_broadened_energy_dist( doppler_broadened_energy_dist )
{
  // Make sure the scattering function is valid
  testPrecondition( scattering_function.get() );
  // Make sure the Doppler broadened energy distribution is valid
  testPrecondition( doppler_broadened_energy_dist.get() );
}

// Randomly scatter the photon and return the shell that was interacted with
void DopplerBroadenedHybridIncoherentPhotonScatteringDistribution::scatterPhoton( 
			             PhotonState& photon,
				     ParticleBank& bank,
			             SubshellType& shell_of_interaction ) const
{
  double outgoing_energy, scattering_angle_cosine;

  // Sample an outgoing energy and direction
  this->sample( photon.getEnergy(),
		outgoing_energy,
		scattering_angle_cosine );

  // Doppler broaden the photon energy by interacting with a subshell
  d_doppler_broadened_energy_dist->sample( photon.getEnergy(),
					   scattering_angle_cosine,
					   outgoing_energy,
					   shell_of_interaction );

  // Sample the azimuthal angle of the outgoing photon
  const double azimuthal_angle = this->sampleAzimuthalAngle();

  // Create the ejectected electron 
  this->createEjectedElectron( photon, 
			       scattering_angle_cosine, 
			       azimuthal_angle,
			       bank );

  // Set the new energy
  photon.setEnergy( outgoing_energy );

  // Set the new direction
  photon.rotateDirection( scattering_angle_cosine, azimuthal_angle );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_DopplerBroadenedIncoherentPhotonScatteringDistribution.cpp
//---------------------------------------------------------------------------//

