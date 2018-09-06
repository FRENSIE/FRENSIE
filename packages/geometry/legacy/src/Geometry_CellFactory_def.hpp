//---------------------------------------------------------------------------//
//!
//! \file   Geometry_CellFactory_def.hpp
//! \author Alex Robinson
//! \brief  Cell factory definition
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_CELL_FACTORY_DEF_HPP
#define GEOMETRY_CELL_FACTORY_DEF_HPP

// Std lib includes
#include <string>
#include <map>
#include <algorithm>
#include <iterator>

// Trilinos Includes
#include <Teuchos_ArrayView.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Geometry_Cell.hpp"
#include "Geometry_Surface.hpp"
#include "Geometry_Polygon.hpp"
#include "Geometry_CellPolygonFactory.hpp"
#include "Geometry_VectorHelpers.hpp"
#include "Geometry_IntersectionPointHelpers.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_DesignByContract.hpp"

namespace Geometry{

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
    {
      if( cell->isAnalyticallyIntegrable() )
	calculatePolyhedralCellVolumeAndArea( cell );
      else
      {
	std::cout << "Warning: the volume of polyhedral cell "
		  << id
		  << " cannot be calculated due to its complexity"
		  << std::endl;
      }
    }
    else
    {
      //calculateRotationallySymmetricCellVolumeAndArea( cell );

      std::cout << "Warning: the volume of a non-polyhedral cell ("
		<< id
		<< ") cannot currently be calculated." << std::endl;

      cell->setVolume( 1.0 );

      typename Cell::SurfaceSensePairsIterator cell_surface =
	cell->beginSurfaceSensePairs();

      while( cell_surface != cell->endSurfaceSensePairs() )
      {
	cell->setSurfaceArea( cell_surface->first->getId(), 1.0 );

	++cell_surface;
      }
    }
  }

  return cell;
}

// Calculate the volume and area of a polyhedral cell
template<typename Cell, typename SurfaceMap>
void CellFactory<Cell,SurfaceMap>::calculatePolyhedralCellVolumeAndArea( CellPtr &cell ) const
{
  // Make sure that the cell is analytically integrable
  testPrecondition( cell->isAnalyticallyIntegrable() );

  // All surface polygons will be stored in an array
  Teuchos::Array<CellPolygon> cell_polygons;

  // Create the polygons bounding the cell (one for each bounding surface)
  CellFactory<Cell,SurfaceMap>::createBoundingPolygons( cell_polygons, cell );

  // Assign the cell surface areas
  typename Teuchos::Array<CellPolygon>::const_iterator polygon, end_polygon;
  polygon = cell_polygons.begin();
  end_polygon = cell_polygons.end();

  while( polygon != end_polygon )
  {
    cell->setSurfaceArea( polygon->getId(), polygon->getArea() );

    ++polygon;
  }

  scalarType cell_volume =
    CellFactory<Cell,SurfaceMap>::calculatePolyhedralCellVolumeFromPolygons(
							       cell_polygons );
  // Assign the calculated volume to the cell
  cell->setVolume( cell_volume );
}

// Calculate the polygons bounding the cell
template<typename Cell, typename SurfaceMap>
void CellFactory<Cell,SurfaceMap>::createBoundingPolygons(
			            Teuchos::Array<CellPolygon> &cell_polygons,
			            CellPtr &cell )
{
  // Initialize the polygon array
  cell_polygons.clear();

  // Get the surfaces that define the cell
  typename Cell::SurfaceSensePairsIterator surface_sense_pair =
    cell->beginSurfaceSensePairs();
  typename Cell::SurfaceSensePairsIterator end_surface_sense_pair =
    cell->endSurfaceSensePairs();

  // Create a polygon factory for this cell
  CellPolygonFactory<Cell> polygon_factory( cell );

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
    std::list<Point> intersection_points;
    calculateIntersectionPointsOnPlane( intersection_points,
				        surface_sense_pair,
					cell );

    // Create a new ordered list of points (polygon) from the intersections
    typename CellPolygonFactory<Cell>::PolygonPtr current_surface_polygon =
      polygon_factory.create( intersection_points );

    // Add this polygon to the array of cell polygons
    cell_polygons.push_back( *current_surface_polygon );

    // Finished processing the current surface
    ++surface_sense_pair;
  }
}

// Calculate the volume of a polyhedral cell using bounding polygons
template<typename Cell, typename SurfaceMap>
typename CellFactory<Cell,SurfaceMap>::scalarType
CellFactory<Cell,SurfaceMap>::calculatePolyhedralCellVolumeFromPolygons(
				 const Teuchos::Array<CellPolygon> &cell_polygons )
{
  // Initialize the cell volume
  scalarType cell_volume = ST::zero();

  // The reference surface will be parallel to the x-y plane (z=c)
  Vector<scalarType> reference_unit_normal = createZAxisVector<scalarType>();
  scalarType reference_z_position = -ST::rmax();

  typename Teuchos::Array<CellPolygon>::const_iterator polygon, end_polygon;
  polygon = cell_polygons.begin();
  end_polygon = cell_polygons.end();

  while( polygon != end_polygon )
  {
    if( polygon->getMaxZCoordinate() > reference_z_position )
      reference_z_position = polygon->getMaxZCoordinate();

    ++polygon;
  }

  // Calculate the volume contribution from each polygon (V_c = d*A*cos_ang)
  polygon = cell_polygons.begin();
  while( polygon != end_polygon )
  {
    scalarType z_centroid = polygon->getCentroidZCoordinate();

    // d = abs( centroid_z - z_position )
    scalarType distance =
      ST::magnitude( z_centroid - reference_z_position );

    Vector<scalarType> polygon_plane_unit_normal =
      polygon->getPolygonPlaneUnitNormal();

    scalarType cos_angle =
      polygon_plane_unit_normal.angleCosine( reference_unit_normal );

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
// template<typename Cell, typename SurfaceMap>
// void CellFactor<Cell,SurfaceMap>::calculateBoundingBoxFromPolygons(
// 				 BoundingBox &cell_bounding_box,
// 				 const Teuchos::Array<Polygon> &cell_polygons )
// {
//   Pair<scalarType,scalarType> min_max_x_coords( ST::rmax(), -ST::rmax() );
//   Pair<scalarType,scalarType> min_max_y_coords( ST::rmax(), -ST::rmax() );
//   Pair<scalarType,scalarType> min_max_z_coords( ST::rmax(), -ST::rmax() );

//   Teuchos::Array<Polygon>::const_iterator polygon, end_polygon;
//   polygon = cell_polygons.begin();
//   end_polygon = cell_polygons.end();

//   while( polygon != end_polygon )
//   {
//     // find x_min
//     if( polygon->getSmallesXCoordinate() < min_max_x_coords.first )
//       min_max_x_coords.first = polygon->getSmallestXCoordinate();

//     // find x_max
//     if( polygon->getMaxXCoordinate() > min_max_x_coords.second )
//       min_max_x_coords.second = polygon->getMaxXCoordinate();

//     // find y_min
//     if( polygon->getSmallestYCoordinate() < min_max_y_coords.first )
//       min_max_y_coords.first = polygon->getSmallestYCoordinate();

//     // find y_max
//     if( polygon->getMaxYCoordinate() > min_max_y_coords.second )
//       min_max_y_coords.second = polygon->getMaxYCoordinate();

//     // find z_min
//     if( polygon->getSmallestZCoordinate() < min_max_z_coords.first )
//       min_max_z_coords.first = polygon->getSmallestZCoordinate();

//     // find z_max
//     if( polygon->getMaxZCoordinate() > min_max_z_coords.second )
//       min_max_z_coords.second = polygon->getMaxZCoordinate();

//     ++polygon;
//   }

//   // Make sure that the bounding box dimensions found are valid
//   testPostcondition( min_max_x_coords.first < min_max_x_coords.second );
//   testPostcondition( min_max_y_coords.first < min_max_y_coords.second );
//   testPostcondition( min_max_z_coords.first < min_max_z_coords.second );

//   // Assign the dimensions of the bounding box
//   cell_bounding_box.second = min_max_x_coords;
//   cell_bounding_box.third = min_max_y_coords;
//   cell_bounding_box.fourth = min_max_z_coords;
// }

// Calculate the intersection points of planes with a plane of interest
template<typename Cell, typename SurfaceMap>
void CellFactory<Cell,SurfaceMap>::calculateIntersectionPointsOnPlane(
			    std::list<Point> &intersection_points,
			    const typename Cell::SurfaceSensePairsIterator
			    &plane_of_polygon,
			    const CellPtr &cell )
{
  // Make sure that the intersection points list is empty
  intersection_points.clear();

  typename Cell::SurfaceSensePairsIterator secondary_surface =
    cell->beginSurfaceSensePairs();
  typename Cell::SurfaceSensePairsIterator tertiary_surface =
    cell->beginSurfaceSensePairs();
  typename Cell::SurfaceSensePairsIterator end_surface =
    cell->endSurfaceSensePairs();

  // Processed secondary surfaces (the same surf. may appear mult. times)
  std::set<surfaceOrdinalType> processed_secondary_surfaces;
  processed_secondary_surfaces.insert( plane_of_polygon->first->getId() );

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
    Vector<scalarType> primary_surface_normal =
      plane_of_polygon->first->getLinearTermVector();
    Vector<scalarType> secondary_surface_normal =
      secondary_surface->first->getLinearTermVector();

    if( primary_surface_normal.isParallel( secondary_surface_normal ) ||
	primary_surface_normal.isAntiparallel( secondary_surface_normal ) )
    {
      ++secondary_surface;
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
      Vector<scalarType> tertiary_surface_normal =
	tertiary_surface->first->getLinearTermVector();

      if( tertiary_surface_normal.isParallel( primary_surface_normal ) ||
	  tertiary_surface_normal.isAntiparallel( primary_surface_normal )||
	  tertiary_surface_normal.isParallel( secondary_surface_normal )||
	  tertiary_surface_normal.isAntiparallel( secondary_surface_normal ) )
      {
	  ++tertiary_surface;
	  continue;
      }

      // Calculate the intersection point
      Point intersection_point =
	createIntersectionPoint( *(plane_of_polygon->first),
				 *(secondary_surface->first),
				 *(tertiary_surface->first) );

      // Test if the intersection point is on the cell
      bool possible_intersection_point =
	cell->isOn( intersection_point.getXCoordinate(),
		    intersection_point.getYCoordinate(),
		    intersection_point.getZCoordinate() );

      // Test if the intersection point is real
      bool real_intersection_point = false;
      if( possible_intersection_point )
      {
	real_intersection_point =
	  intersection_point.isRealIntersectionPoint( *cell );
      }

      // If a real intersection point has been found, add it to the list
      if( real_intersection_point )
	intersection_points.push_back( intersection_point );

      ++tertiary_surface;
    }

    ++secondary_surface;
  }
}

} // end Geometry namespace

#endif // end GEOMETRY_CELL_FACTORY_DEF_HPP

//---------------------------------------------------------------------------//
// end Geometry_CellFactory_def.hpp
//---------------------------------------------------------------------------//
