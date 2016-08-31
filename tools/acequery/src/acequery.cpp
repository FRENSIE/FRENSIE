//---------------------------------------------------------------------------//
//!
//! \file   acequery.cpp
//! \author Alex Robinson, Eli Moll
//! \brief  acequery tool
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
#include "Data_CrossSectionsXMLProperties.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

int main( int argc, char** argv )
{
  Teuchos::RCP<Teuchos::FancyOStream> out =
    Teuchos::VerboseObjectBase::getDefaultOStream();

  // Set up the command line options
  Teuchos::CommandLineProcessor acequery_clp;

  std::string cs_directory;
  std::string cs_alias;

  acequery_clp.setDocString( "Query information in the requested continuous energy neutron ACE table.\n");
  acequery_clp.setOption( "cs_dir",
			  &cs_directory,
			  "The name (and location) of the cross_sections.xml "
			  "file" );
  acequery_clp.setOption( "cs_alias",
			  &cs_alias,
			  "Neutron cross section table alias",
			  true );

  acequery_clp.throwExceptions( false );

  // Parse the command line
  Teuchos::CommandLineProcessor::EParseCommandLineReturn
    parse_return = acequery_clp.parse( argc, argv );

  if( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL )
  {
    acequery_clp.printHelpMessage( argv[0], *out );

    return parse_return;
  }

  // Open the cross_sections.xml file
  std::string cross_sections_xml_file = cs_directory;
  cross_sections_xml_file += "/cross_sections.xml";

  Teuchos::RCP<Teuchos::ParameterList> cs_table_info =
    Teuchos::getParametersFromXmlFile( cross_sections_xml_file );

  std::string data_file_path, data_file_type, data_table_name;
  int data_file_start_line, atomic_number, atomic_mass_number, isomer_number;
  double atomic_weight_ratio, temperature;

  Data::CrossSectionsXMLProperties::extractInfoFromNuclideTableInfoParameterList(
							 cs_directory,
							 cs_alias,
							 *cs_table_info,
							 data_file_path,
							 data_file_type,
							 data_table_name,
							 data_file_start_line,
							 atomic_number,
							 atomic_mass_number,
							 isomer_number,
							 atomic_weight_ratio,
							 temperature );

  // Create the data extractor
  if( data_file_type == "ACE" )
  {
    Teuchos::RCP<const Data::XSSNeutronDataExtractor> data_extractor;

    {
      Data::ACEFileHandler ace_file_handler( data_file_path,
					     data_table_name,
					     data_file_start_line,
					     true );

      data_extractor.reset( new Data::XSSNeutronDataExtractor(
				       ace_file_handler.getTableNXSArray(),
				       ace_file_handler.getTableJXSArray(),
				       ace_file_handler.getTableXSSArray() ) );
    }

    std::cout << "ACE table name: " << data_table_name << "\n" << std::endl;

    Teuchos::ArrayView<const double> MTRBlock =
                                             data_extractor->extractMTRBlock();

    std::cout << "Neutron MT Numbers: \n\n";
    for ( int i = 0; i < MTRBlock.size(); ++i )
    {
      if ( i != MTRBlock.size() - 1 )
      {
        std::cout << int (MTRBlock[i]) << ", ";
      }
      else
      {
        std::cout << int (MTRBlock[i]);
      }
    }
    std::cout << std::endl;

    Teuchos::ArrayView<const double> MTRPBlock =
                                            data_extractor->extractMTRPBlock();

    std::cout << "\nPhoton Production MT Numbers: \n\n";
    for ( int i = 0; i < MTRPBlock.size(); ++i )
    {
      if ( i != MTRPBlock.size() - 1 )
      {
        std::cout << int (MTRPBlock[i]) << ", ";
      }
      else
      {
        std::cout << int (MTRPBlock[i]);
      }
    }
    std::cout << std::endl;

    Teuchos::ArrayRCP<double> AceLaws = data_extractor->extractAceLaws();

    std::cout << "\nAce Laws (MT Number): \n\n";
    for ( int i = 0; i < AceLaws.size(); ++i )
    {
      if ( i != AceLaws.size() - 1 )
      {
        std::cout << int (AceLaws[i]) << " (" << int (MTRBlock[i]) << "), ";
      }
      else
      {
        std::cout << int (AceLaws[i]) << " (" << int (MTRBlock[i]) << ")";
      }
    }
    std::cout << std::endl;

  }
  else
  {
    std::cerr << "Error: Only ACE tables can be queried!" << std::endl;

    return 1;
  }

  return 0;
}

//---------------------------------------------------------------------------//
// end acequery.cpp
//---------------------------------------------------------------------------//
