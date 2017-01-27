//---------------------------------------------------------------------------//
//!
//! \file   Utility_DiscreteDistribution_def.hpp
//! \author Alex Robinson
//! \brief  Discrete distribution class definition.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_DISCRETE_DISTRIBUTION_DEF_HPP
#define UTILITY_DISCRETE_DISTRIBUTION_DEF_HPP

// Std Lib Includes
#include <stdexcept>

// FRENSIE Includes
#include "Utility_DataProcessor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ArrayString.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Explicit instantiation (extern declaration)
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareDiscreteDistribution<void,void> );

// Default Constructor
template<typename IndependentUnit,typename DependentUnit>
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::UnitAwareDiscreteDistribution()
{ /* ... */ }

// Basic Constructor (potentiall dangerous)
/*! \details A precalculated CDF can be passed as the dependent values as
 * long as the interpret_dependent_values_as_cdf argument is true.
 */
template<typename IndependentUnit,typename DependentUnit>
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::UnitAwareDiscreteDistribution(
			      const Teuchos::Array<double>& independent_values,
			      const Teuchos::Array<double>& dependent_values,
			      const bool interpret_dependent_values_as_cdf )
  : d_distribution( independent_values.size() ),
    d_norm_constant()
{
  this->initializeDistribution( independent_values,
				dependent_values,
				interpret_dependent_values_as_cdf );
}

// CDF Constructor (potentially dangerous)
template<typename IndependentUnit,typename DependentUnit>
template<typename InputIndepQuantity>
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::UnitAwareDiscreteDistribution(
	      const Teuchos::Array<InputIndepQuantity>& independent_quantities,
	      const Teuchos::Array<double>& dependent_values )
  : d_distribution( independent_quantities.size() ),
    d_norm_constant()
{
  this->initializeDistributionFromCDF( independent_quantities,
				       dependent_values );
}

// Constructor
template<typename IndependentUnit,typename DependentUnit>
template<typename InputIndepQuantity,typename InputDepQuantity>
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::UnitAwareDiscreteDistribution(
	      const Teuchos::Array<InputIndepQuantity>& independent_quantities,
	      const Teuchos::Array<InputDepQuantity>& dependent_values )
  : d_distribution( independent_quantities.size() ),
    d_norm_constant()
{
  this->initializeDistribution( independent_quantities,
				dependent_values );
}

// Copy constructor
/*! \details Just like boost::units::quantity objects, the unit-aware
 * distribution can be explicitly cast to a distribution with compatible
 * units. If the units are not compatible, this function will not compile. Note
 * that this allows distributions to be scaled safely (unit conversions
 * are completely taken care of by boost::units)!
 */
template<typename IndependentUnit,typename DependentUnit>
template<typename InputIndepUnit, typename InputDepUnit>
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::UnitAwareDiscreteDistribution(
	  const UnitAwareDiscreteDistribution<InputIndepUnit,InputDepUnit>& dist_instance )
  : d_distribution(),
    d_norm_constant()
{
  // Make sure that the distribution is valid
  testPrecondition( dist_instance.d_distribution.size() > 0 );

  typedef typename UnitAwareDiscreteDistribution<InputIndepUnit,InputDepUnit>::IndepQuantity InputIndepQuantity;

  typedef typename UnitAwareDiscreteDistribution<InputIndepUnit,InputDepUnit>::DepQuantity InputDepQuantity;

  // Reconstruct the original input distribution
  Teuchos::Array<InputIndepQuantity> input_indep_quantities;
  Teuchos::Array<InputDepQuantity> input_dep_quantities;

  dist_instance.reconstructOriginalDistribution( input_indep_quantities,
						 input_dep_quantities );

  this->initializeDistribution( input_indep_quantities, input_dep_quantities );
}

// Copy constructor (copying from unitless distribution only)
template<typename IndependentUnit,typename DependentUnit>
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::UnitAwareDiscreteDistribution(
  const UnitAwareDiscreteDistribution<void,void>& unitless_dist_instance, int )
  : d_distribution(),
    d_norm_constant()
{
  // Make sure that the distribution is valid
  testPrecondition( unitless_dist_instance.d_distribution.size() > 0 );

  // Reconstruct the original input distribution
  Teuchos::Array<double> input_bin_boundaries, input_bin_values;

  unitless_dist_instance.reconstructOriginalDistribution( input_bin_boundaries,
							  input_bin_values );

  this->initializeDistribution( input_bin_boundaries, input_bin_values, false );
}

// Construct distribution from a unitless dist. (potentially dangerous)
/*! \details Constructing a unit-aware distribution from a unitless
 * distribution is potentially dangerous. By forcing users to construct objects
 * using this method instead of a standard constructor we are trying to make
 * sure users are aware of the danger. This is designed to mimic the interface
 * of the boost::units::quantity, which also has to deal with this issue.
 */
template<typename IndependentUnit,typename DependentUnit>
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::fromUnitlessDistribution(
        const UnitAwareDiscreteDistribution<void,void>& unitless_distribution )
{
  return ThisType( unitless_distribution, 0 );
}

// Assignment operator
template<typename IndependentUnit,typename DependentUnit>
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>&
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::operator=(
	  const UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>& dist_instance )
{
  // Make sure that the distribution is valid
  testPrecondition( dist_instance.d_distribution.size() > 0 );

  if( this != &dist_instance )
  {
    d_distribution = dist_instance.d_distribution;
    d_norm_constant = dist_instance.d_norm_constant;
  }

  return *this;
}

// Evaluate the distribution
/*! \details The discrete distribution can be expressed as a sum of delta
 * functions, which allows it to behave as a continuous distribution.
 * Therefore, the discrete distribution can technically only take on
 * two values: 0.0 and infinity. It is more useful to return the dependent
 * value associated with a defined independent value.
 */
template<typename IndependentUnit,typename DependentUnit>
typename UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::DepQuantity
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::evaluate( const typename UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  return getRawQuantity(this->evaluatePDF( indep_var_value ))*d_norm_constant;
}

// Evaluate the PDF
/*! \details It is acceptable for the same independent variable to appear
 * multiple times. When multiple occurances are found, the sum will be
 * returned.
 */
template<typename IndependentUnit,typename DependentUnit>
typename UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::evaluatePDF( const typename UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  double raw_pdf = 0.0;

  if( indep_var_value >= d_distribution.front().first &&
      indep_var_value <= d_distribution.back().first )
  {
    typename Teuchos::Array<Pair<IndepQuantity,double> >::const_iterator bin =
      Search::binaryLowerBound<FIRST>( d_distribution.begin(),
				       d_distribution.end(),
				       indep_var_value );

    typename Teuchos::Array<Pair<IndepQuantity,double> >::const_iterator
      prev_bin = bin;
    --prev_bin;

    // The same independent variable may appear multiple times
    while( bin->first == indep_var_value )
    {
      if( bin != d_distribution.begin() )
      {
	raw_pdf += bin->second - prev_bin->second;

	--bin;
	--prev_bin;
      }
      else
      {
	raw_pdf += bin->second;

	break;
      }
    }
  }
  else
    raw_pdf = 0.0;

  return QuantityTraits<InverseIndepQuantity>::initializeQuantity( raw_pdf );
}

// Evaluate the CDF
template<typename IndependentUnit,typename DependentUnit>
double UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::evaluateCDF( const typename UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  double cdf = 0.0;

  if( indep_var_value >= d_distribution.front().first &&
      indep_var_value <= d_distribution.back().first )
  {
    typename Teuchos::Array<Pair<IndepQuantity,double> >::const_iterator bin =
      Search::binaryLowerBound<FIRST>( d_distribution.begin(),
				       d_distribution.end(),
				       indep_var_value );

    // The same independent variable may appear multiple times
    cdf = bin->second;
  }
  else if( indep_var_value < d_distribution.front().first )
    cdf = 0.0;
  else
    cdf = 1.0;

  return cdf;
}


// Return a random sample from the distribution
template<typename IndependentUnit,typename DependentUnit>
typename UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::sample() const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  unsigned dummy_index;

  return this->sampleImplementation( random_number, dummy_index );
}

// Return a random sample and record the number of trials
template<typename IndependentUnit,typename DependentUnit>
typename UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::sampleAndRecordTrials( DistributionTraits::Counter& trials ) const
{
  ++trials;

  return this->sample();
}

// Return a random sample and sampled index from the corresponding CDF
template<typename IndependentUnit,typename DependentUnit>
typename UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::sampleAndRecordBinIndex(
					    unsigned& sampled_bin_index ) const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleImplementation( random_number, sampled_bin_index );
}

// Return a random sample and sampled index from the corresponding CDF
template<typename IndependentUnit,typename DependentUnit>
typename UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::sampleWithRandomNumber(
					     const double random_number ) const
{
  unsigned dummy_index;

  return this->sampleImplementation( random_number, dummy_index );
}

// Return a random sample from the corresponding CDF in a subrange
template<typename IndependentUnit,typename DependentUnit>
typename UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::sampleInSubrange( const typename UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::IndepQuantity max_indep_var ) const
{
  // Make sure the max independent variable is valid
  testPrecondition( max_indep_var >= d_distribution.front().first );

  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleWithRandomNumberInSubrange( random_number,
						 max_indep_var );
}

// Return a random sample using the random number and record the bin index
template<typename IndependentUnit,typename DependentUnit>
inline typename UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::sampleImplementation(
					    double random_number,
					    unsigned& sampled_bin_index ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );

  // Get the bin index sampled
  sampled_bin_index =
    Search::binaryUpperBoundIndex<SECOND>( d_distribution.begin(),
					   d_distribution.end(),
					   random_number );

  return d_distribution[sampled_bin_index].first;
}

// Return a random sample from the distribution at the given CDF value in a subrange
template<typename IndependentUnit,typename DependentUnit>
inline typename UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::sampleWithRandomNumberInSubrange(
   const double random_number,
   const typename UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::IndepQuantity max_indep_var ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );
  // Make sure the max independent variable is valid
  testPrecondition( max_indep_var >= d_distribution.front().first );

  // Scale the random number to the cdf at the max indep var
  double scaled_random_number =
    random_number*this->evaluateCDF( max_indep_var );

  unsigned dummy_index;

  return this->sampleImplementation( scaled_random_number, dummy_index );
}

// Return the upper bound of the distribution independent variable
template<typename IndependentUnit,typename DependentUnit>
typename UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::getUpperBoundOfIndepVar() const
{
  return d_distribution.back().first;
}

// Return the lower bound of the independent variable
template<typename IndependentUnit,typename DependentUnit>
typename UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::getLowerBoundOfIndepVar() const
{
  return d_distribution.front().first;
}

// Return the distribution type
template<typename IndependentUnit,typename DependentUnit>
OneDDistributionType
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::getDistributionType() const
{
  return UnitAwareDiscreteDistribution::distribution_type;
}

// Test if the distribution is continuous
template<typename IndependentUnit,typename DependentUnit>
bool UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::isContinuous() const
{
  return false;
}

// Method for placing the object in an output stream
template<typename IndependentUnit,typename DependentUnit>
void UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::toStream( std::ostream& os ) const
{
  Teuchos::Array<double> independent_values, dependent_values;

  this->reconstructOriginalUnitlessDistribution( independent_values,
						 dependent_values );

  os << "{" << independent_values << "," << dependent_values << "}";
}

// Method for initializing the object from an input stream
template<typename IndependentUnit,typename DependentUnit>
void UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::fromStream( std::istream& is )
{
  // Read the initial '{'
  std::string start_bracket;
  std::getline( is, start_bracket, '{' );
  start_bracket = Teuchos::Utils::trimWhiteSpace( start_bracket );

  TEST_FOR_EXCEPTION( start_bracket.size() != 0,
		      InvalidDistributionStringRepresentation,
		      "Error: the input stream is not a valid discrete "
		      "distribution representation!" );

  std::string independent_values_rep;
  std::getline( is, independent_values_rep, '}' );
  independent_values_rep += "}";

  // Parse special charaters
  try{
    ArrayString::locateAndReplacePi( independent_values_rep );
    ArrayString::locateAndReplaceIntervalOperator( independent_values_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
			      InvalidDistributionStringRepresentation,
			      "Error: the discrete distribution cannot be "
			      "constructed because the independent values are "
			      "not valid (see details below)!\n" );

  Teuchos::Array<double> independent_values;
  try{
    independent_values =
      Teuchos::fromStringToArray<double>( independent_values_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
			      InvalidDistributionStringRepresentation,
			      "Error: the discrete distribution cannot be "
			      "constructed because the independent values are "
			      "not valid (see details below)!\n" );

  TEST_FOR_EXCEPTION( !Sort::isSortedAscending( independent_values.begin(),
						independent_values.end() ),
		      InvalidDistributionStringRepresentation,
		      "Error: the discrete distribution cannot be constructed "
		      "because the bin boundaries "
		      << independent_values_rep << " are not sorted!" );

  // Read the ","
  std::string separator;
  std::getline( is, separator, ',' );

  std::string dependent_values_rep;
  std::getline( is, dependent_values_rep, '}' );
  dependent_values_rep += "}";

  // Parse special charaters
  try{
    ArrayString::locateAndReplacePi( dependent_values_rep );
    ArrayString::locateAndReplaceIntervalOperator( dependent_values_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
			      InvalidDistributionStringRepresentation,
			      "Error: the discrete distribution cannot be "
			      "constructed because the dependent values are "
			      "not valid (see details below)!\n" );

  Teuchos::Array<double> dependent_values;
  try{
    dependent_values =
      Teuchos::fromStringToArray<double>( dependent_values_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
			      InvalidDistributionStringRepresentation,
			      "Error: the discrete distribution cannot be "
			      "constructed because the dependent values are "
			      "not valid (see details below)!\n" );

  TEST_FOR_EXCEPTION( independent_values.size() != dependent_values.size(),
		      InvalidDistributionStringRepresentation,
		      "Error: the discrete distribution "
		      "{" << independent_values_rep << "},{"
		      << dependent_values_rep << "} "
		      "cannot be constructed because the number of "
		      "independent values does not match the number of "
		      "dependent values!" );

  this->initializeDistribution( independent_values, dependent_values, false );
}

// Method for testing if two objects are equivalent
template<typename IndependentUnit,typename DependentUnit>
bool UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::isEqual( const UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>& other ) const
{
  return d_distribution == other.d_distribution &&
    d_norm_constant == other.d_norm_constant;
}

// Initialize the distribution
template<typename IndependentUnit,typename DependentUnit>
void UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::initializeDistribution(
			  const Teuchos::Array<double>& independent_values,
			  const Teuchos::Array<double>& dependent_values,
			  const bool interpret_dependent_values_as_cdf )
{
  // Make sure that every value has a probability assigned
  testPrecondition( independent_values.size() == dependent_values.size() );
  // Make sure that the bins are sorted
  testPrecondition( Sort::isSortedAscending( independent_values.begin(),
					     independent_values.end() ) );

  // Convert the raw independent values to quantities
  Teuchos::Array<IndepQuantity> independent_quantities;

  this->convertUnitlessValues( independent_values, independent_quantities );

  if( interpret_dependent_values_as_cdf )
  {
    this->initializeDistributionFromCDF( independent_quantities,
					 dependent_values );
  }
  else
  {
    // Convert the raw dependent values to quantities
    Teuchos::Array<DepQuantity> dependent_quantities;

    this->convertUnitlessValues( dependent_values, dependent_quantities );

    this->initializeDistribution( independent_quantities,
				  dependent_quantities );
  }
}

// Initialize the distribution from a cdf
template<typename IndependentUnit,typename DependentUnit>
template<typename InputIndepQuantity>
void UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::initializeDistributionFromCDF(
	      const Teuchos::Array<InputIndepQuantity>& independent_quantities,
	      const Teuchos::Array<double>& cdf_values )
{
  // Make sure that every value has a probability assigned
  testPrecondition( independent_quantities.size() == cdf_values.size() );
  // Make sure that the bins are sorted
  testPrecondition( Sort::isSortedAscending( independent_quantities.begin(),
					     independent_quantities.end() ) );
  // Make sure that the cdf is sorted
  testPrecondition( Sort::isSortedAscending( cdf_values.begin(),
					     cdf_values.end() ) );

  // Resize the distribution
  d_distribution.resize( independent_quantities.size() );

  // Assign the distribution
  for( unsigned i = 0; i < cdf_values.size(); ++i )
  {
    d_distribution[i].first = IndepQuantity( independent_quantities[i] );

    d_distribution[i].second = cdf_values[i];
  }

  // Verify that the CDF is normalized (in event of round-off errors)
  if( cdf_values.back() != 1.0 )
  {
    for( unsigned i = 0; i < d_distribution.size(); ++i )
      d_distribution[i].second /= d_distribution.back().second;
  }

  // Set the normalization constant
  setQuantity( d_norm_constant, 1.0 );
}

// Initialize the distribution
template<typename IndependentUnit,typename DependentUnit>
template<typename InputIndepQuantity,typename InputDepQuantity>
void UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::initializeDistribution(
		  const Teuchos::Array<InputIndepQuantity>& independent_values,
		  const Teuchos::Array<InputDepQuantity>& dependent_values )
{
  // Make sure that every value has a probability assigned
  testPrecondition( independent_values.size() == dependent_values.size() );
  // Make sure that the bins are sorted
  testPrecondition( Sort::isSortedAscending( independent_values.begin(),
					     independent_values.end() ) );

  // Resize the distribution array
  d_distribution.resize( independent_values.size() );

  // Assign the raw distribution data
  for( unsigned i = 0; i < dependent_values.size(); ++i )
  {
    d_distribution[i].first = IndepQuantity( independent_values[i] );

    // Use an explicit cast to desired unit
    DepQuantity dep_quantity( dependent_values[i] );

    d_distribution[i].second = getRawQuantity( dep_quantity );

    d_norm_constant += dep_quantity;
  }

  // Create a CDF from the raw distribution data
  DataProcessor::calculateDiscreteCDF<SECOND,SECOND>( d_distribution );
}

// Reconstruct original distribution
template<typename IndependentUnit,typename DependentUnit>
void UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::reconstructOriginalDistribution(
		     Teuchos::Array<IndepQuantity>& independent_quantities,
		     Teuchos::Array<DepQuantity>& dependent_quantities ) const
{
  // Resize the arrays
  independent_quantities.resize( d_distribution.size() );
  dependent_quantities.resize( d_distribution.size() );

  for( unsigned i = 0u; i < d_distribution.size(); ++i )
  {
    independent_quantities[i] = d_distribution[i].first;

    if( i != 0u )
    {
      dependent_quantities[i] = d_norm_constant*
	( d_distribution[i].second - d_distribution[i-1].second );
    }
    else
      dependent_quantities[i] = d_norm_constant*d_distribution[i].second;
  }
}

// Reconstruct original distribution w/o units
template<typename IndependentUnit,typename DependentUnit>
void UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::reconstructOriginalUnitlessDistribution(
			      Teuchos::Array<double>& independent_values,
			      Teuchos::Array<double>& dependent_values ) const
{
  // Resize the arrays
  independent_values.resize( d_distribution.size() );
  dependent_values.resize( d_distribution.size() );

  for( unsigned i = 0u; i < d_distribution.size(); ++i )
  {
    independent_values[i] = getRawQuantity( d_distribution[i].first );

    if( i != 0u )
    {
      dependent_values[i] = getRawQuantity( d_norm_constant )*
	(d_distribution[i].second - d_distribution[i-1].second);
    }
    else
    {
      dependent_values[i] =
	d_distribution[i].second*getRawQuantity( d_norm_constant );
    }
  }
}

// Convert the unitless values to the correct units
template<typename IndependentUnit,typename DependentUnit>
template<typename Quantity>
void UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::convertUnitlessValues(
		                 const Teuchos::Array<double>& unitless_values,
				 Teuchos::Array<Quantity>& quantities )
{
  // Resize the quantities array
  quantities.resize( unitless_values.size() );

  // Copy the values
  for( unsigned i = 0u; i < unitless_values.size(); ++i )
    setQuantity( quantities[i], unitless_values[i] );
}

// Test if the dependent variable can be zero within the indep bounds
template<typename IndependentUnit,typename DependentUnit>
bool UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::canDepVarBeZeroInIndepBounds() const
{
  return true;
}

} // end Utility namespace

#endif // end UTILITY_DISCRETE_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_DiscreteDistribution_def.hpp
//---------------------------------------------------------------------------//
