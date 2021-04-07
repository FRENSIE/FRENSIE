//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ScreenedRutherfordElasticElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  The electron screened Rutherford elastic scattering distribution definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ScreenedRutherfordElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_KinematicHelpers.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"

namespace MonteCarlo{

// Constructor
ScreenedRutherfordElasticElectronScatteringDistribution::ScreenedRutherfordElasticElectronScatteringDistribution(
    const int atomic_number,
    const bool seltzer_modification_on )
{
  d_elastic_traits.reset( new ElasticTraits( atomic_number,
                                             seltzer_modification_on ) );
}

// Evaluate the distribution at the given energy and scattering angle cosine
/*! \details The returned value is not normalized to the elastic cutoff
 *  distribution. The correct normalized value can be calculated by multiplying
 *  the the returned value by the pdf of the cutoff distribution at mu peak.
 *  When the scattering angle cosine is very close to one, precision will be lost.
 */
double ScreenedRutherfordElasticElectronScatteringDistribution::evaluate(
        const double incoming_energy,
        const double scattering_angle_cosine ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= ElasticTraits::mu_peak );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  return this->evaluatePDF( incoming_energy, scattering_angle_cosine );
}

// Evaluate the distribution at the given energy and scattering angle cosine
/*! \details The returned value is not normalized to the elastic cutoff
 *  distribution. The correct normalized value can be calculated by multiplying
 *  the the returned value by the pdf of the cutoff distribution at mu peak.
 *  When the scattering angle cosine is very close to one, precision will be lost.
 */
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

  return this->evaluatePDF( incoming_energy, scattering_angle_cosine, eta );
}


// Evaluate the PDF at the given energy and scattering angle cosine
/*! \details The returned value is not normalized to the elastic cutoff
 *  distribution. The correct normalized value can be calculated by multiplying
 *  the the returned value by the pdf of the cutoff distribution at mu peak.
 *  When the scattering angle cosine is very close to one, precision will be lost.
 */
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
/*! \details The returned value is not normalized to the elastic cutoff
 *  distribution. The correct normalized value can be calculated by multiplying
 *  the the returned value by the pdf of the cutoff distribution at mu peak.
 *  When the scattering angle cosine is very close to one, precision will be lost.
 */
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

  return ( ElasticTraits::delta_mu_peak + eta )*( ElasticTraits::delta_mu_peak + eta )/(
         ( delta_mu + eta )*( delta_mu + eta ) );
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

  Counter trial_dummy;

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
                        Counter& trials ) const
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

  Counter trial_dummy;

  // Sample an outgoing direction
  this->sampleAndRecordTrialsImpl( electron.getEnergy(),
                                   scattering_angle_cosine,
                                   trial_dummy );

  shell_of_interaction =Data::UNKNOWN_SUBSHELL;

  // Set the new direction
  electron.rotateDirection( scattering_angle_cosine,
                            this->sampleAzimuthalAngle() );
}

// Randomly scatter the positron
void ScreenedRutherfordElasticElectronScatteringDistribution::scatterPositron(
         PositronState& positron,
         ParticleBank& bank,
         Data::SubshellType& shell_of_interaction ) const
{
  double scattering_angle_cosine;

  Counter trial_dummy;

  // Sample an outgoing direction
  this->sampleAndRecordTrialsImpl( positron.getEnergy(),
                                   scattering_angle_cosine,
                                   trial_dummy );

  shell_of_interaction =Data::UNKNOWN_SUBSHELL;

  // Set the new direction
  positron.rotateDirection( scattering_angle_cosine,
                            this->sampleAzimuthalAngle() );
}

// Randomly scatter the adjoint electron
void ScreenedRutherfordElasticElectronScatteringDistribution::scatterAdjointElectron(
                     AdjointElectronState& adjoint_electron,
                     ParticleBank& bank,
                     Data::SubshellType& shell_of_interaction ) const
{
  double scattering_angle_cosine;

  Counter trial_dummy;

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
                                                Counter& trials ) const
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
  testPostcondition( scattering_angle_cosine >= ElasticTraits::mu_peak - 1e-15 );
  testPostcondition( scattering_angle_cosine <= 1.0+1e-15 );

  // There will sometimes be roundoff error in which case the scattering angle
  // cosine should never be greater than 1
  scattering_angle_cosine = std::min( scattering_angle_cosine, 1.0 );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ScreenedRutherfordElasticElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
