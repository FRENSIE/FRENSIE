//---------------------------------------------------------------------------//
//!
//! \file   tstModuleInterface.cpp
//! \author Alex Robinson
//! \brief  Source module interface unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "MonteCarlo_SourceModuleInterface_Native.hpp"
#include "MonteCarlo_StandardParticleSource.hpp"
#include "MonteCarlo_SourceHDF5FileHandler.hpp"
#include "MonteCarlo_ParticleModeType.hpp"
#include "Utility_PointSpatialDistribution.hpp"
#include "Utility_SphericalDirectionalDistribution.hpp"
#include "Utility_DeltaDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_GlobalOpenMPSession.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a particle state can be sampled
TEUCHOS_UNIT_TEST( ModuleInterface, sampleParticleState )
{
  typedef MonteCarlo::SourceModuleInterface<MonteCarlo::ParticleSource> SMI;

  MonteCarlo::ParticleBank bank;

  SMI::sampleParticleState( bank, 0 );

  TEST_ASSERT( bank.size() > 0 );
  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 0 );
}

//---------------------------------------------------------------------------//
// Check that a particle state can be sampled
TEUCHOS_UNIT_TEST( ModuleInterface, sampleParticleState_thread_safe )
{
  typedef MonteCarlo::SourceModuleInterface<MonteCarlo::ParticleSource> SMI;

  unsigned threads = 
    Utility::GlobalOpenMPSession::getRequestedNumberOfThreads();

  std::vector<MonteCarlo::ParticleBank> banks( threads );
  
  SMI::enableThreadSupport( threads );

  // Create a sample for each thread
  #pragma omp parallel num_threads( threads )
  {
    SMI::sampleParticleState( 
                            banks[Utility::GlobalOpenMPSession::getThreadId()],
                            Utility::GlobalOpenMPSession::getThreadId() );
  }

  // Splice all of the banks
  MonteCarlo::ParticleBank combined_bank;
  
  for( unsigned i = 0; i < banks.size(); ++i )
    combined_bank.splice( banks[i] );

  TEST_EQUALITY_CONST( combined_bank.size(), threads );
}

//---------------------------------------------------------------------------//
// Check that the number of trials can be returned
TEUCHOS_UNIT_TEST( ModuleInterface, getNumberOfTrials )
{
  typedef MonteCarlo::SourceModuleInterface<MonteCarlo::ParticleSource> SMI;

  SMI::resetSourceData();

  MonteCarlo::ParticleBank bank;

  // Conduct a sample for each thread
  for( unsigned i = 0; i < 10; ++i )
    SMI::sampleParticleState( bank, i );

  TEST_EQUALITY_CONST( SMI::getNumberOfTrials(), 10 );
}

//---------------------------------------------------------------------------//
// Check that the number of samples can be returned
TEUCHOS_UNIT_TEST( ModuleInterface, getNumberOfSamples )
{
  typedef MonteCarlo::SourceModuleInterface<MonteCarlo::ParticleSource> SMI;

  SMI::resetSourceData();

  MonteCarlo::ParticleBank bank;

  // Conduct a sample for each thread
  for( unsigned i = 0; i < 10; ++i )
    SMI::sampleParticleState( bank, i );

  TEST_EQUALITY_CONST( SMI::getNumberOfSamples(), 10 );
}

//---------------------------------------------------------------------------//
// Check that the sampling efficiency can be returned
TEUCHOS_UNIT_TEST( ModuleInterface, getSamplingEfficiency )
{
  typedef MonteCarlo::SourceModuleInterface<MonteCarlo::ParticleSource> SMI;

  SMI::resetSourceData();

  MonteCarlo::ParticleBank bank;

  // Conduct a sample for each thread
  for( unsigned i = 0; i < 10; ++i )
    SMI::sampleParticleState( bank, i );

  TEST_EQUALITY_CONST( SMI::getSamplingEfficiency(), 1.0 );

  std::cout << std::endl;
  SMI::printSourceSummary( std::cout );
}

//---------------------------------------------------------------------------//
// Check that the source data can be exported
TEUCHOS_UNIT_TEST( ModuleInterface, exportSourceData )
{
  typedef MonteCarlo::SourceModuleInterface<MonteCarlo::ParticleSource> SMI;

  SMI::resetSourceData();

  MonteCarlo::ParticleBank bank;

  // Conduct a sample for each thread
  for( unsigned i = 0; i < 10; ++i )
    SMI::sampleParticleState( bank, i );

  // Export the source data
  std::string source_data_file_name( "test_standard_particle_source.h5" );

  {
    std::shared_ptr<Utility::HDF5FileHandler> hdf5_file(
                                                new Utility::HDF5FileHandler );
    hdf5_file->openHDF5FileAndOverwrite( source_data_file_name );

    SMI::exportSourceData( hdf5_file );
  }

  // Check that the source data was written correctly
  MonteCarlo::SourceHDF5FileHandler source_file_handler( 
               source_data_file_name,
               MonteCarlo::SourceHDF5FileHandler::READ_ONLY_SOURCE_HDF5_FILE );

  TEST_ASSERT( source_file_handler.doesSourceExist( 0 ) );
  TEST_EQUALITY_CONST(
                source_file_handler.getNumberOfSourceSamplingTrials( 0 ), 10 );
  TEST_EQUALITY_CONST(
            source_file_handler.getNumberOfDefaultSourceSamplingTrials(), 10 );
  TEST_EQUALITY_CONST( source_file_handler.getNumberOfSourceSamples( 0 ), 10 );
  TEST_EQUALITY_CONST(
                   source_file_handler.getNumberOfDefaultSourceSamples(), 10 );
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

  // Initialize the source handler
  {
    // Create the spatial distribution
    std::shared_ptr<Utility::SpatialDistribution>
      spatial_distribution( 
                      new Utility::PointSpatialDistribution( 0.0, 0.0, 0.0 ) );

    // Create the directional distribution
    std::shared_ptr<Utility::OneDDistribution>
      theta_distribution( new Utility::DeltaDistribution( 0.0 ) );

    std::shared_ptr<Utility::OneDDistribution>
      mu_distribution( new Utility::DeltaDistribution( 1.0 ) );

    std::shared_ptr<Utility::DirectionalDistribution>
      directional_distribution( new Utility::SphericalDirectionalDistribution(
                                                           theta_distribution,
							   mu_distribution ) );
    
    // Create the energy distribution
    std::shared_ptr<Utility::OneDDistribution>
      energy_distribution( new Utility::DeltaDistribution( 1.0 ) );

    // Create the time distribution
    std::shared_ptr<Utility::OneDDistribution>
      time_distribution( new Utility::DeltaDistribution( 0.0 ) );

    // Create the source
    std::shared_ptr<MonteCarlo::ParticleSource> source(
                                     new MonteCarlo::StandardParticleSource(
                                                      0u,
                                                      spatial_distribution,
                                                      directional_distribution,
                                                      energy_distribution,
                                                      time_distribution,
                                                      MonteCarlo::PHOTON ) );
    
    MonteCarlo::setSourceHandlerInstance( source );
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
// end tstModuleInterface.cpp
//---------------------------------------------------------------------------//
