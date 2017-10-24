//---------------------------------------------------------------------------//
//!
//! \file   Utility_InterpolatedFullyTabularTwoDDistribution_def.hpp
//! \author Alex Robinson
//! \brief  The interpolated fully tabular two-dimensional dist. class def.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_INTERPOLATED_FULLY_TABULAR_TWO_D_DISTRIBUTION_DEF_HPP
#define UTILITY_INTERPOLATED_FULLY_TABULAR_TWO_D_DISTRIBUTION_DEF_HPP

// FRENSIE Includes
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Constructor
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::UnitAwareInterpolatedFullyTabularTwoDDistribution(
                          const DistributionType& distribution,
                          const double fuzzy_boundary_tol,
                          const double evaluate_relative_error_tol,
                          const double evaluate_error_tol )
  : ParentType( distribution, fuzzy_boundary_tol )
{
  // Make sure the fuzzy boundary tolerance is valid
  testPrecondition( fuzzy_boundary_tol >= 0.0 );
  testPrecondition( fuzzy_boundary_tol < 1.0 );
  // Make sure the relative error tolerance is valid
  testPrecondition( evaluate_relative_error_tol >= 0.0 );
  testPrecondition( evaluate_relative_error_tol < 1.0 );
  // Make sure the error tolerance is valid
  testPrecondition( evaluate_error_tol >= 0.0 );
  testPrecondition( evaluate_error_tol < 1.0 );

  this->setEvaluationTolerances( fuzzy_boundary_tol,
                                 evaluate_relative_error_tol,
                                 evaluate_error_tol );
}

// Constructor
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<template<typename T, typename... Args> class ArrayA,
         template<typename T, typename... Args> class ArrayB>
UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::UnitAwareInterpolatedFullyTabularTwoDDistribution(
          const ArrayA<PrimaryIndepQuantity>& primary_indep_grid,
          const ArrayB<std::shared_ptr<const UnitAwareTabularOneDDistribution<SecondaryIndependentUnit,DependentUnit> > >& secondary_distributions,
          const double fuzzy_boundary_tol,
          const double evaluate_relative_error_tol,
          const double evaluate_error_tol )
  : ParentType( primary_indep_grid, secondary_distributions, fuzzy_boundary_tol )
{
  // Make sure the fuzzy boundary tolerance is valid
  testPrecondition( fuzzy_boundary_tol >= 0.0 );
  testPrecondition( fuzzy_boundary_tol < 1.0 );
  // Make sure the relative error tolerance is valid
  testPrecondition( evaluate_relative_error_tol >= 0.0 );
  testPrecondition( evaluate_relative_error_tol < 1.0 );
  // Make sure the error tolerance is valid
  testPrecondition( evaluate_error_tol >= 0.0 );
  testPrecondition( evaluate_error_tol < 1.0 );

  this->setEvaluationTolerances( fuzzy_boundary_tol,
                                 evaluate_relative_error_tol,
                                 evaluate_error_tol );
}

// Constructor
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<template<typename T, typename... Args> class ArrayA,
         template<typename T, typename... Args> class ArrayB,
         template<typename T, typename... Args> class SubarrayB,
         template<typename T, typename... Args> class ArrayC,
         template<typename T, typename... Args> class SubarrayC>
UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::UnitAwareInterpolatedFullyTabularTwoDDistribution(
        const ArrayA<PrimaryIndepQuantity>& primary_indep_grid,
        const ArrayB<SubarrayB<SecondaryIndepQuantity> >& secondary_indep_grids,
        const ArrayC<SubarrayC<DepQuantity> >& dependent_values,
        const double fuzzy_boundary_tol,
        const double evaluate_relative_error_tol,
        const double evaluate_error_tol )
{
  // Make sure the fuzzy boundary tolerance is valid
  testPrecondition( fuzzy_boundary_tol >= 0.0 );
  testPrecondition( fuzzy_boundary_tol < 1.0 );
  // Make sure the relative error tolerance is valid
  testPrecondition( evaluate_relative_error_tol >= 0.0 );
  testPrecondition( evaluate_relative_error_tol < 1.0 );
  // Make sure the error tolerance is valid
  testPrecondition( evaluate_error_tol >= 0.0 );
  testPrecondition( evaluate_error_tol < 1.0 );
  // Make sure the grids are valid
  testPrecondition( Sort::isSortedAscending( primary_indep_grid.begin(),
                                             primary_indep_grid.end() ) );
  testPrecondition( primary_indep_grid.size() > 1 );
  testPrecondition( primary_indep_grid.size() == secondary_indep_grids.size());
  testPrecondition( primary_indep_grid.size() == dependent_values.size() );

  // Construct the 2D distribution
  DistributionType distribution( primary_indep_grid.size() );
  
  for( size_t i = 0; i < primary_indep_grid.size(); ++i )
  {
    distribution[i].first = primary_indep_grid[i];
    distribution[i].second.reset(
      new UnitAwareTabularDistribution<typename TwoDInterpPolicy::SecondaryBasePolicy,SecondaryIndependentUnit,DependentUnit>(
                                                      secondary_indep_grids[i],
                                                      dependent_values[i] ) );
  }

  // Set the 2D distribution
  this->setDistribution( distribution );
  this->setEvaluationTolerances( fuzzy_boundary_tol,
                                 evaluate_relative_error_tol,
                                 evaluate_error_tol );
}

//---------------------------------------------------------------------------//
// EVALUATING METHODS
//---------------------------------------------------------------------------//

// Evaluate the secondary conditional CDF
//! \todo Check why the CDFInterpPolicy (changing the z interp to Lin) is necessary
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
double UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateSecondaryConditionalCDF(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value,
            const bool use_direct_eval_method ) const
{
  return this->template evaluateImpl<TwoDInterpPolicy,double>(
                                      primary_indep_var_value,
                                      secondary_indep_var_value,
                                      &BaseOneDDistributionType::evaluateCDF,
                                      use_direct_eval_method,
                                      0.0,
                                      1.0 );
}

// Evaluate the secondary conditional CDF
//! \todo Check why the CDFInterpPolicy (changing the z interp to Lin) is necessary
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
double UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateSecondaryConditionalCDF(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              min_secondary_indep_var_functor,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              max_secondary_indep_var_functor,
            const bool use_direct_eval_method ) const
{
  return this->template evaluateImpl<TwoDInterpPolicy,double>(
                                      primary_indep_var_value,
                                      secondary_indep_var_value,
                                      min_secondary_indep_var_functor,
                                      max_secondary_indep_var_functor,
                                      &BaseOneDDistributionType::evaluateCDF,
                                      use_direct_eval_method,
                                      0.0,
                                      1.0 );
}

//---------------------------------------------------------------------------//
// SAMPLING METHODS
//---------------------------------------------------------------------------//

// Return a random sample from the secondary conditional PDF
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditional(
    const PrimaryIndepQuantity primary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Use this random number to do create the sample functor
  const double random_number =
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseOneDDistributionType&)>
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                             &BaseOneDDistributionType::sampleWithRandomNumber,
                             std::placeholders::_1,
                             random_number );

  return this->sampleImpl( primary_indep_var_value,
                           sampling_functor );
}

// Return a random sample from the secondary conditional PDF
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditional(
            const PrimaryIndepQuantity primary_indep_var_value,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              min_secondary_indep_var_functor,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              max_secondary_indep_var_functor ) const
  -> SecondaryIndepQuantity
{
  // Use this random number to do create the sample functor
  const double random_number =
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseOneDDistributionType&)>
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                             &BaseOneDDistributionType::sampleWithRandomNumber,
                             std::placeholders::_1,
                             random_number );

  return this->sampleImpl( primary_indep_var_value,
                           sampling_functor,
                           min_secondary_indep_var_functor,
                           max_secondary_indep_var_functor );
}

// Return a random sample and record the number of trials
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalAndRecordTrials(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            unsigned& trials ) const
  -> SecondaryIndepQuantity
{
  // Use this random number to do create the sample functor
  const double random_number =
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseOneDDistributionType&)>
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                             &BaseOneDDistributionType::sampleWithRandomNumber,
                             std::placeholders::_1,
                             random_number );

  ++trials;
  return this->sampleImpl( primary_indep_var_value, sampling_functor );
}

// Return a random sample from the secondary conditional PDF at the CDF val
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalWithRandomNumber(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            const double random_number ) const
  -> SecondaryIndepQuantity
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );

  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseOneDDistributionType&)>
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                             &BaseOneDDistributionType::sampleWithRandomNumber,
                             std::placeholders::_1,
                             random_number );

  return this->sampleImpl( primary_indep_var_value, sampling_functor );
}

// Return a random sample from the secondary conditional PDF at the CDF val
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalWithRandomNumber(
            const PrimaryIndepQuantity primary_indep_var_value,
            const double random_number,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              min_secondary_indep_var_functor,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              max_secondary_indep_var_functor ) const
  -> SecondaryIndepQuantity
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );

  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseOneDDistributionType&)>
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                             &BaseOneDDistributionType::sampleWithRandomNumber,
                             std::placeholders::_1,
                             random_number );

  return this->sampleImpl( primary_indep_var_value,
                           sampling_functor,
                           min_secondary_indep_var_functor,
                           max_secondary_indep_var_functor );
}

// Return a random sample from the secondary conditional PDF in the subrange
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalInSubrange(
             const PrimaryIndepQuantity primary_indep_var_value,
             const SecondaryIndepQuantity max_secondary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Make sure the secondary limit is valid
  testPrecondition( max_secondary_indep_var_value >
                    this->getLowerBoundOfConditionalIndepVar( primary_indep_var_value ) );
  
  // Generate a random number
  double random_number =
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleSecondaryConditionalWithRandomNumberInSubrange(
                                               primary_indep_var_value,
                                               random_number,
                                               max_secondary_indep_var_value );
}

// Return a random sample from the secondary conditional PDF in the subrange
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalInSubrange(
            const PrimaryIndepQuantity primary_indep_var_value,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              min_secondary_indep_var_functor,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              max_secondary_indep_var_functor,
            const SecondaryIndepQuantity max_secondary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Make sure the secondary limit is valid
  testPrecondition( max_secondary_indep_var_value >
                    this->getLowerBoundOfConditionalIndepVar( primary_indep_var_value ) );
  
  // Generate a random number
  double random_number =
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleSecondaryConditionalWithRandomNumberInSubrange(
                                    primary_indep_var_value,
                                    random_number,
                                    min_secondary_indep_var_functor,
                                    max_secondary_indep_var_functor,
                                    max_secondary_indep_var_value );
}

// Return a random sample from the secondary conditional PDF in the subrange
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalWithRandomNumberInSubrange(
             const PrimaryIndepQuantity primary_indep_var_value,
             const double random_number,
             const SecondaryIndepQuantity max_secondary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );
  // Make sure the secondary limit is valid
  testPrecondition( max_secondary_indep_var_value >
                    this->getLowerBoundOfConditionalIndepVar( primary_indep_var_value ) );

  // Create the lower bound functor
  std::function<SecondaryIndepQuantity(const PrimaryIndepQuantity)>
    lower_bound_functor = std::bind<SecondaryIndepQuantity>(
                              &ThisType::getLowerBoundOfConditionalIndepVar,
                              std::cref( *this ),
                              std::placeholders::_1 );

  // Create the upper bound functor
  std::function<SecondaryIndepQuantity(const PrimaryIndepQuantity)>
    upper_bound_functor = std::bind<SecondaryIndepQuantity>(
                              &ThisType::getUpperBoundOfConditionalIndepVar,
                              std::cref( *this ),
                              std::placeholders::_1 );

  return this->sampleSecondaryConditionalWithRandomNumberInSubrange(
                                  primary_indep_var_value,
                                  random_number,
                                  lower_bound_functor,
                                  upper_bound_functor,
                                  max_secondary_indep_var_value );
}

// Return a random sample from the secondary conditional PDF in the subrange
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalWithRandomNumberInSubrange(
            const PrimaryIndepQuantity primary_indep_var_value,
            const double random_number,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              min_secondary_indep_var_functor,
            const std::function<SecondaryIndepQuantity(PrimaryIndepQuantity)>&
              max_secondary_indep_var_functor,
            const SecondaryIndepQuantity max_secondary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );
  // Make sure the secondary limit is valid
  testPrecondition( max_secondary_indep_var_value >
                    min_secondary_indep_var_functor( primary_indep_var_value ) );

  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseOneDDistributionType&, const SecondaryIndepQuantity)>
  subrange_sample_functor = std::bind<SecondaryIndepQuantity>(
            &BaseOneDDistributionType::sampleWithRandomNumberInSubrange,
            std::placeholders::_1,
            random_number,
            std::placeholders::_2 );

  // Find the bin boundaries
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;

  this->findBinBoundaries( primary_indep_var_value,
                          lower_bin_boundary,
                          upper_bin_boundary );

  if( lower_bin_boundary != upper_bin_boundary )
  {
    return TwoDSamplePolicy::template sampleInSubrange<TwoDInterpPolicy,PrimaryIndepQuantity,SecondaryIndepQuantity>(
                    subrange_sample_functor,
                    min_secondary_indep_var_functor,
                    max_secondary_indep_var_functor,
                    primary_indep_var_value,
                    lower_bin_boundary,
                    upper_bin_boundary,
                    max_secondary_indep_var_value );
  }
  else
  {
    if( this->arePrimaryLimitsExtended() )
    {
      if( max_secondary_indep_var_value <
          max_secondary_indep_var_functor( primary_indep_var_value ) )
      {
        return subrange_sample_functor( *lower_bin_boundary->second,
                                        max_secondary_indep_var_value );
      }
      else
      {
        return subrange_sample_functor( *lower_bin_boundary->second,
                                        lower_bin_boundary->second->getUpperBoundOfIndepVar() );
      }
    }
    else
    {
      THROW_EXCEPTION( std::logic_error,
                      "Error: Sampling beyond the primary grid boundaries "
                      "cannot be done unless the grid has been extended ("
                      << primary_indep_var_value << " not in ["
                      << this->getLowerBoundOfPrimaryIndepVar() << ","
                      << this->getUpperBoundOfPrimaryIndepVar() << "])!" );
    }
  }
}

// Return a random sample from the secondary conditional PDF and the index
/*! \details The primary_bin_index stores the index of the bin boundary that
 * was used to generate the sample.
 */
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalAndRecordBinIndices(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            unsigned& primary_bin_index,
                            unsigned& secondary_bin_index ) const
  -> SecondaryIndepQuantity
{
  // Dummy variable
  SecondaryIndepQuantity dummy_raw_sample;
  
  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseOneDDistributionType&)>
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                            &BaseOneDDistributionType::sampleAndRecordBinIndex,
                            std::placeholders::_1,
                            std::ref( secondary_bin_index ) );

  return this->sampleDetailedImpl( primary_indep_var_value,
                                   sampling_functor,
                                   dummy_raw_sample,
                                   primary_bin_index );
}

// Return a random sample from the secondary conditional PDF and the index
/*! \details The primary_bin_index stores the index of the bin boundary that
 * was used to generate the raw_sample. The raw_sample is the original sample
 * that was made before the scaling operation was done.
 */
template<typename TwoDInterpPolicy,
         typename TwoDSamplePolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,TwoDSamplePolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalAndRecordBinIndices(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            SecondaryIndepQuantity& raw_sample,
                            unsigned& primary_bin_index,
                            unsigned& secondary_bin_index ) const
  -> SecondaryIndepQuantity
{
  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseOneDDistributionType&)>
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                            &BaseOneDDistributionType::sampleAndRecordBinIndex,
                            std::placeholders::_1,
                            std::ref( secondary_bin_index ) );

  return this->sampleDetailedImpl( primary_indep_var_value,
                                   sampling_functor,
                                   raw_sample,
                                   primary_bin_index );
}

} // end Utility namespace

#endif // UTILITY_INTERPOLATED_FULLY_TABULAR_TWO_D_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_InterpolatedFullyTabularTwoDDistribution_def.hpp
//---------------------------------------------------------------------------//
