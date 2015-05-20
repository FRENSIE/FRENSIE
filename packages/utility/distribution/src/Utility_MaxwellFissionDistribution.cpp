//---------------------------------------------------------------------------//
//!
//! \file   Utility_MaxwellFissionDistribution.cpp
//! \author Aaron Tumulak
//! \brief  Maxwell Fission distribution class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_MaxwellFissionDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ArrayString.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Constructor
MaxwellFissionDistribution::MaxwellFissionDistribution(
					const double incident_energy,
					const double nuclear_temperature,
					const double restriction_energy )
  : d_incident_energy( incident_energy ),
    d_nuclear_temperature( nuclear_temperature ),
    d_restriction_energy( restriction_energy )
{
  // Make sure values are valid
  testPrecondition( !ST::isnaninf( incident_energy ) );
  testPrecondition( !ST::isnaninf( nuclear_temperature ) );
  testPrecondition( !ST::isnaninf( restriction_energy ) );
  // Make sure that incident energy is non-negative, nuclear temperature is positive
  testPrecondition( incident_energy >= 0.0 );
  testPrecondition( nuclear_temperature > 0.0 );
}

// Copy constructor
MaxwellFissionDistribution::MaxwellFissionDistribution(
				 const MaxwellFissionDistribution& dist_instance )
  : d_incident_energy( dist_instance.d_incident_energy),
    d_nuclear_temperature( dist_instance.d_nuclear_temperature),
    d_restriction_energy( dist_instance.d_restriction_energy)
{
  // Make sure the multipliers are valid
  testPrecondition( !ST::isnaninf( dist_instance.d_incident_energy ) );
  testPrecondition( !ST::isnaninf( dist_instance.d_nuclear_temperature) );
  testPrecondition( !ST::isnaninf( dist_instance.d_restriction_energy) );
  // Make sure that incident energy is non-negative, nuclear temperature is positive
  testPrecondition( dist_instance.d_incident_energy >= 0.0 );
  testPrecondition( dist_instance.d_nuclear_temperature > 0.0 );
}

// Assignment operator
MaxwellFissionDistribution& MaxwellFissionDistribution::operator=(
				 const MaxwellFissionDistribution& dist_instance )
{
  // Make sure the distribution is valid
  testPrecondition( !ST::isnaninf( dist_instance.d_incident_energy ) );
  testPrecondition( !ST::isnaninf( dist_instance.d_nuclear_temperature ) );
  testPrecondition( !ST::isnaninf( dist_instance.d_restriction_energy ) );
  testPrecondition( dist_instance.d_incident_energy >= 0.0 );
  testPrecondition( dist_instance.d_nuclear_temperature > 0.0 );

  if( this != &dist_instance )
  {
    d_incident_energy = dist_instance.d_incident_energy;
    d_nuclear_temperature = dist_instance.d_nuclear_temperature;
    d_restriction_energy = dist_instance.d_restriction_energy;
  }
  
  return *this;
}

// Evaluate the distribution
double MaxwellFissionDistribution::evaluate( const double indep_var_value ) const
{
  if( indep_var_value < 0.0 )
    return 0.0;
  else
    return evaluatePDF( indep_var_value );
}

// Evaluate the PDF
double MaxwellFissionDistribution::evaluatePDF( const double indep_var_value ) const
{
  if( indep_var_value < 0.0 )
    return 0.0;
  else
  {
    double normalizationConstant = getNormalizationConstant( d_incident_energy, d_nuclear_temperature, d_restriction_energy );
    return normalizationConstant * sqrt( indep_var_value ) * exp( -indep_var_value / d_nuclear_temperature );
  }
}

// Return a random sample from the distribution
double MaxwellFissionDistribution::sample() const
{
  unsigned trials = 0;

  return MaxwellFissionDistribution::sampleAndRecordTrials(
  d_incident_energy,
  d_nuclear_temperature,
  d_restriction_energy,
  trials );
}

// Return a random sample and record the number of trials
double MaxwellFissionDistribution::sampleAndRecordTrials( 
						       unsigned& trials ) const
{
  return MaxwellFissionDistribution::sampleAndRecordTrials( 
  d_incident_energy,
  d_nuclear_temperature,
  d_restriction_energy,
  trials );
}

// Return a random sample from the corresponding CDF and record the number of trials
double MaxwellFissionDistribution::sampleAndRecordTrials(
  const double incident_energy,
  const double nuclear_temperature,
  const double restriction_energy,
  unsigned& trials )
{
  double random_number_1, random_number_2, random_number_3;
  double term_1, term_2, sample;
  
  // Use the method outlined in OpenMC documentation under "5.7.2.4. ACE Law 7 - Maxwell Fission Spectrum"
  while( true )
  {
    random_number_1 = RandomNumberGenerator::getRandomNumber<double>();
    random_number_2 = RandomNumberGenerator::getRandomNumber<double>();
    random_number_3 = RandomNumberGenerator::getRandomNumber<double>();
    
    term_1 = log(random_number_1);
    term_2 = log(random_number_2)
      * pow( cos( PhysicalConstants::pi * random_number_3 * 0.5 ), 2.0 );
    sample = -nuclear_temperature * ( term_1 + term_2 );
  
    if( sample <= (incident_energy - restriction_energy) )
    {
      ++trials;
      break;
    }
    else
      ++trials;
  }
  
  return sample;
}

// Return the normalization constant of the distribution, pass in parameters
/*!
 * As given by ENDF Law 7
 * c^(-1) = T^(3/2)*[(sqrt(pi)/2)*erf(sqrt((E-U)/T)) - sqrt((E-U)/T)*exp(-(E-U)/T)]
 */
double MaxwellFissionDistribution::getNormalizationConstant( const double incident_energy, const double nuclear_temperature, const double restriction_energy ) const
{
  double argument = (incident_energy - restriction_energy) / nuclear_temperature;

  double normalizationConstantInverse = pow( nuclear_temperature, 3.0 * 0.5 ) * ( sqrt( PhysicalConstants::pi ) * 0.5 * erf( sqrt(argument) ) - sqrt(argument) * exp(-argument) );

  return pow( normalizationConstantInverse, -1.0 );
}

// Return the upper bound of the distribution independent variable
double MaxwellFissionDistribution::getUpperBoundOfIndepVar() const
{
  return (d_incident_energy - d_restriction_energy);
}

// Return the lower bound of the distribution independent variable
double MaxwellFissionDistribution::getLowerBoundOfIndepVar() const
{
  return 0.0;
}

// Return the distribution type
OneDDistributionType MaxwellFissionDistribution::getDistributionType() const
{
  return MaxwellFissionDistribution::distribution_type;
}

// Test if the distribution is continuous
bool MaxwellFissionDistribution::isContinuous() const
{
  return true;
}

// Method for placing the object in an output stream
void MaxwellFissionDistribution::toStream( std::ostream& os ) const
{
  os << "{" << d_incident_energy << "," << d_nuclear_temperature << ","
  << d_restriction_energy << "}";
}

// Method for initializing the object from an input stream
void MaxwellFissionDistribution::fromStream( std::istream& is )
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
  
  TEST_FOR_EXCEPTION( distribution.size() > 3,
                     InvalidDistributionStringRepresentation,
                     "Error: the Maxwell Fission distribution cannot "
                     "be constructed because the representation is "
                     "not valid"
                     "(only 3 values or fewer  may be specified)!" );
  
  // Set the incient neutron energy
  TEST_FOR_EXCEPTION( distribution[0].find_first_not_of( " 0123456789.e" ) <
                     distribution[0].size(),
                     InvalidDistributionStringRepresentation,
                     "Error: the Maxwell Fission distribution cannot be "
                     "constructed because of an invalid incident energy "
                     << distribution[0] );
  {
    std::istringstream iss( distribution[0] );
    Teuchos::extractDataFromISS( iss, d_incident_energy );
  }
  
  TEST_FOR_EXCEPTION( ST::isnaninf( d_incident_energy ),
                     InvalidDistributionStringRepresentation,
                     "Error: the Maxwell Fission distribution cannot be "
                     "constructed because of an invalid incident energy "
                     << d_incident_energy );
  
  TEST_FOR_EXCEPTION( d_incident_energy < 0.0,
                     InvalidDistributionStringRepresentation,
                     "Error: the Maxwell Fission distribution cannot be "
                     "constructed because of an invalid incident energy "
                     << d_incident_energy );
  
  // Set the nuclear temperature
  TEST_FOR_EXCEPTION( distribution[1].find_first_not_of( " 0123456789.e" ) <
                     distribution[1].size(),
                     InvalidDistributionStringRepresentation,
                     "Error: the Maxwell Fission distribution cannot be "
                     "constructed because of an invalid nuclear temperature "
                     << distribution[1] );
  {
    std::istringstream iss( distribution[1] );
    Teuchos::extractDataFromISS( iss, d_nuclear_temperature );
  }
  
  TEST_FOR_EXCEPTION( ST::isnaninf( d_nuclear_temperature ),
                     InvalidDistributionStringRepresentation,
                     "Error: the Maxwell Fission distribution cannot be "
                     "constructed because of an invalid nuclear temperature "
                     << d_nuclear_temperature );
  
  TEST_FOR_EXCEPTION( d_nuclear_temperature <= 0.0,
                     InvalidDistributionStringRepresentation,
                     "Error: the Maxwell Fission distribution cannot be "
                     "constructed because of an invalid nuclear temperature "
                     << d_nuclear_temperature );

  // Set the restriction energy
  TEST_FOR_EXCEPTION( distribution[2].find_first_not_of( " 0123456789.e" ) <
                     distribution[2].size(),
                     InvalidDistributionStringRepresentation,
                     "Error: the Maxwell Fission distribution cannot be "
                     "constructed because of an invalid restriction energy "
                     << distribution[2] );
  {
    std::istringstream iss( distribution[2] );
    Teuchos::extractDataFromISS( iss, d_restriction_energy );
  }
  
  TEST_FOR_EXCEPTION( ST::isnaninf( d_restriction_energy ),
                     InvalidDistributionStringRepresentation,
                     "Error: the Maxwell Fission distribution cannot be "
                     "constructed because of an invalid restriction energy "
                     << d_restriction_energy );
  
}

// Method for testing if two objects are equivalent
bool MaxwellFissionDistribution::isEqual( const MaxwellFissionDistribution& other ) const
{
  return d_incident_energy == other.d_incident_energy &&
  d_nuclear_temperature == other.d_nuclear_temperature &&
  d_restriction_energy == other.d_restriction_energy;
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_MaxwellFissionDistribution.cpp
//---------------------------------------------------------------------------//
