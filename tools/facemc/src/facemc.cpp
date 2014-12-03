//---------------------------------------------------------------------------//
//!
//! \file   facemc.cpp
//! \author Alex Robinson
//! \brief  main facemc executable
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <signal.h>

// Trilinos Includes
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_CommandLineProcessor.hpp>
#include <Teuchos_FancyOStream.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleSimulationManagerFactory.hpp"
#include "Utility_OneDDistributionEntryConverterDB.hpp"

// The simulation manager
Teuchos::RCP<MonteCarlo::SimulationManager> simulation_manager;

// The signal handler
void signalHandlerWrapper(int signal)
{
  if( !simulation_manager.is_null() )
    simulation_manager->signalHandler(signal);
}

// Main facemc function
int main( int argc, char** argv )
{
  // Assign the signal handler
  void (*handler)(int);
  handler = signal(SIGINT,signalHandlerWrapper);
  
  Utility::OneDDistributionEntryConverterDB::standardInitialization();
  
  Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::RCP<Teuchos::ParameterList> simulation_info;
  Teuchos::RCP<Teuchos::ParameterList> geometry_definition;
  Teuchos::RCP<Teuchos::ParameterList> source_definition;
  Teuchos::RCP<Teuchos::ParameterList> response_function_definitions;
  Teuchos::RCP<Teuchos::ParameterList> estimator_definitions;
  Teuchos::RCP<Teuchos::ParameterList> material_definitions;
  
  std::string simulation_info_xml_file;
  std::string geometry_definition_xml_file;
  std::string source_definition_xml_file;
  std::string response_function_definition_xml_file;
  std::string estimator_definition_xml_file;
  std::string material_definition_xml_file;
  std::string cross_section_directory;
  
  // Set up the command line options
  Teuchos::CommandLineProcessor facemc_clp;

  facemc_clp.setDocString( "Forward-Adjoint Continuous Energy Monte Carlo "
			   "Program\n" );
  facemc_clp.setOption( "sim_info", 
			&simulation_info_xml_file,
			"Name of XML file containing simulation info",
			true );
  facemc_clp.setOption( "geom_def",
			&geometry_definition_xml_file,
			"Name of XML file containing geometry definition",
			true );
  facemc_clp.setOption( "src_def",
			&source_definition_xml_file,
			"Name of XML file containing source definition",
			true );
  facemc_clp.setOption( "resp_def",
			&response_function_definition_xml_file,
			"Name of XML file containing response function "
			"definitions",
			true );
  facemc_clp.setOption( "est_def",
			&estimator_definition_xml_file,
			"Name of XML file containing estimator definitions",
			true );
  facemc_clp.setOption( "mat_def",
			&material_definition_xml_file,
			"Name of XML file containing material definitions",
			true );
  facemc_clp.setOption( "cross_sec_dir",
			&cross_section_directory,
			"Directory containing desired cross section tables",
			true );

  facemc_clp.throwExceptions( false );

  // Parse the command line
  Teuchos::CommandLineProcessor::EParseCommandLineReturn
    parse_return = facemc_clp.parse( argc, argv );
  
  if( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL )
  {
    facemc_clp.printHelpMessage( argv[0], *out );
    
    return parse_return;
  }

  // Create parameter list from the input xml files
  simulation_info = 
    Teuchos::getParametersFromXmlFile( simulation_info_xml_file );

  geometry_definition = 
    Teuchos::getParametersFromXmlFile( geometry_definition_xml_file );

  source_definition =
    Teuchos::getParametersFromXmlFile( source_definition_xml_file );

  response_function_definitions = 
    Teuchos::getParametersFromXmlFile( response_function_definition_xml_file );
  
  estimator_definitions = 
    Teuchos::getParametersFromXmlFile( estimator_definition_xml_file );
  
  material_definitions = 
    Teuchos::getParametersFromXmlFile( material_definition_xml_file );

  // Open the cross_sections.xml file
  std::string cross_sections_xml_file = cross_section_directory;
  cross_sections_xml_file += "/cross_sections.xml";

  Teuchos::RCP<Teuchos::ParameterList> cross_sections_table_info = 
    Teuchos::getParametersFromXmlFile( cross_sections_xml_file );

  // Create the simulation manager
  simulation_manager = 
    MonteCarlo::ParticleSimulationManagerFactory::createManager( 
						*simulation_info,
						*geometry_definition,
						*source_definition,
						*response_function_definitions,
						*estimator_definitions,
						*material_definitions,
						*cross_sections_table_info,
						cross_section_directory );

  // Run the simulation
  simulation_manager->runSimulation();

  // Print the simulation summary
  simulation_manager->printSimulationSummary( *out );

  return 0;
}

//---------------------------------------------------------------------------//
// end facemc.cpp
//---------------------------------------------------------------------------//
