//---------------------------------------------------------------------------//
//! 
//! \file   Geometry_ModuleInterface_Root.cpp
//! \author Alex Robinson, Eli Moll
//! \brief  Root Specialization decl. of the geometry ModuleInterface class
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Geometry_ModuleInterface_Root.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Geometry{

// Initialize the Root geometry module interface static member data
const ModuleInterface<Root>::ExternalSurfaceHandle
ModuleInterface<Root>::invalid_external_surface_handle = 0;

const ModuleInterface<Root>::ExternalCellHandle
ModuleInterface<Root>::invalid_external_cell_handle = 0;

// Do just in time initialization of interface members
static void initialize()
{ 
  #pragma omp master
  {
    ModuleInterface<Root>::assignCellIds();
  }
  #pragma omp barrier
}

// Enable support for multiple threads
static void enableThreadSupport( const unsigned num_threads )
{  
  THROW_EXCEPTION( std::logic_error,
                   "Error: The Root module interface does not support "
                   "multiple threads yet!");
}

// Assign unique identities to all volumes in the geometry
inline void ModuleInterface<Root>::assignCellIds()
{
  TObjArray* volume_list = Root::getManager()->GetListOfVolumes();
  TIterator* volume_list_iterator = volume_list->MakeIterator();
  int number_volumes = volume_list->GetEntries();
  
  for (int i=0; i < number_volumes; i++) 
  {
    TObject* current_volume = volume_list_iterator->Next();
    current_volume->SetUniqueID(i + 1); 
  }
}

// Compute and map all cell volumes
inline void ModuleInterface<Root>::storeCellVolumes()
{
  TObjArray* volume_list = Root::getManager()->GetListOfVolumes();
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
  Root::getManager()->SetCurrentPosition( ray.getPosition() );
  Root::getManager()->SetCurrentDirection( ray.getDirection() );

  TGeoNode* current_node = Root::getManager()->GetCurrentNode();
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
  TGeoNode* current_node = Root::getManager()->GetCurrentNode();
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
  Root::getManager()->SetCurrentPosition( ray.getPosition() );
  Root::getManager()->SetCurrentDirection( ray.getDirection() );
  
  Root::getManager()->FindNextBoundaryAndStep();
  
  distance_to_surface_hit = 
      Root::getManager()->GetCurrentNavigator()->GetStep();
}	       

// Get the point location w.r.t. a given cell
static PointLocation getPointLocation( const Ray& ray,
				 const InternalCellHandle cell )
{
    ExternalCellHandle cell_external = 
      ModuleInterface<Root>::getExternalCellHandle( cell );
      
    TGeoVolume* volume = Root::getManager()->GetVolume( cell_external );
    
    return volume->Contains(ray.getPosition());
}				    

} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_ModuleInterface_Root.cpp
//---------------------------------------------------------------------------//
