//---------------------------------------------------------------------------//
//!
//! \file   tstNeutronNuclearReactionACEFactory.cpp
//! \author Alex Robinson
//! \brief  Nuclear reaction factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_NeutronNuclearReactionACEFactory.hpp"
#include "MonteCarlo_NeutronNuclearReaction.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<const Data::ACEFileHandler> h1_ace_file_handler;
std::shared_ptr<const Data::XSSNeutronDataExtractor> h1_xss_data_extractor;
std::shared_ptr<const std::vector<double> > h1_energy_grid;
std::shared_ptr<const Utility::HashBasedGridSearcher<double> > h1_energy_grid_searcher;

std::shared_ptr<const Data::ACEFileHandler> o16_ace_file_handler;
std::shared_ptr<const Data::XSSNeutronDataExtractor> o16_xss_data_extractor;
std::shared_ptr<const std::vector<double> > o16_energy_grid;
std::shared_ptr<const Utility::HashBasedGridSearcher<double> > o16_energy_grid_searcher;

std::shared_ptr<const MonteCarlo::SimulationProperties> properties;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the factory can be constructed
FRENSIE_UNIT_TEST( NeutronNuclearReactionACEFactory_h1, constructor )
{
  std::shared_ptr<MonteCarlo::NeutronNuclearReactionACEFactory> factory;

  FRENSIE_CHECK_NO_THROW( factory.reset( new MonteCarlo::NeutronNuclearReactionACEFactory(
                            "h1_test_table",
                            h1_ace_file_handler->getTableAtomicWeightRatio(),
			    h1_ace_file_handler->getTableTemperature().value(),
                            h1_energy_grid,
                            h1_energy_grid_searcher,
                            *properties,
                            *h1_xss_data_extractor ) ) );
}

//---------------------------------------------------------------------------//
// Check that the factory can be constructed
FRENSIE_UNIT_TEST( NeutronNuclearReactionACEFactory_o16, constructor )
{
  std::shared_ptr<MonteCarlo::NeutronNuclearReactionACEFactory> factory;

  FRENSIE_CHECK_NO_THROW( factory.reset( new MonteCarlo::NeutronNuclearReactionACEFactory(
                           "o16_test_table",
                           o16_ace_file_handler->getTableAtomicWeightRatio(),
                           o16_ace_file_handler->getTableTemperature().value(),
                           o16_energy_grid,
                           o16_energy_grid_searcher,
                           *properties,
                           *o16_xss_data_extractor ) ) );
}

//---------------------------------------------------------------------------//
// Check that the scattering reaction can be created
FRENSIE_UNIT_TEST( NeutronNuclearReactionACEFactory_h1, createScatteringReactions )
{
  std::shared_ptr<MonteCarlo::NeutronNuclearReactionACEFactory> factory(
                         new MonteCarlo::NeutronNuclearReactionACEFactory(
                            "h1_test_table",
                            h1_ace_file_handler->getTableAtomicWeightRatio(),
			    h1_ace_file_handler->getTableTemperature().value(),
                            h1_energy_grid,
                            h1_energy_grid_searcher,
                            *properties,
                            *h1_xss_data_extractor ) );

  std::unordered_map<MonteCarlo::NuclearReactionType,std::shared_ptr< MonteCarlo::NeutronNuclearReaction> > reactions;
  factory->createScatteringReactions( reactions );

  FRENSIE_CHECK_EQUAL( reactions.size(), 1 );

  std::shared_ptr<MonteCarlo::NeutronNuclearReaction>& elastic_reaction =
    reactions.find( MonteCarlo::N__N_ELASTIC_REACTION )->second;

  FRENSIE_CHECK_EQUAL( elastic_reaction->getReactionType(),
		       MonteCarlo::N__N_ELASTIC_REACTION );
  FRENSIE_CHECK_EQUAL( elastic_reaction->getQValue(), 0.0 );
  FRENSIE_CHECK_EQUAL( elastic_reaction->getNumberOfEmittedParticles( 0.0 ), 1);
  FRENSIE_CHECK_EQUAL( elastic_reaction->getThresholdEnergy(), 1.0e-11 );
  FRENSIE_CHECK_EQUAL( elastic_reaction->getCrossSection( 1.0e-11 ),
		       1.1605460e3 );
  FRENSIE_CHECK_EQUAL( elastic_reaction->getCrossSection( 2.0e1 ),
		       4.827462e-1 );
}

//---------------------------------------------------------------------------//
// Check that the scattering reaction can be created
FRENSIE_UNIT_TEST( NeutronNuclearReactionACEFactory_o16, createScatteringReactions )
{
  std::shared_ptr<MonteCarlo::NeutronNuclearReactionACEFactory> factory(
                         new MonteCarlo::NeutronNuclearReactionACEFactory(
                           "o16_test_table",
                           o16_ace_file_handler->getTableAtomicWeightRatio(),
                           o16_ace_file_handler->getTableTemperature().value(),
                           o16_energy_grid,
                           o16_energy_grid_searcher,
                           *properties,
                           *o16_xss_data_extractor ) );

  std::unordered_map<MonteCarlo::NuclearReactionType,std::shared_ptr< MonteCarlo::NeutronNuclearReaction> > reactions;

  factory->createScatteringReactions( reactions );

  typedef std::unordered_map<MonteCarlo::NuclearReactionType,std::shared_ptr<MonteCarlo::NeutronNuclearReaction> >::const_iterator Reaction;

  FRENSIE_CHECK_EQUAL( reactions.size(), 18 );

  std::shared_ptr<MonteCarlo::NeutronNuclearReaction>& elastic_reaction =
    reactions.find( MonteCarlo::N__N_ELASTIC_REACTION )->second;

  FRENSIE_CHECK_EQUAL( elastic_reaction->getReactionType(),
		       MonteCarlo::N__N_ELASTIC_REACTION );
  FRENSIE_CHECK_EQUAL( elastic_reaction->getQValue(), 0.0 );
  FRENSIE_CHECK_EQUAL( elastic_reaction->getNumberOfEmittedParticles( 0.0 ), 1);
  FRENSIE_CHECK_EQUAL( elastic_reaction->getThresholdEnergy(), 1.0e-11 );
  FRENSIE_CHECK_EQUAL( elastic_reaction->getCrossSection( 1.0e-11 ),
		       5.50078400000e+01 );
  FRENSIE_CHECK_EQUAL( elastic_reaction->getCrossSection( 150.0 ),
		       1.48000000000e-01 );

  std::shared_ptr<MonteCarlo::NeutronNuclearReaction>& inelastic_level_1_reaction =
    reactions.find( MonteCarlo::N__N_EXCITED_STATE_1_REACTION )->second;
  FRENSIE_CHECK_EQUAL( inelastic_level_1_reaction->getQValue(),
		       -6.04940000000e+00 );
  FRENSIE_CHECK_EQUAL(
		 inelastic_level_1_reaction->getNumberOfEmittedParticles( 0.0 ),
		 1 );
  FRENSIE_CHECK_EQUAL( inelastic_level_1_reaction->getThresholdEnergy(),
		       6.43088600000e+00 );
  FRENSIE_CHECK_EQUAL(
		      inelastic_level_1_reaction->getCrossSection( 1.0e-11 ),
		      0.0 );
  FRENSIE_CHECK_EQUAL( inelastic_level_1_reaction->getCrossSection( 7.0 ),
		       1.022538000000e-03 );
  FRENSIE_CHECK_EQUAL( inelastic_level_1_reaction->getCrossSection( 150.0 ),
		       0.0 );

  std::shared_ptr<MonteCarlo::NeutronNuclearReaction>& inelastic_continuum_reaction =
    reactions.find( MonteCarlo::N__N_CONTINUUM_REACTION )->second;
  FRENSIE_CHECK_EQUAL( inelastic_continuum_reaction->getQValue(),
		       -9.58500000000e+00 );
  FRENSIE_CHECK_EQUAL(
	       inelastic_continuum_reaction->getNumberOfEmittedParticles( 0.0 ),
	       1);
  FRENSIE_CHECK_EQUAL( inelastic_continuum_reaction->getThresholdEnergy(),
		       1.01894600000e+01 );
  FRENSIE_CHECK_EQUAL(
	    inelastic_continuum_reaction->getCrossSection( 1.01894600000e+01 ),
	    0.0 );
  FRENSIE_CHECK_EQUAL( inelastic_continuum_reaction->getCrossSection( 150.0 ),
		       0.0 );
}

//---------------------------------------------------------------------------//
// Check that the absorption reactions can be created
FRENSIE_UNIT_TEST( NeutronNuclearReactionACEFactory_h1, createAbsorptionReactions )
{
  std::shared_ptr<MonteCarlo::NeutronNuclearReactionACEFactory> factory(
                         new MonteCarlo::NeutronNuclearReactionACEFactory(
                            "h1_test_table",
                            h1_ace_file_handler->getTableAtomicWeightRatio(),
                            h1_ace_file_handler->getTableTemperature().value(),
                            h1_energy_grid,
                            h1_energy_grid_searcher,
                            *properties,
                            *h1_xss_data_extractor ) );

  std::unordered_map<MonteCarlo::NuclearReactionType,std::shared_ptr<MonteCarlo::NeutronNuclearReaction> > reactions;

  factory->createAbsorptionReactions( reactions );

  FRENSIE_CHECK_EQUAL( reactions.size(), 3 );

  std::shared_ptr< MonteCarlo::NeutronNuclearReaction>& n_gamma_reaction =
    reactions.find( MonteCarlo::N__GAMMA_REACTION )->second;

  FRENSIE_CHECK_EQUAL( n_gamma_reaction->getReactionType(),
		       MonteCarlo::N__GAMMA_REACTION );
  FRENSIE_CHECK_EQUAL( n_gamma_reaction->getQValue(), 2.224631 );
  FRENSIE_CHECK_EQUAL( n_gamma_reaction->getNumberOfEmittedParticles( 0.0 ), 0);
  FRENSIE_CHECK_EQUAL( n_gamma_reaction->getThresholdEnergy(), 1.0e-11 );
  FRENSIE_CHECK_EQUAL( n_gamma_reaction->getCrossSection( 1.0e-11 ),
		       1.670111e1 );
  FRENSIE_CHECK_EQUAL( n_gamma_reaction->getCrossSection( 2.0e1 ),
		       2.722354e-5 );

  std::shared_ptr< MonteCarlo::NeutronNuclearReaction>& d_production_reaction =
    reactions.find( MonteCarlo::N__TOTAL_D_PRODUCTION )->second;

  FRENSIE_CHECK_EQUAL( d_production_reaction->getReactionType(),
		       MonteCarlo::N__TOTAL_D_PRODUCTION );
  FRENSIE_CHECK_EQUAL( d_production_reaction->getQValue(), 0.0 );
  FRENSIE_CHECK_EQUAL( d_production_reaction->getNumberOfEmittedParticles(0.0),
		       0 );
  FRENSIE_CHECK_EQUAL( d_production_reaction->getThresholdEnergy(), 1.0e-11 );
  FRENSIE_CHECK_EQUAL( d_production_reaction->getCrossSection( 1.0e-11 ),
		       1.670111e1 );
  FRENSIE_CHECK_EQUAL( d_production_reaction->getCrossSection( 2.0e1 ),
		       2.722354e-5 );

  std::shared_ptr< MonteCarlo::NeutronNuclearReaction>& dpa_reaction =
    reactions.find( MonteCarlo::N__DAMAGE )->second;

  FRENSIE_CHECK_EQUAL( dpa_reaction->getReactionType(),
		       MonteCarlo::N__DAMAGE );
  FRENSIE_CHECK_EQUAL( dpa_reaction->getQValue(), 0.0 );
  FRENSIE_CHECK_EQUAL( dpa_reaction->getNumberOfEmittedParticles( 0.0 ), 0 );
  FRENSIE_CHECK_EQUAL( dpa_reaction->getThresholdEnergy(), 2.375e-05);
  FRENSIE_CHECK_EQUAL( dpa_reaction->getCrossSection( 2.375e-05 ), 0.0 );
  FRENSIE_CHECK_EQUAL( dpa_reaction->getCrossSection( 2.0e1 ), 3.067696e-04 );
}

//---------------------------------------------------------------------------//
// Check that the absorption reactions can be created
FRENSIE_UNIT_TEST( NeutronNuclearReactionACEFactory_o16, createAbsorptionReactions )
{
  std::shared_ptr<MonteCarlo::NeutronNuclearReactionACEFactory> factory(
                         new MonteCarlo::NeutronNuclearReactionACEFactory(
                           "o16_test_table",
                           o16_ace_file_handler->getTableAtomicWeightRatio(),
                           o16_ace_file_handler->getTableTemperature().value(),
                           o16_energy_grid,
                           o16_energy_grid_searcher,
                           *properties,
                           *o16_xss_data_extractor ) );

  std::unordered_map<MonteCarlo::NuclearReactionType,std::shared_ptr< MonteCarlo::NeutronNuclearReaction> > reactions;

  factory->createAbsorptionReactions( reactions );

  typedef std::unordered_map<MonteCarlo::NuclearReactionType,std::shared_ptr< MonteCarlo::NeutronNuclearReaction> >::const_iterator Reaction;

  FRENSIE_CHECK_EQUAL( reactions.size(), 51 );

  std::shared_ptr< MonteCarlo::NeutronNuclearReaction>& n_gamma_reaction =
    reactions.find( MonteCarlo::N__GAMMA_REACTION )->second;

  FRENSIE_CHECK_EQUAL( n_gamma_reaction->getReactionType(),
		       MonteCarlo::N__GAMMA_REACTION );
  FRENSIE_CHECK_EQUAL( n_gamma_reaction->getQValue(), 4.14342300000e+00 );
  FRENSIE_CHECK_EQUAL( n_gamma_reaction->getNumberOfEmittedParticles( 0.0 ), 0);
  FRENSIE_CHECK_EQUAL( n_gamma_reaction->getThresholdEnergy(), 1.0e-11 );
  FRENSIE_CHECK_EQUAL( n_gamma_reaction->getCrossSection( 1.0e-11 ),
		       9.55754000000e-03 );
  FRENSIE_CHECK_EQUAL( n_gamma_reaction->getCrossSection( 150.0 ), 0.0 );

 std::shared_ptr< MonteCarlo::NeutronNuclearReaction>& n_alpha_ex_3_reaction =
    reactions.find( MonteCarlo::N__ALPHA_EXCITED_STATE_3_REACTION )->second;

  FRENSIE_CHECK_EQUAL( n_alpha_ex_3_reaction->getReactionType(),
		       MonteCarlo::N__ALPHA_EXCITED_STATE_3_REACTION );
  FRENSIE_CHECK_EQUAL( n_alpha_ex_3_reaction->getQValue(), -6.06940000000e+00);
  FRENSIE_CHECK_EQUAL(n_alpha_ex_3_reaction->getNumberOfEmittedParticles( 0.0 ),
		      0);
  FRENSIE_CHECK_EQUAL( n_alpha_ex_3_reaction->getThresholdEnergy(),
		       6.45214700000e+00 );
  FRENSIE_CHECK_EQUAL( n_alpha_ex_3_reaction->getCrossSection( 1.0e-11 ),
		       0.0 );
  FRENSIE_CHECK_EQUAL( n_alpha_ex_3_reaction->getCrossSection( 150.0 ),
		       0.0 );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_h1_ace_file_name, test_o16_ace_file_name;
unsigned test_h1_ace_file_start_line, test_o16_ace_file_start_line;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_h1_ace_file",
                                         test_h1_ace_file_name, "",
                                         "Test h1 ACE file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_h1_ace_file_start_line",
                                         test_h1_ace_file_start_line, 1,
                                         "Test h1 ACE file start line" );

  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_o16_ace_file",
                                        test_o16_ace_file_name, "",
                                        "Test o16 ACE file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_o16_ace_file_start_line",
                                        test_o16_ace_file_start_line, 1,
                                        "Test o16 ACE file start line" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create the H-1 file handler, data extractor and energy grid
  h1_ace_file_handler.reset(
                     new Data::ACEFileHandler( test_h1_ace_file_name,
                                               "1001.70c",
                                               test_h1_ace_file_start_line ) );

  h1_xss_data_extractor.reset( new Data::XSSNeutronDataExtractor(
                                   h1_ace_file_handler->getTableNXSArray(),
                                   h1_ace_file_handler->getTableJXSArray(),
				   h1_ace_file_handler->getTableXSSArray() ) );

  h1_energy_grid.reset(
       new std::vector<double>( h1_xss_data_extractor->extractEnergyGrid() ) );

  h1_energy_grid_searcher.reset(
        new Utility::StandardHashBasedGridSearcher<std::vector<double>, false>(
                                               h1_energy_grid,
                                               h1_energy_grid->size()/100+1) );

  // Create the O-16 file handler, data extractor and energy grid
  o16_ace_file_handler.reset(
                    new Data::ACEFileHandler( test_o16_ace_file_name,
                                              "8016.70c",
                                              test_o16_ace_file_start_line ) );

  o16_xss_data_extractor.reset( new Data::XSSNeutronDataExtractor(
                                  o16_ace_file_handler->getTableNXSArray(),
                                  o16_ace_file_handler->getTableJXSArray(),
                                  o16_ace_file_handler->getTableXSSArray() ) );

  o16_energy_grid.reset(
      new std::vector<double>( o16_xss_data_extractor->extractEnergyGrid() ) );

  o16_energy_grid_searcher.reset(
        new Utility::StandardHashBasedGridSearcher<std::vector<double>, false>(
                                              o16_energy_grid,
                                              o16_energy_grid->size()/100+1) );

  // Initialize the simulation properties
  properties.reset( new MonteCarlo::SimulationProperties );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstNeutronNuclearReactionACEFactory.cpp
//---------------------------------------------------------------------------//
