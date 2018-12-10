//---------------------------------------------------------------------------//
//!
//! \file   Geometry_RootModel.cpp
//! \author Alex Robinson, Eli Moll
//! \brief  Root model class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <exception>
#include <thread>

// FRENSIE Includes
#include "FRENSIE_Archives.hpp" // Must include first
#include "Geometry_RootModel.hpp"
#include "Geometry_RootLoggingMacros.hpp"
#include "Utility_Set.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_OpenMPProperties.hpp"

namespace Geometry{

// Initialize static member data
std::shared_ptr<RootModel> RootModel::s_instance;

// Get the Root model instance
std::shared_ptr<RootModel> RootModel::getInstance()
{
  // Just-in-time initialization
  if( !s_instance )
    s_instance.reset( new RootModel );

  return s_instance;
}

// Constructor
RootModel::RootModel()
  : d_manager( NULL )
{ /* ... */ }

// Initialize the model just-in-time
void RootModel::initializeJustInTime()
{
  this->initialize( *d_model_properties );
}

// Check if root has been initialized
bool RootModel::isInitialized() const
{
  return d_manager != NULL;
}

// Initialize the root geometry manager
/*! \details Valid root initialization verbosity levels are (from lowest to
 * highest) kPrint, kInfo, kWarning, kError, kSysError, kFatal. After
 * initialization the verbosity level will be set to kWarning. Some basic
 * verification of the geometry will be done during initialization. Each cell
 * will be checked for a non-zero id that is not repeated by any other cell
 * (unique id).
 */
void RootModel::initialize( const RootModelProperties& model_properties,
                            const int root_init_verbosity )
{
  // Make sure to initialize only once
  testPrecondition( !this->isInitialized() );

  if( !this->isInitialized() )
  {
    // Cache the model properties
    d_model_properties.reset( new RootModelProperties( model_properties ) );

    FRENSIE_LOG_PARTIAL_NOTIFICATION( "Loading model "
                                      << d_model_properties->getModelFileNameWithPath() <<
                                      " ... " );
    try{
      this->loadRootGeometry( root_init_verbosity );
    }
    EXCEPTION_CATCH_RETHROW( InvalidRootGeometry,
                             "Unable to load Root geometry file "
                             << d_model_properties->getModelFileNameWithPath() <<
                             "!" );

    // Create the cell id to unique id map
    try{
      this->createCellIdToUniqueIdMap();
    }
    EXCEPTION_CATCH_RETHROW( InvalidRootGeometry,
                             "Unable to parse the unique cell ids!" );

    // Validate the model
    try{
      this->validateModel();
    }
    EXCEPTION_CATCH_RETHROW( InvalidRootGeometry,
                             "Invalid root geometry detected!" );

    FRENSIE_LOG_NOTIFICATION( "done!" );
    FRENSIE_FLUSH_ALL_LOGS();
  }
  else
  {
    FRENSIE_LOG_ROOT_WARNING( "Cannot load requested model ("
                              << model_properties.getModelFileNameWithPath() <<
                              ") because a model has already been loaded!" );
  }
}

// Load the Root geometry file
void RootModel::loadRootGeometry( const int root_init_verbosity )
{
  // Tell Root to suppress all message below the requested verbosity level
  gErrorIgnoreLevel = root_init_verbosity;

  // Set the custom error handler
  SetErrorHandler( RootModel::handleRootError );

  try{
    d_manager =
      TGeoManager::Import( d_model_properties->getModelFileNameWithPath().c_str() );
  }
  EXCEPTION_CATCH_RETHROW( InvalidRootGeometry,
                           "Root could not import file "
                           << d_model_properties->getModelFileNameWithPath() << "!" );

  // Make sure the import was successful
  TEST_FOR_EXCEPTION( d_manager == NULL,
                      InvalidRootGeometry,
                      "Root could not import file "
                      << d_model_properties->getModelFileNameWithPath() << "!" );

  // Lock the geometry so no other geometries can be imported
  TGeoManager::LockGeometry();

  // Set up thread support so that navigators can be constructed and
  // destructed correctly
  unsigned int max_threads = std::thread::hardware_concurrency();

  if( max_threads == 0 )
    max_threads = 1;

  d_manager->SetMaxThreads( max_threads );

  // Tell Root to suppress all message below the warning level after this point
  gErrorIgnoreLevel = kWarning;
}

// Create the cell id to unique id map
void RootModel::createCellIdToUniqueIdMap()
{
  // Get the list of volumes
  TObjArray* volume_list = d_manager->GetListOfVolumes();
  TIterator* volume_it = volume_list->MakeIterator();
  size_t number_volumes = volume_list->GetEntries();

  // Set up the cell id to UID map and make sure that the cell ids are unique
  for( size_t i = 0; i < number_volumes; ++i )
  {
    TObject* object = volume_it->Next();
    TGeoVolume* cell = dynamic_cast<TGeoVolume*>( object );

    TEST_FOR_EXCEPTION( cell->GetUniqueID() == 0,
                        InvalidRootGeometry,
                        "Root contains a cell which has not been "
                        "assigned an id in the input file!" );

    TEST_FOR_EXCEPTION( cell->GetUniqueID() == Model::invalidCellId(),
                        InvalidRootGeometry,
                        "Root contains a cell that has a reserved id ("
                        << Model::invalidCellId() <<
                        ") in the input file!" );

    TEST_FOR_EXCEPTION( d_cell_id_uid_map.find( cell->GetUniqueID() ) !=
                        d_cell_id_uid_map.end(),
                        InvalidRootGeometry,
                        "Root contains cells with the same id ("
                        << cell->GetUniqueID() << ") in the input file!" );

    d_cell_id_uid_map[cell->GetUniqueID()] =
      d_manager->GetUID( cell->GetName() );
  }
}

// Validate the model
void RootModel::validateModel() const
{
  // Verify that at least one termination cell is present
  size_t num_termination_cells = 0;

  CellIdUidMap::const_iterator cell_it, cell_end;
  cell_it = d_cell_id_uid_map.begin();
  cell_end = d_cell_id_uid_map.end();

  while( cell_it != cell_end )
  {
    if( this->isTerminationCell( cell_it->first ) )
      ++num_termination_cells;

    ++cell_it;
  }

  TEST_FOR_EXCEPTION( num_termination_cells == 0,
                      InvalidRootGeometry,
                      "Root contains no cells with the terminal "
                      "material!" );
}

// Get the model properties
const RootModelProperties& RootModel::getModelProperties() const
{
  return *d_model_properties;
}

// Check if the model has cell estimator data
bool RootModel::hasCellEstimatorData() const
{
  return false;
}

// Get the material ids
void RootModel::getMaterialIds( MaterialIdSet& material_ids ) const
{
  CellIdMatIdMap cell_id_mat_id_map;

  this->getCellMaterialIds( cell_id_mat_id_map );

  CellIdMatIdMap::const_iterator cell_id_mat_id_it =
    cell_id_mat_id_map.begin();

  while( cell_id_mat_id_it != cell_id_mat_id_map.end() )
  {
    material_ids.insert( cell_id_mat_id_it->second );

    ++cell_id_mat_id_it;
  }
}

// Get the problem cells
void RootModel::getCells( CellIdSet& cell_set,
                          const bool include_void_cells,
                          const bool include_termination_cells ) const
{
  // Get a list of the cells
  TObjArray* cells = d_manager->GetListOfVolumes();
  size_t number_of_cells = cells->GetEntries();

  TIterator* cell_it  = cells->MakeIterator();

  for( size_t i = 0; i < number_of_cells; ++i )
  {
    // Get the cell
    TGeoVolume* cell = dynamic_cast<TGeoVolume*>( cell_it->Next() );

    // Check if it is a void cell
    if( this->isVoidVolume( cell ) )
    {
      if( include_void_cells )
        cell_set.insert( cell->GetUniqueID() );
    }
    // Check if it is a termination cell
    else if( this->isTerminationVolume( cell ) )
    {
      if( include_termination_cells )
        cell_set.insert( cell->GetUniqueID() );
    }
    else
      cell_set.insert( cell->GetUniqueID() );
  }
}

// Get the cell material ids
void RootModel::getCellMaterialIds( CellIdMatIdMap& cell_id_mat_id_map ) const
{
  // Make sure that root is initialized
  testPrecondition( this->isInitialized() );

  // Set the material property name plus underscore separator
  std::string material_property_suffix =
    d_model_properties->getMaterialPropertyName() + "_";

  // Get the cell material names
  typedef std::unordered_map<EntityId,std::string>
    CellIdMatNameMap;
  CellIdMatNameMap cell_id_material_name;

  this->getCellMaterialNames( cell_id_material_name );

  CellIdMatNameMap::const_iterator cell_it = cell_id_material_name.begin();

  while( cell_it != cell_id_material_name.end() )
  {
    const std::string& material_name = cell_it->second;

    if( material_name != d_model_properties->getVoidMaterialName() &&
        material_name != d_model_properties->getTerminalMaterialName() )
    {
      TEST_FOR_EXCEPTION( material_name.find( material_property_suffix ) != 0,
                          InvalidRootGeometry,
                          "Root cell " << cell_it->first <<
                          " has an invalid material name ("
                          << material_name << ")!" );

      TEST_FOR_EXCEPTION( material_name.find_first_not_of( "0123456789", material_property_suffix.size() )
                          < material_name.size(),
                          InvalidRootGeometry,
                          "Root cell " << cell_it->first <<
                          " has an invalid material name ("
                          << material_name << ")!" );

      // Extract the material id from the name
      std::istringstream
        iss( material_name.substr( material_property_suffix.size() ) );

      iss >> cell_id_mat_id_map[cell_it->first];
    }

    ++cell_it;
  }
}

// Get the cell densities
/*! \details Void and terminal cells will not be added to the map.
 */
void RootModel::getCellDensities( CellIdDensityMap& cell_id_density_map ) const
{
  // Make sure that root is initialized
  testPrecondition( this->isInitialized() );

  // Get a list of the cells
  TObjArray* cells = d_manager->GetListOfVolumes();
  size_t number_of_cells = cells->GetEntries();

  TIterator* cell_it  = cells->MakeIterator();

  for( size_t i = 0; i < number_of_cells; ++i )
  {
    // Get the cell
    TGeoVolume* cell = dynamic_cast<TGeoVolume*>( cell_it->Next() );

    // Get the cell material
    TGeoMaterial* mat = cell->GetMaterial();

    // Get the material name
    std::string mat_name = mat->GetName();

    // Add the density to the map
    if( mat_name != d_model_properties->getVoidMaterialName() &&
        mat_name != d_model_properties->getTerminalMaterialName() )
    {
      double raw_density = mat->GetDensity();

      TEST_FOR_EXCEPTION( raw_density == 0.0,
                          InvalidRootGeometry,
                          "Root cell " << cell->GetUniqueID() <<
                          "has an invalid density ("
                          << mat->GetDensity() << ")!" );

      // Convert 1/b-cm to 1/cm^3
      if( raw_density > 0.0 )
        raw_density *= 1e24;

      cell_id_density_map[cell->GetUniqueID()] =
        Density::from_value( raw_density );
    }
  }
}

// Get the cell estimator data
/*! \details Root models do not store cell estimator data.
 */
void RootModel::getCellEstimatorData( CellEstimatorIdDataMap&  ) const
{ /* ... */ }

// Check if a cell exists
bool RootModel::doesCellExist( const EntityId cell_id ) const
{
  // Make sure that root has been initialized
  testPrecondition( this->isInitialized() );

  return d_cell_id_uid_map.find( cell_id ) != d_cell_id_uid_map.end();
}

// Check if the cell is a termination cell
bool RootModel::isTerminationCell( const EntityId cell_id ) const
{
  // Make sure that root has been initialized
  testPrecondition( this->isInitialized() );
  // Make sure the cell exists
  testPrecondition( this->doesCellExist( cell_id ) );

  return this->isTerminationVolume( this->getVolumePtr( cell_id ) );
}

// Check if the volume is a termination volume
bool RootModel::isTerminationVolume( const TGeoVolume* volume ) const
{
  return volume->GetMaterial()->GetName() ==
    d_model_properties->getTerminalMaterialName();
}

// Check if the cell is a void cell
bool RootModel::isVoidCell( const EntityId cell_id ) const
{
  // Make sure that root has been initialized
  testPrecondition( RootModel::isInitialized() );
  // Make sure the cell exists
  testPrecondition( RootModel::doesCellExist( cell_id ) );

  return this->isVoidVolume( this->getVolumePtr( cell_id ) );
}

// Check if the volume is a void volume
bool RootModel::isVoidVolume( const TGeoVolume* volume ) const
{
  return volume->GetMaterial()->GetName() ==
    d_model_properties->getVoidMaterialName();
}

// Get the cell volume
/*! \details This will only return the correct cell volume when the daughters
 * are completely contained in the cell of interest (no overlaps)
 */
auto RootModel::getCellVolume( const EntityId cell_id ) const -> Volume
{
  // Make sure that root has been initialized
  testPrecondition( this->isInitialized() );
  // Make sure the cell exists
  testPrecondition( this->doesCellExist( cell_id ) );

  // Get the volume of the cell
  TGeoVolume* volume_ptr = this->getVolumePtr( cell_id );

  Volume volume = Volume::from_value( volume_ptr->Capacity() );

  // Subtract of the daughter cell volumes
  TObjArray* daughters = volume_ptr->GetNodes();

  if( daughters != NULL )
  {
    TIterator* daughter_it = daughters->MakeIterator();
    size_t number_of_daughters = daughters->GetEntries();

    for( size_t i = 0; i < number_of_daughters; ++i )
    {
      // Obtain the next object in the array and cast it to its derived class
      TObject* daughter_object = daughter_it->Next();
      TGeoNode* daughter_node = dynamic_cast<TGeoNode*>( daughter_object );

      TGeoVolume* daughter_volume = daughter_node->GetVolume();

      // Subtract the daughter volume
      volume -= Volume::from_value( daughter_volume->Capacity() );
    }
  }

  // Make sure the calculated volume is valid
  TEST_FOR_EXCEPTION( volume <= Utility::QuantityTraits<Volume>::zero(),
                      InvalidRootGeometry,
                      "an invalid volume was calculated for cell "
                      << cell_id << " (" << volume << ")!" );

  return volume;
}

// Create a raw, heap-allocated navigator
RootNavigator* RootModel::createNavigatorAdvanced(
    const Navigator::AdvanceCompleteCallback& advance_complete_callback ) const
{
  // Make sure that root has been initialized
  testPrecondition( this->isInitialized() );
  
  return new RootNavigator( RootModel::getInstance(),
                            advance_complete_callback );
}

// Create a raw, heap-allocated navigator
RootNavigator* RootModel::createNavigatorAdvanced() const
{
  // Make sure that root has been initialized
  testPrecondition( this->isInitialized() );

  return new RootNavigator( RootModel::getInstance() );
}

// Get the cell
TGeoVolume* RootModel::getVolumePtr( const EntityId& cell_id ) const
{
  // Make sure root is initialized
  testPrecondition( this->isInitialized() );
  // Make sure the cell exists
  testPrecondition( this->doesCellExist( cell_id ) );

  return d_manager->GetVolume( d_cell_id_uid_map.find( cell_id )->second );
}

// The custom root error handler
void RootModel::handleRootError( int level,
                                 Bool_t abort,
                                 const char* location,
                                 const char* msg )
{
  // Only process the information is the level is above ignore threshold
  if( level >= gErrorIgnoreLevel )
  {
    if( level == kInfo )
    {
      FRENSIE_LOG_ROOT_DETAILS( msg );
    }
    else if( level == kWarning )
    {
      FRENSIE_LOG_ROOT_WARNING( msg << "\n"
                                "  Root Location: " << location );
    }
    else if( level >= kError )
    {
      FRENSIE_LOG_ROOT_ERROR( msg << "\n"
                              "  Root Location: " << location );
    }

    // Request to abort will instead be sent to the FRENSIE exception handling
    // system
    if( abort )
    {
      // if( gSystem )
      //   gSystem->StackTrace();

      THROW_EXCEPTION( InvalidRootGeometry,
                       "Request to abort from Root!" );
    }
  }
}

// Get the model name
std::string RootModel::getName() const
{
  return d_model_properties->getModelFileNameWithPath();
}

// Get the manager
TGeoManager* RootModel::getManager() const
{
  return d_manager;
}

EXPLICIT_CLASS_SAVE_LOAD_INST( RootModel );

} // end Geometry namespace

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( RootModel, Geometry );

//---------------------------------------------------------------------------//
// end Geometry_Root.cpp
//---------------------------------------------------------------------------//
