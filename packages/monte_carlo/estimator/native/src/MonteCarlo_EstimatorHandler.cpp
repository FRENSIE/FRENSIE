//---------------------------------------------------------------------------//
//! 
//! \file   MonteCarlo_EstimatorHandler.cpp
//! \author Alex Robinson
//! \brief  Estimator handler class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_EstimatorHandler.hpp"
#include "Utility_GlobalOpenMPSession.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Initialize the static member data
EstimatorHandler::EstimatorArray EstimatorHandler::master_array;

// Return the number of estimators that have been added
unsigned EstimatorHandler::getNumberOfEstimators()
{
  return EstimatorHandler::master_array.size();
}

// Enable support for multiple threads
/*! \details This should only be called after all of the estimators have been
 * added.
 */
void EstimatorHandler::enableThreadSupport( const unsigned num_threads )
{
  // Make sure only the master thread calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  
  EstimatorArray::iterator it = EstimatorHandler::master_array.begin();
  
  while( it != EstimatorHandler::master_array.end() )
  {
    (*it)->enableThreadSupport( num_threads );
    
    ++it;
  }
}

// Commit the estimator history contributions
void EstimatorHandler::commitEstimatorHistoryContributions()
{
  EstimatorArray::iterator it = EstimatorHandler::master_array.begin();
  
  while( it != EstimatorHandler::master_array.end() )
  {
    if( (*it)->hasUncommittedHistoryContribution() )
      (*it)->commitHistoryContribution();
    
    ++it;
  }
}

// Print the estimators
void EstimatorHandler::printEstimators( std::ostream& os,
					const double num_histories,
					const double start_time,
					const double end_time )
{
  // Make sure only the master thread calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  
  Estimator::setNumberOfHistories( num_histories );
  Estimator::setStartTime( start_time );
  Estimator::setEndTime( end_time );
  
  os << "Estimators: " << std::endl;
  
  EstimatorArray::iterator it = EstimatorHandler::master_array.begin();
  
  while( it != EstimatorHandler::master_array.end() )
  {
    os << *(*it) << std::endl;

    ++it;
  }
}

// Reset estimator data
void EstimatorHandler::resetEstimatorData()
{
  // Make sure only the master thread calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  
  EstimatorArray::iterator it = EstimatorHandler::master_array.begin();

  while( it != EstimatorHandler::master_array.end() )
  {
    (*it)->resetData();

    ++it;
  }
}

// Reduce the estimator data on all processes in comm and collect on the root
void EstimatorHandler::reduceEstimatorData(
	    const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
	    const int root_process )
{
  // Make sure only the master thread calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  
  EstimatorArray::iterator it = EstimatorHandler::master_array.begin();

  while( it != EstimatorHandler::master_array.end() )
  {
    (*it)->reduceData( comm, root_process );

    ++it;
  }
}

// Export the estimator data
void EstimatorHandler::exportEstimatorData( 
				  const std::string& data_file_name,
				  const unsigned long long last_history_number,
				  const unsigned long long histories_completed,
				  const double start_time,
				  const double end_time,
				  const bool process_data )
{
  // Make sure only the master thread calls this function
  testPrecondition( Utility::GlobalOpenMPSession::getThreadId() == 0 );
  
  // Initialize the HDF5 file
  EstimatorHDF5FileHandler hdf5_file_handler( data_file_name );

  // Set the simulation time
  hdf5_file_handler.setSimulationTime( end_time - start_time );

  Estimator::setStartTime( start_time );
  Estimator::setEndTime( end_time );
  
  // Set the last history simulated
  hdf5_file_handler.setLastHistorySimulated( last_history_number );

  // Set the number of histories simulated
  hdf5_file_handler.setNumberOfHistoriesSimulated( histories_completed );

  Estimator::setNumberOfHistories( histories_completed );

  // Export the data in each estimator
  EstimatorArray::iterator it = EstimatorHandler::master_array.begin();

  while( it != EstimatorHandler::master_array.end() )
  {
    (*it)->exportData( hdf5_file_handler, process_data );

    ++it;
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_EstimatorHandler.cpp
//---------------------------------------------------------------------------//
