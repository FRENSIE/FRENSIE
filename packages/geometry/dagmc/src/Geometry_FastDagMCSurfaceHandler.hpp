//---------------------------------------------------------------------------//
//!
//! \file   Geometry_FastDagMCSurfaceHandler.hpp
//! \author Alex Robinson
//! \brief  The fast DagMC surface handler class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_FAST_DAGMC_SURFACE_HANDLER_HPP
#define GEOMETRY_FAST_DAGMC_SURFACE_HANDLER_HPP

// Std Lib Includes
#include <unordered_set>

// Boost Includes
#include <boost/bimap.hpp>
#include <boost/bimap/unordered_set_of.hpp>

// FRENSIE Includes
#include "Geometry_DagMCSurfaceHandler.hpp"

namespace Geometry{

/*! The FastDagMCSurfaceHandler class
 * \details This class is optimized for performance. The conversion from
 * surface handle to surface id or surface id to surface handle is fast. The 
 * handles are stored twice to allow for the fast lookup times (extra storage 
 * overhead).
 */
class FastDagMCSurfaceHandler : public DagMCSurfaceHandler
{

public:

  //! Constructor
  FastDagMCSurfaceHandler( const moab::DagMC* dagmc_instance );

  //! Destructor
  ~FastDagMCSurfaceHandler()
  { /* ... */ }

  //! Check if the surface exists
  bool doesSurfaceExist( const ModuleTraits::InternalSurfaceHandle surface_id ) const;

  // Check if the surface handle exists
  bool doesSurfaceHandleExist( const moab::EntityHandle surface_handle ) const;

  //! Get the surface id from a surface handle
  ModuleTraits::InternalSurfaceHandle getSurfaceId( 
                               const moab::EntityHandle surface_handle ) const;

  //! Get the surface handle from a surface id
  moab::EntityHandle getSurfaceHandle(
                  const ModuleTraits::InternalSurfaceHandle surface_id ) const;

private:

  // The surface id to surface handle map
  typedef boost::bimap<boost::bimaps::unordered_set_of<ModuleTraits::InternalSurfaceHandle>,boost::bimaps::unordered_set_of<moab::EntityHandle> > SurfaceIdHandleMap;

  SurfaceIdHandleMap d_surface_id_handle_map;
};

} // end Geometry namespace

#endif // end GEOMETRY_FAST_DAGMC_SURFACE_HANDLER_HPP

//---------------------------------------------------------------------------//
// end Geometry_FastDagMCSurfaceHandler.hpp
//---------------------------------------------------------------------------//
