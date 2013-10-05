//---------------------------------------------------------------------------//
//!
//! \file   Polygon_def.hpp
//! \author Alex Robinson
//! \brief  Polygon class declaration
//!
//---------------------------------------------------------------------------//

#ifndef POLYGON_DEF_HPP
#define POLYGON_DEF_HPP

// Std Lib Includes
#include <list>

// FACEMC Includes
#include "Tuple.hpp"

namespace FACEMC{

// Constructor
/*! \details The corners can be arranged in either clockwise or 
 * counterclockwise order. During the polygon construction, they will be
 * transformed to a counterclockwise ordering. This simplifies the creation
 * of complex polygons in R3.
 */ 
template<typename OrdinalType, typename ScalarType>
Polygon<OrdinalType,ScalarType>::Polygon( 
			      const OrdinalType polygon_id,
			      const std::list<Point> &ordered_polygon_corners )
  : d_id( polygon_id ),
    d_corners( ordered_polygon_corners.size() ),
    d_largest_coordinates(),
    d_area( ST::zero() ),
    d_centroid(),
    d_unit_normal( 3 ),
    d_rotation_matrix( 3, 3 ),
    d_translation_vector( 3 )
{
  // The polygon must have at least 4 corners (3 + copy of first point)
  testPrecondition( d_corners.size() >= 4 );
  // Make sure that the polygon starts and ends with the same point
  testPrecondition( d_corners.front() == d_corners.back() );

  // Compute the unit normal to the plane of the polygon
  d_unit_normal = 
    Polygon<OrdinalType,ScalarType>::calculatePolygonPlaneUnitNormal( 
						     ordered_polygon_corners );
  
  // Find and set the largest coordinates of the polygon
  Polygon<OrdinalType,ScalarType>::getLargestCoordinates( 
						       ordered_polygon_corners,
						       d_largest_coordinates );

  // Create and set the transformation matrix and vector
  Polygon<OrdinalType,ScalarType>::getTransformMatrixAndVector( 
					       d_unit_normal,
					       ordered_polygon_corners.front(),
					       d_rotation_matrix,
					       d_translation_vector );

  // Simplify the polygon by transforming the plane-of-polygon to xy-plane
  Polygon<OrdinalType,ScalarType>::transformPolygon( 
						   ordered_polygon_corners,
						   d_corners,
						   d_rotation_matrix,
						   d_translation_vector );

  // Compute and cache the polygon area
  d_area = Polygon<OrdinalType,ScalarType>::calculateArea( d_corners );
						  
  // Compute and cache the polygon centroid
  PointProjection transformed_centroid = 
    Polygon<OrdinalType,ScalarType>::calculateCentroid( d_corners,
							d_area );

  d_centroid = Polygon<OrdinalType,ScalarType>::applyReverseTransform(
							transformed_centroid,
							d_rotation_matrix,
							d_translation_vector );
}

// Return the polygon id
template<typename OrdinalType, typename ScalarType>
inline OrdinalType Polygon<OrdinalType,ScalarType>::getId() const
{
  return d_id;
}

// Return the area of the polygon
template<typename OrdinalType, typename ScalarType>
inline ScalarType Polygon<OrdinalType,ScalarType>::getArea() const
{
  return d_area;
}

// Return the largest x-coordinate
template<typename OrdinalType, typename ScalarType>
inline ScalarType 
Polygon<OrdinalType,ScalarType>::getLargestXCoordinate() const
{
  return d_largest_coordinates.first;
}

// Return the largest y-coordinate
template<typename OrdinalType, typename ScalarType>
inline ScalarType
Polygon<OrdinalType,ScalarType>::getLargestYCoordinate() const
{
  return d_largest_coordinates.second;
}

// Return the largest z-coordinate
template<typename OrdinalType, typename ScalarType>
inline ScalarType
Polygon<OrdinalType,ScalarType>::getLargestZCoordinate() const
{
  return d_largest_coordinates.third;
}

// Return the polygon centroid
template<typename OrdinalType, typename ScalarType>
typename Polygon<OrdinalType,ScalarType>::Point
Polygon<OrdinalType,ScalarType>::getCentroid() const
{
  return d_centroid;
}

// Return the unit normal to the plane of the polygon
template<typename OrdinalType, typename ScalarType>
typename ThreeSpaceTraitsAndPolicy<ScalarType>::Vector
Polygon<OrdinalType,ScalarType>::getPolygonPlaneUnitNormal() const
{
  return d_unit_normal;
}

// Print the polygon
template<typename OrdinalType, typename ScalarType>
void Polygon<OrdinalType,ScalarType>::print( 
					    std::ostream &output_stream ) const
{
  typename std::list<PointProjection>::const_iterator corner, end_corner;
  corner = d_corners.begin();
  end_corner = d_corners.end();

  while( corner != end_corner )
  {
    Point original_point = 
      Polygon<OrdinalType,ScalarType>::applyReverseTransform( 
							*corner,
							d_rotation_matrix,
							d_translation_vector );
    output_stream << "{" << original_point.first << ","
		  << original_point.second << ","
		  << original_point.third << "} ";
      
    ++corner;
  }

  output_stream << std::endl;
}

// Compute the unit normal to the plane of the polygon
template<typename OrdinalType, typename ScalarType>
typename ThreeSpaceTraitsAndPolicy<ScalarType>::Vector
Polygon<OrdinalType,ScalarType>::calculatePolygonPlaneUnitNormal(
			              const std::list<Point> &polygon_corners )
{
  // The polygon must have at least 4 corners (3 + copy of first point)
  testPrecondition( polygon_corners.size() >= 4 );
  
  typename std::list<Point>::const_iterator first_point, second_point, 
    third_point;
  
  first_point = polygon_corners.begin();
  
  second_point = first_point;
  ++second_point;
    
  third_point = second_point;
  ++third_point;

  // The orientation of these vector assures that the transformed polygon
  // will have a left-handed orientation on the xy-plane (needed for pos. area)
  Vector polygon_vector_1 =
    ThreeSpace::createVector( second_point->first - third_point->first,
			      second_point->second - third_point->second,
			      second_point->third - third_point->third );

  Vector polygon_vector_2 = 
    ThreeSpace::createVector( second_point->first - first_point->first,
			      second_point->second - first_point->second,
			      second_point->third - first_point->third );

  Vector polygon_plane_normal =
    LAP::computeCrossProduct( polygon_vector_1, polygon_vector_2 );
  
  LAP::normalizeVector( polygon_plane_normal );

  return polygon_plane_normal;
}

// Find and set the largest coordinates of the polygon
template<typename OrdinalType, typename ScalarType>
void Polygon<OrdinalType,ScalarType>::getLargestCoordinates(
				       const std::list<Point> &polygon_corners,
				       Point &largest_coordinates )
{
  // The polygon must have at least 4 corners (3 + copy of first point)
  testPrecondition( polygon_corners.size() >= 4 );

  // Initialize the largest coordinates
  largest_coordinates.first = -ST::rmax();
  largest_coordinates.second = -ST::rmax();
  largest_coordinates.third = -ST::rmax();

  typename std::list<Point>::const_iterator corner, end_corner;
  corner = polygon_corners.begin();
  end_corner = polygon_corners.end();

  while( corner != end_corner )
  {
    if( corner->first > largest_coordinates.first )
      largest_coordinates.first = corner->first;
    
    if( corner->second > largest_coordinates.second )
      largest_coordinates.second = corner->second;
    
    if( corner->third > largest_coordinates.third )
      largest_coordinates.third = corner->second;

    ++corner;
  }
}

// Create and set the transformation matrix and vector
template<typename OrdinalType, typename ScalarType>
void Polygon<OrdinalType,ScalarType>::getTransformMatrixAndVector( 
				       const Vector &polygon_plane_unit_normal,
				       const Point &polygon_corner,
				       Matrix &rotation_matrix,
				       Vector &translation_vector )
{
  // Make sure the unit normal is valid
  testPrecondition( ST::magnitude( polygon_plane_unit_normal.normFrobenius() - 
				   ST::one() ) < ST::prec() );

  // Create the rotation matrix
  rotation_matrix = LAP::createRotationMatrixFromUnitVectors( 
						   polygon_plane_unit_normal,
						   ThreeSpace::zaxisVector() );

  // Convert the polygon corner to a three space vector
  Vector point = ThreeSpace::createVector( polygon_corner.first,
					   polygon_corner.second,
					   polygon_corner.third );

  // Determine the rotated polygon plane constant
  Vector rotation_matrix_row_3 = ThreeSpace::createVector( 
						     rotation_matrix( 2, 0 ), 
						     rotation_matrix( 2, 1 ),
						     rotation_matrix( 2, 2 ) );
  ScalarType rotated_plane_constant = rotation_matrix_row_3.dot( point );

  // The translation will only need to occur in the z-direction
  ScalarType delta_z = -rotated_plane_constant;

  // Create the translation vector
  translation_vector = ThreeSpace::createVector( ST::zero(),
						 ST::zero(),
						 delta_z );
}

// Simplify the polygon by transforming plane-of-polygon to x-y plane
template<typename OrdinalType, typename ScalarType>
void Polygon<OrdinalType,ScalarType>::transformPolygon(
		      const std::list<Point> &polygon_corners,
		      std::list<PointProjection> &transformed_polygon_corners,
		      const Matrix &rotation_matrix,
		      const Vector &translation_vector )
{
  // The polygon must have at least 4 corners (3 + copy of first point)
  testPrecondition( polygon_corners.size() >= 4 );
  testPrecondition( polygon_corners.size() == 
		    transformed_polygon_corners.size() );

  typename std::list<Point>::const_iterator corner, end_corner;
  corner = polygon_corners.begin();
  end_corner = polygon_corners.end();

  typename std::list<PointProjection>::iterator transformed_corner = 
    transformed_polygon_corners.begin();

  while( corner != end_corner )
  {
    *transformed_corner = Polygon<OrdinalType,ScalarType>::applyTransform(
							  *corner,
							  rotation_matrix,
							  translation_vector );
    ++corner;
    ++transformed_corner;
  }
}

// Apply transform to a point on the polygon
template<typename OrdinalType, typename ScalarType>
typename Polygon<OrdinalType,ScalarType>::PointProjection
Polygon<OrdinalType,ScalarType>::applyTransform( 
					     const Point &point_on_polygon,
					     const Matrix &rotation_matrix,
					     const Vector &translation_vector )
{
  // Make sure that the rotation matrix is valid (3x3 and orthonormal)
  testPrecondition( rotation_matrix.numRows() == 3 );
  testPrecondition( rotation_matrix.numCols() == 3 );
  testPrecondition( LAP::isOrthonormal( rotation_matrix ) );

  // Convert the point to a vector
  Vector point = ThreeSpace::createVector( point_on_polygon.first,
					   point_on_polygon.second,
					   point_on_polygon.third );

  // Apply the transformation (x' = R*x + x_0)
  Vector transformed_point( translation_vector );
  remember( int multiply_success = )
    transformed_point.multiply( Teuchos::NO_TRANS,
				Teuchos::NO_TRANS,
				ST::one(),
				rotation_matrix,
				point,
				ST::one() );

  // Make sure that the multiplication was successful
  testPostcondition( multiply_success == 0 );
  
  // Make sure that the transform was successful
  testPostcondition( ST::magnitude( transformed_point[2] ) < ST::prec() );

  // Return the point
  PointProjection new_point( transformed_point[0], transformed_point[1] );
  return new_point;
}

// Apply reverse transform to a point on the polygon
template<typename OrdinalType, typename ScalarType>
typename Polygon<OrdinalType,ScalarType>::Point
Polygon<OrdinalType,ScalarType>::applyReverseTransform( 
				       const PointProjection &xy_plane_point,
				       const Matrix &rotation_matrix,
				       const Vector &translation_vector )
{
  // Make sure that the rotation matrix is valid (3x3 and orthonormal)
  testPrecondition( rotation_matrix.numRows() == 3 );
  testPrecondition( rotation_matrix.numCols() == 3 );
  testPrecondition( LAP::isOrthonormal( rotation_matrix ) );

  // Convert the point to a vector (x' - x_0)
  Vector point = ThreeSpace::createVector( 
				 xy_plane_point.first - translation_vector[0],
				 xy_plane_point.second - translation_vector[1],
				 -translation_vector[2] );

  // Apply the reverse transformation ( x = R^T*(x' - x_0) )
  Vector transformed_point( translation_vector );
  remember( int multiply_success = )
    transformed_point.multiply( Teuchos::TRANS,
				Teuchos::NO_TRANS,
				ST::one(),
				rotation_matrix,
				point,
				ST::zero() );

  // Make sure that the multiplication was successful
  testPostcondition( multiply_success == 0 );

  // Return the point
  Point new_point( transformed_point[0], 
		   transformed_point[1],
		   transformed_point[2] );
  return new_point;
}

// Compute the area of a simplified polygon
template<typename OrdinalType,typename ScalarType>
ScalarType Polygon<OrdinalType,ScalarType>::calculateArea(
			 const std::list<PointProjection> &simplified_polygon )
{
  // The polygon must have at least 4 corners (3 + copy of first point)
  testPrecondition( simplified_polygon.size() >= 4 );

  typename std::list<PointProjection>::const_iterator first_corner, 
    second_corner, end_corner;
  
  first_corner = simplified_polygon.begin();
  
  second_corner = first_corner;
  ++second_corner;
  
  end_corner = simplified_polygon.end();

  ScalarType area = ST::zero();

  // A = 0.5 * Sum_{i=0}^{n-1}(x_i + x_{i+1})*(y_{i+1} - y_i)
  while( second_corner != end_corner )
  {
    area += (first_corner->first*second_corner->second - 
	     second_corner->first*first_corner->second);

    ++first_corner;
    ++second_corner;
  }

  area /= 2;

  // Make sure that the calculate area is physical
  testPostcondition( area > ST::zero() );
  testPostcondition( !ST::isnaninf( area ) );

  return area;
}

// Calculate the polygon centroid
template<typename OrdinalType,typename ScalarType>
typename Polygon<OrdinalType,ScalarType>::PointProjection
Polygon<OrdinalType,ScalarType>::calculateCentroid( 
			  const std::list<PointProjection> &simplified_polygon,
			  const ScalarType polygon_area )
{
  // The polygon must have at least 4 corners (3 + copy of first point)
  testPrecondition( simplified_polygon.size() >= 4 );

  PointProjection centroid;

  centroid.first = 
    Polygon<OrdinalType,ScalarType>::calculateCentroidXCoordinate( 
							    simplified_polygon,
							    polygon_area );

  centroid.second = 
    Polygon<OrdinalType,ScalarType>::calculateCentroidYCoordinate( 
							    simplified_polygon,
							    polygon_area );
  return centroid;
}

// Compute the x-coordinate of a simplified polygon centroid
template<typename OrdinalType,typename ScalarType>
ScalarType Polygon<OrdinalType,ScalarType>::calculateCentroidXCoordinate(
			  const std::list<PointProjection> &simplified_polygon,
			  const ScalarType polygon_area )
{
  // The polygon must have at least 4 corners (3 + copy of first point)
  testPrecondition( simplified_polygon.size() >= 4 );

  typename std::list<PointProjection>::const_iterator first_corner, 
    second_corner, end_corner;
  
  first_corner = simplified_polygon.begin();
  
  second_corner = first_corner;
  ++second_corner;
  
  end_corner = simplified_polygon.end();

  ScalarType centroid_x_coord = ST::zero();

  // x_c = (6*Area)^{-1} * Sum_{i=0}^{n-1}(x_{i+1}^2 + x_{i+1}*x_i + x_i^2)*
  //                                      (y_{i+1} - y_i)
  while( second_corner != end_corner )
  {
    centroid_x_coord += (first_corner->first + second_corner->first)*
      (first_corner->first*second_corner->second - 
       second_corner->first*first_corner->second);

    ++first_corner;
    ++second_corner;
  }

  centroid_x_coord /= 6*polygon_area;

  // Make sure that the calculated coordinate is physical
  testPostcondition( !ST::isnaninf( centroid_x_coord ) );
  
  return centroid_x_coord;
}

// Compute the y-coordinate of a simplified polygon centroid
template<typename OrdinalType,typename ScalarType>
ScalarType Polygon<OrdinalType,ScalarType>::calculateCentroidYCoordinate(
			  const std::list<PointProjection> &simplified_polygon,
			  const ScalarType polygon_area )
{
  // The polygon must have at least 4 corners (3 + copy of first point)
  testPrecondition( simplified_polygon.size() >= 4 );

  typename std::list<PointProjection>::const_iterator first_corner, 
    second_corner, end_corner;
  
  first_corner = simplified_polygon.begin();
  
  second_corner = first_corner;
  ++second_corner;
  
  end_corner = simplified_polygon.end();

  ScalarType centroid_y_coord = ST::zero();

  while( second_corner != end_corner )
  {
    centroid_y_coord += (first_corner->second + second_corner->second)*
      (first_corner->first*second_corner->second - 
       second_corner->first*first_corner->second);

    ++first_corner;
    ++second_corner;
  }

  centroid_y_coord /= 6*polygon_area;

  // Make sure that the calculate coordinate is physical
  testPostcondition( !ST::isnaninf( centroid_y_coord ) );

  return centroid_y_coord;
}

} // end FACEMC namespace

#endif // end POLYGON_DEF_HPP

//---------------------------------------------------------------------------//
// end Polygon_def.hpp
//---------------------------------------------------------------------------//

