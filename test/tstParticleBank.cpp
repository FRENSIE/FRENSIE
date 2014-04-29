//---------------------------------------------------------------------------//
//!
//! \file   tstParticleBank.cpp
//! \author Alex Robinson
//! \brief  Particle bank unit test
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FACEMC Includes
#include "ParticleBank.hpp"
#include "NeutronState.hpp"
#include "PhotonState.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that particles can be pushed to the particle bank
TEUCHOS_UNIT_TEST( ParticleBank, push )
{
  FACEMC::ParticleBank bank;

  TEST_ASSERT( bank.empty() );

  FACEMC::ParticleBank::ParticleStatePtr particle( 
					     new FACEMC::PhotonState( 0ull ) );
  
  bank.push( particle );

  TEST_ASSERT( !bank.empty() );
  TEST_EQUALITY_CONST( bank.size(), 1 );

  particle.reset( new FACEMC::NeutronState( 0ull ) );

  bank.push( particle, FACEMC::N__N_ELASTIC_REACTION );

  TEST_ASSERT( !bank.empty() );
  TEST_EQUALITY_CONST( bank.size(), 2 );
}

//---------------------------------------------------------------------------//
// Check that that the top element of the bank can be accessed
TEUCHOS_UNIT_TEST( ParticleBank, top )
{
  FACEMC::ParticleBank bank;
  
  FACEMC::ParticleBank::ParticleStatePtr particle( 
					     new FACEMC::PhotonState( 0ull ) );
  
  bank.push( particle );

  TEST_EQUALITY( particle,  bank.top() );

  const FACEMC::ParticleBank& const_bank = bank;
  
  TEST_EQUALITY( particle,  const_bank.top() );
}

//---------------------------------------------------------------------------//
// Check that particles can be removed from the bank
TEUCHOS_UNIT_TEST( ParticleBank, pop )
{
  FACEMC::ParticleBank bank;
  
  FACEMC::ParticleBank::ParticleStatePtr particle( 
					     new FACEMC::PhotonState( 0ull ) );
  
  bank.push( particle );

  TEST_ASSERT( !bank.empty() );

  bank.pop();
  
  TEST_ASSERT( bank.empty() );
}

//---------------------------------------------------------------------------//
// end tstParticleBank.cpp
//---------------------------------------------------------------------------//
