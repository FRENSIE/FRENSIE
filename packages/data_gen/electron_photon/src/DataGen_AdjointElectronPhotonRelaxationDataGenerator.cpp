//---------------------------------------------------------------------------//
//!
//! \file   DataGen_AdjointElectronPhotonRelaxationDataGenerator.cpp
//! \author Luke Kersting, Alex Robinson
//! \brief  The adjoint electron-photon-relaxation data generator base class decl.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "DataGen_AdjointElectronPhotonRelaxationDataGenerator.hpp"
#include "Utility_DesignByContract.hpp"

namespace DataGen{

// Constructor
AdjointElectronPhotonRelaxationDataGenerator::AdjointElectronPhotonRelaxationDataGenerator(
                                          const unsigned atomic_number,
                                          const double atomic_weight,
                                          const double min_photon_energy,
                                          const double max_photon_energy,
                                          const double min_electron_energy,
                                          const double max_electron_energy )
  : d_data_container(),
    d_default_photon_grid_generator(
           new Utility::GridGenerator<Utility::LinLin>( 1e-3, 1e-13, 1e-13 ) ),
    d_default_electron_grid_generator(
           new Utility::GridGenerator<Utility::LogLog>( 1e-3, 1e-13, 1e-13 ) ),
    d_two_d_interp( MonteCarlo::LOGLOGLOG_INTERPOLATION ),
    d_two_d_grid( MonteCarlo::UNIT_BASE_CORRELATED_GRID )
{
  // Make sure the atomic number is valid
  testPrecondition( atomic_number <= 100u );
  // Make sure the photon energy limits are valid
  testPrecondition( min_photon_energy > 0.0 );
  testPrecondition( min_photon_energy < max_photon_energy );
  // Make sure the electron energy limits are valid
  testPrecondition( min_electron_energy > 0.0 );
  testPrecondition( min_electron_energy < max_electron_energy );

  // Set the basic data
  d_data_container.setAtomicNumber( atomic_number );
  d_data_container.setAtomicWeight( atomic_weight );
  d_data_container.setMinPhotonEnergy( min_photon_energy );
  d_data_container.setMaxPhotonEnergy( max_photon_energy );
  d_data_container.setMinElectronEnergy( min_electron_energy );
  d_data_container.setMaxElectronEnergy( max_electron_energy );

  // Set some default tolerances and values
  d_data_container.setAdjointPhotonGridConvergenceTolerance( d_default_photon_grid_generator->getConvergenceTolerance() );
  d_data_container.setAdjointPhotonGridAbsoluteDifferenceTolerance( d_default_photon_grid_generator->getAbsoluteDifferenceTolerance() );
  d_data_container.setAdjointPhotonGridDistanceTolerance( d_default_photon_grid_generator->getDistanceTolerance() );

  d_data_container.setAdjointElectronGridConvergenceTolerance( d_default_electron_grid_generator->getConvergenceTolerance() );
  d_data_container.setAdjointElectronGridAbsoluteDifferenceTolerance( d_default_electron_grid_generator->getAbsoluteDifferenceTolerance() );
  d_data_container.setAdjointElectronGridDistanceTolerance( d_default_electron_grid_generator->getDistanceTolerance() );


  d_data_container.setAdjointPairProductionEnergyDistNormConstantEvaluationTolerance( 1e-3 );
  d_data_container.setAdjointPairProductionEnergyDistNormConstantNudgeValue( 1e-6 );
  d_data_container.setAdjointTripletProductionEnergyDistNormConstantEvaluationTolerance( 1e-3 );
  d_data_container.setAdjointTripletProductionEnergyDistNormConstantNudgeValue( 1e-6 );
  d_data_container.setAdjointIncoherentMaxEnergyNudgeValue( 0.2 );
  d_data_container.setAdjointIncoherentEnergyToMaxEnergyNudgeValue( 1e-6 );
  d_data_container.setAdjointIncoherentEvaluationTolerance( 0.001 );
  d_data_container.setAdjointIncoherentGridConvergenceTolerance( 0.001 );
  d_data_container.setAdjointIncoherentGridAbsoluteDifferenceTolerance( 1e-20 );
  d_data_container.setAdjointIncoherentGridDistanceTolerance( 1e-14 );
  d_data_container.setElectronTabularEvaluationTolerance( 1e-8 );
  d_data_container.setAdjointBremsstrahlungMaxEnergyNudgeValue( 0.2 );
  d_data_container.setAdjointBremsstrahlungEnergyToOutgoingEnergyNudgeValue( 1e-7 );
  d_data_container.setAdjointBremsstrahlungEvaluationTolerance( 1e-6 );
  d_data_container.setAdjointBremsstrahlungGridConvergenceTolerance( 0.001 );
  d_data_container.setAdjointBremsstrahlungAbsoluteDifferenceTolerance( 1e-16 );
  d_data_container.setAdjointBremsstrahlungDistanceTolerance( 1e-8 );
  d_data_container.setAdjointElectroionizationEvaluationTolerance( 1e-6 );
  d_data_container.setAdjointElectroionizationGridConvergenceTolerance( 0.001 );
  d_data_container.setAdjointElectroionizationAbsoluteDifferenceTolerance( 1e-16 );
  d_data_container.setAdjointElectroionizationDistanceTolerance( 1e-8 );
  d_data_container.setCutoffAngleCosine( 1.0 );
  d_data_container.setNumberOfAdjointMomentPreservingAngles( 0 );
  d_data_container.setElectronTwoDInterpPolicy( Utility::toString( MonteCarlo::LOGLOGLOG_INTERPOLATION ) );
  d_data_container.setElectronTwoDGridPolicy( Utility::toString( MonteCarlo::UNIT_BASE_CORRELATED_GRID ) );

  // Have the default grid generators throw exception on dirty convergence
  d_default_photon_grid_generator->throwExceptionOnDirtyConvergence();
  d_default_electron_grid_generator->throwExceptionOnDirtyConvergence();
}

// Constructor (existing data container)
AdjointElectronPhotonRelaxationDataGenerator::AdjointElectronPhotonRelaxationDataGenerator(
                           const boost::filesystem::path& file_name_with_path )
  : d_data_container( file_name_with_path ),
    d_default_photon_grid_generator( new Utility::GridGenerator<Utility::LinLin>(
                   d_data_container.getAdjointPhotonGridConvergenceTolerance(),
                   d_data_container.getAdjointPhotonGridAbsoluteDifferenceTolerance(),
                   d_data_container.getAdjointPhotonGridDistanceTolerance() ) ),
    d_default_electron_grid_generator( new Utility::GridGenerator<Utility::LogLog>(
                 d_data_container.getAdjointElectronGridConvergenceTolerance(),
                 d_data_container.getAdjointElectronGridAbsoluteDifferenceTolerance(),
                 d_data_container.getAdjointElectronGridDistanceTolerance() ) )
{
  // Have the default grid generators throw exception on dirty convergence
  d_default_photon_grid_generator->throwExceptionOnDirtyConvergence();
  d_default_electron_grid_generator->throwExceptionOnDirtyConvergence();
}

// Get the atomic number
unsigned AdjointElectronPhotonRelaxationDataGenerator::getAtomicNumber() const
{
  return d_data_container.getAtomicNumber();
}

// Set the min photon energy
void AdjointElectronPhotonRelaxationDataGenerator::setMinPhotonEnergy(
                                               const double min_photon_energy )
{
  // Make sure the min photon energy is valid
  testPrecondition( min_photon_energy > 0.0 );

  d_data_container.setMinPhotonEnergy( min_photon_energy );
}

// Return the min photon energy
double AdjointElectronPhotonRelaxationDataGenerator::getMinPhotonEnergy() const
{
  return d_data_container.getMinPhotonEnergy();
}

// Set the max photon energy
void AdjointElectronPhotonRelaxationDataGenerator::setMaxPhotonEnergy(
                                               const double max_photon_energy )
{
  // Make sure the max photon energy is valid
  testPrecondition( d_data_container.getMinPhotonEnergy() < max_photon_energy );

  d_data_container.setMaxPhotonEnergy( max_photon_energy );
}

// Return the max photon energy
double AdjointElectronPhotonRelaxationDataGenerator::getMaxPhotonEnergy() const
{
  return d_data_container.getMaxPhotonEnergy();
}

//! Set the min electron energy
void AdjointElectronPhotonRelaxationDataGenerator::setMinElectronEnergy(
                                             const double min_electron_energy )
{
  // Make sure the min electron energy is valid
  testPrecondition( min_electron_energy > 0.0 );

  d_data_container.setMinElectronEnergy( min_electron_energy );
}

// Return the min electron energy
double AdjointElectronPhotonRelaxationDataGenerator::getMinElectronEnergy() const
{
  return d_data_container.getMinElectronEnergy();
}

// Set the max electron energy
void AdjointElectronPhotonRelaxationDataGenerator::setMaxElectronEnergy(
                                             const double max_electron_energy )
{
  // Make sure the max electron energy is valid
  testPrecondition( d_data_container.getMinElectronEnergy() <
                    max_electron_energy );

  d_data_container.setMaxElectronEnergy( max_electron_energy );
}

// Return the max electron energy
double AdjointElectronPhotonRelaxationDataGenerator::getMaxElectronEnergy() const
{
  return d_data_container.getMaxElectronEnergy();
}

// Set the default photon grid convergence tolerance
void AdjointElectronPhotonRelaxationDataGenerator::setPhotonGridConvergenceTolerance(
                                                 const double convergence_tol )
{
  // Make sure the convergence tolerance is valid
  TEST_FOR_EXCEPTION( convergence_tol >= 1.0,
                      std::runtime_error,
                      "The grid convergence tolerance must be between 0.0 and "
                      "1.0!" );
  TEST_FOR_EXCEPTION( convergence_tol <= 0.0,
                      std::runtime_error,
                      "The grid convergence tolerance must be between 0.0 and "
                      "1.0!" );

  d_default_photon_grid_generator->setConvergenceTolerance( convergence_tol );
  d_data_container.setAdjointPhotonGridConvergenceTolerance( convergence_tol );
}

// Get the default photon grid convergence tolerance
double AdjointElectronPhotonRelaxationDataGenerator::getPhotonGridConvergenceTolerance() const
{
  return d_default_photon_grid_generator->getConvergenceTolerance();
}

// Set the default photon grid absolute difference tolerance
void AdjointElectronPhotonRelaxationDataGenerator::setPhotonGridAbsoluteDifferenceTolerance(
                                               const double absolute_diff_tol )
{
  // Make sure the absolute difference tolerance is valid
  TEST_FOR_EXCEPTION( absolute_diff_tol >= 1.0,
                      std::runtime_error,
                      "The absolute difference tolerance must be between 0.0 "
                      "and 1.0!" );
  TEST_FOR_EXCEPTION( absolute_diff_tol <= 0.0,
                      std::runtime_error,
                      "The absolute difference tolerance must be between 0.0 "
                      "and 1.0!" );

  d_default_photon_grid_generator->setAbsoluteDifferenceTolerance(absolute_diff_tol);
  d_data_container.setAdjointPhotonGridAbsoluteDifferenceTolerance( absolute_diff_tol );
}

// Get the default photon grid absolute difference tolerance
double AdjointElectronPhotonRelaxationDataGenerator::getPhotonGridAbsoluteDifferenceTolerance() const
{
  return d_default_photon_grid_generator->getAbsoluteDifferenceTolerance();
}

// Set the default photon grid distance tolerance
void AdjointElectronPhotonRelaxationDataGenerator::setPhotonGridDistanceTolerance(
                                                    const double distance_tol )
{
  // Make sure the distance tolerance is valid
  TEST_FOR_EXCEPTION( distance_tol >= 1.0,
                      std::runtime_error,
                      "The distance tolerance must be between 0.0 and 1.0!" );
  TEST_FOR_EXCEPTION( distance_tol <= 0.0,
                      std::runtime_error,
                      "The distance tolerance must be between 0.0 and 1.0!" );

  d_default_photon_grid_generator->setDistanceTolerance( distance_tol );
  d_data_container.setAdjointPhotonGridDistanceTolerance( distance_tol );
}

// Get the default photon grid distance tolerance
double AdjointElectronPhotonRelaxationDataGenerator::getPhotonGridDistanceTolerance() const
{
  return d_default_photon_grid_generator->getDistanceTolerance();
}

// Set the default electron grid convergence tolerance
void AdjointElectronPhotonRelaxationDataGenerator::setElectronGridConvergenceTolerance(
                                                 const double convergence_tol )
{
  // Make sure the convergence tolerance is valid
  TEST_FOR_EXCEPTION( convergence_tol >= 1.0,
                      std::runtime_error,
                      "The grid convergence tolerance must be between 0.0 and "
                      "1.0!" );
  TEST_FOR_EXCEPTION( convergence_tol <= 0.0,
                      std::runtime_error,
                      "The grid convergence tolerance must be between 0.0 and "
                      "1.0!" );

  d_default_electron_grid_generator->setConvergenceTolerance( convergence_tol );
  d_data_container.setAdjointElectronGridConvergenceTolerance( convergence_tol );
}

// Get the default electron grid convergence tolerance
double AdjointElectronPhotonRelaxationDataGenerator::getElectronGridConvergenceTolerance() const
{
  return d_default_electron_grid_generator->getConvergenceTolerance();
}

// Set the default electron grid absolute difference tolerance
void AdjointElectronPhotonRelaxationDataGenerator::setElectronGridAbsoluteDifferenceTolerance(
                                               const double absolute_diff_tol )
{
  // Make sure the absolute difference tolerance is valid
  TEST_FOR_EXCEPTION( absolute_diff_tol >= 1.0,
                      std::runtime_error,
                      "The absolute difference tolerance must be between 0.0 "
                      "and 1.0!" );
  TEST_FOR_EXCEPTION( absolute_diff_tol <= 0.0,
                      std::runtime_error,
                      "The absolute difference tolerance must be between 0.0 "
                      "and 1.0!" );

  d_default_electron_grid_generator->setAbsoluteDifferenceTolerance(absolute_diff_tol);
  d_data_container.setAdjointElectronGridAbsoluteDifferenceTolerance( absolute_diff_tol );
}

// Get the default electron grid absolute difference tolerance
double AdjointElectronPhotonRelaxationDataGenerator::getElectronGridAbsoluteDifferenceTolerance() const
{
  return d_default_electron_grid_generator->getAbsoluteDifferenceTolerance();
}

// Set the default electron grid distance tolerance
void AdjointElectronPhotonRelaxationDataGenerator::setElectronGridDistanceTolerance(
                                                    const double distance_tol )
{
  // Make sure the distance tolerance is valid
  TEST_FOR_EXCEPTION( distance_tol >= 1.0,
                      std::runtime_error,
                      "The distance tolerance must be between 0.0 and 1.0!" );
  TEST_FOR_EXCEPTION( distance_tol <= 0.0,
                      std::runtime_error,
                      "The distance tolerance must be between 0.0 and 1.0!" );

  d_default_electron_grid_generator->setDistanceTolerance( distance_tol );
  d_data_container.setAdjointElectronGridDistanceTolerance( distance_tol );
}

// Get the default electron grid distance tolerance
double AdjointElectronPhotonRelaxationDataGenerator::getElectronGridDistanceTolerance() const
{
  return d_default_electron_grid_generator->getDistanceTolerance();
}

//! Get a default photon grid generator (Lin-Lin grid)
const Utility::GridGenerator<Utility::LinLin>&
AdjointElectronPhotonRelaxationDataGenerator::getDefaultPhotonGridGenerator() const
{
  return *d_default_photon_grid_generator;
}

//! Get a default electron grid generator (Log-Log grid)
const Utility::GridGenerator<Utility::LogLog>&
AdjointElectronPhotonRelaxationDataGenerator::getDefaultElectronGridGenerator() const
{
  return *d_default_electron_grid_generator;
}

// Get the data container
const Data::AdjointElectronPhotonRelaxationDataContainer&
AdjointElectronPhotonRelaxationDataGenerator::getDataContainer() const
{
  return d_data_container;
}

// Get the volatile data container
Data::AdjointElectronPhotonRelaxationVolatileDataContainer&
AdjointElectronPhotonRelaxationDataGenerator::getVolatileDataContainer()
{
  return d_data_container;
}

} // end DataGen

//---------------------------------------------------------------------------//
// end DataGen_AdjointElectronPhotonRelaxationDataGenerator.cpp
//---------------------------------------------------------------------------//
