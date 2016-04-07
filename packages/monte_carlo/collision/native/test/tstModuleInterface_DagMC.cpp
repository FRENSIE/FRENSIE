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

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check if cells can be tested as void
TEUCHOS_UNIT_TEST( ModuleInterface, isCellVoid )
{
  typedef MonteCarlo::CollisionModuleInterface<MonteCarlo::CollisionHandler> CMI;
  
  TEST_ASSERT( !CMI::isCellVoid( 26, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 27, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 28, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 29, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 30, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 31, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 32, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 33, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 34, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 35, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 36, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 37, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 48, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 49, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 50, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 51, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 52, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 53, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 54, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 55, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 56, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 57, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 58, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 59, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 70, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 71, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 72, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 73, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 74, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 75, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 76, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 77, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 78, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 79, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 80, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 81, MonteCarlo::NEUTRON ) );
  
  TEST_ASSERT( !CMI::isCellVoid( 9, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 88, MonteCarlo::NEUTRON ) );
  
  TEST_ASSERT( !CMI::isCellVoid( 136, MonteCarlo::NEUTRON ) );
  
  TEST_ASSERT( !CMI::isCellVoid( 19, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 41, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 63, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 82, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 152, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 166, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 184, MonteCarlo::NEUTRON ) );
  
  TEST_ASSERT( !CMI::isCellVoid( 3, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 7, MonteCarlo::NEUTRON ) );
  
  TEST_ASSERT( !CMI::isCellVoid( 5, MonteCarlo::NEUTRON ) );
  
  TEST_ASSERT( !CMI::isCellVoid( 1, MonteCarlo::NEUTRON ) );
  
  TEST_ASSERT( !CMI::isCellVoid( 13, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 83, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 154, MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 168, MonteCarlo::NEUTRON ) );

  TEST_ASSERT( !CMI::isCellVoid( 26, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 27, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 28, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 29, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 30, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 31, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 32, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 33, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 34, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 35, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 36, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 37, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 48, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 49, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 50, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 51, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 52, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 53, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 54, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 55, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 56, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 57, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 58, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 59, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 70, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 71, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 72, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 73, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 74, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 75, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 76, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 77, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 78, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 79, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 80, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 81, MonteCarlo::PHOTON ) );
  
  TEST_ASSERT( !CMI::isCellVoid( 9, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 88, MonteCarlo::PHOTON ) );
  
  TEST_ASSERT( !CMI::isCellVoid( 136, MonteCarlo::PHOTON ) );
  
  TEST_ASSERT( !CMI::isCellVoid( 19, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 41, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 63, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 82, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 152, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 166, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 184, MonteCarlo::PHOTON ) );
  
  TEST_ASSERT( !CMI::isCellVoid( 3, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 7, MonteCarlo::PHOTON ) );
  
  TEST_ASSERT( !CMI::isCellVoid( 5, MonteCarlo::PHOTON ) );
  
  TEST_ASSERT( !CMI::isCellVoid( 1, MonteCarlo::PHOTON ) );
  
  TEST_ASSERT( !CMI::isCellVoid( 13, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 83, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 154, MonteCarlo::PHOTON ) );
  TEST_ASSERT( !CMI::isCellVoid( 168, MonteCarlo::PHOTON ) );
}

//---------------------------------------------------------------------------//
// Check if the macroscopic total cross section in a cell can be retrieved
TEUCHOS_UNIT_TEST( ModuleInterface, getMacroscopicTotalCrossSection )
{
  typedef MonteCarlo::CollisionModuleInterface<MonteCarlo::CollisionHandler> CMI;
  
  MonteCarlo::NeutronState neutron( 0ull );
  neutron.setEnergy( 1.0e-11 );
  neutron.setCell( 26 );
  
  double cross_section = 
    CMI::getMacroscopicTotalCrossSection( neutron );
  
  TEST_FLOATING_EQUALITY( cross_section, 5508.0178459802, 1e-13 );

  neutron.setEnergy( 2.0e1 );

  cross_section = 
    CMI::getMacroscopicTotalCrossSection( neutron );

  TEST_FLOATING_EQUALITY( cross_section, 2.2587650565199, 1e-9 );
}

//---------------------------------------------------------------------------//
// Check if the reaction cross section in a cell can be retrieved
TEUCHOS_UNIT_TEST( ModuleInterface, getMacroscopicReactionCrossSection )
{
  typedef MonteCarlo::CollisionModuleInterface<MonteCarlo::CollisionHandler> CMI;
  
  MonteCarlo::NeutronState neutron( 0ull );
  neutron.setEnergy( 1.0e-11 );
  neutron.setCell( 26 );
  
  double cross_section = 
    CMI::getMacroscopicReactionCrossSection( neutron, 
					     MonteCarlo::N__TOTAL_REACTION );
  
  TEST_FLOATING_EQUALITY( cross_section, 5508.0178459802, 1e-13 );

  neutron.setEnergy( 2.0e1 );

  cross_section = 
    CMI::getMacroscopicReactionCrossSection( neutron, 
					     MonteCarlo::N__TOTAL_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 2.2587650565199, 1e-9 );

  neutron.setEnergy( 1.0e-11 );

  cross_section = 
    CMI::getMacroscopicReactionCrossSection( neutron, 
					     MonteCarlo::N__N_ELASTIC_REACTION );
  
  TEST_FLOATING_EQUALITY( cross_section, 5429.8779115975, 1e-13 );

  neutron.setEnergy( 2.0e1 );

  cross_section = 
    CMI::getMacroscopicReactionCrossSection( neutron, 
					     MonteCarlo::N__N_ELASTIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 2.2586376828559, 1e-9 );
}

//---------------------------------------------------------------------------//
// Check that a neutron can collide with the material in a cell
TEUCHOS_UNIT_TEST( ModuleInterface, collideWithCellMaterial )
{
  typedef MonteCarlo::CollisionModuleInterface<MonteCarlo::CollisionHandler> CMI;
  
  MonteCarlo::NeutronState neutron( 0ull );
  neutron.setCell( 26 );
  neutron.setDirection( 0.0, 0.0, 1.0 );
  neutron.setEnergy( 1.0 );
  neutron.setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;

  CMI::collideWithCellMaterial( neutron, bank, true );

  TEST_EQUALITY_CONST( neutron.getWeight(), 1.0 );

  neutron.setEnergy( 1.0 );
  
  CMI::collideWithCellMaterial( neutron, bank, true );

  TEST_EQUALITY_CONST( neutron.getWeight(), 1.0 );  

  neutron.setEnergy( 1.03125e-11 );

  CMI::collideWithCellMaterial( neutron, bank, false );

  TEST_FLOATING_EQUALITY( neutron.getWeight(), 0.98581348192787, 1e-14 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_cross_sections_xml_directory;
  std::string test_material_xml_file_name;
  std::string test_geom_xml_file_name;
 
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

  {
    // Initialize DagMC
    Teuchos::RCP<Teuchos::ParameterList> geom_rep = 
      Teuchos::getParametersFromXmlFile( test_geom_xml_file_name );
    
    Geometry::DagMCInstanceFactory::initializeDagMC( *geom_rep );

    // Initialize the particle mode
    MonteCarlo::SimulationGeneralProperties::setParticleMode( MonteCarlo::NEUTRON_PHOTON_MODE );
    
    // Initialize the random number generator
    Utility::RandomNumberGenerator::createStreams();
    
    // Initialize the collison handler
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

  MonteCarlo::getCollisionHandlerFactoryInstance<Geometry::DagMC>()->initializeHandler( 
					   material_reps,
					   cross_section_table_info,
					   test_cross_sections_xml_directory );
  }

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
// end tstModuleInterface.cpp
//---------------------------------------------------------------------------//
