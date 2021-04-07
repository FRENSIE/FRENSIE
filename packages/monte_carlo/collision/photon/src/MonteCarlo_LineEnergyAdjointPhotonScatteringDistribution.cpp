//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_LineEnergyAdjointPhotonScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  The line energy adjoint photon scattering distribution
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_LineEnergyAdjointPhotonScatteringDistribution.hpp"
#include "MonteCarlo_AdjointPhotonProbeState.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
LineEnergyAdjointPhotonScatteringDistribution::LineEnergyAdjointPhotonScatteringDistribution(
                 const double line_energy,
                 const double energy_dist_norm_constant,
                 const std::shared_ptr<const Utility::TabularUnivariateDistribution>&
                 energy_dist )
  : d_line_energy( line_energy ),
    d_energy_dist_norm_constant( energy_dist_norm_constant ),
    d_energy_dist( energy_dist ),
    d_critical_line_energies( new std::vector<double>( 1, 0.0 ) )
{
  // Make sure the line energy is valid
  testPrecondition( line_energy > 0.0 );
  // Make sure the norm constant is valid
  testPrecondition( energy_dist_norm_constant > 0.0 );
  // Make sure the energy dist is valid
  testPrecondition( energy_dist != NULL );
}

// Set the critical line energies
void LineEnergyAdjointPhotonScatteringDistribution::setCriticalLineEnergies(
                             const std::shared_ptr<const std::vector<double> >&
                             critical_line_energies )
{
  // Make sure the critical line energies are valid
  testPrecondition( critical_line_energies.get() );
  testPrecondition( critical_line_energies->size() > 0 );
  testPrecondition( Utility::Sort::isSortedAscending(
					     critical_line_energies->begin(),
					     critical_line_energies->end() ) );
  
  d_critical_line_energies = critical_line_energies;
}

// Get the critical line energies
const std::vector<double>& LineEnergyAdjointPhotonScatteringDistribution::getCriticalLineEnergies() const
{
  return *d_critical_line_energies;
}

// Get the max energy
double LineEnergyAdjointPhotonScatteringDistribution::getMaxEnergy() const
{
  return d_energy_dist->getUpperBoundOfIndepVar();
}

// Return the line energy
double LineEnergyAdjointPhotonScatteringDistribution::getLineEnergy() const
{
  return d_line_energy;
}

// Return the minimum outgoing energy
double LineEnergyAdjointPhotonScatteringDistribution::getMinOutgoingEnergy() const
{
  return d_energy_dist->getLowerBoundOfIndepVar();
}

// Return the maximum outgoing energy
double LineEnergyAdjointPhotonScatteringDistribution::getMaxOutgoingEnergy() const
{
  return d_energy_dist->getUpperBoundOfIndepVar();
}

// Evaluate the distribution (differential in scattering angle cosine)
double LineEnergyAdjointPhotonScatteringDistribution::evaluate(
                                   const double incoming_energy,
                                   const double scattering_angle_cosine ) const
{
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );
  
  if( incoming_energy == d_line_energy )
    return 0.5*d_energy_dist_norm_constant;
  else
    return 0.0;
}

// Evaluate the distribution (double differential)
double LineEnergyAdjointPhotonScatteringDistribution::evaluate(
                                   const double incoming_energy,
                                   const double outgoing_energy,
                                   const double scattering_angle_cosine ) const
{
  // Make sure the outgoing energy is valid
  testPrecondition( outgoing_energy >= incoming_energy );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  if( incoming_energy == d_line_energy )
    return 0.5*d_energy_dist->evaluate( outgoing_energy );
  else
    return 0.0;
}

// Evaluate the Marginal PDF (differential in scattering angle cosine)
double LineEnergyAdjointPhotonScatteringDistribution::evaluatePDF(
                                   const double incoming_energy,
                                   const double scattering_angle_cosine ) const
{
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );
  
  if( incoming_energy == d_line_energy )
    return 0.5;
  else
    return 0.0;
}

// Evaluate the Marginal PDF (differential in outgoing energy)
double LineEnergyAdjointPhotonScatteringDistribution::evaluateEnergyPDF(
                                           const double incoming_energy,
                                           const double outgoing_energy ) const
{
  // Make sure the outgoing energy is valid
  testPrecondition( outgoing_energy >= incoming_energy );

  if( incoming_energy == d_line_energy )
    return d_energy_dist->evaluatePDF( outgoing_energy );
  else
    return 0.0;
}

// Evaluate the Joint PDF
double LineEnergyAdjointPhotonScatteringDistribution::evaluateJointPDF(
                                   const double incoming_energy,
                                   const double outgoing_energy,
                                   const double scattering_angle_cosine ) const
{
  // Make sure the outgoing energy is valid
  testPrecondition( outgoing_energy >= incoming_energy );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  if( incoming_energy == d_line_energy )
    return 0.5*d_energy_dist->evaluatePDF( outgoing_energy );
  else
    return 0.0;
}

// Evaluate the integrated cross section (b)
double LineEnergyAdjointPhotonScatteringDistribution::evaluateIntegratedCrossSection(
                                                 const double incoming_energy,
                                                 const double precision ) const
{
  if( incoming_energy == d_line_energy )
    return d_energy_dist_norm_constant;
  else
    return 0.0;
}

// Sample an outgoing energy and direction from the distribution
void LineEnergyAdjointPhotonScatteringDistribution::sample(
                                        const double incoming_energy,
                                        double& outgoing_energy,
                                        double& scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy == d_line_energy );

  this->sample( outgoing_energy, scattering_angle_cosine );
}

// Sample an outgoing energy and direction from the distribution
void LineEnergyAdjointPhotonScatteringDistribution::sample(
                                        double& outgoing_energy,
                                        double& scattering_angle_cosine ) const
{
  // Sample the outgoing energy from the energy distribution
  outgoing_energy = d_energy_dist->sample();
  
  // Sample a uniformly distributed outgoing scattering angle cosine
  scattering_angle_cosine = this->samplePolarScatteringAngleCosine();
}

// Sample an outgoing energy and direction and record the number of trials
void LineEnergyAdjointPhotonScatteringDistribution::sampleAndRecordTrials(
                                               const double incoming_energy,
                                               double& outgoing_energy,
                                               double& scattering_angle_cosine,
                                               Counter& trials ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy == d_line_energy );

  this->sample( outgoing_energy, scattering_angle_cosine );

  ++trials;
}

// Sample an outgoing energy and direction and record the number of trials
void LineEnergyAdjointPhotonScatteringDistribution::sampleAndRecordTrials(
                                               double& outgoing_energy,
                                               double& scattering_angle_cosine,
                                               Counter& trials ) const
{
  this->sample( outgoing_energy, scattering_angle_cosine );

  ++trials;
}

// Sample the polar scattering angle cosine
double LineEnergyAdjointPhotonScatteringDistribution::samplePolarScatteringAngleCosine() const
{
  return Utility::UniformDistribution::sample( -1.0, 1.0 );
}

// Randomly scatter the photon and return the shell that was interacted with
void LineEnergyAdjointPhotonScatteringDistribution::scatterAdjointPhoton(
                               AdjointPhotonState& adjoint_photon,
                               ParticleBank& bank,
                               Data::SubshellType& shell_of_interaction ) const
{
  if( adjoint_photon.getEnergy() == d_line_energy )
  {
    // Generate probe particles
    this->createProbeParticles( adjoint_photon, bank );
    
    // Scatter the adjoint photon
    double outgoing_energy, scattering_angle_cosine;

    this->sample( outgoing_energy, scattering_angle_cosine );

    adjoint_photon.setEnergy( outgoing_energy );

    adjoint_photon.rotateDirection( scattering_angle_cosine,
                                    this->sampleAzimuthalAngle() );
  }

  shell_of_interaction = Data::UNKNOWN_SUBSHELL;
}

// Create the probe particles
void LineEnergyAdjointPhotonScatteringDistribution::createProbeParticles(
                                      const AdjointPhotonState& adjoint_photon,
                                      ParticleBank& bank ) const
{
  const double min_critical_line_energy =
    d_energy_dist->getLowerBoundOfIndepVar();
  
  for( size_t i = 0; i < d_critical_line_energies->size(); ++i )
  {
    if( (*d_critical_line_energies)[i] > min_critical_line_energy )
    {
      const double weight_mult =
        d_energy_dist->evaluatePDF( (*d_critical_line_energies)[i] );

      // Create a probe with the desired energy and modified weight
      std::shared_ptr<AdjointPhotonProbeState> probe(
                               new AdjointPhotonProbeState( adjoint_photon ) );

      probe->setEnergy( (*d_critical_line_energies)[i] );
      probe->rotateDirection( this->samplePolarScatteringAngleCosine(),
                              this->sampleAzimuthalAngle() );
      probe->multiplyWeight( weight_mult );
      probe->activate();

      // Add the probe to the bank
      bank.push( probe );
    }
  }
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_LineEnergyAdjointPhotonScatteringDistribution.cpp
//---------------------------------------------------------------------------//
