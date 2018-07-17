//---------------------------------------------------------------------------//
//!
//! \file   Utility_EquiprobableBinDistribution_def.hpp
//! \author Alex Robinson
//! \brief  Equiprobable bin distribution class definition.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_EQUIPROBABLE_BIN_DISTRIBUTION_DEF_HPP
#define UTILITY_EQUIPROBABLE_BIN_DISTRIBUTION_DEF_HPP

// Std Lib Includes
#include <algorithm>

// FRENSIE Includes
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

BOOST_SERIALIZATION_DISTRIBUTION2_EXPORT_IMPLEMENT( UnitAwareEquiprobableBinDistribution );

namespace Utility{

// Basic constructor
template<typename IndependentUnit, typename DependentUnit>
UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::UnitAwareEquiprobableBinDistribution(
				 const std::vector<double>& bin_boundaries )
  : UnitAwareEquiprobableBinDistribution( Utility::arrayViewOfConst( bin_boundaries ) )
{ /* ... */ }

// Basic constructor (potentially dangerous)
template<typename IndependentUnit, typename DependentUnit>
UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::UnitAwareEquiprobableBinDistribution(
                       const Utility::ArrayView<const double>& bin_boundaries )
  : d_bin_boundaries( bin_boundaries.size() )
{
  // Verify that the bin boundaries are valid
  this->verifyValidBinBoundaries( bin_boundaries );
  
  this->initializeDistribution( bin_boundaries );

  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Constructor
template<typename IndependentUnit, typename DependentUnit>
template<typename InputIndepQuantity>
UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::UnitAwareEquiprobableBinDistribution(
	           const std::vector<InputIndepQuantity>& bin_boundaries )
  : UnitAwareEquiprobableBinDistribution( Utility::arrayViewOfConst( bin_boundaries ) )
{ /* ... */ }

// View constructor
template<typename IndependentUnit, typename DependentUnit>
template<typename InputIndepQuantity>
UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::UnitAwareEquiprobableBinDistribution( const Utility::ArrayView<const InputIndepQuantity>& bin_boundaries )
  : d_bin_boundaries( bin_boundaries.size() )
{
  // Verify that the bin boundaries are valid
  this->verifyValidBinBoundaries( bin_boundaries );

  this->initializeDistribution( bin_boundaries );

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
UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::UnitAwareEquiprobableBinDistribution(
  const UnitAwareEquiprobableBinDistribution<InputIndepUnit,InputDepUnit>& dist_instance )
  : d_bin_boundaries()
{
  this->initializeDistribution( Utility::arrayViewOfConst(dist_instance.d_bin_boundaries) );

  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Copy constructor (copying from unitless distribution only)
template<typename IndependentUnit, typename DependentUnit>
UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::UnitAwareEquiprobableBinDistribution(
 const UnitAwareEquiprobableBinDistribution<void,void>& unitless_dist_instance, int )
  : d_bin_boundaries()
{
  this->initializeDistribution( Utility::arrayViewOfConst(unitless_dist_instance.d_bin_boundaries) );

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
UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>
UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::fromUnitlessDistribution(
 const UnitAwareEquiprobableBinDistribution<void,void>& unitless_distribution )
{
  return ThisType( unitless_distribution, 0 );
}

// Assignment operator
template<typename IndependentUnit, typename DependentUnit>
UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>&
UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::operator=(
		             const UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>& dist_instance )
{
  if( this != &dist_instance )
    d_bin_boundaries = dist_instance.d_bin_boundaries;

  return *this;
}


// Evaluate the distribution
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::DepQuantity
UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::evaluate(
  const typename UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  return QuantityTraits<DepQuantity>::initializeQuantity(
		      getRawQuantity( this->evaluatePDF( indep_var_value ) ) );
}

// Evaluate the PDF
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity
UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::evaluatePDF(
    const typename UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  if( indep_var_value < d_bin_boundaries.front() )
    return QuantityTraits<InverseIndepQuantity>::zero();
  else if( indep_var_value > d_bin_boundaries.back() )
    return QuantityTraits<InverseIndepQuantity>::zero();
  else
  {
    typename std::vector<IndepQuantity>::const_iterator lower_bin_boundary,
      upper_bin_boundary;

    if( indep_var_value >= d_bin_boundaries.front() &&
	indep_var_value < d_bin_boundaries.back() )
    {
      lower_bin_boundary =
	Search::binaryLowerBound( d_bin_boundaries.begin(),
				  d_bin_boundaries.end(),
				  indep_var_value );

     upper_bin_boundary = lower_bin_boundary;
     ++upper_bin_boundary;
    }
    else
    {
      upper_bin_boundary = d_bin_boundaries.end();
      --upper_bin_boundary;

      lower_bin_boundary = upper_bin_boundary;
      --lower_bin_boundary;
    }

    return (1.0/(d_bin_boundaries.size()-1))/
      (*upper_bin_boundary - *lower_bin_boundary);
  }
}

// Evaluate the CDF
template<typename IndependentUnit, typename DependentUnit>
double UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::evaluateCDF(
   const typename UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  if( indep_var_value < d_bin_boundaries.front() )
    return 0.0;
  else if( indep_var_value >= d_bin_boundaries.back() )
    return 1.0;
  else
  {
    size_t bin_index =
      Search::binaryLowerBoundIndex( d_bin_boundaries.begin(),
				     d_bin_boundaries.end(),
				     indep_var_value );

    size_t bins = d_bin_boundaries.size()-1;

    double bin_contribution = (indep_var_value - d_bin_boundaries[bin_index])/
      (d_bin_boundaries[bin_index+1] - d_bin_boundaries[bin_index]);

    return (bin_index + bin_contribution)/bins;
  }
}

// Return a random sample from the distribution
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::sample() const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  size_t dummy_index;

  return this->sampleImplementation( random_number, dummy_index );
}

// Return a random sample and record the number of trials
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::sampleAndRecordTrials( DistributionTraits::Counter& trials ) const
{
  ++trials;

  return this->sample();
}

// Return a random sample from the distribution and the sampled index
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::sampleAndRecordBinIndex(
					    size_t& sampled_bin_index ) const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleImplementation( random_number, sampled_bin_index );
}

// Return a random sample from the distribution at the given CDF value
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::sampleWithRandomNumber(
					     const double random_number ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );

  size_t dummy_index;

  return this->sampleImplementation( random_number, dummy_index );
}

// Return a random sample from the distribution in a subrange
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::sampleInSubrange(
 const typename UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::IndepQuantity max_indep_var ) const
{
  // Make sure the max independent variable is valid
  testPrecondition( max_indep_var >= d_bin_boundaries.front() );

  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleWithRandomNumberInSubrange( random_number,
						 max_indep_var );
}

// Return a random sample using the random number and record the bin index
template<typename IndependentUnit, typename DependentUnit>
inline typename UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::sampleImplementation(
				            double random_number,
				            size_t& sampled_bin_index ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );

  double bin_location = random_number*(d_bin_boundaries.size()-1);

  sampled_bin_index = (size_t)floor(bin_location);

  return d_bin_boundaries[sampled_bin_index] +
    (bin_location - sampled_bin_index)*(d_bin_boundaries[sampled_bin_index+1]-
					d_bin_boundaries[sampled_bin_index]);
}

// Return a random sample from the distribution at the given CDF value in a subrange
template<typename IndependentUnit, typename DependentUnit>
inline typename UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::sampleWithRandomNumberInSubrange(
     const double random_number,
     const typename UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::IndepQuantity max_indep_var ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );
  // Make sure the max independent variable is valid
  testPrecondition( max_indep_var >= d_bin_boundaries.front() );

  // Compute the scaled random number
  double scaled_random_number =
    random_number*this->evaluateCDF( max_indep_var );

  size_t dummy_index;

  return this->sampleImplementation( scaled_random_number, dummy_index );
}

// Return the upper bound of the distribution independent variable
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::getUpperBoundOfIndepVar() const
{
  return d_bin_boundaries.back();
}

// Return the lower bound of the distribution independent variable
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::getLowerBoundOfIndepVar() const
{
  return d_bin_boundaries.front();
}

// Return the distribution type
template<typename IndependentUnit, typename DependentUnit>
UnivariateDistributionType UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::getDistributionType() const
{
  return ThisType::distribution_type;
}

// Test if the distribution is continuous
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::isContinuous() const
{
  return true;
}

// Method for placing the object in an output stream
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::toStream( std::ostream& os ) const
{
  this->toStreamDistImpl( os,
                          std::make_pair( "bin boundaries", d_bin_boundaries ) );
}

// Save the distribution to an archive
template<typename IndependentUnit, typename DependentUnit>
template<typename Archive>
void UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::save( Archive& ar, const unsigned version ) const
{
  // Save the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Save the local member data
  ar & BOOST_SERIALIZATION_NVP( d_bin_boundaries );
}

// Load the distribution from an archive
template<typename IndependentUnit, typename DependentUnit>
template<typename Archive>
void UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::load( Archive& ar, const unsigned version )
{
  // Load the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Load the local member data
  ar & BOOST_SERIALIZATION_NVP( d_bin_boundaries );
}

// Equality comparison operator
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::operator==(
                      const UnitAwareEquiprobableBinDistribution& other ) const
{
  return d_bin_boundaries == other.d_bin_boundaries;
}

// Inequality comparison operator
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::operator!=(
                      const UnitAwareEquiprobableBinDistribution& other ) const
{
  return d_bin_boundaries != other.d_bin_boundaries;
}

// Initialize the distribution
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::initializeDistribution(
                       const Utility::ArrayView<const double>& bin_boundaries )
{
  // Make sure there is at least one bin
  testPrecondition( bin_boundaries.size() > 1 );
  // Make sure that the bins are sorted
  testPrecondition( Sort::isSortedAscending( bin_boundaries.begin(),
					     bin_boundaries.end() ) );

  // Resize the bin boundaries array
  d_bin_boundaries.resize( bin_boundaries.size() );

  // Copy the bin boundaries
  for( size_t i = 0; i < bin_boundaries.size(); ++i )
    setQuantity( d_bin_boundaries[i], bin_boundaries[i] );
}

// Initialize the distribution
template<typename IndependentUnit, typename DependentUnit>
template<typename InputIndepQuantity>
void UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::initializeDistribution(
           const Utility::ArrayView<const InputIndepQuantity>& bin_boundaries )
{
  // Make sure there is at least one bin
  testPrecondition( bin_boundaries.size() > 1 );
  // Make sure that the bins are sorted
  testPrecondition( Sort::isSortedAscending( bin_boundaries.begin(),
					     bin_boundaries.end() ) );

  // Resize the bin boundaries array
  d_bin_boundaries.resize( bin_boundaries.size() );

  // Explicitly cast each bin boundary to the desired quantity
  for( size_t i = 0; i < bin_boundaries.size(); ++i )
    d_bin_boundaries[i] = IndepQuantity( bin_boundaries[i] );
}

// Test if the dependent variable can be zero within the indep bounds
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::canDepVarBeZeroInIndepBounds() const
{
  return false;
}

// Verify that the bin boundaries are valid
template<typename IndependentUnit, typename DependentUnit>
template<typename InputIndepQuantity>
void UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::verifyValidBinBoundaries(
           const Utility::ArrayView<const InputIndepQuantity>& bin_boundaries )
{
  TEST_FOR_EXCEPTION( bin_boundaries.size() <= 1,
		      Utility::BadUnivariateDistributionParameter,
		      "The equiprobable bin distribution cannot be "
		      "constructed because at least one bin (consisting of "
                      "two boundaries) is required!" );

  TEST_FOR_EXCEPTION( !Sort::isSortedAscending( bin_boundaries.begin(),
						bin_boundaries.end() ),
		      Utility::BadUnivariateDistributionParameter,
		      "The equiprobable bin distribution cannot be "
		      "constructed because the bin boundaries "
		      << bin_boundaries << " are not sorted!" );

  typedef Utility::QuantityTraits<InputIndepQuantity> IIQT;

  TEST_FOR_EXCEPTION( IIQT::isnaninf( bin_boundaries.front() ),
                      Utility::BadUnivariateDistributionParameter,
                      "The equiprobable bin distribution cannot be "
                      "constructed because the first bin boundary is "
                      "invalid!" );

  TEST_FOR_EXCEPTION( IIQT::isnaninf( bin_boundaries.back() ),
                      Utility::BadUnivariateDistributionParameter,
                      "The equiprobable bin distribution cannot be "
                      "constructed because the last bin boundary is "
                      "invalid!" );

  typename Utility::ArrayView<const InputIndepQuantity>::const_iterator repeat_bin_boundary =
    std::adjacent_find( bin_boundaries.begin(), bin_boundaries.end() );

  TEST_FOR_EXCEPTION( repeat_bin_boundary != bin_boundaries.end(),
                      Utility::BadUnivariateDistributionParameter,
                      "The equiprobable bin distribution cannot be "
                      "constructed because there is a repeated bin boundary "
                      "at index "
                      << std::distance( bin_boundaries.begin(), repeat_bin_boundary ) <<
                      " (" << *repeat_bin_boundary << ")!" );
}

} // end Utility namespace

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareEquiprobableBinDistribution<void,void> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Utility, UnitAwareEquiprobableBinDistribution<void,void> );

#endif // end UTILITY_EQUIPROBABLE_BIN_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_EquiprobableBinDistribution_def.hpp
//---------------------------------------------------------------------------//
