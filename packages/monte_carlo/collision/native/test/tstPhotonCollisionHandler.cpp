//---------------------------------------------------------------------------//
//!
//! \file   tstPhotonCollisionHandler.cpp
//! \author Alex Robinson
//! \brief  Photon collision handler class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhotoatomFactory.hpp"
#include "MonteCarlo_PhotonMaterial.hpp"
#include "MonteCarlo_PhotonCollisionHandler.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<const MonteCarlo::PhotonMaterial> lead;
std::shared_ptr<MonteCarlo::PhotonCollisionHandler> collision_handler;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that materials can be added to the collision handler
TEUCHOS_UNIT_TEST( PhotonCollisionHandler, addMaterial )
{
  TEST_ASSERT( collision_handler->isCellVoid( 1 ) );
  TEST_ASSERT( collision_handler->isCellVoid( 2 ) );
  TEST_ASSERT( collision_handler->isCellVoid( 3 ) );

  Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>
    cells_containing_material( 3 );
  cells_containing_material[0] = 1;
  cells_containing_material[1] = 2;
  cells_containing_material[2] = 3;

  collision_handler->addMaterial( lead, cells_containing_material );

  TEST_ASSERT( !collision_handler->isCellVoid( 1 ) );
  TEST_ASSERT( !collision_handler->isCellVoid( 2 ) );
  TEST_ASSERT( !collision_handler->isCellVoid( 3 ) );
}

//---------------------------------------------------------------------------//
// Check that a material contained in a cell can be retrieved
TEUCHOS_UNIT_TEST( PhotonCollisionHandler, getMaterial )
{
  Teuchos::RCP<const MonteCarlo::PhotonMaterial> cell_material =
    collision_handler->getMaterial( 1 );

  TEST_ASSERT( !cell_material.is_null() );
  TEST_EQUALITY_CONST( cell_material->getId(), 0 );
  TEST_EQUALITY_CONST( cell_material, lead );

  cell_material = collision_handler->getMaterial( 2 );

  TEST_ASSERT( !cell_material.is_null() );
  TEST_EQUALITY_CONST( cell_material->getId(), 0 );
  TEST_EQUALITY_CONST( cell_material, lead );

  cell_material = collision_handler->getMaterial( 3 );

  TEST_ASSERT( !cell_material.is_null() );
  TEST_EQUALITY_CONST( cell_material->getId(), 0 );
  TEST_EQUALITY_CONST( cell_material, lead );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic total cross section in a cell can be retrieved
TEUCHOS_UNIT_TEST( PhotonCollisionHandler, getMacroscopicTotalCrossSection )
{
  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 1.0000000000042743e-06 );
  photon.setCell( 1 );

  double cross_section =
    collision_handler->getMacroscopicTotalCrossSection( photon );

  TEST_FLOATING_EQUALITY( cross_section, 1.823831998305667e-05, 1e-12 );

  photon.setEnergy( 99999.99999997711 );

  cross_section =
    collision_handler->getMacroscopicTotalCrossSection( photon );

  TEST_FLOATING_EQUALITY( cross_section, 0.11970087585747362, 1e-12 );

  photon.setCell( 2 );
  photon.setEnergy( 1.0000000000042743e-06 );

  cross_section =
    collision_handler->getMacroscopicTotalCrossSection( photon );

  TEST_FLOATING_EQUALITY( cross_section, 1.823831998305667e-05, 1e-12 );

  photon.setEnergy( 99999.99999997711 );

  cross_section =
    collision_handler->getMacroscopicTotalCrossSection( photon );

  TEST_FLOATING_EQUALITY( cross_section, 0.11970087585747362, 1e-12 );

  photon.setCell( 3 );
  photon.setEnergy( 1.0000000000042743e-06 );

  cross_section =
    collision_handler->getMacroscopicTotalCrossSection( photon );

  TEST_FLOATING_EQUALITY( cross_section, 1.823831998305667e-05, 1e-12 );

  photon.setEnergy( 99999.99999997711 );

  cross_section =
    collision_handler->getMacroscopicTotalCrossSection( photon );

  TEST_FLOATING_EQUALITY( cross_section, 0.11970087585747362, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic total forward cross section in a cell can be
// retrieved
TEUCHOS_UNIT_TEST( PhotonCollisionHandler,
                   getMacroscopicTotalForwardCrossSection )
{
  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 1.0000000000042743e-06 );
  photon.setCell( 1 );

  double cross_section =
    collision_handler->getMacroscopicTotalForwardCrossSection( photon );

  TEST_FLOATING_EQUALITY( cross_section, 1.823831998305667e-05, 1e-12 );

  photon.setEnergy( 99999.99999997711 );

  cross_section =
    collision_handler->getMacroscopicTotalForwardCrossSection( photon );

  TEST_FLOATING_EQUALITY( cross_section, 0.11970087585747362, 1e-12 );

  photon.setCell( 2 );
  photon.setEnergy( 1.0000000000042743e-06 );

  cross_section =
    collision_handler->getMacroscopicTotalForwardCrossSection( photon );

  TEST_FLOATING_EQUALITY( cross_section, 1.823831998305667e-05, 1e-12 );

  photon.setEnergy( 99999.99999997711 );

  cross_section =
    collision_handler->getMacroscopicTotalForwardCrossSection( photon );

  TEST_FLOATING_EQUALITY( cross_section, 0.11970087585747362, 1e-12 );

  photon.setCell( 3 );
  photon.setEnergy( 1.0000000000042743e-06 );

  cross_section =
    collision_handler->getMacroscopicTotalForwardCrossSection( photon );

  TEST_FLOATING_EQUALITY( cross_section, 1.823831998305667e-05, 1e-12 );

  photon.setEnergy( 99999.99999997711 );

  cross_section =
    collision_handler->getMacroscopicTotalForwardCrossSection( photon );

  TEST_FLOATING_EQUALITY( cross_section, 0.11970087585747362, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic reaction cross section in a cell can be
// retrieved
TEUCHOS_UNIT_TEST( PhotonCollisionHandler,
                   getMacroscopicReactionCrossSection )
{
  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 1.0000000000042743e-06 );
  photon.setCell( 1 );

  double cross_section =
    collision_handler->getMacroscopicReactionCrossSection(
			   photon,
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 4.460222195795113e-09, 1e-12 );

  photon.setEnergy( 99999.99999997711 );

  cross_section =
    collision_handler->getMacroscopicReactionCrossSection(
			   photon,
			   MonteCarlo::TOTAL_INCOHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 4.060877396028078e-06, 1e-12 );

  photon.setEnergy( 1.0000000000042743e-06 );

  cross_section =
    collision_handler->getMacroscopicReactionCrossSection(
				   photon,
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.8233859760860873e-05, 1e-12 );

  photon.setEnergy( 99999.99999997711 );

  cross_section =
    collision_handler->getMacroscopicReactionCrossSection(
				   photon,
				   MonteCarlo::COHERENT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 2.712301051729535e-13, 1e-12 );

  photon.setEnergy( 1.0000000000042743e-06 );

  cross_section =
    collision_handler->getMacroscopicReactionCrossSection(
		   photon,
		   MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

   TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

   photon.setEnergy( 99999.99999997711 );

   cross_section =
     collision_handler->getMacroscopicReactionCrossSection(
		   photon,
		   MonteCarlo::K_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

   TEST_FLOATING_EQUALITY( cross_section, 3.4075097760409515e-08, 1e-12 );

   photon.setEnergy( 1.0000000000042743e-06 );

   cross_section =
     collision_handler->getMacroscopicReactionCrossSection(
		  photon,
		  MonteCarlo::P3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

   TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

   photon.setEnergy( 99999.99999997711 );

   cross_section =
     collision_handler->getMacroscopicReactionCrossSection(
		  photon,
		  MonteCarlo::P3_SUBSHELL_PHOTOELECTRIC_PHOTOATOMIC_REACTION );

   TEST_FLOATING_EQUALITY( cross_section, 1.5612230905027824e-13, 1e-12 );

   photon.setEnergy( 1.0000000000042743e-06 );

   cross_section =
     collision_handler->getMacroscopicReactionCrossSection(
		  photon,
		  MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

   TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

   photon.setEnergy( 99999.99999997711 );

   cross_section =
     collision_handler->getMacroscopicReactionCrossSection(
		  photon,
		  MonteCarlo::PAIR_PRODUCTION_PHOTOATOMIC_REACTION );

   TEST_FLOATING_EQUALITY( cross_section, 0.11969677359280363, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that a photon can collide with the material in a cell
TEUCHOS_UNIT_TEST( PhotonCollisionHandler, collideWithCellMaterial_analogue )
{
  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );
  photon.setWeight( 1.0 );
  photon.setCell( 1 );

  MonteCarlo::ParticleBank bank;

  // Set up the random number stream
  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.5; // select the pb atom
  fake_stream[1] = 0.9; // select the incoherent reaction
  fake_stream[2] = 0.001; // sample from first term of koblinger's method
  fake_stream[3] = 0.5; // x = 40.13902672495315, mu = 0.0
  fake_stream[4] = 0.5; // accept x in scattering function rejection loop
  fake_stream[5] = 0.005; // select first shell for collision - old
  fake_stream[6] = 0.005; // select first shell for collision - endf
  fake_stream[7] = 6.427713151861e-01; // select pz = 40.0
  fake_stream[8] = 0.25; // select energy loss

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  collision_handler->collideWithCellMaterial( photon, bank );

  TEST_FLOATING_EQUALITY( photon.getEnergy(), 0.352804013048420073, 1e-12 );
  TEST_FLOATING_EQUALITY( photon.getZDirection(), 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( photon.getWeight(), 1.0, 1e-15 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a photon can collide with the material in a cell
TEUCHOS_UNIT_TEST( PhotonCollisionHandler,
                   collideWithCellMaterial_survival_bias )
{
  // Reset the collision handler
  collision_handler.reset( new MonteCarlo::PhotonCollisionHandler( false ) );

  Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>
    cells_containing_material( 3 );
  cells_containing_material[0] = 1;
  cells_containing_material[1] = 2;
  cells_containing_material[2] = 3;
  
  collision_handler->addMaterial( lead, cells_containing_material );
  
  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );
  photon.setWeight( 1.0 );
  photon.setCell( 1 );

  MonteCarlo::ParticleBank bank;

  collision_handler->collideWithCellMaterial( photon, bank );
  
  TEST_FLOATING_EQUALITY( photon.getWeight(), 0.99623491442141221, 1e-12 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_cross_sections_xml_directory;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_cross_sections_xml_directory",
                   &test_cross_sections_xml_directory,
                   "Directory where test cross_sections.xml file is located.");
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Assign the name of the cross_sections.xml file with path
  std::string cross_section_xml_file = test_cross_sections_xml_directory;
  cross_section_xml_file += "/cross_sections.xml";

  Teuchos::ParameterList cross_section_table_info;
  
  // Read in the xml file storing the cross section table information
  Teuchos::updateParametersFromXmlFile(
			         cross_section_xml_file,
			         Teuchos::inoutArg(cross_section_table_info) );

  // Assign the atom fractions and names
  std::unordered_set<std::string> atom_aliases;
  atom_aliases.insert( "Pb" );
  
  Teuchos::Array<double> atom_fractions( 1 );
  Teuchos::Array<std::string> atom_names( 1 );
  
  atom_fractions[0] = -1.0; // weight fraction
  atom_names[0] = "Pb";
  
  // Create the atomic relaxation factory
  Teuchos::RCP<MonteCarlo::AtomicRelaxationModelFactory>
    atomic_relaxation_model_factory(
                                new MonteCarlo::AtomicRelaxationModelFactory );

  MonteCarlo::SimulationProperties properties;
  properties.setNumberOfPhotonHashGridBins( 1000 );
  properties.setIncoherentModelType( MonteCarlo::DECOUPLED_HALF_PROFILE_DB_HYBRID_INCOHERENT_MODEL );
  properties.setKahnSamplingCutoffEnergy( 3.0 );
  properties.setAtomicRelaxationModeOn( MonteCarlo::PHOTON );
  properties.setDetailedPairProductionModeOff();
  
  // Create the photoatom factory
  MonteCarlo::PhotoatomFactory photoatom_factory(
                                             test_cross_sections_xml_directory,
                                             cross_section_table_info,
                                             atom_aliases,
                                             atomic_relaxation_model_factory,
                                             properties );

  std::unordered_map<std::string,Teuchos::RCP<MonteCarlo::Photoatom> >
    photoatom_map;

  photoatom_factory.createPhotoatomMap( photoatom_map );
  
  // Create lead
  lead.reset( new MonteCarlo::PhotonMaterial( 0,
                                              -1.0,
                                              photoatom_map,
                                              atom_fractions,
                                              atom_names ) );

  // Initialize the collision handler
  collision_handler.reset( new MonteCarlo::PhotonCollisionHandler );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstPhotonCollisionHandler.cpp
//---------------------------------------------------------------------------//
