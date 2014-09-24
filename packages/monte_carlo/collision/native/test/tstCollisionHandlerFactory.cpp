//---------------------------------------------------------------------------//
//!
//! \file   tstCollisionHandlerFactory.cpp
//! \author Alex Robinson
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

  MonteCarlo::CollisionHandlerFactory::initializeHandlerUsingDagMC( 
					   material_reps,
					   cross_section_table_info,
					   test_cross_sections_xml_directory );

  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 26 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 26 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 27 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 27 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 28 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 28 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 29 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 29 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 30 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 30 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 31 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 31 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 32 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 32 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 33 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 33 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 34 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 34 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 35 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 35 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 36 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 36 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 37 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 37 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 48 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 48 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 49 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 49 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 50 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 50 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 51 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 51 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 52 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 52 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 53 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 53 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 54 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 54 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 55 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 55 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 56 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 56 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 57 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 57 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 58 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 58 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 59 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 59 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 70 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 70 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 71 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 71 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 72 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 72 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 73 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 73 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 74 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 74 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 75 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 75 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 76 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 76 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 77 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 77 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 78 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 78 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 79 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 79 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 80 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 80 )->getId() == 9 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 81 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 81 )->getId() == 9 );
  TEST_FLOATING_EQUALITY( 
	   MonteCarlo::CollisionHandler::getCellMaterial( 81 )->getNumberDensity(),
	   4.6787270057348,
	   1e-12 );
  
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 9 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 9 )->getId() == 1 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 88 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 88 )->getId() == 1 );
  TEST_FLOATING_EQUALITY( 
	   MonteCarlo::CollisionHandler::getCellMaterial( 88 )->getNumberDensity(),
	   4.7964421040911,
	   1e-12 );
  
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 136 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 136 )->getId() == 2);
  TEST_FLOATING_EQUALITY( 
	  MonteCarlo::CollisionHandler::getCellMaterial( 136 )->getNumberDensity(),
	  4.6309239201079,
	  1e-12 );
  
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 19 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 19 )->getId() == 3 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 41 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 41 )->getId() == 3 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 63 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 63 )->getId() == 3 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 82 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 82 )->getId() == 3 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 152 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 152 )->getId() == 3);
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 166 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 166 )->getId() == 3);
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 184 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 184 )->getId() == 3);
  TEST_FLOATING_EQUALITY( 
	  MonteCarlo::CollisionHandler::getCellMaterial( 184 )->getNumberDensity(),
	  9.7578048535952e-4,
	  1e-12 );
  
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 3 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 3 )->getId() == 4 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 7 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 7 )->getId() == 4 );
  TEST_FLOATING_EQUALITY( 
	  MonteCarlo::CollisionHandler::getCellMaterial( 7 )->getNumberDensity(),
	  0.59648092706701,
	  1e-12 );
  
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 5 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 5 )->getId() == 10 );
  TEST_FLOATING_EQUALITY( 
	  MonteCarlo::CollisionHandler::getCellMaterial( 5 )->getNumberDensity(),
	  7.9532383711789,
	  1e-12 );
  
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 1 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 1 )->getId() == 8 );
  TEST_FLOATING_EQUALITY( 
	  MonteCarlo::CollisionHandler::getCellMaterial( 1 )->getNumberDensity(),
	  1.1104059252563,
	  1e-12 );
  
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 13 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 13 )->getId() == 7 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 83 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 83 )->getId() == 7 );
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 154 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 154 )->getId() == 7);
  TEST_ASSERT( !MonteCarlo::CollisionHandler::isCellVoid( 168 ) );
  TEST_ASSERT( MonteCarlo::CollisionHandler::getCellMaterial( 168 )->getId() == 7);
  TEST_FLOATING_EQUALITY( 
	  MonteCarlo::CollisionHandler::getCellMaterial( 168 )->getNumberDensity(),
	  3.3760929224013,
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
// end tstCollisionHandlerFactory.cpp
//---------------------------------------------------------------------------//
