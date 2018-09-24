//---------------------------------------------------------------------------//
//!
//! \file   tstElectroatomicReactionNativeFactoryHelpers.cpp
//! \author Luke Kersting
//! \brief  Electroatomic reaction factory using Native data unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_ElectroatomicReactionNativeFactoryHelpers.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<Data::ElectronPhotonRelaxationDataContainer> data_container;
std::shared_ptr<const MonteCarlo::ElectroatomicReaction> reaction;

double eval_tol = 1e-7;

//---------------------------------------------------------------------------//
// LinLinLog Tests.
//---------------------------------------------------------------------------//
// Check that an coupled elastic reaction can be created
FRENSIE_UNIT_TEST( ElectroatomicReactionNativeFactory,
                   createCoupledElasticReaction_LogLogCosLog )
{
  reaction = MonteCarlo::createCoupledElasticReaction<Utility::LogNudgedLogCosLog ,Utility::Correlated>(
                *data_container,
                MonteCarlo::TWO_D_UNION,
                eval_tol );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
                       MonteCarlo::COUPLED_ELASTIC_ELECTROATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1.0e-5 );

  // Test that the stored cross section is correct
  double energy = 1.0e-5;
  double cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.48924e+09, 1e-12 );

  energy = 4.0e-4;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.43663545845802366734e+08, 1e-12 );

  energy = 1.0e5;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.11161e+06, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an decoupled elastic reaction can be created
FRENSIE_UNIT_TEST( ElectroatomicReactionNativeFactory,
                   createDecoupledElasticReaction_LogLogCosLog )
{
  reaction = MonteCarlo::createDecoupledElasticReaction<Utility::LogLogCosLog,Utility::Correlated>(
                *data_container,
                eval_tol );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
                       MonteCarlo::DECOUPLED_ELASTIC_ELECTROATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1.0e-5 );

  // Test that the stored cross section is correct
  double energy = 1.0e-5;
  double cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.48924e+09, 1e-12 );

  energy = 4.0e-4;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.43663545845802366734e+08, 1e-12 );

  energy = 1.0e5;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.11161e+06, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an hybrid elastic reaction can be created
FRENSIE_UNIT_TEST( ElectroatomicReactionNativeFactory,
                   createHybridElasticReaction_LogLogCosLog )
{
  double cutoff_angle_cosine = 0.9;

  reaction = MonteCarlo::createHybridElasticReaction<Utility::LogNudgedLogCosLog ,Utility::Correlated>(
                *data_container,
                cutoff_angle_cosine,
                1e-14 );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
                       MonteCarlo::HYBRID_ELASTIC_ELECTROATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1.0e-5 );

  // Test that the stored cross section is correct
  double energy = 1.0e-5;
  double cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.4754121265454507e+09, 1e-12 );

  energy = 4.0e-4;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.2786275809074390e+08, 1e-12 );

  energy = 1.0e5;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.2050564844577009e-03, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an cutoff elastic reaction can be created
FRENSIE_UNIT_TEST( ElectroatomicReactionNativeFactory,
                   createCutoffElasticReaction_LogLogCosLog )
{
  reaction = MonteCarlo::createCutoffElasticReaction<Utility::LogLogCosLog,Utility::Correlated>(
                *data_container,
                1.0,
                eval_tol );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
                       MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1.0e-5 );

  // Test that the stored cross section is correct
  double energy = 1.0e-5;
  double cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.48924e9, 1e-12 );

  energy = 4.0e-4;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.436635458458e8, 1e-12 );

  energy = 1.0e5;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.83051e-2, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// LinLinLog Tests.
//---------------------------------------------------------------------------//
// Check that an coupled elastic reaction can be created
FRENSIE_UNIT_TEST( ElectroatomicReactionNativeFactoryHelpers,
                   createCoupledElasticReaction_LinLinLog )
{
  reaction = MonteCarlo::createCoupledElasticReaction<Utility::LinLinLog,Utility::Correlated>(
                *data_container,
                MonteCarlo::TWO_D_UNION,
                eval_tol );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
                       MonteCarlo::COUPLED_ELASTIC_ELECTROATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1.0e-5 );

  // Test that the stored cross section is correct
  double energy = 1.0e-5;
  double cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.48924e+09, 1e-12 );

  energy = 4.0e-4;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.43663545845802366734e+08, 1e-12 );

  energy = 1.0e5;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.11161e+06, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that a decoupled elastic reaction can be created
FRENSIE_UNIT_TEST( ElectroatomicReactionNativeFactoryHelpers,
                   createDecoupledElasticReaction_LinLinLog )
{
  reaction = MonteCarlo::createDecoupledElasticReaction<Utility::LinLinLog,Utility::Correlated>(
                *data_container,
                eval_tol );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
                       MonteCarlo::DECOUPLED_ELASTIC_ELECTROATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1.0e-5 );

  // Test that the stored cross section is correct
  double energy = 1.0e-5;
  double cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.48924e+09, 1e-12 );

  energy = 4.0e-4;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.43663545845802366734e+08, 1e-12 );

  energy = 1.0e5;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.11161e+06, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an hybrid elastic reaction can be created
FRENSIE_UNIT_TEST( ElectroatomicReactionNativeFactory,
                   createHybridElasticReaction_LinLinLog )
{
  double cutoff_angle_cosine = 0.9;

    reaction = MonteCarlo::createHybridElasticReaction<Utility::LinLinLog,Utility::Correlated>(
                *data_container,
                cutoff_angle_cosine,
                1e-14 );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
                       MonteCarlo::HYBRID_ELASTIC_ELECTROATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1.0e-5 );

  // Test that the stored cross section is correct
  double energy = 1.0e-5;
  double cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.4754121265454507e+09, 1e-12 );

  energy = 4.0e-4;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.0310818301823217e+08, 1e-12 );

  energy = 1.0e5;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.2050564844577009e-03, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an cutoff elastic reaction can be created
FRENSIE_UNIT_TEST( ElectroatomicReactionNativeFactoryHelpers,
                   createCutoffElasticReaction_LinLinLog )
{
  reaction = MonteCarlo::createCutoffElasticReaction<Utility::LinLinLog,Utility::Correlated>(
                *data_container,
                1.0,
                eval_tol );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
                       MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1.0e-5 );

  // Test that the stored cross section is correct
  double energy = 1.0e-5;
  double cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.48924e9, 1e-12 );

  energy = 4.0e-4;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.436635458458e8, 1e-12 );

  energy = 1.0e5;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.83051e-2, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that a screened Rutherford elastic reaction can be created
FRENSIE_UNIT_TEST( ElectroatomicReactionNativeFactoryHelpers,
                   createScreenedRutherfordElasticReaction )
{
  reaction = MonteCarlo::createScreenedRutherfordElasticReaction(
                *data_container );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
                       MonteCarlo::SCREENED_RUTHERFORD_ELASTIC_ELECTROATOMIC_REACTION );
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
FRENSIE_UNIT_TEST( ElectroatomicReactionNativeFactoryHelpers,
                   createMomentPreservingElasticReaction_LinLinLog )
{
  reaction = MonteCarlo::createMomentPreservingElasticReaction<Utility::LinLinLog,Utility::Correlated>(
                *data_container,
                0.9,
                eval_tol );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
                       MonteCarlo::MOMENT_PRESERVING_ELASTIC_ELECTROATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double energy = 1e-5;
  double cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.1063294415585944e+08, 1e-12 );

  energy = 4.0e-4;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.7788808128946811e+07, 1e-12 );

  energy = 1.0e5;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.2037700886489448e-03, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an atomic excitation reaction can be created
FRENSIE_UNIT_TEST( ElectroatomicReactionNativeFactoryHelpers,
                   createAtomicExcitationReaction )
{
  reaction = MonteCarlo::createAtomicExcitationReaction( *data_container );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
                       MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1.0e-5 );

  // Test that the stored cross section is correct
  double cross_section = reaction->getCrossSection( 1.0e-5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.75755e6, 1e-12 );

  cross_section = reaction->getCrossSection( 4.0e-4 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.22682e8, 1e-12 );

  cross_section = reaction->getCrossSection( 1.0e5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.57861e6, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that the electroionization subshell reactions can be created
FRENSIE_UNIT_TEST( ElectroatomicReactionNativeFactoryHelpers,
                   createSubshellElectroelectricReactions_LinLinLog )
{
  std::vector<std::shared_ptr<const MonteCarlo::ElectroatomicReaction> >
  reactions = MonteCarlo::createSubshellElectroionizationReactions<Utility::LinLinLog,Utility::UnitBaseCorrelated>(
                               *data_container,
                               eval_tol );

  FRENSIE_CHECK_EQUAL( reactions.size(), 24 );

  // Test the first shell's reaction properties
  FRENSIE_CHECK_EQUAL(
              reactions.front()->getReactionType(),
              MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reactions.front()->getThresholdEnergy(),
                       8.82899999999999935e-2 );

  // Test the first shell's stored cross section is correct
  double cross_section = reactions.front()->getCrossSection( 8.829e-2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = reactions.front()->getCrossSection( 1.0e-1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.2835e-1, 1e-12 );

  cross_section = reactions.front()->getCrossSection( 1.58489e2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.788860e1, 1e-12 );

  cross_section = reactions.front()->getCrossSection( 1.0e5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.649190e1, 1e-12 );

  // Check the last shell's reaction properties
  FRENSIE_CHECK_EQUAL(
          reactions.back()->getReactionType(),
          MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reactions.back()->getThresholdEnergy(), 1.0e-5 );

  cross_section = reactions.back()->getCrossSection( 1.0e-5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.0653e8, 1e-12 );

  cross_section = reactions.back()->getCrossSection( 1.0e-3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.248850e7, 1e-12 );

  cross_section = reactions.back()->getCrossSection( 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.0335e5, 1e-12 );

  cross_section = reactions.back()->getCrossSection( 1.0e5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.82234e5, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a basic (dipole distribution) bremsstrahlung reaction can be created
FRENSIE_UNIT_TEST( ElectroatomicReactionNativeFactoryHelpers,
                   createBremsstrahlungReaction_dipole_LinLinLog )
{
  bool dipole_distribution_mode_on = true;
  reaction =
    MonteCarlo::createBremsstrahlungReaction<Utility::LinLinLog,Utility::Correlated>(
                                          *data_container,
                                          dipole_distribution_mode_on,
                                          eval_tol );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
                       MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1.0e-5 );

  // Test that the stored cross section is correct
  double cross_section =
            reaction->getCrossSection( reaction->getThresholdEnergy() );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.8698e3, 1e-12 );

  cross_section = reaction->getCrossSection( 1.0e-3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.528370e3, 1e-12 );

  cross_section = reaction->getCrossSection( 4.0e1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.405050e3, 1e-12 );

  cross_section = reaction->getCrossSection( 1.0e5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.95417e3, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
/* Check that a electroatom with detailed 2BS photon angular distribution
 * data can be created
 */
FRENSIE_UNIT_TEST( ElectroatomicReactionNativeFactoryHelpers,
                   createBremsstrahlungReaction_2bs_LinLinLog )
{
  bool dipole_distribution_mode_on = false;

  reaction =
    MonteCarlo::createBremsstrahlungReaction<Utility::LinLinLog,Utility::Correlated>(
                                            *data_container,
                                            dipole_distribution_mode_on,
                                            eval_tol );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
                       MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1.0e-5 );

  // Test that the stored cross section is correct
  double cross_section =
                reaction->getCrossSection( reaction->getThresholdEnergy() );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.8698e3, 1e-12 );

  cross_section = reaction->getCrossSection( 1.0e-3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.528370e3, 1e-12 );

  cross_section = reaction->getCrossSection( 4.0e1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.405050e3, 1e-12 );

  cross_section = reaction->getCrossSection( 1.0e5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.95417e3, 1e-12 );

  // Clear the reaction
  reaction.reset();
}


//---------------------------------------------------------------------------//
// LinLinLin Tests.
//---------------------------------------------------------------------------//
// Check that an coupled elastic reaction can be created
FRENSIE_UNIT_TEST( ElectroatomicReactionNativeFactoryHelpers,
                   createCoupledElasticReaction_LinLinLin )
{
  reaction = MonteCarlo::createCoupledElasticReaction<Utility::LinLinLin,Utility::Correlated>(
      *data_container,
      MonteCarlo::TWO_D_UNION,
      eval_tol );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
                       MonteCarlo::COUPLED_ELASTIC_ELECTROATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1.0e-5 );

  // Test that the stored cross section is correct
  double energy = 1.0e-5;
  double cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.48924e+09, 1e-12 );

  energy = 4.0e-4;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.43663545845802366734e+08, 1e-12 );

  energy = 1.0e5;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.11161e+06, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an cutoff elastic reaction can be created
FRENSIE_UNIT_TEST( ElectroatomicReactionNativeFactoryHelpers,
                   createCutoffElasticReaction_LinLinLin )
{
  reaction = MonteCarlo::createCutoffElasticReaction<Utility::LinLinLin,Utility::Correlated>(
                *data_container,
                1.0,
                eval_tol );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
                       MonteCarlo::CUTOFF_ELASTIC_ELECTROATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1.0e-5 );

  // Test that the stored cross section is correct
  double energy = 1.0e-5;
  double cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.48924e9, 1e-12 );

  energy = 4.0e-4;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.436635458458e8, 1e-12 );

  energy = 1.0e5;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.83051e-2, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that an moment preserving elastic reaction can be created
FRENSIE_UNIT_TEST( ElectroatomicReactionNativeFactoryHelpers,
                   createMomentPreservingElasticReaction_LinLinLin )
{
  reaction = MonteCarlo::createMomentPreservingElasticReaction<Utility::LinLinLin,Utility::Correlated>(
                        *data_container,
                        0.9,
                        eval_tol );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
                       MonteCarlo::MOMENT_PRESERVING_ELASTIC_ELECTROATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-5 );

  // Test that the stored cross section is correct
  double energy = 1e-5;
  double cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.1063294415585944e+08, 1e-12 );

  energy = 4.0e-4;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.2813487936725482e+07, 1e-12 );

  energy = 1.0e5;
  cross_section = reaction->getCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.2037700886489448e-03, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
// Check that the electroionization subshell reactions can be created
FRENSIE_UNIT_TEST( ElectroatomicReactionNativeFactoryHelpers,
                   createSubshellElectroionizationReactions_LinLinLin )
{
  std::vector<std::shared_ptr<const MonteCarlo::ElectroatomicReaction> >
  reactions = MonteCarlo::createSubshellElectroionizationReactions<Utility::LinLinLin,Utility::Correlated>(
                               *data_container,
                               eval_tol );

  FRENSIE_CHECK_EQUAL( reactions.size(), 24 );

  // Test the first shell's reaction properties
  FRENSIE_CHECK_EQUAL(
              reactions.front()->getReactionType(),
              MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reactions.front()->getThresholdEnergy(),
                       8.82899999999999935e-2 );

  // Test the first shell's stored cross section is correct
  double cross_section = reactions.front()->getCrossSection( 8.829e-2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = reactions.front()->getCrossSection( 1.0e-1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.2835e-1, 1e-12 );

  cross_section = reactions.front()->getCrossSection( 1.58489e2 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.788860e1, 1e-12 );

  cross_section = reactions.front()->getCrossSection( 1.0e5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.649190e1, 1e-12 );

  // Check the last shell's reaction properties
  FRENSIE_CHECK_EQUAL(
          reactions.back()->getReactionType(),
          MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reactions.back()->getThresholdEnergy(), 1.0e-5 );

  cross_section = reactions.back()->getCrossSection( 1.0e-5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.0653e8, 1e-12 );

  cross_section = reactions.back()->getCrossSection( 1.0e-3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.248850e7, 1e-12 );

  cross_section = reactions.back()->getCrossSection( 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.0335e5, 1e-12 );

  cross_section = reactions.back()->getCrossSection( 1.0e5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.82234e5, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a basic (dipole distribution) bremsstrahlung reaction can be created
FRENSIE_UNIT_TEST( ElectroatomicReactionNativeFactoryHelpers,
                   createBremsstrahlungReaction_dipole_LinLinLin )
{
  bool dipole_distribution_mode_on = true;

  reaction =
    MonteCarlo::createBremsstrahlungReaction<Utility::LinLinLin,Utility::Correlated>(
                    *data_container,
                    dipole_distribution_mode_on,
                    eval_tol );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
                       MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1.0e-5 );

  // Test that the stored cross section is correct
  double cross_section =
    reaction->getCrossSection( reaction->getThresholdEnergy() );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.8698e3, 1e-12 );

  cross_section = reaction->getCrossSection( 1.0e-3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.528370e3, 1e-12 );

  cross_section = reaction->getCrossSection( 4.0e1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.405050e3, 1e-12 );

  cross_section = reaction->getCrossSection( 1.0e5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.95417e3, 1e-12 );

  // Clear the reaction
  reaction.reset();
}

//---------------------------------------------------------------------------//
/* Check that a electroatom with detailed 2BS photon angular distribution
 * data can be created
 */
FRENSIE_UNIT_TEST( ElectroatomicReactionNativeFactoryHelpers,
                   createBremsstrahlungReaction_2bs_LinLinLin )
{
  bool dipole_distribution_mode_on = false;

  reaction =
    MonteCarlo::createBremsstrahlungReaction<Utility::LinLinLin,Utility::Correlated>(
                                              *data_container,
                                              dipole_distribution_mode_on,
                                              eval_tol );

  // Test reaction properties
  FRENSIE_CHECK_EQUAL( reaction->getReactionType(),
                       MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );
  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1.0e-5 );

  // Test that the stored cross section is correct
  double cross_section =
    reaction->getCrossSection( reaction->getThresholdEnergy() );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.8698e3, 1e-12 );

  cross_section = reaction->getCrossSection( 1.0e-3 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.528370e3, 1e-12 );

  cross_section = reaction->getCrossSection( 4.0e1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.40505e3, 1e-12 );

  cross_section = reaction->getCrossSection( 1.0e5 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.95417e3, 1e-12 );

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
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstElectroatomicReactionNativeFactoryHelpers.cpp
//---------------------------------------------------------------------------//

