//---------------------------------------------------------------------------//
//!
//! \file   tstSourceHDF5FileHandler.cpp
//! \author Alex Robinson
//! \brief  Source hdf5 file handler unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <string>
#include <set>
#include <unordered_set>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_SourceHDF5FileHandler.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_HDF5FileHandler.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

const std::string hdf5_file_name( "test_source.h5" );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that source trials can be set
TEUCHOS_UNIT_TEST( SourceHDF5FileHandler, setNumberOfSourceSamplingTrials )
{
  MonteCarlo::SourceHDF5FileHandler file_handler( hdf5_file_name );

  file_handler.setNumberOfSourceSamplingTrials( 0, 10000ull );
  file_handler.setNumberOfSourceSamplingTrials( 1, 1001ull );

  TEST_EQUALITY_CONST( file_handler.getNumberOfSourceSamplingTrials( 0 ),
                       10000ull );
  TEST_EQUALITY_CONST( file_handler.getNumberOfSourceSamplingTrials( 1 ),
                       1001ull );
}

//---------------------------------------------------------------------------//
// Check that source samples can be set
TEUCHOS_UNIT_TEST( SourceHDF5FileHandler, setNumberOfSourceSamples )
{
  MonteCarlo::SourceHDF5FileHandler file_handler( hdf5_file_name );

  file_handler.setNumberOfSourceSamples( 0, 10000ull );
  file_handler.setNumberOfSourceSamples( 1, 1001ull );

  TEST_EQUALITY_CONST( file_handler.getNumberOfSourceSamples( 0 ), 10000ull );
  TEST_EQUALITY_CONST( file_handler.getNumberOfSourceSamples( 1 ), 1001ull );
}

//---------------------------------------------------------------------------//
// Check that the number of source dimension sampling trials can be set
TEUCHOS_UNIT_TEST( SourceHDF5FileHandler,
                   setNumberOfSourceDimensionSamplingTrials )
{
  MonteCarlo::SourceHDF5FileHandler file_handler( hdf5_file_name );

  file_handler.setNumberOfSourceDimensionSamplingTrials( 0, MonteCarlo::PRIMARY_SPATIAL_DIMENSION, 100 );
  file_handler.setNumberOfSourceDimensionSamplingTrials( 1, MonteCarlo::PRIMARY_SPATIAL_DIMENSION, 101 );

  file_handler.setNumberOfSourceDimensionSamplingTrials( 0, MonteCarlo::SECONDARY_SPATIAL_DIMENSION, 200 );
  file_handler.setNumberOfSourceDimensionSamplingTrials( 1, MonteCarlo::SECONDARY_SPATIAL_DIMENSION, 201 );

  file_handler.setNumberOfSourceDimensionSamplingTrials( 0, MonteCarlo::TERTIARY_SPATIAL_DIMENSION, 300 );
  file_handler.setNumberOfSourceDimensionSamplingTrials( 1, MonteCarlo::TERTIARY_SPATIAL_DIMENSION, 301 );

  file_handler.setNumberOfSourceDimensionSamplingTrials( 0, MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION, 400 );
  file_handler.setNumberOfSourceDimensionSamplingTrials( 1, MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION, 401 );

  file_handler.setNumberOfSourceDimensionSamplingTrials( 0, MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION, 500 );
  file_handler.setNumberOfSourceDimensionSamplingTrials( 1, MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION, 501 );

  file_handler.setNumberOfSourceDimensionSamplingTrials( 0, MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION, 600 );
  file_handler.setNumberOfSourceDimensionSamplingTrials( 1, MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION, 601 );
  
  file_handler.setNumberOfSourceDimensionSamplingTrials( 0, MonteCarlo::ENERGY_DIMENSION, 700 );
  file_handler.setNumberOfSourceDimensionSamplingTrials( 1, MonteCarlo::ENERGY_DIMENSION, 701 );

  file_handler.setNumberOfSourceDimensionSamplingTrials( 0, MonteCarlo::TIME_DIMENSION, 800 );
  file_handler.setNumberOfSourceDimensionSamplingTrials( 1, MonteCarlo::TIME_DIMENSION, 801 );

  file_handler.setNumberOfSourceDimensionSamplingTrials( 0, MonteCarlo::WEIGHT_DIMENSION, 900 );
  file_handler.setNumberOfSourceDimensionSamplingTrials( 1, MonteCarlo::WEIGHT_DIMENSION, 901 );
  
  TEST_EQUALITY_CONST( file_handler.getNumberOfSourceDimensionSamplingTrials( 0, MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 100 );
  TEST_EQUALITY_CONST( file_handler.getNumberOfSourceDimensionSamplingTrials( 1, MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 101 );
  TEST_EQUALITY_CONST( file_handler.getNumberOfSourceDimensionSamplingTrials( 0, MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 200 );
  TEST_EQUALITY_CONST( file_handler.getNumberOfSourceDimensionSamplingTrials( 1, MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 201 );
  TEST_EQUALITY_CONST( file_handler.getNumberOfSourceDimensionSamplingTrials( 0, MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 300 );
  TEST_EQUALITY_CONST( file_handler.getNumberOfSourceDimensionSamplingTrials( 1, MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 301 );
  TEST_EQUALITY_CONST( file_handler.getNumberOfSourceDimensionSamplingTrials( 0, MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 400 );
  TEST_EQUALITY_CONST( file_handler.getNumberOfSourceDimensionSamplingTrials( 1, MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 401 );
  TEST_EQUALITY_CONST( file_handler.getNumberOfSourceDimensionSamplingTrials( 0, MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 500 );
  TEST_EQUALITY_CONST( file_handler.getNumberOfSourceDimensionSamplingTrials( 1, MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 501 );
  TEST_EQUALITY_CONST( file_handler.getNumberOfSourceDimensionSamplingTrials( 0, MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 600 );
  TEST_EQUALITY_CONST( file_handler.getNumberOfSourceDimensionSamplingTrials( 1, MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 601 );
  TEST_EQUALITY_CONST( file_handler.getNumberOfSourceDimensionSamplingTrials( 0, MonteCarlo::ENERGY_DIMENSION ), 700 );
  TEST_EQUALITY_CONST( file_handler.getNumberOfSourceDimensionSamplingTrials( 1, MonteCarlo::ENERGY_DIMENSION ), 701 );
  TEST_EQUALITY_CONST( file_handler.getNumberOfSourceDimensionSamplingTrials( 0, MonteCarlo::TIME_DIMENSION ), 800 );
  TEST_EQUALITY_CONST( file_handler.getNumberOfSourceDimensionSamplingTrials( 1, MonteCarlo::TIME_DIMENSION ), 801 );
  TEST_EQUALITY_CONST( file_handler.getNumberOfSourceDimensionSamplingTrials( 0, MonteCarlo::WEIGHT_DIMENSION ), 900 );
  TEST_EQUALITY_CONST( file_handler.getNumberOfSourceDimensionSamplingTrials( 1, MonteCarlo::WEIGHT_DIMENSION ), 901 );
}

//---------------------------------------------------------------------------//
// Check that the number of source dimension samples can be set
TEUCHOS_UNIT_TEST( SourceHDF5FileHandler,
                   setNumberOfSourceDimensionSamples )
{
  MonteCarlo::SourceHDF5FileHandler file_handler( hdf5_file_name );

  file_handler.setNumberOfSourceDimensionSamples( 0, MonteCarlo::PRIMARY_SPATIAL_DIMENSION, 100 );
  file_handler.setNumberOfSourceDimensionSamples( 1, MonteCarlo::PRIMARY_SPATIAL_DIMENSION, 101 );

  file_handler.setNumberOfSourceDimensionSamples( 0, MonteCarlo::SECONDARY_SPATIAL_DIMENSION, 200 );
  file_handler.setNumberOfSourceDimensionSamples( 1, MonteCarlo::SECONDARY_SPATIAL_DIMENSION, 201 );

  file_handler.setNumberOfSourceDimensionSamples( 0, MonteCarlo::TERTIARY_SPATIAL_DIMENSION, 300 );
  file_handler.setNumberOfSourceDimensionSamples( 1, MonteCarlo::TERTIARY_SPATIAL_DIMENSION, 301 );

  file_handler.setNumberOfSourceDimensionSamples( 0, MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION, 400 );
  file_handler.setNumberOfSourceDimensionSamples( 1, MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION, 401 );

  file_handler.setNumberOfSourceDimensionSamples( 0, MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION, 500 );
  file_handler.setNumberOfSourceDimensionSamples( 1, MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION, 501 );

  file_handler.setNumberOfSourceDimensionSamples( 0, MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION, 600 );
  file_handler.setNumberOfSourceDimensionSamples( 1, MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION, 601 );
  
  file_handler.setNumberOfSourceDimensionSamples( 0, MonteCarlo::ENERGY_DIMENSION, 700 );
  file_handler.setNumberOfSourceDimensionSamples( 1, MonteCarlo::ENERGY_DIMENSION, 701 );

  file_handler.setNumberOfSourceDimensionSamples( 0, MonteCarlo::TIME_DIMENSION, 800 );
  file_handler.setNumberOfSourceDimensionSamples( 1, MonteCarlo::TIME_DIMENSION, 801 );

  file_handler.setNumberOfSourceDimensionSamples( 0, MonteCarlo::WEIGHT_DIMENSION, 900 );
  file_handler.setNumberOfSourceDimensionSamples( 1, MonteCarlo::WEIGHT_DIMENSION, 901 );
  
  TEST_EQUALITY_CONST( file_handler.getNumberOfSourceDimensionSamples( 0, MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 100 );
  TEST_EQUALITY_CONST( file_handler.getNumberOfSourceDimensionSamples( 1, MonteCarlo::PRIMARY_SPATIAL_DIMENSION ), 101 );
  TEST_EQUALITY_CONST( file_handler.getNumberOfSourceDimensionSamples( 0, MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 200 );
  TEST_EQUALITY_CONST( file_handler.getNumberOfSourceDimensionSamples( 1, MonteCarlo::SECONDARY_SPATIAL_DIMENSION ), 201 );
  TEST_EQUALITY_CONST( file_handler.getNumberOfSourceDimensionSamples( 0, MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 300 );
  TEST_EQUALITY_CONST( file_handler.getNumberOfSourceDimensionSamples( 1, MonteCarlo::TERTIARY_SPATIAL_DIMENSION ), 301 );
  TEST_EQUALITY_CONST( file_handler.getNumberOfSourceDimensionSamples( 0, MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 400 );
  TEST_EQUALITY_CONST( file_handler.getNumberOfSourceDimensionSamples( 1, MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION ), 401 );
  TEST_EQUALITY_CONST( file_handler.getNumberOfSourceDimensionSamples( 0, MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 500 );
  TEST_EQUALITY_CONST( file_handler.getNumberOfSourceDimensionSamples( 1, MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION ), 501 );
  TEST_EQUALITY_CONST( file_handler.getNumberOfSourceDimensionSamples( 0, MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 600 );
  TEST_EQUALITY_CONST( file_handler.getNumberOfSourceDimensionSamples( 1, MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION ), 601 );
  TEST_EQUALITY_CONST( file_handler.getNumberOfSourceDimensionSamples( 0, MonteCarlo::ENERGY_DIMENSION ), 700 );
  TEST_EQUALITY_CONST( file_handler.getNumberOfSourceDimensionSamples( 1, MonteCarlo::ENERGY_DIMENSION ), 701 );
  TEST_EQUALITY_CONST( file_handler.getNumberOfSourceDimensionSamples( 0, MonteCarlo::TIME_DIMENSION ), 800 );
  TEST_EQUALITY_CONST( file_handler.getNumberOfSourceDimensionSamples( 1, MonteCarlo::TIME_DIMENSION ), 801 );
  TEST_EQUALITY_CONST( file_handler.getNumberOfSourceDimensionSamples( 0, MonteCarlo::WEIGHT_DIMENSION ), 900 );
  TEST_EQUALITY_CONST( file_handler.getNumberOfSourceDimensionSamples( 1, MonteCarlo::WEIGHT_DIMENSION ), 901 );
}

//---------------------------------------------------------------------------//
// Check that the start cell cache can be set
TEUCHOS_UNIT_TEST( SourceHDF5FileHandle, setStartCellCache )
{
  MonteCarlo::SourceHDF5FileHandler file_handler( hdf5_file_name );

  {
    std::set<Geometry::ModuleTraits::InternalCellHandle> start_cell_cache;
    start_cell_cache.insert( 1 );
    start_cell_cache.insert( 3 );
    start_cell_cache.insert( 201 );
    
    file_handler.setStartCellCache( 1, start_cell_cache );
  }

  std::set<Geometry::ModuleTraits::InternalCellHandle> start_cell_cache;
  file_handler.getStartCellCache( 1, start_cell_cache );

  TEST_EQUALITY_CONST( start_cell_cache.size(), 3 );
  TEST_ASSERT( start_cell_cache.count( 1 ) );
  TEST_ASSERT( start_cell_cache.count( 3 ) );
  TEST_ASSERT( start_cell_cache.count( 201 ) );

  {
    std::unordered_set<Geometry::ModuleTraits::InternalCellHandle> start_cell_cache;
    start_cell_cache.insert( 2 );
    start_cell_cache.insert( 51 );
    start_cell_cache.insert( 1023 );
    start_cell_cache.insert( 9 );

    file_handler.setStartCellCache( 2, start_cell_cache );
  }

  std::unordered_set<Geometry::ModuleTraits::InternalCellHandle>
    unordered_start_cell_cache;
  file_handler.getStartCellCache( 2, unordered_start_cell_cache );

  TEST_EQUALITY_CONST( unordered_start_cell_cache.size(), 4 );
  TEST_ASSERT( unordered_start_cell_cache.count( 2 ) );
  TEST_ASSERT( unordered_start_cell_cache.count( 51 ) );
  TEST_ASSERT( unordered_start_cell_cache.count( 1023 ) );
  TEST_ASSERT( unordered_start_cell_cache.count( 9 ) );
}

//---------------------------------------------------------------------------//
// Check if sources exist
TEUCHOS_UNIT_TEST( SourceHDF5FileHandler, doesSourceExist )
{
  MonteCarlo::SourceHDF5FileHandler file_handler( hdf5_file_name );

  file_handler.setNumberOfSourceSamplingTrials( 0, 0ull );
  file_handler.setNumberOfSourceSamples( 0, 0ull );

  file_handler.setNumberOfSourceSamplingTrials( 1, 0ull );
  file_handler.setNumberOfSourceSamples( 1, 0ull );

  TEST_ASSERT( file_handler.doesSourceExist( 0 ) );
  TEST_ASSERT( file_handler.doesSourceExist( 1 ) );
  TEST_ASSERT( !file_handler.doesSourceExist( 2 ) );
}

//---------------------------------------------------------------------------//
// Check if a source dimension has data
TEUCHOS_UNIT_TEST( SourceHDF5FileHandler, doesSourceDimensionExist )
{
  MonteCarlo::SourceHDF5FileHandler file_handler( hdf5_file_name );

  file_handler.setNumberOfSourceSamplingTrials( 0, 1 );
  file_handler.setNumberOfSourceSamples( 0, 1 );
  file_handler.setNumberOfSourceDimensionSamplingTrials( 0, MonteCarlo::ENERGY_DIMENSION, 10 );
  file_handler.setNumberOfSourceDimensionSamples( 0, MonteCarlo::ENERGY_DIMENSION, 10 );

  file_handler.setNumberOfSourceSamplingTrials( 1, 2 );
  file_handler.setNumberOfSourceSamples( 1, 2 );
  file_handler.setNumberOfSourceDimensionSamplingTrials( 1, MonteCarlo::TIME_DIMENSION, 20 );
  file_handler.setNumberOfSourceDimensionSamples( 1, MonteCarlo::TIME_DIMENSION, 20 );

  TEST_ASSERT( file_handler.doesSourceDimensionExist( 0, MonteCarlo::ENERGY_DIMENSION ) );
  TEST_ASSERT( !file_handler.doesSourceDimensionExist( 0, MonteCarlo::TIME_DIMENSION ) );
  TEST_ASSERT( !file_handler.doesSourceDimensionExist( 1, MonteCarlo::ENERGY_DIMENSION ) );
  TEST_ASSERT( file_handler.doesSourceDimensionExist( 1, MonteCarlo::TIME_DIMENSION ) );
}

//---------------------------------------------------------------------------//
// end tstSourceHDF5FileHandler.cpp
//---------------------------------------------------------------------------//
