//---------------------------------------------------------------------------//
//!
//! \file   Geometry_InfiniteMediumModel.cpp
//! \author Alex Robinson
//! \brief  The infinite medium geometry model class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "FRENSIE_Archives.hpp" // Must be included first
#include "Geometry_InfiniteMediumModel.hpp"

namespace Geometry{

// Constructor
InfiniteMediumModel::InfiniteMediumModel(
                               const EntityId cell,
                               const Model::MaterialId material_id,
                               const Model::Density density )
  : Model(),
    d_cell( cell ),
    d_material_id( material_id ),
    d_density( density )
{ /* ... */ }

// Get the model name
std::string InfiniteMediumModel::getName() const
{
  return "Infinite Medium";
}

// Check if the model has cell estimator data
bool InfiniteMediumModel::hasCellEstimatorData() const
{
  return false;
}

// Get the material ids
void InfiniteMediumModel::getMaterialIds( MaterialIdSet& material_ids ) const
{
  material_ids.insert( d_material_id );
}

// Get the cells
void InfiniteMediumModel::getCells( CellIdSet& cell_set,
                                    const bool include_void_cells,
                                    const bool ) const
{
  if( d_density == 0.0*Model::DensityUnit() )
  {
    if( include_void_cells )
      cell_set.insert( d_cell );
  }
  else
    cell_set.insert( d_cell );
}

// Get the cell material ids
void InfiniteMediumModel::getCellMaterialIds(
                                     CellIdMatIdMap& cell_id_mat_id_map ) const
{
  cell_id_mat_id_map[d_cell] = d_material_id;
}

// Get the cell densities
void InfiniteMediumModel::getCellDensities(
                                  CellIdDensityMap& cell_id_density_map ) const
{
  cell_id_density_map[d_cell] = d_density;
}

// Get the cell estimator data
void InfiniteMediumModel::getCellEstimatorData( CellEstimatorIdDataMap& ) const
{ /* ... */ }

// Check if a cell exists
bool InfiniteMediumModel::doesCellExist( const EntityId cell ) const
{
  if( cell == d_cell )
    return true;
  else
    return false;
}

// Check if the cell is a termination cell
/*! \details An infinite medium has no termination cell.
 */
bool InfiniteMediumModel::isTerminationCell( const EntityId ) const
{
  return false;
}

// Check if a cell is void
bool InfiniteMediumModel::isVoidCell( const EntityId cell ) const
{
  if( cell == d_cell )
  {
    if( d_density == 0.0*Model::DensityUnit() )
      return true;
    else
      return false;
  }
}

// Get the cell volume
auto InfiniteMediumModel::getCellVolume(
                                const EntityId cell ) const -> Volume
{
  if( cell == d_cell )
    return Utility::QuantityTraits<Volume>::inf();
  else
    return Utility::QuantityTraits<Volume>::zero();
}

// Create a raw, heap-allocated navigator
InfiniteMediumNavigator* InfiniteMediumModel::createNavigatorAdvanced(
    const Navigator::AdvanceCompleteCallback& advance_complete_callback ) const
{
  return new InfiniteMediumNavigator( d_cell, advance_complete_callback );
}

// Create a raw, heap-allocated navigator (no callback)
InfiniteMediumNavigator* InfiniteMediumModel::createNavigatorAdvanced() const
{
  return new InfiniteMediumNavigator( d_cell );
}

// Check if the model has been initialized
bool InfiniteMediumModel::isInitialized() const
{
  return true;
}

// Initialize the model just-in-time
void InfiniteMediumModel::initializeJustInTime()
{ /* ... */ }
  
} // end Geometry namespace

EXPLICIT_CLASS_SAVE_LOAD_INST( Geometry::InfiniteMediumModel );
BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( InfiniteMediumModel, Geometry );

//---------------------------------------------------------------------------//
// end Geometry_InfiniteMediumModel.cpp
//---------------------------------------------------------------------------//
