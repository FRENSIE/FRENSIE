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
#include <unordered_set>
#include <vector>
#include <iostream>

// Boost Includes
#include <boost/bimap.hpp>
#include <boost/scoped_ptr.hpp>

// Moab Includes
#include <DagMC.hpp>

// FRENSIE Includes
#include "Geometry_DagMCRay.hpp"
#include "Geometry_DagMCCellHandler.hpp"
#include "Geometry_DagMCSurfaceHandler.hpp"
#include "Geometry_ModuleTraits.hpp"
#include "Geometry_PointLocation.hpp"
#include "Utility_ContractException.hpp"

namespace Geometry{

//! The DagMC geometry manager wrapper
class DagMC
{

public:

  //! Set the termination cell property name
  static void setTerminationCellPropertyName( const std::string& name );

  //! Get the termination cell property name
  static const std::string& getTerminationCellPropertyName();

  //! Set the reflecting surface property name
  static void setReflectingSurfacePropertyName( const std::string& name );

  //! Get the reflecting surface property name
  static const std::string& getReflectingSurfacePropertyName();

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

  //! Check if the surface estimator type is valid
  static bool isSurfaceEstimatorTypeValid( const std::string& estimator_type );

  //! Check if the estimator type is valid
  static bool isEstimatorTypeValid( const std::string& estimator_type );

  //! Check if the particle type is valid
  static bool isParticleTypeValid( const std::string& particle_type );

  //! Check if DagMC has been initialized
  static bool isInitialized();

  //! Initialize the DagMC geometry manager
  static void initialize( const std::string& filename,
                          const double facet_tol,
                          const bool use_fast_id_lookup = false,
                          std::ostream& os_warn = std::cerr );

  //! Enable thread support
  static void enableThreadSupport( const unsigned num_threads );

  //! Get the material ids
  template<typename Set>
  static void getMaterialIds( Set& material_ids );

  //! Get the cell estimator data
  template<typename Map>
  static void getCellEstimatorData( Map& estimator_id_data_map );

  //! Get the surface estimator data
  template<typename Map>
  static void getSurfaceEstimatorData( Map& estimator_id_data_map );

  //! Check if a cell exists
  static bool doesCellExist( const ModuleTraits::InternalCellHandle cell_id );

  //! Get the problem cells
  template<typename Set>
  static void getCells( Set& cell_set,
                        const bool include_void_cells = true,
                        const bool include_termination_cells = false );

  //! Get the cell volume
  static double getCellVolume( const ModuleTraits::InternalCellHandle cell_id);

  //! Get the cell material ids
  template<typename Map>
  static void getCellMaterialIds( Map& cell_id_mat_id_map );

  //! Get the cell densities
  template<typename Map>
  static void getCellDensities( Map& cell_id_density_map );

  //! Check if the cell is a termination cell
  static bool isTerminationCell(
                              const ModuleTraits::InternalCellHandle cell_id );

  //! Check if the cell is a void cell
  static bool isVoidCell( const ModuleTraits::InternalCellHandle cell_id );

  //! Check if the surface exists
  static bool doesSurfaceExist( 
                        const ModuleTraits::InternalSurfaceHandle surface_id );
  
  //! Get the problem surfaces
  template<typename Set>
  static void getSurfaces( Set& surface_set );

  //! Get the surface area
  static double getSurfaceArea( 
                        const ModuleTraits::InternalSurfaceHandle surface_id );

  //! Check if the surface is a reflecting surface
  static bool isReflectingSurface( 
                        const ModuleTraits::InternalSurfaceHandle surface_id );

  //! Get the point location w.r.t. a given cell
  static PointLocation getPointLocation( 
                              const Ray& ray,
                              const ModuleTraits::InternalCellHandle cell_id );

  //! Get the boundary cell 
  static ModuleTraits::InternalCellHandle
  getBoundaryCell( 
               const ModuleTraits::InternalCellHandle cell_id,
               const ModuleTraits::InternalSurfaceHandle boundary_surface_id );

  //! Get the surface normal at a point on the surface
  static void getSurfaceNormal( 
                          const ModuleTraits::InternalSurfaceHandle surface_id,
                          const double position[3],
                          double normal[3] );

  //! Clear the found cell cache
  static void clearFoundCellCache();

  //! Get the found cell cache
  template<typename Set>
  static void getFoundCellCache( Set& cached_cells );

  //! Find the cell that contains the external ray
  static ModuleTraits::InternalCellHandle findCellContainingExternalRay(
                                            const Ray& ray,
                                            const bool boundary_check = true );

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
                              const bool cache_start_cell = false );

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

  //! Change the internal ray direction (without changing its location)
  static void changeInternalRayDirection( const double x_direction,
                                          const double y_direction,
                                          const double z_direction );

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
  static bool advanceInternalRayToCellBoundary( double* surface_normal = NULL);

  //! Advance the internal DagMC ray a substep
  static void advanceInternalRayBySubstep( const double substep_distance );

  //! Destructor
  ~DagMC()
  { /* ... */ }

private:

  // Constructor
  DagMC();

  // Get all of the properties
  static void getPropertyNames( std::vector<std::string>& properties );

  // validate the properties
  static void validatePropertyNames(const std::vector<std::string>& properties,
                                    std::ostream& os_warn );

  // Get the surface normal at a point on the surface
  static void getSurfaceHandleNormal( 
                               const moab::EntityHandle surface_handle,
                               const double position[3],
                               double normal[3],
                               const moab::DagMC::RayHistory* history = NULL );

  // Get the property values associated with a property name
  template<typename StringArray>
  static void getPropertyValues( const std::string& property,
                                 StringArray& values );

  // Get the cells associated with a property name
  static void getCellsWithProperty( std::vector<moab::EntityHandle>& cells,
                                    const std::string& property,
                                    const std::string* property_value = NULL );

  // Get the surfaces associated with a property name
  static void getSurfacesWithProperty( 
                                    std::vector<moab::EntityHandle>& surfaces,
                                    const std::string& property,
                                    const std::string* property_value = NULL );

  // Get the property values associated with a property name and cell id
  template<typename Map>
  static void getCellPropertyValues( const std::string& property,
                                     Map& cell_id_prop_val_map );

  // Get the cell ids with a property value
  template<typename Map>
  static void getCellIdsWithPropertyValue( const std::string& property,
                                           Map& prop_val_cell_id_map );

  // Get the property values associated with a property name and surface id
  template<typename Map>
  static void getSurfacePropertyValues( const std::string& property,
                                        Map& surface_id_prop_val_map );

  // Get the surface ids with a property value
  template<typename Map>
  static void getSurfaceIdsWithPropertyValue( const std::string& property,
                                              Map& prop_val_surface_id_map );

  // Extract estimator property values
  static void extractEstimatorPropertyValues( const std::string& prop_value,
					      unsigned& estimator_id,
					      std::string& estimator_type,
					      std::string& particle_type );

  //! Check if the surface handle is a reflecting surface
  static bool isReflectingSurfaceHandle( 
                                     const moab::EntityHandle surface_handle );

  // Get the point location w.r.t. a given cell
  static PointLocation getPointLocation( 
                               const double position[3],
                               const double direction[3],
                               const moab::EntityHandle cell_handle,
                               const moab::DagMC::RayHistory* history = NULL );

  // Get the boundary cell handle
  static moab::EntityHandle
  getBoundaryCellHandle( const moab::EntityHandle cell_handle,
                         const moab::EntityHandle boundary_surface_handle );

  // Find the cell handle that contains the external ray 
  static moab::EntityHandle findCellHandleContainingExternalRay( 
                                            const Ray& ray,
                                            const bool boundary_check = true );

  // Find the cell handle that contains the external ray 
  static moab::EntityHandle findCellHandleContainingRay( 
                                        const double position[3],
                                        const double direction[3],
                                        const bool check_on_boundary = false );

  // Find and cache the cell handle that contains the external ray 
  static moab::EntityHandle findAndCacheCellHandleContainingRay( 
                                                   const double position[3],
                                                   const double direction[3] );

  // Get the distance from the external ray position to the nearest boundary
  static double fireExternalRayWithCellHandle( 
                            const double position[3],
                            const double direction[3],
                            const moab::EntityHandle current_cell_handle,
                            moab::EntityHandle& surface_hit_handle );

  // Set an internal DagMC ray
  static void setInternalRay( const double position[3],
                              const double direction[3],
                              const moab::EntityHandle current_cell_handle );

  // Get the internal DagMC ray
  static DagMCRay& getInternalRay();

  // Check the found cell cache for a cell that contains the point
  static moab::EntityHandle checkFoundCellCache( const double position[3],
                                                 const double direction[3] );

  // Add cell to found cell cache
  static void addCellToFoundCellCache( const moab::EntityHandle cell_handle );

  // Convert an array to a string
  static std::string arrayToString( const double data[3] );

  // The DagMC instance
  static moab::DagMC* s_dagmc;

  // The DagMC cell handler
  static boost::scoped_ptr<Geometry::DagMCCellHandler> s_cell_handler;

  // The DagMC surface handle
  static boost::scoped_ptr<Geometry::DagMCSurfaceHandler> s_surface_handler;

  // The termination cells
  static std::unordered_set<ModuleTraits::InternalCellHandle>
  s_termination_cells;

  // The reflecting surfaces
  typedef boost::bimap<ModuleTraits::InternalSurfaceHandle,moab::EntityHandle>
  ReflectingSurfaceIdHandleMap;
  static ReflectingSurfaceIdHandleMap s_reflecting_surfaces;

  // The found cell cache
  static std::unordered_set<moab::EntityHandle> s_found_cell_cache;
  
  // The internal rays
  static std::vector<DagMCRay> s_internal_rays;

  //! The termination cell property name
  static std::string termination_cell_property;

  //! The reflecting surface property name
  static std::string reflecting_surface_property;

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

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Geometry_DagMC_def.hpp"

//---------------------------------------------------------------------------//

#endif // end GEOMETRY_DAGMC_HPP

//---------------------------------------------------------------------------//
// end Geometry_DagMC.hpp
//---------------------------------------------------------------------------//
