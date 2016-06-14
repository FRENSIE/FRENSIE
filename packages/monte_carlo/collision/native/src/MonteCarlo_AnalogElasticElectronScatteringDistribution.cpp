//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AnalogElasticElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  The electron analog elastic scattering distribution definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "MonteCarlo_AnalogElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_TwoDDistributionHelpers.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_DirectionHelpers.hpp"
#include "Utility_KinematicHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_ElasticElectronDistribution.hpp"

namespace MonteCarlo{

// Constructor
AnalogElasticElectronScatteringDistribution::AnalogElasticElectronScatteringDistribution(
    const ElasticDistribution& elastic_scattering_distribution,
    const double upper_cutoff_angle_cosine )
  : d_elastic_scattering_distribution( elastic_scattering_distribution ),
    d_upper_cutoff_angle_cosine( upper_cutoff_angle_cosine )
{
  // Make sure the array is valid
  testPrecondition( d_elastic_scattering_distribution.size() > 0 );
  // Make sure the upper cutoff angle cosine is valid
  testPrecondition( upper_cutoff_angle_cosine >= -1.0 );
  testPrecondition( upper_cutoff_angle_cosine <= 1.0 );
}

// Evaluate the distribution
double AnalogElasticElectronScatteringDistribution::evaluate(
    const double incoming_energy,
    const double scattering_angle_cosine ) const
{
  // Make sure the energy and angle cosine are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  return MonteCarlo::evaluateTwoDDistributionCorrelated(
                        incoming_energy,
                        scattering_angle_cosine,
                        d_elastic_scattering_distribution );
}

// Evaluate the distribution
double AnalogElasticElectronScatteringDistribution::evaluate(
    const unsigned incoming_energy_bin,
    const double scattering_angle_cosine ) const
{
  // Make sure the energy and angle cosine are valid
  testPrecondition( incoming_energy_bin <
                    d_elastic_scattering_distribution.size() );
  testPrecondition( incoming_energy_bin >= 0 );
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  double pdf =
    d_elastic_scattering_distribution[incoming_energy_bin].second->evaluate(
        scattering_angle_cosine );

  return pdf;
}

// Evaluate the PDF
double AnalogElasticElectronScatteringDistribution::evaluatePDF(
                            const double incoming_energy,
                            const double scattering_angle_cosine ) const
{
  // Make sure the energy and angle cosine are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  return MonteCarlo::evaluateTwoDDistributionCorrelatedPDF(
                         incoming_energy,
                         scattering_angle_cosine,
                         d_elastic_scattering_distribution );
}

// Evaluate the PDF
double AnalogElasticElectronScatteringDistribution::evaluatePDF(
    const unsigned incoming_energy_bin,
    const double scattering_angle_cosine ) const
{
  // Make sure the energy and angle cosine are valid
  testPrecondition( incoming_energy_bin <
                    d_elastic_scattering_distribution.size() );
  testPrecondition( incoming_energy_bin >= 0 );
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  double pdf =
    d_elastic_scattering_distribution[incoming_energy_bin].second->evaluatePDF(
      scattering_angle_cosine );

  return pdf;
}

// Evaluate the CDF
double AnalogElasticElectronScatteringDistribution::evaluateCDF(
      const double incoming_energy,
      const double scattering_angle_cosine ) const
{
  // Make sure the energy and angle cosine are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  return MonteCarlo::evaluateTwoDDistributionCorrelatedCDF(
                        incoming_energy,
                        scattering_angle_cosine,
                        d_elastic_scattering_distribution );
}

// Evaluate the cross section ratio for the cutoff angle
double AnalogElasticElectronScatteringDistribution::evaluateCutoffCrossSectionRatio(
        const double incoming_energy ) const
{
  double cross_section_ratio = 0.0;

  // Get the max cdf value
  double max_cdf = evaluateCDF( incoming_energy, 1.0 );

  // Get the cdf at the cutoff
  double cutoff_cdf = evaluateCDF( incoming_energy, d_upper_cutoff_angle_cosine );

  // Make sure the cdf values are valid
  testPostcondition( max_cdf >= cutoff_cdf );
  testPostcondition( cutoff_cdf >= 0.0 );


  if ( max_cdf > 0.0 )
      cross_section_ratio = cutoff_cdf/max_cdf;

  return cross_section_ratio;
}


// Return the energy at a given energy bin
double AnalogElasticElectronScatteringDistribution::getEnergy(
    const unsigned energy_bin ) const
{
  // Make sure the energy bin is valid
  testPrecondition( energy_bin < d_elastic_scattering_distribution.size() );
  testPrecondition( energy_bin >= 0 );

  return d_elastic_scattering_distribution[energy_bin].first;
}

// Sample an outgoing energy and direction from the distribution
void AnalogElasticElectronScatteringDistribution::sample(
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
void AnalogElasticElectronScatteringDistribution::sampleAndRecordTrials(
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
void AnalogElasticElectronScatteringDistribution::scatterElectron(
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
void AnalogElasticElectronScatteringDistribution::scatterAdjointElectron(
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
void AnalogElasticElectronScatteringDistribution::sampleAndRecordTrialsImpl(
        const double incoming_energy,
        double& scattering_angle_cosine,
        unsigned& trials ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );

  // Increment the number of trials
  ++trials;

  double scaled_random_number;

  // evaluate the cdf value at the upper cutoff angle cosine
  double upper_cutoff_cdf =
          evaluateCDF( incoming_energy, d_upper_cutoff_angle_cosine );

  // scale the random number to only sample below the upper cutoff angle cosine
  scaled_random_number = upper_cutoff_cdf*
      Utility::RandomNumberGenerator::getRandomNumber<double>();

  scattering_angle_cosine =
      sampleTwoDDistributionCorrelatedWithRandomNumber(
          incoming_energy,
          d_elastic_scattering_distribution,
          scaled_random_number );

  // Make sure the scattering angle cosine is valid
  testPostcondition( scattering_angle_cosine >= -1.0 );
  testPostcondition( scattering_angle_cosine <= d_upper_cutoff_angle_cosine );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AnalogElasticElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
