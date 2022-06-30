//---------------------------------------------------------------------------//
//!
//! \file   Utility_TabularDistribution_def.hpp
//! \author Alex Robinson
//! \brief  Tabular distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TABULAR_DISTRIBUTION_DEF_HPP
#define UTILITY_TABULAR_DISTRIBUTION_DEF_HPP

// FRENSIE Includes
#include "Utility_DataProcessor.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_Vector.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_DesignByContract.hpp"

BOOST_SERIALIZATION_CLASS3_EXPORT_IMPLEMENT( UnitAwareTabularDistribution, Utility );

namespace Utility{

// Basic constructor (potentially dangerous)
/*! \details The independent values are assumed to be sorted (lowest to
 * highest). If cdf values are provided a pdf will be calculated. Because
 * information is lost when converting from a pdf to a cdf, only a first order
 * approximation of the pdf will be calculated. Evaluate the resulting
 * distribution with caution (there will be no difference when sampling from
 * the distribution)!
 */
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::UnitAwareTabularDistribution(
		  const std::vector<double>& independent_values,
		  const std::vector<double>& dependent_values )
  : UnitAwareTabularDistribution( Utility::arrayViewOfConst(independent_values),
                                  Utility::arrayViewOfConst(dependent_values) )
{ /* ... */ }

// Basic view constructor (potentially dangerous)
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::UnitAwareTabularDistribution(
                    const Utility::ArrayView<const double>& independent_values,
                    const Utility::ArrayView<const double>& dependent_values )
  : d_distribution( independent_values.size() ),
    d_norm_constant( DNQT::zero() )
{
  // Make sure there is at lease one bin

  testPrecondition( independent_values.size() > 1 );
  testPrecondition( dependent_values.size() == independent_values.size() );
  // Make sure that the bins are sorted
  testPrecondition( Sort::isSortedAscending( independent_values.begin(),
					     independent_values.end() ) );
  // Verify that the values are valid
  this->verifyValidValues( independent_values, dependent_values );

  this->initializeDistributionFromRawData( independent_values,
                                           dependent_values );

  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Constructor
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
template<typename InputIndepQuantity, typename InputDepQuantity>
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::UnitAwareTabularDistribution(
		  const std::vector<InputIndepQuantity>& independent_values,
		  const std::vector<InputDepQuantity>& dependent_values )
  : UnitAwareTabularDistribution( Utility::arrayViewOfConst( independent_values ),
                                  Utility::arrayViewOfConst( dependent_values ) )
{ /* ... */ }

// View constructor
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
template<typename InputIndepQuantity, typename InputDepQuantity>
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::UnitAwareTabularDistribution(
        const Utility::ArrayView<const InputIndepQuantity>& independent_values,
        const Utility::ArrayView<const InputDepQuantity>& dependent_values )
  : d_distribution( independent_values.size() ),
    d_norm_constant( DNQT::zero() )
{
  // Verify that the values are valid
  this->verifyValidValues( independent_values, dependent_values );

  this->initializeDistribution( independent_values, dependent_values );

  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Copy constructor
/*! \details Just like boost::units::quantity objects, the unit-aware
 * distribution can be explicitly cast to a distribution with compatible
 * units. If the units are not compatible, this function will not compile. Note
 * that this allows distributions to be scaled safely (unit conversions
 * are completely taken care of by boost::units)!
 */
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
template<typename InputIndepUnit, typename InputDepUnit>
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::UnitAwareTabularDistribution(
 const UnitAwareTabularDistribution<InterpolationPolicy,InputIndepUnit,InputDepUnit>& dist_instance )
  : d_distribution(),
    d_norm_constant()
{
  typedef typename UnitAwareTabularDistribution<InterpolationPolicy,InputIndepUnit,InputDepUnit>::IndepQuantity InputIndepQuantity;

  typedef typename UnitAwareTabularDistribution<InterpolationPolicy,InputIndepUnit,InputDepUnit>::DepQuantity InputDepQuantity;

  // Reconstruct the original input distribution
  std::vector<InputIndepQuantity> input_indep_values;
  std::vector<InputDepQuantity> input_dep_values;

  dist_instance.reconstructOriginalDistribution( input_indep_values,
                                                 input_dep_values );

  this->initializeDistribution( Utility::arrayViewOfConst(input_indep_values),
                                Utility::arrayViewOfConst(input_dep_values) );

  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Copy constructor (copying from unitless distribution only)
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::UnitAwareTabularDistribution( const UnitAwareTabularDistribution<InterpolationPolicy,void,void>& unitless_dist_instance, int )
  : d_distribution(),
    d_norm_constant()
{
  // Reconstruct the original input distribution
  std::vector<double> input_indep_values, input_dep_values;

  unitless_dist_instance.reconstructOriginalDistribution( input_indep_values,
                                                          input_dep_values );

  this->initializeDistributionFromRawData(
                                 Utility::arrayViewOfConst(input_indep_values),
                                 Utility::arrayViewOfConst(input_dep_values) );

  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Construct distribution from a unitless dist. (potentially dangerous)
/*! \details Constructing a unit-aware distribution from a unitless
 * distribution is potentially dangerous. By forcing users to construct objects
 * using this method instead of a standard constructor we are trying to make
 * sure users are aware of the danger. This is designed to mimic the interface
 * of the boost::units::quantity, which also has to deal with this issue.
 */
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::fromUnitlessDistribution( const UnitAwareTabularDistribution<InterpolationPolicy,void,void>& unitless_distribution )
{
  return ThisType( unitless_distribution, 0 );
}

// Assignment operator
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>&
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::operator=(
  const UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>& dist_instance )
{
  if( this != &dist_instance )
  {
    d_distribution = dist_instance.d_distribution;
    d_norm_constant = dist_instance.d_norm_constant;
  }

  return *this;
}

// Evaluate the distribution
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::DepQuantity
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::evaluate(
 const typename UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  if( indep_var_value < Utility::get<0>(d_distribution.front()) )
    return DQT::zero();
  else if( indep_var_value > Utility::get<0>(d_distribution.back()) )
    return DQT::zero();
  else if( indep_var_value == Utility::get<0>(d_distribution.back()) )
    return Utility::get<2>(d_distribution.back());
  else
  {
    typename DistributionArray::const_iterator start, end, lower_bin_boundary,
      upper_bin_boundary;
    start = d_distribution.begin();
    end = d_distribution.end();

    lower_bin_boundary = Search::binaryLowerBound<0>( start,
                                                      end,
                                                      indep_var_value );

    upper_bin_boundary = lower_bin_boundary;
    ++upper_bin_boundary;

    IndepQuantity lower_indep_value = Utility::get<0>(*lower_bin_boundary);
    DepQuantity lower_dep_value = Utility::get<2>(*lower_bin_boundary);
    IndepQuantity upper_indep_value = Utility::get<0>(*upper_bin_boundary);
    DepQuantity upper_dep_value = Utility::get<2>(*upper_bin_boundary);

    return InterpolationPolicy::interpolate( lower_indep_value,
                                             upper_indep_value,
                                             indep_var_value,
                                             lower_dep_value,
                                             upper_dep_value );
  }
}

// Evaluate the PDF
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::InverseIndepQuantity
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::evaluatePDF(
 const typename UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  return this->evaluate( indep_var_value )*d_norm_constant;
}

// Evaluate the CDF
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
double UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::evaluateCDF(
  const typename UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  if( indep_var_value < Utility::get<0>(d_distribution.front()) )
    return 0.0;
  else if( indep_var_value >= Utility::get<0>(d_distribution.back()) )
    return 1.0;
  else
  {
    typename DistributionArray::const_iterator start, end, lower_bin_boundary;
    start = d_distribution.begin();
    end = d_distribution.end();

    lower_bin_boundary = Search::binaryLowerBound<0>( start,
                                                      end,
                                                      indep_var_value );
    IndepQuantity indep_diff =
      indep_var_value - Utility::get<0>(*lower_bin_boundary);

    return (Utility::get<1>(*lower_bin_boundary) +
            indep_diff*Utility::get<2>(*lower_bin_boundary) +
	    indep_diff*indep_diff*
            Utility::get<3>(*lower_bin_boundary)/2.0)*d_norm_constant;
  }
}

// Return a random sample from the distribution
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
inline typename UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sample() const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  size_t dummy_index;

  return this->sampleImplementation( random_number, dummy_index );
}

// Return a random sample and record the number of trials
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sampleAndRecordTrials(
                                    DistributionTraits::Counter& trials ) const
{
  ++trials;

  return this->sample();
}

// Return a random sample and bin index from the distribution
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sampleAndRecordBinIndex(
					    size_t& sampled_bin_index ) const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleImplementation( random_number, sampled_bin_index );
}

// Return a sample from the distribution at the given CDF value
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sampleWithRandomNumber(
                                             const double random_number ) const
{
  size_t dummy_index;

  return this->sampleImplementation( random_number, dummy_index );
}

// Return a random sample from the corresponding CDF in a subrange
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sampleInSubrange(
 const typename UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity max_indep_var ) const
{
  // Make sure the maximum indep var is valid
  testPrecondition( max_indep_var >= this->getLowerBoundOfIndepVar() );

  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleWithRandomNumberInSubrange( random_number,
                                                 max_indep_var );
}

// Return a random sample from the distribution at the given CDF value in a subrange
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
inline typename UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sampleWithRandomNumberInSubrange(
 const double random_number,
 const typename UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity max_indep_var ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );
  // Make sure the maximum indep var is valid
  testPrecondition( max_indep_var >= this->getLowerBoundOfIndepVar() );

  // Calculate a scaled random number
  double scaled_random_number =
    random_number*this->evaluateCDF( max_indep_var );

  size_t dummy_index;

  return this->sampleImplementation( scaled_random_number, dummy_index );
}

// Return a random sample using the random number and record the bin index
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sampleImplementation(
					    double random_number,
					    size_t& sampled_bin_index ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );

  // Scale the random number
  UnnormCDFQuantity scaled_random_number = random_number*
    Utility::get<1>(d_distribution.back());

  typename DistributionArray::const_iterator start, end, lower_bin_boundary;
  start = d_distribution.begin();
  end = d_distribution.end();

  lower_bin_boundary = Search::binaryLowerBound<1>( start,
                                                    end,
                                                    scaled_random_number);

  // Calculate the sampled bin index
  sampled_bin_index = std::distance(d_distribution.begin(),lower_bin_boundary);

  // Calculate the sampled independent value
  IndepQuantity sample;

  IndepQuantity indep_value = Utility::get<0>(*lower_bin_boundary);
  UnnormCDFQuantity cdf_diff =
    scaled_random_number - Utility::get<1>(*lower_bin_boundary);
  DepQuantity pdf_value = Utility::get<2>(*lower_bin_boundary);
  SlopeQuantity slope = Utility::get<3>(*lower_bin_boundary);

  // x = x0 + [sqrt(pdf(x0)^2 + 2m[cdf(x)-cdf(x0)]) - pdf(x0)]/m
  if( slope != QuantityTraits<SlopeQuantity>::zero() )
  {
    typedef typename QuantityTraits<DepQuantity>::template GetQuantityToPowerType<2>::type DepQuantitySqr;

    DepQuantitySqr term_1 = pdf_value*pdf_value;
    DepQuantitySqr term_2( 2.0*slope*cdf_diff );

    IndepQuantity term_3((Utility::sqrt( term_1 + term_2 ) - pdf_value)/slope);

    sample = indep_value + term_3;

  }
  // x = x0 + [cdf(x)-cdf(x0)]/pdf(x0) => L'Hopital's rule
  else
  {
    IndepQuantity term_2( cdf_diff/pdf_value );

    sample =  indep_value + term_2;
  }

  // Make sure the sample is valid
  testPostcondition( !IQT::isnaninf( sample ) );
  testPostcondition( sample >= this->getLowerBoundOfIndepVar() );
  testPostcondition( sample <= this->getUpperBoundOfIndepVar() );

  return sample;
}

// Return the upper bound of the distribution independent variable
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::getUpperBoundOfIndepVar() const
{
  return Utility::get<0>(d_distribution.back());
}

// Return the lower bound of the distribution independent variable
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::getLowerBoundOfIndepVar() const
{
  return Utility::get<0>(d_distribution.front());
}

// Return the distribution type
template<typename InterpolationPolicy,
	 typename IndependentUnit,
	 typename DependentUnit>
UnivariateDistributionType
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::getDistributionType() const
{
  return ThisType::distribution_type;
}

// Test if the distribution is continuous
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
bool UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::isContinuous() const
{
  return true;
}

// Method for placing the object in an output stream
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
void UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::toStream(
                                                       std::ostream& os ) const
{
  std::vector<IndepQuantity> independent_values;
  std::vector<DepQuantity> dependent_values;

  this->reconstructOriginalDistribution( independent_values,
                                         dependent_values );

  this->toStreamDistImpl( os,
                          std::make_pair( "interp", InterpolationPolicy::name() ),
                          std::make_pair( "independent values", independent_values ),
                          std::make_pair( "dependent values", dependent_values ) );
}

// Save the distribution to an archive
template<typename InterpolationPolicy,
	 typename IndependentUnit,
	 typename DependentUnit>
template<typename Archive>
void UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::save( Archive& ar, const unsigned version ) const
{
  // Save the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Save the local member data
  ar & BOOST_SERIALIZATION_NVP( d_distribution );
  ar & BOOST_SERIALIZATION_NVP( d_norm_constant );
}

// Load the distribution from an archive
template<typename InterpolationPolicy,
	 typename IndependentUnit,
	 typename DependentUnit>
template<typename Archive>
void UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::load( Archive& ar, const unsigned version )
{
  // Load the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Load the local member data
  ar & BOOST_SERIALIZATION_NVP( d_distribution );
  ar & BOOST_SERIALIZATION_NVP( d_norm_constant );
}

// Method for testing if two objects are equivalent
template<typename InterpolationPolicy,
	 typename IndependentUnit,
	 typename DependentUnit>
bool UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::operator==(
 const UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>& other ) const
{
  return d_distribution == other.d_distribution &&
    d_norm_constant == other.d_norm_constant;
}

// Method for testing if two objects are different
template<typename InterpolationPolicy,
	 typename IndependentUnit,
	 typename DependentUnit>
bool UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::operator!=(
 const UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>& other ) const
{
  return d_distribution != other.d_distribution ||
    d_norm_constant != other.d_norm_constant;
}

// Initialize the distribution
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
void UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::initializeDistributionFromRawData(
                    const Utility::ArrayView<const double>& independent_values,
                    const Utility::ArrayView<const double>& dependent_values )
{
  // Make sure there is at least one bin
  testPrecondition( independent_values.size() > 1 );
  testPrecondition( dependent_values.size() == independent_values.size() );

  // Convert the raw independent values to quantities
  std::vector<IndepQuantity> independent_quantities;

  this->convertUnitlessValues( independent_values, independent_quantities );

  // Convert the raw dependent values to quantities
  std::vector<DepQuantity> dependent_quantities;

  this->convertUnitlessValues( dependent_values, dependent_quantities );

  this->initializeDistribution( Utility::arrayViewOfConst( independent_quantities ),
                                Utility::arrayViewOfConst( dependent_quantities ) );
}

// Initialize the distribution
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
template<typename InputIndepQuantity, typename InputDepQuantity>
void UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::initializeDistribution(
        const Utility::ArrayView<const InputIndepQuantity>& independent_values,
        const Utility::ArrayView<const InputDepQuantity>& dependent_values )
{
  // Make sure that at least two points of the distribution are specified
  testPrecondition( independent_values.size() > 1 );
  // Make sure that every independent value has a dependent value
  testPrecondition( independent_values.size() == dependent_values.size() );
  // Make sure that the independent values are sorted
  testPrecondition( Sort::isSortedAscending( independent_values.begin(),
                                             independent_values.end() ) );

  // Resize the distribution
  d_distribution.resize( independent_values.size() );

  // Assign the raw distribution data
  for( size_t i = 0; i < independent_values.size(); ++i )
  {
    Utility::get<0>(d_distribution[i]) =
      IndepQuantity( independent_values[i] );
    Utility::get<2>(d_distribution[i]) =
      DepQuantity( dependent_values[i] );
  }

  // Create a CDF from the raw distribution data
  d_norm_constant =
    DataProcessor::calculateContinuousCDF<0,2,1>( d_distribution, false );

  // Calculate the slopes of the PDF
  DataProcessor::calculateSlopes<0,2,3>( d_distribution );
}

// Reconstruct original distribution
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
void UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::reconstructOriginalDistribution(
			 std::vector<IndepQuantity>& independent_values,
			 std::vector<DepQuantity>& dependent_values ) const
{
  // Resize the arrays
  independent_values.resize( d_distribution.size() );
  dependent_values.resize( d_distribution.size() );

  for( size_t i = 0u; i < d_distribution.size(); ++i )
  {
    independent_values[i] = Utility::get<0>(d_distribution[i]);

    dependent_values[i] = Utility::get<2>(d_distribution[i]);
  }
}

// Reconstruct original distribution w/o units
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
void UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::reconstructOriginalUnitlessDistribution(
			       std::vector<double>& independent_values,
			       std::vector<double>& dependent_values ) const
{
  // Resize the arrays
  independent_values.resize( d_distribution.size() );
  dependent_values.resize( d_distribution.size() );

  for( size_t i = 0u; i < d_distribution.size(); ++i )
  {
    independent_values[i] =
      getRawQuantity( Utility::get<0>(d_distribution[i]) );

    dependent_values[i] =
      getRawQuantity( Utility::get<2>(d_distribution[i]) );
  }
}

// Convert the unitless values to the correct units
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
template<typename Quantity>
void UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::convertUnitlessValues(
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
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
bool UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::canDepVarBeZeroInIndepBounds() const
{
  bool possible_zero = false;

  for( size_t i = 0; i < d_distribution.size(); ++i )
  {
    if( Utility::get<2>(d_distribution[i]) == DQT::zero() )
    {
      possible_zero = true;

      break;
    }
  }

  return possible_zero;
}

// // Test if the independent variable is compatible with Lin processing
// template<typename InterpolationPolicy,
//          typename IndependentUnit,
//          typename DependentUnit>
// bool UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::isIndepVarCompatibleWithProcessingType(
//                                          const LinIndepVarProcessingTag ) const
// {
//   return boost::is_same<typename InterpolationPolicy::IndepVarProcessingTag,LinIndepVarProcessingTag>::value;
// }

// // Test if the independent variable is compatible with Log processing
// template<typename InterpolationPolicy,
//          typename IndependentUnit,
//          typename DependentUnit>
// bool UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::isIndepVarCompatibleWithProcessingType(
//                                          const LogIndepVarProcessingTag ) const
// {
//   return boost::is_same<typename InterpolationPolicy::IndepVarProcessingTag,LogIndepVarProcessingTag>::value;
// }

// // Test if the dependent variable is compatible with Lin processing
// template<typename InterpolationPolicy,
//          typename IndependentUnit,
//          typename DependentUnit>
// bool UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::isDepVarCompatibleWithProcessingType(
//                                            const LinDepVarProcessingTag ) const
// {
//   return boost::is_same<typename InterpolationPolicy::DepVarProcessingTag,LinDepVarProcessingTag>::value;
// }

// // Test if the dependent variable is compatible with Log processing
// template<typename InterpolationPolicy,
//          typename IndependentUnit,
//          typename DependentUnit>
// bool UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::isDepVarCompatibleWithProcessingType(
//                                            const LogDepVarProcessingTag ) const
// {
//   return boost::is_same<typename InterpolationPolicy::DepVarProcessingTag,LogDepVarProcessingTag>::value;
// }

// Verify that the values are valid
template<typename InterpolationPolicy,
	 typename IndependentUnit,
	 typename DependentUnit>
template<typename InputIndepQuantity, typename InputDepQuantity>
void UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::verifyValidValues(
        const Utility::ArrayView<const InputIndepQuantity>& independent_values,
        const Utility::ArrayView<const InputDepQuantity>& dependent_values )
{
  // There must be at least two independent values
  TEST_FOR_EXCEPTION( independent_values.size() < 2,
                      Utility::StringConversionException,
                      "The tabular distribution cannot be constructed "
                      "because there aren't enough independent values "
                      "specified!" );

  // The independent values must be sorted
  TEST_FOR_EXCEPTION( !Sort::isSortedAscending( independent_values.begin(),
						independent_values.end() ),
		      Utility::StringConversionException,
		      "The tabular distribution cannot be constructed "
		      "because the independent values are not sorted!" );

  typedef Utility::QuantityTraits<InputIndepQuantity> InputIQT;

  TEST_FOR_EXCEPTION( InputIQT::isnaninf( independent_values.front() ),
                      Utility::StringConversionException,
                      "The tabular distribution cannot be constructed "
                      "because the first independent value is invalid!" );

  TEST_FOR_EXCEPTION( InputIQT::isnaninf( independent_values.back() ),
                      Utility::StringConversionException,
                      "The tabular distribution cannot be constructed "
                      "because the last independent value is invalid!" );

  // Make sure that the independent values are compatible with the
  // interpolation type
  TEST_FOR_EXCEPTION( !InterpolationPolicy::isIndepVarInValidRange( independent_values.front() ),
                      Utility::StringConversionException,
                      "The tabular distribution cannot be constructed "
                      "because the independent values are not within the "
                      "range supported by "
                      << boost::algorithm::to_lower_copy( InterpolationPolicy::name() ) <<
                      " interpolation!" );

  // There must be a dependent value for every independent value specified
  TEST_FOR_EXCEPTION( independent_values.size() != dependent_values.size(),
		      Utility::StringConversionException,
		      "The tabular distribution cannot be constructed "
                      "because the number of independent values ("
                      << independent_values.size() << ") does not "
                      "equal the number of dependent values ("
                      << dependent_values.size() << ")!" );

  typedef Utility::QuantityTraits<InputDepQuantity> InputDQT;

  // Search for bad dependent values
  typename Utility::ArrayView<const InputDepQuantity>::const_iterator bad_dependent_value =
    std::find_if( dependent_values.begin(),
                  dependent_values.end(),
                  [](const InputDepQuantity& element){ return element < InputDQT::zero() || InputDQT::isnaninf( element ) || !InterpolationPolicy::isDepVarInValidRange( element ); } );

  TEST_FOR_EXCEPTION( bad_dependent_value != dependent_values.end(),
                      Utility::StringConversionException,
                      "The tabular distribution cannot be constructed "
                      "because the dependent value at index "
                      << std::distance( dependent_values.begin(), bad_dependent_value ) <<
                      " (" << *bad_dependent_value << ") is not valid!" );
}

} // end Utility namespace

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareTabularDistribution<Utility::LinLin,void,void> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Utility, UnitAwareTabularDistribution<Utility::LinLin,void,void> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareTabularDistribution<Utility::LinLog,void,void> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Utility, UnitAwareTabularDistribution<Utility::LinLog,void,void> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareTabularDistribution<Utility::LogLin,void,void> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Utility, UnitAwareTabularDistribution<Utility::LogLin,void,void> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareTabularDistribution<Utility::LogLog,void,void> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Utility, UnitAwareTabularDistribution<Utility::LogLog,void,void> );

#endif // end Utility_TabularDistribution_def.hpp

//---------------------------------------------------------------------------//
// end Utility_TabularDistribution_def.hpp
//---------------------------------------------------------------------------//
