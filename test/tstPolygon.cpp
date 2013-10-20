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

// FACEMC Includes
#include "FACEMC_UnitTestHarnessExtensions.hpp"
#include "Polygon.hpp"
#include "Vector.hpp"
#include "Matrix.hpp"
#include "MatrixHelpers.hpp"

//---------------------------------------------------------------------------//
// Instantiation Macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, short, float ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, short, double ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, int, float ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, int, double ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, long, float ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, long, double ) 

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
template<typename OrdinalType, typename ScalarType>
class TestPolygon : public FACEMC::Polygon<OrdinalType,ScalarType>
{
public:
  TestPolygon()
  { /* ... */ }

  virtual ~TestPolygon()
  { /* ... */ }

  // Allow public access to the protected member functions
  using FACEMC::Polygon<OrdinalType,ScalarType>::PointProjection;
  using FACEMC::Polygon<OrdinalType,ScalarType>::isValidPointList;
  using FACEMC::Polygon<OrdinalType,ScalarType>::hasCorrectSize;
  using FACEMC::Polygon<OrdinalType,ScalarType>::isClosed;
  using FACEMC::Polygon<OrdinalType,ScalarType>::hasNoConsecutiveRepeatedPoints;
  using FACEMC::Polygon<OrdinalType,ScalarType>::isInitializedProperly;
  using FACEMC::Polygon<OrdinalType,ScalarType>::hasAllPointsOnSamePlane;
  using FACEMC::Polygon<OrdinalType,ScalarType>::calculatePolygonPlaneUnitNormal;
  using FACEMC::Polygon<OrdinalType,ScalarType>::getExtremeCoordinates;
  using FACEMC::Polygon<OrdinalType,ScalarType>::getTransformMatrixAndVector;
  using FACEMC::Polygon<OrdinalType,ScalarType>::transformPolygon;
  using FACEMC::Polygon<OrdinalType,ScalarType>::applyTransform;
  using FACEMC::Polygon<OrdinalType,ScalarType>::applyReverseTransform;
  using FACEMC::Polygon<OrdinalType,ScalarType>::calculateArea;
  using FACEMC::Polygon<OrdinalType,ScalarType>::calculateCentroid;
  using FACEMC::Polygon<OrdinalType,ScalarType>::calculateCentroidXCoordinate;
  using FACEMC::Polygon<OrdinalType,ScalarType>::calculateCentroidYCoordinate;
};

//---------------------------------------------------------------------------//
// Testing Functions
//---------------------------------------------------------------------------//
// Create the corners of a triangle
template<typename CornerContainer>
void createThreeSpaceTriangle( CornerContainer &polygon_corners )
{
  polygon_corners.clear();
  
  // First point on origin
  typename CornerContainer::value_type corner_1( 0.0, 0.0, 0.0 );
  polygon_corners.push_back( corner_1 );
  
  // Second point at (1, 1, 1)
  typename CornerContainer::value_type corner_2( 1.0, 1.0, 1.0 );
  polygon_corners.push_back( corner_2 );

  // Third point at (1, 0, 0)
  typename CornerContainer::value_type corner_3( 1.0, 0.0, 0.0 );
  polygon_corners.push_back( corner_3 );

  // Add a copy of the first point
  polygon_corners.push_back( corner_1 );
}

// Create the corners of a square
template<typename CornerContainer>
void createSimpleThreeSpaceSquare( CornerContainer &polygon_corners )
{
  polygon_corners.clear();

  // First point at (1, 1, 1)
  typename CornerContainer::value_type corner_1( 1.0, 1.0, 1.0 );
  polygon_corners.push_back( corner_1 );

  // Second point at (-1, 1, 1)
  typename CornerContainer::value_type corner_2( -1.0, 1.0, 1.0 );
  polygon_corners.push_back( corner_2 );

  // Third point at (-1, 1, -1)
  typename CornerContainer::value_type corner_3( -1.0, 1.0, -1.0 );
  polygon_corners.push_back( corner_3 );

  // Fourth point at (1, 1, -1)
  typename CornerContainer::value_type corner_4( 1.0, 1.0, -1.0 );
  polygon_corners.push_back( corner_4 );

  // Add a copy of the first point
  polygon_corners.push_back( corner_1 );
}

// Create the corners of a complex square (internal square removed)
template<typename CornerContainer>
void createComplexThreeSpaceSquare( CornerContainer &polygon_corners )
{
  polygon_corners.clear();

  // First point at (2, 2, 2)
  typename CornerContainer::value_type corner_1( 2.0, 2.0, 2.0 );
  polygon_corners.push_back( corner_1 );

  // Second point at (2, -2, 2)
  typename CornerContainer::value_type corner_2( 2.0, -2.0, 2.0 );
  polygon_corners.push_back( corner_2 );

  // Third point at (2, -2, -2)
  typename CornerContainer::value_type corner_3( 2.0, -2.0, -2.0 );
  polygon_corners.push_back( corner_3 );

  // Fourth point at (2, 2, -2)
  typename CornerContainer::value_type corner_4( 2.0, 2.0, -2.0 );
  polygon_corners.push_back( corner_4 );

  // Add a copy of the first point
  polygon_corners.push_back( corner_1 );

  // Fifth point at (2, 1, 1)
  typename CornerContainer::value_type corner_5( 2.0, 1.0, 1.0 );
  polygon_corners.push_back( corner_5 );

  // Sixth point at (2, 1, -1)
  typename CornerContainer::value_type corner_6( 2.0, 1.0, -1.0 );
  polygon_corners.push_back( corner_6 );

  // Seventh point at (2, -1, -1)
  typename CornerContainer::value_type corner_7( 2.0, -1.0, -1.0 );
  polygon_corners.push_back( corner_7 );

  // Eigthth point at (2, -1, 1)
  typename CornerContainer::value_type corner_8( 2.0, -1.0, 1.0 );
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

  // First point at (1, 1, 1)
  typename CornerContainer::value_type corner_1( 1.0, 1.0, 1.0 );
  polygon_corners.push_back( corner_1 );

  // Second point at (-1, 1, 1)
  typename CornerContainer::value_type corner_2( -1.0, 1.0, 1.0 );
  polygon_corners.push_back( corner_2 );

  // Third point at (-1, 1, -1)
  typename CornerContainer::value_type corner_3( -1.0, 1.0, -1.0 );
  polygon_corners.push_back( corner_3 );

  // Fourth point at (1, 1, -1)
  typename CornerContainer::value_type corner_4( 1.0, 1.0, -1.0 );
  polygon_corners.push_back( corner_4 );

  // Add a copy of the first point
  polygon_corners.push_back( corner_1 );

  // Fifth point at (1, 1, 4)
  typename CornerContainer::value_type corner_5( 1.0, 1.0, 4.0 );
  polygon_corners.push_back( corner_5 );

  // Sixth point at (-1, 1, 4)
  typename CornerContainer::value_type corner_6( -1.0, 1.0, 4.0 );
  polygon_corners.push_back( corner_6 );

  // Seventh point at (-1, 1, 2)
  typename CornerContainer::value_type corner_7( -1.0, 1.0, 2.0 );
  polygon_corners.push_back( corner_7 );

  // Eighth point at (1, 1, 2 )
  typename CornerContainer::value_type corner_8( 1.0, 1.0, 2.0 );
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
  
  // First point at (1, 1, 1)
  typename CornerContainer::value_type corner_1( 1.0, 1.0, 1.0 );
  polygon_corners.push_back( corner_1 );

  // Second point at (-1, 1, 1)
  typename CornerContainer::value_type corner_2( -1.0, 1.0, 1.0 );
  polygon_corners.push_back( corner_2 );

  // Third point at (-1, 1, -1)
  typename CornerContainer::value_type corner_3( -1.0, 1.0, -1.0 );
  polygon_corners.push_back( corner_3 );
}

// Create an open polygon (first point not copied to the end
template<typename CornerContainer>
void createInvalidPolygonTypeB( CornerContainer &polygon_corners )
{
  polygon_corners.clear();

  // First point at (1, 1, 1)
  typename CornerContainer::value_type corner_1( 1.0, 1.0, 1.0 );
  polygon_corners.push_back( corner_1 );

  // Second point at (-1, 1, 1)
  typename CornerContainer::value_type corner_2( -1.0, 1.0, 1.0 );
  polygon_corners.push_back( corner_2 );

  // Third point at (-1, 1, -1)
  typename CornerContainer::value_type corner_3( -1.0, 1.0, -1.0 );
  polygon_corners.push_back( corner_3 );

  // Fourth point at (1, 1, -1)
  typename CornerContainer::value_type corner_4( 1.0, 1.0, -1.0 );
  polygon_corners.push_back( corner_4 );
}

// Create an invalid polygon (has consecutive repeated points)
template<typename CornerContainer>
void createInvalidPolygonTypeC( CornerContainer &polygon_corners )
{
  polygon_corners.clear();

  // First point at (1, 1, 1)
  typename CornerContainer::value_type corner_1( 1.0, 1.0, 1.0 );
  polygon_corners.push_back( corner_1 );

  // Second point at (-1, 1, 1)
  typename CornerContainer::value_type corner_2( -1.0, 1.0, 1.0 );
  polygon_corners.push_back( corner_2 );

  // Third point at (-1, 1, -1)
  typename CornerContainer::value_type corner_3( -1.0, 1.0, -1.0 );
  polygon_corners.push_back( corner_3 );
  polygon_corners.push_back( corner_3 );

  // Fourth point at (1, 1, -1)
  typename CornerContainer::value_type corner_4( 1.0, 1.0, -1.0 );
  polygon_corners.push_back( corner_4 );

  // Add a copy of the first point
  polygon_corners.push_back( corner_1 );
}

// Create an invalid polygon (first three points in a line)
template<typename CornerContainer>
void createInvalidPolygonTypeD( CornerContainer &polygon_corners )
{
  polygon_corners.clear();
  
  // First point at (1, 1, 1)
  typename CornerContainer::value_type corner_1( 1.0, 1.0, 1.0 );
  polygon_corners.push_back( corner_1 );
  
  // Second point at (2, 2, 2)
  typename CornerContainer::value_type corner_2( 2.0, 2.0, 2.0 );
  polygon_corners.push_back( corner_2 );
  
  // Third point at (3, 3, 3)
  typename CornerContainer::value_type corner_3( 3.0, 3.0, 3.0 );
  polygon_corners.push_back( corner_3 );

  // Add a copy of the first point
  polygon_corners.push_back( corner_1 );
}

// Create an invalid polygon (not all points on same plane)
template<typename CornerContainer>
void createInvalidPolygonTypeE( CornerContainer &polygon_corners )
{
  // First point at (1, 1, 1)
  typename CornerContainer::value_type corner_1( 1.0, 1.0, 1.0 );
  polygon_corners.push_back( corner_1 );

  // Second point at (-1, 1, 1)
  typename CornerContainer::value_type corner_2( -1.0, 1.0, 1.0 );
  polygon_corners.push_back( corner_2 );

  // Third point at (-1, 1, -1)
  typename CornerContainer::value_type corner_3( -1.0, 1.0, -1.0 );
  polygon_corners.push_back( corner_3 );

  // Fourth point at (1, 1, -1)
  typename CornerContainer::value_type corner_4( 1.0, 2.0, -1.0 );
  polygon_corners.push_back( corner_4 );

  // Add a copy of the first point
  polygon_corners.push_back( corner_1 );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the polygon can calculate its unit normal
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( Polygon,
				   calculatePolygonPlaneUnitNormal,
				   OrdinalType,
				   ScalarType )
{
  typedef TestPolygon<OrdinalType,ScalarType> Polygon;
  
  std::list<FACEMC::Vector<ScalarType> > polygon_corners;

  // Create a triangle
  createThreeSpaceTriangle( polygon_corners );

  // Get the unit normal to the polygon
  FACEMC::Vector<ScalarType> unit_normal = 
    Polygon::calculatePolygonPlaneUnitNormal( polygon_corners );

  // Assign the reference unit normal
  FACEMC::Vector<ScalarType> ref_unit_normal( 0.0, -1.0, 1.0 );
  
  TEST_ASSERT( unit_normal.isParallel( ref_unit_normal ) ||
	       unit_normal.isAntiparallel( ref_unit_normal ) );
}

UNIT_TEST_INSTANTIATION( Polygon, calculatePolygonPlaneUnitNormal );

//---------------------------------------------------------------------------//
// Check that a point list can be checked as having the correct size
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( Polygon,
				   hasCorrectSize,
				   OrdinalType,
				   ScalarType )
{
  typedef TestPolygon<OrdinalType,ScalarType> Polygon;
  
  std::list<FACEMC::Vector<ScalarType> > triangle_corners;
  std::list<FACEMC::Vector<ScalarType> > invalid_polygon_type_a;
  
  // Create a triangle
  createThreeSpaceTriangle( triangle_corners );

  // Create an invalid polygon
  createInvalidPolygonTypeA( invalid_polygon_type_a );

  TEST_ASSERT( Polygon::hasCorrectSize( triangle_corners ) );
  TEST_ASSERT( !Polygon::hasCorrectSize( invalid_polygon_type_a ) );
}

UNIT_TEST_INSTANTIATION( Polygon, hasCorrectSize );

//---------------------------------------------------------------------------//
// Check that a point list can be checked as being closed
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( Polygon,
				   isClosed,
				   OrdinalType,
				   ScalarType )
{
  typedef TestPolygon<OrdinalType,ScalarType> Polygon;

  std::list<FACEMC::Vector<ScalarType> > triangle_corners;
  std::list<FACEMC::Vector<ScalarType> > invalid_polygon_type_b;

  // Create a triangle
  createThreeSpaceTriangle( triangle_corners );

  // Create an invalid polygon
  createInvalidPolygonTypeB( invalid_polygon_type_b );

  TEST_ASSERT( Polygon::isClosed( triangle_corners ) );
  TEST_ASSERT( !Polygon::isClosed( invalid_polygon_type_b ) );
}

UNIT_TEST_INSTANTIATION( Polygon, isClosed );

//---------------------------------------------------------------------------//
// Check that the point list can be checked for consecutive repeated points
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( Polygon,
				   hasNoConsecutiveRepeatedPoints,
				   OrdinalType,
				   ScalarType )
{
  typedef TestPolygon<OrdinalType,ScalarType> Polygon;

  std::list<FACEMC::Vector<ScalarType> > triangle_corners;
  std::list<FACEMC::Vector<ScalarType> > invalid_polygon_type_c;

  // Create a triangle
  createThreeSpaceTriangle( triangle_corners );

  // Create an invalid polygon
  createInvalidPolygonTypeC( invalid_polygon_type_c );

  TEST_ASSERT( Polygon::hasNoConsecutiveRepeatedPoints( triangle_corners ) );
  TEST_ASSERT( !Polygon::hasNoConsecutiveRepeatedPoints( invalid_polygon_type_c ) );
}

UNIT_TEST_INSTANTIATION( Polygon, hasNoConsecutiveRepeatedPoints );

//---------------------------------------------------------------------------//
// Check that the initialization of a point list can be correctly checked
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( Polygon,
				   isInitializedProperly,
				   OrdinalType,
				   ScalarType )
{
  typedef TestPolygon<OrdinalType,ScalarType> Polygon;

  std::list<FACEMC::Vector<ScalarType> > triangle_corners;
  std::list<FACEMC::Vector<ScalarType> > invalid_polygon_type_d;

  // Create a triangle
  createThreeSpaceTriangle( triangle_corners );

  // Create an invalid polygon
  createInvalidPolygonTypeD( invalid_polygon_type_d );

  TEST_ASSERT( Polygon::isInitializedProperly( triangle_corners ) );
  TEST_ASSERT( !Polygon::isInitializedProperly( invalid_polygon_type_d ) );
}

UNIT_TEST_INSTANTIATION( Polygon, isInitializedProperly );

//---------------------------------------------------------------------------//
// Check that the point list can be tested as having all points on same plane
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( Polygon,
				   hasAllPointsOnSamePlane,
				   OrdinalType,
				   ScalarType )
{
  typedef TestPolygon<OrdinalType,ScalarType> Polygon;

  std::list<FACEMC::Vector<ScalarType> > triangle_corners;
  std::list<FACEMC::Vector<ScalarType> > simple_square_corners;
  std::list<FACEMC::Vector<ScalarType> > complex_square_corners;
  std::list<FACEMC::Vector<ScalarType> > disjoint_square_corners;
  std::list<FACEMC::Vector<ScalarType> > invalid_polygon_type_e;

  // Create a triangle
  createThreeSpaceTriangle( triangle_corners );

  // Create a simple square
  createSimpleThreeSpaceSquare( simple_square_corners );

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

UNIT_TEST_INSTANTIATION( Polygon, hasAllPointsOnSamePlane );

//---------------------------------------------------------------------------//
// Check that all points in the ordered list can be tested as on the same plane
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( Polygon,
				   isValidPointList,
				   OrdinalType,
				   ScalarType )
{
  typedef FACEMC::Polygon<OrdinalType,ScalarType> Polygon;
  
  std::list<FACEMC::Vector<ScalarType> > triangle_corners;
  std::list<FACEMC::Vector<ScalarType> > simple_square_corners;
  std::list<FACEMC::Vector<ScalarType> > complex_square_corners;
  std::list<FACEMC::Vector<ScalarType> > disjoint_square_corners;
  std::list<FACEMC::Vector<ScalarType> > invalid_polygon_type_a;
  std::list<FACEMC::Vector<ScalarType> > invalid_polygon_type_b;
  std::list<FACEMC::Vector<ScalarType> > invalid_polygon_type_c;
  std::list<FACEMC::Vector<ScalarType> > invalid_polygon_type_d;
  std::list<FACEMC::Vector<ScalarType> > invalid_polygon_type_e;

  // Create a triangle
  createThreeSpaceTriangle( triangle_corners );

  // Create a simple square
  createSimpleThreeSpaceSquare( simple_square_corners );

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

UNIT_TEST_INSTANTIATION( Polygon, isValidPointList );

//---------------------------------------------------------------------------//
// Check that the polygon can find its largest coordinates
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( Polygon,
				   getExtremeCoordinates,
				   OrdinalType,
				   ScalarType )
{
  typedef TestPolygon<OrdinalType,ScalarType> Polygon;
    
  std::list<FACEMC::Vector<ScalarType> > polygon_corners;
  FACEMC::Vector<ScalarType> min_coordinates;
  FACEMC::Vector<ScalarType> max_coordinates;

  // Create a triangle
  createThreeSpaceTriangle( polygon_corners );

  // Get the largest coordinates
  Polygon::getExtremeCoordinates( polygon_corners,
				  min_coordinates,
				  max_coordinates );

  FACEMC::Vector<ScalarType> ref_min_coordinates( 0.0, 0.0, 0.0 );
  FACEMC::Vector<ScalarType> ref_max_coordinates( 1.0, 1.0, 1.0 );

  TEST_EQUALITY( min_coordinates, ref_min_coordinates );
  TEST_EQUALITY( max_coordinates, ref_max_coordinates );
}

UNIT_TEST_INSTANTIATION( Polygon, getExtremeCoordinates );

//---------------------------------------------------------------------------//
// Check that the polygon can be transformed to a polygon in the x-y plane
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( Polygon,
				   transformPolygon,
				   OrdinalType,
				   ScalarType )
{
  typedef TestPolygon<OrdinalType,ScalarType> Polygon;
  typedef typename Polygon::PointProjection PointProjection;
  typedef Teuchos::ScalarTraits<ScalarType> ST;

  std::list<FACEMC::Vector<ScalarType> > polygon_corners;

  // Create a triangle
  createThreeSpaceTriangle( polygon_corners );

  // Calculate the polygon plane unit normal
  FACEMC::Vector<ScalarType> unit_normal = 
    Polygon::calculatePolygonPlaneUnitNormal( polygon_corners );

  // Create the transformation matrix and vector
  FACEMC::Matrix<ScalarType> rotation_matrix;
  FACEMC::Vector<ScalarType> translation_vector;
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
  
  FACEMC_TEST_FLOATING_EQUALITY( transformed_polygon_corners.front(),
				 ref_point_1,
				 ST::prec() );
  FACEMC_TEST_FLOATING_EQUALITY( *(++transformed_polygon_corners.begin()),
				 ref_point_2,
				 ST::prec() );
  FACEMC_TEST_FLOATING_EQUALITY( *(++(++transformed_polygon_corners.begin())),
				 ref_point_3,
				 ST::prec() );
}

UNIT_TEST_INSTANTIATION( Polygon, transformPolygon );

//---------------------------------------------------------------------------//
// Check that a transformed point can be reverse transformed
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( Polygon,
				   applyReverseTransform,
				   OrdinalType,
				   ScalarType )
{
  typedef Teuchos::ScalarTraits<ScalarType> ST;
  typedef TestPolygon<OrdinalType,ScalarType> Polygon;
  typedef typename Polygon::PointProjection PointProjection;

  std::list<FACEMC::Vector<ScalarType> > polygon_corners;

  // Create a triangle
  createThreeSpaceTriangle( polygon_corners );

  // Calculate the polygon plane unit normal
  FACEMC::Vector<ScalarType> unit_normal = 
    Polygon::calculatePolygonPlaneUnitNormal( polygon_corners );

  // Create the transformation matrix and vector
  FACEMC::Matrix<ScalarType> rotation_matrix;
  FACEMC::Vector<ScalarType> translation_vector;
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
  FACEMC::Vector<ScalarType> point_1 = Polygon::applyReverseTransform( 
					  transformed_polygon_corners.front(),
					  rotation_matrix,
					  translation_vector );
  FACEMC::Vector<ScalarType> point_2 = Polygon::applyReverseTransform(
				      *(++transformed_polygon_corners.begin()),
				      rotation_matrix,
				      translation_vector );

  FACEMC::Vector<ScalarType> point_3 = Polygon::applyReverseTransform(
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

UNIT_TEST_INSTANTIATION( Polygon, applyReverseTransform );

//---------------------------------------------------------------------------//
// Check that the area of a triangle can be calculated
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( Polygon,
				   calculateArea_triangle,
				   OrdinalType,
				   ScalarType )
{
  typedef Teuchos::ScalarTraits<ScalarType> ST;
  typedef TestPolygon<OrdinalType,ScalarType> Polygon;
  typedef typename Polygon::PointProjection PointProjection;

  std::list<FACEMC::Vector<ScalarType> > polygon_corners;

  // Create a triangle
  createThreeSpaceTriangle( polygon_corners );

  // Calculate the polygon plane unit normal
  FACEMC::Vector<ScalarType> unit_normal = 
    Polygon::calculatePolygonPlaneUnitNormal( polygon_corners );

  // Create the transformation matrix and vector
  FACEMC::Matrix<ScalarType> rotation_matrix;
  FACEMC::Vector<ScalarType> translation_vector;
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

UNIT_TEST_INSTANTIATION( Polygon, calculateArea_triangle );

//---------------------------------------------------------------------------//
// Check that the area of a simple square can be calculated
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( Polygon,
				   calculateArea_simple_square,
				   OrdinalType,
				   ScalarType )
{
  typedef TestPolygon<OrdinalType,ScalarType> Polygon;
  typedef typename Polygon::PointProjection PointProjection;
  typedef Teuchos::ScalarTraits<ScalarType> ST;

  std::list<FACEMC::Vector<ScalarType> > polygon_corners;

  // Create a triangle
  createSimpleThreeSpaceSquare( polygon_corners );

  // Calculate the polygon plane unit normal
  FACEMC::Vector<ScalarType> unit_normal = 
    Polygon::calculatePolygonPlaneUnitNormal( polygon_corners );

  // Create the transformation matrix and vector
  FACEMC::Matrix<ScalarType> rotation_matrix;
  FACEMC::Vector<ScalarType> translation_vector;
  
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

UNIT_TEST_INSTANTIATION( Polygon, calculateArea_simple_square );

//---------------------------------------------------------------------------//
// Check that the area of a complex square can be calculated
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( Polygon,
				   calculateArea_complex_square,
				   OrdinalType,
				   ScalarType )
{
  typedef Teuchos::ScalarTraits<ScalarType> ST;
  typedef TestPolygon<OrdinalType,ScalarType> Polygon;
  typedef typename Polygon::PointProjection PointProjection;

  std::list<FACEMC::Vector<ScalarType> > polygon_corners;

  // Create a triangle
  createComplexThreeSpaceSquare( polygon_corners );

  // Calculate the polygon plane unit normal
  FACEMC::Vector<ScalarType> unit_normal = 
    Polygon::calculatePolygonPlaneUnitNormal( polygon_corners );

  // Create the transformation matrix and vector
  FACEMC::Matrix<ScalarType> rotation_matrix;
  FACEMC::Vector<ScalarType> translation_vector;
  
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

UNIT_TEST_INSTANTIATION( Polygon, calculateArea_complex_square );

//---------------------------------------------------------------------------//
// Check that the centroid of a triangle can be calculated
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( Polygon,
				   calculateCentroid_triangle,
				   OrdinalType,
				   ScalarType )
{
  typedef Teuchos::ScalarTraits<ScalarType> ST;
  typedef FACEMC::Polygon<OrdinalType,ScalarType> Polygon;
  
  // Create the corners of the polygon
  std::list<FACEMC::Vector<ScalarType> > polygon_corners;
  
  createThreeSpaceTriangle( polygon_corners );

  // Create the polygon
  Polygon triangle( 0, polygon_corners );
  
  // Get the centroid of the polygon
  FACEMC::Vector<ScalarType> centroid = triangle.getCentroid();

  // Assign the reference centroid
  FACEMC::Vector<ScalarType> ref_centroid( 2.0/3.0, 1.0/3.0, 1.0/3.0 );

  TEST_COMPARE_FLOATING_ARRAYS( centroid(), ref_centroid(), ST::prec() );
}

UNIT_TEST_INSTANTIATION( Polygon, calculateCentroid_triangle );

//---------------------------------------------------------------------------//
// Check that the centroid of a simple square can be calculated
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( Polygon,
				   calculateCentroid_simple_square,
				   OrdinalType,
				   ScalarType )
{
  typedef Teuchos::ScalarTraits<ScalarType> ST;
  typedef FACEMC::Polygon<OrdinalType,ScalarType> Polygon;
    
  // Create the corners of the polygon
  std::list<FACEMC::Vector<ScalarType> > polygon_corners;
  
  createSimpleThreeSpaceSquare( polygon_corners );

  // Create the polygon
  Polygon square( 0, polygon_corners );
  
  // Get the centroid of the polygon
  FACEMC::Vector<ScalarType> centroid = square.getCentroid();

  // Assign the reference centroid
  FACEMC::Vector<ScalarType> ref_centroid( 0.0, 1.0, 0.0 );

  TEST_COMPARE_FLOATING_ARRAYS( centroid(), ref_centroid(), ST::prec() );
}

UNIT_TEST_INSTANTIATION( Polygon, calculateCentroid_simple_square );

//---------------------------------------------------------------------------//
// Check that the centroid of a complex square can be calculated
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( Polygon,
				   calculateCentroid_complex_square,
				   OrdinalType,
				   ScalarType )
{
  typedef Teuchos::ScalarTraits<ScalarType> ST;
  typedef FACEMC::Polygon<OrdinalType,ScalarType> Polygon;
    
  // Create the corners of the polygon
  std::list<FACEMC::Vector<ScalarType> > polygon_corners;
  
  createComplexThreeSpaceSquare( polygon_corners );

  // Create the polygon
  Polygon square( 0, polygon_corners );
  
  // Get the centroid of the polygon
  FACEMC::Vector<ScalarType> centroid = square.getCentroid();

  // Assign the reference centroid
  FACEMC::Vector<ScalarType> ref_centroid( 2.0, 0.0, 0.0 );

  TEST_COMPARE_FLOATING_ARRAYS( centroid(), ref_centroid(), ST::prec() );
}

UNIT_TEST_INSTANTIATION( Polygon, calculateCentroid_complex_square );

//---------------------------------------------------------------------------//
// end tstPolygon.cpp
//---------------------------------------------------------------------------//

