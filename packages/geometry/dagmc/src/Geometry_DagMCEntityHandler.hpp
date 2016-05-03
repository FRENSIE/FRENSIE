//---------------------------------------------------------------------------//
//!
//! \file   Geometry_DagMCEntityHandler.hpp
//! \author Alex Robinson
//! \brief  The DagMC entity handler class declaration
//! 
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_DAGMC_ENTITY_HANDLER_HPP
#define GEOMETRY_DAGMC_ENTITY_HANDLER_HPP

// Moab Includes
#include <moab/Range.hpp>

namespace Geometry{

//! The DagMCEntityHandler class
class DagMCEntityHandler
{
  
public:

  //! Constructor
  DagMCEntityHandler( const moab::Range& entities );

  //! Destructor
  virtual ~DagMCEntityHandler()
  { /* ... */ }

  //! Get the beginning const iterator
  moab::Range::const_iterator begin() const;

  //! Get the ending const iterator
  moab::Range::const_iterator end() const;

protected:

  //! Constructor
  DagMCEntityHandler();

  //! Set the entities
  void setEntities( const moab::Range& entities );

  //! Get the number of entities
  size_t getNumberOfEntities() const;

  //! Check if the entity exists
  bool doesEntityHandleExist( const moab::EntityHandle entity_handle ) const;

private:
  
  // The entities
  moab::Range d_entities;
};

} // end Geometry namespace

#endif // end GEOMETRY_DAGMC_ENTITY_HANDLER_HPP

//---------------------------------------------------------------------------//
// end Geometry_DagMCEntityHandler.hpp
//---------------------------------------------------------------------------//
