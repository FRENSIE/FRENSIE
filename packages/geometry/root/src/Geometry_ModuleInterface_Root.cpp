//---------------------------------------------------------------------------//
//! 
//! \file   Geometry_ModuleInterface_Root.cpp
//! \author Alex Robinson, Eli Moll
//! \brief  Root Specialization decl. of the geometry ModuleInterface class
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/unordered_set.hpp>

// FRENSIE Includes
#include "Geometry_ModuleInterface_Root.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Geometry{

// Initialize the Root geometry module interface static member data
const ModuleInterface<Root>::ExternalSurfaceHandle
ModuleInterface<Root>::invalid_external_surface_handle = 0;

const ModuleInterface<Root>::ExternalCellHandle
ModuleInterface<Root>::invalid_external_cell_handle = 0;

boost::unordered_map<ModuleInterface<Root>::ExternalCellHandle, Int_t> 
                ModuleInterface<Root>::s_root_uniqueid_to_uid_map;

// Do just in time initialization of interface members
void ModuleInterface<Root>::initialize()
{ 
  ModuleInterface<Root>::assignCellIds();
}

// Enable support for multiple threads
void ModuleInterface<Root>::enableThreadSupport( const unsigned num_threads )
{ 
  if( num_threads > 1 )
  {
    THROW_EXCEPTION( std::logic_error,
                     "Error: The Root module interface does not support "
                     "multiple threads yet!");
  }
}

// Assign unique identities to all volumes in the geometry
void ModuleInterface<Root>::assignCellIds()
{
  TObjArray* volume_list = Root::getManager()->GetListOfVolumes();
  TIterator* volume_list_iterator = volume_list->MakeIterator();
  int number_volumes = volume_list->GetEntries();
  
  boost::unordered_set<Int_t> cell_ids;
  
  for ( int i=0; i < number_volumes; i++ ) 
  {
    TObject* current_object = volume_list_iterator->Next();
    TGeoVolume* current_volume = dynamic_cast<TGeoVolume*>( current_object );
    if ( current_volume->GetUniqueID() == 0 )
    {
      THROW_EXCEPTION( std::runtime_error,
                       "Error: Root contains a cell which has been"
                       " assigned the restricted id 0." );
    }
    else if ( cell_ids.find( current_volume->GetUniqueID() ) != cell_ids.end() )
    {
      std::string other_volume_name = Root::getManager()->GetVolume( s_root_uniqueid_to_uid_map.find( current_volume->GetUniqueID() )->second )->GetName();
      THROW_EXCEPTION( std::runtime_error,
                       "Error: Root has found the following cells which have"
                       " been assigned the cell id " << 
                       current_volume->GetUniqueID() << ": " << 
                       current_volume->GetName() << ", " << 
                       other_volume_name );
    }
    else
    {
      cell_ids.insert( current_volume->GetUniqueID() );
    }
    s_root_uniqueid_to_uid_map[ current_volume->GetUniqueID() ] = 
                      Root::getManager()->GetUID( current_volume->GetName() ); 
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

  TGeoNode* current_node = Root::getManager()->InitTrack( 
                                point[0], point[1], point[2],
                                direction[0], direction[1], direction[2] );
  
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
  int cell_external = 
               Root::getManager()->GetCurrentNode()->GetVolume()->GetUniqueID();
               
  return ModuleInterface<Root>::getInternalCellHandle( cell_external );
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

  Root::getManager()->InitTrack( point[0], point[1], point[2],
                                direction[0], direction[1], direction[2] );
  
  TGeoNode* surface_node = Root::getManager()->FindNextBoundaryAndStep();

  distance_to_surface_hit = 
      Root::getManager()->GetStep();
      
  int surface_hit_external = surface_node->GetVolume()->GetUniqueID();
                                      
  surface_hit = ModuleInterface<Root>::getInternalCellHandle(
                                                        surface_hit_external );
}	       

// Get the point location w.r.t. a given cell
PointLocation ModuleInterface<Root>::getPointLocation( const Ray& ray,
				 const ModuleInterface<Root>::InternalCellHandle cell )
{
  ModuleInterface<Root>::ExternalCellHandle cell_external = 
                 ModuleInterface<Root>::getExternalCellHandle( cell );
  
  TGeoVolume* volume = Root::getManager()->GetVolume( s_root_uniqueid_to_uid_map.find( cell_external )->second );
    
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
