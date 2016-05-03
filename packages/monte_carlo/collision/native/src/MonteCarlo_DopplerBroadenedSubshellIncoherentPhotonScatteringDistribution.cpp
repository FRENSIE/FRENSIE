//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DopplerBroadenedSubshellIncoherentPhotonScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  The Doppler broadened subshell incoherent photon scat. dist. def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_DopplerBroadenedSubshellIncoherentPhotonScatteringDistribution.hpp"
#include "MonteCarlo_ComptonProfileHelpers.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
/*! \details The occupation number and Compton profile grid be in me*c units.
 * The Compton profile must be in inverse me*c units.
 */
DopplerBroadenedSubshellIncoherentPhotonScatteringDistribution::DopplerBroadenedSubshellIncoherentPhotonScatteringDistribution(
    const std::shared_ptr<const SubshellDopplerBroadenedPhotonEnergyDistribution>&
    doppler_broadened_energy_dist,
    const Teuchos::RCP<const Utility::OneDDistribution>& occupation_number,
    const double kahn_sampling_cutoff_energy )
  : SubshellIncoherentPhotonScatteringDistribution( 
	       doppler_broadened_energy_dist->getSubshell(),
	       doppler_broadened_energy_dist->getSubshellOccupancy(),
	       doppler_broadened_energy_dist->getSubshellBindingEnergy(),
	       occupation_number,
	       kahn_sampling_cutoff_energy ),
    d_doppler_broadened_energy_dist( doppler_broadened_energy_dist )
{
  // Make sure the Doppler broadened energy dist is valid
  testPrecondition( doppler_broadened_energy_dist.get() );
}

// Randomly scatter the photon and return the shell that was interacted with
void DopplerBroadenedSubshellIncoherentPhotonScatteringDistribution::scatterPhoton( 
				     PhotonState& photon,
				     ParticleBank& bank,
				     SubshellType& shell_of_interaction ) const
{
  double outgoing_energy, scattering_angle_cosine;

  // Sample an outgoing energy and direction
  this->sample( photon.getEnergy(),
		outgoing_energy,
		scattering_angle_cosine );

  // Doppler broaden the compton line
  d_doppler_broadened_energy_dist->sample( photon.getEnergy(),
					   scattering_angle_cosine,
					   outgoing_energy,
					   shell_of_interaction );
  
  // Sample an azimuthal angle
  const double azimuthal_angle = this->sampleAzimuthalAngle();

  // Create the ejected electron
  this->createEjectedElectron( photon,
			       scattering_angle_cosine,
			       azimuthal_angle,
			       bank );

  // Set the new energy
  if( outgoing_energy > 0.0 )
  {
    photon.setEnergy( outgoing_energy );
    
    // Set the new direction
    photon.rotateDirection( scattering_angle_cosine, azimuthal_angle );
  }
  else
  {
    photon.setEnergy( std::numeric_limits<double>::min() );

    photon.setAsGone();
  }  
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_DopplerBroadenedSubshellIncoherentPhotonScatteringDistribution.cpp
//---------------------------------------------------------------------------//
