//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PositronatomFactory.cpp
//! \author Luke Kersting
//! \brief  The positron-atom factory class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_PositronatomFactory.hpp"
#include "MonteCarlo_PositronatomACEFactory.hpp"
#include "MonteCarlo_PositronatomNativeFactory.hpp"
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
PositronatomFactory::PositronatomFactory(
            const boost::filesystem::path& data_directory,
            const ScatteringCenterNameSet& positronatom_names,
            const ScatteringCenterDefinitionDatabase& positronatom_definitions,
            const std::shared_ptr<AtomicRelaxationModelFactory>&
            atomic_relaxation_model_factory,
            const SimulationProperties& properties,
            const bool verbose )
  : d_positronatom_name_map(),
    d_positronatomic_table_name_map(),
    d_verbose( verbose )
{
  FRENSIE_LOG_NOTIFICATION( "Starting to load positronatom data tables ... " );
  FRENSIE_FLUSH_ALL_LOGS();

  // Create each positron-atom in the set
  ScatteringCenterNameSet::const_iterator positronatom_name =
    positronatom_names.begin();

  while( positronatom_name != positronatom_names.end() )
  {
    TEST_FOR_EXCEPTION( !positronatom_definitions.doesDefinitionExist( *positronatom_name ),
                        std::runtime_error,
                        "Positronatom " << *positronatom_name << " cannot be "
                        "created because its definition has not been "
                        "specified!" );

    const ScatteringCenterDefinition& positronatom_definition =
      positronatom_definitions.getDefinition( *positronatom_name );

    TEST_FOR_EXCEPTION( !positronatom_definition.hasElectroatomicDataProperties(),
                        std::runtime_error,
                        "Positronatom " << *positronatom_name << " cannot be "
                        "created because its definition does not specify "
                        "any positronatomic data properties!" );

    double atomic_weight;

    const Data::ElectroatomicDataProperties& electroatom_data_properties =
      positronatom_definition.getElectroatomicDataProperties( &atomic_weight );

    if( electroatom_data_properties.fileType() ==
        Data::ElectroatomicDataProperties::ACE_EPR_FILE )
    {
      // Initialize the positronatomic table name map for ACE_EPR files
      if( d_positronatomic_table_name_map.find( Data::ElectroatomicDataProperties::ACE_EPR_FILE ) ==
          d_positronatomic_table_name_map.end() )
      {
        d_positronatomic_table_name_map[Data::ElectroatomicDataProperties::ACE_EPR_FILE];
      }

      this->createPositronatomFromACETable( data_directory,
                                            *positronatom_name,
                                            atomic_weight,
                                            electroatom_data_properties,
                                            atomic_relaxation_model_factory,
                                            properties );
    }
    else if( electroatom_data_properties.fileType() ==
             Data::ElectroatomicDataProperties::Native_EPR_FILE )
    {
      this->createPositronatomFromNativeTable( data_directory,
                                               *positronatom_name,
                                               atomic_weight,
                                               electroatom_data_properties,
                                               atomic_relaxation_model_factory,
                                               properties );
    }
    else
    {
      THROW_EXCEPTION( std::runtime_error,
                       "Positronatom " << *positronatom_name << " cannot be "
                       "created because its definition specifies the use of "
                       "a positronatomic data file of type "
                       << electroatom_data_properties.fileType() <<
                       ", which is currently unsupported!" );
    }

    ++positronatom_name;
  }

  // Make sure that every positron-atom has been created
  testPostcondition( d_positronatom_name_map.size() == positronatom_names.size() );

  FRENSIE_LOG_NOTIFICATION( "Finished loading positronatom data tables." );
  FRENSIE_FLUSH_ALL_LOGS();
}

// Create the map of positron-atoms
void PositronatomFactory::createPositronatomMap(
                             PositronatomNameMap& positronatom_name_map ) const
{
  positronatom_name_map = d_positronatom_name_map;
}

// Create a positron-atom from an ACE table
void PositronatomFactory::createPositronatomFromACETable(
                      const boost::filesystem::path& data_directory,
                      const std::string& positronatom_name,
                      const double atomic_weight,
		      const Data::ElectroatomicDataProperties& data_properties,
                      const std::shared_ptr<AtomicRelaxationModelFactory>&
                      atomic_relaxation_model_factory,
                      const SimulationProperties& properties )
{
  // Check if the table has already been loaded
  if( d_positronatomic_table_name_map[Data::ElectroatomicDataProperties::ACE_EPR_FILE].find( data_properties.tableName() ) ==
      d_positronatomic_table_name_map[Data::ElectroatomicDataProperties::ACE_EPR_FILE].end() )
  {
    // Construct the the path to the data file
    boost::filesystem::path ace_file_path = data_directory;
    ace_file_path /= data_properties.filePath();
    ace_file_path.make_preferred();

    if( d_verbose )
    {
      FRENSIE_LOG_PARTIAL_NOTIFICATION(
                                 "Loading ACE EPR positronatomic cross section "
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

    // Initialize the new positron-atom
    PositronatomNameMap::mapped_type& positronatom =
      d_positronatom_name_map[positronatom_name];

    // Create the new positron-atom
    PositronatomACEFactory::createPositronatom( xss_data_extractor,
                                                data_properties.tableName(),
                                                atomic_weight,
                                                atomic_relaxation_model,
                                                properties,
                                                positronatom );

    // Cache the new positron-atom in the table name map
    d_positronatomic_table_name_map[Data::ElectroatomicDataProperties::ACE_EPR_FILE][data_properties.tableName()] = positronatom;

    if( d_verbose )
    {
      FRENSIE_LOG_NOTIFICATION( "done." );
      FRENSIE_FLUSH_ALL_LOGS();
    }
  }
  // The table has already been loaded
  else
  {
    d_positronatom_name_map[positronatom_name] =
      d_positronatomic_table_name_map[Data::ElectroatomicDataProperties::ACE_EPR_FILE][data_properties.tableName()];
  }
}


// Create a positron-atom from a Native table
void PositronatomFactory::createPositronatomFromNativeTable(
                      const boost::filesystem::path& data_directory,
                      const std::string& positronatom_name,
                      const double atomic_weight,
                      const Data::ElectroatomicDataProperties& data_properties,
                      const std::shared_ptr<AtomicRelaxationModelFactory>&
                      atomic_relaxation_model_factory,
                      const SimulationProperties& properties  )
{
  // Check if the table has already been loaded
  if( d_positronatomic_table_name_map[Data::ElectroatomicDataProperties::Native_EPR_FILE].find( data_properties.filePath().string() ) ==
      d_positronatomic_table_name_map[Data::ElectroatomicDataProperties::Native_EPR_FILE].end() )
  {
    // Construct the path to the native file
    boost::filesystem::path native_file_path = data_directory;
    native_file_path /= data_properties.filePath();
    native_file_path.make_preferred();

    if( d_verbose )
    {
      FRENSIE_LOG_PARTIAL_NOTIFICATION(
                                "Loading native EPR cross section table "
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

    // Initialize the new positron-atom
    PositronatomNameMap::mapped_type& positronatom =
      d_positronatom_name_map[positronatom_name];

    // Create the new positron-atom
    PositronatomNativeFactory::createPositronatom( data_container,
                                                   data_properties.filePath().string(),
                                                   atomic_weight,
                                                   atomic_relaxation_model,
                                                   properties,
                                                   positronatom );

    // Cache the new positron-atom in the table name map
    d_positronatomic_table_name_map[Data::ElectroatomicDataProperties::Native_EPR_FILE][data_properties.filePath().string()] = positronatom;

    if( d_verbose )
    {
      FRENSIE_LOG_NOTIFICATION( "done." );
      FRENSIE_FLUSH_ALL_LOGS();
    }
  }
  // The table has already been loaded
  else
  {
    d_positronatom_name_map[positronatom_name] =
      d_positronatomic_table_name_map[Data::ElectroatomicDataProperties::Native_EPR_FILE][data_properties.filePath().string()];
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PositronatomFactory.cpp
//---------------------------------------------------------------------------//
