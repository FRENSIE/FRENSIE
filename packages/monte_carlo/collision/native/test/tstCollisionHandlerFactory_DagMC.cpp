//---------------------------------------------------------------------------//
//!
//! \file   tstCollisionHandlerFactoryNeutronMode_DagMC.cpp
//! \author Alex Robinson, Eli Moll
//! \brief  Collision handler factory unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "MonteCarlo_NuclideFactory.hpp"
#include "MonteCarlo_NeutronMaterial.hpp"
#include "MonteCarlo_CollisionHandlerFactory.hpp"
#include "MonteCarlo_StandardCollisionHandlerFactory_DagMC.hpp"
#include "MonteCarlo_SimulationGeneralProperties.hpp"
#include "Geometry_DagMCInstanceFactory.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//
std::string test_cross_sections_xml_directory;
Teuchos::ParameterList cross_section_table_info;
Teuchos::ParameterList forward_material_reps;
Teuchos::ParameterList adjoint_material_reps;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the collision handler can be initialize with DagMC
TEUCHOS_UNIT_TEST( CollisionHandlerFactoryDagMC,
                   createHandler_neutron_mode_analogue )
{
  // Set the particle mode to NEUTRON_MODE
  MonteCarlo::SimulationGeneralProperties::setParticleMode( MonteCarlo::NEUTRON_MODE );

  std::shared_ptr<MonteCarlo::CollisionHandler> collision_handler =
    MonteCarlo::getCollisionHandlerFactoryInstance<Geometry::DagMC>()->createHandler(
                                           forward_material_reps,
					   cross_section_table_info,
					   test_cross_sections_xml_directory );

  std::shared_ptr<MonteCarlo::NeutronCollisionHandler>
    neutron_collision_handler = std::dynamic_pointer_cast<MonteCarlo::NeutronCollisionHandler>( collision_handler );
  
  // Neutrons
  TEST_ASSERT( !collision_handler->isCellVoid( 1, MonteCarlo::NEUTRON ) );
  TEST_EQUALITY_CONST( neutron_collision_handler->getMaterial( 1 )->getId(),
                       1 );
  
  TEST_ASSERT( !collision_handler->isCellVoid( 3, MonteCarlo::NEUTRON ) );
  TEST_EQUALITY_CONST( neutron_collision_handler->getMaterial( 3 )->getId(),
                       2 );
  
  TEST_ASSERT( !collision_handler->isCellVoid( 5, MonteCarlo::NEUTRON ) );
  TEST_EQUALITY_CONST( neutron_collision_handler->getMaterial( 5 )->getId(),
                       3 );
  
  TEST_ASSERT( !collision_handler->isCellVoid( 7, MonteCarlo::NEUTRON ) );
  TEST_EQUALITY_CONST( neutron_collision_handler->getMaterial( 7 )->getId(),
                       2 );
  
  TEST_ASSERT( !collision_handler->isCellVoid( 9, MonteCarlo::NEUTRON ) );
  TEST_EQUALITY_CONST( neutron_collision_handler->getMaterial( 9 )->getId(),
                       4 );
  
  TEST_ASSERT( collision_handler->isCellVoid( 13, MonteCarlo::NEUTRON ) );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_forward_material_xml_file_name;
std::string test_adjoint_material_xml_file_name;
std::string test_geom_xml_file_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_cross_sections_xml_directory",
                   &test_cross_sections_xml_directory,
                   "Test cross_sections.xml file directory name" );

  clp().setOption( "test_forward_mat_xml_file",
                   &test_forward_material_xml_file_name,
                   "Test xml material file name for forward particles" );

  clp().setOption( "test_adjoint_mat_xml_file",
                   &test_adjoint_material_xml_file_name,
                   "Test xml material file name for adjoint particles" );

  clp().setOption( "test_geom_xml_file",
                   &test_geom_xml_file_name,
                   "Test xml geometry file name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Assign the name of the cross_sections.xml file with path
  std::string cross_section_xml_file = test_cross_sections_xml_directory;
  cross_section_xml_file += "/cross_sections.xml";

  // Read in the xml file storing the cross section table information
  Teuchos::updateParametersFromXmlFile(
			         cross_section_xml_file,
			         Teuchos::inoutArg(cross_section_table_info) );

  // Read in the xml file storing the material specifications
  Teuchos::updateParametersFromXmlFile( test_forward_material_xml_file_name,
					Teuchos::inoutArg(forward_material_reps) );

  Teuchos::updateParametersFromXmlFile( test_adjoint_material_xml_file_name,
                                        Teuchos::inoutArg(adjoint_material_reps) );

  // Initialize DagMC
  Teuchos::RCP<Teuchos::ParameterList> geom_rep =
    Teuchos::getParametersFromXmlFile( test_geom_xml_file_name );

  Geometry::DagMCInstanceFactory::initializeDagMC( *geom_rep );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstCollisionHandlerFactoryNeutronMode_DagMC.cpp
//---------------------------------------------------------------------------//
