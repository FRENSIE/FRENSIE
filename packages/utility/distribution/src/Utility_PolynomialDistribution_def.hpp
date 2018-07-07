//---------------------------------------------------------------------------//
//!
//! \file   Utility_PolynomialDistribution_def.hpp
//! \author Alex Robinson
//! \brief  Polynomial distribution class definition
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_POLYNOMIAL_DISTRIBUTION_DEF_HPP
#define UTILITY_POLYNOMIAL_DISTRIBUTION_DEF_HPP

// FRENSIE Includes
#include "Utility_ExponentiationAlgorithms.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_DesignByContract.hpp"

BOOST_SERIALIZATION_DISTRIBUTION2_EXPORT_IMPLEMENT( UnitAwarePolynomialDistribution );

namespace Utility{

// Constructor
/*! \details This constructor will explicitly cast the input quantities to
 * the distribution quantity (which includes any unit-conversion). The
 * dimension type must match and there must be a unit-conversion defined using
 * the boost methodology.
 */
template<typename IndependentUnit, typename DependentUnit>
template<typename InputIndepQuantity>
UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::UnitAwarePolynomialDistribution(
			            const std::vector<double>& coefficients,
				    const InputIndepQuantity min_indep_limit,
				    const InputIndepQuantity max_indep_limit )
  : d_coefficients( coefficients ),
    d_term_sampling_cdf( coefficients.size() ),
    d_indep_limits_to_series_powers_p1( coefficients.size() ),
    d_norm_constant( DNQT::one() )
{
  // Verify that the values are valid
  this->verifyValidDistributionData( d_coefficients,
                                     min_indep_limit,
                                     max_indep_limit );

  this->initializeDistribution( IndepQuantity( min_indep_limit ),
				IndepQuantity( max_indep_limit ) );

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
UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::UnitAwarePolynomialDistribution(
 const UnitAwarePolynomialDistribution<InputIndepUnit,InputDepUnit>& dist_instance )
  : d_coefficients( dist_instance.d_coefficients.size() ),
    d_term_sampling_cdf( dist_instance.d_term_sampling_cdf.size() ),
    d_indep_limits_to_series_powers_p1(
		     dist_instance.d_indep_limits_to_series_powers_p1.size() ),
    d_norm_constant()
{
  typedef typename UnitAwarePolynomialDistribution<InputIndepUnit,InputDepUnit>::DepQuantity InputDepQuantity;

  typedef typename UnitAwarePolynomialDistribution<InputIndepUnit,InputDepUnit>::IndepQuantity InputIndepQuantity;

  double coeff_scale_factor =
    Utility::getRawQuantity( DepQuantity( QuantityTraits<InputDepQuantity>::one() ) );

  // Scale the coefficients
  for( size_t i = 0; i < d_coefficients.size(); ++i )
  {
    d_coefficients[i] = dist_instance.d_coefficients[i]*coeff_scale_factor;

    coeff_scale_factor /=
      Utility::getRawQuantity(IndepQuantity(QuantityTraits<InputIndepQuantity>::one()));
  }

  IndepQuantity min_indep_limit(
    QuantityTraits<InputIndepQuantity>::initializeQuantity(
          Utility::get<0>(dist_instance.d_indep_limits_to_series_powers_p1.front()) ) );

  IndepQuantity max_indep_limit(
    QuantityTraits<InputIndepQuantity>::initializeQuantity(
          Utility::get<1>(dist_instance.d_indep_limits_to_series_powers_p1.front()) ) );

  this->initializeDistribution( min_indep_limit, max_indep_limit );

  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Copy constructor (copying from unitless distribution only)
template<typename IndependentUnit, typename DependentUnit>
UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::UnitAwarePolynomialDistribution(
	       const UnitAwarePolynomialDistribution<void,void>& dist_instance,
	       int )
  : d_coefficients( dist_instance.d_coefficients ),
    d_term_sampling_cdf( dist_instance.d_term_sampling_cdf ),
    d_indep_limits_to_series_powers_p1(
		            dist_instance.d_indep_limits_to_series_powers_p1 ),
    d_norm_constant( DNQT::initializeQuantity(dist_instance.d_norm_constant) )
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
UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>
UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::fromUnitlessDistribution(
      const UnitAwarePolynomialDistribution<void,void>& unitless_distribution )
{
  return ThisType( unitless_distribution, 0 );
}

// Assignment operator
template<typename IndependentUnit, typename DependentUnit>
UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>&
UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::operator=(
  const UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>& dist_instance )
{
  if( this != &dist_instance )
  {
    d_coefficients = dist_instance.d_coefficients;
    d_term_sampling_cdf = dist_instance.d_term_sampling_cdf;
    d_indep_limits_to_series_powers_p1 =
			      dist_instance.d_indep_limits_to_series_powers_p1;
    d_norm_constant = dist_instance.d_norm_constant;
  }

  return *this;
}

// Evaluate the distribution
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::DepQuantity
UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::evaluate(
const typename UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  double raw_indep_var_value = Utility::getRawQuantity( indep_var_value );

  if( raw_indep_var_value <
      Utility::get<0>( d_indep_limits_to_series_powers_p1.front() ) )
    return DQT::zero();
  else if( raw_indep_var_value >
	   Utility::get<1>( d_indep_limits_to_series_powers_p1.front() ) )
    return DQT::zero();
  else
  {
    double dep_value = 0.0;
    double indep_var_to_series_power = 1.0;

    for( unsigned i = 0; i < d_coefficients.size(); ++i )
    {
      dep_value += d_coefficients[i]*indep_var_to_series_power;

      indep_var_to_series_power *= raw_indep_var_value;
    }

    return DQT::initializeQuantity( dep_value );
  }
}

// Evaluate the PDF
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity
UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::evaluatePDF(
 const typename UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value) const
{
  return this->evaluate( indep_var_value )*d_norm_constant;
}

// Return a random sample from the distribution
/*! \details The probability mixing technique is used to sample from the
 * polynomial exactly (as long as all coefficients have the same sign).
 */
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::sample() const
{
  double random_number_1 = RandomNumberGenerator::getRandomNumber<double>();

  unsigned sampled_term =
    Search::binaryUpperBoundIndex( d_term_sampling_cdf.begin(),
				   d_term_sampling_cdf.end(),
				   random_number_1 );

  double argument = RandomNumberGenerator::getRandomNumber<double>()*
    (Utility::get<1>(d_indep_limits_to_series_powers_p1[sampled_term]) -
     Utility::get<0>(d_indep_limits_to_series_powers_p1[sampled_term]) ) +
    Utility::get<0>(d_indep_limits_to_series_powers_p1[sampled_term]);

  double sample;

  if( sampled_term == 0u )
    sample = argument;
  else if( sampled_term == 1u )
    sample = sqrt( argument );
  else
    sample = pow( argument, 1.0/(sampled_term+1u) );

  return IQT::initializeQuantity( sample );
}

//! Return a random sample and record the number of trials
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::sampleAndRecordTrials( DistributionTraits::Counter& trials ) const
{
  ++trials;

  return this->sample();
}

// Return the upper bound of the distribution independent variable
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::getUpperBoundOfIndepVar() const
{
  return IQT::initializeQuantity( Utility::get<1>(d_indep_limits_to_series_powers_p1.front()) );
}

// Return the lower bound of the distribution independent variable
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::getLowerBoundOfIndepVar() const
{
  return IQT::initializeQuantity( Utility::get<0>(d_indep_limits_to_series_powers_p1.front()) );
}

// Return the distribution type
template<typename IndependentUnit, typename DependentUnit>
UnivariateDistributionType
UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::getDistributionType() const
{
  return UnitAwarePolynomialDistribution::distribution_type;
}

// Test if the distribution is continuous
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::isContinuous() const
{
  return true;
}

// Method for placing the object in an output stream
template<typename IndependentUnit, typename DependentUnit>
void UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::toStream( std::ostream& os ) const
{
  this->toStreamWithLimitsDistImpl( os,
                                    std::make_pair( "coefficients", d_coefficients ) );
}

// Save the distribution to an archive
template<typename IndependentUnit, typename DependentUnit>
template<typename Archive>
void UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::save( Archive& ar, const unsigned version ) const
{
  // Save the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Save the local member data
  ar & BOOST_SERIALIZATION_NVP( d_coefficients );
  ar & BOOST_SERIALIZATION_NVP( d_term_sampling_cdf );
  ar & BOOST_SERIALIZATION_NVP( d_indep_limits_to_series_powers_p1 );
  ar & BOOST_SERIALIZATION_NVP( d_norm_constant );
}

// Load the distribution from an archive
template<typename IndependentUnit, typename DependentUnit>
template<typename Archive>
void UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::load( Archive& ar, const unsigned version )
{
  // Load the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Load the local member data
  ar & BOOST_SERIALIZATION_NVP( d_coefficients );
  ar & BOOST_SERIALIZATION_NVP( d_term_sampling_cdf );
  ar & BOOST_SERIALIZATION_NVP( d_indep_limits_to_series_powers_p1 );
  ar & BOOST_SERIALIZATION_NVP( d_norm_constant );
}

// Method for testing if two objects are equivalent
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::operator==(
                           const UnitAwarePolynomialDistribution& other ) const
{
  return d_coefficients == other.d_coefficients &&
    Utility::get<0>(d_indep_limits_to_series_powers_p1.front()) ==
    Utility::get<0>(other.d_indep_limits_to_series_powers_p1.front()) &&
    Utility::get<1>(d_indep_limits_to_series_powers_p1.front()) ==
    Utility::get<1>(other.d_indep_limits_to_series_powers_p1.front());
}

// Method for testing if two objects are equivalent
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::operator!=(
                           const UnitAwarePolynomialDistribution& other ) const
{
  return d_coefficients != other.d_coefficients ||
    Utility::get<0>(d_indep_limits_to_series_powers_p1.front()) !=
    Utility::get<0>(other.d_indep_limits_to_series_powers_p1.front()) ||
    Utility::get<1>(d_indep_limits_to_series_powers_p1.front()) !=
    Utility::get<1>(other.d_indep_limits_to_series_powers_p1.front());
}

// Initialize the distribution
template<typename IndependentUnit, typename DependentUnit>
void UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::initializeDistribution(
 const typename UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::IndepQuantity min_indep_limit,
 const typename UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::IndepQuantity max_indep_limit )
{
  d_indep_limits_to_series_powers_p1.resize( d_coefficients.size() );
  double min_indep_limit_to_term_power_p1 = Utility::getRawQuantity( min_indep_limit );
  double max_indep_limit_to_term_power_p2 = Utility::getRawQuantity( max_indep_limit );

  for( unsigned i = 0; i < d_coefficients.size(); ++i )
  {
    Utility::get<0>(d_indep_limits_to_series_powers_p1[i]) =
      min_indep_limit_to_term_power_p1;
    Utility::get<1>(d_indep_limits_to_series_powers_p1[i]) =
      max_indep_limit_to_term_power_p2;

    min_indep_limit_to_term_power_p1 *= Utility::getRawQuantity( max_indep_limit );
    max_indep_limit_to_term_power_p2 *= Utility::getRawQuantity( max_indep_limit );
  }

  // Calculate the norm constant and the term sampling cdf
  d_term_sampling_cdf.resize( d_coefficients.size() );

  for( unsigned i = 0; i < d_coefficients.size(); ++i )
  {
    d_term_sampling_cdf[i] = d_coefficients[i]/(i+1u)*
      (Utility::get<1>(d_indep_limits_to_series_powers_p1[i]) -
       Utility::get<0>(d_indep_limits_to_series_powers_p1[i]));

    if( i > 0 )
      d_term_sampling_cdf[i] += d_term_sampling_cdf[i-1];
  }

  double raw_norm_constant = 1.0/d_term_sampling_cdf.back();

  d_norm_constant = DNQT::initializeQuantity( raw_norm_constant );

  // Normalize the term sampling cdf
  for( unsigned i = 0; i < d_term_sampling_cdf.size(); ++i )
    d_term_sampling_cdf[i] *= raw_norm_constant;

  // Check for round-off error
  if( fabs( d_term_sampling_cdf.back() - 1.0 ) < 1e-9 )
    d_term_sampling_cdf.back() = 1.0;

  // Make sure the term sampling cdf has been constructed correctly
  testPostcondition( d_term_sampling_cdf.back() == 1.0 );
}

// Test if the dependent variable can be zero within the indep bounds
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::canDepVarBeZeroInIndepBounds() const
{
  if( d_coefficients[0] == 0 )
  {
    if( Utility::get<0>(d_indep_limits_to_series_powers_p1.front()) == 0.0 )
      return true;
    else if( Utility::get<1>(d_indep_limits_to_series_powers_p1.front()) == 0.0 )
      return true;
    else
      return false;
  }
  else
    return false;
}

// Verify that the distribution data is valid
template<typename IndependentUnit, typename DependentUnit>
template<typename InputIndepQuantity>
void UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::verifyValidDistributionData(
                                     const std::vector<double>& coefficients,
                                     const InputIndepQuantity min_indep_limit,
                                     const InputIndepQuantity max_indep_limit )
{
  TEST_FOR_EXCEPTION( coefficients.size() == 0,
                      Utility::BadUnivariateDistributionParameter,
                      "The polynomial distribution cannot be constructed "
                      "because there are no coefficients specified!" );

  std::vector<double>::const_iterator non_zero_coefficient =
    std::find_if( coefficients.begin(),
                  coefficients.end(),
                  []( double coeff ){ return coeff != 0.0; } );

  TEST_FOR_EXCEPTION( non_zero_coefficient == coefficients.end(),
                      Utility::BadUnivariateDistributionParameter,
                      "The polynomial distribution cannot be constructed "
                      "because all coefficients are zero!" );

  std::vector<double>::const_iterator bad_coefficient =
    std::find_if( coefficients.begin(),
                  coefficients.end(),
                  []( double coeff ){ return coeff < 0.0 || Utility::isnaninf( coeff ); } );

  TEST_FOR_EXCEPTION( bad_coefficient != coefficients.end(),
                      Utility::BadUnivariateDistributionParameter,
                      "The polynomial distribution cannot be constructed "
                      "because an invalid (negative or inf) coefficient ("
                      << *bad_coefficient << ") "
                      "was encountered at index "
                      << std::distance(coefficients.begin(), bad_coefficient)<<
                      "!" );

  typedef Utility::QuantityTraits<InputIndepQuantity> InputIQT;

  TEST_FOR_EXCEPTION( min_indep_limit < InputIQT::zero(),
                      Utility::BadUnivariateDistributionParameter,
                      "The polynomial distribution cannot be constructed "
                      "because the lower limits is negative!" );

  TEST_FOR_EXCEPTION( max_indep_limit <= min_indep_limit,
                      Utility::BadUnivariateDistributionParameter,
                      "The polynomial distribution cannot be constructed "
                      "because the limits are invalid!" );
}

} // end Utility namespace

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwarePolynomialDistribution<void,void> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Utility, UnitAwarePolynomialDistribution<void,void> );

#endif // end UTILITY_POLYNOMIAL_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_UnitAwarePolynomialDistribution_def.hpp
//---------------------------------------------------------------------------//
