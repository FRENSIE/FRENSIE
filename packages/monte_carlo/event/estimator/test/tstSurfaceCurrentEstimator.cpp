//---------------------------------------------------------------------------//
//!
//! \file   tstSurfaceCurrentEstimator.cpp
//! \author Alex Robinson
//! \brief  Surface current estimator unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_SurfaceCurrentEstimator.hpp"
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
// Check that the estimator is a surface type estimator
FRENSIE_UNIT_TEST_TEMPLATE( SurfaceCurrentEstimator,
                            check_type,
                            MonteCarlo::WeightMultiplier,
                            MonteCarlo::WeightAndEnergyMultiplier,
                            MonteCarlo::WeightAndChargeMultiplier )
{
  FETCH_TEMPLATE_PARAM( 0, ContributionMultiplierPolicy );

  std::shared_ptr<MonteCarlo::Estimator> estimator;

  std::vector<MonteCarlo::StandardSurfaceEstimator::SurfaceIdType>
    surface_ids( 2 );
  surface_ids[0] = 0;
  surface_ids[1] = 1;

  std::vector<double> surface_areas( 2 );
  surface_areas[0] = 1.0;
  surface_areas[1] = 2.0;

  estimator.reset( new MonteCarlo::SurfaceCurrentEstimator<ContributionMultiplierPolicy>(
                                                               0u,
                                                               10.0,
                                                               surface_ids ) );

  FRENSIE_CHECK( !estimator->isCellEstimator() );
  FRENSIE_CHECK( estimator->isSurfaceEstimator() );
  FRENSIE_CHECK( !estimator->isMeshEstimator() );
}

//---------------------------------------------------------------------------//
// Check that the number of bins can be returned
FRENSIE_UNIT_TEST_TEMPLATE( SurfaceCurrentEstimator,
                            getNumberOfBins,
                            MonteCarlo::WeightMultiplier,
                            MonteCarlo::WeightAndEnergyMultiplier,
                            MonteCarlo::WeightAndChargeMultiplier )
{
  FETCH_TEMPLATE_PARAM( 0, ContributionMultiplierPolicy );

  std::shared_ptr<MonteCarlo::Estimator> estimator;

  std::vector<MonteCarlo::StandardSurfaceEstimator::SurfaceIdType>
    surface_ids( 2 );
  surface_ids[0] = 0;
  surface_ids[1] = 1;

  std::vector<double> surface_areas( 2 );
  surface_areas[0] = 1.0;
  surface_areas[1] = 2.0;

  estimator.reset( new MonteCarlo::SurfaceCurrentEstimator<ContributionMultiplierPolicy>(
                                                               0u,
                                                               10.0,
                                                               surface_ids ) );

  FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins(), 1u );

  // Set the energy bins
  std::vector<double> energy_bin_boundaries( 3 );
  energy_bin_boundaries[0] = 0.0;
  energy_bin_boundaries[1] = 0.1;
  energy_bin_boundaries[2] = 1.0;

  estimator->setDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION>(
                                                       energy_bin_boundaries );

  FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins(), 2u );

  // Set the cosine bins
  std::vector<double> cosine_bins( 3 );
  cosine_bins[0] = -1.0;
  cosine_bins[1] = 0.0;
  cosine_bins[2] = 1.0;

  estimator->setDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION>( cosine_bins );

  FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins(), 4u );

  // Set the time bins
  std::vector<double> time_bins( 3 );
  time_bins[0] = 0.0;
  time_bins[1] = 0.5;
  time_bins[2] = 1.0;

  estimator->setDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION>( time_bins );

  FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins(), 8u );

  // Set the collision number bins
  std::vector<unsigned> coll_bins( 2 );
  coll_bins[0] = 0u;
  coll_bins[1] = std::numeric_limits<unsigned>::max();

  estimator->setDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION>(
                                                                   coll_bins );

  FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins(), 16u );
}

//---------------------------------------------------------------------------//
// Check that a partial history contribution can be added to the estimator
FRENSIE_UNIT_TEST( SurfaceCurrentEstimator,
                   updateFromParticleCrossingSurfaceEvent )
{
  std::shared_ptr<MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightMultiplier> >
    estimator_1;
  std::shared_ptr<MonteCarlo::Estimator> estimator_1_base;

  std::shared_ptr<MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightAndEnergyMultiplier> >
    estimator_2;
  std::shared_ptr<MonteCarlo::Estimator> estimator_2_base;

  std::shared_ptr<MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightAndChargeMultiplier> >
    estimator_3;
  std::shared_ptr<MonteCarlo::Estimator> estimator_3_base;

  {
    // Set the surface ids
    std::vector<MonteCarlo::StandardSurfaceEstimator::SurfaceIdType>
      surface_ids( 2 );
    surface_ids[0] = 0;
    surface_ids[1] = 1;

    estimator_1.reset( new MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightMultiplier>(
                                                             0u,
                                                             10.0,
                                                             surface_ids ) );
    estimator_1_base = estimator_1;

    estimator_2.reset( new MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightAndEnergyMultiplier>(
                                                             1u,
                                                             10.0,
                                                             surface_ids ) );
    estimator_2_base = estimator_2;

    estimator_3.reset(
     new MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightAndChargeMultiplier>(
                                                             2u,
                                                             1.0,
                                                             surface_ids ) );
    estimator_3_base = estimator_3;

    // Set the energy bins
    std::vector<double> energy_bin_boundaries( 3 );
    energy_bin_boundaries[0] = 0.0;
    energy_bin_boundaries[1] = 0.1;
    energy_bin_boundaries[2] = 1.0;

    estimator_1_base->setDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION>(
                                                       energy_bin_boundaries );
    estimator_2_base->setDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION>(
                                                       energy_bin_boundaries );
    estimator_3_base->setDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION>(
                                                       energy_bin_boundaries );

    // Set the cosine bins
    std::vector<double> cosine_bins( 3 );
    cosine_bins[0] = -1.0;
    cosine_bins[1] = 0.0;
    cosine_bins[2] = 1.0;

    estimator_1_base->setDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION>(
                                                                 cosine_bins );
    estimator_2_base->setDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION>(
                                                                 cosine_bins );
    estimator_3_base->setDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION>(
                                                                 cosine_bins );

    // Set the time bins
    std::vector<double> time_bins( 3 );
    time_bins[0] = 0.0;
    time_bins[1] = 1.0;
    time_bins[2] = 2.0;

    estimator_1_base->setDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION>(time_bins );
    estimator_2_base->setDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION>(time_bins );
    estimator_3_base->setDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION>(time_bins );

    // Set the collision number bins
    std::vector<unsigned> collision_number_bins( 2 );
    collision_number_bins[0] = 0u;
    collision_number_bins[1] = 1u;

    estimator_1_base->setDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION>(
                                                       collision_number_bins );
    estimator_2_base->setDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION>(
                                                       collision_number_bins );
    estimator_3_base->setDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION>(
                                                       collision_number_bins );

    // Set the particle types
    std::vector<MonteCarlo::ParticleType> particle_types( 1 );
    particle_types[0] = MonteCarlo::ELECTRON;

    estimator_1_base->setParticleTypes( particle_types );
    estimator_2_base->setParticleTypes( particle_types );
    estimator_3_base->setParticleTypes( particle_types );
  }

  FRENSIE_CHECK( !estimator_1_base->hasUncommittedHistoryContribution() );
  FRENSIE_CHECK( !estimator_2_base->hasUncommittedHistoryContribution() );
  FRENSIE_CHECK( !estimator_3_base->hasUncommittedHistoryContribution() );

  // bin 0
  MonteCarlo::ElectronState particle( 0u );
  particle.setEnergy( 1.0 );
  particle.setTime( 2.0 );

  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

  estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
  estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

  FRENSIE_CHECK( estimator_1_base->hasUncommittedHistoryContribution() );
  FRENSIE_CHECK( estimator_2_base->hasUncommittedHistoryContribution() );
  FRENSIE_CHECK( estimator_3_base->hasUncommittedHistoryContribution() );

  // bin 1
  particle.setEnergy( 0.1 );

  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

  particle.setWeight( 10.0 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

  particle.setWeight( 1.0 );
  estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
  estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

  // bin 2
  particle.setEnergy( 1.0 );
  particle.setWeight( 1.0 );

  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

  estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
  estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

  // bin 3
  particle.setEnergy( 0.1 );

  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

  particle.setWeight( 10.0 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

  particle.setWeight( 1.0 );
  estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
  estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

  // bin 4
  particle.setEnergy( 1.0 );
  particle.setTime( 1.0 );
  particle.setWeight( 1.0 );

  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

  estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
  estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

  // bin 5
  particle.setEnergy( 0.1 );

  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

  particle.setWeight( 10.0 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

  particle.setWeight( 1.0 );
  estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
  estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

  // bin 6
  particle.setEnergy( 1.0 );
  particle.setWeight( 1.0 );

  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

  estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
  estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

  // bin 7
  particle.setEnergy( 0.1 );

  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

  particle.setWeight( 10.0 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

  particle.setWeight( 1.0 );
  estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
  estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

  // bin 8
  particle.setEnergy( 1.0 );
  particle.setTime( 2.0 );
  particle.incrementCollisionNumber();
  particle.setWeight( 1.0 );

  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

  estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
  estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

  // bin 9
  particle.setEnergy( 0.1 );

  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

  particle.setWeight( 10.0 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

  particle.setWeight( 1.0 );
  estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
  estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

  // bin 10
  particle.setEnergy( 1.0 );
  particle.setWeight( 1.0 );

  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

  estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
  estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

  // bin 11
  particle.setEnergy( 0.1 );

  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

  particle.setWeight( 10.0 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

  particle.setWeight( 1.0 );
  estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
  estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

  // bin 12
  particle.setEnergy( 1.0 );
  particle.setTime( 1.0 );
  particle.setWeight( 1.0 );

  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

  estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
  estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

  // bin 13
  particle.setEnergy( 0.1 );

  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

  particle.setWeight( 10.0 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

  particle.setWeight( 1.0 );
  estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
  estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

  // bin 14
  particle.setEnergy( 1.0 );
  particle.setWeight( 1.0 );

  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

  estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
  estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

  // bin 15
  particle.setEnergy( 0.1 );

  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

  particle.setWeight( 10.0 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

  particle.setWeight( 1.0 );
  estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
  estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

  // Commit the contributions
  estimator_1_base->commitHistoryContribution();
  estimator_2_base->commitHistoryContribution();
  estimator_3_base->commitHistoryContribution();

  FRENSIE_CHECK( !estimator_1_base->hasUncommittedHistoryContribution() );
  FRENSIE_CHECK( !estimator_2_base->hasUncommittedHistoryContribution() );
  FRENSIE_CHECK( !estimator_3_base->hasUncommittedHistoryContribution() );

  MonteCarlo::Estimator::setNumberOfHistories( 1.0 );
  MonteCarlo::Estimator::setElapsedTime( 1.0 );

  // Check the entity bin data moments
  Utility::ArrayView<const double> entity_bin_first_moments =
    estimator_1_base->getEntityBinDataFirstMoments( 0 );

  Utility::ArrayView<const double> entity_bin_second_moments =
    estimator_1_base->getEntityBinDataSecondMoments( 0 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 16, 1.0 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 16, 1.0 ) );

  entity_bin_first_moments =
    estimator_1_base->getEntityBinDataFirstMoments( 1 );

  entity_bin_second_moments =
    estimator_1_base->getEntityBinDataSecondMoments( 1 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 16, 1.0 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 16, 1.0 ) );

  entity_bin_first_moments =
    estimator_2_base->getEntityBinDataFirstMoments( 0 );

  entity_bin_second_moments =
    estimator_2_base->getEntityBinDataSecondMoments( 0 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 16, 1.0 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 16, 1.0 ) );

  entity_bin_first_moments =
    estimator_2_base->getEntityBinDataFirstMoments( 1 );

  entity_bin_second_moments =
    estimator_2_base->getEntityBinDataSecondMoments( 1 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 16, 1.0 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 16, 1.0 ) );

  entity_bin_first_moments =
    estimator_3_base->getEntityBinDataFirstMoments( 0 );

  entity_bin_second_moments =
    estimator_3_base->getEntityBinDataSecondMoments( 0 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 16, -1.0 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 16, 1.0 ) );

  entity_bin_first_moments =
    estimator_3_base->getEntityBinDataFirstMoments( 1 );

  entity_bin_second_moments =
    estimator_3_base->getEntityBinDataSecondMoments( 1 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 16, -1.0 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 16, 1.0 ) );

  // Check the total bin data moments
  Utility::ArrayView<const double> total_bin_first_moments =
    estimator_1_base->getTotalBinDataFirstMoments();

  Utility::ArrayView<const double> total_bin_second_moments =
    estimator_1_base->getTotalBinDataSecondMoments();

  FRENSIE_CHECK_EQUAL( total_bin_first_moments,
                       std::vector<double>( 16, 2.0 ) );
  FRENSIE_CHECK_EQUAL( total_bin_second_moments,
                       std::vector<double>( 16, 4.0 ) );

  total_bin_first_moments = estimator_2_base->getTotalBinDataFirstMoments();
  total_bin_second_moments = estimator_2_base->getTotalBinDataSecondMoments();

  FRENSIE_CHECK_EQUAL( total_bin_first_moments,
                       std::vector<double>( 16, 2.0 ) );
  FRENSIE_CHECK_EQUAL( total_bin_second_moments,
                       std::vector<double>( 16, 4.0 ) );

  total_bin_first_moments = estimator_3_base->getTotalBinDataFirstMoments();
  total_bin_second_moments = estimator_3_base->getTotalBinDataSecondMoments();

  FRENSIE_CHECK_EQUAL( total_bin_first_moments,
                       std::vector<double>( 16, -2.0 ) );
  FRENSIE_CHECK_EQUAL( total_bin_second_moments,
                       std::vector<double>( 16, 4.0 ) );

  // Check the entity total data moments
  Utility::ArrayView<const double> entity_total_first_moments =
    estimator_1_base->getEntityTotalDataFirstMoments( 0 );

  Utility::ArrayView<const double> entity_total_second_moments =
    estimator_1_base->getEntityTotalDataSecondMoments( 0 );

  Utility::ArrayView<const double> entity_total_third_moments =
    estimator_1_base->getEntityTotalDataThirdMoments( 0 );

  Utility::ArrayView<const double> entity_total_fourth_moments =
    estimator_1_base->getEntityTotalDataFourthMoments( 0 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, 16.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 256.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, 4096.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 65536.0 ) );

  entity_total_first_moments =
    estimator_1_base->getEntityTotalDataFirstMoments( 1 );

  entity_total_second_moments =
    estimator_1_base->getEntityTotalDataSecondMoments( 1 );

  entity_total_third_moments =
    estimator_1_base->getEntityTotalDataThirdMoments( 1 );

  entity_total_fourth_moments =
    estimator_1_base->getEntityTotalDataFourthMoments( 1 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, 16.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 256.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, 4096.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 65536.0 ) );

  entity_total_first_moments =
    estimator_2_base->getEntityTotalDataFirstMoments( 0 );

  entity_total_second_moments =
    estimator_2_base->getEntityTotalDataSecondMoments( 0 );

  entity_total_third_moments =
    estimator_2_base->getEntityTotalDataThirdMoments( 0 );

  entity_total_fourth_moments =
    estimator_2_base->getEntityTotalDataFourthMoments( 0 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, 16.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 256.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, 4096.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 65536.0 ) );

  entity_total_first_moments =
    estimator_2_base->getEntityTotalDataFirstMoments( 1 );

  entity_total_second_moments =
    estimator_2_base->getEntityTotalDataSecondMoments( 1 );

  entity_total_third_moments =
    estimator_2_base->getEntityTotalDataThirdMoments( 1 );

  entity_total_fourth_moments =
    estimator_2_base->getEntityTotalDataFourthMoments( 1 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, 16.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 256.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, 4096.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 65536.0 ) );

  entity_total_first_moments =
    estimator_3_base->getEntityTotalDataFirstMoments( 0 );

  entity_total_second_moments =
    estimator_3_base->getEntityTotalDataSecondMoments( 0 );

  entity_total_third_moments =
    estimator_3_base->getEntityTotalDataThirdMoments( 0 );

  entity_total_fourth_moments =
    estimator_3_base->getEntityTotalDataFourthMoments( 0 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, -16.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 256.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, -4096.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 65536.0 ) );

  entity_total_first_moments =
    estimator_3_base->getEntityTotalDataFirstMoments( 1 );

  entity_total_second_moments =
    estimator_3_base->getEntityTotalDataSecondMoments( 1 );

  entity_total_third_moments =
    estimator_3_base->getEntityTotalDataThirdMoments( 1 );

  entity_total_fourth_moments =
    estimator_3_base->getEntityTotalDataFourthMoments( 1 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, -16.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 256.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, -4096.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 65536.0 ) );

  // Check the total data moments
  Utility::ArrayView<const double> total_first_moments =
    estimator_1_base->getTotalDataFirstMoments();

  Utility::ArrayView<const double> total_second_moments =
    estimator_1_base->getTotalDataSecondMoments();

  Utility::ArrayView<const double> total_third_moments =
    estimator_1_base->getTotalDataThirdMoments();

  Utility::ArrayView<const double> total_fourth_moments =
    estimator_1_base->getTotalDataFourthMoments();

  FRENSIE_CHECK_EQUAL( total_first_moments,
                       std::vector<double>( 1, 32.0 ) );
  FRENSIE_CHECK_EQUAL( total_second_moments,
                       std::vector<double>( 1, 1024.0 ) );
  FRENSIE_CHECK_EQUAL( total_third_moments,
                       std::vector<double>( 1, 32768.0 ) );
  FRENSIE_CHECK_EQUAL( total_fourth_moments,
                       std::vector<double>( 1, 1048576.0 ) );

  total_first_moments = estimator_2_base->getTotalDataFirstMoments();
  total_second_moments = estimator_2_base->getTotalDataSecondMoments();
  total_third_moments = estimator_2_base->getTotalDataThirdMoments();
  total_fourth_moments = estimator_2_base->getTotalDataFourthMoments();

  FRENSIE_CHECK_EQUAL( total_first_moments,
                       std::vector<double>( 1, 32.0 ) );
  FRENSIE_CHECK_EQUAL( total_second_moments,
                       std::vector<double>( 1, 1024.0 ) );
  FRENSIE_CHECK_EQUAL( total_third_moments,
                       std::vector<double>( 1, 32768.0 ) );
  FRENSIE_CHECK_EQUAL( total_fourth_moments,
                       std::vector<double>( 1, 1048576.0 ) );

  total_first_moments = estimator_3_base->getTotalDataFirstMoments();
  total_second_moments = estimator_3_base->getTotalDataSecondMoments();
  total_third_moments = estimator_3_base->getTotalDataThirdMoments();
  total_fourth_moments = estimator_3_base->getTotalDataFourthMoments();

  FRENSIE_CHECK_EQUAL( total_first_moments,
                       std::vector<double>( 1, -32.0 ) );
  FRENSIE_CHECK_EQUAL( total_second_moments,
                       std::vector<double>( 1, 1024.0 ) );
  FRENSIE_CHECK_EQUAL( total_third_moments,
                       std::vector<double>( 1, -32768.0 ) );
  FRENSIE_CHECK_EQUAL( total_fourth_moments,
                       std::vector<double>( 1, 1048576.0 ) );
}

//---------------------------------------------------------------------------//
// Check that a partial history contribution can be added to the estimator
FRENSIE_UNIT_TEST( SurfaceCurrentEstimator,
                   updateFromParticleCrossingSurfaceEvent_thread_safe )
{
  std::shared_ptr<MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightMultiplier> >
    estimator_1;
  std::shared_ptr<MonteCarlo::Estimator> estimator_1_base;

  std::shared_ptr<MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightAndEnergyMultiplier> >
    estimator_2;
  std::shared_ptr<MonteCarlo::Estimator> estimator_2_base;

  std::shared_ptr<MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightAndChargeMultiplier> >
    estimator_3;
  std::shared_ptr<MonteCarlo::Estimator> estimator_3_base;

  {
    // Set the surface ids
    std::vector<MonteCarlo::StandardSurfaceEstimator::SurfaceIdType>
      surface_ids( 2 );
    surface_ids[0] = 0;
    surface_ids[1] = 1;

    estimator_1.reset( new MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightMultiplier>(
                                                             0u,
                                                             10.0,
                                                             surface_ids ) );
    estimator_1_base = estimator_1;

    estimator_2.reset( new MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightAndEnergyMultiplier>(
                                                             1u,
                                                             10.0,
                                                             surface_ids ) );
    estimator_2_base = estimator_2;

    estimator_3.reset(
     new MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightAndChargeMultiplier>(
                                                             2u,
                                                             1.0,
                                                             surface_ids ) );
    estimator_3_base = estimator_3;

    // Set the energy bins
    std::vector<double> energy_bin_boundaries( 3 );
    energy_bin_boundaries[0] = 0.0;
    energy_bin_boundaries[1] = 0.1;
    energy_bin_boundaries[2] = 1.0;

    estimator_1_base->setDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION>(
                                                       energy_bin_boundaries );
    estimator_2_base->setDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION>(
                                                       energy_bin_boundaries );
    estimator_3_base->setDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION>(
                                                       energy_bin_boundaries );

    // Set the cosine bins
    std::vector<double> cosine_bins( 3 );
    cosine_bins[0] = -1.0;
    cosine_bins[1] = 0.0;
    cosine_bins[2] = 1.0;

    estimator_1_base->setDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION>(
                                                                 cosine_bins );
    estimator_2_base->setDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION>(
                                                                 cosine_bins );
    estimator_3_base->setDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION>(
                                                                 cosine_bins );

    // Set the time bins
    std::vector<double> time_bins( 3 );
    time_bins[0] = 0.0;
    time_bins[1] = 1.0;
    time_bins[2] = 2.0;

    estimator_1_base->setDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION>(time_bins );
    estimator_2_base->setDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION>(time_bins );
    estimator_3_base->setDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION>(time_bins );

    // Set the collision number bins
    std::vector<unsigned> collision_number_bins( 2 );
    collision_number_bins[0] = 0u;
    collision_number_bins[1] = 1u;

    estimator_1_base->setDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION>(
                                                       collision_number_bins );
    estimator_2_base->setDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION>(
                                                       collision_number_bins );
    estimator_3_base->setDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION>(
                                                       collision_number_bins );

    // Set the particle types
    std::vector<MonteCarlo::ParticleType> particle_types( 1 );
    particle_types[0] = MonteCarlo::ELECTRON;

    estimator_1_base->setParticleTypes( particle_types );
    estimator_2_base->setParticleTypes( particle_types );
    estimator_3_base->setParticleTypes( particle_types );

    // Enable thread support
    estimator_1_base->enableThreadSupport( Utility::OpenMPProperties::getRequestedNumberOfThreads() );
    estimator_2_base->enableThreadSupport( Utility::OpenMPProperties::getRequestedNumberOfThreads() );
    estimator_3_base->enableThreadSupport( Utility::OpenMPProperties::getRequestedNumberOfThreads() );
  }

  FRENSIE_CHECK( !estimator_1_base->hasUncommittedHistoryContribution() );
  FRENSIE_CHECK( !estimator_2_base->hasUncommittedHistoryContribution() );
  FRENSIE_CHECK( !estimator_3_base->hasUncommittedHistoryContribution() );

  unsigned threads =
    Utility::OpenMPProperties::getRequestedNumberOfThreads();

  #pragma omp parallel num_threads( threads )
  {
    // bin 0
    MonteCarlo::ElectronState particle( 0u );
    particle.setEnergy( 1.0 );
    particle.setTime( 2.0 );

    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    FRENSIE_CHECK( estimator_1_base->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_2_base->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_3_base->hasUncommittedHistoryContribution() );

    // bin 1
    particle.setEnergy( 0.1 );

    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    particle.setWeight( 10.0 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    particle.setWeight( 1.0 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    // bin 2
    particle.setEnergy( 1.0 );
    particle.setWeight( 1.0 );

    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    // bin 3
    particle.setEnergy( 0.1 );

    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    particle.setWeight( 10.0 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    particle.setWeight( 1.0 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    // bin 4
    particle.setEnergy( 1.0 );
    particle.setTime( 1.0 );
    particle.setWeight( 1.0 );

    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    // bin 5
    particle.setEnergy( 0.1 );

    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    particle.setWeight( 10.0 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    particle.setWeight( 1.0 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    // bin 6
    particle.setEnergy( 1.0 );
    particle.setWeight( 1.0 );

    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    // bin 7
    particle.setEnergy( 0.1 );

    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    particle.setWeight( 10.0 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    particle.setWeight( 1.0 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    // bin 8
    particle.setEnergy( 1.0 );
    particle.setTime( 2.0 );
    particle.incrementCollisionNumber();
    particle.setWeight( 1.0 );

    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    // bin 9
    particle.setEnergy( 0.1 );

    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    particle.setWeight( 10.0 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    particle.setWeight( 1.0 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    // bin 10
    particle.setEnergy( 1.0 );
    particle.setWeight( 1.0 );

    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    // bin 11
    particle.setEnergy( 0.1 );

    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    particle.setWeight( 10.0 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    particle.setWeight( 1.0 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    // bin 12
    particle.setEnergy( 1.0 );
    particle.setTime( 1.0 );
    particle.setWeight( 1.0 );

    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    // bin 13
    particle.setEnergy( 0.1 );

    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    particle.setWeight( 10.0 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    particle.setWeight( 1.0 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    // bin 14
    particle.setEnergy( 1.0 );
    particle.setWeight( 1.0 );

    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    // bin 15
    particle.setEnergy( 0.1 );

    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    particle.setWeight( 10.0 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    particle.setWeight( 1.0 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    // Commit the contributions
    estimator_1_base->commitHistoryContribution();
    estimator_2_base->commitHistoryContribution();
    estimator_3_base->commitHistoryContribution();
  }

  FRENSIE_CHECK( !estimator_1_base->hasUncommittedHistoryContribution() );
  FRENSIE_CHECK( !estimator_2_base->hasUncommittedHistoryContribution() );
  FRENSIE_CHECK( !estimator_3_base->hasUncommittedHistoryContribution() );

  MonteCarlo::Estimator::setNumberOfHistories( threads );
  MonteCarlo::Estimator::setElapsedTime( 1.0 );

  // Check the entity bin data moments
  Utility::ArrayView<const double> entity_bin_first_moments =
    estimator_1_base->getEntityBinDataFirstMoments( 0 );

  Utility::ArrayView<const double> entity_bin_second_moments =
    estimator_1_base->getEntityBinDataSecondMoments( 0 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 16, threads ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 16, threads ) );

  entity_bin_first_moments =
    estimator_1_base->getEntityBinDataFirstMoments( 1 );

  entity_bin_second_moments =
    estimator_1_base->getEntityBinDataSecondMoments( 1 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 16, threads ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 16, threads ) );

  entity_bin_first_moments =
    estimator_2_base->getEntityBinDataFirstMoments( 0 );

  entity_bin_second_moments =
    estimator_2_base->getEntityBinDataSecondMoments( 0 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 16, threads ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 16, threads ) );

  entity_bin_first_moments =
    estimator_2_base->getEntityBinDataFirstMoments( 1 );

  entity_bin_second_moments =
    estimator_2_base->getEntityBinDataSecondMoments( 1 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 16, threads ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 16, threads ) );

  entity_bin_first_moments =
    estimator_3_base->getEntityBinDataFirstMoments( 0 );

  entity_bin_second_moments =
    estimator_3_base->getEntityBinDataSecondMoments( 0 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 16, -1.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 16, 1.0*threads ) );

  entity_bin_first_moments =
    estimator_3_base->getEntityBinDataFirstMoments( 1 );

  entity_bin_second_moments =
    estimator_3_base->getEntityBinDataSecondMoments( 1 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 16, -1.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 16, 1.0*threads ) );

  // Check the total bin data moments
  Utility::ArrayView<const double> total_bin_first_moments =
    estimator_1_base->getTotalBinDataFirstMoments();

  Utility::ArrayView<const double> total_bin_second_moments =
    estimator_1_base->getTotalBinDataSecondMoments();

  FRENSIE_CHECK_EQUAL( total_bin_first_moments,
                       std::vector<double>( 16, 2.0*threads ) );
  FRENSIE_CHECK_EQUAL( total_bin_second_moments,
                       std::vector<double>( 16, 4.0*threads ) );

  total_bin_first_moments = estimator_2_base->getTotalBinDataFirstMoments();
  total_bin_second_moments = estimator_2_base->getTotalBinDataSecondMoments();

  FRENSIE_CHECK_EQUAL( total_bin_first_moments,
                       std::vector<double>( 16, 2.0*threads ) );
  FRENSIE_CHECK_EQUAL( total_bin_second_moments,
                       std::vector<double>( 16, 4.0*threads ) );

  total_bin_first_moments = estimator_3_base->getTotalBinDataFirstMoments();
  total_bin_second_moments = estimator_3_base->getTotalBinDataSecondMoments();

  FRENSIE_CHECK_EQUAL( total_bin_first_moments,
                       std::vector<double>( 16, -2.0*threads ) );
  FRENSIE_CHECK_EQUAL( total_bin_second_moments,
                       std::vector<double>( 16, 4.0*threads ) );

  // Check the entity total data moments
  Utility::ArrayView<const double> entity_total_first_moments =
    estimator_1_base->getEntityTotalDataFirstMoments( 0 );

  Utility::ArrayView<const double> entity_total_second_moments =
    estimator_1_base->getEntityTotalDataSecondMoments( 0 );

  Utility::ArrayView<const double> entity_total_third_moments =
    estimator_1_base->getEntityTotalDataThirdMoments( 0 );

  Utility::ArrayView<const double> entity_total_fourth_moments =
    estimator_1_base->getEntityTotalDataFourthMoments( 0 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, 16.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 256.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, 4096.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 65536.0*threads ) );

  entity_total_first_moments =
    estimator_1_base->getEntityTotalDataFirstMoments( 1 );

  entity_total_second_moments =
    estimator_1_base->getEntityTotalDataSecondMoments( 1 );

  entity_total_third_moments =
    estimator_1_base->getEntityTotalDataThirdMoments( 1 );

  entity_total_fourth_moments =
    estimator_1_base->getEntityTotalDataFourthMoments( 1 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, 16.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 256.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, 4096.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 65536.0*threads ) );

  entity_total_first_moments =
    estimator_2_base->getEntityTotalDataFirstMoments( 0 );

  entity_total_second_moments =
    estimator_2_base->getEntityTotalDataSecondMoments( 0 );

  entity_total_third_moments =
    estimator_2_base->getEntityTotalDataThirdMoments( 0 );

  entity_total_fourth_moments =
    estimator_2_base->getEntityTotalDataFourthMoments( 0 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, 16.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 256.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, 4096.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 65536.0*threads ) );

  entity_total_first_moments =
    estimator_2_base->getEntityTotalDataFirstMoments( 1 );

  entity_total_second_moments =
    estimator_2_base->getEntityTotalDataSecondMoments( 1 );

  entity_total_third_moments =
    estimator_2_base->getEntityTotalDataThirdMoments( 1 );

  entity_total_fourth_moments =
    estimator_2_base->getEntityTotalDataFourthMoments( 1 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, 16.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 256.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, 4096.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 65536.0*threads ) );

  entity_total_first_moments =
    estimator_3_base->getEntityTotalDataFirstMoments( 0 );

  entity_total_second_moments =
    estimator_3_base->getEntityTotalDataSecondMoments( 0 );

  entity_total_third_moments =
    estimator_3_base->getEntityTotalDataThirdMoments( 0 );

  entity_total_fourth_moments =
    estimator_3_base->getEntityTotalDataFourthMoments( 0 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, -16.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 256.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, -4096.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 65536.0*threads ) );

  entity_total_first_moments =
    estimator_3_base->getEntityTotalDataFirstMoments( 1 );

  entity_total_second_moments =
    estimator_3_base->getEntityTotalDataSecondMoments( 1 );

  entity_total_third_moments =
    estimator_3_base->getEntityTotalDataThirdMoments( 1 );

  entity_total_fourth_moments =
    estimator_3_base->getEntityTotalDataFourthMoments( 1 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, -16.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 256.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, -4096.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 65536.0*threads ) );

  // Check the total data moments
  Utility::ArrayView<const double> total_first_moments =
    estimator_1_base->getTotalDataFirstMoments();

  Utility::ArrayView<const double> total_second_moments =
    estimator_1_base->getTotalDataSecondMoments();

  Utility::ArrayView<const double> total_third_moments =
    estimator_1_base->getTotalDataThirdMoments();

  Utility::ArrayView<const double> total_fourth_moments =
    estimator_1_base->getTotalDataFourthMoments();

  FRENSIE_CHECK_EQUAL( total_first_moments,
                       std::vector<double>( 1, 32.0*threads ) );
  FRENSIE_CHECK_EQUAL( total_second_moments,
                       std::vector<double>( 1, 1024.0*threads ) );
  FRENSIE_CHECK_EQUAL( total_third_moments,
                       std::vector<double>( 1, 32768.0*threads ) );
  FRENSIE_CHECK_EQUAL( total_fourth_moments,
                       std::vector<double>( 1, 1048576.0*threads ) );

  total_first_moments = estimator_2_base->getTotalDataFirstMoments();
  total_second_moments = estimator_2_base->getTotalDataSecondMoments();
  total_third_moments = estimator_2_base->getTotalDataThirdMoments();
  total_fourth_moments = estimator_2_base->getTotalDataFourthMoments();

  FRENSIE_CHECK_EQUAL( total_first_moments,
                       std::vector<double>( 1, 32.0*threads ) );
  FRENSIE_CHECK_EQUAL( total_second_moments,
                       std::vector<double>( 1, 1024.0*threads ) );
  FRENSIE_CHECK_EQUAL( total_third_moments,
                       std::vector<double>( 1, 32768.0*threads ) );
  FRENSIE_CHECK_EQUAL( total_fourth_moments,
                       std::vector<double>( 1, 1048576.0*threads ) );

  total_first_moments = estimator_3_base->getTotalDataFirstMoments();
  total_second_moments = estimator_3_base->getTotalDataSecondMoments();
  total_third_moments = estimator_3_base->getTotalDataThirdMoments();
  total_fourth_moments = estimator_3_base->getTotalDataFourthMoments();

  FRENSIE_CHECK_EQUAL( total_first_moments,
                       std::vector<double>( 1, -32.0*threads ) );
  FRENSIE_CHECK_EQUAL( total_second_moments,
                       std::vector<double>( 1, 1024.0*threads ) );
  FRENSIE_CHECK_EQUAL( total_third_moments,
                       std::vector<double>( 1, -32768.0*threads ) );
  FRENSIE_CHECK_EQUAL( total_fourth_moments,
                       std::vector<double>( 1, 1048576.0*threads ) );
}

//---------------------------------------------------------------------------//
// Check that an estimator can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( SurfaceCurrentEstimator,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_surface_current_estimator" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::shared_ptr<MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightMultiplier> >
      estimator_1;
    std::shared_ptr<MonteCarlo::Estimator> estimator_1_base;

    std::shared_ptr<MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightAndEnergyMultiplier> >
      estimator_2;
    std::shared_ptr<MonteCarlo::Estimator> estimator_2_base;

    std::shared_ptr<MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightAndChargeMultiplier> >
      estimator_3;
    std::shared_ptr<MonteCarlo::Estimator> estimator_3_base;

    {
      // Set the surface ids
      std::vector<MonteCarlo::StandardSurfaceEstimator::SurfaceIdType>
        surface_ids( 2 );
      surface_ids[0] = 0;
      surface_ids[1] = 1;

      estimator_1.reset( new MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightMultiplier>(
                                                             0u,
                                                             1.0,
                                                             surface_ids ) );
      estimator_1_base = estimator_1;

      estimator_2.reset( new MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightAndEnergyMultiplier>(
                                                             1u,
                                                             10.0,
                                                             surface_ids ) );
      estimator_2_base = estimator_2;

      estimator_3.reset(
      new MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightAndChargeMultiplier>(
                                                              2u,
                                                              1.0,
                                                              surface_ids ) );
      estimator_3_base = estimator_3;

      // Set the energy bins
      std::vector<double> energy_bin_boundaries( 3 );
      energy_bin_boundaries[0] = 0.0;
      energy_bin_boundaries[1] = 0.1;
      energy_bin_boundaries[2] = 1.0;

      estimator_1_base->setDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION>(
                                                       energy_bin_boundaries );
      estimator_2_base->setDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION>(
                                                       energy_bin_boundaries );
      estimator_3_base->setDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION>(
                                                       energy_bin_boundaries );

      // Set the cosine bins
      std::vector<double> cosine_bins( 3 );
      cosine_bins[0] = -1.0;
      cosine_bins[1] = 0.0;
      cosine_bins[2] = 1.0;

      estimator_1_base->setDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION>(
                                                                 cosine_bins );
      estimator_2_base->setDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION>(
                                                                 cosine_bins );
      estimator_3_base->setDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION>(
                                                                 cosine_bins );

      // Set the time bins
      std::vector<double> time_bins( 3 );
      time_bins[0] = 0.0;
      time_bins[1] = 1.0;
      time_bins[2] = 2.0;

      estimator_1_base->setDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION>(time_bins );
      estimator_2_base->setDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION>(time_bins );
      estimator_3_base->setDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION>(time_bins );

      // Set the collision number bins
      std::vector<unsigned> collision_number_bins( 2 );
      collision_number_bins[0] = 0u;
      collision_number_bins[1] = 1u;

      estimator_1_base->setDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION>(
                                                       collision_number_bins );
      estimator_2_base->setDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION>(
                                                       collision_number_bins );
      estimator_3_base->setDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION>(
                                                       collision_number_bins );

      // Set the particle types
      std::vector<MonteCarlo::ParticleType> particle_types( 1 );
      particle_types[0] = MonteCarlo::ELECTRON;

      estimator_1_base->setParticleTypes( particle_types );
      estimator_2_base->setParticleTypes( particle_types );
      estimator_3_base->setParticleTypes( particle_types );
    }

    // bin 0
    MonteCarlo::ElectronState particle( 0u );
    particle.setEnergy( 1.0 );
    particle.setTime( 2.0 );

    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    FRENSIE_CHECK( estimator_1_base->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_2_base->hasUncommittedHistoryContribution() );
    FRENSIE_CHECK( estimator_3_base->hasUncommittedHistoryContribution() );

    // bin 1
    particle.setEnergy( 0.1 );

    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    particle.setWeight( 10.0 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    particle.setWeight( 1.0 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    // bin 2
    particle.setEnergy( 1.0 );
    particle.setWeight( 1.0 );

    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    // bin 3
    particle.setEnergy( 0.1 );

    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    particle.setWeight( 10.0 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    particle.setWeight( 1.0 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    // bin 4
    particle.setEnergy( 1.0 );
    particle.setTime( 1.0 );
    particle.setWeight( 1.0 );

    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    // bin 5
    particle.setEnergy( 0.1 );

    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    particle.setWeight( 10.0 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    particle.setWeight( 1.0 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    // bin 6
    particle.setEnergy( 1.0 );
    particle.setWeight( 1.0 );

    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    // bin 7
    particle.setEnergy( 0.1 );

    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    particle.setWeight( 10.0 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    particle.setWeight( 1.0 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    // bin 8
    particle.setEnergy( 1.0 );
    particle.setTime( 2.0 );
    particle.incrementCollisionNumber();
    particle.setWeight( 1.0 );

    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    // bin 9
    particle.setEnergy( 0.1 );

    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    particle.setWeight( 10.0 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    particle.setWeight( 1.0 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    // bin 10
    particle.setEnergy( 1.0 );
    particle.setWeight( 1.0 );

    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    // bin 11
    particle.setEnergy( 0.1 );

    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    particle.setWeight( 10.0 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    particle.setWeight( 1.0 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    // bin 12
    particle.setEnergy( 1.0 );
    particle.setTime( 1.0 );
    particle.setWeight( 1.0 );

    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    // bin 13
    particle.setEnergy( 0.1 );

    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    particle.setWeight( 10.0 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    particle.setWeight( 1.0 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

    // bin 14
    particle.setEnergy( 1.0 );
    particle.setWeight( 1.0 );

    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    // bin 15
    particle.setEnergy( 0.1 );

    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    particle.setWeight( 10.0 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    particle.setWeight( 1.0 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
    estimator_3->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

    // Commit the contributions
    estimator_1_base->commitHistoryContribution();
    estimator_2_base->commitHistoryContribution();
    estimator_3_base->commitHistoryContribution();

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( estimator_1 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( estimator_1_base ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( estimator_2 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( estimator_2_base ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( estimator_3 ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( estimator_3_base ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::shared_ptr<MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightMultiplier> >
    estimator_1;
  std::shared_ptr<MonteCarlo::Estimator> estimator_1_base;

  std::shared_ptr<MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightAndEnergyMultiplier> >
    estimator_2;
  std::shared_ptr<MonteCarlo::Estimator> estimator_2_base;

  std::shared_ptr<MonteCarlo::SurfaceCurrentEstimator<MonteCarlo::WeightAndChargeMultiplier> >
    estimator_3;
  std::shared_ptr<MonteCarlo::Estimator> estimator_3_base;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( estimator_1 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( estimator_1_base ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( estimator_2 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( estimator_2_base ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( estimator_3 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( estimator_3_base ) );

  iarchive.reset();

  {
    FRENSIE_CHECK( estimator_1.get() == estimator_1_base.get() );

    FRENSIE_CHECK_EQUAL( estimator_1_base->getId(), 0 );
    FRENSIE_CHECK_EQUAL( estimator_1_base->getMultiplier(), 1.0 );
    FRENSIE_CHECK_EQUAL( estimator_1_base->getNumberOfBins(), 16 );
    FRENSIE_CHECK_EQUAL( estimator_1_base->getNumberOfBins( MonteCarlo::OBSERVER_COSINE_DIMENSION ), 2 );
    FRENSIE_CHECK_EQUAL( estimator_1_base->getNumberOfBins( MonteCarlo::OBSERVER_ENERGY_DIMENSION ), 2 );
    FRENSIE_CHECK_EQUAL( estimator_1_base->getNumberOfBins( MonteCarlo::OBSERVER_TIME_DIMENSION ), 2 );
    FRENSIE_CHECK_EQUAL( estimator_1_base->getNumberOfBins( MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION ), 2 );
    FRENSIE_CHECK_EQUAL( estimator_1_base->getNumberOfResponseFunctions(), 1 );
    FRENSIE_CHECK_EQUAL( estimator_1_base->getParticleTypes().size(), 1 );
    FRENSIE_CHECK( estimator_1_base->getParticleTypes().find( MonteCarlo::ELECTRON ) != estimator_1_base->getParticleTypes().end() );

    std::set<uint64_t> entity_ids;

    estimator_1->getEntityIds( entity_ids );

    FRENSIE_CHECK_EQUAL( entity_ids.size(), 2 );
    FRENSIE_CHECK( entity_ids.find( 0 ) != entity_ids.end() );
    FRENSIE_CHECK( entity_ids.find( 1 ) != entity_ids.end() );

    FRENSIE_CHECK_EQUAL( estimator_1_base->getEntityNormConstant( 0 ), 1.0 );
    FRENSIE_CHECK_EQUAL( estimator_1_base->getEntityNormConstant( 1 ), 1.0 );
    FRENSIE_CHECK_EQUAL( estimator_1_base->getTotalNormConstant(), 1.0 );

    // Check the entity bin data moments
    Utility::ArrayView<const double> entity_bin_first_moments =
      estimator_1_base->getEntityBinDataFirstMoments( 0 );

    Utility::ArrayView<const double> entity_bin_second_moments =
      estimator_1_base->getEntityBinDataSecondMoments( 0 );

    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 16, 1.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 16, 1.0 ) );

    entity_bin_first_moments =
      estimator_1_base->getEntityBinDataFirstMoments( 1 );

    entity_bin_second_moments =
      estimator_1_base->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 16, 1.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 16, 1.0 ) );

    // Check the total bin data moments
    Utility::ArrayView<const double> total_bin_first_moments =
      estimator_1_base->getTotalBinDataFirstMoments();

    Utility::ArrayView<const double> total_bin_second_moments =
      estimator_1_base->getTotalBinDataSecondMoments();

    FRENSIE_CHECK_EQUAL( total_bin_first_moments,
                         std::vector<double>( 16, 2.0 ) );
    FRENSIE_CHECK_EQUAL( total_bin_second_moments,
                         std::vector<double>( 16, 4.0 ) );

    // Check the entity total data moments
    Utility::ArrayView<const double> entity_total_first_moments =
      estimator_1_base->getEntityTotalDataFirstMoments( 0 );

    Utility::ArrayView<const double> entity_total_second_moments =
      estimator_1_base->getEntityTotalDataSecondMoments( 0 );

    Utility::ArrayView<const double> entity_total_third_moments =
      estimator_1_base->getEntityTotalDataThirdMoments( 0 );

    Utility::ArrayView<const double> entity_total_fourth_moments =
      estimator_1_base->getEntityTotalDataFourthMoments( 0 );

    FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                         std::vector<double>( 1, 16.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                         std::vector<double>( 1, 256.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                         std::vector<double>( 1, 4096.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                         std::vector<double>( 1, 65536.0 ) );

    entity_total_first_moments =
      estimator_1_base->getEntityTotalDataFirstMoments( 1 );

    entity_total_second_moments =
      estimator_1_base->getEntityTotalDataSecondMoments( 1 );

    entity_total_third_moments =
      estimator_1_base->getEntityTotalDataThirdMoments( 1 );

    entity_total_fourth_moments =
      estimator_1_base->getEntityTotalDataFourthMoments( 1 );

    FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                         std::vector<double>( 1, 16.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                         std::vector<double>( 1, 256.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                         std::vector<double>( 1, 4096.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                         std::vector<double>( 1, 65536.0 ) );

    // Check the total data moments
    Utility::ArrayView<const double> total_first_moments =
      estimator_1_base->getTotalDataFirstMoments();

    Utility::ArrayView<const double> total_second_moments =
      estimator_1_base->getTotalDataSecondMoments();

    Utility::ArrayView<const double> total_third_moments =
      estimator_1_base->getTotalDataThirdMoments();

    Utility::ArrayView<const double> total_fourth_moments =
      estimator_1_base->getTotalDataFourthMoments();

    FRENSIE_CHECK_EQUAL( total_first_moments,
                         std::vector<double>( 1, 32.0 ) );
    FRENSIE_CHECK_EQUAL( total_second_moments,
                         std::vector<double>( 1, 1024.0 ) );
    FRENSIE_CHECK_EQUAL( total_third_moments,
                         std::vector<double>( 1, 32768.0 ) );
    FRENSIE_CHECK_EQUAL( total_fourth_moments,
                         std::vector<double>( 1, 1048576.0 ) );
  }

  {
    FRENSIE_CHECK( estimator_2.get() == estimator_2_base.get() );

    FRENSIE_CHECK_EQUAL( estimator_2_base->getId(), 1 );
    FRENSIE_CHECK_EQUAL( estimator_2_base->getMultiplier(), 10.0 );
    FRENSIE_CHECK_EQUAL( estimator_2_base->getNumberOfBins(), 16 );
    FRENSIE_CHECK_EQUAL( estimator_2_base->getNumberOfBins( MonteCarlo::OBSERVER_COSINE_DIMENSION ), 2 );
    FRENSIE_CHECK_EQUAL( estimator_2_base->getNumberOfBins( MonteCarlo::OBSERVER_ENERGY_DIMENSION ), 2 );
    FRENSIE_CHECK_EQUAL( estimator_2_base->getNumberOfBins( MonteCarlo::OBSERVER_TIME_DIMENSION ), 2 );
    FRENSIE_CHECK_EQUAL( estimator_2_base->getNumberOfBins( MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION ), 2 );
    FRENSIE_CHECK_EQUAL( estimator_2_base->getNumberOfResponseFunctions(), 1 );
    FRENSIE_CHECK_EQUAL( estimator_2_base->getParticleTypes().size(), 1 );
    FRENSIE_CHECK( estimator_2_base->getParticleTypes().find( MonteCarlo::ELECTRON ) != estimator_2_base->getParticleTypes().end() );

    std::set<uint64_t> entity_ids;

    estimator_2->getEntityIds( entity_ids );

    FRENSIE_CHECK_EQUAL( entity_ids.size(), 2 );
    FRENSIE_CHECK( entity_ids.find( 0 ) != entity_ids.end() );
    FRENSIE_CHECK( entity_ids.find( 1 ) != entity_ids.end() );

    FRENSIE_CHECK_EQUAL( estimator_2_base->getEntityNormConstant( 0 ), 1.0 );
    FRENSIE_CHECK_EQUAL( estimator_2_base->getEntityNormConstant( 1 ), 1.0 );
    FRENSIE_CHECK_EQUAL( estimator_2_base->getTotalNormConstant(), 1.0 );

    // Check the entity bin data moments
    Utility::ArrayView<const double> entity_bin_first_moments =
      estimator_2_base->getEntityBinDataFirstMoments( 0 );

    Utility::ArrayView<const double> entity_bin_second_moments =
      estimator_2_base->getEntityBinDataSecondMoments( 0 );

    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 16, 1.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 16, 1.0 ) );

    entity_bin_first_moments =
      estimator_2_base->getEntityBinDataFirstMoments( 1 );

    entity_bin_second_moments =
      estimator_2_base->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 16, 1.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 16, 1.0 ) );

    // Check the total bin data moments
    Utility::ArrayView<const double> total_bin_first_moments =
      estimator_2_base->getTotalBinDataFirstMoments();

    Utility::ArrayView<const double> total_bin_second_moments =
      estimator_2_base->getTotalBinDataSecondMoments();

    FRENSIE_CHECK_EQUAL( total_bin_first_moments,
                         std::vector<double>( 16, 2.0 ) );
    FRENSIE_CHECK_EQUAL( total_bin_second_moments,
                         std::vector<double>( 16, 4.0 ) );

    // Check the entity total data moments
    Utility::ArrayView<const double> entity_total_first_moments =
      estimator_2_base->getEntityTotalDataFirstMoments( 0 );

    Utility::ArrayView<const double> entity_total_second_moments =
      estimator_2_base->getEntityTotalDataSecondMoments( 0 );

    Utility::ArrayView<const double> entity_total_third_moments =
      estimator_2_base->getEntityTotalDataThirdMoments( 0 );

    Utility::ArrayView<const double> entity_total_fourth_moments =
      estimator_2_base->getEntityTotalDataFourthMoments( 0 );

    FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                         std::vector<double>( 1, 16.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                         std::vector<double>( 1, 256.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                         std::vector<double>( 1, 4096.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                         std::vector<double>( 1, 65536.0 ) );

    entity_total_first_moments =
      estimator_2_base->getEntityTotalDataFirstMoments( 1 );

    entity_total_second_moments =
      estimator_2_base->getEntityTotalDataSecondMoments( 1 );

    entity_total_third_moments =
      estimator_2_base->getEntityTotalDataThirdMoments( 1 );

    entity_total_fourth_moments =
      estimator_2_base->getEntityTotalDataFourthMoments( 1 );

    FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                         std::vector<double>( 1, 16.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                         std::vector<double>( 1, 256.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                         std::vector<double>( 1, 4096.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                         std::vector<double>( 1, 65536.0 ) );

    // Check the total data moments
    Utility::ArrayView<const double> total_first_moments =
      estimator_2_base->getTotalDataFirstMoments();

    Utility::ArrayView<const double> total_second_moments =
      estimator_2_base->getTotalDataSecondMoments();

    Utility::ArrayView<const double> total_third_moments =
      estimator_2_base->getTotalDataThirdMoments();

    Utility::ArrayView<const double> total_fourth_moments =
      estimator_2_base->getTotalDataFourthMoments();

    FRENSIE_CHECK_EQUAL( total_first_moments,
                         std::vector<double>( 1, 32.0 ) );
    FRENSIE_CHECK_EQUAL( total_second_moments,
                         std::vector<double>( 1, 1024.0 ) );
    FRENSIE_CHECK_EQUAL( total_third_moments,
                         std::vector<double>( 1, 32768.0 ) );
    FRENSIE_CHECK_EQUAL( total_fourth_moments,
                         std::vector<double>( 1, 1048576.0 ) );
  }

  {
    FRENSIE_CHECK( estimator_3.get() == estimator_3_base.get() );

    FRENSIE_CHECK_EQUAL( estimator_3_base->getId(), 2 );
    FRENSIE_CHECK_EQUAL( estimator_3_base->getMultiplier(), 1.0 );
    FRENSIE_CHECK_EQUAL( estimator_3_base->getNumberOfBins(), 16 );
    FRENSIE_CHECK_EQUAL( estimator_3_base->getNumberOfBins( MonteCarlo::OBSERVER_COSINE_DIMENSION ), 2 );
    FRENSIE_CHECK_EQUAL( estimator_3_base->getNumberOfBins( MonteCarlo::OBSERVER_ENERGY_DIMENSION ), 2 );
    FRENSIE_CHECK_EQUAL( estimator_3_base->getNumberOfBins( MonteCarlo::OBSERVER_TIME_DIMENSION ), 2 );
    FRENSIE_CHECK_EQUAL( estimator_3_base->getNumberOfBins( MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION ), 2 );
    FRENSIE_CHECK_EQUAL( estimator_3_base->getNumberOfResponseFunctions(), 1 );
    FRENSIE_CHECK_EQUAL( estimator_3_base->getParticleTypes().size(), 1 );
    FRENSIE_CHECK( estimator_3_base->getParticleTypes().find( MonteCarlo::ELECTRON ) != estimator_3_base->getParticleTypes().end() );

    std::set<uint64_t> entity_ids;

    estimator_3->getEntityIds( entity_ids );

    FRENSIE_CHECK_EQUAL( entity_ids.size(), 2 );
    FRENSIE_CHECK( entity_ids.find( 0 ) != entity_ids.end() );
    FRENSIE_CHECK( entity_ids.find( 1 ) != entity_ids.end() );

    FRENSIE_CHECK_EQUAL( estimator_3_base->getEntityNormConstant( 0 ), 1.0 );
    FRENSIE_CHECK_EQUAL( estimator_3_base->getEntityNormConstant( 1 ), 1.0 );
    FRENSIE_CHECK_EQUAL( estimator_3_base->getTotalNormConstant(), 1.0 );

    // Check the entity bin data moments
    Utility::ArrayView<const double> entity_bin_first_moments =
      estimator_3_base->getEntityBinDataFirstMoments( 0 );

    Utility::ArrayView<const double> entity_bin_second_moments =
      estimator_3_base->getEntityBinDataSecondMoments( 0 );

    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 16, -1.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 16, 1.0 ) );

    entity_bin_first_moments =
      estimator_3_base->getEntityBinDataFirstMoments( 1 );

    entity_bin_second_moments =
      estimator_3_base->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 16, -1.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 16, 1.0 ) );

    // Check the total bin data moments
    Utility::ArrayView<const double> total_bin_first_moments =
      estimator_3_base->getTotalBinDataFirstMoments();

    Utility::ArrayView<const double> total_bin_second_moments =
      estimator_3_base->getTotalBinDataSecondMoments();

    FRENSIE_CHECK_EQUAL( total_bin_first_moments,
                         std::vector<double>( 16, -2.0 ) );
    FRENSIE_CHECK_EQUAL( total_bin_second_moments,
                         std::vector<double>( 16, 4.0 ) );

    // Check the entity total data moments
    Utility::ArrayView<const double> entity_total_first_moments =
      estimator_3_base->getEntityTotalDataFirstMoments( 0 );

    Utility::ArrayView<const double> entity_total_second_moments =
      estimator_3_base->getEntityTotalDataSecondMoments( 0 );

    Utility::ArrayView<const double> entity_total_third_moments =
      estimator_3_base->getEntityTotalDataThirdMoments( 0 );

    Utility::ArrayView<const double> entity_total_fourth_moments =
      estimator_3_base->getEntityTotalDataFourthMoments( 0 );

    FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                         std::vector<double>( 1, -16.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                         std::vector<double>( 1, 256.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                         std::vector<double>( 1, -4096.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                         std::vector<double>( 1, 65536.0 ) );

    entity_total_first_moments =
      estimator_3_base->getEntityTotalDataFirstMoments( 1 );

    entity_total_second_moments =
      estimator_3_base->getEntityTotalDataSecondMoments( 1 );

    entity_total_third_moments =
      estimator_3_base->getEntityTotalDataThirdMoments( 1 );

    entity_total_fourth_moments =
      estimator_3_base->getEntityTotalDataFourthMoments( 1 );

    FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                         std::vector<double>( 1, -16.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                         std::vector<double>( 1, 256.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                         std::vector<double>( 1, -4096.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                         std::vector<double>( 1, 65536.0 ) );

    // Check the total data moments
    Utility::ArrayView<const double> total_first_moments =
      estimator_3_base->getTotalDataFirstMoments();

    Utility::ArrayView<const double> total_second_moments =
      estimator_3_base->getTotalDataSecondMoments();

    Utility::ArrayView<const double> total_third_moments =
      estimator_3_base->getTotalDataThirdMoments();

    Utility::ArrayView<const double> total_fourth_moments =
      estimator_3_base->getTotalDataFourthMoments();

    FRENSIE_CHECK_EQUAL( total_first_moments,
                         std::vector<double>( 1, -32.0 ) );
    FRENSIE_CHECK_EQUAL( total_second_moments,
                         std::vector<double>( 1, 1024.0 ) );
    FRENSIE_CHECK_EQUAL( total_third_moments,
                         std::vector<double>( 1, -32768.0 ) );
    FRENSIE_CHECK_EQUAL( total_fourth_moments,
                         std::vector<double>( 1, 1048576.0 ) );
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
// end tstSurfaceCurrentEstimator.cpp
//---------------------------------------------------------------------------//
