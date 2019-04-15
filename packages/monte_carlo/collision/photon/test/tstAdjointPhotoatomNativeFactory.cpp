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

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotoatomNativeFactory.hpp"
#include "MonteCarlo_LineEnergyAdjointPhotoatomicReaction.hpp"
#include "MonteCarlo_IncoherentAdjointPhotoatomicReaction.hpp"
#include "MonteCarlo_SimulationProperties.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<const Data::AdjointElectronPhotonRelaxationDataContainer>
  data_container;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that an adjoint photoatom core can be constructed
FRENSIE_UNIT_TEST( AdjointPhotoatomNativeFactory,
                   createAdjointPhotoatomCore )
{
  std::shared_ptr<const MonteCarlo::AdjointPhotoatomCore> adjoint_photoatom_core;

  MonteCarlo::SimulationProperties properties;

  {
    std::vector<double> user_critical_line_energies( 1 );
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
  FRENSIE_CHECK( !adjoint_photoatom_core->getGridSearcher().isValueWithinGridBounds( 9.9e-4 ) );
  FRENSIE_CHECK( adjoint_photoatom_core->getGridSearcher().isValueWithinGridBounds( 1e-3 ) );
  FRENSIE_CHECK( adjoint_photoatom_core->getGridSearcher().isValueWithinGridBounds( 20.0 ) );
  FRENSIE_CHECK( !adjoint_photoatom_core->getGridSearcher().isValueWithinGridBounds( 20.1 ) );
  FRENSIE_CHECK( adjoint_photoatom_core->hasSharedEnergyGrid() );

  // Check that the critical line energies were constructed correctly
  FRENSIE_CHECK_EQUAL( adjoint_photoatom_core->getCriticalLineEnergies().size(), 2 );
  FRENSIE_CHECK_EQUAL( adjoint_photoatom_core->getCriticalLineEnergies()[0],
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( adjoint_photoatom_core->getCriticalLineEnergies()[1],
                       20.0 );

  // Check that the total forward reaction was constructed correctly
  FRENSIE_CHECK_EQUAL( adjoint_photoatom_core->getTotalForwardReaction().getThresholdEnergy(),
                       1e-3 );
  FRENSIE_CHECK( adjoint_photoatom_core->getTotalForwardReaction().getCrossSection( 20.0 ) > 0.0 );

  // Check that the scattering reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    scattering_reactions = adjoint_photoatom_core->getScatteringReactions();

  FRENSIE_CHECK_EQUAL( scattering_reactions.size(), 2 );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );

  std::shared_ptr<const MonteCarlo::AdjointPhotoatomicReaction> reaction =
    scattering_reactions.find( MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION )->second;

  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-3 );
  FRENSIE_CHECK_EQUAL( reaction->getMaxEnergy(), 20.0 );

  std::shared_ptr<const MonteCarlo::IncoherentAdjointPhotoatomicReaction<Utility::LinLin,false> > incoherent_reaction =
    std::dynamic_pointer_cast<const MonteCarlo::IncoherentAdjointPhotoatomicReaction<Utility::LinLin,false> >( reaction );

  FRENSIE_CHECK_EQUAL( incoherent_reaction->getCriticalLineEnergies(),
                       adjoint_photoatom_core->getCriticalLineEnergies() );

  reaction = scattering_reactions.find( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION )->second;

  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-3 );
  FRENSIE_CHECK_EQUAL( reaction->getMaxEnergy(), 20.0 );

  // Check that the absorption reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    absorption_reactions = adjoint_photoatom_core->getAbsorptionReactions();

  FRENSIE_CHECK_EQUAL( absorption_reactions.size(), 0 );

  // Check that the line energy reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstLineEnergyReactionMap&
    line_energy_reactions = adjoint_photoatom_core->getLineEnergyReactions();

  FRENSIE_CHECK_EQUAL( line_energy_reactions.size(), 1 );
  FRENSIE_CHECK( line_energy_reactions.count( Utility::PhysicalConstants::electron_rest_mass_energy ) );

  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    me_line_energy_reactions = line_energy_reactions.find( Utility::PhysicalConstants::electron_rest_mass_energy )->second;

  FRENSIE_CHECK_EQUAL( me_line_energy_reactions.size(), 2 );
  FRENSIE_CHECK( me_line_energy_reactions.count( MonteCarlo::PAIR_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( me_line_energy_reactions.count( MonteCarlo::TRIPLET_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION ) );

  reaction = me_line_energy_reactions.find( MonteCarlo::PAIR_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION )->second;

  std::shared_ptr<const MonteCarlo::LineEnergyAdjointPhotoatomicReaction>
    line_energy_reaction = std::dynamic_pointer_cast<const MonteCarlo::LineEnergyAdjointPhotoatomicReaction>( reaction );

  FRENSIE_CHECK_EQUAL( line_energy_reaction->getMinOutgoingEnergy(),
                       2*Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( line_energy_reaction->getMaxOutgoingEnergy(), 20.0 );

  reaction = me_line_energy_reactions.find( MonteCarlo::TRIPLET_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION )->second;

  line_energy_reaction = std::dynamic_pointer_cast<const MonteCarlo::LineEnergyAdjointPhotoatomicReaction>( reaction );

  FRENSIE_CHECK_EQUAL( line_energy_reaction->getMinOutgoingEnergy(),
                       4*Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( line_energy_reaction->getMaxOutgoingEnergy(), 20.0 );
}

//---------------------------------------------------------------------------//
// Check that an adjoint photoatom core can be constructed
FRENSIE_UNIT_TEST( AdjointPhotoatomNativeFactory,
                   createAdjointPhotoatomCore_subshells )
{
  std::shared_ptr<const MonteCarlo::AdjointPhotoatomCore> adjoint_photoatom_core;

  MonteCarlo::SimulationProperties properties;

  {
    std::vector<double> user_critical_line_energies( 1 );
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
  FRENSIE_CHECK( !adjoint_photoatom_core->getGridSearcher().isValueWithinGridBounds( 9.9e-4 ) );
  FRENSIE_CHECK( adjoint_photoatom_core->getGridSearcher().isValueWithinGridBounds( 1e-3 ) );
  FRENSIE_CHECK( adjoint_photoatom_core->getGridSearcher().isValueWithinGridBounds( 20.0 ) );
  FRENSIE_CHECK( !adjoint_photoatom_core->getGridSearcher().isValueWithinGridBounds( 20.1 ) );
  FRENSIE_CHECK( adjoint_photoatom_core->hasSharedEnergyGrid() );

  // Check that the critical line energies were constructed correctly
  FRENSIE_CHECK_EQUAL( adjoint_photoatom_core->getCriticalLineEnergies().size(), 2 );
  FRENSIE_CHECK_EQUAL( adjoint_photoatom_core->getCriticalLineEnergies()[0],
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( adjoint_photoatom_core->getCriticalLineEnergies()[1],
                       20.0 );

  // Check that the total forward reaction was constructed correctly
  FRENSIE_CHECK_EQUAL( adjoint_photoatom_core->getTotalForwardReaction().getThresholdEnergy(),
                       1e-3 );
  FRENSIE_CHECK( adjoint_photoatom_core->getTotalForwardReaction().getCrossSection( 20.0 ) > 0.0 );

  // Check that the scattering reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    scattering_reactions = adjoint_photoatom_core->getScatteringReactions();

  FRENSIE_CHECK_EQUAL( scattering_reactions.size(), 8 );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::K_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::L1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::L2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::L3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::M1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::M2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::M3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );

  std::shared_ptr<const MonteCarlo::AdjointPhotoatomicReaction> reaction =
    scattering_reactions.find( MonteCarlo::K_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION )->second;

  FRENSIE_CHECK_FLOATING_EQUALITY( reaction->getThresholdEnergy(),
                                   1.815507193800007350e-03,
                                   1e-15 );
  FRENSIE_CHECK_EQUAL( reaction->getMaxEnergy(), 20.0 );

  std::shared_ptr<const MonteCarlo::IncoherentAdjointPhotoatomicReaction<Utility::LinLin,false> > incoherent_reaction =
    std::dynamic_pointer_cast<const MonteCarlo::IncoherentAdjointPhotoatomicReaction<Utility::LinLin,false> >( reaction );

  FRENSIE_CHECK_EQUAL( incoherent_reaction->getCriticalLineEnergies(),
                       adjoint_photoatom_core->getCriticalLineEnergies() );

  reaction =
    scattering_reactions.find( MonteCarlo::M3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION )->second;

  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-3 );
  FRENSIE_CHECK_EQUAL( reaction->getMaxEnergy(), 20.0 );

  incoherent_reaction =
    std::dynamic_pointer_cast<const MonteCarlo::IncoherentAdjointPhotoatomicReaction<Utility::LinLin,false> >( reaction );

  FRENSIE_CHECK_EQUAL( incoherent_reaction->getCriticalLineEnergies(),
                       adjoint_photoatom_core->getCriticalLineEnergies() );

  reaction = scattering_reactions.find( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION )->second;

  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-3 );
  FRENSIE_CHECK_EQUAL( reaction->getMaxEnergy(), 20.0 );

  // Check that the absorption reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    absorption_reactions = adjoint_photoatom_core->getAbsorptionReactions();

  FRENSIE_CHECK_EQUAL( absorption_reactions.size(), 0 );

  // Check that the line energy reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstLineEnergyReactionMap&
    line_energy_reactions = adjoint_photoatom_core->getLineEnergyReactions();

  FRENSIE_CHECK_EQUAL( line_energy_reactions.size(), 1 );
  FRENSIE_CHECK( line_energy_reactions.count( Utility::PhysicalConstants::electron_rest_mass_energy ) );

  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    me_line_energy_reactions = line_energy_reactions.find( Utility::PhysicalConstants::electron_rest_mass_energy )->second;

  FRENSIE_CHECK_EQUAL( me_line_energy_reactions.size(), 2 );
  FRENSIE_CHECK( me_line_energy_reactions.count( MonteCarlo::PAIR_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( me_line_energy_reactions.count( MonteCarlo::TRIPLET_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION ) );

  reaction = me_line_energy_reactions.find( MonteCarlo::PAIR_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION )->second;

  std::shared_ptr<const MonteCarlo::LineEnergyAdjointPhotoatomicReaction>
    line_energy_reaction = std::dynamic_pointer_cast<const MonteCarlo::LineEnergyAdjointPhotoatomicReaction>( reaction );

  FRENSIE_CHECK_EQUAL( line_energy_reaction->getMinOutgoingEnergy(),
                       2*Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( line_energy_reaction->getMaxOutgoingEnergy(), 20.0 );

  reaction = me_line_energy_reactions.find( MonteCarlo::TRIPLET_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION )->second;

  line_energy_reaction = std::dynamic_pointer_cast<const MonteCarlo::LineEnergyAdjointPhotoatomicReaction>( reaction );

  FRENSIE_CHECK_EQUAL( line_energy_reaction->getMinOutgoingEnergy(),
                       4*Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( line_energy_reaction->getMaxOutgoingEnergy(), 20.0 );
}

//---------------------------------------------------------------------------//
// Check that an adjoint photoatom core can be constructed
FRENSIE_UNIT_TEST( AdjointPhotoatomNativeFactory,
                   createAdjointPhotoatomCore_no_tp )
{
  std::shared_ptr<const MonteCarlo::AdjointPhotoatomCore> adjoint_photoatom_core;

  MonteCarlo::SimulationProperties properties;

  {
    std::vector<double> user_critical_line_energies( 1 );
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
  FRENSIE_CHECK( !adjoint_photoatom_core->getGridSearcher().isValueWithinGridBounds( 9.9e-4 ) );
  FRENSIE_CHECK( adjoint_photoatom_core->getGridSearcher().isValueWithinGridBounds( 1e-3 ) );
  FRENSIE_CHECK( adjoint_photoatom_core->getGridSearcher().isValueWithinGridBounds( 1.5 ) );
  FRENSIE_CHECK( !adjoint_photoatom_core->getGridSearcher().isValueWithinGridBounds( 1.6 ) );
  FRENSIE_CHECK( adjoint_photoatom_core->hasSharedEnergyGrid() );

  // Check that the critical line energies were constructed correctly
  FRENSIE_CHECK_EQUAL( adjoint_photoatom_core->getCriticalLineEnergies().size(), 2 );
  FRENSIE_CHECK_EQUAL( adjoint_photoatom_core->getCriticalLineEnergies()[0],
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( adjoint_photoatom_core->getCriticalLineEnergies()[1],
                       1.5 );

  // Check that the total forward reaction was constructed correctly
  FRENSIE_CHECK_EQUAL( adjoint_photoatom_core->getTotalForwardReaction().getThresholdEnergy(),
                       1e-3 );
  FRENSIE_CHECK( adjoint_photoatom_core->getTotalForwardReaction().getCrossSection( 1.5 ) > 0.0 );

  // Check that the scattering reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    scattering_reactions = adjoint_photoatom_core->getScatteringReactions();

  FRENSIE_CHECK_EQUAL( scattering_reactions.size(), 2 );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );

  std::shared_ptr<const MonteCarlo::AdjointPhotoatomicReaction> reaction =
    scattering_reactions.find( MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION )->second;

  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-3 );
  FRENSIE_CHECK_EQUAL( reaction->getMaxEnergy(), 1.5 );

  std::shared_ptr<const MonteCarlo::IncoherentAdjointPhotoatomicReaction<Utility::LinLin,false> > incoherent_reaction =
    std::dynamic_pointer_cast<const MonteCarlo::IncoherentAdjointPhotoatomicReaction<Utility::LinLin,false> >( reaction );

  FRENSIE_CHECK_EQUAL( incoherent_reaction->getCriticalLineEnergies(),
                       adjoint_photoatom_core->getCriticalLineEnergies() );

  reaction = scattering_reactions.find( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION )->second;

  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-3 );
  FRENSIE_CHECK_EQUAL( reaction->getMaxEnergy(), 1.5 );

  // Check that the absorption reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    absorption_reactions = adjoint_photoatom_core->getAbsorptionReactions();

  FRENSIE_CHECK_EQUAL( absorption_reactions.size(), 0 );

  // Check that the line energy reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstLineEnergyReactionMap&
    line_energy_reactions = adjoint_photoatom_core->getLineEnergyReactions();

  FRENSIE_CHECK_EQUAL( line_energy_reactions.size(), 1 );
  FRENSIE_CHECK( line_energy_reactions.count( Utility::PhysicalConstants::electron_rest_mass_energy ) );

  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    me_line_energy_reactions = line_energy_reactions.find( Utility::PhysicalConstants::electron_rest_mass_energy )->second;

  FRENSIE_CHECK_EQUAL( me_line_energy_reactions.size(), 1 );
  FRENSIE_CHECK( me_line_energy_reactions.count( MonteCarlo::PAIR_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( !me_line_energy_reactions.count( MonteCarlo::TRIPLET_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION ) );

  reaction = me_line_energy_reactions.find( MonteCarlo::PAIR_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION )->second;

  std::shared_ptr<const MonteCarlo::LineEnergyAdjointPhotoatomicReaction>
    line_energy_reaction = std::dynamic_pointer_cast<const MonteCarlo::LineEnergyAdjointPhotoatomicReaction>( reaction );

  FRENSIE_CHECK_EQUAL( line_energy_reaction->getMinOutgoingEnergy(),
                       2*Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( line_energy_reaction->getMaxOutgoingEnergy(), 1.5 );
}

//---------------------------------------------------------------------------//
// Chck that an adjoint photoatom core can be constructed
FRENSIE_UNIT_TEST( AdjointPhotoatomNativeFactory,
                   createAdjointPhotoatomCore_no_pp )
{
  std::shared_ptr<const MonteCarlo::AdjointPhotoatomCore> adjoint_photoatom_core;

  MonteCarlo::SimulationProperties properties;

  {
    std::vector<double> user_critical_line_energies( 1 );
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
  FRENSIE_CHECK( !adjoint_photoatom_core->getGridSearcher().isValueWithinGridBounds( 9.9e-4 ) );
  FRENSIE_CHECK( adjoint_photoatom_core->getGridSearcher().isValueWithinGridBounds( 1e-3 ) );
  FRENSIE_CHECK( adjoint_photoatom_core->getGridSearcher().isValueWithinGridBounds( 1.0 ) );
  FRENSIE_CHECK( !adjoint_photoatom_core->getGridSearcher().isValueWithinGridBounds( 1.1 ) );
  FRENSIE_CHECK( adjoint_photoatom_core->hasSharedEnergyGrid() );

  // Check that the critical line energies were constructed correctly
  FRENSIE_CHECK_EQUAL( adjoint_photoatom_core->getCriticalLineEnergies().size(), 1 );
  FRENSIE_CHECK_EQUAL( adjoint_photoatom_core->getCriticalLineEnergies()[0],
                       1.0 );

  // Check that the total forward reaction was constructed correctly
  FRENSIE_CHECK_EQUAL( adjoint_photoatom_core->getTotalForwardReaction().getThresholdEnergy(),
                       1e-3 );
  FRENSIE_CHECK( adjoint_photoatom_core->getTotalForwardReaction().getCrossSection( 1.0 ) > 0.0 );

  // Check that the scattering reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    scattering_reactions = adjoint_photoatom_core->getScatteringReactions();

  FRENSIE_CHECK_EQUAL( scattering_reactions.size(), 2 );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );

  std::shared_ptr<const MonteCarlo::AdjointPhotoatomicReaction> reaction =
    scattering_reactions.find( MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION )->second;

  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-3 );
  FRENSIE_CHECK_EQUAL( reaction->getMaxEnergy(), 1.0 );

  std::shared_ptr<const MonteCarlo::IncoherentAdjointPhotoatomicReaction<Utility::LinLin,false> > incoherent_reaction =
    std::dynamic_pointer_cast<const MonteCarlo::IncoherentAdjointPhotoatomicReaction<Utility::LinLin,false> >( reaction );

  FRENSIE_CHECK_EQUAL( incoherent_reaction->getCriticalLineEnergies(),
                       adjoint_photoatom_core->getCriticalLineEnergies() );

  reaction = scattering_reactions.find( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION )->second;

  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-3 );
  FRENSIE_CHECK_EQUAL( reaction->getMaxEnergy(), 1.0 );

  // Check that the absorption reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    absorption_reactions = adjoint_photoatom_core->getAbsorptionReactions();

  FRENSIE_CHECK_EQUAL( absorption_reactions.size(), 0 );

  // Check that the line energy reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstLineEnergyReactionMap&
    line_energy_reactions = adjoint_photoatom_core->getLineEnergyReactions();

  FRENSIE_CHECK_EQUAL( line_energy_reactions.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that an adjoint photoatom can be constructed
FRENSIE_UNIT_TEST( AdjointPhotoatomNativeFactory, createAdjointPhotoatom )
{
  std::shared_ptr<const MonteCarlo::AdjointPhotoatom> adjoint_photoatom;

  MonteCarlo::SimulationProperties properties;

  {
    std::vector<double> user_critical_line_energies( 1 );
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
  FRENSIE_CHECK_EQUAL( adjoint_photoatom->getAtomName(), "test_aepr_14" );

  // Check that the atomic number is correct
  FRENSIE_CHECK_EQUAL( adjoint_photoatom->getAtomicNumber(), 14 );

  // Check that the atomic weight is correct
  FRENSIE_CHECK_EQUAL( adjoint_photoatom->getAtomicWeight(), 14.0 );

  const MonteCarlo::AdjointPhotoatomCore& core =
    adjoint_photoatom->getCore();

  // Check that the grid searcher was constructed correctly
  FRENSIE_CHECK( !core.getGridSearcher().isValueWithinGridBounds( 9.9e-4 ) );
  FRENSIE_CHECK( core.getGridSearcher().isValueWithinGridBounds( 1e-3 ) );
  FRENSIE_CHECK( core.getGridSearcher().isValueWithinGridBounds( 10.0 ) );
  FRENSIE_CHECK( !core.getGridSearcher().isValueWithinGridBounds( 10.1 ) );
  FRENSIE_CHECK( core.hasSharedEnergyGrid() );

  // Check that the critical line energies were constructed correctly
  FRENSIE_CHECK_EQUAL( core.getCriticalLineEnergies().size(), 2 );
  FRENSIE_CHECK_EQUAL( core.getCriticalLineEnergies()[0],
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( core.getCriticalLineEnergies()[1],
                       10.0 );

  // Check that the total forward reaction was constructed correctly
  FRENSIE_CHECK_EQUAL( core.getTotalForwardReaction().getThresholdEnergy(),
                       1e-3 );
  FRENSIE_CHECK( core.getTotalForwardReaction().getCrossSection( 10.0 ) > 0.0 );

  // Check that the scattering reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    scattering_reactions = core.getScatteringReactions();

  FRENSIE_CHECK_EQUAL( scattering_reactions.size(), 2 );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );

  std::shared_ptr<const MonteCarlo::AdjointPhotoatomicReaction> reaction =
    scattering_reactions.find( MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION )->second;

  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-3 );
  FRENSIE_CHECK_EQUAL( reaction->getMaxEnergy(), 10.0 );

  std::shared_ptr<const MonteCarlo::IncoherentAdjointPhotoatomicReaction<Utility::LinLin,false> > incoherent_reaction =
    std::dynamic_pointer_cast<const MonteCarlo::IncoherentAdjointPhotoatomicReaction<Utility::LinLin,false> >( reaction );

  FRENSIE_CHECK_EQUAL( incoherent_reaction->getCriticalLineEnergies(),
                       core.getCriticalLineEnergies() );

  reaction = scattering_reactions.find( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION )->second;

  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-3 );
  FRENSIE_CHECK_EQUAL( reaction->getMaxEnergy(), 10.0 );

  // Check that the absorption reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    absorption_reactions = core.getAbsorptionReactions();

  FRENSIE_CHECK_EQUAL( absorption_reactions.size(), 0 );

  // Check that the line energy reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstLineEnergyReactionMap&
    line_energy_reactions = core.getLineEnergyReactions();

  FRENSIE_CHECK_EQUAL( line_energy_reactions.size(), 1 );
  FRENSIE_CHECK( line_energy_reactions.count( Utility::PhysicalConstants::electron_rest_mass_energy ) );

  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    me_line_energy_reactions = line_energy_reactions.find( Utility::PhysicalConstants::electron_rest_mass_energy )->second;

  FRENSIE_CHECK_EQUAL( me_line_energy_reactions.size(), 2 );
  FRENSIE_CHECK( me_line_energy_reactions.count( MonteCarlo::PAIR_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( me_line_energy_reactions.count( MonteCarlo::TRIPLET_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION ) );

  reaction = me_line_energy_reactions.find( MonteCarlo::PAIR_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION )->second;

  std::shared_ptr<const MonteCarlo::LineEnergyAdjointPhotoatomicReaction>
    line_energy_reaction = std::dynamic_pointer_cast<const MonteCarlo::LineEnergyAdjointPhotoatomicReaction>( reaction );

  FRENSIE_CHECK_EQUAL( line_energy_reaction->getMinOutgoingEnergy(),
                       2*Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( line_energy_reaction->getMaxOutgoingEnergy(), 10.0 );

  reaction = me_line_energy_reactions.find( MonteCarlo::TRIPLET_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION )->second;

  line_energy_reaction = std::dynamic_pointer_cast<const MonteCarlo::LineEnergyAdjointPhotoatomicReaction>( reaction );

  FRENSIE_CHECK_EQUAL( line_energy_reaction->getMinOutgoingEnergy(),
                       4*Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( line_energy_reaction->getMaxOutgoingEnergy(), 10.0 );
}

//---------------------------------------------------------------------------//
// Check that an adjoint photoatom can be constructed
FRENSIE_UNIT_TEST( AdjointPhotoatomNativeFactory,
                   createAdjointPhotoatom_subshells )
{
  std::shared_ptr<const MonteCarlo::AdjointPhotoatom> adjoint_photoatom;

  MonteCarlo::SimulationProperties properties;

  {
    std::vector<double> user_critical_line_energies( 1 );
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
  FRENSIE_CHECK_EQUAL( adjoint_photoatom->getAtomName(), "test_aepr_14" );

  // Check that the atomic number is correct
  FRENSIE_CHECK_EQUAL( adjoint_photoatom->getAtomicNumber(), 14 );

  // Check that the atomic weight is correct
  FRENSIE_CHECK_EQUAL( adjoint_photoatom->getAtomicWeight(), 14.0 );

  const MonteCarlo::AdjointPhotoatomCore& core =
    adjoint_photoatom->getCore();
  
  // Check that the grid searcher was constructed correctly
  FRENSIE_CHECK( !core.getGridSearcher().isValueWithinGridBounds( 9.9e-4 ) );
  FRENSIE_CHECK( core.getGridSearcher().isValueWithinGridBounds( 1e-3 ) );
  FRENSIE_CHECK( core.getGridSearcher().isValueWithinGridBounds( 10.0 ) );
  FRENSIE_CHECK( !core.getGridSearcher().isValueWithinGridBounds( 10.1 ) );
  FRENSIE_CHECK( core.hasSharedEnergyGrid() );

  // Check that the critical line energies were constructed correctly
  FRENSIE_CHECK_EQUAL( core.getCriticalLineEnergies().size(), 2 );
  FRENSIE_CHECK_EQUAL( core.getCriticalLineEnergies()[0],
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( core.getCriticalLineEnergies()[1],
                       10.0 );

  // Check that the total forward reaction was constructed correctly
  FRENSIE_CHECK_EQUAL( core.getTotalForwardReaction().getThresholdEnergy(),
                       1e-3 );
  FRENSIE_CHECK( core.getTotalForwardReaction().getCrossSection( 10.0 ) > 0.0 );

  // Check that the scattering reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    scattering_reactions = core.getScatteringReactions();

  FRENSIE_CHECK_EQUAL( scattering_reactions.size(), 8 );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::K_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::L1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::L2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::L3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::M1_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::M2_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::M3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );

  std::shared_ptr<const MonteCarlo::AdjointPhotoatomicReaction> reaction =
    scattering_reactions.find( MonteCarlo::K_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION )->second;

  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-3 );
  FRENSIE_CHECK_EQUAL( reaction->getMaxEnergy(), 10.0 );

  std::shared_ptr<const MonteCarlo::IncoherentAdjointPhotoatomicReaction<Utility::LinLin,false> > incoherent_reaction =
    std::dynamic_pointer_cast<const MonteCarlo::IncoherentAdjointPhotoatomicReaction<Utility::LinLin,false> >( reaction );

  FRENSIE_CHECK_EQUAL( incoherent_reaction->getCriticalLineEnergies(),
                       core.getCriticalLineEnergies() );

  reaction =
    scattering_reactions.find( MonteCarlo::M3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION )->second;

  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-3 );
  FRENSIE_CHECK_EQUAL( reaction->getMaxEnergy(), 10.0 );

  incoherent_reaction =
    std::dynamic_pointer_cast<const MonteCarlo::IncoherentAdjointPhotoatomicReaction<Utility::LinLin,false> >( reaction );

  FRENSIE_CHECK_EQUAL( incoherent_reaction->getCriticalLineEnergies(),
                       core.getCriticalLineEnergies() );

  reaction = scattering_reactions.find( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION )->second;

  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-3 );
  FRENSIE_CHECK_EQUAL( reaction->getMaxEnergy(), 10.0 );

  // Check that the absorption reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    absorption_reactions = core.getAbsorptionReactions();

  FRENSIE_CHECK_EQUAL( absorption_reactions.size(), 0 );

  // Check that the line energy reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstLineEnergyReactionMap&
    line_energy_reactions = core.getLineEnergyReactions();

  FRENSIE_CHECK_EQUAL( line_energy_reactions.size(), 1 );
  FRENSIE_CHECK( line_energy_reactions.count( Utility::PhysicalConstants::electron_rest_mass_energy ) );

  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    me_line_energy_reactions = line_energy_reactions.find( Utility::PhysicalConstants::electron_rest_mass_energy )->second;

  FRENSIE_CHECK_EQUAL( me_line_energy_reactions.size(), 2 );
  FRENSIE_CHECK( me_line_energy_reactions.count( MonteCarlo::PAIR_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( me_line_energy_reactions.count( MonteCarlo::TRIPLET_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION ) );

  reaction = me_line_energy_reactions.find( MonteCarlo::PAIR_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION )->second;

  std::shared_ptr<const MonteCarlo::LineEnergyAdjointPhotoatomicReaction>
    line_energy_reaction = std::dynamic_pointer_cast<const MonteCarlo::LineEnergyAdjointPhotoatomicReaction>( reaction );

  FRENSIE_CHECK_EQUAL( line_energy_reaction->getMinOutgoingEnergy(),
                       2*Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( line_energy_reaction->getMaxOutgoingEnergy(), 10.0 );

  reaction = me_line_energy_reactions.find( MonteCarlo::TRIPLET_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION )->second;

  line_energy_reaction = std::dynamic_pointer_cast<const MonteCarlo::LineEnergyAdjointPhotoatomicReaction>( reaction );

  FRENSIE_CHECK_EQUAL( line_energy_reaction->getMinOutgoingEnergy(),
                       4*Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( line_energy_reaction->getMaxOutgoingEnergy(), 10.0 );
}

//---------------------------------------------------------------------------//
// Check that an adjoint photoatom core can be constructed
FRENSIE_UNIT_TEST( AdjointPhotoatomNativeFactory,
                   createAdjointPhotoatom_no_tp )
{
  std::shared_ptr<const MonteCarlo::AdjointPhotoatom> adjoint_photoatom;

  MonteCarlo::SimulationProperties properties;

  {
    std::vector<double> user_critical_line_energies( 1 );
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
  FRENSIE_CHECK_EQUAL( adjoint_photoatom->getAtomName(), "test_aepr_14" );

  // Check that the atomic number is correct
  FRENSIE_CHECK_EQUAL( adjoint_photoatom->getAtomicNumber(), 14 );

  // Check that the atomic weight is correct
  FRENSIE_CHECK_EQUAL( adjoint_photoatom->getAtomicWeight(), 14.0 );

  const MonteCarlo::AdjointPhotoatomCore& core =
    adjoint_photoatom->getCore();

  // Check that the grid searcher was constructed correctly
  FRENSIE_CHECK( !core.getGridSearcher().isValueWithinGridBounds( 9.9e-4 ) );
  FRENSIE_CHECK( core.getGridSearcher().isValueWithinGridBounds( 1e-3 ) );
  FRENSIE_CHECK( core.getGridSearcher().isValueWithinGridBounds( 1.5 ) );
  FRENSIE_CHECK( !core.getGridSearcher().isValueWithinGridBounds( 1.6 ) );
  FRENSIE_CHECK( core.hasSharedEnergyGrid() );

  // Check that the critical line energies were constructed correctly
  FRENSIE_CHECK_EQUAL( core.getCriticalLineEnergies().size(), 2 );
  FRENSIE_CHECK_EQUAL( core.getCriticalLineEnergies()[0],
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( core.getCriticalLineEnergies()[1],
                       1.5 );

  // Check that the total forward reaction was constructed correctly
  FRENSIE_CHECK_EQUAL( core.getTotalForwardReaction().getThresholdEnergy(),
                       1e-3 );
  FRENSIE_CHECK( core.getTotalForwardReaction().getCrossSection( 1.5 ) > 0.0 );

  // Check that the scattering reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    scattering_reactions = core.getScatteringReactions();

  FRENSIE_CHECK_EQUAL( scattering_reactions.size(), 2 );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );

  std::shared_ptr<const MonteCarlo::AdjointPhotoatomicReaction> reaction =
    scattering_reactions.find( MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION )->second;

  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-3 );
  FRENSIE_CHECK_EQUAL( reaction->getMaxEnergy(), 1.5 );

  std::shared_ptr<const MonteCarlo::IncoherentAdjointPhotoatomicReaction<Utility::LinLin,false> > incoherent_reaction =
    std::dynamic_pointer_cast<const MonteCarlo::IncoherentAdjointPhotoatomicReaction<Utility::LinLin,false> >( reaction );

  FRENSIE_CHECK_EQUAL( incoherent_reaction->getCriticalLineEnergies(),
                       core.getCriticalLineEnergies() );

  reaction = scattering_reactions.find( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION )->second;

  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-3 );
  FRENSIE_CHECK_EQUAL( reaction->getMaxEnergy(), 1.5 );

  // Check that the absorption reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    absorption_reactions = core.getAbsorptionReactions();

  FRENSIE_CHECK_EQUAL( absorption_reactions.size(), 0 );

  // Check that the line energy reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstLineEnergyReactionMap&
    line_energy_reactions = core.getLineEnergyReactions();

  FRENSIE_CHECK_EQUAL( line_energy_reactions.size(), 1 );
  FRENSIE_CHECK( line_energy_reactions.count( Utility::PhysicalConstants::electron_rest_mass_energy ) );

  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    me_line_energy_reactions = line_energy_reactions.find( Utility::PhysicalConstants::electron_rest_mass_energy )->second;

  FRENSIE_CHECK_EQUAL( me_line_energy_reactions.size(), 1 );
  FRENSIE_CHECK( me_line_energy_reactions.count( MonteCarlo::PAIR_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( !me_line_energy_reactions.count( MonteCarlo::TRIPLET_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION ) );

  reaction = me_line_energy_reactions.find( MonteCarlo::PAIR_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION )->second;

  std::shared_ptr<const MonteCarlo::LineEnergyAdjointPhotoatomicReaction>
    line_energy_reaction = std::dynamic_pointer_cast<const MonteCarlo::LineEnergyAdjointPhotoatomicReaction>( reaction );

  FRENSIE_CHECK_EQUAL( line_energy_reaction->getMinOutgoingEnergy(),
                       2*Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( line_energy_reaction->getMaxOutgoingEnergy(), 1.5 );
}

//---------------------------------------------------------------------------//
// Chck that an adjoint photoatom core can be constructed
FRENSIE_UNIT_TEST( AdjointPhotoatomNativeFactory,
                   createAdjointPhotoatom_no_pp )
{
  std::shared_ptr<const MonteCarlo::AdjointPhotoatom> adjoint_photoatom;

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
  FRENSIE_CHECK_EQUAL( adjoint_photoatom->getAtomName(), "test_aepr_14" );

  // Check that the atomic number is correct
  FRENSIE_CHECK_EQUAL( adjoint_photoatom->getAtomicNumber(), 14 );

  // Check that the atomic weight is correct
  FRENSIE_CHECK_EQUAL( adjoint_photoatom->getAtomicWeight(), 14.0 );

  const MonteCarlo::AdjointPhotoatomCore& core =
    adjoint_photoatom->getCore();

  // Check that the grid searcher was constructed correctly
  FRENSIE_CHECK( !core.getGridSearcher().isValueWithinGridBounds( 9.9e-4 ) );
  FRENSIE_CHECK( core.getGridSearcher().isValueWithinGridBounds( 1e-3 ) );
  FRENSIE_CHECK( core.getGridSearcher().isValueWithinGridBounds( 1.0 ) );
  FRENSIE_CHECK( !core.getGridSearcher().isValueWithinGridBounds( 1.1 ) );
  FRENSIE_CHECK( core.hasSharedEnergyGrid() );

  // Check that the critical line energies were constructed correctly
  FRENSIE_CHECK_EQUAL( core.getCriticalLineEnergies().size(), 0 );

  // Check that the total forward reaction was constructed correctly
  FRENSIE_CHECK_EQUAL( core.getTotalForwardReaction().getThresholdEnergy(),
                       1e-3 );
  FRENSIE_CHECK( core.getTotalForwardReaction().getCrossSection( 1.0 ) > 0.0 );

  // Check that the scattering reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    scattering_reactions = core.getScatteringReactions();

  FRENSIE_CHECK_EQUAL( scattering_reactions.size(), 2 );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );

  std::shared_ptr<const MonteCarlo::AdjointPhotoatomicReaction> reaction =
    scattering_reactions.find( MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION )->second;

  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-3 );
  FRENSIE_CHECK_EQUAL( reaction->getMaxEnergy(), 1.0 );

  std::shared_ptr<const MonteCarlo::IncoherentAdjointPhotoatomicReaction<Utility::LinLin,false> > incoherent_reaction =
    std::dynamic_pointer_cast<const MonteCarlo::IncoherentAdjointPhotoatomicReaction<Utility::LinLin,false> >( reaction );

  FRENSIE_CHECK_EQUAL( incoherent_reaction->getCriticalLineEnergies().size(), 1 );
  FRENSIE_CHECK_EQUAL( incoherent_reaction->getCriticalLineEnergies()[0], 0.0 );

  reaction = scattering_reactions.find( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION )->second;

  FRENSIE_CHECK_EQUAL( reaction->getThresholdEnergy(), 1e-3 );
  FRENSIE_CHECK_EQUAL( reaction->getMaxEnergy(), 1.0 );

  // Check that the absorption reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    absorption_reactions = core.getAbsorptionReactions();

  FRENSIE_CHECK_EQUAL( absorption_reactions.size(), 0 );

  // Check that the line energy reactions were constructed correctly
  const MonteCarlo::AdjointPhotoatomCore::ConstLineEnergyReactionMap&
    line_energy_reactions = core.getLineEnergyReactions();

  FRENSIE_CHECK_EQUAL( line_energy_reactions.size(), 0 );
}

//---------------------------------------------------------------------------//
// Custom Setup
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
  // Create the native data file container
  data_container.reset( new Data::AdjointElectronPhotonRelaxationDataContainer(
                                                     test_native_file_name ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstAdjointPhotoatomNativeFactory.cpp
//---------------------------------------------------------------------------//
