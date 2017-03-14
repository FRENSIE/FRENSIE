//---------------------------------------------------------------------------//
//!
//! \file   Geometry_DagMCNavigator.cpp
//! \author Alex Robinson
//! \brief  The DagMC navigator class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <sstream>

// FRENSIE Includes
#include "Geometry_DagMCNavigator.hpp"
#include "Utility_GlobalOpenMPSession.hpp"
#include "Utility_MOABException.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Geometry{

// Initialize static member data
const double DagMCNavigator::s_boundary_tol = 1e-5;

// Constructor
DagMCNavigator::DagMCNavigator(
      moab::DagMC* dagmc_instance,
      const std::shared_ptr<Geometry::DagMCCellHandle>& cell_handler,
      const std::shared_ptr<Geometry::DagMCSurfaceHandler>& surface_handler,
      const std::shared_ptr<ReflectinSurfaceIdHandleMap>& reflecting_surfaces )
  : d_dagmc( dagmc_instance ),
    d_cell_handler( cell_handler ),
    d_surface_handler( surface_handler ),
    d_reflecting_surfaces( reflecting_surfaces ),
    d_internal_rays( 1 )
{
  // Make sure that the dagmc instance is valid
  testPrecondition( dagmc_instance );
  // Make sure that the cell handler is valid
  testPrecondition( cell_handler.get() );
  // Make sure that the surface handler is valid
  testPrecondition( surface_handler.get() );
  // Make sure that the reflecting surfaces are valid
  testPrecondition( reflecting_surfaces.get() );
}

// Enable thread support
/*! \details This should be called before a parallel block is entered.
 */
void DagMCNavigator::enableThreadSupport( const size_t num_threads )
{
  // Make sure that the number of threads is valid
  testPrecondition( num_threads > 0 );

  // Create an internal ray for each thread
  d_internal_rays.resize( num_threads );
}

// Get the point location w.r.t. a given cell
/*! \details This function will only return if a point is inside of or
 * outside of the cell of interest (not on the cell). The ray direction will be
 * used when it is close to the surface.
 */
PointLocation DagMCNavigator::getPointLocation(
                         const Ray& ray,
                         const ModuleTraits::InternalCellHandle cell_id ) const
{
  // Make sure that the cell exists
  testPrecondition( d_cell_handler->doesCellExist( cell_id ) );

  moab::EntityHandle cell_handle = d_cell_handler->getCellHandle( cell_id );

  try{
    return this->getPointLocation( ray.getPosition(),
                                   ray.getDirection(),
                                   cell_handle );
  }
  EXCEPTION_CATCH_RETHROW( DagMCGeometryError,
                           "Could not determing the location of the "
                           "ray with respect to cell "
                           << cell_id << "! Here are the details...\n  "
                           "Ray: " << ray  );
}

// Get the surface normal at a point on the surface
/*! \details The dot product of the normal and the direction will be 
 * positive defined.
 */
void DagMCNavigator::getSurfaceNormal(
                          const ModuleTraits::InternalSurfaceHandle surface_id,
                          const double position[3],
                          const double direction[3],
                          double normal[3] ) const
{
  // Make sure that the surface exists
  testPrecondition( d_surface_handler->doesSurfaceExist( surface_id ) );

  moab::EntityHandle surface_handle =
    d_surface_handler->getSurfaceHandle( surface_id );

  this->getSurfaceHandleNormal( surface_handle, position, direction, normal );
}

// Get the surface normal at a point on the surface
void DagMCNavigator::getSurfaceHandleNormal(
                                 const moab::EntityHandle surface_handle,
                                 const double position[3],
                                 const double direction[3],
                                 double normal[3],
                                 const moab::DagMC::RayHistory* history ) const
{
  moab::ErrorCode return_value = d_dagmc->get_angle( surface_handle,
                                                     position,
                                                     normal,
                                                     history );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      DagMCGeometryError,
                      moab::ErrorCodeStr[return_value] );

  // Make sure that the dot product of the direction and the surface normal
  // is positive defined
  if( Utility::calculateCosineOfAngleBetweenUnitVectors(direction, normal)< 0 )
  {
    normal[0] *= -1.0;
    normal[1] *= -1.0;
    normal[2] *= -1.0;
  }
}

// Get the boundary cell
/*! \details DagMC geometries are set up so that every surface belongs to
 * exactly two cells. When a ray crosses a boundary surface finding the
 * next cell that will be entered is simply a matter of knowing the current
 * cell and the boundary surface.
 */
ModuleTraits::InternalCellHandle DagMCNavigator::getBoundaryCell(
          const ModuleTraits::InternalCellHandle cell_id,
          const ModuleTraits::InternalSurfaceHandle boundary_surface_id ) const
{
  // Make sure that the cell exists
  testPrecondition( d_cell_handler->doesCellExist( cell_id ) );
  // Make sure that the surface exists
  testPrecondition( d_surface_handler->doesSurfaceExist( boundary_surface_id ) );

  moab::EntityHandle current_cell_handle =
    d_cell_handler->getCellHandle( cell_id );

  moab::EntityHandle boundary_surface_handle =
    d_surface_handler->getSurfaceHandle( boundary_surface_id );

  moab::EntityHandle boundary_cell_handle =
    this->getBoundaryCellHandle( current_cell_handle,
                                 boundary_surface_handle );

  return d_cell_handler->getCellId( boundary_cell_handle );
}

// Find the cell that contains the start ray
ModuleTraits::InternalCellHandle DagMCNavigator::findCellContainingStartRay(
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
    PointLocation test_point_location;

    try{
      test_point_location =
        this->getPointLocation( ray, *start_cell_cache_it );
    }
    EXCEPTION_CATCH_RETHROW( DagMCGeometryError,
                             "Could not find the location of the ray!" );

    if( test_point_location == POINT_INSIDE_CELL )
      return *start_cell_cache_it;
    
    ++start_cell_cache_it;
  }

  // Check all other cells
  ModuleTraits::InternalCellHandle found_cell;

  try{
    found_cell = this->findCellContainingRay( ray );
  }
  EXCEPTION_CATCH_RETHROW( DagMCGeometryError,
                           "Could not find the cell that contains the ray!" );

  // Add the cell to the cache
  start_cell_cache.insert( found_cell );

  return found_cell;
}

// Find the cell that contains the ray
ModuleTraits::InternalCellHandle DagMCNavigator::findCellContainingRay(
                                                         const Ray& ray ) const
{
  moab::EntityHandle cell_handle =
    this->findCellHandleContainingExternalRay( ray );

  return d_cell_handler->getCellId( cell_handle );
}

// Find the cell that contains the ray
ModuleTraits::InternalCellHandle
DagMCNavigator::findCellContainingRayWithoutBoundaryCheck(
                                                         const Ray& ray ) const
{
  moab::EntityHandle cell_handle =
    this->findCellHandleContainingExternalRay( ray, false );

  return d_cell_handler->getCellId( cell_handle );
}

// Fire the ray through the geometry
/*! \details The cell containing the ray position will be found before firing
 * the ray.
 */
double DagMCNavigator::fireRay(
                       const Ray& ray,
                       ModuleTraits::InternalSurfaceHandle& surface_hit ) const
{
  // Find the cell that contains the ray
  moab::EntityHandle cell_handle;

  // Fire the ray
  moab::EntityHandle surface_hit_handle;

  double distance_to_surface_hit =
    this->fireRayWithCellHandle( ray.getPosition(),
                                 ray.getDirection(),
                                 cell_handle,
                                 surface_hit_handle );

  surface_hit = d_surface_handler->getSurfaceId( surface_hit_handle );

  return distance_to_surface_hit;
}

// Check if the internal ray is set
bool DagMCNavigator::isInternalRaySet() const
{
  return this->getInternalRay().isReady();
}

// Initialize (or reset) an internal DagMC ray
void DagMCNavigator::setInternalRay( const double x_position,
                                     const double y_position,
                                     const double z_position,
                                     const double x_direction,
                                     const double y_direction,
                                     const double z_direction )
{
  // Make sure that the direction is valid
  testPrecondition( Utility::isUnitVector( x_direction, y_direction, z_direction ) );

  moab::EntityHandle cell_handle =
    this->findCellHandleContainingRay( x_position, y_position, z_position,
                                       x_direction, y_direction, z_direction );

  this->setInternalRay( x_position, y_position, z_position,
                        x_direction, y_direction, z_direction,
                        cell_handle );
}
                       
// Initialize (or reset) an internal DagMC ray
void DagMCNavigator::setInternalRay(
                          const double x_position,
                          const double y_position,
                          const double z_position,
                          const double x_direction,
                          const double y_direction,
                          const double z_direction,
                          const ModuleTraits::InternalCellHandle current_cell )
{
  // Make sure that the direction is valid
  testPrecondition( Utility::isUnitVector( x_direction, y_direction, z_direction ) );
  // Make sure that the cell exists
  testPrecondition( d_cell_handler->doesCellExist( current_cell ) );
  // Make sure that the cell contains the ray
  remember( Ray test_ray( x_position, y_position, z_position,
                          x_direction, y_direction, z_direction ) );
  testPrecondition( this->findCellContainingRayWithoutBoundaryCheck( test_ray )
                    == current_cell );

  moab::EntityHandle cell_handle =
    d_cell_handler->getCellHandle( current_cell );

  this->setInternalRay( x_position, y_position, z_position,
                        x_direction, y_direction, z_direction,
                        cell_handle );
}

// Get the internal DagMC ray position
const double* DagMCNavigator::getInternalRayPosition() const
{
  // Make sure that the ray is set
  testPrecondition( this->isInternalRaySet() );

  return this->getInternalRay().getPosition();
}

// Get the internal DagMC ray direction
const double* DagMCNavigator::getInternalRayDirection() const
{
  // Make sure that the ray is set
  testPrecondition( this->isInternalRaySet() );

  return this->getInternalRay().getDirection();
}

// Find the cell containing the internal DagMC ray position
ModuleTraits::InternalCellHandle
DagMCNavigator::findCellContainingInternalRay()
{
  // Make sure that the ray is set
  testPrecondition( this->isInternalRaySet() );

  return d_cell_handler->getCellId( this->getInternalRay().getCurrentCell() );
}

// Get the distance from the internal DagMC ray pos. to the nearest boundary
double DagMCNavigator::fireInternalRay(
                             ModuleTraits::InternalSurfaceHandle& surface_hit )
{
  // Make sure that the ray is set
  testPrecondition( this->isInternalRaySet() );

  double distance_to_surface;

  DagMCRay& ray = this->getInternalRay();

  // Check if the ray has already been fired
  if( ray.knowsIntersectionSurface() )
  {
    surface_hit =
      d_surface_handler->getSurfaceId( ray.getIntersectionSurface() );

    distance_to_surface = ray.getDistanceToIntersectionSurface();
  }
  else
  {
    moab::EntityHandle surface_hit_handle;

    distance_to_surface = this->fireRayWithCellHandle( ray.getPosition(),
                                                       ray.getDirection(),
                                                       ray.getCurrentCell(),
                                                       surface_hit_handle,
                                                       &ray.getHistory() );

    surface_hit = s_surface_handler->getSurfaceId( surface_hit_handle );

    // Cache the surface data in the ray
    ray.setIntersectionSurfaceData( surface_hit_handle, distance_to_surface );
  }

  return distance_to_surface;
}

// Advance the internal DagMC ray to the next boundary
/*! \details Upon reaching the boundary the internal ray will enter the
 * boundary cell if the boundary surface is not a reflecting surface. The
 * ray will be reflected at the boundary if a reflecting surface is
 * encountered. This method will return true if a reflecting boundary
 * was encountered. If the surface normal at the intersection point is
 * required an array can be passed to the method.
 */
bool DagMCNavigator::advanceInternalRayToCellBoundary( double* surface_normal )
{
  // Make sure that the ray is set
  testPrecondition( this->isInternalRaySet() );
  // Make sure that the instersection surface is know
  testPrecondition( this->getInternalRay().knowsIntersectionSurface() );
  
  bool reflecting_boundary = false;

  DagMCRay& ray = this->getInternalRay();

  moab::EntityHandle intersection_surface = ray.getIntersectionSurface();

  // Reflect the ray if a reflecting surface is encountered
  if( this->isReflectingSurfaceHandle( ray.getIntersectionSurface() ) )
  {
    // Advance the ray to the cell boundary and enter the next cell
    ray.advanceToIntersectionSurface( ray.getCurrentCell() );

    double local_surface_normal[3];

    this->getSurfaceHandleNormal( intersection_surface,
                                  ray.getPosition(),
                                  local_surface_normal,
                                  &ray.getHistory() );

    if( surface_normal != NULL )
    {
      surface_normal[0] = local_surface_normal[0];
      surface_normal[1] = local_surface_normal[1];
      surface_normal[2] = local_surface_normal[2];
    }

    double reflected_direction[3];

    Utility::reflectUnitVector( ray.getDirection(),
                                local_surface_normal,
                                reflected_direction );

    // This will also fire a ray to fill the new intersection data
    this->changeInternalRayDirection( reflected_direction );

    reflecting_boundary = true;
  }
  // Pass into the next cell if a normal surface is encountered
  else
  {
    moab::EntityHandle next_cell_handle =
      this->getBoundaryCellHandle( ray.getCurrentCell(),
                                   ray.getIntersectionSurface() );

    ray.advanceToIntersectionSurface( next_cell_handle );

    if( surface_normal != NULL )
    {
      this->getSurfaceHandleNormal( intersection_surface,
                                    ray.getPosition(),
                                    surface_normal,
                                    &ray.getHistory() );
    }
  }

  // Fire the ray so that the new intersection data is set
  ModuleTraits::InternalSurfaceHandle dummy_surface;

  double distance = this->fireInternalRay( dummy_surface );

  return reflecting_boundary;
}

// Advance the internal DagMC ray a substep
/*! \details The substep distance must be less than the distance to the
 * intersection surface.
 */
void DagMCNavigator::advanceInternalRayBySubstep(
                                                const double substep_distance )
{
  // Make sure that the ray is set
  testPrecondition( this->isInternalRaySet() );
  // Make sure that the substep distance is valid
  testPrecondition( substep_distance >= 0.0 );
  testPrecondition( substep_distance <
                    this->getInternalRay().getDistanceToIntersectionSurface());
  
  this->getInternalRay().advanceSubstep( substep_distance );
}

// Change the internal ray direction (without changing its location)
void DagMCNavigator::changeInternalRayDirection( const double x_direction,
                                                 const double y_direction,
                                                 const double z_direction )
{
  // Make sure that the ray is set
  testPrecondition( this->isInternalRaySet() );
  // Make sure that the direction is valid
  testPrecondition( Utility::isUnitVector( x_direction, y_direction, z_direction ) );

  DagMCRay& internal_ray = this->getInternalRay();

  // Change the direction
  internal_ray.changeDirection( x_direction, y_direction, z_direction );

  // Fire the ray so that the new intersection data is set
  ModuleTraits::InternalSurfaceHandle dummy_surface;

  double distance = this->fireInternalRay( dummy_surface );
}

// Convert an array to a string
std::string DagMCNavigator::arrayToString( const double data[3] )
{
  std::ostringstream oss;

  oss << "{" << data[0] << "," << data[1] << "," << data[2] << "}";

  return oss.str();
}

// Check if the surface handle is a reflecting surface
bool DagMCNavigator::isReflectingSurfaceHandle(
                                const moab::EntityHandle surface_handle ) const
{
  return d_reflecting_surfaces.right.find( surface_handle ) !=
    d_reflecting_surfaces.right.end();
}

// Get the point location w.r.t. a given cell
PointLocation DagMCNavigator::getPointLocation(
                                 const double position[3],
                                 const double direction[3],
                                 const moab::EntityHandle cell_handle,
                                 const moab::DagMC::RayHistory* history ) const
{
  // Make sure that the direction is valid
  testPrecondition( Utility::isUnitVector( direction ) );

  int test_result;

  moab::ErrorCode return_value = d_dagmc->point_in_volume( cell_handle,
                                                           position,
                                                           test_result,
                                                           direction,
                                                           history );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
		      DagMCGeometryError,
		      moab::ErrorCodeStr[return_value] );

  switch( test_result )
  {
  case -1:
    return POINT_ON_CELL;
  case 0:
    return POINT_OUTSIDE_CELL;
  case 1:
    return POINT_INSIDE_CELL;
  }
}
  
// Get the boundary cell handle
moab::EntityHandle DagMCNavigator::getBoundaryCellHandle(
                       const moab::EntityHandle cell_handle,
                       const moab::EntityHandle boundary_surface_handle ) const
{
  moab::EntityHandle boundary_cell_handle;

  moab::ErrorCode return_value = d_dagmc->next_vol( boundary_surface_handle,
                                                    cell_handle,
                                                    boundary_cell_handle );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
		      DagMCGeometryError,
		      moab::ErrorCodeStr[return_value] );

  TEST_FOR_EXCEPTION(
               boundary_cell_handle == 0,
               DagMCGeometryError,
               "Could not find the boundary cell! Here are the details...\n"
               "  Current cell: "
               << d_cell_handler->getCellId( cell_handle ) << "\n"
               "  Boundary Surface: "
               << d_surface_handler->getSurfaceId( boundary_surface_handle ) );

  return boundary_cell_handle;
}

// Get the internal DagMC ray
DagMCRay& DagMCNavigator::getInternalRay()
{
  // Make sure that thread support has been set up correctly
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() <
                    d_internal_rays.size() );

  return d_internal_rays[Utility::GlobalOpenMPSession::getThreadId()];
}

// Get the internal DagMC ray
const DagMCRay& DagMCNavigator::getInternalRay() const
{
  // Make sure that thread support has been set up correctly
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() <
                    d_internal_rays.size() );

  return d_internal_rays[Utility::GlobalOpenMPSession::getThreadId()];
}

// Find the cell handle that contains the ray (brute force)
// All of the cells in the geometry will be tested for containment of
// the ray head. This is an order N search.
moab::EntityHandle DagMCNavigator::findCellHandleContainingRay(
                                       const Ray& ray,
                                       const bool boundary_check = true ) const
{
  return this->findCellHandleContainingRay( ray.getPosition(),
                                            ray.getDirection(),
                                            boundary_check );
}

// Find the cell handle that contains the ray
moab::EntityHandle DagMCNavigator::findCellHandleContainingRay(
                                   const double position[3],
                                   const double direction[3],
                                   const bool check_on_boundary = false ) const
{
  // Make sure that the direction is valid
  testPrecondition( Utility::isUnitVector( direction ) );

  moab::EntityHandle cell_handle = 0;

  // Test all of the cells
  moab::Range::const_iterator cell_handle_it = d_cell_handler->begin();

  while( cell_handle_it != d_cell_handler->end() )
  {
    PointLocation test_point_location;

    try{
      test_point_location =
        this->getPointLocation( position, direction, *cell_handle_it );
    }
    EXCEPTION_CATCH_RETHROW( DagMCGeometryError,
                             "Could not find the location of the ray with "
                             "respect to cell "
                             << d_cell_handler->getCellId( *cell_handle_it ) <<
                             "! Here are the details...\n"
                             "Position: "
                             << this->arrayToString( position ) << "\n"
                             "Direction: "
                             << this->arrayToString( direction ) );

    if( test_point_location == POINT_INSIDE_CELL )
    {
      cell_handle = *cell_handle_it;

      break;
    }

    ++cell_handle_it;
  }

  // Make sure that a cell handle was found
  TEST_FOR_EXCEPTION( cell_handle == 0,
                      DagMCGeometryError,
                      "Could not find a cell that contains the requested ray! "
                      "Here are the details...\n"
                      "  Position: "
                      << this->arrayToString( position ) << "\n"
                      "  Direction: "
                      << this->arrayToString( direction ) );

  if( check_on_boundary )
  {
    moab::EntityHandle surface_hit_handle;

    double distance_to_boundary = this->fireExternalRayWithCellHandle(
                                                          position,
                                                          direction,
                                                          cell_handle,
                                                          surface_hit_handle );

    // Return the next cell instead
    if( distance_to_boundary < s_boundary_tol )
    {
      cell_handle = this->getBoundaryCellHandle( cell_handle,
                                                 surface_hit_handle );
   } 
  }
}

// Get the distance from the ray position to the nearest boundary
double DagMCNavigator::fireRayWithCellHandle(
                                 const double position[3],
                                 const double direction[3],
                                 const moab::EntityHandle current_cell_handle,
                                 moab::EntityHandle& surface_hit_handle,
                                 moab::DagMC::RayHistory* history ) const
{
  // Make sure that the direction is valid
  testPrecondition( Utility::isUnitVector( direction ) );

  double distance_to_surface;

  moab::ErrorCode return_value = d_dagmc->ray_fire( current_cell_handle,
                                                    position,
                                                    direction,
                                                    surface_hit_handle,
                                                    distance_to_surface,
                                                    &ray.getHistory() );
  
  // Check for a ray misfire which can be caused by a poorly created geometry
  // or by gaps in the surface facets, which can occur for properly created
  // geometries.
  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      DagMCGeometryError,
                      moab::ErrorCodeStr[return_value] );

  TEST_FOR_EXCEPTION(
                   surface_hit_handle == 0,
                   DagMCGeometryError,
                   "DagMC had a ray misfire! Here are the details...\n"
                   "  Current Cell: "
                   << s_cell_handler->getCellId( current_cell_handle ) << "\n"
                   "  Position: "
                   << this->arrayToString( position ) << "\n"
                   "  Direction: "
                   << this->arrayToString( direction ) );

  TEST_FOR_EXCEPTION(
               distance_to_surface < 0.0,
               DagMCGeometryError,
               "DagMC had a ray misfire! Here are the details...\n"
               "  Current Cell: "
               << s_cell_handler->getCellId( current_cell_handle ) << "\n"
               "  Surface Hit: "
               << s_surface_handler->getSurfaceId( surface_hit_handle ) << "\n"
               "  Position: "
               << this->arrayToString( position ) << "\n"
               "  Direction: "
               << this->arrayToString( direction ) );

  return distance_to_surface;
}

// Set an internal DagMC ray
void DagMCNavigator::setInternalRay(
                                 const double x_position,
                                 const double y_position,
                                 const double z_position,
                                 const double x_direction,
                                 const double y_direction,
                                 const double z_direction,
                                 const moab::EntityHandle current_cell_handle )
{
  // Make sure that the direction is valid
  testPrecondition( Utility::isUnitVector( x_direction, y_direction, z_direction ) );
  
  DagMCRay& dagmc_ray = this->getInternalRay();

  // Set the basic ray info
  dagmc_ray.set( position, direction, current_cell_handle );

  // Fire the ray so that the intersection data is set
  ModuleTraits::InternalSurfaceHandle dummy_surface;

  double distance = this->fireInternalRay( dummy_surface );
}
  
} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_DagMCNavigator.cpp
//---------------------------------------------------------------------------//
