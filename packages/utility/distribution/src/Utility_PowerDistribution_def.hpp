//---------------------------------------------------------------------------//
//!
//! \file   Utility_PowerDistribution_def.hpp
//! \author Alex Robinson
//! \brief  Power distribution class definition.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_POWER_DISTRIBUTION_DEF_HPP
#define UTILITY_POWER_DISTRIBUTION_DEF_HPP

// FRENSIE Includes
#include "Utility_ContractException.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ArrayString.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"

namespace Utility{

// Explicit instantiation (extern declaration)
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( UnitAwarePowerDistribution<1,void,void> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( UnitAwarePowerDistribution<2,void,void> );

// Default constructor
template<unsigned N, typename IndependentUnit, typename DependentUnit>
UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::UnitAwarePowerDistribution()
{ 
  // Make sure the exponent is valid
  testStaticPrecondition( N > 0 );
}

// Constructor
/*! \details This constructor will explicitly cast the input quantities to
 * the distribution quantity (which includes any unit-conversion). The
 * dimension type must match and there must be a unit-conversion defined using
 * the boost methodology.
 */
template<unsigned N, typename IndependentUnit, typename DependentUnit>
template<typename InputIndepQuantity>
UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::UnitAwarePowerDistribution( 
				     const double constant_multiplier,
				     const InputIndepQuantity min_indep_limit,
				     const InputIndepQuantity max_indep_limit )
  : d_multiplier( DMQT::initializeQuantity( constant_multiplier ) ),
    d_min_indep_limit( min_indep_limit ),
    d_min_indep_limit_to_power_Np1(),
    d_max_indep_limit( max_indep_limit ),
    d_max_indep_limit_to_power_Np1(),
    d_norm_constant()
{
  // Make sure the exponent is valid
  testStaticPrecondition( N > 0 );
  // Make sure that the values are valid
  testPrecondition( !QT::isnaninf( constant_multiplier ) );
  testPrecondition( !QuantityTraits<InputIndepQuantity>::isnaninf( min_indep_limit ) );
  testPrecondition( !QuantityTraits<InputIndepQuantity>::isnaninf( max_indep_limit ) );
  // Make sure that the min value is greater than or equal to zero
  testPrecondition( min_indep_limit >= 
		    QuantityTraits<InputIndepQuantity>::zero() );
  // Make sure that the max value is greater than the min value
  testPrecondition( max_indep_limit > min_indep_limit );

  this->initializeDistribution();
}

// Copy constructor
/*! \details Just like boost::units::quantity objects, the unit-aware 
 * distribution can be explicitly cast to a distribution with compatible
 * units. If the units are not compatible, this function will not compile. Note
 * that this allows distributions to be scaled safely (unit conversions 
 * are completely taken care of by boost::units)!
 */
template<unsigned N, typename IndependentUnit, typename DependentUnit>
template<typename InputIndepUnit, typename InputDepUnit>
UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::UnitAwarePowerDistribution( 
 const UnitAwarePowerDistribution<N,InputIndepUnit,InputDepUnit>& dist_instance )
  : d_multiplier(),
    d_min_indep_limit( dist_instance.d_min_indep_limit ),
    d_min_indep_limit_to_power_Np1(),
    d_max_indep_limit( dist_instance.d_max_indep_limit ),
    d_max_indep_limit_to_power_Np1(),
    d_norm_constant()
{
  // Make sure the exponent is valid
  testStaticPrecondition( N > 0 );
  // Make sure that the values are valid
  remember( typedef QuantityTraits<typename UnitAwarePowerDistribution<N,InputIndepUnit,InputDepUnit>::IndepQuantity> InputIQT );
  testPrecondition( !InputIQT::isnaninf( dist_instance.d_min_indep_limit ) );
  testPrecondition( !InputIQT::isnaninf( dist_instance.d_max_indep_limit ) );
  // Make sure that the min value is greater than or equal to zero
  testPrecondition( dist_instance.d_min_indep_limit >= InputIQT::zero() );
  // Make sure that the max value is greater than the min value
  testPrecondition( dist_instance.d_max_indep_limit > 
		    dist_instance.d_min_indep_limit );

  typedef typename UnitAwarePowerDistribution<N,InputIndepUnit,InputDepUnit>::DepQuantity InputDepQuantity;

  typedef typename UnitAwarePowerDistribution<N,InputIndepUnit,InputDepUnit>::IndepQuantity InputIndepQuantity;

  // Calculate the scaled multiplier (for complex units, boost::units has
  // problems doing the conversion so we will do it manually)
  d_multiplier = getRawQuantity( dist_instance.d_multiplier )*
    DepQuantity( QuantityTraits<InputDepQuantity>::one() )/
    PowerDistributionTraits<N>::powN( 
		  IndepQuantity( QuantityTraits<InputIndepQuantity>::one() ) );

  this->initializeDistribution();
}

// Copy constructor (copying from unitless distribution only)
template<unsigned N, typename IndependentUnit, typename DependentUnit>
UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::UnitAwarePowerDistribution( const UnitAwarePowerDistribution<N,void,void>& unitless_dist_instance, int )
  : d_multiplier( DMQT::initializeQuantity( unitless_dist_instance.d_multiplier ) ),
    d_min_indep_limit( IQT::initializeQuantity( unitless_dist_instance.d_min_indep_limit ) ),
    d_min_indep_limit_to_power_Np1(),
    d_max_indep_limit( IQT::initializeQuantity( unitless_dist_instance.d_max_indep_limit ) ),
    d_max_indep_limit_to_power_Np1(),
    d_norm_constant()
{
  // Make sure the exponent is valid
  testStaticPrecondition( N > 0 );
  // Make sure that the values are valid
  testPrecondition( !QT::isnaninf( unitless_dist_instance.d_multiplier ) );
  testPrecondition( !QT::isnaninf( unitless_dist_instance.d_min_indep_limit ));
  testPrecondition( !QT::isnaninf( unitless_dist_instance.d_max_indep_limit ));
  // Make sure that the min value is greater than or equal to zero
  testPrecondition( unitless_dist_instance.d_min_indep_limit >= QT::zero() );
  // Make sure that the max value is greater than the min value
  testPrecondition( unitless_dist_instance.d_max_indep_limit > 
		    unitless_dist_instance.d_min_indep_limit );

  this->initializeDistribution();
}

// Construct distribution from a unitless dist. (potentially dangerous)
/*! \details Constructing a unit-aware distribution from a unitless 
 * distribution is potentially dangerous. By forcing users to construct objects
 * using this method instead of a standard constructor we are trying to make
 * sure users are aware of the danger. This is designed to mimic the interface 
 * of the boost::units::quantity, which also has to deal with this issue. 
 */
template<unsigned N, typename IndependentUnit, typename DependentUnit>
UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit> 
UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::fromUnitlessDistribution( const UnitAwarePowerDistribution<N,void,void>& unitless_distribution )
{
  return ThisType( unitless_distribution, 0 );
}

// Assignment operator
template<unsigned N, typename IndependentUnit, typename DependentUnit>
UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>& 
UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::operator=( 
   const UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>& dist_instance )
{
  // Make sure the distribution is valid
  testPrecondition( dist_instance.d_min_indep_limit >= IQT::zero() );
  testPrecondition( dist_instance.d_max_indep_limit > 
		    dist_instance.d_min_indep_limit );
  
  if( this != &dist_instance )
  {
    d_multiplier = dist_instance.d_multiplier;
    
    d_min_indep_limit = dist_instance.d_min_indep_limit;
    
    d_min_indep_limit_to_power_Np1 = 
      dist_instance.d_min_indep_limit_to_power_Np1;
    
    d_max_indep_limit = dist_instance.d_max_indep_limit;
    
    d_max_indep_limit_to_power_Np1 = 
      dist_instance.d_max_indep_limit_to_power_Np1;
    
    d_norm_constant = dist_instance.d_norm_constant;
  }
  
  return *this;
}

// Evaluate the distribution
template<unsigned N, typename IndependentUnit, typename DependentUnit>
typename UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::DepQuantity
UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::evaluate( 
  const UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  if( indep_var_value < d_min_indep_limit )
    return DQT::zero();
  else if( indep_var_value > d_max_indep_limit )
    return DQT::zero();
  else
    return d_multiplier*PowerDistributionTraits<N>::powN( indep_var_value );
}

// Evaluate the PDF
template<unsigned N, typename IndependentUnit, typename DependentUnit>
typename UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::InverseIndepQuantity
UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::evaluatePDF( 
  const UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  return evaluate( indep_var_value )*d_norm_constant;
}

// Return a random sample from the distribution
template<unsigned N, typename IndependentUnit, typename DependentUnit>
typename UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::IndepQuantity 
UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::sample() const
{
  IndepQuantityNp1 argument = RandomNumberGenerator::getRandomNumber<double>()*
    (d_max_indep_limit_to_power_Np1 - d_min_indep_limit_to_power_Np1 ) +
    d_min_indep_limit_to_power_Np1;
  
  return PowerDistributionTraits<N>::np1Root( argument );
}

// Return a random sample from the distribution
template<unsigned N, typename IndependentUnit, typename DependentUnit>
typename UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::IndepQuantity 
UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::sample( 
  const UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::IndepQuantity min_independent_value,
  const UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::IndepQuantity max_independent_value )
{
  // Make sure that the values are valid
  testPrecondition( !IQT::isnaninf( min_independent_value ) );
  testPrecondition( !IQT::isnaninf( max_independent_value ) );
  // Make sure that the min value is greater than or equal to zero
  testPrecondition( min_independent_value >= IQT::zero() );
  // Make sure that the max value is greater than the min value
  testPrecondition( max_independent_value > min_independent_value );

  IndepQuantityNp1 min_indep_limit_to_power_np1 = 
    PowerDistributionTraits<N>::powNp1( min_independent_value );

  IndepQuantityNp1 argument = RandomNumberGenerator::getRandomNumber<double>()*
    (PowerDistributionTraits<N>::powNp1( max_independent_value ) -
     min_indep_limit_to_power_np1) + min_indep_limit_to_power_np1;

  return PowerDistributionTraits<N>::np1Root( argument );
}

// Return a random sample and record the number of trials
template<unsigned N, typename IndependentUnit, typename DependentUnit>
typename UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::sampleAndRecordTrials( unsigned& trials ) const
{
  ++trials;

  return this->sample();
}

// Return the upper bound of the distribution independent variable
template<unsigned N, typename IndependentUnit, typename DependentUnit>
typename UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::getUpperBoundOfIndepVar() const
{
  return d_max_indep_limit;
}

// Return the lower bound of the distribution independent variable
template<unsigned N, typename IndependentUnit, typename DependentUnit>
typename UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::getLowerBoundOfIndepVar() const 
{
  return d_min_indep_limit;
}

// Return the distribution type
template<unsigned N, typename IndependentUnit, typename DependentUnit>
OneDDistributionType 
UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::getDistributionType() const
{
  return PowerDistributionTraits<N>::distribution_type;
}

// Test if the distribution is continuous
template<unsigned N, typename IndependentUnit, typename DependentUnit>
bool 
UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::isContinuous() const
{
  return true;
}

// Method for placing the object in an output stream
template<unsigned N, typename IndependentUnit, typename DependentUnit>
void UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::toStream( 
						       std::ostream& os ) const
{
  os << "{" << getRawQuantity( d_multiplier )
     << "," << getRawQuantity( d_min_indep_limit )
     << "," << getRawQuantity( d_max_indep_limit )
     << "}";
}

// Method for initializing the object from an input stream
template<unsigned N, typename IndependentUnit, typename DependentUnit>
void UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::fromStream( 
							     std::istream& is )
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
			      "Error: the power " << N << " distribution "
			      "cannot be constructed because the "
			      "representation is not valid (see details "
			      "below)!\n" );

  Teuchos::Array<double> distribution;
  try{
    distribution = Teuchos::fromStringToArray<double>( dist_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
			      InvalidDistributionStringRepresentation,
			      "Error: the power " << N << " distribution "
			      "cannot be constructed because the "
			      "representation is not valid (see details "
			      "below)!\n" );
  
  TEST_FOR_EXCEPTION( distribution.size() < 2 || distribution.size() > 3,
		      InvalidDistributionStringRepresentation,
		      "Error: the power " << N << " distribution cannot be "
		      "constructed because the representation is not valid "
		      "(only 3 values may be specified)!" );

  // Set the constant multiplier
  if( distribution.size() == 3 )
    d_multiplier = DMQT::initializeQuantity( distribution[0] );
  else
    d_multiplier = DMQT::one();
  
  TEST_FOR_EXCEPTION( DMQT::isnaninf( d_multiplier ),
		      InvalidDistributionStringRepresentation,
		      "Error: the power " << N << " distribution cannot be "
		      "constructed because the constant multiplier is not "
		      "valid!" );
  
  // Read the min independent limit
  if( distribution.size() == 3 )
    d_min_indep_limit = IQT::initializeQuantity( distribution[1] );
  else
    d_min_indep_limit = IQT::initializeQuantity( distribution[0] );

  TEST_FOR_EXCEPTION( IQT::isnaninf( d_min_indep_limit ),
		      InvalidDistributionStringRepresentation,
		      "Error: the power " << N << " distribution cannot be "
		      "constructed because the min independent limit is not "
		      "valid!" );

  TEST_FOR_EXCEPTION( d_min_indep_limit < IQT::zero(),
		      InvalidDistributionStringRepresentation,
		      "Error: the power " << N << " distribution cannot be "
		      "constructed because the min independent limit is not "
		      "valid!" );

  // Read the max independent limit
  if( distribution.size() == 3 )
    d_max_indep_limit = IQT::initializeQuantity( distribution[2] );
  else
    d_max_indep_limit = IQT::initializeQuantity( distribution[1] );

  TEST_FOR_EXCEPTION( IQT::isnaninf( d_max_indep_limit ),
		      InvalidDistributionStringRepresentation,
		      "Error: the power " << N << " distribution cannot be "
		      "constructed because the max independent limit is not "
		      "valid!" );

  TEST_FOR_EXCEPTION( d_max_indep_limit <= d_min_indep_limit,
		      InvalidDistributionStringRepresentation,
		      "Error: the power " << N << " distribution cannot be "
		      "constructed because the max independent limit is not "
		      "valid!" );

  this->initializeDistribution();	      
}

// Method for testing if two objects are equivalent
template<unsigned N, typename IndependentUnit, typename DependentUnit>
bool UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::isEqual( const UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>& other ) const
{
  return d_multiplier == other.d_multiplier &&
    d_min_indep_limit == other.d_min_indep_limit &&
    d_max_indep_limit == other.d_max_indep_limit;
}

// Initialize the distribution
template<unsigned N, typename IndependentUnit, typename DependentUnit>
void UnitAwarePowerDistribution<N,IndependentUnit,DependentUnit>::initializeDistribution()
{
  // Take the limits to the power N+1
  d_min_indep_limit_to_power_Np1 = 
    PowerDistributionTraits<N>::powNp1( d_min_indep_limit );
  
  d_max_indep_limit_to_power_Np1 = 
    PowerDistributionTraits<N>::powNp1( d_max_indep_limit );
  
  // Calculate the normalization constant
  d_norm_constant = (N+1.0)/
    (d_multiplier*(d_max_indep_limit_to_power_Np1 - 
  		   d_min_indep_limit_to_power_Np1 ));
}

} // end Utility namespace

#endif // end UTILITY_POWER_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_PowerDistribution_def.hpp
//---------------------------------------------------------------------------//
