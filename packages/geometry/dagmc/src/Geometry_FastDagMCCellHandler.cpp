//---------------------------------------------------------------------------//
//!
//! \file   Geometry_FastDagMCCellHandle.cpp
//! \author Alex Robinson
//! \brief  The fast DagMC cell handler class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Geometry_FastDagMCCellHandler.hpp"
#include "Utility_ContractException.hpp"

namespace Geometry{

// Constructor
FastDagMCCellHandler::FastDagMCCellHandler( const moab::DagMC* dagmc_instance )
  : DagMCCellHandler( dagmc_instance ),
    d_cell_id_handle_map()
{
  // Make sure the DagMC instance is valid
  testPrecondition( dagmc_instance != NULL );

  moab::Range::const_iterator cell_it = this->begin();

  while( cell_it != this->end() )
  {
    ModuleTraits::InternalCellHandle cell_id = 
      const_cast<moab::DagMC*>( dagmc_instance )->get_entity_id( *cell_it );
    
    d_cell_id_handle_map.insert( 
                            CellIdHandleMap::value_type( cell_id, *cell_it ) );
    
    ++cell_it;
  }
}

// Get the cell id from a cell handle
ModuleTraits::InternalCellHandle FastDagMCCellHandler::getCellId( 
                                  const moab::EntityHandle cell_handle ) const
{
  // Make sure the cell handle exists
  testPrecondition( this->doesCellHandleExist( cell_handle ) );

  return d_cell_id_handle_map.right.find( cell_handle )->second;
}

// Get the cell handle from a cell id
moab::EntityHandle FastDagMCCellHandler::getCellHandle(
                        const ModuleTraits::InternalCellHandle cell_id ) const
{
  // Make sure the cell id exists
  testPrecondition( this->doesCellExist( cell_id ) );
  

  return d_cell_id_handle_map.left.find( cell_id )->second;
}

// Check if the cell exists
bool FastDagMCCellHandler::doesCellExist( 
                         const ModuleTraits::InternalCellHandle cell_id ) const
{
  return d_cell_id_handle_map.left.find( cell_id ) !=
    d_cell_id_handle_map.left.end();
}

// Check if the cell handle exists
bool FastDagMCCellHandler::doesCellHandleExist( 
                                   const moab::EntityHandle cell_handle ) const
{
  return d_cell_id_handle_map.right.find( cell_handle ) !=
    d_cell_id_handle_map.right.end();
}

} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_FastDagMCCellHandler.cpp
//---------------------------------------------------------------------------//
