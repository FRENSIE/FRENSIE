//---------------------------------------------------------------------------//
//!
//! \file   Geometry_IntersectionPoint_def.hpp
//! \author Alex Robinson
//! \file   IntersectionPoint class definition.
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_INTERSECTION_POINT_DEF_HPP
#define GEOMETRY_INTERSECTION_POINT_DEF_HPP

// Trilinos Includes
#include <Teuchos_ArrayRCP.hpp>

namespace Geometry{

// Default constructor
template<typename OrdinalType, typename ScalarType>
IntersectionPoint<OrdinalType,ScalarType>::IntersectionPoint()

  : Utility::PrintableObject( "IntersectionPoint" ),
    ThreeSpaceObject( THREE_SPACE_VECTOR ),
    d_x( ST::nan() ),
    d_y( ST::nan() ),
    d_z( ST::nan() ),
    d_first_surface_id( OT::invalid() ),
    d_second_surface_id( OT::invalid() ),
    d_third_surface_id( OT::invalid() ),
    d_is_star_corner( false )
{ /* ... */ }

// General constructor
template<typename OrdinalType, typename ScalarType>
IntersectionPoint<OrdinalType,ScalarType>::IntersectionPoint(
					   const ScalarType x,
					   const ScalarType y,
					   const ScalarType z,
					   const OrdinalType first_surface_id,
		                           const OrdinalType second_surface_id,
				           const OrdinalType third_surface_id,
					   const bool is_star_corner )
  : Utility::PrintableObject( "IntersectionPoint" ),
    ThreeSpaceObject( THREE_SPACE_POINT ),
    d_x( x ),
    d_y( y ),
    d_z( z ),
    d_first_surface_id( first_surface_id ),
    d_second_surface_id( second_surface_id ),
    d_third_surface_id( third_surface_id ),
    d_is_star_corner( is_star_corner )
{
  // The coordinates of the intersection point must be valid
  testPrecondition( !ST::isnaninf( x ) );
  testPrecondition( !ST::isnaninf( y ) );
  testPrecondition( !ST::isnaninf( z ) );
  // The surface ids must be valid
  testPrecondition( first_surface_id >= OT::zero() );
  testPrecondition( first_surface_id != OT::invalid() );
  testPrecondition( second_surface_id >= OT::zero() );
  testPrecondition( second_surface_id != OT::invalid() );
  testPrecondition( third_surface_id >= OT::zero() );
  testPrecondition( third_surface_id != OT::invalid() );
  // All of the surface ids must be unique
  testPrecondition( first_surface_id != second_surface_id );
  testPrecondition( first_surface_id != third_surface_id );
  testPrecondition( second_surface_id != third_surface_id );
}

// Vector constructor
template<typename OrdinalType, typename ScalarType>
IntersectionPoint<OrdinalType,ScalarType>::IntersectionPoint(
			       const Vector<ScalarType> raw_intersection_point,
			       const OrdinalType first_surface_id,
			       const OrdinalType second_surface_id,
			       const OrdinalType third_surface_id,
			       const bool is_star_corner )
  : Utility::PrintableObject( "IntersectionPoint" ),
    ThreeSpaceObject( THREE_SPACE_POINT ),
    d_x( raw_intersection_point[0] ),
    d_y( raw_intersection_point[1] ),
    d_z( raw_intersection_point[2] ),
    d_first_surface_id( first_surface_id ),
    d_second_surface_id( second_surface_id ),
    d_third_surface_id( third_surface_id ),
    d_is_star_corner( is_star_corner )
{
  // The coordinates of the intersection point must be valid
  testPrecondition( !ST::isnaninf( d_x ) );
  testPrecondition( !ST::isnaninf( d_y ) );
  testPrecondition( !ST::isnaninf( d_z ) );
  // The surface ids must be valid
  testPrecondition( first_surface_id >= OT::zero() );
  testPrecondition( first_surface_id != OT::invalid() );
  testPrecondition( second_surface_id >= OT::zero() );
  testPrecondition( second_surface_id != OT::invalid() );
  testPrecondition( third_surface_id >= OT::zero() );
  testPrecondition( third_surface_id != OT::invalid() );
  // All of the surface ids must be unique
  testPrecondition( first_surface_id != second_surface_id );
  testPrecondition( first_surface_id != third_surface_id );
  testPrecondition( second_surface_id != third_surface_id );
}

// Copy constructor
template<typename OrdinalType, typename ScalarType>
IntersectionPoint<OrdinalType,ScalarType>::IntersectionPoint(
	        const IntersectionPoint<OrdinalType,ScalarType> &source_point )
  : Utility::PrintableObject( "IntersectionPoint" ),
    ThreeSpaceObject( THREE_SPACE_POINT ),
    d_x( source_point.d_x ),
    d_y( source_point.d_y ),
    d_z( source_point.d_z ),
    d_first_surface_id( source_point.d_first_surface_id ),
    d_second_surface_id( source_point.d_second_surface_id ),
    d_third_surface_id( source_point.d_third_surface_id ),
    d_is_star_corner( source_point.d_is_star_corner )
{
  // The coordinates of the intersection point must be valid
  testPostcondition( !ST::isnaninf( d_x ) );
  testPostcondition( !ST::isnaninf( d_y ) );
  testPostcondition( !ST::isnaninf( d_z ) );
  // The surface ids must be valid
  testPostcondition( d_first_surface_id >= OT::zero() );
  testPostcondition( d_first_surface_id != OT::invalid() );
  testPostcondition( d_second_surface_id >= OT::zero() );
  testPostcondition( d_second_surface_id != OT::invalid() );
  testPostcondition( d_third_surface_id >= OT::zero() );
  testPostcondition( d_third_surface_id != OT::invalid() );
  // All of the surface ids must be unique
  testPostcondition( d_first_surface_id != d_second_surface_id );
  testPostcondition( d_first_surface_id != d_third_surface_id );
  testPostcondition( d_second_surface_id != d_third_surface_id );
}

// Copies values from one intersection point to another
template<typename OrdinalType, typename ScalarType>
IntersectionPoint<OrdinalType,ScalarType>&
IntersectionPoint<OrdinalType,ScalarType>::operator=(
	        const IntersectionPoint<OrdinalType,ScalarType> &source_point )
{
  // Test if the source point is the same as the target
  if( this != &source_point )
  {
    d_x = source_point.d_x;
    d_y = source_point.d_y;
    d_z = source_point.d_z;
    d_first_surface_id = source_point.d_first_surface_id;
    d_second_surface_id = source_point.d_second_surface_id;
    d_third_surface_id = source_point.d_third_surface_id;
    d_is_star_corner = source_point.d_is_star_corner;
  }

  // The coordinates of the intersection point must be valid
  testPostcondition( !ST::isnaninf( d_x ) );
  testPostcondition( !ST::isnaninf( d_y ) );
  testPostcondition( !ST::isnaninf( d_z ) );
  // The surface ids must be valid
  testPostcondition( d_first_surface_id >= OT::zero() );
  testPostcondition( d_first_surface_id != OT::invalid() );
  testPostcondition( d_second_surface_id >= OT::zero() );
  testPostcondition( d_second_surface_id != OT::invalid() );
  testPostcondition( d_third_surface_id >= OT::zero() );
  testPostcondition( d_third_surface_id != OT::invalid() );
  // All of the surface ids must be unique
  testPostcondition( d_first_surface_id != d_second_surface_id );
  testPostcondition( d_first_surface_id != d_third_surface_id );
  testPostcondition( d_second_surface_id != d_third_surface_id );

  return *this;
}

// Element access method (const.)
/*! \details Allows this class to be used in Point class templates, which
 * only require that this operator be defined.
 */
template<typename OrdinalType, typename ScalarType>
const ScalarType& IntersectionPoint<OrdinalType,ScalarType>::operator[](
						const ordinalType index ) const
{
  // Make sure that the index is valid
  testPrecondition( index >= 0 && index < 3 );

  switch( index )
  {
  case 0:
    return d_x;
  case 1:
    return d_y;
  case 2:
    return d_z;
  }
}

// Equality of two intersection points
template<typename OrdinalType, typename ScalarType>
bool IntersectionPoint<OrdinalType,ScalarType>::operator==(
	       const IntersectionPoint<OrdinalType,ScalarType> &operand ) const
{
  return d_x == operand.d_x &&
    d_y == operand.d_y &&
    d_z == operand.d_z &&
    d_first_surface_id == operand.d_first_surface_id &&
    d_second_surface_id == operand.d_second_surface_id &&
    d_third_surface_id == operand.d_third_surface_id &&
    d_is_star_corner == operand.d_is_star_corner;
}

// Inequality of two intersection points
template<typename OrdinalType, typename ScalarType>
bool IntersectionPoint<OrdinalType,ScalarType>::operator!=(
	       const IntersectionPoint<OrdinalType,ScalarType> &operand ) const
{
  return d_x != operand.d_x ||
    d_y != operand.d_y ||
    d_z != operand.d_z ||
    d_first_surface_id != operand.d_first_surface_id ||
    d_second_surface_id != operand.d_second_surface_id ||
    d_third_surface_id != operand.d_third_surface_id ||
    d_is_star_corner != operand.d_is_star_corner;
}

// X coordinate access method
template<typename OrdinalType, typename ScalarType>
ScalarType IntersectionPoint<OrdinalType,ScalarType>::getXCoordinate() const
{
  return d_x;
}

// Y coordinate access method
template<typename OrdinalType, typename ScalarType>
ScalarType IntersectionPoint<OrdinalType,ScalarType>::getYCoordinate() const
{
  return d_y;
}

// Z coordinate access method
template<typename OrdinalType, typename ScalarType>
ScalarType IntersectionPoint<OrdinalType,ScalarType>::getZCoordinate() const
{
  return d_z;
}

// First surface id access method
template<typename OrdinalType, typename ScalarType>
OrdinalType
IntersectionPoint<OrdinalType,ScalarType>::getFirstSurfaceId() const
{
  return d_first_surface_id;
}

// Second surface id access method
template<typename OrdinalType, typename ScalarType>
OrdinalType
IntersectionPoint<OrdinalType,ScalarType>::getSecondSurfaceId() const
{
  return d_second_surface_id;
}

// Third surface id access method
template<typename OrdinalType, typename ScalarType>
OrdinalType
IntersectionPoint<OrdinalType,ScalarType>::getThirdSurfaceId() const
{
  return d_third_surface_id;
}

// Return the raw point (stripped of connectivity data)
template<typename OrdinalType, typename ScalarType>
Vector<ScalarType>
IntersectionPoint<OrdinalType,ScalarType>::getRawPoint() const
{
  return Vector<ScalarType>( d_x, d_y, d_z );
}

// Set this point as a star corner
template<typename OrdinalType, typename ScalarType>
void IntersectionPoint<OrdinalType,ScalarType>::setAsStarCorner()
{
  d_is_star_corner = true;
}

// Return if this point is a star corner
template<typename OrdinalType, typename ScalarType>
bool IntersectionPoint<OrdinalType,ScalarType>::isStarCorner() const
{
  return d_is_star_corner;
}

// Test if this point contains the requested surface id
template<typename OrdinalType, typename ScalarType>
bool IntersectionPoint<OrdinalType,ScalarType>::isOnSurface(
					   const OrdinalType surface_id ) const
{
  return surface_id == d_first_surface_id ||
    surface_id == d_second_surface_id ||
    surface_id == d_third_surface_id;
}

// Test if this point lies on the same plane as another intersection point
template<typename OrdinalType, typename ScalarType>
bool IntersectionPoint<OrdinalType,ScalarType>::isOnSamePlane(
	    const IntersectionPoint<OrdinalType,ScalarType> &test_point ) const
{
  // The points cannot be the same
  testPrecondition( *this != test_point );

  unsigned number_of_shared_surfaces =
    IntersectionPoint<OrdinalType,ScalarType>::getNumberOfSharedSurfaces(
								  *this,
								  test_point );
  if( number_of_shared_surfaces >= 1 )
    return true;
  else
    return false;
}

// Test if this point is connected to another intersection point
template<typename OrdinalType, typename ScalarType>
bool IntersectionPoint<OrdinalType,ScalarType>::isOnSameCurve(
	    const IntersectionPoint<OrdinalType,ScalarType> &test_point ) const
{
  // The points cannot be the same
  testPrecondition( *this != test_point );

  unsigned number_of_shared_surfaces =
    IntersectionPoint<OrdinalType,ScalarType>::getNumberOfSharedSurfaces(
								  *this,
								  test_point );
  if( number_of_shared_surfaces == 2 )
    return true;
  else
    return false;
}

// Test if the intersection point is a real intersection point on a cell
template<typename OrdinalType,typename ScalarType>
template<typename Cell>
bool IntersectionPoint<OrdinalType,ScalarType>::isRealIntersectionPoint(
						       const Cell &cell ) const
{
  // The surface ids stored by this point must exist in the cell
  testPrecondition( cell.getSurfaceSensePair( d_first_surface_id ) !=
		    cell.endSurfaceSensePairs() );
  testPrecondition( cell.getSurfaceSensePair( d_second_surface_id ) !=
		    cell.endSurfaceSensePairs() );
  testPrecondition( cell.getSurfaceSensePair( d_third_surface_id ) !=
		    cell.endSurfaceSensePairs() );

  bool is_real_intersection_point = false;

  // The intersection point can only be real if it lies on the cell
  if( cell.isOn( d_x, d_y, d_z ) )
  {
    // Delta value
    bool cell_present = false;

    unsigned test_function_value = 0;

    // Need to evaluate the function Sum_(i=1)^8 2^(i-1)*delta_i mod3
    for( unsigned index = START_OCTANT; index < END_OCTANT; ++index )
    {
      // get the octant from the index
      Octant octant = getOctantFromInteger( index );

      bool primary_surface_boolean_parameter;
      bool secondary_surface_boolean_parameter;
      bool tertiary_surface_boolean_parameter;

      initializeBooleansForPointTest( octant,
				      primary_surface_boolean_parameter,
				      secondary_surface_boolean_parameter,
				      tertiary_surface_boolean_parameter );

      typename Cell::SurfaceSensePairsIterator surface_sense_pair =
	cell.beginSurfaceSensePairs();
      typename Cell::SurfaceSensePairsIterator end_surface_sense_pair =
	cell.endSurfaceSensePairs();

      // Array of bools for surface sense tests
      Teuchos::ArrayRCP<bool>
	sense_tests(std::distance(surface_sense_pair, end_surface_sense_pair));

      Teuchos::ArrayRCP<bool>::iterator test = sense_tests.begin();

      while( surface_sense_pair != end_surface_sense_pair )
      {
	if( surface_sense_pair->first->getId() == d_first_surface_id )
	  *test = primary_surface_boolean_parameter;
	else if( surface_sense_pair->first->getId() == d_second_surface_id )
	  *test = secondary_surface_boolean_parameter;
	else if( surface_sense_pair->first->getId() == d_third_surface_id )
	  *test = tertiary_surface_boolean_parameter;
	else
	{
	  SurfaceSense sense =
	    surface_sense_pair->first->getSenseOfPoint( d_x, d_y, d_z );

	  if( sense == surface_sense_pair->second || sense == ON_SURFACE )
	    *test = true;
	  else
	    *test = false;
	}

	++surface_sense_pair;
	++test;
      }

      // Determine if the cell is present in the octant
      cell_present = cell.isCellPresent( sense_tests );

      if( cell_present )
	test_function_value += getPointTestFunctionMultiplier( octant );
    }

    // The point is only real if the test function value is not 0 modulo 3
    if( test_function_value%3 != 0 )
      is_real_intersection_point = true;
  }

  return is_real_intersection_point;
}

// Get the unshared surface id between this point and another point
template<typename OrdinalType,typename ScalarType>
OrdinalType IntersectionPoint<OrdinalType,ScalarType>::getUnsharedSurfaceId(
				const IntersectionPoint<OrdinalType,ScalarType>
				&connected_point ) const
{
  // The two points must be on the same curve
  testPrecondition( isOnSameCurve( connected_point ) );

  OrdinalType unshared_surface_id;

  // compare the surface ids
  if( d_first_surface_id != connected_point.d_first_surface_id &&
      d_first_surface_id != connected_point.d_second_surface_id &&
      d_first_surface_id != connected_point.d_third_surface_id )
    unshared_surface_id = d_first_surface_id;

  else if( d_second_surface_id != connected_point.d_first_surface_id &&
	   d_second_surface_id != connected_point.d_second_surface_id &&
	   d_second_surface_id != connected_point.d_third_surface_id )
    unshared_surface_id = d_second_surface_id;

  else
    unshared_surface_id = d_third_surface_id;

  return unshared_surface_id;
}

// Print method that defines the behavior of the std::stream << operator
template<typename OrdinalType,typename ScalarType>
void IntersectionPoint<OrdinalType,ScalarType>::print( std::ostream &os ) const
{
  os << "Coordinates: {" << d_x << "," << d_y << "," << d_z << "}"
     << std::endl;
  os << "Planes Creating Intersection: " << d_first_surface_id << ", "
     << d_second_surface_id << ", " << d_third_surface_id << std::endl;
  os << "Type: " << ((d_is_star_corner) ? "star" : "normal") << std::endl;
}

// Get the unshared surface id between two connected intersection points
template<typename OrdinalType,typename ScalarType>
unsigned IntersectionPoint<OrdinalType,ScalarType>::getNumberOfSharedSurfaces(
		const IntersectionPoint<OrdinalType,ScalarType> &first_point,
		const IntersectionPoint<OrdinalType,ScalarType> &second_point )
{
  // The points cannot be the same
  testPrecondition( first_point != second_point );

  unsigned number_of_shared_surfaces = 0;

  OrdinalType first_point_surf_id_1 = first_point.getFirstSurfaceId();
  OrdinalType first_point_surf_id_2 = first_point.getSecondSurfaceId();
  OrdinalType first_point_surf_id_3 = first_point.getThirdSurfaceId();
  OrdinalType second_point_surf_id_1 = second_point.getFirstSurfaceId();
  OrdinalType second_point_surf_id_2 = second_point.getSecondSurfaceId();
  OrdinalType second_point_surf_id_3 = second_point.getThirdSurfaceId();

  // Two surface must be shared for the points to be connected
  if( first_point_surf_id_1 == second_point_surf_id_1 )
    ++number_of_shared_surfaces;
  else if( first_point_surf_id_1 == second_point_surf_id_2 )
    ++number_of_shared_surfaces;
  else if( first_point_surf_id_1 == second_point_surf_id_3 )
    ++number_of_shared_surfaces;

  if( first_point_surf_id_2 == second_point_surf_id_1 )
    ++number_of_shared_surfaces;
  else if( first_point_surf_id_2 == second_point_surf_id_2 )
    ++number_of_shared_surfaces;
  else if( first_point_surf_id_2 == second_point_surf_id_3 )
    ++number_of_shared_surfaces;

  if( first_point_surf_id_3 == second_point_surf_id_1 )
    ++number_of_shared_surfaces;
  else if( first_point_surf_id_3 == second_point_surf_id_2 )
    ++number_of_shared_surfaces;
  else if( first_point_surf_id_3 == second_point_surf_id_3 )
    ++number_of_shared_surfaces;

  // For a set of properly defined intersection points, only two surfaces
  // should ever be shared
  testPostcondition( number_of_shared_surfaces <= 2 );

  return number_of_shared_surfaces;
}

// Initialize the boolean variables used in the real point test
template<typename OrdinalType, typename ScalarType>
void IntersectionPoint<OrdinalType,ScalarType>::initializeBooleansForPointTest(
				     const Octant octant,
				     bool &primary_surface_boolean_parameter,
				     bool &secondary_surface_boolean_parameter,
			             bool &tertiary_surface_boolean_parameter )
{
  // The octant must not be the END_OCTANT
  testPrecondition( octant != END_OCTANT );

  switch( octant )
  {
  case POS_POS_POS_OCTANT:
    primary_surface_boolean_parameter = true;
    secondary_surface_boolean_parameter = true;
    tertiary_surface_boolean_parameter = true;
    break;
  case POS_NEG_POS_OCTANT:
    primary_surface_boolean_parameter = true;
    secondary_surface_boolean_parameter = false;
    tertiary_surface_boolean_parameter = true;
    break;
  case POS_NEG_NEG_OCTANT:
    primary_surface_boolean_parameter = true;
    secondary_surface_boolean_parameter = false;
    tertiary_surface_boolean_parameter = false;
    break;
  case POS_POS_NEG_OCTANT:
    primary_surface_boolean_parameter = true;
    secondary_surface_boolean_parameter = true;
    tertiary_surface_boolean_parameter = false;
    break;
  case NEG_NEG_POS_OCTANT:
    primary_surface_boolean_parameter = false;
    secondary_surface_boolean_parameter = false;
    tertiary_surface_boolean_parameter = true;
    break;
  case NEG_NEG_NEG_OCTANT:
    primary_surface_boolean_parameter = false;
    secondary_surface_boolean_parameter = false;
    tertiary_surface_boolean_parameter = false;
    break;
  case NEG_POS_NEG_OCTANT:
    primary_surface_boolean_parameter = false;
    secondary_surface_boolean_parameter = true;
    tertiary_surface_boolean_parameter = false;
    break;
  case NEG_POS_POS_OCTANT:
    primary_surface_boolean_parameter = false;
    secondary_surface_boolean_parameter = true;
    tertiary_surface_boolean_parameter = true;
    break;
  }
}

// Get the multiplier for the requested stage of the real point test function
template<typename OrdinalType, typename ScalarType>
unsigned
IntersectionPoint<OrdinalType,ScalarType>:: getPointTestFunctionMultiplier(
							  const Octant octant )
{
  // The octant must not be the END_OCTANT
  testPrecondition( octant != END_OCTANT );

  switch( octant )
  {
  case POS_POS_POS_OCTANT:
    return 1;
  case POS_NEG_POS_OCTANT:
    return 2;
  case POS_NEG_NEG_OCTANT:
    return 4;
  case POS_POS_NEG_OCTANT:
    return 8;
  case NEG_NEG_POS_OCTANT:
    return 16;
  case NEG_NEG_NEG_OCTANT:
    return 32;
  case NEG_POS_NEG_OCTANT:
    return 64;
  case NEG_POS_POS_OCTANT:
    return 128;
  }
}

} // end Geometry namespace

#endif // end GEOMETRY_INTERSECTION_POINT_DEF_HPP

//---------------------------------------------------------------------------//
// end Geometry_IntersectionPoint_def.hpp
//---------------------------------------------------------------------------//
