//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointBremsstrahlungCrossSection.cpp
//! \author Luke Kersting
//! \brief  Adjoint bremsstrahlung cross section evaluator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "DataGen_AdjointBremsstrahlungCrossSectionEvaluator.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_HashBasedGridSearcher.hpp"
#include "MonteCarlo_BremsstrahlungElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroatomicReactionACEFactory.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<DataGen::AdjointBremsstrahlungCrossSectionEvaluator>
  adjoint_h_cs;

std::shared_ptr<MonteCarlo::BremsstrahlungElectroatomicReaction<Utility::LinLin> >
  bremsstrahlung_reaction;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the hydrogen adjoint cross section can be evaluated
TEUCHOS_UNIT_TEST( AdjointBremsstrahlungCrossSectionEvaluator,
		   evaluateAdjointCrossSection_h )
{
  double cross_section = adjoint_h_cs->evaluateAdjointCrossSection( 1.0e-5, 1.0e-6 );
  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  4.3722061293165644713e1,
                                  1e-6 );

  cross_section = adjoint_h_cs->evaluateAdjointCrossSection( 5.0e-4, 1.0e-6 );
  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  2.7299876754030748316e1,
                                  1e-6 );

  cross_section = adjoint_h_cs->evaluateAdjointCrossSection( 6.0e4, 1.0e-6 );
  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  0.9539521986214219984,
                                  1e-6 );

  cross_section = adjoint_h_cs->evaluateAdjointCrossSection( 1.0e5, 1.0e-6 );
  TEST_EQUALITY_CONST( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the hydrogen adjoint differential cross section can be evaluated
TEUCHOS_UNIT_TEST( AdjointBremsstrahlungCrossSectionEvaluator,
		   evaluateAdjointPDF_h )
{

  double diff_cross_section =
    adjoint_h_cs->evaluateAdjointPDF( 5.0e-4,
                                      5.0e-3,
                                      1.0e-6 );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
                                  2.763762632859210E+01/2.7299876754030748316e1,
                                  1e-6 );

  diff_cross_section =
    adjoint_h_cs->evaluateAdjointPDF( 6.0e4,
                                      1.0e5,
                                      1.0e-6 );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
                                  5.641165944163830E-07/0.9539521986214219984,
                                  1e-6 );

  diff_cross_section =
    adjoint_h_cs->evaluateAdjointPDF( 1.0e5-5.0e-8,
                                      1.0e5,
                                      1.0e-6 );

  TEST_EQUALITY_CONST( diff_cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_ace_file_name, test_ace_table_name;

  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_ace_file",
		 &test_ace_file_name,
		 "Test ACE file name" );
  clp.setOption( "test_ace_table",
		 &test_ace_table_name,
		 "Test ACE table name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out =
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return =
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

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
  DataGen::AdjointBremsstrahlungCrossSectionEvaluator::BremsstrahlungDistribution
    energy_loss_distribution( N );

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

  bremsstrahlung_reaction.reset(
        new MonteCarlo::BremsstrahlungElectroatomicReaction<Utility::LinLin>(
            energy_grid,
            bremsstrahlung_cross_section,
            threshold_energy_index,
            grid_searcher,
            bremsstrahlung_distribution ) );

  // Initialize the hydrogen adjoint cross section evaluator
  adjoint_h_cs.reset( new DataGen::AdjointBremsstrahlungCrossSectionEvaluator(
                    bremsstrahlung_reaction,
                    integration_points ) );

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
// end tstAdjointBremsstrahlungCrossSectionEvaluator.cpp
//---------------------------------------------------------------------------//
