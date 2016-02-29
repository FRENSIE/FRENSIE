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
template<typename IndependentUnit, typename DependentUnit>
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::UnitAwareDeltaDistribution()
{ /* ... */ }

// Basic Constructor
template<typename IndependentUnit, typename DependentUnit>
template<typename InputIndepQuantity>
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::UnitAwareDeltaDistribution( const InputIndepQuantity location )
  : d_location( location ),
    d_multiplier( DQT::one() )
{
  // Make sure that the point is valid
  testPrecondition( !QuantityTraits<InputIndepQuantity>::isnaninf(location) );
}

// Advanced Constructor
template<typename IndependentUnit, typename DependentUnit>
template<typename InputIndepQuantity, typename InputDepQuantity>
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::UnitAwareDeltaDistribution( 
                                            const InputIndepQuantity location,
					    const InputDepQuantity multiplier )
  : d_location( location ),
    d_multiplier( multiplier )
{
  // Make sure that the point is valid
  testPrecondition( !QuantityTraits<InputIndepQuantity>::isnaninf( location ));
  // Make sure the multiplier is valid
  testPrecondition( !QuantityTraits<InputDepQuantity>::isnaninf( multiplier ));
  testPrecondition( multiplier != QuantityTraits<InputDepQuantity>::zero() );
}
  
// Copy constructor
/*! \details Just like boost::units::quantity objects, the unit-aware 
 * distribution can be explicitly cast to a distribution with compatible
 * units. If the units are not compatible, this function will not compile. Note
 * that this allows distributions to be scaled safely (unit conversions 
 * are completely taken care of by boost::units)!
 */
template<typename IndependentUnit, typename DependentUnit>
template<typename InputIndepUnit, typename InputDepUnit>
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::UnitAwareDeltaDistribution( 
 const UnitAwareDeltaDistribution<InputIndepUnit,InputDepUnit>& dist_instance )
  : d_location( dist_instance.d_location ),
    d_multiplier( dist_instance.d_multiplier )
{ 
  remember( typedef QuantityTraits<typename UnitAwareDeltaDistribution<InputIndepUnit,InputDepUnit>::IndepQuantity> InputIQT );
  remember( typedef QuantityTraits<typename UnitAwareDeltaDistribution<InputIndepUnit,InputDepUnit>::DepQuantity> InputDQT );
  // Make sure that the point is valid
  testPrecondition( !InputIQT::isnaninf( dist_instance.d_location ) );
  // Make sure that the multiplier is valid
  testPrecondition( !InputDQT::isnaninf( dist_instance.d_multiplier ) );
  testPrecondition( dist_instance.d_multiplier != InputDQT::zero() );
}

// Copy constructor (copying from unitless distribution only)
template<typename IndependentUnit, typename DependentUnit>
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::UnitAwareDeltaDistribution( 
const UnitAwareDeltaDistribution<void,void>& unitless_dist_instance, int )
  : d_location( IQT::initializeQuantity( unitless_dist_instance.d_location ) ),
    d_multiplier( DQT::initializeQuantity( unitless_dist_instance.d_multiplier ) )
{ 
  // Make sure that the point is valid
  testPrecondition( !QT::isnaninf( unitless_dist_instance.d_location ) );
  // Make sure that the multiplier is valid
  testPrecondition( !QT::isnaninf( unitless_dist_instance.d_multiplier ) );
  testPrecondition( unitless_dist_instance.d_multiplier != 0.0 );
}

// Construct distribution from a unitless dist. (potentially dangerous)
/*! \details Constructing a unit-aware distribution from a unitless 
 * distribution is potentially dangerous. By forcing users to construct objects
 * using this method instead of a standard constructor we are trying to make
 * sure users are aware of the danger. This is designed to mimic the interface 
 * of the boost::units::quantity, which also has to deal with this issue. 
 */
template<typename IndependentUnit, typename DependentUnit>
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit> UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::fromUnitlessDistribution( 
	   const UnitAwareDeltaDistribution<void,void>& unitless_distribution )
{
  return ThisType( unitless_distribution, 0 );
}

// Assignment operator
template<typename IndependentUnit, typename DependentUnit>
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>& 
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::operator=( 
 const UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>& dist_instance )
{
  if( this != &dist_instance )
  {
    d_location = dist_instance.d_location;
    
    d_multiplier = dist_instance.d_multiplier;
  }

  return *this;
}

// Evaluate the distribution
/*! \details The delta distribution is a continuous distribution
 * that can evaluate to one of two values: 0.0 and infinity. It is more
 * useful (and safer) to simply return 0.0 and a (the multiplier).
 */
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::DepQuantity
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::evaluate( 
   const typename UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  if( indep_var_value == d_location )
    return d_multiplier;
  else
    return DQT::zero();
}

// Evaluate the PDF
/*! \details The delta distribution is a continuous distribution
 * that can evaluate to one of two values: 0.0 and infinity. It is more
 * useful (and safer) to simply return 0.0 and 1.0.
 */
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity 
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::evaluatePDF( 
 const typename UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  if( indep_var_value == d_location )
    return QuantityTraits<InverseIndepQuantity>::one();
  else
    return QuantityTraits<InverseIndepQuantity>::zero();
}

// Evaluate the CDF
template<typename IndependentUnit, typename DependentUnit>
double UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::evaluateCDF( 
  const typename UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  if( indep_var_value < d_location )
    return 0.0;
  else
    return 1.0;
}

// Return a random sample from the distribution
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::IndepQuantity 
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::sample() const
{
  return d_location;
}

// Return a random sample from the corresponding CDF and record the number of trials
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::sampleAndRecordTrials( unsigned& trials ) const
{
  ++trials;
  
  return d_location;
}

// Return a random sample from the distribution and the sampled index 
template<typename IndependentUnit, typename DependentUnit>
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
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::IndepQuantity 
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::sampleWithRandomNumber( 
					     const double random_number ) const
{
  return d_location;
}

// Return a random sample from the distribution in a subrange
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::sampleInSubrange( 
 const typename UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::IndepQuantity max_indep_var ) const
{
  // Make sure the max independent variable is valid
  testPrecondition( max_indep_var >= d_location );

  return d_location;
}

// Return a random sample from the distribution at the given CDF value in a subrange
/*! \details The random number will be ignored since only a single value can
 * ever be returned
 */
template<typename IndependentUnit, typename DependentUnit>
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
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::getUpperBoundOfIndepVar() const
{
  return d_location;
}

// Return the minimum point at which the distribution is non-zero
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::getLowerBoundOfIndepVar() const
{
  return d_location;
}

// Return the distribution type
template<typename IndependentUnit, typename DependentUnit>
OneDDistributionType UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::getDistributionType() const
{
  return ThisType::distribution_type;
}

// Test if the distribution is continuous
/*! \details Though the delta distribution is technically continuous 
 * because it is only non-zero at the specified point it will be treated as
 * a discrete distribution.
 */
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::isContinuous() const
{
  return false;
}

// Method for placing the object in an output stream
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::toStream( std::ostream& os ) const
{
  os << "{" << getRawQuantity( d_location );
  
  if( d_multiplier != DQT::one() )
    os << "," << getRawQuantity( d_multiplier ) << "}";
  else
    os << "}";
}

// Method for initializing the object from an input stream
template<typename IndependentUnit, typename DependentUnit>
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

  TEST_FOR_EXCEPTION( distribution.size() < 1 || distribution.size() > 2,
		      InvalidDistributionStringRepresentation,
		      "Error: the delta distribution cannot be constructed "
		      "because the representation is not valid (only one or"
		      "two values can be specified)!" );
  
  setQuantity( d_location, distribution[0] );

  TEST_FOR_EXCEPTION( QT::isnaninf( distribution[0] ), 
		      InvalidDistributionStringRepresentation,
		      "Error: the delta distribution cannot be constructed " 
		      "because of an invalid location (" << distribution[0] <<
		      ")!" );

  if( distribution.size() > 1 )
  {
    setQuantity( d_multiplier, distribution[1] );

    TEST_FOR_EXCEPTION( QT::isnaninf( distribution[1] ),
			InvalidDistributionStringRepresentation,
			"Error: the delta distribution cannot be constructed "
			"because of an invalid multiplier ("
			<< distribution[1] << ")!" );
    
    TEST_FOR_EXCEPTION( distribution[1] == 0.0,
			InvalidDistributionStringRepresentation,
			"Error: the delta distribution cannot be constructed "
			"because of an invalid multiplier ("
			<< distribution[1] << ")!" );
  }
  else
    d_multiplier = DQT::one();
}

// Method for testing if two objects are equivalent
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::isEqual( 
 const UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>& other ) const
{
  return d_location == other.d_location &&
    d_multiplier == other.d_multiplier;
}

} // end Utility namespace

#endif // end UTILITY_DELTA_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utiliyt_DeltaDistribution_def.hpp
//---------------------------------------------------------------------------//
