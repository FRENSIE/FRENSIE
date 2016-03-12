//---------------------------------------------------------------------------//
//!
//! \file   Geometry_DagMCRay.cpp
//! \author Alex Robinson
//! \brief  The DagMC ray definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Geometry_DagMCRay.hpp"
#include "Utility_DirectionHelpers.hpp"
#include "Utility_ContractException.hpp"

namespace Geometry{

// Constructor
DagMCRay::DagMCRay()
  : d_basic_ray(),
    d_cell_handle( 0 ),
    d_history(),
    d_intersection_distance( -1.0 ),
    d_intersection_surface_handle( 0 )
{ /* ... */ }

// Constructor
DagMCRay::DagMCRay( const Ray& ray, moab::EntityHandle cell_handle )
  : d_basic_ray.reset( new Ray( ray.getPosition(), ray.getDirection() ) ),
    d_cell_handle( cell_handle ),
    d_history(),
    d_intersection_distance( -1.0 ),
    d_intersection_surface_handle( 0 )
{ 
  // Make sure the cell handle is valid
  testPrecondition( cell_handle != 0 );
}
  
// Check if the ray is ready (basic ray, current cell handle set)
bool DagMCRay::isReady() const
{
  return (d_basic_ray.get() != NULL) && (d_cell_handle != 0);
}

// Set the ray (minimum data required)
/*! \details The history will be cleared.
 */
void DagMCRay::set( const Ray& ray, const moab::EntityHandle cell_handle )
{
  // Make sure the cell is valid
  testPrecondition( cell_handle != 0 );
  
  this->set( ray.getPosition(), ray.getDirection(), cell_handle );
}

// Set the ray (minimum data required)
/*! \details All other data will be cleared.
 */
void DagMCRay::set( const double position[3], 
                    const double direction[3],
                    const moab::EntityHandle cell_handle )
{
  // Make sure the direction is valid
  testPrecondition( Utility::validDirection( direction ) );
  // Make sure the cell is valid
  testPrecondition( cell_handle != 0 );
  
  // Set the basic ray
  d_basic_ray.reset( new Ray( position, direction ) );

  // Set the cell handle
  d_cell_handle = cell_handle;

  // Reset the extra data
  d_history.reset();
  d_intersection_distance = -1.0;
  d_intersection_surface_handle = 0;  
}

// Change the direction
/*! \details This method will reset the history.
 */
void DagMCRay::changeDirection( const double direction[3] )
{
  // Make sure the ray is ready
  testPrecondition( this->isReady() );
  
  d_basic_ray->changeDirection( direction );

  d_history.reset();
}

// Get the position
const double* DagMCRay::getPosition() const
{
  // Make sure the ray is ready
  testPrecondition( this->isReady() );
  
  return d_basic_ray->getPosition();
}

// Get the direction
const double* DagMCRay::getDirection() const
{
  // Make sure the ray is ready
  testPrecondition( this->isReady() );
  
  return d_basic_ray->getDirection();
}

// Get the current cell handle
moab::EntityHandle DagMCRay::getCurrentCell() const
{
  // Make sure the ray is ready
  testPrecondition( this->isReady() );
  
  return d_cell_handle;
}

// Check if the ray knows the surface it will hit
bool DagMCRay::knowsIntersectionSurface() const
{
  return d_intersection_surface_handle != 0;
}

// Get the distance to the next surface 
double DagMCRay::getDistanceToIntersectionSurface() const
{
  // Make sure the intersection surface has been set
  testPrecondition( this->knowsIntersectionSurface() );

  return d_intersection_distance;
}

// Get the intersection surface handle 
moab::EntityHandle DagMCRay::getIntersectionSurface() const
{
  // Make sure the intersection surface has been set
  testPrecondition( this->knowsIntersectionSurface() );

  return d_intersection_surface_handle;
}

// Set the intersection surface handle
void DagMCRay::setIntersectionSurfaceData( 
                                       const moab::EntityHandle surface_handle,
                                       const double distance ) const
{
  // Make sure the surface handle is valid
  testPrecondition( surface_handle != 0 );
  // Make sure the distance is valid
  testPrecondition( distance >= 0.0 );
  
  d_intersection_surface_handle = surface_handle;
  
  d_intersection_distance = distance;
}

// Rest the intersection surface data
void DagMCRay::resetIntersectionSurfaceData()
{
  d_intersection_surface_handle = 0;
  
  d_intersection_distance = -1.0;
}

// Get the ray history
const moab::DagMC::RayHistory& DagMCRay::getHistory() const
{
  return d_history;
}

// Get the ray history
moab::DagMC::RayHistory& DagMCRay::getHistory()
{
  return d_history;
}

// Advance the ray to the intersection surface
/*! \details This method will reset the intersection data.
 */
void DagMCRay::advanceToIntersectionSurface( 
                               const moab::EntityHandle next_cell_handle) const
{
  // Make sure the next cell is valid
  testPrecondition( next_cell_handle != 0 );
  
  // Advance the basic ray to the surface
  d_basic_ray->advanceHead( d_intersection_distance );

  // Reset the intersection data
  d_intersection_distance = -1.0;
  d_intersection_surface_handle = 0;
}

// Advance the ray a substep
/*! \details This method should only be used to move the ray a distance
 * that is less than the intersection distance.
 */
void DagMCRay::advanceSubstep( const double substep_distance ) const
{
  // Make sure the substep is less than the intersection distance
  testPrecondition( substep_distance < d_intersection_distance );

  // Advance the basic ray the substep distance
  d_basic_ray->advanceHead( substep_distance );

  // Update the intersection distance
  d_intersection_distance -= substep_distance;
}

} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_DagMCRay.hpp
//---------------------------------------------------------------------------//
