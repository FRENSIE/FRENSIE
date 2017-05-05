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

namespace Geometry{

//! The infinite medium model
class InfiniteMediumModel : public Model
{

public:

  //! Constructor
  InfiniteMediumModel( const ModuleTraits::InternalCellHandle cell = 1 );

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
  void getCells( CellIdSet& cells,
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
  bool doesCellExist(
                  const ModuleTraits::InternalCellHandle cell ) const override;

  //! Check if the cell is a termination cell
  bool isTerminationCell(
                  const ModuleTraits::InternalCellHandle cell ) const override;

  //! Check if a cell is void
  bool isVoidCell(
                  const ModuleTraits::InternalCellHandle cell ) const override;

  //! Get the cell volume
  double getCellVolume(
                  const ModuleTraits::InternalCellHandle cell ) const override;

  //! Create a raw, heap-allocated navigator
  InfiniteMediumNavigator* createNavigatorAdvanced() const override;

private:

  // The infinite medium cell id
  ModuleTraits::InternalCellHandle d_cell;
};
  
} // end Geometry namespace

#endif // end GEOMETRY_INFINITE_MEDIUM_MODEL_HPP

//---------------------------------------------------------------------------//
// end Geometry_InfiniteMediumModel.hpp
//---------------------------------------------------------------------------//
