//---------------------------------------------------------------------------//
//!
//! \file   Utility_HistogramDistribution_def.pp
//! \author Alex Robinson
//! \brief  Histogram distribution class definition.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_HISTOGRAM_DISTRIBUTION_DEF_HPP
#define UTILITY_HISTOGRAM_DISTRIBUTION_DEF_HPP

// Std Lib Includes
#include <algorithm>

// FRENSIE Includes
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_DesignByContract.hpp"

BOOST_SERIALIZATION_DISTRIBUTION2_EXPORT_IMPLEMENT( UnitAwareHistogramDistribution );

namespace Utility{

// Basic constructor (potentially dangerous)
/*! \details The bin boundaries are assumed to be sorted (lowest to
 * highest). If cdf values are provided a pdf will be calculated. Note that
 * the first cdf value, which is always zero, should not be passed (N-1 cdf
 * values for N bin boundaries).
 */
template<typename IndependentUnit, typename DependentUnit>
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::UnitAwareHistogramDistribution(
				 const std::vector<double>& bin_boundaries,
				 const std::vector<double>& bin_values,
				 const bool interpret_dependent_values_as_cdf )
  : UnitAwareHistogramDistribution( Utility::arrayViewOfConst(bin_boundaries),
                                    Utility::arrayViewOfConst(bin_values),
                                    interpret_dependent_values_as_cdf )
{ /* ... */ }

// Basic view constructor
/*! \details The bin boundaries are assumed to be sorted (lowest to
 * highest). If cdf values are provided a pdf will be calculated. Note that
 * the first cdf value, which is always zero, should not be passed (N-1 cdf
 * values for N bin boundaries).
 */
template<typename IndependentUnit, typename DependentUnit>
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::UnitAwareHistogramDistribution(
                        const Utility::ArrayView<const double>& bin_boundaries,
                        const Utility::ArrayView<const double>& bin_values,
                        const bool interpret_dependent_values_as_cdf )
  : d_distribution( bin_boundaries.size() ),
    d_norm_constant( DNQT::one() )
{
  // Verify that the values are valid
  this->verifyValidValues( bin_boundaries,
                           bin_values, 
                           interpret_dependent_values_as_cdf );
  
  this->initializeDistribution( bin_boundaries,
				bin_values,
				interpret_dependent_values_as_cdf );

  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// CDF constructor
/*! \details The bin boundaries are assumed to be sorted (lowest to highest).
 * A pdf will be calculated from the cdf. Note that the first cdf value, which
 * is always zero, should not be passed (N-1 cdf values for N bin boundaries).
 */
template<typename IndependentUnit, typename DependentUnit>
template<typename InputIndepQuantity>
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::UnitAwareHistogramDistribution(
		      const std::vector<InputIndepQuantity>& bin_boundaries,
		      const std::vector<double>& cdf_values )
  : UnitAwareHistogramDistribution( Utility::arrayViewOfConst(bin_boundaries),
                                    Utility::arrayViewOfConst(cdf_values) )
{ /* ... */ }

// CDF view constructor
template<typename IndependentUnit, typename DependentUnit>
template<typename InputIndepQuantity>
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::UnitAwareHistogramDistribution(
            const Utility::ArrayView<const InputIndepQuantity>& bin_boundaries,
            const Utility::ArrayView<const double>& cdf_values )
  : d_distribution( bin_boundaries.size() ),
    d_norm_constant( DNQT::one() )
{
  // Verify that the values are valid
  this->verifyValidValues( bin_boundaries, cdf_values, true );

  this->initializeDistributionFromCDF( bin_boundaries, cdf_values );

  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Constructor
template<typename IndependentUnit, typename DependentUnit>
template<typename InputIndepQuantity, typename InputDepQuantity>
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::UnitAwareHistogramDistribution(
		      const std::vector<InputIndepQuantity>& bin_boundaries,
		      const std::vector<InputDepQuantity>& bin_values )
  : UnitAwareHistogramDistribution( Utility::arrayViewOfConst(bin_boundaries),
                                    Utility::arrayViewOfConst(bin_values) )
{ /* ... */ }

// View constructor
template<typename IndependentUnit, typename DependentUnit>
template<typename InputIndepQuantity, typename InputDepQuantity>
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::UnitAwareHistogramDistribution(
            const Utility::ArrayView<const InputIndepQuantity>& bin_boundaries,
            const Utility::ArrayView<const InputDepQuantity>& bin_values )
  : d_distribution( bin_boundaries.size() ),
    d_norm_constant( DNQT::one() )
{
  // Verify that the values are valid
  this->verifyValidValues( bin_boundaries, bin_values, false );

  this->initializeDistribution( bin_boundaries, bin_values );

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
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::UnitAwareHistogramDistribution(
 const UnitAwareHistogramDistribution<InputIndepUnit,InputDepUnit>& dist_instance )
  : d_distribution(),
    d_norm_constant()
{

  typedef typename UnitAwareHistogramDistribution<InputIndepUnit,InputDepUnit>::IndepQuantity InputIndepQuantity;

  typedef typename UnitAwareHistogramDistribution<InputIndepUnit,InputDepUnit>::DepQuantity InputDepQuantity;

  // Reconstruct the original input distribution
  std::vector<InputIndepQuantity> input_bin_boundaries;
  std::vector<InputDepQuantity> input_bin_values;

  dist_instance.reconstructOriginalDistribution( input_bin_boundaries,
						 input_bin_values );

  this->initializeDistribution( Utility::arrayViewOfConst(input_bin_boundaries),
                                Utility::arrayViewOfConst(input_bin_values) );

  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Copy constructor (copying from unitless distribution only)
template<typename IndependentUnit, typename DependentUnit>
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::UnitAwareHistogramDistribution(
 const UnitAwareHistogramDistribution<void,void>& unitless_dist_instance, int )
  : d_distribution(),
    d_norm_constant()
{
  // Reconstruct the original input distribution
  std::vector<double> input_bin_boundaries, input_bin_values;

  unitless_dist_instance.reconstructOriginalDistribution( input_bin_boundaries,
							  input_bin_values );

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
template<typename IndependentUnit, typename DependentUnit>
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::fromUnitlessDistribution(
       const UnitAwareHistogramDistribution<void,void>& unitless_distribution )
{
  return ThisType( unitless_distribution, 0 );
}

// Assignment operator
template<typename IndependentUnit, typename DependentUnit>
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>&
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::operator=(
  const UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>& dist_instance )
{
  if( this != &dist_instance )
  {
    d_distribution = dist_instance.d_distribution;
    d_norm_constant = dist_instance.d_norm_constant;
  }

  return *this;
}

// Evaluate the distribution
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::DepQuantity
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::evaluate(
 const typename UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  if( indep_var_value < Utility::get<0>(d_distribution.front()) )
    return DQT::zero();
  else if( indep_var_value > Utility::get<0>(d_distribution.back()) )
    return DQT::zero();
  else
  {
    typename DistributionArray::const_iterator bin =
      Search::binaryLowerBound<0>( d_distribution.begin(),
                                       d_distribution.end(),
                                       indep_var_value );

    return Utility::get<1>(*bin);
  }
}

// Evaluate the PDF
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::evaluatePDF(
 const typename UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  return evaluate( indep_var_value )*d_norm_constant;
}

// Evaluate the CDF
template<typename IndependentUnit, typename DependentUnit>
double UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::evaluateCDF(
  const typename UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  if( indep_var_value < Utility::get<0>(d_distribution.front()) )
    return 0.0;
  else if( indep_var_value >= Utility::get<0>(d_distribution.back()) )
    return 1.0;
  else
  {
    typename DistributionArray::const_iterator lower_bin =
      Search::binaryLowerBound<0>( d_distribution.begin(),
                                       d_distribution.end(),
                                       indep_var_value );

    IndepQuantity indep_diff =
      indep_var_value - Utility::get<0>(*lower_bin);

    return (Utility::get<2>(*lower_bin) +
            Utility::get<1>(*lower_bin)*indep_diff)*d_norm_constant;
  }
}

// Return a random sample from the distribution
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::sample() const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  size_t dummy_index;

  return this->sampleImplementation( random_number, dummy_index );
}

// Return a random sample and record the number of trials
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::sampleAndRecordTrials( DistributionTraits::Counter& trials ) const
{
  ++trials;

  return this->sample();
}

// Return a random sample and bin index from the distribution
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::sampleAndRecordBinIndex(
					    size_t& sampled_bin_index ) const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleImplementation( random_number, sampled_bin_index );
}

// Return a random sample from the distribution at the given CDF value
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::sampleWithRandomNumber(
					     const double random_number ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );

  size_t dummy_index;

  return this->sampleImplementation( random_number, dummy_index );
}

// Return a random sample from the corresponding CDF in a subrange
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::sampleInSubrange(
   const typename UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::IndepQuantity max_indep_var ) const
{
  // Make sure the maximum indep var is valid
  testPrecondition( max_indep_var >= this->getLowerBoundOfIndepVar() );

  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleWithRandomNumberInSubrange( random_number,
						 max_indep_var );
}

// Return a sample from the distribution at the given CDF value in a subrange
template<typename IndependentUnit, typename DependentUnit>
inline typename UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::sampleWithRandomNumberInSubrange(
  const double random_number,
  const typename UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::IndepQuantity max_indep_var ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );
  // Make sure the maximum indep var is valid
  testPrecondition( max_indep_var >= this->getLowerBoundOfIndepVar() );

  // Compute the scaled random number
  double scaled_random_number =
    random_number*this->evaluateCDF( max_indep_var );

  size_t dummy_index;

  return this->sampleImplementation( scaled_random_number, dummy_index );
}

// Return a random sample from the corresponding CDF in a subrange with a min value included
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::sampleInSubrange(
   const typename UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::IndepQuantity min_indep_var,
   const typename UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::IndepQuantity max_indep_var ) const
{
  // Make sure the maximum indep var is valid
  testPrecondition( max_indep_var >= this->getLowerBoundOfIndepVar() );
  testPrecondition( min_indep_var <= this->getUpperBoundOfIndepVar() );

  double random_number = RandomNumberGenerator::getRandomNumber<double>();
  return this->sampleWithRandomNumberInSubrange( random_number,
                                                 min_indep_var,
						                                     max_indep_var );
}

// Return a sample from the distribution at the given CDF value in a subrange
template<typename IndependentUnit, typename DependentUnit>
inline typename UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::sampleWithRandomNumberInSubrange(
  const double random_number,
  const typename UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::IndepQuantity min_indep_var,
  const typename UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::IndepQuantity max_indep_var ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );
  // Make sure the maximum indep var is valid
  testPrecondition( max_indep_var >= this->getLowerBoundOfIndepVar() );
  testPrecondition( min_indep_var <= this->getUpperBoundOfIndepVar() );

  // Compute the scaled random number
  double scaled_random_number =
    random_number*(this->evaluateCDF( max_indep_var )-this->evaluateCDF(min_indep_var))+this->evaluateCDF(min_indep_var);

  size_t dummy_index;

  return this->sampleImplementation( scaled_random_number, dummy_index );
}

// Return a random sample using the random number and record the bin index
template<typename IndependentUnit, typename DependentUnit>
inline typename UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::sampleImplementation(
					    double random_number,
					    size_t& sampled_bin_index ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );

  UnnormCDFQuantity scaled_random_number =
    random_number*Utility::get<2>(d_distribution.back());

  typename DistributionArray::const_iterator bin =
    Search::binaryLowerBound<2>( d_distribution.begin(),
				     d_distribution.end(),
				     scaled_random_number );

  sampled_bin_index = std::distance( d_distribution.begin(), bin );

  return Utility::get<0>(*bin) +
    IndepQuantity((scaled_random_number - Utility::get<2>(*bin))/
                  Utility::get<1>(*bin));
}

// Return the upper bound of the distribution independent variable
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::getUpperBoundOfIndepVar() const
{
  return Utility::get<0>(d_distribution.back());
}

// Return the lower bound of the distribution independent variable
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::getLowerBoundOfIndepVar() const
{
  return Utility::get<0>(d_distribution.front());
}

// Return the distribution type
template<typename IndependentUnit, typename DependentUnit>
UnivariateDistributionType
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::getDistributionType() const
{
  return UnitAwareHistogramDistribution::distribution_type;
}

//! Test if the distribution is continuous
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::isContinuous() const
{
  return true;
}

// Method for placing the object in an output stream
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::toStream(
						       std::ostream& os ) const
{
  std::vector<IndepQuantity> bin_boundaries;
  std::vector<DepQuantity> bin_values;

  this->reconstructOriginalDistribution( bin_boundaries, bin_values );

  this->toStreamDistImpl( os,
                          std::make_pair( "bin boundaries", bin_boundaries ),
                          std::make_pair( "bin values", bin_values ) );
}

// Save the distribution to an archive
template<typename IndependentUnit, typename DependentUnit>
template<typename Archive>
void UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::save( Archive& ar, const unsigned version ) const
{
  // Save the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Save the local member data
  ar & BOOST_SERIALIZATION_NVP( d_distribution );
  ar & BOOST_SERIALIZATION_NVP( d_norm_constant );
}

// Load the distribution from an archive
template<typename IndependentUnit, typename DependentUnit>
template<typename Archive>
void UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::load( Archive& ar, const unsigned version )
{
  // Load the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Load the local member data
  ar & BOOST_SERIALIZATION_NVP( d_distribution );
  ar & BOOST_SERIALIZATION_NVP( d_norm_constant );
}

// Equality comparison operator
template<typename IndependentUnit,typename DependentUnit>
bool UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::operator==( const UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>& other ) const
{
  return d_distribution == other.d_distribution &&
    d_norm_constant == other.d_norm_constant;
}

// Inequality comparison operator
template<typename IndependentUnit,typename DependentUnit>
bool UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::operator!=( const UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>& other ) const
{
  return d_distribution != other.d_distribution ||
    d_norm_constant != other.d_norm_constant;
}  

// Initialize the distribution
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::initializeDistribution(
                        const Utility::ArrayView<const double>& bin_boundaries,
                        const Utility::ArrayView<const double>& bin_values,
                        const bool interpret_dependent_values_as_cdf )
{
  // Make sure that the bin boundaries are sorted
  testPrecondition( Sort::isSortedAscending( bin_boundaries.begin(),
					     bin_boundaries.end() ) );
  // Make sure there is at least one bin
  testPrecondition( bin_boundaries.size() > 1 );
  // Make sure that for n bin boundaries there are n-1 bin values
  testPrecondition( bin_boundaries.size()-1 == bin_values.size() );

  // Convert the raw independent values to quantities
  std::vector<IndepQuantity> bin_boundary_quantities;

  this->convertUnitlessValues( bin_boundaries, bin_boundary_quantities );

  if( interpret_dependent_values_as_cdf )
  {
    this->initializeDistributionFromCDF(
                            Utility::arrayViewOfConst(bin_boundary_quantities),
                            bin_values );
  }
  else
  {
    // Convert the raw bin values to quantities
    std::vector<DepQuantity> bin_quantities;

    this->convertUnitlessValues( bin_values, bin_quantities );

    this->initializeDistribution(
                            Utility::arrayViewOfConst(bin_boundary_quantities),
                            Utility::arrayViewOfConst(bin_quantities) );
  }
}

// Initialize the distribution from a cdf
template<typename IndependentUnit, typename DependentUnit>
template<typename InputIndepQuantity>
void UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::initializeDistributionFromCDF(
            const Utility::ArrayView<const InputIndepQuantity>& bin_boundaries,
            const Utility::ArrayView<const double>& cdf_values )
{
  // Make sure that the bin boundaries are sorted
  testPrecondition( Sort::isSortedAscending( bin_boundaries.begin(),
					     bin_boundaries.end() ) );
  // Make sure that the bin values are sorted
  testPrecondition( Sort::isSortedAscending( cdf_values.begin(),
					     cdf_values.end() ) );
  // Make sure there is at least one bin
  testPrecondition( bin_boundaries.size() > 1 );
  // Make sure that for n bin boundaries there are n-1 bin values
  testPrecondition( bin_boundaries.size()-1 == cdf_values.size() );

  // Resize the distribution
  d_distribution.resize( bin_boundaries.size() );

  // Assign the first cdf value
  Utility::get<0>(d_distribution[0]) = IndepQuantity( bin_boundaries[0] );
  setQuantity( Utility::get<2>(d_distribution[0]), 0.0 );

    // Assign the distribution
    for( size_t i = 1; i < bin_boundaries.size(); ++i )
    {
      Utility::get<0>(d_distribution[i]) =
        IndepQuantity( bin_boundaries[i] );
      
      setQuantity( Utility::get<2>(d_distribution[i]), cdf_values[i-1] );

      // Calculate the pdf from the cdf
      Utility::get<1>(d_distribution[i-1]) =
        DepQuantity( (Utility::get<2>(d_distribution[i]) -
                      Utility::get<2>(d_distribution[i-1]))/
		     (Utility::get<0>(d_distribution[i]) -
                      Utility::get<0>(d_distribution[i-1])) );
    }

    // Last PDF value is unused and can be assigned to the second to last value
    Utility::get<1>(d_distribution.back()) =
      Utility::get<1>(d_distribution[d_distribution.size()-2]);

    // Set normalization constant
    d_norm_constant = 1.0/Utility::get<2>(d_distribution.back());
}

// Initialize the distribution
template<typename IndependentUnit, typename DependentUnit>
template<typename InputIndepQuantity, typename InputDepQuantity>
void UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::initializeDistribution(
            const Utility::ArrayView<const InputIndepQuantity>& bin_boundaries,
            const Utility::ArrayView<const InputDepQuantity>& bin_values )
{
  // Make sure that the bin boundaries are sorted
  testPrecondition( Sort::isSortedAscending( bin_boundaries.begin(),
					     bin_boundaries.end() ) );
  // Make sure there is at least one bin
  testPrecondition( bin_boundaries.size() > 1 );
  // Make sure that for n bin boundaries there are n-1 bin values
  testPrecondition( bin_boundaries.size()-1 == bin_values.size() );

  // Resize the distribution
  d_distribution.resize( bin_boundaries.size() );

  // Construct the distribution
  for( size_t i = 0; i < bin_boundaries.size(); ++i )
  {
    // Assign the min and max bin boundaries (respectively)
    Utility::get<0>(d_distribution[i]) =
      IndepQuantity( bin_boundaries[i] );

    // Assign the bin PDF value
    if( i < bin_boundaries.size() - 1 )
      Utility::get<1>(d_distribution[i]) = DepQuantity( bin_values[i] );
    else
      Utility::get<1>(d_distribution[i]) = DepQuantity( bin_values[i-1] );

    // Assign the discrete CDF value
    if( i > 0 )
    {
      Utility::get<2>(d_distribution[i]) =
        Utility::get<2>(d_distribution[i-1]);

      Utility::get<2>(d_distribution[i]) += DepQuantity( bin_values[i-1] )*
        IndepQuantity( Utility::get<0>(d_distribution[i]) -
                       Utility::get<0>(d_distribution[i-1]) );
    }
    else
      setQuantity( Utility::get<2>(d_distribution[i]), 0.0 );
  }

  // Assign the normalization constant
  d_norm_constant = 1.0/Utility::get<2>(d_distribution.back());
}

// Reconstruct original distribution
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::reconstructOriginalDistribution(
			 std::vector<IndepQuantity>& bin_boundaries,
			 std::vector<DepQuantity>& bin_values ) const
{
  // Resize the arrays
  if( d_distribution.size() > 0 )
    bin_boundaries.resize( d_distribution.size() );
  else
    bin_boundaries.clear();

  if( d_distribution.size() > 1 )
    bin_values.resize( d_distribution.size()-1 );
  else
    bin_values.clear();
  
  for( size_t i = 0u; i < d_distribution.size(); ++i )
  {
    bin_boundaries[i] = Utility::get<0>(d_distribution[i]);

    if( i < d_distribution.size() - 1 )
      bin_values[i] = Utility::get<1>(d_distribution[i]);
  }
}

// Reconstruct original distribution w/o units
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::reconstructOriginalUnitlessDistribution(
			      std::vector<double>& bin_boundaries,
			      std::vector<double>& bin_values ) const
{
  // Resize the arrays
  if( d_distribution.size() > 0 )
    bin_boundaries.resize( d_distribution.size() );
  else
    bin_boundaries.clear();

  if( d_distribution.size() > 1 )
    bin_values.resize( d_distribution.size()-1 );
  else
    bin_values.clear();

  for( size_t i = 0u; i < d_distribution.size(); ++i )
  {
    bin_boundaries[i] =
      Utility::getRawQuantity( Utility::get<0>(d_distribution[i]) );

    if( i < d_distribution.size() - 1 )
    {
      bin_values[i] =
        Utility::getRawQuantity( Utility::get<1>(d_distribution[i]) );
    }
  }
}

// Convert the unitless values to the correct units
template<typename IndependentUnit, typename DependentUnit>
template<typename Quantity>
void UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::convertUnitlessValues(
                       const Utility::ArrayView<const double>& unitless_values,
                       std::vector<Quantity>& quantities )
{
  // Resize the quantity array
  quantities.resize( unitless_values.size() );

  // Copy the bin boundaries
  for( size_t i = 0u; i < unitless_values.size(); ++i )
    setQuantity( quantities[i], unitless_values[i] );
}

// Test if the dependent variable can be zero within the indep bounds
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::canDepVarBeZeroInIndepBounds() const
{
  bool possible_zero = false;
  
  for( size_t i = 0; i < d_distribution.size(); ++i )
  {
    if( Utility::get<1>(d_distribution[i]) == DQT::zero() )
    {
      possible_zero = true;

      break;
    }
  }

  return possible_zero;
}

// Verify that the values are valid
template<typename IndependentUnit, typename DependentUnit>
template<typename InputIndepQuantity, typename InputDepQuantity>
void UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::verifyValidValues(
            const Utility::ArrayView<const InputIndepQuantity>& bin_boundaries,
            const Utility::ArrayView<const InputDepQuantity>& bin_values,
            const bool cdf_bin_values )
{
  TEST_FOR_EXCEPTION( bin_boundaries.size() <= 1,
                      Utility::BadUnivariateDistributionParameter,
                      "The histogram distribution cannot be constructed "
                      "because no full bins have been specified!" );
  
  TEST_FOR_EXCEPTION( !Sort::isSortedAscending( bin_boundaries.begin(),
						bin_boundaries.end() ),
		      Utility::BadUnivariateDistributionParameter,
		      "The histogram distribution cannot be "
		      "constructed because the bin boundaries "
		      << bin_boundaries << " are not sorted!" );

  typedef Utility::QuantityTraits<InputIndepQuantity> InputIQT;
  
  TEST_FOR_EXCEPTION( InputIQT::isnaninf( bin_boundaries.front() ),
                      Utility::BadUnivariateDistributionParameter,
                      "The histogram distribution cannot be constructed "
                      "because the first bin boundary is invalid!" );

  TEST_FOR_EXCEPTION( InputIQT::isnaninf( bin_boundaries.back() ),
                      Utility::BadUnivariateDistributionParameter,
                      "The histogram distribution cannot be constructed "
                      "because the last bin boundary is invalid!" );

  TEST_FOR_EXCEPTION( bin_boundaries.size() != bin_values.size()+1,
		      Utility::BadUnivariateDistributionParameter,
		      "The histogram distribution cannot be constructed "
                      "because the number of bin boundaries ("
                      << bin_boundaries.size() << ") does not match the "
                      "number of bin values plus 1 ("
                      << bin_values.size() + 1 << ")!" );

  if( cdf_bin_values )
  {
    TEST_FOR_EXCEPTION( !Sort::isSortedAscending( bin_values.begin(),
                                                  bin_values.end() ),
                        Utility::BadUnivariateDistributionParameter,
                        "The histogram distribution cannot be "
                        "constructed because the bin cdf values "
                        " are not sorted!" );

    // typename Utility::ArrayView<const InputDepQuantity>::const_iterator repeat_bin_value =
    //   std::adjacent_find( bin_values.begin(), bin_values.end() );
    
    // TEST_FOR_EXCEPTION( repeat_bin_value != bin_values.end(),
    //                     Utility::BadUnivariateDistributionParameter,
    //                     "The histogram distribution cannot be "
    //                     "constructed because there is a repeated bin cdf "
    //                     "value at index "
    //                     << std::distance( bin_values.begin(), repeat_bin_value ) <<
    //                     " (" << *repeat_bin_value << ")!" );
  }

  typedef Utility::QuantityTraits<InputDepQuantity> InputDQT;
  
  typename Utility::ArrayView<const InputDepQuantity>::const_iterator bad_bin_value =
    std::find_if( bin_values.begin(),
                  bin_values.end(),
                  [](const InputDepQuantity& element){ return InputDQT::isnaninf( element ) || element < InputDQT::zero(); } );

  TEST_FOR_EXCEPTION(  bad_bin_value != bin_values.end(),
                       Utility::BadUnivariateDistributionParameter,
                       "The histogram distribution cannot be constructed "
                       "because the bin value at index "
                         << std::distance( bin_values.begin(), bad_bin_value ) <<
                       " (" << *bad_bin_value << ") is not valid!" );
}

} // end Utility namespace

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareHistogramDistribution<void,void> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Utility, UnitAwareHistogramDistribution<void,void> );

#endif // end UTILITY_HISTOGRAM_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_HistogramDistribution_def.hpp
//---------------------------------------------------------------------------//
