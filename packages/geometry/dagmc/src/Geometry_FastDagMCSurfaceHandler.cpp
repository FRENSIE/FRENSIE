//---------------------------------------------------------------------------//
//!
//! \file   Geometry_FastDagMCSurfaceHandle.cpp
//! \author Alex Robinson
//! \brief  The fast DagMC surface handler class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Geometry_FastDagMCSurfaceHandler.hpp"
#include "Utility_ContractException.hpp"

namespace Geometry{

// Constructor
FastDagMCSurfaceHandler::FastDagMCSurfaceHandler( 
                                            const moab::DagMC* dagmc_instance )
  : DagMCSurfaceHandler( dagmc_instance ),
    d_surface_id_handle_map()
{
  // Make sure the DagMC instance is valid
  testPrecondition( dagmc_instance != NULL );

  moab::Range::const_iterator surface_it = this->begin();

  while( surface_it != this->end() )
  {
    ModuleTraits::InternalSurfaceHandle surface_id = 
      const_cast<moab::DagMC*>( dagmc_instance )->get_entity_id( *surface_it );
    
    d_surface_id_handle_map.insert( 
                   SurfaceIdHandleMap::value_type( surface_id, *surface_it ) );
    
    ++surface_it;
  }
}

// Get the surface id from a surface handle
ModuleTraits::InternalSurfaceHandle FastDagMCSurfaceHandler::getSurfaceId( 
                                const moab::EntityHandle surface_handle ) const
{
  // Make sure the surface handle exists
  testPrecondition( this->doesSurfaceHandleExist( surface_handle ) );

  return d_surface_id_handle_map.right.find( surface_handle )->second;
}

// Get the surface handle from a surface id
moab::EntityHandle FastDagMCSurfaceHandler::getSurfaceHandle(
                   const ModuleTraits::InternalSurfaceHandle surface_id ) const
{
  // Make sure the surface id exists
  testPrecondition( this->doesSurfaceExist( surface_id ) );
  

  return d_surface_id_handle_map.left.find( surface_id )->second;
}

// Check if the surface exists
bool FastDagMCSurfaceHandler::doesSurfaceExist( 
                   const ModuleTraits::InternalSurfaceHandle surface_id ) const
{
  return d_surface_id_handle_map.left.find( surface_id ) !=
    d_surface_id_handle_map.left.end();
}

// Check if the surface handle exists
bool FastDagMCSurfaceHandler::doesSurfaceHandleExist( 
                                const moab::EntityHandle surface_handle ) const
{
  return d_surface_id_handle_map.right.find( surface_handle ) !=
    d_surface_id_handle_map.right.end();
}

} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_FastDagMCSurfaceHandler.cpp
//---------------------------------------------------------------------------//
