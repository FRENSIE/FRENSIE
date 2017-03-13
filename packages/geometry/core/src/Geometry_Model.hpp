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
#include <unordered_map>
#include <memory>

// FRENSIE Includes
#include "Geometry_ModuleTraits.hpp"
#include "Geometry_Navigator.hpp"
#include "Utility_ContractException.hpp"

namespace Geometry{

//! The model base class
class Model
{

public:

  //! The material id set type
  typedef std::unordered_set<ModuleTraits::InternalMaterialHandle> MaterialIdSet;

  //! The cell set type
  typedef std::unordered_set<ModuleTraits::InternalCellHandle> CellSet;

  //! The cell id material id map type
  typedef std::unordered_map<ModuleTraits::InternalCellHandle,ModuleTraits::InternalMaterialHandle> CellIdMatIdMap;

  //! The cell id density map type
  typedef std::unordered_map<ModuleTraits::InternalCellHandle,double> CellIdDensityMap;

  //! Constructor
  Model()
  { /* ... */ }

  //! Destructor
  virtual ~Model()
  { /* ... */ }

  //! Get the material ids
  virtual void getMaterialIds( MaterialIdSet& material_ids ) const = 0;

  //! Get the cells
  virtual void getCells( CellSet& cells,
                         const bool include_void_cells,
                         const bool include_termination_cells ) const = 0;

  //! Get the cell material ids
  virtual void getCellMaterialIds(
                                CellIdMatIdMap& cell_id_mat_id_map ) const = 0;

  //! Get the cell densities
  virtual void getCellDensities( CellDensityMap& cell_density_map ) const = 0;

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
  virtual std::shared_ptr<Navigator> createNavigator() const = 0;
};
  
} // end Geometry namespace

#endif // end GEOMETRY_MODEL_HPP

//---------------------------------------------------------------------------//
// end Geometry_Model.hpp
//---------------------------------------------------------------------------//
