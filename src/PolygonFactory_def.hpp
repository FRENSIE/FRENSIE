//---------------------------------------------------------------------------//
//!
//! \file   PolygonFactory_def.hpp
//! \author Alex Robinson
//! \brief  Polygon factory class definition.
//!
//---------------------------------------------------------------------------//

#define POLYGON_FACTORY_DEF_HPP
#define POLYGON_FACTORY_DEF_HPP

namespace FACEMC{

// Create a polygon from intersection points on a surface
template<typename OrdinalType, typename ScalarType>
PolygonFactory<OrdinalType,ScalarType>::PolygonPtr
PolygonFactory<OrdinalType,ScalarType>::create(
		       std::list<IntersectionPoint> &unordered_polygon_corners,
		       const Surface &plane_of_polygon,
		       const SurfaceSense plane_sense ) const
{
  // There must be at least three intersection points to create a polygon
  testPrecondition( polygon_corners.size() >= 3 );
  // The plane of the polygon must be a plane
  testPrecondition( plane_of_polygon.isPlanar() );
  // The surface sense must be positive or negative - not on
  testPrecondition( surface_sense != ON_SURFACE );

  // An ordered list of points that define the polygon
  std::list<IntersectionPoint<OrdinalType,ScalarType> > 
    ordered_polygon_corners;

  // The unordered intersection points will be iterated through
  typename std::list<IntersectionPoint<OrdinalType,ScalarType> >::iterator 
    next_intersection_point, end_intersection_point;
  
  // The initial point of each disjoint polygon will be added to the end
  // of the ordered list. The very first corner will always again last.
  typename std::list<IntersectionPoint<OrdinalType,ScalarType> >::iterator 
    global_start_corner, local_start_corner;

  // The most recently added corner of the polygon will be be used to search
  // for the next polygon corner using the connectivity data.
  typename std::list<IntersectionPoint<OrdinalType,ScalarType> >::reverse_iterator current_corner, previous_corner;

  // Count the number of disjoint polygons (for point ordering purposes)
  unsigned disjoint_polygon_number = 0;

  // There may be multiple disjoint polygons
  while( polygon_corners.size() > 0 )
  {
    // Find the first three points on the boundary of the polygon
    local_start_corner = initializePolygonCorners( ordered_polygon_corners,
						   unordered_polygon_corners,
						   plane_of_polygon,
						   plane_sense );

    // Save the initial start corner
    if( disjoint_polygon_number == 0 )
      global_start_corner = local_start_corner;

    // Determine the surface on which the next point will be searched for
    current_corner = ordered_polygon_corners.rbegin(); 
    previous_corner = ++current_corner;
    
    OrdinalType current_secondary_surface_id = 
      current_corner->getUnsharedSurfaceId( *previous_corner );

    // Continue adding points to the polygon until no more points can be found
    while( true )
    {
      next_point = getNextPolygonCorner( current_secondary_surface_id,
					 current_corner->getRawPoint(),
					 unordered_polygon_corners,
					 POINT_MAY_NOT_BE_FOUND );
      end_point = intersection_points.end();

      // The next corner of the polygon has been found (add it to the list)
      if( next_point != end_point )
      {
	ordered_polygon_corners.push_back( *next_point );
	
	current_secondary_surface_id = 
	  next_point->getUnsharedSurfaceId( *current_corner );
	
	unordered_polygon_corners.erase( next_point );

	current_corner = ordered_polygon_corners.rbegin();
      }
      else // This section of the possibly disjoint polygon is finished
      {
	// Add a copy of the start corner to the end of the polygon
	ordered_polygon_corners.push_back( *local_start_corner );

	break;
      }
    }
    
    // Add copy of global start
    if( disjoint_polygon_number > 0 )
      ordered_polygon_corners.push_back( *global_start_corner );

    ++disjoint_polygon_number;
  }
	
  // Make sure that all intersection points have been processed
  testPostcondition( intersection_points.size() == 0 );

  // Create a new list with no connectivity data
  typename std::list<IntersectionPoint<OrdinalType,ScalarType> >::const_iterator intersection_point, end_intersection_point;
  
  std::list<Vector<ScalarType> > ordered_raw_polygon_corners;
  
  while( intersection_point != end_intersection_point )
  {
    ordered_raw_polygon_corners.push_back(intersection_point->getRawPoint());

    ++intersection_point;
  }

  // Create the polygon on this surface
  return PolygonPtr( new Polygon( plane_of_polygon.getId(), 
				  ordered_raw_polygon_corners ) );
}

// Find the first three points on the boundary of the polygon
template<typename OrdinalType, typename ScalarType>
typename std::list<IntersectionPoint<OrdinalType,ScalarType> >::const_iterator
PolygonFactory<OrdinalType,ScalarType>::initializePolygonCorners( 
		       std::list<IntersectionPoint> &ordered_polygon_corners,
		       std::list<IntersectionPoint> &unordered_polygon_corners,
		       const Surface &plane_of_polygon,
		       const SurfaceSense plane_sense )
{
  // There must be at least three intersection points left to create a polygon
  testPrecondition( unordered_polygon_corners.size() >= 3 );

  typename std::list<IntersectionPoint>::iterator first_point, second_point,
    third_point, end_point;
  end_point = unordered_polygon_corners.end();

  // Find the lexicographically largest point (need to find point on convex
  // hull of polygon to correctly initialize it)
  second_point = getLexicographicallyLargestPoint( unordered_polygon_corners );

  // Add this point to the polygon
  oriented_polygon_corners.push_back( second_point->first );
  
  // Save the surfaces ids that this point is on
  surfaceOrdinalType polygon_plane_id = second_point->second.first;
  surfaceOrdinalType first_surface_id = second_point->second.second;
  surfaceOrdinalType second_surface_id = second_point->second.third;
  surfaceOrdinalType next_surface_id, final_surface_id;
    
  // Remove this point from the intersection point list
  second_point = unordered_polygon_corners.erase( second_point );

  // Get the polygon plane, first surface and second surface
  SurfaceSensePairsIterator polygon_plane = 
    cell->getSurfaceSensePair( polygon_plane_id );
  
  SurfaceSensePairsIterator first_surface = 
    cell->getSurfaceSensePair( first_surface_id );

  SurfaceSensePairsIterator second_surface = 
    cell->getSurfaceSensePair( second_surface_id );

  // Find the first and third points 
  first_point = getNextPolygonCorner( first_surface_id,
				      polygon.begin(),
				      unordered_polygon_corners );

  third_point = getNextPolygonCorner( second_surface_id,
				      polygon.begin(),
				      unordered_polygon_corners );

  // Find the next surface id and final surface id
  final_surface_id = getNextSurfaceId( first_surface_id,
				       first_point );
  next_surface_id = getNextSurfaceId( second_surface_id,
				      third_point );
  
  // Determine the handedness of the point ordering (w.r.t. the surface normal
  // in the direction of the specified surface sense)
  SurfaceSense sense_of_third_point = 
    first_surface->first->getSense( third_point->first.first,
				    third_point->first.second,
				    third_point->first.third );

  SurfaceSense sense_of_first_point = 
    second_surface->first->getSense( first_point->first.first,
				     first_point->first.second,
				     first_point->first.third );

  PolygonOrientation polygon_orientation;
  
  if( sense_of_third_point == first_surface->second  &&
      sense_of_first_point == second_surface->second )
    polygon_orientation = LEFT_HANDED;
  else if( sense_of_third_point != first_surface->second &&
	   sense_of_first_point != second_surface->second )
    polygon_orientation = RIGHT_HANDED;
  else
    polygon_orientation = INVALID_ORIENTATION;

  // Determine if the points need to be swapped to keep desired point ordering
  Vector polygon_plane_normal = polygon_plane->first->getLinearTermVector(
						       polygon_plane->second );
  
  Vector point_1_to_point_2 = 
    ThreeSpace::createVector( oriented_polygon_corners.front().first -
			      first_point->first.first,
			      oriented_polygon_corners.front().second -
			      first_point->first.second,
			      oriented_polygon_corners.front().third -
			      first_point->first.third );
  Vector point_2_to_point_3 = 
    ThreeSpace::createVector( third_point->first.first - 
			      oriented_polygon_corners.front().first,
			      third_point->first.second - 
			      oriented_polygon_corners.front().second,
			      third_point->first.third -
			      oriented_polygon_corners.front().third );

  Vector point_1_2_3_cross_product = 
    LAP::computeCrossProduct( point_1_to_point_2, point_2_to_point_3 );

  if( polygon_orientation == LEFT_HANDED )
  {
    if( !LAP::isParallel( polygon_plane_normal, point_1_2_3_cross_product ) )
    {
      std::swap( first_point, third_point );
      std::swap( next_surface_id, final_surface_id );
    }
  }
  else if( polygon_orientation == RIGHT_HANDED )
  {
    if( !LAP::isAntiparallel( polygon_plane_normal, point_1_2_3_cross_product))
    {
      std::swap( first_point, third_point );
      std::swap( next_surface_id, final_surface_id );
    }
  }
  
  // Add the points to the polygon list
  ordered_polygon_corners.push_front( *first_point );
  ordered_polygon_corners.push_back( *third_point );
			       
  // Remove the points from the intersection points list
  first_point = unordered_polygon_corners.erase( first_point );
  third_point = unordered_polygon_corners.erase( third_point );

  // Make sure the a valid orientation for the polygon was determined
  testPostcondition( polygon_orientation != INVALID_ORIENTATION )
}

// Find the lexicographically largest point
template<typename OrdinalType, typename ScalarType>
typename std::list<IntersectionPoint<OrdinalType,ScalarType> >::const_iterator
PolygonFactory<OrdinalType,ScalarType>::getLexicographicallyLargestPoint(
	        const std::list<IntersectionPoint> &unordered_polygon_corners )
{

}	 

// Find the next point on the boundary of the polygon
/*! \details If the point may not be found by this function 
   * (POINT_MAY_NOT_BE_FOUND), this function may return an iterator to the
   * end of the list. It is therefore important to test the iterator returned.
   */
template<typename OrdinalType, typename ScalarType>
typename std::list<IntersectionPoint<OrdinalType,ScalarType> >::const_iterator
PolygonFactory<OrdinalType,ScalarType>::getNextPolygonCorner(
	        const OrdinalType desired_surface_id,
	        const Vector<ScalarType> &current_corner,
	        const std::list<IntersectionPoint> &unordered_polygon_corners,
                PointFindNecessity point_find_necessity = POINT_MUST_BE_FOUND )
{

}
			 

} // end FACEMC namespace

#endif // end POLYGON_FACTORY_DEF_HPP

//---------------------------------------------------------------------------//
// end PolygonFactory_def.hpp
//---------------------------------------------------------------------------//
