//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ResponseFunction.hpp
//! \author Alex Robinson
//! \brief  Response function base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_RESPONSE_FUNCTION_HPP
#define MONTE_CARLO_RESPONSE_FUNCTION_HPP

// Std Lib Includes
#include <string>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_ModuleTraits.hpp"
#include "MonteCarlo_ParticleState.hpp"

namespace MonteCarlo{

//! The response function base class
class ResponseFunction
{

public:

  //! Constructor
  ResponseFunction()
  { /* ... */ }

  //! Destructor
  virtual ~ResponseFunction()
  { /* ... */ }

  //! Return the id
  virtual ModuleTraits::InternalROIHandle getId() const;

  //! Return the name of the response function
  virtual const std::string& getName() const;

  //! Evaluate the response function at the desired phase space point
  virtual double evaluate( const ParticleState& particle ) const;

  //! Check if the response function is spatially uniform
  virtual bool isSpatiallyUniform() const;

  //! Default response function
  static const std::shared_ptr<ResponseFunction> default_response_function;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_RESPONSE_FUNCTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ResponseFunction.hpp
//---------------------------------------------------------------------------//
