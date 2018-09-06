//---------------------------------------------------------------------------//
//!
//! \file   DataGen_FormFactorEvaluator.cpp
//! \author Alex Robinson
//! \brief  The form factor squared evaluator definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "DataGen_FormFactorEvaluator.hpp"
#include "Utility_DesignByContract.hpp"

namespace DataGen{

// Constructor
FormFactorEvaluator::FormFactorEvaluator(
                   std::unique_ptr<const MonteCarlo::FormFactor>& form_factor )
{
  // Make sure the form factor is valid
  testPrecondition( form_factor.get() );

  // Take ownership of the form factor object
  d_form_factor.swap( form_factor );
}

// Evaluate the form factor
double FormFactorEvaluator::evaluateFormFactor( const double argument ) const
{
  // Make sure the squared argument is valid
  testPrecondition( argument >= 0.0 );

  return d_form_factor->evaluate(argument*Utility::Units::inverse_centimeter);
}

// Return a function that wraps the form factor evaluation method
std::function<double(double)>
FormFactorEvaluator::getFormFactorEvaluationWrapper() const
{
  return std::bind<double>( &FormFactorEvaluator::evaluateFormFactor,
                            std::cref( *this ),
                            std::placeholders::_1 );
}

// Evaluate the form factor squared
/*! \details The squared argument must have units of inverse square cm.
 */
double FormFactorEvaluator::evaluateFormFactorSquared(
                                          const double squared_argument ) const
{
  // Make sure the squared argument is valid
  testPrecondition( squared_argument >= 0.0 );

  const double form_factor_value =
    d_form_factor->evaluate( std::sqrt(squared_argument)*
                             Utility::Units::inverse_centimeter );

  return form_factor_value*form_factor_value;
}

// Return a function that wraps the evaluation method
std::function<double(double)>
FormFactorEvaluator::getFormFactorSquaredEvaluationWrapper() const
{
  return std::bind<double>( &FormFactorEvaluator::evaluateFormFactorSquared,
                            std::cref( *this ),
                            std::placeholders::_1 );
}
  
} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_FormFactorEvaluator.cpp
//---------------------------------------------------------------------------//
