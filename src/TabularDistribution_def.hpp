//---------------------------------------------------------------------------//
//!
//! \file   TabularDistribution_def.hpp
//! \author Alex Robinson
//! \brief  Tabular distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef TABULAR_DISTRIBUTION_DEF_HPP
#define TABULAR_DISTRIBUTION_DEF_HPP

// FACEMC Includes
#include "DataProcessor.hpp"
#include "SearchAlgorithms.hpp"
#include "RandomNumberGenerator.hpp"
#include "ContractException.hpp"

namespace FACEMC{

// Constructor
/*! \details The independent values are assumed to be sorted (lowest to 
 * highest).
 */ 
template<typename InterpolationPolicy>
TabularDistribution<InterpolationPolicy>::TabularDistribution( 
			      const Teuchos::Array<double>& independent_values,
			      const Teuchos::Array<double>& dependent_values )
  : d_distribution( independent_values.size() ),
    d_norm_constant( 0.0 )
{
  // Make sure that at least two points of the distribution are specified
  testPrecondition( independent_values.size() > 1 );
  // Make sure that every independent value has a dependent value
  testPrecondition( independent_values.size() == dependent_values.size() );

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

    lower_bin_boundary = Search::binarySearchContinuousData<FIRST>( start,
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

// Return a sample from the distribution
template<typename InterpolationPolicy>
double TabularDistribution<InterpolationPolicy>::sample()
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  DistributionArray::const_iterator start, end, lower_bin_boundary;
  start = d_distribution.begin();
  end = d_distribution.end();

  lower_bin_boundary = Search::binarySearchContinuousData<SECOND>( start,
								   end,
								   random_number );

  double indep_value = lower_bin_boundary->first;
  double cdf_diff = random_number - lower_bin_boundary->second;
  double pdf_value = lower_bin_boundary->third;
  double slope = lower_bin_boundary->fourth;

  // x = x0 + [sqrt(pdf(x0)^2 + 2m[cdf(x)-cdf(x0)]) - pdf(x0)]/m 
  return indep_value + 
    (sqrt( pdf_value*pdf_value + 2*slope*cdf_diff ) - pdf_value)/slope;
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
OneDDistribution 
TabularDistribution<InterpolationPolicy>::getDistributionType() const
{
  return TabularDistribution<InterpolationPolicy>::distribution_type;
}
				       			    
} // end FACEMC namespace

#endif // end TabularDistribution_def.hpp

//---------------------------------------------------------------------------//
// end TabularDistribution_def.hpp
//---------------------------------------------------------------------------//
