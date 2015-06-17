//---------------------------------------------------------------------------//
//! 
//! \file   Geometry_ModuleInterface_Root.cpp
//! \author Eli Moll
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
  Root::gGeoManager;
  
boost::unordered_map<ModuleInterface<Root>::InternalCellHandle,
		     ModuleInterface<Root>::ExternalCellHandle> 
ModuleInterface<Root>::cell_handle_map;

// Do just in time initialization of interface members
static void initialize()
{ /* ... */ } // TODO

// Enable support for multiple threads
static void enableThreadSupport( const unsigned num_threads )
{ /* ... */ } // TODO

// Assign unique identities to all volumes in the geometry
inline void ModuleInterface<Root>::assignCellIds()
{
  Root::TObjArray volume_list = tgeomanager_instance->GetListOfVolumes();
  Root::TIterator volume_list_iterator = volume_list->MakeIterator();
  int number_volumes = volume_list->GetEntries();
  
  for (int i=0; i < number_volumes; i++) 
  {
    Root::TObject current_volume = volume_list_iterator->next();
    current_volume->SetUniqueID(i + 1) 
  }
}

// Compute and store all cell volumes
inline void ModuleInterface<Root>::StoreCellVolumes()
{
  volume_list = tgeomanager_instance->GetListOfVolumes();
  volume_list_iterator = volume_list->MakeIterator();
  number_volumes = volume_list->GetEntries();
  
  tvolumes.resize(number_volumes,double);
  
  for (int i=0; i < number_volumes; i++) 
  {
    current_volume = volume_list_iterator->next();
    tvolumes[i] = current_volume->SetUniqueID(i)
    
    // TODO - correct implementation of cell map
  }
}

// Find the cell that contains a given point (start of history)
static InternalCellHandle findCellContainingPoint( const Ray& ray )
{
  tgeomanager_instance->SetCurrentPosition( ray.getPosition() );
  tgeomanager_instance->SetCurrentDirection( ray.getDirection() );

  Root::TGeoNode current_node = tgeomanager_instance->GetCurrentNode();
  Root::TGeoVolume current_volume = current_node->GetVolume();
  int cell_external = current_volume->GetUniqueID();
  
  return ModuleInterface<Root>::getInternalCellHandle( cell_external );
}

// Find the cell that contains a given point (surface crossing)
static InternalCellHandle findCellContainingPoint( 
				 const Ray& ray,
				 const InternalCellHandle current_cell,
				 const InternalSurfaceHandle surface )
{
  // Find the new node occupied at the surface crossing
  Root::TGeoNode current_node = tgeomanager_instance->GetCurrentNode();
  Root::TGeoVolume current_volume = current_node->GetVolume();
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
      
    Root::TGeoVolume volume = tgeomanager_instance->GetVolume( cell_external );
    
    return volume->Contains(ray.getPosition());
}				    

} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_ModuleInterface_Root.cpp
//---------------------------------------------------------------------------//
