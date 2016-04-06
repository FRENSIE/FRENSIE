//---------------------------------------------------------------------------//
//!
//! \file   facemcCore.cpp
//! \author Alex Robinson
//! \brief  main facemc function definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_CommandLineProcessor.hpp>
#include <Teuchos_FancyOStream.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "facemcCore.hpp"
#include "MonteCarlo_ParticleSimulationManagerFactory.hpp"
#include "Utility_OneDDistributionEntryConverterDB.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

std::shared_ptr<MonteCarlo::SimulationManager> facemc_manager;

/*! \details This function should be executed by simply wrapping a main 
 * function around it. If desired a signal handler can also be attached
 */
int facemcCore( int argc, 
                char** argv,
                Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm )
{
  // Make sure the communicator is valid
  testPrecondition( !comm.is_null() );
  
  Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::RCP<Teuchos::ParameterList> simulation_info;
  Teuchos::RCP<Teuchos::ParameterList> geometry_definition;
  Teuchos::RCP<Teuchos::ParameterList> source_definition;
  Teuchos::RCP<Teuchos::ParameterList> response_function_definitions;
  Teuchos::RCP<Teuchos::ParameterList> observer_definitions;
  Teuchos::RCP<Teuchos::ParameterList> material_definitions;
  
  std::string simulation_info_xml_file;
  std::string geometry_definition_xml_file;
  std::string source_definition_xml_file;
  std::string response_function_definition_xml_file;
  std::string observer_definition_xml_file;
  std::string material_definition_xml_file;
  std::string cross_section_directory;
  std::string simulation_name = "simulation.h5";
  int threads = 1;
  
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
			&observer_definition_xml_file,
			"Name of XML file containing observer definitions",
			true );
  facemc_clp.setOption( "mat_def",
			&material_definition_xml_file,
			"Name of XML file containing material definitions",
			true );
  facemc_clp.setOption( "cross_sec_dir",
			&cross_section_directory,
			"Directory containing desired cross section tables",
			true );
  facemc_clp.setOption( "simulation_name",
			&simulation_name,
			"Simulation name (default=simulation) - optional",
			false );
  facemc_clp.setOption( "threads",
			&threads,
			"Number of parallel threads (default=1) - optional",
			false );

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
  try{
    simulation_info = 
      Teuchos::getParametersFromXmlFile( simulation_info_xml_file );
  }
  EXCEPTION_CATCH_AND_EXIT( std::exception,
                            "Error: xml file " << simulation_info_xml_file <<
                            " has an xml syntax error!" );

  try{
    geometry_definition = 
      Teuchos::getParametersFromXmlFile( geometry_definition_xml_file );
  }
  EXCEPTION_CATCH_AND_EXIT( std::exception,
                            "Error: xml file " 
                            << geometry_definition_xml_file <<
                            " has an xml syntax error!" );
  
  try{
    source_definition =
      Teuchos::getParametersFromXmlFile( source_definition_xml_file );
  }
  EXCEPTION_CATCH_AND_EXIT( std::exception,
                            "Error: xml file " << source_definition_xml_file <<
                            " has an xml syntax error!" );
    
  try{
    response_function_definitions = 
      Teuchos::getParametersFromXmlFile( response_function_definition_xml_file );
  }
  EXCEPTION_CATCH_AND_EXIT( std::exception,
                            "Error: xml file " 
                            << response_function_definition_xml_file << 
                            " has an xml syntax error!" );
  try{
    observer_definitions = 
      Teuchos::getParametersFromXmlFile( observer_definition_xml_file );
  }
  EXCEPTION_CATCH_AND_EXIT( std::exception,
                            "Error: xml file " 
                            << observer_definition_xml_file <<
                            " has an xml syntax error!" );
  
  try{
    material_definitions = 
      Teuchos::getParametersFromXmlFile( material_definition_xml_file );
  }
  EXCEPTION_CATCH_AND_EXIT( std::exception,
                            "Error: xml file " 
                            << material_definition_xml_file <<
                            " has an xml syntax error!" );
  
    
  // Set up the global OpenMP session
  if( Utility::GlobalOpenMPSession::isOpenMPUsed() )
    Utility::GlobalOpenMPSession::setNumberOfThreads( threads );

  // Parse the simulation name
  if( simulation_name.find( ".h5" ) > simulation_name.size() )
    simulation_name += ".h5";

  // Open the cross_sections.xml file
  std::string cross_sections_xml_file = cross_section_directory;
  cross_sections_xml_file += "/cross_sections.xml";

  Teuchos::RCP<Teuchos::ParameterList> cross_sections_table_info;
  try{
    cross_sections_table_info = 
      Teuchos::getParametersFromXmlFile( cross_sections_xml_file );
  }
  EXCEPTION_CATCH_AND_EXIT( std::exception,
                            "Error: xml file " 
                            << cross_sections_xml_file <<
                            " has an xml syntax error!" );

  // Create the simulation manager
  try{
  facemc_manager =
    MonteCarlo::ParticleSimulationManagerFactory::createManager(
                                                *simulation_info,
                                                *geometry_definition,
                                                *source_definition,
                                                *response_function_definitions,
                                                *observer_definitions,
                                                *material_definitions,
                                                *cross_sections_table_info,
                                                cross_section_directory,
                                                comm );
  }
  EXCEPTION_CATCH_AND_EXIT( std::exception,
                            "Error: could not create the simulation "
                            "manager!" );


  // Run the simulation
  try{
    facemc_manager->runSimulation();
  }
  EXCEPTION_CATCH_AND_EXIT( std::exception,
                            "Error: could not finish the simulation!" );

  // Export the simulation data
  try{
    facemc_manager->exportSimulationData( simulation_name, *out );
  }
  EXCEPTION_CATCH_AND_EXIT( std::exception,
                            "Error: could not export the simulation data!" );

  // Print the simulation summary
  try{
    facemc_manager->printSimulationSummary( *out );
  }
  EXCEPTION_CATCH_AND_EXIT( std::exception,
                            "Error: could not print the simulation summary!" );
  
  // Create a parameter list with all inputs for continue runs
  if( comm->getRank() == 0 )
  {
    Teuchos::ParameterList master_list( "continue_run_info" );
    master_list.set( "simulation_info", *simulation_info );
    master_list.set( "geometry_definition", *geometry_definition );
    master_list.set( "source_definition", *source_definition );
    master_list.set( "response_function_definitions", *response_function_definitions );
    master_list.set( "observer_definitions", *observer_definitions );
    master_list.set( "material_definitions", *material_definitions );
    
    Teuchos::writeParameterListToXmlFile( master_list, "continue_run.xml" );
  }
  
  comm->barrier();
  
  return 0;
}

//---------------------------------------------------------------------------//
// end facemcCore.cpp
//---------------------------------------------------------------------------//
