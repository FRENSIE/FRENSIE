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
