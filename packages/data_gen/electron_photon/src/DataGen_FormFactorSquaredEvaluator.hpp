//---------------------------------------------------------------------------//
//!
//! \file   DataGen_FormFactorSquaredEvaluator.hpp
//! \author Alex Robinson
//! \brief  The form factor squared evaluator declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_FORM_FACTOR_SQUARED_EVALUATOR_HPP
#define DATA_GEN_FORM_FACTOR_SQUARED_EVALUATOR_HPP

// Std Lib Includes
#include <memory>
#include <functional>

// FRENSIE Includes
#include "MonteCarlo_FormFactor.hpp"

namespace DataGen{

//! The form factor squared evaluator
class FormFactorSquaredEvaluator
{

public:

  //! Construction helper
  template<typename InterpPolicy,
           typename GridArgumentUnit,
           template<typename,typename...> class Array>
  static std::shared_ptr<FormFactorSquaredEvaluator> createEvaluator(
                                     const Array<double>& argument_grid,
                                     const Array<double>& form_factor_values );

  //! Destructor
  ~FormFactorSquaredEvaluator()
  { /* ... */ }

  //! Evaluate the form factor squared
  double evaluateFormFactorSquared( const double squared_argument ) const;

  //! Return a function that wraps the evaluation method
  std::function<double(double)> getFormFactorSquaredEvalutionWrapper() const;

private:

  //! Constructor
  FormFactorSquaredEvaluator(
                  std::unique_ptr<const MonteCarlo::FormFactor>& form_factor );

  // The form factor
  std::unique_ptr<const MonteCarlo::FormFactor> d_form_factor;
};
  
} // end DataGen namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "DataGen_FormFactorSquaredEvaluator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_GEN_FORM_FACTOR_SQUARED_EVALUATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_FormFactorSquaredEvaluator.hpp
//---------------------------------------------------------------------------//
