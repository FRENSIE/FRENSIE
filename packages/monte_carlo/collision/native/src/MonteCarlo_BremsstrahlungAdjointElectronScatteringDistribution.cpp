//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BremsstrahlungAdjointElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  The electron bremsstrahlung scattering distribution definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_BremsstrahlungAdjointElectronScatteringDistribution.hpp"

namespace MonteCarlo{

// Constructor
BremsstrahlungAdjointElectronScatteringDistribution::BremsstrahlungAdjointElectronScatteringDistribution(
    const std::shared_ptr<TwoDDist>& adjoint_brem_scatter_dist,
    const bool correlated_sampling_mode_on,
    const bool unit_based_interpolation_mode_on )
  : d_adjoint_brem_scatter_dist( adjoint_brem_scatter_dist )
{
  // Make sure the array is valid
  testPrecondition( d_adjoint_brem_scatter_dist.use_count() > 0 );

  this->setSamplingRoutine( correlated_sampling_mode_on,
                            unit_based_interpolation_mode_on );
  this->setEvaluationRoutines( unit_based_interpolation_mode_on );
}

// Set the sampling routine
/*! \details There are often multiple ways to sample from two-dimensional
 * distributions (e.g. stochastic and correlated sampling). This function sets
 * the sample function pointer to the desired sampling routine.
 */
void BremsstrahlungAdjointElectronScatteringDistribution::setSamplingRoutine(
                                    const bool correlated_sampling_mode_on,
                                    const bool unit_based_interpolation_mode_on )
{
  if( unit_based_interpolation_mode_on )
  {
    if( correlated_sampling_mode_on )
    {
      // Set the correlated unit based sample routine
      d_sample_function = std::bind<double>(
           &TwoDDist::correlatedSampleSecondaryConditional,
           std::cref( *d_adjoint_brem_scatter_dist ),
           std::placeholders::_1 );
    }
    else
    {
      // Set the stochastic unit based sample routine
      d_sample_function = std::bind<double>(
           &TwoDDist::sampleSecondaryConditional,
           std::cref( *d_adjoint_brem_scatter_dist ),
           std::placeholders::_1 );
    }
  }
  else
  {
      // Set the correlated exact sample routine
    d_sample_function = std::bind<double>(
           &TwoDDist::sampleSecondaryConditionalExact,
           std::cref( *d_adjoint_brem_scatter_dist ),
           std::placeholders::_1 );
  }
}

// Set the evaluation routines
/*! \details This function sets the evalute, evaluatePDF and evaluateCDF
 *  function pointers to either an exact or unit based routine. The exact and
 *  unit based routines are consistent with the correlatedSampleExact and
 *  correlatedSampleUnitBased respectively.
 */
void BremsstrahlungAdjointElectronScatteringDistribution::setEvaluationRoutines(
                                    const bool unit_based_interpolation_mode_on )
{
  if( unit_based_interpolation_mode_on )
  {
    // Set the correlated unit based evaluation routines
    d_evaluate_function = std::bind<double>(
       &TwoDDist::correlatedEvaluate,
       std::cref( *d_adjoint_brem_scatter_dist ),
       std::placeholders::_1,
       std::placeholders::_2 );

    d_evaluate_pdf_function = std::bind<double>(
       &TwoDDist::correlatedEvaluateSecondaryConditionalPDF,
       std::cref( *d_adjoint_brem_scatter_dist ),
       std::placeholders::_1,
       std::placeholders::_2 );

    d_evaluate_cdf_function = std::bind<double>(
       &TwoDDist::correlatedEvaluateSecondaryConditionalCDF,
       std::cref( *d_adjoint_brem_scatter_dist ),
       std::placeholders::_1,
       std::placeholders::_2 );
  }
  else
  {
    // Set the correlated exact evaluation routines
    d_evaluate_function = std::bind<double>(
       &TwoDDist::evaluateExact,
       std::cref( *d_adjoint_brem_scatter_dist ),
       std::placeholders::_1,
       std::placeholders::_2 );

    d_evaluate_pdf_function = std::bind<double>(
       &TwoDDist::evaluateSecondaryConditionalPDFExact,
       std::cref( *d_adjoint_brem_scatter_dist ),
       std::placeholders::_1,
       std::placeholders::_2 );

    d_evaluate_cdf_function = std::bind<double>(
       &TwoDDist::evaluateSecondaryConditionalCDFExact,
       std::cref( *d_adjoint_brem_scatter_dist ),
       std::placeholders::_1,
       std::placeholders::_2 );
  }
}

// Return the min incoming energy
double BremsstrahlungAdjointElectronScatteringDistribution::getMinEnergy() const
{
  return d_adjoint_brem_scatter_dist->getLowerBoundOfPrimaryIndepVar();
}

// Return the Max incoming energy
double BremsstrahlungAdjointElectronScatteringDistribution::getMaxEnergy() const
{
  return d_adjoint_brem_scatter_dist->getUpperBoundOfPrimaryIndepVar();
}

// Evaluate the distribution
double BremsstrahlungAdjointElectronScatteringDistribution::evaluate(
        const double incoming_energy,
        const double outgoing_energy ) const
{
  // Make sure the energies are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( outgoing_energy > incoming_energy );

  // evaluate the distribution
  return d_evaluate_function( incoming_energy, outgoing_energy );
}

// Evaluate the PDF
double BremsstrahlungAdjointElectronScatteringDistribution::evaluatePDF(
        const double incoming_energy,
        const double outgoing_energy ) const
{
  // Make sure the energies are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( outgoing_energy > incoming_energy );

  // evaluate the pdf
  return d_evaluate_pdf_function( incoming_energy, outgoing_energy );
}

// Evaluate the PDF
double BremsstrahlungAdjointElectronScatteringDistribution::evaluateCDF(
        const double incoming_energy,
        const double outgoing_energy ) const
{
  // Make sure the energies are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( outgoing_energy > incoming_energy );

  // evaluate the cdf
  return d_evaluate_cdf_function( incoming_energy, outgoing_energy );
}

// Sample an outgoing energy and direction from the distribution
/*! \details In the forward case the scattering angle cosine of the incoming
 *  electron is considered to be negligible. Similarly the scattering angle
 *  cosine of the incoming adjoint electron will be considered negligible.
 *  This is not the case for the creation of an adjoint electron by an
 *  adjoint bremsstrahlung photon.
 */
void BremsstrahlungAdjointElectronScatteringDistribution::sample(
        const double incoming_energy,
        double& outgoing_energy,
        double& scattering_angle_cosine ) const
{
  // The adjoint electron angle scattering is assumed to be negligible
  scattering_angle_cosine = 1.0;

  outgoing_energy = d_sample_function( incoming_energy );

  testPostcondition( outgoing_energy > incoming_energy );
}

// Sample an outgoing energy and direction and record the number of trials
void BremsstrahlungAdjointElectronScatteringDistribution::sampleAndRecordTrials(
                            const double incoming_energy,
                            double& outgoing_energy,
                            double& scattering_angle_cosine,
                            unsigned& trials ) const
{
  trials++;

  this->sample( incoming_energy, outgoing_energy, scattering_angle_cosine );

}
// Randomly scatter the electron
void BremsstrahlungAdjointElectronScatteringDistribution::scatterAdjointElectron(
                                AdjointElectronState& adjoint_electron,
                                ParticleBank& bank,
                                Data::SubshellType& shell_of_interaction ) const
{
  // outgoing electron energy
  double outgoing_energy;

  // Scattering angle of the electron
  double scattering_angle_cosine;

  // Sample outgoing electron energy
  this->sample( adjoint_electron.getEnergy(),
                outgoing_energy,
                scattering_angle_cosine );

  // Set the new electron energy
  adjoint_electron.setEnergy( outgoing_energy );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_BremsstrahlungAdjointElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
