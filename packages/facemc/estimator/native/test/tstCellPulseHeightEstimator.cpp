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
#include "Facemc_CellPulseHeightEstimator.hpp"
#include "Facemc_PhotonState.hpp"
#include "Geometry_ModuleTraits.hpp"

//---------------------------------------------------------------------------//
// Instantiation Macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name ) \
  using namespace Facemc;						\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, WeightMultiplier ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, WeightAndEnergyMultiplier)\

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Set the entity energy bins (and response functions)
void setEstimatorBins( Teuchos::RCP<Facemc::Estimator>& estimator )
{
  // Set the energy bins
  Teuchos::Array<double> energy_bin_boundaries( 3 );
  energy_bin_boundaries[0] = 0.0;
  energy_bin_boundaries[1] = 1e-1;
  energy_bin_boundaries[2] = 1.0;

  estimator->setBinBoundaries<Facemc::ENERGY_DIMENSION>(energy_bin_boundaries);
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
					     entity_ids,
					     false ) );

  Teuchos::RCP<Facemc::Estimator> estimator_base = 
    Teuchos::rcp_dynamic_cast<Facemc::Estimator>( estimator );
  
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
  typedef Facemc::CellPulseHeightEstimator<ContributionMultiplierPolicy> 
    CellPulseHeightEstimator;

  Teuchos::RCP<CellPulseHeightEstimator> estimator;
  initializePulseHeightEstimator<CellPulseHeightEstimator>( estimator );

  TEST_EQUALITY_CONST( estimator->getNumberOfBins(), 2u );

  Teuchos::Array<double> double_bins( 2 );
  double_bins[0] = 0.0;
  double_bins[1] = 1.0;

  estimator->template setBinBoundaries<Facemc::COSINE_DIMENSION>( double_bins);
  
  TEST_EQUALITY_CONST( estimator->getNumberOfBins(), 2u );

  estimator->template setBinBoundaries<Facemc::TIME_DIMENSION>( double_bins );

  TEST_EQUALITY_CONST( estimator->getNumberOfBins(), 2u );

  Teuchos::Array<unsigned> unsigned_bins( 1 );
  unsigned_bins[0] = 0u;

  estimator->template setBinBoundaries<Facemc::COLLISION_NUMBER_DIMENSION>( 
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
  typedef Facemc::CellPulseHeightEstimator<ContributionMultiplierPolicy> 
    CellPulseHeightEstimator;

  Teuchos::RCP<CellPulseHeightEstimator> estimator;
  initializePulseHeightEstimator<CellPulseHeightEstimator>( estimator );

  Teuchos::Array<Facemc::ParticleType> particle_types( 4 );
  particle_types[0] = Facemc::PHOTON;
  particle_types[1] = Facemc::NEUTRON;
  particle_types[2] = Facemc::ADJOINT_PHOTON;
  particle_types[3] = Facemc::ADJOINT_NEUTRON;
  
  estimator->setParticleTypes( particle_types );

  TEST_ASSERT( estimator->isParticleTypeAssigned( Facemc::PHOTON ) );
  TEST_ASSERT( !estimator->isParticleTypeAssigned( Facemc::NEUTRON ) );
  TEST_ASSERT( !estimator->isParticleTypeAssigned( Facemc::ADJOINT_PHOTON ) );
  TEST_ASSERT( !estimator->isParticleTypeAssigned( Facemc::ADJOINT_NEUTRON ) );
}

UNIT_TEST_INSTANTIATION( CellPulseHeightEstimator, setParticleTypes );

//---------------------------------------------------------------------------//
// Check that a partial history contribution can be added to the estimator
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( CellPulseHeightEstimator,
				   addPartialHistoryContribution,
				   ContributionMultiplierPolicy )
{
  typedef Facemc::CellPulseHeightEstimator<ContributionMultiplierPolicy> 
    CellPulseHeightEstimator;

  Teuchos::RCP<CellPulseHeightEstimator> estimator;
  initializePulseHeightEstimator<CellPulseHeightEstimator>( estimator );

  Facemc::PhotonState particle( 0ull );
  particle.setWeight( 1.0 );
  particle.setEnergy( 1.0 );

  estimator->addPartialHistoryContribution( particle, 2, 0 );

  particle.setEnergy( 0.5 );

  estimator->addPartialHistoryContribution( particle, 0, 1 );

  particle.setEnergy( 0.1 );
  
  estimator->addPartialHistoryContribution( particle, 1, 2 );

  estimator->commitHistoryContribution();

  Facemc::Estimator::setNumberOfHistories( 1.0 );
  Facemc::Estimator::setEndTime( 1.0 );

  std::cout << std::endl << *estimator << std::endl;
}

UNIT_TEST_INSTANTIATION( CellPulseHeightEstimator, 
			 addPartialHistoryContribution );

//---------------------------------------------------------------------------//
// end tstCellPulseHeightEstimator.cpp
//---------------------------------------------------------------------------//
