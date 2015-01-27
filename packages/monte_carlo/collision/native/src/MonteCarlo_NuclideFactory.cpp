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
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

// Constructor
NuclideFactory::NuclideFactory( 
		     const std::string& cross_sections_xml_directory,
		     const Teuchos::ParameterList& cross_section_table_info,
		     const boost::unordered_set<std::string>& nuclide_aliases,
		     const bool use_unresolved_resonance_data,
		     const bool use_photon_production_data )
{ 
  // Create each nuclide in the set
  boost::unordered_set<std::string>::const_iterator nuclide_name = 
    nuclide_aliases.begin();
  
  while( nuclide_name != nuclide_aliases.end() )
  {
    Teuchos::ParameterList table_info;
    
    try{
      table_info = cross_section_table_info.sublist( *nuclide_name );
    }
    EXCEPTION_CATCH_AND_EXIT( std::exception,
			      "There is no data present in the "
			      "cross_sections.xml file at "
			      << cross_sections_xml_directory <<
			      " for nuclide " << *nuclide_name << "!" );

    // Use the appropriate procedure for the particular table type
    std::string table_type;

    try{ 
      table_type = table_info.get<std::string>( "nuclear_file_type" );
    }
    EXCEPTION_CATCH_AND_EXIT( Teuchos::Exceptions::InvalidParameter,
			      "Error: cross section table entry "
			      << *nuclide_name <<
			      " is invalid! Please fix this entry." );

    if( table_type == "ACE" )
    {
      createNuclideFromACETable( cross_sections_xml_directory,
				 *nuclide_name,
				 table_info,
				 use_unresolved_resonance_data,
				 use_photon_production_data );
    }
    else
    {
      THROW_EXCEPTION( std::logic_error,
		       "Error: nuclear table type " << table_type <<
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
  boost::unordered_map<std::string,Teuchos::RCP<Nuclide> >& nuclide_map ) const
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
			    const Teuchos::ParameterList& nuclide_table_info,
			    const bool use_unresolved_resonance_data,
			    const bool use_photon_production_data )
{
  // Set the abs. path to the ace library file containing the desired table
  std::string ace_file_path = cross_sections_xml_directory + "/";

  try{
    ace_file_path += 
      nuclide_table_info.get<std::string>( "nuclear_file_path" );
  }
  EXCEPTION_CATCH_AND_EXIT( Teuchos::Exceptions::InvalidParameter,
			    "Error: cross section table entry "
			    << nuclide_alias << 
			    " is invalid or does not contain neutron data! "
			    " Please fix this entry or select another "
			    " isotope." );
  
  // Get the start line
  int nuclide_file_start_line;
    
    try{
      nuclide_file_start_line = 
	nuclide_table_info.get<int>( "nuclear_file_start_line" );
    }
    EXCEPTION_CATCH_AND_EXIT( Teuchos::Exceptions::InvalidParameter,
			      "Error: cross section table entry "
			      << nuclide_alias <<
			      " is invalid! Please fix this entry." );

    // Get the table name
    std::string nuclear_table_name;

    try{
      nuclear_table_name = 
	nuclide_table_info.get<std::string>( "nuclear_table_name" );
    }
    EXCEPTION_CATCH_AND_EXIT( Teuchos::Exceptions::InvalidParameter,
			      "Error: cross section table entry " 
			      << nuclide_alias <<
			      " is invalid! Please fix this entry." );

    // Get the atomic number
    int atomic_number;

    try{
      atomic_number = nuclide_table_info.get<int>( "atomic_number" );
    }
    EXCEPTION_CATCH_AND_EXIT( Teuchos::Exceptions::InvalidParameter,
			      "Error: cross section table entry "
			      << nuclide_alias <<
			      " is invalid! Please fix this entry." );

    // Get the atomic mass number
    int atomic_mass_number;

    try{
      atomic_mass_number = nuclide_table_info.get<int>( "atomic_mass_number" );
    }
    EXCEPTION_CATCH_AND_EXIT( Teuchos::Exceptions::InvalidParameter,
			      "Error: cross section table entry "
			      << nuclide_alias <<
			      " is invalid! Please fix this entry." );

    // Get the isomer number
    int isomer_number;

    try{
      isomer_number = nuclide_table_info.get<int>( "isomer_number" );
    }
    EXCEPTION_CATCH_AND_EXIT( Teuchos::Exceptions::InvalidParameter,
			      "Error: cross section table entry "
			      << nuclide_alias <<
			      " is invalid! Please fix this entry." );

    // Get the atomic weight ratio
    double atomic_weight_ratio;

    try{
      atomic_weight_ratio = 
	nuclide_table_info.get<double>( "atomic_weight_ratio" );
    }
    EXCEPTION_CATCH_AND_EXIT( Teuchos::Exceptions::InvalidParameter,
			      "Error: cross section table entry "
			      << nuclide_alias <<
			      " is invalid! Please fix this entry." );
    
    // Get the temperature
    double temperature;

    try{
      temperature = nuclide_table_info.get<double>( "temperature" );
    }
    EXCEPTION_CATCH_AND_EXIT( Teuchos::Exceptions::InvalidParameter,
			      "Error: cross section table entry "
			      << nuclide_alias <<
			      " is invalid! Please fix this entry." );
    
    // Load the cross section data with the specified format
    std::cout << "Loading ACE cross section table " 
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
    
    std::cout << "done." << std::endl;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclideFactory.cpp
//---------------------------------------------------------------------------//
