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
void ModuleInterface<Root>::initialize()
{ 
  #pragma omp master
  {
    ModuleInterface<Root>::assignCellIds();
  }
  #pragma omp barrier
}

// Enable support for multiple threads
void ModuleInterface<Root>::enableThreadSupport( const unsigned num_threads )
{  
  THROW_EXCEPTION( std::logic_error,
                   "Error: The Root module interface does not support "
                   "multiple threads yet!");
}

// Assign unique identities to all volumes in the geometry
void ModuleInterface<Root>::assignCellIds()
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

// Find the cell that contains a given point (start of history)
ModuleInterface<Root>::InternalCellHandle ModuleInterface<Root>::findCellContainingPoint( const Ray& ray )
{
  // Get current position and direction from ray
  const double* position  = ray.getPosition();
  const double* direction = ray.getDirection();

  // Assign position and direction to ROOT Double_t arrays
  Double_t point[3];
  point[0] = position[0];  
  point[1] = position[1];  
  point[2] = position[2]; 

  Double_t dir[3];
  dir[0] = direction[0];
  dir[1] = direction[1];
  dir[2] = direction[2];

  Root::getManager()->SetCurrentPoint( point );
  Root::getManager()->SetCurrentDirection( dir );

  TGeoNode* current_node = Root::getManager()->GetCurrentNode();
  TGeoVolume* current_volume = current_node->GetVolume();
  int cell_external = current_volume->GetUniqueID();
  
  return ModuleInterface<Root>::getInternalCellHandle( cell_external );
}

// Find the cell that contains a given point (surface crossing)
ModuleInterface<Root>::InternalCellHandle ModuleInterface<Root>::findCellContainingPoint( 
				 const Ray& ray,
				 const ModuleInterface<Root>::InternalCellHandle current_cell,
				 const ModuleInterface<Root>::InternalSurfaceHandle surface )
{
  return ModuleInterface<Root>::findCellContainingPoint( ray );
}	
	
// Fire a ray through the geometry
void ModuleInterface<Root>::fireRay( const Ray& ray,
	       const ModuleInterface<Root>::InternalCellHandle& current_cell,
	       ModuleInterface<Root>::InternalSurfaceHandle& surface_hit,
	       double& distance_to_surface_hit )
{
  // Get current position and direction from ray
  const double* position  = ray.getPosition();
  const double* direction = ray.getDirection();

  // Assign position and direction to ROOT Double_t arrays
  Double_t point[3];
  point[0] = position[0];  
  point[1] = position[1];  
  point[2] = position[2]; 

  Double_t dir[3];
  dir[0] = direction[0];
  dir[1] = direction[1];
  dir[2] = direction[2];

  Root::getManager()->SetCurrentPoint( point );
  Root::getManager()->SetCurrentDirection( dir );
  
  Root::getManager()->FindNextBoundaryAndStep();
  Root::getManager()->FindNextBoundary();
  
  distance_to_surface_hit = 
      Root::getManager()->GetStep();
      
  Root::getManager()->Step( distance_to_surface_hit );
}	       

// Get the point location w.r.t. a given cell
PointLocation ModuleInterface<Root>::getPointLocation( const Ray& ray,
				 const ModuleInterface<Root>::InternalCellHandle cell )
{
  ModuleInterface<Root>::ExternalCellHandle cell_external = 
                 ModuleInterface<Root>::getExternalCellHandle( cell );
      
  TGeoVolume* volume = Root::getManager()->GetVolume( cell_external );
    
  // Get current position and direction from ray
  const double* position  = ray.getPosition();

  // Assign position and direction to ROOT Double_t arrays
  Double_t point[3];
  point[0] = position[0];  
  point[1] = position[1];  
  point[2] = position[2]; 

  bool contain = volume->Contains( point );
  if ( contain && Root::getManager()->IsOnBoundary() )
    return POINT_ON_CELL;
  else if ( contain && !Root::getManager()->IsOnBoundary() )
    return POINT_INSIDE_CELL;
  else
    return POINT_OUTSIDE_CELL;
}				    

} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_ModuleInterface_Root.cpp
//---------------------------------------------------------------------------//
