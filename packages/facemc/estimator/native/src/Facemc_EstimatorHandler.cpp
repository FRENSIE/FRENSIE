//---------------------------------------------------------------------------//
//! 
//! \file   Facemc_EstimatorHandler.cpp
//! \author Alex Robinson
//! \brief  Estimator handler class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Facemc_EstimatorHandler.hpp"
#include "Utility_ContractException.hpp"

namespace Facemc{

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
void EstimatorHandler::printEstimators( std::ostream& os )
{
  os << "Estimators: " << std::endl;
  
  EstimatorArray::iterator it = EstimatorHandler::master_array.begin();
  
  while( it != EstimatorHandler::master_array.end() )
  {
    os << *(*it) << std::endl;

    ++it;
  }
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_EstimatorHandler.cpp
//---------------------------------------------------------------------------//
