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
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_DesignByContract.hpp"

BOOST_SERIALIZATION_DISTRIBUTION2_EXPORT_IMPLEMENT( UnitAwareNormalDistribution );

namespace Utility{

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
  // Verify that the shape parameters are valid
  this->verifyValidShapeParameters( d_constant_multiplier,
                                    d_mean,
                                    d_standard_deviation,
                                    d_min_independent_value,
                                    d_max_independent_value );

  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
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
  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
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
  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
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
  DistributionTraits::Counter number_of_trials;

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
				    DistributionTraits::Counter& trials,
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
UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::sampleAndRecordTrials( DistributionTraits::Counter& trials ) const
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
UnivariateDistributionType
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
  this->toStreamWithLimitsDistImpl( os,
                                    std::make_pair( "mean", d_mean ),
                                    std::make_pair( "standard dev", d_standard_deviation ),
                                    std::make_pair( "multiplier", d_constant_multiplier ) );
}

// Save the distribution to an archive
template<typename IndependentUnit, typename DependentUnit>
template<typename Archive>
void UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::save( Archive& ar, const unsigned version ) const
{
  // Save the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Save the local member data
  ar & BOOST_SERIALIZATION_NVP( d_constant_multiplier );
  ar & BOOST_SERIALIZATION_NVP( d_mean );
  ar & BOOST_SERIALIZATION_NVP( d_standard_deviation );

  // We cannot safely serialize -inf to all archive types - create a flag that
  // records if the lower limit is -inf
  const bool __lower_limit_is_neg_inf__ =
    (d_min_independent_value == -IQT::inf());

  ar & BOOST_SERIALIZATION_NVP( __lower_limit_is_neg_inf__ );

  if( __lower_limit_is_neg_inf__ )
  {
    IndepQuantity tmp_lower_limit = IQT::lowest();

    ar & boost::serialization::make_nvp( "d_min_independent_value", tmp_lower_limit );
  }
  else
  {
    ar & BOOST_SERIALIZATION_NVP( d_min_independent_value );
  }
  
  // We cannot safely serialize inf to all archive types - create a flag that
  // records if the upper limit is inf
  const bool __upper_limit_is_inf__ = (d_max_independent_value == IQT::inf());

  ar & BOOST_SERIALIZATION_NVP( __upper_limit_is_inf__ );

  if( __upper_limit_is_inf__ )
  {
    IndepQuantity tmp_upper_limit = IQT::max();

    ar & boost::serialization::make_nvp( "d_max_independent_value", tmp_upper_limit );
  }
  else
  {
    ar & BOOST_SERIALIZATION_NVP( d_max_independent_value );
  }
}

// Load the distribution from an archive
template<typename IndependentUnit, typename DependentUnit>
template<typename Archive>
void UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::load( Archive& ar, const unsigned version )
{
  // Load the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Load the local member data
  ar & BOOST_SERIALIZATION_NVP( d_constant_multiplier );
  ar & BOOST_SERIALIZATION_NVP( d_mean );
  ar & BOOST_SERIALIZATION_NVP( d_standard_deviation );

  // Load the lower limit inf flag
  bool __lower_limit_is_neg_inf__;
  ar & BOOST_SERIALIZATION_NVP( __lower_limit_is_neg_inf__ );

  ar & BOOST_SERIALIZATION_NVP( d_min_independent_value );

  // Restore the neg inf value of the lower limit
  if( __lower_limit_is_neg_inf__ )
    d_min_independent_value = -IQT::inf();

  // Load the upper limit inf flag
  bool __upper_limit_is_inf__;
  ar & BOOST_SERIALIZATION_NVP( __upper_limit_is_inf__ );
  
  ar & BOOST_SERIALIZATION_NVP( d_max_independent_value );

  if( __upper_limit_is_inf__ )
    d_max_independent_value = IQT::inf();
}

// Method for testing if two objects are equivalent
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::operator==( const UnitAwareNormalDistribution& other ) const
{
  return d_constant_multiplier == other.d_constant_multiplier &&
    d_mean == other.d_mean &&
    d_standard_deviation == other.d_standard_deviation &&
    d_min_independent_value == other.d_min_independent_value &&
    d_max_independent_value == other.d_max_independent_value;
}

// Method for testing if two objects are different
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::operator!=( const UnitAwareNormalDistribution& other ) const
{
  return d_constant_multiplier != other.d_constant_multiplier ||
    d_mean != other.d_mean ||
    d_standard_deviation != other.d_standard_deviation ||
    d_min_independent_value != other.d_min_independent_value ||
    d_max_independent_value != other.d_max_independent_value;
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

// Verify that the shape parameters are valid
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareNormalDistribution<IndependentUnit,DependentUnit>::verifyValidShapeParameters(
                                   const DepQuantity& const_multiplier,
                                   const IndepQuantity& mean,
                                   const IndepQuantity& standard_deviation,
                                   const IndepQuantity& min_independent_value,
                                   const IndepQuantity& max_independent_value )
{
  TEST_FOR_EXCEPTION( DQT::isnaninf( const_multiplier ),
		      Utility::BadUnivariateDistributionParameter,
		      "The normal distribution cannot be constructed "
		      "because of the multiplier is invalid!" );
  
  TEST_FOR_EXCEPTION( const_multiplier == DQT::zero(),
		      Utility::BadUnivariateDistributionParameter,
		      "The normal distribution cannot be constructed "
		      "because of the multiplier is invalid!" );
  
  TEST_FOR_EXCEPTION( IQT::isnaninf( mean ),
		      Utility::BadUnivariateDistributionParameter,
		      "The normal distribution cannot be constructed "
		      "because the mean is invalid!" );

  TEST_FOR_EXCEPTION( IQT::isnaninf( standard_deviation ),
		      Utility::BadUnivariateDistributionParameter,
		      "The normal distribution cannot be constructed "
		      "because the standard deviation is invalid!" );

  TEST_FOR_EXCEPTION( standard_deviation <= IQT::zero(),
		      Utility::BadUnivariateDistributionParameter,
		      "The normal distribution cannot be constructed "
		      "because the standard deviation is invalid!" );

  TEST_FOR_EXCEPTION( max_independent_value <= min_independent_value,
		      Utility::BadUnivariateDistributionParameter,
		      "The normal distribution cannot be constructed because "
                      "the upper limit is invalid!" );
}

} // end Utility namespace

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareNormalDistribution<void,void> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Utility, UnitAwareNormalDistribution<void,void> );

#endif // end UTILITY_NORMAL_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_NormalDistribution_def.hpp
//---------------------------------------------------------------------------//
