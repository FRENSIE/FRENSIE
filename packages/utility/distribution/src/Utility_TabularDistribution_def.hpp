//---------------------------------------------------------------------------//
//!
//! \file   Utility_TabularDistribution_def.hpp
//! \author Alex Robinson
//! \brief  Tabular distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TABULAR_DISTRIBUTION_DEF_HPP
#define UTILITY_TABULAR_DISTRIBUTION_DEF_HPP

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
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareTabularDistribution<LinLin,void,void> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareTabularDistribution<LinLog,void,void> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareTabularDistribution<LogLin,void,void> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareTabularDistribution<LogLog,void,void> );

// Default constructor
template<typename InterpolationPolicy, 
	 typename IndependentUnit,
	 typename DependentUnit>
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::UnitAwareTabularDistribution()
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
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::UnitAwareTabularDistribution( 
		  const Teuchos::Array<double>& independent_values,
		  const Teuchos::Array<double>& dependent_values )
  : d_distribution( independent_values.size() ),
    d_norm_constant( DNQT::zero() )
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

// Constructor
template<typename InterpolationPolicy, 
	 typename IndependentUnit,
	 typename DependentUnit>
template<typename InputIndepQuantity, typename InputDepQuantity>
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::UnitAwareTabularDistribution(
		  const Teuchos::Array<InputIndepQuantity>& independent_values,
		  const Teuchos::Array<InputDepQuantity>& dependent_values )
  : d_distribution( independent_values.size() ),
    d_norm_constant( DNQT::zero() )
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
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::UnitAwareTabularDistribution(
 const UnitAwareTabularDistribution<InterpolationPolicy,InputIndepUnit,InputDepUnit>& dist_instance )
  : d_distribution(),
    d_norm_constant()
{
  // Make sure the distribution is valid
  testPrecondition( dist_instance.d_distribution.size() > 0 );
  
  typedef typename UnitAwareTabularDistribution<InterpolationPolicy,InputIndepUnit,InputDepUnit>::IndepQuantity InputIndepQuantity;

  typedef typename UnitAwareTabularDistribution<InterpolationPolicy,InputIndepUnit,InputDepUnit>::DepQuantity InputDepQuantity;

  // Reconstruct the original input distribution
  Teuchos::Array<InputIndepQuantity> input_indep_values;
  Teuchos::Array<InputDepQuantity> input_dep_values;

  dist_instance.reconstructOriginalDistribution( input_indep_values,
						 input_dep_values );

  this->initializeDistribution( input_indep_values, input_dep_values );
}

// Copy constructor (copying from unitless distribution only)
template<typename InterpolationPolicy, 
	 typename IndependentUnit,
	 typename DependentUnit>
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::UnitAwareTabularDistribution( const UnitAwareTabularDistribution<InterpolationPolicy,void,void>& unitless_dist_instance, int )
  : d_distribution(),
    d_norm_constant()
{
  // Make sure the distribution is valid
  testPrecondition( unitless_dist_instance.d_distribution.size() > 0 );

  // Reconstruct the original input distribution
  Teuchos::Array<double> input_indep_values, input_dep_values;

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
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::fromUnitlessDistribution( const UnitAwareTabularDistribution<InterpolationPolicy,void,void>& unitless_distribution )
{
  return ThisType( unitless_distribution, 0 );
}

// Assignment operator
template<typename InterpolationPolicy, 
	 typename IndependentUnit,
	 typename DependentUnit>
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>& 
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::operator=(
  const UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>& dist_instance )
{
  // Make sure the distribution is valid
  testPrecondition( dist_instance.d_distribution.size() > 0 );

  if( this != &dist_instance )
  {
    d_distribution = dist_instance.d_distribution;
    d_norm_constant = dist_instance.d_norm_constant;
  }
  
  return *this;
}

// Evaluate the distribution
template<typename InterpolationPolicy, 
	 typename IndependentUnit,
	 typename DependentUnit>
typename UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::DepQuantity
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::evaluate( 
 const typename UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  if( indep_var_value < d_distribution.front().first )
    return DQT::zero();
  else if( indep_var_value > d_distribution.back().first )
    return DQT::zero();
  else if( indep_var_value == d_distribution.back().first )
    return d_distribution.back().third;
  else
  {
    typename DistributionArray::const_iterator start, end, lower_bin_boundary,
      upper_bin_boundary;
    start = d_distribution.begin();
    end = d_distribution.end();

    lower_bin_boundary = Search::binaryLowerBound<FIRST>( start,
							  end,
							  indep_var_value );

    upper_bin_boundary = lower_bin_boundary;
    ++upper_bin_boundary;
    
    IndepQuantity lower_indep_value = lower_bin_boundary->first;
    DepQuantity lower_dep_value = lower_bin_boundary->third;
    IndepQuantity upper_indep_value = upper_bin_boundary->first;
    DepQuantity upper_dep_value = upper_bin_boundary->third;
    
    return InterpolationPolicy::interpolate( lower_indep_value,
					     upper_indep_value,
					     indep_var_value,
					     lower_dep_value,
					     upper_dep_value );
  }
}

// Evaluate the PDF
template<typename InterpolationPolicy, 
	 typename IndependentUnit,
	 typename DependentUnit>
typename UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::InverseIndepQuantity
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::evaluatePDF( 
 const typename UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  return this->evaluate( indep_var_value )*d_norm_constant;
}

// Evaluate the CDF
template<typename InterpolationPolicy, 
	 typename IndependentUnit,
	 typename DependentUnit>
double UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::evaluateCDF( 
  const typename UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  if( indep_var_value < d_distribution.front().first )
    return 0.0;
  else if( indep_var_value >= d_distribution.back().first )
    return 1.0;
  else
  {
    typename DistributionArray::const_iterator start, end, lower_bin_boundary;
    start = d_distribution.begin();
    end = d_distribution.end();

    lower_bin_boundary = Search::binaryLowerBound<FIRST>( start,
							  end,
							  indep_var_value );

    IndepQuantity indep_diff = indep_var_value - lower_bin_boundary->first;

    return (lower_bin_boundary->second + indep_diff*lower_bin_boundary->third +
	    indep_diff*indep_diff*lower_bin_boundary->fourth/2.0)*
      d_norm_constant;
  }
}

// Return a random sample from the distribution
template<typename InterpolationPolicy, 
	 typename IndependentUnit,
	 typename DependentUnit>
inline typename UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sample() const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();
  
  unsigned dummy_index;
  
  return this->sampleImplementation( random_number, dummy_index );
}

// Return a random sample and record the number of trials
template<typename InterpolationPolicy, 
	 typename IndependentUnit,
	 typename DependentUnit>
typename UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sampleAndRecordTrials( 
						       unsigned& trials ) const
{
  ++trials;

  return this->sample();
}

// Return a random sample and bin index from the distribution
template<typename InterpolationPolicy, 
	 typename IndependentUnit,
	 typename DependentUnit>
typename UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sampleAndRecordBinIndex( 
					    unsigned& sampled_bin_index ) const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleImplementation( random_number, sampled_bin_index );
}

// Return a sample from the distribution at the given CDF value
template<typename InterpolationPolicy, 
	 typename IndependentUnit,
	 typename DependentUnit>
typename UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sampleWithRandomNumber( 
					     const double random_number ) const
{
  unsigned dummy_index;

  return this->sampleImplementation( random_number, dummy_index );
}

// Return a random sample from the corresponding CDF in a subrange
template<typename InterpolationPolicy, 
	 typename IndependentUnit,
	 typename DependentUnit>
typename UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sampleInSubrange( 
 const typename UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity max_indep_var ) const
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
inline typename UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sampleWithRandomNumberInSubrange( 
 const double random_number,
 const typename UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity max_indep_var ) const
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
typename UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sampleImplementation( 
					    double random_number,
					    unsigned& sampled_bin_index ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );

  // Scale the random number
  UnnormCDFQuantity scaled_random_number = random_number*
    d_distribution.back().second;

  typename DistributionArray::const_iterator start, end, lower_bin_boundary;
  start = d_distribution.begin();
  end = d_distribution.end();

  lower_bin_boundary = Search::binaryLowerBound<SECOND>( start,
							 end,
							 scaled_random_number);

  // Calculate the sampled bin index
  sampled_bin_index = std::distance(d_distribution.begin(),lower_bin_boundary);

  // Calculate the sampled independent value
  IndepQuantity sample;
  
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
    
    sample =  indep_value + term_2;
  }

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
typename UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity 
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::getUpperBoundOfIndepVar() const
{
  return d_distribution.back().first;
}

// Return the lower bound of the distribution independent variable
template<typename InterpolationPolicy, 
	 typename IndependentUnit,
	 typename DependentUnit>
typename UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::getLowerBoundOfIndepVar() const
{
  return d_distribution.front().first;
}

// Return the distribution type
template<typename InterpolationPolicy, 
	 typename IndependentUnit,
	 typename DependentUnit>
OneDDistributionType 
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::getDistributionType() const
{
  return ThisType::distribution_type;
}

// Test if the distribution is continuous
template<typename InterpolationPolicy, 
	 typename IndependentUnit,
	 typename DependentUnit>
bool UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::isContinuous() const
{
  return true;
}

// Method for placing the object in an output stream
template<typename InterpolationPolicy, 
	 typename IndependentUnit,
	 typename DependentUnit>
void UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::toStream( 
						       std::ostream& os ) const
{
  Teuchos::Array<double> independent_values, dependent_values;

  this->reconstructOriginalUnitlessDistribution( independent_values,
						 dependent_values );

  os << "{" << independent_values << "," << dependent_values << "}";
}

// Method for initializing the object from an input stream
template<typename InterpolationPolicy, 
	 typename IndependentUnit,
	 typename DependentUnit>
void UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::fromStream( std::istream& is )
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
		        
  this->initializeDistributionFromRawData( independent_values,
                                           dependent_values );
}

// Method for testing if two objects are equivalent
template<typename InterpolationPolicy, 
	 typename IndependentUnit,
	 typename DependentUnit>
bool UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::isEqual( 
 const UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>& other ) const
{
  return d_distribution == other.d_distribution && 
    d_norm_constant == other.d_norm_constant;
}

// Initialize the distribution
template<typename InterpolationPolicy, 
	 typename IndependentUnit,
	 typename DependentUnit>
void UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::initializeDistributionFromRawData(
			      const Teuchos::Array<double>& independent_values,
			      const Teuchos::Array<double>& dependent_values )
{
  // Make sure there is at least one bin
  testPrecondition( independent_values.size() > 1 );
  testPrecondition( dependent_values.size() == independent_values.size() );
  
  // Convert the raw independent values to quantities
  Teuchos::Array<IndepQuantity> independent_quantities;

  this->convertUnitlessValues( independent_values, independent_quantities );

  // Convert the raw dependent values to quantities
  Teuchos::Array<DepQuantity> dependent_quantities;
  
  this->convertUnitlessValues( dependent_values, dependent_quantities );
  
  this->initializeDistribution( independent_quantities, 
                                dependent_quantities );
}

// Initialize the distribution
template<typename InterpolationPolicy, 
	 typename IndependentUnit,
	 typename DependentUnit>
template<typename InputIndepQuantity, typename InputDepQuantity>
void UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::initializeDistribution( 
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

  // Calculate the slopes of the PDF
  DataProcessor::calculateSlopes<FIRST,THIRD,FOURTH>( d_distribution );
}

// Reconstruct original distribution
template<typename InterpolationPolicy, 
	 typename IndependentUnit,
	 typename DependentUnit>
void UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::reconstructOriginalDistribution(
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

// Reconstruct original distribution w/o units
template<typename InterpolationPolicy, 
	 typename IndependentUnit,
	 typename DependentUnit>
void UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::reconstructOriginalUnitlessDistribution(
			       Teuchos::Array<double>& independent_values,
			       Teuchos::Array<double>& dependent_values ) const
{
  // Resize the arrays
  independent_values.resize( d_distribution.size() );
  dependent_values.resize( d_distribution.size() );

  for( unsigned i = 0u; i < d_distribution.size(); ++i )
  {
    independent_values[i] = getRawQuantity( d_distribution[i].first );
    
    dependent_values[i] = getRawQuantity( d_distribution[i].third );
  }
}

// Convert the unitless values to the correct units
template<typename InterpolationPolicy, 
	 typename IndependentUnit,
	 typename DependentUnit>
template<typename Quantity>
void UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::convertUnitlessValues( 
		                 const Teuchos::Array<double>& unitless_values,
				 Teuchos::Array<Quantity>& quantities )
{
  // Resize the quantity array
  quantities.resize( unitless_values.size() );

  // Copy the bin boundaries
  for( unsigned i = 0u; i < unitless_values.size(); ++i )
    setQuantity( quantities[i], unitless_values[i] );
}
				       			    
} // end Utility namespace

#endif // end Utility_TabularDistribution_def.hpp

//---------------------------------------------------------------------------//
// end Utility_TabularDistribution_def.hpp
//---------------------------------------------------------------------------//
