//---------------------------------------------------------------------------//
//!
//! \file   Geometry_Root.cpp
//! \author Alex Robinson, Eli Moll
//! \brief  Root singleton wrapper class
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <exception>

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

// Initialize the root geometry manager
void Root::initialize( const std::string& filename )
{
  // Tell ROOT to suppress all non-fatal messages
  gErrorIgnoreLevel = kFatal;

  s_manager = TGeoManager::Import( filename.c_str() );
  
  // Get the list of volumes
  TObjArray* volume_list = Geometry::Root::getManager()->GetListOfVolumes();
  TIterator* volume_list_iterator = volume_list->MakeIterator();
  int number_volumes = volume_list->GetEntries();
  
  // Make sure that the cell ids are unique or estimators cannot be assigned
  for( unsigned i = 0; i < number_volumes; ++i ) 
  {
    TObject* current_object = volume_list_iterator->Next();
    TGeoVolume* current_volume = dynamic_cast<TGeoVolume*>( current_object );
    
    TEST_FOR_EXCEPTION( current_volume->GetUniqueID() == 0,
                        std::runtime_error,
                        "Error: Root contains a cell which has not been "
                        "assigned a unique cell ID in the input file!" );

    TEST_FOR_EXCEPTION( current_volume->GetUniqueID() ==
                        ModuleTraits::invalid_internal_cell_handle,
                        std::runtime_error,
                        "Error: Root contains a cell that has a reserved id ("
                        << ModuleTraits::invalid_internal_cell_handle <<
                        ") in the input file!" );
  } 
}

} // end Geoemtry namespace

//---------------------------------------------------------------------------//
// end Geometry_Root.cpp
//---------------------------------------------------------------------------//
