//---------------------------------------------------------------------------//
//! 
//! \file   Geometry_DagMC.hpp
//! \author Alex Robinson
//! \brief  DagMC wrapper class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_DAGMC_HPP
#define GEOMETRY_DAGMC_HPP

// Std Lib Includes
#include <string>
#include <stdexcept>
#include <unordered_map>
#include <vector>

// Moab Includes
#include <DagMC.hpp>

// FRENSIE Includes
#include "Geometry_DagMCRay.hpp"
#include "Geometry_ModuleTraits.hpp"
#include "Geometry_PointLocation.hpp"
#include "Utility_ContractException.hpp"

namespace Geometry{

/*! The DagMC geometry manager wrapper
  \details
 */
class DagMC
{

public:

  //! Set the termination cell property name
  static void setTerminationCellPropertyName( const std::string& name );

  //! Get the termination cell property name
  static const std::string& getTerminationCellPropertyName();

  //! Set the material property name
  static void setMaterialPropertyName( const std::string& name );

  //! Get the material property name
  static const std::string& getMaterialPropertyName();

  //! Set the density property name
  static void setDensityPropertyName( const std::string& name );

  //! Get the density property name
  static const std::string& getDensityPropertyName();

  //! Set the estimator property name
  static void setEstimatorPropertyName( const std::string& name );

  //! Get the estimator property name
  static const std::string& getEstimatorPropertyName();

  //! Set the surface current name
  static void setSurfaceCurrentName( const std::string& name );

  //! Get the surface current name
  static const std::string& getSurfaceCurrentName();

  //! Set the surface flux name
  static void setSurfaceFluxName( const std::string& name );

  //! Get the surface flux name
  static const std::string& getSurfaceFluxName();

  //! Set the cell pulse height name
  static void setCellPulseHeightName( const std::string& name );

  //! Get the cell pulse height name
  static const std::string& getCellPulseHeightName();

  //! Set the cell track-length flux name
  static void setCellTrackLengthFluxName( const std::string& name );

  //! Get the cell pulse height name
  static const std::string& getCellTrackLengthFluxName();

  //! Set the cell collision flux name
  static void setCellCollisionFluxName( const std::string& name );

  //! Get the cell collision flux name
  static const std::string& getCellCollisionFluxName();

  //! Check if the cell estimator type is valid
  static bool isCellEstimatorTypeValid( const std::string& estimator_type );

  //! Check if the cell observer type is valid
  static bool isCellObserverTypeValid( const std::string& observer_type );

  //! Check if the surface estimator type is valid
  static bool isSurfaceEstimatorTypeValid( const std::string& estimator_type );

  //! Check if the surface observer type is valid
  static bool isSurfaceObserverTypeValid( const std::string& observer_type );

  //! Check if the estimator type is valid
  static bool isEstimatorTypeValid( const std::string& estimator_type );

  //! Check if the observer type is valid
  static bool isObserverTypeValid( const std::string& observer_type );

  //! Check if the particle type is valid
  static bool isParticleTypeValid( const std::string& particle_type );

  //! Extract estimator property values
  static void extractEstimatorPropertyValues( const std::string& prop_value,
					      unsigned& estimator_id,
					      std::string& estimator_type,
					      std::string& particle_type );

  //! Check if DagMC has been initialized
  static bool isInitialized();

  //! Initialize the DagMC geometry manager
  static void initialize( const std::string& filename,
                          const std::vector<std::string>& property_names,
                          const double facet_tol );

  //! Enable thread support
  static void enableThreadSupport( const unsigned num_threads );

  //! Check if a cell exists
  static bool doesCellExist( const ModuleTraits::InternalCellHandle cell_id );

  //! Check if the surface exists
  static bool doesSurfaceExist( 
                        const ModuleTraits::InternalSurfaceHandle surface_id );

  //! Get the problem cells
  template<typename Set>
  static void getCells( Set& cell_set,
                        const bool include_void_cells = true,
                        const bool include_termination_cells = false );

  //! Get the problem surfaces
  template<typename Set>
  static void getSurfaces( Set& surface_set );
                           

  //! Get the cell volume
  static double getCellVolume( const ModuleTraits::InternalCellHandle cell_id);

  //! Get the surface area
  static double getSurfaceArea( 
                        const ModuleTraits::InternalSurfaceHandle surface_id );

  //! Check if the cell is a termination cell
  static bool isTerminationCell(
                              const ModuleTraits::InternalCellHandle cell_id );

  //! Check if the cell is a void cell
  static bool isVoidCell( const ModuleTraits::InternalCellHandle cell_id );

  //! Check if the surface is a reflecting surface
  static bool isReflectingSurface( 
                        const ModuleTraits::InternalSurfaceHandle surface_id );

  //! Get the cell material ids
  template<typename Map>
  static void getCellMaterialIds( Map& cell_id_mat_id_map );

  //! Get the cell densities
  template<typename Map>
  static void getCellDensities( Map& cell_id_density_map );

  //! Get the point location w.r.t. a given cell
  static PointLocation getPointLocation( 
                             const Ray& ray,
                             const ModuleTraits::InternalCellHandle& cell_id );

  //! Get the boundary cell 
  static ModuleTraits::InternalCellHandle
  getBoundaryCell( 
               const ModuleTraits::InternalCellHandle cell_id,
               const ModuleTraits::InternalSurfaceHandle boundary_surface_id );

  //! Get the surface normal at a point on the surface
  static void getSurfaceNormal( 
                          const ModuleTraits::InternalSurfaceHandle surface_id,
                          const double position[3],
                          double norma[3] );

  //! Clear the found cell cache
  static void clearFoundCellCache();

  //! Get the found cell cache
  template<typename Set>
  static void getFoundCellCache( Set& cached_cells );

  //! Find the cell that contains the external ray
  static ModuleTraits::InternalCellHandle findCellContainingExternalRay(
                                                              const Ray& ray );

  //! Find and cached the cell that contains the external ray
  static ModuleTraits::InternalCellHandle 
  findAndCacheCellContainingExternalRay( const Ray& ray );

  //! Get the distance from the external ray position to the nearest boundary
  static double fireExternalRay( 
                            const Ray& ray, 
                            ModuleTraits::InternalSurfaceHandle& surface_hit );

  //! Get the distance from the external ray position to the nearest boundary
  static double fireExternalRay(
                           const Ray& ray,
                           const ModuleTraits::InternalCellHandle current_cell,
                           ModuleTraits::InternalSurfaceHandle& surface_hit );

  //! Check if the internal ray is set
  static bool isInternalRaySet();

  //! Initialize (or reset) an internal DagMC ray
  static void setInternalRay( const double position[3],
                              const double direction[3],
                              const bool cache_start_cell );

  //! Initialize (or reset) an internal DagMC ray
  static void setInternalRay( 
                         const double position[3],
                         const double direction[3],
                         const ModuleTraits::InternalCellHandle current_cell,
                         const bool cache_start_cell = false );

  //! Initialize (or reset) an internal DagMC ray
  static void setInternalRay( const Ray& ray,
                              const bool cache_start_cell = false );

  //! Initialize (or reset) an internal DagMC ray
  static void setInternalRay( 
                         const Ray& ray,
                         const ModuleTraits::InternalCellHandle current_cell,
                         const bool cache_start_cell = false );

  //! Change the internal ray direction (without changing its location)
  static void changeInternalRayDirection( const double direction[3] );

  //! Get the internal DagMC ray position
  static const double* getInternalRayPosition();

  //! Get the internal DagMC ray direction
  static const double* getInternalRayDirection();

  //! Find the cell containing the internal DagMC ray position
  static ModuleTraits::InternalCellHandle findCellContainingInternalRay();

  //! Get the distance from the internal DagMC ray pos. to the nearest boundary
  static double fireInternalRay( 
                            ModuleTraits::InternalSurfaceHandle& surface_hit );

  //! Advance the internal DagMC ray to the next boundary
  static void advanceInternalRayToCellBoundary();

  //! Advance the internal DagMC ray a substep
  static void advanceInternalRayBySubstep( const double substep_distance );

  //! Destructor
  ~DagMC()
  { /* ... */ }

private:

  // Constructor
  DagMC();

  // Get all of the properties
  static void getProperties( std::vector<std::string>& properties );

  // validate the properties
  static void validateProperties( const std::vector<std::string>& properties );

  // Get the cell handle
  static moab::EntityHandle getCellHandle( 
                              const ModuleTraits::InternalCellHandle cell_id );

  // Get the cell id
  static ModuleTraits::InternalCellHandle getCellId( 
                                        const moab::EntityHandle cell_handle );
  
  // Get the surface handle
  static moab::EntityHandle getSurfaceHandle(
                        const ModuleTraits::InternalSurfaceHandle surface_id );

  // Get the surface id
  static ModuleTraits::InternalSurfaceHandle getSurfaceId( 
                                     const moab::EntityHandle surface_handle );

  // Get the point location w.r.t. a given cell
  static PointLocation getPointLocation( 
                                       const double position[3],
                                       const double direction[3],
                                       const moab::EntityHandle& cell_handle );

  // Get the boundary cell 
  static moab::EntityHandle
  getBoundaryCell( const moab::EntityHandle cell_handle,
                   const moab::EntityHandle boundary_surface_handle );

  // Find the cell handle that contains the external ray 
  static moab::EntityHandle findCellHandleContainingExternalRay( 
                                                              const Ray& ray );

  // Find the cell handle that contains the external ray 
  static moab::EntityHandle findCellHandleContainingRay( 
                                                   const double position[3],
                                                   const double direction[3] );

  // Find and cache the cell handle that contains the external ray 
  static moab::EntityHandle findAndCacheCellHandleContainingRay( 
                                                   const double position[3],
                                                   const double direction[3] );

  // Get the distance from the external ray position to the nearest boundary
  static double fireExternalRay( 
                            const Ray& ray,
                            const moab::EntityHandle current_cell_handle,
                            ModuleTraits::InternalSurfaceHandle& surface_hit );

  // Set an internal DagMC ray
  static void setInternalRay( const double position[3],
                              const double direction[3],
                              const moab::EntityHandle current_cell_handle );

  // Get the internal DagMC ray
  static DagMCRay& getInternalRay();

  // Check the found cell cache for a cell that contains the point
  moab::EntityHandle checkFoundCellCache( const double position[3],
                                          const double direction[3] );

  // Add cell to found cell cache
  void addCellToFoundCellCache( const moab::EntityHandle cell_handle );

  // The DagMC instance
  static moab::DagMC* s_dagmc;

  // The problem cells
  static moab::Range s_cells;

  // The problem surfaces
  static moab::Range s_surfaces;

  // The termination cells
  static std::unordered_set<ModuleTraits::InternalCellHandle>
  s_termination_cells;

  // The found cell cache
  static std::unordered_set<moab::EntityHandle> s_found_cell_cache;

  // The internal rays
  static std::vector<DagMCRay> s_internal_rays;

  //! The termination cell property name
  static std::string termination_cell_property;

  //! The material property name
  static std::string material_property;

  //! The density property name
  static std::string density_property;

  //! The estimator property name
  static std::string estimator_property;

  //! The surface current name
  static std::string surface_current_name;

  //! The surface flux name
  static std::string surface_flux_name;

  //! The cell pulse height name
  static std::string cell_pulse_height_name;

  //! The cell track-length flux name
  static std::string cell_track_length_flux_name;

  //! The cell collision flux name
  static std::string cell_collision_flux_name;
};

//! The invalid DagMC geometry error
class InvalidDagMCGeometry : public std::runtime_error
{

public:

  InvalidDagMCGeometry( const std::string& what_arg )
    : std::runtime_error( what_arg )
  { /* ... */ }
};

/*! The DagMC ray misfire error
 * \details This error class can be used to record geometry gaps.
 */
class DagMCRayMisfire : public std::runtime_error
{
 
public:

  DagMCRayMisfire( const std::string& what_arg )
    : std::runtime_error( what_arg )
  { /* ... */ }
};

} // end Geometry namespace

#endif // end GEOMETRY_DAGMC_HPP

//---------------------------------------------------------------------------//
// end Geometry_DagMC.hpp
//---------------------------------------------------------------------------//
