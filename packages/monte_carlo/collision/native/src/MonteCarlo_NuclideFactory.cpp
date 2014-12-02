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
#include "MonteCarlo_NuclearReactionFactory.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

// Constructor
NuclideFactory::NuclideFactory( 
		     const std::string& cross_sections_xml_directory,
		     const Teuchos::ParameterList& cross_section_table_info,
		     const boost::unordered_set<std::string>& nuclide_aliases )
{ 
  // The nuclide that will be created
  Teuchos::RCP<Nuclide> nuclide;

  // Create each nuclide in the set
  boost::unordered_set<std::string>::const_iterator nuclide_name,
    end_nuclide_name;
  nuclide_name = nuclide_aliases.begin();
  end_nuclide_name = nuclide_aliases.end();

  while( nuclide_name != end_nuclide_name )
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
    
    // Set the abs. path to the ace library file containing the desired table
    std::string ace_file_path = cross_sections_xml_directory + "/";

    try{
      ace_file_path += table_info.get<std::string>( "nuclear_file_path" );
    }
    EXCEPTION_CATCH_AND_EXIT( Teuchos::Exceptions::InvalidParameter,
			      "Error: cross section table entry "
			      << *nuclide_name << 
			      " is invalid or does not contain neutron data! "
			      " Please fix this entry or select another "
			      " isotope." );

    // Get the file type
    std::string file_type;
    
    try{
      file_type = table_info.get<std::string>( "nuclear_file_type" );
    }
    EXCEPTION_CATCH_AND_EXIT( Teuchos::Exceptions::InvalidParameter,
			      "Error: cross section table entry "
			      << *nuclide_name <<
			      " is invalid! Please fix this entry." );

    // Get the start line
    int start_line;
    
    try{
      start_line = table_info.get<int>( "nuclear_file_start_line" );
    }
    EXCEPTION_CATCH_AND_EXIT( Teuchos::Exceptions::InvalidParameter,
			      "Error: cross section table entry "
			      << *nuclide_name <<
			      " is invalid! Please fix this entry." );

    // Get the table name
    std::string table_name;

    try{
      table_name = table_info.get<std::string>( "nuclear_table_name" );
    }
    EXCEPTION_CATCH_AND_EXIT( Teuchos::Exceptions::InvalidParameter,
			      "Error: cross section table entry " 
			      << *nuclide_name <<
			      " is invalid! Please fix this entry." );

    // Get the atomic number
    int atomic_number;

    try{
      atomic_number = table_info.get<int>( "atomic_number" );
    }
    EXCEPTION_CATCH_AND_EXIT( Teuchos::Exceptions::InvalidParameter,
			      "Error: cross section table entry "
			      << *nuclide_name <<
			      " is invalid! Please fix this entry." );

    // Get the atomic mass number
    int atomic_mass_number;

    try{
      atomic_mass_number = table_info.get<int>( "atomic_mass_number" );
    }
    EXCEPTION_CATCH_AND_EXIT( Teuchos::Exceptions::InvalidParameter,
			      "Error: cross section table entry "
			      << *nuclide_name <<
			      " is invalid! Please fix this entry." );

    // Get the isomer number
    int isomer_number;

    try{
      isomer_number = table_info.get<int>( "isomer_number" );
    }
    EXCEPTION_CATCH_AND_EXIT( Teuchos::Exceptions::InvalidParameter,
			      "Error: cross section table entry "
			      << *nuclide_name <<
			      " is invalid! Please fix this entry." );

    // Get the atomic weight ratio
    double atomic_weight_ratio;

    try{
      atomic_weight_ratio = table_info.get<double>( "atomic_weight_ratio" );
    }
    EXCEPTION_CATCH_AND_EXIT( Teuchos::Exceptions::InvalidParameter,
			      "Error: cross section table entry "
			      << *nuclide_name <<
			      " is invalid! Please fix this entry." );
    
    // Get the temperature
    double temperature;

    try{
      temperature = table_info.get<double>( "temperature" );
    }
    EXCEPTION_CATCH_AND_EXIT( Teuchos::Exceptions::InvalidParameter,
			      "Error: cross section table entry "
			      << *nuclide_name <<
			      " is invalid! Please fix this entry." );
    
    // Load the cross section data with the specified format
    if( file_type == "ACE" )
    {
      std::cout << "Loading ACE cross section table " 
		<< table_name << " (" << *nuclide_name << ") ... ";
      
      // The ACE table reader
      Data::ACEFileHandler ace_file_handler( ace_file_path,
					     table_name,
					     start_line,
					     true );
      
      // The XSS neutron data extractor
      Data::XSSNeutronDataExtractor xss_data_extractor( 
					 ace_file_handler.getTableNXSArray(),
					 ace_file_handler.getTableJXSArray(),
				         ace_file_handler.getTableXSSArray() );

      // Create a standard nuclide
      if( !xss_data_extractor.hasUnresolvedResonanceData() )
      {
	nuclide.reset( new Nuclide( table_name,
				    atomic_number,
				    atomic_mass_number,
				    isomer_number,
				    atomic_weight_ratio,
				    temperature,
				    xss_data_extractor ) );
      }
      // Create a nuclide with unresolved resonances
      else
      {
	std::cerr << "Warning: Nuclei with unresolved resonance data has been "
		  << "requested. Unresolved resonance data will be ignored!"
		  << std::endl;

	nuclide.reset( new Nuclide( table_name,
				    atomic_number,
				    atomic_mass_number,
				    isomer_number,
				    atomic_weight_ratio,
				    temperature,
				    xss_data_extractor ) );
      }		     

      // Add the nuclide to the map
      d_nuclide_name_map[*nuclide_name] = nuclide;

      std::cout << "done." << std::endl;
    }
    else
    {
      THROW_EXCEPTION( std::logic_error, 
		       "Error: cross section file type " << file_type <<
		       " is not currently supported!" );
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

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclideFactory.cpp
//---------------------------------------------------------------------------//
