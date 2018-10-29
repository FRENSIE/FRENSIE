//---------------------------------------------------------------------------//
//!
//! \file   tstParticleCrossingSurfaceEventDispatcherDB.cpp
//! \author Alex Robinson
//! \brief  Particle crossing surface event dispatcher unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_SurfaceCurrentEstimator.hpp"
#include "MonteCarlo_SurfaceFluxEstimator.hpp"
#include "MonteCarlo_ParticleCrossingSurfaceEventDispatcher.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "Geometry_Model.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<MonteCarlo::WeightMultipliedSurfaceCurrentEstimator>
estimator_1;

std::shared_ptr<MonteCarlo::WeightAndEnergyMultipliedSurfaceFluxEstimator>
estimator_2;

std::shared_ptr<MonteCarlo::WeightAndChargeMultipliedSurfaceFluxEstimator>
estimator_3;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the correct event dispatchers can be returned
FRENSIE_UNIT_TEST( ParticleCrossingSurfaceEventDispatcher, getLocalDispatcher )
{
  std::shared_ptr<MonteCarlo::ParticleCrossingSurfaceEventDispatcher>
    dispatcher( new MonteCarlo::ParticleCrossingSurfaceEventDispatcher );

  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 0 ).getEntityId(), 0 );

  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 1 ).getEntityId(), 1 );
}

//---------------------------------------------------------------------------//
// Check that observers can be managed
FRENSIE_UNIT_TEST( ParticleCrossingSurfaceEventDispatcher, manage_observers )
{
  std::shared_ptr<MonteCarlo::ParticleCrossingSurfaceEventDispatcher>
    dispatcher( new MonteCarlo::ParticleCrossingSurfaceEventDispatcher );

  dispatcher->attachObserver( 0, estimator_1 );

  FRENSIE_CHECK( estimator_1.use_count() > 1 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 0 ).getNumberOfObservers( MonteCarlo::PHOTON ), 1 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 0 ).getNumberOfObservers( MonteCarlo::ELECTRON ), 1 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 0 ).getNumberOfObservers( MonteCarlo::POSITRON ), 1 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 0 ).getNumberOfObservers( MonteCarlo::NEUTRON ), 1 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::PHOTON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::ELECTRON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::POSITRON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::NEUTRON ), 0 );

  dispatcher->detachAllObservers();

  FRENSIE_CHECK_EQUAL( estimator_1.use_count(), 1 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 0 ).getNumberOfObservers( MonteCarlo::PHOTON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 0 ).getNumberOfObservers( MonteCarlo::ELECTRON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 0 ).getNumberOfObservers( MonteCarlo::POSITRON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 0 ).getNumberOfObservers( MonteCarlo::NEUTRON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::PHOTON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::ELECTRON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::POSITRON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::NEUTRON ), 0 );

  dispatcher->attachObserver( 0, {MonteCarlo::PHOTON}, estimator_1 );

  FRENSIE_CHECK_EQUAL( estimator_1.use_count(), 2 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 0 ).getNumberOfObservers( MonteCarlo::PHOTON ), 1 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 0 ).getNumberOfObservers( MonteCarlo::ELECTRON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 0 ).getNumberOfObservers( MonteCarlo::POSITRON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 0 ).getNumberOfObservers( MonteCarlo::NEUTRON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::PHOTON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::ELECTRON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::POSITRON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::NEUTRON ), 0 );

  dispatcher->attachObserver( 0, estimator_1 );
  dispatcher->attachObserver( 1, estimator_1 );

  FRENSIE_CHECK( estimator_1.use_count() > 1 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 0 ).getNumberOfObservers( MonteCarlo::PHOTON ), 1 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 0 ).getNumberOfObservers( MonteCarlo::ELECTRON ), 1 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 0 ).getNumberOfObservers( MonteCarlo::POSITRON ), 1 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 0 ).getNumberOfObservers( MonteCarlo::NEUTRON ), 1 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::PHOTON ), 1 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::ELECTRON ), 1 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::POSITRON ), 1 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::NEUTRON ), 1 );

  dispatcher->detachObserver( 0, estimator_1 );

  FRENSIE_CHECK( estimator_1.use_count() > 1 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 0 ).getNumberOfObservers( MonteCarlo::PHOTON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 0 ).getNumberOfObservers( MonteCarlo::ELECTRON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 0 ).getNumberOfObservers( MonteCarlo::POSITRON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 0 ).getNumberOfObservers( MonteCarlo::NEUTRON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::PHOTON ), 1 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::ELECTRON ), 1 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::POSITRON ), 1 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::NEUTRON ), 1 );

  dispatcher->detachObserver( 1, estimator_1 );

  FRENSIE_CHECK_EQUAL( estimator_1.use_count(), 1 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 0 ).getNumberOfObservers( MonteCarlo::PHOTON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 0 ).getNumberOfObservers( MonteCarlo::ELECTRON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 0 ).getNumberOfObservers( MonteCarlo::POSITRON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 0 ).getNumberOfObservers( MonteCarlo::NEUTRON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::PHOTON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::ELECTRON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::POSITRON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::NEUTRON ), 0 );

  dispatcher->attachObserver( 0, estimator_1 );
  dispatcher->attachObserver( 1, estimator_1 );

  dispatcher->detachObserver( estimator_1 );

  FRENSIE_CHECK_EQUAL( estimator_1.use_count(), 1 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 0 ).getNumberOfObservers( MonteCarlo::PHOTON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 0 ).getNumberOfObservers( MonteCarlo::ELECTRON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 0 ).getNumberOfObservers( MonteCarlo::POSITRON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 0 ).getNumberOfObservers( MonteCarlo::NEUTRON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::PHOTON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::ELECTRON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::POSITRON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::NEUTRON ), 0 );
}

//---------------------------------------------------------------------------//
// Check that a surface crossing event can be dispatched
FRENSIE_UNIT_TEST( ParticleCrossingSurfaceEventDispatcher,
                   dispatchParticleCrossingSurfaceEvent )
{
  std::shared_ptr<MonteCarlo::ParticleCrossingSurfaceEventDispatcher>
    dispatcher( new MonteCarlo::ParticleCrossingSurfaceEventDispatcher );

  dispatcher->attachObserver( 0, estimator_1->getParticleTypes(), estimator_1 );
  dispatcher->attachObserver( 0, estimator_2->getParticleTypes(), estimator_2 );
  dispatcher->attachObserver( 0, estimator_3->getParticleTypes(), estimator_3 );

  dispatcher->attachObserver( 1, estimator_1->getParticleTypes(), estimator_1 );
  dispatcher->attachObserver( 1, estimator_2->getParticleTypes(), estimator_2 );
  dispatcher->attachObserver( 1, estimator_3->getParticleTypes(), estimator_3 );

  {
    MonteCarlo::PhotonState photon( 0ull );
    photon.setWeight( 1.0 );
    photon.setEnergy( 1.0 );

    FRENSIE_CHECK( !estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_3->hasUncommittedHistoryContribution() );

    dispatcher->dispatchParticleCrossingSurfaceEvent( photon, 0, 1.0 );

    FRENSIE_CHECK( estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_3->hasUncommittedHistoryContribution() );

    MonteCarlo::ElectronState electron( 0ull );
    electron.setWeight( 1.0 );
    electron.setEnergy( 1.0 );

    dispatcher->dispatchParticleCrossingSurfaceEvent( electron, 0, 1.0 );

    FRENSIE_CHECK( estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_3->hasUncommittedHistoryContribution() );

    estimator_1->commitHistoryContribution();
    estimator_2->commitHistoryContribution();
    estimator_3->commitHistoryContribution();

    Utility::ArrayView<const double> first_moments, second_moments;
    first_moments = estimator_1->getEntityBinDataFirstMoments( 0 );
    second_moments = estimator_1->getEntityBinDataSecondMoments( 0 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = estimator_1->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_1->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = estimator_2->getEntityBinDataFirstMoments( 0 );
    second_moments = estimator_2->getEntityBinDataSecondMoments( 0 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = estimator_2->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_2->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = estimator_3->getEntityBinDataFirstMoments( 0 );
    second_moments = estimator_3->getEntityBinDataSecondMoments( 0 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {-1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = estimator_3->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_3->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );
  }

  {
    MonteCarlo::PhotonState photon( 0ull );
    photon.setWeight( 1.0 );
    photon.setEnergy( 1.0 );

    FRENSIE_CHECK( !estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_3->hasUncommittedHistoryContribution() );

    dispatcher->dispatchParticleCrossingSurfaceEvent( photon, 1, 1.0 );

    FRENSIE_CHECK( estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_3->hasUncommittedHistoryContribution() );

    MonteCarlo::ElectronState electron( 0ull );
    electron.setWeight( 1.0 );
    electron.setEnergy( 1.0 );

    dispatcher->dispatchParticleCrossingSurfaceEvent( electron, 1, 1.0 );

    FRENSIE_CHECK( estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_3->hasUncommittedHistoryContribution() );

    estimator_1->commitHistoryContribution();
    estimator_2->commitHistoryContribution();
    estimator_3->commitHistoryContribution();

    Utility::ArrayView<const double> first_moments, second_moments;
    first_moments = estimator_1->getEntityBinDataFirstMoments( 0 );
    second_moments = estimator_1->getEntityBinDataSecondMoments( 0 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = estimator_1->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_1->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = estimator_2->getEntityBinDataFirstMoments( 0 );
    second_moments = estimator_2->getEntityBinDataSecondMoments( 0 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = estimator_2->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_2->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = estimator_3->getEntityBinDataFirstMoments( 0 );
    second_moments = estimator_3->getEntityBinDataSecondMoments( 0 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {-1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = estimator_3->getEntityBinDataFirstMoments( 1 );
    second_moments = estimator_3->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {-1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );
  }
}

//---------------------------------------------------------------------------//
// Check that an event dispatcher can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( ParticleCrossingSurfaceEventDispatcher,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_particle_crossing_surface_event_dispatcher" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::shared_ptr<MonteCarlo::WeightMultipliedSurfaceCurrentEstimator>
      local_estimator_1;

    std::shared_ptr<MonteCarlo::WeightAndEnergyMultipliedSurfaceFluxEstimator>
      local_estimator_2;

    std::shared_ptr<MonteCarlo::WeightAndChargeMultipliedSurfaceFluxEstimator>
      local_estimator_3;

    {
      // Set the entity ids
      std::vector<Geometry::Model::EntityId> surface_ids( {0, 1 } );
      std::vector<double> surface_areas( {1.0, 2.0} );

      local_estimator_1.reset( new MonteCarlo::WeightMultipliedSurfaceCurrentEstimator(
                                                               10,
                                                               1.0,
                                                               surface_ids ) );

      local_estimator_1->setParticleTypes( std::vector<MonteCarlo::ParticleType>( {MonteCarlo::PHOTON} ) );

      local_estimator_2.reset( new MonteCarlo::WeightAndEnergyMultipliedSurfaceFluxEstimator(
                                                             11,
                                                             10.0,
                                                             surface_ids,
                                                             surface_areas ) );

      local_estimator_2->setParticleTypes( std::vector<MonteCarlo::ParticleType>( {MonteCarlo::ELECTRON} ) );

      local_estimator_3.reset( new MonteCarlo::WeightAndChargeMultipliedSurfaceFluxEstimator(
                                                              12,
                                                              1.0,
                                                              surface_ids,
                                                              surface_areas ) );

      local_estimator_3->setParticleTypes( std::vector<MonteCarlo::ParticleType>( {MonteCarlo::ELECTRON} ) );
    }

    std::shared_ptr<MonteCarlo::ParticleCrossingSurfaceEventDispatcher>
      dispatcher( new MonteCarlo::ParticleCrossingSurfaceEventDispatcher );

    dispatcher->attachObserver( 0, local_estimator_1->getParticleTypes(), local_estimator_1 );
    dispatcher->attachObserver( 0, local_estimator_2->getParticleTypes(), local_estimator_2 );
    dispatcher->attachObserver( 0, local_estimator_3->getParticleTypes(), local_estimator_3 );

    dispatcher->attachObserver( 1, local_estimator_1->getParticleTypes(), local_estimator_1 );
    dispatcher->attachObserver( 1, local_estimator_2->getParticleTypes(), local_estimator_2 );
    dispatcher->attachObserver( 1, local_estimator_3->getParticleTypes(), local_estimator_3 );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(local_estimator_1) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(local_estimator_2) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(local_estimator_3) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(dispatcher) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::shared_ptr<MonteCarlo::WeightMultipliedSurfaceCurrentEstimator>
    local_estimator_1;

  std::shared_ptr<MonteCarlo::WeightAndEnergyMultipliedSurfaceFluxEstimator>
    local_estimator_2;

  std::shared_ptr<MonteCarlo::WeightAndChargeMultipliedSurfaceFluxEstimator>
    local_estimator_3;

  std::shared_ptr<MonteCarlo::ParticleCrossingSurfaceEventDispatcher>
    dispatcher;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(local_estimator_1) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(local_estimator_2) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(local_estimator_3) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(dispatcher) );

  iarchive.reset();

  {
    FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 0 ).getNumberOfObservers( MonteCarlo::PHOTON ), 1 );
    FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 0 ).getNumberOfObservers( MonteCarlo::ELECTRON ), 2 );

    MonteCarlo::PhotonState photon( 0ull );
    photon.setWeight( 1.0 );
    photon.setEnergy( 1.0 );

    FRENSIE_CHECK( !local_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !local_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !local_estimator_3->hasUncommittedHistoryContribution() );

    dispatcher->dispatchParticleCrossingSurfaceEvent( photon, 0, 1.0 );

    FRENSIE_CHECK( local_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !local_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !local_estimator_3->hasUncommittedHistoryContribution() );

    MonteCarlo::ElectronState electron( 0ull );
    electron.setWeight( 1.0 );
    electron.setEnergy( 1.0 );

    dispatcher->dispatchParticleCrossingSurfaceEvent( electron, 0, 1.0 );

    FRENSIE_CHECK( local_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( local_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( local_estimator_3->hasUncommittedHistoryContribution() );

    local_estimator_1->commitHistoryContribution();
    local_estimator_2->commitHistoryContribution();
    local_estimator_3->commitHistoryContribution();

    Utility::ArrayView<const double> first_moments, second_moments;
    first_moments = local_estimator_1->getEntityBinDataFirstMoments( 0 );
    second_moments = local_estimator_1->getEntityBinDataSecondMoments( 0 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = local_estimator_1->getEntityBinDataFirstMoments( 1 );
    second_moments = local_estimator_1->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = local_estimator_2->getEntityBinDataFirstMoments( 0 );
    second_moments = local_estimator_2->getEntityBinDataSecondMoments( 0 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = local_estimator_2->getEntityBinDataFirstMoments( 1 );
    second_moments = local_estimator_2->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );

    first_moments = local_estimator_3->getEntityBinDataFirstMoments( 0 );
    second_moments = local_estimator_3->getEntityBinDataSecondMoments( 0 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {-1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = local_estimator_3->getEntityBinDataFirstMoments( 1 );
    second_moments = local_estimator_3->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {0.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {0.0} ) );
  }

  {
    FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::PHOTON ), 1 );
    FRENSIE_CHECK_EQUAL( dispatcher->getLocalDispatcher( 1 ).getNumberOfObservers( MonteCarlo::ELECTRON ), 2 );

    MonteCarlo::PhotonState photon( 0ull );
    photon.setWeight( 1.0 );
    photon.setEnergy( 1.0 );

    FRENSIE_CHECK( !local_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !local_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !local_estimator_3->hasUncommittedHistoryContribution() );

    dispatcher->dispatchParticleCrossingSurfaceEvent( photon, 1, 1.0 );

    FRENSIE_CHECK( local_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !local_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !local_estimator_3->hasUncommittedHistoryContribution() );

    MonteCarlo::ElectronState electron( 0ull );
    electron.setWeight( 1.0 );
    electron.setEnergy( 1.0 );

    dispatcher->dispatchParticleCrossingSurfaceEvent( electron, 1, 1.0 );

    FRENSIE_CHECK( local_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( local_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( local_estimator_3->hasUncommittedHistoryContribution() );

    local_estimator_1->commitHistoryContribution();
    local_estimator_2->commitHistoryContribution();
    local_estimator_3->commitHistoryContribution();

    Utility::ArrayView<const double> first_moments, second_moments;
    first_moments = local_estimator_1->getEntityBinDataFirstMoments( 0 );
    second_moments = local_estimator_1->getEntityBinDataSecondMoments( 0 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = local_estimator_1->getEntityBinDataFirstMoments( 1 );
    second_moments = local_estimator_1->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = local_estimator_2->getEntityBinDataFirstMoments( 0 );
    second_moments = local_estimator_2->getEntityBinDataSecondMoments( 0 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = local_estimator_2->getEntityBinDataFirstMoments( 1 );
    second_moments = local_estimator_2->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = local_estimator_3->getEntityBinDataFirstMoments( 0 );
    second_moments = local_estimator_3->getEntityBinDataSecondMoments( 0 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {-1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );

    first_moments = local_estimator_3->getEntityBinDataFirstMoments( 1 );
    second_moments = local_estimator_3->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {-1.0} ) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1.0} ) );
  }
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Set the entity ids
  std::vector<Geometry::Model::EntityId> surface_ids( {0, 1 } );
  std::vector<double> surface_areas( {1.0, 2.0} );

  estimator_1.reset( new MonteCarlo::WeightMultipliedSurfaceCurrentEstimator(
                                                               0,
                                                               1.0,
                                                               surface_ids ) );

  estimator_1->setParticleTypes( std::vector<MonteCarlo::ParticleType>( {MonteCarlo::PHOTON} ) );

  estimator_2.reset( new MonteCarlo::WeightAndEnergyMultipliedSurfaceFluxEstimator(
                                                             1,
                                                             10.0,
                                                             surface_ids,
                                                             surface_areas ) );

  estimator_2->setParticleTypes( std::vector<MonteCarlo::ParticleType>( {MonteCarlo::ELECTRON} ) );

  estimator_3.reset( new MonteCarlo::WeightAndChargeMultipliedSurfaceFluxEstimator(
                                                              2,
                                                              1.0,
                                                              surface_ids,
                                                              surface_areas ) );

  estimator_3->setParticleTypes( std::vector<MonteCarlo::ParticleType>( {MonteCarlo::ELECTRON} ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstParticleCrossingSurfaceEventDispatcher.cpp
//---------------------------------------------------------------------------//
