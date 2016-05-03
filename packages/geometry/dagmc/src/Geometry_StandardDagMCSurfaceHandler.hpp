//---------------------------------------------------------------------------//
//!
//! \file   Geometry_StandardDagMCSurfaceHandler.hpp
//! \author Alex Robinson
//! \brief  The standard DagMC surface handler class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_STANDARD_DAGMC_SURFACE_HANDLER_HPP
#define GEOMETRY_STANDARD_DAGMC_SURFACE_HANDLER_HPP

// FRENSIE Includes
#include "Geometry_DagMCSurfaceHandler.hpp"

namespace Geometry{

/*! The StandardDagMCSurfaceHandler class
 * \details This class is optimized for minimal storage. The conversion
 * from surface handle to surface id is fast but the conversion from surface id
 * to surface handle is very slow. Avoid the later conversion if performance is
 * a concern.
 */
class StandardDagMCSurfaceHandler : public DagMCSurfaceHandler
{

public:

  //! Constructor
  StandardDagMCSurfaceHandler( const moab::DagMC* dagmc_instance );
  

  //! Destructor
  ~StandardDagMCSurfaceHandler()
  { /* ... */ }

  //! Check if the surface exists
  bool doesSurfaceExist( 
                  const ModuleTraits::InternalSurfaceHandle surface_id ) const;

  //! Get the surface id from a surface handle
  ModuleTraits::InternalSurfaceHandle getSurfaceId( 
                               const moab::EntityHandle surface_handle ) const;

  //! Get the surface handle from a surface id
  moab::EntityHandle getSurfaceHandle(
                  const ModuleTraits::InternalSurfaceHandle surface_id ) const;

private:

  // The dagmc instance
  const moab::DagMC* d_dagmc_instance;
};

} // end Geometry namespace

#endif // end GEOMETRY_STANDARD_DAGMC_SURFACE_HANDLER_HPP

//---------------------------------------------------------------------------//
// end Geometry_StandardDagMCSurfaceHandler.hpp
//---------------------------------------------------------------------------//
