//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroionizationSubshellAdjointElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  The adjoint electron subshell electroionization scattering distribution definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ElectroionizationSubshellAdjointElectronScatteringDistribution.hpp"
#include "MonteCarlo_KinematicHelpers.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"

namespace MonteCarlo{

// Constructor
ElectroionizationSubshellAdjointElectronScatteringDistribution::ElectroionizationSubshellAdjointElectronScatteringDistribution(
    const std::shared_ptr<const BasicBivariateDist>&
        electroionization_subshell_distribution,
    const double& binding_energy )
  : d_ionization_subshell_dist( electroionization_subshell_distribution ),
    d_binding_energy( binding_energy )
{
  // Make sure the arrays are valid
  testPrecondition( d_ionization_subshell_dist.use_count() > 0 );
  testPrecondition( binding_energy > 0.0 );
}

// Return the binding energy
double ElectroionizationSubshellAdjointElectronScatteringDistribution::getBindingEnergy() const
{
  return d_binding_energy;
}

// Evaluate the distribution for a given incoming and outgoing energy
double ElectroionizationSubshellAdjointElectronScatteringDistribution::evaluate(
                     const double incoming_energy,
                     const double outgoing_energy ) const
{
  // Make sure the energies are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( outgoing_energy > incoming_energy );

  // evaluate the distribution
  return d_ionization_subshell_dist->evaluate(
            incoming_energy, outgoing_energy );
}

// Evaluate the PDF value for a given incoming and outgoing energy
double ElectroionizationSubshellAdjointElectronScatteringDistribution::evaluatePDF(
                     const double incoming_energy,
                     const double outgoing_energy ) const
{
  // Make sure the energies are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( outgoing_energy > incoming_energy );

  // evaluate the distribution
  return d_ionization_subshell_dist->evaluateSecondaryConditionalPDF(
            incoming_energy, outgoing_energy );
}

// Evaluate the CDF value for a given incoming and outgoing energy
double ElectroionizationSubshellAdjointElectronScatteringDistribution::evaluateCDF(
                     const double incoming_energy,
                     const double outgoing_energy ) const
{
  // Make sure the energies are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( outgoing_energy > incoming_energy );

  // evaluate the distribution
  return d_ionization_subshell_dist->evaluateSecondaryConditionalCDF(
            incoming_energy, outgoing_energy );
}


// Sample an knock on energy and direction from the distribution
void ElectroionizationSubshellAdjointElectronScatteringDistribution::sample(
               const double incoming_energy,
               double& outgoing_energy,
               double& outgoing_angle_cosine ) const
{
  // Sample knock-on electron energy
  outgoing_energy =
      d_ionization_subshell_dist->sampleSecondaryConditional( incoming_energy );

  // Calculate the outgoing angle cosine for the knock on electron
  outgoing_angle_cosine = outgoingAngle( incoming_energy, outgoing_energy );
}

// Sample an knock on energy and direction and record the number of trials
void ElectroionizationSubshellAdjointElectronScatteringDistribution::sampleAndRecordTrials(
                              const double incoming_energy,
                              double& outgoing_energy,
                              double& outgoing_angle_cosine,
                              Counter& trials ) const
{
  trials++;

  this->sample( incoming_energy, outgoing_energy, outgoing_angle_cosine );
}

// Randomly scatter the electron
void ElectroionizationSubshellAdjointElectronScatteringDistribution::scatterAdjointElectron(
        AdjointElectronState& electron,
        ParticleBank& bank,
        Data::SubshellType& shell_of_interaction ) const
{
  // The energy and angle cosine of the outgoing electron
  double outgoing_energy, scattering_angle_cosine;

  // Sample the distribution
  this->sample( electron.getEnergy(), outgoing_energy, scattering_angle_cosine );

  // Set the outgoing electron energy
  electron.setEnergy( outgoing_energy );

  // Set the new direction of the primary electron
  electron.rotateDirection( scattering_angle_cosine,
                            this->sampleAzimuthalAngle() );
}

// Calculate the outgoing angle cosine
double ElectroionizationSubshellAdjointElectronScatteringDistribution::outgoingAngle(
                                            const double incoming_energy,
                                            const double outgoing_energy ) const
{
  // The normalized outgoing electron energy
  double normalized_outgoing_energy =
          outgoing_energy/Utility::PhysicalConstants::electron_rest_mass_energy;

  // The ratio of outgoing to incoming energy
  double energy_ratio = incoming_energy/outgoing_energy;

  // Calculate the plane of scattering
  return sqrt( energy_ratio*( normalized_outgoing_energy + 2.0 )/
             ( energy_ratio*normalized_outgoing_energy + 2.0 ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationAdjointElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
