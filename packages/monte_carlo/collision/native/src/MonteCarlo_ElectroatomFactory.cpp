//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroatomFactory.cpp
//! \author Alex Robinson
//! \brief  The electroatom factory class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ElectroatomFactory.hpp"
#include "MonteCarlo_ElectroatomACEFactory.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

namespace MonteCarlo{

// Constructor
ElectroatomFactory::ElectroatomFactory(
		  const std::string& cross_sections_xml_directory,
		  const Teuchos::ParameterList& cross_section_table_info,
		  const std::unordered_set<std::string>& electroatom_aliases,
		  const Teuchos::RCP<AtomicRelaxationModelFactory>& 
		  atomic_relaxation_model_factory,
		  const BremsstrahlungAngularDistributionType 
		  photon_distribution_function,
		  const bool use_atomic_relaxation_data,
		  std::ostream* os_message )
  : d_os_message( os_message )
{
  // Make sure the message stream is valid
  testPrecondition( os_message != NULL );
  
  // Create each electroatom in the set
  std::unordered_set<std::string>::const_iterator electroatom_name = 
    electroatom_aliases.begin();

  while( electroatom_name != electroatom_aliases.end() )
  {
    Teuchos::ParameterList table_info;

    try{
      table_info = cross_section_table_info.sublist( *electroatom_name );
    }
    EXCEPTION_CATCH_AND_EXIT( std::exception,
			      "There is no data present in the "
			      "cross_sections.xml file at "
			      << cross_sections_xml_directory <<
			      " for atom " << *electroatom_name << "!" );

    // Use the appropriate procedure for the particular table type
    std::string table_type;
    
    try{
      table_type = table_info.get<std::string>( "electroatomic_file_type" );
    }
    EXCEPTION_CATCH_AND_EXIT( Teuchos::Exceptions::InvalidParameter,
			      "Error: cross section table entry "
			      << *electroatom_name << 
			      " is invalid! Please fix this entry." );

    if( table_type == "ACE" )
    {
      createElectroatomFromACETable( cross_sections_xml_directory, 
                                     *electroatom_name,
                                     table_info,
                                     atomic_relaxation_model_factory,
                                     photon_distribution_function,
                                     use_atomic_relaxation_data );
    }
    else
    {
      THROW_EXCEPTION( std::logic_error,
		       "Error: electroatomic table type " << table_type <<
		       " is not supported!" );
    }

    ++electroatom_name;
  }

  // Make sure that every electroatom has been created
  testPostcondition( d_electroatom_name_map.size() == electroatom_aliases.size() );

}

// Create the map of electroatoms
void ElectroatomFactory::createElectroatomMap(
		    std::unordered_map<std::string,Teuchos::RCP<Electroatom> >&
		    electroatom_map ) const
{
  // Reset the electroatom map
  electroatom_map.clear();

  // Copy the stored map
  electroatom_map.insert( d_electroatom_name_map.begin(), 
			              d_electroatom_name_map.end() );
}

// Create a electroatom from an ACE table
void ElectroatomFactory::createElectroatomFromACETable(
			  const std::string& cross_sections_xml_directory,
			  const std::string& electroatom_alias,
			  const Teuchos::ParameterList& electroatom_table_info,
			  const Teuchos::RCP<AtomicRelaxationModelFactory>& 
			  atomic_relaxation_model_factory,
              const BremsstrahlungAngularDistributionType 
                     photon_distribution_function,
              const bool use_atomic_relaxation_data )
{

  // Set the abs. path to the ace library file containing the desired table
  std::string ace_file_path = cross_sections_xml_directory + "/";
  
  try{
    ace_file_path += 
      electroatom_table_info.get<std::string>("electroatomic_file_path");
  }
  EXCEPTION_CATCH_AND_EXIT( Teuchos::Exceptions::InvalidParameter,
			    "Error: cross section table entry "
			    << electroatom_alias <<
			    "is invalid! Please fix this entry." );

  // Get the start line
  int electroatomic_file_start_line;
  
  try{
    electroatomic_file_start_line = 
      electroatom_table_info.get<int>( "electroatomic_file_start_line" );
  }
  EXCEPTION_CATCH_AND_EXIT( Teuchos::Exceptions::InvalidParameter,
			    "Error: cross section table entry "
			    << electroatom_alias <<
			    " is invalid! Please fix this entry." );
  
  // Get the table name
  std::string electroatomic_table_name;
  
  try{
    electroatomic_table_name = 
      electroatom_table_info.get<std::string>( "electroatomic_table_name" );
  }
  EXCEPTION_CATCH_AND_EXIT( Teuchos::Exceptions::InvalidParameter,
			    "Error: cross section table entry "
			    << electroatom_alias <<
			    " is invalid! Please fix this entry." );

  // Get the atomic weight of the electroatom
  double atomic_weight;
  
  try{
    atomic_weight = electroatom_table_info.get<double>( "atomic_weight_ratio" );
  }
  EXCEPTION_CATCH_AND_EXIT( Teuchos::Exceptions::InvalidParameter,
			    "Error: cross section table entry "
			    << electroatom_alias <<
			    " is invalid! Please fix this entry." );
  
  atomic_weight *= Utility::PhysicalConstants::neutron_rest_mass_amu;

  bool electroatomic_file_is_ascii;
  try{
    electroatomic_file_is_ascii = 
      (electroatom_table_info.get<std::string>( "electroatomic_file_type" ) ==
       "ACE");
  }
  EXCEPTION_CATCH_AND_EXIT( Teuchos::Exceptions::InvalidParameter,
			    "Error: cross section table entry "
			    << electroatom_alias <<
			    " is invalid! Please fix this entry." );
  
  *d_os_message << "Loading ACE electroatomic cross section table "
		<< electroatomic_table_name << " (" << electroatom_alias << ") ... ";

  // Check if the table has already been loaded
  if( d_electroatomic_table_name_map.find( electroatomic_table_name ) ==
      d_electroatomic_table_name_map.end() )
  {
    // Create the ACEFileHandler
    Data::ACEFileHandler ace_file_handler( ace_file_path,
					   electroatomic_table_name,
					   electroatomic_file_start_line,
					   electroatomic_file_is_ascii );
    
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

    // Initialize the new electroatom
    Teuchos::RCP<Electroatom>& electroatom = d_electroatom_name_map[electroatom_alias];

    // Create the new electroatom
    ElectroatomACEFactory::createElectroatom( xss_data_extractor,
                                              electroatomic_table_name,
                                              atomic_weight,
                                              atomic_relaxation_model,
                                              electroatom,
                                              photon_distribution_function,
                                              use_atomic_relaxation_data );

    // Cache the new electroatom in the table name map
    d_electroatomic_table_name_map[electroatomic_table_name] = electroatom;
  }
  // The table has already been loaded
  else
  {
    d_electroatom_name_map[electroatom_alias] = 
      d_electroatomic_table_name_map[electroatomic_table_name];
  }

  *d_os_message << "done." << std::endl;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomFactory.cpp
//---------------------------------------------------------------------------//
