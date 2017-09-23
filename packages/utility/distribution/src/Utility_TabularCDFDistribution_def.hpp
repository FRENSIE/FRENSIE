//---------------------------------------------------------------------------//
//!
//! \file   Utility_TabularCDFDistribution_def.hpp
//! \author Luke Kersting
//! \brief  Tabular CDF distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TABULAR_CDF_DISTRIBUTION_DEF_HPP
#define UTILITY_TABULAR_CDF_DISTRIBUTION_DEF_HPP

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

namespace Utility{

// Explicit instantiation (extern declaration)
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareTabularCDFDistribution<LinLin,void,void> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareTabularCDFDistribution<LinLog,void,void> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareTabularCDFDistribution<LogLin,void,void> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareTabularCDFDistribution<LogLog,void,void> );

// Default constructor
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::UnitAwareTabularCDFDistribution()
{ /* ... */ }

// Basic constructor (potentially dangerous)
/*! \details The independent values are assumed to be sorted (lowest to
 * highest). If cdf values are provided the pdf will not be calculated.
 * Evaluating the distribution or the pdf will always return a result zero!
 */
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::UnitAwareTabularCDFDistribution(
                  const Teuchos::Array<double>& independent_values,
                  const Teuchos::Array<double>& dependent_values,
                  const bool interpret_dependent_values_as_cdf )
  : d_distribution( independent_values.size() ),
    d_norm_constant( DNQT::zero() ),
    d_interpret_dependent_values_as_cdf( interpret_dependent_values_as_cdf )
{
  // Make sure there is at lease one bin
  testPrecondition( independent_values.size() > 1 );
  testPrecondition( dependent_values.size() == independent_values.size() );
  // Make sure that the bins are sorted
  testPrecondition( Sort::isSortedAscending( independent_values.begin(),
                                             independent_values.end() ) );

  this->initializeDistributionFromRawData( independent_values,
                                           dependent_values );
}

// CDF constructor
/*! \details The independent values are assumed to be sorted (lowest to
 * highest). Since cdf values are provided the pdf will not be calculated.
 * Evaluating the distribution or the pdf will always return a result zero!
 */
template<typename InterpolationPolicy,
typename IndependentUnit,
typename DependentUnit>
template<typename InputIndepQuantity>
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::UnitAwareTabularCDFDistribution(
const Teuchos::Array<InputIndepQuantity>& independent_values,
const Teuchos::Array<double>& cdf_values )
: d_distribution( independent_values.size() ),
  d_norm_constant( DNQT::zero() ),
  d_interpret_dependent_values_as_cdf( true )
{
  // Make sure there is at lease one bin
  testPrecondition( independent_values.size() > 1 );
  testPrecondition( cdf_values.size() == independent_values.size() );
  // Make sure that the bins are sorted
  testPrecondition( Sort::isSortedAscending( independent_values.begin(),
                                             independent_values.end() ) );

  this->initializeDistributionFromCDF( independent_values, cdf_values );
}

// Constructor
/*! \details The independent values are assumed to be sorted (lowest to
 * highest). The pdf will be used to calculate the cdf.
 * Evaluating the distribution or the pdf will always return a result zero!
 */
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
template<typename InputIndepQuantity, typename InputDepQuantity>
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::UnitAwareTabularCDFDistribution(
                  const Teuchos::Array<InputIndepQuantity>& independent_values,
                  const Teuchos::Array<InputDepQuantity>& dependent_values )
  : d_distribution( independent_values.size() ),
    d_norm_constant( DNQT::zero() ),
    d_interpret_dependent_values_as_cdf( false )
{
  // Make sure there is at lease one bin
  testPrecondition( independent_values.size() > 1 );
  testPrecondition( dependent_values.size() == independent_values.size() );
  // Make sure that the bins are sorted
  testPrecondition( Sort::isSortedAscending( independent_values.begin(),
                                             independent_values.end() ) );

  this->initializeDistribution( independent_values, dependent_values );
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
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::UnitAwareTabularCDFDistribution(
 const UnitAwareTabularCDFDistribution<InterpolationPolicy,InputIndepUnit,InputDepUnit>& dist_instance )
  : d_distribution(),
    d_norm_constant(),
    d_interpret_dependent_values_as_cdf( dist_instance.wasContructedFromCDF() )
{
  // Make sure the distribution is valid
  testPrecondition( dist_instance.d_distribution.size() > 0 );

  typedef typename UnitAwareTabularCDFDistribution<InterpolationPolicy,InputIndepUnit,InputDepUnit>::IndepQuantity InputIndepQuantity;

  typedef typename UnitAwareTabularCDFDistribution<InterpolationPolicy,InputIndepUnit,InputDepUnit>::DepQuantity InputDepQuantity;

  
  // Reconstruct the original input distribution
  Teuchos::Array<InputIndepQuantity> input_indep_values;

  if( d_interpret_dependent_values_as_cdf )
  {
    Teuchos::Array<double> input_cdf_values;

    dist_instance.reconstructOriginalCDFDistribution( input_indep_values,
                                                      input_cdf_values );
    
    this->initializeDistributionFromCDF( input_indep_values, input_cdf_values );
  }
  else
  {
    Teuchos::Array<InputDepQuantity> input_dep_values;

    dist_instance.reconstructOriginalDistribution( input_indep_values,
                                                   input_dep_values );

    this->initializeDistribution( input_indep_values, input_dep_values );
  }
}

// Copy constructor (copying from unitless distribution only)
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::UnitAwareTabularCDFDistribution( const UnitAwareTabularCDFDistribution<InterpolationPolicy,void,void>& unitless_dist_instance, int )
  : d_distribution(),
    d_norm_constant(),
    d_interpret_dependent_values_as_cdf( unitless_dist_instance.wasContructedFromCDF() )
{
  // Make sure the distribution is valid
  testPrecondition( unitless_dist_instance.d_distribution.size() > 0 );

  // Reconstruct the original input distribution
  Teuchos::Array<double> input_indep_values, input_dep_values;

  if( d_interpret_dependent_values_as_cdf )
  {
    unitless_dist_instance.reconstructOriginalCDFDistribution(
      input_indep_values, input_dep_values );
  }
  else
  {
    unitless_dist_instance.reconstructOriginalDistribution(
      input_indep_values, input_dep_values );
  }

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
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::fromUnitlessDistribution( const UnitAwareTabularCDFDistribution<InterpolationPolicy,void,void>& unitless_distribution )
{
  return ThisType( unitless_distribution, 0 );
}

// Assignment operator
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>&
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::operator=(
  const UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>& dist_instance )
{
  // Make sure the distribution is valid
  testPrecondition( dist_instance.d_distribution.size() > 0 );

  if( this != &dist_instance )
  {
    d_distribution = dist_instance.d_distribution;
    d_norm_constant = dist_instance.d_norm_constant;
    d_interpret_dependent_values_as_cdf =
      dist_instance.d_interpret_dependent_values_as_cdf;
  }

  return *this;
}

// Evaluate the distribution
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::DepQuantity
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::evaluate(
 const typename UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  return DQT::zero();
}

// Evaluate the PDF
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::InverseIndepQuantity
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::evaluatePDF(
 const typename UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  return IIQT::zero();
}

// Evaluate the CDF
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
double UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::evaluateCDF(
  const typename UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  if( indep_var_value < d_distribution.front().first )
    return 0.0;
  else if( indep_var_value >= d_distribution.back().first )
    return 1.0;
  else
  {
    typename DistributionArray::const_iterator lower_bin_boundary =
                    Search::binaryLowerBound<FIRST>( d_distribution.begin(),
                                                    d_distribution.end(),
                                                    indep_var_value );

    typename DistributionArray::const_iterator upper_bin_boundary =
                                                            lower_bin_boundary;
    ++upper_bin_boundary;

    IndepQuantity lower_indep_value = lower_bin_boundary->first;
    IndepQuantity upper_indep_value = upper_bin_boundary->first;
    UnnormCDFQuantity lower_dep_value = lower_bin_boundary->second;
    UnnormCDFQuantity upper_dep_value = upper_bin_boundary->second;

    if( lower_dep_value == QuantityTraits<UnnormCDFQuantity>::zero() )
    {
      return LinLin::interpolate( lower_indep_value,
                                  upper_indep_value,
                                  indep_var_value,
                                  lower_dep_value,
                                  upper_dep_value )*d_norm_constant;
    }
    else
    {
      return InterpolationPolicy::interpolate( lower_indep_value,
                                               upper_indep_value,
                                               indep_var_value,
                                               lower_dep_value,
                                               upper_dep_value )*d_norm_constant;
    }
  }
}

// Return a random sample from the distribution
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
inline typename UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sample() const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  unsigned dummy_index;

  return this->sampleImplementation( random_number, dummy_index );
}

// Return a random sample and record the number of trials
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sampleAndRecordTrials(
                                                       unsigned& trials ) const
{
  ++trials;

  return this->sample();
}

// Return a random sample and bin index from the distribution
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sampleAndRecordBinIndex(
                                            unsigned& sampled_bin_index ) const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleImplementation( random_number, sampled_bin_index );
}

// Return a sample from the distribution at the given CDF value
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sampleWithRandomNumber(
                                             const double random_number ) const
{
  unsigned dummy_index;

  return this->sampleImplementation( random_number, dummy_index );
}

// Return a random sample from the corresponding CDF in a subrange
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sampleInSubrange(
 const typename UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity max_indep_var ) const
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
inline typename UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sampleWithRandomNumberInSubrange(
 const double random_number,
 const typename UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity max_indep_var ) const
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
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sampleImplementation(
                                            double random_number,
                                            unsigned& sampled_bin_index ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );

  // Scale the random number
  UnnormCDFQuantity scaled_random_number = random_number*
    d_distribution.back().second;

  typename DistributionArray::const_iterator lower_bin_boundary =
                Search::binaryLowerBound<SECOND>( d_distribution.begin(),
                                                  d_distribution.end(),
                                                  scaled_random_number );

  // Calculate the sampled bin index
  sampled_bin_index = std::distance(d_distribution.begin(),lower_bin_boundary);

  // Calculate the sampled independent value
  IndepQuantity sample;

  if( lower_bin_boundary->second == QuantityTraits<UnnormCDFQuantity>::zero() )
  {
    sample = QuantityTraits<IndepQuantity>::initializeQuantity(
      LinLin::interpolate( LinLin::processIndepVar(lower_bin_boundary->second),
                           LinLin::processIndepVar(scaled_random_number),
                           LinLin::processIndepVar(lower_bin_boundary->first),
                           LinLin::processIndepVar(lower_bin_boundary->fourth ) ) );
  }
  else
  {
    sample = QuantityTraits<IndepQuantity>::initializeQuantity(
     InterpolationPolicy::interpolate( InterpolationPolicy::processDepVar(lower_bin_boundary->second),
                                       InterpolationPolicy::processDepVar(scaled_random_number),
                                       InterpolationPolicy::processIndepVar(lower_bin_boundary->first),
                                       LinLin::processIndepVar(lower_bin_boundary->fourth) ) );
  }
  ++lower_bin_boundary;

  // Make sure the sample is valid
  testPostcondition( !IQT::isnaninf( sample ) );
  testPostcondition( sample >= this->getLowerBoundOfIndepVar() );
  testPostcondition( sample <= this->getUpperBoundOfIndepVar() );

  return sample;
}

// Return the upper bound of the distribution independent variable
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::getUpperBoundOfIndepVar() const
{
  return d_distribution.back().first;
}

// Return the lower bound of the distribution independent variable
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::getLowerBoundOfIndepVar() const
{
  return d_distribution.front().first;
}

// Return the distribution type
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
OneDDistributionType
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::getDistributionType() const
{
  return ThisType::distribution_type;
}

//! Return if the distribution was continuous from a CDF
template<typename InterpolationPolicy,
typename IndependentUnit,
typename DependentUnit>
bool UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::wasContructedFromCDF() const
{
  return d_interpret_dependent_values_as_cdf;
}

// Test if the distribution is continuous
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
bool UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::isContinuous() const
{
  return true;
}

// Method for placing the object in an output stream
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
void UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::toStream(
                                                       std::ostream& os ) const
{
  Teuchos::Array<double> independent_values, dependent_values;

  this->reconstructOriginalUnitlessDistribution( independent_values,
                                                 dependent_values );

  os << "{" << independent_values << ","
            << dependent_values << ","
            << d_interpret_dependent_values_as_cdf << "}";
}

// Method for initializing the object from an input stream
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
void UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::fromStream( std::istream& is )
{
  // Read the initial '{'
  std::string start_bracket;
  std::getline( is, start_bracket, '{' );
  start_bracket = Teuchos::Utils::trimWhiteSpace( start_bracket );

  TEST_FOR_EXCEPTION( start_bracket.size() != 0,
                      InvalidDistributionStringRepresentation,
                      "Error: the input stream is not a valid tabular "
                      "distribution representation!" );

  std::string independent_values_rep;
  std::getline( is, independent_values_rep, '}' );
  independent_values_rep += "}";

  // Parse special characters
  try{
    ArrayString::locateAndReplacePi( independent_values_rep );
    ArrayString::locateAndReplaceIntervalOperator( independent_values_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                              InvalidDistributionStringRepresentation,
                              "Error: the tabular distribution cannot be "
                              "constructed because the representation is not "
                              "valid (see details below)!\n" );

  Teuchos::Array<double> independent_values;
  try{
    independent_values =
      Teuchos::fromStringToArray<double>( independent_values_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
                              InvalidDistributionStringRepresentation,
                              "Error: the tabular distribution cannot be "
                              "constructed because the representation is not "
                              "valid (see details below)!\n" );

  TEST_FOR_EXCEPTION( !Sort::isSortedAscending( independent_values.begin(),
                                                independent_values.end() ),
                      InvalidDistributionStringRepresentation,
                      "Error: the tabular distribution cannot be constructed "
                      "because the bin boundaries "
                      << independent_values_rep << " are not sorted!" );

  // Read the ","
  std::string separator;
  std::getline( is, separator, ',' );

  std::string dependent_values_rep;
  std::getline( is, dependent_values_rep, '}' );
  dependent_values_rep += "}";

  // Parse special characters
  try{
    ArrayString::locateAndReplacePi( dependent_values_rep );
    ArrayString::locateAndReplaceIntervalOperator( dependent_values_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                              InvalidDistributionStringRepresentation,
                              "Error: the tabular distribution cannot be "
                              "constructed because the representation is not "
                              "valid (see details below)!\n" );

  Teuchos::Array<double> dependent_values;
  try{
    dependent_values =
      Teuchos::fromStringToArray<double>( dependent_values_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
                              InvalidDistributionStringRepresentation,
                              "Error: the tabular distribution cannot be "
                              "constructed because the representation is not "
                              "valid (see details below)!\n" );

  TEST_FOR_EXCEPTION( independent_values.size() != dependent_values.size(),
                      InvalidDistributionStringRepresentation,
                      "Error: the tabular distribution "
                      "{" << independent_values_rep << "},{"
                      << dependent_values_rep << "} "
                      "cannot be constructed because the number of "
                      "independent values does not equal the number of "
                      "dependent values" );

  // Read the ","
  std::getline( is, separator, ',' );
  
  std::string interpret_dependent_values_as_cdf_rep;
  std::getline( is, interpret_dependent_values_as_cdf_rep, '}' );

  // Check if end of file is reached
  if ( is.eof() || interpret_dependent_values_as_cdf_rep.empty() )
  {
    THROW_EXCEPTION( std::runtime_error,
                     "Error: their is no \'interpret dependent "
                     "values as cdf\' boolean!\n" );
  }

  // Parse special characters
  try{
    ArrayString::locateAndReplacePi( interpret_dependent_values_as_cdf_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                              InvalidDistributionStringRepresentation,
                              "Error: the tabular cdf distribution cannot be "
                              "constructed because the representation is not "
                              "valid (see details below)!\n" );

  bool interpret_dependent_values_as_cdf;
  try{
    interpret_dependent_values_as_cdf =
                  std::stoul( interpret_dependent_values_as_cdf_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
                              InvalidDistributionStringRepresentation,
                              "Error: the tabular cdf distribution cannot be "
                              "constructed because the representation is not "
                              "valid (see details below)!\n" );

  // Set the interpret dependent values as cdf falg
  d_interpret_dependent_values_as_cdf = interpret_dependent_values_as_cdf;

  this->initializeDistributionFromRawData( independent_values,
                                           dependent_values );
}

// Method for testing if two objects are equivalent
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
bool UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::isEqual(
 const UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>& other ) const
{
  return d_distribution == other.d_distribution &&
         d_norm_constant == other.d_norm_constant &&
         d_interpret_dependent_values_as_cdf == other.d_interpret_dependent_values_as_cdf;
}

// Initialize the distribution
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
void UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::initializeDistributionFromRawData(
                              const Teuchos::Array<double>& independent_values,
                              const Teuchos::Array<double>& dependent_values )
{
  // Make sure there is at least one bin
  testPrecondition( independent_values.size() > 1 );
  testPrecondition( dependent_values.size() == independent_values.size() );

  // Convert the raw independent values to quantities
  Teuchos::Array<IndepQuantity> independent_quantities;

  this->convertUnitlessValues( independent_values, independent_quantities );

  if( d_interpret_dependent_values_as_cdf )
  {
    this->initializeDistributionFromCDF( independent_quantities, dependent_values );
  }
  else
  {
    // Convert the raw dependent values to quantities
    Teuchos::Array<DepQuantity> dependent_quantities;

    this->convertUnitlessValues( dependent_values, dependent_quantities );

    this->initializeDistribution( independent_quantities, dependent_quantities );
  }
}

// Initialize the distribution from a cdf
/*! \details When the distribution is initialized from the CDF no PDF data is
 *  is calculated. The PDF distribution is left blank.
 */
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
template<typename InputIndepQuantity>
void UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::initializeDistributionFromCDF(
              const Teuchos::Array<InputIndepQuantity>& independent_values,
              const Teuchos::Array<double>& cdf_values )
{
  // Make sure that the bin boundaries are sorted
  testPrecondition( Sort::isSortedAscending( independent_values.begin(),
                                             independent_values.end() ) );
  // Make sure that the bin values are sorted
  testPrecondition( Sort::isSortedAscending( cdf_values.begin(),
                                             cdf_values.end() ) );
  // Make sure there is at least one bin
  testPrecondition( independent_values.size() > 1 );
  testPrecondition( independent_values.size() == cdf_values.size() );

  // Resize the distribution
  d_distribution.resize( independent_values.size() );

  d_distribution[0].first = IndepQuantity( independent_values[0] );
  setQuantity( d_distribution[0].second, cdf_values[0] );

  // Assign the distribution
  for( unsigned i = 1; i < independent_values.size(); ++i )
  {
    d_distribution[i].first = IndepQuantity( independent_values[i] );
    setQuantity( d_distribution[i].second, cdf_values[i] );

    double slope =
      getRawQuantity( independent_values[i] - independent_values[i-1] )/
      ( cdf_values[i] - cdf_values[i-1] );

    setQuantity( d_distribution[i-1].fourth, slope );
    setQuantity( d_distribution[i].fourth, 0.0 );
  }

  // Set normalization constant
  d_norm_constant = 1.0/d_distribution.back().second;
}

// Initialize the distribution
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
template<typename InputIndepQuantity, typename InputDepQuantity>
void UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::initializeDistribution(
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

  // Resize the distribution
  d_distribution.resize( independent_values.size() );

  // Assign the raw distribution data
  for( unsigned i = 0; i < independent_values.size(); ++i )
  {
    d_distribution[i].first = IndepQuantity( independent_values[i] );
    d_distribution[i].third = DepQuantity( dependent_values[i] );
  }

  // Create a CDF from the raw distribution data
  d_norm_constant =
    DataProcessor::calculateContinuousCDF<FIRST,THIRD,SECOND>( d_distribution,
                                                               false );


  // Calculate the CDF slopes
  for( unsigned i = 1; i < independent_values.size(); ++i )
  {
    double slope =
      getRawQuantity( d_distribution[i].first - d_distribution[i-1].first )/
      getRawQuantity( d_distribution[i].second - d_distribution[i-1].second );

    setQuantity( d_distribution[i-1].fourth, slope );
    setQuantity( d_distribution[i].fourth, 0.0 );
  }
}

// Reconstruct original distribution
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
void UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::reconstructOriginalDistribution(
                         Teuchos::Array<IndepQuantity>& independent_values,
                         Teuchos::Array<DepQuantity>& dependent_values ) const
{
  // Resize the arrays
  independent_values.resize( d_distribution.size() );
  dependent_values.resize( d_distribution.size() );

  for( unsigned i = 0u; i < d_distribution.size(); ++i )
  {
    independent_values[i] = d_distribution[i].first;
    dependent_values[i] = d_distribution[i].third;
  }
}

// Reconstruct original distribution
template<typename InterpolationPolicy,
typename IndependentUnit,
typename DependentUnit>
void UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::reconstructOriginalCDFDistribution(
                Teuchos::Array<IndepQuantity>& independent_values,
                Teuchos::Array<double>& cdf_values ) const
{
  // Resize the arrays
  independent_values.resize( d_distribution.size() );
  cdf_values.resize( d_distribution.size() );

  for( unsigned i = 0u; i < d_distribution.size(); ++i )
  {
    independent_values[i] = d_distribution[i].first;
    cdf_values[i] = getRawQuantity( d_distribution[i].second );
  }
}

// Reconstruct original distribution w/o units
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
void UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::reconstructOriginalUnitlessDistribution(
                               Teuchos::Array<double>& independent_values,
                               Teuchos::Array<double>& dependent_values ) const
{
  // Resize the arrays
  independent_values.resize( d_distribution.size() );
  dependent_values.resize( d_distribution.size() );

  for( unsigned i = 0u; i < d_distribution.size(); ++i )
  {
    independent_values[i] = getRawQuantity( d_distribution[i].first );

    if( d_interpret_dependent_values_as_cdf )
    {
      dependent_values[i] = getRawQuantity( d_distribution[i].second );
    }
    else
    {
      dependent_values[i] = getRawQuantity( d_distribution[i].third );
    }
  }
}

// Convert the unitless values to the correct units
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
template<typename Quantity>
void UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::convertUnitlessValues(
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
bool UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::canDepVarBeZeroInIndepBounds() const
{
  bool possible_zero = false;

  for( size_t i = 0; i < d_distribution.size(); ++i )
  {
    if( d_distribution[i].third == DQT::zero() )
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
bool UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::isIndepVarCompatibleWithProcessingType(
                                         const LinIndepVarProcessingTag ) const
{
  return boost::is_same<typename InterpolationPolicy::IndepVarProcessingTag,LinIndepVarProcessingTag>::value;
}

// Test if the independent variable is compatible with Log processing
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
bool UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::isIndepVarCompatibleWithProcessingType(
                                         const LogIndepVarProcessingTag ) const
{
  return boost::is_same<typename InterpolationPolicy::IndepVarProcessingTag,LogIndepVarProcessingTag>::value;
}

// Test if the dependent variable is compatible with Lin processing
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
bool UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::isDepVarCompatibleWithProcessingType(
                                           const LinDepVarProcessingTag ) const
{
  return boost::is_same<typename InterpolationPolicy::DepVarProcessingTag,LinDepVarProcessingTag>::value;
}

// Test if the dependent variable is compatible with Log processing
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
bool UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::isDepVarCompatibleWithProcessingType(
                                           const LogDepVarProcessingTag ) const
{
  return boost::is_same<typename InterpolationPolicy::DepVarProcessingTag,LogDepVarProcessingTag>::value;
}

} // end Utility namespace

#endif // end Utility_TabularCDFDistribution_def.hpp

//---------------------------------------------------------------------------//
// end Utility_TabularCDFDistribution_def.hpp
//---------------------------------------------------------------------------//
