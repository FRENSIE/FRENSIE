//---------------------------------------------------------------------------//
//!
//! \file   Geometry_IntersectionPoint.hpp
//! \author Alex Robinson
//! \brief  IntersectionPoint class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_INTERSECTION_POINT_HPP
#define GEOMETRY_INTERSECTION_POINT_HPP

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_OrdinalTraits.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Geometry_ThreeSpaceObject.hpp"
#include "Geometry_Vector.hpp"
#include "Geometry_Cell.hpp"
#include "Utility_PrintableObject.hpp"

namespace Geometry{

/*! \brief Eighth space enumeration
 * 
 * Assigning the booleans in this order assures that the octants
 * are iterated through in counter-clockwise order w.r.t. the x-y plane.
 */
enum Octant{
  START_OCTANT = 0,
  POS_POS_POS_OCTANT = START_OCTANT,
  POS_NEG_POS_OCTANT,
  POS_NEG_NEG_OCTANT,
  POS_POS_NEG_OCTANT,
  NEG_NEG_POS_OCTANT,
  NEG_NEG_NEG_OCTANT,
  NEG_POS_NEG_OCTANT,
  NEG_POS_POS_OCTANT,
  END_OCTANT
};

//! An intersection point between three planar surfaces
template<typename OrdinalType, typename ScalarType>
class IntersectionPoint : public Utility::PrintableObject, public ThreeSpaceObject
{

public:

  //!@{
  //! Typedefs
  //! Typedef for ordinal type
  typedef OrdinalType ordinalType;
  //! Typedef for scalar type
  typedef ScalarType scalarType;
  //@}

private:

  // Typedef for OrdinalTraits
  typedef Teuchos::OrdinalTraits<OrdinalType> OT;
  // Typedef for ScalarTraits
  typedef Teuchos::ScalarTraits<ScalarType> ST;

public:

  //! Default constructor
  IntersectionPoint();

  //! General constructor
  IntersectionPoint( const ScalarType x,
		     const ScalarType y,
		     const ScalarType z,
		     const OrdinalType first_surface_id,
		     const OrdinalType second_surface_id,
		     const OrdinalType third_surface_id,
		     const bool is_star_corner = false );

  //! Vector constructor
  IntersectionPoint( const Vector<ScalarType> raw_intersection_point,
		     const OrdinalType first_surface_id,
		     const OrdinalType second_surface_id,
		     const OrdinalType third_surface_id,
		     const bool is_star_corner = false );
  
  //! Copy constructor
  IntersectionPoint( const IntersectionPoint<OrdinalType,ScalarType> 
		     &source_point );

  //! Destructor
  virtual ~IntersectionPoint()
  { /* ... */ }

  //! Copies values from one intersection point to another
  IntersectionPoint<OrdinalType,ScalarType>&
  operator=( const IntersectionPoint<OrdinalType,ScalarType> &source_point );

  //! Element access method (const).
  const ScalarType& operator[]( const ordinalType index ) const;

  //! Equality of two intersection points
  bool operator==( 
	      const IntersectionPoint<OrdinalType,ScalarType> &operand ) const;

  //! Inequality of two intersection points
  bool operator!=( 
	      const IntersectionPoint<OrdinalType,ScalarType> &operand ) const;

  //! X coordinate access method
  ScalarType getXCoordinate() const;

  //! Y coordinate access method
  ScalarType getYCoordinate() const;

  //! Z coordinate access method
  ScalarType getZCoordinate() const;

  //! First surface id access method
  OrdinalType getFirstSurfaceId() const;

  //! Second surface id access method
  OrdinalType getSecondSurfaceId() const;

  //! Third surface id access method
  OrdinalType getThirdSurfaceId() const;

  //! Return the raw point (stripped of connectivity data)
  Vector<ScalarType> getRawPoint() const;

  //! Set this point as a star corner
  void setAsStarCorner();

  //! Return if this point is a star corner
  bool isStarCorner() const;

  //! Test if this point contains the requested surface id
  bool isOnSurface( const OrdinalType surface_id ) const;

  //! Test if this point is on the same plane as another intersection point
  bool isOnSamePlane( const IntersectionPoint<OrdinalType,ScalarType>
		      &test_point ) const;

  //! Test if this point lies on the same curve as another intersection point
  bool isOnSameCurve( const IntersectionPoint<OrdinalType,ScalarType> 
		      &test_point ) const;

  //! Test if the intersection point is a real intersection point on a cell
  template<typename Cell>
  bool isRealIntersectionPoint( const Cell &cell ) const;

  //! Get the unshared surface id between this point and another point
  OrdinalType getUnsharedSurfaceId( 
			        const IntersectionPoint<OrdinalType,ScalarType>
				&connected_point ) const;

  //! Print method that defines the behavior of the std::stream << operator
  void print( std::ostream &os ) const;

protected:
  
  // Get the number of shared surfaces between two intersection points
  static unsigned getNumberOfSharedSurfaces( 
	       const IntersectionPoint<OrdinalType,ScalarType> &first_point,
	       const IntersectionPoint<OrdinalType,ScalarType> &second_point );

  // Initialize the boolean variables used in the real point test
  static void initializeBooleansForPointTest(
			      const Octant octant,
			      bool &primary_surface_boolean_parameter,
			      bool &secondary_surface_boolean_parameter,
			      bool &tertiary_surface_boolean_parameter );

  // Get the multiplier for the requested stage of the real point test function
  static unsigned getPointTestFunctionMultiplier( const Octant octant );

private:
  
  // Intersection point
  ScalarType d_x;
  ScalarType d_y;
  ScalarType d_z;

  // Intersection point connectivity data
  OrdinalType d_first_surface_id;
  OrdinalType d_second_surface_id;
  OrdinalType d_third_surface_id; 

  // It must be recorded whether or not this point is a star corner
  bool d_is_star_corner;
};

// Get an Octant from an integer type
template<typename T>
Octant getOctantFromInteger( const T value )
{
  Octant octant;
  switch( value )
  {
  case POS_POS_POS_OCTANT:
    octant = POS_POS_POS_OCTANT;
    break;
  case POS_NEG_POS_OCTANT:
    octant = POS_NEG_POS_OCTANT;
    break;
  case POS_NEG_NEG_OCTANT:
    octant = POS_NEG_NEG_OCTANT;
    break;
  case POS_POS_NEG_OCTANT:
    octant = POS_POS_NEG_OCTANT;
    break;
  case NEG_NEG_POS_OCTANT:
    octant = NEG_NEG_POS_OCTANT;
    break;
  case NEG_NEG_NEG_OCTANT:
    octant = NEG_NEG_NEG_OCTANT;
    break;
  case NEG_POS_NEG_OCTANT:
    octant = NEG_POS_NEG_OCTANT;
    break;
  case NEG_POS_POS_OCTANT:
    octant = NEG_POS_POS_OCTANT;
    break;
  default:
    octant = END_OCTANT;
    break;
  }

  return octant;
}

} // end FRENSIE namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "Geometry_IntersectionPoint_def.hpp"

//---------------------------------------------------------------------------//

#endif // end GEOMETRY_INTERSECTION_POINT_HPP

//---------------------------------------------------------------------------//
// end Geometry_IntersectionPoint.hpp
//---------------------------------------------------------------------------//
