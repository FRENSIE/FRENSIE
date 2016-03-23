//---------------------------------------------------------------------------//
//!
//! \file   tstDistributedStandardParticleSource.cpp
//! \author Alex Robinson
//! \brief  Standard particle source distributed parallel unit tests
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
#include <Teuchos_DefaultComm.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_StandardParticleSource.hpp"
#include "Utility_SphericalSpatialDistribution.hpp"
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
// Tests
//---------------------------------------------------------------------------//
// Check that the source data can be reduced
TEUCHOS_UNIT_TEST( StandardParticleSource, reduceData )
{
  MonteCarlo::ParticleBank bank;

  for( unsigned i = 0; i < 10; ++i )
  {
    source->sampleParticleState( bank, 
                                 Teuchos::GlobalMPISession::getRank()*10+i );
  }

  TEST_EQUALITY_CONST( source->getNumberOfTrials(), 10 );
  TEST_EQUALITY_CONST( source->getNumberOfSamples(), 10 );
  TEST_EQUALITY_CONST( source->getSamplingEfficiency(), 1.0 );

  Teuchos::RCP<const Teuchos::Comm<unsigned long long> > comm = 
    Teuchos::DefaultComm<unsigned long long>::getComm();
  
  comm->barrier();

  source->reduceData( comm, 0 );

  // Check that the source data has been gathered on the root process
  if( comm->getRank() == 0 )
  {
    TEST_EQUALITY_CONST( source->getNumberOfTrials(), comm->getSize()*10 );
    TEST_EQUALITY_CONST( source->getNumberOfSamples(), comm->getSize()*10 );
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

  // Initialize the source
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
      energy_distribution( new Utility::UniformDistribution( 1e-3, 1.0, 1.0 ));

    // Delta distribution in time dimension
    std::shared_ptr<Utility::OneDDistribution>
      time_distribution( new Utility::DeltaDistribution( 0.0 ) );

    // Create the distributed source
    source.reset( new MonteCarlo::StandardParticleSource( 
                                                      0u,
                                                      spatial_distribution,
                                                      directional_distribution,
                                                      energy_distribution,
                                                      time_distribution,
                                                      MonteCarlo::PHOTON ) );
  }

  mpiSession.barrier();

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
// end tstStandardParticleSource.cpp
//---------------------------------------------------------------------------//

