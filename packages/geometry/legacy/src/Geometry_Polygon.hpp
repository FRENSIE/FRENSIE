//---------------------------------------------------------------------------//
//!
//! \file   Geometry_Polygon.hpp
//! \author Alex Robinson
//! \brief  Polygon class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_POLYGON_HPP
#define GEOMETRY_POLYGON_HPP

// Std Lib Includes
#include <list>
#include <iostream>

// FRENSIE Includes
#include "Geometry_ThreeSpaceObject.hpp"
#include "Geometry_Vector.hpp"
#include "Geometry_Matrix.hpp"
#include "Utility_PrintableObject.hpp"
#include "Utility_Tuple.hpp"

namespace Geometry{

template<typename OrdinalType,typename ScalarType>
class Polygon : public Utility::PrintableObject, public ThreeSpaceObject
{

public:

  //@{
  //! Typedefs
  //! Typedef for ordinal type
  typedef OrdinalType ordinalType;
  //! Typedef for scalar type
  typedef ScalarType scalarType;
  //! Typedef
  //@}

protected:

  //! Typedef for projected point
  typedef Utility::Pair<ScalarType,ScalarType> PointProjection;

private:

  //! Typedef for scalar traits
  typedef Teuchos::ScalarTraits<ScalarType> ST;
  //! Typedef for cell ordinal traits
  typedef Teuchos::OrdinalTraits<OrdinalType> OT;

public:

  //! Constructor
  template<typename Point>
  Polygon( const OrdinalType polygon_id,
	   const std::list<Point> &ordered_polygon_corners );

  //! Destructor
  ~Polygon()
  { /* ... */ }

  //! Return the polygon id
  inline OrdinalType getId() const;

  //! Return the area of the polygon
  inline ScalarType getArea() const;

  //! Return the minimum x-coordinate
  inline ScalarType getMinXCoordinate() const;

  //! Return the maximum x-coordinate
  inline ScalarType getMaxXCoordinate() const;

  //! Return the minimum y-coordinate
  inline ScalarType getMinYCoordinate() const;

  //! Return the maximum y-coordinate
  inline ScalarType getMaxYCoordinate() const;

  //! Return the minimum z-coordinate
  inline ScalarType getMinZCoordinate() const;

  //! Return the maximum z-coordinate
  inline ScalarType getMaxZCoordinate() const;

  //! Return the centroid x-coordinate
  inline ScalarType getCentroidXCoordinate() const;

  //! Return the centroid y-coordinate
  inline ScalarType getCentroidYCoordinate() const;

  //! Return the centroid z-coordinate
  inline ScalarType getCentroidZCoordinate() const;

  //! Return the polygon centroid
  inline Vector<ScalarType> getCentroid() const;

  //! Return the unit normal to the plane of the polygon
  inline Vector<ScalarType> getPolygonPlaneUnitNormal() const;

  //! Print method that defines the behavior of the std::stream << operator
  void print( std::ostream &os ) const;

  //! Check that a point list is a valid polygon representation
  template<typename Point>
  static bool isValidPointList( const std::list<Point> &polygon_corners );

protected:

  //@{
  //! Valid point list tests
  //! Check that the point list has the correct size
  template<typename Point>
  static bool hasCorrectSize( const std::list<Point> &polygon_corners );

  //! Check that the point list is closed
  template<typename Point>
  static bool isClosed( const std::list<Point> &polygon_corners );

  //! Check that the point list doesn't contain any consecutive repeated points
  template<typename Point>
  static bool hasNoConsecutiveRepeatedPoints(
			             const std::list<Point> &polygon_corners );

  //! Check that the point list is initialized properly
  template<typename Point>
  static bool isInitializedProperly( const std::list<Point> &polygon_corners );

  // Check that the point list has all points on the same plane
  template<typename Point>
  static bool hasAllPointsOnSamePlane(
				     const std::list<Point> &polygon_corners );
  //@}

  //! Calculate the normal of the plane formed by three points
  template<typename Point>
  static Vector<ScalarType> calculateNormalOfPlaneFromThreePoints(
						    const Point &first_point,
						    const Point &second_point,
						    const Point &third_point );

  //! Compute the unit normal to the plane of the polygon
  template<typename Point>
  static Vector<ScalarType> calculatePolygonPlaneUnitNormal(
		       const std::list<Point> &polygon_corners );

  //! Find and the maximum and minimum coordinates of the polygon
  template<typename Point>
  static void getExtremeCoordinates( const std::list<Point> &polygon_corners,
				     Vector<ScalarType> &min_coordinates,
				     Vector<ScalarType> &max_coordinates );

  //! Create and set the transformation matrix and vector
  template<typename Point>
  static void getTransformMatrixAndVector(
			  const Vector<ScalarType> &polygon_plane_unit_normal,
			  const Point &polygon_corner,
			  Matrix<ScalarType> &rotation_matrix,
			  Vector<ScalarType> &translation_vector );

  //! Simplify the polygon by transforming plane-of-polygon to x-y plane
  template<typename Point>
  static void transformPolygon(
		     const std::list<Point> &polygon_corners,
		     std::list<PointProjection> &transformed_polygon_corners,
		     const Matrix<ScalarType> &rotation_matrix,
		     const Vector<ScalarType> &translation_vector );

  //! Apply transform to a point on the polygon (move to x-y plane)
  template<typename Point>
  static PointProjection applyTransform(
				const Point &point_on_polygon,
				const Matrix<ScalarType> &rotation_matrix,
				const Vector<ScalarType> &translation_vector );

  //! Apply reverse transform to point on the x-y plane
  static Vector<ScalarType> applyReverseTransform(
				const PointProjection &xy_plane_point,
				const Matrix<ScalarType> &rotation_matrix,
				const Vector<ScalarType> &translation_vector );

  //! Calculate the area of a simplified polygon
  static ScalarType calculateArea(
		        const std::list<PointProjection> &simplified_polygon );

  //! Calculate the polygon centroid
  static PointProjection calculateCentroid(
			  const std::list<PointProjection> &simplified_polygon,
			  const ScalarType polygon_area );

  //! Calculate the x-coordinate of a simplified polygon centroid
  static ScalarType calculateCentroidXCoordinate(
			  const std::list<PointProjection> &simplified_polygon,
			  const ScalarType polygon_area );

  //! Calculate the y-coordinate of a simplified polygon centroid
  static ScalarType calculateCentroidYCoordinate(
			  const std::list<PointProjection> &simplified_polygon,
			  const ScalarType polygon_area );

private:

  // Polygon Id
  OrdinalType d_id;

  // Polygon corners
  std::list<PointProjection> d_corners;

  // Min coordinates of the polygon
  Vector<ScalarType> d_min_coordinates;

  // Max coordinates of the polygon
  Vector<ScalarType> d_max_coordinates;

  // Polygon area
  ScalarType d_area;

  // Centroid of the polygon
  Vector<ScalarType> d_centroid;

  // Unit normal to plane of polygon
  Vector<ScalarType> d_unit_normal;

  // Rotation matrix to transform plane-of-polygon to x-y plane
  Matrix<ScalarType> d_rotation_matrix;

  // Translation vector to transform plane-of-polygon to x-y plane
  Vector<ScalarType> d_translation_vector;
};

} // end Geometry namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "Geometry_Polygon_def.hpp"

//---------------------------------------------------------------------------//

#endif // end GEOMETRY_POLYGON_HPP

//---------------------------------------------------------------------------//
// end Geometry_Polygon.hpp
//---------------------------------------------------------------------------//

