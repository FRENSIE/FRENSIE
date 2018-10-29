//---------------------------------------------------------------------------//
//!
//! \file   tstTetMeshTrackLengthFluxEstimator.cpp
//! \author Eli Moll
//! \brief  TetMeshTrackLengthFluxEstimator class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_MeshTrackLengthFluxEstimator.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Utility_TetMesh.hpp"
#include "Utility_OpenMPProperties.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

typedef std::tuple<MonteCarlo::WeightMultiplier,
                   MonteCarlo::WeightAndEnergyMultiplier,
                   MonteCarlo::WeightAndChargeMultiplier
                  > MultiplierPolicies;

//---------------------------------------------------------------------------//
// Testing variables
//---------------------------------------------------------------------------//

std::shared_ptr<const Utility::Mesh> tet_mesh;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the estimator is a mesh type estimator
FRENSIE_UNIT_TEST_TEMPLATE( TetMeshTrackLengthFluxEstimator,
                            check_type,
                            MultiplierPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, ContributionMultiplierPolicy );

  std::shared_ptr<MonteCarlo::Estimator> estimator(
    new MonteCarlo::MeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>(
                                                                  0,
                                                                  1.0,
                                                                  tet_mesh ) );

  FRENSIE_CHECK( !estimator->isCellEstimator() );
  FRENSIE_CHECK( !estimator->isSurfaceEstimator() );
  FRENSIE_CHECK( estimator->isMeshEstimator() );

}
//---------------------------------------------------------------------------//
// Check that estimator bins can be set
FRENSIE_UNIT_TEST_TEMPLATE( TetMeshTrackLengthFluxEstimator,
                            setDiscretization,
                            MultiplierPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, ContributionMultiplierPolicy );

  std::shared_ptr<MonteCarlo::Estimator> estimator(
    new MonteCarlo::MeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>(
                                                                  0,
                                                                  1.0,
                                                                  tet_mesh ) );

  std::vector<double> energy_bin_boundaries( 3 );
  energy_bin_boundaries[0] = 0.0;
  energy_bin_boundaries[1] = 0.1;
  energy_bin_boundaries[2] = 1.0;

  estimator->setDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION>(
						       energy_bin_boundaries );

  FRENSIE_CHECK_EQUAL(estimator->getNumberOfBins(MonteCarlo::OBSERVER_ENERGY_DIMENSION),
		      2 );
  FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins(), 2 );

  std::vector<double> time_bin_boundaries( 3 );
  time_bin_boundaries[0] = 0.0;
  time_bin_boundaries[1] = 1.0;
  time_bin_boundaries[2] = 2.0;

  estimator->setDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION>(
							 time_bin_boundaries );

  FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins(MonteCarlo::OBSERVER_TIME_DIMENSION),
		       2 );
  FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins(), 4 );

  std::vector<unsigned> collision_number_bins( 2 );
  collision_number_bins[0] = 0u;
  collision_number_bins[1] = 10u;

  estimator->setDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION>(
						       collision_number_bins );

  FRENSIE_CHECK_EQUAL(
     estimator->getNumberOfBins( MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION ), 2 );
  FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins(), 8 );

  // Make sure cosine bins cannot be set
  std::vector<double> cosine_bin_boundaries( 3 );
  cosine_bin_boundaries[0] = -1.0;
  cosine_bin_boundaries[1] = 0.0;
  cosine_bin_boundaries[2] = 1.0;

  estimator->setDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION>(
						       cosine_bin_boundaries );

  FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins( MonteCarlo::OBSERVER_COSINE_DIMENSION ),
                       1 );
  FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins(), 8 );
}

//---------------------------------------------------------------------------//
// Check that particle types can be assigned
FRENSIE_UNIT_TEST_TEMPLATE( TetMeshTrackLengthFluxEstimator,
                            setParticleType,
                            MultiplierPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, ContributionMultiplierPolicy );

  std::shared_ptr<MonteCarlo::Estimator> estimator(
    new MonteCarlo::MeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>(
                                                                  0,
                                                                  1.0,
                                                                  tet_mesh ) );

  std::vector<MonteCarlo::ParticleType> particle_types( 4 );
  particle_types[0] = MonteCarlo::PHOTON;
  particle_types[1] = MonteCarlo::NEUTRON;
  particle_types[2] = MonteCarlo::ADJOINT_PHOTON;
  particle_types[3] = MonteCarlo::ADJOINT_NEUTRON;

  // All but the first particle type should be ignored
  estimator->setParticleTypes( particle_types );

  FRENSIE_CHECK( estimator->isParticleTypeAssigned( MonteCarlo::PHOTON ) );
  FRENSIE_CHECK( !estimator->isParticleTypeAssigned( MonteCarlo::NEUTRON ) );
  FRENSIE_CHECK( !estimator->isParticleTypeAssigned( MonteCarlo::ADJOINT_PHOTON ) );
  FRENSIE_CHECK( !estimator->isParticleTypeAssigned( MonteCarlo::ADJOINT_NEUTRON ) );

  particle_types[0] = MonteCarlo::NEUTRON;
  particle_types[1] = MonteCarlo::PHOTON;

  // All particle types should be ignored
  estimator->setParticleTypes( particle_types );

  FRENSIE_CHECK( estimator->isParticleTypeAssigned( MonteCarlo::PHOTON ) );
  FRENSIE_CHECK( !estimator->isParticleTypeAssigned( MonteCarlo::NEUTRON ) );
  FRENSIE_CHECK( !estimator->isParticleTypeAssigned( MonteCarlo::ADJOINT_PHOTON ) );
  FRENSIE_CHECK( !estimator->isParticleTypeAssigned( MonteCarlo::ADJOINT_NEUTRON ) );
}

//---------------------------------------------------------------------------//
// Check that a partial history contribution can be added to the estimator
FRENSIE_UNIT_TEST( TetMeshTrackLengthFluxEstimator,
                   updateFromGlobalParticleSubtrackEndingEvent )
{
  std::shared_ptr<MonteCarlo::MeshTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier> > estimator_1;
  std::shared_ptr<MonteCarlo::MeshTrackLengthFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier> > estimator_2;
  std::shared_ptr<MonteCarlo::MeshTrackLengthFluxEstimator<MonteCarlo::WeightAndChargeMultiplier> > estimator_3;

  std::shared_ptr<MonteCarlo::Estimator> estimator_1_base, estimator_2_base, estimator_3_base;

  {
    estimator_1.reset( new MonteCarlo::MeshTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier>(
                                                                  0,
                                                                  1.0,
                                                                  tet_mesh ) );

    estimator_1_base = estimator_1;

    estimator_2.reset( new MonteCarlo::MeshTrackLengthFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier>(
                                                                  1,
                                                                  10.0,
                                                                  tet_mesh ) );

    estimator_2_base = estimator_2;

    estimator_3.reset( new MonteCarlo::MeshTrackLengthFluxEstimator<MonteCarlo::WeightAndChargeMultiplier>(
                                                                  2,
                                                                  1.0,
                                                                  tet_mesh ) );

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

    // Set the time bins
    std::vector<double> time_bin_boundaries( 3 );
    time_bin_boundaries[0] = 0.0;
    time_bin_boundaries[1] = 1.0213272871857804e-11;
    time_bin_boundaries[2] = 2.0426545743715607e-11;

    estimator_1_base->setDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION>(
						       time_bin_boundaries );

    // Set the particle types
    std::vector<MonteCarlo::ParticleType> particle_types( 1 );
    particle_types[0] = MonteCarlo::PHOTON;

    estimator_1_base->setParticleTypes( particle_types );
    estimator_2_base->setParticleTypes( particle_types );
    estimator_3_base->setParticleTypes( particle_types );
  }

  // Known contributions and values
  double track_length = 0.6123724356957940;
  double volume = 1.0/6;
  double num_tets = 6.0;

  double start_point_1[3] = { 0.25, 0.0, 0.75 };
  double end_point_1[3] = { 0.75, 0.25, 1.0 };

  double start_point_2[3] = { 0.0, 0.25, 0.75 };
  double end_point_2[3] = { 0.25, 0.75, 1.0 };

  double start_point_3[3] = { 0.75, 0.0, 0.25 };
  double end_point_3[3] = { 1.0, 0.25, 0.75 };

  double start_point_4[3] = { 0.0, 0.75, 0.25 };
  double end_point_4[3] = { 0.25, 1.0, 0.75 };

  double start_point_5[3] = { 0.75, 0.25, 0.0 };
  double end_point_5[3] = { 1.0, 0.75, 0.25 };

  double start_point_6[3] = { 0.25, 0.75, 0.0 };
  double end_point_6[3] = { 0.75, 1.0, 0.25 };

  // bin 0, 2
  MonteCarlo::PhotonState particle( 0 );
  particle.setEnergy( 1.0 );
  particle.setTime( 2.0426545743715623e-11 );
  particle.setWeight( 1.0 );

  estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_1,
                                                            end_point_1 );
  estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_2,
                                                            end_point_2 );
  estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_3,
                                                            end_point_3 );
  estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_4,
                                                            end_point_4 );
  estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_5,
                                                            end_point_5 );
  estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_6,
                                                            end_point_6 );

  estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_1,
                                                            end_point_1 );
  estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_2,
                                                            end_point_2 );
  estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_3,
                                                            end_point_3 );
  estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_4,
                                                            end_point_4 );
  estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_5,
                                                            end_point_5 );
  estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_6,
                                                            end_point_6 );

  estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_1,
                                                            end_point_1 );
  estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_2,
                                                            end_point_2 );
  estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_3,
                                                            end_point_3 );
  estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_4,
                                                            end_point_4 );
  estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_5,
                                                            end_point_5 );
  estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_6,
                                                            end_point_6 );

  FRENSIE_CHECK( estimator_1->hasUncommittedHistoryContribution() );
  FRENSIE_CHECK( estimator_2->hasUncommittedHistoryContribution() );
  FRENSIE_CHECK( estimator_3->hasUncommittedHistoryContribution() );

  // bin 1, 3
  particle.setEnergy( 0.1 );

  estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_1,
                                                            end_point_1 );
  estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_2,
                                                            end_point_2 );
  estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_3,
                                                            end_point_3 );
  estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_4,
                                                            end_point_4 );
  estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_5,
                                                            end_point_5 );
  estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_6,
                                                            end_point_6 );

  particle.setWeight( 10.0 );

  estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_1,
                                                            end_point_1 );
  estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_2,
                                                            end_point_2 );
  estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_3,
                                                            end_point_3 );
  estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_4,
                                                            end_point_4 );
  estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_5,
                                                            end_point_5 );
  estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_6,
                                                            end_point_6 );

  particle.setWeight( 1.0 );

  estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_1,
                                                            end_point_1 );
  estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_2,
                                                            end_point_2 );
  estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_3,
                                                            end_point_3 );
  estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_4,
                                                            end_point_4 );
  estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_5,
                                                            end_point_5 );
  estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_6,
                                                            end_point_6 );

  // Commit the contributions
  estimator_1_base->commitHistoryContribution();
  estimator_2_base->commitHistoryContribution();
  estimator_3_base->commitHistoryContribution();

  FRENSIE_CHECK( !estimator_1_base->hasUncommittedHistoryContribution() );
  FRENSIE_CHECK( !estimator_2_base->hasUncommittedHistoryContribution() );
  FRENSIE_CHECK( !estimator_3_base->hasUncommittedHistoryContribution() );

  MonteCarlo::ParticleHistoryObserver::setNumberOfHistories( 1.0 );
  MonteCarlo::ParticleHistoryObserver::setElapsedTime( 1.0 );

  // Check the entity bin data moments
  Utility::ArrayView<const double> entity_bin_first_moments =
    estimator_1_base->getEntityBinDataFirstMoments( 5764607523034234881 );

  Utility::ArrayView<const double> entity_bin_second_moments =
    estimator_1_base->getEntityBinDataSecondMoments( 5764607523034234881 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 4, 3.061862178478970131e-01 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 4, 0.09374999999999985 ),
                                   1e-15 );

  entity_bin_first_moments =
    estimator_1_base->getEntityBinDataFirstMoments( 5764607523034234882 );

  entity_bin_second_moments =
    estimator_1_base->getEntityBinDataSecondMoments( 5764607523034234882 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 4, 3.061862178478970131e-01 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 4, 0.09374999999999985 ),
                                   1e-15 );

  entity_bin_first_moments =
    estimator_1_base->getEntityBinDataFirstMoments( 5764607523034234883 );

  entity_bin_second_moments =
    estimator_1_base->getEntityBinDataSecondMoments( 5764607523034234883 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 4, 3.061862178478970131e-01 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 4, 0.09374999999999985 ),
                                   1e-15 );

  entity_bin_first_moments =
    estimator_1_base->getEntityBinDataFirstMoments( 5764607523034234884 );

  entity_bin_second_moments =
    estimator_1_base->getEntityBinDataSecondMoments( 5764607523034234884 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 4, 3.061862178478970131e-01 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 4, 0.09374999999999985 ),
                                   1e-15 );

  entity_bin_first_moments =
    estimator_1_base->getEntityBinDataFirstMoments( 5764607523034234885 );

  entity_bin_second_moments =
    estimator_1_base->getEntityBinDataSecondMoments( 5764607523034234885 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 4, 3.061862178478970131e-01 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 4, 0.09374999999999985 ),
                                   1e-15 );

  entity_bin_first_moments =
    estimator_1_base->getEntityBinDataFirstMoments( 5764607523034234886 );

  entity_bin_second_moments =
    estimator_1_base->getEntityBinDataSecondMoments( 5764607523034234886 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 4, 3.061862178478970131e-01 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 4, 0.09374999999999985 ),
                                   1e-15 );

  entity_bin_first_moments =
    estimator_2_base->getEntityBinDataFirstMoments( 5764607523034234881 );

  entity_bin_second_moments =
    estimator_2_base->getEntityBinDataSecondMoments( 5764607523034234881 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 2, 0.6123724356957940 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 2, 0.3749999999999994 ),
                                   1e-14 );

  entity_bin_first_moments =
    estimator_2_base->getEntityBinDataFirstMoments( 5764607523034234882 );

  entity_bin_second_moments =
    estimator_2_base->getEntityBinDataSecondMoments( 5764607523034234882 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 2, 0.6123724356957940 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 2, 0.3749999999999994 ),
                                   1e-14 );

  entity_bin_first_moments =
    estimator_2_base->getEntityBinDataFirstMoments( 5764607523034234883 );

  entity_bin_second_moments =
    estimator_2_base->getEntityBinDataSecondMoments( 5764607523034234883 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 2, 0.6123724356957940 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 2, 0.3749999999999994 ),
                                   1e-14 );

  entity_bin_first_moments =
    estimator_2_base->getEntityBinDataFirstMoments( 5764607523034234884 );

  entity_bin_second_moments =
    estimator_2_base->getEntityBinDataSecondMoments( 5764607523034234884 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 2, 0.6123724356957940 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 2, 0.3749999999999994 ),
                                   1e-14 );

  entity_bin_first_moments =
    estimator_2_base->getEntityBinDataFirstMoments( 5764607523034234885 );

  entity_bin_second_moments =
    estimator_2_base->getEntityBinDataSecondMoments( 5764607523034234885 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 2, 0.6123724356957940 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 2, 0.3749999999999994 ),
                                   1e-14 );

  entity_bin_first_moments =
    estimator_2_base->getEntityBinDataFirstMoments( 5764607523034234886 );

  entity_bin_second_moments =
    estimator_2_base->getEntityBinDataSecondMoments( 5764607523034234886 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 2, 0.6123724356957940 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 2, 0.3749999999999994 ),
                                   1e-14 );

  entity_bin_first_moments =
    estimator_3_base->getEntityBinDataFirstMoments( 5764607523034234881 );

  entity_bin_second_moments =
    estimator_3_base->getEntityBinDataSecondMoments( 5764607523034234881 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 2, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 2, 0.0 ), 1e-15 );

  entity_bin_first_moments =
    estimator_3_base->getEntityBinDataFirstMoments( 5764607523034234882 );

  entity_bin_second_moments =
    estimator_3_base->getEntityBinDataSecondMoments( 5764607523034234882 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 2, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 2, 0.0 ), 1e-15 );

  entity_bin_first_moments =
    estimator_3_base->getEntityBinDataFirstMoments( 5764607523034234883 );

  entity_bin_second_moments =
    estimator_3_base->getEntityBinDataSecondMoments( 5764607523034234883 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 2, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 2, 0.0 ), 1e-15 );

  entity_bin_first_moments =
    estimator_3_base->getEntityBinDataFirstMoments( 5764607523034234884 );

  entity_bin_second_moments =
    estimator_3_base->getEntityBinDataSecondMoments( 5764607523034234884 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 2, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 2, 0.0 ), 1e-15 );

  entity_bin_first_moments =
    estimator_3_base->getEntityBinDataFirstMoments( 5764607523034234885 );

  entity_bin_second_moments =
    estimator_3_base->getEntityBinDataSecondMoments( 5764607523034234885 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 2, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 2, 0.0 ), 1e-15 );

  entity_bin_first_moments =
    estimator_3_base->getEntityBinDataFirstMoments( 5764607523034234886 );

  entity_bin_second_moments =
    estimator_3_base->getEntityBinDataSecondMoments( 5764607523034234886 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 2, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 2, 0.0 ), 1e-15 );

  // Check the total bin data moments
  Utility::ArrayView<const double> total_bin_first_moments =
    estimator_1_base->getTotalBinDataFirstMoments();

  Utility::ArrayView<const double> total_bin_second_moments =
    estimator_1_base->getTotalBinDataSecondMoments();

  FRENSIE_CHECK_FLOATING_EQUALITY( total_bin_first_moments,
                                   std::vector<double>( 4, 1.837117307087382 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_bin_second_moments,
                                   std::vector<double>( 4, 3.3749999999999947 ),
                                   1e-15 );

  total_bin_first_moments =
    estimator_2_base->getTotalBinDataFirstMoments();

  total_bin_second_moments =
    estimator_2_base->getTotalBinDataSecondMoments();

  FRENSIE_CHECK_FLOATING_EQUALITY( total_bin_first_moments,
                                   std::vector<double>( 2, 3.674234614174764 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_bin_second_moments,
                                   std::vector<double>( 2, 13.499999999999979 ),
                                   1e-14 );

  total_bin_first_moments =
    estimator_3_base->getTotalBinDataFirstMoments();

  total_bin_second_moments =
    estimator_3_base->getTotalBinDataSecondMoments();

  FRENSIE_CHECK_FLOATING_EQUALITY( total_bin_first_moments,
                                   std::vector<double>( 2, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_bin_second_moments,
                                   std::vector<double>( 2, 0.0 ), 1e-15 );

  // Check the entity total data moments
  Utility::ArrayView<const double> entity_total_first_moments =
    estimator_1_base->getEntityTotalDataFirstMoments( 5764607523034234881 );

  Utility::ArrayView<const double> entity_total_second_moments =
    estimator_1_base->getEntityTotalDataSecondMoments( 5764607523034234881 );

  Utility::ArrayView<const double> entity_total_third_moments =
    estimator_1_base->getEntityTotalDataThirdMoments( 5764607523034234881 );

  Utility::ArrayView<const double> entity_total_fourth_moments =
    estimator_1_base->getEntityTotalDataFourthMoments( 5764607523034234881 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 1, 1.224744871391588 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 1, 1.4999999999999976 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 1, 1.8371173070873792 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 1, 2.249999999999993 ),
                                   1e-15 );

  entity_total_first_moments =
    estimator_1_base->getEntityTotalDataFirstMoments( 5764607523034234882 );

  entity_total_second_moments =
    estimator_1_base->getEntityTotalDataSecondMoments( 5764607523034234882 );

  entity_total_third_moments =
    estimator_1_base->getEntityTotalDataThirdMoments( 5764607523034234882 );

  entity_total_fourth_moments =
    estimator_1_base->getEntityTotalDataFourthMoments( 5764607523034234882 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 1, 1.224744871391588 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 1, 1.4999999999999976 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 1, 1.8371173070873792 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 1, 2.249999999999993 ),
                                   1e-15 );

  entity_total_first_moments =
    estimator_1_base->getEntityTotalDataFirstMoments( 5764607523034234883 );

  entity_total_second_moments =
    estimator_1_base->getEntityTotalDataSecondMoments( 5764607523034234883 );

  entity_total_third_moments =
    estimator_1_base->getEntityTotalDataThirdMoments( 5764607523034234883 );

  entity_total_fourth_moments =
    estimator_1_base->getEntityTotalDataFourthMoments( 5764607523034234883 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 1, 1.224744871391588 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 1, 1.4999999999999976 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 1, 1.8371173070873792 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 1, 2.249999999999993 ),
                                   1e-15 );

  entity_total_first_moments =
    estimator_1_base->getEntityTotalDataFirstMoments( 5764607523034234884 );

  entity_total_second_moments =
    estimator_1_base->getEntityTotalDataSecondMoments( 5764607523034234884 );

  entity_total_third_moments =
    estimator_1_base->getEntityTotalDataThirdMoments( 5764607523034234884 );

  entity_total_fourth_moments =
    estimator_1_base->getEntityTotalDataFourthMoments( 5764607523034234884 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 1, 1.224744871391588 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 1, 1.4999999999999976 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 1, 1.8371173070873792 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 1, 2.249999999999993 ),
                                   1e-15 );

  entity_total_first_moments =
    estimator_1_base->getEntityTotalDataFirstMoments( 5764607523034234885 );

  entity_total_second_moments =
    estimator_1_base->getEntityTotalDataSecondMoments( 5764607523034234885 );

  entity_total_third_moments =
    estimator_1_base->getEntityTotalDataThirdMoments( 5764607523034234885 );

  entity_total_fourth_moments =
    estimator_1_base->getEntityTotalDataFourthMoments( 5764607523034234885 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 1, 1.224744871391588 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 1, 1.4999999999999976 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 1, 1.8371173070873792 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 1, 2.249999999999993 ),
                                   1e-15 );

  entity_total_first_moments =
    estimator_1_base->getEntityTotalDataFirstMoments( 5764607523034234886 );

  entity_total_second_moments =
    estimator_1_base->getEntityTotalDataSecondMoments( 5764607523034234886 );

  entity_total_third_moments =
    estimator_1_base->getEntityTotalDataThirdMoments( 5764607523034234886 );

  entity_total_fourth_moments =
    estimator_1_base->getEntityTotalDataFourthMoments( 5764607523034234886 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 1, 1.224744871391588 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 1, 1.4999999999999976 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 1, 1.8371173070873792 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 1, 2.249999999999993 ),
                                   1e-15 );

  entity_total_first_moments =
    estimator_2_base->getEntityTotalDataFirstMoments( 5764607523034234881 );

  entity_total_second_moments =
    estimator_2_base->getEntityTotalDataSecondMoments( 5764607523034234881 );

  entity_total_third_moments =
    estimator_2_base->getEntityTotalDataThirdMoments( 5764607523034234881 );

  entity_total_fourth_moments =
    estimator_2_base->getEntityTotalDataFourthMoments( 5764607523034234881 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 1, 1.224744871391588 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 1, 1.4999999999999976 ),
                                   1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 1, 1.8371173070873792 ),
                                   1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 1, 2.249999999999993 ),
                                   1e-14 );

  entity_total_first_moments =
    estimator_2_base->getEntityTotalDataFirstMoments( 5764607523034234882 );

  entity_total_second_moments =
    estimator_2_base->getEntityTotalDataSecondMoments( 5764607523034234882 );

  entity_total_third_moments =
    estimator_2_base->getEntityTotalDataThirdMoments( 5764607523034234882 );

  entity_total_fourth_moments =
    estimator_2_base->getEntityTotalDataFourthMoments( 5764607523034234882 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 1, 1.224744871391588 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 1, 1.4999999999999976 ),
                                   1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 1, 1.8371173070873792 ),
                                   1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 1, 2.249999999999993 ),
                                   1e-14 );

  entity_total_first_moments =
    estimator_2_base->getEntityTotalDataFirstMoments( 5764607523034234883 );

  entity_total_second_moments =
    estimator_2_base->getEntityTotalDataSecondMoments( 5764607523034234883 );

  entity_total_third_moments =
    estimator_2_base->getEntityTotalDataThirdMoments( 5764607523034234883 );

  entity_total_fourth_moments =
    estimator_2_base->getEntityTotalDataFourthMoments( 5764607523034234883 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 1, 1.224744871391588 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 1, 1.4999999999999976 ),
                                   1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 1, 1.8371173070873792 ),
                                   1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 1, 2.249999999999993 ),
                                   1e-14 );

  entity_total_first_moments =
    estimator_2_base->getEntityTotalDataFirstMoments( 5764607523034234884 );

  entity_total_second_moments =
    estimator_2_base->getEntityTotalDataSecondMoments( 5764607523034234884 );

  entity_total_third_moments =
    estimator_2_base->getEntityTotalDataThirdMoments( 5764607523034234884 );

  entity_total_fourth_moments =
    estimator_2_base->getEntityTotalDataFourthMoments( 5764607523034234884 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 1, 1.224744871391588 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 1, 1.4999999999999976 ),
                                   1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 1, 1.8371173070873792 ),
                                   1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 1, 2.249999999999993 ),
                                   1e-14 );

  entity_total_first_moments =
    estimator_2_base->getEntityTotalDataFirstMoments( 5764607523034234885 );

  entity_total_second_moments =
    estimator_2_base->getEntityTotalDataSecondMoments( 5764607523034234885 );

  entity_total_third_moments =
    estimator_2_base->getEntityTotalDataThirdMoments( 5764607523034234885 );

  entity_total_fourth_moments =
    estimator_2_base->getEntityTotalDataFourthMoments( 5764607523034234885 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 1, 1.224744871391588 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 1, 1.4999999999999976 ),
                                   1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 1, 1.8371173070873792 ),
                                   1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 1, 2.249999999999993 ),
                                   1e-14 );

  entity_total_first_moments =
    estimator_2_base->getEntityTotalDataFirstMoments( 5764607523034234886 );

  entity_total_second_moments =
    estimator_2_base->getEntityTotalDataSecondMoments( 5764607523034234886 );

  entity_total_third_moments =
    estimator_2_base->getEntityTotalDataThirdMoments( 5764607523034234886 );

  entity_total_fourth_moments =
    estimator_2_base->getEntityTotalDataFourthMoments( 5764607523034234886 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 1, 1.224744871391588 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 1, 1.4999999999999976 ),
                                   1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 1, 1.8371173070873792 ),
                                   1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 1, 2.249999999999993 ),
                                   1e-14 );

  entity_total_first_moments =
    estimator_3_base->getEntityTotalDataFirstMoments( 5764607523034234881 );

  entity_total_second_moments =
    estimator_3_base->getEntityTotalDataSecondMoments( 5764607523034234881 );

  entity_total_third_moments =
    estimator_3_base->getEntityTotalDataThirdMoments( 5764607523034234881 );

  entity_total_fourth_moments =
    estimator_3_base->getEntityTotalDataFourthMoments( 5764607523034234881 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );

  entity_total_first_moments =
    estimator_3_base->getEntityTotalDataFirstMoments( 5764607523034234882 );

  entity_total_second_moments =
    estimator_3_base->getEntityTotalDataSecondMoments( 5764607523034234882 );

  entity_total_third_moments =
    estimator_3_base->getEntityTotalDataThirdMoments( 5764607523034234882 );

  entity_total_fourth_moments =
    estimator_3_base->getEntityTotalDataFourthMoments( 5764607523034234882 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );

  entity_total_first_moments =
    estimator_3_base->getEntityTotalDataFirstMoments( 5764607523034234883 );

  entity_total_second_moments =
    estimator_3_base->getEntityTotalDataSecondMoments( 5764607523034234883 );

  entity_total_third_moments =
    estimator_3_base->getEntityTotalDataThirdMoments( 5764607523034234883 );

  entity_total_fourth_moments =
    estimator_3_base->getEntityTotalDataFourthMoments( 5764607523034234883 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );

  entity_total_first_moments =
    estimator_3_base->getEntityTotalDataFirstMoments( 5764607523034234884 );

  entity_total_second_moments =
    estimator_3_base->getEntityTotalDataSecondMoments( 5764607523034234884 );

  entity_total_third_moments =
    estimator_3_base->getEntityTotalDataThirdMoments( 5764607523034234884 );

  entity_total_fourth_moments =
    estimator_3_base->getEntityTotalDataFourthMoments( 5764607523034234884 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );

  entity_total_first_moments =
    estimator_3_base->getEntityTotalDataFirstMoments( 5764607523034234885 );

  entity_total_second_moments =
    estimator_3_base->getEntityTotalDataSecondMoments( 5764607523034234885 );

  entity_total_third_moments =
    estimator_3_base->getEntityTotalDataThirdMoments( 5764607523034234885 );

  entity_total_fourth_moments =
    estimator_3_base->getEntityTotalDataFourthMoments( 5764607523034234885 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );

  entity_total_first_moments =
    estimator_3_base->getEntityTotalDataFirstMoments( 5764607523034234886 );

  entity_total_second_moments =
    estimator_3_base->getEntityTotalDataSecondMoments( 5764607523034234886 );

  entity_total_third_moments =
    estimator_3_base->getEntityTotalDataThirdMoments( 5764607523034234886 );

  entity_total_fourth_moments =
    estimator_3_base->getEntityTotalDataFourthMoments( 5764607523034234886 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );

  // Check the total data moments
  Utility::ArrayView<const double> total_first_moments =
    estimator_1_base->getTotalDataFirstMoments();

  Utility::ArrayView<const double> total_second_moments =
    estimator_1_base->getTotalDataSecondMoments();

  Utility::ArrayView<const double> total_third_moments =
    estimator_1_base->getTotalDataThirdMoments();

  Utility::ArrayView<const double> total_fourth_moments =
    estimator_1_base->getTotalDataFourthMoments();

  FRENSIE_CHECK_FLOATING_EQUALITY( total_first_moments,
                                   std::vector<double>( 1, 7.348469228349528 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_second_moments,
                                   std::vector<double>( 1, 53.999999999999915 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_third_moments,
                                   std::vector<double>( 1, 396.8173383308739 ),
                                   1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_fourth_moments,
                                   std::vector<double>( 1, 2915.9999999999905 ),
                                   1e-14 );

  total_first_moments = estimator_2_base->getTotalDataFirstMoments();
  total_second_moments = estimator_2_base->getTotalDataSecondMoments();
  total_third_moments = estimator_2_base->getTotalDataThirdMoments();
  total_fourth_moments = estimator_2_base->getTotalDataFourthMoments();

  FRENSIE_CHECK_FLOATING_EQUALITY( total_first_moments,
                                   std::vector<double>( 1, 7.348469228349528 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_second_moments,
                                   std::vector<double>( 1, 53.999999999999915 ),
                                   1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_third_moments,
                                   std::vector<double>( 1, 396.8173383308739 ),
                                   1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_fourth_moments,
                                   std::vector<double>( 1, 2915.9999999999905 ),
                                   1e-14 );

  total_first_moments = estimator_3_base->getTotalDataFirstMoments();
  total_second_moments = estimator_3_base->getTotalDataSecondMoments();
  total_third_moments = estimator_3_base->getTotalDataThirdMoments();
  total_fourth_moments = estimator_3_base->getTotalDataFourthMoments();

  FRENSIE_CHECK_FLOATING_EQUALITY( total_first_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_second_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_third_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_fourth_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a partial history contribution can be added to the estimator
FRENSIE_UNIT_TEST( TetMeshTrackLengthFluxEstimator,
                   updateFromGlobalParticleSubtrackEndingEvent_thread_safe )
{
  std::shared_ptr<MonteCarlo::MeshTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier> > estimator_1;
  std::shared_ptr<MonteCarlo::MeshTrackLengthFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier> > estimator_2;
  std::shared_ptr<MonteCarlo::MeshTrackLengthFluxEstimator<MonteCarlo::WeightAndChargeMultiplier> > estimator_3;

  std::shared_ptr<MonteCarlo::Estimator> estimator_1_base, estimator_2_base, estimator_3_base;

  {
    estimator_1.reset( new MonteCarlo::MeshTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier>(
                                                                  0,
                                                                  1.0,
                                                                  tet_mesh ) );

    estimator_1_base = estimator_1;

    estimator_2.reset( new MonteCarlo::MeshTrackLengthFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier>(
                                                                  1,
                                                                  10.0,
                                                                  tet_mesh ) );

    estimator_2_base = estimator_2;

    estimator_3.reset( new MonteCarlo::MeshTrackLengthFluxEstimator<MonteCarlo::WeightAndChargeMultiplier>(
                                                                  2,
                                                                  1.0,
                                                                  tet_mesh ) );

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

    // Set the time bins
    std::vector<double> time_bin_boundaries( 3 );
    time_bin_boundaries[0] = 0.0;
    time_bin_boundaries[1] = 1.0213272871857804e-11;
    time_bin_boundaries[2] = 2.0426545743715607e-11;

    estimator_1_base->setDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION>(
						       time_bin_boundaries );

    // Set the particle types
    std::vector<MonteCarlo::ParticleType> particle_types( 1 );
    particle_types[0] = MonteCarlo::PHOTON;

    estimator_1_base->setParticleTypes( particle_types );
    estimator_2_base->setParticleTypes( particle_types );
    estimator_3_base->setParticleTypes( particle_types );

    // Enable thread support
    estimator_1_base->enableThreadSupport( Utility::OpenMPProperties::getRequestedNumberOfThreads() );
    estimator_2_base->enableThreadSupport( Utility::OpenMPProperties::getRequestedNumberOfThreads() );
    estimator_3_base->enableThreadSupport( Utility::OpenMPProperties::getRequestedNumberOfThreads() );
  }

  // Known contributions and values
  double track_length = 0.6123724356957940;
  double volume = 1.0/6;
  double num_tets = 6.0;

  double start_point_1[3] = { 0.25, 0.0, 0.75 };
  double end_point_1[3] = { 0.75, 0.25, 1.0 };

  double start_point_2[3] = { 0.0, 0.25, 0.75 };
  double end_point_2[3] = { 0.25, 0.75, 1.0 };

  double start_point_3[3] = { 0.75, 0.0, 0.25 };
  double end_point_3[3] = { 1.0, 0.25, 0.75 };

  double start_point_4[3] = { 0.0, 0.75, 0.25 };
  double end_point_4[3] = { 0.25, 1.0, 0.75 };

  double start_point_5[3] = { 0.75, 0.25, 0.0 };
  double end_point_5[3] = { 1.0, 0.75, 0.25 };

  double start_point_6[3] = { 0.25, 0.75, 0.0 };
  double end_point_6[3] = { 0.75, 1.0, 0.25 };

  unsigned threads =
    Utility::OpenMPProperties::getRequestedNumberOfThreads();

  #pragma omp parallel num_threads( threads )
  {
    // bin 0, 2
    MonteCarlo::PhotonState particle( 0 );
    particle.setEnergy( 1.0 );
    particle.setTime( 2.0426545743715623e-11 );
    particle.setWeight( 1.0 );

    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1,
                                                              end_point_1 );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2,
                                                              end_point_2 );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3,
                                                              end_point_3 );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4,
                                                              end_point_4 );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_5,
                                                              end_point_5 );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_6,
                                                              end_point_6 );

    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1,
                                                              end_point_1 );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2,
                                                              end_point_2 );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3,
                                                              end_point_3 );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4,
                                                              end_point_4 );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_5,
                                                              end_point_5 );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_6,
                                                              end_point_6 );

    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1,
                                                              end_point_1 );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2,
                                                              end_point_2 );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3,
                                                              end_point_3 );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4,
                                                              end_point_4 );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_5,
                                                              end_point_5 );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_6,
                                                              end_point_6 );

    // bin 1, 3
    particle.setEnergy( 0.1 );

    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1,
                                                              end_point_1 );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2,
                                                              end_point_2 );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3,
                                                              end_point_3 );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4,
                                                              end_point_4 );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_5,
                                                              end_point_5 );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_6,
                                                              end_point_6 );

    particle.setWeight( 10.0 );

    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1,
                                                              end_point_1 );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2,
                                                              end_point_2 );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3,
                                                              end_point_3 );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4,
                                                              end_point_4 );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_5,
                                                              end_point_5 );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_6,
                                                              end_point_6 );

    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1,
                                                              end_point_1 );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2,
                                                              end_point_2 );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3,
                                                              end_point_3 );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4,
                                                              end_point_4 );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_5,
                                                              end_point_5 );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_6,
                                                              end_point_6 );

    // Commit the contributions
    estimator_1_base->commitHistoryContribution();
    estimator_2_base->commitHistoryContribution();
    estimator_3_base->commitHistoryContribution();
  }

  FRENSIE_CHECK( !estimator_1_base->hasUncommittedHistoryContribution() );
  FRENSIE_CHECK( !estimator_2_base->hasUncommittedHistoryContribution() );
  FRENSIE_CHECK( !estimator_3_base->hasUncommittedHistoryContribution() );

  MonteCarlo::ParticleHistoryObserver::setNumberOfHistories( threads );
  MonteCarlo::ParticleHistoryObserver::setElapsedTime( 1.0 );

  // Check the entity bin data moments
  Utility::ArrayView<const double> entity_bin_first_moments =
    estimator_1_base->getEntityBinDataFirstMoments( 5764607523034234881 );

  Utility::ArrayView<const double> entity_bin_second_moments =
    estimator_1_base->getEntityBinDataSecondMoments( 5764607523034234881 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 4, 3.061862178478970131e-01*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 4, 0.09374999999999985*threads ),
                                   1e-15 );

  entity_bin_first_moments =
    estimator_1_base->getEntityBinDataFirstMoments( 5764607523034234882 );

  entity_bin_second_moments =
    estimator_1_base->getEntityBinDataSecondMoments( 5764607523034234882 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 4, 3.061862178478970131e-01*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 4, 0.09374999999999985*threads ),
                                   1e-15 );

  entity_bin_first_moments =
    estimator_1_base->getEntityBinDataFirstMoments( 5764607523034234883 );

  entity_bin_second_moments =
    estimator_1_base->getEntityBinDataSecondMoments( 5764607523034234883 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 4, 3.061862178478970131e-01*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 4, 0.09374999999999985*threads ),
                                   1e-15 );

  entity_bin_first_moments =
    estimator_1_base->getEntityBinDataFirstMoments( 5764607523034234884 );

  entity_bin_second_moments =
    estimator_1_base->getEntityBinDataSecondMoments( 5764607523034234884 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 4, 3.061862178478970131e-01*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 4, 0.09374999999999985*threads ),
                                   1e-15 );

  entity_bin_first_moments =
    estimator_1_base->getEntityBinDataFirstMoments( 5764607523034234885 );

  entity_bin_second_moments =
    estimator_1_base->getEntityBinDataSecondMoments( 5764607523034234885 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 4, 3.061862178478970131e-01*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 4, 0.09374999999999985*threads ),
                                   1e-15 );

  entity_bin_first_moments =
    estimator_1_base->getEntityBinDataFirstMoments( 5764607523034234886 );

  entity_bin_second_moments =
    estimator_1_base->getEntityBinDataSecondMoments( 5764607523034234886 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 4, 3.061862178478970131e-01*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 4, 0.09374999999999985*threads ),
                                   1e-15 );

  entity_bin_first_moments =
    estimator_2_base->getEntityBinDataFirstMoments( 5764607523034234881 );

  entity_bin_second_moments =
    estimator_2_base->getEntityBinDataSecondMoments( 5764607523034234881 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 2, 0.6123724356957940*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 2, 0.3749999999999994*threads ),
                                   1e-14 );

  entity_bin_first_moments =
    estimator_2_base->getEntityBinDataFirstMoments( 5764607523034234882 );

  entity_bin_second_moments =
    estimator_2_base->getEntityBinDataSecondMoments( 5764607523034234882 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 2, 0.6123724356957940*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 2, 0.3749999999999994*threads ),
                                   1e-14 );

  entity_bin_first_moments =
    estimator_2_base->getEntityBinDataFirstMoments( 5764607523034234883 );

  entity_bin_second_moments =
    estimator_2_base->getEntityBinDataSecondMoments( 5764607523034234883 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 2, 0.6123724356957940*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 2, 0.3749999999999994*threads ),
                                   1e-14 );

  entity_bin_first_moments =
    estimator_2_base->getEntityBinDataFirstMoments( 5764607523034234884 );

  entity_bin_second_moments =
    estimator_2_base->getEntityBinDataSecondMoments( 5764607523034234884 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 2, 0.6123724356957940*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 2, 0.3749999999999994*threads ),
                                   1e-14 );

  entity_bin_first_moments =
    estimator_2_base->getEntityBinDataFirstMoments( 5764607523034234885 );

  entity_bin_second_moments =
    estimator_2_base->getEntityBinDataSecondMoments( 5764607523034234885 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 2, 0.6123724356957940*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 2, 0.3749999999999994*threads ),
                                   1e-14 );

  entity_bin_first_moments =
    estimator_2_base->getEntityBinDataFirstMoments( 5764607523034234886 );

  entity_bin_second_moments =
    estimator_2_base->getEntityBinDataSecondMoments( 5764607523034234886 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 2, 0.6123724356957940*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 2, 0.3749999999999994*threads ),
                                   1e-14 );

  entity_bin_first_moments =
    estimator_3_base->getEntityBinDataFirstMoments( 5764607523034234881 );

  entity_bin_second_moments =
    estimator_3_base->getEntityBinDataSecondMoments( 5764607523034234881 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 2, 0.0 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 2, 0.0 ),
                                   1e-15 );

  entity_bin_first_moments =
    estimator_3_base->getEntityBinDataFirstMoments( 5764607523034234882 );

  entity_bin_second_moments =
    estimator_3_base->getEntityBinDataSecondMoments( 5764607523034234882 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 2, 0.0 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 2, 0.0 ),
                                   1e-15 );

  entity_bin_first_moments =
    estimator_3_base->getEntityBinDataFirstMoments( 5764607523034234883 );

  entity_bin_second_moments =
    estimator_3_base->getEntityBinDataSecondMoments( 5764607523034234883 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 2, 0.0 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 2, 0.0 ),
                                   1e-15 );

  entity_bin_first_moments =
    estimator_3_base->getEntityBinDataFirstMoments( 5764607523034234884 );

  entity_bin_second_moments =
    estimator_3_base->getEntityBinDataSecondMoments( 5764607523034234884 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 2, 0.0 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 2, 0.0 ),
                                   1e-15 );

  entity_bin_first_moments =
    estimator_3_base->getEntityBinDataFirstMoments( 5764607523034234885 );

  entity_bin_second_moments =
    estimator_3_base->getEntityBinDataSecondMoments( 5764607523034234885 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 2, 0.0 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 2, 0.0 ),
                                   1e-15 );

  entity_bin_first_moments =
    estimator_3_base->getEntityBinDataFirstMoments( 5764607523034234886 );

  entity_bin_second_moments =
    estimator_3_base->getEntityBinDataSecondMoments( 5764607523034234886 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 2, 0.0 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 2, 0.0 ),
                                   1e-15 );

  // Check the total bin data moments
  Utility::ArrayView<const double> total_bin_first_moments =
    estimator_1_base->getTotalBinDataFirstMoments();

  Utility::ArrayView<const double> total_bin_second_moments =
    estimator_1_base->getTotalBinDataSecondMoments();

  FRENSIE_CHECK_FLOATING_EQUALITY( total_bin_first_moments,
                                   std::vector<double>( 4, 1.837117307087382*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_bin_second_moments,
                                   std::vector<double>( 4, 3.3749999999999947*threads ),
                                   1e-15 );

  total_bin_first_moments =
    estimator_2_base->getTotalBinDataFirstMoments();

  total_bin_second_moments =
    estimator_2_base->getTotalBinDataSecondMoments();

  FRENSIE_CHECK_FLOATING_EQUALITY( total_bin_first_moments,
                                   std::vector<double>( 2, 3.674234614174764*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_bin_second_moments,
                                   std::vector<double>( 2, 13.499999999999979*threads ),
                                   1e-14 );

  total_bin_first_moments =
    estimator_3_base->getTotalBinDataFirstMoments();

  total_bin_second_moments =
    estimator_3_base->getTotalBinDataSecondMoments();

  FRENSIE_CHECK_FLOATING_EQUALITY( total_bin_first_moments,
                                   std::vector<double>( 2, 0.0),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_bin_second_moments,
                                   std::vector<double>( 2, 0.0),
                                   1e-15 );

  // Check the entity total data moments
  Utility::ArrayView<const double> entity_total_first_moments =
    estimator_1_base->getEntityTotalDataFirstMoments( 5764607523034234881 );

  Utility::ArrayView<const double> entity_total_second_moments =
    estimator_1_base->getEntityTotalDataSecondMoments( 5764607523034234881 );

  Utility::ArrayView<const double> entity_total_third_moments =
    estimator_1_base->getEntityTotalDataThirdMoments( 5764607523034234881 );

  Utility::ArrayView<const double> entity_total_fourth_moments =
    estimator_1_base->getEntityTotalDataFourthMoments( 5764607523034234881 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 1, 1.224744871391588*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 1, 1.4999999999999976*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 1, 1.8371173070873792*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 1, 2.249999999999993*threads ),
                                   1e-15 );

  entity_total_first_moments =
    estimator_1_base->getEntityTotalDataFirstMoments( 5764607523034234882 );

  entity_total_second_moments =
    estimator_1_base->getEntityTotalDataSecondMoments( 5764607523034234882 );

  entity_total_third_moments =
    estimator_1_base->getEntityTotalDataThirdMoments( 5764607523034234882 );

  entity_total_fourth_moments =
    estimator_1_base->getEntityTotalDataFourthMoments( 5764607523034234882 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 1, 1.224744871391588*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 1, 1.4999999999999976*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 1, 1.8371173070873792*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 1, 2.249999999999993*threads ),
                                   1e-15 );

  entity_total_first_moments =
    estimator_1_base->getEntityTotalDataFirstMoments( 5764607523034234883 );

  entity_total_second_moments =
    estimator_1_base->getEntityTotalDataSecondMoments( 5764607523034234883 );

  entity_total_third_moments =
    estimator_1_base->getEntityTotalDataThirdMoments( 5764607523034234883 );

  entity_total_fourth_moments =
    estimator_1_base->getEntityTotalDataFourthMoments( 5764607523034234883 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 1, 1.224744871391588*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 1, 1.4999999999999976*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 1, 1.8371173070873792*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 1, 2.249999999999993*threads ),
                                   1e-15 );

  entity_total_first_moments =
    estimator_1_base->getEntityTotalDataFirstMoments( 5764607523034234884 );

  entity_total_second_moments =
    estimator_1_base->getEntityTotalDataSecondMoments( 5764607523034234884 );

  entity_total_third_moments =
    estimator_1_base->getEntityTotalDataThirdMoments( 5764607523034234884 );

  entity_total_fourth_moments =
    estimator_1_base->getEntityTotalDataFourthMoments( 5764607523034234884 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 1, 1.224744871391588*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 1, 1.4999999999999976*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 1, 1.8371173070873792*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 1, 2.249999999999993*threads ),
                                   1e-15 );

  entity_total_first_moments =
    estimator_1_base->getEntityTotalDataFirstMoments( 5764607523034234885 );

  entity_total_second_moments =
    estimator_1_base->getEntityTotalDataSecondMoments( 5764607523034234885 );

  entity_total_third_moments =
    estimator_1_base->getEntityTotalDataThirdMoments( 5764607523034234885 );

  entity_total_fourth_moments =
    estimator_1_base->getEntityTotalDataFourthMoments( 5764607523034234885 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 1, 1.224744871391588*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 1, 1.4999999999999976*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 1, 1.8371173070873792*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 1, 2.249999999999993*threads ),
                                   1e-15 );

  entity_total_first_moments =
    estimator_1_base->getEntityTotalDataFirstMoments( 5764607523034234886 );

  entity_total_second_moments =
    estimator_1_base->getEntityTotalDataSecondMoments( 5764607523034234886 );

  entity_total_third_moments =
    estimator_1_base->getEntityTotalDataThirdMoments( 5764607523034234886 );

  entity_total_fourth_moments =
    estimator_1_base->getEntityTotalDataFourthMoments( 5764607523034234886 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 1, 1.224744871391588*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 1, 1.4999999999999976*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 1, 1.8371173070873792*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 1, 2.249999999999993*threads ),
                                   1e-15 );

  entity_total_first_moments =
    estimator_2_base->getEntityTotalDataFirstMoments( 5764607523034234881 );

  entity_total_second_moments =
    estimator_2_base->getEntityTotalDataSecondMoments( 5764607523034234881 );

  entity_total_third_moments =
    estimator_2_base->getEntityTotalDataThirdMoments( 5764607523034234881 );

  entity_total_fourth_moments =
    estimator_2_base->getEntityTotalDataFourthMoments( 5764607523034234881 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 1, 1.224744871391588*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 1, 1.4999999999999976*threads ),
                                   1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 1, 1.8371173070873792*threads ),
                                   1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 1, 2.249999999999993*threads ),
                                   1e-14 );

  entity_total_first_moments =
    estimator_2_base->getEntityTotalDataFirstMoments( 5764607523034234882 );

  entity_total_second_moments =
    estimator_2_base->getEntityTotalDataSecondMoments( 5764607523034234882 );

  entity_total_third_moments =
    estimator_2_base->getEntityTotalDataThirdMoments( 5764607523034234882 );

  entity_total_fourth_moments =
    estimator_2_base->getEntityTotalDataFourthMoments( 5764607523034234882 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 1, 1.224744871391588*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 1, 1.4999999999999976*threads ),
                                   1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 1, 1.8371173070873792*threads ),
                                   1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 1, 2.249999999999993*threads ),
                                   1e-14 );

  entity_total_first_moments =
    estimator_2_base->getEntityTotalDataFirstMoments( 5764607523034234883 );

  entity_total_second_moments =
    estimator_2_base->getEntityTotalDataSecondMoments( 5764607523034234883 );

  entity_total_third_moments =
    estimator_2_base->getEntityTotalDataThirdMoments( 5764607523034234883 );

  entity_total_fourth_moments =
    estimator_2_base->getEntityTotalDataFourthMoments( 5764607523034234883 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 1, 1.224744871391588*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 1, 1.4999999999999976*threads ),
                                   1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 1, 1.8371173070873792*threads ),
                                   1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 1, 2.249999999999993*threads ),
                                   1e-14 );

  entity_total_first_moments =
    estimator_2_base->getEntityTotalDataFirstMoments( 5764607523034234884 );

  entity_total_second_moments =
    estimator_2_base->getEntityTotalDataSecondMoments( 5764607523034234884 );

  entity_total_third_moments =
    estimator_2_base->getEntityTotalDataThirdMoments( 5764607523034234884 );

  entity_total_fourth_moments =
    estimator_2_base->getEntityTotalDataFourthMoments( 5764607523034234884 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 1, 1.224744871391588*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 1, 1.4999999999999976*threads ),
                                   1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 1, 1.8371173070873792*threads ),
                                   1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 1, 2.249999999999993*threads ),
                                   1e-14 );

  entity_total_first_moments =
    estimator_2_base->getEntityTotalDataFirstMoments( 5764607523034234885 );

  entity_total_second_moments =
    estimator_2_base->getEntityTotalDataSecondMoments( 5764607523034234885 );

  entity_total_third_moments =
    estimator_2_base->getEntityTotalDataThirdMoments( 5764607523034234885 );

  entity_total_fourth_moments =
    estimator_2_base->getEntityTotalDataFourthMoments( 5764607523034234885 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 1, 1.224744871391588*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 1, 1.4999999999999976*threads ),
                                   1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 1, 1.8371173070873792*threads ),
                                   1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 1, 2.249999999999993*threads ),
                                   1e-14 );

  entity_total_first_moments =
    estimator_2_base->getEntityTotalDataFirstMoments( 5764607523034234886 );

  entity_total_second_moments =
    estimator_2_base->getEntityTotalDataSecondMoments( 5764607523034234886 );

  entity_total_third_moments =
    estimator_2_base->getEntityTotalDataThirdMoments( 5764607523034234886 );

  entity_total_fourth_moments =
    estimator_2_base->getEntityTotalDataFourthMoments( 5764607523034234886 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 1, 1.224744871391588*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 1, 1.4999999999999976*threads ),
                                   1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 1, 1.8371173070873792*threads ),
                                   1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 1, 2.249999999999993*threads ),
                                   1e-14 );

  entity_total_first_moments =
    estimator_3_base->getEntityTotalDataFirstMoments( 5764607523034234881 );

  entity_total_second_moments =
    estimator_3_base->getEntityTotalDataSecondMoments( 5764607523034234881 );

  entity_total_third_moments =
    estimator_3_base->getEntityTotalDataThirdMoments( 5764607523034234881 );

  entity_total_fourth_moments =
    estimator_3_base->getEntityTotalDataFourthMoments( 5764607523034234881 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 1, 0.0),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 1, 0.0),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 1, 0.0),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 1, 0.0),
                                   1e-15 );

  entity_total_first_moments =
    estimator_3_base->getEntityTotalDataFirstMoments( 5764607523034234882 );

  entity_total_second_moments =
    estimator_3_base->getEntityTotalDataSecondMoments( 5764607523034234882 );

  entity_total_third_moments =
    estimator_3_base->getEntityTotalDataThirdMoments( 5764607523034234882 );

  entity_total_fourth_moments =
    estimator_3_base->getEntityTotalDataFourthMoments( 5764607523034234882 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 1, 0.0),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 1, 0.0),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 1, 0.0),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 1, 0.0),
                                   1e-15 );

  entity_total_first_moments =
    estimator_3_base->getEntityTotalDataFirstMoments( 5764607523034234883 );

  entity_total_second_moments =
    estimator_3_base->getEntityTotalDataSecondMoments( 5764607523034234883 );

  entity_total_third_moments =
    estimator_3_base->getEntityTotalDataThirdMoments( 5764607523034234883 );

  entity_total_fourth_moments =
    estimator_3_base->getEntityTotalDataFourthMoments( 5764607523034234883 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 1, 0.0),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 1, 0.0),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 1, 0.0),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 1, 0.0),
                                   1e-15 );

  entity_total_first_moments =
    estimator_3_base->getEntityTotalDataFirstMoments( 5764607523034234884 );

  entity_total_second_moments =
    estimator_3_base->getEntityTotalDataSecondMoments( 5764607523034234884 );

  entity_total_third_moments =
    estimator_3_base->getEntityTotalDataThirdMoments( 5764607523034234884 );

  entity_total_fourth_moments =
    estimator_3_base->getEntityTotalDataFourthMoments( 5764607523034234884 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 1, 0.0),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 1, 0.0),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 1, 0.0),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 1, 0.0),
                                   1e-15 );

  entity_total_first_moments =
    estimator_3_base->getEntityTotalDataFirstMoments( 5764607523034234885 );

  entity_total_second_moments =
    estimator_3_base->getEntityTotalDataSecondMoments( 5764607523034234885 );

  entity_total_third_moments =
    estimator_3_base->getEntityTotalDataThirdMoments( 5764607523034234885 );

  entity_total_fourth_moments =
    estimator_3_base->getEntityTotalDataFourthMoments( 5764607523034234885 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 1, 0.0),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 1, 0.0),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 1, 0.0),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 1, 0.0),
                                   1e-15 );

  entity_total_first_moments =
    estimator_3_base->getEntityTotalDataFirstMoments( 5764607523034234886 );

  entity_total_second_moments =
    estimator_3_base->getEntityTotalDataSecondMoments( 5764607523034234886 );

  entity_total_third_moments =
    estimator_3_base->getEntityTotalDataThirdMoments( 5764607523034234886 );

  entity_total_fourth_moments =
    estimator_3_base->getEntityTotalDataFourthMoments( 5764607523034234886 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 1, 0.0),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 1, 0.0),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 1, 0.0),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 1, 0.0),
                                   1e-15 );

  // Check the total data moments
  Utility::ArrayView<const double> total_first_moments =
    estimator_1_base->getTotalDataFirstMoments();

  Utility::ArrayView<const double> total_second_moments =
    estimator_1_base->getTotalDataSecondMoments();

  Utility::ArrayView<const double> total_third_moments =
    estimator_1_base->getTotalDataThirdMoments();

  Utility::ArrayView<const double> total_fourth_moments =
    estimator_1_base->getTotalDataFourthMoments();

  FRENSIE_CHECK_FLOATING_EQUALITY( total_first_moments,
                                   std::vector<double>( 1, 7.348469228349528*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_second_moments,
                                   std::vector<double>( 1, 53.999999999999915*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_third_moments,
                                   std::vector<double>( 1, 396.8173383308739*threads ),
                                   1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_fourth_moments,
                                   std::vector<double>( 1, 2915.9999999999905*threads ),
                                   1e-14 );

  total_first_moments = estimator_2_base->getTotalDataFirstMoments();
  total_second_moments = estimator_2_base->getTotalDataSecondMoments();
  total_third_moments = estimator_2_base->getTotalDataThirdMoments();
  total_fourth_moments = estimator_2_base->getTotalDataFourthMoments();

  FRENSIE_CHECK_FLOATING_EQUALITY( total_first_moments,
                                   std::vector<double>( 1, 7.348469228349528*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_second_moments,
                                   std::vector<double>( 1, 53.999999999999915*threads ),
                                   1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_third_moments,
                                   std::vector<double>( 1, 396.8173383308739*threads ),
                                   1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_fourth_moments,
                                   std::vector<double>( 1, 2915.9999999999905*threads ),
                                   1e-14 );

  total_first_moments = estimator_3_base->getTotalDataFirstMoments();
  total_second_moments = estimator_3_base->getTotalDataSecondMoments();
  total_third_moments = estimator_3_base->getTotalDataThirdMoments();
  total_fourth_moments = estimator_3_base->getTotalDataFourthMoments();

  FRENSIE_CHECK_FLOATING_EQUALITY( total_first_moments,
                                   std::vector<double>( 1, 0.0 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_second_moments,
                                   std::vector<double>( 1, 0.0 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_third_moments,
                                   std::vector<double>( 1, 0.0 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_fourth_moments,
                                   std::vector<double>( 1, 0.0 ),
                                   1e-15 );
}

// //---------------------------------------------------------------------------//
// // Make sure that the data is being calculated correctly
// TEUCHOS_UNIT_TEST( TetMeshTrackLengthFluxEstimator,
//                    updateFromGlobalParticleSubtrackEndingEvent )
// {
//   Teuchos::RCP<MonteCarlo::TetMeshTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier> > estimator;
//   Teuchos::RCP<MonteCarlo::Estimator> estimator_base;

//   double multiplier = 4.0;

//   {
//     estimator.reset(
//     new MonteCarlo::TetMeshTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier>(
//                          0u,
//                          multiplier,
//                          test_input_mesh_file_name,
//                          "unit_cube_output.vtk" ) );

//     // Assign energy bins
//     Teuchos::Array<double> energy_bin_boundaries( 3 );
//     energy_bin_boundaries[0] = 0.0;
//     energy_bin_boundaries[1] = 0.1;
//     energy_bin_boundaries[2] = 1.0;

//     estimator->setBinBoundaries<MonteCarlo::ENERGY_DIMENSION>(
//                              energy_bin_boundaries );

//     // Set the particle types
//     Teuchos::Array<MonteCarlo::ParticleType> particle_types ( 1 );
//     particle_types[0] = MonteCarlo::PHOTON;

//     estimator->setParticleTypes( particle_types );

//     estimator_base = estimator;
//   }

//   // Known contributions and values
//   double track_length = 0.6123724356957940;
//   double volume = 1.0/6.0;
//   double num_tets = 6.0;

//   // Start and end point on mesh element surfaces
//   double start_point_1[3] = { 0.25, 0.0, 0.75 };
//   double end_point_1[3] = { 0.75, 0.25, 1.0 };
//   double direction_1[3] = { 0.8164965809277261,
// 			    0.4082482904638631,
// 			    0.4082482904638631 };

//   // Start point outside of mesh, end point on mesh element surface
//   // start intersection { 0.0, 0.25, 0.75 };
//   double start_point_2[3] = { -0.4082482904638631,
// 			      -0.5664965809277261,
//                               0.3417517095361369 };
//   double end_point_2[3] = { 0.25, 0.75, 1.0 };
//   double direction_2[3] = { 0.4082482904638631,
// 			    0.8164965809277261,
// 			    0.4082482904638631 };

//   // Start point on mesh element surface, end point outside of surface
//   // end intersection { 1.0, 0.25, 0.75 }
//   double start_point_3[3] = { 0.75, 0.0, 0.25 };
//   double end_point_3[3] = { 1.4082482904638631,
// 			    0.6582482904638631,
// 			    1.5664965809277263 };
//   double direction_3[3] = { 0.4082482904638631,
// 			    0.4082482904638631,
// 			    0.8164965809277261 };

//   // Start point and end point outside of surface
//   // start intersection { 0.0, 0.75, 0.25 }
//   // end intersection { 0.25, 1.0, 0.75 }
//   double start_point_4[3] = { -0.4082482904638631,
// 			      0.3417517095361369,
//                               -0.5664965809277261 };
//   double end_point_4[3] = { 0.6582482904638631,
// 			    1.4082482904638631,
// 			    1.5664965809277263 };
//   double direction_4[3] = { 0.4082482904638631,
// 			    0.4082482904638631,
// 			    0.8164965809277261 };

//   // Start point outside of mesh, end point inside of mesh element
//   // start intersection { 0.75, 0.25, 0.0 }
//   double start_point_5_a[3] = { 0.3417517095361369,
// 			      -0.5664965809277261,
// 			      -0.4082482904638631 };
//   double end_point_5_a[3] = { 0.875, 0.5, 0.125 };
//   double direction_5[3] = { 0.4082482904638631,
// 			    0.8164965809277261,
// 			    0.4082482904638631 };

//   // Start point inside of mesh, end point outside of mesh
//   // end intersection { 1.0, 0.75, 0.25 }
//   double start_point_5_b[3] = { 0.875, 0.5, 0.125 };
//   double end_point_5_b[3] = { 1.4082482904638631,
// 			      1.5664965809277263,
// 			      0.6582482904638631 };

//   // Start point on mesh element surface, end point in mesh element
//   // start intersection { 0.25, 0.75, 0.0 }
//   double start_point_6_a[3] = { 0.25, 0.75, 0.0 };
//   double end_point_6_a[3] = { 0.41666666666666663,
// 			      0.8333333333333334,
// 			      0.08333333333333333 };
//   double direction_6[3] = { 0.8164965809277261,
// 			    0.4082482904638631,
// 			    0.4082482904638631 };

//   // Start point in mesh element, end point in mesh element
//   double start_point_6_b[3] = { 0.41666666666666663,
// 				0.8333333333333334,
// 				0.08333333333333333 };
//   double end_point_6_b[3] = { 0.5833333333333333,
// 			      0.9166666666666666,
// 			      0.16666666666666666 };

//   // Start point in mesh element, end point on mesh element surface
//   // end intersection { 0.75, 1.0, 0.25 }
//   double start_point_6_c[3] = { 0.5833333333333333,
// 				0.9166666666666666,
// 				0.16666666666666666 };
//   double end_point_6_c[3] = { 0.75, 1.0, 0.25 };

//   // bin 0
//   MonteCarlo::PhotonState particle( 0ull );
//   double weight = 0.5;
//   particle.setWeight( weight );
//   particle.setEnergy( 1.0 );
//   particle.setDirection( direction_1 );

//   TEST_ASSERT( !estimator->hasUncommittedHistoryContribution() );

//   estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
//                                                           start_point_1,
//                                                           end_point_1 );

//   particle.setDirection( direction_2 );
//   estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
//                                                           start_point_2,
//                                                           end_point_2 );

//   particle.setDirection( direction_3 );
//   estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
//                                                           start_point_3,
//                                                           end_point_3 );

//   particle.setDirection( direction_4 );
//   estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
//                                                           start_point_4,
//                                                           end_point_4 );

//   particle.setDirection( direction_5 );
//   estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
//                                                           start_point_5_a,
//                                                           end_point_5_a );
//   estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
//                                                           start_point_5_b,
//                                                           end_point_5_b );


//   particle.setDirection( direction_6 );
//   estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
//                                                           start_point_6_a,
//                                                           end_point_6_a );
//   estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
//                                                           start_point_6_b,
//                                                           end_point_6_b );
//   estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
//                                                           start_point_6_c,
//                                                           end_point_6_c );

//   TEST_ASSERT( estimator->hasUncommittedHistoryContribution() );

//   // bin 1
//   particle.setEnergy( 0.1 );

//   particle.setDirection( direction_1 );
//   estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
//                                                           start_point_1,
//                                                           end_point_1 );

//   particle.setDirection( direction_2 );
//   estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
//                                                           start_point_2,
//                                                           end_point_2 );

//   particle.setDirection( direction_3 );
//   estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
//                                                           start_point_3,
//                                                           end_point_3 );

//   particle.setDirection( direction_4 );
//   estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
//                                                           start_point_4,
//                                                           end_point_4 );

//   particle.setDirection( direction_5 );
//   estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
//                                                           start_point_5_a,
//                                                           end_point_5_a );
//   estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
//                                                           start_point_5_b,
//                                                           end_point_5_b );

//   particle.setDirection( direction_6 );
//   estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
//                                                           start_point_6_a,
//                                                           end_point_6_a );
//   estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
//                                                           start_point_6_b,
//                                                           end_point_6_b );
//   estimator->updateFromGlobalParticleSubtrackEndingEvent( particle,
//                                                           start_point_6_c,
//                                                           end_point_6_c );

//   // Commit history contributions
//   estimator_base->commitHistoryContribution();

//   TEST_ASSERT( !estimator->hasUncommittedHistoryContribution() );

//   MonteCarlo::Estimator::setNumberOfHistories( 1.0 );
//   MonteCarlo::Estimator::setEndTime( 1.0 );

//   // Initialize the HDF5 file
//   std::shared_ptr<Utility::HDF5FileHandler>
//     hdf5_file( new Utility::HDF5FileHandler );
//   hdf5_file->openHDF5FileAndOverwrite( "test_tet_mesh_track_length_flux_estimator.h5" );

//   estimator->exportData( hdf5_file, true );

//   // Create an estimator hdf5 file handler
//   MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler( hdf5_file );

//   // Get the tet EntityHandles for use in data retrieval
//   const moab::Range all_tet_elements = estimator->getAllTetElements();

//   // Retrieve the raw bin data for each tet
//   moab::Range::const_iterator tet = all_tet_elements.begin();

//   Teuchos::Array<Utility::Pair<double,double> >

//       raw_bin_data( 2, Utility::Pair<double,double>(
//                                    track_length*weight,
//                                    track_length*track_length*weight*weight ) ),
//       raw_bin_data_copy;

//   hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
//                              0u, *tet, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
//                                         raw_bin_data_copy,
//                                         1e-12 );

//   ++tet;

//   hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
//                              0u, *tet, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
//                                         raw_bin_data_copy,
//                                         1e-12 );

//   ++tet;

//   hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
//                              0u, *tet, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
//                                         raw_bin_data_copy,
//                                         1e-12 );

//   ++tet;

//   hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
//                              0u, *tet, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
//                                         raw_bin_data_copy,
//                                         1e-12 );

//   ++tet;

//   hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
//                              0u, *tet, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
//                                         raw_bin_data_copy,
//                                         1e-12 );

//   ++tet;

//   hdf5_file_handler.getRawEstimatorEntityBinData<moab::EntityHandle>(
//                              0u, *tet, raw_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_bin_data,
//                                         raw_bin_data_copy,
//                                         1e-12 );

//   // Retrieve the processed bin data for each entity
//   tet = all_tet_elements.begin();

//   Teuchos::Array<Utility::Pair<double,double> >
//     processed_bin_data( 2, Utility::Pair<double,double>(
//                                 multiplier*track_length*weight/volume, 0.0 ) ),
//     processed_bin_data_copy;

//   hdf5_file_handler.getProcessedEstimatorEntityBinData<moab::EntityHandle>(
//                              0u, *tet, processed_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_bin_data,
//                                         processed_bin_data_copy,
//                                         1e-12 );

//   ++tet;

//   hdf5_file_handler.getProcessedEstimatorEntityBinData<moab::EntityHandle>(
//                              0u, *tet, processed_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_bin_data,
//                                         processed_bin_data_copy,
//                                         1e-12 );

//   ++tet;

//   hdf5_file_handler.getProcessedEstimatorEntityBinData<moab::EntityHandle>(
//                              0u, *tet, processed_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_bin_data,
//                                         processed_bin_data_copy,
//                                         1e-12 );

//   ++tet;

//   hdf5_file_handler.getProcessedEstimatorEntityBinData<moab::EntityHandle>(
//                              0u, *tet, processed_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_bin_data,
//                                         processed_bin_data_copy,
//                                         1e-12 );

//   ++tet;

//   hdf5_file_handler.getProcessedEstimatorEntityBinData<moab::EntityHandle>(
//                              0u, *tet, processed_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_bin_data,
//                                         processed_bin_data_copy,
//                                         1e-12 );

//   ++tet;

//   hdf5_file_handler.getProcessedEstimatorEntityBinData<moab::EntityHandle>(
//                              0u, *tet, processed_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_bin_data,
//                                         processed_bin_data_copy,
//                                         1e-12 );

//   // Retrieve the raw total bin data
//   tet = all_tet_elements.begin();

//   Teuchos::Array<Utility::Pair<double,double> >
//     raw_total_bin_data( 2, Utility::Pair<double,double>(
//                          num_tets*track_length*weight,
//                          num_tets*num_tets*track_length*track_length*weight*weight ) ),
//     raw_total_bin_data_copy;

//   hdf5_file_handler.getRawEstimatorTotalBinData(
//                              0u, raw_total_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_bin_data,
//                                         raw_total_bin_data_copy,
//                                         1e-12 );

//   ++tet;

//   hdf5_file_handler.getRawEstimatorTotalBinData(
//                              0u, raw_total_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_bin_data,
//                                         raw_total_bin_data_copy,
//                                         1e-12 );

//   ++tet;

//   hdf5_file_handler.getRawEstimatorTotalBinData(
//                              0u, raw_total_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_bin_data,
//                                         raw_total_bin_data_copy,
//                                         1e-12 );

//   ++tet;

//   hdf5_file_handler.getRawEstimatorTotalBinData(
//                              0u, raw_total_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_bin_data,
//                                         raw_total_bin_data_copy,
//                                         1e-12 );

//   ++tet;

//   hdf5_file_handler.getRawEstimatorTotalBinData(
//                              0u, raw_total_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_bin_data,
//                                         raw_total_bin_data_copy,
//                                         1e-12 );

//   ++tet;

//   hdf5_file_handler.getRawEstimatorTotalBinData(
//                              0u, raw_total_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_bin_data,
//                                         raw_total_bin_data_copy,
//                                         1e-12 );

//   // Retrieve the processed total bin data
//   tet = all_tet_elements.begin();

//   Teuchos::Array<Utility::Pair<double,double> >
//     processed_total_bin_data( 2, Utility::Pair<double,double>(
//                          multiplier*num_tets*track_length*weight,
//                          0.0 ) ),
//     processed_total_bin_data_copy;

//   hdf5_file_handler.getProcessedEstimatorTotalBinData(
//                              0u, processed_total_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_bin_data,
//                                         processed_total_bin_data_copy,
//                                         1e-12 );

//   ++tet;

//   hdf5_file_handler.getProcessedEstimatorTotalBinData(
//                              0u, processed_total_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_bin_data,
//                                         processed_total_bin_data_copy,
//                                         1e-12 );

//   ++tet;

//   hdf5_file_handler.getProcessedEstimatorTotalBinData(
//                              0u, processed_total_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_bin_data,
//                                         processed_total_bin_data_copy,
//                                         1e-12 );

//   ++tet;

//   hdf5_file_handler.getProcessedEstimatorTotalBinData(
//                              0u, processed_total_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_bin_data,
//                                         processed_total_bin_data_copy,
//                                         1e-12 );

//   ++tet;

//   hdf5_file_handler.getProcessedEstimatorTotalBinData(
//                              0u, processed_total_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_bin_data,
//                                         processed_total_bin_data_copy,
//                                         1e-12 );

//   ++tet;

//   hdf5_file_handler.getProcessedEstimatorTotalBinData(
//                              0u, processed_total_bin_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_bin_data,
//                                         processed_total_bin_data_copy,
//                                         1e-12 );

//   // Retrieve the raw estimator total data for each entity
//   tet = all_tet_elements.begin();

//   Utility::Quad<double,double,double,double>

//     raw_moments( track_length*weight*2.0,
//                  track_length*track_length*weight*weight*4.0,
//                  track_length*track_length*track_length*weight*weight*weight*8.0,
//                  track_length*track_length*track_length*track_length*weight*weight*weight*weight*16.0 );

//   Teuchos::Array<Utility::Quad<double,double,double,double> >
//     raw_total_data( 1, raw_moments ),
//     raw_total_data_copy;

//   hdf5_file_handler.getRawEstimatorEntityTotalData<moab::EntityHandle>(
//                              0u, *tet, raw_total_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data,
//                                         raw_total_data_copy,
//                                         1e-12 );

//   ++tet;

//   hdf5_file_handler.getRawEstimatorEntityTotalData<moab::EntityHandle>(
//                              0u, *tet, raw_total_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data,
//                                         raw_total_data_copy,
//                                         1e-12 );

//   ++tet;

//   hdf5_file_handler.getRawEstimatorEntityTotalData<moab::EntityHandle>(
//                              0u, *tet, raw_total_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data,
//                                         raw_total_data_copy,
//                                         1e-12 );

//   ++tet;


//   hdf5_file_handler.getRawEstimatorEntityTotalData<moab::EntityHandle>(
//                              0u, *tet, raw_total_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data,
//                                         raw_total_data_copy,
//                                         1e-12 );

//   ++tet;

//   hdf5_file_handler.getRawEstimatorEntityTotalData<moab::EntityHandle>(
//                              0u, *tet, raw_total_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data,
//                                         raw_total_data_copy,
//                                         1e-12 );

//   ++tet;

//   hdf5_file_handler.getRawEstimatorEntityTotalData<moab::EntityHandle>(
//                              0u, *tet, raw_total_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data,
//                                         raw_total_data_copy,
//                                         1e-12 );

//   // Retrieve the processed estimator total data for each entity
//   tet = all_tet_elements.begin();

//   Utility::Quad<double,double,double,double>
//     processed_moments( multiplier*track_length*weight*2.0/volume,
//                        0.0,
//                        0.0,
//                        0.0 );

//   Teuchos::Array<Utility::Quad<double,double,double,double> >
//     processed_total_data( 1, processed_moments ),
//     processed_total_data_copy;

//   hdf5_file_handler.getProcessedEstimatorEntityTotalData<moab::EntityHandle>(
//                              0u, *tet, processed_total_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_data,
//                                         processed_total_data_copy,
//                                         1e-12 );

//   ++tet;

//   hdf5_file_handler.getProcessedEstimatorEntityTotalData<moab::EntityHandle>(
//                              0u, *tet, processed_total_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_data,
//                                         processed_total_data_copy,
//                                         1e-12 );

//   ++tet;

//   hdf5_file_handler.getProcessedEstimatorEntityTotalData<moab::EntityHandle>(
//                              0u, *tet, processed_total_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_data,
//                                         processed_total_data_copy,
//                                         1e-12 );

//   ++tet;

//   hdf5_file_handler.getProcessedEstimatorEntityTotalData<moab::EntityHandle>(
//                              0u, *tet, processed_total_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_data,
//                                         processed_total_data_copy,
//                                         1e-12 );

//   ++tet;

//   hdf5_file_handler.getProcessedEstimatorEntityTotalData<moab::EntityHandle>(
//                              0u, *tet, processed_total_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_data,
//                                         processed_total_data_copy,
//                                         1e-12 );

//   ++tet;

//   hdf5_file_handler.getProcessedEstimatorEntityTotalData<moab::EntityHandle>(
//                              0u, *tet, processed_total_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_data,
//                                         processed_total_data_copy,
//                                         1e-12 );

//   // Retrieve the raw estimator total data
//   raw_total_data[0]( num_tets*track_length*weight*2.0,
//                      num_tets*num_tets*track_length*track_length*weight*weight*4.0,
//                      num_tets*num_tets*num_tets*track_length*track_length*track_length*weight*weight*weight*8.0,
//                      num_tets*num_tets*num_tets*num_tets*track_length*track_length*track_length*track_length*weight*weight*weight*weight*16.0 );


//   hdf5_file_handler.getRawEstimatorTotalData( 0u, raw_total_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( raw_total_data,
//                                         raw_total_data_copy,
//                                         1e-12 );

//   // Retrieve the processed estimator total data
//   processed_total_data[0]( num_tets*track_length*weight*multiplier*2.0,
//                            0.0,
//                            0.0,
//                            0.0 );

//   hdf5_file_handler.getProcessedEstimatorTotalData( 0u,
//                                                 processed_total_data_copy );

//   UTILITY_TEST_COMPARE_FLOATING_ARRAYS( processed_total_data,
//                                         processed_total_data_copy,
//                                         1e-12 );
// }

//---------------------------------------------------------------------------//
// Check that an estimator can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( HexMeshTrackLengthFluxEstimator,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_tet_mesh_track_length_flux_estimator" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::shared_ptr<MonteCarlo::MeshTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier> > estimator_1;
    std::shared_ptr<MonteCarlo::MeshTrackLengthFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier> > estimator_2;
    std::shared_ptr<MonteCarlo::MeshTrackLengthFluxEstimator<MonteCarlo::WeightAndChargeMultiplier> > estimator_3;

    std::shared_ptr<MonteCarlo::Estimator> estimator_1_base, estimator_2_base, estimator_3_base;

    {
      estimator_1.reset( new MonteCarlo::MeshTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier>(
                                                                  0,
                                                                  1.0,
                                                                  tet_mesh ) );

      estimator_1_base = estimator_1;

      estimator_2.reset( new MonteCarlo::MeshTrackLengthFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier>(
                                                                  1,
                                                                  10.0,
                                                                  tet_mesh ) );

      estimator_2_base = estimator_2;

      estimator_3.reset( new MonteCarlo::MeshTrackLengthFluxEstimator<MonteCarlo::WeightAndChargeMultiplier>(
                                                                  2,
                                                                  1.0,
                                                                  tet_mesh ) );

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

      // Set the time bins
      std::vector<double> time_bin_boundaries( 3 );
      time_bin_boundaries[0] = 0.0;
      time_bin_boundaries[1] = 1.0213272871857804e-11;
      time_bin_boundaries[2] = 2.0426545743715607e-11;

      estimator_1_base->setDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION>(
						       time_bin_boundaries );

      // Set the particle types
      std::vector<MonteCarlo::ParticleType> particle_types( 1 );
      particle_types[0] = MonteCarlo::PHOTON;

      estimator_1_base->setParticleTypes( particle_types );
      estimator_2_base->setParticleTypes( particle_types );
      estimator_3_base->setParticleTypes( particle_types );
    }

    double start_point_1[3] = { 0.25, 0.0, 0.75 };
    double end_point_1[3] = { 0.75, 0.25, 1.0 };

    double start_point_2[3] = { 0.0, 0.25, 0.75 };
    double end_point_2[3] = { 0.25, 0.75, 1.0 };

    double start_point_3[3] = { 0.75, 0.0, 0.25 };
    double end_point_3[3] = { 1.0, 0.25, 0.75 };

    double start_point_4[3] = { 0.0, 0.75, 0.25 };
    double end_point_4[3] = { 0.25, 1.0, 0.75 };

    double start_point_5[3] = { 0.75, 0.25, 0.0 };
    double end_point_5[3] = { 1.0, 0.75, 0.25 };

    double start_point_6[3] = { 0.25, 0.75, 0.0 };
    double end_point_6[3] = { 0.75, 1.0, 0.25 };

    // bin 0, 2
    MonteCarlo::PhotonState particle( 0 );
    particle.setEnergy( 1.0 );
    particle.setTime( 2.0426545743715623e-11 );
    particle.setWeight( 1.0 );

    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1,
                                                              end_point_1 );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2,
                                                              end_point_2 );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3,
                                                              end_point_3 );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4,
                                                              end_point_4 );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_5,
                                                              end_point_5 );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_6,
                                                              end_point_6 );

    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1,
                                                              end_point_1 );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2,
                                                              end_point_2 );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3,
                                                              end_point_3 );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4,
                                                              end_point_4 );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_5,
                                                              end_point_5 );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_6,
                                                              end_point_6 );

    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1,
                                                              end_point_1 );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2,
                                                              end_point_2 );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3,
                                                              end_point_3 );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4,
                                                              end_point_4 );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_5,
                                                              end_point_5 );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_6,
                                                              end_point_6 );

    // bin 1, 3
    particle.setEnergy( 0.1 );

    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1,
                                                              end_point_1 );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2,
                                                              end_point_2 );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3,
                                                              end_point_3 );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4,
                                                              end_point_4 );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_5,
                                                              end_point_5 );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_6,
                                                              end_point_6 );

    particle.setWeight( 10.0 );

    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1,
                                                              end_point_1 );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2,
                                                              end_point_2 );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3,
                                                              end_point_3 );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4,
                                                              end_point_4 );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_5,
                                                              end_point_5 );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_6,
                                                              end_point_6 );

    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1,
                                                              end_point_1 );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2,
                                                              end_point_2 );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3,
                                                              end_point_3 );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4,
                                                              end_point_4 );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_5,
                                                              end_point_5 );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_6,
                                                              end_point_6 );

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

  std::shared_ptr<MonteCarlo::MeshTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier> > estimator_1;
  std::shared_ptr<MonteCarlo::MeshTrackLengthFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier> > estimator_2;
  std::shared_ptr<MonteCarlo::MeshTrackLengthFluxEstimator<MonteCarlo::WeightAndChargeMultiplier> > estimator_3;

  std::shared_ptr<MonteCarlo::Estimator> estimator_1_base, estimator_2_base, estimator_3_base;

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
    FRENSIE_CHECK_EQUAL( estimator_1_base->getNumberOfBins(), 4 );
    FRENSIE_CHECK_EQUAL( estimator_1_base->getNumberOfBins( MonteCarlo::OBSERVER_ENERGY_DIMENSION ), 2 );
    FRENSIE_CHECK_EQUAL( estimator_1_base->getNumberOfBins( MonteCarlo::OBSERVER_TIME_DIMENSION ), 2 );
    FRENSIE_CHECK_EQUAL( estimator_1_base->getNumberOfResponseFunctions(), 1 );
    FRENSIE_CHECK_EQUAL( estimator_1_base->getParticleTypes().size(), 1 );
    FRENSIE_CHECK( estimator_1_base->getParticleTypes().find( MonteCarlo::PHOTON ) != estimator_1_base->getParticleTypes().end() );

    std::set<uint64_t> entity_ids;

    estimator_1->getEntityIds( entity_ids );

    FRENSIE_CHECK_EQUAL( entity_ids.size(), 6 );
    FRENSIE_CHECK( entity_ids.find( 5764607523034234881 ) != entity_ids.end() );
    FRENSIE_CHECK( entity_ids.find( 5764607523034234882 ) != entity_ids.end() );
    FRENSIE_CHECK( entity_ids.find( 5764607523034234883 ) != entity_ids.end() );
    FRENSIE_CHECK( entity_ids.find( 5764607523034234884 ) != entity_ids.end() );
    FRENSIE_CHECK( entity_ids.find( 5764607523034234885 ) != entity_ids.end() );
    FRENSIE_CHECK( entity_ids.find( 5764607523034234886 ) != entity_ids.end() );

    FRENSIE_CHECK_EQUAL( estimator_1_base->getEntityNormConstant( 5764607523034234881 ), 1.0/6 );
    FRENSIE_CHECK_EQUAL( estimator_1_base->getEntityNormConstant( 5764607523034234882 ), 1.0/6 );
    FRENSIE_CHECK_EQUAL( estimator_1_base->getEntityNormConstant( 5764607523034234883 ), 1.0/6 );
    FRENSIE_CHECK_EQUAL( estimator_1_base->getEntityNormConstant( 5764607523034234884 ), 1.0/6 );
    FRENSIE_CHECK_EQUAL( estimator_1_base->getEntityNormConstant( 5764607523034234885 ), 1.0/6 );
    FRENSIE_CHECK_EQUAL( estimator_1_base->getEntityNormConstant( 5764607523034234886 ), 1.0/6 );
    FRENSIE_CHECK_FLOATING_EQUALITY( estimator_1_base->getTotalNormConstant(),
                                     1.0,
                                     1e-15 );

    // Check the entity bin data moments
    Utility::ArrayView<const double> entity_bin_first_moments =
      estimator_1_base->getEntityBinDataFirstMoments( 5764607523034234881 );

    Utility::ArrayView<const double> entity_bin_second_moments =
      estimator_1_base->getEntityBinDataSecondMoments( 5764607523034234881 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 4, 3.061862178478970131e-01 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                     std::vector<double>( 4, 0.09374999999999985 ),
                                     1e-15 );

    entity_bin_first_moments =
      estimator_1_base->getEntityBinDataFirstMoments( 5764607523034234882 );

    entity_bin_second_moments =
      estimator_1_base->getEntityBinDataSecondMoments( 5764607523034234882 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 4, 3.061862178478970131e-01 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                     std::vector<double>( 4, 0.09374999999999985 ),
                                     1e-15 );

    entity_bin_first_moments =
      estimator_1_base->getEntityBinDataFirstMoments( 5764607523034234883 );

    entity_bin_second_moments =
      estimator_1_base->getEntityBinDataSecondMoments( 5764607523034234883 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 4, 3.061862178478970131e-01 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                     std::vector<double>( 4, 0.09374999999999985 ),
                                     1e-15 );

    entity_bin_first_moments =
      estimator_1_base->getEntityBinDataFirstMoments( 5764607523034234884 );

    entity_bin_second_moments =
      estimator_1_base->getEntityBinDataSecondMoments( 5764607523034234884 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 4, 3.061862178478970131e-01 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                     std::vector<double>( 4, 0.09374999999999985 ),
                                     1e-15 );

    entity_bin_first_moments =
      estimator_1_base->getEntityBinDataFirstMoments( 5764607523034234885 );

    entity_bin_second_moments =
      estimator_1_base->getEntityBinDataSecondMoments( 5764607523034234885 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 4, 3.061862178478970131e-01 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                     std::vector<double>( 4, 0.09374999999999985 ),
                                     1e-15 );

    entity_bin_first_moments =
      estimator_1_base->getEntityBinDataFirstMoments( 5764607523034234886 );

    entity_bin_second_moments =
      estimator_1_base->getEntityBinDataSecondMoments( 5764607523034234886 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 4, 3.061862178478970131e-01 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                     std::vector<double>( 4, 0.09374999999999985 ),
                                     1e-15 );

    // Check the total bin data moments
    Utility::ArrayView<const double> total_bin_first_moments =
      estimator_1_base->getTotalBinDataFirstMoments();

    Utility::ArrayView<const double> total_bin_second_moments =
      estimator_1_base->getTotalBinDataSecondMoments();

    FRENSIE_CHECK_FLOATING_EQUALITY( total_bin_first_moments,
                                     std::vector<double>( 4, 1.837117307087382 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( total_bin_second_moments,
                                     std::vector<double>( 4, 3.3749999999999947 ),
                                     1e-15 );

    // Check the entity total data moments
    Utility::ArrayView<const double> entity_total_first_moments =
      estimator_1_base->getEntityTotalDataFirstMoments( 5764607523034234881 );

    Utility::ArrayView<const double> entity_total_second_moments =
      estimator_1_base->getEntityTotalDataSecondMoments( 5764607523034234881 );

    Utility::ArrayView<const double> entity_total_third_moments =
      estimator_1_base->getEntityTotalDataThirdMoments( 5764607523034234881 );

    Utility::ArrayView<const double> entity_total_fourth_moments =
      estimator_1_base->getEntityTotalDataFourthMoments( 5764607523034234881 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                     std::vector<double>( 1, 1.224744871391588 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                     std::vector<double>( 1, 1.4999999999999976 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                     std::vector<double>( 1, 1.8371173070873792 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                     std::vector<double>( 1, 2.249999999999993 ),
                                     1e-15 );

    entity_total_first_moments =
      estimator_1_base->getEntityTotalDataFirstMoments( 5764607523034234882 );

    entity_total_second_moments =
      estimator_1_base->getEntityTotalDataSecondMoments( 5764607523034234882 );

    entity_total_third_moments =
      estimator_1_base->getEntityTotalDataThirdMoments( 5764607523034234882 );

    entity_total_fourth_moments =
      estimator_1_base->getEntityTotalDataFourthMoments( 5764607523034234882 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                     std::vector<double>( 1, 1.224744871391588 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                     std::vector<double>( 1, 1.4999999999999976 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                     std::vector<double>( 1, 1.8371173070873792 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                     std::vector<double>( 1, 2.249999999999993 ),
                                     1e-15 );

    entity_total_first_moments =
      estimator_1_base->getEntityTotalDataFirstMoments( 5764607523034234883 );

    entity_total_second_moments =
      estimator_1_base->getEntityTotalDataSecondMoments( 5764607523034234883 );

    entity_total_third_moments =
      estimator_1_base->getEntityTotalDataThirdMoments( 5764607523034234883 );

    entity_total_fourth_moments =
      estimator_1_base->getEntityTotalDataFourthMoments( 5764607523034234883 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                     std::vector<double>( 1, 1.224744871391588 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                     std::vector<double>( 1, 1.4999999999999976 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                     std::vector<double>( 1, 1.8371173070873792 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                     std::vector<double>( 1, 2.249999999999993 ),
                                     1e-15 );

    entity_total_first_moments =
      estimator_1_base->getEntityTotalDataFirstMoments( 5764607523034234884 );

    entity_total_second_moments =
      estimator_1_base->getEntityTotalDataSecondMoments( 5764607523034234884 );

    entity_total_third_moments =
      estimator_1_base->getEntityTotalDataThirdMoments( 5764607523034234884 );

    entity_total_fourth_moments =
      estimator_1_base->getEntityTotalDataFourthMoments( 5764607523034234884 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                     std::vector<double>( 1, 1.224744871391588 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                     std::vector<double>( 1, 1.4999999999999976 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                     std::vector<double>( 1, 1.8371173070873792 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                     std::vector<double>( 1, 2.249999999999993 ),
                                     1e-15 );

    entity_total_first_moments =
      estimator_1_base->getEntityTotalDataFirstMoments( 5764607523034234885 );

    entity_total_second_moments =
      estimator_1_base->getEntityTotalDataSecondMoments( 5764607523034234885 );

    entity_total_third_moments =
      estimator_1_base->getEntityTotalDataThirdMoments( 5764607523034234885 );

    entity_total_fourth_moments =
      estimator_1_base->getEntityTotalDataFourthMoments( 5764607523034234885 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                     std::vector<double>( 1, 1.224744871391588 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                     std::vector<double>( 1, 1.4999999999999976 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                     std::vector<double>( 1, 1.8371173070873792 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                     std::vector<double>( 1, 2.249999999999993 ),
                                     1e-15 );

    entity_total_first_moments =
      estimator_1_base->getEntityTotalDataFirstMoments( 5764607523034234886 );

    entity_total_second_moments =
      estimator_1_base->getEntityTotalDataSecondMoments( 5764607523034234886 );

    entity_total_third_moments =
      estimator_1_base->getEntityTotalDataThirdMoments( 5764607523034234886 );

    entity_total_fourth_moments =
      estimator_1_base->getEntityTotalDataFourthMoments( 5764607523034234886 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                     std::vector<double>( 1, 1.224744871391588 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                     std::vector<double>( 1, 1.4999999999999976 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                     std::vector<double>( 1, 1.8371173070873792 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                     std::vector<double>( 1, 2.249999999999993 ),
                                     1e-15 );

    // Check the total data moments
    Utility::ArrayView<const double> total_first_moments =
      estimator_1_base->getTotalDataFirstMoments();

    Utility::ArrayView<const double> total_second_moments =
      estimator_1_base->getTotalDataSecondMoments();

    Utility::ArrayView<const double> total_third_moments =
      estimator_1_base->getTotalDataThirdMoments();

    Utility::ArrayView<const double> total_fourth_moments =
      estimator_1_base->getTotalDataFourthMoments();

    FRENSIE_CHECK_FLOATING_EQUALITY( total_first_moments,
                                     std::vector<double>( 1, 7.348469228349528 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( total_second_moments,
                                     std::vector<double>( 1, 53.999999999999915 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( total_third_moments,
                                     std::vector<double>( 1, 396.8173383308739 ),
                                     1e-14 );
    FRENSIE_CHECK_FLOATING_EQUALITY( total_fourth_moments,
                                     std::vector<double>( 1, 2915.9999999999905 ),
                                     1e-14 );

    // Check that the correct contribution method is still used after restoring
    double start_point_1[3] = { 0.25, 0.0, 0.75 };
    double end_point_1[3] = { 0.75, 0.25, 1.0 };

    double start_point_2[3] = { 0.0, 0.25, 0.75 };
    double end_point_2[3] = { 0.25, 0.75, 1.0 };

    double start_point_3[3] = { 0.75, 0.0, 0.25 };
    double end_point_3[3] = { 1.0, 0.25, 0.75 };

    double start_point_4[3] = { 0.0, 0.75, 0.25 };
    double end_point_4[3] = { 0.25, 1.0, 0.75 };

    double start_point_5[3] = { 0.75, 0.25, 0.0 };
    double end_point_5[3] = { 1.0, 0.75, 0.25 };

    double start_point_6[3] = { 0.25, 0.75, 0.0 };
    double end_point_6[3] = { 0.75, 1.0, 0.25 };

    // bin 0, 2
    MonteCarlo::PhotonState particle( 0 );
    particle.setEnergy( 1.0 );
    particle.setTime( 2.0426545743715623e-11 );
    particle.setWeight( 1.0 );

    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1,
                                                              end_point_1 );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2,
                                                              end_point_2 );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3,
                                                              end_point_3 );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4,
                                                              end_point_4 );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_5,
                                                              end_point_5 );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_6,
                                                              end_point_6 );
    // bin 1, 3
    particle.setEnergy( 0.1 );

    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1,
                                                              end_point_1 );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2,
                                                              end_point_2 );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3,
                                                              end_point_3 );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4,
                                                              end_point_4 );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_5,
                                                              end_point_5 );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_6,
                                                              end_point_6 );
    // Commit the contributions
    estimator_1_base->commitHistoryContribution();

    entity_bin_first_moments =
      estimator_1_base->getEntityBinDataFirstMoments( 5764607523034234881 );

    entity_bin_second_moments =
      estimator_1_base->getEntityBinDataSecondMoments( 5764607523034234881 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 4, 3.061862178478970131e-01*2 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                     std::vector<double>( 4, 0.09374999999999985*2 ),
                                     1e-15 );

    entity_bin_first_moments =
      estimator_1_base->getEntityBinDataFirstMoments( 5764607523034234882 );

    entity_bin_second_moments =
      estimator_1_base->getEntityBinDataSecondMoments( 5764607523034234882 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 4, 3.061862178478970131e-01*2 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                     std::vector<double>( 4, 0.09374999999999985*2 ),
                                     1e-15 );

    entity_bin_first_moments =
      estimator_1_base->getEntityBinDataFirstMoments( 5764607523034234883 );

    entity_bin_second_moments =
      estimator_1_base->getEntityBinDataSecondMoments( 5764607523034234883 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 4, 3.061862178478970131e-01*2 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                     std::vector<double>( 4, 0.09374999999999985*2 ),
                                     1e-15 );

    entity_bin_first_moments =
      estimator_1_base->getEntityBinDataFirstMoments( 5764607523034234884 );

    entity_bin_second_moments =
      estimator_1_base->getEntityBinDataSecondMoments( 5764607523034234884 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 4, 3.061862178478970131e-01*2 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                     std::vector<double>( 4, 0.09374999999999985*2 ),
                                     1e-15 );

    entity_bin_first_moments =
      estimator_1_base->getEntityBinDataFirstMoments( 5764607523034234885 );

    entity_bin_second_moments =
      estimator_1_base->getEntityBinDataSecondMoments( 5764607523034234885 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 4, 3.061862178478970131e-01*2 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                     std::vector<double>( 4, 0.09374999999999985*2 ),
                                     1e-15 );

    entity_bin_first_moments =
      estimator_1_base->getEntityBinDataFirstMoments( 5764607523034234886 );

    entity_bin_second_moments =
      estimator_1_base->getEntityBinDataSecondMoments( 5764607523034234886 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 4, 3.061862178478970131e-01*2 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                     std::vector<double>( 4, 0.09374999999999985*2 ),
                                     1e-15 );
  }

  {
    FRENSIE_CHECK( estimator_2.get() == estimator_2_base.get() );

    FRENSIE_CHECK_EQUAL( estimator_2_base->getId(), 1 );
    FRENSIE_CHECK_EQUAL( estimator_2_base->getMultiplier(), 10.0 );
    FRENSIE_CHECK_EQUAL( estimator_2_base->getNumberOfBins(), 2 );
    FRENSIE_CHECK_EQUAL( estimator_2_base->getNumberOfBins( MonteCarlo::OBSERVER_ENERGY_DIMENSION ), 2 );
    FRENSIE_CHECK_EQUAL( estimator_2_base->getNumberOfResponseFunctions(), 1 );
    FRENSIE_CHECK_EQUAL( estimator_2_base->getParticleTypes().size(), 1 );
    FRENSIE_CHECK( estimator_2_base->getParticleTypes().find( MonteCarlo::PHOTON ) != estimator_2_base->getParticleTypes().end() );

    std::set<uint64_t> entity_ids;

    estimator_2->getEntityIds( entity_ids );

    FRENSIE_CHECK_EQUAL( entity_ids.size(), 6 );
    FRENSIE_CHECK( entity_ids.find( 5764607523034234881 ) != entity_ids.end() );
    FRENSIE_CHECK( entity_ids.find( 5764607523034234882 ) != entity_ids.end() );
    FRENSIE_CHECK( entity_ids.find( 5764607523034234883 ) != entity_ids.end() );
    FRENSIE_CHECK( entity_ids.find( 5764607523034234884 ) != entity_ids.end() );
    FRENSIE_CHECK( entity_ids.find( 5764607523034234885 ) != entity_ids.end() );
    FRENSIE_CHECK( entity_ids.find( 5764607523034234886 ) != entity_ids.end() );

    FRENSIE_CHECK_EQUAL( estimator_2_base->getEntityNormConstant( 5764607523034234881 ), 1.0/6 );
    FRENSIE_CHECK_EQUAL( estimator_2_base->getEntityNormConstant( 5764607523034234882 ), 1.0/6 );
    FRENSIE_CHECK_EQUAL( estimator_2_base->getEntityNormConstant( 5764607523034234883 ), 1.0/6 );
    FRENSIE_CHECK_EQUAL( estimator_2_base->getEntityNormConstant( 5764607523034234884 ), 1.0/6 );
    FRENSIE_CHECK_EQUAL( estimator_2_base->getEntityNormConstant( 5764607523034234885 ), 1.0/6 );
    FRENSIE_CHECK_EQUAL( estimator_2_base->getEntityNormConstant( 5764607523034234886 ), 1.0/6 );
    FRENSIE_CHECK_FLOATING_EQUALITY( estimator_2_base->getTotalNormConstant(),
                                     1.0,
                                     1e-15 );

    // Check the entity bin data moments
    Utility::ArrayView<const double> entity_bin_first_moments =
      estimator_2_base->getEntityBinDataFirstMoments( 5764607523034234881 );

    Utility::ArrayView<const double> entity_bin_second_moments =
      estimator_2_base->getEntityBinDataSecondMoments( 5764607523034234881 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.6123724356957940 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                     std::vector<double>( 2, 0.3749999999999994 ),
                                     1e-14 );

    entity_bin_first_moments =
      estimator_2_base->getEntityBinDataFirstMoments( 5764607523034234882 );

    entity_bin_second_moments =
      estimator_2_base->getEntityBinDataSecondMoments( 5764607523034234882 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.6123724356957940 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                     std::vector<double>( 2, 0.3749999999999994 ),
                                     1e-14 );

    entity_bin_first_moments =
      estimator_2_base->getEntityBinDataFirstMoments( 5764607523034234883 );

    entity_bin_second_moments =
      estimator_2_base->getEntityBinDataSecondMoments( 5764607523034234883 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.6123724356957940 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                     std::vector<double>( 2, 0.3749999999999994 ),
                                     1e-14 );

    entity_bin_first_moments =
      estimator_2_base->getEntityBinDataFirstMoments( 5764607523034234884 );

    entity_bin_second_moments =
      estimator_2_base->getEntityBinDataSecondMoments( 5764607523034234884 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.6123724356957940 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                     std::vector<double>( 2, 0.3749999999999994 ),
                                     1e-14 );

    entity_bin_first_moments =
      estimator_2_base->getEntityBinDataFirstMoments( 5764607523034234885 );

    entity_bin_second_moments =
      estimator_2_base->getEntityBinDataSecondMoments( 5764607523034234885 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.6123724356957940 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                     std::vector<double>( 2, 0.3749999999999994 ),
                                     1e-14 );

    entity_bin_first_moments =
      estimator_2_base->getEntityBinDataFirstMoments( 5764607523034234886 );

    entity_bin_second_moments =
      estimator_2_base->getEntityBinDataSecondMoments( 5764607523034234886 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.6123724356957940 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                     std::vector<double>( 2, 0.3749999999999994 ),
                                     1e-14 );

    // Check the total bin data moments
    Utility::ArrayView<const double> total_bin_first_moments =
      estimator_2_base->getTotalBinDataFirstMoments();

    Utility::ArrayView<const double> total_bin_second_moments =
      estimator_2_base->getTotalBinDataSecondMoments();

    FRENSIE_CHECK_FLOATING_EQUALITY( total_bin_first_moments,
                                     std::vector<double>( 2, 3.674234614174764 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( total_bin_second_moments,
                                     std::vector<double>( 2, 13.499999999999979 ),
                                     1e-14 );

    // Check the entity total data moments
    Utility::ArrayView<const double> entity_total_first_moments =
      estimator_2_base->getEntityTotalDataFirstMoments( 5764607523034234881 );

    Utility::ArrayView<const double> entity_total_second_moments =
      estimator_2_base->getEntityTotalDataSecondMoments( 5764607523034234881 );

    Utility::ArrayView<const double> entity_total_third_moments =
      estimator_2_base->getEntityTotalDataThirdMoments( 5764607523034234881 );

    Utility::ArrayView<const double> entity_total_fourth_moments =
      estimator_2_base->getEntityTotalDataFourthMoments( 5764607523034234881 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                     std::vector<double>( 1, 1.224744871391588 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                     std::vector<double>( 1, 1.4999999999999976 ),
                                     1e-14 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                     std::vector<double>( 1, 1.8371173070873792 ),
                                     1e-14 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                     std::vector<double>( 1, 2.249999999999993 ),
                                     1e-14 );

    entity_total_first_moments =
      estimator_2_base->getEntityTotalDataFirstMoments( 5764607523034234882 );

    entity_total_second_moments =
      estimator_2_base->getEntityTotalDataSecondMoments( 5764607523034234882 );

    entity_total_third_moments =
      estimator_2_base->getEntityTotalDataThirdMoments( 5764607523034234882 );

    entity_total_fourth_moments =
      estimator_2_base->getEntityTotalDataFourthMoments( 5764607523034234882 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                     std::vector<double>( 1, 1.224744871391588 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                     std::vector<double>( 1, 1.4999999999999976 ),
                                     1e-14 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                     std::vector<double>( 1, 1.8371173070873792 ),
                                     1e-14 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                     std::vector<double>( 1, 2.249999999999993 ),
                                     1e-14 );

    entity_total_first_moments =
      estimator_2_base->getEntityTotalDataFirstMoments( 5764607523034234883 );

    entity_total_second_moments =
      estimator_2_base->getEntityTotalDataSecondMoments( 5764607523034234883 );

    entity_total_third_moments =
      estimator_2_base->getEntityTotalDataThirdMoments( 5764607523034234883 );

    entity_total_fourth_moments =
      estimator_2_base->getEntityTotalDataFourthMoments( 5764607523034234883 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                     std::vector<double>( 1, 1.224744871391588 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                     std::vector<double>( 1, 1.4999999999999976 ),
                                     1e-14 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                     std::vector<double>( 1, 1.8371173070873792 ),
                                     1e-14 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                     std::vector<double>( 1, 2.249999999999993 ),
                                     1e-14 );

    entity_total_first_moments =
      estimator_2_base->getEntityTotalDataFirstMoments( 5764607523034234884 );

    entity_total_second_moments =
      estimator_2_base->getEntityTotalDataSecondMoments( 5764607523034234884 );

    entity_total_third_moments =
      estimator_2_base->getEntityTotalDataThirdMoments( 5764607523034234884 );

    entity_total_fourth_moments =
      estimator_2_base->getEntityTotalDataFourthMoments( 5764607523034234884 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                     std::vector<double>( 1, 1.224744871391588 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                     std::vector<double>( 1, 1.4999999999999976 ),
                                     1e-14 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                     std::vector<double>( 1, 1.8371173070873792 ),
                                     1e-14 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                     std::vector<double>( 1, 2.249999999999993 ),
                                     1e-14 );

    entity_total_first_moments =
      estimator_2_base->getEntityTotalDataFirstMoments( 5764607523034234885 );

    entity_total_second_moments =
      estimator_2_base->getEntityTotalDataSecondMoments( 5764607523034234885 );

    entity_total_third_moments =
      estimator_2_base->getEntityTotalDataThirdMoments( 5764607523034234885 );

    entity_total_fourth_moments =
      estimator_2_base->getEntityTotalDataFourthMoments( 5764607523034234885 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                     std::vector<double>( 1, 1.224744871391588 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                     std::vector<double>( 1, 1.4999999999999976 ),
                                     1e-14 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                     std::vector<double>( 1, 1.8371173070873792 ),
                                     1e-14 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                     std::vector<double>( 1, 2.249999999999993 ),
                                     1e-14 );

    entity_total_first_moments =
      estimator_2_base->getEntityTotalDataFirstMoments( 5764607523034234886 );

    entity_total_second_moments =
      estimator_2_base->getEntityTotalDataSecondMoments( 5764607523034234886 );

    entity_total_third_moments =
      estimator_2_base->getEntityTotalDataThirdMoments( 5764607523034234886 );

    entity_total_fourth_moments =
      estimator_2_base->getEntityTotalDataFourthMoments( 5764607523034234886 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                     std::vector<double>( 1, 1.224744871391588 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                     std::vector<double>( 1, 1.4999999999999976 ),
                                     1e-14 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                     std::vector<double>( 1, 1.8371173070873792 ),
                                     1e-14 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                     std::vector<double>( 1, 2.249999999999993 ),
                                     1e-14 );

    // Check the total data moments
    Utility::ArrayView<const double> total_first_moments =
      estimator_2_base->getTotalDataFirstMoments();
    Utility::ArrayView<const double> total_second_moments =
      estimator_2_base->getTotalDataSecondMoments();
    Utility::ArrayView<const double> total_third_moments =
      estimator_2_base->getTotalDataThirdMoments();
    Utility::ArrayView<const double> total_fourth_moments =
      estimator_2_base->getTotalDataFourthMoments();

    FRENSIE_CHECK_FLOATING_EQUALITY( total_first_moments,
                                     std::vector<double>( 1, 7.348469228349528 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( total_second_moments,
                                     std::vector<double>( 1, 53.999999999999915 ),
                                     1e-14 );
    FRENSIE_CHECK_FLOATING_EQUALITY( total_third_moments,
                                     std::vector<double>( 1, 396.8173383308739 ),
                                     1e-14 );
    FRENSIE_CHECK_FLOATING_EQUALITY( total_fourth_moments,
                                     std::vector<double>( 1, 2915.9999999999905 ),
                                     1e-14 );

    // Check that the correct contribution method is still used after restoring
    double start_point_1[3] = { 0.25, 0.0, 0.75 };
    double end_point_1[3] = { 0.75, 0.25, 1.0 };

    double start_point_2[3] = { 0.0, 0.25, 0.75 };
    double end_point_2[3] = { 0.25, 0.75, 1.0 };

    double start_point_3[3] = { 0.75, 0.0, 0.25 };
    double end_point_3[3] = { 1.0, 0.25, 0.75 };

    double start_point_4[3] = { 0.0, 0.75, 0.25 };
    double end_point_4[3] = { 0.25, 1.0, 0.75 };

    double start_point_5[3] = { 0.75, 0.25, 0.0 };
    double end_point_5[3] = { 1.0, 0.75, 0.25 };

    double start_point_6[3] = { 0.25, 0.75, 0.0 };
    double end_point_6[3] = { 0.75, 1.0, 0.25 };

    // bin 0, 2
    MonteCarlo::PhotonState particle( 0 );
    particle.setEnergy( 1.0 );
    particle.setTime( 2.0426545743715623e-11 );
    particle.setWeight( 1.0 );

    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1,
                                                              end_point_1 );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2,
                                                              end_point_2 );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3,
                                                              end_point_3 );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4,
                                                              end_point_4 );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_5,
                                                              end_point_5 );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_6,
                                                              end_point_6 );
    // bin 1, 3
    particle.setEnergy( 0.1 );
    particle.setWeight( 10.0 );

    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1,
                                                              end_point_1 );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2,
                                                              end_point_2 );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3,
                                                              end_point_3 );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4,
                                                              end_point_4 );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_5,
                                                              end_point_5 );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_6,
                                                              end_point_6 );
    // Commit the contributions
    estimator_2_base->commitHistoryContribution();

    entity_bin_first_moments =
    estimator_2_base->getEntityBinDataFirstMoments( 5764607523034234881 );

    entity_bin_second_moments =
      estimator_2_base->getEntityBinDataSecondMoments( 5764607523034234881 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.6123724356957940*2 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                     std::vector<double>( 2, 0.3749999999999994*2 ),
                                     1e-14 );

    entity_bin_first_moments =
      estimator_2_base->getEntityBinDataFirstMoments( 5764607523034234882 );

    entity_bin_second_moments =
      estimator_2_base->getEntityBinDataSecondMoments( 5764607523034234882 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.6123724356957940*2 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                     std::vector<double>( 2, 0.3749999999999994*2 ),
                                     1e-14 );

    entity_bin_first_moments =
      estimator_2_base->getEntityBinDataFirstMoments( 5764607523034234883 );

    entity_bin_second_moments =
      estimator_2_base->getEntityBinDataSecondMoments( 5764607523034234883 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.6123724356957940*2 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                     std::vector<double>( 2, 0.3749999999999994*2 ),
                                     1e-14 );

    entity_bin_first_moments =
      estimator_2_base->getEntityBinDataFirstMoments( 5764607523034234884 );

    entity_bin_second_moments =
      estimator_2_base->getEntityBinDataSecondMoments( 5764607523034234884 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.6123724356957940*2 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                     std::vector<double>( 2, 0.3749999999999994*2 ),
                                     1e-14 );

    entity_bin_first_moments =
      estimator_2_base->getEntityBinDataFirstMoments( 5764607523034234885 );

    entity_bin_second_moments =
      estimator_2_base->getEntityBinDataSecondMoments( 5764607523034234885 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.6123724356957940*2 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                     std::vector<double>( 2, 0.3749999999999994*2 ),
                                     1e-14 );

    entity_bin_first_moments =
      estimator_2_base->getEntityBinDataFirstMoments( 5764607523034234886 );

    entity_bin_second_moments =
      estimator_2_base->getEntityBinDataSecondMoments( 5764607523034234886 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.6123724356957940*2 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                     std::vector<double>( 2, 0.3749999999999994*2 ),
                                     1e-14 );
  }

  {
    FRENSIE_CHECK( estimator_3.get() == estimator_3_base.get() );

    FRENSIE_CHECK_EQUAL( estimator_3_base->getId(), 2 );
    FRENSIE_CHECK_EQUAL( estimator_3_base->getMultiplier(), 1.0 );
    FRENSIE_CHECK_EQUAL( estimator_3_base->getNumberOfBins(), 2 );
    FRENSIE_CHECK_EQUAL( estimator_3_base->getNumberOfBins( MonteCarlo::OBSERVER_ENERGY_DIMENSION ), 2 );
    FRENSIE_CHECK_EQUAL( estimator_3_base->getNumberOfResponseFunctions(), 1 );
    FRENSIE_CHECK_EQUAL( estimator_3_base->getParticleTypes().size(), 1 );
    FRENSIE_CHECK( estimator_3_base->getParticleTypes().find( MonteCarlo::PHOTON ) != estimator_3_base->getParticleTypes().end() );

    std::set<uint64_t> entity_ids;

    estimator_3->getEntityIds( entity_ids );

    FRENSIE_CHECK_EQUAL( entity_ids.size(), 6 );
    FRENSIE_CHECK( entity_ids.find( 5764607523034234881 ) != entity_ids.end() );
    FRENSIE_CHECK( entity_ids.find( 5764607523034234882 ) != entity_ids.end() );
    FRENSIE_CHECK( entity_ids.find( 5764607523034234883 ) != entity_ids.end() );
    FRENSIE_CHECK( entity_ids.find( 5764607523034234884 ) != entity_ids.end() );
    FRENSIE_CHECK( entity_ids.find( 5764607523034234885 ) != entity_ids.end() );
    FRENSIE_CHECK( entity_ids.find( 5764607523034234886 ) != entity_ids.end() );

    FRENSIE_CHECK_EQUAL( estimator_3_base->getEntityNormConstant( 5764607523034234881 ), 1.0/6 );
    FRENSIE_CHECK_EQUAL( estimator_3_base->getEntityNormConstant( 5764607523034234882 ), 1.0/6 );
    FRENSIE_CHECK_EQUAL( estimator_3_base->getEntityNormConstant( 5764607523034234883 ), 1.0/6 );
    FRENSIE_CHECK_EQUAL( estimator_3_base->getEntityNormConstant( 5764607523034234884 ), 1.0/6 );
    FRENSIE_CHECK_EQUAL( estimator_3_base->getEntityNormConstant( 5764607523034234885 ), 1.0/6 );
    FRENSIE_CHECK_EQUAL( estimator_3_base->getEntityNormConstant( 5764607523034234886 ), 1.0/6 );
    FRENSIE_CHECK_FLOATING_EQUALITY( estimator_3_base->getTotalNormConstant(),
                                     1.0,
                                     1e-15 );

    // Check the entity bin data moments
    Utility::ArrayView<const double> entity_bin_first_moments =
      estimator_3_base->getEntityBinDataFirstMoments( 5764607523034234881 );

    Utility::ArrayView<const double> entity_bin_second_moments =
      estimator_3_base->getEntityBinDataSecondMoments( 5764607523034234881 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );

    entity_bin_first_moments =
      estimator_3_base->getEntityBinDataFirstMoments( 5764607523034234882 );

    entity_bin_second_moments =
      estimator_3_base->getEntityBinDataSecondMoments( 5764607523034234882 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );

    entity_bin_first_moments =
      estimator_3_base->getEntityBinDataFirstMoments( 5764607523034234883 );

    entity_bin_second_moments =
      estimator_3_base->getEntityBinDataSecondMoments( 5764607523034234883 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );

    entity_bin_first_moments =
      estimator_3_base->getEntityBinDataFirstMoments( 5764607523034234884 );

    entity_bin_second_moments =
      estimator_3_base->getEntityBinDataSecondMoments( 5764607523034234884 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );

    entity_bin_first_moments =
      estimator_3_base->getEntityBinDataFirstMoments( 5764607523034234885 );

    entity_bin_second_moments =
      estimator_3_base->getEntityBinDataSecondMoments( 5764607523034234885 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );

    entity_bin_first_moments =
      estimator_3_base->getEntityBinDataFirstMoments( 5764607523034234886 );

    entity_bin_second_moments =
      estimator_3_base->getEntityBinDataSecondMoments( 5764607523034234886 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );

    // Check the total bin data moments
    Utility::ArrayView<const double> total_bin_first_moments =
      estimator_3_base->getTotalBinDataFirstMoments();

    Utility::ArrayView<const double> total_bin_second_moments =
      estimator_3_base->getTotalBinDataSecondMoments();

    FRENSIE_CHECK_FLOATING_EQUALITY( total_bin_first_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( total_bin_second_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );

    // Check the entity total data moments
    Utility::ArrayView<const double> entity_total_first_moments =
      estimator_3_base->getEntityTotalDataFirstMoments( 5764607523034234881 );

    Utility::ArrayView<const double> entity_total_second_moments =
      estimator_3_base->getEntityTotalDataSecondMoments( 5764607523034234881 );

    Utility::ArrayView<const double> entity_total_third_moments =
      estimator_3_base->getEntityTotalDataThirdMoments( 5764607523034234881 );

    Utility::ArrayView<const double> entity_total_fourth_moments =
      estimator_3_base->getEntityTotalDataFourthMoments( 5764607523034234881 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                     std::vector<double>( 1, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                     std::vector<double>( 1, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                     std::vector<double>( 1, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                     std::vector<double>( 1, 0.0 ),
                                     1e-15 );

    entity_total_first_moments =
      estimator_3_base->getEntityTotalDataFirstMoments( 5764607523034234882 );

    entity_total_second_moments =
      estimator_3_base->getEntityTotalDataSecondMoments( 5764607523034234882 );

    entity_total_third_moments =
      estimator_3_base->getEntityTotalDataThirdMoments( 5764607523034234882 );

    entity_total_fourth_moments =
      estimator_3_base->getEntityTotalDataFourthMoments( 5764607523034234882 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                     std::vector<double>( 1, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                     std::vector<double>( 1, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                     std::vector<double>( 1, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                     std::vector<double>( 1, 0.0 ),
                                     1e-15 );

    entity_total_first_moments =
      estimator_3_base->getEntityTotalDataFirstMoments( 5764607523034234883 );

    entity_total_second_moments =
      estimator_3_base->getEntityTotalDataSecondMoments( 5764607523034234883 );

    entity_total_third_moments =
      estimator_3_base->getEntityTotalDataThirdMoments( 5764607523034234883 );

    entity_total_fourth_moments =
      estimator_3_base->getEntityTotalDataFourthMoments( 5764607523034234883 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                     std::vector<double>( 1, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                     std::vector<double>( 1, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                     std::vector<double>( 1, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                     std::vector<double>( 1, 0.0 ),
                                     1e-15 );

    entity_total_first_moments =
      estimator_3_base->getEntityTotalDataFirstMoments( 5764607523034234884 );

    entity_total_second_moments =
      estimator_3_base->getEntityTotalDataSecondMoments( 5764607523034234884 );

    entity_total_third_moments =
      estimator_3_base->getEntityTotalDataThirdMoments( 5764607523034234884 );

    entity_total_fourth_moments =
      estimator_3_base->getEntityTotalDataFourthMoments( 5764607523034234884 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                     std::vector<double>( 1, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                     std::vector<double>( 1, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                     std::vector<double>( 1, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                     std::vector<double>( 1, 0.0 ),
                                     1e-15 );

    entity_total_first_moments =
      estimator_3_base->getEntityTotalDataFirstMoments( 5764607523034234885 );

    entity_total_second_moments =
      estimator_3_base->getEntityTotalDataSecondMoments( 5764607523034234885 );

    entity_total_third_moments =
      estimator_3_base->getEntityTotalDataThirdMoments( 5764607523034234885 );

    entity_total_fourth_moments =
      estimator_3_base->getEntityTotalDataFourthMoments( 5764607523034234885 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                     std::vector<double>( 1, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                     std::vector<double>( 1, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                     std::vector<double>( 1, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                     std::vector<double>( 1, 0.0 ),
                                     1e-15 );

    entity_total_first_moments =
      estimator_3_base->getEntityTotalDataFirstMoments( 5764607523034234886 );

    entity_total_second_moments =
      estimator_3_base->getEntityTotalDataSecondMoments( 5764607523034234886 );

    entity_total_third_moments =
      estimator_3_base->getEntityTotalDataThirdMoments( 5764607523034234886 );

    entity_total_fourth_moments =
      estimator_3_base->getEntityTotalDataFourthMoments( 5764607523034234886 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                     std::vector<double>( 1, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                     std::vector<double>( 1, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                     std::vector<double>( 1, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                     std::vector<double>( 1, 0.0 ),
                                     1e-15 );

    // Check the total data moments
    Utility::ArrayView<const double> total_first_moments =
      estimator_3_base->getTotalDataFirstMoments();
    Utility::ArrayView<const double> total_second_moments =
      estimator_3_base->getTotalDataSecondMoments();
    Utility::ArrayView<const double> total_third_moments =
      estimator_3_base->getTotalDataThirdMoments();
    Utility::ArrayView<const double> total_fourth_moments =
      estimator_3_base->getTotalDataFourthMoments();

    FRENSIE_CHECK_FLOATING_EQUALITY( total_first_moments,
                                     std::vector<double>( 1, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( total_second_moments,
                                     std::vector<double>( 1, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( total_third_moments,
                                     std::vector<double>( 1, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( total_fourth_moments,
                                     std::vector<double>( 1, 0.0 ),
                                     1e-15 );

    // Check that the correct contribution method is still used after restoring
    double start_point_1[3] = { 0.25, 0.0, 0.75 };
    double end_point_1[3] = { 0.75, 0.25, 1.0 };

    double start_point_2[3] = { 0.0, 0.25, 0.75 };
    double end_point_2[3] = { 0.25, 0.75, 1.0 };

    double start_point_3[3] = { 0.75, 0.0, 0.25 };
    double end_point_3[3] = { 1.0, 0.25, 0.75 };

    double start_point_4[3] = { 0.0, 0.75, 0.25 };
    double end_point_4[3] = { 0.25, 1.0, 0.75 };

    double start_point_5[3] = { 0.75, 0.25, 0.0 };
    double end_point_5[3] = { 1.0, 0.75, 0.25 };

    double start_point_6[3] = { 0.25, 0.75, 0.0 };
    double end_point_6[3] = { 0.75, 1.0, 0.25 };

    // bin 0, 2
    MonteCarlo::PhotonState particle( 0 );
    particle.setEnergy( 1.0 );
    particle.setTime( 2.0426545743715623e-11 );
    particle.setWeight( 1.0 );

    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1,
                                                              end_point_1 );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2,
                                                              end_point_2 );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3,
                                                              end_point_3 );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4,
                                                              end_point_4 );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_5,
                                                              end_point_5 );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_6,
                                                              end_point_6 );
    // bin 1, 3
    particle.setEnergy( 0.1 );
    particle.setWeight( 10.0 );

    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1,
                                                              end_point_1 );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2,
                                                              end_point_2 );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3,
                                                              end_point_3 );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4,
                                                              end_point_4 );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_5,
                                                              end_point_5 );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_6,
                                                              end_point_6 );
    // Commit the contributions
    estimator_3_base->commitHistoryContribution();

    entity_bin_first_moments =
    estimator_3_base->getEntityBinDataFirstMoments( 5764607523034234881 );

    entity_bin_second_moments =
      estimator_3_base->getEntityBinDataSecondMoments( 5764607523034234881 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );

    entity_bin_first_moments =
      estimator_3_base->getEntityBinDataFirstMoments( 5764607523034234882 );

    entity_bin_second_moments =
      estimator_3_base->getEntityBinDataSecondMoments( 5764607523034234882 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );

    entity_bin_first_moments =
      estimator_3_base->getEntityBinDataFirstMoments( 5764607523034234883 );

    entity_bin_second_moments =
      estimator_3_base->getEntityBinDataSecondMoments( 5764607523034234883 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );

    entity_bin_first_moments =
      estimator_3_base->getEntityBinDataFirstMoments( 5764607523034234884 );

    entity_bin_second_moments =
      estimator_3_base->getEntityBinDataSecondMoments( 5764607523034234884 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );

    entity_bin_first_moments =
      estimator_3_base->getEntityBinDataFirstMoments( 5764607523034234885 );

    entity_bin_second_moments =
      estimator_3_base->getEntityBinDataSecondMoments( 5764607523034234885 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );

    entity_bin_first_moments =
      estimator_3_base->getEntityBinDataFirstMoments( 5764607523034234886 );

    entity_bin_second_moments =
      estimator_3_base->getEntityBinDataSecondMoments( 5764607523034234886 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );
  }
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

int threads;
std::string test_input_mesh_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "threads",
                                        threads, 1,
                                        "Number of threads to use" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_input_mesh_file_name",
                                        test_input_mesh_file_name, "",
                                        "Test input mesh file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Set up the global OpenMP session
  if( Utility::OpenMPProperties::isOpenMPUsed() )
    Utility::OpenMPProperties::setNumberOfThreads( threads );

  // Create the tet mesh
  tet_mesh.reset( new Utility::TetMesh( test_input_mesh_file_name ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstTetMeshTrackLengthFluxEstimator.cpp
//---------------------------------------------------------------------------//
