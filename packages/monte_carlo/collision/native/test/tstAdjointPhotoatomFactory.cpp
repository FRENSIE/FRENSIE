//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointPhotoatomFactory.cpp
//! \author Alex Robinson
//! \brief  The adjoint photoatom factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotoatomFactory.hpp"
#include "MonteCarlo_LineEnergyAdjointPhotoatomicReaction.hpp"
#include "MonteCarlo_IncoherentAdjointPhotoatomicReaction.hpp"
#include "MonteCarlo_SimulationProperties.hpp"
#include "MonteCarlo_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::string cross_sections_xml_directory;
Teuchos::ParameterList cross_section_table_info;

//---------------------------------------------------------------------------//
// Check that an adjoint photoatom map can be created
TEUCHOS_UNIT_TEST( AdjointPhotoatomFactory,
                   createAdjointPhotoatomMap_native )
{
  std::unordered_set<std::string> adjoint_photoatom_aliases;
  adjoint_photoatom_aliases.insert( "Si-Native" );
  adjoint_photoatom_aliases.insert( "Al-Native" );

  MonteCarlo::SimulationProperties properties;

  {
    Teuchos::Array<double> user_critical_line_energies( 1, 20.0 );

    properties.setMaxAdjointPhotonEnergy( 20.0 );
    properties.setNumberOfAdjointPhotonHashGridBins( 100 );
    properties.setIncoherentAdjointModelType( MonteCarlo::WH_INCOHERENT_ADJOINT_MODEL );
    properties.setCriticalAdjointPhotonLineEnergies( user_critical_line_energies );
  }

  MonteCarlo::AdjointPhotoatomFactory factory( cross_sections_xml_directory,
                                               cross_section_table_info,
                                               adjoint_photoatom_aliases,
                                               properties,
                                               &out );
  
  std::unordered_map<std::string,Teuchos::RCP<MonteCarlo::AdjointPhotoatom> >
    adjoint_photoatom_map;

  factory.createAdjointPhotoatomMap( adjoint_photoatom_map );

  TEST_EQUALITY_CONST( adjoint_photoatom_map.size(), 2 );
  TEST_ASSERT( adjoint_photoatom_map.count( "Si-Native" ) );
  TEST_ASSERT( adjoint_photoatom_map.count( "Al-Native" ) );

  // We will just check one of the atoms since they will all be constructed
  // in the same way
  const MonteCarlo::AdjointPhotoatom adjoint_photoatom =
    *adjoint_photoatom_map.find( "Si-Native" )->second;

  // Check that the name is correct
  TEST_ASSERT( adjoint_photoatom.getAtomName().find( "14" ) <
               adjoint_photoatom.getAtomName().size() );

  // Check that the atomic number is correct
  TEST_EQUALITY_CONST( adjoint_photoatom.getAtomicNumber(), 14 );

  // Check that the atomic weight is correct
  TEST_EQUALITY_CONST( adjoint_photoatom.getAtomicWeight(),
                       2.80859719866649300e+01 );

  const MonteCarlo::AdjointPhotoatomCore& core = adjoint_photoatom.getCore();

  // Check that the grid searcher was constructed correctly
  TEST_ASSERT( !core.getGridSearcher().isValueWithinGridBounds( 9.9e-4 ) );
  TEST_ASSERT( core.getGridSearcher().isValueWithinGridBounds( 1e-3 ) );
  TEST_ASSERT( core.getGridSearcher().isValueWithinGridBounds( 20.0 ) );
  TEST_ASSERT( !core.getGridSearcher().isValueWithinGridBounds( 20.1 ) );
  TEST_ASSERT( core.hasSharedEnergyGrid() );

  // Check that the critical line energies were constructed correctly
  TEST_EQUALITY_CONST( core.getCriticalLineEnergies().size(), 2 );
  TEST_EQUALITY_CONST( core.getCriticalLineEnergies()[0],
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  TEST_EQUALITY_CONST( core.getCriticalLineEnergies()[1],
                       20.0 );

  // Check that the total forward reaction was constructed correctly
  TEST_EQUALITY_CONST( core.getTotalForwardReaction().getThresholdEnergy(),
                       1e-3 );
  TEST_ASSERT( core.getTotalForwardReaction().getCrossSection( 20.0 ) > 0.0 );

  // Check that the scattering reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    scattering_reactions = core.getScatteringReactions();

  TEST_EQUALITY_CONST( scattering_reactions.size(), 2 );
  TEST_ASSERT( scattering_reactions.count( MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( scattering_reactions.count( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );

  std::shared_ptr<const MonteCarlo::AdjointPhotoatomicReaction> reaction =
    scattering_reactions.find( MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION )->second;

  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-3 );
  TEST_EQUALITY_CONST( reaction->getMaxEnergy(), 20.0 );

  std::shared_ptr<const MonteCarlo::IncoherentAdjointPhotoatomicReaction<Utility::LinLin,false> > incoherent_reaction =
    std::dynamic_pointer_cast<const MonteCarlo::IncoherentAdjointPhotoatomicReaction<Utility::LinLin,false> >( reaction );

  TEST_EQUALITY_CONST( incoherent_reaction->getCriticalLineEnergies(),
                       core.getCriticalLineEnergies() );

  reaction = scattering_reactions.find( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION )->second;

  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-3 );
  TEST_EQUALITY_CONST( reaction->getMaxEnergy(), 20.0 );

  // Check that the absorption reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    absorption_reactions = core.getAbsorptionReactions();

  TEST_EQUALITY_CONST( absorption_reactions.size(), 0 );

  // Check that the line energy reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstLineEnergyReactionMap&
    line_energy_reactions = core.getLineEnergyReactions();

  TEST_EQUALITY_CONST( line_energy_reactions.size(), 1 );
  TEST_ASSERT( line_energy_reactions.count( Utility::PhysicalConstants::electron_rest_mass_energy ) );

  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    me_line_energy_reactions = line_energy_reactions.find( Utility::PhysicalConstants::electron_rest_mass_energy )->second;

  TEST_EQUALITY_CONST( me_line_energy_reactions.size(), 2 );
  TEST_ASSERT( me_line_energy_reactions.count( MonteCarlo::PAIR_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( me_line_energy_reactions.count( MonteCarlo::TRIPLET_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION ) );

  reaction = me_line_energy_reactions.find( MonteCarlo::PAIR_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION )->second;

  std::shared_ptr<const MonteCarlo::LineEnergyAdjointPhotoatomicReaction>
    line_energy_reaction = std::dynamic_pointer_cast<const MonteCarlo::LineEnergyAdjointPhotoatomicReaction>( reaction );

  TEST_EQUALITY_CONST( line_energy_reaction->getMinOutgoingEnergy(),
                       2*Utility::PhysicalConstants::electron_rest_mass_energy );
  TEST_EQUALITY_CONST( line_energy_reaction->getMaxOutgoingEnergy(), 20.0 );

  reaction = me_line_energy_reactions.find( MonteCarlo::TRIPLET_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION )->second;

  line_energy_reaction = std::dynamic_pointer_cast<const MonteCarlo::LineEnergyAdjointPhotoatomicReaction>( reaction );

  TEST_EQUALITY_CONST( line_energy_reaction->getMinOutgoingEnergy(),
                       4*Utility::PhysicalConstants::electron_rest_mass_energy );
  TEST_EQUALITY_CONST( line_energy_reaction->getMaxOutgoingEnergy(), 20.0 );
}

//---------------------------------------------------------------------------//
// Check that an adjoint photoatom map can be created
TEUCHOS_UNIT_TEST( AdjointPhotoatomFactory,
                   creatAdjointPhotoatomMap_native_subshells )
{
  std::unordered_set<std::string> adjoint_photoatom_aliases;
  adjoint_photoatom_aliases.insert( "Si-Native" );
  adjoint_photoatom_aliases.insert( "Al-Native" );

  MonteCarlo::SimulationProperties properties;

  {
    Teuchos::Array<double> user_critical_line_energies( 1, 20.0 );

    properties.setMaxAdjointPhotonEnergy( 20.0 );
    properties.setNumberOfAdjointPhotonHashGridBins( 100 );
    properties.setIncoherentAdjointModelType( MonteCarlo::IMPULSE_INCOHERENT_ADJOINT_MODEL );
    properties.setCriticalAdjointPhotonLineEnergies( user_critical_line_energies );
  }

  MonteCarlo::AdjointPhotoatomFactory factory( cross_sections_xml_directory,
                                               cross_section_table_info,
                                               adjoint_photoatom_aliases,
                                               properties,
                                               &out );

  std::unordered_map<std::string,Teuchos::RCP<MonteCarlo::AdjointPhotoatom> >
    adjoint_photoatom_map;

  factory.createAdjointPhotoatomMap( adjoint_photoatom_map );

  TEST_EQUALITY_CONST( adjoint_photoatom_map.size(), 2 );
  TEST_ASSERT( adjoint_photoatom_map.count( "Si-Native" ) );
  TEST_ASSERT( adjoint_photoatom_map.count( "Al-Native" ) );

  // We will just check one of the atoms since they will all be constructed
  // in the same way
  const MonteCarlo::AdjointPhotoatom adjoint_photoatom =
    *adjoint_photoatom_map.find( "Si-Native" )->second;

  // Check that the name is correct
  TEST_ASSERT( adjoint_photoatom.getAtomName().find( "14" ) <
               adjoint_photoatom.getAtomName().size() );

  // Check that the atomic number is correct
  TEST_EQUALITY_CONST( adjoint_photoatom.getAtomicNumber(), 14 );

  // Check that the atomic weight is correct
  TEST_EQUALITY_CONST( adjoint_photoatom.getAtomicWeight(),
                       2.80859719866649300e+01 );

  const MonteCarlo::AdjointPhotoatomCore& core = adjoint_photoatom.getCore();

  // Check that the grid searcher was constructed correctly
  TEST_ASSERT( !core.getGridSearcher().isValueWithinGridBounds( 9.9e-4 ) );
  TEST_ASSERT( core.getGridSearcher().isValueWithinGridBounds( 1e-3 ) );
  TEST_ASSERT( core.getGridSearcher().isValueWithinGridBounds( 20.0 ) );
  TEST_ASSERT( !core.getGridSearcher().isValueWithinGridBounds( 20.1 ) );
  TEST_ASSERT( core.hasSharedEnergyGrid() );

  // Check that the critical line energies were constructed correctly
  TEST_EQUALITY_CONST( core.getCriticalLineEnergies().size(), 2 );
  TEST_EQUALITY_CONST( core.getCriticalLineEnergies()[0],
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  TEST_EQUALITY_CONST( core.getCriticalLineEnergies()[1],
                       20.0 );

  // Check that the total forward reaction was constructed correctly
  TEST_EQUALITY_CONST( core.getTotalForwardReaction().getThresholdEnergy(),
                       1e-3 );
  TEST_ASSERT( core.getTotalForwardReaction().getCrossSection( 20.0 ) > 0.0 );

  // Check that the scattering reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    scattering_reactions = core.getScatteringReactions();

  TEST_EQUALITY_CONST( scattering_reactions.size(), 8 );
  TEST_ASSERT( scattering_reactions.count( MonteCarlo::K_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( scattering_reactions.count( MonteCarlo::L1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( scattering_reactions.count( MonteCarlo::L2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( scattering_reactions.count( MonteCarlo::L3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( scattering_reactions.count( MonteCarlo::M1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( scattering_reactions.count( MonteCarlo::M2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( scattering_reactions.count( MonteCarlo::M3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( scattering_reactions.count( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );

  std::shared_ptr<const MonteCarlo::AdjointPhotoatomicReaction> reaction =
    scattering_reactions.find( MonteCarlo::K_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION )->second;

  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-3 );
  TEST_EQUALITY_CONST( reaction->getMaxEnergy(), 20.0 );

  std::shared_ptr<const MonteCarlo::IncoherentAdjointPhotoatomicReaction<Utility::LinLin,false> > incoherent_reaction =
    std::dynamic_pointer_cast<const MonteCarlo::IncoherentAdjointPhotoatomicReaction<Utility::LinLin,false> >( reaction );

  TEST_EQUALITY_CONST( incoherent_reaction->getCriticalLineEnergies(),
                       core.getCriticalLineEnergies() );

  reaction =
    scattering_reactions.find( MonteCarlo::M3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION )->second;

  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-3 );
  TEST_EQUALITY_CONST( reaction->getMaxEnergy(), 20.0 );

  incoherent_reaction =
    std::dynamic_pointer_cast<const MonteCarlo::IncoherentAdjointPhotoatomicReaction<Utility::LinLin,false> >( reaction );

  TEST_EQUALITY_CONST( incoherent_reaction->getCriticalLineEnergies(),
                       core.getCriticalLineEnergies() );

  reaction = scattering_reactions.find( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION )->second;

  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-3 );
  TEST_EQUALITY_CONST( reaction->getMaxEnergy(), 20.0 );

  // Check that the absorption reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    absorption_reactions = core.getAbsorptionReactions();

  TEST_EQUALITY_CONST( absorption_reactions.size(), 0 );

  // Check that the line energy reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstLineEnergyReactionMap&
    line_energy_reactions = core.getLineEnergyReactions();

  TEST_EQUALITY_CONST( line_energy_reactions.size(), 1 );
  TEST_ASSERT( line_energy_reactions.count( Utility::PhysicalConstants::electron_rest_mass_energy ) );

  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    me_line_energy_reactions = line_energy_reactions.find( Utility::PhysicalConstants::electron_rest_mass_energy )->second;

  TEST_EQUALITY_CONST( me_line_energy_reactions.size(), 2 );
  TEST_ASSERT( me_line_energy_reactions.count( MonteCarlo::PAIR_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( me_line_energy_reactions.count( MonteCarlo::TRIPLET_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION ) );

  reaction = me_line_energy_reactions.find( MonteCarlo::PAIR_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION )->second;

  std::shared_ptr<const MonteCarlo::LineEnergyAdjointPhotoatomicReaction>
    line_energy_reaction = std::dynamic_pointer_cast<const MonteCarlo::LineEnergyAdjointPhotoatomicReaction>( reaction );

  TEST_EQUALITY_CONST( line_energy_reaction->getMinOutgoingEnergy(),
                       2*Utility::PhysicalConstants::electron_rest_mass_energy );
  TEST_EQUALITY_CONST( line_energy_reaction->getMaxOutgoingEnergy(), 20.0 );

  reaction = me_line_energy_reactions.find( MonteCarlo::TRIPLET_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION )->second;

  line_energy_reaction = std::dynamic_pointer_cast<const MonteCarlo::LineEnergyAdjointPhotoatomicReaction>( reaction );

  TEST_EQUALITY_CONST( line_energy_reaction->getMinOutgoingEnergy(),
                       4*Utility::PhysicalConstants::electron_rest_mass_energy );
  TEST_EQUALITY_CONST( line_energy_reaction->getMaxOutgoingEnergy(), 20.0 );
}

//---------------------------------------------------------------------------//
// Check that an adjoint photoatom map can be created
TEUCHOS_UNIT_TEST( AdjointPhotoatomFactory,
                   createAdjointPhotoatomMap_native_no_tp )
{
  std::unordered_set<std::string> adjoint_photoatom_aliases;
  adjoint_photoatom_aliases.insert( "Si-Native" );
  adjoint_photoatom_aliases.insert( "Al-Native" );

  MonteCarlo::SimulationProperties properties;

  {
    Teuchos::Array<double> user_critical_line_energies( 1, 1.5 );

    properties.setMaxAdjointPhotonEnergy( 1.5 );
    properties.setNumberOfAdjointPhotonHashGridBins( 100 );
    properties.setIncoherentAdjointModelType( MonteCarlo::WH_INCOHERENT_ADJOINT_MODEL );
    properties.setCriticalAdjointPhotonLineEnergies( user_critical_line_energies );
  }
  
  MonteCarlo::AdjointPhotoatomFactory factory( cross_sections_xml_directory,
                                               cross_section_table_info,
                                               adjoint_photoatom_aliases,
                                               properties,
                                               &out );

  std::unordered_map<std::string,Teuchos::RCP<MonteCarlo::AdjointPhotoatom> >
    adjoint_photoatom_map;

  factory.createAdjointPhotoatomMap( adjoint_photoatom_map );

  TEST_EQUALITY_CONST( adjoint_photoatom_map.size(), 2 );
  TEST_ASSERT( adjoint_photoatom_map.count( "Si-Native" ) );
  TEST_ASSERT( adjoint_photoatom_map.count( "Al-Native" ) );

  // We will just check one of the atoms since they will all be constructed
  // in the same way
  const MonteCarlo::AdjointPhotoatom adjoint_photoatom =
    *adjoint_photoatom_map.find( "Si-Native" )->second;

  // Check that the name is correct
  TEST_ASSERT( adjoint_photoatom.getAtomName().find( "14" ) <
               adjoint_photoatom.getAtomName().size() );

  // Check that the atomic number is correct
  TEST_EQUALITY_CONST( adjoint_photoatom.getAtomicNumber(), 14 );

  // Check that the atomic weight is correct
  TEST_EQUALITY_CONST( adjoint_photoatom.getAtomicWeight(),
                       2.80859719866649300e+01 );

  const MonteCarlo::AdjointPhotoatomCore& core = adjoint_photoatom.getCore();

  // Check that the grid searcher was constructed correctly
  TEST_ASSERT( !core.getGridSearcher().isValueWithinGridBounds( 9.9e-4 ) );
  TEST_ASSERT( core.getGridSearcher().isValueWithinGridBounds( 1e-3 ) );
  TEST_ASSERT( core.getGridSearcher().isValueWithinGridBounds( 1.5 ) );
  TEST_ASSERT( !core.getGridSearcher().isValueWithinGridBounds( 1.6 ) );
  TEST_ASSERT( core.hasSharedEnergyGrid() );

  // Check that the critical line energies were constructed correctly
  TEST_EQUALITY_CONST( core.getCriticalLineEnergies().size(), 2 );
  TEST_EQUALITY_CONST( core.getCriticalLineEnergies()[0],
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  TEST_EQUALITY_CONST( core.getCriticalLineEnergies()[1],
                       1.5 );

  // Check that the total forward reaction was constructed correctly
  TEST_EQUALITY_CONST( core.getTotalForwardReaction().getThresholdEnergy(),
                       1e-3 );
  TEST_ASSERT( core.getTotalForwardReaction().getCrossSection( 1.5 ) > 0.0 );

  // Check that the scattering reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    scattering_reactions = core.getScatteringReactions();

  TEST_EQUALITY_CONST( scattering_reactions.size(), 2 );
  TEST_ASSERT( scattering_reactions.count( MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( scattering_reactions.count( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );

  std::shared_ptr<const MonteCarlo::AdjointPhotoatomicReaction> reaction =
    scattering_reactions.find( MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION )->second;

  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-3 );
  TEST_EQUALITY_CONST( reaction->getMaxEnergy(), 1.5 );

  std::shared_ptr<const MonteCarlo::IncoherentAdjointPhotoatomicReaction<Utility::LinLin,false> > incoherent_reaction =
    std::dynamic_pointer_cast<const MonteCarlo::IncoherentAdjointPhotoatomicReaction<Utility::LinLin,false> >( reaction );

  TEST_EQUALITY_CONST( incoherent_reaction->getCriticalLineEnergies(),
                       core.getCriticalLineEnergies() );

  reaction = scattering_reactions.find( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION )->second;

  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-3 );
  TEST_EQUALITY_CONST( reaction->getMaxEnergy(), 1.5 );

  // Check that the absorption reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    absorption_reactions = core.getAbsorptionReactions();

  TEST_EQUALITY_CONST( absorption_reactions.size(), 0 );

  // Check that the line energy reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstLineEnergyReactionMap&
    line_energy_reactions = core.getLineEnergyReactions();

  TEST_EQUALITY_CONST( line_energy_reactions.size(), 1 );
  TEST_ASSERT( line_energy_reactions.count( Utility::PhysicalConstants::electron_rest_mass_energy ) );

  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    me_line_energy_reactions = line_energy_reactions.find( Utility::PhysicalConstants::electron_rest_mass_energy )->second;

  TEST_EQUALITY_CONST( me_line_energy_reactions.size(), 1 );
  TEST_ASSERT( me_line_energy_reactions.count( MonteCarlo::PAIR_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( !me_line_energy_reactions.count( MonteCarlo::TRIPLET_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION ) );

  reaction = me_line_energy_reactions.find( MonteCarlo::PAIR_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION )->second;

  std::shared_ptr<const MonteCarlo::LineEnergyAdjointPhotoatomicReaction>
    line_energy_reaction = std::dynamic_pointer_cast<const MonteCarlo::LineEnergyAdjointPhotoatomicReaction>( reaction );

  TEST_EQUALITY_CONST( line_energy_reaction->getMinOutgoingEnergy(),
                       2*Utility::PhysicalConstants::electron_rest_mass_energy );
  TEST_EQUALITY_CONST( line_energy_reaction->getMaxOutgoingEnergy(), 1.5 );
}

//---------------------------------------------------------------------------//
// Check that an adjoint photoatom map can be created
TEUCHOS_UNIT_TEST( AdjointPhotoatomFactory,
                   createAdjointPhotoatomMap_native_no_pp )
{
  std::unordered_set<std::string> adjoint_photoatom_aliases;
  adjoint_photoatom_aliases.insert( "Si-Native" );
  adjoint_photoatom_aliases.insert( "Al-Native" );

  MonteCarlo::SimulationProperties properties;

  {
    properties.setMaxAdjointPhotonEnergy( 1.0 );
    properties.setNumberOfAdjointPhotonHashGridBins( 100 );
    properties.setIncoherentAdjointModelType( MonteCarlo::WH_INCOHERENT_ADJOINT_MODEL );
  }

  MonteCarlo::AdjointPhotoatomFactory factory( cross_sections_xml_directory,
                                               cross_section_table_info,
                                               adjoint_photoatom_aliases,
                                               properties,
                                               &out );

  std::unordered_map<std::string,Teuchos::RCP<MonteCarlo::AdjointPhotoatom> >
    adjoint_photoatom_map;

  factory.createAdjointPhotoatomMap( adjoint_photoatom_map );

  TEST_EQUALITY_CONST( adjoint_photoatom_map.size(), 2 );
  TEST_ASSERT( adjoint_photoatom_map.count( "Si-Native" ) );
  TEST_ASSERT( adjoint_photoatom_map.count( "Al-Native" ) );

  // We will just check one of the atoms since they will all be constructed
  // in the same way
  const MonteCarlo::AdjointPhotoatom adjoint_photoatom =
    *adjoint_photoatom_map.find( "Si-Native" )->second;

  // Check that the name is correct
  TEST_ASSERT( adjoint_photoatom.getAtomName().find( "14" ) <
               adjoint_photoatom.getAtomName().size() );

  // Check that the atomic number is correct
  TEST_EQUALITY_CONST( adjoint_photoatom.getAtomicNumber(), 14 );

  // Check that the atomic weight is correct
  TEST_EQUALITY_CONST( adjoint_photoatom.getAtomicWeight(),
                       2.80859719866649300e+01 );

  const MonteCarlo::AdjointPhotoatomCore& core = adjoint_photoatom.getCore();

  // Check that the grid searcher was constructed correctly
  TEST_ASSERT( !core.getGridSearcher().isValueWithinGridBounds( 9.9e-4 ) );
  TEST_ASSERT( core.getGridSearcher().isValueWithinGridBounds( 1e-3 ) );
  TEST_ASSERT( core.getGridSearcher().isValueWithinGridBounds( 1.0 ) );
  TEST_ASSERT( !core.getGridSearcher().isValueWithinGridBounds( 1.1 ) );
  TEST_ASSERT( core.hasSharedEnergyGrid() );

  // Check that the critical line energies were constructed correctly
  TEST_EQUALITY_CONST( core.getCriticalLineEnergies().size(), 0 );

  // Check that the total forward reaction was constructed correctly
  TEST_EQUALITY_CONST( core.getTotalForwardReaction().getThresholdEnergy(),
                       1e-3 );
  TEST_ASSERT( core.getTotalForwardReaction().getCrossSection( 1.0 ) > 0.0 );

  // Check that the scattering reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    scattering_reactions = core.getScatteringReactions();

  TEST_EQUALITY_CONST( scattering_reactions.size(), 2 );
  TEST_ASSERT( scattering_reactions.count( MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( scattering_reactions.count( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );

  std::shared_ptr<const MonteCarlo::AdjointPhotoatomicReaction> reaction =
    scattering_reactions.find( MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION )->second;

  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-3 );
  TEST_EQUALITY_CONST( reaction->getMaxEnergy(), 1.0 );

  std::shared_ptr<const MonteCarlo::IncoherentAdjointPhotoatomicReaction<Utility::LinLin,false> > incoherent_reaction =
    std::dynamic_pointer_cast<const MonteCarlo::IncoherentAdjointPhotoatomicReaction<Utility::LinLin,false> >( reaction );

  TEST_EQUALITY_CONST( incoherent_reaction->getCriticalLineEnergies().size(), 1 );
  TEST_EQUALITY_CONST( incoherent_reaction->getCriticalLineEnergies()[0], 0.0 );

  reaction = scattering_reactions.find( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION )->second;

  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-3 );
  TEST_EQUALITY_CONST( reaction->getMaxEnergy(), 1.0 );

  // Check that the absorption reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    absorption_reactions = core.getAbsorptionReactions();

  TEST_EQUALITY_CONST( absorption_reactions.size(), 0 );

  // Check that the line energy reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstLineEnergyReactionMap&
    line_energy_reactions = core.getLineEnergyReactions();

  TEST_EQUALITY_CONST( line_energy_reactions.size(), 0 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_cross_sections_xml_directory",
                   &cross_sections_xml_directory,
                   "Test cross_sections.xml file name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  std::string cross_sections_xml_file = cross_sections_xml_directory;
  cross_sections_xml_file += "/cross_sections.xml";

  // Read in the xml file storing the cross section table info
  Teuchos::updateParametersFromXmlFile(
                               cross_sections_xml_file,
                               Teuchos::inoutArg( cross_section_table_info ) );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstAdjointPhotoatomFactory.cpp
//---------------------------------------------------------------------------//
