//---------------------------------------------------------------------------//
//!
//! \file   Utility_HybridElasticDistribution_def.hpp
//! \author Luke Kersting
//! \brief  Hybrid elastic distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_HYBRID_ELASTIC_DISTRIBUTION_DEF_HPP
#define UTILITY_HYBRID_ELASTIC_DISTRIBUTION_DEF_HPP

// Std Includes
#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstdlib>

// FRENSIE Includes
#include "Utility_DataProcessor.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ArrayString.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_ElasticElectronTraits.hpp"

namespace Utility{

// Explicit instantiation (extern declaration)
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareHybridElasticDistribution<LinLin,void,void> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareHybridElasticDistribution<LogLin,void,void> );

// Default constructor
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::UnitAwareHybridElasticDistribution()
{ /* ... */ }

// Basic constructor (potentially dangerous)
/*! \details The independent values are assumed to be sorted (lowest to
 * highest). If cdf values are provided a pdf will be calculated. Because
 * information is lost when converting from a pdf to a cdf, only a first order
 * approximation of the pdf will be calculated. Evaluate the resulting
 * distribution with caution (there will be no difference when sampling from
 * the distribution)!
 */
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::UnitAwareHybridElasticDistribution(
                    const Teuchos::Array<double>& independent_cutoff_values,
                    const Teuchos::Array<double>& dependent_cutoff_values,
                    const Teuchos::Array<double>& independent_discrete_values,
                    const Teuchos::Array<double>& dependent_discrete_values,
                    const double& cutoff_angle_cosine,
                    const double& cutoff_cross_section_ratio )
  : d_cutoff_distribution( independent_cutoff_values.size() ),
    d_discrete_distribution( independent_discrete_values.size() ),
    d_cutoff_mu( cutoff_angle_cosine ),
    d_cutoff_cross_section_ratio( cutoff_cross_section_ratio ),
    d_scaling_parameter( 1.0/( 1.0 - cutoff_cross_section_ratio ) ),
    d_discrete_norm_constant( DNQT::zero() ),
    d_cutoff_norm_constant( DNQT::zero() ),
    d_max_cdf( UCQT::zero() )
{
  // Make sure there is at lease one bin in the cutoff distribution
  testPrecondition( independent_cutoff_values.size() > 1 );
  testPrecondition( dependent_cutoff_values.size() ==
                    independent_cutoff_values.size() );
  testPrecondition( dependent_discrete_values.size() ==
                    independent_discrete_values.size() );
  // Make sure that the bins are sorted
  testPrecondition( Sort::isSortedAscending( independent_cutoff_values.begin(),
                                             independent_cutoff_values.end() ) );
  testPrecondition( Sort::isSortedAscending( independent_discrete_values.begin(),
                                             independent_discrete_values.end() ) );
  // Make sure that the independent_values have the proper range
  testPrecondition( independent_cutoff_values.front() == -1.0 );
  testPrecondition( independent_cutoff_values.back() <= 0.999999 );
  testPrecondition( independent_discrete_values.front() >= cutoff_angle_cosine );
  testPrecondition( independent_discrete_values.back() < 1.0 );

  this->initializeDistributionsFromRawData( independent_cutoff_values,
                                            dependent_cutoff_values,
                                            independent_discrete_values,
                                            dependent_discrete_values );
}


// Constructor
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
template<typename InputIndepQuantity, typename InputDepQuantity>
UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::UnitAwareHybridElasticDistribution(
        const Teuchos::Array<InputIndepQuantity>& independent_cutoff_values,
        const Teuchos::Array<InputDepQuantity>& dependent_cutoff_values,
        const Teuchos::Array<InputIndepQuantity>& independent_discrete_values,
        const Teuchos::Array<InputDepQuantity>& dependent_discrete_values,
        const InputIndepQuantity& cutoff_angle_cosine,
        const double& cutoff_cross_section_ratio )
  : d_cutoff_distribution( independent_cutoff_values.size() ),
    d_discrete_distribution( independent_discrete_values.size() ),
    d_cutoff_mu( cutoff_angle_cosine*QuantityTraits<InputDepQuantity>::one() ),
    d_cutoff_cross_section_ratio( cutoff_cross_section_ratio ),
    d_discrete_norm_constant( DNQT::zero() ),
    d_cutoff_norm_constant( DNQT::zero() ),
    d_max_cdf( UCQT::zero() )
{
  // Make sure there is at lease one bin in the cutoff distribution
  testPrecondition( independent_cutoff_values.size() > 1 );
  testPrecondition( dependent_cutoff_values.size() ==
                    independent_cutoff_values.size() );
  testPrecondition( dependent_discrete_values.size() ==
                    independent_discrete_values.size() );
  // Make sure that the bins are sorted
  testPrecondition( Sort::isSortedAscending( independent_cutoff_values.begin(),
                                             independent_cutoff_values.end() ) );
  testPrecondition( Sort::isSortedAscending( independent_discrete_values.begin(),
                                             independent_discrete_values.end() ) );
  // Make sure that the independent_values have the proper range
  testPrecondition( independent_cutoff_values.front() == -1.0 );
  testPrecondition( independent_cutoff_values.back() <= 0.999999 );
  testPrecondition( independent_discrete_values.front() >= cutoff_angle_cosine );
  testPrecondition( independent_discrete_values.back() < 1.0 );

  this->initializeCutoffDistribution( independent_cutoff_values,
                                      dependent_cutoff_values );
  this->initializeDiscreteDistribution( independent_discrete_values,
                                        dependent_discrete_values );
}

// Copy constructor
/*! \details Just like boost::units::quantity objects, the unit-aware
 * distribution can be explicitly cast to a distribution with compatible
 * units. If the units are not compatible, this function will not compile. Note
 * that this allows distributions to be scaled safely (unit conversions
 * are completely taken care of by boost::units)!
 */
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
template<typename InputIndepUnit, typename InputDepUnit>
UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::UnitAwareHybridElasticDistribution(
 const UnitAwareHybridElasticDistribution<InterpolationPolicy,InputIndepUnit,InputDepUnit>& dist_instance )
  : d_cutoff_distribution(),
    d_discrete_distribution(),
    d_cutoff_mu(),
    d_cutoff_cross_section_ratio(),
    d_scaling_parameter(),
    d_discrete_norm_constant(),
    d_cutoff_norm_constant(),
    d_max_cdf()
{
  // Make sure the distribution is valid
  testPrecondition( dist_instance.d_cutoff_distribution.size() > 0 );
  testPrecondition( dist_instance.d_discrete_distribution.size() > 0 );

  // Assign unitless member data
  d_cutoff_mu = dist_instance.d_cutoff_mu;
  d_cutoff_cross_section_ratio = dist_instance.d_cutoff_cross_section_ratio;
  d_scaling_parameter = dist_instance.d_scaling_parameter;

  typedef typename UnitAwareHybridElasticDistribution<InterpolationPolicy,InputIndepUnit,InputDepUnit>::IndepQuantity InputIndepQuantity;

  typedef typename UnitAwareHybridElasticDistribution<InterpolationPolicy,InputIndepUnit,InputDepUnit>::DepQuantity InputDepQuantity;

  // Reconstruct the original cutoff input distribution
  Teuchos::Array<InputIndepQuantity> input_indep_cutoff_values;
  Teuchos::Array<InputDepQuantity> input_dep_cutoff_values;
  Teuchos::Array<InputIndepQuantity> input_indep_discrete_values;
  Teuchos::Array<InputDepQuantity> input_dep_discrete_values;

  dist_instance.reconstructOriginalDistributions( input_indep_cutoff_values,
                                                  input_dep_cutoff_values,
                                                  input_indep_discrete_values,
                                                  input_dep_discrete_values );

  this->initializeCutoffDistribution( input_indep_cutoff_values,
                                      input_dep_cutoff_values );

  this->initializeDiscreteDistribution( input_indep_discrete_values,
                                        input_dep_discrete_values );
}

// Copy constructor (copying from unitless distribution only)
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::UnitAwareHybridElasticDistribution( const UnitAwareHybridElasticDistribution<InterpolationPolicy,void,void>& unitless_dist_instance, int )
  : d_cutoff_distribution(),
    d_discrete_distribution(),
    d_cutoff_mu(),
    d_cutoff_cross_section_ratio(),
    d_scaling_parameter(),
    d_discrete_norm_constant(),
    d_cutoff_norm_constant(),
    d_max_cdf()
{
  // Make sure the distribution is valid
  testPrecondition( unitless_dist_instance.d_cutoff_distribution.size() > 0 );
  testPrecondition( unitless_dist_instance.d_discrete_distribution.size() > 0 );

  // Assign unitless member data
  d_cutoff_mu = unitless_dist_instance.d_cutoff_mu;
  d_cutoff_cross_section_ratio =
                        unitless_dist_instance.d_cutoff_cross_section_ratio;
  d_scaling_parameter = unitless_dist_instance.d_scaling_parameter;

  // Reconstruct the original cutoff input distribution
  Teuchos::Array<double> input_indep_cutoff_values, input_dep_cutoff_values,
                         input_indep_discrete_values, input_dep_discrete_values;

  unitless_dist_instance.reconstructOriginalDistributions(
                        input_indep_cutoff_values, input_dep_cutoff_values,
                        input_indep_discrete_values, input_dep_discrete_values );

  this->initializeDistributionsFromRawData( input_indep_cutoff_values,
                                            input_dep_cutoff_values,
                                            input_indep_discrete_values,
                                            input_dep_discrete_values );
}

// Construct distribution from a unitless dist. (potentially dangerous)
/*! \details Constructing a unit-aware distribution from a unitless
 * distribution is potentially dangerous. By forcing users to construct objects
 * using this method instead of a standard constructor we are trying to make
 * sure users are aware of the danger. This is designed to mimic the interface
 * of the boost::units::quantity, which also has to deal with this issue.
 */
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>
UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::fromUnitlessDistribution( const UnitAwareHybridElasticDistribution<InterpolationPolicy,void,void>& unitless_distribution )
{
  return ThisType( unitless_distribution, 0 );
}

// Assignment operator
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>&
UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::operator=(
  const UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>& dist_instance )
{
  // Make sure the distribution is valid
  testPrecondition( dist_instance.d_cutoff_distribution.size() > 0 );
  testPrecondition( dist_instance.d_discrete_distribution.size() > 0 );

  if( this != &dist_instance )
  {
    d_cutoff_distribution = dist_instance.d_cutoff_distribution;
    d_discrete_distribution = dist_instance.d_discrete_distribution;
    d_cutoff_mu = dist_instance.d_cutoff_mu;
    d_cutoff_cross_section_ratio = dist_instance.d_cutoff_cross_section_ratio;
    d_scaling_parameter = dist_instance.d_scaling_parameter;
    d_discrete_norm_constant = dist_instance.d_discrete_norm_constant;
    d_cutoff_norm_constant = dist_instance.d_cutoff_norm_constant;
    d_max_cdf = dist_instance.d_max_cdf;
  }

  return *this;
}

// Evaluate the distribution
/*! \details The discrete distribution can be expressed as a sum of delta
 * functions, which allows it to behave as a continuous distribution.
 * Therefore, the discrete distribution can technically only take on
 * two values: 0.0 and infinity. If the discrete portion of the distribution is
 * evaluated a value of 0.0 will be returned for simplicity.
 */
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::DepQuantity
UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::evaluate(
 const typename UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  // Make sure the indep var variable is within its limits
  testPrecondition( indep_var_value >= this->getLowerBoundOfIndepVar() );
  testPrecondition( indep_var_value <= this->getUpperBoundOfIndepVar() );

  // Check to see if the tabular or discrete portion will be evaluated
  if( indep_var_value < d_cutoff_mu )
  { // evaluate the cutoff tabular large angle distribution

    typename DistributionArray::const_iterator lower_bin_boundary =
                Search::binaryLowerBound<FIRST>( d_cutoff_distribution.begin(),
                                                 d_cutoff_distribution.end(),
                                                  indep_var_value );

    typename DistributionArray::const_iterator upper_bin_boundary =
                                                            lower_bin_boundary;
    ++upper_bin_boundary;

    return InterpolationPolicy::interpolate( lower_bin_boundary->first,
                                             upper_bin_boundary->first,
                                             indep_var_value,
                                             lower_bin_boundary->third,
                                             upper_bin_boundary->third );
  }
  else if( indep_var_value == d_cutoff_mu )
    return d_cutoff_distribution.back().third;
  else
    return DQT::zero(); // getRawQuantity(this->evaluatePDF( indep_var_value ))*d_discrete_norm_constant;
}

// Evaluate the PDF
/*! \details The discrete distribution can be expressed as a sum of delta
 * functions, which allows it to behave as a continuous distribution.
 * Therefore, the discrete distribution can technically only take on
 * two values: 0.0 and infinity. If the discrete portion of the distribution is
 * evaluated a value of 0.0 will be returned for simplicity.
 */
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::InverseIndepQuantity
UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::evaluatePDF(
 const typename UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  // Make sure the indep var variable is within its limits
  testPrecondition( indep_var_value >= this->getLowerBoundOfIndepVar() );
  testPrecondition( indep_var_value <= this->getUpperBoundOfIndepVar() );

  // Check to see if the tabular or discrete portion will be evaluated
  if( indep_var_value <= d_cutoff_mu )
    return this->evaluate( indep_var_value )*d_cutoff_norm_constant;
//  else if( indep_var_value >= d_discrete_distribution.front().first &&
//           indep_var_value <= d_discrete_distribution.back().first )
//  {
//    typename Teuchos::Array<Pair<IndepQuantity,double> >::const_iterator bin =
//        Search::binaryLowerBound<FIRST>( d_discrete_distribution.begin(),
//                                         d_discrete_distribution.end(),
//                                         indep_var_value );


//    typename Teuchos::Array<Pair<IndepQuantity,double> >::const_iterator
//      prev_bin = bin;
//    --prev_bin;

//    if( bin->first == indep_var_value )
//      return IIQT::initializeQuantity( bin->second - prev_bin->second );
//    else
//      return IIQT::zero();
//  }
  else
    return IIQT::zero();
}

// Evaluate the CDF
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
double UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::evaluateCDF(
  const typename UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  // Make sure the indep var variable is within its limits
  testPrecondition( indep_var_value >= this->getLowerBoundOfIndepVar() );
  testPrecondition( indep_var_value <= this->getUpperBoundOfIndepVar() );

  if( indep_var_value == this->getLowerBoundOfIndepVar() )
    return 0.0;
  else if( indep_var_value < d_cutoff_mu )
  {
    typename DistributionArray::const_iterator lower_bin_boundary =
                Search::binaryLowerBound<FIRST>( d_cutoff_distribution.begin(),
                                                 d_cutoff_distribution.end(),
                                                 indep_var_value );

    IndepQuantity indep_diff = indep_var_value - lower_bin_boundary->first;

    return (lower_bin_boundary->second + indep_diff*lower_bin_boundary->third +
          indep_diff*indep_diff*lower_bin_boundary->fourth/2.0)*d_cutoff_norm_constant;
  }
  else if( indep_var_value < d_discrete_distribution.front().first )
    return d_cutoff_cross_section_ratio;
  else if( indep_var_value >= d_discrete_distribution.back().first )
    return 1.0;
  else // indep_var_value >= d_discrete_distribution.front().first && indep_var_value <= d_discrete_distribution.back().first
  {
    typename Teuchos::Array<Pair<IndepQuantity,double> >::const_iterator bin =
      Search::binaryLowerBound<FIRST>( d_discrete_distribution.begin(),
                                       d_discrete_distribution.end(),
                                       indep_var_value );

    return bin->second;
  }
}

// Return a random sample from the distribution
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
inline typename UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sample() const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  unsigned dummy_index;

  return this->sampleImplementation( random_number, dummy_index );
}

// Return a random sample and record the number of trials
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sampleAndRecordTrials(
                                                       unsigned& trials ) const
{
  ++trials;

  return this->sample();
}

// Return a random sample and bin index from the distribution
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sampleAndRecordBinIndex(
                                            unsigned& sampled_bin_index ) const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleImplementation( random_number, sampled_bin_index );
}

// Return a sample from the distribution at the given CDF value
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sampleWithRandomNumber(
                                             const double random_number ) const
{
  unsigned dummy_index;

  return this->sampleImplementation( random_number, dummy_index );
}

// Return a random sample from the corresponding CDF in a subrange
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sampleInSubrange(
 const typename UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity max_indep_var ) const
{
  // Make sure the maximum indep var is valid
  testPrecondition( max_indep_var >= this->getLowerBoundOfIndepVar() );

  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleWithRandomNumberInSubrange( random_number,
                                                 max_indep_var );
}

// Return a random sample from the distribution at the given CDF value in a subrange
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
inline typename UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sampleWithRandomNumberInSubrange(
 const double random_number,
 const typename UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity max_indep_var ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );
  // Make sure the maximum indep var is valid
  testPrecondition( max_indep_var >= this->getLowerBoundOfIndepVar() );

  // Calculate a scaled random number
  double scaled_random_number =
    random_number*this->evaluateCDF( max_indep_var );

  unsigned dummy_index;

  return this->sampleImplementation( scaled_random_number, dummy_index );
}

// Return a random sample using the random number and record the bin index
/*! \details The returned sampled bin index will be the sampled bin index of the
    cutoff distribution or the sampled index of the discrete distribution plus
    the number of bins in the cutoff distribution. This ensures the returned
    sampled bin index will be incremental.
 */
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sampleImplementation(
                                            double random_number,
                                            unsigned& sampled_bin_index ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );

  // Calculate the sampled independent value
  IndepQuantity sample;

  // Sample the moment preserving discrete distribution
  if ( random_number == d_cutoff_cross_section_ratio )
  {
    // Set the sampled bin index to the last bin
    sampled_bin_index = d_cutoff_distribution.size() - 1;

    return d_cutoff_mu;
  }
  else if ( random_number >= d_cutoff_cross_section_ratio )
  {
    double scaled_random_number =
        ( random_number - d_cutoff_cross_section_ratio )*d_scaling_parameter;

    sample = this->sampleDiscrete( scaled_random_number, sampled_bin_index );

    // Add the total number of cutoff bins to the sampled discrete bin
    sampled_bin_index += d_cutoff_distribution.size() - 1;
  }
  else
  {
    sample = this->sampleCutoff( random_number, sampled_bin_index );
  }

  return sample;
}

// Return a random sample of the moment preserving discrete distribution using the random number and record the bin index
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sampleDiscrete(
                                            double random_number,
                                            unsigned& sampled_bin_index ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );

  // Get the bin index sampled
  sampled_bin_index =
    Search::binaryUpperBoundIndex<SECOND>( d_discrete_distribution.begin(),
                                           d_discrete_distribution.end(),
                                           random_number );

  return d_discrete_distribution[sampled_bin_index].first;
}

// Return a random sample of the cutoff tabular distribution using the random number and record the bin index
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sampleCutoff(
                                            double random_number,
                                            unsigned& sampled_bin_index ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= d_cutoff_cross_section_ratio );

  // Calculate the sampled independent value
  IndepQuantity sample;

  UnnormCDFQuantity scaled_random_number;

  // Scale the random number
  scaled_random_number = random_number*d_max_cdf;

  typename DistributionArray::const_iterator lower_bin_boundary =
                Search::binaryLowerBound<SECOND>( d_cutoff_distribution.begin(),
                                                  d_cutoff_distribution.end(),
                                                  scaled_random_number);

  // Calculate the sampled bin index
  sampled_bin_index =
            std::distance( d_cutoff_distribution.begin(), lower_bin_boundary );

  IndepQuantity indep_value = lower_bin_boundary->first;
  UnnormCDFQuantity cdf_diff =
    scaled_random_number - lower_bin_boundary->second;
  DepQuantity pdf_value = lower_bin_boundary->third;
  SlopeQuantity slope = lower_bin_boundary->fourth;

  // x = x0 + [sqrt(pdf(x0)^2 + 2m[cdf(x)-cdf(x0)]) - pdf(x0)]/m
  if( slope != QuantityTraits<SlopeQuantity>::zero() )
  {
    typedef typename QuantityTraits<DepQuantity>::template GetQuantityToPowerType<2>::type DepQuantitySqr;

    DepQuantitySqr term_1 = pdf_value*pdf_value;
    DepQuantitySqr term_2( 2.0*slope*cdf_diff );

    IndepQuantity term_3((Utility::sqrt( term_1 + term_2 ) - pdf_value)/slope);

    sample = indep_value + term_3;

  }
  // x = x0 + [cdf(x)-cdf(x0)]/pdf(x0) => L'Hopital's rule
  else
  {
    IndepQuantity term_2( cdf_diff/pdf_value );

    sample = indep_value + term_2;
  }

  // Make sure the sample is valid
  testPostcondition( !IQT::isnaninf( sample ) );
  testPostcondition( sample >= this->getLowerBoundOfIndepVar() );
  testPostcondition( sample <= d_cutoff_mu );

  return sample;
}

// Return the upper bound of the distribution independent variable
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::getUpperBoundOfIndepVar() const
{
  return IQT::one();
}

// Return the cutoff bound of the distribution independent variable
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::getCutoffBoundOfIndepVar() const
{
  return d_cutoff_mu;
}

// Return the lower bound of the distribution independent variable
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::getLowerBoundOfIndepVar() const
{
  return -1.0*IQT::one();
}

// Return the distribution type
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
OneDDistributionType
UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::getDistributionType() const
{
  return ThisType::distribution_type;
}

// Return the cutoff cross section ratio for the distribution
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
double
UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::getCutoffCrossSectionRatio() const
{
  return ThisType::d_cutoff_cross_section_ratio;
}

// Test if the distribution is continuous
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
bool UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::isContinuous() const
{
  return true;
}

// Method for placing the object in an output stream
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
void UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::toStream(
                                                       std::ostream& os ) const
{
  Teuchos::Array<double> independent_cutoff_values, dependent_cutoff_values,
                         independent_discrete_values, dependent_discrete_values;

  this->reconstructOriginalUnitlessDistributions( independent_cutoff_values,
                                                  dependent_cutoff_values,
                                                  independent_discrete_values,
                                                  dependent_discrete_values );

  os << "{" << independent_cutoff_values << ","
            << dependent_cutoff_values << ","
            << independent_discrete_values << ","
            << dependent_discrete_values << ","
            << d_cutoff_mu << ","
            << d_cutoff_cross_section_ratio << "}";
}

// Method for initializing the object from an input stream
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
void UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::fromStream( std::istream& is )
{
  // Read the initial '{'
  std::string start_bracket;
  std::getline( is, start_bracket, '{' );
  start_bracket = Teuchos::Utils::trimWhiteSpace( start_bracket );

  TEST_FOR_EXCEPTION( start_bracket.size() != 0,
                      InvalidDistributionStringRepresentation,
                      "Error: the input stream is not a valid hybrid elastic "
                      "distribution representation!" );

  std::string independent_cutoff_values_rep;
  std::getline( is, independent_cutoff_values_rep, '}' );
  independent_cutoff_values_rep += "}";

  // Parse special characters
  try{
    ArrayString::locateAndReplacePi( independent_cutoff_values_rep );
    ArrayString::locateAndReplaceIntervalOperator( independent_cutoff_values_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                              InvalidDistributionStringRepresentation,
                              "Error: the hybrid elastic distribution cannot be "
                              "constructed because the representation is not "
                              "valid (see details below)!\n" );

  Teuchos::Array<double> independent_cutoff_values;
  try{
    independent_cutoff_values =
      Teuchos::fromStringToArray<double>( independent_cutoff_values_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
                              InvalidDistributionStringRepresentation,
                              "Error: the hybrid elastic distribution cannot be "
                              "constructed because the representation is not "
                              "valid (see details below)!\n" );

  TEST_FOR_EXCEPTION( !Sort::isSortedAscending( independent_cutoff_values.begin(),
                                                independent_cutoff_values.end() ),
                      InvalidDistributionStringRepresentation,
                      "Error: the hybrid elastic distribution cannot be constructed "
                      "because the cutoff bin boundaries "
                      << independent_cutoff_values_rep << " are not sorted!" );

  // Read the ","
  std::string separator;
  std::getline( is, separator, ',' );

  std::string dependent_cutoff_values_rep;
  std::getline( is, dependent_cutoff_values_rep, '}' );
  dependent_cutoff_values_rep += "}";

  // Parse special characters
  try{
    ArrayString::locateAndReplacePi( dependent_cutoff_values_rep );
    ArrayString::locateAndReplaceIntervalOperator( dependent_cutoff_values_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                              InvalidDistributionStringRepresentation,
                              "Error: the hybrid elastic distribution cannot be "
                              "constructed because the representation is not "
                              "valid (see details below)!\n" );

  Teuchos::Array<double> dependent_cutoff_values;
  try{
    dependent_cutoff_values =
      Teuchos::fromStringToArray<double>( dependent_cutoff_values_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
                              InvalidDistributionStringRepresentation,
                              "Error: the hybrid elastic distribution cannot be "
                              "constructed because the representation is not "
                              "valid (see details below)!\n" );

  TEST_FOR_EXCEPTION( independent_cutoff_values.size() != dependent_cutoff_values.size(),
                      InvalidDistributionStringRepresentation,
                      "Error: the hybrid elastic distribution "
                      "{" << independent_cutoff_values_rep << "},{"
                      << dependent_cutoff_values_rep << "} "
                      "cannot be constructed because the number of "
                      "independent cutoff values does not equal the number of "
                      "dependent cutoff values" );

  // Read the ","
  std::getline( is, separator, ',' );

  std::string independent_discrete_values_rep;
  std::getline( is, independent_discrete_values_rep, '}' );
  independent_discrete_values_rep += "}";

  // Parse special characters
  try{
    ArrayString::locateAndReplacePi( independent_discrete_values_rep );
    ArrayString::locateAndReplaceIntervalOperator( independent_discrete_values_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                              InvalidDistributionStringRepresentation,
                              "Error: the hybrid elastic distribution cannot be "
                              "constructed because the representation is not "
                              "valid (see details below)!\n" );

  Teuchos::Array<double> independent_discrete_values;
  try{
    independent_discrete_values =
      Teuchos::fromStringToArray<double>( independent_discrete_values_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
                              InvalidDistributionStringRepresentation,
                              "Error: the hybrid elastic distribution cannot be "
                              "constructed because the representation is not "
                              "valid (see details below)!\n" );

  TEST_FOR_EXCEPTION( !Sort::isSortedAscending( independent_discrete_values.begin(),
                                                independent_discrete_values.end() ),
                      InvalidDistributionStringRepresentation,
                      "Error: the hybrid elastic distribution cannot be constructed "
                      "because the discrete bin boundaries "
                      << independent_discrete_values_rep << " are not sorted!" );

  // Read the ","
  std::getline( is, separator, ',' );

  std::string dependent_discrete_values_rep;
  std::getline( is, dependent_discrete_values_rep, '}' );
  dependent_discrete_values_rep += "}";

  // Parse special characters
  try{
    ArrayString::locateAndReplacePi( dependent_discrete_values_rep );
    ArrayString::locateAndReplaceIntervalOperator( dependent_discrete_values_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                              InvalidDistributionStringRepresentation,
                              "Error: the hybrid elastic distribution cannot be "
                              "constructed because the representation is not "
                              "valid (see details below)!\n" );

  Teuchos::Array<double> dependent_discrete_values;
  try{
    dependent_discrete_values =
      Teuchos::fromStringToArray<double>( dependent_discrete_values_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
                              InvalidDistributionStringRepresentation,
                              "Error: the hybrid elastic distribution cannot be "
                              "constructed because the representation is not "
                              "valid (see details below)!\n" );

  TEST_FOR_EXCEPTION( independent_discrete_values.size() != dependent_discrete_values.size(),
                      InvalidDistributionStringRepresentation,
                      "Error: the hybrid elastic distribution "
                      "{" << independent_discrete_values_rep << "},{"
                      << dependent_discrete_values_rep << "} "
                      "cannot be constructed because the number of "
                      "independent discrete values does not equal the number of "
                      "dependent discrete values" );

  // Read the ","
  std::getline( is, separator, ',' );

  std::string cutoff_mu_rep;
  std::getline( is, cutoff_mu_rep, ',' );

  // Parse special characters
  try{
    ArrayString::locateAndReplacePi( cutoff_mu_rep );
//    ArrayString::locateAndReplaceIntervalOperator( cutoff_mu_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                              InvalidDistributionStringRepresentation,
                              "Error: the hybrid elastic distribution cannot be "
                              "constructed because the representation is not "
                              "valid (see details below)!\n" );

  double cutoff_mu;
  try{
    cutoff_mu = std::stod( cutoff_mu_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
                              InvalidDistributionStringRepresentation,
                              "Error: the hybrid elastic distribution cannot be "
                              "constructed because the representation is not "
                              "valid (see details below)!\n" );

  std::string cutoff_ratio_value_rep;
  std::getline( is, cutoff_ratio_value_rep, '}' );

  // Parse special characters
  try{
    ArrayString::locateAndReplacePi( cutoff_ratio_value_rep );
//    ArrayString::locateAndReplaceIntervalOperator( cutoff_ratio_value_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                              InvalidDistributionStringRepresentation,
                              "Error: the hybrid elastic distribution cannot be "
                              "constructed because the representation is not "
                              "valid (see details below)!\n" );

  double cutoff_cross_section_ratio;
  try{
    cutoff_cross_section_ratio = std::stod( cutoff_ratio_value_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
                              InvalidDistributionStringRepresentation,
                              "Error: the hybrid elastic distribution cannot be "
                              "constructed because the representation is not "
                              "valid (see details below)!\n" );

  // Set the member data
  d_cutoff_mu = cutoff_mu;
  d_cutoff_cross_section_ratio = cutoff_cross_section_ratio;
  d_scaling_parameter = 1.0/( 1.0 - cutoff_cross_section_ratio );
  this->initializeDistributionsFromRawData( independent_cutoff_values,
                                            dependent_cutoff_values,
                                            independent_discrete_values,
                                            dependent_discrete_values );
}

// Method for testing if two objects are equivalent
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
bool UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::isEqual(
 const UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>& other ) const
{
  return d_cutoff_distribution == other.d_cutoff_distribution &&
         d_discrete_distribution == other.d_discrete_distribution &&
         d_cutoff_mu == other.d_cutoff_mu &&
         d_cutoff_cross_section_ratio == other.d_cutoff_cross_section_ratio &&
         d_discrete_norm_constant == other.d_discrete_norm_constant &&
         d_cutoff_norm_constant == other.d_cutoff_norm_constant &&
         d_max_cdf == other.d_max_cdf;
}

// Initialize the distributions
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
void UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::initializeDistributionsFromRawData(
                      const Teuchos::Array<double>& independent_cutoff_values,
                      const Teuchos::Array<double>& dependent_cutoff_values,
                      const Teuchos::Array<double>& independent_discrete_values,
                      const Teuchos::Array<double>& dependent_discrete_values )
{
  // Make sure there is at least one bin
  testPrecondition( independent_cutoff_values.size() > 1 );
  testPrecondition( dependent_cutoff_values.size() ==
                    independent_cutoff_values.size() );
  testPrecondition( dependent_discrete_values.size() ==
                    independent_discrete_values.size() );
  // Make sure that the independent_values have the proper range
  testPrecondition( independent_cutoff_values.front() == -1.0 );
  testPrecondition( independent_cutoff_values.back() >= d_cutoff_mu );
  testPrecondition( independent_cutoff_values.back() <= 0.999999 );
  testPrecondition( independent_discrete_values.front() >= d_cutoff_mu );
  testPrecondition( independent_discrete_values.back() < 1.0 );

  // Initialize the cutoff distribution
  {
  // Convert the raw independent cutoff values to quantities
  Teuchos::Array<IndepQuantity> independent_quantities;

  this->convertUnitlessValues( independent_cutoff_values, independent_quantities );

  // Convert the raw dependent cutoff values to quantities
  Teuchos::Array<DepQuantity> dependent_quantities;

  this->convertUnitlessValues( dependent_cutoff_values, dependent_quantities );

  this->initializeCutoffDistribution( independent_quantities,
                                      dependent_quantities );
  }

  // Initialize the discrete distribution
  {
  // Convert the raw independent discrete values to quantities
  Teuchos::Array<IndepQuantity> independent_quantities;

  this->convertUnitlessValues( independent_discrete_values, independent_quantities );

  // Convert the raw dependent discrete values to quantities
  Teuchos::Array<DepQuantity> dependent_quantities;

  this->convertUnitlessValues( dependent_discrete_values, dependent_quantities );

  this->initializeDiscreteDistribution( independent_quantities,
                                        dependent_quantities );
  }
}

// Initialize the distribution
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
template<typename InputIndepQuantity, typename InputDepQuantity>
void UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::initializeCutoffDistribution(
                  const Teuchos::Array<InputIndepQuantity>& independent_values,
                  const Teuchos::Array<InputDepQuantity>& dependent_values )
{
  // Make sure that at least two points of the distribution are specified
  testPrecondition( independent_values.size() > 1 );
  // Make sure that every independent value has a dependent value
  testPrecondition( independent_values.size() == dependent_values.size() );
  // Make sure that the independent values are sorted
  testPrecondition( Sort::isSortedAscending( independent_values.begin(),
                                             independent_values.end() ) );
  // Make sure that the independent_values have the proper range
  testPrecondition( independent_values.front() == this->getLowerBoundOfIndepVar() );
  testPrecondition( independent_values.back() <= IndepQuantity(0.999999) );
  testPrecondition( independent_values.back() >= d_cutoff_mu );

  // Resize the distribution
  d_cutoff_distribution.resize( independent_values.size() );


  // Assign the raw distribution data
  for( unsigned i = 0; i < independent_values.size(); ++i )
  {
    d_cutoff_distribution[i].first = IndepQuantity( independent_values[i] );

    // Scale the dependent values by the cross section ratio
    /*! \details The pdf values are for the tabular cutoff elastic distribution
     *  and must be re-scaled for the total hybrid elastic distribution.
     */
    d_cutoff_distribution[i].third =
                DepQuantity( dependent_values[i]*d_cutoff_cross_section_ratio );
  }

  // Create a CDF from the raw distribution data
  d_cutoff_norm_constant =
    DataProcessor::calculateContinuousCDF<FIRST,THIRD,SECOND>( d_cutoff_distribution,
                                                               false );

  // Calculate the slopes of the PDF
  DataProcessor::calculateSlopes<FIRST,THIRD,FOURTH>( d_cutoff_distribution );


  typename DistributionArray::const_iterator lower_bin_boundary =
                Search::binaryLowerBound<FIRST>( d_cutoff_distribution.begin(),
                                                 d_cutoff_distribution.end(),
                                                 d_cutoff_mu );

    IndepQuantity indep_diff = d_cutoff_mu - lower_bin_boundary->first;

    double cdf = (lower_bin_boundary->second + indep_diff*lower_bin_boundary->third +
          indep_diff*indep_diff*lower_bin_boundary->fourth/2.0);

    double cdf_norm = cdf*d_cutoff_norm_constant;

std::cout << std::setprecision(20) << "\nlower_bin_boundary->first =\t" <<     lower_bin_boundary->first << std::endl;
std::cout << std::setprecision(20) << "lower_bin_boundary->second =\t" <<     lower_bin_boundary->second << std::endl;
std::cout << std::setprecision(20) << "lower_bin_boundary->third =\t" << lower_bin_boundary->third << std::endl;
std::cout << std::setprecision(20) << "cdf =\t" <<   cdf << std::endl;
std::cout << std::setprecision(20) << "d_cutoff_norm_constant =\t" << d_cutoff_norm_constant << std::endl;
std::cout << std::setprecision(20) << "cdf_norm =\t" << cdf_norm << std::endl;

  // Scale norm constant by the cross section ratio
  /*! \details The norm constant given by the calculateContinuousCDF function
   *  is for the tabular cutoff elastic distribution and must be re-scaled for
   *  the total elastic distribution.
   */
  d_cutoff_norm_constant *= d_cutoff_cross_section_ratio;

cdf_norm = cdf*d_cutoff_norm_constant;
std::cout << std::setprecision(20) << "d_cutoff_cross_section_ratio =\t" << d_cutoff_cross_section_ratio << std::endl;
std::cout << std::setprecision(20) << "d_cutoff_norm_constant =\t" << d_cutoff_norm_constant << std::endl;
std::cout << std::setprecision(20) << "cdf_norm =\t" << cdf_norm << std::endl;

  // Set the max CDF for the total elastic distribution
  d_max_cdf = 1.0/d_cutoff_norm_constant;

std::cout << std::setprecision(20) << "d_max_cdf =\t" << d_max_cdf << std::endl;
  d_max_cdf = cdf/d_cutoff_cross_section_ratio;




  // Scale the random number
  double scaled_random_number = cdf;

  lower_bin_boundary =
                Search::binaryLowerBound<SECOND>( d_cutoff_distribution.begin(),
                                                  d_cutoff_distribution.end(),
                                                  scaled_random_number);

  // Calculate the sampled bin index

std::cout << std::setprecision(20) << "lower_bin_boundary->first =\t" << lower_bin_boundary->first << std::endl;
  IndepQuantity indep_value = lower_bin_boundary->first;
  UnnormCDFQuantity cdf_diff =
    scaled_random_number - lower_bin_boundary->second;
  DepQuantity pdf_value = lower_bin_boundary->third;
  SlopeQuantity slope = lower_bin_boundary->fourth;

double sample;
  // x = x0 + [sqrt(pdf(x0)^2 + 2m[cdf(x)-cdf(x0)]) - pdf(x0)]/m
  if( slope != QuantityTraits<SlopeQuantity>::zero() )
  {
    typedef typename QuantityTraits<DepQuantity>::template GetQuantityToPowerType<2>::type DepQuantitySqr;

    DepQuantitySqr term_1 = pdf_value*pdf_value;
    DepQuantitySqr term_2( 2.0*slope*cdf_diff );

    IndepQuantity term_3((Utility::sqrt( term_1 + term_2 ) - pdf_value)/slope);

    sample = indep_value + term_3;

  }
  // x = x0 + [cdf(x)-cdf(x0)]/pdf(x0) => L'Hopital's rule
  else
  {
    IndepQuantity term_2( cdf_diff/pdf_value );

    sample = indep_value + term_2;
  }
std::cout << std::setprecision(20) << "sample =\t" << sample << std::endl;














  // Scale the random number
  scaled_random_number = d_cutoff_cross_section_ratio/d_cutoff_norm_constant - 1e-15;

  lower_bin_boundary =
                Search::binaryLowerBound<SECOND>( d_cutoff_distribution.begin(),
                                                  d_cutoff_distribution.end(),
                                                  scaled_random_number);

  // Calculate the sampled bin index

std::cout << std::setprecision(20) << "lower_bin_boundary->first =\t" << lower_bin_boundary->first << std::endl;
  indep_value = lower_bin_boundary->first;
  cdf_diff =
    scaled_random_number - lower_bin_boundary->second;
  pdf_value = lower_bin_boundary->third;
  slope = lower_bin_boundary->fourth;

  // x = x0 + [sqrt(pdf(x0)^2 + 2m[cdf(x)-cdf(x0)]) - pdf(x0)]/m
  if( slope != QuantityTraits<SlopeQuantity>::zero() )
  {
    typedef typename QuantityTraits<DepQuantity>::template GetQuantityToPowerType<2>::type DepQuantitySqr;

    DepQuantitySqr term_1 = pdf_value*pdf_value;
    DepQuantitySqr term_2( 2.0*slope*cdf_diff );

    IndepQuantity term_3((Utility::sqrt( term_1 + term_2 ) - pdf_value)/slope);

    sample = indep_value + term_3;

  }
  // x = x0 + [cdf(x)-cdf(x0)]/pdf(x0) => L'Hopital's rule
  else
  {
    IndepQuantity term_2( cdf_diff/pdf_value );

    sample = indep_value + term_2;
  }
std::cout << std::setprecision(20) << "sample =\t" << sample << std::endl;
}

// Initialize the distribution
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
template<typename InputIndepQuantity, typename InputDepQuantity>
void UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::initializeDiscreteDistribution(
                const Teuchos::Array<InputIndepQuantity>& independent_values,
                const Teuchos::Array<InputDepQuantity>& dependent_values )
{
  // Make sure that every value has a probability assigned
  testPrecondition( independent_values.size() == dependent_values.size() );
  // Make sure that the bins are sorted
  testPrecondition( Sort::isSortedAscending( independent_values.begin(),
                                             independent_values.end() ) );

  // Resize the distribution array
  d_discrete_distribution.resize( independent_values.size() );

  // Assign the raw distribution data
  for( unsigned i = 0; i < dependent_values.size(); ++i )
  {
    d_discrete_distribution[i].first = IndepQuantity( independent_values[i] );

    // Use an explicit cast to desired unit
    DepQuantity dep_quantity( dependent_values[i] );

    d_discrete_distribution[i].second = getRawQuantity( dep_quantity );

    d_discrete_norm_constant += dep_quantity;
  }

  // Create a CDF from the raw distribution data
  DataProcessor::calculateDiscreteCDF<SECOND,SECOND>( d_discrete_distribution );
}

// Reconstruct original distribution
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
void UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::reconstructOriginalDistributions(
                 Teuchos::Array<IndepQuantity>& independent_cutoff_values,
                 Teuchos::Array<DepQuantity>& dependent_cutoff_values,
                 Teuchos::Array<IndepQuantity>& independent_discrete_values,
                 Teuchos::Array<DepQuantity>& dependent_discrete_values ) const
{
  // Resize the arrays
  independent_cutoff_values.resize( d_cutoff_distribution.size() );
  dependent_cutoff_values.resize( d_cutoff_distribution.size() );
  independent_discrete_values.resize( d_discrete_distribution.size() );
  dependent_discrete_values.resize( d_discrete_distribution.size() );

  // Reconstruct the cutoff distribution
  for( unsigned i = 0u; i < d_cutoff_distribution.size(); ++i )
  {
    independent_cutoff_values[i] = d_cutoff_distribution[i].first;

    dependent_cutoff_values[i] =
                d_cutoff_distribution[i].third/d_cutoff_cross_section_ratio;
  }

  // Reconstruct the discrete distribution
  for( unsigned i = 0u; i < d_discrete_distribution.size(); ++i )
  {
    independent_discrete_values[i] = d_discrete_distribution[i].first;

    if( i != 0u )
    {
      dependent_discrete_values[i] = d_discrete_norm_constant*
      (d_discrete_distribution[i].second - d_discrete_distribution[i-1].second);
    }
    else
    {
      dependent_discrete_values[i] =
                d_discrete_norm_constant*d_discrete_distribution[i].second;
    }
  }
}

// Reconstruct original distribution w/o units
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
void UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::reconstructOriginalUnitlessDistributions(
                 Teuchos::Array<double>& independent_cutoff_values,
                 Teuchos::Array<double>& dependent_cutoff_values,
                 Teuchos::Array<double>& independent_discrete_values,
                 Teuchos::Array<double>& dependent_discrete_values ) const
{
  // Resize the arrays
  independent_cutoff_values.resize( d_cutoff_distribution.size() );
  dependent_cutoff_values.resize( d_cutoff_distribution.size() );
  independent_discrete_values.resize( d_discrete_distribution.size() );
  dependent_discrete_values.resize( d_discrete_distribution.size() );

  // Reconstruct the cutoff distribution
  for( unsigned i = 0u; i < d_cutoff_distribution.size(); ++i )
  {
    independent_cutoff_values[i] =
                            getRawQuantity( d_cutoff_distribution[i].first );
    dependent_cutoff_values[i] =
      getRawQuantity( d_cutoff_distribution[i].third/d_cutoff_cross_section_ratio );
  }

  // Reconstruct the discrete distribution
  for( unsigned i = 0u; i < d_discrete_distribution.size(); ++i )
  {
    independent_discrete_values[i] = getRawQuantity( d_discrete_distribution[i].first );

    if( i != 0u )
    {
      dependent_discrete_values[i] = getRawQuantity( d_discrete_norm_constant )*
        (d_discrete_distribution[i].second - d_discrete_distribution[i-1].second);
    }
    else
    {
      dependent_discrete_values[i] =
        d_discrete_distribution[i].second*getRawQuantity( d_discrete_norm_constant );
    }
  }
}

// Convert the unitless values to the correct units
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
template<typename Quantity>
void UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::convertUnitlessValues(
                                 const Teuchos::Array<double>& unitless_values,
                                 Teuchos::Array<Quantity>& quantities )
{
  // Resize the quantity array
  quantities.resize( unitless_values.size() );

  // Copy the bin boundaries
  for( unsigned i = 0u; i < unitless_values.size(); ++i )
    setQuantity( quantities[i], unitless_values[i] );
}

// Test if the dependent variable can be zero within the indep bounds
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
bool UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::canDepVarBeZeroInIndepBounds() const
{
  bool possible_zero = false;

  for( size_t i = 0; i < d_cutoff_distribution.size(); ++i )
  {
    if( d_cutoff_distribution[i].third == DQT::zero() )
    {
      possible_zero = true;

      break;
    }
  }

  return possible_zero;
}

// Test if the independent variable is compatible with Lin processing
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
bool UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::isIndepVarCompatibleWithProcessingType(
                                         const LinIndepVarProcessingTag ) const
{
  return boost::is_same<typename InterpolationPolicy::IndepVarProcessingTag,LinIndepVarProcessingTag>::value;
}
  
// Test if the independent variable is compatible with Log processing
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
bool UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::isIndepVarCompatibleWithProcessingType(
                                         const LogIndepVarProcessingTag ) const
{
  return boost::is_same<typename InterpolationPolicy::IndepVarProcessingTag,LogIndepVarProcessingTag>::value;
}

// Test if the dependent variable is compatible with Lin processing
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
bool UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::isDepVarCompatibleWithProcessingType(
                                           const LinDepVarProcessingTag ) const
{
  return boost::is_same<typename InterpolationPolicy::DepVarProcessingTag,LinDepVarProcessingTag>::value;
}

// Test if the dependent variable is compatible with Log processing
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
bool UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::isDepVarCompatibleWithProcessingType(
                                           const LogDepVarProcessingTag ) const
{
  return boost::is_same<typename InterpolationPolicy::DepVarProcessingTag,LogDepVarProcessingTag>::value;
}

} // end Utility namespace

#endif // end UTILITY_HYBRID_ELASTIC_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_HybridElasticDistribution_def.hpp
//---------------------------------------------------------------------------//
