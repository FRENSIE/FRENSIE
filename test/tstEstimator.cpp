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

// FACEMC Includes
#include "FACEMC_UnitTestHarnessExtensions.hpp"
#include "Estimator.hpp"
#include "UniformDistribution.hpp"
#include "EnergySpaceResponseFunction.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestEstimator : public FACEMC::Estimator
{
public:
  TestEstimator( const unsigned long long id,
		 const double multiplier )
    : FACEMC::Estimator( id, multiplier )
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
  using FACEMC::Estimator::getBoundariesOfEnergyBin;
  using FACEMC::Estimator::getBoundariesOfCosineBin;
  using FACEMC::Estimator::getBoundariesOfTimeBin;
  using FACEMC::Estimator::getBoundariesOfCollisionNumberBin;
  using FACEMC::Estimator::getResponseFunctionName;
  using FACEMC::Estimator::evaluateResponseFunction;
  using FACEMC::Estimator::isEnergyInEstimatorEnergySpace;
  using FACEMC::Estimator::isAngleCosineInEstimatorCosineSpace;
  using FACEMC::Estimator::isTimeInEstimatorTimeSpace;
  using FACEMC::Estimator::isCollisionNumberInEstimatorCollisionNumberSpace;
  using FACEMC::Estimator::isPointInEstimatorPhaseSpace;
  using FACEMC::Estimator::calculateEnergyBinIndex;
  using FACEMC::Estimator::calculateCosineBinIndex;
  using FACEMC::Estimator::calculateTimeBinIndex;
  using FACEMC::Estimator::calculateCollisionNumberBinIndex;
  using FACEMC::Estimator::calculateBinIndex;
  using FACEMC::Estimator::calculateMean;
  using FACEMC::Estimator::calculateRelativeError;
  using FACEMC::Estimator::calculateVOV;
  using FACEMC::Estimator::calculateFOM;
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

  estimator.setEnergyBinBoundaries( energy_bin_boundaries );

  TEST_EQUALITY_CONST( estimator.getNumberOfEnergyBins(), 6u );
}

//---------------------------------------------------------------------------//
// Check that the energy boundaries of a bin can be returned
TEUCHOS_UNIT_TEST( Estimator, getBoundariesOfEnergyBin )
{
  FACEMC::Pair<double,double> bin_boundaries( 0.0, 1e-1 );
  
  FACEMC_TEST_EQUALITY( estimator.getBoundariesOfEnergyBin( 0u ),
			bin_boundaries );

  bin_boundaries( 1e-1, 1e-1 );

  FACEMC_TEST_EQUALITY( estimator.getBoundariesOfEnergyBin( 1u ),
			bin_boundaries );

  bin_boundaries( 1e-1, 1.0 );
  
  FACEMC_TEST_EQUALITY( estimator.getBoundariesOfEnergyBin( 2u ),
			bin_boundaries );

  bin_boundaries( 1.0, 10.0 );
  
  FACEMC_TEST_EQUALITY( estimator.getBoundariesOfEnergyBin( 3u ),
			bin_boundaries );

  bin_boundaries( 10.0, 10.0 );

  FACEMC_TEST_EQUALITY( estimator.getBoundariesOfEnergyBin( 4u ),
			bin_boundaries );

  bin_boundaries( 10.0, 20.0 );
    
  FACEMC_TEST_EQUALITY( estimator.getBoundariesOfEnergyBin( 5u ),
			bin_boundaries );
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
  
  estimator.setCosineBinBoundaries( cosine_bin_boundaries );
  
  TEST_EQUALITY_CONST( estimator.getNumberOfCosineBins(), 3u );
}

//---------------------------------------------------------------------------//
// Check that cosine boundaries of a bin can be returned
TEUCHOS_UNIT_TEST( Estimator, getBoundariesOfCosineBin )
{
  FACEMC::Pair<double,double> bin_boundaries( -1.0, -1.0/3.0 );

  FACEMC_TEST_EQUALITY( estimator.getBoundariesOfCosineBin( 0u ),
			bin_boundaries );

  bin_boundaries( -1.0/3.0, 1.0/3.0 );

  FACEMC_TEST_EQUALITY( estimator.getBoundariesOfCosineBin( 1u ),
			bin_boundaries );

  bin_boundaries( 1.0/3.0, 1.0 );

  FACEMC_TEST_EQUALITY( estimator.getBoundariesOfCosineBin( 2u ),
			bin_boundaries );
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

  estimator.setTimeBinBoundaries( time_bin_boundaries );
  
  TEST_EQUALITY_CONST( estimator.getNumberOfTimeBins(), 3u );
}

//---------------------------------------------------------------------------//
// Check that time boundaries of a bin can be returned
TEUCHOS_UNIT_TEST( Estimator, getBoundariesOfTimeBin )
{
  FACEMC::Pair<double,double> bin_boundaries( 0.0, 1e3 );

  FACEMC_TEST_EQUALITY( estimator.getBoundariesOfTimeBin( 0u ),
			bin_boundaries );

  bin_boundaries( 1e3, 1e5 );

  FACEMC_TEST_EQUALITY( estimator.getBoundariesOfTimeBin( 1u ),
			bin_boundaries );

  bin_boundaries( 1e5, 1e7 );

  FACEMC_TEST_EQUALITY( estimator.getBoundariesOfTimeBin( 2u ),
			bin_boundaries );
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

  estimator.setCollisionNumberBins( collision_number_bins );

  TEST_EQUALITY_CONST( estimator.getNumberOfCollisionNumberBins(), 4u );
}

//---------------------------------------------------------------------------//
// Check that the collision number boundaries of a bin can be returned
TEUCHOS_UNIT_TEST( Estimator, getBoundariesOfCollisionNumberBin )
{
  FACEMC::Pair<unsigned,unsigned>  bin_boundaries( 0u, 0u );

  FACEMC_TEST_EQUALITY( estimator.getBoundariesOfCollisionNumberBin( 0u ),
			bin_boundaries );

  bin_boundaries( 1u, 1u );

  FACEMC_TEST_EQUALITY( estimator.getBoundariesOfCollisionNumberBin( 1u ),
			bin_boundaries );

  bin_boundaries( 2u, 2u );

  FACEMC_TEST_EQUALITY( estimator.getBoundariesOfCollisionNumberBin( 2u ),
			bin_boundaries );

  bin_boundaries( 3u, std::numeric_limits<unsigned>::max() );

  FACEMC_TEST_EQUALITY( estimator.getBoundariesOfCollisionNumberBin( 3u ),
			bin_boundaries );
}

//---------------------------------------------------------------------------//
// Check that the total number of bins can be returned
TEUCHOS_UNIT_TEST( estimator, getNumberOfBins )
{
  TEST_EQUALITY_CONST( estimator.getNumberOfBins(), 216u );
}

//---------------------------------------------------------------------------//
// Check that the response functions can be set
TEUCHOS_UNIT_TEST( estimator, setResponseFunctions )
{
  Teuchos::Array<Teuchos::RCP<FACEMC::ResponseFunction> > 
    response_functions( 2 );
  
  Teuchos::RCP<FACEMC::OneDDistribution> energy_distribution(
			     new FACEMC::UniformDistribution( 0.0, 10, 1.0 ) );

  response_functions[0].reset( new FACEMC::EnergySpaceResponseFunction( 
						       "uniform_energy",
						       energy_distribution ) );
  response_functions[1] = FACEMC::ResponseFunction::default_response_function;

  estimator.setResponseFunctions( response_functions );

  TEST_EQUALITY_CONST( estimator.getNumberOfResponseFunctions(), 2u );
}

//---------------------------------------------------------------------------//
// Check that the response function names can be returned
TEUCHOS_UNIT_TEST( estimator, getResponseFunctionNames )
{
  TEST_EQUALITY_CONST( estimator.getResponseFunctionName( 0u ),
		       "uniform_energy" );
  TEST_EQUALITY_CONST( estimator.getResponseFunctionName( 1u ),
		       "default" );
}

//---------------------------------------------------------------------------//
// Check that the particle types that can contribute to the estimator can
// be set
TEUCHOS_UNIT_TEST( estimator, setParticleTypes )
{
  Teuchos::Array<FACEMC::ParticleType> particle_types( 2 );
  particle_types[0] = FACEMC::PHOTON;
  particle_types[1] = FACEMC::NEUTRON;

  estimator.setParticleTypes( particle_types );

  TEST_ASSERT( estimator.isParticleTypeAssigned( FACEMC::PHOTON ) );
  TEST_ASSERT( estimator.isParticleTypeAssigned( FACEMC::NEUTRON ) );
  TEST_ASSERT( !estimator.isParticleTypeAssigned( FACEMC::ADJOINT_PHOTON ) );
  TEST_ASSERT( !estimator.isParticleTypeAssigned( FACEMC::ADJOINT_NEUTRON ) );
}

//---------------------------------------------------------------------------//
// Check that the response functions can be evaluated
TEUCHOS_UNIT_TEST( estimator, evaluateResponseFunction )
{
  FACEMC::BasicParticleState particle;
  particle.setEnergy( 1.0 );

  double response_function_value = 
    estimator.evaluateResponseFunction( particle, 0u );

  TEST_EQUALITY_CONST( response_function_value, 1.0 );

  response_function_value = 
    estimator.evaluateResponseFunction( particle, 1u );

  TEST_EQUALITY_CONST( response_function_value, 1.0 );
}

//---------------------------------------------------------------------------//
// Check if the energy lies within the estimator energy space
TEUCHOS_UNIT_TEST( estimator, isEnergyInEstimatorEnergySpace )
{
  TEST_ASSERT( estimator.isEnergyInEstimatorEnergySpace( 0.0 ) );
  TEST_ASSERT( estimator.isEnergyInEstimatorEnergySpace( 20.0 ) );
  TEST_ASSERT( !estimator.isEnergyInEstimatorEnergySpace( 21.0 ) );
}

//---------------------------------------------------------------------------//
// Check if the angle cosine lies within the estimator angle cosine space
TEUCHOS_UNIT_TEST( estimator, isAngleCosineInEstimatorCosineSpace )
{
  TEST_ASSERT( estimator.isAngleCosineInEstimatorCosineSpace( -1.0 ) );
  TEST_ASSERT( estimator.isAngleCosineInEstimatorCosineSpace( 0.0 ) );
  TEST_ASSERT( estimator.isAngleCosineInEstimatorCosineSpace( 1.0 ) );
}

//---------------------------------------------------------------------------//
// Check if the time lies within the estimator time space
TEUCHOS_UNIT_TEST( estimator, isTimeInEstimatorTimeSpace )
{
  TEST_ASSERT( estimator.isTimeInEstimatorTimeSpace( 0.0 ) );
  TEST_ASSERT( estimator.isTimeInEstimatorTimeSpace( 1e7 ) );
  TEST_ASSERT( !estimator.isTimeInEstimatorTimeSpace( 2e7 ) );
}

//---------------------------------------------------------------------------//
// Check if the collision number lies within the estimator collision number
// space
TEUCHOS_UNIT_TEST( estimator, isCollisionNumberInEstimatorCollisionNumberSpace)
{
  TEST_ASSERT( estimator.isCollisionNumberInEstimatorCollisionNumberSpace(0u));
  TEST_ASSERT( estimator.isCollisionNumberInEstimatorCollisionNumberSpace(
				      std::numeric_limits<unsigned>::max() ) );
}

//---------------------------------------------------------------------------//
// Check if a phase space point lies within the estimator phase space
TEUCHOS_UNIT_TEST( estimator, isPointInEstimatorPhaseSpace )
{
  TEST_ASSERT( estimator.isPointInEstimatorPhaseSpace( 0.0, -1.0, 0.0, 0u ) );
  TEST_ASSERT( estimator.isPointInEstimatorPhaseSpace( 
				      20.0, 
				      1.0, 
				      1e7, 
				      std::numeric_limits<unsigned>::max() ) );
  TEST_ASSERT( !estimator.isPointInEstimatorPhaseSpace( 21.0, 0.0, 2e7, 0u ) );
}

//---------------------------------------------------------------------------//
// Check that the energy bin index can be calculated
TEUCHOS_UNIT_TEST( estimator, calculateEnergyBinIndex )
{
  unsigned bin_index = estimator.calculateEnergyBinIndex( 0.0 );

  TEST_EQUALITY_CONST( bin_index, 0u );

  bin_index = estimator.calculateEnergyBinIndex( 0.05 );

  TEST_EQUALITY_CONST( bin_index, 0u );

  bin_index = estimator.calculateEnergyBinIndex( 0.0999999999999 );

  TEST_EQUALITY_CONST( bin_index, 0u );
  
  bin_index = estimator.calculateEnergyBinIndex( 1e-1 );

  TEST_EQUALITY_CONST( bin_index, 1u );

  bin_index = estimator.calculateEnergyBinIndex( 0.1000000000001 );

  TEST_EQUALITY_CONST( bin_index, 2u );

  bin_index = estimator.calculateEnergyBinIndex( 1.0 );

  TEST_EQUALITY_CONST( bin_index, 2u );

  bin_index = estimator.calculateEnergyBinIndex( 1.0000000000001 );

  TEST_EQUALITY_CONST( bin_index, 3u );

  bin_index = estimator.calculateEnergyBinIndex( 9.9999999999999 );
    
  TEST_EQUALITY_CONST( bin_index, 3u );

  bin_index = estimator.calculateEnergyBinIndex( 10.0 );
  
  TEST_EQUALITY_CONST( bin_index, 4u );

  bin_index = estimator.calculateEnergyBinIndex( 10.000000000001 );

  TEST_EQUALITY_CONST( bin_index, 5u );

  bin_index = estimator.calculateEnergyBinIndex( 20.0 );

  TEST_EQUALITY_CONST( bin_index, 5u );
}

//---------------------------------------------------------------------------//
// Check that the cosine bin index can be calculated
TEUCHOS_UNIT_TEST( estimator, calculateCosineBinIndex )
{
  unsigned bin_index = estimator.calculateCosineBinIndex( -1.0 );

  TEST_EQUALITY_CONST( bin_index, 0u );

  bin_index = estimator.calculateCosineBinIndex( -1.0/3.0 );

  TEST_EQUALITY_CONST( bin_index, 0u );

  bin_index = estimator.calculateCosineBinIndex( -1.0/3.0 + 1e-9 );

  TEST_EQUALITY_CONST( bin_index, 1u );

  bin_index = estimator.calculateCosineBinIndex( 1.0/3.0 );

  TEST_EQUALITY_CONST( bin_index, 1u );

  bin_index = estimator.calculateCosineBinIndex( 1.0/3.0 + 1e-9 );
  
  TEST_EQUALITY_CONST( bin_index, 2u );

  bin_index = estimator.calculateCosineBinIndex( 1.0 );

  TEST_EQUALITY_CONST( bin_index, 2u );
}

//---------------------------------------------------------------------------//
// Check that the time bin index can be calculated
TEUCHOS_UNIT_TEST( estimator, calculateTimeBinIndex )
{
  unsigned bin_index = estimator.calculateTimeBinIndex( 0.0 );

  TEST_EQUALITY_CONST( bin_index, 0u );

  bin_index = estimator.calculateTimeBinIndex( 1e3 );

  TEST_EQUALITY_CONST( bin_index, 0u );

  bin_index = estimator.calculateTimeBinIndex( 1e3 + 1e-9 );

  TEST_EQUALITY_CONST( bin_index, 1u );

  bin_index = estimator.calculateTimeBinIndex( 1e5 );

  TEST_EQUALITY_CONST( bin_index, 1u );

  bin_index = estimator.calculateTimeBinIndex( 1e5 + 1e-9 );

  TEST_EQUALITY_CONST( bin_index, 2u );

  bin_index = estimator.calculateTimeBinIndex( 1e7 );

  TEST_EQUALITY_CONST( bin_index, 2u );
}

//---------------------------------------------------------------------------//
// Check that the collision number bin index can be calculated
TEUCHOS_UNIT_TEST( estimator, calculateCollisionNumberBinIndex )
{
  unsigned bin_index = estimator.calculateCollisionNumberBinIndex( 0u );

  TEST_EQUALITY_CONST( bin_index, 0u );

  bin_index = estimator.calculateCollisionNumberBinIndex( 1u );
  
  TEST_EQUALITY_CONST( bin_index, 1u );

  bin_index = estimator.calculateCollisionNumberBinIndex( 2u );

  TEST_EQUALITY_CONST( bin_index, 2u );

  bin_index = estimator.calculateCollisionNumberBinIndex( 3u );

  TEST_EQUALITY_CONST( bin_index, 3u );

  bin_index = estimator.calculateCollisionNumberBinIndex( 
					std::numeric_limits<unsigned>::max() );

  TEST_EQUALITY_CONST( bin_index, 3u );
}

//---------------------------------------------------------------------------//
// Check that the bin index for the desired response function can be 
// calculated
TEUCHOS_UNIT_TEST( estimator, calculateBinIndex )
{
  unsigned bin_index = estimator.calculateBinIndex( 10.0, 0.0, 1e6, 2u, 0u );

  TEST_EQUALITY_CONST( bin_index, 154 );
}

//---------------------------------------------------------------------------//
// Calculate the mean of a set of contributions
TEUCHOS_UNIT_TEST( estimator, calculateMean )
{
  FACEMC::Estimator::setNumberOfHistories( 100ull );

  double mean = estimator.calculateMean( 100.00 );

  TEST_EQUALITY_CONST( mean, 1.0 );
}

//---------------------------------------------------------------------------//
// Calculate the relative error of a set of contributions
TEUCHOS_UNIT_TEST( estimator, calculateRelativeError )
{
  double rel_err = estimator.calculateRelativeError( 100.0, 150.0 );

  TEST_FLOATING_EQUALITY( rel_err, 0.070710678118655, 1e-14 );
}

//---------------------------------------------------------------------------//
// Calculate the variance of the variance of a set of contributions
TEUCHOS_UNIT_TEST( estimator, calculateVOV )
{
  double vov = estimator.calculateVOV( 100.0, 150.0, 300.0, 800.0 );

  TEST_EQUALITY_CONST( vov, 0.07 );
}

//---------------------------------------------------------------------------//
// Calculate the figure of merit of a of an estimator bin
TEUCHOS_UNIT_TEST( estimator, calculateFOM )
{
  FACEMC::Estimator::setStartTime( 0.0 );
  FACEMC::Estimator::setEndTime( 1.0 );

  double fom = estimator.calculateFOM( 0.01 );

  TEST_EQUALITY_CONST( fom, 10000.0 );
}

//---------------------------------------------------------------------------//
// end tstEstimator.cpp
//---------------------------------------------------------------------------//
