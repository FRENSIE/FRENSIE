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
#include "MonteCarlo_ElectroatomNativeFactory.hpp"
#include "MonteCarlo_CrossSectionsXMLProperties.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Data_EvaluatedElectronDataContainer.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

namespace MonteCarlo{

// Constructor
ElectroatomFactory::ElectroatomFactory(
		    const std::string& cross_sections_xml_directory,
		    const Teuchos::ParameterList& cross_section_table_info,
            const boost::unordered_set<std::string>& electroatom_aliases,
	        const Teuchos::RCP<AtomicRelaxationModelFactory>& 
		        atomic_relaxation_model_factory,
            const unsigned hash_grid_bins,
		    const BremsstrahlungAngularDistributionType 
		        photon_distribution_function,
		    const bool use_atomic_relaxation_data,
            const double cutoff_angle )
{
  // Create each electroatom in the set
  boost::unordered_set<std::string>::const_iterator electroatom_name = 
    electroatom_aliases.begin();

  std::string electroatom_file_path, electroatom_file_type, electroatom_table_name;
  int electroatom_file_start_line;
  double atomic_weight;

  while( electroatom_name != electroatom_aliases.end() )
  {
    CrossSectionsXMLProperties::extractInfoFromElectroatomTableInfoParameterList(
						  cross_sections_xml_directory,
						  *electroatom_name,
						  cross_section_table_info,
						  electroatom_file_path,
						  electroatom_file_type,
						  electroatom_table_name,
						  electroatom_file_start_line,
						  atomic_weight );
						   
    if( electroatom_file_type == CrossSectionsXMLProperties::ace_file )
    {
      createElectroatomFromACETable(  
				   *electroatom_name,
				   electroatom_file_path,
				   electroatom_table_name,
				   electroatom_file_start_line,
				   atomic_weight,
				   atomic_relaxation_model_factory,
				   hash_grid_bins,
                   photon_distribution_function,
                   use_atomic_relaxation_data,
                   cutoff_angle );
    }
    else if( electroatom_file_type == CrossSectionsXMLProperties::native_file )
    {
      createElectroatomFromNativeTable( 
				    *electroatom_name,
				    electroatom_file_path,
                    atomic_weight,
				    atomic_relaxation_model_factory,
				    hash_grid_bins,
                    photon_distribution_function,  
				    use_atomic_relaxation_data,
                    cutoff_angle );
    }
    else
    {
      THROW_EXCEPTION( std::logic_error,
		       "Error: electroatomic file type " 
		       << electroatom_file_type <<
		       " is not supported!" );
    }

    ++electroatom_name;
  }

  // Make sure that every electroatom has been created
  testPostcondition( d_electroatom_name_map.size() == electroatom_aliases.size() );

}

// Create the map of electroatoms
void ElectroatomFactory::createElectroatomMap(
		    boost::unordered_map<std::string,Teuchos::RCP<Electroatom> >&
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
			  const std::string& electroatom_alias,
			  const std::string& ace_file_path,
			  const std::string& electroatomic_table_name,
			  const int electroatomic_file_start_line,
			  const double atomic_weight,
			  const Teuchos::RCP<AtomicRelaxationModelFactory>& 
			    atomic_relaxation_model_factory,
			  const unsigned hash_grid_bins,
              const BremsstrahlungAngularDistributionType 
                photon_distribution_function,
              const bool use_atomic_relaxation_data,
              const double cutoff_angle )
{
  std::cout << "Loading ACE electroatomic cross section table "
	    << electroatomic_table_name << " (" << electroatom_alias << ") ... ";

  // Check if the table has already been loaded
  if( d_electroatomic_table_name_map.find( electroatomic_table_name ) ==
      d_electroatomic_table_name_map.end() )
  {
    // Create the ACEFileHandler
    Data::ACEFileHandler ace_file_handler( ace_file_path,
					   electroatomic_table_name,
					   electroatomic_file_start_line,
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

    // Initialize the new electroatom
    Teuchos::RCP<Electroatom>& electroatom = d_electroatom_name_map[electroatom_alias];

    // Create the new electroatom
    ElectroatomACEFactory::createElectroatom( xss_data_extractor,
                                              electroatomic_table_name,
                                              atomic_weight,
                                              hash_grid_bins, 
                                              atomic_relaxation_model,
                                              electroatom,
                                              photon_distribution_function,
                                              use_atomic_relaxation_data,
                                              cutoff_angle );

    // Cache the new electroatom in the table name map
    d_electroatomic_table_name_map[electroatomic_table_name] = electroatom;
  }
  // The table has already been loaded
  else
  {
    d_electroatom_name_map[electroatom_alias] = 
      d_electroatomic_table_name_map[electroatomic_table_name];
  }

  std::cout << "done." << std::endl;
}


// Create a electroatom from a Native table
void ElectroatomFactory::createElectroatomFromNativeTable(
			  const std::string& electroatom_alias,
			  const std::string& native_file_path,
			  const double atomic_weight,
			  const Teuchos::RCP<AtomicRelaxationModelFactory>&
			    atomic_relaxation_model_factory,
			  const unsigned hash_grid_bins, 
              const BremsstrahlungAngularDistributionType 
                photon_distribution_function,
              const bool use_atomic_relaxation_data,
              const double cutoff_angle )
{
  std::cout << "Loading native electroatomic cross section table "
	    << electroatom_alias << " ... ";

  // Check if the table has already been loaded
  if( d_electroatomic_table_name_map.find( native_file_path ) ==
      d_electroatomic_table_name_map.end() )
  {
    // Create the eedl data container
    Data::EvaluatedElectronDataContainer 
      data_container( native_file_path );
  
    // Create the atomic relaxation model
    Teuchos::RCP<AtomicRelaxationModel> atomic_relaxation_model;
    
    atomic_relaxation_model_factory->createAndCacheAtomicRelaxationModel(
				    data_container,
					atomic_relaxation_model,
                    use_atomic_relaxation_data );

    // Initialize the new electroatom
    Teuchos::RCP<Electroatom>& electroatom = d_electroatom_name_map[electroatom_alias];

    // Create the new electroatom
    ElectroatomNativeFactory::createElectroatom( data_container,
					     native_file_path,
					     atomic_weight,
                         hash_grid_bins, 
					     atomic_relaxation_model,
					     electroatom,
					     photon_distribution_function,
                         use_atomic_relaxation_data,
                         cutoff_angle );

    // Cache the new electroatom in the table name map
    d_electroatomic_table_name_map[native_file_path] = electroatom;
  }
  // The table has already been loaded
  else
  {
    d_electroatom_name_map[electroatom_alias] = 
      d_electroatomic_table_name_map[native_file_path];
  }

  std::cout << "done." << std::endl;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomFactory.cpp
//---------------------------------------------------------------------------//
