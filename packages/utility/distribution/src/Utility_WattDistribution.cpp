//---------------------------------------------------------------------------//
//!
//! \file   Utility_WattDistribution.cpp
//! \author Aaron Tumulak
//! \brief  Watt distribution class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_WattDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ArrayString.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_MaxwellFissionDistribution.hpp"

namespace Utility{

// Constructor
WattDistribution::WattDistribution(
					const double incident_energy,
					const double a_parameter,
					const double b_parameter,
					const double restriction_energy )
  : d_incident_energy( incident_energy ),
    d_a_parameter( a_parameter ),
    d_b_parameter( b_parameter ),
    d_restriction_energy( restriction_energy )
{
  // Make sure values are valid
  testPrecondition( !ST::isnaninf( incident_energy ) );
  testPrecondition( !ST::isnaninf( a_parameter ) );
  testPrecondition( !ST::isnaninf( b_parameter ) );
  testPrecondition( !ST::isnaninf( restriction_energy ) );
  // Make sure that incident energy is non-negative, a_parameter is positive,
  // b_parameter is positive
  testPrecondition( incident_energy >= 0.0 );
  testPrecondition( a_parameter > 0.0 );
  testPrecondition( b_parameter > 0.0 );
}

// Copy constructor
WattDistribution::WattDistribution(
				 const WattDistribution& dist_instance )
  : d_incident_energy( dist_instance.d_incident_energy),
    d_a_parameter( dist_instance.d_a_parameter),
    d_b_parameter( dist_instance.d_b_parameter),
    d_restriction_energy( dist_instance.d_restriction_energy)
{
  // Make sure the multipliers are valid
  testPrecondition( !ST::isnaninf( dist_instance.d_incident_energy ) );
  testPrecondition( !ST::isnaninf( dist_instance.d_a_parameter ) );
  testPrecondition( !ST::isnaninf( dist_instance.d_b_parameter ) );
  testPrecondition( !ST::isnaninf( dist_instance.d_restriction_energy) );
  // Make sure that incident energy is non-negative, a_parameter is positive,
  // b_parameter is positive
  testPrecondition( dist_instance.d_incident_energy >= 0.0 );
  testPrecondition( dist_instance.d_a_parameter > 0.0 );
  testPrecondition( dist_instance.d_b_parameter > 0.0 );
}

// Assignment operator
WattDistribution& WattDistribution::operator=(
				 const WattDistribution& dist_instance )
{
  // Make sure the distribution is valid
  testPrecondition( !ST::isnaninf( dist_instance.d_incident_energy ) );
  testPrecondition( !ST::isnaninf( dist_instance.d_a_parameter ) );
  testPrecondition( !ST::isnaninf( dist_instance.d_b_parameter ) );
  testPrecondition( !ST::isnaninf( dist_instance.d_restriction_energy ) );
  testPrecondition( dist_instance.d_incident_energy >= 0.0 );
  testPrecondition( dist_instance.d_a_parameter > 0.0 );
  testPrecondition( dist_instance.d_b_parameter > 0.0 );

  if( this != &dist_instance )
  {
    d_incident_energy = dist_instance.d_incident_energy;
    d_a_parameter = dist_instance.d_a_parameter;
    d_b_parameter = dist_instance.d_b_parameter;
    d_restriction_energy = dist_instance.d_restriction_energy;
  }
  
  return *this;
}

// Evaluate the distribution
double WattDistribution::evaluate( const double indep_var_value ) const
{
  if( indep_var_value < 0.0 )
    return 0.0;
  else
    return evaluatePDF( indep_var_value );
}

// Evaluate the PDF
/*! \details PDF(x) = c*e^(-x/a)*sinh(sqrt(b*x))
 */
double WattDistribution::evaluatePDF( const double indep_var_value ) const
{
  if( indep_var_value < 0.0 )
    return 0.0;
  else
  {
    return getNormalizationConstant( d_incident_energy, d_a_parameter, d_b_parameter, d_restriction_energy ) * exp( -indep_var_value / d_a_parameter ) * sinh( sqrt( d_b_parameter * indep_var_value ) );
  }
}

// Return a random sample from the distribution
double WattDistribution::sample() const
{
  unsigned trials = 0;

  return WattDistribution::sampleAndRecordTrials(
  d_incident_energy,
  d_a_parameter,
  d_b_parameter,
  d_restriction_energy,
  trials );
}

// Return a random sample and record the number of trials
double WattDistribution::sampleAndRecordTrials( unsigned& trials ) const
{
  return WattDistribution::sampleAndRecordTrials(
  d_incident_energy,
  d_a_parameter,
  d_b_parameter,
  d_restriction_energy,
  trials );
}

// Return a random sample from the corresponding CDF and record the number of trials
double WattDistribution::sampleAndRecordTrials(
  const double incident_energy,
  const double a_parameter,
  const double b_parameter,
  const double restriction_energy,
  unsigned& trials )
{
  double maxwell_sample, random_number;
  double sample;
  
  // Use ACE law 11
  while( true )
  {
    // Sample Maxwell Fission Distribution
    unsigned maxwell_trials = 0;

    maxwell_sample = Utility::MaxwellFissionDistribution::sampleAndRecordTrials(
      incident_energy,
      a_parameter,
      restriction_energy,
      maxwell_trials ); 
   
    // Sample random number 
    random_number = RandomNumberGenerator::getRandomNumber<double>();
    
    sample = maxwell_sample + ( pow( a_parameter, 2.0 ) * b_parameter * 0.25 ) 
      + ( 2.0 * random_number - 1.0 ) * sqrt( pow( a_parameter , 2.0 ) * b_parameter 
      * maxwell_sample ); 
 
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
/*! \details As given in ENDF Law 11:
 * c^(-1) = (1/2)*sqrt(pi*a^3*b/4)*exp(a*b/4)*(erf(sqrt((E-U)/a)-sqrt(a*b/4))+erf(sqrt((E-U)/a)+sqrt(a*b/4)))
 * - a*exp(-(E-U)/a)*sinh(sqrt(b*(E-U)))
 */
double WattDistribution::getNormalizationConstant(
  const double incident_energy,
  const double a_parameter,
  const double b_parameter,
  const double restriction_energy ) const
{
  double argument_1 = ( incident_energy - restriction_energy ) / a_parameter;
  double argument_2 = a_parameter * b_parameter * 0.25;
  double argument_3 = PhysicalConstants::pi * pow( a_parameter, 3.0 ) * b_parameter * 0.25;

  double normalizationConstantInverse = 0.5 * sqrt( argument_3 ) * exp( argument_2 )
    * ( erf( sqrt( argument_1) - sqrt( argument_2 ) ) + erf( sqrt( argument_1 )
    + sqrt( argument_2 ) ) ) - a_parameter * exp( -argument_1 )
    * sinh( sqrt( argument_1 * a_parameter * b_parameter ) );

  return pow( normalizationConstantInverse, -1.0 );
}

// Return the upper bound of the distribution independent variable
double WattDistribution::getUpperBoundOfIndepVar() const
{
  return (d_incident_energy - d_restriction_energy);
}

// Return the lower bound of the distribution independent variable
double WattDistribution::getLowerBoundOfIndepVar() const
{
  return 0.0;
}

// Return the distribution type
OneDDistributionType WattDistribution::getDistributionType() const
{
  return WattDistribution::distribution_type;
}

// Test if the distribution is continuous
bool WattDistribution::isContinuous() const
{
  return true;
}

// Method for placing the object in an output stream
void WattDistribution::toStream( std::ostream& os ) const
{
  os << "{" << d_incident_energy << "," << d_a_parameter << ","
  << d_b_parameter << "," << d_restriction_energy << "}";
}

// Method for initializing the object from an input stream
void WattDistribution::fromStream( std::istream& is )
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
    std::string message( "Error: the Watt distribution cannot be "
                        "constructed because the representation is not valid "
                        "(see details below)!\n" );
    message += error.what();
    
    throw InvalidDistributionStringRepresentation( message );
  }
  
  TEST_FOR_EXCEPTION( distribution.size() > 4,
                     InvalidDistributionStringRepresentation,
                     "Error: the Watt distribution cannot "
                     "be constructed because the representation is "
                     "not valid"
                     "(only 4 values or fewer  may be specified)!" );
  
  // Set the incient neutron energy
  TEST_FOR_EXCEPTION( distribution[0].find_first_not_of( " 0123456789.e" ) <
                     distribution[0].size(),
                     InvalidDistributionStringRepresentation,
                     "Error: the Watt distribution cannot be "
                     "constructed because of an invalid incident energy "
                     << distribution[0] );
  {
    std::istringstream iss( distribution[0] );
    Teuchos::extractDataFromISS( iss, d_incident_energy );
  }
  
  TEST_FOR_EXCEPTION( ST::isnaninf( d_incident_energy ),
                     InvalidDistributionStringRepresentation,
                     "Error: the Watt distribution cannot be "
                     "constructed because of an invalid incident energy "
                     << d_incident_energy );
  
  TEST_FOR_EXCEPTION( d_incident_energy < 0.0,
                     InvalidDistributionStringRepresentation,
                     "Error: the Watt distribution cannot be "
                     "constructed because of an invalid incident energy "
                     << d_incident_energy );
  
  // Set the a_parameter
  TEST_FOR_EXCEPTION( distribution[1].find_first_not_of( " 0123456789.e" ) <
                     distribution[1].size(),
                     InvalidDistributionStringRepresentation,
                     "Error: the Watt distribution cannot be "
                     "constructed because of an invalid a_parameter "
                     << distribution[1] );
  {
    std::istringstream iss( distribution[1] );
    Teuchos::extractDataFromISS( iss, d_a_parameter );
  }
  
  TEST_FOR_EXCEPTION( ST::isnaninf( d_a_parameter ),
                     InvalidDistributionStringRepresentation,
                     "Error: the Watt distribution cannot be "
                     "constructed because of an invalid a_parameter "
                     << d_a_parameter );
  
  TEST_FOR_EXCEPTION( d_a_parameter <= 0.0,
                     InvalidDistributionStringRepresentation,
                     "Error: the Watt distribution cannot be "
                     "constructed because of an invalid a_parameter "
                     << d_a_parameter );

  // Set the b_parameter
  TEST_FOR_EXCEPTION( distribution[2].find_first_not_of( " 0123456789.e" ) <
                     distribution[2].size(),
                     InvalidDistributionStringRepresentation,
                     "Error: the Watt distribution cannot be "
                     "constructed because of an invalid b_parameter "
                     << distribution[2] );
  {
    std::istringstream iss( distribution[2] );
    Teuchos::extractDataFromISS( iss, d_b_parameter );
  }
  
  TEST_FOR_EXCEPTION( ST::isnaninf( d_b_parameter ),
                     InvalidDistributionStringRepresentation,
                     "Error: the Watt distribution cannot be "
                     "constructed because of an invalid b_parameter "
                     << d_b_parameter );
  
  TEST_FOR_EXCEPTION( d_b_parameter <= 0.0,
                     InvalidDistributionStringRepresentation,
                     "Error: the Watt distribution cannot be "
                     "constructed because of an invalid b_parameter "
                     << d_b_parameter );

  // Set the restriction energy
  TEST_FOR_EXCEPTION( distribution[3].find_first_not_of( " 0123456789.e" ) <
                     distribution[3].size(),
                     InvalidDistributionStringRepresentation,
                     "Error: the Watt distribution cannot be "
                     "constructed because of an invalid restriction energy "
                     << distribution[3] );
  {
    std::istringstream iss( distribution[3] );
    Teuchos::extractDataFromISS( iss, d_restriction_energy );
  }
  
  TEST_FOR_EXCEPTION( ST::isnaninf( d_restriction_energy ),
                     InvalidDistributionStringRepresentation,
                     "Error: the Watt distribution cannot be "
                     "constructed because of an invalid restriction energy "
                     << d_restriction_energy );
  
}

// Method for testing if two objects are equivalent
bool WattDistribution::isEqual( const WattDistribution& other ) const
{
  return d_incident_energy == other.d_incident_energy &&
  d_a_parameter == other.d_a_parameter &&
  d_b_parameter == other.d_b_parameter &&
  d_restriction_energy == other.d_restriction_energy;
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_WattDistribution.cpp
//---------------------------------------------------------------------------//
