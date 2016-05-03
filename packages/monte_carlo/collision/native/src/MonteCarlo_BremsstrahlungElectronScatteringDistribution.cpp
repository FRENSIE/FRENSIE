//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BremsstrahlungElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  The electron bremsstrahlung scattering distribution definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_BremsstrahlungElectronScatteringDistribution.hpp"
#include "MonteCarlo_TwoDDistributionHelpers.hpp"
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
    const BremsstrahlungDistribution& bremsstrahlung_scattering_distribution )
  : d_bremsstrahlung_scattering_distribution( bremsstrahlung_scattering_distribution )
{
  // Make sure the array is valid
  testPrecondition( d_bremsstrahlung_scattering_distribution.size() > 0 );

  // Use simple analytical photon angular distribution
  d_angular_distribution_func = boost::bind<double>( 
           &BremsstrahlungElectronScatteringDistribution::SampleDipoleAngle,
           boost::cref( *this ),
           _1,
           _2 );
}

// Constructor with detailed tabular photon angular distribution
BremsstrahlungElectronScatteringDistribution::BremsstrahlungElectronScatteringDistribution(
    const BremsstrahlungDistribution& bremsstrahlung_scattering_distribution,
    const Teuchos::RCP<Utility::OneDDistribution>& angular_distribution,
    const double lower_cutoff_energy,
    const double upper_cutoff_energy )
  : d_bremsstrahlung_scattering_distribution( bremsstrahlung_scattering_distribution ),
    d_angular_distribution( angular_distribution ),
    d_lower_cutoff_energy( lower_cutoff_energy ),
    d_upper_cutoff_energy( upper_cutoff_energy )
{
  // Make sure the arraies are valid
  testPrecondition( d_bremsstrahlung_scattering_distribution.size() > 0 );
  testPrecondition( !d_angular_distribution.is_null() );

  // Use detailed photon angular distribution
  d_angular_distribution_func = boost::bind<double>( 
            &BremsstrahlungElectronScatteringDistribution::SampleTabularAngle,
            boost::cref( *this ),
            _1,
            _2 );
}

// Constructor with detailed 2BS photon angular distribution
BremsstrahlungElectronScatteringDistribution::BremsstrahlungElectronScatteringDistribution(
  const BremsstrahlungDistribution& bremsstrahlung_scattering_distribution,
  const int atomic_number )
  : d_bremsstrahlung_scattering_distribution( bremsstrahlung_scattering_distribution ),
    d_atomic_number( atomic_number )
{
  // Make sure the arraies are valid
  testPrecondition( d_bremsstrahlung_scattering_distribution.size() > 0 );

  // Use detailed photon angular distribution
  d_angular_distribution_func = boost::bind<double>( 
		    &BremsstrahlungElectronScatteringDistribution::Sample2BSAngle,
		    boost::cref( *this ),
                   _1,
                   _2 );
}

// Return the min incoming energy
double BremsstrahlungElectronScatteringDistribution::getMinEnergy() const
{
  return d_bremsstrahlung_scattering_distribution.front().first;
}

// Return the Max incoming energy
double BremsstrahlungElectronScatteringDistribution::getMaxEnergy() const
{
  return d_bremsstrahlung_scattering_distribution.back().first;
}

// Return the max incoming electron energy for a given outgoing electron energy
double BremsstrahlungElectronScatteringDistribution::getMaxIncomingEnergyAtOutgoingEnergy( 
        const double energy ) const
{
  // Start at the largest energy grid point
  unsigned grid_point = d_bremsstrahlung_scattering_distribution.size();

  MonteCarlo::TwoDDistribution::const_iterator 
                                        highest_energy_bin, lowest_energy_bin;

  lowest_energy_bin = d_bremsstrahlung_scattering_distribution.begin();
  highest_energy_bin = d_bremsstrahlung_scattering_distribution.end();
  highest_energy_bin--;

  // Make sure the outgoing energy is possible
  testPrecondition( energy < highest_energy_bin->first -
                    highest_energy_bin->second->sampleWithRandomNumber( 0.0 ) );

  for ( highest_energy_bin; highest_energy_bin !=lowest_energy_bin; highest_energy_bin -- ) 
  {
    // Find the maximum photon energy for an electron at the grid_point energy
    double max_photon_energy = 
      highest_energy_bin->second->sampleWithRandomNumber( 1.0 );
  
    // Calculate the corresponding minimum outgoing electron energy
    double min_energy = highest_energy_bin->first - max_photon_energy;

    /* If the minimum outgoing electron energy is at or below the given energy 
       then return the grid_point energy */
    if ( min_energy <= energy )
    {
      return highest_energy_bin->first;
    }
  }
  return 0.0;
}

// Evaluate the PDF value for a given incoming and photon energy
double BremsstrahlungElectronScatteringDistribution::evaluatePDF( 
                     const double incoming_energy, 
                     const double photon_energy ) const
{
  // Make sure the energies are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( photon_energy > 0.0 );

  return MonteCarlo::evaluateTwoDDistributionCorrelatedPDF<BremsstrahlungDistribution>( 
                         incoming_energy,
                         photon_energy,
                         d_bremsstrahlung_scattering_distribution );
}

// Sample the photon energy and direction from the distribution
void BremsstrahlungElectronScatteringDistribution::sample( 
             const double incoming_energy,
             double& photon_energy,
             double& photon_angle_cosine ) const
{
  // Sample the photon energy
  photon_energy = sampleTwoDDistributionCorrelated<BremsstrahlungDistribution>( 
                                     incoming_energy,
                                     d_bremsstrahlung_scattering_distribution );

  // Sample the photon outgoing angle cosine
  photon_angle_cosine = d_angular_distribution_func( incoming_energy, 
                                                     photon_energy );
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
                                SubshellType& shell_of_interaction ) const
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

// Sample the detailed outgoing photon direction
double BremsstrahlungElectronScatteringDistribution::SampleTabularAngle( 
                                          const double incoming_electron_energy, 
                                          const double photon_energy ) const
{
    if ( incoming_electron_energy > d_upper_cutoff_energy )
  {
    return SampleDipoleAngle( incoming_electron_energy, photon_energy );
  }
  else 
  {
    if ( incoming_electron_energy > d_lower_cutoff_energy )
    {
      return d_angular_distribution->evaluate( photon_energy );
    }
    else
    {
    return SampleDipoleAngle( incoming_electron_energy, photon_energy );
    } 
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_BremsstrahlungElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
