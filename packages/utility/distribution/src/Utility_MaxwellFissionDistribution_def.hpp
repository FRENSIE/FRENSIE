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
#include "Utility_ArrayString.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

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
  // Make sure values are valid
  testPrecondition( !QuantityTraits<InputIndepQuantityA>::isnaninf( incident_energy ) );
  testPrecondition( !QuantityTraits<InputIndepQuantityB>::isnaninf( nuclear_temperature ) );
  testPrecondition( !QuantityTraits<InputIndepQuantityC>::isnaninf( restriction_energy ) );
  testPrecondition( !QT::isnaninf( constant_multiplier ) );
  // Make sure that incident energy and nuclear temperature is positive
  testPrecondition( incident_energy > 
		    QuantityTraits<InputIndepQuantityA>::zero() );
  testPrecondition( nuclear_temperature > 
		    QuantityTraits<InputIndepQuantityB>::zero() );
  // Make sure that the constant multiplier is positive
  testPrecondition( constant_multiplier > 0.0 );

  // Calculate the norm constant 
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
UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::UnitAwareMaxwellFissionDistribution(
  const UnitAwareMaxwellFissionDistribution<InputIndepUnit,InputDepUnit>& dist_instance )
  : d_incident_energy( dist_instance.d_incident_energy ),
    d_nuclear_temperature( dist_instance.d_nuclear_temperature ),
    d_restriction_energy( dist_instance.d_restriction_energy ),
    d_multiplier(),
    d_norm_constant()
{
  // Make sure the multipliers are valid
  remember( typedef QuantityTraits<typename UnitAwareMaxwellFissionDistribution<InputIndepUnit,InputDepUnit>::IndepQuantity> InputIQT );
  testPrecondition( !InputIQT::isnaninf( dist_instance.d_incident_energy ) );
  testPrecondition( !InputIQT::isnaninf( dist_instance.d_nuclear_temperature));
  testPrecondition( !InputIQT::isnaninf( dist_instance.d_restriction_energy) );
  // Make sure that incident energy and nuclear temperature is positive
  testPrecondition( dist_instance.d_incident_energy > InputIQT::zero() );
  testPrecondition( dist_instance.d_nuclear_temperature > InputIQT::zero() );

  // Calculate the scaled multiplier (for complex units, boost::units often has
  // problems doing the conversion so we will do it manually)
  d_multiplier = getRawQuantity( dist_instance.d_multiplier )*DepQuantity( QuantityTraits<typename UnitAwareMaxwellFissionDistribution<InputIndepUnit,InputDepUnit>::DepQuantity>::one() )/Utility::sqrt( IndepQuantity( QuantityTraits<typename UnitAwareMaxwellFissionDistribution<InputIndepUnit,InputDepUnit>::IndepQuantity>::one() ) );

  // Calculate the norm constant
  this->calculateNormalizationConstant();
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
/*! \details This is simply the unnormalized distribution. An implicit 
 * conversion factor (1.0) is used to convert to the correct units.
 */
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::DepQuantity
UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::evaluate( 
 const typename UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  if( indep_var_value < IQT::zero() )
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
  unsigned trials = 0;

  return ThisType::sampleAndRecordTrials( incident_energy,
					  nuclear_temperature,
					  restriction_energy,
					  trials );
}

// Return a random sample and record the number of trials
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::sampleAndRecordTrials( unsigned& trials ) const
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
  unsigned& trials )
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

  d_norm_constant =  rpow<3,-2>(d_nuclear_temperature)/
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
OneDDistributionType UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::getDistributionType() const
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
void UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::fromStream( std::istream& is )
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
    std::string message( "Error: the Maxwell Fission distribution cannot be "
                        "constructed because the representation is not valid "
                        "(see details below)!\n" );
    message += error.what();
    
    throw InvalidDistributionStringRepresentation( message );
  }
  
  TEST_FOR_EXCEPTION( distribution.size() > 4,
                     InvalidDistributionStringRepresentation,
                     "Error: the Maxwell Fission distribution cannot "
                     "be constructed because the representation is "
                     "not valid"
                     "(only 4 values or fewer  may be specified)!" );
  
  // Set the incient neutron energy
  if( distribution.size() > 0 )
  {
    TEST_FOR_EXCEPTION( distribution[0].find_first_not_of( " 0123456789.e" ) <
			distribution[0].size(),
			InvalidDistributionStringRepresentation,
			"Error: the Maxwell Fission distribution cannot be "
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
			"Error: the Maxwell Fission distribution cannot be "
			"constructed because of an invalid incident energy "
			<< d_incident_energy );
  
    TEST_FOR_EXCEPTION( d_incident_energy < IQT::zero(),
			InvalidDistributionStringRepresentation,
			"Error: the Maxwell Fission distribution cannot be "
			"constructed because of an invalid incident energy "
			<< d_incident_energy );
  }
  
  // Set the nuclear temperature
  if( distribution.size() > 1 )
  {
    TEST_FOR_EXCEPTION( distribution[1].find_first_not_of( " 0123456789.e" ) <
			distribution[1].size(),
			InvalidDistributionStringRepresentation,
			"Error: the Maxwell Fission distribution cannot be "
			"constructed because of an invalid nuclear temperature "
			<< distribution[1] );
    {
      double nuclear_temperature;
      
      std::istringstream iss( distribution[1] );
      Teuchos::extractDataFromISS( iss, nuclear_temperature );

      setQuantity( d_nuclear_temperature, nuclear_temperature );
    }
  
    TEST_FOR_EXCEPTION( IQT::isnaninf( d_nuclear_temperature ),
			InvalidDistributionStringRepresentation,
			"Error: the Maxwell Fission distribution cannot be "
			"constructed because of an invalid nuclear temperature "
			<< d_nuclear_temperature );
  
    TEST_FOR_EXCEPTION( d_nuclear_temperature <= IQT::zero(),
			InvalidDistributionStringRepresentation,
			"Error: the Maxwell Fission distribution cannot be "
			"constructed because of an invalid nuclear temperature "
			<< d_nuclear_temperature );
  }

  // Set the restriction energy
  if( distribution.size() > 2 )
  {
    TEST_FOR_EXCEPTION( distribution[2].find_first_not_of( " 0123456789.e" ) <
			distribution[2].size(),
			InvalidDistributionStringRepresentation,
			"Error: the Maxwell Fission distribution cannot be "
			"construcqted because of an invalid restriction energy "
			<< distribution[2] );
    {
      double restriction_energy;
      
      std::istringstream iss( distribution[2] );
      Teuchos::extractDataFromISS( iss, restriction_energy );

      setQuantity( d_restriction_energy, restriction_energy );
    }
    
    TEST_FOR_EXCEPTION( IQT::isnaninf( d_restriction_energy ),
			InvalidDistributionStringRepresentation,
			"Error: the Maxwell Fission distribution cannot be "
			"constructed because of an invalid restriction energy "
			<< d_restriction_energy );
  }

  // Set the multiplier
  if( distribution.size() > 3 )
  {
    TEST_FOR_EXCEPTION( distribution[3].find_first_not_of( " 0123456789.e" ) <
			distribution[3].size(),
			InvalidDistributionStringRepresentation,
			"Error: the Maxwell Fission distribution cannot be "
			"construcqted because of an invalid multiplier "
			<< distribution[3] );

    {
      double multiplier;
      
      std::istringstream iss( distribution[3] );
      Teuchos::extractDataFromISS( iss, multiplier );

      setQuantity( d_multiplier, multiplier );
    }

    TEST_FOR_EXCEPTION( DMQT::isnaninf( d_multiplier ),
			InvalidDistributionStringRepresentation,
			"Error: the Maxwell Fission distribution cannot be "
			"constructed because of an invalid multiplier "
			<< getRawQuantity( d_multiplier ) );
  }

  // Calculate the normalization constant
  this->calculateNormalizationConstant();
}

// Method for testing if two objects are equivalent
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::isEqual( const UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>& other ) const
{
  return d_incident_energy == other.d_incident_energy &&
    d_nuclear_temperature == other.d_nuclear_temperature &&
    d_restriction_energy == other.d_restriction_energy && 
    d_multiplier == other.d_multiplier;
}

} // end Utility namespace

#endif // end UTILITY_MAXWELL_FISSION_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_MaxwellFissionDistribution_def.hpp
//---------------------------------------------------------------------------//
