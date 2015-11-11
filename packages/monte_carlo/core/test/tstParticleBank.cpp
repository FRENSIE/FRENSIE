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
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_ElectronState.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that particles can be pushed to the particle bank
TEUCHOS_UNIT_TEST( ParticleBank, push )
{
  MonteCarlo::ParticleBank bank;
    
  TEST_ASSERT( bank.empty() );
  
  unsigned history_number = 1.0;
    
  MonteCarlo::ParticleState::pointerType particle;
    
  particle.reset( new MonteCarlo::PhotonState( history_number ) );
    
  bank.push( particle );
    
  TEST_ASSERT( !bank.empty() );
  TEST_EQUALITY_CONST( bank.size(), 1 );

  particle.reset( new MonteCarlo::NeutronState( history_number ) );
      
  bank.push( particle, MonteCarlo::N__N_ELASTIC_REACTION );
    
  TEST_ASSERT( !bank.empty() );
  TEST_EQUALITY_CONST( bank.size(), 2 );
   
  particle.reset( new MonteCarlo::ElectronState( history_number ) );
      
  bank.push( particle );
    
  TEST_ASSERT( !bank.empty() );
  TEST_EQUALITY_CONST( bank.size(), 3 );
}

//---------------------------------------------------------------------------//
// Check that that the top element of the bank can be accessed
TEUCHOS_UNIT_TEST( ParticleBank, top )
{
  MonteCarlo::ParticleBank bank;
  
  MonteCarlo::ParticleState::pointerType particle( 
					     new MonteCarlo::PhotonState( 0ull ) );
  
  bank.push( particle );

  TEST_EQUALITY( particle,  bank.top() );

  const MonteCarlo::ParticleBank& const_bank = bank;
  
  TEST_EQUALITY( particle,  const_bank.top() );
}

//---------------------------------------------------------------------------//
// Check that particles can be removed from the bank
TEUCHOS_UNIT_TEST( ParticleBank, pop )
{
  MonteCarlo::ParticleBank bank;
  
  MonteCarlo::ParticleState::pointerType particle( 
					     new MonteCarlo::PhotonState( 0ull ) );
  
  bank.push( particle );

  TEST_ASSERT( !bank.empty() );

  bank.pop();
  
  TEST_ASSERT( bank.empty() );
}

//---------------------------------------------------------------------------//
// end tstParticleBank.cpp
//---------------------------------------------------------------------------//
