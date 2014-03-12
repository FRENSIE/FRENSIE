//---------------------------------------------------------------------------//
//!
//! \file   ResponseFunction.hpp
//! \author Alex Robinson
//! \brief  Response function base class declaration 
//!
//---------------------------------------------------------------------------//

#ifndef RESPONSE_FUNCTION_HPP
#define RESPONSE_FUNCTION_HPP

// Std Lib Includes
#include <string>

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FACEMC Includes
#include "BasicParticleState.hpp"

namespace FACEMC{

//! The response function base class
class ResponseFunction
{

public:

  //! Constructor
  ResponseFunction( const std::string& name );

  //! Destructor
  virtual ~ResponseFunction()
  { /* ... */ }

  //! Return the name of the response function
  const std::string& getName() const;

  //! Evaluate the response function at the desired phase space point
  virtual double evaluate( const BasicParticleState& particle ) const;

  //! Check if the response function is spatially uniform
  virtual bool isSpatiallyUniform() const;

  //! Default response function
  static const Teuchos::RCP<ResponseFunction> default_response_function;

private:

  // The response function name
  std::string d_name;
};

} // end FACEMC namespace

#endif // end RESPONSE_FUNCTION_HPP

//---------------------------------------------------------------------------//
// end ResponseFunction.hpp
//---------------------------------------------------------------------------//
