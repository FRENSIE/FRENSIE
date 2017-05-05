//---------------------------------------------------------------------------//
//!
//! \file   Geometry_DagMCNavigator.hpp
//! \author Alex Robinson
//! \brief  The DagMC navigator class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_DAGMC_NAVIGATOR_HPP
#define GEOMETRY_DAGMC_NAVIGATOR_HPP

// Boost Includes
#include <boost/bimap.hpp>

// Moab Includes
#include <DagMC.hpp>

// FRENSIE Includes
#include "Geometry_DagMCCellHandler.hpp"
#include "Geometry_DagMCSurfaceHandler.hpp"
#include "Geometry_DagMCRay.hpp"
#include "Geometry_Navigator.hpp"

namespace Geometry{

//! The DagMC ray tracer
class DagMCNavigator : public Navigator
{

public:

  //! The reflecting surface map type
  typedef boost::bimap<ModuleTraits::InternalSurfaceHandle,moab::EntityHandle>
  ReflectingSurfaceIdHandleMap;

  //! Constructor
  DagMCNavigator( moab::DagMC* dagmc_instance,
                  const std::shared_ptr<const Geometry::DagMCCellHandler>&
                  cell_handler,
                  const std::shared_ptr<const Geometry::DagMCSurfaceHandler>&
                  surface_handler,
                  const std::shared_ptr<const ReflectingSurfaceIdHandleMap>&
                  reflecting_surfaces );

  //! Destructor
  ~DagMCNavigator()
  { /* ... */ }

  //! Get the point location w.r.t. a given cell
  PointLocation getPointLocation(
               const double position[3],
               const double direction[3],
               const ModuleTraits::InternalCellHandle cell_id ) const override;

  //! Get the surface normal at a point on the surface
  void getSurfaceNormal( const ModuleTraits::InternalSurfaceHandle surface_id,
                         const double position[3],
                         const double direction[3],
                         double normal[3] ) const override;

  //! Get the boundary cell
  ModuleTraits::InternalCellHandle getBoundaryCell(
         const ModuleTraits::InternalCellHandle cell_id,
         const ModuleTraits::InternalSurfaceHandle boundary_surface_id ) const;

  //! Find the cell that contains a given ray
  ModuleTraits::InternalCellHandle findCellContainingRay(
                                  const double position[3],
                                  const double direction[3],
                                  CellIdSet& found_cell_cache ) const override;

  //! Find the cell that contains the ray
  ModuleTraits::InternalCellHandle findCellContainingRay(
                                    const double position[3],
                                    const double direction[3] ) const override;

  //! Check if the internal ray is set
  bool isInternalRaySet() const override;

  //! Initialize (or reset) an internal DagMC ray
  void setInternalRay( const double x_position,
                       const double y_position,
                       const double z_position,
                       const double x_direction,
                       const double y_direction,
                       const double z_direction ) override;
                      
                       
  //! Initialize (or reset) an internal DagMC ray
  void setInternalRay(
                const double x_position,
                const double y_position,
                const double z_position,
                const double x_direction,
                const double y_direction,
                const double z_direction,
                const ModuleTraits::InternalCellHandle current_cell ) override;

  //! Get the internal DagMC ray position
  const double* getInternalRayPosition() const override;

  //! Get the internal DagMC ray direction
  const double* getInternalRayDirection() const override;

  //! Get the cell containing the internal DagMC ray position
  ModuleTraits::InternalCellHandle getCellContainingInternalRay() const override;

  //! Get the distance from the internal DagMC ray pos. to the nearest boundary
  double fireInternalRay( ModuleTraits::InternalSurfaceHandle* surface_hit ) override;

  //! Advance the internal DagMC ray to the next boundary
  bool advanceInternalRayToCellBoundary( double* surface_normal ) override;

  //! Advance the internal DagMC ray a substep
  void advanceInternalRayBySubstep( const double substep_distance ) override;

  //! Change the internal ray direction (without changing its location)
  void changeInternalRayDirection( const double x_direction,
                                   const double y_direction,
                                   const double z_direction ) override;

  //! Clone the navigator
  DagMCNavigator* clone() const override;

private:

  // Check if the surface handle is a reflecting surface
  bool isReflectingSurfaceHandle(
                               const moab::EntityHandle surface_handle ) const;

  // Get the point location w.r.t. a given cell
  PointLocation getPointLocation(
                         const double position[3],
                         const double direction[3],
                         const moab::EntityHandle cell_handle,
                         const moab::DagMC::RayHistory* history = NULL ) const;

  // Get the surface normal at a point on the surface
  void getSurfaceHandleNormal(
                         const moab::EntityHandle surface_handle,
                         const double position[3],
                         const double direction[3],
                         double normal[3],
                         const moab::DagMC::RayHistory* history = NULL ) const;

  // Get the boundary cell handle
  moab::EntityHandle getBoundaryCellHandle(
                      const moab::EntityHandle cell_handle,
                      const moab::EntityHandle boundary_surface_handle ) const;

  // Find the cell handle that contains the ray
  moab::EntityHandle findCellHandleContainingRay(
                                  const double position[3],
                                  const double direction[3],
                                  const bool check_on_boundary = false ) const;

  // Find the cell handle that contains the ray
  moab::EntityHandle findCellHandleContainingRay(
                                  const double x_position,
                                  const double y_position,
                                  const double z_position,
                                  const double x_direction,
                                  const double y_direction,
                                  const double z_direction,
                                  const bool check_on_boundary = false ) const;

  // Get the distance from the ray position to the nearest boundary
  double fireRayWithCellHandle(
                               const double position[3],
                               const double direction[3],
                               const moab::EntityHandle current_cell_handle,
                               moab::EntityHandle& surface_hit_handle,
                               moab::DagMC::RayHistory* history = NULL ) const;

  // Set an internal DagMC ray
  void setInternalRay( const double x_position,
                       const double y_position,
                       const double z_position,
                       const double x_direction,
                       const double y_direction,
                       const double z_direction,
                       const moab::EntityHandle current_cell_handle );

  // The boundary tolerance
  static const double s_boundary_tol;

  // The raw DagMC instance
  moab::DagMC* d_dagmc;

  // The DagMC cell handler
  std::shared_ptr<const Geometry::DagMCCellHandler> d_cell_handler;

  // The DagMC surface handler
  std::shared_ptr<const Geometry::DagMCSurfaceHandler> d_surface_handler;

  // The reflecting surfaces
  std::shared_ptr<const ReflectingSurfaceIdHandleMap> d_reflecting_surfaces;

  // The internal rays
  DagMCRay d_internal_ray;
};

/*! The DagMC geometry error
 * \details This error class can be used to record geometry gaps.
 */
class DagMCGeometryError : public std::runtime_error
{

public:

  DagMCGeometryError( const std::string& what_arg )
    : std::runtime_error( what_arg )
  { /* ... */ }
};
  
} // end Geometry namespace

#endif // end GEOMETRY_DAGMC_NAVIGATOR_HPP

//---------------------------------------------------------------------------//
// end Geometry_DagMCNavigator.hpp
//---------------------------------------------------------------------------//
