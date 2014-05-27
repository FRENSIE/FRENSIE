//---------------------------------------------------------------------------//
//!
//! \file   Utility_ThirtyTwoEquiprobableBinDistribution.cpp
//! \author Alex Robinson
//! \brief  Thirty-Two equiprobable bin distribution class definition.
//!
//---------------------------------------------------------------------------//

// FRNECS Includes
#include "Utility_ThirtyTwoEquiprobableBinDistribution.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Constructor
ThirtyTwoEquiprobableBinDistribution::ThirtyTwoEquiprobableBinDistribution( 
				 const Teuchos::Array<double>& bin_boundaries )
: d_bin_boundaries( bin_boundaries )
{
  // Make sure there are exactly 33 bin boundaries
  testPrecondition( bin_boundaries.size() == 33 );
  // Make sure that the bins are sorted
  testPrecondition( Sort::isSortedAscending( bin_boundaries.begin(),
					     bin_boundaries.end() ) );
}

// Evaulate the distribution
double ThirtyTwoEquiprobableBinDistribution::evaluate( 
					   const double indep_var_value ) const
{
  return evaluatePDF( indep_var_value );
}

// Evaluate the PDF
double ThirtyTwoEquiprobableBinDistribution::evaluatePDF(
					   const double indep_var_value ) const
{
  if( indep_var_value < d_bin_boundaries.front() )
    return 0.0;
  else if( indep_var_value > d_bin_boundaries.back() )
    return 0.0;
  else
  {
    Teuchos::Array<double>::const_iterator lower_bin_boundary,
      upper_bin_boundary;
    
    if( indep_var_value >= d_bin_boundaries.front() &&
	indep_var_value < d_bin_boundaries.back() )
    {
      lower_bin_boundary = 
	Search::binaryLowerBound( d_bin_boundaries.begin(),
				  d_bin_boundaries.end(),
				  indep_var_value );

     upper_bin_boundary = lower_bin_boundary;
     ++upper_bin_boundary;
    }
    else
    {
      upper_bin_boundary = d_bin_boundaries.end();
      --upper_bin_boundary;
      
      lower_bin_boundary = upper_bin_boundary;
      --lower_bin_boundary;
    }
    
    return (1.0/32)/(*upper_bin_boundary - *lower_bin_boundary);
  }
}

// Return a random sample from the distribution
double ThirtyTwoEquiprobableBinDistribution::sample()
{
  return 
    (const_cast<const ThirtyTwoEquiprobableBinDistribution*>(this))->sample();
}

// Return a random sample from the distribution
double ThirtyTwoEquiprobableBinDistribution::sample() const
{
  double bin_location = 
    RandomNumberGenerator::getRandomNumber<double>()*32;
  
  unsigned index = (unsigned)floor(bin_location);
  
  return d_bin_boundaries[index] + 
    (bin_location - index)*(d_bin_boundaries[index+1]-d_bin_boundaries[index]);
}

// Return the sampling efficiency from the distribution
double ThirtyTwoEquiprobableBinDistribution::getSamplingEfficiency() const
{
  return 1.0;
}

// Return the upper bound of the distribution independent variable
double ThirtyTwoEquiprobableBinDistribution::getUpperBoundOfIndepVar() const
{
  return d_bin_boundaries.back();
}

// Return the lower bound of the distribution independent variable
double ThirtyTwoEquiprobableBinDistribution::getLowerBoundOfIndepVar() const
{
  return d_bin_boundaries.front();
}

// Return the distribution type
OneDDistributionType 
ThirtyTwoEquiprobableBinDistribution::getDistributionType() const
{
  return ThirtyTwoEquiprobableBinDistribution::distribution_type;
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_ThirtyTwoEquiprobableBinDistribution.cpp
//---------------------------------------------------------------------------//
