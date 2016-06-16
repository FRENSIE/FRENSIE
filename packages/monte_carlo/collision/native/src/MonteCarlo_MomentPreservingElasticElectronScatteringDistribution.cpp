//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_MomentPreservingElasticElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  The moment preserving electron elastic scattering distribution definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "MonteCarlo_MomentPreservingElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_TwoDDistributionHelpers.hpp"

namespace MonteCarlo{

// Constructor
MomentPreservingElasticElectronScatteringDistribution::MomentPreservingElasticElectronScatteringDistribution(
    const DiscreteElasticDistribution& discrete_scattering_distribution,
    const double cutoff_angle_cosine )
  : d_discrete_scattering_distribution( discrete_scattering_distribution ),
    d_cutoff_angle_cosine( cutoff_angle_cosine )
{
  // Make sure the array is valid
  testPrecondition( d_discrete_scattering_distribution.size() > 0 );
  // Make sure the cutoff angle cosine is valid
  testPostcondition( d_cutoff_angle_cosine >= -1.0 );
  testPostcondition( d_cutoff_angle_cosine < 1.0 );
}


// Evaluate the distribution
double MomentPreservingElasticElectronScatteringDistribution::evaluate(
    const double incoming_energy,
    const double scattering_angle_cosine ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  // evaluate the distribution at the incoming energy and scattering_angle_cosine
  return MonteCarlo::evaluateTwoDDistributionCorrelated<DiscreteElasticDistribution>(
                         incoming_energy,
                         scattering_angle_cosine,
                         d_discrete_scattering_distribution );
}

// Evaluate the distribution
double MomentPreservingElasticElectronScatteringDistribution::evaluate(
                            const unsigned incoming_energy_bin,
                            const double scattering_angle_cosine ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy_bin <
                    d_discrete_scattering_distribution.size() );
  testPrecondition( incoming_energy_bin >= 0 );
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  // evaluate the distribution at the bin and scattering_angle_cosine
  return d_discrete_scattering_distribution[incoming_energy_bin].second->evaluate(
        scattering_angle_cosine );
}

// Evaluate the PDF
double MomentPreservingElasticElectronScatteringDistribution::evaluatePDF(
                            const double incoming_energy,
                            const double scattering_angle_cosine ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  // evaluate the PDF at the incoming energy and scattering_angle_cosine
  return MonteCarlo::evaluateTwoDDistributionCorrelatedPDF<DiscreteElasticDistribution>(
                         incoming_energy,
                         scattering_angle_cosine,
                         d_discrete_scattering_distribution );
}

// Evaluate the PDF
double MomentPreservingElasticElectronScatteringDistribution::evaluatePDF(
                            const unsigned incoming_energy_bin,
                            const double scattering_angle_cosine ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy_bin <
                    d_discrete_scattering_distribution.size() );
  testPrecondition( incoming_energy_bin >= 0 );
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  // evaluate the PDF at the bin and scattering_angle_cosine
  return d_discrete_scattering_distribution[incoming_energy_bin].second->evaluatePDF(
        scattering_angle_cosine );
}

// Evaluate the CDF
double MomentPreservingElasticElectronScatteringDistribution::evaluateCDF(
                            const double incoming_energy,
                            const double scattering_angle_cosine ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  // evaluate the CDF at the incoming energy and scattering_angle_cosine
  return MonteCarlo::evaluateTwoDDistributionCorrelatedCDF<DiscreteElasticDistribution>(
                         incoming_energy,
                         scattering_angle_cosine,
                         d_discrete_scattering_distribution );
}

// Sample an outgoing energy and direction from the distribution
void MomentPreservingElasticElectronScatteringDistribution::sample(
               const double incoming_energy,
               double& outgoing_energy,
               double& scattering_angle_cosine ) const
{
  // The outgoing energy is always equal to the incoming energy
  outgoing_energy = incoming_energy;

  unsigned trial_dummy;

  // Sample an outgoing direction
  this->sampleAndRecordTrialsImpl( incoming_energy,
				                   scattering_angle_cosine,
				                   trial_dummy );
}

// Sample an outgoing energy and direction and record the number of trials
void MomentPreservingElasticElectronScatteringDistribution::sampleAndRecordTrials(
                const double incoming_energy,
                double& outgoing_energy,
                double& scattering_angle_cosine,
                unsigned& trials ) const
{
  // The outgoing energy is always equal to the incoming energy
  outgoing_energy = incoming_energy;

  // Sample an outgoing direction
  this->sampleAndRecordTrialsImpl( incoming_energy,
				                   scattering_angle_cosine,
				                   trials );
}

// Randomly scatter the electron
void MomentPreservingElasticElectronScatteringDistribution::scatterElectron(
                ElectronState& electron,
                ParticleBank& bank,
                Data::SubshellType& shell_of_interaction ) const
{
  double scattering_angle_cosine;

  unsigned trial_dummy;

  // Sample an outgoing direction
  this->sampleAndRecordTrialsImpl( electron.getEnergy(),
				                   scattering_angle_cosine,
				                   trial_dummy );

  shell_of_interaction = Data::UNKNOWN_SUBSHELL;

  // Set the new direction
  electron.rotateDirection( scattering_angle_cosine,
			                this->sampleAzimuthalAngle() );
}

// Randomly scatter the adjoint electron
void MomentPreservingElasticElectronScatteringDistribution::scatterAdjointElectron(
                AdjointElectronState& adjoint_electron,
                ParticleBank& bank,
                Data::SubshellType& shell_of_interaction ) const
{
  double scattering_angle_cosine;

  unsigned trial_dummy;

  // Sample an outgoing direction
  this->sampleAndRecordTrialsImpl( adjoint_electron.getEnergy(),
				                   scattering_angle_cosine,
				                   trial_dummy );

  shell_of_interaction = Data::UNKNOWN_SUBSHELL;

  // Set the new direction
  adjoint_electron.rotateDirection( scattering_angle_cosine,
				                    this->sampleAzimuthalAngle() );
}

// Sample an outgoing direction from the distribution
void MomentPreservingElasticElectronScatteringDistribution::sampleAndRecordTrialsImpl(
                const double incoming_energy,
                double& scattering_angle_cosine,
                unsigned& trials ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );

  // Increment the number of trials
  ++trials;

  scattering_angle_cosine = MonteCarlo::sampleTwoDDistributionCorrelated(
                                incoming_energy,
                                d_discrete_scattering_distribution );

  // Make sure the scattering angle cosine is valid
  testPostcondition( scattering_angle_cosine >= d_cutoff_angle_cosine );
  testPostcondition( scattering_angle_cosine <= 1.0 );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElasticElectronScatteringDistribution.hpp
//---------------------------------------------------------------------------//
