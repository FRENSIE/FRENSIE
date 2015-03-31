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
 * highest).
 */ 
template<typename InterpolationPolicy>
TabularDistribution<InterpolationPolicy>::TabularDistribution( 
			      const Teuchos::Array<double>& independent_values,
			      const Teuchos::Array<double>& dependent_values,
                  const bool interpret_dependent_values_as_cdf )
  : d_distribution( independent_values.size() ),
    d_norm_constant( 0.0 )
{
  if( interpret_dependent_values_as_cdf )
  {
    // Make sure that the bin values are sorted
    testPrecondition( Sort::isSortedAscending( dependent_values.begin(), 
					     dependent_values.end() ) );

    // Make sure that for n bin boundaries there are n bin values
    testPrecondition( independent_values.size() == dependent_values.size() );

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

    // Calculate the slopes of the PDF
    DataProcessor::calculateSlopes<FIRST,THIRD,FOURTH>( d_distribution );
  }
  else
  {
    initializeDistribution( independent_values, dependent_values );
  }
}

// Copy constructor
template<typename InterpolationPolicy>
TabularDistribution<InterpolationPolicy>::TabularDistribution(
		const TabularDistribution<InterpolationPolicy>& dist_instance )
  : d_distribution( dist_instance.d_distribution ),
    d_norm_constant( dist_instance.d_norm_constant )
{
  // Make sure the distribution is valid
  testPrecondition( dist_instance.d_distribution.size() > 0 );
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
  else if( indep_var_value == d_distribution.back().first )
    return d_distribution.back().third;
  else
  {
    DistributionArray::const_iterator start, end, lower_bin_boundary,
      upper_bin_boundary;
    start = d_distribution.begin();
    end = d_distribution.end();

    lower_bin_boundary = Search::binaryLowerBound<FIRST>( start,
							  end,
							  indep_var_value );

    upper_bin_boundary = lower_bin_boundary;
    ++upper_bin_boundary;
    
    double lower_indep_value = lower_bin_boundary->first;
    double lower_pdf_value = lower_bin_boundary->third;
    double upper_indep_value = upper_bin_boundary->first;
    double upper_pdf_value = upper_bin_boundary->third;
    
    return InterpolationPolicy::interpolate( lower_indep_value,
					     upper_indep_value,
					     indep_var_value,
					     lower_pdf_value,
					     upper_pdf_value );
  }
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
    DistributionArray::const_iterator start, end, lower_bin_boundary;
    start = d_distribution.begin();
    end = d_distribution.end();

    lower_bin_boundary = Search::binaryLowerBound<FIRST>( start,
							  end,
							  indep_var_value );

    double indep_diff = indep_var_value - lower_bin_boundary->first;

    return lower_bin_boundary->second + indep_diff*lower_bin_boundary->third +
           indep_diff*indep_diff/2.0 * lower_bin_boundary->fourth;
  }
}

// Return a random sample from the distribution
template<typename InterpolationPolicy>
inline double TabularDistribution<InterpolationPolicy>::sample()
{
  return (const_cast<const TabularDistribution<InterpolationPolicy>*>(this))->sample();
}

// Return a random sample from the distribution
template<typename InterpolationPolicy>
inline double TabularDistribution<InterpolationPolicy>::sample() const
{
  unsigned bin_index;
  
  return this->sample( bin_index );
}

// Return a random sample and bin index from the distribution
template<typename InterpolationPolicy>
double TabularDistribution<InterpolationPolicy>::sample( 
					    unsigned& sampled_bin_index ) const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  DistributionArray::const_iterator start, end, lower_bin_boundary;
  start = d_distribution.begin();
  end = d_distribution.end();

  lower_bin_boundary = Search::binaryLowerBound<SECOND>( start,
							 end,
							 random_number );

  // Calculate the sampled bin index
  sampled_bin_index = std::distance(d_distribution.begin(),lower_bin_boundary);

  // Calculate the sampled independent value
  double sample;
  
  double indep_value = lower_bin_boundary->first;
  double cdf_diff = random_number - lower_bin_boundary->second;
  double pdf_value = lower_bin_boundary->third;
  double slope = lower_bin_boundary->fourth;

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

// Return a random sample from the corresponding CDF in a subrange
template<typename InterpolationPolicy>
double TabularDistribution<InterpolationPolicy>::sample( 
					     const double max_indep_var ) const
{
  // Make sure the maximum indep var is valid
  testPrecondition( max_indep_var >= this->getLowerBoundOfIndepVar() );
  testPrecondition( max_indep_var <= this->getUpperBoundOfIndepVar() );
  
  if( max_indep_var == this->getLowerBoundOfIndepVar() )
    return max_indep_var;
  else if( max_indep_var >= this->getUpperBoundOfIndepVar() )
    return this->sample();
  else
  {
    // Find the CDF value at the maximum independent variable
    DistributionArray::const_iterator start, end, lower_bin_boundary;
    start = d_distribution.begin();
    end = d_distribution.end();

    lower_bin_boundary = Search::binaryLowerBound<FIRST>( start,
							  end,
							  max_indep_var );

    // cdf(x) = cdf(x0) + (x-x0)*pdf(x0) + 0.5*(x-x0)^2*m
    double indep_value_diff = max_indep_var - lower_bin_boundary->first;
    double cdf_max = lower_bin_boundary->second + 
      indep_value_diff*lower_bin_boundary->third +
      0.5*indep_value_diff*indep_value_diff*lower_bin_boundary->fourth;
    
    // Sample a scaled random number
    double random_number = RandomNumberGenerator::getRandomNumber<double>()*
      cdf_max;

    start = d_distribution.begin();
    end = d_distribution.end();
    
    lower_bin_boundary = Search::binaryLowerBound<SECOND>( start,
							   end,
							   random_number );
    // Calculate the sampled independent value
    double sample;
    
    double indep_value = lower_bin_boundary->first;
    double cdf_diff = random_number - lower_bin_boundary->second;
    double pdf_value = lower_bin_boundary->third;
    double slope = lower_bin_boundary->fourth;
    
    // x = x0 + [sqrt(pdf(x0)^2 + 2m[cdf(x)-cdf(x0)]) - pdf(x0)]/m 
    if( slope != 0.0 )
    {
      sample = indep_value + 
	(sqrt( pdf_value*pdf_value + 2*slope*cdf_diff ) - pdf_value)/slope;
    }
    // x = x0 + [cdf(x)-cdf(x0)]/pdf(x0) => L'Hopital's rule
    else
      sample =  indep_value + cdf_diff/pdf_value;

    // Make sure a valid cdf value was found
    testPostcondition( lower_bin_boundary->second <= cdf_max );
    // Make sure the sample is valid
    testPostcondition( !Teuchos::ScalarTraits<double>::isnaninf( sample ) );

    return sample;
  }
}

// Return a sample from the distribution at the given CDF value
template<typename InterpolationPolicy>
double TabularDistribution<InterpolationPolicy>::sampleWithValue( 
					    const double cdf_value ) const
{
  DistributionArray::const_iterator lower_bin_boundary = 
                       Search::binaryLowerBound<SECOND>( d_distribution.begin(),
                                                         d_distribution.end(),
                                                         cdf_value );

  // Calculate the sampled independent value
  double sample;
  
  double indep_value = lower_bin_boundary->first;
  double cdf_diff = cdf_value - lower_bin_boundary->second;
  double pdf_value = lower_bin_boundary->third;
  double slope = lower_bin_boundary->fourth;

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

// Return the sampling efficiency
template<typename InterpolationPolicy>
double TabularDistribution<InterpolationPolicy>::getSamplingEfficiency() const
{
  return 1.0;
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
template<typename InterpolationPolicy>
bool TabularDistribution<InterpolationPolicy>::isEqual( 
		  const TabularDistribution<InterpolationPolicy>& other ) const
{
  return d_distribution == other.d_distribution && 
    d_norm_constant == other.d_norm_constant;
}

// Initialize the distribution
template<typename InterpolationPolicy>
void TabularDistribution<InterpolationPolicy>::initializeDistribution(
			      const Teuchos::Array<double>& independent_values,
			      const Teuchos::Array<double>& dependent_values )
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
    d_distribution[i].first = independent_values[i];
    d_distribution[i].third = dependent_values[i];
  }

  // Create a CDF from the raw distribution data
  d_norm_constant = 
    DataProcessor::calculateContinuousCDF<FIRST,THIRD,SECOND>(d_distribution);

  // Calculate the slopes of the PDF
  DataProcessor::calculateSlopes<FIRST,THIRD,FOURTH>( d_distribution );
}
				       			    
} // end Utility namespace

#endif // end Utility_TabularDistribution_def.hpp

//---------------------------------------------------------------------------//
// end Utility_TabularDistribution_def.hpp
//---------------------------------------------------------------------------//
