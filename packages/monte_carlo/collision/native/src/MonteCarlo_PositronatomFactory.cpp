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
#include "Data_CrossSectionsXMLProperties.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

namespace MonteCarlo{

// Constructor
PositronatomFactory::PositronatomFactory(
    const std::string& cross_sections_xml_directory,
    const Teuchos::ParameterList& cross_section_table_info,
    const std::unordered_set<std::string>& positronatom_aliases,
    const Teuchos::RCP<AtomicRelaxationModelFactory>&
    atomic_relaxation_model_factory,
    const SimulationProperties& properties,
    std::ostream* os_message )
  :d_os_message( os_message )
{
  // Make sure the message stream is valid
  testPrecondition( os_message != NULL );

  // Create each positron-atom in the set
  std::unordered_set<std::string>::const_iterator positronatom_name =
    positronatom_aliases.begin();

  std::string positronatom_file_path, positronatom_file_type, positronatom_table_name;
  int positronatom_file_start_line;
  double atomic_weight;

  while( positronatom_name != positronatom_aliases.end() )
  {
    Data::CrossSectionsXMLProperties::extractInfoFromElectroatomTableInfoParameterList(
                          cross_sections_xml_directory,
                          *positronatom_name,
                          cross_section_table_info,
                          positronatom_file_path,
                          positronatom_file_type,
                          positronatom_table_name,
                          positronatom_file_start_line,
                          atomic_weight );

    if( positronatom_file_type == Data::CrossSectionsXMLProperties::ace_file )
    {
      this->createPositronatomFromACETable( *positronatom_name,
                                           positronatom_file_path,
                                           positronatom_table_name,
                                           positronatom_file_start_line,
                                           atomic_weight,
                                           atomic_relaxation_model_factory,
                                           properties );
    }
    else if( positronatom_file_type == Data::CrossSectionsXMLProperties::native_file )
    {
      this->createPositronatomFromNativeTable( *positronatom_name,
                                              positronatom_file_path,
                                              atomic_weight,
                                              atomic_relaxation_model_factory,
                                              properties );
    }
    else
    {
      THROW_EXCEPTION( std::logic_error,
               "Error: positron-atomic file type "
               << positronatom_file_type <<
               " is not supported!" );
    }

    ++positronatom_name;
  }

  // Make sure that every positron-atom has been created
  testPostcondition( d_positronatom_name_map.size() == positronatom_aliases.size() );

}

// Create the map of positron-atoms
void PositronatomFactory::createPositronatomMap(
            std::unordered_map<std::string,Teuchos::RCP<Positronatom> >&
            positronatom_map ) const
{
  // Reset the positron-atom map
  positronatom_map.clear();

  // Copy the stored map
  positronatom_map.insert( d_positronatom_name_map.begin(),
                          d_positronatom_name_map.end() );
}

// Create a positron-atom from an ACE table
void PositronatomFactory::createPositronatomFromACETable(
                              const std::string& positronatom_alias,
                              const std::string& ace_file_path,
                              const std::string& positronatomic_table_name,
                              const int positronatomic_file_start_line,
                              const double atomic_weight,
                              const Teuchos::RCP<AtomicRelaxationModelFactory>&
                              atomic_relaxation_model_factory,
                              const SimulationProperties& properties )
{
  *d_os_message << "Loading ACE positron-atomic cross section table "
        << positronatomic_table_name << " (" << positronatom_alias << ") ... ";


  // Check if the table has already been loaded
  if( d_positronatomic_table_name_map.find( positronatomic_table_name ) ==
      d_positronatomic_table_name_map.end() )
  {
    // Create the ACEFileHandler
    Data::ACEFileHandler ace_file_handler( ace_file_path,
                       positronatomic_table_name,
                       positronatomic_file_start_line,
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
                             properties.getMinPhotonEnergy(),
                             properties.getMinElectronEnergy(),
                             properties.isAtomicRelaxationModeOn( ELECTRON ) );

    // Initialize the new positron-atom
    Teuchos::RCP<Positronatom>& positronatom =
      d_positronatom_name_map[positronatom_alias];

    // Create the new positron-atom
    PositronatomACEFactory::createPositronatom( xss_data_extractor,
                                              positronatomic_table_name,
                                              atomic_weight,
                                              atomic_relaxation_model,
                                              properties,
                                              positronatom );

    // Cache the new positron-atom in the table name map
    d_positronatomic_table_name_map[positronatomic_table_name] = positronatom;
  }
  // The table has already been loaded
  else
  {
    d_positronatom_name_map[positronatom_alias] =
      d_positronatomic_table_name_map[positronatomic_table_name];
  }

  *d_os_message << "done." << std::endl;
}


// Create a positron-atom from a Native table
void PositronatomFactory::createPositronatomFromNativeTable(
                              const std::string& positronatom_alias,
                              const std::string& native_file_path,
                              const double atomic_weight,
                              const Teuchos::RCP<AtomicRelaxationModelFactory>&
                              atomic_relaxation_model_factory,
                              const SimulationProperties& properties )
{
  std::cout << "Loading native positron-atomic cross section table "
            << positronatom_alias << " ... ";

  // Check if the table has already been loaded
  if( d_positronatomic_table_name_map.find( native_file_path ) ==
      d_positronatomic_table_name_map.end() )
  {
    // Create the eedl data container
    Data::ElectronPhotonRelaxationDataContainer
      data_container( native_file_path );

    // Create the atomic relaxation model
    Teuchos::RCP<AtomicRelaxationModel> atomic_relaxation_model;

    atomic_relaxation_model_factory->createAndCacheAtomicRelaxationModel(
                             data_container,
                             atomic_relaxation_model,
                             properties.getMinPhotonEnergy(),
                             properties.getMinElectronEnergy(),
                             properties.isAtomicRelaxationModeOn( ELECTRON ) );

    // Initialize the new positron-atom
    Teuchos::RCP<Positronatom>& positronatom =
      d_positronatom_name_map[positronatom_alias];

    // Create the new positron-atom
    PositronatomNativeFactory::createPositronatom( data_container,
                                                 native_file_path,
                                                 atomic_weight,
                                                 atomic_relaxation_model,
                                                 properties,
                                                 positronatom );

    // Cache the new positron-atom in the table name map
    d_positronatomic_table_name_map[native_file_path] = positronatom;
  }
  // The table has already been loaded
  else
  {
    d_positronatom_name_map[positronatom_alias] =
      d_positronatomic_table_name_map[native_file_path];
  }

  std::cout << "done." << std::endl;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PositronatomFactory.cpp
//---------------------------------------------------------------------------//
