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
#include "DataGen_OccupationNumberEvaluator.hpp"
#include "MonteCarlo_ComptonProfileHelpers.hpp"
#include "MonteCarlo_ComptonProfileSubshellConverterFactory.hpp"
#include "MonteCarlo_SubshellType.hpp"
#include "Utility_GridGenerator.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace DataGen{

// Initialize the static member data
const double StandardElectronPhotonRelaxationDataGenerator::s_threshold_energy_nudge_factor = 1.0001;

// Constructor
StandardElectronPhotonRelaxationDataGenerator::StandardElectronPhotonRelaxationDataGenerator( 
	   const unsigned atomic_number,
	   const Teuchos::RCP<const Data::XSSEPRDataExtractor>& ace_epr_data,
	   const double min_photon_energy,
	   const double max_photon_energy,
	   const double occupation_number_evaluation_tolerance,
	   const double subshell_incoherent_evaluation_tolerance,
	   const double grid_convergence_tol,
	   const double grid_absolute_diff_tol,
	   const double grid_distance_tol )
  : ElectronPhotonRelaxationDataGenerator( atomic_number ),
    d_ace_epr_data( ace_epr_data ),
    d_min_photon_energy( min_photon_energy ),
    d_max_photon_energy( max_photon_energy ),
    d_occupation_number_evaluation_tolerance( occupation_number_evaluation_tolerance ),
    d_subshell_incoherent_evaluation_tolerance( subshell_incoherent_evaluation_tolerance ),
    d_grid_convergence_tol( grid_convergence_tol ),
    d_grid_absolute_diff_tol( grid_absolute_diff_tol ),
    d_grid_distance_tol( grid_distance_tol )
{
  // Make sure the atomic number is valid
  testPrecondition( atomic_number <= 100u );
  // Make sure the ace data is valid
  testPrecondition( !ace_epr_data.is_null() );
  // Make sure the photon energy limits are valid
  testPrecondition( min_photon_energy > 0.0 );
  testPrecondition( min_photon_energy < max_photon_energy );
}

// Populate the electron-photon-relaxation data container
void StandardElectronPhotonRelaxationDataGenerator::populateEPRDataContainer(
			   Data::ElectronPhotonRelaxationVolatileDataContainer&
			   data_container ) const
{
  // Set the atomic number
  this->setAtomicNumber( data_container );

  // Set the relaxation data
  std::cout << "Setting the relaxation data...";
  std::cout.flush();
  this->setRelaxationData( data_container );
  std::cout << "done." << std::endl;

  // Set the Compton profile data
  std::cout << "Setting the Compton profile data...";
  std::cout.flush();
  this->setComptonProfileData( data_container );
  std::cout << "done." << std::endl;

  // Set the occupation number data
  std::cout << "Setting the occupation number data...";
  std::cout.flush();
  this->setOccupationNumberData( data_container );
  std::cout << "done." << std::endl;

  // Set the Waller-Hartree scattering function data
  std::cout << "Setting the Waller-Hartree scattering function data...";
  std::cout.flush();
  this->setWallerHartreeScatteringFunctionData( data_container );
  std::cout << "done." << std::endl;

  // Set the Waller-Hartree atomic form factor data
  std::cout << "Setting the Waller-Hartree atomic form factor data...";
  this->setWallerHartreeAtomicFormFactorData( data_container );
  std::cout << "done." << std::endl;

  // Set the photon data
  std::cout << "Setting the photon cross section data: " << std::endl;
  this->setPhotonData( data_container );

  // Set the electron data
  this->setElectronData( data_container );
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
						  true );

    MonteCarlo::convertMomentumGridToMeCUnits( full_momentum_grid.begin(),
					       full_momentum_grid.end() );

    MonteCarlo::convertProfileToInverseMeCUnits( full_profile.begin(), 
						 full_profile.end());

    data_container.setComptonProfileMomentumGrid( *subshell,
						  full_momentum_grid );
    
    data_container.setComptonProfile( *subshell, full_profile );

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
  
  while( subshell != subshells.end() )
  {
    const std::vector<double>& momentum_grid = 
      data_container.getComptonProfileMomentumGrid( *subshell );

    const std::vector<double>& compton_profile = 
      data_container.getComptonProfile( *subshell );
    
    // Create the occupation number evaluator
    OccupationNumberEvaluator occupation_number_evaluator( 
				    momentum_grid,
				    compton_profile,
				    d_occupation_number_evaluation_tolerance );

    // Create the occupation number grid
    boost::function<double (double pz)> grid_function = 
      boost::bind( &OccupationNumberEvaluator::evaluateOccupationNumber,
		   boost::cref( occupation_number_evaluator ),
		   _1,
		   d_occupation_number_evaluation_tolerance );

    std::vector<double> occupation_number_momentum_grid( 3 ), 
      occupation_number;
    occupation_number_momentum_grid[0] = -1.0;
    occupation_number_momentum_grid[1] = 0.0;
    occupation_number_momentum_grid[2] = 1.0;

    Utility::GridGenerator<Utility::LinLin> occupation_number_grid_generator(
						      d_grid_convergence_tol,
						      d_grid_absolute_diff_tol,
						      d_grid_distance_tol );

    occupation_number_grid_generator.generateAndEvaluateInPlace(
					       occupation_number_momentum_grid,
					       occupation_number,
					       grid_function );

    // Fix the grid rounding errors
    std::vector<double>::iterator unity_occupation = 
      std::find_if( occupation_number.begin(),
		    occupation_number.end(),
		    greaterThanOrEqualToOne );

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
  Teuchos::ArrayView<const double> jince_block = 
    d_ace_epr_data->extractJINCEBlock();

  unsigned scatt_func_size = jince_block.size()/2;

  Teuchos::ArrayView<const double> raw_recoil_momentum(
					   jince_block( 0, scatt_func_size ) );

  Teuchos::ArrayView<const double> raw_scattering_function(
			     jince_block( scatt_func_size, scatt_func_size ) );

  std::vector<double> recoil_momentum, scattering_function;
  
  recoil_momentum.assign( raw_recoil_momentum.begin(),
			  raw_recoil_momentum.end() );
  
  scattering_function.assign( raw_scattering_function.begin(),
			      raw_scattering_function.end() );

  // Convert from inverse Angstroms to inverse cm
  for( unsigned i = 0; i < recoil_momentum.size(); ++i )
  {
    recoil_momentum[i] *= 1e8;

    if( recoil_momentum[i] == 0.0 )
      recoil_momentum[i] = std::numeric_limits<double>::min();

    if( scattering_function[i] == 0.0 )
      scattering_function[i] = std::numeric_limits<double>::min();
  }

  data_container.setWallerHartreeScatteringFunctionMomentumGrid(
							     recoil_momentum );
  data_container.setWallerHartreeScatteringFunction( scattering_function );
}

// Set the Waller-Hartree atomic form factor data
void StandardElectronPhotonRelaxationDataGenerator::setWallerHartreeAtomicFormFactorData(
			   Data::ElectronPhotonRelaxationVolatileDataContainer&
			   data_container ) const
{
  Teuchos::ArrayView<const double> jcohe_block = 
    d_ace_epr_data->extractJCOHEBlock();
  
  unsigned form_factor_size = jcohe_block.size()/3;

  Teuchos::ArrayView<const double> raw_recoil_momentum( 
					  jcohe_block( 0, form_factor_size ) );

  Teuchos::ArrayView<const double> raw_form_factor(
			 jcohe_block( 2*form_factor_size, form_factor_size ) );
  
  std::vector<double> recoil_momentum, form_factor;

  recoil_momentum.assign( raw_recoil_momentum.begin(),
			  raw_recoil_momentum.end() );

  form_factor.assign( raw_form_factor.begin(), raw_form_factor.end() );

  // Convert from inverse Angstroms to inverse cm
  for( unsigned i = 0; i < recoil_momentum.size(); ++i )
  {
    recoil_momentum[i] *= 1e8;

    if( recoil_momentum[i] == 0.0 )
      recoil_momentum[i] = std::numeric_limits<double>::min();
    
    if( form_factor[i] == 0.0 )
      form_factor[i] = std::numeric_limits<double>::min();
  }

  data_container.setWallerHartreeAtomicFormFactorMomentumGrid(recoil_momentum);
  data_container.setWallerHartreeAtomicFormFactor( form_factor );
}

// Set the photon data
void StandardElectronPhotonRelaxationDataGenerator::setPhotonData( 
			   Data::ElectronPhotonRelaxationVolatileDataContainer&
			   data_container ) const
{
  // Extract the heating numbers
  Teuchos::RCP<const Utility::OneDDistribution> heating_numbers;

  this->extractCrossSection<Utility::LinLog>( 
				     d_ace_epr_data->extractPhotonEnergyGrid(),
				     d_ace_epr_data->extractLHNMBlock(),
				     heating_numbers );

  // Extract the Waller-Hartree incoherent cross section
  Teuchos::RCP<const Utility::OneDDistribution> waller_hartree_incoherent_cs;

  this->extractCrossSection<Utility::LogLog>( 
			       d_ace_epr_data->extractPhotonEnergyGrid(),
			       d_ace_epr_data->extractIncoherentCrossSection(),
			       waller_hartree_incoherent_cs );

  // Extract the Waller-Hartree coherent cross section
  Teuchos::RCP<const Utility::OneDDistribution> waller_hartree_coherent_cs;

  this->extractCrossSection<Utility::LogLog>( 
				 d_ace_epr_data->extractPhotonEnergyGrid(),
				 d_ace_epr_data->extractCoherentCrossSection(),
				 waller_hartree_coherent_cs );

  // Extract the pair production cross section
  Teuchos::RCP<const Utility::OneDDistribution> pair_production_cs;

  this->extractCrossSection<Utility::LogLog>(
			   d_ace_epr_data->extractPhotonEnergyGrid(),
			   d_ace_epr_data->extractPairProductionCrossSection(),
			   pair_production_cs );

  // Extract the subshell photoelectric effect cross sections
  Teuchos::Array<std::pair<unsigned,Teuchos::RCP<const Utility::OneDDistribution> > >
    subshell_photoelectric_effect_css;

  this->extractSubshellPhotoelectricCrossSections( 
					   subshell_photoelectric_effect_css );
  
  // Create the impulse approx. incoherent cross section evaluators
  Teuchos::Array<std::pair<unsigned,Teuchos::RCP<const SubshellIncoherentCrossSectionEvaluator> > > 
    impulse_approx_incoherent_cs_evaluators;
  
  this->createSubshellImpulseApproxIncoherentCrossSectionEvaluators(
				     data_container,
				     impulse_approx_incoherent_cs_evaluators );

  // Create the union energy grid
  std::cout << " Creating union energy grid";
  std::cout.flush();
  std::list<double> union_energy_grid;
  
  this->initializePhotonUnionEnergyGrid( data_container, union_energy_grid );

  Utility::GridGenerator<Utility::LinLin> 
    union_energy_grid_generator( d_grid_convergence_tol,
				 d_grid_absolute_diff_tol,
				 d_grid_distance_tol );
  
  // Calculate the union energy grid
  boost::function<double (double pz)> grid_function = 
    boost::bind( &Utility::OneDDistribution::evaluate,
		 boost::cref( *heating_numbers ),
		 _1 );

  union_energy_grid_generator.generateInPlace( union_energy_grid,
					       grid_function );
  std::cout << ".";
  std::cout.flush();
  
  grid_function = boost::bind( &Utility::OneDDistribution::evaluate,
			       boost::cref( *waller_hartree_incoherent_cs ),
			       _1 );

  union_energy_grid_generator.generateInPlace( union_energy_grid,
					       grid_function );
  std::cout << ".";
  std::cout.flush();
  
  grid_function = boost::bind( &Utility::OneDDistribution::evaluate,
			       boost::cref( *waller_hartree_coherent_cs ),
			       _1 );
  
  union_energy_grid_generator.generateInPlace( union_energy_grid,
					       grid_function );
  std::cout << ".";
  std::cout.flush();
  
  grid_function = boost::bind( &Utility::OneDDistribution::evaluate,
			       boost::cref( *pair_production_cs ),
			       _1 );

  union_energy_grid_generator.generateInPlace( union_energy_grid,
					       grid_function );
  std::cout << ".";
  std::cout.flush();
  
  for( unsigned i = 0; i < subshell_photoelectric_effect_css.size(); ++i )
  {
    grid_function = boost::bind( 
		   &Utility::OneDDistribution::evaluate,
		   boost::cref( *subshell_photoelectric_effect_css[i].second ),
		   _1 );

    union_energy_grid_generator.generateInPlace( union_energy_grid,
						 grid_function );
    std::cout << ".";
    std::cout.flush();
  }

  for( unsigned i = 0; i < impulse_approx_incoherent_cs_evaluators.size(); ++i)
  {
    grid_function = boost::bind(
	     &SubshellIncoherentCrossSectionEvaluator::evaluateCrossSection,
	     boost::cref( *impulse_approx_incoherent_cs_evaluators[i].second ),
	     _1,
	     d_subshell_incoherent_evaluation_tolerance );

    union_energy_grid_generator.generateInPlace( union_energy_grid,
						 grid_function );
    std::cout << ".";
    std::cout.flush();
  }
  
  std::cout << "done." << std::endl;

  // Set the union energy grid
  std::vector<double> energy_grid;
  energy_grid.assign( union_energy_grid.begin(),
		      union_energy_grid.end() );
  
  data_container.setPhotonEnergyGrid( energy_grid );

  // Create and set the cross sections
  std::vector<double> cross_section;
  unsigned threshold;

  std::cout << " Setting the average heating numbers...";
  std::cout.flush();
  this->createCrossSectionOnUnionEnergyGrid( union_energy_grid,
					     heating_numbers,
					     cross_section,
					     threshold );

  data_container.setAveragePhotonHeatingNumbers( cross_section );
  std::cout << "done." << std::endl;
  
  std::cout << " Setting the Waller-Hartree incoherent cross section...";
  std::cout.flush();
  this->createCrossSectionOnUnionEnergyGrid( union_energy_grid,
					     waller_hartree_incoherent_cs,
					     cross_section,
					     threshold );
  
  data_container.setWallerHartreeIncoherentCrossSection( cross_section );
  data_container.setWallerHartreeIncoherentCrossSectionThresholdEnergyIndex( 
								   threshold );
  std::cout << "done." << std::endl;

  std::cout << " Setting the Waller-Hartree coherent cross section...";
  std::cout.flush();
  this->createCrossSectionOnUnionEnergyGrid( union_energy_grid,
					     waller_hartree_coherent_cs,
					     cross_section,
					     threshold );

  data_container.setWallerHartreeCoherentCrossSection( cross_section );
  data_container.setWallerHartreeCoherentCrossSectionThresholdEnergyIndex(
								   threshold );
  std::cout << "done." << std::endl;

  std::cout << " Setting the pair production cross section...";
  std::cout.flush();
  this->createCrossSectionOnUnionEnergyGrid( union_energy_grid,
					     pair_production_cs,
					     cross_section,
					     threshold );

  data_container.setPairProductionCrossSection( cross_section );
  data_container.setPairProductionCrossSectionThresholdEnergyIndex(
								   threshold );
  std::cout << "done." << std::endl;
  
  for( unsigned i = 0; i < subshell_photoelectric_effect_css.size(); ++i )
  {
    std::cout << " Setting subshell " 
	      << subshell_photoelectric_effect_css[i].first 
	      << " photoelectric cross section...";
    std::cout.flush();
    this->createCrossSectionOnUnionEnergyGrid( 
				   union_energy_grid,
				   subshell_photoelectric_effect_css[i].second,
				   cross_section,
				   threshold );

    data_container.setSubshellPhotoelectricCrossSection( 
				    subshell_photoelectric_effect_css[i].first,
				    cross_section );
    data_container.setSubshellPhotoelectricCrossSectionThresholdEnergyIndex(
				    subshell_photoelectric_effect_css[i].first,
				    threshold );
    std::cout << "done." << std::endl;
  }
  
  for( unsigned i = 0; i < impulse_approx_incoherent_cs_evaluators.size(); ++i)
  {
    std::cout << " Setting subshell "
	      << impulse_approx_incoherent_cs_evaluators[i].first
	      << " impusle approx incoherent cross section...";
    std::cout.flush();
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
    std::cout << "done." << std::endl;
  }
  
  std::cout << " Setting the total photoelectric cross section...";
  std::cout.flush();
  this->calculateTotalPhotoelectricCrossSection( data_container );
  std::cout << "done." << std::endl;
  
  std::cout << " Setting the impulse approx total incoherent cross section...";
  std::cout.flush();
  this->calculateImpulseApproxTotalIncoherentCrossSection( data_container );
  std::cout << "done." << std::endl;

  std::cout << " Setting the Waller-Hartree total cross section...";
  std::cout.flush();
  this->calculateWallerHartreeTotalCrossSection( data_container );
  std::cout << "done." << std::endl;

  std::cout << " Setting the impulse approx total cross section...";
  std::cout.flush();
  this->calculateImpulseApproxTotalCrossSection( data_container );
  std::cout << "done." << std::endl;
}

// Extract the half Compton profile from the ACE table
void StandardElectronPhotonRelaxationDataGenerator::extractHalfComptonProfile( 
				      const unsigned subshell,
				      std::vector<double>& half_momentum_grid,
				      std::vector<double>& half_profile ) const
{
  // Extract the subshell ENDF designators 
  Teuchos::ArrayView<const double> subshell_designators = 
    d_ace_epr_data->extractSubshellENDFDesignators();

  // Extract the raw Compton profile data
  Teuchos::ArrayView<const double> lswd_block = 
    d_ace_epr_data->extractLSWDBlock();

  Teuchos::ArrayView<const double> swd_block = 
    d_ace_epr_data->extractSWDBlock();
  
  // Create the Compton profile subshell converter for this
  Teuchos::RCP<MonteCarlo::ComptonProfileSubshellConverter> converter;
  
  MonteCarlo::ComptonProfileSubshellConverterFactory::createConverter(
						     converter,
						     this->getAtomicNumber() );
  
  // Assign the Compton profile for each subshell
  for( unsigned i = 0; i < subshell_designators.size(); ++i )
  {
    unsigned compton_subshell_index = converter->convertSubshellToIndex(
			      MonteCarlo::convertENDFDesignatorToSubshellEnum( 
						   subshell_designators[i] ) );
    
    unsigned profile_index = lswd_block[compton_subshell_index];

    unsigned grid_size = swd_block[profile_index];
    
    // Extract and modify the profile
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
}

// Extract the subshell photoelectric effect cross section
void StandardElectronPhotonRelaxationDataGenerator::extractSubshellPhotoelectricCrossSections(
	  Teuchos::Array<std::pair<unsigned,Teuchos::RCP<const Utility::OneDDistribution> > >& cross_sections ) const
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

    this->extractCrossSection<Utility::LogLog>( energy_grid,
						raw_subshell_pe_cross_section,
						cross_sections[i].second );
  }
}

// Create the subshell impulse approx incoherent cross section evaluators
void StandardElectronPhotonRelaxationDataGenerator::createSubshellImpulseApproxIncoherentCrossSectionEvaluators(
     const Data::ElectronPhotonRelaxationVolatileDataContainer& data_container,
     Teuchos::Array<std::pair<unsigned,Teuchos::RCP<const SubshellIncoherentCrossSectionEvaluator> > >& evaluators ) const
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
       new Utility::TabularDistribution<Utility::LogLin>( momentum_grid,
							  occupation_number ) );

    evaluators[i].second.reset( new SubshellIncoherentCrossSectionEvaluator( 
		   MonteCarlo::convertENDFDesignatorToSubshellEnum( subshell ),
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
  union_energy_grid.push_back( d_min_photon_energy );
  
  const std::set<unsigned>& subshells = data_container.getSubshells();

  std::set<unsigned>::const_iterator subshell = subshells.begin();

  // Add the subshell binding energies
  while( subshell != subshells.end() )
  {
    double binding_energy = 
      data_container.getSubshellBindingEnergy( *subshell );

    if( binding_energy > d_min_photon_energy )
    {
      union_energy_grid.push_back( binding_energy );
      union_energy_grid.push_back( binding_energy*
				   s_threshold_energy_nudge_factor );
    }

    ++subshell;
  }

  // Add the pair production threshold
  double pp_threshold = 
    2*Utility::PhysicalConstants::electron_rest_mass_energy;

  if( pp_threshold > d_min_photon_energy )
  {
    union_energy_grid.push_back( pp_threshold );
    union_energy_grid.push_back( pp_threshold*
				 s_threshold_energy_nudge_factor );
  }

  // Add the max photon energy
  union_energy_grid.push_back( d_max_photon_energy );

  // Sort the union energy grid
  union_energy_grid.sort();
}

// Create the cross section on the union energy grid
void StandardElectronPhotonRelaxationDataGenerator::createCrossSectionOnUnionEnergyGrid(
   const std::list<double>& union_energy_grid,
   const Teuchos::RCP<const Utility::OneDDistribution>& original_cross_section,
   std::vector<double>& cross_section,
   unsigned& threshold_index ) const
{
  std::vector<double> raw_cross_section( union_energy_grid.size() );
  
  std::list<double>::const_iterator energy_grid_pt = union_energy_grid.begin();
  
  unsigned index = 0u;
  
  while( energy_grid_pt != union_energy_grid.end() )
  {
    raw_cross_section[index] = 
      original_cross_section->evaluate( *energy_grid_pt );

    ++energy_grid_pt;
    ++index;
  }

  std::vector<double>::iterator start = 
    std::find_if( raw_cross_section.begin(),
		  raw_cross_section.end(),
		  notEqualZero );

  cross_section.assign( start, raw_cross_section.end() );

  threshold_index = std::distance( raw_cross_section.begin(), start );
}

// Create the cross section on the union energy grid
void StandardElectronPhotonRelaxationDataGenerator::createCrossSectionOnUnionEnergyGrid(
	     const std::list<double>& union_energy_grid,
	     const Teuchos::RCP<const SubshellIncoherentCrossSectionEvaluator>&
	     original_cross_section,
	     std::vector<double>& cross_section,
	     unsigned& threshold_index ) const
{
  std::vector<double> raw_cross_section( union_energy_grid.size() );
  
  std::list<double>::const_iterator energy_grid_pt = union_energy_grid.begin();
  
  unsigned index = 0u;
  
  while( energy_grid_pt != union_energy_grid.end() )
  {
    raw_cross_section[index] = original_cross_section->evaluateCrossSection( 
				  *energy_grid_pt, 
				  d_subshell_incoherent_evaluation_tolerance );
    
    ++energy_grid_pt;
    ++index;
  }
  
  std::vector<double>::iterator start = 
    std::find_if( raw_cross_section.begin(),
		  raw_cross_section.end(),
		  notEqualZero );

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

  std::vector<double>::iterator start = 
    std::find_if( raw_cross_section.begin(),
		  raw_cross_section.end(),
		  notEqualZero );

  std::vector<double> cross_section;
  cross_section.assign( start, raw_cross_section.end() );

  unsigned threshold = std::distance( raw_cross_section.begin(), start );

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

  std::vector<double>::iterator start = 
    std::find_if( raw_cross_section.begin(),
		  raw_cross_section.end(),
		  notEqualZero );

  std::vector<double> cross_section;
  cross_section.assign( start, raw_cross_section.end() );

  unsigned threshold = std::distance( raw_cross_section.begin(), start );

  data_container.setImpulseApproxIncoherentCrossSection( cross_section );
  data_container.setImpulseApproxIncoherentCrossSectionThresholdEnergyIndex(
								   threshold );
}

// Calculate the Waller-Hartree total cross section
void StandardElectronPhotonRelaxationDataGenerator::calculateWallerHartreeTotalCrossSection(
		          Data::ElectronPhotonRelaxationVolatileDataContainer&
			  data_container ) const
{
  const std::vector<double>& energy_grid = 
    data_container.getPhotonEnergyGrid();

  std::vector<double> cross_section( energy_grid.size(), 0.0 );
  
  const std::vector<double>& incoherent_cs = 
    data_container.getWallerHartreeIncoherentCrossSection();

  unsigned start_index = energy_grid.size() - incoherent_cs.size();

  for( unsigned i = 0; i < incoherent_cs.size(); ++i )
    cross_section[start_index+i] += incoherent_cs[i];
  
  const std::vector<double>& coherent_cs = 
    data_container.getWallerHartreeCoherentCrossSection();

  start_index = energy_grid.size() - coherent_cs.size();

  for( unsigned i = 0; i < coherent_cs.size(); ++i )
    cross_section[start_index+i] += coherent_cs[i];
  
  const std::vector<double>& pair_production_cs = 
    data_container.getPairProductionCrossSection();

  start_index = energy_grid.size() - pair_production_cs.size();

  for( unsigned i = 0; i < pair_production_cs.size(); ++i )
    cross_section[start_index+i] += pair_production_cs[i];

  const std::vector<double>& photoelectric_cs = 
    data_container.getPhotoelectricCrossSection();

  start_index = energy_grid.size() - photoelectric_cs.size();

  for( unsigned i = 0; i < photoelectric_cs.size(); ++i )
    cross_section[start_index+i] += photoelectric_cs[i];
  
  data_container.setWallerHartreeTotalCrossSection( cross_section );
}

// Calculate the impulse approx total cross section
void StandardElectronPhotonRelaxationDataGenerator::calculateImpulseApproxTotalCrossSection(
		          Data::ElectronPhotonRelaxationVolatileDataContainer&
			  data_container ) const
{
  const std::vector<double>& energy_grid = 
    data_container.getPhotonEnergyGrid();

  std::vector<double> cross_section( energy_grid.size(), 0.0 );
  
  const std::vector<double>& incoherent_cs = 
    data_container.getImpulseApproxIncoherentCrossSection();

  unsigned start_index = energy_grid.size() - incoherent_cs.size();
  
  for( unsigned i = 0; i < incoherent_cs.size(); ++i )
    cross_section[start_index+i] += incoherent_cs[i];
  
  const std::vector<double>& coherent_cs = 
    data_container.getWallerHartreeCoherentCrossSection();

  start_index = energy_grid.size() - coherent_cs.size();

  for( unsigned i = 0; i < coherent_cs.size(); ++i )
    cross_section[start_index+i] += coherent_cs[i];
  
  const std::vector<double>& pair_production_cs = 
    data_container.getPairProductionCrossSection();

  start_index = energy_grid.size() - pair_production_cs.size();

  for( unsigned i = 0; i < pair_production_cs.size(); ++i )
    cross_section[start_index+i] += pair_production_cs[i];

  const std::vector<double>& photoelectric_cs = 
    data_container.getPhotoelectricCrossSection();

  start_index = energy_grid.size() - photoelectric_cs.size();

  for( unsigned i = 0; i < photoelectric_cs.size(); ++i )
    cross_section[start_index+i] += photoelectric_cs[i];
  
  data_container.setImpulseApproxTotalCrossSection( cross_section );
}

// Set the electron data
void StandardElectronPhotonRelaxationDataGenerator::setElectronData( 
			   Data::ElectronPhotonRelaxationVolatileDataContainer&
			   data_container ) const
{

}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_StandardElectronPhotonRelaxationDataGenerator.cpp
//---------------------------------------------------------------------------//
