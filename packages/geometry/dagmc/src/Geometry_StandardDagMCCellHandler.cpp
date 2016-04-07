//---------------------------------------------------------------------------//
//!
//! \file   Geometry_StandardDagMCCellHandler.cpp
//! \author Alex Robinson
//! \brief  The standard DagMC cell handler class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Geometry_StandardDagMCCellHandler.hpp"
#include "Utility_ContractException.hpp"

namespace Geometry{

// Constructor
StandardDagMCCellHandler::StandardDagMCCellHandler( 
                                            const moab::DagMC* dagmc_instance )
  : DagMCCellHandler( dagmc_instance ),
    d_dagmc_instance( dagmc_instance )
{
  // Make sure the DagMC instance is valid
  testPrecondition( dagmc_instance != NULL );
}

// Get the cell id from a cell handle
ModuleTraits::InternalCellHandle StandardDagMCCellHandler::getCellId( 
                                  const moab::EntityHandle cell_handle ) const
{
  // Make sure the cell handle exists
  testPrecondition( this->doesCellHandleExist( cell_handle ) );
  
  return const_cast<moab::DagMC*>( d_dagmc_instance )->get_entity_id( cell_handle );
}

// Get the cell handle from a cell id
/*! \details This function is very slow! Avoid it if possible if 
 * performance is a concern. 
 */
moab::EntityHandle StandardDagMCCellHandler::getCellHandle(
                        const ModuleTraits::InternalCellHandle cell_id ) const
{
  // Make sure the cell exists
  testPrecondition( this->doesCellExist( cell_id ) );

  return const_cast<moab::DagMC*>( d_dagmc_instance )->entity_by_id( 3, cell_id );
}

// Check if the cell exists
/*! \details This function is very slow! Avoid it if possible if 
 * performance is a concern. 
 */
bool StandardDagMCCellHandler::doesCellExist( 
                         const ModuleTraits::InternalCellHandle cell_id ) const
{
  moab::EntityHandle entity_handle = 
    const_cast<moab::DagMC*>( d_dagmc_instance )->entity_by_id( 3, cell_id );

  return this->doesEntityHandleExist( entity_handle );
}

} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_StandardDagMCCellHandler.cpp
//---------------------------------------------------------------------------//
