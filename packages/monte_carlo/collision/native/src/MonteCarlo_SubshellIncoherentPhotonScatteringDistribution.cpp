//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SubshellIncoherentPhotonScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  The subshell incoherent photon scattering distribution decl.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "MonteCarlo_SubshellIncoherentPhotonScatteringDistribution.hpp"
#include "MonteCarlo_ComptonProfileHelpers.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
/*! \details The occupation number grid must be in me*c units.
 */
SubshellIncoherentPhotonScatteringDistribution::SubshellIncoherentPhotonScatteringDistribution(
       const SubshellType interaction_subshell,
       const double num_electrons_in_subshell,
       const double binding_energy,
       const Teuchos::RCP<const Utility::OneDDistribution>& occupation_number,
       const double kahn_sampling_cutoff_energy )
  : IncoherentPhotonScatteringDistribution( occupation_number, 
					    kahn_sampling_cutoff_energy ),
    d_subshell( interaction_subshell ),
    d_num_electrons_in_subshell( num_electrons_in_subshell ),
    d_binding_energy( binding_energy )
{
  // Make sure the interaction subshell is valid
  testPrecondition( interaction_subshell != INVALID_SUBSHELL );
  testPrecondition( interaction_subshell != UNKNOWN_SUBSHELL );
  // Make sure the number of electrons is valid
  testPrecondition( num_electrons_in_subshell > 0.0 );
  // Make sure the binding energy is valid
  testPrecondition( binding_energy > 0.0 );
  // Make sure the occupation number is valid
  testPrecondition( !occupation_number.is_null() );
  testPrecondition( occupation_number->getLowerBoundOfIndepVar() == -1.0 );  
  testPrecondition( occupation_number->getLowerBoundOfIndepVar() < 0.0 );
}


// Return the subshell
SubshellType 
SubshellIncoherentPhotonScatteringDistribution::getSubshell() const
{
  return d_subshell;
}

// Return the number of electrons in the subshell
double SubshellIncoherentPhotonScatteringDistribution::getNumberOfElectronsInSubshell() const
{
  return d_num_electrons_in_subshell;
}

// Return the binding energy
double SubshellIncoherentPhotonScatteringDistribution::getBindingEnergy() const
{
  return d_binding_energy;
}

// Evaluate the distribution
double SubshellIncoherentPhotonScatteringDistribution::evaluate( 
			           const double incoming_energy,
			           const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > d_binding_energy );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );
  
  return d_num_electrons_in_subshell*
    IncoherentPhotonScatteringDistribution::evaluate( incoming_energy,
						      scattering_angle_cosine);
}

// Evaluate the integrated cross section (cm^2)
double SubshellIncoherentPhotonScatteringDistribution::evaluateIntegratedCrossSection( 
						  const double incoming_energy,
						  const double precision) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > d_binding_energy );

  return d_num_electrons_in_subshell*
    IncoherentPhotonScatteringDistribution::evaluateIntegratedCrossSection(
							       incoming_energy,
							       precision );
}

// Sample an outgoing energy and direction from the distribution
/*! \details This function will only sample a Compton line energy (no
 * Doppler broadening).
 */ 
void SubshellIncoherentPhotonScatteringDistribution::sample( 
				     const double incoming_energy,
				     double& outgoing_energy,
				     double& scattering_angle_cosine,
				     SubshellType& shell_of_interaction ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > d_binding_energy );

  unsigned trial_dummy;
  
  return this->sampleAndRecordTrials( incoming_energy,
				      outgoing_energy,
				      scattering_angle_cosine,
				      shell_of_interaction,
				      trial_dummy );
}

// Sample an outgoing energy and direction and record the number of trials
/*! \details This function will only sample a Compton line energy (no
 * Doppler broadening).
 */ 
void SubshellIncoherentPhotonScatteringDistribution::sampleAndRecordTrials( 
					    const double incoming_energy,
					    double& outgoing_energy,
					    double& scattering_angle_cosine,
					    SubshellType& shell_of_interaction,
					    unsigned& trials ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > d_binding_energy );

  IncoherentPhotonScatteringDistribution::sampleAndRecordTrials( 
						       incoming_energy,
						       outgoing_energy,
						       scattering_angle_cosine,
						       shell_of_interaction,
						       trials );

  shell_of_interaction = d_subshell;
}

// Calculate the scattering function argument
/*! \details This implementation calculates the max electron momentum
 * projection for the given energy and scattering angle cosine.
 */ 
double SubshellIncoherentPhotonScatteringDistribution::calculateScatteringFunctionArgument( 
				   const double incoming_energy,
				   const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy >= d_binding_energy );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );
  
  return calculateMaxElectronMomentumProjection( incoming_energy,
						 d_binding_energy,
						 scattering_angle_cosine );
}

// Randomly scatter the photon
/*! \details The particle bank is used to store the electron that is emitted
 * from the collision. Whether or not Doppler broadening is done, the 
 * energy and direction of the outgoing electron is calculated as if it were
 * at rest initially (feel free to update this model!).
 */
void SubshellIncoherentPhotonScatteringDistribution::scatterPhoton( 
				     PhotonState& photon,
				     ParticleBank& bank,
				     SubshellType& shell_of_interaction ) const
{
  // Make sure the photon energy is valid
  testPrecondition( photon.getEnergy() > d_binding_energy );

  double outgoing_energy, scattering_angle_cosine;

  // Sample an outgoing energy and direction
  this->sample( photon.getEnergy(),
		outgoing_energy,
		scattering_angle_cosine,
		shell_of_interaction );

  // Sample the azimuthal angle of the outgoing photon
  const double azimuthal_angle = this->sampleAzimuthalAngle();

  // Create the ejectected electron
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
// end MonteCarlo_SubshellIncoherentPhotonScatteringDistribution.cpp
//---------------------------------------------------------------------------//
