//---------------------------------------------------------------------------//
//!
//! \file   DataGen_ScatteringFunctionEvaluator_def.hpp
//! \author Alex Robinson
//! \brief  The scattering function evaluator template definitions
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_SCATTERING_FUNCTION_EVALUATOR_DEF_HPP
#define DATA_GEN_SCATTERING_FUNCTION_EVALUATOR_DEF_HPP

// Std Lib Includes
#include "MonteCarlo_StandardScatteringFunction.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_DesignByContract.hpp"

namespace DataGen{

// Construction helper
template<typename InterpPolicy,
           typename GridArgumentUnit,
           typename FloatType,
           template<typename,typename...> class Array>
std::shared_ptr<ScatteringFunctionEvaluator>
ScatteringFunctionEvaluator::createEvaluator(
                          const Array<FloatType>& argument_grid,
                          const Array<FloatType>& scattering_function_values )
{
  // Make sure the argument grid is valid
  testPrecondition( argument_grid.front() >= 0.0 );
  testPrecondition( Utility::Sort::isSortedAscending( argument_grid.begin(),
                                                      argument_grid.end() ) );

  // Create the raw scattering function
  std::shared_ptr<Utility::UnitAwareUnivariateDistribution<GridArgumentUnit,void> >
    raw_scattering_function( new Utility::UnitAwareTabularDistribution<InterpPolicy,GridArgumentUnit,void>(
                                                argument_grid,
                                                scattering_function_values ) );

  std::unique_ptr<const MonteCarlo::ScatteringFunction> scattering_function(
                 new MonteCarlo::StandardScatteringFunction<GridArgumentUnit>(
                                                   raw_scattering_function ) );

  return std::shared_ptr<ScatteringFunctionEvaluator>(
                      new ScatteringFunctionEvaluator( scattering_function ) );
}

} // end DataGen namespace

#endif // end DATA_GEN_SCATTERING_FUNCTION_EVALUATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end DataGen_ScatteringFunctionEvaluator_def.hpp
//---------------------------------------------------------------------------//
