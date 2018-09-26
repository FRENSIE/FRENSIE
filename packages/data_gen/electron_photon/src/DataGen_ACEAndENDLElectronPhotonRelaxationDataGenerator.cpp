//---------------------------------------------------------------------------//
//!
//! \file   DataGen_ACEAndENDLElectronPhotonRelaxationDataGenerator.hpp
//! \author Alex Robinson
//! \brief  The ACE and ENDL electron-photon-relaxation data generator class
//!         definition
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// FRENSIE Includes
#include "DataGen_ACEAndENDLElectronPhotonRelaxationDataGenerator.hpp"
#include "DataGen_FormFactorEvaluator.hpp"
#include "DataGen_ScatteringFunctionEvaluator.hpp"
#include "DataGen_OccupationNumberEvaluator.hpp"
#include "MonteCarlo_ComptonProfileHelpers.hpp"
#include "MonteCarlo_ComptonProfileSubshellConverterFactory.hpp"
#include "Data_SubshellType.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_AtomicMomentumUnit.hpp"
#include "Utility_InverseAngstromUnit.hpp"
#include "Utility_StaticOutputFormatter.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace DataGen{

// Constructor
ACEAndENDLElectronPhotonRelaxationDataGenerator::ACEAndENDLElectronPhotonRelaxationDataGenerator(
     const std::shared_ptr<const Data::XSSEPRDataExtractor>& ace_epr_data,
     const std::shared_ptr<const Data::ENDLDataContainer>& endl_data_container,
     const double min_photon_energy,
     const double max_photon_energy,
     const double min_electron_energy,
     const double max_electron_energy )
  : ENDLElectronPhotonRelaxationDataGenerator( endl_data_container,
                                               min_photon_energy,
                                               max_photon_energy,
                                               min_electron_energy,
                                               max_electron_energy,
                                               false ),
    d_ace_epr_data( ace_epr_data )
{
  // Make sure the ace data is valid
  testPrecondition( ace_epr_data.get() );

  // Check if the data tables are compatible
  TEST_FOR_EXCEPTION( ace_epr_data->extractAtomicNumber() !=
                      this->getENDLDataContainer().getAtomicNumber(),
                      std::runtime_error,
                      "The ACE and ENDL data tables are not compatible "
                      "(Z-ACE=" << ace_epr_data->extractAtomicNumber() <<
                      "(Z-ENDL=" << this->getENDLDataContainer().getAtomicNumber() <<
                      ")!" );

  // Check if the min photon energy is below the ace table min energy
  const double table_min_photon_energy =
    exp( ace_epr_data->extractPhotonEnergyGrid().front() );

  if( min_photon_energy < table_min_photon_energy )
  {
    this->setMinPhotonEnergy( table_min_photon_energy );

    FRENSIE_LOG_WARNING( "the min photon energy requested is below the "
                         << "ACE table min photon energy! The ACE table's min "
                         << "photon energy (" << table_min_photon_energy
                         << ") will be used instead." );
  }

  // Check if the max photon energy is above the ace table max energy
  const double table_max_photon_energy =
    exp( ace_epr_data->extractPhotonEnergyGrid().back() );

  if( max_photon_energy > table_max_photon_energy )
  {
    this->setMaxPhotonEnergy( table_max_photon_energy );

    FRENSIE_LOG_WARNING( "the max photon energy requested is above the "
                         << "ACE table max photon energy! The ACE table's max "
                         << "photon energy (" << table_max_photon_energy
                         << ") will be used instead." );
  }
}

// Basic constructor
ACEAndENDLElectronPhotonRelaxationDataGenerator::ACEAndENDLElectronPhotonRelaxationDataGenerator(
    const std::shared_ptr<const Data::XSSEPRDataExtractor>& ace_epr_data,
    const std::shared_ptr<const Data::ENDLDataContainer>& endl_data_container )
  : ACEAndENDLElectronPhotonRelaxationDataGenerator(
                        ace_epr_data,
                        endl_data_container,
                        exp( ace_epr_data->extractPhotonEnergyGrid().front() ),
                        exp( ace_epr_data->extractPhotonEnergyGrid().back() ),
                        endl_data_container->getElasticEnergyGrid().front(),
                        endl_data_container->getElasticEnergyGrid().back() )
{ /* ... */ }

// Constructor (existing data container)
ACEAndENDLElectronPhotonRelaxationDataGenerator::ACEAndENDLElectronPhotonRelaxationDataGenerator(
     const std::shared_ptr<const Data::XSSEPRDataExtractor>& ace_epr_data,
     const std::shared_ptr<const Data::ENDLDataContainer>& endl_data_container,
     const boost::filesystem::path& file_name_with_path )
  : ENDLElectronPhotonRelaxationDataGenerator( endl_data_container,
                                               file_name_with_path ),
    d_ace_epr_data( ace_epr_data )
{
  // Check if the data tables are compatible
  TEST_FOR_EXCEPTION( ace_epr_data->extractAtomicNumber() !=
                      this->getENDLDataContainer().getAtomicNumber(),
                      std::runtime_error,
                      "The ACE and ENDL data tables are not compatible "
                      "(Z-ACE=" << ace_epr_data->extractAtomicNumber() <<
                      "(Z-ENDL=" << this->getENDLDataContainer().getAtomicNumber() <<
                      ")!" );
}

// Set the relaxation data
void ACEAndENDLElectronPhotonRelaxationDataGenerator::setRelaxationData()
{
  Data::ElectronPhotonRelaxationVolatileDataContainer& data_container =
    this->getVolatileDataContainer();

  // Extract the subshell ENDF designators
  Utility::ArrayView<const double> subshell_designators =
    d_ace_epr_data->extractSubshellENDFDesignators();

  // Assign the set of all subshells
  {
    std::set<unsigned> subshells;

    for( unsigned i = 0; i < subshell_designators.size(); ++i )
      subshells.insert( (unsigned)subshell_designators[i] );

    data_container.setSubshells( subshells );
  }

  // Extract the subshell occupancies
  Utility::ArrayView<const double> subshell_occupancies =
    d_ace_epr_data->extractSubshellOccupancies();

  // Extract the subshell binding energies
  Utility::ArrayView<const double> subshell_binding_energies =
    d_ace_epr_data->extractSubshellBindingEnergies();

  // Extract the number of subshell vacancy transitions
  Utility::ArrayView<const double> subshell_vacancy_transitions =
    d_ace_epr_data->extractSubshellVacancyTransitionPaths();

  // Extract the relo block
  Utility::ArrayView<const double> relo_block =
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
                               (unsigned)relo_block[i] );
    }
  }
}

// Set the transition data
void ACEAndENDLElectronPhotonRelaxationDataGenerator::setTransitionData(
                                     const unsigned subshell,
                                     const unsigned transitions,
                                     const unsigned subshell_data_start_index )
{
  // Make sure the number of transitions is valid
  testPrecondition( transitions > 0 );

  // Extract the xprob block
  Utility::ArrayView<const double> xprob_block =
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

  Data::ElectronPhotonRelaxationVolatileDataContainer& data_container =
    this->getVolatileDataContainer();

  data_container.setSubshellRelaxationVacancies( subshell,
                                                 relaxation_vacancies );

  data_container.setSubshellRelaxationParticleEnergies(
                                                subshell,
                                                relaxation_particle_energies );

  data_container.setSubshellRelaxationProbabilities(subshell,
                                                    relaxation_probabilities );
}

// Set the Compton profile data
void ACEAndENDLElectronPhotonRelaxationDataGenerator::setComptonProfileData()
{
  Data::ElectronPhotonRelaxationVolatileDataContainer& data_container =
    this->getVolatileDataContainer();

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
                              this->getOccupationNumberEvaluationTolerance() );

    std::function<double(double)> evaluation_wrapper =
      evaluator->getComptonProfileEvaluationWrapper();

    std::vector<double> optimized_momentum_grid( 5 ), evaluated_profile;
    optimized_momentum_grid[0] = -1.0;
    optimized_momentum_grid[1] = -0.5;
    optimized_momentum_grid[2] = 0.0;
    optimized_momentum_grid[3] = 0.5;
    optimized_momentum_grid[4] = 1.0;

    try{
      this->getDefaultPhotonGridGenerator().generateAndEvaluateInPlace(
                                                       optimized_momentum_grid,
                                                       evaluated_profile,
                                                       evaluation_wrapper );
    }
    EXCEPTION_CATCH_RETHROW(
                   std::runtime_error,
                   "Could not generate an optimized Compton "
                   "profile momentum grid for the "
                   << Data::convertENDFDesignatorToSubshellEnum( *subshell ) <<
                   " subshell with the provided convergence parameters!" );

    data_container.setComptonProfileMomentumGrid( *subshell,
                                                  optimized_momentum_grid );

    data_container.setComptonProfile( *subshell, evaluated_profile );

    ++subshell;
  }
}

// Set the Waller-Hartree scattering function data
void ACEAndENDLElectronPhotonRelaxationDataGenerator::setWallerHartreeScatteringFunctionData()
{
  Data::ElectronPhotonRelaxationVolatileDataContainer& data_container =
    this->getVolatileDataContainer();

  // Create the evaluator, initial recoil momentum grid
  std::shared_ptr<const ScatteringFunctionEvaluator> evaluator;

  std::list<double> recoil_momentum_grid;

  {
    Utility::ArrayView<const double> jince_block =
      d_ace_epr_data->extractJINCEBlock();

    unsigned scatt_func_size = jince_block.size()/2;

    Utility::ArrayView<const double> raw_recoil_momentum(
                                         jince_block( 1, scatt_func_size-1 ) );

    Utility::ArrayView<const double> raw_scattering_function_values(
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
    this->getDefaultPhotonGridGenerator().generateAndEvaluateInPlace(
                                                          recoil_momentum_grid,
                                                          scattering_function,
                                                          grid_function );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "Could not generate an optimized scattering "
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
void ACEAndENDLElectronPhotonRelaxationDataGenerator::setWallerHartreeAtomicFormFactorData()
{
  Data::ElectronPhotonRelaxationVolatileDataContainer& data_container =
    this->getVolatileDataContainer();

  // Generate the form factor
  {
    Utility::ArrayView<const double> jcohe_block =
      d_ace_epr_data->extractJCOHEBlock();

    unsigned form_factor_size = jcohe_block.size()/3;

    Utility::ArrayView<const double> raw_recoil_momentum(
                                        jcohe_block( 1, form_factor_size-1 ) );

    Utility::ArrayView<const double> raw_form_factor(
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
                                             jcohe_block[2*form_factor_size] );
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
    this->getDefaultPhotonGridGenerator().generateAndEvaluateInPlace(
                                                  squared_recoil_momentum_grid,
                                                  squared_form_factor,
                                                  evaluation_wrapper );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "Could not generate an optimized squared "
                           "form factor squared recoil momentum grid with the "
                           "provided convergence parameters!" );

  data_container.setWallerHartreeSquaredAtomicFormFactorSquaredMomentumGrid(
                                                squared_recoil_momentum_grid );
  data_container.setWallerHartreeSquaredAtomicFormFactor( squared_form_factor );
}

// Set the Waller-Hartree atomic form factor data
void ACEAndENDLElectronPhotonRelaxationDataGenerator::setWallerHartreeAtomicFormFactorData(
                       const std::function<double(double)>& evaluation_wrapper,
                       std::list<double>& recoil_momentum_grid,
                       const double initial_grid_value,
                       const double initial_form_factor_value )
{
  // Generate the new optimized recoil momentum grid
  std::list<double> form_factor;

  try{
    this->getDefaultPhotonGridGenerator().generateAndEvaluateInPlace(
                                                          recoil_momentum_grid,
                                                          form_factor,
                                                          evaluation_wrapper );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "Could not generate an optimized form "
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

  Data::ElectronPhotonRelaxationVolatileDataContainer& data_container =
    this->getVolatileDataContainer();

  data_container.setWallerHartreeAtomicFormFactorMomentumGrid(
                                                     refined_recoil_momentum );
  data_container.setWallerHartreeAtomicFormFactor( refined_form_factor );
}

// Extract the photon heating numbers
void ACEAndENDLElectronPhotonRelaxationDataGenerator::extractPhotonHeatingNumbers(
                        std::shared_ptr<const Utility::UnivariateDistribution>&
                        heating_numbers ) const
{
  this->extractPhotonCrossSection<Utility::LinLog>(
                                     d_ace_epr_data->extractPhotonEnergyGrid(),
                                     d_ace_epr_data->extractLHNMBlock(),
                                     heating_numbers );
}

// Extract the Waller-Hartree incoherent cross section
void ACEAndENDLElectronPhotonRelaxationDataGenerator::extractWallerHartreeIncoherentCrossSection(
                        std::shared_ptr<const Utility::UnivariateDistribution>&
                        waller_hartree_incoherent_cs ) const
{
  this->extractPhotonCrossSection<Utility::LogLog>(
                               d_ace_epr_data->extractPhotonEnergyGrid(),
                               d_ace_epr_data->extractIncoherentCrossSection(),
                               waller_hartree_incoherent_cs );
}

// Extract the Waller-Hartree coherent cross section
void ACEAndENDLElectronPhotonRelaxationDataGenerator::extractWallerHartreeCoherentCrossSection(
                        std::shared_ptr<const Utility::UnivariateDistribution>&
                        waller_hartree_coherent_cs ) const
{
  this->extractPhotonCrossSection<Utility::LogLog>(
                                 d_ace_epr_data->extractPhotonEnergyGrid(),
                                 d_ace_epr_data->extractCoherentCrossSection(),
                                 waller_hartree_coherent_cs );
}

// Extract the subshell photoelectric effect cross section
void ACEAndENDLElectronPhotonRelaxationDataGenerator::extractSubshellPhotoelectricEffectCrossSections(
          std::vector<std::pair<unsigned,std::shared_ptr<const Utility::UnivariateDistribution> > >& cross_sections ) const
{
  Utility::ArrayView<const double> subshell_ordering =
    d_ace_epr_data->extractSubshellENDFDesignators();

  Utility::ArrayView<const double> energy_grid =
      d_ace_epr_data->extractPhotonEnergyGrid();

  Utility::ArrayView<const double> raw_subshell_pe_cross_sections =
    d_ace_epr_data->extractSPHELBlock();

  cross_sections.resize( subshell_ordering.size() );

  for( unsigned i = 0; i < subshell_ordering.size(); ++i )
  {
    cross_sections[i].first = (unsigned)subshell_ordering[i];

    Utility::ArrayView<const double> raw_subshell_pe_cross_section =
      raw_subshell_pe_cross_sections( i*energy_grid.size(),
                                      energy_grid.size() );

    this->extractPhotonCrossSection<Utility::LogLog>(
                                                energy_grid,
                                                raw_subshell_pe_cross_section,
                                                cross_sections[i].second );
  }
}

// Create the heating numbers on the union energy grid
bool ACEAndENDLElectronPhotonRelaxationDataGenerator::createHeatingNumbersOnUnionEnergyGrid(
                  const std::list<double>& union_energy_grid,
                  const std::shared_ptr<const Utility::UnivariateDistribution>&
                  original_cross_section,
                  std::vector<double>& cross_section ) const
{
  unsigned threshold;

  this->createCrossSectionOnUnionEnergyGrid( union_energy_grid,
                                             original_cross_section,
                                             cross_section,
                                             threshold,
                                             0.0,
                                             false );
  return true;
}

// Extract the half Compton profile from the ACE table
void ACEAndENDLElectronPhotonRelaxationDataGenerator::extractHalfComptonProfile(
                                      const unsigned subshell,
                                      std::vector<double>& half_momentum_grid,
                                      std::vector<double>& half_profile ) const
{
  // Extract the raw Compton profile data
  Utility::ArrayView<const double> lswd_block =
    d_ace_epr_data->extractLSWDBlock();

  Utility::ArrayView<const double> swd_block =
    d_ace_epr_data->extractSWDBlock();

  // Create the Compton profile subshell converter for this
  std::shared_ptr<const MonteCarlo::ComptonProfileSubshellConverter> converter;

  MonteCarlo::ComptonProfileSubshellConverterFactory::createConverter(
                                                     converter,
                                                     this->getAtomicNumber() );

  unsigned compton_subshell_index = converter->convertSubshellToIndex(
                              Data::convertENDFDesignatorToSubshellEnum(
                                                                  subshell ) );

  unsigned profile_index = lswd_block[compton_subshell_index];

  unsigned grid_size = swd_block[profile_index];

  // Extract the profile
  Utility::ArrayView<const double> raw_compton_profile_momentum_grid =
    swd_block( profile_index + 1, grid_size );

  Utility::ArrayView<const double> raw_compton_profile =
    swd_block( profile_index + 1 + grid_size, grid_size );

  // Make sure the ACE data has the expected properties
  TEST_FOR_EXCEPTION( raw_compton_profile_momentum_grid.front() != 0.0,
                      std::runtime_error,
                      "The Compton profile momentum grid extracted "
                      "from the ACE table does not have the expected "
                      "properties (grid.front() == 0.0)!" );

  TEST_FOR_EXCEPTION( raw_compton_profile_momentum_grid.back() >=
                      Utility::PhysicalConstants::inverse_fine_structure_constant,
                      std::runtime_error,
                      "The Compton profile momentum grid extracted "
                      "from the ACE table does not have the expected "
                      "properties (grid.back() < IFSC)!" );

  half_momentum_grid.assign( raw_compton_profile_momentum_grid.begin(),
                             raw_compton_profile_momentum_grid.end() );
  half_profile.assign( raw_compton_profile.begin(),
                       raw_compton_profile.end() );
}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_ACEAndENDLElectronPhotonRelaxationDataGenerator.cpp
//---------------------------------------------------------------------------//
