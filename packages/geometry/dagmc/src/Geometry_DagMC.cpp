//---------------------------------------------------------------------------//
//!
//! \file   Geometry_DagMC.cpp
//! \author Alex Robinson
//! \brief  DagMC wrapper class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <exception>
#include <unordered_set>

// FRENSIE Includes
#include "Geometry_DagMC.hpp"
#include "Utility_DirectionHelpers.hpp"
#include "Utility_GlobalOpenMPSession.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Geometry{

// Initialize static member data
moab::DagMC* DagMC::s_dagmc = NULL;
moab::Range DagMC::s_cells;
moab::Range DagMC::s_surfaces;
std::unordered_set<ModuleTraits::InternalCellHandle> 
  DagMC::s_termination_cells;
boost::bimap<ModuleTraits::InternalSurfaceHandle,moab::EntityHandle> 
  DagMC::s_reflecting_surfaces;
std::unordered_set<moab::EntityHandle> DagMC::s_found_cell_cache;
std::vector<DagMC::DagMCRay> DagMC::s_internal_rays;
std::string DagMC::termination_cell_property = "termination.cell";
std::string DagMC::reflecting_surface_property = "reflecting.surface";
std::string DagMC::material_property = "material";
std::string DagMC::density_property = "density";
std::string DagMC::estimator_property = "estimator";
std::string DagMC::surface_current_name = "surface.current";
std::string DagMC::surface_flux_name = "surface.flux";
std::string DagMC::cell_pulse_height_name = "cell.pulse.height";
std::string DagMC::cell_track_length_flux_name = "cell.tl.flux";
std::string DagMC::cell_collision_flux_name = "cell.c.flux";

// Set the termination cell property name
void DagMC::setTerminationCellPropertyName( const std::string& name )
{
  // Make sure the name is valid
  testPrecondition( name.find( "_" ) >= name.size() );
  
  DagMC::termination_cell_property = name;
}

// Get the termination cell property name
const std::string& DagMC::getTerminationCellPropertyName()
{
  return DagMC::termination_cell_property;
}

// Set the reflecting surface property name
void setReflectingSurfacePropertyName( const std::string& name )
{
  // Make sure the name is valid
  testPrecondition( name.find( "_" ) >= name.size() );

  DagMC::reflecting_surface_property = name;
}

// Get the reflecting surface property name
const std::string& getReflectingSurfacePropertyName()
{
  return DagMC::reflecting_surface_property;
}

// Set the material property name
void DagMC::setMaterialPropertyName( const std::string& name )
{
  // Make sure the name is valid
  testPrecondition( name.find( "_" ) >= name.size() );
  
  DagMC::material_property = name;
}

// Get the material property name
const std::string& DagMC::getMaterialPropertyName()
{
  return DagMC::material_property;
}

// Set the density property name
void DagMC::setDensityPropertyName( const std::string& name )
{
  // Make sure the name is valid
  testPrecondition( name.find( "_" ) >= name.size() );
  
  DagMC::density_property = name;
}

// Get the density property name
const std::string& DagMC::getDensityPropertyName()
{
  return DagMC::density_property;
}

// Set the estimator property name
void DagMC::setEstimatorPropertyName( const std::string& name )
{
  // Make sure the name is valid
  testPrecondition( name.find( "_" ) >= name.size() );
  
  DagMC::estimator_property = name;
}

// Get the estimator property name
const std::string& DagMC::getEstimatorPropertyName()
{
  return DagMC::estimator_property;
}

// Set the surface current name
void DagMC::setSurfaceCurrentName( const std::string& name )
{
  // Make sure the name is valid
  testPrecondition( name.find( "_" ) >= name.size() );
  
  DagMC::surface_current_name = name;
}

// Get the surface current name
const std::string& DagMC::getSurfaceCurrentName()
{
  return DagMC::surface_current_name;
}

// Set the surface flux name
void DagMC::setSurfaceFluxName( const std::string& name )
{
  // Make sure the name is valid
  testPrecondition( name.find( "_" ) >= name.size() );

  DagMC::surface_flux_name = name;
}

// Get the surface flux name
const std::string& DagMC::getSurfaceFluxName()
{
  return DagMC::surface_flux_name;
}

// Set the cell pulse height name
void DagMC::setCellPulseHeightName( const std::string& name )
{
  // Make sure the name is valid
  testPrecondition( name.find( "_" ) >= name.size() );

  DagMC::cell_pulse_height_name = name;
}

// Get the cell pulse height name
const std::string& DagMC::getCellPulseHeightName()
{
  return DagMC::cell_pulse_height_name;
}

// Set the cell track-length flux name
void DagMC::setCellTrackLengthFluxName( const std::string& name )
{
  // Make sure the name is valid
  testPrecondition( name.find( "_" ) >= name.size() );
  
  DagMC::cell_track_length_flux_name = name;
}

// Get the cell pulse height name
const std::string& DagMC::getCellTrackLengthFluxName()
{
  return DagMC::cell_track_length_flux_name;
}

// Set the cell collision flux name
void DagMC::setCellCollisionFluxName( const std::string& name )
{
  // Make sure the name is valid
  testPrecondition( name.find( "_" ) >= name.size() );
  
  DagMC::cell_collision_flux_name = name;
}

// Get the cell collision flux name
const std::string& DagMC::getCellCollisionFluxName()
{
  return DagMC::cell_collision_flux_name;
}

// Extract estimator property values
/*! \details An estimator property is assumed to have the form 
 *  id.type.ptype
 */
void DagMC::extractEstimatorPropertyValues( 
						 const std::string& prop_value,
						 unsigned& estimator_id,
						 std::string& estimator_type,
						 std::string& particle_type )
{
  unsigned first_pos = prop_value.find_first_of( "." );
  unsigned last_pos = prop_value.find_last_of( "." );

  TEST_FOR_EXCEPTION( first_pos > prop_value.size(),
                      std::runtime_error,
                      "Error: the observer property " << prop_value <<
                      " found in the .sat file is invalid (the form needs to "
                      "be id.type.ptype)!" );
  TEST_FOR_EXCEPTION( last_pos > prop_value.size(),
                      std::runtime_error,
                      "Error: the observer property " << prop_value <<
                      " found in the .sat file is invalid (the form needs to "
                      "be id.type.ptype)!" );
  TEST_FOR_EXCEPTION( first_pos == last_pos,
                      std::runtime_error,
                      "Error: the observer property " << prop_value <<
                      " found in the .sat file is invalid (the form needs to "
                      "be id.type.ptype)!" );

  std::string id_string = prop_value.substr( 0, first_pos );

  std::istringstream iss( id_string );

  iss >> estimator_id;

  estimator_type = prop_value.substr( first_pos+1, last_pos-first_pos-1 );

  particle_type = prop_value.substr( last_pos+1, prop_value.size()-last_pos-1);
}
	
// Check if the cell estimator type is valid
bool DagMC::isCellEstimatorTypeValid( 
					    const std::string& estimator_type )
{
  return estimator_type.compare(DagMC::cell_pulse_height_name)== 0 ||
    estimator_type.compare(DagMC::cell_track_length_flux_name)== 0 ||
    estimator_type.compare( DagMC::cell_collision_flux_name ) == 0;
}

// Check if the surface estimator type is valid
bool DagMC::isSurfaceEstimatorTypeValid( 
					    const std::string& estimator_type )
{
  return estimator_type.compare( DagMC::surface_flux_name ) == 0 ||
    estimator_type.compare( DagMC::surface_current_name ) == 0;
}

// Check if the estimator type is valid
bool DagMC::isEstimatorTypeValid( const std::string& estimator_type )
{
  return DagMC::isCellEstimatorTypeValid( estimator_type ) ||
    DagMC::isSurfaceEstimatorTypeValid( estimator_type );
}

// Check if the particle type is valid
bool DagMC::isParticleTypeValid( const std::string& particle_type )
{
  return particle_type.compare( "n" ) == 0 ||
    particle_type.compare( "p" ) == 0 ||
    particle_type.compare( "e" ) == 0;
}

// Get all of the properties
void DagMC::getPropertyNames( std::vector<std::string>& properties )
{
  properties.clear();
  properties.resize( 5 );

  properties[0] = DagMC::termination_cell_property;
  properties[1] = DagMC::reflecting_surface_property;
  properties[2] = DagMC::material_property;
  properties[3] = DagMC::density_property;
  properties[4] = DagMC::estimator_property;
}

// validate the properties
  void validatePropertyNames( const std::vector<std::string>& properties,
                              std::ostream& os_warn )
{
  // Get the valid property names
  std::vector<std::string> valid_properties;
  DagMC::getPropertyNames( valid_properties );

  // Record any invalid property names
  std::string invalid_properties;
  
  for( unsigned i = 0; i < properties; ++i )
  {
    bool valid_property = false;

    for( unsigned j = 0; j < valid_properties.size(); ++j )
    {
      if( properties[i] == valid_properties[j] )
      {
        valid_property = true;
        
        break;
      }
    }

    if( !valid_property )
    {
      if( invalid_properties.size() > 0 )
        invalid_properties += ", ";
      
      invalid_properties += properties[i];
    }
  }

  os_warn << "Warning: Unknown properties were detected in the DagMC " <<
          << "geometry! Here are the unknown properties: "
          << invalid_properties << std::endl;
}

// Check if DagMC has been initialized
bool DagMC::isInitialized()
{
  return s_dagmc != NULL;
}

// Initialize the DagMC geometry manager
void DagMC::initialize( const std::string& filename, 
                        const double facet_tol,
                        std::ostream& os_warn )
{
  // Make sure that the file name is valid
  testPrecondition( filename.size() > 0 );
  testPrecondition( filename.find(".sat")< filename.size() ||
		    filename.find(".h5m") < filename.size() );
  // Make sure that the facet tolerance is valid
  testPrecondition( facet_tol >= 0.0 );

  // Load the geometry
  moab::ErrorCode return_value = 
    s_dagmc->load_file( filename.c_str(), facet_tol );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      InvalidDagMCGeometry,
                      moab::ErrorCodeStr[return_value] );

  // Initialize the OBB Tree
  raturn_value = s_dagmc->init_OBBTree();

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS, 
		      InvalidDagMCGeometry,
		      moab::ErrorCodeStr[return_value] );

  // Detect and validate the properties in the geometry
  {
    std::vector<std::string> detected_property_names;
    
    return_value = s_dagmc->detect_available_props( detected_property_names );

    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS, 
                        InvalidDagMCGeometry,
                        moab::ErrorCodeStr[return_value] );

    try{
      DagMC::validatePropertyNames( detected_property_names, os_warn );
    }
    EXCEPTION_CATCH_RETHROW( InvalidDagMCGeometry,
                             "Error: Could not initialize the DagMC "
                             "geometry!" );
  }
  
  // Parse the properties
  {
    std::vector<std::string> properties;

    DagMC::getPropertyNames( properties );
    
    return_value = s_dagmc->parse_properties( properties );

    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                        InvalidDagMCGeometry,
                        moab::ErrorCodeStr[return_value] );
  }
                                
  // Get all of the problem cells
  {
    moab::Interface* moab_instance = s_dagmc->moab_instance();
  
    const int three = 3;
    const void* const three_val[] = {&three};
  
    moab::Tag geom_tag = s_dagmc->geom_tag();
  
    moab::ErrorCode return_value = 
      moab_instance->get_entities_by_type_and_tag( 0, 
                                                   moab::MBENTITYSET,
                                                   &geom_tag,
                                                   three_val,
                                                   1,
                                                   DagMC::s_cells );
    
    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                        InvalidDagMCGeometry,
                        moab::ErrorCodeStr[return_value] );
  }

  // Get all of the problem surfaces
  {
    moab::Interface* moab_instance = s_dagmc->moab_instance();

    const int two = 2;
    const void* const two_val[] = {&two};
        
    moab::Tag geom_tag = s_dagmc->geom_tag();
  
    moab::ErrorCode return_value = 
      moab_instance->get_entities_by_type_and_tag( 0, 
                                                   moab::MBENTITYSET,
                                                   &geom_tag,
                                                   two_val,
                                                   1,
                                                   DagMC::s_surfaces );
    
    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                        InvalidDagMCGeometry,
                        moab::ErrorCodeStr[return_value] );
  }

  // Get the termination cells
  {
    std::vector<moab::EntityHandle> cells_with_property;

    try{
      DagMC::getCellsWithProperty( cells_with_property,
                                   DagMC::getTerminationCellPropertyName() );
    }
    EXCEPTION_CATCH_RETHROW( InvalidDagMCGeometry,
                             "Error: Unable to parse the termination cells." );

    for( unsigned i = 0; i < cells_with_property.size(); ++i )
      s_termination_cells.insert( DagMC::getCellId( cells_with_property[i] ) );

    // Make sure that at least one termination cell has been set
    TEST_FOR_EXCEPTION( s_termination_cells.size() == 0,
                        InvalidDagMCGeometry,
                        "Error: At least one termination cell must be set!" );
  }

  // Get the reflecting surfaces
  {
    std::vector<moab::EntityHandle> surfaces_with_property;
    
    try{
      DagMC::getSurfacesWithProperty(
                                   surfaces_with_property,
                                   DagMC::getReflectingSurfacePropertyName() );
    }
    EXCEPTION_CATCH_RETHROW( InvalidDagMCGeometry,
                             "Error: Unable to parse the reflecting "
                             "surfaces!" );

    for( unsigned i = 0; i < surfaces_with_property.size(); ++i )
    {
      ModuleTraits::InternalSurfaceHandle surface_id = 
        DagMC::getSurfaceId( surfaces_with_property[i] );
      
      s_reflecting_surfaces.left[surface_id] = surfaces_with_property[i];
    }
  }
}

// Enable thread support
void DagMC::enableThreadSupport( const unsigned num_threads )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  // Make sure the number of threads is valid
  testPrecondition( num_threads > 0 );

  // Create an internal ray for each thread
  s_internal_rays.resize( num_threads );
}

// Extract estimator property values
void DagMC::extractEstimatorPropertyValues( const std::string& prop_value,
                                            unsigned& estimator_id,
                                            std::string& estimator_type,
                                            std::string& particle_type )
{
  unsigned first_pos = prop_value.find_first_of( "." );
  unsigned last_pos = prop_value.find_last_of( "." );

  // Make sure the estimator property format is valid
  TEST_FOR_EXCEPTION( first_pos > prop_value.size(),
                      std::runtime_error,
                      "Error: the estimator property " << prop_value <<
                      " found in the .sat file is invalid (the form needs to "
                      "be id.type.ptype)!" );
  TEST_FOR_EXCEPTION( last_pos > prop_value.size(),
                      std::runtime_error,
                      "Error: the estimator property " << prop_value <<
                      " found in the .sat file is invalid (the form needs to "
                      "be id.type.ptype)!" );
  TEST_FOR_EXCEPTION( first_pos == last_pos,
                      std::runtime_error,
                      "Error: the estimator property " << prop_value <<
                      " found in the .sat file is invalid (the form needs to "
                      "be id.type.ptype)!" );

  std::string id_string = prop_value.substr( 0, first_pos );

  std::istringstream iss( id_string );

  iss >> estimator_id;

  estimator_type = prop_value.substr( first_pos+1, last_pos-first_pos-1 );

  // Make sure the estimator type is valid
  TEST_FOR_EXCEPTION( !DagMC::isValidEstimatorType( estimator_type ),
                      InvalidDagMCGeometry,
                      "Error: estimator " << id << " has an invalid estimator "
                      "type (" << estimator_type << ") specified in the .sat "
                      "file!" );

  particle_type = prop_value.substr( last_pos+1, prop_value.size()-last_pos-1);

  // Make sure the particle type is valid
  TEST_FOR_EXCEPTION( !DagMC::isParticleTypeValid( particle_type ),
                      InvalidDagMCGeometry,
                      "Error: estimator " << id << " has particle type "
                      << particle_type << " specified in the .sat file, "
                      "which is an invalid particle type (choose n, p or "
                      "e)!" );
}

// Check if a cell exists
bool DagMC::doesCellExist( const ModuleTraits::InternalCellHandle cell_id )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  
  return DagMC::getCellHandle() != 0;
}

// Check if the surface exists
bool DagMC::doesSurfaceExist( 
                         const ModuleTraits::InternalSurfaceHandle surface_id )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  
  return DagMC::getSurfaceHandle() != 0;
}

// Get the cell volume
double DagMC::getCellVolume( const ModuleTraits::InternalCellHandle cell_id )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  // Make sure the cell exists
  testPrecondition( DagMC::doesCellExist( cell_id ) );

  moab::EntityHandle cell_handle = DagMC::getCellHandle( cell_id );

  double volume = 0.0;

  moab::ErrorCode return_value = 
    s_dagmc->measure_volume( cell_handle, volume );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
		      InvalidDagMCGeometry,
		      moab::ErrorCodeStr[return_value] );

  TEST_FOR_EXCEPTION( volume <= 0.0,
                      InvalidDagMCGeometry,
                      "Error: an invalid volume was calculated for cell "
                      << cell_id << "!" );

  return volume;
}

// Get the surface area
double DagMC::getSurfaceArea( 
                        const ModuleTraits::InternalSurfaceHandle surface_id )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  // Make sure the cell exists
  testPrecondition( DagMC::doesSurfaceExist( surface_id ) );

  moab::EntityHandle surface_handle = DagMC::getSurfaceHandle( surface_id );

  double surface_area = 0.0;

  moab::ErrorCode return_value = 
    s_dagmc->measure_area( surface_handle, surface_area );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
		      InvalidDagMCGeometry,
		      moab::ErrorCodeStr[return_value] );

  TEST_FOR_EXCEPTION( surface_area <= 0.0,
                      InvalidDagMCGeometry,
                      "Error: an invalid surface area was calculated for "
                      "surface " << surface_id << "!" );

  return surface_area;
}

// Check if the cell is a termination cell
bool DagMC::isTerminationCell( const ModuleTraits::InternalCellHandle cell_id )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  // Make sure the cell exists
  testPrecondition( DagMC::doesCellExist( cell_id ) );

  return s_termination_cells.find( cell_id ) !=
    s_termination_cells.end();
}

// Check if the cell is a void cell
bool DagMC::isVoidCell( const ModuleTraits::InternalCellHandle cell_id )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  // Make sure the cell exists
  testPrecondition( DagMC::doesCellExist( cell_id ) );

  moab::EntityHandle cell_handle = DagMC::getCellHandle( cell_id );
  
  return !s_dagmc->has_prop( *cell_handle_it,
                             DagMC::getMaterialPropertyName() );
}

// Check if the surface is a reflecting surface
bool DagMC::isReflectingSurface( 
                        const ModuleTraits::InternalSurfaceHandle surface_id )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  // Make sure the surface exists
  testPrecondition( DagMC::doesSurfaceExist( surface_id ) );

  return s_reflecting_surfaces.left.find( surface_id ) !=
    s_reflecting_surfaces.left.end();
}

// Get the point location w.r.t. a given cell
PointLocation DagMC::getPointLocation( 
                             const Ray& ray,
                             const ModuleTraits::InternalCellHandle& cell_id )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  // Make sure the cell exists
  testPrecondition( DagMC::doesCellExist( cell_id ) );
  
  moab::EntityHandle cell_handle = DagMC::getCellHandle( cell_id );

  try{
    return DagMC::getPointLocation( ray.getPosition(),
                                    ray.getDirection(),
                                    cell_handle );
  }
  EXCEPTION_CATCH_RETHROW( InvalidDagMCGeometry,
                           "Error: Could not determing the location of the "
                           "ray with respect to cell " 
                           << cell_id << "! Here are the details...\n"
                           "Ray: " << ray  );
}

// Get the point location w.r.t. a given cell
PointLocation DagMC::getPointLocation( const double position[3],
                                       const double direction[3],
                                       const moab::EntityHandle& cell_handle )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  // Make sure the direction is valid
  testPrecondition( DagMC::validDirection( direction ) );
  
  int test_result;

  moab::DagMC::RayHistory ray_history;

  moab::ErrorCode return_value = s_dagmc->point_in_volume( cell_handle,
                                                           position,
                                                           test_result,
                                                           direction );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
		      InvalidDagMCGeometry,
		      moab::ErrorCodeStr[return_value] );

  switch( test_result )
  {
  case -1: 
    return POINT_ON_CELL;
  case 0:
    return POINT_OUTSIDE_CELL;
  case 1:
    return POINT_INSIDE_CELL;
  }
}

// Get the boundary cell 
moab::EntityHandle
DagMC::getBoundaryCell( const moab::EntityHandle cell_handle,
                        const moab::EntityHandle boundary_surface_handle )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );

  moab::EntityHandle boundary_cell_handle;

  moab::ErrorCode return_value = s_dagmc->next_vol( boundary_surface_handle,
                                                    current_cell_handle,
                                                    boundary_cell_handle );
    
  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
		      InvalidDagMCGeometry,
		      moab::ErrorCodeStr[return_value] );

  TEST_FOR_EXCEPTION( boundary_cell_handle == 0,
		      InvalidDagMCGeometry,
		      "Error: Could not find the boundary cell! "
                      " Here are the details...\n"
                      "Current cell: " 
                      << DagMC::getCellId( current_cell_handle ) << "\n"
                      "Boundary Surface: " 
                      << DagMC::getSurfaceId( boundary_surface_handle ) );
}

// Get the boundary cell 
/*! \details DagMC geometry are set up so that every surface belongs to
 * exactly two cells. When a ray crosses a boundary surface finding the
 * next cell that will be entered is simply a matter of knowing the current
 * cell and the boundary surface.
 */
ModuleTraits::InternalCellHandle
getBoundaryCell(
                const ModuleTraits::InternalCellHandle cell_id,
                const ModuleTraits::InternalSurfaceHandle boundary_surface_id )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  // Make sure the cell exists
  testPrecondition( DagMC::doesCellExist( current_cell_id ) );
  // Make sure the surface exists
  testPrecondition( DagMC::doesSurfaceExist( surface_id ) );

  moab::EntityHandle current_cell_handle = 
    DagMC::getCellHandle( current_cell_id );

  moab::EntityHandle boundary_surface_handle = 
    DagMC::getSurfaceHandle( boundary_surface_id );

  moab::EntityHandle boundary_cell_handle =
    DagMC::getBoundaryCell( current_cell_handle, boundary_surface_handle );
                      
  return DagMC::getCellId( boundary_cell_handle );
}

// Get the surface normal at a point on the surface
void getSurfaceNormal( const moab::EntityHandle surface_handle,
                       const double position[3],
                       double normal[3] )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );

  moab::ErrorCode return_value = s_dagmc->get_angle( surface_handle,
                                                     position,
                                                     normal );
                                                     
  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
		      InvalidDagMCGeometry,
		      moab::ErrorCodeStr[return_value] );
}

// Get the surface normal at a point on the surface
void DagMC::getSurfaceNormal( 
                          const ModuleTraits::InternalSurfaceHandle surface_id,
                          const double position[3],
                          double normal[3] )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  // Make sure the surface exists
  testPrecondition( DagMC::doesSurfaceExist( surface_id ) );

  moab::EntityHandle surface_handle = DagMC::getSurfaceHandle( surface_id );

  DagMC::getSurfaceNormal( surface_handle, position, normal );
}

// Clear the found cell cache
void DagMC::clearFoundCellCache()
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );

  #pragma omp critical( modify_use_found_cell_cache )
  s_found_cell_cache.clear();
}

// Add cell to found cell cache
void DagMC::addCellToFoundCellCache( const moab::EntityHandle cell_handle )
{
  // Make sure the cell handle is valid
  testPrecondition( cell_handle != 0 );

  #pragma omp critical( modify_use_found_cell_cache )
  s_found_cell_cache.insert( cell_handle );
}

// Check the found cell cache for a cell that contains the point
// Will return 0 if no cell in the cache contains the point
moab::EntityHandle DagMC::checkFoundCellCache( const double position[3],
                                               const double direction[3] )
{
  // Make sure the direction is valid
  testPrecondition( Utility::validDirection( direction ) );
  
  moab::EntityHandle cell_handle = 0;
  
  #pragma omp critical( modify_use_found_cell_cache )
  {
    std::unordered_set<moab::EntityHandle>::const_iterator 
      cached_cell_handle_it = s_found_cell_cache.begin();

    std::unordered_set<moab::EntityHandle>::const_iterator
      cached_cell_handle_end = s_found_cell_cache.end();
  }
  
  while( cached_cell_handle_it != cached_cell_handle_end )
  {
    PointLocation test_point_location;

    try{
      test_point_location = 
        DagMC::getPointLocation( position, 
                                 direction,
                                 *cached_cell_handle_it );
    }
    EXCEPTION_CATCH_RETHROW( InvalidDagMCGeometry,
                             "Error: Could not find the location of the ray "
                             "with respect to cell "
                             << DagMC::getCellId( *cell_handle_it ) <<
                             "! Here are the details...\n"
                             "Ray: " << ray );
    
    if( test_point_location == POINT_INSIDE_CELL )
    {
      cell_handle = *cached_cell_handle_it;
      
      break;
    }
    
    ++cached_cell_handle_it;
  }

  return cell_handle;
}

// Find the cell handle that contains the ray (brute force)
// All of the cells in the geometry will be tested for containment of
// the ray head. This is an order N search.
moab::EntityHandle DagMC::findCellHandleContainingRay( 
                                                   const double position[3],
                                                   const double direction[3] )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  // Make sure the direction is valid
  testPrecondition( Utility::validDirection( direction ) );

  moab::EntityHandle cell_handle = 0;
  
  // Test all of the cells
  moab::Range::const_iterator cell_handle_it = s_cells.begin();
    
  while( cell_handle_it != s_cells.end() )
  {
    PointLocation test_point_location;
    
    try{
      test_point_location = 
        DagMC::getPointLocation( position, direction, *cell_handle_it );
    }
    EXCEPTION_CATCH_RETHROW( InvalidDagMCGeometry,
                             "Error: Could not find the location of the ray "
                             "with respect to cell "
                             << DagMC::getCellId( *cell_handle_it ) <<
                             "! Here are the details...\n"
                             "Position: {"
                             << position[0] << ","
                             << position[1] << ","
                             << position[2] << "}\n"
                             "Direction: {"
                             << direction[0] << ","
                             << direction[1] << ","
                             << direction[2] << "}" );
                             
      
    if( test_point_location == POINT_INSIDE_CELL )
    {
      cell_handle = *cell_handle_it;

      break;
    }
      
      ++cell_handle_it;
  }
  
  // Make sure a cell handle was found
  TEST_FOR_EXCEPTION( cell_handle == 0,
                      InvalidDagMCGeometry,
                      "Error: Could not find a cell that contains the "
                      "requested ray! Here are the details...\n"
                      "Ray position: {" 
                      << position[0] << ","
                      << position[1] << ","
                      << position[2] << "}\n"
                      "Ray direction: {"
                      << direction[0] << ","
                      << direction[1] << ","
                      << direction[2] << "}" );

  return cell_handle;
}

// Find and cache the cell handle that contains the external ray 
moab::EntityHandle DagMC::findAndCacheCellHandleContainingRay( 
                                                    const double position[3],
                                                    const double direction[3] )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  // Make sure the direction is valid
  testPrecondition( Utility::validDirection( direction ) );
  
  // Test the cells in the cache first
  moab::EntityHandle cell_handle = 
    DagMC::checkFoundCellCache( position, direction );

  // Test all of the cells since none of the cached cells contained the ray
  if( cell_handle == 0 )
  {
    cell_handle = DagMC::findCellHandleContainingRay( position, direction );

    // Cache the cell handle
    DagMC::addCellToFoundCellCache( cell_handle );
  }
}

// Find the cell handle that contains the external ray
moab::EntityHandle DagMC::findCellHandleContainingExternalRay( const Ray& ray )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );

  return DagMC::findCellHandleContainingExternalRay( ray.getPosition(),
                                                     ray.getDirection() );
}

// Find the cell that contains the external ray
ModuleTraits::InternalCellHandle DagMC::findCellContainingExternalRay(
                                                               const Ray& ray )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  
  std::vector<ModuleTraits::InternalCellHandle> dummy;

  return DagMC::findCellContainingExternalRay( ray, dummy );
}

// Find the cell that contains the external ray
ModuleTraits::InternalCellHandle DagMC::findCellContainingExternalRay(
                                                               const Ray& ray )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );

  moab::EntityHandle cell_handle =
    DagMC::findCellHandleContainingExternalRay( ray );

  return DagMC::getCellId( *cell_handle_it );
}

// Find and cache the cell that contains the external ray
ModuleTraits::InternalCellHandle DagMC::findAndCacheCellContainingExternalRay(
                                                               const Ray& ray )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  
  moab::EntityHandle cell_handle =
    DagMC::findAndCacheCellHandleContainingRay( ray.getPosition(),
                                                ray.getDirection() );

  // Return the cell that contains the point
  return DagMC::getCellId( cell_handle );
}

// Get the distance from the external ray position to the nearest boundary
/*! \details The cell containing the ray position will be found before firing
 * the ray.
 */
double DagMC::fireExternalRay( 
                            const Ray& ray, 
                            ModuleTraits::InternalSurfaceHandle& surface_hit )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  
  // Find the cell that contains the external ray
  cell_handle = DagMC::findCellHandleContainingExternalRay( ray );

  // Fire the external ray
  return DagMC::fireExternalRay( ray, cell_handle, surface_hit );
}

// Get the distance from the external ray position to the nearest boundary
/*! \details The ray must be contained by the current_cell id.
 */
double DagMC::fireExternalRay(
                          const Ray& ray,
                          const ModuleTraits::InternalCellHandle current_cell,
                          ModuleTraits::InternalSurfaceHandle& surface_hit )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  // Make sure the external cell exists
  testPrecondition( DagMC::doesCellExist( current_cell ) );
  // Make sure the ray is contained by the current cell
  testPrecondition( DagMC::findCellContainingExternalRay( ray ) ==
                    current_cell );
  
  moab::EntityHandle cell_handle = DagMC::getCellHandle( current_cell );

  // Fire the external ray
  return DagMC::fireExternalRay( ray, cell_handle, surface_hit );
}

// Get the distance from the external ray position to the nearest boundary
double DagMC::fireExternalRay( 
                            const Ray& ray,
                            const moab::EntityHandle current_cell_handle,
                            ModuleTraits::InternalSurfaceHandle& surface_hit )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );

  moab::EntityHandle surface_hit_handle;

  double distance_to_surface;
  
  moab::ErrorCode return_value = s_dagmc->ray_fire( current_cell_handle,
                                                    ray.getPosition(),
                                                    ray.getDirection(),
                                                    surface_hit_handle,
                                                    distance_to_surface );

  // Check for a ray misfire which can be caused by a poorly created geometry
  // or by gaps in the surface facets, which can occur for properly created
  // geometries.
  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      DagMCGeometryError,
                      moab::ErrorCodeStr[return_value] );

  TEST_FOR_EXCEPTION( surface_hit_handle == 0,
                      DagMCGeometryError,
                      "Error: DagMC had a ray misfire! Here are the "
                      "details...\nCurrent Cell: "
                      << DagMC::getCellId( current_cell_handle ) << "\n"
                      "Ray: " << ray );

  TEST_FOR_EXCEPTION( distance_to_surface < 0.0,
                      DagMCGeometryError,
                      "Error: DagMC had a ray misfire! Here are the "
                      "details...\nCurrent Cell: "
                      << DagMC::getCellId( current_cell_handle ) << "\n"
                      "Surface Hit: " 
                      << DagMC::getSurfaceId( surface_hit_handle ) << "\n"
                      "Ray: " << ray );

  surface_hit = DagMC::getSurfaceId( surface_hit_handle );

  return distance_to_surface;
}

// Check if the internal ray is set
bool DagMC::isInternalRaySet()
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  
  return DagMC::getInternalRay().isReady();
}

// Initialize (or reset) an internal DagMC ray
void DagMC::setInternalRay( const double position[3],
                            const double direction[3],
                            const bool cache_start_cell )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  // Make sure the direction is valid
  testPrecondition( Utility::validDirection( direction ) );
  // Make sure thread support has been set up correctly
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() <
                    s_internal_rays.size() );

  moab::EntityHandle cell_handle;

  if( cache_start_cell )
  {
    cell_handle = DagMC::findAndCacheCellHandleContainingRay( position,
                                                              direction );
  }
  else
    cell_handle = DagMC::findCellHandleContainingRay( position, direction );

  DagMC::setInternalRay( position, direction, current_cell_handle );
}

// Initialize (or reset) an internal DagMC ray
void DagMC::setInternalRay( 
                          const double position[3],
                          const double direction[3],
                          const ModuleTraits::InternalCellHandle current_cell,
                          const bool cache_start_cell )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  // Make sure the direction is valid
  testPrecondition( Utility::validDirection( direction ) );
  // Make sure the cell exists
  testPrecondition( DagMC::doesCellExist( current_cell ) );
  // Make sure the cell contains the ray
  remember( Ray test_ray( position, direction ) );
  testPrecondition( DagMC::findCellContainingExternalRay( test_ray ) ==
                    current_cell );
  // Make sure thread support has been set up correctly
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() <
                    s_internal_rays.size() );
  
  moab::EntityHandle cell_handle = DagMC::getCellHandle( current_cell );

  if( cache_start_cell )
    DagMC::addCellToFoundCellCache( cell_handle );

  DagMC::setInternalRay( position, direction, cell_handle );
}

// Set an internal DagMC ray
void DagMC::setInternalRay( const double position[3],
                            const double direction[3],
                            const moab::EntityHandle current_cell_handle );
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  // Make sure the direction is valid
  testPrecondition( Utility::validDirection( direction ) );
  
  DagMCRay& dagmc_ray = DagMC::getInternalRay();

  // Set the basic ray
  dagmc_ray.set( position, direction, current_cell_handle );
}

// Initialize (or reset) an internal DagMC ray
void DagMC::setInternalRay( const Ray& ray, const bool cache_start_cell )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );

  DagMC::setInternalRay( ray.getPosition(), ray.getDirection() );
}

// Initialize (or reset) an internal DagMC ray
void setInternalRay( const Ray& ray,
                     const ModuleTraits::InternalCellHandle current_cell,
                     const bool cache_start_cell )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  // Make sure the direction is valid
  testPrecondition( Utility::validDirection( direction ) );
  // Make sure the cell exists
  testPrecondition( DagMC::doesCellExist( current_cell ) );
  // Make sure the cell contains the ray
  testPrecondition( DagMC::findCellContainingExternalRay( ray ) ==
                    current_cell );

  moab::EntityHandle current_cell_handle = 
    DagMC::getCellHandle( current_cell );

  DagMC::setInternalRay( ray.getPosition(), 
                         ray.getDirection(), 
                         current_cell_handle );
}

// Get the internal DagMC ray
DagMCRay& DagMC::getInternalRay()
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  // Make sure thread support has been set up correctly
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() <
                    s_internal_rays.size() );
  
  return s_internal_rays[Utility::GlobalOpenMPSession::getThreadId()];
}

// Change the internal ray direction (without changing its location)
void DagMC::changeInternalRayDirection( const double direction[3] )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  // Make sure the direction is valid
  testPrecondition( Utility::validDirection( direction ) );
  // Make sure the ray is set
  testPrecondition( DagMC::isInternalRaySet() );

  DagMCRay& internal_ray = DagMC::getInternalRay();

  // Change the direction
  internal_ray.changeDirection( direction );
}

// Get the internal DagMC ray position
const double* DagMC::getInternalRayPosition()
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  // Make sure the ray is set
  testPrecondition( DagMC::isInternalRaySet() );
  
  DagMC::getInternalRay().getBasicRay().getPosition();
}

// Get the internal DagMC ray direction
const double* DagMC::getInternalRayDirection()
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  // Make sure the ray is set
  testPrecondition( DagMC::isInternalRaySet() );
  
  DagMC::getInternalRay().getDirection();
}

// Get the cell containing the internal DagMC ray position
ModuleTraits::InternalCellHandle DagMC::findCellContainingInternalRay()
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  // Make sure the ray is set
  testPrecondition( DagMC::isInternalRaySet() );

  return DagMC::getCellId( DagMC::getInternalRay().getCurrentCell() );
}

// Get the distance from the internal DagMC ray pos. to the nearest boundary
double DagMC::fireInternalRay( 
                            ModuleTraits::InternalSurfaceHandle& surface_hit )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  // Make sure the ray is set
  testPrecondition( DagMC::isInternalRaySet() );

  double distance_to_surface;

  DagMCRay& ray = DagMC::getInternalRay();

  // Check if the ray has already been fired
  if( ray.knowsIntersectionSurface() )
  {
    surface_hit = DagMC::getSurfaceId( ray.getIntersectionSurface() );

    distance_to_surface = ray.getDistanceToIntersectionSurface();
  }
  // This is the first time the ray has been fired from this location
  else
  {
    moab::EntityHandle surface_hit_handle;

    double distance_to_surface;
  
    moab::ErrorCode return_value = s_dagmc->ray_fire( current_cell_handle,
                                                      ray.getPosition(),
                                                      ray.getDirection(),
                                                      surface_hit_handle,
                                                      distance_to_surface,
                                                      &ray.getHistory() );

    // Check for a ray misfire which can be caused by a poorly created geometry
    // or by gaps in the surface facets, which can occur for properly created
    // geometries.
    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                        DagMCGeometryError,
                        moab::ErrorCodeStr[return_value] );

    TEST_FOR_EXCEPTION( surface_hit_handle == 0,
                        DagMCGeometryError,
                        "Error: DagMC had a ray misfire! Here are the "
                        "details...\nCurrent Cell: "
                        << DagMC::getCellId( current_cell_handle ) << "\n"
                        "Position: {" 
                        << ray.getPosition()[0] << ","
                        << ray.getPosition()[1] << ","
                        << ray.getPosition()[2] << "}\n"
                        "Direction: {"
                        << ray.getDirection()[0] << "," 
                        << ray.getDirection()[1] << ","
                        << ray.getDirection()[2] << "}" );
    
    TEST_FOR_EXCEPTION( distance_to_surface < 0.0,
                        DagMCGeometryError,
                        "Error: DagMC had a ray misfire! Here are the "
                        "details...\nCurrent Cell: "
                        << DagMC::getCellId( current_cell_handle ) << "\n"
                        "Surface Hit: " 
                        << DagMC::getSurfaceId( surface_hit_handle ) << "\n"
                        "Position: {" 
                        << ray.getPosition()[0] << ","
                        << ray.getPosition()[1] << ","
                        << ray.getPosition()[2] << "}\n"
                        "Direction: {"
                        << ray.getDirection()[0] << "," 
                        << ray.getDirection()[1] << ","
                        << ray.getDirection()[2] << "}" );
    
    surface_hit = DagMC::getSurfaceId( surface_hit_handle );

    // Cache the surface data in the ray
    ray.setIntersectionSurfaceData( surface_hit_handle, distance_to_surface );
  }
    
  return distance_to_surface;
}

// Advance the internal DagMC ray to the next boundary
/*! \details Upon reaching the boundary the internal ray will enter the
 * boundary cell if the boundary surface is not a reflecting surface. The
 * ray will be reflected at the boundary if a reflecting surface is
 * encountered. This method will return true if a reflecting boundary
 * was encountered.
 */
bool DagMC::advanceInternalRayToCellBoundary()
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  // Make sure the ray is set
  testPrecondition( DagMC::isInternalRaySet() );

  bool reflecting_boundary = false;
  
  DagMCRay& ray = DagMC::getInternalRay();

  // Reflect the ray if a reflecting surface is encountered
  if( DagMC::isReflectingSurface( ray.getIntersectionSurface() ) )
  {
    // Advance the ray to the cell boundary and enter the next cell
    ray.advanceToIntersectionSurface( ray.getCurrentCell() );

    // Reflect the ray
    double surface_normal[3];

    DagMC::getSurfaceNormal( ray.getIntersectionSurface(),
                             ray.getPosition(),
                             surface_normal );

    double reflected_direction[3];

    Utility::reflectDirection( ray.getDirection(), 
                               surface_normal, 
                               reflected_direction );

    ray.changeDirection( reflected_direction );

    reflecting_boundary = true;
  }
  // Pass into the next cell if a normal surface is encountered
  else
  {
    moab::EntityHandle next_cell_handle = 
      DagMC::getBoundaryCell( ray.getCurrentCell(),
                              ray.getIntersectionSurface() );
    
    ray.advanceToIntersectionSurface( next_cell_handle );
  }

  // Fire the ray so the new intersection data is set
  ModuleTraits::InternalSurfaceHandle& dummy_surface;
  
  double distance = DagMC::fireInternalRay( dummy_surface );

  return reflecting_boundary;
}

// Advance the internal DagMC ray a substep
/*! \details The substep distance must be less than the distance to the
 * intersection surface.
 */
void DagMC::advanceInternalRayBySubstep( const double substep_distance )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  // Make sure the ray is set
  testPrecondition( DagMC::isInternalRaySet() );
  // Make sure the substep distance is valid
  testPrecondition( substep_distance >= 0.0 );
  testPrecondition(substep_distance < 
                   DagMC::getInternalRay().getDistanceToIntersectionSurface());

  DagMC::getInternalRay().advanceSubstep( substep_distance );  
}

// Get the cell handle
// Note: this will return 0 when the cell doesn't exist
moab::EntityHandle getCellHandle( 
                              const ModuleTraits::InternalCellHandle cell_id )
{
  return s_dagmc->entity_by_id( 3, cell_id );
}

// Get the cell id
ModuleTraits::InternalCellHandle DagMC::getCellId( 
                                         const moab::EntityHandle cell_handle )
{
  return s_dagmc->get_entity_id( cell_handle );
}
  
// Get the surface handle
// Note: this will return 0 when the surface doesn't exist
moab::EntityHandle getSurfaceHandle(
                        const ModuleTraits::InternalSurfaceHandle surface_id )
{
  return s_dagmc->entity_by_id( 2, surface_id );
}

// Get the surface id
ModuleTraits::InternalSurfaceHandle getSurfaceId( 
                                     const moab::EntityHandle surface_handle )
{
  return s_dagmc->get_entity_id( surface_handle );
}

// Get the cells associated with a property name
// Note: If a property value is passed only the cells with both the property
// and value will be returned.
void DagMC::getCellsWithProperty( std::vector<moab::EntityHandle>& cells, 
                                  const std::string& property,
                                  const std::string* property_value )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  
  moab::ErrorCode return_value = 
    s_dagmc->entities_by_property( property, cells, 3, property_value );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS, 
                      InvalidDagMCGeometry,
		      moab::ErrorCodeStr[return_value] );
}

// Get the surfaces associated with a property name
void DagMC::getSurfacesWithProperty( std::vector<moab::EntityHandle>& surfaces,
                                     const std::string& property,
                                     const std::string* property_value )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );

  moab::ErrorCode return_value = 
    s_dagmc->entities_by_property( property, cells, 2, property_value );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS, 
                      InvalidDagMCGeometry,
		      moab::ErrorCodeStr[return_value] );
}

// Check if the surface is a reflecting surface
bool DagMC::isReflectingSurface( const moab::EntityHandle surface_handle )
{
  // Make sure DagMC has been initialized
  testPrecondition( DagMC::isInitialized() );
  
  return s_reflecting_surfaces.right.find( surface_handle ) !=
    s_reflecting_surfaces.right.end();
}

}  // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_DagMC.cpp
//---------------------------------------------------------------------------//
