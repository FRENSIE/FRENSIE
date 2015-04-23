//---------------------------------------------------------------------------//
//!
//! \file   Utility_DeltaDistribution.cpp
//! \author Alex Robinson
//! \brief  Delta distribution class declaration.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "Utility_DeltaDistribution.hpp"
#include "Utility_ArrayString.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Default constructor
DeltaDistribution::DeltaDistribution()
{ /* ... */ }

// Constructor
DeltaDistribution::DeltaDistribution( const double location )
  : d_location( location )
{
  // Make sure that the point is valid
  testPrecondition( !ST::isnaninf( location ) );
}

// Copy constructor
DeltaDistribution::DeltaDistribution( const DeltaDistribution& dist_instance )
  : d_location( dist_instance.d_location )
{ /* ... */ }

// Assignment operator
DeltaDistribution& DeltaDistribution::operator=( 
				       const DeltaDistribution& dist_instance )
{
  if( this != &dist_instance )
    d_location = dist_instance.d_location;

  return *this;
}

// Evaluate the distribution
double DeltaDistribution::evaluate( const double indep_var_value ) const
{
  if( indep_var_value == d_location )
    return std::numeric_limits<double>::infinity();
  else
    return 0.0;
}

// Evaluate the PDF
double DeltaDistribution::evaluatePDF( const double indep_var_value ) const
{
  if( indep_var_value == d_location )
    return 1.0;
  else
    return 0.0;
}

// Evaluate the CDF
double DeltaDistribution::evaluateCDF( const double indep_var_value ) const
{
  if( indep_var_value < d_location )
    return 0.0;
  else
    return 1.0;
}

// Return a random sample from the distribution
double DeltaDistribution::sample() const
{
  return d_location;
}

//! Return a random sample from the corresponding CDF and record the number of trials
double DeltaDistribution::sampleAndRecordTrials( unsigned& trials ) const
{
  ++trials;
  
  return d_location;
}

// Return a random sample from the distribution and the sampled index 
double DeltaDistribution::sampleAndRecordBinIndex( 
					    unsigned& sampled_bin_index ) const
{
  sampled_bin_index = 0;

  return d_location;
}

// Return a random sample from the distribution at the given CDF value
/*! \details The random number will be ignored since only a single value can
 * every be returned
 */
double DeltaDistribution::sampleWithRandomNumber( 
					     const double random_number ) const
{
  return d_location;
}

// Return a random sample from the distribution in a subrange
double DeltaDistribution::sampleInSubrange( const double max_indep_var ) const
{
  // Make sure the max independent variable is valid
  testPrecondition( max_indep_var >= d_location );

  return d_location;
}

// Return a random sample from the distribution at the given CDF value in a subrange
/*! \details The random number will be ignored since only a single value can
 * every be returned
 */
double DeltaDistribution::sampleWithRandomNumberInSubrange( 
					     const double random_number,
					     const double max_indep_var ) const
{
  // Make sure the max independent variable is valid
  testPrecondition( max_indep_var >= d_location );

  return d_location;
}

// Return the maximum point at which the distribution is non-zero
double DeltaDistribution::getUpperBoundOfIndepVar() const
{
  return d_location;
}

// Return the minimum point at which the distribution is non-zero
double DeltaDistribution::getLowerBoundOfIndepVar() const
{
  return d_location;
}

// Return the distribution type
OneDDistributionType DeltaDistribution::getDistributionType() const
{
  return DeltaDistribution::distribution_type;
}

// Test if the distribution is continuous
/*! \details Though the delta distribution is technically continuous 
 * because it is only non-zero at the specified point it will be treated as
 * a discrete distribution.
 */
bool DeltaDistribution::isContinuous() const
{
  return false;
}

// Method for placing the object in an output stream
void DeltaDistribution::toStream( std::ostream& os ) const
{
  os << "{" << d_location << "}";
}

// Method for initializing the object from an input stream
void DeltaDistribution::fromStream( std::istream& is )
{
  // Read in the distribution representation
  std::string dist_rep;
  std::getline( is, dist_rep, '}' );
  dist_rep += '}';

  // Parse special characters
  try{
    ArrayString::locateAndReplacePi( dist_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
			      InvalidDistributionStringRepresentation,
			      "Error: the delta distribution cannot be "
			      "constructed because the representation is not "
			      "valid (see details below)!\n" );

  Teuchos::Array<double> distribution;
  try{
    distribution = Teuchos::fromStringToArray<double>( dist_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
			      InvalidDistributionStringRepresentation,
			      "Error: the delta distribution cannot be "
			      "constructed because the representation is not "
			      "valid (see details below)!\n" );

  TEST_FOR_EXCEPTION( distribution.size() != 1,
		      InvalidDistributionStringRepresentation,
		      "Error: the delta distribution cannot be constructed "
		      "because the representation is not valid (only one "
		      "value can be specified)!" );
  d_location = distribution[0];

  TEST_FOR_EXCEPTION( ST::isnaninf( d_location ), 
		      InvalidDistributionStringRepresentation,
		      "Error: the delta distribution cannot be constructed " 
		      "because of an invalid location (" << d_location <<
		      ")!" );
}

// Method for testing if two objects are equivalent
bool DeltaDistribution::isEqual( const DeltaDistribution& other ) const
{
  return d_location == other.d_location;
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utiliyt_DeltaDistribution.cpp
//---------------------------------------------------------------------------//
