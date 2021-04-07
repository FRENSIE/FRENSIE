//---------------------------------------------------------------------------//
//!
//! \file   DataGen_FormFactorEvaluator_def.hpp
//! \author Alex Robinson
//! \brief  The form factor evaluator declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_FORM_FACTOR_EVALUATOR_DEF_HPP
#define DATA_GEN_FORM_FACTOR_EVALUATOR_DEF_HPP

// FRENSIE Includes
#include "MonteCarlo_StandardFormFactor.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_DesignByContract.hpp"

namespace DataGen{

// Construction helper
template<typename InterpPolicy,
         typename GridArgumentUnit,
         typename ScalarType,
         template<typename,typename...> class Array>
std::shared_ptr<FormFactorEvaluator>
FormFactorEvaluator::createEvaluator(
                                  const Array<ScalarType>& argument_grid,
                                  const Array<ScalarType>& form_factor_values )
{
  // Make sure the argument grid is valid
  testPrecondition( argument_grid.front() >= 0.0 );
  testPrecondition( Utility::Sort::isSortedAscending( argument_grid.begin(),
                                                      argument_grid.end() ) );
  // Make sure the form factor values are valid
  testPrecondition( form_factor_values.back() >= 0.0 );
  testPrecondition( Utility::Sort::isSortedDescending(
                                                  form_factor_values.begin(),
                                                  form_factor_values.end() ) );

  // Create the raw form factor
  std::shared_ptr<Utility::UnitAwareUnivariateDistribution<GridArgumentUnit,void> >
    raw_form_factor( new Utility::UnitAwareTabularDistribution<InterpPolicy,GridArgumentUnit,void>(
                                                        argument_grid,
                                                        form_factor_values ) );

  std::unique_ptr<const MonteCarlo::FormFactor> form_factor(
                         new MonteCarlo::StandardFormFactor<GridArgumentUnit>(
                                                           raw_form_factor ) );

  return std::shared_ptr<FormFactorEvaluator>(
                                      new FormFactorEvaluator( form_factor ) );
}

} // end DataGen namespace

#endif // end DATA_GEN_FORM_FACTOR_EVALUATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end DataGen_FormFactorEvaluator_def.hpp
//---------------------------------------------------------------------------//
