//---------------------------------------------------------------------------//
//!
//! \file   Geometry_InfiniteMediumModel.cpp
//! \author Alex Robinson
//! \brief  The infinite medium geometry model class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// Boost Includes
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>

// FRENSIE Includes
#include "Geometry_InfiniteMediumModel.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"

namespace Geometry{

// Constructor
InfiniteMediumModel::InfiniteMediumModel(
                                  const ModuleTraits::InternalCellHandle cell )
  : Model(),
    d_cell( cell )
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
/*! \details By default the infinite medium is void.
 */
void InfiniteMediumModel::getMaterialIds( MaterialIdSet& ) const
{ /* ... */ }

// Get the cells
/*! \details By default there will only be a single cell with an id of 1.
 */
void InfiniteMediumModel::getCells( CellIdSet& cells,
                                    const bool include_void_cells,
                                    const bool ) const
{
  if( include_void_cells )
    cells.insert( d_cell );
}

// Get the cell material ids
/*! \details By default the infinite medium is void.
 */
void InfiniteMediumModel::getCellMaterialIds( CellIdMatIdMap& ) const
{ /* ... */ }

// Get the cell densities
/*! \details By default the infinite medium is void.
 */
void InfiniteMediumModel::getCellDensities( CellIdDensityMap& ) const
{ /* ... */ }

// Get the cell estimator data
void InfiniteMediumModel::getCellEstimatorData( CellEstimatorIdDataMap& ) const
{ /* ... */ }

// Check if a cell exists
bool InfiniteMediumModel::doesCellExist(
                            const ModuleTraits::InternalCellHandle cell ) const
{
  if( cell == d_cell )
    return true;
  else
    return false;
}

// Check if the cell is a termination cell
/*! \details An infinite medium has no termination cell.
 */
bool InfiniteMediumModel::isTerminationCell(
                                 const ModuleTraits::InternalCellHandle ) const
{
  return false;
}

// Check if a cell is void
/*! \details By default there will only be a single void cell with an id of 1.
 */
bool InfiniteMediumModel::isVoidCell(
                            const ModuleTraits::InternalCellHandle cell ) const
{
  if( cell == d_cell )
    return true;
  else
    return false;
}

// Get the cell volume
double InfiniteMediumModel::getCellVolume(
                            const ModuleTraits::InternalCellHandle cell ) const
{
  if( cell == d_cell )
    return std::numeric_limits<double>::infinity();
  else
    return 0.0;
}

// Create a raw, heap-allocated navigator
InfiniteMediumNavigator* InfiniteMediumModel::createNavigatorAdvanced() const
{
  return new InfiniteMediumNavigator( d_cell );
}

// Save the model to an archive
template<typename Archive>
void InfiniteMediumModel::save( Archive& ar, const unsigned version ) const
{
  // Save the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( Model );
  
  // Save the local member data
  ar & BOOST_SERIALIZATION_NVP( d_cell );
}

// Load the model from an archive
template<typename Archive>
void InfiniteMediumModel::load( Archive& ar, const unsigned version )
{
  // Load the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( Model );
  
  // Load the local member data
  ar & BOOST_SERIALIZATION_NVP( d_cell );
}

EXPLICIT_GEOMETRY_CLASS_SAVE_LOAD_INST( InfiniteMediumModel );
  
} // end Geometry namespace

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( InfiniteMediumModel, Geometry );

//---------------------------------------------------------------------------//
// end Geometry_InfiniteMediumModel.cpp
//---------------------------------------------------------------------------//
