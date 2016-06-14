//---------------------------------------------------------------------------//
//!
//! \file   endl_cs_xml_modifier.cpp
//! \author Luke Kersting
//! \brief  tool to modify the cross_section.xml file with endl data 
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
#include "MonteCarlo_CrossSectionsXMLProperties.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

int main( int argc, char** argv )
{
  
  Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  // Set up the command line options
  Teuchos::CommandLineProcessor endl_cs_xml_clp;

  std::string cross_section_directory, cross_section_alias;

  endl_cs_xml_clp.setDocString( "ENDL cross_section.xml modifier\n" );
  endl_cs_xml_clp.setOption( "cross_sec_dir",
			       &cross_section_directory,
			       "cross section tables directory",
			       true );
  endl_cs_xml_clp.setOption( "cross_sec_alias",
			       &cross_section_alias,
			       "ENDL cross section table alias",
			       true );

  endl_cs_xml_clp.throwExceptions( false );

  // Parse the command line
  Teuchos::CommandLineProcessor::EParseCommandLineReturn
    parse_return = endl_cs_xml_clp.parse( argc, argv );

  if( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL )
  {
    endl_cs_xml_clp.printHelpMessage( argv[0], *out );

    return parse_return;
  }

  // Open the cross_sections.xml file
  std::string cross_sections_xml_file = cross_section_directory;
  cross_sections_xml_file += "/cross_sections.xml";

  Teuchos::RCP<Teuchos::ParameterList> cross_sections_table_info = 
    Teuchos::getParametersFromXmlFile( cross_sections_xml_file );

  // Get info from paramter list
  std::string new_cross_section_alias( cross_section_alias );
  new_cross_section_alias += "-ENDL";

  Teuchos::ParameterList& old_table_info = 
    cross_sections_table_info->sublist( cross_section_alias );
    
  Teuchos::ParameterList& new_table_info = 
    cross_sections_table_info->sublist( new_cross_section_alias );

  new_table_info.setParameters( old_table_info );

  // Set path to endl data file
  int atomic_number = old_table_info.get<int>("atomic_number");

  std::ostringstream oss;
  oss << "endl_" << atomic_number << "_native.xml";

  std::string file_path = "endldata/";
  file_path += oss.str();

  // photoatom info    
  new_table_info.set( 
    MonteCarlo::CrossSectionsXMLProperties::photoatomic_file_path_prop,
    file_path );
  new_table_info.set( 
    MonteCarlo::CrossSectionsXMLProperties::photoatomic_file_type_prop,
    MonteCarlo::CrossSectionsXMLProperties::endl_file );
  new_table_info.set( 
    MonteCarlo::CrossSectionsXMLProperties::photoatomic_file_start_line_prop,
    -1 );
  new_table_info.set( 
    MonteCarlo::CrossSectionsXMLProperties::photoatomic_table_name_prop,
    "" );

  // electroatom info  
  new_table_info.set( 
    MonteCarlo::CrossSectionsXMLProperties::electroatomic_file_path_prop,
    file_path );
  new_table_info.set( 
    MonteCarlo::CrossSectionsXMLProperties::electroatomic_file_type_prop,
    MonteCarlo::CrossSectionsXMLProperties::endl_file );
  new_table_info.set( 
    MonteCarlo::CrossSectionsXMLProperties::electroatomic_file_start_line_prop,
    -1 );
  new_table_info.set( 
    MonteCarlo::CrossSectionsXMLProperties::electroatomic_table_name_prop,
    "" );

  Teuchos::writeParameterListToXmlFile( 
    *cross_sections_table_info,
    cross_sections_xml_file );
							      
  return 0;
}

//---------------------------------------------------------------------------//
// end endl_generator.cpp
//---------------------------------------------------------------------------//
