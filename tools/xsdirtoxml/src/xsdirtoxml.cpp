//---------------------------------------------------------------------------//
//!
//! \file   xsdirtoxml.cpp
//! \author Alex Robinson
//! \brief  xsdirtoxml tool
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <fstream>

// Trilinos Includes
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_CommandLineProcessor.hpp>
#include <Teuchos_FancyOStream.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "DataGen_Xsdir.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

int main( int argc, char** argv )
{
  Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  // Set up the command line options
  Teuchos::CommandLineProcessor xsdirtoxml_clp;

  std::string xsdir_file_name( "xsdir" );
  bool overwrite = false;

  xsdirtoxml_clp.setDocString( "xsdir to cross_sections.xml converter\n" );
  xsdirtoxml_clp.setOption( "xsdir_file",
			    &xsdir_file_name,
			    "The name of the xsdir file to convert" );
  xsdirtoxml_clp.setOption( "overwrite",
			    "append",
			    &overwrite,
			    "Overwrite or append the current "
			    "cross_sections.xml file" );

  // Parse the command line
  Teuchos::CommandLineProcessor::EParseCommandLineReturn
    parse_return = xsdirtoxml_clp.parse( argc, argv );

  if( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL )
  {
    xsdirtoxml_clp.printHelpMessage( argv[0], *out );
    
    return parse_return;
  }

  // Create the xsdir object
  Teuchos::RCP<DataGen::Xsdir> xsdir;

  try{
    xsdir.reset( new DataGen::Xsdir( xsdir_file_name.c_str() ) );
  }
  EXCEPTION_CATCH_AND_EXIT( std::exception, 
			    "Error creating the xsdir object!" );

  // Open the cross_sections.xml file
  Teuchos::RCP<Teuchos::ParameterList> cross_sections_xml( 
		    new Teuchos::ParameterList( "Cross Sections Directory" ) );

  if( !overwrite )
  {
    std::ifstream file( "cross_sections.xml" );

    if( file.good() )
    {
      cross_sections_xml = 
	Teuchos::getParametersFromXmlFile( "cross_sections.xml" );
    }
  }

  // Add the alias map sublist if necessary
  if( !cross_sections_xml->isSublist( "alias map" ) )
  {
    Teuchos::ParameterList& alias_map_list = 
      cross_sections_xml->sublist( "alias map" );
  }

  // Export the xsdir info
  xsdir->exportInfo( *cross_sections_xml );

  Teuchos::writeParameterListToXmlFile( *cross_sections_xml, 
					"cross_sections.xml" );

  return 0;
}

//---------------------------------------------------------------------------//
// end xsdirtoxml.cpp
//---------------------------------------------------------------------------//
