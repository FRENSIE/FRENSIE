//---------------------------------------------------------------------------//
//!
//! \file   tstCollisionHandlerFactoryNeutronPhotonMode_DagMC.cpp
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

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//
std::string test_cross_sections_xml_directory;
std::string test_material_xml_file_name;
std::string test_geom_xml_file_name;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the collision handler can be initialize with DagMC
TEUCHOS_UNIT_TEST( CollisionHandlerFactory, initializeHandlerUsingDagMC )
{
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

  // Set the particle mode to NEUTRON_PHOTON_MODE
  MonteCarlo::SimulationGeneralProperties::setParticleMode( MonteCarlo::NEUTRON_PHOTON_MODE);

  MonteCarlo::getCollisionHandlerFactoryInstance<Geometry::DagMC>()->initializeHandler( 
					   material_reps,
					   cross_section_table_info,
					   test_cross_sections_xml_directory );

  // Neutrons
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 26, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 26 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 27, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 27 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 28, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 28 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 29, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 29 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 30, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 30 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 31, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 31 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 32, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 32 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 33, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 33 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 34, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 34 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 35, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 35 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 36, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 36 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 37, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 37 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 48, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 48 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 49, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 49 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 50, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 50 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 51, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 51 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 52, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 52 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 53, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 53 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 54, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 54 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 55, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 55 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 56, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 56 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 57, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 57 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 58, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 58 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 59, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 59 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 70, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 70 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 71, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 71 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 72, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 72 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 73, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 73 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 74, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 74 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 75, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 75 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 76, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 76 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 77, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 77 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 78, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 78 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 79, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 79 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 80, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 80 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 81, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 81 )->getId() == 9 );
  TEST_FLOATING_EQUALITY( 
	   MonteCarlo::CollisionHandler::getCellNeutronMaterial( 81 )->getNumberDensity(),
	   4.6787270057348,
	   1e-12 );
  
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 9, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 9 )->getId() == 1 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 88, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 88 )->getId() == 1 );
  TEST_FLOATING_EQUALITY( 
	   MonteCarlo::CollisionHandler::getCellNeutronMaterial( 88 )->getNumberDensity(),
	   4.7964421040911,
	   1e-12 );
  
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 136, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 136 )->getId() == 2);
  TEST_FLOATING_EQUALITY( 
	  MonteCarlo::CollisionHandler::getCellNeutronMaterial( 136 )->getNumberDensity(),
	  4.6309239201079,
	  1e-12 );
  
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 19, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 19 )->getId() == 3 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 41, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 41 )->getId() == 3 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 63, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 63 )->getId() == 3 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 82, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 82 )->getId() == 3 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 152, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 152 )->getId() == 3);
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 166, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 166 )->getId() == 3);
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 184, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 184 )->getId() == 3);
  TEST_FLOATING_EQUALITY( 
	  MonteCarlo::CollisionHandler::getCellNeutronMaterial( 184 )->getNumberDensity(),
	  9.7578048535952e-4,
	  1e-12 );
  
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 3, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 3 )->getId() == 4 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 7, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 7 )->getId() == 4 );
  TEST_FLOATING_EQUALITY( 
	  MonteCarlo::CollisionHandler::getCellNeutronMaterial( 7 )->getNumberDensity(),
	  0.59648092706701,
	  1e-12 );
  
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 5, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 5 )->getId() == 10 );
  TEST_FLOATING_EQUALITY( 
	  MonteCarlo::CollisionHandler::getCellNeutronMaterial( 5 )->getNumberDensity(),
	  7.9532383711789,
	  1e-12 );
  
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 1, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 1 )->getId() == 8 );
  TEST_FLOATING_EQUALITY( 
	  MonteCarlo::CollisionHandler::getCellNeutronMaterial( 1 )->getNumberDensity(),
	  1.1104059252563,
	  1e-12 );
  
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 13, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 13 )->getId() == 7 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 83, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 83 )->getId() == 7 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 154, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 154 )->getId() == 7);
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 168, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 168 )->getId() == 7);
  TEST_FLOATING_EQUALITY( 
	  MonteCarlo::CollisionHandler::getCellNeutronMaterial( 168 )->getNumberDensity(),
	  3.3760929224013,
	  1e-12 );

  // Photons
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 26, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 26 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 27, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 27 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 28, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 28 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 29, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 29 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 30, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 30 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 31, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 31 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 32, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 32 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 33, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 33 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 34, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 34 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 35, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 35 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 36, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 36 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 37, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 37 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 48, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 48 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 49, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 49 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 50, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 50 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 51, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 51 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 52, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 52 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 53, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 53 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 54, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 54 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 55, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 55 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 56, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 56 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 57, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 57 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 58, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 58 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 59, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 59 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 70, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 70 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 71, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 71 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 72, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 72 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 73, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 73 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 74, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 74 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 75, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 75 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 76, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 76 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 77, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 77 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 78, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 78 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 79, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 79 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 80, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 80 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 81, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 81 )->getId() == 9 );
  TEST_FLOATING_EQUALITY( 
	   MonteCarlo::CollisionHandler::getCellPhotonMaterial( 81 )->getNumberDensity(),
	   4.6787270057348,
	   1e-12 );
  
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 9, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 9 )->getId() == 1 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 88, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 88 )->getId() == 1 );
  TEST_FLOATING_EQUALITY( 
	   MonteCarlo::CollisionHandler::getCellPhotonMaterial( 88 )->getNumberDensity(),
	   4.7964421040911,
	   1e-12 );
  
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 136, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 136 )->getId() == 2);
  TEST_FLOATING_EQUALITY( 
	  MonteCarlo::CollisionHandler::getCellPhotonMaterial( 136 )->getNumberDensity(),
	  4.6309239201079,
	  1e-12 );
  
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 19, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 19 )->getId() == 3 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 41, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 41 )->getId() == 3 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 63, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 63 )->getId() == 3 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 82, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 82 )->getId() == 3 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 152, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 152 )->getId() == 3);
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 166, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 166 )->getId() == 3);
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 184, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 184 )->getId() == 3);
  TEST_FLOATING_EQUALITY( 
	  MonteCarlo::CollisionHandler::getCellPhotonMaterial( 184 )->getNumberDensity(),
	  9.7578048535952e-4,
	  1e-12 );
  
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 3, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 3 )->getId() == 4 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 7, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 7 )->getId() == 4 );
  TEST_FLOATING_EQUALITY( 
	  MonteCarlo::CollisionHandler::getCellPhotonMaterial( 7 )->getNumberDensity(),
	  0.59648092706701,
	  1e-12 );
  
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 5, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 5 )->getId() == 10 );
  TEST_FLOATING_EQUALITY( 
	  MonteCarlo::CollisionHandler::getCellPhotonMaterial( 5 )->getNumberDensity(),
	  7.9532383711789,
	  1e-12 );
  
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 1, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 1 )->getId() == 8 );
  TEST_FLOATING_EQUALITY( 
	  MonteCarlo::CollisionHandler::getCellPhotonMaterial( 1 )->getNumberDensity(),
	  1.1104059252563,
	  1e-12 );
  
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 13, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 13 )->getId() == 7 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 83, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 83 )->getId() == 7 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 154, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 154 )->getId() == 7);
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 168, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellPhotonMaterial( 168 )->getId() == 7);
  TEST_FLOATING_EQUALITY( 
	  MonteCarlo::CollisionHandler::getCellPhotonMaterial( 168 )->getNumberDensity(),
	  3.3760929224013,
	  1e-12 );

  // Electrons
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 26, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 27, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 28, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 29, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 30, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 31, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 32, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 33, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 34, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 35, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 36, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 37, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 48, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 49, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 50, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 51, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 52, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 53, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 54, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 55, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 56, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 57, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 58, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 59, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 70, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 71, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 72, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 73, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 74, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 75, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 76, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 77, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 78, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 79, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 80, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 81, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 9, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 88, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 136, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 19, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 41, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 63, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 82, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 152, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 166, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 184, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 3, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 7, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 5, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 1, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 13, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 83, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 154, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 168, MonteCarlo::ELECTRON ) );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_cross_sections_xml_directory",
		 &test_cross_sections_xml_directory,
		 "Test cross_sections.xml file directory name" );

  clp.setOption( "test_mat_xml_file",
		 &test_material_xml_file_name,
		 "Test xml material file name" );

  clp.setOption( "test_geom_xml_file",
		 &test_geom_xml_file_name,
		 "Test xml geometry file name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();
  
  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Initialize DagMC
  Teuchos::RCP<Teuchos::ParameterList> geom_rep = 
    Teuchos::getParametersFromXmlFile( test_geom_xml_file_name );

  Geometry::DagMCInstanceFactory::initializeDagMC( *geom_rep );

  // Run the unit tests
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  
  const bool success = Teuchos::UnitTestRepository::runUnitTests(*out);

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstCollisionHandlerFactoryNeutronPhotonMode_DagMC.cpp
//---------------------------------------------------------------------------//
