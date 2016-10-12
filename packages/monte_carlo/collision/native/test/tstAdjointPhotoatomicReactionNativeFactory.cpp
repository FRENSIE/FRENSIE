//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointPhotoatomicReactionNativeFactory.cpp
//! \author Alex Robinson
//! \brief  Adjoint photoatomic reaction native factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotoatomicReactionNativeFactory.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<Data::AdjointElectronPhotonRelaxationDataContainer> data_container;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a union energy grid can be created
TEUCHOS_UNIT_TEST( AdjointPhotoatomicReactionNativeFactory,
                   createUnionEnergyGrid )
{
  Teuchos::ArrayRCP<double> energy_grid;

  MonteCarlo::AdjointPhotoatomicReactionNativeFactory::createUnionEnergyGrid(
                                                               *data_container,
                                                               energy_grid,
                                                               1.0 );

  TEST_EQUALITY_CONST( energy_grid[0], 1e-3 );
  TEST_EQUALITY_CONST( energy_grid[energy_grid.size()-1], 1.0 );
  TEST_ASSERT( Utility::Sort::isSortedAscending( energy_grid.begin(),
                                                 energy_grid.end() ) );

  MonteCarlo::AdjointPhotoatomicReactionNativeFactory::createUnionEnergyGrid(
                                                               *data_container,
                                                               energy_grid,
                                                               10.0 );

  TEST_EQUALITY_CONST( energy_grid[0], 1e-3 );
  TEST_EQUALITY_CONST( energy_grid[energy_grid.size()-1], 10.0 );
  TEST_ASSERT( Utility::Sort::isSortedAscending( energy_grid.begin(),
                                                 energy_grid.end() ) );

  MonteCarlo::AdjointPhotoatomicReactionNativeFactory::createUnionEnergyGrid(
                                                               *data_container,
                                                               energy_grid,
                                                               20.0 );

  TEST_EQUALITY_CONST( energy_grid[0], 1e-3 );
  TEST_EQUALITY_CONST( energy_grid[energy_grid.size()-1], 20.0 );
  TEST_ASSERT( Utility::Sort::isSortedAscending( energy_grid.begin(),
                                                 energy_grid.end() ) );
}

//---------------------------------------------------------------------------//
// Check that an incoherent adjoint reaction can be created
TEUCHOS_UNIT_TEST( AdjointPhotoatomicReactionNativeFactory,
                   createIncoherentReactions )
{
  // Create the union energy grid
  Teuchos::ArrayRCP<double> energy_grid;

  MonteCarlo::AdjointPhotoatomicReactionNativeFactory::createUnionEnergyGrid(
                                                               *data_container,
                                                               energy_grid,
                                                               10.0 );
  // Create the hash based grid searcher
  Teuchos::RCP<const Utility::HashBasedGridSearcher> grid_searcher(
   new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<double>,false>(
                                                                   energy_grid,
                                                                   100 ) );

  // Create the Waller-Hartree incoherent adjoint reaction
  Teuchos::ArrayRCP<double> critical_line_energies( 2 );
  critical_line_energies[0] =
    Utility::PhysicalConstants::electron_rest_mass_energy;
  critical_line_energies[1] = 10.0;
  
  std::vector<std::shared_ptr<MonteCarlo::AdjointPhotoatomicReaction> >
    reactions;
  
  MonteCarlo::AdjointPhotoatomicReactionNativeFactory::createIncoherentReactions(
                                       *data_container,
                                       energy_grid,
                                       grid_searcher,
                                       reactions,
                                       MonteCarlo::WH_INCOHERENT_ADJOINT_MODEL,
                                       critical_line_energies );

  // Check that the reaction properties are correct
  TEST_EQUALITY_CONST( reactions.size(), 1 );
  TEST_EQUALITY_CONST( reactions[0]->getReactionType(),
                       MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  TEST_EQUALITY_CONST( reactions[0]->getMaxEnergy(), 10.0 );
  TEST_FLOATING_EQUALITY( reactions[0]->getThresholdEnergy(), 1e-3, 1e-15 );

  // Check that the stored cross section is correct
  double cross_section = reactions[0]->getCrossSection( 0.001 );

  TEST_FLOATING_EQUALITY( cross_section, 0.620920802623559753, 1e-12 );

  cross_section = reactions[0]->getCrossSection( 1.0 );
  
  TEST_FLOATING_EQUALITY( cross_section, 2.60724515922206379, 1e-12 );

  cross_section = reactions[0]->getCrossSection( 10.0 );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  // Check that the critical energies were assigned
  MonteCarlo::AdjointPhotonState adjoint_photon( 0 );
  adjoint_photon.setEnergy( 0.3 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType subshell;
  
  reactions[0]->react( adjoint_photon, bank, subshell );

  TEST_EQUALITY_CONST( bank.size(), 2 );
  TEST_EQUALITY_CONST( bank.top().getEnergy(),
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  bank.pop();
  TEST_EQUALITY_CONST( bank.top().getEnergy(), 10.0 );                       
}

//---------------------------------------------------------------------------//
// Check that subshell incoherent adjoint reactions can be created
TEUCHOS_UNIT_TEST( AdjointPhotoatomicReactionNativeFactory,
                   createIncoherentReactions_subshell )
{
  // Create the union energy grid
  Teuchos::ArrayRCP<double> energy_grid;

  MonteCarlo::AdjointPhotoatomicReactionNativeFactory::createUnionEnergyGrid(
                                                               *data_container,
                                                               energy_grid,
                                                               10.0 );
  // Create the hash based grid searcher
  Teuchos::RCP<const Utility::HashBasedGridSearcher> grid_searcher(
   new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<double>,false>(
                                                                   energy_grid,
                                                                   100 ) );

  // Create the impulse approx. incoherent adjoint reactions
  Teuchos::ArrayRCP<double> critical_line_energies( 1 );
  critical_line_energies[0] =
    Utility::PhysicalConstants::electron_rest_mass_energy;

  std::vector<std::shared_ptr<MonteCarlo::AdjointPhotoatomicReaction> >
    reactions;

  MonteCarlo::AdjointPhotoatomicReactionNativeFactory::createIncoherentReactions(
                                  *data_container,
                                  energy_grid,
                                  grid_searcher,
                                  reactions,
                                  MonteCarlo::IMPULSE_INCOHERENT_ADJOINT_MODEL,
                                  critical_line_energies );

  TEST_EQUALITY_CONST( reactions.size(), 7 );
  
  // Check that the first subshell reaction properties are correct
  TEST_EQUALITY_CONST( reactions.front()->getReactionType(),
                       MonteCarlo::K_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  TEST_EQUALITY_CONST( reactions.front()->getMaxEnergy(), 10.0 );
  TEST_FLOATING_EQUALITY( reactions.front()->getThresholdEnergy(), 1e-3, 1e-15 );

  double cross_section = reactions.front()->getCrossSection( 1e-3 );
  
  TEST_FLOATING_EQUALITY( cross_section, 1.70397435126473889e-05, 1e-12 );

  cross_section = reactions.front()->getCrossSection( 1.0 );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.341266992358144006, 1e-12 );

  cross_section = reactions.front()->getCrossSection( 10.0-1.8285e-3 );
  
  UTILITY_TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = reactions.front()->getCrossSection( 10.0 );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  MonteCarlo::AdjointPhotonState adjoint_photon( 0 );
  adjoint_photon.setEnergy( 0.3 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType subshell;
  
  reactions.front()->react( adjoint_photon, bank, subshell );

  TEST_EQUALITY_CONST( bank.size(), 1 );
  TEST_EQUALITY_CONST( bank.top().getEnergy(),
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  bank.pop();

  // Check that the last subshell reaction properties are correct
  TEST_EQUALITY_CONST( reactions.back()->getReactionType(),
                       MonteCarlo::M3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  TEST_EQUALITY_CONST( reactions.back()->getMaxEnergy(), 10.0 );
  TEST_FLOATING_EQUALITY( reactions.back()->getThresholdEnergy(), 1e-3, 1e-15 );

  cross_section = reactions.back()->getCrossSection( 1e-3 );

  TEST_FLOATING_EQUALITY( cross_section, 0.154116414030485815, 1e-12 );

  cross_section = reactions.back()->getCrossSection( 1.0 );

  TEST_FLOATING_EQUALITY( cross_section, 0.24537236048981062, 1e-12 );

  cross_section = reactions.back()->getCrossSection( 10.0-6.52e-6 );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = reactions.back()->getCrossSection( 10.0 );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  adjoint_photon.setEnergy( 0.3 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );

  reactions.back()->react( adjoint_photon, bank, subshell );

  TEST_EQUALITY_CONST( bank.size(), 1 );
  TEST_EQUALITY_CONST( bank.top().getEnergy(),
                       Utility::PhysicalConstants::electron_rest_mass_energy );
}

//---------------------------------------------------------------------------//
// Check that subshell incoherent adjoint reactions with Doppler broadening
// can be created
TEUCHOS_UNIT_TEST( AdjointPhotoatomicReactionNativeFactory,
                   createIncoherentReactions_subshell_dopp )
{
  // Create the union energy grid
  Teuchos::ArrayRCP<double> energy_grid;

  MonteCarlo::AdjointPhotoatomicReactionNativeFactory::createUnionEnergyGrid(
                                                               *data_container,
                                                               energy_grid,
                                                               1.0 );
  // Create the hash based grid searcher
  Teuchos::RCP<const Utility::HashBasedGridSearcher> grid_searcher(
   new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<double>,false>(
                                                                   energy_grid,
                                                                   100 ) );

  // Create the impulse approx. incoherent adjoint reactions
  Teuchos::ArrayRCP<double> critical_line_energies;

  std::vector<std::shared_ptr<MonteCarlo::AdjointPhotoatomicReaction> >
    reactions;

  MonteCarlo::AdjointPhotoatomicReactionNativeFactory::createIncoherentReactions(
                               *data_container,
                               energy_grid,
                               grid_searcher,
                               reactions,
                               MonteCarlo::DB_IMPULSE_INCOHERENT_ADJOINT_MODEL,
                               critical_line_energies );

  TEST_EQUALITY_CONST( reactions.size(), 7 );

  // Check that the first subshell reaction properties are correct
  TEST_EQUALITY_CONST( reactions.front()->getReactionType(),
                       MonteCarlo::K_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  TEST_EQUALITY_CONST( reactions.front()->getMaxEnergy(), 1.0 );
  TEST_FLOATING_EQUALITY( reactions.front()->getThresholdEnergy(), 1e-3, 1e-15 );

  double cross_section = reactions.front()->getCrossSection( 1e-3 );
  
  TEST_FLOATING_EQUALITY( cross_section, 2.13109682664046061e-06, 1e-12 );

  cross_section = reactions.front()->getCrossSection( 0.5 );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.0403122020637910819, 1e-12 );

  cross_section = reactions.front()->getCrossSection( 1.0-1.8285e-3 );
  
  UTILITY_TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = reactions.front()->getCrossSection( 1.0 );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  MonteCarlo::AdjointPhotonState adjoint_photon( 0 );
  adjoint_photon.setEnergy( 0.3 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;
  Data::SubshellType subshell;
  
  reactions.front()->react( adjoint_photon, bank, subshell );

  TEST_EQUALITY_CONST( bank.size(), 0 );

  // Check that the last subshell reaction properties are correct
  TEST_EQUALITY_CONST( reactions.back()->getReactionType(),
                       MonteCarlo::M3_SUBSHELL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  TEST_EQUALITY_CONST( reactions.back()->getMaxEnergy(), 1.0 );
  TEST_FLOATING_EQUALITY( reactions.back()->getThresholdEnergy(), 1e-3, 1e-15 );

  cross_section = reactions.back()->getCrossSection( 1e-3 );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.146081299107709617, 1e-12 );

  cross_section = reactions.back()->getCrossSection( 0.5 );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.0300480787362737839, 1e-12 );

  cross_section = reactions.back()->getCrossSection( 1.0-6.52e-6 );

  UTILITY_TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = reactions.back()->getCrossSection( 1.0 );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  adjoint_photon.setEnergy( 0.3 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );

  reactions.back()->react( adjoint_photon, bank, subshell );

  TEST_EQUALITY_CONST( bank.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the coherent adjoint reaction can be constructed
TEUCHOS_UNIT_TEST( AdjointPhotoatomicReactionNativeFactory,
                   createCoherentReaction )
{
  // Create the union energy grid
  Teuchos::ArrayRCP<double> energy_grid;

  MonteCarlo::AdjointPhotoatomicReactionNativeFactory::createUnionEnergyGrid(
                                                               *data_container,
                                                               energy_grid,
                                                               10.0 );
  // Create the hash based grid searcher
  Teuchos::RCP<const Utility::HashBasedGridSearcher> grid_searcher(
   new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<double>,false>(
                                                                   energy_grid,
                                                                   100 ) );

  // Create the coherent reaction
  std::shared_ptr<MonteCarlo::AdjointPhotoatomicReaction> reaction;

  MonteCarlo::AdjointPhotoatomicReactionNativeFactory::createCoherentReaction(
                                                               *data_container,
                                                               energy_grid,
                                                               grid_searcher,
                                                               reaction );

  // Check that the reaction properties are correct
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getMaxEnergy(), 10.0 );
  TEST_FLOATING_EQUALITY( reaction->getThresholdEnergy(), 1e-3, 1e-15 );

  // Check that the stored cross section is correct
  double cross_section = reaction->getCrossSection( 0.001 );
  
  TEST_FLOATING_EQUALITY( cross_section, 99.9639104922271571, 1e-12 );

  cross_section = reaction->getCrossSection( 1.0 );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.00783640704399895215, 1e-12 );

  cross_section = reaction->getCrossSection( 10.0 );

  TEST_FLOATING_EQUALITY( cross_section, 7.85383293330718803e-05, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the total forward reaction can be constructed
TEUCHOS_UNIT_TEST( AdjointPhotoatomicReactionNativeFactory,
                   createTotalForwardReaction )
{
  // Create the union energy grid
  Teuchos::ArrayRCP<double> energy_grid;

  MonteCarlo::AdjointPhotoatomicReactionNativeFactory::createUnionEnergyGrid(
                                                               *data_container,
                                                               energy_grid,
                                                               20.0 );
  // Create the hash based grid searcher
  Teuchos::RCP<const Utility::HashBasedGridSearcher> grid_searcher(
   new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<double>,false>(
                                                                   energy_grid,
                                                                   100 ) );

  // Create the total forward reaction
  std::shared_ptr<MonteCarlo::PhotoatomicReaction> reaction;

  MonteCarlo::AdjointPhotoatomicReactionNativeFactory::createTotalForwardReaction(
                                                               *data_container,
                                                               energy_grid,
                                                               grid_searcher,
                                                               reaction );

  // Check that the reaction properties are correct
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::TOTAL_PHOTOATOMIC_REACTION );
  TEST_FLOATING_EQUALITY( reaction->getThresholdEnergy(), 1e-3, 1e-15 );

  // Check that the stored cross section is correct
  double cross_section = reaction->getCrossSection( 0.001 );
  
  TEST_FLOATING_EQUALITY( cross_section, 73136.5325778411352, 1e-12 );

  cross_section = reaction->getCrossSection( 1.0 );
  
  TEST_FLOATING_EQUALITY( cross_section, 2.96240900282447228, 1e-12 );

  cross_section = reaction->getCrossSection( 20.0 );
  
  TEST_FLOATING_EQUALITY( cross_section, 1.08806003440055754, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the pair production adjoint reaction can be constructed
TEUCHOS_UNIT_TEST( AdjointPhotoatomicReactionNativeFactory,
                   createPairProductionReaction )
{
  // Create the union energy grid
  Teuchos::ArrayRCP<double> energy_grid;

  MonteCarlo::AdjointPhotoatomicReactionNativeFactory::createUnionEnergyGrid(
                                                               *data_container,
                                                               energy_grid,
                                                               20.0 );
  // Create the hash based grid searcher
  Teuchos::RCP<const Utility::HashBasedGridSearcher> grid_searcher(
   new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<double>,false>(
                                                                   energy_grid,
                                                                   100 ) );

  // Create the pair production reaction
  std::shared_ptr<MonteCarlo::LineEnergyAdjointPhotoatomicReaction> reaction;

  MonteCarlo::AdjointPhotoatomicReactionNativeFactory::createPairProductionReaction(
                                                               *data_container,
                                                               energy_grid,
                                                               grid_searcher,
                                                               reaction );

  // Check if the reaction properties are correct
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::PAIR_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getLineEnergy(),
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  TEST_EQUALITY_CONST( reaction->getMinOutgoingEnergy(),
                       2*Utility::PhysicalConstants::electron_rest_mass_energy );
  TEST_EQUALITY_CONST( reaction->getMaxOutgoingEnergy(),
                       20.0 );
}

//---------------------------------------------------------------------------//
// Check that the triplet production adjoint reaction can be constructed
TEUCHOS_UNIT_TEST( AdjointPhotoatomicReactionNativeFactory,
                   createTripletProductionReaction )
{
  // Create the union energy grid
  Teuchos::ArrayRCP<double> energy_grid;

  MonteCarlo::AdjointPhotoatomicReactionNativeFactory::createUnionEnergyGrid(
                                                               *data_container,
                                                               energy_grid,
                                                               10.0 );
  // Create the hash based grid searcher
  Teuchos::RCP<const Utility::HashBasedGridSearcher> grid_searcher(
   new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<double>,false>(
                                                                   energy_grid,
                                                                   100 ) );

  // Create the triplet production reaction
  std::shared_ptr<MonteCarlo::LineEnergyAdjointPhotoatomicReaction> reaction;

  MonteCarlo::AdjointPhotoatomicReactionNativeFactory::createTripletProductionReaction(
                                                               *data_container,
                                                               energy_grid,
                                                               grid_searcher,
                                                               reaction );

  // Check if the reaction properties are correct
  TEST_EQUALITY_CONST( reaction->getReactionType(),
                       MonteCarlo::TRIPLET_PRODUCTION_ADJOINT_PHOTOATOMIC_REACTION );
  TEST_EQUALITY_CONST( reaction->getLineEnergy(),
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  TEST_EQUALITY_CONST( reaction->getMinOutgoingEnergy(),
                       4*Utility::PhysicalConstants::electron_rest_mass_energy );
  TEST_EQUALITY_CONST( reaction->getMaxOutgoingEnergy(),
                       10.0 );
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

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstAdjointPhotoatomicReactionNativeFactory.cpp
//---------------------------------------------------------------------------//
