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
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

namespace MonteCarlo{

// // Constructor
// AdjointPhotoatomFactory::AdjointPhotoatomFactory(
//               const std::string& cross_sections_xml_directory,
//               const Teuchos::ParameterList& cross_section_table_info,
//               const std::unordered_set<std::string>& adjoint_photoatom_aliases,
//               const SimulationAdjointPhotonProperties& properties,
//               std::ostream* os_message )
//   : d_os_message( os_message )
// {
//   // Make sure the message output stream is valid
//   testPrecondition( os_message != NULL );

//   // Create each adjoint photoatom in the set
//   std::unordered_set<std::string>::const_iterator adjoint_photoatom_name =
//     adjoint_photoatom_aliases.begin();

//   std::string file_path, file_type, table_name;
//   int file_start_line;
//   double atomic_weight;

//   while( adjoint_photoatom_name != adjoint_photoatom_aliases.end() )
//   {
//     Data::CrossSectionsXMLProperties::extractInfoFromAdjointPhotoatomTableInfoParameterList(
//                                                   cross_sections_xml_directory,
//                                                   *adjoint_photoatom_name,
//                                                   cross_section_table_info,
//                                                   file_path,
//                                                   file_type,
//                                                   table_name,
//                                                   file_start_line,
//                                                   atomic_weight );

//     if( file_type == Data::CrossSectionsXMLProperties::native_file )
//     {
//       this->createAdjointPhotoatomFromNativeTable(cross_sections_xml_directory,
//                                                   *adjoint_photoatom_name,
//                                                   file_path,
//                                                   atomic_weight,
//                                                   properties );
//     }
//     else
//     {
//       THROW_EXCEPTION( std::logic_error,
//                        "adjoint photoatomic file type "
//                        << file_type << " is not supported!" );
//     }

//     ++adjoint_photoatom_name;
//   }

//   // Make sure that every adjoint photoatom has been created
//   testPostcondition( d_adjoint_photoatom_name_map.size() ==
//                      adjoint_photoatom_aliases.size() );
// }

// // Create the map of adjoint photoatoms
// void AdjointPhotoatomFactory::createAdjointPhotoatomMap(
//                std::unordered_map<std::string,std::shared_ptr<const AdjointPhotoatom> >&
//                adjoint_photoatom_map ) const
// {
//   // Reset the adjoint photoatom map
//   adjoint_photoatom_map.clear();

//   // Copy the stored map
//   adjoint_photoatom_map.insert( d_adjoint_photoatom_name_map.begin(),
//                                 d_adjoint_photoatom_name_map.end() );
// }

// // Create an adjoint photoatom from a Native table
// void AdjointPhotoatomFactory::createAdjointPhotoatomFromNativeTable(
//                           const std::string& cross_sections_xml_directory,
//                           const std::string& adjoint_photoatom_alias,
//                           const std::string& native_file_path,
//                           const double atomic_weight,
//                           const SimulationAdjointPhotonProperties& properties )
// {
//   *d_os_message << "Loading native adjoint photoatomic cross section table "
//                 << adjoint_photoatom_alias << " ... " << std::flush;

//   // Check if the table has already been loaded
//   if( d_adjoint_photoatomic_table_name_map.find( native_file_path ) ==
//       d_adjoint_photoatomic_table_name_map.end() )
//   {
//     // Create the aepr data container
//     Data::AdjointElectronPhotonRelaxationDataContainer
//       data_container( native_file_path );

//     // Initialize the new adjoint photoatom
//     std::shared_ptr<const AdjointPhotoatom>& adjoint_photoatom =
//       d_adjoint_photoatom_name_map[adjoint_photoatom_alias];

//     // Create the new adjoint photoatom
//     AdjointPhotoatomNativeFactory::createAdjointPhotoatom(
//                                         data_container,
//                                         native_file_path,
//                                         atomic_weight,
//                                         properties,
//                                         adjoint_photoatom );
    
//     // Cache the new adjoint photoatom in the table name map
//     d_adjoint_photoatomic_table_name_map[native_file_path] = adjoint_photoatom;
//   }
//   // The table has already been loaded
//   else
//   {
//     d_adjoint_photoatom_name_map[adjoint_photoatom_alias] =
//       d_adjoint_photoatomic_table_name_map[native_file_path];
//   }

//   *d_os_message << "done." << std::endl;
// }
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointPhotoatomFactory.cpp
//---------------------------------------------------------------------------//
