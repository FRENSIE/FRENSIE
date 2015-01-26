//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EstimatorHandler_def.hpp
//! \author Alex Robinson
//! \brief  Estimator handler class definition.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_ESTIMATOR_HANDLER_DEF_HPP
#define FACEMC_ESTIMATOR_HANDLER_DEF_HPP

// FRENSIE Includes
#include "MonteCarlo_ObserverRegistrationHelpers.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Add an estimator to the handler
/*! \details The estimator will be registered with the appropriate dispatchers.
 */
template<typename EstimatorType, typename EntityHandle>
void EstimatorHandler::addEstimator( 
			       Teuchos::RCP<EstimatorType>& estimator,
			       const Teuchos::Array<EntityHandle>& entity_ids )
{
  // Make sure the estimator is valid
  testPrecondition( !estimator.is_null() );
  // Make sure at least one entity id is specified
  testPrecondition( entity_ids.size() > 0 );
  
  // Register the estimator with the particle event dispatchers
  REGISTER_OBSERVER_WITH_DISPATCHERS( estimator, entity_ids );

  // Add the estimator to the master list
  EstimatorHandler::master_array.push_back( estimator );
}

// Add a global estimator to the handler
/*! \details The estimator will be registered with the appropriate dispatchers.
 */
template<typename EstimatorType>
void EstimatorHandler::addGlobalEstimator( 
				       Teuchos::RCP<EstimatorType>& estimator )
{
  // Make sure estimator is valid
  testPrecondition( !estimator.is_null() );
 
  // Register the estimator with the particle global event dispatchers
  REGISTER_GLOBAL_OBSERVER_WITH_DISPATCHERS( estimator );

  // Add the estimator to the master list
  EstimatorHandler::master_array.push_back( estimator );
}

} // end MonteCarlo namespace

#endif // end FACEMC_ESTIMATOR_HANDLER_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_EstimatorHandler_def.hpp
//---------------------------------------------------------------------------//
