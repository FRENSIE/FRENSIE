//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroatomFactory.cpp
//! \author Luke Kersting
//! \brief  The electroatom factory class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ElectroatomFactory.hpp"
#include "MonteCarlo_ElectroatomACEFactory.hpp"
#include "MonteCarlo_ElectroatomNativeFactory.hpp"
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
ElectroatomFactory::ElectroatomFactory(
             const boost::filesystem::path& data_directory,
             const ScatteringCenterNameSet& electroatom_names,
             const ScatteringCenterDefinitionDatabase& electroatom_definitions,
             const std::shared_ptr<AtomicRelaxationModelFactory>&
             atomic_relaxation_model_factory,
             const SimulationProperties& properties,
             const bool verbose )
  : d_electroatom_name_map(),
    d_electroatomic_table_name_map(),
    d_verbose( verbose )
{
  FRENSIE_LOG_NOTIFICATION( "Starting to load electroatom data tables ... " );
  FRENSIE_FLUSH_ALL_LOGS();

  // Create each electroatom in the set
  ScatteringCenterNameSet::const_iterator electroatom_name =
    electroatom_names.begin();

  while( electroatom_name != electroatom_names.end() )
  {
    TEST_FOR_EXCEPTION( !electroatom_definitions.doesDefinitionExist( *electroatom_name ),
                        std::runtime_error,
                        "Electroatom " << *electroatom_name << " cannot be "
                        "created because its definition has not been "
                        "specified!" );

    const ScatteringCenterDefinition& electroatom_definition =
      electroatom_definitions.getDefinition( *electroatom_name );

    TEST_FOR_EXCEPTION( !electroatom_definition.hasElectroatomicDataProperties(),
                        std::runtime_error,
                        "Electroatom " << *electroatom_name << " cannot be "
                        "created because its definition does not specify "
                        "any electroatomic data properties!" );

    double atomic_weight;

    const Data::ElectroatomicDataProperties& electroatom_data_properties =
      electroatom_definition.getElectroatomicDataProperties( &atomic_weight );

    if( electroatom_data_properties.fileType() ==
        Data::ElectroatomicDataProperties::ACE_EPR_FILE )
    {
      // Initialize the electroatomic table name map for ACE_EPR files
      if( d_electroatomic_table_name_map.find( Data::ElectroatomicDataProperties::ACE_EPR_FILE ) ==
          d_electroatomic_table_name_map.end() )
      {
        d_electroatomic_table_name_map[Data::ElectroatomicDataProperties::ACE_EPR_FILE];
      }

      this->createElectroatomFromACETable( data_directory,
                                           *electroatom_name,
                                           atomic_weight,
                                           electroatom_data_properties,
                                           atomic_relaxation_model_factory,
                                           properties );
    }
    else if( electroatom_data_properties.fileType() ==
             Data::ElectroatomicDataProperties::Native_EPR_FILE )
    {
      // Initialize the electroatomic table name map for Native_EPR files
      if( d_electroatomic_table_name_map.find( Data::ElectroatomicDataProperties::Native_EPR_FILE ) ==
          d_electroatomic_table_name_map.end() )
      {
        d_electroatomic_table_name_map[Data::ElectroatomicDataProperties::Native_EPR_FILE];
      }

      this->createElectroatomFromNativeTable( data_directory,
                                              *electroatom_name,
                                              atomic_weight,
                                              electroatom_data_properties,
                                              atomic_relaxation_model_factory,
                                              properties );
    }
    else
    {
      THROW_EXCEPTION( std::runtime_error,
                       "Electroatom " << *electroatom_name << " cannot be "
                       "created because its definition specifies the use of "
                       "an electroatomic data file of type "
                       << electroatom_data_properties.fileType() <<
                       ", which is currently unsupported!" );
    }

    ++electroatom_name;
  }

  // Make sure that every electroatom has been created
  testPostcondition( d_electroatom_name_map.size() == electroatom_names.size() );

  FRENSIE_LOG_NOTIFICATION( "Finished loading electroatom data tables." );
  FRENSIE_FLUSH_ALL_LOGS();
}

// Create the map of electroatoms
void ElectroatomFactory::createElectroatomMap(
                               ElectroatomNameMap& electroatom_name_map ) const
{
  electroatom_name_map = d_electroatom_name_map;
}

// Create a electroatom from an ACE table
void ElectroatomFactory::createElectroatomFromACETable(
                      const boost::filesystem::path& data_directory,
                      const std::string& electroatom_name,
                      const double atomic_weight,
		      const Data::ElectroatomicDataProperties& data_properties,
                      const std::shared_ptr<AtomicRelaxationModelFactory>&
                      atomic_relaxation_model_factory,
                      const SimulationProperties& properties )
{
  // Check if the table has already been loaded
  if( d_electroatomic_table_name_map[Data::ElectroatomicDataProperties::ACE_EPR_FILE].find( data_properties.tableName() ) ==
      d_electroatomic_table_name_map[Data::ElectroatomicDataProperties::ACE_EPR_FILE].end() )
  {
    // Construct the the path to the data file
    boost::filesystem::path ace_file_path = data_directory;
    ace_file_path /= data_properties.filePath();
    ace_file_path.make_preferred();

    if( d_verbose )
    {
      FRENSIE_LOG_PARTIAL_NOTIFICATION(
                                " Loading ACE EPR electroatomic cross section "
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
                             properties.isAtomicRelaxationModeOn( ELECTRON ) );

    // Initialize the new electroatom
    ElectroatomNameMap::mapped_type& electroatom =
      d_electroatom_name_map[electroatom_name];

    // Create the new electroatom
    ElectroatomACEFactory::createElectroatom( xss_data_extractor,
                                              data_properties.tableName(),
                                              atomic_weight,
                                              atomic_relaxation_model,
                                              properties,
                                              electroatom );

    // Cache the new electroatom in the table name map
    d_electroatomic_table_name_map[Data::ElectroatomicDataProperties::ACE_EPR_FILE][data_properties.tableName()] = electroatom;

    if( d_verbose )
    {
      FRENSIE_LOG_NOTIFICATION( "done." );
      FRENSIE_FLUSH_ALL_LOGS();
    }
  }
  // The table has already been loaded
  else
  {
    d_electroatom_name_map[electroatom_name] =
      d_electroatomic_table_name_map[Data::ElectroatomicDataProperties::ACE_EPR_FILE][data_properties.tableName()];
  }
}


// Create an electroatom from a Native table
void ElectroatomFactory::createElectroatomFromNativeTable(
                      const boost::filesystem::path& data_directory,
                      const std::string& electroatom_name,
                      const double atomic_weight,
                      const Data::ElectroatomicDataProperties& data_properties,
                      const std::shared_ptr<AtomicRelaxationModelFactory>&
                      atomic_relaxation_model_factory,
                      const SimulationProperties& properties )
{
  // Check if the table has already been loaded
  if( d_electroatomic_table_name_map[Data::ElectroatomicDataProperties::Native_EPR_FILE].find( data_properties.filePath().string() ) ==
      d_electroatomic_table_name_map[Data::ElectroatomicDataProperties::Native_EPR_FILE].end() )
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
                             properties.isAtomicRelaxationModeOn( ELECTRON ) );

    // Initialize the new electroatom
    ElectroatomNameMap::mapped_type& electroatom =
      d_electroatom_name_map[electroatom_name];

    // Create the new electroatom
    ElectroatomNativeFactory::createElectroatom( data_container,
                                                 data_properties.filePath().string(),
                                                 atomic_weight,
                                                 atomic_relaxation_model,
                                                 properties,
                                                 electroatom );

    // Cache the new electroatom in the table name map
    d_electroatomic_table_name_map[Data::ElectroatomicDataProperties::Native_EPR_FILE][data_properties.filePath().string()] = electroatom;

    if( d_verbose )
    {
      FRENSIE_LOG_NOTIFICATION( "done." );
      FRENSIE_FLUSH_ALL_LOGS();
    }
  }
  // The table has already been loaded
  else
  {
    d_electroatom_name_map[electroatom_name] =
      d_electroatomic_table_name_map[Data::ElectroatomicDataProperties::Native_EPR_FILE][data_properties.filePath().string()];
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomFactory.cpp
//---------------------------------------------------------------------------//
