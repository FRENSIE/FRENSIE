//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroionizationSubshellElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  The electron subshell electroionization scattering distribution definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistribution.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "Utility_DirectionHelpers.hpp"
#include "Utility_KinematicHelpers.hpp"

namespace MonteCarlo{
// Constructor
ElectroionizationSubshellElectronScatteringDistribution::ElectroionizationSubshellElectronScatteringDistribution(
    const ElectroionizationSubshellDistribution&
      electroionization_subshell_scattering_distribution,
    const double& binding_energy )
  : d_electroionization_subshell_scattering_distribution(
      electroionization_subshell_scattering_distribution ),
    d_binding_energy( binding_energy )
{
  // Make sure the arraies are valid
  testPrecondition( d_electroionization_subshell_scattering_distribution.size() > 0 );
}

// Return the binding energy
double ElectroionizationSubshellElectronScatteringDistribution::getBindingEnergy() const
{
  return d_binding_energy;
}

// Return the max secondary (knock-on) electron energy for a given incoming electron energy
double ElectroionizationSubshellElectronScatteringDistribution::getMaxSecondaryEnergyAtIncomingEnergy(
        const double energy ) const
{
  ElectroionizationSubshellDistribution::const_iterator 
    lower_distribution, upper_distribution;

  MonteCarlo::findLowerAndUpperBinBoundary(
    energy,
    d_electroionization_subshell_scattering_distribution,
    lower_distribution,
    upper_distribution );

  if( lower_distribution != upper_distribution )
  {
    return InterpolationPolicy::interpolate(
            lower_distribution->first,
            upper_distribution->first,
            energy,
            lower_distribution->second->sampleWithRandomNumber( 1.0 ),
            upper_distribution->second->sampleWithRandomNumber( 1.0 ) );
  }
  else
  {
    return upper_distribution->second->sampleWithRandomNumber( 1.0 );
  }
}

// Evaluate the PDF value for a given incoming and knock-on energy (efficient)
double ElectroionizationSubshellElectronScatteringDistribution::evaluatePDF(
                    const unsigned lower_bin_index,
                    const double incoming_energy,
                    const double knock_on_energy ) const
{
  // Make sure the energies are valid
  testPrecondition( lower_bin_index >= 0 );
  testPrecondition( lower_bin_index <
                    d_electroionization_subshell_scattering_distribution.size() );
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( knock_on_energy > 0.0 );

  return MonteCarlo::evaluateTwoDDistributionCorrelatedPDF<ElectroionizationSubshellDistribution, InterpolationPolicy>(
            lower_bin_index,
            incoming_energy,
            knock_on_energy,
            d_electroionization_subshell_scattering_distribution );
}

// Evaluate the PDF value for a given incoming and knock-on energy
double ElectroionizationSubshellElectronScatteringDistribution::evaluatePDF(
                     const double incoming_energy,
                     const double knock_on_energy ) const
{
  // Make sure the energies are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( knock_on_energy > 0.0 );
  testPrecondition( incoming_energy > knock_on_energy );

  return MonteCarlo::evaluateTwoDDistributionCorrelatedPDF<ElectroionizationSubshellDistribution, InterpolationPolicy>(
                         incoming_energy,
                         knock_on_energy,
                         d_electroionization_subshell_scattering_distribution );
}

// Sample an knock on energy and direction from the distribution
void ElectroionizationSubshellElectronScatteringDistribution::sample(
               const double incoming_energy,
               double& knock_on_energy,
               double& knock_on_angle_cosine ) const
{
  // Sample knock-on electron energy
  knock_on_energy =
    sampleTwoDDistributionCorrelated<ElectroionizationSubshellDistribution>(
                         incoming_energy,
                         d_electroionization_subshell_scattering_distribution );

  // Calculate the outgoing angle cosine for the knock on electron
  knock_on_angle_cosine = outgoingAngle( incoming_energy,
                                         knock_on_energy );
}

// Sample an knock on energy and direction from the distribution
void ElectroionizationSubshellElectronScatteringDistribution::sample(
               const double incoming_energy,
               double& outgoing_energy,
               double& knock_on_energy,
               double& scattering_angle_cosine,
               double& knock_on_angle_cosine ) const
{
  // Sample knock-on electron energy and outgoing angle
  sample( incoming_energy, knock_on_energy, knock_on_angle_cosine );

  outgoing_energy =
        std::max( 1e-15, incoming_energy - knock_on_energy - d_binding_energy );

  // Calculate the outgoing angle cosine for the primary electron
  scattering_angle_cosine = outgoingAngle( incoming_energy,
                                           outgoing_energy );
}

// Sample an knock on energy and direction and record the number of trials
void ElectroionizationSubshellElectronScatteringDistribution::sampleAndRecordTrials(
                              const double incoming_energy,
                              double& knock_on_energy,
                              double& knock_on_angle_cosine,
                              unsigned& trials ) const
{
  trials++;

  sample( incoming_energy, knock_on_energy, knock_on_angle_cosine );
}

// Randomly scatter the electron
void ElectroionizationSubshellElectronScatteringDistribution::scatterElectron(
                                ElectronState& electron,
			                    ParticleBank& bank,
                                Data::SubshellType& shell_of_interaction ) const
{
  // The energy of the outgoing and knock-on electron
  double outgoing_energy, knock_on_energy;

  // The angle cosine of the outgoing and knock-on electron
  double scattering_angle_cosine, knock_on_angle_cosine;

  // Sample the distribution
  sample( electron.getEnergy(),
          outgoing_energy,
          knock_on_energy,
          scattering_angle_cosine,
          knock_on_angle_cosine );

  // Create new elecrton
  Teuchos::RCP<ElectronState> knock_on_electron(
                           new ElectronState( electron, true, true ) );

  // Set knock-on electron energy
  knock_on_electron->setEnergy( knock_on_energy );


  // Set the direction of the knock-on electron
  knock_on_electron->rotateDirection( knock_on_angle_cosine,
			                          this->sampleAzimuthalAngle() );

  // Bank the knock-on electron
  bank.push( knock_on_electron );


  // Set the outgoing electron energy
  electron.setEnergy( outgoing_energy );

  // Set the new direction of the primary electron
  electron.rotateDirection( scattering_angle_cosine,
                            this->sampleAzimuthalAngle() );

  // Increment the electron generation number
  electron.incrementGenerationNumber();
}

// Calculate the outgoing angle cosine
double ElectroionizationSubshellElectronScatteringDistribution::outgoingAngle(
                                            const double incoming_energy,
                                            const double outgoing_energy ) const
{
  // The normalized incoming electron energy
  double normalized_incoming_energy =
          incoming_energy/Utility::PhysicalConstants::electron_rest_mass_energy;

  // The ratio of incoming to outgoing energy
  double energy_ratio = outgoing_energy/incoming_energy;

  // Randomly select the plane of scattering
  return sqrt( energy_ratio*( normalized_incoming_energy + 2.0 )/
             ( energy_ratio*normalized_incoming_energy + 2.0 ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
