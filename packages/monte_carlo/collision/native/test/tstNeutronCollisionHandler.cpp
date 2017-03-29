//---------------------------------------------------------------------------//
//!
//! \file   tstNeutronCollisionHandler.cpp
//! \author Alex Robinson
//! \brief  Neutron collision handler class unit tests
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
#include "MonteCarlo_NuclideFactory.hpp"
#include "MonteCarlo_NeutronMaterial.hpp"
#include "MonteCarlo_NeutronCollisionHandler.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

Teuchos::RCP<const MonteCarlo::NeutronMaterial> cold_hydrogen;
Teuchos::RCP<const MonteCarlo::NeutronMaterial> hot_hydrogen;
std::shared_ptr<MonteCarlo::NeutronCollisionHandler> collision_handler;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that materials can be added to the collision handler
TEUCHOS_UNIT_TEST( NeutronCollisionHandler, addMaterial )
{
  TEST_ASSERT( collision_handler->isCellVoid( 1 ) );
  TEST_ASSERT( collision_handler->isCellVoid( 2 ) );
  TEST_ASSERT( collision_handler->isCellVoid( 3 ) );
  TEST_ASSERT( collision_handler->isCellVoid( 4 ) );
  TEST_ASSERT( collision_handler->isCellVoid( 5 ) );
  TEST_ASSERT( collision_handler->isCellVoid( 6 ) );
  
  Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>
    cells_containing_material( 3 );
  cells_containing_material[0] = 1;
  cells_containing_material[1] = 2;
  cells_containing_material[2] = 3;
  
  collision_handler->addMaterial( cold_hydrogen, cells_containing_material );

  TEST_ASSERT( !collision_handler->isCellVoid( 1 ) );
  TEST_ASSERT( !collision_handler->isCellVoid( 2 ) );
  TEST_ASSERT( !collision_handler->isCellVoid( 3 ) );

  cells_containing_material[0] = 4;
  cells_containing_material[1] = 5;
  cells_containing_material[2] = 6;

  collision_handler->addMaterial( hot_hydrogen, cells_containing_material );

  TEST_ASSERT( !collision_handler->isCellVoid( 4 ) );
  TEST_ASSERT( !collision_handler->isCellVoid( 5 ) );
  TEST_ASSERT( !collision_handler->isCellVoid( 6 ) );
}

//---------------------------------------------------------------------------//
// Check that the material contained in a cell can be retrieved
TEUCHOS_UNIT_TEST( NeutronCollisionHandler, getMaterial )
{
  Teuchos::RCP<const MonteCarlo::NeutronMaterial> cell_material =
    collision_handler->getMaterial( 1 );

  TEST_ASSERT( !cell_material.is_null() );
  TEST_EQUALITY_CONST( cell_material->getId(), 0 );
  TEST_EQUALITY_CONST( cell_material, cold_hydrogen );

  cell_material = collision_handler->getMaterial( 2 );

  TEST_ASSERT( !cell_material.is_null() );
  TEST_EQUALITY_CONST( cell_material->getId(), 0 );
  TEST_EQUALITY_CONST( cell_material, cold_hydrogen );

  cell_material = collision_handler->getMaterial( 3 );

  TEST_ASSERT( !cell_material.is_null() );
  TEST_EQUALITY_CONST( cell_material->getId(), 0 );
  TEST_EQUALITY_CONST( cell_material, cold_hydrogen );

  cell_material = collision_handler->getMaterial( 4 );

  TEST_ASSERT( !cell_material.is_null() );
  TEST_EQUALITY_CONST( cell_material->getId(), 1 );
  TEST_EQUALITY_CONST( cell_material, hot_hydrogen );

  cell_material = collision_handler->getMaterial( 5 );

  TEST_ASSERT( !cell_material.is_null() );
  TEST_EQUALITY_CONST( cell_material->getId(), 1 );
  TEST_EQUALITY_CONST( cell_material, hot_hydrogen );

  cell_material = collision_handler->getMaterial( 6 );

  TEST_ASSERT( !cell_material.is_null() );
  TEST_EQUALITY_CONST( cell_material->getId(), 1 );
  TEST_EQUALITY_CONST( cell_material, hot_hydrogen );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic total cross section in a cell can be retrieved
TEUCHOS_UNIT_TEST( NeutronCollisionHandler, getMacroscopicTotalCrossSection )
{
  MonteCarlo::NeutronState neutron( 0ull );
  neutron.setEnergy( 1.0e-11 );
  neutron.setCell( 1 );

  double cross_section =
    collision_handler->getMacroscopicTotalCrossSection( neutron );

  TEST_FLOATING_EQUALITY( cross_section, 703.45055504218, 1e-13 );

  neutron.setEnergy( 2.0e1 );

  cross_section =
    collision_handler->getMacroscopicTotalCrossSection( neutron );

  TEST_FLOATING_EQUALITY( cross_section, 0.28847574157342, 1e-9 );

  neutron.setEnergy( 1.0e-11 );
  neutron.setCell( 2 );

  cross_section =
    collision_handler->getMacroscopicTotalCrossSection( neutron );

  TEST_FLOATING_EQUALITY( cross_section, 703.45055504218, 1e-13 );

  neutron.setEnergy( 2.0e1 );

  cross_section =
    collision_handler->getMacroscopicTotalCrossSection( neutron );

  TEST_FLOATING_EQUALITY( cross_section, 0.28847574157342, 1e-9 );

  neutron.setEnergy( 1.0e-11 );
  neutron.setCell( 3 );

  cross_section =
    collision_handler->getMacroscopicTotalCrossSection( neutron );

  TEST_FLOATING_EQUALITY( cross_section, 703.45055504218, 1e-13 );

  neutron.setEnergy( 2.0e1 );

  cross_section =
    collision_handler->getMacroscopicTotalCrossSection( neutron );

  TEST_FLOATING_EQUALITY( cross_section, 0.28847574157342, 1e-9 );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic total forward cross section in a cell can be
// retrieved
TEUCHOS_UNIT_TEST( NeutronCollisionHandler,
                   getMacroscopicTotalForwardCrossSection )
{
  MonteCarlo::NeutronState neutron( 0ull );
  neutron.setEnergy( 1.0e-11 );
  neutron.setCell( 1 );

  double cross_section =
    collision_handler->getMacroscopicTotalForwardCrossSection( neutron );

  TEST_FLOATING_EQUALITY( cross_section, 703.45055504218, 1e-13 );

  neutron.setEnergy( 2.0e1 );

  cross_section =
    collision_handler->getMacroscopicTotalForwardCrossSection( neutron );

  TEST_FLOATING_EQUALITY( cross_section, 0.28847574157342, 1e-9 );

  neutron.setEnergy( 1.0e-11 );
  neutron.setCell( 2 );

  cross_section =
    collision_handler->getMacroscopicTotalForwardCrossSection( neutron );

  TEST_FLOATING_EQUALITY( cross_section, 703.45055504218, 1e-13 );

  neutron.setEnergy( 2.0e1 );

  cross_section =
    collision_handler->getMacroscopicTotalForwardCrossSection( neutron );

  TEST_FLOATING_EQUALITY( cross_section, 0.28847574157342, 1e-9 );

  neutron.setEnergy( 1.0e-11 );
  neutron.setCell( 3 );

  cross_section =
    collision_handler->getMacroscopicTotalForwardCrossSection( neutron );

  TEST_FLOATING_EQUALITY( cross_section, 703.45055504218, 1e-13 );

  neutron.setEnergy( 2.0e1 );

  cross_section =
    collision_handler->getMacroscopicTotalForwardCrossSection( neutron );

  TEST_FLOATING_EQUALITY( cross_section, 0.28847574157342, 1e-9 );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic reaction cross section in a cell can be
// retrieved
TEUCHOS_UNIT_TEST( NeutronCollisionHandler,
                   getMacroscopicReactionCrossSection )
{
  // Neutron reactions
  MonteCarlo::NeutronState neutron( 0ull );
  neutron.setEnergy( 1.0e-11 );
  neutron.setCell( 1 );

  double cross_section =
    collision_handler->getMacroscopicReactionCrossSection(
						   neutron,
						   MonteCarlo::N__TOTAL_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 703.45055504218, 1e-13 );

  neutron.setEnergy( 2.0e1 );

  cross_section =
    collision_handler->getMacroscopicReactionCrossSection(
						   neutron,
						   MonteCarlo::N__TOTAL_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.28847574157342, 1e-9 );

  neutron.setEnergy( 1.0e-11 );

  cross_section =
    collision_handler->getMacroscopicReactionCrossSection(
					       neutron,
					       MonteCarlo::N__N_ELASTIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 693.47099764974, 1e-13 );

  neutron.setEnergy( 2.0e1 );

  cross_section =
    collision_handler->getMacroscopicReactionCrossSection(
					       neutron,
					       MonteCarlo::N__N_ELASTIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.28845947418338, 1e-13 );

  neutron.setEnergy( 1.0e-11 );

  cross_section =
    collision_handler->getMacroscopicReactionCrossSection(
					       neutron,
					       MonteCarlo::N__GAMMA_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 9.9795573924326, 1e-13 );

  neutron.setEnergy( 2.0e1 );

  cross_section =
    collision_handler->getMacroscopicReactionCrossSection(
					       neutron,
					       MonteCarlo::N__GAMMA_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.6267115171099e-5, 1e-13 );

  neutron.setEnergy( 1.0e-11 );

  cross_section =
    collision_handler->getMacroscopicReactionCrossSection(
					       neutron,
					       MonteCarlo::N__TOTAL_D_PRODUCTION );

  TEST_FLOATING_EQUALITY( cross_section, 9.9795573924326, 1e-13 );

  neutron.setEnergy( 2.0e1 );

  cross_section =
    collision_handler->getMacroscopicReactionCrossSection(
					       neutron,
					       MonteCarlo::N__TOTAL_D_PRODUCTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.6267115171099e-5, 1e-13 );

  neutron.setEnergy( 1.0e-11 );

  cross_section =
    collision_handler->getMacroscopicReactionCrossSection(
					       neutron,
					       MonteCarlo::N__DPA );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-15 );

  neutron.setEnergy( 2.0e1 );

  cross_section =
    collision_handler->getMacroscopicReactionCrossSection(
					       neutron,
					       MonteCarlo::N__DPA );

  TEST_FLOATING_EQUALITY( cross_section, 1.833066682067e-4, 1e-13 );

  neutron.setEnergy( 1.0e-11 );

  cross_section =
    collision_handler->getMacroscopicReactionCrossSection(
					       neutron,
					       MonteCarlo::N__FISSION_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a neutron can collide with the material in a cell
TEUCHOS_UNIT_TEST( NeutronCollisionHandler, collideWithCellMaterial_analogue )
{
  MonteCarlo::NeutronState neutron( 0ull );
  neutron.setCell( 1 );
  neutron.setDirection( 0.0, 0.0, 1.0 );
  neutron.setEnergy( 1.0 );
  neutron.setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;

  collision_handler->collideWithCellMaterial( neutron, bank );

  TEST_EQUALITY_CONST( neutron.getWeight(), 1.0 );

  neutron.setCell( 4 );
  neutron.setEnergy( 1.0 );

  collision_handler->collideWithCellMaterial( neutron, bank );

  TEST_EQUALITY_CONST( neutron.getWeight(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that a neutron can collide with the material in a cell
TEUCHOS_UNIT_TEST( NeutronCollisionHandler,
                   collideWithCellMaterial_survival_bias )
{
  // Reset the collision handler
  collision_handler.reset( new MonteCarlo::NeutronCollisionHandler( false ) );

  Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>
    cells_containing_material( 3 );
  cells_containing_material[0] = 1;
  cells_containing_material[1] = 2;
  cells_containing_material[2] = 3;
  
  collision_handler->addMaterial( cold_hydrogen, cells_containing_material );
  
  MonteCarlo::NeutronState neutron( 0ull );
  neutron.setCell( 1 );
  neutron.setDirection( 0.0, 0.0, 1.0 );
  neutron.setEnergy( 1.03125e-11 );
  neutron.setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;

  collision_handler->collideWithCellMaterial( neutron, bank );

  TEST_FLOATING_EQUALITY( neutron.getWeight(), 0.98581348192787, 1e-14 );
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

  std::unordered_set<std::string> nuclide_aliases;
  nuclide_aliases.insert( "H-1_293.6K" );
  nuclide_aliases.insert( "H-1_900K" );

  MonteCarlo::SimulationProperties properties;

  // Create the nuclide factory
  MonteCarlo::NuclideFactory nuclide_factory(
					     test_cross_sections_xml_directory,
					     cross_section_table_info,
					     nuclide_aliases,
                                             properties );

  std::unordered_map<std::string,Teuchos::RCP<MonteCarlo::Nuclide> >
    nuclide_map;

  nuclide_factory.createNuclideMap( nuclide_map );

  // Create cold hydrogen
  Teuchos::Array<double> nuclide_fractions( 1 );
  Teuchos::Array<std::string> nuclide_names( 1 );
  
  nuclide_fractions[0] = -1.0;
  nuclide_names[0] = "H-1_293.6K";
  
  cold_hydrogen.reset( new MonteCarlo::NeutronMaterial( 0,
                                                        -1.0,
                                                        nuclide_map,
                                                        nuclide_fractions,
                                                        nuclide_names ) );
  
  // Create hot hydrogen
  nuclide_names[0] = "H-1_900K";
  
  hot_hydrogen.reset( new MonteCarlo::NeutronMaterial( 1,
                                                       -1.0,
                                                       nuclide_map,
                                                       nuclide_fractions,
                                                       nuclide_names ) );

  // Initialize the collision handler
  collision_handler.reset( new MonteCarlo::NeutronCollisionHandler );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstNeutronCollisionHandler.cpp
//---------------------------------------------------------------------------//
