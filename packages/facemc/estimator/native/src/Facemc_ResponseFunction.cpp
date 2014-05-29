//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ResponseFunction.cpp
//! \author Alex Robinson
//! \brief  Response function base class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Facemc_ResponseFunction.hpp"
#include "Utility_ContractException.hpp"

namespace Facemc{

// Initialize the default response function
const Teuchos::RCP<ResponseFunction> 
ResponseFunction::default_response_function( new ResponseFunction("default") );

// Constructor
ResponseFunction::ResponseFunction( const std::string& name )
  : d_name( name )
{
  // Make sure the name is valid
  testPrecondition( name.size() > 0 );
}

// Return the name of the response function
const std::string& ResponseFunction::getName() const
{
  return d_name;
}

// Evaluate the response function at the desired phase space point
double ResponseFunction::evaluate( const ParticleState& particle ) const
{
  return 1.0;
}

// Check if the response function is spatially uniform
bool ResponseFunction::isSpatiallyUniform() const
{
  return true;
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_ResponseFunction.cpp
//---------------------------------------------------------------------------//
