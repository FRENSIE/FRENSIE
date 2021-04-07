//---------------------------------------------------------------------------//
//!
//! \file   Geometry_Cell.hpp
//! \author Alex Robinson
//! \brief  Cell class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_CELL_HPP
#define GEOMETRY_CELL_HPP

// Std Lib Includes
#include <string>
#include <map>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayView.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Geometry_BooleanCellFunctor.hpp"
#include "Geometry_Surface.hpp"
#include "Geometry_Vector.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_DesignByContract.hpp"

namespace Geometry{

//! The cell class
template<typename CellOrdinalType,
	 typename SurfaceOrdinalType,
	 typename ScalarType>
class Cell : public Utility::PrintableObject, public ThreeSpaceObject
{

private:

  //! Typedef for surface-sense pair
  typedef Utility::Pair<Teuchos::RCP<Surface<SurfaceOrdinalType,ScalarType> >,
			SurfaceSense> SurfaceSensePair;

  //! Typedef for surface-sense pairs container
  typedef Teuchos::Array<SurfaceSensePair> SurfaceSensePairContainer;

public:

  //@{
  //! Typedefs
  //! Typedef for cell ordinal type (only used for cell ids)
  typedef CellOrdinalType ordinalType;
  //! Typedef for surface ordinal type (only used for surface ids)
  typedef SurfaceOrdinalType surfaceOrdinalType;
  //! Typedef for scalar type
  typedef ScalarType scalarType;
  //! Typedef for surface-sense pairs array const iterator
  typedef typename SurfaceSensePairContainer::const_iterator
  SurfaceSensePairsIterator;
  //@}

private:

  //! Typedef for scalar traits
  typedef Teuchos::ScalarTraits<ScalarType> ST;
  //! Typedef for cell ordinal traits
  typedef Teuchos::OrdinalTraits<CellOrdinalType> CellOT;
  //! Typedef for surface ordinal traits
  typedef Teuchos::OrdinalTraits<SurfaceOrdinalType> SurfaceOT;
  //! Typedef for surface area map
  typedef std::map<SurfaceOrdinalType,ScalarType> SurfaceAreaMap;
  //! Typedef for Boolean array
  typedef BooleanCellFunctor::BooleanArray BooleanArray;

public:

  //! Constructor
  template<typename SurfaceMap>
  Cell( const CellOrdinalType id,
	std::string &cell_definition,
	const SurfaceMap &global_surface_map );

  //! Destructor
  virtual ~Cell()
  { /* ... */ }

  //@{
  //! Primary abstraction
  //! Return if the point is in the cell
  bool isIn( const ScalarType x,
	     const ScalarType y,
	     const ScalarType z ) const;

  //! Return if the point is in the cell
  bool isIn( const Vector<ScalarType> &point ) const;

  //! Return if the point is on the cell
  bool isOn( const ScalarType x,
	     const ScalarType y,
	     const ScalarType z ) const;

  //! Return if the point is on the cell
  bool isOn( const Vector<ScalarType> &point ) const;

  //! Evaluate the cell definition
  template<typename BoolArray>
  bool isCellPresent( const BoolArray &surface_tests ) const;

  //! Return if the cell is a polyhedron
  bool isPolyhedron() const;

  //! Return if the cell is analytically integrable
  bool isAnalyticallyIntegrable() const;

  //! Return the volume of the cell
  ScalarType getVolume() const;

  //! Manually set the volume of the cell
  void setVolume( const ScalarType volume );

  //! Return the cell id
  CellOrdinalType getId() const;

  //! Return the area of a surface bounding the cell
  ScalarType getSurfaceArea( const SurfaceOrdinalType surface_id ) const;

  //! Manually set the surface area of one of the cell surfaces
  void setSurfaceArea( const SurfaceOrdinalType surface_id,
		       const ScalarType surface_area );
  //@}

  //@{
  //! Container based abstraction
  //! Get a const iterator to beginning of the surface-sense pairs container
  inline SurfaceSensePairsIterator beginSurfaceSensePairs() const;

  //! Get a const iterator to end of the surface-sense pairs container
  inline SurfaceSensePairsIterator endSurfaceSensePairs() const;

  //! Get a const iterator to first occurrence of specific surface-sense pair
  SurfaceSensePairsIterator getSurfaceSensePair(
				   const SurfaceOrdinalType surface_id ) const;
  //@}

  //! Print method that defines the behavior of the std::stream << operator
  void print( std::ostream &os ) const;

protected:

  //! Strip the cell definition of set operation characters
  static void simplifyCellDefinitionString( std::string &cell_definition );

private:

  //! Assign surfaces to the cell
  template<typename SurfaceMap>
  void assignSurfaces( std::string &cell_definition,
		       const SurfaceMap &global_surface_map );

  // Cell Id
  CellOrdinalType d_id;

  // Cell definition (cache)
  std::string d_cell_definition_string;

  // Functor used to evaluate the cell definition
  BooleanCellFunctor d_cell_definition_evaluator;

  // Surfaces and Senses that define the cell
  SurfaceSensePairContainer d_surface_sense_pairs;

  // Surface information particular to this cell
  SurfaceAreaMap d_surface_id_area_map;

  // Cell volume
  ScalarType d_volume;
};

} // end Geometry namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "Geometry_Cell_def.hpp"

//---------------------------------------------------------------------------//

#endif // end GEOMETRY_CELL_HPP

//---------------------------------------------------------------------------//
// end Geometry_Cell.hpp
//---------------------------------------------------------------------------//
