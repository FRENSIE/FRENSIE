//---------------------------------------------------------------------------//
//!
//! \file   Geometry_CellPolygonFactory.hpp
//! \author Alex Robinson
//! \brief  Declaration of factory class that creates polygons on cell surfs.
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_CELL_POLYGON_FACTORY_HPP
#define GEOMETRY_CELL_POLYGON_FACTORY_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_OrdinalTraits.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Geometry_Polygon.hpp"
#include "Geometry_IntersectionPoint.hpp"
#include "Geometry_Cell.hpp"

namespace Geometry{

/*! \brief Enumeration to specify whether function must find a point
 *
 * This enumeration is used by the findNextPolygonCorner member function when
 * design-by-contract is enabled.
 */
enum PointFindNecessity{
  POINT_MUST_BE_FOUND,
  POINT_MAY_NOT_BE_FOUND
};

/*! \brief Enumeration to specify the orientation of a polygon
 */
enum PolygonOrientation{
  CELL_ON_LEFT,
  CELL_ON_RIGHT,
  INVALID_ORIENTATION
};

template<typename Cell>
class CellPolygonFactory
{

public:

  //@{
  //! Typedefs
  //! Typedef for ordinal type
  typedef typename Cell::surfaceOrdinalType ordinalType;
  //! Typedef for scalar type
  typedef typename Cell::scalarType scalarType;
  //! Typedef for polygon pointer
  typedef typename Teuchos::RCP<Polygon<ordinalType,scalarType> > PolygonPtr;

private:

  // Typedef for IntersectionPoint
  typedef IntersectionPoint<ordinalType,scalarType> Point;
  // Typedef for OrdinalTraits
  typedef Teuchos::OrdinalTraits<ordinalType> OT;
  // Typedef for ScalarTraits
  typedef Teuchos::ScalarTraits<scalarType> ST;

public:

  //! Constructor
  CellPolygonFactory( const Teuchos::RCP<Cell> &cell_ptr );

  //! Destructor
  ~CellPolygonFactory()
  { /* ... */ }

  //! Create a polygon from intersection points on a surface
  PolygonPtr create( std::list<Point> &unordered_polygon_corners ) const;

protected:

  //! Find the first three points on the boundary of the polygon
  typename std::list<Point>::const_iterator
  initializePolygonCorners(
		       std::list<Point> &ordered_polygon_corners,
		       std::list<Point> &unordered_polygon_corners,
		       const ordinalType plane_of_polygon_id ) const;

  //! Determine if the ordering of a polygon initialization needs to reverse
  bool cornerTripletNeedsReversing(
			 const ordinalType plane_of_polygon_id,
			 const ordinalType first_to_second_point_surface_id,
			 const ordinalType second_to_third_point_surface_id,
			 const Point &first_point,
			 const Point &second_point,
			 const Point &third_point ) const;

  //! Test if all of the points lie on the same plane
  static bool allPointsOnSamePlane(
	       const std::list<Point> &unordered_polygon_corners );

  //! Find the id of the polygon plane
  static ordinalType getPlaneOfPolygonId(
	       const std::list<Point> &unordered_polygon_corners );

  //! Find the lexicographically largest point
  static typename std::list<Point>::iterator
  getLexicographicallyLargestPoint(
				 std::list<Point> &unordered_polygon_corners );

  //! Find the next point on the boundary of the polygon
  static typename std::list<Point>::iterator
  getNextPolygonCorner(
               const ordinalType desired_surface_id,
	       const Point &current_corner,
	       std::list<Point> &unordered_polygon_corners,
               PointFindNecessity point_find_necessity = POINT_MUST_BE_FOUND );

private:

  // The cell on which all polygons will lie
  Teuchos::RCP<Cell> d_cell_ptr;
};

} // end Geometry namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "Geometry_CellPolygonFactory_def.hpp"

//---------------------------------------------------------------------------//

#endif // end GEOMETRY_CELL_POLYGON_FACTORY_HPP

//---------------------------------------------------------------------------//
// end Geometry_CellPolygonFactory.hpp
//---------------------------------------------------------------------------//
