//---------------------------------------------------------------------------//
//!
//! \file   Geometry_RootNavigator.cpp
//! \author Alex Robinson, Eli Moll
//! \brief  The Root navigator class declaration
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Geometry_RootNavigator.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_GlobalOpenMPSession.hpp"
#include "Utility_ContractException.hpp"

namespace Geometry{

// Initialize static member data
const double RootNavigator::s_tol = 1e-5;

// Constructor
RootNavigator::RootNavigator(
                             const TGeoManager* manager,
                             const CellIdToTGeoVolumeFunction& get_volume_ptr )
  : d_manager( manager ),
    d_get_volume_ptr( get_volume_ptr ),
    d_internal_ray_set( 1, false ),
    d_navigators( 1, NULL )
{
  // Initialize a navigator
  d_navigators.front() = new TGeoNavigator( d_manager );
  d_manager->AddNavigator( d_navigators.front() );
}

// Destructor
RootNavigator::~RootNavigator()
{
  this->deleteNavigators();
}

// Delete the navigators
void RootNavigator::deleteNavigators()
{
  // Delete the navigators
  for( size_t i = 0; i < d_navigators.size(); ++i )
    d_manager->RemoveNavigator( d_navigators[i] );
}

// Enable thread support
void RootNavigator::enableThreadSupport( const size_t num_threads )
{
  // Make sure that the number of threads is valid
  testPrecondition( num_threads > 0 );

  // Check if a different number of threads must be supported
  if( num_threads != d_navigators.size() )
  {
    // Delete the default navigator
    this->deleteNavigators();
    
    // Check if the max number of threads in the manager needs to be increased
    Int_t current_num_threads = d_manager->GetMaxThreads( num_threads );

    if( current_num_threads < num_threads )
      d_manager->SetMaxThreads( num_threads );

    // Resize the thread data
    d_navigators.resize( num_threads );
    d_internal_ray_set.resize( num_threads, false );

    // A navigator must be created for each thread, by each thread
    #pragma omp parallel num_threads( num_threads )
    {
      d_navigators[Utility::GlobalOpenMPSession::getThreadId()] =
        s_manager->AddNavigator();
    }
  }
}

// Get the point location w.r.t. a given cell
/*! \details Root only allows one to test if a point is inside or outside
 * a cell (not on a cell). If the point is on a cell Root will return
 * inside (unless one of the boundary cells is a daughter node of the
 * cell or interest). This method is thread safe as long as enableThreadSupport
 * has been called.
 */
PointLocation RootNavigator::getPointLocation(
                         const Ray& ray,
                         const ModuleTraits::InternalCellHandle cell_id ) const
{
  return this->getPointLocation( ray.getPosition(), cell_id );
}

// Get the point location w.r.t. a given cell
PointLocation RootNavigator::getPointLocation(
                         const double position[3],
                         const ModuleTraits::InternalCellHandle cell_id ) const
{
  TGeoVolume* cell = d_get_volume_ptr( cell_id );

  PointLocation location;

  if( cell->Contains( position ) )
  {
    location = POINT_INSIDE_CELL;

    // Check if the point is an any daughters
    TObjArray* daughters = cell->GetNodes();

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

// Get the surface normal at a point on the surface
/*! \details The surface id will not be used. The dot product of the normal
 * and the direction will be positive defined. This method is thread safe as
 * long as enableThreadSupport has been called.
 */
void RootNavigator::getSurfaceNormal(
                          const ModuleTraits::InternalSurfaceHandle,
                          const double position[3],
                          const double direction[3],
                          double normal[3] ) const
{
  TGeoNode* node = this->findNodeContainingRay( ray );

  const TGeoNavigator* navigator = this->getNavigator();
  
  // Note: This is basically a reimplementation of the
  // TGeoNavigator::GetNormalFast method. Because we want to preserve our
  // internal ray state this reimplementation is necessary
  double local_position[3];
  node->MasterToLocal( position, local_position );
  
  double local_direction[3];
  node->MasterToLocal( direction, local_direction );

  double local_normal[3];

  node->GetVolume()->GetShape()->ComputeNormal( local_position,
                                                local_direction,
                                                local_normal );

  node->LocalToMaster( local_direction, normal );

  // Make sure that the normal is a unit vector
  if( !Utility::isUnitVector( normal ) )
    Utility::normalizeVector( normal );
}

// Find the cell that contains the start ray
/*! \details This method is thread safe as long as enableThreadSupport has
 * been called.
 */
ModuleTraits::InternalCellHandle RootNavigator::findCellContainingStartRay(
                                              const Ray& ray,
                                              CellSet& start_cell_cache ) const
{
  // Test the cells in the cache first
  CellSet::const_iterator start_cell_cache_it, start_cell_cache_end;
  start_cell_cache_it = start_cell_cache.begin();
  start_cell_cache_end = start_cell_cache.end();

  // Check the cache first
  while( start_cell_cache_it != start_cell_cache_end )
  {
    PointLocation test_point_location =
      this->getPointLocation( ray, *start_cell_cache_it );

    if( test_point_location == POINT_INSIDE_CELL )
      return *start_cell_cache_it;
    
    ++start_cell_cache_it;
  }

  // Check all other cells
  ModuleTraits::InternalCellHandle found_cell =
    this->findCellContainingRay( ray );

  // Add the cell to the cache
  start_cell_cache.insert( found_cell );

  return found_cell;
}

// Find the cell that contains the ray
/*! \details This method is thread safe as long as enableThreadSupport has
 * been called.
 */
ModuleTraits::InternalCellHandle RootNavigator::findCellContainingRay(
                                           const Ray& ray,
                                           double* distance_to_boundary ) const
{
  return this->findNodeContainingRay( ray )->GetVolume()->GetUniqueID();
}

// Find the node containing the ray
// Note: The internal ray will have to be modified during the execution
//       of this method. However, it's initial state will be restored, which
//       will make it appear as if it hasn't been changed. That is why this
//       this method is const.
TGeoNode* RootNavigator::findNodeContainingRay( const Ray& ray ) const
{
  // Get the calling thread's navigator
  TGeoNavigator* navigator = const_cast<TGeoNavigator*>(this->getNavigator());

  // Cache the navigator's state
  double cached_position[3];
  double cached_direction[3];

  if( this->isInternalRaySet() )
  {
    RootNavigator::deepCopy( cached_position, navigator->GetCurrentPoint() );
    RootNavigator::deepCopy( cached_direction,
                             navigator->GetCurrentDirection() );
  }

  // Set the temporary state
  TGeoNode* current_node = navigator->InitTrack( ray.getPosition(),
                                                 ray.getDirection() );

  TGeoNode* boundary_node = navigator->FindNextBoundary();

  double step_size = navigator->GetStep();

  TGeoNode* node_containing_point;

  // If the point is within the boundary tolerance return the next node
  if( step_size < s_tol )
  {
    node_containing_point = navigator->Step();

    // Update the step size
    navigator->FindNextBoundary();
    step_size = navigator->GetStep();
  }
  else
    node_containing_point = current_node;

  // Make sure the node is valid
  testPostcondition( node_containing_point != NULL );

  // Reset the navigator state
  if( this->isInternalRaySet() )
  {
    navigator->InitTrack( cached_position, cached_direction );
    navigator->FindNextBoundary();
  }

  // Set the distance to the boundary
  if( distance_to_boundary != NULL )
    *distance_to_boundary = step_size;

  return node_containing_point;
}

// Fire the ray through the geometry
/*! \details The distance to the nearest boundary will be returned. Surfaces
 * aren't managed separately in Root (they are simply part of the cell
 * definition). Therefore the surface hit will always be invalid. This method
 * is thread safe as long as enableThreadSupport has been called. 
 */
double RootNavigator::fireRay(
                       const Ray& ray,
                       ModuleTraits::InternalSurfaceHandle& surface_hit ) const
{
  double distance_to_boundary;
  
  TGeoNode* start_node =
    this->findNodeContainingRay( ray, &distance_to_boundary );

  surface_hit = ModuleTraits::invalid_internal_surface_handle;
  
  return distance_to_boundary;
}

// Check if the internal ray is set
bool RootNavigator::isInternalRaySet() const
{
  // Make sure that thread support has been set up correctly
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() <
                    d_internal_ray_set.size() );

  return d_internal_ray_set[Utility::GlobalOpenMPSession::getThreadId()];
}

// Set the internal ray set flag
void RootNavigator::internalRaySet()
{
  // Make sure that thread support has been set up correctly
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() <
                    d_internal_ray_set.size() );

  d_internal_ray_set[Utility::GlobalOpenMPSession::getThreadId()] = true;
}

// Initialize (or reset) an internal Root ray
/*! \details This method is thread safe as long as enableThreadSupport has
 * been called.
 */
void RootNavigator::setInternalRay( const double x_position,
                                    const double y_position,
                                    const double z_position,
                                    const double x_direction,
                                    const double y_direction,
                                    const double z_direction )
{
  // Make sure that the direction is valid
  testPrecondition( Utility::isUnitVector( x_direction, y_direction, z_direction ) );

  // The internal ray is set now
  this->internalRaySet();

  this->getNavigator()->InitTrack( x_position, y_position, z_position,
                                   x_direction, y_direction, z_direction );
}
                      
                       
// Initialize (or reset) an internal Root ray
/*! \details Root will not use the cell to speed up it's lookup. This method is
 * thread safe as long as enableThreadSupport has been called.
 */
void RootNavigator::setInternalRay(
                          const double x_position,
                          const double y_position,
                          const double z_position,
                          const double x_direction,
                          const double y_direction,
                          const double z_direction,
                          const ModuleTraits::InternalCellHandle )
{
  this->setInternalRay( x_position, y_position, z_position,
                        x_direction, y_direction, z_direction );
}

// Get the internal Root ray position
/*! \details This method is thread safe as long as enableThreadSupport has
 * been called.
 */
const double* RootNavigator::getInternalRayPosition() const
{
  // Make sure that the internal ray is set
  testPrecondition( this->isInternalRaySet() );

  return this->getNavigator()->GetCurrentPoint();
}

// Get the internal Root ray direction
/*! \details This method is thread safe as long as enableThreadSupport has
 * been called.
 */
const double* RootNavigator::getInternalRayDirection() const
{
  // Make sure that the internal ray is set
  testPrecondition( this->isInternalRaySet() );

  return this->getNavigator()->GetCurrentDirection();
}

// Find the cell containing the internal Root ray position
/*! \details This method is thread safe as long as enableThreadSupport has
 * been called.
 */
ModuleTraits::InternalCellHandle RootNavigator::findCellContainingInternalRay()
{
  // Make sure that the internal ray is set
  testPrecondition( this->isInternalRaySet() );

  return this->getNavigator()->GetCurrentVolume()->GetUniqueID();
}

// Get the distance from the internal Root ray pos. to the nearest boundary
/*! \details The distance to the nearest boundary will be returned. Surfaces
 * aren't managed separately in Root (they are simply part of the cell
 * definition). Therefore the surface hit will always be invalid. This method
 * is thread safe as long as enableThreadSupport has been called. 
 */
double RootNavigator::fireInternalRay(
                             ModuleTraits::InternalSurfaceHandle& surface_hit )
{
  // Make sure that the internal ray is set
  testPrecondition( this->isInternalRaySet() );

  TGeoNavigator* navigator = this->getNavigator();
  
  TGeoNode* boundary_node = navigator->FindNextBoundary();

  surface_hit = ModuleTraits::invalid_internal_surface_handle;

  return navigator->GetStep();
}

// Advance the internal Root ray to the next boundary
/*! \details This method is thread safe as long as enableThreadSupport has
 * been called.
 */
bool RootNavigator::advanceInternalRayToCellBoundary( double* surface_normal )
{
  // Make sure that the internal ray is set
  testPrecondition( this->isInternalRaySet() );
  
  TGeoNavigator* navigator = this->getNavigator();

  TGeoNode* next_node = navigator->Step();

  // Compute the surface normal at the boundary
  const double* calculated_normal = navigator->FindNormal();

  RootNavigator::deepCopy( surface_normal, calculated_normal );
}

// Advance the internal Root ray a substep
/*! \details This method is thread safe as long as enableThreadSupport has
 * been called.
 */
void RootNavigator::advanceInternalRayBySubstep( const double substep_distance )
{
  // Make sure that the internal ray is set
  testPrecondition( this->isInternalRaySet() );
  // Make sure that the substep distance is valid
  testPrecondition( substep_distance > 0.0 );
  testPrecondition( substep_distance < this->getNavigator()->GetStep() );

  TGeoNavigator* navigator = this->getNavigator();

  // Set the step size
  navigator->SetStep( substep_distance );

  // Advance the root ray
  TGeoNode* next_node = navigator->Step();

  // Update the ray data
  this->fireInternalRay();
}

// Change the internal ray direction (without changing its location)
/*! \details This method is thread safe as long as enableThreadSupport has
 * been called.
 */
void RootNavigator::changeInternalRayDirection( const double x_direction,
                                                const double y_direction,
                                                const double z_direction )
{
  // Make sure that the internal ray is set
  testPrecondition( this->isInternalRaySet() );
  // Make sure that the direction is valid
  testPrecondition( Utility::isUnitVector( x_direction, y_direction, z_direction ) );

  this->getNavigator()->SetCurrentDirection( x_direction,
                                             y_direction,
                                             z_direction );
}

// Get the navigator for the calling thread
TGeoNavigator* RootNavigator::getNavigator()
{
  // Make sure that thread support has been set up correctly
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() <
                    d_internal_ray_set.size() );

  return d_navigators[Utility::GlobalOpenMPSession::getThreadId()];
}

// Get the navigator for the calling thread
const TGeoNavigator* RootNavigator::getNavigator() const
{
  // Make sure that thread support has been set up correctly
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() <
                    d_internal_ray_set.size() );

  return d_navigators[Utility::GlobalOpenMPSession::getThreadId()];
}
  
} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_RootNavigator.cpp
//---------------------------------------------------------------------------//
