//---------------------------------------------------------------------------//
//!
//! \file   Utility_UniformDistribution_def.hpp
//! \author Alex Robinson
//! \brief  Uniform distribution class definition
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_UNIFORM_DISTRIBUTION_DEF_HPP
#define UTILITY_UNIFORM_DISTRIBUTION_DEF_HPP

// FRENSIE Includes
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ArrayString.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

namespace Utility{

// Default constructor
template<typename IndependentUnit, typename DependentUnit>
UnitAwareUniformDistribution<IndependentUnit,DependentUnit>::UnitAwareUniformDistribution()
{ /* ... */ }

// Constructor
/*! \details A quantity with a different unit can be used as an input. This
 * will be explicitly cast to the desired unit during object construction.
 */
template<typename IndependentUnit, typename DependentUnit>
template<typename InputIndepQuantity, typename InputDepQuantity>
UnitAwareUniformDistribution<IndependentUnit,DependentUnit>::UnitAwareUniformDistribution( 
	                       const InputIndepQuantity& min_independent_value,
			       const InputIndepQuantity& max_independent_value,
			       const InputDepQuantity& dependent_value )
  : d_min_independent_value( min_independent_value ),
    d_max_independent_value( max_independent_value ),
    d_dependent_value( dependent_value ),
    d_pdf_value(1.0/(max_independent_value - min_independent_value))
{
  // Make sure that the values are valid
  testPrecondition( !ST::isnaninf( getRawQuantity( min_independent_value ) ) );
  testPrecondition( !ST::isnaninf( getRawQuantity( max_independent_value ) ) );
  testPrecondition( !ST::isnaninf( getRawQuantity( dependent_value ) ) );
  // Make sure that the max value is greater than the min value
  testPrecondition( max_independent_value > min_independent_value );
}

// Copy constructor
template<typename IndependentUnit, typename DependentUnit>
UnitAwareUniformDistribution<IndependentUnit,DependentUnit>::UnitAwareUniformDistribution( const UnitAwareUniformDistribution<IndependentUnit,DependentUnit>& dist_instance )
  : d_min_independent_value( dist_instance.d_min_independent_value ),
    d_max_independent_value( dist_instance.d_max_independent_value ),
    d_dependent_value( dist_instance.d_dependent_value ),
    d_pdf_value( dist_instance.d_pdf_value )
{
  // Make sure that the values are valid
  testPrecondition( !ST::isnaninf( getRawQuantity( dist_instance.d_min_independent_value ) ) );
  testPrecondition( !ST::isnaninf( getRawQuantity( dist_instance.d_max_independent_value ) ) );
  testPrecondition( !ST::isnaninf( getRawQuantity( dist_instance.d_dependent_value ) ) );
  // Make sure that the max value is greater than the min value
  testPrecondition( dist_instance.d_max_independent_value > 
		    dist_instance.d_min_independent_value );
}

// Assignment operator
template<typename IndependentUnit, typename DependentUnit>
UnitAwareUniformDistribution<IndependentUnit,DependentUnit>& UnitAwareUniformDistribution<IndependentUnit,DependentUnit>::operator=(
       const UnitAwareUniformDistribution<IndependentUnit,DependentUnit>& dist_instance )
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
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareUniformDistribution<IndependentUnit,DependentUnit>::DepQuantity
UnitAwareUniformDistribution<IndependentUnit,DependentUnit>::evaluate( 
const typename UnitAwareUniformDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  if( indep_var_value >= d_min_independent_value && 
      indep_var_value <= d_max_independent_value )
    return d_dependent_value;
  else
    return QuantityTraits<DepQuantity>::zero();
}

// Evaluate the PDF
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareUniformDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity
UnitAwareUniformDistribution<IndependentUnit,DependentUnit>::evaluatePDF(
const typename UnitAwareUniformDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  if( indep_var_value >= d_min_independent_value &&
      indep_var_value <= d_max_independent_value )
    return d_pdf_value;
  else
    return QuantityTraits<InverseIndepQuantity>::zero();
}

// Evaluate the CDF
template<typename IndependentUnit, typename DependentUnit>
double UnitAwareUniformDistribution<IndependentUnit,DependentUnit>::evaluateCDF(
const typename UnitAwareUniformDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  if( indep_var_value >= d_min_independent_value &&
      indep_var_value <= d_max_independent_value )
    return d_pdf_value*(indep_var_value - d_min_independent_value);
  else if( indep_var_value < d_min_independent_value )
    return 0.0;
  else
    return 1.0;
}

// Return a random sample from the distribution
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareUniformDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareUniformDistribution<IndependentUnit,DependentUnit>::sample() const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleWithRandomNumber( random_number );
}

// Return a random sample from the corresponding CDF and record the number of trials
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareUniformDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareUniformDistribution<IndependentUnit,DependentUnit>::sampleAndRecordTrials( unsigned& trials ) const
{
  ++trials;

  return this->sample();
}

// Return a random sample and sampled index from the corresponding CDF
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareUniformDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareUniformDistribution<IndependentUnit,DependentUnit>::sampleAndRecordBinIndex( 
					    unsigned& sampled_bin_index ) const
{
  sampled_bin_index = 0u;

  return this->sample();
}

// Return a random sample from the corresponding CDF in a subrange
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareUniformDistribution<IndependentUnit,DependentUnit>::IndepQuantity 
UnitAwareUniformDistribution<IndependentUnit,DependentUnit>::sampleInSubrange(const UnitAwareUniformDistribution<IndependentUnit,DependentUnit>::IndepQuantity max_indep_var ) const
{
  // Make sure the upper bound of the subrange is valid
  testPrecondition( max_indep_var <= d_max_independent_value );
  testPrecondition( max_indep_var >= d_min_independent_value );

  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleWithRandomNumberInSubrange( random_number,
						 max_indep_var );
}

// Return the upper bound of the distribution independent variable
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareUniformDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareUniformDistribution<IndependentUnit,DependentUnit>::getUpperBoundOfIndepVar() const
{
  return d_max_independent_value;
}

// Return the lower bound of the distribution independent variable
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareUniformDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareUniformDistribution<IndependentUnit,DependentUnit>::getLowerBoundOfIndepVar() const
{
  return d_min_independent_value;
}

// Return the distribution type
template<typename IndependentUnit, typename DependentUnit>
OneDDistributionType UnitAwareUniformDistribution<IndependentUnit,DependentUnit>::getDistributionType() const
{
  return UnitAwareUniformDistribution::distribution_type;
}

// Test if the distribution is continuous
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareUniformDistribution<IndependentUnit,DependentUnit>::isContinuous() const
{
  return true;
}

// Method for placing the object in an output stream
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareUniformDistribution<IndependentUnit,DependentUnit>::toStream( std::ostream& os ) const
{
  os << "{" << getRawQuantity( d_min_independent_value )
     << "," << getRawQuantity( d_max_independent_value )
     << "," << getRawQuantity( d_dependent_value )
     << "}";
}

// Method for initializing the object from an input stream
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareUniformDistribution<IndependentUnit,DependentUnit>::fromStream( std::istream& is )
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
			      "Error: the exponential distribution cannot be "
			      "constructed because the representation is not "
			      "valid (only three values may be specified)!" );

  Teuchos::Array<double> distribution;
  try{
    distribution = Teuchos::fromStringToArray<double>( dist_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
			      InvalidDistributionStringRepresentation,
			      "Error: the uniform distribution cannot be "
			      "constructed because the representation is not "
			      "valid (see details below)!\n" );
  
  TEST_FOR_EXCEPTION( distribution.size() < 2 || distribution.size() > 3,
		      InvalidDistributionStringRepresentation,
		      "Error: the exponential distribution cannot be "
		      "constructed because the representation is not valid "
		      "(only three values may be specified)!" );

  setQuantity( d_min_independent_value, distribution[0] );

  TEST_FOR_EXCEPTION( ST::isnaninf( getRawQuantity( d_min_independent_value )),
		      InvalidDistributionStringRepresentation,
		      "Error: the uniform distribution cannot be "
		      "constructed because of an invalid min "
		      "independent value " << 
		      getRawQuantity( d_min_independent_value ) );

  setQuantity( d_max_independent_value, distribution[1] );

  TEST_FOR_EXCEPTION( ST::isnaninf( getRawQuantity( d_max_independent_value )),
		      InvalidDistributionStringRepresentation,
		      "Error: the uniform distribution cannot be "
		      "constructed because of an invalid max "
		      "independent value " << 
		      getRawQuantity( d_max_independent_value ) );

  TEST_FOR_EXCEPTION( d_max_independent_value <= d_min_independent_value,
		      InvalidDistributionStringRepresentation,
		      "Error: the uniform distribution cannot be "
		      "constructed because of invalid independent values!" );

  if( distribution.size() == 3 )
    setQuantity( d_dependent_value, distribution[2] );
  else
    setQuantity( d_dependent_value, 1.0 );

  TEST_FOR_EXCEPTION( ST::isnaninf( getRawQuantity( d_dependent_value ) ),
		      InvalidDistributionStringRepresentation,
		      "Error: the uniform distribution cannot be "
		      "constructed because of an invalid dependent "
		      "value " << 
		      getRawQuantity( d_dependent_value ) );

  d_pdf_value = 1.0/(d_max_independent_value - d_min_independent_value);
}

// Method for testing if two objects are equivalent
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareUniformDistribution<IndependentUnit,DependentUnit>::isEqual( const UnitAwareUniformDistribution<IndependentUnit,DependentUnit>& other ) const
{
  return d_min_independent_value == other.d_min_independent_value &&
    d_max_independent_value == other.d_max_independent_value &&
    d_dependent_value == other.d_dependent_value &&
    d_pdf_value == other.d_pdf_value;
}

} // end Utility namespace

#endif // end UTILITY_UNIFORM_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_UniformDistribution_def.hpp
//---------------------------------------------------------------------------//
