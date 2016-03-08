//---------------------------------------------------------------------------//
//!
//! \file   Geometry_Root.cpp
//! \author Alex Robinson, Eli Moll
//! \brief  Root singleton wrapper class
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <exception>
#include <unordered_set>

// Root Includes
#include <TError.h>

// FRENSIE Includes
#include "Geometry_Root.hpp"
#include "Geometry_ModuleTraits.hpp"
#include "Utility_ContractException.hpp"

namespace Geometry{

// Initialize static member data
TGeoManager* Root::s_manager = NULL;
std::string Root::s_terminal_material_name = "graveyard";
std::string Root::s_void_material_name = "void";

// Set the void material property name
void Root::setVoidMaterialName( const std::string& void_material_name )
{
  // Make sure the void material name is valid
  testPrecondition( void_material_name.size() > 0 );
  
  s_void_material_name = void_material_name;
}

// Set the terminal material property name
void Root::setTerminalMaterialName( const std::string& terminal_material_name )
{
  // Make sure the terminal property name is valid
  testPrecondition( terminal_material_name.size() > 0 );
  
  s_terminal_material_name = terminal_material_name;
}

// Initialize the root geometry manager
/*! \details Some basic verification of the geometry will be done
 * during initialization. Each cell will be checked for a non-zero id that
 * is not repeated by any other cell (unique id).
 */
void Root::initialize( const std::string& filename )
{
  // Tell ROOT to suppress all non-fatal messages
  gErrorIgnoreLevel = kFatal;

  s_manager = TGeoManager::Import( filename.c_str() );
  
  // Get the list of volumes
  TObjArray* volume_list = Geometry::Root::getManager()->GetListOfVolumes();
  TIterator* volume_list_iterator = volume_list->MakeIterator();
  int number_volumes = volume_list->GetEntries();

  std::unordered_set<unsigned long long> cell_ids;
  
  // Make sure that the cell ids are unique or estimators cannot be assigned
  for( unsigned i = 0; i < number_volumes; ++i ) 
  {
    TObject* current_object = volume_list_iterator->Next();
    TGeoVolume* current_volume = dynamic_cast<TGeoVolume*>( current_object );
    
    TEST_FOR_EXCEPTION( current_volume->GetUniqueID() == 0,
                        std::runtime_error,
                        "Error: ROOT contains a cell which has not been "
                        "assigned a unique cell ID in the input file!" );

    TEST_FOR_EXCEPTION( current_volume->GetUniqueID() ==
                        ModuleTraits::invalid_internal_cell_handle,
                        std::runtime_error,
                        "Error: ROOT contains a cell that has a reserved id ("
                        << ModuleTraits::invalid_internal_cell_handle <<
                        ") in the input file!" );

    TEST_FOR_EXCEPTION( cell_ids.find( current_volume->GetUniqueID() ) !=
                        cell_ids.end(),
                        std::runtime_error,
                        "Error: ROOT contains cells with the same id ("
                        << current_volume->GetUniqueID() <<
                        ") in the input file!" );

    cell_ids.insert( current_volume->GetUniqueID() );
  } 
}

} // end Geoemtry namespace

//---------------------------------------------------------------------------//
// end Geometry_Root.cpp
//---------------------------------------------------------------------------//
