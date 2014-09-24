//---------------------------------------------------------------------------//
//!
//! \file   tstCellTrackLengthFluxEstimator.cpp
//! \author Alex Robinson
//! \brief  Cell track length flux estimator unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_CellTrackLengthFluxEstimator.hpp"
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
// Set the energy bins (and response functions)
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
template<typename CellTrackLengthFluxEstimator>
void initializeCellTrackLengthFluxEstimator( 
			Teuchos::RCP<CellTrackLengthFluxEstimator>& estimator )
{  
  // Set the entity ids
  Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle> 
    cell_ids( 2 );
  cell_ids[0] = 0;
  cell_ids[1] = 1;

  Teuchos::Array<double> cell_volumes( 2 );
  cell_volumes[0] = 1.0;
  cell_volumes[1] = 2.0;

  // Set the estimator multiplier
  double estimator_multiplier = 10.0;

  estimator.reset( new CellTrackLengthFluxEstimator( 0ull, 
						     estimator_multiplier,
						     cell_ids,
						     cell_volumes ) );
						     
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
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( CellTrackLengthFluxEstimator,
				   getNumberOfBins,
				   ContributionMultiplierPolicy )
{
  typedef MonteCarlo::CellTrackLengthFluxEstimator<ContributionMultiplierPolicy>
    CellTrackLengthFluxEstimator;

  Teuchos::RCP<CellTrackLengthFluxEstimator> estimator;
  initializeCellTrackLengthFluxEstimator<CellTrackLengthFluxEstimator>( 
								   estimator );

  TEST_EQUALITY_CONST( estimator->getNumberOfBins(), 2u );

  Teuchos::Array<double> time_bins( 3 );
  time_bins[0] = 0.0;
  time_bins[1] = 0.5;
  time_bins[2] = 1.0;

  estimator->template setBinBoundaries<MonteCarlo::TIME_DIMENSION>( time_bins );

  TEST_EQUALITY_CONST( estimator->getNumberOfBins(), 4u );

  Teuchos::Array<unsigned> coll_bins( 2 );
  coll_bins[0] = 0u;
  coll_bins[1] = std::numeric_limits<unsigned>::max();

  estimator->template setBinBoundaries<MonteCarlo::COLLISION_NUMBER_DIMENSION>( 
							       coll_bins );

  TEST_EQUALITY_CONST( estimator->getNumberOfBins(), 8u );
}

UNIT_TEST_INSTANTIATION( CellTrackLengthFluxEstimator, getNumberOfBins );

//---------------------------------------------------------------------------//
// Check that a partial history contribution can be added to the estimator
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( CellTrackLengthFluxEstimator,
				   updateFromParticleSubtrackEndingInCellEvent,
				   ContributionMultiplierPolicy )
{
  typedef MonteCarlo::CellTrackLengthFluxEstimator<ContributionMultiplierPolicy>
    CellTrackLengthFluxEstimator;

  Teuchos::RCP<CellTrackLengthFluxEstimator> estimator;
  initializeCellTrackLengthFluxEstimator<CellTrackLengthFluxEstimator>( 
								   estimator );

  MonteCarlo::PhotonState particle( 0ull );
  particle.setWeight( 1.0 );
  particle.setEnergy( 1.0 );

  TEST_ASSERT( !estimator->hasUncommittedHistoryContribution() );

  estimator->updateFromParticleSubtrackEndingInCellEvent( particle, 0, 1.0 );

  TEST_ASSERT( estimator->hasUncommittedHistoryContribution() );

  particle.setEnergy( 0.5 );

  estimator->updateFromParticleSubtrackEndingInCellEvent( particle, 1, 1.0 );

  TEST_ASSERT( estimator->hasUncommittedHistoryContribution() );

  estimator->commitHistoryContribution();

  TEST_ASSERT( !estimator->hasUncommittedHistoryContribution() );

  MonteCarlo::Estimator::setNumberOfHistories( 1.0 );
  MonteCarlo::Estimator::setEndTime( 1.0 );

  std::cout << std::endl << *estimator << std::endl;
}

UNIT_TEST_INSTANTIATION( CellTrackLengthFluxEstimator, 
			 updateFromParticleSubtrackEndingInCellEvent );

//---------------------------------------------------------------------------//
// end tstCellTrackLengthFluxEstimator.cpp
//---------------------------------------------------------------------------//
