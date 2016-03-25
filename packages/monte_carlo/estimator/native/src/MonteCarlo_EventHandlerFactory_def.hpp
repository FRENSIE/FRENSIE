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
#include "MonteCarlo_ParticleTrackerFactory.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

//! Create the event handler
template<typename GeometryHandler>
std::shared_ptr<EventHandler>
EventHandlerFactory<GeometryHandler>::createHandler( 
       const Teuchos::ParameterList& observer_reps,
       const boost::unordered_map<unsigned,std::shared_ptr<ResponseFunction> >&
       response_function_id_map,
       std::ostream* os_warn )
{
  // Create a new event handler
  std::shared_ptr<EventHandler> event_handler( new EventHandler() );

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

  // Create the particle tracker factory
  std::shared_ptr<ParticleTrackerFactory> ptrac_factory;
  
  try{
    ptrac_factory =
      getParticleTrackerFactoryInstance( event_handler,
                                         os_warn );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::exception,
                              InvalidObserverRepresentation,
                              "Error: The particle tracker could not be created!" );

  // Create the observers
  Teuchos::ParameterList::ConstIterator observer_rep_it = 
    observer_reps.begin();

  while( observer_rep_it != observer_reps.end() )
  {
    // Make sure every parameter entry is a list
    TEST_FOR_EXCEPTION( !observer_rep_it->second.isList(),
                        InvalidObserverRepresentation,
                        "Error: all observers must be specified with "
                        "parameter lists (non-list parameter was found in "
                        "the observers xml file!" );
                        
    const Teuchos::ParameterList& observer_rep = 
      Teuchos::any_cast<Teuchos::ParameterList>( 
                                            observer_rep_it->second.getAny() );

    try{
      // Create the estimator
      if( estimator_factory->isEstimatorRep( observer_rep ) )
        estimator_factory->createAndRegisterEstimator( observer_rep );
      
      // Create the particle tracker
      else if( ptrac_factory->isParticleTrackerRep( observer_rep ) )
        ptrac_factory->createAndRegisterParticleTracker( observer_rep );
      
      // Invalid observer
      else
      {
        THROW_EXCEPTION( InvalidObserverRepresentation,
                         "Error: observer " << observer_rep.name() <<
                         " is not supported!" );
      }
    }
    EXCEPTION_CATCH_RETHROW_AS( std::exception,
                                InvalidObserverRepresentation,
                                "Error: The observers could not be "
                                "created!");

    ++observer_rep_it;
  }

  // Create any cached observers
  try{
    estimator_factory->createAndRegisterCachedEstimators();
  }
  EXCEPTION_CATCH_RETHROW_AS( std::exception,
                              InvalidObserverRepresentation,
                              "Error: the cached observers could not be "
                              "created!" );

  // Return the new event handler
  return event_handler;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_EVENT_HANDLER_FACTORY_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_EventHandlerFactory_def.hpp
//---------------------------------------------------------------------------//
