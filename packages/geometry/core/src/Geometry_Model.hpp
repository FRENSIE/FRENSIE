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
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <map>
#include <vector>
#include <memory>
#include <tuple>
#include <iostream>

// FRENSIE Includes
#include "Geometry_ModuleTraits.hpp"
#include "Geometry_Navigator.hpp"
#include "Geometry_EstimatorType.hpp"
#include "Geometry_ParticleType.hpp"
#include "Utility_ContractException.hpp"

namespace Geometry{

//! The model base class
class Model
{

public:

  //! The material id set type
  typedef std::set<ModuleTraits::InternalMaterialHandle> MaterialIdSet;

  //! The cell id set type
  typedef std::set<ModuleTraits::InternalCellHandle> CellIdSet;

  //! The cell id material id map type
  typedef std::map<ModuleTraits::InternalCellHandle,ModuleTraits::InternalMaterialHandle> CellIdMatIdMap;

  //! The cell id density map type
  typedef std::map<ModuleTraits::InternalCellHandle,double> CellIdDensityMap;

  //! The cell id array type
  typedef std::vector<ModuleTraits::InternalCellHandle> CellIdArray;

  //! The cell estimator data type
  typedef std::tuple<EstimatorType,ParticleType,CellIdArray> CellEstimatorData;

  //! The cell estimator id data map type
  typedef std::map<ModuleTraits::InternalEstimatorHandle,CellEstimatorData> CellEstimatorIdDataMap;

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
  virtual void getCells( CellIdSet& cells,
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
  virtual bool doesCellExist(
                       const ModuleTraits::InternalCellHandle cell ) const = 0;

  //! Check if the cell is a termination cell
  virtual bool isTerminationCell(
                       const ModuleTraits::InternalCellHandle cell ) const = 0;

  //! Check if a cell is void
  virtual bool isVoidCell(
                       const ModuleTraits::InternalCellHandle cell ) const = 0;

  //! Get the cell volume
  virtual double getCellVolume(
                       const ModuleTraits::InternalCellHandle cell ) const = 0;

  //! Create a navigator
  virtual std::shared_ptr<Geometry::Navigator> createNavigator() const = 0;
};

// Check if this is an advanced model
inline bool Model::isAdvanced() const
{
  return false;
}
  
} // end Geometry namespace

#endif // end GEOMETRY_MODEL_HPP

//---------------------------------------------------------------------------//
// end Geometry_Model.hpp
//---------------------------------------------------------------------------//
