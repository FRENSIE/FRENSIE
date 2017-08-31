//---------------------------------------------------------------------------//
//!
//! \file   tstElectroatomicReactionNativeFactoryHelpers.cpp
//! \author Luke Kersting
//! \brief  Electroatomic reaction factory using Native data unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectroatomicReactionNativeFactoryHelpers.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<Data::ElectronPhotonRelaxationDataContainer> data_container;
std::shared_ptr<MonteCarlo::ElectroatomicReaction> reaction;

double eval_tol = 1e-7;

//---------------------------------------------------------------------------//
// LinLinLog Tests.
//---------------------------------------------------------------------------//
// Check that an coupled elastic reaction can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactoryHelpers,
                   createCoupledElasticReaction )
{
  bool correlated_sampling_mode_on = true;

  reaction = MonteCarlo::createCoupledElasticReaction(
                *data_container,
                "LinLinLog",
                correlated_sampling_mode_on,
                eval_tol );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::COUPLED_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1.0e-5 );

  // Test that the stored cross section is correct
  double energy = 1.0e-5;
  double cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.48924e+09, 1e-12 );

  energy = 4.0e-4;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 4.43663545845802366734e+08, 1e-12 );

  energy = 1.0e5;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.11161e+06, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that a decoupled elastic reaction can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactoryHelpers,
                   createDecoupledElasticReaction )
{
  bool correlated_sampling_mode_on = true;

  reaction = MonteCarlo::createDecoupledElasticReaction(
                *data_container,
                "LinLinLog",
                correlated_sampling_mode_on,
                eval_tol );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::DECOUPLED_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1.0e-5 );

  // Test that the stored cross section is correct
  double energy = 1.0e-5;
  double cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.48924e+09, 1e-12 );

  energy = 4.0e-4;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 4.43663545845802366734e+08, 1e-12 );

  energy = 1.0e5;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.11161e+06, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an hybrid elastic reaction can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactory,
                   createHybridElasticReaction )
{
  bool correlated_sampling_mode_on = true;
  double cutoff_angle_cosine = 0.9;

    reaction = MonteCarlo::createHybridElasticReaction(
                *data_container,
                cutoff_angle_cosine,
                "LinLinLog",
                correlated_sampling_mode_on,
                1e-14 );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::HYBRID_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1.0e-5 );

  // Test that the stored cross section is correct
  double energy = 1.0e-5;
  double cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.4754121265454507e+09, 1e-12 );

  energy = 4.0e-4;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 5.2888196704079199e+08, 1e-12 );

  energy = 1.0e5;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.2050564844577009e-03, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an cutoff elastic reaction can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactoryHelpers,
                   createCutoffElasticReaction )
{
  bool correlated_sampling_mode_on = true;

  reaction = MonteCarlo::createCutoffElasticReaction(
                *data_container,
                1.0,
                "LinLinLog",
                correlated_sampling_mode_on,
                eval_tol );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1.0e-5 );

  // Test that the stored cross section is correct
  double energy = 1.0e-5;
  double cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.48924e9, 1e-12 );

  energy = 4.0e-4;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 4.436635458458e8, 1e-12 );

  energy = 1.0e5;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 8.83051e-2, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that a screened Rutherford elastic reaction can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactoryHelpers,
                   createScreenedRutherfordElasticReaction )
{
  bool correlated_sampling_mode_on = true;

  reaction = MonteCarlo::createScreenedRutherfordElasticReaction(
                *data_container,
                0.9,
                "LinLinLog",
                correlated_sampling_mode_on,
                eval_tol );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 6.654785 );

  // Test that the stored cross section is correct
  double energy = 1e1;
  double cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 3.722e5, 1e-12 );

  energy = 1e2;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.0561378e6, 1e-12 );

  energy = 1e5;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.1116099116949e6, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an moment preserving elastic reaction can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactoryHelpers,
                   createMomentPreservingElasticReaction )
{
  bool correlated_sampling_mode_on = true;

  reaction = MonteCarlo::createMomentPreservingElasticReaction(
                *data_container,
                0.9,
                "LinLinLog",
                correlated_sampling_mode_on,
                eval_tol );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::MOMENT_PRESERVING_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double energy = 1e-5;
  double cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 1.1063294415585944e+08, 1e-12 );

  energy = 4.0e-4;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 1.9356264227342713e+08, 1e-12 );

  energy = 1.0e5;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.2037700886489448e-03, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an atomic excitation reaction can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactoryHelpers,
                   createAtomicExcitationReaction )
{
  reaction = MonteCarlo::createAtomicExcitationReaction( *data_container );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1.0e-5 );

  // Test that the stored cross section is correct
  double cross_section = reaction->getCrossSection( 1.0e-5 );
  TEST_FLOATING_EQUALITY( cross_section, 8.75755e6, 1e-12 );

  cross_section = reaction->getCrossSection( 4.0e-4 );
  TEST_FLOATING_EQUALITY( cross_section, 6.22682e8, 1e-12 );

  cross_section = reaction->getCrossSection( 1.0e5 );
  TEST_FLOATING_EQUALITY( cross_section, 1.57861e6, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that the electroionization subshell reactions can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactoryHelpers,
                   createSubshellElectroelectricReactions )
{
  bool correlated_sampling_mode_on = true;
  bool unit_based_interpolation_mode_on = true;

  std::vector<std::shared_ptr<MonteCarlo::ElectroatomicReaction> >
  reactions = MonteCarlo::createSubshellElectroionizationReactions(
                               *data_container,
                               "LinLinLog",
                               correlated_sampling_mode_on,
                               unit_based_interpolation_mode_on,
                               eval_tol );

  TEST_EQUALITY_CONST( reactions.size(), 24 );

  // Test the first shell's reaction properties
  TEST_EQUALITY_CONST(
              reactions.front()->getReactionType(),
              MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reactions.front()->getThresholdEnergy(),
                       8.82899999999999935e-2 );

  // Test the first shell's stored cross section is correct
  double cross_section = reactions.front()->getCrossSection( 8.829e-2 );
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = reactions.front()->getCrossSection( 1.0e-1 );
  TEST_FLOATING_EQUALITY( cross_section, 9.2835e-1, 1e-12 );

  cross_section = reactions.front()->getCrossSection( 1.58489e2 );
  TEST_FLOATING_EQUALITY( cross_section, 2.788860e1, 1e-12 );

  cross_section = reactions.front()->getCrossSection( 1.0e5 );
  TEST_FLOATING_EQUALITY( cross_section, 3.649190e1, 1e-12 );

  // Check the last shell's reaction properties
  TEST_EQUALITY_CONST(
          reactions.back()->getReactionType(),
          MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reactions.back()->getThresholdEnergy(), 1.0e-5 );

  cross_section = reactions.back()->getCrossSection( 1.0e-5 );
  TEST_FLOATING_EQUALITY( cross_section, 1.0653e8, 1e-12 );

  cross_section = reactions.back()->getCrossSection( 1.0e-3 );
  TEST_FLOATING_EQUALITY( cross_section, 3.248850e7, 1e-12 );

  cross_section = reactions.back()->getCrossSection( 1.0 );
  TEST_FLOATING_EQUALITY( cross_section, 2.0335e5, 1e-12 );

  cross_section = reactions.back()->getCrossSection( 1.0e5 );
  TEST_FLOATING_EQUALITY( cross_section, 1.82234e5, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a basic (dipole distribution) bremsstrahlung reaction can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactoryHelpers,
                   createBremsstrahlungReaction_dipole )
{
  bool dipole_distribution_mode_on = true;
  bool correlated_sampling_mode_on = true;
  bool unit_based_interpolation_mode_on = false;

  reaction =
    MonteCarlo::createBremsstrahlungReaction( *data_container,
                                             dipole_distribution_mode_on,
                                             "LinLinLog",
                                             correlated_sampling_mode_on,
                                             unit_based_interpolation_mode_on,
                                             eval_tol );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1.0e-5 );

  // Test that the stored cross section is correct
  double cross_section =
            reaction->getCrossSection( reaction->getThresholdEnergy() );
  TEST_FLOATING_EQUALITY( cross_section, 4.8698e3, 1e-12 );

  cross_section = reaction->getCrossSection( 1.0e-3 );
  TEST_FLOATING_EQUALITY( cross_section, 9.528370e3, 1e-12 );

  cross_section = reaction->getCrossSection( 4.0e1 );
  TEST_FLOATING_EQUALITY( cross_section, 1.405050e3, 1e-12 );

  cross_section = reaction->getCrossSection( 1.0e5 );
  TEST_EQUALITY_CONST( cross_section, 1.95417e3 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
/* Check that a electroatom with detailed 2BS photon angular distribution
 * data can be created
 */
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactoryHelpers,
                   createBremsstrahlungReaction_2bs )
{
  bool dipole_distribution_mode_on = false;
  bool correlated_sampling_mode_on = true;
  bool unit_based_interpolation_mode_on = false;

  reaction =
    MonteCarlo::createBremsstrahlungReaction( *data_container,
                                             dipole_distribution_mode_on,
                                             "LinLinLog",
                                             correlated_sampling_mode_on,
                                             unit_based_interpolation_mode_on,
                                             eval_tol );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1.0e-5 );

  // Test that the stored cross section is correct
  double cross_section =
                reaction->getCrossSection( reaction->getThresholdEnergy() );
  TEST_FLOATING_EQUALITY( cross_section, 4.8698e3, 1e-12 );

  cross_section = reaction->getCrossSection( 1.0e-3 );
  TEST_FLOATING_EQUALITY( cross_section, 9.528370e3, 1e-12 );

  cross_section = reaction->getCrossSection( 4.0e1 );
  TEST_FLOATING_EQUALITY( cross_section, 1.405050e3, 1e-12 );

  cross_section = reaction->getCrossSection( 1.0e5 );
  TEST_EQUALITY_CONST( cross_section, 1.95417e3 );

  // Clear the reaction
  reaction.reset();
}


//---------------------------------------------------------------------------//
// LinLinLog Tests.
//---------------------------------------------------------------------------//
// Check that an coupled elastic reaction can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactoryHelpers,
                   createCoupledElasticReaction_lin )
{
  bool linlinlog_interpolation_mode_on = false;
  bool correlated_sampling_mode_on = true;

  reaction = MonteCarlo::createCoupledElasticReaction(
                *data_container,
                "LinLinLin",
                correlated_sampling_mode_on,
                eval_tol );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::COUPLED_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1.0e-5 );

  // Test that the stored cross section is correct
  double energy = 1.0e-5;
  double cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.48924e+09, 1e-12 );

  energy = 4.0e-4;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 4.43663545845802366734e+08, 1e-12 );

  energy = 1.0e5;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.11161e+06, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an cutoff elastic reaction can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactoryHelpers,
                   createCutoffElasticReaction_lin )
{
  bool linlinlog_interpolation_mode_on = false;
  bool correlated_sampling_mode_on = true;


  reaction = MonteCarlo::createCutoffElasticReaction(
                *data_container,
                1.0,
                "LinLinLin",
                correlated_sampling_mode_on,
                eval_tol );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1.0e-5 );

  // Test that the stored cross section is correct
  double energy = 1.0e-5;
  double cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.48924e9, 1e-12 );

  energy = 4.0e-4;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 4.436635458458e8, 1e-12 );

  energy = 1.0e5;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 8.83051e-2, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an moment preserving elastic reaction can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactoryHelpers,
                   createMomentPreservingElasticReaction_lin )
{
  bool linlinlog_interpolation_mode_on = false;
  bool correlated_sampling_mode_on = true;

  reaction = MonteCarlo::createMomentPreservingElasticReaction(
                        *data_container,
                        0.9,
                        "LinLinLin",
                        correlated_sampling_mode_on,
                        eval_tol );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::MOMENT_PRESERVING_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double energy = 1e-5;
  double cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 1.1063294415585944e+08, 1e-12 );

  energy = 4.0e-4;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 1.9356264227342713e+08, 1e-12 );

  energy = 1.0e5;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.2037700886489448e-03, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that the electroionization subshell reactions can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactoryHelpers,
                   createSubshellElectroionizationReactions_lin )
{
  bool linlinlog_interpolation_mode_on = false;
  bool correlated_sampling_mode_on = true;
  bool unit_based_interpolation_mode_on = false;

  std::vector<std::shared_ptr<MonteCarlo::ElectroatomicReaction> >
  reactions = MonteCarlo::createSubshellElectroionizationReactions(
                               *data_container,
                               "LinLinLin",
                               correlated_sampling_mode_on,
                               unit_based_interpolation_mode_on,
                               eval_tol );

  TEST_EQUALITY_CONST( reactions.size(), 24 );

  // Test the first shell's reaction properties
  TEST_EQUALITY_CONST(
              reactions.front()->getReactionType(),
              MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reactions.front()->getThresholdEnergy(),
                       8.82899999999999935e-2 );

  // Test the first shell's stored cross section is correct
  double cross_section = reactions.front()->getCrossSection( 8.829e-2 );
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = reactions.front()->getCrossSection( 1.0e-1 );
  TEST_FLOATING_EQUALITY( cross_section, 9.2835e-1, 1e-12 );

  cross_section = reactions.front()->getCrossSection( 1.58489e2 );
  TEST_FLOATING_EQUALITY( cross_section, 2.788860e1, 1e-12 );

  cross_section = reactions.front()->getCrossSection( 1.0e5 );
  TEST_FLOATING_EQUALITY( cross_section, 3.649190e1, 1e-12 );

  // Check the last shell's reaction properties
  TEST_EQUALITY_CONST(
          reactions.back()->getReactionType(),
          MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reactions.back()->getThresholdEnergy(), 1.0e-5 );

  cross_section = reactions.back()->getCrossSection( 1.0e-5 );
  TEST_FLOATING_EQUALITY( cross_section, 1.0653e8, 1e-12 );

  cross_section = reactions.back()->getCrossSection( 1.0e-3 );
  TEST_FLOATING_EQUALITY( cross_section, 3.248850e7, 1e-12 );

  cross_section = reactions.back()->getCrossSection( 1.0 );
  TEST_FLOATING_EQUALITY( cross_section, 2.0335e5, 1e-12 );

  cross_section = reactions.back()->getCrossSection( 1.0e5 );
  TEST_FLOATING_EQUALITY( cross_section, 1.82234e5, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a basic (dipole distribution) bremsstrahlung reaction can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactoryHelpers,
                   createBremsstrahlungReaction_dipole_lin )
{
  bool dipole_distribution_mode_on = true;
  bool linlinlog_interpolation_mode_on = false;
  bool correlated_sampling_mode_on = true;
  bool unit_based_interpolation_mode_on = false;

  reaction =
    MonteCarlo::createBremsstrahlungReaction( *data_container,
                                             dipole_distribution_mode_on,
                                             "LinLinLin",
                                             correlated_sampling_mode_on,
                                             unit_based_interpolation_mode_on,
                                             eval_tol );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1.0e-5 );

  // Test that the stored cross section is correct
  double cross_section =
    reaction->getCrossSection( reaction->getThresholdEnergy() );
  TEST_FLOATING_EQUALITY( cross_section, 4.8698e3, 1e-12 );

  cross_section = reaction->getCrossSection( 1.0e-3 );
  TEST_FLOATING_EQUALITY( cross_section, 9.528370e3, 1e-12 );

  cross_section = reaction->getCrossSection( 4.0e1 );
  TEST_FLOATING_EQUALITY( cross_section, 1.405050e3, 1e-12 );

  cross_section = reaction->getCrossSection( 1.0e5 );
  TEST_EQUALITY_CONST( cross_section, 1.95417e3 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
/* Check that a electroatom with detailed 2BS photon angular distribution
 * data can be created
 */
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactoryHelpers,
                   createBremsstrahlungReaction_2bs_lin )
{
  bool dipole_distribution_mode_on = false;
  bool linlinlog_interpolation_mode_on = false;
  bool correlated_sampling_mode_on = true;
  bool unit_based_interpolation_mode_on = false;

  reaction =
    MonteCarlo::createBremsstrahlungReaction( *data_container,
                                             dipole_distribution_mode_on,
                                             "LinLinLin",
                                             correlated_sampling_mode_on,
                                             unit_based_interpolation_mode_on,
                                             eval_tol );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1.0e-5 );

  // Test that the stored cross section is correct
  double cross_section =
    reaction->getCrossSection( reaction->getThresholdEnergy() );
  TEST_FLOATING_EQUALITY( cross_section, 4.8698e3, 1e-12 );

  cross_section = reaction->getCrossSection( 1.0e-3 );
  TEST_FLOATING_EQUALITY( cross_section, 9.528370e3, 1e-12 );

  cross_section = reaction->getCrossSection( 4.0e1 );
  TEST_FLOATING_EQUALITY( cross_section, 1.40505e3, 1e-12 );

  cross_section = reaction->getCrossSection( 1.0e5 );
  TEST_EQUALITY_CONST( cross_section, 1.95417e3 );

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
  eval_tol = 1e-7;

  // Create the native data file container
  data_container.reset( new Data::ElectronPhotonRelaxationDataContainer(
                             test_native_file_name ) );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstElectroatomicReactionNativeFactoryHelpers.cpp
//---------------------------------------------------------------------------//

