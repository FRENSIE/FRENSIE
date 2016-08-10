//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointElectronCrossSectionEvaluator.cpp
//! \author Luke Kersting
//! \brief  Adjoint electron cross section evaluator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "DataGen_AdjointElectronCrossSectionEvaluator.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "MonteCarlo_ElectroionizationSubshellElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistribution.hpp"
#include "MonteCarlo_BremsstrahlungElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroatomicReactionACEFactory.hpp"

//---------------------------------------------------------------------------//
// Testing Typedefs
//---------------------------------------------------------------------------//
  typedef MonteCarlo::ElectroionizationSubshellElectroatomicReaction<Utility::LinLin>
    ElectroionizationReaction;

  typedef MonteCarlo::BremsstrahlungElectroatomicReaction<Utility::LinLin> 
    BremsstrahlungReaction;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<DataGen::AdjointElectronCrossSectionEvaluator<ElectroionizationReaction> >
  native_adjoint_ionization_cs;

std::shared_ptr<DataGen::AdjointElectronCrossSectionEvaluator<BremsstrahlungReaction> >
  ace_adjoint_brem_cs, native_adjoint_brem_cs;

double max_ionization_subshell_adjoint_energy, max_brem_adjoint_energy;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the hydrogen adjoint cross section can be evaluated
TEUCHOS_UNIT_TEST( AdjointElectronCrossSectionEvaluator,
                   evaluateAdjointCrossSection )
{
  // Native Electroionization
  double cross_section =
    native_adjoint_ionization_cs->evaluateAdjointCrossSection( 1.361E-05, 1.0e-9 );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  139697665948165.1875,
                                  1e-6 );

  cross_section =
    native_adjoint_ionization_cs->evaluateAdjointCrossSection( 1.88E-05, 1.0e-9 );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  79238679438792.5625,
                                  1e-6 );

  cross_section =
    native_adjoint_ionization_cs->evaluateAdjointCrossSection( 1.123900E-02, 1.0e-9 );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  206857228.81668719649,
                                  1e-6 );

  cross_section =
    native_adjoint_ionization_cs->evaluateAdjointCrossSection( 8.75350E-01, 1.0e-9 );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  125955.16376563441008,
                                  1e-6 );

  cross_section =
    native_adjoint_ionization_cs->evaluateAdjointCrossSection(
        max_ionization_subshell_adjoint_energy - 6.0e-8,
        1.0e-9 );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  799.79064580439091969,
                                  1e-6 );

  cross_section =
    native_adjoint_ionization_cs->evaluateAdjointCrossSection(
        max_ionization_subshell_adjoint_energy,
        1.0e-12 );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  0.0,
                                  1e-6 );


  // ACE Bremsstrahlung
  cross_section =
    ace_adjoint_brem_cs->evaluateAdjointCrossSection( 1.0e-5, 1.0e-6 );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  4.3722061293165644713e1,
                                  1e-6 );

  cross_section =
    ace_adjoint_brem_cs->evaluateAdjointCrossSection( 5.0e-4, 1.0e-6 );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  2.7299876754030748316e1,
                                  1e-6 );

  cross_section =
    ace_adjoint_brem_cs->evaluateAdjointCrossSection( 6.0e4, 1.0e-6 );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  0.9539521986214219984,
                                  1e-6 );

  cross_section =
    ace_adjoint_brem_cs->evaluateAdjointCrossSection( 1.0e5, 1.0e-6 );

  TEST_EQUALITY_CONST( cross_section, 0.0 );


  // ACE Bremsstrahlung
  cross_section =
    native_adjoint_brem_cs->evaluateAdjointCrossSection( 1.0e-5, 1.0e-6 );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  4.3499365965888287633e1,
                                  1e-6 );

  cross_section =
    native_adjoint_brem_cs->evaluateAdjointCrossSection( 5.0e-4, 1.0e-6 );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  2.7374365055849828821e1,
                                  1e-6 );

  cross_section =
    native_adjoint_brem_cs->evaluateAdjointCrossSection( 6.0e4, 1.0e-6 );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  0.95353250375262488259,
                                  1e-6 );

  cross_section =
    native_adjoint_brem_cs->evaluateAdjointCrossSection( 1.0e5, 1.0e-6 );

  TEST_EQUALITY_CONST( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the hydrogen adjoint differential cross section can be evaluated
TEUCHOS_UNIT_TEST( AdjointElectronCrossSectionEvaluator,
                   evaluateAdjointPDF )
{
  // Native Electroionization
  double diff_cross_section =
    native_adjoint_ionization_cs->evaluateAdjointPDF( 1.88E-05,
                                      1.0E-04,
                                      1.0e-9 );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
                                  4.99027E+07*12876.48039/79238679438792.5625,
                                  1e-6 );

  diff_cross_section =
    native_adjoint_ionization_cs->evaluateAdjointPDF( 1.123900E-02,
                                      3.16228,
                                      1.0e-9 );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
                                  2.19766977908530E+03/206857228.81668719649,
                                  1e-6 );

  diff_cross_section =
    native_adjoint_ionization_cs->evaluateAdjointPDF( 8.75350E-01,
                                      1.0e5,
                                      1.0e-9 );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
                                  3.36107129975999E-01/125955.16376563441008,
                                  1.0e-6 );

  // ACE Bremsstrahlung
  diff_cross_section =
    ace_adjoint_brem_cs->evaluateAdjointPDF( 5.0e-4,
                                          5.0e-3,
                                          1.0e-6 );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
                                  2.763762632859210E+01/2.7299876754030748316e1,
                                  1e-6 );

  diff_cross_section =
    ace_adjoint_brem_cs->evaluateAdjointPDF( 6.0e4,
                                          1.0e5,
                                          1.0e-6 );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
                                  5.641165944163830E-07/0.9539521986214219984,
                                  1e-6 );

  diff_cross_section =
    ace_adjoint_brem_cs->evaluateAdjointPDF( 1.0e5-5.0e-8,
                                          1.0e5,
                                          1.0e-6 );

  TEST_EQUALITY_CONST( diff_cross_section, 0.0 );


  // Native Bremsstralung
  diff_cross_section =
    native_adjoint_brem_cs->evaluateAdjointPDF( 5.0e-4,
                                      5.0e-3,
                                      1.0e-6 );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
                                  1.2054818736422567849,
                                  1e-6 );

  diff_cross_section =
    native_adjoint_brem_cs->evaluateAdjointPDF( 6.0e4,
                                      1.0e5,
                                      1.0e-6 );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
                                  6.625704416102020535e-07,
                                  1e-6 );

  diff_cross_section =
    native_adjoint_brem_cs->evaluateAdjointPDF( 1.0e5-5.0e-8,
                                      1.0e5,
                                      1.0e-6 );

  TEST_EQUALITY_CONST( diff_cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_ace_file_name, test_ace_table_name, test_native_file_name;

  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_ace_file",
		 &test_ace_file_name,
		 "Test ACE file name" );
  clp.setOption( "test_ace_table",
		 &test_ace_table_name,
		 "Test ACE table name" );
  clp.setOption( "test_native_file",
		 &test_native_file_name,
		 "Test Native file name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out =
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return =
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Create ACE adjoint brem cross section evaluator
  {
  // Create a file handler and data extractor
  std::shared_ptr<Data::ACEFileHandler> ace_file_handler(
				 new Data::ACEFileHandler( test_ace_file_name,
							   test_ace_table_name,
							   1u ) );

  std::shared_ptr<Data::XSSEPRDataExtractor> xss_data_extractor(
				new Data::XSSEPRDataExtractor(
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );

  // Extract the common energy grid used for this atom
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.deepCopy( xss_data_extractor->extractElectronEnergyGrid() );

  // Index of first non zero cross section in the energy grid
  unsigned threshold_energy_index;

  // Bremsstrahlung cross section with zeros removed
  Teuchos::ArrayRCP<double> bremsstrahlung_cross_section;

  MonteCarlo::ElectroatomicReactionACEFactory::removeZerosFromCrossSection(
			energy_grid,
			xss_data_extractor->extractBremsstrahlungCrossSection(),
			bremsstrahlung_cross_section,
			threshold_energy_index );

  // Extract the bremsstrahlung scattering information data block (BREMI)
  Teuchos::ArrayView<const double> bremi_block =
    xss_data_extractor->extractBREMIBlock();

  // Extract the number of tabulated distributions
  int N = bremi_block.size()/3;

  // Extract the electron energy grid for bremsstrahlung energy distributions
  Teuchos::Array<double> electron_energy_grid(bremi_block(0,N));

  // Extract the table lengths for bremsstrahlung energy distributions
  Teuchos::Array<double> table_length(bremi_block(N,N));

  // Extract the offsets for bremsstrahlung energy distributions
  Teuchos::Array<double> offset(bremi_block(2*N,N));

  // Extract the bremsstrahlung photon energy distributions block (BREME)
  Teuchos::ArrayView<const double> breme_block =
    xss_data_extractor->extractBREMEBlock();

  // Create the bremsstrahlung scattering functions
  MonteCarlo::TwoDDistribution energy_loss_distribution( N );

  std::vector<double> integration_points( N );

  for( unsigned n = 0; n < N; ++n )
  {
    energy_loss_distribution[n].first = electron_energy_grid[n];
    integration_points[n] = electron_energy_grid[n];

    energy_loss_distribution[n].second.reset(
	  new Utility::HistogramDistribution(
		 breme_block( offset[n], table_length[n] ),
		 breme_block( offset[n] + 1 + table_length[n], table_length[n]-1 ),
         true ) );
  }

  std::shared_ptr<const MonteCarlo::BremsstrahlungElectronScatteringDistribution>
    bremsstrahlung_distribution(
        new MonteCarlo::BremsstrahlungElectronScatteringDistribution(
            energy_loss_distribution ) );

  // Create the hash-based grid searcher
  Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
        new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>,false>(
        energy_grid,
        energy_grid[0],
        energy_grid[energy_grid.size()-1],
        energy_grid.size()/10+1 ) );

  std::shared_ptr<MonteCarlo::BremsstrahlungElectroatomicReaction<Utility::LinLin> >
    bremsstrahlung_reaction(
        new MonteCarlo::BremsstrahlungElectroatomicReaction<Utility::LinLin>(
            energy_grid,
            bremsstrahlung_cross_section,
            threshold_energy_index,
            grid_searcher,
            bremsstrahlung_distribution ) );

  // Initialize the hydrogen adjoint cross section evaluator
  ace_adjoint_brem_cs.reset( new DataGen::AdjointElectronCrossSectionEvaluator<BremsstrahlungReaction>(
                    bremsstrahlung_reaction,
                    integration_points ) );
  }

  // Create the native data file container
  std::shared_ptr<Data::ElectronPhotonRelaxationDataContainer> data_container(
    new Data::ElectronPhotonRelaxationDataContainer(
        test_native_file_name ) );

  // Extract the common energy grid
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.assign( data_container->getElectronEnergyGrid().begin(),
                      data_container->getElectronEnergyGrid().end() );

  // Create the hash-based grid searcher
  Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
        new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>,false>(
        energy_grid,
        energy_grid[0],
        energy_grid[energy_grid.size()-1],
        energy_grid.size()/10+1 ) );

  // Create Native adjoint brem cross section evaluator
  {
  // Get the energy grid for bremsstrahlung energy distributions
  std::vector<double> brem_energy_grid =
        data_container->getBremsstrahlungEnergyGrid();

  // Create the scattering function
  MonteCarlo::BremsstrahlungElectronScatteringDistribution::BremsstrahlungDistribution
         energy_loss_function( brem_energy_grid.size() );

  std::vector<double> integration_points( brem_energy_grid.size() );

  for( unsigned n = 0; n < brem_energy_grid.size(); ++n )
  {
    energy_loss_function[n].first = brem_energy_grid[n];
    integration_points[n] = brem_energy_grid[n];

    // Get the energy of the bremsstrahlung photon at the incoming energy
    std::vector<double> photon_energy(
        data_container->getBremsstrahlungPhotonEnergy( brem_energy_grid[n] ) );

    // Get the bremsstrahlung photon pdf at the incoming energy
    std::vector<double> pdf(
        data_container->getBremsstrahlungPhotonPDF( brem_energy_grid[n] ) );

    energy_loss_function[n].second.reset(
	  new const Utility::TabularDistribution<Utility::LinLin>( photon_energy,
                                                               pdf ) );
  }

  std::shared_ptr<const MonteCarlo::BremsstrahlungElectronScatteringDistribution>
    bremsstrahlung_distribution(
        new MonteCarlo::BremsstrahlungElectronScatteringDistribution(
            energy_loss_function,
            data_container->getAtomicNumber() ) );

  // Bremsstrahlung cross section
  Teuchos::ArrayRCP<double> bremsstrahlung_cross_section;
  bremsstrahlung_cross_section.assign(
	   data_container->getBremsstrahlungCrossSection().begin(),
	   data_container->getBremsstrahlungCrossSection().end() );

  // Index of first non zero cross section in the energy grid
  unsigned threshold_energy_index =
    data_container->getBremsstrahlungCrossSectionThresholdEnergyIndex();

  std::shared_ptr<MonteCarlo::BremsstrahlungElectroatomicReaction<Utility::LinLin> >
    bremsstrahlung_reaction(
        new MonteCarlo::BremsstrahlungElectroatomicReaction<Utility::LinLin>(
            energy_grid,
            bremsstrahlung_cross_section,
            threshold_energy_index,
            grid_searcher,
            bremsstrahlung_distribution ) );

  // Initialize the hydrogen adjoint cross section evaluator
  native_adjoint_brem_cs.reset( new DataGen::AdjointElectronCrossSectionEvaluator<BremsstrahlungReaction>(
                    bremsstrahlung_reaction,
                    integration_points ) );
  }

  // Create the Native adjoint electroionization cross section evaluators
  {
  // Extract the subshell information
  std::set<unsigned> subshells = data_container->getSubshells();

  Data::SubshellType subshell_type;

  std::set<unsigned>::iterator shell = subshells.begin();

  // Convert subshell number to enum
  subshell_type = Data::convertENDFDesignatorToSubshellEnum( *shell );

  // Electroionization cross section
  Teuchos::ArrayRCP<double> subshell_cross_section;
  subshell_cross_section.assign(
    data_container->getElectroionizationCrossSection( *shell ).begin(),
    data_container->getElectroionizationCrossSection( *shell ).end() );

  // Electroionization cross section threshold energy bin index
  unsigned threshold_energy_index =
    data_container->getElectroionizationCrossSectionThresholdEnergyIndex(
      *shell );

  // The electroionization subshell distribution
  std::shared_ptr<const MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution>
    electroionization_subshell_distribution;

  // Get the energies for which knock-on sampling tables are given
  std::vector<double> ionization_energy_grid =
    data_container->getElectroionizationEnergyGrid( *shell );

  // Subshell distribution
  MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution::ElectroionizationSubshellDistribution
        subshell_distribution( ionization_energy_grid.size() );

  std::vector<double> integration_points( ionization_energy_grid.size() );

  for( unsigned n = 0; n < ionization_energy_grid.size(); ++n )
  {
    subshell_distribution[n].first = ionization_energy_grid[n];
    integration_points[n] = ionization_energy_grid[n];

    // Get the recoil energy distribution at the incoming energy
    Teuchos::Array<double> recoil_energy(
        data_container->getElectroionizationRecoilEnergy(
            *shell,
            ionization_energy_grid[n] ) );

    // Get the recoil energy pdf at the incoming energy
    Teuchos::Array<double> pdf(
        data_container->getElectroionizationRecoilPDF(
            *shell,
            ionization_energy_grid[n] ) );

    subshell_distribution[n].second.reset(
	  new const Utility::TabularDistribution<Utility::LinLin>( recoil_energy,
                                                             pdf ) );
  }

  double binding_energy = data_container->getSubshellBindingEnergy( *shell );

  // Set the max allowed adjoint energy
  max_ionization_subshell_adjoint_energy = 1.0e5 - binding_energy - 1.0e-7;

  integration_points.back() = max_ionization_subshell_adjoint_energy;
  integration_points.push_back( ionization_energy_grid.back() );

  electroionization_subshell_distribution.reset(
    new MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution(
            subshell_distribution,
            binding_energy ) );

  // Create the subshell electroelectric reaction
  std::shared_ptr<ElectroionizationReaction> 
    electroionization_subshell_reaction(
      new ElectroionizationReaction(
            energy_grid,
            subshell_cross_section,
            threshold_energy_index,
            grid_searcher,
            subshell_type,
            electroionization_subshell_distribution ) );

  native_adjoint_ionization_cs.reset(
    new DataGen::AdjointElectronCrossSectionEvaluator<ElectroionizationReaction>(
      electroionization_subshell_reaction,
      integration_points ) );
  }

  // Run the unit tests
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  const bool success = Teuchos::UnitTestRepository::runUnitTests( *out );

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstAdjointElectronCrossSectionEvaluator.cpp
//---------------------------------------------------------------------------//
