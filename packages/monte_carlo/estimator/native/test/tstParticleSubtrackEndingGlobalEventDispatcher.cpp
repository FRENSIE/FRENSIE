//---------------------------------------------------------------------------//
//! 
//! \file   tstParticleSubtrackEndingGlobalEventDispatcher.cpp
//! \author Alex Robinson, Eli Moll
//! \brief  Particle subtrack ending in cell event dispatcher unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

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
Teuchos::RCP<MonteCarlo::TetMeshTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier> >
estimator;

std::string test_input_mesh_file_name;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Initialize the estimator
void initializeTetMeshEstimator()
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

//---------------------------------------------------------------------------//
// Tests.
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

  MonteCarlo::ParticleSubtrackEndingGlobalEventDispatcher::dispatchParticleSubtrackEndingGlobalEvent(
                                                            particle,
                                                            start_point,
                                                            end_point );

  TEST_ASSERT( !estimator->hasUncommittedHistoryContribution() );
}

// Check that the cell number of observers can be found
TEUCHOS_UNIT_TEST( ParticleSubtrackEndingGlobalEventDispatcher, 
                   getNumberOfObservers )
{
  TEST_EQUALITY_CONST( MonteCarlo::ParticleSubtrackEndingGlobalEventDispatcher::getNumberOfObservers(), 0 );
}

//---------------------------------------------------------------------------//
// Check that an observer can be attached to the dispatcher
TEUCHOS_UNIT_TEST( ParticleSubtrackEndingGlobalEventDispatcher, 
		   attachObserver )
{  
  Teuchos::RCP<MonteCarlo::ParticleSubtrackEndingGlobalEventObserver> observer =
    Teuchos::rcp_dynamic_cast<MonteCarlo::ParticleSubtrackEndingGlobalEventObserver>( estimator );
    
  MonteCarlo::ParticleSubtrackEndingGlobalEventDispatcher::attachObserver( 
                                                      estimator->getId(),
                                                      observer );
                                                             
  observer.reset();
  
  TEST_EQUALITY_CONST( estimator.total_count(), 2 );
  TEST_EQUALITY_CONST( MonteCarlo::ParticleSubtrackEndingGlobalEventDispatcher::getNumberOfObservers(), 1 );
}

//---------------------------------------------------------------------------//
// Check that an observer can be detached from the dispatcher
TEUCHOS_UNIT_TEST( ParticleSubtrackEndingGlobalEventDispatcher, 
		   detachObserver )
{
  MonteCarlo::ParticleSubtrackEndingGlobalEventDispatcher::detachObserver( 
                                                     estimator->getId() ); 
                                   
  TEST_EQUALITY_CONST( estimator.total_count(), 1 );
  TEST_EQUALITY_CONST( MonteCarlo::ParticleSubtrackEndingGlobalEventDispatcher::getNumberOfObservers(), 0 );
}

//---------------------------------------------------------------------------//
// Check that all observers can be detached from the dispatcher
TEUCHOS_UNIT_TEST( ParticleSubtrackEndingGlobalEventDispatcher, 
		   detachAllObservers )
{
  Teuchos::RCP<MonteCarlo::ParticleSubtrackEndingGlobalEventObserver> observer =
    Teuchos::rcp_dynamic_cast<MonteCarlo::ParticleSubtrackEndingGlobalEventObserver>( estimator );

  MonteCarlo::ParticleSubtrackEndingGlobalEventDispatcher::attachObserver(  
                                                      estimator->getId(),
                                                      observer );

  observer.reset();
                               
  TEST_EQUALITY_CONST( estimator.total_count(), 2 );
  TEST_EQUALITY_CONST( MonteCarlo::ParticleSubtrackEndingGlobalEventDispatcher::getNumberOfObservers(), 1 );                                                           
                                                             
  MonteCarlo::ParticleSubtrackEndingGlobalEventDispatcher::detachAllObservers(); 
  TEST_EQUALITY_CONST( estimator.total_count(), 1 );
  TEST_EQUALITY_CONST( MonteCarlo::ParticleSubtrackEndingGlobalEventDispatcher::getNumberOfObservers(), 0 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
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
  
  initializeTetMeshEstimator();
  
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
