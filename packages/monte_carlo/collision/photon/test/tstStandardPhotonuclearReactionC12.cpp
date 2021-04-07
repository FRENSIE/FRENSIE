//---------------------------------------------------------------------------//
//!
//! \file   tstPhotonuclearReactionC12.cpp
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
    FRENSIE_CHECK_EQUAL( c12_photonuclear_reaction->getReactionType(),
                         MonteCarlo::GAMMA__N_EXCITED_STATE_0_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the Q value can be returned
FRENSIE_UNIT_TEST( PhotonuclearReaction_total, getQValue )
{
   FRENSIE_CHECK_EQUAL( c12_photonuclear_reaction->getQValue(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
FRENSIE_UNIT_TEST( PhotonuclearReaction_total, getThresholdEnergy )
{
  FRENSIE_CHECK_EQUAL( c12_photonuclear_reaction->getThresholdEnergy(),
                       7.366593 );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
FRENSIE_UNIT_TEST( PhotonuclearReaction_total, getCrossSection )
{
  // C-12 CrossSection Test
  double c12_cross_section =
    c12_photonuclear_reaction->getCrossSection( c12_photonuclear_reaction->getThresholdEnergy() );

  FRENSIE_CHECK_EQUAL( c12_cross_section , 0 );
  
  c12_cross_section = c12_photonuclear_reaction->getCrossSection( 7.3666 );
  
  FRENSIE_CHECK_EQUAL( c12_cross_section , 0 );
  
  c12_cross_section = c12_photonuclear_reaction->getCrossSection( 7.5 );
  
  FRENSIE_CHECK_EQUAL( c12_cross_section , 1.3019e-6 );

  c12_cross_section = c12_photonuclear_reaction->getCrossSection( 145 );
  
  FRENSIE_CHECK_EQUAL( c12_cross_section , 7.47069582e-4 );
  
  c12_cross_section = c12_photonuclear_reaction->getCrossSection( 147.5 );
  
  FRENSIE_CHECK_EQUAL( c12_cross_section , 8.7044537e-4 );
  
  c12_cross_section = c12_photonuclear_reaction->getCrossSection( 150 );
  
  FRENSIE_CHECK_EQUAL( c12_cross_section , 1.0447981e-3 );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string c12_ace_file_name;
unsigned c12_ace_file_start_line;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "c12_ace_file",
                                        c12_ace_file_name, "",
                                        "Test basic C12 ACE file name" );

  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "c12_ace_file_start_line",
                                        c12_ace_file_start_line, 1,
                                        "Test basic C12 ACE file start line" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  std::unique_ptr<Data::ACEFileHandler> ace_file_handler(
                         new Data::ACEFileHandler( c12_ace_file_name,
                                                   "6012.24u",
                                                   c12_ace_file_start_line ) );
  
  std::unique_ptr<Data::XSSPhotonuclearDataExtractor> xss_data_extractor(
   new Data::XSSPhotonuclearDataExtractor(
                                      ace_file_handler->getTableNXSArray(),
  				      ace_file_handler->getTableJXSArray(),
  				      ace_file_handler->getTableXSSArray() ) );

  std::shared_ptr<const std::vector<double> > energy_grid(
            new std::vector<double>( xss_data_extractor->extractESZBlock() ) );

  std::shared_ptr<const Utility::HashBasedGridSearcher<double> > grid_searcher(
        new Utility::StandardHashBasedGridSearcher<std::vector<double>,false>(
                                                 energy_grid,
                                                 energy_grid->size()/100+1 ) );

  std::shared_ptr<const std::vector<double> > cross_section(
           new std::vector<double>(  xss_data_extractor->extractTOTBlock() ) );

  c12_photonuclear_reaction.reset( new TestPhotonuclearReaction(
                                 energy_grid,
                                 cross_section,
                                 0u,
                                 grid_searcher,
                                 MonteCarlo::GAMMA__N_EXCITED_STATE_0_REACTION,
                                 0 ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstPhotonuclearReactionC12.cpp
//---------------------------------------------------------------------------//
