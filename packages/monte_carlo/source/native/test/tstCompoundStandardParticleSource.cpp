//---------------------------------------------------------------------------//
//!
//! \file   tstCompoundStandardParticleSource.cpp
//! \author Alex Robinson
//! \brief  Compound distributed particle source unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Boost Includes
#include <boost/bind.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_UnitTestRepository.hpp>
#include <Teuchos_GlobalMPISession.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_Ptr.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_StandardParticleSource.hpp"
#include "MonteCarlo_CompoundStandardParticleSource.hpp"
#include "MonteCarlo_SourceHDF5FileHandler.hpp"
#include "Utility_GlobalOpenMPSession.hpp"
#include "Utility_SphericalSpatialDistribution.hpp"
#include "Utility_CartesianSpatialDistribution.hpp"
#include "Utility_SphericalDirectionalDistribution.hpp"
#include "Utility_PowerDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_DeltaDistribution.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_RandomNumberGenerator.hpp"

//---------------------------------------------------------------------------//
// Testing variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::ParticleSource> source;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that particle states can be sampled
TEUCHOS_UNIT_TEST( CompoundStandardParticleSource, sampleParticleState )
{
  MonteCarlo::ParticleBank bank;
  
  source->sampleParticleState( bank, 0 );

  TEST_ASSERT( bank.top().getParticleType() == MonteCarlo::PHOTON ||
	       bank.top().getParticleType() == MonteCarlo::NEUTRON );
  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 0 );
  TEST_COMPARE( bank.top().getXPosition(), >=, -2.0 );
  TEST_COMPARE( bank.top().getXPosition(), <=, 2.0 );
  TEST_COMPARE( bank.top().getYPosition(), >=, -2.0 );
  TEST_COMPARE( bank.top().getYPosition(), <=, 2.0 );
  TEST_COMPARE( bank.top().getZPosition(), >=, -2.0 );
  TEST_COMPARE( bank.top().getZPosition(), <=, 2.0 );
  TEST_COMPARE( bank.top().getXDirection(), >=, -1.0 );
  TEST_COMPARE( bank.top().getXDirection(), <=, 1.0 );
  TEST_COMPARE( bank.top().getYDirection(), >=, -1.0 );
  TEST_COMPARE( bank.top().getYDirection(), <=, 1.0 );
  TEST_COMPARE( bank.top().getZDirection(), >=, -1.0 );
  TEST_COMPARE( bank.top().getZDirection(), <=, 1.0 );
  TEST_COMPARE( bank.top().getEnergy(), >=, 1e-3 );
  TEST_ASSERT( bank.top().getEnergy() <= 1.0 ||
	       bank.top().getEnergy() == 14.1 );
  TEST_EQUALITY_CONST( bank.top().getTime(), 0.0 );
  TEST_EQUALITY_CONST( bank.top().getWeight(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that particle states can be sampled
TEUCHOS_UNIT_TEST( CompoundStandardParticleSource, 
                   sampleParticleState_thread_safe )
{
  source->resetData();

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
// Check that the source data can be exported
TEUCHOS_UNIT_TEST( CompoundStandardParticleSource, exportData )
{
  source->resetData();

  MonteCarlo::ParticleBank bank;
  
  // Conduct 10 samples
  for( unsigned i = 0; i < 10; ++i )
    source->sampleParticleState( bank, i );

  // Export the source data
  std::string source_data_file_name( 
                                 "test_compound_standard_particle_source.h5" );

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
  TEST_ASSERT( source_file_handler.doesSourceExist( 1 ) );

  unsigned long long total_trials = 
    source_file_handler.getNumberOfSourceSamplingTrials( 0 ) +
    source_file_handler.getNumberOfSourceSamplingTrials( 1 );
  
  TEST_EQUALITY( source_file_handler.getNumberOfDefaultSourceSamplingTrials(),
                 total_trials );
  
  unsigned long long total_samples = 
    source_file_handler.getNumberOfSourceSamples( 0 ) +
    source_file_handler.getNumberOfSourceSamples( 1 );
  
  TEST_EQUALITY( source_file_handler.getNumberOfDefaultSourceSamples(),
                 total_samples );
}

//---------------------------------------------------------------------------//
// Check that the number of trials can be returned
TEUCHOS_UNIT_TEST( CompoundStandardParticleSource, getNumberOfTrials )
{
  source->resetData();

  unsigned threads = 
    Utility::GlobalOpenMPSession::getRequestedNumberOfThreads();
  
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
TEUCHOS_UNIT_TEST( CompoundStandardParticleSource, getNumberOfSamples )
{
  source->resetData();

  unsigned threads = 
    Utility::GlobalOpenMPSession::getRequestedNumberOfThreads();
  
  // Create a sample for each thread
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
TEUCHOS_UNIT_TEST( CompoundStandardParticleSource, getSamplingEfficiency )
{
  source->resetData();
  
  MonteCarlo::ParticleBank bank;
  
  // Conduct 10 samples
  for( unsigned i = 0; i < 10; ++i )
    source->sampleParticleState( bank, i );

  // Theoretical efficiency: eff_a*eff_b/(p_a*eff_b+p_b*eff_a)
  // eff_a = (4/sqrt(3))^3/(4*pi*2^3/3) ~= 0.367552
  TEST_COMPARE( source->getSamplingEfficiency(), >, 0.0 );
  TEST_COMPARE( source->getSamplingEfficiency(), <=, 1.0 );

  source->printSummary( std::cout );
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

  // Initialize the source
  {
    // Create the distributions required for each source
    std::shared_ptr<Utility::OneDDistribution>
      r_distribution( new Utility::PowerDistribution<2u>( 3.0, 0.0, 2.0 ) );
    std::shared_ptr<Utility::OneDDistribution>
      theta_distribution( new Utility::UniformDistribution( 
					      0.0,
					      2*Utility::PhysicalConstants::pi,
					      1.0 ) );
    std::shared_ptr<Utility::OneDDistribution>
      mu_distribution( new Utility::UniformDistribution( -1.0, 1.0, 1.0 ) );

    std::shared_ptr<Utility::SpatialDistribution>
      source_1_spatial_distribution( new Utility::SphericalSpatialDistribution(
							    r_distribution,
							    theta_distribution,
							    mu_distribution,
							    0.0,
							    0.0,
							    0.0 ) );
    std::shared_ptr<Utility::DirectionalDistribution>
      directional_distribution( new Utility::SphericalDirectionalDistribution( 
							   theta_distribution,
							   mu_distribution ) );

    std::shared_ptr<Utility::OneDDistribution>
      source_1_energy_distribution( new Utility::UniformDistribution( 1e-3, 
                                                                      1.0, 
                                                                      1.0 ) );
    std::shared_ptr<Utility::OneDDistribution>
      time_distribution( new Utility::DeltaDistribution( 0.0 ) );

    std::shared_ptr<Utility::OneDDistribution>
      x_distribution( new Utility::DeltaDistribution( 0.0 ) );
    std::shared_ptr<Utility::OneDDistribution>
      y_distribution( new Utility::DeltaDistribution( 0.0 ) );
    std::shared_ptr<Utility::OneDDistribution>
      z_distribution( new Utility::DeltaDistribution( 0.0 ) );
    
    std::shared_ptr<Utility::SpatialDistribution>
      source_2_spatial_distribution( new Utility::CartesianSpatialDistribution(
							    x_distribution,
							    y_distribution,
							    z_distribution ) );
    std::shared_ptr<Utility::OneDDistribution>
      source_2_energy_distribution( new Utility::DeltaDistribution( 14.1 ) );
  
    // Create the uniform spherical source
    std::shared_ptr<MonteCarlo::StandardParticleSource> spherical_source( 
                                     new MonteCarlo::StandardParticleSource(
                                                 0u,
	                                         source_1_spatial_distribution,
                                                 directional_distribution,
                                                 source_1_energy_distribution,
                                                 time_distribution,
                                                 MonteCarlo::PHOTON ) );
  
    // Create the point source
    std::shared_ptr<MonteCarlo::StandardParticleSource> point_source( 
                                     new MonteCarlo::StandardParticleSource(
	                                         1u,
                                                 source_2_spatial_distribution,
                                                 directional_distribution,
                                                 source_2_energy_distribution,
                                                 time_distribution,
                                                 MonteCarlo::NEUTRON ) );
    

    Teuchos::Array<std::shared_ptr<MonteCarlo::StandardParticleSource> > 
      sources( 2 );
    sources[0] = spherical_source;
    sources[1] = point_source;
    
    Teuchos::Array<double> source_weights( 2 );
    source_weights[0] = 0.5;
    source_weights[1] = 0.5;
    
    // Create the compound source
    source.reset( new MonteCarlo::CompoundStandardParticleSource( 
                                                   sources, source_weights ) );
  }

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
// end tstCompoundStandardParticleSource.cpp
//---------------------------------------------------------------------------//

