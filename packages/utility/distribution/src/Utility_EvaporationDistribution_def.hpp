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
#include "Utility_ContractException.hpp"

namespace Utility{

// Default Constructor
template<typename IndependentUnit, typename DependentUnit>
UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::UnitAwareEvaporationDistribution(
  const UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::IndepQuantity incident_energy,
  const UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::IndepQuantity nuclear_temperature,
  const UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::IndepQuantity restriction_energy )
  : d_incident_energy( incident_energy ),
    d_nuclear_temperature( nuclear_temperature ),
    d_restriction_energy( restriction_energy )
{
  // Make sure values are valid
  testPrecondition( !ST::isnaninf( getRawQuantity( incident_energy ) ) );
  testPrecondition( !ST::isnaninf( getRawQuantity( nuclear_temperature ) ) );
  testPrecondition( !ST::isnaninf( getRawQuantity( restriction_energy ) ) );
  // Make sure that incident energy and nuclear temperature are positive
  testPrecondition( incident_energy > QuantityTraits<IndepQuantity>::zero() );
  testPrecondition( nuclear_temperature > QuantityTraits<IndepQuantity>::zero() );
}

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
				 const InputIndepQuantityC restriction_energy )
  : d_incident_energy( incident_energy ),
    d_nuclear_temperature( nuclear_temperature ),
    d_restriction_energy( restriction_energy )
{
  // Make sure values are valid
  testPrecondition( !ST::isnaninf( getRawQuantity( incident_energy ) ) );
  testPrecondition( !ST::isnaninf( getRawQuantity( nuclear_temperature ) ) );
  testPrecondition( !ST::isnaninf( getRawQuantity( restriction_energy ) ) );
  // Make sure that incident energy and nuclear temperature are positive
  testPrecondition( incident_energy > QuantityTraits<InputIndepQuantityA>::zero() );
  testPrecondition( nuclear_temperature > QuantityTraits<InputIndepQuantityB>::zero() );
}

// Copy constructor
template<typename IndependentUnit, typename DependentUnit>
UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::UnitAwareEvaporationDistribution(
  const UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>& dist_instance )
  : d_incident_energy( dist_instance.d_incident_energy),
    d_nuclear_temperature( dist_instance.d_nuclear_temperature),
    d_restriction_energy( dist_instance.d_restriction_energy)
{
  // Make sure the multipliers are valid
  testPrecondition( !ST::isnaninf( getRawQuantity( dist_instance.d_incident_energy ) ) );
  testPrecondition( !ST::isnaninf( getRawQuantity( dist_instance.d_nuclear_temperature) ) );
  testPrecondition( !ST::isnaninf( getRawQuantity( dist_instance.d_restriction_energy) ) );
  // Make sure that incident energy and nuclear temperature are positive
  testPrecondition( dist_instance.d_incident_energy > 
		    QuantityTraits<IndepQuantity>::zero() );
  testPrecondition( dist_instance.d_nuclear_temperature > 
		    QuantityTraits<IndepQuantity>::zero() );
}

// Assignment operator
template<typename IndependentUnit, typename DependentUnit>
UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>& 
UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::operator=(
   const UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>& dist_instance )
{
  // Make sure the distribution is valid
  testPrecondition( !ST::isnaninf( getRawQuantity( dist_instance.d_incident_energy ) ) );
  testPrecondition( !ST::isnaninf( getRawQuantity( dist_instance.d_nuclear_temperature ) ) );
  testPrecondition( !ST::isnaninf( getRawQuantity( dist_instance.d_restriction_energy ) ) );
  testPrecondition( dist_instance.d_incident_energy > 
		    QuantityTraits<IndepQuantity>::zero() );
  testPrecondition( dist_instance.d_nuclear_temperature > 
		    QuantityTraits<IndepQuantity>::zero() );

  if( this != &dist_instance )
  {
    d_incident_energy = dist_instance.d_incident_energy;
    d_nuclear_temperature = dist_instance.d_nuclear_temperature;
    d_restriction_energy = dist_instance.d_restriction_energy;
  }
  
  return *this;
}

// Evaluate the distribution
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::DepQuantity
UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::evaluate( 
  const typename UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  return Utility::QuantityTraits<DepQuantity>::initializeQuantity( 
		      getRawQuantity( this->evaluatePDF( indep_var_value ) ) );
}

// Evaluate the PDF
/*! \details PDF(x) = c*x*exp(-x/T) if x >= 0, = 0 if x < 0
 */
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity
UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::evaluatePDF( 
const typename UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  if( indep_var_value < QuantityTraits<IndepQuantity>::zero() )
    return QuantityTraits<InverseIndepQuantity>::zero();
  else
  {
    return UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::getNormalizationConstant( d_incident_energy, d_nuclear_temperature, d_restriction_energy ) * indep_var_value * exp( -indep_var_value / d_nuclear_temperature );
  }
}

// Return a random sample from the distribution
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::sample() const
{
  unsigned trials = 0;
    
  return UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::sampleAndRecordTrials(
  d_incident_energy,
  d_nuclear_temperature,
  d_restriction_energy,
  trials );
}

// Return a random sample and record the number of trials
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::sampleAndRecordTrials( unsigned& trials ) const
{
  return UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::sampleAndRecordTrials(
  d_incident_energy,
  d_nuclear_temperature,
  d_restriction_energy,
  trials );
}

// Return a random sample from the corresponding CDF and record the number of trials
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::sampleAndRecordTrials(
  const typename UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::IndepQuantity incident_energy,
  const typename UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::IndepQuantity nuclear_temperature,
  const typename UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::IndepQuantity restriction_energy,
  unsigned& trials )
{
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

// Return the normalization constant of the distribution, pass in parameters
/*!
 * \details As given in LA-UR-14-27694
 * c = T^(-2)*[1-exp(-(E-U)/T)*(1+(E-U)/T)]^-1
 */
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::InverseSquaredIndepQuantity
UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::getNormalizationConstant(
  const typename UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::IndepQuantity incident_energy,
  const typename UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::IndepQuantity nuclear_temperature,
  const typename UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::IndepQuantity restriction_energy )
{
  double argument = (incident_energy - restriction_energy) / nuclear_temperature;

  return 1.0/( nuclear_temperature*nuclear_temperature*
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
  return QuantityTraits<IndepQuantity>::zero();
}

// Return the distribution type
template<typename IndependentUnit, typename DependentUnit>
OneDDistributionType 
UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::getDistributionType() const
{
  return UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::distribution_type;
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
     << "," << getRawQuantity( d_restriction_energy ) << "}";
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
  
  TEST_FOR_EXCEPTION( distribution.size() > 3,
                     InvalidDistributionStringRepresentation,
                     "Error: the Evaporation distribution cannot "
                     "be constructed because the representation is "
                     "not valid"
                     "(only 3 values or fewer  may be specified)!" );
  
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
  
    TEST_FOR_EXCEPTION( ST::isnaninf( getRawQuantity( d_incident_energy ) ),
			InvalidDistributionStringRepresentation,
			"Error: the Evaporation distribution cannot be "
			"constructed because of an invalid incident energy "
			<< d_incident_energy );
    
    TEST_FOR_EXCEPTION(d_incident_energy < QuantityTraits<IndepQuantity>::zero(),
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
    
    TEST_FOR_EXCEPTION(ST::isnaninf( getRawQuantity( d_nuclear_temperature ) ),
		       InvalidDistributionStringRepresentation,
		       "Error: the Evaporation distribution cannot be "
		       "constructed because of an invalid nuclear temperature "
		       << d_nuclear_temperature );
    
    TEST_FOR_EXCEPTION(d_nuclear_temperature <= 
		       QuantityTraits<IndepQuantity>::zero(),
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
    
    TEST_FOR_EXCEPTION( ST::isnaninf( getRawQuantity( d_restriction_energy ) ),
			InvalidDistributionStringRepresentation,
			"Error: the Evaporation distribution cannot be "
			"constructed because of an invalid restriction energy "
			<< d_restriction_energy );
  }
}

// Method for testing if two objects are equivalent
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::isEqual( 
const UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>& other ) const
{
  return d_incident_energy == other.d_incident_energy &&
  d_nuclear_temperature == other.d_nuclear_temperature &&
  d_restriction_energy == other.d_restriction_energy;
}

} // end Utility namespace

#endif // end UTILITY_EVAPORATION_DISTRIBUTION_DEF_HPP 

//---------------------------------------------------------------------------//
// end Utility_EvaporationDistribution_def.hpp
//---------------------------------------------------------------------------//
