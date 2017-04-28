//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ScreenedRutherfordElasticElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  The electron screened Rutherford elastic scattering distribution definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_ScreenedRutherfordElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_TwoDDistributionHelpers.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_KinematicHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_TabularDistribution.hpp"

namespace MonteCarlo{


// Initialize static member data

// The change scattering angle cosine below which the screened Rutherford distribution is used
double ScreenedRutherfordElasticElectronScatteringDistribution::s_cutoff_delta_mu = 1.0e-6;

// The scattering angle cosine above which the screened Rutherford distribution is used
double ScreenedRutherfordElasticElectronScatteringDistribution::s_cutoff_mu = 0.999999;

// The fine structure constant squared
double ScreenedRutherfordElasticElectronScatteringDistribution::s_fine_structure_const_squared=
        Utility::PhysicalConstants::fine_structure_constant *
        Utility::PhysicalConstants::fine_structure_constant;

// A parameter for moliere's screening factor  (1/2*(fsc/0.885)**2)
double ScreenedRutherfordElasticElectronScatteringDistribution::s_screening_param1 =
      ScreenedRutherfordElasticElectronScatteringDistribution::s_fine_structure_const_squared/
      ( 2.0*0.885*0.885 );

// Constructor
ScreenedRutherfordElasticElectronScatteringDistribution::ScreenedRutherfordElasticElectronScatteringDistribution(
    const ElasticDistribution& elastic_cutoff_distribution,
    const int atomic_number )
  : d_elastic_cutoff_distribution( elastic_cutoff_distribution ),
    d_atomic_number( atomic_number ),
    d_Z_two_thirds_power( pow( atomic_number, 2.0/3.0 ) ),
    d_screening_param2( 3.76*s_fine_structure_const_squared*
                              d_atomic_number*d_atomic_number )
{
  // Make sure the array is valid
  testPrecondition( d_elastic_cutoff_distribution.use_count() > 0 );
  // Make sure the atomic number is valid
  testPrecondition( d_atomic_number > 0 );
  testPrecondition( d_atomic_number <= 100u );
}

// Evaluate the distribution at the given energy and scattering angle cosine
//! \details Because the scattering angle cosine is very close to one, precision will be lost.
double ScreenedRutherfordElasticElectronScatteringDistribution::evaluate(
        const double incoming_energy,
        const double scattering_angle_cosine ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= s_cutoff_mu );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  double eta = evaluateMoliereScreeningConstant( incoming_energy );

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
  testPrecondition( scattering_angle_cosine >= s_cutoff_mu );
  testPrecondition( scattering_angle_cosine <= 1.0 );
  testPrecondition( eta > 0.0 );

  double delta_mu = 1.0 - scattering_angle_cosine;

  double cutoff_pdf =
    d_elastic_cutoff_distribution->evaluate( incoming_energy, s_cutoff_mu );

  double pdf = cutoff_pdf*
            ( s_cutoff_delta_mu + eta )*( s_cutoff_delta_mu + eta )/(
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
  testPrecondition( scattering_angle_cosine >= s_cutoff_mu );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  double eta = evaluateMoliereScreeningConstant( incoming_energy );

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
  testPrecondition( scattering_angle_cosine >= s_cutoff_mu );
  testPrecondition( scattering_angle_cosine <= 1.0 );
  testPrecondition( eta > 0.0 );

  double delta_mu = 1.0 - scattering_angle_cosine;

  double cutoff_pdf =
    d_elastic_cutoff_distribution->evaluatePDF( incoming_energy, s_cutoff_mu );

  return cutoff_pdf*
            ( s_cutoff_delta_mu + eta )*( s_cutoff_delta_mu + eta )/(
            ( delta_mu + eta )*( delta_mu + eta ) );
}

// Evaluate the integrated PDF at the given energy
double ScreenedRutherfordElasticElectronScatteringDistribution::evaluateIntegratedPDF(
        const double incoming_energy ) const
{
  // Make sure the energy is valid
  testPrecondition( incoming_energy > 0.0 );

  double eta = evaluateMoliereScreeningConstant( incoming_energy );

  return this->evaluateIntegratedPDF( incoming_energy, eta );
}

// Evaluate the integrated PDF at the given energy
double ScreenedRutherfordElasticElectronScatteringDistribution::evaluateIntegratedPDF(
        const double incoming_energy,
        const double eta ) const
{
  // Make sure the energy and eta are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( eta > 0.0 );

  double cutoff_pdf =
    d_elastic_cutoff_distribution->evaluatePDF( incoming_energy, s_cutoff_mu );

  return cutoff_pdf*s_cutoff_delta_mu*( s_cutoff_delta_mu + eta )/( eta );
}

// Evaluate the CDF
double ScreenedRutherfordElasticElectronScatteringDistribution::evaluateCDF(
        const double incoming_energy,
        const double scattering_angle_cosine ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= s_cutoff_mu );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  double eta = this->evaluateMoliereScreeningConstant( incoming_energy );

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
  testPrecondition( scattering_angle_cosine >= s_cutoff_mu );
  testPrecondition( scattering_angle_cosine <= 1.0 );
  testPrecondition( eta > 0.0 );

  double delta_mu = 1.0 - scattering_angle_cosine;

  return ( s_cutoff_delta_mu + eta )/( delta_mu + eta )*
         ( delta_mu/s_cutoff_delta_mu );
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

// Evaluate Moliere's atomic screening constant (modified by Seltzer) at the given electron energy
double ScreenedRutherfordElasticElectronScatteringDistribution::evaluateMoliereScreeningConstant(
                                              const double energy ) const
{
  // get the energy-momentum**2 of the electron in units of electron_rest_mass_energy
  double electron_energy_momentum_squared =
           Utility::calculateDimensionlessRelativisticMomentumSquared(
                          Utility::PhysicalConstants::electron_rest_mass_energy,
                          energy );

  // get the velocity of the electron divided by the speed of light beta = v/c
  double beta_squared = Utility::calculateDimensionlessRelativisticSpeedSquared(
           Utility::PhysicalConstants::electron_rest_mass_energy,
           energy );

  double screening_param3 = 1.0/beta_squared*sqrt( energy/
            ( energy + Utility::PhysicalConstants::electron_rest_mass_energy) );

 // Calculate Moliere's atomic screening constant
 return s_screening_param1 * 1.0/electron_energy_momentum_squared *
        d_Z_two_thirds_power * ( 1.13 + d_screening_param2*screening_param3 );
}

// Sample an outgoing direction from the distribution
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

  double eta = evaluateMoliereScreeningConstant( incoming_energy );

  scattering_angle_cosine =
        ( ( 1.0 - random_number*( 1.0 + eta ) )*s_cutoff_delta_mu + eta )/
        ( ( 1.0 - random_number )*s_cutoff_delta_mu + eta );

  // Make sure the scattering angle cosine is valid
  testPostcondition( scattering_angle_cosine >= s_cutoff_mu );
  testPostcondition( scattering_angle_cosine <= 1.0 );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ScreenedRutherfordElasticElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
