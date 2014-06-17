//---------------------------------------------------------------------------//
//!
//! \file   Facemc_NuclideFactory.cpp
//! \author Alex Robinson
//! \brief  The nuclide factory class definition
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_ParameterList.hpp>

// FRENSIE Includes
#include "Facemc_NuclideFactory.hpp"
#include "Facemc_NuclearReactionFactory.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"
#include "Utility_ContractException.hpp"

namespace Facemc{

// Constructor
NuclideFactory::NuclideFactory( 
		     const std::string& cross_sections_xml_directory,
		     const Teuchos::ParameterList& cross_section_table_info,
		     const boost::unordered_set<std::string>& nuclide_aliases )
{ 
  // The ACE table reader
  Teuchos::RCP<Data::ACEFileHandler> ace_file_handler;

  // The path to the ace file
  std::string ace_file_path;

  // The XSS neutron data extractor
  Teuchos::RCP<Data::XSSNeutronDataExtractor> xss_data_extractor;

  // The nuclide that will be created
  Teuchos::RCP<Nuclide> nuclide;

  // Create each nuclide in the set
  boost::unordered_set<std::string>::const_iterator nuclide_name,
    end_nuclide_name;
  nuclide_name = nuclide_aliases.begin();
  end_nuclide_name = nuclide_aliases.end();

  while( nuclide_name != end_nuclide_name )
  {
    const Teuchos::ParameterList& table_info =
      cross_section_table_info.sublist( *nuclide_name );

    std::cout << "Loading ACE cross section table " 
	      << table_info.get<std::string>( "table_name" )
	      << " (" << *nuclide_name << ") ... ";

    // Set the abs. path to the ace library file containing the desired table
    ace_file_path = cross_sections_xml_directory + "/" + 
      table_info.get<std::string>( "file_path" );

    // Ensure that the previous ACEFileHandler get deleted
    ace_file_handler.reset();
    
    // Create a file handler for the desired library file
    ace_file_handler.reset( new Data::ACEFileHandler( 
			  ace_file_path,
			  table_info.get<std::string>( "table_name" ),
			  table_info.get<int>( "start_line" ),
			  cross_section_table_info.get<bool>( "is_ascii" ) ) );

    // Create the XSS data extractor
    xss_data_extractor.reset( new Data::XSSNeutronDataExtractor( 
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );
    
    // Create a standard nuclide
    if( !xss_data_extractor->hasUnresolvedResonanceData() )
    {
      nuclide.reset( new Nuclide( 
			      table_info.get<std::string>( "table_name" ),
			      table_info.get<int>( "atomic_number" ),
		              table_info.get<int>( "atomic_mass_number" ),
			      table_info.get<int>( "isomer_number" ),
			      table_info.get<double>( "atomic_weight_ratio" ),
			      table_info.get<double>( "temperature" ),
			      *xss_data_extractor ) );
    }
    // Create a nuclide with unresolved resonances
    else
    {
      throw std::runtime_error( "Nuclei with unresolved resonance data are not currently supported." );
    }		     

    // Add the nuclide to the map
    d_nuclide_name_map[*nuclide_name] = nuclide;

    std::cout << "done." << std::endl;

    ++nuclide_name;
  }

  // Make sure that every nuclide has been created
  testPostcondition( d_nuclide_name_map.size() == nuclide_aliases.size() );
}

// Create the map of nuclides
/*! \details the nuclide name will be converted to a unique identifier that
 * will be used as its key in the map that is populated.
 */
void NuclideFactory::createNuclideMap( 
  boost::unordered_map<std::string,Teuchos::RCP<Nuclide> >& nuclide_map ) const
{   
  // Reset the nuclide map
  nuclide_map.clear();

  // Copy the stored map
  nuclide_map.insert( d_nuclide_name_map.begin(), d_nuclide_name_map.end() );

}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_NuclideFactory.cpp
//---------------------------------------------------------------------------//
