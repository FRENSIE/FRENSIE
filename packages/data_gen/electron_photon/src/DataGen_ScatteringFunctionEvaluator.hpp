//---------------------------------------------------------------------------//
//!
//! \file   DataGen_ScatteringFunctionEvaluator.hpp
//! \author Alex Robinson
//! \brief  The scattering function evaluator declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_SCATTERING_FUNCTION_EVALUATOR_HPP
#define DATA_GEN_SCATTERING_FUNCTION_EVALUATOR_HPP

// Std Lib Includes
#include <memory>
#include <functional>

// FRENSIE Includes
#include "MonteCarlo_ScatteringFunction.hpp"

namespace DataGen{

//! The scattering function evaluator
class ScatteringFunctionEvaluator
{

public:

  //! Constructor helper
  template<typename InterpPolicy,
           typename GridArgumentUnit,
           typename FloatType,
           template<typename,typename...> class Array>
  static std::shared_ptr<ScatteringFunctionEvaluator> createEvaluator(
                          const Array<FloatType>& argument_grid,
                          const Array<FloatType>& scattering_function_values );

  //! Destructor
  ~ScatteringFunctionEvaluator()
  { /* ... */ }

  //! Evaluate the scattering function
  double evaluateScatteringFunction( const double argument ) const;

  //! Return a function that wraps the scattering function evaluation method
  std::function<double(double)> getScatteringFunctionEvaluationWrapper() const;

private:

  //! Constructor
  ScatteringFunctionEvaluator(
   std::unique_ptr<const MonteCarlo::ScatteringFunction>& scattering_function);

  // The scattering function
  std::unique_ptr<const MonteCarlo::ScatteringFunction> d_scattering_function;
};
  
} // end DataGen namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "DataGen_ScatteringFunctionEvaluator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_GEN_SCATTERING_FUNCTION_EVALUATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_ScatteringFunctionEvaluator.hpp
//---------------------------------------------------------------------------//
