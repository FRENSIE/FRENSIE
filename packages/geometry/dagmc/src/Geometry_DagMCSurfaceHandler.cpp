//---------------------------------------------------------------------------//
//!
//! \file   Geometry_DagMCSurfaceHandler.cpp
//! \author Alex Robinson
//! \brief  The DagMC surface handle class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Geometry_DagMCSurfaceHandler.hpp"
#include "Utility_MOABException.hpp"
#include "Utility_ContractException.hpp"

namespace Geometry{

//! Constructor
DagMCSurfaceHandler::DagMCSurfaceHandler( const moab::DagMC* dagmc_instance )
  : DagMCEntityHandler()
{
  // Make sure the DagMC instance is valid
  testPrecondition( dagmc_instance != NULL );

  moab::DagMC* nonconst_dagmc_instance = 
    const_cast<moab::DagMC*>( dagmc_instance );

  moab::Interface* moab_instance = nonconst_dagmc_instance->moab_instance();
  
  const int two = 2;
  const void* const two_val[] = {&two};
  
  moab::Tag geom_tag = nonconst_dagmc_instance->geom_tag();

  moab::Range surface_handles;
  
  moab::ErrorCode return_value = 
    moab_instance->get_entities_by_type_and_tag( 0, 
                                                 moab::MBENTITYSET,
                                                 &geom_tag,
                                                 two_val,
                                                 1,
                                                 surface_handles );
    
  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      Utility::MOABException,
                      moab::ErrorCodeStr[return_value] );

  this->setEntities( surface_handles );
}

// Get the number of surfaces
size_t DagMCSurfaceHandler::getNumberOfSurfaces() const
{
  return this->getNumberOfEntities();
}

// Check if the surface handle exists
bool DagMCSurfaceHandler::doesSurfaceHandleExist(
                                const moab::EntityHandle surface_handle ) const
{
  return this->doesEntityHandleExist( surface_handle );
}

} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_DagMCSurfaceHandler.cpp
//---------------------------------------------------------------------------//
