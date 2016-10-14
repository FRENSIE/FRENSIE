//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointPhotoatomCore.cpp
//! \author Alex Robinson
//! \brief  Adjoint photoatom core unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotoatomCore.hpp"
#include "MonteCarlo_AdjointPhotoatomicReactionNativeFactory.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::AdjointPhotoatomCore> adjoint_photoatom_core;

//---------------------------------------------------------------------------//
// Check that the total forward reaction can be returned
TEUCHOS_UNIT_TEST( AdjointPhotoatomCore, getTotalForwardReaction )
{
  const MonteCarlo::PhotoatomicReaction& total_forward_reaction =
    adjoint_photoatom_core->getTotalForwardReaction();

  TEST_EQUALITY_CONST( total_forward_reaction.getReactionType(),
                       MonteCarlo::TOTAL_PHOTOATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( total_forward_reaction.getThresholdEnergy(),
                          1e-3,
                          1e-15 );

  double cross_section = total_forward_reaction.getCrossSection( 0.001 );

  TEST_FLOATING_EQUALITY( cross_section, 73136.5325778411352, 1e-12 );

  cross_section = total_forward_reaction.getCrossSection( 1.0 );
  
  TEST_FLOATING_EQUALITY( cross_section, 2.96240900282447228, 1e-12 );

  cross_section = total_forward_reaction.getCrossSection( 20.0 );
  
  TEST_FLOATING_EQUALITY( cross_section, 1.08806003440055754, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the scattering reactions can be returned
TEUCHOS_UNIT_TEST( AdjointPhotoatomCore, getScatteringReactions )
{
  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    scattering_reactions = adjoint_photoatom_core->getScatteringReactions();

  TEST_EQUALITY_CONST( scattering_reactions.size(), 2 );
  TEST_ASSERT( scattering_reactions.count( MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( scattering_reactions.count( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );

  const MonteCarlo::AdjointPhotoatomicReaction& incoherent_reaction =
    *(scattering_reactions.find(MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION)->second);

  double cross_section = incoherent_reaction.getCrossSection( 1e-3 );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.620920802623559753, 1e-12 );

  cross_section = incoherent_reaction.getCrossSection( 1.0 );
  
  TEST_FLOATING_EQUALITY( cross_section, 5.50415974966055277, 1e-12 );

  cross_section = incoherent_reaction.getCrossSection( 20.0 );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  const MonteCarlo::AdjointPhotoatomicReaction& coherent_reaction =
    *(scattering_reactions.find(MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION)->second);

  cross_section = coherent_reaction.getCrossSection( 1e-3 );
  
  TEST_FLOATING_EQUALITY( cross_section, 99.9639104922271571, 1e-12 );

  cross_section = coherent_reaction.getCrossSection( 1.0 );

  TEST_FLOATING_EQUALITY( cross_section, 0.00783640704399895215, 1e-12 );

  cross_section = coherent_reaction.getCrossSection( 20.0 );

  TEST_FLOATING_EQUALITY( cross_section, 1.96243862843467646e-05, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the absorption reactions can be returned
TEUCHOS_UNIT_TEST( AdjointPhotoatomCore, getAbsorptionReactions )
{
  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    absorption_reactions = adjoint_photoatom_core->getAbsorptionReactions();

  TEST_EQUALITY_CONST( absorption_reactions.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the line energy reactions can be returned
TEUCHOS_UNIT_TEST( AdjointPhotoatomCore, getLineEnergyReactions )
{
  const MonteCarlo::AdjointPhotoatomCore::ConstLineEnergyReactionMap&
    line_energy_reactions = adjoint_photoatom_core->getLineEnergyReactions();

  TEST_EQUALITY_CONST( line_energy_reactions.size(), 1 );
  TEST_ASSERT( line_energy_reactions.count( Utility::PhysicalConstants::electron_rest_mass_energy ) );

  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    me_line_energy_reactions = line_energy_reactions.find(
               Utility::PhysicalConstants::electron_rest_mass_energy )->second;

  TEST_EQUALITY_CONST( me_line_energy_reactions.size(), 2 );
  TEST_ASSERT( me_line_energy_reactions.count( MonteCarlo::PAIR_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( me_line_energy_reactions.count( MonteCarlo::TRIPLET_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION ) );
  
  const MonteCarlo::AdjointPhotoatomicReaction& pp_reaction =
    *(me_line_energy_reactions.find( MonteCarlo::PAIR_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION )->second );

  TEST_FLOATING_EQUALITY( pp_reaction.getCrossSection( Utility::PhysicalConstants::electron_rest_mass_energy ),
                          7.36968106381629173,
                          1e-12 );

  const MonteCarlo::AdjointPhotoatomicReaction& tp_reaction =
    *(me_line_energy_reactions.find( MonteCarlo::TRIPLET_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION )->second );
  
  TEST_FLOATING_EQUALITY( tp_reaction.getCrossSection( Utility::PhysicalConstants::electron_rest_mass_energy ),
                          0.311089687386319702,
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the grid searcher can be returned
TEUCHOS_UNIT_TEST( AdjointPhotoatomCore, getGridSearcher )
{
  const Utility::HashBasedGridSearcher& grid_searcher =
    adjoint_photoatom_core->getGridSearcher();

  unsigned grid_index = grid_searcher.findLowerBinIndex( 1e-3 );

  TEST_EQUALITY_CONST( grid_index, 0u );

  grid_index = grid_searcher.findLowerBinIndex( 20.0 );

  TEST_EQUALITY_CONST( grid_index, 1166 );
}

//---------------------------------------------------------------------------//
// Check if all of the reactions share a common energy grid
TEUCHOS_UNIT_TEST( AdjointPhotoatomCore, hasSharedEnergyGrid )
{
  TEST_ASSERT( adjoint_photoatom_core->hasSharedEnergyGrid() );
}

//---------------------------------------------------------------------------//
// Check the copy constructor
TEUCHOS_UNIT_TEST( AdjointPhotoatomCore, copy_constructor )
{
  MonteCarlo::AdjointPhotoatomCore core_copy( *adjoint_photoatom_core );

  const MonteCarlo::PhotoatomicReaction& total_forward_reaction =
    core_copy.getTotalForwardReaction();

  TEST_EQUALITY_CONST( total_forward_reaction.getReactionType(),
                       MonteCarlo::TOTAL_PHOTOATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( total_forward_reaction.getThresholdEnergy(),
                          1e-3,
                          1e-15 );

  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    scattering_reactions = core_copy.getScatteringReactions();

  TEST_EQUALITY_CONST( scattering_reactions.size(), 2 );
  TEST_ASSERT( scattering_reactions.count( MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( scattering_reactions.count( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );

  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    absorption_reactions = core_copy.getAbsorptionReactions();

  TEST_EQUALITY_CONST( absorption_reactions.size(), 0 );

  const MonteCarlo::AdjointPhotoatomCore::ConstLineEnergyReactionMap&
    line_energy_reactions = core_copy.getLineEnergyReactions();

  TEST_EQUALITY_CONST( line_energy_reactions.size(), 1 );
  TEST_ASSERT( line_energy_reactions.count( Utility::PhysicalConstants::electron_rest_mass_energy ) );

  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    me_line_energy_reactions = line_energy_reactions.find(
               Utility::PhysicalConstants::electron_rest_mass_energy )->second;

  TEST_EQUALITY_CONST( me_line_energy_reactions.size(), 2 );
  TEST_ASSERT( me_line_energy_reactions.count( MonteCarlo::PAIR_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( me_line_energy_reactions.count( MonteCarlo::TRIPLET_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION ) );
}

//---------------------------------------------------------------------------//
// Check the assignment operator
TEUCHOS_UNIT_TEST( AdjointPhotoatomCore, assignment_operator )
{
  MonteCarlo::AdjointPhotoatomCore core_copy = *adjoint_photoatom_core;

  const MonteCarlo::PhotoatomicReaction& total_forward_reaction =
    core_copy.getTotalForwardReaction();

  TEST_EQUALITY_CONST( total_forward_reaction.getReactionType(),
                       MonteCarlo::TOTAL_PHOTOATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( total_forward_reaction.getThresholdEnergy(),
                          1e-3,
                          1e-15 );

  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    scattering_reactions = core_copy.getScatteringReactions();

  TEST_EQUALITY_CONST( scattering_reactions.size(), 2 );
  TEST_ASSERT( scattering_reactions.count( MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( scattering_reactions.count( MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION ) );

  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    absorption_reactions = core_copy.getAbsorptionReactions();

  TEST_EQUALITY_CONST( absorption_reactions.size(), 0 );

  const MonteCarlo::AdjointPhotoatomCore::ConstLineEnergyReactionMap&
    line_energy_reactions = core_copy.getLineEnergyReactions();

  TEST_EQUALITY_CONST( line_energy_reactions.size(), 1 );
  TEST_ASSERT( line_energy_reactions.count( Utility::PhysicalConstants::electron_rest_mass_energy ) );

  const MonteCarlo::AdjointPhotoatomCore::ConstReactionMap&
    me_line_energy_reactions = line_energy_reactions.find(
               Utility::PhysicalConstants::electron_rest_mass_energy )->second;

  TEST_EQUALITY_CONST( me_line_energy_reactions.size(), 2 );
  TEST_ASSERT( me_line_energy_reactions.count( MonteCarlo::PAIR_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION ) );
  TEST_ASSERT( me_line_energy_reactions.count( MonteCarlo::TRIPLET_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION ) );
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
  Data::AdjointElectronPhotonRelaxationDataContainer
    data_container( test_native_file_name );

  // Create the union energy grid
  Teuchos::ArrayRCP<double> energy_grid;

  MonteCarlo::AdjointPhotoatomicReactionNativeFactory::createUnionEnergyGrid(
                                                                data_container,
                                                                energy_grid,
                                                                20.0 );

  // Create the hash based grid searcher
  Teuchos::RCP<const Utility::HashBasedGridSearcher> grid_searcher(
   new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<double>,false>(
                                                                   energy_grid,
                                                                   100 ) );

  // Create the total forward reaction
  std::shared_ptr<MonteCarlo::PhotoatomicReaction> total_forward_reaction;

  MonteCarlo::AdjointPhotoatomicReactionNativeFactory::createTotalForwardReaction(
                                       data_container,
                                       energy_grid,
                                       grid_searcher,
                                       MonteCarlo::WH_INCOHERENT_ADJOINT_MODEL,
                                       total_forward_reaction );

  // Create the scattering reactions
  MonteCarlo::AdjointPhotoatomCore::ReactionMap scattering_reactions;

  {
    Teuchos::ArrayRCP<double> critical_line_energies( 2 );
    critical_line_energies[0] =
      Utility::PhysicalConstants::electron_rest_mass_energy;
    critical_line_energies[1] = 20.0;
    
    std::vector<std::shared_ptr<MonteCarlo::AdjointPhotoatomicReaction> >
      incoherent_reactions;

    MonteCarlo::AdjointPhotoatomicReactionNativeFactory::createIncoherentReactions(
                                       data_container,
                                       energy_grid,
                                       grid_searcher,
                                       incoherent_reactions,
                                       MonteCarlo::WH_INCOHERENT_ADJOINT_MODEL,
                                       critical_line_energies );

    scattering_reactions[incoherent_reactions[0]->getReactionType()] =
      incoherent_reactions[0];
  }

  {
    std::shared_ptr<MonteCarlo::AdjointPhotoatomicReaction> coherent_reaction;

    MonteCarlo::AdjointPhotoatomicReactionNativeFactory::createCoherentReaction(
                                                           data_container,
                                                           energy_grid,
                                                           grid_searcher,
                                                           coherent_reaction );

    scattering_reactions[coherent_reaction->getReactionType()] =
      coherent_reaction;
  }

  // Create the line energy reactions
  MonteCarlo::AdjointPhotoatomCore::LineEnergyReactionMap
    line_energy_reactions;

  {
    MonteCarlo::AdjointPhotoatomCore::ReactionMap& me_line_energy_reactions =
      line_energy_reactions[Utility::PhysicalConstants::electron_rest_mass_energy];
    
    std::shared_ptr<MonteCarlo::LineEnergyAdjointPhotoatomicReaction> reaction;

    MonteCarlo::AdjointPhotoatomicReactionNativeFactory::createPairProductionReaction(
                                                                data_container,
                                                                energy_grid,
                                                                grid_searcher,
                                                                reaction );

    me_line_energy_reactions[reaction->getReactionType()] = reaction;

    MonteCarlo::AdjointPhotoatomicReactionNativeFactory::createTripletProductionReaction(
                                                                data_container,
                                                                energy_grid,
                                                                grid_searcher,
                                                                reaction );

    me_line_energy_reactions[reaction->getReactionType()] = reaction;
  }

  // Construct the core
  adjoint_photoatom_core.reset(
           new MonteCarlo::AdjointPhotoatomCore(
                               grid_searcher,
                               total_forward_reaction,
                               scattering_reactions,
                               MonteCarlo::AdjointPhotoatomCore::ReactionMap(),
                               line_energy_reactions ) );
                                                         
    
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstAdjointPhotoatomCore.cpp
//---------------------------------------------------------------------------//
