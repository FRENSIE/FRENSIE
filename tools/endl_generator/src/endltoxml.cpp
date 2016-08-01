//---------------------------------------------------------------------------//
//!
//! \file   endltoxml.cpp
//! \author Luke Kersting
//! \brief  tool to convert endl data files to xml format 
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>

// Trilinos Includes
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_CommandLineProcessor.hpp>
#include <Teuchos_FancyOStream.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "DataGen_StandardENDLDataGenerator.hpp"
#include "MonteCarlo_CrossSectionsXMLProperties.hpp"
#include "MonteCarlo_AtomType.hpp"
#include "Data_ENDLFileHandler.hpp"
#include "Data_ENDLVolatileDataContainer.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

int main( int argc, char** argv )
{
  Teuchos::RCP<const DataGen::ENDLDataGenerator> 
    endl_to_xml;
  
  Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  // Set up the command line options
  Teuchos::CommandLineProcessor endl_to_xml_clp;

  std::string cross_section_directory;

  endl_to_xml_clp.setDocString( "ENDL to XML Tool\n" );
  endl_to_xml_clp.setOption( "cross_sec_dir",
			       &cross_section_directory,
			       "Desired cross section directory",
			       true );

  endl_to_xml_clp.throwExceptions( false );

  // Parse the command line
  Teuchos::CommandLineProcessor::EParseCommandLineReturn
    parse_return = endl_to_xml_clp.parse( argc, argv );

  if( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL )
  {
    endl_to_xml_clp.printHelpMessage( argv[0], *out );

    return parse_return;
  }

  // Run the Python script passing a filename argument to create bash script.
  std::string command = 
    "python /home/lkersting/frensie/src/scripts/endl.py -d " + cross_section_directory;
  int error_flag = system(command.c_str());
  if ( error_flag == -1 )
  {
    std::cerr << "Error: unable to execute command: "
	      << command.c_str();
  }

  // Run the bash script to download ENDL files
  command = "bash endl.sh && rm endl.sh";
  error_flag = system(command.c_str());
  if ( error_flag == -1 )
  {
    std::cerr << "Error: unable to execute command: "
	      << command.c_str();
  }
		
  // Set array of endl element id's
  Teuchos::Array<std::string> endl_element_id(100);

  for ( int i = 0; i < endl_element_id.size(); i++ )
  {
    std::string id = std::to_string((i+1)*1000);
    if ( i < 9 )
        endl_element_id[i] = "za00" + id;
    else if ( i < 99 )
        endl_element_id[i] = "za0" + id;
    else
        endl_element_id[i] = "za" + id;
  }

  // Create the new data container
  Data::ENDLVolatileDataContainer data_container;

  std::string endl_directory_path = cross_section_directory + "/endldata";

  for ( int i = 0; i < endl_element_id.size(); i++ )
  {

  unsigned atomic_number = i+1;
  std::string eadl_file_path = 
    endl_directory_path + "/eadl/" + endl_element_id[i];
  std::string epdl_file_path = 
    endl_directory_path + "/epdl/" + endl_element_id[i];
  std::string eedl_file_path = 
    endl_directory_path + "/eedl/" + endl_element_id[i];

  endl_to_xml.reset( 
	    new const DataGen::StandardENDLDataGenerator( 
					    atomic_number,
					    eadl_file_path,
                        epdl_file_path,    
					    eedl_file_path ) );

  endl_to_xml->populateENDLDataContainer( data_container );

  std::ostringstream oss;
  oss << "endl_" << atomic_number << "_native.xml";

  std::string new_file_name= endl_directory_path;
    new_file_name += "/";
    new_file_name += oss.str();

  data_container.exportData( new_file_name,
			     Utility::ArchivableObject::XML_ARCHIVE );
  }
							      
  return 0;
}

//---------------------------------------------------------------------------//
// end endl_to_xml.cpp
//---------------------------------------------------------------------------//
