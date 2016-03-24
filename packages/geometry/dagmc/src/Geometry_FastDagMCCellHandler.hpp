//---------------------------------------------------------------------------//
//!
//! \file   Geometry_FastDagMCCellHandler.hpp
//! \author Alex Robinson
//! \brief  The fast DagMC cell handler class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_FAST_DAGMC_CELL_HANDLER_HPP
#define GEOMETRY_FAST_DAGMC_CELL_HANDLER_HPP

// Std Lib Includes
#include <unordered_set>

// Boost Includes
#include <boost/bimap.hpp>
#include <boost/bimap/unordered_set_of.hpp>

// FRENSIE Includes
#include "Geometry_DagMCCellHandler.hpp"

namespace Geometry{

/*! The FastDagMCCellHandler class
 * \details This class is optimized for performance. The conversion from
 * cell handle to cell id or cell id to cell handle is fast. The handles
 * are stored twice to allow for the fast lookup times (extra storage 
 * overhead).
 */
class FastDagMCCellHandler : public DagMCCellHandler
{

public:

  //! Constructor
  FastDagMCCellHandler( const moab::DagMC* dagmc_instance );

  //! Destructor
  ~FastDagMCCellHandler()
  { /* ... */ }

  //! Check if the cell exists
  bool doesCellExist( const ModuleTraits::InternalCellHandle cell_id ) const;

  // Check if the cell handle exists
  bool doesCellHandleExist( const moab::EntityHandle cell_handle ) const;

  //! Get the cell id from a cell handle
  ModuleTraits::InternalCellHandle getCellId( 
                                  const moab::EntityHandle cell_handle ) const;

  //! Get the cell handle from a cell id
  moab::EntityHandle getCellHandle(
                        const ModuleTraits::InternalCellHandle cell_id ) const;

private:

  // The cell id to cell handle map
  typedef boost::bimap<boost::bimaps::unordered_set_of<ModuleTraits::InternalCellHandle>,boost::bimaps::unordered_set_of<moab::EntityHandle> > CellIdHandleMap;

  CellIdHandleMap d_cell_id_handle_map;
};

} // end Geometry namespace

#endif // end GEOMETRY_FAST_DAGMC_CELL_HANDLER_HPP

//---------------------------------------------------------------------------//
// end Geometry_FastDagMCCellHandler.hpp
//---------------------------------------------------------------------------//
