//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SimulationElectronProperties.cpp
//! \author Alex Robinson, Luke Kersting
//! \brief  Simulation electron properties class def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_SimulationElectronProperties.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// The absolute min electron energy
const double SimulationElectronProperties::absolute_min_electron_energy = 1.5e-5;

// The minimum electron energy (MeV)
double SimulationElectronProperties::min_electron_energy =
  SimulationElectronProperties::absolute_min_electron_energy;

// The absolute max electron energy (MeV)
const double SimulationElectronProperties::absolute_max_electron_energy = 20.0;

// The max electron energy (MeV)
double SimulationElectronProperties::max_electron_energy =
  SimulationElectronProperties::absolute_max_electron_energy;

// The atomic relaxation mode (true = on - default, false = off)
bool SimulationElectronProperties::atomic_relaxation_mode_on = true;

// The bremsstrahlung photon angular distribution function (2BS by default)
BremsstrahlungAngularDistributionType
  SimulationElectronProperties::bremsstrahlung_angular_distribution_function =
                             TWOBS_DISTRIBUTION;

// The elastic cutoff angle cosine (default 1.0)
double SimulationElectronProperties::elastic_cutoff_angle_cosine = 1.0;

// The number of electron has grid bins
unsigned SimulationElectronProperties::num_electron_hash_grid_bins = 1000;

// Set the minimum electron energy (MeV)
void SimulationElectronProperties::setMinElectronEnergy( const double energy )
{
  // Make sure the energy is valid
  testPrecondition(energy >= SimulationElectronProperties::absolute_min_electron_energy);
  testPrecondition( energy < SimulationElectronProperties::max_electron_energy );

  SimulationElectronProperties::min_electron_energy = energy;
}

// Set the maximum electron energy (MeV)
void SimulationElectronProperties::setMaxElectronEnergy( const double energy )
{
  // Make sure the energy is valid
  testPrecondition( energy > SimulationElectronProperties::min_electron_energy );
  testPrecondition(energy <= SimulationElectronProperties::absolute_max_electron_energy);

  SimulationElectronProperties::max_electron_energy = energy;
}

// Set atomic relaxation mode to off (on by default)
void SimulationElectronProperties::setAtomicRelaxationModeOff()
{
  SimulationElectronProperties::atomic_relaxation_mode_on = false;
}

// Set the bremsstrahlung photon angular distribution function (2BS by default)
void SimulationElectronProperties::setBremsstrahlungAngularDistributionFunction(
                          const BremsstrahlungAngularDistributionType function )
{
  SimulationElectronProperties::bremsstrahlung_angular_distribution_function = function;
}

// Set the elastic cutoff angle cosine (mu = 0.999999 by default)
void SimulationElectronProperties::setElasticCutoffAngleCosine(
                          const double cutoff_angle_cosine )
{
  SimulationElectronProperties::elastic_cutoff_angle_cosine =
    cutoff_angle_cosine;
}

// Set the number of electron hash grid bins
void SimulationElectronProperties::setNumberOfElectronHashGridBins( const unsigned bins )
{
  // Make sure the number of bins is valid
  testPrecondition( bins >= 1 );

  SimulationElectronProperties::num_electron_hash_grid_bins = bins;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_SimulationElectronProperties.cpp
//---------------------------------------------------------------------------//
