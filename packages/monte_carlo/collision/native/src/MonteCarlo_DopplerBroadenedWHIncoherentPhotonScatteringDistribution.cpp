//---------------------------------------------------------------------------//
//!
//! \file MonteCarlo_DopplerBroadenedWHIncoherentPhotonScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  The Doppler broadened Waller-Hartree incoherent photon scattering dist. def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_DopplerBroadenedWHIncoherentPhotonScatteringDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor  
DopplerBroadenedWHIncoherentPhotonScatteringDistribution::DopplerBroadenedWHIncoherentPhotonScatteringDistribution( 
      const Teuchos::RCP<const Utility::OneDDistribution>& scattering_function,
      const Teuchos::Array<double>& subshell_binding_energies,
      const Teuchos::Array<double>& subshell_occupancies,
      const Teuchos::Array<SubshellType>& subshell_order,
      const Teuchos::RCP<ComptonProfileSubshellConverter>& subshell_converter,
      const double kahn_sampling_cutoff_energy )
  : WHIncoherentPhotonScatteringDistribution( scattering_function,
					      subshell_binding_energies,
					      subshell_occupancies,
					      subshell_order,
					      kahn_sampling_cutoff_energy ),
    d_subshell_converter( subshell_converter )
{
  // Make sure the scattering function is valid
  testPrecondition( !scattering_function.is_null() );
  // Make sure the shell interaction data is valid
  testPrecondition( subshell_binding_energies.size() > 0 );
  testPrecondition( subshell_occupancies.size() ==
		    subshell_binding_energies.size() );
  testPrecondition( subshell_order.size() == 
		    subshell_binding_energies.size() );
  // Make sure the subshell converter is valid
  testPrecondition( !subshell_converter.is_null() );
}

// Randomly scatter the photon and return the shell that was interacted with
/*! \details The particle bank is used to store the electron that is emitted
 * from the collision. The energy and direction of the outgoing electron is 
 * calculated as if it were at rest initially (feel free to update this 
 * model!).
 */ 
void DopplerBroadenedWHIncoherentPhotonScatteringDistribution::scatterPhoton( 
				     PhotonState& photon,
				     ParticleBank& bank,
				     SubshellType& shell_of_interaction ) const
{
  double compton_line_energy, scattering_angle_cosine;

  // Sample an outgoing energy and direction
  this->sample( photon.getEnergy(),
		compton_line_energy,
		scattering_angle_cosine,
		shell_of_interaction );

  // Doppler broaden the compton line
  double outgoing_energy = this->sampleDopplerBroadenedComptonLineEnergy( 
						       photon.getEnergy(),
						       scattering_angle_cosine,
						       shell_of_interaction );

  // Sample an azimuthal angle
  const double azimuthal_angle = this->sampleAzimuthalAngle();

  // Create the ejected electron
  this->createEjectedElectron( photon,
			       scattering_angle_cosine,
			       azimuthal_angle,
			       bank );

  // Set the new energy
  photon.setEnergy( outgoing_energy );

  // Set the new direction
  photon.rotateDirection( scattering_angle_cosine, azimuthal_angle );
}

// Sample the subshell that is interacted with
void DopplerBroadenedWHIncoherentPhotonScatteringDistribution::sampleInteractionSubshell( 
				          SubshellType& shell_of_interaction,
					  double& subshell_binding_energy,
				          unsigned& compton_shell_index ) const
{
  WHIncoherentPhotonScatteringDistribution::sampleInteractionSubshell( 
						     shell_of_interaction,
						     subshell_binding_energy );

  compton_shell_index = 
    d_subshell_converter->convertSubshellToIndex( shell_of_interaction );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_DopplerBroadenedIncoherentPhotonScatteringDistribution.cpp
//---------------------------------------------------------------------------//

