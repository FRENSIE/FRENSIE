//---------------------------------------------------------------------------//
//!
//! \file   Utility_EquiprobableBinDistribution.cpp
//! \author Alex Robinson
//! \brief  Equiprobable bin distribution class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_EquiprobableBinDistribution.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ArrayString.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Utility{

// Default constructor
EquiprobableBinDistribution::EquiprobableBinDistribution()
{ /* ... */ }

// Constructor
EquiprobableBinDistribution::EquiprobableBinDistribution( 
				 const Teuchos::Array<double>& bin_boundaries )
: d_bin_boundaries( bin_boundaries )
{
  // Make sure there is at least one bin
  testPrecondition( bin_boundaries.size() > 1 );
  // Make sure that the bins are sorted
  testPrecondition( Sort::isSortedAscending( bin_boundaries.begin(),
					     bin_boundaries.end() ) );
}

// Copy constructor
EquiprobableBinDistribution::EquiprobableBinDistribution(
		    const EquiprobableBinDistribution& dist_instance )
  : d_bin_boundaries( dist_instance.d_bin_boundaries )
{ /* ... */ }

// Assignment operator
EquiprobableBinDistribution& 
EquiprobableBinDistribution::operator=(
		             const EquiprobableBinDistribution& dist_instance )
{
  if( this != &dist_instance )
    d_bin_boundaries = dist_instance.d_bin_boundaries;

  return *this;
}


// Evaulate the distribution
double EquiprobableBinDistribution::evaluate( 
					   const double indep_var_value ) const
{
  return evaluatePDF( indep_var_value );
}

// Evaluate the PDF
double EquiprobableBinDistribution::evaluatePDF(
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
    
    return (1.0/(d_bin_boundaries.size()-1))/
      (*upper_bin_boundary - *lower_bin_boundary);
  }
}

// Evaluate the CDF
double EquiprobableBinDistribution::evaluateCDF( 
					   const double indep_var_value ) const
{
  if( indep_var_value < d_bin_boundaries.front() )
    return 0.0;
  else if( indep_var_value >= d_bin_boundaries.back() )
    return 1.0;
  else
  {
    unsigned bin_index = 
      Search::binaryLowerBoundIndex( d_bin_boundaries.begin(),
				     d_bin_boundaries.end(),
				     indep_var_value );

    unsigned bins = d_bin_boundaries.size()-1;
    
    double bin_contribution = (indep_var_value - d_bin_boundaries[bin_index])/
      (d_bin_boundaries[bin_index+1] - d_bin_boundaries[bin_index]);

    return (bin_index + bin_contribution)/bins;
  }
}

// Return a random sample from the distribution
double EquiprobableBinDistribution::sample() const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  unsigned dummy_index;

  return this->sampleImplementation( random_number, dummy_index );
}

// Return a random sample and record the number of trials
double EquiprobableBinDistribution::sampleAndRecordTrials( unsigned& trials ) const
{
  ++trials;

  return this->sample();
}

// Return a random sample from the distribution and the sampled index 
double EquiprobableBinDistribution::sampleAndRecordBinIndex( 
					    unsigned& sampled_bin_index ) const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleImplementation( random_number, sampled_bin_index );
}

// Return a random sample from the distribution at the given CDF value
double EquiprobableBinDistribution::sampleWithRandomNumber( 
					     const double random_number ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );

  unsigned dummy_index;

  return this->sampleImplementation( random_number, dummy_index );
}

// Return a random sample from the distribution in a subrange
double EquiprobableBinDistribution::sampleInSubrange( 
					     const double max_indep_var ) const
{
  // Make sure the max independent variable is valid
  testPrecondition( max_indep_var >= d_bin_boundaries.front() );

  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleWithRandomNumberInSubrange( random_number,
						 max_indep_var );
}

// Return the upper bound of the distribution independent variable
double EquiprobableBinDistribution::getUpperBoundOfIndepVar() const
{
  return d_bin_boundaries.back();
}

// Return the lower bound of the distribution independent variable
double EquiprobableBinDistribution::getLowerBoundOfIndepVar() const
{
  return d_bin_boundaries.front();
}

// Return the distribution type
OneDDistributionType EquiprobableBinDistribution::getDistributionType() const
{
  return EquiprobableBinDistribution::distribution_type;
}

// Test if the distribution is continuous
bool EquiprobableBinDistribution::isContinuous() const
{
  return true;
}

// Method for placing the object in an output stream
void EquiprobableBinDistribution::toStream( std::ostream& os ) const
{
  os << d_bin_boundaries;
}

// Method for initializing the object from an input stream
void EquiprobableBinDistribution::fromStream( std::istream& is )
{
  std::string bin_boundaries_rep;
  std::getline( is, bin_boundaries_rep, '}' );
  bin_boundaries_rep += "}";
  
  // Parse special characters
  try{
    ArrayString::locateAndReplacePi( bin_boundaries_rep );
    ArrayString::locateAndReplaceIntervalOperator( bin_boundaries_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
			      InvalidDistributionStringRepresentation,
			      "Error: the equiprobable bin distribution "
			      "cannot be constructed because the "
			      "representation is not valid (see details "
			      "below)!\n" );

  try{
    d_bin_boundaries = Teuchos::fromStringToArray<double>( bin_boundaries_rep);
  }
  EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
			      InvalidDistributionStringRepresentation,
			      "Error: the equiprobable bin distribution "
			      "cannot be constructed because the "
			      "representation is not valid (see details "
			      "below)!\n" );
  
  TEST_FOR_EXCEPTION( d_bin_boundaries.size() <= 1,
		      InvalidDistributionStringRepresentation, 
		      "Error: the equiprobable bin distribution cannot be "
		      "constructed because at least one bin (two boundaries) "
		      "is required!\n" );

  TEST_FOR_EXCEPTION( !Sort::isSortedAscending( d_bin_boundaries.begin(),
						d_bin_boundaries.end() ),
		      InvalidDistributionStringRepresentation, 
		      "Error: the equiprobable bin distribution cannot be "
		      "constructed because the bin boundaries "
		      << bin_boundaries_rep << " are not sorted!" );
}

// Method for testing if two objects are equivalent
bool EquiprobableBinDistribution::isEqual( 
		      const EquiprobableBinDistribution& other ) const
{
  return d_bin_boundaries == other.d_bin_boundaries;
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_EquiprobableBinDistribution.cpp
//---------------------------------------------------------------------------//
