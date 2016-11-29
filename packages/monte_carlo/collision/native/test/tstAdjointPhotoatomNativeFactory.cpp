//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointPhotatomNativeFactory.cpp
//! \author Alex Robinson
//! \brief  The adjoint photoatom native factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotoatomNativeFactory.hpp"
#include "MonteCarlo_LineEnergyAdjointPhotoatomicReaction.hpp"
#include "MonteCarlo_IncoherentAdjointPhotoatomicReaction.hpp"
#include "MonteCarlo_SimulationProperties.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<const Data::AdjointElectronPhotonRelaxationDataContainer>
  data_container;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that an adjoint photoatom core can be constructed
TEUCHOS_UNIT_TEST( AdjointPhotoatomNativeFactory,
                   createAdjointPhotoatomCore )
{
  Teuchos::RCP<MonteCarlo::AdjointPhotoatomCore> adjoint_photoatom_core;

  MonteCarlo::SimulationProperties properties;

  {
    Teuchos::Array<double> user_critical_line_energies( 1 );
    user_critical_line_energies[0] = 20.0;

    properties.setMaxAdjointPhotonEnergy( 20.0 );
    properties.setNumberOfAdjointPhotonHashGridBins( 100 );
    properties.setIncoherentAdjointModelType( MonteCarlo::WH_INCOHERENT_ADJOINT_MODEL );
    properties.setCriticalAdjointPhotonLineEnergies( user_critical_line_energies );
  }
  
  MonteCarlo::AdjointPhotoatomNativeFactory::createAdjointPhotoatomCore(
                                                      *data_container,
                                                      properties,
                                                      adjoint_photoatom_core );

  // Check that the grid searcher was constructed correctly
  TEST_ASSERT( !adjoint_photoatom_core->getGridSearcher().isValueWithinGridBounds( 9.9e-4 ) );
  TEST_ASSERT( adjoint_photoatom_core->getGridSearcher().isValueWithinGridBounds( 1e-3 ) );
  TEST_ASSERT( adjoint_photoatom_core->getGridSearcher().isValueWithinGridBounds( 20.0 ) );
  TEST_ASSERT( !adjoint_photoatom_core->getGridSearcher().isValueWithinGridBounds( 20.1 ) );
  TEST_ASSERT( adjoint_photoatom_core->hasSharedEnergyGrid() );

  // Check that the critical line energies were constructed correctly
  TEST_EQUALITY_CONST( adjoint_photoatom_core->getCriticalLineEnergies().size(), 2 );
  TEST_EQUALITY_CONST( adjoint_photoatom_core->getCriticalLineEnergies()[0],
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  TEST_EQUALITY_CONST( adjoint_photoatom_core->getCriticalLineEnergies()[1],
                       20.0 );

  // Check that the total forward reaction was constructed correctly
  TEST_EQUALITY_CONST( adjoint_photoatom_core->getTotalForwardReaction().getThresholdEnergy(),
                       1e-3 );
  TEST_ASSERT( adjoint_photoatom_core->getTotalForwardReaction().getCrossSection( 20.0 ) > 0.0 );

  // Check that the scattering reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    scattering_reactions = adjoint_photoatom_core->getScatteringReactions();

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
                       adjoint_photoatom_core->getCriticalLineEnergies() );

  reaction = scattering_reactions.find( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION )->second;

  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-3 );
  TEST_EQUALITY_CONST( reaction->getMaxEnergy(), 20.0 );

  // Check that the absorption reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    absorption_reactions = adjoint_photoatom_core->getAbsorptionReactions();

  TEST_EQUALITY_CONST( absorption_reactions.size(), 0 );

  // Check that the line energy reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstLineEnergyReactionMap&
    line_energy_reactions = adjoint_photoatom_core->getLineEnergyReactions();

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
// Check that an adjoint photoatom core can be constructed
TEUCHOS_UNIT_TEST( AdjointPhotoatomNativeFactory,
                   createAdjointPhotoatomCore_subshells )
{
  Teuchos::RCP<MonteCarlo::AdjointPhotoatomCore> adjoint_photoatom_core;

  MonteCarlo::SimulationProperties properties;

  {
    Teuchos::Array<double> user_critical_line_energies( 1 );
    user_critical_line_energies[0] = 20.0;

    properties.setMaxAdjointPhotonEnergy( 20.0 );
    properties.setNumberOfAdjointPhotonHashGridBins( 100 );
    properties.setIncoherentAdjointModelType( MonteCarlo::IMPULSE_INCOHERENT_ADJOINT_MODEL );
    properties.setCriticalAdjointPhotonLineEnergies( user_critical_line_energies );
  }
  
  MonteCarlo::AdjointPhotoatomNativeFactory::createAdjointPhotoatomCore(
                                                      *data_container,
                                                      properties,
                                                      adjoint_photoatom_core );

  // Check that the grid searcher was constructed correctly
  TEST_ASSERT( !adjoint_photoatom_core->getGridSearcher().isValueWithinGridBounds( 9.9e-4 ) );
  TEST_ASSERT( adjoint_photoatom_core->getGridSearcher().isValueWithinGridBounds( 1e-3 ) );
  TEST_ASSERT( adjoint_photoatom_core->getGridSearcher().isValueWithinGridBounds( 20.0 ) );
  TEST_ASSERT( !adjoint_photoatom_core->getGridSearcher().isValueWithinGridBounds( 20.1 ) );
  TEST_ASSERT( adjoint_photoatom_core->hasSharedEnergyGrid() );

  // Check that the critical line energies were constructed correctly
  TEST_EQUALITY_CONST( adjoint_photoatom_core->getCriticalLineEnergies().size(), 2 );
  TEST_EQUALITY_CONST( adjoint_photoatom_core->getCriticalLineEnergies()[0],
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  TEST_EQUALITY_CONST( adjoint_photoatom_core->getCriticalLineEnergies()[1],
                       20.0 );

  // Check that the total forward reaction was constructed correctly
  TEST_EQUALITY_CONST( adjoint_photoatom_core->getTotalForwardReaction().getThresholdEnergy(),
                       1e-3 );
  TEST_ASSERT( adjoint_photoatom_core->getTotalForwardReaction().getCrossSection( 20.0 ) > 0.0 );

  // Check that the scattering reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    scattering_reactions = adjoint_photoatom_core->getScatteringReactions();

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
                       adjoint_photoatom_core->getCriticalLineEnergies() );

  reaction =
    scattering_reactions.find( MonteCarlo::M3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION )->second;

  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-3 );
  TEST_EQUALITY_CONST( reaction->getMaxEnergy(), 20.0 );

  incoherent_reaction =
    std::dynamic_pointer_cast<const MonteCarlo::IncoherentAdjointPhotoatomicReaction<Utility::LinLin,false> >( reaction );

  TEST_EQUALITY_CONST( incoherent_reaction->getCriticalLineEnergies(),
                       adjoint_photoatom_core->getCriticalLineEnergies() );

  reaction = scattering_reactions.find( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION )->second;

  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-3 );
  TEST_EQUALITY_CONST( reaction->getMaxEnergy(), 20.0 );

  // Check that the absorption reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    absorption_reactions = adjoint_photoatom_core->getAbsorptionReactions();

  TEST_EQUALITY_CONST( absorption_reactions.size(), 0 );

  // Check that the line energy reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstLineEnergyReactionMap&
    line_energy_reactions = adjoint_photoatom_core->getLineEnergyReactions();

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
// Check that an adjoint photoatom core can be constructed
TEUCHOS_UNIT_TEST( AdjointPhotoatomNativeFactory,
                   createAdjointPhotoatomCore_no_tp )
{
  Teuchos::RCP<MonteCarlo::AdjointPhotoatomCore> adjoint_photoatom_core;

  MonteCarlo::SimulationProperties properties;

  {
    Teuchos::Array<double> user_critical_line_energies( 1 );
    user_critical_line_energies[0] = 1.5;

    properties.setMaxAdjointPhotonEnergy( 1.5 );
    properties.setNumberOfAdjointPhotonHashGridBins( 100 );
    properties.setIncoherentAdjointModelType( MonteCarlo::WH_INCOHERENT_ADJOINT_MODEL );
    properties.setCriticalAdjointPhotonLineEnergies( user_critical_line_energies );
  }
  
  MonteCarlo::AdjointPhotoatomNativeFactory::createAdjointPhotoatomCore(
                                                      *data_container,
                                                      properties,
                                                      adjoint_photoatom_core );

  // Check that the grid searcher was constructed correctly
  TEST_ASSERT( !adjoint_photoatom_core->getGridSearcher().isValueWithinGridBounds( 9.9e-4 ) );
  TEST_ASSERT( adjoint_photoatom_core->getGridSearcher().isValueWithinGridBounds( 1e-3 ) );
  TEST_ASSERT( adjoint_photoatom_core->getGridSearcher().isValueWithinGridBounds( 1.5 ) );
  TEST_ASSERT( !adjoint_photoatom_core->getGridSearcher().isValueWithinGridBounds( 1.6 ) );
  TEST_ASSERT( adjoint_photoatom_core->hasSharedEnergyGrid() );

  // Check that the critical line energies were constructed correctly
  TEST_EQUALITY_CONST( adjoint_photoatom_core->getCriticalLineEnergies().size(), 2 );
  TEST_EQUALITY_CONST( adjoint_photoatom_core->getCriticalLineEnergies()[0],
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  TEST_EQUALITY_CONST( adjoint_photoatom_core->getCriticalLineEnergies()[1],
                       1.5 );

  // Check that the total forward reaction was constructed correctly
  TEST_EQUALITY_CONST( adjoint_photoatom_core->getTotalForwardReaction().getThresholdEnergy(),
                       1e-3 );
  TEST_ASSERT( adjoint_photoatom_core->getTotalForwardReaction().getCrossSection( 1.5 ) > 0.0 );

  // Check that the scattering reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    scattering_reactions = adjoint_photoatom_core->getScatteringReactions();

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
                       adjoint_photoatom_core->getCriticalLineEnergies() );

  reaction = scattering_reactions.find( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION )->second;

  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-3 );
  TEST_EQUALITY_CONST( reaction->getMaxEnergy(), 1.5 );

  // Check that the absorption reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    absorption_reactions = adjoint_photoatom_core->getAbsorptionReactions();

  TEST_EQUALITY_CONST( absorption_reactions.size(), 0 );

  // Check that the line energy reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstLineEnergyReactionMap&
    line_energy_reactions = adjoint_photoatom_core->getLineEnergyReactions();

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
// Chck that an adjoint photoatom core can be constructed
TEUCHOS_UNIT_TEST( AdjointPhotoatomNativeFactory,
                   createAdjointPhotoatomCore_no_pp )
{
  Teuchos::RCP<MonteCarlo::AdjointPhotoatomCore> adjoint_photoatom_core;

  MonteCarlo::SimulationProperties properties;

  {
    Teuchos::Array<double> user_critical_line_energies( 1 );
    user_critical_line_energies[0] = 1.0;

    properties.setMaxAdjointPhotonEnergy( 1.0 );
    properties.setNumberOfAdjointPhotonHashGridBins( 100 );
    properties.setIncoherentAdjointModelType( MonteCarlo::WH_INCOHERENT_ADJOINT_MODEL );
    properties.setCriticalAdjointPhotonLineEnergies( user_critical_line_energies );
  }
  
  MonteCarlo::AdjointPhotoatomNativeFactory::createAdjointPhotoatomCore(
                                                      *data_container,
                                                      properties,
                                                      adjoint_photoatom_core );

  // Check that the grid searcher was constructed correctly
  TEST_ASSERT( !adjoint_photoatom_core->getGridSearcher().isValueWithinGridBounds( 9.9e-4 ) );
  TEST_ASSERT( adjoint_photoatom_core->getGridSearcher().isValueWithinGridBounds( 1e-3 ) );
  TEST_ASSERT( adjoint_photoatom_core->getGridSearcher().isValueWithinGridBounds( 1.0 ) );
  TEST_ASSERT( !adjoint_photoatom_core->getGridSearcher().isValueWithinGridBounds( 1.1 ) );
  TEST_ASSERT( adjoint_photoatom_core->hasSharedEnergyGrid() );

  // Check that the critical line energies were constructed correctly
  TEST_EQUALITY_CONST( adjoint_photoatom_core->getCriticalLineEnergies().size(), 1 );
  TEST_EQUALITY_CONST( adjoint_photoatom_core->getCriticalLineEnergies()[0],
                       1.0 );

  // Check that the total forward reaction was constructed correctly
  TEST_EQUALITY_CONST( adjoint_photoatom_core->getTotalForwardReaction().getThresholdEnergy(),
                       1e-3 );
  TEST_ASSERT( adjoint_photoatom_core->getTotalForwardReaction().getCrossSection( 1.0 ) > 0.0 );

  // Check that the scattering reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    scattering_reactions = adjoint_photoatom_core->getScatteringReactions();

  TEST_EQUALITY_CONST( scattering_reactions.size(), 2 );
  TEST_ASSERT( scattering_reactions.count( MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( scattering_reactions.count( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );

  std::shared_ptr<const MonteCarlo::AdjointPhotoatomicReaction> reaction =
    scattering_reactions.find( MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION )->second;

  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-3 );
  TEST_EQUALITY_CONST( reaction->getMaxEnergy(), 1.0 );

  std::shared_ptr<const MonteCarlo::IncoherentAdjointPhotoatomicReaction<Utility::LinLin,false> > incoherent_reaction =
    std::dynamic_pointer_cast<const MonteCarlo::IncoherentAdjointPhotoatomicReaction<Utility::LinLin,false> >( reaction );

  TEST_EQUALITY_CONST( incoherent_reaction->getCriticalLineEnergies(),
                       adjoint_photoatom_core->getCriticalLineEnergies() );

  reaction = scattering_reactions.find( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION )->second;

  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-3 );
  TEST_EQUALITY_CONST( reaction->getMaxEnergy(), 1.0 );

  // Check that the absorption reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    absorption_reactions = adjoint_photoatom_core->getAbsorptionReactions();

  TEST_EQUALITY_CONST( absorption_reactions.size(), 0 );

  // Check that the line energy reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstLineEnergyReactionMap&
    line_energy_reactions = adjoint_photoatom_core->getLineEnergyReactions();

  TEST_EQUALITY_CONST( line_energy_reactions.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that an adjoint photoatom can be constructed
TEUCHOS_UNIT_TEST( AdjointPhotoatomNativeFactory, createAdjointPhotoatom )
{
  Teuchos::RCP<MonteCarlo::AdjointPhotoatom> adjoint_photoatom;

  MonteCarlo::SimulationProperties properties;

  {
    Teuchos::Array<double> user_critical_line_energies( 1 );
    user_critical_line_energies[0] = 10.0;

    properties.setMaxAdjointPhotonEnergy( 10.0 );
    properties.setNumberOfAdjointPhotonHashGridBins( 100 );
    properties.setIncoherentAdjointModelType( MonteCarlo::WH_INCOHERENT_ADJOINT_MODEL );
    properties.setCriticalAdjointPhotonLineEnergies( user_critical_line_energies );
  }

  MonteCarlo::AdjointPhotoatomNativeFactory::createAdjointPhotoatom(
                                       *data_container,
                                       "test_aepr_14",
                                       14.0,
                                       properties,
                                       adjoint_photoatom );

  // Check that the name is correct
  TEST_EQUALITY_CONST( adjoint_photoatom->getAtomName(), "test_aepr_14" );

  // Check that the atomic number is correct
  TEST_EQUALITY_CONST( adjoint_photoatom->getAtomicNumber(), 14 );

  // Check that the atomic weight is correct
  TEST_EQUALITY_CONST( adjoint_photoatom->getAtomicWeight(), 14.0 );

  const MonteCarlo::AdjointPhotoatomCore& core =
    adjoint_photoatom->getCore();

  // Check that the grid searcher was constructed correctly
  TEST_ASSERT( !core.getGridSearcher().isValueWithinGridBounds( 9.9e-4 ) );
  TEST_ASSERT( core.getGridSearcher().isValueWithinGridBounds( 1e-3 ) );
  TEST_ASSERT( core.getGridSearcher().isValueWithinGridBounds( 10.0 ) );
  TEST_ASSERT( !core.getGridSearcher().isValueWithinGridBounds( 10.1 ) );
  TEST_ASSERT( core.hasSharedEnergyGrid() );

  // Check that the critical line energies were constructed correctly
  TEST_EQUALITY_CONST( core.getCriticalLineEnergies().size(), 2 );
  TEST_EQUALITY_CONST( core.getCriticalLineEnergies()[0],
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  TEST_EQUALITY_CONST( core.getCriticalLineEnergies()[1],
                       10.0 );

  // Check that the total forward reaction was constructed correctly
  TEST_EQUALITY_CONST( core.getTotalForwardReaction().getThresholdEnergy(),
                       1e-3 );
  TEST_ASSERT( core.getTotalForwardReaction().getCrossSection( 10.0 ) > 0.0 );

  // Check that the scattering reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    scattering_reactions = core.getScatteringReactions();

  TEST_EQUALITY_CONST( scattering_reactions.size(), 2 );
  TEST_ASSERT( scattering_reactions.count( MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( scattering_reactions.count( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );

  std::shared_ptr<const MonteCarlo::AdjointPhotoatomicReaction> reaction =
    scattering_reactions.find( MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION )->second;

  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-3 );
  TEST_EQUALITY_CONST( reaction->getMaxEnergy(), 10.0 );

  std::shared_ptr<const MonteCarlo::IncoherentAdjointPhotoatomicReaction<Utility::LinLin,false> > incoherent_reaction =
    std::dynamic_pointer_cast<const MonteCarlo::IncoherentAdjointPhotoatomicReaction<Utility::LinLin,false> >( reaction );

  TEST_EQUALITY_CONST( incoherent_reaction->getCriticalLineEnergies(),
                       core.getCriticalLineEnergies() );

  reaction = scattering_reactions.find( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION )->second;

  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-3 );
  TEST_EQUALITY_CONST( reaction->getMaxEnergy(), 10.0 );

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
  TEST_EQUALITY_CONST( line_energy_reaction->getMaxOutgoingEnergy(), 10.0 );

  reaction = me_line_energy_reactions.find( MonteCarlo::TRIPLET_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION )->second;

  line_energy_reaction = std::dynamic_pointer_cast<const MonteCarlo::LineEnergyAdjointPhotoatomicReaction>( reaction );

  TEST_EQUALITY_CONST( line_energy_reaction->getMinOutgoingEnergy(),
                       4*Utility::PhysicalConstants::electron_rest_mass_energy );
  TEST_EQUALITY_CONST( line_energy_reaction->getMaxOutgoingEnergy(), 10.0 );
}

//---------------------------------------------------------------------------//
// Check that an adjoint photoatom can be constructed
TEUCHOS_UNIT_TEST( AdjointPhotoatomNativeFactory,
                   createAdjointPhotoatom_subshells )
{
  Teuchos::RCP<MonteCarlo::AdjointPhotoatom> adjoint_photoatom;

  MonteCarlo::SimulationProperties properties;

  {
    Teuchos::Array<double> user_critical_line_energies( 1 );
    user_critical_line_energies[0] = 10.0;

    properties.setMaxAdjointPhotonEnergy( 10.0 );
    properties.setNumberOfAdjointPhotonHashGridBins( 100 );
    properties.setIncoherentAdjointModelType( MonteCarlo::DB_IMPULSE_INCOHERENT_ADJOINT_MODEL );
    properties.setCriticalAdjointPhotonLineEnergies( user_critical_line_energies );
  }

  MonteCarlo::AdjointPhotoatomNativeFactory::createAdjointPhotoatom(
                               *data_container,
                               "test_aepr_14",
                               14.0,
                               properties,
                               adjoint_photoatom );

  // Check that the name is correct
  TEST_EQUALITY_CONST( adjoint_photoatom->getAtomName(), "test_aepr_14" );

  // Check that the atomic number is correct
  TEST_EQUALITY_CONST( adjoint_photoatom->getAtomicNumber(), 14 );

  // Check that the atomic weight is correct
  TEST_EQUALITY_CONST( adjoint_photoatom->getAtomicWeight(), 14.0 );

  const MonteCarlo::AdjointPhotoatomCore& core =
    adjoint_photoatom->getCore();
  
  // Check that the grid searcher was constructed correctly
  TEST_ASSERT( !core.getGridSearcher().isValueWithinGridBounds( 9.9e-4 ) );
  TEST_ASSERT( core.getGridSearcher().isValueWithinGridBounds( 1e-3 ) );
  TEST_ASSERT( core.getGridSearcher().isValueWithinGridBounds( 10.0 ) );
  TEST_ASSERT( !core.getGridSearcher().isValueWithinGridBounds( 10.1 ) );
  TEST_ASSERT( core.hasSharedEnergyGrid() );

  // Check that the critical line energies were constructed correctly
  TEST_EQUALITY_CONST( core.getCriticalLineEnergies().size(), 2 );
  TEST_EQUALITY_CONST( core.getCriticalLineEnergies()[0],
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  TEST_EQUALITY_CONST( core.getCriticalLineEnergies()[1],
                       10.0 );

  // Check that the total forward reaction was constructed correctly
  TEST_EQUALITY_CONST( core.getTotalForwardReaction().getThresholdEnergy(),
                       1e-3 );
  TEST_ASSERT( core.getTotalForwardReaction().getCrossSection( 10.0 ) > 0.0 );

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
  TEST_EQUALITY_CONST( reaction->getMaxEnergy(), 10.0 );

  std::shared_ptr<const MonteCarlo::IncoherentAdjointPhotoatomicReaction<Utility::LinLin,false> > incoherent_reaction =
    std::dynamic_pointer_cast<const MonteCarlo::IncoherentAdjointPhotoatomicReaction<Utility::LinLin,false> >( reaction );

  TEST_EQUALITY_CONST( incoherent_reaction->getCriticalLineEnergies(),
                       core.getCriticalLineEnergies() );

  reaction =
    scattering_reactions.find( MonteCarlo::M3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION )->second;

  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-3 );
  TEST_EQUALITY_CONST( reaction->getMaxEnergy(), 10.0 );

  incoherent_reaction =
    std::dynamic_pointer_cast<const MonteCarlo::IncoherentAdjointPhotoatomicReaction<Utility::LinLin,false> >( reaction );

  TEST_EQUALITY_CONST( incoherent_reaction->getCriticalLineEnergies(),
                       core.getCriticalLineEnergies() );

  reaction = scattering_reactions.find( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION )->second;

  TEST_EQUALITY_CONST( reaction->getThresholdEnergy(), 1e-3 );
  TEST_EQUALITY_CONST( reaction->getMaxEnergy(), 10.0 );

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
  TEST_EQUALITY_CONST( line_energy_reaction->getMaxOutgoingEnergy(), 10.0 );

  reaction = me_line_energy_reactions.find( MonteCarlo::TRIPLET_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION )->second;

  line_energy_reaction = std::dynamic_pointer_cast<const MonteCarlo::LineEnergyAdjointPhotoatomicReaction>( reaction );

  TEST_EQUALITY_CONST( line_energy_reaction->getMinOutgoingEnergy(),
                       4*Utility::PhysicalConstants::electron_rest_mass_energy );
  TEST_EQUALITY_CONST( line_energy_reaction->getMaxOutgoingEnergy(), 10.0 );
}

//---------------------------------------------------------------------------//
// Check that an adjoint photoatom core can be constructed
TEUCHOS_UNIT_TEST( AdjointPhotoatomNativeFactory,
                   createAdjointPhotoatom_no_tp )
{
  Teuchos::RCP<MonteCarlo::AdjointPhotoatom> adjoint_photoatom;

  MonteCarlo::SimulationProperties properties;

  {
    Teuchos::Array<double> user_critical_line_energies( 1 );
    user_critical_line_energies[0] = 1.5;

    properties.setMaxAdjointPhotonEnergy( 1.5 );
    properties.setNumberOfAdjointPhotonHashGridBins( 100 );
    properties.setIncoherentAdjointModelType( MonteCarlo::WH_INCOHERENT_ADJOINT_MODEL );
    properties.setCriticalAdjointPhotonLineEnergies( user_critical_line_energies );
  }

  MonteCarlo::AdjointPhotoatomNativeFactory::createAdjointPhotoatom(
                                                           *data_container,
                                                           "test_aepr_14",
                                                           14.0,
                                                           properties,
                                                           adjoint_photoatom );

  // Check that the name is correct
  TEST_EQUALITY_CONST( adjoint_photoatom->getAtomName(), "test_aepr_14" );

  // Check that the atomic number is correct
  TEST_EQUALITY_CONST( adjoint_photoatom->getAtomicNumber(), 14 );

  // Check that the atomic weight is correct
  TEST_EQUALITY_CONST( adjoint_photoatom->getAtomicWeight(), 14.0 );

  const MonteCarlo::AdjointPhotoatomCore& core =
    adjoint_photoatom->getCore();

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
// Chck that an adjoint photoatom core can be constructed
TEUCHOS_UNIT_TEST( AdjointPhotoatomNativeFactory,
                   createAdjointPhotoatom_no_pp )
{
  Teuchos::RCP<MonteCarlo::AdjointPhotoatom> adjoint_photoatom;

  MonteCarlo::SimulationProperties properties;

  properties.setMaxAdjointPhotonEnergy( 1.0 );
  properties.setNumberOfAdjointPhotonHashGridBins( 100 );
  properties.setIncoherentAdjointModelType( MonteCarlo::WH_INCOHERENT_ADJOINT_MODEL );

  MonteCarlo::AdjointPhotoatomNativeFactory::createAdjointPhotoatom(
                                                           *data_container,
                                                           "test_aepr_14",
                                                           14.0,
                                                           properties,
                                                           adjoint_photoatom );

  // Check that the name is correct
  TEST_EQUALITY_CONST( adjoint_photoatom->getAtomName(), "test_aepr_14" );

  // Check that the atomic number is correct
  TEST_EQUALITY_CONST( adjoint_photoatom->getAtomicNumber(), 14 );

  // Check that the atomic weight is correct
  TEST_EQUALITY_CONST( adjoint_photoatom->getAtomicWeight(), 14.0 );

  const MonteCarlo::AdjointPhotoatomCore& core =
    adjoint_photoatom->getCore();

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
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstAdjointPhotoatomNativeFactory.cpp
//---------------------------------------------------------------------------//
