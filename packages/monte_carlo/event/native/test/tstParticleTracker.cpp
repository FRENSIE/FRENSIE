//---------------------------------------------------------------------------//
//!
//! \file   tstSharedParallelParticleTracker.cpp
//! \author Eli Moll
//! \brief  Shared parallel particle Tracker unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <typeinfo>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_DefaultComm.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleTracker.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_ParticleTrackerHDF5FileHandler.hpp"
#include "Utility_GlobalOpenMPSession.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Construct a particle tracker
MonteCarlo::ParticleTracker particle_tracker( 100u );
int threads = 1;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the data is updated appropriately in the 
// GlobalSubtrackEndingEvent
TEUCHOS_UNIT_TEST( SharedParallelParticleTracker, 
                   testUpdateFromGlobalSubtrackEndingEvent )
{ 
  particle_tracker.enableThreadSupport( threads );
               
  #pragma omp parallel num_threads( threads )
  {
    MonteCarlo::PhotonState particle( Utility::GlobalOpenMPSession::getThreadId() );
  
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
    std::vector< double > input_x_position;
    input_x_position.push_back( 1.0 );
    input_x_position.push_back( 2.0 );
    
    std::vector< double > input_y_position;
    input_y_position.push_back( 1.0 );
    input_y_position.push_back( 1.0 );
    
    std::vector< double > input_z_position;
    input_z_position.push_back( 1.0 );
    input_z_position.push_back( 1.0 );
    
    std::vector< double > input_x_direction;
    input_x_direction.push_back( 1.0 );
    input_x_direction.push_back( 1.0 );
    
    std::vector< double > input_y_direction;
    input_y_direction.push_back( 0.0 );
    input_y_direction.push_back( 0.0 );
    
    std::vector< double > input_z_direction;
    input_z_direction.push_back( 0.0 );
    input_z_direction.push_back( 0.0 );
    
    std::vector< double > input_energy;
    input_energy.push_back( 2.5 );
    input_energy.push_back( 2.5 );
    
    std::vector< double > input_collision_number;
    input_collision_number.push_back( 0.0 );
    input_collision_number.push_back( 0.0 );
    
    std::vector< double > input_weight;
    input_weight.push_back( 1.0 );
    input_weight.push_back( 1.0 );
    
    // Define and populate the output data                              
    std::vector< double > output_x_position;
    particle_tracker.getXPositionData( output_x_position );
    
    std::vector< double > output_y_position;
    particle_tracker.getYPositionData( output_y_position );
    
    std::vector< double > output_z_position;
    particle_tracker.getZPositionData( output_z_position );
    
    std::vector< double > output_x_direction;
    particle_tracker.getXDirectionData( output_x_direction );
    
    std::vector< double > output_y_direction;
    particle_tracker.getYDirectionData( output_y_direction );
    
    std::vector< double > output_z_direction;
    particle_tracker.getZDirectionData( output_z_direction );
    
    std::vector< double > output_energy;
    particle_tracker.getEnergyData( output_energy );
    
    std::vector< double > output_collision_number;
    particle_tracker.getCollisionNumberData( output_collision_number );
    
    std::vector< double > output_weight;
    particle_tracker.getWeightData( output_weight );

    #pragma omp critical
    {
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
  }
  
  particle_tracker.resetData();
}

//---------------------------------------------------------------------------//
// Check that the data is committed appropriately
TEUCHOS_UNIT_TEST( SharedParallelParticleTracker, testcommitParticleTrackData )
{
  #pragma omp parallel num_threads( threads )      
  {
    MonteCarlo::PhotonState particle( Utility::GlobalOpenMPSession::getThreadId() );
  
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
    }
  
  // Expected data
  std::vector< double > input_x_position;                                                            
  input_x_position.push_back( 2.0 );
  
  MonteCarlo::ParticleTrackerHDF5FileHandler::OverallHistoryMap history_map;
  
  particle_tracker.getDataMap( history_map );
  
  std::vector< double > mapped_x_position;
  
  mapped_x_position = history_map[ 0 ][ MonteCarlo::PHOTON ][ 0 ][ 0 ][ 0 ];

  #pragma omp critical
  {
    UTILITY_TEST_COMPARE_ARRAYS( input_x_position, mapped_x_position );
  }

  particle_tracker.resetData();
}

//---------------------------------------------------------------------------//
// Check that the data can be reset
TEUCHOS_UNIT_TEST( SharedParallelParticleTracker, testParticleReset )
{
  #pragma omp parallel num_threads( threads )
  {
    #pragma omp critical
    {
      TEST_ASSERT( particle_tracker.isParticleReset() );
    }
  }
}

//---------------------------------------------------------------------------//
// Check that the data map can be converted into a string and back into a map
TEUCHOS_UNIT_TEST( SharedParallelParticleTracker, testDataPackaging )
{
  #pragma omp parallel num_threads( threads )
  {
    MonteCarlo::PhotonState particle( Utility::GlobalOpenMPSession::getThreadId() );
  
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
  }

  std::string packaged_data = particle_tracker.packDataInString();
  
  MonteCarlo::ParticleTrackerHDF5FileHandler::OverallHistoryMap history_map;

  particle_tracker.unpackDataFromString( packaged_data, history_map );
  
  // Test that the data is unchanged after serialization/deserialization
  
  // Expected data
  std::vector< double > input_x_position;                                                            
  input_x_position.push_back( 2.0 );
  
  std::vector< double > mapped_x_position;
  
  mapped_x_position = history_map[ 0 ][ MonteCarlo::PHOTON ][ 0 ][ 0 ][ 0 ];
  
  UTILITY_TEST_COMPARE_ARRAYS( input_x_position, mapped_x_position );
}

//---------------------------------------------------------------------------//
// Check that parallel data can be brought together
TEUCHOS_UNIT_TEST( SharedParallelParticleTracker, checkParallelData )
{
  // Overall history map 
  MonteCarlo::ParticleTrackerHDF5FileHandler::OverallHistoryMap history_map;
  particle_tracker.getDataMap( history_map );
  
  // Expected data
  std::vector< double > input_x_position;                                                            
  input_x_position.push_back( 2.0 );
  
  // Mapped data
  std::vector< double > mapped_x_position_0 =
    history_map[ 0 ][ MonteCarlo::PHOTON ][ 0 ][ 0 ][ 0 ];

  UTILITY_TEST_COMPARE_ARRAYS( input_x_position, mapped_x_position_0 );

  if( threads > 1 )
  {
    std::vector< double > mapped_x_position_1 =
      history_map[ 1 ][ MonteCarlo::PHOTON ][ 0 ][ 0 ][ 0 ];

    UTILITY_TEST_COMPARE_ARRAYS( input_x_position, mapped_x_position_1 );
  }

  if( threads > 2 )
  {
    std::vector< double > mapped_x_position_2 =
      history_map[ 2 ][ MonteCarlo::PHOTON ][ 0 ][ 0 ][ 0 ];

    UTILITY_TEST_COMPARE_ARRAYS( input_x_position, mapped_x_position_2 );
  }

  if( threads > 3 )
  {
    std::vector< double > mapped_x_position_3 = 
      history_map[ 3 ][ MonteCarlo::PHOTON ][ 0 ][ 0 ][ 0 ];

    UTILITY_TEST_COMPARE_ARRAYS( input_x_position, mapped_x_position_3 );
  }  
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();
  
  clp.setOption( "threads",
		 &threads,
		 "Number of threads to use" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Set up the global OpenMP session
  if( Utility::GlobalOpenMPSession::isOpenMPUsed() )
    Utility::GlobalOpenMPSession::setNumberOfThreads( threads );

  // Run the unit tests
  const bool success = Teuchos::UnitTestRepository::runUnitTests(*out);

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstStandardCellEstimator.cpp
//---------------------------------------------------------------------------//
