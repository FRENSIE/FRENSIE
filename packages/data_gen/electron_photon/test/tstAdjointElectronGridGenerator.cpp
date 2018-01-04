//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointElectronGridGenerator.cpp
//! \author Luke Kersting
//! \brief  Adjoint electron grid generator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "DataGen_AdjointElectronGridGenerator.hpp"
#include "MonteCarlo_BremsstrahlungElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroionizationSubshellElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroatomicReactionNativeFactory.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Typedefs
//---------------------------------------------------------------------------//

typedef MonteCarlo::ElectroionizationSubshellElectroatomicReaction<Utility::LogLog>
  ElectroionizationReaction;

typedef MonteCarlo::BremsstrahlungElectroatomicReaction<Utility::LogLog> 
  BremsstrahlungReaction;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<const BremsstrahlungReaction> h_brem_reaction;
std::shared_ptr<const ElectroionizationReaction> h_ionization_reaction;
std::vector<double> brem_energy_grid, ionization_energy_grid;
double binding_energy;
double max_ionization_subshell_adjoint_energy;

double min_energy = 1e-5;
double max_energy = 20.0;
double max_energy_nudge_value = 0.2;
double energy_to_outgoing_energy_nudge_value = 2e-7;
double convergence_tol = 0.001;
double absolute_diff_tol = 1e-10;
double distance_tol = 1e-8;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the min energy can be returned 
TEUCHOS_UNIT_TEST( AdjointElectronGridGenerator, getMinEnergy )
{
  DataGen::AdjointElectronGridGenerator<BremsstrahlungReaction,Utility::LinLinLin>
  grid_generator( h_brem_reaction,
                  brem_energy_grid );

  TEST_EQUALITY_CONST( grid_generator.getMinEnergy(), 1e-5 );
}

//---------------------------------------------------------------------------//
// Check that the max energy can be returned 
TEUCHOS_UNIT_TEST( AdjointElectronGridGenerator, getMaxEnergy )
{
  DataGen::AdjointElectronGridGenerator<BremsstrahlungReaction,Utility::LinLinLin>
  grid_generator( h_brem_reaction,
                  brem_energy_grid );

  TEST_EQUALITY_CONST( grid_generator.getMaxEnergy(), 20.0 );
}

//---------------------------------------------------------------------------//
// Check that the max energy nudge value can be set
TEUCHOS_UNIT_TEST( AdjointElectronGridGenerator, setMaxEnergyNudgeValue )
{
  DataGen::AdjointElectronGridGenerator<BremsstrahlungReaction,Utility::LinLinLin>
  grid_generator( h_brem_reaction,
                  brem_energy_grid );

  TEST_EQUALITY_CONST( grid_generator.getNudgedMaxEnergy(), 20.2 );

  grid_generator.setMaxEnergyNudgeValue( 0.5 );

  TEST_EQUALITY_CONST( grid_generator.getNudgedMaxEnergy(), 20.5 );
}

//---------------------------------------------------------------------------//
// Check that the energy to max energy nudge value can be set
TEUCHOS_UNIT_TEST( AdjointElectronGridGenerator,
                   setEnergyToOutgoingEnergyNudgeValue )
{
  DataGen::AdjointElectronGridGenerator<BremsstrahlungReaction,Utility::LinLinLin>
  grid_generator( h_brem_reaction,
                  brem_energy_grid );

  TEST_EQUALITY_CONST( grid_generator.getNudgedEnergy( 1.0 ), 1.000001 );

  grid_generator.setEnergyToOutgoingEnergyNudgeValue( 1e-4 );

  TEST_EQUALITY_CONST( grid_generator.getNudgedEnergy( 1.0 ), 1.0001 );
}

//---------------------------------------------------------------------------//
// Check that the hydrogen adjoint cross section can be evaluated
TEUCHOS_UNIT_TEST( AdjointElectronGridGenerator,
                   evaluateAdjointCrossSection )
{
  double precision = 1e-5;
  double cross_section;

  // Native Electroionization
  {
  DataGen::AdjointElectronGridGenerator<ElectroionizationReaction,Utility::LinLinLin>
    grid_generator( h_ionization_reaction,
                    ionization_energy_grid,
                    min_energy,
                    max_ionization_subshell_adjoint_energy,
                    2.0*binding_energy,
                    binding_energy + 1.0e-7,
                    convergence_tol,
                    absolute_diff_tol,
                    distance_tol );

  cross_section =
    grid_generator.evaluateAdjointCrossSection( 1.361E-05, precision );
  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  2.8259853613553445e+13,
                                  1e-5 );

  cross_section =
    grid_generator.evaluateAdjointCrossSection( 1.88E-05, precision );
  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  1.5012051754783895e+13,
                                  1e-5 );

  cross_section =
    grid_generator.evaluateAdjointCrossSection( 1.123900E-02, precision );
  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  1.8693697855518397e+07,
                                  1e-5 );

  cross_section =
    grid_generator.evaluateAdjointCrossSection( 8.75350E-01, precision );
  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  2.7467207608280925e+04,
                                  1e-5 );

  cross_section =
    grid_generator.evaluateAdjointCrossSection(
                            max_ionization_subshell_adjoint_energy - 6.0e-8,
                            precision );
  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  1.9462275129042428e+04,
                                  1e-5 );

  cross_section =
    grid_generator.evaluateAdjointCrossSection(
                                        max_ionization_subshell_adjoint_energy,
                                        precision );
  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  1.9445701148603432e+04,
                                  1e-5 );
  }

  // Native Bremsstrahlung
  {
  DataGen::AdjointElectronGridGenerator<BremsstrahlungReaction,Utility::LinLinLin>
    grid_generator( h_brem_reaction,
                    brem_energy_grid,
                    min_energy,
                    1e5 - 1e-5,
                    1e-9,
                    0.0,
                    convergence_tol,
                    absolute_diff_tol,
                    distance_tol );

  cross_section =
    grid_generator.evaluateAdjointCrossSection( 1.0e-5, precision );
  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  1.6837683241416762e+01,
                                  1e-5 );

  cross_section =
    grid_generator.evaluateAdjointCrossSection( 5.0e-4, precision );
  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  8.9374265084435329,
                                  1e-5 );

  cross_section =
    grid_generator.evaluateAdjointCrossSection( 6.0e4, precision );
  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  1.4200314623419494e-01,
                                  1e-5 );

  cross_section =
    grid_generator.evaluateAdjointCrossSection( 1.0e5, precision );
  TEST_EQUALITY_CONST( cross_section, 0.0 );
  }

  // Native Bremsstrahlung
  {
  DataGen::AdjointElectronGridGenerator<BremsstrahlungReaction,Utility::LogLogLog>
    grid_generator( h_brem_reaction,
                    brem_energy_grid,
                    min_energy,
                    1e5 - 1e-5,
                    1e-9,
                    0.0,
                    convergence_tol,
                    absolute_diff_tol,
                    distance_tol );

  cross_section =
    grid_generator.evaluateAdjointCrossSection( 1.0e-5, precision );
  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  1.6837683241416762e+01,
                                  1e-5 );

  cross_section =
    grid_generator.evaluateAdjointCrossSection( 5.0e-4, precision );
  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  8.9374265084435329,
                                  1e-5 );

  cross_section =
    grid_generator.evaluateAdjointCrossSection( 6.0e4, precision );
  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  1.4200314623419494e-01,
                                  1e-5 );

  cross_section =
    grid_generator.evaluateAdjointCrossSection( 1.0e5, precision );
  TEST_EQUALITY_CONST( cross_section, 0.0 );
  }
}

//---------------------------------------------------------------------------//
// Check that the hydrogen adjoint differential cross section can be evaluated
TEUCHOS_UNIT_TEST( AdjointElectronGridGenerator,
                   evaluateAdjointPDF )
{
  double diff_cross_section;

  // Native Electroionization
  {
  DataGen::AdjointElectronGridGenerator<ElectroionizationReaction,Utility::LinLinLin>
    grid_generator( h_ionization_reaction,
                    ionization_energy_grid,
                    min_energy,
                    max_ionization_subshell_adjoint_energy,
                    2.0*binding_energy,
                    binding_energy + 1.0e-7,
                    convergence_tol,
                    absolute_diff_tol,
                    distance_tol );

  diff_cross_section =
    grid_generator.evaluateAdjointPDF( 1.88E-05, 1.0E-04, 1.0e-4 );
  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
                                  3.8798354723063463e-02,
                                  1e-5 );

                                  diff_cross_section =
    grid_generator.evaluateAdjointPDF( 1.123900E-02, 3.16228, 1.0e-4 );
  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
                                  1.1408238447187018e-04,
                                  1e-6 );

                                  diff_cross_section =
    grid_generator.evaluateAdjointPDF( 8.75350E-01,
                                       max_ionization_subshell_adjoint_energy,
                                       1.0e-4 );
  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
                                  7.6551190817011801e-07,
                                  1.0e-5 );
  }

  // Native Bremsstrahlung
  {
  DataGen::AdjointElectronGridGenerator<BremsstrahlungReaction,Utility::LinLinLin>
    grid_generator( h_brem_reaction,
                    brem_energy_grid,
                    min_energy,
                    1e5 -1e-9,
                    1e-9,
                    0.0,
                    convergence_tol,
                    absolute_diff_tol,
                    distance_tol );

  diff_cross_section =
    grid_generator.evaluateAdjointPDF( 5.0e-4, 5.0e-3, 1.0e-4 );
  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
                                  3.6854609980444470,
                                  1e-5 );

                                  diff_cross_section =
    grid_generator.evaluateAdjointPDF( 6.0e4, 1.0e5, 1.0e-4 );
  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
                                  4.4490736202820424e-06,
                                  1e-5 );

                                  diff_cross_section =
    grid_generator.evaluateAdjointPDF( 1.0e5-5.0e-8, 1.0e5, 1.0e-4 );
  TEST_EQUALITY_CONST( diff_cross_section, 0.0 );
  }

  // Native Bremsstrahlung
  {
  DataGen::AdjointElectronGridGenerator<BremsstrahlungReaction,Utility::LogLogLog>
    grid_generator( h_brem_reaction,
                    brem_energy_grid,
                    min_energy,
                    1e5 -1e-9,
                    1e-9,
                    0.0,
                    convergence_tol,
                    absolute_diff_tol,
                    distance_tol );

  diff_cross_section =
    grid_generator.evaluateAdjointPDF( 5.0e-4, 5.0e-3, 1.0e-4 );
  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
                                  3.6854609980444470,
                                  1e-5 );

                                  diff_cross_section =
    grid_generator.evaluateAdjointPDF( 6.0e4, 1.0e5, 1.0e-4 );
  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
                                  4.4490736202820424e-06,
                                  1e-5 );

                                  diff_cross_section =
    grid_generator.evaluateAdjointPDF( 1.0e5-5.0e-8, 1.0e5, 1.0e-4 );
  TEST_EQUALITY_CONST( diff_cross_section, 0.0 );
  }
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung outgoing energy grid can be generated for H
TEUCHOS_UNIT_TEST( AdjointElectronGridGenerator,
                   generateAndEvaluateDistribution_brem_h )
{
  DataGen::AdjointElectronGridGenerator<BremsstrahlungReaction,Utility::LinLinLin>
    grid_generator( h_brem_reaction,
                    brem_energy_grid,
                    min_energy,
                    max_energy,
                    max_energy_nudge_value,
                    energy_to_outgoing_energy_nudge_value,
                    convergence_tol,
                    absolute_diff_tol,
                    distance_tol );

  // Set the primary energy grid
  std::vector<double> primary_energy_grid(2);
  primary_energy_grid[0] = 0.01;
  primary_energy_grid[1] = 1.0;

  // cross section values
  std::vector<double> cross_sections(2);
  cross_sections[0] = 1.0;
  cross_sections[1] = 1.0;

  
  std::map<double,std::vector<double> > outgoing_energy_grid, pdf;

  // Generate an outgoing energy grid at E=0.01 MeV
  grid_generator.generateAndEvaluateDistributionOnPrimaryEnergyGrid(
          outgoing_energy_grid,
          pdf,
          1e-6,
          primary_energy_grid,
          cross_sections,
          0 );

  // Check the generated outgoing energy grid
  TEST_EQUALITY_CONST( outgoing_energy_grid[0.01].size(), 991 );
  UTILITY_TEST_FLOATING_EQUALITY( outgoing_energy_grid[0.01].front(),
                                  0.01 + 2e-7 + 1e-9,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( outgoing_energy_grid[0.01].back(), 20.2, 1e-6 );

  // Check the evaluated pdf
  TEST_EQUALITY_CONST( pdf[0.01].size(), 991 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf[0.01].front(),
                                  1.0831428661238090e+06,
                                  1e-6 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf[0.01].back(),
                                  1.7350912728678646e-07,
                                  1e-6 );

  // Check the generated max energy grid
  TEST_EQUALITY_CONST( outgoing_energy_grid[1.0].size(), 482 );
  UTILITY_TEST_FLOATING_EQUALITY( outgoing_energy_grid[1.0].front(),
                                  1.0 + 2e-7 + 1e-9,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( outgoing_energy_grid[1.0].back(), 20.2, 1e-6 );

  // Check the evaluated cross section
  TEST_EQUALITY_CONST( pdf[1.0].size(), 482 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf[1.0].front(),
                                  1.4404679211211676e+05,
                                  1e-6 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf[1.0].back(),
                                  7.4522027154863208e-06,
                                  1e-6 );



  DataGen::AdjointElectronGridGenerator<BremsstrahlungReaction,Utility::LogLogLog>
    log_grid_generator( h_brem_reaction,
                        brem_energy_grid,
                        min_energy,
                        max_energy,
                        max_energy_nudge_value,
                        energy_to_outgoing_energy_nudge_value,
                        convergence_tol,
                        absolute_diff_tol,
                        distance_tol );

  // // Set the primary energy grid
  // std::vector<double> primary_energy_grid(2);
  // primary_energy_grid[0] = 0.01;
  // primary_energy_grid[1] = 1.0;

  // // cross section values
  // std::vector<double> cross_sections(2);
  // cross_sections[0] = 1.0;
  // cross_sections[1] = 1.0;

  // std::map<double,std::vector<double> > outgoing_energy_grid, pdf;

  // Generate an outgoing energy grid at E=0.01 MeV
  log_grid_generator.generateAndEvaluateDistributionOnPrimaryEnergyGrid(
          outgoing_energy_grid,
          pdf,
          1e-6,
          primary_energy_grid,
          cross_sections,
          0 );

  // Check the generated outgoing energy grid
  TEST_EQUALITY_CONST( outgoing_energy_grid[0.01].size(), 663 );
  UTILITY_TEST_FLOATING_EQUALITY( outgoing_energy_grid[0.01].front(),
                                  0.01 + 2e-7 + 1e-9,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( outgoing_energy_grid[0.01].back(), 20.2, 1e-6 );

  // Check the evaluated pdf
  TEST_EQUALITY_CONST( pdf[0.01].size(), 663 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf[0.01].front(),
                                  1.0831428661238090e+06,
                                  1e-6 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf[0.01].back(),
                                  1.7350912728678646e-07,
                                  1e-6 );

  // Check the generated max energy grid
  TEST_EQUALITY_CONST( outgoing_energy_grid[1.0].size(), 357 );
  UTILITY_TEST_FLOATING_EQUALITY( outgoing_energy_grid[1.0].front(),
                                  1.0 + 2e-7 + 1e-9,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( outgoing_energy_grid[1.0].back(), 20.2, 1e-6 );

  // Check the evaluated cross section
  TEST_EQUALITY_CONST( pdf[1.0].size(), 357 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf[1.0].front(),
                                  1.4404679211211676e+05,
                                  1e-6 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf[1.0].back(),
                                  7.4522027154863208e-06,
                                  1e-6 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_native_h_file_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_native_h_file",
                   &test_native_h_file_name,
                   "Test Native H file name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{

  // Create the H distributions
  {
    // Create the native data file container
    Data::ElectronPhotonRelaxationDataContainer
      data_container( test_native_h_file_name );

    // Extract the common electron energy grid
    Teuchos::ArrayRCP<double> union_energy_grid;
    union_energy_grid.assign(
      data_container.getElectronEnergyGrid().begin(),
      data_container.getElectronEnergyGrid().end() );

    Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
      new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>,false>(
                union_energy_grid,
                union_energy_grid[0],
                union_energy_grid[union_energy_grid.size()-1],
                union_energy_grid.size()/10 + 1 ) );

    double evaluation_tol = 3e-6;

    MonteCarlo::ElectroatomicReactionNativeFactory::createBremsstrahlungReaction(
        data_container,
        union_energy_grid,
        grid_searcher,
        h_brem_reaction,
        MonteCarlo::DIPOLE_DISTRIBUTION,
        evaluation_tol );

    brem_energy_grid = data_container.getBremsstrahlungEnergyGrid();

    // Extract the subshell information
    std::set<unsigned> subshells = data_container.getSubshells();

    Data::SubshellType subshell_type;

    std::set<unsigned>::iterator shell = subshells.begin();

    // Get the energies for which knock-on sampling tables are given
    ionization_energy_grid =
      data_container.getElectroionizationEnergyGrid( *shell );

    evaluation_tol = 1e-7;

    // Create the subshell electroelectric reaction
    MonteCarlo::ElectroatomicReactionNativeFactory::createSubshellElectroionizationReaction(
        data_container,
        union_energy_grid,
        grid_searcher,
        *shell,
        h_ionization_reaction,
        evaluation_tol );

    binding_energy = data_container.getSubshellBindingEnergy( *shell );

    max_ionization_subshell_adjoint_energy = 1e5 - 2.0*binding_energy;
  }
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstAdjointElectronGridGenerator.cpp
//---------------------------------------------------------------------------//
