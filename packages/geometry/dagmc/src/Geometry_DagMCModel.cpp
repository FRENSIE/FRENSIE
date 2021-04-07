//---------------------------------------------------------------------------//
//!
//! \file   Geometry_DagMCModel.cpp
//! \author Alex Robinson
//! \brief  DagMC model class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <exception>
#include <unordered_set>

// FRENSIE Includes
#include "FRENSIE_Archives.hpp" // Must be included first
#include "Geometry_DagMCModel.hpp"
#include "Geometry_StandardDagMCCellHandler.hpp"
#include "Geometry_FastDagMCCellHandler.hpp"
#include "Geometry_StandardDagMCSurfaceHandler.hpp"
#include "Geometry_FastDagMCSurfaceHandler.hpp"
#include "Geometry_DagMCLoggingMacros.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_MOABException.hpp"
#include "Utility_FromStringTraits.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace Geometry{

// Default constructor
DagMCModel::DagMCModel()
  : d_dagmc( NULL )
{ /* ... */ }

// Constructor
DagMCModel::DagMCModel( const DagMCModelProperties& model_properties,
                        const bool suppress_dagmc_output )
  : d_dagmc( NULL ),
    d_cell_handler(),
    d_surface_handler(),
    d_termination_cells(),
    d_reflecting_surfaces(),
    d_model_properties( new DagMCModelProperties( model_properties ) )
{ 
  this->initialize( suppress_dagmc_output );
}

// Destructor
DagMCModel::~DagMCModel()
{
  if( d_dagmc )
    delete d_dagmc;
}
    

// Initialize the model just-in-time
void DagMCModel::initializeJustInTime()
{
  this->initialize( true );
}

// Check if the model has been initialized
bool DagMCModel::isInitialized() const
{
  return d_dagmc != NULL;
}

// Initialize the model
void DagMCModel::initialize( const bool suppress_dagmc_output )
{
  FRENSIE_LOG_PARTIAL_NOTIFICATION( "Loading model "
                                    << d_model_properties->getModelFileNameWithPath()
                                    << " ... " );
  FRENSIE_FLUSH_ALL_LOGS();

  try{
    this->loadDagMCGeometry( suppress_dagmc_output );
  }
  EXCEPTION_CATCH_RETHROW( InvalidDagMCGeometry,
                           "Unable to load DagMC geometry file "
                           << d_model_properties->getModelFileNameWithPath() << "!" );

  // Validate the properties in the geometry
  try{
    this->validatePropertyNames();
  }
  EXCEPTION_CATCH_RETHROW( InvalidDagMCGeometry,
                           "Invalid DagMC geometry properties encountered!" );

  // Parse the properties
  try{
    this->parseProperties();
  }
  EXCEPTION_CATCH_RETHROW( InvalidDagMCGeometry,
                           "Unable to parse the DagMC properties!" );

  // Construct the cell and surface handlers
  try{
    this->constructEntityHandlers();
  }
  EXCEPTION_CATCH_RETHROW( InvalidDagMCGeometry,
                           "Unable to construct the entity handlers!" );

  // Extract the termination cells
  try{
    this->extractTerminationCells();
  }
  EXCEPTION_CATCH_RETHROW( InvalidDagMCGeometry,
                           "Unable to extract the termination cells!" );
  
  // Get the reflecting surfaces
  try{
    this->extractReflectingSurfaces();
  }
  EXCEPTION_CATCH_RETHROW( InvalidDagMCGeometry,
                           "Unable to extract the reflecting surfaces!" );

  FRENSIE_LOG_NOTIFICATION( "done!" );
  FRENSIE_FLUSH_ALL_LOGS();
}

// validate the properties
void DagMCModel::validatePropertyNames() const
{
  // Get the property names in the DagMC geometry
  std::vector<std::string> properties;

  moab::ErrorCode return_value = d_dagmc->detect_available_props( properties );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      InvalidDagMCGeometry,
                      moab::ErrorCodeStr[return_value] );

  // Get the valid property names
  std::vector<std::string> valid_properties;
  d_model_properties->getPropertyNames( valid_properties );

  // Record any invalid property names
  std::string invalid_properties;

  for( size_t i = 0; i < properties.size(); ++i )
  {
    bool valid_property = false;

    for( size_t j = 0; j < valid_properties.size(); ++j )
    {
      if( properties[i] == valid_properties[j] )
      {
        valid_property = true;

        break;
      }
    }

    // Trelis has an internal property names picked that should be ignored
    if( !valid_property && properties[i] != "picked" )
    {
      if( invalid_properties.size() > 0 )
        invalid_properties += ", ";

      invalid_properties += properties[i];
    }
  }

  if( invalid_properties.size() > 0 )
  {
    FRENSIE_LOG_DAGMC_WARNING( "Unknown properties were detected in the "
                               "DagMC geometry! Here are the unknown "
                               "properties: " << invalid_properties );
  }
}

// Load the DagMC geometry file
void DagMCModel::loadDagMCGeometry( const bool suppress_dagmc_output )
{
  // Create a new DagMC instance
  d_dagmc = new moab::DagMC();

  // Check if DagMC output should be suppressed on initialization
  std::streambuf* cout_streambuf, *cerr_streambuf;

  if( suppress_dagmc_output )
  {
    cout_streambuf = std::cout.rdbuf();
    cerr_streambuf = std::cerr.rdbuf();

    std::cout.rdbuf( NULL );
    std::cerr.rdbuf( NULL );
  }

  // Load the geometry
  moab::ErrorCode return_value =
    d_dagmc->load_file( d_model_properties->getModelFileNameWithPath().c_str() );

  // Restore cout and cerr if they were suppressed
  if( suppress_dagmc_output )
  {
    std::cout.rdbuf( cout_streambuf );
    std::cerr.rdbuf( cerr_streambuf );
  }

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      InvalidDagMCGeometry,
                      moab::ErrorCodeStr[return_value] );

  if( suppress_dagmc_output )
  {
    cout_streambuf = std::cout.rdbuf();
    cerr_streambuf = std::cerr.rdbuf();

    std::cout.rdbuf( NULL );
    std::cerr.rdbuf( NULL );
  }

  // Initialize the OBB Tree
  return_value = d_dagmc->init_OBBTree();

  // Restore cout and cerr if they were suppressed
  if( suppress_dagmc_output )
  {
    std::cout.rdbuf( cout_streambuf );
    std::cerr.rdbuf( cerr_streambuf );
  }

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
		      InvalidDagMCGeometry,
		      moab::ErrorCodeStr[return_value] );
}

// Parse the properties
void DagMCModel::parseProperties() const
{
  std::vector<std::string> properties;

  d_model_properties->getPropertyNames( properties );

  moab::ErrorCode return_value = d_dagmc->parse_properties( properties );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      InvalidDagMCGeometry,
                      moab::ErrorCodeStr[return_value] );
}

// Construct the entity handlers
void DagMCModel::constructEntityHandlers()
{
  if( d_model_properties->isFastIdLookupUsed() )
  {
    try{
      d_cell_handler.reset( new FastDagMCCellHandler( d_dagmc ) );

      d_surface_handler.reset( new FastDagMCSurfaceHandler( d_dagmc ) );
    }
    EXCEPTION_CATCH_RETHROW_AS( Utility::MOABException,
                                InvalidDagMCGeometry,
                                "Unable to set up the model entity "
                                "handlers!" );
  }
  else
  {
    try{
      d_cell_handler.reset( new StandardDagMCCellHandler( d_dagmc ) );

      d_surface_handler.reset( new StandardDagMCSurfaceHandler( d_dagmc ) );
    }
    EXCEPTION_CATCH_RETHROW_AS( Utility::MOABException,
                                InvalidDagMCGeometry,
                                "Unable to set up the problem entity "
                                "handlers!" );
  }
}

// Extract the termination cells
void DagMCModel::extractTerminationCells()
{
  std::vector<moab::EntityHandle> cells_with_property;

  try{
    this->getCellsWithProperty(
                        cells_with_property,
                        d_model_properties->getTerminationCellPropertyName() );
  }
  EXCEPTION_CATCH_RETHROW( InvalidDagMCGeometry,
                           "Unable to parse the termination cells!" );

  for( size_t i = 0; i < cells_with_property.size(); ++i )
  {
    d_termination_cells.insert(
                         d_cell_handler->getCellId( cells_with_property[i] ) );
  }

  // Make sure that at least one termination cell has been set
  TEST_FOR_EXCEPTION( d_termination_cells.size() == 0,
                      InvalidDagMCGeometry,
                      "At least one termination cell must be set!" );
}

// Extract the reflecting surfaces
void DagMCModel::extractReflectingSurfaces()
{
  std::vector<moab::EntityHandle> surfaces_with_property;

  try{
    this->getSurfacesWithProperty(
                      surfaces_with_property,
                      d_model_properties->getReflectingSurfacePropertyName() );
  }
  EXCEPTION_CATCH_RETHROW( InvalidDagMCGeometry,
                           "Unable to parse the reflecting surfaces!" );

  // Initialize the reflecting surfaces
  d_reflecting_surfaces.clear();

  for( size_t i = 0; i < surfaces_with_property.size(); ++i )
  {
    EntityId surface_id =
      d_surface_handler->getSurfaceId( surfaces_with_property[i] );

    d_reflecting_surfaces.insert( ReflectingSurfaceIdHandleMap::value_type(
                                     surface_id, surfaces_with_property[i] ) );
  }
}

// Get the model properties
const DagMCModelProperties& DagMCModel::getModelProperties() const
{
  return *d_model_properties;
}

// Check if the model has cell estimator data
bool DagMCModel::hasCellEstimatorData() const
{
  return true;
}

// Check if the model has surface estimator data
bool DagMCModel::hasSurfaceEstimatorData() const
{
  return true;
}

// Get the material ids
void DagMCModel::getMaterialIds( MaterialIdSet& material_ids ) const
{
  std::vector<std::string> raw_material_ids;

  this->getPropertyValues( d_model_properties->getMaterialPropertyName(),
                           raw_material_ids );

  // Convert the material names to material ids
  for( size_t i = 0; i < raw_material_ids.size(); ++i )
  {
    TEST_FOR_EXCEPTION( raw_material_ids[i].find_first_not_of( "0123456789" ) <
                        raw_material_ids[i].size(),
                        InvalidDagMCGeometry,
                        "An invalid material id ("
                        << raw_material_ids[i] <<
                        ") was found! " );

    std::istringstream iss( raw_material_ids[i] );

    typename MaterialIdSet::value_type material_id;

    iss >> material_id;

    material_ids.insert( material_id );
  }
}

// Get the problem cells
void DagMCModel::getCells( CellIdSet& cell_set,
                           const bool include_void_cells,
                           const bool include_termination_cells ) const
{
  moab::Range::const_iterator cell_handle_it = d_cell_handler->begin();

  while( cell_handle_it != d_cell_handler->end() )
  {
    EntityId cell_id =
      d_cell_handler->getCellId( *cell_handle_it );

    // Check if it is a termination cell
    if( this->isTerminationCell( cell_id ) )
    {
      if( include_termination_cells )
        cell_set.insert( cell_id );
    }
    // Check if it is a void cell
    else if( this->isVoidCell( cell_id ) )
    {
      if( include_void_cells )
        cell_set.insert( cell_id );
    }
    // Cell with material
    else
      cell_set.insert( cell_id );

    ++cell_handle_it;
  }
}

// Get the cell material ids
void DagMCModel::getCellMaterialIds( CellIdMatIdMap& cell_id_mat_id_map ) const
{
  // Load a map of the cell ids and material names
  CellIdPropertyValuesMap cell_id_mat_name_map;

  try{
    this->getCellPropertyValues( d_model_properties->getMaterialPropertyName(),
                                 cell_id_mat_name_map );
  }
  EXCEPTION_CATCH_RETHROW( InvalidDagMCGeometry,
                           "Unable to parse the cell material ids!" );

  // Convert the material names to material ids
  CellIdPropertyValuesMap::const_iterator cell_it =
    cell_id_mat_name_map.begin();

  while( cell_it != cell_id_mat_name_map.end() )
  {
    TEST_FOR_EXCEPTION( cell_it->second.size() > 1,
                        InvalidDagMCGeometry,
                        "Cell " << cell_it->first << " has multiple "
                        "materials assigned!" );

    TEST_FOR_EXCEPTION(
                    cell_it->second.front().find_first_not_of( "0123456789" ) <
                    cell_it->second.size(),
                    InvalidDagMCGeometry,
                    "Cell " << cell_it->first << " has an invalid "
                    "material id (" << cell_it->second.front() << ")! " );

    std::istringstream iss( cell_it->second.front() );

    iss >> cell_id_mat_id_map[cell_it->first];

    ++cell_it;
  }
}

// Get the cell densities
/*! \details Void and terminal cells will not be added to the map.
 */
void DagMCModel::getCellDensities( CellIdDensityMap& cell_id_density_map ) const
{
  // Load a map of the cell ids and density names
  CellIdPropertyValuesMap cell_id_density_name_map;

  try{
    this->getCellPropertyValues( d_model_properties->getDensityPropertyName(),
                                 cell_id_density_name_map );
  }
  EXCEPTION_CATCH_RETHROW( InvalidDagMCGeometry,
                           "Unable to parse the cell densities!" );

  // Convert the material names to material ids
  CellIdPropertyValuesMap::const_iterator cell_it =
    cell_id_density_name_map.begin();

  while( cell_it != cell_id_density_name_map.end() )
  {
    TEST_FOR_EXCEPTION( cell_it->second.size() > 1,
                        InvalidDagMCGeometry,
                        "Cell " << cell_it->first << " has multiple "
                        "densities assigned!" );

    TEST_FOR_EXCEPTION(
                  cell_it->second.front().find_first_not_of( "-.0123456789" ) <
                  cell_it->second.size(),
                  InvalidDagMCGeometry,
                  "Cell " << cell_it->first << " has an invalid "
                  "density (" << cell_it->second.front() << ")! " );

    double raw_density =
      Utility::fromString<double>( cell_it->second.front() );

    // Convert 1/b-cm top 1/cm^3
    if( raw_density > 0.0 )
      raw_density *= 1e24;

    cell_id_density_map[cell_it->first] = Density::from_value( raw_density );

    ++cell_it;
  }
}

// Get the cell estimator data
void DagMCModel::getCellEstimatorData(
                          CellEstimatorIdDataMap& estimator_id_data_map ) const
{
  // Load the estimator property cell id map
  PropValueCellIdMap estimator_prop_cell_id_map;

  try{
    this->getCellIdsWithPropertyValue(
                                d_model_properties->getEstimatorPropertyName(),
                                estimator_prop_cell_id_map );
  }
  EXCEPTION_CATCH_RETHROW( InvalidDagMCGeometry,
                           "Unable to parse the cell estimator data!" );

  PropValueCellIdMap::const_iterator estimator_it =
    estimator_prop_cell_id_map.begin();

  // Loop through all of the cell estimators and extract their information
  while( estimator_it != estimator_prop_cell_id_map.end() )
  {
    CellEstimatorIdDataMap::key_type id;
    EstimatorType estimator_type;
    ParticleType particle_type;

    try{
      this->extractEstimatorPropertyValues( estimator_it->first,
                                            id,
                                            estimator_type,
                                            particle_type );
    }
    EXCEPTION_CATCH_RETHROW( InvalidDagMCGeometry,
                             "an invalid estimator specification "
                             "was found (" << estimator_it->first << ")! "
                             "The correct format is id.type.ptype." );

    // Make sure the id is valid
    TEST_FOR_EXCEPTION( estimator_id_data_map.find( id ) !=
                        estimator_id_data_map.end(),
                        InvalidDagMCGeometry,
                        "estimator id " << id << " is used multiple "
                        "times!" );

    // Make sure the estimator type is valid
    TEST_FOR_EXCEPTION( !isCellEstimator( estimator_type ),
                        InvalidDagMCGeometry,
                        "cell estimator " << id << " has a surface estimator "
                        "type specified!" );

    // Make sure at least one cell has been assigned to the estimator
    TEST_FOR_EXCEPTION( estimator_it->second.size() == 0,
                        InvalidDagMCGeometry,
                        "estimator " << id << " has no cells assigned!" );

    // Add the estimator info to the map
    CellEstimatorIdDataMap::mapped_type& estimator_data_tuple =
      estimator_id_data_map[id];

    // Assign the estimator surface info
    Utility::get<0>(estimator_data_tuple) = estimator_type;
    Utility::get<1>(estimator_data_tuple) = particle_type;
    Utility::get<2>(estimator_data_tuple).assign( estimator_it->second.begin(),
                                                  estimator_it->second.end() );

    ++estimator_it;
  }
}

// Get the problem surfaces
void DagMCModel::getSurfaces( SurfaceIdSet& surface_set ) const
{
  moab::Range::const_iterator surface_handle_it = d_surface_handler->begin();

  while( surface_handle_it != d_surface_handler->end() )
  {
    EntityId surface_id =
      d_surface_handler->getSurfaceId( *surface_handle_it );

    surface_set.insert( surface_id );

    ++surface_handle_it;
  }
}

// Get the surface estimator data
void DagMCModel::getSurfaceEstimatorData(
                       SurfaceEstimatorIdDataMap& estimator_id_data_map ) const
{
  // Load the estimator property surface id map
  PropValueSurfaceIdMap estimator_prop_surface_id_map;

  try{
    this->getSurfaceIdsWithPropertyValue(
                                d_model_properties->getEstimatorPropertyName(),
                                estimator_prop_surface_id_map );
  }
  EXCEPTION_CATCH_RETHROW( InvalidDagMCGeometry,
                           "Unable to parse the surface estimator "
                           "properties!" );

  PropValueSurfaceIdMap::const_iterator estimator_it =
    estimator_prop_surface_id_map.begin();

  // Loop through all of the surface estimators and extract their information
  while( estimator_it != estimator_prop_surface_id_map.end() )
  {
    SurfaceEstimatorIdDataMap::key_type id;
    EstimatorType estimator_type;
    ParticleType particle_type;

    try{
      this->extractEstimatorPropertyValues( estimator_it->first,
                                            id,
                                            estimator_type,
                                            particle_type );
    }
    EXCEPTION_CATCH_RETHROW( InvalidDagMCGeometry,
                             "an invalid estimator specification "
                             "was found!" );

    // Make sure the id is valid
    TEST_FOR_EXCEPTION( estimator_id_data_map.find( id ) !=
                        estimator_id_data_map.end(),
                        InvalidDagMCGeometry,
                        "estimator id " << id << " is used multiple "
                        "times!" );

    // Make sure the estimator type is valid
    TEST_FOR_EXCEPTION( !isSurfaceEstimator( estimator_type ),
                        InvalidDagMCGeometry,
                        "surface estimator " << id << " has a cell estimator "
                        "type specified!" );

    // Make sure at least one surface has been assigned to the estimator
    TEST_FOR_EXCEPTION( estimator_it->second.size() == 0,
                        InvalidDagMCGeometry,
                        "estimator " << id << " has no surfaces "
                        "assigned!" );

    // Add the estimator info to the map
    SurfaceEstimatorIdDataMap::mapped_type& estimator_data_tuple =
      estimator_id_data_map[id];

    // Assign the estimator surface info
    Utility::get<0>(estimator_data_tuple) = estimator_type;
    Utility::get<1>(estimator_data_tuple) = particle_type;
    Utility::get<2>(estimator_data_tuple).assign( estimator_it->second.begin(),
                                                  estimator_it->second.end() );

    ++estimator_it;
  }
}

// Check if a cell exists
bool DagMCModel::doesCellExist( const EntityId cell_id ) const
{
  return d_cell_handler->doesCellExist( cell_id );
}

// Check if the surface exists
bool DagMCModel::doesSurfaceExist( const EntityId surface_id ) const
{
  return d_surface_handler->doesSurfaceExist( surface_id );
}

// Get the cell volume
auto DagMCModel::getCellVolume( const EntityId cell_id ) const -> Volume
{
  // Make sure the cell exists
  testPrecondition( this->doesCellExist( cell_id ) );

  moab::EntityHandle cell_handle = d_cell_handler->getCellHandle( cell_id );

  double raw_volume = 0.0;

  moab::ErrorCode return_value =
   d_dagmc->measure_volume( cell_handle, raw_volume );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
		      InvalidDagMCGeometry,
		      moab::ErrorCodeStr[return_value] );

  TEST_FOR_EXCEPTION( raw_volume <= 0.0,
                      InvalidDagMCGeometry,
                      "an invalid volume was calculated for cell "
                      << cell_id << "!" );

  return Volume::from_value(raw_volume);
}

// Get the surface area
auto DagMCModel::getSurfaceArea( const EntityId surface_id ) const -> Area
{
  // Make sure the cell exists
  testPrecondition( this->doesSurfaceExist( surface_id ) );

  moab::EntityHandle surface_handle =
    d_surface_handler->getSurfaceHandle( surface_id );

  double raw_surface_area = 0.0;

  moab::ErrorCode return_value =
    d_dagmc->measure_area( surface_handle, raw_surface_area );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
		      InvalidDagMCGeometry,
		      moab::ErrorCodeStr[return_value] );

  TEST_FOR_EXCEPTION( raw_surface_area <= 0.0,
                      InvalidDagMCGeometry,
                      "an invalid surface area was calculated for "
                      "surface " << surface_id << "!" );

  return Area::from_value(raw_surface_area);
}

// Check if the cell is a termination cell
bool DagMCModel::isTerminationCell( const EntityId cell_id ) const
{
  // Make sure the cell exists
  testPrecondition( this->doesCellExist( cell_id ) );

  return d_termination_cells.find( cell_id ) !=
    d_termination_cells.end();
}

// Check if the cell is a void cell
bool DagMCModel::isVoidCell( const EntityId cell_id ) const
{
  // Make sure the cell exists
  testPrecondition( this->doesCellExist( cell_id ) );

  moab::EntityHandle cell_handle = d_cell_handler->getCellHandle( cell_id );

  return !d_dagmc->has_prop( cell_handle,
                             d_model_properties->getMaterialPropertyName() );
}

// Check if the surface is a reflecting surface
bool DagMCModel::isReflectingSurface( const EntityId surface_id ) const
{
  // Make sure the surface exists
  testPrecondition( this->doesSurfaceExist( surface_id ) );

  return d_reflecting_surfaces.left.find( surface_id ) !=
    d_reflecting_surfaces.left.end();
}

// Create a raw, heap-allocated navigator
DagMCNavigator* DagMCModel::createNavigatorAdvanced(
    const Navigator::AdvanceCompleteCallback& advance_complete_callback ) const
{
  return new DagMCNavigator( this->shared_from_this(),
                             advance_complete_callback );
}

// Create a raw, heap-allocated navigator
DagMCNavigator* DagMCModel::createNavigatorAdvanced() const
{
  return new DagMCNavigator( this->shared_from_this() );
}

// Get the cells associated with a property name
// Note: If a property value is passed only the cells with both the property
// and value will be returned.
void DagMCModel::getCellsWithProperty( std::vector<moab::EntityHandle>& cells,
                                       const std::string& property,
                                       const std::string* property_value ) const
{
  moab::ErrorCode return_value =
    d_dagmc->entities_by_property( property, cells, 3, property_value );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      InvalidDagMCGeometry,
		      moab::ErrorCodeStr[return_value] );
}

// Get the surfaces associated with a property name
// Note: If a property value is passed only the cells with both the property
// and value will be returned.
void DagMCModel::getSurfacesWithProperty(
                                     std::vector<moab::EntityHandle>& surfaces,
                                     const std::string& property,
                                     const std::string* property_value ) const
{
  moab::ErrorCode return_value =
    d_dagmc->entities_by_property( property, surfaces, 2, property_value );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      InvalidDagMCGeometry,
		      moab::ErrorCodeStr[return_value] );
}

// Get the property values associated with a property name
void DagMCModel::getPropertyValues( const std::string& property,
                                    std::vector<std::string>& values ) const
{
  // Get all of the property values
  moab::ErrorCode return_value =
    d_dagmc->get_all_prop_values( property, values );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
		      InvalidDagMCGeometry,
		      moab::ErrorCodeStr[return_value] );
}

// Get the property values associated with a property name and cell id
void DagMCModel::getCellPropertyValues(
                          const std::string& property,
                          CellIdPropertyValuesMap& cell_id_prop_val_map ) const
{
  std::vector<moab::EntityHandle> cells_with_property;

  // Get all of the cells with the desired property
  try{
    this->getCellsWithProperty( cells_with_property, property );
  }
  EXCEPTION_CATCH_RETHROW( InvalidDagMCGeometry,
                           "Unable to extract cells with property "
                           << property << "!" );

  // Get the property value for each cell
  for( size_t i = 0; i < cells_with_property.size(); ++i )
  {
    EntityId cell_id =
      d_cell_handler->getCellId( cells_with_property[i] );

    moab::ErrorCode return_value =
      d_dagmc->prop_values( cells_with_property[i],
                            property,
                            cell_id_prop_val_map[cell_id] );

    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
			InvalidDagMCGeometry,
			moab::ErrorCodeStr[return_value] );
  }
}

// Get the cell ids with a property value
void DagMCModel::getCellIdsWithPropertyValue(
                               const std::string& property,
                               PropValueCellIdMap& prop_val_cell_id_map ) const
{
  // Get all of the values for the desired property
  PropertyValuesArray property_values;

  moab::ErrorCode return_value =
    d_dagmc->get_all_prop_values( property, property_values );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      InvalidDagMCGeometry,
                      moab::ErrorCodeStr[return_value] );

  // Load the map
  std::vector<moab::EntityHandle> cells;

  for( size_t i = 0; i < property_values.size(); ++i )
  {
    try{
      this->getCellsWithProperty( cells, property, &property_values[i] );
    }
    EXCEPTION_CATCH_RETHROW( InvalidDagMCGeometry,
                             "Unable to extract cells with property "
                             << property << " and value "
                             << property_values[i] << "!" );

    if( cells.size() > 0 )
    {
      PropValueCellIdMap::mapped_type& cell_ids =
        prop_val_cell_id_map[property_values[i]];

      cell_ids.resize( cells.size() );

      // Convert the entity handles to cell ids
      for( size_t j = 0; j < cells.size(); ++j )
	cell_ids[j] = d_cell_handler->getCellId( cells[j] );

      cells.clear();
    }
  }
}

// Get the property values associated with a property name and surface id
void DagMCModel::getSurfacePropertyValues(
                    const std::string& property,
                    SurfaceIdPropertyValuesMap& surface_id_prop_val_map ) const
{
  std::vector<moab::EntityHandle> surfaces_with_property;

  // Get all of the surfaces with the desired property
  try{
    this->getSurfacesWithProperty( surfaces_with_property, property );
  }
  EXCEPTION_CATCH_RETHROW( InvalidDagMCGeometry,
                           "Unable to extract surfaces with property "
                           << property << "!" );

  // Get the property value for each surface
  for( size_t i = 0; i < surfaces_with_property.size(); ++i )
  {
    EntityId surface_id =
      d_surface_handler->getSurfaceId( surfaces_with_property[i] );

    moab::EntityHandle return_value =
      d_dagmc->prop_values( surfaces_with_property[i],
                            property,
                            surface_id_prop_val_map[surface_id] );

    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
			InvalidDagMCGeometry,
			moab::ErrorCodeStr[return_value] );
  }
}

// Get the surface ids with a property value
void DagMCModel::getSurfaceIdsWithPropertyValue(
                         const std::string& property,
                         PropValueSurfaceIdMap& prop_val_surface_id_map ) const
{
  // Get all of the values for the desired property
  PropertyValuesArray property_values;

  moab::ErrorCode return_value =
    d_dagmc->get_all_prop_values( property, property_values );

  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      InvalidDagMCGeometry,
                      moab::ErrorCodeStr[return_value] );

  // Load the map
  std::vector<moab::EntityHandle> surfaces;

  for( size_t i = 0; i < property_values.size(); ++i )
  {
    return_value = d_dagmc->entities_by_property( property,
                                                  surfaces,
                                                  2,
                                                  &property_values[i] );

    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                        InvalidDagMCGeometry,
                        moab::ErrorCodeStr[return_value] );

    if( surfaces.size() > 0 )
    {
      PropValueSurfaceIdMap::mapped_type& surface_ids =
	prop_val_surface_id_map[property_values[i]];

      surface_ids.resize( surfaces.size() );

      // Convert the entity handles to surface ids
      for( size_t j = 0; j < surfaces.size(); ++j )
	surface_ids[j] = d_surface_handler->getSurfaceId( surfaces[j] );

      surfaces.clear();
    }
  }
}

// Print model details
std::string DagMCModel::getName() const
{
  return d_model_properties->getModelFileNameWithPath();
}

// Return the cell handler
const Geometry::DagMCCellHandler& DagMCModel::getCellHandler() const
{
  return *d_cell_handler;
}

// Return the surface handler
const Geometry::DagMCSurfaceHandler& DagMCModel::getSurfaceHandler() const
{
  return *d_surface_handler;
}

// Return the reflecting surfaces
const DagMCNavigator::ReflectingSurfaceIdHandleMap&
DagMCModel::getReflectingSurfaceIdHandleMap() const
{
  return d_reflecting_surfaces;
}

// Return the raw dagmc instance
moab::DagMC& DagMCModel::getRawDagMCInstance() const
{
  return *d_dagmc;
}

EXPLICIT_CLASS_SAVE_LOAD_INST( DagMCModel );

}  // end Geometry namespace

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( DagMCModel, Geometry );

//---------------------------------------------------------------------------//
// end Geometry_DagMC.cpp
//---------------------------------------------------------------------------//
