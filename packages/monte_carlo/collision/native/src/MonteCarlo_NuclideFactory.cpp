//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NuclideFactory.cpp
//! \author Alex Robinson
//! \brief  The nuclide factory class definition
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_ParameterList.hpp>

// FRENSIE Includes
#include "MonteCarlo_NuclideFactory.hpp"
#include "MonteCarlo_NuclideACEFactory.hpp"
#include "MonteCarlo_NuclearReactionACEFactory.hpp"
#include "MonteCarlo_CrossSectionsXMLProperties.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

// Constructor
NuclideFactory::NuclideFactory( 
		     const std::string& cross_sections_xml_directory,
		     const Teuchos::ParameterList& cross_section_table_info,
		     const std::unordered_set<std::string>& nuclide_aliases,
		     const bool use_unresolved_resonance_data,
		     const bool use_photon_production_data,
		     std::ostream* os_message )
  : d_os_message( os_message )
{ 
  // Make sure the message output stream is valid
  testPrecondition( os_message != NULL );
  
  // Create each nuclide in the set
  std::unordered_set<std::string>::const_iterator nuclide_name = 
    nuclide_aliases.begin();
  
  std::string nuclide_file_path, nuclide_file_type, nuclide_table_name;
  int nuclide_file_start_line;
  int atomic_number, atomic_mass_number, isomer_number;
  double atomic_weight_ratio, temperature;

  while( nuclide_name != nuclide_aliases.end() )
  {
    CrossSectionsXMLProperties::extractInfoFromNuclideTableInfoParameterList(
						  cross_sections_xml_directory,
						  *nuclide_name,
						  cross_section_table_info,
						  nuclide_file_path,
						  nuclide_file_type,
						  nuclide_table_name,
						  nuclide_file_start_line,
						  atomic_number,
						  atomic_mass_number,
						  isomer_number,
						  atomic_weight_ratio,
						  temperature );

    if( nuclide_file_type == CrossSectionsXMLProperties::ace_file )
    {
      createNuclideFromACETable( cross_sections_xml_directory,
				 *nuclide_name,
				 nuclide_file_path,
				 nuclide_table_name,
				 nuclide_file_start_line,
				 atomic_number,
				 atomic_mass_number,
				 isomer_number,
				 atomic_weight_ratio,
				 temperature,
				 use_unresolved_resonance_data,
				 use_photon_production_data );
    }
    else
    {
      THROW_EXCEPTION( std::logic_error,
		       "Error: nuclear table type " << nuclide_file_type <<
		       " is not supported!" );
    }

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
  std::unordered_map<std::string,Teuchos::RCP<Nuclide> >& nuclide_map ) const
{   
  // Reset the nuclide map
  nuclide_map.clear();

  // Copy the stored map
  nuclide_map.insert( d_nuclide_name_map.begin(), d_nuclide_name_map.end() );

}

// Create a nuclide from an ACE table
void NuclideFactory::createNuclideFromACETable(
			    const std::string& cross_sections_xml_directory,
			    const std::string& nuclide_alias,
			    const std::string& ace_file_path,
			    const std::string& nuclear_table_name,
			    const int nuclide_file_start_line,
			    const int atomic_number,
			    const int atomic_mass_number,
			    const int isomer_number,
			    const double atomic_weight_ratio,
			    const double temperature,
			    const bool use_unresolved_resonance_data,
			    const bool use_photon_production_data )
{
  // Load the cross section data with the specified format
  *d_os_message << "Loading ACE cross section table " 
		<< nuclear_table_name << " (" << nuclide_alias << ") ... ";
  
  // The ACE table reader
  Data::ACEFileHandler ace_file_handler( ace_file_path,
					 nuclear_table_name,
					 nuclide_file_start_line,
					 true );
  
  // The XSS neutron data extractor
  Data::XSSNeutronDataExtractor xss_data_extractor( 
					 ace_file_handler.getTableNXSArray(),
					 ace_file_handler.getTableJXSArray(),
				         ace_file_handler.getTableXSSArray() );

  // Initialize the new nuclide
  Teuchos::RCP<Nuclide>& nuclide = d_nuclide_name_map[nuclide_alias];
  
  // Create the new nuclide
  NuclideACEFactory::createNuclide( xss_data_extractor,
				    nuclear_table_name,
				    atomic_number,
				    atomic_mass_number,
				    isomer_number,
				    atomic_weight_ratio,
				    temperature,
				    nuclide,
				    use_unresolved_resonance_data,
				    use_photon_production_data );
  
  *d_os_message << "done." << std::endl;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclideFactory.cpp
//---------------------------------------------------------------------------//
