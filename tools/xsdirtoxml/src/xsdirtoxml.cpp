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

// Boost Includes
#include <boost/algorithm/string/split.hpp>

// Trilinos Includes
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_CommandLineProcessor.hpp>
#include <Teuchos_FancyOStream.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "DataGen_StandardElectronPhotonRelaxationDataGenerator.hpp"
#include "MonteCarlo_CrossSectionInfoHelpers.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Data_ElectronPhotonRelaxationVolatileDataContainer.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

int main( int argc, char** argv )
{
  Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  // Set up the command line options
  Teuchos::CommandLineProcessor xsdirtoxml_clp;

  std::string xsdir_file( "xsdir" );
  bool overwrite = false;

  xsdirtoxml_clp.setDocString( "xsdir to cross_sections.xml converter\n" );
  xsdirtoxml_clp.setOption( "xsdir_file",
			    &xsdir_file,
			    "The name of the xsdir file to convert" );
  xsdirtoxml_clp.setOption( "overwrite",
			    "append",
			    overwrite,
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

  // Open the xsdir file
  ifstream xsdir_file_stream( xsdir_file.c_str() );
  
  if( !xsdir_file_stream.good() )
  {
    std::cerr << "Error: the xsdir file " << xsdir_file 
	      << " cannot be opened!" << std::endl;

    return 1;
  }

  // Open the cross_sections.xml file
  Teuchos::RCP<Teuchos::ParameterList> cross_sections_xml;

  {
    std::ifstream file( "cross_sections.xml" );

    if( file.good() )
    {
      cross_sections_xml = 
	Teuchos::getParametersFromXmlFile( "cross_sections.xml" );
    }
  }

  // Loop through the xsdir file and construct the cross_sections.xml file
  std::string xsdir_line;
  std::vector<std::string> xsdir_line_elems;
  
  while( !xsdir_file_stream.eof() )
  {
    std::getline( xsdir_file_stream, line );

    // Make sure the file stream is still valid
    if( !xsdir_file_stream.eof() )
    {
      boost::split( xsdir_line_elems, xsdir_line, boost::is_any_of( " " ) );

      
      if( xsdir_line_elems.front().find( "." ) <
	  xsdir_line_elems.front().size() )
      {
	std::vector<std::string> zaid_type;

	boost::split( zaid_type, 
		      xsdir_line_elems.front(), 
		      boost::is_any_of( "." ) );

	std::ostringstream iss( zaid_type.front() );	  
	int zaid;
	iss >> zaid;

	iss.str( zaid_type.back()[0] );
	int version;
	iss >> version;

	// Continuous energy neutron table
	if( zaid_type.back().find( "c" ) <
	    zaid_type.back().size() )
	{
	  
	}

	// Electron-photon-relaxation table
	if( zaid_type.back() == "12p" )
	{
	  
	}
      }
    }
  }
}

//---------------------------------------------------------------------------//
// end xsdirtoxml.cpp
//---------------------------------------------------------------------------//
