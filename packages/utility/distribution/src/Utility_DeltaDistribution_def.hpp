//---------------------------------------------------------------------------//
//!
//! \file   Utility_DeltaDistribution_def.hpp
//! \author Alex Robinson
//! \brief  Delta distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_DELTA_DISTRIBUTION_DEF_HPP
#define UTILITY_DELTA_DISTRIBUTION_DEF_HPP

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_ContractException.hpp"

BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT( UnitAwareDeltaDistribution );

namespace Utility{

// Initialize static member data
template<typename IndependentUnit, typename DependentUnit>
const std::string UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::s_location_value_key( "location" );

template<typename IndependentUnit, typename DependentUnit>
const std::string UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::s_location_value_min_match_string( "loc" );

template<typename IndependentUnit, typename DependentUnit>
const std::string UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::s_multiplier_value_key( "multiplier" );

template<typename IndependentUnit, typename DependentUnit>
const std::string UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::s_multiplier_value_min_match_string( "mult" );

// Constructor
template<typename IndependentUnit, typename DependentUnit>
template<typename InputIndepQuantity, typename InputDepQuantity>
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::UnitAwareDeltaDistribution(
                                            const InputIndepQuantity location,
					    const InputDepQuantity multiplier )
  : d_location( location ),
    d_multiplier( multiplier )
{
  // Make sure that the point is valid
  testPrecondition( !QuantityTraits<InputIndepQuantity>::isnaninf( location ));
  // Make sure the multiplier is valid
  testPrecondition( !QuantityTraits<InputDepQuantity>::isnaninf( multiplier ));
  testPrecondition( multiplier != QuantityTraits<InputDepQuantity>::zero() );

  BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Copy constructor
/*! \details Just like boost::units::quantity objects, the unit-aware
 * distribution can be explicitly cast to a distribution with compatible
 * units. If the units are not compatible, this function will not compile. Note
 * that this allows distributions to be scaled safely (unit conversions
 * are completely taken care of by boost::units)!
 * Note: The Dummy template parameter is used to keep the Python interfaces
 *       generated by SWIG clean.
 */
template<typename IndependentUnit, typename DependentUnit>
template<typename InputIndepUnit, typename InputDepUnit, typename Dummy>
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::UnitAwareDeltaDistribution(
 const UnitAwareDeltaDistribution<InputIndepUnit,InputDepUnit>& dist_instance )
  : d_location( dist_instance.d_location ),
    d_multiplier( dist_instance.d_multiplier )
{
  remember( typedef QuantityTraits<typename UnitAwareDeltaDistribution<InputIndepUnit,InputDepUnit>::IndepQuantity> InputIQT );
  remember( typedef QuantityTraits<typename UnitAwareDeltaDistribution<InputIndepUnit,InputDepUnit>::DepQuantity> InputDQT );
  // Make sure that the point is valid
  testPrecondition( !InputIQT::isnaninf( dist_instance.d_location ) );
  // Make sure that the multiplier is valid
  testPrecondition( !InputDQT::isnaninf( dist_instance.d_multiplier ) );
  testPrecondition( dist_instance.d_multiplier != InputDQT::zero() );

  BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Copy constructor (copying from unitless distribution only)
template<typename IndependentUnit, typename DependentUnit>
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::UnitAwareDeltaDistribution(
const UnitAwareDeltaDistribution<void,void>& unitless_dist_instance, int )
  : d_location( IQT::initializeQuantity( unitless_dist_instance.d_location ) ),
    d_multiplier( DQT::initializeQuantity( unitless_dist_instance.d_multiplier ) )
{
  // Make sure that the point is valid
  testPrecondition( !QT::isnaninf( unitless_dist_instance.d_location ) );
  // Make sure that the multiplier is valid
  testPrecondition( !QT::isnaninf( unitless_dist_instance.d_multiplier ) );
  testPrecondition( unitless_dist_instance.d_multiplier != 0.0 );

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
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit> UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::fromUnitlessDistribution(
	   const UnitAwareDeltaDistribution<void,void>& unitless_distribution )
{
  return ThisType( unitless_distribution, 0 );
}

// Assignment operator
template<typename IndependentUnit, typename DependentUnit>
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>&
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::operator=(
 const UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>& dist_instance )
{
  if( this != &dist_instance )
  {
    d_location = dist_instance.d_location;

    d_multiplier = dist_instance.d_multiplier;
  }

  return *this;
}

// Evaluate the distribution
/*! \details The delta distribution is a continuous distribution
 * that can evaluate to one of two values: 0.0 and infinity. It is more
 * useful (and safer) to simply return 0.0 and a (the multiplier).
 */
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::DepQuantity
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::evaluate(
   const typename UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  if( indep_var_value == d_location )
    return d_multiplier;
  else
    return DQT::zero();
}

// Evaluate the PDF
/*! \details The delta distribution is a continuous distribution
 * that can evaluate to one of two values: 0.0 and infinity. It is more
 * useful (and safer) to simply return 0.0 and 1.0.
 */
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::evaluatePDF(
 const typename UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  if( indep_var_value == d_location )
    return QuantityTraits<InverseIndepQuantity>::one();
  else
    return QuantityTraits<InverseIndepQuantity>::zero();
}

// Evaluate the CDF
template<typename IndependentUnit, typename DependentUnit>
double UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::evaluateCDF(
  const typename UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  if( indep_var_value < d_location )
    return 0.0;
  else
    return 1.0;
}

// Return a random sample from the distribution
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::sample() const
{
  return d_location;
}

// Return a random sample from the corresponding CDF and record the number of trials
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::sampleAndRecordTrials( DistributionTraits::Counter& trials ) const
{
  ++trials;

  return d_location;
}

// Return a random sample from the distribution and the sampled index
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::sampleAndRecordBinIndex(
					    unsigned& sampled_bin_index ) const
{
  sampled_bin_index = 0;

  return d_location;
}

// Return a random sample from the distribution at the given CDF value
/*! \details The random number will be ignored since only a single value can
 * every be returned
 */
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::sampleWithRandomNumber(
					     const double random_number ) const
{
  return d_location;
}

// Return a random sample from the distribution in a subrange
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::sampleInSubrange(
 const typename UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::IndepQuantity max_indep_var ) const
{
  // Make sure the max independent variable is valid
  testPrecondition( max_indep_var >= d_location );

  return d_location;
}

// Return a random sample from the distribution at the given CDF value in a subrange
/*! \details The random number will be ignored since only a single value can
 * ever be returned
 */
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::sampleWithRandomNumberInSubrange(
 const double random_number,
 const typename UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::IndepQuantity max_indep_var ) const
{
  // Make sure the max independent variable is valid
  testPrecondition( max_indep_var >= d_location );

  return d_location;
}

// Return the maximum point at which the distribution is non-zero
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::getUpperBoundOfIndepVar() const
{
  return d_location;
}

// Return the minimum point at which the distribution is non-zero
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::getLowerBoundOfIndepVar() const
{
  return d_location;
}

// Return the distribution type
template<typename IndependentUnit, typename DependentUnit>
OneDDistributionType UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::getDistributionType() const
{
  return ThisType::distribution_type;
}

// Return the distribution type name
template<typename IndependentUnit, typename DependentUnit>
std::string UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::typeName(
                                                const bool verbose_name,
                                                const bool use_template_params,
                                                const std::string& delim )
{
  return BaseType::typeNameImpl( "Delta",
                                 verbose_name,
                                 use_template_params,
                                 delim );
}

// Return the distribution type name
template<typename IndependentUnit, typename DependentUnit>
std::string UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::getDistributionTypeName(
                                                   const bool verbose_name,
                                                   const bool lowercase ) const
{
  std::string name = this->typeName( verbose_name, false, " " );

  if( lowercase )
    boost::algorithm::to_lower( name );

  return name;
}

// Test if the distribution is continuous
/*! \details Though the delta distribution is technically continuous
 * because it is only non-zero at the specified point it will be treated as
 * a discrete distribution.
 */
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::isContinuous() const
{
  return false;
}

// Method for placing the object in an output stream
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::toStream( std::ostream& os ) const
{
  this->toStreamImpl( os,
                      Utility::getRawQuantity( d_location ),
                      Utility::getRawQuantity( d_multiplier ) );
}

// Method for initializing the object from an input stream
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::fromStream(
                                                           std::istream& is,
                                                           const std::string& )
{
  VariantList distribution_data;

  this->fromStreamImpl( is, distribution_data );

  // Extract the location value
  if( !distribution_data.empty() )
  {
    this->extractValue( distribution_data.front(),
                        d_location,
                        this->getDistributionTypeName( true, true ) );

    distribution_data.pop_front();
  }
  else
    d_location = ThisType::getDefaultLocation<IndepQuantity>();

  // Extract the multiplier value
  if( !distribution_data.empty() )
  {
    this->extractValue( distribution_data.front(),
                        d_multiplier,
                        this->getDistributionTypeName( true, true ) );
    
    distribution_data.pop_front();
  }
  else
    d_multiplier = ThisType::getDefaultMultiplier<DepQuantity>();

  // Verify that shape parameters are valid
  this->verifyValidShapeParameters( d_location, d_multiplier );

  // Check if there is any superfluous data
  this->checkForUnusedStreamData( distribution_data );
}

// Method for placing the object in the desired property tree node
template<typename IndependentUnit, typename DependentUnit>
Utility::PropertyTree UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::toPropertyTree(
                                                 const bool inline_data ) const
{
  if( inline_data )
    return this->toInlinedPropertyTreeImpl();
  else
  {
    return this->toPropertyTreeImpl(
     std::tie(s_location_value_key, Utility::getRawQuantity(d_location)),
     std::tie(s_multiplier_value_key, Utility::getRawQuantity(d_multiplier)) );
  }
}

// Method for initializing the object from a property tree
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::fromPropertyTree(
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
    d_location = ThisType::getDefaultLocation<IndepQuantity>();
    d_multiplier = ThisType::getDefaultMultiplier<DepQuantity>();

    std::string type_name = this->getDistributionTypeName( true, true );

    // Create the data extractor map
    typename BaseType::DataExtractorMap data_extractors;

    data_extractors.insert(
     std::make_pair( s_location_value_key,
      std::make_tuple( s_location_value_min_match_string, BaseType::OPTIONAL_DATA,
                       std::bind<void>( &BaseType::template extractValueFromNode<IndepQuantity>,
                                        std::placeholders::_1,
                                        std::ref(d_location),
                                        std::cref(type_name)) )));
    data_extractors.insert(
     std::make_pair( s_multiplier_value_key,
      std::make_tuple( s_multiplier_value_min_match_string, BaseType::OPTIONAL_DATA,
                       std::bind<void>( &BaseType::template extractValueFromNode<DepQuantity>,
                                        std::placeholders::_1,
                                        std::ref(d_multiplier),
                                        std::cref(type_name)) )));

    this->fromPropertyTreeImpl( node, unused_children, data_extractors );

    // Verify that shape parameters are valid
    try{
      this->verifyValidShapeParameters( d_location, d_multiplier );
    }
    EXCEPTION_CATCH_RETHROW_AS( Utility::StringConversionException,
                                Utility::PropertyTreeConversionException,
                                "Invalid shape parameter detected!" );
  }
}

// Save the distribution to an archive
template<typename IndependentUnit, typename DependentUnit>
template<typename Archive>
void UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::save( Archive& ar, const unsigned version ) const
{
  // Save the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Save the local member data
  ar & BOOST_SERIALIZATION_NVP( d_location );
  ar & BOOST_SERIALIZATION_NVP( d_multiplier );
}

// Load the distribution from an archive
template<typename IndependentUnit, typename DependentUnit>
template<typename Archive>
void UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::load( Archive& ar, const unsigned version )
{
  // Load the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Load the local member data
  ar & BOOST_SERIALIZATION_NVP( d_location );
  ar & BOOST_SERIALIZATION_NVP( d_multiplier );
}

// Verify that the shape parameters are valid
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::verifyValidShapeParameters(
                                                const IndepQuantity& location,
                                                const DepQuantity& multiplier )
{
  TEST_FOR_EXCEPTION( IQT::isnaninf( location ),
		      Utility::StringConversionException,
		      "The delta distribution cannot be constructed "
		      "because of an invalid location!" );
  
  TEST_FOR_EXCEPTION( DQT::isnaninf( multiplier ),
                      Utility::StringConversionException,
                      "The delta distribution cannot be constructed "
                      "because of an invalid multiplier!" );

  TEST_FOR_EXCEPTION( multiplier == DQT::zero(),
                      Utility::StringConversionException,
                      "The delta distribution cannot be constructed "
                      "because of an invalid multiplier!" );
}

// Equality comparison operator
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::operator==(
 const UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>& other ) const
{
  return d_location == other.d_location &&
    d_multiplier == other.d_multiplier;
}

// Inequality comparison operator
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::operator!=(
 const UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>& other ) const
{
  return d_location != other.d_location ||
    d_multiplier != other.d_multiplier;
}

// Test if the dependent variable can be zero within the indep bounds
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::canDepVarBeZeroInIndepBounds() const
{
  return false;
}

// Explicit instantiation (extern declaration)
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareDeltaDistribution<void,void> );

} // end Utility namespace

#endif // end UTILITY_DELTA_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utiliyt_DeltaDistribution_def.hpp
//---------------------------------------------------------------------------//
