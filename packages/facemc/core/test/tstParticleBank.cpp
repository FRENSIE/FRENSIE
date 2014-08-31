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
#include "Facemc_ParticleBank.hpp"
#include "Facemc_NeutronState.hpp"
#include "Facemc_PhotonState.hpp"
#include "Utility_GlobalOpenMPSession.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that particles can be pushed to the particle bank
TEUCHOS_UNIT_TEST( ParticleBank, push )
{
  Facemc::ParticleBank bank;
  
  #pragma omp parallel num_threads( Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() )
  {
    //#pragma omp critical
    {
      TEST_ASSERT( bank.empty() );
      
      unsigned history_number = Utility::GlobalOpenMPSession::getThreadId();
      
      // Facemc::ParticleState::pointerType particle( 
      // 				   new Facemc::PhotonState( history_number ) );
    
      // bank.push( particle );
      
      // TEST_ASSERT( !bank.empty() );
      // TEST_EQUALITY_CONST( bank.size(), 1 );
    
      // particle.reset( new Facemc::NeutronState( history_number + 1u ) );
      // std::cout << *particle << std::endl;
      // bank.push( particle, Facemc::N__N_ELASTIC_REACTION );
      
      // TEST_ASSERT( !bank.empty() );
      // TEST_EQUALITY_CONST( bank.size(), 2 );
    }
  }
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
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();
 
  int threads = 1;
 
  clp.setOption( "threads",
		 &threads,
		 "Number of threads to use" );
  
  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  const Teuchos::RCP<Teuchos::FancyOStream> out = Teuchos::VerboseObjectBase::getDefaultOStream();

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Set up the global OpenMP session
  if( Utility::GlobalOpenMPSession::isOpenMPUsed() )
    Utility::GlobalOpenMPSession::setNumberOfThreads( threads );
  
  // Run the unit tests
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  out->setProcRankAndSize( mpiSession.getRank(), mpiSession.getNProc() );
  out->setOutputToRootOnly( 0 );

  const bool success = Teuchos::UnitTestRepository::runUnitTests(*out);

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstParticleBank.cpp
//---------------------------------------------------------------------------//
