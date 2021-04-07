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

// Forward declare the DagMCModel
class DagMCModel;

//! The DagMC ray tracer
class DagMCNavigator : public Navigator
{

public:

  //! The reflecting surface map type
  typedef boost::bimap<EntityId,moab::EntityHandle>
  ReflectingSurfaceIdHandleMap;

  //! Constructor
  DagMCNavigator(
          const std::shared_ptr<const DagMCModel>& dagmc_model,
          const Navigator::AdvanceCompleteCallback& advance_complete_callback =
          Navigator::AdvanceCompleteCallback() );

  //! Destructor
  ~DagMCNavigator()
  { /* ... */ }

  //! Get the point location w.r.t. a given cell
  PointLocation getPointLocation(
                             const Length position[3],
                             const double direction[3],
                             const EntityId cell_id ) const override;

  //! Get the surface normal at a point on the surface
  void getSurfaceNormal( const EntityId surface_id,
                         const Length position[3],
                         const double direction[3],
                         double normal[3] ) const override;

  //! Get the boundary cell
  EntityId getBoundaryCell(
                       const EntityId cell_id,
                       const EntityId boundary_surface_id ) const;

  //! Find the cell that contains a given ray
  EntityId findCellContainingRay(
                                  const Length position[3],
                                  const double direction[3],
                                  CellIdSet& found_cell_cache ) const override;

  //! Find the cell that contains the ray
  EntityId findCellContainingRay(
                                    const Length position[3],
                                    const double direction[3] ) const override;

  //! Check if the internal ray is set
  bool isStateSet() const override;

  //! Initialize (or reset) an internal DagMC ray
  void setState( const Length x_position,
                 const Length y_position,
                 const Length z_position,
                 const double x_direction,
                 const double y_direction,
                 const double z_direction ) override;


  //! Initialize (or reset) an internal DagMC ray
  void setState( const Length x_position,
                 const Length y_position,
                 const Length z_position,
                 const double x_direction,
                 const double y_direction,
                 const double z_direction,
                 const EntityId current_cell ) override;

  //! Initialize (or reset) the state (base overloads)
  using Navigator::setState;

  //! Get the internal DagMC ray position
  const Length* getPosition() const override;

  //! Get the internal DagMC ray direction
  const double* getDirection() const override;

  //! Get the cell containing the internal DagMC ray position
  EntityId getCurrentCell() const override;

  //! Get the distance from the internal DagMC ray pos. to the nearest boundary in all directions
  Length getDistanceToClosestBoundary() override;

  //! Get the distance from the internal DagMC ray pos. to the nearest boundary
  Length fireRay( EntityId* surface_hit ) override;

  //! Change the internal ray direction (without changing its location)
  void changeDirection( const double x_direction,
                        const double y_direction,
                        const double z_direction ) override;

  //! Clone the navigator
  DagMCNavigator* clone( const AdvanceCompleteCallback& advance_complete_callback ) const override;

  //! Clone the navigator
  DagMCNavigator* clone() const override;

protected:

  //! Copy constructor
  DagMCNavigator( const DagMCNavigator& other );

  //! Advance the internal DagMC ray to the next boundary
  bool advanceToCellBoundaryImpl( double* surface_normal,
                                  Length& distance_traveled ) override;

  //! Advance the internal DagMC ray a substep
  void advanceBySubstepImpl( const Length substep_distance ) override;

private:

  // Default constructor
  DagMCNavigator();

  // Check if the surface handle is a reflecting surface
  bool isReflectingSurfaceHandle(
                               const moab::EntityHandle surface_handle ) const;

  // Get the point location w.r.t. a given cell
  PointLocation getPointLocationWithCellHandle(
                         const Length position[3],
                         const double direction[3],
                         const moab::EntityHandle cell_handle,
                         const moab::DagMC::RayHistory* history = NULL ) const;

  // Get the surface normal at a point on the surface
  void getSurfaceHandleNormal(
                         const moab::EntityHandle surface_handle,
                         const Length position[3],
                         const double direction[3],
                         double normal[3],
                         const moab::DagMC::RayHistory* history = NULL ) const;

  // Get the boundary cell handle
  moab::EntityHandle getBoundaryCellHandle(
                      const moab::EntityHandle cell_handle,
                      const moab::EntityHandle boundary_surface_handle ) const;

  // Find the cell handle that contains the ray
  moab::EntityHandle findCellHandleContainingRay(
                                  const Length position[3],
                                  const double direction[3],
                                  const bool check_on_boundary = false ) const;

  // Find the cell handle that contains the ray
  moab::EntityHandle findCellHandleContainingRay(
                                  const Length x_position,
                                  const Length y_position,
                                  const Length z_position,
                                  const double x_direction,
                                  const double y_direction,
                                  const double z_direction,
                                  const bool check_on_boundary = false ) const;

  // Get the distance from the ray position to the nearest boundary
  Length fireRayWithCellHandle( const Length position[3],
                                const double direction[3],
                                const moab::EntityHandle current_cell_handle,
                                moab::EntityHandle& surface_hit_handle,
                                moab::DagMC::RayHistory* history = NULL ) const;

  // Set an internal DagMC ray
  void setStateWithCellHandle( const Length x_position,
                               const Length y_position,
                               const Length z_position,
                               const double x_direction,
                               const double y_direction,
                               const double z_direction,
                               const moab::EntityHandle current_cell_handle );

  // Change the direction of the ray
  void changeDirection( const double x_direction,
                        const double y_direction,
                        const double z_direction,
                        const bool reflection );

  // The boundary tolerance
  static const double s_boundary_tol;

  // The DagMC model
  std::shared_ptr<const DagMCModel> d_dagmc_model;

  // The internal ray
  DagMCRay d_internal_ray;
};

/*! The DagMC geometry error
 * \details This error class can be used to record geometry gaps.
 */
class DagMCGeometryError : public GeometryError
{

public:

  DagMCGeometryError( const std::string& what )
    : GeometryError( what )
  { /* ... */ }
};

} // end Geometry namespace

#endif // end GEOMETRY_DAGMC_NAVIGATOR_HPP

//---------------------------------------------------------------------------//
// end Geometry_DagMCNavigator.hpp
//---------------------------------------------------------------------------//
