//---------------------------------------------------------------------------//
//!
//! \file   Geometry_CellPolygonFactory_def.hpp
//! \author Alex Robinson
//! \brief  Definition of factory class that creates polygons on cell surfs.
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_CELL_POLYGON_FACTORY_DEF_HPP
#define GEOMETRY_CELL_POLYGON_FACTORY_DEF_HPP

// FRENSIE Includes
#include "Geometry_LinearAlgebraAlgorithms.hpp"
#include "Utility_ContractException.hpp"

namespace Geometry{

// Constructor
template<typename Cell>
CellPolygonFactory<Cell>::CellPolygonFactory( 
					   const Teuchos::RCP<Cell> &cell_ptr )
  : d_cell_ptr( cell_ptr )
{
  // The cell ptr must be valid
  testPrecondition( !cell_ptr.is_null() );
}

// Create a polygon from intersection points on a surface
template<typename Cell>
typename CellPolygonFactory<Cell>::PolygonPtr
CellPolygonFactory<Cell>::create(
			    std::list<Point> &unordered_polygon_corners ) const
{
  // There must be at least three intersection points to create a polygon
  testPrecondition( unordered_polygon_corners.size() >= 3 );
  // All points in the list must be on the same plane
  testPrecondition( CellPolygonFactory<Cell>::allPointsOnSamePlane( 
						 unordered_polygon_corners ) );

  // Determine the polygon plane id
  ordinalType plane_of_polygon_id =
  CellPolygonFactory<Cell>::getPlaneOfPolygonId( unordered_polygon_corners );

  // An ordered list of points that define the polygon will be created
  std::list<Point> ordered_polygon_corners;

  // The unordered intersection points will be iterated through
  typename std::list<Point>::iterator next_point, 
    end_point;
  
  // The initial point of each disjoint polygon will be added to the end
  // of the ordered list. The very first corner will always again last.
  typename std::list<Point>::const_iterator global_start_corner, 
    local_start_corner;

  // The most recently added corner of the polygon will be be used to search
  // for the next polygon corner using the connectivity data.
  typename std::list<Point>::reverse_iterator current_corner, 
    previous_corner;

  // Count the number of disjoint polygons (for point ordering purposes)
  unsigned disjoint_polygon_number = 0;

  // Organize the intersection points (there may be multiple disjoint polygons)
  while( unordered_polygon_corners.size() > 0 )
  {
    // Find the first three points on the boundary of the polygon
    local_start_corner = initializePolygonCorners( ordered_polygon_corners,
						   unordered_polygon_corners,
						   plane_of_polygon_id );

    // Save the initial start corner
    if( disjoint_polygon_number == 0 )
      global_start_corner = local_start_corner;

    // Determine the surface on which the next point will be searched for
    current_corner = ordered_polygon_corners.rbegin(); 
    previous_corner = current_corner;
    ++previous_corner;
    
    ordinalType current_secondary_surface_id = 
      current_corner->getUnsharedSurfaceId( *previous_corner );
    
    // Continue adding points to the polygon until no more points can be found
    while( true )
    {
      next_point = getNextPolygonCorner( current_secondary_surface_id,
					 *current_corner,
					 unordered_polygon_corners,
					 POINT_MAY_NOT_BE_FOUND );
      end_point = unordered_polygon_corners.end();
      
      // The next corner of the polygon has been found (add it to the list)
      if( next_point != end_point )
      {
	ordered_polygon_corners.push_back( *next_point );
	
	next_point = unordered_polygon_corners.erase( next_point );
	
	current_corner = ordered_polygon_corners.rbegin();
	previous_corner = current_corner;
	++previous_corner;

	current_secondary_surface_id = 
	  current_corner->getUnsharedSurfaceId( *previous_corner );
      }
      else // This section of the possibly disjoint polygon is finished
      {
	// Add a copy of the start corner to the end of the polygon
	ordered_polygon_corners.push_back( *local_start_corner );

	break;
      }
    }
    
    // Add a copy of the global start corner
    if( disjoint_polygon_number > 0 )
      ordered_polygon_corners.push_back( *global_start_corner );

    ++disjoint_polygon_number;
  }
  
  // Create the polygon on this surface
  return PolygonPtr( new Polygon<ordinalType,scalarType>( 
					           plane_of_polygon_id, 
				                   ordered_polygon_corners ) );
}

// Find the first three points on the boundary of the polygon
template<typename Cell>
typename std::list<IntersectionPoint<typename Cell::surfaceOrdinalType,
				     typename Cell::scalarType> >::const_iterator
CellPolygonFactory<Cell>::initializePolygonCorners( 
		       std::list<Point> &ordered_polygon_corners,
		       std::list<Point> &unordered_polygon_corners,
		       const ordinalType plane_of_polygon_id ) const
{
  // There must be at least three intersection points left to create a polygon
  testPrecondition( unordered_polygon_corners.size() >= 3 );
  // The plane of polygon id must be valid
  testPrecondition( plane_of_polygon_id >= OT::zero() );
  testPrecondition( plane_of_polygon_id != OT::invalid() );
  // Keep a copy of the current size of the ordered polygon corners list
  remember( ordinalType start_size = ordered_polygon_corners.size() );

  typename std::list<Point>::iterator first_point, second_point,
    third_point, end_point;
  end_point = unordered_polygon_corners.end();

  // Find the lexicographically largest point (need to find point on convex
  // hull of polygon to correctly initialize it)
  second_point = getLexicographicallyLargestPoint( unordered_polygon_corners );

  // Save the surfaces ids that this point is on
  ordinalType secondary_surface_id, tertiary_surface_id;
  
  if( second_point->getFirstSurfaceId() == plane_of_polygon_id )
  {
    secondary_surface_id = second_point->getSecondSurfaceId();
    tertiary_surface_id = second_point->getThirdSurfaceId();
  }
  else if( second_point->getSecondSurfaceId() == plane_of_polygon_id )
  {
    secondary_surface_id = second_point->getFirstSurfaceId();
    tertiary_surface_id = second_point->getThirdSurfaceId();
  }
  else
  {
    secondary_surface_id = second_point->getFirstSurfaceId();
    tertiary_surface_id = second_point->getSecondSurfaceId();
  }

  // Find the first and third points 
  first_point = getNextPolygonCorner( secondary_surface_id,
				      *second_point,
				      unordered_polygon_corners );

  third_point = getNextPolygonCorner( tertiary_surface_id,
				      *second_point,
				      unordered_polygon_corners );

  // Determine if the first and third point need to be swapped
  bool swap_first_and_third_points =
    cornerTripletNeedsReversing( plane_of_polygon_id,
				 secondary_surface_id,
				 tertiary_surface_id,
				 *first_point,
				 *second_point,
				 *third_point );
   
  if( swap_first_and_third_points )
    std::swap( first_point, third_point );
  
  // Add the points to the polygon list
  ordered_polygon_corners.push_back( *first_point );
  ordered_polygon_corners.push_back( *second_point );
  ordered_polygon_corners.push_back( *third_point );
  
			       
  // Remove the points from the unordered points list
  first_point = unordered_polygon_corners.erase( first_point );
  second_point = unordered_polygon_corners.erase( second_point );
  third_point = unordered_polygon_corners.erase( third_point );

  // An iterator to the first point added must be returned
  typename std::list<Point>::const_iterator first_point_added;
  first_point_added = ordered_polygon_corners.end();
  --first_point_added;
  --first_point_added;
  --first_point_added;
  
  // Make sure that three points were added
  testPostcondition( ordered_polygon_corners.size() - start_size == 3 );

  return first_point_added;
}

// Determine if the ordering of a polygon initialization needs to reverse
template<typename Cell>
bool CellPolygonFactory<Cell>::cornerTripletNeedsReversing(
			 const ordinalType plane_of_polygon_id,
			 const ordinalType first_to_second_point_surface_id,
			 const ordinalType second_to_third_point_surface_id,
			 const Point &first_point,
			 const Point &second_point,
			 const Point &third_point ) const
{
  // The first point must be on the plane_of_polygon and the 
  // first_to_second surface
  testPrecondition( first_point.isOnSurface( plane_of_polygon_id ) );
  testPrecondition( first_point.isOnSurface(first_to_second_point_surface_id));
  // The second point must be on all three surfaces
  testPrecondition( second_point.isOnSurface( plane_of_polygon_id ) );
  testPrecondition(second_point.isOnSurface(first_to_second_point_surface_id));
  testPrecondition(second_point.isOnSurface(second_to_third_point_surface_id));
  // The third point must be on the plane_of_polygon and the 
  // second_to_third surface
  testPrecondition( third_point.isOnSurface( plane_of_polygon_id ) );
  testPrecondition( third_point.isOnSurface(second_to_third_point_surface_id));
  
  // Get the polygon plane, first surface and second surface
  typename Cell::SurfaceSensePairsIterator plane_of_polygon = 
    d_cell_ptr->getSurfaceSensePair( plane_of_polygon_id );
  
  typename Cell::SurfaceSensePairsIterator first_surface = 
    d_cell_ptr->getSurfaceSensePair( first_to_second_point_surface_id );

  typename Cell::SurfaceSensePairsIterator second_surface = 
    d_cell_ptr->getSurfaceSensePair( second_to_third_point_surface_id );
  
  // Get the senses of the points w.r.t. the unattached surfaces
  SurfaceSense sense_of_third_point = 
    first_surface->first->getSenseOfPoint( third_point[0],
					   third_point[1],
					   third_point[2] );

  SurfaceSense sense_of_first_point = 
    second_surface->first->getSenseOfPoint( first_point[0],
					    first_point[1],
					    first_point[2] );
  
  // Determine the required polygon orientation to keep the cell on the left
  // of the polygon boundary (w.r.t. its ordering).
  PolygonOrientation polygon_orientation;
  
  if( sense_of_third_point == first_surface->second  ||
      sense_of_first_point == second_surface->second )
    polygon_orientation = CELL_ON_LEFT;
  else if( sense_of_third_point != first_surface->second &&
	   sense_of_first_point != second_surface->second )
    polygon_orientation = CELL_ON_RIGHT;
  else
    polygon_orientation = INVALID_ORIENTATION;

  // Determine if the points need to be swapped to keep desired point ordering
  Vector<scalarType> polygon_plane_normal = 
    plane_of_polygon->first->getUnitNormalAtPoint( second_point.getRawPoint(),
						   plane_of_polygon->second );
  
  Vector<scalarType> first_point_to_second_point( 
					    second_point[0] - first_point[0],
					    second_point[1] - first_point[1],
					    second_point[2] - first_point[2] );
  Vector<scalarType> second_point_to_third_point(
					    third_point[0] - second_point[0],
					    third_point[1] - second_point[1],
					    third_point[2] - second_point[2] );
 
  Vector<scalarType> corner_cross_product = LinearAlgebra::computeCrossProduct(
					         first_point_to_second_point,
					         second_point_to_third_point );
  
  bool reverse_corner_ordering = false;
  
  if( polygon_orientation == CELL_ON_LEFT )
  {
    if( !polygon_plane_normal.isParallel( corner_cross_product ) )
      reverse_corner_ordering = true;
  }
  else if( polygon_orientation == CELL_ON_RIGHT )
  {
    if( !polygon_plane_normal.isAntiparallel( corner_cross_product ) )
      reverse_corner_ordering = true;
  }
  
  // Make sure that a valid orientation was found
  testPostcondition( polygon_orientation != INVALID_ORIENTATION );

  return reverse_corner_ordering;
}

// Test if all of the points lie on the same plane
template<typename Cell>
bool CellPolygonFactory<Cell>::allPointsOnSamePlane(
		const std::list<Point> &unordered_polygon_corners )
{
  typename std::list<Point>::const_iterator first_point,
    point, end_point;
  first_point = unordered_polygon_corners.begin();
  point = first_point;
  ++point;
  end_point = unordered_polygon_corners.end();

  bool all_points_on_same_plane = true;
  
  while( point != end_point )
  {
    if( !first_point->isOnSamePlane( *point ) )
    {
      all_points_on_same_plane = false;
      break;
    }
  
    ++point;
  }

  return all_points_on_same_plane;
}

// Find the id of the polygon plane
template<typename Cell>
typename CellPolygonFactory<Cell>::ordinalType
CellPolygonFactory<Cell>::getPlaneOfPolygonId(
		const std::list<Point> &unordered_polygon_corners )
{
  // There must be at least three intersection points for a valid polygon
  testPrecondition( unordered_polygon_corners.size() >= 3 );
  // All points in the list must be on the same plane
  testPrecondition( CellPolygonFactory<Cell>::allPointsOnSamePlane( 
						 unordered_polygon_corners ) );

  typename std::list<Point>::const_iterator first_point,
    second_point, third_point;
  
  first_point = unordered_polygon_corners.begin();
  second_point = first_point;
  ++second_point;
  third_point = second_point;
  ++third_point;
  
  // Make a list of the surface ids stored by these three intersection points
  std::list<ordinalType> surface_id_list;

  surface_id_list.push_back( first_point->getFirstSurfaceId() );
  surface_id_list.push_back( first_point->getSecondSurfaceId() );
  surface_id_list.push_back( first_point->getThirdSurfaceId() );
  surface_id_list.push_back( second_point->getFirstSurfaceId() );
  surface_id_list.push_back( second_point->getSecondSurfaceId() );
  surface_id_list.push_back( second_point->getThirdSurfaceId() );
  surface_id_list.push_back( third_point->getFirstSurfaceId() );
  surface_id_list.push_back( third_point->getSecondSurfaceId() );
  surface_id_list.push_back( third_point->getThirdSurfaceId() );

  // sort the list of surface id
  surface_id_list.sort();

  // Find the id in the list that repeats three times
  typename std::list<ordinalType>::const_iterator first_id, second_id, 
    third_id, end_id;
  first_id = surface_id_list.begin();
  second_id = first_id;
  ++second_id;
  third_id = second_id;
  ++third_id;
  end_id = surface_id_list.end();

  ordinalType plane_of_polygon_id = OT::invalid();
  
  while( third_id != end_id )
  {
    if( *first_id == *second_id && *first_id == *third_id )
      plane_of_polygon_id = *first_id;

    ++first_id;
    ++second_id;
    ++third_id;
  }
  
  // Make sure that the polygon plane id was found
  testPostcondition( plane_of_polygon_id != OT::invalid() );

  return plane_of_polygon_id;
}

// Find the lexicographically largest point
template<typename Cell>
typename std::list<IntersectionPoint<typename Cell::surfaceOrdinalType,
				     typename Cell::scalarType> >::iterator
CellPolygonFactory<Cell>::getLexicographicallyLargestPoint(
				  std::list<Point> &unordered_polygon_corners )
{
  // The list must not be empty
  testPrecondition( unordered_polygon_corners.size() > 0 );

  typename std::list<Point>::iterator point, largest_point,
    end_point;

  largest_point = unordered_polygon_corners.begin();
  point = largest_point;
  ++point;
  end_point = unordered_polygon_corners.end();
  
  while( point != end_point )
  {
    if( (*point)[0] - (*largest_point)[0] > ST::prec() )
      largest_point = point;
    else if( ST::magnitude( (*point)[0] - (*largest_point)[0] ) < ST::prec() &&
	     (*point)[1] > (*largest_point)[1] )
      largest_point = point;
    else if( ST::magnitude( (*point)[0] - (*largest_point)[0] ) < ST::prec() &&
	     ST::magnitude( (*point)[1] - (*largest_point)[1] ) < ST::prec() &&
	     (*point)[2] > (*largest_point)[2] )
      largest_point = point;

    ++point;
  }

  return largest_point;
}	 

// Find the next point on the boundary of the polygon
/*! \details If the point may not be found by this function 
   * (POINT_MAY_NOT_BE_FOUND), this function may return an iterator to the
   * end of the list. It is therefore important to test the iterator returned.
   */
template<typename Cell>
typename std::list<IntersectionPoint<typename Cell::surfaceOrdinalType,
				     typename Cell::scalarType> >::iterator
CellPolygonFactory<Cell>::getNextPolygonCorner(
	        const ordinalType desired_surface_id,
	        const Point &current_corner,
	        std::list<Point> &unordered_polygon_corners,
                PointFindNecessity point_find_necessity )
{
  typename std::list<Point>::iterator point, desired_point,
    end_point;
  
  point = unordered_polygon_corners.begin();
  end_point = unordered_polygon_corners.end();
  desired_point = end_point;

  while( point != end_point )
  {
    // Test if the point is on the desired surface
    if( point->isOnSurface( desired_surface_id ) && *point != current_corner )
    {
      // No points on the desired surface have been found yet
      if( desired_point == end_point )
	desired_point = point;
     
      // At least one point on the desired surface has already been found - 
      // take the one that is closest to the current polygon corner.
      else
      {
	Vector<scalarType> current_vector(
					(*desired_point)[0]-current_corner[0],
					(*desired_point)[1]-current_corner[1],
					(*desired_point)[2]-current_corner[2]);
	
	Vector<scalarType> new_vector( (*point)[0]-current_corner[0],
				       (*point)[1]-current_corner[1],
				       (*point)[2]-current_corner[2] );
		
	if( new_vector.normTwo() < current_vector.normTwo() )
	  desired_point = point;
      }
    }

    ++point;
  }

  // Make sure that a point was found if one must be
  testPostcondition( (point_find_necessity == POINT_MUST_BE_FOUND) ? 
		     (desired_point != end_point ) : true );
  // Make sure that if a point was found, it is not equal to the current corner
  testPostcondition( (desired_point != end_point) ?
		     (*desired_point != current_corner) : true );

  return desired_point;
}
			 

} // end Geometry namespace

#endif // end GEOMETRY_CELL_POLYGON_FACTORY_DEF_HPP

//---------------------------------------------------------------------------//
// end Geometry_CellPolygonFactory_def.hpp
//---------------------------------------------------------------------------//
