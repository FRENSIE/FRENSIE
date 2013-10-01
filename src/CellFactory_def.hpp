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
    calculateIntersectionPoints( surface_sense_pair,
				 cell,
				 intersection_points );

    // Rotate the intersection points to the x-y plane
    Matrix rotation_matrix;
    Vector translation_vector;
    transformIntersectionPoints( surface_sense_pair,
			      intersection_points,
			      rotation_matrix,
			      translation_vector );

    Surface reference_surface( reference_surface_sense_pair->first->getId(),
			       *(reference_surface_sense_pair->first),
			       rotation_matrix,
			       translation_vector );

    // Create a new polygon from the intersection points
    std::list<Pair<ScalarType,ScalarType> > polgon;
    createPolygon( intersection_points, cell, polygon );

    // Calculate the area of the polygon (current surface)
    ScalarType area = calculatePolygonArea( polygon );
    cell->setSurfaceArea( surface_sense_pair->first->getId(),
			  area );
    
    // Calculate the volume contribution from this surface
    ScalarType volume += calculatePolygonVolumeContribution( 
					polygon,
					reference_surface,
					surface_sense_pair->second,
					reference_surface_sense_pair->second );
    
    ++surface_sense_pair;
  }
  
  // Make sure that the volume calculated is valid
  testPostcondition( volume > ST::zero() );
  testPostcondition( !ST::isnaninf( volume ) );

  cell->setVolume( volume );
}

template<typename Cell, typename SurfaceMap>
void CellFactory<Cell,SurfaceMap>::calculateIntersectionPoints(
			     const SurfaceSensePairsIterator &plane_of_polygon,
			     const CellPtr &cell,
			     std::list<IntersectionPoints>
			     &intersection_points ) const
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

// Rotate the intersection points to the x-y plane
template<typename Cell, typename SurfaceMap>
void CellFactory<Cell,SurfaceMap>::transformIntersectionPoints(
			    const SurfaceSensePairsIterator &plane_of_polygon,
			    std::list<IntersectionPoints> &intersection_points,
			    Matrix &rotation_matrix,
			    Vector &translation_vector ) const	   
{
  // Create the necessary rotation matrix
  Vector plane_of_polygon_normal = 
    plane_of_polygon->first->getLinearTermVector();
  rotation_matrix = LAP::createRotationMatrixFromUnitVectors( 
			                             ThreeSpace::zaxisVector(),
						     plane_of_polygon_normal );

  // Create the necessary translation vector
  translation_vector = LAP::createZeroingVector( 
				  plane_of_polygon_normal,
				  plane_of_polygon->first->getConstantTerm() );

  // Transform each intersection point
  typename std::list<IntersectionPoint>::iterator intersection_point =
    intersection_points.begin();
  typename std::list<IntersectionPoint>::iterator end_intersection_point = 
    intersection_points.end();

  remember( bool multiply_success = true );
  remember( bool all_points_on_xy_plane = true );

  while( intersection_point != end_intersection_point )
  {
    Vector point_coordinates = ThreeSpace::createVector( 
					    intersection_point->first.first,
					    intersection_point->first.second,
					    intersection_point->first.third );
    
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

    // Reassign the intersection point coordinates
    intersection_point->first.first = transformed_point_coordinates[0];
    intersection_point->first.second = transformed_point_coordinates[1];
    intersection_point->first.third = transformed_point_coordinates[2];

    remember( bool this_point_on_xy_plane = 
	      (ST::magnitude(intersection_point->first.third) < ST::prec()) );
    remember( all_points_on_xy_plane = (this_point_on_xy_plane) ? 
	      all_points_on_xy_plane : this_point_on_xy_plane );
    
    ++intersection_point;
  }
					    
  // Make sure that all multiplications were successful
  testPostcondition( multiply_success );
  // Make sure that the transformation was successful
  testPostcondition( all_points_on_xy_plane );
}

// Create a polygon from intersection points
template<typename Cell, typename Surfacemap>
void CellFactory<Cell,SurfaceMap>::createPolygon( 
		      const std::list<IntersectionPoints> &intersection_points,
		      const CellPtr &Cell,
		      std::list<Pair<ScalarType,ScalarType> > &polygon ) const
{

}

// Calculate the area of a polygon
template<typename Cell, typename SurfaceMap>
ScalarType CellFactory<Cell,SurfaceMap>::calculatePolygonArea(
		 const std::list<Pair<ScalarType,ScalarType> > &polygon ) const
{

}

// Calculate the volume contribution from a surface bounding this cell
template<typename Cell, typename SurfaceMap>
ScalarType CellFactory<Cell,SurfaceMap>::calculatePolygonVolumeContribution(
			const std::list<Pair<ScalarType,ScalarType> > &polygon,
			const Surface &reference_surface,
			SurfaceSense polygon_sense,
			SurfaceSense reference_sense )	
{

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
