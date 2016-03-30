//---------------------------------------------------------------------------//
//!
//! \file   tstParticleTrackerFactory.cpp
//! \author Eli Moll
//! \brief  Particle tracker factory test
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <typeinfo>
#include <memory>
#include <unordered_map>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_DefaultComm.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleTracker.hpp"
#include "MonteCarlo_ParticleTrackerFactory.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "MonteCarlo_ParticleTrackerHDF5FileHandler.hpp"
#include "MonteCarlo_ResponseFunctionFactory.hpp"
#include "MonteCarlo_EventHandler.hpp"


//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
Teuchos::RCP<Teuchos::ParameterList> observer_reps;

std::shared_ptr<MonteCarlo::EventHandler> event_handler;

std::shared_ptr<MonteCarlo::ParticleTrackerFactory> ptrac_factory;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the factory can be constructed
TEUCHOS_UNIT_TEST( ParticleTrackerFactory, constructor )
{
  TEST_NOTHROW( ptrac_factory = 
                MonteCarlo::getParticleTrackerFactoryInstance(
                                                  event_handler ) );
}

//---------------------------------------------------------------------------//
// Check if estimators can be created and registered with the event handler
TEUCHOS_UNIT_TEST( ParticleTrackerFactory, createAndRegisterParticleTracker )
{
  Teuchos::ParameterList::ConstIterator observer_rep_it = 
    observer_reps->begin();

  while( observer_rep_it != observer_reps->end() )
  {
    const Teuchos::ParameterList& observer_rep = 
      Teuchos::any_cast<Teuchos::ParameterList>(
                                            observer_rep_it->second.getAny() );

    ptrac_factory->createAndRegisterParticleTracker( observer_rep );

    ++observer_rep_it;
  }

  // Check that the ptrac was created
  TEST_EQUALITY_CONST( event_handler->getNumberOfObservers(), 1 );

  std::string ptrac_file_name( "particle_tracker_factory.h5" );

  {
    std::shared_ptr<Utility::HDF5FileHandler>
        hdf5_file( new Utility::HDF5FileHandler );
    hdf5_file->openHDF5FileAndOverwrite( ptrac_file_name );

    event_handler->exportObserverData( hdf5_file,
                                       1,
                                       1,
                                       0.0,
                                       1.0,
                                       false );
                                       
    // PTRAC HDF5 File Handler can import/export the data map for a completed
    //   particle tracking routine. This could be implemented in this test if
    //   needed, although it is already done in the 
    //   ParticleTrackerHDF5FileHandler test
  }
}

//---------------------------------------------------------------------------//
// Get the particle tracker ID
TEUCHOS_UNIT_TEST( ParticleTrackerFactory, getParticleTrackerID )
{
  Teuchos::ParameterList::ConstIterator observer_rep_it = 
  observer_reps->begin();

  while( observer_rep_it != observer_reps->end() )
  {
    const Teuchos::ParameterList& observer_rep = 
      Teuchos::any_cast<Teuchos::ParameterList>(
                                            observer_rep_it->second.getAny() );

      TEST_EQUALITY_CONST( ptrac_factory->getParticleTrackerID( observer_rep ), 1 );

    ++observer_rep_it;
  }
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_observer_xml_file_name;
 
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_observer_xml_file",
		 &test_observer_xml_file_name,
		 "Test estimator xml file name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();
  
  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Load the observer parameter lists
  observer_reps = 
    Teuchos::getParametersFromXmlFile( test_observer_xml_file_name );


  // Initialize the event handler
  event_handler.reset( new MonteCarlo::EventHandler );

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
// end tstParticleTrackerFactory.cpp
//---------------------------------------------------------------------------//
