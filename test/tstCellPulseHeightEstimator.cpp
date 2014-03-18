//---------------------------------------------------------------------------//
//!
//! \file   tstCellPulseHeightEstimator.cpp
//! \author Alex Robinson
//! \brief  Cell pulse height estimator unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FACEMC Includes
#include "CellPulseHeightEstimator.hpp"

//---------------------------------------------------------------------------//
// Instantiation Macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name ) \
  using namespace FACEMC;						\
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, int, WeightMultiplier ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( type, name, int, WeightAndEnergyMultiplier ) \

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Set the entity energy bins (and response functions)
void setEstimatorBins( Teuchos::RCP<FACEMC::Estimator>& estimator )
{
  // Set the energy bins
  Teuchos::Array<double> energy_bin_boundaries( 3 );
  energy_bin_boundaries[0] = 0.0;
  energy_bin_boundaries[1] = 1e-1;
  energy_bin_boundaries[2] = 1.0;

  estimator->setBinBoundaries<FACEMC::ENERGY_DIMENSION>(energy_bin_boundaries);
}

// Initialize the estimator
template<typename PulseHeightEstimator>
void initializePulseHeightEstimator( 
				Teuchos::RCP<PulseHeightEstimator>& estimator )
{  
  // Set the entity ids
  Teuchos::Array<int> entity_ids( 2 );
  entity_ids[0] = 0;
  entity_ids[1] = 1;

  // Set the estimator multiplier
  double estimator_multiplier = 10.0;

  estimator.reset( new PulseHeightEstimator( 0ull, 
					     estimator_multiplier,
					     entity_ids ) );

  Teuchos::RCP<FACEMC::Estimator> estimator_base = 
    Teuchos::rcp_dynamic_cast<FACEMC::Estimator>( estimator );
  
  // Set the estimator bins (and response functions)
  setEstimatorBins( estimator_base );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the number of bins can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( CellPulseHeightEstimator,
				   getNumberOfBins,
				   EntityId,
				   ContributionMultiplierPolicy )
{
  typedef FACEMC::CellPulseHeightEstimator<EntityId,ContributionMultiplierPolicy> CellPulseHeightEstimator;

  Teuchos::RCP<CellPulseHeightEstimator> estimator;
  initializePulseHeightEstimator<CellPulseHeightEstimator>( estimator );

  TEST_EQUALITY_CONST( estimator->getNumberOfBins(), 2u );

  Teuchos::Array<double> double_bins( 2 );
  double_bins[0] = 0.0;
  double_bins[1] = 1.0;

  estimator->template setBinBoundaries<FACEMC::COSINE_DIMENSION>( double_bins);
  
  TEST_EQUALITY_CONST( estimator->getNumberOfBins(), 2u );

  estimator->template setBinBoundaries<FACEMC::TIME_DIMENSION>( double_bins );

  TEST_EQUALITY_CONST( estimator->getNumberOfBins(), 2u );

  Teuchos::Array<unsigned> unsigned_bins( 1 );
  unsigned_bins[0] = 0u;

  estimator->template setBinBoundaries<FACEMC::COLLISION_NUMBER_DIMENSION>( 
							       unsigned_bins );

  TEST_EQUALITY_CONST( estimator->getNumberOfBins(), 2u );
}

UNIT_TEST_INSTANTIATION( CellPulseHeightEstimator, getNumberOfBins );

//---------------------------------------------------------------------------//
// Check that the particle types can be set
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( CellPulseHeightEstimator,
				   setParticleTypes,
				   EntityId,
				   ContributionMultiplierPolicy )
{
  typedef FACEMC::CellPulseHeightEstimator<EntityId,ContributionMultiplierPolicy> CellPulseHeightEstimator;

  Teuchos::RCP<CellPulseHeightEstimator> estimator;
  initializePulseHeightEstimator<CellPulseHeightEstimator>( estimator );

  Teuchos::Array<FACEMC::ParticleType> particle_types( 4 );
  particle_types[0] = FACEMC::PHOTON;
  particle_types[1] = FACEMC::NEUTRON;
  particle_types[2] = FACEMC::ADJOINT_PHOTON;
  particle_types[3] = FACEMC::ADJOINT_NEUTRON;
  
  estimator->setParticleTypes( particle_types );

  TEST_ASSERT( estimator->isParticleTypeAssigned( FACEMC::PHOTON ) );
  TEST_ASSERT( !estimator->isParticleTypeAssigned( FACEMC::NEUTRON ) );
  TEST_ASSERT( !estimator->isParticleTypeAssigned( FACEMC::ADJOINT_PHOTON ) );
  TEST_ASSERT( !estimator->isParticleTypeAssigned( FACEMC::ADJOINT_NEUTRON ) );
}

UNIT_TEST_INSTANTIATION( CellPulseHeightEstimator, setParticleTypes );

//---------------------------------------------------------------------------//
// Check that a partial history contribution can be added to the estimator
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( CellPulseHeightEstimator,
				   addPartialHistoryContribution,
				   EntityId,
				   ContributionMultiplierPolicy )
{
  typedef FACEMC::CellPulseHeightEstimator<EntityId,ContributionMultiplierPolicy> CellPulseHeightEstimator;

  Teuchos::RCP<CellPulseHeightEstimator> estimator;
  initializePulseHeightEstimator<CellPulseHeightEstimator>( estimator );

  FACEMC::BasicParticleState particle;
  particle.setWeight( 1.0 );
  particle.setEnergy( 1.0 );

  estimator->addPartialHistoryContribution( particle, 2, 0 );

  particle.setEnergy( 0.5 );

  estimator->addPartialHistoryContribution( particle, 0, 1 );

  particle.setEnergy( 0.1 );
  
  estimator->addPartialHistoryContribution( particle, 1, 2 );

  estimator->commitHistoryContribution();

  FACEMC::Estimator::setNumberOfHistories( 1.0 );
  FACEMC::Estimator::setEndTime( 1.0 );

  std::cout << std::endl << *estimator << std::endl;
}

UNIT_TEST_INSTANTIATION( CellPulseHeightEstimator, 
			 addPartialHistoryContribution );

//---------------------------------------------------------------------------//
// end tstCellPulseHeightEstimator.cpp
//---------------------------------------------------------------------------//
