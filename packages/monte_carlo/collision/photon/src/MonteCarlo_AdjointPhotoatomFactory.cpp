//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointPhotoatomFactory.cpp
//! \author Alex Robinson
//! \brief  The adjoint photoatom factory class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotoatomFactory.hpp"
#include "MonteCarlo_AdjointPhotoatomNativeFactory.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_DesignByContract.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

namespace MonteCarlo{

// Constructor
AdjointPhotoatomFactory::AdjointPhotoatomFactory(
       const boost::filesystem::path& data_directory,
       const ScatteringCenterNameSet& adjoint_photoatom_names,
       const ScatteringCenterDefinitionDatabase& adjoint_photoatom_definitions,
       const SimulationAdjointPhotonProperties& properties,
       const bool verbose )
  : d_adjoint_photoatom_name_map(),
    d_adjoint_photoatomic_table_name_map(),
    d_verbose( verbose )
{
  FRENSIE_LOG_NOTIFICATION( "Starting to load adjoint photoatom data tables ... " );
  FRENSIE_FLUSH_ALL_LOGS();

  // Create each adjoint photoatom in the set
  ScatteringCenterNameSet::const_iterator adjoint_photoatom_name =
    adjoint_photoatom_names.begin();

  while( adjoint_photoatom_name != adjoint_photoatom_names.end() )
  {
    TEST_FOR_EXCEPTION( !adjoint_photoatom_definitions.doesDefinitionExist( *adjoint_photoatom_name ),
                        std::runtime_error,
                        "Adjoint photoatom " << *adjoint_photoatom_name <<
                        " cannot be created because it's definition has not "
                        "been specified!" );

    const ScatteringCenterDefinition& adjoint_photoatom_definition =
      adjoint_photoatom_definitions.getDefinition( *adjoint_photoatom_name );

    TEST_FOR_EXCEPTION( !adjoint_photoatom_definition.hasAdjointPhotoatomicDataProperties(),
                        std::runtime_error,
                        "Adjoint photoatom " << *adjoint_photoatom_name <<
                        " cannot be created because its definition does not "
                        "specify any adjoint photoatomic data properties!" );

    const Data::AdjointPhotoatomicDataProperties& adjoint_photoatom_data_properties =
      adjoint_photoatom_definition.getAdjointPhotoatomicDataProperties();

    // Get the atomic weight
    double atomic_weight;

    // Check if there is an atomic weight override
    if( adjoint_photoatom_definition.isAtomicWeightSet() )
      atomic_weight = adjoint_photoatom_definition.getAtomicWeight();
    else
      atomic_weight = adjoint_photoatom_data_properties.atomicWeight().value();

    if( adjoint_photoatom_data_properties.fileType() ==
        Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE )
    {
      // Initialize the adjoint photoatomic table name map for Native EPR
      // files
      if( d_adjoint_photoatomic_table_name_map.find( Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE ) ==
          d_adjoint_photoatomic_table_name_map.end() )
      {
        d_adjoint_photoatomic_table_name_map[Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE];
      }

      this->createAdjointPhotoatomFromNativeTable(
                                             data_directory,
                                             *adjoint_photoatom_name,
                                             atomic_weight,
                                             adjoint_photoatom_data_properties,
                                             properties );
    }
    else
    {
      THROW_EXCEPTION( std::runtime_error,
                       "Adjoint photoatom " << *adjoint_photoatom_name <<
                       " cannot be created because its definition specifies "
                       "the use of an adjoint photoatomic data file of type "
                       << adjoint_photoatom_data_properties.fileType() <<
                       ", which is currently unsupported!" );
    }

    ++adjoint_photoatom_name;
  }

  // Make sure that every adjoint photoatom has been created
  testPostcondition( d_adjoint_photoatom_name_map.size() ==
                     adjoint_photoatom_names.size() );

  FRENSIE_LOG_NOTIFICATION( "Finished loading adjoint photoatom data tables." );
  FRENSIE_FLUSH_ALL_LOGS();
}

// Create the map of adjoint photoatoms
void AdjointPhotoatomFactory::createAdjointPhotoatomMap(
                        AdjointPhotoatomNameMap& adjoint_photoatom_map ) const
{
  adjoint_photoatom_map = d_adjoint_photoatom_name_map;
}

// Create an adjoint photoatom from a Native table
void AdjointPhotoatomFactory::createAdjointPhotoatomFromNativeTable(
                 const boost::filesystem::path& data_directory,
                 const std::string& adjoint_photoatom_name,
                 const double atomic_weight,
                 const Data::AdjointPhotoatomicDataProperties& data_properties,
                 const SimulationAdjointPhotonProperties& properties )
{
  // Check if the table has already been loaded
  if( d_adjoint_photoatomic_table_name_map[Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE].find( data_properties.filePath().string() ) ==
      d_adjoint_photoatomic_table_name_map[Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE].end() )
  {
    // Construct the path to the native file
    boost::filesystem::path native_file_path = data_directory;
    native_file_path /= data_properties.filePath();
    native_file_path.make_preferred();

    if( d_verbose )
    {
      FRENSIE_LOG_PARTIAL_NOTIFICATION(
                           "Loading native adjoint EPR cross section table (v "
                           << data_properties.fileVersion() <<
                           ") for " << data_properties.atom() <<
                           " from " << native_file_path.string() <<
                           " ... " );
      FRENSIE_FLUSH_ALL_LOGS();
    }

    // Create the aepr data container
    Data::AdjointElectronPhotonRelaxationDataContainer
      data_container( native_file_path );

    // Initialize the new adjoint photoatom
    AdjointPhotoatomNameMap::mapped_type& adjoint_photoatom =
      d_adjoint_photoatom_name_map[adjoint_photoatom_name];

    // Create the new adjoint photoatom
    AdjointPhotoatomNativeFactory::createAdjointPhotoatom(
                                           data_container,
                                           data_properties.filePath().string(),
                                           atomic_weight,
                                           properties,
                                           adjoint_photoatom );

    // Cache the new adjoint photoatom in the table name map
    d_adjoint_photoatomic_table_name_map[Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE][data_properties.filePath().string()] = adjoint_photoatom;

    if( d_verbose )
    {
      FRENSIE_LOG_NOTIFICATION( "done." );
      FRENSIE_FLUSH_ALL_LOGS();
    }
  }
  // The table has already been loaded
  else
  {
    d_adjoint_photoatom_name_map[adjoint_photoatom_name] =
      d_adjoint_photoatomic_table_name_map[Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE][data_properties.filePath().string()];
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointPhotoatomFactory.cpp
//---------------------------------------------------------------------------//
