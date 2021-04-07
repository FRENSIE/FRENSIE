//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectroatomFactory.cpp
//! \author Luke Kersting
//! \brief  The adjoint electroatom factory class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatomFactory.hpp"
#include "MonteCarlo_AdjointElectroatomNativeFactory.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
AdjointElectroatomFactory::AdjointElectroatomFactory(
     const boost::filesystem::path& data_directory,
     const ScatteringCenterNameSet& adjoint_electroatom_names,
     const ScatteringCenterDefinitionDatabase& adjoint_electroatom_definitions,
     const SimulationProperties& properties,
     const bool verbose )
  : d_adjoint_electroatom_name_map(),
    d_adjoint_electroatomic_table_name_map(),
    d_verbose( verbose )
{
  FRENSIE_LOG_NOTIFICATION( "Starting to load adjoint electroatom data tables ... " );
  FRENSIE_FLUSH_ALL_LOGS();

  // Create each adjoint electroatom in the set
  ScatteringCenterNameSet::const_iterator adjoint_electroatom_name =
    adjoint_electroatom_names.begin();

  while( adjoint_electroatom_name != adjoint_electroatom_names.end() )
  {
    TEST_FOR_EXCEPTION( !adjoint_electroatom_definitions.doesDefinitionExist( *adjoint_electroatom_name ),
                        std::runtime_error,
                        "Adjoint electroatom " << *adjoint_electroatom_name <<
                        " cannot be created because its definition has not "
                        "been specified!" );

    const ScatteringCenterDefinition& adjoint_electroatom_definition =
      adjoint_electroatom_definitions.getDefinition( *adjoint_electroatom_name );

    TEST_FOR_EXCEPTION( !adjoint_electroatom_definition.hasAdjointElectroatomicDataProperties(),
                        std::runtime_error,
                        "Adjoint electroatom " << *adjoint_electroatom_name <<
                        " cannot be created because its definition does not "
                        "specify any adjoint electroatomic data properties!" );

    double atomic_weight;

    const Data::AdjointElectroatomicDataProperties& adjoint_electroatomic_data_properties =
      adjoint_electroatom_definition.getAdjointElectroatomicDataProperties( &atomic_weight );

    if( adjoint_electroatomic_data_properties.fileType() ==
        Data::AdjointElectroatomicDataProperties::Native_EPR_FILE )
    {
      if( d_adjoint_electroatomic_table_name_map.find( Data::AdjointElectroatomicDataProperties::Native_EPR_FILE ) ==
          d_adjoint_electroatomic_table_name_map.end() )
      {
        d_adjoint_electroatomic_table_name_map[Data::AdjointElectroatomicDataProperties::Native_EPR_FILE];
      }

      this->createAdjointElectroatomFromNativeTable(
                                         data_directory,
                                         *adjoint_electroatom_name,
                                         atomic_weight,
                                         adjoint_electroatomic_data_properties,
                                         properties );
    }
    else
    {
      THROW_EXCEPTION( std::runtime_error,
                       "Adjoint electroatom " << *adjoint_electroatom_name <<
                       " cannot be created because its definition specifies "
                       "the use of an adjoint electroatomic data file of type "
                       << adjoint_electroatomic_data_properties.fileType() <<
                       ", which is currently unsupported!" );
    }

    ++adjoint_electroatom_name;
  }

  // Make sure that every adjoint electroatom has been created
  testPostcondition( d_adjoint_electroatom_name_map.size() ==
                     adjoint_electroatom_names.size() );

  FRENSIE_LOG_NOTIFICATION( "Finished loading adjoint electroatom data tables." );
  FRENSIE_FLUSH_ALL_LOGS();
}

// Create the map of adjoint electroatoms
void AdjointElectroatomFactory::createAdjointElectroatomMap(
                AdjointElectroatomNameMap& adjoint_electroatom_name_map ) const
{
  adjoint_electroatom_name_map = d_adjoint_electroatom_name_map;
}

// Create a adjoint electroatom from a Native table
void AdjointElectroatomFactory::createAdjointElectroatomFromNativeTable(
               const boost::filesystem::path& data_directory,
               const std::string& adjoint_electroatom_name,
               const double atomic_weight,
               const Data::AdjointElectroatomicDataProperties& data_properties,
               const SimulationProperties& properties )
{
  // Check if the table has already been loaded
  if( d_adjoint_electroatomic_table_name_map[Data::AdjointElectroatomicDataProperties::Native_EPR_FILE].find( data_properties.filePath().string() ) ==
      d_adjoint_electroatomic_table_name_map[Data::AdjointElectroatomicDataProperties::Native_EPR_FILE].end() )
  {
    // Construct the path to the native file
    boost::filesystem::path native_file_path = data_directory;
    native_file_path /= data_properties.filePath();
    native_file_path.make_preferred();

    if( d_verbose )
    {
      FRENSIE_LOG_PARTIAL_NOTIFICATION(
                                "Loading native adjoint EPR cross section "
                                "table (v " << data_properties.fileVersion() <<
                                ") for " << data_properties.atom() <<
                                " from " << native_file_path.string() <<
                                " ... " );
      FRENSIE_FLUSH_ALL_LOGS();
    }

    // Create the native data container
    Data::AdjointElectronPhotonRelaxationDataContainer
      data_container( native_file_path );

    // Make sure the min adjoint electron energy are within the energy grid limits
    TEST_FOR_EXCEPTION( properties.getMinAdjointElectronEnergy() < data_container.getAdjointElectronEnergyGrid().front(),
                        std::runtime_error,
                        "The minimum adjoint electron energy "
                        << properties.getMinAdjointElectronEnergy() <<
                        " was set below the minimum energy in the adjoint "
                        "electron energy grid "
                        << data_container.getAdjointElectronEnergyGrid().front() <<
                        ". Please rerun the simulation with a valid minimum "
                        "adjoint electron energy!" );

    // Make sure the max adjoint electron energy are within the energy grid limits
    TEST_FOR_EXCEPTION( properties.getMaxAdjointElectronEnergy() > data_container.getAdjointElectronEnergyGrid().back(),
                        std::runtime_error,
                        "The maximum adjoint electron energy "
                        << properties.getMaxAdjointElectronEnergy() <<
                        " was set above the maximum energy in the adjoint "
                        "electron energy grid "
                        << data_container.getAdjointElectronEnergyGrid().back() <<
                        ". Please rerun the simulation with a valid maximum "
                        "adjoint electron energy!" );

    // Initialize the new adjoint electroatom
    AdjointElectroatomNameMap::mapped_type& adjoint_electroatom =
      d_adjoint_electroatom_name_map[adjoint_electroatom_name];

    // Create the new adjoint electroatom
    AdjointElectroatomNativeFactory::createAdjointElectroatom(
                                           data_container,
                                           data_properties.filePath().string(),
                                           atomic_weight,
                                           properties,
                                           adjoint_electroatom );

    // Cache the new adjoint electroatom in the table name map
    d_adjoint_electroatomic_table_name_map[Data::AdjointElectroatomicDataProperties::Native_EPR_FILE][data_properties.filePath().string()] =
      adjoint_electroatom;

    if( d_verbose )
    {
      FRENSIE_LOG_NOTIFICATION( "done." );
      FRENSIE_FLUSH_ALL_LOGS();
    }
  }
  // The table has already been loaded
  else
  {
    d_adjoint_electroatom_name_map[adjoint_electroatom_name] =
      d_adjoint_electroatomic_table_name_map[Data::AdjointElectroatomicDataProperties::Native_EPR_FILE][data_properties.filePath().string()];
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectroatomFactory.cpp
//---------------------------------------------------------------------------//
