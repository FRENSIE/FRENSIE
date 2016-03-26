//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ResponseFunction.cpp
//! \author Alex Robinson
//! \brief  Response function base class definition.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "MonteCarlo_ResponseFunction.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Initialize the default response function
const std::shared_ptr<ResponseFunction> 
ResponseFunction::default_response_function( new ResponseFunction(
					  std::numeric_limits<unsigned>::max(),
					  "default" ) );

// Constructor
ResponseFunction::ResponseFunction( const unsigned id,
				    const std::string& name )
  : d_id( id ),
    d_name( name )
{
  // Make sure the name is valid
  testPrecondition( name.size() > 0 );
}

// Return the id
unsigned ResponseFunction::getId() const
{
  return d_id;
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

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ResponseFunction.cpp
//---------------------------------------------------------------------------//
