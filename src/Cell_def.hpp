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
				       const SurfaceMap &global_surface_map )
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

} // end FACEMC namespace

#endif // end CELL_DEF_HPP

//---------------------------------------------------------------------------//
// end Cell_def.hpp
//---------------------------------------------------------------------------//

