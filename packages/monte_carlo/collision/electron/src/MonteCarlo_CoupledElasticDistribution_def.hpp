//---------------------------------------------------------------------------//
//!
//! \file   Utility_CoupledElasticDistribution_def.hpp
//! \author Luke Kersting
//! \brief  Coupled elastic distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COUPLED_ELASTIC_DISTRIBUTION_DEF_HPP
#define MONTE_CARLO_COUPLED_ELASTIC_DISTRIBUTION_DEF_HPP

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

BOOST_SERIALIZATION_CLASS3_EXPORT_IMPLEMENT( UnitAwareCoupledElasticDistribution, MonteCarlo );

namespace MonteCarlo{

// Default constructor
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::UnitAwareCoupledElasticDistribution()
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
UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::UnitAwareCoupledElasticDistribution(
                  const std::vector<double>& independent_values,
                  const std::vector<double>& dependent_values,
                  const double& moliere_screening_constant,
                  const double& cutoff_cross_section_ratio )
  : d_distribution( independent_values.size() ),
    d_moliere_eta( moliere_screening_constant ),
    d_cutoff_cross_section_ratio( cutoff_cross_section_ratio ),
    d_scaling_parameter( 1.0/( 1.0 - cutoff_cross_section_ratio ) ),
    d_pdf_parameter( DQT::zero() ),
    d_cdf_parameter( ( 1.0 - cutoff_cross_section_ratio )*moliere_screening_constant*1e6 ),
    d_norm_constant( DNQT::zero() ),
    d_scaled_norm_constant( DNQT::zero() ),
    d_max_cdf( UCQT::zero() )
{
  // Make sure there is at lease one bin
  testPrecondition( independent_values.size() > 1 );
  testPrecondition( dependent_values.size() == independent_values.size() );
  // Make sure that the bins are sorted
  testPrecondition( Utility::Sort::isSortedAscending( independent_values.begin(),
                                                      independent_values.end() ) );
  // Make sure that the independent_values have the proper range
  testPrecondition( independent_values.front() == -1.0 );
  testPrecondition( independent_values.back() == 0.999999 );
  // Make sure the Moliere screeneding constant is valid
  testPrecondition( moliere_screening_constant > 0.0 );
  // Make sure the cutoff cross section ratio is valid
  testPrecondition( cutoff_cross_section_ratio > 0.0 );
  testPrecondition( cutoff_cross_section_ratio <= 1.0 );

  // Verify that the values are valid
  this->verifyValidValues( independent_values,
                           dependent_values,
                           moliere_screening_constant,
                           cutoff_cross_section_ratio );

  this->initializeDistributionFromRawData( independent_values,
                                           dependent_values );

  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}


// Constructor
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
template<typename InputIndepQuantity, typename InputDepQuantity>
UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::UnitAwareCoupledElasticDistribution(
                  const std::vector<InputIndepQuantity>& independent_values,
                  const std::vector<InputDepQuantity>& dependent_values,
                  const double& moliere_screening_constant,
                  const double& cutoff_cross_section_ratio )
  : d_distribution( independent_values.size() ),
    d_moliere_eta( moliere_screening_constant ),
    d_cutoff_cross_section_ratio( cutoff_cross_section_ratio ),
    d_scaling_parameter( 1.0/( 1.0 - cutoff_cross_section_ratio ) ),
    d_pdf_parameter( DQT::zero() ),
    d_cdf_parameter( ( 1.0 - cutoff_cross_section_ratio )*moliere_screening_constant*1e6 ),
    d_norm_constant( DNQT::zero() ),
    d_scaled_norm_constant( DNQT::zero() ),
    d_max_cdf( UCQT::zero() )
{
  // Make sure there is at lease one bin
  testPrecondition( independent_values.size() > 1 );
  testPrecondition( dependent_values.size() == independent_values.size() );
  // Make sure that the bins are sorted
  testPrecondition( Utility::Sort::isSortedAscending( independent_values.begin(),
                                                      independent_values.end() ) );
  // Make sure that the independent_values have the proper range
  testPrecondition( independent_values.front() == InputIndepQuantity(-1.0) );
  testPrecondition( independent_values.back() == InputIndepQuantity(0.999999) );
  // Make sure the Moliere screeneding constant is valid
  testPrecondition( moliere_screening_constant > 0.0 );
  // Make sure the cutoff cross section ratio is valid
  testPrecondition( cutoff_cross_section_ratio > 0.0 );
  testPrecondition( cutoff_cross_section_ratio <= 1.0 );

  // Verify that the values are valid
  this->verifyValidValues( independent_values,
                           dependent_values,
                           moliere_screening_constant,
                           cutoff_cross_section_ratio );

  this->initializeDistribution( independent_values, dependent_values );

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
UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::UnitAwareCoupledElasticDistribution(
 const UnitAwareCoupledElasticDistribution<InterpolationPolicy,InputIndepUnit,InputDepUnit>& dist_instance )
  : d_distribution(),
    d_moliere_eta( dist_instance.d_moliere_eta ),
    d_cutoff_cross_section_ratio( dist_instance.d_cutoff_cross_section_ratio ),
    d_scaling_parameter( dist_instance.d_scaling_parameter ),
    d_pdf_parameter(),
    d_cdf_parameter( dist_instance.d_cdf_parameter ),
    d_norm_constant(),
    d_scaled_norm_constant(),
    d_max_cdf()
{
  // Make sure the distribution is valid
  testPrecondition( dist_instance.d_distribution.size() > 0 );

  typedef typename UnitAwareCoupledElasticDistribution<InterpolationPolicy,InputIndepUnit,InputDepUnit>::IndepQuantity InputIndepQuantity;

  typedef typename UnitAwareCoupledElasticDistribution<InterpolationPolicy,InputIndepUnit,InputDepUnit>::DepQuantity InputDepQuantity;

  // Reconstruct the original input distribution
  std::vector<InputIndepQuantity> input_indep_values;
  std::vector<InputDepQuantity> input_dep_values;

  dist_instance.reconstructOriginalDistribution( input_indep_values,
                                                 input_dep_values );

  this->initializeDistribution( input_indep_values, input_dep_values );

  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Copy constructor (copying from unitless distribution only)
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::UnitAwareCoupledElasticDistribution( const UnitAwareCoupledElasticDistribution<InterpolationPolicy,void,void>& unitless_dist_instance, int )
  : d_distribution(),
    d_moliere_eta( unitless_dist_instance.d_moliere_eta ),
    d_cutoff_cross_section_ratio( unitless_dist_instance.d_cutoff_cross_section_ratio ),
    d_scaling_parameter( unitless_dist_instance.d_scaling_parameter ),
    d_pdf_parameter(),
    d_cdf_parameter( unitless_dist_instance.d_cdf_parameter ),
    d_norm_constant(),
    d_scaled_norm_constant(),
    d_max_cdf()
{
  // Make sure the distribution is valid
  testPrecondition( unitless_dist_instance.d_distribution.size() > 0 );

  // Reconstruct the original input distribution
  std::vector<double> input_indep_values, input_dep_values;

  unitless_dist_instance.reconstructOriginalDistribution( input_indep_values,
                                                          input_dep_values );

  this->initializeDistributionFromRawData( input_indep_values,
                                           input_dep_values );
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
UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>
UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::fromUnitlessDistribution( const UnitAwareCoupledElasticDistribution<InterpolationPolicy,void,void>& unitless_distribution )
{
  return ThisType( unitless_distribution, 0 );
}

// Assignment operator
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>&
UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::operator=(
  const UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>& dist_instance )
{
  // Make sure the distribution is valid
  testPrecondition( dist_instance.d_distribution.size() > 0 );

  if( this != &dist_instance )
  {
    d_distribution = dist_instance.d_distribution;
    d_moliere_eta = dist_instance.d_moliere_eta;
    d_cutoff_cross_section_ratio = dist_instance.d_cutoff_cross_section_ratio;
    d_scaling_parameter = dist_instance.d_scaling_parameter;
    d_pdf_parameter = dist_instance.d_pdf_parameter;
    d_cdf_parameter = dist_instance.d_cdf_parameter;
    d_norm_constant = dist_instance.d_norm_constant;
    d_scaled_norm_constant = dist_instance.d_scaled_norm_constant;
    d_max_cdf = dist_instance.d_max_cdf;
  }

  return *this;
}

// Evaluate the distribution
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::DepQuantity
UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::evaluate(
 const typename UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  // Make sure the indep var variable is within its limits
  testPrecondition( indep_var_value >= this->getLowerBoundOfIndepVar() );
  testPrecondition( indep_var_value <= this->getUpperBoundOfIndepVar() );

  // Check to see if the tabular or analytical portion will be evaluated
  if( indep_var_value > this->getCutoffBoundOfIndepVar() )
  { // evaluate the screened Rutherford analytical peak

    // Change in angle cosine
    double delta_mu = ( 1.0L - indep_var_value );

    // cutoff_cs_ratio*cutoff_pdf*( 1 - mu_c + eta )**2/ ( 1 - mu   + eta )**2;
    return d_pdf_parameter/
                ( ( delta_mu + d_moliere_eta )*( delta_mu + d_moliere_eta ) );
  }
  else if( indep_var_value == this->getCutoffBoundOfIndepVar() )
  {
    return Utility::get<2>(d_distribution.back());
  }
  else
  { // evaluate the cutoff tabular large angle distribution

    typename DistributionArray::const_iterator start, end, lower_bin_boundary,
      upper_bin_boundary;
    start = d_distribution.begin();
    end = d_distribution.end();

    lower_bin_boundary =
      Utility::Search::binaryLowerBound<Utility::FIRST>( start,
                                                         end,
                                                         indep_var_value );

    upper_bin_boundary = lower_bin_boundary;
    ++upper_bin_boundary;

    return InterpolationPolicy::interpolate(
                                        Utility::get<0>(*lower_bin_boundary),
                                        Utility::get<0>(*upper_bin_boundary),
                                        indep_var_value,
                                        Utility::get<2>(*lower_bin_boundary),
                                        Utility::get<2>(*upper_bin_boundary) );
  }
}

// Evaluate the PDF
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::InverseIndepQuantity
UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::evaluatePDF(
 const typename UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  // Make sure the indep var variable is within its limits
  testPrecondition( indep_var_value >= this->getLowerBoundOfIndepVar() );
  testPrecondition( indep_var_value <= this->getUpperBoundOfIndepVar() );

  // Check to see if the tabular or analytical portion will be evaluated
  if( indep_var_value > this->getCutoffBoundOfIndepVar() )
    return this->evaluate( indep_var_value )*d_norm_constant;
  else
    return this->evaluate( indep_var_value )*d_scaled_norm_constant;

}

// Evaluate the CDF
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
double UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::evaluateCDF(
  const typename UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  // Make sure the indep var variable is within its limits
  testPrecondition( indep_var_value >= this->getLowerBoundOfIndepVar() );
  testPrecondition( indep_var_value <= this->getUpperBoundOfIndepVar() );

  if( indep_var_value == this->getLowerBoundOfIndepVar() )
    return 0.0;
  else if( indep_var_value < this->getCutoffBoundOfIndepVar() )
  {
    typename DistributionArray::const_iterator start, end, lower_bin_boundary;
    start = d_distribution.begin();
    end = d_distribution.end();

    lower_bin_boundary =
      Utility::Search::binaryLowerBound<Utility::FIRST>( start,
                                                         end,
                                                         indep_var_value );

    IndepQuantity indep_diff =
      indep_var_value - Utility::get<0>(*lower_bin_boundary);

    return (Utility::get<1>(*lower_bin_boundary) +
            indep_diff*Utility::get<2>(*lower_bin_boundary) +
            indep_diff*indep_diff*Utility::get<3>(*lower_bin_boundary)/2.0)*
      d_scaled_norm_constant;
  }
  else if( indep_var_value == this->getCutoffBoundOfIndepVar() )
    return d_cutoff_cross_section_ratio;
  else if( indep_var_value == this->getUpperBoundOfIndepVar() )
    return 1.0;
  else // indep_var_value > Cutoff Bound Of Indep Var
  {
  // cutoff_cs_ratio + (1 - cutoff_cs_ratio)*eta/mu_c*( mu - mu_c )/( eta + 1 - mu )
  return d_cutoff_cross_section_ratio +
         d_cdf_parameter*( indep_var_value - ElasticElectronTraits::mu_peak )/
                         ( d_moliere_eta + (1.0 - indep_var_value) );
  }
}

// Return a random sample from the distribution
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
inline typename UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sample() const
{
  double random_number =
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  size_t dummy_index;

  return this->sampleImplementation( random_number, dummy_index );
}

// Return a random sample and record the number of trials
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sampleAndRecordTrials(
                           Utility::DistributionTraits::Counter& trials ) const
{
  ++trials;

  return this->sample();
}

// Return a random sample and bin index from the distribution
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sampleAndRecordBinIndex(
                                            size_t& sampled_bin_index ) const
{
  double random_number =
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleImplementation( random_number, sampled_bin_index );
}

// Return a sample from the distribution at the given CDF value
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sampleWithRandomNumber(
                                             const double random_number ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );

  size_t dummy_index;

  return this->sampleImplementation( random_number, dummy_index );
}

// Return a random sample from the corresponding CDF in a subrange
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sampleInSubrange(
 const typename UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity max_indep_var ) const
{
  // Make sure the maximum indep var is valid
  testPrecondition( max_indep_var >= this->getLowerBoundOfIndepVar() );

  double random_number =
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleWithRandomNumberInSubrange( random_number,
                                                 max_indep_var );
}

// Return a random sample from the distribution at the given CDF value in a subrange
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
inline typename UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sampleWithRandomNumberInSubrange(
 const double random_number,
 const typename UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity max_indep_var ) const
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
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sampleImplementation(
                                            double random_number,
                                            size_t& sampled_bin_index ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );

  // Calculate the sampled independent value
  IndepQuantity sample;

  // Sample the screened Rutherford analytical distribution
  if ( random_number == d_cutoff_cross_section_ratio )
  {
    // Set the sampled bin index to the last bin
    sampled_bin_index = d_distribution.size() - 1;

    return this->getCutoffBoundOfIndepVar();
  }
  else if ( random_number >= d_cutoff_cross_section_ratio )
  {
    // Set the sampled bin index to the last bin
    sampled_bin_index = d_distribution.size() - 1;

    double scaled_random_number =
        ( random_number - d_cutoff_cross_section_ratio )*d_scaling_parameter;

    sample = this->sampleScreenedRutherford( scaled_random_number );
  }
  else
  {
    sample = this->sampleCutoff( random_number, sampled_bin_index );
  }

  return sample;
}

// Return a random sample of the screened Rutherford analytical peak using the random number
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sampleScreenedRutherford(
                                            double random_number ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );

  // Calculate the sampled independent value
  IndepQuantity sample;

  // NOTE: This method gives and sampled angle > 1 for a random number of 1
  /* mu = ( mu_c eta + ( 1 + eta )( 1 - mu_c )*random_number )/
   *      (      eta +            ( 1 - mu_c )*random_number )
   */
//  sample = ( ElasticElectronTraits::mu_peak*d_moliere_eta +
//           (1.0L + d_moliere_eta)*ElasticElectronTraits::delta_mu_peak*random_number ) /
//           ( d_moliere_eta + ElasticElectronTraits::delta_mu_peak*random_number );


  double delta_rand = ElasticElectronTraits::delta_mu_peak*random_number;

  /* mu = ( eta*( mu_c + ( 1 - mu_c )*random_number ) + ( 1 - mu_c )*random_number )/
   *      ( eta +            ( 1 - mu_c )*random_number )
   */
  sample = ( d_moliere_eta*( ElasticElectronTraits::mu_peak + delta_rand ) + delta_rand )/
           ( d_moliere_eta                              + delta_rand );

  // Make sure the sample is valid
  testPostcondition( !IQT::isnaninf( sample ) );
  testPostcondition( sample >= this->getCutoffBoundOfIndepVar() );
  testPostcondition( sample <= this->getUpperBoundOfIndepVar() );

  return sample;
}

// Return a random sample of the cutoff tabular distribution using the random number and record the bin index
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sampleCutoff(
                                            double random_number,
                                            size_t& sampled_bin_index ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= d_cutoff_cross_section_ratio );

  // Calculate the sampled independent value
  IndepQuantity sample;

  UnnormCDFQuantity scaled_random_number;

  // Scale the random number
  scaled_random_number = random_number*d_max_cdf;

  typename DistributionArray::const_iterator start, end, lower_bin_boundary;
  start = d_distribution.begin();
  end = d_distribution.end();

  lower_bin_boundary =
    Utility::Search::binaryLowerBound<Utility::SECOND>( start,
                                                        end,
                                                        scaled_random_number);

  // Calculate the sampled bin index
  sampled_bin_index = std::distance(d_distribution.begin(),lower_bin_boundary);

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

    sample = indep_value + term_2;
  }

  // Make sure the sample is valid
  testPostcondition( !IQT::isnaninf( sample ) );
  testPostcondition( sample >= this->getLowerBoundOfIndepVar() );
  testPostcondition( sample <= this->getCutoffBoundOfIndepVar() );

  return sample;
}

// Return the upper bound of the distribution independent variable
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
auto UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::getUpperBoundOfIndepVar() const -> IndepQuantity
{
  return IQT::one();
}

// Return the cutoff bound of the distribution independent variable
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
auto UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::getCutoffBoundOfIndepVar() const -> IndepQuantity
{
  return IQT::initializeQuantity(0.999999);
}

// Return the lower bound of the distribution independent variable
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
auto UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::getLowerBoundOfIndepVar() const -> IndepQuantity
{
  return IQT::initializeQuantity(-1.0);
}

// Return the distribution type
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
Utility::UnivariateDistributionType
UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::getDistributionType() const
{
  return ThisType::distribution_type;
}


// Return the moliere screening constant for the distribution
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
double
UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::getMoliereScreeningConstant() const
{
  return ThisType::d_moliere_eta;
}

// Return the cutoff cross section ratio for the distribution
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
double
UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::getCutoffCrossSectionRatio() const
{
  return ThisType::d_cutoff_cross_section_ratio;
}

// Test if the distribution is continuous
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
bool UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::isContinuous() const
{
  return true;
}

// Method for placing the object in an output stream
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
void UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::toStream(
                                                       std::ostream& os ) const
{
  std::vector<double> independent_values, dependent_values;

  this->reconstructOriginalUnitlessDistribution( independent_values,
                                                 dependent_values );

  this->toStreamImpl( os,
                      std::make_pair( "interp", InterpolationPolicy::name() ),
                      std::make_pair( "independent values", independent_values ),
                      std::make_pair( "dependent values", dependent_values ),
                      std::make_pair( "moliere eta", d_moliere_eta ),
                      std::make_pair( "cutoff cs ratio", d_cutoff_cross_section_ratio ) );
}

// Method for testing if two objects are equivalent
template<typename InterpolationPolicy,
	 typename IndependentUnit,
	 typename DependentUnit>
bool UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::operator==(
 const UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>& other ) const
{
  return d_distribution == other.d_distribution &&
         d_moliere_eta == other.d_moliere_eta &&
         d_cutoff_cross_section_ratio == other.d_cutoff_cross_section_ratio &&
         d_norm_constant == other.d_norm_constant &&
         d_scaled_norm_constant == other.d_scaled_norm_constant &&
         d_max_cdf == other.d_max_cdf;
}

// Method for testing if two objects are different
template<typename InterpolationPolicy,
	 typename IndependentUnit,
	 typename DependentUnit>
bool UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::operator!=(
 const UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>& other ) const
{
  return d_distribution != other.d_distribution ||
         d_moliere_eta != other.d_moliere_eta ||
         d_cutoff_cross_section_ratio != other.d_cutoff_cross_section_ratio ||
         d_norm_constant != other.d_norm_constant ||
         d_scaled_norm_constant != other.d_scaled_norm_constant ||
         d_max_cdf != other.d_max_cdf;
}

// Initialize the distribution
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
void UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::initializeDistributionFromRawData(
                              const std::vector<double>& independent_values,
                              const std::vector<double>& dependent_values )
{
  // Make sure there is at least one bin
  testPrecondition( independent_values.size() > 1 );
  testPrecondition( dependent_values.size() == independent_values.size() );
  // Make sure that the independent_values have the proper range
  testPrecondition( independent_values.front() == -1.0 );
  testPrecondition( independent_values.back() == 0.999999 );

  // Convert the raw independent values to quantities
  std::vector<IndepQuantity> independent_quantities;

  this->convertUnitlessValues( independent_values, independent_quantities );

  // Convert the raw dependent values to quantities
  std::vector<DepQuantity> dependent_quantities;

  this->convertUnitlessValues( dependent_values, dependent_quantities );

  this->initializeDistribution( independent_quantities,
                                dependent_quantities );
}

// Initialize the distribution
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
template<typename InputIndepQuantity, typename InputDepQuantity>
void UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::initializeDistribution(
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
  testPrecondition( independent_values.front() == IndepQuantity(-1.0) );
  testPrecondition( independent_values.back() == IndepQuantity(0.999999) );

  // Resize the distribution
  d_distribution.resize( independent_values.size() );


  // Assign the raw distribution data
  for( unsigned i = 0; i < independent_values.size(); ++i )
  {
    Utility::get<0>(d_distribution[i]) =
      IndepQuantity( independent_values[i] );

    // Scale the dependent values by the cross section ratio
    /*! \details The pdf values are for the tabular cutoff elastic distribution
     *  and must be re-scaled for the total elastic distribution.
     */
    Utility::get<2>(d_distribution[i]) =
      DepQuantity( dependent_values[i]*d_cutoff_cross_section_ratio );
  }

  /* Set the PDF evaluating parameter
   * ( cutoff_cs_ratio * cutoff_pdf * ( 1 - mu_c + eta )**2 )
   */
  d_pdf_parameter = Utility::get<2>(d_distribution.back())*
    ( ElasticElectronTraits::delta_mu_peak + d_moliere_eta )*( ElasticElectronTraits::delta_mu_peak + d_moliere_eta );

  // Create a CDF from the raw distribution data
  d_norm_constant =
    Utility::DataProcessor::calculateContinuousCDF<Utility::FIRST,Utility::THIRD,Utility::SECOND>( d_distribution, false );

  // Scale norm constant by the cross section ratio
  /*! \details The norm constant given by the calculateContinuousCDF function
   *  is for the tabular cutoff elastic distribution and must be re-scaled for
   *  the total elastic distribution.
   */
  d_scaled_norm_constant = d_norm_constant*d_cutoff_cross_section_ratio;

  // Set the max CDF for the total elastic distribution
  d_max_cdf = 1.0/d_scaled_norm_constant;

  /* Set the CDF evaluating parameter
   * ( (1 - cutoff_cs_ratio)*eta/mu_c )
   */
  d_cdf_parameter = (1.0 - d_cutoff_cross_section_ratio )*d_moliere_eta*1e6;

  // Calculate the slopes of the PDF
  Utility::DataProcessor::calculateSlopes<Utility::FIRST,Utility::THIRD,Utility::FOURTH>( d_distribution );
}

// Reconstruct original distribution
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
void UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::reconstructOriginalDistribution(
                         std::vector<IndepQuantity>& independent_values,
                         std::vector<DepQuantity>& dependent_values ) const
{
  // Resize the arrays
  independent_values.resize( d_distribution.size() );
  dependent_values.resize( d_distribution.size() );

  for( unsigned i = 0u; i < d_distribution.size(); ++i )
  {
    independent_values[i] = Utility::get<0>(d_distribution[i]);

    dependent_values[i] =
      Utility::get<2>(d_distribution[i])/d_cutoff_cross_section_ratio;
  }
}

// Reconstruct original distribution w/o units
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
void UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::reconstructOriginalUnitlessDistribution(
                               std::vector<double>& independent_values,
                               std::vector<double>& dependent_values ) const
{
  // Resize the arrays
  independent_values.resize( d_distribution.size() );
  dependent_values.resize( d_distribution.size() );

  for( unsigned i = 0u; i < d_distribution.size(); ++i )
  {
    independent_values[i] =
      Utility::getRawQuantity( Utility::get<0>(d_distribution[i]) );

    dependent_values[i] =
      Utility::getRawQuantity( Utility::get<2>(d_distribution[i])/d_cutoff_cross_section_ratio );
  }
}

// Convert the unitless values to the correct units
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
template<typename Quantity>
void UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::convertUnitlessValues(
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
bool UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::canDepVarBeZeroInIndepBounds() const
{
  bool possible_zero = false;

  for( size_t i = 0; i < d_distribution.size(); ++i )
  {
    if( Utility::get<2>(d_distribution[i]) == DQT::zero() )
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
// bool UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::isIndepVarCompatibleWithProcessingType(
//                                          const LinIndepVarProcessingTag ) const
// {
//   return boost::is_same<typename InterpolationPolicy::IndepVarProcessingTag,LinIndepVarProcessingTag>::value;
// }

// // Test if the independent variable is compatible with Log processing
// template<typename InterpolationPolicy,
//          typename IndependentUnit,
//          typename DependentUnit>
// bool UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::isIndepVarCompatibleWithProcessingType(
//                                          const LogIndepVarProcessingTag ) const
// {
//   return boost::is_same<typename InterpolationPolicy::IndepVarProcessingTag,LogIndepVarProcessingTag>::value;
// }

// // Test if the dependent variable is compatible with Lin processing
// template<typename InterpolationPolicy,
//          typename IndependentUnit,
//          typename DependentUnit>
// bool UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::isDepVarCompatibleWithProcessingType(
//                                            const LinDepVarProcessingTag ) const
// {
//   return boost::is_same<typename InterpolationPolicy::DepVarProcessingTag,LinDepVarProcessingTag>::value;
// }

// // Test if the dependent variable is compatible with Log processing
// template<typename InterpolationPolicy,
//          typename IndependentUnit,
//          typename DependentUnit>
// bool UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::isDepVarCompatibleWithProcessingType(
//                                            const LogDepVarProcessingTag ) const
// {
//   return boost::is_same<typename InterpolationPolicy::DepVarProcessingTag,LogDepVarProcessingTag>::value;
// }

// Verify that the values are valid
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
template<typename InputIndepQuantity, typename InputDepQuantity>
void UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::verifyValidValues(
                    const std::vector<InputIndepQuantity>& independent_values,
                    const std::vector<InputDepQuantity>& dependent_values,
                    const double& moliere_screening_constant,
                    const double& cutoff_cross_section_ratio )
{

}

// Save the distribution to an archive
template<typename InterpolationPolicy,
	 typename IndependentUnit,
	 typename DependentUnit>
template<typename Archive>
void UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::save( Archive& ar, const unsigned version ) const
{
  // Save the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Save the local member data
  ar & BOOST_SERIALIZATION_NVP( d_distribution );
  ar & BOOST_SERIALIZATION_NVP( d_norm_constant );
  ar & BOOST_SERIALIZATION_NVP( d_scaled_norm_constant );
  ar & BOOST_SERIALIZATION_NVP( d_max_cdf );
  ar & BOOST_SERIALIZATION_NVP( d_min_indep_var );
  ar & BOOST_SERIALIZATION_NVP( d_max_indep_var );
  ar & BOOST_SERIALIZATION_NVP( d_moliere_eta );
  ar & BOOST_SERIALIZATION_NVP( d_cutoff_cross_section_ratio );
  ar & BOOST_SERIALIZATION_NVP( d_scaling_parameter );
  ar & BOOST_SERIALIZATION_NVP( d_pdf_parameter );
  ar & BOOST_SERIALIZATION_NVP( d_cdf_parameter );
}

// Load the distribution from an archive
template<typename InterpolationPolicy,
	 typename IndependentUnit,
	 typename DependentUnit>
template<typename Archive>
void UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::load( Archive& ar, const unsigned version )
{
  // Load the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Load the local member data
  ar & BOOST_SERIALIZATION_NVP( d_distribution );
  ar & BOOST_SERIALIZATION_NVP( d_norm_constant );
  ar & BOOST_SERIALIZATION_NVP( d_scaled_norm_constant );
  ar & BOOST_SERIALIZATION_NVP( d_max_cdf );
  ar & BOOST_SERIALIZATION_NVP( d_min_indep_var );
  ar & BOOST_SERIALIZATION_NVP( d_max_indep_var );
  ar & BOOST_SERIALIZATION_NVP( d_moliere_eta );
  ar & BOOST_SERIALIZATION_NVP( d_cutoff_cross_section_ratio );
  ar & BOOST_SERIALIZATION_NVP( d_scaling_parameter );
  ar & BOOST_SERIALIZATION_NVP( d_pdf_parameter );
  ar & BOOST_SERIALIZATION_NVP( d_cdf_parameter );
}

} // end MonteCarlo namespace

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::UnitAwareCoupledElasticDistribution<Utility::LinLin,void,void> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, UnitAwareCoupledElasticDistribution<Utility::LinLin,void,void> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::UnitAwareCoupledElasticDistribution<Utility::LogLin,void,void> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, UnitAwareCoupledElasticDistribution<Utility::LogLin,void,void> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::UnitAwareCoupledElasticDistribution<Utility::LinNudgedLogCos,void,void> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, UnitAwareCoupledElasticDistribution<Utility::LinNudgedLogCos,void,void> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( MonteCarlo::UnitAwareCoupledElasticDistribution<Utility::LogNudgedLogCos,void,void> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, UnitAwareCoupledElasticDistribution<Utility::LogNudgedLogCos,void,void> );

#endif // end MONTE_CARLO_COUPLED_ELASTIC_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_CoupledElasticDistribution_def.hpp
//---------------------------------------------------------------------------//
