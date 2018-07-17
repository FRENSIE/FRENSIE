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
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_DesignByContract.hpp"

BOOST_SERIALIZATION_DISTRIBUTION2_EXPORT_IMPLEMENT( UnitAwareWattDistribution );

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
  // Verify that the shape parameters are valid
  this->verifyValidShapeParameters( d_incident_energy,
                                    d_a_parameter,
                                    d_b_parameter,
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
UnitAwareWattDistribution<IndependentUnit,DependentUnit>::UnitAwareWattDistribution(
  const UnitAwareWattDistribution<InputIndepUnit,InputDepUnit>& dist_instance )
  : d_incident_energy( dist_instance.d_incident_energy),
    d_a_parameter( dist_instance.d_a_parameter),
    d_b_parameter( dist_instance.d_b_parameter),
    d_restriction_energy( dist_instance.d_restriction_energy),
    d_multiplier( dist_instance.d_multiplier ),
    d_norm_constant()
{
  // Calculate the norm constant
  this->calculateNormalizationConstant();

  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
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
  if( indep_var_value < this->getLowerBoundOfIndepVar() )
    return DQT::zero();
  else if( indep_var_value > this->getUpperBoundOfIndepVar() )
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
  DistributionTraits::Counter trials = 0;

  return ThisType::sampleAndRecordTrials( incident_energy,
					  a_parameter,
					  b_parameter,
					  restriction_energy,
					  trials );
}

// Return a random sample and record the number of trials
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareWattDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareWattDistribution<IndependentUnit,DependentUnit>::sampleAndRecordTrials( DistributionTraits::Counter& trials ) const
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
  DistributionTraits::Counter& trials )
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
UnivariateDistributionType
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
  this->toStreamDistImpl( os,
                          std::make_pair( "incident energy", d_incident_energy ),
                          std::make_pair( "a parameter", d_a_parameter ),
                          std::make_pair( "b parameter", d_b_parameter ),
                          std::make_pair( "restriction energy", d_restriction_energy ),
                          std::make_pair( "multiplier", Utility::getRawQuantity( d_multiplier ) ) );
}

// Save the distribution to an archive
template<typename IndependentUnit, typename DependentUnit>
template<typename Archive>
void UnitAwareWattDistribution<IndependentUnit,DependentUnit>::save( Archive& ar, const unsigned version ) const
{
  // Save the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Save the local member data
  ar & BOOST_SERIALIZATION_NVP( d_incident_energy );
  ar & BOOST_SERIALIZATION_NVP( d_a_parameter );
  ar & BOOST_SERIALIZATION_NVP( d_b_parameter );
  ar & BOOST_SERIALIZATION_NVP( d_restriction_energy );
  ar & BOOST_SERIALIZATION_NVP( d_multiplier );
  ar & BOOST_SERIALIZATION_NVP( d_norm_constant );
}

// Load the distribution from an archive
template<typename IndependentUnit, typename DependentUnit>
template<typename Archive>
void UnitAwareWattDistribution<IndependentUnit,DependentUnit>::load( Archive& ar, const unsigned version )
{
  // Load the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Load the local member data
  ar & BOOST_SERIALIZATION_NVP( d_incident_energy );
  ar & BOOST_SERIALIZATION_NVP( d_a_parameter );
  ar & BOOST_SERIALIZATION_NVP( d_b_parameter );
  ar & BOOST_SERIALIZATION_NVP( d_restriction_energy );
  ar & BOOST_SERIALIZATION_NVP( d_multiplier );
  ar & BOOST_SERIALIZATION_NVP( d_norm_constant );
}

// Method for testing if two objects are equivalent
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareWattDistribution<IndependentUnit,DependentUnit>::operator==(
  const UnitAwareWattDistribution<IndependentUnit,DependentUnit>& other ) const
{
  return d_incident_energy == other.d_incident_energy &&
  d_a_parameter == other.d_a_parameter &&
  d_b_parameter == other.d_b_parameter &&
  d_restriction_energy == other.d_restriction_energy &&
  d_multiplier == other.d_multiplier;
}

// Method for testing if two objects are different
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareWattDistribution<IndependentUnit,DependentUnit>::operator!=(
  const UnitAwareWattDistribution<IndependentUnit,DependentUnit>& other ) const
{
  return d_incident_energy != other.d_incident_energy ||
  d_a_parameter != other.d_a_parameter ||
  d_b_parameter != other.d_b_parameter ||
  d_restriction_energy != other.d_restriction_energy ||
  d_multiplier != other.d_multiplier;
}

// Test if the dependent variable can be zero within the indep bounds
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareWattDistribution<IndependentUnit,DependentUnit>::canDepVarBeZeroInIndepBounds() const
{
  return true;
}

// Verify that the shape parameters are valid
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareWattDistribution<IndependentUnit,DependentUnit>::verifyValidShapeParameters(
                                           IndepQuantity& incident_energy,
                                           IndepQuantity& a_parameter,
                                           InverseIndepQuantity& b_parameter,
                                           IndepQuantity& restriction_energy,
                                           DistMultiplierQuantity& multiplier )
{
  TEST_FOR_EXCEPTION( IQT::isnaninf( incident_energy ),
                      Utility::BadUnivariateDistributionParameter,
                      "The watt distribution cannot be constructed "
                      "because the incident energy is invalid!" );

  TEST_FOR_EXCEPTION( incident_energy <= IQT::zero(),
                      Utility::BadUnivariateDistributionParameter,
                      "The watt distribution cannot be constructed "
                      "because the incident energy is invalid!" );

  TEST_FOR_EXCEPTION( IQT::isnaninf( a_parameter ),
                      Utility::BadUnivariateDistributionParameter,
                      "The watt distribution cannot be constructed "
                      "because the A parameter is invalid!" );

  TEST_FOR_EXCEPTION( a_parameter <= IQT::zero(),
                      Utility::BadUnivariateDistributionParameter,
                      "The watt distribution cannot be constructed "
                      "because the A parameter is invalid!" );
  
  TEST_FOR_EXCEPTION( IIQT::isnaninf( b_parameter ),
                      Utility::BadUnivariateDistributionParameter,
                      "The watt distribution cannot be constructed "
                      "because the B parameter is invalid!" );
  
  TEST_FOR_EXCEPTION( b_parameter <= IIQT::zero(),
                      Utility::BadUnivariateDistributionParameter,
                      "The watt distribution cannot be constructed "
                      "because the B parameter is invalid!" );
  
  TEST_FOR_EXCEPTION( IQT::isnaninf( restriction_energy ),
                      Utility::BadUnivariateDistributionParameter,
                      "The watt distribution cannot be constructed "
                      "because the restriction energy is invalid!" );

  TEST_FOR_EXCEPTION( incident_energy <= restriction_energy,
                      Utility::BadUnivariateDistributionParameter,
                      "The watt distribution cannot be constructed "
                      "because the incident energy ("
                      << Utility::toString(incident_energy) << ")"
                      " is not greater than the restriction energy ("
                      << Utility::toString(restriction_energy) << ")!" );

  TEST_FOR_EXCEPTION( DMQT::isnaninf( multiplier ),
                      Utility::BadUnivariateDistributionParameter,
                      "The watt distribution cannot be constructed "
                      "because the multiplier is invalid!" );

  TEST_FOR_EXCEPTION( multiplier == DMQT::zero(),
                      Utility::BadUnivariateDistributionParameter,
                      "The watt distribution cannot be constructed "
                      "because the multiplier is invalid!" );  
}

} // end Utility namespace

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareWattDistribution<void,void> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Utility, UnitAwareWattDistribution<void,void> );

#endif // end UTILITY_WATT_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_WattDistribution_def.hpp
//---------------------------------------------------------------------------//
