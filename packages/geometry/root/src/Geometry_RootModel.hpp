//---------------------------------------------------------------------------//
//!
//! \file   Geometry_RootModel.hpp
//! \author Alex Robinson, Eli Moll
//! \brief  Root model class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_ROOT_MODEL_HPP
#define GEOMETRY_ROOT_MODEL_HPP

// Std Lib Includes
#include <string>
#include <stdexcept>
#include <unordered_map>
#include <vector>

// Root Includes
#include <TGeoManager.h>
#include <TError.h>

// FRENSIE Includes
#include "Geometry_RootModelProperties.hpp"
#include "Geometry_RootNavigator.hpp"
#include "Geometry_ModuleTraits.hpp"
#include "Geometry_PointLocation.hpp"
#include "Geometry_Model.hpp"
#include "Utility_ContractException.hpp"

namespace Geometry{

/*! The Root geometry model
 * \details This class is a singleton since Root currently does not allow 
 * multiple geometries to be initialized in a single program. Once a Root 
 * model is initialized cell properties can be queried and navigators can be
 * created. 
 */
class RootModel : public Model
{

public:

  //! Get the Root model instance
  static std::shared_ptr<RootModel> getInstance();

  //! Destructor
  ~RootModel()
  {/* ... */}

  //! Check if the Root model has been initialized
  bool isInitialized() const;

  //! Initialize the Root model
  void initialize( const RootModelProperties& model_properties,
                   const int root_init_verbosity = kWarning );

  //! Get the model properties
  const RootModelProperties& getModelProperties() const;

  //! Get the model name
  std::string getName() const override;

  //! Check if the model has cell estimator data
  bool hasCellEstimatorData() const override;

  //! Get the material ids
  void getMaterialIds( MaterialIdSet& material_ids ) const override;

  //! Get the problem cells
  void getCells( CellIdSet& cell_set,
                 const bool include_void_cells,
                 const bool include_termination_cells ) const override;

  //! Get the cell materials
  template<template<typename,typename,typename...> class MapType>
  void getCellMaterialNames(
                         MapType<ModuleTraits::InternalCellHandle,std::string>&
                         cell_id_mat_name_map ) const;

  //! Get the cell material ids
  void getCellMaterialIds( CellIdMatIdMap& cell_id_mat_id_map ) const override;

  //! Get the cell densities
  void getCellDensities( CellIdDensityMap& cell_id_density_map ) const override;

  //! Get the cell estimator data
  void getCellEstimatorData(
           CellEstimatorIdDataMap& cell_estimator_id_data_map ) const override;

  //! Check if a cell exists
  bool doesCellExist( const ModuleTraits::InternalCellHandle cell_id ) const override;

  //! Check if the cell is a termination cell
  bool isTerminationCell( const ModuleTraits::InternalCellHandle cell_id ) const override;

  //! Check if the cell is a void cell
  bool isVoidCell( const ModuleTraits::InternalCellHandle cell_id ) const override;

  //! Get the cell volume
  double getCellVolume( const ModuleTraits::InternalCellHandle cell_id ) const override;

  //! Create a Root navigator
  std::shared_ptr<RootNavigator> createRootNavigator() const;

  //! Create a navigator
  std::shared_ptr<Navigator> createNavigator() const override;

private:

  // Constructor
  RootModel();

  // Load the Root geometry file
  void loadRootGeometry( const int root_init_verbosity );

  // Create the cell id to unique id map
  void createCellIdToUniqueIdMap();

  // Validate the model
  void validateModel() const;

  // Check if the volume is a void volume
  bool isVoidVolume( const TGeoVolume* volume ) const;

  // Check if the volume is a termination volume
  bool isTerminationVolume( const TGeoVolume* volume ) const;

  // Get the cell
  TGeoVolume* getVolumePtr( const ModuleTraits::InternalCellHandle& cell_id ) const;

  // The custom root error handler
  static void handleRootError( int level,
                               Bool_t abort,
                               const char* location,
                               const char* msg );

  // The Root model instance
  static std::shared_ptr<RootModel> s_instance;

  // Root TGeoManager
  TGeoManager* d_manager;

  // Root cell id to uid map
  typedef std::unordered_map<ModuleTraits::InternalCellHandle,Int_t>
  CellIdUidMap;
  CellIdUidMap d_cell_id_uid_map;

  // The model properties
  std::unique_ptr<const RootModelProperties> d_model_properties;
};

//! The invalid root geometry error
class InvalidRootGeometry : public std::runtime_error
{

public:

  InvalidRootGeometry( const std::string& what_arg )
    : std::runtime_error( what_arg )
  { /* ... */ }
};

} // end Geometry namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Geometry_RootModel_def.hpp"

//---------------------------------------------------------------------------//

#endif // end GEOMETRY_ROOT_MODEL_HPP

//---------------------------------------------------------------------------//
// end Geometry_RootModel.hpp
//---------------------------------------------------------------------------//
