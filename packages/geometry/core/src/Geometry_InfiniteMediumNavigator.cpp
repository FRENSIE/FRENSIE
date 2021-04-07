//---------------------------------------------------------------------------//
//!
//! \file   Geometry_InfiniteMediumNavigator.cpp
//! \author Alex Robinson
//! \brief  The infinite medium navigator class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "Geometry_InfiniteMediumNavigator.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_DesignByContract.hpp"

namespace Geometry{

// Default constructor
InfiniteMediumNavigator::InfiniteMediumNavigator()
  : InfiniteMediumNavigator( Geometry::Navigator::invalidCellId() )
{ /* ... */ }

// Constructor
InfiniteMediumNavigator::InfiniteMediumNavigator(
          const EntityId infinite_medium_cell_id,
          const Navigator::AdvanceCompleteCallback& advance_complete_callback )
  : Navigator( advance_complete_callback ),
    d_cell( infinite_medium_cell_id ),
    d_position( new Length[3] ),
    d_direction( new double[3] )
{
  d_position[0] = 0.0*boost::units::cgs::centimeter;
  d_position[1] = 0.0*boost::units::cgs::centimeter;;
  d_position[2] = 0.0*boost::units::cgs::centimeter;;

  d_direction[0] = 0.0;
  d_direction[1] = 0.0;
  d_direction[2] = 1.0;
}

// Copy constructor
/*! \details This constructor should only be used within the clone method. The
 * Navigator::AdvanceCompleteCallback will also be copied
 */
InfiniteMediumNavigator::InfiniteMediumNavigator(
                                         const InfiniteMediumNavigator& other )
  : Navigator( other ),
    d_cell( other.d_cell ),
    d_position( new Length[3] ),
    d_direction( new double[3] )
{
  d_position[0] = other.d_position[0];
  d_position[1] = other.d_position[1];
  d_position[2] = other.d_position[2];

  d_direction[0] = other.d_direction[0];
  d_direction[1] = other.d_direction[1];
  d_direction[2] = other.d_direction[2];
}

// Destructor
InfiniteMediumNavigator::~InfiniteMediumNavigator()
{
  delete[] d_position;
  delete[] d_direction;
}

// Get the location of a point w.r.t. a given cell
PointLocation InfiniteMediumNavigator::getPointLocation(
                                          const Length*,
                                          const double*,
                                          const EntityId cell ) const
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
void InfiniteMediumNavigator::getSurfaceNormal( const EntityId,
                                                const Length*,
                                                const double*,
                                                double normal[3] ) const
{
  normal[0] = 0.0;
  normal[1] = 0.0;
  normal[2] = 1.0;
}

// Find the cell that contains a given ray
auto InfiniteMediumNavigator::findCellContainingRay(
                      const Length*,
                      const double*,
                      CellIdSet& found_cell_cache ) const -> EntityId
{
  found_cell_cache.insert( d_cell );

  return d_cell;
}

// Find the cell that contains a given ray
auto InfiniteMediumNavigator::findCellContainingRay(
                                    const Length*,
                                    const double* ) const -> EntityId
{
  return d_cell;
}

// Check if an internal ray has been set
bool InfiniteMediumNavigator::isStateSet() const
{
  return true;
}

// Set the internal ray with unknown starting cell
void InfiniteMediumNavigator::setState( const Length x_position,
                                        const Length y_position,
                                        const Length z_position,
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
void InfiniteMediumNavigator::setState( const Length x_position,
                                        const Length y_position,
                                        const Length z_position,
                                        const double x_direction,
                                        const double y_direction,
                                        const double z_direction,
                                        const EntityId )
{
  this->setState( x_position, y_position, z_position,
                        x_direction, y_direction, z_direction );
}

// Get the internal ray position
auto InfiniteMediumNavigator::getPosition() const -> const Length*
{
  return d_position;
}

// Get the internal ray direction
const double* InfiniteMediumNavigator::getDirection() const
{
  return d_direction;
}

// Get the cell that contains the internal ray
auto InfiniteMediumNavigator::getCurrentCell() const -> EntityId
{
  return d_cell;
}

// Get the distance from the internal DagMC ray pos. to the nearest boundary in all directions
//! \details An infinite medium has no surface.
auto InfiniteMediumNavigator::getDistanceToClosestBoundary() -> Length
{
  return Utility::QuantityTraits<Length>::inf();
}

// Fire the internal ray through the geometry
/*! \details An infinite medium has no surface. The surface hit will be set
 * to the invalid surface.
 */
auto InfiniteMediumNavigator::fireRay(
                                 EntityId* surface_hit ) -> Length
{
  if( surface_hit != NULL )
    *surface_hit = Navigator::invalidSurfaceId();

  return Utility::QuantityTraits<Length>::inf();
}

// Advance the internal ray to the cell boundary
/*! \details Calling this method will invalidate the current navigator state
 * (the position will be at infinity). An infinite medium has no surface so
 * the surface normal will always be set to the internal ray direction.
 */
bool InfiniteMediumNavigator::advanceToCellBoundaryImpl( double* surface_normal,
                                                         Length& distance_traveled )
{
  // Move the ray position to infinity
  d_position[0] = Utility::QuantityTraits<Length>::inf();
  d_position[1] = d_position[0];
  d_position[2] = d_position[0];

  // Set the surface normal
  if( surface_normal != NULL )
  {
    surface_normal[0] = d_direction[0];
    surface_normal[1] = d_direction[1];
    surface_normal[2] = d_direction[2];
  }

  // The distance traveled is infinite
  distance_traveled = Utility::QuantityTraits<Length>::inf();

  // There are no reflecting surface
  return false;
}

// Advance the internal ray by a substep (less than distance to boundary)
void InfiniteMediumNavigator::advanceBySubstepImpl( const Length step_size )
{
  d_position[0] += d_direction[0]*step_size;
  d_position[1] += d_direction[1]*step_size;
  d_position[2] += d_direction[2]*step_size;
}

// Change the internal ray direction
void InfiniteMediumNavigator::changeDirection( const double x_direction,
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
InfiniteMediumNavigator* InfiniteMediumNavigator::clone(
               const AdvanceCompleteCallback& advance_complete_callback ) const
{
  InfiniteMediumNavigator* cloned_navigator =
    new InfiniteMediumNavigator( this->getCurrentCell(),
                                 advance_complete_callback );

  cloned_navigator->setState( this->getPosition(), this->getDirection() );

  return cloned_navigator;
}

// Clone the navigator
InfiniteMediumNavigator* InfiniteMediumNavigator::clone() const
{
  return new InfiniteMediumNavigator( *this );
}

// // Save the model to an archive
// template<typename Archive>
// void InfiniteMediumNavigator::save( Archive& ar, const unsigned version ) const
// {
//   // Save the base class first
//   ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( Navigator );

//   // Save the local member data
//   ar & BOOST_SERIALIZATION_NVP( d_cell );

//   ar & boost::serialization::make_nvp( "d_position", boost::serialization::make_array<Length>( d_position, 3 ) );
//   ar & boost::serialization::make_nvp( "d_direction", boost::serialization::make_array<double>( d_direction, 3 ) );
// }

// // Load the model from an archive
// template<typename Archive>
// void InfiniteMediumNavigator::load( Archive& ar, const unsigned version )
// {
//   // Load the base class first
//   ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( Navigator );

//   // Load the local member data
//   ar & BOOST_SERIALIZATION_NVP( d_cell );

//   // The position array should always be initialized - this check is added
//   // for extra safety
//   if( !d_position )
//     d_position = new Length[3];

//   ar & boost::serialization::make_nvp( "d_position", boost::serialization::make_array<Length>( d_position, 3 ) );

//   // The direction array should always be initialized - this check is added
//   // for extra safety
//   if( !d_direction )
//     d_direction = new double[3];

//   ar & boost::serialization::make_nvp( "d_direction", boost::serialization::make_array<double>( d_direction, 3 ) );
// }
} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_InfiniteMediumNavigator.cpp
//---------------------------------------------------------------------------//
