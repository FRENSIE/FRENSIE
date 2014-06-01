//---------------------------------------------------------------------------//
//!
//! \file   Utility_UniformDistribution.cpp
//! \author Alex Robinson
//! \brief  Uniform distribution class declaration.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_UniformDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Utility{

// Default constructor
UniformDistribution::UniformDistribution()
{ /* ... */ }

// Constructor
UniformDistribution::UniformDistribution( const double min_independent_value, 
					  const double max_independent_value,
					  const double dependent_value )
  : d_min_independent_value( min_independent_value ),
    d_max_independent_value( max_independent_value ),
    d_dependent_value( dependent_value ),
    d_pdf_value( 1.0/(max_independent_value - min_independent_value) )
{
  // Make sure that the values are valid
  testPrecondition( !ST::isnaninf( min_independent_value ) );
  testPrecondition( !ST::isnaninf( max_independent_value ) );
  testPrecondition( !ST::isnaninf( dependent_value ) );
  // Make sure that the max value is greater than the min value
  testPrecondition( max_independent_value > min_independent_value );
}

// Copy constructor
UniformDistribution::UniformDistribution( 
				     const UniformDistribution& dist_instance )
  : d_min_independent_value( dist_instance.d_min_independent_value ),
    d_max_independent_value( dist_instance.d_max_independent_value ),
    d_dependent_value( dist_instance.d_dependent_value ),
    d_pdf_value( dist_instance.d_pdf_value )
{
  // Make sure that the values are valid
  testPrecondition( !ST::isnaninf( dist_instance.d_min_independent_value ) );
  testPrecondition( !ST::isnaninf( dist_instance.d_max_independent_value ) );
  testPrecondition( !ST::isnaninf( dist_instance.d_dependent_value ) );
  // Make sure that the max value is greater than the min value
  testPrecondition( dist_instance.d_max_independent_value > 
		    dist_instance.d_min_independent_value );
}

// Assignment operator
UniformDistribution& UniformDistribution::operator=(
				     const UniformDistribution& dist_instance )
{
  // Make sure that the distribution is valid
  testPrecondition( dist_instance.d_max_independent_value > 
		    dist_instance.d_min_independent_value );

  if( this != &dist_instance )
  {
    d_min_independent_value = dist_instance.d_min_independent_value;
    d_max_independent_value = dist_instance.d_max_independent_value;
    d_dependent_value = dist_instance.d_dependent_value;
    d_pdf_value = dist_instance.d_pdf_value;
  }

  return *this;
}

// Evaluate the distribution
double UniformDistribution::evaluate( const double indep_var_value ) const
{
  if( indep_var_value >= d_min_independent_value && 
      indep_var_value <= d_max_independent_value )
    return d_dependent_value;
  else
    return 0.0;
}

// Evaluate the PDF
double UniformDistribution::evaluatePDF( const double indep_var_value ) const
{
  if( indep_var_value >= d_min_independent_value &&
      indep_var_value <= d_max_independent_value )
    return d_pdf_value;
  else
    return 0.0;
}

// Return a random sample from the distribution
double UniformDistribution::sample()
{
  return (const_cast<const UniformDistribution*>(this))->sample();
}

// Return a random sample from the distribution
double UniformDistribution::sample() const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  return random_number*(d_max_independent_value - d_min_independent_value) +
    d_min_independent_value;
}

// Return the sampling efficiency from the distribution
double UniformDistribution::getSamplingEfficiency() const
{
  return 1.0;
}

// Return the upper bound of the distribution independent variable
double UniformDistribution::getUpperBoundOfIndepVar() const
{
  return d_max_independent_value;
}

// Return the lower bound of the distribution independent variable
double UniformDistribution::getLowerBoundOfIndepVar() const
{
  return d_min_independent_value;
}

// Return the distribution type
OneDDistributionType UniformDistribution::getDistributionType() const
{
  return UniformDistribution::distribution_type;
}

// Method for placing the object in an output stream
void UniformDistribution::toStream( std::ostream& os ) const
{
  os << "{" << d_min_independent_value
     << "," << d_max_independent_value
     << "," << d_dependent_value
     << "}";
}

// Method for initializing the object from an input stream
void UniformDistribution::fromStream( std::istream& is )
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
    std::string message( "Error: the uniform distribution cannot be "
			 "constructed because the representation is not valid "
			 "(see details below)!\n" );
    message += error.what();

    throw InvalidDistributionStringRepresentation( message );
  }

  TEST_FOR_EXCEPTION( distribution.size() != 3,
		      InvalidDistributionStringRepresentation,
		      "Error: the exponential distribution cannot be "
		      "constructed because the representation is not valid "
		      "(only three values may be specified)!" );

  d_min_independent_value = distribution[0];

  TEST_FOR_EXCEPTION( ST::isnaninf( d_min_independent_value ),
		      InvalidDistributionStringRepresentation,
		      "Error: the uniform distribution cannot be "
		      "constructed because of an invalid min "
		      "independent value " << d_min_independent_value );

  d_max_independent_value = distribution[1];

  TEST_FOR_EXCEPTION( ST::isnaninf( d_max_independent_value ),
		      InvalidDistributionStringRepresentation,
		      "Error: the uniform distribution cannot be "
		      "constructed because of an invalid max "
		      "independent value " << d_max_independent_value );

  TEST_FOR_EXCEPTION( d_max_independent_value <= d_min_independent_value,
		      InvalidDistributionStringRepresentation,
		      "Error: the uniform distribution cannot be "
		      "constructed because of invalid independent values!" );

  d_dependent_value = distribution[2];

  TEST_FOR_EXCEPTION( ST::isnaninf( d_dependent_value ),
		      InvalidDistributionStringRepresentation,
		      "Error: the uniform distribution cannot be "
		      "constructed because of an invalid dependent "
		      "value " << d_dependent_value );

  d_pdf_value = 1.0/(d_max_independent_value - d_min_independent_value);
}

// Method for testing if two objects are equivalent
bool UniformDistribution::isEqual( const UniformDistribution& other ) const
{
  return d_min_independent_value == other.d_min_independent_value &&
    d_max_independent_value == other.d_max_independent_value &&
    d_dependent_value == other.d_dependent_value &&
    d_pdf_value == other.d_pdf_value;
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_UniformDistribution.cpp
//---------------------------------------------------------------------------//
