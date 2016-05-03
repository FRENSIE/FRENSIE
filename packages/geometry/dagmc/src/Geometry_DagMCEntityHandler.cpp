//---------------------------------------------------------------------------//
//!
//! \file   Geometry_DagMCEntityHandler.cpp
//! \author Alex Robinson
//! \brief  The DagMC entity handler class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Geometry_DagMCEntityHandler.hpp"
#include "Utility_ContractException.hpp"

namespace Geometry{

// Constructor
DagMCEntityHandler::DagMCEntityHandler()
  : d_entities()
{ /* ...*/ }

// Constructor
DagMCEntityHandler::DagMCEntityHandler( const moab::Range& entities )
  : d_entities( entities )
{
  // Make sure there are entities
  testPrecondition( !entities.empty() );
}

// Set the entities
void DagMCEntityHandler::setEntities( const moab::Range& entities )
{
  // Make sure there are entities
  testPrecondition( !entities.empty() );
  
  d_entities = entities;
}

// Get the number of entities
size_t DagMCEntityHandler::getNumberOfEntities() const
{
  return d_entities.size();
}

// Check if the entity exists
bool DagMCEntityHandler::doesEntityHandleExist( 
                                 const moab::EntityHandle entity_handle ) const
{
  return d_entities.find( entity_handle ) != d_entities.end();
}

// Get the beginning const iterator
moab::Range::const_iterator DagMCEntityHandler::begin() const
{
  return d_entities.begin();
}

// Get the ending const iterator
moab::Range::const_iterator DagMCEntityHandler::end() const
{
  return d_entities.end();
}

} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_DagMCEntityHandler.cpp
//---------------------------------------------------------------------------//
