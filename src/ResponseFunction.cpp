//---------------------------------------------------------------------------//
//!
//! \file   ResponseFunction.cpp
//! \author Alex Robinson
//! \brief  Response function base class definition.
//!
//---------------------------------------------------------------------------//

// FACEMC Includes
#include "ContractException.hpp"
#include "ResponseFunction.hpp"

namespace FACEMC{

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
double ResponseFunction::evaluate( const BasicParticleState& particle ) const
{
  return 1.0;
}

// Check if the response function is spatially uniform
bool ResponseFunction::isSpatiallyUniform() const
{
  return true;
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end ResponseFunction.cpp
//---------------------------------------------------------------------------//
