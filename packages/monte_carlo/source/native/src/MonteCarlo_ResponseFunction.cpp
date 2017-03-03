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
ResponseFunction::default_response_function;

// Return the id
ModuleTraits::InternalROIHandle ResponseFunction::getId() const
{
  return std::numeric_limits<ModuleTraits::InternalROIHandle>::max();
}

// Return the name of the response function
const std::string& ResponseFunction::getName() const
{
  static const std::string default_name( "default" );
  
  return default_name;
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
