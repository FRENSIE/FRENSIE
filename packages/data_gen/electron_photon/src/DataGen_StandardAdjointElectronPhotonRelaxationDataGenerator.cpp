//---------------------------------------------------------------------------//
//!
//! \file   DataGen_StandardAdjointElectronPhotonRelaxationDataGenerator.hpp
//! \author Luke Kersting
//! \brief  The standard adjoint electron-photon-relaxation data generator class def.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <algorithm>

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// FRENSIE Includes
#include "DataGen_StandardAdjointElectronPhotonRelaxationDataGenerator.hpp"
#include "DataGen_AdjointPairProductionEnergyDistributionNormConstantEvaluator.hpp"
#include "DataGen_AdjointElectronDistributionGenerator.hpp"
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_ElectroatomicReactionNativeFactory.hpp"
#include "MonteCarlo_AnalogElasticElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroatomicReactionNativeFactory.hpp"
#include "MonteCarlo_VoidStandardElectroatomicReaction.hpp"
#include "MonteCarlo_BremsstrahlungElectronScatteringDistribution.hpp"
#include "MonteCarlo_StandardComptonProfile.hpp"
#include "MonteCarlo_StandardOccupationNumber.hpp"
#include "MonteCarlo_StandardScatteringFunction.hpp"
#include "MonteCarlo_WHIncoherentAdjointPhotonScatteringDistribution.hpp"
#include "MonteCarlo_SubshellIncoherentAdjointPhotonScatteringDistribution.hpp"
#include "Data_SubshellType.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_GridGenerator.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_SloanRadauQuadrature.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"

namespace DataGen{

// Advanced Constructor
StandardAdjointElectronPhotonRelaxationDataGenerator::StandardAdjointElectronPhotonRelaxationDataGenerator(
      const std::shared_ptr<const Data::ElectronPhotonRelaxationDataContainer>&
      forward_epr_data,
      const double min_photon_energy,
      const double max_photon_energy,
      const double min_electron_energy,
      const double max_electron_energy,
      std::ostream* os_log,
      std::ostream* os_warn )
  : AdjointElectronPhotonRelaxationDataGenerator( forward_epr_data->getAtomicNumber(),
                                                  min_photon_energy,
                                                  max_photon_energy,
                                                  min_electron_energy,
                                                  max_electron_energy ),
    d_forward_epr_data( forward_epr_data ),
    d_os_log( os_log ),
    d_adjoint_incoherent_max_energy_nudge_value( 0.2 ),
    d_adjoint_incoherent_energy_to_max_energy_nudge_value( 1e-6 ),
    d_adjoint_incoherent_evaluation_tol( 0.001 ),
    d_adjoint_incoherent_grid_convergence_tol( 0.001 ),
    d_adjoint_incoherent_grid_absolute_diff_tol( 1e-20 ),
    d_adjoint_incoherent_grid_distance_tol( 1e-14 ),
    d_adjoint_electron_grid_convergence_tol( 0.001 ),
    d_adjoint_electron_absolute_diff_tol( 1e-16 ),
    d_adjoint_electron_distance_tol( 1e-8 ),
    d_adjoint_bremsstrahlung_max_energy_nudge_value( 0.2 ),
    d_adjoint_bremsstrahlung_energy_to_outgoing_energy_nudge_value( 1e-7 ),
    d_adjoint_bremsstrahlung_evaluation_tol( 1e-6 ),
    d_adjoint_bremsstrahlung_grid_convergence_tol( 0.001 ),
    d_adjoint_bremsstrahlung_absolute_diff_tol( 1e-12 ),
    d_adjoint_bremsstrahlung_distance_tol( 1e-14 ),
    d_adjoint_electroionization_evaluation_tol( 1e-6 ),
    d_adjoint_electroionization_grid_convergence_tol( 0.001 ),
    d_adjoint_electroionization_absolute_diff_tol( 1e-12 ),
    d_adjoint_electroionization_distance_tol( 1e-14 )
{
  // Make sure the forward epr data is valid
  testPrecondition( forward_epr_data.get() );
  // Make sure the log stream is valid
  testPrecondition( os_log != NULL );
  // Make sure the warning stream is valid
  testPrecondition( os_warn != NULL );

  // Check if the min photon energy is below the forward table min energy
  if( min_photon_energy < forward_epr_data->getMinPhotonEnergy() )
  {
    this->setMinPhotonEnergy( forward_epr_data->getMinPhotonEnergy() );

    (*os_warn) << "Warning: the min photon energy requested is below the "
               << "requested forward table min photon energy! The table's min "
               << "photon energy will be used instead."
               << std::endl;
  }

  // Check if the max photon energy is above the forward table max energy
  if( max_photon_energy > forward_epr_data->getMaxPhotonEnergy() )
  {
    this->setMaxPhotonEnergy( forward_epr_data->getMaxPhotonEnergy() );

    (*os_warn) << "Warning: the max photon energy requested is above the "
               << "requested forward table max photon energy! The table's max "
               << "photon energy will be used instead."
               << std::endl;
  }

  // Check if the min electron energy is below the forward table min energy
  if( min_electron_energy < forward_epr_data->getMinElectronEnergy() )
  {
    this->setMinElectronEnergy( forward_epr_data->getMinElectronEnergy() );

    (*os_warn) << "Warning: the min electron energy requested is above the "
               << "requested forward table min electron energy! The table's "
               << "min electron energy will be used instead."
               << std::endl;
  }

  // Check if the max electron energy is above the forward table max energy
  if( max_electron_energy > forward_epr_data->getMaxElectronEnergy() )
  {
    this->setMaxElectronEnergy( forward_epr_data->getMaxElectronEnergy() );

    (*os_warn) << "Warning: the max electron energy requested is above the "
               << "requested forward table max electron energy! The table's "
               << "max electron energy will be used instead."
               << std::endl;
  }
}

// Basic Constructor
StandardAdjointElectronPhotonRelaxationDataGenerator::StandardAdjointElectronPhotonRelaxationDataGenerator(
      const std::shared_ptr<const Data::ElectronPhotonRelaxationDataContainer>&
      forward_epr_data,
      std::ostream* os_log )
  : StandardAdjointElectronPhotonRelaxationDataGenerator(
                                    forward_epr_data,
                                    forward_epr_data->getMinPhotonEnergy(),
                                    forward_epr_data->getMaxPhotonEnergy(),
                                    forward_epr_data->getMinElectronEnergy(),
                                    forward_epr_data->getMaxElectronEnergy(),
                                    os_log )
{ /* ... */ }

// Set the adjoint pair production energy dist. norm const. evaluation tol.
void StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointPairProductionEnergyDistNormConstEvaluationTolerance(
                                                  const double evaluation_tol )
{
  // Make sure the evaluation tolerance is valid
  testPrecondition( evaluation_tol > 0.0 );
  testPrecondition( evaluation_tol < 1.0 );

  d_adjoint_pair_production_energy_dist_norm_const_evaluation_tol =
    evaluation_tol;
}

// Get the adjoint pair production energy dist. norm const. evaluation tol
double StandardAdjointElectronPhotonRelaxationDataGenerator::getAdjointPairProductionEnergyDistNormConstEvaluationTolerance() const
{
  return d_adjoint_pair_production_energy_dist_norm_const_evaluation_tol;
}

// Set the adjoint triplet production energy dist. norm const. evaluation tol.
void StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointTripletProductionEnergyDistNormConstEvaluationTolerance(
                                                  const double evaluation_tol )
{
  // Make sure the evaluation tolerance is valid
  testPrecondition( evaluation_tol > 0.0 );
  testPrecondition( evaluation_tol < 1.0 );

  d_adjoint_triplet_production_energy_dist_norm_const_evaluation_tol =
    evaluation_tol;
}

// Get the adjoint triplet production energy dist. norm const. evaluation tol
double StandardAdjointElectronPhotonRelaxationDataGenerator::getAdjointTripletProductionEnergyDistNormConstEvaluationTolerance() const
{
  return d_adjoint_triplet_production_energy_dist_norm_const_evaluation_tol;
}

// Set the adjoint incoherent max energy nudge value
void StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointIncoherentMaxEnergyNudgeValue(
                                          const double max_energy_nudge_value )
{
  // Make sure the nudge value is valid
  testPrecondition( max_energy_nudge_value > 0.0 );

  d_adjoint_incoherent_max_energy_nudge_value = max_energy_nudge_value;
}
  
// Return the adjoint incoherent max energy nudge value
double StandardAdjointElectronPhotonRelaxationDataGenerator::getAdjointIncoherentMaxEnergyNudgeValue() const
{
  return d_adjoint_incoherent_max_energy_nudge_value;
}

// Set the adjoint incoherent energy to max energy nudge value
void StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointIncoherentEnergyToMaxEnergyNudgeValue(
                                const double energy_to_max_energy_nudge_value )
{
  // Make sure the nudge value is valid
  testPrecondition( energy_to_max_energy_nudge_value >= 0.0 );

  d_adjoint_incoherent_energy_to_max_energy_nudge_value =
    energy_to_max_energy_nudge_value;
}

// Return the adjoint incoherent energy to max energy nudge value
double StandardAdjointElectronPhotonRelaxationDataGenerator::getAdjointIncoherentEnergyToMaxEnergyNudgeValue() const
{
  return d_adjoint_incoherent_energy_to_max_energy_nudge_value;
}

// Set the adjoint incoherent cross section evaluation tolerance
void StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointIncoherentEvaluationTolerance(
                                                  const double evaluation_tol )
{
  // Make sure the evaluation tolerance is valid
  testPrecondition( evaluation_tol > 0.0 );
  testPrecondition( evaluation_tol < 1.0 );

  d_adjoint_incoherent_evaluation_tol = evaluation_tol;
}

// Return the adjoint incoherent cross section evaluation tolerance
double StandardAdjointElectronPhotonRelaxationDataGenerator::getAdjointIncoherentCrossSectionEvaluationTolerance() const
{
  return d_adjoint_incoherent_evaluation_tol;
}

// Set the adjoint incoherent grid convergence tolerance
void StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointIncoherentGridConvergenceTolerance(
                                                 const double convergence_tol )
{
  // Make sure the convergence tolerance is valid
  testPrecondition( convergence_tol <= 1.0 );
  testPrecondition( convergence_tol > 0.0 );

  d_adjoint_incoherent_grid_convergence_tol = convergence_tol;
}

// Return the adjoint incoherent grid convergence tolerance
double StandardAdjointElectronPhotonRelaxationDataGenerator::getAdjointIncoherentGridConvergenceTolerance() const
{
  return d_adjoint_incoherent_grid_convergence_tol;
}

// Set the adjoint incoherent absolute difference tolerance
void StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointIncoherentAbsoluteDifferenceTolerance(
                                               const double absolute_diff_tol )
{
  // Make sure the absolute difference tolerance is valid
  testPrecondition( absolute_diff_tol <= 1.0 );
  testPrecondition( absolute_diff_tol >= 0.0 );

  d_adjoint_incoherent_grid_absolute_diff_tol = absolute_diff_tol;
}

// Get the adjoint incoherent absolute difference tolerance
double StandardAdjointElectronPhotonRelaxationDataGenerator::getAdjointIncoherentAbsoluteDifferenceTolerance() const
{
  return d_adjoint_incoherent_grid_absolute_diff_tol;
}

// Set the adjoint incoherent distance tolerance
void StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointIncoherentDistanceTolerance(
                                                    const double distance_tol )
{
  // Make sure the distance tolerance is valid
  testPrecondition( distance_tol <= 1.0 );
  testPrecondition( distance_tol >= 0.0 );

  d_adjoint_incoherent_grid_distance_tol = distance_tol;
}

// Get the adjoint incoherent distance tolerance
double StandardAdjointElectronPhotonRelaxationDataGenerator::getAdjointIncoherentDistanceTolerance() const
{
  return d_adjoint_incoherent_grid_distance_tol;
}

// Get the cutoff angle cosine above which screened rutherford is used
double StandardAdjointElectronPhotonRelaxationDataGenerator::getCutoffAngleCosine() const
{
  return d_forward_epr_data->getCutoffAngleCosine();
}

// Get the number of moment preserving angles
unsigned StandardAdjointElectronPhotonRelaxationDataGenerator::getNumberOfMomentPreservingAngles() const
{
  return d_forward_epr_data->getCutoffAngleCosine();
}

// Set the adjoint bremsstrahlung max energy nudge value
void StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointBremsstrahlungMaxEnergyNudgeValue(
                                          const double max_energy_nudge_value )
{
  // Make sure the nudge value is valid
  testPrecondition( max_energy_nudge_value > 0.0 );

  d_adjoint_bremsstrahlung_max_energy_nudge_value = max_energy_nudge_value;
}
  
// Return the adjoint bremsstrahlung max energy nudge value
double StandardAdjointElectronPhotonRelaxationDataGenerator::getAdjointBremsstrahlungMaxEnergyNudgeValue() const
{
  return d_adjoint_bremsstrahlung_max_energy_nudge_value;
}

// Set the adjoint bremsstrahlung energy to outgoing energy nudge value
void StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointBremsstrahlungEnergyToOutgoingEnergyNudgeValue(
                            const double energy_to_outgoing_energy_nudge_value )
{
  // Make sure the nudge value is valid
  testPrecondition( energy_to_outgoing_energy_nudge_value >= 0.0 );

  d_adjoint_bremsstrahlung_energy_to_outgoing_energy_nudge_value =
    energy_to_outgoing_energy_nudge_value;
}

// Return the adjoint bremsstrahlung energy to outgoing energy nudge value
double StandardAdjointElectronPhotonRelaxationDataGenerator::getAdjointBremsstrahlungEnergyToOutgoingEnergyNudgeValue() const
{
  return d_adjoint_bremsstrahlung_energy_to_outgoing_energy_nudge_value;
}

// Set the evaluation tolerance for the adjoint bremsstrahlung cross section
void StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointBremsstrahlungEvaluationTolerance(
                                            const double evaluation_tolerance )
{
  // Make sure the evaluation tolerance is valid
  testPrecondition( evaluation_tolerance > 0.0 );
  testPrecondition( evaluation_tolerance < 1.0 );

  d_adjoint_bremsstrahlung_evaluation_tol = evaluation_tolerance;
}
  
// Get the evaluation tolerance for the adjoint bremsstrahlung cross section
double StandardAdjointElectronPhotonRelaxationDataGenerator::getAdjointBremsstrahlungEvaluationTolerance() const
{
  return d_adjoint_bremsstrahlung_evaluation_tol;
}

// Set the adjoint bremsstrahlung grid convergence tolerance
void StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointBremsstrahlungGridConvergenceTolerance(
                                                 const double convergence_tol )
{
  // Make sure the convergence tolerance is valid
  testPrecondition( convergence_tol <= 1.0 );
  testPrecondition( convergence_tol > 0.0 );

  d_adjoint_bremsstrahlung_grid_convergence_tol = convergence_tol;
}

// Return the adjoint bremsstrahlung grid convergence tolerance
double StandardAdjointElectronPhotonRelaxationDataGenerator::getAdjointBremsstrahlungGridConvergenceTolerance() const
{
  return d_adjoint_bremsstrahlung_grid_convergence_tol;
}

// Set the adjoint bremsstrahlung absolute difference tolerance
void StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointBremsstrahlungAbsoluteDifferenceTolerance(
                                               const double absolute_diff_tol )
{
  // Make sure the absolute difference tolerance is valid
  testPrecondition( absolute_diff_tol <= 1.0 );
  testPrecondition( absolute_diff_tol >= 0.0 );

  d_adjoint_bremsstrahlung_absolute_diff_tol = absolute_diff_tol;
}

// Get the adjoint bremsstrahlung absolute difference tolerance
double StandardAdjointElectronPhotonRelaxationDataGenerator::getAdjointBremsstrahlungAbsoluteDifferenceTolerance() const
{
  return d_adjoint_bremsstrahlung_absolute_diff_tol;
}

// Set the adjoint bremsstrahlung distance tolerance
void StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointBremsstrahlungDistanceTolerance(
                                                    const double distance_tol )
{
  // Make sure the distance tolerance is valid
  testPrecondition( distance_tol <= 1.0 );
  testPrecondition( distance_tol >= 0.0 );

  d_adjoint_bremsstrahlung_distance_tol = distance_tol;
}

// Get the adjoint bremsstrahlung distance tolerance
double StandardAdjointElectronPhotonRelaxationDataGenerator::getAdjointBremsstrahlungDistanceTolerance() const
{
  return d_adjoint_bremsstrahlung_distance_tol;
}

// Set the evaluation tolerance for the adjoint electroionization cross section
void StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointElectroionizationEvaluationTolerance(
                                            const double evaluation_tolerance )
{
  // Make sure the evaluation tolerance is valid
  testPrecondition( evaluation_tolerance > 0.0 );
  testPrecondition( evaluation_tolerance < 1.0 );

  d_adjoint_electroionization_evaluation_tol = evaluation_tolerance;
}
  
// Get the evaluation tolerance for the adjoint electroionization cross section
double StandardAdjointElectronPhotonRelaxationDataGenerator::getAdjointElectroionizationEvaluationTolerance() const
{
  return d_adjoint_electroionization_evaluation_tol;
}

// Set the adjoint electroionization grid convergence tolerance
void StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointElectroionizationGridConvergenceTolerance(
                                                 const double convergence_tol )
{
  // Make sure the convergence tolerance is valid
  testPrecondition( convergence_tol <= 1.0 );
  testPrecondition( convergence_tol > 0.0 );

  d_adjoint_electroionization_grid_convergence_tol = convergence_tol;
}

// Return the adjoint electroionization grid convergence tolerance
double StandardAdjointElectronPhotonRelaxationDataGenerator::getAdjointElectroionizationGridConvergenceTolerance() const
{
  return d_adjoint_electroionization_grid_convergence_tol;
}

// Set the adjoint electroionization absolute difference tolerance
void StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointElectroionizationAbsoluteDifferenceTolerance(
                                               const double absolute_diff_tol )
{
  // Make sure the absolute difference tolerance is valid
  testPrecondition( absolute_diff_tol <= 1.0 );
  testPrecondition( absolute_diff_tol >= 0.0 );

  d_adjoint_electroionization_absolute_diff_tol = absolute_diff_tol;
}

// Get the adjoint electroionization absolute difference tolerance
double StandardAdjointElectronPhotonRelaxationDataGenerator::getAdjointElectroionizationAbsoluteDifferenceTolerance() const
{
  return d_adjoint_electroionization_absolute_diff_tol;
}

// Set the adjoint electroionization distance tolerance
void StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointElectroionizationDistanceTolerance(
                                                    const double distance_tol )
{
  // Make sure the distance tolerance is valid
  testPrecondition( distance_tol <= 1.0 );
  testPrecondition( distance_tol >= 0.0 );

  d_adjoint_electroionization_distance_tol = distance_tol;
}

// Get the adjoint electroionization distance tolerance
double StandardAdjointElectronPhotonRelaxationDataGenerator::getAdjointElectroionizationDistanceTolerance() const
{
  return d_adjoint_electroionization_distance_tol;
}

// Set the adjoint electron grid convergence tolerance
void StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointElectronGridConvergenceTolerance(
                        const double adjoint_electron_grid_convergence_tol )
{
  d_adjoint_electron_grid_convergence_tol =
    adjoint_electron_grid_convergence_tol;
}

// Get the adjoint electron grid convergence tolerance
double StandardAdjointElectronPhotonRelaxationDataGenerator::getAdjointElectronGridConvergenceTolerance() const
{
  return d_adjoint_electron_grid_convergence_tol;
}

// Set the adjoint electron absolute diff tolerance
void StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointElectronAbsoluteDifferenceTolerance(
                        const double adjoint_electron_absolute_diff_tol )
{
  d_adjoint_electron_absolute_diff_tol = adjoint_electron_absolute_diff_tol;
}

// Get the adjoint electron absolute diff tolerance
double StandardAdjointElectronPhotonRelaxationDataGenerator::getAdjointElectronAbsoluteDifferenceTolerance() const
{
  return d_adjoint_electron_absolute_diff_tol;
}

// Set the adjoint electron distance tolerance
void StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointElectronDistanceTolerance(
                        const double adjoint_electron_distance_tol )
{
  d_adjoint_electron_distance_tol = adjoint_electron_distance_tol;
}

// Get the adjoint electron distance tolerance
double StandardAdjointElectronPhotonRelaxationDataGenerator::getAdjointElectronDistanceTolerance() const
{
  return d_adjoint_electron_distance_tol;
}

// Populate the adjoint electron-photon-relaxation data container
void StandardAdjointElectronPhotonRelaxationDataGenerator::populateEPRDataContainer(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container ) const
{
  // Set the table data
  (*d_os_log) << std::endl << "Setting the table data...";
  d_os_log->flush();
  this->setTableData( data_container );
  (*d_os_log) << "done." << std::endl;

  // Set the relaxation data
  (*d_os_log) << std::endl << "Setting the adjoint relaxation data...";
  d_os_log->flush();
  this->setAdjointRelaxationData( data_container );
  (*d_os_log) << "done." << std::endl;

  // Set the Compton profile data
  (*d_os_log) << "Setting the Compton profile data...";
  d_os_log->flush();
  this->setComptonProfileData( data_container );
  (*d_os_log) << "done." << std::endl;

  // Set the occupation number data
  (*d_os_log) << "Setting the occupation number data...";
  d_os_log->flush();
  this->setOccupationNumberData( data_container );
  (*d_os_log) << "done." << std::endl;

  // Set the Waller-Hartree scattering function data
  (*d_os_log) << "Setting the Waller-Hartree scattering function data...";
  d_os_log->flush();
  this->setWallerHartreeScatteringFunctionData( data_container );
  (*d_os_log) << "done." << std::endl;

  // Set the Waller-Hartree atomic form factor data
  (*d_os_log) << "Setting the Waller-Hartree atomic form factor data...";
  d_os_log->flush();
  this->setWallerHartreeAtomicFormFactorData( data_container );
  (*d_os_log) << "done." << std::endl;

  // Set the photon data
  (*d_os_log) << "Setting the adjoint photon data... " << std::endl;
  d_os_log->flush();
  this->setAdjointPhotonData( data_container );
  (*d_os_log) << "done." << std::endl;

  // Set the electron data
  (*d_os_log) << "Setting the adjoint electron data: " << std::endl;
  this->setAdjointElectronData( data_container );
  (*d_os_log) << "done." << std::endl;
}

// Set the table data
void StandardAdjointElectronPhotonRelaxationDataGenerator::setTableData(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container ) const
{
  this->setBasicData( data_container );
  this->setDefaultConvergenceParameters( data_container );

  data_container.setAdjointPairProductionEnergyDistNormConstantEvaluationTolerance(
             d_adjoint_pair_production_energy_dist_norm_const_evaluation_tol );
  data_container.setAdjointTripletProductionEnergyDistNormConstantEvaluationTolerance(
          d_adjoint_triplet_production_energy_dist_norm_const_evaluation_tol );
  data_container.setAdjointIncoherentMaxEnergyNudgeValue(
                                 d_adjoint_incoherent_max_energy_nudge_value );
  data_container.setAdjointIncoherentEnergyToMaxEnergyNudgeValue(
                       d_adjoint_incoherent_energy_to_max_energy_nudge_value );
  data_container.setAdjointIncoherentEvaluationTolerance(
                                         d_adjoint_incoherent_evaluation_tol );
  data_container.setAdjointIncoherentGridConvergenceTolerance(
                                   d_adjoint_incoherent_grid_convergence_tol );
  data_container.setAdjointIncoherentGridAbsoluteDifferenceTolerance(
                                 d_adjoint_incoherent_grid_absolute_diff_tol );
  data_container.setAdjointIncoherentGridDistanceTolerance(
                                      d_adjoint_incoherent_grid_distance_tol );
  data_container.setCutoffAngleCosine(
                    d_forward_epr_data->getCutoffAngleCosine() );
  data_container.setNumberOfAdjointMomentPreservingAngles(
                    d_forward_epr_data->getNumberOfMomentPreservingAngles() );
}

// Set the relaxation data
void StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointRelaxationData(
			   Data::AdjointElectronPhotonRelaxationVolatileDataContainer&
			   data_container ) const
{
  // Extract and set the subshells
  const std::set<unsigned>& subshells = d_forward_epr_data->getSubshells();
  
  data_container.setSubshells( subshells );

  // Extract and set the other subshell data
  std::set<unsigned>::const_iterator subshell_it =
    subshells.begin();
  
  while( subshell_it != subshells.end() )
  {
    data_container.setSubshellOccupancy(
                    *subshell_it,
                    d_forward_epr_data->getSubshellOccupancy( *subshell_it ) );

    data_container.setSubshellBindingEnergy(
                *subshell_it,
                d_forward_epr_data->getSubshellBindingEnergy( *subshell_it ) );

    ++subshell_it;
  }
}

// Set the Compton profile data
void StandardAdjointElectronPhotonRelaxationDataGenerator::setComptonProfileData(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container ) const
{
  // Get the subshells
  const std::set<unsigned>& subshells = d_forward_epr_data->getSubshells();

  std::set<unsigned>::const_iterator subshell_it =
    subshells.begin();
  
  // Extract and set the Compton profiles and grids
  while( subshell_it != subshells.end() )
  {
    data_container.setComptonProfileMomentumGrid(
           *subshell_it,
           d_forward_epr_data->getComptonProfileMomentumGrid( *subshell_it ) );

    data_container.setComptonProfile(
                       *subshell_it,
                       d_forward_epr_data->getComptonProfile( *subshell_it ) );

    ++subshell_it;
  }
}

// Set the occupation number data
void StandardAdjointElectronPhotonRelaxationDataGenerator::setOccupationNumberData(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container ) const
{
  // Get the subshells
  const std::set<unsigned>& subshells = d_forward_epr_data->getSubshells();

  std::set<unsigned>::const_iterator subshell_it =
    subshells.begin();

  // Extract and set the occupation numbers and grids
  while( subshell_it != subshells.end() )
  {
    data_container.setOccupationNumberMomentumGrid(
         *subshell_it,
         d_forward_epr_data->getOccupationNumberMomentumGrid( *subshell_it ) );

    data_container.setOccupationNumber(
                     *subshell_it,
                     d_forward_epr_data->getOccupationNumber( *subshell_it ) );

    ++subshell_it;
  }
}

// Set the Waller-Hartree scattering function data
void StandardAdjointElectronPhotonRelaxationDataGenerator::setWallerHartreeScatteringFunctionData(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container ) const
{
  // Extract and set the scattering function grid
  data_container.setWallerHartreeScatteringFunctionMomentumGrid(
        d_forward_epr_data->getWallerHartreeScatteringFunctionMomentumGrid() );

  // Extract and set the scattering function
  data_container.setWallerHartreeScatteringFunction(
                    d_forward_epr_data->getWallerHartreeScatteringFunction() );
}

//! Set the Waller-Hartree atomic form factor data
void StandardAdjointElectronPhotonRelaxationDataGenerator::setWallerHartreeAtomicFormFactorData(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container ) const
{
  // Extract and set the atomic form factor grid
  data_container.setWallerHartreeAtomicFormFactorMomentumGrid(
          d_forward_epr_data->getWallerHartreeAtomicFormFactorMomentumGrid() );

  // Extract and set the atomic form
  data_container.setWallerHartreeAtomicFormFactor(
                      d_forward_epr_data->getWallerHartreeAtomicFormFactor() );
}

// Set the photon data
void StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointPhotonData(
			   Data::AdjointElectronPhotonRelaxationVolatileDataContainer&
			   data_container ) const
{
  // Extract the coherent cross section
  std::shared_ptr<const Utility::OneDDistribution> waller_hartree_coherent_cs(
       new Utility::TabularDistribution<Utility::LinLin>(
                d_forward_epr_data->getPhotonEnergyGrid(),
                d_forward_epr_data->getWallerHartreeCoherentCrossSection() ) );

  // Extract the Waller-Hartree total forward cross section
  std::shared_ptr<const Utility::OneDDistribution> waller_hartree_total_forward_cs(
       new Utility::TabularDistribution<Utility::LinLin>(
                   d_forward_epr_data->getPhotonEnergyGrid(),
                   d_forward_epr_data->getWallerHartreeTotalCrossSection() ) );

  // Extract the impulse approx. total forward cross section
  std::shared_ptr<const Utility::OneDDistribution> impulse_approx_total_forward_cs(
       new Utility::TabularDistribution<Utility::LinLin>(
                   d_forward_epr_data->getPhotonEnergyGrid(),
                   d_forward_epr_data->getImpulseApproxTotalCrossSection() ) );

  // Create the Waller-Hartree incoherent adjoint cross section evaluator
  std::shared_ptr<const MonteCarlo::IncoherentAdjointPhotonScatteringDistribution>
    waller_hartree_incoherent_adjoint_cs_evaluator;

  this->createWallerHartreeIncoherentAdjointCrossSectionEvaluator(
                              waller_hartree_incoherent_adjoint_cs_evaluator );

  // Create the impulse approx. incoherent adjoint cross section evaluators
  Teuchos::Array<std::pair<unsigned,std::shared_ptr<const MonteCarlo::SubshellIncoherentAdjointPhotonScatteringDistribution> > >
    impulse_approx_incoherent_adjoint_cs_evaluators;

  this->createSubshellImpulseApproxIncoherentAdjointCrossSectionEvaluators(
                             impulse_approx_incoherent_adjoint_cs_evaluators );

  // Create the union energy grid
  (*d_os_log) << " Creating union energy grid";
  d_os_log->flush();

  std::list<double> union_energy_grid;

  this->initializeAdjointPhotonUnionEnergyGrid( union_energy_grid );

  // Calculate the union energy grid
  this->updateAdjointPhotonUnionEnergyGrid(
           union_energy_grid, waller_hartree_incoherent_adjoint_cs_evaluator );

  this->updateAdjointPhotonUnionEnergyGrid(
          union_energy_grid, impulse_approx_incoherent_adjoint_cs_evaluators );

  this->updateAdjointPhotonUnionEnergyGrid(
                               union_energy_grid, waller_hartree_coherent_cs );

  this->updateAdjointPhotonUnionEnergyGrid(
                          union_energy_grid, waller_hartree_total_forward_cs );

  this->updateAdjointPhotonUnionEnergyGrid(
                          union_energy_grid, impulse_approx_total_forward_cs );

  (*d_os_log) << "done." << std::endl;

  // Set the union energy grid
  std::vector<double> energy_grid;
  energy_grid.assign( union_energy_grid.begin(),
                      union_energy_grid.end() );

  data_container.setAdjointPhotonEnergyGrid( energy_grid );

  // Create and set the 2-D cross sections
  {
    std::vector<std::vector<double> > max_energy_grid, cross_section;

    (*d_os_log) << " Setting the Waller-Hartree incoherent adjoint "
                << " cross section...";
    d_os_log->flush();
    
    this->createCrossSectionOnUnionEnergyGrid(
                                union_energy_grid,
                                waller_hartree_incoherent_adjoint_cs_evaluator,
                                max_energy_grid,
                                cross_section );

    data_container.setAdjointWallerHartreeIncoherentMaxEnergyGrid(
                                                             max_energy_grid );
    data_container.setAdjointWallerHartreeIncoherentCrossSection(
                                                               cross_section );
    (*d_os_log) << "done." << std::endl;

    for( unsigned i = 0u; i < impulse_approx_incoherent_adjoint_cs_evaluators.size(); ++i )
    {
      (*d_os_log) << " Setting the subshell "
                  << impulse_approx_incoherent_adjoint_cs_evaluators[i].first
                  << " impulse approx incoherent adjoint cross section...";
      d_os_log->flush();

      this->createCrossSectionOnUnionEnergyGrid(
                     union_energy_grid,
                     impulse_approx_incoherent_adjoint_cs_evaluators[i].second,
                     max_energy_grid,
                     cross_section );

      data_container.setAdjointImpulseApproxSubshellIncoherentMaxEnergyGrid(
                      impulse_approx_incoherent_adjoint_cs_evaluators[i].first,
                      max_energy_grid );
      data_container.setAdjointImpulseApproxSubshellIncoherentCrossSection(
                      impulse_approx_incoherent_adjoint_cs_evaluators[i].first,
                      cross_section );

      (*d_os_log) << "done." << std::endl;
    }

    (*d_os_log) << " Setting the impulse approx total incoherent adjoint"
                << " cross section...";
    d_os_log->flush();
    this->calculateAdjointImpulseApproxTotalIncoherentCrossSection(
                                                              data_container );
    (*d_os_log) << "done." << std::endl;
    
  }

  // Create and set the 1-D cross sections
  {
    std::vector<double> cross_section;

    (*d_os_log) << " Setting the Waller-Hartree coherent adjoint "
                << " cross section...";
    d_os_log->flush();

    this->createCrossSectionOnUnionEnergyGrid( union_energy_grid,
                                               waller_hartree_coherent_cs,
                                               cross_section );

    data_container.setAdjointWallerHartreeCoherentCrossSection(cross_section);

    (*d_os_log) << "done." << std::endl;

    (*d_os_log) << " Setting the forward Waller-Hartree total "
                << " cross section...";
    d_os_log->flush();

    this->createCrossSectionOnUnionEnergyGrid( union_energy_grid,
                                               waller_hartree_total_forward_cs,
                                               cross_section );

    data_container.setWallerHartreeTotalCrossSection( cross_section );

    (*d_os_log) << "done." << std::endl;

    (*d_os_log) << " Setting the forward impulse approx. total "
                << " cross section...";
    d_os_log->flush();

    this->createCrossSectionOnUnionEnergyGrid( union_energy_grid,
                                               impulse_approx_total_forward_cs,
                                               cross_section );

    data_container.setImpulseApproxTotalCrossSection( cross_section );

    (*d_os_log) << "done." << std::endl;
  }

  // Set the total adjoint cross sections
  (*d_os_log) << " Setting the adjoint Waller-Hartree total cross section...";
  d_os_log->flush();

  this->calculateAdjointPhotonTotalCrossSection( data_container, true );

  (*d_os_log) << "done." << std::endl;

  (*d_os_log) << " Setting the adjoint impulse approx total cross section...";
  d_os_log->flush();

  this->calculateAdjointPhotonTotalCrossSection( data_container, false );

  (*d_os_log) << "done." << std::endl;

  // Set the adjoint pair production energy distribution
  (*d_os_log) << "Setting the adjoint pair production energy distribution "
              << "data...";
  d_os_log->flush();
    
  this->setAdjointPairProductionEnergyDistribution( data_container );

  (*d_os_log) << "done." << std::endl;

  // Set the adjoint triplet production energy distribution
  (*d_os_log) << "Setting the adjoint triplet production energy distribution "
              << "data...";
  d_os_log->flush();

  this->setAdjointTripletProductionEnergyDistribution( data_container );

  (*d_os_log) << "done." << std::endl;
}

// Set the adjoint pair production energy distributions
void StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointPairProductionEnergyDistribution(
         Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container ) const
{
  // Create the evaluator
  std::shared_ptr<AdjointPairProductionEnergyDistributionNormConstantEvaluator>
    evaluator = AdjointPairProductionEnergyDistributionNormConstantEvaluator::createEvaluator<Utility::LinLin,false>(
     d_forward_epr_data->getPhotonEnergyGrid(),
     d_forward_epr_data->getPairProductionCrossSection(),
     d_forward_epr_data->getPairProductionCrossSectionThresholdEnergyIndex() );

  // Create the evaluation wrapper
  std::function<double(double)> evaluation_wrapper =
    evaluator->getEnergyDistributionNormConstantEvaluationWrapper(
             d_adjoint_pair_production_energy_dist_norm_const_evaluation_tol );

  // Create the energy distribution norm constant grid
  std::vector<double> energy_grid( 2 ), energy_dist_norm_constants;
  energy_grid[0] = 2*Utility::PhysicalConstants::electron_rest_mass_energy;
  energy_grid[1] = this->getMaxPhotonEnergy();

  try{
    this->getDefaultGridGenerator().generateAndEvaluateInPlace(
                                                    energy_grid,
                                                    energy_dist_norm_constants,
                                                    evaluation_wrapper );
  }
  EXCEPTION_CATCH_RETHROW(std::runtime_error,
                          "Error: Could not generate an optimized energy grid "
                          "for the adjoint pair production energy "
                          "distribution norm constants!" );

  // Set the norm constants
  data_container.setAdjointPairProductionEnergyDistributionNormConstantGrid(
                                                                 energy_grid );
  data_container.setAdjointPairProductionEnergyDistributionNormConstant(
                                                  energy_dist_norm_constants );

  // Set the energy distribution
  unsigned threshold_index =
    d_forward_epr_data->getPairProductionCrossSectionThresholdEnergyIndex();

  std::vector<double>::const_iterator start_it =
    d_forward_epr_data->getPhotonEnergyGrid().begin() + threshold_index;

  energy_grid.assign( start_it,
                      d_forward_epr_data->getPhotonEnergyGrid().end() );

  data_container.setAdjointPairProductionEnergyDistributionGrid( energy_grid );
  data_container.setAdjointPairProductionEnergyDistribution(
                         d_forward_epr_data->getPairProductionCrossSection() );
}

// Set the adjoint triplet production energy distribution
void StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointTripletProductionEnergyDistribution(
         Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container ) const
{
  // Create the evaluator
  std::shared_ptr<AdjointPairProductionEnergyDistributionNormConstantEvaluator>
    evaluator = AdjointPairProductionEnergyDistributionNormConstantEvaluator::createEvaluator<Utility::LinLin,false>(
     d_forward_epr_data->getPhotonEnergyGrid(),
     d_forward_epr_data->getTripletProductionCrossSection(),
     d_forward_epr_data->getTripletProductionCrossSectionThresholdEnergyIndex() );

  // Create the evaluation wrapper
  std::function<double(double)> evaluation_wrapper =
    evaluator->getEnergyDistributionNormConstantEvaluationWrapper(
          d_adjoint_triplet_production_energy_dist_norm_const_evaluation_tol );

  // Create the energy distribution norm constant grid
  std::vector<double> energy_grid( 2 ), energy_dist_norm_constants;
  energy_grid[0] = 4*Utility::PhysicalConstants::electron_rest_mass_energy;
  energy_grid[1] = this->getMaxPhotonEnergy();

  try{
    this->getDefaultGridGenerator().generateAndEvaluateInPlace(
                                                    energy_grid,
                                                    energy_dist_norm_constants,
                                                    evaluation_wrapper );
  }
  EXCEPTION_CATCH_RETHROW(std::runtime_error,
                          "Error: Could not generate an optimized energy grid "
                          "for the adjoint triplet production energy "
                          "distribution norm constants!" );

  // Set the norm constants
  data_container.setAdjointTripletProductionEnergyDistributionNormConstantGrid(
                                                                 energy_grid );
  data_container.setAdjointTripletProductionEnergyDistributionNormConstant(
                                                  energy_dist_norm_constants );

  // Set the energy distribution
  unsigned threshold_index =
    d_forward_epr_data->getTripletProductionCrossSectionThresholdEnergyIndex();

  std::vector<double>::const_iterator start_it =
    d_forward_epr_data->getPhotonEnergyGrid().begin() + threshold_index;

  energy_grid.assign( start_it,
                      d_forward_epr_data->getPhotonEnergyGrid().end() );

  data_container.setAdjointTripletProductionEnergyDistributionGrid(
                                                                 energy_grid );
  data_container.setAdjointTripletProductionEnergyDistribution(
                      d_forward_epr_data->getTripletProductionCrossSection() );
}

// Create the Waller-Hartree incoherent adjoint cs evaluator
void StandardAdjointElectronPhotonRelaxationDataGenerator::createWallerHartreeIncoherentAdjointCrossSectionEvaluator(
         std::shared_ptr<const MonteCarlo::IncoherentAdjointPhotonScatteringDistribution>& cs_evaluator ) const
{
  // Create a scattering function
  std::shared_ptr<const Utility::UnitAwareOneDDistribution<Utility::Units::InverseCentimeter,void> > raw_scattering_function(
         new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::InverseCentimeter,void>(
          d_forward_epr_data->getWallerHartreeScatteringFunctionMomentumGrid(),
          d_forward_epr_data->getWallerHartreeScatteringFunction() ) );
    
  std::shared_ptr<const MonteCarlo::ScatteringFunction> scattering_function(
         new MonteCarlo::StandardScatteringFunction<Utility::Units::InverseCentimeter>(
                                                   raw_scattering_function ) );

  // Create the cross section evaluator
  cs_evaluator.reset(
               new MonteCarlo::WHIncoherentAdjointPhotonScatteringDistribution(
                                                    this->getMaxPhotonEnergy(),
                                                    scattering_function ) );
}

// Create the subshell impulse approx incoherent adjoint cs evaluators
void StandardAdjointElectronPhotonRelaxationDataGenerator::createSubshellImpulseApproxIncoherentAdjointCrossSectionEvaluators(
          Teuchos::Array<std::pair<unsigned,std::shared_ptr<const MonteCarlo::SubshellIncoherentAdjointPhotonScatteringDistribution> > >&
          cs_evaluators ) const
{
  // Get the subshells
  const std::set<unsigned>& subshells = d_forward_epr_data->getSubshells();

  std::set<unsigned>::const_iterator subshell_it =
    subshells.begin();

  // Resize the cs_evaluators array
  cs_evaluators.resize( subshells.size() );

  Teuchos::Array<std::pair<unsigned,std::shared_ptr<const MonteCarlo::SubshellIncoherentAdjointPhotonScatteringDistribution> > >::iterator
    cs_evaluators_it = cs_evaluators.begin();
  
  // Extract and set the occupation numbers and grids
  while( subshell_it != subshells.end() )
  {
    cs_evaluators_it->first = *subshell_it;

    this->createSubshellImpulseApproxIncoherentAdjointCrossSectionEvaluator(
                                                    cs_evaluators_it->first,
                                                    cs_evaluators_it->second );
    
    ++subshell_it;
    ++cs_evaluators_it;
  }
}

// Create a subshell impulse approx incoherent adjoint cs evaluator
void StandardAdjointElectronPhotonRelaxationDataGenerator::createSubshellImpulseApproxIncoherentAdjointCrossSectionEvaluator(
         const unsigned subshell,
         std::shared_ptr<const MonteCarlo::SubshellIncoherentAdjointPhotonScatteringDistribution>& cs_evaluator ) const
{
  // Create the occupation number
  std::shared_ptr<Utility::UnitAwareTabularOneDDistribution<Utility::Units::MeCMomentum,void> > raw_occupation_number(
    new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::MeCMomentum,void>(
               d_forward_epr_data->getOccupationNumberMomentumGrid( subshell ),
               d_forward_epr_data->getOccupationNumber( subshell ) ) );

  std::shared_ptr<MonteCarlo::OccupationNumber> occupation_number(
         new MonteCarlo::StandardOccupationNumber<Utility::Units::MeCMomentum>(
                                                     raw_occupation_number ) );

  cs_evaluator.reset(
        new MonteCarlo::SubshellIncoherentAdjointPhotonScatteringDistribution(
                      this->getMaxPhotonEnergy(),
                      Data::convertENDFDesignatorToSubshellEnum( subshell ),
                      d_forward_epr_data->getSubshellOccupancy( subshell ),
                      d_forward_epr_data->getSubshellBindingEnergy( subshell ),
                      occupation_number ) );
}
  
// Initialize the adjoint photon union energy grid
// Note: We will start the with the forward photon energy grid and then
//       eliminate the grid points before the min photon energy and beyond the
//       max photon energy.
void StandardAdjointElectronPhotonRelaxationDataGenerator::initializeAdjointPhotonUnionEnergyGrid(
                                   std::list<double>& union_energy_grid ) const
{
  // Find the location of the first grid point that is >= the min photon energy
  std::vector<double>::const_iterator lower_location_it =
    std::lower_bound( d_forward_epr_data->getPhotonEnergyGrid().begin(),
                      d_forward_epr_data->getPhotonEnergyGrid().end(),
                      this->getMinPhotonEnergy() );

  // Find the location of the first grid point that is >= the max photon energy
  std::vector<double>::const_iterator upper_location_it =
    std::lower_bound( d_forward_epr_data->getPhotonEnergyGrid().begin(),
                      d_forward_epr_data->getPhotonEnergyGrid().end(),
                      this->getMaxPhotonEnergy() );

  // Set the union energy grid
  union_energy_grid.clear();
  union_energy_grid.assign( lower_location_it, upper_location_it );

  // Check if the min photon energy needs to be added
  if( union_energy_grid.front() != this->getMinPhotonEnergy() )
    union_energy_grid.push_front( this->getMinPhotonEnergy() );

  // Check if the last grid point is correct
  if( union_energy_grid.back() != this->getMaxPhotonEnergy() )
    union_energy_grid.push_back( this->getMaxPhotonEnergy() );
}

// Update the adjoint photon union energy grid
void StandardAdjointElectronPhotonRelaxationDataGenerator::updateAdjointPhotonUnionEnergyGrid(
         std::list<double>& union_energy_grid,
         const std::shared_ptr<const MonteCarlo::IncoherentAdjointPhotonScatteringDistribution>& cs_evaluator ) const
{
  // Create an adjoint incoherent grid generator
  AdjointIncoherentGridGenerator<Utility::LinLinLin>
    grid_generator( this->getMaxPhotonEnergy(),
                    d_adjoint_incoherent_max_energy_nudge_value,
                    d_adjoint_incoherent_energy_to_max_energy_nudge_value,
                    d_adjoint_incoherent_grid_convergence_tol,
                    d_adjoint_incoherent_grid_absolute_diff_tol,
                    d_adjoint_incoherent_grid_distance_tol );

  // Throw an exception if dirty convergence occurs
  grid_generator.throwExceptionOnDirtyConvergence();

  std::function<double(double,double)> cs_evaluation_wrapper =
    grid_generator.createCrossSectionEvaluator(
                           cs_evaluator, d_adjoint_incoherent_evaluation_tol );

  try{
    grid_generator.generateInPlace( union_energy_grid, cs_evaluation_wrapper );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "Error: Unable to generate the energy grid for the "
                           "Waller-Hartree incoherent adjoint cross section "
                           "with the provided adjoint incoherent "
                           "tolerances!" );
}

// Update the adjoint photon union energy grid
void StandardAdjointElectronPhotonRelaxationDataGenerator::updateAdjointPhotonUnionEnergyGrid(
         std::list<double>& union_energy_grid,
         const Teuchos::Array<std::pair<unsigned,std::shared_ptr<const MonteCarlo::SubshellIncoherentAdjointPhotonScatteringDistribution> > >&
         cs_evaluators ) const
{
  for( unsigned i = 0u; i < cs_evaluators.size(); ++i )
  {
    Data::SubshellType subshell = Data::convertENDFDesignatorToSubshellEnum(
                                                      cs_evaluators[i].first );

    const std::shared_ptr<const MonteCarlo::SubshellIncoherentAdjointPhotonScatteringDistribution>& cs_evaluator =
      cs_evaluators[i].second;
    
    // Create an adjoint incoherent grid generator
    AdjointIncoherentGridGenerator<Utility::LinLinLin>
      grid_generator( this->getMaxPhotonEnergy(),
                      cs_evaluator->getSubshellBindingEnergy()+
                      d_adjoint_incoherent_max_energy_nudge_value,
                      cs_evaluator->getSubshellBindingEnergy()+
                      d_adjoint_incoherent_energy_to_max_energy_nudge_value,
                      d_adjoint_incoherent_grid_convergence_tol,
                      d_adjoint_incoherent_grid_absolute_diff_tol,
                      d_adjoint_incoherent_grid_distance_tol );

    // Throw an exception if dirty convergence occurs
    grid_generator.throwExceptionOnDirtyConvergence();

    std::function<double(double,double)> cs_evaluation_wrapper =
      grid_generator.createCrossSectionEvaluator(
                           cs_evaluator, d_adjoint_incoherent_evaluation_tol );

    try{
      grid_generator.generateInPlace( union_energy_grid, cs_evaluation_wrapper );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "Error: Unable to generate the energy grid for "
                             "the " << subshell << " subshell impulse approx. "
                             " incoherent adjoint cross section "
                             "with the provided adjoint incoherent "
                             "tolerances!" );
  }
}

// Update the adjoint photon union energy grid
void StandardAdjointElectronPhotonRelaxationDataGenerator::updateAdjointPhotonUnionEnergyGrid(
                        std::list<double>& union_energy_grid,
                        const std::shared_ptr<const Utility::OneDDistribution>&
                        cs_evaluator ) const
{
  // Create a cross section evaluation wrapper
  std::function<double (double)> cs_evaluation_wrapper =
    std::bind<double>( &Utility::OneDDistribution::evaluate,
                       std::cref( *cs_evaluator ),
                       std::placeholders::_1 );
  
  try{
    this->getDefaultGridGenerator().generateInPlace( union_energy_grid,
                                                     cs_evaluation_wrapper );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "Error: Unable to generate the energy grid for the "
                           "1-D photon cross section with the default "
                           "tolerances!" );
}

// Create the cross section on the union energy grid
void StandardAdjointElectronPhotonRelaxationDataGenerator::createCrossSectionOnUnionEnergyGrid(
          const std::list<double>& union_energy_grid,
          const std::shared_ptr<const MonteCarlo::IncoherentAdjointPhotonScatteringDistribution>& cs_evaluator,
          std::vector<std::vector<double> >& max_energy_grid,
          std::vector<std::vector<double> >& cross_section ) const
{
  // Resize the max energy grid and cross section arrays
  max_energy_grid.resize( union_energy_grid.size() );
  cross_section.resize( union_energy_grid.size() );

  // Create a grid generator
  AdjointIncoherentGridGenerator<Utility::LinLinLin>
    grid_generator( this->getMaxPhotonEnergy(),
                    d_adjoint_incoherent_max_energy_nudge_value,
                    d_adjoint_incoherent_energy_to_max_energy_nudge_value,
                    d_adjoint_incoherent_grid_convergence_tol,
                    d_adjoint_incoherent_grid_absolute_diff_tol,
                    d_adjoint_incoherent_grid_distance_tol );

  // Throw an exception if dirty convergence occurs
  grid_generator.throwExceptionOnDirtyConvergence();

  std::function<double(double,double)> cs_evaluation_wrapper =
    grid_generator.createCrossSectionEvaluator(
                           cs_evaluator, d_adjoint_incoherent_evaluation_tol );

  // Evaluate the cross section at every energy grid point
  std::list<double>::const_iterator energy_grid_it =
    union_energy_grid.begin();

  std::vector<std::vector<double> >::iterator max_energy_grid_it =
    max_energy_grid.begin();
  
  std::vector<std::vector<double> >::iterator cross_section_it =
    cross_section.begin();

  while( energy_grid_it != union_energy_grid.end() )
  {
    grid_generator.generateAndEvaluateSecondaryInPlace(*max_energy_grid_it,
                                                       *cross_section_it,
                                                       *energy_grid_it,
                                                       cs_evaluation_wrapper );

    // Check if the first max energy grid point is valid. The energy to
    // max energy nudge value is used to improve convergence time by ignoring
    // the secondary grid point where the cross section is zero
    // (energy = max energy). We must add it back in for the grid to be usable.
    if( max_energy_grid_it->front() > *energy_grid_it )
    {
      // This operation is inefficient with vectors!!!
      max_energy_grid_it->insert( max_energy_grid_it->begin(),
                                  *energy_grid_it );
      cross_section_it->insert( cross_section_it->begin(), 0.0 );
    }
    
    ++energy_grid_it;
    ++max_energy_grid_it;
    ++cross_section_it;
  }
}

// Create the cross section on the union energy grid
void StandardAdjointElectronPhotonRelaxationDataGenerator::createCrossSectionOnUnionEnergyGrid(
          const std::list<double>& union_energy_grid,
          const std::shared_ptr<const MonteCarlo::SubshellIncoherentAdjointPhotonScatteringDistribution>& cs_evaluator,
          std::vector<std::vector<double> >& max_energy_grid,
          std::vector<std::vector<double> >& cross_section ) const
{
  // Resize the max energy grid and cross section arrays
  max_energy_grid.resize( union_energy_grid.size() );
  cross_section.resize( union_energy_grid.size() );

  // Create a grid generator
  AdjointIncoherentGridGenerator<Utility::LinLinLin>
    grid_generator( this->getMaxPhotonEnergy(),
                    cs_evaluator->getSubshellBindingEnergy()+
                    d_adjoint_incoherent_max_energy_nudge_value,
                    cs_evaluator->getSubshellBindingEnergy()+
                    d_adjoint_incoherent_energy_to_max_energy_nudge_value,
                    d_adjoint_incoherent_grid_convergence_tol,
                    d_adjoint_incoherent_grid_absolute_diff_tol,
                    d_adjoint_incoherent_grid_distance_tol );

  // Throw an exception if dirty convergence occurs
  grid_generator.throwExceptionOnDirtyConvergence();

  std::function<double(double,double)> cs_evaluation_wrapper =
    grid_generator.createCrossSectionEvaluator(
                           cs_evaluator, d_adjoint_incoherent_evaluation_tol );

  // Evaluate the cross section at every energy grid point
  std::list<double>::const_iterator energy_grid_it =
    union_energy_grid.begin();

  std::vector<std::vector<double> >::iterator max_energy_grid_it =
    max_energy_grid.begin();
  
  std::vector<std::vector<double> >::iterator cross_section_it =
    cross_section.begin();

  while( energy_grid_it != union_energy_grid.end() )
  {
    grid_generator.generateAndEvaluateSecondaryInPlace(*max_energy_grid_it,
                                                       *cross_section_it,
                                                       *energy_grid_it,
                                                       cs_evaluation_wrapper );

    // Check if the first max energy grid point is valid. The energy to
    // max energy nudge value is used to improve convergence time by ignoring
    // the secondary grid point where the cross section is zero
    // (energy = max energy). We must add it back in for the grid to be usable.
    if( max_energy_grid_it->front() >
        *energy_grid_it + cs_evaluator->getSubshellBindingEnergy() )
    {
      // This operation is inefficient with vectors!!!
      max_energy_grid_it->insert(
                  max_energy_grid_it->begin(),
                  *energy_grid_it + cs_evaluator->getSubshellBindingEnergy() );
      cross_section_it->insert( cross_section_it->begin(), 0.0 );
    }
    
    ++energy_grid_it;
    ++max_energy_grid_it;
    ++cross_section_it;
  }
}

// Create the cross section on the union energy grid
void StandardAdjointElectronPhotonRelaxationDataGenerator::createCrossSectionOnUnionEnergyGrid(
          const std::list<double>& union_energy_grid,
          const std::shared_ptr<const Utility::OneDDistribution>& cs_evaluator,
          std::vector<double>& cross_section ) const
{
  // Resize the cross section array
  cross_section.resize( union_energy_grid.size() );

  // Evaluate the cross section at every energy grid point
  std::list<double>::const_iterator energy_grid_it =
    union_energy_grid.begin();

  std::vector<double>::iterator cross_section_it = cross_section.begin();

  while( energy_grid_it != union_energy_grid.end() )
  {
    *cross_section_it = cs_evaluator->evaluate( *energy_grid_it );

    ++energy_grid_it;
    ++cross_section_it;
  }
}

// Calculate the total incoherent adjoint cross section
void StandardAdjointElectronPhotonRelaxationDataGenerator::calculateAdjointImpulseApproxTotalIncoherentCrossSection(
                    Data::AdjointElectronPhotonRelaxationVolatileDataContainer&
                    data_container ) const
{
  // Get the union energy grid
  const std::vector<double>& energy_grid =
    data_container.getAdjointPhotonEnergyGrid();

  // Initialize the max energy grid
  std::vector<std::vector<double> > max_energy_grid( energy_grid.size() );
  std::vector<std::vector<double> > cross_section( energy_grid.size() );

  // The max_energy_grid at an energy
  std::list<double> local_max_energy_grid;

  // Get the subshells
  const std::set<unsigned>& subshells = data_container.getSubshells();

  // Generate the max energy grid at each energy grid point
  for( unsigned i = 0u; i < energy_grid.size(); ++i )
  {
    local_max_energy_grid.clear();
    
    std::set<unsigned>::const_iterator subshell = subshells.begin();

    while( subshell != subshells.end() )
    {
      local_max_energy_grid.insert(
        local_max_energy_grid.end(),
        data_container.getAdjointImpulseApproxSubshellIncoherentMaxEnergyGrid( *subshell )[i].begin(),
        data_container.getAdjointImpulseApproxSubshellIncoherentMaxEnergyGrid( *subshell )[i].end() );
      
      ++subshell;
    }

    // Sort the local max energy grid
    local_max_energy_grid.sort();

    // Remove duplicate grid points from the local max energy grid
    local_max_energy_grid.unique();

    // Assigne the max energy grid at this energy
    max_energy_grid[i].assign( local_max_energy_grid.begin(),
                               local_max_energy_grid.end() );
    cross_section[i].resize( max_energy_grid[i].size(), 0 );

    // Evaluate the cross section on the max energy grid at this energy
    subshell = subshells.begin();

    while( subshell != subshells.end() )
    {
      Utility::TabularDistribution<Utility::LinLin> subshell_cs(
        data_container.getAdjointImpulseApproxSubshellIncoherentMaxEnergyGrid( *subshell )[i],
        data_container.getAdjointImpulseApproxSubshellIncoherentCrossSection( *subshell )[i] );

      for( unsigned j = 0u; j < max_energy_grid[i].size(); ++j )
        cross_section[i][j] += subshell_cs.evaluate( max_energy_grid[i][j] );
      
      ++subshell;
    }
  }

  // Set the adjoint impulse approx total incoherent cross section
  data_container.setAdjointImpulseApproxIncoherentMaxEnergyGrid(
                                                             max_energy_grid );
  data_container.setAdjointImpulseApproxIncoherentCrossSection(cross_section );
}

// Calculate the adjoint photon total cross section
void StandardAdjointElectronPhotonRelaxationDataGenerator::calculateAdjointPhotonTotalCrossSection(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container,
    const bool use_waller_hartree_adjoint_incoherent_cs ) const
{
  // Get the adjoint photon energy grid
  const std::vector<double>& energy_grid =
    data_container.getAdjointPhotonEnergyGrid();

  // Get the coherent cross section
  const std::vector<double>& coherent_cs =
    data_container.getAdjointWallerHartreeCoherentCrossSection();

  // Get the max energy grid and initialize the cross section
  std::vector<std::vector<double> > max_energy_grid;
  std::vector<std::vector<double> > total_cross_section;
  
  if( use_waller_hartree_adjoint_incoherent_cs )
  {
    max_energy_grid =
      data_container.getAdjointWallerHartreeIncoherentMaxEnergyGrid();

    total_cross_section =
      data_container.getAdjointWallerHartreeIncoherentCrossSection();
  }
  else
  {
    max_energy_grid =
      data_container.getAdjointImpulseApproxIncoherentMaxEnergyGrid();

    total_cross_section =
      data_container.getAdjointImpulseApproxIncoherentCrossSection();
  }

  // Add the coherent cross section to the total
  for( unsigned i = 0u; i < energy_grid.size(); ++i )
  {
    for( unsigned j = 0u; j < max_energy_grid[i].size(); ++j )
      total_cross_section[i][j] += coherent_cs[i];
  }

  // Set the total cross section
  if( use_waller_hartree_adjoint_incoherent_cs )
  {
    data_container.setAdjointWallerHartreeTotalMaxEnergyGrid(max_energy_grid );
    data_container.setAdjointWallerHartreeTotalCrossSection(
                                                         total_cross_section );
  }
  else
  {
    data_container.setAdjointImpulseApproxTotalMaxEnergyGrid(max_energy_grid );
    data_container.setAdjointImpulseApproxTotalCrossSection(
                                                         total_cross_section );
  }
}

// Evaluate the total cross section at an energy and max energy
double StandardAdjointElectronPhotonRelaxationDataGenerator::evaluateAdjointPhotonTotalCrossSection(
          const std::vector<std::shared_ptr<const Utility::OneDDistribution> >&
          cross_sections,
          const double max_energy ) const
{

}

// Set the adjoint electron data
void StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointElectronData(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container ) const
{
//---------------------------------------------------------------------------//
// Set Electron Cross Section Data Data
//---------------------------------------------------------------------------//

  std::cout << " Setting the adjoint electron cross section data:" << std::endl;
  std::cout.flush();

  // Extract the common electron energy grid
  Teuchos::ArrayRCP<double> forward_electron_energy_grid;
  forward_electron_energy_grid.assign(
    d_forward_epr_data->getElectronEnergyGrid().begin(),
    d_forward_epr_data->getElectronEnergyGrid().end() );

  Teuchos::RCP<Utility::HashBasedGridSearcher> forward_grid_searcher(
      new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>,false>(
                forward_electron_energy_grid,
                forward_electron_energy_grid[0],
                forward_electron_energy_grid[forward_electron_energy_grid.size()-1],
                forward_electron_energy_grid.size()/10 + 1 ) );

  //---------------------------------------------------------------------------//
  // Create union energy grid and calculate cross sections
  //---------------------------------------------------------------------------//

  // Create the union energy grid
  std::cout << "   Creating union energy grid";
  std::cout.flush();
  std::list<double> union_energy_grid;

  this->initializeAdjointElectronUnionEnergyGrid(
          data_container,
          union_energy_grid );

  Utility::GridGenerator<Utility::LinLin>
  union_energy_grid_generator( d_adjoint_electron_grid_convergence_tol,
                               d_adjoint_electron_absolute_diff_tol,
                               d_adjoint_electron_distance_tol );

  // Calculate the union energy grid


  //---------------------------------------------------------------------------//
  // Generate Grid Points For The Elastic Cross Section Data
  //---------------------------------------------------------------------------//
  // Extract the cutoff elastic cross section data
  Teuchos::ArrayRCP<double> forward_cutoff_elastic_cs;
  forward_cutoff_elastic_cs.assign(
    d_forward_epr_data->getCutoffElasticCrossSection().begin(),
    d_forward_epr_data->getCutoffElasticCrossSection().end() );

  // Create the reaction
  std::shared_ptr<MonteCarlo::ElectroatomicReaction> cutoff_elastic_reaction(
    new MonteCarlo::VoidStandardElectroatomicReaction<Utility::LinLin>(
        forward_electron_energy_grid,
        forward_cutoff_elastic_cs,
        d_forward_epr_data->getCutoffElasticCrossSectionThresholdEnergyIndex(),
        forward_grid_searcher ) );

  // Bind the reaction
  boost::function<double (double pz)> cutoff_elastic_grid_function =
    boost::bind( &MonteCarlo::ElectroatomicReaction::getCrossSection,
                 boost::cref( *cutoff_elastic_reaction ),
                 _1 );

  // Generate cutoff elastic
  union_energy_grid_generator.generateInPlace( union_energy_grid,
                                               cutoff_elastic_grid_function );

  std::cout << ".";
  std::cout.flush();

  // Extract the total elastic cross section data
  Teuchos::ArrayRCP<double> forward_total_elastic_cs;
  forward_total_elastic_cs.assign(
    d_forward_epr_data->getTotalElasticCrossSection().begin(),
    d_forward_epr_data->getTotalElasticCrossSection().end() );

  // Create the reaction
  std::shared_ptr<MonteCarlo::ElectroatomicReaction> total_elastic_reaction(
    new MonteCarlo::VoidStandardElectroatomicReaction<Utility::LinLin>(
        forward_electron_energy_grid,
        forward_total_elastic_cs,
        d_forward_epr_data->getTotalElasticCrossSectionThresholdEnergyIndex(),
        forward_grid_searcher ) );

  // Bind the reaction
  boost::function<double (double pz)> total_elastic_grid_function =
    boost::bind( &MonteCarlo::ElectroatomicReaction::getCrossSection,
                 boost::cref( *total_elastic_reaction ),
                 _1 );


  // Generate total elastic
  union_energy_grid_generator.generateInPlace( union_energy_grid,
                                               total_elastic_grid_function );

  std::cout << ".";
  std::cout.flush();

  //---------------------------------------------------------------------------//
  // Generate Grid Points For The Adjoint Atomic Excitation Cross Section Data
  //---------------------------------------------------------------------------//

  // Create the cross section distribution
  std::shared_ptr<const Utility::OneDDistribution> adjoint_excitation_cross_section;
  this->createAdjointAtomicExcitationCrossSectionDistribution(
          data_container,
          forward_electron_energy_grid,
          forward_grid_searcher,
          adjoint_excitation_cross_section );

  // Bind the distribution
  boost::function<double (double pz)> atomic_excitation_grid_function =
    boost::bind( &Utility::OneDDistribution::evaluate,
  		                   boost::cref( *adjoint_excitation_cross_section ),
  		                   _1 );

  // Generate atomic excitation (don't generate new grid points above the last grid point)
  union_energy_grid_generator.refineInPlace( 
    union_energy_grid,
    atomic_excitation_grid_function,
    this->getMinElectronEnergy(),
    data_container.getAdjointAtomicExcitationEnergyGrid().back() );

  std::cout << ".";
  std::cout.flush();


  //---------------------------------------------------------------------------//
  // Generate Grid Points For The Adjoint Bremsstrahlung Cross Section Data
  //---------------------------------------------------------------------------//
  // Create he adjoint bremsstrahlung cross section evaluator
  std::shared_ptr<BremsstrahlungEvaluator >
    adjoint_bremsstrahlung_cs_evaluator;

  // Bind the function
  boost::function<double (double)> bremsstrahlung_grid_function;
  this->createAdjointBremsstrahlungCrossSectionEvaluator(
          forward_electron_energy_grid,
          forward_grid_searcher,
          adjoint_bremsstrahlung_cs_evaluator,  
          bremsstrahlung_grid_function );

  // Temporarily save cross section values so they don't have to be generated again
  std::vector<double> old_adjoint_bremsstrahlung_cs;

  // Generate bremsstrahlung (temporarily keep this grid and evaluated function)
  union_energy_grid_generator.generateAndEvaluateInPlace(
    union_energy_grid,
    old_adjoint_bremsstrahlung_cs,
    bremsstrahlung_grid_function );

  std::list<double> old_adjoint_bremsstrahlung_union_energy_grid(
    union_energy_grid );

  std::cout << ".";
  std::cout.flush();

  //---------------------------------------------------------------------------//
  // Generate Grid Points For The Adjoint Electroionization Subshell Cross Section Data
  //---------------------------------------------------------------------------//
  // Create the adjoint electroionization subshell cross section evaluator
  std::map<unsigned,std::shared_ptr<ElectroionizationEvaluator> >
    adjoint_electroionization_cs_evaluators;
  std::map<unsigned,boost::function<double (double)> >
    ionization_grid_functions;

  // Temporarily save cross section values so they don't have to be generated again
  std::map<unsigned,std::list<double> > old_adjoint_electroionization_union_energy_grid;
  std::map<unsigned,std::vector<double> > old_adjoint_electroionization_cs;

  std::set<unsigned>::iterator shell = data_container.getSubshells().begin();

  // Loop through electroionization evaluator for every subshell
  for ( shell; shell != data_container.getSubshells().end(); shell++ )
  {
    // Create the evaluator and boost function for the subshell
    this->createAdjointElectroionizationSubshellCrossSectionEvaluator(
      forward_electron_energy_grid,
      forward_grid_searcher,
      adjoint_electroionization_cs_evaluators[*shell],
      ionization_grid_functions[*shell],
      *shell );

    // Generate electroionization (temporarily keep this grid and evaluated function)
    union_energy_grid_generator.generateAndEvaluateInPlace(
      union_energy_grid,
      old_adjoint_electroionization_cs[*shell],
      ionization_grid_functions[*shell] );

    old_adjoint_electroionization_union_energy_grid[*shell] =
      union_energy_grid;

    std::cout << ".";
    std::cout.flush();
  }

  std::cout << "done." << std::endl;

  // Set the union energy grid
  std::vector<double> energy_grid(
        union_energy_grid.begin(),
        union_energy_grid.end() );

  data_container.setAdjointElectronEnergyGrid( energy_grid );

  // Create and set the cross sections
  std::vector<double> cross_section;
  unsigned threshold;

  // Set the adjoint elastic cross section data
  std::cout << "   Setting the adjoint total elastic cross section...";
  std::cout.flush();
  std::vector<double> total_cross_section;
  this->createCrossSectionOnUnionEnergyGrid(
      union_energy_grid,
      total_elastic_grid_function,
      total_cross_section,
      threshold );
  data_container.setAdjointTotalElasticCrossSection( total_cross_section );
  data_container.setAdjointTotalElasticCrossSectionThresholdEnergyIndex( threshold );
  std::cout << "done." << std::endl;

  std::cout << "   Setting the adjoint cutoff elastic cross section...";
  std::cout.flush();
  std::vector<double> cutoff_cross_section;
  this->createCrossSectionOnUnionEnergyGrid(
      union_energy_grid,
      cutoff_elastic_grid_function,
      cutoff_cross_section,
      threshold );
  data_container.setAdjointCutoffElasticCrossSection( cutoff_cross_section );
  data_container.setAdjointCutoffElasticCrossSectionThresholdEnergyIndex( threshold );
  std::cout << "done." << std::endl;


  std::cout << "   Setting the screened Rutherford elastic cross section...";
  std::cout.flush();
  {
  std::vector<double> raw_cross_section( total_cross_section.size() );
  for ( int i = 0; i < total_cross_section.size(); ++i )
  {
      raw_cross_section.at(i) = total_cross_section.at(i) - cutoff_cross_section.at(i);

      double relative_difference = raw_cross_section.at(i)/total_cross_section.at(i);

      // Check for roundoff error and reduce to zero if needed
      if ( relative_difference < 1.0e-16 )
      {
          raw_cross_section[i] = 0.0;

          // Update threshold index
          threshold = i+1;
      }
  }

  std::vector<double>::iterator start = raw_cross_section.begin();
  std::advance( start, threshold );

  cross_section.assign( start, raw_cross_section.end() );

  data_container.setAdjointScreenedRutherfordElasticCrossSection( cross_section );
  data_container.setAdjointScreenedRutherfordElasticCrossSectionThresholdEnergyIndex(
  threshold );
  }
  std::cout << "done." << std::endl;

  if( d_forward_epr_data->hasMomentPreservingData() )
  {
    std::cout << "   Setting the adjoint moment preserving elastic cross section...";
    std::cout.flush();

    // Extract the moment preserving elastic cross section data
    Teuchos::ArrayRCP<double> forward_moment_preserving_elastic_cs;
    forward_moment_preserving_elastic_cs.assign(
      d_forward_epr_data->getMomentPreservingCrossSection().begin(),
      d_forward_epr_data->getMomentPreservingCrossSection().end() );

    std::shared_ptr<MonteCarlo::ElectroatomicReaction> moment_preserving_elastic_reaction(
      new MonteCarlo::VoidStandardElectroatomicReaction<Utility::LinLin>(
          forward_electron_energy_grid,
          forward_moment_preserving_elastic_cs,
          d_forward_epr_data->getMomentPreservingCrossSectionThresholdEnergyIndex(),
          forward_grid_searcher ) );

    boost::function<double (double pz)> moment_preserving_elastic_grid_function =
      boost::bind( &MonteCarlo::ElectroatomicReaction::getCrossSection,
                   boost::cref( *moment_preserving_elastic_reaction ),
                   _1 );

    std::vector<double> moment_preserving_cross_section;
    this->createCrossSectionOnUnionEnergyGrid(
        union_energy_grid,
        moment_preserving_elastic_grid_function,
        moment_preserving_cross_section,
        threshold );
    data_container.setAdjointMomentPreservingCrossSection( moment_preserving_cross_section );
    data_container.setAdjointMomentPreservingCrossSectionThresholdEnergyIndex( threshold );
    std::cout << "done." << std::endl;
  }

  // Set the adjoint atomic excitation cross section data
  std::cout << "   Setting the adjoint atomic excitation cross section...";
  std::cout.flush();
  std::vector<double> excitation_cross_section;
  this->createCrossSectionOnUnionEnergyGrid(
      union_energy_grid,
      atomic_excitation_grid_function,
      excitation_cross_section,
      threshold );

  data_container.setAdjointAtomicExcitationCrossSection( excitation_cross_section );
  data_container.setAdjointAtomicExcitationCrossSectionThresholdEnergyIndex( threshold );
  std::cout << "done." << std::endl;

  // Set the adjoint bremsstrahlung cross section data
  std::cout << "   Setting the adjoint bremsstrahlung cross section...";
  std::cout.flush();
  std::vector<double> bremsstrahlung_cross_section;
  unsigned bremsstrahlung_threshold_index;
  this->updateCrossSectionOnUnionEnergyGrid(
      union_energy_grid,
      old_adjoint_bremsstrahlung_union_energy_grid,
      old_adjoint_bremsstrahlung_cs,  
      bremsstrahlung_grid_function,
      bremsstrahlung_cross_section,
      bremsstrahlung_threshold_index );

  data_container.setAdjointBremsstrahlungElectronCrossSection( bremsstrahlung_cross_section );
  data_container.setAdjointBremsstrahlungElectronCrossSectionThresholdEnergyIndex( bremsstrahlung_threshold_index );
  std::cout << "done." << std::endl;

  // Set the adjoint electroionization subshell cross section data
  std::cout << "   Setting the adjoint electroionization subshell cross section...";
  std::cout.flush();

  std::map<unsigned,std::vector<double> > ionization_cross_sections;
  std::map<unsigned,unsigned > ionization_cross_section_thresholds;

  // Loop through the electroionization subshells
  shell = data_container.getSubshells().begin();
  for ( shell; shell != data_container.getSubshells().end(); shell++ )
  {
    this->updateCrossSectionOnUnionEnergyGrid(
        union_energy_grid,
        old_adjoint_electroionization_union_energy_grid[*shell],
        old_adjoint_electroionization_cs[*shell],  
        ionization_grid_functions[*shell],
        ionization_cross_sections[*shell],
        ionization_cross_section_thresholds[*shell] );

    data_container.setAdjointElectroionizationCrossSection(
      *shell,
      ionization_cross_sections[*shell] );

    data_container.setAdjointElectroionizationCrossSectionThresholdEnergyIndex(
      *shell,
      ionization_cross_section_thresholds[*shell] );
  }
  std::cout << "done." << std::endl;

//---------------------------------------------------------------------------//
// Set Elastic Data
//---------------------------------------------------------------------------//
  std::cout << " Setting the adjoint elastic cutoff data...";
  std::cout.flush();

  // Set elastic angular distribution
  data_container.setAdjointElasticAngularEnergyGrid(
        d_forward_epr_data->getElasticAngularEnergyGrid() );

  data_container.setAdjointCutoffElasticAngles(
        d_forward_epr_data->getCutoffElasticAngles() );

  data_container.setAdjointCutoffElasticPDF(
        d_forward_epr_data->getCutoffElasticPDF() );

  std::cout << "done." << std::endl;

  std::cout << " Setting the adjoint elastic moment preserving data...";
  std::cout.flush();

  data_container.setAdjointMomentPreservingElasticDiscreteAngles(
        d_forward_epr_data->getMomentPreservingElasticDiscreteAngles() );

  data_container.setAdjointMomentPreservingElasticWeights(
        d_forward_epr_data->getMomentPreservingElasticWeights() );

  std::cout << "done." << std::endl;

//---------------------------------------------------------------------------//
// Set Bremsstrahlung Data
//---------------------------------------------------------------------------//
  std::cout << " Setting the bremsstrahlung data...";
  std::cout.flush();
  {
  std::shared_ptr<DataGen::AdjointElectronDistributionGenerator<Utility::LinLinLin> >
      distribution_grid_generator;

  /* The energy to outgoing energy nudge value for the should be set slighty
   * higher for the distribution_grid_generator than for the bremsstrahlung
   * cross section evaluator. This will ensure that there are no pdf values of
   * zero in the distribution.
   */
  distribution_grid_generator.reset(
    new AdjointElectronDistributionGenerator<Utility::LinLinLin>(
          this->getMaxElectronEnergy(),
          d_adjoint_bremsstrahlung_max_energy_nudge_value,
          2.0*d_adjoint_bremsstrahlung_energy_to_outgoing_energy_nudge_value,
          d_adjoint_bremsstrahlung_grid_convergence_tol,
          d_adjoint_bremsstrahlung_absolute_diff_tol,
          d_adjoint_bremsstrahlung_distance_tol ) );

  std::vector<double> brem_energy_grid, brem_pdf;

  for ( unsigned i = 0; i < energy_grid.size(); ++i )
  {
    unsigned energy_index = i + bremsstrahlung_threshold_index;

    distribution_grid_generator->generateAndEvaluateDistributionInPlace<BremsstrahlungReaction>(
      brem_energy_grid,
      brem_pdf,
      adjoint_bremsstrahlung_cs_evaluator,
      d_adjoint_bremsstrahlung_evaluation_tol,
      energy_grid[energy_index],
      bremsstrahlung_cross_section[i] );

    // Set the adjoint bremsstrahlung scattering distribution
    data_container.setAdjointElectronBremsstrahlungEnergyAtIncomingEnergy(
      energy_grid[energy_index],
      brem_energy_grid );

    data_container.setAdjointElectronBremsstrahlungPDFAtIncomingEnergy(
      energy_grid[energy_index],
      brem_pdf );

    // Clear the data
    brem_energy_grid.clear();
    brem_pdf.clear();
  }
  }
  std::cout << "done." << std::endl;

//---------------------------------------------------------------------------//
// Set Electroionization Data
//---------------------------------------------------------------------------//
  std::cout << " Setting the electroionization data...";
  std::cout.flush();
  {
  shell = data_container.getSubshells().begin();

  // Loop through electroionization data for every subshell
  for ( shell; shell != data_container.getSubshells().end(); shell++ )
  {
    std::shared_ptr<DataGen::AdjointElectronDistributionGenerator<Utility::LinLinLin> >
        distribution_grid_generator;

    double binding_energy =
      data_container.getSubshellBindingEnergy( *shell );

    /* The energy to outgoing energy nudge value for the should be set slighty
     * higher for the distribution_grid_generator than for the electroionization
     * cross section evaluator. This will ensure that there are no pdf values of
     * zero in the distribution.
     */
    distribution_grid_generator.reset(
      new AdjointElectronDistributionGenerator<Utility::LinLinLin>(
            this->getMaxElectronEnergy(),
            binding_energy*2.0,
            binding_energy + 5e-7,
            d_adjoint_electroionization_grid_convergence_tol,
            d_adjoint_electroionization_absolute_diff_tol,
            d_adjoint_electroionization_distance_tol ) );

    std::vector<double> ionization_energy_grid, ionization_pdf;

    for ( unsigned i = 0; i < energy_grid.size(); ++i )
    {
      unsigned energy_index = i + ionization_cross_section_thresholds[*shell];

      distribution_grid_generator->generateAndEvaluateDistributionInPlace<ElectroionizationReaction>(
        ionization_energy_grid,
        ionization_pdf,
        adjoint_electroionization_cs_evaluators.find( *shell )->second,
        d_adjoint_electroionization_evaluation_tol,
        energy_grid[energy_index],
        ionization_cross_sections.find(*shell)->second[i] );

      // Set the adjoint bremsstrahlung scattering distribution
      data_container.setAdjointElectroionizationRecoilEnergyAtIncomingEnergy(
        *shell,
        energy_grid[energy_index],
        ionization_energy_grid );

      data_container.setAdjointElectroionizationRecoilPDFAtIncomingEnergy(
        *shell,
        energy_grid[energy_index],
        ionization_pdf );

      // Clear the data
      ionization_energy_grid.clear();
      ionization_pdf.clear();
    }
  }
  }
  std::cout << "done." << std::endl;
}

// Create the adjoint atomic excitation cross section reaction
void StandardAdjointElectronPhotonRelaxationDataGenerator::createAdjointAtomicExcitationCrossSectionDistribution(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container,
    const Teuchos::ArrayRCP<const double>& forward_electron_energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& forward_grid_searcher,
    std::shared_ptr<const Utility::OneDDistribution>&
      adjoint_excitation_cross_section_distribution ) const
{
  // Extract the total elastic cross section data
  Teuchos::ArrayRCP<double> atomic_excitation_cross_section;
  atomic_excitation_cross_section.assign(
    d_forward_epr_data->getAtomicExcitationCrossSection().begin(),
    d_forward_epr_data->getAtomicExcitationCrossSection().end() );

  std::shared_ptr<MonteCarlo::ElectroatomicReaction> atomic_excitation_reaction(
    new MonteCarlo::VoidStandardElectroatomicReaction<Utility::LinLin>(
        forward_electron_energy_grid,
        atomic_excitation_cross_section,
        d_forward_epr_data->getAtomicExcitationCrossSectionThresholdEnergyIndex(),
        forward_grid_searcher ) );

  // Find the upper and lower boundary bins for the min and max energy
  std::vector<double>::const_iterator energy_grid_start, energy_grid_end;
  this->findLowerAndUpperBinBoundary(
          this->getMinElectronEnergy(),
          this->getMaxElectronEnergy(),
          d_forward_epr_data->getAtomicExcitationEnergyGrid(),
          energy_grid_start,
          energy_grid_end );
  ++energy_grid_end;

  // Get the index of the energy_grid_start
  unsigned start_index = std::distance(
    d_forward_epr_data->getAtomicExcitationEnergyGrid().begin(),
    energy_grid_start );

  std::vector<double>::const_iterator energy_gain_start =
    d_forward_epr_data->getAtomicExcitationEnergyLoss().begin();

  // Advance the energy_gain_start to the same index as the energy_grid_start
  std::advance( energy_gain_start, start_index );

  // Make sure the first adjoint energy grid point is above the min electron energy
  while ( *energy_grid_start - *energy_gain_start < this->getMinElectronEnergy()  )
  {
    ++energy_grid_start;
    ++energy_gain_start;
  }

  // Include the energy right below the min electron energy for interpolation purposes 
  --energy_grid_start;
  --energy_gain_start;

  // Get the index of the energy_grid_start
  unsigned end_index = std::distance(
    d_forward_epr_data->getAtomicExcitationEnergyGrid().begin(),
    energy_grid_end );

  std::vector<double>::const_iterator energy_gain_end =
    d_forward_epr_data->getAtomicExcitationEnergyLoss().begin();

  // Advance the energy_gain_end to the same index as the energy_grid_end
  std::advance( energy_gain_end, end_index ); 

  std::vector<double> adjoint_excitation_energy_gain(
    energy_gain_start,
    energy_gain_end );

  std::vector<double> adjoint_excitation_energy_grid(
    energy_grid_start,
    energy_grid_end );

  std::vector<double> adjoint_excitation_cross_section(
    adjoint_excitation_energy_gain.size() );

  // Calcualte the adjoint icoming energy grid from the forward incoming energy grid and energy loss
  for ( int i = 0; i < adjoint_excitation_energy_grid.size(); i++ )
  {
    // Evaluate the cross section at the forward energy
    adjoint_excitation_cross_section[i] =
      atomic_excitation_reaction->getCrossSection( adjoint_excitation_energy_grid[i] );

    // Calculate the adjoint energy grid point at the forward energy
    adjoint_excitation_energy_grid[i] -= adjoint_excitation_energy_gain[i];
  }

  // Set atomic excitation energy grid (adjoint energy grid = forward energy grid - forward energy loss)
  data_container.setAdjointAtomicExcitationEnergyGrid(
    adjoint_excitation_energy_grid );

  // Set atomic excitation energy gain (adjoint energy gain = forward energy loss)
  data_container.setAdjointAtomicExcitationEnergyGain(
    adjoint_excitation_energy_gain );

  adjoint_excitation_cross_section_distribution.reset(
    new Utility::TabularDistribution<Utility::LinLin>(
      adjoint_excitation_energy_grid,
      adjoint_excitation_cross_section ) );
}

// Create the adjoint bremsstrahlung cross section evaluator
    /*! \details This function uses the bremsstrahlung reaction and the primary
     * (incoming) energy grid of the pdf distribution to construct the adjoint
     * cross section evaluator. 
     */
void StandardAdjointElectronPhotonRelaxationDataGenerator::createAdjointBremsstrahlungCrossSectionEvaluator(
    const Teuchos::ArrayRCP<const double>& forward_electron_energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& forward_grid_searcher,
    std::shared_ptr<BremsstrahlungEvaluator >&
        adjoint_bremsstrahlung_cs_evaluator,
    boost::function<double (double)>& bremsstrahlung_grid_function ) const
{
  std::shared_ptr<BremsstrahlungReaction> bremsstrahlung_reaction;

  MonteCarlo::ElectroatomicReactionNativeFactory::createBremsstrahlungReaction(
    *d_forward_epr_data,
    forward_electron_energy_grid,
    forward_grid_searcher,
    bremsstrahlung_reaction,
    MonteCarlo::DIPOLE_DISTRIBUTION );

  adjoint_bremsstrahlung_cs_evaluator.reset(
    new BremsstrahlungEvaluator(
        bremsstrahlung_reaction,
        d_forward_epr_data->getBremsstrahlungEnergyGrid(),
        this->getMinElectronEnergy(),
        this->getMaxElectronEnergy(),
        d_adjoint_bremsstrahlung_max_energy_nudge_value,
        d_adjoint_bremsstrahlung_energy_to_outgoing_energy_nudge_value ) );

  // Bind the function
  bremsstrahlung_grid_function =  boost::bind(
    (double(BremsstrahlungEvaluator::*)(double,double) const)&BremsstrahlungEvaluator::evaluateAdjointCrossSection,
    boost::cref( *adjoint_bremsstrahlung_cs_evaluator ),
    _1,
    d_adjoint_bremsstrahlung_evaluation_tol );

}

// Generate adjoint bremsstrahlung photon energy distribution
void StandardAdjointElectronPhotonRelaxationDataGenerator::evaluateAdjointBremsstrahlungPhotonDistribution(
    const double incoming_adjoint_energy,
    const unsigned bin_index,
    const unsigned threshold_energy_index,
    const Teuchos::ArrayRCP<const double>& adjoint_cross_section,
    const Teuchos::ArrayRCP<const double>& adjoint_electron_energy_grid,
    const std::shared_ptr<BremsstrahlungEvaluator >
        adjoint_bremsstrahlung_cs_evaluator,
    const std::vector<double>& adjoint_bremsstrahlung_photon_energy,
    std::vector<double>& adjoint_bremsstrahlung_pdf ) const
{
  // double adjoint_bremsstrahlung_cs =
  //   MonteCarlo::StandardElectroatomicReaction<Utility::LinLin, false>::getCrossSection(
  //       incoming_adjoint_energy,
  //       bin_index,
  //       adjoint_cross_section,
  //       adjoint_electron_energy_grid,
  //       threshold_energy_index );

  // adjoint_bremsstrahlung_pdf.resize(
  //   adjoint_bremsstrahlung_photon_energy.size() );

  // // Calculate the adjoint PDF values at the given incoming adjoint energy
  // for ( int j = 0; j < adjoint_bremsstrahlung_photon_energy.size(); ++j )
  // {
  //   double outgoing_adjoint_energy =
  //     incoming_adjoint_energy + adjoint_bremsstrahlung_photon_energy[j];

  //   if ( outgoing_adjoint_energy <= this->getMaxElectronEnergy() )
  //   {
  //     adjoint_bremsstrahlung_pdf[j] =
  //         adjoint_bremsstrahlung_cs_evaluator->evaluateAdjointPDF(
  //           adjoint_bremsstrahlung_cs,
  //           incoming_adjoint_energy,
  //           outgoing_adjoint_energy,
  //           d_adjoint_bremsstrahlung_evaluation_tol );
  //   }
  //   else
  //     adjoint_bremsstrahlung_pdf[j] = 0.0;
  // }
}

// Create the adjoint electroionization subshell cross section evaluator
    /*! \details This function uses the electroionization subshell reaction
     * and the primary (incoming) energy grids of the pdf subshell distributions
     * to construct the adjoint cross section evaluator and boost function. 
     */
void StandardAdjointElectronPhotonRelaxationDataGenerator::createAdjointElectroionizationSubshellCrossSectionEvaluator(
    const Teuchos::ArrayRCP<const double>& forward_electron_energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& forward_grid_searcher,
    std::shared_ptr<ElectroionizationEvaluator>&
        adjoint_electroionization_cs_evaluator,
    boost::function<double (double)>& ionization_grid_function,
    const unsigned shell ) const
{
  // Create the subshell reaction
  std::shared_ptr<ElectroionizationReaction>
    electroionization_subshell_reaction;

  MonteCarlo::ElectroatomicReactionNativeFactory::createSubshellElectroionizationReaction(
    *d_forward_epr_data,
    forward_electron_energy_grid,
    forward_grid_searcher,
    shell,
    electroionization_subshell_reaction );

  /* The max energy nudge value should be greater than the binding energy (a
    * factor of two is used to help with convergence). The energy to outgoing
    * energy nudge value should be equal to or greater than the binding energy,
    * by adding a factor of 1e-7 to the binding energy the integrated cross
    * section assumes all knock-on electrons with an energy < 1e-7 have a pdf
    * and cross section value of zero.
    */
  adjoint_electroionization_cs_evaluator.reset(
    new ElectroionizationEvaluator(
        electroionization_subshell_reaction,
        d_forward_epr_data->getElectroionizationEnergyGrid( shell),
        this->getMinElectronEnergy(),
        this->getMaxElectronEnergy(),
        2.00 * d_forward_epr_data->getSubshellBindingEnergy( shell ),
        1e-7 + d_forward_epr_data->getSubshellBindingEnergy( shell ) ) );

  ionization_grid_function = boost::bind(
    (double(ElectroionizationEvaluator::*)(double,double) const)&ElectroionizationEvaluator::evaluateAdjointCrossSection,
    boost::cref( *adjoint_electroionization_cs_evaluator ),
    _1,
    d_adjoint_bremsstrahlung_evaluation_tol );
}

// Initialize the electron union energy grid
void StandardAdjointElectronPhotonRelaxationDataGenerator::initializeAdjointElectronUnionEnergyGrid(
     const Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container,
     std::list<double>& union_energy_grid ) const
{
  // Add the min electron energy to the union energy grid
  union_energy_grid.push_back( this->getMinElectronEnergy() );

  const std::set<unsigned>& subshells = data_container.getSubshells();

  std::set<unsigned>::const_iterator subshell = subshells.begin();

  // Add the subshell binding energies
  while( subshell != subshells.end() )
  {
    double binding_energy =
      data_container.getSubshellBindingEnergy( *subshell );

      union_energy_grid.push_back(
        this->getMaxElectronEnergy() - binding_energy - 1e-7 );

    ++subshell;
  }

  // Add the max electron energy
  union_energy_grid.push_back( this->getMaxElectronEnergy() );

  // Sort the union energy grid
  union_energy_grid.sort();
}

// Find the lower and upper bin boundary for a min and max energy
void StandardAdjointElectronPhotonRelaxationDataGenerator::findLowerAndUpperBinBoundary(
    const double min_energy,
    const double max_energy,
    const std::vector<double>& energy_distribution,
    std::vector<double>::const_iterator& lower_energy_boundary,
    std::vector<double>::const_iterator& upper_energy_boundary ) const
{

  if ( min_energy <= energy_distribution.front() )
  {
    lower_energy_boundary = energy_distribution.begin();
  }
  else
  {
    // Get energy iterator below/equal to min_energy
    lower_energy_boundary = Utility::Search::binaryLowerBound(
                energy_distribution.begin(),
                energy_distribution.end(),
                min_energy );
  }

  // Get energy iterator above/equal to max_electron_energy
  upper_energy_boundary = Utility::Search::binaryUpperBound(
              lower_energy_boundary,
              energy_distribution.end(),
              max_energy );
}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_StandardAdjointElectronPhotonRelaxationDataGenerator.cpp
//---------------------------------------------------------------------------//
