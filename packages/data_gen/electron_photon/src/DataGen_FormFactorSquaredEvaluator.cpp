//---------------------------------------------------------------------------//
//!
//! \file   DataGen_FormFactorSquaredEvaluator.cpp
//! \author Alex Robinson
//! \brief  The form factor squared evaluator definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "DataGen_FormFactorSquaredEvaluator.hpp"
#include "Utility_ContractException.hpp"

namespace DataGen{

// Constructor
FormFactorSquaredEvaluator::FormFactorSquaredEvaluator(
                   std::unique_ptr<const MonteCarlo::FormFactor>& form_factor )
{
  // Make sure the form factor is valid
  testPrecondition( form_factor.get() );

  // Take ownership of the form factor object
  d_form_factor.swap( form_factor );
}

// Evaluate the form factor squared
/*! \details The squared argument must have units of inverse square cm.
 */
double FormFactorSquaredEvaluator::evaluateFormFactorSquared(
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
FormFactorSquaredEvaluator::getFormFactorSquaredEvalutionWrapper() const
{
  return std::bind<double>(
                        &FormFactorSquaredEvaluator::evaluateFormFactorSquared,
                        std::cref( *this ),
                        std::placeholders::_1 );
}
  
} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_FormFactorSquaredEvaluator.cpp
//---------------------------------------------------------------------------//
