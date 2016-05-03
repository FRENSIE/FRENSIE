//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CutoffElasticElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  The electron cutoff elastic scattering distribution definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_CutoffElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_TwoDDistributionHelpers.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_DirectionHelpers.hpp"
#include "Utility_KinematicHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_TabularDistribution.hpp"

namespace MonteCarlo{

// Constructor 
CutoffElasticElectronScatteringDistribution::CutoffElasticElectronScatteringDistribution(
    const ElasticDistribution& elastic_scattering_distribution,
    const double upper_cutoff_angle_cosine,
    const bool angle_cosine_is_used_as_independent_variable )
  : d_elastic_scattering_distribution( elastic_scattering_distribution ),
    d_upper_cutoff_angle_cosine( upper_cutoff_angle_cosine ),
    d_lower_cutoff_delta_mu( 1.0L - upper_cutoff_angle_cosine ),
    d_angle_cosine_is_used_as_independent_variable( angle_cosine_is_used_as_independent_variable )
{
  // Make sure the array is valid
  testPrecondition( d_elastic_scattering_distribution.size() > 0 );
  // Make sure the upper_cutoff_angle_cosine is valid
  testPrecondition( upper_cutoff_angle_cosine >= -1.0 );
  testPrecondition( upper_cutoff_angle_cosine <= 1.0 );
}

// Evaluate the distribution
double CutoffElasticElectronScatteringDistribution::evaluate( 
                            const double incoming_energy,
                            const double scattering_angle_cosine ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  if ( !d_angle_cosine_is_used_as_independent_variable )
  {  
    // Get the change is scattering angle cosine
    double delta_mu = 1.0L - scattering_angle_cosine;

    // evaluate the distribution at the incoming energy and change in scattering_angle_cosine
    return MonteCarlo::evaluateTwoDDistributionCorrelated<ElasticDistribution>( 
                         incoming_energy,
                         delta_mu,
                         d_elastic_scattering_distribution );
  }
  else
  {
    // evaluate the distribution at the incoming energy and scattering_angle_cosine
    return MonteCarlo::evaluateTwoDDistributionCorrelated<ElasticDistribution>( 
                         incoming_energy,
                         scattering_angle_cosine,
                         d_elastic_scattering_distribution );
  }
}

// Evaluate the distribution
double CutoffElasticElectronScatteringDistribution::evaluate( 
                            const unsigned incoming_energy_bin,
                            const double scattering_angle_cosine ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy_bin < 
                    d_elastic_scattering_distribution.size() );
  testPrecondition( incoming_energy_bin >= 0 );
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  if ( !d_angle_cosine_is_used_as_independent_variable )
  { 
    // Get the change is scattering angle cosine
    double delta_mu = 1.0L - scattering_angle_cosine;

    // evaluate the distribution at the bin and change in scattering_angle_cosine
    return d_elastic_scattering_distribution[incoming_energy_bin].second->evaluate( 
        delta_mu );
  }
  else
  {
    // evaluate the distribution at the bin and scattering_angle_cosine
    return d_elastic_scattering_distribution[incoming_energy_bin].second->evaluate( 
        scattering_angle_cosine );
  }
}

// Evaluate the PDF
double CutoffElasticElectronScatteringDistribution::evaluatePDF( 
                            const double incoming_energy,
                            const double scattering_angle_cosine ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  if ( !d_angle_cosine_is_used_as_independent_variable )
  {  
    // Get the change is scattering angle cosine
    double delta_mu = 1.0L - scattering_angle_cosine;

    // evaluate the PDF at the incoming energy and change in scattering_angle_cosine
    return MonteCarlo::evaluateTwoDDistributionCorrelatedPDF<ElasticDistribution>( 
                         incoming_energy,
                         delta_mu,
                         d_elastic_scattering_distribution );
  }
  else
  {
    // evaluate the PDF at the incoming energy and scattering_angle_cosine
    return MonteCarlo::evaluateTwoDDistributionCorrelatedPDF<ElasticDistribution>( 
                         incoming_energy,
                         scattering_angle_cosine,
                         d_elastic_scattering_distribution );
  }
}

// Evaluate the PDF
double CutoffElasticElectronScatteringDistribution::evaluatePDF( 
                            const unsigned incoming_energy_bin,
                            const double scattering_angle_cosine ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy_bin < 
                    d_elastic_scattering_distribution.size() );
  testPrecondition( incoming_energy_bin >= 0 );
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  if ( !d_angle_cosine_is_used_as_independent_variable )
  { 
    // Get the change is scattering angle cosine
    double delta_mu = 1.0L - scattering_angle_cosine;

    // evaluate the PDF at the bin and change in scattering_angle_cosine
    return d_elastic_scattering_distribution[incoming_energy_bin].second->evaluatePDF( 
        delta_mu );
  }
  else
  {
    // evaluate the PDF at the bin and scattering_angle_cosine
    return d_elastic_scattering_distribution[incoming_energy_bin].second->evaluatePDF( 
        scattering_angle_cosine );
  }
}

// Evaluate the CDF
double CutoffElasticElectronScatteringDistribution::evaluateCDF( 
                            const double incoming_energy,
                            const double scattering_angle_cosine ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  if ( !d_angle_cosine_is_used_as_independent_variable )
  {  
    // Get the change is scattering angle cosine
    double delta_mu = 1.0L - scattering_angle_cosine;

    // evaluate the CDF at the incoming energy and change in scattering_angle_cosine
    return MonteCarlo::evaluateTwoDDistributionCorrelatedCDF<ElasticDistribution>( 
                         incoming_energy,
                         delta_mu,
                         d_elastic_scattering_distribution );
  }
  else
  {
    // evaluate the CDF at the incoming energy and scattering_angle_cosine
    return MonteCarlo::evaluateTwoDDistributionCorrelatedCDF<ElasticDistribution>( 
                         incoming_energy,
                         scattering_angle_cosine,
                         d_elastic_scattering_distribution );
  }
}

// Evaluate the cross section ratio at the cutoff delta mu
/*! \details The cutoff cross section ration represents the ratio of the 
 *  elastic_scattering_distribution within the angular displacement cutoff
 */
double CutoffElasticElectronScatteringDistribution::evaluateCutoffCrossSectionRatio( 
        const double incoming_energy ) const
{
  double cross_section_ratio = 0.0;

  if ( !d_angle_cosine_is_used_as_independent_variable )
  {  
    /* Get the cdf at the cutoff angle cosine 
     * Note: the cutoff cdf represents the ratio of the distribution outside 
     * the cutoff value
     */
    double cutoff_cdf = evaluateCDF( incoming_energy, d_upper_cutoff_angle_cosine );

    // The cutoff cdf represents the area of the distribution
    cross_section_ratio = 1.0 - cutoff_cdf;
  }
  else
  {
    // Get the max cdf value (aka the CDF at an angle cosine of 0.999999)
    double max_cdf = evaluateCDF( incoming_energy, 0.999999 );

    /* Get the cdf at the cutoff angle cosine 
     * Note: the cutoff cdf represents the unormalized ratio of the distribution within 
     * the cutoff value
     */
    double cutoff_cdf = evaluateCDF( incoming_energy, d_upper_cutoff_angle_cosine );

    // Make sure the cdf values are valid
    testPostcondition( max_cdf >= cutoff_cdf );
    testPostcondition( cutoff_cdf >= 0.0 );

    // normalize the cross_section_ratio by the max_cdf value
    if ( max_cdf > 0.0 )
     cross_section_ratio = cutoff_cdf/max_cdf;
  }

  return cross_section_ratio;
}


// Return the energy at a given energy bin
double CutoffElasticElectronScatteringDistribution::getEnergy( 
    const unsigned energy_bin ) const
{
  // Make sure the energy bin is valid
  testPrecondition( energy_bin < d_elastic_scattering_distribution.size() );
  testPrecondition( energy_bin >= 0 );

  return d_elastic_scattering_distribution[energy_bin].first;
}

// Sample an outgoing energy and direction from the distribution
void CutoffElasticElectronScatteringDistribution::sample( 
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
void CutoffElasticElectronScatteringDistribution::sampleAndRecordTrials( 
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
void CutoffElasticElectronScatteringDistribution::scatterElectron( 
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

// Sample an outgoing direction from the distribution
void CutoffElasticElectronScatteringDistribution::sampleAndRecordTrialsImpl( 
        const double incoming_energy,
        double& scattering_angle_cosine,
        unsigned& trials ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );

  // Increment the number of trials
  ++trials;

  double scaled_random_number;

  if ( !d_angle_cosine_is_used_as_independent_variable )
  {  
    // evaluate the cdf value at the lower cutoff angle
    double lower_cutoff_cdf = 
            evaluateCDF( incoming_energy, d_upper_cutoff_angle_cosine );

    // scale the random number to only sample above the lower cutoff delta mu
    scaled_random_number = ( 1.0L - lower_cutoff_cdf )*
        Utility::RandomNumberGenerator::getRandomNumber<double>() +
        lower_cutoff_cdf;

    // sample the change in scattering angle cosine 
    double delta_mu = 
        sampleTwoDDistributionCorrelatedWithRandomNumber<ElasticDistribution>( 
            incoming_energy,
            d_elastic_scattering_distribution,
            scaled_random_number );

    // calculate the scattering angle cosine
    scattering_angle_cosine = 1.0L - delta_mu;
  }
  else
  {
    // evaluate the cdf value at the upper cutoff angle cosine
    double upper_cutoff_cdf = 
            evaluateCDF( incoming_energy, d_upper_cutoff_angle_cosine );

    // scale the random number to only sample below the upper cutoff angle cosine
    scaled_random_number = upper_cutoff_cdf*
        Utility::RandomNumberGenerator::getRandomNumber<double>();

    // sample the scattering angle cosine 
    scattering_angle_cosine = 
        sampleTwoDDistributionCorrelatedWithRandomNumber<ElasticDistribution>( 
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
// end MonteCarlo_CutoffElasticElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
