//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ResponseFunctionFactory.hpp
//! \author Alex Robinson
//! \brief  Response function factory class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_RESPONSE_FUNCTION_FACTORY_HPP
#define MONTE_CARLO_RESPONSE_FUNCTION_FACTORY_HPP

// Std Lib Includes
#include <stdexcept>
#include <memory>

// Boost Includes
#include <boost/unordered_map.hpp>

// Trilinos Includes
#include <Teuchos_ParameterList.hpp>

// FRENSIE Includes
#include "MonteCarlo_ResponseFunction.hpp"

namespace MonteCarlo{

//! The response function factory
class ResponseFunctionFactory
{
  
public:

  //! Create the response functions specified
  static void createResponseFunctions( 
	     const Teuchos::ParameterList& response_reps,
	     boost::unordered_map<unsigned,std::shared_ptr<ResponseFunction> >&
             response_id_map );

private:

  // Constructor
  ResponseFunctionFactory();

  // Validate a response function representation
  static void validateResponseFunctionRep(
				  const Teuchos::ParameterList& response_rep );

  // Create an energy space response function
  static void createEnergySpaceResponseFunction(
	     const Teuchos::ParameterList& response_rep,
	     boost::unordered_map<unsigned,std::shared_ptr<ResponseFunction> >&
             response_id_map );

  // Create a phase space response function
  static void createPhaseSpaceResponseFunction(
	     const Teuchos::ParameterList& response_rep,
	     boost::unordered_map<unsigned,std::shared_ptr<ResponseFunction> >&
             response_id_map );

  // Create the response function name
  static std::string createName( const Teuchos::ParameterList& response_rep );
};

//! The invalid response function representation error
class InvalidResponseFunctionRepresentation : public std::logic_error
{
  
public:

  InvalidResponseFunctionRepresentation( const std::string& what_arg )
    : std::logic_error( what_arg )
  { /* ... */ }
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_RESPONSE_FUNCTION_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ResponseFunctionFactory.hpp
//---------------------------------------------------------------------------//
