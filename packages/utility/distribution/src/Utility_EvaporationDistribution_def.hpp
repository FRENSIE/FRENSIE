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
#include "Utility_ArrayString.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Explicit instantiation (extern declaration)
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareEvaporationDistribution<void,void> );

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
  // Make sure values are valid
  testPrecondition( !QuantityTraits<InputIndepQuantityA>::isnaninf( incident_energy ) );
  testPrecondition( !QuantityTraits<InputIndepQuantityB>::isnaninf( nuclear_temperature ) );
  testPrecondition( !QuantityTraits<InputIndepQuantityC>::isnaninf( restriction_energy ) );
  testPrecondition( !QT::isnaninf( constant_multiplier ) );
  // Make sure that incident energy and nuclear temperature are positive
  testPrecondition( incident_energy >
		    QuantityTraits<InputIndepQuantityA>::zero() );
  testPrecondition( nuclear_temperature >
		    QuantityTraits<InputIndepQuantityB>::zero() );
  // Make sure that the constant multiplier is positive
  testPrecondition( constant_multiplier > 0.0 );

  // Calculate the normalization constant
  this->calculateNormalizationConstant();
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
  // Make sure the multipliers are valid
  remember( typedef QuantityTraits<typename UnitAwareEvaporationDistribution<InputIndepUnit,InputDepUnit>::IndepQuantity> InputIQT );
  testPrecondition( !InputIQT::isnaninf( dist_instance.d_incident_energy ) );
  testPrecondition( !InputIQT::isnaninf( dist_instance.d_nuclear_temperature));
  testPrecondition( !InputIQT::isnaninf( dist_instance.d_restriction_energy) );
  // Make sure that incident energy and nuclear temperature are positive
  testPrecondition( dist_instance.d_incident_energy > InputIQT::zero() );
  testPrecondition( dist_instance.d_nuclear_temperature > InputIQT::zero() );

  // Calculate the scaled multiplier (for complex units, boost::units often has
  // problems doing the conversion so we will do it manually)
  d_multiplier = getRawQuantity( dist_instance.d_multiplier )*DepQuantity( QuantityTraits<typename UnitAwareEvaporationDistribution<InputIndepUnit,InputDepUnit>::DepQuantity>::one() )/IndepQuantity( QuantityTraits<typename UnitAwareEvaporationDistribution<InputIndepUnit,InputDepUnit>::IndepQuantity>::one() );

  // Calculate the norm constant
  this->calculateNormalizationConstant();
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
  // Make sure the multipliers are valid
  testPrecondition( !QT::isnaninf( unitless_dist_instance.d_incident_energy ) );
  testPrecondition( !QT::isnaninf( unitless_dist_instance.d_nuclear_temperature) );
  testPrecondition( !QT::isnaninf( unitless_dist_instance.d_restriction_energy) );
  // Make sure that incident energy and nuclear temperature is positive
  testPrecondition( unitless_dist_instance.d_incident_energy > 0.0 );
  testPrecondition( unitless_dist_instance.d_nuclear_temperature > 0.0 );

  // Calculate the norm constant
  this->calculateNormalizationConstant();
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
  // Make sure the distribution is valid
  testPrecondition( !IQT::isnaninf( dist_instance.d_incident_energy ) );
  testPrecondition( !IQT::isnaninf( dist_instance.d_nuclear_temperature ) );
  testPrecondition( !IQT::isnaninf( dist_instance.d_restriction_energy ) );
  testPrecondition( !DMQT::isnaninf( dist_instance.d_multiplier ) );
  testPrecondition( dist_instance.d_incident_energy > IQT::zero() );
  testPrecondition( dist_instance.d_nuclear_temperature > IQT::zero() );

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
OneDDistributionType
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
  os << "{" << getRawQuantity( d_incident_energy )
     << "," << getRawQuantity( d_nuclear_temperature )
     << "," << getRawQuantity( d_restriction_energy );

  // Only print the multiplier when a scaling has been done
  if( d_multiplier != DMQT::one() )
    os << "," << getRawQuantity( d_multiplier ) << "}";
  else
    os << "}";
}

// Method for initializing the object from an input stream
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::fromStream( std::istream& is )
{
  // Read in the distribution representation
  std::string dist_rep;
  std::getline( is, dist_rep, '}' );
  dist_rep += '}';

  Teuchos::Array<std::string> distribution;
  try{
    distribution = Teuchos::fromStringToArray<std::string>( dist_rep );
  }
  catch( Teuchos::InvalidArrayStringRepresentation& error )
  {
    std::string message( "Error: the Evaporation distribution cannot be "
                        "constructed because the representation is not valid "
                        "(see details below)!\n" );
    message += error.what();

    throw InvalidDistributionStringRepresentation( message );
  }

  TEST_FOR_EXCEPTION( distribution.size() > 4,
                     InvalidDistributionStringRepresentation,
                     "Error: the Evaporation distribution cannot "
                     "be constructed because the representation is "
                     "not valid"
                     "(only 4 values or fewer  may be specified)!" );

  // Set the incient neutron energy
  if( distribution.size() > 0 )
  {
    TEST_FOR_EXCEPTION( distribution[0].find_first_not_of( " 0123456789.e" ) <
			distribution[0].size(),
			InvalidDistributionStringRepresentation,
			"Error: the Evaporation distribution cannot be "
			"constructed because of an invalid incident energy "
			<< distribution[0] );
    {
      double incident_energy;

      std::istringstream iss( distribution[0] );
      Teuchos::extractDataFromISS( iss, incident_energy );

      setQuantity( d_incident_energy, incident_energy );
    }

    TEST_FOR_EXCEPTION( IQT::isnaninf( d_incident_energy ),
			InvalidDistributionStringRepresentation,
			"Error: the Evaporation distribution cannot be "
			"constructed because of an invalid incident energy "
			<< d_incident_energy );

    TEST_FOR_EXCEPTION( d_incident_energy < IQT::zero(),
			InvalidDistributionStringRepresentation,
			"Error: the Evaporation distribution cannot be "
			"constructed because of an invalid incident energy "
			<< d_incident_energy );
  }

  // Set the nuclear temperature
  if( distribution.size() > 1 )
  {
    TEST_FOR_EXCEPTION( distribution[1].find_first_not_of( " 0123456789.e" ) <
			distribution[1].size(),
			InvalidDistributionStringRepresentation,
			"Error: the Evaporation distribution cannot be "
			"constructed because of an invalid nuclear temperature "
			<< distribution[1] );
    {
      double nuclear_temperature;

      std::istringstream iss( distribution[1] );
      Teuchos::extractDataFromISS( iss, nuclear_temperature );

      setQuantity( d_nuclear_temperature, nuclear_temperature );
    }

    TEST_FOR_EXCEPTION(IQT::isnaninf( d_nuclear_temperature ),
		       InvalidDistributionStringRepresentation,
		       "Error: the Evaporation distribution cannot be "
		       "constructed because of an invalid nuclear temperature "
		       << d_nuclear_temperature );

    TEST_FOR_EXCEPTION(d_nuclear_temperature <= IQT::zero(),
		       InvalidDistributionStringRepresentation,
		       "Error: the Evaporation distribution cannot be "
		       "constructed because of an invalid nuclear temperature "
		       << d_nuclear_temperature );

  }

  // Set the restriction energy
  if( distribution.size() > 2 )
  {
    TEST_FOR_EXCEPTION(distribution[2].find_first_not_of( " 0123456789.e" ) <
		       distribution[2].size(),
		       InvalidDistributionStringRepresentation,
		       "Error: the Evaporation distribution cannot be "
		       "constructed because of an invalid restriction energy "
		       << distribution[2] );
    {
      double restriction_energy;

      std::istringstream iss( distribution[2] );
      Teuchos::extractDataFromISS( iss, restriction_energy );

      setQuantity( d_restriction_energy, restriction_energy );
    }

    TEST_FOR_EXCEPTION( IQT::isnaninf( d_restriction_energy ),
			InvalidDistributionStringRepresentation,
			"Error: the Evaporation distribution cannot be "
			"constructed because of an invalid restriction energy "
			<< d_restriction_energy );
  }

  // Set the multiplier
  if( distribution.size() > 3 )
  {
    TEST_FOR_EXCEPTION( distribution[3].find_first_not_of( " 0123456789.e" ) <
			distribution[3].size(),
			InvalidDistributionStringRepresentation,
			"Error: the Evaporation distribution cannot be "
			"constructed because of an invalid multiplier "
			<< distribution[3] );
    {
      double multiplier;

      std::istringstream iss( distribution[3] );
      Teuchos::extractDataFromISS( iss, multiplier );

      setQuantity( d_multiplier, multiplier );
    }

    TEST_FOR_EXCEPTION( DMQT::isnaninf( d_multiplier ),
			InvalidDistributionStringRepresentation,
			"Error: the Evaporation distribution cannot be "
			"constructed because of an invalid multiplier "
			<< getRawQuantity( d_multiplier ) );
  }

  // Calculate the normalization constant
  this->calculateNormalizationConstant();
}

// Method for testing if two objects are equivalent
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::isEqual(
const UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>& other ) const
{
  return d_incident_energy == other.d_incident_energy &&
    d_nuclear_temperature == other.d_nuclear_temperature &&
    d_restriction_energy == other.d_restriction_energy &&
    d_multiplier == other.d_multiplier;
}

// Test if the dependent variable can be zero within the indep bounds
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::canDepVarBeZeroInIndepBounds() const
{
  return true;
}

} // end Utility namespace

#endif // end UTILITY_EVAPORATION_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_EvaporationDistribution_def.hpp
//---------------------------------------------------------------------------//
