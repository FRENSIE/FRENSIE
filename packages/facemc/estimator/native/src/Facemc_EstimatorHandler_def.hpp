//---------------------------------------------------------------------------//
//!
//! \file   Facemc_EstimatorHandler_def.hpp
//! \author Alex Robinson
//! \brief  Estimator handler class definition.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_ESTIMATOR_HANDLER_DEF_HPP
#define FACEMC_ESTIMATOR_HANDLER_DEF_HPP

// FRENSIE Includes
#include "Facemc_ObserverRegistrationHelpers.hpp"
#include "Utility_ContractException.hpp"

namespace Facemc{

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

} // end Facemc namespace

#endif // end FACEMC_ESTIMATOR_HANDLER_DEF_HPP

//---------------------------------------------------------------------------//
// end Facemc_EstimatorHandler_def.hpp
//---------------------------------------------------------------------------//
