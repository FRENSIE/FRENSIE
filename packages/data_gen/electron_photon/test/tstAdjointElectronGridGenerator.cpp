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

typedef MonteCarlo::ElectroionizationSubshellElectroatomicReaction<Utility::LinLin>
  ElectroionizationReaction;

typedef MonteCarlo::BremsstrahlungElectroatomicReaction<Utility::LinLin> 
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
                                  1.24070944606782875e15,
                                  1e-5 );

  cross_section =
    grid_generator.evaluateAdjointCrossSection( 1.88E-05, precision );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  1.20814984485908125e15,
                                  1e-5 );

  cross_section =
    grid_generator.evaluateAdjointCrossSection( 1.123900E-02, precision );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  1.1037229360055688477e12,
                                  1e-5 );

  cross_section =
    grid_generator.evaluateAdjointCrossSection( 8.75350E-01, precision );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  1.7717016620250481367e8,
                                  1e-5 );

  cross_section =
    grid_generator.evaluateAdjointCrossSection(
        max_ionization_subshell_adjoint_energy - 6.0e-8,
        precision );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  6.2498959635742576211e4,
                                  1e-5 );

  cross_section =
    grid_generator.evaluateAdjointCrossSection(
        max_ionization_subshell_adjoint_energy,
        precision );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  6.2415414649009922869e4,
                                  1e-5 );
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

  cross_section =
    grid_generator.evaluateAdjointCrossSection( 1.0e-5, precision );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  6.4064216868408593086e1,
                                  1e-5 );

  cross_section =
    grid_generator.evaluateAdjointCrossSection( 5.0e-4, precision );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  3.1844399889852791574e1,
                                  1e-5 );

  cross_section =
    grid_generator.evaluateAdjointCrossSection( 6.0e4, precision );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section,
                                  1.435228075256366651e2,
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
                                  5.31863324213552096306e-04,
                                  1e-5 );

  diff_cross_section =
    grid_generator.evaluateAdjointPDF( 1.123900E-02, 3.16228, 1.0e-4 );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
                                  1.99114216905034926044e-09,
                                  1e-6 );

  diff_cross_section =
    grid_generator.evaluateAdjointPDF( 8.75350E-01,
                                       max_ionization_subshell_adjoint_energy,
                                       1.0e-4 );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
                                  1.89708690449891991391e-09,
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
                                  1.03626700429070384146,
                                  1e-5 );

  diff_cross_section =
    grid_generator.evaluateAdjointPDF( 6.0e4, 1.0e5, 1.0e-4 );

  UTILITY_TEST_FLOATING_EQUALITY( diff_cross_section,
                                  4.40196553421104620864e-09,
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
  TEST_EQUALITY_CONST( outgoing_energy_grid[0.01].size(), 489 );
  UTILITY_TEST_FLOATING_EQUALITY( outgoing_energy_grid[0.01].front(),
                                  0.01 + 2e-7 + 1e-9,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( outgoing_energy_grid[0.01].back(), 20.2, 1e-6 );

  // Check the evaluated pdf
  TEST_EQUALITY_CONST( pdf[0.01].size(), 489 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf[0.01].front(),
                                  1.83873405521627049893e+06,
                                  1e-6 );

  UTILITY_TEST_FLOATING_EQUALITY( pdf[0.01].back(), 
                                  6.07022103854779505606e-06,
                                  1e-6 );

  // Check the generated max energy grid
  TEST_EQUALITY_CONST( outgoing_energy_grid[1.0].size(), 398 );
  UTILITY_TEST_FLOATING_EQUALITY( outgoing_energy_grid[1.0].front(),
                                  1.0 + 2e-7 + 1e-9,
                                  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( outgoing_energy_grid[1.0].back(), 20.2, 1e-6 );

  // Check the evaluated cross section
  TEST_EQUALITY_CONST( pdf[1.0].size(), 398 );
  UTILITY_TEST_FLOATING_EQUALITY( pdf[1.0].front(),
                                  2.08058824803910742048e+05,
                                  1e-6 );

  UTILITY_TEST_FLOATING_EQUALITY( pdf[1.0].back(),
                                  2.55274262000830477661e-04,
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
  bool correlated_sampling_mode_on = true;
  bool unit_based_interpolation_mode_on = true;
  double evaluation_tol = 1e-7;

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

    MonteCarlo::ElectroatomicReactionNativeFactory::createBremsstrahlungReaction(
        data_container,
        union_energy_grid,
        grid_searcher,
        h_brem_reaction,
        MonteCarlo::DIPOLE_DISTRIBUTION,
        correlated_sampling_mode_on,
        unit_based_interpolation_mode_on,
        evaluation_tol );

    brem_energy_grid = data_container.getBremsstrahlungEnergyGrid();

    // Extract the subshell information
    std::set<unsigned> subshells = data_container.getSubshells();

    Data::SubshellType subshell_type;

    std::set<unsigned>::iterator shell = subshells.begin();

    // Get the energies for which knock-on sampling tables are given
    ionization_energy_grid =
      data_container.getElectroionizationEnergyGrid( *shell );

    // Create the subshell electroelectric reaction
    MonteCarlo::ElectroatomicReactionNativeFactory::createSubshellElectroionizationReaction(
        data_container,
        union_energy_grid,
        grid_searcher,
        *shell,
        h_ionization_reaction,
        correlated_sampling_mode_on,
        unit_based_interpolation_mode_on,
        evaluation_tol );

    binding_energy = data_container.getSubshellBindingEnergy( *shell );

    max_ionization_subshell_adjoint_energy = 1e5 - 2.0*binding_energy;
  }
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstAdjointElectronGridGenerator.cpp
//---------------------------------------------------------------------------//
