//---------------------------------------------------------------------------//
//!
//! \file   Utility_EvaporationDistribution_def.hpp
//! \author Aaron Tumulak
//! \brief  Evaporation distribution class definition. Modified by Alex
//!         Robinson to accommodate units.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_EVAPORATION_DISTRIBUTION_DEF_HPP
#define UTILITY_EVAPORATION_DISTRIBUTION_DEF_HPP

// FRENSIE Includes
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_DesignByContract.hpp"

BOOST_SERIALIZATION_DISTRIBUTION2_EXPORT_IMPLEMENT( UnitAwareEvaporationDistribution );

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
UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::UnitAwareEvaporationDistribution(
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
  
  // Calculate the normalization constant
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
UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::UnitAwareEvaporationDistribution(
  const UnitAwareEvaporationDistribution<InputIndepUnit,InputDepUnit>& dist_instance )
  : d_incident_energy( dist_instance.d_incident_energy),
    d_nuclear_temperature( dist_instance.d_nuclear_temperature),
    d_restriction_energy( dist_instance.d_restriction_energy),
    d_multiplier(),
    d_norm_constant()
{
  // Calculate the scaled multiplier (for complex units, boost::units often has
  // problems doing the conversion so we will do it manually)
  d_multiplier = Utility::getRawQuantity( dist_instance.d_multiplier )*DepQuantity( QuantityTraits<typename UnitAwareEvaporationDistribution<InputIndepUnit,InputDepUnit>::DepQuantity>::one() )/IndepQuantity( QuantityTraits<typename UnitAwareEvaporationDistribution<InputIndepUnit,InputDepUnit>::IndepQuantity>::one() );

  // Calculate the norm constant
  this->calculateNormalizationConstant();

  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Copy constructor (copying from unitless distribution only)
template<typename IndependentUnit, typename DependentUnit>
UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::UnitAwareEvaporationDistribution( const UnitAwareEvaporationDistribution<void,void>& unitless_dist_instance, int )
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
UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>
UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::fromUnitlessDistribution( const UnitAwareEvaporationDistribution<void,void>& unitless_distribution )
{
  return ThisType( unitless_distribution, 0 );
}

// Assignment operator
template<typename IndependentUnit, typename DependentUnit>
UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>&
UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::operator=(
   const UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>& dist_instance )
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
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::DepQuantity
UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::evaluate(
  const typename UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  if( indep_var_value < this->getLowerBoundOfIndepVar() )
    return DQT::zero();
  else if( indep_var_value > this->getUpperBoundOfIndepVar() )
    return DQT::zero();
  else
  {
    return d_multiplier*indep_var_value*
      exp( -indep_var_value / d_nuclear_temperature );
  }
}

// Evaluate the PDF
/*! \details PDF(x) = c*x*exp(-x/T) if x >= 0, = 0 if x < 0
 */
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity
UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::evaluatePDF(
const typename UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  return this->evaluate( indep_var_value )*d_norm_constant;
}

// Return a random sample from the distribution
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::sample() const
{
  return ThisType::sample( d_incident_energy,
			   d_nuclear_temperature,
			   d_restriction_energy );
}

// Return a random sample from the distribution
template<typename IndependentUnit, typename DependentUnit>
inline typename UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::sample(
  const typename UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::IndepQuantity incident_energy,
  const typename UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::IndepQuantity nuclear_temperature,
  const typename UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::IndepQuantity restriction_energy )
{
  DistributionTraits::Counter trials = 0;

  return ThisType::sampleAndRecordTrials( incident_energy,
					  nuclear_temperature,
					  restriction_energy,
					  trials );
}

// Return a random sample and record the number of trials
template<typename IndependentUnit, typename DependentUnit>
inline typename UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::sampleAndRecordTrials( DistributionTraits::Counter& trials ) const
{
  return ThisType::sampleAndRecordTrials( d_incident_energy,
					  d_nuclear_temperature,
					  d_restriction_energy,
					  trials );
}

// Return a random sample from the corresponding CDF and record the number of trials
template<typename IndependentUnit, typename DependentUnit>
inline typename UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::sampleAndRecordTrials(
  const typename UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::IndepQuantity incident_energy,
  const typename UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::IndepQuantity nuclear_temperature,
  const typename UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::IndepQuantity restriction_energy,
  DistributionTraits::Counter& trials )
{
  // Make sure values are valid
  testPrecondition( !IQT::isnaninf( incident_energy ) );
  testPrecondition( !IQT::isnaninf( nuclear_temperature ) );
  testPrecondition( !IQT::isnaninf( restriction_energy ) );
  // Make sure that incident energy and nuclear temperature are positive
  testPrecondition( incident_energy > IQT::zero() );
  testPrecondition( nuclear_temperature > IQT::zero() );

  double random_number_1, random_number_2;
  IndepQuantity sample;

  double argument = 1.0 - exp( -(incident_energy - restriction_energy)
    / nuclear_temperature );

  // Use the method outlined in LA-UR-14-27694
  while( true )
  {
    // Increment the trials counter
    ++trials;

    random_number_1 = RandomNumberGenerator::getRandomNumber<double>();
    random_number_2 = RandomNumberGenerator::getRandomNumber<double>();

    sample = - nuclear_temperature
      * log( (1.0 - argument * random_number_1) * (1.0 - argument * random_number_2) );

    if( sample <= (incident_energy - restriction_energy) )
      break;
  }

  return sample;
}

// Calculate the normalization constant of the distribution
/*
 * \details As given in LA-UR-14-27694
 * c = T^(-2)*[1-exp(-(E-U)/T)*(1+(E-U)/T)]^-1
 */
template<typename IndependentUnit, typename DependentUnit>
void
UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::calculateNormalizationConstant()
{
  double argument = (d_incident_energy - d_restriction_energy) / d_nuclear_temperature;

  d_norm_constant = 1.0/( d_multiplier*d_nuclear_temperature*d_nuclear_temperature*
			  (1.0 - exp(-argument)*(1.0 + argument)) );
}

// Return the upper bound of the distribution independent variable
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::getUpperBoundOfIndepVar() const
{
  return (d_incident_energy - d_restriction_energy);
}

// Return the lower bound of the distribution independent variable
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::getLowerBoundOfIndepVar() const
{
  return IQT::zero();
}

// Return the distribution type
template<typename IndependentUnit, typename DependentUnit>
UnivariateDistributionType
UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::getDistributionType() const
{
  return ThisType::distribution_type;
}

// Test if the distribution is continuous
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::isContinuous() const
{
  return true;
}

// Method for placing the object in an output stream
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::toStream( std::ostream& os ) const
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
void UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::save( Archive& ar, const unsigned version ) const
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
void UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::load( Archive& ar, const unsigned version )
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
bool UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::operator==(
                          const UnitAwareEvaporationDistribution& other ) const
{
  return d_incident_energy == other.d_incident_energy &&
    d_nuclear_temperature == other.d_nuclear_temperature &&
    d_restriction_energy == other.d_restriction_energy &&
    d_multiplier == other.d_multiplier;
}

// Method for testing if two objects are equivalent
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::operator!=(
                          const UnitAwareEvaporationDistribution& other ) const
{
  return d_incident_energy != other.d_incident_energy ||
    d_nuclear_temperature != other.d_nuclear_temperature ||
    d_restriction_energy != other.d_restriction_energy ||
    d_multiplier != other.d_multiplier;
}

// Test if the dependent variable can be zero within the indep bounds
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::canDepVarBeZeroInIndepBounds() const
{
  return true;
}

// Verify that the shape parameters are valid
template<typename IndependentUnit, typename DependentUnit>
template<typename InputIndepQuantity, typename InputDistMultQuantity>
void UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::verifyValidShapeParameters(
                                        InputIndepQuantity& incident_energy,
                                        InputIndepQuantity& nuclear_temp,
                                        InputIndepQuantity& restriction_energy,
                                        InputDistMultQuantity& multiplier )
{
  typedef Utility::QuantityTraits<InputIndepQuantity> IIQT;
  
  TEST_FOR_EXCEPTION( IIQT::isnaninf( incident_energy ),
                      Utility::BadUnivariateDistributionParameter,
                      "The evaporation distribution cannot be constructed "
                      "because the incident energy is invalid!" );

  TEST_FOR_EXCEPTION( incident_energy <= IIQT::zero(),
                      Utility::BadUnivariateDistributionParameter,
                      "The evaporation distribution cannot be constructed "
                      "because the incident energy is invalid!" );

  TEST_FOR_EXCEPTION( IIQT::isnaninf( nuclear_temp ),
                      Utility::BadUnivariateDistributionParameter,
                      "The evaporation distribution cannot be constructed "
                      "because the nuclear temperature is invalid!" );

  TEST_FOR_EXCEPTION( nuclear_temp <= IIQT::zero(),
		      Utility::BadUnivariateDistributionParameter,
                      "The evaporation distribution cannot be constructed "
                      "because the nuclear temperature is invalid!" );
  
  TEST_FOR_EXCEPTION( IIQT::isnaninf( restriction_energy ),
                      Utility::BadUnivariateDistributionParameter,
                      "The evaporation distribution cannot be constructed "
                      "because the restriction energy is invalid!" );

  TEST_FOR_EXCEPTION( incident_energy <= restriction_energy,
                      Utility::BadUnivariateDistributionParameter,
                      "The evaporation distribution cannot be constructed "
                      "because the incident energy ("
                      << Utility::toString(incident_energy) << ")"
                      " is not greater than the restriction energy ("
                      << Utility::toString(restriction_energy) << ")!" );

  typedef Utility::QuantityTraits<InputDistMultQuantity> IDMQT;

  TEST_FOR_EXCEPTION( IDMQT::isnaninf( multiplier ),
                      Utility::BadUnivariateDistributionParameter,
                      "The evaporation distribution cannot be constructed "
                      "because the multiplier is invalid!" );

  TEST_FOR_EXCEPTION( multiplier == IDMQT::zero(),
                      Utility::BadUnivariateDistributionParameter,
                      "The evaporation distribution cannot be constructed "
                      "because the multiplier is invalid!" );
}

} // end Utility namespace

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareEvaporationDistribution<void,void> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Utility, UnitAwareEvaporationDistribution<void,void> );

#endif // end UTILITY_EVAPORATION_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_EvaporationDistribution_def.hpp
//---------------------------------------------------------------------------//
