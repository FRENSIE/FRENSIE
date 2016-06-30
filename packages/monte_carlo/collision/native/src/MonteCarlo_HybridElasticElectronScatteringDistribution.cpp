//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_HybridElasticElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  The analog elastic electron scattering distribution definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_HybridElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_TwoDDistributionHelpers.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_DirectionHelpers.hpp"
#include "Utility_KinematicHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"

namespace MonteCarlo{

// Constructor
HybridElasticElectronScatteringDistribution::HybridElasticElectronScatteringDistribution(
    const TwoDDistribution& elastic_cutoff_distribution,
    const DiscreteDistribution& elastic_discrete_distribution,
    const double& cutoff_angle_cosine )
  : d_elastic_cutoff_distribution( elastic_cutoff_distribution ),
    d_elastic_discrete_distribution( elastic_discrete_distribution ),
    d_cutoff_angle_cosine( cutoff_angle_cosine )
{
  // Make sure the arrays are valid
  testPrecondition( d_elastic_cutoff_distribution.size() > 0 );
  testPrecondition( d_elastic_discrete_distribution.size() > 0 );
  // Make sure the cutoff angle cosine is valid
  testPostcondition( d_cutoff_angle_cosine >= -1.0 );
  testPostcondition( d_cutoff_angle_cosine < 1.0 );
}

// Evaluate the distribution at the given energy and scattering angle cosine
/*! \details The cutoff and moment preserving distributions are evaluated 
 *  independently of eachother.
 */
double HybridElasticElectronScatteringDistribution::evaluate(
        const double incoming_energy,
        const double scattering_angle_cosine ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  if ( scattering_angle_cosine <= d_cutoff_angle_cosine )
  {
    return MonteCarlo::evaluateTwoDDistributionCorrelated<TwoDDistribution>(
                         incoming_energy,
                         scattering_angle_cosine,
                         d_elastic_cutoff_distribution );
  }
  else
  {
    return MonteCarlo::evaluateTwoDDistributionCorrelated<DiscreteDistribution>(
                         incoming_energy,
                         scattering_angle_cosine,
                         d_elastic_discrete_distribution );
  }
}


// Evaluate the PDF at the given energy and scattering angle cosine
/*! \details The cutoff and moment preserving PDF values are evaluated 
 *  independently of eachother.
 */
double HybridElasticElectronScatteringDistribution::evaluatePDF(
        const double incoming_energy,
        const double scattering_angle_cosine ) const
{
  // Make sure the energy, eta and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  if ( scattering_angle_cosine <= d_cutoff_angle_cosine )
  {
    return MonteCarlo::evaluateTwoDDistributionCorrelatedPDF<TwoDDistribution>(
                         incoming_energy,
                         scattering_angle_cosine,
                         d_elastic_cutoff_distribution );
  }
  else
  {
    return MonteCarlo::evaluateTwoDDistributionCorrelatedPDF<DiscreteDistribution>(
                         incoming_energy,
                         scattering_angle_cosine,
                         d_elastic_discrete_distribution );
  }
}

// Evaluate the CDF
/*! \details The cutoff and moment preserving CDF values are evaluated 
 *  independently of eachother.
 */
double HybridElasticElectronScatteringDistribution::evaluateCDF(
        const double incoming_energy,
        const double scattering_angle_cosine ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  // Make sure the energy, eta and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  if ( scattering_angle_cosine <= d_cutoff_angle_cosine )
  {
    return MonteCarlo::evaluateTwoDDistributionCorrelatedCDF<TwoDDistribution>(
                         incoming_energy,
                         scattering_angle_cosine,
                         d_elastic_cutoff_distribution );
  }
  else
  {
    return MonteCarlo::evaluateTwoDDistributionCorrelatedCDF<DiscreteDistribution>(
                         incoming_energy,
                         scattering_angle_cosine,
                         d_elastic_discrete_distribution );
  }
}

// Sample an outgoing energy and direction from the distribution
void HybridElasticElectronScatteringDistribution::sample(
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
void HybridElasticElectronScatteringDistribution::sampleAndRecordTrials(
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
void HybridElasticElectronScatteringDistribution::scatterElectron(
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

  shell_of_interaction =Data::UNKNOWN_SUBSHELL;

  // Set the new direction
  electron.rotateDirection( scattering_angle_cosine,
			  this->sampleAzimuthalAngle() );
}

// Randomly scatter the adjoint electron
void HybridElasticElectronScatteringDistribution::scatterAdjointElectron(
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
void HybridElasticElectronScatteringDistribution::sampleAndRecordTrialsImpl(
                                                const double incoming_energy,
                                                double& scattering_angle_cosine,
                                                unsigned& trials ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );

  // Increment the number of trials
  ++trials;

  TwoDDistribution::const_iterator lower_bin_boundary, upper_bin_boundary;
  lower_bin_boundary = d_elastic_cutoff_distribution.begin();
  upper_bin_boundary = d_elastic_cutoff_distribution.end();

  unsigned lower_bin_index, upper_bin_index;
  findLowerAndUpperBinIndex(
        incoming_energy,
        d_elastic_cutoff_distribution,
        lower_bin_index,
        upper_bin_index );

  double random_number =
      Utility::RandomNumberGenerator::getRandomNumber<double>();

  double lower_angle, upper_angle;
  // sample lower bin
  this->sampleIndependent( lower_bin_index, random_number, lower_angle );

  // sample upper bin
  this->sampleIndependent( upper_bin_index, random_number, upper_angle );

  if ( lower_bin_index != upper_bin_index )
  {
    scattering_angle_cosine = Utility::LogLog::interpolate(
        d_elastic_cutoff_distribution[lower_bin_index].first,
        d_elastic_cutoff_distribution[upper_bin_index].first,
        incoming_energy,
        lower_angle,
        upper_angle );
  }
  else
  {
    scattering_angle_cosine = lower_angle;
  }

  // Make sure the scattering angle cosine is valid
  testPostcondition( scattering_angle_cosine >= -1.0 );
  testPostcondition( scattering_angle_cosine <= 1.0 );
}

// Sample an outgoing direction from the given distribution
void HybridElasticElectronScatteringDistribution::sampleIndependent(
        const unsigned& energy_bin,
        const double& random_number,
        double& scattering_angle_cosine ) const
{
  // get the ratio of the cutoff cross section to the moment preserving cross section
  double cross_section_ratio =
    d_elastic_discrete_distribution[energy_bin].third;

  // calculate a sampling ratio
  double sampling_ratio =  cross_section_ratio/( 1.0 + cross_section_ratio );

  // Scale the random number
  double scaled_random_number = sampling_ratio*random_number;

  if ( random_number < sampling_ratio )
  {
    double scaled_random_number = random_number/sampling_ratio;

    scattering_angle_cosine =
        d_elastic_cutoff_distribution[energy_bin].second->sampleWithRandomNumberInSubrange(
            scaled_random_number, d_cutoff_angle_cosine );
  }
  else
  {
    double scaled_random_number =
        random_number*( 1.0 + cross_section_ratio) - cross_section_ratio;

    scattering_angle_cosine =
        d_elastic_discrete_distribution[energy_bin].second->sampleWithRandomNumber(
            scaled_random_number );
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_HybridElasticElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
