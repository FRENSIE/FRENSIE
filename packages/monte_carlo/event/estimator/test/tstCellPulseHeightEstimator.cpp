//---------------------------------------------------------------------------//
//!
//! \file   tstCellPulseHeightEstimator.cpp
//! \author Alex Robinson
//! \brief  Cell pulse height estimator unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_CellPulseHeightEstimator.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef std::tuple<MonteCarlo::WeightMultiplier,
                   MonteCarlo::WeightAndEnergyMultiplier,
                   MonteCarlo::WeightAndChargeMultiplier
                   > MultiplierPolicies;

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the estimator is a cell type estimator
FRENSIE_UNIT_TEST_TEMPLATE( CellPulseHeightEstimator,
                            check_type,
                            MultiplierPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, ContributionMultiplierPolicy );

  typedef MonteCarlo::CellPulseHeightEstimator<ContributionMultiplierPolicy>
    CellPulseHeightEstimator;

  std::shared_ptr<MonteCarlo::Estimator> estimator( new CellPulseHeightEstimator(
                                                                0ull,
                                                                10.0,
                                                                {0, 1} ) );

  FRENSIE_CHECK( estimator->isCellEstimator() );
  FRENSIE_CHECK( !estimator->isSurfaceEstimator() );
  FRENSIE_CHECK( !estimator->isMeshEstimator() );
}

//---------------------------------------------------------------------------//
// Check that the number of bins can be returned
FRENSIE_UNIT_TEST_TEMPLATE( CellPulseHeightEstimator,
                            setDiscretization,
                            MultiplierPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, ContributionMultiplierPolicy );

  typedef MonteCarlo::CellPulseHeightEstimator<ContributionMultiplierPolicy>
    CellPulseHeightEstimator;

  std::shared_ptr<MonteCarlo::Estimator> estimator( new CellPulseHeightEstimator(
                                                                0ull,
                                                                10.0,
                                                                {0, 1} ) );

  FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins(), 1u );

  std::vector<double> double_bins( {0.0, 0.5, 1.0} );

  estimator->setDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION>( double_bins );

  FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins(), 2u );

  // Only energy bins are allowed
  estimator->setDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION>( double_bins);

  FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins(), 2u );

  // Only energy bins are allowed
  estimator->setDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION>( double_bins );

  FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins(), 2u );

  std::vector<unsigned> unsigned_bins( {0u, 1u} );

  // Only energy bins are allowed
  estimator->setDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION>(
                                                               unsigned_bins );

  FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins(), 2u );
}

//---------------------------------------------------------------------------//
// Check that a response function can be set
FRENSIE_UNIT_TEST_TEMPLATE( CellPulseHeightEstimator,
                            setResponseFunctions,
                            MultiplierPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, ContributionMultiplierPolicy );

  typedef MonteCarlo::CellPulseHeightEstimator<ContributionMultiplierPolicy>
    CellPulseHeightEstimator;

  std::shared_ptr<MonteCarlo::Estimator> estimator( new CellPulseHeightEstimator(
                                                                0ull,
                                                                10.0,
                                                                {0, 1} ) );

  FRENSIE_CHECK_EQUAL( estimator->getNumberOfResponseFunctions(), 1 );

  std::vector<std::shared_ptr<const MonteCarlo::ParticleResponse> >
    response_functions( 2 );
  response_functions[0] = MonteCarlo::ParticleResponse::getDefault();
  response_functions[1] = response_functions[0];

  // Response functions are not allowed with pulse height estimators
  estimator->setResponseFunctions( response_functions );

  FRENSIE_CHECK_EQUAL( estimator->getNumberOfResponseFunctions(), 1 );
}

//---------------------------------------------------------------------------//
// Check that the particle types can be set
FRENSIE_UNIT_TEST_TEMPLATE( CellPulseHeightEstimator,
                            setParticleTypes,
                            MultiplierPolicies )
{
  FETCH_TEMPLATE_PARAM( 0, ContributionMultiplierPolicy );

  typedef MonteCarlo::CellPulseHeightEstimator<ContributionMultiplierPolicy>
    CellPulseHeightEstimator;

  std::shared_ptr<MonteCarlo::Estimator> estimator( new CellPulseHeightEstimator(
                                                                0ull,
                                                                10.0,
                                                                {0, 1} ) );


  std::vector<MonteCarlo::ParticleType> particle_types( 4 );
  particle_types[0] = MonteCarlo::PHOTON;
  particle_types[1] = MonteCarlo::NEUTRON;
  particle_types[2] = MonteCarlo::ADJOINT_PHOTON;
  particle_types[3] = MonteCarlo::ADJOINT_NEUTRON;

  estimator->setParticleTypes( particle_types );

  FRENSIE_CHECK( estimator->isParticleTypeAssigned( MonteCarlo::PHOTON ) );
  FRENSIE_CHECK( estimator->isParticleTypeAssigned( MonteCarlo::ELECTRON ) );
  FRENSIE_CHECK( estimator->isParticleTypeAssigned( MonteCarlo::POSITRON ) );
  FRENSIE_CHECK( !estimator->isParticleTypeAssigned( MonteCarlo::NEUTRON ) );
  FRENSIE_CHECK( !estimator->isParticleTypeAssigned( MonteCarlo::ADJOINT_PHOTON ) );
  FRENSIE_CHECK( !estimator->isParticleTypeAssigned( MonteCarlo::ADJOINT_NEUTRON ) );

  particle_types.resize( 3 );
  particle_types[0] = MonteCarlo::ELECTRON;
  particle_types[1] = MonteCarlo::POSITRON;
  particle_types[2] = MonteCarlo::ADJOINT_ELECTRON;

  estimator->setParticleTypes( particle_types );

  FRENSIE_CHECK( estimator->isParticleTypeAssigned( MonteCarlo::PHOTON ) );
  FRENSIE_CHECK( estimator->isParticleTypeAssigned( MonteCarlo::ELECTRON ) );
  FRENSIE_CHECK( estimator->isParticleTypeAssigned( MonteCarlo::POSITRON ) );
  FRENSIE_CHECK( !estimator->isParticleTypeAssigned( MonteCarlo::ADJOINT_ELECTRON ) );
}

//---------------------------------------------------------------------------//
// Check that a partial history contribution can be added to the estimator
FRENSIE_UNIT_TEST( CellPulseHeightEstimator, updateFromParticleEvent )
{
  std::shared_ptr<MonteCarlo::Estimator> estimator_1_base, estimator_2_base, estimator_3_base;
  std::shared_ptr<MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightMultiplier> > estimator_1;
  std::shared_ptr<MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightAndEnergyMultiplier> > estimator_2;
  std::shared_ptr<MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightAndChargeMultiplier> > estimator_3;

  {
    // Set the entity ids
    std::vector<Geometry::Model::EntityId> entity_ids( 2 );
    entity_ids[0] = 0;
    entity_ids[1] = 1;

    estimator_1.reset( new MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightMultiplier>(
                                                                0ull,
                                                                10.0,
                                                                entity_ids ) );

    estimator_1_base = estimator_1;

    estimator_2.reset( new MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightAndEnergyMultiplier>(
                                                                1ull,
                                                                10.0,
                                                                entity_ids ) );
    estimator_2_base = estimator_2;

    estimator_3.reset( new MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightAndChargeMultiplier>(
                                                                2ull,
                                                                10.0,
                                                                entity_ids ) );

    estimator_3_base = estimator_3;

    // Set the energy bins
    std::vector<double> energy_bin_boundaries( 3 );
    energy_bin_boundaries[0] = 0.0;
    energy_bin_boundaries[1] = 1e-1;
    energy_bin_boundaries[2] = 1.0;

    estimator_1_base->setDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION>(
                                                       energy_bin_boundaries );
    estimator_2_base->setDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION>(
                                                       energy_bin_boundaries );
    estimator_3_base->setDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION>(
                                                       energy_bin_boundaries );
  }

  FRENSIE_CHECK_EQUAL( estimator_1_base->getParticleTypes().size(), 3 );
  FRENSIE_CHECK( estimator_1_base->getParticleTypes().find( MonteCarlo::PHOTON ) != estimator_1_base->getParticleTypes().end() );
  FRENSIE_CHECK( estimator_1_base->getParticleTypes().find( MonteCarlo::ELECTRON ) != estimator_1_base->getParticleTypes().end() );
  FRENSIE_CHECK( estimator_1_base->getParticleTypes().find( MonteCarlo::POSITRON ) != estimator_1_base->getParticleTypes().end() );
  FRENSIE_CHECK_EQUAL( estimator_2_base->getParticleTypes().size(), 3 );
  FRENSIE_CHECK( estimator_2_base->getParticleTypes().find( MonteCarlo::PHOTON ) != estimator_2_base->getParticleTypes().end() );
  FRENSIE_CHECK( estimator_2_base->getParticleTypes().find( MonteCarlo::ELECTRON ) != estimator_2_base->getParticleTypes().end() );
  FRENSIE_CHECK( estimator_2_base->getParticleTypes().find( MonteCarlo::POSITRON ) != estimator_2_base->getParticleTypes().end() );
  FRENSIE_CHECK_EQUAL( estimator_3_base->getParticleTypes().size(), 3 );
  FRENSIE_CHECK( estimator_3_base->getParticleTypes().find( MonteCarlo::PHOTON ) != estimator_3_base->getParticleTypes().end() );
  FRENSIE_CHECK( estimator_3_base->getParticleTypes().find( MonteCarlo::ELECTRON ) != estimator_3_base->getParticleTypes().end() );
  FRENSIE_CHECK( estimator_3_base->getParticleTypes().find( MonteCarlo::POSITRON ) != estimator_3_base->getParticleTypes().end() );

  MonteCarlo::ElectronState particle( 0ull );
  particle.setSourceWeight( 1.0 );
  particle.setWeight( 1.0 );
  particle.setEnergy( 1.0 );

  FRENSIE_CHECK( !estimator_1_base->hasUncommittedHistoryContribution() );
  FRENSIE_CHECK( !estimator_2_base->hasUncommittedHistoryContribution() );
  FRENSIE_CHECK( !estimator_3_base->hasUncommittedHistoryContribution() );

  estimator_1->updateFromParticleEnteringCellEvent( particle, 0 );
  estimator_2->updateFromParticleEnteringCellEvent( particle, 0 );
  estimator_3->updateFromParticleEnteringCellEvent( particle, 0 );

  FRENSIE_CHECK( estimator_1_base->hasUncommittedHistoryContribution() );
  FRENSIE_CHECK( estimator_2_base->hasUncommittedHistoryContribution() );
  FRENSIE_CHECK( estimator_3_base->hasUncommittedHistoryContribution() );

  particle.setEnergy( 0.5 );

  estimator_1->updateFromParticleLeavingCellEvent( particle, 0 );
  estimator_2->updateFromParticleLeavingCellEvent( particle, 0 );
  estimator_3->updateFromParticleLeavingCellEvent( particle, 0 );

  estimator_1->updateFromParticleEnteringCellEvent( particle, 1 );
  estimator_2->updateFromParticleEnteringCellEvent( particle, 1 );
  estimator_3->updateFromParticleEnteringCellEvent( particle, 1 );

  FRENSIE_CHECK( estimator_1_base->hasUncommittedHistoryContribution() );
  FRENSIE_CHECK( estimator_2_base->hasUncommittedHistoryContribution() );
  FRENSIE_CHECK( estimator_3_base->hasUncommittedHistoryContribution() );

  particle.setEnergy( 0.45 );

  estimator_1->updateFromParticleLeavingCellEvent( particle, 1 );
  estimator_2->updateFromParticleLeavingCellEvent( particle, 1 );

  FRENSIE_CHECK( estimator_1_base->hasUncommittedHistoryContribution() );
  FRENSIE_CHECK( estimator_2_base->hasUncommittedHistoryContribution() );
  FRENSIE_CHECK( estimator_3_base->hasUncommittedHistoryContribution() );

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
                       std::vector<double>( {0.0, 1.0} ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( {0.0, 1.0} ) );

  entity_bin_first_moments =
    estimator_1_base->getEntityBinDataFirstMoments( 1 );

  entity_bin_second_moments =
    estimator_1_base->getEntityBinDataSecondMoments( 1 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( {1.0, 0.0} ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( {1.0, 0.0} ) );

  entity_bin_first_moments =
    estimator_2_base->getEntityBinDataFirstMoments( 0 );

  entity_bin_second_moments =
    estimator_2_base->getEntityBinDataSecondMoments( 0 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( {0.0, 0.5} ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( {0.0, 0.25} ) );

  entity_bin_first_moments =
    estimator_2_base->getEntityBinDataFirstMoments( 1 );

  entity_bin_second_moments =
    estimator_2_base->getEntityBinDataSecondMoments( 1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( {0.05, 0.0} ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( {0.0025, 0.0} ),
                                   1e-15 );

  entity_bin_first_moments =
    estimator_3_base->getEntityBinDataFirstMoments( 0 );

  entity_bin_second_moments =
    estimator_3_base->getEntityBinDataSecondMoments( 0 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( {0.0, 0.0} ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( {0.0, 0.0} ) );

  entity_bin_first_moments =
    estimator_3_base->getEntityBinDataFirstMoments( 1 );

  entity_bin_second_moments =
    estimator_3_base->getEntityBinDataSecondMoments( 1 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( {0.0, -1.0} ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( {0.0, 1.0} ) );

  // Check the total bin data moments
  Utility::ArrayView<const double> total_bin_first_moments =
    estimator_1_base->getTotalBinDataFirstMoments();

  Utility::ArrayView<const double> total_bin_second_moments =
    estimator_1_base->getTotalBinDataSecondMoments();

  FRENSIE_CHECK_EQUAL( total_bin_first_moments,
                       std::vector<double>( {0.0, 1.0} ) );
  FRENSIE_CHECK_EQUAL( total_bin_second_moments,
                       std::vector<double>( {0.0, 1.0} ) );

  total_bin_first_moments =
    estimator_2_base->getTotalBinDataFirstMoments();

  total_bin_second_moments =
    estimator_2_base->getTotalBinDataSecondMoments();

  FRENSIE_CHECK_EQUAL( total_bin_first_moments,
                       std::vector<double>( {0.0, 0.55} ) );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_bin_second_moments,
                                   std::vector<double>( {0.0, 0.3025} ),
                                   1e-15 );

  total_bin_first_moments =
    estimator_3_base->getTotalBinDataFirstMoments();

  total_bin_second_moments =
    estimator_3_base->getTotalBinDataSecondMoments();

  FRENSIE_CHECK_EQUAL( total_bin_first_moments,
                       std::vector<double>( {0.0, -1.0} ) );
  FRENSIE_CHECK_EQUAL( total_bin_second_moments,
                       std::vector<double>( {0.0, 1.0} ) );
}

//---------------------------------------------------------------------------//
// Check that a partial history contribution can be added to the estimator
FRENSIE_UNIT_TEST( CellPulseHeightEstimator,
                   updateFromParticleEvent_thread_safe )
{
  std::shared_ptr<MonteCarlo::Estimator> estimator_1_base, estimator_2_base, estimator_3_base;
  std::shared_ptr<MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightMultiplier> > estimator_1;
  std::shared_ptr<MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightAndEnergyMultiplier> > estimator_2;
  std::shared_ptr<MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightAndChargeMultiplier> > estimator_3;

  {
    // Set the entity ids
    std::vector<Geometry::Model::EntityId> entity_ids( {0, 1} );

    estimator_1.reset( new MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightMultiplier>(
                                                                0ull,
                                                                10.0,
                                                                entity_ids ) );

    estimator_1_base = estimator_1;

    estimator_2.reset( new MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightAndEnergyMultiplier>(
                                                                1ull,
                                                                10.0,
                                                                entity_ids ) );
    estimator_2_base = estimator_2;

    estimator_3.reset( new MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightAndChargeMultiplier>(
                                                                2ull,
                                                                10.0,
                                                                entity_ids ) );

    estimator_3_base = estimator_3;

    // Set the energy bins
    std::vector<double> energy_bin_boundaries( 3 );
    energy_bin_boundaries[0] = 0.0;
    energy_bin_boundaries[1] = 1e-1;
    energy_bin_boundaries[2] = 1.0;

    estimator_1_base->setDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION>(
                                                       energy_bin_boundaries );
    estimator_2_base->setDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION>(
                                                       energy_bin_boundaries );
    estimator_3_base->setDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION>(
                                                       energy_bin_boundaries );

    estimator_1->enableThreadSupport( Utility::OpenMPProperties::getRequestedNumberOfThreads() );
    estimator_2->enableThreadSupport( Utility::OpenMPProperties::getRequestedNumberOfThreads() );
    estimator_3->enableThreadSupport( Utility::OpenMPProperties::getRequestedNumberOfThreads() );
  }

  FRENSIE_CHECK_EQUAL( estimator_1_base->getParticleTypes().size(), 3 );
  FRENSIE_CHECK( estimator_1_base->getParticleTypes().find( MonteCarlo::PHOTON ) != estimator_1_base->getParticleTypes().end() );
  FRENSIE_CHECK( estimator_1_base->getParticleTypes().find( MonteCarlo::ELECTRON ) != estimator_1_base->getParticleTypes().end() );
  FRENSIE_CHECK( estimator_1_base->getParticleTypes().find( MonteCarlo::POSITRON ) != estimator_1_base->getParticleTypes().end() );
  FRENSIE_CHECK_EQUAL( estimator_2_base->getParticleTypes().size(), 3 );
  FRENSIE_CHECK( estimator_2_base->getParticleTypes().find( MonteCarlo::PHOTON ) != estimator_2_base->getParticleTypes().end() );
  FRENSIE_CHECK( estimator_2_base->getParticleTypes().find( MonteCarlo::ELECTRON ) != estimator_2_base->getParticleTypes().end() );
  FRENSIE_CHECK( estimator_2_base->getParticleTypes().find( MonteCarlo::POSITRON ) != estimator_2_base->getParticleTypes().end() );
  FRENSIE_CHECK_EQUAL( estimator_3_base->getParticleTypes().size(), 3 );
  FRENSIE_CHECK( estimator_3_base->getParticleTypes().find( MonteCarlo::PHOTON ) != estimator_3_base->getParticleTypes().end() );
  FRENSIE_CHECK( estimator_3_base->getParticleTypes().find( MonteCarlo::ELECTRON ) != estimator_3_base->getParticleTypes().end() );
  FRENSIE_CHECK( estimator_3_base->getParticleTypes().find( MonteCarlo::POSITRON ) != estimator_3_base->getParticleTypes().end() );

  unsigned threads =
    Utility::OpenMPProperties::getRequestedNumberOfThreads();

  #pragma omp parallel num_threads( threads )
  {
    MonteCarlo::ElectronState particle( Utility::OpenMPProperties::getThreadId() );
    particle.setWeight( 1.0 );
    particle.setEnergy( 1.0 );

    estimator_1->updateFromParticleEnteringCellEvent( particle, 0 );
    estimator_2->updateFromParticleEnteringCellEvent( particle, 0 );
    estimator_3->updateFromParticleEnteringCellEvent( particle, 0 );

    particle.setEnergy( 0.5 );

    estimator_1->updateFromParticleLeavingCellEvent( particle, 0 );
    estimator_2->updateFromParticleLeavingCellEvent( particle, 0 );
    estimator_3->updateFromParticleEnteringCellEvent( particle, 0 );

    estimator_1->updateFromParticleEnteringCellEvent( particle, 1 );
    estimator_2->updateFromParticleEnteringCellEvent( particle, 1 );
    estimator_3->updateFromParticleEnteringCellEvent( particle, 1 );

    particle.setEnergy( 0.45 );

    estimator_1->updateFromParticleLeavingCellEvent( particle, 1 );
    estimator_2->updateFromParticleLeavingCellEvent( particle, 1 );

    estimator_1_base->commitHistoryContribution();
    estimator_2_base->commitHistoryContribution();
    estimator_3_base->commitHistoryContribution();
  }

  MonteCarlo::ParticleHistoryObserver::setNumberOfHistories( threads );
  MonteCarlo::ParticleHistoryObserver::setElapsedTime( 1.0 );

  // Check the entity bin data moments
  Utility::ArrayView<const double> entity_bin_first_moments =
    estimator_1_base->getEntityBinDataFirstMoments( 0 );

  Utility::ArrayView<const double> entity_bin_second_moments =
    estimator_1_base->getEntityBinDataSecondMoments( 0 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( {0.0, 1.0*threads} ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( {0.0, 1.0*threads} ) );

  entity_bin_first_moments =
    estimator_1_base->getEntityBinDataFirstMoments( 1 );

  entity_bin_second_moments =
    estimator_1_base->getEntityBinDataSecondMoments( 1 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( {1.0*threads, 0.0} ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( {1.0*threads, 0.0} ) );

  entity_bin_first_moments =
    estimator_2_base->getEntityBinDataFirstMoments( 0 );

  entity_bin_second_moments =
    estimator_2_base->getEntityBinDataSecondMoments( 0 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( {0.0, 0.5*threads} ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( {0.0, 0.25*threads} ) );

  entity_bin_first_moments =
    estimator_2_base->getEntityBinDataFirstMoments( 1 );

  entity_bin_second_moments =
    estimator_2_base->getEntityBinDataSecondMoments( 1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( {0.05*threads, 0.0} ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( {0.0025*threads, 0.0} ),
                                   1e-15 );

  entity_bin_first_moments =
    estimator_3_base->getEntityBinDataFirstMoments( 0 );

  entity_bin_second_moments =
    estimator_3_base->getEntityBinDataSecondMoments( 0 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( {0.0, 0.0} ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( {0.0, 0.0} ) );

  entity_bin_first_moments =
    estimator_3_base->getEntityBinDataFirstMoments( 1 );

  entity_bin_second_moments =
    estimator_3_base->getEntityBinDataSecondMoments( 1 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( {0.0, -1.0*threads} ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( {0.0, 1.0*threads} ) );

  // Check the total bin data moments
  Utility::ArrayView<const double> total_bin_first_moments =
    estimator_1_base->getTotalBinDataFirstMoments();

  Utility::ArrayView<const double> total_bin_second_moments =
    estimator_1_base->getTotalBinDataSecondMoments();

  FRENSIE_CHECK_EQUAL( total_bin_first_moments,
                       std::vector<double>( {0.0, 1.0*threads} ) );
  FRENSIE_CHECK_EQUAL( total_bin_second_moments,
                       std::vector<double>( {0.0, 1.0*threads} ) );

  total_bin_first_moments =
    estimator_2_base->getTotalBinDataFirstMoments();

  total_bin_second_moments =
    estimator_2_base->getTotalBinDataSecondMoments();

  FRENSIE_CHECK_FLOATING_EQUALITY( total_bin_first_moments,
                                   std::vector<double>( {0.0, 0.55*threads} ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_bin_second_moments,
                                   std::vector<double>( {0.0, 0.3025*threads} ),
                                   1e-15 );

  total_bin_first_moments =
    estimator_3_base->getTotalBinDataFirstMoments();

  total_bin_second_moments =
    estimator_3_base->getTotalBinDataSecondMoments();

  FRENSIE_CHECK_EQUAL( total_bin_first_moments,
                       std::vector<double>( {0.0, -1.0*threads} ) );
  FRENSIE_CHECK_EQUAL( total_bin_second_moments,
                       std::vector<double>( {0.0, 1.0*threads} ) );
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

  std::string archive_base_name( "test_cell_pulse_height_estimator" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::shared_ptr<MonteCarlo::Estimator> estimator_1_base, estimator_2_base, estimator_3_base;
    std::shared_ptr<MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightMultiplier> > estimator_1;
    std::shared_ptr<MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightAndEnergyMultiplier> > estimator_2;
    std::shared_ptr<MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightAndChargeMultiplier> > estimator_3;

    {
      // Set the entity ids
      std::vector<Geometry::Model::EntityId> entity_ids( {0, 1} );

      estimator_1.reset( new MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightMultiplier>(
                                                                0ull,
                                                                1.0,
                                                                entity_ids ) );

      estimator_1_base = estimator_1;

      estimator_2.reset( new MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightAndEnergyMultiplier>(
                                                                1ull,
                                                                10.0,
                                                                entity_ids ) );
      estimator_2_base = estimator_2;

      estimator_3.reset( new MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightAndChargeMultiplier>(
                                                                  2ull,
                                                                  1.0,
                                                                  entity_ids ) );

      estimator_3_base = estimator_3;

      // Set the energy bins
      std::vector<double> energy_bin_boundaries( 3 );
      energy_bin_boundaries[0] = 0.0;
      energy_bin_boundaries[1] = 1e-1;
      energy_bin_boundaries[2] = 1.0;

      estimator_1_base->setDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION>(
                                                       energy_bin_boundaries );
      estimator_2_base->setDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION>(
                                                       energy_bin_boundaries );
      estimator_3_base->setDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION>(
                                                       energy_bin_boundaries );
    }

    MonteCarlo::PhotonState particle( 0ull );
    particle.setWeight( 1.0 );
    particle.setEnergy( 1.0 );

    estimator_1->updateFromParticleEnteringCellEvent( particle, 0 );
    estimator_2->updateFromParticleEnteringCellEvent( particle, 0 );
    estimator_3->updateFromParticleEnteringCellEvent( particle, 0 );

    particle.setEnergy( 0.5 );

    estimator_1->updateFromParticleLeavingCellEvent( particle, 0 );
    estimator_2->updateFromParticleLeavingCellEvent( particle, 0 );
    estimator_3->updateFromParticleEnteringCellEvent( particle, 0 );

    estimator_1->updateFromParticleEnteringCellEvent( particle, 1 );
    estimator_2->updateFromParticleEnteringCellEvent( particle, 1 );
    estimator_3->updateFromParticleEnteringCellEvent( particle, 1 );

    particle.setEnergy( 0.45 );

    estimator_1->updateFromParticleLeavingCellEvent( particle, 1 );
    estimator_2->updateFromParticleLeavingCellEvent( particle, 1 );
    estimator_3->updateFromParticleLeavingCellEvent( particle, 1 );

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

  std::shared_ptr<MonteCarlo::Estimator> estimator_1_base, estimator_2_base, estimator_3_base;
  std::shared_ptr<MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightMultiplier> > estimator_1;
  std::shared_ptr<MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightAndEnergyMultiplier> > estimator_2;
  std::shared_ptr<MonteCarlo::CellPulseHeightEstimator<MonteCarlo::WeightAndChargeMultiplier> > estimator_3;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( estimator_1 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( estimator_1_base ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( estimator_2 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( estimator_2_base ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( estimator_3 ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( estimator_3_base ) );

  iarchive.reset();

  {
    FRENSIE_CHECK( estimator_1.get() == estimator_1_base.get() );
    FRENSIE_CHECK_EQUAL( estimator_1_base->getMultiplier(), 1.0 );
    FRENSIE_CHECK_EQUAL( estimator_1_base->getNumberOfBins(), 2 );
    FRENSIE_CHECK_EQUAL( estimator_1_base->getNumberOfBins( MonteCarlo::OBSERVER_ENERGY_DIMENSION ), 2 );
    FRENSIE_CHECK_EQUAL( estimator_1_base->getNumberOfResponseFunctions(), 1 );
    FRENSIE_CHECK_EQUAL( estimator_1_base->getParticleTypes().size(), 3 );
    FRENSIE_CHECK( estimator_1_base->getParticleTypes().find( MonteCarlo::PHOTON ) != estimator_1_base->getParticleTypes().end() );
    FRENSIE_CHECK( estimator_1_base->getParticleTypes().find( MonteCarlo::ELECTRON ) != estimator_1_base->getParticleTypes().end() );
    FRENSIE_CHECK( estimator_1_base->getParticleTypes().find( MonteCarlo::POSITRON ) != estimator_1_base->getParticleTypes().end() );

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
                         std::vector<double>( {0.0, 1.0} ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( {0.0, 1.0} ) );

    entity_bin_first_moments =
      estimator_1_base->getEntityBinDataFirstMoments( 1 );

    entity_bin_second_moments =
      estimator_1_base->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( {1.0, 0.0} ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( {1.0, 0.0} ) );

    // Check the total bin data moments
    Utility::ArrayView<const double> total_bin_first_moments =
      estimator_1_base->getTotalBinDataFirstMoments();

    Utility::ArrayView<const double> total_bin_second_moments =
      estimator_1_base->getTotalBinDataSecondMoments();

    FRENSIE_CHECK_EQUAL( total_bin_first_moments,
                         std::vector<double>( {0.0, 1.0} ) );
    FRENSIE_CHECK_EQUAL( total_bin_second_moments,
                         std::vector<double>( {0.0, 1.0} ) );
  }

  {
    FRENSIE_CHECK( estimator_2.get() == estimator_2_base.get() );
    FRENSIE_CHECK_EQUAL( estimator_2_base->getMultiplier(), 10.0 );
    FRENSIE_CHECK_EQUAL( estimator_2_base->getNumberOfBins(), 2 );
    FRENSIE_CHECK_EQUAL( estimator_2_base->getNumberOfBins( MonteCarlo::OBSERVER_ENERGY_DIMENSION ), 2 );
    FRENSIE_CHECK_EQUAL( estimator_2_base->getNumberOfResponseFunctions(), 1 );
    FRENSIE_CHECK_EQUAL( estimator_2_base->getParticleTypes().size(), 3 );
    FRENSIE_CHECK( estimator_2_base->getParticleTypes().find( MonteCarlo::PHOTON ) != estimator_2_base->getParticleTypes().end() );
    FRENSIE_CHECK( estimator_2_base->getParticleTypes().find( MonteCarlo::ELECTRON ) != estimator_2_base->getParticleTypes().end() );
    FRENSIE_CHECK( estimator_2_base->getParticleTypes().find( MonteCarlo::POSITRON ) != estimator_2_base->getParticleTypes().end() );

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
                         std::vector<double>( {0.0, 0.5} ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( {0.0, 0.25} ) );

    entity_bin_first_moments =
      estimator_2_base->getEntityBinDataFirstMoments( 1 );

    entity_bin_second_moments =
      estimator_2_base->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                     std::vector<double>( {0.05, 0.0} ),
                                     1e-15 );
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                     std::vector<double>( {0.0025, 0.0} ),
                                     1e-15 );

    // Check the total bin data moments
    Utility::ArrayView<const double> total_bin_first_moments =
      estimator_2_base->getTotalBinDataFirstMoments();

    Utility::ArrayView<const double> total_bin_second_moments =
      estimator_2_base->getTotalBinDataSecondMoments();

    FRENSIE_CHECK_EQUAL( total_bin_first_moments,
                         std::vector<double>( {0.0, 0.55} ) );
    FRENSIE_CHECK_FLOATING_EQUALITY( total_bin_second_moments,
                                     std::vector<double>( {0.0, 0.3025} ),
                                     1e-15 );
  }

  {
    FRENSIE_CHECK( estimator_3.get() == estimator_3_base.get() );
    FRENSIE_CHECK_EQUAL( estimator_3_base->getMultiplier(), 1.0 );
    FRENSIE_CHECK_EQUAL( estimator_3_base->getNumberOfBins(), 2 );
    FRENSIE_CHECK_EQUAL( estimator_3_base->getNumberOfBins( MonteCarlo::OBSERVER_ENERGY_DIMENSION ), 2 );
    FRENSIE_CHECK_EQUAL( estimator_3_base->getNumberOfResponseFunctions(), 1 );
    FRENSIE_CHECK_EQUAL( estimator_3_base->getParticleTypes().size(), 3 );
    FRENSIE_CHECK( estimator_3_base->getParticleTypes().find( MonteCarlo::PHOTON ) != estimator_2_base->getParticleTypes().end() );
    FRENSIE_CHECK( estimator_3_base->getParticleTypes().find( MonteCarlo::ELECTRON ) != estimator_2_base->getParticleTypes().end() );
    FRENSIE_CHECK( estimator_3_base->getParticleTypes().find( MonteCarlo::POSITRON ) != estimator_2_base->getParticleTypes().end() );

    std::set<uint64_t> entity_ids;

    estimator_1->getEntityIds( entity_ids );

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
                         std::vector<double>( {0.0, 0.0} ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( {0.0, 0.0} ) );

    entity_bin_first_moments =
      estimator_3_base->getEntityBinDataFirstMoments( 1 );

    entity_bin_second_moments =
      estimator_3_base->getEntityBinDataSecondMoments( 1 );

    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( {0.0, 0.0} ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( {0.0, 0.0} ) );

    // Check the total bin data moments
    Utility::ArrayView<const double> total_bin_first_moments =
      estimator_3_base->getTotalBinDataFirstMoments();

    Utility::ArrayView<const double> total_bin_second_moments =
      estimator_3_base->getTotalBinDataSecondMoments();

    FRENSIE_CHECK_EQUAL( total_bin_first_moments,
                         std::vector<double>( {0.0, 0.0} ) );
    FRENSIE_CHECK_EQUAL( total_bin_second_moments,
                         std::vector<double>( {0.0, 0.0} ) );
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
// end tstCellPulseHeightEstimator.cpp
//---------------------------------------------------------------------------//
