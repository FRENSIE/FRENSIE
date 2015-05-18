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
	const SubshellType interaction_subshell,
	const double num_electrons_in_subshell,
	const double binding_energy,
	const Teuchos::RCP<const Utility::OneDDistribution>& occupation_number,
	const Teuchos::RCP<const Utility::TabularOneDDistribution>& 
	compton_profile,
	const double kahn_sampling_cutoff_energy )
  : SubshellIncoherentPhotonScatteringDistribution( interaction_subshell,
						    num_electrons_in_subshell,
						    binding_energy,
						    occupation_number,
						    kahn_sampling_cutoff_energy ),
    d_compton_profile( compton_profile )
{
  // Make sure the Compton profile is valid
  testPrecondition( !compton_profile.is_null() );
  testPrecondition( compton_profile->getLowerBoundOfIndepVar() == -1.0 );
  testPrecondition( compton_profile->getLowerBoundOfIndepVar() < 0.0 );
  testPrecondition( compton_profile->getLowerBoundOfIndepVar() ==
		    occupation_number->getLowerBoundOfIndepVar() );
}

// Sample an outgoing energy from the differential distribution
double DopplerBroadenedSubshellIncoherentPhotonScatteringDistribution::sampleDopplerBroadenedComptonLineEnergy( 
				     const double incoming_energy,
				     const double scattering_angle_cosine,
				     SubshellType& shell_of_interaction ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy >= this->getBindingEnergy() );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  // Calculate the max electron momentum projection
  double pz_max = this->calculateOccupationNumberArgument(
					             incoming_energy,
					             scattering_angle_cosine );

  // Sample an electron momentum projection
  double pz = d_compton_profile->sampleInSubrange( pz_max );

  // Calculate the doppler broadened energy
  bool energetically_possible;

  double outgoing_energy = calculateDopplerBroadenedEnergy(
						      pz,
						      incoming_energy,
						      scattering_angle_cosine,
						      energetically_possible );

  // Make sure the outgoing energy is valid
  testPostcondition( energetically_possible );
  testPostcondition( outgoing_energy >= 0.0 );

  return outgoing_energy;
}

// Randomly scatter the photon and return the shell that was interacted with
void DopplerBroadenedSubshellIncoherentPhotonScatteringDistribution::scatterPhoton( 
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
