//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EventHandlerFactory.hpp
//! \author Alex Robinson
//! \brief  The event handler factory base class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_EVENT_HANDLER_FACTORY_HPP
#define MONTE_CARLO_EVENT_HANDLER_FACTORY_HPP

// Std Lib Includes
#include <stdexcept>
#include <iostream>
#include <memory>

// Boost Includes
#include <boost/unordered_map.hpp>

// Trilinos Includes
#include <Teuchos_ParameterList.hpp>

// FRENSIE Includes
#include "MonteCarlo_EventHandler.hpp"
#include "MonteCarlo_ResponseFunction.hpp"

namespace MonteCarlo{
//
//! The event handler factory
template<typename GeometryHandler>
class EventHandlerFactory
{

public:

  //! Create the event handler
  static std::shared_ptr<EventHandler> createHandler(
       const Teuchos::ParameterList& observer_reps,
       const boost::unordered_map<unsigned,std::shared_ptr<ResponseFunction> >&
       response_function_id_map,
       std::ostream* os_warn = &std::cerr );

private:

  // Constructor
  EventHandlerFactory();
};

//! The invalid observer representation error
class InvalidObserverRepresentation : public std::runtime_error
{

public:

  InvalidObserverRepresentation( const std::string& what_arg )
    : std::runtime_error( what_arg )
  { /* ... */ }
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_EventHandlerFactory_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_EVENT_HANDLER_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_EventHandlerFactory.hpp
//---------------------------------------------------------------------------//
