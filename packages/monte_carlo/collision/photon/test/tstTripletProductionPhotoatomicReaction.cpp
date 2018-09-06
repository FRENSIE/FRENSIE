//---------------------------------------------------------------------------//
//!
//! \file   tstTripletProductionPhotoatomicReaction.cpp
//! \author Alex Robinson
//! \brief  Triplet production photoatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_TripletProductionPhotoatomicReaction.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::PhotoatomicReaction> basic_tp_reaction;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
FRENSIE_UNIT_TEST( TripletProductionPhotoatomicReaction, getReactionType )
{
  FRENSIE_CHECK_EQUAL( basic_tp_reaction->getReactionType(),
                       MonteCarlo::TRIPLET_PRODUCTION_PHOTOATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
FRENSIE_UNIT_TEST( TripletProductionPhotoatomicReaction, getThresholdEnergy )
{
  FRENSIE_CHECK_EQUAL( basic_tp_reaction->getThresholdEnergy(),
                       4*Utility::PhysicalConstants::electron_rest_mass_energy );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the reaction can be returned
FRENSIE_UNIT_TEST( TripletProductionPhotoatomicReaction,
                   getNumberOfEmittedPhotons )
{
  FRENSIE_CHECK_EQUAL( basic_tp_reaction->getNumberOfEmittedPhotons( 1e-4 ),
                       0u );

  FRENSIE_CHECK_EQUAL( basic_tp_reaction->getNumberOfEmittedPhotons(
                                     basic_tp_reaction->getThresholdEnergy() ),
                       2u );

  FRENSIE_CHECK_EQUAL( basic_tp_reaction->getNumberOfEmittedPhotons( 20.0 ),
                       2u );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( TripletProductionPhotoatomicReaction,
                   getNumberOfEmittedElectrons )
{
  FRENSIE_CHECK_EQUAL( basic_tp_reaction->getNumberOfEmittedElectrons( 1e-4 ),
                       0u );

  FRENSIE_CHECK_EQUAL( basic_tp_reaction->getNumberOfEmittedElectrons(
                                     basic_tp_reaction->getThresholdEnergy() ),
                       2u );

  FRENSIE_CHECK_EQUAL( basic_tp_reaction->getNumberOfEmittedElectrons( 20.0 ),
                       2u );
}

//---------------------------------------------------------------------------//
// Check that the number of positrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( TripletProductionPhotoatomicReaction,
                   getNumberOfEmittedPositrons )
{
  FRENSIE_CHECK_EQUAL( basic_tp_reaction->getNumberOfEmittedPositrons( 1e-4 ),
                       0u );

  FRENSIE_CHECK_EQUAL( basic_tp_reaction->getNumberOfEmittedPositrons(
                                     basic_tp_reaction->getThresholdEnergy() ),
                       0u );

  FRENSIE_CHECK_EQUAL( basic_tp_reaction->getNumberOfEmittedPositrons( 20.0 ),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the triplet production cross section can be returned
FRENSIE_UNIT_TEST( TripletProductionPhotoatomicReaction, getCrossSection )
{
  double cross_section = basic_tp_reaction->getCrossSection( 1e-3 );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = basic_tp_reaction->getCrossSection(
                                     basic_tp_reaction->getThresholdEnergy() );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = basic_tp_reaction->getCrossSection( 20.0 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.186299999999999993, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the triplet production reaction can be returned
FRENSIE_UNIT_TEST( TripletProductionPhotoatomicReaction, react )
{
  std::shared_ptr<MonteCarlo::PhotonState> photon( new MonteCarlo::PhotonState(0));
  photon->setDirection( 0.0, 0.0, 1.0 );
  photon->setEnergy( 3.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType subshell;

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  basic_tp_reaction->react( *photon, bank, subshell );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // Check the bank size
  FRENSIE_CHECK_EQUAL( bank.size(), 3 );

  // Check the subshell
  FRENSIE_CHECK_EQUAL( subshell, Data::UNKNOWN_SUBSHELL );

  // Check the initial photon (which is now an annihilation photon)
  FRENSIE_CHECK_EQUAL( photon->getEnergy(),
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_SMALL( photon->getZDirection(), 1e-15 );
  FRENSIE_CHECK_SMALL( photon->getYDirection(), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon->getXDirection(), -1.0, 1e-15 );
  FRENSIE_CHECK_EQUAL( photon->getCollisionNumber(), 0 );
  FRENSIE_CHECK_EQUAL( photon->getGenerationNumber(), 1 );

  // Check the first generated electron
  FRENSIE_CHECK_EQUAL( bank.top().getParticleType(), MonteCarlo::ELECTRON );
  FRENSIE_CHECK_EQUAL( bank.top().getZDirection(), 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getEnergy(), 0.6593340599133334, 1e-12 );
  FRENSIE_CHECK_EQUAL( bank.top().getCollisionNumber(), 0 );
  FRENSIE_CHECK_EQUAL( bank.top().getGenerationNumber(), 1 );

  bank.pop();

  // Check the second generated electron
  FRENSIE_CHECK_EQUAL( bank.top().getParticleType(), MonteCarlo::ELECTRON );
  FRENSIE_CHECK_EQUAL( bank.top().getZDirection(), 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getEnergy(), 0.6593340599133334, 1e-12 );
  FRENSIE_CHECK_EQUAL( bank.top().getCollisionNumber(), 0 );
  FRENSIE_CHECK_EQUAL( bank.top().getGenerationNumber(), 1 );
  
  bank.pop();

  // Check the second annihilation photon
  FRENSIE_CHECK_EQUAL( bank.top().getParticleType(), MonteCarlo::PHOTON );
  FRENSIE_CHECK_EQUAL( bank.top().getEnergy(),
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_SMALL( bank.top().getZDirection(), 1e-15 );
  FRENSIE_CHECK_SMALL( bank.top().getYDirection(), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getXDirection(), 1.0, 1e-15 );
  FRENSIE_CHECK_EQUAL( bank.top().getCollisionNumber(), 0 );
  FRENSIE_CHECK_EQUAL( bank.top().getGenerationNumber(), 1 );
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
  {
    // Create the native data file container
    Data::ElectronPhotonRelaxationDataContainer 
      data_container( test_native_file_name );

    // Extract the photon energy grid
    std::shared_ptr<std::vector<double> > photon_energy_grid(
             new std::vector<double>( data_container.getPhotonEnergyGrid() ) );

    // Extract the triplet production cross section
    std::shared_ptr<std::vector<double> > triplet_production_cs(
      new std::vector<double>( data_container.getTripletProductionCrossSection() ) );

    size_t threshold_index =
      data_container.getTripletProductionCrossSectionThresholdEnergyIndex();

    basic_tp_reaction.reset(
      new MonteCarlo::TripletProductionPhotoatomicReaction<Utility::LinLin,false>(
                                                         photon_energy_grid,
                                                         triplet_production_cs,
                                                         threshold_index,
                                                         false ) );
  }
  
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstTripletProductionPhotoatomicReaction.cpp
//---------------------------------------------------------------------------//
