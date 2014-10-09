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
#include <Teuchos_ArrayRCP.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_StateSource.hpp"

Teuchos::RCP<MonteCarlo::ParticleSource> source;

//---------------------------------------------------------------------------//
// Testing Functions
//---------------------------------------------------------------------------//
// Initialize the source
void initializeSource()
{
  Teuchos::ArrayRCP<MonteCarlo::ParticleStateCore> raw_particle_states( 4 );

  MonteCarlo::ParticleStateCore particle_core_1( 1ull,
					     MonteCarlo::PHOTON,
					     1.0, 1.0, 1.0,
					     1.0, 0.0, 0.0,
					     1.0,
					     0.5,
					     1u,
					     1u,
					     0.25 );

  raw_particle_states[0] = particle_core_1;

  MonteCarlo::ParticleStateCore particle_core_2( 10ull,
					     MonteCarlo::NEUTRON,
					     2.0, 2.0, 2.0,
					     0.0, 1.0, 0.0,
					     2.0,
					     0.75,
					     2u,
					     2u,
					     0.3 );

  raw_particle_states[1] = particle_core_2;

  MonteCarlo::ParticleStateCore particle_core_3( 1ull,
					     MonteCarlo::PHOTON,
					     3.0, 3.0, 3.0,
					     0.0, 0.0, 1.0,
					     3.0,
					     0.9,
					     2u,
					     3u,
					     0.5 );

  raw_particle_states[2] = particle_core_3;

  MonteCarlo::ParticleStateCore particle_core_4( 2ull,
					     MonteCarlo::PHOTON,
					     1.0, 1.0, 1.0,
					     0.0, 0.0, 1.0,
					     3.0,
					     0.5,
					     2u,
					     1u,
					     0.5 );

  raw_particle_states[3] = particle_core_4;

  source.reset( new MonteCarlo::StateSource( raw_particle_states ) );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that particle states can be "sampled"
TEUCHOS_UNIT_TEST( StateSource, sampleParticleState )
{
  initializeSource();
  
  MonteCarlo::ParticleBank bank;
  source->sampleParticleState( bank );

  TEST_EQUALITY_CONST( bank.size(), 2 );

  Teuchos::RCP<MonteCarlo::ParticleState> particle = bank.top();
  bank.pop();

  TEST_EQUALITY_CONST( particle->getHistoryNumber(), 0ull );
  TEST_EQUALITY_CONST( particle->getParticleType(), MonteCarlo::PHOTON );
  TEST_EQUALITY_CONST( particle->getXPosition(), 1.0 );
  TEST_EQUALITY_CONST( particle->getYPosition(), 1.0 );
  TEST_EQUALITY_CONST( particle->getZPosition(), 1.0 );
  TEST_EQUALITY_CONST( particle->getXDirection(), 1.0 );
  TEST_EQUALITY_CONST( particle->getYDirection(), 0.0 );
  TEST_EQUALITY_CONST( particle->getZDirection(), 0.0 );
  TEST_EQUALITY_CONST( particle->getEnergy(), 1.0 );
  TEST_EQUALITY_CONST( particle->getTime(), 0.5 );
  TEST_EQUALITY_CONST( particle->getCollisionNumber(), 1u );
  TEST_EQUALITY_CONST( particle->getGenerationNumber(), 1u );
  TEST_EQUALITY_CONST( particle->getWeight(), 0.25 );

  particle = bank.top();
  bank.pop();

  TEST_EQUALITY_CONST( particle->getHistoryNumber(), 0ull );
  TEST_EQUALITY_CONST( particle->getParticleType(), MonteCarlo::PHOTON );
  TEST_EQUALITY_CONST( particle->getXPosition(), 3.0 );
  TEST_EQUALITY_CONST( particle->getYPosition(), 3.0 );
  TEST_EQUALITY_CONST( particle->getZPosition(), 3.0 );
  TEST_EQUALITY_CONST( particle->getXDirection(), 0.0 );
  TEST_EQUALITY_CONST( particle->getYDirection(), 0.0 );
  TEST_EQUALITY_CONST( particle->getZDirection(), 1.0 );
  TEST_EQUALITY_CONST( particle->getEnergy(), 3.0 );
  TEST_EQUALITY_CONST( particle->getTime(), 0.9 );
  TEST_EQUALITY_CONST( particle->getCollisionNumber(), 2u );
  TEST_EQUALITY_CONST( particle->getGenerationNumber(), 3u );
  TEST_EQUALITY_CONST( particle->getWeight(), 0.5 );

  // Sample from the source again
  source->sampleParticleState( bank );

  TEST_EQUALITY_CONST( bank.size(), 1 );

  particle = bank.top();
  bank.top();

  TEST_EQUALITY_CONST( particle->getHistoryNumber(), 1ull );
  TEST_EQUALITY_CONST( particle->getParticleType(), MonteCarlo::NEUTRON );
  TEST_EQUALITY_CONST( particle->getXPosition(), 2.0 );
  TEST_EQUALITY_CONST( particle->getYPosition(), 2.0 );
  TEST_EQUALITY_CONST( particle->getZPosition(), 2.0 );
  TEST_EQUALITY_CONST( particle->getXDirection(), 0.0 );
  TEST_EQUALITY_CONST( particle->getYDirection(), 1.0 );
  TEST_EQUALITY_CONST( particle->getZDirection(), 0.0 );
  TEST_EQUALITY_CONST( particle->getEnergy(), 2.0 );
  TEST_EQUALITY_CONST( particle->getTime(), 0.75 );
  TEST_EQUALITY_CONST( particle->getCollisionNumber(), 2u );
  TEST_EQUALITY_CONST( particle->getGenerationNumber(), 2u );
  TEST_EQUALITY_CONST( particle->getWeight(), 0.3 );

  // Attempting to get another particle state should cause an exception
  TEST_THROW( source->sampleParticleState( bank ), std::runtime_error );
}

//---------------------------------------------------------------------------//
// Check that the sampling efficiency can be returned
TEUCHOS_UNIT_TEST( StateSource, getSamplingEfficiency )
{
  TEST_EQUALITY_CONST( source->getSamplingEfficiency(), 1.0 );
}

//---------------------------------------------------------------------------//
// end tstStateSource.cpp
//---------------------------------------------------------------------------//
