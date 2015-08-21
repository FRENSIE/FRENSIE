//---------------------------------------------------------------------------//
//!
//! \file   Utility_DeltaDistribution_def.hpp
//! \author Alex Robinson
//! \brief  Delta distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_DELTA_DISTRIBUTION_DEF_HPP
#define UTILITY_DELTA_DISTRIBUTION_DEF_HPP

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "Utility_ArrayString.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Default constructor
template<typename IndependentUnit,typename DependentUnit>
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::UnitAwareDeltaDistribution()
{ /* ... */ }

// Constructor
template<typename IndependentUnit,typename DependentUnit>
template<typename InputIndepQuantity>
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::UnitAwareDeltaDistribution( const InputIndepQuantity location )
  : d_location( location )
{
  // Make sure that the point is valid
  testPrecondition( !ST::isnaninf( getRawQuantity( location ) ) );
}

// Copy constructor
template<typename IndependentUnit,typename DependentUnit>
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::UnitAwareDeltaDistribution( const UnitAwareDeltaDistribution& dist_instance )
  : d_location( dist_instance.d_location )
{ /* ... */ }

// Assignment operator
template<typename IndependentUnit,typename DependentUnit>
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>& 
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::operator=( 
  const UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>& dist_instance )
{
  if( this != &dist_instance )
    d_location = dist_instance.d_location;

  return *this;
}

// Evaluate the distribution
/*! \details The delta distribution is technically a continuous distribution
 * which can evaluate to one of two values: 0.0 and infinity. It is more
 * useful to simply return 0.0 and 1.0.
 */
template<typename IndependentUnit,typename DependentUnit>
typename UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::DepQuantity
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::evaluate( const typename UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  if( indep_var_value == d_location )
    return QuantityTraits<DepQuantity>::one();
  else
    return QuantityTraits<DepQuantity>::zero();
}

// Evaluate the PDF
template<typename IndependentUnit,typename DependentUnit>
typename UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity 
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::evaluatePDF( const typename UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  if( indep_var_value == d_location )
    return QuantityTraits<InverseIndepQuantity>::one();
  else
    return QuantityTraits<InverseIndepQuantity>::zero();
}

// Evaluate the CDF
template<typename IndependentUnit,typename DependentUnit>
double UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::evaluateCDF( const typename UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  if( indep_var_value < d_location )
    return 0.0;
  else
    return 1.0;
}

// Return a random sample from the distribution
template<typename IndependentUnit,typename DependentUnit>
typename UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::IndepQuantity 
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::sample() const
{
  return d_location;
}

// Return a random sample from the corresponding CDF and record the number of trials
template<typename IndependentUnit,typename DependentUnit>
typename UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::sampleAndRecordTrials( unsigned& trials ) const
{
  ++trials;
  
  return d_location;
}

// Return a random sample from the distribution and the sampled index 
template<typename IndependentUnit,typename DependentUnit>
typename UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::sampleAndRecordBinIndex( 
					    unsigned& sampled_bin_index ) const
{
  sampled_bin_index = 0;

  return d_location;
}

// Return a random sample from the distribution at the given CDF value
/*! \details The random number will be ignored since only a single value can
 * every be returned
 */
template<typename IndependentUnit,typename DependentUnit>
typename UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::IndepQuantity 
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::sampleWithRandomNumber( 
					     const double random_number ) const
{
  return d_location;
}

// Return a random sample from the distribution in a subrange
template<typename IndependentUnit,typename DependentUnit>
typename UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::sampleInSubrange( const typename UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::IndepQuantity max_indep_var ) const
{
  // Make sure the max independent variable is valid
  testPrecondition( max_indep_var >= d_location );

  return d_location;
}

// Return a random sample from the distribution at the given CDF value in a subrange
/*! \details The random number will be ignored since only a single value can
 * ever be returned
 */
template<typename IndependentUnit,typename DependentUnit>
typename UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::sampleWithRandomNumberInSubrange( 
 const double random_number,
 const typename UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::IndepQuantity max_indep_var ) const
{
  // Make sure the max independent variable is valid
  testPrecondition( max_indep_var >= d_location );

  return d_location;
}

// Return the maximum point at which the distribution is non-zero
template<typename IndependentUnit,typename DependentUnit>
typename UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::getUpperBoundOfIndepVar() const
{
  return d_location;
}

// Return the minimum point at which the distribution is non-zero
template<typename IndependentUnit,typename DependentUnit>
typename UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::getLowerBoundOfIndepVar() const
{
  return d_location;
}

// Return the distribution type
template<typename IndependentUnit,typename DependentUnit>
OneDDistributionType UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::getDistributionType() const
{
  return UnitAwareDeltaDistribution::distribution_type;
}

// Test if the distribution is continuous
/*! \details Though the delta distribution is technically continuous 
 * because it is only non-zero at the specified point it will be treated as
 * a discrete distribution.
 */
template<typename IndependentUnit,typename DependentUnit>
bool UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::isContinuous() const
{
  return false;
}

// Method for placing the object in an output stream
template<typename IndependentUnit,typename DependentUnit>
void UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::toStream( std::ostream& os ) const
{
  os << "{" << getRawQuantity( d_location ) << "}";
}

// Method for initializing the object from an input stream
template<typename IndependentUnit,typename DependentUnit>
void UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::fromStream( std::istream& is )
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
  setQuantity( d_location, distribution[0] );

  TEST_FOR_EXCEPTION( ST::isnaninf( distribution[0] ), 
		      InvalidDistributionStringRepresentation,
		      "Error: the delta distribution cannot be constructed " 
		      "because of an invalid location (" << distribution[0] <<
		      ")!" );
}

// Method for testing if two objects are equivalent
template<typename IndependentUnit,typename DependentUnit>
bool UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::isEqual( const UnitAwareDeltaDistribution& other ) const
{
  return d_location == other.d_location;
}

} // end Utility namespace

#endif // end UTILITY_DELTA_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utiliyt_DeltaDistribution_def.hpp
//---------------------------------------------------------------------------//
