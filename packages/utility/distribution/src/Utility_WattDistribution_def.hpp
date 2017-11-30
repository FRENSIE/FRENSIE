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
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_ContractException.hpp"

BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT( UnitAwareWattDistribution );

namespace Utility{

// Initialize static member data
template<typename IndependentUnit, typename DependentUnit>
const std::string UnitAwareWattDistribution<IndependentUnit,DependentUnit>::s_incident_energy_value_key( "incident energy" );
  
template<typename IndependentUnit, typename DependentUnit>
const std::string UnitAwareWattDistribution<IndependentUnit,DependentUnit>::s_incident_energy_value_min_match_string( "energy" );

template<typename IndependentUnit, typename DependentUnit>
const std::string UnitAwareWattDistribution<IndependentUnit,DependentUnit>::s_a_parameter_value_key( "a parameter" );
  
template<typename IndependentUnit, typename DependentUnit>
const std::string UnitAwareWattDistribution<IndependentUnit,DependentUnit>::s_a_parameter_value_min_match_string( "a" );

template<typename IndependentUnit, typename DependentUnit>
const std::string UnitAwareWattDistribution<IndependentUnit,DependentUnit>::s_b_parameter_value_key( "b parameter" );
  
template<typename IndependentUnit, typename DependentUnit>
const std::string UnitAwareWattDistribution<IndependentUnit,DependentUnit>::s_b_parameter_value_min_match_string( "b" );

template<typename IndependentUnit, typename DependentUnit>
const std::string UnitAwareWattDistribution<IndependentUnit,DependentUnit>::s_restriction_energy_value_key( "restriction energy" );

template<typename IndependentUnit, typename DependentUnit>
const std::string UnitAwareWattDistribution<IndependentUnit,DependentUnit>::s_restriction_energy_value_min_match_string( "restrict" );

template<typename IndependentUnit, typename DependentUnit>
const std::string UnitAwareWattDistribution<IndependentUnit,DependentUnit>::s_multiplier_value_key( "multiplier" );

template<typename IndependentUnit, typename DependentUnit>
const std::string UnitAwareWattDistribution<IndependentUnit,DependentUnit>::s_multiplier_value_min_match_string( "mult" );
  
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

  BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
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

  BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
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

  BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
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
OneDDistributionType
UnitAwareWattDistribution<IndependentUnit,DependentUnit>::getDistributionType() const
{
  return ThisType::distribution_type;
}

// Return the distribution type name
template<typename IndependentUnit, typename DependentUnit>
std::string UnitAwareWattDistribution<IndependentUnit,DependentUnit>::typeName(
                                                const bool verbose_name,
                                                const bool use_template_params,
                                                const std::string& delim )
{
  return BaseType::typeNameImpl( "Watt",
                                 verbose_name,
                                 use_template_params,
                                 delim );
}

// Return the distribution type name
template<typename IndependentUnit, typename DependentUnit>
std::string UnitAwareWattDistribution<IndependentUnit,DependentUnit>::getTypeNameImpl(
                                                const bool verbose_name ) const
{
  return this->typeName( verbose_name, false, " " );
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
  this->toStreamImpl( os,
                      Utility::getRawQuantity( d_incident_energy ),
                      Utility::getRawQuantity( d_a_parameter ),
                      Utility::getRawQuantity( d_b_parameter ),
                      Utility::getRawQuantity( d_restriction_energy ),
                      Utility::getRawQuantity( d_multiplier ) );
}

// Method for initializing the object from an input stream
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareWattDistribution<IndependentUnit,DependentUnit>::fromStreamImpl(
                                               VariantList& distribution_data )
{
  // Set the incident energy
  if( !distribution_data.empty() )
  {
    this->extractValue( distribution_data.front(),
                        d_incident_energy,
                        this->getTypeName( true, true ) );

    distribution_data.pop_front();
  }
  else
    d_incident_energy = ThisType::getDefaultIncidentEnergy<IndepQuantity>();

  // Set the a parameter
  if( !distribution_data.empty() )
  {
    this->extractValue( distribution_data.front(),
                        d_a_parameter,
                        this->getTypeName( true, true ) );

    distribution_data.pop_front();
  }
  else
    d_a_parameter = ThisType::getDefaultAParameter<IndepQuantity>();

  // Set the b parameter
  if( !distribution_data.empty() )
  {
    this->extractValue( distribution_data.front(),
                        d_b_parameter,
                        this->getTypeName( true, true ) );

    distribution_data.pop_front();
  }
  else
    d_b_parameter = ThisType::getDefaultBParameter<InverseIndepQuantity>();

  // Set the restriction energy
  if( !distribution_data.empty() )
  {
    this->extractValue( distribution_data.front(),
                        d_restriction_energy,
                        this->getTypeName( true, true ) );
    
    distribution_data.pop_front();
  }
  else
    d_restriction_energy = ThisType::getDefaultRestrictionEnergy<IndepQuantity>();

  // Set the constant multiplier
  if( !distribution_data.empty() )
  {
    this->extractValue( distribution_data.front(),
                        d_multiplier,
                        this->getTypeName( true, true ) );
    
    distribution_data.pop_front();
  }
  else
    Utility::setQuantity( d_multiplier, ThisType::getDefaultConstantMultiplier() );

  // Verify that the shape parameters are valid
  this->verifyValidShapeParameters( d_incident_energy,
                                    d_a_parameter,
                                    d_b_parameter,
                                    d_restriction_energy,
                                    d_multiplier );

  // Calculate the normalization constant
  this->calculateNormalizationConstant();
}

// Method for converting the type to a property tree
template<typename IndependentUnit, typename DependentUnit>
Utility::PropertyTree UnitAwareWattDistribution<IndependentUnit,DependentUnit>::toPropertyTree( const bool inline_data ) const
{
  if( inline_data )
    return this->toInlinedPropertyTreeImpl();
  else
  {
    return this->toPropertyTreeImpl(
       std::tie(s_incident_energy_value_key, Utility::getRawQuantity(d_incident_energy)),
       std::tie(s_a_parameter_value_key, Utility::getRawQuantity(d_a_parameter)),
       std::tie(s_b_parameter_value_key, Utility::getRawQuantity(d_b_parameter)),
       std::tie(s_restriction_energy_value_key, Utility::getRawQuantity(d_restriction_energy)),
       std::tie(s_multiplier_value_key, Utility::getRawQuantity(d_multiplier)) );
  }
}

// Method for initializing the object from a property tree
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareWattDistribution<IndependentUnit,DependentUnit>::fromPropertyTree(
                                    const Utility::PropertyTree& node,
                                    std::vector<std::string>& unused_children )
{
  // Initialize from inline data
  if( node.size() == 0 )
    this->fromInlinedPropertyTreeImpl( node );
    
  // Initialize from child nodes
  else
  {
    // Initialize the member data to default values
    d_incident_energy =
      ThisType::getDefaultIncidentEnergy<IndepQuantity>();
    d_a_parameter =
      ThisType::getDefaultAParameter<IndepQuantity>();
    d_b_parameter =
      ThisType::getDefaultBParameter<InverseIndepQuantity>();
    d_restriction_energy =
      ThisType::getDefaultRestrictionEnergy<IndepQuantity>();
    Utility::setQuantity( d_multiplier,
                          ThisType::getDefaultConstantMultiplier() );

    std::string type_name = this->getTypeName( true, true );

    // Create the data extractor map
    typename BaseType::DataExtractorMap data_extractors;    

    data_extractors.insert(
     std::make_pair( s_incident_energy_value_key,
      std::make_tuple( s_incident_energy_value_min_match_string, BaseType::OPTIONAL_DATA,
       std::bind<void>(&BaseType::template extractValueFromNode<IndepQuantity>,
                       std::placeholders::_1,
                       std::ref(d_incident_energy),
                       std::cref(type_name)) )));
    
    data_extractors.insert(
     std::make_pair( s_a_parameter_value_key,
      std::make_tuple( s_a_parameter_value_min_match_string, BaseType::OPTIONAL_DATA,
       std::bind<void>(&BaseType::template extractValueFromNode<IndepQuantity>,
                       std::placeholders::_1,
                       std::ref(d_a_parameter),
                       std::cref(type_name)) )));

    data_extractors.insert(
     std::make_pair( s_b_parameter_value_key,
      std::make_tuple( s_b_parameter_value_min_match_string, BaseType::OPTIONAL_DATA,
       std::bind<void>(&BaseType::template extractValueFromNode<InverseIndepQuantity>,
                       std::placeholders::_1,
                       std::ref(d_b_parameter),
                       std::cref(type_name)) )));
    
    data_extractors.insert(
     std::make_pair( s_restriction_energy_value_key,
      std::make_tuple( s_restriction_energy_value_min_match_string, BaseType::OPTIONAL_DATA,
       std::bind<void>(&BaseType::template extractValueFromNode<IndepQuantity>,
                       std::placeholders::_1,
                       std::ref(d_restriction_energy),
                       std::cref(type_name)) )));

    data_extractors.insert(
     std::make_pair( s_multiplier_value_key,
      std::make_tuple( s_multiplier_value_min_match_string, BaseType::OPTIONAL_DATA,
       std::bind<void>(&BaseType::template extractValueFromNode<DistMultiplierQuantity>,
                       std::placeholders::_1,
                       std::ref(d_multiplier),
                       std::cref(type_name)) )));

    this->fromPropertyTreeImpl( node, unused_children, data_extractors );

    
    // Verify that the shape parameters are valid
    try{
      this->verifyValidShapeParameters( d_incident_energy,
                                        d_a_parameter,
                                        d_b_parameter,
                                        d_restriction_energy,
                                        d_multiplier );
    }
    EXCEPTION_CATCH_RETHROW_AS( Utility::StringConversionException,
                                Utility::PropertyTreeConversionException,
                                "Invalid shape parameter detected!" );

    // Calculate the normalization constant
    this->calculateNormalizationConstant();
  }
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
                      Utility::StringConversionException,
                      "The watt distribution cannot be constructed "
                      "because the incident energy is invalid!" );

  TEST_FOR_EXCEPTION( incident_energy <= IQT::zero(),
                      Utility::StringConversionException,
                      "The watt distribution cannot be constructed "
                      "because the incident energy is invalid!" );

  TEST_FOR_EXCEPTION( IQT::isnaninf( a_parameter ),
                      Utility::StringConversionException,
                      "The watt distribution cannot be constructed "
                      "because the A parameter is invalid!" );

  TEST_FOR_EXCEPTION( a_parameter <= IQT::zero(),
                      Utility::StringConversionException,
                      "The watt distribution cannot be constructed "
                      "because the A parameter is invalid!" );
  
  TEST_FOR_EXCEPTION( IIQT::isnaninf( b_parameter ),
                      Utility::StringConversionException,
                      "The watt distribution cannot be constructed "
                      "because the B parameter is invalid!" );
  
  TEST_FOR_EXCEPTION( b_parameter <= IIQT::zero(),
                      Utility::StringConversionException,
                      "The watt distribution cannot be constructed "
                      "because the B parameter is invalid!" );
  
  TEST_FOR_EXCEPTION( IQT::isnaninf( restriction_energy ),
                      Utility::StringConversionException,
                      "The watt distribution cannot be constructed "
                      "because the restriction energy is invalid!" );

  TEST_FOR_EXCEPTION( incident_energy <= restriction_energy,
                      Utility::StringConversionException,
                      "The watt distribution cannot be constructed "
                      "because the incident energy ("
                      << Utility::toString(incident_energy) << ")"
                      " is not greater than the restriction energy ("
                      << Utility::toString(restriction_energy) << ")!" );

  TEST_FOR_EXCEPTION( DMQT::isnaninf( multiplier ),
                      Utility::StringConversionException,
                      "The watt distribution cannot be constructed "
                      "because the multiplier is invalid!" );

  TEST_FOR_EXCEPTION( multiplier == DMQT::zero(),
                      Utility::StringConversionException,
                      "The watt distribution cannot be constructed "
                      "because the multiplier is invalid!" );  
}

} // end Utility namespace

EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareWattDistribution<void,void> );

#endif // end UTILITY_WATT_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_WattDistribution_def.hpp
//---------------------------------------------------------------------------//
