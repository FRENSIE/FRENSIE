//---------------------------------------------------------------------------//
//! 
//! \file   tstStateSource.cpp
//! \author Alex Robinson
//! \brief  State source unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FACEMC Includes
#include "BasicParticleState.hpp"
#include "ParticleState.hpp"
#include "StateSource.hpp"

Teuchos::RCP<FACEMC::StateSource> source;

//---------------------------------------------------------------------------//
// Testing Functions
//---------------------------------------------------------------------------//
// Initialize the source
void initializeSource()
{
  Teuchos::Array<FACEMC::BasicParticleState> particle_states( 3 );

  double position[3] = {1.0, 1.0, 1.0};
  double direction[3] = {1.0/sqrt(3.0),1.0/sqrt(3.0),1.0/sqrt(3.0)};
  
  FACEMC::BasicParticleState particle_1( FACEMC::PHOTON,
					 position,
					 direction,
					 1.0,
					 0.0,
					 1.0 );

  particle_states[0] = particle_1;

  FACEMC::BasicParticleState particle_2( FACEMC::PHOTON,
					 position,
					 direction,
					 2.0,
					 0.0,
					 1.0 );

  particle_states[1] = particle_2;

  FACEMC::BasicParticleState particle_3( FACEMC::NEUTRON,
					 position,
					 direction,
					 3.0,
					 0.0,
					 1.0 );

  particle_states[2] = particle_3;

  source.reset( new FACEMC::StateSource( particle_states ) );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that particle states can be "sampled"
TEUCHOS_UNIT_TEST( StateSource, sampleParticleState )
{
  initializeSource();

  FACEMC::ParticleState<unsigned long long> particle_1( 1ull );

  source->sampleParticleState( particle_1 );

  TEST_EQUALITY_CONST( particle_1.getParticleType(), FACEMC::PHOTON );
  TEST_EQUALITY_CONST( particle_1.getXPosition(), 1.0 );
  TEST_EQUALITY_CONST( particle_1.getYPosition(), 1.0 );
  TEST_EQUALITY_CONST( particle_1.getZPosition(), 1.0 );
  TEST_EQUALITY_CONST( particle_1.getXDirection(), 1.0/sqrt(3.0) );
  TEST_EQUALITY_CONST( particle_1.getYDirection(), 1.0/sqrt(3.0) );
  TEST_EQUALITY_CONST( particle_1.getZDirection(), 1.0/sqrt(3.0) );
  TEST_EQUALITY_CONST( particle_1.getEnergy(), 1.0 );
  TEST_EQUALITY_CONST( particle_1.getTime(), 0.0 );
  TEST_EQUALITY_CONST( particle_1.getWeight(), 1.0 );

  FACEMC::ParticleState<unsigned long long> particle_2( 2ull );
  
  source->sampleParticleState( particle_2 );

  TEST_EQUALITY_CONST( particle_2.getParticleType(), FACEMC::PHOTON );
  TEST_EQUALITY_CONST( particle_2.getXPosition(), 1.0 );
  TEST_EQUALITY_CONST( particle_2.getYPosition(), 1.0 );
  TEST_EQUALITY_CONST( particle_2.getZPosition(), 1.0 );
  TEST_EQUALITY_CONST( particle_2.getXDirection(), 1.0/sqrt(3.0) );
  TEST_EQUALITY_CONST( particle_2.getYDirection(), 1.0/sqrt(3.0) );
  TEST_EQUALITY_CONST( particle_2.getZDirection(), 1.0/sqrt(3.0) );
  TEST_EQUALITY_CONST( particle_2.getEnergy(), 2.0 );
  TEST_EQUALITY_CONST( particle_2.getTime(), 0.0 );
  TEST_EQUALITY_CONST( particle_2.getWeight(), 1.0 );

  FACEMC::ParticleState<unsigned long long> particle_3( 3ull );
  
  source->sampleParticleState( particle_3 );

  TEST_EQUALITY_CONST( particle_3.getParticleType(), FACEMC::NEUTRON );
  TEST_EQUALITY_CONST( particle_3.getXPosition(), 1.0 );
  TEST_EQUALITY_CONST( particle_3.getYPosition(), 1.0 );
  TEST_EQUALITY_CONST( particle_3.getZPosition(), 1.0 );
  TEST_EQUALITY_CONST( particle_3.getXDirection(), 1.0/sqrt(3.0) );
  TEST_EQUALITY_CONST( particle_3.getYDirection(), 1.0/sqrt(3.0) );
  TEST_EQUALITY_CONST( particle_3.getZDirection(), 1.0/sqrt(3.0) );
  TEST_EQUALITY_CONST( particle_3.getEnergy(), 3.0 );
  TEST_EQUALITY_CONST( particle_3.getTime(), 0.0 );
  TEST_EQUALITY_CONST( particle_3.getWeight(), 1.0 );

  // Attempting to get another particle state should cause an exception
  TEST_THROW( source->sampleParticleState( particle_3 ), std::runtime_error );
}

//---------------------------------------------------------------------------//
// Check that the sampling efficiency can be returned
TEUCHOS_UNIT_TEST( StateSource, getSamplingEfficiency )
{
  initializeSource();

  TEST_EQUALITY_CONST( source->getSamplingEfficiency(), 1.0 );
}

//---------------------------------------------------------------------------//
// end tstStateSource.cpp
//---------------------------------------------------------------------------//
