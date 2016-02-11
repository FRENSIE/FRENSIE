//---------------------------------------------------------------------------//
//!
//! \file   tstParticleTracker.cpp
//! \author Eli Moll
//! \brief  Particle Tracker unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleTracker.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "MonteCarlo_ParticleTrackerHDF5FileHandler.hpp"

//---------------------------------------------------------------------------//

// Construct a particle tracker
MonteCarlo::ParticleTracker particle_tracker( 1u );

// Construct a sample particle
MonteCarlo::PhotonState particle( 0u );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the data is updated appropriately in the GlobalSubtrackEndingEvent
TEUCHOS_UNIT_TEST( ParticleTracker, testUpdateFromGlobalSubtrackEndingEvent )
{                         
  // Initial particle state
  particle.setPosition( 1.0, 1.0, 1.0 );
  particle.setDirection( 1.0, 0.0, 0.0 );
  particle.setEnergy( 2.5 );
  particle.setWeight( 1.0 );
  
  // Start and end positions
  double start_point[3] = { 1.0, 1.0, 1.0 };
  double end_point[3] = { 2.0, 1.0, 1.0 };
  
  particle_tracker.updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                                start_point,
                                                                end_point );
  
  // Final particle state
  particle.setPosition( 2.0, 1.0, 1.0 );
  particle.setDirection( 1.0, 0.0, 0.0 );
  particle.setEnergy( 2.5 );
  particle.setWeight( 1.0 );
  
  // Start and end positions
  start_point[0] = 2.0;
  
  particle_tracker.updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                                start_point,
                                                                end_point );
  
  // Expected data
  Teuchos::Array< double > input_x_position;
  input_x_position.push_back( 1.0 );
  input_x_position.push_back( 2.0 );
  
  Teuchos::Array< double > input_y_position;
  input_y_position.push_back( 1.0 );
  input_y_position.push_back( 1.0 );
  
  Teuchos::Array< double > input_z_position;
  input_z_position.push_back( 1.0 );
  input_z_position.push_back( 1.0 );
  
  Teuchos::Array< double > input_x_direction;
  input_x_direction.push_back( 1.0 );
  input_x_direction.push_back( 1.0 );
  
  Teuchos::Array< double > input_y_direction;
  input_y_direction.push_back( 0.0 );
  input_y_direction.push_back( 0.0 );
  
  Teuchos::Array< double > input_z_direction;
  input_z_direction.push_back( 0.0 );
  input_z_direction.push_back( 0.0 );
  
  Teuchos::Array< double > input_energy;
  input_energy.push_back( 2.5 );
  input_energy.push_back( 2.5 );
  
  Teuchos::Array< double > input_collision_number;
  input_collision_number.push_back( 0.0 );
  input_collision_number.push_back( 0.0 );
  
  Teuchos::Array< double > input_weight;
  input_weight.push_back( 1.0 );
  input_weight.push_back( 1.0 );
  
  
  // Define and populate the output data                              
  Teuchos::Array< double > output_x_position;
  particle_tracker.getXPositionData( output_x_position );
  
  Teuchos::Array< double > output_y_position;
  particle_tracker.getYPositionData( output_y_position );
  
  Teuchos::Array< double > output_z_position;
  particle_tracker.getZPositionData( output_z_position );
  
  Teuchos::Array< double > output_x_direction;
  particle_tracker.getXDirectionData( output_x_direction );
  
  Teuchos::Array< double > output_y_direction;
  particle_tracker.getYDirectionData( output_y_direction );
  
  Teuchos::Array< double > output_z_direction;
  particle_tracker.getZDirectionData( output_z_direction );
  
  Teuchos::Array< double > output_energy;
  particle_tracker.getEnergyData( output_energy );
  
  Teuchos::Array< double > output_collision_number;
  particle_tracker.getCollisionNumberData( output_collision_number );
  
  Teuchos::Array< double > output_weight;
  particle_tracker.getWeightData( output_weight );

  UTILITY_TEST_COMPARE_ARRAYS( input_x_position, output_x_position );
  UTILITY_TEST_COMPARE_ARRAYS( input_y_position, output_y_position );
  UTILITY_TEST_COMPARE_ARRAYS( input_z_position, output_z_position );
  
  UTILITY_TEST_COMPARE_ARRAYS( input_x_direction, output_x_direction );
  UTILITY_TEST_COMPARE_ARRAYS( input_y_direction, output_y_direction );
  UTILITY_TEST_COMPARE_ARRAYS( input_z_direction, output_z_direction );
  
  UTILITY_TEST_COMPARE_ARRAYS( input_energy, output_energy );
  UTILITY_TEST_COMPARE_ARRAYS( input_collision_number, output_collision_number );
  UTILITY_TEST_COMPARE_ARRAYS( input_weight, output_weight );
}

// Check that the data is committed appropriately
TEUCHOS_UNIT_TEST( ParticleTracker, testcommitParticleTrackData )
{

  // Final particle state
  particle.setPosition( 2.0, 1.0, 1.0 );
  particle.setDirection( 1.0, 0.0, 0.0 );
  particle.setEnergy( 2.5 );
  particle.setWeight( 1.0 );
  particle.setAsGone();
  
  // Start and end positions
  double start_point[3] = { 2.0, 1.0, 1.0 };
  double end_point[3] = { 2.0, 1.0, 1.0 };
  
  particle_tracker.updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                                start_point,
                                                                end_point );
  
  // Expected data
  Teuchos::Array< double > input_x_position;
  input_x_position.push_back( 1.0 );
  input_x_position.push_back( 2.0 );                                                             
  input_x_position.push_back( 2.0 );
  
  MonteCarlo::ParticleTrackerHDF5FileHandler::OverallHistoryMap history_map;
  
  particle_tracker.getDataMap( history_map );
  
  Teuchos::Array< double > mapped_x_position;
  
  mapped_x_position = history_map[ 0 ][ MonteCarlo::PHOTON ][ 0 ][ 0 ][ 0 ];

  UTILITY_TEST_COMPARE_ARRAYS( input_x_position, mapped_x_position );
}

// Check that the data can be reset
TEUCHOS_UNIT_TEST( ParticleTracker, testParticleReset )
{
  TEST_ASSERT( particle_tracker.isParticleReset() );
}

//---------------------------------------------------------------------------//
// end tstStandardCellEstimator.cpp
//---------------------------------------------------------------------------//

