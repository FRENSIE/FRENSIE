//---------------------------------------------------------------------------//
//!
//! \file   Cell.hpp
//! \author Alex Robinson
//! \brief  Cell class declaration
//!
//---------------------------------------------------------------------------//

#ifndef CELL_HPP
#define CELL_HPP

// Std Lib Includes
#include <string>
#include <map>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayView.hpp>
#include <Teuchos_RCP.hpp>

// FACEMC Includes
#include "BooleanCellFunctor.hpp"
#include "Surface.hpp"
#include "Tuple.hpp"
#include "ContractException.hpp"

namespace FACEMC{

template<typename CellOrdinalType, 
	 typename SurfaceOrdinalType, 
	 typename ScalarType,
	 typename SurfaceMap = 
	 std::map<SurfaceOrdinalType,
		  Teuchos::RCP<Surface<SurfaceOrdinalType,ScalarType> > > >
class Cell
{

public:

  //@{
  //! Typedefs
  //! Typedef for cell ordinal type (only used for cell ids)
  typedef CellOrdinalType ordinalType;
  //! Typedef for surface ordinal type (only used for surface ids)
  typedef SurfaceOrdinalType surfaceOrdinalType;
  //! Typedef for scalar type
  typedef ScalarType scalarType;
  //! Typedef for surface type
  typedef Surface<SurfaceOrdinalType,ScalarType> Surface;
  //! Typedef for surface map type
  typedef SurfaceMap SurfaceMap;
  //! Typedef for surface-sense pairs array const iterator
  typedef Teuchos::Array<Pair<Teuchos::RCP<Surface>,SurfaceSense> >::const_iterator SurfaceSensePairsIterator;
  //@}

private:

  //! Typedef for scalar traits
  typedef Teuchos::ScalarTraits<ScalarType> ST;
  //! Typedef for cell ordinal traits
  typedef Teuchos::OrdinalTraits<CellOrdinalType> CellOT;
  //! Typedef for surface ordinal traits
  typedef Teuchos::OrdinalTraits<SurfaceOrdinalType> SurfaceOT;
  //! Typedef for three space traits and policy struct
  typedef ThreeSpaceTraitsAndPolicy<ScalarType> ThreeSpace;
  //! Typedef for vector
  typedef typename ThreeSpace::Vector Vector;
  //! Typedef for surface area map
  typedef std::map<SurfaceOrdinalType,ScalarType> SurfaceAreaMap;
  //! Typedef for Boolean array
  typedef BooleanCellFunctor::BooleanArray BooleanArray;

public:
  
  //! Constructor
  Cell( const CellOrdinalType id,
	const std::string &cell_definition,
	const SurfaceMap &global_surface_map );

  //! Destructor
  ~Cell()
  { /* ... */ }

  //! Return if the point is in the cell
  bool isIn( const ScalarType x,
	     const ScalarType y,
	     const ScalarType z ) const;

  //! Return if the point is in the cell
  bool isIn( const Vector &point ) const;

  //! Return if the point is on the cell
  bool IsOn( const ScalarType x,
	     const ScalarType y,
	     const ScalarType z ) const;

  //! Return if the point is on the cell
  bool isOn( const Vector &point ) const;

  //! Return if the cell is a polyhedron
  bool isPolyhedron() const;

  //! Return the volume of the cell
  ScalarType getVolume() const;

  //! Manually set the volume of the cell
  void setVolume( const ScalarType volume );

  //! Return the area of a surface bounding the cell
  ScalarType getSurfaceArea( const SurfaceOrdinalType surface_id ) const;

  //! Manually set the surface area of one of the cell surfaces
  void setSurfaceArea( const SurfaceOrdinalType surface_id,
		       const ScalarType surface_area );

  //! Get a const iterator to the beginning of the surface sense pairs array
  SurfaceSensePairsIterator beginSurfaceSensePairs() const;

  //! Get a const iterator to the end of the surface sense pairs array
  SurfaceSensePairsIterator endSurfaceSensePairs() const;

  //! Evaluate the cell definition
  bool isCellPresent( BooleanArray &surface_tests );

  //! Strip the cell definition of set operation characters
  static void simplifyCellDefinitionString( std::string &cell_definition );

protected:

  //! Assign surfaces to the cell
  void assignSurfaces( std::string &cell_definition, 
		       SurfaceMap &global_surface_map );

private:

  // Cell Id
  CellOrdinalType d_id;

  // Functor used to evaluate the cell definition
  BooleanCellFunctor d_cell_definition_evaluator;

  // Surfaces and Senses that define the cell
  Teuchos::Array<Pair<Teuchos::RCP<Surface>,SurfaceSense> > 
  d_surface_sense_pairs;
  
  // Surface information particular to this cell
  SurfaceAreaMap d_surface_id_area_map;

  // Cell volume
  ScalarType d_volume;
};

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "Cell_def.hpp"

//---------------------------------------------------------------------------//

#endif // end CELL_HPP

//---------------------------------------------------------------------------//
// end Cell.hpp
//---------------------------------------------------------------------------//
