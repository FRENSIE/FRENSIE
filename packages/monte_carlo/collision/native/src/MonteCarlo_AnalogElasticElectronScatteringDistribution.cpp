//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AnalogElasticElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  The electron analog elastic scattering distribution definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_AnalogElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_TwoDDistributionHelpers.hpp"
#include "Utility_GaussKronrodQuadratureKernel.hpp"
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
    const double lower_cutoff_angle,
    const bool angle_is_used_as_independent_variable )
  : d_elastic_scattering_distribution( elastic_scattering_distribution ),
    d_lower_cutoff_angle( lower_cutoff_angle ),
    d_angle_is_used_as_independent_variable( angle_is_used_as_independent_variable )
{
  // Make sure the array is valid
  testPrecondition( d_elastic_scattering_distribution.size() > 0 );
  // Make sure the lower cutoff angle is valid
  testPrecondition( lower_cutoff_angle >= 0.0 );
  testPrecondition( lower_cutoff_angle < 2.0 );
}

// Evaluate the PDF
double AnalogElasticElectronScatteringDistribution::evaluatePDF( 
                            const double incoming_energy,
                            const double scattering_angle ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle >= d_lower_cutoff_angle );
  testPrecondition( scattering_angle <= 2.0 );

  if ( d_angle_is_used_as_independent_variable )
  {  
    return MonteCarlo::evaluateTwoDDistributionCorrelatedPDF( 
                         incoming_energy,
                         scattering_angle,
                         d_elastic_scattering_distribution );
  }
  else
  {
    double scattering_angle_cosine = 1.0L - scattering_angle;
    return MonteCarlo::evaluateTwoDDistributionCorrelatedPDF( 
                         incoming_energy,
                         scattering_angle_cosine,
                         d_elastic_scattering_distribution );
  }
}

// Evaluate the PDF
double AnalogElasticElectronScatteringDistribution::evaluatePDF( 
                            const unsigned incoming_energy_bin,
                            const double scattering_angle ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy_bin < 
                    d_elastic_scattering_distribution.size() );
  testPrecondition( incoming_energy_bin >= 0 );
  testPrecondition( scattering_angle >= d_lower_cutoff_angle );
  testPrecondition( scattering_angle <= 2.0 );

  double pdf;

  if ( d_angle_is_used_as_independent_variable )
  { 
    pdf = 
     d_elastic_scattering_distribution[incoming_energy_bin].second->evaluatePDF( 
        scattering_angle );
  }
  else
  {
    double scattering_angle_cosine = 1.0L - scattering_angle;

    pdf = 
     d_elastic_scattering_distribution[incoming_energy_bin].second->evaluatePDF( 
        scattering_angle_cosine );
  }

  return pdf;
}

// Evaluate the CDF
double AnalogElasticElectronScatteringDistribution::evaluateCDF( 
                            const double incoming_energy,
                            const double scattering_angle ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle >= d_lower_cutoff_angle );
  testPrecondition( scattering_angle <= 2.0 );

  if ( d_angle_is_used_as_independent_variable )
  {  
    return MonteCarlo::evaluateTwoDDistributionCorrelatedCDF( 
                         incoming_energy,
                         scattering_angle,
                         d_elastic_scattering_distribution );
  }
  else
  {
    double scattering_angle_cosine = 1.0L - scattering_angle;

    return MonteCarlo::evaluateTwoDDistributionCorrelatedCDF( 
                         incoming_energy,
                         scattering_angle_cosine,
                         d_elastic_scattering_distribution );
  }
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
				     SubshellType& shell_of_interaction ) const
{
  double scattering_angle_cosine;

  unsigned trial_dummy;

  // Sample an outgoing direction
  this->sampleAndRecordTrialsImpl( electron.getEnergy(),
				                   scattering_angle_cosine,
				                   trial_dummy );

  shell_of_interaction = UNKNOWN_SUBSHELL;

  // Set the new direction
  electron.rotateDirection( scattering_angle_cosine, 
			  this->sampleAzimuthalAngle() );
}

// Randomly scatter the adjoint electron
void AnalogElasticElectronScatteringDistribution::scatterAdjointElectron( 
				     AdjointElectronState& adjoint_electron,
				     ParticleBank& bank,
				     SubshellType& shell_of_interaction ) const
{
  double scattering_angle_cosine;

  unsigned trial_dummy;

  // Sample an outgoing direction
  this->sampleAndRecordTrialsImpl( adjoint_electron.getEnergy(),
				                   scattering_angle_cosine,
				                   trial_dummy );
  
  shell_of_interaction = UNKNOWN_SUBSHELL;

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

  if ( d_angle_is_used_as_independent_variable )
  {  
    // evaluate the cdf value at the lower cutoff angle
    double lower_cutoff_cdf = 
            evaluateCDF( incoming_energy, d_lower_cutoff_angle );

    // scale the random number to only sample above the lower cutoff angle
    scaled_random_number = ( 1.0L - lower_cutoff_cdf )*
        Utility::RandomNumberGenerator::getRandomNumber<double>() +
        lower_cutoff_cdf;

  double scattering_angle = 
        sampleTwoDDistributionCorrelatedWithRandomNumber( 
            incoming_energy,
            d_elastic_scattering_distribution,
            scaled_random_number );

  scattering_angle_cosine = 1.0L - scattering_angle;
  }
  else
  {
    // evaluate the cdf value at the upper cutoff angle cosine
    double upper_cutoff_cdf = 
            evaluateCDF( incoming_energy, d_lower_cutoff_angle );

    // scale the random number to only sample below the upper cutoff angle cosine
    scaled_random_number = upper_cutoff_cdf*
        Utility::RandomNumberGenerator::getRandomNumber<double>();

    scattering_angle_cosine = 
        sampleTwoDDistributionCorrelatedWithRandomNumber( 
            incoming_energy,
            d_elastic_scattering_distribution,
            scaled_random_number );
  }

  // Make sure the scattering angle cosine is valid
  testPostcondition( scattering_angle_cosine >= -1.0 );
  testPostcondition( scattering_angle_cosine <= 1.0 );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AnalogElasticElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
