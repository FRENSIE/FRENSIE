//---------------------------------------------------------------------------//
//!
//! \file   Cell_def.hpp
//! \author Alex Robinson
//! \brief  Cell class definition
//!
//---------------------------------------------------------------------------//

#ifndef CELL_DEF_HPP
#define CELL_DEF_HPP

// Std Lib Includes
#include <string>
#include <sstream>
#include <map>
#include <iterator>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayView.hpp>
#include <Teuchos_Tuple.hpp>
#include <Teuchos_RCP.hpp>

// FACEMC Includes
#include "Surface.hpp"
#include "Tuple.hpp"
#include "ContractException.hpp"
#include "FACEMC_Assertion.hpp"

namespace FACEMC{

//! Constructor
template<typename CellOrdinalType,
	 typename SurfaceOrdinalType,
	 typename ScalarType,
	 typename SurfaceMap>
Cell<CellOrdinalType,
     SurfaceOrdinalType,
     ScalarType,
     SurfaceMap>::Cell( const CellOrdinalType id,
			std::string &cell_definition,
			const SurfaceMap &global_surface_map )
  : d_id( id ), 
    d_cell_definition_evaluator( cell_definition ), 
    d_volume( 0.0 )
{
  // Remove all characters from the cell definition string except for the ids
  Cell<CellOrdinalType,
       SurfaceOrdinalType,
       ScalarType,
       SurfaceMap>::simplifyCellDefinitionString( cell_definition );
  
  // Query the surface map and assign the surfaces that define this cell
  assignSurfaces( cell_definition, global_surface_map );

  // Initialize the surface id-area map
  Teuchos::Array<Pair<Teuchos::RCP<Surface>,SurfaceSense> >::const_iterator
    surface_sense_pair, end_surface_sense_pair;

  surface_sense_pair = d_surface_sense_pairs.begin();
  end_surface_sense_pair = d_surface_sense_pair.end();

  while( surface_sense_pair != end_surface_sense_pair )
  {
    d_surface_id_area_map[surface_sense_pair->first->getId()] = ST::zero();
    
    ++surface_sense_pair;
  }
}

// Return if the point is in the cell
template<typename CellOrdinalType, 
	 typename SurfaceOrdinalType, 
	 typename ScalarType,
	 typename SurfaceMap>
bool Cell<CellOrdinalType,
	  SurfaceOrdinalType,
	  ScalarType,
	  SurfaceMap>::isIn( const Vector &point ) const
{
  return isIn( point[0], point[1], point[2] );
}

// Return if the point is in the cell
template<typename CellOrdinalType, 
	 typename SurfaceOrdinalType, 
	 typename ScalarType,
	 typename SurfaceMap>
bool Cell<CellOrdinalType,
	  SurfaceOrdinalType,
	  ScalarType,
	  SurfaceMap>::isIn( const ScalarType x,
			     const ScalarType y,
			     const ScalarType z ) const
{
  Teuchos::Array<Pair<Teuchos::RCP<Surface>,SurfaceSense> >::const_iterator
    surface_sense_pair, end_surface_sense_pair;
  surface_sense_pair = d_surface_sense_pairs.begin();
  end_surface_sense_pair = d_surface_sense_pairs.end();

  // Sense of the point with respect to the surface of interest
  SurfaceSense sense;

  // If the sense matches the cell surface sense, true is added to this array
  // else false is added (The surface ordering is the same as in the 
  // d_surfaces_sense_pair array)
  Teuchos::ArrayRCP<bool> sense_tests( d_surfaces.size() );
  Teuchos::ArrayRCP<bool>::iterator test = sense_tests.begin();

  while( surface_sense_pair != end_surface_sense_pair )
  {
    sense = surface_sense_pair->first->getSense( x, y, z );
    
    if( sense == surface_sense_pair->second )
      *test = true;
    else
      *test = false;
    
    ++surface;
    ++test;
  }

  return d_cell_definition_evaluator( sense_tests );
}

// Return if the point is on the cell
template<typename CellOrdinalType, 
	 typename SurfaceOrdinalType, 
	 typename ScalarType,
	 typename SurfaceMap>
bool Cell<CellOrdinalType,
	  SurfaceOrdinalType,
	  ScalarType,
	  SurfaceMap>::isOn( const Vector &point ) const
{
  return isOn( point[0], point[1], point[2] );
}

//! Return if the point is on the cell
template<typename CellOrdinalType, 
	 typename SurfaceOrdinalType,
	 typename ScalarType,
	 typename SurfaceMap>
bool Cell<CellOrdinalType,
	  SurfaceOrdinalType,
	  ScalarType,
	  SurfaceMap>::isOn( const ScalarType x,
			     const ScalarType y,
			     const ScalarType z ) const
{
  Teuchos::Array<Pair<Teuchos::RCP<Surface>,Surface::Sense> >::const_iterator
    surface_sense_pair, end_surface_sense_pair;
  surface_sense_pair = d_surface_sense_pairs.begin();
  end_surface_sense_pair = d_surface_sense_pairs.end();

  // Sense of the point with respect to the surface of interest
  SurfaceSense sense;

  // If the sense matches the cell surface sense, true is added to this array
  // else false is added (The surface ordering is the same as in the d_surfaces
  // array)
  Teuchos::ArrayRCP<bool> sense_tests( d_surfaces.size() );
  Teuchos::ArrayRCP<bool>::iterator test = sense_tests.begin();

  while( surface_sense_pair != end_surface_sense_pair )
  {
    sense = surface_sense_pair->first->getSense( x, y, z );
    
    if( sense == surface_sense_pair->second || sense == ON_SURFACE )
      *test = true;
    else
      *test = false;
    
    ++surface;
    ++test;
  }

  return d_cell_definition_evaluator( sense_tests );
}

// Return if the cell is a polyhedron
template<typename CellOrdinalType, 
	 typename SurfaceOrdinalType, 
	 typename ScalarType,
	 typename SurfaceMap>
bool Cell<CellOrdinalType,
	  SurfaceOrdinalType,
	  ScalarType,
	  SurfaceMap>::isPolyhedron() const
{
  Teuchos::Array<Pair<Teuchos::RCP<Surface>,Surface::Sense> >::const_iterator
    surface_sense_pair, end_surface_sense_pair;
  surface_sense_pair = d_surface_sense_pairs.begin();
  end_surface_sense_pair = d_surface_sense_pairs.end();

  bool all_planar_surfaces = true;

  // Test that all surfaces are planar
  while( surface_sense_pair != end_surface_sense_pair )
  {
    if( !surface_sense_pair->first->isPlanar() )
    {
      all_planar_surfaces = false;
      break;
    }
  }
  
  return all_planar_surfaces;
}

// Return the volume of the cell
template<typename CellOrdinalType, 
	 typename SurfaceOrdinalType, 
	 typename ScalarType,
	 typename SurfaceMap>
ScalarType Cell<CellOrdinalType,
		SurfaceOrdinalType,
		ScalarType,
		SurfaceMap>::getVolume() const
{  
  // Make sure that the cell volume returned is valid
  testPostcondition( d_volume > ST::zero() );
  testPostcondition( !ST::isnaninf( d_volume );
  return d_volume;
}

// Manually set the volume of the cell
template<typename CellOrdinalType, 
	 typename SurfaceOrdinalType, 
	 typename ScalarType,
	 typename SurfaceMap>
void Cell<CellOrdinalType,
	  SurfaceOrdinalType,
	  ScalarType,
	  SurfaceMap>::setVolume( const ScalarType volume )
{
  // Make sure that the cell volume assigned is valid
  testPrecondition( d_volume > ST::zero() );
  testPrecondition( !ST::isnaninf( d_volume ) );
  d_volume = volume;
}

// Return the area of a surface bounding the cell
template<typename CellOrdinalType, 
	 typename SurfaceOrdinalType, 
	 typename ScalarType,
	 typename SurfaceMap>
ScalarType Cell<CellOrdinalType,
		SurfaceOrdinalType,
		ScalarType,
		SurfaceMap>::getSurfaceArea( 
				    const SurfaceOrdinalType surface_id ) const
{
  // The requested surface must be present in the cell (and have area data)
  testPrecondition( d_surface_id_area_map.count( surface_id ) > 0 );

  typename SurfaceAreaMap::const_iterator surface_id_area_pair;
  typename SurfaceAreaMap::const_iterator end_surface_id_area_pair = 
    d_surface_id_area_map.end();
  
  surface_id_area_pair = d_surface_id_area_map.find( surface_id );

  ScalarType area;
  
  if( surface_id_area_pair != end_surface_id_area_pair )
    area =  surface_id_area_pair->second;
  else
    area = ST::zero();

  // Make sure that the surface area returned is valid
  testPostcondition( area > ST::zero() );
  testPostcondition( !ST::isnaninf( area ) );
}
  
// Return the area of a surface bounding the cell
template<typename CellOrdinalType, 
	 typename SurfaceOrdinalType, 
	 typename ScalarType,
	 typename SurfaceMap>
void Cell<CellOrdinalType,
	  SurfaceOrdinalType,
	  ScalarType,
	  SurfaceMap>::setSurfaceArea( const SurfaceOrdinalType surface_id,
				       const ScalarType surface_area ) 
{
  // The requested surface must be present in the cell (and have area data)
  testPrecondition( d_surface_id_area_map.count( surface_id ) > 0 );
  // Make sure that the surface area is valid
  testPrecondition( surface_area > ST::zero() );
  testPrecondition( !ST::isnaninf() );

  SurfaceAreaMap::iterator surface_id_area_pair;
  surface_id_area_pair = d_surface_id_area_map.find( surface_id );

  surface_id_area_pair->second = surface_area;
}

// Get a const iterator to the beginning of the surface sense pairs array
template<typename CellOrdinalType, 
	 typename SurfaceOrdinalType, 
	 typename ScalarType,
	 typename SurfaceMap>
inline Cell<CellOrdinalType,
	    SurfaceOrdinalType,
	    ScalarType,
	    SurfaceMap>::SurfaceSensePairsIterator
Cell<CellOrdinalType,
     SurfaceOrdinalType,
     ScalarType,
     SurfaceMap>::beginSurfaceSensePairs() const
{  
  return d_surface_sense_pairs.begin();
}

// Get a const iterator to the end of the surface sense pairs array
template<typename CellOrdinalType, 
	 typename SurfaceOrdinalType, 
	 typename ScalarType,
	 typename SurfaceMap>
inline Cell<CellOrdinalType,
	    SurfaceOrdinalType,
	    ScalarType,
	    SurfaceMap>::SurfaceSensePairsIterator
Cell<CellOrdinalType,
     SurfaceOrdinalType,
     ScalarType,
     SurfaceMap>::endSurfaceSensePairs() const
{  
  return d_surface_sense_pairs.end();
}

// Get a const iterator to a specific surface-sense pair in container
template<typename CellOrdinalType, 
	 typename SurfaceOrdinalType, 
	 typename ScalarType,
	 typename SurfaceMap>
Cell<CellOrdinalType,
     SurfaceOrdinalType,
     ScalarType,
     SurfaceMap>::SurfaceSensePairsIterator
Cell<CellOrdinalType,
     SurfaceOrdinalType,
     ScalarType,
     SurfaceMap>::getSurfaceSensePair( 
				    const SurfaceOrdinalType surface_id ) const
{
  SurfaceSensePairsIterator surface_sense_pair =
    d_surface_sense_pairs.begin();
  SurfaceSensePairsIterator end_surface_sense_pair = 
    d_surface_sense_pairs.end();
  
  while( surface_sense_pair != end_surface_sense_pair )
  {
    if( surface_sense_pair->first->getId() == surface_id )
      break;
  }

  // Make sure that the desired surface was found
  testPostcondition( surface_sense_pair != end_surface_sense_pair );

  return surface_sense_pair;
}

// Evaluate the cell definition
template<typename CellOrdinalType, 
	 typename SurfaceOrdinalType, 
	 typename ScalarType,
	 typename SurfaceMap>
bool Cell<CellOrdinalType,
	  SurfaceOrdinalType,
	  ScalarType,
	  SurfaceMap>::isCellPresent( Teuchos::ArrayRCP<bool> &surface_tests )
{
  return d_cell_definition_evaluator( surface_tests );
}

// Strip the cell definition string of set operation characters
template<typename CellOrdinalType, 
	 typename SurfaceOrdinalType, 
	 typename ScalarType,
	 typename SurfaceMap>
void Cell<CellOrdinalType,
	  SurfaceOrdinalType,
	  ScalarType,
	  SurfaceMap>::simplifyCellDefinitionString( 
						 std::string &cell_definition )
{
  // The cell definition must be valid
  testPrecondition( cell_definition.find_first_not_of( "0123456789-nu() ", 0 ) 
		    == std::string::npos );
  // The cell definition must not contain free floating negative signs
  testPrecondition( cell_definition.find( "- ", 0 ) == std::string::npos );
  // The cell definition must not contain any double negative signs
  testPrecondition( cell_definition.find( "--", 0 ) == std::string::npos );

  std::string operation_characters( "nu()" );

  unsigned operation_loc = 
    cell_definition.find_first_of( operation_characters );

  // Remove the set operation characters
  while( operation_loc < cell_definition.size() )
  {
    cell_definition[operation_loc] = ' ';

    operation_loc = cell_definition.find_first_of( operation_characters,
						   operation_loc+1 );
  }
  
  // Make sure that the cell definition is free of trailing white space
  unsigned end_white_space_loc = 
    cell_definition.find_last_of( "0123456789" ) + 1;

  if( end_white_space_loc < cell_definition.size() )
  {
    cell_definition.erase( end_white_space_loc, 
			   cell_definition.size() - end_white_space_loc );  
  }
}

// Assign surfaces to the cell
template<typename CellOrdinalType, 
	 typename SurfaceOrdinalType, 
	 typename ScalarType,
	 typename SurfaceMap>
void Cell<CellOrdinalType,
	  SurfaceOrdinalType,
	  ScalarType,
	  SurfaceMap>::assignSurfaces( std::string &cell_definition,
				       SurfaceMap &global_surface_map )
{
  // The cell_definition must be simplified
  testPrecondition( cell_definition.find_first_of( "nu()", 0 ) == 
		    std::string::npos );
  // A surface cannot have an id of 0
  testPrecondition( cell_definition.find( " 0 " ) == std::string::npos );
  testPrecondition( cell_definition.find( " -0 " ) == std::string::npos );

  typename SurfaceMap::const_iterator global_surface_sense_pair,
    end_global_surface_sense_pair = global_surface_map.end();
  
  Pair<Teuchos::RCP<Surface>,SurfaceSense> local_surface_sense_pair;

  std::stringstream simplified_cell_definition( cell_definition );
  SurfaceOrdinalType surface_id_with_sense, surface_id;
  SurfaceSense surface_sense;
  bool surface_exists = true;

  while( simplified_cell_definition )
  {
    simplified_cell_definition >> surface_id_with_sense;
    
    if( surface_id_with_sense < SurfaceOT::zero() )
    {
      surface_sense = NEG_SURFACE_SENSE;
      surface_id = surface_id_with_sense*(-Surface::OT::one());
    }
    else
    {
      surface_sense = POS_SURFACE_SENSE;
      surface_id = surface_id_with_sense;
    }

    // Pull the surface from the global map
    global_surface_sense_pair = global_surface_map.find( surface_id );

    if( global_surface_sense_pair == end_global_surface_sense_pair )
      surface_exists = false;
    
    // If the surface was not found exit the program
    FACEMC_ASSERT_ALWAYS_MSG( surface_exists, "Fatal Error: Surface " << surface_id << " requested by Cell " << d_id << " does not exist." );

    // Store this surface
    local_surface.first = global_surface->second;
    local_surface.second = surface_sense;
    d_surfaces.push_back( local_surface );
    
    // Remove the next whitespace from the cell_definition
    simplified_cell_definition.ignore();
  }
  
  // Make sure that at least one surface was assigned to the cell
  testPostcondition( d_surface_sense_pairs.size() > 0 );
}

//! Calculate the cell volume and surface areas of the bounding surfaces
void Cell::calculateVolumeAndSurfaceAreas()
{
  // Check if the cell is a Polyhedron
  bool is_polyhedron = true;
  
  Teuchos::Array<Pair<Teuchos::RCP<Surface>,Surface::Sense> >::const_iterator
    surface, end_surface;
  surface = d_surfaces.begin();
  end_surface = d_surfaces.end();

  while( surface != end_surface )
  {
    if( !surface->first->isPlanar() )
    {
      is_polyhedron = false;
      break;
    }

    ++surface;
  }

  if( is_polyhedron )
    calculatePolyhedralCellVolumeAndSurfaceAreas();
  else
  {
    // Calculate the rotationally symmetric cell volume and surface areas
    bool success = calculateRotationallySymmetricCellVolumeAndSurfaceAreas();

    // Calculate the generic cell volume and surface areas using brute force
    // Monte Carlo integration
    if( !success )
      calculateVolumeAndSurfaceAreasUsingMonteCarlo();
  }
}  

//! Calculate the polyhedron volume and surface areas
void Cell::calculatePolyhedralCellVolumeAndSurfaceAreas()
{
  // Reference surface for calculating volume of polyhedron 
  Surface reference_surface = *d_surfaces[0].first;
  Surface::Sense reference_surface_sense = d_surfaces[0].second;
  
  // Z-axis unit normal
  Surface::Vector z_axis = Teuchos::tuple( 0.0, 0.0, 1.0 );

  // Processed surfaces (the same surface may appear more than once in a cell
  // definition)
  std::set<unsigned> processed_surfaces;

  // For every surface, transform the cell so that the surface is the x-y plane
  for( unsigned i = 0; i < d_surfaces.size(); ++i )
  {
    // Only use a surface if it hasn't been processed yet
    if( processed_surfaces.find( d_surfaces[i].first->getId() ) != 
	processed_surfaces.end() )
      continue;
    else
      processed_surfaces.insert( d_surfaces[i].first->getId() );
      
    // Make a copy of the surfaces that make up this cell
    Teuchos::Array<Pair<Surface,Surface::Sense> > copy_surfaces;
    Surface copy_reference_surface = reference_surface;
  
    {
      Teuchos::Array<Pair<Teuchos::RCP<Surface>,Surface::Sense> >::const_iterator surface, end_surface;
      surface = d_surfaces.begin();
      end_surface = d_surfaces.end();
    
      while( surface != end_surface )
      {
	Pair<Surface,Surface::Sense> 
	  copied_surface( *(surface->first), surface->second );
	
	copy_surfaces.push_back( copied_surface );
	
	++surface;
      }
    }
    
    Teuchos::Array<Pair<Surface,Surface::Sense> >::iterator 
      master_surface, surface, end_surface;

    // Specify the surface that will have its area and volume constribution 
    // calculated (master surface)
    master_surface = copy_surfaces.begin();
    std::advance( master_surface, i );

    surface = copy_surfaces.begin();
    end_surface = copy_surfaces.end();

    // Create a rotation matrix that will be used to rotate the master surface 
    // to the z-axis
    Surface::Vector master_unit_normal = 
      master_surface->first.getLinearTermVector();
    LinearAlgebra::normalizeVector( master_unit_normal );

    Surface::Matrix master_rotation_matrix = 
      LinearAlgebra::generateRotationMatrixFromUnitVectors( z_axis,
							    master_unit_normal );
    // Translation vector that will be used to move the rotated master surface
    // to the z=0 plane
    Surface::Vector master_translation_vector;
    if( fabs(master_unit_normal[0]) > 1e-12 )
    {
      master_translation_vector = 
	Teuchos::tuple( -master_surface->first.getConstantTerm()/
			master_unit_normal[0], 0.0, 0.0 );
    }
    else if( fabs(master_unit_normal[1]) > 1e-12 )
    {
      master_translation_vector = 
	Teuchos::tuple( 0.0, -master_surface->first.getConstantTerm()/
			master_unit_normal[1], 0.0 );
    }
    else
    {
      master_translation_vector = 
	Teuchos::tuple( 0.0, 0.0, -master_surface->first.getConstantTerm()/
			master_unit_normal[2] );
    }
      
    // Transform all surfaces
    copy_reference_surface.transformSurface( master_rotation_matrix,
					     master_translation_vector );
    while( surface != end_surface )
    {
      surface->first.transformSurface( master_rotation_matrix,
				       master_translation_vector );
      ++surface;
    }
	  
    // Determine the intersection points with the master surface (z=0 plane)
    std::list<Quad<double,double,unsigned,unsigned> > intersection_points;
    calculatePolygonIntersectionPoints( master_surface->first.getId(),
					copy_surfaces,
					intersection_points );
    //std::list<Quad<double,double,unsigned,unsigned> >::const_iterator
    //start = intersection_points.begin(), end = intersection_points.end();
    //std::cout << master_surface->first.getId() << ": " 
    //	      << intersection_points.size() << std::endl;
    //while( start != end )
    //{
    //std::cout << "{" << start->first << "," << start->second
    //		<< "," << start->third << "," << start->fourth << "} ";
    //++start;
    //}
    //std::cout << std::endl;
    // Organize the points into a polygon (polygons)
    createPolygon( intersection_points,
		   copy_surfaces );
    std::list<Quad<double,double,unsigned,unsigned> >::const_iterator
    start = intersection_points.begin(), end = intersection_points.end();
    std::cout << master_surface->first.getId() << ": " 
    	      << intersection_points.size() << std::endl;
    while( start != end )
    {
      std::cout << "{" << start->first << "," << start->second
    		<< "," << start->third << "," << start->fourth << "} ";
      ++start;
    }
    std::cout << std::endl;
    std::list<double> polygon_areas;
    
    // Calculate the area of the master surface
    calculatePolygonArea( master_surface->first.getId(),
			  intersection_points,
			  polygon_areas );

    // Assign the correct sign to the polygon areas
    assignPolygonAreaSign( polygon_areas );

    // Calculate the volume contribution from the master surface
    calculatePolygonVolumeContribution( copy_reference_surface,
					intersection_points,
					polygon_areas,
					reference_surface_sense,
					master_surface->second );
  }
}

//! Calculate the intersection points of planes with the z-axis
void Cell::calculatePolygonIntersectionPoints(
			    const unsigned xy_plane_surface_id,
			    const Teuchos::Array<Pair<Surface,Surface::Sense> > 
			    &surfaces,
			    std::list<Quad<double,double,unsigned,unsigned> > 
			    &intersection_points ) const
{
  // Make sure that the intersection points list is empty
  intersection_points.clear();
  
  Teuchos::Array<Pair<Surface,Surface::Sense> >::const_iterator
    master_surface, slave_surface, end_surface;
  master_surface = surfaces.begin();
  end_surface = surfaces.end();

  // Processed surfaces (the same surface may appear more than once in a cell
  // definition)
  std::set<unsigned> processed_surfaces;
  
  while( master_surface != end_surface )
  {
    // Only use a surface if it hasn't been processed yet
    if( processed_surfaces.find( master_surface->first.getId() ) != 
	processed_surfaces.end() )
    {
      ++master_surface;
      continue;
    }
    else
      processed_surfaces.insert( master_surface->first.getId() );
      
    // Check if the master surface is parallel to the z=0 plane
    Surface::Vector master_normal = 
      master_surface->first.getLinearTermVector();
    
    if( fabs(master_normal[0]) < 1e-12 &&
	fabs(master_normal[1]) < 1e-12 )
    {
      ++master_surface;
      continue;
    }

    std::set<unsigned> processed_slave_surfaces;
    
    slave_surface = surfaces.begin();

    while( slave_surface != end_surface )
    {
      // Check if the slave surface has already been processed as a master
      if( processed_surfaces.find( slave_surface->first.getId() ) !=
	  processed_surfaces.end() )
      {
	++slave_surface;
	continue;
      }
      // Check if the slave surface has already been processed as a slave
      else if( processed_slave_surfaces.find( slave_surface->first.getId() ) !=
	       processed_slave_surfaces.end() )
      {
	++slave_surface;
	continue;
      }
      else
	processed_slave_surfaces.insert( slave_surface->first.getId() );

      // Check if an intersection occurs on the z=0 plane
      Surface::Vector slave_normal = 
	slave_surface->first.getLinearTermVector();
      
      if( fabs( master_normal[0]*slave_normal[1] - 
		master_normal[1]*slave_normal[0] ) < 1e-12 )
      {
	++slave_surface;
	continue;
      }	  

      // Calculate the intersection point
      Quad<double,double,unsigned,unsigned> intersection_point;
      
      double master_constant_term = master_surface->first.getConstantTerm();
      double slave_constant_term = slave_surface->first.getConstantTerm();

      // y coordinate
      intersection_point.second = -(slave_normal[0]*master_constant_term -
				    master_normal[0]*slave_constant_term)/
	(slave_normal[0]*master_normal[1] - 
	 master_normal[0]*slave_normal[1]);

      // G1 != 0
      if( fabs(master_normal[0]) > 1e-12 )
      {
	// x coordinate
	intersection_point.first = (-master_constant_term +
	  master_normal[1]*intersection_point.second)/master_normal[0];
      }
      // G2 != 0
      else
      {
	// x coordinate
	intersection_point.first = (-slave_constant_term +
	  slave_normal[1]*intersection_point.second)/slave_normal[0];
      }

      intersection_point.third = master_surface->first.getId();
      intersection_point.fourth = slave_surface->first.getId();

      // Test if the intersection point is on the cell
      bool possible_intersection =
	isOn( Teuchos::tuple( intersection_point.first,
			      intersection_point.second,
			      0.0 ),
	      surfaces );

      // Test if the intersection point is real
      bool true_intersection;
      if( possible_intersection )
      {
	true_intersection = testIntersectionPoint( surfaces,
						   intersection_point,
						   xy_plane_surface_id );
      }
      else
	true_intersection = false;
      
      if( true_intersection )
	intersection_points.push_back( intersection_point );

      ++slave_surface;
    }
    
    ++master_surface;
  }
}

//! Test if an intersection point is real
bool Cell::testIntersectionPoint( 
			    const Teuchos::Array<Pair<Surface,Surface::Sense> > 
			    &surfaces,
			    const Quad<double,double,unsigned,unsigned>
			    &intersection_point,
			    const unsigned third_surface_id ) const
{
  unsigned short delta_value;

  unsigned test_function_value = 0.0;

  for( unsigned int i = 0; i < 8; ++i )
  {
    bool first_surface_boolean_parameter;
    bool second_surface_boolean_parameter;
    bool third_surface_boolean_parameter;
	
    // Note: Assigning the booleans in this order assures that the
    // eighth spaces are evaluated in counter-clockwise order w.r.t.
    // the first surface associated with this intersection point
    if( i == 0 )
    {
      first_surface_boolean_parameter = true;
      second_surface_boolean_parameter = true;
      third_surface_boolean_parameter = true;
    }
    else if( i == 1 )
    {
      first_surface_boolean_parameter = false;
      second_surface_boolean_parameter = true;
      third_surface_boolean_parameter = true;
    }
    else if( i == 2 )
    {
      first_surface_boolean_parameter = false;
      second_surface_boolean_parameter = false;
      third_surface_boolean_parameter = true;
    }
    else if( i == 3 )
    {
      first_surface_boolean_parameter = true;
      second_surface_boolean_parameter = false;
      third_surface_boolean_parameter = true;
    }
    else if( i == 4 )
    {
      first_surface_boolean_parameter = false;
      second_surface_boolean_parameter = true;
      third_surface_boolean_parameter = false;
    }
    else if( i == 5 )
    {
      first_surface_boolean_parameter = false;
      second_surface_boolean_parameter = false;
      third_surface_boolean_parameter = false;
    }
    else if( i == 6 )
    {
      first_surface_boolean_parameter = true;
      second_surface_boolean_parameter = false;
      third_surface_boolean_parameter = false;
    }
    else
    {
      first_surface_boolean_parameter = true;
      second_surface_boolean_parameter = true;
      third_surface_boolean_parameter = false;
    }

    Surface::Vector point = Teuchos::tuple( intersection_point.first,
					    intersection_point.second,
					    0.0 );
	  
    Teuchos::Array<Pair<Surface,Surface::Sense> >::const_iterator
      surface, end_surface;
    surface = surfaces.begin();
    end_surface = surfaces.end();
    
    Teuchos::ArrayRCP<bool> sense_tests( surfaces.size() );
    Teuchos::ArrayRCP<bool>::iterator test = sense_tests.begin();
    
    while( surface != end_surface )
    {
      if( surface->first.getId() == intersection_point.third )
	*test = first_surface_boolean_parameter;
      else if( surface->first.getId() == intersection_point.fourth )
	*test = second_surface_boolean_parameter;
      else if( surface->first.getId() == third_surface_id )
	*test = third_surface_boolean_parameter;
      else
      {
	Surface::Sense sense = surface->first.getSense( point );
	
	if( sense == surface->second || sense == 0 )
	  *test = true;
	else
	  *test = false;
      }
      
      ++surface;
      ++test;
    }
    
    bool cell_present = d_cell_definition_evaluator( sense_tests );
    if( cell_present )
      delta_value = 1;
    else
      delta_value = 0; 

    unsigned multiplier;
    if( i == 0 )
      multiplier = 1;
    else if( i == 1 )
      multiplier = 2;
    else if( i == 2 )
      multiplier = 4;
    else if( i == 3 )
      multiplier = 8;
    else if( i == 4 )
      multiplier = 16;
    else if( i == 5 )
      multiplier = 32;
    else if( i == 6 )
      multiplier = 64;
    else
      multiplier = 128;
    
    // Test function value: SUM( delta_i*2^(i-1); i=0..3 )
    test_function_value += delta_value*multiplier;
  }

  // The intersection is only true if the test function value is not 0 modulo 3
  if( test_function_value%3 != 0 )
    return true;
  else
    return false;
}  

void Cell::createPolygon( std::list<Quad<double,double,unsigned,unsigned> >
			  &intersection_points,
			  const Teuchos::Array<Pair<Surface,Surface::Sense> > 
			  &surfaces ) const
{
  // There must be at least three intersection points to create a polygon
  testPrecondition( intersection_points.size() >= 3 );
  
  std::list<Quad<double,double,unsigned,unsigned> > polygon;
  
  std::list<Quad<double,double,unsigned,unsigned> >::const_iterator start_point;
  std::list<Quad<double,double,unsigned,unsigned> >::iterator
    point, next_point, prev_point, end_point;
  point = intersection_points.begin();
  start_point = point;
  end_point = intersection_points.end();

  // There may be multiple disjoint polygons - keep processing them until
  // all intersection points have been processed
  while( intersection_points.size() > 0 )
  {
    unsigned current_surface_id, next_surface_id;
    
    // Find the first three points on the boundary of the polygon
    start_point = initializePolygon( polygon,
				     intersection_points,
				     surfaces,
				     current_surface_id );

    // Complete the rest of the polygon
    prev_point = polygon.end();
    --prev_point;

    // Continue adding points to the polygon until no more points can be found
    // (break from loop if this happens)
    while( true )
    {
      point = intersection_points.begin();
      end_point = intersection_points.end();
      next_point = end_point;
    
      while( point != end_point )
      {
	if( point->third == current_surface_id ||
	    point->fourth == current_surface_id )
	{
	  if( next_point != end_point )
	  {
	    Teuchos::Tuple<double,3> current_distance_vector = 
	      Teuchos::tuple( next_point->first - prev_point->first,
			      next_point->second - prev_point->second,
			      0.0 );
	    
	    Teuchos::Tuple<double,3> new_distance_vector = 
	      Teuchos::tuple( point->first - prev_point->first,
			      point->second - prev_point->second,
			      0.0 );
	  
	    if( LinearAlgebra::vectorMagnitude( new_distance_vector ) <
		LinearAlgebra::vectorMagnitude( current_distance_vector ) )
	    {
	      next_point = point;
	      if( point->third == current_surface_id )
		next_surface_id = point->fourth;
	      else
		next_surface_id = point->third;
	    }
	  }
	  else
	  {
	    next_point = point;
	    if( point->third == current_surface_id )
	      next_surface_id = point->fourth;
	    else
	      next_surface_id = point->third;
	  }
	}
	
	++point;
      }
    
      if( next_point != end_point )
      {
	++prev_point;
	prev_point = polygon.insert( prev_point, *next_point );
	intersection_points.erase( next_point );

	current_surface_id = next_surface_id;
      }
      // The polygon is finished - add a copy of the first point to the end
      // of the polygon point list
      else
      {
	++prev_point;
	prev_point = polygon.insert( prev_point, *start_point );
	break;
      }
    }
  }
  
  // The polygon(s) have been created
  intersection_points = polygon;
}

//! Initialize the polygon
std::list<Quad<double,double,unsigned,unsigned> >::const_iterator
Cell::initializePolygon(
			std::list<Quad<double,double,unsigned,unsigned> > 
			&polygon,
			std::list<Quad<double,double,unsigned,unsigned> > 
			&intersection_points,
			const Teuchos::Array<Pair<Surface,Surface::Sense> > 
			&surfaces,
			unsigned &current_surface_id ) const
{
  // There must be at least three intersection points left to create a polygon
  testPrecondition( intersection_points.size() >= 3 );
  
  std::list<Quad<double,double,unsigned,unsigned> >::iterator
    point, start_point, next_point, prev_point, return_point, end_point;
  point = intersection_points.begin();
  start_point = point;
  end_point = intersection_points.end();
  
  // Find the starting point (upper-rightmost point)
  while( point != end_point )
  {
    if( point->first - start_point->first > 1e-12 )
      start_point = point;
    else if( fabs(point->first - start_point->first) < 1e-12 &&
	     point->second > start_point->second )
      start_point = point;
    
    ++point;
  }

  // Add the start point to the polygon
  polygon.push_back( *start_point );
  point = intersection_points.erase( start_point );

  // Find the two points closest to the starting point on the intersecting 
  // surfaces
  start_point = polygon.end();
  --start_point;
  point = intersection_points.begin();
  next_point = end_point;
  prev_point = end_point;
  while( point != end_point )
  {
    if( point->third == start_point->third ||
	point->fourth == start_point->third )
    {
      if( next_point != end_point )
      {
	Teuchos::Tuple<double,3> current_distance_vector = 
	  Teuchos::tuple( next_point->first - start_point->first,
			  next_point->second - start_point->second,
			  0.0 );

	Teuchos::Tuple<double,3> new_distance_vector = 
	  Teuchos::tuple( point->first - start_point->first,
			  point->second - start_point->second,
			  0.0 );

	if( LinearAlgebra::vectorMagnitude( new_distance_vector ) <
	    LinearAlgebra::vectorMagnitude( current_distance_vector ) )
	  next_point = point;
      }
      else
	next_point = point;
      
      ++point;
      continue;
    }
    if( point->third == start_point->fourth ||
	point->fourth == start_point->fourth )
    {
      if( prev_point != end_point )
      {
	Teuchos::Tuple<double,3> current_distance_vector = 
	  Teuchos::tuple( prev_point->first - start_point->first,
			  prev_point->second - start_point->second,
			  0.0 );

	Teuchos::Tuple<double,3> new_distance_vector = 
	  Teuchos::tuple( point->first - start_point->first,
			  point->second - start_point->second,
			  0.0 );

	if( LinearAlgebra::vectorMagnitude( new_distance_vector ) <
	    LinearAlgebra::vectorMagnitude( current_distance_vector ) )
	  prev_point = point;
      }
      else
	prev_point = point;
      
      ++point;
      continue;
    }

    ++point;
  }

  // Make sure that the next point is the point that would follow the start
  // point assuming a counterclockwise polygon (cell on inside of polygon)
  unsigned prev_surface_id, curr_surface_id, next_surface_id;
  if( next_point->second < prev_point->second )
  {
    std::swap( next_point, prev_point );
    prev_surface_id = start_point->third;
    curr_surface_id = start_point->fourth;
  }
  else
  {
    prev_surface_id = start_point->fourth;
    curr_surface_id = start_point->third;
  }
  
  // Find the previous surface
  Teuchos::Array<Pair<Surface,Surface::Sense> >::const_iterator
    surface, prev_surface, end_surface;
  surface = surfaces.begin();
  end_surface = surfaces.end();
  
  while( surface != end_surface )
  {
    if( surface->first.getId() == prev_surface_id )
    {
      prev_surface = surface;
      break;
    }
    
    ++surface;
  }

  // If the sense of the next point w.r.t. the previous surface equals the cell
  // w.r.t. the previous surface, the polygon is counterclockwise and the 
  // next point is indeed next. O.w. the polygon is clockwise and the previous 
  // point is next.
  Surface::Vector next_point_3d = 
    Teuchos::tuple( next_point->first, next_point->second, 0.0 );

  if( prev_surface->first.getSense( next_point_3d ) == 
      prev_surface->second )
  {
    return_point = polygon.insert( start_point, *prev_point );
    point = intersection_points.erase( prev_point );
    
    if( next_point->third == curr_surface_id )
      next_surface_id = next_point->fourth;
    else
      next_surface_id = next_point->third;
    
    ++start_point;
    start_point = polygon.insert( start_point, *next_point );
    point = intersection_points.erase( next_point );
  }
  else
  {
    return_point = polygon.insert( start_point, *next_point );
    point = intersection_points.erase( next_point );

    if( prev_point->third == prev_surface_id )
      next_surface_id = prev_point->fourth;
    else
      next_surface_id = prev_point->third;
    
    ++start_point;
    start_point = polygon.insert( start_point, *prev_point );
    point = intersection_points.erase( prev_point );
  }

  // The id of the other surface associated with the last point added to the 
  // polygon list must be returned
  current_surface_id = next_surface_id;

  return return_point;
} 

//! Calculate the area of a surface bounding the polyhedral cell
void Cell::calculatePolygonArea( 
	       const unsigned surface_id,
	       const std::list<Quad<double,double,unsigned,unsigned> > &polygon,
	       std::list<double> &polygon_areas )
{
  // The polygon must have at least 4 points (triangle with first point copied)
  testPrecondition( polygon.size() >= 4 );
  
  // The polygon areas list must be empty
  polygon_areas.clear();
  
  std::list<Quad<double,double,unsigned,unsigned> >::const_iterator
    point, next_point, start_point, end_point;
  
  start_point = polygon.begin();
  
  point = start_point;
  next_point = start_point;
  ++next_point;
  
  end_point = polygon.end();

  double area = 0.0;

  while( next_point != end_point )
  {
    double partial_area = (point->first + next_point->first)*
      (next_point->second - point->second);

    ++point;
    ++next_point;
    
    while( *point != *start_point )
    {
      partial_area += (point->first + next_point->first)*
      (next_point->second - point->second);

      ++point;
      ++next_point;
    }

    area += 0.5*partial_area;
    polygon_areas.push_back( 0.5*partial_area );
    
    if( next_point != end_point )
    {
      start_point = next_point;
      point = next_point;
      ++next_point;
    }
  }
  
  // Record this surfaces area relative to this cell
  d_surface_areas[surface_id] = fabs( area );
}

//! Assign the correct sign to the polygon areas
void Cell::assignPolygonAreaSign( std::list<double> &polygon_areas )
{
  // There must be at least one polygon area
  testPrecondition( polygon_areas.size() > 0 );
  
  std::list<double>::iterator area, max_area, end_area;
  max_area = polygon_areas.begin();
  area = polygon_areas.begin();
  ++area;
  end_area = polygon_areas.end();

  while( area != end_area )
  {
    if( fabs(*area) > fabs(*max_area) )
      max_area = area;

    ++area;
  }

  if( *max_area < 0.0 )
  {
    area = polygon_areas.begin();
    
    while( area != end_area )
    {
      *area *= -1.0;
      ++area;
    }
  }
} 

//! Calculate the volume contribution from a surface bounding this cell
void Cell::calculatePolygonVolumeContribution(
	       const Surface &reference_surface,
	       const std::list<Quad<double,double,unsigned,unsigned> > &polygon,
	       const std::list<double> &polygon_areas,
	       const Surface::Sense reference_surface_sense,
	       const Surface::Sense current_surface_sense )
{
  std::list<double>::const_iterator polygon_area = polygon_areas.begin();
  
  std::list<Quad<double,double,unsigned,unsigned> >::const_iterator
    point, next_point, start_point, end_point;
  
  start_point = polygon.begin();
  
  point = start_point;
  next_point = start_point;
  ++next_point;
  
  end_point = polygon.end();

  Surface::Vector ref_unit_normal = reference_surface.getLinearTermVector();
  double ref_normal_magnitude = 
    LinearAlgebra::vectorMagnitude( ref_unit_normal );
  LinearAlgebra::normalizeVector( ref_unit_normal );
  // Make sure the reference surface is pointing out of the cell and the 
  // current surface is pointing in to the cell
  ref_unit_normal *= (reference_surface_sense*-1)*current_surface_sense;
  double mu = ref_unit_normal[2];

  while( next_point != end_point )
  {
    Pair<double,double> centroid;
    centroid.first = (next_point->first*next_point->first +
		      next_point->first*point->first +
		      point->first*point->first)*
      (next_point->second - point->second);
    
    centroid.second = (next_point->first - point->first)*
      (next_point->second*next_point->second +
       next_point->second*point->second +
       point->second*point->second);

    ++point;
    ++next_point;
    
    while( (*point) != (*start_point) )
    {
      centroid.first += (next_point->first*next_point->first +
		      next_point->first*point->first +
		      point->first*point->first)*
	(next_point->second - point->second);

      centroid.second += (next_point->first - point->first)*
	(next_point->second*next_point->second +
	 next_point->second*point->second +
	 point->second*point->second);

      ++point;
      ++next_point;
    }

    centroid.first /= 6.0*(*polygon_area);
    centroid.second /= 6.0*(*polygon_area);

    double distance = fabs(ref_unit_normal[0]*centroid.first +
			   ref_unit_normal[1]*centroid.second +
			   reference_surface.getConstantTerm()/
			   ref_normal_magnitude);
    
    d_volume += distance*(*polygon_area)*mu;
    
    if( next_point != end_point )
    {
      start_point = next_point;
      point = next_point;
      ++next_point;
      
      ++polygon_area;
    }
  }
}

//! Calculate the rotationally symmetric cell volume and surface areas
bool Cell::calculateRotationallySymmetricCellVolumeAndSurfaceAreas()
{

}

//! Calculate the cell volume and surface areas using monte carlo integration
void Cell::calculateVolumeAndSurfaceAreasUsingMonteCarlo()
{

}

//! Calculate a bounding box for the cell
Cell Cell::calculateBoundingBox() const
{

}

//! Get the surface array
Teuchos::Array<Pair<Teuchos::RCP<Surface>,Surface::Sense> >
Cell::getSurfaceArray() const
{
  return d_surfaces;
}

} // end FACEMC namespace

#endif // end CELL_DEF_HPP

//---------------------------------------------------------------------------//
// end Cell_def.hpp
//---------------------------------------------------------------------------//

