//---------------------------------------------------------------------------//
//!
//! \file   DataGen_StandardElectronPhotonRelaxationDataGenerator.hpp
//! \author Alex Robinson
//! \brief  The standard electron-photon-relaxation data generator class def.
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// FRENSIE Includes
#include "DataGen_StandardElectronPhotonRelaxationDataGenerator.hpp"
#include "DataGen_MomentPreservingElectronDataGenerator.hpp"
#include "DataGen_FormFactorEvaluator.hpp"
#include "DataGen_ScatteringFunctionEvaluator.hpp"
#include "DataGen_OccupationNumberEvaluator.hpp"
#include "MonteCarlo_ComptonProfileHelpers.hpp"
#include "MonteCarlo_ComptonProfileSubshellConverterFactory.hpp"
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "Data_SubshellType.hpp"
#include "Utility_SloanRadauQuadrature.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_AtomicMomentumUnit.hpp"
#include "Utility_InverseAngstromUnit.hpp"
#include "Utility_StaticOutputFormatter.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

namespace DataGen{

// Constructor
StandardElectronPhotonRelaxationDataGenerator::StandardElectronPhotonRelaxationDataGenerator(
     const std::shared_ptr<const Data::XSSEPRDataExtractor>& ace_epr_data,
     const std::shared_ptr<const Data::ENDLDataContainer>& endl_data_container,
     const double min_photon_energy,
     const double max_photon_energy,
     const double min_electron_energy,
     const double max_electron_energy,
     std::ostream* os_log,
     std::ostream* os_warn )
  : ElectronPhotonRelaxationDataGenerator( ace_epr_data->extractAtomicNumber(),
                                           min_photon_energy,
                                           max_photon_energy,
                                           min_electron_energy,
                                           max_electron_energy ),
    d_ace_epr_data( ace_epr_data ),
    d_endl_data_container( endl_data_container ),
    d_os_log( os_log ),
    d_occupation_number_evaluation_tolerance( 1e-3 ),
    d_subshell_incoherent_evaluation_tolerance( 1e-3 ),
    d_photon_threshold_energy_nudge_factor( 1.0001 ),
    d_integrated_total_elastic_cross_section_mode_on( false ),
    d_cutoff_angle_cosine( 1.0 ),
    d_number_of_moment_preserving_angles( 0 ),
    d_tabular_evaluation_tol( 1e-7 ),
    d_linlinlog_interpolation_mode_on( true ),
    d_correlated_sampling_mode_on( true ),
    d_unit_based_interpolation_mode_on( true )
{ 
  // Make sure the ace data is valid
  testPrecondition( ace_epr_data.get() );
  // Make sure the endl data is valid
  testPrecondition( endl_data_container.get() );
  // Make sure the log stream is valid
  testPrecondition( os_log );
  // Make sure the warning stream is valid
  testPrecondition( os_warn );
  
  // Check if the data tables are compatible
  TEST_FOR_EXCEPTION( ace_epr_data->extractAtomicNumber() !=
                      endl_data_container->getAtomicNumber(),
                      std::runtime_error,
                      "Error: The ACE and ENDL data tables are not compatible "
                      "(Z-ACE=" << ace_epr_data->extractAtomicNumber() << 
                      "(Z-ENDL=" << endl_data_container->getAtomicNumber() <<
                      ")!" );

  // Check if the min photon energy is below the ace table min energy
  const double table_min_photon_energy =
    exp( ace_epr_data->extractPhotonEnergyGrid().front() );
  
  if( min_photon_energy < table_min_photon_energy )
  {
    this->setMinPhotonEnergy( table_min_photon_energy );

    (*os_warn) << Utility::BoldMagenta( "Warning: " ) 
               << "the min photon energy requested is below the "
               << "ACE table min photon energy! The ACE table's min photon "
               << "energy (" << table_min_photon_energy << ") will be used "
               << "instead." << std::endl;
  }
  
  // Check if the max photon energy is above the ace table max energy
  const double table_max_photon_energy =
    exp( ace_epr_data->extractPhotonEnergyGrid().back() );
  
  if( max_photon_energy > table_max_photon_energy )
  {
    this->setMaxPhotonEnergy( table_max_photon_energy );

    (*os_warn) << Utility::BoldMagenta( "Warning: " )
               << "the max photon energy requested is above the "
               << "ACE table max photon energy! The ACE table's max photon "
               << "energy (" << table_max_photon_energy << ") will be used "
               << "instead." << std::endl;
  }
  
  // Check if the min electron energy is below the endl table min energy
  const double table_min_electron_energy =
    endl_data_container->getElasticEnergyGrid().front();

  if( min_electron_energy < table_min_electron_energy )
  {
    this->setMinElectronEnergy( table_min_electron_energy );

    (*os_warn) << Utility::BoldMagenta( "Warning: " )
               << "the min electron energy requested is below the "
               << "ENDL table min electron energy! The ENDL table's min "
               << "electron energy (" << table_min_electron_energy << ") "
               << "will be used instead." << std::endl;
  }

  // Check if the max electron energy is above the endl table max energy
  const double table_max_electron_energy =
    endl_data_container->getElasticEnergyGrid().back();

  if( max_electron_energy > table_max_electron_energy )
  {
    this->setMaxElectronEnergy( table_max_electron_energy );

    (*os_warn) << Utility::BoldMagenta( "Warning: " )
               << "the max electron energy requested is above the "
               << "ENDL table max electron energy! The ENDL table's max "
               << "electron energy (" << table_max_electron_energy << ") "
               << "will be used instead." << std::endl;
  }
}

// Basic constructor
StandardElectronPhotonRelaxationDataGenerator::StandardElectronPhotonRelaxationDataGenerator(
     const std::shared_ptr<const Data::XSSEPRDataExtractor>& ace_epr_data,
     const std::shared_ptr<const Data::ENDLDataContainer>& endl_data_container,
     std::ostream* os_log )
  : StandardElectronPhotonRelaxationDataGenerator(
                        ace_epr_data,
                        endl_data_container,
                        exp( ace_epr_data->extractPhotonEnergyGrid().front() ),
                        exp( ace_epr_data->extractPhotonEnergyGrid().back() ),
                        endl_data_container->getElasticEnergyGrid().front(),
                        endl_data_container->getElasticEnergyGrid().back(),
                        os_log,
                        &std::cerr )
{ /* ... */ }

// Set the occupation number evaluation tolerance
void StandardElectronPhotonRelaxationDataGenerator::setOccupationNumberEvaluationTolerance(
                                            const double evaluation_tolerance )
{
  // Make sure the evaluation tolerance is valid
  testPrecondition( evaluation_tolerance > 0.0 );
  testPrecondition( evaluation_tolerance < 1.0 );

  d_occupation_number_evaluation_tolerance = evaluation_tolerance;
}

// Get the occupation number evaluation tolerance
double StandardElectronPhotonRelaxationDataGenerator::getOccupationNumberEvaluationTolerance() const
{
  return d_occupation_number_evaluation_tolerance;
}

// Set the subshell incoherent evaluation tolerance
void StandardElectronPhotonRelaxationDataGenerator::setSubshellIncoherentEvaluationTolerance(
                                            const double evaluation_tolerance )
{
  // Make sure the evaluation tolerance is valid
  testPrecondition( evaluation_tolerance > 0.0 );
  testPrecondition( evaluation_tolerance < 1.0 );

  d_subshell_incoherent_evaluation_tolerance = evaluation_tolerance;
}

// Get the subshell incoherent evaluation tolerance
double StandardElectronPhotonRelaxationDataGenerator::getSubshellIncoherentEvaluationTolerance() const
{
  return d_subshell_incoherent_evaluation_tolerance;
}

// Set the photon threshold energy nudge factor
void StandardElectronPhotonRelaxationDataGenerator::setPhotonThresholdEnergyNudgeFactor(
                                                    const double nudge_factor )
{
  // Make sure the nudge factor is valid
  testPrecondition( nudge_factor >= 1.0 );

  d_photon_threshold_energy_nudge_factor = nudge_factor;
}

// Get the photon threshold energy nudge factor
double StandardElectronPhotonRelaxationDataGenerator::getPhotonThresholdEnergyNudgeFactor() const
{
  return d_photon_threshold_energy_nudge_factor;
}

// Set electron total elastic integrated cross section mode to off (on by default)
void StandardElectronPhotonRelaxationDataGenerator::setElectronTotalElasticIntegratedCrossSectionModeOff()
{
  d_integrated_total_elastic_cross_section_mode_on = false;
}

// Set electron total elastic integrated cross section mode to on (on by default)
void StandardElectronPhotonRelaxationDataGenerator::setElectronTotalElasticIntegratedCrossSectionModeOn()
{
  d_integrated_total_elastic_cross_section_mode_on = true;
}

// Return if electron total elastic integrated cross section mode to on (on by default)
bool StandardElectronPhotonRelaxationDataGenerator::isElectronTotalElasticIntegratedCrossSectionModeOn() const
{
  return d_integrated_total_elastic_cross_section_mode_on;
}

// Set the cutoff angle cosine
void StandardElectronPhotonRelaxationDataGenerator::setCutoffAngleCosine(
                                             const double cutoff_angle_cosine )
{
  // Make sure the cutoff angle cosine is valid
  testPrecondition( cutoff_angle_cosine >= -1.0 );
  testPrecondition( cutoff_angle_cosine <= 1.0 );

  d_cutoff_angle_cosine = cutoff_angle_cosine;
}

// Get the cutoff angle cosine
double StandardElectronPhotonRelaxationDataGenerator::getCutoffAngleCosine() const
{
  return d_cutoff_angle_cosine;
}

// Set the number of moment preserving angles
void StandardElectronPhotonRelaxationDataGenerator::setNumberOfMomentPreservingAngles(
                                              const unsigned number_of_angles )
{
  d_number_of_moment_preserving_angles = number_of_angles;
}

// Get the number of moment preserving angles
double StandardElectronPhotonRelaxationDataGenerator::getNumberOfMomentPreservingAngles() const
{
  return d_number_of_moment_preserving_angles;
}

// Set the FullyTabularTwoDDistribution evaluation tolerance
void StandardElectronPhotonRelaxationDataGenerator::setTabularEvaluationTolerance(
    const double evaluation_tolerance )
{
  // Make sure the evaluation tolerance is valid
  testPrecondition( evaluation_tolerance > 0.0 );
  testPrecondition( evaluation_tolerance < 1.0 );

  d_tabular_evaluation_tol = evaluation_tolerance;
}

// Get the FullyTabularTwoDDistribution evaluation tolerance
double StandardElectronPhotonRelaxationDataGenerator::getTabularEvaluationTolerance() const
{
  return d_tabular_evaluation_tol;
}

// Set electron FullyTabularTwoDDistribution LinLinLog interpolation mode to off (on by default)
void StandardElectronPhotonRelaxationDataGenerator::setElectronLinLinLogInterpolationModeOff()
{
  d_linlinlog_interpolation_mode_on = false;
}

// Set electron FullyTabularTwoDDistribution LinLinLog interpolation mode to on (on by default)
void StandardElectronPhotonRelaxationDataGenerator::setElectronLinLinLogInterpolationModeOn()
{
  d_linlinlog_interpolation_mode_on = true;
}

// Return if electron FullyTabularTwoDDistribution LinLinLog interpolation mode is on
bool StandardElectronPhotonRelaxationDataGenerator::isElectronLinLinLogInterpolationModeOn() const
{
  return d_linlinlog_interpolation_mode_on;
}

// Set electron FullyTabularTwoDDistribution correlated sampling mode to off (on by default)
void StandardElectronPhotonRelaxationDataGenerator::setElectronCorrelatedSamplingModeOff()
{
  d_correlated_sampling_mode_on = false;
}

// Set electron FullyTabularTwoDDistribution correlated sampling mode to on (on by default)
void StandardElectronPhotonRelaxationDataGenerator::setElectronCorrelatedSamplingModeOn()
{
  d_correlated_sampling_mode_on = true;
}

// Return if electron FullyTabularTwoDDistribution correlated sampling mode is on
bool StandardElectronPhotonRelaxationDataGenerator::isElectronCorrelatedSamplingModeOn() const
{
  return d_correlated_sampling_mode_on;
}

// Set electron FullyTabularTwoDDistribution unit based interpolation mode to off (on by default)
void StandardElectronPhotonRelaxationDataGenerator::setElectronUnitBasedInterpolationModeOff()
{
  d_unit_based_interpolation_mode_on = false;
}

// Set electron FullyTabularTwoDDistribution unit based interpolation mode to on (on by default)
void StandardElectronPhotonRelaxationDataGenerator::setElectronUnitBasedInterpolationModeOn()
{
  d_unit_based_interpolation_mode_on = true;
}

// Return if electron FullyTabularTwoDDistribution unit based interpolation mode is on
bool StandardElectronPhotonRelaxationDataGenerator::isElectronUnitBasedInterpolationModeOn() const
{
  return d_unit_based_interpolation_mode_on;
}

// Populate the electron-photon-relaxation data container
void StandardElectronPhotonRelaxationDataGenerator::populateEPRDataContainer(
    Data::ElectronPhotonRelaxationVolatileDataContainer& data_container ) const
{
  // Set the table data
  this->setBasicData( data_container );
  this->setDefaultConvergenceParameters( data_container );
  data_container.setOccupationNumberEvaluationTolerance(
    d_occupation_number_evaluation_tolerance );
  data_container.setSubshellIncoherentEvaluationTolerance(
    d_subshell_incoherent_evaluation_tolerance );
  data_container.setPhotonThresholdEnergyNudgeFactor(
    d_photon_threshold_energy_nudge_factor );
  data_container.setElectronTotalElasticIntegratedCrossSectionModeOnOff(
    d_integrated_total_elastic_cross_section_mode_on );
  data_container.setCutoffAngleCosine( d_cutoff_angle_cosine );
  data_container.setNumberOfMomentPreservingAngles(
    d_number_of_moment_preserving_angles );
  data_container.setElectronTabularEvaluationTolerance(
    d_tabular_evaluation_tol );
  data_container.setElectronLinLinLogInterpolationModeOnOff(
    d_linlinlog_interpolation_mode_on );
  data_container.setElectronCorrelatedSamplingModeOnOff(
    d_correlated_sampling_mode_on );
  data_container.setElectronUnitBasedInterpolationModeOnOff(
    d_unit_based_interpolation_mode_on );

  // Set the relaxation data
  (*d_os_log) << std::endl << Utility::Bold( "Setting the relaxation data" )
              << "...";
  d_os_log->flush();
  this->setRelaxationData( data_container );
  (*d_os_log) << Utility::BoldGreen( "done." ) << std::endl;

  // Set the photon data
  (*d_os_log) << Utility::Bold( "Setting the photon data: " )
              << std::endl;
  this->setPhotonData( data_container );
  (*d_os_log) << Utility::BoldGreen( "done." ) << std::endl;

  // Set the electron data
  (*d_os_log) << Utility::Bold("Setting the electron data: " ) << std::endl;
  this->setElectronData( data_container );
  (*d_os_log) << Utility::BoldGreen( "done." ) << std::endl;

}

// Repopulate the electron elastic data
void StandardElectronPhotonRelaxationDataGenerator::repopulateElectronElasticData(
    Data::ElectronPhotonRelaxationVolatileDataContainer& data_container,
    const double max_electron_energy,
    const double cutoff_angle_cosine,
    const double tabular_evaluation_tol,
    const unsigned number_of_moment_preserving_angles,
    const bool linlinlog_interpolation_mode_on,
    std::ostream& os_log )
{
  testPrecondition( max_electron_energy > 0.0 );
  testPrecondition( cutoff_angle_cosine <= 1.0 );
  testPrecondition( cutoff_angle_cosine > -1.0 );
  testPrecondition( tabular_evaluation_tol > 0.0 );
  testPrecondition( tabular_evaluation_tol < 1.0 );
  testPrecondition( number_of_moment_preserving_angles >= 0 );

  // Get the elastic angular energy grid
  std::vector<double> angular_energy_grid(
    data_container.getElasticAngularEnergyGrid() );

  if( max_electron_energy != angular_energy_grid.back() )
  {
    // Get the elastic cutoff data
    std::map<double,std::vector<double> > elastic_pdf(
      data_container.getCutoffElasticPDF() );
    std::map<double,std::vector<double> > elastic_angle(
      data_container.getCutoffElasticAngles() );

    // Get the upper boundary of the max energy
    std::vector<double>::iterator energy_bin = 
      Utility::Search::binaryUpperBound( angular_energy_grid.begin(),
                                         angular_energy_grid.end(),
                                         max_electron_energy );

    if( *energy_bin != max_electron_energy )
    {
      std::vector<double> angles, pdf;
      double max_cutoff_angle_cosine = 1.0;
      // Get the angular grid and pdf at the max energy
      if ( linlinlog_interpolation_mode_on )
      {
        MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGridAndPDF<Utility::LinLinLog>(
          angles,
          pdf,
          elastic_angle,
          elastic_pdf,
          max_electron_energy,
          max_cutoff_angle_cosine,
          tabular_evaluation_tol );
      }
      else
      {
        MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGridAndPDF<Utility::LinLinLin>(
          angles,
          pdf,
          elastic_angle,
          elastic_pdf,
          max_electron_energy,
          max_cutoff_angle_cosine,
          tabular_evaluation_tol );
      }

      elastic_angle[max_electron_energy] = angles;
      elastic_pdf[max_electron_energy] = pdf;
    }

    // Set new angular energy grid
    std::vector<double> new_energy_grid( angular_energy_grid.begin(), energy_bin );
    new_energy_grid.push_back( max_electron_energy );

    // Erase all distributions above the max electron energy
    for( energy_bin; energy_bin != angular_energy_grid.end(); energy_bin++ )
    {
      elastic_angle.erase( *energy_bin );
      elastic_pdf.erase( *energy_bin );
    }

    // Set the elastic cutoff data
    data_container.setElasticAngularEnergyGrid( new_energy_grid );
    data_container.setCutoffElasticPDF( elastic_pdf );
    data_container.setCutoffElasticAngles( elastic_angle );
  }
  
  // Repopulate moment preserving data
  StandardElectronPhotonRelaxationDataGenerator::repopulateMomentPreservingData(
    data_container,
    cutoff_angle_cosine,
    tabular_evaluation_tol,
    number_of_moment_preserving_angles,
    linlinlog_interpolation_mode_on,
    os_log );
}

// Repopulate the electron moment preserving data
void StandardElectronPhotonRelaxationDataGenerator::repopulateMomentPreservingData(
    Data::ElectronPhotonRelaxationVolatileDataContainer& data_container,
    const double cutoff_angle_cosine,
    const double tabular_evaluation_tol,
    const unsigned number_of_moment_preserving_angles,
    const bool linlinlog_interpolation_mode_on,
    std::ostream& os_log )
{
  testPrecondition( cutoff_angle_cosine <= 1.0 );
  testPrecondition( cutoff_angle_cosine >= -1.0 );
  testPrecondition( tabular_evaluation_tol > 0.0 );
  testPrecondition( tabular_evaluation_tol < 1.0 );
  testPrecondition( number_of_moment_preserving_angles >= 0 );

  data_container.setCutoffAngleCosine( cutoff_angle_cosine );
  data_container.setNumberOfMomentPreservingAngles( 
    number_of_moment_preserving_angles );
  data_container.setElectronLinLinLogInterpolationModeOnOff(
    linlinlog_interpolation_mode_on );

  std::vector<double> angular_energy_grid(
    data_container.getElasticAngularEnergyGrid() );

  os_log << std::endl
         << Utility::Bold( "Setting the moment preserving electron data" )
         << "...";
  os_log.flush();

  // Clear the old moment preservinf data
  data_container.clearMomentPreservingData();

  // Check if moment preserving data can be generated
  if ( cutoff_angle_cosine > 0.999999 ||
       number_of_moment_preserving_angles < 1 )
  {
    os_log << Utility::BoldYellow( "done." ) << std::endl;
    
    if( cutoff_angle_cosine > 0.999999 )
    {
      os_log << Utility::BoldCyan( "  Note: " )
             << "Moment preserving data was not generated because the"
             << std::endl
             << "        cutoff angle cosine is greater than 0.999999 (mu"
             << "=" << cutoff_angle_cosine << ")."
             << std::endl;
    }

    if( number_of_moment_preserving_angles < 1 )
    {
      os_log << Utility::BoldCyan( "  Note: " )
             << "Moment preserving data was not generated because the"
             << std::endl 
             << "        number of moment preserving angles is less "
             << "than 1." << std::endl;
    }
  }
  // Set the moment preserving data
  else
  {
    StandardElectronPhotonRelaxationDataGenerator::setMomentPreservingData(
      angular_energy_grid,
      tabular_evaluation_tol,
      linlinlog_interpolation_mode_on,
      data_container );
    os_log << Utility::BoldGreen( "done." ) << std::endl;
  }
}

// Set the relaxation data
void StandardElectronPhotonRelaxationDataGenerator::setRelaxationData(
                           Data::ElectronPhotonRelaxationVolatileDataContainer&
                           data_container ) const
{
  // Extract the subshell ENDF designators
  Teuchos::ArrayView<const double> subshell_designators =
    d_ace_epr_data->extractSubshellENDFDesignators();

  // Assign the set of all subshells
  {
    std::set<unsigned> subshells;

    for( unsigned i = 0; i < subshell_designators.size(); ++i )
      subshells.insert( (unsigned)subshell_designators[i] );

    data_container.setSubshells( subshells );
  }

  // Extract the subshell occupancies
  Teuchos::ArrayView<const double> subshell_occupancies =
    d_ace_epr_data->extractSubshellOccupancies();

  // Extract the subshell binding energies
  Teuchos::ArrayView<const double> subshell_binding_energies =
    d_ace_epr_data->extractSubshellBindingEnergies();

  // Extract the number of subshell vacancy transitions
  Teuchos::ArrayView<const double> subshell_vacancy_transitions =
    d_ace_epr_data->extractSubshellVacancyTransitionPaths();

  // Extract the relo block
  Teuchos::ArrayView<const double> relo_block =
    d_ace_epr_data->extractRELOBlock();

  // Assign the subshell data
  for( unsigned i = 0; i < subshell_designators.size(); ++i )
  {
    data_container.setSubshellOccupancy( subshell_designators[i],
                                         subshell_occupancies[i] );

    data_container.setSubshellBindingEnergy( subshell_designators[i],
                                             subshell_binding_energies[i] );

    unsigned transitions = (unsigned)subshell_vacancy_transitions[i];

    if( transitions > 0 )
    {
      data_container.setSubshellRelaxationTransitions( subshell_designators[i],
                                                       transitions );

      this->setTransitionData( subshell_designators[i],
                               transitions,
                               (unsigned)relo_block[i],
                               data_container );
    }
  }
}

// Set the transition data
void StandardElectronPhotonRelaxationDataGenerator::setTransitionData(
                          const unsigned subshell,
                          const unsigned transitions,
                          const unsigned subshell_data_start_index,
                          Data::ElectronPhotonRelaxationVolatileDataContainer&
                          data_container ) const
{
  // Make sure the number of transitions is valid
  testPrecondition( transitions > 0 );

  // Extract the xprob block
  Teuchos::ArrayView<const double> xprob_block =
    d_ace_epr_data->extractXPROBBlock();

  std::vector<std::pair<unsigned,unsigned> > relaxation_vacancies(
                                                                 transitions );
  std::vector<double> relaxation_particle_energies( transitions );
  std::vector<double> relaxation_probabilities( transitions );
  std::vector<double> relaxation_cdf( transitions );

  for( unsigned j = 0; j < transitions; ++j )
  {
    // Extract the primary transition subshell vacancy
    relaxation_vacancies[j].first =
      (unsigned)xprob_block[subshell_data_start_index+j*4];

    // Extract the secondary transition subshell vacancy
    relaxation_vacancies[j].second =
      (unsigned)xprob_block[subshell_data_start_index+j*4+1];

    // Extract the outgoing particle energies
    relaxation_particle_energies[j] =
      xprob_block[subshell_data_start_index+j*4+2];

    // Extract the transition cdf
    relaxation_cdf[j] = xprob_block[subshell_data_start_index+j*4+3];

    // Convert the cdf value to a pdf value
    if( j != 0 )
      relaxation_probabilities[j] = relaxation_cdf[j]-relaxation_cdf[j-1];
    else // j == 0
      relaxation_probabilities[j] = relaxation_cdf[j];
  }

  data_container.setSubshellRelaxationVacancies( subshell,
                                                 relaxation_vacancies );

  data_container.setSubshellRelaxationParticleEnergies(
                                                subshell,
                                                relaxation_particle_energies );

  data_container.setSubshellRelaxationProbabilities(subshell,
                                                    relaxation_probabilities );
}

// Set the Compton profile data
void StandardElectronPhotonRelaxationDataGenerator::setComptonProfileData(
                           Data::ElectronPhotonRelaxationVolatileDataContainer&
                           data_container ) const
{
  const std::set<unsigned>& subshells = data_container.getSubshells();

  std::set<unsigned>::const_iterator subshell = subshells.begin();

  // The evaluator
  std::shared_ptr<OccupationNumberEvaluator> evaluator;

  while( subshell != subshells.end() )
  {
    // Extract the half profile from the ACE data
    std::vector<double> half_momentum_grid, half_profile;

    this->extractHalfComptonProfile( *subshell,
                                     half_momentum_grid,
                                     half_profile );

    std::vector<double> full_momentum_grid, full_profile;

    MonteCarlo::createFullProfileFromHalfProfile( half_momentum_grid.begin(),
                                                  half_momentum_grid.end(),
                                                  half_profile.begin(),
                                                  half_profile.end(),
                                                  full_momentum_grid,
                                                  full_profile,
                                                  true,
                                                  true );

    evaluator = OccupationNumberEvaluator::createEvaluator<Utility::LogLin,Utility::Units::AtomicMomentum>(
                                    full_momentum_grid,
                                    full_profile,
                                    d_occupation_number_evaluation_tolerance );

    std::function<double(double)> evaluation_wrapper =
      evaluator->getComptonProfileEvaluationWrapper();

    std::vector<double> optimized_momentum_grid( 5 ), evaluated_profile;
    optimized_momentum_grid[0] = -1.0;
    optimized_momentum_grid[1] = -0.5;
    optimized_momentum_grid[2] = 0.0;
    optimized_momentum_grid[3] = 0.5;
    optimized_momentum_grid[4] = 1.0;

    try{
      this->getDefaultGridGenerator().generateAndEvaluateInPlace(
                                                       optimized_momentum_grid,
                                                       evaluated_profile,
                                                       evaluation_wrapper );
    }
    EXCEPTION_CATCH_RETHROW(
                   std::runtime_error,
                   "Error: Could not generate an optimized Compton "
                   "profile momentum grid for the "
                   << Data::convertENDFDesignatorToSubshellEnum( *subshell ) <<
                   " subshell with the provided convergence parameters!" );

    data_container.setComptonProfileMomentumGrid( *subshell,
                                                  optimized_momentum_grid );

    data_container.setComptonProfile( *subshell, evaluated_profile );

    ++subshell;
  }
}

// Set the Occupation number data
void StandardElectronPhotonRelaxationDataGenerator::setOccupationNumberData(
                           Data::ElectronPhotonRelaxationVolatileDataContainer&
                           data_container ) const
{
  const std::set<unsigned>& subshells = data_container.getSubshells();

  std::set<unsigned>::const_iterator subshell = subshells.begin();

  // The evaluator
  std::shared_ptr<OccupationNumberEvaluator> evaluator;

  while( subshell != subshells.end() )
  {
    const std::vector<double>& momentum_grid =
      data_container.getComptonProfileMomentumGrid( *subshell );

    const std::vector<double>& compton_profile =
      data_container.getComptonProfile( *subshell );

    // Create the occupation number evaluator
    evaluator = OccupationNumberEvaluator::createEvaluator<Utility::LinLin,Utility::Units::MeCMomentum>(
                                    momentum_grid,
                                    compton_profile,
                                    d_occupation_number_evaluation_tolerance );

    std::function<double(double)> evaluation_wrapper =
      evaluator->getOccupationNumberEvaluationWrapper(
                                    d_occupation_number_evaluation_tolerance );

    // Create the occupation number grid
    std::vector<double> occupation_number_momentum_grid( 5 ),
      occupation_number;
    occupation_number_momentum_grid[0] = -1.0;
    occupation_number_momentum_grid[1] = -0.5;
    occupation_number_momentum_grid[2] = 0.0;
    occupation_number_momentum_grid[3] = 0.5;
    occupation_number_momentum_grid[4] = 1.0;

    try{
      this->getDefaultGridGenerator().generateAndEvaluateInPlace(
                                               occupation_number_momentum_grid,
                                               occupation_number,
                                               evaluation_wrapper );
    }
    EXCEPTION_CATCH_RETHROW(
                   std::runtime_error,
                   "Error: Could not generate an optimized occupation "
                   "number momentum grid for the "
                   << Data::convertENDFDesignatorToSubshellEnum( *subshell ) <<
                   " subshell with the provided convergence parameters!" );

    // Fix the grid rounding errors
    std::vector<double>::iterator unity_occupation =
      std::lower_bound( occupation_number.begin(),
                        occupation_number.end(),
                        1.0 );

    while( unity_occupation != occupation_number.end() )
    {
      *unity_occupation = 1.0;

      ++unity_occupation;
    }

    data_container.setOccupationNumberMomentumGrid(
                                             *subshell,
                                             occupation_number_momentum_grid );
    data_container.setOccupationNumber( *subshell, occupation_number );

    ++subshell;
  }
}

// Set the Waller-Hartree scattering function data
void StandardElectronPhotonRelaxationDataGenerator::setWallerHartreeScatteringFunctionData(
                           Data::ElectronPhotonRelaxationVolatileDataContainer&
                           data_container ) const
{
  // Create the evaluator, initial recoil momentum grid
  std::shared_ptr<const ScatteringFunctionEvaluator> evaluator;

  std::list<double> recoil_momentum_grid;
  
  {
    Teuchos::ArrayView<const double> jince_block =
      d_ace_epr_data->extractJINCEBlock();
    
    unsigned scatt_func_size = jince_block.size()/2;
    
    Teuchos::ArrayView<const double> raw_recoil_momentum(
                                         jince_block( 1, scatt_func_size-1 ) );

    Teuchos::ArrayView<const double> raw_scattering_function_values(
                         jince_block( scatt_func_size+1, scatt_func_size-1 ) );

    // Convert the initial and final grid values from inverse Angstrom to
    // inverse cm before adding them to the new grid.
    recoil_momentum_grid.push_back( raw_recoil_momentum.front()*1e8 );
    recoil_momentum_grid.push_back( raw_recoil_momentum.back()*1e8 );

    evaluator = DataGen::ScatteringFunctionEvaluator::createEvaluator<Utility::LogLog,Utility::Units::InverseAngstrom>(
                                              raw_recoil_momentum,
                                              raw_scattering_function_values );
  }

  boost::function<double (double)> grid_function =
    evaluator->getScatteringFunctionEvaluationWrapper();

  std::list<double> scattering_function;
  
  try{
    this->getDefaultGridGenerator().generateAndEvaluateInPlace(
                                                          recoil_momentum_grid,
                                                          scattering_function,
                                                          grid_function );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "Error: Could not generate an optimized scattering "
                           "function recoil momentum grid with the provided "
                           "convergence parameters!" );

  // This grid point was left off because both the recoil momentum and the
  // scattering function are 0.0, which is incompatible with log-log
  // interpolation
  recoil_momentum_grid.push_front( 0.0 );
  scattering_function.push_front( 0.0 );

  std::vector<double> refined_recoil_momentum, refined_scattering_function;

  refined_recoil_momentum.assign( recoil_momentum_grid.begin(),
                                  recoil_momentum_grid.end() );

  refined_scattering_function.assign( scattering_function.begin(),
                                      scattering_function.end() );

  data_container.setWallerHartreeScatteringFunctionMomentumGrid(
                                                     refined_recoil_momentum );
  data_container.setWallerHartreeScatteringFunction(
                                                 refined_scattering_function );
}

// Set the Waller-Hartree atomic form factor data
void StandardElectronPhotonRelaxationDataGenerator::setWallerHartreeAtomicFormFactorData(
                           Data::ElectronPhotonRelaxationVolatileDataContainer&
                           data_container ) const
{
  // Generate the form factor
  {
    Teuchos::ArrayView<const double> jcohe_block =
      d_ace_epr_data->extractJCOHEBlock();

    unsigned form_factor_size = jcohe_block.size()/3;

    Teuchos::ArrayView<const double> raw_recoil_momentum(
                                        jcohe_block( 1, form_factor_size-1 ) );

    Teuchos::ArrayView<const double> raw_form_factor(
                     jcohe_block( 2*form_factor_size+1, form_factor_size-1 ) );

    // Create a form factor evaluator
    std::shared_ptr<FormFactorEvaluator> evaluator =
      FormFactorEvaluator::createEvaluator<Utility::LogLog,Utility::Units::InverseAngstrom>(
                                                           raw_recoil_momentum,
                                                           raw_form_factor );

    // Create the evaluation wrapper
    std::function<double(double)> evaluation_wrapper =
      evaluator->getFormFactorEvaluationWrapper();

    // Initialize the recoil momentum grid
    std::list<double> recoil_momentum_grid;

    // Convert the initial values from inverse Angstrom to inverse cm
    recoil_momentum_grid.push_back( raw_recoil_momentum.front()*1e8 );
    recoil_momentum_grid.push_back( raw_recoil_momentum.back()*1e8 );
    
    // Convert the initial grid value from inverse Angstrom to inverse cm
    // before passing it into this method
    this->setWallerHartreeAtomicFormFactorData(
                                           evaluation_wrapper,
                                           recoil_momentum_grid,
                                           jcohe_block.front()*1e8,
                                           jcohe_block[2*form_factor_size],
                                           data_container );
  }

  // Generate the squared form factor from the newly generated form factor
  std::shared_ptr<FormFactorEvaluator> evaluator =
      FormFactorEvaluator::createEvaluator<Utility::LinLin,Utility::Units::InverseCentimeter>(
                 data_container.getWallerHartreeAtomicFormFactorMomentumGrid(),
                 data_container.getWallerHartreeAtomicFormFactor() );

  // Create the evaluation wrapper
    std::function<double(double)> evaluation_wrapper =
      evaluator->getFormFactorSquaredEvaluationWrapper();

  // Initialize the squared recoil momentum grid
  std::vector<double> squared_recoil_momentum_grid( 2 ), squared_form_factor;

  squared_recoil_momentum_grid[0] = 
    data_container.getWallerHartreeAtomicFormFactorMomentumGrid().front();
  squared_recoil_momentum_grid[0] *= squared_recoil_momentum_grid[0];

  squared_recoil_momentum_grid[1] = 
    data_container.getWallerHartreeAtomicFormFactorMomentumGrid().back();
  squared_recoil_momentum_grid[1] *= squared_recoil_momentum_grid[1];

  try{
    this->getDefaultGridGenerator().generateAndEvaluateInPlace(
                                                  squared_recoil_momentum_grid,
                                                  squared_form_factor,
                                                  evaluation_wrapper );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "Error: Could not generate an optimized squared "
                           "form factor squared recoil momentum grid with the "
                           "provided convergence parameters!" );

  data_container.setWallerHartreeSquaredAtomicFormFactorSquaredMomentumGrid(
                                                squared_recoil_momentum_grid );
  data_container.setWallerHartreeSquaredAtomicFormFactor( squared_form_factor );
}

// Set the Waller-Hartree atomic form factor data
void StandardElectronPhotonRelaxationDataGenerator::setWallerHartreeAtomicFormFactorData(
                       const std::function<double(double)>& evaluation_wrapper,
                       std::list<double>& recoil_momentum_grid,
                       const double initial_grid_value,
                       const double initial_form_factor_value,
                       Data::ElectronPhotonRelaxationVolatileDataContainer&
                       data_container ) const
{
  // Generate the new optimized recoil momentum grid
  std::list<double> form_factor;

  try{
    this->getDefaultGridGenerator().generateAndEvaluateInPlace(
                                                          recoil_momentum_grid,
                                                          form_factor,
                                                          evaluation_wrapper );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "Error: Could not generate an optimized form "
                           "factor recoil momentum grid with the "
                           "provided convergence parameters!" );

  // The first value was kept off of the grid because the 0.0
  // value of the recoil momentum, which is not compatible with Log-Log
  // interpolation
  recoil_momentum_grid.push_front( initial_grid_value );
  form_factor.push_front( initial_form_factor_value );
      
  std::vector<double> refined_recoil_momentum, refined_form_factor;
    
  refined_recoil_momentum.assign( recoil_momentum_grid.begin(),
                                  recoil_momentum_grid.end() );
    
  refined_form_factor.assign( form_factor.begin(),
                              form_factor.end() );

  data_container.setWallerHartreeAtomicFormFactorMomentumGrid(
                                                     refined_recoil_momentum );
  data_container.setWallerHartreeAtomicFormFactor( refined_form_factor );
}

// Set the photon data
void StandardElectronPhotonRelaxationDataGenerator::setPhotonData(
                           Data::ElectronPhotonRelaxationVolatileDataContainer&
                           data_container ) const
{
  // Set the Compton profile data
  (*d_os_log) << " Setting the " << Utility::Italicized( "Compton profile" )
              << " data...";
  d_os_log->flush();
  this->setComptonProfileData( data_container );
  (*d_os_log) << Utility::BoldGreen( "done." ) << std::endl;

  // Set the occupation number data
  (*d_os_log) << " Setting the " << Utility::Italicized( "occupation number" )
              << " data...";
  d_os_log->flush();
  this->setOccupationNumberData( data_container );
  (*d_os_log) << Utility::BoldGreen( "done." ) << std::endl;

  // Set the Waller-Hartree scattering function data
  (*d_os_log) << " Setting the "
              << Utility::Italicized( "Waller-Hartree scattering function" )
              << " data...";
  d_os_log->flush();
  this->setWallerHartreeScatteringFunctionData( data_container );
  (*d_os_log) << Utility::BoldGreen( "done." ) << std::endl;

  // Set the Waller-Hartree atomic form factor data
  (*d_os_log) << " Setting the "
              << Utility::Italicized( "Waller-Hartree atomic form factor" )
              << " data...";
  d_os_log->flush();
  this->setWallerHartreeAtomicFormFactorData( data_container );
  (*d_os_log) << Utility::BoldGreen( "done." ) << std::endl;

  (*d_os_log) << " Setting the photon cross section data:" << std::endl;
  
  // Extract the heating numbers
  std::shared_ptr<const Utility::OneDDistribution> heating_numbers;

  this->extractPhotonCrossSection<Utility::LinLog>(
                                     d_ace_epr_data->extractPhotonEnergyGrid(),
                                     d_ace_epr_data->extractLHNMBlock(),
                                     heating_numbers );

  // Extract the Waller-Hartree incoherent cross section
  std::shared_ptr<const Utility::OneDDistribution> waller_hartree_incoherent_cs;

  this->extractPhotonCrossSection<Utility::LogLog>(
                               d_ace_epr_data->extractPhotonEnergyGrid(),
                               d_ace_epr_data->extractIncoherentCrossSection(),
                               waller_hartree_incoherent_cs );

  // Extract the Waller-Hartree coherent cross section
  std::shared_ptr<const Utility::OneDDistribution> waller_hartree_coherent_cs;

  this->extractPhotonCrossSection<Utility::LogLog>(
                                 d_ace_epr_data->extractPhotonEnergyGrid(),
                                 d_ace_epr_data->extractCoherentCrossSection(),
                                 waller_hartree_coherent_cs );

  // Extract the pair production cross section
  std::shared_ptr<const Utility::OneDDistribution> pair_production_cs;

  this->extractPhotonCrossSection<Utility::LogLog>(
              d_endl_data_container->getPairProductionCrossSectionEnergyGrid(),
              d_endl_data_container->getPairProductionCrossSection(),
              pair_production_cs,
              false );

  // Extract the triplet production cross section
  std::shared_ptr<const Utility::OneDDistribution> triplet_production_cs;
  
  this->extractPhotonCrossSection<Utility::LogLog>(
           d_endl_data_container->getTripletProductionCrossSectionEnergyGrid(),
           d_endl_data_container->getTripletProductionCrossSection(),
           triplet_production_cs,
           false );                                            

  // Extract the subshell photoelectric effect cross sections
  std::vector<std::pair<unsigned,std::shared_ptr<const Utility::OneDDistribution> > >
    subshell_photoelectric_effect_css;

  this->extractSubshellPhotoelectricCrossSections(
                                           subshell_photoelectric_effect_css );

  // Create the impulse approx. incoherent cross section evaluators
  Teuchos::Array<std::pair<unsigned,std::shared_ptr<const MonteCarlo::SubshellIncoherentPhotonScatteringDistribution> > >
    impulse_approx_incoherent_cs_evaluators;

  this->createSubshellImpulseApproxIncoherentCrossSectionEvaluators(
                                     data_container,
                                     impulse_approx_incoherent_cs_evaluators );

  // Create the union energy grid
  (*d_os_log) << "   Creating " << Utility::Italicized( "union energy grid" );
  d_os_log->flush();
  std::list<double> union_energy_grid;

  this->initializePhotonUnionEnergyGrid( data_container, union_energy_grid );

  // Calculate the union energy grid
  boost::function<double (double pz)> grid_function =
    boost::bind( &Utility::OneDDistribution::evaluate,
                 boost::cref( *heating_numbers ),
                 _1 );

  try{
    this->getDefaultGridGenerator().generateInPlace( union_energy_grid,
                                                     grid_function );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "Error: Could not generate an optimized photon "
                           "energy grid for the heating numbers with the "
                           "provided convergence parameters!" );
  (*d_os_log) << ".";
  d_os_log->flush();

  grid_function = boost::bind( &Utility::OneDDistribution::evaluate,
                               boost::cref( *waller_hartree_incoherent_cs ),
                               _1 );

  try{
    this->getDefaultGridGenerator().generateInPlace( union_energy_grid,
                                                     grid_function );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "Error: Could not generate an optimized photon "
                           "energy grid for the Waller-Hartree incoherent "
                           "cross section with the provided convergence "
                           "parameters!" );
  (*d_os_log) << ".";
  d_os_log->flush();

  grid_function = boost::bind( &Utility::OneDDistribution::evaluate,
                               boost::cref( *waller_hartree_coherent_cs ),
                               _1 );

  try{
    this->getDefaultGridGenerator().generateInPlace( union_energy_grid,
                                                     grid_function );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "Error: Could not generate an optimized photon "
                           "energy grid for the Waller-Hartree coherent "
                           "cross section with the provided convergence "
                           "parameters!" );
  (*d_os_log) << ".";
  d_os_log->flush();

  grid_function = boost::bind( &Utility::OneDDistribution::evaluate,
                               boost::cref( *pair_production_cs ),
                               _1 );

  try{
    this->getDefaultGridGenerator().generateInPlace( union_energy_grid,
                                                     grid_function );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "Error: Could not generate an optimized photon "
                           "energy grid for the pair production cross section "
                           "with the provided convergence parameters!" );
  (*d_os_log) << ".";
  d_os_log->flush();

  grid_function = boost::bind( &Utility::OneDDistribution::evaluate,
                               boost::cref( *triplet_production_cs ),
                               _1 );

  try{
    this->getDefaultGridGenerator().generateInPlace( union_energy_grid,
                                                     grid_function );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "Error: Could not generate an optimized photon "
                           "energy grid for the triplet production cross "
                           "section with the provided convergence "
                           "parameters!" );

  (*d_os_log) << ".";
  d_os_log->flush();

  for( unsigned i = 0; i < subshell_photoelectric_effect_css.size(); ++i )
  {
    grid_function = boost::bind(
                   &Utility::OneDDistribution::evaluate,
                   boost::cref( *subshell_photoelectric_effect_css[i].second ),
                   _1 );

    try{
      this->getDefaultGridGenerator().generateInPlace( union_energy_grid,
                                                       grid_function );
    }
    EXCEPTION_CATCH_RETHROW( std::runtime_error,
                             "Error: Could not generate an optimized photon "
                             "energy grid for the subshell "
                             << Data::convertENDFDesignatorToSubshellEnum(
                                subshell_photoelectric_effect_css[i].first ) <<
                             " photoelectric cross section with the provided "
                             "convergence parameters!" );
    (*d_os_log) << ".";
    d_os_log->flush();
  }

  for( unsigned i = 0; i < impulse_approx_incoherent_cs_evaluators.size(); ++i)
  {
    grid_function = boost::bind(
             &MonteCarlo::SubshellIncoherentPhotonScatteringDistribution::evaluateIntegratedCrossSection,
             boost::cref( *impulse_approx_incoherent_cs_evaluators[i].second ),
             _1,
             d_subshell_incoherent_evaluation_tolerance );

    try{
      this->getDefaultGridGenerator().generateInPlace( union_energy_grid,
                                                       grid_function );
    }
    EXCEPTION_CATCH_RETHROW(
                          std::runtime_error,
                          "Error: Could not generate an optimized photon "
                          "energy grid for the subshell "
                          << Data::convertENDFDesignatorToSubshellEnum(
                          impulse_approx_incoherent_cs_evaluators[i].first ) <<
                          " impulse approx. cross section with the "
                          "provided convergence parameters!" );
    (*d_os_log) << ".";
    d_os_log->flush();
  }

  (*d_os_log) << Utility::BoldGreen( "done." ) << std::endl;
  d_os_log->flush();

  // Set the union energy grid
  std::vector<double> energy_grid;
  energy_grid.assign( union_energy_grid.begin(),
                      union_energy_grid.end() );

  data_container.setPhotonEnergyGrid( energy_grid );

  // Create and set the cross sections
  std::vector<double> cross_section;
  unsigned threshold;

  (*d_os_log) << "   Setting the "
              << Utility::Italicized( "average heating numbers" ) << "...";
  d_os_log->flush();
  this->createCrossSectionOnUnionEnergyGrid( union_energy_grid,
                                             heating_numbers,
                                             cross_section,
                                             threshold,
                                             0.0,
                                             false );

  data_container.setAveragePhotonHeatingNumbers( cross_section );
  (*d_os_log) << Utility::BoldGreen( "done." ) << std::endl;

  (*d_os_log) << "   Setting the "
              << Utility::Italicized( "Waller-Hartree incoherent " )
              << "cross section...";
  d_os_log->flush();
  this->createCrossSectionOnUnionEnergyGrid( union_energy_grid,
                                             waller_hartree_incoherent_cs,
                                             cross_section,
                                             threshold,
                                             0.0,
                                             false );

  data_container.setWallerHartreeIncoherentCrossSection( cross_section );
  data_container.setWallerHartreeIncoherentCrossSectionThresholdEnergyIndex(
                                                                   threshold );
  (*d_os_log) << Utility::BoldGreen( "done." ) << std::endl;

  (*d_os_log) << "   Setting the "
              << Utility::Italicized( "Waller-Hartree coherent " )
              << "cross section...";
  d_os_log->flush();
  this->createCrossSectionOnUnionEnergyGrid( union_energy_grid,
                                             waller_hartree_coherent_cs,
                                             cross_section,
                                             threshold,
                                             0.0,
                                             false );

  data_container.setWallerHartreeCoherentCrossSection( cross_section );
  data_container.setWallerHartreeCoherentCrossSectionThresholdEnergyIndex(
                                                                   threshold );
  (*d_os_log) << Utility::BoldGreen( "done." ) << std::endl;

  (*d_os_log) << "   Setting the "
              << Utility::Italicized( "pair production " )
              << "cross section...";
  d_os_log->flush();
  this->createCrossSectionOnUnionEnergyGrid(
                     union_energy_grid,
                     pair_production_cs,
                     cross_section,
                     threshold,
                     2*Utility::PhysicalConstants::electron_rest_mass_energy,
                     true );

  data_container.setPairProductionCrossSection( cross_section );
  data_container.setPairProductionCrossSectionThresholdEnergyIndex(
                                                                   threshold );
  (*d_os_log) << Utility::BoldGreen( "done." ) << std::endl;

  (*d_os_log) << "   Setting the "
              << Utility::Italicized( "triplet production " )
              << "cross section...";
  d_os_log->flush();
  this->createCrossSectionOnUnionEnergyGrid(
                     union_energy_grid,
                     triplet_production_cs,
                     cross_section,
                     threshold,
                     4*Utility::PhysicalConstants::electron_rest_mass_energy,
                     true );

  data_container.setTripletProductionCrossSection( cross_section );
  data_container.setTripletProductionCrossSectionThresholdEnergyIndex(
                                                                   threshold );

  (*d_os_log) << Utility::BoldGreen( "done." ) << std::endl;

  for( unsigned i = 0; i < subshell_photoelectric_effect_css.size(); ++i )
  {
    (*d_os_log) << "   Setting " << Utility::Italicized( "subshell " )
                << Utility::Italicized(Data::convertENDFDesignatorToSubshellEnum(
                                 subshell_photoelectric_effect_css[i].first ) )
                << Utility::Italicized( " photoelectric " )
                << "cross section...";
    d_os_log->flush();
    
    this->createCrossSectionOnUnionEnergyGrid(
                            union_energy_grid,
                            subshell_photoelectric_effect_css[i].second,
                            cross_section,
                            threshold,
                            data_container.getSubshellBindingEnergy(
                                  subshell_photoelectric_effect_css[i].first ),
                            false );

    data_container.setSubshellPhotoelectricCrossSection(
                                    subshell_photoelectric_effect_css[i].first,
                                    cross_section );
    data_container.setSubshellPhotoelectricCrossSectionThresholdEnergyIndex(
                                    subshell_photoelectric_effect_css[i].first,
                                    threshold );
    (*d_os_log) << Utility::BoldGreen( "done." ) << std::endl;
  }

  for( unsigned i = 0; i < impulse_approx_incoherent_cs_evaluators.size(); ++i)
  {
    (*d_os_log) << "   Setting " << Utility::Italicized( "subshell " )
                << Utility::Italicized(Data::convertENDFDesignatorToSubshellEnum(
                           impulse_approx_incoherent_cs_evaluators[i].first ) )
                << Utility::Italicized(" impusle approx incoherent " )
                << "cross section...";
    d_os_log->flush();
    this->createCrossSectionOnUnionEnergyGrid(
                             union_energy_grid,
                             impulse_approx_incoherent_cs_evaluators[i].second,
                             cross_section,
                             threshold );

    data_container.setImpulseApproxSubshellIncoherentCrossSection(
                              impulse_approx_incoherent_cs_evaluators[i].first,
                              cross_section );
    data_container.setImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex(
                              impulse_approx_incoherent_cs_evaluators[i].first,
                              threshold );
    (*d_os_log) << Utility::BoldGreen( "done." ) << std::endl;
  }

  (*d_os_log) << "   Setting the "
              << Utility::Italicized( "total photoelectric " )
              << "cross section...";
  d_os_log->flush();
  this->calculateTotalPhotoelectricCrossSection( data_container );
  (*d_os_log) << Utility::BoldGreen( "done." ) << std::endl;

  (*d_os_log) << "   Setting the "
              << Utility::Italicized( "impulse approx total incoherent " )
              << "cross section...";
  d_os_log->flush();
  this->calculateImpulseApproxTotalIncoherentCrossSection( data_container );
  (*d_os_log) << Utility::BoldGreen( "done." ) << std::endl;

  (*d_os_log) << "   Setting the "
              << Utility::Italicized( "Waller-Hartree total " )
              << "cross section...";
  d_os_log->flush();
  this->calculatePhotonTotalCrossSection( data_container, true );
  (*d_os_log) << Utility::BoldGreen( "done." ) << std::endl;

  (*d_os_log) << "   Setting the "
              << Utility::Italicized( "impulse approx total " )
              << "cross section...";
  d_os_log->flush();
  this->calculatePhotonTotalCrossSection( data_container, false );
  (*d_os_log) << Utility::BoldGreen( "done." ) << std::endl;
}


// Set the electron data
void StandardElectronPhotonRelaxationDataGenerator::setElectronData(
    Data::ElectronPhotonRelaxationVolatileDataContainer& data_container ) const
{

//---------------------------------------------------------------------------//
// Set Elastic Data
//---------------------------------------------------------------------------//
  (*d_os_log) << " Setting the "
              << Utility::Italicized( "elastic cutoff " )
              << "data...";
  d_os_log->flush();

  // Set elastic angular distribution
  std::map<double,std::vector<double> > elastic_pdf, elastic_angle;

  std::vector<double> angular_energy_grid(
    d_endl_data_container->getCutoffElasticAngularEnergyGrid() );

  /* ENDL gives the angular distribution in terms of the change in angle cosine
   * (delta_angle_cosine = 1 - angle_cosine). For the native format it needs to
   * be in terms of angle_cosine. This for loop flips the distribution and
   * changes the variables to angle_cosine.
   */
  std::vector<double>::iterator energy = angular_energy_grid.begin();
  std::vector<double>::iterator end_energy = 
    Utility::Search::binaryUpperBound( energy,
                                       angular_energy_grid.end(),
                                       this->getMaxElectronEnergy() );
  end_energy++;

  for ( energy; energy != end_energy; energy++ )
  {
    calculateElasticAngleCosine(
        d_endl_data_container->getCutoffElasticAnglesAtEnergy( *energy ),
        d_endl_data_container->getCutoffElasticPDFAtEnergy( *energy ),
        elastic_angle[*energy],
        elastic_pdf[*energy] );
  }

  end_energy--;
  if( *end_energy != this->getMaxElectronEnergy() )
  {
    double max_cutoff_angle_cosine = 1.0;
    if ( d_linlinlog_interpolation_mode_on )
    {
      MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGridAndPDF<Utility::LinLinLog>(
        elastic_angle[this->getMaxElectronEnergy()],
        elastic_pdf[this->getMaxElectronEnergy()] ,
        elastic_angle,
        elastic_pdf,
        this->getMaxElectronEnergy(),
        max_cutoff_angle_cosine,
        d_tabular_evaluation_tol );
    }
    else
    {
      MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGridAndPDF<Utility::LinLinLin>(
        elastic_angle[this->getMaxElectronEnergy()],
        elastic_pdf[this->getMaxElectronEnergy()] ,
        elastic_angle,
        elastic_pdf,
        this->getMaxElectronEnergy(),
        max_cutoff_angle_cosine,
        d_tabular_evaluation_tol );
    }

    elastic_angle.erase( *end_energy );
    elastic_pdf.erase( *end_energy );
  }

  // Set new angular energy grid
  while( angular_energy_grid.back() >= this->getMaxElectronEnergy() )
  {
    angular_energy_grid.pop_back();
  }
  angular_energy_grid.push_back( this->getMaxElectronEnergy() );

  // Set the elastic cutoff data
  data_container.setElasticAngularEnergyGrid( angular_energy_grid );
  data_container.setCutoffElasticPDF( elastic_pdf );
  data_container.setCutoffElasticAngles( elastic_angle );

  (*d_os_log) << Utility::BoldGreen( "done." ) << std::endl;

//---------------------------------------------------------------------------//
// Set Electron Cross Section Data Data
//---------------------------------------------------------------------------//
/*! \details The cross section data is needed for caluculating the
 *  moment preserving data and must be set first.
 */
  (*d_os_log) << " Setting the electron cross section data:" << std::endl;
  d_os_log->flush();
  setElectronCrossSectionsData( data_container );

  (*d_os_log) << " Setting the "
              << Utility::Italicized( "elastic moment preserving " )
              << "data...";
  d_os_log->flush();

  // Check if moment preserving data can be generated
  if ( d_cutoff_angle_cosine > 0.999999 ||
       d_number_of_moment_preserving_angles < 1 )
  {
    (*d_os_log) << Utility::BoldYellow( "done." ) << std::endl;
    
    if( d_cutoff_angle_cosine > 0.999999 )
    {
      (*d_os_log) << Utility::BoldCyan( "  Note: " )
                  << "Moment preserving data was not generated because the"
                  << std::endl
                  << "        cutoff angle cosine is greater than 0.999999 (mu"
                  << "=" << d_cutoff_angle_cosine << ")."
                  << std::endl;
    }

    if( d_number_of_moment_preserving_angles < 1 )
    {
      (*d_os_log) << Utility::BoldCyan( "  Note: " )
                  << "Moment preserving data was not generated because the"
                  << std::endl 
                  << "        number of moment preserving angles is less "
                  << "than 1." << std::endl;
    }
  }
  // Set the moment preserving data
  else
  {
    StandardElectronPhotonRelaxationDataGenerator::setMomentPreservingData(
        angular_energy_grid,
        d_tabular_evaluation_tol,
        d_linlinlog_interpolation_mode_on,
        data_container );
    (*d_os_log) << Utility::BoldGreen( "done." ) << std::endl;
  }

//---------------------------------------------------------------------------//
// Set Electroionization Data
//---------------------------------------------------------------------------//
  (*d_os_log) << " Setting the "
              << Utility::Italicized( "electroionization " )
              << "data...";
  d_os_log->flush();

  std::set<unsigned>::iterator shell = data_container.getSubshells().begin();

  // Loop through electroionization data for every subshell
  for ( shell; shell != data_container.getSubshells().end(); shell++ )
  {
    data_container.setElectroionizationEnergyGrid(
        *shell,
        d_endl_data_container->getElectroionizationRecoilEnergyGrid( *shell ) );

    data_container.setElectroionizationRecoilEnergy(
        *shell,
        d_endl_data_container->getElectroionizationRecoilEnergy( *shell ) );

    data_container.setElectroionizationRecoilPDF(
        *shell,
        d_endl_data_container->getElectroionizationRecoilPDF( *shell ) );
  }
  (*d_os_log) << Utility::BoldGreen( "done." ) << std::endl;

//---------------------------------------------------------------------------//
// Set Bremsstrahlung Data
//---------------------------------------------------------------------------//
  (*d_os_log) << " Setting the "
              << Utility::Italicized( "bremsstrahlung " )
              << "data...";
  d_os_log->flush();

  data_container.setBremsstrahlungEnergyGrid(
    d_endl_data_container->getBremsstrahlungPhotonEnergyGrid() );

  data_container.setBremsstrahlungPhotonEnergy(
    d_endl_data_container->getBremsstrahlungPhotonEnergy() );

  data_container.setBremsstrahlungPhotonPDF(
    d_endl_data_container->getBremsstrahlungPhotonPDF() );

  (*d_os_log) << Utility::BoldGreen( "done." ) << std::endl;

//---------------------------------------------------------------------------//
// Set Atomic Excitation Data
//---------------------------------------------------------------------------//
  (*d_os_log) << " Setting the "
              << Utility::Italicized( "atomic excitation " )
              << "data...";
  d_os_log->flush();

  std::vector<double> raw_energy_grid =
    d_endl_data_container->getAtomicExcitationEnergyGrid();

  // Set atomic excitation energy loss
  data_container.setAtomicExcitationEnergyGrid( raw_energy_grid );
  data_container.setAtomicExcitationEnergyLoss(
    d_endl_data_container->getAtomicExcitationEnergyLoss() );

  (*d_os_log) << Utility::BoldGreen( "done." ) << std::endl;
}


// Set the electron cross section union energy grid
void StandardElectronPhotonRelaxationDataGenerator::setElectronCrossSectionsData(
    Data::ElectronPhotonRelaxationVolatileDataContainer& data_container ) const
{
  // cross sections in the file
  std::shared_ptr<const Utility::OneDDistribution>
        bremsstrahlung_cross_section, atomic_excitation_cross_section,
        cutoff_elastic_cross_section, total_elastic_cross_section;

  // Initialize union energy grid
  std::list<double> union_energy_grid;
  this->initializeElectronUnionEnergyGrid( data_container, union_energy_grid );

//---------------------------------------------------------------------------//
// Get Elastic Data Cross Section Data
//---------------------------------------------------------------------------//
  // Get cutoff elastic cross section to union energy grid
  std::vector<double> raw_energy_grid =
    d_endl_data_container->getElasticEnergyGrid();

  cutoff_elastic_cross_section.reset(
    new Utility::TabularDistribution<Utility::LogLog>(
    raw_energy_grid,
    d_endl_data_container->getCutoffElasticCrossSection() ) );

  // merge raw energy grid with the union energy grid
  mergeElectronUnionEnergyGrid( raw_energy_grid, union_energy_grid );

  // Calculate the electron total elastic cross section
  this->calculateElectronTotalElasticCrossSection(
            data_container,
            total_elastic_cross_section,
            raw_energy_grid );

//---------------------------------------------------------------------------//
// Get Electroionization Data Cross Section Data
//---------------------------------------------------------------------------//

  std::set<unsigned>::iterator shell = data_container.getSubshells().begin();

  std::vector<std::pair<unsigned,std::shared_ptr<const Utility::OneDDistribution> > >
    electroionization_cross_section( data_container.getSubshells().size() );

  unsigned i = 0;
  // Loop through electroionization data for every subshell
  for ( shell; shell != data_container.getSubshells().end(); shell++ )
  {
    // Get the raw energy grid
    raw_energy_grid =
        d_endl_data_container->getElectroionizationCrossSectionEnergyGrid(*shell);

    // merge raw energy grid with the union energy grid
    mergeElectronUnionEnergyGrid( raw_energy_grid, union_energy_grid );

    /*! \details There is conflicting documentation on the proper interpolation
     *  of the electroionization cross section data. The endl data file interp flag
     *  specifies lin-lin, but the documentation wrtie-up says to use log-log
     *  interpolation on all cross sections. It was decided to match MCNP which
     *  uses log-log interpolation for electroionization.
     */
    this->extractElectronCrossSection<Utility::LogLog>(
                raw_energy_grid,
                d_endl_data_container->getElectroionizationCrossSection(*shell),
                electroionization_cross_section[i].second );

    // Set the shell indentifier
    electroionization_cross_section[i].first = *shell;
    i++;
  }

//---------------------------------------------------------------------------//
// Get Bremsstrahlung Cross Section Data
//---------------------------------------------------------------------------//

  raw_energy_grid =
    d_endl_data_container->getBremsstrahlungCrossSectionEnergyGrid();

  bremsstrahlung_cross_section.reset(
    new Utility::TabularDistribution<Utility::LinLin>(
    raw_energy_grid,
    d_endl_data_container->getBremsstrahlungCrossSection() ) );

  // merge raw energy grid with the union energy grid
  mergeElectronUnionEnergyGrid( raw_energy_grid, union_energy_grid );


//---------------------------------------------------------------------------//
// Get Atomic Excitation Data Cross Section Data
//---------------------------------------------------------------------------//

  raw_energy_grid = d_endl_data_container->getAtomicExcitationEnergyGrid();

  atomic_excitation_cross_section.reset(
    new Utility::TabularDistribution<Utility::LinLin>(
    raw_energy_grid,
    d_endl_data_container->getAtomicExcitationCrossSection() ) );

  // merge raw energy grid with the union energy grid
  mergeElectronUnionEnergyGrid( raw_energy_grid, union_energy_grid );

//---------------------------------------------------------------------------//
// Create union energy grid and calculate cross sections
//---------------------------------------------------------------------------//

  // Create the union energy grid
  (*d_os_log) << "   Creating " << Utility::Italicized( "union energy grid" );
  d_os_log->flush();


  // Calculate the union energy grid
  boost::function<double (double pz)> grid_function =
    boost::bind( &Utility::OneDDistribution::evaluate,
                 boost::cref( *cutoff_elastic_cross_section ),
                 _1 );

  try{
    this->getDefaultGridGenerator().generateInPlace( union_energy_grid,
                                                     grid_function );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "Error: Could not generate an optimized electron "
                           "energy grid for the cutoff elastic cross section "
                           "with the provided convergence parameters!" );

  (*d_os_log) << ".";
  d_os_log->flush();

  grid_function = boost::bind(
        &Utility::OneDDistribution::evaluate,
        boost::cref( *total_elastic_cross_section ),
        _1 );

  try{
    this->getDefaultGridGenerator().generateInPlace( union_energy_grid,
                                                     grid_function );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "Error: Could not generate an optimized electron "
                           "energy grid for the total elastic cross section "
                           "with the provided convergence parameters!" );
  (*d_os_log) << ".";
  d_os_log->flush();

  grid_function = boost::bind( &Utility::OneDDistribution::evaluate,
                               boost::cref( *bremsstrahlung_cross_section ),
                               _1 );

  try{
    this->getDefaultGridGenerator().generateInPlace( union_energy_grid,
                                                     grid_function );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "Error: Could not generate an optimized electron "
                           "energy grid for the bremsstrahlung cross section "
                           "with the provided convergence parameters!" );
  (*d_os_log) << ".";
  d_os_log->flush();

  grid_function = boost::bind( &Utility::OneDDistribution::evaluate,
                               boost::cref( *atomic_excitation_cross_section ),
                               _1 );

  try{
    this->getDefaultGridGenerator().generateInPlace( union_energy_grid,
                                                     grid_function );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "Error: Could not generate an optimized electron "
                           "energy grid for the atomic excitation cross "
                           "section with the provided convergence "
                           "parameters!" );
  (*d_os_log) << ".";
  d_os_log->flush();

  for( unsigned i = 0; i < electroionization_cross_section.size(); ++i )
  {
    grid_function = boost::bind(
                   &Utility::OneDDistribution::evaluate,
                   boost::cref( *electroionization_cross_section[i].second ),
                   _1 );

    try{
      this->getDefaultGridGenerator().generateInPlace( union_energy_grid,
                                                       grid_function );
    }
    EXCEPTION_CATCH_RETHROW(
                          std::runtime_error,
                          "Error: Could not generate an optimized electron "
                          "energy grid for the subshell "
                          << Data::convertENDFDesignatorToSubshellEnum(
                                  electroionization_cross_section[i].first ) <<
                          " electroionization cross section with the "
                          "provided convergence parameters!" );
    (*d_os_log) << ".";
    d_os_log->flush();
  }

  (*d_os_log) << Utility::BoldGreen( "done." ) << std::endl;

  // Set the union energy grid
  std::vector<double> energy_grid;
  energy_grid.assign( union_energy_grid.begin(),
                      union_energy_grid.end() );

  data_container.setElectronEnergyGrid( energy_grid );


  // Create and set the cross sections
  std::vector<double> cross_section;
  unsigned threshold;

  {
  // Set Elastic cross section data
  std::vector<double> cutoff_cross_section, total_cross_section;

  (*d_os_log) << "   Setting the "
              << Utility::Italicized( "cutoff elastic " )
              << "cross section...";
  d_os_log->flush();
  
  this->createCrossSectionOnUnionEnergyGrid(
                     union_energy_grid,
                     cutoff_elastic_cross_section,
                     cutoff_cross_section,
                     threshold,
                     cutoff_elastic_cross_section->getLowerBoundOfIndepVar(),
                     false );
  
  data_container.setCutoffElasticCrossSection( cutoff_cross_section );
  data_container.setCutoffElasticCrossSectionThresholdEnergyIndex( threshold );
  
  (*d_os_log) << Utility::BoldGreen( "done." ) << std::endl;

  (*d_os_log) << "   Setting the "
              << Utility::Italicized( "screened Rutherford elastic " )
              << "cross section...";
  d_os_log->flush();
  
  this->createCrossSectionOnUnionEnergyGrid(
                      union_energy_grid,
                      total_elastic_cross_section,
                      total_cross_section,
                      threshold,
                      total_elastic_cross_section->getLowerBoundOfIndepVar(),
                      false );

  data_container.setTotalElasticCrossSection( total_cross_section );
  data_container.setTotalElasticCrossSectionThresholdEnergyIndex( threshold );

  std::vector<double> raw_cross_section( total_cross_section.size() );
  for ( int i = 0; i < total_cross_section.size(); ++i )
  {
    raw_cross_section[i] = total_cross_section[i] - cutoff_cross_section[i];

    // Calcualte the relative difference between the total and cutoff cross sections
    double relative_difference = raw_cross_section[i]/total_cross_section[i];

    // Check for roundoff error and reduce to zero if needed
    if ( relative_difference < 1.0e-6 )
    {
      raw_cross_section[i] = 0.0;

      // Update threshold index
      threshold = i+1;
    }
  }

  std::vector<double>::iterator start = raw_cross_section.begin();
  std::advance( start, threshold );

  cross_section.assign( start, raw_cross_section.end() );

  data_container.setScreenedRutherfordElasticCrossSection( cross_section );
  data_container.setScreenedRutherfordElasticCrossSectionThresholdEnergyIndex(
    threshold );
  (*d_os_log) << Utility::BoldGreen( "done." ) << std::endl;
  }

  (*d_os_log) << "   Setting the " << Utility::Italicized( "bremsstrahlung " )
              << "cross section...";
  d_os_log->flush();
  
  this->createCrossSectionOnUnionEnergyGrid(
                     union_energy_grid,
                     bremsstrahlung_cross_section,
                     cross_section,
                     threshold,
                     bremsstrahlung_cross_section->getLowerBoundOfIndepVar(),
                     false );

  data_container.setBremsstrahlungCrossSection( cross_section );
  data_container.setBremsstrahlungCrossSectionThresholdEnergyIndex( threshold );
  (*d_os_log) << Utility::BoldGreen( "done." ) << std::endl;

  (*d_os_log) << "   Setting the " 
              << Utility::Italicized( "atomic excitation " )
              << "cross section...";
  d_os_log->flush();
  
  this->createCrossSectionOnUnionEnergyGrid(
                  union_energy_grid,
                  atomic_excitation_cross_section,
                  cross_section,
                  threshold,
                  atomic_excitation_cross_section->getLowerBoundOfIndepVar(),
                  true );

  data_container.setAtomicExcitationCrossSection( cross_section );
  data_container.setAtomicExcitationCrossSectionThresholdEnergyIndex(
                                                                   threshold );
  
  (*d_os_log) << Utility::BoldGreen( "done." ) << std::endl;

  for( unsigned i = 0; i < electroionization_cross_section.size(); ++i )
  {
    (*d_os_log) << "   Setting " << Utility::Italicized( "subshell " )
                << Utility::Italicized(Data::convertENDFDesignatorToSubshellEnum(
                                   electroionization_cross_section[i].first ) )
                << Utility::Italicized( " electroionization " )
                << "cross section...";
    d_os_log->flush();
    
    this->createCrossSectionOnUnionEnergyGrid(
                               union_energy_grid,
                               electroionization_cross_section[i].second,
                               cross_section,
                               threshold,
                               data_container.getSubshellBindingEnergy(
                                    electroionization_cross_section[i].first ),
                               true );

    data_container.setElectroionizationCrossSection(
                                    electroionization_cross_section[i].first,
                                    cross_section );
    data_container.setElectroionizationCrossSectionThresholdEnergyIndex(
                                    electroionization_cross_section[i].first,
                                    threshold );
    (*d_os_log) << Utility::BoldGreen( "done." ) << std::endl;
  }
}

// Set the moment preserving data
void StandardElectronPhotonRelaxationDataGenerator::setMomentPreservingData(
    const std::vector<double>& angular_energy_grid,
    const double tabular_evaluation_tol,
    const bool linlinlog_interpolation_mode_on,
    Data::ElectronPhotonRelaxationVolatileDataContainer& data_container )
{
  // Make sure the tolerance is valid
  testPrecondition( tabular_evaluation_tol > 0.0 );
  testPrecondition( tabular_evaluation_tol < 1.0 );

  // Create the analog elastic distribution (combined Cutoff and Screened Rutherford)
  std::shared_ptr<const MonteCarlo::AnalogElasticElectronScatteringDistribution>
        analog_distribution;

  bool correlated_sampling_mode_on = true;

  if ( linlinlog_interpolation_mode_on )
  {
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createAnalogElasticDistribution<Utility::LinLinLog>(
        analog_distribution,
        data_container.getCutoffElasticAngles(),
        data_container.getCutoffElasticPDF(),
        angular_energy_grid,
        data_container.getAtomicNumber(),
        correlated_sampling_mode_on,
        tabular_evaluation_tol );
  }
  else
  {
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createAnalogElasticDistribution<Utility::LinLinLin>(
        analog_distribution,
        data_container.getCutoffElasticAngles(),
        data_container.getCutoffElasticPDF(),
        angular_energy_grid,
        data_container.getAtomicNumber(),
        correlated_sampling_mode_on,
        tabular_evaluation_tol );
  }

  // Construct the hash-based grid searcher for this atom
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.assign( data_container.getElectronEnergyGrid().begin(),
                      data_container.getElectronEnergyGrid().end() );

  Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
     new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>, false>(
             energy_grid,
             100u ) );

  // Construct the cutoff reaction
  Teuchos::ArrayRCP<double> cutoff_cross_section;
  cutoff_cross_section.assign(
    data_container.getCutoffElasticCrossSection().begin(),
    data_container.getCutoffElasticCrossSection().end() );

  // Construct the screened Rutherford reaction
  Teuchos::ArrayRCP<double> rutherford_cross_section;
  rutherford_cross_section.assign(
    data_container.getScreenedRutherfordElasticCrossSection().begin(),
    data_container.getScreenedRutherfordElasticCrossSection().end() );

  // Create the moment evaluator of the elastic scattering distribution
  std::shared_ptr<DataGen::ElasticElectronMomentsEvaluator> moments_evaluator;
  moments_evaluator.reset(
    new DataGen::ElasticElectronMomentsEvaluator(
        data_container.getCutoffElasticAngles(),
        energy_grid,
        grid_searcher,
        cutoff_cross_section,
        rutherford_cross_section,
        data_container.getCutoffElasticCrossSectionThresholdEnergyIndex(),
        data_container.getScreenedRutherfordElasticCrossSectionThresholdEnergyIndex(),
        analog_distribution,
        data_container.getCutoffAngleCosine() ) );

  // Moment preserving discrete angles and weights
  std::vector<double> discrete_angles, weights;

  // weights for a discrete angle cosine = 1
  std::vector<double> cross_section_reduction( angular_energy_grid.size() );

  // iterate through all angular energy bins
  for ( unsigned i = 0; i < angular_energy_grid.size(); i++ )
  {
    StandardElectronPhotonRelaxationDataGenerator::calculateDiscreteAnglesAndWeights(
        moments_evaluator,
        angular_energy_grid[i],
        data_container.getNumberOfMomentPreservingAngles(),
        discrete_angles,
        weights,
        cross_section_reduction[i] );

    data_container.setMomentPreservingElasticDiscreteAngles(
        angular_energy_grid[i],
        discrete_angles );
    data_container.setMomentPreservingElasticWeights(
        angular_energy_grid[i],
        weights );
  }

  // Set the cross section reduction
  data_container.setMomentPreservingCrossSectionReduction(
    cross_section_reduction );

  // Generate a cross section reduction distribution
  std::shared_ptr<const Utility::OneDDistribution> reduction_distribution;

  if ( linlinlog_interpolation_mode_on )
  {
    // Use LinLog interpoaltion between bins of coarse angular energy grid
    reduction_distribution.reset(
        new Utility::TabularDistribution<Utility::LinLog>(
            angular_energy_grid,
            cross_section_reduction ) );
  }
  else
  {
    // Use LinLin interpoaltion between bins of coarse angular energy grid
    reduction_distribution.reset(
        new Utility::TabularDistribution<Utility::LinLin>(
            angular_energy_grid,
            cross_section_reduction ) );
  }

  // Calculate the moment preserving cross section
  std::vector<double> moment_preserving_cross_section;
  StandardElectronPhotonRelaxationDataGenerator::calculateMomentPreservingCrossSection(
        energy_grid,
        cutoff_cross_section,
        rutherford_cross_section,
        data_container.getCutoffElasticCrossSectionThresholdEnergyIndex(),
        data_container.getScreenedRutherfordElasticCrossSectionThresholdEnergyIndex(),
        analog_distribution,
        reduction_distribution,
        data_container.getCutoffAngleCosine(),
        moment_preserving_cross_section );

  data_container.setMomentPreservingCrossSection(
    moment_preserving_cross_section );

  data_container.setMomentPreservingCrossSectionThresholdEnergyIndex(
    data_container.getCutoffElasticCrossSectionThresholdEnergyIndex() );
}

// Extract the half Compton profile from the ACE table
void StandardElectronPhotonRelaxationDataGenerator::extractHalfComptonProfile(
                                      const unsigned subshell,
                                      std::vector<double>& half_momentum_grid,
                                      std::vector<double>& half_profile ) const
{
  // Extract the raw Compton profile data
  Teuchos::ArrayView<const double> lswd_block =
    d_ace_epr_data->extractLSWDBlock();

  Teuchos::ArrayView<const double> swd_block =
    d_ace_epr_data->extractSWDBlock();

  // Create the Compton profile subshell converter for this
  std::shared_ptr<MonteCarlo::ComptonProfileSubshellConverter> converter;

  MonteCarlo::ComptonProfileSubshellConverterFactory::createConverter(
                                                     converter,
                                                     this->getAtomicNumber() );

  unsigned compton_subshell_index = converter->convertSubshellToIndex(
                              Data::convertENDFDesignatorToSubshellEnum(
                                                                  subshell ) );

  unsigned profile_index = lswd_block[compton_subshell_index];

  unsigned grid_size = swd_block[profile_index];

  // Extract the profile
  Teuchos::ArrayView<const double> raw_compton_profile_momentum_grid =
    swd_block( profile_index + 1, grid_size );

  Teuchos::ArrayView<const double> raw_compton_profile =
    swd_block( profile_index + 1 + grid_size, grid_size );

  // Make sure the ACE data has the expected properties
  TEST_FOR_EXCEPTION( raw_compton_profile_momentum_grid.front() != 0.0,
                      std::runtime_error,
                      "Error: The Compton profile momentum grid extracted "
                      "from the ACE table does not have the expected "
                      "properties (grid.front() == 0.0)!" );

  TEST_FOR_EXCEPTION( raw_compton_profile_momentum_grid.back() >=
                      Utility::PhysicalConstants::inverse_fine_structure_constant,
                      std::runtime_error,
                      "Error: The Compton profile momentum grid extracted "
                      "from the ACE table does not have the expected "
                      "properties (grid.back() < IFSC)!" );

  half_momentum_grid.assign( raw_compton_profile_momentum_grid.begin(),
                             raw_compton_profile_momentum_grid.end() );
  half_profile.assign( raw_compton_profile.begin(),
                       raw_compton_profile.end() );
}

// Extract the subshell photoelectric effect cross section
void StandardElectronPhotonRelaxationDataGenerator::extractSubshellPhotoelectricCrossSections(
          std::vector<std::pair<unsigned,std::shared_ptr<const Utility::OneDDistribution> > >& cross_sections ) const
{
  Teuchos::ArrayView<const double> subshell_ordering =
    d_ace_epr_data->extractSubshellENDFDesignators();

  Teuchos::ArrayView<const double> energy_grid =
      d_ace_epr_data->extractPhotonEnergyGrid();

  Teuchos::ArrayView<const double> raw_subshell_pe_cross_sections =
    d_ace_epr_data->extractSPHELBlock();

  cross_sections.resize( subshell_ordering.size() );

  for( unsigned i = 0; i < subshell_ordering.size(); ++i )
  {
    cross_sections[i].first = (unsigned)subshell_ordering[i];

    Teuchos::ArrayView<const double> raw_subshell_pe_cross_section =
      raw_subshell_pe_cross_sections( i*energy_grid.size(),
                                      energy_grid.size() );

    this->extractPhotonCrossSection<Utility::LogLog>(
                                                energy_grid,
                                                raw_subshell_pe_cross_section,
                                                cross_sections[i].second );
  }
}

// Create the subshell impulse approx incoherent cross section evaluators
void StandardElectronPhotonRelaxationDataGenerator::createSubshellImpulseApproxIncoherentCrossSectionEvaluators(
     const Data::ElectronPhotonRelaxationVolatileDataContainer& data_container,
     Teuchos::Array<std::pair<unsigned,std::shared_ptr<const MonteCarlo::SubshellIncoherentPhotonScatteringDistribution> > >& evaluators ) const
{
  Teuchos::ArrayView<const double> subshell_ordering =
    d_ace_epr_data->extractSubshellENDFDesignators();

  evaluators.resize( subshell_ordering.size() );

  for( unsigned i = 0; i < subshell_ordering.size(); ++i )
  {
    unsigned subshell = (unsigned)subshell_ordering[i];

    evaluators[i].first = subshell;

    const std::vector<double>& momentum_grid =
      data_container.getOccupationNumberMomentumGrid( subshell );

    const std::vector<double>& occupation_number =
      data_container.getOccupationNumber( subshell );

    Teuchos::RCP<const Utility::OneDDistribution> occupation_number_dist(
       new Utility::TabularDistribution<Utility::LinLin>( momentum_grid,
                                                          occupation_number ) );

    evaluators[i].second.reset( new MonteCarlo::SubshellIncoherentPhotonScatteringDistribution(
                   Data::convertENDFDesignatorToSubshellEnum( subshell ),
                   data_container.getSubshellOccupancy( subshell ),
                   data_container.getSubshellBindingEnergy( subshell ),
                   occupation_number_dist ) );
  }
}

// Initialize the photon union energy grid
void StandardElectronPhotonRelaxationDataGenerator::initializePhotonUnionEnergyGrid(
     const Data::ElectronPhotonRelaxationVolatileDataContainer& data_container,
     std::list<double>& union_energy_grid ) const
{
  // Add the min photon energy to the union energy grid
  union_energy_grid.push_back( this->getMinPhotonEnergy() );

  // Add the binding energies
  this->addBindingEnergiesToUnionEnergyGrid( data_container,
                                             this->getMinPhotonEnergy(),
                                             this->getMaxPhotonEnergy(),
                                             true,
                                             union_energy_grid );

  // Add the pair production threshold
  const double pp_threshold =
    2*Utility::PhysicalConstants::electron_rest_mass_energy;

  if( pp_threshold > this->getMinPhotonEnergy() &&
      pp_threshold < this->getMaxPhotonEnergy() )
  {
    union_energy_grid.push_back( pp_threshold );
  }

  const double nudged_pp_threshold =
    pp_threshold*d_photon_threshold_energy_nudge_factor;

  if( nudged_pp_threshold > this->getMinPhotonEnergy() &&
      nudged_pp_threshold < this->getMinPhotonEnergy() )
  {
    union_energy_grid.push_back( nudged_pp_threshold );
  }

  // Add the triplet production threshold
  const double tp_threshold =
    4*Utility::PhysicalConstants::electron_rest_mass_energy;

  if( tp_threshold > this->getMinPhotonEnergy() &&
      tp_threshold < this->getMaxPhotonEnergy() )
  {
    union_energy_grid.push_back( tp_threshold );
  }

  const double nudged_tp_threshold =
    tp_threshold*d_photon_threshold_energy_nudge_factor;

  if( nudged_tp_threshold > this->getMinPhotonEnergy() &&
      nudged_tp_threshold < this->getMaxPhotonEnergy() )
  {
    union_energy_grid.push_back( nudged_tp_threshold );
  }

  // Add the max photon energy
  union_energy_grid.push_back( this->getMaxPhotonEnergy() );

  // Sort the union energy grid
  union_energy_grid.sort();
}
  
// Initialize the electron union energy grid
void StandardElectronPhotonRelaxationDataGenerator::initializeElectronUnionEnergyGrid(
     const Data::ElectronPhotonRelaxationVolatileDataContainer& data_container,
     std::list<double>& union_energy_grid ) const
{
  // Add the min electron energy to the union energy grid
  union_energy_grid.push_back( this->getMinElectronEnergy() );

  // Add the binding energies
  this->addBindingEnergiesToUnionEnergyGrid( data_container,
                                             this->getMinElectronEnergy(),
                                             this->getMaxElectronEnergy(),
                                             true,
                                             union_energy_grid );

  // Add the max electron energy
  union_energy_grid.push_back( this->getMaxElectronEnergy() );

  // Sort the union energy grid
  union_energy_grid.sort();
}

// Add binding energies to union energy grid
void StandardElectronPhotonRelaxationDataGenerator::addBindingEnergiesToUnionEnergyGrid(
     const Data::ElectronPhotonRelaxationVolatileDataContainer& data_container,
     const double min_energy,
     const double max_energy,
     const bool add_nudged_values,
     std::list<double>& union_energy_grid ) const
{
  const std::set<unsigned>& subshells = data_container.getSubshells();

  std::set<unsigned>::const_iterator subshell = subshells.begin();

  // Add the subshell binding energies
  while( subshell != subshells.end() )
  {
    double binding_energy =
      data_container.getSubshellBindingEnergy( *subshell );

    // The subshell photoelectric cross sections have a jump discontinuity at
    // the binding energy of the subshell. Ideally we would add in the binding
    // energy twice and evaluate it to zero at the first instance and the cross
    // section value at the second instance. We will use a very small shift
    // value to mimic this behavior since our grid generation algorithm is not
    // set up to handle this special case
    if( binding_energy - 1e-9 > min_energy &&
        binding_energy - 1e-9 < max_energy )
    {
      union_energy_grid.push_back( binding_energy - 1e-9 );
    }
    
    if( binding_energy > min_energy &&
        binding_energy < max_energy )
    {
      union_energy_grid.push_back( binding_energy );
    }

    // Since the subshell incoherent, pair production and triplet production
    // cross sections go to zero at the binding energy we will add another
    // grid point, which is the binding energy plus a small shift value.
    // Avoiding the zero value of the cross section has been shown to improve
    // grid generation times. The true threshold energy (binding energy) will
    // be added back into the grid for the subshell cross section at the end
    if( add_nudged_values )
    {
      const double nudged_binding_energy =
        binding_energy*d_photon_threshold_energy_nudge_factor;
      
      if( nudged_binding_energy > this->getMinPhotonEnergy() &&
          nudged_binding_energy < this->getMaxPhotonEnergy() )
      {
        union_energy_grid.push_back( nudged_binding_energy );
      }
    }

    ++subshell;
  }
}

// Merge a secondary energy grid with the electron union energy grid
void StandardElectronPhotonRelaxationDataGenerator::mergeElectronUnionEnergyGrid(
     const std::vector<double>& energy_grid,
     std::list<double>& union_energy_grid ) const
{
  // Assign the new grid to the union grid
  union_energy_grid.insert( union_energy_grid.begin(),
                            energy_grid.begin(),
                            energy_grid.end() );

  // Sort the union energy grid
  union_energy_grid.sort();

  // Remove all energies less than the min
  while ( union_energy_grid.front() < this->getMinElectronEnergy() )
  {
    union_energy_grid.pop_front();
  }

  // Remove all energies greater than the max
  while ( union_energy_grid.back() > this->getMaxElectronEnergy() )
  {
    union_energy_grid.pop_back();
  }

  // Make sure the union energy grid values are unique
  union_energy_grid.unique();
}

// Create the cross section on the union energy grid
void StandardElectronPhotonRelaxationDataGenerator::createCrossSectionOnUnionEnergyGrid(
   const std::list<double>& union_energy_grid,
   const std::shared_ptr<const Utility::OneDDistribution>& original_cross_section,
   std::vector<double>& cross_section,
   unsigned& threshold_index,
   const double true_threshold_energy,
   const bool zero_at_threshold  ) const
{
  // Make the threshold region cross section (this step is not necessary if
  // the true threshold energy == the threshold energy present in the cross
  // section distribution)
  std::shared_ptr<const Utility::OneDDistribution>
    threshold_region_cross_section;

  // Get the cross sections current (possibly fictitious) threshold energy
  double current_threshold_energy =
    original_cross_section->getLowerBoundOfIndepVar();

  // Note: The cross section in the threshold region will either be a
  //       line from zero to the cross section at the current threshold
  //       energy (if the cross section goes to zero at its threshold - e.g.
  //       pair production) or a uniform distribution with a value equal to
  //       the cross section at the current threshold energy (if the cross
  //       section has a jump discontinuity at its threshold - e.g.
  //       photoelectric).
  {
    // Get the cross section at the current threshold energy
    double current_threshold_cross_section =
      original_cross_section->evaluate( current_threshold_energy );
  
    // Create a distribution for the range between the true threshold and
    // the current threshold
    if( true_threshold_energy < current_threshold_energy )
    {
      std::vector<double> threshold_region_energy_range( 2 );
      threshold_region_energy_range[0] = true_threshold_energy;
      threshold_region_energy_range[1] = current_threshold_energy;
      
      std::vector<double> threshold_region_cross_section_values( 2 );
      
      if( zero_at_threshold )
        threshold_region_cross_section_values[0] = 0.0;
      else
      {
        threshold_region_cross_section_values[0] =
          current_threshold_cross_section;
      }
      
      threshold_region_cross_section_values[1] =
        current_threshold_cross_section;
      
      threshold_region_cross_section.reset(
                          new Utility::TabularDistribution<Utility::LinLin>(
                                     threshold_region_energy_range,
                                     threshold_region_cross_section_values ) );
    }
  }

  // Evaluate the cross section on the union energy grid
  std::vector<double> raw_cross_section( union_energy_grid.size() );

  std::list<double>::const_iterator energy_grid_pt = union_energy_grid.begin();

  unsigned index = 0u;

  while( energy_grid_pt != union_energy_grid.end() )
  {
    if( *energy_grid_pt < true_threshold_energy )
      raw_cross_section[index] = 0.0;
    
    else if( *energy_grid_pt >= true_threshold_energy &&
             *energy_grid_pt < current_threshold_energy )
    {
      raw_cross_section[index] =
        threshold_region_cross_section->evaluate( *energy_grid_pt );
    }
    else
    {
      raw_cross_section[index] =
        original_cross_section->evaluate( *energy_grid_pt );
    }
    
    ++energy_grid_pt;
    ++index;
  }

  this->populateCrossSection( raw_cross_section,
                              cross_section,
                              threshold_index,
                              zero_at_threshold );
}

// Create the cross section on the union energy grid
void StandardElectronPhotonRelaxationDataGenerator::createCrossSectionOnUnionEnergyGrid(
             const std::list<double>& union_energy_grid,
             const std::shared_ptr<const MonteCarlo::SubshellIncoherentPhotonScatteringDistribution>&
             original_cross_section,
             std::vector<double>& cross_section,
             unsigned& threshold_index ) const
{
  std::vector<double> raw_cross_section( union_energy_grid.size() );

  std::list<double>::const_iterator energy_grid_pt = union_energy_grid.begin();

  unsigned index = 0u;

  while( energy_grid_pt != union_energy_grid.end() )
  {
    raw_cross_section[index] =
      original_cross_section->evaluateIntegratedCrossSection(
                                  *energy_grid_pt,
                                  d_subshell_incoherent_evaluation_tolerance );

    ++energy_grid_pt;
    ++index;
  }

  // The subshell incoherent cross section is zero at the threshold energy
  this->populateCrossSection( raw_cross_section,
                              cross_section,
                              threshold_index,
                              true );
}

// Populate a cross section using the raw cross section
void StandardElectronPhotonRelaxationDataGenerator::populateCrossSection(
                                  const std::vector<double>& raw_cross_section,
                                  std::vector<double>& cross_section,
                                  unsigned& threshold_index,
                                  const bool zero_at_threshold ) const
{
  // Find the threshold energy index
  std::vector<double>::const_iterator start =
    std::find_if( raw_cross_section.begin(),
                  raw_cross_section.end(),
                  notEqualZero );

  // If the value of the cross section at the threshold energy is zero, set
  // the threshold energy of the cross section to the last energy where it
  // was equal to zero.
  if( start != raw_cross_section.begin() && zero_at_threshold )
    --start;
  
  cross_section.assign( start, raw_cross_section.end() );

  threshold_index = std::distance( raw_cross_section.begin(), start );
}

// Calculate the total photoelectric cross section
void StandardElectronPhotonRelaxationDataGenerator::calculateTotalPhotoelectricCrossSection(
                           Data::ElectronPhotonRelaxationVolatileDataContainer&
                           data_container ) const
{
  const std::vector<double>& energy_grid =
    data_container.getPhotonEnergyGrid();

  std::vector<double> raw_cross_section( energy_grid.size(), 0.0 );

  const std::set<unsigned>& subshells = data_container.getSubshells();

  std::set<unsigned>::const_iterator subshell = subshells.begin();

  while( subshell != subshells.end() )
  {
    const std::vector<double>& subshell_photoelectric_cs =
      data_container.getSubshellPhotoelectricCrossSection( *subshell );

    unsigned start_index =
      energy_grid.size() - subshell_photoelectric_cs.size();

    for( unsigned i = 0; i < subshell_photoelectric_cs.size(); ++i )
      raw_cross_section[start_index+i] += subshell_photoelectric_cs[i];

    ++subshell;
  }

  std::vector<double> cross_section;
  unsigned threshold;

  // Note: The cross section has jump discontinuity at the lowest binding
  //       energy. We will therefore not shift the start index back one (as
  //       is done when the cross section is zero at the threshold).
  this->populateCrossSection( raw_cross_section,
                              cross_section,
                              threshold,
                              false );
  
  data_container.setPhotoelectricCrossSection( cross_section );
  data_container.setPhotoelectricCrossSectionThresholdEnergyIndex( threshold );
}

// Calculate the total impulse approx. incoherent cross section
void StandardElectronPhotonRelaxationDataGenerator::calculateImpulseApproxTotalIncoherentCrossSection(
                           Data::ElectronPhotonRelaxationVolatileDataContainer&
                           data_container ) const
{
  const std::vector<double>& energy_grid =
    data_container.getPhotonEnergyGrid();

  std::vector<double> raw_cross_section( energy_grid.size(), 0.0 );

  const std::set<unsigned>& subshells = data_container.getSubshells();

  std::set<unsigned>::const_iterator subshell = subshells.begin();

  while( subshell != subshells.end() )
  {
    const std::vector<double>& subshell_incoherent_cs =
      data_container.getImpulseApproxSubshellIncoherentCrossSection(*subshell);

    unsigned start_index = energy_grid.size() - subshell_incoherent_cs.size();

    for( unsigned i = 0; i < subshell_incoherent_cs.size(); ++i )
      raw_cross_section[start_index+i] += subshell_incoherent_cs[i];

    ++subshell;
  }

  std::vector<double> cross_section;
  unsigned threshold;

  // The value of the cross section at the threshold energy is zero. Set
  // the threshold energy of the cross section to the last energy where it
  // was equal to zero.
  this->populateCrossSection( raw_cross_section,
                              cross_section,
                              threshold,
                              true );

  data_container.setImpulseApproxIncoherentCrossSection( cross_section );
  data_container.setImpulseApproxIncoherentCrossSectionThresholdEnergyIndex(
                                                                   threshold );
}

// Calculate the photon total cross section
void StandardElectronPhotonRelaxationDataGenerator::calculatePhotonTotalCrossSection(
           Data::ElectronPhotonRelaxationVolatileDataContainer& data_container,
           const bool use_waller_hartree_incoherent_cs ) const
{
  const std::vector<double>& energy_grid =
    data_container.getPhotonEnergyGrid();

  std::vector<double> total_cross_section( energy_grid.size(), 0.0 );

  // Add the incoherent cs
  if( use_waller_hartree_incoherent_cs )
  {
    this->addCrossSectionToPhotonTotalCrossSection(
                       energy_grid,
                       data_container.getWallerHartreeIncoherentCrossSection(),
                       total_cross_section );
  }
  else
  {
    this->addCrossSectionToPhotonTotalCrossSection(
                       energy_grid,
                       data_container.getImpulseApproxIncoherentCrossSection(),
                       total_cross_section );
  }

  // Add the coherent cs
  this->addCrossSectionToPhotonTotalCrossSection(
                       energy_grid,
                       data_container.getWallerHartreeCoherentCrossSection(),
                       total_cross_section );

  // Add the pair production cs
  this->addCrossSectionToPhotonTotalCrossSection(
                       energy_grid,
                       data_container.getPairProductionCrossSection(),
                       total_cross_section );

  // Add the triplet production cs
  this->addCrossSectionToPhotonTotalCrossSection(
                       energy_grid,
                       data_container.getTripletProductionCrossSection(),
                       total_cross_section );
  
  // Add the photoelectric cs
  this->addCrossSectionToPhotonTotalCrossSection(
                       energy_grid,
                       data_container.getPhotoelectricCrossSection(),
                       total_cross_section );

  if( use_waller_hartree_incoherent_cs )
    data_container.setWallerHartreeTotalCrossSection( total_cross_section );
  else
    data_container.setImpulseApproxTotalCrossSection( total_cross_section );
}

// Add cross section to photon total cross section
void StandardElectronPhotonRelaxationDataGenerator::addCrossSectionToPhotonTotalCrossSection(
                               const std::vector<double>& energy_grid,
                               const std::vector<double>& cross_section,
                               std::vector<double>& total_cross_section ) const
{
  unsigned start_index = energy_grid.size() - cross_section.size();

  for( unsigned i = 0; i < cross_section.size(); ++i )
    total_cross_section[start_index+i] += cross_section[i];
}

// Calculate the elastic anglular distribution for the angle cosine
void StandardElectronPhotonRelaxationDataGenerator::calculateElasticAngleCosine(
    const std::vector<double>& raw_elastic_angle,
    const std::vector<double>& raw_elastic_pdf,
    std::vector<double>& elastic_angle,
    std::vector<double>& elastic_pdf ) const
{
  int size = raw_elastic_angle.size();
  int r_bin = size - 1;

  elastic_angle.resize( size );
  elastic_pdf.resize( size );

  for ( int bin = 0; bin < size; bin++ )
  {
    elastic_pdf[r_bin] = raw_elastic_pdf[bin];
    long double angle_cosine = 1.0L - raw_elastic_angle[bin];
    elastic_angle[r_bin] = angle_cosine;
    r_bin--;
  }
}

// Calculate the elastic moment preserving discrete angle cosines and weights
void StandardElectronPhotonRelaxationDataGenerator::calculateDiscreteAnglesAndWeights(
    const std::shared_ptr<DataGen::ElasticElectronMomentsEvaluator>& moments_evaluator,
    const double& energy,
    const int& number_of_moment_preserving_angles,
    std::vector<double>& discrete_angles,
    std::vector<double>& weights,
    double& cross_section_reduction )
{
  std::vector<Utility::long_float> legendre_moments;
  double precision = 1e-13;
  int n = ( number_of_moment_preserving_angles+1 )*2 -2;

  // Get the elastic moments
  moments_evaluator->evaluateElasticMoment( legendre_moments,
                                            energy,
                                            n,
                                            precision );

  // Use radau quadrature to find the discrete angles and weights from the moments
  std::shared_ptr<Utility::SloanRadauQuadrature> radau_quadrature(
      new Utility::SloanRadauQuadrature( legendre_moments ) );

  radau_quadrature->getRadauNodesAndWeights( discrete_angles,
                                             weights,
                                             number_of_moment_preserving_angles+1 );

  // Eliminate the forward discrete angle (mu = 1)
  discrete_angles.pop_back();
  weights.pop_back();

  // Renormalize weights and set the cross_section_reduction to the sum of the weights 
  cross_section_reduction = 0.0;
  for( int i = 0; i < weights.size(); i++ )
  {
    cross_section_reduction += weights[i];
  }

  for( int i = 0; i < weights.size(); i++ )
  {
    weights[i] /= cross_section_reduction;
  }
}

// Calculate the electron total elastic cross section
/*! \details The ENDL tables have a total elastic cross section alternatively
 * the total elastic cross section can also be calculated from integrating over
 * the cutoff distribution and the normalized screened Rutherford distribution.
 * The two versions of the cross section will usually be of the same magnitude,
 * but will not agree due to the course 2D grid and roundoff error.
 */
void StandardElectronPhotonRelaxationDataGenerator::calculateElectronTotalElasticCrossSection(
    Data::ElectronPhotonRelaxationVolatileDataContainer& data_container,
    std::shared_ptr<const Utility::OneDDistribution>& total_elastic_cross_section,
    const std::vector<double>& raw_energy_grid ) const
{
  // Check to see if the ENDL or integrated cross section is wanted
  if ( !d_integrated_total_elastic_cross_section_mode_on )
  {
    // Get total elastic cross section provided with ENDL
    total_elastic_cross_section.reset(
      new Utility::TabularDistribution<Utility::LogLog>(
        raw_energy_grid,
        d_endl_data_container->getTotalElasticCrossSection() ) );
  }
  else
  {
    std::shared_ptr<const MonteCarlo::AnalogElasticElectronScatteringDistribution>
            analog_endl_distribution;

    if ( d_linlinlog_interpolation_mode_on )
    {
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createAnalogElasticDistribution<Utility::LinLinLog>(
        analog_endl_distribution,
        data_container.getCutoffElasticAngles(),
        data_container.getCutoffElasticPDF(),
        data_container.getElasticAngularEnergyGrid(),
        data_container.getAtomicNumber(),
        d_correlated_sampling_mode_on,
        d_tabular_evaluation_tol );
    }
    else
    {
        MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createAnalogElasticDistribution<Utility::LinLinLin>(
            analog_endl_distribution,
            data_container.getCutoffElasticAngles(),
            data_container.getCutoffElasticPDF(),
            data_container.getElasticAngularEnergyGrid(),
            data_container.getAtomicNumber(),
            d_correlated_sampling_mode_on,
            d_tabular_evaluation_tol );
    }

    std::vector<double> raw_elastic_cross_section =
        d_endl_data_container->getCutoffElasticCrossSection();

    // Calculate the total elastic cross section
    for (unsigned n = 0; n < raw_elastic_cross_section.size(); n++)
    {
      // Get the energy
      double energy = raw_energy_grid[n];

      // Get the CDF value at the cutoff angle cosine
      double cutoff_cdf = analog_endl_distribution->evaluateCDFAtCutoff( energy );

      // Evaluate the total analog cross section at the incoming energy
      raw_elastic_cross_section[n] /= cutoff_cdf;
    }

    // Get total elastic cross section (same energy grid as cutoff)
    total_elastic_cross_section.reset(
      new Utility::TabularDistribution<Utility::LogLog>(
        raw_energy_grid,
        raw_elastic_cross_section ) );
  }
}


// Calculate the elastic moment preserving cross section
/*! \details The analog elastic distributions and elastic cross sections are on
 *  different energy grids. To calculate the moment preserving cross sections
 *  reduction values will have to be interpolated on the course analog energy
 *  grid. The analog distribution may be on a smaller energy grid, in which case
 *  the moment preserving cross section would be evaluated as zero outside the
 *  analog energy grid range.
 */
void StandardElectronPhotonRelaxationDataGenerator::calculateMomentPreservingCrossSection(
    const Teuchos::ArrayRCP<double>& electron_energy_grid,
    const Teuchos::ArrayRCP<const double>& cutoff_cross_sections,
    const Teuchos::ArrayRCP<const double>& screened_rutherford_cross_sections,
    const unsigned cutoff_threshold_energy_index,
    const unsigned screened_rutherford_threshold_energy_index,
    const std::shared_ptr<const MonteCarlo::AnalogElasticElectronScatteringDistribution>
        analog_distribution,
    const std::shared_ptr<const Utility::OneDDistribution>& reduction_distribution,
    const double cutoff_angle_cosine,
    std::vector<double>& moment_preserving_cross_section )
{
  // Get the max energy of the distributions
  double max_energy = reduction_distribution->getUpperBoundOfIndepVar();

  moment_preserving_cross_section.resize( cutoff_cross_sections.size() );

  unsigned begin = cutoff_threshold_energy_index;

  for( unsigned i = begin; i < cutoff_cross_sections.size(); i++ )
  {
    double cutoff_cdf =
                analog_distribution->evaluateCutoffCDF( electron_energy_grid[i],
                                                        cutoff_angle_cosine );

    double cross_section_reduction =
        reduction_distribution->evaluate( electron_energy_grid[i] );

    double rutherford_cross_section;
    if ( i < screened_rutherford_threshold_energy_index )
        rutherford_cross_section = 0.0;
    else
    {
      rutherford_cross_section = screened_rutherford_cross_sections[
                                  i-screened_rutherford_threshold_energy_index];
    }

    double cutoff_cross_section =
        cutoff_cross_sections[i-cutoff_threshold_energy_index];

    moment_preserving_cross_section[i] = cross_section_reduction*
        (rutherford_cross_section + (1.0 - cutoff_cdf)*cutoff_cross_section);
  }
}


} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_StandardElectronPhotonRelaxationDataGenerator.cpp
//---------------------------------------------------------------------------//
