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
#include "Geometry_DagMCModel.hpp"
#include "Utility_OpenMPProperties.hpp"
#include "Utility_MOABException.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace Geometry{

// Initialize static member data
const double DagMCNavigator::s_boundary_tol = 1e-5;

// Default constructor
DagMCNavigator::DagMCNavigator()
{ /* ... */ }

// Constructor
DagMCNavigator::DagMCNavigator(
          const std::shared_ptr<const DagMCModel>& dagmc_model,
          const Navigator::AdvanceCompleteCallback& advance_complete_callback )
  : Navigator( advance_complete_callback ),
    d_dagmc_model( dagmc_model ),
    d_internal_ray()
{
  // Make sure that the dagmc instance is valid
  testPrecondition( dagmc_model.get() );
}

// Copy constructor
/*! \details This constructor should only be used by the clone method.
 */
DagMCNavigator::DagMCNavigator( const DagMCNavigator& other )
  : Navigator( other ),
    d_dagmc_model( other.d_dagmc_model ),
    d_internal_ray( other.d_internal_ray )
{ /* ... */ }

// Get the point location w.r.t. a given cell
/*! \details This function will only return if a point is inside of or
 * outside of the cell of interest (not on the cell). The ray direction will be
 * used when it is close to the surface.
 */
PointLocation DagMCNavigator::getPointLocation(
                                       const Length position[3],
                                       const double direction[3],
                                       const EntityId cell_id ) const
{
  // Make sure that the cell exists
  testPrecondition( d_dagmc_model->getCellHandler().doesCellExist( cell_id ) );

  moab::EntityHandle cell_handle = d_dagmc_model->getCellHandler().getCellHandle( cell_id );

  try{
    return this->getPointLocationWithCellHandle( position,
                                                 direction,
                                                 cell_handle );
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
void DagMCNavigator::getSurfaceNormal( const EntityId surface_id,
                                       const Length position[3],
                                       const double direction[3],
                                       double normal[3] ) const
{
  // Make sure that the surface exists
  testPrecondition( d_dagmc_model->getSurfaceHandler().doesSurfaceExist( surface_id ) );

  moab::EntityHandle surface_handle =
    d_dagmc_model->getSurfaceHandler().getSurfaceHandle( surface_id );

  this->getSurfaceHandleNormal( surface_handle, position, direction, normal );
}

// Get the surface normal at a point on the surface
void DagMCNavigator::getSurfaceHandleNormal(
                                 const moab::EntityHandle surface_handle,
                                 const Length position[3],
                                 const double direction[3],
                                 double normal[3],
                                 const moab::DagMC::RayHistory* history ) const
{
  moab::ErrorCode return_value =
    d_dagmc_model->getRawDagMCInstance().get_angle( surface_handle,
                                                    Utility::reinterpretAsRaw(position),
                                                    normal,
                                                    history );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      DagMCGeometryError,
                      moab::ErrorCodeStr[return_value] );
}

// Get the boundary cell
/*! \details DagMC geometries are set up so that every surface belongs to
 * exactly two cells. When a ray crosses a boundary surface finding the
 * next cell that will be entered is simply a matter of knowing the current
 * cell and the boundary surface.
 */
auto DagMCNavigator::getBoundaryCell(
  const EntityId cell_id,
  const EntityId boundary_surface_id ) const -> EntityId
{
  // Make sure that the cell exists
  testPrecondition( d_dagmc_model->getCellHandler().doesCellExist( cell_id ) );
  // Make sure that the surface exists
  testPrecondition( d_dagmc_model->getSurfaceHandler().doesSurfaceExist( boundary_surface_id ) );

  moab::EntityHandle current_cell_handle =
    d_dagmc_model->getCellHandler().getCellHandle( cell_id );

  moab::EntityHandle boundary_surface_handle =
    d_dagmc_model->getSurfaceHandler().getSurfaceHandle( boundary_surface_id );

  moab::EntityHandle boundary_cell_handle =
    this->getBoundaryCellHandle( current_cell_handle,
                                 boundary_surface_handle );

  return d_dagmc_model->getCellHandler().getCellId( boundary_cell_handle );
}

// Find the cell that contains a given ray
auto DagMCNavigator::findCellContainingRay( const Length position[3],
                                            const double direction[3],
                                            CellIdSet& found_cell_cache ) const
  -> EntityId
{
  // Test the cells in the cache first
  CellIdSet::const_iterator cell_cache_it, cell_cache_end;
  cell_cache_it = found_cell_cache.begin();
  cell_cache_end = found_cell_cache.end();

  while( cell_cache_it != cell_cache_end )
  {
    PointLocation test_point_location =
      this->getPointLocation( position, direction, *cell_cache_it );

    if( test_point_location == POINT_INSIDE_CELL )
      return *cell_cache_it;

    ++cell_cache_it;
  }

  // Check all other cells
  EntityId found_cell =
    this->findCellContainingRay( position, direction );

  // Add the new cell to the cache
  found_cell_cache.insert( found_cell );

  return found_cell;
}

// Find the cell that contains the ray
auto DagMCNavigator::findCellContainingRay( const Length position[3],
                                            const double direction[3] ) const
  -> EntityId
{
  moab::EntityHandle cell_handle =
    this->findCellHandleContainingRay( position, direction );

  return d_dagmc_model->getCellHandler().getCellId( cell_handle );
}

// Check if the internal ray is set
bool DagMCNavigator::isStateSet() const
{
  return d_internal_ray.isReady();
}

// Initialize (or reset) an internal DagMC ray
void DagMCNavigator::setState( const Length x_position,
                               const Length y_position,
                               const Length z_position,
                               const double x_direction,
                               const double y_direction,
                               const double z_direction )
{
  // Make sure that the direction is valid
  testPrecondition( Utility::isUnitVector( x_direction, y_direction, z_direction ) );

  moab::EntityHandle cell_handle =
    this->findCellHandleContainingRay( x_position, y_position, z_position,
                                       x_direction, y_direction, z_direction );

  this->setStateWithCellHandle( x_position, y_position, z_position,
                                x_direction, y_direction, z_direction,
                                cell_handle );
}

// Initialize (or reset) an internal DagMC ray
void DagMCNavigator::setState( const Length x_position,
                               const Length y_position,
                               const Length z_position,
                               const double x_direction,
                               const double y_direction,
                               const double z_direction,
                               const EntityId current_cell )
{
  // Make sure that the direction is valid
  testPrecondition( Utility::isUnitVector( x_direction, y_direction, z_direction ) );
  // Make sure that the cell exists
  testPrecondition( d_dagmc_model->getCellHandler().doesCellExist( current_cell ) );
  // Make sure that the cell contains the ray
  remember( moab::EntityHandle test_cell_handle =
            this->findCellHandleContainingRay(
                                        x_position, y_position, z_position,
                                        x_direction, y_direction, z_direction,
                                        false ) );
  testPrecondition( d_dagmc_model->getCellHandler().getCellId( test_cell_handle ) ==
                    current_cell );

  moab::EntityHandle cell_handle =
    d_dagmc_model->getCellHandler().getCellHandle( current_cell );

  this->setStateWithCellHandle( x_position, y_position, z_position,
                                x_direction, y_direction, z_direction,
                                cell_handle );
}

// Get the internal DagMC ray position
auto DagMCNavigator::getPosition() const -> const Length*
{
  // Make sure that the ray is set
  testPrecondition( this->isStateSet() );

  return Utility::reinterpretAsQuantity<Length>(d_internal_ray.getPosition());
}

// Get the internal DagMC ray direction
const double* DagMCNavigator::getDirection() const
{
  // Make sure that the ray is set
  testPrecondition( this->isStateSet() );

  return d_internal_ray.getDirection();
}

// Get the cell containing the internal DagMC ray position
auto DagMCNavigator::getCurrentCell() const -> EntityId
{
  // Make sure that the ray is set
  testPrecondition( this->isStateSet() );

  return d_dagmc_model->getCellHandler().getCellId( d_internal_ray.getCurrentCell() );
}

// Get the distance from the internal DagMC ray pos. to the nearest boundary in all directions
auto DagMCNavigator::getDistanceToClosestBoundary() -> Length
{
  // Make sure that the ray is set
  testPrecondition( this->isStateSet() );

  moab::EntityHandle surface_hit_handle;

  double raw_distance_to_surface;

  moab::ErrorCode return_value =
    d_dagmc_model->getRawDagMCInstance().closest_to_location(
      d_internal_ray.getCurrentCell(),
      d_internal_ray.getPosition(),
      raw_distance_to_surface );

  // Check for a ray misfire which can be caused by a poorly created geometry
  // or by gaps in the surface facets, which can occur for properly created
  // geometries.
  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      DagMCGeometryError,
                      moab::ErrorCodeStr[return_value] );

  TEST_FOR_EXCEPTION(
               raw_distance_to_surface < 0.0,
               DagMCGeometryError,
               "DagMC had a ray closest boundary misfire! Here are the details...\n"
               "  Current Cell: "
               << d_internal_ray.getCurrentCell() << "\n"
               "  Position: "
               << this->arrayToString( d_internal_ray.getPosition() ) );

  return Length::from_value(raw_distance_to_surface);
}

// Get the distance from the internal DagMC ray pos. to the nearest boundary
auto DagMCNavigator::fireRay( EntityId* surface_hit ) -> Length
{
  // Make sure that the ray is set
  testPrecondition( this->isStateSet() );

  Length distance_to_surface;

  // Check if the ray has already been fired
  if( d_internal_ray.knowsIntersectionSurface() )
  {
    if( surface_hit != NULL )
    {
      *surface_hit = d_dagmc_model->getSurfaceHandler().getSurfaceId(
                                     d_internal_ray.getIntersectionSurface() );
    }

    distance_to_surface =
      Length::from_value(d_internal_ray.getDistanceToIntersectionSurface());
  }
  else
  {
    moab::EntityHandle surface_hit_handle;

    distance_to_surface = this->fireRayWithCellHandle(
          Utility::reinterpretAsQuantity<Length>(d_internal_ray.getPosition()),
          d_internal_ray.getDirection(),
          d_internal_ray.getCurrentCell(),
          surface_hit_handle,
          &d_internal_ray.getHistory() );

    if( surface_hit != NULL )
      *surface_hit = d_dagmc_model->getSurfaceHandler().getSurfaceId( surface_hit_handle );

    // Cache the surface data in the ray
    d_internal_ray.setIntersectionSurfaceData( surface_hit_handle,
                                               distance_to_surface.value() );
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
bool DagMCNavigator::advanceToCellBoundaryImpl( double* surface_normal,
                                                Length& distance_traveled )
{
  // Make sure that the ray is set
  testPrecondition( this->isStateSet() );
  // Make sure that the instersection surface is know
  testPrecondition( d_internal_ray.knowsIntersectionSurface() );

  bool reflecting_boundary = false;

  moab::EntityHandle intersection_surface =
    d_internal_ray.getIntersectionSurface();

  distance_traveled =
    Length::from_value( d_internal_ray.getDistanceToIntersectionSurface() );

  // Reflect the ray if a reflecting surface is encountered
  if( this->isReflectingSurfaceHandle(d_internal_ray.getIntersectionSurface()))
  {
    // Advance the ray to the cell boundary and enter the next cell
    d_internal_ray.advanceToIntersectionSurface(
                                             d_internal_ray.getCurrentCell() );

    double local_surface_normal[3];

    this->getSurfaceHandleNormal( intersection_surface,
                                  Utility::reinterpretAsQuantity<Length>(d_internal_ray.getPosition()),
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
    this->changeDirection( reflected_direction[0],
                           reflected_direction[1],
                           reflected_direction[2],
                           true );

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
                                    Utility::reinterpretAsQuantity<Length>(d_internal_ray.getPosition()),
                                    d_internal_ray.getDirection(),
                                    surface_normal,
                                    &d_internal_ray.getHistory() );
    }
  }

  // Fire the ray so that the new intersection data is set
  Navigator::fireRay();

  return reflecting_boundary;
}

// Advance the internal DagMC ray a substep
/*! \details The substep distance must be less than the distance to the
 * intersection surface.
 */
void DagMCNavigator::advanceBySubstepImpl( const Length substep_distance )
{
  // Make sure that the ray is set
  testPrecondition( this->isStateSet() );
  // Make sure that the substep distance is valid
  testPrecondition( substep_distance.value() >= 0.0 );
  testPrecondition( substep_distance.value() <
                    d_internal_ray.getDistanceToIntersectionSurface());

  d_internal_ray.advanceSubstep( substep_distance.value() );
}

// Change the internal ray direction (without changing its location)
void DagMCNavigator::changeDirection( const double x_direction,
                                      const double y_direction,
                                      const double z_direction )
{
  this->changeDirection( x_direction, y_direction, z_direction, false );
}

// Change the direction of the ray
void DagMCNavigator::changeDirection( const double x_direction,
                                      const double y_direction,
                                      const double z_direction,
                                      const bool reflection )
{
  // Make sure that the ray is set
  testPrecondition( this->isStateSet() );
  // Make sure that the direction is valid
  testPrecondition( Utility::isUnitVector( x_direction, y_direction, z_direction ) );

  // Change the direction
  d_internal_ray.changeDirection( x_direction,
                                  y_direction,
                                  z_direction,
                                  reflection );

  // Fire the ray so that the new intersection data is set
  Navigator::fireRay();
}

// Check if the surface handle is a reflecting surface
bool DagMCNavigator::isReflectingSurfaceHandle(
                                const moab::EntityHandle surface_handle ) const
{
  return d_dagmc_model->getReflectingSurfaceIdHandleMap().right.find( surface_handle ) !=
    d_dagmc_model->getReflectingSurfaceIdHandleMap().right.end();
}

// Get the point location w.r.t. a given cell
PointLocation DagMCNavigator::getPointLocationWithCellHandle(
                                 const Length position[3],
                                 const double direction[3],
                                 const moab::EntityHandle cell_handle,
                                 const moab::DagMC::RayHistory* history ) const
{
  // Make sure that the direction is valid
  testPrecondition( Utility::isUnitVector( direction ) );

  int test_result;

  moab::ErrorCode return_value =
    d_dagmc_model->getRawDagMCInstance().point_in_volume( cell_handle,
                                                          Utility::reinterpretAsRaw(position),
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

  moab::ErrorCode return_value =
    d_dagmc_model->getRawDagMCInstance().next_vol( boundary_surface_handle,
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
               << d_dagmc_model->getCellHandler().getCellId( cell_handle ) << "\n"
               "  Boundary Surface: "
               << d_dagmc_model->getSurfaceHandler().getSurfaceId( boundary_surface_handle ) );

  return boundary_cell_handle;
}

// Find the cell handle that contains the ray
moab::EntityHandle DagMCNavigator::findCellHandleContainingRay(
                                           const Length position[3],
                                           const double direction[3],
                                           const bool check_on_boundary ) const
{
  // Make sure that the direction is valid
  testPrecondition( Utility::isUnitVector( direction ) );

  moab::EntityHandle cell_handle = 0;

  // Test all of the cells
  moab::Range::const_iterator cell_handle_it = d_dagmc_model->getCellHandler().begin();

  while( cell_handle_it != d_dagmc_model->getCellHandler().end() )
  {
    PointLocation test_point_location;

    try{
      test_point_location =
        this->getPointLocationWithCellHandle( position,
                                              direction,
                                              *cell_handle_it );
    }
    EXCEPTION_CATCH_RETHROW( DagMCGeometryError,
                             "Could not find the location of the ray with "
                             "respect to cell "
                             << d_dagmc_model->getCellHandler().getCellId( *cell_handle_it ) <<
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

    Length distance_to_boundary = this->fireRayWithCellHandle(
                                                          position,
                                                          direction,
                                                          cell_handle,
                                                          surface_hit_handle );

    // Return the next cell instead
    if( distance_to_boundary.value() < s_boundary_tol )
    {
      cell_handle = this->getBoundaryCellHandle( cell_handle,
                                                 surface_hit_handle );
    }
  }

  return cell_handle;
}

// Find the cell handle that contains the ray
moab::EntityHandle DagMCNavigator::findCellHandleContainingRay(
                                           const Length x_position,
                                           const Length y_position,
                                           const Length z_position,
                                           const double x_direction,
                                           const double y_direction,
                                           const double z_direction,
                                           const bool check_on_boundary ) const
{
  // Create position and direction arrays
  const Length position[3] = {x_position, y_position, z_position};
  const double direction[3] = {x_direction, y_direction, z_direction};

  return this->findCellHandleContainingRay( position,
                                            direction,
                                            check_on_boundary );
}

// Get the distance from the ray position to the nearest boundary
auto DagMCNavigator::fireRayWithCellHandle(
                             const Length position[3],
                             const double direction[3],
                             const moab::EntityHandle current_cell_handle,
                             moab::EntityHandle& surface_hit_handle,
                             moab::DagMC::RayHistory* history ) const -> Length
{
  // Make sure that the direction is valid
  testPrecondition( Utility::isUnitVector( direction ) );

  double raw_distance_to_surface;

  moab::ErrorCode return_value =
    d_dagmc_model->getRawDagMCInstance().ray_fire( current_cell_handle,
                                                   Utility::reinterpretAsRaw(position),
                                                   direction,
                                                   surface_hit_handle,
                                                   raw_distance_to_surface,
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
                   << d_dagmc_model->getCellHandler().getCellId( current_cell_handle ) << "\n"
                   "  Position: "
                   << this->arrayToString( position ) << "\n"
                   "  Direction: "
                   << this->arrayToString( direction ) );

  TEST_FOR_EXCEPTION(
               raw_distance_to_surface < 0.0,
               DagMCGeometryError,
               "DagMC had a ray misfire! Here are the details...\n"
               "  Current Cell: "
               << d_dagmc_model->getCellHandler().getCellId( current_cell_handle ) << "\n"
               "  Surface Hit: "
               << d_dagmc_model->getSurfaceHandler().getSurfaceId( surface_hit_handle ) << "\n"
               "  Position: "
               << this->arrayToString( position ) << "\n"
               "  Direction: "
               << this->arrayToString( direction ) );

  return Length::from_value(raw_distance_to_surface);
}

// Set an internal DagMC ray
void DagMCNavigator::setStateWithCellHandle(
                                 const Length x_position,
                                 const Length y_position,
                                 const Length z_position,
                                 const double x_direction,
                                 const double y_direction,
                                 const double z_direction,
                                 const moab::EntityHandle current_cell_handle )
{
  // Make sure that the direction is valid
  testPrecondition( Utility::isUnitVector( x_direction, y_direction, z_direction ) );

  // Set the basic ray info
  d_internal_ray.set( x_position.value(),
                      y_position.value(),
                      z_position.value(),
                      x_direction,
                      y_direction,
                      z_direction,
                      current_cell_handle );

  // Fire the ray so that the intersection data is set
  Navigator::fireRay();
}

//! Clone the navigator
DagMCNavigator* DagMCNavigator::clone( const AdvanceCompleteCallback& advance_complete_callback ) const
{
  // Copy the geometry data
  DagMCNavigator* clone = new DagMCNavigator( d_dagmc_model,
                                              advance_complete_callback );

  // Copy the current position and direction
  clone->setState( this->getPosition(),
                   this->getDirection(),
                   this->getCurrentCell() );

  return clone;
}

// Clone the navigator
DagMCNavigator* DagMCNavigator::clone() const
{
  return new DagMCNavigator( *this );
}

// // Save the model to an archive
// template<typename Archive>
// void DagMCNavigator::save( Archive& ar, const unsigned version ) const
// {
//   // Save the base class first
//   ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( Navigator );

//   // Save the local data
//   ar & BOOST_SERIALIZATION_NVP( d_dagmc_model );

//   const bool internal_ray_set = this->isStateSet();

//   ar & BOOST_SERIALIZATION_NVP( internal_ray_set );

//   if( internal_ray_set )
//   {
//     EntityId current_cell = this->getCurrentCell();

//     ar & BOOST_SERIALIZATION_NVP( current_cell );
//     ar & boost::serialization::make_nvp( "current_position", boost::serialization::make_array<double>( const_cast<double*>(Utility::reinterpretAsRaw(this->getPosition())), 3 ) );
//     ar & boost::serialization::make_nvp( "current_direction", boost::serialization::make_array<double>( const_cast<double*>(this->getDirection()), 3 ) );
//   }
// }

// // Load the model from an archive
// template<typename Archive>
// void DagMCNavigator::load( Archive& ar, const unsigned version )
// {
//   // Load the base class first
//   ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( Navigator );

//   // Load the local data
//   ar & BOOST_SERIALIZATION_NVP( d_dagmc_model );

//   bool internal_ray_set;

//   ar & BOOST_SERIALIZATION_NVP( internal_ray_set );

//   if( internal_ray_set )
//   {
//     EntityId current_cell;
//     Length current_position[3];
//     double current_direction[3];

//     ar & BOOST_SERIALIZATION_NVP( current_cell );
//     ar & boost::serialization::make_nvp( "current_position", boost::serialization::make_array<double>( Utility::reinterpretAsRaw(current_position), 3 ) );
//     ar & boost::serialization::make_nvp( "current_direction", boost::serialization::make_array<double>( current_direction, 3 ) );

//     dynamic_cast<Navigator*>(this)->setState( current_position, current_direction, current_cell );
//   }
// }

} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_DagMCNavigator.cpp
//---------------------------------------------------------------------------//
