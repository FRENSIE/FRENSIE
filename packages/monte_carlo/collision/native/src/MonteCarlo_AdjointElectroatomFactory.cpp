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
#include "Data_CrossSectionsXMLProperties.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

namespace MonteCarlo{

// Constructor
AdjointElectroatomFactory::AdjointElectroatomFactory(
    const std::string& cross_sections_xml_directory,
    const Teuchos::ParameterList& cross_section_table_info,
    const std::unordered_set<std::string>& electroatom_aliases,
    const SimulationProperties& properties,
    std::ostream* os_message )
  :d_os_message( os_message )
{
  // Make sure the message stream is valid
  testPrecondition( os_message != NULL );

  // Create each adjoint electroatom in the set
  std::unordered_set<std::string>::const_iterator electroatom_name =
    electroatom_aliases.begin();

  std::string electroatom_file_path, electroatom_file_type, electroatom_table_name;
  int electroatom_file_start_line;
  double atomic_weight;

  while( electroatom_name != electroatom_aliases.end() )
  {
    Data::CrossSectionsXMLProperties::extractInfoFromAdjointElectroatomTableInfoParameterList(
                          cross_sections_xml_directory,
                          *electroatom_name,
                          cross_section_table_info,
                          electroatom_file_path,
                          electroatom_file_type,
                          electroatom_table_name,
                          electroatom_file_start_line,
                          atomic_weight );

    if( electroatom_file_type == Data::CrossSectionsXMLProperties::native_file )
    {
      createAdjointElectroatomFromNativeTable(
                *electroatom_name,
                electroatom_file_path,
                atomic_weight,
                properties );
    }
    else
    {
      THROW_EXCEPTION( std::logic_error,
               "Error: adjoint electroatomic file type "
               << electroatom_file_type <<
               " is not supported!" );
    }

    ++electroatom_name;
  }

  // Make sure that every adjoint electroatom has been created
  testPostcondition( d_electroatom_name_map.size() == electroatom_aliases.size() );

}

// Create the map of adjoint electroatoms
void AdjointElectroatomFactory::createAdjointElectroatomMap(
            std::unordered_map<std::string,Teuchos::RCP<AdjointElectroatom> >&
            electroatom_map ) const
{
  // Reset the adjoint electroatom map
  electroatom_map.clear();

  // Copy the stored map
  electroatom_map.insert( d_electroatom_name_map.begin(),
                          d_electroatom_name_map.end() );
}

// Create a adjoint electroatom from a Native table
void AdjointElectroatomFactory::createAdjointElectroatomFromNativeTable(
    const std::string& electroatom_alias,
    const std::string& native_file_path,
    const double atomic_weight,
    const SimulationProperties& properties )
{
  std::cout << "Loading native adjoint electroatomic cross section table "
            << electroatom_alias << " ... ";

  // Check if the table has already been loaded
  if( d_electroatomic_table_name_map.find( native_file_path ) ==
      d_electroatomic_table_name_map.end() )
  {
    // Create the native data container
    Data::AdjointElectronPhotonRelaxationDataContainer
      data_container( native_file_path );

    // Initialize the new adjoint electroatom
    Teuchos::RCP<AdjointElectroatom>& electroatom = d_electroatom_name_map[electroatom_alias];

    // Create the new adjoint electroatom
    AdjointElectroatomNativeFactory::createAdjointElectroatom( data_container,
                                                 native_file_path,
                                                 atomic_weight,
                                                 properties,
                                                 electroatom );

    // Cache the new adjoint electroatom in the table name map
    d_electroatomic_table_name_map[native_file_path] = electroatom;
  }
  // The table has already been loaded
  else
  {
    d_electroatom_name_map[electroatom_alias] =
      d_electroatomic_table_name_map[native_file_path];
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectroatomFactory.cpp
//---------------------------------------------------------------------------//
