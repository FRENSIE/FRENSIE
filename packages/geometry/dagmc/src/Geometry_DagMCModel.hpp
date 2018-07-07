//---------------------------------------------------------------------------//
//!
//! \file   Geometry_DagMCModel.hpp
//! \author Alex Robinson
//! \brief  DagMC model class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_DAGMC_MODEL_HPP
#define GEOMETRY_DAGMC_MODEL_HPP

// Std Lib Includes
#include <string>
#include <stdexcept>
#include <iostream>
#include <memory>

// Moab Includes
#include <DagMC.hpp>

// FRENSIE Includes
#include "Geometry_DagMCModelProperties.hpp"
#include "Geometry_DagMCCellHandler.hpp"
#include "Geometry_DagMCSurfaceHandler.hpp"
#include "Geometry_DagMCNavigator.hpp"
#include "Geometry_PointLocation.hpp"
#include "Geometry_AdvancedModel.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"
#include "Utility_Map.hpp"
#include "Utility_Set.hpp"
#include "Utility_Vector.hpp"

namespace Geometry{

/*! The DagMC geometry model
 * \details This class is a singleton since the underlying moab::DagMC object
 * is also a singleton. Once a DagMC model is initialized cell and surface
 * properties can be queried and navigators can be created.
 */
class DagMCModel : public AdvancedModel
{

public:

  //! Destructor
  ~DagMCModel()
  { /* ... */ }

  //! Get the DagMC model instance
  static std::shared_ptr<DagMCModel> getInstance();

  //! Check if the DagMC model has been initialized
  bool isInitialized() const;

  //! Initialize the DagMC model
  void initialize( const DagMCModelProperties& model_properties,
                   const bool suppress_dagmc_output = true );

  //! Get the model properties
  const DagMCModelProperties& getModelProperties() const;

  //! Get the model name
  std::string getName() const override;

  //! Check if the model has cell estimator data
  bool hasCellEstimatorData() const override;

  //! Check if the model has surface estimator data
  bool hasSurfaceEstimatorData() const override;

  //! Get the material ids
  void getMaterialIds( MaterialIdSet& material_ids ) const override;

  //! Get the problem cells
  void getCells( CellIdSet& cell_set,
                 const bool include_void_cells,
                 const bool include_termination_cells ) const override;

  //! Get the cell material ids
  void getCellMaterialIds( CellIdMatIdMap& cell_id_mat_id_map ) const override;

  //! Get the cell densities
  void getCellDensities( CellIdDensityMap& cell_id_density_map ) const override;

  //! Get the cell estimator data
  void getCellEstimatorData( CellEstimatorIdDataMap& estimator_id_data_map ) const override;

  //! Check if a cell exists
  bool doesCellExist( const InternalCellHandle cell_id ) const override;

  //! Check if the cell is a termination cell
  bool isTerminationCell( const InternalCellHandle cell_id ) const override;

  //! Check if the cell is a void cell
  bool isVoidCell( const InternalCellHandle cell_id ) const override;

  //! Get the cell volume
  Volume getCellVolume( const InternalCellHandle cell_id ) const override;

  //! Get the problem surfaces
  void getSurfaces( SurfaceIdSet& surface_set ) const override;

  //! Get the surface estimator data
  void getSurfaceEstimatorData( SurfaceEstimatorIdDataMap& estimator_id_data_map ) const;

  //! Check if the surface exists
  bool doesSurfaceExist( const InternalSurfaceHandle surface_id ) const override;

  //! Get the surface area
  Area getSurfaceArea( const InternalSurfaceHandle surface_id ) const override;

  //! Check if the surface is a reflecting surface
  bool isReflectingSurface( const InternalSurfaceHandle surface_id ) const override;

  //! Create a raw, heap-allocated navigator
  DagMCNavigator* createNavigatorAdvanced( const Navigator::AdvanceCompleteCallback& advance_complete_callback ) const override;

  //! Create a raw, heap-allocated navigator
  DagMCNavigator* createNavigatorAdvanced() const override;


private:

  // The property values type
  typedef std::vector<std::string> PropertyValuesArray;

  // The cell id property values array map type
  typedef std::map<InternalCellHandle,PropertyValuesArray> CellIdPropertyValuesMap;

  // The property value cell id array map type
  typedef std::map<std::string,CellIdArray> PropValueCellIdMap;

  // The surface id property values array map type
  typedef std::map<InternalSurfaceHandle,PropertyValuesArray> SurfaceIdPropertyValuesMap;

  // The property value surface id array map type
  typedef std::map<std::string,SurfaceIdArray> PropValueSurfaceIdMap;

  // Constructor
  DagMCModel();

  // Load the dagmc geometry file
  void loadDagMCGeometry( const bool suppress_dagmc_output );

  // Validate the properties
  void validatePropertyNames() const;

  // Parse the properties
  void parseProperties() const;

  // Construct the entity handlers
  void constructEntityHandlers();

  // Extract the termination cells
  void extractTerminationCells();

  // Extract the reflecting surfaces
  void extractReflectingSurfaces();

  // Get the property values associated with a property name
  void getPropertyValues( const std::string& property,
                          PropertyValuesArray& values ) const;

  // Get the cells associated with a property name
  void getCellsWithProperty( std::vector<moab::EntityHandle>& cells,
                             const std::string& property,
                             const std::string* property_value = NULL ) const;

  // Get the surfaces associated with a property name
  void getSurfacesWithProperty(
                              std::vector<moab::EntityHandle>& surfaces,
                              const std::string& property,
                              const std::string* property_value = NULL ) const;

  // Get the property values associated with a property name and cell id
  void getCellPropertyValues(
                      const std::string& property,
                      CellIdPropertyValuesMap& cell_id_prop_values_map ) const;

  // Get the cell ids with a property value
  void getCellIdsWithPropertyValue(
                              const std::string& property,
                              PropValueCellIdMap& prop_val_cell_id_map ) const;

  // Get the property values associated with a property name and surface id
  void getSurfacePropertyValues(
                   const std::string& property,
                   SurfaceIdPropertyValuesMap& surface_id_prop_val_map ) const;

  // Get the surface ids with a property value
  void getSurfaceIdsWithPropertyValue(
                        const std::string& property,
                        PropValueSurfaceIdMap& prop_val_surface_id_map ) const;

  // Extract estimator property values
  template<typename IntType>
  void extractEstimatorPropertyValues( const std::string& prop_value,
                                       IntType& estimator_id,
                                       EstimatorType& estimator_type,
                                       ParticleType& particle_type ) const;

  //! Return the cell handler
  const Geometry::DagMCCellHandler& getCellHandler() const;

  //! Return the surface handler
  const Geometry::DagMCSurfaceHandler& getSurfaceHandler() const;

  //! Return the reflecting surfaces
  const DagMCNavigator::ReflectingSurfaceIdHandleMap&
  getReflectingSurfaceIdHandleMap() const;

  //! Return the raw dagmc instance
  moab::DagMC& getRawDagMCInstance() const;

  // Save the model to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the model from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // Declare the DagMCNavigator as a friend
  friend class DagMCNavigator;

  // The DagMC model instance
  static std::shared_ptr<DagMCModel> s_instance;

  // The raw DagMC instance
  moab::DagMC* d_dagmc;

  // The DagMC cell handler
  std::unique_ptr<const Geometry::DagMCCellHandler> d_cell_handler;

  // The DagMC surface handle
  std::unique_ptr<const Geometry::DagMCSurfaceHandler> d_surface_handler;

  // The termination cells
  CellIdSet d_termination_cells;

  // The reflecting surfaces
  typedef DagMCNavigator::ReflectingSurfaceIdHandleMap
  ReflectingSurfaceIdHandleMap;
  ReflectingSurfaceIdHandleMap d_reflecting_surfaces;

  // The model properties
  std::unique_ptr<const DagMCModelProperties> d_model_properties;
};

//! The invalid DagMC geometry error
class InvalidDagMCGeometry : public std::runtime_error
{

public:

  InvalidDagMCGeometry( const std::string& what_arg )
    : std::runtime_error( what_arg )
  { /* ... */ }
};

} // end Geometry namespace

BOOST_SERIALIZATION_CLASS_VERSION( DagMCModel, Geometry, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( DagMCModel, Geometry );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Geometry, DagMCModel );

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Geometry_DagMCModel_def.hpp"

//---------------------------------------------------------------------------//

#endif // end GEOMETRY_DAGMC_MODEL_HPP

//---------------------------------------------------------------------------//
// end Geometry_DagMCModel.hpp
//---------------------------------------------------------------------------//
