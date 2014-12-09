//---------------------------------------------------------------------------//
//! 
//! \file   MonteCarlo_EstimatorHandler.cpp
//! \author Alex Robinson
//! \brief  Estimator handler class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_EstimatorHandler.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Initialize the static member data
EstimatorHandler::EstimatorArray EstimatorHandler::master_array;

// Return the number of estimators that have been added
unsigned EstimatorHandler::getNumberOfEstimators()
{
  return EstimatorHandler::master_array.size();
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

// Export the estimator data
void EstimatorHandler::exportEstimatorData( const std::string& data_file_name,
					    const unsigned last_history_number,
					    const unsigned histories_completed,
					    const double start_time,
					    const double end_time )
{
  
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_EstimatorHandler.cpp
//---------------------------------------------------------------------------//
