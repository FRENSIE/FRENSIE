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
#include "Utility_ArrayString.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Default constructor
template<typename IndependentUnit, typename DependentUnit>
UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::UnitAwarePolynomialDistribution()
{ /* ... */ }

// Constructor
template<typename IndependentUnit, typename DependentUnit>
template<typename InputIndepQuantity>
UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::UnitAwarePolynomialDistribution(
			            const Teuchos::Array<double>& coefficients,
				    const InputIndepQuantity min_indep_limit,
				    const InputIndepQuantity max_indep_limit )
  : d_min_indep_limit( min_indep_limit ),
    d_max_indep_limit( max_indep_limit ),
    d_norm_constant(),
    d_terms()
{
  // Make sure the polynomial is valid
  testPrecondition( coefficients.size() > 0 );
  // Make sure the values are valid
  testPrecondition( !IQT::isnaninf( min_indep_limit ) );
  testPrecondition( !IQT::isnaninf( max_indep_limit ) );
  // Make sure the distribution is valid
  testPrecondition( this->isValidSamplingDistribution( coefficient,
						       min_indep_limit,
						       max_indep_limit ) );

  PolynomialConstructionHelper<IndependentUnit,DependentUnit>::createPolynomial( 
						             coefficients,
							     min_indep_limit,
							     max_indep_limit,
							     d_norm_constant,
						             d_terms );
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
  : d_min_indep_limit( dist_instance.d_min_indep_limit ),
    d_max_indep_limit( dist_instance.d_max_indep_limit ),
    d_norm_constant(),
    d_terms()
{
  // Make sure the polynomial is valid
  testPrecondition( dist_instance.d_terms.size() > 0 );
  // Make sure the values are valid
  remember( typedef QuantityTraits<typename UnitAwarePolynomialDistribution<InputIndepUnit,InputDepUnit>::IndepQuantity> InputIQT );
  testPrecondition( !InputIQT::isnaninf( dist_instance.d_min_indep_limit ) );
  testPrecondition( !InputIQT::isnaninf( dist_instance.d_max_indep_limit ) );

  PolynomialConstructionHelper<IndependentUnit,DependentUnit>::convertPolynomial( 
							 dist_instance.d_terms,
							 d_norm_constant,
							 d_terms );
}

// Copy constructor (copying from unitless distribution only)
template<typename IndependentUnit, typename DependentUnit>
UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::UnitAwarePolynomialDistribution( 
      const UnitAwarePolynomialDistribution<void,void>& unitless_dist_instance,
      int )
  : d_min_indep_limit( IQT::initializeQuantity( unitless_dist_instance.d_min_indep_limit ) ),
    d_max_indep_limit( IQT::initializeQuantity( unitless_dist_instance.d_max_indep_limit ) ),
    d_norm_constant(),
    d_terms()
{
  // Make sure the polynomial is valid
  testPrecondition( unitless_dist_instance.d_terms.size() > 0 );
  // Make sure the limits are valid
  testPrecondition( !QT::isnaninf( unitless_dist_instance.d_min_indep_limit ));
  testPrecondition( !QT::isnaninf( unitless_dist_instance.d_max_indep_limit ));

  PolynomialConstructionHelper<IndependentUnit,DependentUnit>::convertPolynomial(
						unitless_dist_instance.d_terms,
						d_norm_constant,
						d_terms );
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
UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::fromUnitlessDistribution( const UnitAwarePolynomialDistribution<void,void>& unitless_distribution )
{
  return ThisType( unitless_distribution, 0 );
}

// Assignment operator
template<typename IndependentUnit, typename DependentUnit>
UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>& 
UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::operator=( 
    const UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>& dist_instance )
{
  // Make sure the polynomial is valid
  testPrecondition( dist_instance.d_terms.size() > 0 );
  // Make sure the limits are valid
  testPrecondition( !IQT::isnaninf(unitless_dist_instance.d_min_indep_limit) );
  testPrecondition( !IQT::isnaninf(unitless_dist_instance.d_max_indep_limit) );
  
  if( this != &dist_instance )
  {
    d_min_indep_limit = dist_instance.d_min_indep_limit;
    d_max_indep_limit = dist_instance.d_max_indep_limit;

    PolynomialConstructionHelper<IndependentUnit,DependentUnit>::convertPolynomial(
						dist_instance.d_terms,
						d_norm_constant,
						d_terms );
  }

  return *this;
}

// Evaluate the distribution
template<typename IndependentUnit, typename DependentUnit>
UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::DepQuantity
UnitAwarePolynomialDistribution::evaluate( 
 const typename UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  if( indep_var_value < d_min_indep_limit )
    return 0.0;
  else if( indep_var_value > d_max_indep_limit )
    return 0.0;
  else
  {
    DepQuanity dep_quantity;

    setQuantity( quantity, 0.0 );
    
    for( unsigned i = 0u; i < d_terms.size(); ++i )
    {
      if( d_terms[i].second )
	dep_quantity += d_terms[i]->evaluate( indep_var_value );
    }
    
    return dep_value;
  }
}

// Evaluate the PDF
template<typename IndependentUnit, typename DependentUnit>
UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity
UnitAwarePolynomialDistribution::evaluatePDF( 
 const typename UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value) const
{
  DepQuantity pdf_value = DQT::zero();
  
  for( unsigned i = 0u; i < d_terms.size(); ++i )
  {
    if( d_terms[i].second )
    {
      pdf_value += d_terms[i].second->evaluatePDF( indep_var_value )/
	d_terms[i].second->getNormConstant();
    }
  }
  
  return pdf_value*d_norm_constant;
}

// Evaluate the CDF
template<typename IndependentUnit, typename DependentUnit>
double
UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::evaluateCDF( 
  const typename UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  DistNormQuantity cdf_value = DNQT::zero();

  for( unsigned i = 0; i < d_terms.size(); ++i )
  {
    if( d_terms[i].second )
    {
      cdf_value += d_terms[i].second->evaluateCDF( indep_var_value )/
	d_terms[i].second->getNormConstant();
    }
  }

  return cdf_value*d_norm_constant;
}

// Return a random sample from the distribution
/*! \details The probability mixing technique is used to sample from the
 * polynomial exactly.
 */
double UnitAwarePolynomialDistribution::sample() const
{
  double random_number_1 = RandomNumberGenerator::getRandomNumber<double>();

  unsigned sampled_term;
  
  // Sample which term of the series will be used to sample from
  for( unsigned i = 0; i < d_term_sampling_cdf.size(); ++i )
  {
    if( random_number_1 < d_term_sampling_cdf[i] )
    {
      sampled_term = i;

      break;
    }
  }

  double argument = RandomNumberGenerator::getRandomNumber<double>()*
    (d_indep_limits_to_series_powers_p1[sampled_term].second - 
     d_indep_limits_to_series_powers_p1[sampled_term].first) +
    d_indep_limits_to_series_powers_p1[sampled_term].first;

  if( sampled_term == 0u )
    return argument;
  else if( sampled_term == 1u )
    return sqrt( argument );
  else
    return pow( argument, 1.0/(sampled_term+1u) );
}

//! Return a random sample and record the number of trials
double UnitAwarePolynomialDistribution::sampleAndRecordTrials( unsigned& trials ) const
{
  ++trials;

  return this->sample();
}

// Return the upper bound of the distribution independent variable
double UnitAwarePolynomialDistribution::getUpperBoundOfIndepVar() const
{
  return d_indep_limits_to_series_powers_p1.front().second;
}

// Return the lower bound of the distribution independent variable
double UnitAwarePolynomialDistribution::getLowerBoundOfIndepVar() const
{
  return d_indep_limits_to_series_powers_p1.front().first;
}

// Return the distribution type
OneDDistributionType UnitAwarePolynomialDistribution::getDistributionType() const
{
  return UnitAwarePolynomialDistribution::distribution_type;
}

// Test if the distribution is continuous
bool UnitAwarePolynomialDistribution::isContinuous() const
{
  return true;
}

// Method for placing the object in an output stream
void UnitAwarePolynomialDistribution::toStream( std::ostream& os ) const
{
  os << "{" << d_coefficients
     << "," << d_indep_limits_to_series_powers_p1.front().first
     << "," << d_indep_limits_to_series_powers_p1.front().second
     << "}";
}

// Method for initializing the object from an input stream
void UnitAwarePolynomialDistribution::fromStream( std::istream& is )
{
  // Read the initial '{'
  std::string start_bracket;
  std::getline( is, start_bracket, '{' );
  start_bracket = Teuchos::Utils::trimWhiteSpace( start_bracket );

  TEST_FOR_EXCEPTION( start_bracket.size() != 0,
		      InvalidDistributionStringRepresentation,
		      "Error: the input stream is not a valid polynomial "
		      "distribution representation!" );
  
  std::string coeffs_rep;
  std::getline( is, coeffs_rep, '}' );
  coeffs_rep += '}';

  // Parse special characters
  try{
    ArrayString::locateAndReplacePi( coeffs_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
			      InvalidDistributionStringRepresentation,
			      "Error: the polynomial distribution cannot be "
			      "constructed because the representation is not "
			      "valid (see details below)!\n" );

  d_coefficients.clear();
  try{
    d_coefficients = Teuchos::fromStringToArray<double>( coeffs_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
			      InvalidDistributionStringRepresentation,
			      "Error: the polynomial distribution cannot be "
			      "constructed because the representation is not "
			      "valid (see details below)!\n" );
  
  // Read the ","
  std::string separator;
  std::getline( is, separator, ',' );
  
  // Read the rest of the values
  std::string limits_rep( "{" );
  std::string raw_limits_rep;
  std::getline( is, raw_limits_rep, '}' );
  raw_limits_rep += '}';
  
  limits_rep += raw_limits_rep;

  try{
    ArrayString::locateAndReplacePi( limits_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
			      InvalidDistributionStringRepresentation,
			      "Error: the polynomial distribution cannot be "
			      "constructed because the representation is not "
			      "valid (see details below)!\n" );

  Teuchos::Array<double> independent_limits;
  try{
    independent_limits = 
      Teuchos::fromStringToArray<double>( limits_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
			      InvalidDistributionStringRepresentation,
			      "Error: the polynomial distribution cannot be "
			      "constructed because the representation is not "
			      "valid (see details below)!\n" );
    
  TEST_FOR_EXCEPTION( independent_limits.size() != 2,
		      InvalidDistributionStringRepresentation,
		      "Error: the polynomial distribution cannot be "
		      "constructed because a lower and upper limit were not "
		      "given - "
		      << independent_limits.size() << " limits were given "
		      << independent_limits << "!" );
  
  TEST_FOR_EXCEPTION( independent_limits[0] >= independent_limits[1],
		      InvalidDistributionStringRepresentation,
		      "Error: the polynomial distribution cannot be "
		      "constructed because the lower limit is not less than "
		      " the upper limit (" << independent_limits[0] << ","
		      << independent_limits[1] << ")!" );

  initializeDistribution( independent_limits[0], independent_limits[1] );

  // Make sure the distribution is valid for sampling
  TEST_FOR_EXCEPTION( !isValidSamplingDistribution(),
		      InvalidDistributionStringRepresentation,
		      "Error: each term of the polynomial distribution is not "
		      "a positive functions and can therefor not be used for "
		      "sampling!" );
}

// Method for testing if two objects are equivalent
bool UnitAwarePolynomialDistribution::isEqual( const UnitAwarePolynomialDistribution& other ) const
{
  return d_coefficients == other.d_coefficients &&
    d_indep_limits_to_series_powers_p1.front().first ==
    other.d_indep_limits_to_series_powers_p1.front().first &&
    d_indep_limits_to_series_powers_p1.front().second ==
    other.d_indep_limits_to_series_powers_p1.front().second;
}

// Initialize the distribution
void UnitAwarePolynomialDistribution::initializeDistribution(		            
						 const double min_indep_limit,
						 const double max_indep_limit )
{
  d_indep_limits_to_series_powers_p1.resize( d_coefficients.size() );
  double min_indep_limit_to_term_power_p1 = min_indep_limit;
  double max_indep_limit_to_term_power_p2 = max_indep_limit;

  for( unsigned i = 0; i < d_coefficients.size(); ++i )
  {
    d_indep_limits_to_series_powers_p1[i].first = 
      min_indep_limit_to_term_power_p1;
    d_indep_limits_to_series_powers_p1[i].second = 
      max_indep_limit_to_term_power_p2;

    min_indep_limit_to_term_power_p1 *= max_indep_limit;
    max_indep_limit_to_term_power_p2 *= max_indep_limit;
  }

  // Calculate the term sampling cdf and the norm constant
  d_term_sampling_cdf.resize( d_coefficients.size() );

  d_norm_constant = 0.0;
  
  for( unsigned i = 0; i < d_coefficients.size(); ++i )
  {
    d_term_sampling_cdf[i] = d_coefficients[i]/(i+1u)*
      (d_indep_limits_to_series_powers_p1[i].second -
       d_indep_limits_to_series_powers_p1[i].first);
    
    if( i > 0 )
      d_term_sampling_cdf[i] += d_term_sampling_cdf[i-1];
  }

  d_norm_constant = 1.0/d_term_sampling_cdf.back();

  for( unsigned i = 0; i < d_coefficients.size(); ++i )
    d_term_sampling_cdf[i] /= d_norm_constant;
  
  // Make sure the term sampling cdf has been constructed correctly
  testPostcondition( d_term_sampling_cdf.back() == 1.0 );
}

// Test if the distribution can be used for sampling (each term must be a
// positive function
bool UnitAwarePolynomialDistribution::isValidSamplingDistribution(
				   const Teuchos::Array<double>& coefficients,
				   const double min_indep_limit,
				   const double max_indep_limit )
				   
{
  if( min_indep_limit < 0.0 && d_max_indep_limit > 0.0 )
    return false;
  else if( min_indep_limit < 0.0 && max_indep_limit <= 0.0 )
  {
    for( unsigned i = 0; i < coefficients.size(); ++i )
    {
      if( coefficients[i] > 0.0 )
	return false;
    }
    return true;
  }
  else if( min_indep_limit >= 0.0 && max_indep_limit > 0.0 )
  {
    for( unsigned i = 0; i < coefficients.size(); ++i )
    {
      if( coefficients[i] < 0.0 )
	return false;
    }
    return true;
  }
  else
    return false;
}

} // end Utility namespace

#endif // end UTILITY_POLYNOMIAL_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_PolynomialDistribution_def.hpp
//---------------------------------------------------------------------------//
