//---------------------------------------------------------------------------//
//!
//! \file   PolygonFactory.hpp
//! \author Alex Robinson
//! \brief  Polygon factory class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef POLYGON_FACTORY_HPP
#define POLYGON_FACTORY_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FACEMC Includes
#include "Surface.hpp"
#include "Polygon.hpp"
#include "IntersectionPoint.hpp"

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

template<typename OrdinalType, typename ScalarType>
class PolygonFactory
{

public:

  //@{
  //! Typedefs
  //! Typedef for polygon pointer
  typedef typename Teuchos::RCP<Polygon<OrdinalType,ScalarType> > PolygonPtr;

private:

  //! Typedef for IntersectionPoint
  typedef IntersectionPoint<OrdinalType,ScalarType> IntersectionPoint;
  //! Typedef for Surface
  typedef Surface<OrdinalType,ScalarType> Surface;
  //! Typedef for Polygon
  typedef Polygon<OrdinalType,ScalarType> Polygon
  

  //! Constructor
  PolygonFactory()
  { /* ... */ }

  //! Destructor
  ~PolygonFactory()
  { /* ... */ }
  
  //! Create a polygon from intersection points on a surface
  PolygonPtr create( std::list<IntersectionPoint> &unordered_polygon_corners,
		     const Surface &plane_of_polygon,
		     const SurfaceSense plane_sense ) const;

protected:

  //! Find the first three points on the boundary of the polygon
  static typename std::list<IntersectionPoint>::const_iterator 
  initializePolygonCorners( 
		       std::list<IntersectionPoint> &ordered_polygon_corners,
		       std::list<IntersectionPoint> &unordered_polygon_corners,
		       const Surface &plane_of_polygon,
		       const SurfaceSense plane_sense );

  //! Find the lexicographically largest point
  static typename std::list<IntersectionPoint>::const_iterator
  getLexicographicallyLargestPoint(
	 const std::list<IntersectionPoint> &unordered_polygon_corners );

  //! Find the next point on the boundary of the polygon
  
  static typename std::list<IntersectionPoint>::const_iterator
  getNextPolygonCorner( 
               const OrdinalType desired_surface_id,
	       const Vector<ScalarType> &current_corner,
	       const std::list<IntersectionPoint> &unordered_polygon_corners,
               PointFindNecessity point_find_necessity = POINT_MUST_BE_FOUND );
};

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "PolygonFactory_def.hpp"

//---------------------------------------------------------------------------//

#endif // end POLYGON_FACTORY_HPP

//---------------------------------------------------------------------------//
// end PolygonFactory.hpp
//---------------------------------------------------------------------------//
