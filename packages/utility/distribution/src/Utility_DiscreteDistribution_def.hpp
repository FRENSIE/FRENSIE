//---------------------------------------------------------------------------//
//!
//! \file   Utility_DiscreteDistribution_def.hpp
//! \author Alex Robinson
//! \brief  Discrete distribution class definition.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_DISCRETE_DISTRIBUTION_DEF_HPP
#define UTILITY_DISCRETE_DISTRIBUTION_DEF_HPP

// Std Lib Includes
#include <algorithm>

// FRENSIE Includes
#include "Utility_DataProcessor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_DesignByContract.hpp"

BOOST_SERIALIZATION_DISTRIBUTION2_EXPORT_IMPLEMENT( UnitAwareDiscreteDistribution );

namespace Utility{

// Basic Constructor (potentially dangerous)
/*! \details A precalculated CDF can be passed as the dependent values as
 * long as the interpret_dependent_values_as_cdf argument is true.
 */
template<typename IndependentUnit,typename DependentUnit>
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::UnitAwareDiscreteDistribution(
			      const std::vector<double>& independent_values,
			      const std::vector<double>& dependent_values,
			      const bool interpret_dependent_values_as_cdf,
                              const bool treat_as_continuous )
  : UnitAwareDiscreteDistribution( Utility::arrayViewOfConst( independent_values ),
                                   Utility::arrayViewOfConst( dependent_values ),
                                   interpret_dependent_values_as_cdf,
                                   treat_as_continuous )
{ /* ... */ }

// Basic View Constructor (potentially dangerous)
/*! \details A precalculated CDF can be passed as the dependent values as
 * long as the interpret_dependent_values_as_cdf argument is true.
 */
template<typename IndependentUnit,typename DependentUnit>
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::UnitAwareDiscreteDistribution(
                    const Utility::ArrayView<const double>& independent_values,
                    const Utility::ArrayView<const double>& dependent_values,
                    const bool interpret_dependent_values_as_cdf,
                    const bool treat_as_continuous )
  : d_distribution( independent_values.size() ),
    d_norm_constant(),
    d_continuous( treat_as_continuous )
{
  // Verify that the values are valid
  this->verifyValidValues( independent_values,
                           dependent_values,
                           interpret_dependent_values_as_cdf );
  
  this->initializeDistribution( independent_values,
				dependent_values,
				interpret_dependent_values_as_cdf );

  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// CDF Constructor (potentially dangerous)
template<typename IndependentUnit,typename DependentUnit>
template<typename InputIndepQuantity>
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::UnitAwareDiscreteDistribution(
	      const std::vector<InputIndepQuantity>& independent_quantities,
	      const std::vector<double>& dependent_values,
              const bool treat_as_continuous )
  : UnitAwareDiscreteDistribution( Utility::arrayViewOfConst(independent_quantities),
                                   Utility::arrayViewOfConst(dependent_values),
                                   treat_as_continuous )
{ /* ... */ }

// CDF view constructor
template<typename IndependentUnit,typename DependentUnit>
template<typename InputIndepQuantity>
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::UnitAwareDiscreteDistribution(
    const Utility::ArrayView<const InputIndepQuantity>& independent_quantities,
    const Utility::ArrayView<const double>& dependent_values,
    const bool treat_as_continuous )
  : d_distribution( independent_quantities.size() ),
    d_norm_constant(),
    d_continuous( treat_as_continuous )
{
  // Verify that the values are valid
  this->verifyValidValues( independent_quantities, dependent_values, true );
  
  this->initializeDistributionFromCDF( independent_quantities,
				       dependent_values );

  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Constructor
template<typename IndependentUnit,typename DependentUnit>
template<typename InputIndepQuantity,typename InputDepQuantity>
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::UnitAwareDiscreteDistribution(
	      const std::vector<InputIndepQuantity>& independent_quantities,
	      const std::vector<InputDepQuantity>& dependent_quantities,
              const bool treat_as_continuous )
  : UnitAwareDiscreteDistribution( Utility::arrayViewOfConst(independent_quantities),
                                   Utility::arrayViewOfConst(dependent_quantities),
                                   treat_as_continuous )
{ /* ... */ }

// View constructor
template<typename IndependentUnit,typename DependentUnit>
template<typename InputIndepQuantity,typename InputDepQuantity>
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::UnitAwareDiscreteDistribution(
    const Utility::ArrayView<const InputIndepQuantity>& independent_quantities,
    const Utility::ArrayView<const InputDepQuantity>& dependent_quantities,
    const bool treat_as_continuous )
  : d_distribution( independent_quantities.size() ),
    d_norm_constant(),
    d_continuous( treat_as_continuous )
{
  // Verify that the values are valid
  this->verifyValidValues( independent_quantities,
                           dependent_quantities,
                           false );
    
  this->initializeDistribution( independent_quantities,
				dependent_quantities );

  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}
 
// Copy constructor
/*! \details Just like boost::units::quantity objects, the unit-aware
 * distribution can be explicitly cast to a distribution with compatible
 * units. If the units are not compatible, this function will not compile. Note
 * that this allows distributions to be scaled safely (unit conversions
 * are completely taken care of by boost::units)!
 */
template<typename IndependentUnit,typename DependentUnit>
template<typename InputIndepUnit, typename InputDepUnit>
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::UnitAwareDiscreteDistribution(
	  const UnitAwareDiscreteDistribution<InputIndepUnit,InputDepUnit>& dist_instance )
  : d_distribution(),
    d_norm_constant(),
    d_continuous( dist_instance.d_continuous )
{
  // Make sure that the distribution is valid
  testPrecondition( dist_instance.d_distribution.size() > 0 );

  typedef typename UnitAwareDiscreteDistribution<InputIndepUnit,InputDepUnit>::IndepQuantity InputIndepQuantity;

  typedef typename UnitAwareDiscreteDistribution<InputIndepUnit,InputDepUnit>::DepQuantity InputDepQuantity;

  // Reconstruct the original input distribution
  std::vector<InputIndepQuantity> input_indep_quantities;
  std::vector<InputDepQuantity> input_dep_quantities;

  dist_instance.reconstructOriginalDistribution( input_indep_quantities,
						 input_dep_quantities );

  this->initializeDistribution(
                             Utility::arrayViewOfConst(input_indep_quantities),
                             Utility::arrayViewOfConst(input_dep_quantities) );

  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Copy constructor (copying from unitless distribution only)
template<typename IndependentUnit,typename DependentUnit>
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::UnitAwareDiscreteDistribution(
  const UnitAwareDiscreteDistribution<void,void>& unitless_dist_instance, int )
  : d_distribution(),
    d_norm_constant(),
    d_continuous( unitless_dist_instance.d_continuous )
{
  // Make sure that the distribution is valid
  testPrecondition( unitless_dist_instance.d_distribution.size() > 0 );

  // Reconstruct the original input distribution
  std::vector<double> input_bin_boundaries, input_bin_values;

  unitless_dist_instance.reconstructOriginalDistribution( input_bin_boundaries,
							  input_bin_values );

  // Verify that the values are valid
  this->verifyValidValues( Utility::arrayViewOfConst(input_bin_boundaries),
                           Utility::arrayViewOfConst(input_bin_values),
                           false );

  this->initializeDistribution( Utility::arrayViewOfConst(input_bin_boundaries),
                                Utility::arrayViewOfConst(input_bin_values),
                                false );

  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Construct distribution from a unitless dist. (potentially dangerous)
/*! \details Constructing a unit-aware distribution from a unitless
 * distribution is potentially dangerous. By forcing users to construct objects
 * using this method instead of a standard constructor we are trying to make
 * sure users are aware of the danger. This is designed to mimic the interface
 * of the boost::units::quantity, which also has to deal with this issue.
 */
template<typename IndependentUnit,typename DependentUnit>
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::fromUnitlessDistribution(
        const UnitAwareDiscreteDistribution<void,void>& unitless_distribution )
{
  return ThisType( unitless_distribution, 0 );
}

// Assignment operator
template<typename IndependentUnit,typename DependentUnit>
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>&
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::operator=(
	  const UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>& dist_instance )
{
  // Make sure that the distribution is valid
  testPrecondition( dist_instance.d_distribution.size() > 0 );

  if( this != &dist_instance )
  {
    d_distribution = dist_instance.d_distribution;
    d_norm_constant = dist_instance.d_norm_constant;
    d_continuous = dist_instance.d_continuous;
  }

  return *this;
}

// Evaluate the distribution
/*! \details The discrete distribution can be expressed as a sum of delta
 * functions, which allows it to behave as a continuous distribution.
 * Therefore, the discrete distribution can technically only take on
 * two values: 0.0 and infinity. It is more useful to return the dependent
 * value associated with a defined independent value.
 */
template<typename IndependentUnit,typename DependentUnit>
typename UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::DepQuantity
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::evaluate( const typename UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  return Utility::getRawQuantity(this->evaluatePDF( indep_var_value ))*d_norm_constant;
}

// Evaluate the PDF
/*! \details It is acceptable for the same independent variable to appear
 * multiple times. When multiple occurrences are found, the sum will be
 * returned.
 */
template<typename IndependentUnit,typename DependentUnit>
typename UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::evaluatePDF( const typename UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  double raw_pdf = 0.0;

  if( indep_var_value >= Utility::get<0>(d_distribution.front()) &&
      indep_var_value <= Utility::get<0>(d_distribution.back()) )
  {
    typename std::vector<std::pair<IndepQuantity,double> >::const_iterator bin =
      Search::binaryLowerBound<0>( d_distribution.begin(),
				       d_distribution.end(),
				       indep_var_value );

    typename std::vector<std::pair<IndepQuantity,double> >::const_iterator
      prev_bin = bin;
    --prev_bin;

    // The same independent variable may appear multiple times
    while( Utility::get<0>(*bin) == indep_var_value )
    {
      if( bin != d_distribution.begin() )
      {
	raw_pdf += Utility::get<1>(*bin) -
          Utility::get<1>(*prev_bin);

	--bin;
	--prev_bin;
      }
      else
      {
	raw_pdf += Utility::get<1>(*bin);

	break;
      }
    }
  }
  else
    raw_pdf = 0.0;

  return QuantityTraits<InverseIndepQuantity>::initializeQuantity( raw_pdf );
}

// Evaluate the CDF
template<typename IndependentUnit,typename DependentUnit>
double UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::evaluateCDF( const typename UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  double cdf = 0.0;

  if( indep_var_value >= Utility::get<0>(d_distribution.front()) &&
      indep_var_value <= Utility::get<0>(d_distribution.back()) )
  {
    typename std::vector<std::pair<IndepQuantity,double> >::const_iterator bin =
      Search::binaryLowerBound<0>( d_distribution.begin(),
				       d_distribution.end(),
				       indep_var_value );

    // The same independent variable may appear multiple times
    cdf = Utility::get<1>(*bin);
  }
  else if( indep_var_value < Utility::get<0>(d_distribution.front()) )
    cdf = 0.0;
  else
    cdf = 1.0;

  return cdf;
}


// Return a random sample from the distribution
template<typename IndependentUnit,typename DependentUnit>
typename UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::sample() const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  size_t dummy_index;

  return this->sampleImplementation( random_number, dummy_index );
}

// Return a random sample and record the number of trials
template<typename IndependentUnit,typename DependentUnit>
typename UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::sampleAndRecordTrials( DistributionTraits::Counter& trials ) const
{
  ++trials;

  return this->sample();
}

// Return a random sample and sampled index from the corresponding CDF
template<typename IndependentUnit,typename DependentUnit>
typename UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::sampleAndRecordBinIndex(
					    size_t& sampled_bin_index ) const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleImplementation( random_number, sampled_bin_index );
}

// Return a random sample and sampled index from the corresponding CDF
template<typename IndependentUnit,typename DependentUnit>
typename UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::sampleWithRandomNumber(
					     const double random_number ) const
{
  size_t dummy_index;

  return this->sampleImplementation( random_number, dummy_index );
}

// Return a random sample from the corresponding CDF in a subrange
template<typename IndependentUnit,typename DependentUnit>
typename UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::sampleInSubrange( const typename UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::IndepQuantity max_indep_var ) const
{
  // Make sure the max independent variable is valid
  testPrecondition( max_indep_var >= Utility::get<0>(d_distribution.front()) );

  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleWithRandomNumberInSubrange( random_number,
						 max_indep_var );
}

// Return a random sample using the random number and record the bin index
template<typename IndependentUnit,typename DependentUnit>
inline typename UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::sampleImplementation(
					    double random_number,
					    size_t& sampled_bin_index ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );

  // Get the bin index sampled
  sampled_bin_index =
    Search::binaryUpperBoundIndex<1>( d_distribution.begin(),
					   d_distribution.end(),
					   random_number );

  return Utility::get<0>(d_distribution[sampled_bin_index]);
}

// Return a random sample from the distribution at the given CDF value in a subrange
template<typename IndependentUnit,typename DependentUnit>
inline typename UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::sampleWithRandomNumberInSubrange(
   const double random_number,
   const typename UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::IndepQuantity max_indep_var ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );
  // Make sure the max independent variable is valid
  testPrecondition( max_indep_var >= Utility::get<0>(d_distribution.front()) );

  // Scale the random number to the cdf at the max indep var
  double scaled_random_number =
    random_number*this->evaluateCDF( max_indep_var );

  size_t dummy_index;

  return this->sampleImplementation( scaled_random_number, dummy_index );
}

// Return the upper bound of the distribution independent variable
template<typename IndependentUnit,typename DependentUnit>
typename UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::getUpperBoundOfIndepVar() const
{
  return Utility::get<0>(d_distribution.back());
}

// Return the lower bound of the independent variable
template<typename IndependentUnit,typename DependentUnit>
typename UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::getLowerBoundOfIndepVar() const
{
  return Utility::get<0>(d_distribution.front());
}

// Return the distribution type
template<typename IndependentUnit,typename DependentUnit>
UnivariateDistributionType
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::getDistributionType() const
{
  return ThisType::distribution_type;
}

// Test if the distribution is continuous
template<typename IndependentUnit,typename DependentUnit>
bool UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::isContinuous() const
{
  return d_continuous;
}

// Method for placing the object in an output stream
template<typename IndependentUnit,typename DependentUnit>
void UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::toStream( std::ostream& os ) const
{
  std::vector<IndepQuantity> independent_values;
  std::vector<DepQuantity> dependent_values;

  this->reconstructOriginalDistribution(independent_values, dependent_values);

  this->toStreamDistImpl( os,
                          std::make_pair( "independent values", independent_values ),
                          std::make_pair( "dependent values", dependent_values ) );
}

// Save the distribution to an archive
template<typename IndependentUnit, typename DependentUnit>
template<typename Archive>
void UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::save( Archive& ar, const unsigned version ) const
{
  // Save the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Save the local member data
  ar & BOOST_SERIALIZATION_NVP( d_distribution );
  ar & BOOST_SERIALIZATION_NVP( d_norm_constant );
  ar & BOOST_SERIALIZATION_NVP( d_continuous );
}

// Load the distribution from an archive
template<typename IndependentUnit, typename DependentUnit>
template<typename Archive>
void UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::load( Archive& ar, const unsigned version )
{
  // Load the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Load the local member data
  ar & BOOST_SERIALIZATION_NVP( d_distribution );
  ar & BOOST_SERIALIZATION_NVP( d_norm_constant );
  ar & BOOST_SERIALIZATION_NVP( d_continuous );
}

// Equality comparison operator
template<typename IndependentUnit,typename DependentUnit>
bool UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::operator==( const UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>& other ) const
{
  return d_distribution == other.d_distribution &&
    d_norm_constant == other.d_norm_constant;
}

// Inequality comparison operator
template<typename IndependentUnit,typename DependentUnit>
bool UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::operator!=( const UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>& other ) const
{
  return d_distribution != other.d_distribution ||
    d_norm_constant != other.d_norm_constant;
}  

// Initialize the distribution
template<typename IndependentUnit,typename DependentUnit>
void UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::initializeDistribution(
                    const Utility::ArrayView<const double>& independent_values,
                    const Utility::ArrayView<const double>& dependent_values,
                    const bool interpret_dependent_values_as_cdf )
{
  // Make sure that every value has a probability assigned
  testPrecondition( independent_values.size() == dependent_values.size() );
  // Make sure that the bins are sorted
  testPrecondition( Sort::isSortedAscending( independent_values.begin(),
					     independent_values.end() ) );

  // Convert the raw independent values to quantities
  std::vector<IndepQuantity> independent_quantities;

  this->convertUnitlessValues( independent_values, independent_quantities );

  if( interpret_dependent_values_as_cdf )
  {
    this->initializeDistributionFromCDF(
                             Utility::arrayViewOfConst(independent_quantities),
                             dependent_values );
  }
  else
  {
    // Convert the raw dependent values to quantities
    std::vector<DepQuantity> dependent_quantities;

    this->convertUnitlessValues( dependent_values, dependent_quantities );

    this->initializeDistribution(
                             Utility::arrayViewOfConst(independent_quantities),
                             Utility::arrayViewOfConst(dependent_quantities) );
  }
}

// Initialize the distribution from a cdf
template<typename IndependentUnit,typename DependentUnit>
template<typename InputIndepQuantity>
void UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::initializeDistributionFromCDF(
    const Utility::ArrayView<const InputIndepQuantity>& independent_quantities,
    const Utility::ArrayView<const double>& cdf_values )
{
  // Make sure that every value has a probability assigned
  testPrecondition( independent_quantities.size() == cdf_values.size() );
  // Make sure that the bins are sorted
  testPrecondition( Sort::isSortedAscending( independent_quantities.begin(),
					     independent_quantities.end() ) );
  // Make sure that the cdf is sorted
  testPrecondition( Sort::isSortedAscending( cdf_values.begin(),
					     cdf_values.end() ) );

  // Resize the distribution
  d_distribution.resize( independent_quantities.size() );

  // Assign the distribution
  for( size_t i = 0; i < cdf_values.size(); ++i )
  {
    Utility::get<0>(d_distribution[i]) =
      IndepQuantity( independent_quantities[i] );

    Utility::get<1>(d_distribution[i]) = cdf_values[i];
  }

  // Verify that the CDF is normalized (in event of round-off errors)
  if( cdf_values.back() != 1.0 )
  {
    for( size_t i = 0; i < d_distribution.size(); ++i )
    {
      Utility::get<1>(d_distribution[i]) /=
        Utility::get<1>(d_distribution.back());
    }
  }

  // Set the normalization constant
  setQuantity( d_norm_constant, 1.0 );
}

// Initialize the distribution
template<typename IndependentUnit,typename DependentUnit>
template<typename InputIndepQuantity,typename InputDepQuantity>
void UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::initializeDistribution(
        const Utility::ArrayView<const InputIndepQuantity>& independent_values,
        const Utility::ArrayView<const InputDepQuantity>& dependent_values )
{
  // Make sure that every value has a probability assigned
  testPrecondition( independent_values.size() == dependent_values.size() );
  // Make sure that the bins are sorted
  testPrecondition( Sort::isSortedAscending( independent_values.begin(),
					     independent_values.end() ) );

  // Resize the distribution array
  d_distribution.resize( independent_values.size() );

  // Initialize the normalization constant
  Utility::setQuantity( d_norm_constant, 0.0 );

  // Assign the raw distribution data
  for( size_t i = 0; i < dependent_values.size(); ++i )
  {
    Utility::get<0>(d_distribution[i]) =
      IndepQuantity( independent_values[i] );

    // Use an explicit cast to desired unit
    DepQuantity dep_quantity( dependent_values[i] );

    Utility::get<1>(d_distribution[i]) = Utility::getRawQuantity( dep_quantity );

    d_norm_constant += dep_quantity;
  }

  // Create a CDF from the raw distribution data
  DataProcessor::calculateDiscreteCDF<1,1>( d_distribution );
}

// Reconstruct original distribution
template<typename IndependentUnit,typename DependentUnit>
void UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::reconstructOriginalDistribution(
		     std::vector<IndepQuantity>& independent_quantities,
		     std::vector<DepQuantity>& dependent_quantities ) const
{
  // Resize the arrays
  independent_quantities.resize( d_distribution.size() );
  dependent_quantities.resize( d_distribution.size() );

  for( size_t i = 0u; i < d_distribution.size(); ++i )
  {
    independent_quantities[i] = Utility::get<0>(d_distribution[i]);

    if( i != 0u )
    {
      dependent_quantities[i] = d_norm_constant*
	(Utility::get<1>(d_distribution[i]) -
         Utility::get<1>(d_distribution[i-1]));
    }
    else
    {
      dependent_quantities[i] =
        d_norm_constant*Utility::get<1>(d_distribution[i]);
    }
  }
}

// Reconstruct original distribution w/o units
template<typename IndependentUnit,typename DependentUnit>
void UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::reconstructOriginalUnitlessDistribution(
			      std::vector<double>& independent_values,
			      std::vector<double>& dependent_values ) const
{
  // Resize the arrays
  independent_values.resize( d_distribution.size() );
  dependent_values.resize( d_distribution.size() );

  for( size_t i = 0u; i < d_distribution.size(); ++i )
  {
    independent_values[i] =
      Utility::getRawQuantity( Utility::get<0>(d_distribution[i]) );

    if( i != 0u )
    {
      dependent_values[i] = Utility::getRawQuantity( d_norm_constant )*
	(Utility::get<1>(d_distribution[i]) -
         Utility::get<1>(d_distribution[i-1]));
    }
    else
    {
      dependent_values[i] = Utility::get<1>(d_distribution[i])*
        Utility::getRawQuantity( d_norm_constant );
    }
  }
}

// Convert the unitless values to the correct units
template<typename IndependentUnit,typename DependentUnit>
template<typename Quantity>
void UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::convertUnitlessValues(
                       const Utility::ArrayView<const double>& unitless_values,
                       std::vector<Quantity>& quantities )
{
  // Resize the quantities array
  quantities.resize( unitless_values.size() );

  // Copy the values
  for( size_t i = 0u; i < unitless_values.size(); ++i )
    setQuantity( quantities[i], unitless_values[i] );
}

// Test if the dependent variable can be zero within the indep bounds
template<typename IndependentUnit,typename DependentUnit>
bool UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::canDepVarBeZeroInIndepBounds() const
{
  return true;
}

// Verify that the values are valid
template<typename IndependentUnit,typename DependentUnit>
template<typename InputIndepQuantity, typename InputDepQuantity>
void UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::verifyValidValues(
        const Utility::ArrayView<const InputIndepQuantity>& independent_values,
        const Utility::ArrayView<const InputDepQuantity>& dependent_values,
        const bool cdf_bin_values )
{
  TEST_FOR_EXCEPTION( independent_values.size() == 0,
                      Utility::BadUnivariateDistributionParameter,
                      "The discrete distribution cannot be constructed "
                      "because no independent values have been specified!" );
  
  TEST_FOR_EXCEPTION( !Sort::isSortedAscending( independent_values.begin(),
						independent_values.end() ),
		      Utility::BadUnivariateDistributionParameter,
		      "The discrete distribution cannot be constructed "
		      "because the independent values "
		      << independent_values << " are not sorted!" );

  typedef Utility::QuantityTraits<InputIndepQuantity> IIQT;
  
  TEST_FOR_EXCEPTION( IIQT::isnaninf( independent_values.front() ),
                      Utility::BadUnivariateDistributionParameter,
                      "The discrete distribution cannot be constructed "
                      "because the first independent value is invalid!" );

  TEST_FOR_EXCEPTION( IIQT::isnaninf( independent_values.back() ),
                      Utility::BadUnivariateDistributionParameter,
                      "The discrete distribution cannot be constructed "
                      "because the last independent value is invalid!" );
  
  TEST_FOR_EXCEPTION( independent_values.size() != dependent_values.size(),
		      Utility::BadUnivariateDistributionParameter,
		      "The discrete distribution cannot be constructed "
                      "because the number of independent values ("
                      << independent_values.size() << ") does not match the "
                      "number of dependent values ("
                      << dependent_values.size() << ")!" );

  typedef Utility::QuantityTraits<InputDepQuantity> IDQT;

  typename Utility::ArrayView<const InputDepQuantity>::const_iterator bad_dependent_value =
    std::find_if( dependent_values.begin(),
                  dependent_values.end(),
                  [](const InputDepQuantity& element){ return IDQT::isnaninf( element ) || element <= IDQT::zero(); } );
    
  TEST_FOR_EXCEPTION(  bad_dependent_value != dependent_values.end(),
                       Utility::BadUnivariateDistributionParameter,
                      "The discrete distribution cannot be constructed "
                      "because the dependent value at index "
                       << std::distance( dependent_values.begin(), bad_dependent_value ) <<
                       " (" << *bad_dependent_value << ") is not valid!" );

  if( cdf_bin_values )
  {
    TEST_FOR_EXCEPTION( !Sort::isSortedAscending( dependent_values.begin(),
                                                  dependent_values.end() ),
                        Utility::BadUnivariateDistributionParameter,
                        "The discrete distribution cannot be constructed "
                        "because the dependent cdf values  are not "
                        "sorted!" );

    typename Utility::ArrayView<const InputDepQuantity>::const_iterator repeat_cdf_value =
      std::adjacent_find( dependent_values.begin(), dependent_values.end() );
    
    TEST_FOR_EXCEPTION( repeat_cdf_value != dependent_values.end(),
                        Utility::BadUnivariateDistributionParameter,
                        "The discrete distribution cannot be "
                        "constructed because there is a repeated dependent cdf"
                        " value at index "
                        << std::distance( dependent_values.begin(), repeat_cdf_value ) <<
                        " (" << *repeat_cdf_value << ")!" );
  }
}

// Test if the dependent variable is compatible with Log processing
/*! \details Log interpolation of the dependant variable can not be used to
 *  evaluate the distribution, pdf, or cdf between two one-d distribution. There
 *  are cases where it can be used to sample between two one-d distribution.
 *  This is the case with the elastic moment-preserving distribution. To
 *  accomidate the elastic moment-preserving distribution this function is set
 *  to true.
 */
template<typename IndependentUnit,typename DependentUnit>
bool UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::isDepVarCompatibleWithProcessingType(
                                           const LogDepVarProcessingTag ) const
{
  return true;
}

} // end Utility namespace

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareDiscreteDistribution<void,void> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Utility, UnitAwareDiscreteDistribution<void,void> );

#endif // end UTILITY_DISCRETE_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_DiscreteDistribution_def.hpp
//---------------------------------------------------------------------------//
