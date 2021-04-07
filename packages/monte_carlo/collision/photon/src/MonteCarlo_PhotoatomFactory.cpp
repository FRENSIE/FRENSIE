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
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
PhotoatomFactory::PhotoatomFactory(
       const boost::filesystem::path& data_directory,
       const ScatteringCenterNameSet& photoatom_names,
       const ScatteringCenterDefinitionDatabase& photoatom_definitions,
       const std::shared_ptr<AtomicRelaxationModelFactory>&
       atomic_relaxation_model_factory,
       const SimulationProperties& properties,
       const bool verbose )
  : d_photoatom_name_map(),
    d_photoatomic_table_name_map(),
    d_verbose( verbose )
{
  FRENSIE_LOG_NOTIFICATION( "Starting to load photoatom data tables ... " );
  FRENSIE_FLUSH_ALL_LOGS();
  
  // Create each photoatom in the set
  ScatteringCenterNameSet::const_iterator photoatom_name =
    photoatom_names.begin();

  while( photoatom_name != photoatom_names.end() )
  {
    TEST_FOR_EXCEPTION( !photoatom_definitions.doesDefinitionExist( *photoatom_name ),
                        std::runtime_error,
                        "Photoatom " << *photoatom_name << " cannot be "
                        "created because its definition has not been "
                        "specified!" );

    const ScatteringCenterDefinition& photoatom_definition =
      photoatom_definitions.getDefinition( *photoatom_name );

    TEST_FOR_EXCEPTION( !photoatom_definition.hasPhotoatomicDataProperties(),
                        std::runtime_error,
                        "Photoatom " << *photoatom_name << " cannot be "
                        "created because its definition does not specify "
                        "any photoatomic data properties!" );

    double atomic_weight;

    const Data::PhotoatomicDataProperties& photoatom_data_properties =
      photoatom_definition.getPhotoatomicDataProperties( &atomic_weight );

    if( photoatom_data_properties.fileType() ==
        Data::PhotoatomicDataProperties::ACE_EPR_FILE )
    {
      // Initialize the photoatomic table name map for ACE_EPR files
      if( d_photoatomic_table_name_map.find( Data::PhotoatomicDataProperties::ACE_EPR_FILE ) ==
          d_photoatomic_table_name_map.end() )
      {
        d_photoatomic_table_name_map[Data::PhotoatomicDataProperties::ACE_EPR_FILE];
      }
        
      this->createPhotoatomFromACETable( data_directory,
                                         *photoatom_name,
                                         atomic_weight,
                                         photoatom_data_properties,
                                         atomic_relaxation_model_factory,
                                         properties );
    }
    else if( photoatom_data_properties.fileType() ==
             Data::PhotoatomicDataProperties::Native_EPR_FILE )
    {
      // Initialize the photoatomic table name map for Native EPR files
      if( d_photoatomic_table_name_map.find( Data::PhotoatomicDataProperties::Native_EPR_FILE ) ==
          d_photoatomic_table_name_map.end() )
      {
        d_photoatomic_table_name_map[Data::PhotoatomicDataProperties::Native_EPR_FILE];
      }
      
      this->createPhotoatomFromNativeTable( data_directory,
                                            *photoatom_name,
                                            atomic_weight,
                                            photoatom_data_properties,
                                            atomic_relaxation_model_factory,
                                            properties );
    }
    else
    {
      THROW_EXCEPTION( std::runtime_error,
                       "Photoatom " << *photoatom_name << " cannot be "
                       "created because its definition specifies the use of a "
                       "photoatomic data file of type "
                       << photoatom_data_properties.fileType() <<
                       ", which is currently unsupported!" );
    }

    ++photoatom_name;
  }

  // Make sure that every photoatom has been created
  testPostcondition( d_photoatom_name_map.size() == photoatom_names.size() );

  FRENSIE_LOG_NOTIFICATION( "Finished loading photoatom data tables." );
  FRENSIE_FLUSH_ALL_LOGS();
}

// Create the map of photoatoms
void PhotoatomFactory::createPhotoatomMap(
                                        PhotoatomNameMap& photoatom_map ) const
{
  photoatom_map = d_photoatom_name_map;
}

// Create a photoatom from an ACE table
void PhotoatomFactory::createPhotoatomFromACETable(
			const boost::filesystem::path& data_directory,
                        const std::string& photoatom_name,
                        const double atomic_weight,
			const Data::PhotoatomicDataProperties& data_properties,
                        const std::shared_ptr<AtomicRelaxationModelFactory>&
                        atomic_relaxation_model_factory,
                        const SimulationProperties& properties )
{
  // Check if the table has already been loaded
  if( d_photoatomic_table_name_map[Data::PhotoatomicDataProperties::ACE_EPR_FILE].find( data_properties.tableName() ) ==
      d_photoatomic_table_name_map[Data::PhotoatomicDataProperties::ACE_EPR_FILE].end() )
  {
    // Construct the the path to the data file
    boost::filesystem::path ace_file_path = data_directory;
    ace_file_path /= data_properties.filePath();
    ace_file_path.make_preferred();
    
    if( d_verbose )
    {
      FRENSIE_LOG_PARTIAL_NOTIFICATION(
                                   " Loading ACE EPR photoatomic cross section "
                                   "table " << data_properties.tableName() <<
                                   " from " << ace_file_path.string() <<
                                   " ... " );
      FRENSIE_FLUSH_ALL_LOGS();
    }
    
    // Create the ACEFileHandler
    Data::ACEFileHandler ace_file_handler( ace_file_path,
					   data_properties.tableName(),
					   data_properties.fileStartLine(),
					   true );

    // Create the XSS data extractor
    Data::XSSEPRDataExtractor xss_data_extractor(
					 ace_file_handler.getTableNXSArray(),
					 ace_file_handler.getTableJXSArray(),
					 ace_file_handler.getTableXSSArray() );

    // Create the atomic relaxation model
    std::shared_ptr<const AtomicRelaxationModel> atomic_relaxation_model;

    atomic_relaxation_model_factory->createAndCacheAtomicRelaxationModel(
                               xss_data_extractor,
                               atomic_relaxation_model,
                               properties.getMinPhotonEnergy(),
                               properties.getMinElectronEnergy(),
			       properties.isAtomicRelaxationModeOn( PHOTON ) );

    // Initialize the new photoatom
    PhotoatomNameMap::mapped_type& photoatom =
      d_photoatom_name_map[photoatom_name];

    // Create the new photoatom
    PhotoatomACEFactory::createPhotoatom(
                                        xss_data_extractor,
                                        data_properties.tableName(),
                                        atomic_weight,
                                        atomic_relaxation_model,
                                        properties,
                                        photoatom );
    
    // Cache the new photoatom in the table name map
    d_photoatomic_table_name_map[Data::PhotoatomicDataProperties::ACE_EPR_FILE][data_properties.tableName()] = photoatom;

    if( d_verbose )
    {
      FRENSIE_LOG_NOTIFICATION( "done." );
      FRENSIE_FLUSH_ALL_LOGS();
    }
  }
  // The table has already been loaded
  else
  {
    d_photoatom_name_map[photoatom_name] =
      d_photoatomic_table_name_map[Data::PhotoatomicDataProperties::ACE_EPR_FILE][data_properties.tableName()];
  }
}

// Create a photoatom from a Native table
void PhotoatomFactory::createPhotoatomFromNativeTable(
			const boost::filesystem::path& data_directory,
                        const std::string& photoatom_name,
                        const double atomic_weight,
                        const Data::PhotoatomicDataProperties& data_properties,
                        const std::shared_ptr<AtomicRelaxationModelFactory>&
                        atomic_relaxation_model_factory,
                        const SimulationProperties& properties )
{
  // Check if the table has already been loaded
  if( d_photoatomic_table_name_map[Data::PhotoatomicDataProperties::Native_EPR_FILE].find( data_properties.filePath().string() ) ==
      d_photoatomic_table_name_map[Data::PhotoatomicDataProperties::Native_EPR_FILE].end() )
  {
    // Construct the path to the native file
    boost::filesystem::path native_file_path = data_directory;
    native_file_path /= data_properties.filePath();
    native_file_path.make_preferred();

    if( d_verbose )
    {
      FRENSIE_LOG_PARTIAL_NOTIFICATION(
                                " Loading native EPR cross section table "
                                "(v " << data_properties.fileVersion() <<
                                ") for " << data_properties.atom() <<
                                " from " << native_file_path.string() <<
                                " ... " );
      FRENSIE_FLUSH_ALL_LOGS();
    }
    
    // Create the epr data container
    Data::ElectronPhotonRelaxationDataContainer
      data_container( native_file_path );

    // Create the atomic relaxation model
    std::shared_ptr<const AtomicRelaxationModel> atomic_relaxation_model;

    atomic_relaxation_model_factory->createAndCacheAtomicRelaxationModel(
                               data_container,
                               atomic_relaxation_model,
                               properties.getMinPhotonEnergy(),
                               properties.getMinElectronEnergy(),
                               properties.isAtomicRelaxationModeOn( PHOTON ) );

    // Initialize the new photoatom
    PhotoatomNameMap::mapped_type& photoatom =
      d_photoatom_name_map[photoatom_name];

    // Create the new photoatom
    PhotoatomNativeFactory::createPhotoatom(
                                           data_container,
                                           data_properties.filePath().string(),
                                           atomic_weight,
                                           atomic_relaxation_model,
                                           properties,
                                           photoatom );

    // Cache the new photoatom in the table name map
    d_photoatomic_table_name_map[Data::PhotoatomicDataProperties::Native_EPR_FILE][data_properties.filePath().string()] = photoatom;

    if( d_verbose )
    {
      FRENSIE_LOG_NOTIFICATION( "done." );
      FRENSIE_FLUSH_ALL_LOGS();
    }
  }
  // The table has already been loaded
  else
  {
    d_photoatom_name_map[photoatom_name] =
      d_photoatomic_table_name_map[Data::PhotoatomicDataProperties::Native_EPR_FILE][data_properties.filePath().string()];
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotoatomFactory.cpp
//---------------------------------------------------------------------------//
