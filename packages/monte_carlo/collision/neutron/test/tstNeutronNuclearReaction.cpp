//---------------------------------------------------------------------------//
//!
//! \file   tstNeutronNuclearReaction.cpp
//! \author Alex Robinson
//! \brief  Neutron nuclear reaction unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_StandardNeutronNuclearReaction.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<const MonteCarlo::NeutronNuclearReaction> nuclear_reaction;

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestNeutronNuclearReaction : public MonteCarlo::StandardNeutronNuclearReaction
{
public:
  TestNeutronNuclearReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const unsigned threshold_energy_index,
       const MonteCarlo::NuclearReactionType reaction_type,
       const double q_value,
       const double temperature )
    : MonteCarlo::StandardNeutronNuclearReaction( incoming_energy_grid,
                                                  cross_section,
                                                  threshold_energy_index,
                                                  reaction_type,
                                                  q_value,
                                                  temperature )
  { /* ... */ }

  ~TestNeutronNuclearReaction()
  { /* ... */ }

  unsigned getNumberOfEmittedParticles( const double energy ) const final override
  { return 0u; }

  void react( MonteCarlo::NeutronState& neutron, MonteCarlo::ParticleBank& bank ) const final override
  { /* ... */ }
};

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the reaction type of an elastic reaction can be returned
FRENSIE_UNIT_TEST( NuclearReaction_elastic, getReactionType )
{
  FRENSIE_CHECK_EQUAL( nuclear_reaction->getReactionType(),
		       MonteCarlo::N__N_ELASTIC_REACTION );
}

//---------------------------------------------------------------------------//
// Check that the Q value can be returned
FRENSIE_UNIT_TEST( NuclearReaction_elastic, getQValue )
{
  FRENSIE_CHECK_EQUAL( nuclear_reaction->getQValue(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the threshold energy can be returned
FRENSIE_UNIT_TEST( NuclearReaction_elastic, getThresholdEnergy )
{
  FRENSIE_CHECK_EQUAL( nuclear_reaction->getThresholdEnergy(),
		       1.00000000000e-11 );
}

//---------------------------------------------------------------------------//
// Check that the cross section can be returned
FRENSIE_UNIT_TEST( NuclearReaction_elastic, getCrossSection )
{
  double cross_section =
    nuclear_reaction->getCrossSection( 1.00000000000e-11 );

  FRENSIE_CHECK_EQUAL( cross_section, 1.16054600000e+03 );

  cross_section = nuclear_reaction->getCrossSection( 1.015625e-11 );

  FRENSIE_CHECK_EQUAL( cross_section, 1.151689e3 );

  cross_section = nuclear_reaction->getCrossSection( 1.03125e-11 );

  FRENSIE_CHECK_EQUAL( cross_section, 1.142832e3 );

  cross_section = nuclear_reaction->getCrossSection( 1.0625e-11 );

  FRENSIE_CHECK_EQUAL( cross_section, 1.125904e3 );

  cross_section = nuclear_reaction->getCrossSection( 1.09375e-11 );

  FRENSIE_CHECK_EQUAL( cross_section, 1.109708e3 );

  cross_section = nuclear_reaction->getCrossSection( 1.90e1 );

  FRENSIE_CHECK_EQUAL( cross_section, 5.087783e-1 );

  cross_section = nuclear_reaction->getCrossSection( 1.95e1 );

  FRENSIE_CHECK_EQUAL( cross_section, 4.95463e-1 );

  cross_section = nuclear_reaction->getCrossSection( 2.0e1 );

  FRENSIE_CHECK_EQUAL( cross_section, 4.827462e-1 );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_basic_ace_file_name;
unsigned test_basic_ace_file_start_line;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_basic_ace_file",
                                        test_basic_ace_file_name, "",
                                        "Test basic ACE file name" );

  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_basic_ace_file_start_line",
                                        test_basic_ace_file_start_line, 1,
                                        "Test basic ACE file start line" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  std::unique_ptr<Data::ACEFileHandler> ace_file_handler(
                  new Data::ACEFileHandler( test_basic_ace_file_name,
                                            "1001.70c",
					    test_basic_ace_file_start_line ) );

  std::unique_ptr<Data::XSSNeutronDataExtractor> xss_data_extractor(
     new Data::XSSNeutronDataExtractor( ace_file_handler->getTableNXSArray(),
                                        ace_file_handler->getTableJXSArray(),
                                        ace_file_handler->getTableXSSArray()));

  std::shared_ptr<const std::vector<double> > energy_grid(
          new std::vector<double>( xss_data_extractor->extractEnergyGrid() ) );

  std::shared_ptr<const std::vector<double> > cross_section(
          new std::vector<double>( xss_data_extractor->extractElasticCrossSection() ) );

  nuclear_reaction.reset( new TestNeutronNuclearReaction(
                           energy_grid,
                           cross_section,
                           0u,
                           MonteCarlo::N__N_ELASTIC_REACTION,
                           0.0,
                           ace_file_handler->getTableTemperature().value() ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstNeutronNuclearReaction.cpp
//---------------------------------------------------------------------------//
