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
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

namespace MonteCarlo{

// Constructor
AdjointElectroatomFactory::AdjointElectroatomFactory(
    const std::string& cross_sections_xml_directory,
    const Teuchos::ParameterList& cross_section_table_info,
    const std::unordered_set<std::string>& adjoint_electroatom_aliases,
    const SimulationAdjointElectronProperties& properties,
    std::ostream* os_message )
  :d_os_message( os_message )
{
  // Make sure the message stream is valid
  testPrecondition( os_message != NULL );

  // Create each adjoint electroatom in the set
  std::unordered_set<std::string>::const_iterator adjoint_electroatom_name =
    adjoint_electroatom_aliases.begin();

  std::string file_path, file_type, table_name;
  int file_start_line;
  double atomic_weight;

  while( adjoint_electroatom_name != adjoint_electroatom_aliases.end() )
  {
    Data::CrossSectionsXMLProperties::extractInfoFromAdjointElectroatomTableInfoParameterList(
                                                  cross_sections_xml_directory,
                                                  *adjoint_electroatom_name,
                                                  cross_section_table_info,
                                                  file_path,
                                                  file_type,
                                                  table_name,
                                                  file_start_line,
                                                  atomic_weight );

    if( file_type == Data::CrossSectionsXMLProperties::native_file )
    {
      this->createAdjointElectroatomFromNativeTable(
                                                cross_sections_xml_directory,
                                                *adjoint_electroatom_name,
                                                file_path,
                                                atomic_weight,
                                                properties );
    }
    else
    {
      THROW_EXCEPTION( std::logic_error,
                       "adjoint electroatomic file type "
                       << file_type << " is not supported!" );
    }

    ++adjoint_electroatom_name;
  }

  // Make sure that every adjoint electroatom has been created
  testPostcondition( d_adjoint_electroatom_name_map.size() ==
                     adjoint_electroatom_aliases.size() );

}

// Create the map of adjoint electroatoms
void AdjointElectroatomFactory::createAdjointElectroatomMap(
            std::unordered_map<std::string,std::shared_ptr<const AdjointElectroatom> >&
            adjoint_electroatom_map ) const
{
  // Reset the adjoint electroatom map
  adjoint_electroatom_map.clear();

  // Copy the stored map
  adjoint_electroatom_map.insert( d_adjoint_electroatom_name_map.begin(),
                                  d_adjoint_electroatom_name_map.end() );
}

// Create a adjoint electroatom from a Native table
void AdjointElectroatomFactory::createAdjointElectroatomFromNativeTable(
                        const std::string& cross_sections_xml_directory,
                        const std::string& adjoint_electroatom_alias,
                        const std::string& native_file_path,
                        const double atomic_weight,
                        const SimulationAdjointElectronProperties& properties )
{
  std::cout << "Loading native adjoint electroatomic cross section table "
            << adjoint_electroatom_alias << " ... " << std::flush;

  // Check if the table has already been loaded
  if( d_adjoint_electroatomic_table_name_map.find( native_file_path ) ==
      d_adjoint_electroatomic_table_name_map.end() )
  {
    // Create the native data container
    Data::AdjointElectronPhotonRelaxationDataContainer
      data_container( native_file_path );

    // Initialize the new adjoint electroatom
    std::shared_ptr<const AdjointElectroatom>& adjoint_electroatom =
      d_adjoint_electroatom_name_map[adjoint_electroatom_alias];

    // Create the new adjoint electroatom
    AdjointElectroatomNativeFactory::createAdjointElectroatom(
                                        data_container,
                                        native_file_path,
                                        atomic_weight,
                                        properties,
                                        adjoint_electroatom );

    // Cache the new adjoint electroatom in the table name map
    d_adjoint_electroatomic_table_name_map[native_file_path] =
                                                        adjoint_electroatom;
  }
  // The table has already been loaded
  else
  {
    d_adjoint_electroatom_name_map[adjoint_electroatom_alias] =
      d_adjoint_electroatomic_table_name_map[native_file_path];
  }

  *d_os_message << "done." << std::endl;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectroatomFactory.cpp
//---------------------------------------------------------------------------//
