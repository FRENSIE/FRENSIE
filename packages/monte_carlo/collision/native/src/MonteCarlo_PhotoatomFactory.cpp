//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotoatomFactory.cpp
//! \author Alex Robinson
//! \brief  The photoatom factory class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_PhotoatomFactory.hpp"
#include "MonteCarlo_PhotoatomACEFactory.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

namespace MonteCarlo{

// Constructor
PhotoatomFactory::PhotoatomFactory(
		    const std::string& cross_sections_xml_directory,
		    const Teuchos::ParameterList& cross_section_table_info,
		    const boost::unordered_set<std::string>& photoatom_aliases,
		    const Teuchos::RCP<AtomicRelaxationModelFactory>& 
		    atomic_relaxation_model_factory,
		    const bool use_doppler_broadening_data,
		    const bool use_detailed_pair_production_data,
		    const bool use_atomic_relaxation_data )
{
  // Create each photoatom in the set
  boost::unordered_set<std::string>::const_iterator photoatom_name = 
    photoatom_aliases.begin();

  while( photoatom_name != photoatom_aliases.end() )
  {
    Teuchos::ParameterList table_info;

    try{
      table_info = cross_section_table_info.sublist( *photoatom_name );
    }
    EXCEPTION_CATCH_AND_EXIT( std::exception,
			      "There is no data present in the "
			      "cross_sections.xml file at "
			      << cross_sections_xml_directory <<
			      " for atom " << *photoatom_name << "!" );

    // Use the appropriate procedure for the particular table type
    std::string table_type;
    
    try{
      table_type = table_info.get<std::string>( "photoatomic_file_type" );
    }
    EXCEPTION_CATCH_AND_EXIT( Teuchos::Exceptions::InvalidParameter,
			      "Error: cross section table entry "
			      << *photoatom_name << 
			      " is invalid! Please fix this entry." );

    if( table_type == "ACE" )
    {
      createPhotoatomFromACETable( cross_sections_xml_directory, 
				   *photoatom_name,
				   table_info,
				   atomic_relaxation_model_factory,
				   use_doppler_broadening_data,
				   use_detailed_pair_production_data,
				   use_atomic_relaxation_data );
    }
    else
    {
      THROW_EXCEPTION( std::logic_error,
		       "Error: photoatomic table type " << table_type <<
		       " is not supported!" );
    }

    ++photoatom_name;
  }

  // Make sure that every photoatom has been created
  testPostcondition( d_photoatom_name_map.size() == photoatom_aliases.size() );
}

// Create the map of photoatoms
void PhotoatomFactory::createPhotoatomMap(
		    boost::unordered_map<std::string,Teuchos::RCP<Photoatom> >&
		    photoatom_map ) const
{
  // Reset the photoatom map
  photoatom_map.clear();

  // Copy the stored map
  photoatom_map.insert( d_photoatom_name_map.begin(), 
			d_photoatom_name_map.end() );
}

// Create a photoatom from an ACE table
void PhotoatomFactory::createPhotoatomFromACETable(
			  const std::string& cross_sections_xml_directory,
			  const std::string& photoatom_alias,
			  const Teuchos::ParameterList& photoatom_table_info,
			  const Teuchos::RCP<AtomicRelaxationModelFactory>& 
			  atomic_relaxation_model_factory,
			  const bool use_doppler_broadening_data,
			  const bool use_detailed_pair_production_data,
			  const bool use_atomic_relaxation_data )
{
  // Set the abs. path to the ace library file containing the desired table
  std::string ace_file_path = cross_sections_xml_directory + "/";
  
  try{
    ace_file_path += 
      photoatom_table_info.get<std::string>("photoatomic_file_path");
  }
  EXCEPTION_CATCH_AND_EXIT( Teuchos::Exceptions::InvalidParameter,
			    "Error: cross section table entry "
			    << photoatom_alias <<
			    "is invalid! Please fix this entry." );

  // Get the start line
  int photoatomic_file_start_line;
  
  try{
    photoatomic_file_start_line = 
      photoatom_table_info.get<int>( "photoatomic_file_start_line" );
  }
  EXCEPTION_CATCH_AND_EXIT( Teuchos::Exceptions::InvalidParameter,
			    "Error: cross section table entry "
			    << photoatom_alias <<
			    " is invalid! Please fix this entry." );
  
  // Get the table name
  std::string photoatomic_table_name;
  
  try{
    photoatomic_table_name = 
      photoatom_table_info.get<std::string>( "photoatomic_table_name" );
  }
  EXCEPTION_CATCH_AND_EXIT( Teuchos::Exceptions::InvalidParameter,
			    "Error: cross section table entry "
			    << photoatom_alias <<
			    " is invalid! Please fix this entry." );

  // Get the atomic weight of the photoatom
  double atomic_weight;
  
  try{
    atomic_weight = photoatom_table_info.get<double>( "atomic_weight_ratio" );
  }
  EXCEPTION_CATCH_AND_EXIT( Teuchos::Exceptions::InvalidParameter,
			    "Error: cross section table entry "
			    << photoatom_alias <<
			    " is invalid! Please fix this entry." );
  
  atomic_weight *= Utility::PhysicalConstants::neutron_rest_mass_amu;

  bool photoatomic_file_is_ascii;
  try{
    photoatomic_file_is_ascii = 
      (photoatom_table_info.get<std::string>( "photoatomic_file_type" ) ==
       "ACE");
  }
  EXCEPTION_CATCH_AND_EXIT( Teuchos::Exceptions::InvalidParameter,
			    "Error: cross section table entry "
			    << photoatom_alias <<
			    " is invalid! Please fix this entry." );
  
  std::cout << "Loading ACE photoatomic cross section table "
	    << photoatomic_table_name << " (" << photoatom_alias << ") ... ";

  // Check if the table has already been loaded
  if( d_photoatomic_table_name_map.find( photoatomic_table_name ) ==
      d_photoatomic_table_name_map.end() )
  {
    // Create the ACEFileHandler
    Data::ACEFileHandler ace_file_handler( ace_file_path,
					   photoatomic_table_name,
					   photoatomic_file_start_line,
					   photoatomic_file_is_ascii );
    
    // Create the XSS data extractor
    Data::XSSEPRDataExtractor xss_data_extractor( 
					 ace_file_handler.getTableNXSArray(),
					 ace_file_handler.getTableJXSArray(),
					 ace_file_handler.getTableXSSArray() );
  
    // Create the atomic relaxation model
    Teuchos::RCP<AtomicRelaxationModel> atomic_relaxation_model;
    
    atomic_relaxation_model_factory->createAndCacheAtomicRelaxationModel(
						  xss_data_extractor,
						  atomic_relaxation_model,
			                          use_atomic_relaxation_data );

    // Initialize the new photoatom
    Teuchos::RCP<Photoatom>& photoatom = d_photoatom_name_map[photoatom_alias];

    // Create the new photoatom
    PhotoatomACEFactory::createPhotoatom( xss_data_extractor,
					  photoatomic_table_name,
					  atomic_weight,
					  atomic_relaxation_model,
					  photoatom,
					  use_doppler_broadening_data,
					  use_detailed_pair_production_data,
					  use_atomic_relaxation_data );

    // Cache the new photoatom in the table name map
    d_photoatomic_table_name_map[photoatomic_table_name] = photoatom;
  }
  // The table has already been loaded
  else
  {
    d_photoatom_name_map[photoatom_alias] = 
      d_photoatomic_table_name_map[photoatomic_table_name];
  }

  std::cout << "done." << std::endl;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotoatomFactory.cpp
//---------------------------------------------------------------------------//
