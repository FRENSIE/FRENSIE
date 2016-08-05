//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointElectroionizationSubshellCrossSection.cpp
//! \author Luke Kersting
//! \brief  Adjoint electroionization subshell cross section evaluator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "DataGen_AdjointElectroionizationSubshellCrossSectionEvaluator.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "MonteCarlo_ElectroionizationSubshellElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistribution.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<DataGen::AdjointElectroionizationSubshellCrossSectionEvaluator>
  adjoint_h_cs;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the hydrogen adjoint cross section can be evaluated
TEUCHOS_UNIT_TEST( AdjointElectroionizationSubshellCrossSectionEvaluator,
		   evaluateAdjointCrossSection )
{
  double cross_section = adjoint_h_cs->evaluateAdjointCrossSection( 1.361E-05, 1.0e-9 );
  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  139697665948165.1875,
                                  1e-6 );

  cross_section = adjoint_h_cs->evaluateAdjointCrossSection( 1.88E-05, 1.0e-9 );
  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  79238679438792.5625,
                                  1e-6 );

  cross_section = adjoint_h_cs->evaluateAdjointCrossSection( 1.123900E-02, 1.0e-9 );
  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  206857228.81668719649,
                                  1e-6 );

  cross_section = adjoint_h_cs->evaluateAdjointCrossSection( 8.75350E-01, 1.0e-9 );
  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  125955.16376563441008,
                                  1e-6 );
}

//---------------------------------------------------------------------------//
// Check that the hydrogen adjoint differential cross section can be evaluated
TEUCHOS_UNIT_TEST( AdjointElectroionizationSubshellCrossSectionEvaluator,
		   evaluateAdjointPDF )
{

  double diff_cross_section =
    adjoint_h_cs->evaluateAdjointPDF( 1.88E-05,
                                      1.0E-04,
                                      1.0e-9 );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
                                  4.99027E+07*12876.48039/79238679438792.5625,
                                  1e-6 );

  diff_cross_section =
    adjoint_h_cs->evaluateAdjointPDF( 1.123900E-02,
                                      3.16228,
                                      1.0e-9 );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
                                  2.19766977908530E+03/206857228.81668719649,
                                  1e-6 );

  diff_cross_section =
    adjoint_h_cs->evaluateAdjointPDF( 8.75350E-01,
                                      1.0e5,
                                      1.0e-9 );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
                                  3.36107129975999E-01/125955.16376563441008,
                                  1.0e-6 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_native_file_name;

  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

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

  // Create the native data file container
  std::shared_ptr<Data::ElectronPhotonRelaxationDataContainer> data_container(
    new Data::ElectronPhotonRelaxationDataContainer(
        test_native_file_name ) );

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

  electroionization_subshell_distribution.reset(
    new MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution(
            subshell_distribution,
            data_container->getSubshellBindingEnergy( *shell ) ) );

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

  // Create the subshell electroelectric reaction
  std::shared_ptr<MonteCarlo::ElectroionizationSubshellElectroatomicReaction<Utility::LinLin> > 
    electroionization_subshell_reaction(
      new MonteCarlo::ElectroionizationSubshellElectroatomicReaction<Utility::LinLin>(
            energy_grid,
            subshell_cross_section,
            threshold_energy_index,
            grid_searcher,
            subshell_type,
            electroionization_subshell_distribution ) );

  adjoint_h_cs.reset(
    new DataGen::AdjointElectroionizationSubshellCrossSectionEvaluator(
      electroionization_subshell_reaction,
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
// end tstAdjointElectroionizationSubshellCrossSectionEvaluator.cpp
//---------------------------------------------------------------------------//
