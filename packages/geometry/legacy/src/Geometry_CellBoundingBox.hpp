//---------------------------------------------------------------------------//
//!
//! \file   Geometry_CellBoundingBox.hpp
//! \author Alex Robinson
//! \brief  Cell bounding box class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_CELL_BOUNDING_BOX_HPP
#define GEOMETRY_CELL_BOUNDING_BOX_HPP

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Geometry_Cell.hpp"

namespace Geometry{

//! A class that defines a bounding box around a cell
template<typename Cell>
class CellBoundingBox
{

private:

  //! Typedef for cell ordinal type
  typedef typename Cell::ordinalType cellOrdinalType;
  //! Typedef for surface ordinal type
  typedef typename Cell::surfaceOrdinalType surfaceOrdinalType;
  //! Typedef for scalar type
  typedef typename Cell::scalarType scalarType;
  //! Typedef for scalar traits
  typedef Teuchos::ScalarTraits<scalarType> ST;
  //! Typedef for cell ordinal traits
  typedef Teuchos::OrdinalTraits<cellOrdinalType> CellOT;
  //! Typedef for surface ordinal traits
  typedef Teuchos::OrdinalTraits<surfaceOrdinalType> SurfaceOT;

public:

  //! Constructor
  CellBoundingBox( const Teuchos::RCP<Cell> &cell,
		   const scalarType x_min,
		   const scalarType x_max,
		   const scalarType y_min,
		   const scalarType y_max,
		   const scalarType z_min,
		   const scalarType z_max,
		   const scalarType convergence_ratio = 1e-6 );

  //! Destructor
  ~CellBoundingBox()
  { /* ... */ }

  //! Calculate and set the cell volume
  void calculateCellVolume( int max_samples = 100000000 );

  //! Calculate and set the cell surface areas
  void calculateCellSurfaceAreas( int max_samples = 100000000 );

  //! Calculate and set the cell volume and surface areas
  void calculateCellVolumeAndSurfaceAreas( int max_samples = 100000000 );

private:

  // Pointer to the desired cell
  Teuchos::RCP<Cell> d_cell;

  // Lower x bound
  scalarType d_x_min;

  // Upper x bound
  scalarType d_x_max;

  // Lower y bound
  scalarType d_y_min;

  // Upper y bound
  scalarType d_y_max;

  // Lower z bound
  scalarType d_z_min;

  // Upper z bound
  scalarType d_z_max;

  // The convergence tolerance
  scalarType d_convergence_ratio;

};

} // end Geometry namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "Geometry_CellBoundingBox_def.hpp"

//---------------------------------------------------------------------------//

#endif // end GEOMETRY_CELL_BOUNDING_BOX_HPP

//---------------------------------------------------------------------------//
// end Geometry_CellBoundingBox.hpp
//---------------------------------------------------------------------------//
