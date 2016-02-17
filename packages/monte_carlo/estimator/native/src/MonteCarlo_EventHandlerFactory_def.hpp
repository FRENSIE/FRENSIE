//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EventHandlerFactory_def.hpp
//! \author Alex Robinson
//! \brief  The event handler factory
//! 
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_EVENT_HANDLER_FACTORY_DEF_HPP
#define MONTE_CARLO_EVENT_HANDLER_FACTORY_DEF_HPP

// FRENSIE Includes
#include "MonteCarlo_StandardEstimatorFactory_DagMC.hpp"
#include "MonteCarlo_StandardEstimatorFactory_Root.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

//! Create the event handler
template<typename GeometryHandler>
void EventHandlerFactory<GeometryHandler>::createHandler( 
          std::shared_ptr<EventHandler>& event_handler,
          const Teuchos::ParameterList& observer_reps,
          const boost::unordered_map<unsigned,Teuchos::RCP<ResponseFunction> >&
          response_function_id_map,
          std::ostream* os_warn )
{
  // Reset the event handler
  event_handler.reset( new EventHandler() );

  // Create the estimator factory
  std::shared_ptr<EstimatorFactory> estimator_factory;
  
  try{
    estimator_factory = 
      getEstimatorFactoryInstance<GeometryHandler>( event_handler,
                                                    response_function_id_map,
                                                    os_warn );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::exception,
                              InvalidObserverRepresentation,
                              "Error: The observers could not be created!" );

  // Create the observers
  Teuchos::ParameterList::ConstIterator observer_rep = observer_reps.begin();

  while( observer_rep != observer_reps.end() )
  {
    // Note: if the parameter entry is not a parameter list an exception will
    // get thrown here - there should probably be better error handling...
    const Teuchos::Parameterlist& observer_rep = 
      Teuchos::any_cast<Teuchos::ParameterList>( it->second.getAny() );

    try{
      // Create the estimator
      if( estimator_factory->isEstimatorRep( observer_rep ) )
        estimator_factory->createAndRegisterEstimator( observer_rep );
      
      // Invalid observer
      else
      {
        THROW_EXCEPTION( InvalidObserverRepresentation,
                         "Error: observer " << observer_rep.name() <<
                         " is not supported!" );
      }
      EXCEPTION_CATCH_RETHROW_AS( std::exception,
                                  InvalidObserverRepresentation,
                                  "Error: The observers could not be "
                                  "created!");
    }

    ++observer_rep;
  }

  // Create any cached observers
  estimator_factory->createAndRegisterCachedEstimators();
}

#endif // end MONTE_CARLO_EVENT_HANDLER_FACTORY_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_EventHandlerFactory_def.hpp
//---------------------------------------------------------------------------//
