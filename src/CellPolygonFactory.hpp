//---------------------------------------------------------------------------//
//!
//! \file   CellPolygonFactory.hpp
//! \author Alex Robinson
//! \brief  Declaration of factory class that creates polygons on cell surfs.
//!
//---------------------------------------------------------------------------//

#ifndef CELL_POLYGON_FACTORY_HPP
#define CELL_POLYGON_FACTORY_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_OrdinalTraits.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FACEMC Includes
#include "Polygon.hpp"
#include "IntersectionPoint.hpp"
#include "Cell.hpp"

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
  LEFT_HANDED,
  RIGHT_HANDED,
  INVALID_ORIENTATION
};

namespace FACEMC{

template<typename Cell>
class CellPolygonFactory
{

public:

  //@{
  //! Typedefs
  //! Typedef for ordinal type
  typedef typename Cell::surfaceOrdinalType ordinalType
  //! Typedef for scalar type
  typedef typename Cell::scalarType scalarType
  //! Typedef for polygon pointer
  typedef typename Teuchos::RCP<Polygon<ordinalType,scalarType> > PolygonPtr;

private:

  // Typedef for IntersectionPoint
  typedef IntersectionPoint<ordinalType,scalarType> IntersectionPoint;
  // Typedef for Surface
  typedef Surface<ordinalType,scalarType> Surface;
  // Typedef for Polygon
  typedef Polygon<ordinalType,scalarType> Polygon;
  // Typedef for OrdinalTraits
  typedef Teuchos::OrdinalTraits<ordinalType> OT;
  // Typedef for ScalarTraits
  typedef Teuchos::ScalarTraits<scalarType> ST;
  

  //! Constructor
  CellPolygonFactory( const Teuchos::RCP<Cell> &cell_ptr );

  //! Destructor
  ~CellPolygonFactory()
  { /* ... */ }
  
  //! Create a polygon from intersection points on a surface
  PolygonPtr create( 
	       std::list<IntersectionPoint> &unordered_polygon_corners ) const;

protected:

  //! Find the first three points on the boundary of the polygon
  typename std::list<IntersectionPoint>::const_iterator 
  initializePolygonCorners( 
		       std::list<IntersectionPoint> &ordered_polygon_corners,
		       std::list<IntersectionPoint> &unordered_polygon_corners,
		       const ordinalType plane_of_polygon_id ) const;

  //! Determine if the ordering of a polygon initialization needs to reverse
  bool reversePolygonCornerOrdering( 
			 const ordinalType plane_of_polygon_id,
			 const ordinalType first_to_second_point_surface_id,
			 const ordinalType second_to_third_point_surface_id,
			 const IntersectionPoint &first_point,
			 const IntersectionPoint &second_point,
			 const IntersectionPoint &third_point ) const;

  //! Test if all of the points lie on the same plane
  static bool allPointsOnSamePlane( 
	       const std::list<IntersectionPoint> &unordered_polygon_corners );

  //! Find the id of the polygon plane
  static ordinalType getPlaneOfPolygonId( 
	       const std::list<IntersectionPoint> &unordered_polygon_corners );

  //! Find the lexicographically largest point  static typename std::list<IntersectionPoint>::const_iterator
  getLexicographicallyLargestPoint(
	 const std::list<IntersectionPoint> &unordered_polygon_corners );

  //! Find the next point on the boundary of the polygon
  static typename std::list<IntersectionPoint>::const_iterator
  getNextPolygonCorner( 
               const ordinalType desired_surface_id,
	       const Vector<scalarType> &current_corner,
	       const std::list<IntersectionPoint> &unordered_polygon_corners,
               PointFindNecessity point_find_necessity = POINT_MUST_BE_FOUND );

private:
  
  // The cell on which all polygons will lie
  Teuchos::RCP<Cell> d_cell_ptr; 
};

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "CellPolygonFactory_def.hpp"

//---------------------------------------------------------------------------//

#endif // end CELL_POLYGON_FACTORY_HPP

//---------------------------------------------------------------------------//
// end CellPolygonFactory.hpp
//---------------------------------------------------------------------------//
