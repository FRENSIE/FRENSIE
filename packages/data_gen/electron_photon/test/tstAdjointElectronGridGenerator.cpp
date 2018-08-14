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

// FRENSIE Includes
#include "DataGen_AdjointElectronGridGenerator.hpp"
#include "MonteCarlo_BremsstrahlungElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroionizationSubshellElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroatomicReactionNativeFactory.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

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
FRENSIE_UNIT_TEST( AdjointElectronGridGenerator, getMinEnergy )
{
  DataGen::AdjointElectronGridGenerator<BremsstrahlungReaction,Utility::LinLinLin>
  grid_generator( h_brem_reaction,
                  brem_energy_grid );

  FRENSIE_CHECK_EQUAL( grid_generator.getMinEnergy(), 1e-5 );
}

//---------------------------------------------------------------------------//
// Check that the max energy can be returned
FRENSIE_UNIT_TEST( AdjointElectronGridGenerator, getMaxEnergy )
{
  DataGen::AdjointElectronGridGenerator<BremsstrahlungReaction,Utility::LinLinLin>
  grid_generator( h_brem_reaction,
                  brem_energy_grid );

  FRENSIE_CHECK_EQUAL( grid_generator.getMaxEnergy(), 20.0 );
}

//---------------------------------------------------------------------------//
// Check that the max energy nudge value can be set
FRENSIE_UNIT_TEST( AdjointElectronGridGenerator, setMaxEnergyNudgeValue )
{
  DataGen::AdjointElectronGridGenerator<BremsstrahlungReaction,Utility::LinLinLin>
  grid_generator( h_brem_reaction,
                  brem_energy_grid );

  FRENSIE_CHECK_EQUAL( grid_generator.getNudgedMaxEnergy(), 20.2 );

  grid_generator.setMaxEnergyNudgeValue( 0.5 );

  FRENSIE_CHECK_EQUAL( grid_generator.getNudgedMaxEnergy(), 20.5 );
}

//---------------------------------------------------------------------------//
// Check that the energy to max energy nudge value can be set
FRENSIE_UNIT_TEST( AdjointElectronGridGenerator,
                   setEnergyToOutgoingEnergyNudgeValue )
{
  DataGen::AdjointElectronGridGenerator<BremsstrahlungReaction,Utility::LinLinLin>
  grid_generator( h_brem_reaction,
                  brem_energy_grid );

  FRENSIE_CHECK_EQUAL( grid_generator.getNudgedEnergy( 1.0 ), 1.000001 );

  grid_generator.setEnergyToOutgoingEnergyNudgeValue( 1e-4 );

  FRENSIE_CHECK_EQUAL( grid_generator.getNudgedEnergy( 1.0 ), 1.0001 );
}

//---------------------------------------------------------------------------//
// Check that the hydrogen adjoint cross section can be evaluated
FRENSIE_UNIT_TEST( AdjointElectronGridGenerator,
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
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                                  1.4270327666466506e+14,
                                  1e-5 );

  cross_section =
    grid_generator.evaluateAdjointCrossSection( 1.88E-05, precision );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                                  8.0756097836880656e+13,
                                  1e-5 );

  cross_section =
    grid_generator.evaluateAdjointCrossSection( 1.123900E-02, precision );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                                  2.2705620821811357e+08,
                                  1e-5 );

  cross_section =
    grid_generator.evaluateAdjointCrossSection( 8.75350E-01, precision );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                                  1.3240479063194754e+05,
                                  1e-5 );

  cross_section =
    grid_generator.evaluateAdjointCrossSection(
                            max_ionization_subshell_adjoint_energy - 6.0e-8,
                            precision );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                                  6.1798997319080183e+04,
                                  1e-5 );

  cross_section =
    grid_generator.evaluateAdjointCrossSection(
                                        max_ionization_subshell_adjoint_energy,
                                        precision );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                                  6.1716910118185078e+04,
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
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                                  4.4272257691288004e+01,
                                  1e-5 );

  cross_section =
    grid_generator.evaluateAdjointCrossSection( 5.0e-4, precision );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                                  2.5591179271932941e+01,
                                  1e-5 );

  cross_section =
    grid_generator.evaluateAdjointCrossSection( 6.0e4, precision );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                                  7.6528293743103137e-01,
                                  1e-5 );

  cross_section =
    grid_generator.evaluateAdjointCrossSection( 1.0e5, precision );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );
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
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                                  4.4272257691288004e+01,
                                  1e-5 );

  cross_section =
    grid_generator.evaluateAdjointCrossSection( 5.0e-4, precision );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                                  2.5591179271932941e+01,
                                  1e-5 );

  cross_section =
    grid_generator.evaluateAdjointCrossSection( 6.0e4, precision );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
                                  7.6528293743103137e-01,
                                  1e-5 );

  cross_section =
    grid_generator.evaluateAdjointCrossSection( 1.0e5, precision );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );
  }
}

//---------------------------------------------------------------------------//
// Check that the hydrogen adjoint differential cross section can be evaluated
FRENSIE_UNIT_TEST( AdjointElectronGridGenerator,
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
  FRENSIE_CHECK_FLOATING_EQUALITY( diff_cross_section,
                                  7.2123706343473135e-03,
                                  1e-5 );

                                  diff_cross_section =
    grid_generator.evaluateAdjointPDF( 1.123900E-02, 3.16228, 1.0e-4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( diff_cross_section,
                                  9.3924825254675727e-06,
                                  1e-6 );

                                  diff_cross_section =
    grid_generator.evaluateAdjointPDF( 8.75350E-01,
                                       max_ionization_subshell_adjoint_energy,
                                       1.0e-4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( diff_cross_section,
                                  2.5384871967044380e-06,
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
  FRENSIE_CHECK_FLOATING_EQUALITY( diff_cross_section,
                                  1.2871056115631994,
                                  1e-5 );

                                  diff_cross_section =
    grid_generator.evaluateAdjointPDF( 6.0e4, 1.0e5, 1.0e-4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( diff_cross_section,
                                  8.2555408100904352e-07,
                                  1e-5 );

                                  diff_cross_section =
    grid_generator.evaluateAdjointPDF( 1.0e5-5.0e-8, 1.0e5, 1.0e-4 );
  FRENSIE_CHECK_EQUAL( diff_cross_section, 0.0 );
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
  FRENSIE_CHECK_FLOATING_EQUALITY( diff_cross_section,
                                  1.2871056115631994,
                                  1e-5 );

                                  diff_cross_section =
    grid_generator.evaluateAdjointPDF( 6.0e4, 1.0e5, 1.0e-4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( diff_cross_section,
                                  8.2555408100904352e-07,
                                  1e-5 );

                                  diff_cross_section =
    grid_generator.evaluateAdjointPDF( 1.0e5-5.0e-8, 1.0e5, 1.0e-4 );
  FRENSIE_CHECK_EQUAL( diff_cross_section, 0.0 );
  }
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung outgoing energy grid can be generated for H
FRENSIE_UNIT_TEST( AdjointElectronGridGenerator,
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
  FRENSIE_CHECK_EQUAL( outgoing_energy_grid[0.01].size(), 1066 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy_grid[0.01].front(),
                                  0.01 + 2e-7 + 1e-9,
                                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy_grid[0.01].back(), 20.2, 1e-6 );

  // Check the evaluated pdf
  FRENSIE_CHECK_EQUAL( pdf[0.01].size(), 1066 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf[0.01].front(),
                                  1.5037731193391415e+06,
                                  1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf[0.01].back(),
                                  1.3739035660758732e-08,
                                  1e-6 );
std::cout << std::setprecision(16) << std::scientific << "pdf[0.01].front() = \t" << pdf[0.01].front() << std::endl;
std::cout << std::setprecision(16) << std::scientific << "pdf[0.01].back() = \t" << pdf[0.01].back() << std::endl;

  // Check the generated max energy grid
  FRENSIE_CHECK_EQUAL( outgoing_energy_grid[1.0].size(), 515 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy_grid[1.0].front(),
                                  1.0 + 2e-7 + 1e-9,
                                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy_grid[1.0].back(), 20.2, 1e-6 );

  // Check the evaluated cross section
  FRENSIE_CHECK_EQUAL( pdf[1.0].size(), 515 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf[1.0].front(),
                                  2.0004966599906672e+05,
                                  1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf[1.0].back(),
                                  4.4407679324133394e-06,
                                  1e-6 );
std::cout << std::setprecision(16) << std::scientific << "pdf[1.0].front() = \t" << pdf[1.0].front() << std::endl;
std::cout << std::setprecision(16) << std::scientific << "pdf[1.0].back() = \t" << pdf[1.0].back() << std::endl;



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
  FRENSIE_CHECK_EQUAL( outgoing_energy_grid[0.01].size(), 781 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy_grid[0.01].front(),
                                  0.01 + 2e-7 + 1e-9,
                                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy_grid[0.01].back(), 20.2, 1e-6 );

  // Check the evaluated pdf
  FRENSIE_CHECK_EQUAL( pdf[0.01].size(), 781 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf[0.01].front(),
                                  1.5037731193391415e+06,
                                  1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf[0.01].back(),
                                  1.3739035660758732e-08,
                                  1e-6 );
std::cout << std::setprecision(16) << std::scientific << "pdf[0.01].front() = \t" << pdf[0.01].front() << std::endl;
std::cout << std::setprecision(16) << std::scientific << "pdf[0.01].back() = \t" << pdf[0.01].back() << std::endl;

  // Check the generated max energy grid
  FRENSIE_CHECK_EQUAL( outgoing_energy_grid[1.0].size(), 475 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy_grid[1.0].front(),
                                  1.0 + 2e-7 + 1e-9,
                                  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy_grid[1.0].back(), 20.2, 1e-6 );

  // Check the evaluated cross section
  FRENSIE_CHECK_EQUAL( pdf[1.0].size(), 475 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf[1.0].front(),
                                  2.0004966599906672e+05,
                                  1e-6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf[1.0].back(),
                                  4.4407679324133394e-06,
                                  1e-6 );
std::cout << std::setprecision(16) << std::scientific << "pdf[1.0].front() = \t" << pdf[1.0].front() << std::endl;
std::cout << std::setprecision(16) << std::scientific << "pdf[1.0].back() = \t" << pdf[1.0].back() << std::endl;

}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_native_h_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_native_h_file",
                                        test_native_h_file_name, "",
                                        "Test Native H file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{

  // Create the H distributions
  {
    // Create the native data file container
    Data::ElectronPhotonRelaxationDataContainer
      data_container( test_native_h_file_name );

    // Extract the common electron energy grid
  std::shared_ptr<std::vector<double> > union_energy_grid(
       new std::vector<double>( data_container.getElectronEnergyGrid() ) );

  std::shared_ptr<Utility::HashBasedGridSearcher<double> > grid_searcher(
      new Utility::StandardHashBasedGridSearcher<std::vector<double>,false>(
                union_energy_grid,
                union_energy_grid->front(),
                union_energy_grid->back(),
                union_energy_grid->size()/10 + 1 ) );

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

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstAdjointElectronGridGenerator.cpp
//---------------------------------------------------------------------------//
