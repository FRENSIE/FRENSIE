//---------------------------------------------------------------------------//
//!
//! \file   tstParticleTrackerHDF5FileHandler.cpp
//! \author Eli Moll
//! \brief  Particle tracker hdf5 file handler unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <string>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_UnitTestHarnessExtensions.hpp"
#include "MonteCarlo_ParticleTrackerHDF5FileHandler.hpp"
#include "MonteCarlo_PhaseSpaceDimension.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_HDF5FileHandler.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::ParticleTrackerHDF5FileHandler> file_handler;
std::string hdf5_file_name( "test_particle_tracker.h5" );
MonteCarlo::ParticleTrackerHDF5FileHandler::OverallHistoryMap 
  history_number_map;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the handler can be constructed, written to, and read from
TEUCHOS_UNIT_TEST( ParticleTrackerHDF5FileHandler, constructor_ownership )
{
  // Construct a sample data map for manipulation
  std::vector< double > x_pos;
  x_pos.push_back( 1.0 );
  
  std::vector< double > y_pos;
  y_pos.push_back( 1.0 );
  
  std::vector< double > z_pos;
  z_pos.push_back( 1.0 );
  
  std::vector< double > x_dir;
  x_dir.push_back( 1.0 );
  
  std::vector< double > y_dir;
  y_dir.push_back( 0.0 );
  
  std::vector< double > z_dir;
  z_dir.push_back( 0.0 );
  
  std::vector< double > energy;
  energy.push_back( 2.0 );
  
  std::vector< double > col_num;
  col_num.push_back( 0.0 );
  
  std::vector< double > weight;
  weight.push_back( 1.0 );

  MonteCarlo::ParticleTrackerHDF5FileHandler::ParticleDataTwoDArray 
    particle_data;

  // Start by adding the arrays of data to the total particle array
  particle_data.push_back( x_pos );
  particle_data.push_back( y_pos );
  particle_data.push_back( z_pos );
  particle_data.push_back( x_dir );
  particle_data.push_back( y_dir );
  particle_data.push_back( z_dir );
  particle_data.push_back( energy );
  particle_data.push_back( col_num );
  particle_data.push_back( weight );

  // Map of individual particles to array of particle data
  MonteCarlo::ParticleTrackerHDF5FileHandler::IndividualParticleSubmap 
    individual_particle_map;
  individual_particle_map[ 0u ] = particle_data;

  // Map of generation number to individual particles
  MonteCarlo::ParticleTrackerHDF5FileHandler::GenerationNumberSubmap 
    generation_number_map;
  generation_number_map[ 0u ] = individual_particle_map;
    
  // Map of particle type to generation number
  MonteCarlo::ParticleTrackerHDF5FileHandler::ParticleTypeSubmap 
    particle_type_map;
  particle_type_map[ MonteCarlo::PHOTON ] = generation_number_map;

  // Map of the history number to the particle type map
  history_number_map[ 0u ] = particle_type_map;
  
  TEST_NOTHROW( file_handler.reset( 
		new MonteCarlo::ParticleTrackerHDF5FileHandler( hdf5_file_name ) ) );
		
  // Make sure setter methods work
  TEST_NOTHROW( file_handler->setParticleTrackerData( history_number_map ) );
  
  file_handler.reset();
  
  TEST_NOTHROW( file_handler.reset( 
    new MonteCarlo::ParticleTrackerHDF5FileHandler(
	    hdf5_file_name,
	    MonteCarlo::ParticleTrackerHDF5FileHandler::APPEND_PTRACK_HDF5_FILE ) ) );

  // Make sure file has not been overwritten
  std::string data_location = "/Particle_Tracker/0/0/0/0/";

  std::vector< double > sample_x_pos;
  file_handler->getXPositionData( data_location, sample_x_pos );
  
  UTILITY_TEST_COMPARE_ARRAYS( sample_x_pos, x_pos );

  file_handler.reset();

  TEST_NOTHROW( file_handler.reset( new MonteCarlo::ParticleTrackerHDF5FileHandler(
     hdf5_file_name,
     MonteCarlo::ParticleTrackerHDF5FileHandler::READ_ONLY_PTRACK_HDF5_FILE ) ) );

  TEST_THROW( file_handler->setParticleTrackerData( history_number_map ), 
                                                    std::runtime_error );

  // Reset the file
  file_handler.reset();
  file_handler.reset(
		  new MonteCarlo::ParticleTrackerHDF5FileHandler( hdf5_file_name ) );
}

//---------------------------------------------------------------------------//
// end tstParticleTrackerHDF5FileHandler.cpp
//---------------------------------------------------------------------------//
