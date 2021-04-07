//---------------------------------------------------------------------------//
//!
//! \file   tstSubshellPhotoelectricPhotoatomicReaction.cpp
//! \author Alex Robinson
//! \brief  Subshell photoelectric photoatomic reaction unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_SubshellPhotoelectricPhotoatomicReaction.hpp"
#include "Data_SubshellType.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::PhotoatomicReaction> ace_k_photoelectric_reaction;
std::shared_ptr<MonteCarlo::PhotoatomicReaction> ace_l1_photoelectric_reaction;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the subshell can be returned
FRENSIE_UNIT_TEST( SubshellPhotoelectricPhotoatomicReaction, getSubshell_ace )
{
  std::shared_ptr<MonteCarlo::SubshellPhotoelectricPhotoatomicReaction<Utility::LogLog> > true_reaction =
    std::dynamic_pointer_cast<MonteCarlo::SubshellPhotoelectricPhotoatomicReaction<Utility::LogLog> >( ace_k_photoelectric_reaction );

  FRENSIE_CHECK_EQUAL( true_reaction->getSubshell(), Data::K_SUBSHELL );

  true_reaction =
    std::dynamic_pointer_cast<MonteCarlo::SubshellPhotoelectricPhotoatomicReaction<Utility::LogLog> >( ace_l1_photoelectric_reaction );

  FRENSIE_CHECK_EQUAL( true_reaction->getSubshell(), Data::L1_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Check that the subshell binding energy can be returned
FRENSIE_UNIT_TEST( SubshellPhotoelectricPhotoatomicReaction,
		   getSubshellBindingEnergy )
{
  std::shared_ptr<MonteCarlo::SubshellPhotoelectricPhotoatomicReaction<Utility::LogLog> > true_reaction =
    std::dynamic_pointer_cast<MonteCarlo::SubshellPhotoelectricPhotoatomicReaction<Utility::LogLog> >( ace_k_photoelectric_reaction );

  FRENSIE_CHECK_EQUAL( true_reaction->getSubshellBindingEnergy(),
		       8.829000000000E-02 );

  true_reaction =
    std::dynamic_pointer_cast<MonteCarlo::SubshellPhotoelectricPhotoatomicReaction<Utility::LogLog> >( ace_l1_photoelectric_reaction );

  FRENSIE_CHECK_EQUAL( true_reaction->getSubshellBindingEnergy(),
		       1.584700000000E-02 );
}

//---------------------------------------------------------------------------//
// Check that the reaction type can be returned
FRENSIE_UNIT_TEST( SubshellPhotoelectricPhotoatomicReaction,
		   getReactionType_ace )
{
  FRENSIE_CHECK_EQUAL(
		   ace_k_photoelectric_reaction->getReactionType(),
		   MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

  FRENSIE_CHECK_EQUAL(
		  ace_l1_photoelectric_reaction->getReactionType(),
		  MonteCarlo::L1_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
FRENSIE_UNIT_TEST( SubshellPhotoelectricPhotoatomicReaction,
		   getThresholdEnergy_ace )
{
  FRENSIE_CHECK_EQUAL( ace_k_photoelectric_reaction->getThresholdEnergy(),
		       exp( -2.427128314806E+00 ) );

  FRENSIE_CHECK_EQUAL( ace_l1_photoelectric_reaction->getThresholdEnergy(),
		       exp( -4.144774439987E+00 ) );
}

//---------------------------------------------------------------------------//
// Check that the number of photons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( SubshellPhotoelectricPhotoatomicReaction,
		   getNumberOfEmittedPhotons_ace )
{
  FRENSIE_CHECK_EQUAL(
	       ace_k_photoelectric_reaction->getNumberOfEmittedPhotons( 1e-3 ),
	       0u );

  FRENSIE_CHECK_EQUAL(
	       ace_k_photoelectric_reaction->getNumberOfEmittedPhotons( 20.0 ),
	       0u );

  FRENSIE_CHECK_EQUAL(
	      ace_l1_photoelectric_reaction->getNumberOfEmittedPhotons( 1e-3 ),
	      0u );

  FRENSIE_CHECK_EQUAL(
	      ace_l1_photoelectric_reaction->getNumberOfEmittedPhotons( 20.0 ),
	      0u );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( SubshellPhotoelectricPhotoatomicReaction,
		   getNumberOfEmittedElectrons_ace )
{
  FRENSIE_CHECK_EQUAL(
	     ace_k_photoelectric_reaction->getNumberOfEmittedElectrons( 1e-3 ),
             0u );

  FRENSIE_CHECK_EQUAL(
             ace_k_photoelectric_reaction->getNumberOfEmittedElectrons(
                          ace_k_photoelectric_reaction->getThresholdEnergy() ),
             1u );

  FRENSIE_CHECK_EQUAL(
	     ace_k_photoelectric_reaction->getNumberOfEmittedElectrons( 20.0 ),
             1u );

  FRENSIE_CHECK_EQUAL(
            ace_l1_photoelectric_reaction->getNumberOfEmittedElectrons( 1e-3 ),
            0u );

  FRENSIE_CHECK_EQUAL(
            ace_l1_photoelectric_reaction->getNumberOfEmittedElectrons(
                         ace_l1_photoelectric_reaction->getThresholdEnergy() ),
            1u );

  FRENSIE_CHECK_EQUAL(
            ace_l1_photoelectric_reaction->getNumberOfEmittedElectrons( 20.0 ),
            1u );
}

//---------------------------------------------------------------------------//
// Check that the number of positrons emitted from the rxn can be returned
FRENSIE_UNIT_TEST( SubshellPhotoelectricPhotoatomicReaction,
		   getNumberOfEmittedPositrons_ace )
{
  FRENSIE_CHECK_EQUAL(
	     ace_k_photoelectric_reaction->getNumberOfEmittedPositrons( 1e-3 ),
             0u );

  FRENSIE_CHECK_EQUAL(
             ace_k_photoelectric_reaction->getNumberOfEmittedPositrons(
                          ace_k_photoelectric_reaction->getThresholdEnergy() ),
             0u );

  FRENSIE_CHECK_EQUAL(
	     ace_k_photoelectric_reaction->getNumberOfEmittedPositrons( 20.0 ),
             0u );

  FRENSIE_CHECK_EQUAL(
            ace_l1_photoelectric_reaction->getNumberOfEmittedPositrons( 1e-3 ),
            0u );

  FRENSIE_CHECK_EQUAL(
            ace_l1_photoelectric_reaction->getNumberOfEmittedPositrons(
                         ace_l1_photoelectric_reaction->getThresholdEnergy() ),
            0u );

  FRENSIE_CHECK_EQUAL(
            ace_l1_photoelectric_reaction->getNumberOfEmittedPositrons( 20.0 ),
            0u );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
FRENSIE_UNIT_TEST( SubshellPhotoelectricPhotoatomicReaction,
		   getCrossSection_ace )
{
  // K subshell
  double cross_section =
    ace_k_photoelectric_reaction->getCrossSection( exp(-1.381551055796E+01) );

  FRENSIE_CHECK_SMALL( cross_section, 1e-12 );

  cross_section =
    ace_k_photoelectric_reaction->getCrossSection( exp( -2.427128314806E+00 ));

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 7.578565567350E+00 ), 1e-12 );

  cross_section =
    ace_k_photoelectric_reaction->getCrossSection( exp(-2.414302996307E+00) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 7.547192730643E+00 ), 1e-12 );

  cross_section =
    ace_k_photoelectric_reaction->getCrossSection( exp(1.151292546497E+01) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -1.135387253512E+01 ), 1e-12 );

  // L1 subshell
  cross_section =
    ace_l1_photoelectric_reaction->getCrossSection( exp(-1.381551055796E+01) );

  FRENSIE_CHECK_SMALL( cross_section, 1e-12 );

  cross_section =
    ace_l1_photoelectric_reaction->getCrossSection( exp(-4.144774439987E+00) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 8.861685600842E+00 ), 1e-12 );

  cross_section =
    ace_l1_photoelectric_reaction->getCrossSection( exp(-4.136738416467E+00) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 8.847146529853E+00 ), 1e-12 );

  cross_section =
    ace_l1_photoelectric_reaction->getCrossSection( exp(1.151292546497E+01) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -1.347975286228E+01 ), 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the reaction can be modeled
FRENSIE_UNIT_TEST( SubshellPhotoelectricPhotoatomicReaction, react_ace )
{
  std::shared_ptr<MonteCarlo::PhotonState> photon(new MonteCarlo::PhotonState(0));

  photon->setDirection( 0.0, 0.0, 1.0 );
  photon->setEnergy( 2.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType subshell;

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5;
  fake_stream[0] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  ace_k_photoelectric_reaction->react( *photon, bank, subshell );

  FRENSIE_CHECK( photon->isGone() );
  FRENSIE_CHECK_EQUAL( bank.size(), 1 );
  FRENSIE_CHECK_EQUAL( bank.top().getParticleType(), MonteCarlo::ELECTRON );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getEnergy(),
			  2.0 - 8.829000000000E-02,
			  1e-15 );
  FRENSIE_CHECK_SMALL( bank.top().getZDirection(), 1e-15 );
  FRENSIE_CHECK_SMALL( bank.top().getYDirection(), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getXDirection(), 1.0, 1e-15 );

  bank.pop();

  Utility::RandomNumberGenerator::unsetFakeStream();

  photon.reset( new MonteCarlo::PhotonState(0) );

  photon->setDirection( 0.0, 0.0, 1.0 );
  photon->setEnergy( 2.0 );

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  ace_l1_photoelectric_reaction->react( *photon, bank, subshell );

  FRENSIE_CHECK( photon->isGone() );
  FRENSIE_CHECK_EQUAL( bank.size(), 1 );
  FRENSIE_CHECK_EQUAL( bank.top().getParticleType(), MonteCarlo::ELECTRON );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getEnergy(),
			  2.0 - 1.584700000000E-02,
			  1e-15 );
  FRENSIE_CHECK_SMALL( bank.top().getZDirection(), 1e-15 );
  FRENSIE_CHECK_SMALL( bank.top().getYDirection(), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getXDirection(), 1.0, 1e-15 );

  bank.pop();

  Utility::RandomNumberGenerator::unsetFakeStream();
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

  // Extract the subshell information
  Utility::ArrayView<const double> subshell_order =
    xss_data_extractor->extractSubshellENDFDesignators();

  Utility::ArrayView<const double> binding_energies =
    xss_data_extractor->extractSubshellBindingEnergies();

  // Extract the energy grid and cross sections
  std::shared_ptr<std::vector<double> > energy_grid(
    new std::vector<double>( xss_data_extractor->extractPhotonEnergyGrid() ) );

  size_t energy_grid_points = energy_grid->size();

  Utility::ArrayView<const double> subshell_cross_sections =
    xss_data_extractor->extractSPHELBlock();

  Utility::ArrayView<const double> raw_k_cross_section =
    subshell_cross_sections( 0, energy_grid_points );

  Utility::ArrayView<const double>::iterator start =
    std::find_if( raw_k_cross_section.begin(),
		  raw_k_cross_section.end(),
		  [](double cs){ return cs != 0.0; } );

  std::shared_ptr<std::vector<double> > k_cross_section(
                 new std::vector<double>( start, raw_k_cross_section.end() ) );

  size_t k_threshold_index =
    energy_grid->size() - k_cross_section->size();

  Utility::ArrayView<const double> raw_l1_cross_section =
    subshell_cross_sections( energy_grid_points, energy_grid_points );

  start = std::find_if( raw_l1_cross_section.begin(),
			raw_l1_cross_section.end(),
			[](double cs){ return cs != 0.0; } );

  std::shared_ptr<std::vector<double> > l1_cross_section(
                new std::vector<double>( start, raw_l1_cross_section.end() ) );

  size_t l1_threshold_index =
    energy_grid->size() - l1_cross_section->size();

  // Create the reactions
  ace_k_photoelectric_reaction.reset(
    new MonteCarlo::SubshellPhotoelectricPhotoatomicReaction<Utility::LogLog>(
	  energy_grid,
	  k_cross_section,
	  k_threshold_index,
	  Data::convertENDFDesignatorToSubshellEnum( subshell_order[0] ),
	  binding_energies[0] ) );

  ace_l1_photoelectric_reaction.reset(
    new MonteCarlo::SubshellPhotoelectricPhotoatomicReaction<Utility::LogLog>(
	  energy_grid,
	  l1_cross_section,
	  l1_threshold_index,
	  Data::convertENDFDesignatorToSubshellEnum( subshell_order[1] ),
	  binding_energies[1] ) );

  // Clear setup data
  ace_file_handler.reset();
  xss_data_extractor.reset();

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstSubshellPhotoelectricPhotoatomicReaction.cpp
//---------------------------------------------------------------------------//
