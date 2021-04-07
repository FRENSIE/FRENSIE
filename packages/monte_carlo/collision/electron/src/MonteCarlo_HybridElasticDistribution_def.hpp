//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_HybridElasticDistribution_def.hpp
//! \author Luke Kersting
//! \brief  Hybrid elastic distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_HYBRID_ELASTIC_DISTRIBUTION_DEF_HPP
#define MONTE_CARLO_HYBRID_ELASTIC_DISTRIBUTION_DEF_HPP

// Std Includes
#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstdlib>

// FRENSIE Includes
#include "MonteCarlo_ElasticElectronTraits.hpp"
#include "Utility_DataProcessor.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_DesignByContract.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"

BOOST_SERIALIZATION_CLASS3_EXPORT_IMPLEMENT( UnitAwareHybridElasticDistribution, MonteCarlo );

namespace MonteCarlo{

// Default constructor
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::UnitAwareHybridElasticDistribution()
{
  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

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
                    const std::vector<double>& independent_cutoff_values,
                    const std::vector<double>& dependent_cutoff_values,
                    const std::vector<double>& independent_discrete_values,
                    const std::vector<double>& dependent_discrete_values,
                    const double cutoff_angle_cosine,
                    const double cutoff_cross_section_ratio )
  : d_cutoff_distribution( independent_cutoff_values.size() ),
    d_discrete_distribution( independent_discrete_values.size() ),
    d_cutoff_mu( cutoff_angle_cosine ),
    d_cutoff_cross_section_ratio( cutoff_cross_section_ratio ),
    d_scaling_parameter( 1.0/( 1.0 - cutoff_cross_section_ratio ) ),
    d_discrete_norm_constant( DNQT::zero() ),
    d_cutoff_norm_constant( DNQT::zero() ),
    d_max_cutoff_cdf( UCQT::zero() )
{
  // Make sure there is at lease one bin in the cutoff distribution
  testPrecondition( independent_cutoff_values.size() > 1 );
  testPrecondition( dependent_cutoff_values.size() ==
                    independent_cutoff_values.size() );
  testPrecondition( dependent_discrete_values.size() ==
                    independent_discrete_values.size() );
  // Make sure that the bins are sorted
  testPrecondition( Utility::Sort::isSortedAscending( independent_cutoff_values.begin(),
                                             independent_cutoff_values.end() ) );
  testPrecondition( Utility::Sort::isSortedAscending( independent_discrete_values.begin(),
                                             independent_discrete_values.end() ) );
  // Make sure that the independent_values have the proper range
  testPrecondition( independent_cutoff_values.front() == -1.0 );
  testPrecondition( independent_cutoff_values.back() <= 0.999999 );
  testPrecondition( independent_discrete_values.front() >= cutoff_angle_cosine );
  testPrecondition( independent_discrete_values.back() < 1.0 );

  // Verify that the values are valid
  this->verifyValidValues( independent_cutoff_values,
                           dependent_cutoff_values,
                           independent_discrete_values,
                           dependent_discrete_values,
                           cutoff_angle_cosine,
                           cutoff_cross_section_ratio );

  this->initializeDistributionsFromRawData( independent_cutoff_values,
                                            dependent_cutoff_values,
                                            independent_discrete_values,
                                            dependent_discrete_values );

  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}


// Constructor
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
template<typename InputIndepQuantity, typename InputDepQuantity>
UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::UnitAwareHybridElasticDistribution(
        const std::vector<InputIndepQuantity>& independent_cutoff_values,
        const std::vector<InputDepQuantity>& dependent_cutoff_values,
        const std::vector<InputIndepQuantity>& independent_discrete_values,
        const std::vector<InputDepQuantity>& dependent_discrete_values,
        const InputIndepQuantity& cutoff_angle_cosine,
        const double cutoff_cross_section_ratio )
  : d_cutoff_distribution( independent_cutoff_values.size() ),
    d_discrete_distribution( independent_discrete_values.size() ),
    d_cutoff_mu( cutoff_angle_cosine*Utility::QuantityTraits<InputDepQuantity>::one() ),
    d_cutoff_cross_section_ratio( cutoff_cross_section_ratio ),
    d_discrete_norm_constant( DNQT::zero() ),
    d_cutoff_norm_constant( DNQT::zero() ),
    d_max_cutoff_cdf( UCQT::zero() )
{
  // Make sure there is at lease one bin in the cutoff distribution
  testPrecondition( independent_cutoff_values.size() > 1 );
  testPrecondition( dependent_cutoff_values.size() ==
                    independent_cutoff_values.size() );
  testPrecondition( dependent_discrete_values.size() ==
                    independent_discrete_values.size() );
  // Make sure that the bins are sorted
  testPrecondition( Utility::Sort::isSortedAscending( independent_cutoff_values.begin(),
                                             independent_cutoff_values.end() ) );
  testPrecondition( Utility::Sort::isSortedAscending( independent_discrete_values.begin(),
                                             independent_discrete_values.end() ) );
  // Make sure that the independent_values have the proper range
  testPrecondition( independent_cutoff_values.front() == -1.0 );
  testPrecondition( independent_cutoff_values.back() <= 0.999999 );
  testPrecondition( independent_discrete_values.front() >= cutoff_angle_cosine );
  testPrecondition( independent_discrete_values.back() < 1.0 );

  // Verify that the values are valid
  this->verifyValidValues( independent_cutoff_values,
                           dependent_cutoff_values,
                           independent_discrete_values,
                           dependent_discrete_values,
                           cutoff_angle_cosine,
                           cutoff_cross_section_ratio );

  this->initializeCutoffDistribution( independent_cutoff_values,
                                      dependent_cutoff_values );
  this->initializeDiscreteDistribution( independent_discrete_values,
                                        dependent_discrete_values );

  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
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
    d_cutoff_mu( dist_instance.d_cutoff_mu ),
    d_cutoff_cross_section_ratio( dist_instance.d_cutoff_cross_section_ratio ),
    d_scaling_parameter( dist_instance.d_scaling_parameter ),
    d_discrete_norm_constant(),
    d_cutoff_norm_constant(),
    d_max_cutoff_cdf()
{
  // Make sure the distribution is valid
  testPrecondition( dist_instance.d_cutoff_distribution.size() > 0 );
  testPrecondition( dist_instance.d_discrete_distribution.size() > 0 );

  typedef typename UnitAwareHybridElasticDistribution<InterpolationPolicy,InputIndepUnit,InputDepUnit>::IndepQuantity InputIndepQuantity;

  typedef typename UnitAwareHybridElasticDistribution<InterpolationPolicy,InputIndepUnit,InputDepUnit>::DepQuantity InputDepQuantity;

  // Reconstruct the original cutoff input distribution
  std::vector<InputIndepQuantity> input_indep_cutoff_values;
  std::vector<InputDepQuantity> input_dep_cutoff_values;
  std::vector<InputIndepQuantity> input_indep_discrete_values;
  std::vector<InputDepQuantity> input_dep_discrete_values;

  dist_instance.reconstructOriginalDistributions( input_indep_cutoff_values,
                                                  input_dep_cutoff_values,
                                                  input_indep_discrete_values,
                                                  input_dep_discrete_values );

  // Verify that the values are valid
  this->verifyValidValues( input_indep_cutoff_values,
                           input_dep_cutoff_values,
                           input_indep_discrete_values,
                           input_dep_discrete_values,
                           dist_instance.d_cutoff_mu,
                           dist_instance.d_cutoff_cross_section_ratio );

  this->initializeCutoffDistribution( input_indep_cutoff_values,
                                      input_dep_cutoff_values );

  this->initializeDiscreteDistribution( input_indep_discrete_values,
                                        input_dep_discrete_values );

  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Copy constructor (copying from unitless distribution only)
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::UnitAwareHybridElasticDistribution( const UnitAwareHybridElasticDistribution<InterpolationPolicy,void,void>& unitless_dist_instance, int )
  : d_cutoff_distribution(),
    d_discrete_distribution(),
    d_cutoff_mu( unitless_dist_instance.d_cutoff_mu ),
    d_cutoff_cross_section_ratio( unitless_dist_instance.d_cutoff_cross_section_ratio ),
    d_scaling_parameter( unitless_dist_instance.d_scaling_parameter ),
    d_discrete_norm_constant(),
    d_cutoff_norm_constant(),
    d_max_cutoff_cdf()
{
  // Make sure the distribution is valid
  testPrecondition( unitless_dist_instance.d_cutoff_distribution.size() > 0 );
  testPrecondition( unitless_dist_instance.d_discrete_distribution.size() > 0 );

  // Reconstruct the original cutoff input distribution
  std::vector<double> input_indep_cutoff_values, input_dep_cutoff_values,
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
    d_max_cutoff_cdf = dist_instance.d_max_cutoff_cdf;
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
  if( indep_var_value <= d_cutoff_mu )
  { // evaluate the cutoff tabular large angle distribution

    typename DistributionArray::const_iterator lower_bin_boundary =
                Utility::Search::binaryLowerBound<Utility::FIRST>( d_cutoff_distribution.begin(),
                                                 d_cutoff_distribution.end(),
                                                 indep_var_value );

    typename DistributionArray::const_iterator upper_bin_boundary =
                                                            lower_bin_boundary;
    ++upper_bin_boundary;

    return InterpolationPolicy::interpolate(
                                        Utility::get<0>(*lower_bin_boundary),
                                        Utility::get<0>(*upper_bin_boundary),
                                        indep_var_value,
                                        Utility::get<2>(*lower_bin_boundary),
                                        Utility::get<2>(*upper_bin_boundary) );
  }
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
    return this->evaluate( indep_var_value )/d_max_cutoff_cdf;
//  else if( indep_var_value >= d_discrete_distribution.front().first &&
//           indep_var_value <= d_discrete_distribution.back().first )
//  {
//    typename std::vector<Pair<IndepQuantity,double> >::const_iterator bin =
//        Utility::Search::binaryLowerBound<Utility::FIRST>( d_discrete_distribution.begin(),
//                                         d_discrete_distribution.end(),
//                                         indep_var_value );


//    typename std::vector<Pair<IndepQuantity,double> >::const_iterator
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
                Utility::Search::binaryLowerBound<Utility::FIRST>( d_cutoff_distribution.begin(),
                                                 d_cutoff_distribution.end(),
                                                 indep_var_value );

    IndepQuantity indep_diff =
      indep_var_value - Utility::get<0>(*lower_bin_boundary);

    return (Utility::get<1>(*lower_bin_boundary) + indep_diff*Utility::get<2>(*lower_bin_boundary) +
            indep_diff*indep_diff*Utility::get<3>(*lower_bin_boundary)/2.0)*d_cutoff_norm_constant;
  }
  else if( indep_var_value < Utility::get<0>(d_discrete_distribution.front()) )
    return d_cutoff_cross_section_ratio;
  else if( indep_var_value >= Utility::get<0>(d_discrete_distribution.back()) )
    return 1.0;
  else // indep_var_value >= d_discrete_distribution.front().first && indep_var_value <= d_discrete_distribution.back().first
  {
    typename std::vector<std::pair<IndepQuantity,double> >::const_iterator bin =
      Utility::Search::binaryLowerBound<Utility::FIRST>( d_discrete_distribution.begin(),
                                       d_discrete_distribution.end(),
                                       indep_var_value );

    return d_cutoff_cross_section_ratio +
      Utility::get<1>(*bin)*( 1.0 - d_cutoff_cross_section_ratio );
  }
}

// Return a random sample from the distribution
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
inline typename UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sample() const
{
  double random_number = Utility::RandomNumberGenerator::getRandomNumber<double>();

  size_t dummy_index;

  return this->sampleImplementation( random_number, dummy_index );
}

// Return a random sample and record the number of trials
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sampleAndRecordTrials(
                           Utility::DistributionTraits::Counter& trials ) const
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
                                            size_t& sampled_bin_index ) const
{
  double random_number = Utility::RandomNumberGenerator::getRandomNumber<double>();

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
  size_t dummy_index;

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

  double random_number = Utility::RandomNumberGenerator::getRandomNumber<double>();

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

  size_t dummy_index;

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
                                            size_t& sampled_bin_index ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );

  // Calculate the sampled independent value
  IndepQuantity sample;

  if( random_number <= d_cutoff_cross_section_ratio )
  {
    sample = this->sampleCutoff( random_number, sampled_bin_index );
  }
  else if ( random_number > d_cutoff_cross_section_ratio )
  {
    sample = this->sampleDiscrete( random_number, sampled_bin_index );

    // Add the total number of cutoff bins to the sampled discrete bin
    sampled_bin_index += d_cutoff_distribution.size() - 1;
  }

  // Make sure the sample is valid
  testPostcondition( !IQT::isnaninf( sample ) );
  testPostcondition( sample >= this->getLowerBoundOfIndepVar() );
  testPostcondition( sample <= this->getUpperBoundOfIndepVar() );

  return sample;
}

// Return a random sample of the moment preserving discrete distribution using the random number and record the bin index
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sampleDiscrete(
                                            double random_number,
                                            size_t& sampled_bin_index ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= d_cutoff_cross_section_ratio );
  testPrecondition( random_number <= 1.0 );

  // Scale the random number
  UnnormCDFQuantity scaled_random_number =
        ( random_number - d_cutoff_cross_section_ratio )*d_scaling_parameter;

  // Get the bin index sampled
  sampled_bin_index =
    Utility::Search::binaryUpperBoundIndex<Utility::SECOND>( d_discrete_distribution.begin(),
                                           d_discrete_distribution.end(),
                                           scaled_random_number );

  return Utility::get<0>(d_discrete_distribution[sampled_bin_index]);
}

// Return a random sample of the cutoff tabular distribution using the random number and record the bin index
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sampleCutoff(
                                            double random_number,
                                            size_t& sampled_bin_index ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= d_cutoff_cross_section_ratio );

  // Calculate the sampled independent value
  IndepQuantity sample;

  // Scale the random number
  UnnormCDFQuantity scaled_random_number =
                random_number*d_max_cutoff_cdf;

  typename DistributionArray::const_iterator lower_bin_boundary =
        Utility::Search::binaryLowerBound<Utility::SECOND>( d_cutoff_distribution.begin(),
                                          d_cutoff_distribution.end(),
                                          scaled_random_number );

  // Calculate the sampled bin index
  sampled_bin_index =
            std::distance( d_cutoff_distribution.begin(), lower_bin_boundary );


  IndepQuantity indep_value = Utility::get<0>(*lower_bin_boundary);
  UnnormCDFQuantity cdf_diff =
    scaled_random_number - Utility::get<1>(*lower_bin_boundary);
  DepQuantity pdf_value = Utility::get<2>(*lower_bin_boundary);
  SlopeQuantity slope = Utility::get<3>(*lower_bin_boundary);

  // x = x0 + [sqrt(pdf(x0)^2 + 2m[cdf(x)-cdf(x0)]) - pdf(x0)]/m
  if( slope != Utility::QuantityTraits<SlopeQuantity>::zero() )
  {
    typedef typename Utility::QuantityTraits<DepQuantity>::template GetQuantityToPowerType<2>::type DepQuantitySqr;

    DepQuantitySqr term_1 = pdf_value*pdf_value;
    DepQuantitySqr term_2( 2.0*slope*cdf_diff );

    IndepQuantity term_3((Utility::sqrt( term_1 + term_2 ) - pdf_value)/slope);

    sample = indep_value + term_3;

  }
  // x = x0 + [cdf(x)-cdf(x0)]/pdf(x0) => L'Hopital's rule
  else
  {
    IndepQuantity term_2( cdf_diff/pdf_value );

    sample =  indep_value + term_2;
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
Utility::UnivariateDistributionType
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
  std::vector<double> independent_cutoff_values, dependent_cutoff_values,
    independent_discrete_values, dependent_discrete_values;

  this->reconstructOriginalUnitlessDistributions( independent_cutoff_values,
                                                  dependent_cutoff_values,
                                                  independent_discrete_values,
                                                  dependent_discrete_values );

  this->toStreamDistImpl( os,
                          std::make_pair( "interp", InterpolationPolicy::name() ),
                          std::make_pair( "independent cutoff values", independent_cutoff_values ),
                          std::make_pair( "dependent cutoff values", dependent_cutoff_values ),
                          std::make_pair( "independent discrete values", independent_discrete_values ),
                          std::make_pair( "dependent discrete values", dependent_discrete_values ),
                          std::make_pair( "cutoff mu", d_cutoff_mu ),
                          std::make_pair( "cutoff cs ratio", d_cutoff_cross_section_ratio ) );
}

// Method for testing if two objects are equivalent
template<typename InterpolationPolicy,
	 typename IndependentUnit,
	 typename DependentUnit>
bool UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::operator==(
 const UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>& other ) const
{
  return d_cutoff_distribution == other.d_cutoff_distribution &&
         d_discrete_distribution == other.d_discrete_distribution &&
         d_cutoff_mu == other.d_cutoff_mu &&
         d_cutoff_cross_section_ratio == other.d_cutoff_cross_section_ratio &&
         d_discrete_norm_constant == other.d_discrete_norm_constant &&
         d_cutoff_norm_constant == other.d_cutoff_norm_constant &&
         d_max_cutoff_cdf == other.d_max_cutoff_cdf;
}

// Method for testing if two objects are different
template<typename InterpolationPolicy,
	 typename IndependentUnit,
	 typename DependentUnit>
bool UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::operator!=(
 const UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>& other ) const
{
  return d_cutoff_distribution != other.d_cutoff_distribution ||
         d_discrete_distribution != other.d_discrete_distribution ||
         d_cutoff_mu != other.d_cutoff_mu ||
         d_cutoff_cross_section_ratio != other.d_cutoff_cross_section_ratio ||
         d_discrete_norm_constant != other.d_discrete_norm_constant ||
         d_cutoff_norm_constant != other.d_cutoff_norm_constant ||
         d_max_cutoff_cdf != other.d_max_cutoff_cdf;
}

// Initialize the distributions
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
void UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::initializeDistributionsFromRawData(
                      const std::vector<double>& independent_cutoff_values,
                      const std::vector<double>& dependent_cutoff_values,
                      const std::vector<double>& independent_discrete_values,
                      const std::vector<double>& dependent_discrete_values )
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
  std::vector<IndepQuantity> independent_quantities;

  this->convertUnitlessValues( independent_cutoff_values, independent_quantities );

  // Convert the raw dependent cutoff values to quantities
  std::vector<DepQuantity> dependent_quantities;

  this->convertUnitlessValues( dependent_cutoff_values, dependent_quantities );

  this->initializeCutoffDistribution( independent_quantities,
                                      dependent_quantities );
  }

  // Initialize the discrete distribution
  {
  // Convert the raw independent discrete values to quantities
  std::vector<IndepQuantity> independent_quantities;

  this->convertUnitlessValues( independent_discrete_values, independent_quantities );

  // Convert the raw dependent discrete values to quantities
  std::vector<DepQuantity> dependent_quantities;

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
                  const std::vector<InputIndepQuantity>& independent_values,
                  const std::vector<InputDepQuantity>& dependent_values )
{
  // Make sure that at least two points of the distribution are specified
  testPrecondition( independent_values.size() > 1 );
  // Make sure that every independent value has a dependent value
  testPrecondition( independent_values.size() == dependent_values.size() );
  // Make sure that the independent values are sorted
  testPrecondition( Utility::Sort::isSortedAscending( independent_values.begin(),
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
    Utility::get<0>(d_cutoff_distribution[i]) =
      IndepQuantity( independent_values[i] );

    // Scale the dependent values by the cross section ratio
    /*! \details The pdf values are for the tabular cutoff elastic distribution
     *  and must be re-scaled for the total hybrid elastic distribution.
     */
    Utility::get<2>(d_cutoff_distribution[i]) =
      DepQuantity( dependent_values[i]*d_cutoff_cross_section_ratio );
  }

  // Create a CDF from the raw distribution data
  d_cutoff_norm_constant =
    Utility::DataProcessor::calculateContinuousCDF<Utility::FIRST,Utility::THIRD,Utility::SECOND>( d_cutoff_distribution,
                                                               false );

  // Calculate the slopes of the PDF
  Utility::DataProcessor::calculateSlopes<Utility::FIRST,Utility::THIRD,Utility::FOURTH>( d_cutoff_distribution );

  // Find the raw CDF at the cutoff angle cosine
  typename DistributionArray::const_iterator lower_bin_boundary =
                Utility::Search::binaryLowerBound<Utility::FIRST>( d_cutoff_distribution.begin(),
                                                 d_cutoff_distribution.end(),
                                                 d_cutoff_mu );

  IndepQuantity indep_diff =
    d_cutoff_mu - Utility::get<0>(*lower_bin_boundary);

  // Set the max cutoff CDF
  d_max_cutoff_cdf = (Utility::get<1>(*lower_bin_boundary) + indep_diff*Utility::get<2>(*lower_bin_boundary)
                      + indep_diff*indep_diff*Utility::get<3>(*lower_bin_boundary)/2.0)
                /d_cutoff_cross_section_ratio;

  // Set the norm constant to the inverse max cdf value
  d_cutoff_norm_constant = 1.0/d_max_cutoff_cdf;

}

// Initialize the distribution
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
template<typename InputIndepQuantity, typename InputDepQuantity>
void UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::initializeDiscreteDistribution(
                const std::vector<InputIndepQuantity>& independent_values,
                const std::vector<InputDepQuantity>& dependent_values )
{
  // Make sure that every value has a probability assigned
  testPrecondition( independent_values.size() == dependent_values.size() );
  // Make sure that the bins are sorted
  testPrecondition( Utility::Sort::isSortedAscending( independent_values.begin(),
                                             independent_values.end() ) );

  // Resize the distribution array
  d_discrete_distribution.resize( independent_values.size() );

  // Assign the raw distribution data
  for( unsigned i = 0; i < dependent_values.size(); ++i )
  {
    Utility::get<0>(d_discrete_distribution[i]) =
      IndepQuantity( independent_values[i] );

    // Use an explicit cast to desired unit
    DepQuantity dep_quantity( dependent_values[i] );

    Utility::get<1>(d_discrete_distribution[i]) =
      Utility::getRawQuantity( dep_quantity );

    d_discrete_norm_constant += dep_quantity;
  }

  // Create a CDF from the raw distribution data
  Utility::DataProcessor::calculateDiscreteCDF<Utility::SECOND,Utility::SECOND>( d_discrete_distribution );
}

// Reconstruct original distribution
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
void UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::reconstructOriginalDistributions(
                 std::vector<IndepQuantity>& independent_cutoff_values,
                 std::vector<DepQuantity>& dependent_cutoff_values,
                 std::vector<IndepQuantity>& independent_discrete_values,
                 std::vector<DepQuantity>& dependent_discrete_values ) const
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
      Utility::get<0>(d_cutoff_distribution[i]);

    dependent_cutoff_values[i] =
      Utility::get<2>(d_cutoff_distribution[i])/d_cutoff_cross_section_ratio;
  }

  // Reconstruct the discrete distribution
  for( unsigned i = 0u; i < d_discrete_distribution.size(); ++i )
  {
    independent_discrete_values[i] =
      Utility::get<0>(d_discrete_distribution[i]);

    if( i != 0u )
    {
      dependent_discrete_values[i] = d_discrete_norm_constant*
        (Utility::get<1>(d_discrete_distribution[i]) - Utility::get<1>(d_discrete_distribution[i-1]));
    }
    else
    {
      dependent_discrete_values[i] =
        d_discrete_norm_constant*Utility::get<1>(d_discrete_distribution[i]);
    }
  }
}

// Reconstruct original distribution w/o units
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
void UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::reconstructOriginalUnitlessDistributions(
                 std::vector<double>& independent_cutoff_values,
                 std::vector<double>& dependent_cutoff_values,
                 std::vector<double>& independent_discrete_values,
                 std::vector<double>& dependent_discrete_values ) const
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
      Utility::getRawQuantity( Utility::get<0>(d_cutoff_distribution[i]) );
    dependent_cutoff_values[i] =
      Utility::getRawQuantity( Utility::get<2>(d_cutoff_distribution[i])/d_cutoff_cross_section_ratio );
  }

  // Reconstruct the discrete distribution
  for( unsigned i = 0u; i < d_discrete_distribution.size(); ++i )
  {
    independent_discrete_values[i] =
      Utility::getRawQuantity( Utility::get<0>(d_discrete_distribution[i]) );

    if( i != 0u )
    {
      dependent_discrete_values[i] =
        Utility::getRawQuantity( d_discrete_norm_constant )*
        (Utility::get<1>(d_discrete_distribution[i]) - Utility::get<1>(d_discrete_distribution[i-1]));
    }
    else
    {
      dependent_discrete_values[i] =
        Utility::get<1>(d_discrete_distribution[i])*Utility::getRawQuantity( d_discrete_norm_constant );
    }
  }
}

// Convert the unitless values to the correct units
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
template<typename Quantity>
void UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::convertUnitlessValues(
                                 const std::vector<double>& unitless_values,
                                 std::vector<Quantity>& quantities )
{
  // Resize the quantity array
  quantities.resize( unitless_values.size() );

  // Copy the bin boundaries
  for( unsigned i = 0u; i < unitless_values.size(); ++i )
    Utility::setQuantity( quantities[i], unitless_values[i] );
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
    if( Utility::get<2>(d_cutoff_distribution[i]) == DQT::zero() )
    {
      possible_zero = true;

      break;
    }
  }

  return possible_zero;
}

// // Test if the independent variable is compatible with Lin processing
// template<typename InterpolationPolicy,
//          typename IndependentUnit,
//          typename DependentUnit>
// bool UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::isIndepVarCompatibleWithProcessingType(
//                                          const LinIndepVarProcessingTag ) const
// {
//   return boost::is_same<typename InterpolationPolicy::IndepVarProcessingTag,LinIndepVarProcessingTag>::value;
// }

// // Test if the independent variable is compatible with Log processing
// template<typename InterpolationPolicy,
//          typename IndependentUnit,
//          typename DependentUnit>
// bool UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::isIndepVarCompatibleWithProcessingType(
//                                          const LogIndepVarProcessingTag ) const
// {
//   return boost::is_same<typename InterpolationPolicy::IndepVarProcessingTag,LogIndepVarProcessingTag>::value;
// }

// // Test if the dependent variable is compatible with Lin processing
// template<typename InterpolationPolicy,
//          typename IndependentUnit,
//          typename DependentUnit>
// bool UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::isDepVarCompatibleWithProcessingType(
//                                            const LinDepVarProcessingTag ) const
// {
//   return boost::is_same<typename InterpolationPolicy::DepVarProcessingTag,LinDepVarProcessingTag>::value;
// }

// // Test if the dependent variable is compatible with Log processing
// template<typename InterpolationPolicy,
//          typename IndependentUnit,
//          typename DependentUnit>
// bool UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::isDepVarCompatibleWithProcessingType(
//                                            const LogDepVarProcessingTag ) const
// {
//   return boost::is_same<typename InterpolationPolicy::DepVarProcessingTag,LogDepVarProcessingTag>::value;
// }

// Verify that the values are valid
template<typename InterpolationPolicy,
	 typename IndependentUnit,
	 typename DependentUnit>
template<typename InputIndepQuantity, typename InputDepQuantity>
void UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::verifyValidValues(
            const std::vector<InputIndepQuantity>& independent_cutoff_values,
            const std::vector<InputDepQuantity>& dependent_cutoff_values,
            const std::vector<InputIndepQuantity>& independent_discrete_values,
            const std::vector<InputDepQuantity>& dependent_discrete_values,
            const InputIndepQuantity cutoff_angle_cosine,
            const double cutoff_cross_section_ratio)
{

}

// Save the distribution to an archive
template<typename InterpolationPolicy,
	 typename IndependentUnit,
	 typename DependentUnit>
template<typename Archive>
void UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::save( Archive& ar, const unsigned version ) const
{
  // Save the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Save the local member data
  ar & BOOST_SERIALIZATION_NVP( d_cutoff_distribution );
  ar & BOOST_SERIALIZATION_NVP( d_discrete_distribution );
  ar & BOOST_SERIALIZATION_NVP( d_discrete_norm_constant );
  ar & BOOST_SERIALIZATION_NVP( d_cutoff_norm_constant );
  ar & BOOST_SERIALIZATION_NVP( d_max_cutoff_cdf );
  ar & BOOST_SERIALIZATION_NVP( d_cutoff_mu );
  ar & BOOST_SERIALIZATION_NVP( d_cutoff_cross_section_ratio );
  ar & BOOST_SERIALIZATION_NVP( d_scaling_parameter );
}

// Load the distribution from an archive
template<typename InterpolationPolicy,
	 typename IndependentUnit,
	 typename DependentUnit>
template<typename Archive>
void UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::load( Archive& ar, const unsigned version )
{
  // Load the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Load the local member data
  ar & BOOST_SERIALIZATION_NVP( d_cutoff_distribution );
  ar & BOOST_SERIALIZATION_NVP( d_discrete_distribution );
  ar & BOOST_SERIALIZATION_NVP( d_discrete_norm_constant );
  ar & BOOST_SERIALIZATION_NVP( d_cutoff_norm_constant );
  ar & BOOST_SERIALIZATION_NVP( d_max_cutoff_cdf );
  ar & BOOST_SERIALIZATION_NVP( d_cutoff_mu );
  ar & BOOST_SERIALIZATION_NVP( d_cutoff_cross_section_ratio );
  ar & BOOST_SERIALIZATION_NVP( d_scaling_parameter );
}

} // end MonteCarlo namespace

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::UnitAwareHybridElasticDistribution<Utility::LinLin,void,void> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, UnitAwareHybridElasticDistribution<Utility::LinLin,void,void> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::UnitAwareHybridElasticDistribution<Utility::LogLin,void,void> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, UnitAwareHybridElasticDistribution<Utility::LogLin,void,void> );

#endif // end MONTE_CARLO_HYBRID_ELASTIC_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_HybridElasticDistribution_def.hpp
//---------------------------------------------------------------------------//
