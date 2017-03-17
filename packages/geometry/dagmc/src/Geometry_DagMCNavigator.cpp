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
                    const std::shared_ptr<const Geometry::DagMCCellHandler>&
                    cell_handler,
                    const std::shared_ptr<const Geometry::DagMCSurfaceHandler>&
                    surface_handler,
                    const std::shared_ptr<const ReflectingSurfaceIdHandleMap>&
                    reflecting_surfaces )
  : d_dagmc( dagmc_instance ),
    d_cell_handler( cell_handler ),
    d_surface_handler( surface_handler ),
    d_reflecting_surfaces( reflecting_surfaces ),
    d_internal_ray()
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

// Get the point location w.r.t. a given cell
/*! \details This function will only return if a point is inside of or
 * outside of the cell of interest (not on the cell). The ray direction will be
 * used when it is close to the surface.
 */
PointLocation DagMCNavigator::getPointLocation(
                         const double position[3],
                         const double direction[3],
                         const ModuleTraits::InternalCellHandle cell_id ) const
{
  // Make sure that the cell exists
  testPrecondition( d_cell_handler->doesCellExist( cell_id ) );

  moab::EntityHandle cell_handle = d_cell_handler->getCellHandle( cell_id );
 
  try{
    return this->getPointLocation( position, direction, cell_handle );
  }
  EXCEPTION_CATCH_RETHROW( DagMCGeometryError,
                           "Could not determing the location of the "
                           "ray with respect to cell "
                           << cell_id << "! Here are the details...\n  "
                           "  Position: "
                           << this->arrayToString( position ) << "\n"
                           "  Direction: "
                           << this->arrayToString( direction ) );
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

// Find the cell that contains the ray
ModuleTraits::InternalCellHandle DagMCNavigator::findCellContainingRay(
                                              const double position[3],
                                              const double direction[3] ) const
{
  moab::EntityHandle cell_handle =
    this->findCellHandleContainingRay( position, direction );
  
  return d_cell_handler->getCellId( cell_handle );
}

// Check if the internal ray is set
bool DagMCNavigator::isInternalRaySet() const
{
  return d_internal_ray.isReady();
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
  remember( moab::EntityHandle test_cell_handle =
            this->findCellHandleContainingRay(
                                        x_position, y_position, z_position,
                                        x_direction, y_direction, z_direction,
                                        false ) );
  testPrecondition( d_cell_handler->getCellId( test_cell_handle ) ==
                    current_cell );

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

  return d_internal_ray.getPosition();
}

// Get the internal DagMC ray direction
const double* DagMCNavigator::getInternalRayDirection() const
{
  // Make sure that the ray is set
  testPrecondition( this->isInternalRaySet() );

  return d_internal_ray.getDirection();
}

// Get the cell containing the internal DagMC ray position
ModuleTraits::InternalCellHandle
DagMCNavigator::getCellContainingInternalRay() const
{
  // Make sure that the ray is set
  testPrecondition( this->isInternalRaySet() );

  return d_cell_handler->getCellId( d_internal_ray.getCurrentCell() );
}

// Get the distance from the internal DagMC ray pos. to the nearest boundary
double DagMCNavigator::fireInternalRay(
                             ModuleTraits::InternalSurfaceHandle* surface_hit )
{
  // Make sure that the ray is set
  testPrecondition( this->isInternalRaySet() );

  double distance_to_surface;

  // Check if the ray has already been fired
  if( d_internal_ray.knowsIntersectionSurface() )
  {
    if( surface_hit != NULL )
    {
      *surface_hit = d_surface_handler->getSurfaceId(
                                     d_internal_ray.getIntersectionSurface() );
    }

    distance_to_surface = d_internal_ray.getDistanceToIntersectionSurface();
  }
  else
  {
    moab::EntityHandle surface_hit_handle;

    distance_to_surface = this->fireRayWithCellHandle(
                                               d_internal_ray.getPosition(),
                                               d_internal_ray.getDirection(),
                                               d_internal_ray.getCurrentCell(),
                                               surface_hit_handle,
                                               &d_internal_ray.getHistory() );

    if( surface_hit != NULL )
      *surface_hit = d_surface_handler->getSurfaceId( surface_hit_handle );

    // Cache the surface data in the ray
    d_internal_ray.setIntersectionSurfaceData( surface_hit_handle,
                                               distance_to_surface );
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
  testPrecondition( d_internal_ray.knowsIntersectionSurface() );
  
  bool reflecting_boundary = false;

  moab::EntityHandle intersection_surface =
    d_internal_ray.getIntersectionSurface();

  // Reflect the ray if a reflecting surface is encountered
  if( this->isReflectingSurfaceHandle(d_internal_ray.getIntersectionSurface()))
  {
    // Advance the ray to the cell boundary and enter the next cell
    d_internal_ray.advanceToIntersectionSurface(
                                             d_internal_ray.getCurrentCell() );

    double local_surface_normal[3];

    this->getSurfaceHandleNormal( intersection_surface,
                                  d_internal_ray.getPosition(),
                                  d_internal_ray.getDirection(),
                                  local_surface_normal,
                                  &d_internal_ray.getHistory() );

    if( surface_normal != NULL )
    {
      surface_normal[0] = local_surface_normal[0];
      surface_normal[1] = local_surface_normal[1];
      surface_normal[2] = local_surface_normal[2];
    }

    double reflected_direction[3];

    Utility::reflectUnitVector( d_internal_ray.getDirection(),
                                local_surface_normal,
                                reflected_direction );

    // This will also fire a ray to fill the new intersection data
    this->changeInternalRayDirection( reflected_direction[0],
                                      reflected_direction[1],
                                      reflected_direction[2] );

    reflecting_boundary = true;
  }
  // Pass into the next cell if a normal surface is encountered
  else
  {
    moab::EntityHandle next_cell_handle =
      this->getBoundaryCellHandle( d_internal_ray.getCurrentCell(),
                                   d_internal_ray.getIntersectionSurface() );

    d_internal_ray.advanceToIntersectionSurface( next_cell_handle );

    if( surface_normal != NULL )
    {
      this->getSurfaceHandleNormal( intersection_surface,
                                    d_internal_ray.getPosition(),
                                    d_internal_ray.getDirection(),
                                    surface_normal,
                                    &d_internal_ray.getHistory() );
    }
  }

  // Fire the ray so that the new intersection data is set
  Navigator::fireInternalRay();

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
                    d_internal_ray.getDistanceToIntersectionSurface());
  
  d_internal_ray.advanceSubstep( substep_distance );
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

  // Change the direction
  d_internal_ray.changeDirection( x_direction, y_direction, z_direction );

  // Fire the ray so that the new intersection data is set
  Navigator::fireInternalRay();
}

// Check if the surface handle is a reflecting surface
bool DagMCNavigator::isReflectingSurfaceHandle(
                                const moab::EntityHandle surface_handle ) const
{
  return d_reflecting_surfaces->right.find( surface_handle ) !=
    d_reflecting_surfaces->right.end();
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

// Find the cell handle that contains the ray
moab::EntityHandle DagMCNavigator::findCellHandleContainingRay(
                                           const double position[3],
                                           const double direction[3],
                                           const bool check_on_boundary ) const
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
                             "  Position: "
                             << this->arrayToString( position ) << "\n"
                             "  Direction: "
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

    double distance_to_boundary = this->fireRayWithCellHandle(
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

  return cell_handle;
}

// Find the cell handle that contains the ray
moab::EntityHandle DagMCNavigator::findCellHandleContainingRay(
                                           const double x_position,
                                           const double y_position,
                                           const double z_position,
                                           const double x_direction,
                                           const double y_direction,
                                           const double z_direction,
                                           const bool check_on_boundary ) const
{
  // Create position and direction arrays
  const double position[3] = {x_position, y_position, z_position};
  const double direction[3] = {x_direction, y_direction, z_direction};

  return this->findCellHandleContainingRay( position,
                                            direction,
                                            check_on_boundary );
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
                                                    history );
  
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
                   << d_cell_handler->getCellId( current_cell_handle ) << "\n"
                   "  Position: "
                   << this->arrayToString( position ) << "\n"
                   "  Direction: "
                   << this->arrayToString( direction ) );

  TEST_FOR_EXCEPTION(
               distance_to_surface < 0.0,
               DagMCGeometryError,
               "DagMC had a ray misfire! Here are the details...\n"
               "  Current Cell: "
               << d_cell_handler->getCellId( current_cell_handle ) << "\n"
               "  Surface Hit: "
               << d_surface_handler->getSurfaceId( surface_hit_handle ) << "\n"
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
  
  // Set the basic ray info
  d_internal_ray.set( x_position, y_position, z_position,
                      x_direction, y_direction, z_direction,
                      current_cell_handle );

  // Fire the ray so that the intersection data is set
  Navigator::fireInternalRay();
}
  
} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_DagMCNavigator.cpp
//---------------------------------------------------------------------------//
