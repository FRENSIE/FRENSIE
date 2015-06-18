//---------------------------------------------------------------------------//
//! 
//! \file   Geometry_ModuleInterface_Root.cpp
//! \author Alex Robinson, Eli Moll
//! \brief  Root Specialization decl. of the geometry ModuleInterface class
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Geometry_ModuleInterface_Root.hpp"

namespace Geometry{

// Initialize the Root geometry module interface static member data
const ModuleInterface<Root>::ExternalSurfaceHandle
ModuleInterface<Root>::invalid_external_surface_handle = 0;

const ModuleInterface<Root>::ExternalCellHandle
ModuleInterface<Root>::invalid_external_cell_handle = 0;

Root::TGeoManager* const ModuleInterface<Root>::tgeomanager_instance =
  Root::getManager();
  
boost::unordered_map<ModuleInterface<Root>::InternalCellHandle,
		     ModuleInterface<Root>::ExternalCellHandle> 
ModuleInterface<Root>::cell_handle_map;

// Do just in time initialization of interface members
static void initialize()
{ 
  #pragma omp master
  {
    // TODO
  }
  #pragma omp barrier
}

// Enable support for multiple threads
static void enableThreadSupport( const unsigned num_threads )
{ /* ... */ } // TODO

// Assign unique identities to all volumes in the geometry
inline void ModuleInterface<Root>::assignCellIds()
{
  TObjArray* volume_list = tgeomanager_instance->GetListOfVolumes();
  TIterator* volume_list_iterator = volume_list->MakeIterator();
  int number_volumes = volume_list->GetEntries();
  
  for (int i=0; i < number_volumes; i++) 
  {
    TObject* current_volume = volume_list_iterator->next();
    current_volume->SetUniqueID(i + 1) 
  }
}

// Compute and map all cell volumes
inline void ModuleInterface<Root>::storeCellVolumes()
{
  TObjArray* volume_list = tgeomanager_instance->GetListOfVolumes();
  TIterator* volume_list_iterator = volume_list->MakeIterator();
  int number_volumes = volume_list->GetEntries();
  
  tvolumes.resize(number_volumes,double);
  
  for (int i=0; i < number_volumes; i++) 
  {
    TObject* current_volume = volume_list_iterator->next();
    tvolumes[i] = current_volume->Capacity();
    
    // TODO - correct implementation of cell map
  }
}

// Find the cell that contains a given point (start of history)
static InternalCellHandle findCellContainingPoint( const Ray& ray )
{
  tgeomanager_instance->SetCurrentPosition( ray.getPosition() );
  tgeomanager_instance->SetCurrentDirection( ray.getDirection() );

  TGeoNode* current_node = tgeomanager_instance->GetCurrentNode();
  TGeoVolume* current_volume = current_node->GetVolume();
  int cell_external = current_volume->GetUniqueID();
  
  return ModuleInterface<Root>::getInternalCellHandle( cell_external );
}

// Find the cell that contains a given point (surface crossing)
static InternalCellHandle findCellContainingPoint( 
				 const Ray& ray,
				 const InternalCellHandle current_cell,
				 const InternalSurfaceHandle surface )
{
  // Find the new node occupied after surface crossing
  TGeoNode* current_node = tgeomanager_instance->GetCurrentNode();
  TGeoVolume* current_volume = current_node->GetVolume();
  int cell_external = current_volume->GetUniqueID();
  
  return ModuleInterface<Root>::getInternalCellHandle( cell_external );
}	
	
// Fire a ray through the geometry
static void fireRay( const Ray& ray,
	       const InternalCellHandle& current_cell,
	       InternalSurfaceHandle& surface_hit,
	       double& distance_to_surface_hit )
{
  tgeomanager_instance->SetCurrentPosition( ray.getPosition() );
  tgeomanager_instance->SetCurrentDirection( ray.getDirection() );
  
  tgeomanager_instance->FindNextBoundaryAndStep();
  
  distance_to_surface_hit = 
      tgeomanager_instance->GetCurrentNavigator()->GetStep();
}	       

// Get the point location w.r.t. a given cell
static PointLocation getPointLocation( const Ray& ray,
				 const InternalCellHandle cell )
{
    ExternalCellHandle cell_external = 
      ModuleInterface<Root>::getExternalCellHandle( cell );
      
    TGeoVolume* volume = tgeomanager_instance->GetVolume( cell_external );
    
    return volume->Contains(ray.getPosition());
}				    

} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_ModuleInterface_Root.cpp
//---------------------------------------------------------------------------//
