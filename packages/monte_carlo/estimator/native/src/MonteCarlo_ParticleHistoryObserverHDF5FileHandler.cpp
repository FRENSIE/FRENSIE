//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleHistoryObserverHDF5FileHandler.cpp
//! \author Alex Robinson
//! \brief  The particle history observer hdf5 file handler class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ParticleHistoryObserverHDF5FileHandler.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Initialize static member data
const std::string ParticleHistoryObserverHDF5FileHandler::s_pho_group_loc_name(
                                                                         "/" );

// Constructor (file ownership)
/*! \details The ParticleHistoryObserverHDF5FileOps enum will determine how the
 * HDF5 file is opened. If the read only option is used, calling any of the set
 * methods will result in an exception.
 */
ParticleHistoryObserverHDF5FileHandler::ParticleHistoryObserverHDF5FileHandler(
                             const std::string& hdf5_file_name,
                             const ParticleHistoryObserverHDF5FileOps file_op )
  : d_hdf5_file( new Utility::HDF5FileHandler ),
    d_hdf5_file_ownership( true )
{
  // Make sure the name is valid
  testPrecondition( hdf5_file_name.size() > 0 );

  Utility::HDF5FileHandler::throwExceptions();

  try{
    switch( file_op )
    {
    case OVERWRITE_PHO_HDF5_FILE:
      d_hdf5_file->openHDF5FileAndOverwrite( hdf5_file_name );
      break;
    case APPEND_PHO_HDF5_FILE:
      d_hdf5_file->openHDF5FileAndAppend( hdf5_file_name );
      break;
    case READ_ONLY_PHO_HDF5_FILE:
      d_hdf5_file->openHDF5FileAndReadOnly( hdf5_file_name );
      break;
    }
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Ownership Constructor Error" );
}

// Constructor (file sharing)
ParticleHistoryObserverHDF5FileHandler::ParticleHistoryObserverHDF5FileHandler(
                  const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file )
  : d_hdf5_file( hdf5_file ),
    d_hdf5_file_ownership( false )
{
  // Make sure the file is valid
  testPrecondition( hdf5_file.get() );
  testPrecondition( hdf5_file->hasOpenFile() );

  Utility::HDF5FileHandler::throwExceptions();
}

// Destructor
ParticleHistoryObserverHDF5FileHandler::~ParticleHistoryObserverHDF5FileHandler()
{
  if( d_hdf5_file_ownership )
    d_hdf5_file->closeHDF5File();
}

// Set the simulation time
void ParticleHistoryObserverHDF5FileHandler::setSimulationTime( 
                                                 const double simulation_time )
{
  // Make sure the simulation time is valid
  testPrecondition( simulation_time > 0.0 );
  
  try{
    d_hdf5_file->writeValueToGroupAttribute( simulation_time,
					     s_pho_group_loc_name,
					     "simulation_time" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, "Set Simulation Time Error" );
}

// Get the simulation time
void ParticleHistoryObserverHDF5FileHandler::getSimulationTime( double& simulation_time ) const
{
  try{
    d_hdf5_file->readValueFromGroupAttribute( simulation_time,
					      s_pho_group_loc_name,
					      "simulation_time" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, "Get Simulation Time Error" );
}

// Set the last history simulated
void ParticleHistoryObserverHDF5FileHandler::setLastHistorySimulated( 
			     const unsigned long long last_history_simulated )
{
  try{
    d_hdf5_file->writeValueToGroupAttribute( last_history_simulated,
					     s_pho_group_loc_name,
					     "last_history_simulated" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Set Last History Simulated Error" );
}

// Get the last history simulated
void ParticleHistoryObserverHDF5FileHandler::getLastHistorySimulated( 
			    unsigned long long& last_history_simulated ) const
{
  try{
    d_hdf5_file->readValueFromGroupAttribute( last_history_simulated,
					      s_pho_group_loc_name,
					      "last_history_simulated" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Get Last History Simulated Error" );
}

// Set the number of histories simulated
void ParticleHistoryObserverHDF5FileHandler::setNumberOfHistoriesSimulated(
		   const unsigned long long number_histories_simulated )
{
  // Make sure the number of histories simulated is valid
  testPrecondition( number_histories_simulated > 0ull );
  
  try{
    d_hdf5_file->writeValueToGroupAttribute( number_histories_simulated,
					     s_pho_group_loc_name,
					     "number_of_histories_simulated" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Set Number of Histories Simulated Error" );
}

// Get the number of histories simulated
void ParticleHistoryObserverHDF5FileHandler::getNumberOfHistoriesSimulated(
		        unsigned long long& number_histories_simulated ) const
{
  try{
    d_hdf5_file->readValueFromGroupAttribute( number_histories_simulated,
					      s_pho_group_loc_name,
					      "number_of_histories_simulated");
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Get Number of Histories Simulated Error" );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleHistoryObserverHDF5FileHandler.cpp
//---------------------------------------------------------------------------//
