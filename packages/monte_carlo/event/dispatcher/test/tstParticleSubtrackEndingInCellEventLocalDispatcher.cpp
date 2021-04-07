//---------------------------------------------------------------------------//
//!
//! \file   tstParticleSubtrackEndingInCellEventLocalDispatcher.cpp
//! \author Alex Robinson
//! \brief  Particle subtrack ending in cell event local dispatcher unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_CellTrackLengthFluxEstimator.hpp"
#include "MonteCarlo_ParticleSubtrackEndingInCellEventLocalDispatcher.hpp"
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
std::shared_ptr<MonteCarlo::WeightMultipliedCellTrackLengthFluxEstimator>
estimator_1;

std::shared_ptr<MonteCarlo::WeightAndEnergyMultipliedCellTrackLengthFluxEstimator>
estimator_2;

std::shared_ptr<MonteCarlo::WeightAndChargeMultipliedCellTrackLengthFluxEstimator>
estimator_3;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the cell id associated with the dispatcher can be returned
FRENSIE_UNIT_TEST( ParticleSubtrackEndingInCellEventDispatcher, getEntityId )
{
  std::shared_ptr<MonteCarlo::ParticleSubtrackEndingInCellEventLocalDispatcher>
    dispatcher_0( new MonteCarlo::ParticleSubtrackEndingInCellEventLocalDispatcher( 0 ) );

  std::shared_ptr<MonteCarlo::ParticleSubtrackEndingInCellEventLocalDispatcher>
    dispatcher_1( new MonteCarlo::ParticleSubtrackEndingInCellEventLocalDispatcher( 1 ) );

  FRENSIE_CHECK_EQUAL( dispatcher_0->getEntityId(), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher_1->getEntityId(), 1 );
}

//---------------------------------------------------------------------------//
// Check that observers can be managed
FRENSIE_UNIT_TEST( ParticleSubtrackEndingInCellEventDispatcher, manage_observers )
{
  std::shared_ptr<MonteCarlo::ParticleSubtrackEndingInCellEventLocalDispatcher>
    dispatcher_0( new MonteCarlo::ParticleSubtrackEndingInCellEventLocalDispatcher( 0 ) );

  dispatcher_0->attachObserver( estimator_1 );

  FRENSIE_CHECK( estimator_1.use_count() > 1 );
  FRENSIE_CHECK_EQUAL( dispatcher_0->getNumberOfObservers( MonteCarlo::PHOTON ), 1 );
  FRENSIE_CHECK_EQUAL( dispatcher_0->getNumberOfObservers( MonteCarlo::ELECTRON ), 1 );
  FRENSIE_CHECK_EQUAL( dispatcher_0->getNumberOfObservers( MonteCarlo::POSITRON ), 1 );
  FRENSIE_CHECK_EQUAL( dispatcher_0->getNumberOfObservers( MonteCarlo::NEUTRON ), 1 );

  dispatcher_0->detachAllObservers();

  FRENSIE_CHECK_EQUAL( estimator_1.use_count(), 1 );
  FRENSIE_CHECK_EQUAL( dispatcher_0->getNumberOfObservers( MonteCarlo::PHOTON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher_0->getNumberOfObservers( MonteCarlo::ELECTRON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher_0->getNumberOfObservers( MonteCarlo::POSITRON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher_0->getNumberOfObservers( MonteCarlo::NEUTRON ), 0 );

  dispatcher_0->attachObserver( {MonteCarlo::PHOTON}, estimator_1 );

  FRENSIE_CHECK_EQUAL( estimator_1.use_count(), 2 );
  FRENSIE_CHECK_EQUAL( dispatcher_0->getNumberOfObservers( MonteCarlo::PHOTON ), 1 );
  FRENSIE_CHECK_EQUAL( dispatcher_0->getNumberOfObservers( MonteCarlo::ELECTRON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher_0->getNumberOfObservers( MonteCarlo::POSITRON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher_0->getNumberOfObservers( MonteCarlo::NEUTRON ), 0 );

  dispatcher_0->detachObserver( estimator_1 );

  FRENSIE_CHECK_EQUAL( estimator_1.use_count(), 1 );
  FRENSIE_CHECK_EQUAL( dispatcher_0->getNumberOfObservers( MonteCarlo::PHOTON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher_0->getNumberOfObservers( MonteCarlo::ELECTRON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher_0->getNumberOfObservers( MonteCarlo::POSITRON ), 0 );
  FRENSIE_CHECK_EQUAL( dispatcher_0->getNumberOfObservers( MonteCarlo::NEUTRON ), 0 );
}

//---------------------------------------------------------------------------//
// Check that a subtrack ending event can be dispatched
FRENSIE_UNIT_TEST( ParticleSubtrackEndingInCellEventDispatcher,
		   dispatchParticleSubtrackEndingInCellEvent )
{
  std::shared_ptr<MonteCarlo::ParticleSubtrackEndingInCellEventLocalDispatcher>
    dispatcher_0( new MonteCarlo::ParticleSubtrackEndingInCellEventLocalDispatcher( 0 ) );

  std::shared_ptr<MonteCarlo::ParticleSubtrackEndingInCellEventLocalDispatcher>
    dispatcher_1( new MonteCarlo::ParticleSubtrackEndingInCellEventLocalDispatcher( 1 ) );

  dispatcher_0->attachObserver( estimator_1->getParticleTypes(), estimator_1 );
  dispatcher_0->attachObserver( estimator_2->getParticleTypes(), estimator_2 );
  dispatcher_0->attachObserver( estimator_3->getParticleTypes(), estimator_3 );

  dispatcher_1->attachObserver( estimator_1->getParticleTypes(), estimator_1 );
  dispatcher_1->attachObserver( estimator_2->getParticleTypes(), estimator_2 );
  dispatcher_1->attachObserver( estimator_3->getParticleTypes(), estimator_3 );

  {
    MonteCarlo::PhotonState photon( 0ull );
    photon.setWeight( 1.0 );
    photon.setEnergy( 1.0 );

    FRENSIE_CHECK( !estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_3->hasUncommittedHistoryContribution() );

    dispatcher_0->dispatchParticleSubtrackEndingInCellEvent( photon, 0, 1.0 );

    FRENSIE_CHECK( estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_3->hasUncommittedHistoryContribution() );

    MonteCarlo::ElectronState electron( 0ull );
    electron.setWeight( 1.0 );
    electron.setEnergy( 1.0 );

    dispatcher_0->dispatchParticleSubtrackEndingInCellEvent( electron, 0, 1.0 );

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

    dispatcher_1->dispatchParticleSubtrackEndingInCellEvent( photon, 1, 1.0 );

    FRENSIE_CHECK( estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !estimator_3->hasUncommittedHistoryContribution() );

    MonteCarlo::ElectronState electron( 0ull );
    electron.setWeight( 1.0 );
    electron.setEnergy( 1.0 );

    dispatcher_1->dispatchParticleSubtrackEndingInCellEvent( electron, 1, 1.0 );

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
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( ParticleSubtrackEndingInCellEventLocalDispatcher,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_particle_subtrack_ending_in_cell_event_local_dispatcher" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::shared_ptr<MonteCarlo::WeightMultipliedCellTrackLengthFluxEstimator>
      local_estimator_1;

    std::shared_ptr<MonteCarlo::WeightAndEnergyMultipliedCellTrackLengthFluxEstimator>
      local_estimator_2;

    std::shared_ptr<MonteCarlo::WeightAndChargeMultipliedCellTrackLengthFluxEstimator>
      local_estimator_3;

    {
      std::vector<Geometry::Model::EntityId>
        cell_ids( 2 );
      cell_ids[0] = 0;
      cell_ids[1] = 1;

      std::vector<double> cell_volumes( 2 );
      cell_volumes[0] = 1.0;
      cell_volumes[1] = 2.0;

      local_estimator_1.reset( new MonteCarlo::WeightMultipliedCellTrackLengthFluxEstimator(
                                                              10,
                                                              1.0,
                                                              cell_ids,
                                                              cell_volumes ) );

      local_estimator_1->setParticleTypes( std::vector<MonteCarlo::ParticleType>( {MonteCarlo::PHOTON} ) );

      local_estimator_2.reset( new MonteCarlo::WeightAndEnergyMultipliedCellTrackLengthFluxEstimator(
                                                              11,
                                                              10.0,
                                                              cell_ids,
                                                              cell_volumes ) );

      local_estimator_2->setParticleTypes( std::vector<MonteCarlo::ParticleType>( {MonteCarlo::ELECTRON} ) );

      local_estimator_3.reset( new MonteCarlo::WeightAndChargeMultipliedCellTrackLengthFluxEstimator(
                                                              12,
                                                              1.0,
                                                              cell_ids,
                                                              cell_volumes ) );

      local_estimator_3->setParticleTypes( std::vector<MonteCarlo::ParticleType>( {MonteCarlo::ELECTRON} ) );
    }

    std::shared_ptr<MonteCarlo::ParticleSubtrackEndingInCellEventLocalDispatcher>
      dispatcher_0( new MonteCarlo::ParticleSubtrackEndingInCellEventLocalDispatcher( 0 ) );

    std::shared_ptr<MonteCarlo::ParticleSubtrackEndingInCellEventLocalDispatcher>
      dispatcher_1( new MonteCarlo::ParticleSubtrackEndingInCellEventLocalDispatcher( 1 ) );

    dispatcher_0->attachObserver( local_estimator_1->getParticleTypes(), local_estimator_1 );
    dispatcher_0->attachObserver( local_estimator_2->getParticleTypes(), local_estimator_2 );
    dispatcher_0->attachObserver( local_estimator_3->getParticleTypes(), local_estimator_3 );

    dispatcher_1->attachObserver( local_estimator_1->getParticleTypes(), local_estimator_1 );
    dispatcher_1->attachObserver( local_estimator_2->getParticleTypes(), local_estimator_2 );
    dispatcher_1->attachObserver( local_estimator_3->getParticleTypes(), local_estimator_3 );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(local_estimator_1) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(local_estimator_2) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(local_estimator_3) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(dispatcher_0) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP(dispatcher_1) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::shared_ptr<MonteCarlo::WeightMultipliedCellTrackLengthFluxEstimator>
    local_estimator_1;

  std::shared_ptr<MonteCarlo::WeightAndEnergyMultipliedCellTrackLengthFluxEstimator>
    local_estimator_2;

  std::shared_ptr<MonteCarlo::WeightAndChargeMultipliedCellTrackLengthFluxEstimator>
    local_estimator_3;

  std::shared_ptr<MonteCarlo::ParticleSubtrackEndingInCellEventLocalDispatcher>
    dispatcher_0, dispatcher_1;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(local_estimator_1) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(local_estimator_2) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(local_estimator_3) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(dispatcher_0) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP(dispatcher_1) );

  iarchive.reset();

  {
    FRENSIE_CHECK_EQUAL( dispatcher_0->getEntityId(), 0 );
    FRENSIE_CHECK_EQUAL( dispatcher_0->getNumberOfObservers( MonteCarlo::PHOTON ), 1 );
    FRENSIE_CHECK_EQUAL( dispatcher_0->getNumberOfObservers( MonteCarlo::ELECTRON ), 2 );

    MonteCarlo::PhotonState photon( 0ull );
    photon.setWeight( 1.0 );
    photon.setEnergy( 1.0 );

    FRENSIE_CHECK( !local_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !local_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !local_estimator_3->hasUncommittedHistoryContribution() );

    dispatcher_0->dispatchParticleSubtrackEndingInCellEvent( photon, 0, 1.0 );

    FRENSIE_CHECK( local_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !local_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !local_estimator_3->hasUncommittedHistoryContribution() );

    MonteCarlo::ElectronState electron( 0ull );
    electron.setWeight( 1.0 );
    electron.setEnergy( 1.0 );

    dispatcher_0->dispatchParticleSubtrackEndingInCellEvent( electron, 0, 1.0 );

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
    FRENSIE_CHECK_EQUAL( dispatcher_1->getEntityId(), 1 );
    FRENSIE_CHECK_EQUAL( dispatcher_1->getNumberOfObservers( MonteCarlo::PHOTON ), 1 );
    FRENSIE_CHECK_EQUAL( dispatcher_1->getNumberOfObservers( MonteCarlo::ELECTRON ), 2 );

    MonteCarlo::PhotonState photon( 0ull );
    photon.setWeight( 1.0 );
    photon.setEnergy( 1.0 );

    FRENSIE_CHECK( !local_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !local_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !local_estimator_3->hasUncommittedHistoryContribution() );

    dispatcher_1->dispatchParticleSubtrackEndingInCellEvent( photon, 1, 1.0 );

    FRENSIE_CHECK( local_estimator_1->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !local_estimator_2->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( !local_estimator_3->hasUncommittedHistoryContribution() );

    MonteCarlo::ElectronState electron( 0ull );
    electron.setWeight( 1.0 );
    electron.setEnergy( 1.0 );

    dispatcher_1->dispatchParticleSubtrackEndingInCellEvent( electron, 1, 1.0 );

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
  // Set the cells ids and volumes
  std::vector<Geometry::Model::EntityId> cell_ids( {0, 1} );
  std::vector<double> cell_volumes( {1.0, 2.0} );

  estimator_1.reset( new MonteCarlo::WeightMultipliedCellTrackLengthFluxEstimator(
                                                              0,
                                                              1.0,
                                                              cell_ids,
                                                              cell_volumes ) );

  estimator_1->setParticleTypes( std::vector<MonteCarlo::ParticleType>( {MonteCarlo::PHOTON} ) );

  estimator_2.reset( new MonteCarlo::WeightAndEnergyMultipliedCellTrackLengthFluxEstimator(
                                                              1,
                                                              10.0,
                                                              cell_ids,
                                                              cell_volumes ) );

  estimator_2->setParticleTypes( std::vector<MonteCarlo::ParticleType>( {MonteCarlo::ELECTRON} ) );

  estimator_3.reset( new MonteCarlo::WeightAndChargeMultipliedCellTrackLengthFluxEstimator(
                                                              2,
                                                              1.0,
                                                              cell_ids,
                                                              cell_volumes ) );

  estimator_3->setParticleTypes( std::vector<MonteCarlo::ParticleType>( {MonteCarlo::ELECTRON} ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstParticleSubtrackEndingInCellEventLocalDispatcher.cpp
//---------------------------------------------------------------------------//
