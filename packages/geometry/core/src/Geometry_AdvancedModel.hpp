//---------------------------------------------------------------------------//
//!
//! \file   Geometry_Model.hpp
//! \author Alex Robinson
//! \brief  The advanced geometry model base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_ADVANCED_MODEL_HPP
#define GEOMETRY_ADVANCED_MODEL_HPP

// FRENSIE Includes
#include "Geometry_Model.hpp"

namespace Geometry{

//! The advanced model base class
class AdvancedModel : public Model
{
  
public:

  //! The surface id set type
  typedef std::set<ModuleTraits::InternalSurfaceHandle> SurfaceIdSet;

  //! The surface id array type
  typedef std::vector<ModuleTraits::InternalSurfaceHandle> SurfaceIdArray;

  //! The surface estimator data type
  typedef std::tuple<EstimatorType,ParticleType,SurfaceIdArray> SurfaceEstimatorData;

  //! surface estimator id data map type
  typedef std::map<ModuleTraits::InternalEstimatorHandle,SurfaceEstimatorData> SurfaceEstimatorIdDataMap;

  //! Constructor
  AdvancedModel()
  { /* ... */ }

  //! Destructor
  virtual ~AdvancedModel()
  { /* ... */ }

  //! Check if this is an advanced model
  bool isAdvanced() const override;

  //! Check if the model has surface estimator data
  virtual bool hasSurfaceEstimatorData() const = 0;

  //! Get the surfaces
  virtual void getSurfaces( SurfaceIdSet& surfaces ) const = 0;

  //! Get the surface estimator data
  virtual void getSurfaceEstimatorData( SurfaceEstimatorIdDataMap& surface_estimator_id_data_map ) const = 0;

  //! Check if a surface exists
  virtual bool doesSurfaceExist(
              const ModuleTraits::InternalSurfaceHandle surface_id ) const = 0;

  //! Get the surface area
  virtual double getSurfaceArea(
              const ModuleTraits::InternalSurfaceHandle surface_id ) const = 0;

  //! Check if the surface is a reflecting surface
  virtual bool isReflectingSurface(
              const ModuleTraits::InternalSurfaceHandle surface_id ) const = 0;
};

// Check if this is an advanced model
inline bool AdvancedModel::isAdvanced() const
{
  return true;
}
  
} // end Geometry namespace

#endif // end GEOMETRY_ADVANCED_MODEL_HPP

//---------------------------------------------------------------------------//
// end Geometry_AdvancedModel.hpp
//---------------------------------------------------------------------------//
