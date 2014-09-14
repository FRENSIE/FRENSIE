//---------------------------------------------------------------------------//
//!
//! \file   tstSurfaceCurrentEstimator.cpp
//! \author Alex Robinson
//! \brief  Surface current estimator unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_SurfaceCurrentEstimator.hpp"
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
template<typename SurfaceCurrentEstimator>
void initializeSurfaceCurrentEstimator( 
			     Teuchos::RCP<SurfaceCurrentEstimator>& estimator )
{  
  // Set the entity ids
  Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle> 
    surface_ids( 2 );
  surface_ids[0] = 0;
  surface_ids[1] = 1;

  // Set the estimator multiplier
  double estimator_multiplier = 10.0;

  estimator.reset( new SurfaceCurrentEstimator( 0ull, 
						estimator_multiplier,
						surface_ids ) );
						

  Teuchos::Array<MonteCarlo::ParticleType> particle_types( 1 );
  particle_types[0] = MonteCarlo::PHOTON;
  
  estimator->setParticleTypes( particle_types );

  Teuchos::RCP<MonteCarlo::Estimator> estimator_base = 
    Teuchos::rcp_dynamic_cast<MonteCarlo::Estimator>( estimator );
  
  // Set the estimator bins (and response functions)
  setEstimatorBins( estimator_base );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the number of bins can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( SurfaceCurrentEstimator,
				   getNumberOfBins,
				   ContributionMultiplierPolicy )
{
  typedef MonteCarlo::SurfaceCurrentEstimator<ContributionMultiplierPolicy>
    SurfaceCurrentEstimator;

  Teuchos::RCP<SurfaceCurrentEstimator> estimator;
  initializeSurfaceCurrentEstimator<SurfaceCurrentEstimator>( estimator );

  TEST_EQUALITY_CONST( estimator->getNumberOfBins(), 2u );

  Teuchos::Array<double> cosine_bins( 3 );
  cosine_bins[0] = -1.0;
  cosine_bins[1] = 0.0;
  cosine_bins[2] = 1.0;

  estimator->template setBinBoundaries<MonteCarlo::COSINE_DIMENSION>( cosine_bins);
  
  TEST_EQUALITY_CONST( estimator->getNumberOfBins(), 4u );

  Teuchos::Array<double> time_bins( 3 );
  time_bins[0] = 0.0;
  time_bins[1] = 0.5;
  time_bins[2] = 1.0;

  estimator->template setBinBoundaries<MonteCarlo::TIME_DIMENSION>( time_bins );

  TEST_EQUALITY_CONST( estimator->getNumberOfBins(), 8u );

  Teuchos::Array<unsigned> coll_bins( 2 );
  coll_bins[0] = 0u;
  coll_bins[1] = std::numeric_limits<unsigned>::max();

  estimator->template setBinBoundaries<MonteCarlo::COLLISION_NUMBER_DIMENSION>( 
							       coll_bins );

  TEST_EQUALITY_CONST( estimator->getNumberOfBins(), 16u );
}

UNIT_TEST_INSTANTIATION( SurfaceCurrentEstimator, getNumberOfBins );

//---------------------------------------------------------------------------//
// Check that a partial history contribution can be added to the estimator
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( SurfaceCurrentEstimator,
				   updateFromParticleCrossingSurfaceEvent,
				   ContributionMultiplierPolicy )
{
  typedef MonteCarlo::SurfaceCurrentEstimator<ContributionMultiplierPolicy>
    SurfaceCurrentEstimator;

  Teuchos::RCP<SurfaceCurrentEstimator> estimator;
  initializeSurfaceCurrentEstimator<SurfaceCurrentEstimator>( estimator );

  MonteCarlo::PhotonState particle( 0ull );
  particle.setWeight( 1.0 );
  particle.setEnergy( 1.0 );

  TEST_ASSERT( !estimator->hasUncommittedHistoryContribution() );

  estimator->updateFromParticleCrossingSurfaceEvent( particle, 0, 0 );

  TEST_ASSERT( estimator->hasUncommittedHistoryContribution() );

  particle.setEnergy( 0.5 );

  estimator->updateFromParticleCrossingSurfaceEvent( particle, 1, 1 );

  TEST_ASSERT( estimator->hasUncommittedHistoryContribution() );
  
  estimator->commitHistoryContribution();
  
  TEST_ASSERT( !estimator->hasUncommittedHistoryContribution() );

  MonteCarlo::Estimator::setNumberOfHistories( 1.0 );
  MonteCarlo::Estimator::setEndTime( 1.0 );

  std::cout << std::endl << *estimator << std::endl;
}

UNIT_TEST_INSTANTIATION( SurfaceCurrentEstimator, 
			 updateFromParticleCrossingSurfaceEvent );


//---------------------------------------------------------------------------//
// end tstSurfaceCurrentEstimator.cpp
//---------------------------------------------------------------------------//
