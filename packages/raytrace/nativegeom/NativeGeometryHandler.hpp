//---------------------------------------------------------------------------//
//!
//! \file   NativeGeometryHandler.hpp
//! \author Alex Robinson
//! \brief  Native geometry handler class declaration
//!
//---------------------------------------------------------------------------//

#ifndef NATIVE_GEOMETRY_HANDLER_HPP
#define NATIVE_GEOMETRY_HANDLER_HPP

// Std Lib Includes
#include <set>

// Boost Includes
#include <boost/unordered_map.hpp>

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_StandardParameterEntryValidators.hpp>

// FACEMC Includes
#include "PointLocation.hpp"
#include "Surface.hpp"
#include "Cell.hpp"

namespace FACEMC{

//! Native geometry handler class
template<typename Cell>
class NativeGeometryHandler
{

public:

  //@{
  //! Typedefs
  //! Typedef for cell ordinal type (only used for cell ids)
  typedef typename CellMap::mapped_type cellOrdinalType;
  //! Typedef for surface ordinal type (only used for surface ids)
  typedef Cell::surfaceOrdinalType surfaceOrdinalType;
  //! Typedef for scalar type
  typedef Cell::scalarType scalarType;
  //! Typedef for NativeGeometryHandler pointer
  typedef Teuchos::RCP<NativeGeometryHandler<Cell> > Pointer;
  //@}

private:

  // Typedef for scalar traits
  typedef Teuchos::ScalarTraits<scalarType> ST;
  // Typedef for cell ordinal traits
  typedef Teuchos::OrdinalTraits<cellOrdinalType> CellOT;
  // Typedef for surface ordinal traits
  typedef Teuchos::OrdinalTraits<surfaceOrdinalType> SurfaceOT;
  
public:

  //! Get an instance of the handler (singleton pattern)
  static NativeGeometryHandlerPtr getInstance();

  //! Destructor
  ~NativeGeometryHandler()
  { /* ... */ }

  //! Initialize the geometry
  void initializeGeometry( const Teuchos::ParameterList& problem_definition );

  //! Fire a ray at a cell
  void fireRay( const cellOrdinalType cell_id,
		const scalarType ray_start_position[3],
		const scalarType ray_direction[3],
		surfaceOrdinalType& surface_hit,
		scalarType& distance_to_hit_surface );

  //! Get the cell id that contains the given point
  cellOrdinalType getCellContainingPoint( const scalarType point[3] );

  //! Test if a cell contains a given point
  PointLocation getPointLocation( const cellOrdinalType cell_id,
				  const scalarType point[3] ) const;
  
  //! Get the volume of a cell
  scalarType getCellVolume( const cellOrdinalType cell_id ) const;

  //! Get the surface area of a surface bounding a cell
  scalarType getCellSurfaceArea( const cellOrdinalType cell_id,
				 const surfaceOrdinalType surface_id ) const;

  //! Get the cell on the other side of a surface
  cellOrdinalType getNextCell( const surfaceOrdinalType surface_id,
			       const cellOrdinalType current_cell_id,
			       const scalarType point[3] );

private:

  // Default constructor
  NativeGeometryHandler();

  // Constructor
  NativeGeometryHandler( const Teuchos::ParameterList& problem_definition );

  // Copy constructor
  NativeGeometryHandler( const NativeGeometryHandler& existing_handler );

  // Assignment operator
  NativeGeometryHandler& operator=( 
			       const NativeGeometryHandler& existing_handler );

  // Create the surface map from the parameter list
  void createSurfaceMap( const Teuchos::ParameterList& problem_definition );

  // Create the cell map from the parameter list
  void createCellMap( const Teuchos::ParameterList& problem_definition );

  // Sole instance of handler
  static Teuchos::RCP<NativeGeometryHandler> instance;
  
  // Surface id map
  boost::unordered_map<surfaceOrdinalType,scalarType> d_surface_map;

  // Cell id map
  boost::unordered_map<cellOrdinalType,scalarType> d_cell_map;

  // Cells that have been previously found to contain points. This list is 
  // appended every time the getCellContainingPoint function is called and a 
  // new cell is found.
  std::set<cellOrdinalType> d_cells_containing_test_points;

};

} // end FACEMC namespace

#endif // end NATIVE_GEOMETRY_HANDLER_HPP

//---------------------------------------------------------------------------//
// end NativeGeometryHandler.hpp
//---------------------------------------------------------------------------//
