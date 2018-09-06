//---------------------------------------------------------------------------//
//!
//! \file   Utility_MaxwellFissionDistribution_def.hpp
//! \author Aaron Tumulak
//! \brief  Maxwell Fission distribution class definition. Modified by Alex
//!         Robinson to accommodate units.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_MAXWELL_FISSION_DISTRIBUTION_DEF_HPP
#define UTILITY_MAXWELL_FISSION_DISTRIBUTION_DEF_HPP

// Boost Includes
#include <boost/units/cmath.hpp>

// FRENSIE Includes
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_DesignByContract.hpp"

BOOST_SERIALIZATION_DISTRIBUTION2_EXPORT_IMPLEMENT( UnitAwareMaxwellFissionDistribution );

namespace Utility{

// Constructor
/*! \details This constructor will explicitly cast the input quantities to
 * the distribution quantity (which includes any unit-conversion). The
 * dimension type must match and there must be a unit-conversion defined using
 * the boost methodology.
 */
template<typename IndependentUnit, typename DependentUnit>
template<typename InputIndepQuantityA,
	 typename InputIndepQuantityB,
	 typename InputIndepQuantityC>
UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::UnitAwareMaxwellFissionDistribution(
				const InputIndepQuantityA incident_energy,
				const InputIndepQuantityB nuclear_temperature,
				const InputIndepQuantityC restriction_energy,
				const double constant_multiplier )
  : d_incident_energy( incident_energy ),
    d_nuclear_temperature( nuclear_temperature ),
    d_restriction_energy( restriction_energy ),
    d_multiplier( DMQT::initializeQuantity( constant_multiplier ) ),
    d_norm_constant()
{
  // Verify that the shape parameters are valid
  this->verifyValidShapeParameters( d_incident_energy,
                                    d_nuclear_temperature,
                                    d_restriction_energy,
                                    d_multiplier );
  
  // Calculate the norm constant
  this->calculateNormalizationConstant();

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
UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::UnitAwareMaxwellFissionDistribution(
  const UnitAwareMaxwellFissionDistribution<InputIndepUnit,InputDepUnit>& dist_instance )
  : d_incident_energy( dist_instance.d_incident_energy ),
    d_nuclear_temperature( dist_instance.d_nuclear_temperature ),
    d_restriction_energy( dist_instance.d_restriction_energy ),
    d_multiplier(),
    d_norm_constant()
{
  // Calculate the scaled multiplier (for complex units, boost::units often has
  // problems doing the conversion so we will do it manually)
  d_multiplier = getRawQuantity( dist_instance.d_multiplier )*DepQuantity( QuantityTraits<typename UnitAwareMaxwellFissionDistribution<InputIndepUnit,InputDepUnit>::DepQuantity>::one() )/Utility::sqrt( IndepQuantity( QuantityTraits<typename UnitAwareMaxwellFissionDistribution<InputIndepUnit,InputDepUnit>::IndepQuantity>::one() ) );

  // Calculate the norm constant
  this->calculateNormalizationConstant();

  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Copy constructor
template<typename IndependentUnit, typename DependentUnit>
UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::UnitAwareMaxwellFissionDistribution( const UnitAwareMaxwellFissionDistribution<void,void>& unitless_dist_instance, int )
  : d_incident_energy( IQT::initializeQuantity( unitless_dist_instance.d_incident_energy ) ),
    d_nuclear_temperature( IQT::initializeQuantity( unitless_dist_instance.d_nuclear_temperature ) ),
    d_restriction_energy( IQT::initializeQuantity( unitless_dist_instance.d_restriction_energy ) ),
    d_multiplier( DMQT::initializeQuantity( unitless_dist_instance.d_multiplier ) ),
    d_norm_constant()
{
  // Calculate the norm constant
  this->calculateNormalizationConstant();

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
UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>
UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::fromUnitlessDistribution( const UnitAwareMaxwellFissionDistribution<void,void>& unitless_distribution )
{
  return ThisType( unitless_distribution, 0 );
}

// Assignment operator
template<typename IndependentUnit, typename DependentUnit>
UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>&
UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::operator=(
    const UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>& dist_instance )
{
  if( this != &dist_instance )
  {
    d_incident_energy = dist_instance.d_incident_energy;
    d_nuclear_temperature = dist_instance.d_nuclear_temperature;
    d_restriction_energy = dist_instance.d_restriction_energy;
    d_multiplier = dist_instance.d_multiplier;
    d_norm_constant = dist_instance.d_norm_constant;
  }

  return *this;
}

// Evaluate the distribution
/*! \details This is simply the unnormalized distribution. An implicit
 * conversion factor (1.0) is used to convert to the correct units.
 */
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::DepQuantity
UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::evaluate(
 const typename UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  if( indep_var_value < this->getLowerBoundOfIndepVar() )
    return DQT::zero();
  else if( indep_var_value > this->getUpperBoundOfIndepVar() )
    return DQT::zero();
  else
  {
    return d_multiplier*Utility::sqrt( indep_var_value )*
      exp( -indep_var_value / d_nuclear_temperature );
  }
}

// Evaluate the PDF
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity
UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::evaluatePDF(
const typename UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  return this->evaluate( indep_var_value )*d_norm_constant;
}

// Return a random sample from the distribution
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::sample() const
{
  return ThisType::sample( d_incident_energy,
			   d_nuclear_temperature,
			   d_restriction_energy );
}

// Return a random sample from the corresponding CDF and record the number of trials
template<typename IndependentUnit, typename DependentUnit>
inline typename UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::sample(
  const typename UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::IndepQuantity incident_energy,
  const typename UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::IndepQuantity nuclear_temperature,
  const typename UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::IndepQuantity restriction_energy )
{
  DistributionTraits::Counter trials = 0;

  return ThisType::sampleAndRecordTrials( incident_energy,
					  nuclear_temperature,
					  restriction_energy,
					  trials );
}

// Return a random sample and record the number of trials
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::sampleAndRecordTrials( DistributionTraits::Counter& trials ) const
{
  return ThisType::sampleAndRecordTrials( d_incident_energy,
					  d_nuclear_temperature,
					  d_restriction_energy,
					  trials );
}

// Return a random sample from the corresponding CDF and record the number of trials
template<typename IndependentUnit, typename DependentUnit>
inline typename UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::sampleAndRecordTrials(
  const typename UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::IndepQuantity incident_energy,
  const typename UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::IndepQuantity nuclear_temperature,
  const typename UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::IndepQuantity restriction_energy,
  DistributionTraits::Counter& trials )
{
  // Make sure values are valid
  testPrecondition( !IQT::isnaninf( incident_energy ) );
  testPrecondition( !IQT::isnaninf( nuclear_temperature ) );
  testPrecondition( !IQT::isnaninf( restriction_energy ) );

  // Make sure that incident energy and nuclear temperature is positive
  testPrecondition( incident_energy > IQT::zero() );
  testPrecondition( nuclear_temperature > IQT::zero() );

  double random_number_1, random_number_2, random_number_3;
  double term_1, term_2, arg;
  IndepQuantity sample;

  // Use the method outlined in OpenMC documentation under "5.7.2.4. ACE Law 7 - UnitAwareMaxwell Fission Spectrum"
  while( true )
  {
    // Increment the trial counter
    ++trials;

    random_number_1 = RandomNumberGenerator::getRandomNumber<double>();
    random_number_2 = RandomNumberGenerator::getRandomNumber<double>();
    random_number_3 = RandomNumberGenerator::getRandomNumber<double>();

    term_1 = log(random_number_1);

    arg = cos( PhysicalConstants::pi * random_number_3 * 0.5 );

    term_2 = log(random_number_2)*arg*arg;

    sample = -nuclear_temperature * ( term_1 + term_2 );

    if( sample <= (incident_energy - restriction_energy) )
      break;
  }

  return sample;
}

// Calculate the normalization constant of the distribution
/*
 * As given by ENDF Law 7
 * c^(-1) = T^(3/2)*[(sqrt(pi)/2)*erf(sqrt((E-U)/T)) - sqrt((E-U)/T)*exp(-(E-U)/T)]
 */
template<typename IndependentUnit, typename DependentUnit>
void
UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::calculateNormalizationConstant()
{
  double argument = (d_incident_energy - d_restriction_energy) / d_nuclear_temperature;

  d_norm_constant = rpow<3,-2>(d_nuclear_temperature)/
    (d_multiplier*(sqrt( PhysicalConstants::pi ) * 0.5 * erf( sqrt(argument) )-
		   sqrt(argument) * exp(-argument) ) );
}

// Return the upper bound of the distribution independent variable
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::getUpperBoundOfIndepVar() const
{
  return (d_incident_energy - d_restriction_energy);
}

// Return the lower bound of the distribution independent variable
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::getLowerBoundOfIndepVar() const
{
  return IQT::zero();
}

// Return the distribution type
template<typename IndependentUnit, typename DependentUnit>
UnivariateDistributionType UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::getDistributionType() const
{
  return ThisType::distribution_type;
}

// Test if the distribution is continuous
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::isContinuous() const
{
  return true;
}

// Method for placing the object in an output stream
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::toStream( std::ostream& os ) const
{
  this->toStreamDistImpl( os,
                          std::make_pair( "incident energy", d_incident_energy ),
                          std::make_pair( "nuclear temp", d_nuclear_temperature ),
                          std::make_pair( "restriction energy", d_restriction_energy ),
                          std::make_pair( "multiplier", Utility::getRawQuantity( d_multiplier ) ) );
}

// Save the distribution to an archive
template<typename IndependentUnit, typename DependentUnit>
template<typename Archive>
void UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::save( Archive& ar, const unsigned version ) const
{
  // Save the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Save the local member data
  ar & BOOST_SERIALIZATION_NVP( d_incident_energy );
  ar & BOOST_SERIALIZATION_NVP( d_nuclear_temperature );
  ar & BOOST_SERIALIZATION_NVP( d_restriction_energy );
  ar & BOOST_SERIALIZATION_NVP( d_multiplier );
  ar & BOOST_SERIALIZATION_NVP( d_norm_constant );
}

// Load the distribution from an archive
template<typename IndependentUnit, typename DependentUnit>
template<typename Archive>
void UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::load( Archive& ar, const unsigned version )
{
  // Load the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Load the local member data
  ar & BOOST_SERIALIZATION_NVP( d_incident_energy );
  ar & BOOST_SERIALIZATION_NVP( d_nuclear_temperature );
  ar & BOOST_SERIALIZATION_NVP( d_restriction_energy );
  ar & BOOST_SERIALIZATION_NVP( d_multiplier );
  ar & BOOST_SERIALIZATION_NVP( d_norm_constant );
}

// Method for testing if two objects are equivalent
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::operator==(
                       const UnitAwareMaxwellFissionDistribution& other ) const
{
  return d_incident_energy == other.d_incident_energy &&
    d_nuclear_temperature == other.d_nuclear_temperature &&
    d_restriction_energy == other.d_restriction_energy &&
    d_multiplier == other.d_multiplier;
}

// Method for testing if two objects are equivalent
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::operator!=(
                       const UnitAwareMaxwellFissionDistribution& other ) const
{
  return d_incident_energy != other.d_incident_energy ||
    d_nuclear_temperature != other.d_nuclear_temperature ||
    d_restriction_energy != other.d_restriction_energy ||
    d_multiplier != other.d_multiplier;
}

// Test if the dependent variable can be zero within the indep bounds
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::canDepVarBeZeroInIndepBounds() const
{
  return true;
}

// Verify that the shape parameters are valid
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::verifyValidShapeParameters(
                                           IndepQuantity& incident_energy,
                                           IndepQuantity& nuclear_temp,
                                           IndepQuantity& restriction_energy,
                                           DistMultiplierQuantity& multiplier )
{
  TEST_FOR_EXCEPTION( IQT::isnaninf( incident_energy ),
                      Utility::BadUnivariateDistributionParameter,
                      "The maxwell fission distribution cannot be constructed "
                      "because the incident energy is invalid!" );

  TEST_FOR_EXCEPTION( incident_energy <= IQT::zero(),
                      Utility::BadUnivariateDistributionParameter,
                      "The maxwell fission distribution cannot be constructed "
                      "because the incident energy is invalid!" );

  TEST_FOR_EXCEPTION( IQT::isnaninf( nuclear_temp ),
                      Utility::BadUnivariateDistributionParameter,
                      "The maxwell fission distribution cannot be constructed "
                      "because the nuclear temperature is invalid!" );

  TEST_FOR_EXCEPTION( nuclear_temp <= IQT::zero(),
		      Utility::BadUnivariateDistributionParameter,
                      "The maxwell fission distribution cannot be constructed "
                      "because the nuclear temperature is invalid!" );
  
  TEST_FOR_EXCEPTION( IQT::isnaninf( restriction_energy ),
                      Utility::BadUnivariateDistributionParameter,
                      "The maxwell fission distribution cannot be constructed "
                      "because the restriction energy is invalid!" );

  TEST_FOR_EXCEPTION( incident_energy <= restriction_energy,
                      Utility::BadUnivariateDistributionParameter,
                      "The maxwell fission distribution cannot be constructed "
                      "because the incident energy ("
                      << Utility::toString(incident_energy) << ")"
                      " is not greater than the restriction energy ("
                      << Utility::toString(restriction_energy) << ")!" );

  TEST_FOR_EXCEPTION( DMQT::isnaninf( multiplier ),
                      Utility::BadUnivariateDistributionParameter,
                      "The maxwell fission distribution cannot be constructed "
                      "because the multiplier is invalid!" );

  TEST_FOR_EXCEPTION( multiplier == DMQT::zero(),
                      Utility::BadUnivariateDistributionParameter,
                      "The maxwell fission distribution cannot be constructed "
                      "because the multiplier is invalid!" );  
}

} // end Utility namespace

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareMaxwellFissionDistribution<void,void> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Utility, UnitAwareMaxwellFissionDistribution<void,void> );

#endif // end UTILITY_MAXWELL_FISSION_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_MaxwellFissionDistribution_def.hpp
//---------------------------------------------------------------------------//
