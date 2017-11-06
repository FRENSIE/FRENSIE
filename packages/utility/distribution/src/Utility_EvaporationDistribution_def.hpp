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
#include "Utility_ContractException.hpp"

BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT( UnitAwareEvaporationDistribution );

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

  BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_FINALIZE( UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit> );
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

  BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_FINALIZE( UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit> );
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

  BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_FINALIZE( UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit> );
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

// Return the distribution type name
template<typename IndependentUnit, typename DependentUnit>
std::string UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::getDistributionTypeName(
                                                   const bool verbose_name,
                                                   const bool lowercase ) const
{
  std::string name = "Evaporation";

  if( verbose_name )
    name += " Distribution";

  if( lowercase )
    boost::algorithm::to_lower( name );

  return name;
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
  this->toStreamImpl( os,
                      Utility::getRawQuantity( d_incident_energy ),
                      Utility::getRawQuantity( d_nuclear_temperature ),
                      Utility::getRawQuantity( d_restriction_energy ),
                      Utility::getRawQuantity( d_multiplier ) );
}

// Method for initializing the object from an input stream
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::fromStream( std::istream& is, const std::string& )
{
  VariantList distribution_data;

  this->fromStreamImpl( is, distribution_data );
  
  // Extract the distribution shape parameters
  this->extractShapeParameters( Utility::Variant(distribution_data),
                                d_incident_energy,
                                d_nuclear_temperature,
                                d_restriction_energy,
                                d_multiplier );

  // Verify that the shape parameters are valid
  this->verifyValidShapeParameters( d_incident_energy,
                                    d_nuclear_temperature,
                                    d_restriction_energy,
                                    d_multiplier );

  // Calculate the normalization constant
  this->calculateNormalizationConstant();
}

// Method for converting the type to a property tree
template<typename IndependentUnit, typename DependentUnit>
Utility::PropertyTree UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::toPropertyTree( const bool inline_data ) const
{
  Utility::PropertyTree ptree;

  if( inline_data )
    ptree.put_value( *this );
  else
  {
    // this->addTypeNameToPropertyTree( ptree );

    // ptree.put( "indicent energy", Utility::getRawQuantity(d_incident_energy) );
    // ptree.put( "nuclear temperature", Utility::getRawQuantity(d_nuclear_temperature) );
    // ptree.put( "restriction energy", Utility::getRawQuantity(d_restriction_energy) );
    // ptree.put( "multiplier", Utility::getRawQuantity(d_multiplier) );
  }

  return ptree;
}

// Method for initializing the object from a property tree
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::fromPropertyTree(
                                    const Utility::PropertyTree& node,
                                    std::vector<std::string>& unused_children )
{
  // Initialize from inline data
  if( node.size() == 0 )
  {
    std::istringstream iss( node.data().toString() );

    try{
      this->fromStream( iss );
    }
    EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                Utility::PropertyTreeConversionException,
                                "Could not create the evaporation "
                                "distribution!" );
  }
  // Initialize from child nodes
  else
  {
    Utility::PropertyTree::const_iterator node_it, node_end;
    node_it = node.begin();
    node_end = node.end();

    bool type_verified = false;
    bool incident_energy_set = false;
    bool nuclear_temp_set = false;
    bool restriction_energy_set = false;
    bool multiplier_set = false;

    // Initialize the shape parameters
    VariantVector shape_parameters;
    shape_parameters[0] = Utility::Variant( ThisType::getDefaultIncidentEnergy<double>() );
    shape_parameters[1] = Utility::Variant( ThisType::getDefaultNuclearTemperature<double>() );
    shape_parameters[2] = Utility::Variant( ThisType::getDefaultRestrictionEnergy<double>() );
    shape_parameters[3] = Utility::Variant( ThisType::getDefaultConstantMultiplier() );

    // while( node_it != node_end )
    // {
    //   if( !type_verified )
    //     this->attemptToVerifyDistributionType( node_it, type_verified );
    //   else
    //   {
    //     std::string child_node_key =
    //       boost::algorithm::to_lower_copy( node_it->first );

    //     // Extract the incident energy
    //     if( child_node_key.find( "incident" ) < child_node_key.size() )
    //     {
    //       if( !incident_energy_set )
    //       {
    //         shape_parameters[0] = node_it->second.data();
    //         incident_energy_set = true;
    //       }
    //       else
    //         unused_children.push_back( node_it->first );
    //     }

    //     // Extract the nuclear temperature
    //     else if( child_node_key.find( "nuclear" ) < child_node_key.size() )
    //     {
    //       if( !nuclear_temp_set )
    //       {
    //         shape_parameters[1] = node_it->second.data();
    //         nuclear_temp_set = true;
    //       }
    //       else
    //         unused_children.push_back( node_it->first );
    //     }

    //     // Extract the restriction energy
    //     else if( child_node_key.find( "restrict" ) < child_node_key.size() )
    //     {
    //       if( !restriction_energy_set )
    //       {
    //         shape_parameters[2] = node_it->second.data();
    //         restriction_energy_set = true;
    //       }
    //       else
    //         unused_children.push_back( node_it->first );
    //     }

    //     // Extract the multiplier
    //     else if( child_node_key.find( "mult" ) < child_node_key.size() )
    //     {
    //       if( !multiplier_set )
    //       {
    //         shape_parameters[3] = node_it->second.data();
    //         multiplier_set = true;
    //       }
    //       else
    //         unused_children.push_back( node_it->first );
    //     }

    //     // This child node is unused (and is not a comment)
    //     else if( child_node_key.find( PTREE_COMMENT_NODE_KEY ) >=
    //              child_node_key.size() )
    //     {
    //       unused_children.push_back( node_it->first );
    //     }
    //   }
    //   ++node_it;
    // }

    // // Check that the type has been verified
    // this->hasDistributionTypeBeenVerified( type_verified );

    // // Extract the shape parameters
    // this->extractShapeParameters( Utility::Variant( shape_parameters ),
    //                               d_incident_energy,
    //                               d_nuclear_temperature,
    //                               d_restriction_energy,
    //                               d_multiplier );

    // // Verify that the shape parameters are valid
    // this->verifyValidShapeParameters( d_incident_energy,
    //                                   d_nuclear_temperature,
    //                                   d_restriction_energy,
    //                                   d_multiplier );

    // // Calculate the normalization constant
    // this->calculateNormalizationConstant();
  }
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

// Set the shape parameters
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::extractShapeParameters(
                                  const Utility::Variant& shape_parameter_data,
                                  IndepQuantity& incident_energy,
                                  IndepQuantity& nuclear_temp,
                                  IndepQuantity& restriction_energy,
                                  DistMultiplierQuantity& multiplier )
{
  std::vector<double> shape_parameters;

  try{
    shape_parameters =
      Utility::variant_cast<std::vector<double> >( shape_parameter_data );
  }
  EXCEPTION_CATCH_RETHROW( Utility::StringConversionException,
                           "The evaporation distribution cannot be "
                           "constructed because the shape parameters are not "
                           "valid!" );

  ThisType::extractShapeParameters( shape_parameters,
                                    incident_energy,
                                    nuclear_temp,
                                    restriction_energy,
                                    multiplier );
}

// Set the shape parameters
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::extractShapeParameters(
                               const std::vector<double>& shape_parameter_data,
                               IndepQuantity& incident_energy,
                               IndepQuantity& nuclear_temp,
                               IndepQuantity& restriction_energy,
                               DistMultiplierQuantity& multiplier )
{
  TEST_FOR_EXCEPTION( shape_parameter_data.size() > 4,
                      Utility::StringConversionException,
                     "The evaporation distribution cannot be constructed "
                     "because the representation is not valid"
                     "(there are only 4 shape parameters that can be "
                      "specified)!" );

  // Set the incident energy
  if( shape_parameter_data.size() > 0 )
    Utility::setQuantity( incident_energy, shape_parameter_data[0] );
  else
    incident_energy = ThisType::getDefaultIncidentEnergy<IndepQuantity>();

  // Set the nuclear_temperature
  if( shape_parameter_data.size() > 1 )
    Utility::setQuantity( nuclear_temp, shape_parameter_data[1] );
  else
    nuclear_temp = ThisType::getDefaultNuclearTemperature<IndepQuantity>();

  // Set the restriction energy
  if( shape_parameter_data.size() > 2 )
    Utility::setQuantity( restriction_energy, shape_parameter_data[3] );
  else
    restriction_energy = ThisType::getDefaultRestrictionEnergy<IndepQuantity>();

  // Set the constant multiplier
  if( shape_parameter_data.size() > 3 )
    Utility::setQuantity( multiplier, shape_parameter_data[4] );
  else
    multiplier = ThisType::getDefaultConstantMultiplier();
}

// Verify that the shape parameters are valid
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareEvaporationDistribution<IndependentUnit,DependentUnit>::verifyValidShapeParameters(
                                           IndepQuantity& incident_energy,
                                           IndepQuantity& nuclear_temp,
                                           IndepQuantity& restriction_energy,
                                           DistMultiplierQuantity& multiplier )
{
  TEST_FOR_EXCEPTION( IQT::isnaninf( incident_energy ),
                      Utility::StringConversionException,
                      "The evaporation distribution cannot be constructed "
                      "because the incident energy is invalid!" );

  TEST_FOR_EXCEPTION( incident_energy < IQT::zero(),
                      Utility::StringConversionException,
                      "The evaporation distribution cannot be constructed "
                      "because the incident energy is invalid!" );

  TEST_FOR_EXCEPTION( IQT::isnaninf( nuclear_temp ),
                      Utility::StringConversionException,
                      "The evaporation distribution cannot be constructed "
                      "because the nuclear temperature is invalid!" );

  TEST_FOR_EXCEPTION( nuclear_temp <= IQT::zero(),
		      Utility::StringConversionException,
                      "The evaporation distribution cannot be constructed "
                      "because the nuclear temperature is invalid!" );
  
  TEST_FOR_EXCEPTION( IQT::isnaninf( restriction_energy ),
                      Utility::StringConversionException,
                      "The evaporation distribution cannot be constructed "
                      "because the restriction energy is invalid!" );

  TEST_FOR_EXCEPTION( DMQT::isnaninf( multiplier ),
                      Utility::StringConversionException,
                      "The evaporation distribution cannot be constructed "
                      "because the multiplier is invalid!" );
}

} // end Utility namespace

EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareEvaporationDistribution<void,void> );

#endif // end UTILITY_EVAPORATION_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_EvaporationDistribution_def.hpp
//---------------------------------------------------------------------------//
