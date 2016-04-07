//---------------------------------------------------------------------------//
//!
//! \file   tstModuleInterfaceElectronMode.cpp
//! \author Luke Kersting
//! \brief  Collision module interface unit tests for electron mode
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
  
  TEST_ASSERT( !CMI::isCellVoid( 26, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 27, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 28, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 29, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 30, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 31, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 32, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 33, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 34, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 35, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 36, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 37, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 48, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 49, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 50, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 51, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 52, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 53, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 54, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 55, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 56, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 57, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 58, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 59, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 70, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 71, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 72, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 73, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 74, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 75, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 76, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 77, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 78, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 79, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 80, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 81, MonteCarlo::ELECTRON ) );
  
  TEST_ASSERT( !CMI::isCellVoid( 9, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 88, MonteCarlo::ELECTRON ) );
  
  TEST_ASSERT( !CMI::isCellVoid( 136, MonteCarlo::ELECTRON ) );
  
  TEST_ASSERT( !CMI::isCellVoid( 19, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 41, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 63, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 82, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 152, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 166, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 184, MonteCarlo::ELECTRON ) );
  
  TEST_ASSERT( !CMI::isCellVoid( 3, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 7, MonteCarlo::ELECTRON ) );
  
  TEST_ASSERT( !CMI::isCellVoid( 5, MonteCarlo::ELECTRON ) );
  
  TEST_ASSERT( !CMI::isCellVoid( 1, MonteCarlo::ELECTRON ) );
  
  TEST_ASSERT( !CMI::isCellVoid( 13, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 83, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 154, MonteCarlo::ELECTRON ) );
  TEST_ASSERT( !CMI::isCellVoid( 168, MonteCarlo::ELECTRON ) );
}
/*
//---------------------------------------------------------------------------//
// Check if the macroscopic total cross section in a cell can be retrieved
TEUCHOS_UNIT_TEST( ModuleInterface, getMacroscopicTotalCrossSection )
{
  typedef MonteCarlo::CollisionModuleInterface<MonteCarlo::CollisionHandler> CMI;
  
  MonteCarlo::ElectronState electron( 0ull );
  electron.setEnergy( 1.0e-05 );
  electron.setCell( 26 );
  
  double cross_section = 
    CMI::getMacroscopicTotalCrossSection( electron );
  
  TEST_FLOATING_EQUALITY( cross_section, 7.641204418336E+06, 1e-12 );

  electron.setEnergy( 1.0e+05 );

  cross_section = 
    CMI::getMacroscopicTotalCrossSection( electron );

  TEST_FLOATING_EQUALITY( cross_section, 8.269992326372E+03, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check if the reaction cross section in a cell can be retrieved
TEUCHOS_UNIT_TEST( ModuleInterface, getMacroscopicReactionCrossSection )
{
  typedef MonteCarlo::CollisionModuleInterface<MonteCarlo::CollisionHandler> CMI;
  
  MonteCarlo::ElectronState electron( 0ull );
  electron.setEnergy( 1.0e-05 );
  electron.setCell( 26 );

  // Test that the atomic excitation cross section can be returned
  double cross_section = CMI::getMacroscopicReactionCrossSection( 
                         electron,
				         MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 2.545329003693E+04, 1e-12 );

  electron.setEnergy( 1.0e+05 );
  cross_section = CMI::getMacroscopicReactionCrossSection( 
                    electron,
				    MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 4.588134602166E+03, 1e-12 );

  // Test that the bremsstrahlung cross section can be returned
  electron.setEnergy( 1.0e-05 );
  cross_section = CMI::getMacroscopicReactionCrossSection( 
                    electron,
				    MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 1.415377951846E+01, 1e-12 );

  electron.setEnergy( 1.0e+05 );				      
  cross_section = CMI::getMacroscopicReactionCrossSection( 
                    electron,
				    MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 5.679677054824E+00, 1e-12 );

  // Test that the K subshell electroionization cross section can be returned
  electron.setEnergy( 1.0e-05 );
  cross_section = CMI::getMacroscopicReactionCrossSection( 
              electron,
		      MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  electron.setEnergy( 8.97540E-02 );
  cross_section = CMI::getMacroscopicReactionCrossSection( 
              electron,
		      MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 3.6350071826026E-04, 1e-12 );

  electron.setEnergy( 1.0e+05 );
  cross_section = CMI::getMacroscopicReactionCrossSection( 
              electron,
		      MonteCarlo::K_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );
  
  TEST_FLOATING_EQUALITY( cross_section, 1.060615028974E-01, 1e-12 );

  // Test that the P3 subshell electroionization cross section can be returned
  electron.setEnergy( 1.0e-05 );
  cross_section = CMI::getMacroscopicReactionCrossSection( 
             electron,
		     MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 3.096230095899E+05, 1e-12 );

  electron.setEnergy( 1.0e+05 );
  cross_section = CMI::getMacroscopicReactionCrossSection( 
             electron,
		     MonteCarlo::P3_SUBSHELL_ELECTROIONIZATION_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 5.296521123591E+02, 1e-12 );

  // Test that the hard elastic cross section can be returned
  electron.setEnergy( 1.0e-05 );
  cross_section = CMI::getMacroscopicReactionCrossSection( 
                    electron,
			        MonteCarlo::ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 7.234825686582E+06, 1e-12 );

  electron.setEnergy( 1.0e+05 );
  cross_section = CMI::getMacroscopicReactionCrossSection( 
                    electron,
			        MonteCarlo::ELASTIC_ELECTROATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 2.566534386946E-04, 1e-12 );
}
*/
//---------------------------------------------------------------------------//
// Check that a electron can collide with the material in a cell
TEUCHOS_UNIT_TEST( ModuleInterface, collideWithCellMaterial )
{
  typedef MonteCarlo::CollisionModuleInterface<MonteCarlo::CollisionHandler> CMI;
  
  MonteCarlo::ElectronState electron( 0ull );
  electron.setCell( 26 );
  electron.setDirection( 0.0, 0.0, 1.0 );
  electron.setEnergy( 1.0 );
  electron.setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;

  CMI::collideWithCellMaterial( electron, bank, true );

  TEST_EQUALITY_CONST( electron.getWeight(), 1.0 );

  electron.setEnergy( 1.0 );
  
  CMI::collideWithCellMaterial( electron, bank, true );

  TEST_EQUALITY_CONST( electron.getWeight(), 1.0 );  

  electron.setEnergy( 1.0e-05 );

  CMI::collideWithCellMaterial( electron, bank, false );

  TEST_FLOATING_EQUALITY( electron.getWeight(), 1.0, 1e-12 );
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
    MonteCarlo::SimulationGeneralProperties::setParticleMode( MonteCarlo::ELECTRON_MODE );
    
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
