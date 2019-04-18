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
  : d_data_container( new Data::AdjointElectronPhotonRelaxationVolatileDataContainer ),
    d_default_photon_grid_generator(
           new Utility::GridGenerator<Utility::LinLin>( 1e-3, 1e-13, 1e-13 ) ),
    d_default_electron_grid_generator(
           new Utility::GridGenerator<Utility::LogLog>( 1e-3, 1e-13, 1e-13 ) ),
    d_two_d_interp( MonteCarlo::LOGLOGLOG_INTERPOLATION ),
    d_two_d_grid( MonteCarlo::UNIT_BASE_CORRELATED_GRID ),
    d_elastic_sampling_method( MonteCarlo::TWO_D_UNION ),
    d_forward_electroionization_sampling_mode( MonteCarlo::KNOCK_ON_SAMPLING ),
    d_scatter_above_max( true )
{
  // Make sure the atomic number is valid
  testPrecondition( atomic_number <= 100u );
  // Make sure the photon energy limits are valid
  testPrecondition( min_photon_energy > 0.0 );
  testPrecondition( min_photon_energy < max_photon_energy );
  // Make sure the electron energy limits are valid
  testPrecondition( min_electron_energy > 0.0 );
  testPrecondition( min_electron_energy < max_electron_energy );

  // Set the atomic number and weight
  d_data_container->setAtomicNumber( atomic_number );
  d_data_container->setAtomicWeight( atomic_weight );

  // Set some default photon tolerances and values
  d_data_container->setMinPhotonEnergy( min_photon_energy );
  d_data_container->setMaxPhotonEnergy( max_photon_energy );

  d_data_container->setAdjointPhotonGridConvergenceTolerance( d_default_photon_grid_generator->getConvergenceTolerance() );
  d_data_container->setAdjointPhotonGridAbsoluteDifferenceTolerance( d_default_photon_grid_generator->getAbsoluteDifferenceTolerance() );
  d_data_container->setAdjointPhotonGridDistanceTolerance( d_default_photon_grid_generator->getDistanceTolerance() );
  d_data_container->setAdjointPhotonThresholdEnergyNudgeFactor( 1.0001 );

  d_data_container->setAdjointPairProductionEnergyDistNormConstantEvaluationTolerance( 1e-3 );
  d_data_container->setAdjointPairProductionEnergyDistNormConstantNudgeValue( 1e-6 );
  d_data_container->setAdjointTripletProductionEnergyDistNormConstantEvaluationTolerance( 1e-3 );
  d_data_container->setAdjointTripletProductionEnergyDistNormConstantNudgeValue( 1e-6 );
  d_data_container->setAdjointIncoherentMaxEnergyNudgeValue( 0.2 );
  d_data_container->setAdjointIncoherentEnergyToMaxEnergyNudgeValue( 1e-6 );
  d_data_container->setAdjointIncoherentEvaluationTolerance( 0.001 );
  d_data_container->setAdjointIncoherentGridConvergenceTolerance( 0.001 );
  d_data_container->setAdjointIncoherentGridAbsoluteDifferenceTolerance( 1e-20 );
  d_data_container->setAdjointIncoherentGridDistanceTolerance( 1e-14 );

  // Set some default electron tolerances and values
  d_data_container->setMinElectronEnergy( min_electron_energy );
  d_data_container->setMaxElectronEnergy( max_electron_energy );

  d_data_container->setAdjointElectronGridConvergenceTolerance( d_default_electron_grid_generator->getConvergenceTolerance() );
  d_data_container->setAdjointElectronGridAbsoluteDifferenceTolerance( d_default_electron_grid_generator->getAbsoluteDifferenceTolerance() );
  d_data_container->setAdjointElectronGridDistanceTolerance( d_default_electron_grid_generator->getDistanceTolerance() );

  d_data_container->setElectronTabularEvaluationTolerance( 1e-8 );
  d_data_container->setAdjointBremsstrahlungMinEnergyNudgeValue( 1e-9 );
  d_data_container->setAdjointBremsstrahlungMaxEnergyNudgeValue( 1e-2 );
  d_data_container->setAdjointBremsstrahlungEvaluationTolerance( 1e-6 );
  d_data_container->setAdjointBremsstrahlungGridConvergenceTolerance( 0.001 );
  d_data_container->setAdjointBremsstrahlungAbsoluteDifferenceTolerance( 1e-16 );
  d_data_container->setAdjointBremsstrahlungDistanceTolerance( 1e-8 );
  d_data_container->setAdjointElectroionizationMinEnergyNudgeValue( 1e-9 );
  d_data_container->setAdjointElectroionizationMaxEnergyNudgeValue( 1e-2 );
  d_data_container->setAdjointElectroionizationEvaluationTolerance( 1e-6 );
  d_data_container->setAdjointElectroionizationGridConvergenceTolerance( 0.001 );
  d_data_container->setAdjointElectroionizationAbsoluteDifferenceTolerance( 1e-16 );
  d_data_container->setAdjointElectroionizationDistanceTolerance( 1e-8 );
  d_data_container->setCutoffAngleCosine( 1.0 );
  d_data_container->setNumberOfAdjointMomentPreservingAngles( 0 );
  d_data_container->setElectronTwoDInterpPolicy( Utility::toString( d_two_d_interp ) );
  d_data_container->setElectronTwoDGridPolicy( Utility::toString( d_two_d_grid ) );
  d_data_container->setForwardElectroionizationSamplingMode( Utility::toString( d_forward_electroionization_sampling_mode ) );

  // Have the default grid generators throw exception on dirty convergence
  d_default_photon_grid_generator->throwExceptionOnDirtyConvergence();
  d_default_electron_grid_generator->throwExceptionOnDirtyConvergence();
}

// Constructor (existing data container)
AdjointElectronPhotonRelaxationDataGenerator::AdjointElectronPhotonRelaxationDataGenerator(
                           const boost::filesystem::path& file_name_with_path )
  : d_data_container( new Data::AdjointElectronPhotonRelaxationVolatileDataContainer(file_name_with_path ) ),
    d_default_photon_grid_generator( new Utility::GridGenerator<Utility::LinLin>(
                   d_data_container->getAdjointPhotonGridConvergenceTolerance(),
                   d_data_container->getAdjointPhotonGridAbsoluteDifferenceTolerance(),
                   d_data_container->getAdjointPhotonGridDistanceTolerance() ) ),
    d_default_electron_grid_generator( new Utility::GridGenerator<Utility::LogLog>(
                 d_data_container->getAdjointElectronGridConvergenceTolerance(),
                 d_data_container->getAdjointElectronGridAbsoluteDifferenceTolerance(),
                 d_data_container->getAdjointElectronGridDistanceTolerance() ) ),
    d_two_d_interp( this->convertStringToTwoDInterpType( d_data_container->getElectronTwoDInterpPolicy() ) ),
    d_two_d_grid( this->convertStringToTwoDGridType( d_data_container->getElectronTwoDGridPolicy() ) ),
    d_elastic_sampling_method( this->getAdjointElectronElasticSamplingMethod() ),
    d_forward_electroionization_sampling_mode( this->convertStringToElectroionizationSamplingType( d_data_container->getForwardElectroionizationSamplingMode() ) )
{
  // Have the default grid generators throw exception on dirty convergence
  d_default_photon_grid_generator->throwExceptionOnDirtyConvergence();
  d_default_electron_grid_generator->throwExceptionOnDirtyConvergence();
}

// Set the table notes
void AdjointElectronPhotonRelaxationDataGenerator::setNotes( const std::string& notes )
{
  d_data_container->setNotes( notes );
}

// Return the table notes
const std::string& AdjointElectronPhotonRelaxationDataGenerator::getNotes() const
{
  return d_data_container->getNotes();
}

// Get the atomic number
unsigned AdjointElectronPhotonRelaxationDataGenerator::getAtomicNumber() const
{
  return d_data_container->getAtomicNumber();
}

///////////////////////
// Photon Table Data //
///////////////////////

// Set the min photon energy
void AdjointElectronPhotonRelaxationDataGenerator::setMinPhotonEnergy(
                                               const double min_photon_energy )
{
  // Make sure the min photon energy is valid
  testPrecondition( min_photon_energy > 0.0 );

  d_data_container->setMinPhotonEnergy( min_photon_energy );
}

// Return the min photon energy
double AdjointElectronPhotonRelaxationDataGenerator::getMinPhotonEnergy() const
{
  return d_data_container->getMinPhotonEnergy();
}

// Set the max photon energy
void AdjointElectronPhotonRelaxationDataGenerator::setMaxPhotonEnergy(
                                               const double max_photon_energy )
{
  // Make sure the max photon energy is valid
  testPrecondition( d_data_container->getMinPhotonEnergy() < max_photon_energy );

  d_data_container->setMaxPhotonEnergy( max_photon_energy );
}

// Return the max photon energy
double AdjointElectronPhotonRelaxationDataGenerator::getMaxPhotonEnergy() const
{
  return d_data_container->getMaxPhotonEnergy();
}

// Set the default photon grid convergence tolerance
void AdjointElectronPhotonRelaxationDataGenerator::setDefaultPhotonGridConvergenceTolerance(
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
  d_data_container->setAdjointPhotonGridConvergenceTolerance( convergence_tol );
}

// Get the default photon grid convergence tolerance
double AdjointElectronPhotonRelaxationDataGenerator::getDefaultPhotonGridConvergenceTolerance() const
{
  return d_default_photon_grid_generator->getConvergenceTolerance();
}

// Set the default photon grid absolute difference tolerance
void AdjointElectronPhotonRelaxationDataGenerator::setDefaultPhotonGridAbsoluteDifferenceTolerance(
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
  d_data_container->setAdjointPhotonGridAbsoluteDifferenceTolerance( absolute_diff_tol );
}

// Get the default photon grid absolute difference tolerance
double AdjointElectronPhotonRelaxationDataGenerator::getDefaultPhotonGridAbsoluteDifferenceTolerance() const
{
  return d_default_photon_grid_generator->getAbsoluteDifferenceTolerance();
}

// Set the default photon grid distance tolerance
void AdjointElectronPhotonRelaxationDataGenerator::setDefaultPhotonGridDistanceTolerance(
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
  d_data_container->setAdjointPhotonGridDistanceTolerance( distance_tol );
}

// Get the default photon grid distance tolerance
double AdjointElectronPhotonRelaxationDataGenerator::getDefaultPhotonGridDistanceTolerance() const
{
  return d_default_photon_grid_generator->getDistanceTolerance();
}

// Set the photon threshold energy nudge factor
void AdjointElectronPhotonRelaxationDataGenerator::setPhotonThresholdEnergyNudgeFactor( const double nudge_factor )
{
  // Make sure that the nudge factor is valid
  testPrecondition( nudge_factor > 1.0 );
  
  d_data_container->setAdjointPhotonThresholdEnergyNudgeFactor( nudge_factor );
}

// Get the photon threshold energy nudge factor
double AdjointElectronPhotonRelaxationDataGenerator::getPhotonThresholdEnergyNudgeFactor() const
{
  return d_data_container->getAdjointPhotonThresholdEnergyNudgeFactor();
}

// Set the adjoint pair production energy dist. norm const. evaluation tol.
void AdjointElectronPhotonRelaxationDataGenerator::setAdjointPairProductionEnergyDistNormConstantEvaluationTolerance(
                                                  const double evaluation_tol )
{
  // Make sure the evaluation tolerance is valid
  testPrecondition( evaluation_tol > 0.0 );
  testPrecondition( evaluation_tol < 1.0 );

  d_data_container->setAdjointPairProductionEnergyDistNormConstantEvaluationTolerance( evaluation_tol );
}

// Get the adjoint pair production energy dist. norm const. evaluation tol
double AdjointElectronPhotonRelaxationDataGenerator::getAdjointPairProductionEnergyDistNormConstantEvaluationTolerance() const
{
  return d_data_container->getAdjointPairProductionEnergyDistNormConstantEvaluationTolerance();
}

// Set the adjoint pair production energy dist. norm const. nudge value
void AdjointElectronPhotonRelaxationDataGenerator::setAdjointPairProductionEnergyDistNormConstantNudgeValue(
                                                     const double nudge_value )
{
  // Make sure the nudge value is valid
  testPrecondition( nudge_value >= 0.0 );

  d_data_container->setAdjointPairProductionEnergyDistNormConstantNudgeValue( nudge_value );
}

// Get the adjoint pair production energy dist. norm const. nudge value
double AdjointElectronPhotonRelaxationDataGenerator::getAdjointPairProductionEnergyDistNormConstantNudgeValue() const
{
  return d_data_container->getAdjointPairProductionEnergyDistNormConstantNudgeValue();
}

// Set the adjoint triplet production energy dist. norm const. evaluation tol.
void AdjointElectronPhotonRelaxationDataGenerator::setAdjointTripletProductionEnergyDistNormConstantEvaluationTolerance(
                                                  const double evaluation_tol )
{
  // Make sure the evaluation tolerance is valid
  testPrecondition( evaluation_tol > 0.0 );
  testPrecondition( evaluation_tol < 1.0 );

  d_data_container->setAdjointTripletProductionEnergyDistNormConstantEvaluationTolerance( evaluation_tol );
}

// Get the adjoint triplet production energy dist. norm const. evaluation tol
double AdjointElectronPhotonRelaxationDataGenerator::getAdjointTripletProductionEnergyDistNormConstantEvaluationTolerance() const
{
  return d_data_container->getAdjointTripletProductionEnergyDistNormConstantEvaluationTolerance( );
}

// Set the adjoint triplet production energy dist. norm const. nudge value
void AdjointElectronPhotonRelaxationDataGenerator::setAdjointTripletProductionEnergyDistNormConstantNudgeValue(
                                                     const double nudge_value )
{
  // Make sure the nudge value is valid
  testPrecondition( nudge_value >= 0.0 );

  d_data_container->setAdjointTripletProductionEnergyDistNormConstantNudgeValue( nudge_value );
}

// Get the adjoint triplet production energy dist. norm const. nudge value
double AdjointElectronPhotonRelaxationDataGenerator::getAdjointTripletProductionEnergyDistNormConstantNudgeValue() const
{
  return d_data_container->getAdjointTripletProductionEnergyDistNormConstantNudgeValue();
}

// Set the adjoint incoherent max energy nudge value
void AdjointElectronPhotonRelaxationDataGenerator::setAdjointIncoherentMaxEnergyNudgeValue(
                                          const double max_energy_nudge_value )
{
  // Make sure the nudge value is valid
  testPrecondition( max_energy_nudge_value > 0.0 );

  d_data_container->setAdjointIncoherentMaxEnergyNudgeValue( max_energy_nudge_value );
}

// Return the adjoint incoherent max energy nudge value
double AdjointElectronPhotonRelaxationDataGenerator::getAdjointIncoherentMaxEnergyNudgeValue() const
{
  return d_data_container->getAdjointIncoherentMaxEnergyNudgeValue();
}

// Set the adjoint incoherent energy to max energy nudge value
void AdjointElectronPhotonRelaxationDataGenerator::setAdjointIncoherentEnergyToMaxEnergyNudgeValue(
                                const double energy_to_max_energy_nudge_value )
{
  // Make sure the nudge value is valid
  testPrecondition( energy_to_max_energy_nudge_value >= 0.0 );

  d_data_container->setAdjointIncoherentEnergyToMaxEnergyNudgeValue( energy_to_max_energy_nudge_value );
}

// Return the adjoint incoherent energy to max energy nudge value
double AdjointElectronPhotonRelaxationDataGenerator::getAdjointIncoherentEnergyToMaxEnergyNudgeValue() const
{
  return d_data_container->getAdjointIncoherentEnergyToMaxEnergyNudgeValue();
}

// Set the adjoint incoherent cross section evaluation tolerance
void AdjointElectronPhotonRelaxationDataGenerator::setAdjointIncoherentEvaluationTolerance(
                                                  const double evaluation_tol )
{
  // Make sure the evaluation tolerance is valid
  testPrecondition( evaluation_tol > 0.0 );
  testPrecondition( evaluation_tol < 1.0 );

  d_data_container->setAdjointIncoherentEvaluationTolerance( evaluation_tol );
}

// Return the adjoint incoherent cross section evaluation tolerance
double AdjointElectronPhotonRelaxationDataGenerator::getAdjointIncoherentEvaluationTolerance() const
{
  return d_data_container->getAdjointIncoherentEvaluationTolerance();
}

// Set the adjoint incoherent grid convergence tolerance
void AdjointElectronPhotonRelaxationDataGenerator::setAdjointIncoherentGridConvergenceTolerance(
                                                 const double convergence_tol )
{
  // Make sure the convergence tolerance is valid
  testPrecondition( convergence_tol <= 1.0 );
  testPrecondition( convergence_tol > 0.0 );

  d_data_container->setAdjointIncoherentGridConvergenceTolerance( convergence_tol );
}

// Return the adjoint incoherent grid convergence tolerance
double AdjointElectronPhotonRelaxationDataGenerator::getAdjointIncoherentGridConvergenceTolerance() const
{
  return d_data_container->getAdjointIncoherentGridConvergenceTolerance();
}

// Set the adjoint incoherent grid absolute difference tolerance
void AdjointElectronPhotonRelaxationDataGenerator::setAdjointIncoherentGridAbsoluteDifferenceTolerance(
                                               const double absolute_diff_tol )
{
  // Make sure the absolute difference tolerance is valid
  testPrecondition( absolute_diff_tol <= 1.0 );
  testPrecondition( absolute_diff_tol >= 0.0 );

  d_data_container->setAdjointIncoherentGridAbsoluteDifferenceTolerance( absolute_diff_tol );
}

// Get the adjoint incoherent grid absolute difference tolerance
double AdjointElectronPhotonRelaxationDataGenerator::getAdjointIncoherentGridAbsoluteDifferenceTolerance() const
{
  return d_data_container->getAdjointIncoherentGridAbsoluteDifferenceTolerance();
}

// Set the adjoint incoherent grid distance tolerance
void AdjointElectronPhotonRelaxationDataGenerator::setAdjointIncoherentGridDistanceTolerance(
                                                    const double distance_tol )
{
  // Make sure the distance tolerance is valid
  testPrecondition( distance_tol <= 1.0 );
  testPrecondition( distance_tol >= 0.0 );

  d_data_container->setAdjointIncoherentGridDistanceTolerance( distance_tol );
}

// Get the adjoint incoherent grid distance tolerance
double AdjointElectronPhotonRelaxationDataGenerator::getAdjointIncoherentGridDistanceTolerance() const
{
  return d_data_container->getAdjointIncoherentGridDistanceTolerance();
}

/////////////////////////
// Electron Table Data //
/////////////////////////

//! Set the min electron energy
void AdjointElectronPhotonRelaxationDataGenerator::setMinElectronEnergy(
                                             const double min_electron_energy )
{
  // Make sure the min electron energy is valid
  testPrecondition( min_electron_energy > 0.0 );

  d_data_container->setMinElectronEnergy( min_electron_energy );
}

// Return the min electron energy
double AdjointElectronPhotonRelaxationDataGenerator::getMinElectronEnergy() const
{
  return d_data_container->getMinElectronEnergy();
}

// Set the max electron energy
void AdjointElectronPhotonRelaxationDataGenerator::setMaxElectronEnergy(
                                             const double max_electron_energy )
{
  // Make sure the max electron energy is valid
  testPrecondition( d_data_container->getMinElectronEnergy() <
                    max_electron_energy );

  d_data_container->setMaxElectronEnergy( max_electron_energy );
}

// Return the max electron energy
double AdjointElectronPhotonRelaxationDataGenerator::getMaxElectronEnergy() const
{
  return d_data_container->getMaxElectronEnergy();
}

// Set the electron scatter above max energy mode is on (on by default)
void AdjointElectronPhotonRelaxationDataGenerator::setElectronScatterAboveMaxModeOn()
{
  d_scatter_above_max = true;
}

// Set the electron scatter above max energy mode is off (on by default)
void AdjointElectronPhotonRelaxationDataGenerator::setElectronScatterAboveMaxModeOff()
{
  d_scatter_above_max = false;
}

// Return if the electron scatter above max energy mode is on
bool AdjointElectronPhotonRelaxationDataGenerator::isElectronScatterAboveMaxModeOn() const
{
  return d_scatter_above_max;
}

// Set the default electron grid convergence tolerance
void AdjointElectronPhotonRelaxationDataGenerator::setDefaultElectronGridConvergenceTolerance(
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
  d_data_container->setAdjointElectronGridConvergenceTolerance( convergence_tol );
}

// Get the default electron grid convergence tolerance
double AdjointElectronPhotonRelaxationDataGenerator::getDefaultElectronGridConvergenceTolerance() const
{
  return d_default_electron_grid_generator->getConvergenceTolerance();
}

// Set the default electron grid absolute difference tolerance
void AdjointElectronPhotonRelaxationDataGenerator::setDefaultElectronGridAbsoluteDifferenceTolerance(
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
  d_data_container->setAdjointElectronGridAbsoluteDifferenceTolerance( absolute_diff_tol );
}

// Get the default electron grid absolute difference tolerance
double AdjointElectronPhotonRelaxationDataGenerator::getDefaultElectronGridAbsoluteDifferenceTolerance() const
{
  return d_default_electron_grid_generator->getAbsoluteDifferenceTolerance();
}

// Set the default electron grid distance tolerance
void AdjointElectronPhotonRelaxationDataGenerator::setDefaultElectronGridDistanceTolerance(
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
  d_data_container->setAdjointElectronGridDistanceTolerance( distance_tol );
}

// Get the default electron grid distance tolerance
double AdjointElectronPhotonRelaxationDataGenerator::getDefaultElectronGridDistanceTolerance() const
{
  return d_default_electron_grid_generator->getDistanceTolerance();
}

// Set the electron FullyTabularTwoDDistribution evaluation tolerance
void AdjointElectronPhotonRelaxationDataGenerator::setElectronTabularEvaluationTolerance(
                        const double tabular_evaluation_tol )
{
  // Make sure the tolerance is valid
  testPrecondition( tabular_evaluation_tol < 1.0 );
  testPrecondition( tabular_evaluation_tol > 0.0 );

  d_data_container->setElectronTabularEvaluationTolerance( tabular_evaluation_tol );
}

// Get the electron FullyTabularTwoDDistribution evaluation tolerance
double AdjointElectronPhotonRelaxationDataGenerator::getElectronTabularEvaluationTolerance() const
{
  return d_data_container->getElectronTabularEvaluationTolerance();
}

// Set the electron TwoDInterpPolicy (LogLogLog by default)
void AdjointElectronPhotonRelaxationDataGenerator::setElectronTwoDInterpPolicy(
                    const MonteCarlo::TwoDInterpolationType two_d_interp )
{
  d_two_d_interp = two_d_interp;
  d_data_container->setElectronTwoDInterpPolicy( Utility::toString( two_d_interp ) );
}

// Return the electron TwoDInterpPolicy (LogLogLog by default)
MonteCarlo::TwoDInterpolationType AdjointElectronPhotonRelaxationDataGenerator::getElectronTwoDInterpPolicy() const
{
  return d_two_d_interp;
}

// Set the electron TwoDGridPolicy (Unit-base Correlated by default)
void AdjointElectronPhotonRelaxationDataGenerator::setElectronTwoDGridPolicy(
                    const MonteCarlo::TwoDGridType two_d_grid )
{
  d_two_d_grid = two_d_grid;
  d_data_container->setElectronTwoDGridPolicy( Utility::toString( two_d_grid ) );
}

// Return the electron TwoDGridPolicy (Unit-base Correlated by default)
MonteCarlo::TwoDGridType AdjointElectronPhotonRelaxationDataGenerator::getElectronTwoDGridPolicy() const
{
  return d_two_d_grid;
}

// Set the electron elastic sampling method (TWO_D_UNION by default)
void AdjointElectronPhotonRelaxationDataGenerator::setAdjointElectronElasticSamplingMethod(
    MonteCarlo::CoupledElasticSamplingMethod sampling )
{
  d_elastic_sampling_method = sampling;
}

// Return the electron elastic sampling method
MonteCarlo::CoupledElasticSamplingMethod
AdjointElectronPhotonRelaxationDataGenerator::getAdjointElectronElasticSamplingMethod() const
{
  return d_elastic_sampling_method;
}

// Set the cutoff angle cosine above which screened rutherford is used
void AdjointElectronPhotonRelaxationDataGenerator::setCutoffAngleCosine( const double angle_cutoff )
{
  d_data_container->setCutoffAngleCosine( angle_cutoff );
}

// Get the cutoff angle cosine above which screened rutherford is used
double AdjointElectronPhotonRelaxationDataGenerator::getCutoffAngleCosine() const
{
  return d_data_container->getCutoffAngleCosine();
}

// Set the number of moment preserving angles
void AdjointElectronPhotonRelaxationDataGenerator::setNumberOfMomentPreservingAngles( const unsigned number_of_angles )
{
  d_data_container->setNumberOfAdjointMomentPreservingAngles( number_of_angles );
}

// Get the number of moment preserving angles
unsigned AdjointElectronPhotonRelaxationDataGenerator::getNumberOfMomentPreservingAngles() const
{
  return d_data_container->getNumberOfAdjointMomentPreservingAngles();
}

// Set the adjoint bremsstrahlung min energy nudge value
void AdjointElectronPhotonRelaxationDataGenerator::setAdjointBremsstrahlungMinEnergyNudgeValue(
                                          const double min_energy_nudge_value )
{
  // Make sure the nudge value is valid
  testPrecondition( min_energy_nudge_value > 0.0 );

  d_data_container->setAdjointBremsstrahlungMinEnergyNudgeValue( min_energy_nudge_value );
}

// Return the adjoint bremsstrahlung min energy nudge value
double AdjointElectronPhotonRelaxationDataGenerator::getAdjointBremsstrahlungMinEnergyNudgeValue() const
{
  return d_data_container->getAdjointBremsstrahlungMinEnergyNudgeValue();
}

// Set the adjoint bremsstrahlung max energy nudge value
void AdjointElectronPhotonRelaxationDataGenerator::setAdjointBremsstrahlungMaxEnergyNudgeValue(
                                          const double max_energy_nudge_value )
{
  // Make sure the nudge value is valid
  testPrecondition( max_energy_nudge_value > 0.0 );

  d_data_container->setAdjointBremsstrahlungMaxEnergyNudgeValue( max_energy_nudge_value );
}

// Return the adjoint bremsstrahlung max energy nudge value
double AdjointElectronPhotonRelaxationDataGenerator::getAdjointBremsstrahlungMaxEnergyNudgeValue() const
{
  return d_data_container->getAdjointBremsstrahlungMaxEnergyNudgeValue();
}

// Set the evaluation tolerance for the adjoint bremsstrahlung cross section
void AdjointElectronPhotonRelaxationDataGenerator::setAdjointBremsstrahlungEvaluationTolerance(
                                            const double evaluation_tolerance )
{
  // Make sure the evaluation tolerance is valid
  testPrecondition( evaluation_tolerance > 0.0 );
  testPrecondition( evaluation_tolerance < 1.0 );

  d_data_container->setAdjointBremsstrahlungEvaluationTolerance( evaluation_tolerance );
}

// Get the evaluation tolerance for the adjoint bremsstrahlung cross section
double AdjointElectronPhotonRelaxationDataGenerator::getAdjointBremsstrahlungEvaluationTolerance() const
{
  return d_data_container->getAdjointBremsstrahlungEvaluationTolerance();
}

// Set the adjoint bremsstrahlung grid convergence tolerance
void AdjointElectronPhotonRelaxationDataGenerator::setAdjointBremsstrahlungGridConvergenceTolerance(
                                                 const double convergence_tol )
{
  // Make sure the convergence tolerance is valid
  testPrecondition( convergence_tol <= 1.0 );
  testPrecondition( convergence_tol > 0.0 );

  d_data_container->setAdjointBremsstrahlungGridConvergenceTolerance( convergence_tol );
}

// Return the adjoint bremsstrahlung grid convergence tolerance
double AdjointElectronPhotonRelaxationDataGenerator::getAdjointBremsstrahlungGridConvergenceTolerance() const
{
  return d_data_container->getAdjointBremsstrahlungGridConvergenceTolerance();
}

// Set the adjoint bremsstrahlung absolute difference tolerance
void AdjointElectronPhotonRelaxationDataGenerator::setAdjointBremsstrahlungAbsoluteDifferenceTolerance(
                                               const double absolute_diff_tol )
{
  // Make sure the absolute difference tolerance is valid
  testPrecondition( absolute_diff_tol <= 1.0 );
  testPrecondition( absolute_diff_tol >= 0.0 );

  d_data_container->setAdjointBremsstrahlungAbsoluteDifferenceTolerance( absolute_diff_tol );
}

// Get the adjoint bremsstrahlung absolute difference tolerance
double AdjointElectronPhotonRelaxationDataGenerator::getAdjointBremsstrahlungAbsoluteDifferenceTolerance() const
{
  return d_data_container->getAdjointBremsstrahlungAbsoluteDifferenceTolerance();
}

// Set the adjoint bremsstrahlung distance tolerance
void AdjointElectronPhotonRelaxationDataGenerator::setAdjointBremsstrahlungDistanceTolerance(
                                                    const double distance_tol )
{
  // Make sure the distance tolerance is valid
  testPrecondition( distance_tol <= 1.0 );
  testPrecondition( distance_tol >= 0.0 );

  d_data_container->setAdjointBremsstrahlungDistanceTolerance( distance_tol );
}

// Get the adjoint bremsstrahlung distance tolerance
double AdjointElectronPhotonRelaxationDataGenerator::getAdjointBremsstrahlungDistanceTolerance() const
{
  return d_data_container->getAdjointBremsstrahlungDistanceTolerance();
}

// Set the forward electroionization sampling mode
void AdjointElectronPhotonRelaxationDataGenerator::setForwardElectroionizationSamplingMode( const MonteCarlo::ElectroionizationSamplingType sampling_mode )
{
  d_forward_electroionization_sampling_mode = sampling_mode;
  d_data_container->setForwardElectroionizationSamplingMode( Utility::toString( sampling_mode ) );
}

// Return the forward electroionization sampling mode
MonteCarlo::ElectroionizationSamplingType
AdjointElectronPhotonRelaxationDataGenerator::getForwardElectroionizationSamplingMode() const
{
  return d_forward_electroionization_sampling_mode;
}

// Set the adjoint electroionization min energy nudge value
void AdjointElectronPhotonRelaxationDataGenerator::setAdjointElectroionizationMinEnergyNudgeValue(
                                          const double min_energy_nudge_value )
{
  // Make sure the nudge value is valid
  testPrecondition( min_energy_nudge_value > 0.0 );

  d_data_container->setAdjointElectroionizationMinEnergyNudgeValue( min_energy_nudge_value );
}

// Return the adjoint electroionization min energy nudge value
double AdjointElectronPhotonRelaxationDataGenerator::getAdjointElectroionizationMinEnergyNudgeValue() const
{
  return d_data_container->getAdjointElectroionizationMinEnergyNudgeValue();
}

// Set the adjoint electroionization max energy nudge value
void AdjointElectronPhotonRelaxationDataGenerator::setAdjointElectroionizationMaxEnergyNudgeValue(
                                          const double max_energy_nudge_value )
{
  // Make sure the nudge value is valid
  testPrecondition( max_energy_nudge_value > 0.0 );

  d_data_container->setAdjointElectroionizationMaxEnergyNudgeValue( max_energy_nudge_value );
}

// Return the adjoint electroionization max energy nudge value
double AdjointElectronPhotonRelaxationDataGenerator::getAdjointElectroionizationMaxEnergyNudgeValue() const
{
  return d_data_container->getAdjointElectroionizationMaxEnergyNudgeValue();
}

// Set the evaluation tolerance for the adjoint electroionization cross section
void AdjointElectronPhotonRelaxationDataGenerator::setAdjointElectroionizationEvaluationTolerance(
                                            const double evaluation_tolerance )
{
  // Make sure the evaluation tolerance is valid
  testPrecondition( evaluation_tolerance > 0.0 );
  testPrecondition( evaluation_tolerance < 1.0 );

  d_data_container->setAdjointElectroionizationEvaluationTolerance( evaluation_tolerance );
}

// Get the evaluation tolerance for the adjoint electroionization cross section
double AdjointElectronPhotonRelaxationDataGenerator::getAdjointElectroionizationEvaluationTolerance() const
{
  return d_data_container->getAdjointElectroionizationEvaluationTolerance();
}

// Set the adjoint electroionization grid convergence tolerance
void AdjointElectronPhotonRelaxationDataGenerator::setAdjointElectroionizationGridConvergenceTolerance(
                                                 const double convergence_tol )
{
  // Make sure the convergence tolerance is valid
  testPrecondition( convergence_tol <= 1.0 );
  testPrecondition( convergence_tol > 0.0 );

  d_data_container->setAdjointElectroionizationGridConvergenceTolerance( convergence_tol );
}

// Return the adjoint electroionization grid convergence tolerance
double AdjointElectronPhotonRelaxationDataGenerator::getAdjointElectroionizationGridConvergenceTolerance() const
{
  return d_data_container->getAdjointElectroionizationGridConvergenceTolerance();
}

// Set the adjoint electroionization absolute difference tolerance
void AdjointElectronPhotonRelaxationDataGenerator::setAdjointElectroionizationAbsoluteDifferenceTolerance(
                                               const double absolute_diff_tol )
{
  // Make sure the absolute difference tolerance is valid
  testPrecondition( absolute_diff_tol <= 1.0 );
  testPrecondition( absolute_diff_tol >= 0.0 );

  d_data_container->setAdjointElectroionizationAbsoluteDifferenceTolerance( absolute_diff_tol );
}

// Get the adjoint electroionization absolute difference tolerance
double AdjointElectronPhotonRelaxationDataGenerator::getAdjointElectroionizationAbsoluteDifferenceTolerance() const
{
  return d_data_container->getAdjointElectroionizationAbsoluteDifferenceTolerance();
}

// Set the adjoint electroionization distance tolerance
void AdjointElectronPhotonRelaxationDataGenerator::setAdjointElectroionizationDistanceTolerance(
                                                    const double distance_tol )
{
  // Make sure the distance tolerance is valid
  testPrecondition( distance_tol <= 1.0 );
  testPrecondition( distance_tol >= 0.0 );

  d_data_container->setAdjointElectroionizationDistanceTolerance( distance_tol );
}

// Get the adjoint electroionization distance tolerance
double AdjointElectronPhotonRelaxationDataGenerator::getAdjointElectroionizationDistanceTolerance() const
{
  return d_data_container->getAdjointElectroionizationDistanceTolerance();
}

// Convert string to TwoDInterpolationType
const MonteCarlo::TwoDInterpolationType
AdjointElectronPhotonRelaxationDataGenerator::convertStringToTwoDInterpType( const std::string& raw_policy ) const
{
  if( raw_policy == "Lin-Lin-Lin" )
    return MonteCarlo::LINLINLIN_INTERPOLATION;
  else if( raw_policy == "Lin-Lin-Log" )
    return MonteCarlo::LINLINLOG_INTERPOLATION;
  else if( raw_policy == "Lin-Log-Lin" )
    return MonteCarlo::LINLOGLIN_INTERPOLATION;
  else if( raw_policy == "Log-Lin-Lin" )
    return MonteCarlo::LOGLINLIN_INTERPOLATION;
  else if( raw_policy == "Lin-Log-Log" )
    return MonteCarlo::LINLOGLOG_INTERPOLATION;
  else if( raw_policy == "Log-Lin-Log" )
    return MonteCarlo::LOGLINLOG_INTERPOLATION;
  else if( raw_policy == "Log-Log-Lin" )
    return MonteCarlo::LOGLOGLIN_INTERPOLATION;
  else if( raw_policy == "Log-Log-Log" )
    return MonteCarlo::LOGLOGLOG_INTERPOLATION;
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "Error: the 2D interpolation type "
                     << raw_policy <<
                     " is not currently supported!" );
  }
}

// Convert string to TwoDGridType
const MonteCarlo::TwoDGridType AdjointElectronPhotonRelaxationDataGenerator::convertStringToTwoDGridType(
    const std::string& raw_policy ) const
{
  if( raw_policy == "Correlated" )
    return MonteCarlo::CORRELATED_GRID;
  else if( raw_policy == "Unit-base Correlated" )
    return MonteCarlo::UNIT_BASE_CORRELATED_GRID;
  else if( raw_policy == "Direct" )
    return MonteCarlo::DIRECT_GRID;
  else if( raw_policy == "Unit-base" )
    return MonteCarlo::UNIT_BASE_GRID;
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "Error: 2D grid type "
                     << raw_policy <<
                     " is not currently supported!" );
  }
}

// Convert string to ElectroionizationSamplingType
const MonteCarlo::ElectroionizationSamplingType AdjointElectronPhotonRelaxationDataGenerator::convertStringToElectroionizationSamplingType(
    const std::string& raw_policy ) const
{
  if( raw_policy == "Knock-on Electroionization Sampling" )
    return MonteCarlo::KNOCK_ON_SAMPLING;
  else if( raw_policy == "Outgoing Energy Electroionization Sampling" )
    return MonteCarlo::OUTGOING_ENERGY_SAMPLING;
  else if( raw_policy == "Outgoing Energy Ratio Electroionization Sampling" )
    return MonteCarlo::OUTGOING_ENERGY_RATIO_SAMPLING;
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "the electro-ionization sampling mode "
                     << raw_policy <<
                     " is not currently supported!" );
  }
}

// Get a default photon grid generator (Lin-Lin grid)
const Utility::GridGenerator<Utility::LinLin>&
AdjointElectronPhotonRelaxationDataGenerator::getDefaultPhotonGridGenerator() const
{
  return *d_default_photon_grid_generator;
}

// Get a default electron grid generator (Log-Log grid)
const Utility::GridGenerator<Utility::LogLog>&
AdjointElectronPhotonRelaxationDataGenerator::getDefaultElectronGridGenerator() const
{
  return *d_default_electron_grid_generator;
}

// Get the data container
const Data::AdjointElectronPhotonRelaxationDataContainer&
AdjointElectronPhotonRelaxationDataGenerator::getDataContainer() const
{
  return *d_data_container;
}

// Get the shared data container
std::shared_ptr<const Data::AdjointElectronPhotonRelaxationDataContainer>
AdjointElectronPhotonRelaxationDataGenerator::getSharedDataContainer() const
{
  return d_data_container;
}

// Get the volatile data container
Data::AdjointElectronPhotonRelaxationVolatileDataContainer&
AdjointElectronPhotonRelaxationDataGenerator::getVolatileDataContainer()
{
  return *d_data_container;
}

} // end DataGen

//---------------------------------------------------------------------------//
// end DataGen_AdjointElectronPhotonRelaxationDataGenerator.cpp
//---------------------------------------------------------------------------//
