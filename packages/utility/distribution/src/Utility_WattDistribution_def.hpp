//---------------------------------------------------------------------------//
//!
//! \file   Utility_WattDistribution_def.hpp
//! \author Aaron Tumulak
//! \brief  Watt distribution class definition. Modified by Alex Robinson
//!         to accommodate units.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_WATT_DISTRIBUTION_DEF_HPP
#define UTILITY_WATT_DISTRIBUTION_DEF_HPP

// FRENSIE Includes
#include "Utility_MaxwellFissionDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ArrayString.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Explicit instantiation (extern declaration)
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareWattDistribution<void,void> );
  
// Constructor
/*! \details This constructor will explicitly cast the input quantities to
 * the distribution quantity (which includes any unit-conversion). The
 * dimension type must match and there must be a unit-conversion defined using
 * the boost methodology.
 */
template<typename IndependentUnit, typename DependentUnit>
template<typename InputIndepQuantityA,
	 typename InputIndepQuantityB,
	 typename InputInverseIndepQuantity,
	 typename InputIndepQuantityC>
UnitAwareWattDistribution<IndependentUnit,DependentUnit>::UnitAwareWattDistribution(
                                 const InputIndepQuantityA incident_energy,
				 const InputIndepQuantityB a_parameter,
				 const InputInverseIndepQuantity b_parameter,
				 const InputIndepQuantityC restriction_energy,
				 const double constant_multiplier )
  : d_incident_energy( incident_energy ),
    d_a_parameter( a_parameter ),
    d_b_parameter( b_parameter ),
    d_restriction_energy( restriction_energy ),
    d_multiplier( DMQT::initializeQuantity( constant_multiplier ) ),
    d_norm_constant()
{
  // Make sure values are valid
  testPrecondition( !QuantityTraits<InputIndepQuantityA>::isnaninf( incident_energy ) );
  testPrecondition( !QuantityTraits<InputIndepQuantityB>::isnaninf( a_parameter ) );
  testPrecondition( !QuantityTraits<InputInverseIndepQuantity>::isnaninf( b_parameter ) );
  testPrecondition( !QuantityTraits<InputIndepQuantityC>::isnaninf( restriction_energy ) );
  testPrecondition( !QT::isnaninf( constant_multiplier ) );
  // Make sure that incident energy, a_parameter, and b_parameter are positive
  testPrecondition( incident_energy >
		    QuantityTraits<InputIndepQuantityA>::zero() );
  testPrecondition( a_parameter >
		    QuantityTraits<InputIndepQuantityB>::zero() );
  testPrecondition( b_parameter >
		    QuantityTraits<InputInverseIndepQuantity>::zero() );
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
UnitAwareWattDistribution<IndependentUnit,DependentUnit>::UnitAwareWattDistribution(
  const UnitAwareWattDistribution<InputIndepUnit,InputDepUnit>& dist_instance )
  : d_incident_energy( dist_instance.d_incident_energy),
    d_a_parameter( dist_instance.d_a_parameter),
    d_b_parameter( dist_instance.d_b_parameter),
    d_restriction_energy( dist_instance.d_restriction_energy),
    d_multiplier( dist_instance.d_multiplier ),
    d_norm_constant()
{
  // Make sure the multipliers are valid
  remember( typedef QuantityTraits<typename UnitAwareWattDistribution<InputIndepUnit,InputDepUnit>::IndepQuantity> InputIQT );
  remember( typedef QuantityTraits<typename UnitAwareWattDistribution<InputIndepUnit,InputDepUnit>::InverseIndepQuantity> InputIIQT );
  testPrecondition( !InputIQT::isnaninf( dist_instance.d_incident_energy ) );
  testPrecondition( !InputIQT::isnaninf( dist_instance.d_a_parameter ) );
  testPrecondition( !InputIIQT::isnaninf( dist_instance.d_b_parameter ) );
  testPrecondition( !InputIQT::isnaninf( dist_instance.d_restriction_energy ));
  // Make sure that incident energy, a_parameter, and b_parameter are positive
  testPrecondition( dist_instance.d_incident_energy > InputIQT::zero() );
  testPrecondition( dist_instance.d_a_parameter > InputIQT::zero() );
  testPrecondition( dist_instance.d_b_parameter > InputIIQT::zero() );

  // Calculate the norm constant
  this->calculateNormalizationConstant();
}

// Copy constructor (copying from unitless distribution only)
template<typename IndependentUnit, typename DependentUnit>
UnitAwareWattDistribution<IndependentUnit,DependentUnit>::UnitAwareWattDistribution( const UnitAwareWattDistribution<void,void>& unitless_dist_instance, int )
  : d_incident_energy( IQT::initializeQuantity( unitless_dist_instance.d_incident_energy ) ),
    d_a_parameter( IQT::initializeQuantity( unitless_dist_instance.d_a_parameter ) ),
    d_b_parameter( IIQT::initializeQuantity( unitless_dist_instance.d_b_parameter ) ),
    d_restriction_energy( IQT::initializeQuantity( unitless_dist_instance.d_restriction_energy ) ),
    d_multiplier( DMQT::initializeQuantity( unitless_dist_instance.d_multiplier ) ),
    d_norm_constant()
{
  // Make sure the multipliers are valid
  testPrecondition( !QT::isnaninf( unitless_dist_instance.d_incident_energy ) );
  testPrecondition( !QT::isnaninf( unitless_dist_instance.d_a_parameter ) );
  testPrecondition( !QT::isnaninf( unitless_dist_instance.d_b_parameter ) );
  testPrecondition( !QT::isnaninf( unitless_dist_instance.d_restriction_energy ) );
  // Make sure that incident energy, a_parameter, and b_parameter are positive
  testPrecondition( unitless_dist_instance.d_incident_energy > 0.0 );
  testPrecondition( unitless_dist_instance.d_a_parameter > 0.0 );
  testPrecondition( unitless_dist_instance.d_b_parameter > 0.0 );

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
UnitAwareWattDistribution<IndependentUnit,DependentUnit>
UnitAwareWattDistribution<IndependentUnit,DependentUnit>::fromUnitlessDistribution( const UnitAwareWattDistribution<void,void>& unitless_distribution )
{
  return ThisType( unitless_distribution, 0 );
}

// Assignment operator
template<typename IndependentUnit, typename DependentUnit>
UnitAwareWattDistribution<IndependentUnit,DependentUnit>&
UnitAwareWattDistribution<IndependentUnit,DependentUnit>::operator=(
const UnitAwareWattDistribution<IndependentUnit,DependentUnit>& dist_instance )
{
  // Make sure the distribution is valid
  testPrecondition( !IQT::isnaninf( dist_instance.d_incident_energy ) );
  testPrecondition( !IQT::isnaninf( dist_instance.d_a_parameter ) );
  testPrecondition( !IIQT::isnaninf( dist_instance.d_b_parameter ) );
  testPrecondition( !IQT::isnaninf( dist_instance.d_restriction_energy ) );
  testPrecondition( dist_instance.d_incident_energy > IQT::zero() );
  testPrecondition( dist_instance.d_a_parameter > IQT::zero() );
  testPrecondition( dist_instance.d_b_parameter > IIQT::zero() );

  if( this != &dist_instance )
  {
    d_incident_energy = dist_instance.d_incident_energy;
    d_a_parameter = dist_instance.d_a_parameter;
    d_b_parameter = dist_instance.d_b_parameter;
    d_restriction_energy = dist_instance.d_restriction_energy;
    d_multiplier = dist_instance.d_multiplier;
    d_norm_constant = dist_instance.d_norm_constant;
  }

  return *this;
}

// Evaluate the distribution
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareWattDistribution<IndependentUnit,DependentUnit>::DepQuantity
UnitAwareWattDistribution<IndependentUnit,DependentUnit>::evaluate(
  const typename UnitAwareWattDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  if( indep_var_value < IQT::zero() )
    return DQT::zero();
  else
  {
    return d_multiplier*exp( -indep_var_value / d_a_parameter )*
      sinh( sqrt( d_b_parameter * indep_var_value ) );
  }
}

// Evaluate the PDF
/*! \details PDF(x) = c*e^(-x/a)*sinh(sqrt(b*x))
 */
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareWattDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity
UnitAwareWattDistribution<IndependentUnit,DependentUnit>::evaluatePDF(
  const typename UnitAwareWattDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  return this->evaluate( indep_var_value )*d_norm_constant;
}

// Return a random sample from the distribution
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareWattDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareWattDistribution<IndependentUnit,DependentUnit>::sample() const
{
  return ThisType::sample( d_incident_energy,
			   d_a_parameter,
			   d_b_parameter,
			   d_restriction_energy );
}

// Return a sample from the distribution
template<typename IndependentUnit, typename DependentUnit>
inline typename UnitAwareWattDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareWattDistribution<IndependentUnit,DependentUnit>::sample(
  const typename UnitAwareWattDistribution<IndependentUnit,DependentUnit>::IndepQuantity incident_energy,
  const typename UnitAwareWattDistribution<IndependentUnit,DependentUnit>::IndepQuantity a_parameter,
  const typename UnitAwareWattDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity b_parameter,
	const typename UnitAwareWattDistribution<IndependentUnit,DependentUnit>::IndepQuantity restriction_energy )
{
  unsigned trials = 0;

  return ThisType::sampleAndRecordTrials( incident_energy,
					  a_parameter,
					  b_parameter,
					  restriction_energy,
					  trials );
}

// Return a random sample and record the number of trials
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareWattDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareWattDistribution<IndependentUnit,DependentUnit>::sampleAndRecordTrials( unsigned& trials ) const
{
  return ThisType::sampleAndRecordTrials( d_incident_energy,
					  d_a_parameter,
					  d_b_parameter,
					  d_restriction_energy,
					  trials );
}

// Return a random sample from the corresponding CDF and record the number of trials
template<typename IndependentUnit, typename DependentUnit>
inline typename UnitAwareWattDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareWattDistribution<IndependentUnit,DependentUnit>::sampleAndRecordTrials(
  const typename UnitAwareWattDistribution<IndependentUnit,DependentUnit>::IndepQuantity incident_energy,
  const typename UnitAwareWattDistribution<IndependentUnit,DependentUnit>::IndepQuantity a_parameter,
  const typename UnitAwareWattDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity b_parameter,
  const typename UnitAwareWattDistribution<IndependentUnit,DependentUnit>::IndepQuantity restriction_energy,
  unsigned& trials )
{
  // Make sure values are valid
  testPrecondition( !IQT::isnaninf( incident_energy ) );
  testPrecondition( !IQT::isnaninf( a_parameter ) );
  testPrecondition( !IIQT::isnaninf( b_parameter ) );
  testPrecondition( !IQT::isnaninf( restriction_energy ) );
  // Make sure that incident energy, a_parameter, and b_parameter are positive
  testPrecondition( incident_energy > IQT::zero() );
  testPrecondition( a_parameter > IQT::zero() );
  testPrecondition( b_parameter > IIQT::zero() );

  double random_number;
  IndepQuantity maxwell_sample, sample;

  // Use ACE law 11
  while( true )
  {
    // Sample Maxwell Fission Distribution (trials counter incremented inside)
    maxwell_sample = Utility::UnitAwareMaxwellFissionDistribution<IndependentUnit,DependentUnit>::sampleAndRecordTrials(
      incident_energy,
      a_parameter,
      restriction_energy,
      trials );

    // Sample random number
    random_number = RandomNumberGenerator::getRandomNumber<double>();

    sample = maxwell_sample + 0.25*a_parameter*a_parameter*b_parameter +
      (2.0*random_number-1.0)*Utility::sqrt( a_parameter*a_parameter*
					     b_parameter*maxwell_sample );

    if( sample <= (incident_energy - restriction_energy) )
      break;
  }

  return sample;
}

// Calculate the normalization constant of the distribution
/* \details As given in ENDF Law 11:
 * c^(-1) = (1/2)*sqrt(pi*a^3*b/4)*exp(a*b/4)*(erf(sqrt((E-U)/a)-sqrt(a*b/4))+erf(sqrt((E-U)/a)+sqrt(a*b/4)))
 * - a*exp(-(E-U)/a)*sinh(sqrt(b*(E-U)))
 */
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareWattDistribution<IndependentUnit,DependentUnit>::calculateNormalizationConstant()
{
  double argument_1 = (d_incident_energy - d_restriction_energy)/d_a_parameter;
  double argument_2 = d_a_parameter*d_b_parameter*0.25;

  IndepQuantity term_1 = 0.5*exp( argument_2 )*
    (erf( sqrt(argument_1) - sqrt(argument_2) ) +
     erf( sqrt(argument_1)+ sqrt(argument_2) ))*
    Utility::sqrt( 0.25*PhysicalConstants::pi*
		   d_a_parameter*d_a_parameter*d_a_parameter*d_b_parameter );

  IndepQuantity term_2 = d_a_parameter*exp( -argument_1 )*
    sinh( Utility::sqrt(argument_1*d_a_parameter*d_b_parameter) );

  d_norm_constant = 1.0/( d_multiplier*(term_1 - term_2) );
}

// Return the upper bound of the distribution independent variable
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareWattDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareWattDistribution<IndependentUnit,DependentUnit>::getUpperBoundOfIndepVar() const
{
  return (d_incident_energy - d_restriction_energy);
}

// Return the lower bound of the distribution independent variable
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareWattDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareWattDistribution<IndependentUnit,DependentUnit>::getLowerBoundOfIndepVar() const
{
  return IQT::zero();
}

// Return the distribution type
template<typename IndependentUnit, typename DependentUnit>
OneDDistributionType
UnitAwareWattDistribution<IndependentUnit,DependentUnit>::getDistributionType() const
{
  return ThisType::distribution_type;
}

// Test if the distribution is continuous
template<typename IndependentUnit, typename DependentUnit>
bool
UnitAwareWattDistribution<IndependentUnit,DependentUnit>::isContinuous() const
{
  return true;
}

// Method for placing the object in an output stream
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareWattDistribution<IndependentUnit,DependentUnit>::toStream( std::ostream& os ) const
{
  os << "{" << getRawQuantity( d_incident_energy )
     << "," << getRawQuantity( d_a_parameter )
     << "," << getRawQuantity( d_b_parameter )
     << "," << getRawQuantity( d_restriction_energy );

  // Only print the multiplier when a scaling has been done
  if( d_multiplier != DMQT::one() )
    os << "," << getRawQuantity( d_multiplier ) << "}";
  else
    os << "}";
}

// Method for initializing the object from an input stream
template<typename IndependentUnit, typename DependentUnit>
void
UnitAwareWattDistribution<IndependentUnit,DependentUnit>::fromStream( std::istream& is )
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

  TEST_FOR_EXCEPTION( distribution.size() > 5,
                     InvalidDistributionStringRepresentation,
                     "Error: the Watt distribution cannot "
                     "be constructed because the representation is "
                     "not valid"
                     "(only 5 values or fewer  may be specified)!" );

  // Set the incient neutron energy
  if( distribution.size() > 0 )
  {
    TEST_FOR_EXCEPTION( distribution[0].find_first_not_of( " 0123456789.e" ) <
			distribution[0].size(),
			InvalidDistributionStringRepresentation,
			"Error: the Watt distribution cannot be "
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
			"Error: the Watt distribution cannot be "
			"constructed because of an invalid incident energy "
			<< d_incident_energy );

    TEST_FOR_EXCEPTION( d_incident_energy < IQT::zero(),
			InvalidDistributionStringRepresentation,
			"Error: the Watt distribution cannot be "
			"constructed because of an invalid incident energy "
			<< d_incident_energy );
  }

  // Set the a_parameter
  if( distribution.size() > 1 )
  {
    TEST_FOR_EXCEPTION( distribution[1].find_first_not_of( " 0123456789.e" ) <
			distribution[1].size(),
			InvalidDistributionStringRepresentation,
			"Error: the Watt distribution cannot be "
			"constructed because of an invalid a_parameter "
			<< distribution[1] );
    {
      double a_parameter;

      std::istringstream iss( distribution[1] );
      Teuchos::extractDataFromISS( iss, a_parameter );

      setQuantity( d_a_parameter, a_parameter );
    }

    TEST_FOR_EXCEPTION( IQT::isnaninf( d_a_parameter ),
			InvalidDistributionStringRepresentation,
			"Error: the Watt distribution cannot be "
			"constructed because of an invalid a_parameter "
			<< d_a_parameter );

    TEST_FOR_EXCEPTION( d_a_parameter <= IQT::zero(),
			InvalidDistributionStringRepresentation,
			"Error: the Watt distribution cannot be "
			"constructed because of an invalid a_parameter "
			<< d_a_parameter );
  }

  // Set the b_parameter
  if( distribution.size() > 2 )
  {
    TEST_FOR_EXCEPTION( distribution[2].find_first_not_of( " 0123456789.e" ) <
			distribution[2].size(),
			InvalidDistributionStringRepresentation,
			"Error: the Watt distribution cannot be "
			"constructed because of an invalid b_parameter "
			<< distribution[2] );
    {
      double b_parameter;

      std::istringstream iss( distribution[2] );
      Teuchos::extractDataFromISS( iss, b_parameter );

      setQuantity( d_b_parameter, b_parameter );
    }

    TEST_FOR_EXCEPTION( IIQT::isnaninf( d_b_parameter ),
			InvalidDistributionStringRepresentation,
			"Error: the Watt distribution cannot be "
			"constructed because of an invalid b_parameter "
			<< d_b_parameter );

    TEST_FOR_EXCEPTION( d_b_parameter <= IIQT::zero(),
			InvalidDistributionStringRepresentation,
			"Error: the Watt distribution cannot be "
			"constructed because of an invalid b_parameter "
			<< d_b_parameter );
  }

  // Set the restriction energy
  if( distribution.size() > 3 )
  {
    TEST_FOR_EXCEPTION( distribution[3].find_first_not_of( " 0123456789.e" ) <
			distribution[3].size(),
			InvalidDistributionStringRepresentation,
			"Error: the Watt distribution cannot be "
			"constructed because of an invalid restriction energy "
			<< distribution[3] );
    {
      double restriction_energy;

      std::istringstream iss( distribution[3] );
      Teuchos::extractDataFromISS( iss, restriction_energy );

      setQuantity( d_restriction_energy, restriction_energy );
    }

    TEST_FOR_EXCEPTION( IQT::isnaninf( d_restriction_energy ),
			InvalidDistributionStringRepresentation,
			"Error: the Watt distribution cannot be "
			"constructed because of an invalid restriction energy "
			<< d_restriction_energy );
  }

  // Set the multiplier
  if( distribution.size() > 4 )
  {
    TEST_FOR_EXCEPTION( distribution[4].find_first_not_of( " 0123456789.e" ) <
			distribution[4].size(),
			InvalidDistributionStringRepresentation,
			"Error: the Watt distribution cannot be "
			"constructed because of an invalid multiplier "
			<< distribution[4] );
    {
      double multiplier;

      std::istringstream iss( distribution[4] );
      Teuchos::extractDataFromISS( iss, multiplier );

      setQuantity( d_multiplier, multiplier );
    }

    TEST_FOR_EXCEPTION( DMQT::isnaninf( d_multiplier ),
			InvalidDistributionStringRepresentation,
			"Error: the Watt distribution cannot be "
			"constructed because of an invalid multiplier "
			<< getRawQuantity( d_multiplier ) );
  }

  // Calculate the normalization constant
  this->calculateNormalizationConstant();
}

// Method for testing if two objects are equivalent
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareWattDistribution<IndependentUnit,DependentUnit>::isEqual(
  const UnitAwareWattDistribution<IndependentUnit,DependentUnit>& other ) const
{
  return d_incident_energy == other.d_incident_energy &&
  d_a_parameter == other.d_a_parameter &&
  d_b_parameter == other.d_b_parameter &&
  d_restriction_energy == other.d_restriction_energy &&
  d_multiplier == other.d_multiplier;
}

} // end Utility namespace

#endif // end UTILITY_WATT_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_WattDistribution_def.hpp
//---------------------------------------------------------------------------//
