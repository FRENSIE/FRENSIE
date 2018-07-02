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
#include "Utility_DesignByContract.hpp"

BOOST_SERIALIZATION_DISTRIBUTION2_EXPORT_IMPLEMENT( UnitAwareDeltaDistribution );

namespace Utility{

// Constructor
template<typename IndependentUnit, typename DependentUnit>
template<typename InputIndepQuantity, typename InputDepQuantity>
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::UnitAwareDeltaDistribution(
                                            const InputIndepQuantity location,
					    const InputDepQuantity multiplier )
  : d_location( location ),
    d_multiplier( multiplier )
{
  this->verifyValidShapeParameters( d_location, d_multiplier );

  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
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
  this->verifyValidShapeParameters( d_location, d_multiplier );

  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Copy constructor (copying from unitless distribution only)
template<typename IndependentUnit, typename DependentUnit>
UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::UnitAwareDeltaDistribution(
const UnitAwareDeltaDistribution<void,void>& unitless_dist_instance, int )
  : d_location( IQT::initializeQuantity( unitless_dist_instance.d_location ) ),
    d_multiplier( DQT::initializeQuantity( unitless_dist_instance.d_multiplier ) )
{
  this->verifyValidShapeParameters( d_location, d_multiplier );

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
					      size_t& sampled_bin_index ) const
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
UnivariateDistributionType UnitAwareDeltaDistribution<IndependentUnit,DependentUnit>::getDistributionType() const
{
  return ThisType::distribution_type;
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
  this->toStreamDistImpl( os,
                          std::make_pair( "location", d_location ),
                          std::make_pair( "multiplier", d_multiplier ) );
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
		      Utility::BadUnivariateDistributionParameter,
		      "The delta distribution cannot be constructed "
		      "because of an invalid location!" );
  
  TEST_FOR_EXCEPTION( DQT::isnaninf( multiplier ),
                      Utility::BadUnivariateDistributionParameter,
                      "The delta distribution cannot be constructed "
                      "because of an invalid multiplier!" );

  TEST_FOR_EXCEPTION( multiplier == DQT::zero(),
                      Utility::BadUnivariateDistributionParameter,
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

} // end Utility namespace

// Explicit instantiation (extern declaration)
EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareDeltaDistribution<void,void> );

#endif // end UTILITY_DELTA_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_DeltaDistribution_def.hpp
//---------------------------------------------------------------------------//
