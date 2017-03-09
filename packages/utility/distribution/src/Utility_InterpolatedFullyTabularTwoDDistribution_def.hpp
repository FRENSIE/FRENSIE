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
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<template<typename T, typename... Args> class ArrayA,
         template<typename T, typename... Args> class ArrayB,
         template<typename T, typename... Args> class SubarrayB,
         template<typename T, typename... Args> class ArrayC,
         template<typename T, typename... Args> class SubarrayC>
UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::UnitAwareInterpolatedFullyTabularTwoDDistribution(
        const ArrayA<PrimaryIndepQuantity>& primary_indep_grid,
        const ArrayB<SubarrayB<SecondaryIndepQuantity> >& secondary_indep_grids,
        const ArrayC<SubarrayC<DepQuantity> >& dependent_values,
        const double fuzzy_boundary_tol,
        const double evaluate_relative_error_tol )
  : d_relative_error_tol( evaluate_relative_error_tol )
{
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
}

// Evaluate the distribution
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateExact(
                 const PrimaryIndepQuantity primary_indep_var_value,
                 const SecondaryIndepQuantity secondary_indep_var_value ) const
  -> DepQuantity
{
  return this->template evaluateExactImpl<TwoDInterpPolicy,DepQuantity>(
                                          primary_indep_var_value,
                                          secondary_indep_var_value,
                                          &BaseOneDDistributionType::evaluate );
}

// Evaluate the distribution using normalized interpolation
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateNormalized(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity secondary_indep_var_value,
                const SecondaryIndepQuantity min_secondary_indep_var,
                const SecondaryIndepQuantity max_secondary_indep_var ) const
  -> DepQuantity
{
  return this->template evaluateNormalizedImpl<TwoDInterpPolicy,DepQuantity>(
                                          primary_indep_var_value,
                                          secondary_indep_var_value,
                                          min_secondary_indep_var,
                                          max_secondary_indep_var,
                                          &BaseOneDDistributionType::evaluate );
}

// Evaluate the secondary conditional PDF
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateSecondaryConditionalPDFExact(
                 const PrimaryIndepQuantity primary_indep_var_value,
                 const SecondaryIndepQuantity secondary_indep_var_value ) const
  -> InverseSecondaryIndepQuantity
{
  return this->template evaluateExactImpl<TwoDInterpPolicy,InverseSecondaryIndepQuantity>(
                                      primary_indep_var_value,
                                      secondary_indep_var_value,
                                      &BaseOneDDistributionType::evaluatePDF );
}

// Evaluate the secondary conditional PDF using normalized interpolation
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateSecondaryConditionalPDFNormalized(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity secondary_indep_var_value,
                const SecondaryIndepQuantity min_secondary_indep_var,
                const SecondaryIndepQuantity max_secondary_indep_var ) const
  ->  InverseSecondaryIndepQuantity
{
  return this->template evaluateNormalizedImpl<TwoDInterpPolicy,InverseSecondaryIndepQuantity>(
                                    primary_indep_var_value,
                                    secondary_indep_var_value,
                                    min_secondary_indep_var,
                                    max_secondary_indep_var,
                                    &BaseOneDDistributionType::evaluatePDF );
}

// Evaluate the secondary conditional CDF
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
double UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateSecondaryConditionalCDF(
                 const PrimaryIndepQuantity primary_indep_var_value,
                 const SecondaryIndepQuantity secondary_indep_var_value ) const
{
  return this->template evaluateImpl<CDFInterpPolicy,double>(
                                      primary_indep_var_value,
                                      secondary_indep_var_value,
                                      &BaseOneDDistributionType::evaluateCDF,
                                      0.0,
                                      1.0 );
}

// Evaluate the secondary conditional CDF
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
double UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateSecondaryConditionalCDFExact(
                 const PrimaryIndepQuantity primary_indep_var_value,
                 const SecondaryIndepQuantity secondary_indep_var_value ) const
{
  return this->template evaluateExactImpl<CDFInterpPolicy,double>(
                                      primary_indep_var_value,
                                      secondary_indep_var_value,
                                      &BaseOneDDistributionType::evaluateCDF,
                                      0.0,
                                      1.0 );
}

// Evaluate the secondary conditional CDF
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
double UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateSecondaryConditionalCDFNormalized(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity secondary_indep_var_value,
                const SecondaryIndepQuantity min_secondary_indep_var,
                const SecondaryIndepQuantity max_secondary_indep_var ) const
{
  return this->template evaluateNormalizedImpl<TwoDInterpPolicy,double>(
                                      primary_indep_var_value,
                                      secondary_indep_var_value,
                                      min_secondary_indep_var,
                                      max_secondary_indep_var,
                                      &BaseOneDDistributionType::evaluateCDF,
                                      0.0,
                                      1.0 );
}

// Return a random sample from the secondary conditional PDF and the index
/*! \details The primary_bin_index stores the index of the bin boundary that
 * was used to generate the sample.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalAndRecordBinIndices(
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
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalAndRecordBinIndices(
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

// Return a random sample from the secondary conditional PDF at the CDF val
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalWithRandomNumber(
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

// Return a random sample from the secondary conditional PDF in the subrange
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalInSubrange(
             const PrimaryIndepQuantity primary_indep_var_value,
             const SecondaryIndepQuantity max_secondary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Make sure the max secondary independent variable is above the lower
  // bound of the conditional independent variable
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
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalWithRandomNumberInSubrange(
             const PrimaryIndepQuantity primary_indep_var_value,
             const double random_number,
             const SecondaryIndepQuantity max_secondary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Make sure the max secondary independent variable is above the lower
  // bound of the conditional independent variable
  testPrecondition( max_secondary_indep_var_value >
                    this->getLowerBoundOfConditionalIndepVar( primary_indep_var_value ) );
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );

  SecondaryIndepQuantity intermediate_grid_upper_bound =
    this->getUpperBoundOfConditionalIndepVar( primary_indep_var_value );

  // Generate a sample in the subrange
  if( max_secondary_indep_var_value < intermediate_grid_upper_bound )
  {
    // Find the bin boundaries
    typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;

    this->findBinBoundaries( primary_indep_var_value,
                             lower_bin_boundary,
                             upper_bin_boundary );

    typename DistributionType::const_iterator sampled_bin_boundary =
      this->sampleBinBoundary( primary_indep_var_value,
                               lower_bin_boundary,
                               upper_bin_boundary );

    // Calculate the limit on the sampled bin boundary
    typename QuantityTraits<SecondaryIndepQuantity>::RawType grid_length =
      TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseGridLength(
                     sampled_bin_boundary->second->getLowerBoundOfIndepVar(),
                     sampled_bin_boundary->second->getUpperBoundOfIndepVar() );

    SecondaryIndepQuantity intermediate_grid_lower_bound =
    this->getLowerBoundOfConditionalIndepVar( primary_indep_var_value );

    typename QuantityTraits<SecondaryIndepQuantity>::RawType
      intermediate_grid_length =
      TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseGridLength(
                                               intermediate_grid_lower_bound,
                                               intermediate_grid_upper_bound );

    typename QuantityTraits<SecondaryIndepQuantity>::RawType eta =
      TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseIndepVar(
                                                 max_secondary_indep_var_value,
                                                 intermediate_grid_lower_bound,
                                                 intermediate_grid_length );

    SecondaryIndepQuantity max_secondary_indep_var_value_bin_bound =
      TwoDInterpPolicy::SecondaryBasePolicy::calculateIndepVar(
                       eta,
                       sampled_bin_boundary->second->getLowerBoundOfIndepVar(),
                       grid_length );

    // Sample in the bin's subrange
    SecondaryIndepQuantity raw_sample =
      sampled_bin_boundary->second->sampleWithRandomNumberInSubrange(
                                     random_number,
                                     max_secondary_indep_var_value_bin_bound );

    // Scale the sample
    eta = TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseIndepVar(
                       raw_sample,
                       sampled_bin_boundary->second->getLowerBoundOfIndepVar(),
                       grid_length );

    return TwoDInterpPolicy::SecondaryBasePolicy::calculateIndepVar(
                                                 eta,
                                                 intermediate_grid_lower_bound,
                                                 intermediate_grid_length );
  }
  // Generate a sample in the full range
  else
  {
    return this->sampleSecondaryConditionalWithRandomNumber(
                                      primary_indep_var_value, random_number );
  }
}

// Return a random sample from the secondary conditional PDF
/*! \details A sample is made using a correlated sampling technique.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalExact(
                     const PrimaryIndepQuantity primary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Use this random number to do create the correlated sample
  const double random_number =
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleSecondaryConditionalExactWithRandomNumber(
                                      primary_indep_var_value, random_number );
}

// Return a random sample from the secondary conditional PDF at the CDF val
/*! \details A sample is made using a correlated sampling technique.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalExactWithRandomNumber(
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

  return this->sampleExactImpl( primary_indep_var_value, sampling_functor );
}

// Return a random sample from the secondary conditional PDF in the subrange
/*! \details A sample is made using a correlated sampling technique.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalExactInSubrange(
             const PrimaryIndepQuantity primary_indep_var_value,
             const SecondaryIndepQuantity max_secondary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Use this random number to do create the correlated sample
  const double random_number =
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleSecondaryConditionalExactWithRandomNumberInSubrange(
                                               primary_indep_var_value,
                                               random_number,
                                               max_secondary_indep_var_value );
}

// Return a random sample from the secondary conditional PDF in the subrange
/*! \details A sample is made using a correlated sampling technique.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalExactWithRandomNumberInSubrange(
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

  std::function<SecondaryIndepQuantity(const BaseOneDDistributionType&)>
      sampling_functor;

  // Check if the max_secondary_indep_var_value is greater than the max indep value at the energy
  if ( max_secondary_indep_var_value >
       this->getUpperBoundOfConditionalIndepVar( primary_indep_var_value ) )
  {
    // Create the sampling functor
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                             &BaseOneDDistributionType::sampleWithRandomNumberInSubrange,
                             std::placeholders::_1,
                             random_number,
                             this->getUpperBoundOfConditionalIndepVar( primary_indep_var_value ) );
  }
  else
  {
    // Create the sampling functor
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                             &BaseOneDDistributionType::sampleWithRandomNumberInSubrange,
                             std::placeholders::_1,
                             random_number,
                             max_secondary_indep_var_value );
  }

  return this->sampleExactImpl( primary_indep_var_value, sampling_functor );
}

// Return a random sample from the secondary conditional PDF using a normalized interpolation
/*! \details A normalized correlated sampling procedure is used. If the primary
 * value provided is outside of the primary grid limits the appropriate limiting
 * secondary distribution will be used to create the sample. The alternative
 * to this behavior is to throw an exception unless the distribution has
 * been extended by calling the extendBeyondPrimaryIndepLimits method. Since
 * this is a performance critical method we decided against this behavior.
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
auto UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::sampleSecondaryConditionalNormalized(
        const PrimaryIndepQuantity primary_indep_var_value,
        const SecondaryIndepQuantity min_secondary_indep_var,
        const SecondaryIndepQuantity max_secondary_indep_var ) const
  -> SecondaryIndepQuantity
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseOneDDistributionType&)>
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                             &BaseOneDDistributionType::sampleWithRandomNumber,
                             std::placeholders::_1,
                             random_number );

  return this->sampleNormalizedImpl( primary_indep_var_value,
                                     min_secondary_indep_var,
                                     max_secondary_indep_var,
                                     sampling_functor );
}

// Evaluate the distribution using the desired evaluation method
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<typename LocalTwoDInterpPolicy,
         typename ReturnType,
         typename EvaluationMethod>
inline ReturnType UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateExactImpl(
                        const PrimaryIndepQuantity primary_indep_var_value,
                        const SecondaryIndepQuantity secondary_indep_var_value,
                        EvaluationMethod evaluate,
                        const ReturnType below_lower_bound_return,
                        const ReturnType above_upper_bound_return ) const
{
  // Find the bin boundaries
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;

  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  // Check for a primary value outside of the primary grid limits
  if( lower_bin_boundary == upper_bin_boundary )
  {
    if( this->arePrimaryLimitsExtended() )
      return ((*lower_bin_boundary->second).*evaluate)(secondary_indep_var_value);
    else 
      return QuantityTraits<ReturnType>::zero();
  }
  else if( lower_bin_boundary->first == primary_indep_var_value )
  {
    return ((*lower_bin_boundary->second).*evaluate)(secondary_indep_var_value);
  }
  else if( upper_bin_boundary->first == primary_indep_var_value )
  {
    return ((*upper_bin_boundary->second).*evaluate)(secondary_indep_var_value);
  }
  else
  {
    // Get the lower secondary indep grid limits at the primary value
    SecondaryIndepQuantity lower_sec_indep_var_bound =
      TwoDInterpPolicy::ZXInterpPolicy::interpolate(
                      lower_bin_boundary->first,
                      upper_bin_boundary->first,
                      primary_indep_var_value,
                      lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                      upper_bin_boundary->second->getLowerBoundOfIndepVar() );

    // Get the upper secondary indep grid limits at the primary value
    SecondaryIndepQuantity upper_sec_indep_var_bound =
      TwoDInterpPolicy::ZXInterpPolicy::interpolate(
                      lower_bin_boundary->first,
                      upper_bin_boundary->first,
                      primary_indep_var_value,
                      lower_bin_boundary->second->getUpperBoundOfIndepVar(),
                      upper_bin_boundary->second->getUpperBoundOfIndepVar() );

    // Check for a seconday indep value outside of the secondary indep grid limits
    if ( secondary_indep_var_value < lower_sec_indep_var_bound )
      return below_lower_bound_return;
    else if ( secondary_indep_var_value > upper_sec_indep_var_bound )
      return above_upper_bound_return;
    if ( secondary_indep_var_value == lower_sec_indep_var_bound )
    {
      return TwoDInterpPolicy::ZXInterpPolicy::interpolate(
                lower_bin_boundary->first,
                upper_bin_boundary->first,
                primary_indep_var_value,
                ((*lower_bin_boundary->second).*evaluate)(lower_bin_boundary->second->getLowerBoundOfIndepVar()),
                ((*upper_bin_boundary->second).*evaluate)(upper_bin_boundary->second->getLowerBoundOfIndepVar()) );
    }
    else if ( secondary_indep_var_value == upper_sec_indep_var_bound )
    {
      return TwoDInterpPolicy::ZXInterpPolicy::interpolate(
                lower_bin_boundary->first,
                upper_bin_boundary->first,
                primary_indep_var_value,
                ((*lower_bin_boundary->second).*evaluate)(lower_bin_boundary->second->getUpperBoundOfIndepVar()),
                ((*upper_bin_boundary->second).*evaluate)(upper_bin_boundary->second->getUpperBoundOfIndepVar()) );
    }

    // Evaluate the cdf at the upper and lower bin boundaries
    double lower_bin_eval =
      ((*lower_bin_boundary->second).*&BaseOneDDistributionType::evaluateCDF)( secondary_indep_var_value );
     double upper_bin_eval =
      ((*upper_bin_boundary->second).*&BaseOneDDistributionType::evaluateCDF)( secondary_indep_var_value );

    // Get the lower and upper boundaries of the evaluated cdf
    double lower_cdf_bound, upper_cdf_bound;
    if ( lower_bin_eval <= upper_bin_eval )
    {
      lower_cdf_bound = lower_bin_eval;
      upper_cdf_bound = upper_bin_eval;
    }
    else
    {
      lower_cdf_bound = upper_bin_eval;
      upper_cdf_bound = lower_bin_eval;
    }

  // Set the tol
  double rel_error = 1.0;

  SecondaryIndepQuantity lower_bin_sample, upper_bin_sample;

  // Refine the estimated cdf value until it meet the tolerance
  while ( rel_error > d_relative_error_tol )
  {
    // Estimate the cdf as the midpoint of the lower and upper boundaries
    double estimated_cdf = 0.5*( lower_cdf_bound + upper_cdf_bound );

    // Get the sampled values at the upper and lower bin for the estimated_cdf
    lower_bin_sample =
      ((*lower_bin_boundary->second).*&BaseOneDDistributionType::sampleWithRandomNumber)( estimated_cdf );
    upper_bin_sample =
      ((*upper_bin_boundary->second).*&BaseOneDDistributionType::sampleWithRandomNumber)( estimated_cdf );

    // Interpolate using the templated TwoDInterpPolicy::ZXInterpPolicy
    SecondaryIndepQuantity est_secondary_indep_var_value =
      TwoDInterpPolicy::ZXInterpPolicy::interpolate( lower_bin_boundary->first,
                                                     upper_bin_boundary->first,
                                                     primary_indep_var_value,
                                                     lower_bin_sample,
                                                     upper_bin_sample );

    if ( secondary_indep_var_value == est_secondary_indep_var_value )
        break;

    // Update the estimated_cdf estimate
    if ( est_secondary_indep_var_value < secondary_indep_var_value )
    {
      // Calculate the relative error between the secondary_indep_var_value and the estimate
      rel_error = 2.0*( secondary_indep_var_value - est_secondary_indep_var_value )/
                                                    secondary_indep_var_value;

      // If tolerance is met exit loop
      if ( rel_error <= d_relative_error_tol )
        break;

      // Old estimated_cdf estimate is new lower cdf boundary
      lower_cdf_bound = estimated_cdf;
    }
    else
    {
      // Calculate the relative error between the secondary_indep_var_value and the estimate
      rel_error = 2.0*( est_secondary_indep_var_value - secondary_indep_var_value )/
                                                    secondary_indep_var_value;

      // If tolerance is met exit loop
      if ( rel_error <= d_relative_error_tol )
        break;

      // Old estimated_cdf estimate is new upper cdf boundary
      upper_cdf_bound =estimated_cdf;
    }
  }

  return TwoDInterpPolicy::ZXInterpPolicy::interpolate(
                lower_bin_boundary->first,
                upper_bin_boundary->first,
                primary_indep_var_value,
                ((*lower_bin_boundary->second).*evaluate)(lower_bin_sample),
                ((*upper_bin_boundary->second).*evaluate)(upper_bin_sample) );
  }
}

// Evaluate the distribution using the desired evaluation method
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
template<typename LocalTwoDInterpPolicy,
         typename ReturnType,
         typename EvaluationMethod>
inline ReturnType UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit>::evaluateNormalizedImpl(
                        const PrimaryIndepQuantity primary_indep_var_value,
                        const SecondaryIndepQuantity secondary_indep_var_value,
                        const SecondaryIndepQuantity min_secondary_indep_var,
                        const SecondaryIndepQuantity max_secondary_indep_var,
                        EvaluationMethod evaluate,
                        const ReturnType below_lower_bound_return,
                        const ReturnType above_upper_bound_return ) const
{
  // Find the bin boundaries
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;

  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  // Check for a primary value outside of the primary grid limits
  if( lower_bin_boundary == upper_bin_boundary )
  {
    if( this->arePrimaryLimitsExtended() )
      return ((*lower_bin_boundary->second).*evaluate)(secondary_indep_var_value);
    else 
      return QuantityTraits<ReturnType>::zero();
  }
  else if( lower_bin_boundary->first == primary_indep_var_value )
  {
    return ((*lower_bin_boundary->second).*evaluate)(secondary_indep_var_value);
  }
  else if( upper_bin_boundary->first == primary_indep_var_value )
  {
    return ((*upper_bin_boundary->second).*evaluate)(secondary_indep_var_value);
  }
  else
  {
    // Get the lower secondary indep grid limits at the primary value
    SecondaryIndepQuantity lower_sec_indep_var_bound =
      TwoDInterpPolicy::ZXInterpPolicy::interpolate(
                      lower_bin_boundary->first,
                      upper_bin_boundary->first,
                      primary_indep_var_value,
                      lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                      upper_bin_boundary->second->getLowerBoundOfIndepVar() );

    // Get the upper secondary indep grid limits at the primary value
    SecondaryIndepQuantity upper_sec_indep_var_bound =
      TwoDInterpPolicy::ZXInterpPolicy::interpolate(
                      lower_bin_boundary->first,
                      upper_bin_boundary->first,
                      primary_indep_var_value,
                      lower_bin_boundary->second->getUpperBoundOfIndepVar(),
                      upper_bin_boundary->second->getUpperBoundOfIndepVar() );

std::cout << "lower sec bound:" << std::setprecision(20) << lower_sec_indep_var_bound
          << "\tupper sec bound:" << std::setprecision(20) << upper_sec_indep_var_bound << std::endl;

    // Check for a seconday indep value outside of the secondary indep grid limits
    if ( secondary_indep_var_value < lower_sec_indep_var_bound )
      return below_lower_bound_return;
    else if ( secondary_indep_var_value > upper_sec_indep_var_bound )
      return above_upper_bound_return;
    if ( secondary_indep_var_value == lower_sec_indep_var_bound )
    {
std::cout << "lower min eval:" << std::setprecision(20) << ((*lower_bin_boundary->second).*evaluate)(lower_bin_boundary->second->getLowerBoundOfIndepVar())
          << "\tupper min eval:" << std::setprecision(20) << ((*upper_bin_boundary->second).*evaluate)(upper_bin_boundary->second->getLowerBoundOfIndepVar()) << std::endl;

      return TwoDInterpPolicy::ZXInterpPolicy::interpolate(
                lower_bin_boundary->first,
                upper_bin_boundary->first,
                primary_indep_var_value,
                ((*lower_bin_boundary->second).*evaluate)(lower_bin_boundary->second->getLowerBoundOfIndepVar()),
                ((*upper_bin_boundary->second).*evaluate)(upper_bin_boundary->second->getLowerBoundOfIndepVar()) );
    }
    else if ( secondary_indep_var_value == upper_sec_indep_var_bound )
    {
std::cout << "lower max eval:" << std::setprecision(20) << ((*lower_bin_boundary->second).*evaluate)(lower_bin_boundary->second->getUpperBoundOfIndepVar())
          << "\tupper max eval:" << std::setprecision(20) << ((*upper_bin_boundary->second).*evaluate)(upper_bin_boundary->second->getUpperBoundOfIndepVar()) << std::endl;

      return TwoDInterpPolicy::ZXInterpPolicy::interpolate(
                lower_bin_boundary->first,
                upper_bin_boundary->first,
                primary_indep_var_value,
                ((*lower_bin_boundary->second).*evaluate)(lower_bin_boundary->second->getUpperBoundOfIndepVar()),
                ((*upper_bin_boundary->second).*evaluate)(upper_bin_boundary->second->getUpperBoundOfIndepVar()) );
    }

  // Get the min indep value at the upper and lower bin boundary
  SecondaryIndepQuantity lower_bin_indep_min = 
    lower_bin_boundary->second->getLowerBoundOfIndepVar();
  SecondaryIndepQuantity upper_bin_indep_min = 
    upper_bin_boundary->second->getLowerBoundOfIndepVar();

  // Get the range of the indep value at the upper and lower bin boundary
  SecondaryIndepQuantity lower_bin_indep_range =
    lower_bin_boundary->second->getUpperBoundOfIndepVar() - lower_bin_indep_min;
  SecondaryIndepQuantity upper_bin_indep_range =
    upper_bin_boundary->second->getUpperBoundOfIndepVar() - upper_bin_indep_min;
  SecondaryIndepQuantity secondary_indep_range =
                            max_secondary_indep_var - min_secondary_indep_var;

  // Normalize the sec_indep_var_value
  double norm_sec_indep_var_value =
    ( secondary_indep_var_value - min_secondary_indep_var )/secondary_indep_range;

  // Get the sec_indep_var_value normalized to the upper and lower bin boundaries
  SecondaryIndepQuantity lower_sec_indep_var_value =
    norm_sec_indep_var_value*lower_bin_indep_range + lower_bin_indep_min;

  SecondaryIndepQuantity upper_sec_indep_var_value =
    norm_sec_indep_var_value*upper_bin_indep_range + upper_bin_indep_min;

    // Evaluate the cdf at the upper and lower bin boundaries
    double lower_bin_eval =
      ((*lower_bin_boundary->second).*&BaseOneDDistributionType::evaluateCDF)( lower_sec_indep_var_value );
     double upper_bin_eval =
      ((*upper_bin_boundary->second).*&BaseOneDDistributionType::evaluateCDF)( upper_sec_indep_var_value );

    // Get the lower and upper boundaries of the evaluated cdf
    double lower_cdf_bound, upper_cdf_bound ;
    if ( lower_bin_eval <= upper_bin_eval )
    {
      lower_cdf_bound = lower_bin_eval;
      upper_cdf_bound = upper_bin_eval;
    }
    else
    {
      lower_cdf_bound = upper_bin_eval;
      upper_cdf_bound = lower_bin_eval;
    }

std::cout << "lower bound:" << std::setprecision(20) << lower_cdf_bound
          << "\tupper bound:" << std::setprecision(20) << upper_cdf_bound << std::endl;

  // Set the tol
  double rel_error = 1.0;
  int i = 0;

  SecondaryIndepQuantity lower_bin_sample, upper_bin_sample;

  // Refine the estimated cdf value until it meet the tolerance
  while ( rel_error > d_relative_error_tol )
  {
    // Estimate the cdf as the midpoint of the lower and upper boundaries
    double estimated_cdf = 0.5*( lower_cdf_bound + upper_cdf_bound );

    // Get the sampled values at the upper and lower bin for the estimated_cdf
    lower_bin_sample =
      ((*lower_bin_boundary->second).*&BaseOneDDistributionType::sampleWithRandomNumber)( estimated_cdf );
    upper_bin_sample =
      ((*upper_bin_boundary->second).*&BaseOneDDistributionType::sampleWithRandomNumber)( estimated_cdf );

    // Normalized the Sampled values
    double lower_bin_norm_sample =
        ( lower_bin_sample - lower_bin_indep_min )/lower_bin_indep_range;
    double upper_bin_norm_sample =
        ( upper_bin_sample - upper_bin_indep_min )/upper_bin_indep_range;

    // Interpolate using the templated TwoDInterpPolicy::ZXInterpPolicy
    double est_norm_secondary_indep_var_value =
      TwoDInterpPolicy::ZXInterpPolicy::interpolate( lower_bin_boundary->first,
                                                     upper_bin_boundary->first,
                                                     primary_indep_var_value,
                                                     lower_bin_norm_sample,
                                                     upper_bin_norm_sample );

    // Un-normalized the interpolated estimate secondary indep value
    SecondaryIndepQuantity
        est_secondary_indep_var_value = min_secondary_indep_var +
        secondary_indep_range*est_norm_secondary_indep_var_value;

std::cout << std::setprecision(20) << estimated_cdf << ": (" << lower_bin_norm_sample << ") and (" << upper_bin_norm_sample << ") -> (" << est_norm_secondary_indep_var_value << ") -> (" << est_secondary_indep_var_value << ")" << std::endl;

    if ( secondary_indep_var_value == est_secondary_indep_var_value )
        break;

    // Update the estimated_cdf estimate
    if ( est_secondary_indep_var_value < secondary_indep_var_value )
    {
      // Calculate the relative error between the secondary_indep_var_value and the estimate
      rel_error = ( secondary_indep_var_value - est_secondary_indep_var_value )/
                                                    secondary_indep_var_value;

      // If tolerance is met exit loop
      if ( rel_error <= d_relative_error_tol )
        break;

      // Old estimated_cdf estimate is new lower cdf boundary
      lower_cdf_bound = estimated_cdf;
    }
    else
    {
      // Calculate the relative error between the secondary_indep_var_value and the estimate
      rel_error = ( est_secondary_indep_var_value - secondary_indep_var_value )/
                                                    secondary_indep_var_value;

      // If tolerance is met exit loop
      if ( rel_error <= d_relative_error_tol )
        break;

      // Old estimated_cdf estimate is new upper cdf boundary
      upper_cdf_bound =estimated_cdf;
    }

i++;
std::cout << i << ":(" << std::setprecision(20) << estimated_cdf << "): (" << est_secondary_indep_var_value << ") - (" << secondary_indep_var_value << ") = " << rel_error << std::endl;
if ( i > 50 )
    break;
  }

  ReturnType answer =
    TwoDInterpPolicy::ZXInterpPolicy::interpolate(
                lower_bin_boundary->first,
                upper_bin_boundary->first,
                primary_indep_var_value,
                ((*lower_bin_boundary->second).*evaluate)(lower_bin_sample),
                ((*upper_bin_boundary->second).*evaluate)(upper_bin_sample) );

std::cout << "Answer = " << std::setprecision(20) << answer << std::endl;

  return answer;
  }
}
} // end Utility namespace

#endif // UTILITY_INTERPOLATED_FULLY_TABULAR_TWO_D_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_InterpolatedFullyTabularTwoDDistribution_def.hpp
//---------------------------------------------------------------------------//
