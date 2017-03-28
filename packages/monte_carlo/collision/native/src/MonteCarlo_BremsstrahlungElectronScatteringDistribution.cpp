//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BremsstrahlungElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  The electron bremsstrahlung scattering distribution definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_BremsstrahlungElectronScatteringDistribution.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_DirectionHelpers.hpp"
#include "Utility_KinematicHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_TabularDistribution.hpp"

namespace MonteCarlo{

// Constructor with simple analytical photon angular distribution
BremsstrahlungElectronScatteringDistribution::BremsstrahlungElectronScatteringDistribution(
    const std::shared_ptr<TwoDDist>& bremsstrahlung_scattering_distribution,
    const bool correlated_sampling_mode_on,
    const bool unit_based_interpolation_mode_on )
  : d_bremsstrahlung_scattering_distribution( bremsstrahlung_scattering_distribution )
{
  // Make sure the array is valid
  testPrecondition( d_bremsstrahlung_scattering_distribution.use_count() > 0 );

  // Use simple analytical photon angular distribution
  d_angular_distribution_func = std::bind<double>(
           &BremsstrahlungElectronScatteringDistribution::SampleDipoleAngle,
           std::cref( *this ),
           std::placeholders::_1,
           std::placeholders::_2 );

  this->setSamplingRoutine( correlated_sampling_mode_on,
                            unit_based_interpolation_mode_on );
  this->setEvaluationRoutines( unit_based_interpolation_mode_on );
}

// Constructor with detailed 2BS photon angular distribution
BremsstrahlungElectronScatteringDistribution::BremsstrahlungElectronScatteringDistribution(
    const int atomic_number,
    const std::shared_ptr<TwoDDist>& bremsstrahlung_scattering_distribution,
    const bool correlated_sampling_mode_on,
    const bool unit_based_interpolation_mode_on )
  : d_atomic_number( atomic_number ),
    d_bremsstrahlung_scattering_distribution( bremsstrahlung_scattering_distribution )
{
  // Make sure the arraies are valid
  testPrecondition( d_bremsstrahlung_scattering_distribution.use_count() > 0 );

  // Use detailed photon angular distribution
  d_angular_distribution_func = std::bind<double>(
            &BremsstrahlungElectronScatteringDistribution::Sample2BSAngle,
            std::cref( *this ),
            std::placeholders::_1,
            std::placeholders::_2 );

  this->setSamplingRoutine( correlated_sampling_mode_on,
                            unit_based_interpolation_mode_on );
  this->setEvaluationRoutines( unit_based_interpolation_mode_on );
}

// Set the sampling routine
/*! \details There are often multiple ways to sample from two-dimensional
 * distributions (e.g. stochastic and correlated sampling). This function sets
 * the sample function pointer to the desired sampling routine.
 */
void BremsstrahlungElectronScatteringDistribution::setSamplingRoutine(
                                    const bool correlated_sampling_mode_on,
                                    const bool unit_based_interpolation_mode_on )
{
  if( unit_based_interpolation_mode_on )
  {
    if( correlated_sampling_mode_on )
    {
      // Set the correlated unit based sample routine
      d_sample_func = std::bind<double>(
           &BremsstrahlungElectronScatteringDistribution::correlatedSampleUnitBased,
           std::cref( *this ),
           std::placeholders::_1 );
    }
    else
    {
      // Set the stochastic unit based sample routine
      d_sample_func = std::bind<double>(
           &BremsstrahlungElectronScatteringDistribution::sampleUnitBased,
           std::cref( *this ),
           std::placeholders::_1 );
    }
  }
  else
  {
      // Set the correlated exact sample routine
    d_sample_func = std::bind<double>(
           &BremsstrahlungElectronScatteringDistribution::correlatedSampleExact,
           std::cref( *this ),
           std::placeholders::_1 );
  }
}

// Set the evaluation routines
/*! \details This function sets the evalute, evaluatePDF and evaluateCDF
 *  function pointers to either an exact or unit based routine. The exact and
 *  unit based routines are consistent with the correlatedSampleExact and
 *  correlatedSampleUnitBased respectively.
 */
void BremsstrahlungElectronScatteringDistribution::setEvaluationRoutines(
                                    const bool unit_based_interpolation_mode_on )
{
  if( unit_based_interpolation_mode_on )
  {
    // Set the correlated unit based evaluation routines
    d_evaluate_func = std::bind<double>(
       &BremsstrahlungElectronScatteringDistribution::correlatedEvaluateUnitBased,
       std::cref( *this ),
       std::placeholders::_1,
       std::placeholders::_2 );

    d_evaluate_pdf_func = std::bind<double>(
       &BremsstrahlungElectronScatteringDistribution::correlatedEvaluatePDFUnitBased,
       std::cref( *this ),
       std::placeholders::_1,
       std::placeholders::_2 );

    d_evaluate_cdf_func = std::bind<double>(
       &BremsstrahlungElectronScatteringDistribution::correlatedEvaluateCDFUnitBased,
       std::cref( *this ),
       std::placeholders::_1,
       std::placeholders::_2 );
  }
  else
  {
    // Set the correlated exact evaluation routines
    d_evaluate_func = std::bind<double>(
       &BremsstrahlungElectronScatteringDistribution::correlatedEvaluateExact,
       std::cref( *this ),
       std::placeholders::_1,
       std::placeholders::_2 );

    d_evaluate_pdf_func = std::bind<double>(
       &BremsstrahlungElectronScatteringDistribution::correlatedEvaluatePDFExact,
       std::cref( *this ),
       std::placeholders::_1,
       std::placeholders::_2 );

    d_evaluate_cdf_func = std::bind<double>(
       &BremsstrahlungElectronScatteringDistribution::correlatedEvaluateCDFExact,
       std::cref( *this ),
       std::placeholders::_1,
       std::placeholders::_2 );
  }
}

// Return the min incoming energy
double BremsstrahlungElectronScatteringDistribution::getMinEnergy() const
{
  return d_bremsstrahlung_scattering_distribution->getLowerBoundOfPrimaryIndepVar();
}

// Return the Max incoming energy
double BremsstrahlungElectronScatteringDistribution::getMaxEnergy() const
{
  return d_bremsstrahlung_scattering_distribution->getUpperBoundOfPrimaryIndepVar();
}

// Evaluate the distribution for a given incoming and photon energy
double BremsstrahlungElectronScatteringDistribution::evaluate(
                     const double incoming_energy,
                     const double photon_energy ) const
{
  // Make sure the energies are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( photon_energy <= incoming_energy );
  testPrecondition( photon_energy > 0.0 );

  // evaluate the distribution
  return d_evaluate_func( incoming_energy, photon_energy );
}

// Evaluate the PDF value for a given incoming and photon energy
double BremsstrahlungElectronScatteringDistribution::evaluatePDF(
                     const double incoming_energy,
                     const double photon_energy ) const
{
  // Make sure the energies are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( photon_energy <= incoming_energy );
  testPrecondition( photon_energy > 0.0 );

  // evaluate the distribution
  return d_evaluate_pdf_func( incoming_energy, photon_energy );
}

// Evaluate the CDF value for a given incoming and photon energy
double BremsstrahlungElectronScatteringDistribution::evaluateCDF(
                     const double incoming_energy,
                     const double photon_energy ) const
{
  // Make sure the energies are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( photon_energy <= incoming_energy );
  testPrecondition( photon_energy > 0.0 );

  // evaluate the distribution
  return d_evaluate_cdf_func( incoming_energy, photon_energy );
}

// Sample the photon energy and direction from the distribution
void BremsstrahlungElectronScatteringDistribution::sample(
             const double incoming_energy,
             double& photon_energy,
             double& photon_angle_cosine ) const
{
  // Sample the photon energy
  photon_energy = d_sample_func( incoming_energy );

  // Sample the photon outgoing angle cosine
  photon_angle_cosine = d_angular_distribution_func( incoming_energy,
                                                     photon_energy );

  testPostcondition( incoming_energy > photon_energy );
  testPostcondition( photon_energy > 0.0 );
  testPostcondition( photon_angle_cosine <= 1.0 );
  testPostcondition( photon_angle_cosine >= -1.0 );
}

// Sample an outgoing energy and direction and record the number of trials
void BremsstrahlungElectronScatteringDistribution::sampleAndRecordTrials(
                            const double incoming_energy,
                            double& photon_energy,
                            double& photon_angle_cosine,
                            unsigned& trials ) const
{
  trials++;

  sample( incoming_energy, photon_energy, photon_angle_cosine );

}
// Randomly scatter the electron
void BremsstrahlungElectronScatteringDistribution::scatterElectron(
                          ElectronState& electron,
                          ParticleBank& bank,
                          Data::SubshellType& shell_of_interaction ) const
{
  // Incoming electron energy
  double incoming_energy = electron.getEnergy();

  // energy of the bremsstrahlung photon
  double photon_energy;

  // photon outgoing angle cosine
  double photon_angle_cosine;

  // Sample bremsstrahlung photon energy and angle cosine
  sample( incoming_energy, photon_energy, photon_angle_cosine );

  // Set the new electron energy
  electron.setEnergy( incoming_energy - photon_energy );

  // Increment the electron generation number
  electron.incrementGenerationNumber();

  // Create new photon
  Teuchos::RCP<PhotonState> bremsstrahlung_photon(
                           new PhotonState( electron, true, true ) );

  // Set photon energy
  bremsstrahlung_photon->setEnergy( photon_energy );

  // Set the photon outgoing angle cosine
  bremsstrahlung_photon->rotateDirection( photon_angle_cosine,
                                          sampleAzimuthalAngle() );

  // Bank the photon
  bank.push( bremsstrahlung_photon );
}

// Evaluate the distribution for a given incoming and photon energy
double BremsstrahlungElectronScatteringDistribution::correlatedEvaluateUnitBased(
                                        const double incoming_energy,
                                        const double photon_energy ) const
{
  return d_bremsstrahlung_scattering_distribution->correlatedEvaluate(
            incoming_energy,
            photon_energy,
            1e-7,
            incoming_energy );
}

// Evaluate the distribution for a given incoming and photon energy
double BremsstrahlungElectronScatteringDistribution::correlatedEvaluateExact(
                                        const double incoming_energy,
                                        const double photon_energy ) const
{
  return d_bremsstrahlung_scattering_distribution->evaluateExact(
            incoming_energy,
            photon_energy );
}

// Evaluate the PDF value for a given incoming and photon energy
double BremsstrahlungElectronScatteringDistribution::correlatedEvaluatePDFUnitBased(
                                        const double incoming_energy,
                                        const double photon_energy ) const
{
  return d_bremsstrahlung_scattering_distribution->correlatedEvaluateSecondaryConditionalPDF(
            incoming_energy,
            photon_energy,
            1e-7,
            incoming_energy );
}

// Evaluate the PDF value for a given incoming and photon energy
double BremsstrahlungElectronScatteringDistribution::correlatedEvaluatePDFExact(
                                        const double incoming_energy,
                                        const double photon_energy ) const
{
  return d_bremsstrahlung_scattering_distribution->evaluateSecondaryConditionalPDFExact(
            incoming_energy,
            photon_energy );
}

// Evaluate the CDF value for a given incoming and photon energy
double BremsstrahlungElectronScatteringDistribution::correlatedEvaluateCDFUnitBased(
                                        const double incoming_energy,
                                        const double photon_energy ) const
{
  return d_bremsstrahlung_scattering_distribution->correlatedEvaluateSecondaryConditionalCDF(
            incoming_energy,
            photon_energy,
            1e-7,
            incoming_energy );
}

// Evaluate the CDF value for a given incoming and photon energy
double BremsstrahlungElectronScatteringDistribution::correlatedEvaluateCDFExact(
                                        const double incoming_energy,
                                        const double photon_energy ) const
{
  return d_bremsstrahlung_scattering_distribution->evaluateSecondaryConditionalCDFExact(
            incoming_energy,
            photon_energy );
}

// Sample a secondary energy from the distribution
double BremsstrahlungElectronScatteringDistribution::sampleUnitBased(
            const double incoming_energy ) const
{
  // Sample the photon energy
  return d_bremsstrahlung_scattering_distribution->sampleSecondaryConditional(
            incoming_energy );
}

// Sample a secondary energy from the distribution
double BremsstrahlungElectronScatteringDistribution::correlatedSampleUnitBased(
             const double incoming_energy ) const
{
  // Sample the photon energy
  return d_bremsstrahlung_scattering_distribution->correlatedSampleSecondaryConditional(
            incoming_energy,
            1e-7,
            incoming_energy );
}

// Sample a secondary energy from the distribution
double BremsstrahlungElectronScatteringDistribution::correlatedSampleExact(
             const double incoming_energy ) const
{
  // Sample the photon energy
  return d_bremsstrahlung_scattering_distribution->sampleSecondaryConditionalExact(
            incoming_energy );
}

// Sample the outgoing photon direction from the analytical function
double BremsstrahlungElectronScatteringDistribution::SampleDipoleAngle(
                                          const double incoming_electron_energy,
                                          const double photon_energy  ) const
{
  // get the velocity of the electron divided by the speed of light beta = v/c
  double beta = sqrt ( Utility::calculateDimensionlessRelativisticSpeedSquared(
                          Utility::PhysicalConstants::electron_rest_mass_energy,
                          incoming_electron_energy ) );

  double scaled_random_number =
            2.0 * Utility::RandomNumberGenerator::getRandomNumber<double>();

  double parameter = -( 1.0 + beta );

  return ( scaled_random_number        + parameter )/
         ( scaled_random_number * beta + parameter );
}

/* Sample the outgoing photon direction using the 2BS sampling routine of
 * Kock and Motz
 */
double BremsstrahlungElectronScatteringDistribution::Sample2BSAngle(
                                        const double incoming_electron_energy,
                                        const double photon_energy ) const
{
  double outgoing_electron_energy = incoming_electron_energy - photon_energy;
  double ratio = outgoing_electron_energy/incoming_electron_energy;
  double two_ratio = 2.0*ratio;
  double parameter = ( 1.0 + ratio*ratio );

  // calculate the minimum, mid, and maximum values of x
  double x_min = 0;
  double x_mid = 1.0;
  double x_max = Utility::PhysicalConstants::pi*Utility::PhysicalConstants::pi*
                 incoming_electron_energy*incoming_electron_energy;

  // Calculate the rejection function, g(x), for the minimum, mid, and maximum values of x
  double g_x_min = Calculate2BSRejection( outgoing_electron_energy,
                                          two_ratio,
                                          parameter,
                                          x_min );
  double g_x_mid = Calculate2BSRejection( outgoing_electron_energy,
                                          two_ratio,
                                          parameter,
                                          x_mid );
  double g_x_max = Calculate2BSRejection( outgoing_electron_energy,
                                          two_ratio,
                                          parameter,
                                          x_max );

  bool rejected = true;

  double rand1, rand;

  while( rejected )
  {
    rand = Utility::RandomNumberGenerator::getRandomNumber<double>();

    // sample for theta
    double theta = sqrt( rand/( 1.0 - rand + 1.0/x_max ) )/
                   incoming_electron_energy;

    double x = sqrt( incoming_electron_energy*theta );

    // Calculate the rejection function
    double g = Calculate2BSRejection( outgoing_electron_energy,
                                      two_ratio,
                                      parameter,
                                      x );

    // Normalized the rejection function
    g /= std::max( std::max( g_x_min, g_x_max ), g_x_mid );

    // Apply rejection scheme
    rand1 = Utility::RandomNumberGenerator::getRandomNumber<double>();

    if( rand1 < g )
    {
      return cos(theta);
    }
  }
}

// Calculate the rejection function for the 2BS sampling routine
double BremsstrahlungElectronScatteringDistribution::Calculate2BSRejection(
                                          const double outgoing_electron_energy,
                                          const double two_ratio,
                                          const double parameter1,
                                          const double x ) const
{
  double parameter2 = ( 1.0 + x )*( 1.0 + x );

  double m = log( ( parameter1 - two_ratio )/
             ( 4.0*outgoing_electron_energy*outgoing_electron_energy ) +
             pow( d_atomic_number, 2.0/3.0)/( 12321*parameter2 ) );

  return 3.0*parameter1 - two_ratio -
         ( 4.0 + m )*( parameter1 - 2.0*x*two_ratio/parameter2 );

}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_BremsstrahlungElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
