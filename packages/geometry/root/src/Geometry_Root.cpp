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
#include "Utility_DirectionHelpers.hpp"
#include "Utility_GlobalOpenMPSession.hpp"

namespace Geometry{

// Initialize static member data
TGeoManager* Root::s_manager = NULL;
std::unordered_map<ModuleTraits::InternalCellHandle,Int_t> Root::s_cell_id_uid_map;
std::vector<int> Root::s_internal_ray_set;
std::string Root::s_terminal_material_name = "graveyard";
std::string Root::s_void_material_name = "void";
std::string Root::s_material_property_name = "mat";

// Set the material property name
void Root::setMaterialPropertyName( const std::string& material_property_name )
{
  // Make sure Root has not been initialized
  testPrecondition( !Root::isInitialized() );
  
  testPrecondition( material_property_name.size() > 0 );
  
  s_material_property_name = material_property_name;
}

// Set the void material property name
void Root::setVoidMaterialName( const std::string& void_material_name )
{
  // Make sure Root has not been initialized
  testPrecondition( !Root::isInitialized() );
  // Make sure the void material name is valid
  testPrecondition( void_material_name.size() > 0 );
  
  s_void_material_name = void_material_name;
}

// Set the terminal material property name
void Root::setTerminalMaterialName( const std::string& terminal_material_name )
{
  // Make sure Root has not been initialized
  testPrecondition( !Root::isInitialized() );
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
  // Make sure to initialize only once
  testPrecondition( !Root::isInitialized() );

  // Initialize the internal ray set array
  s_internal_ray_set.resize( 1, false );
  
  // Tell ROOT to suppress all non-fatal messages
  gErrorIgnoreLevel = kFatal;

  s_manager = TGeoManager::Import( filename.c_str() );

  // Make sure the import was successful
  TEST_FOR_EXCEPTION( s_manager == NULL,
                      InvalidRootGeometry,
                      "Error: ROOT could not import file "
                      << filename << "!" );

  // Lock the geometry so no other geometries can be imported
  TGeoManager::LockGeometry();
  
  // Get the list of volumes
  TObjArray* volume_list = s_manager->GetListOfVolumes();
  TIterator* volume_it = volume_list->MakeIterator();
  unsigned long long number_volumes = volume_list->GetEntries();

  unsigned num_termination_cells = 0u;

  // Set up the cell id to UID map and make sure that the cell ids are unique 
  for( unsigned long long i = 0; i < number_volumes; ++i ) 
  {
    TObject* object = volume_it->Next();
    TGeoVolume* cell = dynamic_cast<TGeoVolume*>( object );
    
    TEST_FOR_EXCEPTION( cell->GetUniqueID() == 0,
                        InvalidRootGeometry,
                        "Error: ROOT contains a cell which has not been "
                        "assigned an id in the input file!" );

    TEST_FOR_EXCEPTION( cell->GetUniqueID() ==
                        ModuleTraits::invalid_internal_cell_handle,
                        InvalidRootGeometry,
                        "Error: ROOT contains a cell that has a reserved id ("
                        << ModuleTraits::invalid_internal_cell_handle <<
                        ") in the input file!" );

    TEST_FOR_EXCEPTION( s_cell_id_uid_map.find( cell->GetUniqueID() ) != 
                        s_cell_id_uid_map.end(),
                        InvalidRootGeometry,
                        "Error: ROOT contains cells with the same id ("
                        << cell->GetUniqueID() << ") in the input file!" );

    s_cell_id_uid_map[cell->GetUniqueID()] = 
      s_manager->GetUID( cell->GetName() );

    if( Root::isTerminationCell( cell->GetUniqueID() ) )
      ++num_termination_cells;
  } 

  // Make sure at least one termination cell is present
  TEST_FOR_EXCEPTION( num_termination_cells == 0,
                      InvalidRootGeometry,
                      "Error: ROOT contains no cells with the terminal "
                      "material!" );
}

// Enable thread support
void Root::enableThreadSupport( const unsigned num_threads )
{
  // Make sure root has been initialized
  testPrecondition( Root::isInitialized() );
  // Make sure the number of threads is valid
  testPrecondition( num_threads > 0 );

  s_manager->SetMaxThreads( num_threads );
  
  // A navigator must be created for each thread
  // NOTE: this is not done by the SetMaxThreads method (why????)
  #pragma omp parallel num_threads( num_threads )
  {
    // This navigator will also be set to the current navigator for the thread
    TGeoNavigator* thread_navigator = s_manager->AddNavigator();
  }

  // The internal ray for each thread must be monitored
  s_internal_ray_set.resize( num_threads, false );
}

// Check if a cell exists
/*! \details This method is thread safe.
 */
bool Root::doesCellExist( const ModuleTraits::InternalCellHandle cell_id )
{
  // Make sure root has been initialized
  testPrecondition( Root::isInitialized() );
  
  return s_cell_id_uid_map.find( cell_id ) !=
    s_cell_id_uid_map.end();
}

// Get the cell volume
/*! \details This method is thread safe as long as enableThreadSupport has
 * been called.
 * \warning This will only return the cell volume when the daughters are
 * completely contained in the cell of interest (no overlaps)
 */
double Root::getCellVolume( const ModuleTraits::InternalCellHandle cell_id )
{
  // Make sure root has been initialized
  testPrecondition( Root::isInitialized() );
  // Make sure the cell exists
  testPrecondition( Root::doesCellExist( cell_id ) );
  
  // Get the volume of the cell
  double volume = Root::getVolumePtr( cell_id )->Capacity();

  // Subtract of the daughter cell volumes
  TObjArray* daughters = Root::getVolumePtr( cell_id )->GetNodes();

  if( daughters != NULL )
  {
    TIterator* daughter_it = daughters->MakeIterator();
    unsigned long long number_of_daughters = daughters->GetEntries();

    for( unsigned long long i = 0; i < number_of_daughters; ++i )
    {
      // Obtain the next object in the array and cast it to its derived class
      TObject* daughter_object = daughter_it->Next();
      TGeoNode* daughter_node = dynamic_cast<TGeoNode*>( daughter_object );
      
      TGeoVolume* daughter_volume = daughter_node->GetVolume();

      // Subtract the daughter volume
      volume -= daughter_volume->Capacity();
    }
  }

  // Make sure the calculated volume is valid
  TEST_FOR_EXCEPTION( volume <= 0.0,
                      std::logic_error,
                      "Error: an invalid volume was calculated for cell "
                      << cell_id << " (" << volume << ")!" );

  return volume;
}

// Check if the cell is a termination cell
/*! \details This method is thread safe as long as enableThreadSupport has
 * been called.
 */
bool Root::isTerminationCell( const ModuleTraits::InternalCellHandle cell_id)
{
  // Make sure root has been initialized
  testPrecondition( Root::isInitialized() );
  // Make sure the cell exists
  testPrecondition( Root::doesCellExist( cell_id ) );

  TGeoVolume* cell_volume = Root::getVolumePtr( cell_id );

  return cell_volume->GetMaterial()->GetName() ==
    Root::getTerminalMaterialName();
}

// Check if the cell is a void cell
bool Root::isVoidCell( const ModuleTraits::InternalCellHandle cell_id )
{
  // Make sure root has been initialized
  testPrecondition( Root::isInitialized() );
  // Make sure the cell exists
  testPrecondition( Root::doesCellExist( cell_id ) );

  TGeoVolume* cell_volume = Root::getVolumePtr( cell_id );

  return cell_volume->GetMaterial()->GetName() ==
    Root::getVoidMaterialName();
}

// Get the point location w.r.t. a given cell
/*! \details This method is thread safe as long as enableThreadSupport has
 * been called.
 */
PointLocation Root::getPointLocation( 
                              const Ray& ray,
                              const ModuleTraits::InternalCellHandle cell_id )
{
  return Root::getPointLocation( ray.getPosition(), cell_id );
}

// Get the point location w.r.t. a given cell
/*! \details Root only allows one to test if a point is inside or outside
 * a cell (not on a cell). If the point is on a cell Root will return
 * inside (unless one of the boundary cells is a daughter node of the
 * cell or interest). This method is thread safe as long as enableThreadSupport
 * has been called.
 */
PointLocation Root::getPointLocation( 
                               const double position[3],
                               const ModuleTraits::InternalCellHandle cell_id )
{
  // Make sure root has been initialized
  testPrecondition( Root::isInitialized() );
  // Make sure the cell exists
  testPrecondition( Root::doesCellExist( cell_id ) );
  
  TGeoVolume* cell = Root::getVolumePtr( cell_id );

  PointLocation location;

  if( cell->Contains( position ) )
  {
    location = POINT_INSIDE_CELL;
    
    // Check if the point is an any daughters
    TObjArray* daughters = Root::getVolumePtr( cell_id )->GetNodes();

    if( daughters != NULL )
    {
      TIterator* daughter_it = daughters->MakeIterator();
      unsigned long long number_of_daughters = daughters->GetEntries();

      for( unsigned long long i = 0; i < number_of_daughters; ++i )
      {
        // Obtain the next object in the array and cast it to its derived class
        TObject* daughter_object = daughter_it->Next();
        TGeoNode* daughter_node = dynamic_cast<TGeoNode*>( daughter_object );
      
        TGeoVolume* daughter_volume = daughter_node->GetVolume();
        
        if( daughter_volume->Contains( position ) )
        {
          location = POINT_OUTSIDE_CELL;
          
          break;
        }
      }
    }
  }
  else
    location = POINT_OUTSIDE_CELL;

  return location;
}

// Find the node containing the point
// Note: This will update the internal state of Root. This method is thread 
// safe as long as enableThreadSupport has been called.
TGeoNode* Root::findNodeContainingPoint( const Ray& ray )
{
  // Make sure root has been initialized
  testPrecondition( Root::isInitialized() );

  // The internal ray is not set now
  Root::internalRayUnset();

  TGeoNode* current_node = s_manager->InitTrack( ray.getPosition(),
                                                 ray.getDirection() );

  TGeoNode* boundary_node = s_manager->FindNextBoundary();

  double distance_to_boundary = s_manager->GetStep();

  TGeoNode* node_containing_point;
  
  // If the point is within the boundary tolerance return the next node
  if( distance_to_boundary < 1e-5 )
    node_containing_point = s_manager->Step();
  else
    node_containing_point = current_node;

  // Make sure the node is valid
  testPostcondition( node_containing_point != NULL );

  return node_containing_point;
}

// Find the cell that contains the external ray
/*! \details This method is thread safe as long as enableThreadSupport has
 * been called. 
 * \warning This method will reset the internal ray.
 */
ModuleTraits::InternalCellHandle 
Root::findCellContainingExternalRay( const Ray& ray )
{
  // Make sure root has been initialized
  testPrecondition( Root::isInitialized() );

  return Root::findNodeContainingPoint( ray )->GetVolume()->GetUniqueID();
}

// Fire an external ray through the geometry
/*! \details The distance to the nearest boundary will be returned. This method
 * is thread safe as long as enableThreadSupport has been called.
 * \warning This method will reset the internal ray.
 */
double Root::fireExternalRay( const Ray& ray )
{
  // Make sure root has been initialized
  testPrecondition( Root::isInitialized() );
  
  TGeoNode* start_node = Root::findNodeContainingPoint( ray );

  // Find the boundary and distance but do not move the internal ray to it
  TGeoNode* next_node = s_manager->FindNextBoundaryAndStep();
  
  return s_manager->GetStep();
}

// Check if the internal ray is set
/*! \details This method is thread safe as long as enableThreadSupport has
 * been called.
 */
bool Root::isInternalRaySet()
{
  // Make sure root has been initialized
  testPrecondition( Root::isInitialized() );
  // Make sure thread support has been set up correctly
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() <
                    s_internal_ray_set.size() );
  
  return s_internal_ray_set[Utility::GlobalOpenMPSession::getThreadId()];
}

// Reset the internal ray set flag
void Root::internalRayUnset()
{
  // Make sure root has been initialized
  testPrecondition( Root::isInitialized() );
  // Make sure thread support has been set up correctly
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() <
                    s_internal_ray_set.size() );
  
  s_internal_ray_set[Utility::GlobalOpenMPSession::getThreadId()] = false;
}

// Set the internal ray set flag
void Root::internalRaySet()
{
  // Make sure root has been initialized
  testPrecondition( Root::isInitialized() );
  // Make sure thread support has been set up correctly
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() <
                    s_internal_ray_set.size() );
  
  s_internal_ray_set[Utility::GlobalOpenMPSession::getThreadId()] = true;
}

// Initialize (or reset) an internal root ray 
/*! \details This method is thread safe as long as enableThreadSupport has
 * been called.
 */
void Root::setInternalRay( const double position[3], 
                           const double direction[3] )
{
  // Make sure root has been initialized
  testPrecondition( Root::isInitialized() );
  // Make sure the direction is valid
  testPrecondition( Utility::validDirection( direction ) );

  // The internal ray is set now
  Root::internalRaySet();

  TGeoNode* current_node = s_manager->InitTrack( position, direction );
}

// Initialize (or reset) an internal root ray
/*! \details This method is thread safe as long as enableThreadSupport has
 * been called. 
 */
void Root::setInternalRay( const Ray& ray )
{
  // Make sure root has been initialized
  testPrecondition( Root::isInitialized() );
  
  Root::setInternalRay( ray.getPosition(), ray.getDirection() );
}

// Change the internal ray direction (without changing its location)
void Root::changeInternalRayDirection( const double direction[3] )
{
  // Make sure root has been initialized
  testPrecondition( Root::isInitialized() );
  // Make sure the internal ray is set
  testPrecondition( Root::isInternalRaySet() );
  // Make sure the direction is valid
  testPrecondition( Utility::validDirection( direction ) );

  // Note: The TGeoManager interface should take a const double* array
  // but the array it takes is non-const.
  s_manager->SetCurrentDirection( const_cast<double*>( direction ) );
}

// Change the internal ray direction( without changing its location)
void Root::changeInternalRayDirection( const double x_direction,
                                       const double y_direction,
                                       const double z_direction )
{
  // Make sure root has been initialized
  testPrecondition( Root::isInitialized() );
  // Make sure the internal ray is set
  testPrecondition( Root::isInternalRaySet() );
  // Make sure the direction is valid
  testPrecondition( Utility::validDirection( x_direction, 
                                             y_direction,
                                             z_direction ) );

  s_manager->SetCurrentDirection( x_direction, y_direction, z_direction );
}


// Get the internal root ray position
/*! \details This method is thread safe as long as enableThreadSupport has
 * been called.
 */
const double* Root::getInternalRayPosition()
{
  // Make sure root has been initialized
  testPrecondition( Root::isInitialized() );
  // Make sure the internal ray is set
  testPrecondition( Root::isInternalRaySet() );
  
  return s_manager->GetCurrentPoint();
}

// Get the internal root ray direction
/*! \details This method is thread safe as long as enableThreadSupport has
 * been called.
 */
const double* Root::getInternalRayDirection()
{
  // Make sure root has been initialized
  testPrecondition( Root::isInitialized() );
  // Make sure the internal ray is set
  testPrecondition( Root::isInternalRaySet() );
  
  return s_manager->GetCurrentDirection();
}

// Get the cell containing the internal root ray position
/*! \details This method is thread safe as long as enableThreadSupport has
 * been called.
 */
ModuleTraits::InternalCellHandle Root::findCellContainingInternalRay()
{
  // Make sure root has been initialized
  testPrecondition( Root::isInitialized() );
  // Make sure the internal ray is set
  testPrecondition( Root::isInternalRaySet() );
  
  return s_manager->GetCurrentVolume()->GetUniqueID();
}

// Get the distance from the internal root ray position to the next boundary
/*! \details This method is thread safe as long as enableThreadSupport has
 * been called.
 */
double Root::fireInternalRay()
{
  // Make sure root has been initialized
  testPrecondition( Root::isInitialized() );
  // Make sure the internal ray is set
  testPrecondition( Root::isInternalRaySet() );
  
  TGeoNode* boundary_node = s_manager->FindNextBoundary();

  return s_manager->GetStep();
}

// Advance the internal root ray to the next boundary
/*! \details This method is thread safe as long as enableThreadSupport has
 * been called.
 */
void Root::advanceInternalRayToCellBoundary()
{
  // Make sure root has been initialized
  testPrecondition( Root::isInitialized() );
  // Make sure the internal ray is set
  testPrecondition( Root::isInternalRaySet() );
  
  TGeoNode* next_node = s_manager->Step();
}

// Advance the internal root ray a substep
void Root::advanceInternalRayBySubstep( const double substep_distance )
{
  // Make sure root has been initialized
  testPrecondition( Root::isInitialized() );
  // Make sure the internal ray is set
  testPrecondition( Root::isInternalRaySet() );
  // Make sure the substep distance is valid
  testPrecondition( substep_distance > 0.0 );
  testPrecondition( substep_distance < s_manager->GetStep() );

  // Set the step size
  s_manager->SetStep( substep_distance );

  // Advance the root ray
  TGeoNode* next_node = s_manager->Step();

  // Update the distance information
  double new_distance = Root::fireInternalRay();
}

} // end Geoemtry namespace

//---------------------------------------------------------------------------//
// end Geometry_Root.cpp
//---------------------------------------------------------------------------//
