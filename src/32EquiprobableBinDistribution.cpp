//---------------------------------------------------------------------------//
//!
//! \file   32EquiprobableBinDistribution.cpp
//! \author Alex Robinson
//! \brief  32 equiprobable bin distribution class definition.
//!
//---------------------------------------------------------------------------//

// FACEMC Includes
#include "32EquiprobableBinDistribution.hpp"
#include "SearchAlgorithms.hpp"
#include "RandomNumberGenerator.hpp"
#include "ContractException.hpp"

namespace FACEMC{

// Constructor
32EquiprobableBinDistribution::32EquiprobableBinDistribution( 
				 const Teuchos::Array<double>& bin_boundaries )
: d_bin_boundaries( bin_boundaries )
{
  // Make sure there are exactly 33 bin boundaries
  testPrecondition( bin_boundaries.size() == 33 );
}

// Evaulate the distribution
double 32EquiprobableBinDistribution::evaluate( 
					   const double indep_var_value ) const
{
  return evaluatePDF();
}

// Evaluate the PDF
double 32EquiprobableBinDistribution::evaluatePDF(
					   const double indep_var_value ) const
{
  if( indep_var_value < d_bin_boundaries.front() )
    return 0.0;
  else if( indep_var_value > d_bin_boundaries.back() )
    return 0.0;
  else
  {
    Teuchos::Array<double>::const_iterator lower_bin_boundary =
      Search::binarySearchContinuousData( d_bin_boundaries.begin(),
					  d_bin_boundaries.end(),
					  indep_var_value );

    Teuchos::Array<double>::const_iterator upper_bin_boundary = 
      lower_bin_boundary;
    ++upper_bin_boundary;
    
    return (1.0/32)*(*upper_bin_boundary - *lower_bin_boundary);
  }
}

// Return a random sample from the distribution
double 32EquiprobableBinDistribution::sample()
{
  return (const_cast<32EquiprobableBinDistribution*>(this))->sample();
}

// Return a random sample from the distribution
double 32EquiprobableBinDistribution::sample() const
{
  double bin_location = 
    RandomNumberGenerator::getRandomNumber<double>()*32;
  
  unsigned index = (unsigned)floor(bin_location);
  
  return d_bin_boundaries[index] + 
    (bin_location - index)*(d_bin_boundaries[index+1]-d_bin_boundaries[index]);
}

// Return the sampling efficiency from the distribution
double 32EquiprobableBinDistribution::getSamplingEfficiency() const
{
  return 1.0;
}

// Return the upper bound of the distribution independent variable
double 32EquiprobableBinDistribution::getUpperBoundOfIndepVar() const
{
  return d_distribution.back();
}

// Return the lower bound of the distribution independent variable
double 32EquiprobableBinDistribution::getLowerBoundOfIndepVar() const
{
  return d_distribution.front();
}

// Return the distribution type
OneDDistributionType 32EquiprobableBinDistribution::getDistributionType() const
{
  return 32EquiprobableBinDistribution::distribution_type;
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end 32EquiprobableBinDistribution.cpp
//---------------------------------------------------------------------------//
