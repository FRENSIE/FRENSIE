//---------------------------------------------------------------------------//
//!
//! \file   Geometry_StandardDagMCSurfaceHandler.cpp
//! \author Alex Robinson
//! \brief  The standard DagMC surface handler class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Geometry_StandardDagMCSurfaceHandler.hpp"
#include "Utility_ContractException.hpp"

namespace Geometry{

// Constructor
StandardDagMCSurfaceHandler::StandardDagMCSurfaceHandler( 
                                            const moab::DagMC* dagmc_instance )
  : DagMCSurfaceHandler( dagmc_instance ),
    d_dagmc_instance( dagmc_instance )
{
  // Make sure the DagMC instance is valid
  testPrecondition( dagmc_instance != NULL );
}

// Get the surface id from a surface handle
ModuleTraits::InternalSurfaceHandle StandardDagMCSurfaceHandler::getSurfaceId( 
                                const moab::EntityHandle surface_handle ) const
{
  // Make sure the surface handle exists
  testPrecondition( this->doesSurfaceHandleExist( surface_handle ) );
  
  return const_cast<moab::DagMC*>( d_dagmc_instance )->get_entity_id( surface_handle );
}

// Get the surface handle from a surface id
/*! \details This function is very slow! Avoid it if possible if 
 * performance is a concern. 
 */
moab::EntityHandle StandardDagMCSurfaceHandler::getSurfaceHandle(
                   const ModuleTraits::InternalSurfaceHandle surface_id ) const
{
  // Make sure the surface exists
  testPrecondition( this->doesSurfaceExist( surface_id ) );

  return const_cast<moab::DagMC*>( d_dagmc_instance )->entity_by_id( 2, surface_id );
}

// Check if the surface exists
/*! \details This function is very slow! Avoid it if possible if 
 * performance is a concern. 
 */
bool StandardDagMCSurfaceHandler::doesSurfaceExist( 
                   const ModuleTraits::InternalSurfaceHandle surface_id ) const
{
  moab::EntityHandle entity_handle = 
    const_cast<moab::DagMC*>( d_dagmc_instance )->entity_by_id( 2, surface_id);

  return this->doesEntityHandleExist( entity_handle );
}

} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_StandardDagMCSurfaceHandler.cpp
//---------------------------------------------------------------------------//
