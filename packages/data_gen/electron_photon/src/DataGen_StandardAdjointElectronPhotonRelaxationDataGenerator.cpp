//---------------------------------------------------------------------------//
//!
//! \file   DataGen_StandardAdjointElectronPhotonRelaxationDataGenerator.hpp
//! \author Luke Kersting
//! \brief  The standard adjoint electron-photon-relaxation data generator class def.
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// FRENSIE Includes
#include "DataGen_StandardAdjointElectronPhotonRelaxationDataGenerator.hpp"
#include "DataGen_AdjointBremsstrahlungCrossSectionEvaluator.hpp"
#include "DataGen_MomentPreservingElectronDataGenerator.hpp"
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_ElectroatomicReactionNativeFactory.hpp"
#include "MonteCarlo_AnalogElasticElectroatomicReaction.hpp"
#include "MonteCarlo_BremsstrahlungElectronScatteringDistribution.hpp"
#include "MonteCarlo_BremsstrahlungElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_BremsstrahlungElectroatomicReaction.hpp"
#include "Data_SubshellType.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_GridGenerator.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_SloanRadauQuadrature.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"

namespace DataGen{

// Initialize the static member data
const double StandardAdjointElectronPhotonRelaxationDataGenerator::s_threshold_energy_nudge_factor = 1.0001;

// Constructor
StandardAdjointElectronPhotonRelaxationDataGenerator::StandardAdjointElectronPhotonRelaxationDataGenerator(
        const unsigned atomic_number,
        const std::shared_ptr<const Data::ElectronPhotonRelaxationDataContainer>& forward_native_data,
        const double min_photon_energy,
        const double max_photon_energy,
        const double min_electron_energy,
        const double max_electron_energy,
        const double cutoff_angle_cosine,
        const unsigned number_of_moment_preserving_angles,
        const double grid_convergence_tol,
        const double grid_absolute_diff_tol,
        const double grid_distance_tol )
  : AdjointElectronPhotonRelaxationDataGenerator( atomic_number ),
    d_forward_native_data( forward_native_data ),
    d_min_photon_energy( min_photon_energy ),
    d_max_photon_energy( max_photon_energy ),
    d_min_electron_energy( min_electron_energy ),
    d_max_electron_energy( max_electron_energy ),
    d_cutoff_angle_cosine( cutoff_angle_cosine ),
    d_number_of_moment_preserving_angles( number_of_moment_preserving_angles ),
    d_grid_convergence_tol( grid_convergence_tol ),
    d_grid_absolute_diff_tol( grid_absolute_diff_tol ),
    d_grid_distance_tol( grid_distance_tol )
{
  // Make sure the atomic number is valid
  testPrecondition( atomic_number <= 100u );
  // Make sure the native forward data is valid
  testPrecondition( forward_native_data.use_count() > 0 );
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

// Constructor with moment preserving data
StandardAdjointElectronPhotonRelaxationDataGenerator::StandardAdjointElectronPhotonRelaxationDataGenerator(
        const unsigned atomic_number,
        const std::shared_ptr<const Data::ENDLDataContainer>& forward_endl_data,
        const double min_photon_energy,
        const double max_photon_energy,
        const double min_electron_energy,
        const double max_electron_energy,
        const double cutoff_angle_cosine,
        const unsigned number_of_moment_preserving_angles,
        const double grid_convergence_tol,
        const double grid_absolute_diff_tol,
        const double grid_distance_tol )
  : AdjointElectronPhotonRelaxationDataGenerator( atomic_number ),
    d_forward_endl_data( forward_endl_data ),
    d_min_photon_energy( min_photon_energy ),
    d_max_photon_energy( max_photon_energy ),
    d_min_electron_energy( min_electron_energy ),
    d_max_electron_energy( max_electron_energy ),
    d_cutoff_angle_cosine( cutoff_angle_cosine ),
    d_number_of_moment_preserving_angles( number_of_moment_preserving_angles ),
    d_grid_convergence_tol( grid_convergence_tol ),
    d_grid_absolute_diff_tol( grid_absolute_diff_tol ),
    d_grid_distance_tol( grid_distance_tol )
{
  // Make sure the atomic number is valid
  testPrecondition( atomic_number <= 100u );
  // Make sure the endl forward data is valid
  testPrecondition( forward_endl_data.use_count() > 0 );
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

// Populate the adjoint electron-photon-relaxation data container
void StandardAdjointElectronPhotonRelaxationDataGenerator::populateEPRDataContainer(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container ) const
{
/*
  // Make sure the forward endl data is valid
  testPrecondition( d_forward_endl_data.use_count() > 0 );
*/
  // Make sure the forward native data is valid
  testPrecondition( d_forward_native_data.use_count() > 0 );

  // Set the table data
  this->setAtomicNumber( data_container );
  data_container.setMinPhotonEnergy( d_min_photon_energy );
  data_container.setMaxPhotonEnergy( d_max_photon_energy );
  data_container.setMinElectronEnergy( d_min_electron_energy );
  data_container.setMaxElectronEnergy( d_max_electron_energy );
  data_container.setCutoffAngleCosine( d_cutoff_angle_cosine );
  data_container.setNumberOfAdjointMomentPreservingAngles(
    d_number_of_moment_preserving_angles );
  data_container.setGridConvergenceTolerance( d_grid_convergence_tol );
  data_container.setGridAbsoluteDifferenceTolerance( d_grid_absolute_diff_tol );
  data_container.setGridDistanceTolerance( d_grid_distance_tol );

  // Set the relaxation data
  std::cout << std::endl << "Setting the adjoint relaxation data...";
  std::cout.flush();
  this->setAdjointRelaxationData( data_container );
  std::cout << "done." << std::endl;

  // Set the photon data
  std::cout << "Setting the adjoint photon data... " << std::endl;
  std::cout.flush();
  this->setAdjointPhotonData( data_container );
  std::cout << "done." << std::endl;

  // Set the electron data
  std::cout << "Setting the adjoint electron data: " << std::endl;
  this->setAdjointElectronData( data_container );
  std::cout << "done." << std::endl;

}

// Repopulate the electron moment preserving data
void StandardAdjointElectronPhotonRelaxationDataGenerator::repopulateAdjointMomentPreservingData(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container,
    const double cutoff_angle_cosine,
    const unsigned number_of_moment_preserving_angles )
{
  data_container.setCutoffAngleCosine( cutoff_angle_cosine );
  data_container.setNumberOfAdjointMomentPreservingAngles( 
    number_of_moment_preserving_angles );

  std::vector<double> adjoint_angular_energy_grid(
    data_container.getAdjointElasticAngularEnergyGrid() );

  std::cout << std::endl << "Setting the adjoint moment preserving electron data...";
  std::cout.flush();
  StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointMomentPreservingData( 
    adjoint_angular_energy_grid, 
    data_container );
  std::cout << "done." << std::endl;
}

// Set the relaxation data
void StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointRelaxationData(
			   Data::AdjointElectronPhotonRelaxationVolatileDataContainer&
			   data_container ) const
{
  // Assign the subshells
 std::set<unsigned> subshells = d_forward_native_data->getSubshells();

 data_container.setSubshells( subshells );

 std::set<unsigned>::iterator shell = subshells.begin();

  // Assign the subshell data
  for( shell; shell != subshells.end(); ++shell )
  {
    data_container.setSubshellOccupancy(
        *shell,
        d_forward_native_data->getSubshellOccupancy( *shell ) );

    data_container.setSubshellBindingEnergy(
        *shell,
        d_forward_native_data->getSubshellBindingEnergy( *shell ) );
  }
}

// Set the photon data
void StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointPhotonData(
			   Data::AdjointElectronPhotonRelaxationVolatileDataContainer&
			   data_container ) const
{
  std::cout << " Adjoint photon data generation has not been implmented yet!" << std::endl;
}


void StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointElectronData(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container ) const
{
//---------------------------------------------------------------------------//
// Set Electron Cross Section Data Data
//---------------------------------------------------------------------------//
/*! \details The cross section data is needed for caluculating the 
 *  moment preserving data and must be set first.
 */
  std::cout << " Setting the electron cross section data:" << std::endl;
  std::cout.flush();
  setAdjointElectronCrossSectionsData( data_container, false );
//---------------------------------------------------------------------------//
// Set Elastic Data
//---------------------------------------------------------------------------//
  std::cout << " Setting the elastic cutoff data...";
  std::cout.flush();

  // Set elastic angular distribution
  std::vector<double> angular_energy_grid(
    d_forward_native_data->getElasticAngularEnergyGrid() );

  data_container.setAdjointElasticAngularEnergyGrid( angular_energy_grid );

  data_container.setAdjointCutoffElasticPDF(
    d_forward_native_data->getCutoffElasticPDF()  );
  data_container.setAdjointCutoffElasticAngles(
    d_forward_native_data->getCutoffElasticAngles()  );

  std::cout << "done." << std::endl;

  if ( d_cutoff_angle_cosine > 0.999999 )
  {
    std::cout << " Moment preserving data will not be generated because the"
              << " cutoff angle cosine is greater than 0.999999." << std::endl
              << " cutoff_angle_cosine = " << d_cutoff_angle_cosine << std::endl;
  }
  else if ( d_number_of_moment_preserving_angles < 1 )
  {
    std::cout << " Moment preserving data will not be generated because the"
              << " number of moment preserving angles is less than 1." << std::endl
              << " number_of_moment_preserving_angles = "
              << d_number_of_moment_preserving_angles << std::endl;
  }
  else
  {
    std::cout << " Setting the elastic moment preserving data...";
    std::cout.flush();
    // Set the moment preserving data
    StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointMomentPreservingData(
        angular_energy_grid,
        data_container );
    std::cout << "done." << std::endl;
  }

//---------------------------------------------------------------------------//
// Set Electroionization Data
//---------------------------------------------------------------------------//
  std::cout << " Setting the electroionization data...";
  std::cout.flush();

  std::set<unsigned>::iterator shell = data_container.getSubshells().begin();

  // Loop through electroionization data for every subshell
  for ( shell; shell != data_container.getSubshells().end(); shell++ )
  {/*
    data_container.setAdjointElectroionizationEnergyGrid(
        *shell,
        d_forward_native_data->getElectroionizationRecoilEnergyGrid( *shell ) );

    data_container.setAdjointElectroionizationRecoilEnergy(
        *shell,
        d_forward_native_data->getElectroionizationRecoilEnergy( *shell ) );

    data_container.setAdjointElectroionizationRecoilPDF(
        *shell,
        d_forward_native_data->getElectroionizationRecoilPDF( *shell ) );*/
  }
  std::cout << "done." << std::endl;

//---------------------------------------------------------------------------//
// Set Bremsstrahlung Data
//---------------------------------------------------------------------------//
  std::cout << " Setting the bremsstrahlung data...";
  std::cout.flush();
/*
  data_container.setAdjointBremsstrahlungEnergyGrid(
    d_forward_native_data->getBremsstrahlungPhotonEnergyGrid() );

  data_container.setAdjointBremsstrahlungPhotonEnergy(
    d_forward_native_data->getBremsstrahlungPhotonEnergy() );

  data_container.setAdjointBremsstrahlungPhotonPDF(
    d_forward_native_data->getBremsstrahlungPhotonPDF() );
*/
  std::cout << "done." << std::endl;

//---------------------------------------------------------------------------//
// Set Atomic Excitation Data
//---------------------------------------------------------------------------//
  std::cout << " Setting the atomic excitation data...";
  std::cout.flush();
/*
  std::vector<double> raw_energy_grid =
    d_forward_native_data->getAtomicExcitationEnergyGrid();

  // Set atomic excitation energy loss
  data_container.setAdjointAtomicExcitationEnergyGrid( raw_energy_grid );
  data_container.setAdjointAtomicExcitationEnergyLoss(
    d_forward_native_data->getAtomicExcitationEnergyLoss() );
*/
  std::cout << "done." << std::endl;
}


// Set the electron cross section union energy grid
void StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointElectronCrossSectionsData(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container,
    bool recalculate_union_energy_grid ) const
{
  std::vector<double> energy_grid;

  // electron cross sections
  std::shared_ptr<const Utility::OneDDistribution>
        bremsstrahlung_cross_section, atomic_excitation_cross_section,
        cutoff_elastic_cross_section, total_elastic_cross_section;

  std::vector<std::pair<unsigned,std::shared_ptr<const Utility::OneDDistribution> > >
    electroionization_cross_section;

  if( recalculate_union_energy_grid )
  {/*
    // Initialize union energy grid
    std::list<double> union_energy_grid;
    union_energy_grid.push_back( d_min_electron_energy );
    union_energy_grid.push_back( d_max_electron_energy );

    //---------------------------------------------------------------------------//
    // Get Elastic Data Cross Section Data
    //---------------------------------------------------------------------------//
    // Get cutoff elastic cross section to union energy grid
    std::vector<double> raw_energy_grid =
    d_forward_endl_data->getElasticEnergyGrid();

    cutoff_elastic_cross_section.reset(
    new Utility::TabularDistribution<Utility::LogLog>(
    raw_energy_grid,
    d_forward_endl_data->getCutoffElasticCrossSection() ) );

    // merge raw energy grid with the union energy grid
    mergeAdjointElectronUnionEnergyGrid( raw_energy_grid, union_energy_grid );


    // Get total elastic cross section (same energy grid as cutoff)
    total_elastic_cross_section.reset(
    new Utility::TabularDistribution<Utility::LogLog>(
    raw_energy_grid,
    d_forward_endl_data->getTotalElasticCrossSection() ) );

    //---------------------------------------------------------------------------//
    // Get Electroionization Data Cross Section Data
    //---------------------------------------------------------------------------//

    std::set<unsigned>::iterator shell = data_container.getSubshells().begin();

    // Loop through electroionization data for every subshell
    for ( shell; shell != data_container.getSubshells().end(); shell++ )
    {
    std::shared_ptr<const Utility::OneDDistribution> subshell_cross_section;

    raw_energy_grid =
        d_forward_endl_data->getElectroionizationCrossSectionEnergyGrid( *shell );

    subshell_cross_section.reset(
        new Utility::TabularDistribution<Utility::LinLin>(
        raw_energy_grid,
        d_forward_endl_data->getElectroionizationCrossSection( *shell ) ) );

    // merge raw energy grid with the union energy grid
    mergeAdjointElectronUnionEnergyGrid( raw_energy_grid, union_energy_grid );

    electroionization_cross_section.push_back(
        std::make_pair( *shell, subshell_cross_section ) );
    }

    //---------------------------------------------------------------------------//
    // Get Bremsstrahlung Cross Section Data
    //---------------------------------------------------------------------------//
    
    raw_energy_grid =
    d_forward_endl_data->getBremsstrahlungCrossSectionEnergyGrid();

    bremsstrahlung_cross_section.reset(
    new Utility::TabularDistribution<Utility::LinLin>(
    raw_energy_grid,
    d_forward_endl_data->getBremsstrahlungCrossSection() ) );
    
    // merge raw energy grid with the union energy grid
    mergeAdjointElectronUnionEnergyGrid( raw_energy_grid, union_energy_grid );


    //---------------------------------------------------------------------------//
    // Get Atomic Excitation Data Cross Section Data
    //---------------------------------------------------------------------------//
    
    raw_energy_grid = d_forward_endl_data->getAtomicExcitationEnergyGrid();

    atomic_excitation_cross_section.reset(
    new Utility::TabularDistribution<Utility::LinLin>(
    raw_energy_grid,
    d_forward_endl_data->getAtomicExcitationCrossSection() ) );

    // merge raw energy grid with the union energy grid
    mergeAdjointElectronUnionEnergyGrid( raw_energy_grid, union_energy_grid );

    //---------------------------------------------------------------------------//
    // Create union energy grid and calculate cross sections
    //---------------------------------------------------------------------------//

    // Create the union energy grid
    std::cout << "   Creating union energy grid";
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
    energy_grid.assign( union_energy_grid.begin(),
                        union_energy_grid.end() );
    data_container.setAdjointElectronEnergyGrid( energy_grid );

    // Create and set the cross sections
    std::vector<double> cross_section;
    unsigned threshold;

    // Set Elastic cross section data
    std::vector<double> cutoff_cross_section, total_cross_section;

    std::cout << "   Setting the adjoint cutoff elastic cross section...";
    std::cout.flush();
    this->createAdjointCrossSectionOnUnionEnergyGrid(
        union_energy_grid,
        cutoff_elastic_cross_section,
        cutoff_cross_section,
        threshold );
    data_container.setAdjointCutoffElasticCrossSection( cutoff_cross_section );
    data_container.setAdjointCutoffElasticCrossSectionThresholdEnergyIndex( threshold );
    std::cout << "done." << std::endl;


    std::cout << "   Setting the screened Rutherford elastic cross section...";
    std::cout.flush();
    this->createAdjointCrossSectionOnUnionEnergyGrid(
        union_energy_grid,
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

    data_container.setAdjointScreenedRutherfordElasticCrossSection( cross_section );
    data_container.setAdjointScreenedRutherfordElasticCrossSectionThresholdEnergyIndex(
    threshold );
    std::cout << "done." << std::endl;*/
  }
  else
  {
    std::vector<double>::const_iterator start, end;

    // Find the min adjoint electron energy bin index on the forward union energy grid
    unsigned start_index = Utility::Search::binaryLowerBoundIndex(
                        d_forward_native_data->getElectronEnergyGrid().begin(),
                        d_forward_native_data->getElectronEnergyGrid().end(),
                        d_min_electron_energy );

    // Find the min adjoint electron energy bin index on the forward union energy grid
    unsigned end_index = Utility::Search::binaryUpperBoundIndex(
                        d_forward_native_data->getElectronEnergyGrid().begin(),
                        d_forward_native_data->getElectronEnergyGrid().end(),
                        d_max_electron_energy );

    start = d_forward_native_data->getElectronEnergyGrid().begin();
    std::advance( start, start_index );

    end = d_forward_native_data->getElectronEnergyGrid().begin();
    std::advance( end, end_index );

    Teuchos::ArrayRCP<double> electron_energy_grid;
    electron_energy_grid.assign( start, end );

    // Create the hash-based grid searcher
    Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
        new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>,false>(
        electron_energy_grid,
        electron_energy_grid[0],
        electron_energy_grid[electron_energy_grid.size()-1],
        electron_energy_grid.size()/10 + 1 ) );

    // Set the union energy grid
    data_container.setAdjointElectronEnergyGrid( std::vector<double>(start,end) );

    std::cout << "   Setting the adjoint total elastic cross section...";
    unsigned threshold_index =
      d_forward_native_data->getTotalElasticCrossSectionThresholdEnergyIndex();

    if ( threshold_index < start_index )
    {
      threshold_index = start_index;
    }

    start = d_forward_native_data->getTotalElasticCrossSection().begin();
    std::advance( start, threshold_index );
    end = d_forward_native_data->getTotalElasticCrossSection().begin();
    std::advance( end, end_index );

    data_container.setAdjointTotalElasticCrossSection( std::vector<double>(start,end) );
    data_container.setAdjointTotalElasticCrossSectionThresholdEnergyIndex(
        threshold_index - start_index );

    std::cout << "done." << std::endl;


    std::cout << "   Setting the adjoint cutoff elastic cross section...";
    threshold_index =
      d_forward_native_data->getCutoffElasticCrossSectionThresholdEnergyIndex();

    if ( threshold_index < start_index )
    {
      threshold_index = start_index;
    }

    start = d_forward_native_data->getCutoffElasticCrossSection().begin();
    std::advance( start, threshold_index );
    end = d_forward_native_data->getCutoffElasticCrossSection().begin();
    std::advance( end, end_index );

    data_container.setAdjointCutoffElasticCrossSection( std::vector<double>(start,end) );
    data_container.setAdjointCutoffElasticCrossSectionThresholdEnergyIndex(
        threshold_index - start_index );
    std::cout << "done." << std::endl;


    std::cout << "   Setting the adjoint screened Rutherford elastic cross section...";
    threshold_index =
      d_forward_native_data->getScreenedRutherfordElasticCrossSectionThresholdEnergyIndex();

    if( threshold_index < end_index )
    {
      if ( threshold_index < start_index )
      {
        threshold_index = start_index;
      }

      start = d_forward_native_data->getScreenedRutherfordElasticCrossSection().begin();
      std::advance( start, threshold_index );
      end = d_forward_native_data->getScreenedRutherfordElasticCrossSection().begin();
      std::advance( end, end_index );

      data_container.setAdjointScreenedRutherfordElasticCrossSection(
        std::vector<double>(start,end) );
      data_container.setAdjointScreenedRutherfordElasticCrossSectionThresholdEnergyIndex(
        threshold_index - start_index );
    }
    std::cout << "done." << std::endl;

    std::cout << "   Setting the adjoint bremsstrahlung cross section...";
    threshold_index =
      d_forward_native_data->getBremsstrahlungCrossSectionThresholdEnergyIndex();

    if ( threshold_index < start_index )
    {
      threshold_index = start_index;
    }

    start = d_forward_native_data->getBremsstrahlungCrossSection().begin();
    std::advance( start, threshold_index );
    end = d_forward_native_data->getBremsstrahlungCrossSection().begin();
    std::advance( end, end_index );

    threshold_index -= start_index;

    Teuchos::ArrayRCP<double> forward_bremsstrahlung_cross_section;
    forward_bremsstrahlung_cross_section.assign(start, end);

    std::vector<double> adjoint_bremsstrahlung_cross_section;
    this->evaluateAdjointBremsstrahlungCrossSection(
            forward_bremsstrahlung_cross_section,
            threshold_index,
            electron_energy_grid,
            grid_searcher,
            adjoint_bremsstrahlung_cross_section );

  data_container.setAdjointBremsstrahlungCrossSection( adjoint_bremsstrahlung_cross_section );
  data_container.setAdjointBremsstrahlungCrossSectionThresholdEnergyIndex(
    d_forward_native_data->getBremsstrahlungCrossSectionThresholdEnergyIndex() );
    std::cout << "done." << std::endl;

  }

  std::cout << "   Setting the bremsstrahlung cross section...";
  std::cout.flush();/*
  this->createAdjointCrossSectionOnUnionEnergyGrid( union_energy_grid,
                                             bremsstrahlung_cross_section,
                                             cross_section,
                                             threshold );

  data_container.setAdjointBremsstrahlungCrossSection( cross_section );
  data_container.setAdjointBremsstrahlungCrossSectionThresholdEnergyIndex( threshold );*/
  std::cout << "done." << std::endl;


  std::cout << "   Setting the atomic excitation cross section...";
  std::cout.flush();/*
  this->createAdjointCrossSectionOnUnionEnergyGrid( union_energy_grid,
                                             atomic_excitation_cross_section,
                                             cross_section,
                                             threshold );

  data_container.setAdjointAtomicExcitationCrossSection( cross_section );
  data_container.setAdjointAtomicExcitationCrossSectionThresholdEnergyIndex(
                    threshold );*/
  std::cout << "done." << std::endl;


  for( unsigned i = 0; i < electroionization_cross_section.size(); ++i )
  {
    std::cout << "   Setting subshell "
	      << electroionization_cross_section[i].first
	      << " electroionization cross section...";
    std::cout.flush();/*
    this->createAdjointCrossSectionOnUnionEnergyGrid(
				   union_energy_grid,
				   electroionization_cross_section[i].second,
				   cross_section,
				   threshold );

    data_container.setAdjointElectroionizationCrossSection(
				    electroionization_cross_section[i].first,
				    cross_section );
    data_container.setAdjointElectroionizationCrossSectionThresholdEnergyIndex(
				    electroionization_cross_section[i].first,
				    threshold );*/
    std::cout << "done." << std::endl;
  }
}

// Set the screened rutherford data
void StandardAdjointElectronPhotonRelaxationDataGenerator::setAdjointMomentPreservingData(
    const std::vector<double>& angular_energy_grid,
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container )
{
  // Create the analog elastic distribution (combined Cutoff and Screened Rutherford)
  std::shared_ptr<const MonteCarlo::AnalogElasticElectronScatteringDistribution>
        analog_distribution;

  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createAnalogElasticDistribution(
    analog_distribution,
    data_container.getAdjointCutoffElasticAngles(),
    data_container.getAdjointCutoffElasticPDF(),
    angular_energy_grid,
    data_container.getAtomicNumber() );

  // Construct the hash-based grid searcher for this atom
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.assign( data_container.getAdjointElectronEnergyGrid().begin(),
                      data_container.getAdjointElectronEnergyGrid().end() );

  Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
     new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>, false>(
						     energy_grid,
						     100u ) );

  // Construct the cutoff reaction
  Teuchos::ArrayRCP<double> cutoff_cross_section;
  cutoff_cross_section.assign(
    data_container.getAdjointCutoffElasticCrossSection().begin(),
    data_container.getAdjointCutoffElasticCrossSection().end() );

  // Construct the screened Rutherford reaction
  Teuchos::ArrayRCP<double> rutherford_cross_section;
  rutherford_cross_section.assign(
    data_container.getAdjointScreenedRutherfordElasticCrossSection().begin(),
    data_container.getAdjointScreenedRutherfordElasticCrossSection().end() );

  Teuchos::RCP<MonteCarlo::AnalogElasticElectroatomicReaction<Utility::LinLin>> 
    analog_reaction(
    	new MonteCarlo::AnalogElasticElectroatomicReaction<Utility::LinLin>(
            energy_grid,
            cutoff_cross_section,
            rutherford_cross_section,
            data_container.getAdjointCutoffElasticCrossSectionThresholdEnergyIndex(),
            data_container.getAdjointScreenedRutherfordElasticCrossSectionThresholdEnergyIndex(),
            grid_searcher,
            analog_distribution ) );

  // Create the moment evaluator of the elastic scattering distribution
  std::shared_ptr<DataGen::ElasticElectronMomentsEvaluator> moments_evaluator;
  moments_evaluator.reset(
    new DataGen::ElasticElectronMomentsEvaluator(
        data_container.getAdjointCutoffElasticAngles(),
        analog_distribution,
        analog_reaction,
        data_container.getCutoffAngleCosine() ) );

  // Moment preserving discrete angles and weights
  std::vector<double> discrete_angles, weights;

  // weights for a discrete angle cosine = 1
  std::vector<double> cross_section_reduction( angular_energy_grid.size() );

  // iterate through all angular energy bins
  for ( unsigned i = 0; i < angular_energy_grid.size(); i++ )
  {
    StandardAdjointElectronPhotonRelaxationDataGenerator::evaluateDisceteAnglesAndWeights(
        moments_evaluator,
        angular_energy_grid[i],
        data_container.getNumberOfAdjointMomentPreservingAngles(),
        discrete_angles,
        weights,
        cross_section_reduction[i] );

    data_container.setAdjointMomentPreservingElasticDiscreteAngles(
        angular_energy_grid[i],
        discrete_angles );
    data_container.setAdjointMomentPreservingElasticWeights(
        angular_energy_grid[i],
        weights );
  }

  // Generate a cross section reduction distribution
  std::shared_ptr<const Utility::OneDDistribution> reduction_distribution(
    new Utility::TabularDistribution<Utility::LinLin>(
        angular_energy_grid,
        cross_section_reduction ) );

  // Calculate the moment preserving cross section
  std::vector<double> moment_preserving_cross_section;
  StandardAdjointElectronPhotonRelaxationDataGenerator::evaluateAdjointMomentPreservingCrossSection(
        energy_grid,
        analog_reaction,
        analog_distribution,
        reduction_distribution,
        data_container.getCutoffAngleCosine(),
        data_container.getAdjointCutoffElasticCrossSectionThresholdEnergyIndex(),
        moment_preserving_cross_section );

  data_container.setAdjointMomentPreservingCrossSection(
    moment_preserving_cross_section );

  data_container.setAdjointMomentPreservingCrossSectionThresholdEnergyIndex(
    data_container.getAdjointCutoffElasticCrossSectionThresholdEnergyIndex() );
}

// Merge a secondary energy grid with the electron union energy grid
void StandardAdjointElectronPhotonRelaxationDataGenerator::mergeAdjointElectronUnionEnergyGrid(
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
void StandardAdjointElectronPhotonRelaxationDataGenerator::createAdjointCrossSectionOnUnionEnergyGrid(
   const std::list<double>& union_energy_grid,
   const std::shared_ptr<const Utility::OneDDistribution>& original_cross_section,
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

// Calculate the elastic anglular distribution for the angle cosine
void StandardAdjointElectronPhotonRelaxationDataGenerator::calculateElasticAngleCosine(
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

// Generate elastic moment preserving discrete angle cosines and weights
void StandardAdjointElectronPhotonRelaxationDataGenerator::evaluateDisceteAnglesAndWeights(
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

// Generate elastic moment preserving cross section
void StandardAdjointElectronPhotonRelaxationDataGenerator::evaluateAdjointMomentPreservingCrossSection(
    const Teuchos::ArrayRCP<double>& electron_energy_grid,
    const Teuchos::RCP<MonteCarlo::AnalogElasticElectroatomicReaction<Utility::LinLin> >&
        analog_reaction,
    const std::shared_ptr<const MonteCarlo::AnalogElasticElectronScatteringDistribution>&
        analog_distribution,
    const std::shared_ptr<const Utility::OneDDistribution>& reduction_distribution,
    const double cutoff_angle_cosine,
    const unsigned threshold_energy_index,
    std::vector<double>& moment_preserving_cross_section )
{
  moment_preserving_cross_section.resize( electron_energy_grid.size() );

  unsigned begin = threshold_energy_index;

  for( unsigned i = begin; i < electron_energy_grid.size(); i++ )
  {
    double cutoff_cdf = analog_distribution->evaluateCDF(
        electron_energy_grid[i],
        cutoff_angle_cosine );

    double cross_section_reduction =
        reduction_distribution->evaluate( electron_energy_grid[i] );

    double rutherford_cross_section =
        analog_reaction->getScreenedRutherfordCrossSection(
            electron_energy_grid[i] );

    double cutoff_cross_section =
        analog_reaction->getCutoffCrossSection( electron_energy_grid[i] );

    moment_preserving_cross_section[i] = cross_section_reduction*
        (rutherford_cross_section + (1.0 - cutoff_cdf)*cutoff_cross_section);
  }
}

// Generate adjoint bremsstrahlung cross section
void StandardAdjointElectronPhotonRelaxationDataGenerator::evaluateAdjointBremsstrahlungCrossSection(
    const Teuchos::ArrayRCP<double>& forward_bremsstrahlung_cross_section,
    const unsigned threshold_energy_index,
    const Teuchos::ArrayRCP<const double>& electron_energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
    std::vector<double>& adjoint_bremsstrahlung_cross_section ) const
{
  // Get the energy grid for bremsstrahlung energy distributions
  std::vector<double> brem_energy_grid =
    d_forward_native_data->getBremsstrahlungEnergyGrid();

  // Create the energy loss function
  MonteCarlo::BremsstrahlungElectronScatteringDistribution::BremsstrahlungDistribution
    energy_loss_function( brem_energy_grid.size() );

  MonteCarlo::BremsstrahlungElectronScatteringDistributionNativeFactory::createEnergyLossFunction(
    *d_forward_native_data,
    d_forward_native_data->getBremsstrahlungEnergyGrid(),
    energy_loss_function );

  // Create the adjoint bremsstrahlung cross section evaluator
  std::shared_ptr<DataGen::AdjointBremsstrahlungCrossSectionEvaluator> bremsstrahlung_evaluator(
    new DataGen::AdjointBremsstrahlungCrossSectionEvaluator(
        grid_searcher,
        electron_energy_grid,
        forward_bremsstrahlung_cross_section,
        threshold_energy_index,
        energy_loss_function ) );

  adjoint_bremsstrahlung_cross_section.resize(
    electron_energy_grid.size() );

  double min_photon_energy = 1.0e-7;
  /*! \details The highest energy grid point must be at least 1e-7 MeV below
   *  the max energy for the forward data (ie: 1e5 - 1e-7)
   */
  for ( unsigned i = 0; i < electron_energy_grid.size(); ++i )
  {
    adjoint_bremsstrahlung_cross_section[i] =
        bremsstrahlung_evaluator->evaluateAdjointCrossSection(
            electron_energy_grid[i], 1e-4 );
  }
  
}


} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_StandardAdjointElectronPhotonRelaxationDataGenerator.cpp
//---------------------------------------------------------------------------//
