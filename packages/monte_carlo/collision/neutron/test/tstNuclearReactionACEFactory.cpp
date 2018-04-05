//---------------------------------------------------------------------------//
//!
//! \file   tstNuclearReactionACEFactory.cpp
//! \author Alex Robinson
//! \brief  Nuclear reaction factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_NuclearReactionACEFactory.hpp"
#include "MonteCarlo_NuclearReaction.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<const Data::ACEFileHandler> h1_ace_file_handler;
std::shared_ptr<const Data::XSSNeutronDataExtractor> h1_xss_data_extractor;
Teuchos::ArrayRCP<double> h1_energy_grid;

std::shared_ptr<const Data::ACEFileHandler> o16_ace_file_handler;
std::shared_ptr<const Data::XSSNeutronDataExtractor> o16_xss_data_extractor;
Teuchos::ArrayRCP<double> o16_energy_grid;

std::shared_ptr<const MonteCarlo::SimulationProperties> properties;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the factory can be constructed
TEUCHOS_UNIT_TEST( NuclearReactionACEFactory_h1, constructor )
{
  std::shared_ptr<MonteCarlo::NuclearReactionACEFactory> factory;
  
  TEST_NOTHROW( factory.reset( new MonteCarlo::NuclearReactionACEFactory(
                              "h1_test_table",
			      h1_ace_file_handler->getTableAtomicWeightRatio(),
			      h1_ace_file_handler->getTableTemperature(),
			      h1_energy_grid,
                              *properties,
			      *h1_xss_data_extractor ) ) );
}

//---------------------------------------------------------------------------//
// Check that the factory can be constructed
TEUCHOS_UNIT_TEST( NuclearReactionACEFactory_o16, constructor )
{
  std::shared_ptr<MonteCarlo::NuclearReactionACEFactory> factory;

  TEST_NOTHROW( factory.reset( new MonteCarlo::NuclearReactionACEFactory(
                             "o16_test_table",
                             o16_ace_file_handler->getTableAtomicWeightRatio(),
                             o16_ace_file_handler->getTableTemperature(),
                             o16_energy_grid,
                             *properties,
                             *o16_xss_data_extractor ) ) );
}

//---------------------------------------------------------------------------//
// Check that the scattering reaction can be created
TEUCHOS_UNIT_TEST( NuclearReactionACEFactory_h1, createScatteringReactions )
{
  std::shared_ptr<MonteCarlo::NuclearReactionACEFactory> factory(
                           new MonteCarlo::NuclearReactionACEFactory(
                              "h1_test_table",
			      h1_ace_file_handler->getTableAtomicWeightRatio(),
			      h1_ace_file_handler->getTableTemperature(),
			      h1_energy_grid,
                              *properties,
			      *h1_xss_data_extractor ) );
  
  boost::unordered_map<MonteCarlo::NuclearReactionType,
		       Teuchos::RCP<MonteCarlo::NuclearReaction> > reactions;

  factory->createScatteringReactions( reactions );

  TEST_EQUALITY_CONST( reactions.size(), 1 );

  Teuchos::RCP<MonteCarlo::NuclearReaction>& elastic_reaction =
    reactions.find( MonteCarlo::N__N_ELASTIC_REACTION )->second;

  TEST_EQUALITY_CONST( elastic_reaction->getReactionType(),
		       MonteCarlo::N__N_ELASTIC_REACTION );
  TEST_EQUALITY_CONST( elastic_reaction->getQValue(), 0.0 );
  TEST_EQUALITY_CONST( elastic_reaction->getNumberOfEmittedNeutrons( 0.0 ), 1);
  TEST_EQUALITY_CONST( elastic_reaction->getThresholdEnergy(), 1.0e-11 );
  TEST_EQUALITY_CONST( elastic_reaction->getCrossSection( 1.0e-11 ),
		       1.1605460e3 );
  TEST_EQUALITY_CONST( elastic_reaction->getCrossSection( 2.0e1 ),
		       4.827462e-1 );
}

//---------------------------------------------------------------------------//
// Check that the scattering reaction can be created
TEUCHOS_UNIT_TEST( NuclearReactionACEFactory_o16, createScatteringReactions )
{
  std::shared_ptr<MonteCarlo::NuclearReactionACEFactory> factory(
                           new MonteCarlo::NuclearReactionACEFactory(
                             "o16_test_table",
			     o16_ace_file_handler->getTableAtomicWeightRatio(),
                             o16_ace_file_handler->getTableTemperature(),
                             o16_energy_grid,
                             *properties,
                             *o16_xss_data_extractor ) );
  
  boost::unordered_map<MonteCarlo::NuclearReactionType,
		       Teuchos::RCP<MonteCarlo::NuclearReaction> > reactions;

  factory->createScatteringReactions( reactions );

  typedef boost::unordered_map<MonteCarlo::NuclearReactionType,
    Teuchos::RCP<MonteCarlo::NuclearReaction> >::const_iterator Reaction;

  TEST_EQUALITY_CONST( reactions.size(), 18 );

  Teuchos::RCP<MonteCarlo::NuclearReaction>& elastic_reaction =
    reactions.find( MonteCarlo::N__N_ELASTIC_REACTION )->second;

  TEST_EQUALITY_CONST( elastic_reaction->getReactionType(),
		       MonteCarlo::N__N_ELASTIC_REACTION );
  TEST_EQUALITY_CONST( elastic_reaction->getQValue(), 0.0 );
  TEST_EQUALITY_CONST( elastic_reaction->getNumberOfEmittedNeutrons( 0.0 ), 1);
  TEST_EQUALITY_CONST( elastic_reaction->getThresholdEnergy(), 1.0e-11 );
  TEST_EQUALITY_CONST( elastic_reaction->getCrossSection( 1.0e-11 ),
		       5.50078400000e+01 );
  TEST_EQUALITY_CONST( elastic_reaction->getCrossSection( 150.0 ),
		       1.48000000000e-01 );

  Teuchos::RCP<MonteCarlo::NuclearReaction>& inelastic_level_1_reaction =
    reactions.find( MonteCarlo::N__N_EXCITED_STATE_1_REACTION )->second;
  TEST_EQUALITY_CONST( inelastic_level_1_reaction->getQValue(),
		       -6.04940000000e+00 );
  TEST_EQUALITY_CONST(
		 inelastic_level_1_reaction->getNumberOfEmittedNeutrons( 0.0 ),
		 1 );
  TEST_EQUALITY_CONST( inelastic_level_1_reaction->getThresholdEnergy(),
		       6.43088600000e+00 );
  TEST_EQUALITY_CONST(
		      inelastic_level_1_reaction->getCrossSection( 1.0e-11 ),
		      0.0 );
  TEST_EQUALITY_CONST( inelastic_level_1_reaction->getCrossSection( 7.0 ),
		       1.022538000000e-03 );
  TEST_EQUALITY_CONST( inelastic_level_1_reaction->getCrossSection( 150.0 ),
		       0.0 );

  Teuchos::RCP<MonteCarlo::NuclearReaction>& inelastic_continuum_reaction =
    reactions.find( MonteCarlo::N__N_CONTINUUM_REACTION )->second;
  TEST_EQUALITY_CONST( inelastic_continuum_reaction->getQValue(),
		       -9.58500000000e+00 );
  TEST_EQUALITY_CONST(
	       inelastic_continuum_reaction->getNumberOfEmittedNeutrons( 0.0 ),
	       1);
  TEST_EQUALITY_CONST( inelastic_continuum_reaction->getThresholdEnergy(),
		       1.01894600000e+01 );
  TEST_EQUALITY_CONST(
	    inelastic_continuum_reaction->getCrossSection( 1.01894600000e+01 ),
	    0.0 );
  TEST_EQUALITY_CONST( inelastic_continuum_reaction->getCrossSection( 150.0 ),
		       0.0 );
}

//---------------------------------------------------------------------------//
// Check that the absorption reactions can be created
TEUCHOS_UNIT_TEST( NuclearReactionACEFactory_h1, createAbsorptionReactions )
{
  std::shared_ptr<MonteCarlo::NuclearReactionACEFactory> factory(
                           new MonteCarlo::NuclearReactionACEFactory(
                              "h1_test_table",
			      h1_ace_file_handler->getTableAtomicWeightRatio(),
			      h1_ace_file_handler->getTableTemperature(),
			      h1_energy_grid,
                              *properties,
			      *h1_xss_data_extractor ) );
  
  boost::unordered_map<MonteCarlo::NuclearReactionType,
		       Teuchos::RCP<MonteCarlo::NuclearReaction> > reactions;

  factory->createAbsorptionReactions( reactions );

  TEST_EQUALITY_CONST( reactions.size(), 3 );

  Teuchos::RCP<MonteCarlo::NuclearReaction>& n_gamma_reaction =
    reactions.find( MonteCarlo::N__GAMMA_REACTION )->second;

  TEST_EQUALITY_CONST( n_gamma_reaction->getReactionType(),
		       MonteCarlo::N__GAMMA_REACTION );
  TEST_EQUALITY_CONST( n_gamma_reaction->getQValue(), 2.224631 );
  TEST_EQUALITY_CONST( n_gamma_reaction->getNumberOfEmittedNeutrons( 0.0 ), 0);
  TEST_EQUALITY_CONST( n_gamma_reaction->getThresholdEnergy(), 1.0e-11 );
  TEST_EQUALITY_CONST( n_gamma_reaction->getCrossSection( 1.0e-11 ),
		       1.670111e1 );
  TEST_EQUALITY_CONST( n_gamma_reaction->getCrossSection( 2.0e1 ),
		       2.722354e-5 );

  Teuchos::RCP<MonteCarlo::NuclearReaction>& d_production_reaction =
    reactions.find( MonteCarlo::N__TOTAL_D_PRODUCTION )->second;

  TEST_EQUALITY_CONST( d_production_reaction->getReactionType(),
		       MonteCarlo::N__TOTAL_D_PRODUCTION );
  TEST_EQUALITY_CONST( d_production_reaction->getQValue(), 0.0 );
  TEST_EQUALITY_CONST( d_production_reaction->getNumberOfEmittedNeutrons(0.0),
		       0 );
  TEST_EQUALITY_CONST( d_production_reaction->getThresholdEnergy(), 1.0e-11 );
  TEST_EQUALITY_CONST( d_production_reaction->getCrossSection( 1.0e-11 ),
		       1.670111e1 );
  TEST_EQUALITY_CONST( d_production_reaction->getCrossSection( 2.0e1 ),
		       2.722354e-5 );

  Teuchos::RCP<MonteCarlo::NuclearReaction>& dpa_reaction =
    reactions.find( MonteCarlo::N__DPA )->second;

  TEST_EQUALITY_CONST( dpa_reaction->getReactionType(),
		       MonteCarlo::N__DPA );
  TEST_EQUALITY_CONST( dpa_reaction->getQValue(), 0.0 );
  TEST_EQUALITY_CONST( dpa_reaction->getNumberOfEmittedNeutrons( 0.0 ), 0 );
  TEST_EQUALITY_CONST( dpa_reaction->getThresholdEnergy(), 2.375e-05);
  TEST_EQUALITY_CONST( dpa_reaction->getCrossSection( 2.375e-05 ), 0.0 );
  TEST_EQUALITY_CONST( dpa_reaction->getCrossSection( 2.0e1 ), 3.067696e-04 );
}

//---------------------------------------------------------------------------//
// Check that the absorption reactions can be created
TEUCHOS_UNIT_TEST( NuclearReactionACEFactory_o16, createAbsorptionReactions )
{
  std::shared_ptr<MonteCarlo::NuclearReactionACEFactory> factory(
                           new MonteCarlo::NuclearReactionACEFactory(
                             "o16_test_table",
			     o16_ace_file_handler->getTableAtomicWeightRatio(),
                             o16_ace_file_handler->getTableTemperature(),
                             o16_energy_grid,
                             *properties,
                             *o16_xss_data_extractor ) );
  
  boost::unordered_map<MonteCarlo::NuclearReactionType,
		       Teuchos::RCP<MonteCarlo::NuclearReaction> > reactions;

  factory->createAbsorptionReactions( reactions );

  typedef boost::unordered_map<MonteCarlo::NuclearReactionType,
    Teuchos::RCP<MonteCarlo::NuclearReaction> >::const_iterator Reaction;

  TEST_EQUALITY_CONST( reactions.size(), 51 );

  Teuchos::RCP<MonteCarlo::NuclearReaction>& n_gamma_reaction =
    reactions.find( MonteCarlo::N__GAMMA_REACTION )->second;

  TEST_EQUALITY_CONST( n_gamma_reaction->getReactionType(),
		       MonteCarlo::N__GAMMA_REACTION );
  TEST_EQUALITY_CONST( n_gamma_reaction->getQValue(), 4.14342300000e+00 );
  TEST_EQUALITY_CONST( n_gamma_reaction->getNumberOfEmittedNeutrons( 0.0 ), 0);
  TEST_EQUALITY_CONST( n_gamma_reaction->getThresholdEnergy(), 1.0e-11 );
  TEST_EQUALITY_CONST( n_gamma_reaction->getCrossSection( 1.0e-11 ),
		       9.55754000000e-03 );
  TEST_EQUALITY_CONST( n_gamma_reaction->getCrossSection( 150.0 ), 0.0 );

 Teuchos::RCP<MonteCarlo::NuclearReaction>& n_alpha_ex_3_reaction =
    reactions.find( MonteCarlo::N__ALPHA_EXCITED_STATE_3_REACTION )->second;

  TEST_EQUALITY_CONST( n_alpha_ex_3_reaction->getReactionType(),
		       MonteCarlo::N__ALPHA_EXCITED_STATE_3_REACTION );
  TEST_EQUALITY_CONST( n_alpha_ex_3_reaction->getQValue(), -6.06940000000e+00);
  TEST_EQUALITY_CONST(n_alpha_ex_3_reaction->getNumberOfEmittedNeutrons( 0.0 ),
		      0);
  TEST_EQUALITY_CONST( n_alpha_ex_3_reaction->getThresholdEnergy(),
		       6.45214700000e+00 );
  TEST_EQUALITY_CONST( n_alpha_ex_3_reaction->getCrossSection( 1.0e-11 ),
		       0.0 );
  TEST_EQUALITY_CONST( n_alpha_ex_3_reaction->getCrossSection( 150.0 ),
		       0.0 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_h1_ace_file_name;
std::string test_h1_ace_table_name;
std::string test_o16_ace_file_name;
std::string test_o16_ace_table_name;
// std::string test_fission_ace_file_name;
// std::string test_ptable_ace_file_name;
// std::string test_fission_ptable_ace_file_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_h1_ace_file",
		 &test_h1_ace_file_name,
		 "Test h1 ACE file name" );
  clp().setOption( "test_h1_ace_table",
		 &test_h1_ace_table_name,
		 "Test ACE table name in h1 ACE file" );

  clp().setOption( "test_o16_ace_file",
		 &test_o16_ace_file_name,
		 "Test o16 ACE file name" );
  clp().setOption( "test_o16_ace_table",
		 &test_o16_ace_table_name,
		 "Test ACE table name in o16 ACE file" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Create the H-1 file handler, data extractor and energy grid
  h1_ace_file_handler.reset( new Data::ACEFileHandler( test_h1_ace_file_name,
                                                       test_h1_ace_table_name,
                                                       1u ) );

  h1_xss_data_extractor.reset( new Data::XSSNeutronDataExtractor(
                                   h1_ace_file_handler->getTableNXSArray(),
                                   h1_ace_file_handler->getTableJXSArray(),
				   h1_ace_file_handler->getTableXSSArray() ) );

  h1_energy_grid.deepCopy( h1_xss_data_extractor->extractEnergyGrid() );
  
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
