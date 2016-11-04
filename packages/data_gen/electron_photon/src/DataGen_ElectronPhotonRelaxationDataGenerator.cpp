//---------------------------------------------------------------------------//
//!
//! \file   DataGen_ElectronPhotonRelaxationDataGenerator.cpp
//! \author Alex Robinson
//! \brief  The electron-photon-relaxation data generator base class decl.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "DataGen_ElectronPhotonRelaxationDataGenerator.hpp"
#include "Utility_ContractException.hpp"

namespace DataGen{

// Constructor
ElectronPhotonRelaxationDataGenerator::ElectronPhotonRelaxationDataGenerator(
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
    d_default_grid_generator(
            new Utility::GridGenerator<Utility::LinLin>( 1e-3, 1e-13, 1e-13 ) )
{
  // Make sure the atomic number is valid
  testPrecondition( atomic_number <= 100u );
  // Make sure the photon energy limits are valid
  testPrecondition( min_photon_energy > 0.0 );
  testPrecondition( min_photon_energy < max_photon_energy );
  // Make sure the electron energy limits are valid
  testPrecondition( min_electron_energy > 0.0 );
  testPrecondition( min_electron_energy < max_electron_energy );
  // Have the default grid generator throw exception on dirty convergence
  d_default_grid_generator->throwExceptionOnDirtyConvergence();
}

// Get the atomic number
unsigned ElectronPhotonRelaxationDataGenerator::getAtomicNumber() const
{
  return d_atomic_number;
}

// Set the min photon energy
void ElectronPhotonRelaxationDataGenerator::setMinPhotonEnergy(
                                               const double min_photon_energy )
{
  // Make sure the min photon energy is valid
  testPrecondition( min_photon_energy > 0.0 );

  d_min_photon_energy = min_photon_energy;
}

// Return the min photon energy
double ElectronPhotonRelaxationDataGenerator::getMinPhotonEnergy() const
{
  return d_min_photon_energy;
}

// Set the max photon energy
void ElectronPhotonRelaxationDataGenerator::setMaxPhotonEnergy(
                                               const double max_photon_energy )
{
  // Make sure the max photon energy is valid
  testPrecondition( d_min_photon_energy < max_photon_energy );

  d_max_photon_energy = max_photon_energy;
}

// Return the max photon energy
double ElectronPhotonRelaxationDataGenerator::getMaxPhotonEnergy() const
{
  return d_max_photon_energy;
}

// Set the min electron energy
void ElectronPhotonRelaxationDataGenerator::setMinElectronEnergy(
                                             const double min_electron_energy )
{
  // Make sure the min electron energy is valid
  testPrecondition( min_electron_energy > 0.0 );

  d_min_electron_energy = min_electron_energy;
}

// Return the min electron energy
double ElectronPhotonRelaxationDataGenerator::getMinElectronEnergy() const
{
  return d_min_electron_energy;
}

// Set the max electron energy
void ElectronPhotonRelaxationDataGenerator::setMaxElectronEnergy(
                                             const double max_electron_energy )
{
  // Make sure the max electron energy is valid
  testPrecondition( d_min_electron_energy < max_electron_energy );

  d_max_electron_energy = max_electron_energy;
}

// Return the max electron energy
double ElectronPhotonRelaxationDataGenerator::getMaxElectronEnergy() const
{
  return d_max_electron_energy;
}

// Set the default grid convergence tolerance
void ElectronPhotonRelaxationDataGenerator::setDefaultGridConvergenceTolerance(
                                                 const double convergence_tol )
{
  // Make sure the convergence tolerance is valid
  testPrecondition( convergence_tol <= 1.0 );
  testPrecondition( convergence_tol > 0.0 );

  d_default_grid_generator->setConvergenceTolerance( convergence_tol );
}

// Get the default grid convergence tolerance
double ElectronPhotonRelaxationDataGenerator::getDefaultGridConvergenceTolerance() const
{
  return d_default_grid_generator->getConvergenceTolerance();
}

// Set the default grid absolute difference tolerance
void ElectronPhotonRelaxationDataGenerator::setDefaultGridAbsoluteDifferenceTolerance(
                                               const double absolute_diff_tol )
{
  // Make sure the absolute difference tolerance is valid
  testPrecondition( absolute_diff_tol <= 1.0 );
  testPrecondition( absolute_diff_tol >= 0.0 );

  d_default_grid_generator->setAbsoluteDifferenceTolerance(absolute_diff_tol);
}

// Get the default grid absolute difference tolerance
double ElectronPhotonRelaxationDataGenerator::getDefaultGridAbsoluteDifferenceTolerance() const
{
  return d_default_grid_generator->getAbsoluteDifferenceTolerance();
}

// Set the default grid distance tolerance
void ElectronPhotonRelaxationDataGenerator::setDefaultGridDistanceTolerance(
                                                    const double distance_tol )
{
  // Make sure the distance tolerance is valid
  testPrecondition( distance_tol <= 1.0 );
  testPrecondition( distance_tol >= 0.0 );

  d_default_grid_generator->setDistanceTolerance( distance_tol );
}

// Get the default grid distance tolerance
double ElectronPhotonRelaxationDataGenerator::getDefaultGridDistanceTolerance() const
{
  return d_default_grid_generator->getDistanceTolerance();
}

// Set the basic data
void ElectronPhotonRelaxationDataGenerator::setBasicData(
    Data::ElectronPhotonRelaxationVolatileDataContainer& data_container ) const
{
  data_container.setAtomicNumber( d_atomic_number );
  data_container.setMinPhotonEnergy( d_min_photon_energy );
  data_container.setMaxPhotonEnergy( d_max_photon_energy );
  data_container.setMinElectronEnergy( d_min_electron_energy );
  data_container.setMaxElectronEnergy( d_max_electron_energy );
}
  
// Set the default converge parameters
void ElectronPhotonRelaxationDataGenerator::setDefaultConvergenceParameters(
    Data::ElectronPhotonRelaxationVolatileDataContainer& data_container ) const
{
  data_container.setGridConvergenceTolerance( d_default_grid_generator->getConvergenceTolerance() );
  data_container.setGridAbsoluteDifferenceTolerance( d_default_grid_generator->getAbsoluteDifferenceTolerance() );
  data_container.setGridDistanceTolerance( d_default_grid_generator->getDistanceTolerance() );
}

//! Get a default grid generator (Lin-Lin grid)
const Utility::GridGenerator<Utility::LinLin>&
ElectronPhotonRelaxationDataGenerator::getDefaultGridGenerator() const
{
  return *d_default_grid_generator;
}

} // end DataGen

//---------------------------------------------------------------------------//
// end DataGen_ElectronPhotonRelaxationDataGenerator.cpp
//---------------------------------------------------------------------------//
