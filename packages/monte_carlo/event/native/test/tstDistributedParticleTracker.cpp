//---------------------------------------------------------------------------//
//!
//! \file   tstParticleTracker.cpp
//! \author Eli Moll
//! \brief  Particle Tracker unit tests
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
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "MonteCarlo_ParticleTrackerHDF5FileHandler.hpp"

//---------------------------------------------------------------------------//

// Construct a particle tracker
MonteCarlo::ParticleTracker particle_tracker( 100u );

// Construct a sample particle
MonteCarlo::PhotonState particle( 0u );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that parallel data can be brought together
TEUCHOS_UNIT_TEST( ParticleTracker, distributedParallelTest )
{
  // Construct a particle tracker
  MonteCarlo::ParticleTracker particle_tracker_mpi( 4u );

  const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm = 
    Teuchos::DefaultComm<unsigned long long>::getComm();
  
  comm->barrier();
  
  if( comm->getRank() == 0 )
  {
    MonteCarlo::PhotonState particle_mpi(0u);
    
    // Initial particle state
    particle_mpi.setPosition( 1.0, 1.0, 1.0 );
    particle_mpi.setDirection( 1.0, 0.0, 0.0 );
    particle_mpi.setEnergy( 2.5 );
    particle_mpi.setWeight( 1.0 );
    particle_mpi.setAsGone();
    
    // Start and end positions
    double start_point[3] = { 1.0, 1.0, 1.0 };
    double end_point[3] = { 2.0, 1.0, 1.0 };
    
    particle_tracker_mpi.updateFromGlobalParticleSubtrackEndingEvent( 
                                                                  particle_mpi,
                                                                  start_point,
                                                                  end_point );
  }
  else if( comm->getRank() == 1 )
  {
    MonteCarlo::PhotonState particle_mpi(1u);
    
    // Initial particle state
    particle_mpi.setPosition( 1.0, 1.0, 1.0 );
    particle_mpi.setDirection( 1.0, 0.0, 0.0 );
    particle_mpi.setEnergy( 2.5 );
    particle_mpi.setWeight( 1.0 );
    particle_mpi.setAsGone();
    
    // Start and end positions
    double start_point[3] = { 1.0, 1.0, 1.0 };
    double end_point[3] = { 2.0, 1.0, 1.0 };
    
    particle_tracker_mpi.updateFromGlobalParticleSubtrackEndingEvent( particle_mpi,
                                                                  start_point,
                                                                  end_point );
  }
  else if( comm->getRank() == 2 )
  {
    MonteCarlo::PhotonState particle_mpi(2u);
    
    // Initial particle state
    particle_mpi.setPosition( 1.0, 1.0, 1.0 );
    particle_mpi.setDirection( 1.0, 0.0, 0.0 );
    particle_mpi.setEnergy( 2.5 );
    particle_mpi.setWeight( 1.0 );
    particle_mpi.setAsGone();
    
    // Start and end positions
    double start_point[3] = { 1.0, 1.0, 1.0 };
    double end_point[3] = { 2.0, 1.0, 1.0 };
    
    particle_tracker_mpi.updateFromGlobalParticleSubtrackEndingEvent( particle_mpi,
                                                                  start_point,
                                                                  end_point );
  }
  else if( comm->getRank() == 3 )
  {
    MonteCarlo::PhotonState particle_mpi(3u);
    
    // Initial particle state
    particle_mpi.setPosition( 1.0, 1.0, 1.0 );
    particle_mpi.setDirection( 1.0, 0.0, 0.0 );
    particle_mpi.setEnergy( 2.5 );
    particle_mpi.setWeight( 1.0 );
    particle_mpi.setAsGone();
    
    // Start and end positions
    double start_point[3] = { 1.0, 1.0, 1.0 };
    double end_point[3] = { 2.0, 1.0, 1.0 };
    
    particle_tracker_mpi.updateFromGlobalParticleSubtrackEndingEvent( particle_mpi,
                                                                  start_point,
                                                                  end_point );   
  }
  
  particle_tracker_mpi.reduceData( comm, 0 );
  
  MonteCarlo::ParticleTrackerHDF5FileHandler::OverallHistoryMap history_map;
  
  if( comm->getRank() ==  0 )
  {
    particle_tracker_mpi.getDataMap( history_map );
    
    std::vector< double > map_x_pos_h0 = 
      history_map[ 0 ][ MonteCarlo::PHOTON ][ 0 ][ 0 ][ 0 ];

    if( comm->getSize() > 1 )
    {
      std::vector< double > map_x_pos_h1 = 
        history_map[ 1 ][ MonteCarlo::PHOTON ][ 0 ][ 0 ][ 0 ];

      UTILITY_TEST_COMPARE_ARRAYS( map_x_pos_h0, map_x_pos_h1 );
    }
    
    if( comm->getSize() > 2 )
    {
      std::vector< double > map_x_pos_h2 = 
        history_map[ 2 ][ MonteCarlo::PHOTON ][ 0 ][ 0 ][ 0 ];

      UTILITY_TEST_COMPARE_ARRAYS( map_x_pos_h0, map_x_pos_h2 );
    }
    
    if( comm->getSize() > 3 )
    {
      std::vector< double > map_x_pos_h3 =
        history_map[ 3 ][ MonteCarlo::PHOTON ][ 0 ][ 0 ][ 0 ];
      
      UTILITY_TEST_COMPARE_ARRAYS( map_x_pos_h0, map_x_pos_h3 );
    }
  }
  else // The non-root nodes should be reset
  {
    particle_tracker_mpi.getDataMap( history_map );

    TEST_ASSERT( history_map.empty() );
  }
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();
  
  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Initialize the global MPI session
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  out->setProcRankAndSize( mpiSession.getRank(), mpiSession.getNProc() );

  mpiSession.barrier();

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

