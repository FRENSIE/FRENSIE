//---------------------------------------------------------------------------//
//! 
//! \file   tstCachedStateParticleSource.cpp
//! \author Alex Robinson
//! \brief  Cached state particle source unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Boost Includes
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/nvp.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "MonteCarlo_CachedStateParticleSource.hpp"
#include "MonteCarlo_SourceHDF5FileHandler.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "Utility_RandomNumberGenerator.hpp"

//---------------------------------------------------------------------------//
// Testing functions
//---------------------------------------------------------------------------//
// Initialize the source
void initializeSource( std::shared_ptr<MonteCarlo::ParticleSource>& source )
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
  
  std::string bank_archive_name( "test_state_source_bank_archive.xml" );
  std::string bank_name_in_archive( "state_bank" );
 
  {
    std::ofstream ofs( bank_archive_name.c_str() );
    
    boost::archive::xml_oarchive ar(ofs);
    ar << boost::serialization::make_nvp( bank_name_in_archive.c_str(), bank );
  }

  source.reset( new MonteCarlo::CachedStateParticleSource( 
				    bank_archive_name,
				    bank_name_in_archive,
				    Utility::ArchivableObject::XML_ARCHIVE ) );
}

// Compare history numbers
bool compareHistoryNumbers( const MonteCarlo::ParticleState& state_a,
			    const MonteCarlo::ParticleState& state_b )
{
  return state_a.getHistoryNumber() < state_b.getHistoryNumber();
}


//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that particle states can be "sampled"
TEUCHOS_UNIT_TEST( CachedStateParticleSource, sampleParticleState )
{
  std::shared_ptr<MonteCarlo::ParticleSource> source;

  initializeSource( source );
  
  MonteCarlo::ParticleBank bank;
  source->sampleParticleState( bank, 0 );

  TEST_EQUALITY_CONST( bank.size(), 2 );

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 0ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::PHOTON );
  
  bank.pop();
    
  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 0ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::PHOTON );
  
  bank.pop();

  // Sample from the source again
  source->sampleParticleState( bank, 1 );

  TEST_EQUALITY_CONST( bank.size(), 1 );

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 1ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::NEUTRON );
  
  bank.pop();

  // Sample from the source again
  source->sampleParticleState( bank, 2 );

  TEST_EQUALITY_CONST( bank.size(), 1 );

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 2ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::ELECTRON );
  
  bank.pop();

  // Sample from the source again
  source->sampleParticleState( bank, 3 );

  TEST_EQUALITY_CONST( bank.size(), 1 );

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 3ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::NEUTRON );

  bank.pop();

  // Sample from the source again
  source->sampleParticleState( bank, 4 );

  TEST_EQUALITY_CONST( bank.size(), 1 );

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 4ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::PHOTON );

  bank.pop();

  // Sample from the source again
  source->sampleParticleState( bank, 5 );

  TEST_EQUALITY_CONST( bank.size(), 1 );

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 5ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::ELECTRON );

  bank.pop();

  // Sample from the source again
  source->sampleParticleState( bank, 6 );

  TEST_EQUALITY_CONST( bank.size(), 1 );

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 6ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::NEUTRON );

  bank.pop();

  // Sample from the source again
  source->sampleParticleState( bank, 7 );

  TEST_EQUALITY_CONST( bank.size(), 1 );

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 7ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::PHOTON );

  bank.pop();

  // Attempting to get another particle state should cause an exception
  TEST_THROW( source->sampleParticleState( bank, 10 ), std::runtime_error );
}

//---------------------------------------------------------------------------//
// Check that particle states can be "sampled"
TEUCHOS_UNIT_TEST( CachedStateParticleSource, sampleParticleState_thread_safe )
{
  std::shared_ptr<MonteCarlo::ParticleSource> source;

  initializeSource( source );

  unsigned threads = 
    Utility::GlobalOpenMPSession::getRequestedNumberOfThreads();

  source->enableThreadSupport( threads );
  
  std::vector<MonteCarlo::ParticleBank> banks( threads );

  #pragma omp parallel for num_threads( threads )
  for( unsigned i = 0; i < 8; ++i )
  {
    source->sampleParticleState( 
                       banks[Utility::GlobalOpenMPSession::getThreadId()], i );
  }
  
  // Merge the banks
  MonteCarlo::ParticleBank bank;

  for( unsigned i = 0; i < banks.size(); ++i )
    bank.merge( banks[i], compareHistoryNumbers );
  
  banks.clear();

  TEST_EQUALITY_CONST( bank.size(), 9 );
  
  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 0ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::PHOTON );
  
  bank.pop();
    
  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 0ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::PHOTON );
  
  bank.pop();

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 1ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::NEUTRON );
  
  bank.pop();

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 2ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::ELECTRON );
  
  bank.pop();

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 3ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::NEUTRON );

  bank.pop();

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 4ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::PHOTON );

  bank.pop();

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 5ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::ELECTRON );

  bank.pop();

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 6ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::NEUTRON );

  bank.pop();

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 7ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::PHOTON );

  bank.pop();
}

//---------------------------------------------------------------------------//
// Check that the number of trials can be returned
TEUCHOS_UNIT_TEST( CachedStateParticleSource, getNumberOfTrials )
{
  std::shared_ptr<MonteCarlo::ParticleSource> source;

  initializeSource( source );
  
  TEST_EQUALITY_CONST( source->getNumberOfTrials(), 0ull );

  unsigned threads = 
    Utility::GlobalOpenMPSession::getRequestedNumberOfThreads();

  source->enableThreadSupport( threads );

  std::vector<MonteCarlo::ParticleBank> banks( threads );

  #pragma omp parallel for num_threads( threads )
  for( unsigned i = 0; i < 8; ++i )
  {
    source->sampleParticleState( 
                       banks[Utility::GlobalOpenMPSession::getThreadId()], i );
  }

  TEST_EQUALITY_CONST( source->getNumberOfTrials(), 9ull );
}

//---------------------------------------------------------------------------//
// Check that the number of samples can be returned
TEUCHOS_UNIT_TEST( CachedStateParticleSource, getNumberOfSamples )
{
  std::shared_ptr<MonteCarlo::ParticleSource> source;

  initializeSource( source );
  
  TEST_EQUALITY_CONST( source->getNumberOfSamples(), 0ull );

  unsigned threads = 
    Utility::GlobalOpenMPSession::getRequestedNumberOfThreads();

  source->enableThreadSupport( threads );

  std::vector<MonteCarlo::ParticleBank> banks( threads );

  #pragma omp parallel for num_threads( threads )
  for( unsigned i = 0; i < 8; ++i )
  {
    source->sampleParticleState( 
                       banks[Utility::GlobalOpenMPSession::getThreadId()], i );
  }

  TEST_EQUALITY_CONST( source->getNumberOfSamples(), 9ull );
}

//---------------------------------------------------------------------------//
// Check that the sampling efficiency can be returned
TEUCHOS_UNIT_TEST( CachedStateParticleSource, getSamplingEfficiency )
{
  std::shared_ptr<MonteCarlo::ParticleSource> source;

  initializeSource( source );
  
  TEST_EQUALITY_CONST( source->getSamplingEfficiency(), 1.0 );

  unsigned threads = 
    Utility::GlobalOpenMPSession::getRequestedNumberOfThreads();

  source->enableThreadSupport( threads );

  std::vector<MonteCarlo::ParticleBank> banks( threads );

  #pragma omp parallel for num_threads( threads )
  for( unsigned i = 0; i < 8; ++i )
  {
    source->sampleParticleState( 
                       banks[Utility::GlobalOpenMPSession::getThreadId()], i );
  }

  TEST_EQUALITY_CONST( source->getSamplingEfficiency(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the source data can be exported
TEUCHOS_UNIT_TEST( CachedStateParticleSource, exportData )
{
  std::shared_ptr<MonteCarlo::ParticleSource> source;

  initializeSource( source );
  
  MonteCarlo::ParticleBank bank;
  
  // Conduct 10 samples
  for( unsigned i = 0; i < 8; ++i )
    source->sampleParticleState( bank, i );

  // Export the source data
  std::string source_data_file_name( "test_standard_particle_source.h5" );

  {
    std::shared_ptr<Utility::HDF5FileHandler> hdf5_file(
                                                new Utility::HDF5FileHandler );
    hdf5_file->openHDF5FileAndOverwrite( source_data_file_name );

    source->exportData( hdf5_file );
  }

  // Check that the source data was written correctly
  MonteCarlo::SourceHDF5FileHandler source_file_handler( 
               source_data_file_name,
               MonteCarlo::SourceHDF5FileHandler::READ_ONLY_SOURCE_HDF5_FILE );

  TEST_EQUALITY_CONST(
             source_file_handler.getNumberOfDefaultSourceSamplingTrials(), 9 );
  TEST_EQUALITY_CONST(
                    source_file_handler.getNumberOfDefaultSourceSamples(), 9 );
}

//---------------------------------------------------------------------------//
// Check that the source data can be reset
TEUCHOS_UNIT_TEST( CachedStateParticleSource, resetData )
{
  std::shared_ptr<MonteCarlo::ParticleSource> source;

  initializeSource( source );
  
  TEST_EQUALITY_CONST( source->getNumberOfSamples(), 0ull );

  unsigned threads = 
    Utility::GlobalOpenMPSession::getRequestedNumberOfThreads();

  source->enableThreadSupport( threads );

  std::vector<MonteCarlo::ParticleBank> banks( threads );

  #pragma omp parallel for num_threads( threads )
  for( unsigned i = 0; i < 8; ++i )
  {
    source->sampleParticleState( 
                       banks[Utility::GlobalOpenMPSession::getThreadId()], i );
  }

  TEST_EQUALITY_CONST( source->getNumberOfSamples(), 9ull );

  source->resetData();

  TEST_EQUALITY_CONST( source->getNumberOfSamples(), 0ull );
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
  
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
  
  // Run the unit tests
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  const bool success = Teuchos::UnitTestRepository::runUnitTests(*out);

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstCachedStateParticleSource.cpp
//---------------------------------------------------------------------------//
