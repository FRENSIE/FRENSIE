//---------------------------------------------------------------------------//
//!
//! \file   IntersectionPoint.hpp
//! \author Alex Robinson
//! \brief  IntersectionPoint class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef INTERSECTION_POINT_HPP
#define INTERSECTION_POINT_HPP

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_OrdinalTraits.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FACEMC Includes
#include "PrintableObject.hpp"
#include "ThreeSpaceObject.hpp"
#include "Vector.hpp"
#include "Cell.hpp"

namespace FACEMC{

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
  END_OCTANT = NEG_POS_POS_OCTANT
};

//! An intersection point between three planar surfaces
template<typename OrdinalType, typename ScalarType>
class IntersectionPoint : public PrintableObject, public ThreeSpaceObject
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
		     const OrdinalType third_surface_id );

  //! Vector constructor
  IntersectionPoint( const Vector<ScalarType> intersection_point,
		     const OrdinalType first_surface_id,
		     const OrdinalType second_surface_id,
		     const OrdinalType third_surface_id );
  
  //! Copy constructor
  IntersectionPoint( const IntersectionPoint<OrdinalType,ScalarType> 
		     &source_point );

  //! Destructor
  virtual ~IntersectinPoint()
  { /* ... */ }

  //! Copies values from one intersection point to another
  IntersectionPoint<OrdinalType,ScalarType>&
  operator=( const IntersectionPoint<OrdinalType,ScalarType> &source_point );

  //! Element access method (const).
  const ScalarType& operator[]( const ordinalType index ) const;

  //! First surface id access method
  OrdinalType getFirstSurfaceId() const;

  //! Second surface id access method
  OrdinalType getSecondSurfaceId() const;

  //! Third surface id access method
  OrdinalType getThirdSurfaceId() const;

  //! Return the raw point (stripped of connectivity data)
  Vector<ScalarType> getRawPoint() const;

  //! Equality of two intersection points
  bool operator==( 
	      const IntersectionPoint<OrdinalType,ScalarType> &operand ) const;

  //! Inequality of two intersection points
  bool operator!=( 
	      const IntersectionPoint<OrdinalType,ScalarType> &operand ) const;

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
  static unsigned getNumberOfSharedSufaces( 
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
};

} // end FACEMC namespace

#endif // end INTERSECTION_POINT_HPP

//---------------------------------------------------------------------------//
// end IntersectionPoint.hpp
//---------------------------------------------------------------------------//
