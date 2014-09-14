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

// FRENSIE Includes
#include "MonteCarlo_CellPulseHeightEstimator.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Geometry_ModuleTraits.hpp"

//---------------------------------------------------------------------------//
// Instantiation Macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name ) \
  using namespace MonteCarlo;						\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, WeightMultiplier ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, WeightAndEnergyMultiplier)\

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Set the entity energy bins (and response functions)
void setEstimatorBins( Teuchos::RCP<MonteCarlo::Estimator>& estimator )
{
  // Set the energy bins
  Teuchos::Array<double> energy_bin_boundaries( 3 );
  energy_bin_boundaries[0] = 0.0;
  energy_bin_boundaries[1] = 1e-1;
  energy_bin_boundaries[2] = 1.0;

  estimator->setBinBoundaries<MonteCarlo::ENERGY_DIMENSION>(energy_bin_boundaries);
}

// Initialize the estimator
template<typename PulseHeightEstimator>
void initializePulseHeightEstimator( 
				Teuchos::RCP<PulseHeightEstimator>& estimator )
{  
  // Set the entity ids
  Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle> 
    entity_ids( 2 );
  entity_ids[0] = 0;
  entity_ids[1] = 1;

  // Set the estimator multiplier
  double estimator_multiplier = 10.0;

  estimator.reset( new PulseHeightEstimator( 0ull, 
					     estimator_multiplier,
					     entity_ids ) );
					     
  Teuchos::RCP<MonteCarlo::Estimator> estimator_base = 
    Teuchos::rcp_dynamic_cast<MonteCarlo::Estimator>( estimator );
  
  // Set the estimator bins (and response functions)
  setEstimatorBins( estimator_base );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the number of bins can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( CellPulseHeightEstimator,
				   getNumberOfBins,
				   ContributionMultiplierPolicy )
{
  typedef MonteCarlo::CellPulseHeightEstimator<ContributionMultiplierPolicy> 
    CellPulseHeightEstimator;

  Teuchos::RCP<CellPulseHeightEstimator> estimator;
  initializePulseHeightEstimator<CellPulseHeightEstimator>( estimator );

  TEST_EQUALITY_CONST( estimator->getNumberOfBins(), 2u );

  Teuchos::Array<double> double_bins( 2 );
  double_bins[0] = 0.0;
  double_bins[1] = 1.0;

  estimator->template setBinBoundaries<MonteCarlo::COSINE_DIMENSION>( double_bins);
  
  TEST_EQUALITY_CONST( estimator->getNumberOfBins(), 2u );

  estimator->template setBinBoundaries<MonteCarlo::TIME_DIMENSION>( double_bins );

  TEST_EQUALITY_CONST( estimator->getNumberOfBins(), 2u );

  Teuchos::Array<unsigned> unsigned_bins( 1 );
  unsigned_bins[0] = 0u;

  estimator->template setBinBoundaries<MonteCarlo::COLLISION_NUMBER_DIMENSION>( 
							       unsigned_bins );

  TEST_EQUALITY_CONST( estimator->getNumberOfBins(), 2u );
}

UNIT_TEST_INSTANTIATION( CellPulseHeightEstimator, getNumberOfBins );

//---------------------------------------------------------------------------//
// Check that the particle types can be set
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( CellPulseHeightEstimator,
				   setParticleTypes,
				   ContributionMultiplierPolicy )
{
  typedef MonteCarlo::CellPulseHeightEstimator<ContributionMultiplierPolicy> 
    CellPulseHeightEstimator;

  Teuchos::RCP<CellPulseHeightEstimator> estimator;
  initializePulseHeightEstimator<CellPulseHeightEstimator>( estimator );

  Teuchos::Array<MonteCarlo::ParticleType> particle_types( 4 );
  particle_types[0] = MonteCarlo::PHOTON;
  particle_types[1] = MonteCarlo::NEUTRON;
  particle_types[2] = MonteCarlo::ADJOINT_PHOTON;
  particle_types[3] = MonteCarlo::ADJOINT_NEUTRON;
  
  estimator->setParticleTypes( particle_types );

  TEST_ASSERT( estimator->isParticleTypeAssigned( MonteCarlo::PHOTON ) );
  TEST_ASSERT( !estimator->isParticleTypeAssigned( MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !estimator->isParticleTypeAssigned( MonteCarlo::ADJOINT_PHOTON ) );
  TEST_ASSERT( !estimator->isParticleTypeAssigned( MonteCarlo::ADJOINT_NEUTRON ) );
}

UNIT_TEST_INSTANTIATION( CellPulseHeightEstimator, setParticleTypes );

//---------------------------------------------------------------------------//
// Check that a partial history contribution can be added to the estimator
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( CellPulseHeightEstimator,
				   updateFromParticleEvent,
				   ContributionMultiplierPolicy )
{
  typedef MonteCarlo::CellPulseHeightEstimator<ContributionMultiplierPolicy> 
    CellPulseHeightEstimator;

  Teuchos::RCP<CellPulseHeightEstimator> estimator;
  initializePulseHeightEstimator<CellPulseHeightEstimator>( estimator );

  MonteCarlo::PhotonState particle( 0ull );
  particle.setWeight( 1.0 );
  particle.setEnergy( 1.0 );

  TEST_ASSERT( !estimator->hasUncommittedHistoryContribution() );

  estimator->updateFromParticleEnteringCellEvent( particle, 0 );

  TEST_ASSERT( estimator->hasUncommittedHistoryContribution() );

  particle.setEnergy( 0.5 );

  estimator->updateFromParticleLeavingCellEvent( particle, 0 );
  estimator->updateFromParticleEnteringCellEvent( particle, 1 );
  
  TEST_ASSERT( estimator->hasUncommittedHistoryContribution() );
  
  particle.setEnergy( 0.1 );
  
  estimator->updateFromParticleLeavingCellEvent( particle, 1 );

  TEST_ASSERT( estimator->hasUncommittedHistoryContribution() );
  
  estimator->commitHistoryContribution();

  TEST_ASSERT( !estimator->hasUncommittedHistoryContribution() );

  MonteCarlo::Estimator::setNumberOfHistories( 1.0 );
  MonteCarlo::Estimator::setEndTime( 1.0 );

  std::cout << std::endl << *estimator << std::endl;
}

UNIT_TEST_INSTANTIATION( CellPulseHeightEstimator, 
			 updateFromParticleEvent );

//---------------------------------------------------------------------------//
// end tstCellPulseHeightEstimator.cpp
//---------------------------------------------------------------------------//
