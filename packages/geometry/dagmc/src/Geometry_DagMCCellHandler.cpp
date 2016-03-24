//---------------------------------------------------------------------------//
//!
//! \file   Geometry_DagMCCellHandler.cpp
//! \author Alex Robinson
//! \brief  The DagMC cell handle class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Geometry_DagMCCellHandler.hpp"
#include "Utility_MOABException.hpp"
#include "Utility_ContractException.hpp"

namespace Geometry{

//! Constructor
DagMCCellHandler::DagMCCellHandler( const moab::DagMC* dagmc_instance )
  : DagMCEntityHandler()
{
  // Make sure the DagMC instance is valid
  testPrecondition( dagmc_instance != NULL );

  moab::DagMC* nonconst_dagmc_instance = 
    const_cast<moab::DagMC*>( dagmc_instance );

  moab::Interface* moab_instance = nonconst_dagmc_instance->moab_instance();
  
  const int three = 3;
  const void* const three_val[] = {&three};
  
  moab::Tag geom_tag = nonconst_dagmc_instance->geom_tag();

  moab::Range cell_handles;
  
  moab::ErrorCode return_value = 
    moab_instance->get_entities_by_type_and_tag( 0, 
                                                 moab::MBENTITYSET,
                                                 &geom_tag,
                                                 three_val,
                                                 1,
                                                 cell_handles );
    
  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      Utility::MOABException,
                      moab::ErrorCodeStr[return_value] );

  this->setEntities( cell_handles );
}

// Get the number of cells
size_t DagMCCellHandler::getNumberOfCells() const
{
  return this->getNumberOfEntities();
}

// Check if the cell handle exists
bool DagMCCellHandler::doesCellHandleExist(
                                  const moab::EntityHandle cell_handle ) const
{
  return this->doesEntityHandleExist( cell_handle );
}

} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_DagMCCellHandler.cpp
//---------------------------------------------------------------------------//
