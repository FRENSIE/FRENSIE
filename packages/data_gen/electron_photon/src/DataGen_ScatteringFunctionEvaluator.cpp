//---------------------------------------------------------------------------//
//!
//! \file   DataGen_ScatteringFunctionEvaluator.cpp
//! \author Alex Robinson
//! \brief  The scattering function evaluator definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "DataGen_ScatteringFunctionEvaluator.hpp"
#include "Utility_DesignByContract.hpp"

namespace DataGen{

// Constructor
ScatteringFunctionEvaluator::ScatteringFunctionEvaluator(
    std::unique_ptr<const MonteCarlo::ScatteringFunction>& scattering_function)
{
  // Make sure the scattering function is valid
  testPrecondition( scattering_function.get() );

  // Take ownership of the scattering function object
  d_scattering_function.swap( scattering_function );
}
  
// Evaluate the scattering function
double ScatteringFunctionEvaluator::evaluateScatteringFunction(
                                                  const double argument ) const
{
  // Make sure the argument is valid
  testPrecondition( argument >= 0.0 );

  return d_scattering_function->evaluate(
                                 argument*Utility::Units::inverse_centimeter );
}

// Return a function that wraps the scattering function evaluation method
std::function<double(double)> ScatteringFunctionEvaluator::getScatteringFunctionEvaluationWrapper() const
{
  return std::bind<double>(
                      &ScatteringFunctionEvaluator::evaluateScatteringFunction,
                      std::cref( *this ),
                      std::placeholders::_1 );
}
  
} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_ScatteringFunctionEvaluator.cpp
//---------------------------------------------------------------------------//
