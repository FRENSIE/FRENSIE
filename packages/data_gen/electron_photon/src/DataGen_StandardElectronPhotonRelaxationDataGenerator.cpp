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
        const Teuchos::RCP<Data::ENDLFileHandler>& eedl_file_handler,
        const double min_photon_energy,
        const double max_photon_energy,
        const double min_electron_energy,
        const double max_electron_energy,
        const double cutoff_angle,
        const double occupation_number_evaluation_tolerance,
        const double subshell_incoherent_evaluation_tolerance,
        const double grid_convergence_tol,
        const double grid_absolute_diff_tol,
        const double grid_distance_tol )
  : ElectronPhotonRelaxationDataGenerator( atomic_number ),
    d_ace_epr_data( ace_epr_data ),
    d_eedl_file_handler( eedl_file_handler ),
    d_min_photon_energy( min_photon_energy ),
    d_max_photon_energy( max_photon_energy ),
    d_min_electron_energy( min_electron_energy ),
    d_max_electron_energy( max_electron_energy ),
    d_cutoff_angle( cutoff_angle ),
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
  // Make sure the electron energy limits are valid
  testPrecondition( min_electron_energy > 0.0 );
  testPrecondition( min_electron_energy < max_electron_energy );
  // Make sure the cutoff angle is valid
  testPrecondition( cutoff_angle >= 0.0 );
  testPrecondition( cutoff_angle < 2.0 );
}

// Populate the electron-photon-relaxation data container
void StandardElectronPhotonRelaxationDataGenerator::populateEPRDataContainer(
			   Data::ElectronPhotonRelaxationVolatileDataContainer&
			   data_container ) const
{
  // Set the atomic number
  this->setAtomicNumber( data_container );
/*
  // Set cutoff angle
  data_container.setCutoffAngle( d_cutoff_angle );
*/
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
  std::cout << "Setting the electron data: " << std::endl;
  this->setElectronData( data_container );
  std::cout << "done." << std::endl;

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
						  true,
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
					 jince_block( 1, scatt_func_size-1 ) );

  Teuchos::ArrayView<const double> raw_scattering_function(
			 jince_block( scatt_func_size+1, scatt_func_size-1 ) );

  std::vector<double> scaled_recoil_momentum;
  
  scaled_recoil_momentum.assign( raw_recoil_momentum.begin(),
				 raw_recoil_momentum.end() );
  
  // Convert from inverse Angstroms to inverse cm
  for( unsigned i = 0; i < scaled_recoil_momentum.size(); ++i )
    scaled_recoil_momentum[i] *= 1e8;

  Teuchos::RCP<Utility::OneDDistribution> scattering_function_dist( 
              new Utility::TabularDistribution<Utility::LogLog>( 
						   scaled_recoil_momentum,
						   raw_scattering_function ) );

  boost::function<double (double x)> grid_function = 
    boost::bind( &Utility::OneDDistribution::evaluate,
		 boost::cref( *scattering_function_dist ),
		 _1 );

  Utility::GridGenerator<Utility::LinLin> 
    scattering_func_grid_generator( d_grid_convergence_tol,
				    d_grid_absolute_diff_tol,
				    d_grid_distance_tol );

  std::list<double> recoil_momentum_grid, scattering_function;
  recoil_momentum_grid.push_back( scaled_recoil_momentum.front() );
  recoil_momentum_grid.push_back( scaled_recoil_momentum.back() );

  scattering_func_grid_generator.generateAndEvaluateInPlace( 
							  recoil_momentum_grid,
							  scattering_function,
							  grid_function );

  recoil_momentum_grid.push_front( jince_block[0]*1e8 );
  scattering_function.push_front( jince_block[scatt_func_size] );

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
  Teuchos::ArrayView<const double> jcohe_block = 
    d_ace_epr_data->extractJCOHEBlock();
  
  unsigned form_factor_size = jcohe_block.size()/3;

  Teuchos::ArrayView<const double> raw_recoil_momentum( 
					jcohe_block( 1, form_factor_size-1 ) );

  Teuchos::ArrayView<const double> raw_form_factor(
		     jcohe_block( 2*form_factor_size+1, form_factor_size-1 ) );
  
  std::vector<double> scaled_recoil_momentum;

  scaled_recoil_momentum.assign( raw_recoil_momentum.begin(),
				 raw_recoil_momentum.end() );

  // Convert from inverse Angstroms to inverse cm
  for( unsigned i = 0; i < scaled_recoil_momentum.size(); ++i )
    scaled_recoil_momentum[i] *= 1e8;

  Teuchos::RCP<Utility::OneDDistribution> form_factor_dist(
			    new Utility::TabularDistribution<Utility::LogLog>(
						        scaled_recoil_momentum,
							raw_form_factor ) );

  boost::function<double (double x)> grid_function = 
    boost::bind( &Utility::OneDDistribution::evaluate,
		 boost::cref( *form_factor_dist ),
		 _1 );

  Utility::GridGenerator<Utility::LinLin>
    form_factor_grid_generator( d_grid_convergence_tol,
				d_grid_absolute_diff_tol,
				d_grid_distance_tol );

  std::list<double> recoil_momentum_grid, form_factor;
  recoil_momentum_grid.push_back( scaled_recoil_momentum.front() );
  recoil_momentum_grid.push_back( scaled_recoil_momentum.back() );

  form_factor_grid_generator.generateAndEvaluateInPlace( recoil_momentum_grid,
							 form_factor,
							 grid_function );

  recoil_momentum_grid.push_front( jcohe_block.front()*1e8 );
  recoil_momentum_grid.push_back( jcohe_block[form_factor_size-1]*1e8 );
  
  form_factor.push_front( jcohe_block[2*form_factor_size] );
  form_factor.push_back( jcohe_block.back() );

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
  Teuchos::Array<std::pair<unsigned,Teuchos::RCP<const MonteCarlo::SubshellIncoherentPhotonScatteringDistribution> > > 
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
	     &MonteCarlo::SubshellIncoherentPhotonScatteringDistribution::evaluateIntegratedCrossSection,
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


// Process EEDL file
/*! \details This function uses the Data::ENDLFileHandler to read the
 * EEDL data file. The data that is read is then processed into an appropriate
 * format and finally stored in the necessary HDF5 file. 
 */
void StandardElectronPhotonRelaxationDataGenerator::setElectronData( 
    Data::ElectronPhotonRelaxationVolatileDataContainer& data_container ) const
{ /*
  // Information in first header of the EEDL file
  int atomic_number_in_table, 
      outgoing_particle_designator, 
      interpolation_flag;
  double atomic_weight;

  // Information in the second header of the EEDL file
  int reaction_type, electron_shell;
  unsigned subshell_endf;

  // array of all the subshells read
  std::set<unsigned> endf_subshells = data_container.getSubshells();

  // cross sections in the file
  Teuchos::RCP<const Utility::OneDDistribution>  
        bremsstrahlung_cross_section, atomic_excitation_cross_section,
        cutoff_elastic_cross_section, total_elastic_cross_section;

  Teuchos::Array<std::pair<unsigned,Teuchos::RCP<const Utility::OneDDistribution> > >
        electroionization_cross_section;

  // The elastic angular distribution energy grid and pdf
  std::vector<double> elastic_energy_grid;
  std::map<double,std::vector<double> > elastic_pdf;

  // Initialize union energy grid
  std::list<double> union_energy_grid;
  union_energy_grid.push_back( d_min_electron_energy );
  union_energy_grid.push_back( d_max_electron_energy );


  std::cout << " Reading EEDL Data file";
  std::cout.flush();

  // Process every table in the EEDL file
  while( d_eedl_file_handler->validFile() && !d_eedl_file_handler->endOfFile() )
  {
    // Read first table header and determine which element is being processed
    d_eedl_file_handler->readFirstTableHeader( atomic_number_in_table,
                                              outgoing_particle_designator,
                                              atomic_weight,
                                              interpolation_flag );
    
    // Check that the EEDL file is still valid (eof has not been reached)
    if( d_eedl_file_handler->endOfFile() )
    {
	  continue;
    }
      
    testPostcondition( atomic_number_in_table == 
                       data_container.getAtomicNumber() );

    // Read second table header and determine the reaction type
    d_eedl_file_handler->readSecondTableHeader( reaction_type,
                                                electron_shell );

    if ( electron_shell > 0 )
    {
      // Convert subshell number to endf number
      subshell_endf = 
        MonteCarlo::convertEADLDesignatorToENDFDesignator( electron_shell );

      // Check that subshell is valid
      testPrecondition( endf_subshells.count( subshell_endf ) );
      
    }

    // Read and process the data in the current table, then store in the HDF5
    // file
    switch( reaction_type )
    {
  
    case 7000:
      // Integrated elastic transport cross section data - ignored
      
      d_eedl_file_handler->skipTable();

      std::cout << ".";
      std::cout.flush();   
      break;

    case 8000:
    {
      // Interpolation should always be LogLog = 5 
      testPrecondition( interpolation_flag == 5 )

      // Extract in the integrated large angle scattering cross section data
      std::vector<double> raw_energy_grid, raw_cross_section;
      d_eedl_file_handler->processTwoColumnTable( raw_energy_grid, 
                                                  raw_cross_section );

      this->extractElectronCrossSection<Utility::LogLog>( 
                raw_energy_grid,
                raw_cross_section,
                cutoff_elastic_cross_section );

      // merge raw energy grid with the union energy grid
      mergeElectronUnionEnergyGrid( raw_energy_grid, union_energy_grid );


      std::cout << ".";
      std::cout.flush();     
      break;
    }
    case 8011:
      // Average energy to residual atom from elastic scattering - ignored
      
      d_eedl_file_handler->skipTable();

      std::cout << ".";
      std::cout.flush(); 
      break;

    case 8010:
      // Average energy of scattered electron from elastic scattering - ignored
      
      d_eedl_file_handler->skipTable();

      std::cout << ".";
      std::cout.flush();    
      break;


    case 8022:
    {
      // Read in the elastic angular distribution of the scattered electron data

      // Interpolation should always be LinLin = 0 
      testPrecondition( interpolation_flag == 0 )

      std::map<double,std::vector<double> > elastic_angle;

      d_eedl_file_handler->processThreeColumnTable( 
            elastic_energy_grid, 
            elastic_angle,
            elastic_pdf );

      data_container.setElasticAngularEnergyGrid( elastic_energy_grid );
      data_container.setAnalogElasticAngles( elastic_angle );
      data_container.setAnalogElasticPDF( elastic_pdf ); 

      std::cout << ".";
      std::cout.flush(); 
      break;
    }
    case 10000:
    {
      // Extract in the integrated total elastic cross section data

      // Interpolation should always be LogLog = 5 
      testPrecondition( interpolation_flag == 5 )

      std::vector<double> raw_energy_grid, raw_cross_section;
      d_eedl_file_handler->processTwoColumnTable( raw_energy_grid, 
                                                  raw_cross_section );

      this->extractElectronCrossSection<Utility::LogLog>( 
                raw_energy_grid,
                raw_cross_section,
                total_elastic_cross_section );

      // merge raw energy grid with the union energy grid
      mergeElectronUnionEnergyGrid( raw_energy_grid, union_energy_grid );

      std::cout << ".";
      std::cout.flush(); 
      break;
    }
    case 81000:
    {
      // Extract the integrated ionization cross section

      // Interpolation should always be LinLin = 0 
      testPrecondition( interpolation_flag == 0 )

      std::vector<double> raw_energy_grid, raw_cross_section;
      d_eedl_file_handler->processTwoColumnTable( raw_energy_grid, 
                                                  raw_cross_section );

      Teuchos::RCP<const Utility::OneDDistribution> subshell_cross_section;

      this->extractElectronCrossSection<Utility::LinLin>( 
                raw_energy_grid,
                raw_cross_section,
                subshell_cross_section );

      // merge raw energy grid with the union energy grid
      mergeElectronUnionEnergyGrid( raw_energy_grid, union_energy_grid );

      std::pair<unsigned,Teuchos::RCP<const Utility::OneDDistribution> >
        cross_section_pair( subshell_endf, subshell_cross_section );

      electroionization_cross_section.push_back( cross_section_pair );


      std::cout << ".";
      std::cout.flush();     
      break;
    }
    case 81010:

      // Average energy of electron from ionization - ignored
      // ( Yo == 9 )
      // Average energy of secondary electron from ionization - ignored
      // ( Yo == 19 )

      d_eedl_file_handler->skipTable();

      std::cout << ".";
      std::cout.flush(); 
      break;

    case 81021:
    {
      // Interpolation should always be LinLin = 0 
      testPrecondition( interpolation_flag == 0 )
      // The outgoing particle designator should be electron as recoil (19)
      testPrecondition( outgoing_particle_designator == 19 );

      std::vector<double> electron_energy_grid;
      std::map<double,std::vector<double> > electroionization_recoil_energy,
                                            electroionization_recoil_pdf;

      // Read the recoil electron spectrum from ionization for a subshell
      // If electron_shell == 0 then no subshell data only total

      d_eedl_file_handler->processThreeColumnTable( 
            electron_energy_grid, 
            electroionization_recoil_energy,
            electroionization_recoil_pdf );  


      data_container.setElectroionizationEnergyGrid( 
                        subshell_endf,
                        electron_energy_grid );

      data_container.setElectroionizationRecoilEnergy( 
                        subshell_endf,
                        electroionization_recoil_energy );

      data_container.setElectroionizationRecoilPDF( 
                        subshell_endf,
                        electroionization_recoil_pdf );

      std::cout << ".";
      std::cout.flush(); 
      break;
    }
    case 82000:
    {
      // Interpolation should always be LinLin = 0 
      testPrecondition( interpolation_flag == 0 )

      // Extract the integrated bremsstrahlung cross section
      std::vector<double> raw_energy_grid, raw_cross_section;
      d_eedl_file_handler->processTwoColumnTable( raw_energy_grid, 
                                                  raw_cross_section );

      this->extractElectronCrossSection<Utility::LinLin>( 
                raw_energy_grid,
                raw_cross_section,
                bremsstrahlung_cross_section );

      // merge raw energy grid with the union energy grid
      mergeElectronUnionEnergyGrid( raw_energy_grid, union_energy_grid );

      std::cout << ".";
      std::cout.flush();     
      break;
    }
    case 82010:
      // Average energy of secondary photon from bremsstrahlung - ignored
      // ( Yo == 7 )
      // Average energy of secondary electron from bremsstrahlung - ignored
      // ( Yo == 9 )
      
      d_eedl_file_handler->skipTable();

      std::cout << ".";
      std::cout.flush(); 
      break;

    case 82021:
    {
      // Read the sprectrum of the secondary photon from bremsstrahlung

      // Interpolation should always be LinLin = 0 
      testPrecondition( interpolation_flag == 0 )
      // The outgoing particle designator should be photon (7)
      testPrecondition( outgoing_particle_designator == 7 );

      std::vector<double> electron_energy_grid;
      std::map<double,std::vector<double> > bremsstrahlung_photon_energy,
                                            bremsstrahlung_photon_pdf;

      d_eedl_file_handler->processThreeColumnTable( 
            electron_energy_grid, 
            bremsstrahlung_photon_energy,
            bremsstrahlung_photon_pdf );  

      data_container.setBremsstrahlungEnergyGrid( electron_energy_grid );

      data_container.setBremsstrahlungPhotonEnergy( 
                        bremsstrahlung_photon_energy );

      data_container.setBremsstrahlungPhotonPDF( 
                        bremsstrahlung_photon_pdf );

      std::cout << ".";
      std::cout.flush();    
      break;
    }
    case 83000:
    {
      // Extract the integrated excitation cross section

      // Interpolation should always be LinLin = 0 
      testPrecondition( interpolation_flag == 0 )

      std::vector<double> raw_energy_grid, raw_cross_section;
      d_eedl_file_handler->processTwoColumnTable( raw_energy_grid, 
                                                  raw_cross_section );

      this->extractElectronCrossSection<Utility::LinLin>( 
                raw_energy_grid,
                raw_cross_section,
                atomic_excitation_cross_section );

      // merge raw energy grid with the union energy grid
      mergeElectronUnionEnergyGrid( raw_energy_grid, union_energy_grid );

      std::cout << ".";
      std::cout.flush(); 
      break;
    }
    case 83011:
    {
      // Read the average energy loss from excitation
      testPrecondition( interpolation_flag == 0 );

      std::vector<double> atomic_excitation_energy_grid, 
                          atomic_excitation_energy_loss; 

      d_eedl_file_handler->processTwoColumnTable( 
            atomic_excitation_energy_grid, 
            atomic_excitation_energy_loss );

      data_container.setAtomicExcitationEnergyGrid( 
            atomic_excitation_energy_grid );

      data_container.setAtomicExcitationEnergyLoss( 
            atomic_excitation_energy_loss );

      std::cout << ".";
      std::cout.flush();     
      break;
    }
    default:
      // Unknown reaction type found
      {
	bool known_reaction_type = false;
	std::cout << known_reaction_type <<
    " Fatal Error: An unknown reaction type was encountered while processing the EEDL file.";
    std::cout.flush();
      }
      break;
    }
  }
  // Close the EEDL file
  d_eedl_file_handler->closeENDLFile();

  std::cout << "done." << std::endl;

/*
  // Set the screened Rutherford cross section data
  setScreenedRutherfordData( cutoff_elastic_cross_section, 
                             total_elastic_cross_section,
                             elastic_energy_grid, 
                             elastic_pdf,
                             data_container );
*//*
  // Create the union energy grid
  std::cout << " Creating union energy grid";
  std::cout.flush();


  Utility::GridGenerator<Utility::LinLin> 
    union_energy_grid_generator( d_grid_convergence_tol,
                                 d_grid_absolute_diff_tol,
                                 d_grid_distance_tol );
  
  // Calculate the union energy grid
  boost::function<double (double pz)> grid_function = 
    boost::bind( &Utility::OneDDistribution::evaluate,
                 boost::cref( *cutoff_elastic_cross_section ),
                 _1 );

  union_energy_grid_generator.generateInPlace( union_energy_grid,
                                               grid_function );

  std::cout << ".";
  std::cout.flush(); 
  
  grid_function = boost::bind( 
        &Utility::OneDDistribution::evaluate,
        boost::cref( *total_elastic_cross_section ),
        _1 );
  
  union_energy_grid_generator.generateInPlace( union_energy_grid,
                                               grid_function );
  std::cout << ".";
  std::cout.flush(); 

  grid_function = boost::bind( &Utility::OneDDistribution::evaluate,
			                   boost::cref( *bremsstrahlung_cross_section ),
			                   _1 );
  
  union_energy_grid_generator.generateInPlace( union_energy_grid,
                                               grid_function );
  std::cout << ".";
  std::cout.flush();

  grid_function = boost::bind( &Utility::OneDDistribution::evaluate,
			                   boost::cref( *atomic_excitation_cross_section ),
			                   _1 );

  union_energy_grid_generator.generateInPlace( union_energy_grid,
                                               grid_function );
  std::cout << ".";
  std::cout.flush(); 

  for( unsigned i = 0; i < electroionization_cross_section.size(); ++i )
  {
    grid_function = boost::bind( 
		   &Utility::OneDDistribution::evaluate,
		   boost::cref( *electroionization_cross_section[i].second ),
		   _1 );

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
  
  data_container.setElectronEnergyGrid( energy_grid );


  // Create and set the cross sections
  std::vector<double> cross_section;
  unsigned threshold;

  {
  // Set Elastic cross section data
  std::vector<double> cutoff_cross_section, total_cross_section;

  std::cout << " Setting the cutoff elastic cross section...";
  std::cout.flush();
  this->createCrossSectionOnUnionEnergyGrid( union_energy_grid,
                                             cutoff_elastic_cross_section,
                                             cutoff_cross_section,
                                             threshold );
  data_container.setCutoffElasticCrossSection( cutoff_cross_section );
  data_container.setCutoffElasticCrossSectionThresholdEnergyIndex( threshold ); 
  std::cout << "done." << std::endl;


  std::cout << " Setting the screened Rutherford elastic cross section...";
  std::cout.flush();
  this->createCrossSectionOnUnionEnergyGrid( union_energy_grid,
                                             total_elastic_cross_section,
                                             total_cross_section,
                                             threshold );

  std::vector<double> raw_cross_section( total_cross_section.size() );
  for ( int i = 0; i < total_cross_section.size(); ++i )
  {
    raw_cross_section[i] = total_cross_section[i] - cutoff_cross_section[i];

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
  std::cout << "done." << std::endl;
  }


  std::cout << " Setting the bremsstrahlung cross section...";
  std::cout.flush();
  this->createCrossSectionOnUnionEnergyGrid( union_energy_grid,
                                             bremsstrahlung_cross_section,
                                             cross_section,
                                             threshold );

  data_container.setBremsstrahlungCrossSection( cross_section );
  data_container.setBremsstrahlungCrossSectionThresholdEnergyIndex( threshold ); 
  std::cout << "done." << std::endl;


  std::cout << " Setting the atomic excitation cross section...";
  std::cout.flush();
  this->createCrossSectionOnUnionEnergyGrid( union_energy_grid,
                                             atomic_excitation_cross_section,
                                             cross_section,
                                             threshold );

  data_container.setAtomicExcitationCrossSection( cross_section );
  data_container.setAtomicExcitationCrossSectionThresholdEnergyIndex( 
                    threshold ); 
  std::cout << "done." << std::endl;
  

  for( unsigned i = 0; i < electroionization_cross_section.size(); ++i )
  {
    std::cout << " Setting subshell " 
	      << electroionization_cross_section[i].first 
	      << " electroionization cross section...";
    std::cout.flush();
    this->createCrossSectionOnUnionEnergyGrid( 
				   union_energy_grid,
				   electroionization_cross_section[i].second,
				   cross_section,
				   threshold );

    data_container.setElectroionizationCrossSection( 
				    electroionization_cross_section[i].first,
				    cross_section );
    data_container.setElectroionizationCrossSectionThresholdEnergyIndex(
				    electroionization_cross_section[i].first,
				    threshold );
    std::cout << "done." << std::endl;
  }*/
}


// Set the screened rutherford data
void StandardElectronPhotonRelaxationDataGenerator::setScreenedRutherfordData( 
    const Teuchos::RCP<const Utility::OneDDistribution>& 
        cutoff_elastic_cross_section, 
    const Teuchos::RCP<const Utility::OneDDistribution>& 
        total_elastic_cross_section,
    const std::vector<double>& elastic_energy_grid,
    const std::map<double,std::vector<double> >& elastic_pdf,
    Data::ElectronPhotonRelaxationVolatileDataContainer& data_container ) const
{/*
  // Calculate Moliere's screening constant and the screened rutherford normalization constant
  std::vector<double> moliere_screening_constant, 
                      screened_rutherford_normalization_constant;
  
  // iterate through all angular energy bins
  for ( int i = 0; i < elastic_energy_grid.size(); ++i )
  {
    // get the angular energy bin
    double energy = elastic_energy_grid[i];

    // get the screened rutherford cross section
    double sr_cross_section = 
        ( total_elastic_cross_section->evaluate( energy ) -
        cutoff_elastic_cross_section->evaluate( energy ) );

    if ( sr_cross_section == 0.0 )
    {
    /* in order to not calculate negative the screened Rutherford cross section
     * must be greater than ( cutoff_pdf*cutoff_angle ). It should also be small
     * enough to give a negligable contribution to the overall cross section.
     * This can be accomplished by setting eta slightly greater then the cutoff
     * angle.
     *//*
    // get the pdf value at the cutoff angle for the given energy
    double cutoff_pdf = elastic_pdf.find( energy )->second.front(); 

    // calculate Moliere's screening constant
    moliere_screening_constant.push_back( 1.01*d_cutoff_angle );

    // calculate the screened rutherford normalization constant
    screened_rutherford_normalization_constant.push_back( cutoff_pdf*
        ( 2.01*d_cutoff_angle )*( 2.01*d_cutoff_angle ) );
    }
    else
    {
    // get the pdf value at the cutoff angle for the given energy
    double cutoff_pdf = elastic_pdf.find( energy )->second.front(); 

    // calculate Moliere's screening constant
    moliere_screening_constant.push_back( d_cutoff_angle/( 
        sr_cross_section/( d_cutoff_angle*cutoff_pdf ) - 1.0 ) );

    // calculate the screened rutherford normalization constant
    screened_rutherford_normalization_constant.push_back( cutoff_pdf*( 
        ( d_cutoff_angle + moliere_screening_constant.back() )* 
        ( d_cutoff_angle + moliere_screening_constant.back() ) ) );
    }
  }
  // Set Moliere's screening constant
  data_container.setMoliereScreeningConstant( moliere_screening_constant );

  // Set the screened rutherford normalization constant
  data_container.setScreenedRutherfordNormalizationConstant( 
    screened_rutherford_normalization_constant );  */
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
  Teuchos::RCP<MonteCarlo::ComptonProfileSubshellConverter> converter;
  
  MonteCarlo::ComptonProfileSubshellConverterFactory::createConverter(
						     converter,
						     this->getAtomicNumber() );
  
  unsigned compton_subshell_index = converter->convertSubshellToIndex(
			      MonteCarlo::convertENDFDesignatorToSubshellEnum( 
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
     Teuchos::Array<std::pair<unsigned,Teuchos::RCP<const MonteCarlo::SubshellIncoherentPhotonScatteringDistribution> > >& evaluators ) const
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
  while ( *union_energy_grid.begin() < d_min_electron_energy )
  {
      union_energy_grid.pop_front();
  }

  // Make sure the union energy grid values are unique
  union_energy_grid.unique();
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
	     const Teuchos::RCP<const MonteCarlo::SubshellIncoherentPhotonScatteringDistribution>&
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

} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_StandardElectronPhotonRelaxationDataGenerator.cpp
//---------------------------------------------------------------------------//
