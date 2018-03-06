//---------------------------------------------------------------------------//
//!
//! \file   DataGen_FormFactorEvaluator.hpp
//! \author Alex Robinson
//! \brief  The form factor evaluator declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_FORM_FACTOR_EVALUATOR_HPP
#define DATA_GEN_FORM_FACTOR_EVALUATOR_HPP

// Std Lib Includes
#include <memory>
#include <functional>

// FRENSIE Includes
#include "MonteCarlo_FormFactor.hpp"

namespace DataGen{

//! The form factor evaluator
class FormFactorEvaluator
{

public:

  //! Construction helper
  template<typename InterpPolicy,
           typename GridArgumentUnit,
           typename FloatType,
           template<typename,typename...> class Array>
  static std::shared_ptr<FormFactorEvaluator> createEvaluator(
                                  const Array<FloatType>& argument_grid,
                                  const Array<FloatType>& form_factor_values );

  //! Destructor
  ~FormFactorEvaluator()
  { /* ... */ }

  //! Evaluate the form factor
  double evaluateFormFactor( const double argument ) const;

  //! Return a function that wraps the form factor evaluation method
  std::function<double(double)> getFormFactorEvaluationWrapper() const;

  //! Evaluate the form factor squared
  double evaluateFormFactorSquared( const double squared_argument ) const;

  //! Return a function that wraps the form factor squared evaluation method
  std::function<double(double)> getFormFactorSquaredEvaluationWrapper() const;

private:

  //! Constructor
  FormFactorEvaluator(
                  std::unique_ptr<const MonteCarlo::FormFactor>& form_factor );

  // The form factor
  std::unique_ptr<const MonteCarlo::FormFactor> d_form_factor;
};
  
} // end DataGen namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "DataGen_FormFactorEvaluator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_GEN_FORM_FACTOR_EVALUATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_FormFactorEvaluator.hpp
//---------------------------------------------------------------------------//
