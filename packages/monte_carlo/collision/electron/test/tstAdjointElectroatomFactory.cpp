//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointElectroatomFactory.cpp
//! \author Luke Kersting
//! \brief  Adjoint electroatom factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatomFactory.hpp"
#include "MonteCarlo_AtomicRelaxationModelFactory.hpp"
#include "MonteCarlo_BremsstrahlungAdjointElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroionizationSubshellAdjointElectroatomicReaction.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"
#include "MonteCarlo_CutoffElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_AdjointElectronState.hpp"
#include "MonteCarlo_SimulationAdjointElectronProperties.hpp"
#include "Data_ScatteringCenterPropertiesDatabase.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::unique_ptr<const boost::filesystem::path> data_directory;
std::unique_ptr<MonteCarlo::ScatteringCenterDefinitionDatabase> adjoint_electroatom_definitions;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a adjoint electroatom map can be created (only basic data)
FRENSIE_UNIT_TEST( AdjointElectroatomFactory, createAdjointElectroatomMap_basic )
{
  // Create the set of electroatom aliases
  MonteCarlo::AdjointElectroatomFactory::ScatteringCenterNameSet electroatom_aliases;
  electroatom_aliases.insert( "H-Native" );

  MonteCarlo::SimulationProperties properties;
  {
    std::vector<double> user_critical_line_energies( 1, 20.0 );

    properties.setAdjointElasticCutoffAngleCosine( 0.9 );
    properties.setAdjointElectronEvaluationTolerance( 1e-7 );
    properties.setAdjointElasticElectronDistributionMode( MonteCarlo::HYBRID_DISTRIBUTION );
    properties.setCriticalAdjointElectronLineEnergies( user_critical_line_energies );
  }

  std::shared_ptr<MonteCarlo::AdjointElectroatomFactory> electroatom_factory(
                    new MonteCarlo::AdjointElectroatomFactory(
                                              *data_directory,
                                              electroatom_aliases,
                                              *adjoint_electroatom_definitions,
                                              properties,
                                              true ) );

  // Create the native data file container
  std::unique_ptr<Data::AdjointElectronPhotonRelaxationDataContainer> data_container(
                                                                                     new Data::AdjointElectronPhotonRelaxationDataContainer( *data_directory / adjoint_electroatom_definitions->getDefinition( "H-Native" ).getAdjointElectroatomicDataProperties().filePath() ) );

  std::shared_ptr<const MonteCarlo::CutoffElasticElectronScatteringDistribution>
    cutoff_elastic_distribution;

  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution<Utility::LogLogCosLog,Utility::Correlated>(
        cutoff_elastic_distribution,
        *data_container,
        properties.getAdjointElasticCutoffAngleCosine(),
        properties.getAdjointElectronEvaluationTolerance() );

  MonteCarlo::AdjointElectroatomFactory::AdjointElectroatomNameMap
    electroatom_map;

  electroatom_factory->createAdjointElectroatomMap( electroatom_map );

  FRENSIE_CHECK_EQUAL( electroatom_map.size(), 1 );
  FRENSIE_CHECK( electroatom_map.count( "H-Native" ) );
  FRENSIE_CHECK( electroatom_map["H-Native"].get() != NULL );

  std::shared_ptr<const MonteCarlo::AdjointElectroatom>& atom = electroatom_map["H-Native"];

  // Test the electroatom properties
  FRENSIE_CHECK_EQUAL( atom->getAtomicNumber(), 1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( atom->getAtomicWeight(), 1.00790034799796868, 1e-12 );

  const MonteCarlo::AdjointElectroatomCore& core = atom->getCore();

  // Check that the grid searcher was constructed correctly
  FRENSIE_CHECK( !core.getGridSearcher().isValueWithinGridBounds( 9.9e-6 ) );
  FRENSIE_CHECK( core.getGridSearcher().isValueWithinGridBounds( 1e-5 ) );
  FRENSIE_CHECK( core.getGridSearcher().isValueWithinGridBounds( 20.0 ) );
  FRENSIE_CHECK( !core.getGridSearcher().isValueWithinGridBounds( 20.1 ) );
  FRENSIE_CHECK( core.hasSharedEnergyGrid() );

  // Check that the critical line energies were constructed correctly
  FRENSIE_CHECK_EQUAL( core.getCriticalLineEnergies().size(), 1 );
  FRENSIE_CHECK_EQUAL( core.getCriticalLineEnergies()[0], 20.0 );

  // Check that the total forward reaction was constructed correctly
  FRENSIE_CHECK_EQUAL( core.getTotalForwardReaction().getThresholdEnergy(),
                       1e-5 );
  FRENSIE_CHECK( core.getTotalForwardReaction().getCrossSection( 20.0 ) > 0.0 );

  // Check that the scattering reactions were constructed correctly
  const MonteCarlo::AdjointElectroatomCore::ConstReactionMap&
    scattering_reactions = core.getScatteringReactions();

  FRENSIE_CHECK_EQUAL( scattering_reactions.size(), 4 );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::HYBRID_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION ) );

  {
    std::shared_ptr<const MonteCarlo::AdjointElectroatomicReaction> reaction =
      scattering_reactions.find( MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION )->second;

    FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-5 );
    FRENSIE_CHECK_EQUAL( reaction->getMaxEnergy(), 20.0 );

    std::shared_ptr<const MonteCarlo::BremsstrahlungAdjointElectroatomicReaction<Utility::LogLog> > brem_reaction =
      std::dynamic_pointer_cast<const MonteCarlo::BremsstrahlungAdjointElectroatomicReaction<Utility::LogLog> >( reaction );

    FRENSIE_CHECK_EQUAL( brem_reaction->getCriticalLineEnergies(),
                         core.getCriticalLineEnergies() );

    reaction = scattering_reactions.find( MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION )->second;

    FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-5 );
    FRENSIE_CHECK_EQUAL( reaction->getMaxEnergy(), 20.0 );

    std::shared_ptr<const MonteCarlo::ElectroionizationSubshellAdjointElectroatomicReaction<Utility::LogLog> > k_reaction =
      std::dynamic_pointer_cast<const MonteCarlo::ElectroionizationSubshellAdjointElectroatomicReaction<Utility::LogLog> >( reaction );

    FRENSIE_CHECK_EQUAL( k_reaction->getCriticalLineEnergies(),
                         core.getCriticalLineEnergies() );

    reaction = scattering_reactions.find( MonteCarlo::ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION )->second;

    FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-5 );
    FRENSIE_CHECK_EQUAL( reaction->getMaxEnergy(), 20.0 );

    reaction = scattering_reactions.find( MonteCarlo::HYBRID_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION )->second;

    FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-5 );
    FRENSIE_CHECK_EQUAL( reaction->getMaxEnergy(), 20.0 );
  }

  // Check that the absorption reactions were constructed correctly
  const MonteCarlo::AdjointElectroatomCore::ConstReactionMap&
    absorption_reactions = core.getAbsorptionReactions();

  FRENSIE_CHECK_EQUAL( absorption_reactions.size(), 0 );

  // Test that the total cross section can be returned
  double energy = 1e-5;
  double cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.663039149151744843e+10, 1e-12 );

  energy = 1e-3;
  cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.840840949767912924e+07, 1e-12 );

  energy = 20.0;
  cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.371394886240131746e+04, 1e-12 );


  // Test that the absorption cross section can be returned
  cross_section = atom->getAbsorptionCrossSection( 1e-5 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section =  atom->getAbsorptionCrossSection( 1e-3 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 20.0 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  MonteCarlo::AdjointElectroatomicReactionType reaction;

  // Test that the atomic excitation cross section can be returned
  reaction = MonteCarlo::ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.124055828282346576e+07, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.050254326707092859e+07, 1e-12 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 8.182929983612992510e+04, 1e-12 );


  // Test that the bremsstrahlung cross section can be returned
  reaction = MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.420906922047235810e+01, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.557600066967186692e+01, 1e-12 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.314563595767325455e-01, 1e-12 );


  // Test that the coupled elastic cross section can be returned
  reaction = MonteCarlo::DECOUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that the coupled elastic cross section can be returned
  reaction = MonteCarlo::COUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that there is no hybrid elastic cross section
  reaction = MonteCarlo::HYBRID_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.7336893667900169e+08, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.951042357070542872e+06, 1e-12 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.053930205497564110, 1e-12 );


  // Test that there is no total electroionization
  reaction = MonteCarlo::TOTAL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that the K subshell electroionization cross section can be returned
  reaction = MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.629578195234655762e+10, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.595480829753698967e+07, 1e-12 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.188246363970631865e+04, 1e-12 );


  // Test that the L1 subshell electroionization cross section can be returned
  reaction = MonteCarlo::L1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that a adjoint electroatom map can be created (electroionization subshell data)
FRENSIE_UNIT_TEST( AdjointElectroatomFactory,
                   createAdjointElectroatomMap_ionization_subshells )
{
  // Create the set of electroatom aliases
  MonteCarlo::AdjointElectroatomFactory::ScatteringCenterNameSet electroatom_aliases;
  electroatom_aliases.insert( "C-Native" );

  MonteCarlo::SimulationProperties properties;

  {
    std::vector<double> user_critical_line_energies( 1, 10.0 );

    properties.setAdjointElasticCutoffAngleCosine( 1.0 );
    properties.setAdjointElectronEvaluationTolerance( 1e-7 );
    properties.setAdjointElasticElectronDistributionMode( MonteCarlo::DECOUPLED_DISTRIBUTION );
    properties.setCriticalAdjointElectronLineEnergies( user_critical_line_energies );
  }

  std::shared_ptr<MonteCarlo::AdjointElectroatomFactory> electroatom_factory(
                    new MonteCarlo::AdjointElectroatomFactory(
                                              *data_directory,
                                              electroatom_aliases,
                                              *adjoint_electroatom_definitions,
                                              properties,
                                              true ) );

  MonteCarlo::AdjointElectroatomFactory::AdjointElectroatomNameMap
    electroatom_map;

  electroatom_factory->createAdjointElectroatomMap( electroatom_map );

  FRENSIE_CHECK_EQUAL( electroatom_map.size(), 1 );
  FRENSIE_CHECK( electroatom_map.count( "C-Native" ) );
  FRENSIE_CHECK( electroatom_map["C-Native"].get() != NULL );

  std::shared_ptr<const MonteCarlo::AdjointElectroatom>& atom = electroatom_map["C-Native"];

  // Test the adjoint electroatom properties
  FRENSIE_CHECK_EQUAL( atom->getAtomicNumber(), 6 );
  FRENSIE_CHECK_FLOATING_EQUALITY( atom->getAtomicWeight(), 12.010980086796003263, 1e-12 );

  const MonteCarlo::AdjointElectroatomCore& core = atom->getCore();

  // Check that the grid searcher was constructed correctly
  FRENSIE_CHECK( !core.getGridSearcher().isValueWithinGridBounds( 9.9e-6 ) );
  FRENSIE_CHECK( core.getGridSearcher().isValueWithinGridBounds( 1e-5 ) );
  FRENSIE_CHECK( core.getGridSearcher().isValueWithinGridBounds( 20.0 ) );
  FRENSIE_CHECK( !core.getGridSearcher().isValueWithinGridBounds( 20.1 ) );
  FRENSIE_CHECK( core.hasSharedEnergyGrid() );

  // Check that the critical line energies were constructed correctly
  FRENSIE_CHECK_EQUAL( core.getCriticalLineEnergies().size(), 1 );
  FRENSIE_CHECK_EQUAL( core.getCriticalLineEnergies()[0], 10.0 );

  // Check that the total forward reaction was constructed correctly
  FRENSIE_CHECK_EQUAL( core.getTotalForwardReaction().getThresholdEnergy(),
                       1e-5 );
  FRENSIE_CHECK( core.getTotalForwardReaction().getCrossSection( 20.0 ) > 0.0 );

  // Check that the scattering reactions were constructed correctly
  const MonteCarlo::AdjointElectroatomCore::ConstReactionMap&
    scattering_reactions = core.getScatteringReactions();

  FRENSIE_CHECK_EQUAL( scattering_reactions.size(), 7 );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::L1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::L2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::L3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( !scattering_reactions.count( MonteCarlo::M1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::DECOUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION ) );

  {
    std::shared_ptr<const MonteCarlo::AdjointElectroatomicReaction> reaction =
      scattering_reactions.find( MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION )->second;

    FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-5 );
    FRENSIE_CHECK_EQUAL( reaction->getMaxEnergy(), 20.0 );

    std::shared_ptr<const MonteCarlo::ElectroionizationSubshellAdjointElectroatomicReaction<Utility::LogLog> > subshell_reaction =
      std::dynamic_pointer_cast<const MonteCarlo::ElectroionizationSubshellAdjointElectroatomicReaction<Utility::LogLog> >( reaction );

    FRENSIE_CHECK_EQUAL( subshell_reaction->getCriticalLineEnergies(),
                         core.getCriticalLineEnergies() );

    reaction =
      scattering_reactions.find( MonteCarlo::L3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION )->second;

    FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-5 );
    FRENSIE_CHECK_EQUAL( reaction->getMaxEnergy(), 20.0 );

    subshell_reaction =
      std::dynamic_pointer_cast<const MonteCarlo::ElectroionizationSubshellAdjointElectroatomicReaction<Utility::LogLog> >( reaction );

    FRENSIE_CHECK_EQUAL( subshell_reaction->getCriticalLineEnergies(),
                         core.getCriticalLineEnergies() );

    reaction = scattering_reactions.find( MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION )->second;

    FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-5 );
    FRENSIE_CHECK_EQUAL( reaction->getMaxEnergy(), 20.0 );

    std::shared_ptr<const MonteCarlo::BremsstrahlungAdjointElectroatomicReaction<Utility::LogLog> > brem_reaction =
      std::dynamic_pointer_cast<const MonteCarlo::BremsstrahlungAdjointElectroatomicReaction<Utility::LogLog> >( reaction );

    FRENSIE_CHECK_EQUAL( brem_reaction->getCriticalLineEnergies(),
                         core.getCriticalLineEnergies() );
  }

  // Check that the absorption reactions were constructed correctly
  const MonteCarlo::AdjointElectroatomCore::ConstReactionMap&
    absorption_reactions = core.getAbsorptionReactions();

  FRENSIE_CHECK_EQUAL( absorption_reactions.size(), 0 );

  // Test that the total cross section can be returned
  double energy = 1e-5;
  double cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.526128407318110962e+11, 1e-12 );

  energy = 1e-3;
  cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.844223355719951093e+08, 1e-12 );

  energy = 20.0;
  cross_section = atom->getTotalCrossSection( energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.730127126595737645e+05, 1e-12 );


  // Test that the absorption cross section can be returned
  cross_section = atom->getAbsorptionCrossSection( 1e-5 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section =  atom->getAbsorptionCrossSection( 1e-3 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getAbsorptionCrossSection( 20.0 );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  MonteCarlo::AdjointElectroatomicReactionType reaction;

  // Test that the atomic excitation cross section can be returned
  reaction = MonteCarlo::ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 5.9000914445996724e+07, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.528004595006961375e+07, 1e-12 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.240769986497469799e+05, 1e-12 );


  // Test that the bremsstrahlung cross section can be returned
  reaction = MonteCarlo::BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.383502051677240843e+02, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.879585026121018814e+02, 1e-12 );

  cross_section = atom->getReactionCrossSection( 19.9, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.548689592208527976, 1e-12 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 4.536969105953957637 );


  // Test that the coupled elastic cross section can be returned
  reaction = MonteCarlo::DECOUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.06351e+09, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 5.282253794701296091e+07, 1e-12 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.4129048986120211e+05, 1e-12 );


  // Test that the coupled elastic cross section can be returned
  reaction = MonteCarlo::COUPLED_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that there is no hybrid elastic cross section
  reaction = MonteCarlo::HYBRID_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that there is no total electroionization
  reaction = MonteCarlo::TOTAL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );


  // Test that the K subshell electroionization cross section can be returned
  reaction = MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.635900139568387508e+09, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.812006522686839476e+07, 1e-12 );

  cross_section = atom->getReactionCrossSection( 19.9, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.334379746068209533e+04, 1e-12 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 1.334578964645907581e+04 );

  // Test that there is no P3 subshell electroionization cross section
  reaction = MonteCarlo::L3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION;
  cross_section = atom->getReactionCrossSection( 1e-5, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.383647911074849854e+11, 1e-12 );

  cross_section = atom->getReactionCrossSection( 1e-3, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 3.606999221138125658e+07, 1e-12 );

  cross_section = atom->getReactionCrossSection( 19.9, reaction );
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.111426490518493811e+05, 1e-12 );

  cross_section = atom->getReactionCrossSection( 20.0, reaction );
  FRENSIE_CHECK_EQUAL( cross_section, 2.111803641061246162e+05 );

  // Reset the adjoint electroatom factory
  electroatom_factory.reset();
}

//---------------------------------------------------------------------------//
// Check that tables are not duplicated
FRENSIE_UNIT_TEST( AdjointElectroatomFactory, no_duplicate_tables )
{
  // Create the set of electroatom aliases
  MonteCarlo::AdjointElectroatomFactory::ScatteringCenterNameSet electroatom_aliases;
  electroatom_aliases.insert( "H-Native" );
  electroatom_aliases.insert( "H-1-Native" );

  MonteCarlo::SimulationProperties properties;
  properties.setAdjointElasticCutoffAngleCosine( 1.0 );

  std::shared_ptr<MonteCarlo::AdjointElectroatomFactory> electroatom_factory(
                    new MonteCarlo::AdjointElectroatomFactory(
                                              *data_directory,
                                              electroatom_aliases,
                                              *adjoint_electroatom_definitions,
                                              properties,
                                              true ) );

  MonteCarlo::AdjointElectroatomFactory::AdjointElectroatomNameMap
    electroatom_map;

  electroatom_factory->createAdjointElectroatomMap( electroatom_map );

  FRENSIE_CHECK_EQUAL( electroatom_map.size(), 2 );

  FRENSIE_CHECK( electroatom_map.count( "H-Native" ) );
  FRENSIE_CHECK( electroatom_map["H-Native"].get() != NULL );

  FRENSIE_CHECK( electroatom_map.count( "H-1-Native" ) );
  FRENSIE_CHECK( electroatom_map["H-1-Native"].get() != NULL );

  FRENSIE_CHECK( electroatom_map["H-Native"] == electroatom_map["H-1-Native"] );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_scattering_center_database_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_database",
                                        test_scattering_center_database_name, "",
                                        "Test scattering center database name "
                                        "with path" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Determine the database directory
  boost::filesystem::path database_path =
    test_scattering_center_database_name;

  data_directory.reset(
                  new boost::filesystem::path( database_path.parent_path() ) );

  // Load the database
  const Data::ScatteringCenterPropertiesDatabase database( database_path );

  const Data::AtomProperties& h_properties =
    database.getAtomProperties( 1001 );

  const Data::AtomProperties& c_properties =
    database.getAtomProperties( Data::C_ATOM );

  // Initialize the adjoint electroatom definitions
  adjoint_electroatom_definitions.reset( new MonteCarlo::ScatteringCenterDefinitionDatabase );

  MonteCarlo::ScatteringCenterDefinition& h_native_definition =
    adjoint_electroatom_definitions->createDefinition( "H-Native", Data::H_ATOM );

  adjoint_electroatom_definitions->createDefinitionAlias( "H-Native", "H-1-Native" );

  h_native_definition.setAdjointElectroatomicDataProperties(
           h_properties.getSharedAdjointElectroatomicDataProperties(
              Data::AdjointElectroatomicDataProperties::Native_EPR_FILE, 0 ) );

  MonteCarlo::ScatteringCenterDefinition& c_native_definition =
    adjoint_electroatom_definitions->createDefinition( "C-Native", Data::C_ATOM );

  c_native_definition.setAdjointElectroatomicDataProperties(
           c_properties.getSharedAdjointElectroatomicDataProperties(
              Data::AdjointElectroatomicDataProperties::Native_EPR_FILE, 0 ) );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();


//---------------------------------------------------------------------------//
// end tstAdjointElectroatomFactory.cpp
//---------------------------------------------------------------------------//
