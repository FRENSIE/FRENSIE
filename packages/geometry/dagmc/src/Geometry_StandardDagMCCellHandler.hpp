//---------------------------------------------------------------------------//
//!
//! \file   Geometry_StandardDagMCCellHandler.hpp
//! \author Alex Robinson
//! \brief  The standard DagMC cell handler class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_STANDARD_DAGMC_CELL_HANDLER_HPP
#define GEOMETRY_STANDARD_DAGMC_CELL_HANDLER_HPP

// FRENSIE Includes
#include "Geometry_DagMCCellHandler.hpp"

namespace Geometry{

/*! The StandardDagMCCellHandler class
 * \details This class is optimized for minimal storage. The conversion
 * from cell handle to cell id is fast but the conversion from cell id
 * to cell handle is very slow. Avoid the later conversion if performance is
 * a concern.
 */
class StandardDagMCCellHandler : public DagMCCellHandler
{

public:

  //! Constructor
  StandardDagMCCellHandler( const moab::DagMC* dagmc_instance );
  

  //! Destructor
  ~StandardDagMCCellHandler()
  { /* ... */ }

  //! Check if the cell exists
  bool doesCellExist( const ModuleTraits::InternalCellHandle cell_id ) const;

  //! Get the cell id from a cell handle
  ModuleTraits::InternalCellHandle getCellId( 
                                  const moab::EntityHandle cell_handle ) const;

  //! Get the cell handle from a cell id
  moab::EntityHandle getCellHandle(
                        const ModuleTraits::InternalCellHandle cell_id ) const;

private:

  // The dagmc instance
  const moab::DagMC* d_dagmc_instance;
};

} // end Geometry namespace

#endif // end GEOMETRY_STANDARD_DAGMC_CELL_HANDLER_HPP

//---------------------------------------------------------------------------//
// end Geometry_StandardDagMCCellHandler.hpp
//---------------------------------------------------------------------------//
