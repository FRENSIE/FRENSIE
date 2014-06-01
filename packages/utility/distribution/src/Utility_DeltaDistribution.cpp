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
#include "Utility_ExceptionTestMacros.hpp"
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

// Return a random sample from the distribution
double DeltaDistribution::sample()
{
  return (const_cast<const DeltaDistribution*>(this))->sample();
}

// Return a random sample from the distribution
double DeltaDistribution::sample() const
{
  return d_location;
}

// Return the sampling efficiency from this distribution
double DeltaDistribution::getSamplingEfficiency() const
{
  return 1.0;
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

  Teuchos::Array<double> distribution;
  try{
    distribution = Teuchos::fromStringToArray<double>( dist_rep );
  }
  catch( Teuchos::InvalidArrayStringRepresentation& error )
  {
    std::string message( "Error: the delta distribution cannot be constructed "
			 "because the representation is not valid (see "
			 "details below)!\n" );
    message += error.what();

    throw InvalidDistributionStringRepresentation( message );
  }

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
