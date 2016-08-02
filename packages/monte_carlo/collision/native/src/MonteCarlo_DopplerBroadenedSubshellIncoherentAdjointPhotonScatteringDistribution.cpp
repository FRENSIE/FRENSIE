//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DopplerBroadenedSubshellIncoherentAdjointPhotonScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The doppler broadened subshell adjoint incoherent photon scattering
//!         distribution definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_MonteCarlo_DopplerBroadenedSubshellIncoherentAdjointPhotonScatteringDistribution.hpp"
#include "MonteCarlo_AdjointPhotonProbeState.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "ContractException.hpp"

namespace MonteCarlo{

// Constructor
DopplerBroadenedSubshellIncoherentAdjointPhotonScatteringDistribution::DopplerBroadenedSubshellIncoherentAdjointPhotonScatteringDistribution(
         const double max_energy,
         const Data::SubshellType interaction_subshell,
         const double num_electrons_in_subshell,
         const double binding_energy,
         const Teuchos::RCP<const Utility::OneDDistribution>& occupation_number
         const Teuchos::RCP<const ComptonProfile>& compton_profile )
  : SubshellIncoherentAdjointPhotonScatteringDistribution(
                                                     max_energy,
                                                     interaction_subshell,
                                                     num_electrons_in_subshell,
                                                     binding_energy,
                                                     occupation_number ),
    d_compton_profile( compton_profile )
{
  // Make sure the binding energy is valid
  testPrecondition( binding_energy > 0.0 );
  // Make sure the max energy is valid
  testPrecondition( max_energy > binding_energy );
  // Make sure the interaction subshell is valid
  testPrecondition( interaction_subshell != INVALID_SUBSHELL );
  testPrecondition( interaction_subshell != UNKNOWN_SUBSHELL );
  // Make sure the subshell occupancy is valid
  testPrecondition( num_electrons_in_subshell > 0.0 );
  // Make sure the occupation number is valid
  testPrecondition( !occupation_number.is_null() );
  testPrecondition( occupation_number->getLowerBoundOfIndepVar() == -1.0 );
  // Make sure the Compton profile is valid
  testPrecondition( !compton_profile->is_null() );
  testPrecondition( compton_profile->getLowerBoundOfMomentum() ==
                    -1.0*Utility::Units::mec_momentum );
  testPrecondition( compton_profile->getUpperBoundOfMomentum() >=
                    1.0*Utility::Units::mec_momentum );
}

// Sample an outgoing energy and direction from the distribution
void DopplerBroadenedSubshellIncoherentAdjointPhotonScatteringDistribution::sample(
                                       const double incoming_energy,
                                       double& outgoing_energy,
                                       double& scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( incoming_energy <= this->getMaxEnergy() - this->getBindingEnergy() );

  unsigned trial_dummy;

  return this->sampleAndRecordTrials( incoming_energy,
                                      outgoing_energy,
                                      scattering_angle_cosine,
                                      trial_dummy );
}

// Sample an outgoing energy and direction and record the number of trials
void DopplerBroadenedSubshellIncoherentAdjointPhotonScatteringDistribution::sampleAndRecordTrials(
                                               const double incoming_energy,
                                               double& outgoing_energy,
                                               double& scattering_angle_cosine,
                                               unsigned& trials ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( incoming_energy <= this->getMaxEnergy() - this->getBindingEnergy() );

  // Sample the scattering angle
  SubshellIncoherentAdjointPhotonScatteringDistribution::sampleAndRecordTrials(
                                                       incoming_energy,
                                                       outgoing_energy,
                                                       scattering_angle_cosine,
                                                       trials );

  // Calculate the occupation number arguments
  double pz_min, pz_max;
  
  this->calculateOccupationNumberArguments( incoming_energy,
                                            outgoing_energy,
                                            scattering_angle_cosine,
                                            pz_min,
                                            pz_max );

  // Sample the electron momentum projection
  ComptonProfile::MomentumQuantity pz =
    d_compton_profile->sampleInSubrange( pz_max, pz_min );

  // Calculate the doppler broadened adjoint photon energy
  bool energetically_possible;

  calculateDopplerBroadenedEnergyAdjoint( pz,
                                          incoming_energy,
                                          scattering_angle_cosine,
                                          energetically_possible );

  // Make sure the outgoing energy was energetically possible
  testPostcondition( energetically_possible );
}

// Check if an energy is below the scattering window
bool DopplerBroadenedSubshellIncoherentAdjointPhotonScatteringDistribution::isEnergyBelowScatteringWindow(
                                            const double energy_of_interest,
                                            const double initial_energy ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( initial_energy > 0.0 );
  // Make sure the energy of interest is valid
  testPrecondition( energy_of_interest >= 0.0 );

  // As long as the initial energy is valid (> 0.0) it will be above the
  // the scattering window lower bound.
  return false;
}

// Create a probe particle
void DopplerBroadenedSubshellIncoherentAdjointPhotonScatteringDistribution::createProbeParticle(
                                      const double energy_of_interest, 
                                      const AdjointPhotonState& adjoint_photon,
                                      ParticleBank& bank ) const
{
  // Make sure the energy of interest is valid
  testPrecondition( energy_of_interest > 0.0 );
  testPrecondition( energy_of_interest <= d_max_energy );
  // Make sure the adjoint photon energy is valid
  testPrecondition( adjoint_photon.getEnergy() <= d_max_energy - this->getBindingEnergy() );
  // Make sure the energy of interest is in the scattering window
  testPrecondition( this->isEnergyInScatteringWindow( 
						energy_of_interest,
						adjoint_photon.getEnergy() ) );

  // Only generate the probe if the energy is in the scattering window
  if( this->isEnergyInScatteringWindow( energy_of_interest,
                                        adjoint_photon.getEnergy() ) )
  {
    // Sample the scattering angle
    double adjoint_compton_line_energy, scattering_angle_cosine;
    
    SubshellIncoherentAdjointPhotonScatteringDistribution::sample(
                                                   adjoint_photon.getEnergy(),
                                                   adjoint_compton_line_energy,
                                                   scattering_angle_cosine );

    // Evaluate the adjoint occupation number
    const double adjoint_occupation_number =
      this->evaluateAdjointOccupationNumber( adjoint_photon.getEnergy(),
                                             energy_of_interest,
                                             scattering_angle_cosine );
    
    // Calculate pz corresponding to the energy of interest
    const ComptonProfile::MomentumQuantity pz;
    Utility::setQuantity( pz, calculateElectronMomentumProjectionAdjoint(
                                                    adjoint_photon.getEnergy(),
                                                    energy_of_interest,
                                                    scattering_angle_cosine ));

    // Calculate the pdf conversion value
    const double pdf_conversion =
      adjoint_photon.getEnergy()/
      (adjoint_compton_line_energy*
       Utility::PhysicalConstants::electron_rest_mass_energy*
       sqrt( energy_of_interest*energy_of_interest +
             adjoint_photon.getEnergy()*adjoint_photon.getEnergy() -
             2*energy_of_interest*adjoint_photon.getEnergy()*
             scattering_angle_cosine ));
    
    // Calculate the probe weight multiplier
    const double weight_mult = pdf_conversion*
      (d_compton_profile.evaluate( pz ).value()/adjoint_occupation_number);

    // Create the probe with the desired energy and modified weight
    Teuchos::RCP<AdjointPhotonProbe> probe(
                                    new AdjointPhotonProbe( adjoint_photon ) );

    probe->setEnergy( energy_of_interest );
    probe->rotateDirection( scattering_angle_cosine,
                            this->sampleAzimuthalAngle() );
    probe->multiplyWeight( weight_mult );
    probe->activate();

    // Add the probe to the bank
    bank.push( probe );
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_DopplerBroadenedSubshellIncoherentAdjointPhotonScatteringDistribution.hpp
//---------------------------------------------------------------------------//
