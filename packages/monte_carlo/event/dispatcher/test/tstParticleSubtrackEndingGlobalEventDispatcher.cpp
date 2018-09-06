//---------------------------------------------------------------------------//
//!
//! \file   tstParticleSubtrackEndingGlobalEventDispatcher.cpp
//! \author Alex Robinson, Eli Moll
//! \brief  Particle subtrack ending in cell event dispatcher unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_ParticleTracker.hpp"
#include "MonteCarlo_ParticleSubtrackEndingGlobalEventDispatcher.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<MonteCarlo::ParticleTracker> tracker;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that an observer can be managed
FRENSIE_UNIT_TEST( ParticleSubtrackEndingGlobalEventDispatcher,
		   manage_observers )
{
  std::shared_ptr<MonteCarlo::ParticleSubtrackEndingGlobalEventDispatcher>
    dispatcher( new MonteCarlo::ParticleSubtrackEndingGlobalEventDispatcher );

  dispatcher->attachObserver( tracker );

  FRENSIE_CHECK( tracker.use_count() > 1 );
  FRENSIE_CHECK_EQUAL( dispatcher->getNumberOfObservers( MonteCarlo::PHOTON ), 1 );
  FRENSIE_CHECK_EQUAL( dispatcher->getNumberOfObservers( MonteCarlo::ELECTRON ), 1 );
  FRENSIE_CHECK_EQUAL( dispatcher->getNumberOfObservers( MonteCarlo::POSITRON ), 1 );
  FRENSIE_CHECK_EQUAL( dispatcher->getNumberOfObservers( MonteCarlo::NEUTRON ), 1 );

  dispatcher->detachAllObservers();

  FRENSIE_CHECK_EQUAL( tracker.use_count(), 1 );
  FRENSIE_CHECK_EQUAL( dispatcher->getNumberOfObservers( MonteCarlo::PHOTON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getNumberOfObservers( MonteCarlo::ELECTRON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getNumberOfObservers( MonteCarlo::POSITRON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getNumberOfObservers( MonteCarlo::NEUTRON ), 0 );

  dispatcher->attachObserver( {MonteCarlo::PHOTON}, tracker );

  FRENSIE_CHECK_EQUAL( tracker.use_count(), 2 );
  FRENSIE_CHECK_EQUAL( dispatcher->getNumberOfObservers( MonteCarlo::PHOTON ), 1 );
  FRENSIE_CHECK_EQUAL( dispatcher->getNumberOfObservers( MonteCarlo::ELECTRON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getNumberOfObservers( MonteCarlo::POSITRON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getNumberOfObservers( MonteCarlo::NEUTRON ), 0 );

  dispatcher->detachObserver( tracker );

  FRENSIE_CHECK_EQUAL( tracker.use_count(), 1 );
  FRENSIE_CHECK_EQUAL( dispatcher->getNumberOfObservers( MonteCarlo::PHOTON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getNumberOfObservers( MonteCarlo::ELECTRON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getNumberOfObservers( MonteCarlo::POSITRON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getNumberOfObservers( MonteCarlo::NEUTRON ), 0 );
}

//---------------------------------------------------------------------------//
// Check that the dispatcher can update from the global ending event
FRENSIE_UNIT_TEST( ParticleSubtrackEndingGlobalEventDispatcher,
                   dispatchParticleSubtrackEndingGlobalEvent )
{
  std::shared_ptr<MonteCarlo::ParticleSubtrackEndingGlobalEventDispatcher>
    dispatcher( new MonteCarlo::ParticleSubtrackEndingGlobalEventDispatcher );

  dispatcher->attachObserver( tracker );

  {
    MonteCarlo::PhotonState particle( 0 );
    particle.setPosition( 2.0, 1.0, 1.0 );
    particle.setDirection( 1.0, 0.0, 0.0 );
    particle.setEnergy( 2.5 );
    particle.setTime( 5e-11 );
    particle.setWeight( 1.0 );

    // Start and end positions
    double start_point[3] = { 1.0, 1.0, 1.0 };
    double end_point[3] = { 2.0, 1.0, 1.0 };

    dispatcher->dispatchParticleSubtrackEndingGlobalEvent( particle,
                                                           start_point,
                                                           end_point );

    particle.setAsGone();
    
    tracker->updateFromGlobalParticleGoneEvent( particle );
    
    tracker->commitHistoryContribution();

    MonteCarlo::ParticleTracker::OverallHistoryMap history_map;

    tracker->getHistoryData( history_map );

    FRENSIE_REQUIRE( history_map.find( 0 ) != history_map.end() );

    FRENSIE_REQUIRE( history_map[0].find( MonteCarlo::PHOTON ) !=
                     history_map[0].end() );
    FRENSIE_REQUIRE( history_map[0][MonteCarlo::PHOTON].find( 0 ) !=
                     history_map[0][MonteCarlo::PHOTON].end() );
    FRENSIE_REQUIRE( history_map[0][MonteCarlo::PHOTON][0].find( 0 ) !=
                     history_map[0][MonteCarlo::PHOTON][0].end() );

    const MonteCarlo::ParticleTracker::ParticleDataArray
      cached_particle_state = history_map[0][MonteCarlo::PHOTON][0][0];

    FRENSIE_REQUIRE_EQUAL( cached_particle_state.size(), 2 );
    FRENSIE_CHECK_EQUAL( Utility::get<0>( cached_particle_state.at( 0 ) ),
                         (std::array<double,3>( {1.0, 1.0, 1.0} )) );
    FRENSIE_CHECK_EQUAL( Utility::get<1>( cached_particle_state.at( 0 ) ),
                         (std::array<double,3>( {1.0, 0.0, 0.0} )) );
    FRENSIE_CHECK_EQUAL( Utility::get<2>( cached_particle_state.at( 0 ) ),
                         2.5 );
    FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<3>( cached_particle_state.at( 0 ) ),
                                     1.664359048018479962e-11,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( Utility::get<4>( cached_particle_state.at( 0 ) ),
                         1.0 );
    FRENSIE_CHECK_EQUAL( Utility::get<5>( cached_particle_state.at( 0 ) ),
                         0 );

    FRENSIE_CHECK_EQUAL( Utility::get<0>( cached_particle_state.at( 1 ) ),
                         (std::array<double,3>( {2.0, 1.0, 1.0} )) );
    FRENSIE_CHECK_EQUAL( Utility::get<1>( cached_particle_state.at( 1 ) ),
                         (std::array<double,3>( {1.0, 0.0, 0.0} )) );
    FRENSIE_CHECK_EQUAL( Utility::get<2>( cached_particle_state.at( 1 ) ),
                         2.5 );
    FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<3>( cached_particle_state.at( 1 ) ),
                                     5.0e-11,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( Utility::get<4>( cached_particle_state.at( 1 ) ),
                         1.0 );
    FRENSIE_CHECK_EQUAL( Utility::get<5>( cached_particle_state.at( 1 ) ),
                         0 );
  }

  {
    MonteCarlo::ElectronState particle( 2 );
    particle.setPosition( 2.0, 1.0, 1.0 );
    particle.setDirection( 1.0, 0.0, 0.0 );
    particle.setEnergy( 2.5 );
    particle.setTime( 5e-11 );
    particle.setWeight( 1.0 );

    // Start and end positions
    double start_point[3] = { 1.0, 1.0, 1.0 };
    double end_point[3] = { 2.0, 1.0, 1.0 };

    dispatcher->dispatchParticleSubtrackEndingGlobalEvent( particle,
                                                           start_point,
                                                           end_point );

    particle.setAsGone();
    
    tracker->updateFromGlobalParticleGoneEvent( particle );
    
    tracker->commitHistoryContribution();

    MonteCarlo::ParticleTracker::OverallHistoryMap history_map;

    tracker->getHistoryData( history_map );
    

    FRENSIE_REQUIRE( history_map.find( 2 ) != history_map.end() );

    FRENSIE_REQUIRE( history_map[2].find( MonteCarlo::ELECTRON ) !=
                     history_map[2].end() );
    FRENSIE_REQUIRE( history_map[2][MonteCarlo::ELECTRON].find( 0 ) !=
                     history_map[2][MonteCarlo::ELECTRON].end() );
    FRENSIE_REQUIRE( history_map[2][MonteCarlo::ELECTRON][0].find( 0 ) !=
                     history_map[2][MonteCarlo::ELECTRON][0].end() );

    const MonteCarlo::ParticleTracker::ParticleDataArray
      cached_particle_state = history_map[2][MonteCarlo::ELECTRON][0][0];

    FRENSIE_REQUIRE_EQUAL( cached_particle_state.size(), 2 );
    FRENSIE_CHECK_EQUAL( Utility::get<0>( cached_particle_state.at( 0 ) ),
                         (std::array<double,3>( {1.0, 1.0, 1.0} )) );
    FRENSIE_CHECK_EQUAL( Utility::get<1>( cached_particle_state.at( 0 ) ),
                         (std::array<double,3>( {1.0, 0.0, 0.0} )) );
    FRENSIE_CHECK_EQUAL( Utility::get<2>( cached_particle_state.at( 0 ) ),
                         2.5 );
    FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<3>( cached_particle_state.at( 0 ) ),
                                     1.615259720929651211e-11,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( Utility::get<4>( cached_particle_state.at( 0 ) ),
                         1.0 );
    FRENSIE_CHECK_EQUAL( Utility::get<5>( cached_particle_state.at( 0 ) ),
                         0 );

    FRENSIE_CHECK_EQUAL( Utility::get<0>( cached_particle_state.at( 1 ) ),
                         (std::array<double,3>( {2.0, 1.0, 1.0} )) );
    FRENSIE_CHECK_EQUAL( Utility::get<1>( cached_particle_state.at( 1 ) ),
                         (std::array<double,3>( {1.0, 0.0, 0.0} )) );
    FRENSIE_CHECK_EQUAL( Utility::get<2>( cached_particle_state.at( 1 ) ),
                         2.5 );
    FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<3>( cached_particle_state.at( 1 ) ),
                                     5.0e-11,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( Utility::get<4>( cached_particle_state.at( 1 ) ),
                         1.0 );
    FRENSIE_CHECK_EQUAL( Utility::get<5>( cached_particle_state.at( 1 ) ),
                         0 );
  }
}

//---------------------------------------------------------------------------//
// Check that an event dispatcher can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( ParticleSubtrackEndingGlobalEventDispatcher,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_particle_subtrack_ending_global_event_dispatcher" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::shared_ptr<MonteCarlo::ParticleTracker> local_tracker(
                             new MonteCarlo::ParticleTracker( 1, {0, 2, 4} ) );
    
    std::shared_ptr<MonteCarlo::ParticleSubtrackEndingGlobalEventDispatcher>
      dispatcher( new MonteCarlo::ParticleSubtrackEndingGlobalEventDispatcher );

    dispatcher->attachObserver( local_tracker );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(local_tracker) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(dispatcher) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::shared_ptr<MonteCarlo::ParticleTracker> local_tracker;
  std::shared_ptr<MonteCarlo::ParticleSubtrackEndingGlobalEventDispatcher>
    dispatcher;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(local_tracker) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(dispatcher) );

  iarchive.reset();

  FRENSIE_CHECK( local_tracker.use_count() > 1 );
  FRENSIE_CHECK_EQUAL( dispatcher->getNumberOfObservers( MonteCarlo::PHOTON ), 1 );
  FRENSIE_CHECK_EQUAL( dispatcher->getNumberOfObservers( MonteCarlo::ELECTRON ), 1 );
  FRENSIE_CHECK_EQUAL( dispatcher->getNumberOfObservers( MonteCarlo::POSITRON ), 1 );
  FRENSIE_CHECK_EQUAL( dispatcher->getNumberOfObservers( MonteCarlo::NEUTRON ), 1 );

  {
    MonteCarlo::PhotonState particle( 0 );
    particle.setPosition( 2.0, 1.0, 1.0 );
    particle.setDirection( 1.0, 0.0, 0.0 );
    particle.setEnergy( 2.5 );
    particle.setTime( 5e-11 );
    particle.setWeight( 1.0 );

    // Start and end positions
    double start_point[3] = { 1.0, 1.0, 1.0 };
    double end_point[3] = { 2.0, 1.0, 1.0 };

    dispatcher->dispatchParticleSubtrackEndingGlobalEvent( particle,
                                                           start_point,
                                                           end_point );

    particle.setAsGone();
    
    local_tracker->updateFromGlobalParticleGoneEvent( particle );
    
    local_tracker->commitHistoryContribution();

    MonteCarlo::ParticleTracker::OverallHistoryMap history_map;

    local_tracker->getHistoryData( history_map );

    FRENSIE_REQUIRE( history_map.find( 0 ) != history_map.end() );

    FRENSIE_REQUIRE( history_map[0].find( MonteCarlo::PHOTON ) !=
                     history_map[0].end() );
    FRENSIE_REQUIRE( history_map[0][MonteCarlo::PHOTON].find( 0 ) !=
                     history_map[0][MonteCarlo::PHOTON].end() );
    FRENSIE_REQUIRE( history_map[0][MonteCarlo::PHOTON][0].find( 0 ) !=
                     history_map[0][MonteCarlo::PHOTON][0].end() );

    const MonteCarlo::ParticleTracker::ParticleDataArray
      cached_particle_state = history_map[0][MonteCarlo::PHOTON][0][0];

    FRENSIE_REQUIRE_EQUAL( cached_particle_state.size(), 2 );
    FRENSIE_CHECK_EQUAL( Utility::get<0>( cached_particle_state.at( 0 ) ),
                         (std::array<double,3>( {1.0, 1.0, 1.0} )) );
    FRENSIE_CHECK_EQUAL( Utility::get<1>( cached_particle_state.at( 0 ) ),
                         (std::array<double,3>( {1.0, 0.0, 0.0} )) );
    FRENSIE_CHECK_EQUAL( Utility::get<2>( cached_particle_state.at( 0 ) ),
                         2.5 );
    FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<3>( cached_particle_state.at( 0 ) ),
                                     1.664359048018479962e-11,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( Utility::get<4>( cached_particle_state.at( 0 ) ),
                         1.0 );
    FRENSIE_CHECK_EQUAL( Utility::get<5>( cached_particle_state.at( 0 ) ),
                         0 );

    FRENSIE_CHECK_EQUAL( Utility::get<0>( cached_particle_state.at( 1 ) ),
                         (std::array<double,3>( {2.0, 1.0, 1.0} )) );
    FRENSIE_CHECK_EQUAL( Utility::get<1>( cached_particle_state.at( 1 ) ),
                         (std::array<double,3>( {1.0, 0.0, 0.0} )) );
    FRENSIE_CHECK_EQUAL( Utility::get<2>( cached_particle_state.at( 1 ) ),
                         2.5 );
    FRENSIE_CHECK_FLOATING_EQUALITY( Utility::get<3>( cached_particle_state.at( 1 ) ),
                                     5.0e-11,
                                     1e-15 );
    FRENSIE_CHECK_EQUAL( Utility::get<4>( cached_particle_state.at( 1 ) ),
                         1.0 );
    FRENSIE_CHECK_EQUAL( Utility::get<5>( cached_particle_state.at( 1 ) ),
                         0 );
  }
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  tracker.reset( new MonteCarlo::ParticleTracker( 0, {0, 2, 4} ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstParticleSubtrackEndingGlobalEventDispatcher.cpp
//---------------------------------------------------------------------------//
