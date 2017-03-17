//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CutoffElasticElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  The electron cutoff elastic scattering distribution definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_CutoffElasticElectronScatteringDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_DirectionHelpers.hpp"
#include "Utility_KinematicHelpers.hpp"


namespace MonteCarlo{

// Constructor
CutoffElasticElectronScatteringDistribution::CutoffElasticElectronScatteringDistribution(
    const std::shared_ptr<TwoDDist>& scattering_distribution,
    const double cutoff_angle_cosine )
  : d_cutoff_distribution( scattering_distribution ),
    d_cutoff_angle_cosine( cutoff_angle_cosine )
{
  // Make sure the array is valid
  testPrecondition( d_cutoff_distribution.use_count() > 0 );
  // Make sure the cutoff_angle_cosine is valid
  testPrecondition( cutoff_angle_cosine >= -1.0 );
  testPrecondition( cutoff_angle_cosine <= 1.0 );
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

  return d_cutoff_distribution->evaluateExact( incoming_energy,
                                               scattering_angle_cosine );
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

  return d_cutoff_distribution->evaluateSecondaryConditionalPDFExact(
                        incoming_energy,
                        scattering_angle_cosine );
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

  return d_cutoff_distribution->evaluateSecondaryConditionalCDFExact(
                        incoming_energy,
                        scattering_angle_cosine );
}

// Evaluate the cross section ratio at the cutoff delta mu
/*! \details The cutoff cross section ration represents the ratio of the
 *  elastic_scattering_distribution within the angular displacement cutoff
 */
double CutoffElasticElectronScatteringDistribution::evaluateCutoffCrossSectionRatio(
        const double incoming_energy ) const
{
  // Get the max angle
  double max_angle =
    d_cutoff_distribution->getUpperBoundOfConditionalIndepVar( incoming_energy );

  // Get the max cdf value (aka the CDF at an angle cosine of 0.999999 )
  double max_cdf = evaluateCDF( incoming_energy, max_angle );

  /* Get the cdf at the cutoff angle cosine
   * Note: the cutoff cdf represents the unormalized ratio of the distribution within
   * the cutoff value
   */
  double cutoff_cdf = evaluateCDF( incoming_energy, d_cutoff_angle_cosine );

  // Make sure the cdf values are valid
  testPostcondition( max_cdf >= cutoff_cdf );
  testPostcondition( cutoff_cdf >= 0.0 );

  if ( max_cdf > 0.0 ) // normalize the cross_section_ratio by the max_cdf value
   return cutoff_cdf/max_cdf;
  else
   return 0.0;
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
void CutoffElasticElectronScatteringDistribution::scatterAdjointElectron(
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
void CutoffElasticElectronScatteringDistribution::sampleAndRecordTrialsImpl(
        const double incoming_energy,
        double& scattering_angle_cosine,
        unsigned& trials ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );

  // Increment the number of trials
  ++trials;

  // sample the scattering angle cosine
  scattering_angle_cosine =
    d_cutoff_distribution->sampleSecondaryConditionalExact( incoming_energy );

  // Make sure the scattering angle cosine is valid
  testPostcondition( scattering_angle_cosine >= -1.0 );
  testPostcondition( scattering_angle_cosine <= d_cutoff_angle_cosine );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_CutoffElasticElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
