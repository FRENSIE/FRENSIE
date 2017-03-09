//---------------------------------------------------------------------------//
//!
//! \file   Geometry_Model.hpp
//! \author Alex Robinson
//! \brief  The geometry model base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_MODEL_HPP
#define GEOMETRY_MODEL_HPP

// Std Lib Includes
#include <unordered_set>
#include <unordered_map>

// FRENSIE Includes
#include "Geometry_PointLocation.hpp"
#include "Geometry_Ray.hpp"
#include "Geometry_ModuleTraits.hpp"
#include "Utility_ContractException.hpp"

namespace Geometry{

//! The model base class
class Model
{

public:

  //! The material id set type
  typedef std::unordered_set<ModuleTraits::InternalMaterialHandle> MaterialIdSet;

  //! The cell set type
  typedef std::unordered_set<ModuleTraits::InternalCellHandle> CellSet;

  //! The cell id material id map type
  typedef std::unordered_map<ModuleTraits::InternalCellHandle,ModuleTraits::InternalMaterialHandle> CellIdMatIdMap;

  //! The cell id density map type
  typedef std::unordered_map<ModuleTraits::InternalCellHandle,double> CellIdDensityMap;

  //! Constructor
  Model()
  { /* ... */ }

  //! Destructor
  virtual ~Model()
  { /* ... */ }

  //! Enable support for multiple threads
  virtual void enableThreadSupport( const size_t num_threads ) = 0;

  //! Get the cells
  virtual void getCells( CellSet& cells,
                         const bool include_void_cells,
                         const bool include_termination_cells ) const = 0;

  //! Get the material ids
  virtual void getMaterialIds( MaterialIdSet& material_ids ) const = 0;

  //! Get the cell material ids
  virtual void getCellMaterialIds(
                                CellIdMatIdMap& cell_id_mat_id_map ) const = 0;

  //! Get the cell densities
  virtual void getCellDensities( CellDensityMap& cell_density_map ) const = 0;

  //! Check if a cell exists
  virtual bool doesCellExist(
                       const ModuleTraits::InternalCellHandle cell ) const = 0;

  //! Check if the cell is a termination cell
  virtual bool isTerminationCell(
                       const ModuleTraits::InternalCellHandle cell ) const = 0;

  //! Check if a cell is void
  virtual bool isCellVoid(
                       const ModuleTraits::InternalCellHandle cell ) const = 0;

  //! Get the cell volume
  virtual double getCellVolume(
                       const ModuleTraits::InternalCellHandle cell ) const = 0;

  //! Get the location of a cell w.r.t. a given cell
  virtual PointLocation getPointLocation(
                       const Ray& ray,
                       const ModuleTraits::InternalCellHandle cell ) const = 0;

  //! Check if an internal ray has been set
  virtual bool isInternalRaySet();

  /*! Fire an external ray
   *
   * A std::runtime_error (or class derived from it) must be thrown if
   * an error occurs.
   */
  virtual double fireExternalRay(
                  const Ray& ray,
                  ModuleTraits::InternalSurfaceHandle& surface_hit ) const = 0;

  /*! Set the internal ray
   *
   * A std::runtime_error (or class derived from it) must be thrown if
   * an error occurs.
   */
  virtual void setInternalRay(
                       const Ray& ray,
                       const ModuleTraits::InternalCellHandle start_cell ) = 0;

  //! Get the internal ray position
  virtual const double* getInternalRayPosition() const = 0;

  //! Get the internal ray direction
  virtual const double* getInternalRayDirection() const = 0;

  /*! Find the cell that contains a given start ray
   *
   * A std::runtime_error (or class derived from it) must be thrown
   * if an error occurs.
   */
  virtual ModuleTraits::InternalCellHandle findCellContainingStartRay(
                                                    const Ray& ray ) const = 0;

  /*! Find the cell that contains the internal ray
   *
   * A std::runtime_error (or class derived from it) must be thrown
   * if an error occurs.
   */
  virtual ModuleTraits::InternalCellHandle findCellContainingInternalRay() const = 0;

  /*! Fire the internal ray through the geometry
   *
   * A std::runtime_error (or class derived from it) must be thrown
   * if a ray tracing error occurs.
   */
  virtual double fireInternalRay(
                  ModuleTraits::InternalSurfaceHandle& surface_hit ) const = 0;

  /*! Advance the internal ray to the cell boundary
   *
   * If a reflecting surface is hit "true" will be returned.
   */
  virtual bool advanceInternalRayToCellBoundary( double surface_normal[3] ) = 0;

  //! Advance the internal ray by a substep (less than distance to boundary)
  virtual bool advanceInternalRayBySubstep( const double step_size ) = 0;

  //! Change the internal ray direction
  virtual void changeInternalRayDirection( const double direction[3] ) = 0;
};
  
} // end Geometry namespace

#endif // end GEOMETRY_MODEL_HPP

//---------------------------------------------------------------------------//
// end Geometry_Model.hpp
//---------------------------------------------------------------------------//
