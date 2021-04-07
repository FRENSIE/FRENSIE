//---------------------------------------------------------------------------//
//!
//! \file   tstCoherentPhotoatomicReaction.cpp
//! \author Alex Robinson
//! \brief  Coherent photoatomic reaction unit tests
//!
//--------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_CoherentPhotoatomicReaction.hpp"
#include "MonteCarlo_EfficientCoherentScatteringDistribution.hpp"
#include "MonteCarlo_StandardFormFactorSquared.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_InverseSquareAngstromUnit.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::PhotoatomicReaction> ace_coherent_reaction;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
FRENSIE_UNIT_TEST( CoherentPhotoatomicReaction, getReactionType_ace )
{
  FRENSIE_CHECK_EQUAL( ace_coherent_reaction->getReactionType(),
		       MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
FRENSIE_UNIT_TEST( CoherentPhotoatomicReaction, getThresholdEnergy_ace )
{
  FRENSIE_CHECK_EQUAL( ace_coherent_reaction->getThresholdEnergy(),
		       exp( -1.381551055796E+01 ) );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( CoherentPhotoatomicReaction, getNumberOfEmittedPhotons_ace )
{
  FRENSIE_CHECK_EQUAL( ace_coherent_reaction->getNumberOfEmittedPhotons(1e-3),
		       1u );

  FRENSIE_CHECK_EQUAL( ace_coherent_reaction->getNumberOfEmittedPhotons(20.0),
		       1u );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( CoherentPhotoatomicReaction,
                   getNumberOfEmittedElectrons_ace )
{
  FRENSIE_CHECK_EQUAL(ace_coherent_reaction->getNumberOfEmittedElectrons(1e-3),
                      0u );

  FRENSIE_CHECK_EQUAL(ace_coherent_reaction->getNumberOfEmittedElectrons(20.0),
		      0u );
}

//---------------------------------------------------------------------------//
// Check that the number of positrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( CoherentPhotoatomicReaction,
                   getNumberOfEmittedPositrons_ace )
{
  FRENSIE_CHECK_EQUAL(ace_coherent_reaction->getNumberOfEmittedPositrons(1e-3),
                      0u );

  FRENSIE_CHECK_EQUAL(ace_coherent_reaction->getNumberOfEmittedPositrons(20.0),
		      0u );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
FRENSIE_UNIT_TEST( CoherentPhotoatomicReaction, getCrossSection_ace )
{
  double cross_section =
    ace_coherent_reaction->getCrossSection( exp(-1.381551055796E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -5.071403810640E+00 ), 1e-12 );

  cross_section =
    ace_coherent_reaction->getCrossSection( exp( -1.364234411496E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -4.284251858121E+00 ), 1e-12 );

  cross_section =
    ace_coherent_reaction->getCrossSection( exp( 1.151292546497E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -2.309498238246E+01 ), 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the coherent reaction can be simulated
FRENSIE_UNIT_TEST( CoherentPhotoatomicReaction, react_ace )
{
  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  ace_coherent_reaction->react( photon, bank, shell_of_interaction );

  FRENSIE_CHECK_EQUAL( photon.getEnergy(), 20.0 );
  FRENSIE_CHECK( photon.getZDirection() < 1.0 );
  FRENSIE_CHECK_EQUAL( photon.getCollisionNumber(), 1 );
  FRENSIE_CHECK( bank.isEmpty() );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::UNKNOWN_SUBSHELL );
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
                                                  "82000.12p",
						  test_ace_file_start_line ) );
  
  std::shared_ptr<Data::XSSEPRDataExtractor> xss_data_extractor(
                            new Data::XSSEPRDataExtractor(
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );

  // Extract the energy grid and cross section
  std::shared_ptr<std::vector<double> > energy_grid(
    new std::vector<double>( xss_data_extractor->extractPhotonEnergyGrid() ) );

  Utility::ArrayView<const double> raw_coherent_cross_section =
    xss_data_extractor->extractCoherentCrossSection();

  Utility::ArrayView<const double>::iterator start =
    std::find_if( raw_coherent_cross_section.begin(),
                  raw_coherent_cross_section.end(),
                  [](double cs){ return cs != 0.0; } );

  std::shared_ptr<std::vector<double> > coherent_cross_section(
          new std::vector<double>( start, raw_coherent_cross_section.end() ) );

  size_t coherent_threshold_index =
    energy_grid->size() - coherent_cross_section->size();

  // Create the form factor
  Utility::ArrayView<const double>  jcohe_block =
    xss_data_extractor->extractJCOHEBlock();

  size_t form_factor_size = jcohe_block.size()/3;

  std::vector<double> recoil_momentum_squared(
                                          jcohe_block( 0, form_factor_size ) );

  std::vector<double> form_factor_squared(
                         jcohe_block( 2*form_factor_size, form_factor_size ) );

  for( size_t i = 0; i < form_factor_size; ++i )
  {
    recoil_momentum_squared[i] *= recoil_momentum_squared[i];

    form_factor_squared[i] *= form_factor_squared[i];
  }

  std::shared_ptr<Utility::UnitAwareTabularUnivariateDistribution<Utility::Units::InverseSquareAngstrom,void> >
    raw_form_factor_squared(
         new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::InverseSquareAngstrom,void>(
                                                       recoil_momentum_squared,
						       form_factor_squared ) );

  std::shared_ptr<const MonteCarlo::FormFactorSquared> form_factor_obj(
       new MonteCarlo::StandardFormFactorSquared<Utility::Units::InverseSquareAngstrom>(
                                                   raw_form_factor_squared ) );
  
  // Create the coherent scattering distribution
  std::shared_ptr<const MonteCarlo::CoherentScatteringDistribution> distribution(
		       new MonteCarlo::EfficientCoherentScatteringDistribution(
                                                           form_factor_obj ) );

  // Create the reaction
  ace_coherent_reaction.reset(
		new MonteCarlo::CoherentPhotoatomicReaction<Utility::LogLog>(
						      energy_grid,
						      coherent_cross_section,
						      coherent_threshold_index,
						      distribution ) );

  // Clear setup data
  ace_file_handler.reset();
  xss_data_extractor.reset();

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstCoherentPhotoatomicReaction.cpp
//---------------------------------------------------------------------------//
