//---------------------------------------------------------------------------//
//!
//! \file   Utility_TabularDistribution_def.hpp
//! \author Alex Robinson
//! \brief  Tabular distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TABULAR_DISTRIBUTION_DEF_HPP
#define UTILITY_TABULAR_DISTRIBUTION_DEF_HPP

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_DataProcessor.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ArrayString.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

namespace Utility{

// Default constructor
template<typename InterpolationPolicy>
TabularDistribution<InterpolationPolicy>::TabularDistribution()
{ /* ... */ }

// Constructor
/*! \details The independent values are assumed to be sorted (lowest to 
 * highest). If cdf values are provided a pdf will be calculated. Because
 * information is lost when converting from a pdf to a cdf, the pdf becomes
 * ambiguous. Evaluate the resulting distribution with caution (there will
 * be no difference when sampling from the distribution)!
 */ 
template<typename InterpolationPolicy>
TabularDistribution<InterpolationPolicy>::TabularDistribution( 
			      const Teuchos::Array<double>& independent_values,
			      const Teuchos::Array<double>& dependent_values,
                  const bool interpret_dependent_values_as_cdf )
  : d_distribution( independent_values.size() ),
    d_norm_constant( DNQT::zero() )
{
<<<<<<< HEAD
  if( interpret_dependent_values_as_cdf )
  {
    // Make sure that for n bin boundaries there are n bin values
    testPrecondition( independent_values.size() == dependent_values.size() );
    // Make sure that the bins are sorted
    testPrecondition( Sort::isSortedAscending( independent_values.begin(),
					       independent_values.end() ) );
    // Make sure that the bin values are sorted
    testPrecondition( Sort::isSortedAscending( dependent_values.begin(), 
					       dependent_values.end() ) );

    d_distribution[0].first = independent_values[0];
    d_distribution[0].second = dependent_values[0];
    // Arbitrarily set the first pdf value to 1.0
    d_distribution[0].third = 1.0;

    // Assign the distribution
    for( unsigned i = 1; i < independent_values.size(); ++i )
    {
      d_distribution[i].first = independent_values[i];
      d_distribution[i].second = dependent_values[i];

      // Calculate the pdf from the cdf
      d_distribution[i].third = -d_distribution[i-1].third + 2.0 *
        (d_distribution[i].second - d_distribution[i-1].second)/
        (d_distribution[i].first - d_distribution[i-1].first);
    }

    // Set normalization constant
    d_norm_constant = d_distribution.back().second;
 
    // Verify that the CDF is normalized (in event of round-off errors)
    if( dependent_values.back() != 1.0 )
    {
      for( unsigned j = 0; j < d_distribution.size(); ++j )
      {
        d_distribution[j].second /= d_norm_constant;
        d_distribution[j].third /= d_norm_constant;
      }
    }
=======
  // Make sure there is at lease one bin
  testPrecondition( independent_values.size() > 1 );
  testPrecondition( dependent_values.size() == independent_values.size() );
  // Make sure that the bins are sorted
  testPrecondition( Sort::isSortedAscending( independent_values.begin(),
					     independent_values.end() ) );

  this->initializeDistribution( independent_values,
				dependent_values,
				interpret_dependent_values_as_cdf );
}

// CDF constructor
/*! \details The independent values are assumed to be sorted (lowest to 
 * highest). Because information is lost when converting from a pdf to a cdf, 
 * the pdf becomes ambiguous. Evaluate the resulting distribution with caution 
 * (there will be no difference when sampling from the distribution)!
 */ 
template<typename InterpolationPolicy, 
	 typename IndependentUnit,
	 typename DependentUnit>
template<typename InputIndepQuantity>
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::UnitAwareTabularDistribution( 
		  const Teuchos::Array<InputIndepQuantity>& independent_values,
		  const Teuchos::Array<double>& cdf_values )
  : d_distribution( independent_values.size() ),
    d_norm_constant( 0.0 )
{
  // Make sure there is at lease one bin
  testPrecondition( independent_values.size() > 1 );
  testPrecondition( cdf_values.size() == independent_values.size() );
  // Make sure that the bins are sorted
  testPrecondition( Sort::isSortedAscending( independent_values.begin(),
					     independent_values.end() ) );
  // Make sure that the cdf is valid
  testPrecondition( Sort::isSortedAscending( cdf_values.begin(),
					     cdf_values.end() ) );

  this->initializeDistributionFromCDF( independent_values, cdf_values );
}

template<typename InterpolationPolicy, 
	 typename IndependentUnit,
	 typename DependentUnit>
template<typename InputIndepQuantity, typename InputDepQuantity>
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::UnitAwareTabularDistribution(
		  const Teuchos::Array<InputIndepQuantity>& independent_values,
		  const Teuchos::Array<InputDepQuantity>& dependent_values )
  : d_distribution( independent_values.size() ),
    d_norm_constant( 0.0 )
{
  // Make sure there is at lease one bin
  testPrecondition( independent_values.size() > 1 );
  testPrecondition( dependent_values.size() == independent_values.size() );
  // Make sure that the bins are sorted
  testPrecondition( Sort::isSortedAscending( independent_values.begin(),
					     independent_values.end() ) );
>>>>>>> Working on refactoring the TabularDistribution class.

    // Calculate the slopes of the PDF
    DataProcessor::calculateSlopes<FIRST,THIRD,FOURTH>( d_distribution );
  }
  else
  {
    initializeDistribution( independent_values, dependent_values );
  }
}

// Copy constructor
<<<<<<< HEAD
template<typename InterpolationPolicy>
TabularDistribution<InterpolationPolicy>::TabularDistribution(
		const TabularDistribution<InterpolationPolicy>& dist_instance )
  : d_distribution( dist_instance.d_distribution ),
    d_norm_constant( dist_instance.d_norm_constant )
{
  // Make sure the distribution is valid
  testPrecondition( dist_instance.d_distribution.size() > 0 );
=======
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
{
  // Make sure the distribution is valid
  testPrecondition( unitless_dist_instance.d_distribution.size() > 0 );

  // Reconstruct the original input distribution
  Teuchos::Array<double> input_indep_values, input_dep_values;

  unitless_dist_instance.reconstructOriginalDistribution( input_indep_values,
							  input_dep_values );

  this->initializeDistribution( input_indep_values, input_dep_values, false );
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
>>>>>>> Working on refactoring the TabularDistribution class.
}

// Assignment operator
template<typename InterpolationPolicy>
TabularDistribution<InterpolationPolicy>& 
TabularDistribution<InterpolationPolicy>::operator=(
		const TabularDistribution<InterpolationPolicy>& dist_instance )
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
template<typename InterpolationPolicy>
double TabularDistribution<InterpolationPolicy>::evaluate( 
					   const double indep_var_value ) const
{
<<<<<<< HEAD
  return evaluatePDF( indep_var_value )*d_norm_constant;
}

// Evaluate the PDF
template<typename InterpolationPolicy>
double TabularDistribution<InterpolationPolicy>::evaluatePDF( 
					   const double indep_var_value ) const
{
  if( indep_var_value < d_distribution.front().first )
    return 0.0;
  else if( indep_var_value > d_distribution.back().first )
    return 0.0;
=======
  if( indep_var_value < d_distribution.front().first )
    return DQT::zero();
  else if( indep_var_value > d_distribution.back().first )
    return DQT::zero();
>>>>>>> Working on refactoring the TabularDistribution class.
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
    
<<<<<<< HEAD
    double lower_indep_value = lower_bin_boundary->first;
    double lower_pdf_value = lower_bin_boundary->third;
    double upper_indep_value = upper_bin_boundary->first;
    double upper_pdf_value = upper_bin_boundary->third;
=======
    IndepQuantity lower_indep_value = lower_bin_boundary->first;
    DepQuantity lower_dep_value = lower_bin_boundary->third;
    IndepQuantity upper_indep_value = upper_bin_boundary->first;
    DepQuantity upper_dep_value = upper_bin_boundary->third;
>>>>>>> Working on refactoring the TabularDistribution class.
    
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
template<typename InterpolationPolicy>
double TabularDistribution<InterpolationPolicy>::evaluateCDF( 
					   const double indep_var_value ) const
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

    double indep_diff = indep_var_value - lower_bin_boundary->first;

<<<<<<< HEAD
    return lower_bin_boundary->second + indep_diff*lower_bin_boundary->third +
           indep_diff*indep_diff/2.0 * lower_bin_boundary->fourth;
=======
    return (lower_bin_boundary->second + indep_diff*lower_bin_boundary->third +
	    indep_diff*indep_diff*lower_bin_boundary->fourth/2.0)*
      d_norm_constant;
>>>>>>> Working on refactoring the TabularDistribution class.
  }
}

// Return a random sample from the distribution
template<typename InterpolationPolicy>
inline double TabularDistribution<InterpolationPolicy>::sample() const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();
  
  unsigned dummy_index;
  
  return this->sampleImplementation( random_number, dummy_index );
}

// Return a random sample and record the number of trials
template<typename InterpolationPolicy>
double TabularDistribution<InterpolationPolicy>::sampleAndRecordTrials( 
						       unsigned& trials ) const
{
  ++trials;

  return this->sample();
}

// Return a random sample and bin index from the distribution
template<typename InterpolationPolicy>
double TabularDistribution<InterpolationPolicy>::sampleAndRecordBinIndex( 
					    unsigned& sampled_bin_index ) const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleImplementation( random_number, sampled_bin_index );
}

// Return a sample from the distribution at the given CDF value
template<typename InterpolationPolicy>
double TabularDistribution<InterpolationPolicy>::sampleWithRandomNumber( 
					     const double random_number ) const
{
  unsigned dummy_index;

  return this->sampleImplementation( random_number, dummy_index );
}

// Return a random sample from the corresponding CDF in a subrange
template<typename InterpolationPolicy>
double TabularDistribution<InterpolationPolicy>::sampleInSubrange( 
					     const double max_indep_var ) const
{
  // Make sure the maximum indep var is valid
  testPrecondition( max_indep_var >= this->getLowerBoundOfIndepVar() );
    
  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleWithRandomNumberInSubrange( random_number,
						 max_indep_var );
}

// Return a random sample from the distribution at the given CDF value in a subrange
template<typename InterpolationPolicy>
inline double TabularDistribution<InterpolationPolicy>::sampleWithRandomNumberInSubrange( 
					     const double random_number,
					     const double max_indep_var ) const
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
template<typename InterpolationPolicy>
double TabularDistribution<InterpolationPolicy>::sampleImplementation( 
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
  double sample;
  
<<<<<<< HEAD
  double indep_value = lower_bin_boundary->first;
  double cdf_diff = random_number - lower_bin_boundary->second;
  double pdf_value = lower_bin_boundary->third;
  double slope = lower_bin_boundary->fourth;
=======
  IndepQuantity indep_value = lower_bin_boundary->first;
  UnnormCDFQuantity cdf_diff = 
    scaled_random_number - lower_bin_boundary->second;
  DepQuantity pdf_value = lower_bin_boundary->third;
  SlopeQuantity slope = lower_bin_boundary->fourth;
>>>>>>> Working on refactoring the TabularDistribution class.

  // x = x0 + [sqrt(pdf(x0)^2 + 2m[cdf(x)-cdf(x0)]) - pdf(x0)]/m 
  if( slope != 0.0 )
  {
    sample = indep_value + 
      (sqrt( pdf_value*pdf_value + 2*slope*cdf_diff ) - pdf_value)/slope;
  }
  // x = x0 + [cdf(x)-cdf(x0)]/pdf(x0) => L'Hopital's rule
  else
    sample =  indep_value + cdf_diff/pdf_value;

  // Make sure the sample is valid
  testPostcondition( !Teuchos::ScalarTraits<double>::isnaninf( sample ) );

  return sample;
}

// Return the upper bound of the distribution independent variable
template<typename InterpolationPolicy>
double 
TabularDistribution<InterpolationPolicy>::getUpperBoundOfIndepVar() const
{
  return d_distribution.back().first;
}

// Return the lower bound of the distribution independent variable
template<typename InterpolationPolicy>
double 
TabularDistribution<InterpolationPolicy>::getLowerBoundOfIndepVar() const
{
  return d_distribution.front().first;
}

// Return the distribution type
template<typename InterpolationPolicy>
OneDDistributionType 
TabularDistribution<InterpolationPolicy>::getDistributionType() const
{
  return TabularDistribution<InterpolationPolicy>::distribution_type;
}

// Test if the distribution is continuous
template<typename InterpolationPolicy>
bool TabularDistribution<InterpolationPolicy>::isContinuous() const
{
  return true;
}

// Method for placing the object in an output stream
template<typename InterpolationPolicy>
void TabularDistribution<InterpolationPolicy>::toStream( 
						       std::ostream& os ) const
{
  Teuchos::Array<double> independent_values( d_distribution.size() );
  Teuchos::Array<double> dependent_values( d_distribution.size() );

  for( unsigned i = 0u; i < d_distribution.size(); ++i )
  {
    independent_values[i] = d_distribution[i].first;
    
    dependent_values[i] = d_distribution[i].third*d_norm_constant;
  }

  os << "{" << independent_values << "," << dependent_values << "}";
}

// Method for initializing the object from an input stream
template<typename InterpolationPolicy>
void TabularDistribution<InterpolationPolicy>::fromStream( std::istream& is )
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
		        
  initializeDistribution( independent_values, dependent_values );
}

// Method for testing if two objects are equivalent
<<<<<<< HEAD
template<typename InterpolationPolicy>
bool TabularDistribution<InterpolationPolicy>::isEqual( 
		  const TabularDistribution<InterpolationPolicy>& other ) const
=======
template<typename InterpolationPolicy, 
	 typename IndependentUnit,
	 typename DependentUnit>
bool UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::isEqual( 
 const UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>& other ) const
>>>>>>> Working on refactoring the TabularDistribution class.
{
  return d_distribution == other.d_distribution && 
    d_norm_constant == other.d_norm_constant;
}

// Initialize the distribution
template<typename InterpolationPolicy>
void TabularDistribution<InterpolationPolicy>::initializeDistribution(
			      const Teuchos::Array<double>& independent_values,
<<<<<<< HEAD
			      const Teuchos::Array<double>& dependent_values )
=======
			      const Teuchos::Array<double>& dependent_values,
			      const bool interpret_dependent_values_as_cdf )
{
  // Make sure there is at least one bin
  testPrecondition( independent_values.size() > 1 );
  testPrecondition( dependent_values.size() == independent_values.size() );
  
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
template<typename InterpolationPolicy, 
	 typename IndependentUnit,
	 typename DependentUnit>
template<typename InputIndepQuantity>
void UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::initializeDistributionFromCDF(
		  const Teuchos::Array<InputIndepQuantity>& independent_values,
		  const Teuchos::Array<double>& cdf_values )
{
  // Make sure that there is at least one bin
  testPrecondition( independent_values.size() > 1 );
  // Make sure that for n bin boundaries there are n bin values
  testPrecondition( independent_values.size() == cdf_values.size() );
  // Make sure that the cdf is valid
  testPrecondition( cdf_values[0] == 0.0 );
  // Make sure that the bins are sorted
  testPrecondition( Sort::isSortedAscending( independent_values.begin(),
					     independent_values.end() ) );
  // Make sure that the bin values are sorted
  testPrecondition( Sort::isSortedAscending( cdf_values.begin(), 
					     cdf_values.end() ) );

  // Resize the distribution
  d_distribution.resize( independent_values.size() );

  // Set the first bin boundary
  d_distribution[0].first = IndepQuantity( independent_values[0] );
  setQuantity( d_distribution[0].second, cdf_values[0] );
  
  // Assign the distribution
  for( unsigned i = 0; i < independent_values.size(); ++i )
  {
    d_distribution[i].first = independent_values[i];
    
    setQuantity( d_distribution[i].second, cdf_values[i] );
  }

  DataProcessor::calculateContinuousPDF<FIRST,THIRD,SECOND>( d_distribution );

  // Set normalization constant
  d_norm_constant = 1.0/d_distribution.back().second;

  // Calculate the slopes of the PDF
  DataProcessor::calculateSlopes<FIRST,THIRD,FOURTH>( d_distribution );
}

// Initialize the distribution
template<typename InterpolationPolicy, 
	 typename IndependentUnit,
	 typename DependentUnit>
template<typename InputIndepQuantity, typename InputDepQuantity>
void UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::initializeDistribution( 
		  const Teuchos::Array<InputIndepQuantity>& independent_values,
		  const Teuchos::Array<InputDepQuantity>& dependent_values )
>>>>>>> Working on refactoring the TabularDistribution class.
{
  // Make sure that at least two points of the distribution are specified
  testPrecondition( independent_values.size() > 1 );
  // Make sure that the independent values are sorted
  testPrecondition( Sort::isSortedAscending( independent_values.begin(),
					     independent_values.end() ) );
  // Make sure that every independent value has a dependent value
  testPrecondition( independent_values.size() == dependent_values.size() );

  // Resize the distribution
  d_distribution.resize( independent_values.size() );
  
  // Assign the raw distribution data
  for( unsigned i = 0; i < independent_values.size(); ++i )
  {
<<<<<<< HEAD
    d_distribution[i].first = independent_values[i];
    d_distribution[i].third = dependent_values[i];
=======
    d_distribution[i].first = IndepQuantity( independent_values[i] );
    d_distribution[i].third = DepQuantity( dependent_values[i] );
>>>>>>> Working on refactoring the TabularDistribution class.
  }

  // Create a CDF from the raw distribution data
  d_norm_constant = 
<<<<<<< HEAD
    DataProcessor::calculateContinuousCDF<FIRST,THIRD,SECOND>(d_distribution);
=======
    DataProcessor::calculateContinuousCDF<FIRST,THIRD,SECOND>( d_distribution,
							       false );
>>>>>>> Working on refactoring the TabularDistribution class.

  // Calculate the slopes of the PDF
  DataProcessor::calculateSlopes<FIRST,THIRD,FOURTH>( d_distribution );
}
<<<<<<< HEAD
=======

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
>>>>>>> Working on refactoring the TabularDistribution class.
				       			    
} // end Utility namespace

#endif // end Utility_TabularDistribution_def.hpp

//---------------------------------------------------------------------------//
// end Utility_TabularDistribution_def.hpp
//---------------------------------------------------------------------------//
