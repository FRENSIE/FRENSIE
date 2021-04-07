//---------------------------------------------------------------------------//
//!
//! \file   Geometry_InfiniteMedium.hpp
//! \author Alex Robinson
//! \brief  The infinite medium geometry model class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_INFINITE_MEDIUM_MODEL_HPP
#define GEOMETRY_INFINITE_MEDIUM_MODEL_HPP

// FRENSIE Includes
#include "Geometry_Model.hpp"
#include "Geometry_InfiniteMediumNavigator.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"

namespace Geometry{

//! The infinite medium model
class InfiniteMediumModel : public Model
{

public:

  //! Constructor
  InfiniteMediumModel( const EntityId cell = 1,
                       const Model::MaterialId material_id = 0,
                       const Model::Density density = 0.0*Model::DensityUnit() );

  //! Destructor
  ~InfiniteMediumModel()
  { /* ... */ }

  //! Get the model name
  std::string getName() const override;

  //! Check if the model has cell estimator data
  bool hasCellEstimatorData() const override;

  //! Get the material ids
  void getMaterialIds( MaterialIdSet& material_ids ) const override;

  //! Get the cells
  void getCells( CellIdSet& cell_set,
                 const bool include_void_cells,
                 const bool include_termination_cells ) const override;

  //! Get the cell material ids
  void getCellMaterialIds( CellIdMatIdMap& cell_id_mat_id_map ) const override;

  //! Get the cell densities
  void getCellDensities( CellIdDensityMap& cell_density_map ) const override;

  //! Get the cell estimator data
  void getCellEstimatorData(
           CellEstimatorIdDataMap& cell_estimator_id_data_map ) const override;

  //! Check if a cell exists
  bool doesCellExist( const EntityId cell ) const override;

  //! Check if the cell is a termination cell
  bool isTerminationCell( const EntityId cell ) const override;

  //! Check if a cell is void
  bool isVoidCell( const EntityId cell ) const override;

  //! Get the cell volume
  Volume getCellVolume( const EntityId cell ) const override;

  //! Create a raw, heap-allocated navigator
  InfiniteMediumNavigator* createNavigatorAdvanced(
                                    const Navigator::AdvanceCompleteCallback&
                                    advance_complete_callback ) const override;

  //! Create a raw, heap-allocated navigator (no callback)
  InfiniteMediumNavigator* createNavigatorAdvanced() const override;

  //! Check if the model has been initialized
  bool isInitialized() const final override;

protected:

  //! Initialize the model just-in-time
  void initializeJustInTime() final override;

private:

  // Save the model to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the model from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The infinite medium cell id
  EntityId d_cell;

  // The infinite medium material id
  Model::MaterialId d_material_id;

  // The infinite medium material density
  Model::Density d_density;
};

// Save the model to an archive
template<typename Archive>
void InfiniteMediumModel::save( Archive& ar, const unsigned version ) const
{
  // Save the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( Model );

  // Save the local member data
  ar & BOOST_SERIALIZATION_NVP( d_cell );
  ar & BOOST_SERIALIZATION_NVP( d_material_id );
  ar & BOOST_SERIALIZATION_NVP( d_density );
}

// Load the model from an archive
template<typename Archive>
void InfiniteMediumModel::load( Archive& ar, const unsigned version )
{
  // Load the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( Model );

  // Load the local member data
  ar & BOOST_SERIALIZATION_NVP( d_cell );
  ar & BOOST_SERIALIZATION_NVP( d_material_id );
  ar & BOOST_SERIALIZATION_NVP( d_density );
}

} // end Geometry namespace

BOOST_SERIALIZATION_CLASS_VERSION( InfiniteMediumModel, Geometry, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( InfiniteMediumModel, Geometry );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Geometry, InfiniteMediumModel );

#endif // end GEOMETRY_INFINITE_MEDIUM_MODEL_HPP

//---------------------------------------------------------------------------//
// end Geometry_InfiniteMediumModel.hpp
//---------------------------------------------------------------------------//
