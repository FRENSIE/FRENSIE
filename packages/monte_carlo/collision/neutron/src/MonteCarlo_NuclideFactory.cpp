//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NuclideFactory.cpp
//! \author Alex Robinson
//! \brief  The nuclide factory class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_NuclideFactory.hpp"
#include "MonteCarlo_NuclideACEFactory.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
NuclideFactory::NuclideFactory(
                 const boost::filesystem::path& data_directory,
                 const ScatteringCenterNameSet& nuclide_names,
                 const ScatteringCenterDefinitionDatabase& nuclide_definitions,
                 const SimulationProperties& properties,
                 const bool verbose )
{
  FRENSIE_LOG_NOTIFICATION( "Starting to load nuclide data tables ... " );
  FRENSIE_FLUSH_ALL_LOGS();
  
  // Create each nuclide in the set
  ScatteringCenterNameSet::const_iterator nuclide_name =
    nuclide_names.begin();

  while( nuclide_name != nuclide_names.end() )
  {
    TEST_FOR_EXCEPTION( !nuclide_definitions.doesDefinitionExist( *nuclide_name ),
                        std::runtime_error,
                        "Nuclide " << *nuclide_name << " cannot be "
                        "created because its definition has not been "
                        "specified!" );

    const ScatteringCenterDefinition& nuclide_definition =
      nuclide_definitions.getDefinition( *nuclide_name );

    TEST_FOR_EXCEPTION( !nuclide_definition.hasNuclearDataProperties(),
                        std::runtime_error,
                        "Nuclide " << *nuclide_name << " cannot be "
                        "created because its definition does not specify "
                        "any nuclear data properties!" );

    double atomic_weight_ratio;

    const Data::NuclearDataProperties& nuclear_data_properties =
      nuclide_definition.getNuclearDataProperties( &atomic_weight_ratio );

    if( nuclear_data_properties.fileType() ==
        Data::NuclearDataProperties::ACE_FILE )
    {
      // Initialize the nuclear table name map for ACE files
      if( d_nuclear_table_name_map.find( Data::NuclearDataProperties::ACE_FILE ) ==
          d_nuclear_table_name_map.end() )
      {
        d_nuclear_table_name_map[Data::NuclearDataProperties::ACE_FILE];
      }
      
      this->createNuclideFromACETable( data_directory,
                                       *nuclide_name,
                                       atomic_weight_ratio,
                                       nuclear_data_properties,
                                       properties );
    }
    else
    {
      THROW_EXCEPTION( std::runtime_error,
                       "Nuclide " << *nuclide_name << " cannot be created "
                       "because its definition specifies the use of a "
                       "nuclear data file of type "
                       << nuclear_data_properties.fileType() <<
                       ", which is currently unsupported!" );
    }

    ++nuclide_name;
  }

  // Make sure that every nuclide has been created
  testPostcondition( d_nuclide_name_map.size() == nuclide_names.size() );

  FRENSIE_LOG_NOTIFICATION( "Finished loading nuclide data tables." );
  FRENSIE_FLUSH_ALL_LOGS();
}

// Create the map of nuclides
void NuclideFactory::createNuclideMap( NuclideNameMap& nuclide_map ) const
{
  nuclide_map = d_nuclide_name_map;
}

// Create a nuclide from an ACE table
void NuclideFactory::createNuclideFromACETable(
                            const boost::filesystem::path& data_directory,
                            const std::string& nuclide_name,
                            const double atomic_weight_ratio,
                            const Data::NuclearDataProperties& data_properties,
                            const SimulationProperties& properties )
{
  // Check if the table has already been loaded
  if( d_nuclear_table_name_map[Data::NuclearDataProperties::ACE_FILE].find( data_properties.tableName() ) ==
      d_nuclear_table_name_map[Data::NuclearDataProperties::ACE_FILE].end() )
  {
    // Construct the path to the data file
    boost::filesystem::path ace_file_path = data_directory;
    ace_file_path /= data_properties.filePath();
    ace_file_path.make_preferred();
    
    if( d_verbose )
    {
      FRENSIE_LOG_PARTIAL_NOTIFICATION( " Loading ACE cross section table "
                                        << data_properties.tableName() <<
                                        " from " << ace_file_path.string() <<
                                        " ... " );
      FRENSIE_FLUSH_ALL_LOGS();
    }

    // The ACE table reader
    Data::ACEFileHandler ace_file_handler( ace_file_path,
                                           data_properties.tableName(),
                                           data_properties.fileStartLine(),
                                           true );
    
    // The XSS neutron data extractor
    Data::XSSNeutronDataExtractor xss_data_extractor(
					 ace_file_handler.getTableNXSArray(),
					 ace_file_handler.getTableJXSArray(),
				         ace_file_handler.getTableXSSArray() );

    // Initialize the new nuclide
    NuclideNameMap::mapped_type& nuclide = d_nuclide_name_map[nuclide_name];

    // Create the new nuclide
    NuclideACEFactory::createNuclide(
                          xss_data_extractor,
                          data_properties.tableName(),
                          data_properties.zaid().atomicNumber(),
                          data_properties.zaid().atomicMassNumber(),
                          data_properties.zaid().isomerNumber(),
                          atomic_weight_ratio,
                          data_properties.evaluationTemperatureInMeV().value(),
                          properties,
                          nuclide );

    // Cache the new nuclide in the table name map
    d_nuclear_table_name_map[Data::NuclearDataProperties::ACE_FILE][data_properties.tableName()] = nuclide;
    
    if( d_verbose )
    {
      FRENSIE_LOG_NOTIFICATION( "done." );
      FRENSIE_FLUSH_ALL_LOGS();
    }
  }
  // The table has already been loaded
  else
  {
    d_nuclide_name_map[nuclide_name] =
      d_nuclear_table_name_map[Data::NuclearDataProperties::ACE_FILE][data_properties.tableName()];
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclideFactory.cpp
//---------------------------------------------------------------------------//
