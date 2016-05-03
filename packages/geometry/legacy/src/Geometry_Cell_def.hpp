//---------------------------------------------------------------------------//
//!
//! \file   Geometry_Cell_def.hpp
//! \author Alex Robinson
//! \brief  Cell class definition
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_CELL_DEF_HPP
#define GEOMETRY_CELL_DEF_HPP

// Std Lib Includes
#include <string>
#include <sstream>
#include <map>
#include <iterator>
#include <set>

// Boost Includes
#include <boost/unordered_map.hpp>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayView.hpp>
#include <Teuchos_Tuple.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Geometry_Surface.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_ContractException.hpp"

namespace Geometry{

//! Constructor
template<typename CellOrdinalType,
	 typename SurfaceOrdinalType,
	 typename ScalarType>
template<typename SurfaceMap>
Cell<CellOrdinalType,SurfaceOrdinalType,ScalarType>::Cell( 
					 const CellOrdinalType id,
					 std::string &cell_definition,
					 const SurfaceMap &global_surface_map )
  : Utility::PrintableObject( "ThreeSpaceCell" ),
    ThreeSpaceObject( THREE_SPACE_CELL ),
    d_id( id ), 
    d_cell_definition_string( cell_definition ),
    d_cell_definition_evaluator( cell_definition ), 
    d_volume( 0.0 )
{
  // A valid SurfaceMap type must be used
  testStaticPrecondition((boost::is_same<typename SurfaceMap::key_type,typename SurfaceMap::mapped_type::element_type::ordinalType>::value));
  // The map properties must match the cell properties
  testStaticPrecondition((boost::is_same<typename SurfaceMap::key_type,SurfaceOrdinalType>::value));
  testStaticPrecondition((boost::is_same<typename SurfaceMap::mapped_type::element_type::scalarType,ScalarType>::value));
  
  // Remove all characters from the cell definition string except for the ids
  Cell<CellOrdinalType,
       SurfaceOrdinalType,
       ScalarType>::simplifyCellDefinitionString( cell_definition );
  
  // Query the surface map and assign the surfaces that define this cell
  assignSurfaces( cell_definition, global_surface_map );

  // Initialize the surface id-area map
  SurfaceSensePairsIterator surface_sense_pair, end_surface_sense_pair;
  surface_sense_pair = d_surface_sense_pairs.begin();
  end_surface_sense_pair = d_surface_sense_pairs.end();

  while( surface_sense_pair != end_surface_sense_pair )
  {
    d_surface_id_area_map[surface_sense_pair->first->getId()] = ST::zero();
    
    ++surface_sense_pair;
  }
}

// Return if the point is in the cell
template<typename CellOrdinalType, 
	 typename SurfaceOrdinalType, 
	 typename ScalarType>
bool Cell<CellOrdinalType, SurfaceOrdinalType, ScalarType>::isIn( 
				        const Vector<ScalarType> &point ) const
{
  return isIn( point[0], point[1], point[2] );
}

// Return if the point is in the cell
template<typename CellOrdinalType, 
	 typename SurfaceOrdinalType, 
	 typename ScalarType>
bool Cell<CellOrdinalType,SurfaceOrdinalType,ScalarType>::isIn( 
						     const ScalarType x,
						     const ScalarType y,
						     const ScalarType z ) const
{
  SurfaceSensePairsIterator surface_sense_pair, end_surface_sense_pair;
  surface_sense_pair = d_surface_sense_pairs.begin();
  end_surface_sense_pair = d_surface_sense_pairs.end();

  // Sense of the point with respect to the surface of interest
  SurfaceSense sense;

  // If the sense matches the cell surface sense, true is added to this array
  // else false is added (The surface ordering is the same as in the 
  // d_surfaces_sense_pair array)
  BooleanArray sense_tests( d_surface_sense_pairs.size() );
  typename BooleanArray::iterator test = sense_tests.begin();

  while( surface_sense_pair != end_surface_sense_pair )
  {
    sense = surface_sense_pair->first->getSenseOfPoint( x, y, z );
    
    if( sense == surface_sense_pair->second )
      *test = true;
    else
      *test = false;
    
    ++surface_sense_pair;
    ++test;
  }

  return d_cell_definition_evaluator( sense_tests );
}

// Return if the point is on the cell
template<typename CellOrdinalType, 
	 typename SurfaceOrdinalType, 
	 typename ScalarType>
bool Cell<CellOrdinalType, SurfaceOrdinalType, ScalarType>::isOn( 
					const Vector<ScalarType> &point ) const
{
  return isOn( point[0], point[1], point[2] );
}

//! Return if the point is on the cell
template<typename CellOrdinalType, 
	 typename SurfaceOrdinalType,
	 typename ScalarType>
bool Cell<CellOrdinalType, SurfaceOrdinalType, ScalarType>::isOn( 
						     const ScalarType x,
						     const ScalarType y,
						     const ScalarType z ) const
{
  SurfaceSensePairsIterator surface_sense_pair, end_surface_sense_pair;
  surface_sense_pair = d_surface_sense_pairs.begin();
  end_surface_sense_pair = d_surface_sense_pairs.end();

  // Sense of the point with respect to the surface of interest
  SurfaceSense sense;

  // If the sense matches the cell surface sense, true is added to this array
  // else false is added (The surface ordering is the same as in the d_surfaces
  // array)
  BooleanArray sense_tests( d_surface_sense_pairs.size() );
  typename BooleanArray::iterator test = sense_tests.begin();

  bool point_on_a_surface = false;

  while( surface_sense_pair != end_surface_sense_pair )
  {
    sense = surface_sense_pair->first->getSenseOfPoint( x, y, z );
    
    if( sense == surface_sense_pair->second )
      *test = true;
    else if( sense == ON_SURFACE )
    {
      *test = true;
      point_on_a_surface = true;
    }
    else
      *test = false;
    
    ++surface_sense_pair;
    ++test;
  }

  return d_cell_definition_evaluator( sense_tests ) && point_on_a_surface;
}

// Return if the cell is a polyhedron
template<typename CellOrdinalType, 
	 typename SurfaceOrdinalType, 
	 typename ScalarType>
bool Cell<CellOrdinalType,SurfaceOrdinalType,ScalarType>::isPolyhedron() const
{
  SurfaceSensePairsIterator surface_sense_pair, end_surface_sense_pair;
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
    
    ++surface_sense_pair;
  }
  
  return all_planar_surfaces;
}

template<typename CellOrdinalType, 
	 typename SurfaceOrdinalType, 
	 typename ScalarType>
bool Cell<CellOrdinalType,SurfaceOrdinalType,ScalarType>::isAnalyticallyIntegrable() const
{
  bool analytically_integrable_cell = true;

  SurfaceSensePairsIterator first_surface = 
    d_surface_sense_pairs.begin();
  SurfaceSensePairsIterator second_surface = 
    d_surface_sense_pairs.begin();
  SurfaceSensePairsIterator end_surface = 
    d_surface_sense_pairs.end();

  // Processed surfaces
  std::set<SurfaceOrdinalType> processed_surfaces;

  while( first_surface != end_surface )
  {
    if( processed_surfaces.find( first_surface->first->getId() ) == 
	processed_surfaces.end() )
    {
      processed_surfaces.insert( first_surface->first->getId() );
    }
    else // this surface has already been processed
    {
      ++first_surface;
      continue;
    }

    second_surface = d_surface_sense_pairs.begin();

    // See if the same surface appears again in the cell def. with diff. sense
    while( second_surface != end_surface )
    {
      if( second_surface->first->getId() == first_surface->first->getId() )
      {
	if( second_surface->second != first_surface->second )
	{
	  analytically_integrable_cell = false;
	  break;
	}
      }
      
      ++second_surface;
    }

    // If a repeated surface with diff. sense was found, exit the search.
    if( analytically_integrable_cell == false )
      break;
    else
      ++first_surface;	
  }

  return analytically_integrable_cell;
}

// Return the volume of the cell
template<typename CellOrdinalType, 
	 typename SurfaceOrdinalType, 
	 typename ScalarType>
ScalarType Cell<CellOrdinalType,
		SurfaceOrdinalType,
		ScalarType>::getVolume() const
{  
  // Make sure that the cell volume returned is valid
  testPostcondition( d_volume > ST::zero() );
  testPostcondition( !ST::isnaninf( d_volume ) );
  
  return d_volume;
}

// Manually set the volume of the cell
template<typename CellOrdinalType, 
	 typename SurfaceOrdinalType, 
	 typename ScalarType>
void Cell<CellOrdinalType, SurfaceOrdinalType, ScalarType>::setVolume( 
						      const ScalarType volume )
{
  // Make sure that the cell volume assigned is valid
  testPrecondition( volume > ST::zero() );
  testPrecondition( !ST::isnaninf( volume ) );
  
  d_volume = volume;
}

// Return the cell id
template<typename CellOrdinalType,
	 typename SurfaceOrdinalType,
	 typename ScalarType>
CellOrdinalType 
Cell<CellOrdinalType,SurfaceOrdinalType,ScalarType>::getId() const
{
  return d_id;
}

// Return the area of a surface bounding the cell
template<typename CellOrdinalType, 
	 typename SurfaceOrdinalType, 
	 typename ScalarType>
ScalarType Cell<CellOrdinalType,SurfaceOrdinalType,ScalarType>::getSurfaceArea(
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

  return area;
}
  
// Set the area of a surface bounding the cell
template<typename CellOrdinalType, 
	 typename SurfaceOrdinalType, 
	 typename ScalarType>
void Cell<CellOrdinalType, SurfaceOrdinalType, ScalarType>::setSurfaceArea( 
					   const SurfaceOrdinalType surface_id,
					   const ScalarType surface_area ) 
{
  // The requested surface must be present in the cell (and have area data)
  testPrecondition( d_surface_id_area_map.count( surface_id ) > 0 );
  // Make sure that the surface area is valid
  testPrecondition( surface_area > ST::zero() );
  testPrecondition( !ST::isnaninf( surface_area ) );

  typename SurfaceAreaMap::iterator surface_id_area_pair;
  surface_id_area_pair = d_surface_id_area_map.find( surface_id );

  surface_id_area_pair->second = surface_area;
}

// Get a const iterator to the beginning of the surface sense pairs array
template<typename CellOrdinalType, 
	 typename SurfaceOrdinalType, 
	 typename ScalarType>
inline typename Cell<CellOrdinalType,
		     SurfaceOrdinalType,
		     ScalarType>::SurfaceSensePairsIterator
Cell<CellOrdinalType,
     SurfaceOrdinalType,
     ScalarType>::beginSurfaceSensePairs() const
{  
  return d_surface_sense_pairs.begin();
}

// Get a const iterator to the end of the surface sense pairs array
template<typename CellOrdinalType, 
	 typename SurfaceOrdinalType, 
	 typename ScalarType>
inline typename Cell<CellOrdinalType,
		     SurfaceOrdinalType,
		     ScalarType>::SurfaceSensePairsIterator
Cell<CellOrdinalType,
     SurfaceOrdinalType,
     ScalarType>::endSurfaceSensePairs() const
{  
  return d_surface_sense_pairs.end();
}


// Get a const iterator to first occurance of specific surface-sense pair
template<typename CellOrdinalType, 
	 typename SurfaceOrdinalType, 
	 typename ScalarType>
typename Cell<CellOrdinalType,
	      SurfaceOrdinalType,
	      ScalarType>::SurfaceSensePairsIterator
Cell<CellOrdinalType,
     SurfaceOrdinalType,
     ScalarType>::getSurfaceSensePair( 
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
    
    ++surface_sense_pair;
  }

  // Make sure that the desired surface was found
  testPostcondition( surface_sense_pair != end_surface_sense_pair );

  return surface_sense_pair;
}

// Print method that defines the behavior of the std::stream << operator
template<typename CellOrdinalType, 
	 typename SurfaceOrdinalType, 
	 typename ScalarType>
void Cell<CellOrdinalType, SurfaceOrdinalType, ScalarType>::print( 
						       std::ostream &os ) const
{
  os << "Id: " << d_id << std::endl;
  os << "Definition: " << d_cell_definition_string << std::endl;
  os << "Surface(s): " << std::endl;
  
  SurfaceSensePairsIterator pair, end_pair;
  pair = beginSurfaceSensePairs();
  end_pair = endSurfaceSensePairs();
  
  while( pair != end_pair )
  {    
    os << *(pair->first);
    os << "Sense: " << (pair->second == POS_SURFACE_SENSE ? "+" : "-")
       << std::endl;
    
    ++pair;
  }
}

// Evaluate the cell definition
template<typename CellOrdinalType, 
	 typename SurfaceOrdinalType, 
	 typename ScalarType>
template<typename BoolArray>
bool Cell<CellOrdinalType, SurfaceOrdinalType, ScalarType>::isCellPresent( 
				         const BoolArray &surface_tests ) const
{
   // The array must contain boolean types
  testStaticPrecondition((boost::is_same<typename Utility::ArrayTraits<BoolArray>::value_type,bool>::value || boost::is_same<typename Utility::ArrayTraits<BoolArray>::value_type,const bool>::value));
  
  return d_cell_definition_evaluator( surface_tests );
}

// Strip the cell definition string of set operation characters
template<typename CellOrdinalType, 
	 typename SurfaceOrdinalType, 
	 typename ScalarType>
void Cell<CellOrdinalType,
	  SurfaceOrdinalType,
	  ScalarType>::simplifyCellDefinitionString( 
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
	 typename ScalarType>
template<typename SurfaceMap>
  void Cell<CellOrdinalType, SurfaceOrdinalType, ScalarType>::assignSurfaces( 
					 std::string &cell_definition,
				         const SurfaceMap &global_surface_map )
{
  // A valid SurfaceMap type must be used
  testStaticPrecondition((boost::is_same<typename SurfaceMap::key_type,typename SurfaceMap::mapped_type::element_type::ordinalType>::value));
  // The map properties must match the cell properties
  testStaticPrecondition((boost::is_same<typename SurfaceMap::key_type,SurfaceOrdinalType>::value));
  testStaticPrecondition((boost::is_same<typename SurfaceMap::mapped_type::element_type::scalarType,ScalarType>::value));
  // The cell_definition must be simplified
  testPrecondition( cell_definition.find_first_of( "nu()", 0 ) == 
		    std::string::npos );
  // A surface cannot have an id of 0
  testPrecondition( cell_definition.find( " 0 " ) == std::string::npos );
  testPrecondition( cell_definition.find( " -0 " ) == std::string::npos );
  
  // Test that all surfaces requested by cell def. exist
  remember( bool all_surfaces_found = true );

  typename SurfaceMap::const_iterator global_surface_sense_pair,
    end_global_surface_sense_pair = global_surface_map.end();
  
  SurfaceSensePair local_surface_sense_pair;

  std::stringstream simplified_cell_definition( cell_definition );
  SurfaceOrdinalType surface_id_with_sense, surface_id;
  SurfaceSense surface_sense;

  while( simplified_cell_definition )
  {
    simplified_cell_definition >> surface_id_with_sense;
    
    if( surface_id_with_sense < SurfaceOT::zero() )
    {
      surface_sense = NEG_SURFACE_SENSE;
      surface_id = surface_id_with_sense*(-SurfaceOT::one());
    }
    else
    {
      surface_sense = POS_SURFACE_SENSE;
      surface_id = surface_id_with_sense;
    }

    // Pull the surface from the global map
    global_surface_sense_pair = global_surface_map.find( surface_id );

    if( global_surface_sense_pair != end_global_surface_sense_pair )
    {
      // Store this surface
      local_surface_sense_pair.first = global_surface_sense_pair->second;
      local_surface_sense_pair.second = surface_sense;
      d_surface_sense_pairs.push_back( local_surface_sense_pair );
    }
    else
    {
      // If the surface was not found exit the program
      //FRENSIE_ASSERT_ALWAYS_MSG( surface_exists, "Fatal Error: Surface " << surface_id << " requested by Cell " << d_id << " does not exist." );
      remember( all_surfaces_found = false );
    }
    
    // Remove the next whitespace from the cell_definition
    simplified_cell_definition.ignore();
  }
  
  // Make sure that all surfaces were found
  testPostcondition( all_surfaces_found );
  // Make sure that at least one surface was assigned to the cell
  testPostcondition( d_surface_sense_pairs.size() > 0 );
}

} // end Geometry namespace

#endif // end GEOMETRY_CELL_DEF_HPP

//---------------------------------------------------------------------------//
// end Geometry_Cell_def.hpp
//---------------------------------------------------------------------------//

