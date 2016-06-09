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
#include "Data_SubshellType.hpp"
#include "Utility_GridGenerator.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_SloanRadauQuadrature.hpp"

namespace DataGen{

// Initialize the static member data
const double StandardElectronPhotonRelaxationDataGenerator::s_threshold_energy_nudge_factor = 1.0001;

// Constructor
StandardElectronPhotonRelaxationDataGenerator::StandardElectronPhotonRelaxationDataGenerator(
        const unsigned atomic_number,
        const Teuchos::RCP<const Data::XSSEPRDataExtractor>& ace_epr_data,
        const Teuchos::RCP<const Data::ENDLDataContainer>&
            endl_data_container,
        const double min_photon_energy,
        const double max_photon_energy,
        const double min_electron_energy,
        const double max_electron_energy,
        const double occupation_number_evaluation_tolerance,
        const double subshell_incoherent_evaluation_tolerance,
        const double cutoff_angle_cosine,
        const unsigned number_of_moment_preserving_angles,
        const double grid_convergence_tol,
        const double grid_absolute_diff_tol,
        const double grid_distance_tol )
  : ElectronPhotonRelaxationDataGenerator( atomic_number ),
    d_ace_epr_data( ace_epr_data ),
    d_endl_data_container( endl_data_container ),
    d_min_photon_energy( min_photon_energy ),
    d_max_photon_energy( max_photon_energy ),
    d_min_electron_energy( min_electron_energy ),
    d_max_electron_energy( max_electron_energy ),
    d_occupation_number_evaluation_tolerance( occupation_number_evaluation_tolerance ),
    d_subshell_incoherent_evaluation_tolerance( subshell_incoherent_evaluation_tolerance ),
    d_cutoff_angle_cosine( cutoff_angle_cosine ),
    d_number_of_moment_preserving_angles( number_of_moment_preserving_angles ),
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
  testPrecondition( cutoff_angle_cosine <= 1.0 );
  testPrecondition( cutoff_angle_cosine > -1.0 );
  // Make sure the number of moment preserving angles is valid
  testPrecondition( number_of_moment_preserving_angles >= 0 );
}

// Populate the electron-photon-relaxation data container
void StandardElectronPhotonRelaxationDataGenerator::populateEPRDataContainer(
			   Data::ElectronPhotonRelaxationVolatileDataContainer&
			   data_container ) const
{
  // Set the table data
  // Set the atomic number
  this->setAtomicNumber( data_container );
  data_container.setMinPhotonEnergy( d_min_photon_energy );
  data_container.setMaxPhotonEnergy( d_max_photon_energy );
  data_container.setMinElectronEnergy( d_min_electron_energy );
  data_container.setMaxElectronEnergy( d_max_electron_energy );
  data_container.setCutoffAngleCosine( d_cutoff_angle_cosine );
  data_container.setOccupationNumberEvaluationTolerance(
    d_occupation_number_evaluation_tolerance );
  data_container.setSubshellIncoherentEvaluationTolerance(
    d_subshell_incoherent_evaluation_tolerance );
  data_container.setGridConvergenceTolerance( d_grid_convergence_tol );
  data_container.setGridAbsoluteDifferenceTolerance( d_grid_absolute_diff_tol );
  data_container.setGridDistanceTolerance( d_grid_distance_tol );

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
/*! \details This function uses the Data::ENDLDataContainer to read the
 * native EEDL data file.
 */
void StandardElectronPhotonRelaxationDataGenerator::setElectronData(
    Data::ElectronPhotonRelaxationVolatileDataContainer& data_container ) const
{
  // cross sections in the file
  Teuchos::RCP<const Utility::OneDDistribution>
        bremsstrahlung_cross_section, atomic_excitation_cross_section,
        cutoff_elastic_cross_section, total_elastic_cross_section;

  Teuchos::Array<std::pair<unsigned,Teuchos::RCP<const Utility::OneDDistribution> > >
        electroionization_cross_section;

  // Initialize union energy grid
  std::list<double> union_energy_grid;
  union_energy_grid.push_back( d_min_electron_energy );
  union_energy_grid.push_back( d_max_electron_energy );

//---------------------------------------------------------------------------//
// Set Elastic Data
//---------------------------------------------------------------------------//
  std::cout << " Setting the elastic cutoff data...";
  std::cout.flush();

  // Get cutoff elastic cross section to union energy grid
  std::vector<double> raw_energy_grid =
    d_endl_data_container->getElasticEnergyGrid();

  this->extractElectronCrossSection<Utility::LogLog>(
    raw_energy_grid,
    d_endl_data_container->getCutoffElasticCrossSection(),
    cutoff_elastic_cross_section );

  // merge raw energy grid with the union energy grid
  mergeElectronUnionEnergyGrid( raw_energy_grid, union_energy_grid );


  // Get total elastic cross section (same energy grid as cutoff)
  this->extractElectronCrossSection<Utility::LogLog>(
    raw_energy_grid,
    d_endl_data_container->getTotalElasticCrossSection(),
    total_elastic_cross_section );


  // Set elastic angular distribution
  std::map<double,std::vector<double> > elastic_pdf, elastic_angle;

  std::vector<double> elastic_energy_grid =
    d_endl_data_container->getCutoffElasticAngularEnergyGrid();

  data_container.setElasticAngularEnergyGrid( elastic_energy_grid );

  /* ENDL gives the angular distribution in terms of the change in angle cosine
   * (delta_angle_cosine = 1 - angle_cosine). For the native format it needs to
   * be in terms of angle_cosine. This for loop flips the distribution and
   * changes the variables to angle_cosine.
   */
  std::vector<double>::iterator energy = elastic_energy_grid.begin();
  for ( energy; energy != elastic_energy_grid.end(); energy++ )
  {
    calculateElasticAngleCosine(
        d_endl_data_container->getCutoffElasticAnglesAtEnergy( *energy ),
        d_endl_data_container->getCutoffElasticPDFAtEnergy( *energy ),
        elastic_angle[*energy],
        elastic_pdf[*energy] );
  }

  data_container.setCutoffElasticPDF( elastic_pdf );
  data_container.setCutoffElasticAngles( elastic_angle );

  std::cout << "done." << std::endl;

  if ( d_cutoff_angle_cosine > 0.999999 )
  {
    std::cout << " Screened Rutherford data will not be generated because the"
              << " cutoff angle cosine is greater than 0.999999." << std::endl
              << " cutoff_angle_cosine = " << d_cutoff_angle_cosine << std::endl;

    std::cout << " Moment preserving data will not be generated because the"
              << " cutoff angle cosine is greater than 0.999999." << std::endl
              << " cutoff_angle_cosine = " << d_cutoff_angle_cosine << std::endl;
  }
  else if ( d_number_of_moment_preserving_angles < 1 )
  {
    std::cout << " Setting the elastic screened Rutherford data...";
    std::cout.flush();
    // Set the screened Rutherford data
    setScreenedRutherfordData( cutoff_elastic_cross_section,
                               total_elastic_cross_section,
                               elastic_energy_grid,
                               elastic_pdf,
                               data_container );

    std::cout << "done." << std::endl;

    std::cout << " Moment preserving data will not be generated because the"
              << " number of moment preserving angles is less than 1." << std::endl
              << " number_of_moment_preserving_angles = "
              << d_number_of_moment_preserving_angles << std::endl;
  }
  else
  {
    std::cout << " Setting the elastic screened Rutherford data...";
    std::cout.flush();
    // Set the screened Rutherford data
    setScreenedRutherfordData( cutoff_elastic_cross_section,
                               total_elastic_cross_section,
                               elastic_energy_grid,
                               elastic_pdf,
                               data_container );

    std::cout << "done." << std::endl;

    std::cout << " Setting the elastic moment preserving data...";
    std::cout.flush();
    // Set the moment preserving data
    setMomentPreservingData( elastic_energy_grid, data_container );
    std::cout << "done." << std::endl;
  }

//---------------------------------------------------------------------------//
// Set Electroionization Data
//---------------------------------------------------------------------------//

  std::set<unsigned>::iterator shell = data_container.getSubshells().begin();

  // Loop through electroionization data for every subshell
  for ( shell; shell != data_container.getSubshells().end(); shell++ )
  {
    Teuchos::RCP<const Utility::OneDDistribution> subshell_cross_section;

    raw_energy_grid =
        d_endl_data_container->getElectroionizationCrossSectionEnergyGrid( *shell );

    this->extractElectronCrossSection<Utility::LinLin>(
        raw_energy_grid,
        d_endl_data_container->getElectroionizationCrossSection( *shell ),
        subshell_cross_section );

    // merge raw energy grid with the union energy grid
    mergeElectronUnionEnergyGrid( raw_energy_grid, union_energy_grid );

    electroionization_cross_section.push_back(
        std::make_pair( *shell, subshell_cross_section ) );

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

//---------------------------------------------------------------------------//
// Set Bremsstrahlung Data
//---------------------------------------------------------------------------//

  raw_energy_grid =
    d_endl_data_container->getBremsstrahlungCrossSectionEnergyGrid();

  this->extractElectronCrossSection<Utility::LinLin>(
        raw_energy_grid,
        d_endl_data_container->getBremsstrahlungCrossSection(),
        bremsstrahlung_cross_section );

  // merge raw energy grid with the union energy grid
  mergeElectronUnionEnergyGrid( raw_energy_grid, union_energy_grid );

  data_container.setBremsstrahlungEnergyGrid(
    d_endl_data_container->getBremsstrahlungPhotonEnergyGrid() );

  data_container.setBremsstrahlungPhotonEnergy(
    d_endl_data_container->getBremsstrahlungPhotonEnergy() );

  data_container.setBremsstrahlungPhotonPDF(
    d_endl_data_container->getBremsstrahlungPhotonPDF() );


//---------------------------------------------------------------------------//
// Set Atomic Excitation Data
//---------------------------------------------------------------------------//

  raw_energy_grid = d_endl_data_container->getAtomicExcitationEnergyGrid();

  this->extractElectronCrossSection<Utility::LinLin>(
    raw_energy_grid,
    d_endl_data_container->getAtomicExcitationCrossSection(),
    atomic_excitation_cross_section );

  // merge raw energy grid with the union energy grid
  mergeElectronUnionEnergyGrid( raw_energy_grid, union_energy_grid );

  // Set atomic excitation energy loss
  data_container.setAtomicExcitationEnergyGrid( raw_energy_grid );
  data_container.setAtomicExcitationEnergyLoss(
    d_endl_data_container->getAtomicExcitationEnergyLoss() );

//---------------------------------------------------------------------------//
// Create union energy grid and calculate cross sections
//---------------------------------------------------------------------------//

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
  }
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
{

}

// Set the screened rutherford data
void StandardElectronPhotonRelaxationDataGenerator::setMomentPreservingData(
    const std::vector<double>& elastic_energy_grid,
    Data::ElectronPhotonRelaxationVolatileDataContainer& data_container ) const
{
  // Create the moment evaluator of the elastic scattering distribution
  Teuchos::RCP<DataGen::ElasticElectronMomentsEvaluator> moments_evaluator;
  moments_evaluator.reset(
    new DataGen::ElasticElectronMomentsEvaluator( data_container,
                                                  d_cutoff_angle_cosine ) );

  std::vector<double> discrete_angles, weights;

  // iterate through all angular energy bins
  for ( unsigned i = 0; i < elastic_energy_grid.size(); i++ )
  {
    evaluateDisceteAnglesAndWeights(
        moments_evaluator,
        elastic_energy_grid[i],
        discrete_angles,
        weights );

    data_container.setMomentPreservingElasticDiscreteAngles(
        elastic_energy_grid[i],
        discrete_angles );
    data_container.setMomentPreservingElasticWeights(
        elastic_energy_grid[i],
        weights );
  }
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

// Generate elastic discrete angle cosines and weights
void StandardElectronPhotonRelaxationDataGenerator::evaluateDisceteAnglesAndWeights(
    const Teuchos::RCP<DataGen::ElasticElectronMomentsEvaluator>& moments_evaluator,
    const double& energy,
    std::vector<double>& discrete_angles,
    std::vector<double>& weights ) const
{
  std::vector<Utility::long_float> legendre_moments;
  double precision = 1e-13;
  int n = ( d_number_of_moment_preserving_angles+1 )*2 -2;

  // Get the discrete angles and weights
  moments_evaluator->evaluateElasticMoment( legendre_moments,
                                            energy,
                                            n,
                                            precision );

  // Use radau quadrature to find the discrete angles and weights from the moments
  Teuchos::RCP<Utility::SloanRadauQuadrature> radau_quadrature(
      new Utility::SloanRadauQuadrature( legendre_moments ) );

  radau_quadrature->getRadauNodesAndWeights( discrete_angles,
                                             weights,
                                             d_number_of_moment_preserving_angles+1 );
}


} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_StandardElectronPhotonRelaxationDataGenerator.cpp
//---------------------------------------------------------------------------//
