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
#include "Polygon.hpp"
#include "Tuple.hpp"
#include "ContractException.hpp"

namespace FACEMC{

// Constructor
template<typename Cell, typename SurfaceMap>
CellFactory<Cell,SurfaceMap>::CellFactory( 
					 const SurfaceMap &global_surface_map )
: d_global_surface_map( Teuchos::rcpFromRef( global_surface_map ) )
{ 
  // A valid SurfaceMap type must be used
  testStaticPrecondition((boost::is_same<typename SurfaceMap::key_type,typename SurfaceMap::mapped_type::element_type::ordinalType>::value));
  // The map properties must match the cell properties
  testStaticPrecondition((boost::is_same<typename SurfaceMap::key_type,typename Cell::surfaceOrdinalType>::value));
  testStaticPrecondition((boost::is_same<typename SurfaceMap::mapped_type::element_type::scalarType,typename Cell::scalarType>::value));
}

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

// Calculate the volume and area of a polyhedral cell
template<typename Cell, typename SurfaceMap>
void CellFactory<Cell,SurfaceMap>::calculatePolyhedralCellVolumeAndArea( CellPtr &cell ) const
{
  // All surface polygons will be stored in an array
  Teuchos::Array<Polygon> cell_polygons;
  
  // Create the polygons bounding the cell (one for each bounding surface)
  CellFactory<Cell,SurfaceMap>::createBoundingPolygons( cell_polygons, cell );

  // Assign the cell surface areas
  typename Teuchos::Array<Polygon>::const_iterator polygon, end_polygon;
  polygon = cell_polygons.begin();
  end_polygon = cell_polygons.end();

  while( polygon != end_polygon );
  {
    cell->setSurfaceArea( polygon->getId(), polygon->getArea() );

    ++polygon;
  }
  
  // Determine if this cell can have its volume calculated analytically
  bool calculate_volume_analytically = 
    CellFactory<Cell,SurfaceMap>::isPolyhedronAnalyticallyIntegrable( cell );
  
  // Calculate the cell volume analytically if it is possible
  if( calculate_volume_analytically )
  {
    scalarType cell_volume = 
      CellFactory<Cell,SurfaceMap>::calculatePolyhedralCellVolumeFromPolygons(
							       cell_polygons );
    // Assign the calculate volume to the cell
    cell->setVolume( volume );
  }
  
  // Create a bounding box for a Monte Carlo calc of the volume
  else
  {
    BoundingBox cell_bounding_box;
    CellFactor<Cell,SurfaceMap>::createBoundingBoxFromPolygons( 
							     cell_bounding_box,
							     cell_polygons );
    
    // Assign the cell id and the numerical calculation type
    cell_bounding_box.first.first = cell->getId();
    cell_bounding_box.first.second = CELL_VOLUME;

    // add this bounding box to the array of bounding boxes
    d_bounding_boxes.push_back( cell_bounding_box );
  }
}

// Calculate the polygons bounding the cell
template<typename Cell, typename SurfaceMap>
void CellFactory<Cell,SurfaceMap>::createBoundingPolygons(
							  const Teuchos::Array<Polygon> &cell_polygons,
							  CellPtr &cell )
{
  // Initialize the polygon array
  cell_polygons.clear();
  
  // Get the surfaces that define the cell
  SurfaceSensePairsIterator surface_sense_pair = 
    cell->beginSurfaceSensePairs();
  SurfaceSensePairsIterator end_surface_sense_pair = 
    cell->endSurfaceSensePairs();

  // Processed surfaces (the same surf. may appear more than once in cell def)
  std::set<typename Cell::surfaceOrdinalType> processed_surfaces;
  
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

    // Create a new ordered list of points (polygon) from the intersections
    Polygon current_surface_polygon =
      createPolygonFromIntersectionPoints( intersection_points, cell );

    // Add this polygon to the array of cell polygons
    cell_polygons.push_back( current_surface_polygon );

    // Finished processing the current surface
    ++surface_sense_pair
  }
}

// Calculate the volume of a polyhedral cell using bounding polygons
template<typename Cell, typename SurfaceMap>
scalarType 
CellFactor<Cell,SurfaceMap>::calculatePolyhedralCellVolumeFromPolygons(
				 const Teuchos::Array<Polygon> &cell_polygons )
{
  // Initialize the cell volume
  scalarType cell_volume = ST::zero();
  
  // The reference surface will be parallel to the x-y plane (z=c)
  Vector reference_unit_normal = ThreeSpace::zaxisVector();
  scalarType reference_z_position = -ST::rmax();
    
  Teuchos::Array<Polygon>::const_iterator polygon, polygon_end;
  polygon = cell_polygons.begin();
  polygon_end = cell_polygons.end();

  while( polygon != end_polygon )
  {
    if( polygon->getMaxZCoordinate() > z_position )
      reference_z_position = polygon->getMaxZCoordinate();
    
    ++polygon;
  }
    
  // Calculate the volume contribution from each polygon (V_c = d*A*cos_ang)
  polygon = cell_polygons.begin();
  while( polygon != end_polygon )
  {
    Vector polygon_plane_unit_normal = polygon->getPolygonPlaneUnitNormal();
    
    typename Polygon::Point z_centroid = polygon->getCentroidZCoordinate();
    
    // d = abs( reference_plane_z*centroid_z - z_position )
    scalarType distance = 
      ST::magnitude( polygon_plane_unit_normal[2]*z_centroid - 
		     reference_z_position );
    
    scalarType cos_angle = 
      LAP::computeAngleBetweenVectors( polygon_plane_unit_normal,
				       reference_unit_normal );
    
    scalarType polygon_area = polygon->getArea();
    
    // Add the contribution to the cell volume
    cell_volume += distance*polygon_area*cos_angle;
    
    ++polygon;
  }

  // Make sure that the volume is physical
  testPostcondition( cell_volume > ST::zero() );
  testPostcondition( !ST::isnaninf( cell_volume ) );

  return cell_volume;
}

// Create a bounding box for a polyhedral cell from bounding polygons
template<typename Cell, typename SurfaceMap>
void CellFactor<Cell,SurfaceMap>::calculateBoundingBoxFromPolygons(
				 BoundingBox &cell_bounding_box,
				 const Teuchos::Array<Polygon> &cell_polygons )
{
  Pair<scalarType,scalarType> min_max_x_coords( ST::rmax(), -ST::rmax() );
  Pair<scalarType,scalarType> min_max_y_coords( ST::rmax(), -ST::rmax() );
  Pair<scalarType,scalarType> min_max_z_coords( ST::rmax(), -ST::rmax() );
    
  Teuchos::Array<Polygon>::const_iterator polygon, end_polygon;
  polygon = cell_polygons.begin();
  end_polygon = cell_polygons.end();
  
  while( polygon != end_polygon )
  {
    // find x_min
    if( polygon->getSmallesXCoordinate() < min_max_x_coords.first )
      min_max_x_coords.first = polygon->getSmallestXCoordinate();
    
    // find x_max
    if( polygon->getMaxXCoordinate() > min_max_x_coords.second )
      min_max_x_coords.second = polygon->getMaxXCoordinate();
    
    // find y_min
    if( polygon->getSmallestYCoordinate() < min_max_y_coords.first )
      min_max_y_coords.first = polygon->getSmallestYCoordinate();
    
    // find y_max
    if( polygon->getMaxYCoordinate() > min_max_y_coords.second )
      min_max_y_coords.second = polygon->getMaxYCoordinate();
    
    // find z_min
    if( polygon->getSmallestZCoordinate() < min_max_z_coords.first )
      min_max_z_coords.first = polygon->getSmallestZCoordinate();
    
    // find z_max
    if( polygon->getMaxZCoordinate() > min_max_z_coords.second )
      min_max_z_coords.second = polygon->getMaxZCoordinate();
    
    ++polygon;
  }

  // Make sure that the bounding box dimensions found are valid
  testPostcondition( min_max_x_coords.first < min_max_x_coords.second );
  testPostcondition( min_max_y_coords.first < min_max_y_coords.second );
  testPostcondition( min_max_z_coords.first < min_max_z_coords.second );

  // Assign the dimensions of the bounding box
  cell_bounding_box.second = min_max_x_coords;
  cell_bounding_box.third = min_max_y_coords;
  cell_bounding_box.fourth = min_max_z_coords;
}

// Calculate the intersection points of planes with a plane of interest
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
  std::set<surfaceOrdinalType> processed_secondary_surfaces;
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

// Find the first three points on the boundary of the polygon
template<typename Cell, typename SurfaceMap>
typename std::list<PolygonCorner>::const_iterator
CellFactory<Cell,SurfaceMap>::initializePolygonCorners( 
		     std::list<PolygonCorner> &oriented_polygon_corners,
		     std::list<IntersectionPoint> &intersection_points,
		     const CellPtr &cell,
		     surfaceOrdinalType &current_surface_id ) const
{
  
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
