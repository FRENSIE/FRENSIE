//---------------------------------------------------------------------------//
//!
//! \file   Geometry_DagMC_def.hpp
//! \author Alex Robinson
//! \brief  DagMC wrapper class template and inline definitions
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_DAGMC_DEF_HPP
#define GEOMETRY_DAGMC_DEF_HPP

// Std Lib Includes
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

// FRENSIE Includes
#include "Utility_DirectionHelpers.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Geometry{

// Get the boundary cell 
/*! \details DagMC geometry are set up so that every surface belongs to
 * exactly two cells. When a ray crosses a boundary surface finding the
 * next cell that will be entered is simply a matter of knowing the current
 * cell and the boundary surface.
 */
inline ModuleTraits::InternalCellHandle
DagMC::getBoundaryCell(
                const ModuleTraits::InternalCellHandle cell_id,
                const ModuleTraits::InternalSurfaceHandle boundary_surface_id )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  // Make sure the cell exists
  testPrecondition( DagMC::doesCellExist( cell_id ) );
  // Make sure the surface exists
  testPrecondition( DagMC::doesSurfaceExist( boundary_surface_id ) );

  moab::EntityHandle current_cell_handle = 
    s_cell_handler->getCellHandle( cell_id );

  moab::EntityHandle boundary_surface_handle = 
    s_surface_handler->getSurfaceHandle( boundary_surface_id );

  moab::EntityHandle boundary_cell_handle =
    DagMC::getBoundaryCellHandle( current_cell_handle, 
                                  boundary_surface_handle );
                      
  return s_cell_handler->getCellId( boundary_cell_handle );
}

// Get the surface normal at a point on the surface
inline void DagMC::getSurfaceNormal( 
                          const ModuleTraits::InternalSurfaceHandle surface_id,
                          const double position[3],
                          double normal[3] )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  // Make sure the surface exists
  testPrecondition( DagMC::doesSurfaceExist( surface_id ) );

  moab::EntityHandle surface_handle = 
    s_surface_handler->getSurfaceHandle( surface_id );

  DagMC::getSurfaceHandleNormal( surface_handle, position, normal );
}

// Get the property values associated with a property name
/*! \details The StringArray must be an array (e.g. std::vector, 
 * Teuchos::Array, etc.) of std::string types. This method is thread safe as 
 * long as enableThreadSupport has been called.
 */
template<typename StringArray>
void DagMC::getPropertyValues( const std::string& property, 
                               StringArray& values )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );

  std::vector<std::string> stored_values;

  DagMC::getPropertyValues( property, stored_values );

  values.resize( stored_values.size() );

  for( unsigned i = 0; i < stored_values.size(); ++i )
    values[i] = stored_values[i];
}

// Get the material ids
/*! \details The set type must be an integer types. This method is thread safe 
 * as long as enableThreadSupport has been called.
 */
template<typename Set>
void DagMC::getMaterialIds( Set& material_ids )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );

  std::vector<std::string> raw_material_ids;

  DagMC::getPropertyValues( DagMC::getMaterialPropertyName(),
                            raw_material_ids );

  // Convert the material names to material ids
  for( unsigned i = 0; i < raw_material_ids.size(); ++i )
  {
    TEST_FOR_EXCEPTION( raw_material_ids[i].find_first_not_of( "0123456789" ) <
                        raw_material_ids[i].size(),
                        InvalidDagMCGeometry,
                        "Error: An invalid material id ("
                        << raw_material_ids[i] << 
                        ") was found! " );
    
    std::istringstream iss( raw_material_ids[i] );

    typename Set::value_type material_id;

    iss >> material_id;

    material_ids.insert( material_id );
  }
}

// Find the cell handle that contains the external ray
inline moab::EntityHandle 
DagMC::findCellHandleContainingExternalRay( const Ray& ray,
                                            const bool boundary_check )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );

  return DagMC::findCellHandleContainingRay( ray.getPosition(),
                                             ray.getDirection(),
                                             boundary_check );
}

// Find the cell that contains the external ray
inline ModuleTraits::InternalCellHandle DagMC::findCellContainingExternalRay(
                                                    const Ray& ray,
                                                    const bool boundary_check )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );

  moab::EntityHandle cell_handle =
    DagMC::findCellHandleContainingExternalRay( ray, boundary_check );

  return s_cell_handler->getCellId( cell_handle );
}

// Find and cache the cell that contains the external ray
inline ModuleTraits::InternalCellHandle 
DagMC::findAndCacheCellContainingExternalRay( const Ray& ray )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  
  moab::EntityHandle cell_handle =
    DagMC::findAndCacheCellHandleContainingRay( ray.getPosition(),
                                                ray.getDirection() );

  // Return the cell that contains the point
  return s_cell_handler->getCellId( cell_handle );
}

// Initialize (or reset) an internal DagMC ray
inline void DagMC::setInternalRay( const Ray& ray, 
                                   const bool cache_start_cell )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );

  DagMC::setInternalRay( ray.getPosition(), 
                         ray.getDirection(), 
                         cache_start_cell );
}

// Initialize (or reset) an internal DagMC ray
inline void DagMC::setInternalRay(
                           const Ray& ray,
                           const ModuleTraits::InternalCellHandle current_cell,
                           const bool cache_start_cell )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  // Make sure the cell exists
  testPrecondition( DagMC::doesCellExist( current_cell ) );
  // Make sure the cell contains the ray
  testPrecondition( DagMC::findCellContainingExternalRay( ray, false ) ==
                    current_cell );
  
  DagMC::setInternalRay( ray.getPosition(), 
                         ray.getDirection(), 
                         current_cell,
                         cache_start_cell );
}

// Change the internal ray direction (without changing its location)
inline void DagMC::changeInternalRayDirection( const double direction[3] )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  // Make sure the direction is valid
  testPrecondition( Utility::validDirection( direction ) );
  // Make sure the ray is set
  testPrecondition( DagMC::isInternalRaySet() );

  DagMC::changeInternalRayDirection( direction[0],
                                     direction[1],
                                     direction[2] );
}

// Get the problem cells
/*! \details The set value type should be a ModuleTraits::InternalCellHandle. 
 * This method is thread safe as long as enableThreadSupport has been called.
 */
template<typename Set>
void DagMC::getCells( Set& cell_set,
                      const bool include_void_cells,
                      const bool include_termination_cells )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );

  moab::Range::const_iterator cell_handle_it = s_cell_handler->begin();

  while( cell_handle_it != s_cell_handler->end() )
  {
    ModuleTraits::InternalCellHandle cell_id = 
      s_cell_handler->getCellId( *cell_handle_it );

    // Check if it is a termination cell
    if( DagMC::isTerminationCell( cell_id ) )
    {
      if( include_termination_cells )
        cell_set.insert( cell_id );
    }

    // Check if it is a void cell
    if( DagMC::isVoidCell( cell_id ) )
    {
      if( include_void_cells )
        cell_set.insert( cell_id );
    }
    else
      cell_set.insert( cell_id );

    ++cell_handle_it;
  }
}

// Get the property values associated with a property name and cell id
/*! \details The key type must be a ModuleTraits::InternalCellHandle. The
 * mapped type must be an array of strings (e.g. std::vector or 
 * Teuchos::Array). This method is thread safe as long as 
 * enableThreadSupport has been called.
 */
template<typename Map>
void DagMC::getCellPropertyValues( const std::string& property,
                                   Map& cell_id_prop_val_map )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  
  std::vector<moab::EntityHandle> cells_with_property;

  // Get all of the cells with the desired property
  try{
    DagMC::getCellsWithProperty( cells_with_property, property );
  }
  EXCEPTION_CATCH_RETHROW( InvalidDagMCGeometry,
                           "Error: Unable to extract cells with property "
                           << property << "!" );

  // Get the property value for each cell
  for( unsigned i = 0u; i < cells_with_property.size(); ++i )
  {
    ModuleTraits::InternalCellHandle cell_id = 
      s_cell_handler->getCellId( cells_with_property[i] );
    
    moab::ErrorCode return_value = 
      s_dagmc->prop_values( cells_with_property[i],
                            property,
                            cell_id_prop_val_map[cell_id] );

    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS, 
			InvalidDagMCGeometry,
			moab::ErrorCodeStr[return_value] );
  }
}

// Get the cell ids with a property value
/*! \details The key type must be a std::string. The mapped type must be
 * an array of ModuleTraits::InternalCellHandle types. This method is thread 
 * safe as long as enableThreadSupport has been called.
 */
template<typename Map>
void DagMC::getCellIdsWithPropertyValue( const std::string& property,
                                         Map& prop_val_cell_id_map )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  
  // Get all of the values for the desired property
  std::vector<std::string> property_values;

  moab::ErrorCode return_value =
    s_dagmc->get_all_prop_values( property, property_values );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS, 
                      InvalidDagMCGeometry,
                      moab::ErrorCodeStr[return_value] );

  // Load the map
  std::vector<moab::EntityHandle> cells;
  
  for( unsigned i = 0u; i < property_values.size(); ++i )
  {
    try{
      DagMC::getCellsWithProperty( cells, property, &property_values[i] );
    }
    EXCEPTION_CATCH_RETHROW( InvalidDagMCGeometry,
                             "Error: Unable to extract cells with property "
                             << property << " and value "
                             << property_values[i] << "!" );
        
    if( cells.size() > 0 )
    {
      std::vector<ModuleTraits::InternalCellHandle>& cell_ids = 
	prop_val_cell_id_map[property_values[i]];
      
      cell_ids.resize( cells.size() );
      
      // Convert the entity handles to cell ids
      for( unsigned j = 0u; j < cells.size(); ++j )
	cell_ids[j] = s_cell_handler->getCellId( cells[j] );
      
      cells.clear();
    }
  }
}

// Get the cell material ids
/*! \details The key type must be a ModuleTraits::InternalCellHandle. The
 * mapped type must be an unsigned int. This method is thread safe as long as 
 * enableThreadSupport has been called.
 */
template<typename Map>
void DagMC::getCellMaterialIds( Map& cell_id_mat_id_map )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  
  // Load a map of the cell ids and material names
  std::unordered_map<ModuleTraits::InternalCellHandle,std::vector<std::string> >
    cell_id_mat_name_map;

  try{
    DagMC::getCellPropertyValues( DagMC::getMaterialPropertyName(),
                                  cell_id_mat_name_map );
  }
  EXCEPTION_CATCH_RETHROW( InvalidDagMCGeometry,
                           "Error: Unable to parse the cell material ids!" );

  // Convert the material names to material ids
  std::unordered_map<ModuleTraits::InternalCellHandle,std::vector<std::string> >::const_iterator 
    cell_it = cell_id_mat_name_map.begin();

  while( cell_it != cell_id_mat_name_map.end() )
  {
    TEST_FOR_EXCEPTION( cell_it->second.size() > 1,
                        InvalidDagMCGeometry,
                        "Error: Cell " << cell_it->first << " has multiple "
                        "materials assigned!" );
    
    TEST_FOR_EXCEPTION( 
                    cell_it->second.front().find_first_not_of( "0123456789" ) <
                    cell_it->second.size(),
                    InvalidDagMCGeometry,
                    "Error: Cell " << cell_it->first << " has an invalid "
                    "material id (" << cell_it->second.front() << ")! " );
    
    std::istringstream iss( cell_it->second.front() );

    typename Map::mapped_type material_id;
    
    iss >> material_id;
    
    cell_id_mat_id_map[cell_it->first] = material_id;
    
    ++cell_it;
  }
}

// Get the cell densities
/*! \details The key type must be a ModuleTraits::InternalCellHandle. The
 * mapped type must be a double. Note that void and terminal cells will
 * not be added to the map. This method is thread safe as long as 
 * enableThreadSupport has been called
 */
template<typename Map>
void DagMC::getCellDensities( Map& cell_id_density_map )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  
  // Load a map of the cell ids and density names
  std::unordered_map<ModuleTraits::InternalCellHandle,std::vector<std::string> >
    cell_id_density_name_map;

  try{
    DagMC::getCellPropertyValues( DagMC::getDensityPropertyName(),
                                  cell_id_density_name_map );
  }
  EXCEPTION_CATCH_RETHROW( InvalidDagMCGeometry,
                           "Error: Unable to parse the cell densities!" );

  // Convert the material names to material ids
  std::unordered_map<ModuleTraits::InternalCellHandle,std::vector<std::string> >::const_iterator 
    cell_it = cell_id_density_name_map.begin();

  while( cell_it != cell_id_density_name_map.end() )
  {
    TEST_FOR_EXCEPTION( cell_it->second.size() > 1,
                        InvalidDagMCGeometry,
                        "Error: Cell " << cell_it->first << " has multiple "
                        "densities assigned!" );

    TEST_FOR_EXCEPTION( 
                  cell_it->second.front().find_first_not_of( "-.0123456789" ) <
                  cell_it->second.size(),
                  InvalidDagMCGeometry,
                  "Error: Cell " << cell_it->first << " has an invalid "
                  "density (" << cell_it->second.front() << ")! " );
    
    std::istringstream iss( cell_it->second.front() );

    typename Map::mapped_type density;
    
    iss >> density;
    
    cell_id_density_map[cell_it->first] = density;
    
    ++cell_it;
  }
}

// Get the cell estimator data
/*! \details The key type must be an integer type. The mapped type must be
 * tuple (e.g. Utility::Trip or std::tuple) of a std::string, std::string
 * and an array of ModuleTraits::InternalCellHandle types (e.g.
 * Utility::Trip<std::string,std::string,std::vector<ModuleTraits::InternalCellHandle> >).
 * The first string value will store the estimator type, the second
 * string will store the particle type and the array will store all of the
 * assigned cells. This method is thread safe as long as enableThreadSupport 
 * has been called.
 */
template<typename Map>
void DagMC::getCellEstimatorData( Map& estimator_id_data_map )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );

  // Load the estimator property cell id map
  typedef std::unordered_map<std::string,std::vector<ModuleTraits::InternalCellHandle> > 
    EstimatorPropCellIdMap;
  
  EstimatorPropCellIdMap estimator_prop_cell_id_map;

  try{
    DagMC::getCellIdsWithPropertyValue( DagMC::getEstimatorPropertyName(),
                                        estimator_prop_cell_id_map );
  }
  EXCEPTION_CATCH_RETHROW( InvalidDagMCGeometry,
                           "Error: Unable to parse the cell estimator data!" );

  EstimatorPropCellIdMap::const_iterator estimator_it = 
    estimator_prop_cell_id_map.begin();

  // Loop through all of the cell estimators and extract their information
  while( estimator_it != estimator_prop_cell_id_map.end() )
  {
    typename Map::key_type id;
    std::string estimator_type;
    std::string particle_type;
    
    try{
      DagMC::extractEstimatorPropertyValues( estimator_it->first,
                                             id,
                                             estimator_type,
                                             particle_type );
    }
    EXCEPTION_CATCH_RETHROW( InvalidDagMCGeometry,
                             "Error: an invalid estimator specification "
                             "was found in the .sat file ("
                             << estimator_it->first << ")! "
                             "The correct format is id.type.ptype." );

    // Make sure the id is valid
    TEST_FOR_EXCEPTION( estimator_id_data_map.find( id ) !=
                        estimator_id_data_map.end(),
                        InvalidDagMCGeometry,
                        "Error: estimator id " << id << " is used multiple "
                        "times in the .sat file!" );

    // Make sure the estimator type is valid
    TEST_FOR_EXCEPTION( !DagMC::isCellEstimatorTypeValid( estimator_type ),
                        InvalidDagMCGeometry,
                        "Error: cell estimator " << id << " has estimator "
                        "type " << estimator_type << " specified in the .sat "
                        "file, which is an invalid type!" );
                        
    // Make sure at least one cell has been assigned to the estimator
    TEST_FOR_EXCEPTION( estimator_it->second.size() == 0,
                        InvalidDagMCGeometry,
                        "Error: estimator " << id << " has no cells "
                        "assigned!" );

    // Add the estimator info to the map
    typename Map::mapped_type& estimator_data_tuple = 
      estimator_id_data_map[id];

    estimator_data_tuple.first = estimator_type;
    estimator_data_tuple.second = particle_type;
    
    estimator_data_tuple.third.assign( estimator_it->second.begin(),
                                       estimator_it->second.end() );
    
    ++estimator_it;
  }
}

// Get the problem surfaces
/*! \details The set value type should be a 
 * ModuleTraits::InternalSurfaceHandle. This method is thread safe as long as 
 * enableThreadSupport has been called.
 */
template<typename Set>
void DagMC::getSurfaces( Set& surface_set )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  
  moab::Range::const_iterator surface_handle_it = s_surface_handler->begin();

  while( surface_handle_it != s_surface_handler->end() )
  {
    ModuleTraits::InternalCellHandle surface_id = 
      s_surface_handler->getSurfaceId( *surface_handle_it );

    surface_set.insert( surface_id );

    ++surface_handle_it;
  }
}

// Get the property values associated with a property name and surface id
/*! \details The key type must be a ModuleTraits::InternalSurfaceHandle. The
 * mapped type must be an array of strings (e.g. std::vector or 
 * Teuchos::Array). This method is thread safe as long as 
 * enableThreadSupport has been called.
 */
template<typename Map>
void DagMC::getSurfacePropertyValues( const std::string& property,
                                      Map& surface_id_prop_val_map )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  
  std::vector<moab::EntityHandle> surfaces_with_property;

  // Get all of the surfaces with the desired property
  try{
    DagMC::getSurfacesWithProperty( surfaces_with_property, property );
  }
  EXCEPTION_CATCH_RETHROW( InvalidDagMCGeometry,
                           "Error: Unable to extract surfaces with property "
                           << property << "!" );
  
  // Get the property value for each surface
  for( unsigned i = 0u; i < surfaces_with_property.size(); ++i )
  {
    ModuleTraits::InternalSurfaceHandle surface_id = 
      s_surface_handler->getSurfaceId( surfaces_with_property[i] );
    
    moab::EntityHandle return_value = 
      s_dagmc->prop_values( surfaces_with_property[i],
                            property,
                            surface_id_prop_val_map[surface_id] );

    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS, 
			InvalidDagMCGeometry,
			moab::ErrorCodeStr[return_value] );
  }
}

// Get the surface ids with a property value
/*! \details The key type must be a std::string. The mapped type must be
 * an array of ModuleTraits::InternalSurfaceHandle types. This method is 
 * thread safe as long as enableThreadSupport has been called.
 */
template<typename Map>
void DagMC::getSurfaceIdsWithPropertyValue( const std::string& property,
                                            Map& prop_val_surface_id_map )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  
  // Get all of the values for the desired property
  std::vector<std::string> property_values;

  moab::ErrorCode return_value =
    s_dagmc->get_all_prop_values( property, property_values );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS, 
                      InvalidDagMCGeometry,
                      moab::ErrorCodeStr[return_value] );

  // Load the map
  std::vector<moab::EntityHandle> surfaces;
  
  for( unsigned i = 0u; i < property_values.size(); ++i )
  {
    return_value = s_dagmc->entities_by_property( property,
                                                  surfaces,
                                                  2,
                                                  &property_values[i] );

    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                        InvalidDagMCGeometry,
                        moab::ErrorCodeStr[return_value] );
    
    if( surfaces.size() > 0 )
    {
      std::vector<ModuleTraits::InternalSurfaceHandle>& surface_ids = 
	prop_val_surface_id_map[property_values[i]];
      
      surface_ids.resize( surfaces.size() );
      
      // Convert the entity handles to surface ids
      for( unsigned j = 0u; j < surfaces.size(); ++j )
	surface_ids[j] = s_surface_handler->getSurfaceId( surfaces[j] );
      
      surfaces.clear();
    }
  }
}

// Get the surface estimator data
/*! \details The key type must be an integer type. The mapped type must be
 * tuple (e.g. Utility::Trip or std::tuple) of a std::string, std::string
 * and an array of ModuleTraits::InternalSurfaceHandle types (e.g.
 * Utility::Trip<std::string,std::string,std::vector<ModuleTraits::InternalSurfaceHandle> >).
 * The first string value will store the estimator type, the second
 * string will store the particle type and the array will store all of the
 * assigned surfaces. This method is thread safe as long as enableThreadSupport
 * has been called.
 */
template<typename Map>
void DagMC::getSurfaceEstimatorData( Map& estimator_id_data_map )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  
  // Load the estimator property surface id map
  typedef std::unordered_map<std::string,std::vector<ModuleTraits::InternalSurfaceHandle> > 
    EstimatorPropSurfaceIdMap;
  
  EstimatorPropSurfaceIdMap estimator_prop_surface_id_map;

  try{
    DagMC::getSurfaceIdsWithPropertyValue( DagMC::getEstimatorPropertyName(),
                                           estimator_prop_surface_id_map );
  }
  EXCEPTION_CATCH_RETHROW( InvalidDagMCGeometry,
                           "Error: Unable to parse the surface estimator "
                           "properties!" );

  EstimatorPropSurfaceIdMap::const_iterator estimator_it = 
    estimator_prop_surface_id_map.begin();

  // Loop through all of the surface estimators and extract their information
  while( estimator_it != estimator_prop_surface_id_map.end() )
  {
    typename Map::key_type id;
    std::string estimator_type;
    std::string particle_type;

    try{
      DagMC::extractEstimatorPropertyValues( estimator_it->first,
                                             id,
                                             estimator_type,
                                             particle_type );
    }
    EXCEPTION_CATCH_RETHROW( InvalidDagMCGeometry,
                             "Error: an invalid estimator specification "
                             "was found in the .sat file!" );

    // Make sure the id is valid
    TEST_FOR_EXCEPTION( estimator_id_data_map.find( id ) !=
                        estimator_id_data_map.end(),
                        InvalidDagMCGeometry,
                        "Error: estimator id " << id << " is used multiple "
                        "times in the .sat file!" );

    // Make sure the estimator type is valid
    TEST_FOR_EXCEPTION( !DagMC::isSurfaceEstimatorTypeValid( estimator_type ),
                        InvalidDagMCGeometry,
                        "Error: surface estimator " << id << " has estimator "
                        "type " << estimator_type << " specified in the .sat "
                        "file, which is an invalid type!" );
                        
    // Make sure at least one surface has been assigned to the estimator
    TEST_FOR_EXCEPTION( estimator_it->second.size() == 0,
                        InvalidDagMCGeometry,
                        "Error: estimator " << id << " has no surfaces "
                        "assigned!" );

    // Add the estimator info to the map
    typename Map::mapped_type& estimator_data_tuple = 
      estimator_id_data_map[id];

    estimator_data_tuple.first = estimator_type;
    estimator_data_tuple.second = particle_type;
    
    estimator_data_tuple.third.assign( estimator_it->second.begin(),
                                       estimator_it->second.end() );

    ++estimator_it;
  }
}

// Get the found cell cache
/*! \details The set type must be a Geometry::ModuleTraits::InternalCellHandle
 * type. This method is thread safe as long as enableThreadSupport
 * has been called.
 */
template<typename Set>
void DagMC::getFoundCellCache( Set& cached_cells )
{
  std::unordered_set<moab::EntityHandle>::const_iterator
    cached_cell_it = s_found_cell_cache.begin();

  while( cached_cell_it != s_found_cell_cache.end() )
  {
    cached_cells.insert( s_cell_handler->getCellId( *cached_cell_it ) );
    
    ++cached_cell_it;
  }
}

} // end Geometry namespace

#endif // end GEOMETRY_DAGMC_DEF_HPP

//---------------------------------------------------------------------------//
// end Geometry_DagMC_def.hpp
//---------------------------------------------------------------------------//
