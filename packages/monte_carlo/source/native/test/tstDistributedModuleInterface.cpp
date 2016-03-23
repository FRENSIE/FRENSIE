//---------------------------------------------------------------------------//
//!
//! \file   tstDistributedModuleInterface.cpp
//! \author Alex Robinson
//! \brief  Source module interface parallel unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_DefaultComm.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "MonteCarlo_SourceModuleInterface_Native.hpp"
#include "MonteCarlo_StandardParticleSource.hpp"
#include "MonteCarlo_ParticleModeType.hpp"
#include "Utility_PointSpatialDistribution.hpp"
#include "Utility_SphericalDirectionalDistribution.hpp"
#include "Utility_DeltaDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the source data can be reduced
TEUCHOS_UNIT_TEST( ModuleInterface, reduceSourceData )
{
  typedef MonteCarlo::SourceModuleInterface<MonteCarlo::ParticleSource> SMI;

  MonteCarlo::ParticleBank bank;

  for( unsigned i = 0; i < 10; ++i )
  {
    SMI::sampleParticleState( bank, Teuchos::GlobalMPISession::getRank()*10+i);
  }

  TEST_EQUALITY_CONST( SMI::getNumberOfTrials(), 10 );
  TEST_EQUALITY_CONST( SMI::getNumberOfSamples(), 10 );
  TEST_EQUALITY_CONST( SMI::getSamplingEfficiency(), 1.0 );

  Teuchos::RCP<const Teuchos::Comm<unsigned long long> > comm = 
    Teuchos::DefaultComm<unsigned long long>::getComm();

  comm->barrier();

  SMI::reduceSourceData( comm, 0 );

  // Check that the source data has been gathered on the root process
  if( comm->getRank() == 0 )
  {
    TEST_EQUALITY_CONST( SMI::getNumberOfTrials(), comm->getSize()*10 );
    TEST_EQUALITY_CONST( SMI::getNumberOfSamples(), comm->getSize()*10 );
    TEST_EQUALITY_CONST( SMI::getSamplingEfficiency(), 1.0 );
  }
  // Check that the source data on the non-root processes has been reset
  else
  {
    TEST_EQUALITY_CONST( SMI::getNumberOfTrials(), 0 );
    TEST_EQUALITY_CONST( SMI::getNumberOfSamples(), 0 );
    TEST_EQUALITY_CONST( SMI::getSamplingEfficiency(), 1.0 );
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

  // Run the unit tests
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  out->setProcRankAndSize( mpiSession.getRank(), mpiSession.getNProc() );

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

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();

  mpiSession.barrier();
  
  // Run the unit tests
  Teuchos::UnitTestRepository::setGloballyReduceTestResult( true );
  
  const bool success = Teuchos::UnitTestRepository::runUnitTests(*out);

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
// end tstDistributedModuleInterface.cpp
//---------------------------------------------------------------------------//
