//---------------------------------------------------------------------------//
//!
//! \file   tstElectroatomicReactionNativeFactory.cpp
//! \author Luke Kersting
//! \brief  Electroatomic reaction factory using Native data unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectroatomicReactionNativeFactory.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"
#include "MonteCarlo_ElasticElectronDistributionType.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

MonteCarlo::BremsstrahlungAngularDistributionType photon_distribution_function;
std::shared_ptr<Data::ElectronPhotonRelaxationDataContainer> data_container;
Teuchos::ArrayRCP<double> energy_grid;
Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher;
std::shared_ptr<MonteCarlo::ElectroatomicReaction> reaction;

double eval_tol;

//---------------------------------------------------------------------------//
// LinLinLog Tests.
//---------------------------------------------------------------------------//
// Check that an coupled elastic reaction can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactory,
                   createCoupledElasticReaction_LogLogCosLog )
{
  MonteCarlo::CoupledElasticSamplingMethod sampling_method =
    MonteCarlo::TWO_D_UNION;

  MonteCarlo::ElectroatomicReactionNativeFactory::createCoupledElasticReaction<Utility::Correlated<Utility::LogLogCosLog<true> > >(
                *data_container,
                energy_grid,
                grid_searcher,
                reaction,
                sampling_method,
                1e-7 );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::COUPLED_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double energy = 1e-5;
  double cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.48924e+09, 1e-12 );

  energy = 4e-4;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 4.43663545845802366734e+08, 1e-12 );

  energy = 1e5;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.11161e+06, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an decoupled elastic reaction can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactory,
                   createDecoupledElasticReaction_LogLogCosLog )
{
  MonteCarlo::ElectroatomicReactionNativeFactory::createDecoupledElasticReaction<Utility::Correlated<Utility::LogLogCosLog<false> > >(
                *data_container,
                energy_grid,
                grid_searcher,
                reaction,
                1e-7 );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::DECOUPLED_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double energy = 1e-5;
  double cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.48924e+09, 1e-12 );

  energy = 4e-4;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 4.43663545845802366734e+08, 1e-12 );

  energy = 1e5;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.11161e+06, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an hybrid elastic reaction can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactory,
                   createHybridElasticReaction_LogLogCosLog )
{
  double cutoff_angle_cosine = 0.9;

  MonteCarlo::ElectroatomicReactionNativeFactory::createHybridElasticReaction<Utility::Correlated<Utility::LogLogCosLog<true> > >(
                *data_container,
                energy_grid,
                grid_searcher,
                reaction,
                cutoff_angle_cosine,
                1e-14 );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::HYBRID_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double energy = 1e-5;
  double cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.4754121265454507e+09, 1e-12 );

  energy = 4e-4;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 3.2786275809074390e+08, 1e-12 );

  energy = 1e5;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.2050564844577009e-03, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an cutoff elastic reaction can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactory,
                   createCutoffElasticReaction_LogLogCosLog )
{
  MonteCarlo::ElectroatomicReactionNativeFactory::createCutoffElasticReaction<Utility::Correlated<Utility::LogLogCosLog<false> > >(
                *data_container,
                energy_grid,
                grid_searcher,
                reaction,
                1.0,
                1e-7 );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double energy = 1e-5;
  double cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.48924e9, 1e-12 );

  energy = 4e-4;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 4.436635458458e8, 1e-12 );

  energy = 1e5;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 8.83051e-2, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// LinLinLog Tests.
//---------------------------------------------------------------------------//
// Check that an coupled elastic reaction can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactory,
                   createCoupledElasticReaction_LinLinLog )
{
  MonteCarlo::CoupledElasticSamplingMethod sampling_method =
    MonteCarlo::TWO_D_UNION;

  MonteCarlo::ElectroatomicReactionNativeFactory::createCoupledElasticReaction<Utility::Correlated<Utility::LinLinLog> >(
                *data_container,
                energy_grid,
                grid_searcher,
                reaction,
                sampling_method,
                1e-7 );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::COUPLED_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double energy = 1e-5;
  double cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.48924e+09, 1e-12 );

  energy = 4e-4;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 4.43663545845802366734e+08, 1e-12 );

  energy = 1e5;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.11161e+06, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an decoupled elastic reaction can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactory,
                   createDecoupledElasticReaction_LinLinLog )
{
  MonteCarlo::ElectroatomicReactionNativeFactory::createDecoupledElasticReaction<Utility::Correlated<Utility::LinLinLog> >(
                *data_container,
                energy_grid,
                grid_searcher,
                reaction,
                1e-7 );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::DECOUPLED_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double energy = 1e-5;
  double cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.48924e+09, 1e-12 );

  energy = 4e-4;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 4.43663545845802366734e+08, 1e-12 );

  energy = 1e5;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.11161e+06, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an hybrid elastic reaction can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactory,
                   createHybridElasticReaction_LinLinLog )
{
  double cutoff_angle_cosine = 0.9;

  MonteCarlo::ElectroatomicReactionNativeFactory::createHybridElasticReaction<Utility::Correlated<Utility::LinLinLog> >(
                *data_container,
                energy_grid,
                grid_searcher,
                reaction,
                cutoff_angle_cosine,
                1e-14 );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::HYBRID_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double energy = 1e-5;
  double cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.4754121265454507e+09, 1e-12 );

  energy = 4e-4;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 4.0310818301823217e+08, 1e-12 );

  energy = 1e5;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.2050564844577009e-03, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an cutoff elastic reaction can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactory,
                   createCutoffElasticReaction_LinLinLog )
{
  MonteCarlo::ElectroatomicReactionNativeFactory::createCutoffElasticReaction<Utility::Correlated<Utility::LinLinLog> >(
                *data_container,
                energy_grid,
                grid_searcher,
                reaction,
                1.0,
                1e-7 );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double energy = 1e-5;
  double cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.48924e9, 1e-12 );

  energy = 4e-4;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 4.436635458458e8, 1e-12 );

  energy = 1e5;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 8.83051e-2, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that a screened Rutherford elastic reaction can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactory,
                   createScreenedRutherfordElasticReaction )
{
  MonteCarlo::ElectroatomicReactionNativeFactory::createScreenedRutherfordElasticReaction(
                *data_container,
                energy_grid,
                grid_searcher,
                reaction );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 7.0 );

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
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactory,
                   createMomentPreservingElasticReaction_LinLinLog )
{
  MonteCarlo::ElectroatomicReactionNativeFactory::createMomentPreservingElasticReaction<Utility::Correlated<Utility::LinLinLog> >(
                *data_container,
                energy_grid,
                grid_searcher,
                reaction,
                0.9,
                1e-7 );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::MOMENT_PRESERVING_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double energy = 1e-5;
  double cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 1.1063294415585944e+08, 1e-12 );

  energy = 4e-4;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 6.7788808128946811e+07, 1e-12 );

  energy = 1e5;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.2037700886489448e-03, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an atomic excitation reaction can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactory,
                   createAtomicExcitationReaction )
{
  MonteCarlo::ElectroatomicReactionNativeFactory::createAtomicExcitationReaction(
                               *data_container,
                               energy_grid,
                               grid_searcher,
                               reaction);

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double cross_section = reaction->getCrossSection( 1e-5 );
  TEST_FLOATING_EQUALITY( cross_section, 8.75755e6, 1e-12 );

  cross_section = reaction->getCrossSection( 4e-4 );
  TEST_FLOATING_EQUALITY( cross_section, 6.22682e8, 1e-12 );

  cross_section = reaction->getCrossSection( 1e5 );
  TEST_FLOATING_EQUALITY( cross_section, 1.57861e6, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that the electroionization subshell reactions can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactory,
                   createSubshellElectroionizationReactions )
{
  std::vector<std::shared_ptr<MonteCarlo::ElectroatomicReaction> > reactions;

  MonteCarlo::ElectroatomicReactionNativeFactory::createSubshellElectroionizationReactions<MonteCarlo::ElectroatomicReaction,Utility::UnitBaseCorrelated<Utility::LinLinLog> >(
                               *data_container,
                               energy_grid,
                               grid_searcher,
                               reactions,
                               eval_tol );

  TEST_EQUALITY_CONST( reactions.size(), 24 );

  // Test the first shell's reaction properties
  TEST_EQUALITY_CONST(
              reactions.front()->getReactionType(),
              MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reactions.front()->getThresholdEnergy(),
                       8.829e-2 );

  // Test the first shell's stored cross section is correct
  double cross_section = reactions.front()->getCrossSection( 8.829e-2 );
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = reactions.front()->getCrossSection( 1e-1 );
  TEST_FLOATING_EQUALITY( cross_section, 9.2835e-1, 1e-12 );

  cross_section = reactions.front()->getCrossSection( 1.58489e2 );
  TEST_FLOATING_EQUALITY( cross_section, 2.78886e1, 1e-12 );

  cross_section = reactions.front()->getCrossSection( 1e5 );
  TEST_FLOATING_EQUALITY( cross_section, 3.64919e1, 1e-12 );

  // Check the last shell's reaction properties
  TEST_EQUALITY_CONST(
          reactions.back()->getReactionType(),
          MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reactions.back()->getThresholdEnergy(), 1e-5 );

  cross_section = reactions.back()->getCrossSection( 1e-5 );
  TEST_FLOATING_EQUALITY( cross_section, 1.0653e8, 1e-12 );

  cross_section = reactions.back()->getCrossSection( 1e-3 );
  TEST_FLOATING_EQUALITY( cross_section, 3.24885e7, 1e-12 );

  cross_section = reactions.back()->getCrossSection( 1.0 );
  TEST_FLOATING_EQUALITY( cross_section, 2.0335e5, 1e-12 );

  cross_section = reactions.back()->getCrossSection( 1e5 );
  TEST_FLOATING_EQUALITY( cross_section, 1.82234e5, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a basic (dipole distribution) bremsstrahlung reaction can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactory,
                   createBremsstrahlungReaction_dipole )
{
  photon_distribution_function = MonteCarlo::DIPOLE_DISTRIBUTION;

  MonteCarlo::ElectroatomicReactionNativeFactory::createBremsstrahlungReaction<MonteCarlo::ElectroatomicReaction,Utility::UnitBaseCorrelated<Utility::LogLogLog> >(
                               *data_container,
                               energy_grid,
                               grid_searcher,
                               reaction,
                               photon_distribution_function,
                               eval_tol );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double cross_section =
            reaction->getCrossSection( reaction->getThresholdEnergy() );
  TEST_FLOATING_EQUALITY( cross_section, 4.8698e3, 1e-12 );

  cross_section = reaction->getCrossSection( 1e-3 );
  TEST_FLOATING_EQUALITY( cross_section, 9.52837e3, 1e-12 );

  cross_section = reaction->getCrossSection( 4e1 );
  TEST_FLOATING_EQUALITY( cross_section, 1.40505e3, 1e-12 );

  cross_section = reaction->getCrossSection( 1e5 );
  TEST_FLOATING_EQUALITY( cross_section, 1.95417e3, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
/* Check that a electroatom with detailed 2BS photon angular distribution
 * data can be created
 */
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactory,
                   createBremsstrahlungReaction_2bs )
{
  photon_distribution_function = MonteCarlo::TWOBS_DISTRIBUTION;

  MonteCarlo::ElectroatomicReactionNativeFactory::createBremsstrahlungReaction<MonteCarlo::ElectroatomicReaction,Utility::Correlated<Utility::LogLogLog> >(
                               *data_container,
                               energy_grid,
                               grid_searcher,
                               reaction,
                               photon_distribution_function,
                               eval_tol );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double cross_section =
                reaction->getCrossSection( reaction->getThresholdEnergy() );
  TEST_FLOATING_EQUALITY( cross_section, 4.8698e3, 1e-12 );

  cross_section = reaction->getCrossSection( 1e-3 );
  TEST_FLOATING_EQUALITY( cross_section, 9.52837e3, 1e-12 );

  cross_section = reaction->getCrossSection( 4e1 );
  TEST_FLOATING_EQUALITY( cross_section, 1.40505e3, 1e-12 );

  cross_section = reaction->getCrossSection( 1e5 );
  TEST_FLOATING_EQUALITY( cross_section, 1.95417e3, 1e-12 );

  // Clear the reaction
  reaction.reset();
}


//---------------------------------------------------------------------------//
// LinLinLin Tests.
//---------------------------------------------------------------------------//
// Check that an coupled elastic reaction can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactory,
                   createCoupledElasticReaction_LinLinLin )
{
  MonteCarlo::CoupledElasticSamplingMethod sampling_method =
    MonteCarlo::TWO_D_UNION;

  MonteCarlo::ElectroatomicReactionNativeFactory::createCoupledElasticReaction<Utility::Correlated<Utility::LinLinLin> >(
                *data_container,
                energy_grid,
                grid_searcher,
                reaction,
                sampling_method,
                1e-7 );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::COUPLED_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double energy = 1e-5;
  double cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.48924e+09, 1e-12 );

  energy = 4e-4;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 4.43663545845802366734e+08, 1e-12 );

  energy = 1e5;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.11161e+06, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an cutoff elastic reaction can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactory,
                   createCutoffElasticReaction_LinLinLin )
{
  MonteCarlo::ElectroatomicReactionNativeFactory::createCutoffElasticReaction<Utility::Correlated<Utility::LinLinLin> >(
                *data_container,
                energy_grid,
                grid_searcher,
                reaction,
                0.999999,
                1e-7 );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double energy = 1e-5;
  double cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.48924e9, 1e-12 );

  energy = 4e-4;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 4.436635458458e8, 1e-12 );

  energy = 1e5;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 8.83051e-2, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an moment preserving elastic reaction can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactory,
                   createMomentPreservingElasticReaction_LinLinLin )
{
  MonteCarlo::ElectroatomicReactionNativeFactory::createMomentPreservingElasticReaction<Utility::Correlated<Utility::LinLinLin> >(
                *data_container,
                energy_grid,
                grid_searcher,
                reaction,
                0.9,
                1e-7 );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::MOMENT_PRESERVING_ELASTIC_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double energy = 1e-5;
  double cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 1.1063294415585944e+08, 1e-12 );

  energy = 4e-4;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.2813487936725482e+07, 1e-12 );

  energy = 1e5;
  cross_section = reaction->getCrossSection( energy );
  TEST_FLOATING_EQUALITY( cross_section, 2.2037700886489448e-03, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that the electroionization subshell reactions can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactory,
                   createSubshellElectroionizationReactions_LinLinLin )
{
  std::vector<std::shared_ptr<MonteCarlo::ElectroatomicReaction> > reactions;

  MonteCarlo::ElectroatomicReactionNativeFactory::createSubshellElectroionizationReactions<MonteCarlo::ElectroatomicReaction,Utility::Correlated<Utility::LinLinLin> >(
                               *data_container,
                               energy_grid,
                               grid_searcher,
                               reactions,
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

  cross_section = reactions.front()->getCrossSection( 1e-1 );
  TEST_FLOATING_EQUALITY( cross_section, 9.2835e-1, 1e-12 );

  cross_section = reactions.front()->getCrossSection( 1.58489e2 );
  TEST_FLOATING_EQUALITY( cross_section, 2.78886e1, 1e-12 );

  cross_section = reactions.front()->getCrossSection( 1e5 );
  TEST_FLOATING_EQUALITY( cross_section, 3.64919e1, 1e-12 );

  // Check the last shell's reaction properties
  TEST_EQUALITY_CONST(
          reactions.back()->getReactionType(),
          MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reactions.back()->getThresholdEnergy(), 1e-5 );

  cross_section = reactions.back()->getCrossSection( 1e-5 );
  TEST_FLOATING_EQUALITY( cross_section, 1.0653e8, 1e-12 );

  cross_section = reactions.back()->getCrossSection( 1e-3 );
  TEST_FLOATING_EQUALITY( cross_section, 3.24885e7, 1e-12 );

  cross_section = reactions.back()->getCrossSection( 1.0 );
  TEST_FLOATING_EQUALITY( cross_section, 2.0335e5, 1e-12 );

  cross_section = reactions.back()->getCrossSection( 1e5 );
  TEST_FLOATING_EQUALITY( cross_section, 1.82234e5, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a basic (dipole distribution) bremsstrahlung reaction can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactory,
                   createBremsstrahlungReaction_dipole_LinLinLin )
{
  photon_distribution_function = MonteCarlo::DIPOLE_DISTRIBUTION;

  MonteCarlo::ElectroatomicReactionNativeFactory::createBremsstrahlungReaction<MonteCarlo::ElectroatomicReaction,Utility::UnitBaseCorrelated<Utility::LinLinLin> >(
                               *data_container,
                               energy_grid,
                               grid_searcher,
                               reaction,
                               photon_distribution_function,
                               eval_tol );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double cross_section =
    reaction->getCrossSection( reaction->getThresholdEnergy() );
  TEST_FLOATING_EQUALITY( cross_section, 4.8698e3, 1e-12 );

  cross_section = reaction->getCrossSection( 1e-3 );
  TEST_FLOATING_EQUALITY( cross_section, 9.52837e3, 1e-12 );

  cross_section = reaction->getCrossSection( 4e1 );
  TEST_FLOATING_EQUALITY( cross_section, 1.40505e3, 1e-12 );

  cross_section = reaction->getCrossSection( 1e5 );
  TEST_FLOATING_EQUALITY( cross_section, 1.95417e3, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
/* Check that a electroatom with detailed 2BS photon angular distribution
 * data can be created
 */
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactory,
                   createBremsstrahlungReaction_2bs_LinLinLin )
{
  photon_distribution_function = MonteCarlo::TWOBS_DISTRIBUTION;

  MonteCarlo::ElectroatomicReactionNativeFactory::createBremsstrahlungReaction<MonteCarlo::ElectroatomicReaction,Utility::Correlated<Utility::LinLinLin> >(
                               *data_container,
                               energy_grid,
                               grid_searcher,
                               reaction,
                               photon_distribution_function,
                               eval_tol );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double cross_section =
    reaction->getCrossSection( reaction->getThresholdEnergy() );
  TEST_FLOATING_EQUALITY( cross_section, 4.8698e3, 1e-12 );

  cross_section = reaction->getCrossSection( 1e-3 );
  TEST_FLOATING_EQUALITY( cross_section, 9.52837e3, 1e-12 );

  cross_section = reaction->getCrossSection( 4e1 );
  TEST_FLOATING_EQUALITY( cross_section, 1.40505e3, 1e-12 );

  cross_section = reaction->getCrossSection( 1e5 );
  TEST_FLOATING_EQUALITY( cross_section, 1.95417e3, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that a void absorption reaction can be created
TEUCHOS_UNIT_TEST( ElectroatomicReactionNativeFactory,
                   createVoidAbsorptionReaction )
{
  MonteCarlo::ElectroatomicReactionNativeFactory::createVoidAbsorptionReaction(
                                                reaction );

  // Test reaction properties
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::TOTAL_ABSORPTION_ELECTROATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double cross_section =
    reaction->getCrossSection( reaction->getThresholdEnergy() );
  TEST_EQUALITY_CONST( cross_section, 0.0);

  cross_section = reaction->getCrossSection( 1e-4 );
  TEST_EQUALITY_CONST( cross_section, 0.0);

  cross_section = reaction->getCrossSection( 1.79008e-4 );
  TEST_EQUALITY_CONST( cross_section, 0.0);

  cross_section = reaction->getCrossSection( 1e5 );
  TEST_EQUALITY_CONST( cross_section, 0.0);

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

  // Extract the common energy grid
  energy_grid.deepCopy( data_container->getElectronEnergyGrid() );

  // Create the hash-based grid searcher
  grid_searcher.reset( new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>,false>(
                 energy_grid,
                 energy_grid[0],
                 energy_grid[energy_grid.size()-1],
                 100 ) );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstElectroatomicReactionNativeFactory.cpp
//---------------------------------------------------------------------------//

