//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BremsstrahlungElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  The electron bremsstrahlung scattering distribution definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_BremsstrahlungElectronScatteringDistribution.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_KinematicHelpers.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"

namespace MonteCarlo{

// Constructor with simple analytical photon angular distribution
BremsstrahlungElectronScatteringDistribution::BremsstrahlungElectronScatteringDistribution(
    const std::shared_ptr<const BasicBivariateDist>& bremsstrahlung_scattering_distribution,
    const bool bank_secondary_particles )
  : d_bremsstrahlung_scattering_distribution( bremsstrahlung_scattering_distribution ),
    d_bank_secondary_particles( bank_secondary_particles )
{
  // Make sure the array is valid
  testPrecondition( d_bremsstrahlung_scattering_distribution.use_count() > 0 );

  // Use simple analytical photon angular distribution
  d_angular_distribution_func = [this]( const double& incoming_energy,
                                        const double& photon_energy )
  {
        return this->SampleDipoleAngle( incoming_energy, photon_energy );
  };
}

// Constructor with detailed 2BS photon angular distribution
BremsstrahlungElectronScatteringDistribution::BremsstrahlungElectronScatteringDistribution(
    const int atomic_number,
    const std::shared_ptr<const BasicBivariateDist>& bremsstrahlung_scattering_distribution,
    const bool bank_secondary_particles )
  : d_atomic_number( atomic_number ),
    d_bremsstrahlung_scattering_distribution( bremsstrahlung_scattering_distribution ),
    d_bank_secondary_particles( bank_secondary_particles )
{
  // Make sure the arrays are valid
  testPrecondition( d_bremsstrahlung_scattering_distribution.use_count() > 0 );

  // Use detailed photon angular distribution
  d_angular_distribution_func = [this]( const double& incoming_energy,
                                        const double& photon_energy )
  {
        return this->Sample2BSAngle( incoming_energy, photon_energy );
  };
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

// Return the min outgoing photon energy
//! \details It is assumed that the minimum outgoing photon energy is 1e-7 MeV.
double BremsstrahlungElectronScatteringDistribution::getMinPhotonEnergy( const double incoming_energy ) const
{
  return 1e-7;
}

// Return the Max outgoing photon energy
/*! \details It is assumed that the maximum outgoing photon energy is the
 * incoming electron energy.
 */
double BremsstrahlungElectronScatteringDistribution::getMaxPhotonEnergy( const double incoming_energy ) const
{
  return incoming_energy;
}

// Evaluate the distribution for a given incoming and photon energy
double BremsstrahlungElectronScatteringDistribution::evaluate(
                     const double incoming_energy,
                     const double photon_energy ) const
{
  // Make sure the energies are valid
  testPrecondition( photon_energy > 0.0 );
  testPrecondition( photon_energy <= incoming_energy );

  // evaluate the distribution
  return d_bremsstrahlung_scattering_distribution->evaluate(
            incoming_energy,
            photon_energy,
            [self = this](const double& energy){return self->getMinPhotonEnergy( energy );},
            [self = this](const double& energy){return self->getMaxPhotonEnergy( energy );} );
}

// Evaluate the PDF value for a given incoming and photon energy
double BremsstrahlungElectronScatteringDistribution::evaluatePDF(
                     const double incoming_energy,
                     const double photon_energy ) const
{
  // Make sure the energies are valid
  testPrecondition( photon_energy > 0.0 );
  testPrecondition( photon_energy <= incoming_energy );

  // evaluate the distribution
  return d_bremsstrahlung_scattering_distribution->evaluateSecondaryConditionalPDF(
            incoming_energy,
            photon_energy,
            [self = this](const double& energy){return self->getMinPhotonEnergy( energy );},
            [self = this](const double& energy){return self->getMaxPhotonEnergy( energy );} );
}

// Evaluate the CDF value for a given incoming and photon energy
double BremsstrahlungElectronScatteringDistribution::evaluateCDF(
                     const double incoming_energy,
                     const double photon_energy ) const
{
  // Make sure the energies are valid
  testPrecondition( photon_energy > 0.0 );
  testPrecondition( photon_energy <= incoming_energy );

  // evaluate the distribution
  return d_bremsstrahlung_scattering_distribution->evaluateSecondaryConditionalCDF(
            incoming_energy,
            photon_energy,
            [self = this](const double& energy){return self->getMinPhotonEnergy( energy );},
            [self = this](const double& energy){return self->getMaxPhotonEnergy( energy );} );
}

// Sample the photon energy and direction from the distribution
void BremsstrahlungElectronScatteringDistribution::sample(
             const double incoming_energy,
             double& photon_energy,
             double& photon_angle_cosine ) const
{
  // Sample the photon energy
  photon_energy =
    d_bremsstrahlung_scattering_distribution->sampleSecondaryConditional(
      incoming_energy,
      [self = this](const double& energy){return self->getMinPhotonEnergy( energy );},
      [self = this](const double& energy){return self->getMaxPhotonEnergy( energy );} );

  // Sample the photon outgoing angle cosine
  photon_angle_cosine = d_angular_distribution_func( incoming_energy,
                                                     photon_energy );

  testPostcondition( incoming_energy > photon_energy );
  testPostcondition( photon_energy > 0.0 );
  testPostcondition( photon_angle_cosine <= 1.0 );
  testPostcondition( photon_angle_cosine >= -1.0 );
}

// Sample the photon energy from the distribution with a random number
double BremsstrahlungElectronScatteringDistribution::sampleWithRandomNumber(
             const double incoming_energy,
             const double random_number ) const
{
  // Sample the photon energy
  return d_bremsstrahlung_scattering_distribution->sampleSecondaryConditionalWithRandomNumber(
      incoming_energy,
      random_number,
      [self = this](const double& energy){return self->getMinPhotonEnergy( energy );},
      [self = this](const double& energy){return self->getMaxPhotonEnergy( energy );} );
}

// Sample an outgoing energy and direction and record the number of trials
void BremsstrahlungElectronScatteringDistribution::sampleAndRecordTrials(
                            const double incoming_energy,
                            double& photon_energy,
                            double& photon_angle_cosine,
                            Counter& trials ) const
{
  trials++;

  this->sample( incoming_energy, photon_energy, photon_angle_cosine );

}

// Randomly scatter the electron
void BremsstrahlungElectronScatteringDistribution::scatterElectron(
                          ElectronState& electron,
                          ParticleBank& bank,
                          Data::SubshellType& shell_of_interaction ) const
{
  // Sample the energy and angle of the bremsstrahlung photon
  double photon_energy, photon_angle_cosine;
  this->sample( electron.getEnergy(), photon_energy, photon_angle_cosine );

  // Check if bremsstrahlung photon will be banked
  if ( d_bank_secondary_particles )
  {
    // Create new photon
    std::shared_ptr<PhotonState> bremsstrahlung_photon(
                            new PhotonState( electron, true, true ) );

    // Set photon energy
    bremsstrahlung_photon->setEnergy( photon_energy );

    // Set the photon outgoing angle cosine
    bremsstrahlung_photon->rotateDirection( photon_angle_cosine,
                                            sampleAzimuthalAngle() );

    // Bank the photon
    bank.push( bremsstrahlung_photon );
  }

  // Set the new electron energy (if zero then set as gone)
  double outgoing_energy = electron.getEnergy() - photon_energy;
  if( outgoing_energy > 0.0 )
    electron.setEnergy( outgoing_energy );
  else
    electron.setAsGone();

  // Increment the electron generation number
  electron.incrementGenerationNumber();

  testPostcondition( photon_energy > 0.0 );
  testPostcondition( photon_angle_cosine <= 1.0 );
  testPostcondition( photon_angle_cosine >= -1.0 );
}

// Randomly scatter the positron
void BremsstrahlungElectronScatteringDistribution::scatterPositron(
                          PositronState& positron,
                          ParticleBank& bank,
                          Data::SubshellType& shell_of_interaction ) const
{
  // Sample the energy and angle of the bremsstrahlung photon
  double photon_energy, photon_angle_cosine;
  this->sample( positron.getEnergy(), photon_energy, photon_angle_cosine );

  // Check if bremsstrahlung photon will be banked
  if ( d_bank_secondary_particles )
  {
    // Create new photon
    std::shared_ptr<PhotonState> bremsstrahlung_photon(
                            new PhotonState( positron, true, true ) );

    // Set photon energy
    bremsstrahlung_photon->setEnergy( photon_energy );

    // Set the photon outgoing angle cosine
    bremsstrahlung_photon->rotateDirection( photon_angle_cosine,
                                            sampleAzimuthalAngle() );

    // Bank the photon
    bank.push( bremsstrahlung_photon );
  }

  // Set the new electron energy (if zero then set to negligible amount)
  double outgoing_energy = positron.getEnergy() - photon_energy;
  if( outgoing_energy > 0.0 )
    positron.setEnergy( outgoing_energy );
  else
    positron.setEnergy( 1e-15 );

  // Increment the positron generation number
  positron.incrementGenerationNumber();

  testPostcondition( photon_energy > 0.0 );
  testPostcondition( photon_angle_cosine <= 1.0 );
  testPostcondition( photon_angle_cosine >= -1.0 );
}

// Sample the outgoing photon direction from the analytical function
double BremsstrahlungElectronScatteringDistribution::SampleDipoleAngle(
                                          const double incoming_electron_energy,
                                          const double photon_energy  ) const
{
  // Make sure the energies are valid
  testPrecondition( photon_energy > 0.0 );
  testPrecondition( photon_energy <= incoming_electron_energy );

  // get the velocity of the electron divided by the speed of light beta = v/c
  double beta =
    std::sqrt( MonteCarlo::calculateDimensionlessRelativisticSpeedSquared(
                         Utility::PhysicalConstants::electron_rest_mass_energy,
                         incoming_electron_energy ) );

  double scaled_random_number =
            2.0 * Utility::RandomNumberGenerator::getRandomNumber<double>();

  double parameter = -( 1.0 + beta );

  double photon_angle_cosine = ( scaled_random_number        + parameter )/
                               ( scaled_random_number * beta + parameter );

  testPostcondition( photon_angle_cosine <= 1.0 );
  testPostcondition( photon_angle_cosine >= -1.0 );

  return photon_angle_cosine;
}

/* Sample the outgoing photon direction using the 2BS sampling routine of
 * Kock and Motz
 */
double BremsstrahlungElectronScatteringDistribution::Sample2BSAngle(
                                        const double incoming_electron_energy,
                                        const double photon_energy ) const
{
  // Make sure the energies are valid
  testPrecondition( photon_energy > 0.0 );
  testPrecondition( photon_energy <= incoming_electron_energy );

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
      testPostcondition( cos(theta) <= 1.0 );
      testPostcondition( cos(theta) >= -1.0 );

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
