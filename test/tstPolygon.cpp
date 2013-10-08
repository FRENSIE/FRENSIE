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
#include "ThreeSpaceTraitsAndPolicy.hpp"
#include "LinearAlgebraPolicy.hpp"

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
template<typename CornerContainer>
void createThreeSpaceTriangle( CornerContainer &polygon_corners )
{
  polygon_corners.clear();
  
  // First point on origin
  typename CornerContainer::value_type corner( 0.0, 0.0, 0.0 );
  polygon_corners.push_back( corner );
  
  // Second point at (1, 1, 1)
  corner( 1.0, 1.0, 1.0 );
  polygon_corners.push_back( corner );

  // Third point at (1, 0, 0)
  corner( 1.0, 0.0, 0.0 );
  polygon_corners.push_back( corner );

  // Add a copy of the first point
  polygon_corners.push_back( polygon_corners.front() );
}

template<typename CornerContainer>
void createSimpleThreeSpaceSquare( CornerContainer &polygon_corners )
{
  polygon_corners.clear();

  // First point at (1, 1, 1)
  typename CornerContainer::value_type corner( 1.0, 1.0, 1.0 );
  polygon_corners.push_back( corner );

  // Second point at (-1, 1, 1)
  corner( -1.0, 1.0, 1.0 );
  polygon_corners.push_back( corner );

  // Third point at (-1, 1, -1)
  corner( -1.0, 1.0, -1.0 );
  polygon_corners.push_back( corner );

  // Fourth point at (1, 1, -1)
  corner( 1.0, 1.0, -1.0 );
  polygon_corners.push_back( corner );

  // Add a copy of the first point
  polygon_corners.push_back( polygon_corners.front() );
}

template<typename CornerContainer>
void createComplexThreeSpaceSquare( CornerContainer &polygon_corners )
{
  polygon_corners.clear();

  // First point at (2, 2, 2)
  typename CornerContainer::value_type corner( 2.0, 2.0, 2.0 );
  polygon_corners.push_back( corner );

  // Second point at (2, -2, 2)
  corner( 2.0, -2.0, 2.0 );
  polygon_corners.push_back( corner );

  // Third point at (2, -2, -2)
  corner( 2.0, -2.0, -2.0 );
  polygon_corners.push_back( corner );

  // Fourth point at (2, 2, -2)
  corner( 2.0, 2.0, -2.0 );
  polygon_corners.push_back( corner );

  // Add a copy of the first point
  polygon_corners.push_back( polygon_corners.front() );

  // Fifth point at (2, 1, 1)
  corner( 2.0, 1.0, 1.0 );
  polygon_corners.push_back( corner );

  // Store the inner square start corner
  typename CornerContainer::value_type inner_start_corner = corner;

  // Sixth point at (2, 1, -1)
  corner( 2.0, 1.0, -1.0 );
  polygon_corners.push_back( corner );

  // Seventh point at (2, -1, -1)
  corner( 2.0, -1.0, -1.0 );
  polygon_corners.push_back( corner );

  // Eigthth point at (2, -1, 1)
  corner( 2.0, -1.0, 1.0 );
  polygon_corners.push_back( corner );

  // Add a copy of the inner square start corner
  polygon_corners.push_back( inner_start_corner );

  // Add a copy of the first point
  polygon_corners.push_back( polygon_corners.front() );
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
  typedef FACEMC::ThreeSpaceTraitsAndPolicy<ScalarType> ThreeSpace;
  typedef FACEMC::LinearAlgebraPolicy<ScalarType> LAP;
  typedef Teuchos::ScalarTraits<ScalarType> ST;
  typedef TestPolygon<OrdinalType,ScalarType> Polygon;
  typedef typename Polygon::Point Point;
  
  std::list<Point> polygon_corners;

  // Create a triangle
  createThreeSpaceTriangle( polygon_corners );

  // Get the unit normal to the polygon
  typename ThreeSpace::Vector unit_normal = 
    Polygon::calculatePolygonPlaneUnitNormal( polygon_corners );

  // Assign the reference unit normal
  typename ThreeSpace::Vector ref_unit_normal =
    ThreeSpace::createVector( ST::zero(), -ST::one(), ST::one() );
  
  TEST_ASSERT( LAP::isParallel( unit_normal, ref_unit_normal ) ||
	       LAP::isAntiparallel( unit_normal, ref_unit_normal ) );
}

UNIT_TEST_INSTANTIATION( Polygon, calculatePolygonPlaneUnitNormal );

//---------------------------------------------------------------------------//
// Check that the polygon can find its largest coordinates
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( Polygon,
				   getExtremeCoordinates,
				   OrdinalType,
				   ScalarType )
{
  typedef FACEMC::ThreeSpaceTraitsAndPolicy<ScalarType> ThreeSpace;
  typedef FACEMC::LinearAlgebraPolicy<ScalarType> LAP;
  typedef Teuchos::ScalarTraits<ScalarType> ST;
  typedef TestPolygon<OrdinalType,ScalarType> Polygon;
  typedef typename Polygon::Point Point;
  
  std::list<Point> polygon_corners;
  Point min_coordinates;
  Point max_coordinates;

  // Create a triangle
  createThreeSpaceTriangle( polygon_corners );

  // Get the largest coordinates
  Polygon::getExtremeCoordinates( polygon_corners,
				  min_coordinates,
				  max_coordinates );

  Point ref_min_coordinates( ST::zero(), ST::zero(), ST::zero() );
  Point ref_max_coordinates( ST::one(), ST::one(), ST::one() );

  FACEMC_TEST_EQUALITY( min_coordinates, ref_min_coordinates );
  FACEMC_TEST_EQUALITY( max_coordinates, ref_max_coordinates );
}

UNIT_TEST_INSTANTIATION( Polygon, getExtremeCoordinates );

//---------------------------------------------------------------------------//
// Check that the polygon can be transformed to a polygon in the x-y plane
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( Polygon,
				   transformPolygon,
				   OrdinalType,
				   ScalarType )
{
  typedef FACEMC::ThreeSpaceTraitsAndPolicy<ScalarType> ThreeSpace;
  typedef FACEMC::LinearAlgebraPolicy<ScalarType> LAP;
  typedef Teuchos::ScalarTraits<ScalarType> ST;
  typedef TestPolygon<OrdinalType,ScalarType> Polygon;
  typedef typename Polygon::Point Point;
  typedef typename Polygon::PointProjection PointProjection;

  std::list<Point> polygon_corners;

  // Create a triangle
  createThreeSpaceTriangle( polygon_corners );

  // Calculate the polygon plane unit normal
  typename ThreeSpace::Vector unit_normal = 
    Polygon::calculatePolygonPlaneUnitNormal( polygon_corners );

  // Create the transformation matrix and vector
  typename ThreeSpace::Matrix rotation_matrix( 3, 3 );
  typename ThreeSpace::Vector translation_vector( 3 );
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
  typedef FACEMC::ThreeSpaceTraitsAndPolicy<ScalarType> ThreeSpace;
  typedef FACEMC::LinearAlgebraPolicy<ScalarType> LAP;
  typedef Teuchos::ScalarTraits<ScalarType> ST;
  typedef TestPolygon<OrdinalType,ScalarType> Polygon;
  typedef typename Polygon::Point Point;
  typedef typename Polygon::PointProjection PointProjection;

  std::list<Point> polygon_corners;

  // Create a triangle
  createThreeSpaceTriangle( polygon_corners );

  // Calculate the polygon plane unit normal
  typename ThreeSpace::Vector unit_normal = 
    Polygon::calculatePolygonPlaneUnitNormal( polygon_corners );

  // Create the transformation matrix and vector
  typename ThreeSpace::Matrix rotation_matrix( 3, 3 );
  typename ThreeSpace::Vector translation_vector( 3 );
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
  Point point_1 = Polygon::applyReverseTransform( 
					  transformed_polygon_corners.front(),
					  rotation_matrix,
					  translation_vector );
  Point point_2 = Polygon::applyReverseTransform(
				      *(++transformed_polygon_corners.begin()),
				      rotation_matrix,
				      translation_vector );

  Point point_3 = Polygon::applyReverseTransform(
				  *(++(++transformed_polygon_corners.begin())),
				  rotation_matrix,
				  translation_vector );
  
  FACEMC_TEST_FLOATING_EQUALITY( point_1,
				 polygon_corners.front(),
				 ST::prec() );
  FACEMC_TEST_FLOATING_EQUALITY( point_2,
				 *(++polygon_corners.begin()),
				 ST::prec() );
  FACEMC_TEST_FLOATING_EQUALITY( point_3,
				 *(++(++polygon_corners.begin())),
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
  typedef FACEMC::ThreeSpaceTraitsAndPolicy<ScalarType> ThreeSpace;
  typedef FACEMC::LinearAlgebraPolicy<ScalarType> LAP;
  typedef Teuchos::ScalarTraits<ScalarType> ST;
  typedef TestPolygon<OrdinalType,ScalarType> Polygon;
  typedef typename Polygon::Point Point;
  typedef typename Polygon::PointProjection PointProjection;

  std::list<Point> polygon_corners;

  // Create a triangle
  createThreeSpaceTriangle( polygon_corners );

  // Calculate the polygon plane unit normal
  typename ThreeSpace::Vector unit_normal = 
    Polygon::calculatePolygonPlaneUnitNormal( polygon_corners );

  // Create the transformation matrix and vector
  typename ThreeSpace::Matrix rotation_matrix( 3, 3 );
  typename ThreeSpace::Vector translation_vector( 3 );
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
  typedef FACEMC::ThreeSpaceTraitsAndPolicy<ScalarType> ThreeSpace;
  typedef FACEMC::LinearAlgebraPolicy<ScalarType> LAP;
  typedef Teuchos::ScalarTraits<ScalarType> ST;
  typedef TestPolygon<OrdinalType,ScalarType> Polygon;
  typedef typename Polygon::Point Point;
  typedef typename Polygon::PointProjection PointProjection;

  std::list<Point> polygon_corners;

  // Create a triangle
  createSimpleThreeSpaceSquare( polygon_corners );

  // Calculate the polygon plane unit normal
  typename ThreeSpace::Vector unit_normal = 
    Polygon::calculatePolygonPlaneUnitNormal( polygon_corners );

  // Create the transformation matrix and vector
  typename ThreeSpace::Matrix rotation_matrix( 3, 3 );
  typename ThreeSpace::Vector translation_vector( 3 );
  
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
  typedef FACEMC::ThreeSpaceTraitsAndPolicy<ScalarType> ThreeSpace;
  typedef FACEMC::LinearAlgebraPolicy<ScalarType> LAP;
  typedef Teuchos::ScalarTraits<ScalarType> ST;
  typedef TestPolygon<OrdinalType,ScalarType> Polygon;
  typedef typename Polygon::Point Point;
  typedef typename Polygon::PointProjection PointProjection;

  std::list<Point> polygon_corners;

  // Create a triangle
  createComplexThreeSpaceSquare( polygon_corners );

  // Calculate the polygon plane unit normal
  typename ThreeSpace::Vector unit_normal = 
    Polygon::calculatePolygonPlaneUnitNormal( polygon_corners );

  // Create the transformation matrix and vector
  typename ThreeSpace::Matrix rotation_matrix( 3, 3 );
  typename ThreeSpace::Vector translation_vector( 3 );
  
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
  typedef typename Polygon::Point Point;
  
  // Create the corners of the polygon
  std::list<Point> polygon_corners;
  
  createThreeSpaceTriangle( polygon_corners );

  // Create the polygon
  Polygon triangle( 0, polygon_corners );
  
  // Get the centroid of the polygon
  Point centroid = triangle.getCentroid();

  // Assign the reference centroid
  Point ref_centroid( 2.0/3.0, 1.0/3.0, 1.0/3.0 );

  FACEMC_TEST_FLOATING_EQUALITY( centroid, ref_centroid, ST::prec() );
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
  typedef typename Polygon::Point Point;
  
  // Create the corners of the polygon
  std::list<Point> polygon_corners;
  
  createSimpleThreeSpaceSquare( polygon_corners );

  // Create the polygon
  Polygon square( 0, polygon_corners );
  
  // Get the centroid of the polygon
  Point centroid = square.getCentroid();

  // Assign the reference centroid
  Point ref_centroid( 0.0, 1.0, 0.0 );

  FACEMC_TEST_FLOATING_EQUALITY( centroid, ref_centroid, ST::prec() );
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
  typedef typename Polygon::Point Point;
  
  // Create the corners of the polygon
  std::list<Point> polygon_corners;
  
  createComplexThreeSpaceSquare( polygon_corners );

  // Create the polygon
  Polygon square( 0, polygon_corners );
  
  // Get the centroid of the polygon
  Point centroid = square.getCentroid();

  // Assign the reference centroid
  Point ref_centroid( 2.0, 0.0, 0.0 );

  FACEMC_TEST_FLOATING_EQUALITY( centroid, ref_centroid, ST::prec() );
}

UNIT_TEST_INSTANTIATION( Polygon, calculateCentroid_complex_square );

//---------------------------------------------------------------------------//
// end tstPolygon.cpp
//---------------------------------------------------------------------------//

