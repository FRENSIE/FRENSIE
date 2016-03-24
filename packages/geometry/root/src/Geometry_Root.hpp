//---------------------------------------------------------------------------//
//!
//! \file   Geometry_Root.hpp
//! \author Alex Robinson, Eli Moll
//! \brief  Root wrapper class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_ROOT_HPP
#define GEOMETRY_ROOT_HPP

// Std Lib Includes
#include <string>
#include <stdexcept>
#include <unordered_map>
#include <vector>

// Root Includes
#include <TGeoManager.h>

// FRENSIE Includes
#include "Geometry_Ray.hpp"
#include "Geometry_ModuleTraits.hpp"
#include "Geometry_PointLocation.hpp"
#include "Utility_ContractException.hpp"

namespace Geometry{

/*! Root geometry manager wrapper
 * \details This wrapper class is designed to hide the Root classes and
 * interfaces. Once a Root geometry is initialized cell properties can be
 * queried and ray tracing can be done. Note that ray tracing can be done
 * in two ways: with external rays (Geomery::Ray objects) or internal rays,
 * which are completely hidden from the user. When using external rays the 
 * internal root ray will be modified. Mixing external and internal methods 
 * during a ray trace is therefore not recommended. Performance for 
 * the internal ray trace should be better than for the external ray trace.
 */
class Root
{

public:

  //! Get the material property name
  static const std::string& getMaterialPropertyName();

  //! Set the material property name
  static void setMaterialPropertyName( 
                                   const std::string& material_property_name );

  //! Get the void material property name
  static const std::string& getVoidMaterialName();

  //! Set the void material property name
  static void setVoidMaterialName( const std::string& void_material_name );

  //! Get the terminal material property name
  static const std::string& getTerminalMaterialName();

  //! Set the terminal material property name
  static void setTerminalMaterialName(
                                   const std::string& terminal_material_name );

  //! Check if root has been initialized
  static bool isInitialized();

  //! Initialize the root geometry manager
  static void initialize( const std::string& filename );
  
  //! Enable thread support
  static void enableThreadSupport( const unsigned num_threads );

  //! Get the material ids
  template<typename Set>
  static void getMaterialIds( Set& material_ids );

  //! Check if a cell exists
  static bool doesCellExist( const ModuleTraits::InternalCellHandle cell_id );

  //! Get the problem cells
  template<typename Set>
  static void getCells( Set& cell_set, 
                        const bool include_void_cells = true,
                        const bool include_termination_cells = false );
  
  //! Get the cell volume
  static double getCellVolume( const ModuleTraits::InternalCellHandle cell_id);

  //! Get the cell materials
  template<typename Map>
  static void getCellMaterialNames( Map& cell_id_mat_name_map );

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

  //! Get the point location w.r.t. a given cell
  static PointLocation getPointLocation( 
                              const double position[3],
                              const ModuleTraits::InternalCellHandle cell_id );

  //! Get the point location w.r.t. a given cell
  static PointLocation getPointLocation( 
                              const Ray& ray,
                              const ModuleTraits::InternalCellHandle cell_id );

  //! Find the cell that contains the external ray
  static ModuleTraits::InternalCellHandle findCellContainingExternalRay( 
                                                              const Ray& ray );

  //! Get the distance from the external ray position to the nearest boundary
  static double fireExternalRay( const Ray& ray );

  //! Check if the internal ray is set
  static bool isInternalRaySet();

  //! Initialize (or reset) an internal root ray 
  static void setInternalRay( const double position[3], 
                              const double direction[3] );

  //! Initialize (or reset) an internal root ray
  static void setInternalRay( const Ray& ray );

  //! Change the internal ray direction (without changing its location)
  static void changeInternalRayDirection( const double direction[3] );

  //! Change the internal ray direction( without changing its location)
  static void changeInternalRayDirection( const double x_direction,
                                          const double y_direction,
                                          const double z_direction );

  //! Get the internal root ray position
  static const double* getInternalRayPosition();

  //! Get the internal root ray direction
  static const double* getInternalRayDirection();

  //! Get the cell containing the internal root ray position
  static ModuleTraits::InternalCellHandle findCellContainingInternalRay();

  //! Get the distance from the internal root ray pos. to the nearest boundary
  static double fireInternalRay();

  //! Advance the internal root ray to the next boundary
  static void advanceInternalRayToCellBoundary();

  //! Advance the internal root ray a substep
  static void advanceInternalRayBySubstep( const double substep_distance );
  
  //! Destructor
  ~Root()
  {/* ... */}

private:
  
  // Constructor
  Root();

  // Get the cell
  static TGeoVolume* getVolumePtr( 
                             const ModuleTraits::InternalCellHandle& cell_id );

  // Find the node containing the point
  static TGeoNode* findNodeContainingPoint( const Ray& ray );

  // Reset the internal ray set flag
  static void internalRayUnset();

  // Set the internal ray set flag
  static void internalRaySet();

  // Root TGeoManager
  static TGeoManager* s_manager;

  // Root cell id to uid map
  static std::unordered_map<ModuleTraits::InternalCellHandle,Int_t>
  s_cell_id_uid_map;

  // Internal ray set
  static std::vector<int> s_internal_ray_set;

  // Root void material name
  static std::string s_void_material_name;

  // Root terminal material name
  static std::string s_terminal_material_name;
  
  // Root material property name
  static std::string s_material_property_name;
};

//! The invalid root geometry error
class InvalidRootGeometry : public std::runtime_error
{

public:

  InvalidRootGeometry( const std::string& what_arg )
    : std::runtime_error( what_arg )
  { /* ... */ }
};

// Get the material property name
inline const std::string& Root::getMaterialPropertyName()
{
  return s_material_property_name;
}

// Get the void material property name
inline const std::string& Root::getVoidMaterialName()
{
  return s_void_material_name;
}

// Get the terminal material property name
inline const std::string& Root::getTerminalMaterialName()
{
  return s_terminal_material_name;
}

// Check if root has been initialized
inline bool Root::isInitialized()
{
  return s_manager != NULL;
}

// Get the cell
inline TGeoVolume* Root::getVolumePtr( 
                              const ModuleTraits::InternalCellHandle& cell_id )
{
  // Make sure root is initialized
  testPrecondition( Root::isInitialized() );
  // Make sure the cell exists
  testPrecondition( Root::doesCellExist( cell_id ) );

  return s_manager->GetVolume( s_cell_id_uid_map.find( cell_id )->second );
}

} // end Geometry namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Geometry_Root_def.hpp"

//---------------------------------------------------------------------------//

#endif // end GEOMETRY_ROOT_HPP

//---------------------------------------------------------------------------//
// end Geometry_Root.hpp
//---------------------------------------------------------------------------//
