//---------------------------------------------------------------------------//
//!
//! \file   CellFactory_def.hpp
//! \author Alex Robinson
//! \brief  Cell factory definition
//!
//---------------------------------------------------------------------------//

#ifndef CELL_FACTORY_DEF_HPP
#define CELL_FACTORY_DEF_HPP

// Std lib includes
#include <string>
#include <map>
#include <algorithm>
#include <iterator>

// Trilinos Includes
#include <Teuchos_ArrayView.hpp>
#include <Teuchos_RCP.hpp>

// FACEMC Includes
#include "Cell.hpp"
#include "Surface.hpp"
#include "Tuple.hpp"

namespace FACEMC{

// Constructor
template<typename Cell, typename SurfaceMap>
CellFactory<Cell,SurfaceMap>::CellFactory( 
					 const SurfaceMap &global_surface_map )
: d_global_surface_map( Teuchos::rcpFromRef( global_surface_map ) )
{ /* ... */ }

// Create the desired cell
template<typename Cell, typename SurfaceMap>
typename CellFactory<Cell,SurfaceMap>::CellPtr
CellFactory<Cell,SurfaceMap>::create(
				   const typename Cell::ordinalType id,
				   std::string &cell_definition,
				   const bool calculate_volume_and_area ) const
{
  CellPtr cell( new Cell( id, 
			  cell_definition,
			  *d_global_surface_map ) );

  if( calculate_volume_and_area )
  {
    if( cell->isPolyhedron() )
      calculatePolyhedralCellVolumeAndArea( cell );
    else
      calculateRotationallySymmetricCellVolumeAndArea( cell );
  }

  return cell;
}

// Get the cells needing Monte Carlo integration
template<typename Cell, typename SurfaceMap>
Teuchos::ArrayView<const typename Cell::ordinalType>
CellFactory<Cell,SurfaceMap>::getCellsNeedingMonteCarloIntegration() const
{
  return d_cells_needing_mc_integration();
}

// Calculate the volume and area of a polyhedral cell
template<typename Cell, typename SurfaceMap>
void CellFactory<Cell,SurfaceMap>::calculatePolyhedralCellVolumeAndArea( CellPtr &cell ) const
{
  // Get the cells that define the cell
  SurfaceSensePairsIterator surface_sense_pair = 
    cell->beginSurfaceSensePairs();
  SurfaceSensePairsIterator end_surface_sense_pair = 
    cell->endSurfaceSensePairs();
  
  // Assign the reference surface used for calculating the cell vol.
  typename Cell::SurfaceSensePairsIterator reference_surface_sense_pair = 
    surface_sense_pair;

  // Processed surfaces (the same surf. may appear more than once in cell def)
  std::set<typename Cell::surfaceOrdinalType> processed_surfaces;

  // Initialize the cell volume
  ScalarType volume = ST::zero();

  // Process every surface of the cell and create a polygon
  while( surface_sense_pair != end_surface_sense_pair )
  {
    // Only use a surface if it hasn't been processed yet
    if( processed_surfaces.find( surface_sense_pair->first->getId() ) ==
	processed_surfaces.end() )
    {
      processed_surfaces.insert( surface_sense_pair->first->getId() );
    }
    else // this surface has already been processed
    {
      ++surface_sense_pair;
      continue;
    }      
    
    // Determine the intersection points of all other surfaces with this surf.
    std::list<IntersectionPoint> intersection_points;
    calculateIntersectionPoints( intersection_points,
				 surface_sense_pair,
				 cell );

    // Create a new polygon from the intersection points
    std::list<PolygonCorner> polygon;
    createPolygon( polygon, intersection_points, cell );

    // Rotate the polygon to the x-y plane to simplify area and volume calcs.
    Matrix rotation_matrix;
    Vector translation_vector;
    transformPolygon( polygon,
		      surface_sense_pair,
		      rotation_matrix,
		      translation_vector );

    // Calculate the area of the polygon (current surface)
    ScalarType polygon_area = calculatePolygonArea( polygon );
    cell->setSurfaceArea( surface_sense_pair->first->getId(),
			  polygon_area );

    // Move this to a new function: //@{
    // Transform the reference surface using the same transformation
    Surface reference_surface( reference_surface_sense_pair->first->getId(),
			       *(reference_surface_sense_pair->first),
			       rotation_matrix,
			       translation_vector );

    // Get a point on the reference surface
    Vector point_on_reference_surface = 
      LAP::createZeroingVector( reference_surface.getLinearTermVector(),
				reference_surface.getConstantTerm() );

    // Get the normal to the reference surface pointing outside the cell
    if( reference_surface_sense_pair->second == POS_SURFACE_SENSE )
      // change this to normal (not unit normal)
      reference_surface.getUnitNormalAtPoint( point_on_reference_surface,
					      NEG_SURFACE_SENSE );
    else
      reference_surface.getUnitNormalAtPoint( point_on_reference_surface,
					      POS_SURFACE_SENSE );
    //@}
					    
    
    // Calculate the volume contribution from this surface
    ScalarType volume += calculatePolygonVolumeContribution( 
					polygon,
					polygon_area,
					plane_of_polygon_normal,
					reference_plane_normal,
					reference_plane_const_term )
    
    ++surface_sense_pair;
  }
  
  // Make sure that the volume calculated is valid
  testPostcondition( volume > ST::zero() );
  testPostcondition( !ST::isnaninf( volume ) );

  cell->setVolume( volume );
}

template<typename Cell, typename SurfaceMap>
void CellFactory<Cell,SurfaceMap>::calculateIntersectionPoints(
			    std::list<IntersectionPoints> &intersection_points,
			    const SurfaceSensePairsIterator &plane_of_polygon,
			    const CellPtr &cell ) const
{
  // Make sure that the intersection points list is empty
  intersection_points.clear();

  SurfaceSensePairsIterator secondary_surface = cell->beginSurfaceSensePairs();
  SurfaceSensePairsIterator tertiary_surface = cell->beginSurfaceSensePairs();
  SurfaceSensePairsIterator end_surface = cell->endSurfaceSensePairs();

  // Processed secondary surfaces (the same surf. may appear mult. times)
  std::set<typename Cell::surfaceOrdinalType> processed_secondary_surfaces;
  processed_surfaces.insert( plane_of_polygon->first->getId() );

  while( secondary_surface != end_surface )
  {
    // Only use a surface if it hasn't been processed yet
    if( processed_secondary_surfaces.find( secondary_surface->first->getId() ) 
	== processed_secondary_surfaces.end() )
    {
      processed_secondary_surfaces.insert( secondary_surface->first->getId() );
    }
    else // this surface has already been processed
    {
      ++secondary_surface;
      continue;
    }
    
    // Check if the secondary surf. is parallel to the primary surf. (ignore)
    Vector primary_surface_normal = 
      plane_of_polygon->first->getLinearTermVector();
    Vector secondary_surface_normal =
      secondary_surface->first->getLinearTermVector();
    
    if( LAP::isParallel( primary_surface_normal, secondary_surface_normal ) ||
	LAP::isAntiparallel( primary_surface_normal, secondary_surface_normal))
    {
      ++secondary_surf;
      continue;
    }
      
    // Processed tertiary surfaces
    std::set<typename Cell::surfaceOrdinalType> processed_tertiary_surfaces;
    
    tertiary_surface = cell->beginSurfaceSensePairs();
    
    while( tertiary_surface != end_surface )
    {
      // Only use a surface if it hasn't been processed yet
      if( processed_secondary_surfaces.find( tertiary_surface->first->getId())
	  != processed_secondary_surfaces.end() )
      {
	++tertiary_surface;
	continue;
      }
      else if( processed_tertiary_surfaces.find( tertiary_surface->first->getId() )
	       == processed_tertiary_surfaces.end() )
      {
	processed_tertiary_surfaces.insert(tertiary_surface->first->getId());
      }
      else // this surface has already been processed
      {
	++tertiary_surface;
	continue;
      }

      // Check if the tertiary surf. is parallel to the other surfs (ignore)
      Vector tertiary_surface_normal =
	tertiary_surface->first->getLinearTermVector();
         
      if(LAP::isParallel( tertiary_surface_normal, primary_surface_normal ) ||
	 LAP::isAntiparallel(tertiary_surface_normal,primary_surface_normal)||
	 LAP::isParallel( tertiary_surface_normal, secondary_surface_normal)||
	 LAP::isAntiParallel(tertiary_surface_normal,secondary_surface_normal))
      {
	  ++tertiary_surf;
	  continue;
      }
      
      // Calculate the intersection point
      IntersectionPoint intersection_point = 
	calculateIntersectionPoint( plane_of_polygon,
				    secondary_surface,
				    tertiary_surface );
      
      // Test if the intersection point is on the cell
      bool possible_intersection_point = 
	cell->isOn( intersection_point.first.first,
		    intersection_point.first.second,
		    intersection_point.first.third );

      // Test if the intersection point is real
      bool real_intersection_point = false;
      if( possible_intersection_point )
      {
	real_intersection_point = isRealIntersectionPoint( intersection_point,
							   cell );
      }

      // If a real intersection point has been found, add it to the list
      if( real_intersection_point )
	intersection_points.push_back( intersection_point );

      ++tertiary_surface;	
    }
    
    ++secondary_surface;
  }
}

template<typename Cell, typename SurfaceMap>
IntersectionPoint CellFactory<Cell,SurfaceMap>::calculateIntersectionPoint(
		      const SurfaceSensePairsIterator &primary_surface,
		      const SurfaceSensePairsIterator &secondary_surface,
		      const SurfaceSensePairsIterator &tertiary_surface ) const
{
  // Create the system that will be solved (Ax = b)
  Matrix A = ThreeSpace::createSquareMatrixFromRows(
			      primary_surface->first->getLinearTermVector(),
			      secondary_surface->first->getLinearTermVector(),
			      tertiary_surface->first->getLinearTermVector() );

  Vector b = ThreeSpace::createVector(
				 -primary_surface->first->getConstantTerm(),
				 -secondary_surface->first->getConstantTerm(),
				 -tertiary_surface->first->getConstantTerm() );

  Vector x = LAP::solveSystem( A, b );

  IntersectionPoint point;
  point.first.first = x[0];
  point.first.second = x[1];
  point.first.third = x[2];
  point.second.first = primary_surface->first->getId();
  point.second.second = secondary_surface->first->getId();
  point.second.third = tertiary_surface->first->getId();

  return point;
}

// Return if an intersection point is real
template<typename Cell, typename SurfaceMap>
bool CellFactory<Cell,SurfaceMap>::isRealIntersectionPoint( 
						const IntersectionPoint &point,
						const CellPtr &cell ) const
{
  // Delta value
  bool cell_present = false;

  unsigned test_function_value = 0;

  // Need to evaluate the function Sum_i=1^8 2^(i-1)*delta_i mod3
  for( Octant octant = START_OCTANT; octant <= END_OCTANT; ++octant )
  {
    bool primary_surface_boolean_parameter;
    bool secondary_surface_boolean_parameter;
    bool tertiary_surface_boolean_parameter;

    initializeBooleansForPointTest( octant,
				    primary_surface_boolean_parameter,
				    secondary_surface_boolean_parameter,
				    tertiary_surface_boolean_parameter );

    SurfaceSensePairsIterator surface_sense_pair =
      cell->beginSurfaceSensePairs();
    SurfaceSensePairsIterator end_surface_sense_pair = 
      cell->endSurfaceSensePairs();

    // Array of bools for surface sense tests
    BooleanArray sense_tests( std::distance( surface_sense_pair,
					     end_surface_sense_pair ) );
    BooleanArray::iterator test = sense_tests.begin();

    while( surface_sense_pair != end_surface_sense_pair )
    {
      if( surface_sense_pair->first->getId() == point.second.first )
	*test = primary_surface_boolean_parameter;
      else if( surface_sense_pair->first->getId() == point.second.second )
	*test = secondary_surface_boolean_parameter;
      else if( surface_sense_pair->first->getId() == point.second.third )
	*test = tertiary_surface_boolean_parameter;
      else
      {
	SurfaceSense sense = 
	  surface_sense_pair->first->getSense( point.first.first,
					       point.first.second,
					       point.first.third );
	
	if( sense == surface_sense_pair->second() || sense == ON_SURFACE )
	  *test = true;
	else
	  *test = false;
      }

      ++surface_sense_pair;
      ++test;
    }

    // Determine if the cell is present in the octant
    cell_present = cell->isCellPresent( sense_tests );

    if( cell_present )
      test_function_value += getPointTestFunctionMultiplier( octant );
  }

  // The point is only real if the test function value is not 0 modulo 3
  if( test_function_value%3 != 0 )
    return true;
  else
    return false;      
}

// Initialize the boolean variables for the point test
template<typename Cell, typename SurfaceMap>
void CellFactory<Cell,SurfaceMap>::initializeBooleansForPointTest(
			       const Octant octant,
			       bool &primary_surface_boolean_parameter,
			       bool &secondary_surface_boolean_parameter,
			       bool &tertiary_surface_boolean_parameter ) const
{
  switch( octant )
  {
  case POS_POS_POS_OCTANT:
    primary_surface_boolean_parameter = true;
    secondary_surface_boolean_parameter = true;
    tertiary_surface_boolean_parameter = true;
    break;
  case POS_NEG_POS_OCTANT:
    primary_surface_boolean_parameter = true;
    secondary_surface_boolean_parameter = false;
    tertiary_surface_boolean_parameter = true;
    break;
  case POS_NEG_NEG_OCTANT:
    primary_surface_boolean_parameter = true;
    secondary_surface_boolean_parameter = false;
    tertiary_surface_boolean_parameter = false;
    break;
  case POS_POS_NEG_OCTANT:
    primary_surface_boolean_parameter = true;
    secondary_surface_boolean_parameter = true;
    tertiary_surface_boolean_parameter = false;
    break;
  case NEG_NEG_POS_OCTANT:
    primary_surface_boolean_parameter = false;
    secondary_surface_boolean_parameter = false;
    tertiary_surface_boolean_parameter = true;
    break;
  case NEG_NEG_NEG_OCTANT:
    primary_surface_boolean_parameter = false;
    secondary_surface_boolean_parameter = false;
    tertiary_surface_boolean_parameter = false;
    break;
  case NEG_POS_NEG_OCTANT:
    primary_surface_boolean_parameter = false;
    secondary_surface_boolean_parameter = true;
    tertiary_surface_boolean_parameter = false;
    break;
  case NEG_POS_POS_OCTANT:
    primary_surface_boolean_parameter = false;
    secondary_surface_boolean_parameter = true;
    tertiary_surface_boolean_parameter = true;
    break:
  }
}

// Get the point test function multiplier
template<typename Cell, typename SurfaceMap>
unsigned CellFactory<Cell,SurfaceMap>::getPointTestFunctionMultiplier(
						    const Octant octant ) const
{  
  switch( octant )
  {
  case POS_POS_POS_OCTANT:
    return 1;
  case POS_NEG_POS_OCTANT:
    return 2;
  case POS_NEG_NEG_OCTANT:
    return 4;
  case POS_POS_NEG_OCTANT:
    return 8;
  case NEG_NEG_POS_OCTANT:
    return 16;
  case NEG_NEG_NEG_OCTANT:
    return 32;
  case NEG_POS_NEG_OCTANT:
    return 64;
  case NEG_POS_POS_OCTANT:
    return 128;
  }
}

// Create a polygon from intersection points
template<typename Cell, typename Surfacemap>
void CellFactory<Cell,SurfaceMap>::createPolygon( 
			     std::list<PolygonCorner> &polygon,
		             std::list<IntersectionPoint> &intersection_points,
			     const CellPtr &cell ) const
{
  // There must be at least three intersection points to create a polygon
  testPrecondition( intersection_points.size() >= 3 );

  typename std::list<IntersectionPoint>::iterator next_point, end_point;

  typename std::list<PolygonCorner>::iterator global_start_corner, 
    local_start_corner;
  typename std::list<PolygonCorner>::reverse_iterator current_corner;

  unsigned disjoint_polygon_number = 0;

  // There may be multiple disjoint polygons
  while( intersection_points.size() > 0 )
  {
    surfaceOrdinalType current_surface_id;

    // Find the first three points on the boundary of the polygon
    local_start_corner = initializePolygon( polygon,
					    intersection_points,
					    cell,
					    current_surface_id );
    
    current_corner = polygon.rbegin(); 

    // Save the initial start corner
    if( disjoint_polygon_number == 0 )
      global_start_corner = local_start_corner;

    // Continue adding points to the polygon until no more points can be found
    while( true )
    {
      // The current surface id will be reassigned by this function
      next_point = getNextPolygonCorner( current_surface_id,
					 current_corner,
					 intersection_points,
					 POINT_MAY_NOT_BE_FOUND );
      end_point = intersection_points.end();

      if( next_point != end_point )
      {
	polygon.push_back( next_point->first );
	
	current_surface_id = getNextSurfaceId( current_surface_id,
					       next_point );
	
	intersection_points.erase( next_point );

	current_corner = polygon.rbegin();
      }
      else // This section of the possibly disjoint polygon is finished
      {
	// Add a copy of the start corner to the end of the polygon
	polygon.push_back( *local_start_corner );

	break;
      }
    }
    
    // Add copy of global start
    if( disjoint_polygon_number > 0 )
      polygon.push_back( *global_start_corner );

    ++disjoint_polygon_number;
  }
	
  // Make sure that all intersection points have been processed
  testPostcondition( intersection_points.size() == 0 );
}

// Find the first three points on the boundary of the polygon
template<typename Cell, typename SurfaceMap>
typename std::list<PolygonCorner>::const_iterator
CellFactory<Cell,SurfaceMap>::initializePolygon( 
		     std::list<PolygonCorner> &polygon,
		     std::list<IntersectionPoint> &intersection_points,
		     const CellPtr &cell,
		     surfaceOrdinalType &current_surface_id ) const
{
  // There must be at least three intersection points left to create a polygon
  testPrecondition( intersection_points.size() >= 3 );

  typename std::list<IntersectionPoint>::iterator first_point, second_point,
    third_point, end_point;
  end_point = intersection_points.end();

  // Find the lexicographically largest point
  second_point = getLexicographicallyLargestPoint( intersection_points );

  // Add this point to the polygon
  polygon.push_back( polygon_corner->first );
  
  // Save the surfaces ids that this point is on
  surfaceOrdinalType first_surface_id = second_point->second.second;
  surfaceOrdinalType second_surface_id = second_point->second.third;
  surfaceOrdinalType next_surface_id, final_surface_id;
    
  // Remove this point from the intersection point list
  second_point = intersection_points.erase( second_point );

  // Get the first surface
  SurfaceSensePairsIterator first_surface = 
    cell->getSurfaceSensePair( first_surface_id );

  // Find the first and third points 
  first_point = getNextPolygonCorner( first_surface_id,
				      polygon.begin(),
				      intersection_points );

  third_point = getNextPolygonCorner( second_surface_id,
				      polygon.begin(),
				      intersection_points );

  // Find the next surface id and final surface id
  final_surface_id = getNextSurfaceId( first_surface_id,
				       first_point );
  next_surface_id = getNextSurfaceId( second_surface_id,
				      third_point );

  // Determine if the points need to be swapped to keep cell on left
  SurfaceSense sense_of_third_point = 
    first_surface->first->getSense( third_point->first.first,
				    third_point->first.second,
				    third_point->first.third );
  if( sense_of_third_point != first_surface->second )
  {
    std::swap( first_point, third_point );
    std::swap( next_surface_id, final_surface_id );
  }

  // Add the points to the polygon
  polygon.push_front( first_point->first );
  polygon.push_back( third_point->first );

  // Remove the points from the intersection points list
  first_point = intersection_points.erase( first_point );
  third_point = intersection_points.erase( third_point );

  // Set the next surface id to the current surface id
  current_surface_id = next_surface_id;  
}

// Find the lexicographically largest point
template<typename Cell, typename SurfaceMap>
typename std::list<IntersectionPoint>::const_iterator
CellFactory<Cell,SurfaceMap>::getLexicographicallyLargestPoint(
	        const std::list<IntersectionPoint> &intersection_points ) const
{
  // The list must not be empty
  testPrecondition( intersection_points.size() > 0 );

  typename std::list<IntersectionPoint>::const_iterator point, largest_point,
    end_point;

  largest_point = intersection_points.begin();
  point = largest_point;
  ++point;
  end_point = intersection_points.end();
  
  while( point != end_point )
  {
    if( point->first.first - largest_point->first.first > ST::prec() )
      largest_point = point;
    else if( ST::magnitude( point->first.first - largest_point->first.first )
	     < ST::prec() && point->first.second > largest_point->first.second)
      largest_point = point;
    else if( ST::magnitude( point->first.first - largest_point->first.first )
	     < ST::prec() && 
	     ST::magnitude( point->first.second - largest_point->first.second )
	     < ST::prec() && point->first.third > largest_point->first.third )
      largest_point = point;

    ++point;
  }

  return largest_point;
}

// Find the next point on the boundary of the polygon
template<typename Cell, typename SurfaceMap>
typename std::list<IntersectionPoint>::const_iterator
CellFactory<Cell,SurfaceMap>::getNextPolygonCorner(
       const surfaceOrdinalType desired_surface_id,
       const typename std::list<PolygonCorner>::const_iterator &current_corner,
       const std::list<IntersectionPoint> &intersection_points,
       PointFindNecessity point_find_necessity ) const
{
  // The list must not be empty
  testPrecondition( intersection_points.size() > 0 );

  typename std::list<IntersectionPoint>::const_iterator point, desired_point,
    end_point;
  
  point = intersection_points.begin();
  end_point = intersection_points.end();
  desired_point = end_point;

  while( point != end_point )
  {
    // Test if the point is on the desired surface
    if( point->second.second == desired_surface_id ||
	point->second.third == desired_surface_id )
    {
      // No points on the desired surface have been found yet
      if( desired_point == end_point )
      {
	desired_point = point;
      }
      // At least one point on the desired surface has already been found - 
      // take the one that is closest to the current polygon corner.
      else
      {
	scalarType current_x = desired_point->first.first - 
	  current_corner->first;
	scalarType current_y = desired_point->first.second - 
	  current_corner->second;
	scalarType current_z = desired_point->first.third -
	  current_corner->third;
	Vector current_vector = ThreeSpace::createVector( current_x,
							  current_y,
							  current_z );
	
	scalarType new_x = point->first.first - current_corner->first;
	scalarType new_y = point->first.second - current_corner->second;
	scalarType new_z = point->first.third - current_corner->third;
	Vector new_vector = ThreeSpace::createVector( new_x,
						      new_y,
						      new_z );
	
	if( new_vector.normFrobenius() < current_vector.normFrobenius() )
	  desired_point = point;
      }
    }

    ++point;
  }

  // Make sure that a point was found if one must be
  testPostCondition( (point_find_necessity == POINT_MUST_BE_FOUND) ? 
		     (desired_point != end_point ) : true );

  return desired_point;
}

// Get the next surface id (edge) of the polygon
template<typename Cell, typename SurfaceMap>
scalarType CellFactory<Cell,SurfaceMap>::getNextSurfaceId(
		    const surfaceOrdinalType current_surface_id,   
		    const typename std::list<IntersectionPoint>::const_iterator
		    &intersection_point ) const
{
  // The point must be on the given surface
  testPrecondition( intersection_point->second.second == current_surface_id ||
		    intersection_point->second.third == current_surface_id );

  if( intersection_point->second.second == current_surface_id )
    return intersection_point->second.third;
  else if( intersection_point->second.third == current_surface_id )
    return intersection_point->second.second;
}

// Rotate the intersection points to the x-y plane
template<typename Cell, typename SurfaceMap>
void CellFactory<Cell,SurfaceMap>::transformPolygon(
			    std::list<PolygonCorner> &polygon,
			    const SurfaceSensePairsIterator &plane_of_polygon,
			    Matrix &rotation_matrix,
			    Vector &translation_vector ) const	   
{
  Vector plane_of_polygon_normal = 
    plane_of_polygon->first->getLinearTermVector();

  // Create the necessary translation vector
  translation_vector = LAP::createZeroingVector( 
				  plane_of_polygon_normal,
				  plane_of_polygon->first->getConstantTerm() );

  // Normalize the normal to the polygon plane
  LAP::normalizeVector( plane_of_polygon_unit_normal );

  // Create the necessary rotation matrix
  rotation_matrix = LAP::createRotationMatrixFromUnitVectors( 
			                        ThreeSpace::zaxisVector(),
						plane_of_polygon_normal );

  // Transform each point of the polygon
  typename std::list<PolygonCorner>::iterator polygon_corner = polygon.begin();
  typename std::list<PolygonCorner>::iterator end_polygon_corner = 
    polygon.end();

  remember( bool multiply_success = true );
  remember( bool all_points_on_xy_plane = true );

  while( polygon_corner != end_polygon_corner )
  {
    Vector point_coordinates = ThreeSpace::createVector( 
					    polygon_corner->first,
					    polygon_corner->first,
					    polygon_corner->first );
    
    // x' = Rx + x0
    Vector transformed_point_coordinates( translation_vector );
    remember( bool local_multiply_success = );
    transformed_point_coordinates.multiply( Teuchos::NO_TRANS,
					    Teuchos::NO_TRANS,
					    ST::one(),
					    rotation_matrix,
					    point_coordinates,
					    ST::one() );

    remember( multiply_success = (local_multiply_success) ? multiply_success :
	      local_multiply_success );

    // Reassign the point coordinates
    polygon_corner->first = transformed_point_coordinates[0];
    polygon_corner->second = transformed_point_coordinates[1];
    polygon_corner->third = transformed_point_coordinates[2];

    remember( bool this_point_on_xy_plane = 
	      (ST::magnitude(polygon_corner->first.third) < ST::prec()) );
    remember( all_points_on_xy_plane = (this_point_on_xy_plane) ? 
	      all_points_on_xy_plane : false );
    
    ++polygon_corner;
  }
					    
  // Make sure that all multiplications were successful
  testPostcondition( multiply_success );
  // Make sure that the transformation was successful
  testPostcondition( all_points_on_xy_plane );
}

// Calculate the area of a polygon
template<typename Cell, typename SurfaceMap>
scalarType CellFactory<Cell,SurfaceMap>::calculatePolygonArea(
		                const std::list<PolygonCorner> &polygon ) const
{
  // The polygon must have at least 4 points (triangle with first point copied)
  testPrecondition( polygon.size() >= 4 );

  typename std::list<PolygonCorner>::const_iterator first_point, second_point, 
    end_point;

  first_point = polygon.begin();

  second_point = first_point;
  ++second_point;

  end_point = polygon.end();

  scalarType area = ST::zero();

  // A = 0.5 * Sum_{i=0}^{n-1}(x_i + x_{i+1})*(y_{i+1} - y_i)
  while( second_point != end_point )
  {
    area += (first_point->first + second_point->first)*
      (second_point->second - first_point->second);
    
    ++first_point;
    ++second_point;
  }

  area /= 2;

  // Make sure that the calculated area is physical
  testPostcondition( area > ST::zero() );
  testPostcondition( !ST::isnaninf( area ) );

  return area;
}

// Calculate the x-coord. of the polygon centroid
template<typename Cell, typename SurfaceMap>
scalarType 
CellFactory<Cell,SurfaceMap>::calculatePolygonCentroidXCoordinate(
				       const std::list<PolygonCorner> &polygon,
				       const scalarType polygon_area ) const
{
  // The polygon must have at least 4 points (triangle with first point copied)
  testPrecondition( polygon.size() >= 4 );

  typename std::list<PolygonCorner>::const_iterator first_point, second_point, 
    end_point;

  first_point = polygon.begin();

  second_point = first_point;
  ++second_point;

  end_point = polygon.end();

  scalarType centroid_x_coord = ST::zero();

  // x_c = (6*Area)^{-1} * Sum_{i=0}^{n-1}(x_{i+1}^2 + x_{i+1}*x_i + x_i^2)*
  //                                      (y_{i+1} - y_i)
  while( second_point != end_point )
  {
    centroid_x_coord += (second_point->first*second_point->first +
			  second_point->first*first_point->first +
			  first_point->first*first_point->first)*
      (second_point->second - first_point->second);
    
    ++first_point;
    ++second_point;
  }

  centroid_x_coord /= 6*polygon_area;

  // Make sure that the calculated coordinate is physical
  testPostcondition( !ST::isnaninf( centroid_x_coord ) );

  return centroid_x_coord;
}

// Calculate the y-coord. of the polygon centroid
template<typename Cell, typename SurfaceMap>
scalarType 
CellFactory<Cell,SurfaceMap>::calculatePolygonCentroidYCoordinate(
				       const std::list<PolygonCorner> &polygon,
				       const scalarType polygon_area ) const
{
  // The polygon must have at least 4 points (triangle with first point copied)
  testPrecondition( polygon.size() >= 4 );

  typename std::list<PolygonCorner>::const_iterator first_point, second_point, 
    end_point;

  first_point = polygon.begin();

  second_point = first_point;
  ++second_point;

  end_point = polygon.end();

  scalarType centroid_y_coord = ST::zero();

  // y_c = (6*Area)^{-1} * Sum_{i=0}^{n-1}(y_{i+1}^2 + y_{i+1}*y_i + y_i^2)*
  //                                      (x_{i+1} - x_i)
  while( second_point != end_point )
  {
    centroid_y_coord += (second_point->second*second_point->second +
			  second_point->second*first_point->second +
			  first_point->second*first_point->second)*
      (second_point->first - first_point->first);
    
    ++first_point;
    ++second_point;
  }

  centroid_y_coord /= 6*polygon_area;

  // Make sure that the calculated coordinate is physical
  testPostcondition( !ST::isnaninf( centroid_y_coord ) );

  return centroid_y_coord;
}

// Calculate the volume contribution from a surface bounding this cell
/*! \details To calculate the volume correctly the reference surface unit
 * normal must be directed out of the cell and the unit normal to the plane
 * of the polygon must be directed into the cell.
 */
template<typename Cell, typename SurfaceMap>
scalarType CellFactory<Cell,SurfaceMap>::calculatePolygonVolumeContribution(
			  const std::list<PolygonCorner> &polygon,
			  const scalarType polygon_area,
			  const Vector plane_of_polygon_normal,
			  const Vector reference_plane_normal,
			  const scalarType reference_plane_const_term ) const
{
  // The polygon must have at least 4 points (triangle with first point copied)
  testPrecondition( polygon.size() >= 4 );
  // The polygon area must be physical
  testPrecondition( area > ST::zero() );
  testPrecondition( !ST::isnaninf( area ) );

  // Calculate the polygon centroid
  scalarType centroid_x_coord = 
    calculatePolygonCentroidXCoordinate( polygon, polygon_area );
  scalarType centeroid_y_coord = 
    calculatePolygonCentroidYCoordinate( polygon, polygon_area );

  // Calculate the angle between the two normals
  scalarType cos_angle = 
    LAP::computeCosineAngleBetweenVectors( plane_of_polygon_unit_normal,
					   reference_surface_unit_normal );

  // Calculate the distance between the centroid and the reference plane
  scalarType reference_plane_normal_magnitude = 
    reference_plane_normal.normFrobenius();
  scalarType distance = 
    ST::magnitude( reference_plane_normal[0]*centroid_x_coord +
		   reference_plane_normal[1]*centroid_y_coord +
		   reference_plane_constant_term )/
    reference_plane_normal_magnitude;

  // Calculate the volume contribution (V = d*Area*cos_angle)
  scalarType volume_contribution = distance*polygon_area*cos_angle;

  // Make sure that the calculated volume is physical (neg. contribs. possible)
  testPostcondition( !ST::isnaninf( volume_contribution ) );

  return volume_contribution;  
}		    

// Calculate the volume and area of a rotationally symmetric cell
template<typename Cell, typename SurfaceMap>
void CellFactory<Cell,SurfaceMap>::calculateRotationallySymmetricCellVolumeAndArea( CellPtr &cell )
{
  
}

} // end FACEMC namespace

#endif // end CELL_FACTORY_DEF_HPP

//---------------------------------------------------------------------------//
// end CellFactory_def.hpp
//---------------------------------------------------------------------------//
