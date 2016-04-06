//---------------------------------------------------------------------------//
//! 
//! \file   tstDistributedCachedStateParticleSource.cpp
//! \author Alex Robinson
//! \brief  Cached state particle source unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <memory>

// Boost Includes
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/nvp.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_GlobalMPISession.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_DefaultComm.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_CachedStateParticleSource.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "Utility_RandomNumberGenerator.hpp"

//---------------------------------------------------------------------------//
// Testing variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::ParticleSource> source;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the source data can be reduced
TEUCHOS_UNIT_TEST( DistributedCachedStateParticleSource, reduceData )
{
  MonteCarlo::ParticleBank bank;

  source->sampleParticleState( bank, Teuchos::GlobalMPISession::getRank() );
  
  if( Teuchos::GlobalMPISession::getRank() == 0 )
  {
    TEST_EQUALITY_CONST( source->getNumberOfTrials(), 2 );
    TEST_EQUALITY_CONST( source->getNumberOfSamples(), 2 );
    TEST_EQUALITY_CONST( source->getSamplingEfficiency(), 1.0 );
  }
  else
  {
    TEST_EQUALITY_CONST( source->getNumberOfTrials(), 1 );
    TEST_EQUALITY_CONST( source->getNumberOfSamples(), 1 );
    TEST_EQUALITY_CONST( source->getSamplingEfficiency(), 1.0 );
  }

  Teuchos::RCP<const Teuchos::Comm<unsigned long long> > comm = 
    Teuchos::DefaultComm<unsigned long long>::getComm();
  
  comm->barrier();

  source->reduceData( comm, 0 );

  // Check that the source data has been gathered on the root process
  if( comm->getRank() == 0 )
  {
    TEST_EQUALITY_CONST( source->getNumberOfTrials(), comm->getSize()+1 );
    TEST_EQUALITY_CONST( source->getNumberOfSamples(), comm->getSize()+1 );
    TEST_EQUALITY_CONST( source->getSamplingEfficiency(), 1.0 );
  }
  // Check that the source data on the non-root processes has been reset
  else
  {
    TEST_EQUALITY_CONST( source->getNumberOfTrials(), 0 );
    TEST_EQUALITY_CONST( source->getNumberOfSamples(), 0 );
    TEST_EQUALITY_CONST( source->getSamplingEfficiency(), 1.0 );
  }
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  out->setProcRankAndSize( mpiSession.getRank(), mpiSession.getNProc() );

  mpiSession.barrier();

  // Initialize the source
  {
    MonteCarlo::ParticleBank bank;
    
    boost::shared_ptr<MonteCarlo::ParticleState> particle( 
					 new MonteCarlo::PhotonState( 1ull ) );

    bank.push( *particle );
    
    particle.reset( new MonteCarlo::NeutronState( 10ull ) );
    
    bank.push( *particle );
    
    particle.reset( new MonteCarlo::PhotonState( 1ull ) );
    
    bank.push( *particle );
    
    particle.reset( new MonteCarlo::ElectronState( 11ull ) );
    
    bank.push( *particle );

    particle.reset( new MonteCarlo::NeutronState( 12ull ) );
  
    bank.push( *particle );
  
    particle.reset( new MonteCarlo::PhotonState( 13ull ) );
    
    bank.push( *particle );
    
    particle.reset( new MonteCarlo::ElectronState( 14ull ) );
    
    bank.push( *particle );
    
    particle.reset( new MonteCarlo::NeutronState( 15ull ) );
    
    bank.push( *particle );
    
    particle.reset( new MonteCarlo::PhotonState( 16ull ) );
    
    bank.push( *particle );

    std::ostringstream oss;

    oss << "test_state_source_bank_archive_proc_" << mpiSession.getRank();

    std::string bank_name_in_archive( "state_bank" );

    {
      std::ofstream ofs( oss.str().c_str() );
    
      boost::archive::xml_oarchive ar(ofs);
      ar << boost::serialization::make_nvp( bank_name_in_archive.c_str(), 
                                            bank );
    }

    source.reset( new MonteCarlo::CachedStateParticleSource(
                                    oss.str(),
                                    bank_name_in_archive,
                                    Utility::ArchivableObject::XML_ARCHIVE ) );
  }
  
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
  
  // Run the unit tests
  Teuchos::UnitTestRepository::setGloballyReduceTestResult( true );
  
  const bool success = Teuchos::UnitTestRepository::runUnitTests( *out );

  mpiSession.barrier();

  out->setOutputToRootOnly( 0 );

  if( success )
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstDistributedCachedStateParticleSource.cpp
//---------------------------------------------------------------------------//
