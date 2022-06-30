//---------------------------------------------------------------------------//
//!
//! \file   tstDecoupledPhotonProductionReactionACEFactory.cpp
//! \author Eli Moll
//! \brief  Nuclear reaction factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_DecoupledPhotonProductionReactionACEFactory.hpp"
#include "MonteCarlo_DecoupledPhotonProductionReaction.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<const Data::ACEFileHandler> o16_ace_file_handler;
std::shared_ptr<const Data::XSSNeutronDataExtractor> o16_xss_data_extractor;
std::shared_ptr<const std::vector<double> > o16_energy_grid;
std::shared_ptr<const Utility::HashBasedGridSearcher<double> > o16_energy_grid_searcher;

std::shared_ptr<const MonteCarlo::SimulationProperties> properties;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the factory can be constructed
FRENSIE_UNIT_TEST( DecoupledPhotonProductionReactionACEFactory, constructor )
{
  std::shared_ptr<MonteCarlo::DecoupledPhotonProductionReactionACEFactory>
    factory;

  FRENSIE_CHECK_NO_THROW( factory.reset(
                   new MonteCarlo::DecoupledPhotonProductionReactionACEFactory(
                           "o16_test_table",
                           o16_ace_file_handler->getTableAtomicWeightRatio(),
                           o16_ace_file_handler->getTableTemperature().value(),
                           o16_energy_grid,
                           o16_energy_grid_searcher,
                           *properties,
                           *o16_xss_data_extractor ) ) );
}

//---------------------------------------------------------------------------//
// Check that the photon production reactions can be created
FRENSIE_UNIT_TEST( NuclearReactionACEFactory_hydrogen,
                   createPhotonProductionReactions)
{
  std::shared_ptr<MonteCarlo::DecoupledPhotonProductionReactionACEFactory>
    factory( new MonteCarlo::DecoupledPhotonProductionReactionACEFactory(
                           "o16_test_table",
                           o16_ace_file_handler->getTableAtomicWeightRatio(),
                           o16_ace_file_handler->getTableTemperature().value(),
                           o16_energy_grid,
                           o16_energy_grid_searcher,
                           *properties,
                           *o16_xss_data_extractor ) );

  std::unordered_map<unsigned,std::shared_ptr<const MonteCarlo::DecoupledPhotonProductionReaction> > reactions;

  factory->createPhotonProductionReactions( reactions );

  FRENSIE_CHECK_EQUAL( reactions.size(), 131 );

  // Test the yield based reaction (102001)
  std::shared_ptr<const MonteCarlo::DecoupledPhotonProductionReaction>& yield_based_reaction_102001 =
    reactions.find( 102001u )->second;

  FRENSIE_CHECK_EQUAL( yield_based_reaction_102001->getReactionType(),
		       MonteCarlo::N__GAMMA_REACTION );
  FRENSIE_CHECK_EQUAL( yield_based_reaction_102001->getPhotonProductionReactionId(),
		       102001u );
  FRENSIE_CHECK_EQUAL( yield_based_reaction_102001->getCrossSection( 1.0e-11 ),
		       0.146*9.55754000000E-03 );

  // Test the XS based reaction (4001)
  std::shared_ptr<const MonteCarlo::DecoupledPhotonProductionReaction>& xs_based_reaction_4001 =
    reactions.find( 4001u )->second;

  FRENSIE_CHECK_EQUAL( xs_based_reaction_4001->getReactionType(),
		       MonteCarlo::N__N_INELASTIC_REACTION );
  FRENSIE_CHECK_EQUAL( xs_based_reaction_4001->getPhotonProductionReactionId(),
		       4001u );
  FRENSIE_CHECK_EQUAL( xs_based_reaction_4001->getThresholdEnergy(),
                       9.431376000000000204e+00 );
  FRENSIE_CHECK_EQUAL( xs_based_reaction_4001->getMaxEnergy(),
                       3.000000999999999962e+01 );
  FRENSIE_CHECK_SMALL( xs_based_reaction_4001->getCrossSection( xs_based_reaction_4001->getThresholdEnergy() ),
                       1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( xs_based_reaction_4001->getCrossSection( 9.43140000000E+00 ),
                                   4.461182999999999813e-11,
                                   1e-15 );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_o16_ace_file_name;
unsigned test_o16_ace_file_start_line;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_o16_ace_file",
                                        test_o16_ace_file_name, "",
                                        "Test o16 ACE file name" );
  
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_o16_ace_file_start_line",
                                        test_o16_ace_file_start_line, 1,
                                        "Test o16 ACE file start line" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create the O-16 file handler, data extractor and energy grid
  o16_ace_file_handler.reset(
                    new Data::ACEFileHandler( test_o16_ace_file_name,
                                              "8016.70c",
                                              test_o16_ace_file_start_line ) );

  o16_xss_data_extractor.reset( new Data::XSSNeutronDataExtractor(
                                  o16_ace_file_handler->getTableNXSArray(),
                                  o16_ace_file_handler->getTableJXSArray(),
                                  o16_ace_file_handler->getTableXSSArray() ) );

  o16_energy_grid.reset( new std::vector<double>( o16_xss_data_extractor->extractEnergyGrid() ) );

  o16_energy_grid_searcher.reset(
        new Utility::StandardHashBasedGridSearcher<std::vector<double>, false>(
                                              o16_energy_grid,
                                              o16_energy_grid->size()/100+1) );

  // Initialize the simulation properties
  properties.reset( new MonteCarlo::SimulationProperties );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstNuclearReactionACEFactory.cpp
//---------------------------------------------------------------------------//
