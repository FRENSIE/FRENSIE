//---------------------------------------------------------------------------//
//!
//! \file   tstPositronatomicReactionNativeFactory.cpp
//! \author Luke Kersting
//! \brief  Positronatomic reaction factory using Native data unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_PositronatomicReactionNativeFactory.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"
#include "MonteCarlo_ElasticElectronDistributionType.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

MonteCarlo::BremsstrahlungAngularDistributionType photon_distribution_function;
std::unique_ptr<Data::ElectronPhotonRelaxationDataContainer> data_container;
std::shared_ptr<std::vector<double> > energy_grid( new std::vector<double> );
std::shared_ptr<Utility::HashBasedGridSearcher<double> > grid_searcher;
std::shared_ptr<const MonteCarlo::PositronatomicReaction> reaction;

double eval_tol;

//---------------------------------------------------------------------------//
// LinLinLog Tests.
//---------------------------------------------------------------------------//
// Check that an coupled elastic reaction can be created
FRENSIE_UNIT_TEST( PositronatomicReactionNativeFactory,
                   createCoupledElasticReaction_LogLogCosLog )
{
  MonteCarlo::CoupledElasticSamplingMethod sampling_method =
    MonteCarlo::TWO_D_UNION;

  MonteCarlo::PositronatomicReactionNativeFactory::createCoupledElasticReaction<Utility::LogNudgedLogCosLog,Utility::Correlated>(
                *data_container,
                energy_grid,
                grid_searcher,
                reaction,
                sampling_method,
                1e-7 );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
                       MonteCarlo::COUPLED_ELASTIC_POSITRONATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double energy = 1e-5;
  double cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.48924e+09, 1e-12 );

  energy = 4e-4;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.43663545845802366734e+08, 1e-12 );

  energy = 1e5;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.11161e+06, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an decoupled elastic reaction can be created
FRENSIE_UNIT_TEST( PositronatomicReactionNativeFactory,
                   createDecoupledElasticReaction_LogLogCosLog )
{
  MonteCarlo::PositronatomicReactionNativeFactory::createDecoupledElasticReaction<Utility::LogLogCosLog,Utility::Correlated>(
                *data_container,
                energy_grid,
                grid_searcher,
                reaction,
                1e-7 );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
                       MonteCarlo::DECOUPLED_ELASTIC_POSITRONATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double energy = 1e-5;
  double cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.48924e+09, 1e-12 );

  energy = 4e-4;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.43663545845802366734e+08, 1e-12 );

  energy = 1e5;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.11161e+06, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an hybrid elastic reaction can be created
FRENSIE_UNIT_TEST( PositronatomicReactionNativeFactory,
                   createHybridElasticReaction_LogLogCosLog )
{
  double cutoff_angle_cosine = 0.9;

  MonteCarlo::PositronatomicReactionNativeFactory::createHybridElasticReaction<Utility::LogNudgedLogCosLog ,Utility::Correlated>(
                *data_container,
                energy_grid,
                grid_searcher,
                reaction,
                cutoff_angle_cosine,
                1e-14 );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
                       MonteCarlo::HYBRID_ELASTIC_POSITRONATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double energy = 1e-5;
  double cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.4754121265454507e+09, 1e-12 );

  energy = 4e-4;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.2786275809074390e+08, 1e-12 );

  energy = 1e5;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.2050564844577009e-03, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an cutoff elastic reaction can be created
FRENSIE_UNIT_TEST( PositronatomicReactionNativeFactory,
                   createCutoffElasticReaction_LogLogCosLog )
{
  MonteCarlo::PositronatomicReactionNativeFactory::createCutoffElasticReaction<Utility::LogLogCosLog,Utility::Correlated>(
                *data_container,
                energy_grid,
                grid_searcher,
                reaction,
                1.0,
                1e-7 );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
                       MonteCarlo::CUTOFF_ELASTIC_POSITRONATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double energy = 1e-5;
  double cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.48924e9, 1e-12 );

  energy = 4e-4;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.436635458458e8, 1e-12 );

  energy = 1e5;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.83051e-2, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// LinLinLog Tests.
//---------------------------------------------------------------------------//
// Check that an coupled elastic reaction can be created
FRENSIE_UNIT_TEST( PositronatomicReactionNativeFactory,
                   createCoupledElasticReaction_LinLinLog )
{
  MonteCarlo::CoupledElasticSamplingMethod sampling_method =
    MonteCarlo::TWO_D_UNION;

  MonteCarlo::PositronatomicReactionNativeFactory::createCoupledElasticReaction<Utility::LinLinLog,Utility::Correlated>(
                *data_container,
                energy_grid,
                grid_searcher,
                reaction,
                sampling_method,
                1e-7 );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
                       MonteCarlo::COUPLED_ELASTIC_POSITRONATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double energy = 1e-5;
  double cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.48924e+09, 1e-12 );

  energy = 4e-4;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.43663545845802366734e+08, 1e-12 );

  energy = 1e5;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.11161e+06, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an decoupled elastic reaction can be created
FRENSIE_UNIT_TEST( PositronatomicReactionNativeFactory,
                   createDecoupledElasticReaction_LinLinLog )
{
  MonteCarlo::PositronatomicReactionNativeFactory::createDecoupledElasticReaction<Utility::LinLinLog,Utility::Correlated>(
                *data_container,
                energy_grid,
                grid_searcher,
                reaction,
                1e-7 );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
                       MonteCarlo::DECOUPLED_ELASTIC_POSITRONATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double energy = 1e-5;
  double cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.48924e+09, 1e-12 );

  energy = 4e-4;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.43663545845802366734e+08, 1e-12 );

  energy = 1e5;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.11161e+06, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an hybrid elastic reaction can be created
FRENSIE_UNIT_TEST( PositronatomicReactionNativeFactory,
                   createHybridElasticReaction_LinLinLog )
{
  double cutoff_angle_cosine = 0.9;

  MonteCarlo::PositronatomicReactionNativeFactory::createHybridElasticReaction<Utility::LinLinLog,Utility::Correlated>(
                *data_container,
                energy_grid,
                grid_searcher,
                reaction,
                cutoff_angle_cosine,
                1e-14 );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
                       MonteCarlo::HYBRID_ELASTIC_POSITRONATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double energy = 1e-5;
  double cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.4754121265454507e+09, 1e-12 );

  energy = 4e-4;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.0310818301823217e+08, 1e-12 );

  energy = 1e5;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.2050564844577009e-03, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an cutoff elastic reaction can be created
FRENSIE_UNIT_TEST( PositronatomicReactionNativeFactory,
                   createCutoffElasticReaction_LinLinLog )
{
  MonteCarlo::PositronatomicReactionNativeFactory::createCutoffElasticReaction<Utility::LinLinLog,Utility::Correlated>(
                *data_container,
                energy_grid,
                grid_searcher,
                reaction,
                1.0,
                1e-7 );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
                       MonteCarlo::CUTOFF_ELASTIC_POSITRONATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double energy = 1e-5;
  double cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.48924e9, 1e-12 );

  energy = 4e-4;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.436635458458e8, 1e-12 );

  energy = 1e5;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.83051e-2, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that a screened Rutherford elastic reaction can be created
FRENSIE_UNIT_TEST( PositronatomicReactionNativeFactory,
                   createScreenedRutherfordElasticReaction )
{
  MonteCarlo::PositronatomicReactionNativeFactory::createScreenedRutherfordElasticReaction(
                *data_container,
                energy_grid,
                grid_searcher,
                reaction );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
                       MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_POSITRONATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 7.0 );

  // Test that the stored cross section is correct
  double energy = 1e1;
  double cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.722e5, 1e-12 );

  energy = 1e2;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.0561378e6, 1e-12 );

  energy = 1e5;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.1116099116949e6, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an moment preserving elastic reaction can be created
FRENSIE_UNIT_TEST( PositronatomicReactionNativeFactory,
                   createMomentPreservingElasticReaction_LinLinLog )
{
  MonteCarlo::PositronatomicReactionNativeFactory::createMomentPreservingElasticReaction<Utility::LinLinLog,Utility::Correlated>(
                *data_container,
                energy_grid,
                grid_searcher,
                reaction,
                0.9,
                1e-7 );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
                       MonteCarlo::MOMENT_PRESERVING_ELASTIC_POSITRONATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double energy = 1e-5;
  double cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.1063294415585944e+08, 1e-12 );

  energy = 4e-4;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.7788808128946811e+07, 1e-12 );

  energy = 1e5;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.2037700886489448e-03, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an atomic excitation reaction can be created
FRENSIE_UNIT_TEST( PositronatomicReactionNativeFactory,
                   createAtomicExcitationReaction )
{
  MonteCarlo::PositronatomicReactionNativeFactory::createAtomicExcitationReaction(
                               *data_container,
                               energy_grid,
                               grid_searcher,
                               reaction );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
                       MonteCarlo::ATOMIC_EXCITATION_POSITRONATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double cross_section = reaction->getCrossSection( 1e-5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.75755e6, 1e-12 );

  cross_section = reaction->getCrossSection( 4e-4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.22682e8, 1e-12 );

  cross_section = reaction->getCrossSection( 1e5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.57861e6, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that the electroionization subshell reactions can be created
FRENSIE_UNIT_TEST( PositronatomicReactionNativeFactory,
                   createSubshellPositronionizationReactions )
{
  std::vector<std::shared_ptr<const MonteCarlo::PositronatomicReaction> > reactions;

  MonteCarlo::ElectroionizationSamplingType sampling_type =
    MonteCarlo::KNOCK_ON_SAMPLING;

  MonteCarlo::PositronatomicReactionNativeFactory::createSubshellPositronionizationReactions<Utility::LinLinLog,Utility::UnitBaseCorrelated>(
                               *data_container,
                               energy_grid,
                               grid_searcher,
                               reactions,
                               sampling_type,
                               eval_tol );

  FRENSIE_CHECK_EQUAL( reactions.size(), 24 );

  // Test the first shell's reaction properties
  FRENSIE_CHECK_EQUAL(
              reactions.front()->getReactionType(),
              MonteCarlo::K_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reactions.front()->getThresholdEnergy(),
                       8.829e-2 );

  // Test the first shell's stored cross section is correct
  double cross_section = reactions.front()->getCrossSection( 8.829e-2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = reactions.front()->getCrossSection( 1e-1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.2835e-1, 1e-12 );

  cross_section = reactions.front()->getCrossSection( 1.58489e2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.78886e1, 1e-12 );

  cross_section = reactions.front()->getCrossSection( 1e5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.64919e1, 1e-12 );

  // Check the last shell's reaction properties
  FRENSIE_CHECK_EQUAL(
          reactions.back()->getReactionType(),
          MonteCarlo::P3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reactions.back()->getThresholdEnergy(), 1e-5 );

  cross_section = reactions.back()->getCrossSection( 1e-5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.0653e8, 1e-12 );

  cross_section = reactions.back()->getCrossSection( 1e-3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.24885e7, 1e-12 );

  cross_section = reactions.back()->getCrossSection( 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.0335e5, 1e-12 );

  cross_section = reactions.back()->getCrossSection( 1e5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.82234e5, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a basic (dipole distribution) bremsstrahlung reaction can be created
FRENSIE_UNIT_TEST( PositronatomicReactionNativeFactory,
                   createBremsstrahlungReaction_dipole )
{
  photon_distribution_function = MonteCarlo::DIPOLE_DISTRIBUTION;

  MonteCarlo::PositronatomicReactionNativeFactory::createBremsstrahlungReaction<Utility::LogLogLog,Utility::UnitBaseCorrelated>(
                               *data_container,
                               energy_grid,
                               grid_searcher,
                               reaction,
                               photon_distribution_function,
                               eval_tol );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
                       MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double cross_section =
            reaction->getCrossSection( reaction->getThresholdEnergy() );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.8698e3, 1e-12 );

  cross_section = reaction->getCrossSection( 1e-3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.52837e3, 1e-12 );

  cross_section = reaction->getCrossSection( 4e1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.40505e3, 1e-12 );

  cross_section = reaction->getCrossSection( 1e5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.95417e3, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
/* Check that a positron-atom with detailed 2BS photon angular distribution
 * data can be created
 */
FRENSIE_UNIT_TEST( PositronatomicReactionNativeFactory,
                   createBremsstrahlungReaction_2bs )
{
  photon_distribution_function = MonteCarlo::TWOBS_DISTRIBUTION;

  MonteCarlo::PositronatomicReactionNativeFactory::createBremsstrahlungReaction<Utility::LogLogLog,Utility::Correlated>(
                               *data_container,
                               energy_grid,
                               grid_searcher,
                               reaction,
                               photon_distribution_function,
                               eval_tol );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
                       MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double cross_section =
                reaction->getCrossSection( reaction->getThresholdEnergy() );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.8698e3, 1e-12 );

  cross_section = reaction->getCrossSection( 1e-3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.52837e3, 1e-12 );

  cross_section = reaction->getCrossSection( 4e1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.40505e3, 1e-12 );

  cross_section = reaction->getCrossSection( 1e5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.95417e3, 1e-12 );

  // Clear the reaction
  reaction.reset();
}


//---------------------------------------------------------------------------//
// LinLinLin Tests.
//---------------------------------------------------------------------------//
// Check that an coupled elastic reaction can be created
FRENSIE_UNIT_TEST( PositronatomicReactionNativeFactory,
                   createCoupledElasticReaction_LinLinLin )
{
  MonteCarlo::CoupledElasticSamplingMethod sampling_method =
    MonteCarlo::TWO_D_UNION;

  MonteCarlo::PositronatomicReactionNativeFactory::createCoupledElasticReaction<Utility::LinLinLin,Utility::Correlated>(
                *data_container,
                energy_grid,
                grid_searcher,
                reaction,
                sampling_method,
                1e-7 );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
                       MonteCarlo::COUPLED_ELASTIC_POSITRONATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double energy = 1e-5;
  double cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.48924e+09, 1e-12 );

  energy = 4e-4;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.43663545845802366734e+08, 1e-12 );

  energy = 1e5;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.11161e+06, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an cutoff elastic reaction can be created
FRENSIE_UNIT_TEST( PositronatomicReactionNativeFactory,
                   createCutoffElasticReaction_LinLinLin )
{
  MonteCarlo::PositronatomicReactionNativeFactory::createCutoffElasticReaction<Utility::LinLinLin,Utility::Correlated>(
                *data_container,
                energy_grid,
                grid_searcher,
                reaction,
                0.999999,
                1e-7 );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
                       MonteCarlo::CUTOFF_ELASTIC_POSITRONATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double energy = 1e-5;
  double cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.48924e9, 1e-12 );

  energy = 4e-4;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.436635458458e8, 1e-12 );

  energy = 1e5;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.83051e-2, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an moment preserving elastic reaction can be created
FRENSIE_UNIT_TEST( PositronatomicReactionNativeFactory,
                   createMomentPreservingElasticReaction_LinLinLin )
{
  MonteCarlo::PositronatomicReactionNativeFactory::createMomentPreservingElasticReaction<Utility::LinLinLin,Utility::Correlated>(
                *data_container,
                energy_grid,
                grid_searcher,
                reaction,
                0.9,
                1e-7 );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
                       MonteCarlo::MOMENT_PRESERVING_ELASTIC_POSITRONATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double energy = 1e-5;
  double cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.1063294415585944e+08, 1e-12 );

  energy = 4e-4;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.2813487936725482e+07, 1e-12 );

  energy = 1e5;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.2037700886489448e-03, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that the electroionization subshell reactions can be created
FRENSIE_UNIT_TEST( PositronatomicReactionNativeFactory,
                   createSubshellPositronionizationReactions_LinLinLin )
{
  std::vector<std::shared_ptr<const MonteCarlo::PositronatomicReaction> > reactions;

  MonteCarlo::ElectroionizationSamplingType sampling_type =
    MonteCarlo::KNOCK_ON_SAMPLING;

  MonteCarlo::PositronatomicReactionNativeFactory::createSubshellPositronionizationReactions<Utility::LinLinLin,Utility::Correlated>(
                               *data_container,
                               energy_grid,
                               grid_searcher,
                               reactions,
                               sampling_type,
                               eval_tol );

  FRENSIE_CHECK_EQUAL( reactions.size(), 24 );

  // Test the first shell's reaction properties
  FRENSIE_CHECK_EQUAL(
              reactions.front()->getReactionType(),
              MonteCarlo::K_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reactions.front()->getThresholdEnergy(),
                       8.82899999999999935e-2 );

  // Test the first shell's stored cross section is correct
  double cross_section = reactions.front()->getCrossSection( 8.829e-2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = reactions.front()->getCrossSection( 1e-1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.2835e-1, 1e-12 );

  cross_section = reactions.front()->getCrossSection( 1.58489e2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.78886e1, 1e-12 );

  cross_section = reactions.front()->getCrossSection( 1e5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.64919e1, 1e-12 );

  // Check the last shell's reaction properties
  FRENSIE_CHECK_EQUAL(
          reactions.back()->getReactionType(),
          MonteCarlo::P3_SUBSHELL_POSITRONIONIZATION_POSITRONATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reactions.back()->getThresholdEnergy(), 1e-5 );

  cross_section = reactions.back()->getCrossSection( 1e-5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.0653e8, 1e-12 );

  cross_section = reactions.back()->getCrossSection( 1e-3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.24885e7, 1e-12 );

  cross_section = reactions.back()->getCrossSection( 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.0335e5, 1e-12 );

  cross_section = reactions.back()->getCrossSection( 1e5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.82234e5, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a basic (dipole distribution) bremsstrahlung reaction can be created
FRENSIE_UNIT_TEST( PositronatomicReactionNativeFactory,
                   createBremsstrahlungReaction_dipole_LinLinLin )
{
  photon_distribution_function = MonteCarlo::DIPOLE_DISTRIBUTION;

  MonteCarlo::PositronatomicReactionNativeFactory::createBremsstrahlungReaction<Utility::LinLinLin,Utility::UnitBaseCorrelated>(
                               *data_container,
                               energy_grid,
                               grid_searcher,
                               reaction,
                               photon_distribution_function,
                               eval_tol );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
                       MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double cross_section =
    reaction->getCrossSection( reaction->getThresholdEnergy() );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.8698e3, 1e-12 );

  cross_section = reaction->getCrossSection( 1e-3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.52837e3, 1e-12 );

  cross_section = reaction->getCrossSection( 4e1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.40505e3, 1e-12 );

  cross_section = reaction->getCrossSection( 1e5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.95417e3, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
/* Check that a positron-atom with detailed 2BS photon angular distribution
 * data can be created
 */
FRENSIE_UNIT_TEST( PositronatomicReactionNativeFactory,
                   createBremsstrahlungReaction_2bs_LinLinLin )
{
  photon_distribution_function = MonteCarlo::TWOBS_DISTRIBUTION;

  MonteCarlo::PositronatomicReactionNativeFactory::createBremsstrahlungReaction<Utility::LinLinLin,Utility::Correlated>(
                               *data_container,
                               energy_grid,
                               grid_searcher,
                               reaction,
                               photon_distribution_function,
                               eval_tol );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
                       MonteCarlo::BREMSSTRAHLUNG_POSITRONATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double cross_section =
    reaction->getCrossSection( reaction->getThresholdEnergy() );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.8698e3, 1e-12 );

  cross_section = reaction->getCrossSection( 1e-3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.52837e3, 1e-12 );

  cross_section = reaction->getCrossSection( 4e1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.40505e3, 1e-12 );

  cross_section = reaction->getCrossSection( 1e5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.95417e3, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that a void absorption reaction can be created
FRENSIE_UNIT_TEST( PositronatomicReactionNativeFactory,
                   createVoidAbsorptionReaction )
{
  MonteCarlo::PositronatomicReactionNativeFactory::createVoidAbsorptionReaction(
                                                reaction );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
                       MonteCarlo::TOTAL_ABSORPTION_POSITRONATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 0.0 );

  // Test that the stored cross section is correct
  double cross_section =
    reaction->getCrossSection( reaction->getThresholdEnergy() );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0);

  cross_section = reaction->getCrossSection( 1e-4 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0);

  cross_section = reaction->getCrossSection( 1.79008e-4 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0);

  cross_section = reaction->getCrossSection( 1e5 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0);

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_native_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_native_file",
                                        test_native_file_name, "",
                                        "Test Native file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  eval_tol = 1e-7;

  // Create the native data file container
  data_container.reset( new Data::ElectronPhotonRelaxationDataContainer(
                             test_native_file_name ) );

  // Extract the common energy grid
  energy_grid->assign( data_container->getElectronEnergyGrid().begin(),
                       data_container->getElectronEnergyGrid().end() );

  // Create the hash-based grid searcher
  grid_searcher.reset( new Utility::StandardHashBasedGridSearcher<std::vector<double>,false>(
                 energy_grid,
                 energy_grid->front(),
                 energy_grid->back(),
                 100 ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstPositronatomicReactionNativeFactory.cpp
//---------------------------------------------------------------------------//

