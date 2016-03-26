//---------------------------------------------------------------------------//
//!
//! \file   tstParticleHistoryObserverHDF5FileHandler.cpp
//! \author Alex Robinson
//! \brief  Particle history observer hdf5 file handler unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <string>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_UnitTestHarnessExtensions.hpp"
#include "MonteCarlo_ParticleHistoryObserverHDF5FileHandler.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_HDF5FileHandler.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

const std::string hdf5_file_name( "test_pho.h5" );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the handler can be constructed
TEUCHOS_UNIT_TEST( ParticleHistoryObserverHDF5FileHandler, 
                   constructor_ownership )
{
  std::shared_ptr<MonteCarlo::ParticleHistoryObserverHDF5FileHandler> file_handler;
  TEST_NOTHROW( file_handler.reset( 
		new MonteCarlo::ParticleHistoryObserverHDF5FileHandler( 
                                                          hdf5_file_name ) ) );

  // Make sure setter methods work
  TEST_NOTHROW( file_handler->setSimulationTime( 1.0 ) );
  
  file_handler.reset();
  
  TEST_NOTHROW( file_handler.reset( 
                       new MonteCarlo::ParticleHistoryObserverHDF5FileHandler(
	hdf5_file_name,
	MonteCarlo::ParticleHistoryObserverHDF5FileHandler::APPEND_PHO_HDF5_FILE ) ) );

  // Make sure file has not been overwritten
  double simulation_time;
  file_handler->getSimulationTime( simulation_time );
  
  TEST_EQUALITY_CONST( simulation_time, 1.0 );

  // Make sure setter methods work
  TEST_NOTHROW( file_handler->setSimulationTime( 2.0 ) );

  file_handler.reset();

  TEST_NOTHROW( file_handler.reset( new MonteCarlo::ParticleHistoryObserverHDF5FileHandler(
     hdf5_file_name,
     MonteCarlo::ParticleHistoryObserverHDF5FileHandler::READ_ONLY_PHO_HDF5_FILE ) ) );

  // Make sure file has not been overwritten
  file_handler->getSimulationTime( simulation_time );
  TEST_EQUALITY_CONST( simulation_time, 2.0 );

  TEST_THROW( file_handler->setSimulationTime( 3.0 ), std::runtime_error );

  // Reset the file
  file_handler.reset();
  file_handler.reset(
		  new MonteCarlo::ParticleHistoryObserverHDF5FileHandler( hdf5_file_name ) );
}

//---------------------------------------------------------------------------//
// Check that the handler can be constructed
TEUCHOS_UNIT_TEST( ParticleHistoryObserverHDF5FileHandler, constructor_sharing )
{
  std::shared_ptr<Utility::HDF5FileHandler> shared_handler( 
						new Utility::HDF5FileHandler );
  shared_handler->openHDF5FileAndOverwrite( hdf5_file_name );

  std::shared_ptr<MonteCarlo::ParticleHistoryObserverHDF5FileHandler> 
    estimator_file_handler(
                       new MonteCarlo::ParticleHistoryObserverHDF5FileHandler( 
                                                            shared_handler ) );

  estimator_file_handler->setSimulationTime( 1.0 );
  
  estimator_file_handler.reset();

  TEST_ASSERT( shared_handler->hasOpenFile() );
  
  shared_handler->closeHDF5File();
}

//---------------------------------------------------------------------------//
// Check that the simulation time can be set
TEUCHOS_UNIT_TEST( ParticleHistoryObserverHDF5FileHandler, 
                   set_getSimulationTime )
{
  MonteCarlo::ParticleHistoryObserverHDF5FileHandler 
    file_handler( hdf5_file_name );

  // Write new simulation time
  file_handler.setSimulationTime( 1.0 );
  
  double simulation_time;

  file_handler.getSimulationTime( simulation_time );

  TEST_EQUALITY_CONST( simulation_time, 1.0 );

  // Overwrite simulation time
  file_handler.setSimulationTime( 2.0 );

  file_handler.getSimulationTime( simulation_time );

  TEST_EQUALITY_CONST( simulation_time, 2.0 );
}

//---------------------------------------------------------------------------//
// Check that the last history simulated can be set
TEUCHOS_UNIT_TEST( ParticleHistoryObserverHDF5FileHandler, 
                   set_getLastHistorySimulated )
{
  MonteCarlo::ParticleHistoryObserverHDF5FileHandler file_handler( hdf5_file_name );

  // Write new last history simulated
  file_handler.setLastHistorySimulated( 0ull );
  
  unsigned long long last_history_simulated;

  file_handler.getLastHistorySimulated( last_history_simulated );

  TEST_EQUALITY_CONST( last_history_simulated, 0ull );

  // Overwrite last history simulated
  file_handler.setLastHistorySimulated( 100ull );

  file_handler.getLastHistorySimulated( last_history_simulated );

  TEST_EQUALITY_CONST( last_history_simulated, 100ull );
}

//---------------------------------------------------------------------------//
// Check that the number of histories simulated can be set
TEUCHOS_UNIT_TEST( ParticleHistoryObserverHDF5FileHandler, 
                   set_getNumberOfHistoriesSimulated)
{
  MonteCarlo::ParticleHistoryObserverHDF5FileHandler 
    file_handler( hdf5_file_name );

  // Write new number of histories simulated
  file_handler.setNumberOfHistoriesSimulated( 10ull );

  unsigned long long number_simulated;

  file_handler.getNumberOfHistoriesSimulated( number_simulated );

  TEST_EQUALITY_CONST( number_simulated, 10ull );

  // Overwrite number of histories simulated
  file_handler.setNumberOfHistoriesSimulated( 100ull );

  file_handler.getNumberOfHistoriesSimulated( number_simulated );

  TEST_EQUALITY_CONST( number_simulated, 100ull );
}

//---------------------------------------------------------------------------//
// end tstParticleHistoryObserverHDF5FileHandler.cpp
//---------------------------------------------------------------------------//
