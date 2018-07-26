//---------------------------------------------------------------------------//
//!
//! \file   tstSharedParallelParticleTracker.cpp
//! \author Eli Moll
//! \brief  Shared parallel particle Tracker unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_ParticleTracker.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "Utility_OpenMPProperties.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the id can be returned
FRENSIE_UNIT_TEST( ParticleTracker, getId )
{
  MonteCarlo::ParticleTracker particle_tracker_0( 0, 100 );

  FRENSIE_CHECK_EQUAL( particle_tracker_0.getId(), 0 );

  MonteCarlo::ParticleTracker particle_tracker_1( 1, 100 );

  FRENSIE_CHECK_EQUAL( particle_tracker_1.getId(), 1 );
}

//---------------------------------------------------------------------------//
// Check that the tracked histories can be returned
FRENSIE_UNIT_TEST( ParticleTracker, getTrackedHistories )
{
  MonteCarlo::ParticleTracker particle_tracker_a( 0, 3 );

  FRENSIE_CHECK_EQUAL( particle_tracker_a.getTrackedHistories().size(), 3 );
  FRENSIE_CHECK( particle_tracker_a.getTrackedHistories().count( 0 ) );
  FRENSIE_CHECK( particle_tracker_a.getTrackedHistories().count( 1 ) );
  FRENSIE_CHECK( particle_tracker_a.getTrackedHistories().count( 2 ) );

  MonteCarlo::ParticleTracker particle_tracker_b( 1, {0, 2, 4, 7} );

  FRENSIE_CHECK_EQUAL( particle_tracker_b.getTrackedHistories().size(), 4 );
  FRENSIE_CHECK( particle_tracker_b.getTrackedHistories().count( 0 ) );
  FRENSIE_CHECK( particle_tracker_b.getTrackedHistories().count( 2 ) );
  FRENSIE_CHECK( particle_tracker_b.getTrackedHistories().count( 4 ) );
  FRENSIE_CHECK( particle_tracker_b.getTrackedHistories().count( 7 ) );
}

//---------------------------------------------------------------------------//
// Check that the data is updated appropriately after events
FRENSIE_UNIT_TEST( ParticleTracker, update_from_events )
{
  MonteCarlo::ParticleTracker particle_tracker( 0, 100 );

  unsigned threads = Utility::OpenMPProperties::getRequestedNumberOfThreads();
  
  particle_tracker.enableThreadSupport( threads );
  
  #pragma omp parallel num_threads( threads )
  {
    // Initial particle state
    std::unique_ptr<MonteCarlo::ParticleState> particle;

    if( Utility::OpenMPProperties::getThreadId()%2 == 0 )
    {
      particle.reset( new MonteCarlo::PhotonState( Utility::OpenMPProperties::getThreadId() ) );
    }
    else
    {
      particle.reset( new MonteCarlo::ElectronState( Utility::OpenMPProperties::getThreadId() ) );
    }
    
    particle->setPosition( 2.0, 1.0, 1.0 );
    particle->setDirection( 1.0, 0.0, 0.0 );
    particle->setEnergy( 2.5 );
    particle->setTime( 5e-11 );
    particle->setWeight( 1.0 );

    // Start and end positions
    double start_point[3] = { 1.0, 1.0, 1.0 };
    double end_point[3] = { 2.0, 1.0, 1.0 };

    particle_tracker.updateFromGlobalParticleSubtrackEndingEvent( *particle,
                                                                  start_point,
                                                                  end_point );
    
    particle->setAsGone();
    
    particle_tracker.updateFromGlobalParticleGoneEvent( *particle );
    particle_tracker.commitHistoryContribution();
  }

  MonteCarlo::ParticleTracker::OverallHistoryMap history_map;

  particle_tracker.getHistoryData( history_map );

  const MonteCarlo::ParticleTracker::ParticleDataArray* cached_particle_state;
  
  for( size_t i = 0; i < threads; ++i )
  {
    FRENSIE_REQUIRE( history_map.find( i ) != history_map.end() );

    if( i%2 == 0 )
    {
      FRENSIE_REQUIRE( history_map[i].find( MonteCarlo::PHOTON ) !=
                       history_map[i].end() );
      FRENSIE_REQUIRE( history_map[i][MonteCarlo::PHOTON].find( 0 ) !=
                       history_map[i][MonteCarlo::PHOTON].end() );
      FRENSIE_REQUIRE( history_map[i][MonteCarlo::PHOTON][0].find( 0 ) !=
                       history_map[i][MonteCarlo::PHOTON][0].end() );

      cached_particle_state = &history_map[i][MonteCarlo::PHOTON][0][0];
    }
    else
    {
      FRENSIE_REQUIRE( history_map[i].find( MonteCarlo::ELECTRON ) !=
                       history_map[i].end() );
      FRENSIE_REQUIRE( history_map[i][MonteCarlo::ELECTRON].find( 0 ) !=
                       history_map[i][MonteCarlo::ELECTRON].end() );
      FRENSIE_REQUIRE( history_map[i][MonteCarlo::ELECTRON][0].find( 0 ) !=
                       history_map[i][MonteCarlo::ELECTRON][0].end() );

      cached_particle_state = &history_map[i][MonteCarlo::ELECTRON][0][0];
    }

    FRENSIE_REQUIRE_EQUAL( cached_particle_state->size(), 2 );
    FRENSIE_CHECK_EQUAL( Utility::get<0>( cached_particle_state->at( 0 ) ),
                         (std::array<double,3>( {1.0, 1.0, 1.0} )) );
    FRENSIE_CHECK_EQUAL( Utility::get<1>( cached_particle_state->at( 0 ) ),
                         (std::array<double,3>( {1.0, 0.0, 0.0} )) );
    FRENSIE_CHECK_EQUAL( Utility::get<2>( cached_particle_state->at( 0 ) ),
                         2.5 );

    if( i%2 == 0 )
    {
      FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<3>( cached_particle_state->at( 0 ) ),
                                       1.664359048018479962e-11,
                                       1e-15 );
    }
    else
    {
      FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<3>( cached_particle_state->at( 0 ) ),
                                       1.615259720929651211e-11,
                                       1e-15 );
    }
    
    FRENSIE_CHECK_EQUAL( Utility::get<4>( cached_particle_state->at( 0 ) ),
                         1.0 );
    FRENSIE_CHECK_EQUAL( Utility::get<5>( cached_particle_state->at( 0 ) ),
                         0 );

    FRENSIE_CHECK_EQUAL( Utility::get<0>( cached_particle_state->at( 1 ) ),
                         (std::array<double,3>( {2.0, 1.0, 1.0} )) );
    FRENSIE_CHECK_EQUAL( Utility::get<1>( cached_particle_state->at( 1 ) ),
                         (std::array<double,3>( {1.0, 0.0, 0.0} )) );
    FRENSIE_CHECK_EQUAL( Utility::get<2>( cached_particle_state->at( 1 ) ),
                         2.5 );
    FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<3>( cached_particle_state->at( 1 ) ),
                                     5.0e-11,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( Utility::get<4>( cached_particle_state->at( 1 ) ),
                         1.0 );
    FRENSIE_CHECK_EQUAL( Utility::get<5>( cached_particle_state->at( 1 ) ),
                         0 );
  }
}

//---------------------------------------------------------------------------//
// Check that particle tracker data can be reset
FRENSIE_UNIT_TEST( ParticleTracker, resetData )
{
  MonteCarlo::ParticleTracker particle_tracker( 0, 100 );

  unsigned threads = Utility::OpenMPProperties::getRequestedNumberOfThreads();
  
  particle_tracker.enableThreadSupport( threads );
  
  // Initial particle state
  MonteCarlo::PhotonState particle( 0 );

  particle.setPosition( 2.0, 1.0, 1.0 );
  particle.setDirection( 1.0, 0.0, 0.0 );
  particle.setEnergy( 2.5 );
  particle.setTime( 5e-11 );
  particle.setWeight( 1.0 );

  // Start and end positions
  double start_point[3] = { 1.0, 1.0, 1.0 };
  double end_point[3] = { 2.0, 1.0, 1.0 };

  particle_tracker.updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                                start_point,
                                                                end_point );
    
  particle.setAsGone();
    
  particle_tracker.updateFromGlobalParticleGoneEvent( particle );
  particle_tracker.commitHistoryContribution();

  // Reset the data
  particle_tracker.resetData();
  
  MonteCarlo::ParticleTracker::OverallHistoryMap history_map;

  particle_tracker.getHistoryData( history_map );

  FRENSIE_CHECK( history_map.empty() );
}

//---------------------------------------------------------------------------//
// Check that particle tracker data can be reduced
FRENSIE_UNIT_TEST( ParticleTracker, reduceData )
{
  MonteCarlo::ParticleTracker particle_tracker( 0, 100 );

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  comm->barrier();
  
  // Initial particle state
  std::unique_ptr<MonteCarlo::ParticleState> particle;

  if( comm->rank()%2 == 0 )
  {
    particle.reset( new MonteCarlo::PhotonState( comm->rank() ) );
  }
  else
  {
    particle.reset( new MonteCarlo::ElectronState( comm->rank() ) );
  }
    
  particle->setPosition( 2.0, 1.0, 1.0 );
  particle->setDirection( 1.0, 0.0, 0.0 );
  particle->setEnergy( 2.5 );
  particle->setTime( 5e-11 );
  particle->setWeight( 1.0 );
  
  // Start and end positions
  double start_point[3] = { 1.0, 1.0, 1.0 };
  double end_point[3] = { 2.0, 1.0, 1.0 };
  
  particle_tracker.updateFromGlobalParticleSubtrackEndingEvent( *particle,
                                                                start_point,
                                                                end_point );
  
  particle->setAsGone();
  
  particle_tracker.updateFromGlobalParticleGoneEvent( *particle );
  particle_tracker.commitHistoryContribution();

  particle_tracker.reduceData( *comm, 0 );

  MonteCarlo::ParticleTracker::OverallHistoryMap history_map;

  particle_tracker.getHistoryData( history_map );

  if( comm->rank() == 0 )
  {
    const MonteCarlo::ParticleTracker::ParticleDataArray* cached_particle_state;
  
    for( size_t i = 0; i < comm->size(); ++i )
    {
      FRENSIE_REQUIRE( history_map.find( i ) != history_map.end() );
      
      if( i%2 == 0 )
      {
        FRENSIE_REQUIRE( history_map[i].find( MonteCarlo::PHOTON ) !=
                         history_map[i].end() );
        FRENSIE_REQUIRE( history_map[i][MonteCarlo::PHOTON].find( 0 ) !=
                         history_map[i][MonteCarlo::PHOTON].end() );
        FRENSIE_REQUIRE( history_map[i][MonteCarlo::PHOTON][0].find( 0 ) !=
                         history_map[i][MonteCarlo::PHOTON][0].end() );
        
        cached_particle_state = &history_map[i][MonteCarlo::PHOTON][0][0];
      }
      else
      {
        FRENSIE_REQUIRE( history_map[i].find( MonteCarlo::ELECTRON ) !=
                         history_map[i].end() );
        FRENSIE_REQUIRE( history_map[i][MonteCarlo::ELECTRON].find( 0 ) !=
                         history_map[i][MonteCarlo::ELECTRON].end() );
        FRENSIE_REQUIRE( history_map[i][MonteCarlo::ELECTRON][0].find( 0 ) !=
                         history_map[i][MonteCarlo::ELECTRON][0].end() );
        
        cached_particle_state = &history_map[i][MonteCarlo::ELECTRON][0][0];
      }
      
      FRENSIE_REQUIRE_EQUAL( cached_particle_state->size(), 2 );
      FRENSIE_CHECK_EQUAL( Utility::get<0>( cached_particle_state->at( 0 ) ),
                           (std::array<double,3>( {1.0, 1.0, 1.0} )) );
      FRENSIE_CHECK_EQUAL( Utility::get<1>( cached_particle_state->at( 0 ) ),
                           (std::array<double,3>( {1.0, 0.0, 0.0} )) );
      FRENSIE_CHECK_EQUAL( Utility::get<2>( cached_particle_state->at( 0 ) ),
                           2.5 );
      
      if( i%2 == 0 )
      {
        FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<3>( cached_particle_state->at( 0 ) ),
                                         1.664359048018479962e-11,
                                         1e-15 );
      }
      else
      {
        FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<3>( cached_particle_state->at( 0 ) ),
                                         1.615259720929651211e-11,
                                         1e-15 );
      }
      
      FRENSIE_CHECK_EQUAL( Utility::get<4>( cached_particle_state->at( 0 ) ),
                           1.0 );
      FRENSIE_CHECK_EQUAL( Utility::get<5>( cached_particle_state->at( 0 ) ),
                           0 );
      
      FRENSIE_CHECK_EQUAL( Utility::get<0>( cached_particle_state->at( 1 ) ),
                           (std::array<double,3>( {2.0, 1.0, 1.0} )) );
      FRENSIE_CHECK_EQUAL( Utility::get<1>( cached_particle_state->at( 1 ) ),
                           (std::array<double,3>( {1.0, 0.0, 0.0} )) );
      FRENSIE_CHECK_EQUAL( Utility::get<2>( cached_particle_state->at( 1 ) ),
                           2.5 );
      FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<3>( cached_particle_state->at( 1 ) ),
                                       5.0e-11,
                                       1e-15 );
      FRENSIE_CHECK_EQUAL( Utility::get<4>( cached_particle_state->at( 1 ) ),
                           1.0 );
      FRENSIE_CHECK_EQUAL( Utility::get<5>( cached_particle_state->at( 1 ) ),
                           0 );
    }
  }
  else
  {
    FRENSIE_CHECK( history_map.empty() );
  }
}

//---------------------------------------------------------------------------//
// Check that an estimator can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( SurfaceFluxEstimator,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_particle_tracker" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::shared_ptr<MonteCarlo::ParticleTracker>
      particle_tracker( new MonteCarlo::ParticleTracker( 0, 100 ) );
  
    // Initial particle state
    for( size_t i = 0; i < 4; ++i )
    {
      // Initial particle state
      std::unique_ptr<MonteCarlo::ParticleState> particle;
      
      if( i%2 == 0 )
      {
        particle.reset( new MonteCarlo::PhotonState( i ) );
      }
      else
      {
        particle.reset( new MonteCarlo::ElectronState( i ) );
      }
    
      particle->setPosition( 2.0, 1.0, 1.0 );
      particle->setDirection( 1.0, 0.0, 0.0 );
      particle->setEnergy( 2.5 );
      particle->setTime( 5e-11 );
      particle->setWeight( 1.0 );
      
      // Start and end positions
      double start_point[3] = { 1.0, 1.0, 1.0 };
      double end_point[3] = { 2.0, 1.0, 1.0 };
      
      particle_tracker->updateFromGlobalParticleSubtrackEndingEvent( *particle,
                                                                     start_point,
                                                                     end_point );
      
      particle->setAsGone();
      
      particle_tracker->updateFromGlobalParticleGoneEvent( *particle );
      particle_tracker->commitHistoryContribution();
    }

    std::shared_ptr<const MonteCarlo::ParticleSubtrackEndingGlobalEventObserver>
      global_event_observer_a = particle_tracker;

    std::shared_ptr<const MonteCarlo::ParticleGoneGlobalEventObserver>
      global_event_observer_b = particle_tracker;

    std::shared_ptr<const MonteCarlo::ParticleHistoryObserver>
      history_observer = particle_tracker;

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( particle_tracker ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( global_event_observer_a ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( global_event_observer_b ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( history_observer ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::shared_ptr<MonteCarlo::ParticleTracker> particle_tracker;
  
  std::shared_ptr<const MonteCarlo::ParticleSubtrackEndingGlobalEventObserver>
    global_event_observer_a;

  std::shared_ptr<const MonteCarlo::ParticleGoneGlobalEventObserver>
    global_event_observer_b;

  std::shared_ptr<const MonteCarlo::ParticleHistoryObserver>
    history_observer;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( particle_tracker ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( global_event_observer_a ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( global_event_observer_b ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( history_observer ) );

  iarchive.reset();

  FRENSIE_CHECK( particle_tracker.get() == global_event_observer_a.get() );
  FRENSIE_CHECK( particle_tracker.get() == global_event_observer_b.get() );
  FRENSIE_CHECK( particle_tracker.get() == history_observer.get() );

  MonteCarlo::ParticleTracker::OverallHistoryMap history_map;

  particle_tracker->getHistoryData( history_map );

  const MonteCarlo::ParticleTracker::ParticleDataArray* cached_particle_state;
  
  for( size_t i = 0; i < 4; ++i )
  {
    FRENSIE_REQUIRE( history_map.find( i ) != history_map.end() );

    if( i%2 == 0 )
    {
      FRENSIE_REQUIRE( history_map[i].find( MonteCarlo::PHOTON ) !=
                       history_map[i].end() );
      FRENSIE_REQUIRE( history_map[i][MonteCarlo::PHOTON].find( 0 ) !=
                       history_map[i][MonteCarlo::PHOTON].end() );
      FRENSIE_REQUIRE( history_map[i][MonteCarlo::PHOTON][0].find( 0 ) !=
                       history_map[i][MonteCarlo::PHOTON][0].end() );

      cached_particle_state = &history_map[i][MonteCarlo::PHOTON][0][0];
    }
    else
    {
      FRENSIE_REQUIRE( history_map[i].find( MonteCarlo::ELECTRON ) !=
                       history_map[i].end() );
      FRENSIE_REQUIRE( history_map[i][MonteCarlo::ELECTRON].find( 0 ) !=
                       history_map[i][MonteCarlo::ELECTRON].end() );
      FRENSIE_REQUIRE( history_map[i][MonteCarlo::ELECTRON][0].find( 0 ) !=
                       history_map[i][MonteCarlo::ELECTRON][0].end() );

      cached_particle_state = &history_map[i][MonteCarlo::ELECTRON][0][0];
    }

    FRENSIE_REQUIRE_EQUAL( cached_particle_state->size(), 2 );
    FRENSIE_CHECK_EQUAL( Utility::get<0>( cached_particle_state->at( 0 ) ),
                         (std::array<double,3>( {1.0, 1.0, 1.0} )) );
    FRENSIE_CHECK_EQUAL( Utility::get<1>( cached_particle_state->at( 0 ) ),
                         (std::array<double,3>( {1.0, 0.0, 0.0} )) );
    FRENSIE_CHECK_EQUAL( Utility::get<2>( cached_particle_state->at( 0 ) ),
                         2.5 );

    if( i%2 == 0 )
    {
      FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<3>( cached_particle_state->at( 0 ) ),
                                       1.664359048018479962e-11,
                                       1e-15 );
    }
    else
    {
      FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<3>( cached_particle_state->at( 0 ) ),
                                       1.615259720929651211e-11,
                                       1e-15 );
    }
    
    FRENSIE_CHECK_EQUAL( Utility::get<4>( cached_particle_state->at( 0 ) ),
                         1.0 );
    FRENSIE_CHECK_EQUAL( Utility::get<5>( cached_particle_state->at( 0 ) ),
                         0 );

    FRENSIE_CHECK_EQUAL( Utility::get<0>( cached_particle_state->at( 1 ) ),
                         (std::array<double,3>( {2.0, 1.0, 1.0} )) );
    FRENSIE_CHECK_EQUAL( Utility::get<1>( cached_particle_state->at( 1 ) ),
                         (std::array<double,3>( {1.0, 0.0, 0.0} )) );
    FRENSIE_CHECK_EQUAL( Utility::get<2>( cached_particle_state->at( 1 ) ),
                         2.5 );
    FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<3>( cached_particle_state->at( 1 ) ),
                                     5.0e-11,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( Utility::get<4>( cached_particle_state->at( 1 ) ),
                         1.0 );
    FRENSIE_CHECK_EQUAL( Utility::get<5>( cached_particle_state->at( 1 ) ),
                         0 );
  }
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

int threads;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "threads",
                                        threads, 1,
                                        "Number of threads to use" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Set up the global OpenMP session
  if( Utility::OpenMPProperties::isOpenMPUsed() )
    Utility::OpenMPProperties::setNumberOfThreads( threads );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstStandardCellEstimator.cpp
//---------------------------------------------------------------------------//
