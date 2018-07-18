//---------------------------------------------------------------------------//
//!
//! \file   tstSurfaceFluxEstimator.cpp
//! \author Alex Robinson
//! \brief  Surface flux estimator unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_SurfaceFluxEstimator.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Utility_OpenMPProperties.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the number of bins can be returned
FRENSIE_UNIT_TEST_TEMPLATE( SurfaceFluxEstimator,
                            getNumberOfBins,
                            MonteCarlo::WeightMultiplier,
                            MonteCarlo::WeightAndEnergyMultiplier )
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

  estimator.reset(
	   new MonteCarlo::SurfaceFluxEstimator<ContributionMultiplierPolicy>(
							     0u,
							     10.0,
							     surface_ids,
							     surface_areas ) );

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
// Check that the surface ids associated with the estimator can be returned
FRENSIE_UNIT_TEST( SurfaceFluxEstimator, getEntityIds )
{
  std::shared_ptr<MonteCarlo::Estimator> estimator_1;
  std::shared_ptr<MonteCarlo::Estimator> estimator_2;

  {
    // Set the surface ids
    std::vector<MonteCarlo::StandardSurfaceEstimator::SurfaceIdType>
      surface_ids( 2 );
    surface_ids[0] = 0;
    surface_ids[1] = 1;

    // Set the surface areas
    std::vector<double> surface_areas( 2 );
    surface_areas[0] = 1.0;
    surface_areas[1] = 2.0;

    estimator_1.reset(
	    new MonteCarlo::SurfaceFluxEstimator<MonteCarlo::WeightMultiplier>(
							     0u,
							     10.0,
							     surface_ids,
							     surface_areas ) );
    estimator_2.reset(
     new MonteCarlo::SurfaceFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier>(
							     1u,
							     10.0,
							     surface_ids,
							     surface_areas ) );
  }
  
  std::set<uint64_t> entity_ids;
  
  estimator_1->getEntityIds( entity_ids );
  
  FRENSIE_CHECK_EQUAL( entity_ids.size(), 2 );
  FRENSIE_CHECK( entity_ids.find( 0 ) != entity_ids.end() );
  FRENSIE_CHECK( entity_ids.find( 1 ) != entity_ids.end() );

  entity_ids.clear();

  estimator_2->getEntityIds( entity_ids );

  FRENSIE_CHECK_EQUAL( entity_ids.size(), 2 );
  FRENSIE_CHECK( entity_ids.find( 0 ) != entity_ids.end() );
  FRENSIE_CHECK( entity_ids.find( 1 ) != entity_ids.end() );
}

//---------------------------------------------------------------------------//
// Check that a partial history contribution can be added to the estimator
FRENSIE_UNIT_TEST( SurfaceFluxEstimator,
		   updateFromParticleCrossingSurfaceEvent )
{
  std::shared_ptr<MonteCarlo::SurfaceFluxEstimator<MonteCarlo::WeightMultiplier> >
    estimator_1;
  std::shared_ptr<MonteCarlo::Estimator> estimator_1_base;

  std::shared_ptr<MonteCarlo::SurfaceFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier> >
    estimator_2;
  std::shared_ptr<MonteCarlo::Estimator> estimator_2_base;

  {
    // Set the surface ids
    std::vector<MonteCarlo::StandardSurfaceEstimator::SurfaceIdType>
      surface_ids( 2 );
    surface_ids[0] = 0;
    surface_ids[1] = 1;

    // Set the surface areas
    std::vector<double> surface_areas( 2 );
    surface_areas[0] = 1.0;
    surface_areas[1] = 2.0;

    estimator_1.reset(
	    new MonteCarlo::SurfaceFluxEstimator<MonteCarlo::WeightMultiplier>(
							     0u,
							     10.0,
							     surface_ids,
							     surface_areas ) );
    estimator_1_base = estimator_1;

    estimator_2.reset(
     new MonteCarlo::SurfaceFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier>(
							     1u,
							     10.0,
							     surface_ids,
							     surface_areas ) );
    estimator_2_base = estimator_2;

    // Set the energy bins
    std::vector<double> energy_bin_boundaries( 3 );
    energy_bin_boundaries[0] = 0.0;
    energy_bin_boundaries[1] = 0.1;
    energy_bin_boundaries[2] = 1.0;

    estimator_1_base->setDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION>(
						       energy_bin_boundaries );
    estimator_2_base->setDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION>(
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

    // Set the time bins
    std::vector<double> time_bins( 3 );
    time_bins[0] = 0.0;
    time_bins[1] = 1.0;
    time_bins[2] = 2.0;

    estimator_1_base->setDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION>(time_bins );
    estimator_2_base->setDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION>(time_bins );

    // Set the collision number bins
    std::vector<unsigned> collision_number_bins( 2 );
    collision_number_bins[0] = 0u;
    collision_number_bins[1] = 1u;

    estimator_1_base->setDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION>(
						       collision_number_bins );
    estimator_2_base->setDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION>(
						       collision_number_bins );

    // Set the particle types
    std::vector<MonteCarlo::ParticleType> particle_types( 1 );
    particle_types[0] = MonteCarlo::PHOTON;

    estimator_1_base->setParticleTypes( particle_types );
    estimator_2_base->setParticleTypes( particle_types );
  }

  FRENSIE_CHECK( !estimator_1_base->hasUncommittedHistoryContribution() );
  FRENSIE_CHECK( !estimator_2_base->hasUncommittedHistoryContribution() );

  // bin 0
  MonteCarlo::PhotonState particle( 0u );
  particle.setEnergy( 1.0 );
  particle.setTime( 2.0 );

  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );
  
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

  FRENSIE_CHECK( estimator_1_base->hasUncommittedHistoryContribution() );
  FRENSIE_CHECK( estimator_2_base->hasUncommittedHistoryContribution() );

  // bin 1
  particle.setEnergy( 0.1 );

  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

  particle.setWeight( 10.0 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

  // bin 2
  particle.setEnergy( 1.0 );
  particle.setWeight( 1.0 );

  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

  // bin 3
  particle.setEnergy( 0.1 );

  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

  particle.setWeight( 10.0 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

  // bin 4
  particle.setEnergy( 1.0 );
  particle.setTime( 1.0 );
  particle.setWeight( 1.0 );

  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );
  
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

  // bin 5
  particle.setEnergy( 0.1 );

  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

  particle.setWeight( 10.0 );
    estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

  // bin 6
  particle.setEnergy( 1.0 );
  particle.setWeight( 1.0 );

  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

  // bin 7
  particle.setEnergy( 0.1 );

  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

  particle.setWeight( 10.0 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

  // bin 8
  particle.setEnergy( 1.0 );
  particle.setTime( 2.0 );
  particle.incrementCollisionNumber();
  particle.setWeight( 1.0 );

  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

  // bin 9
  particle.setEnergy( 0.1 );

  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

  particle.setWeight( 10.0 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

  // bin 10
  particle.setEnergy( 1.0 );
  particle.setWeight( 1.0 );

  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

  // bin 11
  particle.setEnergy( 0.1 );

  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

  particle.setWeight( 10.0 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

  // bin 12
  particle.setEnergy( 1.0 );
  particle.setTime( 1.0 );
  particle.setWeight( 1.0 );

  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

  // bin 13
  particle.setEnergy( 0.1 );

  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );  
  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

  particle.setWeight( 10.0 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

  // bin 14
  particle.setEnergy( 1.0 );
  particle.setWeight( 1.0 );

  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

  // bin 15
  particle.setEnergy( 0.1 );

  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
  estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

  particle.setWeight( 10.0 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
  estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

  // Commit the contributions
  estimator_1_base->commitHistoryContribution();
  estimator_2_base->commitHistoryContribution();

  FRENSIE_CHECK( !estimator_1_base->hasUncommittedHistoryContribution() );
  FRENSIE_CHECK( !estimator_2_base->hasUncommittedHistoryContribution() );

  MonteCarlo::Estimator::setNumberOfHistories( 1.0 );
  MonteCarlo::Estimator::setElapsedTime( 1.0 );

  // Check the entity bin data moments
  Utility::ArrayView<const double> entity_bin_first_moments =
    estimator_1_base->getEntityBinDataFirstMoments( 0 );

  Utility::ArrayView<const double> entity_bin_second_moments =
    estimator_1_base->getEntityBinDataSecondMoments( 0 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 16, 2.0 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 16, 4.0 ) );

  entity_bin_first_moments = estimator_1_base->getEntityBinDataFirstMoments( 1 );

  entity_bin_second_moments = estimator_1_base->getEntityBinDataSecondMoments( 1 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 16, 2.0 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 16, 4.0 ) );

  entity_bin_first_moments = estimator_2_base->getEntityBinDataFirstMoments( 0 );
  entity_bin_second_moments = estimator_2_base->getEntityBinDataSecondMoments( 0 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 16, 2.0 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 16, 4.0 ) );

  entity_bin_first_moments = estimator_2_base->getEntityBinDataFirstMoments( 1 );
  entity_bin_second_moments = estimator_2_base->getEntityBinDataSecondMoments( 1 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 16, 2.0 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 16, 4.0 ) );

  // Check the total bin data moments
  Utility::ArrayView<const double> total_bin_first_moments =
    estimator_1_base->getTotalBinDataFirstMoments();

  Utility::ArrayView<const double> total_bin_second_moments =
    estimator_1_base->getTotalBinDataSecondMoments();

  FRENSIE_CHECK_EQUAL( total_bin_first_moments,
                       std::vector<double>( 16, 4.0 ) );
  FRENSIE_CHECK_EQUAL( total_bin_second_moments,
                       std::vector<double>( 16, 16.0 ) );

  total_bin_first_moments = estimator_2_base->getTotalBinDataFirstMoments();
  total_bin_second_moments = estimator_2_base->getTotalBinDataSecondMoments();

  FRENSIE_CHECK_EQUAL( total_bin_first_moments,
                       std::vector<double>( 16, 4.0 ) );
  FRENSIE_CHECK_EQUAL( total_bin_second_moments,
                       std::vector<double>( 16, 16.0 ) );

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
                       std::vector<double>( 1, 32.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 1024.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, 32768.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 1048576.0 ) );

  entity_total_first_moments =
    estimator_1_base->getEntityTotalDataFirstMoments( 1 );

  entity_total_second_moments =
    estimator_1_base->getEntityTotalDataSecondMoments( 1 );

  entity_total_third_moments =
    estimator_1_base->getEntityTotalDataThirdMoments( 1 );

  entity_total_fourth_moments =
    estimator_1_base->getEntityTotalDataFourthMoments( 1 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, 32.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 1024.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, 32768.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 1048576.0 ) );
  
  entity_total_first_moments =
    estimator_2_base->getEntityTotalDataFirstMoments( 0 );

  entity_total_second_moments =
    estimator_2_base->getEntityTotalDataSecondMoments( 0 );

  entity_total_third_moments =
    estimator_2_base->getEntityTotalDataThirdMoments( 0 );

  entity_total_fourth_moments =
    estimator_2_base->getEntityTotalDataFourthMoments( 0 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, 32.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 1024.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, 32768.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 1048576.0 ) );

  entity_total_first_moments =
    estimator_2_base->getEntityTotalDataFirstMoments( 1 );

  entity_total_second_moments =
    estimator_2_base->getEntityTotalDataSecondMoments( 1 );

  entity_total_third_moments =
    estimator_2_base->getEntityTotalDataThirdMoments( 1 );

  entity_total_fourth_moments =
    estimator_2_base->getEntityTotalDataFourthMoments( 1 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, 32.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 1024.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, 32768.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 1048576.0 ) );

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
                       std::vector<double>( 1, 64.0 ) );
  FRENSIE_CHECK_EQUAL( total_second_moments,
                       std::vector<double>( 1, 4096.0 ) );
  FRENSIE_CHECK_EQUAL( total_third_moments,
                       std::vector<double>( 1, 262144.0 ) );
  FRENSIE_CHECK_EQUAL( total_fourth_moments,
                       std::vector<double>( 1, 16777216.0 ) );

  total_first_moments = estimator_2_base->getTotalDataFirstMoments();
  total_second_moments = estimator_2_base->getTotalDataSecondMoments();
  total_third_moments = estimator_2_base->getTotalDataThirdMoments();
  total_fourth_moments = estimator_2_base->getTotalDataFourthMoments();

  FRENSIE_CHECK_EQUAL( total_first_moments,
                       std::vector<double>( 1, 64.0 ) );
  FRENSIE_CHECK_EQUAL( total_second_moments,
                       std::vector<double>( 1, 4096.0 ) );
  FRENSIE_CHECK_EQUAL( total_third_moments,
                       std::vector<double>( 1, 262144.0 ) );
  FRENSIE_CHECK_EQUAL( total_fourth_moments,
                       std::vector<double>( 1, 16777216.0 ) );
}

// //---------------------------------------------------------------------------//
// // Check that a partial history contribution can be added to the estimator -
// // special case (|mu| < mu_cut)
// TEUCHOS_UNIT_TEST( SurfaceFluxEstimator,
// 		   updateFromParticleCrossingSurfaceEvent_special_case )
// {
//   Teuchos::RCP<MonteCarlo::SurfaceFluxEstimator<MonteCarlo::WeightMultiplier> >
//     estimator_1;
//   Teuchos::RCP<MonteCarlo::Estimator> estimator_1_base;

//   Teuchos::RCP<MonteCarlo::SurfaceFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier> >
//     estimator_2;
//   Teuchos::RCP<MonteCarlo::Estimator> estimator_2_base;

//   {
//     // Set the surface ids
//     std::vector<MonteCarlo::StandardSurfaceEstimator::SurfaceIdType>
//     surface_ids( 1 );
//     surface_ids[0] = 0;

//     // Set the surface areas
//     std::vector<double> surface_areas( 1 );
//     surface_areas[0] = 1.0;

//     estimator_1.reset(
// 	    new MonteCarlo::SurfaceFluxEstimator<MonteCarlo::WeightMultiplier>(
// 							     0u,
// 							     10.0,
// 							     surface_ids,
// 							     surface_areas,
//                                                              0.1 ) );
//     estimator_1_base = estimator_1;

//     estimator_2.reset(
//      new MonteCarlo::SurfaceFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier>(
// 							     1u,
// 							     10.0,
// 							     surface_ids,
// 							     surface_areas,
//                                                              0.1 ) );
//     estimator_2_base = estimator_2;

//     // Set the cosine bins
//     std::vector<double> cosine_bins( 3 );
//     cosine_bins[0] = -1.0;
//     cosine_bins[1] = 0.0;
//     cosine_bins[2] = 1.0;

//     estimator_1_base->setDiscretization<MonteCarlo::COSINE_DIMENSION>(
// 								 cosine_bins );
//     estimator_2_base->setDiscretization<MonteCarlo::COSINE_DIMENSION>(
// 								 cosine_bins );

//     // Set the particle types
//     std::vector<MonteCarlo::ParticleType> particle_types( 1 );
//     particle_types[0] = MonteCarlo::PHOTON;

//     estimator_1_base->setParticleTypes( particle_types );
//     estimator_2_base->setParticleTypes( particle_types );
//   }

//   FRENSIE_CHECK( !estimator_1_base->hasUncommittedHistoryContribution() );
//   FRENSIE_CHECK( !estimator_2_base->hasUncommittedHistoryContribution() );

//   // bin 0
//   MonteCarlo::PhotonState particle( 0u );
//   particle.setEnergy( 0.1 );

//   estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.05 );
//   estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.01 );

//   FRENSIE_CHECK( estimator_1_base->hasUncommittedHistoryContribution() );
//   FRENSIE_CHECK( estimator_2_base->hasUncommittedHistoryContribution() );

//   // bin 1
//   estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.01 );
//   estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.05 );

//   FRENSIE_CHECK( estimator_1_base->hasUncommittedHistoryContribution() );
//   FRENSIE_CHECK( estimator_2_base->hasUncommittedHistoryContribution() );

//   // Commit the contributions
//   estimator_1_base->commitHistoryContribution();
//   estimator_2_base->commitHistoryContribution();

//   FRENSIE_CHECK( !estimator_1_base->hasUncommittedHistoryContribution() );
//   FRENSIE_CHECK( !estimator_2_base->hasUncommittedHistoryContribution() );

//   MonteCarlo::Estimator::setNumberOfHistories( 1.0 );
//   MonteCarlo::Estimator::setEndTime( 1.0 );

//   // Initialize the hfd5 file
//   std::shared_ptr<Utility::HDF5FileHandler>
//     hdf5_file( new Utility::HDF5FileHandler );
//   hdf5_file->openHDF5FileAndOverwrite( "test_surface_flux_estimator-special.h5" );

//   estimator_1_base->exportData( hdf5_file, true );
//   estimator_2_base->exportData( hdf5_file, true );

//   // Create an estimator hdf5 file handler
//   MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler( hdf5_file );

//   typedef MonteCarlo::StandardSurfaceEstimator::SurfaceIdType SurfaceId;

//   // Retrieve the raw bin data for each entity
//   std::vector<Utility::Pair<double,double> >
//     raw_bin_data( 2, Utility::Pair<double,double>( 20.0, 400.0 ) ),
//     raw_bin_data_copy;

//   hdf5_file_handler.getRawEstimatorEntityBinData<SurfaceId>(
//   						   0u, 0u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
//   					raw_bin_data_copy,
//   					1e-15 );

//   raw_bin_data[0]( 2.0, 4.0 );
//   raw_bin_data[1]( 2.0, 4.0 );

//   hdf5_file_handler.getRawEstimatorEntityBinData<SurfaceId>(
//   						   1u, 0u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
//   					raw_bin_data_copy,
//   					1e-15 );

//   // Retrieve the processed bin data for each entity
//   std::vector<Utility::Pair<double,double> >
//     processed_bin_data( 2, Utility::Pair<double,double>( 200.0, 0.0 ) ),
//     processed_bin_data_copy;

//   hdf5_file_handler.getProcessedEstimatorEntityBinData<SurfaceId>(
//   					     0u, 0u, processed_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_bin_data,
//   					processed_bin_data_copy,
//   					1e-15 );

//   processed_bin_data[0]( 20.0, 0.0 );
//   processed_bin_data[1]( 20.0, 0.0 );

//   hdf5_file_handler.getProcessedEstimatorEntityBinData<SurfaceId>(
//   					     1u, 0u, processed_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_bin_data,
//   					processed_bin_data_copy,
//   					1e-15 );

//   // Retrieve the raw total bin data
//   std::vector<Utility::Pair<double,double> >
//     raw_total_bin_data( 2.0, Utility::Pair<double,double>( 20.0, 400.0 ) ),
//     raw_total_bin_data_copy;

//   hdf5_file_handler.getRawEstimatorTotalBinData( 0u, raw_total_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_bin_data,
//   					raw_total_bin_data_copy,
//   					1e-15 );

//   raw_total_bin_data[0]( 2.0, 4.0 );
//   raw_total_bin_data[1]( 2.0, 4.0 );

//   hdf5_file_handler.getRawEstimatorTotalBinData( 1u, raw_total_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_bin_data,
//   					raw_total_bin_data_copy,
//   					1e-15 );

//   // Retrieve the processed total bin data
//   std::vector<Utility::Pair<double,double> >
//     processed_total_bin_data( 2, Utility::Pair<double,double>( 200.0, 0.0 )),
//     processed_total_bin_data_copy;

//   hdf5_file_handler.getProcessedEstimatorTotalBinData(
//   					   0u, processed_total_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_bin_data,
//   					processed_total_bin_data_copy,
//   					1e-15 );

//   processed_total_bin_data[0]( 20.0, 0.0 );
//   processed_total_bin_data[1]( 20.0, 0.0 );

//   hdf5_file_handler.getProcessedEstimatorTotalBinData(
//   					   1u, processed_total_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_bin_data,
//   					processed_total_bin_data_copy,
//   					1e-15 );

//   // Retrieve the raw estimator total data for each entity
//   Utility::Quad<double,double,double,double>
//     raw_moments( 40.0, 1600.0, 64000, 2560000 );

//   std::vector<Utility::Quad<double,double,double,double> >
//     raw_total_data( 1, raw_moments ),
//     raw_total_data_copy;

//   hdf5_file_handler.getRawEstimatorEntityTotalData<SurfaceId>(
//   						 0u, 0u, raw_total_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data,
//   					raw_total_data_copy,
//   					1e-15 );

//   raw_total_data[0]( 4.0, 16.0, 64.0, 256.0 );

//   hdf5_file_handler.getRawEstimatorEntityTotalData<SurfaceId>(
//   						 1u, 0u, raw_total_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data,
//   					raw_total_data_copy,
//   					1e-15 );

//   // Retrieve the processed estimator total data for each entity
//   Utility::Quad<double,double,double,double>
//     processed_moments( 400.0, 0.0, 0.0, 0.0 );

//   std::vector<Utility::Quad<double,double,double,double> >
//     processed_total_data( 1, processed_moments ),
//     processed_total_data_copy;

//   hdf5_file_handler.getProcessedEstimatorEntityTotalData<SurfaceId>(
//   					   0u, 0u, processed_total_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_data,
//   					processed_total_data_copy,
//   					1e-15 );

//   processed_total_data[0]( 40.0, 0.0, 0.0, 0.0 );

//   hdf5_file_handler.getProcessedEstimatorEntityTotalData<SurfaceId>(
//   					   1u, 0u, processed_total_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_data,
//   					processed_total_data_copy,
//   					1e-15 );

//   // Retrieve the raw total data
//   raw_total_data[0]( 40.0, 1600.0, 64000, 2560000 );

//   hdf5_file_handler.getRawEstimatorTotalData( 0u, raw_total_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data,
//   					raw_total_data_copy,
//   					1e-15 );

//   raw_total_data[0]( 4.0, 16.0, 64.0, 256.0 );

//   hdf5_file_handler.getRawEstimatorTotalData( 1u, raw_total_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data,
//   					raw_total_data_copy,
//   					1e-15 );

//   // Retrieve the processed total data
//   processed_total_data[0]( 400.0, 0.0, 0.0, 0.0 );

//   hdf5_file_handler.getProcessedEstimatorTotalData(
//   					       0u, processed_total_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_data,
//   					processed_total_data_copy,
//   					1e-15 );

//   processed_total_data[0]( 40.0, 0.0, 0.0, 0.0 );

//   hdf5_file_handler.getProcessedEstimatorTotalData(
//   					       1u, processed_total_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_data,
//   					processed_total_data_copy,
//   					1e-15 );
// }

// //---------------------------------------------------------------------------//
// // Check that a partial history contribution can be added to the estimator
// TEUCHOS_UNIT_TEST( SurfaceFluxEstimator,
// 		   updateFromParticleCrossingSurfaceEvent_thread_safe )
// {
//   Teuchos::RCP<MonteCarlo::SurfaceFluxEstimator<MonteCarlo::WeightMultiplier> >
//     estimator_1;
//   Teuchos::RCP<MonteCarlo::Estimator> estimator_1_base;

//   Teuchos::RCP<MonteCarlo::SurfaceFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier> >
//     estimator_2;
//   Teuchos::RCP<MonteCarlo::Estimator> estimator_2_base;

//   {
//     // Set the surface ids
//     std::vector<MonteCarlo::StandardSurfaceEstimator::SurfaceIdType>
//     surface_ids( 2 );
//     surface_ids[0] = 0;
//     surface_ids[1] = 1;

//     // Set the surface areas
//     std::vector<double> surface_areas( 2 );
//     surface_areas[0] = 1.0;
//     surface_areas[1] = 2.0;

//     estimator_1.reset(
// 	    new MonteCarlo::SurfaceFluxEstimator<MonteCarlo::WeightMultiplier>(
// 							     0u,
// 							     10.0,
// 							     surface_ids,
// 							     surface_areas ) );
//     estimator_1_base = estimator_1;

//     estimator_2.reset(
//      new MonteCarlo::SurfaceFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier>(
// 							     1u,
// 							     10.0,
// 							     surface_ids,
// 							     surface_areas ) );
//     estimator_2_base = estimator_2;

//     // Set the energy bins
//     std::vector<double> energy_bin_boundaries( 3 );
//     energy_bin_boundaries[0] = 0.0;
//     energy_bin_boundaries[1] = 0.1;
//     energy_bin_boundaries[2] = 1.0;

//     estimator_1_base->setDiscretization<MonteCarlo::ENERGY_DIMENSION>(
// 						       energy_bin_boundaries );
//     estimator_2_base->setDiscretization<MonteCarlo::ENERGY_DIMENSION>(
// 						       energy_bin_boundaries );

//     // Set the cosine bins
//     std::vector<double> cosine_bins( 3 );
//     cosine_bins[0] = -1.0;
//     cosine_bins[1] = 0.0;
//     cosine_bins[2] = 1.0;

//     estimator_1_base->setDiscretization<MonteCarlo::COSINE_DIMENSION>(
// 								 cosine_bins );
//     estimator_2_base->setDiscretization<MonteCarlo::COSINE_DIMENSION>(
// 								 cosine_bins );

//     // Set the time bins
//     std::vector<double> time_bins( 3 );
//     time_bins[0] = 0.0;
//     time_bins[1] = 1.0;
//     time_bins[2] = 2.0;

//     estimator_1_base->setDiscretization<MonteCarlo::TIME_DIMENSION>(time_bins );
//     estimator_2_base->setDiscretization<MonteCarlo::TIME_DIMENSION>(time_bins );

//     // Set the collision number bins
//     std::vector<unsigned> collision_number_bins( 2 );
//     collision_number_bins[0] = 0u;
//     collision_number_bins[1] = 1u;

//     estimator_1_base->setDiscretization<MonteCarlo::COLLISION_NUMBER_DIMENSION>(
// 						       collision_number_bins );
//     estimator_2_base->setDiscretization<MonteCarlo::COLLISION_NUMBER_DIMENSION>(
// 						       collision_number_bins );

//     // Set the particle types
//     std::vector<MonteCarlo::ParticleType> particle_types( 1 );
//     particle_types[0] = MonteCarlo::PHOTON;

//     estimator_1_base->setParticleTypes( particle_types );
//     estimator_2_base->setParticleTypes( particle_types );

//     // Enable thread support
//     estimator_1_base->enableThreadSupport(
// 		 Utility::OpenMPProperties::getRequestedNumberOfThreads() );
//     estimator_2_base->enableThreadSupport(
// 		 Utility::OpenMPProperties::getRequestedNumberOfThreads() );
//   }

//   FRENSIE_CHECK( !estimator_1_base->hasUncommittedHistoryContribution() );
//   FRENSIE_CHECK( !estimator_2_base->hasUncommittedHistoryContribution() );

//   unsigned threads =
//     Utility::OpenMPProperties::getRequestedNumberOfThreads();

//   #pragma omp parallel num_threads( threads )
//   {
//     // bin 0
//     MonteCarlo::PhotonState particle( 0u );
//     particle.setEnergy( 1.0 );
//     particle.setTime( 2.0 );

//     estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
//     estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );

//     estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );
//     estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

//     // bin 1
//     particle.setEnergy( 0.1 );

//     estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
//     estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );

//     estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );
//     estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

//     // bin 2
//     particle.setEnergy( 1.0 );

//     estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
//     estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );

//     estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );
//     estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

//     // bin 3
//     particle.setEnergy( 0.1 );

//     estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
//     estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );

//     estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );
//     estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

//     // bin 4
//     particle.setEnergy( 1.0 );
//     particle.setTime( 1.0 );

//     estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
//     estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );

//     estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );
//     estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

//     // bin 5
//     particle.setEnergy( 0.1 );

//     estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
//     estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );

//     estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );
//     estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

//     // bin 6
//     particle.setEnergy( 1.0 );

//     estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
//     estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );

//     estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );
//     estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

//     // bin 7
//     particle.setEnergy( 0.1 );

//     estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
//     estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );

//     estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );
//     estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

//     // bin 8
//     particle.setEnergy( 1.0 );
//     particle.setTime( 2.0 );
//     particle.incrementCollisionNumber();

//     estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
//     estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );

//     estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );
//     estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

//     // bin 9
//     particle.setEnergy( 0.1 );

//     estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
//     estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );

//     estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );
//     estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

//     // bin 10
//     particle.setEnergy( 1.0 );

//     estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
//     estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );

//     estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );
//     estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

//     // bin 11
//     particle.setEnergy( 0.1 );

//     estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
//     estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );

//     estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );
//     estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

//     // bin 12
//     particle.setEnergy( 1.0 );
//     particle.setTime( 1.0 );

//     estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
//     estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );

//     estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );
//     estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

//     // bin 13
//     particle.setEnergy( 0.1 );

//     estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );
//     estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, 0.5 );

//     estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );
//     estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, 0.5 );

//     // bin 14
//     particle.setEnergy( 1.0 );

//     estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
//     estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );

//     estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );
//     estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

//     // bin 15
//     particle.setEnergy( 0.1 );

//     estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );
//     estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 0, -0.5 );

//     estimator_1->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );
//     estimator_2->updateFromParticleCrossingSurfaceEvent( particle, 1, -0.5 );

//     // Commit the contributions
//     estimator_1_base->commitHistoryContribution();
//     estimator_2_base->commitHistoryContribution();
//   }

//   FRENSIE_CHECK( !estimator_1_base->hasUncommittedHistoryContribution() );
//   FRENSIE_CHECK( !estimator_2_base->hasUncommittedHistoryContribution() );

//   MonteCarlo::Estimator::setNumberOfHistories( threads );
//   MonteCarlo::Estimator::setEndTime( 1.0 );

//   // Initialize the hfd5 file
//   std::shared_ptr<Utility::HDF5FileHandler>
//     hdf5_file( new Utility::HDF5FileHandler );
//   hdf5_file->openHDF5FileAndOverwrite( "test_surface_flux_estimator2.h5" );

//   estimator_1_base->exportData( hdf5_file, true );
//   estimator_2_base->exportData( hdf5_file, true );

//   // Create an estimator hdf5 file handler
//   MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler( hdf5_file );

//   typedef MonteCarlo::StandardSurfaceEstimator::SurfaceIdType SurfaceId;

//   // Retrieve the raw bin data for each entity
//   std::vector<Utility::Pair<double,double> >
//     raw_bin_data( 16, Utility::Pair<double,double>(2.0*threads, 4.0*threads) ),
//     raw_bin_data_copy;

//   hdf5_file_handler.getRawEstimatorEntityBinData<SurfaceId>(
//   						   0u, 0u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
//   					raw_bin_data_copy,
//   					1e-15 );

//   hdf5_file_handler.getRawEstimatorEntityBinData<SurfaceId>(
//   						   0u, 1u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
//   					raw_bin_data_copy,
//   					1e-15 );

//   raw_bin_data[0]( 0.2*threads, 0.2*0.2*threads );
//   raw_bin_data[2]( 0.2*threads, 0.2*0.2*threads );
//   raw_bin_data[4]( 0.2*threads, 0.2*0.2*threads );
//   raw_bin_data[6]( 0.2*threads, 0.2*0.2*threads );
//   raw_bin_data[8]( 0.2*threads, 0.2*0.2*threads );
//   raw_bin_data[10]( 0.2*threads, 0.2*0.2*threads );
//   raw_bin_data[12]( 0.2*threads, 0.2*0.2*threads );
//   raw_bin_data[14]( 0.2*threads, 0.2*0.2*threads );

//   hdf5_file_handler.getRawEstimatorEntityBinData<SurfaceId>(
//   						   1u, 0u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
//   					raw_bin_data_copy,
//   					1e-15 );

//   hdf5_file_handler.getRawEstimatorEntityBinData<SurfaceId>(
//   						   1u, 1u, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
//   					raw_bin_data_copy,
//   					1e-15 );

//   // Retrieve the processed bin data for each entity
//   std::vector<Utility::Pair<double,double> >
//     processed_bin_data( 16, Utility::Pair<double,double>( 20.0, 0.0 ) ),
//     processed_bin_data_copy;

//   hdf5_file_handler.getProcessedEstimatorEntityBinData<SurfaceId>(
//   					     0u, 0u, processed_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_bin_data,
//   					processed_bin_data_copy,
//   					1e-15 );

//   processed_bin_data.clear();
//   processed_bin_data.resize( 16, Utility::Pair<double,double>( 10.0, 0.0 ) );

//   hdf5_file_handler.getProcessedEstimatorEntityBinData<SurfaceId>(
//   					     0u, 1u, processed_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_bin_data,
//   					processed_bin_data_copy,
//   					1e-15 );

//   processed_bin_data.clear();
//   processed_bin_data.resize( 16, Utility::Pair<double,double>( 20.0, 0.0 ) );
//   processed_bin_data[0]( 2.0, 0.0 );
//   processed_bin_data[2]( 2.0, 0.0 );
//   processed_bin_data[4]( 2.0, 0.0 );
//   processed_bin_data[6]( 2.0, 0.0 );
//   processed_bin_data[8]( 2.0, 0.0 );
//   processed_bin_data[10]( 2.0, 0.0 );
//   processed_bin_data[12]( 2.0, 0.0 );
//   processed_bin_data[14]( 2.0, 0.0 );

//   hdf5_file_handler.getProcessedEstimatorEntityBinData<SurfaceId>(
//   					     1u, 0u, processed_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_bin_data,
//   					processed_bin_data_copy,
//   					1e-15 );

//   processed_bin_data.clear();
//   processed_bin_data.resize( 16, Utility::Pair<double,double>( 10.0, 0.0 ) );
//   processed_bin_data[0]( 1.0, 0.0 );
//   processed_bin_data[2]( 1.0, 0.0 );
//   processed_bin_data[4]( 1.0, 0.0 );
//   processed_bin_data[6]( 1.0, 0.0 );
//   processed_bin_data[8]( 1.0, 0.0 );
//   processed_bin_data[10]( 1.0, 0.0 );
//   processed_bin_data[12]( 1.0, 0.0 );
//   processed_bin_data[14]( 1.0, 0.0 );

//   hdf5_file_handler.getProcessedEstimatorEntityBinData<SurfaceId>(
//   					     1u, 1u, processed_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_bin_data,
//   					processed_bin_data_copy,
//   					1e-15 );

//   // Retrieve the raw total bin data
//   std::vector<Utility::Pair<double,double> >
//     raw_total_bin_data(16,
// 		       Utility::Pair<double,double>(4.0*threads,16.0*threads)),
//     raw_total_bin_data_copy;

//   hdf5_file_handler.getRawEstimatorTotalBinData( 0u, raw_total_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_bin_data,
//   					raw_total_bin_data_copy,
//   					1e-15 );

//   raw_total_bin_data[0]( 0.4*threads, 0.16*threads );
//   raw_total_bin_data[2]( 0.4*threads, 0.16*threads );
//   raw_total_bin_data[4]( 0.4*threads, 0.16*threads );
//   raw_total_bin_data[6]( 0.4*threads, 0.16*threads );
//   raw_total_bin_data[8]( 0.4*threads, 0.16*threads );
//   raw_total_bin_data[10]( 0.4*threads, 0.16*threads );
//   raw_total_bin_data[12]( 0.4*threads, 0.16*threads );
//   raw_total_bin_data[14]( 0.4*threads, 0.16*threads );

//   hdf5_file_handler.getRawEstimatorTotalBinData( 1u, raw_total_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_bin_data,
//   					raw_total_bin_data_copy,
//   					1e-15 );

//   // Retrieve the processed total bin data
//   std::vector<Utility::Pair<double,double> >
//     processed_total_bin_data( 16, Utility::Pair<double,double>( 40.0/3, 0.0 )),
//     processed_total_bin_data_copy;

//   hdf5_file_handler.getProcessedEstimatorTotalBinData(
//   					   0u, processed_total_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_bin_data,
//   					processed_total_bin_data_copy,
//   					1e-15 );

//   processed_total_bin_data[0]( 4.0/3, 0.0 );
//   processed_total_bin_data[2]( 4.0/3, 0.0 );
//   processed_total_bin_data[4]( 4.0/3, 0.0 );
//   processed_total_bin_data[6]( 4.0/3, 0.0 );
//   processed_total_bin_data[8]( 4.0/3, 0.0 );
//   processed_total_bin_data[10]( 4.0/3, 0.0 );
//   processed_total_bin_data[12]( 4.0/3, 0.0 );
//   processed_total_bin_data[14]( 4.0/3, 0.0 );

//   hdf5_file_handler.getProcessedEstimatorTotalBinData(
//   					   1u, processed_total_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_bin_data,
//   					processed_total_bin_data_copy,
//   					1e-15 );

//   // Retrieve the raw estimator total data for each entity
//   Utility::Quad<double,double,double,double>
//     raw_moments( 32.0*threads,
// 		 1024.0*threads,
// 		 32768.0*threads,
// 		 1048576.0*threads );

//   std::vector<Utility::Quad<double,double,double,double> >
//     raw_total_data( 1, raw_moments ),
//     raw_total_data_copy;

//   hdf5_file_handler.getRawEstimatorEntityTotalData<SurfaceId>(
//   						 0u, 0u, raw_total_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data,
//   					raw_total_data_copy,
//   					1e-15 );

//   hdf5_file_handler.getRawEstimatorEntityTotalData<SurfaceId>(
//   						 0u, 1u, raw_total_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data,
//   					raw_total_data_copy,
//   					1e-15 );

//   raw_total_data[0]( 17.6*threads,
// 		     309.76*threads,
// 		     5451.776*threads,
// 		     95951.2576*threads );

//   hdf5_file_handler.getRawEstimatorEntityTotalData<SurfaceId>(
//   						 1u, 0u, raw_total_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data,
//   					raw_total_data_copy,
//   					1e-15 );

//   hdf5_file_handler.getRawEstimatorEntityTotalData<SurfaceId>(
//   						 1u, 1u, raw_total_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data,
//   					raw_total_data_copy,
//   					1e-15 );

//   // Retrieve the processed estimator total data for each entity
//   Utility::Quad<double,double,double,double>
//     processed_moments( 320.0, 0.0, 0.0, 0.0 );

//   std::vector<Utility::Quad<double,double,double,double> >
//     processed_total_data( 1, processed_moments ),
//     processed_total_data_copy;

//   hdf5_file_handler.getProcessedEstimatorEntityTotalData<SurfaceId>(
//   					   0u, 0u, processed_total_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_data,
//   					processed_total_data_copy,
//   					1e-15 );

//   processed_total_data[0]( 160.0, 0.0, 0.0, 0.0 );

//   hdf5_file_handler.getProcessedEstimatorEntityTotalData<SurfaceId>(
//   					   0u, 1u, processed_total_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_data,
//   					processed_total_data_copy,
//   					1e-15 );

//   processed_total_data[0]( 176.0, 0.0, 0.0, 0.0 );

//   hdf5_file_handler.getProcessedEstimatorEntityTotalData<SurfaceId>(
//   					   1u, 0u, processed_total_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_data,
//   					processed_total_data_copy,
//   					1e-15 );

//   processed_total_data[0]( 88.0, 0.0, 0.0, 0.0 );

//   hdf5_file_handler.getProcessedEstimatorEntityTotalData<SurfaceId>(
//   					   1u, 1u, processed_total_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_data,
//   					processed_total_data_copy,
//   					1e-15 );

//   // Retrieve the raw total data
//   raw_total_data[0]( 64.0*threads,
// 		     4096.0*threads,
// 		     262144.0*threads,
// 		     16777216.0*threads );

//   hdf5_file_handler.getRawEstimatorTotalData( 0u, raw_total_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data,
//   					raw_total_data_copy,
//   					1e-15 );

//   raw_total_data[0]( 35.2*threads,
// 		     1239.04*threads,
// 		     43614.208*threads,
// 		     1535220.1216*threads );

//   hdf5_file_handler.getRawEstimatorTotalData( 1u, raw_total_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data,
//   					raw_total_data_copy,
//   					1e-15 );

//   // Retrieve the processed total data
//   processed_total_data[0]( 640.0/3, 0.0, 0.0, 0.0 );

//   hdf5_file_handler.getProcessedEstimatorTotalData(
//   					       0u, processed_total_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_data,
//   					processed_total_data_copy,
//   					1e-15 );

//   processed_total_data[0]( 352.0/3, 0.0, 0.0, 0.0 );

//   hdf5_file_handler.getProcessedEstimatorTotalData(
//   					       1u, processed_total_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_data,
//   					processed_total_data_copy,
//   					1e-15 );
// }

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
// end tstSurfaceFluxEstimator.cpp
//---------------------------------------------------------------------------//
