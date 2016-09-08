//---------------------------------------------------------------------------//
//!
//! \file   tstPolygon.cpp
//! \author Alex Robinson
//! \brief  Polygon class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Tuple.hpp>
#include <Teuchos_ArrayView.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Geometry_Polygon.hpp"
#include "Geometry_Vector.hpp"
#include "Geometry_Matrix.hpp"
#include "Geometry_MatrixHelpers.hpp"
#include "Geometry_IntersectionPoint.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_Empty.hpp"

//---------------------------------------------------------------------------//
// Instantiation Macros.
//---------------------------------------------------------------------------//
#define VEC_TYPEDEFS()					   \
  typedef Geometry::Vector<float>	vec_f;			   \
  typedef Geometry::Vector<double> vec_d;			   \

#define INTERSECTION_POINT_TYPEDEFS()				    \
  typedef Geometry::IntersectionPoint<short,float> intersection_s_f;  \
  typedef Geometry::IntersectionPoint<short,double> intersection_s_d; \
  typedef Geometry::IntersectionPoint<int,float> intersection_i_f;    \
  typedef Geometry::IntersectionPoint<int,double> intersection_i_d;   \
  typedef Geometry::IntersectionPoint<long,float> intersection_l_f;   \
  typedef Geometry::IntersectionPoint<long,double> intersection_l_d;

#define UNIT_TEST_INSTANTIATION_VEC( type, name )		   \
  VEC_TYPEDEFS()						   \
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, vec_f, short, float ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, vec_d, short, double ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, vec_f, int, float )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, vec_d, int, double ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, vec_f, long, float ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, vec_d, long, double ) \

#define UNIT_TEST_INSTANTIATION_INTERSECTION_PT( type, name )		\
  INTERSECTION_POINT_TYPEDEFS()						\
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, intersection_s_f, short, float ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, intersection_s_d, short, double ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, intersection_i_f, int, float )	\
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, intersection_i_d, int, double ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, intersection_l_f, long, float ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_3_INSTANT( type, name, intersection_l_d, long, double )

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
template<typename OrdinalType, typename ScalarType>
class TestPolygon : public Geometry::Polygon<OrdinalType,ScalarType>
{
public:
  TestPolygon()
  { /* ... */ }

  virtual ~TestPolygon()
  { /* ... */ }

  // Allow public access to the protected member functions
  using Geometry::Polygon<OrdinalType,ScalarType>::PointProjection;
  using Geometry::Polygon<OrdinalType,ScalarType>::isValidPointList;
  using Geometry::Polygon<OrdinalType,ScalarType>::hasCorrectSize;
  using Geometry::Polygon<OrdinalType,ScalarType>::isClosed;
  using Geometry::Polygon<OrdinalType,ScalarType>::hasNoConsecutiveRepeatedPoints;
  using Geometry::Polygon<OrdinalType,ScalarType>::isInitializedProperly;
  using Geometry::Polygon<OrdinalType,ScalarType>::hasAllPointsOnSamePlane;
  using Geometry::Polygon<OrdinalType,ScalarType>::calculatePolygonPlaneUnitNormal;
  using Geometry::Polygon<OrdinalType,ScalarType>::getExtremeCoordinates;
  using Geometry::Polygon<OrdinalType,ScalarType>::getTransformMatrixAndVector;
  using Geometry::Polygon<OrdinalType,ScalarType>::transformPolygon;
  using Geometry::Polygon<OrdinalType,ScalarType>::applyTransform;
  using Geometry::Polygon<OrdinalType,ScalarType>::applyReverseTransform;
  using Geometry::Polygon<OrdinalType,ScalarType>::calculateArea;
  using Geometry::Polygon<OrdinalType,ScalarType>::calculateCentroid;
  using Geometry::Polygon<OrdinalType,ScalarType>::calculateCentroidXCoordinate;
  using Geometry::Polygon<OrdinalType,ScalarType>::calculateCentroidYCoordinate;
};

template<typename T, typename T2 = Utility::Empty>
struct PointCreationPolicy
{
  typedef T scalarType;

  static inline T createPoint( const scalarType x,
			       const scalarType y,
			       const scalarType z )
  { return T::notDefined(); }
};

template<typename T>
struct PointCreationPolicy<Geometry::Vector<T> >
{
  typedef T scalarType;

  static inline Geometry::Vector<T> createPoint( const T x,
			       const T y,
			       const T z )
  { return Geometry::Vector<T>( x, y, z ); }
};

template<typename T, typename T2>
struct PointCreationPolicy<Geometry::IntersectionPoint<T,T2> >
{
  typedef T2 scalarType;

  static inline Geometry::IntersectionPoint<T,T2> createPoint(const scalarType x,
							    const scalarType y,
							    const scalarType z)
  { return Geometry::IntersectionPoint<T,T2>( x, y, z, 0, 1, 2 ); }
};

//---------------------------------------------------------------------------//
// Testing Functions
//---------------------------------------------------------------------------//
// Create the corners of a triangle
template<typename CornerContainer>
void createThreeSpaceTriangle( CornerContainer &polygon_corners )
{
  polygon_corners.clear();

  // Point class
  typedef typename CornerContainer::value_type Point;

  // Point creation policy class
  typedef PointCreationPolicy<typename CornerContainer::value_type> PCP;

  // First point on origin
  Point corner_1 = PCP::createPoint( 0.0, 0.0, 0.0 );
  polygon_corners.push_back( corner_1 );

  // Second point at (1, 1, 1)
  Point corner_2 = PCP::createPoint( 1.0, 1.0, 1.0 );
  polygon_corners.push_back( corner_2 );

  // Third point at (1, 0, 0)
  Point corner_3 = PCP::createPoint( 1.0, 0.0, 0.0 );
  polygon_corners.push_back( corner_3 );

  // Add a copy of the first point
  polygon_corners.push_back( corner_1 );
}

// Create the corners of a square perpendicular to y-axis
template<typename CornerContainer>
void createSimpleThreeSpaceSquareYAxis( CornerContainer &polygon_corners )
{
  polygon_corners.clear();

  // Point class
  typedef typename CornerContainer::value_type Point;

  // Point creation policy class
  typedef PointCreationPolicy<typename CornerContainer::value_type> PCP;

  // First point at (1, 1, 1)
  Point corner_1 = PCP::createPoint( 1.0, 1.0, 1.0 );
  polygon_corners.push_back( corner_1 );

  // Second point at (-1, 1, 1)
  Point corner_2 = PCP::createPoint( -1.0, 1.0, 1.0 );
  polygon_corners.push_back( corner_2 );

  // Third point at (-1, 1, -1)
  Point corner_3 = PCP::createPoint( -1.0, 1.0, -1.0 );
  polygon_corners.push_back( corner_3 );

  // Fourth point at (1, 1, -1)
  Point corner_4 = PCP::createPoint( 1.0, 1.0, -1.0 );
  polygon_corners.push_back( corner_4 );

  // Add a copy of the first point
  polygon_corners.push_back( corner_1 );
}

// Create the corners of a square perpendicular to z-axis
template<typename CornerContainer>
void createSimpleThreeSpaceSquareZAxis( CornerContainer &polygon_corners )
{
  polygon_corners.clear();

  // Point class
  typedef typename CornerContainer::value_type Point;

  // Point creation policy class
  typedef PointCreationPolicy<typename CornerContainer::value_type> PCP;

  // First point at (-1, 1, 1)
  Point corner_1 = PCP::createPoint( -1.0, 1.0, 1.0 );
  polygon_corners.push_back( corner_1 );

  // Second point at (1, 1, 1)
  Point corner_2 = PCP::createPoint( 1.0, 1.0, 1.0 );
  polygon_corners.push_back( corner_2 );

  // Third point at (1, -1, 1)
  Point corner_3 = PCP::createPoint( 1.0, -1.0, 1.0 );
  polygon_corners.push_back( corner_3 );

  // Fourth point at (-1, -1, 1)
  Point corner_4 = PCP::createPoint( -1.0, -1.0, 1.0 );
  polygon_corners.push_back( corner_4 );

  // Add a copy of the first point
  polygon_corners.push_back( corner_1 );
}

// Create the corners of a complex square (internal square removed)
template<typename CornerContainer>
void createComplexThreeSpaceSquare( CornerContainer &polygon_corners )
{
  polygon_corners.clear();

  // Point class
  typedef typename CornerContainer::value_type Point;

  // Point creation policy class
  typedef PointCreationPolicy<typename CornerContainer::value_type> PCP;

  // First point at (2, 2, 2)
  Point corner_1 = PCP::createPoint( 2.0, 2.0, 2.0 );
  polygon_corners.push_back( corner_1 );

  // Second point at (2, -2, 2)
  Point corner_2 = PCP::createPoint( 2.0, -2.0, 2.0 );
  polygon_corners.push_back( corner_2 );

  // Third point at (2, -2, -2)
  Point corner_3 = PCP::createPoint( 2.0, -2.0, -2.0 );
  polygon_corners.push_back( corner_3 );

  // Fourth point at (2, 2, -2)
  Point corner_4 = PCP::createPoint( 2.0, 2.0, -2.0 );
  polygon_corners.push_back( corner_4 );

  // Add a copy of the first point
  polygon_corners.push_back( corner_1 );

  // Fifth point at (2, 1, 1)
  Point corner_5 = PCP::createPoint( 2.0, 1.0, 1.0 );
  polygon_corners.push_back( corner_5 );

  // Sixth point at (2, 1, -1)
  Point corner_6 = PCP::createPoint( 2.0, 1.0, -1.0 );
  polygon_corners.push_back( corner_6 );

  // Seventh point at (2, -1, -1)
  Point corner_7 = PCP::createPoint( 2.0, -1.0, -1.0 );
  polygon_corners.push_back( corner_7 );

  // Eigthth point at (2, -1, 1)
  Point corner_8 = PCP::createPoint( 2.0, -1.0, 1.0 );
  polygon_corners.push_back( corner_8 );

  // Add a copy of the inner square start corner
  polygon_corners.push_back( corner_5 );

  // Add a copy of the first point
  polygon_corners.push_back( corner_1 );
}

// Create the corners of a disjoint square polygon
template<typename CornerContainer>
void createDisjointThreeSpaceSquare( CornerContainer &polygon_corners )
{
  polygon_corners.clear();

  // Point class
  typedef typename CornerContainer::value_type Point;

  // Point creation policy class
  typedef PointCreationPolicy<typename CornerContainer::value_type> PCP;

  // First point at (1, 1, 1)
  Point corner_1 = PCP::createPoint( 1.0, 1.0, 1.0 );
  polygon_corners.push_back( corner_1 );

  // Second point at (-1, 1, 1)
  Point corner_2 = PCP::createPoint( -1.0, 1.0, 1.0 );
  polygon_corners.push_back( corner_2 );

  // Third point at (-1, 1, -1)
  Point corner_3 = PCP::createPoint( -1.0, 1.0, -1.0 );
  polygon_corners.push_back( corner_3 );

  // Fourth point at (1, 1, -1)
  Point corner_4 = PCP::createPoint( 1.0, 1.0, -1.0 );
  polygon_corners.push_back( corner_4 );

  // Add a copy of the first point
  polygon_corners.push_back( corner_1 );

  // Fifth point at (1, 1, 4)
  Point corner_5 = PCP::createPoint( 1.0, 1.0, 4.0 );
  polygon_corners.push_back( corner_5 );

  // Sixth point at (-1, 1, 4)
  Point corner_6 = PCP::createPoint( -1.0, 1.0, 4.0 );
  polygon_corners.push_back( corner_6 );

  // Seventh point at (-1, 1, 2)
  Point corner_7 = PCP::createPoint( -1.0, 1.0, 2.0 );
  polygon_corners.push_back( corner_7 );

  // Eighth point at (1, 1, 2 )
  Point corner_8 = PCP::createPoint( 1.0, 1.0, 2.0 );
  polygon_corners.push_back( corner_8 );

  // Add a copy of the local first point
  polygon_corners.push_back( corner_5 );

  // Add a copy of the global first point
  polygon_corners.push_back( corner_1 );
}

// Create a polygon with an incorrect size
template<typename CornerContainer>
void createInvalidPolygonTypeA( CornerContainer &polygon_corners )
{
  polygon_corners.clear();

  // Point class
  typedef typename CornerContainer::value_type Point;

  // Point creation policy class
  typedef PointCreationPolicy<typename CornerContainer::value_type> PCP;

  // First point at (1, 1, 1)
  Point corner_1 = PCP::createPoint( 1.0, 1.0, 1.0 );
  polygon_corners.push_back( corner_1 );

  // Second point at (-1, 1, 1)
  Point corner_2 = PCP::createPoint( -1.0, 1.0, 1.0 );
  polygon_corners.push_back( corner_2 );

  // Third point at (-1, 1, -1)
  Point corner_3 = PCP::createPoint( -1.0, 1.0, -1.0 );
  polygon_corners.push_back( corner_3 );
}

// Create an open polygon (first point not copied to the end
template<typename CornerContainer>
void createInvalidPolygonTypeB( CornerContainer &polygon_corners )
{
  polygon_corners.clear();

  // Point class
  typedef typename CornerContainer::value_type Point;

  // Point creation policy class
  typedef PointCreationPolicy<typename CornerContainer::value_type> PCP;

  // First point at (1, 1, 1)
  Point corner_1 = PCP::createPoint( 1.0, 1.0, 1.0 );
  polygon_corners.push_back( corner_1 );

  // Second point at (-1, 1, 1)
  Point corner_2 = PCP::createPoint( -1.0, 1.0, 1.0 );
  polygon_corners.push_back( corner_2 );

  // Third point at (-1, 1, -1)
  Point corner_3 = PCP::createPoint( -1.0, 1.0, -1.0 );
  polygon_corners.push_back( corner_3 );

  // Fourth point at (1, 1, -1)
  Point corner_4 = PCP::createPoint( 1.0, 1.0, -1.0 );
  polygon_corners.push_back( corner_4 );
}

// Create an invalid polygon (has consecutive repeated points)
template<typename CornerContainer>
void createInvalidPolygonTypeC( CornerContainer &polygon_corners )
{
  polygon_corners.clear();

  // Point class
  typedef typename CornerContainer::value_type Point;

  // Point creation policy class
  typedef PointCreationPolicy<typename CornerContainer::value_type> PCP;

  // First point at (1, 1, 1)
  Point corner_1 = PCP::createPoint( 1.0, 1.0, 1.0 );
  polygon_corners.push_back( corner_1 );

  // Second point at (-1, 1, 1)
  Point corner_2 = PCP::createPoint( -1.0, 1.0, 1.0 );
  polygon_corners.push_back( corner_2 );

  // Third point at (-1, 1, -1)
  Point corner_3 = PCP::createPoint( -1.0, 1.0, -1.0 );
  polygon_corners.push_back( corner_3 );
  polygon_corners.push_back( corner_3 );

  // Fourth point at (1, 1, -1)
  Point corner_4 = PCP::createPoint( 1.0, 1.0, -1.0 );
  polygon_corners.push_back( corner_4 );

  // Add a copy of the first point
  polygon_corners.push_back( corner_1 );
}

// Create an invalid polygon (first three points in a line)
template<typename CornerContainer>
void createInvalidPolygonTypeD( CornerContainer &polygon_corners )
{
  polygon_corners.clear();

  // Point class
  typedef typename CornerContainer::value_type Point;

  // Point creation policy class
  typedef PointCreationPolicy<typename CornerContainer::value_type> PCP;

  // First point at (1, 1, 1)
  Point corner_1 = PCP::createPoint( 1.0, 1.0, 1.0 );
  polygon_corners.push_back( corner_1 );

  // Second point at (2, 2, 2)
  Point corner_2 = PCP::createPoint( 2.0, 2.0, 2.0 );
  polygon_corners.push_back( corner_2 );

  // Third point at (3, 3, 3)
  Point corner_3 = PCP::createPoint( 3.0, 3.0, 3.0 );
  polygon_corners.push_back( corner_3 );

  // Add a copy of the first point
  polygon_corners.push_back( corner_1 );
}

// Create an invalid polygon (not all points on same plane)
template<typename CornerContainer>
void createInvalidPolygonTypeE( CornerContainer &polygon_corners )
{
  polygon_corners.clear();

  // Point class
  typedef typename CornerContainer::value_type Point;

  // Point creation policy class
  typedef PointCreationPolicy<typename CornerContainer::value_type> PCP;

  // First point at (1, 1, 1)
  Point corner_1 = PCP::createPoint( 1.0, 1.0, 1.0 );
  polygon_corners.push_back( corner_1 );

  // Second point at (-1, 1, 1)
  Point corner_2 = PCP::createPoint( -1.0, 1.0, 1.0 );
  polygon_corners.push_back( corner_2 );

  // Third point at (-1, 1, -1)
  Point corner_3 = PCP::createPoint( -1.0, 1.0, -1.0 );
  polygon_corners.push_back( corner_3 );

  // Fourth point at (1, 1, -1)
  Point corner_4 = PCP::createPoint( 1.0, 2.0, -1.0 );
  polygon_corners.push_back( corner_4 );

  // Add a copy of the first point
  polygon_corners.push_back( corner_1 );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the polygon can calculate its unit normal
TEUCHOS_UNIT_TEST_TEMPLATE_3_DECL( Polygon,
				   calculatePolygonPlaneUnitNormal,
				   Point,
				   OrdinalType,
				   ScalarType )
{
  typedef TestPolygon<OrdinalType,ScalarType> Polygon;

  std::list<Point> polygon_corners;

  // Create a triangle
  createThreeSpaceTriangle( polygon_corners );

  // Get the unit normal to the polygon
  Geometry::Vector<ScalarType> unit_normal =
    Polygon::calculatePolygonPlaneUnitNormal( polygon_corners );

  // Assign the reference unit normal
  Geometry::Vector<ScalarType> ref_unit_normal( 0.0, -1.0, 1.0 );

  TEST_ASSERT( unit_normal.isParallel( ref_unit_normal ) ||
	       unit_normal.isAntiparallel( ref_unit_normal ) );
}

UNIT_TEST_INSTANTIATION_VEC( Polygon, calculatePolygonPlaneUnitNormal );
UNIT_TEST_INSTANTIATION_INTERSECTION_PT( Polygon,
					 calculatePolygonPlaneUnitNormal  );

//---------------------------------------------------------------------------//
// Check that a point list can be checked as having the correct size
TEUCHOS_UNIT_TEST_TEMPLATE_3_DECL( Polygon,
				   hasCorrectSize,
				   Point,
				   OrdinalType,
				   ScalarType )
{
  typedef TestPolygon<OrdinalType,ScalarType> Polygon;

  std::list<Point> triangle_corners;
  std::list<Point> invalid_polygon_type_a;

  // Create a triangle
  createThreeSpaceTriangle( triangle_corners );

  // Create an invalid polygon
  createInvalidPolygonTypeA( invalid_polygon_type_a );

  TEST_ASSERT( Polygon::hasCorrectSize( triangle_corners ) );
  TEST_ASSERT( !Polygon::hasCorrectSize( invalid_polygon_type_a ) );
}

UNIT_TEST_INSTANTIATION_VEC( Polygon, hasCorrectSize );
UNIT_TEST_INSTANTIATION_INTERSECTION_PT( Polygon, hasCorrectSize );

//---------------------------------------------------------------------------//
// Check that a point list can be checked as being closed
TEUCHOS_UNIT_TEST_TEMPLATE_3_DECL( Polygon,
				   isClosed,
				   Point,
				   OrdinalType,
				   ScalarType )
{
  typedef TestPolygon<OrdinalType,ScalarType> Polygon;

  std::list<Point> triangle_corners;
  std::list<Point> invalid_polygon_type_b;

  // Create a triangle
  createThreeSpaceTriangle( triangle_corners );

  // Create an invalid polygon
  createInvalidPolygonTypeB( invalid_polygon_type_b );

  TEST_ASSERT( Polygon::isClosed( triangle_corners ) );
  TEST_ASSERT( !Polygon::isClosed( invalid_polygon_type_b ) );
}

UNIT_TEST_INSTANTIATION_VEC( Polygon, isClosed );
UNIT_TEST_INSTANTIATION_INTERSECTION_PT( Polygon, isClosed );

//---------------------------------------------------------------------------//
// Check that the point list can be checked for consecutive repeated points
TEUCHOS_UNIT_TEST_TEMPLATE_3_DECL( Polygon,
				   hasNoConsecutiveRepeatedPoints,
				   Point,
				   OrdinalType,
				   ScalarType )
{
  typedef TestPolygon<OrdinalType,ScalarType> Polygon;

  std::list<Point> triangle_corners;
  std::list<Point> invalid_polygon_type_c;

  // Create a triangle
  createThreeSpaceTriangle( triangle_corners );

  // Create an invalid polygon
  createInvalidPolygonTypeC( invalid_polygon_type_c );

  TEST_ASSERT( Polygon::hasNoConsecutiveRepeatedPoints( triangle_corners ) );
  TEST_ASSERT( !Polygon::hasNoConsecutiveRepeatedPoints( invalid_polygon_type_c ) );
}

UNIT_TEST_INSTANTIATION_VEC( Polygon, hasNoConsecutiveRepeatedPoints );
UNIT_TEST_INSTANTIATION_INTERSECTION_PT( Polygon,
					 hasNoConsecutiveRepeatedPoints );

//---------------------------------------------------------------------------//
// Check that the initialization of a point list can be correctly checked
TEUCHOS_UNIT_TEST_TEMPLATE_3_DECL( Polygon,
				   isInitializedProperly,
				   Point,
				   OrdinalType,
				   ScalarType )
{
  typedef TestPolygon<OrdinalType,ScalarType> Polygon;

  std::list<Point> triangle_corners;
  std::list<Point> invalid_polygon_type_d;

  // Create a triangle
  createThreeSpaceTriangle( triangle_corners );

  // Create an invalid polygon
  createInvalidPolygonTypeD( invalid_polygon_type_d );

  TEST_ASSERT( Polygon::isInitializedProperly( triangle_corners ) );
  TEST_ASSERT( !Polygon::isInitializedProperly( invalid_polygon_type_d ) );
}

UNIT_TEST_INSTANTIATION_VEC( Polygon, isInitializedProperly );
UNIT_TEST_INSTANTIATION_INTERSECTION_PT( Polygon, isInitializedProperly );

//---------------------------------------------------------------------------//
// Check that the point list can be tested as having all points on same plane
TEUCHOS_UNIT_TEST_TEMPLATE_3_DECL( Polygon,
				   hasAllPointsOnSamePlane,
				   Point,
				   OrdinalType,
				   ScalarType )
{
  typedef TestPolygon<OrdinalType,ScalarType> Polygon;

  std::list<Point> triangle_corners;
  std::list<Point> simple_square_corners;
  std::list<Point> complex_square_corners;
  std::list<Point> disjoint_square_corners;
  std::list<Point> invalid_polygon_type_e;

  // Create a triangle
  createThreeSpaceTriangle( triangle_corners );

  // Create a simple square
  createSimpleThreeSpaceSquareYAxis( simple_square_corners );

  // Create a complex square
  createComplexThreeSpaceSquare( complex_square_corners );

  // Create a disjoint square
  createDisjointThreeSpaceSquare( disjoint_square_corners );

  // Create an invalid polygon
  createInvalidPolygonTypeE( invalid_polygon_type_e );

  TEST_ASSERT( Polygon::hasAllPointsOnSamePlane( triangle_corners ) );
  TEST_ASSERT( Polygon::hasAllPointsOnSamePlane( simple_square_corners ) );
  TEST_ASSERT( Polygon::hasAllPointsOnSamePlane( complex_square_corners ) );
  TEST_ASSERT( Polygon::hasAllPointsOnSamePlane( disjoint_square_corners ) );
  TEST_ASSERT( !Polygon::hasAllPointsOnSamePlane( invalid_polygon_type_e ) );
}

UNIT_TEST_INSTANTIATION_VEC( Polygon, hasAllPointsOnSamePlane );
UNIT_TEST_INSTANTIATION_INTERSECTION_PT( Polygon, hasAllPointsOnSamePlane );

//---------------------------------------------------------------------------//
// Check that all points in the ordered list can be tested as on the same plane
TEUCHOS_UNIT_TEST_TEMPLATE_3_DECL( Polygon,
				   isValidPointList,
				   Point,
				   OrdinalType,
				   ScalarType )
{
  typedef Geometry::Polygon<OrdinalType,ScalarType> Polygon;

  std::list<Point> triangle_corners;
  std::list<Point> simple_square_corners;
  std::list<Point> complex_square_corners;
  std::list<Point> disjoint_square_corners;
  std::list<Point> invalid_polygon_type_a;
  std::list<Point> invalid_polygon_type_b;
  std::list<Point> invalid_polygon_type_c;
  std::list<Point> invalid_polygon_type_d;
  std::list<Point> invalid_polygon_type_e;

  // Create a triangle
  createThreeSpaceTriangle( triangle_corners );

  // Create a simple square
  createSimpleThreeSpaceSquareYAxis( simple_square_corners );

  // Create a complex square
  createComplexThreeSpaceSquare( complex_square_corners );

  // Create a disjoint square
  createDisjointThreeSpaceSquare( disjoint_square_corners );

  // Create an invalid polygon
  createInvalidPolygonTypeA( invalid_polygon_type_a );
  createInvalidPolygonTypeB( invalid_polygon_type_b );
  createInvalidPolygonTypeC( invalid_polygon_type_c );
  createInvalidPolygonTypeD( invalid_polygon_type_d );
  createInvalidPolygonTypeE( invalid_polygon_type_e );


  TEST_ASSERT( Polygon::isValidPointList( triangle_corners ) );
  TEST_ASSERT( Polygon::isValidPointList( simple_square_corners ) );
  TEST_ASSERT( Polygon::isValidPointList( complex_square_corners ) );
  TEST_ASSERT( Polygon::isValidPointList( disjoint_square_corners ) );
  TEST_ASSERT( !Polygon::isValidPointList( invalid_polygon_type_a ) );
  TEST_ASSERT( !Polygon::isValidPointList( invalid_polygon_type_b ) );
  TEST_ASSERT( !Polygon::isValidPointList( invalid_polygon_type_c ) );
  TEST_ASSERT( !Polygon::isValidPointList( invalid_polygon_type_d ) );
  TEST_ASSERT( !Polygon::isValidPointList( invalid_polygon_type_e ) );
}

UNIT_TEST_INSTANTIATION_VEC( Polygon, isValidPointList );
UNIT_TEST_INSTANTIATION_INTERSECTION_PT( Polygon, isValidPointList );

//---------------------------------------------------------------------------//
// Check that the polygon can find its largest coordinates
TEUCHOS_UNIT_TEST_TEMPLATE_3_DECL( Polygon,
				   getExtremeCoordinates,
				   Point,
				   OrdinalType,
				   ScalarType )
{
  typedef TestPolygon<OrdinalType,ScalarType> Polygon;

  std::list<Point> polygon_corners;
  Geometry::Vector<ScalarType> min_coordinates;
  Geometry::Vector<ScalarType> max_coordinates;

  // Create a triangle
  createThreeSpaceTriangle( polygon_corners );

  // Get the largest coordinates
  Polygon::getExtremeCoordinates( polygon_corners,
				  min_coordinates,
				  max_coordinates );

  Geometry::Vector<ScalarType> ref_min_coordinates( 0.0, 0.0, 0.0 );
  Geometry::Vector<ScalarType> ref_max_coordinates( 1.0, 1.0, 1.0 );

  TEST_EQUALITY( min_coordinates, ref_min_coordinates );
  TEST_EQUALITY( max_coordinates, ref_max_coordinates );
}

UNIT_TEST_INSTANTIATION_VEC( Polygon, getExtremeCoordinates );

//---------------------------------------------------------------------------//
// Check that the polygon can be transformed to a polygon in the x-y plane
TEUCHOS_UNIT_TEST_TEMPLATE_3_DECL( Polygon,
				   transformPolygon,
				   Point,
				   OrdinalType,
				   ScalarType )
{
  typedef TestPolygon<OrdinalType,ScalarType> Polygon;
  typedef typename Polygon::PointProjection PointProjection;
  typedef Teuchos::ScalarTraits<ScalarType> ST;

  std::list<Point> polygon_corners;

  // Create a triangle
  createThreeSpaceTriangle( polygon_corners );

  // Calculate the polygon plane unit normal
  Geometry::Vector<ScalarType> unit_normal =
    Polygon::calculatePolygonPlaneUnitNormal( polygon_corners );

  // Create the transformation matrix and vector
  Geometry::Matrix<ScalarType> rotation_matrix;
  Geometry::Vector<ScalarType> translation_vector;
  Polygon::getTransformMatrixAndVector( unit_normal,
					polygon_corners.front(),
					rotation_matrix,
					translation_vector );

  // Transform the polygon
  std::list<PointProjection> transformed_polygon_corners(
						      polygon_corners.size() );
  Polygon::transformPolygon( polygon_corners,
			     transformed_polygon_corners,
			     rotation_matrix,
			     translation_vector );

  // Reference transformed corners
  PointProjection ref_point_1( 0.0, 0.0 );
  PointProjection ref_point_2( -ST::squareroot( 2.0 ), -1.0 );
  PointProjection ref_point_3( 0.0, -1.0 );

  UTILITY_TEST_FLOATING_EQUALITY( transformed_polygon_corners.front(),
				 ref_point_1,
				 ST::prec() );
  UTILITY_TEST_FLOATING_EQUALITY( *(++transformed_polygon_corners.begin()),
				 ref_point_2,
				 ST::prec() );
  UTILITY_TEST_FLOATING_EQUALITY( *(++(++transformed_polygon_corners.begin())),
				 ref_point_3,
				 ST::prec() );
}

UNIT_TEST_INSTANTIATION_VEC( Polygon, transformPolygon );

//---------------------------------------------------------------------------//
// Check that a transformed point can be reverse transformed
TEUCHOS_UNIT_TEST_TEMPLATE_3_DECL( Polygon,
				   applyReverseTransform,
				   Point,
				   OrdinalType,
				   ScalarType )
{
  typedef Teuchos::ScalarTraits<ScalarType> ST;
  typedef TestPolygon<OrdinalType,ScalarType> Polygon;
  typedef typename Polygon::PointProjection PointProjection;

  std::list<Point> polygon_corners;

  // Create a triangle
  createThreeSpaceTriangle( polygon_corners );

  // Calculate the polygon plane unit normal
  Geometry::Vector<ScalarType> unit_normal =
    Polygon::calculatePolygonPlaneUnitNormal( polygon_corners );

  // Create the transformation matrix and vector
  Geometry::Matrix<ScalarType> rotation_matrix;
  Geometry::Vector<ScalarType> translation_vector;
  Polygon::getTransformMatrixAndVector( unit_normal,
					polygon_corners.front(),
					rotation_matrix,
					translation_vector );

  // Transform the polygon
  std::list<PointProjection> transformed_polygon_corners(
						      polygon_corners.size() );
  Polygon::transformPolygon( polygon_corners,
			     transformed_polygon_corners,
			     rotation_matrix,
			     translation_vector );

  // Reverse transform the transformed corners
  Geometry::Vector<ScalarType> point_1 = Polygon::applyReverseTransform(
					  transformed_polygon_corners.front(),
					  rotation_matrix,
					  translation_vector );
  Geometry::Vector<ScalarType> point_2 = Polygon::applyReverseTransform(
				      *(++transformed_polygon_corners.begin()),
				      rotation_matrix,
				      translation_vector );

  Geometry::Vector<ScalarType> point_3 = Polygon::applyReverseTransform(
				  *(++(++transformed_polygon_corners.begin())),
				  rotation_matrix,
				  translation_vector );

  TEST_COMPARE_FLOATING_ARRAYS( point_1(),
				polygon_corners.front().view(),
				 ST::prec() );
  TEST_COMPARE_FLOATING_ARRAYS( point_2(),
				(*(++polygon_corners.begin())).view(),
				ST::prec() );
  TEST_COMPARE_FLOATING_ARRAYS( point_3(),
				(*(++(++polygon_corners.begin()))).view(),
				ST::prec() );
}

UNIT_TEST_INSTANTIATION_VEC( Polygon, applyReverseTransform );

//---------------------------------------------------------------------------//
// Check that the area of a triangle can be calculated
TEUCHOS_UNIT_TEST_TEMPLATE_3_DECL( Polygon,
				   calculateArea_triangle,
				   Point,
				   OrdinalType,
				   ScalarType )
{
  typedef Teuchos::ScalarTraits<ScalarType> ST;
  typedef TestPolygon<OrdinalType,ScalarType> Polygon;
  typedef typename Polygon::PointProjection PointProjection;

  std::list<Point> polygon_corners;

  // Create a triangle
  createThreeSpaceTriangle( polygon_corners );

  // Calculate the polygon plane unit normal
  Geometry::Vector<ScalarType> unit_normal =
    Polygon::calculatePolygonPlaneUnitNormal( polygon_corners );

  // Create the transformation matrix and vector
  Geometry::Matrix<ScalarType> rotation_matrix;
  Geometry::Vector<ScalarType> translation_vector;
  Polygon::getTransformMatrixAndVector( unit_normal,
					polygon_corners.front(),
					rotation_matrix,
					translation_vector );

  // Transform the polygon
  std::list<PointProjection> transformed_polygon_corners(
						      polygon_corners.size() );
  Polygon::transformPolygon( polygon_corners,
			     transformed_polygon_corners,
			     rotation_matrix,
			     translation_vector );

  // Calculate the polygon area
  ScalarType area = Polygon::calculateArea( transformed_polygon_corners );

  // Assign the reference polygon area
  ScalarType ref_area = ST::squareroot( 2.0 )/2;

  TEST_FLOATING_EQUALITY( area, ref_area, ST::prec() );
}

UNIT_TEST_INSTANTIATION_VEC( Polygon, calculateArea_triangle );

//---------------------------------------------------------------------------//
// Check that the area of a simple square can be calculated
TEUCHOS_UNIT_TEST_TEMPLATE_3_DECL( Polygon,
				   calculateArea_simple_square,
				   Point,
				   OrdinalType,
				   ScalarType )
{
  typedef TestPolygon<OrdinalType,ScalarType> Polygon;
  typedef typename Polygon::PointProjection PointProjection;
  typedef Teuchos::ScalarTraits<ScalarType> ST;

  std::list<Point> polygon_corners;

  // Create a square perpendicular to the y-axis
  createSimpleThreeSpaceSquareYAxis( polygon_corners );

  // Calculate the polygon plane unit normal
  Geometry::Vector<ScalarType> unit_normal =
    Polygon::calculatePolygonPlaneUnitNormal( polygon_corners );

  // Create the transformation matrix and vector
  Geometry::Matrix<ScalarType> rotation_matrix;
  Geometry::Vector<ScalarType> translation_vector;

  Polygon::getTransformMatrixAndVector( unit_normal,
					polygon_corners.front(),
					rotation_matrix,
					translation_vector );

  // Transform the polygon
  std::list<PointProjection> transformed_polygon_corners(
						      polygon_corners.size() );
  Polygon::transformPolygon( polygon_corners,
			     transformed_polygon_corners,
			     rotation_matrix,
			     translation_vector );

  // Calculate the polygon area
  ScalarType area = Polygon::calculateArea( transformed_polygon_corners );

  // Assign the reference polygon area
  ScalarType ref_area = 4.0;

  TEST_FLOATING_EQUALITY( area, ref_area, ST::prec() );
}

UNIT_TEST_INSTANTIATION_VEC( Polygon, calculateArea_simple_square );

//---------------------------------------------------------------------------//
// Check that the area of a complex square can be calculated
TEUCHOS_UNIT_TEST_TEMPLATE_3_DECL( Polygon,
				   calculateArea_complex_square,
				   Point,
				   OrdinalType,
				   ScalarType )
{
  typedef Teuchos::ScalarTraits<ScalarType> ST;
  typedef TestPolygon<OrdinalType,ScalarType> Polygon;
  typedef typename Polygon::PointProjection PointProjection;

  std::list<Point> polygon_corners;

  // Create a triangle
  createComplexThreeSpaceSquare( polygon_corners );

  // Calculate the polygon plane unit normal
  Geometry::Vector<ScalarType> unit_normal =
    Polygon::calculatePolygonPlaneUnitNormal( polygon_corners );

  // Create the transformation matrix and vector
  Geometry::Matrix<ScalarType> rotation_matrix;
  Geometry::Vector<ScalarType> translation_vector;

  Polygon::getTransformMatrixAndVector( unit_normal,
					polygon_corners.front(),
					rotation_matrix,
					translation_vector );

  // Transform the polygon
  std::list<PointProjection> transformed_polygon_corners(
						      polygon_corners.size() );
  Polygon::transformPolygon( polygon_corners,
			     transformed_polygon_corners,
			     rotation_matrix,
			     translation_vector );

  // Calculate the polygon area
  ScalarType area = Polygon::calculateArea( transformed_polygon_corners );

  // Assign the reference polygon area
  ScalarType ref_area = 12.0;

  TEST_FLOATING_EQUALITY( area, ref_area, ST::prec() );
}

UNIT_TEST_INSTANTIATION_VEC( Polygon, calculateArea_complex_square );

//---------------------------------------------------------------------------//
// Check that the centroid of a triangle can be calculated
TEUCHOS_UNIT_TEST_TEMPLATE_3_DECL( Polygon,
				   calculateCentroid_triangle,
				   Point,
				   OrdinalType,
				   ScalarType )
{
  typedef Teuchos::ScalarTraits<ScalarType> ST;
  typedef Geometry::Polygon<OrdinalType,ScalarType> Polygon;

  // Create the corners of the polygon
  std::list<Point> polygon_corners;

  createThreeSpaceTriangle( polygon_corners );

  // Create the polygon
  Polygon triangle( 0, polygon_corners );

  // Get the centroid of the polygon
  Geometry::Vector<ScalarType> centroid = triangle.getCentroid();

  // Assign the reference centroid
  Geometry::Vector<ScalarType> ref_centroid( 2.0/3.0, 1.0/3.0, 1.0/3.0 );

  TEST_COMPARE_FLOATING_ARRAYS( centroid(), ref_centroid(), ST::prec() );
}

UNIT_TEST_INSTANTIATION_VEC( Polygon, calculateCentroid_triangle );
UNIT_TEST_INSTANTIATION_INTERSECTION_PT( Polygon, calculateCentroid_triangle );

//---------------------------------------------------------------------------//
// Check that the centroid of a simple square can be calculated
TEUCHOS_UNIT_TEST_TEMPLATE_3_DECL( Polygon,
				   calculateCentroid_simple_square,
				   Point,
				   OrdinalType,
				   ScalarType )
{
  typedef Teuchos::ScalarTraits<ScalarType> ST;
  typedef Geometry::Polygon<OrdinalType,ScalarType> Polygon;

  // Create the corners of the polygon
  std::list<Point> polygon_corners;

  createSimpleThreeSpaceSquareZAxis( polygon_corners );

  // Create the polygon
  Polygon square( 0, polygon_corners );

  // Get the centroid of the polygon
  Geometry::Vector<ScalarType> centroid = square.getCentroid();

  // Assign the reference centroid
  Geometry::Vector<ScalarType> ref_centroid( 0.0, 0.0, 1.0 );

  TEST_COMPARE_FLOATING_ARRAYS( centroid(), ref_centroid(), ST::prec() );
}

UNIT_TEST_INSTANTIATION_VEC( Polygon, calculateCentroid_simple_square );
UNIT_TEST_INSTANTIATION_INTERSECTION_PT( Polygon,
					 calculateCentroid_simple_square );

//---------------------------------------------------------------------------//
// Check that the centroid of a complex square can be calculated
TEUCHOS_UNIT_TEST_TEMPLATE_3_DECL( Polygon,
				   calculateCentroid_complex_square,
				   Point,
				   OrdinalType,
				   ScalarType )
{
  typedef Teuchos::ScalarTraits<ScalarType> ST;
  typedef Geometry::Polygon<OrdinalType,ScalarType> Polygon;

  // Create the corners of the polygon
  std::list<Point> polygon_corners;

  createComplexThreeSpaceSquare( polygon_corners );

  // Create the polygon
  Polygon square( 0, polygon_corners );

  // Get the centroid of the polygon
  Geometry::Vector<ScalarType> centroid = square.getCentroid();

  // Assign the reference centroid
  Geometry::Vector<ScalarType> ref_centroid( 2.0, 0.0, 0.0 );

  TEST_COMPARE_FLOATING_ARRAYS( centroid(), ref_centroid(), ST::prec() );
}

UNIT_TEST_INSTANTIATION_VEC( Polygon, calculateCentroid_complex_square );
UNIT_TEST_INSTANTIATION_INTERSECTION_PT( Polygon,
					 calculateCentroid_complex_square );

//---------------------------------------------------------------------------//
// end tstPolygon.cpp
//---------------------------------------------------------------------------//

