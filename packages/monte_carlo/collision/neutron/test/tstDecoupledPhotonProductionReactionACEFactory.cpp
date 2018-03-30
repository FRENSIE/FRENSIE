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

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_DecoupledPhotonProductionReactionACEFactory.hpp"
#include "MonteCarlo_DecoupledPhotonProductionReaction.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<const Data::ACEFileHandler> o16_ace_file_handler;
std::shared_ptr<const Data::XSSNeutronDataExtractor> o16_xss_data_extractor;
Teuchos::ArrayRCP<double> o16_energy_grid;

std::shared_ptr<const MonteCarlo::SimulationProperties> properties;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the factory can be constructed
TEUCHOS_UNIT_TEST( DecoupledPhotonProductionReactionACEFactory, constructor )
{
  std::shared_ptr<MonteCarlo::DecoupledPhotonProductionReactionACEFactory>
    factory;
  
  TEST_NOTHROW( factory.reset(
                   new MonteCarlo::DecoupledPhotonProductionReactionACEFactory(
                             "o16_test_table",
                             o16_ace_file_handler->getTableAtomicWeightRatio(),
                             o16_ace_file_handler->getTableTemperature(),
                             o16_energy_grid,
                             *properties,
                             *o16_xss_data_extractor ) ) );
}

//---------------------------------------------------------------------------//
// Check that the photon production reactions can be created
TEUCHOS_UNIT_TEST( NuclearReactionACEFactory_hydrogen,
                   createPhotonProductionReactions)
{
  std::shared_ptr<MonteCarlo::DecoupledPhotonProductionReactionACEFactory>
    factory( new MonteCarlo::DecoupledPhotonProductionReactionACEFactory(
                             "o16_test_table",
                             o16_ace_file_handler->getTableAtomicWeightRatio(),
                             o16_ace_file_handler->getTableTemperature(),
                             o16_energy_grid,
                             *properties,
                             *o16_xss_data_extractor ) );

  boost::unordered_map<unsigned,
                     Teuchos::RCP<MonteCarlo::DecoupledPhotonProductionReaction> > reactions;

  factory->createPhotonProductionReactions( reactions );

  TEST_EQUALITY_CONST( reactions.size(), 131 );

  // Test the yield based reaction (102001)
  Teuchos::RCP<MonteCarlo::DecoupledPhotonProductionReaction>& yield_based_reaction_102001 =
    reactions.find( 102001u )->second;

  TEST_EQUALITY_CONST( yield_based_reaction_102001->getBaseReactionType(),
		       MonteCarlo::N__GAMMA_REACTION );
  TEST_EQUALITY_CONST( yield_based_reaction_102001->getPhotonProductionReactionId(),
		       102001u );
  TEST_EQUALITY_CONST( yield_based_reaction_102001->getCrossSection( 1.0e-11 ),
		       0.146*9.55754000000E-03 );

  // Test the XS based reaction (4001)
  Teuchos::RCP<MonteCarlo::DecoupledPhotonProductionReaction>& xs_based_reaction_4001 =
    reactions.find( 4001u )->second;

  TEST_EQUALITY_CONST( xs_based_reaction_4001->getBaseReactionType(),
		       MonteCarlo::N__N_INELASTIC_REACTION );
  TEST_EQUALITY_CONST( xs_based_reaction_4001->getPhotonProductionReactionId(),
		       4001u );
  TEST_EQUALITY_CONST( xs_based_reaction_4001->getCrossSection( 9.43140000000E+00 ),
		       1.85882800000E-12 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_o16_ace_file_name;
std::string test_o16_ace_table_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_o16_ace_file",
                   &test_o16_ace_file_name,
                   "Test o16 ACE file name" );
  clp().setOption( "test_o16_ace_table",
                   &test_o16_ace_table_name,
                   "Test ACE table name in o16 ACE file" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Create the O-16 file handler, data extractor and energy grid
  o16_ace_file_handler.reset( new Data::ACEFileHandler(test_o16_ace_file_name,
                                                       test_o16_ace_table_name,
                                                       1u ) );

  o16_xss_data_extractor.reset( new Data::XSSNeutronDataExtractor(
                                  o16_ace_file_handler->getTableNXSArray(),
                                  o16_ace_file_handler->getTableJXSArray(),
                                  o16_ace_file_handler->getTableXSSArray() ) );

  o16_energy_grid.deepCopy( o16_xss_data_extractor->extractEnergyGrid() );

  // Initialize the simulation properties
  properties.reset( new MonteCarlo::SimulationProperties );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstNuclearReactionACEFactory.cpp
//---------------------------------------------------------------------------//
