//---------------------------------------------------------------------------//
//!
//! \file   Utility_TabularCDFDistribution_def.hpp
//! \author Luke Kersting
//! \brief  Tabular CDF distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TABULAR_CDF_DISTRIBUTION_DEF_HPP
#define UTILITY_TABULAR_CDF_DISTRIBUTION_DEF_HPP

// FRENSIE Includes
#include "Utility_DataProcessor.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_DesignByContract.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"

BOOST_SERIALIZATION_CLASS3_EXPORT_IMPLEMENT( UnitAwareTabularCDFDistribution, Utility );

namespace Utility{

// Default constructor
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::UnitAwareTabularCDFDistribution()
{
  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Basic constructor (potentially dangerous)
/*! \details The independent values are assumed to be sorted (lowest to
 * highest). If cdf values are provided the pdf will not be calculated.
 * Evaluating the distribution or the pdf will always return a result zero!
 */
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::UnitAwareTabularCDFDistribution(
                  const std::vector<double>& independent_values,
                  const std::vector<double>& dependent_values,
                  const bool interpret_dependent_values_as_cdf )
  : UnitAwareTabularCDFDistribution( Utility::arrayViewOfConst( independent_values ),
                                     Utility::arrayViewOfConst( dependent_values ),
                                     interpret_dependent_values_as_cdf )
{ /* ... */ }

// Basic view constructor (potentially dangerous)
/*! \details The independent values are assumed to be sorted (lowest to
 * highest). If cdf values are provided the pdf will not be calculated.
 * Evaluating the distribution or the pdf will always return a result zero!
 */
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::UnitAwareTabularCDFDistribution(
                    const Utility::ArrayView<const double>& independent_values,
                    const Utility::ArrayView<const double>& dependent_values,
                    const bool interpret_dependent_values_as_cdf )
  : d_distribution( independent_values.size() ),
    d_norm_constant( DNQT::zero() ),
    d_interpret_dependent_values_as_cdf( interpret_dependent_values_as_cdf )
{
  // Verify that the values are valid
  this->verifyValidValues( independent_values, dependent_values );

  this->initializeDistributionFromRawData( independent_values,
                                           dependent_values );

  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// CDF constructor
/*! \details The independent values are assumed to be sorted (lowest to
 * highest). Since cdf values are provided the pdf will not be calculated.
 * Evaluating the distribution or the pdf will always return a result zero!
 */
template<typename InterpolationPolicy,
typename IndependentUnit,
typename DependentUnit>
template<typename InputIndepQuantity>
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::UnitAwareTabularCDFDistribution(
const std::vector<InputIndepQuantity>& independent_values,
const std::vector<double>& cdf_values )
  : UnitAwareTabularCDFDistribution( Utility::arrayViewOfConst( independent_values ),
                                     Utility::arrayViewOfConst( cdf_values ) )
{ /* ... */ }

// CDF view constructor
/*! \details The independent values are assumed to be sorted (lowest to
 * highest). Since cdf values are provided the pdf will not be calculated.
 * Evaluating the distribution or the pdf will always return a result zero!
 */
template<typename InterpolationPolicy,
typename IndependentUnit,
typename DependentUnit>
template<typename InputIndepQuantity>
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::UnitAwareTabularCDFDistribution(
        const Utility::ArrayView<const InputIndepQuantity>& independent_values,
        const Utility::ArrayView<const double>& cdf_values )
  : d_distribution( independent_values.size() ),
    d_norm_constant( DNQT::zero() ),
    d_interpret_dependent_values_as_cdf( true )
{
  // Verify that the values are valid
  this->verifyValidValues( independent_values, cdf_values );

  this->initializeDistributionFromCDF( independent_values, cdf_values );

  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Constructor
/*! \details The independent values are assumed to be sorted (lowest to
 * highest). The pdf will be used to calculate the cdf.
 * Evaluating the distribution or the pdf will always return a result zero!
 */
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
template<typename InputIndepQuantity, typename InputDepQuantity>
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::UnitAwareTabularCDFDistribution(
                  const std::vector<InputIndepQuantity>& independent_values,
                  const std::vector<InputDepQuantity>& dependent_values )
  : UnitAwareTabularCDFDistribution( Utility::arrayViewOfConst( independent_values ),
                                     Utility::arrayViewOfConst( dependent_values ) )
{ /* ... */ }

// View constructor
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
template<typename InputIndepQuantity, typename InputDepQuantity>
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::UnitAwareTabularCDFDistribution(
        const Utility::ArrayView<const InputIndepQuantity>& independent_values,
        const Utility::ArrayView<const InputDepQuantity>& dependent_values )
  : d_distribution( independent_values.size() ),
    d_norm_constant( DNQT::zero() ),
    d_interpret_dependent_values_as_cdf( false )
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
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::UnitAwareTabularCDFDistribution(
 const UnitAwareTabularCDFDistribution<InterpolationPolicy,InputIndepUnit,InputDepUnit>& dist_instance )
  : d_distribution(),
    d_norm_constant(),
    d_interpret_dependent_values_as_cdf( dist_instance.wasConstructedFromCDF() )
{
  typedef typename UnitAwareTabularCDFDistribution<InterpolationPolicy,InputIndepUnit,InputDepUnit>::IndepQuantity InputIndepQuantity;

  typedef typename UnitAwareTabularCDFDistribution<InterpolationPolicy,InputIndepUnit,InputDepUnit>::DepQuantity InputDepQuantity;


  // Reconstruct the original input distribution
  std::vector<InputIndepQuantity> input_indep_values;

  if( d_interpret_dependent_values_as_cdf )
  {
    std::vector<double> input_cdf_values;

    dist_instance.reconstructOriginalCDFDistribution( input_indep_values,
                                                      input_cdf_values );

    this->initializeDistributionFromCDF(
                                 Utility::arrayViewOfConst(input_indep_values),
                                 Utility::arrayViewOfConst(input_cdf_values) );
  }
  else
  {
    std::vector<InputDepQuantity> input_dep_values;

    dist_instance.reconstructOriginalDistribution( input_indep_values,
                                                   input_dep_values );

    this->initializeDistribution(
                                 Utility::arrayViewOfConst(input_indep_values),
                                 Utility::arrayViewOfConst(input_dep_values) );
  }

  BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Copy constructor (copying from unitless distribution only)
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::UnitAwareTabularCDFDistribution( const UnitAwareTabularCDFDistribution<InterpolationPolicy,void,void>& unitless_dist_instance, int )
  : d_distribution(),
    d_norm_constant(),
    d_interpret_dependent_values_as_cdf( unitless_dist_instance.wasConstructedFromCDF() )
{
  // Make sure the distribution is valid
  testPrecondition( unitless_dist_instance.d_distribution.size() > 0 );

  // Reconstruct the original input distribution
  std::vector<double> input_indep_values, input_dep_values;

  if( d_interpret_dependent_values_as_cdf )
  {
    unitless_dist_instance.reconstructOriginalCDFDistribution(
      input_indep_values, input_dep_values );
  }
  else
  {
    unitless_dist_instance.reconstructOriginalDistribution(
      input_indep_values, input_dep_values );
  }

  this->initializeDistributionFromRawData(
                                 Utility::arrayViewOfConst(input_indep_values),
                                 Utility::arrayViewOfConst(input_dep_values) );
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
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::fromUnitlessDistribution( const UnitAwareTabularCDFDistribution<InterpolationPolicy,void,void>& unitless_distribution )
{
  return ThisType( unitless_distribution, 0 );
}

// Assignment operator
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>&
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::operator=(
  const UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>& dist_instance )
{
  // Make sure the distribution is valid
  testPrecondition( dist_instance.d_distribution.size() > 0 );

  if( this != &dist_instance )
  {
    d_distribution = dist_instance.d_distribution;
    d_norm_constant = dist_instance.d_norm_constant;
    d_interpret_dependent_values_as_cdf =
      dist_instance.d_interpret_dependent_values_as_cdf;
  }

  return *this;
}

// Evaluate the distribution
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::DepQuantity
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::evaluate(
 const typename UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  return DQT::zero();
}

// Evaluate the PDF
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::InverseIndepQuantity
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::evaluatePDF(
 const typename UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  FRENSIE_LOG_TAGGED_WARNING( "TabularCDFDistribution",
                              "The PDF cannot be evaluated! Use the "
                              "TabularDistribution if the PDF must be "
                              "evaluated." );
  return IIQT::zero();
}

// Evaluate the CDF
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
double UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::evaluateCDF(
  const typename UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  if( indep_var_value < Utility::get<0>(d_distribution.front()) )
    return 0.0;
  else if( indep_var_value >= Utility::get<0>(d_distribution.back()) )
    return 1.0;
  else
  {
    typename DistributionArray::const_iterator lower_bin_boundary =
                    Search::binaryLowerBound<FIRST>( d_distribution.begin(),
                                                     d_distribution.end(),
                                                     indep_var_value );

    typename DistributionArray::const_iterator upper_bin_boundary =
                                                            lower_bin_boundary;
    ++upper_bin_boundary;

    IndepQuantity lower_indep_value = Utility::get<0>(*lower_bin_boundary);
    IndepQuantity upper_indep_value = Utility::get<0>(*upper_bin_boundary);
    UnnormCDFQuantity lower_dep_value = Utility::get<1>(*lower_bin_boundary);
    UnnormCDFQuantity upper_dep_value = Utility::get<1>(*upper_bin_boundary);

    if( lower_dep_value == QuantityTraits<UnnormCDFQuantity>::zero() )
    {
      return LinLin::interpolate( lower_indep_value,
                                  upper_indep_value,
                                  indep_var_value,
                                  lower_dep_value,
                                  upper_dep_value )*d_norm_constant;
    }
    else
    {
      return InterpolationPolicy::interpolate( lower_indep_value,
                                               upper_indep_value,
                                               indep_var_value,
                                               lower_dep_value,
                                               upper_dep_value )*d_norm_constant;
    }
  }
}

// Return a random sample from the distribution
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
inline typename UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sample() const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  size_t dummy_index;

  return this->sampleImplementation( random_number, dummy_index );
}

// Return a random sample and record the number of trials
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sampleAndRecordTrials(
                                    DistributionTraits::Counter& trials ) const
{
  ++trials;

  return this->sample();
}

// Return a random sample and bin index from the distribution
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sampleAndRecordBinIndex(
                                            size_t& sampled_bin_index ) const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleImplementation( random_number, sampled_bin_index );
}

// Return a sample from the distribution at the given CDF value
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sampleWithRandomNumber(
                                             const double random_number ) const
{
  size_t dummy_index;

  return this->sampleImplementation( random_number, dummy_index );
}

// Return a random sample from the corresponding CDF in a subrange
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sampleInSubrange(
 const typename UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity max_indep_var ) const
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
inline typename UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sampleWithRandomNumberInSubrange(
 const double random_number,
 const typename UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity max_indep_var ) const
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
typename UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sampleImplementation(
                                            double random_number,
                                            size_t& sampled_bin_index ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );

  // Scale the random number
  UnnormCDFQuantity scaled_random_number = random_number*
    Utility::get<1>(d_distribution.back());

  typename DistributionArray::const_iterator lower_bin_boundary =
                Search::binaryLowerBound<SECOND>( d_distribution.begin(),
                                                  d_distribution.end(),
                                                  scaled_random_number );

  // Calculate the sampled bin index
  sampled_bin_index = std::distance(d_distribution.begin(),lower_bin_boundary);

  // Calculate the sampled independent value
  IndepQuantity sample;

  if( Utility::get<1>(*lower_bin_boundary) == QuantityTraits<UnnormCDFQuantity>::zero() )
  {
    sample = QuantityTraits<IndepQuantity>::initializeQuantity(
               LinLin::interpolate( LinLin::processIndepVar(Utility::get<1>(*lower_bin_boundary)),
                                    LinLin::processIndepVar(scaled_random_number),
                                    LinLin::processIndepVar(Utility::get<0>(*lower_bin_boundary)),
                                    LinLin::processIndepVar(Utility::get<3>(*lower_bin_boundary)) ) );
  }
  else
  {
    sample = QuantityTraits<IndepQuantity>::initializeQuantity(
              InverseInterp::interpolate( InterpolationPolicy::processDepVar(Utility::get<1>(*lower_bin_boundary)),
                                          InterpolationPolicy::processDepVar(scaled_random_number),
                                          InterpolationPolicy::processIndepVar(Utility::get<0>(*lower_bin_boundary)),
                                          Utility::getRawQuantity(Utility::get<3>(*lower_bin_boundary)) ) );
  }

  ++lower_bin_boundary;

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
typename UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::getUpperBoundOfIndepVar() const
{
  return Utility::get<0>(d_distribution.back());
}

// Return the lower bound of the distribution independent variable
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::getLowerBoundOfIndepVar() const
{
  return Utility::get<0>(d_distribution.front());
}

// Return the distribution type
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
UnivariateDistributionType
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::getDistributionType() const
{
  return ThisType::distribution_type;
}

//! Return if the distribution was continuous from a CDF
template<typename InterpolationPolicy,
typename IndependentUnit,
typename DependentUnit>
bool UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::wasConstructedFromCDF() const
{
  return d_interpret_dependent_values_as_cdf;
}

// Test if the distribution is continuous
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
bool UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::isContinuous() const
{
  return true;
}

// Method for placing the object in an output stream
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
void UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::toStream(
                                                       std::ostream& os ) const
{
  std::vector<double> independent_values, dependent_values;

  this->reconstructOriginalUnitlessDistribution( independent_values,
                                                 dependent_values );

  this->toStreamDistImpl( os,
                          std::make_pair( "interp", InterpolationPolicy::name() ),
                          std::make_pair( "independent values", independent_values ),
                          std::make_pair( "dependent values", dependent_values ),
                          std::make_pair( "cdf dependent values", d_interpret_dependent_values_as_cdf ) );
}

// Method for testing if two objects are equivalent
template<typename InterpolationPolicy,
	 typename IndependentUnit,
	 typename DependentUnit>
bool UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::operator==(
 const UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>& other ) const
{
  return d_distribution == other.d_distribution &&
    d_norm_constant == other.d_norm_constant &&
    d_interpret_dependent_values_as_cdf == other.d_interpret_dependent_values_as_cdf;
}

// Method for testing if two objects are different
template<typename InterpolationPolicy,
	 typename IndependentUnit,
	 typename DependentUnit>
bool UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::operator!=(
 const UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>& other ) const
{
  return d_distribution != other.d_distribution ||
    d_norm_constant != other.d_norm_constant ||
    d_interpret_dependent_values_as_cdf != other.d_interpret_dependent_values_as_cdf;
}

// Calculate the processed slope
/*! \details Special consideration is taken when calculating the slope between
 * the first and second CDF bin because the first CDF is always zero. Therefore,
 * even when log interpolation of the CDF is request, lin interpolation is used
 * between the first and second CDF bins.
 */
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
typename UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::SlopeQuantity
UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::calculateProcessedSlope(
                                  const IndepQuantity indep_var_0,
                                  const IndepQuantity indep_var_1,
                                  const UnnormCDFQuantity cdf_var_0,
                                  const UnnormCDFQuantity cdf_var_1 ) const
{
  // Process the variables
  double processed_cdf_1, processed_cdf_0, processed_indep_1, processed_indep_0;
  if( cdf_var_0 == QuantityTraits<UnnormCDFQuantity>::zero() )
  {
    processed_indep_1 = getRawQuantity( indep_var_1 );
    processed_indep_0 = getRawQuantity( indep_var_0 );
    processed_cdf_1 = getRawQuantity( cdf_var_1 );
    processed_cdf_0 = getRawQuantity( cdf_var_0 );
  }
  else
  {
    processed_indep_1 = InterpolationPolicy::processIndepVar( indep_var_1 );
    processed_indep_0 = InterpolationPolicy::processIndepVar( indep_var_0 );
    processed_cdf_1 = InterpolationPolicy::processDepVar( cdf_var_1 );
    processed_cdf_0 = InterpolationPolicy::processDepVar( cdf_var_0 );
  }

  // Return the calculated slope
  return QuantityTraits<SlopeQuantity>::initializeQuantity(
            ( processed_indep_1 - processed_indep_0 )/
            ( processed_cdf_1 - processed_cdf_0 ) );
}

// Initialize the distribution
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
void UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::initializeDistributionFromRawData(
                    const Utility::ArrayView<const double>& independent_values,
                    const Utility::ArrayView<const double>& dependent_values )
{
  // Convert the raw independent values to quantities
  std::vector<IndepQuantity> independent_quantities;

  this->convertUnitlessValues( independent_values, independent_quantities );

  if( d_interpret_dependent_values_as_cdf )
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
/*! \details When the distribution is initialized from the CDF no PDF data is
 *  is calculated. The PDF distribution is left blank.
 */
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
template<typename InputIndepQuantity>
void UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::initializeDistributionFromCDF(
        const Utility::ArrayView<const InputIndepQuantity>& independent_values,
        const Utility::ArrayView<const double>& cdf_values )
{
  // Resize the distribution
  d_distribution.resize( independent_values.size() );

  // Set the first distribution point
  Utility::get<0>(d_distribution[0]) = IndepQuantity( independent_values[0] );
  Utility::setQuantity( Utility::get<1>(d_distribution[0]), cdf_values[0] );

  // Assign the distribution
  for( unsigned i = 1; i < independent_values.size(); ++i )
  {
    Utility::get<0>(d_distribution[i]) =
      IndepQuantity( independent_values[i] );

    Utility::setQuantity( Utility::get<1>(d_distribution[i]), cdf_values[i] );

    Utility::get<3>(d_distribution[i-1]) =
      calculateProcessedSlope( Utility::get<0>(d_distribution[i-1]),
                               Utility::get<0>(d_distribution[i]),
                               Utility::get<1>(d_distribution[i-1]),
                               Utility::get<1>(d_distribution[i]) );
  }

  // Set the last slope to zero
  Utility::setQuantity( Utility::get<3>(d_distribution.back()), 0.0 );

  // Set normalization constant
  d_norm_constant = 1.0/Utility::get<1>(d_distribution.back());
}

// Initialize the distribution
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
template<typename InputIndepQuantity, typename InputDepQuantity>
void UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::initializeDistribution(
        const Utility::ArrayView<const InputIndepQuantity>& independent_values,
        const Utility::ArrayView<const InputDepQuantity>& dependent_values )
{
  // Resize the distribution
  d_distribution.resize( independent_values.size() );

  // Assign the raw distribution data
  for( unsigned i = 0; i < independent_values.size(); ++i )
  {
    Utility::get<0>(d_distribution[i]) =
      IndepQuantity( independent_values[i] );

    Utility::get<2>(d_distribution[i]) =
      DepQuantity( dependent_values[i] );
  }

  // Create a CDF from the raw distribution data
  d_norm_constant =
    DataProcessor::calculateContinuousCDF<FIRST,THIRD,SECOND>( d_distribution,
                                                               false );

  // Calculate the CDF slopes
  for( unsigned i = 1; i < independent_values.size(); ++i )
  {
    Utility::get<3>(d_distribution[i-1]) =
      calculateProcessedSlope( Utility::get<0>(d_distribution[i-1]),
                               Utility::get<0>(d_distribution[i]),
                               Utility::get<1>(d_distribution[i-1]),
                               Utility::get<1>(d_distribution[i]) );
  }

  // Set the last slope to zero
  Utility::setQuantity( Utility::get<3>(d_distribution.back()), 0.0 );
}

// Reconstruct original distribution
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
void UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::reconstructOriginalDistribution(
                         std::vector<IndepQuantity>& independent_values,
                         std::vector<DepQuantity>& dependent_values ) const
{
  // Resize the arrays
  independent_values.resize( d_distribution.size() );
  dependent_values.resize( d_distribution.size() );

  for( unsigned i = 0u; i < d_distribution.size(); ++i )
  {
    independent_values[i] = Utility::get<0>(d_distribution[i]);
    dependent_values[i] = Utility::get<2>(d_distribution[i]);
  }
}

// Reconstruct original distribution
template<typename InterpolationPolicy,
typename IndependentUnit,
typename DependentUnit>
void UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::reconstructOriginalCDFDistribution(
                std::vector<IndepQuantity>& independent_values,
                std::vector<double>& cdf_values ) const
{
  // Resize the arrays
  independent_values.resize( d_distribution.size() );
  cdf_values.resize( d_distribution.size() );

  for( unsigned i = 0u; i < d_distribution.size(); ++i )
  {
    independent_values[i] = Utility::get<0>(d_distribution[i]);
    cdf_values[i] = Utility::getRawQuantity( Utility::get<1>(d_distribution[i]) );
  }
}

// Reconstruct original distribution w/o units
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
void UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::reconstructOriginalUnitlessDistribution(
                               std::vector<double>& independent_values,
                               std::vector<double>& dependent_values ) const
{
  // Resize the arrays
  independent_values.resize( d_distribution.size() );
  dependent_values.resize( d_distribution.size() );

  for( unsigned i = 0u; i < d_distribution.size(); ++i )
  {
    independent_values[i] =
      Utility::getRawQuantity( Utility::get<0>(d_distribution[i]) );

    if( d_interpret_dependent_values_as_cdf )
    {
      dependent_values[i] =
        Utility::getRawQuantity( Utility::get<1>(d_distribution[i]) );
    }
    else
    {
      dependent_values[i] =
        Utility::getRawQuantity( Utility::get<2>(d_distribution[i]) );
    }
  }
}

// Convert the unitless values to the correct units
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
template<typename Quantity>
void UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::convertUnitlessValues(
                       const Utility::ArrayView<const double>& unitless_values,
                       std::vector<Quantity>& quantities )
{
  // Resize the quantity array
  quantities.resize( unitless_values.size() );

  // Copy the bin boundaries
  for( unsigned i = 0u; i < unitless_values.size(); ++i )
    Utility::setQuantity( quantities[i], unitless_values[i] );
}

// Test if the dependent variable can be zero within the indep bounds
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
bool UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::canDepVarBeZeroInIndepBounds() const
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
// bool UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::isIndepVarCompatibleWithProcessingType(
//                                          const LinIndepVarProcessingTag ) const
// {
//   return boost::is_same<typename InterpolationPolicy::IndepVarProcessingTag,LinIndepVarProcessingTag>::value;
// }

// // Test if the independent variable is compatible with Log processing
// template<typename InterpolationPolicy,
//          typename IndependentUnit,
//          typename DependentUnit>
// bool UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::isIndepVarCompatibleWithProcessingType(
//                                          const LogIndepVarProcessingTag ) const
// {
//   return boost::is_same<typename InterpolationPolicy::IndepVarProcessingTag,LogIndepVarProcessingTag>::value;
// }

// Test if the dependent variable is compatible with Lin processing
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
bool UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::isDepVarCompatibleWithProcessingType(
                                           const LinDepVarProcessingTag ) const
{
  if( d_interpret_dependent_values_as_cdf )
    return true;
  else
    return !this->canDepVarBeZeroInIndepBounds();
}

// Test if the dependent variable is compatible with Log processing
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
bool UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::isDepVarCompatibleWithProcessingType(
                                           const LogDepVarProcessingTag ) const
{
  if( d_interpret_dependent_values_as_cdf )
    return true;
  else
    return !this->canDepVarBeZeroInIndepBounds();
}

// Verify that the values are valid
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
template<typename InputIndepQuantity, typename InputDepQuantity>
void UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::verifyValidValues(
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
                  [](const InputDepQuantity& element){ return element < InputDQT::zero() || InputDQT::isnaninf( element ); } );

  TEST_FOR_EXCEPTION( bad_dependent_value != dependent_values.end(),
                      Utility::StringConversionException,
                      "The tabular distribution cannot be constructed "
                      "because the dependent value at index "
                      << std::distance( dependent_values.begin(), bad_dependent_value ) <<
                      " (" << *bad_dependent_value << ") is not valid!" );
}

// Save the distribution to an archive
template<typename InterpolationPolicy,
	 typename IndependentUnit,
	 typename DependentUnit>
template<typename Archive>
void UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::save( Archive& ar, const unsigned version ) const
{
  // Save the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Save the local member data
  ar & BOOST_SERIALIZATION_NVP( d_distribution );
  ar & BOOST_SERIALIZATION_NVP( d_norm_constant );
  ar & BOOST_SERIALIZATION_NVP( d_interpret_dependent_values_as_cdf );
}

// Load the distribution from an archive
template<typename InterpolationPolicy,
	 typename IndependentUnit,
	 typename DependentUnit>
template<typename Archive>
void UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::load( Archive& ar, const unsigned version )
{
  // Load the base class first
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType );

  // Load the local member data
  ar & BOOST_SERIALIZATION_NVP( d_distribution );
  ar & BOOST_SERIALIZATION_NVP( d_norm_constant );
  ar & BOOST_SERIALIZATION_NVP( d_interpret_dependent_values_as_cdf );
}

} // end Utility namespace

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareTabularCDFDistribution<Utility::LinLin,void,void> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Utility, UnitAwareTabularCDFDistribution<Utility::LinLin,void,void> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareTabularCDFDistribution<Utility::LogLog,void,void> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Utility, UnitAwareTabularCDFDistribution<Utility::LogLog,void,void> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareTabularCDFDistribution<Utility::LinLog,void,void> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Utility, UnitAwareTabularCDFDistribution<Utility::LinLog,void,void> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareTabularCDFDistribution<Utility::LogLin,void,void> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Utility, UnitAwareTabularCDFDistribution<Utility::LogLin,void,void> );

// Explicit cosine instantiation (extern declaration)
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareTabularCDFDistribution<Utility::LogLogCos,void,void> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Utility, UnitAwareTabularCDFDistribution<Utility::LogLogCos,void,void> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareTabularCDFDistribution<Utility::LinLogCos,void,void> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Utility, UnitAwareTabularCDFDistribution<Utility::LinLogCos,void,void> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareTabularCDFDistribution<Utility::LogNudgedLogCos,void,void> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Utility, UnitAwareTabularCDFDistribution<Utility::LogNudgedLogCos,void,void> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( Utility::UnitAwareTabularCDFDistribution<Utility::LinNudgedLogCos,void,void> );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Utility, UnitAwareTabularCDFDistribution<Utility::LinNudgedLogCos,void,void> );

#endif // end Utility_TabularCDFDistribution_def.hpp

//---------------------------------------------------------------------------//
// end Utility_TabularCDFDistribution_def.hpp
//---------------------------------------------------------------------------//
