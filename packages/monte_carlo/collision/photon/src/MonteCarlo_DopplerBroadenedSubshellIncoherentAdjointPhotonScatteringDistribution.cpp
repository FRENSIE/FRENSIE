//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DopplerBroadenedSubshellIncoherentAdjointPhotonScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The doppler broadened subshell adjoint incoherent photon scattering
//!         distribution definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_DopplerBroadenedSubshellIncoherentAdjointPhotonScatteringDistribution.hpp"
#include "MonteCarlo_AdjointPhotonProbeState.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
DopplerBroadenedSubshellIncoherentAdjointPhotonScatteringDistribution::DopplerBroadenedSubshellIncoherentAdjointPhotonScatteringDistribution(
     const double max_energy,
     const Data::SubshellType interaction_subshell,
     const double num_electrons_in_subshell,
     const double binding_energy,
     const std::shared_ptr<const OccupationNumber>& occupation_number,
     const std::shared_ptr<const ComptonProfile>& compton_profile,
     const AdjointKleinNishinaSamplingType sampling_type )
  : SubshellIncoherentAdjointPhotonScatteringDistribution(
                                                     max_energy,
                                                     interaction_subshell,
                                                     num_electrons_in_subshell,
                                                     binding_energy,
                                                     occupation_number,
                                                     sampling_type ),
    d_compton_profile( compton_profile )
{
  // Make sure the binding energy is valid
  testPrecondition( binding_energy > 0.0 );
  // Make sure the max energy is valid
  testPrecondition( max_energy > binding_energy );
  // Make sure the interaction subshell is valid
  testPrecondition( interaction_subshell != Data::INVALID_SUBSHELL );
  testPrecondition( interaction_subshell != Data::UNKNOWN_SUBSHELL );
  // Make sure the subshell occupancy is valid
  testPrecondition( num_electrons_in_subshell > 0.0 );
  // Make sure the occupation number is valid
  testPrecondition( occupation_number.get() );
  testPrecondition( occupation_number->getLowerBoundOfMomentum() ==
                    -1.0*Utility::Units::mec_momentum );
  // Make sure the Compton profile is valid
  testPrecondition( compton_profile.get() );
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
  testPrecondition( incoming_energy <= this->getMaxEnergy() - this->getSubshellBindingEnergy() );

  Counter trial_dummy;

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
                                               Counter& trials ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( incoming_energy <= this->getMaxEnergy() - this->getSubshellBindingEnergy() );

  // Sample the scattering angle
  SubshellIncoherentAdjointPhotonScatteringDistribution::sampleAndRecordTrials(
                                                       incoming_energy,
                                                       outgoing_energy,
                                                       scattering_angle_cosine,
                                                       trials );

  // Calculate the occupation number arguments
  ComptonProfile::MomentumQuantity pz_min, pz_max;

  {
    double raw_pz_min, raw_pz_max;

    this->calculateOccupationNumberArguments( incoming_energy,
                                              this->getMaxEnergy(),
                                              scattering_angle_cosine,
                                              raw_pz_min,
                                              raw_pz_max );

    pz_min = raw_pz_min*Utility::Units::mec_momentum;
    pz_max = raw_pz_max*Utility::Units::mec_momentum;
  }

  // Sample the electron momentum projection
  ComptonProfile::MomentumQuantity pz =
    d_compton_profile->sampleInSubrange( pz_max, pz_min );

  // Calculate the doppler broadened adjoint photon energy
  bool energetically_possible;

  outgoing_energy =
    calculateDopplerBroadenedEnergyAdjoint( pz.value(),
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

// Check if the cross section is non-zero
bool DopplerBroadenedSubshellIncoherentAdjointPhotonScatteringDistribution::isCrossSectionNonZero(
                                   const double incoming_energy,
                                   const double max_energy,
                                   const double ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( incoming_energy <= max_energy );

  return incoming_energy < max_energy - this->getSubshellBindingEnergy();
}

// Create a probe particle
void DopplerBroadenedSubshellIncoherentAdjointPhotonScatteringDistribution::createProbeParticle(
                                      const double energy_of_interest,
                                      const AdjointPhotonState& adjoint_photon,
                                      ParticleBank& bank ) const
{
  // Make sure the energy of interest is valid
  testPrecondition( energy_of_interest > 0.0 );
  testPrecondition( energy_of_interest <= this->getMaxEnergy() );
  // Make sure the adjoint photon energy is valid
  testPrecondition( adjoint_photon.getEnergy() <=
                    this->getMaxEnergy() - this->getSubshellBindingEnergy() );
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
                                             this->getMaxEnergy(),
                                             scattering_angle_cosine );

    // Calculate pz corresponding to the energy of interest
    ComptonProfile::MomentumQuantity pz;
    Utility::setQuantity( pz, calculateElectronMomentumProjectionAdjoint(
                                                    adjoint_photon.getEnergy(),
                                                    energy_of_interest,
                                                    scattering_angle_cosine ));

    // Calculate the pdf conversion value
    const double pdf_conversion =
      adjoint_photon.getEnergy()/
      (adjoint_compton_line_energy*
       sqrt( energy_of_interest*energy_of_interest +
             adjoint_photon.getEnergy()*adjoint_photon.getEnergy() -
             2*energy_of_interest*adjoint_photon.getEnergy()*
             scattering_angle_cosine ));

    // Calculate the probe weight multiplier
    double weight_mult = pdf_conversion*
      (d_compton_profile->evaluate( pz ).value()/adjoint_occupation_number);

    // If the pz value is very large, the Compton profile will evaluate to 0.0.
    // Set the weight to 1e-15 when this occurs
    if( weight_mult == 0.0 )
      weight_mult = 1e-15;

    // Create the probe with the desired energy and modified weight
    std::shared_ptr<AdjointPhotonProbeState> probe(
                               new AdjointPhotonProbeState( adjoint_photon ) );

    probe->setEnergy( energy_of_interest );
    probe->rotateDirection( scattering_angle_cosine,
                            this->sampleAzimuthalAngle() );
    probe->multiplyWeight( weight_mult );
    probe->activate();

    // Add the probe to the bank
    bank.push( probe );
  }
}

// Calculate the occupation number arguments
double DopplerBroadenedSubshellIncoherentAdjointPhotonScatteringDistribution::calculateOccupationNumberArguments(
                                          const double incoming_energy,
                                          const double max_energy,
                                          const double scattering_angle_cosine,
                                          double& pz_min,
                                          double& pz_max ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( incoming_energy <= max_energy - this->getSubshellBindingEnergy() );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >=
                    calculateMinScatteringAngleCosine( incoming_energy, max_energy ) );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  pz_max = calculateMaxElectronMomentumProjectionAdjoint(
                                                     incoming_energy,
                                                     this->getSubshellBindingEnergy(),
                                                     scattering_angle_cosine );

  pz_min = calculateMinElectronMomentumProjectionAdjoint(
                                                     incoming_energy,
                                                     max_energy,
                                                     scattering_angle_cosine );

  // Note: pz_max has no bound. We therefore limit it to the maximum pz
  // stored in the occupation number grid. If pz_max is very large, pz_min
  // can also be very large (especially at small scattering angles) but can
  // never be larger than pz_max. Because we are limiting pz_max we must
  // also limit pz_min.
  if( pz_min > pz_max )
    pz_min = pz_max;
}

// Evaluate the occupation number
double DopplerBroadenedSubshellIncoherentAdjointPhotonScatteringDistribution::evaluateAdjointOccupationNumber(
                                   const double incoming_energy,
                                   const double max_energy,
                                   const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( incoming_energy <= max_energy - this->getSubshellBindingEnergy() );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >=
                    calculateMinScatteringAngleCosine( incoming_energy, max_energy ) );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  // Evaluate the occupation number at pz_max and pz_min
  double pz_min, pz_max;

  this->calculateOccupationNumberArguments( incoming_energy,
                                            max_energy,
                                            scattering_angle_cosine,
                                            pz_min,
                                            pz_max );
  
  const double upper_occupation_number_value =
    this->evaluateOccupationNumber( pz_max );

  const double lower_occupation_number_value =
    this->evaluateOccupationNumber( pz_min );

  // Evaluate the adjoint occupation number
  double adjoint_occupation_number =
    upper_occupation_number_value - lower_occupation_number_value;

  // Due to floating-point roundoff, it is possible for the adjoint
  // occupation number to be slightly outside of [0,1]. When this occurs,
  // manually set to 0 or 1.
  if( adjoint_occupation_number < 0.0 )
    adjoint_occupation_number = 0.0;
  else if( adjoint_occupation_number > 1.0 )
    adjoint_occupation_number = 1.0;

  // Make sure the adjoint occupation number is valid
  testPrecondition( adjoint_occupation_number >= 0.0 );
  testPrecondition( adjoint_occupation_number <= 1.0 );

  return adjoint_occupation_number;
}

// Evaluate the max adjoint occupation number
/*! \details It's not clear how to determine the scattering angle cosine that
 * corresponds to the max adjoint occupation number. To be safe, we will always
 * return the absolute maximum adjoint occupation number of 1.0.
 */
double DopplerBroadenedSubshellIncoherentAdjointPhotonScatteringDistribution::evaluateMaxAdjointOccupationNumber(
                                                           const double,
                                                           const double ) const
{
  return 1.0;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_DopplerBroadenedSubshellIncoherentAdjointPhotonScatteringDistribution.hpp
//---------------------------------------------------------------------------//
