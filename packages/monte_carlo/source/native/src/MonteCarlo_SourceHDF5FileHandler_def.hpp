//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SourceHDF5FileHandler_def.hpp
//! \author Alex Robinson
//! \brief  Source HDF5 file handler class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SOURCE_HDF5_FILE_HANDLER_DEF_HPP
#define MONTE_CARLO_SOURCE_HDF5_FILE_HANDLER_DEF_HPP

// Std Lib Includes
#include <vector>

namespace MonteCarlo{

// Set the start cell cache
template<template<typename,typename...> class StdCompliantSet>
void SourceHDF5FileHandler::setStartCellCache(
                               const ModuleTraits::InternalROIHandle source_id,
                               const StdCompliantSet<Geometry::ModuleTraits::InternalCellHandle>& starting_cell_cache )
{
  std::vector<Geometry::ModuleTraits::InternalCellHandle> starting_cells(
                                                   starting_cell_cache.begin(),
                                                   starting_cell_cache.end() );

  std::string starting_cells_location =
    this->getSourceGroupLocation( source_id );

  starting_cells_location += "start_cell_cache";

  try{
    this->getHDF5File().writeArrayToDataSet( starting_cells,
                                             starting_cells_location );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "Unable to set the starting cell cache for source "
                           << source_id << "!" );
}

// Get the start cell cache
template<template<typename,typename...> class StdCompliantSet>
void SourceHDF5FileHandler::getStartCellCache(
                               const ModuleTraits::InternalROIHandle source_id,
                               StdCompliantSet<Geometry::ModuleTraits::InternalCellHandle>& starting_cell_cache )
{
  std::string starting_cells_location =
    this->getSourceGroupLocation( source_id );

  starting_cells_location += "start_cell_cache";

  std::vector<Geometry::ModuleTraits::InternalCellHandle> starting_cells;

  try{
    this->getHDF5File().readArrayFromDataSet( starting_cells,
                                              starting_cells_location );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "Unable to get the starting cell cache for source "
                           << source_id << "!" );

  starting_cell_cache.insert( starting_cells.begin(), starting_cells.end() );
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SOURCE_HDF5_FILE_HANDLER_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SourceHDF5FileHandler_def.hpp
//---------------------------------------------------------------------------//
