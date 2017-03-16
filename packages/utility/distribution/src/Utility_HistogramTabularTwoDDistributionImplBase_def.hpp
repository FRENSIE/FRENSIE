//---------------------------------------------------------------------------//
//!
//! \file   Utility_HistogramTabularTwoDDistributionImplBase_def.hpp
//! \author Alex Robinson
//! \brief  The histogram tabular two-dimensional dist. helper class def.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_HISTOGRAM_TABULAR_TWO_D_DISTRIBUTION_IMPL_BASE_DEF_HPP
#define UTILITY_HISTOGRAM_TABULAR_TWO_D_DISTRIBUTION_IMPL_BASE_DEF_HPP

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace Utility{

// Evaluate the distribution
template<typename Distribution>
auto UnitAwareHistogramTabularTwoDDistributionImplBase<Distribution>::evaluate(
  const PrimaryIndepQuantity primary_indep_var_value,
  const SecondaryIndepQuantity secondary_indep_var_value ) const -> DepQuantity
{
  return this->evaluateImpl<DepQuantity>( primary_indep_var_value,
                                          secondary_indep_var_value,
                                          &BaseOneDDistributionType::evaluate);
}

// Evaluate the distribution
template<typename Distribution>
inline auto UnitAwareHistogramTabularTwoDDistributionImplBase<Distribution>::correlatedEvaluate(
  const PrimaryIndepQuantity primary_indep_var_value,
  const SecondaryIndepQuantity secondary_indep_var_value,
  const SecondaryIndepQuantity min_secondary_indep_var,
  const SecondaryIndepQuantity max_secondary_indep_var ) const -> DepQuantity
{
  return this->evaluate( primary_indep_var_value,
                         secondary_indep_var_value );
}

// Evaluate the distribution
template<typename Distribution>
inline auto UnitAwareHistogramTabularTwoDDistributionImplBase<Distribution>::evaluateExact(
  const PrimaryIndepQuantity primary_indep_var_value,
  const SecondaryIndepQuantity secondary_indep_var_value ) const -> DepQuantity
{
  return this->evaluate( primary_indep_var_value,
                         secondary_indep_var_value );
}

// Evaluate the secondary conditional PDF
template<typename Distribution>
auto UnitAwareHistogramTabularTwoDDistributionImplBase<Distribution>::evaluateSecondaryConditionalPDF(
                 const PrimaryIndepQuantity primary_indep_var_value,
                 const SecondaryIndepQuantity secondary_indep_var_value ) const
  -> InverseSecondaryIndepQuantity
{
  return this->evaluateImpl<InverseSecondaryIndepQuantity>(
                                      primary_indep_var_value,
                                      secondary_indep_var_value,
                                      &BaseOneDDistributionType::evaluatePDF );
}

// Evaluate the secondary conditional PDF
template<typename Distribution>
inline auto UnitAwareHistogramTabularTwoDDistributionImplBase<Distribution>::correlatedEvaluateSecondaryConditionalPDF(
  const PrimaryIndepQuantity primary_indep_var_value,
  const SecondaryIndepQuantity secondary_indep_var_value,
  const SecondaryIndepQuantity min_secondary_indep_var,
  const SecondaryIndepQuantity max_secondary_indep_var ) const -> InverseSecondaryIndepQuantity
{
  return this->evaluateSecondaryConditionalPDF( primary_indep_var_value,
                                                secondary_indep_var_value );
}

// Evaluate the secondary conditional PDF
template<typename Distribution>
inline auto UnitAwareHistogramTabularTwoDDistributionImplBase<Distribution>::evaluateSecondaryConditionalPDFExact(
                 const PrimaryIndepQuantity primary_indep_var_value,
                 const SecondaryIndepQuantity secondary_indep_var_value ) const
  -> InverseSecondaryIndepQuantity
{
  return this->evaluateSecondaryConditionalPDF( primary_indep_var_value,
                                                secondary_indep_var_value );
}

// Evaluate the distribution using the desired evaluation method
template<typename Distribution>
template<typename ReturnType, typename EvaluationMethod>
inline ReturnType UnitAwareHistogramTabularTwoDDistributionImplBase<Distribution>::evaluateImpl(
                        const PrimaryIndepQuantity primary_indep_var_value,
                        const SecondaryIndepQuantity secondary_indep_var_value,
                        EvaluationMethod evaluate ) const
{
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;

  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  // Check for a primary value outside of the primary grid limits
  if( lower_bin_boundary == upper_bin_boundary )
  {
    if( this->arePrimaryLimitsExtended() )
      return ((*lower_bin_boundary->second).*evaluate)( secondary_indep_var_value );
    else
      return QuantityTraits<ReturnType>::zero();
  }
  else
    return ((*lower_bin_boundary->second).*evaluate)( secondary_indep_var_value );
}

// Sample from the distribution using the desired sampling functor
template<typename Distribution>
template<typename SampleFunctor>
inline auto UnitAwareHistogramTabularTwoDDistributionImplBase<Distribution>::sampleDetailedImpl(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            SampleFunctor sample_functor,
                            unsigned& primary_bin_index ) const
  -> SecondaryIndepQuantity
{
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;
  
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  // Calculate the index of the primary bin boundary that will be used to
  // create the secondary conditional sample
  primary_bin_index = this->calculateBinIndex( lower_bin_boundary );

  if( lower_bin_boundary != upper_bin_boundary )
    return sample_functor( *lower_bin_boundary->second );
  else
  {
    if( this->arePrimaryLimitsExtended() )
      return sample_functor( *lower_bin_boundary->second );
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

// Sample from the distribution using the desired sampling functor
template<typename Distribution>
template<typename SampleFunctor>
inline auto UnitAwareHistogramTabularTwoDDistributionImplBase<Distribution>::sampleImpl(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            SampleFunctor sample_functor ) const
  -> SecondaryIndepQuantity
{
  // Dummy variables
  unsigned dummy_primary_bin_index;

  return this->sampleDetailedImpl( primary_indep_var_value,
                                   sample_functor,
                                   dummy_primary_bin_index );
}

// Return a random sample from the secondary conditional PDF
template<typename Distribution>
auto UnitAwareHistogramTabularTwoDDistributionImplBase<Distribution>::sampleSecondaryConditional(
                     const PrimaryIndepQuantity primary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseOneDDistributionType&)>
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                                             &BaseOneDDistributionType::sample,
                                             std::placeholders::_1 );

  return this->sampleImpl( primary_indep_var_value, sampling_functor );
}

// Return a random sample and record the number of trials
template<typename Distribution>
auto UnitAwareHistogramTabularTwoDDistributionImplBase<Distribution>::sampleSecondaryConditionalAndRecordTrials(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            unsigned& trials ) const -> SecondaryIndepQuantity
{
  // Create the sampling functor
  std::function<SecondaryIndepQuantity(const BaseOneDDistributionType&)>
    sampling_functor = std::bind<SecondaryIndepQuantity>(
                              &BaseOneDDistributionType::sampleAndRecordTrials,
                              std::placeholders::_1,
                              std::ref( trials ) );

  return this->sampleImpl( primary_indep_var_value, sampling_functor );
}

// Return the upper bound of the conditional distribution
template<typename Distribution>
auto UnitAwareHistogramTabularTwoDDistributionImplBase<Distribution>::getUpperBoundOfConditionalIndepVar(
                     const PrimaryIndepQuantity primary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;
  
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  return lower_bin_boundary->second->getUpperBoundOfIndepVar();
}

// Return the lower bound of the conditional distribution
template<typename Distribution>
auto UnitAwareHistogramTabularTwoDDistributionImplBase<Distribution>::getLowerBoundOfConditionalIndepVar(
                     const PrimaryIndepQuantity primary_indep_var_value ) const
  -> SecondaryIndepQuantity
{
  typename DistributionType::const_iterator lower_bin_boundary, upper_bin_boundary;
  
  this->findBinBoundaries( primary_indep_var_value,
                           lower_bin_boundary,
                           upper_bin_boundary );

  return lower_bin_boundary->second->getLowerBoundOfIndepVar();
}

// Test if the distribution is continuous in the primary dimension
template<typename Distribution>
bool UnitAwareHistogramTabularTwoDDistributionImplBase<Distribution>::isPrimaryDimensionContinuous() const
{
  return true;
}
  
} // end Utility namespace

#endif // end UTILITY_HISTOGRAM_TABULAR_TWO_D_DISTRIBUTION_IMPL_BASE_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_HistogramTabularTwoDDistributionImplBase_def.hpp
//---------------------------------------------------------------------------//
