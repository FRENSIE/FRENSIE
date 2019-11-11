//---------------------------------------------------------------------------//
//!
//! \file   tstStandardPhotoatomicReaction.cpp
//! \author Alex Robinson
//! \brief  Standard photoatomic reaction unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <algorithm>

// FRENSIE Includes
#include "MonteCarlo_StandardReactionBaseImpl.hpp"
#include "MonteCarlo_PhotoatomicReaction.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSPhotoatomicDataExtractor.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::PhotoatomicReaction> ace_pp_reaction;
std::shared_ptr<MonteCarlo::PhotoatomicReaction> ace_pe_reaction;

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
template<typename InterpPolicy, bool processed_cross_section>
class TestPhotoatomicReaction : public MonteCarlo::StandardReactionBaseImpl<MonteCarlo::PhotoatomicReaction,InterpPolicy,processed_cross_section>
{
public:
  TestPhotoatomicReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index )
    : MonteCarlo::StandardReactionBaseImpl<MonteCarlo::PhotoatomicReaction,InterpPolicy,processed_cross_section>( incoming_energy_grid, cross_section, threshold_energy_index )
  { /* ... */ }

  ~TestPhotoatomicReaction()
  { /* ... */ }

  unsigned getNumberOfEmittedPhotons( const double energy ) const override
  { return 1u; }

  unsigned getNumberOfEmittedElectrons( const double energy ) const override
  { return 0u; }

  unsigned getNumberOfEmittedPositrons( const double energy ) const override
  { return 0u; }

  MonteCarlo::PhotoatomicReactionType getReactionType() const override
  { return MonteCarlo::TOTAL_PHOTOATOMIC_REACTION; }

  void react( MonteCarlo::PhotonState& photon,
	      MonteCarlo::ParticleBank& bank,
	      Data::SubshellType& shell_of_interaction ) const override
  { /* ... */ }
};

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
FRENSIE_UNIT_TEST( StandardPhotoatomicReaction, getThresholdEnergy_ace_pp )
{
  FRENSIE_CHECK_EQUAL( ace_pp_reaction->getThresholdEnergy(),
		       exp( 2.17614917816E-02 ) );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
FRENSIE_UNIT_TEST( StandardPhotoatomicReaction, getThresholdEnergy_ace_pe )
{
  FRENSIE_CHECK_EQUAL( ace_pe_reaction->getThresholdEnergy(),
		       exp( -6.90775527898E+00 ) );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
// \todo Complete tests using the raw EPDL cross section data
FRENSIE_UNIT_TEST( StandardPhotoatomicReaction, getCrossSection_ace_pp )
{
  double cross_section =
    ace_pp_reaction->getCrossSection( ace_pp_reaction->getThresholdEnergy() );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -3.84621780013E+01 ), 1e-12 );

  cross_section = ace_pp_reaction->getCrossSection( exp( 5.98672834901E+00 ));

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 3.62139611703E+00 ), 1e-12 );

  cross_section = ace_pp_reaction->getCrossSection( exp( 1.15129254650E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 3.71803283438E+00 ), 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
// \todo Complete tests using the raw EPDL cross section data
FRENSIE_UNIT_TEST( StandardPhotoatomicReaction, getCrossSection_ace_pe )
{
  double cross_section =
    ace_pe_reaction->getCrossSection( ace_pe_reaction->getThresholdEnergy() );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( 1.43969286532E+01 ), 1e-12 );

  cross_section = ace_pe_reaction->getCrossSection( exp( 5.98672834901E+00 ));

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -5.62662022605E+00 ), 1e-12 );

  cross_section = ace_pe_reaction->getCrossSection( exp( 1.15129254650E+01 ) );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, exp( -1.11594725061E+01 ), 1e-12 );
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
                new std::vector<double>( start, raw_pp_cross_section.end() ) );

  size_t pp_threshold_index =
    energy_grid->size() - pp_cross_section->size();

  std::shared_ptr<std::vector<double> > pe_cross_section(
     new std::vector<double>( xss_data_extractor->extractPhotoelectricCrossSection() ) );

  ace_pp_reaction.reset(
    new TestPhotoatomicReaction<Utility::LogLog,true>( energy_grid,
						       pp_cross_section,
						       pp_threshold_index ) );

  ace_pe_reaction.reset(
	   new TestPhotoatomicReaction<Utility::LogLog,true>( energy_grid,
							      pe_cross_section,
							      0u ) );

  // Clear setup data
  ace_file_handler.reset();
  xss_data_extractor.reset();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstStandardPhotoatomicReaction.cpp
//---------------------------------------------------------------------------//
