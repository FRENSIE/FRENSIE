//---------------------------------------------------------------------------//
//! 
//! \file   tstParticleSubtrackEndingGlobalEventDispatcher.cpp
//! \author Alex Robinson, Eli Moll
//! \brief  Particle subtrack ending in cell event dispatcher unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "MonteCarlo_TetMeshTrackLengthFluxEstimator.hpp"
#include "MonteCarlo_ParticleSubtrackEndingGlobalEventDispatcher.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Geometry_ModuleTraits.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<MonteCarlo::TetMeshTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier> >
estimator;

std::shared_ptr<MonteCarlo::ParticleSubtrackEndingGlobalEventDispatcher>
dispatcher( new MonteCarlo::ParticleSubtrackEndingGlobalEventDispatcher );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that an observer can be attached to the dispatcher
TEUCHOS_UNIT_TEST( ParticleSubtrackEndingGlobalEventDispatcher, 
		   attachObserver )
{  
  std::shared_ptr<MonteCarlo::ParticleSubtrackEndingGlobalEventObserver> observer =
    std::dynamic_pointer_cast<MonteCarlo::ParticleSubtrackEndingGlobalEventObserver>( estimator );
    
  dispatcher->attachObserver( estimator->getId(), observer );
                                                             
  observer.reset();
  
  TEST_EQUALITY_CONST( estimator.use_count(), 2 );
  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 1 );
}

//---------------------------------------------------------------------------//
// Check that the dispatcher can update from the global ending event
TEUCHOS_UNIT_TEST( ParticleSubtrackEndingGlobalEventDispatcher, 
                   dispatchParticleSubtrackEndingGlobalEvent )
{
  MonteCarlo::PhotonState particle( 0ull );
  particle.setWeight( 1.0 );
  particle.setEnergy( 1.0 );
  
  double start_point[3] = { 0.0, 1.0, 0.0 };
  double end_point[3] = { 0.25, 0.75, 1.0 };

  TEST_ASSERT( !estimator->hasUncommittedHistoryContribution() );

  dispatcher->dispatchParticleSubtrackEndingGlobalEvent( 
                                            particle, start_point, end_point );

  TEST_ASSERT( estimator->hasUncommittedHistoryContribution() );

  estimator->commitHistoryContribution();

  TEST_ASSERT( !estimator->hasUncommittedHistoryContribution() );
}

//---------------------------------------------------------------------------//
// Check that an observer can be detached from the dispatcher
TEUCHOS_UNIT_TEST( ParticleSubtrackEndingGlobalEventDispatcher, 
		   detachObserver )
{
  dispatcher->detachObserver( estimator->getId() ); 
                                   
  TEST_EQUALITY_CONST( estimator.use_count(), 1 );
  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 0 );
}

//---------------------------------------------------------------------------//
// Check that all observers can be detached from the dispatcher
TEUCHOS_UNIT_TEST( ParticleSubtrackEndingGlobalEventDispatcher, 
		   detachAllObservers )
{
  std::shared_ptr<MonteCarlo::ParticleSubtrackEndingGlobalEventObserver> observer =
    std::dynamic_pointer_cast<MonteCarlo::ParticleSubtrackEndingGlobalEventObserver>( estimator );

  dispatcher->attachObserver(  estimator->getId(), observer );

  observer.reset();
                               
  TEST_EQUALITY_CONST( estimator.use_count(), 2 );
  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 1 );
                                                             
  dispatcher->detachAllObservers(); 
  
  TEST_EQUALITY_CONST( estimator.use_count(), 1 );
  TEST_EQUALITY_CONST( dispatcher->getNumberOfObservers(), 0 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_input_mesh_file_name;
  
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_input_mesh_file_name",
		 &test_input_mesh_file_name,
		 "Test input mesh file name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();
  
  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }
  
  // Initialize the estimator
  {
    estimator.reset(
                    new MonteCarlo::TetMeshTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier>(
                         0u,
                         1.0,
                         test_input_mesh_file_name,
                         "unit_cube_output.vtk" ) );
    
    // Assign energy bins
    Teuchos::Array<double> energy_bin_boundaries( 2 );
    energy_bin_boundaries[0] = 0.0;
    energy_bin_boundaries[1] = 1.0;
    
    estimator->setBinBoundaries<MonteCarlo::ENERGY_DIMENSION>(
                                                       energy_bin_boundaries );
                             
    // Set the particle types
    Teuchos::Array<MonteCarlo::ParticleType> particle_types ( 1 );
    particle_types[0] = MonteCarlo::PHOTON;
    
    estimator->setParticleTypes( particle_types );
  }
  
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
// end tstParticleSubtrackEndingGlobalEventDispatcher.cpp
//---------------------------------------------------------------------------//
