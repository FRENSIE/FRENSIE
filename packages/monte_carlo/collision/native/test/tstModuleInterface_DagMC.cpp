//---------------------------------------------------------------------------//
//!
//! \file   tstModuleInterface.cpp
//! \author Alex Robinson
//! \brief  Collision module interface unit tests
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
#include "MonteCarlo_CollisionHandlerFactory.hpp"
#include "MonteCarlo_StandardCollisionHandlerFactory.hpp"
#include "MonteCarlo_StandardCollisionHandlerFactory_DagMC.hpp"
#include "MonteCarlo_CollisionModuleInterface_Native.hpp"
#include "MonteCarlo_SimulationGeneralProperties.hpp"
#include "Geometry_DagMCInstanceFactory.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check if cells can be tested as void
TEUCHOS_UNIT_TEST( ModuleInterface, isCellVoid )
{
  typedef MonteCarlo::CollisionModuleInterface<MonteCarlo::CollisionHandler> CMI;

  TEST_ASSERT( !CMI::isCellVoid( 1, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( CMI::isCellVoid( 1, MonteCarlo::PHOTON ) );
  TEST_ASSERT( CMI::isCellVoid( 1, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( CMI::isCellVoid( 1, MonteCarlo::ELECTRON ) );
    
  TEST_ASSERT( !CMI::isCellVoid( 3, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( CMI::isCellVoid( 3, MonteCarlo::PHOTON ) );
  TEST_ASSERT( CMI::isCellVoid( 3, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( CMI::isCellVoid( 3, MonteCarlo::ELECTRON ) );
    
  TEST_ASSERT( !CMI::isCellVoid( 5, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( CMI::isCellVoid( 5, MonteCarlo::PHOTON ) );
  TEST_ASSERT( CMI::isCellVoid( 5, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( CMI::isCellVoid( 5, MonteCarlo::ELECTRON ) );
    
  TEST_ASSERT( !CMI::isCellVoid( 7, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( CMI::isCellVoid( 7, MonteCarlo::PHOTON ) );
  TEST_ASSERT( CMI::isCellVoid( 7, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( CMI::isCellVoid( 7, MonteCarlo::ELECTRON ) );
    
  TEST_ASSERT( !CMI::isCellVoid( 9, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( CMI::isCellVoid( 9, MonteCarlo::PHOTON ) );
  TEST_ASSERT( CMI::isCellVoid( 9, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( CMI::isCellVoid( 9, MonteCarlo::ELECTRON ) );
    
  TEST_ASSERT( CMI::isCellVoid( 13, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( CMI::isCellVoid( 13, MonteCarlo::PHOTON ) );
  TEST_ASSERT( CMI::isCellVoid( 13, MonteCarlo::ADJOINT_PHOTON ));
  TEST_ASSERT( CMI::isCellVoid( 13, MonteCarlo::ELECTRON ) );
}

//---------------------------------------------------------------------------//
// Check if the macroscopic total cross section in a cell can be retrieved
TEUCHOS_UNIT_TEST( ModuleInterface, getMacroscopicTotalCrossSection )
{
  typedef MonteCarlo::CollisionModuleInterface<MonteCarlo::CollisionHandler> CMI;

  MonteCarlo::NeutronState neutron( 0ull );
  neutron.setEnergy( 1.0e-11 );
  neutron.setCell( 1 );

  double cross_section = CMI::getMacroscopicTotalCrossSection( neutron );
  
  TEST_FLOATING_EQUALITY( cross_section, 1177.24711000000002, 1e-13 );

  neutron.setEnergy( 2.0e1 );

  cross_section = CMI::getMacroscopicTotalCrossSection( neutron );

  TEST_FLOATING_EQUALITY( cross_section, 0.482773423540000024, 1e-9 );
}

//---------------------------------------------------------------------------//
// Check if the macroscopic total cross section in a cell can be retrieved
TEUCHOS_UNIT_TEST( ModuleInterface, getMacroscopicTotalForwardCrossSection )
{
  typedef MonteCarlo::CollisionModuleInterface<MonteCarlo::CollisionHandler> CMI;

  MonteCarlo::NeutronState neutron( 0ull );
  neutron.setEnergy( 1.0e-11 );
  neutron.setCell( 1 );

  double cross_section =
    CMI::getMacroscopicTotalForwardCrossSection( neutron );

  TEST_FLOATING_EQUALITY( cross_section, 1177.24711000000002, 1e-13 );

  neutron.setEnergy( 2.0e1 );

  cross_section = CMI::getMacroscopicTotalForwardCrossSection( neutron );

  TEST_FLOATING_EQUALITY( cross_section, 0.482773423540000024, 1e-9 );
}

//---------------------------------------------------------------------------//
// Check that a neutron can collide with the material in a cell
TEUCHOS_UNIT_TEST( ModuleInterface, collideWithCellMaterial )
{
  typedef MonteCarlo::CollisionModuleInterface<MonteCarlo::CollisionHandler> CMI;

  MonteCarlo::NeutronState neutron( 0ull );
  neutron.setCell( 1 );
  neutron.setDirection( 0.0, 0.0, 1.0 );
  neutron.setEnergy( 1.0 );
  neutron.setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;

  CMI::collideWithCellMaterial( neutron, bank );

  TEST_EQUALITY_CONST( neutron.getWeight(), 1.0 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_cross_sections_xml_directory;
std::string test_material_xml_file_name;
std::string test_geom_xml_file_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_cross_sections_xml_directory",
                   &test_cross_sections_xml_directory,
                   "Test cross_sections.xml file directory name" );
  
  clp().setOption( "test_mat_xml_file",
                   &test_material_xml_file_name,
                   "Test xml material file name" );

  clp().setOption( "test_geom_xml_file",
                   &test_geom_xml_file_name,
                   "Test xml geometry file name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Initialize DagMC
  Teuchos::RCP<Teuchos::ParameterList> geom_rep =
    Teuchos::getParametersFromXmlFile( test_geom_xml_file_name );

  Geometry::DagMCInstanceFactory::initializeDagMC( *geom_rep );
  
  // Assign the name of the cross_sections.xml file with path
  std::string cross_section_xml_file = test_cross_sections_xml_directory;
  cross_section_xml_file += "/cross_sections.xml";

  // Read in the xml file storing the cross section table information
  Teuchos::ParameterList cross_section_table_info;
  Teuchos::updateParametersFromXmlFile(
			         cross_section_xml_file,
			         Teuchos::inoutArg(cross_section_table_info) );

  // Read in the xml file storing the material specifications
  Teuchos::ParameterList material_reps;
  Teuchos::updateParametersFromXmlFile( test_material_xml_file_name,
                                        Teuchos::inoutArg(material_reps) );

  // Initialize the collision handler
  MonteCarlo::SimulationProperties properties;
  properties.setParticleMode( MonteCarlo::NEUTRON_MODE );
  properties.setAnalogueCaptureModeOn();

  std::shared_ptr<MonteCarlo::CollisionHandler> collision_handler =
    MonteCarlo::getCollisionHandlerFactoryInstance<Geometry::DagMC>()->createHandler(
                                           material_reps,
					   cross_section_table_info,
                                           properties,
					   test_cross_sections_xml_directory );

  // Assign the collision handler to the interface
  MonteCarlo::setCollisionHandlerInstance( collision_handler );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstModuleInterface.cpp
//---------------------------------------------------------------------------//
