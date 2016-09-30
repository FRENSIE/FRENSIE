//---------------------------------------------------------------------------//
//!
//! \file   Utility_NormalDistribution_def.hpp
//! \author Alex Robinson
//! \brief  Normal distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_NORMAL_DISTRIBUTION_DEF_HPP
#define UTILITY_NORMAL_DISTRIBUTION_DEF_HPP

// FRENSIE Includes
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ArrayString.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Explicit instantiation (extern declaration)
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareNormalDistribution<void,void> );

// Initialize the constant norm factor
template<typename IndependentUnit, typename DependentUnit>
const double UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::constant_norm_factor = 1.0/sqrt( 2*PhysicalConstants::pi );

// Constructor
/*! \details This constructor will explicitly cast the input quantities to
 * the distribution quantity (which includes any unit-conversion). The
 * dimension type must match and there must be a unit-conversion defined using
 * the boost methodology.
 */
template<typename IndependentUnit, typename DependentUnit>
template<typename InputDepQuantity,
	 typename InputIndepQuantityA,
	 typename InputIndepQuantityB,
	 typename InputIndepQuantityC>
UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::UnitAwareNormalDistribution(
			      const InputIndepQuantityA mean,
			      const InputIndepQuantityB standard_deviation,
                              const InputDepQuantity constant_multiplier,
			      const InputIndepQuantityC min_independent_value,
			      const InputIndepQuantityC max_independent_value )
  : d_constant_multiplier( constant_multiplier ),
    d_mean( mean ),
    d_standard_deviation( standard_deviation ),
    d_min_independent_value( min_independent_value ),
    d_max_independent_value( max_independent_value )
{
  // Make sure that the values are valid
  testPrecondition( !QuantityTraits<InputDepQuantity>::isnaninf( constant_multiplier ) );
  testPrecondition( constant_multiplier !=
		    QuantityTraits<InputDepQuantity>::zero() );
  testPrecondition( !QuantityTraits<InputIndepQuantityA>::isnaninf( mean ) );
  testPrecondition( !QuantityTraits<InputIndepQuantityB>::isnaninf( standard_deviation ) );
  // Make sure that the standard deviation is positive
  testPrecondition( standard_deviation >
		    QuantityTraits<InputIndepQuantityB>::zero() );
  // Make sure that the min indep value is < the max indep value
  testPrecondition( min_independent_value < max_independent_value );
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
UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::UnitAwareNormalDistribution(
  const UnitAwareNormalDistribution<InputIndepUnit,InputDepUnit>& dist_instance )
  : d_constant_multiplier( dist_instance.d_constant_multiplier ),
    d_mean( dist_instance.d_mean ),
    d_standard_deviation( dist_instance.d_standard_deviation ),
    d_min_independent_value( dist_instance.d_min_independent_value ),
    d_max_independent_value( dist_instance.d_max_independent_value )
{
  remember( typedef QuantityTraits<typename UnitAwareNormalDistribution<InputIndepUnit,InputDepUnit>::IndepQuantity> InputIQT );
  remember( typedef QuantityTraits<typename UnitAwareNormalDistribution<InputIndepUnit,InputDepUnit>::DepQuantity> InputDQT );
  // Make sure that the values are valid
  testPrecondition( !InputDQT::isnaninf( dist_instance.d_constant_multiplier ) );
  testPrecondition( dist_instance.d_constant_multiplier != InputDQT::zero() );
  testPrecondition( !InputIQT::isnaninf( dist_instance.d_mean ) );
  testPrecondition( !InputIQT::isnaninf( dist_instance.d_standard_deviation ) );
  // Make sure that the standard deviation is positive
  testPrecondition( dist_instance.d_standard_deviation > InputIQT::zero() );
}

// Copy constructor (copying from unitless distribution only)
template<typename IndependentUnit, typename DependentUnit>
UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::UnitAwareNormalDistribution( const UnitAwareNormalDistribution<void,void>& unitless_dist_instance, int )
  : d_constant_multiplier( DQT::initializeQuantity( unitless_dist_instance.d_constant_multiplier ) ),
    d_mean( IQT::initializeQuantity( unitless_dist_instance.d_mean ) ),
    d_standard_deviation( IQT::initializeQuantity( unitless_dist_instance.d_standard_deviation ) ),
    d_min_independent_value( IQT::initializeQuantity( unitless_dist_instance.d_min_independent_value ) ),
    d_max_independent_value( IQT::initializeQuantity( unitless_dist_instance.d_max_independent_value ) )
{
  // Make sure that the values are valid
  testPrecondition( !QT::isnaninf( unitless_dist_instance.d_constant_multiplier ) );
  testPrecondition( unitless_dist_instance.d_constant_multiplier != 0.0 );
  testPrecondition( !QT::isnaninf( unitless_dist_instance.d_mean ) );
  testPrecondition( !QT::isnaninf( unitless_dist_instance.d_standard_deviation ) );
  // Make sure that the standard deviation is positive
  testPrecondition( unitless_dist_instance.d_standard_deviation > 0.0 );
}

// Construct distribution from a unitless dist. (potentially dangerous)
/*! \details Constructing a unit-aware distribution from a unitless
 * distribution is potentially dangerous. By forcing users to construct objects
 * using this method instead of a standard constructor we are trying to make
 * sure users are aware of the danger. This is designed to mimic the interface
 * of the boost::units::quantity, which also has to deal with this issue.
 */
template<typename IndependentUnit, typename DependentUnit>
UnitAwareNormalDistribution<IndependentUnit,DependentUnit>
UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::fromUnitlessDistribution( const UnitAwareNormalDistribution<void,void>& unitless_distribution )
{
  return ThisType( unitless_distribution, 0 );
}

// Assignment operator
template<typename IndependentUnit, typename DependentUnit>
UnitAwareNormalDistribution<IndependentUnit,DependentUnit>&
UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::operator=(
  const UnitAwareNormalDistribution<IndependentUnit,DependentUnit>& dist_instance )
{
  // Make sure that the values are valid
  testPrecondition( !DQT::isnaninf( dist_instance.d_constant_multiplier ) );
  testPrecondition( dist_instance.d_constant_multiplier != DQT::zero() );
  testPrecondition( !IQT::isnaninf( dist_instance.d_mean ) );
  testPrecondition( !IQT::isnaninf( dist_instance.d_standard_deviation ) );
  // Make sure that the standard deviation is positive
  testPrecondition( dist_instance.d_standard_deviation > IQT::zero() );

  if( this != &dist_instance )
  {
    d_constant_multiplier = dist_instance.d_constant_multiplier;
    d_mean = dist_instance.d_mean;
    d_standard_deviation = dist_instance.d_standard_deviation;
    d_min_independent_value = dist_instance.d_min_independent_value;
    d_max_independent_value = dist_instance.d_max_independent_value;
  }

  return *this;
}

// Evaluate the distribution
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::DepQuantity
UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::evaluate( const UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  if( indep_var_value < d_min_independent_value )
    return DQT::zero();
  else if( indep_var_value > d_max_independent_value )
    return DQT::zero();
  else
  {
    double argument = -(indep_var_value-d_mean)*(indep_var_value-d_mean)/
      (2.0*d_standard_deviation*d_standard_deviation);

    return d_constant_multiplier*exp( argument );
  }
}

// Evaluate the PDF
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity
UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::evaluatePDF( const UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  if( indep_var_value < d_min_independent_value )
    return IIQT::zero();
  else if( indep_var_value > d_max_independent_value )
    return IIQT::zero();
  else
  {
    double argument = -(indep_var_value-d_mean)*(indep_var_value-d_mean)/
      (2.0*d_standard_deviation*d_standard_deviation);

    return UnitAwareNormalDistribution::constant_norm_factor*exp( argument )/
      d_standard_deviation;
  }
}

// Return a random sample from the distribution
template<typename IndependentUnit, typename DependentUnit>
inline typename UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::sample(
			            const IndepQuantity mean,
				    const IndepQuantity standard_deviation,
				    const IndepQuantity min_independent_value,
			            const IndepQuantity max_independent_value )
{
  unsigned number_of_trials;

  return ThisType::sampleAndRecordTrials( number_of_trials,
					  mean,
					  standard_deviation,
					  min_independent_value,
					  max_independent_value );
}

// Return a random sample from the distribution
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::sample() const
{
  return ThisType::sample( d_mean,
			   d_standard_deviation,
			   d_min_independent_value,
			   d_max_independent_value );
}

// Return a random sample from the distribution
template<typename IndependentUnit, typename DependentUnit>
inline typename UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::sampleAndRecordTrials(
				    unsigned& trials,
			            const IndepQuantity mean,
				    const IndepQuantity standard_deviation,
				    const IndepQuantity min_independent_value,
			            const IndepQuantity max_independent_value )
{
  double random_number_1, random_number_2;
  double x, y;
  IndepQuantity sample;

  while( true )
  {
    // Use the rejection sampling technique outlined by Kahn in "Applications
    // of Monte Carlo" (1954)
    while( true )
    {
      ++trials;

      random_number_1 = RandomNumberGenerator::getRandomNumber<double>();
      random_number_2 = RandomNumberGenerator::getRandomNumber<double>();

      x = -log( random_number_1 );
      y = -log( random_number_2 );

      if( 0.5*(x - 1)*(x - 1) <= y )
      	break;
    }

    if( RandomNumberGenerator::getRandomNumber<double>() < 0.5 )
      x *= -1.0;

    // stretch and shift the sampled value
    sample = standard_deviation*x+mean;

    if( sample >= min_independent_value &&
	sample <= max_independent_value )
      break;
  }

  return sample;
}

// Return a random sample from the corresponding CDF and record the number of trials
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::sampleAndRecordTrials( unsigned& trials ) const
{
  return ThisType::sampleAndRecordTrials( trials,
					  d_mean,
					  d_standard_deviation,
					  d_min_independent_value,
					  d_max_independent_value );
}

// Return the upper bound of the distribution independent variable
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::getUpperBoundOfIndepVar() const
{
  return d_max_independent_value;
}

// Return the lower bound of the distribution independent variable
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::getLowerBoundOfIndepVar() const
{
  return d_min_independent_value;
}

// Return the distribution type
template<typename IndependentUnit, typename DependentUnit>
OneDDistributionType
UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::getDistributionType() const
{
  return ThisType::distribution_type;
}

// Test if the distribution is continuous
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::isContinuous() const
{
  return true;
}

// Method for placing the object in an output stream
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::toStream( std::ostream& os ) const
{
  os << "{" << getRawQuantity( d_mean )
     << "," << getRawQuantity( d_standard_deviation )
     << "," << getRawQuantity( d_min_independent_value )
     << "," << getRawQuantity( d_max_independent_value )
     << "," << getRawQuantity( d_constant_multiplier ) << "}";
}

// Method for initializing the object from an input stream
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::fromStream( std::istream& is )
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
			      "Error: the normal distribution cannot be "
			      "constructed because the representation is not "
			      "valid (see details below)!\n" );

  Teuchos::Array<std::string> distribution;
  try{
    distribution = Teuchos::fromStringToArray<std::string>( dist_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
			      InvalidDistributionStringRepresentation,
			      "Error: the normal distribution cannot be "
			      "constructed because the representation is not "
			      "valid (see details below)!\n" );

  TEST_FOR_EXCEPTION( distribution.size() < 2 || distribution.size() > 5,
		      InvalidDistributionStringRepresentation,
		      "Error: the normal distribution cannot be constructed "
		      "because the representation is not valid "
		      "(only 2, 3, 4 or 5 values may be specified)!" );

  // Set the mean
  TEST_FOR_EXCEPTION( distribution[0].find_first_not_of( " -0123456789.eE" ) <
		      distribution[0].size(),
		      InvalidDistributionStringRepresentation,
		      "Error: the normal distribution cannot be "
		      "constructed because of an invalid mean "
		      << distribution[0] );
  {
    std::istringstream iss( distribution[0] );

    double raw_mean;
    Teuchos::extractDataFromISS( iss, raw_mean );

    setQuantity( d_mean, raw_mean );
  }

  TEST_FOR_EXCEPTION( IQT::isnaninf( d_mean ),
		      InvalidDistributionStringRepresentation,
		      "Error: the normal distribution cannot be constructed "
		      "because of an invalid mean " << d_mean );

  // Set the standard deviation
  TEST_FOR_EXCEPTION( distribution[1].find_first_not_of( " 0123456789.eE" ) <
		      distribution[1].size(),
		      InvalidDistributionStringRepresentation,
		      "Error: the normal distribution cannot be "
		      "constructed because of an invalid standard deviation "
		      << distribution[1] );
  {
    std::istringstream iss( distribution[1] );

    double raw_standard_deviation;
    Teuchos::extractDataFromISS( iss, raw_standard_deviation );

    setQuantity( d_standard_deviation, raw_standard_deviation );
  }

  TEST_FOR_EXCEPTION( IQT::isnaninf( d_standard_deviation ),
		      InvalidDistributionStringRepresentation,
		      "Error: the normal distribution cannot be constructed "
		      "because of an invalid standard deviation "
		      << d_standard_deviation );

  TEST_FOR_EXCEPTION( d_standard_deviation < IQT::zero(),
		      InvalidDistributionStringRepresentation,
		      "Error: the normal distribution cannot be constructed "
		      "because of an invalid standard deviation "
		      << d_standard_deviation );

  TEST_FOR_EXCEPTION( d_constant_multiplier == DQT::zero(),
		      InvalidDistributionStringRepresentation,
		      "Error: the normal distribution cannot be constructed "
		      "because of an invalid multiplier "
		      << d_constant_multiplier );

  // Set the min independent value
  if( distribution.size() > 2 )
  {
    if( distribution[2].compare( "-inf" ) == 0 )
      d_min_independent_value = -IQT::inf();
    else
    {
      TEST_FOR_EXCEPTION( distribution[2].find_first_not_of( " -0123456789.e")<
			  distribution[2].size(),
			  InvalidDistributionStringRepresentation,
			  "Error: the normal distribution cannot be "
			  "constructed because of an invalid min independent "
			  "value " << distribution[2] );
      std::istringstream entry_iss( distribution[2] );

      double raw_min_independent_value;
      Teuchos::extractDataFromISS( entry_iss, raw_min_independent_value );

      setQuantity( d_min_independent_value, raw_min_independent_value );
    }
  }
  else
    d_min_independent_value = -IQT::inf();

  // Set the max independent value
  if( distribution.size() > 3 )
  {
    if( distribution[3].compare( "inf" ) == 0 )
      d_max_independent_value = IQT::inf();
    else
    {
      TEST_FOR_EXCEPTION( distribution[3].find_first_not_of( " -0123456789.e")<
			  distribution[3].size(),
			  InvalidDistributionStringRepresentation,
			  "Error: the normal distribution cannot be "
			  "constructed because of an invalid max independent "
			  " value " << distribution[3] );
      std::istringstream entry_iss( distribution[3] );

      double raw_max_independent_value;
      Teuchos::extractDataFromISS( entry_iss, raw_max_independent_value );

      setQuantity( d_max_independent_value, raw_max_independent_value );
    }
  }
  else
    d_max_independent_value = IQT::inf();

  TEST_FOR_EXCEPTION( d_max_independent_value <= d_min_independent_value,
		      InvalidDistributionStringRepresentation,
		      "Error: the normal distribution cannot be "
		      "constructed because the max independent value is not "
		      "greater than the min independent value!" );

  // Set the distribution multiplier
  if( distribution.size() > 4 )
  {
    TEST_FOR_EXCEPTION( distribution[4].find_first_not_of( " -0123456789.e") <
			distribution[4].size(),
			InvalidDistributionStringRepresentation,
			"Error: the normal distribution cannot be "
			"constructed because of an invalid multiplier "
			<< distribution[4] );
    std::istringstream entry_iss( distribution[4] );

    double raw_constant_multiplier;
    Teuchos::extractDataFromISS( entry_iss, raw_constant_multiplier );

    setQuantity( d_constant_multiplier, raw_constant_multiplier );
  }
  else
    d_constant_multiplier = DQT::one();
}

// Method for testing if two objects are equivalent
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::isEqual( const UnitAwareNormalDistribution<IndependentUnit,DependentUnit>& other ) const
{
  return
    d_constant_multiplier == other.d_constant_multiplier &&
    d_mean == other.d_mean &&
    d_standard_deviation == other.d_standard_deviation &&
    d_min_independent_value == other.d_min_independent_value &&
    d_max_independent_value == other.d_max_independent_value;
}

// Test if the dependent variable can be zero within the indep bounds
/*! \details If the absolute value of the lower or upper limit is Inf then it 
 * is possible for the distribution to return 0.0 from one of the evaluate 
 * methods. However, the 0.0 value will only occur if the distribution is 
 * evaluated at +/- Inf, which should never actually be done in practice, so we
 *  will return false from this method.
 */
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::canDepVarBeZeroInIndepBounds() const
{
  return false;
}

} // end Utility namespace

#endif // end UTILITY_NORMAL_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_NormalDistribution_def.hpp
//---------------------------------------------------------------------------//
