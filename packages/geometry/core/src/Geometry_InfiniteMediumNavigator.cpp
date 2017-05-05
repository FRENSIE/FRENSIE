//---------------------------------------------------------------------------//
//!
//! \file   Geometry_InfiniteMediumNavigator.cpp
//! \author Alex Robinson
//! \brief  The infinite medium navigator class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Geometry_InfiniteMediumNavigator.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_ContractException.hpp"

namespace Geometry{

// Constructor
InfiniteMediumNavigator::InfiniteMediumNavigator(
               const ModuleTraits::InternalCellHandle infinite_medium_cell_id )
  : d_cell( infinite_medium_cell_id ),
    d_position( new double[3] ),
    d_direction( new double[3] )
{
  d_position[0] = 0.0;
  d_position[1] = 0.0;
  d_position[2] = 0.0;

  d_direction[0] = 0.0;
  d_direction[1] = 0.0;
  d_direction[2] = 1.0;
}

// Destructor
InfiniteMediumNavigator::~InfiniteMediumNavigator()
{
  delete[] d_position;
  delete[] d_direction;
}

// Get the location of a point w.r.t. a given cell
PointLocation InfiniteMediumNavigator::getPointLocation(
                            const double*,
                            const double*,
                            const ModuleTraits::InternalCellHandle cell ) const
{
  if( cell == d_cell )
    return POINT_INSIDE_CELL;
  else
    return POINT_OUTSIDE_CELL;
}
  
// Get the surface normal at a point on the surface
/*! \details An infinite medium has no surface. A normal of (0,0,1) will
 * always be returned.
 */
void InfiniteMediumNavigator::getSurfaceNormal(
                                     const ModuleTraits::InternalSurfaceHandle,
                                     const double*,
                                     const double*,
                                     double normal[3] ) const
{
  normal[0] = 0.0;
  normal[1] = 0.0;
  normal[2] = 1.0;
}

// Find the cell that contains a given ray
ModuleTraits::InternalCellHandle
InfiniteMediumNavigator::findCellContainingRay(
                                            const double*,
                                            const double*,
                                            CellIdSet& found_cell_cache ) const
{
  found_cell_cache.insert( d_cell );

  return d_cell;
}

// Find the cell that contains a given ray
ModuleTraits::InternalCellHandle
InfiniteMediumNavigator::findCellContainingRay( const double*,
                                                const double* ) const
{
  return d_cell;
}
  
// Check if an internal ray has been set
bool InfiniteMediumNavigator::isInternalRaySet() const
{
  return true;
}

// Set the internal ray with unknown starting cell
void InfiniteMediumNavigator::setInternalRay( const double x_position,
                                              const double y_position,
                                              const double z_position,
                                              const double x_direction,
                                              const double y_direction,
                                              const double z_direction )
{
  // Make sure that the direction is valid
  testPrecondition( Utility::isUnitVector( x_direction, y_direction, z_direction ) );

  d_position[0] = x_position;
  d_position[1] = y_position;
  d_position[2] = z_position;

  d_direction[0] = x_direction;
  d_direction[1] = y_direction;
  d_direction[2] = z_direction;
}

// Set the internal ray with known starting cell
void InfiniteMediumNavigator::setInternalRay(
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

// Get the internal ray position
const double* InfiniteMediumNavigator::getInternalRayPosition() const
{
  return d_position;
}

// Get the internal ray direction
const double* InfiniteMediumNavigator::getInternalRayDirection() const
{
  return d_direction;
}

// Get the cell that contains the internal ray
ModuleTraits::InternalCellHandle
InfiniteMediumNavigator::getCellContainingInternalRay() const
{
  return d_cell;
}

// Fire the internal ray through the geometry
/*! \details An infinite medium has no surface. The surface hit will be set
 * to the invalid surface.
 */
double InfiniteMediumNavigator::fireInternalRay(
                             ModuleTraits::InternalSurfaceHandle* surface_hit )
{
  if( surface_hit != NULL )
    *surface_hit = ModuleTraits::invalid_internal_surface_handle;

  return std::numeric_limits<double>::infinity();
}

// Advance the internal ray to the cell boundary
/*! \details Calling this method will invalidate the current navigator state
 * (the position will be at infinity). An infinite medium has no surface so
 * the surface normal will always be set to the internal ray direction.
 */
bool InfiniteMediumNavigator::advanceInternalRayToCellBoundary(
                                                       double* surface_normal )
{
  // Move the ray position to infinity
  d_position[0] = std::numeric_limits<double>::infinity();
  d_position[1] = d_position[0];
  d_position[2] = d_position[0];

  // Set the surface normal
  if( surface_normal != NULL )
  {
    surface_normal[0] = d_direction[0];
    surface_normal[1] = d_direction[1];
    surface_normal[2] = d_direction[2];
  }

  // There are no reflecting surface
  return false;
}

// Advance the internal ray by a substep (less than distance to boundary)
void InfiniteMediumNavigator::advanceInternalRayBySubstep(
                                                       const double step_size )
{
  d_position[0] += d_direction[0]*step_size;
  d_position[1] += d_direction[1]*step_size;
  d_position[2] += d_direction[2]*step_size;
}

// Change the internal ray direction
void InfiniteMediumNavigator::changeInternalRayDirection(
                                                     const double x_direction,
                                                     const double y_direction,
                                                     const double z_direction )
{
  // Make sure that the direction is valid
  testPrecondition( Utility::isUnitVector( x_direction, y_direction, z_direction ) );

  d_direction[0] = x_direction;
  d_direction[1] = y_direction;
  d_direction[2] = z_direction;
}

// Clone the navigator
InfiniteMediumNavigator* InfiniteMediumNavigator::clone() const
{
  InfiniteMediumNavigator* clone = new InfiniteMediumNavigator( d_cell );

  dynamic_cast<Navigator*>( clone )->setInternalRay(
                                             this->getInternalRayPosition(),
                                             this->getInternalRayDirection() );
  return clone;
}
  
} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_InfiniteMediumNavigator.cpp
//---------------------------------------------------------------------------//
