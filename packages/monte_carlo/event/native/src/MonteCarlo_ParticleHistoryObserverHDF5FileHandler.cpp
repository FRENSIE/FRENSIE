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
  : MonteCarlo::HDF5FileHandler( hdf5_file_name, file_op )
{
  // Make sure the name is valid
  testPrecondition( hdf5_file_name.size() > 0 );
}

// Constructor (file sharing)
ParticleHistoryObserverHDF5FileHandler::ParticleHistoryObserverHDF5FileHandler(
                  const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file )
  : MonteCarlo::HDF5FileHandler( hdf5_file )
{ /* ... */ }

// Destructor
ParticleHistoryObserverHDF5FileHandler::~ParticleHistoryObserverHDF5FileHandler()
{ /* ... */ }

// Set the simulation time
void ParticleHistoryObserverHDF5FileHandler::setSimulationTime(
                                                 const double simulation_time )
{
  // Make sure the simulation time is valid
  testPrecondition( simulation_time > 0.0 );

  try{
    this->getHDF5File().writeValueToGroupAttribute( simulation_time,
                                                    s_pho_group_loc_name,
                                                    "simulation_time" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "Could not set the simulation time in the HDF5 "
                           "file!" );
}

// Get the simulation time
void ParticleHistoryObserverHDF5FileHandler::getSimulationTime( double& simulation_time ) const
{
  try{
    this->getHDF5File().readValueFromGroupAttribute( simulation_time,
                                                     s_pho_group_loc_name,
                                                     "simulation_time" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "Could not get the simulation time from the HDF5 "
                           "file!" );
  
}

// Set the last history simulated
void ParticleHistoryObserverHDF5FileHandler::setLastHistorySimulated(
			     const unsigned long long last_history_simulated )
{
  try{
    this->getHDF5File().writeValueToGroupAttribute( last_history_simulated,
                                                    s_pho_group_loc_name,
                                                    "last_history_simulated" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Could not set the last history (id) simulated in "
                           "the HDF5 file!" );
}

// Get the last history simulated
void ParticleHistoryObserverHDF5FileHandler::getLastHistorySimulated(
			    unsigned long long& last_history_simulated ) const
{
  try{
    this->getHDF5File().readValueFromGroupAttribute(last_history_simulated,
                                                    s_pho_group_loc_name,
                                                    "last_history_simulated" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Could not get the last history (id) simulated "
                           "from the HDF5 file!" );
}

// Set the number of histories simulated
void ParticleHistoryObserverHDF5FileHandler::setNumberOfHistoriesSimulated(
		   const unsigned long long number_histories_simulated )
{
  // Make sure the number of histories simulated is valid
  testPrecondition( number_histories_simulated > 0ull );

  try{
    this->getHDF5File().writeValueToGroupAttribute(
                                             number_histories_simulated,
                                             s_pho_group_loc_name,
                                             "number_of_histories_simulated" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Could not set the number of histories simulated "
                           "in the HDF5 file!" );
}

// Get the number of histories simulated
void ParticleHistoryObserverHDF5FileHandler::getNumberOfHistoriesSimulated(
		        unsigned long long& number_histories_simulated ) const
{
  try{
    this->getHDF5File().readValueFromGroupAttribute(
                                              number_histories_simulated,
					      s_pho_group_loc_name,
					      "number_of_histories_simulated");
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Could not get the number of histories simulated "
                           "from the HDF5 file!" );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleHistoryObserverHDF5FileHandler.cpp
//---------------------------------------------------------------------------//
