//---------------------------------------------------------------------------//
//!
//! \file   Geometry_DagMCSurfaceHandler.hpp
//! \author Alex Robinson
//! \brief  The DagMC surface handler class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_DAGMC_SURFACE_HANDLER_HPP
#define GEOMETRY_DAGMC_SURFACE_HANDLER_HPP

// Moab Includes
#include <DagMC.hpp>

// FRENSIE Includes
#include "Geometry_DagMCEntityHandler.hpp"
#include "Geometry_Navigator.hpp"

namespace Geometry{

//! The DagMCSurfaceHandler class
class DagMCSurfaceHandler : public DagMCEntityHandler
{

public:

  //! The internal surface handle type
  typedef unsigned long long EntityId;

  //! Constructor
  DagMCSurfaceHandler( const moab::DagMC* dagmc_instance );

  //! Destructor
  virtual ~DagMCSurfaceHandler()
  { /* ... */ }

  //! Get the number of surfaces
  size_t getNumberOfSurfaces() const;

  //! Check if the surface exists
  virtual bool doesSurfaceExist(
                            const EntityId surface_id ) const = 0;

  //! Check if the surface handle exists
  virtual bool doesSurfaceHandleExist(
                               const moab::EntityHandle surface_handle ) const;

  //! Get the surface id from a surface handle
  virtual EntityId getSurfaceId(
                           const moab::EntityHandle surface_handle ) const = 0;

  //! Get the surface handle from a surface id
  virtual moab::EntityHandle getSurfaceHandle(
                            const EntityId surface_id ) const = 0;
};

} // end Geometry namespace

#endif // end GEOMETRY_DAGMC_SURFACE_HANDLER_HPP

//---------------------------------------------------------------------------//
// end Geometry_DagMCSurfaceHandler.hpp
//---------------------------------------------------------------------------//
