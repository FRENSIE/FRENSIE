//---------------------------------------------------------------------------//
//!
//! \file   tstPhotonuclearReactionH2.cpp
//! \author Ryan Pease
//! \brief  Photonuclear reaction unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_StandardPhotonuclearReaction.hpp"
#include "MonteCarlo_PhotonuclearReactionType.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSPhotonuclearDataExtractor.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestPhotonuclearReaction : public MonteCarlo::StandardPhotonuclearReaction
{
public:

  using MonteCarlo::StandardPhotonuclearReaction::StandardPhotonuclearReaction;

  ~TestPhotonuclearReaction()
  { /* ... */ }

  unsigned getNumberOfEmittedParticles( const double energy ) const final override
  { return 0u; }

  void react( MonteCarlo::PhotonState& photon, MonteCarlo::ParticleBank& bank ) const final override
  { /* ... */ }
};

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::unique_ptr<const MonteCarlo::PhotonuclearReaction> h2_photonuclear_reaction;
std::unique_ptr<const MonteCarlo::PhotonuclearReaction> c12_photonuclear_reaction;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the reaction type of an elastic reaction can be returned
FRENSIE_UNIT_TEST( PhotonuclearReaction_total, getReactionType )
{
  FRENSIE_CHECK_EQUAL( h2_photonuclear_reaction->getReactionType(),
                       MonteCarlo::GAMMA__ANYTHING_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the Q value can be returned
FRENSIE_UNIT_TEST( PhotonuclearReaction_total, getQValue )
{
  FRENSIE_CHECK_EQUAL( h2_photonuclear_reaction->getQValue(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
FRENSIE_UNIT_TEST( PhotonuclearReaction_total, getThresholdEnergy )
{
  FRENSIE_CHECK_EQUAL( h2_photonuclear_reaction->getThresholdEnergy(),
  		       2.2246 );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
FRENSIE_UNIT_TEST( PhotonuclearReaction_total, getCrossSection )
{
  // H-2 CrossSection Test
  double h2_cross_section =
    h2_photonuclear_reaction->getCrossSection( 2.2246 );

  FRENSIE_CHECK_EQUAL( h2_cross_section , 0 );

  h2_cross_section = h2_photonuclear_reaction->getCrossSection( 2.4);

  FRENSIE_CHECK_EQUAL( h2_cross_section , 8.9519e-4 );
  
  h2_cross_section = h2_photonuclear_reaction->getCrossSection( 2.6);
  
  FRENSIE_CHECK_EQUAL( h2_cross_section , 1.1567e-3 );
  
  h2_cross_section = h2_photonuclear_reaction->getCrossSection( 20 );
  
  FRENSIE_CHECK_EQUAL( h2_cross_section , 5.9811e-4);
  
  h2_cross_section = h2_photonuclear_reaction->getCrossSection( 25 );
  
  FRENSIE_CHECK_EQUAL( h2_cross_section , 4.3855e-4 );
  
  h2_cross_section = h2_photonuclear_reaction->getCrossSection( 30 );
  
  FRENSIE_CHECK_EQUAL( h2_cross_section , 3.549e-4 );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string h2_ace_file_name;
unsigned h2_ace_file_start_line;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "h2_ace_file",
                                        h2_ace_file_name, "",
                                        "Test basic H2 ACE file name" );

  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "h2_ace_file_start_line",
                                        h2_ace_file_start_line, 1,
                                        "Test basic H2 ACE file start line" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  std::unique_ptr<Data::ACEFileHandler> ace_file_handler(
                          new Data::ACEFileHandler( h2_ace_file_name,
                                                    "1002.24u",
                                                    h2_ace_file_start_line ) );
    
  std::unique_ptr<Data::XSSPhotonuclearDataExtractor> xss_data_extractor(
        new Data::XSSPhotonuclearDataExtractor(
                                      ace_file_handler->getTableNXSArray(),
                                      ace_file_handler->getTableJXSArray(),
                                      ace_file_handler->getTableXSSArray() ) );
  
  std::shared_ptr<const std::vector<double> > energy_grid(
            new std::vector<double>( xss_data_extractor->extractESZBlock() ) );

  std::shared_ptr<const std::vector<double> > cross_section(
           new std::vector<double>(  xss_data_extractor->extractTOTBlock() ) );

  h2_photonuclear_reaction.reset( new TestPhotonuclearReaction(
                                          energy_grid,
                                          cross_section,
                                          0u,
                                          MonteCarlo::GAMMA__ANYTHING_REACTION,
                                          0 ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstPhotonuclearReactionH2.cpp
//---------------------------------------------------------------------------//
