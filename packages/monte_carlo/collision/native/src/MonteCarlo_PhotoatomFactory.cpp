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
#include "MonteCarlo_PhotoatomNativeFactory.hpp"
#include "MonteCarlo_CrossSectionsXMLProperties.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

namespace MonteCarlo{

// Constructor
PhotoatomFactory::PhotoatomFactory(
		    const std::string& cross_sections_xml_directory,
		    const Teuchos::ParameterList& cross_section_table_info,
		    const std::unordered_set<std::string>& photoatom_aliases,
		    const Teuchos::RCP<AtomicRelaxationModelFactory>& 
		    atomic_relaxation_model_factory,
		    const unsigned hash_grid_bins,
		    const IncoherentModelType incoherent_model,
		    const double kahn_sampling_cutoff_energy,
		    const bool use_detailed_pair_production_data,
		    const bool use_atomic_relaxation_data,
		    std::ostream* os_message )
  : d_os_message( os_message )
{
  // Make sure the message output stream is valid
  testPrecondition( os_message != NULL );
  
  // Create each photoatom in the set
  std::unordered_set<std::string>::const_iterator photoatom_name = 
    photoatom_aliases.begin();

  std::string photoatom_file_path, photoatom_file_type, photoatom_table_name;
  int photoatom_file_start_line;
  double atomic_weight;

  while( photoatom_name != photoatom_aliases.end() )
  {
    
    CrossSectionsXMLProperties::extractInfoFromPhotoatomTableInfoParameterList(
						  cross_sections_xml_directory,
						  *photoatom_name,
						  cross_section_table_info,
						  photoatom_file_path,
						  photoatom_file_type,
						  photoatom_table_name,
						  photoatom_file_start_line,
						  atomic_weight );
						   
    if( photoatom_file_type == CrossSectionsXMLProperties::ace_file )
    {
      createPhotoatomFromACETable( cross_sections_xml_directory, 
				   *photoatom_name,
				   photoatom_file_path,
				   photoatom_table_name,
				   photoatom_file_start_line,
				   atomic_weight,
				   atomic_relaxation_model_factory,
				   hash_grid_bins,
				   incoherent_model,
				   kahn_sampling_cutoff_energy,
				   use_detailed_pair_production_data,
				   use_atomic_relaxation_data );
    }
    else if( photoatom_file_type == CrossSectionsXMLProperties::native_file )
    {
      createPhotoatomFromNativeTable( cross_sections_xml_directory,
				      *photoatom_name,
				      photoatom_file_path,
				      atomic_weight,
				      atomic_relaxation_model_factory,
				      hash_grid_bins,
				      incoherent_model,
				      kahn_sampling_cutoff_energy,
				      use_detailed_pair_production_data,
				      use_atomic_relaxation_data );
    }
    else
    {
      THROW_EXCEPTION( std::logic_error,
		       "Error: photoatomic file type " 
		       << photoatom_file_type <<
		       " is not supported!" );
    }

    ++photoatom_name;
  }

  // Make sure that every photoatom has been created
  testPostcondition( d_photoatom_name_map.size() == photoatom_aliases.size() );
}

// Create the map of photoatoms
void PhotoatomFactory::createPhotoatomMap(
		    std::unordered_map<std::string,Teuchos::RCP<Photoatom> >&
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
			  const std::string& ace_file_path,
			  const std::string& photoatomic_table_name,
			  const int photoatomic_file_start_line,
			  const double atomic_weight,
			  const Teuchos::RCP<AtomicRelaxationModelFactory>& 
			  atomic_relaxation_model_factory,
			  const unsigned hash_grid_bins,
			  const IncoherentModelType incoherent_model,
			  const double kahn_sampling_cutoff_energy,
			  const bool use_detailed_pair_production_data,
			  const bool use_atomic_relaxation_data )
{
  *d_os_message << "Loading ACE photoatomic cross section table "
		<< photoatomic_table_name << " (" << photoatom_alias << ") ... ";

  // Check if the table has already been loaded
  if( d_photoatomic_table_name_map.find( photoatomic_table_name ) ==
      d_photoatomic_table_name_map.end() )
  {
    // Create the ACEFileHandler
    Data::ACEFileHandler ace_file_handler( ace_file_path,
					   photoatomic_table_name,
					   photoatomic_file_start_line,
					   true );
    
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
					  hash_grid_bins,
					  incoherent_model,
					  kahn_sampling_cutoff_energy,
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

  *d_os_message << "done." << std::endl;
}

// Create a photoatom from a Native table
void PhotoatomFactory::createPhotoatomFromNativeTable(
			  const std::string& cross_sections_xml_directory,
			  const std::string& photoatom_alias,
			  const std::string& native_file_path,
			  const double atomic_weight,
			  const Teuchos::RCP<AtomicRelaxationModelFactory>&
			  atomic_relaxation_model_factory,
			  const unsigned hash_grid_bins,
			  const IncoherentModelType incoherent_model,
			  const double kahn_sampling_cutoff_energy,
			  const bool use_detailed_pair_production_data,
			  const bool use_atomic_relaxation_data )
{
  *d_os_message << "Loading native photoatomic cross section table "
	    << photoatom_alias << " ... ";
  
  // Check if the table has already been loaded
  if( d_photoatomic_table_name_map.find( native_file_path ) ==
      d_photoatomic_table_name_map.end() )
  {
    // Create the epr data container
    Data::ElectronPhotonRelaxationDataContainer 
      data_container( native_file_path );
  
    // Create the atomic relaxation model
    Teuchos::RCP<AtomicRelaxationModel> atomic_relaxation_model;
    
    atomic_relaxation_model_factory->createAndCacheAtomicRelaxationModel(
						  data_container,
						  atomic_relaxation_model,
			                          use_atomic_relaxation_data );

    // Initialize the new photoatom
    Teuchos::RCP<Photoatom>& photoatom = d_photoatom_name_map[photoatom_alias];

    // Create the new photoatom
    PhotoatomNativeFactory::createPhotoatom( data_container,
					     native_file_path,
					     atomic_weight,
					     atomic_relaxation_model,
					     photoatom,
					     hash_grid_bins,
					     incoherent_model,
					     kahn_sampling_cutoff_energy,
					     use_detailed_pair_production_data,
					     use_atomic_relaxation_data );

    // Cache the new photoatom in the table name map
    d_photoatomic_table_name_map[native_file_path] = photoatom;
  }
  // The table has already been loaded
  else
  {
    d_photoatom_name_map[photoatom_alias] = 
      d_photoatomic_table_name_map[native_file_path];
  }

  *d_os_message << "done." << std::endl;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotoatomFactory.cpp
//---------------------------------------------------------------------------//
