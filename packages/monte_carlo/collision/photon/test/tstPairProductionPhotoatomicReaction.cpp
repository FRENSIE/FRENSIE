//---------------------------------------------------------------------------//
//!
//! \file   tstPairProductionPhotoatomicReaction.cpp
//! \author Alex Robinson
//! \brief  Pair production photoatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_PairProductionPhotoatomicReaction.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSPhotoatomicDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::PhotoatomicReaction> ace_basic_pp_reaction,
  ace_detailed_pp_reaction;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
FRENSIE_UNIT_TEST( PairProductionPhotoatomicReaction, getReactionType_ace )
{
  FRENSIE_CHECK_EQUAL( ace_basic_pp_reaction->getReactionType(),
                       MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL( ace_detailed_pp_reaction->getReactionType(),
                       MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
FRENSIE_UNIT_TEST( PairProductionPhotoatomicReaction, getThresholdEnergy_ace )
{
  FRENSIE_CHECK_EQUAL( ace_basic_pp_reaction->getThresholdEnergy(),
                       exp( 2.17614917816E-02 ) );

  FRENSIE_CHECK_EQUAL( ace_detailed_pp_reaction->getThresholdEnergy(),
                       exp( 2.17614917816E-02 ) );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( PairProductionPhotoatomicReaction,
                   getNumberOfEmittedPhotons_ace_basic )
{
  FRENSIE_CHECK_EQUAL(ace_basic_pp_reaction->getNumberOfEmittedPhotons( 1e-4 ),
                      0u);

  FRENSIE_CHECK_EQUAL( ace_basic_pp_reaction->getNumberOfEmittedPhotons(
                       ace_basic_pp_reaction->getThresholdEnergy() ),
                       2u );

  FRENSIE_CHECK_EQUAL( ace_basic_pp_reaction->getNumberOfEmittedPhotons( 20.0 ), 2u);
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( PairProductionPhotoatomicReaction,
                   getNumberOfEmittedPhotons_ace_detailed )
{
  FRENSIE_CHECK_EQUAL(ace_detailed_pp_reaction->getNumberOfEmittedPhotons( 1e-4 ),
                      0u);

  FRENSIE_CHECK_EQUAL( ace_detailed_pp_reaction->getNumberOfEmittedPhotons(
                       ace_detailed_pp_reaction->getThresholdEnergy() ),
                       0u );

  FRENSIE_CHECK_EQUAL( ace_detailed_pp_reaction->getNumberOfEmittedPhotons( 20.0 ), 0u);
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( PairProductionPhotoatomicReaction,
                   getNumberOfEmittedElectrons_basic )
{
  FRENSIE_CHECK_EQUAL(
              ace_basic_pp_reaction->getNumberOfEmittedElectrons( 1e-4 ), 0u );

  FRENSIE_CHECK_EQUAL( ace_basic_pp_reaction->getNumberOfEmittedElectrons(
                         ace_basic_pp_reaction->getThresholdEnergy() ),
                       1u );

  FRENSIE_CHECK_EQUAL(
              ace_basic_pp_reaction->getNumberOfEmittedElectrons( 20.0 ), 1u );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( PairProductionPhotoatomicReaction,
                   getNumberOfEmittedElectrons_detailed )
{
  FRENSIE_CHECK_EQUAL(
              ace_detailed_pp_reaction->getNumberOfEmittedElectrons( 1e-4 ), 0u );

  FRENSIE_CHECK_EQUAL( ace_detailed_pp_reaction->getNumberOfEmittedElectrons(
                         ace_detailed_pp_reaction->getThresholdEnergy() ),
                       1u );

  FRENSIE_CHECK_EQUAL(
              ace_detailed_pp_reaction->getNumberOfEmittedElectrons( 20.0 ), 1u );
}

//---------------------------------------------------------------------------//
// Check that the number of positrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( PairProductionPhotoatomicReaction,
                   getNumberOfEmittedPositrons_basic )
{
  FRENSIE_CHECK_EQUAL(
              ace_basic_pp_reaction->getNumberOfEmittedPositrons( 1e-4 ), 0u );

  FRENSIE_CHECK_EQUAL( ace_basic_pp_reaction->getNumberOfEmittedPositrons(
                         ace_basic_pp_reaction->getThresholdEnergy() ),
                       0u );

  FRENSIE_CHECK_EQUAL(
              ace_basic_pp_reaction->getNumberOfEmittedPositrons( 20.0 ), 0u );
}

//---------------------------------------------------------------------------//
// Check that the number of positrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( PairProductionPhotoatomicReaction,
                   getNumberOfEmittedPositrons_detailed )
{
  FRENSIE_CHECK_EQUAL(
              ace_detailed_pp_reaction->getNumberOfEmittedPositrons( 1e-4 ), 0u );

  FRENSIE_CHECK_EQUAL( ace_detailed_pp_reaction->getNumberOfEmittedPositrons(
                         ace_detailed_pp_reaction->getThresholdEnergy() ),
                       1u );

  FRENSIE_CHECK_EQUAL(
           ace_detailed_pp_reaction->getNumberOfEmittedPositrons( 20.0 ), 1u );
}

//---------------------------------------------------------------------------//
// Check that the pair production cross section can be returned
FRENSIE_UNIT_TEST( PairProductionPhotoatomicReaction, getCrossSection_ace )
{
  double cross_section = ace_basic_pp_reaction->getCrossSection( 1.01e-3 );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section = ace_basic_pp_reaction->getCrossSection(
                                 ace_basic_pp_reaction->getThresholdEnergy() );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -3.84621780013E+01 ), 1e-12 );

  cross_section =
    ace_basic_pp_reaction->getCrossSection( exp( 5.98672834901E+00 ));

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 3.62139611703E+00 ), 1e-12 );

  cross_section =
    ace_basic_pp_reaction->getCrossSection( exp( 1.15129254650E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 3.71803283438E+00 ), 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the pair production reaction can be simulated
FRENSIE_UNIT_TEST( PairProductionPhotoatomicReaction, react_ace_basic )
{
  std::shared_ptr<MonteCarlo::PhotonState> photon(new MonteCarlo::PhotonState(0));

  photon->setDirection( 0.0, 0.0, 1.0 );
  photon->setEnergy( 2.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType subshell;

  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.5;
  fake_stream[2] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  ace_basic_pp_reaction->react( *photon, bank, subshell );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // Check the bank
  FRENSIE_CHECK_EQUAL( bank.size(), 2 );

  // Check the subshell
  FRENSIE_CHECK_EQUAL( subshell, Data::UNKNOWN_SUBSHELL );

  // Check the photon (which is now an annihilation photon)
  FRENSIE_CHECK_EQUAL( photon->getEnergy(),
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon->getZDirection(), 0.8649171183642954, 1e-15 );
  FRENSIE_CHECK_SMALL( photon->getYDirection(), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon->getXDirection(), 0.5019147122374511, 1e-15);
  FRENSIE_CHECK_EQUAL( photon->getCollisionNumber(), 0 );
  FRENSIE_CHECK_EQUAL( photon->getGenerationNumber(), 1 );

  // Check the generated electron
  FRENSIE_CHECK_EQUAL( bank.top().getParticleType(), MonteCarlo::ELECTRON );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getEnergy(),0.48900108987, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getZDirection(),
                          0.5019147122374511,
                          1e-15 );
  FRENSIE_CHECK_SMALL( bank.top().getYDirection(), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getXDirection(),
                                   0.8649171183642954,
                                   1e-15 );
  FRENSIE_CHECK_EQUAL( bank.top().getCollisionNumber(), 0 );
  FRENSIE_CHECK_EQUAL( bank.top().getGenerationNumber(), 1 );

  bank.pop();

  // Check the second annihilation photon
  FRENSIE_CHECK_EQUAL( bank.top().getParticleType(), MonteCarlo::PHOTON );
  FRENSIE_CHECK_EQUAL( bank.top().getEnergy(),
                       Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getZDirection(),
                          -0.8649171183642954,
                          1e-15 );
  FRENSIE_CHECK_SMALL( bank.top().getYDirection(), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getXDirection(),
                                   -0.5019147122374511,
                                   1e-15 );
  FRENSIE_CHECK_EQUAL( bank.top().getCollisionNumber(), 0 );
  FRENSIE_CHECK_EQUAL( bank.top().getGenerationNumber(), 1 );
}

//---------------------------------------------------------------------------//
// Check that the pair production reaction can be simulated
FRENSIE_UNIT_TEST( PairProductionPhotoatomicReaction, react_ace_detailed )
{
  std::shared_ptr<MonteCarlo::PhotonState> photon(new MonteCarlo::PhotonState(0));

  photon->setDirection( 0.0, 0.0, 1.0 );
  photon->setEnergy( 2.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType subshell;

  std::vector<double> fake_stream( 5 );
  fake_stream[0] = 0.0; // Sample energy ratio = 0.0
  fake_stream[1] = 0.5; // Assign energy ratio to the electron
  fake_stream[2] = 0.5; // Sample azimuthal angle = pi
  fake_stream[3] = 0.0; // Sample electron angle cosine = 1.0
  fake_stream[4] = 1.0-1e-12; // Sample second angle cosine = -1.0

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  ace_detailed_pp_reaction->react( *photon, bank, subshell );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // Check the bank
  FRENSIE_CHECK_EQUAL( bank.size(), 2 );

  // Check the subshell
  FRENSIE_CHECK_EQUAL( subshell, Data::UNKNOWN_SUBSHELL );

  // Check the photon
  FRENSIE_CHECK( photon->isGone() );
  FRENSIE_CHECK_EQUAL( photon->getCollisionNumber(), 1 );
  FRENSIE_CHECK_EQUAL( photon->getGenerationNumber(), 0 );

  // Check the generated electron
  FRENSIE_CHECK_EQUAL( bank.top().getParticleType(), MonteCarlo::ELECTRON );
  FRENSIE_CHECK_EQUAL( bank.top().getEnergy(), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getZDirection(), 1.0, 1e-15 );
  FRENSIE_CHECK_SMALL( bank.top().getYDirection(), 1e-15);
  FRENSIE_CHECK_SMALL( bank.top().getXDirection(), 1e-15 );
  FRENSIE_CHECK_EQUAL( bank.top().getCollisionNumber(), 0 );
  FRENSIE_CHECK_EQUAL( bank.top().getGenerationNumber(), 1 );

  bank.pop();

  // Check the generated positron
  FRENSIE_CHECK_EQUAL( bank.top().getParticleType(), MonteCarlo::POSITRON );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getEnergy(), 9.7800217974000003e-01, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getZDirection(), -1.0, 1e-15 );
  FRENSIE_CHECK_SMALL( bank.top().getYDirection(), 1e-15 );
  FRENSIE_CHECK_SMALL( bank.top().getXDirection(), 1e-15 );
  FRENSIE_CHECK_EQUAL( bank.top().getCollisionNumber(), 0 );
  FRENSIE_CHECK_EQUAL( bank.top().getGenerationNumber(), 1 );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_ace_file_name;
unsigned test_ace_file_start_line;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_ace_file",
                                        test_ace_file_name, "",
                                        "Test ACE file name" );

  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_ace_file_start_line",
                                        test_ace_file_start_line, 1,
                                        "Test ACE file start line" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create a file handler and data extractor
  std::shared_ptr<Data::ACEFileHandler> ace_file_handler(
                        new Data::ACEFileHandler( test_ace_file_name,
                                                  "82000.04p",
                                                  test_ace_file_start_line ) );
  
  std::shared_ptr<Data::XSSPhotoatomicDataExtractor> xss_data_extractor(
                            new Data::XSSPhotoatomicDataExtractor(
                                      ace_file_handler->getTableNXSArray(),
                                      ace_file_handler->getTableJXSArray(),
                                      ace_file_handler->getTableXSSArray() ) );

  std::shared_ptr<std::vector<double> > energy_grid(
          new std::vector<double>( xss_data_extractor->extractEnergyGrid() ) );

  Utility::ArrayView<const double> raw_pp_cross_section =
    xss_data_extractor->extractPairProductionCrossSection();

  Utility::ArrayView<const double>::iterator start =
    std::find_if( raw_pp_cross_section.begin(),
                  raw_pp_cross_section.end(),
                  [](double cs){ return cs != 0.0; } );

  std::shared_ptr<std::vector<double> > pp_cross_section(
               new std::vector<double>(  start, raw_pp_cross_section.end() ) );

  size_t pp_threshold_index =
    energy_grid->size() - pp_cross_section->size();

  ace_basic_pp_reaction.reset(
    new MonteCarlo::PairProductionPhotoatomicReaction<Utility::LogLog>(
                                                        energy_grid,
                                                        pp_cross_section,
                                                        pp_threshold_index,
                                                        false ) );

  ace_detailed_pp_reaction.reset(
    new MonteCarlo::PairProductionPhotoatomicReaction<Utility::LogLog>(
                                                        energy_grid,
                                                        pp_cross_section,
                                                        pp_threshold_index,
                                                        true ) );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstPairProductionPhotoatomicReaction.cpp
//---------------------------------------------------------------------------//
