//---------------------------------------------------------------------------//
//!
//! \file   Geometry_DagMCCellHandler.hpp
//! \author Alex Robinson
//! \brief  The DagMC cell handler class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_DAGMC_CELL_HANDLER_HPP
#define GEOMETRY_DAGMC_CELL_HANDLER_HPP

// Moab Includes
#include <DagMC.hpp>

// FRENSIE Includes
#include "Geometry_DagMCEntityHandler.hpp"
#include "Geometry_Navigator.hpp"

namespace Geometry{

//! The DagMCCellHandler class
class DagMCCellHandler : public DagMCEntityHandler
{

public:

  //! The internal cell handle type
  typedef Navigator::EntityId EntityId;

  //! Constructor
  DagMCCellHandler( const moab::DagMC* dagmc_instance );

  //! Destructor
  virtual ~DagMCCellHandler()
  { /* ... */ }

  //! Get the number of cells
  size_t getNumberOfCells() const;

  //! Check if the cell exists
  virtual bool doesCellExist( const EntityId cell_id ) const = 0;

  //! Check if the cell handle exists
  virtual bool doesCellHandleExist(
                                  const moab::EntityHandle cell_handle ) const;

  //! Get the cell id from a cell handle
  virtual EntityId getCellId(
                              const moab::EntityHandle cell_handle ) const = 0;

  //! Get the cell handle from a cell id
  virtual moab::EntityHandle getCellHandle(
                                  const EntityId cell_id ) const = 0;
};

} // end Geometry namespace

#endif // end GEOMETRY_DAGMC_CELL_HANDLER_HPP

//---------------------------------------------------------------------------//
// end Geometry_DagMCCellHandler.hpp
//---------------------------------------------------------------------------//
