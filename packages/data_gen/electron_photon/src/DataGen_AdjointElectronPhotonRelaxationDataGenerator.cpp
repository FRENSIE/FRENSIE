//---------------------------------------------------------------------------//
//!
//! \file   DataGen_AdjointElectronPhotonRelaxationDataGenerator.cpp
//! \author Luke Kersting, Alex Robinson
//! \brief  The adjoint electron-photon-relaxation data generator base class decl.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "DataGen_AdjointElectronPhotonRelaxationDataGenerator.hpp"
#include "Utility_ContractException.hpp"

namespace DataGen{

// Constructor
AdjointElectronPhotonRelaxationDataGenerator::AdjointElectronPhotonRelaxationDataGenerator(
                                             const unsigned atomic_number,
                                             const double min_photon_energy,
                                             const double max_photon_energy,
                                             const double min_electron_energy,
                                             const double max_electron_energy )
  : d_atomic_number( atomic_number ),
    d_min_photon_energy( min_photon_energy ),
    d_max_photon_energy( max_photon_energy ),
    d_min_electron_energy( min_electron_energy ),
    d_max_electron_energy( max_electron_energy ),
    d_default_grid_convergence_tol( 0.001 ),
    d_default_absolute_diff_tol( 1e-12 ),
    d_default_distance_tol( 1e-14 )
{
  // Make sure the atomic number is valid
  testPrecondition( atomic_number <= 100u );
  // Make sure the photon energy limits are valid
  testPrecondition( min_photon_energy > 0.0 );
  testPrecondition( min_photon_energy < max_photon_energy );
  // Make sure the electron energy limits are valid
  testPrecondition( min_electron_energy > 0.0 );
  testPrecondition( min_electron_energy < max_electron_energy );
}

// Get the atomic number
unsigned AdjointElectronPhotonRelaxationDataGenerator::getAtomicNumber() const
{
  return d_atomic_number;
}

// Set the min photon energy
void AdjointElectronPhotonRelaxationDataGenerator::setMinPhotonEnergy(
                                               const double min_photon_energy )
{
  // Make sure the min photon energy is valid
  testPrecondition( min_photon_energy > 0.0 );

  d_min_photon_energy = min_photon_energy;
}

// Return the min photon energy
double AdjointElectronPhotonRelaxationDataGenerator::getMinPhotonEnergy() const
{
  return d_min_photon_energy;
}

// Set the max photon energy
void AdjointElectronPhotonRelaxationDataGenerator::setMaxPhotonEnergy(
                                               const double max_photon_energy )
{
  // Make sure the max photon energy is valid
  testPrecondition( d_min_photon_energy < max_photon_energy );

  d_max_photon_energy = max_photon_energy;
}
  
// Return the max photon energy
double AdjointElectronPhotonRelaxationDataGenerator::getMaxPhotonEnergy() const
{
  return d_max_photon_energy;
}

//! Set the min electron energy
void AdjointElectronPhotonRelaxationDataGenerator::setMinElectronEnergy(
                                             const double min_electron_energy )
{
  // Make sure the min electron energy is valid
  testPrecondition( min_electron_energy > 0.0 );

  d_min_electron_energy = min_electron_energy;
}
  
// Return the min electron energy
double AdjointElectronPhotonRelaxationDataGenerator::getMinElectronEnergy() const
{
  return d_min_electron_energy;
}

// Set the max electron energy
void AdjointElectronPhotonRelaxationDataGenerator::setMaxElectronEnergy(
                                             const double max_electron_energy )
{
  // Make sure the max electron energy is valid
  testPrecondition( d_min_electron_energy < max_electron_energy );

  d_max_electron_energy = max_electron_energy;
}
  
// Return the max electron energy
double AdjointElectronPhotonRelaxationDataGenerator::getMaxElectronEnergy() const
{
  return d_max_electron_energy;
}

// Set the default grid convergence tolerance
void AdjointElectronPhotonRelaxationDataGenerator::setDefaultGridConvergenceTolerance(
                                                 const double convergence_tol )
{
  // Make sure the convergence tolerance is valid
  testPrecondition( convergence_tol <= 1.0 );
  testPrecondition( convergence_tol > 0.0 );

  d_default_grid_convergence_tol = convergence_tol;
}

// Get the default grid convergence tolerance
double AdjointElectronPhotonRelaxationDataGenerator::getDefaultGridConvergenceTolerance() const
{
  return d_default_grid_convergence_tol;
}

// Set the default absolute difference tolerance
void AdjointElectronPhotonRelaxationDataGenerator::setDefaultAbsoluteDifferenceTolerance(
                                               const double absolute_diff_tol )
{
  // Make sure the absolute difference tolerance is valid
  testPrecondition( absolute_diff_tol <= 1.0 );
  testPrecondition( absolute_diff_tol >= 0.0 );

  d_default_absolute_diff_tol = absolute_diff_tol;
}

// Get the default absolute difference tolerance
double AdjointElectronPhotonRelaxationDataGenerator::getDefaultAbsoluteDifferenceTolerance() const
{
  return d_default_absolute_diff_tol;
}

// Set the default distance tolerance
void AdjointElectronPhotonRelaxationDataGenerator::setDefaultDistanceTolerance(
                                                    const double distance_tol )
{
  // Make sure the distance tolerance is valid
  testPrecondition( distance_tol <= 1.0 );
  testPrecondition( distance_tol >= 0.0 );

  d_default_distance_tol = distance_tol;
}

// Get the default distance tolerance
double AdjointElectronPhotonRelaxationDataGenerator::getDefaultDistanceTolerance() const
{
  return d_default_distance_tol;
}

} // end DataGen

//---------------------------------------------------------------------------//
// end DataGen_AdjointElectronPhotonRelaxationDataGenerator.cpp
//---------------------------------------------------------------------------//
