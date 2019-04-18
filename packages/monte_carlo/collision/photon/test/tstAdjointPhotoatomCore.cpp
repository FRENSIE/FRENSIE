//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointPhotoatomCore.cpp
//! \author Alex Robinson
//! \brief  Adjoint photoatom core unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotoatomCore.hpp"
#include "MonteCarlo_AdjointPhotoatomicReactionNativeFactory.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::AdjointPhotoatomCore> adjoint_photoatom_core;

//---------------------------------------------------------------------------//
// Check that the total forward reaction can be returned
FRENSIE_UNIT_TEST( AdjointPhotoatomCore, getTotalForwardReaction )
{
  const MonteCarlo::PhotoatomicReaction& total_forward_reaction =
    adjoint_photoatom_core->getTotalForwardReaction();

  FRENSIE_CHECK_EQUAL( total_forward_reaction.getReactionType(),
                       MonteCarlo::TOTAL_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_forward_reaction.getThresholdEnergy(),
                                   1e-3,
                                   1e-15 );

  double cross_section = total_forward_reaction.getCrossSection( 0.001 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 73136.5325778411352, 1e-12 );

  cross_section = total_forward_reaction.getCrossSection( 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.96240900282447228, 1e-12 );

  cross_section = total_forward_reaction.getCrossSection( 20.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.08806003440055754, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the scattering reactions can be returned
FRENSIE_UNIT_TEST( AdjointPhotoatomCore, getScatteringReactions )
{
  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    scattering_reactions = adjoint_photoatom_core->getScatteringReactions();

  FRENSIE_CHECK_EQUAL( scattering_reactions.size(), 2 );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );

  const MonteCarlo::AdjointPhotoatomicReaction& incoherent_reaction =
    *(scattering_reactions.find(MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION)->second);

  double cross_section = incoherent_reaction.getCrossSection( 1e-3 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.620920802623559753, 1e-12 );

  cross_section = incoherent_reaction.getCrossSection( 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 5.50415974966055277, 1e-12 );

  cross_section = incoherent_reaction.getCrossSection( 20.0 );

  FRENSIE_CHECK_SMALL( cross_section, 1e-12 );

  const MonteCarlo::AdjointPhotoatomicReaction& coherent_reaction =
    *(scattering_reactions.find(MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION)->second);

  cross_section = coherent_reaction.getCrossSection( 1e-3 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 99.9639104922271571, 1e-12 );

  cross_section = coherent_reaction.getCrossSection( 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.00783640704399895215, 1e-12 );

  cross_section = coherent_reaction.getCrossSection( 20.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.96243862843467646e-05, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the scattering reaction types can be returned
FRENSIE_UNIT_TEST( AdjointPhotoatomCore, getScatteringReactionTypes )
{
  MonteCarlo::AdjointPhotoatomCore::ReactionEnumTypeSet reaction_types;

  adjoint_photoatom_core->getScatteringReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 2 );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
}

//---------------------------------------------------------------------------//
// Check that the absorption reactions can be returned
FRENSIE_UNIT_TEST( AdjointPhotoatomCore, getAbsorptionReactions )
{
  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    absorption_reactions = adjoint_photoatom_core->getAbsorptionReactions();

  FRENSIE_CHECK_EQUAL( absorption_reactions.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the absorption reaction types can be returned
FRENSIE_UNIT_TEST( AdjointPhotoatomCore, getAbsorptionReactionTypes )
{
  MonteCarlo::AdjointPhotoatomCore::ReactionEnumTypeSet reaction_types;

  adjoint_photoatom_core->getAbsorptionReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the miscellaneous reactions can be returned
FRENSIE_UNIT_TEST( AdjointPhotoatomCore, getMiscReactions )
{
  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    misc_reactions = adjoint_photoatom_core->getMiscReactions();

  FRENSIE_CHECK_EQUAL( misc_reactions.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the miscellaneous reaction types can be returned
FRENSIE_UNIT_TEST( AdjointPhotoatomCore, getMiscReactionTypes )
{
  MonteCarlo::AdjointPhotoatomCore::ReactionEnumTypeSet reaction_types;

  adjoint_photoatom_core->getMiscReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the reaction types can be returned
FRENSIE_UNIT_TEST( AdjointPhotoatomCore, getReactionTypes )
{
  MonteCarlo::AdjointPhotoatomCore::ReactionEnumTypeSet reaction_types;

  adjoint_photoatom_core->getReactionTypes( reaction_types );

  FRENSIE_CHECK_EQUAL( reaction_types.size(), 3 );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::TOTAL_ADJOINT_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( reaction_types.count( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
}

//---------------------------------------------------------------------------//
// Check that the line energy reactions can be returned
FRENSIE_UNIT_TEST( AdjointPhotoatomCore, getLineEnergyReactions )
{
  const MonteCarlo::AdjointPhotoatomCore::ConstLineEnergyReactionMap&
    line_energy_reactions = adjoint_photoatom_core->getLineEnergyReactions();

  FRENSIE_CHECK_EQUAL( line_energy_reactions.size(), 1 );
  FRENSIE_CHECK( line_energy_reactions.count( Utility::PhysicalConstants::electron_rest_mass_energy ) );

  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    me_line_energy_reactions = line_energy_reactions.find(
               Utility::PhysicalConstants::electron_rest_mass_energy )->second;

  FRENSIE_CHECK_EQUAL( me_line_energy_reactions.size(), 2 );
  FRENSIE_CHECK( me_line_energy_reactions.count( MonteCarlo::PAIR_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( me_line_energy_reactions.count( MonteCarlo::TRIPLET_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION ) );

  const MonteCarlo::AdjointPhotoatomicReaction& pp_reaction =
    *(me_line_energy_reactions.find( MonteCarlo::PAIR_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION )->second );

  FRENSIE_CHECK_FLOATING_EQUALITY( pp_reaction.getCrossSection( Utility::PhysicalConstants::electron_rest_mass_energy ),
                          14.739362127632583,
                          1e-12 );

  const MonteCarlo::AdjointPhotoatomicReaction& tp_reaction =
    *(me_line_energy_reactions.find( MonteCarlo::TRIPLET_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION )->second );

  FRENSIE_CHECK_FLOATING_EQUALITY( tp_reaction.getCrossSection( Utility::PhysicalConstants::electron_rest_mass_energy ),
                          0.6221793747726394,
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the critical line energies can be returned
FRENSIE_UNIT_TEST( AdjointPhotoatomCore, getCriticalLineEnergies )
{
  const std::vector<double>& line_energies =
    adjoint_photoatom_core->getCriticalLineEnergies();

  FRENSIE_REQUIRE_EQUAL( line_energies.size(), 2 );
  FRENSIE_CHECK_EQUAL( line_energies[0],
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_EQUAL( line_energies[1], 20.0 );
}

//---------------------------------------------------------------------------//
// Check that the grid searcher can be returned
FRENSIE_UNIT_TEST( AdjointPhotoatomCore, getGridSearcher )
{
  const Utility::HashBasedGridSearcher<double>& grid_searcher =
    adjoint_photoatom_core->getGridSearcher();

  size_t grid_index = grid_searcher.findLowerBinIndex( 1e-3 );

  FRENSIE_CHECK_EQUAL( grid_index, 0u );

  grid_index = grid_searcher.findLowerBinIndex( 20.0 );

  FRENSIE_CHECK_EQUAL( grid_index, 1261 );
}

//---------------------------------------------------------------------------//
// Check if all of the reactions share a common energy grid
FRENSIE_UNIT_TEST( AdjointPhotoatomCore, hasSharedEnergyGrid )
{
  FRENSIE_CHECK( adjoint_photoatom_core->hasSharedEnergyGrid() );
}

//---------------------------------------------------------------------------//
// Check the copy constructor
FRENSIE_UNIT_TEST( AdjointPhotoatomCore, copy_constructor )
{
  MonteCarlo::AdjointPhotoatomCore core_copy( *adjoint_photoatom_core );

  FRENSIE_CHECK_EQUAL( adjoint_photoatom_core->getCriticalLineEnergies(),
                       core_copy.getCriticalLineEnergies() );

  const MonteCarlo::PhotoatomicReaction& total_forward_reaction =
    core_copy.getTotalForwardReaction();

  FRENSIE_CHECK_EQUAL( total_forward_reaction.getReactionType(),
                       MonteCarlo::TOTAL_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_forward_reaction.getThresholdEnergy(),
                          1e-3,
                          1e-15 );

  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    scattering_reactions = core_copy.getScatteringReactions();

  FRENSIE_CHECK_EQUAL( scattering_reactions.size(), 2 );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );

  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    absorption_reactions = core_copy.getAbsorptionReactions();

  FRENSIE_CHECK_EQUAL( absorption_reactions.size(), 0 );

  const MonteCarlo::AdjointPhotoatomCore::ConstLineEnergyReactionMap&
    line_energy_reactions = core_copy.getLineEnergyReactions();

  FRENSIE_CHECK_EQUAL( line_energy_reactions.size(), 1 );
  FRENSIE_CHECK( line_energy_reactions.count( Utility::PhysicalConstants::electron_rest_mass_energy ) );

  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    me_line_energy_reactions = line_energy_reactions.find(
               Utility::PhysicalConstants::electron_rest_mass_energy )->second;

  FRENSIE_CHECK_EQUAL( me_line_energy_reactions.size(), 2 );
  FRENSIE_CHECK( me_line_energy_reactions.count( MonteCarlo::PAIR_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( me_line_energy_reactions.count( MonteCarlo::TRIPLET_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION ) );
}

//---------------------------------------------------------------------------//
// Check the assignment operator
FRENSIE_UNIT_TEST( AdjointPhotoatomCore, assignment_operator )
{
  MonteCarlo::AdjointPhotoatomCore core_copy = *adjoint_photoatom_core;

  const MonteCarlo::PhotoatomicReaction& total_forward_reaction =
    core_copy.getTotalForwardReaction();

  FRENSIE_CHECK_EQUAL( total_forward_reaction.getReactionType(),
                       MonteCarlo::TOTAL_PHOTOATOMIC_REACTION );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_forward_reaction.getThresholdEnergy(),
                          1e-3,
                          1e-15 );

  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    scattering_reactions = core_copy.getScatteringReactions();

  FRENSIE_CHECK_EQUAL( scattering_reactions.size(), 2 );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( scattering_reactions.count( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );

  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    absorption_reactions = core_copy.getAbsorptionReactions();

  FRENSIE_CHECK_EQUAL( absorption_reactions.size(), 0 );

  const MonteCarlo::AdjointPhotoatomCore::ConstLineEnergyReactionMap&
    line_energy_reactions = core_copy.getLineEnergyReactions();

  FRENSIE_CHECK_EQUAL( line_energy_reactions.size(), 1 );
  FRENSIE_CHECK( line_energy_reactions.count( Utility::PhysicalConstants::electron_rest_mass_energy ) );

  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    me_line_energy_reactions = line_energy_reactions.find(
               Utility::PhysicalConstants::electron_rest_mass_energy )->second;

  FRENSIE_CHECK_EQUAL( me_line_energy_reactions.size(), 2 );
  FRENSIE_CHECK( me_line_energy_reactions.count( MonteCarlo::PAIR_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION ) );
  FRENSIE_CHECK( me_line_energy_reactions.count( MonteCarlo::TRIPLET_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION ) );
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
  Data::AdjointElectronPhotonRelaxationDataContainer
    data_container( test_native_file_name );

  // Create the union energy grid
  std::shared_ptr<std::vector<double> > energy_grid( new std::vector<double> );

  MonteCarlo::AdjointPhotoatomicReactionNativeFactory::createUnionEnergyGrid(
                                                                data_container,
                                                                *energy_grid,
                                                                20.0 );

  // Create the hash based grid searcher
  std::shared_ptr<const Utility::HashBasedGridSearcher<double> > grid_searcher(
   new Utility::StandardHashBasedGridSearcher<std::vector<double>,false>(
                                                                   energy_grid,
                                                                   100 ) );

  // Create the total forward reaction
  std::shared_ptr<const MonteCarlo::PhotoatomicReaction> total_forward_reaction;

  MonteCarlo::AdjointPhotoatomicReactionNativeFactory::createTotalForwardReaction(
                                       data_container,
                                       energy_grid,
                                       grid_searcher,
                                       MonteCarlo::WH_INCOHERENT_ADJOINT_MODEL,
                                       total_forward_reaction );

  // Create the scattering reactions
  MonteCarlo::AdjointPhotoatomCore::ConstReactionMap scattering_reactions;

  std::shared_ptr<std::vector<double> >
    critical_line_energies( new std::vector<double>(2) );
  (*critical_line_energies)[0] =
    Utility::PhysicalConstants::electron_rest_mass_energy;
  (*critical_line_energies)[1] = 20.0;

  {
    std::vector<std::shared_ptr<const MonteCarlo::AdjointPhotoatomicReaction> >
      incoherent_reactions;

    MonteCarlo::AdjointPhotoatomicReactionNativeFactory::createIncoherentReactions(
                    data_container,
                    energy_grid,
                    grid_searcher,
                    incoherent_reactions,
                    MonteCarlo::WH_INCOHERENT_ADJOINT_MODEL,
                    MonteCarlo::THREE_BRANCH_INVERSE_MIXED_ADJOINT_KN_SAMPLING,
                    critical_line_energies );

    scattering_reactions[incoherent_reactions[0]->getReactionType()] =
      incoherent_reactions[0];
  }

  {
    std::shared_ptr<const MonteCarlo::AdjointPhotoatomicReaction> coherent_reaction;

    MonteCarlo::AdjointPhotoatomicReactionNativeFactory::createCoherentReaction(
                                                           data_container,
                                                           energy_grid,
                                                           grid_searcher,
                                                           coherent_reaction );

    scattering_reactions[coherent_reaction->getReactionType()] =
      coherent_reaction;
  }

  // Create the line energy reactions
  MonteCarlo::AdjointPhotoatomCore::ConstLineEnergyReactionMap
    line_energy_reactions;

  {
    MonteCarlo::AdjointPhotoatomCore::ConstReactionMap& me_line_energy_reactions =
      line_energy_reactions[Utility::PhysicalConstants::electron_rest_mass_energy];

    std::shared_ptr<const MonteCarlo::LineEnergyAdjointPhotoatomicReaction> reaction;

    MonteCarlo::AdjointPhotoatomicReactionNativeFactory::createPairProductionReaction(
                                                                data_container,
                                                                energy_grid,
                                                                grid_searcher,
                                                                reaction,
                                                                critical_line_energies );

    me_line_energy_reactions[reaction->getReactionType()] = reaction;

    MonteCarlo::AdjointPhotoatomicReactionNativeFactory::createTripletProductionReaction(
                                                                data_container,
                                                                energy_grid,
                                                                grid_searcher,
                                                                reaction,
                                                                critical_line_energies );

    me_line_energy_reactions[reaction->getReactionType()] = reaction;
  }

  // Construct the core
  adjoint_photoatom_core.reset(
           new MonteCarlo::AdjointPhotoatomCore(
                          energy_grid,
                          grid_searcher,
                          critical_line_energies,
                          total_forward_reaction,
                          scattering_reactions,
                          MonteCarlo::AdjointPhotoatomCore::ConstReactionMap(),
                          line_energy_reactions,
                          false,
                          Utility::LinLin() ) );


  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstAdjointPhotoatomCore.cpp
//---------------------------------------------------------------------------//
