//---------------------------------------------------------------------------//
//!
//! \file   tstTetMeshTrackLengthFluxEstimator.cpp
//! \author Philip Britt
//! \brief  TetMeshTrackLengthFluxEstimator class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>
#include <vector>

// FRENSIE Includes
#include "MonteCarlo_MeshTrackLengthFluxEstimator.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Utility_StructuredHexMesh.hpp"
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

std::shared_ptr<const Utility::Mesh> hex_mesh;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the estimator is a mesh type estimator
FRENSIE_UNIT_TEST_TEMPLATE( HexMeshTrackLengthFluxEstimator,
                            check_type,
                            MultiplierPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, ContributionMultiplierPolicy );

  std::shared_ptr<MonteCarlo::Estimator> estimator(
    new MonteCarlo::MeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>(
                                                                  0,
                                                                  1.0,
                                                                  hex_mesh ) );

  FRENSIE_CHECK( !estimator->isCellEstimator() );
  FRENSIE_CHECK( !estimator->isSurfaceEstimator() );
  FRENSIE_CHECK( estimator->isMeshEstimator() );
}
//---------------------------------------------------------------------------//
// Check that estimator bins can be set
FRENSIE_UNIT_TEST_TEMPLATE( HexMeshTrackLengthFluxEstimator,
                            setDiscretization,
                            MultiplierPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, ContributionMultiplierPolicy );

  std::shared_ptr<MonteCarlo::Estimator> estimator(
    new MonteCarlo::MeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>(
                                                                  0,
                                                                  1.0,
                                                                  hex_mesh ) );

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


  estimator->setDirectionDiscretization( MonteCarlo::ObserverDirectionDimensionDiscretization::ObserverDirectionDiscretizationType::PQLA,
                                        2,
                                        true );

  FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins( MonteCarlo::OBSERVER_DIRECTION_DIMENSION ),
                       8*4 );
  FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins(), 8*8*4 );
}

//---------------------------------------------------------------------------//
// Check that particle types can be assigned
FRENSIE_UNIT_TEST_TEMPLATE( HexMeshTrackLengthFluxEstimator,
                            setParticleType,
                            MultiplierPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, ContributionMultiplierPolicy );

  std::shared_ptr<MonteCarlo::Estimator> estimator(
    new MonteCarlo::MeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>(
                                                                  0,
                                                                  1.0,
                                                                  hex_mesh ) );

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
FRENSIE_UNIT_TEST( HexMeshTrackLengthFluxEstimator,
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
                                                                  hex_mesh ) );

    estimator_1_base = estimator_1;

    estimator_2.reset( new MonteCarlo::MeshTrackLengthFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier>(
                                                                  1,
                                                                  10.0,
                                                                  hex_mesh ) );

    estimator_2_base = estimator_2;

    estimator_3.reset( new MonteCarlo::MeshTrackLengthFluxEstimator<MonteCarlo::WeightAndChargeMultiplier>(
                                                                  2,
                                                                  1.0,
                                                                  hex_mesh ) );

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
    time_bin_boundaries[1] = 3.33564095198152e-11;
    time_bin_boundaries[2] = 6.67128190396304e-11;

    estimator_1_base->setDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION>(
						       time_bin_boundaries );

    // Set the particle types
    std::vector<MonteCarlo::ParticleType> particle_types( 1 );
    particle_types[0] = MonteCarlo::PHOTON;

    estimator_1_base->setParticleTypes( particle_types );
    estimator_2_base->setParticleTypes( particle_types );
    estimator_3_base->setParticleTypes( particle_types );
  }

  FRENSIE_CHECK( !estimator_1_base->hasUncommittedHistoryContribution() );
  FRENSIE_CHECK( !estimator_2_base->hasUncommittedHistoryContribution() );
  FRENSIE_CHECK( !estimator_3_base->hasUncommittedHistoryContribution() );

  double track_length = 2.0;
  double volume = 1.0;
  int num_hexes = 8;

  double start_point_1a[3] = {0.5, 0.5, 0.0};
  double end_point_1a[3] = {0.5, 0.5, 2.0};
  double direction_1a[3] = {0.0, 0.0, 1.0};

  double start_point_1b[3] = {0.5, 0.5, 2.0};
  double end_point_1b[3] = {0.5, 0.5, 0.0};
  double direction_1b[3] = {0.0, 0.0, -1.0};

  double start_point_2a[3] = {0.5, 1.5, 0.0};
  double end_point_2a[3] = {0.5, 1.5, 2.0};
  double direction_2a[3] = {0.0, 0.0, 1.0};

  double start_point_2b[3] = {0.5, 1.5, 2.0};
  double end_point_2b[3] = {0.5, 1.5, 0.0};
  double direction_2b[3] = {0.0, 0.0, -1.0};

  double start_point_3a[3] = {1.5, 0.5, 0.0};
  double end_point_3a[3] = {1.5, 0.5, 2.0};
  double direction_3a[3] = {0.0, 0.0, 1.0};

  double start_point_3b[3] = {1.5, 0.5, 2.0};
  double end_point_3b[3] = {1.5, 0.5, 0.0};
  double direction_3b[3] = {0.0, 0.0, -1.0};

  double start_point_4a[3] = {1.5, 1.5, 0.0};
  double end_point_4a[3] = {1.5, 1.5, 2.0};
  double direction_4a[3] = {0.0, 0.0, 1.0};

  double start_point_4b[3] = {1.5, 1.5, 2.0};
  double end_point_4b[3] = {1.5, 1.5, 0.0};
  double direction_4b[3] = {0.0, 0.0, -1.0};

  // bin 0, 2
  MonteCarlo::PhotonState particle( 0 );
  particle.setEnergy( 1.0 );
  particle.setTime( 6.67128190396304e-11 );
  particle.setWeight( 1.0 );

  estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_1a,
                                                            end_point_1a );
  estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_1b,
                                                            end_point_1b );
  estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_2a,
                                                            end_point_2a );
  estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_2b,
                                                            end_point_2b );
  estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_3a,
                                                            end_point_3a );
  estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_3b,
                                                            end_point_3b );
  estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_4a,
                                                            end_point_4a );
  estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_4b,
                                                            end_point_4b );

  estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_1a,
                                                            end_point_1a );
  estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_1b,
                                                            end_point_1b );
  estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_2a,
                                                            end_point_2a );
  estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_2b,
                                                            end_point_2b );
  estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_3a,
                                                            end_point_3a );
  estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_3b,
                                                            end_point_3b );
  estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_4a,
                                                            end_point_4a );
  estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_4b,
                                                            end_point_4b );

  estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_1a,
                                                            end_point_1a );
  estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_1b,
                                                            end_point_1b );
  estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_2a,
                                                            end_point_2a );
  estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_2b,
                                                            end_point_2b );
  estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_3a,
                                                            end_point_3a );
  estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_3b,
                                                            end_point_3b );
  estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_4a,
                                                            end_point_4a );
  estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_4b,
                                                            end_point_4b );

  FRENSIE_CHECK( estimator_1->hasUncommittedHistoryContribution() );
  FRENSIE_CHECK( estimator_2->hasUncommittedHistoryContribution() );
  FRENSIE_CHECK( estimator_3->hasUncommittedHistoryContribution() );

  // bin 1, 3
  particle.setEnergy( 0.1 );
  particle.setTime( 6.67128190396304e-11 );

  estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_1a,
                                                            end_point_1a );
  estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_1b,
                                                            end_point_1b );
  estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_2a,
                                                            end_point_2a );
  estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_2b,
                                                            end_point_2b );
  estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_3a,
                                                            end_point_3a );
  estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_3b,
                                                            end_point_3b );
  estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_4a,
                                                            end_point_4a );
  estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_4b,
                                                            end_point_4b );

  particle.setWeight( 10.0 );
  estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_1a,
                                                            end_point_1a );
  estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_1b,
                                                            end_point_1b );
  estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_2a,
                                                            end_point_2a );
  estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_2b,
                                                            end_point_2b );
  estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_3a,
                                                            end_point_3a );
  estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_3b,
                                                            end_point_3b );
  estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_4a,
                                                            end_point_4a );
  estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_4b,
                                                            end_point_4b );

  particle.setWeight( 1.0 );
  estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_1a,
                                                            end_point_1a );
  estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_1b,
                                                            end_point_1b );
  estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_2a,
                                                            end_point_2a );
  estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_2b,
                                                            end_point_2b );
  estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_3a,
                                                            end_point_3a );
  estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_3b,
                                                            end_point_3b );
  estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_4a,
                                                            end_point_4a );
  estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                            start_point_4b,
                                                            end_point_4b );

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
    estimator_1_base->getEntityBinDataFirstMoments( 0 );

  Utility::ArrayView<const double> entity_bin_second_moments =
    estimator_1_base->getEntityBinDataSecondMoments( 0 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 4, 1.0 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 4, 1.0 ) );

  entity_bin_first_moments =
    estimator_1_base->getEntityBinDataFirstMoments( 1 );

  entity_bin_second_moments =
    estimator_1_base->getEntityBinDataSecondMoments( 1 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 4, 1.0 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 4, 1.0 ) );

  entity_bin_first_moments =
    estimator_1_base->getEntityBinDataFirstMoments( 2 );

  entity_bin_second_moments =
    estimator_1_base->getEntityBinDataSecondMoments( 2 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 4, 1.0 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 4, 1.0 ) );

  entity_bin_first_moments =
    estimator_1_base->getEntityBinDataFirstMoments( 3 );

  entity_bin_second_moments =
    estimator_1_base->getEntityBinDataSecondMoments( 3 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 4, 1.0 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 4, 1.0 ) );

  entity_bin_first_moments =
    estimator_1_base->getEntityBinDataFirstMoments( 4 );

  entity_bin_second_moments =
    estimator_1_base->getEntityBinDataSecondMoments( 4 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 4, 1.0 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 4, 1.0 ) );

  entity_bin_first_moments =
    estimator_1_base->getEntityBinDataFirstMoments( 5 );

  entity_bin_second_moments =
    estimator_1_base->getEntityBinDataSecondMoments( 5 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 4, 1.0 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 4, 1.0 ) );

  entity_bin_first_moments =
    estimator_1_base->getEntityBinDataFirstMoments( 6 );

  entity_bin_second_moments =
    estimator_1_base->getEntityBinDataSecondMoments( 6 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 4, 1.0 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 4, 1.0 ) );

  entity_bin_first_moments =
    estimator_1_base->getEntityBinDataFirstMoments( 7 );

  entity_bin_second_moments =
    estimator_1_base->getEntityBinDataSecondMoments( 7 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 4, 1.0 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 4, 1.0 ) );

  entity_bin_first_moments =
    estimator_2_base->getEntityBinDataFirstMoments( 0 );

  entity_bin_second_moments =
    estimator_2_base->getEntityBinDataSecondMoments( 0 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 2, 2.0 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 2, 4.0 ) );

  entity_bin_first_moments =
    estimator_2_base->getEntityBinDataFirstMoments( 1 );

  entity_bin_second_moments =
    estimator_2_base->getEntityBinDataSecondMoments( 1 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 2, 2.0 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 2, 4.0 ) );

  entity_bin_first_moments =
    estimator_2_base->getEntityBinDataFirstMoments( 2 );

  entity_bin_second_moments =
    estimator_2_base->getEntityBinDataSecondMoments( 2 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 2, 2.0 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 2, 4.0 ) );

  entity_bin_first_moments =
    estimator_2_base->getEntityBinDataFirstMoments( 3 );

  entity_bin_second_moments =
    estimator_2_base->getEntityBinDataSecondMoments( 3 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 2, 2.0 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 2, 4.0 ) );

  entity_bin_first_moments =
    estimator_2_base->getEntityBinDataFirstMoments( 4 );

  entity_bin_second_moments =
    estimator_2_base->getEntityBinDataSecondMoments( 4 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 2, 2.0 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 2, 4.0 ) );

  entity_bin_first_moments =
    estimator_2_base->getEntityBinDataFirstMoments( 5 );

  entity_bin_second_moments =
    estimator_2_base->getEntityBinDataSecondMoments( 5 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 2, 2.0 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 2, 4.0 ) );

  entity_bin_first_moments =
    estimator_2_base->getEntityBinDataFirstMoments( 6 );

  entity_bin_second_moments =
    estimator_2_base->getEntityBinDataSecondMoments( 6 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 2, 2.0 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 2, 4.0 ) );

  entity_bin_first_moments =
    estimator_2_base->getEntityBinDataFirstMoments( 7 );

  entity_bin_second_moments =
    estimator_2_base->getEntityBinDataSecondMoments( 7 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 2, 2.0 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 2, 4.0 ) );

  entity_bin_first_moments =
    estimator_3_base->getEntityBinDataFirstMoments( 0 );

  entity_bin_second_moments =
    estimator_3_base->getEntityBinDataSecondMoments( 0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 2, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 2, 0.0 ), 1e-15 );

  entity_bin_first_moments =
    estimator_3_base->getEntityBinDataFirstMoments( 1 );

  entity_bin_second_moments =
    estimator_3_base->getEntityBinDataSecondMoments( 1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 2, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 2, 0.0 ), 1e-15 );

  entity_bin_first_moments =
    estimator_3_base->getEntityBinDataFirstMoments( 2 );

  entity_bin_second_moments =
    estimator_3_base->getEntityBinDataSecondMoments( 2 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 2, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 2, 0.0 ), 1e-15 );

  entity_bin_first_moments =
    estimator_3_base->getEntityBinDataFirstMoments( 3 );

  entity_bin_second_moments =
    estimator_3_base->getEntityBinDataSecondMoments( 3 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 2, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 2, 0.0 ), 1e-15 );

  entity_bin_first_moments =
    estimator_3_base->getEntityBinDataFirstMoments( 4 );

  entity_bin_second_moments =
    estimator_3_base->getEntityBinDataSecondMoments( 4 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 2, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 2, 0.0 ), 1e-15 );

  entity_bin_first_moments =
    estimator_3_base->getEntityBinDataFirstMoments( 5 );

  entity_bin_second_moments =
    estimator_3_base->getEntityBinDataSecondMoments( 5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 2, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 2, 0.0 ), 1e-15 );

  entity_bin_first_moments =
    estimator_3_base->getEntityBinDataFirstMoments( 6 );

  entity_bin_second_moments =
    estimator_3_base->getEntityBinDataSecondMoments( 6 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 2, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 2, 0.0 ), 1e-15 );

  entity_bin_first_moments =
    estimator_3_base->getEntityBinDataFirstMoments( 7 );

  entity_bin_second_moments =
    estimator_3_base->getEntityBinDataSecondMoments( 7 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 2, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 2, 0.0 ), 1e-15 );

  // Check the total bin data moments
  Utility::ArrayView<const double> total_bin_first_moments =
    estimator_1_base->getTotalBinDataFirstMoments();

  Utility::ArrayView<const double> total_bin_second_moments =
    estimator_1_base->getTotalBinDataSecondMoments();

  FRENSIE_CHECK_EQUAL( total_bin_first_moments,
                       std::vector<double>( 4, 8.0 ) );
  FRENSIE_CHECK_EQUAL( total_bin_second_moments,
                       std::vector<double>( 4, 64.0 ) );

  total_bin_first_moments =
    estimator_2_base->getTotalBinDataFirstMoments();

  total_bin_second_moments =
    estimator_2_base->getTotalBinDataSecondMoments();

  FRENSIE_CHECK_EQUAL( total_bin_first_moments,
                       std::vector<double>( 2, 16.0 ) );
  FRENSIE_CHECK_EQUAL( total_bin_second_moments,
                       std::vector<double>( 2, 256.0 ) );

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
    estimator_1_base->getEntityTotalDataFirstMoments( 0 );

  Utility::ArrayView<const double> entity_total_second_moments =
    estimator_1_base->getEntityTotalDataSecondMoments( 0 );

  Utility::ArrayView<const double> entity_total_third_moments =
    estimator_1_base->getEntityTotalDataThirdMoments( 0 );

  Utility::ArrayView<const double> entity_total_fourth_moments =
    estimator_1_base->getEntityTotalDataFourthMoments( 0 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, 4.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 16.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, 64.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 256.0 ) );

  entity_total_first_moments =
    estimator_1_base->getEntityTotalDataFirstMoments( 1 );

  entity_total_second_moments =
    estimator_1_base->getEntityTotalDataSecondMoments( 1 );

  entity_total_third_moments =
    estimator_1_base->getEntityTotalDataThirdMoments( 1 );

  entity_total_fourth_moments =
    estimator_1_base->getEntityTotalDataFourthMoments( 1 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, 4.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 16.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, 64.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 256.0 ) );

  entity_total_first_moments =
    estimator_1_base->getEntityTotalDataFirstMoments( 2 );

  entity_total_second_moments =
    estimator_1_base->getEntityTotalDataSecondMoments( 2 );

  entity_total_third_moments =
    estimator_1_base->getEntityTotalDataThirdMoments( 2 );

  entity_total_fourth_moments =
    estimator_1_base->getEntityTotalDataFourthMoments( 2 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, 4.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 16.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, 64.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 256.0 ) );

  entity_total_first_moments =
    estimator_1_base->getEntityTotalDataFirstMoments( 3 );

  entity_total_second_moments =
    estimator_1_base->getEntityTotalDataSecondMoments( 3 );

  entity_total_third_moments =
    estimator_1_base->getEntityTotalDataThirdMoments( 3 );

  entity_total_fourth_moments =
    estimator_1_base->getEntityTotalDataFourthMoments( 3 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, 4.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 16.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, 64.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 256.0 ) );

  entity_total_first_moments =
    estimator_1_base->getEntityTotalDataFirstMoments( 4 );

  entity_total_second_moments =
    estimator_1_base->getEntityTotalDataSecondMoments( 4 );

  entity_total_third_moments =
    estimator_1_base->getEntityTotalDataThirdMoments( 4 );

  entity_total_fourth_moments =
    estimator_1_base->getEntityTotalDataFourthMoments( 4 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, 4.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 16.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, 64.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 256.0 ) );

  entity_total_first_moments =
    estimator_1_base->getEntityTotalDataFirstMoments( 5 );

  entity_total_second_moments =
    estimator_1_base->getEntityTotalDataSecondMoments( 5 );

  entity_total_third_moments =
    estimator_1_base->getEntityTotalDataThirdMoments( 5 );

  entity_total_fourth_moments =
    estimator_1_base->getEntityTotalDataFourthMoments( 5 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, 4.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 16.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, 64.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 256.0 ) );

  entity_total_first_moments =
    estimator_1_base->getEntityTotalDataFirstMoments( 6 );

  entity_total_second_moments =
    estimator_1_base->getEntityTotalDataSecondMoments( 6 );

  entity_total_third_moments =
    estimator_1_base->getEntityTotalDataThirdMoments( 6 );

  entity_total_fourth_moments =
    estimator_1_base->getEntityTotalDataFourthMoments( 6 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, 4.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 16.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, 64.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 256.0 ) );

  entity_total_first_moments =
    estimator_1_base->getEntityTotalDataFirstMoments( 7 );

  entity_total_second_moments =
    estimator_1_base->getEntityTotalDataSecondMoments( 7 );

  entity_total_third_moments =
    estimator_1_base->getEntityTotalDataThirdMoments( 7 );

  entity_total_fourth_moments =
    estimator_1_base->getEntityTotalDataFourthMoments( 7 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, 4.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 16.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, 64.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 256.0 ) );

  entity_total_first_moments =
    estimator_2_base->getEntityTotalDataFirstMoments( 0 );

  entity_total_second_moments =
    estimator_2_base->getEntityTotalDataSecondMoments( 0 );

  entity_total_third_moments =
    estimator_2_base->getEntityTotalDataThirdMoments( 0 );

  entity_total_fourth_moments =
    estimator_2_base->getEntityTotalDataFourthMoments( 0 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, 4.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 16.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, 64.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 256.0 ) );

  entity_total_first_moments =
    estimator_2_base->getEntityTotalDataFirstMoments( 1 );

  entity_total_second_moments =
    estimator_2_base->getEntityTotalDataSecondMoments( 1 );

  entity_total_third_moments =
    estimator_2_base->getEntityTotalDataThirdMoments( 1 );

  entity_total_fourth_moments =
    estimator_2_base->getEntityTotalDataFourthMoments( 1 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, 4.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 16.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, 64.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 256.0 ) );

  entity_total_first_moments =
    estimator_2_base->getEntityTotalDataFirstMoments( 2 );

  entity_total_second_moments =
    estimator_2_base->getEntityTotalDataSecondMoments( 2 );

  entity_total_third_moments =
    estimator_2_base->getEntityTotalDataThirdMoments( 2 );

  entity_total_fourth_moments =
    estimator_2_base->getEntityTotalDataFourthMoments( 2 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, 4.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 16.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, 64.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 256.0 ) );

  entity_total_first_moments =
    estimator_2_base->getEntityTotalDataFirstMoments( 3 );

  entity_total_second_moments =
    estimator_2_base->getEntityTotalDataSecondMoments( 3 );

  entity_total_third_moments =
    estimator_2_base->getEntityTotalDataThirdMoments( 3 );

  entity_total_fourth_moments =
    estimator_2_base->getEntityTotalDataFourthMoments( 3 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, 4.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 16.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, 64.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 256.0 ) );

  entity_total_first_moments =
    estimator_2_base->getEntityTotalDataFirstMoments( 4 );

  entity_total_second_moments =
    estimator_2_base->getEntityTotalDataSecondMoments( 4 );

  entity_total_third_moments =
    estimator_2_base->getEntityTotalDataThirdMoments( 4 );

  entity_total_fourth_moments =
    estimator_2_base->getEntityTotalDataFourthMoments( 4 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, 4.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 16.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, 64.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 256.0 ) );

  entity_total_first_moments =
    estimator_2_base->getEntityTotalDataFirstMoments( 5 );

  entity_total_second_moments =
    estimator_2_base->getEntityTotalDataSecondMoments( 5 );

  entity_total_third_moments =
    estimator_2_base->getEntityTotalDataThirdMoments( 5 );

  entity_total_fourth_moments =
    estimator_2_base->getEntityTotalDataFourthMoments( 5 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, 4.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 16.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, 64.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 256.0 ) );

  entity_total_first_moments =
    estimator_2_base->getEntityTotalDataFirstMoments( 6 );

  entity_total_second_moments =
    estimator_2_base->getEntityTotalDataSecondMoments( 6 );

  entity_total_third_moments =
    estimator_2_base->getEntityTotalDataThirdMoments( 6 );

  entity_total_fourth_moments =
    estimator_2_base->getEntityTotalDataFourthMoments( 6 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, 4.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 16.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, 64.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 256.0 ) );

  entity_total_first_moments =
    estimator_2_base->getEntityTotalDataFirstMoments( 7 );

  entity_total_second_moments =
    estimator_2_base->getEntityTotalDataSecondMoments( 7 );

  entity_total_third_moments =
    estimator_2_base->getEntityTotalDataThirdMoments( 7 );

  entity_total_fourth_moments =
    estimator_2_base->getEntityTotalDataFourthMoments( 7 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, 4.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 16.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, 64.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 256.0 ) );

  entity_total_first_moments =
    estimator_3_base->getEntityTotalDataFirstMoments( 0 );

  entity_total_second_moments =
    estimator_3_base->getEntityTotalDataSecondMoments( 0 );

  entity_total_third_moments =
    estimator_3_base->getEntityTotalDataThirdMoments( 0 );

  entity_total_fourth_moments =
    estimator_3_base->getEntityTotalDataFourthMoments( 0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );

  entity_total_first_moments =
    estimator_3_base->getEntityTotalDataFirstMoments( 1 );

  entity_total_second_moments =
    estimator_3_base->getEntityTotalDataSecondMoments( 1 );

  entity_total_third_moments =
    estimator_3_base->getEntityTotalDataThirdMoments( 1 );

  entity_total_fourth_moments =
    estimator_3_base->getEntityTotalDataFourthMoments( 1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );

  entity_total_first_moments =
    estimator_3_base->getEntityTotalDataFirstMoments( 2 );

  entity_total_second_moments =
    estimator_3_base->getEntityTotalDataSecondMoments( 2 );

  entity_total_third_moments =
    estimator_3_base->getEntityTotalDataThirdMoments( 2 );

  entity_total_fourth_moments =
    estimator_3_base->getEntityTotalDataFourthMoments( 2 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );

  entity_total_first_moments =
    estimator_3_base->getEntityTotalDataFirstMoments( 3 );

  entity_total_second_moments =
    estimator_3_base->getEntityTotalDataSecondMoments( 3 );

  entity_total_third_moments =
    estimator_3_base->getEntityTotalDataThirdMoments( 3 );

  entity_total_fourth_moments =
    estimator_3_base->getEntityTotalDataFourthMoments( 3 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );

  entity_total_first_moments =
    estimator_3_base->getEntityTotalDataFirstMoments( 4 );

  entity_total_second_moments =
    estimator_3_base->getEntityTotalDataSecondMoments( 4 );

  entity_total_third_moments =
    estimator_3_base->getEntityTotalDataThirdMoments( 4 );

  entity_total_fourth_moments =
    estimator_3_base->getEntityTotalDataFourthMoments( 4 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );

  entity_total_first_moments =
    estimator_3_base->getEntityTotalDataFirstMoments( 5 );

  entity_total_second_moments =
    estimator_3_base->getEntityTotalDataSecondMoments( 5 );

  entity_total_third_moments =
    estimator_3_base->getEntityTotalDataThirdMoments( 5 );

  entity_total_fourth_moments =
    estimator_3_base->getEntityTotalDataFourthMoments( 5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );

  entity_total_first_moments =
    estimator_3_base->getEntityTotalDataFirstMoments( 6 );

  entity_total_second_moments =
    estimator_3_base->getEntityTotalDataSecondMoments( 6 );

  entity_total_third_moments =
    estimator_3_base->getEntityTotalDataThirdMoments( 6 );

  entity_total_fourth_moments =
    estimator_3_base->getEntityTotalDataFourthMoments( 6 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 1, 0.0 ), 1e-15 );

  entity_total_first_moments =
    estimator_3_base->getEntityTotalDataFirstMoments( 7 );

  entity_total_second_moments =
    estimator_3_base->getEntityTotalDataSecondMoments( 7 );

  entity_total_third_moments =
    estimator_3_base->getEntityTotalDataThirdMoments( 7 );

  entity_total_fourth_moments =
    estimator_3_base->getEntityTotalDataFourthMoments( 7 );

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
FRENSIE_UNIT_TEST( HexMeshTrackLengthFluxEstimator,
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
                                                                  hex_mesh ) );

    estimator_1_base = estimator_1;

    estimator_2.reset( new MonteCarlo::MeshTrackLengthFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier>(
                                                                  1,
                                                                  10.0,
                                                                  hex_mesh ) );

    estimator_2_base = estimator_2;

    estimator_3.reset( new MonteCarlo::MeshTrackLengthFluxEstimator<MonteCarlo::WeightAndChargeMultiplier>(
                                                                  2,
                                                                  1.0,
                                                                  hex_mesh ) );

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
    time_bin_boundaries[1] = 3.33564095198152e-11;
    time_bin_boundaries[2] = 6.67128190396304e-11;

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

  FRENSIE_CHECK( !estimator_1_base->hasUncommittedHistoryContribution() );
  FRENSIE_CHECK( !estimator_2_base->hasUncommittedHistoryContribution() );
  FRENSIE_CHECK( !estimator_3_base->hasUncommittedHistoryContribution() );

  double track_length = 2.0;
  double volume = 1.0;
  int num_hexes = 8;

  double start_point_1a[3] = {0.5, 0.5, 0.0};
  double end_point_1a[3] = {0.5, 0.5, 2.0};
  double direction_1a[3] = {0.0, 0.0, 1.0};

  double start_point_1b[3] = {0.5, 0.5, 2.0};
  double end_point_1b[3] = {0.5, 0.5, 0.0};
  double direction_1b[3] = {0.0, 0.0, -1.0};

  double start_point_2a[3] = {0.5, 1.5, 0.0};
  double end_point_2a[3] = {0.5, 1.5, 2.0};
  double direction_2a[3] = {0.0, 0.0, 1.0};

  double start_point_2b[3] = {0.5, 1.5, 2.0};
  double end_point_2b[3] = {0.5, 1.5, 0.0};
  double direction_2b[3] = {0.0, 0.0, -1.0};

  double start_point_3a[3] = {1.5, 0.5, 0.0};
  double end_point_3a[3] = {1.5, 0.5, 2.0};
  double direction_3a[3] = {0.0, 0.0, 1.0};

  double start_point_3b[3] = {1.5, 0.5, 2.0};
  double end_point_3b[3] = {1.5, 0.5, 0.0};
  double direction_3b[3] = {0.0, 0.0, -1.0};

  double start_point_4a[3] = {1.5, 1.5, 0.0};
  double end_point_4a[3] = {1.5, 1.5, 2.0};
  double direction_4a[3] = {0.0, 0.0, 1.0};

  double start_point_4b[3] = {1.5, 1.5, 2.0};
  double end_point_4b[3] = {1.5, 1.5, 0.0};
  double direction_4b[3] = {0.0, 0.0, -1.0};

  unsigned threads =
    Utility::OpenMPProperties::getRequestedNumberOfThreads();

  #pragma omp parallel num_threads( threads )
  {
    // bin 0, 2
    MonteCarlo::PhotonState particle( 0 );
    particle.setEnergy( 1.0 );
    particle.setTime( 6.67128190396304e-11 );
    particle.setWeight( 1.0 );

    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1a,
                                                              end_point_1a );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1b,
                                                              end_point_1b );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2a,
                                                              end_point_2a );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2b,
                                                              end_point_2b );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3a,
                                                              end_point_3a );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3b,
                                                              end_point_3b );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4a,
                                                              end_point_4a );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4b,
                                                              end_point_4b );

    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1a,
                                                              end_point_1a );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1b,
                                                              end_point_1b );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2a,
                                                              end_point_2a );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2b,
                                                              end_point_2b );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3a,
                                                              end_point_3a );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3b,
                                                              end_point_3b );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4a,
                                                              end_point_4a );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4b,
                                                              end_point_4b );

    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1a,
                                                              end_point_1a );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1b,
                                                              end_point_1b );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2a,
                                                              end_point_2a );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2b,
                                                              end_point_2b );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3a,
                                                              end_point_3a );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3b,
                                                              end_point_3b );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4a,
                                                              end_point_4a );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4b,
                                                              end_point_4b );

    // bin 1, 3
    particle.setEnergy( 0.1 );
    particle.setTime( 6.67128190396304e-11 );

    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1a,
                                                              end_point_1a );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1b,
                                                              end_point_1b );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2a,
                                                              end_point_2a );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2b,
                                                              end_point_2b );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3a,
                                                              end_point_3a );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3b,
                                                              end_point_3b );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4a,
                                                              end_point_4a );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4b,
                                                              end_point_4b );

    particle.setWeight( 10.0 );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1a,
                                                              end_point_1a );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1b,
                                                              end_point_1b );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2a,
                                                              end_point_2a );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2b,
                                                              end_point_2b );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3a,
                                                              end_point_3a );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3b,
                                                              end_point_3b );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4a,
                                                              end_point_4a );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4b,
                                                              end_point_4b );

    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1a,
                                                              end_point_1a );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1b,
                                                              end_point_1b );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2a,
                                                              end_point_2a );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2b,
                                                              end_point_2b );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3a,
                                                              end_point_3a );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3b,
                                                              end_point_3b );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4a,
                                                              end_point_4a );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4b,
                                                              end_point_4b );

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
    estimator_1_base->getEntityBinDataFirstMoments( 0 );

  Utility::ArrayView<const double> entity_bin_second_moments =
    estimator_1_base->getEntityBinDataSecondMoments( 0 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 4, 1.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 4, 1.0*threads ) );

  entity_bin_first_moments =
    estimator_1_base->getEntityBinDataFirstMoments( 1 );

  entity_bin_second_moments =
    estimator_1_base->getEntityBinDataSecondMoments( 1 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 4, 1.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 4, 1.0*threads ) );

  entity_bin_first_moments =
    estimator_1_base->getEntityBinDataFirstMoments( 2 );

  entity_bin_second_moments =
    estimator_1_base->getEntityBinDataSecondMoments( 2 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 4, 1.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 4, 1.0*threads ) );

  entity_bin_first_moments =
    estimator_1_base->getEntityBinDataFirstMoments( 3 );

  entity_bin_second_moments =
    estimator_1_base->getEntityBinDataSecondMoments( 3 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 4, 1.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 4, 1.0*threads ) );

  entity_bin_first_moments =
    estimator_1_base->getEntityBinDataFirstMoments( 4 );

  entity_bin_second_moments =
    estimator_1_base->getEntityBinDataSecondMoments( 4 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 4, 1.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 4, 1.0*threads ) );

  entity_bin_first_moments =
    estimator_1_base->getEntityBinDataFirstMoments( 5 );

  entity_bin_second_moments =
    estimator_1_base->getEntityBinDataSecondMoments( 5 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 4, 1.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 4, 1.0*threads ) );

  entity_bin_first_moments =
    estimator_1_base->getEntityBinDataFirstMoments( 6 );

  entity_bin_second_moments =
    estimator_1_base->getEntityBinDataSecondMoments( 6 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 4, 1.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 4, 1.0*threads ) );

  entity_bin_first_moments =
    estimator_1_base->getEntityBinDataFirstMoments( 7 );

  entity_bin_second_moments =
    estimator_1_base->getEntityBinDataSecondMoments( 7 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 4, 1.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 4, 1.0*threads ) );

  entity_bin_first_moments =
    estimator_2_base->getEntityBinDataFirstMoments( 0 );

  entity_bin_second_moments =
    estimator_2_base->getEntityBinDataSecondMoments( 0 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 2, 2.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 2, 4.0*threads ) );

  entity_bin_first_moments =
    estimator_2_base->getEntityBinDataFirstMoments( 1 );

  entity_bin_second_moments =
    estimator_2_base->getEntityBinDataSecondMoments( 1 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 2, 2.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 2, 4.0*threads ) );

  entity_bin_first_moments =
    estimator_2_base->getEntityBinDataFirstMoments( 2 );

  entity_bin_second_moments =
    estimator_2_base->getEntityBinDataSecondMoments( 2 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 2, 2.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 2, 4.0*threads ) );

  entity_bin_first_moments =
    estimator_2_base->getEntityBinDataFirstMoments( 3 );

  entity_bin_second_moments =
    estimator_2_base->getEntityBinDataSecondMoments( 3 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 2, 2.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 2, 4.0*threads ) );

  entity_bin_first_moments =
    estimator_2_base->getEntityBinDataFirstMoments( 4 );

  entity_bin_second_moments =
    estimator_2_base->getEntityBinDataSecondMoments( 4 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 2, 2.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 2, 4.0*threads ) );

  entity_bin_first_moments =
    estimator_2_base->getEntityBinDataFirstMoments( 5 );

  entity_bin_second_moments =
    estimator_2_base->getEntityBinDataSecondMoments( 5 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 2, 2.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 2, 4.0*threads ) );

  entity_bin_first_moments =
    estimator_2_base->getEntityBinDataFirstMoments( 6 );

  entity_bin_second_moments =
    estimator_2_base->getEntityBinDataSecondMoments( 6 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 2, 2.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 2, 4.0*threads ) );

  entity_bin_first_moments =
    estimator_2_base->getEntityBinDataFirstMoments( 7 );

  entity_bin_second_moments =
    estimator_2_base->getEntityBinDataSecondMoments( 7 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 2, 2.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 2, 4.0*threads ) );

  entity_bin_first_moments =
    estimator_3_base->getEntityBinDataFirstMoments( 0 );

  entity_bin_second_moments =
    estimator_3_base->getEntityBinDataSecondMoments( 0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 2, 0.0 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 2, 0.0 ),
                                   1e-15 );

  entity_bin_first_moments =
    estimator_3_base->getEntityBinDataFirstMoments( 1 );

  entity_bin_second_moments =
    estimator_3_base->getEntityBinDataSecondMoments( 1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 2, 0.0 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 2, 0.0 ),
                                   1e-15 );

  entity_bin_first_moments =
    estimator_3_base->getEntityBinDataFirstMoments( 2 );

  entity_bin_second_moments =
    estimator_3_base->getEntityBinDataSecondMoments( 2 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 2, 0.0 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 2, 0.0 ),
                                   1e-15 );

  entity_bin_first_moments =
    estimator_3_base->getEntityBinDataFirstMoments( 3 );

  entity_bin_second_moments =
    estimator_3_base->getEntityBinDataSecondMoments( 3 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 2, 0.0 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 2, 0.0 ),
                                   1e-15 );

  entity_bin_first_moments =
    estimator_3_base->getEntityBinDataFirstMoments( 4 );

  entity_bin_second_moments =
    estimator_3_base->getEntityBinDataSecondMoments( 4 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 2, 0.0 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 2, 0.0 ),
                                   1e-15 );

  entity_bin_first_moments =
    estimator_3_base->getEntityBinDataFirstMoments( 5 );

  entity_bin_second_moments =
    estimator_3_base->getEntityBinDataSecondMoments( 5 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 2, 0.0 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 2, 0.0 ),
                                   1e-15 );

  entity_bin_first_moments =
    estimator_3_base->getEntityBinDataFirstMoments( 6 );

  entity_bin_second_moments =
    estimator_3_base->getEntityBinDataSecondMoments( 6 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 2, 0.0 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 2, 0.0 ),
                                   1e-15 );

  entity_bin_first_moments =
    estimator_3_base->getEntityBinDataFirstMoments( 7 );

  entity_bin_second_moments =
    estimator_3_base->getEntityBinDataSecondMoments( 7 );

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

  FRENSIE_CHECK_EQUAL( total_bin_first_moments,
                       std::vector<double>( 4, 8.0*threads ) );
  FRENSIE_CHECK_EQUAL( total_bin_second_moments,
                       std::vector<double>( 4, 64.0*threads ) );

  total_bin_first_moments =
    estimator_2_base->getTotalBinDataFirstMoments();

  total_bin_second_moments =
    estimator_2_base->getTotalBinDataSecondMoments();

  FRENSIE_CHECK_EQUAL( total_bin_first_moments,
                       std::vector<double>( 2, 16.0*threads ) );
  FRENSIE_CHECK_EQUAL( total_bin_second_moments,
                       std::vector<double>( 2, 256.0*threads ) );

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
    estimator_1_base->getEntityTotalDataFirstMoments( 0 );

  Utility::ArrayView<const double> entity_total_second_moments =
    estimator_1_base->getEntityTotalDataSecondMoments( 0 );

  Utility::ArrayView<const double> entity_total_third_moments =
    estimator_1_base->getEntityTotalDataThirdMoments( 0 );

  Utility::ArrayView<const double> entity_total_fourth_moments =
    estimator_1_base->getEntityTotalDataFourthMoments( 0 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, 4.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 16.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, 64.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 256.0*threads ) );

  entity_total_first_moments =
    estimator_1_base->getEntityTotalDataFirstMoments( 1 );

  entity_total_second_moments =
    estimator_1_base->getEntityTotalDataSecondMoments( 1 );

  entity_total_third_moments =
    estimator_1_base->getEntityTotalDataThirdMoments( 1 );

  entity_total_fourth_moments =
    estimator_1_base->getEntityTotalDataFourthMoments( 1 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, 4.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 16.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, 64.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 256.0*threads ) );

  entity_total_first_moments =
    estimator_1_base->getEntityTotalDataFirstMoments( 2 );

  entity_total_second_moments =
    estimator_1_base->getEntityTotalDataSecondMoments( 2 );

  entity_total_third_moments =
    estimator_1_base->getEntityTotalDataThirdMoments( 2 );

  entity_total_fourth_moments =
    estimator_1_base->getEntityTotalDataFourthMoments( 2 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, 4.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 16.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, 64.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 256.0*threads ) );

  entity_total_first_moments =
    estimator_1_base->getEntityTotalDataFirstMoments( 3 );

  entity_total_second_moments =
    estimator_1_base->getEntityTotalDataSecondMoments( 3 );

  entity_total_third_moments =
    estimator_1_base->getEntityTotalDataThirdMoments( 3 );

  entity_total_fourth_moments =
    estimator_1_base->getEntityTotalDataFourthMoments( 3 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, 4.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 16.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, 64.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 256.0*threads ) );

  entity_total_first_moments =
    estimator_1_base->getEntityTotalDataFirstMoments( 4 );

  entity_total_second_moments =
    estimator_1_base->getEntityTotalDataSecondMoments( 4 );

  entity_total_third_moments =
    estimator_1_base->getEntityTotalDataThirdMoments( 4 );

  entity_total_fourth_moments =
    estimator_1_base->getEntityTotalDataFourthMoments( 4 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, 4.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 16.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, 64.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 256.0*threads ) );

  entity_total_first_moments =
    estimator_1_base->getEntityTotalDataFirstMoments( 5 );

  entity_total_second_moments =
    estimator_1_base->getEntityTotalDataSecondMoments( 5 );

  entity_total_third_moments =
    estimator_1_base->getEntityTotalDataThirdMoments( 5 );

  entity_total_fourth_moments =
    estimator_1_base->getEntityTotalDataFourthMoments( 5 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, 4.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 16.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, 64.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 256.0*threads ) );

  entity_total_first_moments =
    estimator_1_base->getEntityTotalDataFirstMoments( 6 );

  entity_total_second_moments =
    estimator_1_base->getEntityTotalDataSecondMoments( 6 );

  entity_total_third_moments =
    estimator_1_base->getEntityTotalDataThirdMoments( 6 );

  entity_total_fourth_moments =
    estimator_1_base->getEntityTotalDataFourthMoments( 6 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, 4.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 16.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, 64.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 256.0*threads ) );

  entity_total_first_moments =
    estimator_1_base->getEntityTotalDataFirstMoments( 7 );

  entity_total_second_moments =
    estimator_1_base->getEntityTotalDataSecondMoments( 7 );

  entity_total_third_moments =
    estimator_1_base->getEntityTotalDataThirdMoments( 7 );

  entity_total_fourth_moments =
    estimator_1_base->getEntityTotalDataFourthMoments( 7 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, 4.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 16.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, 64.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 256.0*threads ) );

  entity_total_first_moments =
    estimator_2_base->getEntityTotalDataFirstMoments( 0 );

  entity_total_second_moments =
    estimator_2_base->getEntityTotalDataSecondMoments( 0 );

  entity_total_third_moments =
    estimator_2_base->getEntityTotalDataThirdMoments( 0 );

  entity_total_fourth_moments =
    estimator_2_base->getEntityTotalDataFourthMoments( 0 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, 4.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 16.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, 64.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 256.0*threads ) );

  entity_total_first_moments =
    estimator_2_base->getEntityTotalDataFirstMoments( 1 );

  entity_total_second_moments =
    estimator_2_base->getEntityTotalDataSecondMoments( 1 );

  entity_total_third_moments =
    estimator_2_base->getEntityTotalDataThirdMoments( 1 );

  entity_total_fourth_moments =
    estimator_2_base->getEntityTotalDataFourthMoments( 1 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, 4.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 16.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, 64.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 256.0*threads ) );

  entity_total_first_moments =
    estimator_2_base->getEntityTotalDataFirstMoments( 2 );

  entity_total_second_moments =
    estimator_2_base->getEntityTotalDataSecondMoments( 2 );

  entity_total_third_moments =
    estimator_2_base->getEntityTotalDataThirdMoments( 2 );

  entity_total_fourth_moments =
    estimator_2_base->getEntityTotalDataFourthMoments( 2 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, 4.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 16.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, 64.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 256.0*threads ) );

  entity_total_first_moments =
    estimator_2_base->getEntityTotalDataFirstMoments( 3 );

  entity_total_second_moments =
    estimator_2_base->getEntityTotalDataSecondMoments( 3 );

  entity_total_third_moments =
    estimator_2_base->getEntityTotalDataThirdMoments( 3 );

  entity_total_fourth_moments =
    estimator_2_base->getEntityTotalDataFourthMoments( 3 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, 4.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 16.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, 64.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 256.0*threads ) );

  entity_total_first_moments =
    estimator_2_base->getEntityTotalDataFirstMoments( 4 );

  entity_total_second_moments =
    estimator_2_base->getEntityTotalDataSecondMoments( 4 );

  entity_total_third_moments =
    estimator_2_base->getEntityTotalDataThirdMoments( 4 );

  entity_total_fourth_moments =
    estimator_2_base->getEntityTotalDataFourthMoments( 4 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, 4.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 16.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, 64.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 256.0*threads ) );

  entity_total_first_moments =
    estimator_2_base->getEntityTotalDataFirstMoments( 5 );

  entity_total_second_moments =
    estimator_2_base->getEntityTotalDataSecondMoments( 5 );

  entity_total_third_moments =
    estimator_2_base->getEntityTotalDataThirdMoments( 5 );

  entity_total_fourth_moments =
    estimator_2_base->getEntityTotalDataFourthMoments( 5 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, 4.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 16.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, 64.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 256.0*threads ) );

  entity_total_first_moments =
    estimator_2_base->getEntityTotalDataFirstMoments( 6 );

  entity_total_second_moments =
    estimator_2_base->getEntityTotalDataSecondMoments( 6 );

  entity_total_third_moments =
    estimator_2_base->getEntityTotalDataThirdMoments( 6 );

  entity_total_fourth_moments =
    estimator_2_base->getEntityTotalDataFourthMoments( 6 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, 4.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 16.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, 64.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 256.0*threads ) );

  entity_total_first_moments =
    estimator_2_base->getEntityTotalDataFirstMoments( 7 );

  entity_total_second_moments =
    estimator_2_base->getEntityTotalDataSecondMoments( 7 );

  entity_total_third_moments =
    estimator_2_base->getEntityTotalDataThirdMoments( 7 );

  entity_total_fourth_moments =
    estimator_2_base->getEntityTotalDataFourthMoments( 7 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 1, 4.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 1, 16.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 1, 64.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 1, 256.0*threads ) );

  entity_total_first_moments =
    estimator_3_base->getEntityTotalDataFirstMoments( 0 );

  entity_total_second_moments =
    estimator_3_base->getEntityTotalDataSecondMoments( 0 );

  entity_total_third_moments =
    estimator_3_base->getEntityTotalDataThirdMoments( 0 );

  entity_total_fourth_moments =
    estimator_3_base->getEntityTotalDataFourthMoments( 0 );

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
    estimator_3_base->getEntityTotalDataFirstMoments( 1 );

  entity_total_second_moments =
    estimator_3_base->getEntityTotalDataSecondMoments( 1 );

  entity_total_third_moments =
    estimator_3_base->getEntityTotalDataThirdMoments( 1 );

  entity_total_fourth_moments =
    estimator_3_base->getEntityTotalDataFourthMoments( 1 );

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
    estimator_3_base->getEntityTotalDataFirstMoments( 2 );

  entity_total_second_moments =
    estimator_3_base->getEntityTotalDataSecondMoments( 2 );

  entity_total_third_moments =
    estimator_3_base->getEntityTotalDataThirdMoments( 2 );

  entity_total_fourth_moments =
    estimator_3_base->getEntityTotalDataFourthMoments( 2 );

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
    estimator_3_base->getEntityTotalDataFirstMoments( 3 );

  entity_total_second_moments =
    estimator_3_base->getEntityTotalDataSecondMoments( 3 );

  entity_total_third_moments =
    estimator_3_base->getEntityTotalDataThirdMoments( 3 );

  entity_total_fourth_moments =
    estimator_3_base->getEntityTotalDataFourthMoments( 3 );

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
    estimator_3_base->getEntityTotalDataFirstMoments( 4 );

  entity_total_second_moments =
    estimator_3_base->getEntityTotalDataSecondMoments( 4 );

  entity_total_third_moments =
    estimator_3_base->getEntityTotalDataThirdMoments( 4 );

  entity_total_fourth_moments =
    estimator_3_base->getEntityTotalDataFourthMoments( 4 );

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
    estimator_3_base->getEntityTotalDataFirstMoments( 5 );

  entity_total_second_moments =
    estimator_3_base->getEntityTotalDataSecondMoments( 5 );

  entity_total_third_moments =
    estimator_3_base->getEntityTotalDataThirdMoments( 5 );

  entity_total_fourth_moments =
    estimator_3_base->getEntityTotalDataFourthMoments( 5 );

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
    estimator_3_base->getEntityTotalDataFirstMoments( 6 );

  entity_total_second_moments =
    estimator_3_base->getEntityTotalDataSecondMoments( 6 );

  entity_total_third_moments =
    estimator_3_base->getEntityTotalDataThirdMoments( 6 );

  entity_total_fourth_moments =
    estimator_3_base->getEntityTotalDataFourthMoments( 6 );

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
    estimator_3_base->getEntityTotalDataFirstMoments( 7 );

  entity_total_second_moments =
    estimator_3_base->getEntityTotalDataSecondMoments( 7 );

  entity_total_third_moments =
    estimator_3_base->getEntityTotalDataThirdMoments( 7 );

  entity_total_fourth_moments =
    estimator_3_base->getEntityTotalDataFourthMoments( 7 );

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

  std::string archive_base_name( "test_hex_mesh_track_length_flux_estimator" );
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
                                                                  hex_mesh ) );

      estimator_1_base = estimator_1;

      estimator_2.reset( new MonteCarlo::MeshTrackLengthFluxEstimator<MonteCarlo::WeightAndEnergyMultiplier>(
                                                                  1,
                                                                  10.0,
                                                                  hex_mesh ) );

      estimator_2_base = estimator_2;

      estimator_3.reset( new MonteCarlo::MeshTrackLengthFluxEstimator<MonteCarlo::WeightAndChargeMultiplier>(
                                                                  2,
                                                                  1.0,
                                                                  hex_mesh ) );

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
      time_bin_boundaries[1] = 3.33564095198152e-11;
      time_bin_boundaries[2] = 6.67128190396304e-11;

      estimator_1_base->setDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION>(
						       time_bin_boundaries );

      // Set the particle types
      std::vector<MonteCarlo::ParticleType> particle_types( 1 );
      particle_types[0] = MonteCarlo::PHOTON;

      estimator_1_base->setParticleTypes( particle_types );
      estimator_2_base->setParticleTypes( particle_types );
      estimator_3_base->setParticleTypes( particle_types );
    }

    double start_point_1a[3] = {0.5, 0.5, 0.0};
    double end_point_1a[3] = {0.5, 0.5, 2.0};
    double direction_1a[3] = {0.0, 0.0, 1.0};

    double start_point_1b[3] = {0.5, 0.5, 2.0};
    double end_point_1b[3] = {0.5, 0.5, 0.0};
    double direction_1b[3] = {0.0, 0.0, -1.0};

    double start_point_2a[3] = {0.5, 1.5, 0.0};
    double end_point_2a[3] = {0.5, 1.5, 2.0};
    double direction_2a[3] = {0.0, 0.0, 1.0};

    double start_point_2b[3] = {0.5, 1.5, 2.0};
    double end_point_2b[3] = {0.5, 1.5, 0.0};
    double direction_2b[3] = {0.0, 0.0, -1.0};

    double start_point_3a[3] = {1.5, 0.5, 0.0};
    double end_point_3a[3] = {1.5, 0.5, 2.0};
    double direction_3a[3] = {0.0, 0.0, 1.0};

    double start_point_3b[3] = {1.5, 0.5, 2.0};
    double end_point_3b[3] = {1.5, 0.5, 0.0};
    double direction_3b[3] = {0.0, 0.0, -1.0};

    double start_point_4a[3] = {1.5, 1.5, 0.0};
    double end_point_4a[3] = {1.5, 1.5, 2.0};
    double direction_4a[3] = {0.0, 0.0, 1.0};

    double start_point_4b[3] = {1.5, 1.5, 2.0};
    double end_point_4b[3] = {1.5, 1.5, 0.0};
    double direction_4b[3] = {0.0, 0.0, -1.0};

    // bin 0, 2
    MonteCarlo::PhotonState particle( 0 );
    particle.setEnergy( 1.0 );
    particle.setTime( 6.67128190396304e-11 );
    particle.setWeight( 1.0 );

    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1a,
                                                              end_point_1a );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1b,
                                                              end_point_1b );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2a,
                                                              end_point_2a );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2b,
                                                              end_point_2b );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3a,
                                                              end_point_3a );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3b,
                                                              end_point_3b );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4a,
                                                              end_point_4a );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4b,
                                                              end_point_4b );

    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1a,
                                                              end_point_1a );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1b,
                                                              end_point_1b );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2a,
                                                              end_point_2a );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2b,
                                                              end_point_2b );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3a,
                                                              end_point_3a );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3b,
                                                              end_point_3b );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4a,
                                                              end_point_4a );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4b,
                                                              end_point_4b );

    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1a,
                                                              end_point_1a );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1b,
                                                              end_point_1b );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2a,
                                                              end_point_2a );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2b,
                                                              end_point_2b );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3a,
                                                              end_point_3a );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3b,
                                                              end_point_3b );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4a,
                                                              end_point_4a );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4b,
                                                              end_point_4b );
    // bin 1, 3
    particle.setEnergy( 0.1 );
    particle.setTime( 6.67128190396304e-11 );

    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1a,
                                                              end_point_1a );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1b,
                                                              end_point_1b );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2a,
                                                              end_point_2a );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2b,
                                                              end_point_2b );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3a,
                                                              end_point_3a );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3b,
                                                              end_point_3b );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4a,
                                                              end_point_4a );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4b,
                                                              end_point_4b );

    particle.setWeight( 10.0 );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1a,
                                                              end_point_1a );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1b,
                                                              end_point_1b );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2a,
                                                              end_point_2a );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2b,
                                                              end_point_2b );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3a,
                                                              end_point_3a );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3b,
                                                              end_point_3b );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4a,
                                                              end_point_4a );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4b,
                                                              end_point_4b );

    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1a,
                                                              end_point_1a );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1b,
                                                              end_point_1b );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2a,
                                                              end_point_2a );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2b,
                                                              end_point_2b );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3a,
                                                              end_point_3a );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3b,
                                                              end_point_3b );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4a,
                                                              end_point_4a );
    estimator_3->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4b,
                                                              end_point_4b );

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

    FRENSIE_CHECK_EQUAL( entity_ids.size(), 8 );
    FRENSIE_CHECK( entity_ids.find( 0 ) != entity_ids.end() );
    FRENSIE_CHECK( entity_ids.find( 1 ) != entity_ids.end() );
    FRENSIE_CHECK( entity_ids.find( 2 ) != entity_ids.end() );
    FRENSIE_CHECK( entity_ids.find( 3 ) != entity_ids.end() );
    FRENSIE_CHECK( entity_ids.find( 4 ) != entity_ids.end() );
    FRENSIE_CHECK( entity_ids.find( 5 ) != entity_ids.end() );
    FRENSIE_CHECK( entity_ids.find( 6 ) != entity_ids.end() );
    FRENSIE_CHECK( entity_ids.find( 7 ) != entity_ids.end() );

    FRENSIE_CHECK_EQUAL( estimator_1_base->getEntityNormConstant( 0 ), 1.0 );
    FRENSIE_CHECK_EQUAL( estimator_1_base->getEntityNormConstant( 1 ), 1.0 );
    FRENSIE_CHECK_EQUAL( estimator_1_base->getEntityNormConstant( 2 ), 1.0 );
    FRENSIE_CHECK_EQUAL( estimator_1_base->getEntityNormConstant( 3 ), 1.0 );
    FRENSIE_CHECK_EQUAL( estimator_1_base->getEntityNormConstant( 4 ), 1.0 );
    FRENSIE_CHECK_EQUAL( estimator_1_base->getEntityNormConstant( 5 ), 1.0 );
    FRENSIE_CHECK_EQUAL( estimator_1_base->getEntityNormConstant( 6 ), 1.0 );
    FRENSIE_CHECK_EQUAL( estimator_1_base->getEntityNormConstant( 7 ), 1.0 );
    FRENSIE_CHECK_EQUAL( estimator_1_base->getTotalNormConstant(), 8.0 );

    // Check the entity bin data moments
    Utility::ArrayView<const double> entity_bin_first_moments =
      estimator_1_base->getEntityBinDataFirstMoments( 0 );

    Utility::ArrayView<const double> entity_bin_second_moments =
      estimator_1_base->getEntityBinDataSecondMoments( 0 );

    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 4, 1.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 4, 1.0 ) );

    entity_bin_first_moments =
      estimator_1_base->getEntityBinDataFirstMoments( 1 );

    entity_bin_second_moments =
      estimator_1_base->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 4, 1.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 4, 1.0 ) );

    entity_bin_first_moments =
      estimator_1_base->getEntityBinDataFirstMoments( 2 );

    entity_bin_second_moments =
      estimator_1_base->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 4, 1.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 4, 1.0 ) );

    entity_bin_first_moments =
      estimator_1_base->getEntityBinDataFirstMoments( 3 );

    entity_bin_second_moments =
      estimator_1_base->getEntityBinDataSecondMoments( 3 );

    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 4, 1.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 4, 1.0 ) );

    entity_bin_first_moments =
      estimator_1_base->getEntityBinDataFirstMoments( 4 );

    entity_bin_second_moments =
      estimator_1_base->getEntityBinDataSecondMoments( 4 );

    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 4, 1.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 4, 1.0 ) );

    entity_bin_first_moments =
      estimator_1_base->getEntityBinDataFirstMoments( 5 );

    entity_bin_second_moments =
      estimator_1_base->getEntityBinDataSecondMoments( 5 );

    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 4, 1.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 4, 1.0 ) );

    entity_bin_first_moments =
      estimator_1_base->getEntityBinDataFirstMoments( 6 );

    entity_bin_second_moments =
      estimator_1_base->getEntityBinDataSecondMoments( 6 );

    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 4, 1.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 4, 1.0 ) );

    entity_bin_first_moments =
      estimator_1_base->getEntityBinDataFirstMoments( 7 );

    entity_bin_second_moments =
      estimator_1_base->getEntityBinDataSecondMoments( 7 );

    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 4, 1.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 4, 1.0 ) );

    // Check the total bin data moments
    Utility::ArrayView<const double> total_bin_first_moments =
      estimator_1_base->getTotalBinDataFirstMoments();

    Utility::ArrayView<const double> total_bin_second_moments =
      estimator_1_base->getTotalBinDataSecondMoments();

    FRENSIE_CHECK_EQUAL( total_bin_first_moments,
                         std::vector<double>( 4, 8.0 ) );
    FRENSIE_CHECK_EQUAL( total_bin_second_moments,
                         std::vector<double>( 4, 64.0 ) );

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
                         std::vector<double>( 1, 4.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                         std::vector<double>( 1, 16.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                         std::vector<double>( 1, 64.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                         std::vector<double>( 1, 256.0 ) );

    entity_total_first_moments =
      estimator_1_base->getEntityTotalDataFirstMoments( 1 );

    entity_total_second_moments =
      estimator_1_base->getEntityTotalDataSecondMoments( 1 );

    entity_total_third_moments =
      estimator_1_base->getEntityTotalDataThirdMoments( 1 );

    entity_total_fourth_moments =
      estimator_1_base->getEntityTotalDataFourthMoments( 1 );

    FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                         std::vector<double>( 1, 4.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                         std::vector<double>( 1, 16.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                         std::vector<double>( 1, 64.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                         std::vector<double>( 1, 256.0 ) );

    entity_total_first_moments =
      estimator_1_base->getEntityTotalDataFirstMoments( 2 );

    entity_total_second_moments =
      estimator_1_base->getEntityTotalDataSecondMoments( 2 );

    entity_total_third_moments =
      estimator_1_base->getEntityTotalDataThirdMoments( 2 );

    entity_total_fourth_moments =
      estimator_1_base->getEntityTotalDataFourthMoments( 2 );

    FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                         std::vector<double>( 1, 4.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                         std::vector<double>( 1, 16.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                         std::vector<double>( 1, 64.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                         std::vector<double>( 1, 256.0 ) );

    entity_total_first_moments =
      estimator_1_base->getEntityTotalDataFirstMoments( 3 );

    entity_total_second_moments =
      estimator_1_base->getEntityTotalDataSecondMoments( 3 );

    entity_total_third_moments =
      estimator_1_base->getEntityTotalDataThirdMoments( 3 );

    entity_total_fourth_moments =
      estimator_1_base->getEntityTotalDataFourthMoments( 3 );

    FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                         std::vector<double>( 1, 4.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                         std::vector<double>( 1, 16.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                         std::vector<double>( 1, 64.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                         std::vector<double>( 1, 256.0 ) );

    entity_total_first_moments =
      estimator_1_base->getEntityTotalDataFirstMoments( 4 );

    entity_total_second_moments =
      estimator_1_base->getEntityTotalDataSecondMoments( 4 );

    entity_total_third_moments =
      estimator_1_base->getEntityTotalDataThirdMoments( 4 );

    entity_total_fourth_moments =
      estimator_1_base->getEntityTotalDataFourthMoments( 4 );

    FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                         std::vector<double>( 1, 4.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                         std::vector<double>( 1, 16.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                         std::vector<double>( 1, 64.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                         std::vector<double>( 1, 256.0 ) );

    entity_total_first_moments =
      estimator_1_base->getEntityTotalDataFirstMoments( 5 );

    entity_total_second_moments =
      estimator_1_base->getEntityTotalDataSecondMoments( 5 );

    entity_total_third_moments =
      estimator_1_base->getEntityTotalDataThirdMoments( 5 );

    entity_total_fourth_moments =
      estimator_1_base->getEntityTotalDataFourthMoments( 5 );

    FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                         std::vector<double>( 1, 4.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                         std::vector<double>( 1, 16.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                         std::vector<double>( 1, 64.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                         std::vector<double>( 1, 256.0 ) );

    entity_total_first_moments =
      estimator_1_base->getEntityTotalDataFirstMoments( 6 );

    entity_total_second_moments =
      estimator_1_base->getEntityTotalDataSecondMoments( 6 );

    entity_total_third_moments =
      estimator_1_base->getEntityTotalDataThirdMoments( 6 );

    entity_total_fourth_moments =
      estimator_1_base->getEntityTotalDataFourthMoments( 6 );

    FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                         std::vector<double>( 1, 4.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                         std::vector<double>( 1, 16.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                         std::vector<double>( 1, 64.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                         std::vector<double>( 1, 256.0 ) );

    entity_total_first_moments =
      estimator_1_base->getEntityTotalDataFirstMoments( 7 );

    entity_total_second_moments =
      estimator_1_base->getEntityTotalDataSecondMoments( 7 );

    entity_total_third_moments =
      estimator_1_base->getEntityTotalDataThirdMoments( 7 );

    entity_total_fourth_moments =
      estimator_1_base->getEntityTotalDataFourthMoments( 7 );

    FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                         std::vector<double>( 1, 4.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                         std::vector<double>( 1, 16.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                         std::vector<double>( 1, 64.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                         std::vector<double>( 1, 256.0 ) );

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

    // Check that the correct contribution method is still used after restoring
    double start_point_1a[3] = {0.5, 0.5, 0.0};
    double end_point_1a[3] = {0.5, 0.5, 2.0};
    double direction_1a[3] = {0.0, 0.0, 1.0};

    double start_point_1b[3] = {0.5, 0.5, 2.0};
    double end_point_1b[3] = {0.5, 0.5, 0.0};
    double direction_1b[3] = {0.0, 0.0, -1.0};

    double start_point_2a[3] = {0.5, 1.5, 0.0};
    double end_point_2a[3] = {0.5, 1.5, 2.0};
    double direction_2a[3] = {0.0, 0.0, 1.0};

    double start_point_2b[3] = {0.5, 1.5, 2.0};
    double end_point_2b[3] = {0.5, 1.5, 0.0};
    double direction_2b[3] = {0.0, 0.0, -1.0};

    double start_point_3a[3] = {1.5, 0.5, 0.0};
    double end_point_3a[3] = {1.5, 0.5, 2.0};
    double direction_3a[3] = {0.0, 0.0, 1.0};

    double start_point_3b[3] = {1.5, 0.5, 2.0};
    double end_point_3b[3] = {1.5, 0.5, 0.0};
    double direction_3b[3] = {0.0, 0.0, -1.0};

    double start_point_4a[3] = {1.5, 1.5, 0.0};
    double end_point_4a[3] = {1.5, 1.5, 2.0};
    double direction_4a[3] = {0.0, 0.0, 1.0};

    double start_point_4b[3] = {1.5, 1.5, 2.0};
    double end_point_4b[3] = {1.5, 1.5, 0.0};
    double direction_4b[3] = {0.0, 0.0, -1.0};

    // bin 0, 2
    MonteCarlo::PhotonState particle( 0 );
    particle.setEnergy( 1.0 );
    particle.setTime( 6.67128190396304e-11 );
    particle.setWeight( 1.0 );

    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1a,
                                                              end_point_1a );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1b,
                                                              end_point_1b );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2a,
                                                              end_point_2a );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2b,
                                                              end_point_2b );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3a,
                                                              end_point_3a );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3b,
                                                              end_point_3b );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4a,
                                                              end_point_4a );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4b,
                                                              end_point_4b );
    // bin 1, 3
    particle.setEnergy( 0.1 );
    particle.setTime( 6.67128190396304e-11 );

    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1a,
                                                              end_point_1a );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1b,
                                                              end_point_1b );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2a,
                                                              end_point_2a );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2b,
                                                              end_point_2b );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3a,
                                                              end_point_3a );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3b,
                                                              end_point_3b );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4a,
                                                              end_point_4a );
    estimator_1->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4b,
                                                              end_point_4b );
    // Commit the contributions
    estimator_1_base->commitHistoryContribution();

    entity_bin_first_moments =
      estimator_1_base->getEntityBinDataFirstMoments( 0 );

    entity_bin_second_moments =
      estimator_1_base->getEntityBinDataSecondMoments( 0 );

    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 4, 2.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 4, 2.0 ) );

    entity_bin_first_moments =
      estimator_1_base->getEntityBinDataFirstMoments( 1 );

    entity_bin_second_moments =
      estimator_1_base->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 4, 2.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 4, 2.0 ) );

    entity_bin_first_moments =
      estimator_1_base->getEntityBinDataFirstMoments( 2 );

    entity_bin_second_moments =
      estimator_1_base->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 4, 2.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 4, 2.0 ) );

    entity_bin_first_moments =
      estimator_1_base->getEntityBinDataFirstMoments( 3 );

    entity_bin_second_moments =
      estimator_1_base->getEntityBinDataSecondMoments( 3 );

    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 4, 2.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 4, 2.0 ) );

    entity_bin_first_moments =
      estimator_1_base->getEntityBinDataFirstMoments( 4 );

    entity_bin_second_moments =
      estimator_1_base->getEntityBinDataSecondMoments( 4 );

    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 4, 2.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 4, 2.0 ) );

    entity_bin_first_moments =
      estimator_1_base->getEntityBinDataFirstMoments( 5 );

    entity_bin_second_moments =
      estimator_1_base->getEntityBinDataSecondMoments( 5 );

    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 4, 2.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 4, 2.0 ) );

    entity_bin_first_moments =
      estimator_1_base->getEntityBinDataFirstMoments( 6 );

    entity_bin_second_moments =
      estimator_1_base->getEntityBinDataSecondMoments( 6 );

    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 4, 2.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 4, 2.0 ) );

    entity_bin_first_moments =
      estimator_1_base->getEntityBinDataFirstMoments( 7 );

    entity_bin_second_moments =
      estimator_1_base->getEntityBinDataSecondMoments( 7 );

    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 4, 2.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 4, 2.0 ) );
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

    FRENSIE_CHECK_EQUAL( entity_ids.size(), 8 );
    FRENSIE_CHECK( entity_ids.find( 0 ) != entity_ids.end() );
    FRENSIE_CHECK( entity_ids.find( 1 ) != entity_ids.end() );
    FRENSIE_CHECK( entity_ids.find( 2 ) != entity_ids.end() );
    FRENSIE_CHECK( entity_ids.find( 3 ) != entity_ids.end() );
    FRENSIE_CHECK( entity_ids.find( 4 ) != entity_ids.end() );
    FRENSIE_CHECK( entity_ids.find( 5 ) != entity_ids.end() );
    FRENSIE_CHECK( entity_ids.find( 6 ) != entity_ids.end() );
    FRENSIE_CHECK( entity_ids.find( 7 ) != entity_ids.end() );

    FRENSIE_CHECK_EQUAL( estimator_2_base->getEntityNormConstant( 0 ), 1.0 );
    FRENSIE_CHECK_EQUAL( estimator_2_base->getEntityNormConstant( 1 ), 1.0 );
    FRENSIE_CHECK_EQUAL( estimator_2_base->getEntityNormConstant( 2 ), 1.0 );
    FRENSIE_CHECK_EQUAL( estimator_2_base->getEntityNormConstant( 3 ), 1.0 );
    FRENSIE_CHECK_EQUAL( estimator_2_base->getEntityNormConstant( 4 ), 1.0 );
    FRENSIE_CHECK_EQUAL( estimator_2_base->getEntityNormConstant( 5 ), 1.0 );
    FRENSIE_CHECK_EQUAL( estimator_2_base->getEntityNormConstant( 6 ), 1.0 );
    FRENSIE_CHECK_EQUAL( estimator_2_base->getEntityNormConstant( 7 ), 1.0 );
    FRENSIE_CHECK_EQUAL( estimator_2_base->getTotalNormConstant(), 8.0 );

    // Check the entity bin data moments
    Utility::ArrayView<const double> entity_bin_first_moments =
      estimator_2_base->getEntityBinDataFirstMoments( 0 );

    Utility::ArrayView<const double> entity_bin_second_moments =
      estimator_2_base->getEntityBinDataSecondMoments( 0 );

    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 2, 2.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 2, 4.0 ) );

    entity_bin_first_moments =
      estimator_2_base->getEntityBinDataFirstMoments( 1 );

    entity_bin_second_moments =
      estimator_2_base->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 2, 2.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 2, 4.0 ) );

    entity_bin_first_moments =
      estimator_2_base->getEntityBinDataFirstMoments( 2 );

    entity_bin_second_moments =
      estimator_2_base->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 2, 2.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 2, 4.0 ) );

    entity_bin_first_moments =
      estimator_2_base->getEntityBinDataFirstMoments( 3 );

    entity_bin_second_moments =
      estimator_2_base->getEntityBinDataSecondMoments( 3 );

    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 2, 2.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 2, 4.0 ) );

    entity_bin_first_moments =
      estimator_2_base->getEntityBinDataFirstMoments( 4 );

    entity_bin_second_moments =
      estimator_2_base->getEntityBinDataSecondMoments( 4 );

    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 2, 2.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 2, 4.0 ) );

    entity_bin_first_moments =
      estimator_2_base->getEntityBinDataFirstMoments( 5 );

    entity_bin_second_moments =
      estimator_2_base->getEntityBinDataSecondMoments( 5 );

    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 2, 2.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 2, 4.0 ) );

    entity_bin_first_moments =
      estimator_2_base->getEntityBinDataFirstMoments( 6 );

    entity_bin_second_moments =
      estimator_2_base->getEntityBinDataSecondMoments( 6 );

    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 2, 2.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 2, 4.0 ) );

    entity_bin_first_moments =
      estimator_2_base->getEntityBinDataFirstMoments( 7 );

    entity_bin_second_moments =
      estimator_2_base->getEntityBinDataSecondMoments( 7 );

    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 2, 2.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 2, 4.0 ) );

    // Check the total bin data moments
    Utility::ArrayView<const double> total_bin_first_moments =
      estimator_2_base->getTotalBinDataFirstMoments();

    Utility::ArrayView<const double> total_bin_second_moments =
      estimator_2_base->getTotalBinDataSecondMoments();

    FRENSIE_CHECK_EQUAL( total_bin_first_moments,
                         std::vector<double>( 2, 16.0 ) );
    FRENSIE_CHECK_EQUAL( total_bin_second_moments,
                         std::vector<double>( 2, 256.0 ) );

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
                         std::vector<double>( 1, 4.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                         std::vector<double>( 1, 16.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                         std::vector<double>( 1, 64.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                         std::vector<double>( 1, 256.0 ) );

    entity_total_first_moments =
      estimator_2_base->getEntityTotalDataFirstMoments( 1 );

    entity_total_second_moments =
      estimator_2_base->getEntityTotalDataSecondMoments( 1 );

    entity_total_third_moments =
      estimator_2_base->getEntityTotalDataThirdMoments( 1 );

    entity_total_fourth_moments =
      estimator_2_base->getEntityTotalDataFourthMoments( 1 );

    FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                         std::vector<double>( 1, 4.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                         std::vector<double>( 1, 16.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                         std::vector<double>( 1, 64.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                         std::vector<double>( 1, 256.0 ) );

    entity_total_first_moments =
      estimator_2_base->getEntityTotalDataFirstMoments( 2 );

    entity_total_second_moments =
      estimator_2_base->getEntityTotalDataSecondMoments( 2 );

    entity_total_third_moments =
      estimator_2_base->getEntityTotalDataThirdMoments( 2 );

    entity_total_fourth_moments =
      estimator_2_base->getEntityTotalDataFourthMoments( 2 );

    FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                         std::vector<double>( 1, 4.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                         std::vector<double>( 1, 16.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                         std::vector<double>( 1, 64.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                         std::vector<double>( 1, 256.0 ) );

    entity_total_first_moments =
      estimator_2_base->getEntityTotalDataFirstMoments( 3 );

    entity_total_second_moments =
      estimator_2_base->getEntityTotalDataSecondMoments( 3 );

    entity_total_third_moments =
      estimator_2_base->getEntityTotalDataThirdMoments( 3 );

    entity_total_fourth_moments =
      estimator_2_base->getEntityTotalDataFourthMoments( 3 );

    FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                         std::vector<double>( 1, 4.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                         std::vector<double>( 1, 16.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                         std::vector<double>( 1, 64.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                         std::vector<double>( 1, 256.0 ) );

    entity_total_first_moments =
      estimator_2_base->getEntityTotalDataFirstMoments( 4 );

    entity_total_second_moments =
      estimator_2_base->getEntityTotalDataSecondMoments( 4 );

    entity_total_third_moments =
      estimator_2_base->getEntityTotalDataThirdMoments( 4 );

    entity_total_fourth_moments =
      estimator_2_base->getEntityTotalDataFourthMoments( 4 );

    FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                         std::vector<double>( 1, 4.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                         std::vector<double>( 1, 16.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                         std::vector<double>( 1, 64.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                         std::vector<double>( 1, 256.0 ) );

    entity_total_first_moments =
      estimator_2_base->getEntityTotalDataFirstMoments( 5 );

    entity_total_second_moments =
      estimator_2_base->getEntityTotalDataSecondMoments( 5 );

    entity_total_third_moments =
      estimator_2_base->getEntityTotalDataThirdMoments( 5 );

    entity_total_fourth_moments =
      estimator_2_base->getEntityTotalDataFourthMoments( 5 );

    FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                         std::vector<double>( 1, 4.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                         std::vector<double>( 1, 16.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                         std::vector<double>( 1, 64.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                         std::vector<double>( 1, 256.0 ) );

    entity_total_first_moments =
      estimator_2_base->getEntityTotalDataFirstMoments( 6 );

    entity_total_second_moments =
      estimator_2_base->getEntityTotalDataSecondMoments( 6 );

    entity_total_third_moments =
      estimator_2_base->getEntityTotalDataThirdMoments( 6 );

    entity_total_fourth_moments =
      estimator_2_base->getEntityTotalDataFourthMoments( 6 );

    FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                         std::vector<double>( 1, 4.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                         std::vector<double>( 1, 16.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                         std::vector<double>( 1, 64.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                         std::vector<double>( 1, 256.0 ) );

    entity_total_first_moments =
      estimator_2_base->getEntityTotalDataFirstMoments( 7 );

    entity_total_second_moments =
      estimator_2_base->getEntityTotalDataSecondMoments( 7 );

    entity_total_third_moments =
      estimator_2_base->getEntityTotalDataThirdMoments( 7 );

    entity_total_fourth_moments =
      estimator_2_base->getEntityTotalDataFourthMoments( 7 );

    FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                         std::vector<double>( 1, 4.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                         std::vector<double>( 1, 16.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                         std::vector<double>( 1, 64.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                         std::vector<double>( 1, 256.0 ) );

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

    // Check that the correct contribution method is still used after restoring
    double start_point_1a[3] = {0.5, 0.5, 0.0};
    double end_point_1a[3] = {0.5, 0.5, 2.0};
    double direction_1a[3] = {0.0, 0.0, 1.0};

    double start_point_1b[3] = {0.5, 0.5, 2.0};
    double end_point_1b[3] = {0.5, 0.5, 0.0};
    double direction_1b[3] = {0.0, 0.0, -1.0};

    double start_point_2a[3] = {0.5, 1.5, 0.0};
    double end_point_2a[3] = {0.5, 1.5, 2.0};
    double direction_2a[3] = {0.0, 0.0, 1.0};

    double start_point_2b[3] = {0.5, 1.5, 2.0};
    double end_point_2b[3] = {0.5, 1.5, 0.0};
    double direction_2b[3] = {0.0, 0.0, -1.0};

    double start_point_3a[3] = {1.5, 0.5, 0.0};
    double end_point_3a[3] = {1.5, 0.5, 2.0};
    double direction_3a[3] = {0.0, 0.0, 1.0};

    double start_point_3b[3] = {1.5, 0.5, 2.0};
    double end_point_3b[3] = {1.5, 0.5, 0.0};
    double direction_3b[3] = {0.0, 0.0, -1.0};

    double start_point_4a[3] = {1.5, 1.5, 0.0};
    double end_point_4a[3] = {1.5, 1.5, 2.0};
    double direction_4a[3] = {0.0, 0.0, 1.0};

    double start_point_4b[3] = {1.5, 1.5, 2.0};
    double end_point_4b[3] = {1.5, 1.5, 0.0};
    double direction_4b[3] = {0.0, 0.0, -1.0};

    // bin 0, 2
    MonteCarlo::PhotonState particle( 0 );
    particle.setEnergy( 1.0 );
    particle.setTime( 6.67128190396304e-11 );
    particle.setWeight( 1.0 );

    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1a,
                                                              end_point_1a );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1b,
                                                              end_point_1b );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2a,
                                                              end_point_2a );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2b,
                                                              end_point_2b );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3a,
                                                              end_point_3a );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3b,
                                                              end_point_3b );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4a,
                                                              end_point_4a );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4b,
                                                              end_point_4b );
    // bin 1, 3
    particle.setEnergy( 0.1 );
    particle.setTime( 6.67128190396304e-11 );
    particle.setWeight( 10.0 );

    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1a,
                                                              end_point_1a );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_1b,
                                                              end_point_1b );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2a,
                                                              end_point_2a );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_2b,
                                                              end_point_2b );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3a,
                                                              end_point_3a );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_3b,
                                                              end_point_3b );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4a,
                                                              end_point_4a );
    estimator_2->updateFromGlobalParticleSubtrackEndingEvent( particle,
                                                              start_point_4b,
                                                              end_point_4b );

    // Commit the contributions
    estimator_1_base->commitHistoryContribution();
    estimator_2_base->commitHistoryContribution();

    // Check the entity bin data moments
    entity_bin_first_moments =
      estimator_2_base->getEntityBinDataFirstMoments( 0 );

    entity_bin_second_moments =
      estimator_2_base->getEntityBinDataSecondMoments( 0 );

    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 2, 4.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 2, 8.0 ) );

    entity_bin_first_moments =
      estimator_2_base->getEntityBinDataFirstMoments( 1 );

    entity_bin_second_moments =
      estimator_2_base->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 2, 4.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 2, 8.0 ) );

    entity_bin_first_moments =
      estimator_2_base->getEntityBinDataFirstMoments( 2 );

    entity_bin_second_moments =
      estimator_2_base->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 2, 4.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 2, 8.0 ) );

    entity_bin_first_moments =
      estimator_2_base->getEntityBinDataFirstMoments( 3 );

    entity_bin_second_moments =
      estimator_2_base->getEntityBinDataSecondMoments( 3 );

    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 2, 4.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 2, 8.0 ) );

    entity_bin_first_moments =
      estimator_2_base->getEntityBinDataFirstMoments( 4 );

    entity_bin_second_moments =
      estimator_2_base->getEntityBinDataSecondMoments( 4 );

    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 2, 4.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 2, 8.0 ) );

    entity_bin_first_moments =
      estimator_2_base->getEntityBinDataFirstMoments( 5 );

    entity_bin_second_moments =
      estimator_2_base->getEntityBinDataSecondMoments( 5 );

    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 2, 4.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 2, 8.0 ) );

    entity_bin_first_moments =
      estimator_2_base->getEntityBinDataFirstMoments( 6 );

    entity_bin_second_moments =
      estimator_2_base->getEntityBinDataSecondMoments( 6 );

    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 2, 4.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 2, 8.0 ) );

    entity_bin_first_moments =
      estimator_2_base->getEntityBinDataFirstMoments( 7 );

    entity_bin_second_moments =
      estimator_2_base->getEntityBinDataSecondMoments( 7 );

    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 2, 4.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 2, 8.0 ) );
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

    FRENSIE_CHECK_EQUAL( entity_ids.size(), 8 );
    FRENSIE_CHECK( entity_ids.find( 0 ) != entity_ids.end() );
    FRENSIE_CHECK( entity_ids.find( 1 ) != entity_ids.end() );
    FRENSIE_CHECK( entity_ids.find( 2 ) != entity_ids.end() );
    FRENSIE_CHECK( entity_ids.find( 3 ) != entity_ids.end() );
    FRENSIE_CHECK( entity_ids.find( 4 ) != entity_ids.end() );
    FRENSIE_CHECK( entity_ids.find( 5 ) != entity_ids.end() );
    FRENSIE_CHECK( entity_ids.find( 6 ) != entity_ids.end() );
    FRENSIE_CHECK( entity_ids.find( 7 ) != entity_ids.end() );

    FRENSIE_CHECK_EQUAL( estimator_3_base->getEntityNormConstant( 0 ), 1.0 );
    FRENSIE_CHECK_EQUAL( estimator_3_base->getEntityNormConstant( 1 ), 1.0 );
    FRENSIE_CHECK_EQUAL( estimator_3_base->getEntityNormConstant( 2 ), 1.0 );
    FRENSIE_CHECK_EQUAL( estimator_3_base->getEntityNormConstant( 3 ), 1.0 );
    FRENSIE_CHECK_EQUAL( estimator_3_base->getEntityNormConstant( 4 ), 1.0 );
    FRENSIE_CHECK_EQUAL( estimator_3_base->getEntityNormConstant( 5 ), 1.0 );
    FRENSIE_CHECK_EQUAL( estimator_3_base->getEntityNormConstant( 6 ), 1.0 );
    FRENSIE_CHECK_EQUAL( estimator_3_base->getEntityNormConstant( 7 ), 1.0 );
    FRENSIE_CHECK_FLOATING_EQUALITY( estimator_3_base->getTotalNormConstant(),
                                     8.0,
                                     1e-15 );

    // Check the entity bin data moments
    Utility::ArrayView<const double> entity_bin_first_moments =
      estimator_3_base->getEntityBinDataFirstMoments( 0 );

    Utility::ArrayView<const double> entity_bin_second_moments =
      estimator_3_base->getEntityBinDataSecondMoments( 0 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );

    entity_bin_first_moments =
      estimator_3_base->getEntityBinDataFirstMoments( 1 );

    entity_bin_second_moments =
      estimator_3_base->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );

    entity_bin_first_moments =
      estimator_3_base->getEntityBinDataFirstMoments( 2 );

    entity_bin_second_moments =
      estimator_3_base->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );

    entity_bin_first_moments =
      estimator_3_base->getEntityBinDataFirstMoments( 3 );

    entity_bin_second_moments =
      estimator_3_base->getEntityBinDataSecondMoments( 3 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );

    entity_bin_first_moments =
      estimator_3_base->getEntityBinDataFirstMoments( 4 );

    entity_bin_second_moments =
      estimator_3_base->getEntityBinDataSecondMoments( 4 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );

    entity_bin_first_moments =
      estimator_3_base->getEntityBinDataFirstMoments( 5 );

    entity_bin_second_moments =
      estimator_3_base->getEntityBinDataSecondMoments( 5 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );

    entity_bin_first_moments =
      estimator_3_base->getEntityBinDataFirstMoments( 6 );

    entity_bin_second_moments =
      estimator_3_base->getEntityBinDataSecondMoments( 6 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );

    entity_bin_first_moments =
      estimator_3_base->getEntityBinDataFirstMoments( 7 );

    entity_bin_second_moments =
      estimator_3_base->getEntityBinDataSecondMoments( 7 );

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
      estimator_3_base->getEntityTotalDataFirstMoments( 0 );

    Utility::ArrayView<const double> entity_total_second_moments =
      estimator_3_base->getEntityTotalDataSecondMoments( 0 );

    Utility::ArrayView<const double> entity_total_third_moments =
      estimator_3_base->getEntityTotalDataThirdMoments( 0 );

    Utility::ArrayView<const double> entity_total_fourth_moments =
      estimator_3_base->getEntityTotalDataFourthMoments( 0 );

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
      estimator_3_base->getEntityTotalDataFirstMoments( 1 );

    entity_total_second_moments =
      estimator_3_base->getEntityTotalDataSecondMoments( 1 );

    entity_total_third_moments =
      estimator_3_base->getEntityTotalDataThirdMoments( 1 );

    entity_total_fourth_moments =
      estimator_3_base->getEntityTotalDataFourthMoments( 1 );

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
      estimator_3_base->getEntityTotalDataFirstMoments( 2 );

    entity_total_second_moments =
      estimator_3_base->getEntityTotalDataSecondMoments( 2 );

    entity_total_third_moments =
      estimator_3_base->getEntityTotalDataThirdMoments( 2 );

    entity_total_fourth_moments =
      estimator_3_base->getEntityTotalDataFourthMoments( 2 );

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
      estimator_3_base->getEntityTotalDataFirstMoments( 3 );

    entity_total_second_moments =
      estimator_3_base->getEntityTotalDataSecondMoments( 3 );

    entity_total_third_moments =
      estimator_3_base->getEntityTotalDataThirdMoments( 3 );

    entity_total_fourth_moments =
      estimator_3_base->getEntityTotalDataFourthMoments( 3 );

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
      estimator_3_base->getEntityTotalDataFirstMoments( 4 );

    entity_total_second_moments =
      estimator_3_base->getEntityTotalDataSecondMoments( 4 );

    entity_total_third_moments =
      estimator_3_base->getEntityTotalDataThirdMoments( 4 );

    entity_total_fourth_moments =
      estimator_3_base->getEntityTotalDataFourthMoments( 4 );

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
      estimator_3_base->getEntityTotalDataFirstMoments( 5 );

    entity_total_second_moments =
      estimator_3_base->getEntityTotalDataSecondMoments( 5 );

    entity_total_third_moments =
      estimator_3_base->getEntityTotalDataThirdMoments( 5 );

    entity_total_fourth_moments =
      estimator_3_base->getEntityTotalDataFourthMoments( 5 );

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
      estimator_3_base->getEntityTotalDataFirstMoments( 6 );

    entity_total_second_moments =
      estimator_3_base->getEntityTotalDataSecondMoments( 6 );

    entity_total_third_moments =
      estimator_3_base->getEntityTotalDataThirdMoments( 6 );

    entity_total_fourth_moments =
      estimator_3_base->getEntityTotalDataFourthMoments( 6 );

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
      estimator_3_base->getEntityTotalDataFirstMoments( 7 );

    entity_total_second_moments =
      estimator_3_base->getEntityTotalDataSecondMoments( 7 );

    entity_total_third_moments =
      estimator_3_base->getEntityTotalDataThirdMoments( 7 );

    entity_total_fourth_moments =
      estimator_3_base->getEntityTotalDataFourthMoments( 7 );

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
    estimator_3_base->getEntityBinDataFirstMoments( 0 );

    entity_bin_second_moments =
      estimator_3_base->getEntityBinDataSecondMoments( 0 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );

    entity_bin_first_moments =
      estimator_3_base->getEntityBinDataFirstMoments( 1 );

    entity_bin_second_moments =
      estimator_3_base->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );

    entity_bin_first_moments =
      estimator_3_base->getEntityBinDataFirstMoments( 2 );

    entity_bin_second_moments =
      estimator_3_base->getEntityBinDataSecondMoments( 2 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );

    entity_bin_first_moments =
      estimator_3_base->getEntityBinDataFirstMoments( 3 );

    entity_bin_second_moments =
      estimator_3_base->getEntityBinDataSecondMoments( 3 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );

    entity_bin_first_moments =
      estimator_3_base->getEntityBinDataFirstMoments( 4 );

    entity_bin_second_moments =
      estimator_3_base->getEntityBinDataSecondMoments( 4 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );

    entity_bin_first_moments =
      estimator_3_base->getEntityBinDataFirstMoments( 5 );

    entity_bin_second_moments =
      estimator_3_base->getEntityBinDataSecondMoments( 5 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );

    entity_bin_first_moments =
      estimator_3_base->getEntityBinDataFirstMoments( 6 );

    entity_bin_second_moments =
      estimator_3_base->getEntityBinDataSecondMoments( 6 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                     std::vector<double>( 2, 0.0 ),
                                     1e-15 );

    entity_bin_first_moments =
      estimator_3_base->getEntityBinDataFirstMoments( 7 );

    entity_bin_second_moments =
      estimator_3_base->getEntityBinDataSecondMoments( 7 );

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

  // Set up a basic mesh
  std::vector<double> x_planes( {0, 1, 2} ),
    y_planes( {0, 1, 2} ),
    z_planes( {0, 1, 2} );

  hex_mesh.reset( new Utility::StructuredHexMesh( x_planes, y_planes, z_planes ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstHexMeshTrackLengthFluxEstimator.cpp
//---------------------------------------------------------------------------//


