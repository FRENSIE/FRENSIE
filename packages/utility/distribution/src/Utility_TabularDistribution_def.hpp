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
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_EXTRA( UnitAwareTabularDistribution, typename, InterpolationPolicy );

namespace Utility{

// Initialize static member data
template<typename InterpolationPolicy,
	 typename IndependentUnit,
	 typename DependentUnit>
const std::string UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::s_independent_values_key( "independent values" );

template<typename InterpolationPolicy,
	 typename IndependentUnit,
	 typename DependentUnit>
const std::string UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::s_independent_values_min_match_string( "indep" );

template<typename InterpolationPolicy,
	 typename IndependentUnit,
	 typename DependentUnit>
const std::string UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::s_dependent_values_key( "dependent values" );

template<typename InterpolationPolicy,
	 typename IndependentUnit,
	 typename DependentUnit>
const std::string UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::s_dependent_values_min_match_string( "dep" );

// Default constructor
template<typename InterpolationPolicy,
	 typename IndependentUnit,
	 typename DependentUnit>
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::UnitAwareTabularDistribution()
{ BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType ); }

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
  : d_distribution( independent_values.size() ),
    d_norm_constant( DNQT::zero() )
{
  // Make sure there is at lease one bin
  testPrecondition( independent_values.size() > 1 );
  testPrecondition( dependent_values.size() == independent_values.size() );
  // Make sure that the bins are sorted
  testPrecondition( Sort::isSortedAscending( independent_values.begin(),
					     independent_values.end() ) );

  this->initializeDistributionFromRawData( independent_values,
                                           dependent_values );

  BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Constructor
template<typename InterpolationPolicy,
	 typename IndependentUnit,
	 typename DependentUnit>
template<typename InputIndepQuantity, typename InputDepQuantity>
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::UnitAwareTabularDistribution(
		  const std::vector<InputIndepQuantity>& independent_values,
		  const std::vector<InputDepQuantity>& dependent_values )
  : d_distribution( independent_values.size() ),
    d_norm_constant( DNQT::zero() )
{
  // Make sure there is at lease one bin
  testPrecondition( independent_values.size() > 1 );
  testPrecondition( dependent_values.size() == independent_values.size() );
  // Make sure that the bins are sorted
  testPrecondition( Sort::isSortedAscending( independent_values.begin(),
					     independent_values.end() ) );

  this->initializeDistribution( independent_values, dependent_values );

  BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
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
  // Make sure the distribution is valid
  testPrecondition( dist_instance.d_distribution.size() > 0 );

  typedef typename UnitAwareTabularDistribution<InterpolationPolicy,InputIndepUnit,InputDepUnit>::IndepQuantity InputIndepQuantity;

  typedef typename UnitAwareTabularDistribution<InterpolationPolicy,InputIndepUnit,InputDepUnit>::DepQuantity InputDepQuantity;

  // Reconstruct the original input distribution
  std::vector<InputIndepQuantity> input_indep_values;
  std::vector<InputDepQuantity> input_dep_values;

  dist_instance.reconstructOriginalDistribution( input_indep_values,
						 input_dep_values );

  this->initializeDistribution( input_indep_values, input_dep_values );

  BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Copy constructor (copying from unitless distribution only)
template<typename InterpolationPolicy,
	 typename IndependentUnit,
	 typename DependentUnit>
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::UnitAwareTabularDistribution( const UnitAwareTabularDistribution<InterpolationPolicy,void,void>& unitless_dist_instance, int )
  : d_distribution(),
    d_norm_constant()
{
  // Make sure the distribution is valid
  testPrecondition( unitless_dist_instance.d_distribution.size() > 0 );

  // Reconstruct the original input distribution
  std::vector<double> input_indep_values, input_dep_values;

  unitless_dist_instance.reconstructOriginalDistribution( input_indep_values,
							  input_dep_values );

  this->initializeDistributionFromRawData( input_indep_values,
                                           input_dep_values );

  BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
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
  // Make sure the distribution is valid
  testPrecondition( dist_instance.d_distribution.size() > 0 );

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

  unsigned dummy_index;

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
					    unsigned& sampled_bin_index ) const
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
  unsigned dummy_index;

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

  unsigned dummy_index;

  return this->sampleImplementation( scaled_random_number, dummy_index );
}

// Return a random sample using the random number and record the bin index
template<typename InterpolationPolicy,
	 typename IndependentUnit,
	 typename DependentUnit>
typename UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::sampleImplementation(
					    double random_number,
					    unsigned& sampled_bin_index ) const
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
OneDDistributionType
UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::getDistributionType() const
{
  return ThisType::distribution_type;
}

// Return the distribution type name
template<typename InterpolationPolicy,
	 typename IndependentUnit,
	 typename DependentUnit>
std::string UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::typeName(
                                                const bool verbose_name,
                                                const bool use_template_params,
                                                const std::string& delim )
{
  return BaseType::typeNameImpl( {"Tabular", InterpolationPolicy::name()},
                                 verbose_name,
                                 use_template_params,
                                 delim );
}

// Return the distribution type name
template<typename InterpolationPolicy,
	 typename IndependentUnit,
	 typename DependentUnit>
std::string UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::getDistributionTypeName(
                                                   const bool verbose_name,
                                                   const bool lowercase ) const
{
  std::string name = this->typeName( verbose_name, false, " " );

  if( lowercase )
    boost::algorithm::to_lower( name );

  return name;
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
  std::vector<double> independent_values, dependent_values;

  this->reconstructOriginalUnitlessDistribution( independent_values,
						 dependent_values );

  this->toStreamImpl( os, independent_values, dependent_values );
}

// Method for initializing the object from an input stream
template<typename InterpolationPolicy,
	 typename IndependentUnit,
	 typename DependentUnit>
void UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::fromStream( std::istream& is, const std::string& )
{
  VariantList distribution_data;

  this->fromStreamImpl( is, distribution_data );

  // Extract the independent values
  TEST_FOR_EXCEPTION( distribution_data.empty(),
                      Utility::StringConversionException,
                      "The " << this->getDistributionTypeName( true, false ) <<
                      " could not be reconstructed because no independent "
                      "values are specified!" );

  std::vector<double> independent_values;
  this->extractValues( distribution_data.front(), independent_values );

  distribution_data.pop_front();

  // Extract the dependent values
  TEST_FOR_EXCEPTION( distribution_data.empty(),
                      Utility::StringConversionException,
                      "The " << this->getDistributionTypeName( true, false ) <<
                      " could not be reconstructed because no dependent "
                      "values are specified!" );

  std::vector<double> dependent_values;
  this->extractValues( distribution_data.front(), dependent_values );

  distribution_data.pop_front();

  // Verify that the values are valid
  this->verifyValidValues( independent_values, dependent_values );

  // Initialize the distribution
  this->initializeDistributionFromRawData( independent_values,
                                           dependent_values );

  // Check if there is any superfluous data
  this->checkForUnusedStreamData( distribution_data );
}

// Method for converting the type to a property tree
template<typename InterpolationPolicy,
	 typename IndependentUnit,
	 typename DependentUnit>
Utility::PropertyTree UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::toPropertyTree( const bool inline_data ) const
{
  if( inline_data )
    return this->toInlinedPropertyTreeImpl();
  else
  {
    std::vector<double> independent_values, dependent_values;

    this->reconstructOriginalUnitlessDistribution( independent_values,
                                                   dependent_values );

    return this->toPropertyTreeImpl(
                      std::tie( s_independent_values_key, independent_values ),
                      std::tie( s_dependent_values_key, dependent_values ) );
  }
}

// Method for initializing the object from a property tree
template<typename InterpolationPolicy,
	 typename IndependentUnit,
	 typename DependentUnit>
void UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::fromPropertyTree(
                                    const Utility::PropertyTree& node,
                                    std::vector<std::string>& unused_children )
{
  // Initialize from inline data
  if( node.size() == 0 )
    this->fromInlinedPropertyTreeImpl( node );

  // Initialize from child nodes
  else
  {
    std::vector<double> independent_values, dependent_values;

    typename BaseType::DataExtractorMap data_extractors;

    data_extractors.insert(
     std::make_pair( s_independent_values_key,
      std::make_tuple( s_independent_values_min_match_string, BaseType::REQUIRED_DATA,
                       std::bind<void>(&ThisType::extractValuesFromNode,
                                       std::placeholders::_1,
                                       std::ref(independent_values) ) ) ) );
    data_extractors.insert(
     std::make_pair( s_dependent_values_key,
      std::make_tuple( s_dependent_values_min_match_string, BaseType::REQUIRED_DATA,
                       std::bind<void>(&ThisType::extractValuesFromNode,
                                       std::placeholders::_1,
                                       std::ref(dependent_values) ) ) ) );

    this->fromPropertyTreeImpl( node, unused_children, data_extractors );

    // Verify that the values are valid
    try{
      this->verifyValidValues( independent_values, dependent_values );
    }
    EXCEPTION_CATCH_RETHROW_AS( Utility::StringConversionException,
                                Utility::PropertyTreeConversionException,
                                "Invalid values detected!" );

    // Initialize the distribution
    this->initializeDistributionFromRawData( independent_values,
                                             dependent_values );
  }
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
			      const std::vector<double>& independent_values,
			      const std::vector<double>& dependent_values )
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

  this->initializeDistribution( independent_quantities,
                                dependent_quantities );
}

// Initialize the distribution
template<typename InterpolationPolicy,
	 typename IndependentUnit,
	 typename DependentUnit>
template<typename InputIndepQuantity, typename InputDepQuantity>
void UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::initializeDistribution(
		  const std::vector<InputIndepQuantity>& independent_values,
		  const std::vector<InputDepQuantity>& dependent_values )
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
  for( unsigned i = 0; i < independent_values.size(); ++i )
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

  for( unsigned i = 0u; i < d_distribution.size(); ++i )
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

  for( unsigned i = 0u; i < d_distribution.size(); ++i )
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
		                 const std::vector<double>& unitless_values,
				 std::vector<Quantity>& quantities )
{
  // Resize the quantity array
  quantities.resize( unitless_values.size() );

  // Copy the bin boundaries
  for( unsigned i = 0u; i < unitless_values.size(); ++i )
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

// Test if the independent variable is compatible with Lin processing
template<typename InterpolationPolicy,
	 typename IndependentUnit,
	 typename DependentUnit>
bool UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::isIndepVarCompatibleWithProcessingType(
                                         const LinIndepVarProcessingTag ) const
{
  return boost::is_same<typename InterpolationPolicy::IndepVarProcessingTag,LinIndepVarProcessingTag>::value;
}
  
// Test if the independent variable is compatible with Log processing
template<typename InterpolationPolicy,
	 typename IndependentUnit,
	 typename DependentUnit>
bool UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::isIndepVarCompatibleWithProcessingType(
                                         const LogIndepVarProcessingTag ) const
{
  return boost::is_same<typename InterpolationPolicy::IndepVarProcessingTag,LogIndepVarProcessingTag>::value;
}

// Test if the dependent variable is compatible with Lin processing
template<typename InterpolationPolicy,
	 typename IndependentUnit,
	 typename DependentUnit>
bool UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::isDepVarCompatibleWithProcessingType(
                                           const LinDepVarProcessingTag ) const
{
  return boost::is_same<typename InterpolationPolicy::DepVarProcessingTag,LinDepVarProcessingTag>::value;
}

// Test if the dependent variable is compatible with Log processing
template<typename InterpolationPolicy,
	 typename IndependentUnit,
	 typename DependentUnit>
bool UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::isDepVarCompatibleWithProcessingType(
                                           const LogDepVarProcessingTag ) const
{
  return boost::is_same<typename InterpolationPolicy::DepVarProcessingTag,LogDepVarProcessingTag>::value;
}

// Extract the values from a property tree
template<typename InterpolationPolicy,
	 typename IndependentUnit,
	 typename DependentUnit>
void UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::extractValuesFromNode(
                                      const Utility::PropertyTree& values_data,
                                      std::vector<double>& values )
{
  // Inline array
  if( values_data.size() == 0 )
    ThisType::extractValues( values_data.data(), values );

  // JSON array
  else
  {
    try{
      values = Utility::fromPropertyTree<std::vector<double> >( values_data );
    }
    EXCEPTION_CATCH_RETHROW( Utility::PropertyTreeConversionException,
                             "The tabular distribution cannot be "
                             "constructed because the values are not valid!" );
  }
}

// Extract the values
template<typename InterpolationPolicy,
	 typename IndependentUnit,
	 typename DependentUnit>
void UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::extractValues(
                                           const Utility::Variant& values_data,
                                           std::vector<double>& values )
{
  try{
    values = Utility::variant_cast<std::vector<double> >( values_data );
  }
  EXCEPTION_CATCH_RETHROW( Utility::StringConversionException,
                           "The tabular distribution cannot be "
                           "constructed because the values are "
                           "not valid!" );
}

// Verify that the values are valid
template<typename InterpolationPolicy,
	 typename IndependentUnit,
	 typename DependentUnit>
void UnitAwareTabularDistribution<InterpolationPolicy,IndependentUnit,DependentUnit>::verifyValidValues(
                                 const std::vector<double>& independent_values,
                                 const std::vector<double>& dependent_values )
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

  TEST_FOR_EXCEPTION( QT::isnaninf( independent_values.front() ),
                      Utility::StringConversionException,
                      "The tabular distribution cannot be constructed "
                      "because the first independent value is invalid!" );

  TEST_FOR_EXCEPTION( QT::isnaninf( independent_values.back() ),
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

  // Search for bad dependent values
  std::vector<double>::const_iterator bad_dependent_value =
    std::find_if( dependent_values.begin(),
                  dependent_values.end(),
                  [](double element){ return element < 0.0 || QT::isnaninf( element ) || !InterpolationPolicy::isDepVarInValidRange( element ); } );

  TEST_FOR_EXCEPTION( bad_dependent_value != dependent_values.end(),
                      Utility::StringConversionException,
                      "The tabular distribution cannot be constructed "
                      "because the dependent value at index "
                      << std::distance( dependent_values.begin(), bad_dependent_value ) <<
                      " (" << *bad_dependent_value << ") is not valid!" );
}

} // end Utility namespace

// Explicit instantiation (extern declaration)
EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareTabularDistribution<LinLin,void,void> );
EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareTabularDistribution<LinLog,void,void> );
EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareTabularDistribution<LogLin,void,void> );
EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareTabularDistribution<LogLog,void,void> );

#endif // end Utility_TabularDistribution_def.hpp

//---------------------------------------------------------------------------//
// end Utility_TabularDistribution_def.hpp
//---------------------------------------------------------------------------//
