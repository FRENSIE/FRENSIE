//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointElectroatomicReactionNativeFactory.cpp
//! \author Luke Kersting
//! \brief  Adjoint electroatomic reaction factory using Native data unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatomicReactionNativeFactory.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

MonteCarlo::BremsstrahlungAngularDistributionType photon_distribution_function;
std::shared_ptr<Data::AdjointElectronPhotonRelaxationDataContainer> data_container;
Teuchos::ArrayRCP<double> energy_grid;
Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher;
std::shared_ptr<MonteCarlo::AdjointElectroatomicReaction> reaction;

bool correlated_sampling_mode_on = true;
bool unit_based_interpolation_mode_on = true;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that an coupled elastic reaction can be created
TEUCHOS_UNIT_TEST( AdjointElectroatomicReactionNativeFactory,
                   createCoupledElasticReaction )
{
  double evaluation_tol = 1e-7;

  MonteCarlo::AdjointElectroatomicReactionNativeFactory::createCoupledElasticReaction<Utility::LinLinLog>(
                *data_container,
                energy_grid,
                grid_searcher,
                reaction,
                correlated_sampling_mode_on,
                evaluation_tol );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::COUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double energy = 1e-5;
  double cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.74896E+08, 1e-12 );

  energy = 1e-3;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.80490481543817E+06, 1e-12 );

  energy = 20.0;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 1.3022122514987E+04, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an coupled elastic reaction can be created
TEUCHOS_UNIT_TEST( AdjointElectroatomicReactionNativeFactory,
                   createDecoupledElasticReaction )
{
  double evaluation_tol = 1e-7;

  MonteCarlo::AdjointElectroatomicReactionNativeFactory::createDecoupledElasticReaction<Utility::LinLinLog>(
                *data_container,
                energy_grid,
                grid_searcher,
                reaction,
                correlated_sampling_mode_on,
                evaluation_tol );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::DECOUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double energy = 1e-5;
  double cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.74896E+08, 1e-12 );

  energy = 1e-3;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.80490481543817E+06, 1e-12 );

  energy = 20.0;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 1.3022122514987E+04, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an cutoff elastic reaction can be created
TEUCHOS_UNIT_TEST( AdjointElectroatomicReactionNativeFactory,
                   createCutoffElasticReaction )
{
  double cutoff_angle_cosine = 1.0;
  double evaluation_tol = 1e-7;

  MonteCarlo::AdjointElectroatomicReactionNativeFactory::createCutoffElasticReaction<Utility::LinLinLog>(
                *data_container,
                energy_grid,
                grid_searcher,
                reaction,
                cutoff_angle_cosine,
                correlated_sampling_mode_on,
                evaluation_tol );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::CUTOFF_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double energy = 1e-5;
  double cross_section =
    reaction->getCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section, 2.74896E+08, 1e-12 );

  energy = 1e-3;
  cross_section = reaction->getCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section, 2.80490481543817E+06, 1e-12 );

  energy = 20.0;
  cross_section = reaction->getCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section, 3.04727623729037E+02, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that a screened Rutherford elastic reaction can be created
TEUCHOS_UNIT_TEST( AdjointElectroatomicReactionNativeFactory,
                   createScreenedRutherfordElasticReaction )
{
  MonteCarlo::AdjointElectroatomicReactionNativeFactory::createScreenedRutherfordElasticReaction(
                *data_container,
                energy_grid,
                grid_searcher,
                reaction );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
       MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 3.12509629531249944e-01 );

  // Test that the stored cross section is correct
  double energy = 1.0;
  double cross_section =
    reaction->getCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section, 3.49009928113168E+03, 1e-12 );

  energy = 10.0;
  cross_section = reaction->getCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section, 1.20603199788180E+04, 1e-12 );

  energy = 20.0;
  cross_section = reaction->getCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section, 1.27173948912580E+04, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an moment preserving elastic reaction can be created
TEUCHOS_UNIT_TEST( AdjointElectroatomicReactionNativeFactory,
                   createMomentPreservingElasticReaction )
{
  double cutoff_angle_cosine = 0.9;
  double evaluation_tol = 1e-7;

  MonteCarlo::AdjointElectroatomicReactionNativeFactory::createMomentPreservingElasticReaction<Utility::LinLinLog>(
                *data_container,
                energy_grid,
                grid_searcher,
                reaction,
                cutoff_angle_cosine,
                correlated_sampling_mode_on,
                evaluation_tol );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
         MonteCarlo::MOMENT_PRESERVING_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double energy = 1e-5;
  double cross_section =
    reaction->getCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section, 1.2217606103336416e+07, 1e-12 );

  energy = 1e-3;
  cross_section = reaction->getCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section, 1.6696690569928249e+06, 1e-12 );

  energy = 20.0;
  cross_section = reaction->getCrossSection( energy );

  TEST_FLOATING_EQUALITY( cross_section, 2.0498802209908908, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an atomic excitation reaction can be created
TEUCHOS_UNIT_TEST( AdjointElectroatomicReactionNativeFactory,
                   createAtomicExcitationReaction )
{
  MonteCarlo::AdjointElectroatomicReactionNativeFactory::createAtomicExcitationReaction(
                               *data_container,
                               energy_grid,
                               grid_searcher,
                               reaction);

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                 MonteCarlo::ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double cross_section =
    reaction->getCrossSection( 1e-5 );

  TEST_FLOATING_EQUALITY( cross_section, 6.12229969785753563e+07, 1e-12 );

  cross_section = reaction->getCrossSection( 6.20350838928222553e-04 );

  TEST_FLOATING_EQUALITY( cross_section, 1.58264020015645381e+07, 1e-12 );

  cross_section = reaction->getCrossSection( 20.0 );

  TEST_FLOATING_EQUALITY( cross_section, 8.18292998537648382e+04, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that the electroionization subshell reactions can be created
TEUCHOS_UNIT_TEST( AdjointElectroatomicReactionNativeFactory,
                   createSubshellElectroelectricReactions )
{
  double evaluation_tol = 1e-7;

  std::vector<std::shared_ptr<MonteCarlo::AdjointElectroatomicReaction> > reactions;

  MonteCarlo::AdjointElectroatomicReactionNativeFactory::createSubshellElectroionizationReactions(
        *data_container,
        energy_grid,
        grid_searcher,
        reactions,
        correlated_sampling_mode_on,
        unit_based_interpolation_mode_on,
        evaluation_tol );

  TEST_EQUALITY_CONST( reactions.size(), 1 );

  // Test the first shell's reaction properties
  TEST_EQUALITY_CONST( reactions.front()->getReactionType(),
      MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reactions.front()->getThresholdEnergy(),
                       1e-5 );

  // Test the first shell's stored cross section is correct
  double cross_section = reactions.front()->getCrossSection( 1e-5 );
  TEST_FLOATING_EQUALITY( cross_section, 4.6878251924030220e+10, 1e-12 );

  cross_section = reactions.front()->getCrossSection( 1e-3 );
  TEST_FLOATING_EQUALITY( cross_section, 1.6628669703671712e+07, 1e-12 );

  cross_section = reactions.front()->getCrossSection( 20.0 );
  TEST_FLOATING_EQUALITY( cross_section, 6.2903317255053284e+04, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a basic (dipole distribution) bremsstrahlung reaction can be created
TEUCHOS_UNIT_TEST( AdjointElectroatomicReactionNativeFactory,
                   createBremsstrahlungReaction_dipole )
{
  double evaluation_tol = 1e-7;

  MonteCarlo::AdjointElectroatomicReactionNativeFactory::createBremsstrahlungReaction(
        *data_container,
        energy_grid,
        grid_searcher,
        reaction,
        correlated_sampling_mode_on,
        unit_based_interpolation_mode_on,
        evaluation_tol );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                    MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double cross_section = reaction->getCrossSection( reaction->getThresholdEnergy() );
  TEST_FLOATING_EQUALITY( cross_section, 4.6179443997604473e+01, 1e-12 );

  cross_section = reaction->getCrossSection( 1e-3 );
  TEST_FLOATING_EQUALITY( cross_section, 1.6612628318967477e+01, 1e-12 );

  cross_section = reaction->getCrossSection( 20.0 );
  TEST_FLOATING_EQUALITY( cross_section, 7.7113235533702451e-01, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_native_file_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_native_file",
                   &test_native_file_name,
                   "Test Native file name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Create the native data file container
  data_container.reset( new Data::AdjointElectronPhotonRelaxationDataContainer(
                             test_native_file_name ) );

  // Extract the common energy grid
  energy_grid.deepCopy( data_container->getAdjointElectronEnergyGrid() );

  // Create the hash-based grid searcher
  grid_searcher.reset(
    new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<double>,false>(
                 energy_grid,
                 100 ) );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstAdjointElectroatomicReactionNativeFactory.cpp
//---------------------------------------------------------------------------//

