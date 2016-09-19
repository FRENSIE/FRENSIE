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
       const ArrayC<SubarrayC<DepQuantity> >& dependent_values )
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
  
  // Find the bin boundaries
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;
  
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  if( lower_bin_boundary != upper_bin_boundary )
  {
    return TwoDInterpPolicy::calculateIntermediateGridLimit(
         lower_bin_boundary->first,
         upper_bin_boundary->first,
         primary_indep_var_value,
         lower_bin_boundary->second->sampleWithRandomNumber( random_number ),
         upper_bin_boundary->second->sampleWithRandomNumber( random_number ) );
  }
  else
  {
    if( this->arePrimaryLimitsExtended() )
      return lower_bin_boundary->second->sampleWithRandomNumber(random_number);
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

    if( lower_bin_boundary != upper_bin_boundary )
    {
      // Calculate the limits on the bin boundaries
      typename QuantityTraits<SecondaryIndepQuantity>::RawType L0 =
        TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseGridLength(
                       lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                       lower_bin_boundary->second->getUpperBoundOfIndepVar() );

      typename QuantityTraits<SecondaryIndepQuantity>::RawType L1 =
        TwoDInterpPolicy::SecondaryBasePolicy::calculateUnitBaseGridLength(
                       upper_bin_boundary->second->getLowerBoundOfIndepVar(),
                       upper_bin_boundary->second->getUpperBoundOfIndepVar() );

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

      SecondaryIndepQuantity max_secondary_indep_var_value_0 =
        TwoDInterpPolicy::SecondaryBasePolicy::calculateIndepVar(
                         eta,
                         lower_bin_boundary->second->getLowerBoundOfIndepVar(),
                         L0 );

      SecondaryIndepQuantity max_secondary_indep_var_value_1 =
        TwoDInterpPolicy::SecondaryBasePolicy::calculateIndepVar(
                         eta,
                         upper_bin_boundary->second->getLowerBoundOfIndepVar(),
                         L1 );
      
      return TwoDInterpPolicy::calculateIntermediateGridLimit(
         lower_bin_boundary->first,
         upper_bin_boundary->first,
         primary_indep_var_value,
         lower_bin_boundary->second->sampleWithRandomNumberInSubrange( random_number, max_secondary_indep_var_value_0 ),
         upper_bin_boundary->second->sampleWithRandomNumberInSubrange( random_number, max_secondary_indep_var_value_1 ) );
    }
    else
    {
      if( this->arePrimaryLimitsExtended() )
        return lower_bin_boundary->second->sampleWithRandomNumberInSubrange( random_number, max_secondary_indep_var_value );
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
  // Generate a sample in the full range
  else
  {
    return this->sampleSecondaryConditionalExactWithRandomNumber(
                                      primary_indep_var_value, random_number );
  }
}
  
} // end Utility namespace

#endif // UTILITY_INTERPOLATED_FULLY_TABULAR_TWO_D_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_InterpolatedFullyTabularTwoDDistribution_def.hpp
//---------------------------------------------------------------------------//
