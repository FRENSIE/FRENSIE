//---------------------------------------------------------------------------//
//!
//! \file   Polygon.hpp
//! \author Alex Robinson
//! \brief  Polygon class declaration
//!
//---------------------------------------------------------------------------//

#ifndef POLYGON_HPP
#define POLYGON_HPP

// Std Lib Includes
#include <list>
#include <iostream>

// FACEMC Includes
#include "PrintableObject.hpp"
#include "ThreeSpaceObject.hpp"
#include "Tuple.hpp"
#include "Vector.hpp"
#include "Matrix.hpp"

namespace FACEMC{

template<typename OrdinalType,typename ScalarType>
class Polygon : public PrintableObject, public ThreeSpaceObject
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
  typedef Pair<ScalarType,ScalarType> PointProjection;

private:

  //! Typedef for scalar traits
  typedef Teuchos::ScalarTraits<ScalarType> ST;
  //! Typedef for cell ordinal traits
  typedef Teuchos::OrdinalTraits<OrdinalType> OT;

public:

  //! Constructor
  Polygon( const OrdinalType polygon_id,
	   const std::list<Vector<ScalarType> > &ordered_polygon_corners );

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

protected:

  //! Compute the unit normal to the plane of the polygon
  static Vector<ScalarType> calculatePolygonPlaneUnitNormal( 
		       const std::list<Vector<ScalarType> > &polygon_corners );

  //! Find and the maximum and minimum coordinates of the polygon
  static void getExtremeCoordinates( 
			 const std::list<Vector<ScalarType> > &polygon_corners,
			 Vector<ScalarType> &min_coordinates,
			 Vector<ScalarType> &max_coordinates );

  //! Create and set the transformation matrix and vector
  static void getTransformMatrixAndVector( 
			  const Vector<ScalarType> &polygon_plane_unit_normal,
			  const Vector<ScalarType> &polygon_corner,
			  Matrix<ScalarType> &rotation_matrix,
			  Vector<ScalarType> &translation_vector );
  
  //! Simplify the polygon by transforming plane-of-polygon to x-y plane
  static void transformPolygon( 
		     const std::list<Vector<ScalarType> > &polygon_corners,
		     std::list<PointProjection> &transformed_polygon_corners,
		     const Matrix<ScalarType> &rotation_matrix,
		     const Vector<ScalarType> &translation_vector );

  //! Apply transform to a point on the polygon (move to x-y plane)
  static PointProjection applyTransform( 
				const Vector<ScalarType> &point_on_polygon,
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

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "Polygon_def.hpp"

//---------------------------------------------------------------------------//

#endif // end POLYGON_HPP

//---------------------------------------------------------------------------//
// end Polygon.hpp
//---------------------------------------------------------------------------//

