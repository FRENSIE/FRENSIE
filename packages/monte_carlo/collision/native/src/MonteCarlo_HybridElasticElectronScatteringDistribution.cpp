//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_HybridElasticElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  The analog elastic electron scattering distribution definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_HybridElasticElectronScatteringDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_DirectionHelpers.hpp"
#include "Utility_KinematicHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"

namespace MonteCarlo{

// Constructor
HybridElasticElectronScatteringDistribution::HybridElasticElectronScatteringDistribution(
    const std::shared_ptr<TwoDDist>& continuous_distribution,
    const std::shared_ptr<TwoDDist>& discrete_distribution,
    const std::shared_ptr<const Utility::OneDDistribution>& cross_section_ratios,
    const double cutoff_angle_cosine,
    const double evaluation_tol )
  : d_continuous_distribution( continuous_distribution ),
    d_discrete_distribution( discrete_distribution ),
    d_cross_section_ratios( cross_section_ratios ),
    d_cutoff_angle_cosine( cutoff_angle_cosine ),
    d_evaluation_tol( evaluation_tol )
{
  // Make sure the pointers are valid
  testPrecondition( d_continuous_distribution.use_count() > 0 );
  testPrecondition( d_discrete_distribution.use_count() > 0 );
  testPrecondition( d_cross_section_ratios.use_count() > 0 );
  // Make sure the cutoff angle cosine is valid
  testPrecondition( d_cutoff_angle_cosine >= -1.0 );
  testPrecondition( d_cutoff_angle_cosine < 1.0 );
  // Make sure the evaluation tolerance is valid
  testPrecondition( d_evaluation_tol > 0.0 );
  testPrecondition( d_evaluation_tol < 1.0 );
}

// Return the cutoff to moment preserving cross section ratio
inline double HybridElasticElectronScatteringDistribution::getCrossSectionRatio(
                                         const double incoming_energy ) const
{
  // Make sure the energy is valid
  testPrecondition( incoming_energy > 0.0 );

  return d_cross_section_ratios->evaluate( incoming_energy );
}

// Return the sampling ratio at the given incoming energy
inline double HybridElasticElectronScatteringDistribution::getSamplingRatio(
                                        const double incoming_energy ) const
{
  double cross_section_ratio = this->getCrossSectionRatio( incoming_energy );

  return cross_section_ratio/( 1.0 + cross_section_ratio );
}

// Evaluate the distribution at the given energy and scattering angle cosine
/*! \details Only scattering angle cosine within the continuous distribution are
 *  evaluated. If the scattering angle cosine is below the cutoff angle cosine
 *  the continuous distribution is evaluated. If it is above the cutoff angle
 *  a value of zero is returned.
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
    double unormalized_eval = d_continuous_distribution->evaluateExact(
                                    incoming_energy, scattering_angle_cosine);

    return this->normalizeEvalution( incoming_energy,unormalized_eval );
  }
  else
    return 0.0;
}

// Evaluate the PDF at the given energy and scattering angle cosine
/*! \details Only scattering angle cosine within the continuous distribution are
 *  evaluated. If the scattering angle cosine is below the cutoff angle cosine
 *  the continuous distribution is evaluated. If it is above the cutoff angle
 *  a value of zero is returned.
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
    double unormalized_eval =
        d_continuous_distribution->evaluateSecondaryConditionalPDFExact(
                                    incoming_energy, scattering_angle_cosine);

    return this->normalizeEvalution( incoming_energy,unormalized_eval );
  }
  else
    return 0.0;
}

// Evaluate the CDF
/*! \details Only scattering angle cosine within the continuous distribution are
 *  evaluated. If the scattering angle cosine is below the cutoff angle cosine
 *  the continuous distribution is evaluated. If it is above the cutoff angle
 *  a value of zero is returned.
 */
double HybridElasticElectronScatteringDistribution::evaluateCDF(
        const double incoming_energy,
        const double scattering_angle_cosine ) const
{
  // Make sure the energy, eta and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  if ( scattering_angle_cosine <= d_cutoff_angle_cosine )
  {
    double unormalized_eval =
        d_continuous_distribution->evaluateSecondaryConditionalCDFExact(
                                    incoming_energy, scattering_angle_cosine);

    return this->normalizeEvalution( incoming_energy,unormalized_eval );
  }
  else if( incoming_energy <
                d_continuous_distribution->getLowerBoundOfPrimaryIndepVar() ||
           incoming_energy >
                d_continuous_distribution->getUpperBoundOfPrimaryIndepVar() )
  {
    return 0.0;
  }
  else
    return 1.0;
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

  if( incoming_energy < d_continuous_distribution->getLowerBoundOfPrimaryIndepVar() ||
      incoming_energy > d_continuous_distribution->getUpperBoundOfPrimaryIndepVar() )
  {
    scattering_angle_cosine = 1.0;
  }
  else
  {
    double random_number =
      Utility::RandomNumberGenerator::getRandomNumber<double>();

    // Ratio of the cutoff cross section to the moment preserving cross section
    double cross_section_ratio = this->getCrossSectionRatio( incoming_energy );

    // Scale the random number
    double scaled_random_number = ( 1.0 + cross_section_ratio )*random_number;

    if ( scaled_random_number <= cross_section_ratio )
    {
      scaled_random_number /= cross_section_ratio;

      scattering_angle_cosine =
        d_continuous_distribution->sampleSecondaryConditionalExactWithRandomNumberInSubrange(
            incoming_energy, scaled_random_number, d_cutoff_angle_cosine );
    }
    else
    {
      scaled_random_number -= cross_section_ratio;

      scattering_angle_cosine =
        d_discrete_distribution->sampleSecondaryConditionalExactWithRandomNumber(
            incoming_energy, scaled_random_number );
    }
  }

  // Make sure the scattering angle cosine is valid
  testPostcondition( scattering_angle_cosine >= -1.0 );
  testPostcondition( scattering_angle_cosine <= 1.0 );
}

// Normalized the cutoff eval to the entire distribution
inline double HybridElasticElectronScatteringDistribution::normalizeEvalution(
                            const double incoming_energy,
                            const double unormalized_eval ) const
{
  // The cdf of the cutoff distribution at the cutoff angle
  double cutoff_cdf =
        d_continuous_distribution->evaluateSecondaryConditionalCDFExact(
                                    incoming_energy, d_cutoff_angle_cosine );

  // Check to make sure the CDF > 0
  if ( cutoff_cdf == 0.0 )
      return 0.0;

  // Sampling ratio of the cutoff to the moment preserving distribution
  double sampling_ratio = this->getSamplingRatio( incoming_energy );

  return unormalized_eval*sampling_ratio/cutoff_cdf;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_HybridElasticElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
