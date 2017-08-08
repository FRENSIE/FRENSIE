//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ScreenedRutherfordElasticElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  The electron screened Rutherford elastic scattering distribution definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ScreenedRutherfordElasticElectronScatteringDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_DirectionHelpers.hpp"
#include "Utility_KinematicHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"

namespace MonteCarlo{

// Constructor
ScreenedRutherfordElasticElectronScatteringDistribution::ScreenedRutherfordElasticElectronScatteringDistribution(
    const ElasticDistribution& elastic_cutoff_distribution,
    const int atomic_number )
  : d_elastic_cutoff_distribution( elastic_cutoff_distribution )
{
  // Make sure the array is valid
  testPrecondition( d_elastic_cutoff_distribution.use_count() > 0 );

  d_elastic_traits.reset( new ElasticTraits( atomic_number ) );
}

// Evaluate the distribution at the given energy and scattering angle cosine
//! \details Because the scattering angle cosine is very close to one, precision will be lost.
double ScreenedRutherfordElasticElectronScatteringDistribution::evaluate(
        const double incoming_energy,
        const double scattering_angle_cosine ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= ElasticTraits::mu_peak );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  double eta = d_elastic_traits->evaluateMoliereScreeningConstant( incoming_energy );

  return this->evaluate( incoming_energy, scattering_angle_cosine, eta );
}

// Evaluate the distribution at the given energy and scattering angle cosine
//! \details Because the scattering angle cosine is very close to one, precision will be lost.
double ScreenedRutherfordElasticElectronScatteringDistribution::evaluate(
        const double incoming_energy,
        const double scattering_angle_cosine,
        const double eta ) const
{
  // Make sure the energy, eta and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= ElasticTraits::mu_peak );
  testPrecondition( scattering_angle_cosine <= 1.0 );
  testPrecondition( eta > 0.0 );

  double delta_mu = 1.0L - scattering_angle_cosine;

  double cutoff_pdf =
    d_elastic_cutoff_distribution->evaluate( incoming_energy, ElasticTraits::mu_peak );

  double pdf = cutoff_pdf*
            ( ElasticTraits::delta_mu_peak + eta )*( ElasticTraits::delta_mu_peak + eta )/(
            ( delta_mu + eta )*( delta_mu + eta ) );

  return pdf;
}


// Evaluate the PDF at the given energy and scattering angle cosine
double ScreenedRutherfordElasticElectronScatteringDistribution::evaluatePDF(
        const double incoming_energy,
        const double scattering_angle_cosine ) const
{
  // Make sure the energy, eta and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= ElasticTraits::mu_peak );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  double eta = d_elastic_traits->evaluateMoliereScreeningConstant( incoming_energy );

  return this->evaluatePDF( incoming_energy, scattering_angle_cosine, eta );
}

// Evaluate the PDF at the given energy and scattering angle cosine
double ScreenedRutherfordElasticElectronScatteringDistribution::evaluatePDF(
        const double incoming_energy,
        const double scattering_angle_cosine,
        const double eta ) const
{
  // Make sure the energy, eta and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= ElasticTraits::mu_peak );
  testPrecondition( scattering_angle_cosine <= 1.0 );
  testPrecondition( eta > 0.0 );

  double delta_mu = 1.0L - scattering_angle_cosine;

  double cutoff_pdf =
    d_elastic_cutoff_distribution->evaluatePDF( incoming_energy, ElasticTraits::mu_peak );

  return cutoff_pdf*
            ( ElasticTraits::delta_mu_peak + eta )*( ElasticTraits::delta_mu_peak + eta )/(
            ( delta_mu + eta )*( delta_mu + eta ) );
}

// Evaluate the integrated distribution at the given energy
double ScreenedRutherfordElasticElectronScatteringDistribution::evaluateIntegrated(
        const double incoming_energy ) const
{
  // Make sure the energy is valid
  testPrecondition( incoming_energy > 0.0 );

  double cutoff_pdf =
    d_elastic_cutoff_distribution->evaluate( incoming_energy, ElasticTraits::mu_peak );

  double eta = d_elastic_traits->evaluateMoliereScreeningConstant( incoming_energy );

  return this->evaluateIntegratedPDF( cutoff_pdf, eta );
}

// Evaluate the integrated PDF at the given energy
double ScreenedRutherfordElasticElectronScatteringDistribution::evaluateIntegratedPDF(
        const double incoming_energy ) const
{
  // Make sure the energy is valid
  testPrecondition( incoming_energy > 0.0 );

  double cutoff_pdf =
    d_elastic_cutoff_distribution->evaluatePDF( incoming_energy, ElasticTraits::mu_peak );

  double eta = d_elastic_traits->evaluateMoliereScreeningConstant( incoming_energy );

  return this->evaluateIntegratedPDF( cutoff_pdf, eta );
}

// Evaluate the integrated PDF at the given energy
double ScreenedRutherfordElasticElectronScatteringDistribution::evaluateIntegratedPDF(
        const double cutoff_pdf,
        const double eta ) const
{
  // Make sure the cutoff pdf and eta are valid
  testPrecondition( cutoff_pdf >= 0.0 );
  testPrecondition( eta > 0.0 );

  return cutoff_pdf*ElasticTraits::delta_mu_peak*( ElasticTraits::delta_mu_peak + eta )/( eta );
}

// Evaluate the CDF
double ScreenedRutherfordElasticElectronScatteringDistribution::evaluateCDF(
        const double incoming_energy,
        const double scattering_angle_cosine ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= ElasticTraits::mu_peak );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  double eta = d_elastic_traits->evaluateMoliereScreeningConstant( incoming_energy );

  return this->evaluateCDF( incoming_energy, scattering_angle_cosine, eta );
}

// Evaluate the CDF
double ScreenedRutherfordElasticElectronScatteringDistribution::evaluateCDF(
        const double incoming_energy,
        const double scattering_angle_cosine,
        const double eta ) const
{
  // Make sure the energy, eta and angle cosine are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= ElasticTraits::mu_peak );
  testPrecondition( scattering_angle_cosine <= 1.0 );
  testPrecondition( eta > 0.0 );

  double delta_mu = 1.0L - scattering_angle_cosine;

  return ( ElasticTraits::delta_mu_peak + eta )/( delta_mu + eta )*
         ( delta_mu/ElasticTraits::delta_mu_peak );
}

// Sample an outgoing energy and direction from the distribution
void ScreenedRutherfordElasticElectronScatteringDistribution::sample(
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
void ScreenedRutherfordElasticElectronScatteringDistribution::sampleAndRecordTrials(
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
void ScreenedRutherfordElasticElectronScatteringDistribution::scatterElectron(
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
void ScreenedRutherfordElasticElectronScatteringDistribution::scatterAdjointElectron(
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
/* \details The CDF is inverted to create the sampling routine.
 * mu = ( eta mu_p + ( 1 + eta )( 1 - mu_p )CDF )/
 *      ( eta      +            ( 1 - mu_p )CDF )
 */
void ScreenedRutherfordElasticElectronScatteringDistribution::sampleAndRecordTrialsImpl(
                                                const double incoming_energy,
                                                double& scattering_angle_cosine,
                                                unsigned& trials ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );

  // Increment the number of trials
  ++trials;

  double random_number =
              Utility::RandomNumberGenerator::getRandomNumber<double>();

  double eta = d_elastic_traits->evaluateMoliereScreeningConstant( incoming_energy );

  scattering_angle_cosine =
        ( ElasticTraits::mu_peak * eta +
        ( 1.0L + eta ) * ElasticTraits::delta_mu_peak * random_number )/
        ( eta + ElasticTraits::delta_mu_peak * random_number );

  // Make sure the scattering angle cosine is valid
  testPostcondition( scattering_angle_cosine >= ElasticTraits::mu_peak );
  testPostcondition( scattering_angle_cosine <= 1.0 );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ScreenedRutherfordElasticElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
