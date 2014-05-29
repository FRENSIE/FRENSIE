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

// FRENSIE Includes
#include "Facemc_ParticleBank.hpp"
#include "Facemc_NeutronState.hpp"
#include "Facemc_PhotonState.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that particles can be pushed to the particle bank
TEUCHOS_UNIT_TEST( ParticleBank, push )
{
  Facemc::ParticleBank bank;

  TEST_ASSERT( bank.empty() );

  Facemc::ParticleState::pointerType particle( 
					     new Facemc::PhotonState( 0ull ) );
  
  bank.push( particle );

  TEST_ASSERT( !bank.empty() );
  TEST_EQUALITY_CONST( bank.size(), 1 );

  particle.reset( new Facemc::NeutronState( 0ull ) );

  bank.push( particle, Facemc::N__N_ELASTIC_REACTION );

  TEST_ASSERT( !bank.empty() );
  TEST_EQUALITY_CONST( bank.size(), 2 );
}

//---------------------------------------------------------------------------//
// Check that that the top element of the bank can be accessed
TEUCHOS_UNIT_TEST( ParticleBank, top )
{
  Facemc::ParticleBank bank;
  
  Facemc::ParticleState::pointerType particle( 
					     new Facemc::PhotonState( 0ull ) );
  
  bank.push( particle );

  TEST_EQUALITY( particle,  bank.top() );

  const Facemc::ParticleBank& const_bank = bank;
  
  TEST_EQUALITY( particle,  const_bank.top() );
}

//---------------------------------------------------------------------------//
// Check that particles can be removed from the bank
TEUCHOS_UNIT_TEST( ParticleBank, pop )
{
  Facemc::ParticleBank bank;
  
  Facemc::ParticleState::pointerType particle( 
					     new Facemc::PhotonState( 0ull ) );
  
  bank.push( particle );

  TEST_ASSERT( !bank.empty() );

  bank.pop();
  
  TEST_ASSERT( bank.empty() );
}

//---------------------------------------------------------------------------//
// end tstParticleBank.cpp
//---------------------------------------------------------------------------//
