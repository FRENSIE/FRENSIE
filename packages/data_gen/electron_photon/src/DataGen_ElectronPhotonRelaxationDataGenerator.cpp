//---------------------------------------------------------------------------//
//!
//! \file   DataGen_ElectronPhotonRelaxationDataGenerator.cpp
//! \author Alex Robinson
//! \brief  The electron-photon-relaxation data generator base class decl.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "DataGen_ElectronPhotonRelaxationDataGenerator.hpp"
#include "Utility_DesignByContract.hpp"

namespace DataGen{

// Constructor
ElectronPhotonRelaxationDataGenerator::ElectronPhotonRelaxationDataGenerator(
                                         const unsigned atomic_number,
                                         const double atomic_weight,
                                         const double min_photon_energy,
                                         const double max_photon_energy,
                                         const double min_electron_energy,
                                         const double max_electron_energy )
  : d_data_container( new Data::ElectronPhotonRelaxationVolatileDataContainer ),
    d_default_photon_grid_generator(
           new Utility::GridGenerator<Utility::LinLin>( 1e-3, 1e-13, 1e-13 ) ),
    d_default_electron_grid_generator(
           new Utility::GridGenerator<Utility::LogLog>( 1e-3, 1e-13, 1e-13 ) ),
    d_refine_secondary_electron_grid_mode( false ),
    d_elastic_sampling_method( MonteCarlo::TWO_D_UNION ),
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
  d_data_container->setAtomicNumber( atomic_number );
  d_data_container->setAtomicWeight( atomic_weight );
  d_data_container->setMinPhotonEnergy( min_photon_energy );
  d_data_container->setMaxPhotonEnergy( max_photon_energy );
  d_data_container->setMinElectronEnergy( min_electron_energy );
  d_data_container->setMaxElectronEnergy( max_electron_energy );

  // Set some default tolerances and values
  d_data_container->setPhotonGridConvergenceTolerance( d_default_photon_grid_generator->getConvergenceTolerance() );
  d_data_container->setPhotonGridAbsoluteDifferenceTolerance( d_default_photon_grid_generator->getAbsoluteDifferenceTolerance() );
  d_data_container->setPhotonGridDistanceTolerance( d_default_photon_grid_generator->getDistanceTolerance() );

  d_data_container->setElectronGridConvergenceTolerance( d_default_electron_grid_generator->getConvergenceTolerance() );
  d_data_container->setElectronGridAbsoluteDifferenceTolerance( d_default_electron_grid_generator->getAbsoluteDifferenceTolerance() );
  d_data_container->setElectronGridDistanceTolerance( d_default_electron_grid_generator->getDistanceTolerance() );

  d_data_container->setOccupationNumberEvaluationTolerance( 1e-3 );
  d_data_container->setSubshellIncoherentEvaluationTolerance( 1e-3 );
  d_data_container->setPhotonThresholdEnergyNudgeFactor( 1.0001 );

  d_data_container->setCutoffAngleCosine( 1.0 );
  d_data_container->setNumberOfMomentPreservingAngles( 0 );
  d_data_container->setElectronTabularEvaluationTolerance( 1e-7 );
  d_data_container->setElectronTwoDInterpPolicy( Utility::toString( d_two_d_interp ) );
  d_data_container->setElectronTwoDGridPolicy( Utility::toString( d_two_d_grid ) );

  d_data_container->setBremsstrahlungEvaluationTolerance( 1e-7 );
  d_data_container->setBremsstrahlungGridConvergenceTolerance( d_default_electron_grid_generator->getConvergenceTolerance() );
  d_data_container->setBremsstrahlungAbsoluteDifferenceTolerance( 1e-20 );
  d_data_container->setBremsstrahlungDistanceTolerance( d_default_electron_grid_generator->getDistanceTolerance() );

  d_data_container->setElectroionizationEvaluationTolerance( 1e-7 );
  d_data_container->setElectroionizationGridConvergenceTolerance( d_default_electron_grid_generator->getConvergenceTolerance() );
  d_data_container->setElectroionizationAbsoluteDifferenceTolerance( 1e-20 );
  d_data_container->setElectroionizationDistanceTolerance( d_default_electron_grid_generator->getDistanceTolerance() );

  // Have the default grid generators throw exception on dirty convergence
  d_default_photon_grid_generator->throwExceptionOnDirtyConvergence();
  d_default_electron_grid_generator->throwExceptionOnDirtyConvergence();
}

// Constructor (existing data container)
ElectronPhotonRelaxationDataGenerator::ElectronPhotonRelaxationDataGenerator(
                           const boost::filesystem::path& file_name_with_path )
  : d_data_container( new Data::ElectronPhotonRelaxationVolatileDataContainer( file_name_with_path ) ),
    d_refine_secondary_electron_grid_mode( false ),
    d_elastic_sampling_method( MonteCarlo::TWO_D_UNION ),
    d_default_photon_grid_generator( new Utility::GridGenerator<Utility::LinLin>(
                   d_data_container->getPhotonGridConvergenceTolerance(),
                   d_data_container->getPhotonGridAbsoluteDifferenceTolerance(),
                   d_data_container->getPhotonGridDistanceTolerance() ) ),
    d_default_electron_grid_generator( new Utility::GridGenerator<Utility::LogLog>(
                 d_data_container->getElectronGridConvergenceTolerance(),
                 d_data_container->getElectronGridAbsoluteDifferenceTolerance(),
                 d_data_container->getElectronGridDistanceTolerance() ) )
{
  // Have the default grid generators throw exception on dirty convergence
  d_default_photon_grid_generator->throwExceptionOnDirtyConvergence();
  d_default_electron_grid_generator->throwExceptionOnDirtyConvergence();
}

// Get the atomic number
unsigned ElectronPhotonRelaxationDataGenerator::getAtomicNumber() const
{
  return d_data_container->getAtomicNumber();
}

// Set the min photon energy
void ElectronPhotonRelaxationDataGenerator::setMinPhotonEnergy(
                                               const double min_photon_energy )
{
  // Make sure the min photon energy is valid
  testPrecondition( min_photon_energy > 0.0 );

  d_data_container->setMinPhotonEnergy( min_photon_energy );
}

// Return the min photon energy
double ElectronPhotonRelaxationDataGenerator::getMinPhotonEnergy() const
{
  return d_data_container->getMinPhotonEnergy();
}

// Set the max photon energy
void ElectronPhotonRelaxationDataGenerator::setMaxPhotonEnergy(
                                               const double max_photon_energy )
{
  // Make sure the max photon energy is valid
  testPrecondition( d_data_container->getMinPhotonEnergy() < max_photon_energy );

  d_data_container->setMaxPhotonEnergy( max_photon_energy );
}

// Return the max photon energy
double ElectronPhotonRelaxationDataGenerator::getMaxPhotonEnergy() const
{
  return d_data_container->getMaxPhotonEnergy();
}

// Set the min electron energy
void ElectronPhotonRelaxationDataGenerator::setMinElectronEnergy(
                                             const double min_electron_energy )
{
  // Make sure the min electron energy is valid
  testPrecondition( min_electron_energy > 0.0 );

  d_data_container->setMinElectronEnergy( min_electron_energy );
}

// Return the min electron energy
double ElectronPhotonRelaxationDataGenerator::getMinElectronEnergy() const
{
  return d_data_container->getMinElectronEnergy();
}

// Set the max electron energy
void ElectronPhotonRelaxationDataGenerator::setMaxElectronEnergy(
                                             const double max_electron_energy )
{
  // Make sure the max electron energy is valid
  testPrecondition( d_data_container->getMinElectronEnergy() <
                    max_electron_energy );

  d_data_container->setMaxElectronEnergy( max_electron_energy );
}

// Return the max electron energy
double ElectronPhotonRelaxationDataGenerator::getMaxElectronEnergy() const
{
  return d_data_container->getMaxElectronEnergy();
}

// Set the default photon grid convergence tolerance
void ElectronPhotonRelaxationDataGenerator::setDefaultPhotonGridConvergenceTolerance(
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
  d_data_container->setPhotonGridConvergenceTolerance( convergence_tol );
}

// Get the default photon grid convergence tolerance
double ElectronPhotonRelaxationDataGenerator::getDefaultPhotonGridConvergenceTolerance() const
{
  return d_default_photon_grid_generator->getConvergenceTolerance();
}

// Set the default photon grid absolute difference tolerance
void ElectronPhotonRelaxationDataGenerator::setDefaultPhotonGridAbsoluteDifferenceTolerance(
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
  d_data_container->setPhotonGridAbsoluteDifferenceTolerance( absolute_diff_tol );
}

// Get the default photon grid absolute difference tolerance
double ElectronPhotonRelaxationDataGenerator::getDefaultPhotonGridAbsoluteDifferenceTolerance() const
{
  return d_default_photon_grid_generator->getAbsoluteDifferenceTolerance();
}

// Set the default photon grid distance tolerance
void ElectronPhotonRelaxationDataGenerator::setDefaultPhotonGridDistanceTolerance(
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
  d_data_container->setPhotonGridDistanceTolerance( distance_tol );
}

// Get the default photon grid distance tolerance
double ElectronPhotonRelaxationDataGenerator::getDefaultPhotonGridDistanceTolerance() const
{
  return d_default_photon_grid_generator->getDistanceTolerance();
}

// Set the default electron grid convergence tolerance
void ElectronPhotonRelaxationDataGenerator::setDefaultElectronGridConvergenceTolerance(
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
  d_data_container->setElectronGridConvergenceTolerance( convergence_tol );
}

// Get the default electron grid convergence tolerance
double ElectronPhotonRelaxationDataGenerator::getDefaultElectronGridConvergenceTolerance() const
{
  return d_default_electron_grid_generator->getConvergenceTolerance();
}

// Set the default electron grid absolute difference tolerance
void ElectronPhotonRelaxationDataGenerator::setDefaultElectronGridAbsoluteDifferenceTolerance(
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
  d_data_container->setElectronGridAbsoluteDifferenceTolerance( absolute_diff_tol );
}

// Get the default electron grid absolute difference tolerance
double ElectronPhotonRelaxationDataGenerator::getDefaultElectronGridAbsoluteDifferenceTolerance() const
{
  return d_default_electron_grid_generator->getAbsoluteDifferenceTolerance();
}

// Set the default electron grid distance tolerance
void ElectronPhotonRelaxationDataGenerator::setDefaultElectronGridDistanceTolerance(
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
  d_data_container->setElectronGridDistanceTolerance( distance_tol );
}

// Get the default electron grid distance tolerance
double ElectronPhotonRelaxationDataGenerator::getDefaultElectronGridDistanceTolerance() const
{
  return d_default_electron_grid_generator->getDistanceTolerance();
}

// Set the occupation number evaluation tolerance
void ElectronPhotonRelaxationDataGenerator::setOccupationNumberEvaluationTolerance(
                                            const double evaluation_tolerance )
{
  // Make sure the evaluation tolerance is valid
  TEST_FOR_EXCEPTION( evaluation_tolerance <= 0.0,
                      std::runtime_error,
                      "The occupation number evaluation tolerance must be "
                      "between 0.0 and 1.0!" );
  TEST_FOR_EXCEPTION( evaluation_tolerance >= 1.0,
                      std::runtime_error,
                      "The occupation number evaluation tolerance must be "
                      "between 0.0 and 1.0!" );

  d_data_container->setOccupationNumberEvaluationTolerance( evaluation_tolerance );
}

// Get the occupation number evaluation tolerance
double ElectronPhotonRelaxationDataGenerator::getOccupationNumberEvaluationTolerance() const
{
  return d_data_container->getOccupationNumberEvaluationTolerance();
}

// Set the subshell incoherent evaluation tolerance
void ElectronPhotonRelaxationDataGenerator::setSubshellIncoherentEvaluationTolerance(
                                            const double evaluation_tolerance )
{
  // Make sure the evaluation tolerance is valid
  TEST_FOR_EXCEPTION( evaluation_tolerance <= 0.0,
                      std::runtime_error,
                      "The subshell incoherent evaluation tolerance must be "
                      "between 0.0 and 1.0!" );
  TEST_FOR_EXCEPTION( evaluation_tolerance >= 1.0,
                      std::runtime_error,
                      "The subshell incoherent number evaluation tolerance "
                      "must be between 0.0 and 1.0!" );

  d_data_container->setSubshellIncoherentEvaluationTolerance( evaluation_tolerance );
}

// Get the subshell incoherent evaluation tolerance
double ElectronPhotonRelaxationDataGenerator::getSubshellIncoherentEvaluationTolerance() const
{
  return d_data_container->getSubshellIncoherentEvaluationTolerance();
}

// Set the photon threshold energy nudge factor
void ElectronPhotonRelaxationDataGenerator::setPhotonThresholdEnergyNudgeFactor(
                                                    const double nudge_factor )
{
  // Make sure the nudge factor is valid
  TEST_FOR_EXCEPTION( nudge_factor < 1.0,
                      std::runtime_error,
                      "The photon threshold energy nudge factor must be "
                      "greater than or equal to 1.0!" );

  d_data_container->setPhotonThresholdEnergyNudgeFactor( nudge_factor );
}

// Get the photon threshold energy nudge factor
double ElectronPhotonRelaxationDataGenerator::getPhotonThresholdEnergyNudgeFactor() const
{
  return d_data_container->getPhotonThresholdEnergyNudgeFactor();
}

// Set the cutoff angle cosine
void ElectronPhotonRelaxationDataGenerator::setCutoffAngleCosine(
                                             const double cutoff_angle_cosine )
{
  // Make sure the cutoff angle cosine is valid
  TEST_FOR_EXCEPTION( cutoff_angle_cosine < -1.0,
                      std::runtime_error,
                      "The cutoff angle cosine must be between -1.0 and "
                      "1.0!" );
  TEST_FOR_EXCEPTION( cutoff_angle_cosine > 1.0,
                      std::runtime_error,
                      "The cutoff angle cosine must be between -1.0 and "
                      "1.0!" );

  d_data_container->setCutoffAngleCosine( cutoff_angle_cosine );
}

// Get the cutoff angle cosine
double ElectronPhotonRelaxationDataGenerator::getCutoffAngleCosine() const
{
  return d_data_container->getCutoffAngleCosine();
}

// Set the number of moment preserving angles
void ElectronPhotonRelaxationDataGenerator::setNumberOfMomentPreservingAngles(
                                              const unsigned number_of_angles )
{
  d_data_container->setNumberOfMomentPreservingAngles( number_of_angles );
}

// Get the number of moment preserving angles
double ElectronPhotonRelaxationDataGenerator::getNumberOfMomentPreservingAngles() const
{
  return d_data_container->getNumberOfMomentPreservingAngles();
}

// Set refine secondary electron grids mode on (Default off)
void ElectronPhotonRelaxationDataGenerator::setRefineSecondaryElectronGridsModeOn()
{
  d_refine_secondary_electron_grid_mode = true;
}

// Set refine secondary electron grids mode off (Default off)
void ElectronPhotonRelaxationDataGenerator::setRefineSecondaryElectronGridsModeOff()
{
  d_refine_secondary_electron_grid_mode = false;
}

// Return if the refine secondary electron grids mode is on (default off)
bool ElectronPhotonRelaxationDataGenerator::isRefineSecondaryElectronGridsModeOn()
{
  return d_refine_secondary_electron_grid_mode;
}

// Set the electron elastic sampling method (TWO_D_UNION by default)
void ElectronPhotonRelaxationDataGenerator::setElectronElasticSamplingMethod(
    MonteCarlo::CoupledElasticSamplingMethod sampling )
{
  d_elastic_sampling_method = sampling;
}

// Return the electron elastic sampling method
MonteCarlo::CoupledElasticSamplingMethod
ElectronPhotonRelaxationDataGenerator::getElectronElasticSamplingMethod() const
{
  return d_elastic_sampling_method;
}

// Set the evaluation tolerance for the bremsstrahlung cross section
void ElectronPhotonRelaxationDataGenerator::setBremsstrahlungEvaluationTolerance(
                                            const double evaluation_tolerance )
{
  // Make sure the evaluation tolerance is valid
  testPrecondition( evaluation_tolerance > 0.0 );
  testPrecondition( evaluation_tolerance < 1.0 );

  d_data_container->setBremsstrahlungEvaluationTolerance( evaluation_tolerance );
}

// Get the evaluation tolerance for the bremsstrahlung cross section
double ElectronPhotonRelaxationDataGenerator::getBremsstrahlungEvaluationTolerance() const
{
  return d_data_container->getBremsstrahlungEvaluationTolerance();
}

// Set the bremsstrahlung grid convergence tolerance
void ElectronPhotonRelaxationDataGenerator::setBremsstrahlungGridConvergenceTolerance(
                                                 const double convergence_tol )
{
  // Make sure the convergence tolerance is valid
  testPrecondition( convergence_tol <= 1.0 );
  testPrecondition( convergence_tol > 0.0 );

  d_data_container->setBremsstrahlungGridConvergenceTolerance( convergence_tol );
}

// Return the bremsstrahlung grid convergence tolerance
double ElectronPhotonRelaxationDataGenerator::getBremsstrahlungGridConvergenceTolerance() const
{
  return d_data_container->getBremsstrahlungGridConvergenceTolerance();
}

// Set the bremsstrahlung absolute difference tolerance
void ElectronPhotonRelaxationDataGenerator::setBremsstrahlungAbsoluteDifferenceTolerance(
                                               const double absolute_diff_tol )
{
  // Make sure the absolute difference tolerance is valid
  testPrecondition( absolute_diff_tol <= 1.0 );
  testPrecondition( absolute_diff_tol >= 0.0 );

  d_data_container->setBremsstrahlungAbsoluteDifferenceTolerance( absolute_diff_tol );
}

// Get the bremsstrahlung absolute difference tolerance
double ElectronPhotonRelaxationDataGenerator::getBremsstrahlungAbsoluteDifferenceTolerance() const
{
  return d_data_container->getBremsstrahlungAbsoluteDifferenceTolerance();
}

// Set the bremsstrahlung distance tolerance
void ElectronPhotonRelaxationDataGenerator::setBremsstrahlungDistanceTolerance(
                                                    const double distance_tol )
{
  // Make sure the distance tolerance is valid
  testPrecondition( distance_tol <= 1.0 );
  testPrecondition( distance_tol >= 0.0 );

  d_data_container->setBremsstrahlungDistanceTolerance( distance_tol );
}

// Get the bremsstrahlung distance tolerance
double ElectronPhotonRelaxationDataGenerator::getBremsstrahlungDistanceTolerance() const
{
  return d_data_container->getBremsstrahlungDistanceTolerance();
}

// Set the evaluation tolerance for the electroionization cross section
void ElectronPhotonRelaxationDataGenerator::setElectroionizationEvaluationTolerance(
                                            const double evaluation_tolerance )
{
  // Make sure the evaluation tolerance is valid
  testPrecondition( evaluation_tolerance > 0.0 );
  testPrecondition( evaluation_tolerance < 1.0 );

  d_data_container->setElectroionizationEvaluationTolerance( evaluation_tolerance );
}

// Get the evaluation tolerance for the electroionization cross section
double ElectronPhotonRelaxationDataGenerator::getElectroionizationEvaluationTolerance() const
{
  return d_data_container->getElectroionizationEvaluationTolerance();
}

// Set the electroionization grid convergence tolerance
void ElectronPhotonRelaxationDataGenerator::setElectroionizationGridConvergenceTolerance(
                                                 const double convergence_tol )
{
  // Make sure the convergence tolerance is valid
  testPrecondition( convergence_tol <= 1.0 );
  testPrecondition( convergence_tol > 0.0 );

  d_data_container->setElectroionizationGridConvergenceTolerance( convergence_tol );
}

// Return the electroionization grid convergence tolerance
double ElectronPhotonRelaxationDataGenerator::getElectroionizationGridConvergenceTolerance() const
{
  return d_data_container->getElectroionizationGridConvergenceTolerance();
}

// Set the electroionization absolute difference tolerance
void ElectronPhotonRelaxationDataGenerator::setElectroionizationAbsoluteDifferenceTolerance(
                                               const double absolute_diff_tol )
{
  // Make sure the absolute difference tolerance is valid
  testPrecondition( absolute_diff_tol <= 1.0 );
  testPrecondition( absolute_diff_tol >= 0.0 );

  d_data_container->setElectroionizationAbsoluteDifferenceTolerance( absolute_diff_tol );
}

// Get the electroionization absolute difference tolerance
double ElectronPhotonRelaxationDataGenerator::getElectroionizationAbsoluteDifferenceTolerance() const
{
  return d_data_container->getElectroionizationAbsoluteDifferenceTolerance();
}

// Set the electroionization distance tolerance
void ElectronPhotonRelaxationDataGenerator::setElectroionizationDistanceTolerance(
                                                    const double distance_tol )
{
  // Make sure the distance tolerance is valid
  testPrecondition( distance_tol <= 1.0 );
  testPrecondition( distance_tol >= 0.0 );

  d_data_container->setElectroionizationDistanceTolerance( distance_tol );
}

// Get the electroionization distance tolerance
double ElectronPhotonRelaxationDataGenerator::getElectroionizationDistanceTolerance() const
{
  return d_data_container->getElectroionizationDistanceTolerance();
}

// Set the FullyTabularTwoDDistribution evaluation tolerance
void ElectronPhotonRelaxationDataGenerator::setTabularEvaluationTolerance(
    const double evaluation_tolerance )
{
  // Make sure the evaluation tolerance is valid
  TEST_FOR_EXCEPTION( evaluation_tolerance <= 0.0,
                      std::runtime_error,
                      "The tabular evaluation tolerance must be between 0.0 "
                      "and 1.0!" );
  TEST_FOR_EXCEPTION( evaluation_tolerance >= 1.0,
                      std::runtime_error,
                      "The tabular evaluation tolerance must be between 0.0 "
                      "and 1.0!" );

  d_data_container->setElectronTabularEvaluationTolerance( evaluation_tolerance );
}

// Get the FullyTabularTwoDDistribution evaluation tolerance
double ElectronPhotonRelaxationDataGenerator::getTabularEvaluationTolerance() const
{
  return d_data_container->getElectronTabularEvaluationTolerance();
}

// Set the electron TwoDInterpPolicy (LogLogLog by default)
/*! \details When the Y interpolation of the electron 2D interpolation policy
 * is Log (e.g. Lin-Log-Lin, Log-Log-Log, etc) the elastic 2D interpolation uses the LogCos
 * equivelent (e.g. Lin-LogCos-Lin, Log-LogCos-Log, etc).
 */
void ElectronPhotonRelaxationDataGenerator::setElectronTwoDInterpPolicy(
                               MonteCarlo::TwoDInterpolationType two_d_interp )
{

  d_two_d_interp = two_d_interp;

  d_data_container->setElectronTwoDInterpPolicy( Utility::toString( two_d_interp ) );
}

// Return the electron TwoDInterpPolicy
MonteCarlo::TwoDInterpolationType ElectronPhotonRelaxationDataGenerator::getElectronTwoDInterpPolicy() const
{
  return d_two_d_interp;
}

// Set the electron TwoDGridPolicy (UnitBaseCorrelated by default)
void ElectronPhotonRelaxationDataGenerator::setElectronTwoDGridPolicy(
                                      MonteCarlo::TwoDGridType two_d_grid )
{
  d_two_d_grid = two_d_grid;

  d_data_container->setElectronTwoDGridPolicy( Utility::toString( two_d_grid ) );
}

// Return the electron TwoDGridPolicy
MonteCarlo::TwoDGridType ElectronPhotonRelaxationDataGenerator::getElectronTwoDGridPolicy() const
{
  return d_two_d_grid;
}

// Set the generation notes
void ElectronPhotonRelaxationDataGenerator::setNotes( const std::string& notes )
{
  d_data_container->setNotes( notes );
}

// Get the generation notes
const std::string& ElectronPhotonRelaxationDataGenerator::getNotes() const
{
  return d_data_container->getNotes();
}

//! Get a default photon grid generator (Lin-Lin grid)
const Utility::GridGenerator<Utility::LinLin>&
ElectronPhotonRelaxationDataGenerator::getDefaultPhotonGridGenerator() const
{
  return *d_default_photon_grid_generator;
}

//! Get a default electron grid generator (Log-Log grid)
const Utility::GridGenerator<Utility::LogLog>&
ElectronPhotonRelaxationDataGenerator::getDefaultElectronGridGenerator() const
{
  return *d_default_electron_grid_generator;
}

// Get the data container
const Data::ElectronPhotonRelaxationDataContainer&
ElectronPhotonRelaxationDataGenerator::getDataContainer() const
{
  return *d_data_container;
}

// Get the shared data container
std::shared_ptr<const Data::ElectronPhotonRelaxationDataContainer>
ElectronPhotonRelaxationDataGenerator::getSharedDataContainer() const
{
  return d_data_container;
}

// Get the volatile data container
Data::ElectronPhotonRelaxationVolatileDataContainer&
ElectronPhotonRelaxationDataGenerator::getVolatileDataContainer()
{
  return *d_data_container;
}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_ElectronPhotonRelaxationDataGenerator.cpp
//---------------------------------------------------------------------------//
