//---------------------------------------------------------------------------//
//!
//! \file   Geometry_Model.hpp
//! \author Alex Robinson
//! \brief  The geometry model base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_MODEL_HPP
#define GEOMETRY_MODEL_HPP

// Std Lib Includes
#include <memory>
#include <iostream>

// Boost Includes
#include <boost/serialization/split_member.hpp>
#include <boost/units/systems/cgs/length.hpp>
#include <boost/units/systems/cgs/volume.hpp>

// FRENSIE Includes
#include "Geometry_Navigator.hpp"
#include "Geometry_EstimatorType.hpp"
#include "Geometry_ParticleType.hpp"
#include "Utility_Set.hpp"
#include "Utility_Map.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_UnitTraits.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_SerializationHelpers.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"

namespace Geometry{

//! The model base class
class Model
{

public:

  //! The entity (cell or surface) id type
  typedef Geometry::Navigator::EntityId EntityId;

  //! The material id type
  typedef uint32_t MaterialId;

  //! The estimator id type
  typedef uint32_t EstimatorId;

  //! The length unit
  typedef Navigator::LengthUnit LengthUnit;

  //! The length quantity
  typedef Navigator::Length Length;

  //! The volume unit
  typedef boost::units::cgs::volume VolumeUnit;

  //! The volume quantity
  typedef boost::units::quantity<VolumeUnit> Volume;

  /*! The density unit
   *
   * This unit ignores the "mass" component since a density in the model
   * can be defined in terms of mass (negative value) or atoms. The material
   * definition is needed to convert between the two types of densities.
   */
  typedef typename Utility::UnitTraits<VolumeUnit>::InverseUnit DensityUnit;

  //! The density quantity
  typedef boost::units::quantity<DensityUnit> Density;

  //! The material id set type
  typedef std::set<MaterialId> MaterialIdSet;

  //! The cell id set type
  typedef Geometry::Navigator::CellIdSet CellIdSet;

  //! The cell id material id map type
  typedef std::map<EntityId,MaterialId> CellIdMatIdMap;

  //! The cell id density map type
  typedef std::map<EntityId,Density> CellIdDensityMap;

  //! The cell id array type
  typedef std::vector<EntityId> CellIdArray;

  //! The cell estimator data type
  typedef std::tuple<EstimatorType,ParticleType,CellIdArray> CellEstimatorData;

  //! The cell estimator id data map type
  typedef std::map<EstimatorId,CellEstimatorData> CellEstimatorIdDataMap;

  //! Constructor
  Model()
  { /* ... */ }

  //! Destructor
  virtual ~Model()
  { /* ... */ }

  //! Get the model name
  virtual std::string getName() const = 0;

  //! Check if this is an advanced model
  virtual bool isAdvanced() const;

  //! Check if the model has cell estimator data
  virtual bool hasCellEstimatorData() const = 0;

  //! Get the material ids
  virtual void getMaterialIds( MaterialIdSet& material_ids ) const = 0;

  //! Get the cells
  virtual void getCells( CellIdSet& cell_set,
                         const bool include_void_cells,
                         const bool include_termination_cells ) const = 0;

  //! Get the cell material ids
  virtual void getCellMaterialIds(
                                CellIdMatIdMap& cell_id_mat_id_map ) const = 0;

  //! Get the cell densities
  virtual void getCellDensities( CellIdDensityMap& cell_density_map ) const = 0;

  //! Get the cell estimator data
  virtual void getCellEstimatorData(
                CellEstimatorIdDataMap& cell_estimator_id_data_map ) const = 0;

  //! Check if a cell exists
  virtual bool doesCellExist( const EntityId cell ) const = 0;

  //! Check if the cell is a termination cell
  virtual bool isTerminationCell( const EntityId cell ) const = 0;

  //! Check if a cell is void
  virtual bool isVoidCell( const EntityId cell ) const = 0;

  //! Get the cell volume
  virtual Volume getCellVolume( const EntityId cell ) const = 0;

  //! The invalid cell id
  static EntityId invalidCellId();

  //! The invalid surface id
  static EntityId invalidSurfaceId();

  //! The invalid material id
  static MaterialId invalidMaterialId();

  //! The invalid estimator id
  static EstimatorId invalidEstimatorId();

  //! Create a raw, heap-allocated navigator
  virtual Geometry::Navigator* createNavigatorAdvanced(
        const Navigator::AdvanceCompleteCallback& advance_complete_callback ) const = 0;

  //! Create a raw, heap-allocated navigator
  virtual Geometry::Navigator* createNavigatorAdvanced() const;

  //! Create a navigator
  std::shared_ptr<Geometry::Navigator> createNavigator(
          const Navigator::AdvanceCompleteCallback& advance_complete_callback =
          Navigator::AdvanceCompleteCallback() ) const;

  //! Check if the model has been initialized
  virtual bool isInitialized() const = 0;  

protected:

  //! Initialize the model just-in-time
  virtual void initializeJustInTime() = 0;

private:

  // Save the model to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const
  { /* ... */ }

  // Load the model from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version )
  { /* ... */ }

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

// Check if this is an advanced model
inline bool Model::isAdvanced() const
{
  return false;
}

// Create a raw, heap-allocated navigator
inline Geometry::Navigator* Model::createNavigatorAdvanced() const
{
  return this->createNavigatorAdvanced( Navigator::AdvanceCompleteCallback() );
}

// Create a navigator
inline std::shared_ptr<Geometry::Navigator> Model::createNavigator(
             const Navigator::AdvanceCompleteCallback& advance_callback ) const
{
  return std::shared_ptr<Geometry::Navigator>(
                           this->createNavigatorAdvanced( advance_callback ) );
}

} // end Geometry namespace

BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS( Model, Geometry );
BOOST_SERIALIZATION_CLASS_VERSION( Model, Geometry, 0 );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Geometry, Model );

#endif // end GEOMETRY_MODEL_HPP

//---------------------------------------------------------------------------//
// end Geometry_Model.hpp
//---------------------------------------------------------------------------//
