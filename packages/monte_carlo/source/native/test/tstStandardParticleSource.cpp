//---------------------------------------------------------------------------//
//!
//! \file   tstStandardParticleSource.cpp
//! \author Alex Robinson
//! \brief  Standard particle source unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_UnitTestRepository.hpp>
#include <Teuchos_GlobalMPISession.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_Ptr.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_StandardParticleSource.hpp"
#include "MonteCarlo_SourceHDF5FileHandler.hpp"
#include "Utility_SphericalSpatialDistribution.hpp"
#include "Utility_SphericalDirectionalDistribution.hpp"
#include "Utility_PowerDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_DeltaDistribution.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_GlobalOpenMPSession.hpp"

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Initialize the source (uniform spherical source)
template<typename ParticleSourceType>
void initializeSource( std::shared_ptr<ParticleSourceType>& source,
                       const bool set_importance_functions = false )
{
  // Power distribution in r dimension
  std::shared_ptr<Utility::OneDDistribution> 
    r_distribution( new Utility::PowerDistribution<2u>( 3.0, 0.0, 2.0 ) );
  
  // Uniform distribution in theta dimension
  std::shared_ptr<Utility::OneDDistribution>
    theta_distribution( new Utility::UniformDistribution( 
					      0.0,
					      2*Utility::PhysicalConstants::pi,
					      1.0 ) );
  // Uniform distribution in mu dimension
  std::shared_ptr<Utility::OneDDistribution>
    mu_distribution( new Utility::UniformDistribution( -1.0, 1.0, 1.0 ) );

  // Create the spatial distribution
  std::shared_ptr<Utility::SpatialDistribution>
    spatial_distribution( new Utility::SphericalSpatialDistribution( 
							    r_distribution,
							    theta_distribution,
							    mu_distribution,
							    0.0,
							    0.0,
							    0.0 ) );

  // Create the directional distribution
  std::shared_ptr<Utility::DirectionalDistribution>
    directional_distribution( new Utility::SphericalDirectionalDistribution( 
							   theta_distribution,
							   mu_distribution ) );

  // Uniform distribution in energy dimension
  std::shared_ptr<Utility::OneDDistribution>
    energy_distribution( new Utility::UniformDistribution( 1e-3, 1.0, 1.0 ) );

  // Delta distribution in time dimension
  std::shared_ptr<Utility::OneDDistribution>
    time_distribution( new Utility::DeltaDistribution( 0.0 ) );

  // Create the source
  source.reset( new MonteCarlo::StandardParticleSource( 
                                                      0u,
                                                      spatial_distribution,
                                                      directional_distribution,
                                                      energy_distribution,
                                                      time_distribution,
                                                      MonteCarlo::PHOTON ) );

  // Set the importance functions if requested
  if( set_importance_functions )
  {
    // Uniform distribution in theta dimension
    Teuchos::Array<double> bin_boundaries( 4 );
    bin_boundaries[0] = 0.0;
    bin_boundaries[1] = Utility::PhysicalConstants::pi/2;
    bin_boundaries[2] = 3*Utility::PhysicalConstants::pi/2;
    bin_boundaries[3] = 2*Utility::PhysicalConstants::pi;

    Teuchos::Array<double> bin_values( 3 );
    bin_values[0] = 1.0;
    bin_values[1] = 2.0;
    bin_values[2] = 1.0;
    
    std::shared_ptr<Utility::OneDDistribution>
      theta_importance_distribution( new Utility::HistogramDistribution(
								bin_boundaries,
								bin_values ) );

    // Create the spatial importance distribution 
    std::shared_ptr<Utility::SpatialDistribution> spatial_importance_distribution(
       new Utility::SphericalSpatialDistribution( r_distribution,
						 theta_importance_distribution,
						 mu_distribution,
						 0.0,
						 0.0,
						 0.0 ) );

    // Create the directional importance distribution
    std::shared_ptr<Utility::DirectionalDistribution>
      directional_importance_distribution( 
	   new Utility::SphericalDirectionalDistribution( 
						 theta_importance_distribution,
						 mu_distribution ) );

    // Create the energy importance distribution
    bin_boundaries[0] = 1e-3;
    bin_boundaries[1] = 1e-2;
    bin_boundaries[2] = 1e-1;
    bin_boundaries[3] = 1.0;
    
    bin_values[0] = 5.0;
    bin_values[1] = 2.0;
    bin_values[2] = 1.0;
    std::shared_ptr<Utility::OneDDistribution>
      energy_importance_distribution( new Utility::HistogramDistribution(
								bin_boundaries,
								bin_values ) );
    
    std::shared_ptr<MonteCarlo::StandardParticleSource> 
      distributed_source = std::dynamic_pointer_cast<MonteCarlo::StandardParticleSource>( source );
									     
    distributed_source->setSpatialImportanceDistribution( 
					     spatial_importance_distribution );
    distributed_source->setDirectionalImportanceDistribution( 
					 directional_importance_distribution );
    distributed_source->setEnergyImportanceDistribution( 
					      energy_importance_distribution );
  }
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the source id can be returned
TEUCHOS_UNIT_TEST( StandardParticleSource, getId )
{
  std::shared_ptr<MonteCarlo::StandardParticleSource> source;
  
  initializeSource( source, false );

  TEST_EQUALITY_CONST( source->getId(), 0u );

  initializeSource( source, true );

  TEST_EQUALITY_CONST( source->getId(), 0u );
}

//---------------------------------------------------------------------------//
// Check that particle states can be sampled (no importance functions, no
// rejection cell )
TEUCHOS_UNIT_TEST( StandardParticleSource,
                   sampleParticleState_no_importance_no_reject )
{
  std::shared_ptr<MonteCarlo::ParticleSource> source;
  
  initializeSource( source );
  
  MonteCarlo::ParticleBank bank;
  
  source->sampleParticleState( bank, 0 );
  
  MonteCarlo::ParticleState& particle = bank.top();
  
  TEST_EQUALITY_CONST( particle.getParticleType(), MonteCarlo::PHOTON );
  TEST_EQUALITY_CONST( particle.getHistoryNumber(), 0 );
  TEST_COMPARE( particle.getXPosition(), >=, -2.0 );
  TEST_COMPARE( particle.getXPosition(), <=, 2.0 );
  TEST_COMPARE( particle.getYPosition(), >=, -2.0 );
  TEST_COMPARE( particle.getYPosition(), <=, 2.0 );
  TEST_COMPARE( particle.getZPosition(), >=, -2.0 );
  TEST_COMPARE( particle.getZPosition(), <=, 2.0 );
  TEST_COMPARE( particle.getXDirection(), >=, -1.0 );
  TEST_COMPARE( particle.getXDirection(), <=, 1.0 );
  TEST_COMPARE( particle.getYDirection(), >=, -1.0 );
  TEST_COMPARE( particle.getYDirection(), <=, 1.0 );
  TEST_COMPARE( particle.getZDirection(), >=, -1.0 );
  TEST_COMPARE( particle.getZDirection(), <=, 1.0 );
  TEST_COMPARE( particle.getEnergy(), >=, 1e-3 );
  TEST_COMPARE( particle.getEnergy(), <=, 1.0 );
  TEST_EQUALITY_CONST( particle.getTime(), 0.0 );
  TEST_EQUALITY_CONST( particle.getWeight(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that particle states can be sampled (no importance functions, no
// rejection cell )
TEUCHOS_UNIT_TEST( StandardParticleSource,
                   sampleParticleState_no_importance_no_reject_thread_safe )
{
  std::shared_ptr<MonteCarlo::ParticleSource> source;
  
  initializeSource( source );

  unsigned threads = 
    Utility::GlobalOpenMPSession::getRequestedNumberOfThreads();
  
  std::vector<MonteCarlo::ParticleBank> banks( threads );

  source->enableThreadSupport( 
                 Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  // Create a sample for each thread
  #pragma omp parallel num_threads( threads )
  {
    source->sampleParticleState( 
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
// Check that particle states can be sampled (importance functions, no 
// rejection cells )
TEUCHOS_UNIT_TEST( StandardParticleSource,
                   sampleParticleState_importance_no_reject )
{
  std::shared_ptr<MonteCarlo::ParticleSource> source;
  
  initializeSource( source, true );
  
  std::vector<double> fake_stream( 10 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.0;
  fake_stream[4] = 0.0;
  fake_stream[5] = 0.0;
  fake_stream[6] = 0.0;
  fake_stream[7] = 0.0;
  fake_stream[8] = 0.0;
  fake_stream[9] = 0.0;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  
  source->sampleParticleState( bank, 0 );

  MonteCarlo::ParticleState& particle = bank.top();
  
  TEST_EQUALITY_CONST( particle.getHistoryNumber(), 0 );
  TEST_EQUALITY_CONST( particle.getParticleType(), MonteCarlo::PHOTON );
  TEST_EQUALITY_CONST( particle.getXDirection(), 0.0 );
  TEST_EQUALITY_CONST( particle.getYDirection(), 0.0 );
  TEST_EQUALITY_CONST( particle.getZDirection(), -1.0 );
  TEST_EQUALITY_CONST( particle.getXPosition(), 0.0 );
  TEST_EQUALITY_CONST( particle.getYPosition(), 0.0 );
  TEST_EQUALITY_CONST( particle.getZPosition(), 0.0 );
  TEST_EQUALITY_CONST( particle.getEnergy(), 1e-3 );
  TEST_EQUALITY_CONST( particle.getTime(), 0.0 );
  TEST_FLOATING_EQUALITY( particle.getWeight(), 0.3378378378375, 1e-9 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that particle states can be sampled (importance functions, no 
// rejection cells )
TEUCHOS_UNIT_TEST( StandardParticleSource,
                   sampleParticleState_importance_no_reject_thread_safe )
{
  std::shared_ptr<MonteCarlo::ParticleSource> source;
  
  initializeSource( source, true );

  unsigned threads = 
    Utility::GlobalOpenMPSession::getRequestedNumberOfThreads();
  
  std::vector<MonteCarlo::ParticleBank> banks( threads );

  source->enableThreadSupport( 
                 Utility::GlobalOpenMPSession::getRequestedNumberOfThreads() );

  // Create a sample for each thread
  #pragma omp parallel num_threads( threads )
  {
    source->sampleParticleState( 
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
TEUCHOS_UNIT_TEST( StandardParticleSource, getNumberOfTrials )
{
  std::shared_ptr<MonteCarlo::ParticleSource> source;
  
  initializeSource( source, true );

  unsigned threads = 
    Utility::GlobalOpenMPSession::getRequestedNumberOfThreads();

  source->enableThreadSupport( threads );
  
  // Create a sample for each thread
  #pragma omp parallel num_threads( threads )
  {
    MonteCarlo::ParticleBank bank;
    
    source->sampleParticleState( bank, 
                                 Utility::GlobalOpenMPSession::getThreadId() );
  }

  TEST_COMPARE( source->getNumberOfTrials(), >=, threads );
}

//---------------------------------------------------------------------------//
// Check that the number of samples can be returned
TEUCHOS_UNIT_TEST( StandardParticleSource, getNumberOfSamples )
{
  std::shared_ptr<MonteCarlo::ParticleSource> source;
  
  initializeSource( source, true );

  unsigned threads = 
    Utility::GlobalOpenMPSession::getRequestedNumberOfThreads();

  source->enableThreadSupport( threads );
  
  // Conduct a sample for each thread
  #pragma omp parallel num_threads( threads )
  {
    MonteCarlo::ParticleBank bank;
    
    source->sampleParticleState( bank, 
                                 Utility::GlobalOpenMPSession::getThreadId() );
  }

  TEST_EQUALITY_CONST( source->getNumberOfSamples(), threads );
}

//---------------------------------------------------------------------------//
// Check that the sampling efficiency can be returned
TEUCHOS_UNIT_TEST( StandardParticleSource, getSamplingEfficiency )
{
  std::shared_ptr<MonteCarlo::ParticleSource> source;
  
  initializeSource( source, false );
  
  MonteCarlo::ParticleBank bank;
  
  // Conduct 10 samples
  for( unsigned i = 0; i < 10; ++i )
    source->sampleParticleState( bank, i );

  TEST_EQUALITY_CONST( source->getSamplingEfficiency(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the source data can be exported
TEUCHOS_UNIT_TEST( StandardParticleSource, exportData )
{
  std::shared_ptr<MonteCarlo::ParticleSource> source;
  
  initializeSource( source, true );

  MonteCarlo::ParticleBank bank;
  
  // Conduct 10 samples
  for( unsigned i = 0; i < 10; ++i )
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
  
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  // Set up the global OpenMP session
  if( Utility::GlobalOpenMPSession::isOpenMPUsed() )
    Utility::GlobalOpenMPSession::setNumberOfThreads( threads );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
  
  const bool success = Teuchos::UnitTestRepository::runUnitTests(*out);

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstStandardParticleSource.cpp
//---------------------------------------------------------------------------//
