//---------------------------------------------------------------------------//
//!
//! \file   tstCollisionHandlerFactoryNeutronMode_Root.cpp
//! \author Eli Moll
//! \brief  Collision handler factory unit tests for electron mode
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

// Moab Includes
#include "Geometry_Root.hpp"

// FRENSIE Includes
#include "MonteCarlo_NuclideFactory.hpp"
#include "MonteCarlo_NeutronMaterial.hpp"
#include "MonteCarlo_CollisionHandlerFactory.hpp"
#include "MonteCarlo_StandardCollisionHandlerFactory.hpp"
#include "MonteCarlo_StandardCollisionHandlerFactory_Root.hpp"
#include "MonteCarlo_SimulationProperties.hpp"
#include "Geometry_RootInstanceFactory.hpp"

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

  // Set the particle mode to ELECTRON_MODE
  MonteCarlo::SimulationProperties::setParticleMode( MonteCarlo::NEUTRON_MODE );

  MonteCarlo::getCollisionHandlerFactoryInstance<Geometry::Root>()->initializeHandler( 
					   material_reps,
					   cross_section_table_info,
					   test_cross_sections_xml_directory );

  // Electrons
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 1, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 2, MonteCarlo::ELECTRON ) );

  // Photons
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 1, MonteCarlo::PHOTON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 2, MonteCarlo::PHOTON ) );

  // Neutrons
  TEST_ASSERT( MonteCarlo::CollisionHandler::isCellVoid( 1, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 2, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellNeutronMaterial( 2 )->getId() == 1 );
  TEST_FLOATING_EQUALITY( 
	   MonteCarlo::CollisionHandler::getCellNeutronMaterial( 2 )->getNumberDensity(),
	   1.0,
	   1e-12 );
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

  // Initialize Root
  Teuchos::RCP<Teuchos::ParameterList> geom_rep = 
    Teuchos::getParametersFromXmlFile( test_geom_xml_file_name );

  Geometry::RootInstanceFactory::initializeRoot( *geom_rep );

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
// end tstCollisionHandlerFactoryNeutronMode_Root.cpp
//---------------------------------------------------------------------------//
