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

// FRENSIE Includes
#include "Facemc_UnitTestHarnessExtensions.hpp"
#include "Facemc_Estimator.hpp"
#include "Facemc_EnergySpaceResponseFunction.hpp"
#include "Facemc_PhaseSpaceDimension.hpp"
#include "Facemc_PhotonState.hpp"
#include "Utility_UniformDistribution.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestEstimator : public Facemc::Estimator
{
public:
  TestEstimator( const unsigned long long id,
		 const double multiplier )
    : Facemc::Estimator( id, multiplier )
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

  // Allow public access to the estimator protected member functions
  using Facemc::Estimator::DimensionValueMap;
  using Facemc::Estimator::assignBinBoundaries;
  using Facemc::Estimator::getMultiplier;
  using Facemc::Estimator::getResponseFunctionName;
  using Facemc::Estimator::evaluateResponseFunction;
  using Facemc::Estimator::isPointInEstimatorPhaseSpace;
  using Facemc::Estimator::calculateBinIndex;
  using Facemc::Estimator::calculateMean;
  using Facemc::Estimator::calculateRelativeError;
  using Facemc::Estimator::calculateVOV;
  using Facemc::Estimator::calculateFOM;
};

//---------------------------------------------------------------------------//
// Global Testing Variables.
//---------------------------------------------------------------------------//
TestEstimator estimator( 0ull, 1.0 );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the estimator id can be returned
TEUCHOS_UNIT_TEST( Estimator, getId )
{
  TEST_EQUALITY_CONST( estimator.getId(), 0ull );
}

//---------------------------------------------------------------------------//
// Check that the multiplier can be returned
TEUCHOS_UNIT_TEST( Estimator, getMultiplier )
{
  TEST_EQUALITY_CONST( estimator.getMultiplier(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the energy bins can be set
TEUCHOS_UNIT_TEST( Estimator, setEnergyBinBoundaries )
{
  Teuchos::Array<double> energy_bin_boundaries( 7 );
  energy_bin_boundaries[0] = 0.0;
  energy_bin_boundaries[1] = 1e-1;
  energy_bin_boundaries[2] = 1e-1;
  energy_bin_boundaries[3] = 1.0;
  energy_bin_boundaries[4] = 10.0;
  energy_bin_boundaries[5] = 10.0;
  energy_bin_boundaries[6] = 20.0;

  estimator.setBinBoundaries<Facemc::ENERGY_DIMENSION>( energy_bin_boundaries);

  TEST_EQUALITY_CONST( estimator.getNumberOfBins( Facemc::ENERGY_DIMENSION ), 
		       6u );
}

//---------------------------------------------------------------------------//
// Check that cosine bins can be set
TEUCHOS_UNIT_TEST( Estimator, setCosineBinBoundaries )
{
  Teuchos::Array<double> cosine_bin_boundaries( 4 );
  cosine_bin_boundaries[0] = -1.0;
  cosine_bin_boundaries[1] = -1.0/3.0;
  cosine_bin_boundaries[2] = 1.0/3.0;
  cosine_bin_boundaries[3] = 1.0;
  
  estimator.setBinBoundaries<Facemc::COSINE_DIMENSION>( cosine_bin_boundaries);
  
  TEST_EQUALITY_CONST( estimator.getNumberOfBins( Facemc::COSINE_DIMENSION ), 
		       3u );
}

//---------------------------------------------------------------------------//
// Check that the time bins can be set
TEUCHOS_UNIT_TEST( Estimator, setTimeBinBoundaries )
{
  Teuchos::Array<double> time_bin_boundaries( 4 );
  time_bin_boundaries[0] = 0.0;
  time_bin_boundaries[1] = 1e3;
  time_bin_boundaries[2] = 1e5;
  time_bin_boundaries[3] = 1e7;

  estimator.setBinBoundaries<Facemc::TIME_DIMENSION>( time_bin_boundaries );
  
  TEST_EQUALITY_CONST( estimator.getNumberOfBins( Facemc::TIME_DIMENSION ), 
		       3u );
}

//---------------------------------------------------------------------------//
// Check that the collision number bins can be set
TEUCHOS_UNIT_TEST( Estimator, setCollisionNumberBins )
{
  Teuchos::Array<unsigned> collision_number_bins( 4 );
  collision_number_bins[0] = 0u;
  collision_number_bins[1] = 1u;
  collision_number_bins[2] = 2u;
  collision_number_bins[3] = std::numeric_limits<unsigned>::max();

  estimator.setBinBoundaries<Facemc::COLLISION_NUMBER_DIMENSION>( 
						       collision_number_bins );

  TEST_EQUALITY_CONST( estimator.getNumberOfBins( Facemc::COLLISION_NUMBER_DIMENSION ), 4u );
}

//---------------------------------------------------------------------------//
// Check that the total number of bins can be returned
TEUCHOS_UNIT_TEST( Estimator, getNumberOfBins )
{
  TEST_EQUALITY_CONST( estimator.getNumberOfBins(), 216u );
}

//---------------------------------------------------------------------------//
// Check that the response functions can be set
TEUCHOS_UNIT_TEST( Estimator, setResponseFunctions )
{
  Teuchos::Array<Teuchos::RCP<Facemc::ResponseFunction> > 
    response_functions( 2 );
  
  Teuchos::RCP<Utility::OneDDistribution> energy_distribution(
			    new Utility::UniformDistribution( 0.0, 10, 1.0 ) );

  response_functions[0].reset( new Facemc::EnergySpaceResponseFunction( 
						       "uniform_energy",
						       energy_distribution ) );
  response_functions[1] = Facemc::ResponseFunction::default_response_function;

  estimator.setResponseFunctions( response_functions );

  TEST_EQUALITY_CONST( estimator.getNumberOfResponseFunctions(), 2u );
}

//---------------------------------------------------------------------------//
// Check that the response function names can be returned
TEUCHOS_UNIT_TEST( Estimator, getResponseFunctionNames )
{
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
  Teuchos::Array<Facemc::ParticleType> particle_types( 2 );
  particle_types[0] = Facemc::PHOTON;
  particle_types[1] = Facemc::NEUTRON;

  estimator.setParticleTypes( particle_types );

  TEST_ASSERT( estimator.isParticleTypeAssigned( Facemc::PHOTON ) );
  TEST_ASSERT( estimator.isParticleTypeAssigned( Facemc::NEUTRON ) );
  TEST_ASSERT( !estimator.isParticleTypeAssigned( Facemc::ADJOINT_PHOTON ) );
  TEST_ASSERT( !estimator.isParticleTypeAssigned( Facemc::ADJOINT_NEUTRON ) );
}

//---------------------------------------------------------------------------//
// Check that the response functions can be evaluated
TEUCHOS_UNIT_TEST( Estimator, evaluateResponseFunction )
{
  Facemc::PhotonState particle( 0ull );
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
  TestEstimator::DimensionValueMap dimension_values;
  dimension_values[Facemc::ENERGY_DIMENSION] = Teuchos::any( 0.0 );
  dimension_values[Facemc::COSINE_DIMENSION] = Teuchos::any( -1.0 );
  dimension_values[Facemc::TIME_DIMENSION] = Teuchos::any( 0.0 );
  dimension_values[Facemc::COLLISION_NUMBER_DIMENSION] = Teuchos::any( 0u );

  TEST_ASSERT( estimator.isPointInEstimatorPhaseSpace( dimension_values ) );

  dimension_values[Facemc::ENERGY_DIMENSION] = Teuchos::any( 20.0 );
  dimension_values[Facemc::COSINE_DIMENSION] = Teuchos::any( 1.0 );
  dimension_values[Facemc::TIME_DIMENSION] = Teuchos::any( 1e7 );
  dimension_values[Facemc::COLLISION_NUMBER_DIMENSION] = 
    Teuchos::any( std::numeric_limits<unsigned>::max() );

  TEST_ASSERT( estimator.isPointInEstimatorPhaseSpace( dimension_values ) );

  dimension_values[Facemc::ENERGY_DIMENSION] = Teuchos::any( 21.0 );

  TEST_ASSERT( !estimator.isPointInEstimatorPhaseSpace( dimension_values ) );

  dimension_values[Facemc::ENERGY_DIMENSION] = Teuchos::any( 20.0 );
  dimension_values[Facemc::TIME_DIMENSION] = Teuchos::any( 2e7 );

  TEST_ASSERT( !estimator.isPointInEstimatorPhaseSpace( dimension_values ) );
}

//---------------------------------------------------------------------------//
// Check that the bin index for the desired response function can be 
// calculated
TEUCHOS_UNIT_TEST( Estimator, calculateBinIndex )
{
  TestEstimator::DimensionValueMap dimension_values;
  dimension_values[Facemc::ENERGY_DIMENSION] = Teuchos::any( 0.0 );
  dimension_values[Facemc::COSINE_DIMENSION] = Teuchos::any( -1.0 );
  dimension_values[Facemc::TIME_DIMENSION] = Teuchos::any( 0.0 );
  dimension_values[Facemc::COLLISION_NUMBER_DIMENSION] = Teuchos::any( 0u );
  
  unsigned bin_index = estimator.calculateBinIndex( dimension_values, 0u );

  TEST_EQUALITY_CONST( bin_index, 0u );

  bin_index = estimator.calculateBinIndex( dimension_values, 1u );

  TEST_EQUALITY_CONST( bin_index, 216u );
						    
  dimension_values[Facemc::ENERGY_DIMENSION] = Teuchos::any( 10.0 );
  dimension_values[Facemc::COSINE_DIMENSION] = Teuchos::any( 0.0 );
  dimension_values[Facemc::TIME_DIMENSION] = Teuchos::any( 1e6 );
  dimension_values[Facemc::COLLISION_NUMBER_DIMENSION] = Teuchos::any( 2u );
  
  bin_index = estimator.calculateBinIndex( dimension_values, 0u );

  TEST_EQUALITY_CONST( bin_index, 154u );

  bin_index = estimator.calculateBinIndex( dimension_values, 1u );

  TEST_EQUALITY_CONST( bin_index, 370u );

  dimension_values[Facemc::ENERGY_DIMENSION] = Teuchos::any( 20.0 );
  dimension_values[Facemc::COSINE_DIMENSION] = Teuchos::any( 1.0 );
  dimension_values[Facemc::TIME_DIMENSION] = Teuchos::any( 1e7 );
  dimension_values[Facemc::COLLISION_NUMBER_DIMENSION] = 
    Teuchos::any( std::numeric_limits<unsigned>::max() );

  bin_index = estimator.calculateBinIndex( dimension_values, 0u );

  TEST_EQUALITY_CONST( bin_index, 215u );

  bin_index = estimator.calculateBinIndex( dimension_values, 1u );

  TEST_EQUALITY_CONST( bin_index, 431u );
}

//---------------------------------------------------------------------------//
// Calculate the mean of a set of contributions
TEUCHOS_UNIT_TEST( Estimator, calculateMean )
{
  Facemc::Estimator::setNumberOfHistories( 100ull );

  double mean = estimator.calculateMean( 100.00 );

  TEST_EQUALITY_CONST( mean, 1.0 );
}

//---------------------------------------------------------------------------//
// Calculate the relative error of a set of contributions
TEUCHOS_UNIT_TEST( Estimator, calculateRelativeError )
{
  double rel_err = estimator.calculateRelativeError( 100.0, 150.0 );

  TEST_FLOATING_EQUALITY( rel_err, 0.070710678118655, 1e-14 );
}

//---------------------------------------------------------------------------//
// Calculate the variance of the variance of a set of contributions
TEUCHOS_UNIT_TEST( Estimator, calculateVOV )
{
  double vov = estimator.calculateVOV( 100.0, 150.0, 300.0, 800.0 );

  TEST_EQUALITY_CONST( vov, 0.07 );
}

//---------------------------------------------------------------------------//
// Calculate the figure of merit of a of an estimator bin
TEUCHOS_UNIT_TEST( Estimator, calculateFOM )
{
  Facemc::Estimator::setStartTime( 0.0 );
  Facemc::Estimator::setEndTime( 1.0 );

  double fom = estimator.calculateFOM( 0.01 );

  TEST_EQUALITY_CONST( fom, 10000.0 );
}

//---------------------------------------------------------------------------//
// end tstEstimator.cpp
//---------------------------------------------------------------------------//
