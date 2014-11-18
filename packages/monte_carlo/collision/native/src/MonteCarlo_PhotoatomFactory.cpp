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
#include "MonteCarlo_SimulationProperties.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

// Constructor
PhotoatomFactory::PhotoatomFactory(
		    const std::string& cross_sections_xml_directory,
		    const Teuchos::ParameterList& cross_section_table_info,
		    const boost::unordered_set<std::string>& photoatom_aliases,
		    const Teuchos::RCP<AtomicRelaxationModelFactory>& 
		    atomic_relaxation_model_factory )
{
  // Create each photoatom in the set
  boost::unordered_set<std::string>::const_iterator photoatom_name = 
    photoatom_aliases.begin();

  while( photoatom_name != photoatom_aliases.end() )
  {
    const Teuchos::ParameterList& table_info = 
      cross_section_table_info.sublist( *photoatom_name );

    // Use the appropriate procedure for the particular table type
    switch( table_info.get<int>( "table_type" ) )
    {
    case 0:
      createPhotoatomFromACETable( cross_sections_xml_directory, 
				   *photoatom_name,
				   table_info,
				   atomic_relaxation_model_factory );
      break;
    default:
      THROW_EXCEPTION( std::logic_error,
		       "Error: table type " << 
		       table_info.get<int>( "table_type" ) << 
		       " is not valid!" );
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
			  atomic_relaxation_model_factory )
{
  std::string photoatom_table_name = 
    photoatom_table_info.get<std::string>( "table_name" );
  
  std::cout << "Loading ACE cross section table " << photoatom_table_name
	    << " (" << photoatom_alias << ") ... ";

  // Set the abs. path to the ace library file containing the desired table
  std::string ace_file_path = cross_sections_xml_directory + "/" +
    photoatom_table_info.get<std::string>( "file_path" );

  // Create the ACEFileHandler
  Data::ACEFileHandler ace_file_handler( 
			 ace_file_path,
			 photoatom_table_name,
			 photoatom_table_info.get<int>( "start_line" ),
			 photoatom_table_info.get<bool>( "is_ascii" ) );

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
			    SimulationProperties::isAtomicRelaxationModeOn() );

  // Initialize the new photoatom
  Teuchos::RCP<Photoatom>& photoatom = d_photoatom_name_map[photoatom_alias];

  // Create the new photoatom
  PhotoatomACEFactory::createPhotoatom( 
		       xss_data_extractor,
		       photoatom_table_name,
		       atomic_relaxation_model,
		       photoatom,
		       SimulationProperties::isPhotonDopplerBroadeningModeOn(),
		       SimulationProperties::isDetailedPairProductionModeOn(),
		       SimulationProperties::isAtomicRelaxationModeOn() );

  std::cout << "done." << std::endl;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotoatomFactory.cpp
//---------------------------------------------------------------------------//
