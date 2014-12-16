//---------------------------------------------------------------------------//
//!
//! \file   tstEstimator.cpp
//! \author Alex Robinson
//! \brief  Estimator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "MonteCarlo_UnitTestHarnessExtensions.hpp"
#include "MonteCarlo_Estimator.hpp"
#include "MonteCarlo_EstimatorHDF5FileHandler.hpp"
#include "MonteCarlo_EnergySpaceResponseFunction.hpp"
#include "MonteCarlo_PhaseSpaceDimension.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Utility_UniformDistribution.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestEstimator : public MonteCarlo::Estimator
{
public:
  TestEstimator( const unsigned long long id,
		 const double multiplier )
    : MonteCarlo::Estimator( id, multiplier )
  { /* ... */ }

  ~TestEstimator()
  { /* ... */ }

  void print( std::ostream& os ) const
  { 
    printEstimatorResponseFunctionNames( os );
    printEstimatorBins( os );
  }

  void commitHistoryContribution()
  { /* ... */ }

  void reduceEstimatorData(
	    const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
	    const int root_process )
  { /* ... */ }

  // Allow public access to the estimator protected member functions
  using MonteCarlo::Estimator::DimensionValueMap;
  using MonteCarlo::Estimator::setHasUncommittedHistoryContribution;
  using MonteCarlo::Estimator::unsetHasUncommittedHistoryContribution;
  using MonteCarlo::Estimator::assignBinBoundaries;
  using MonteCarlo::Estimator::getMultiplier;
  using MonteCarlo::Estimator::getResponseFunctionName;
  using MonteCarlo::Estimator::evaluateResponseFunction;
  using MonteCarlo::Estimator::isPointInEstimatorPhaseSpace;
  using MonteCarlo::Estimator::calculateBinIndex;
  using MonteCarlo::Estimator::calculateResponseFunctionIndex;
  using MonteCarlo::Estimator::processMoments;
};

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the estimator id can be returned
TEUCHOS_UNIT_TEST( Estimator, getId )
{
  TestEstimator estimator( 0, 1.0 );
  
  TEST_EQUALITY_CONST( estimator.getId(), 0ull );
}

//---------------------------------------------------------------------------//
// Check that the multiplier can be returned
TEUCHOS_UNIT_TEST( Estimator, getMultiplier )
{
  TestEstimator estimator( 0, 1.0 );
  
  TEST_EQUALITY_CONST( estimator.getMultiplier(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the energy bins can be set
TEUCHOS_UNIT_TEST( Estimator, setEnergyBinBoundaries )
{
  TestEstimator estimator( 0, 1.0 );
  
  Teuchos::Array<double> energy_bin_boundaries( 7 );
  energy_bin_boundaries[0] = 0.0;
  energy_bin_boundaries[1] = 1e-1;
  energy_bin_boundaries[2] = 1e-1;
  energy_bin_boundaries[3] = 1.0;
  energy_bin_boundaries[4] = 10.0;
  energy_bin_boundaries[5] = 10.0;
  energy_bin_boundaries[6] = 20.0;

  estimator.setBinBoundaries<MonteCarlo::ENERGY_DIMENSION>( energy_bin_boundaries);

  TEST_EQUALITY_CONST( estimator.getNumberOfBins( MonteCarlo::ENERGY_DIMENSION ), 
		       6u );
}

//---------------------------------------------------------------------------//
// Check that cosine bins can be set
TEUCHOS_UNIT_TEST( Estimator, setCosineBinBoundaries )
{
  TestEstimator estimator( 0, 1.0 );
  
  Teuchos::Array<double> cosine_bin_boundaries( 4 );
  cosine_bin_boundaries[0] = -1.0;
  cosine_bin_boundaries[1] = -1.0/3.0;
  cosine_bin_boundaries[2] = 1.0/3.0;
  cosine_bin_boundaries[3] = 1.0;
  
  estimator.setBinBoundaries<MonteCarlo::COSINE_DIMENSION>( cosine_bin_boundaries);
  
  TEST_EQUALITY_CONST( estimator.getNumberOfBins( MonteCarlo::COSINE_DIMENSION ), 
		       3u );
}

//---------------------------------------------------------------------------//
// Check that the time bins can be set
TEUCHOS_UNIT_TEST( Estimator, setTimeBinBoundaries )
{
  TestEstimator estimator( 0, 1.0 );
  
  Teuchos::Array<double> time_bin_boundaries( 4 );
  time_bin_boundaries[0] = 0.0;
  time_bin_boundaries[1] = 1e3;
  time_bin_boundaries[2] = 1e5;
  time_bin_boundaries[3] = 1e7;

  estimator.setBinBoundaries<MonteCarlo::TIME_DIMENSION>( time_bin_boundaries );
  
  TEST_EQUALITY_CONST( estimator.getNumberOfBins( MonteCarlo::TIME_DIMENSION ), 
		       3u );
}

//---------------------------------------------------------------------------//
// Check that the collision number bins can be set
TEUCHOS_UNIT_TEST( Estimator, setCollisionNumberBins )
{
  TestEstimator estimator( 0, 1.0 );
  
  Teuchos::Array<unsigned> collision_number_bins( 4 );
  collision_number_bins[0] = 0u;
  collision_number_bins[1] = 1u;
  collision_number_bins[2] = 2u;
  collision_number_bins[3] = std::numeric_limits<unsigned>::max();

  estimator.setBinBoundaries<MonteCarlo::COLLISION_NUMBER_DIMENSION>( 
						       collision_number_bins );

  TEST_EQUALITY_CONST( estimator.getNumberOfBins( MonteCarlo::COLLISION_NUMBER_DIMENSION ), 4u );
}

//---------------------------------------------------------------------------//
// Check that the total number of bins can be returned
TEUCHOS_UNIT_TEST( Estimator, getNumberOfBins )
{
  TestEstimator estimator( 0, 1.0 );
  
  Teuchos::Array<double> energy_bin_boundaries( 7 );
  energy_bin_boundaries[0] = 0.0;
  energy_bin_boundaries[1] = 1e-1;
  energy_bin_boundaries[2] = 1e-1;
  energy_bin_boundaries[3] = 1.0;
  energy_bin_boundaries[4] = 10.0;
  energy_bin_boundaries[5] = 10.0;
  energy_bin_boundaries[6] = 20.0;

  estimator.setBinBoundaries<MonteCarlo::ENERGY_DIMENSION>( energy_bin_boundaries);

  Teuchos::Array<double> time_bin_boundaries( 4 );
  time_bin_boundaries[0] = 0.0;
  time_bin_boundaries[1] = 1e3;
  time_bin_boundaries[2] = 1e5;
  time_bin_boundaries[3] = 1e7;

  estimator.setBinBoundaries<MonteCarlo::TIME_DIMENSION>( time_bin_boundaries);
  
  Teuchos::Array<unsigned> collision_number_bins( 4 );
  collision_number_bins[0] = 0u;
  collision_number_bins[1] = 1u;
  collision_number_bins[2] = 2u;
  collision_number_bins[3] = std::numeric_limits<unsigned>::max();

  estimator.setBinBoundaries<MonteCarlo::COLLISION_NUMBER_DIMENSION>( 
						       collision_number_bins );
  
  TEST_EQUALITY_CONST( estimator.getNumberOfBins(), 72u );
}

//---------------------------------------------------------------------------//
// Check that the response functions can be set
TEUCHOS_UNIT_TEST( Estimator, setResponseFunctions )
{
  TestEstimator estimator( 0, 1.0 );
  
  Teuchos::Array<Teuchos::RCP<MonteCarlo::ResponseFunction> > 
    response_functions( 2 );
  
  Teuchos::RCP<Utility::OneDDistribution> energy_distribution(
			    new Utility::UniformDistribution( 0.0, 10, 1.0 ) );

  response_functions[0].reset( new MonteCarlo::EnergySpaceResponseFunction( 
						       0,
						       "uniform_energy",
						       energy_distribution ) );
  response_functions[1] = 
    MonteCarlo::ResponseFunction::default_response_function;

  estimator.setResponseFunctions( response_functions );

  TEST_EQUALITY_CONST( estimator.getNumberOfResponseFunctions(), 2u );
  TEST_EQUALITY_CONST( estimator.getResponseFunctionName( 0u ),
		       "uniform_energy" );
  TEST_EQUALITY_CONST( estimator.getResponseFunctionName( 1u ),
		       "default" );
}


//---------------------------------------------------------------------------//
// Check that the particle types that can contribute to the estimator can
// be set
TEUCHOS_UNIT_TEST( Estimator, setParticleTypes )
{
  TestEstimator estimator( 0, 1.0 );
  
  Teuchos::Array<MonteCarlo::ParticleType> particle_types( 2 );
  particle_types[0] = MonteCarlo::PHOTON;
  particle_types[1] = MonteCarlo::NEUTRON;

  estimator.setParticleTypes( particle_types );

  TEST_ASSERT( estimator.isParticleTypeAssigned( MonteCarlo::PHOTON ) );
  TEST_ASSERT( estimator.isParticleTypeAssigned( MonteCarlo::NEUTRON ) );
  TEST_ASSERT( !estimator.isParticleTypeAssigned( MonteCarlo::ADJOINT_PHOTON ) );
  TEST_ASSERT( !estimator.isParticleTypeAssigned( MonteCarlo::ADJOINT_NEUTRON ) );
}

//---------------------------------------------------------------------------//
// Check that the response functions can be evaluated
TEUCHOS_UNIT_TEST( Estimator, evaluateResponseFunction )
{
  TestEstimator estimator( 0, 1.0 );
  
  Teuchos::Array<Teuchos::RCP<MonteCarlo::ResponseFunction> > 
    response_functions( 2 );
  
  Teuchos::RCP<Utility::OneDDistribution> energy_distribution(
			    new Utility::UniformDistribution( 0.0, 10, 1.0 ) );

  response_functions[0].reset( new MonteCarlo::EnergySpaceResponseFunction( 
						       0,
						       "uniform_energy",
						       energy_distribution ) );
  response_functions[1] = 
    MonteCarlo::ResponseFunction::default_response_function;

  estimator.setResponseFunctions( response_functions );

  MonteCarlo::PhotonState particle( 0ull );
  particle.setEnergy( 1.0 );

  double response_function_value = 
    estimator.evaluateResponseFunction( particle, 0u );

  TEST_EQUALITY_CONST( response_function_value, 1.0 );

  response_function_value = 
    estimator.evaluateResponseFunction( particle, 1u );

  TEST_EQUALITY_CONST( response_function_value, 1.0 );
}

//---------------------------------------------------------------------------//
// Check if a point is in the estimator phase space
TEUCHOS_UNIT_TEST( Estimator, isPointInEstimatorPhaseSpace )
{
  TestEstimator estimator( 0, 1.0 );
  
  Teuchos::Array<double> energy_bin_boundaries( 7 );
  energy_bin_boundaries[0] = 0.0;
  energy_bin_boundaries[1] = 1e-1;
  energy_bin_boundaries[2] = 1e-1;
  energy_bin_boundaries[3] = 1.0;
  energy_bin_boundaries[4] = 10.0;
  energy_bin_boundaries[5] = 10.0;
  energy_bin_boundaries[6] = 20.0;

  estimator.setBinBoundaries<MonteCarlo::ENERGY_DIMENSION>( energy_bin_boundaries);

  Teuchos::Array<double> cosine_bin_boundaries( 4 );
  cosine_bin_boundaries[0] = -1.0;
  cosine_bin_boundaries[1] = -1.0/3.0;
  cosine_bin_boundaries[2] = 1.0/3.0;
  cosine_bin_boundaries[3] = 1.0;
  
  estimator.setBinBoundaries<MonteCarlo::COSINE_DIMENSION>( cosine_bin_boundaries);

  Teuchos::Array<double> time_bin_boundaries( 4 );
  time_bin_boundaries[0] = 0.0;
  time_bin_boundaries[1] = 1e3;
  time_bin_boundaries[2] = 1e5;
  time_bin_boundaries[3] = 1e7;

  estimator.setBinBoundaries<MonteCarlo::TIME_DIMENSION>( time_bin_boundaries);
  
  Teuchos::Array<unsigned> collision_number_bins( 4 );
  collision_number_bins[0] = 0u;
  collision_number_bins[1] = 1u;
  collision_number_bins[2] = 2u;
  collision_number_bins[3] = std::numeric_limits<unsigned>::max();

  estimator.setBinBoundaries<MonteCarlo::COLLISION_NUMBER_DIMENSION>( 
						       collision_number_bins );

  TestEstimator::DimensionValueMap dimension_values;
  dimension_values[MonteCarlo::ENERGY_DIMENSION] = Teuchos::any( 0.0 );
  dimension_values[MonteCarlo::COSINE_DIMENSION] = Teuchos::any( -1.0 );
  dimension_values[MonteCarlo::TIME_DIMENSION] = Teuchos::any( 0.0 );
  dimension_values[MonteCarlo::COLLISION_NUMBER_DIMENSION] = Teuchos::any( 0u );

  TEST_ASSERT( estimator.isPointInEstimatorPhaseSpace( dimension_values ) );

  dimension_values[MonteCarlo::ENERGY_DIMENSION] = Teuchos::any( 20.0 );
  dimension_values[MonteCarlo::COSINE_DIMENSION] = Teuchos::any( 1.0 );
  dimension_values[MonteCarlo::TIME_DIMENSION] = Teuchos::any( 1e7 );
  dimension_values[MonteCarlo::COLLISION_NUMBER_DIMENSION] = 
    Teuchos::any( std::numeric_limits<unsigned>::max() );

  TEST_ASSERT( estimator.isPointInEstimatorPhaseSpace( dimension_values ) );

  dimension_values[MonteCarlo::ENERGY_DIMENSION] = Teuchos::any( 21.0 );

  TEST_ASSERT( !estimator.isPointInEstimatorPhaseSpace( dimension_values ) );

  dimension_values[MonteCarlo::ENERGY_DIMENSION] = Teuchos::any( 20.0 );
  dimension_values[MonteCarlo::TIME_DIMENSION] = Teuchos::any( 2e7 );

  TEST_ASSERT( !estimator.isPointInEstimatorPhaseSpace( dimension_values ) );
}

//---------------------------------------------------------------------------//
// Check that the bin index for the desired response function can be 
// calculated
TEUCHOS_UNIT_TEST( Estimator, calculateBinIndex )
{
  TestEstimator estimator( 0, 1.0 );
  
  // Set the bins
  Teuchos::Array<double> energy_bin_boundaries( 7 );
  energy_bin_boundaries[0] = 0.0;
  energy_bin_boundaries[1] = 1e-1;
  energy_bin_boundaries[2] = 1e-1;
  energy_bin_boundaries[3] = 1.0;
  energy_bin_boundaries[4] = 10.0;
  energy_bin_boundaries[5] = 10.0;
  energy_bin_boundaries[6] = 20.0;

  estimator.setBinBoundaries<MonteCarlo::ENERGY_DIMENSION>( energy_bin_boundaries);

  Teuchos::Array<double> cosine_bin_boundaries( 4 );
  cosine_bin_boundaries[0] = -1.0;
  cosine_bin_boundaries[1] = -1.0/3.0;
  cosine_bin_boundaries[2] = 1.0/3.0;
  cosine_bin_boundaries[3] = 1.0;
  
  estimator.setBinBoundaries<MonteCarlo::COSINE_DIMENSION>( cosine_bin_boundaries);

  Teuchos::Array<double> time_bin_boundaries( 4 );
  time_bin_boundaries[0] = 0.0;
  time_bin_boundaries[1] = 1e3;
  time_bin_boundaries[2] = 1e5;
  time_bin_boundaries[3] = 1e7;

  estimator.setBinBoundaries<MonteCarlo::TIME_DIMENSION>( time_bin_boundaries);
  
  Teuchos::Array<unsigned> collision_number_bins( 4 );
  collision_number_bins[0] = 0u;
  collision_number_bins[1] = 1u;
  collision_number_bins[2] = 2u;
  collision_number_bins[3] = std::numeric_limits<unsigned>::max();

  estimator.setBinBoundaries<MonteCarlo::COLLISION_NUMBER_DIMENSION>( 
						       collision_number_bins );
  
  TestEstimator::DimensionValueMap dimension_values;
  dimension_values[MonteCarlo::ENERGY_DIMENSION] = Teuchos::any( 0.0 );
  dimension_values[MonteCarlo::COSINE_DIMENSION] = Teuchos::any( -1.0 );
  dimension_values[MonteCarlo::TIME_DIMENSION] = Teuchos::any( 0.0 );
  dimension_values[MonteCarlo::COLLISION_NUMBER_DIMENSION] = Teuchos::any( 0u );
  // Set the response functions
  Teuchos::Array<Teuchos::RCP<MonteCarlo::ResponseFunction> > 
    response_functions( 2 );
  
  Teuchos::RCP<Utility::OneDDistribution> energy_distribution(
			    new Utility::UniformDistribution( 0.0, 10, 1.0 ) );

  response_functions[0].reset( new MonteCarlo::EnergySpaceResponseFunction( 
						       0,
						       "uniform_energy",
						       energy_distribution ) );
  response_functions[1] = 
    MonteCarlo::ResponseFunction::default_response_function;

  estimator.setResponseFunctions( response_functions );
  
  // Calculate the bin indices
  unsigned bin_index = estimator.calculateBinIndex( dimension_values, 0u );

  TEST_EQUALITY_CONST( bin_index, 0u );

  bin_index = estimator.calculateBinIndex( dimension_values, 1u );

  TEST_EQUALITY_CONST( bin_index, 216u );
						    
  dimension_values[MonteCarlo::ENERGY_DIMENSION] = Teuchos::any( 10.0 );
  dimension_values[MonteCarlo::COSINE_DIMENSION] = Teuchos::any( 0.0 );
  dimension_values[MonteCarlo::TIME_DIMENSION] = Teuchos::any( 1e6 );
  dimension_values[MonteCarlo::COLLISION_NUMBER_DIMENSION] = Teuchos::any( 2u );
  
  bin_index = estimator.calculateBinIndex( dimension_values, 0u );

  TEST_EQUALITY_CONST( bin_index, 154u );

  bin_index = estimator.calculateBinIndex( dimension_values, 1u );

  TEST_EQUALITY_CONST( bin_index, 370u );

  dimension_values[MonteCarlo::ENERGY_DIMENSION] = Teuchos::any( 20.0 );
  dimension_values[MonteCarlo::COSINE_DIMENSION] = Teuchos::any( 1.0 );
  dimension_values[MonteCarlo::TIME_DIMENSION] = Teuchos::any( 1e7 );
  dimension_values[MonteCarlo::COLLISION_NUMBER_DIMENSION] = 
    Teuchos::any( std::numeric_limits<unsigned>::max() );

  bin_index = estimator.calculateBinIndex( dimension_values, 0u );

  TEST_EQUALITY_CONST( bin_index, 215u );

  bin_index = estimator.calculateBinIndex( dimension_values, 1u );

  TEST_EQUALITY_CONST( bin_index, 431u );
}

//---------------------------------------------------------------------------//
// Check if the estimator can calculate the response function index
TEUCHOS_UNIT_TEST( Estimator, calculateResponseFunctionIndex )
{
  TestEstimator estimator( 0, 1.0 );
  
  // Set the bins
  Teuchos::Array<double> energy_bin_boundaries( 7 );
  energy_bin_boundaries[0] = 0.0;
  energy_bin_boundaries[1] = 1e-1;
  energy_bin_boundaries[2] = 1e-1;
  energy_bin_boundaries[3] = 1.0;
  energy_bin_boundaries[4] = 10.0;
  energy_bin_boundaries[5] = 10.0;
  energy_bin_boundaries[6] = 20.0;

  estimator.setBinBoundaries<MonteCarlo::ENERGY_DIMENSION>( energy_bin_boundaries);

  Teuchos::Array<double> cosine_bin_boundaries( 4 );
  cosine_bin_boundaries[0] = -1.0;
  cosine_bin_boundaries[1] = -1.0/3.0;
  cosine_bin_boundaries[2] = 1.0/3.0;
  cosine_bin_boundaries[3] = 1.0;
  
  estimator.setBinBoundaries<MonteCarlo::COSINE_DIMENSION>( cosine_bin_boundaries);

  Teuchos::Array<double> time_bin_boundaries( 4 );
  time_bin_boundaries[0] = 0.0;
  time_bin_boundaries[1] = 1e3;
  time_bin_boundaries[2] = 1e5;
  time_bin_boundaries[3] = 1e7;

  estimator.setBinBoundaries<MonteCarlo::TIME_DIMENSION>( time_bin_boundaries);
  
  Teuchos::Array<unsigned> collision_number_bins( 4 );
  collision_number_bins[0] = 0u;
  collision_number_bins[1] = 1u;
  collision_number_bins[2] = 2u;
  collision_number_bins[3] = std::numeric_limits<unsigned>::max();

  estimator.setBinBoundaries<MonteCarlo::COLLISION_NUMBER_DIMENSION>( 
						       collision_number_bins );
  
  // Set the response functions
  Teuchos::Array<Teuchos::RCP<MonteCarlo::ResponseFunction> > 
    response_functions( 2 );
  
  Teuchos::RCP<Utility::OneDDistribution> energy_distribution(
			    new Utility::UniformDistribution( 0.0, 10, 1.0 ) );

  response_functions[0].reset( new MonteCarlo::EnergySpaceResponseFunction( 
						       0,
						       "uniform_energy",
						       energy_distribution ) );
  response_functions[1] = 
    MonteCarlo::ResponseFunction::default_response_function;

  estimator.setResponseFunctions( response_functions );
  
  // Calculate the response function index
  unsigned bin_index = 0u;
  
  unsigned response_function_index = 
    estimator.calculateResponseFunctionIndex( bin_index );

  TEST_EQUALITY_CONST( response_function_index, 0u );

  bin_index = 215;

  response_function_index = 
    estimator.calculateResponseFunctionIndex( bin_index );

  TEST_EQUALITY_CONST( response_function_index, 0u );

  bin_index = 216;

  response_function_index = 
    estimator.calculateResponseFunctionIndex( bin_index );

  TEST_EQUALITY_CONST( response_function_index, 1u );

  bin_index = 431;

  response_function_index = 
    estimator.calculateResponseFunctionIndex( bin_index );

  TEST_EQUALITY_CONST( response_function_index, 1u );
}

//---------------------------------------------------------------------------//
// Check if the estimator has an uncommitted history contribution
TEUCHOS_UNIT_TEST( Estimator, hasUncommittedHisotryContribution_serial )
{
  TestEstimator estimator( 0, 1.0 );
  
  TEST_ASSERT( !estimator.hasUncommittedHistoryContribution() );
  
  estimator.setHasUncommittedHistoryContribution( 0u );

  TEST_ASSERT( estimator.hasUncommittedHistoryContribution() );

  estimator.unsetHasUncommittedHistoryContribution( 0u );

  TEST_ASSERT( !estimator.hasUncommittedHistoryContribution() );
}

//---------------------------------------------------------------------------//
// Check if the estimator has an uncommitted history contribution on a 
// given thread
TEUCHOS_UNIT_TEST( Estimator, hasUncommittedHistoryContribution_parallel_safe )
{
  TestEstimator estimator( 0, 1.0 );

  estimator.enableThreadSupport( 
		 Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );
  
  #pragma omp parallel num_threads( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() )
  {
    unsigned thread_id = Utility::GlobalOpenMPSession::getThreadId();
    
    #pragma omp critical(thread_check)
    {
      // Explicit thread id
      TEST_ASSERT( !estimator.hasUncommittedHistoryContribution( thread_id ) );
      // Implicit thread id
      TEST_ASSERT( !estimator.hasUncommittedHistoryContribution() );
    
      estimator.setHasUncommittedHistoryContribution( thread_id );

      TEST_ASSERT( estimator.hasUncommittedHistoryContribution() );
      
      estimator.unsetHasUncommittedHistoryContribution( thread_id );
      
      TEST_ASSERT( !estimator.hasUncommittedHistoryContribution() );
    }
  }
}

//---------------------------------------------------------------------------//
// Process the first and second moments
TEUCHOS_UNIT_TEST( Estimator, processMoments_two )
{
  TestEstimator estimator( 0, 1.0 );
  
  MonteCarlo::Estimator::setNumberOfHistories( 100ull );

  double mean;
  double relative_error;

  Utility::Pair<double,double> moments( 100.0, 150.0 );

  estimator.processMoments( moments,
			    1.0,
			    mean,
			    relative_error );

  TEST_EQUALITY_CONST( mean, 1.0 );
  TEST_FLOATING_EQUALITY( relative_error, 0.070710678118655, 1e-14 );
}

//---------------------------------------------------------------------------//
// Process the first, second, third and fourth moments
TEUCHOS_UNIT_TEST( Estimator, processMoments_four )
{
  TestEstimator estimator( 0, 1.0 );
  
  MonteCarlo::Estimator::setNumberOfHistories( 100ull );
  MonteCarlo::Estimator::setStartTime( 0.0 );
  MonteCarlo::Estimator::setEndTime( 1.0 );

  double mean;
  double relative_error;
  double variance_of_variance;
  double figure_of_merit;

  Utility::Quad<double,double,double,double> moments( 100.0,
						      150.0,
						      300.0,
						      800.0 );

  estimator.processMoments( moments,
			    1.0,
			    mean,
			    relative_error,
			    variance_of_variance,
			    figure_of_merit );
  
  TEST_EQUALITY_CONST( mean, 1.0 );
  TEST_FLOATING_EQUALITY( relative_error, 0.070710678118655, 1e-14 );
  TEST_EQUALITY_CONST( variance_of_variance, 0.07 );
  TEST_EQUALITY_CONST( figure_of_merit, 200.0 );
}

//---------------------------------------------------------------------------//
// Check that the estimator data can be exported
TEUCHOS_UNIT_TEST( Estimator, exportData )
{
  TestEstimator estimator( 0, 10.0 );
  
  Teuchos::Array<double> energy_bin_boundaries, cosine_bin_boundaries,
    time_bin_boundaries;
  Teuchos::Array<unsigned> collision_number_bins;
  
  {
    // Set the bins
    energy_bin_boundaries.resize( 7 );
    energy_bin_boundaries[0] = 0.0;
    energy_bin_boundaries[1] = 1e-1;
    energy_bin_boundaries[2] = 1e-1;
    energy_bin_boundaries[3] = 1.0;
    energy_bin_boundaries[4] = 10.0;
    energy_bin_boundaries[5] = 10.0;
    energy_bin_boundaries[6] = 20.0;

    estimator.setBinBoundaries<MonteCarlo::ENERGY_DIMENSION>( energy_bin_boundaries);

    cosine_bin_boundaries.resize( 4 );
    cosine_bin_boundaries[0] = -1.0;
    cosine_bin_boundaries[1] = -1.0/3.0;
    cosine_bin_boundaries[2] = 1.0/3.0;
    cosine_bin_boundaries[3] = 1.0;
  
    estimator.setBinBoundaries<MonteCarlo::COSINE_DIMENSION>( cosine_bin_boundaries);

    time_bin_boundaries.resize( 4 );
    time_bin_boundaries[0] = 0.0;
    time_bin_boundaries[1] = 1e3;
    time_bin_boundaries[2] = 1e5;
    time_bin_boundaries[3] = 1e7;
    
    estimator.setBinBoundaries<MonteCarlo::TIME_DIMENSION>( time_bin_boundaries);
    
    collision_number_bins.resize( 4 );
    collision_number_bins[0] = 0u;
    collision_number_bins[1] = 1u;
    collision_number_bins[2] = 2u;
    collision_number_bins[3] = std::numeric_limits<unsigned>::max();

    estimator.setBinBoundaries<MonteCarlo::COLLISION_NUMBER_DIMENSION>( 
						       collision_number_bins );
  
    // Set the response functions
    Teuchos::Array<Teuchos::RCP<MonteCarlo::ResponseFunction> > 
      response_functions( 2 );
  
    Teuchos::RCP<Utility::OneDDistribution> energy_distribution(
			    new Utility::UniformDistribution( 0.0, 10, 1.0 ) );

    response_functions[0].reset( new MonteCarlo::EnergySpaceResponseFunction( 
						       0,
						       "uniform_energy",
						       energy_distribution ) );
    response_functions[1] = 
      MonteCarlo::ResponseFunction::default_response_function;

    estimator.setResponseFunctions( response_functions );

    // Set the particle types
    Teuchos::Array<MonteCarlo::ParticleType> particle_types( 2 );
    particle_types[0] = MonteCarlo::PHOTON;
    particle_types[1] = MonteCarlo::NEUTRON;

    estimator.setParticleTypes( particle_types );
  }

  // Set up the hdf5 file
  MonteCarlo::EstimatorHDF5FileHandler hdf5_file_handler( "test_estimator.h5");

  estimator.exportData( hdf5_file_handler, false );

  // Make sure that the estimator exists in the hdf5 file
  TEST_ASSERT( hdf5_file_handler.doesEstimatorExist( 0u ) );

  // Check that the estimator multiplier has been set
  double multiplier;
  hdf5_file_handler.getEstimatorMultiplier( 0u, multiplier );

  TEST_EQUALITY_CONST( multiplier, 10.0 );

  // Check that the estimator response function ordering has been set
  Teuchos::Array<unsigned> response_function_ordering;
  hdf5_file_handler.getEstimatorResponseFunctionOrdering( 
						  0u,
						  response_function_ordering );
  
  TEST_EQUALITY_CONST( response_function_ordering.size(), 2 );
  TEST_EQUALITY_CONST( response_function_ordering[0], 0 );
  TEST_EQUALITY( response_function_ordering[1], 
		 std::numeric_limits<unsigned>::max() );
  
  // Check that the estimator dimension ordering has been set
  Teuchos::Array<MonteCarlo::PhaseSpaceDimension> dimension_ordering;
  hdf5_file_handler.getEstimatorDimensionOrdering( 0u, dimension_ordering );
  
  TEST_EQUALITY_CONST( dimension_ordering.size(), 4 );
  TEST_EQUALITY_CONST( dimension_ordering[0], MonteCarlo::ENERGY_DIMENSION );
  TEST_EQUALITY_CONST( dimension_ordering[1], MonteCarlo::COSINE_DIMENSION );
  TEST_EQUALITY_CONST( dimension_ordering[2], MonteCarlo::TIME_DIMENSION );
  TEST_EQUALITY_CONST( dimension_ordering[3], 
		       MonteCarlo::COLLISION_NUMBER_DIMENSION );

  // Check that the energy bins have been set
  Teuchos::Array<double> energy_bin_boundaries_copy;
  hdf5_file_handler.getEstimatorBinBoundaries<MonteCarlo::ENERGY_DIMENSION>( 
						  0u,
						  energy_bin_boundaries_copy );

  TEST_COMPARE_ARRAYS( energy_bin_boundaries, energy_bin_boundaries_copy );

  // Check that the cosine bins have been set
  Teuchos::Array<double> cosine_bin_boundaries_copy;
  hdf5_file_handler.getEstimatorBinBoundaries<MonteCarlo::COSINE_DIMENSION>( 
						  0u, 
						  cosine_bin_boundaries_copy );

  TEST_COMPARE_ARRAYS( cosine_bin_boundaries, cosine_bin_boundaries_copy );

  // Check that the time bins have been set
  Teuchos::Array<double> time_bin_boundaries_copy;
  hdf5_file_handler.getEstimatorBinBoundaries<MonteCarlo::TIME_DIMENSION>(
						    0u,
						    time_bin_boundaries_copy );

  TEST_COMPARE_ARRAYS( time_bin_boundaries, time_bin_boundaries_copy );

  // Check that the collision number bins have been set
  Teuchos::Array<unsigned> collision_number_bins_copy;
  hdf5_file_handler.getEstimatorBinBoundaries<MonteCarlo::COLLISION_NUMBER_DIMENSION>(
						  0u,
						  collision_number_bins_copy );

  TEST_COMPARE_ARRAYS( collision_number_bins, collision_number_bins_copy );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  int threads = 1;

  clp.setOption( "threads",
		 &threads,
		 "Number of threads to use" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Set up the global OpenMP session
  if( Utility::GlobalOpenMPSession::isOpenMPUsed() )
    Utility::GlobalOpenMPSession::setNumberOfThreads( threads );

  // Run the unit tests
  const bool success = Teuchos::UnitTestRepository::runUnitTests(*out);

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstEstimator.cpp
//---------------------------------------------------------------------------//
