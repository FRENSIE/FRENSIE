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
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_ContractException.hpp"

BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT( UnitAwareHistogramDistribution );

namespace Utility{

// Initialize static member data
template<typename IndependentUnit, typename DependentUnit>
const std::string UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::s_bin_boundary_values_key( "bin boundaries" );

template<typename IndependentUnit, typename DependentUnit>
const std::string UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::s_bin_boundary_values_min_match_string( "boundaries" );

template<typename IndependentUnit, typename DependentUnit>
const std::string UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::s_bin_values_key( "bin values" );

template<typename IndependentUnit, typename DependentUnit>
const std::string UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::s_bin_values_min_match_string( "values" );

template<typename IndependentUnit, typename DependentUnit>
const std::string UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::s_cdf_specified_value_key( "cdf specified" );

template<typename IndependentUnit, typename DependentUnit>
const std::string UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::s_cdf_specified_value_min_match_string( "cdf" );

// Default constructor
template<typename IndependentUnit, typename DependentUnit>
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::UnitAwareHistogramDistribution()
{ 
  BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

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
  : d_distribution( bin_boundaries.size() ),
    d_norm_constant( DNQT::one() )
{
  // Make sure there is at least one bin
  testPrecondition( bin_boundaries.size() > 1 );
  // Make sure the bin boundaries are sorted
  testPrecondition( Sort::isSortedAscending( bin_boundaries.begin(),
					     bin_boundaries.end() ) );
  // Make sure that for n bin boundaries there are n-1 bin values
  testPrecondition( bin_boundaries.size() - 1 == bin_values.size() );

  this->initializeDistribution( bin_boundaries,
				bin_values,
				interpret_dependent_values_as_cdf );

  BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
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
  : d_distribution( bin_boundaries.size() ),
    d_norm_constant( DNQT::one() )
{
  // Make sure there is at least one bin
  testPrecondition( bin_boundaries.size() > 1 );
  // Make sure the bin boundaries are sorted
  testPrecondition( Sort::isSortedAscending( bin_boundaries.begin(),
					     bin_boundaries.end() ) );
  // Make sure the cdf values are sorted
  testPrecondition( Sort::isSortedAscending( cdf_values.begin(),
					     cdf_values.end() ) );
  // Make sure that for n bin boundaries there are n-1 bin values
  testPrecondition( bin_boundaries.size() - 1 == cdf_values.size() );

  this->initializeDistributionFromCDF( bin_boundaries, cdf_values );

  BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Constructor
template<typename IndependentUnit, typename DependentUnit>
template<typename InputIndepQuantity, typename InputDepQuantity>
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::UnitAwareHistogramDistribution(
		      const std::vector<InputIndepQuantity>& bin_boundaries,
		      const std::vector<InputDepQuantity>& bin_values )
  : d_distribution( bin_boundaries.size() ),
    d_norm_constant( DNQT::one() )
{
  // Make sure there is at least one bin
  testPrecondition( bin_boundaries.size() > 1 );
  // Make sure the bin boundaries are sorted
  testPrecondition( Sort::isSortedAscending( bin_boundaries.begin(),
					     bin_boundaries.end() ) );
  // Make sure that for n bin boundaries there are n-1 bin values
  testPrecondition( bin_boundaries.size() - 1 == bin_values.size() );

  this->initializeDistribution( bin_boundaries, bin_values );

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
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::UnitAwareHistogramDistribution(
 const UnitAwareHistogramDistribution<InputIndepUnit,InputDepUnit>& dist_instance )
  : d_distribution(),
    d_norm_constant()
{
  // Make sure that the distribution is valid
  testPrecondition( dist_instance.d_distribution.size() > 0 );

  typedef typename UnitAwareHistogramDistribution<InputIndepUnit,InputDepUnit>::IndepQuantity InputIndepQuantity;

  typedef typename UnitAwareHistogramDistribution<InputIndepUnit,InputDepUnit>::DepQuantity InputDepQuantity;

  // Reconstruct the original input distribution
  std::vector<InputIndepQuantity> input_bin_boundaries;
  std::vector<InputDepQuantity> input_bin_values;

  dist_instance.reconstructOriginalDistribution( input_bin_boundaries,
						 input_bin_values );

  this->initializeDistribution( input_bin_boundaries, input_bin_values );

  BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Copy constructor (copying from unitless distribution only)
template<typename IndependentUnit, typename DependentUnit>
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::UnitAwareHistogramDistribution(
 const UnitAwareHistogramDistribution<void,void>& unitless_dist_instance, int )
  : d_distribution(),
    d_norm_constant()
{
  // Make sure that the distribution is valid
  testPrecondition( unitless_dist_instance.d_distribution.size() > 0 );

  // Reconstruct the original input distribution
  std::vector<double> input_bin_boundaries, input_bin_values;

  unitless_dist_instance.reconstructOriginalDistribution( input_bin_boundaries,
							  input_bin_values );

  this->initializeDistribution( input_bin_boundaries, input_bin_values, false );
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
  // Make sure that the distribution is valid
  testPrecondition( dist_instance.d_distribution.size() > 0 );

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
  if( indep_var_value < Utility::get<FIRST>(d_distribution.front()) )
    return DQT::zero();
  else if( indep_var_value > Utility::get<FIRST>(d_distribution.back()) )
    return DQT::zero();
  else
  {
    typename DistributionArray::const_iterator bin =
      Search::binaryLowerBound<FIRST>( d_distribution.begin(),
                                       d_distribution.end(),
                                       indep_var_value );

    return Utility::get<SECOND>(*bin);
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
  if( indep_var_value < Utility::get<FIRST>(d_distribution.front()) )
    return 0.0;
  else if( indep_var_value >= Utility::get<FIRST>(d_distribution.back()) )
    return 1.0;
  else
  {
    typename DistributionArray::const_iterator lower_bin =
      Search::binaryLowerBound<FIRST>( d_distribution.begin(),
                                       d_distribution.end(),
                                       indep_var_value );

    IndepQuantity indep_diff =
      indep_var_value - Utility::get<FIRST>(*lower_bin);

    return (Utility::get<THIRD>(*lower_bin) +
            Utility::get<SECOND>(*lower_bin)*indep_diff)*d_norm_constant;
  }
}

// Return a random sample from the distribution
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::sample() const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  unsigned dummy_index;

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
					    unsigned& sampled_bin_index ) const
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

  unsigned dummy_index;

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

// Return a random sample using the random number and record the bin index
template<typename IndependentUnit, typename DependentUnit>
inline typename UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::sampleImplementation(
					    double random_number,
					    unsigned& sampled_bin_index ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );

  UnnormCDFQuantity scaled_random_number =
    random_number*Utility::get<THIRD>(d_distribution.back());

  typename DistributionArray::const_iterator bin =
    Search::binaryLowerBound<THIRD>( d_distribution.begin(),
				     d_distribution.end(),
				     scaled_random_number );

  sampled_bin_index = std::distance( d_distribution.begin(), bin );

  return Utility::get<FIRST>(*bin) +
    IndepQuantity((scaled_random_number - Utility::get<THIRD>(*bin))/
                  Utility::get<SECOND>(*bin));
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

  unsigned dummy_index;

  return this->sampleImplementation( scaled_random_number, dummy_index );
}

// Return the upper bound of the distribution independent variable
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::getUpperBoundOfIndepVar() const
{
  return Utility::get<FIRST>(d_distribution.back());
}

// Return the lower bound of the distribution independent variable
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::getLowerBoundOfIndepVar() const
{
  return Utility::get<FIRST>(d_distribution.front());
}

// Return the distribution type
template<typename IndependentUnit, typename DependentUnit>
OneDDistributionType
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::getDistributionType() const
{
  return UnitAwareHistogramDistribution::distribution_type;
}

// Return the distribution type name
template<typename IndependentUnit, typename DependentUnit>
std::string UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::typeName(
                                                const bool verbose_name,
                                                const bool use_template_params,
                                                const std::string& delim )
{
  return BaseType::typeNameImpl( "Histogram",
                                 verbose_name,
                                 use_template_params,
                                 delim );
}

// Return the distribution type name
template<typename IndependentUnit, typename DependentUnit>
std::string UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::getDistributionTypeName(
                                                   const bool verbose_name,
                                                   const bool lowercase ) const
{
  std::string name = this->typeName( verbose_name, false, " " );

  if( lowercase )
    boost::algorithm::to_lower( name );

  return name;
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
  std::vector<double> bin_boundaries, bin_values;

  this->reconstructOriginalUnitlessDistribution( bin_boundaries,
						 bin_values );

  this->toStreamImpl( os, bin_boundaries, bin_values );
}

// Method for initializing the object from an input stream
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::fromStream(
                                                           std::istream& is,
                                                           const std::string& )
{
  VariantList distribution_data;

  this->fromStreamImpl( is, distribution_data );

  // Extract the bin boundaries
  TEST_FOR_EXCEPTION( distribution_data.empty(),
                      Utility::StringConversionException,
                      "The " << this->getDistributionTypeName( true, false ) <<
                      " could not be constructed because no bin boundaries "
                      "are not specified!" );
  
  std::vector<double> bin_boundaries;
  this->extractValues( distribution_data.front(), bin_boundaries );

  distribution_data.pop_front();

  // Extract the bin values
  TEST_FOR_EXCEPTION( distribution_data.empty(),
                      Utility::StringConversionException,
                      "The " << this->getDistributionTypeName( true, false ) <<
                      " could not be constructed because no bin values "
                      "are not specified!" );
  
  std::vector<double> bin_values;
  this->extractValues( distribution_data.front(), bin_values );

  distribution_data.pop_front();

  // Extract the cdf boolean
  bool cdf_specified = false;

  if( !distribution_data.empty() )
  {
    this->extractCDFBoolean( distribution_data.front(), cdf_specified );

    distribution_data.pop_front();
  }

  // Verify that the values are valid
  this->verifyValidValues( bin_boundaries, bin_values, cdf_specified );

  // Initialize the distribution
  this->initializeDistribution( bin_boundaries, bin_values, cdf_specified );

  // Check if there is any superfluous data
  this->checkForUnusedStreamData( distribution_data );
}

// Method for converting the type to a property tree
template<typename IndependentUnit, typename DependentUnit>
Utility::PropertyTree UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::toPropertyTree(
                                                 const bool inline_data ) const
{
  if( inline_data )
    return this->toInlinedPropertyTreeImpl();
  else
  {
    std::vector<double> bin_boundaries, bin_values;

    this->reconstructOriginalUnitlessDistribution( bin_boundaries,
                                                   bin_values );

    return this->toPropertyTreeImpl(
                         std::tie( s_bin_boundary_values_key, bin_boundaries ),
                         std::tie( s_bin_values_key, bin_values ) );
  }
}

// Method for initializing the object from a property tree node
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::fromPropertyTree(
                                    const Utility::PropertyTree& node,
                                    std::vector<std::string>& unused_children )
{
  // Initialize from inline data
  if( node.size() == 0 )
    this->fromInlinedPropertyTreeImpl( node );
  
  // Initialize from child nodes
  else
  {
    std::vector<double> bin_boundaries, bin_values;
    bool cdf_specified = false;

    typename BaseType::DataExtractorMap data_extractors;

    data_extractors.insert(
     std::make_pair( s_bin_boundary_values_key,
      std::make_tuple( s_bin_boundary_values_min_match_string, REQUIRED_DATA,
                       std::bind<void>(&ThisType::extractValuesFromNode,
                                       std::placeholders::_1,
                                       std::ref(bin_boundaries) ) ) ) );
    data_extractors.insert(
     std::make_pair( s_bin_values_key,
      std::make_tuple( s_bin_values_min_match_string, REQUIRED_DATA,
                       std::bind<void>(&ThisType::extractValuesFromNode,
                                       std::placeholders::_1,
                                       std::ref(bin_values) ) ) ) );
    data_extractors.insert(
     std::make_pair( s_cdf_specified_value_key,
      std::make_tuple( s_cdf_specified_value_min_match_string, OPTIONAL_DATA,
                       std::bind<void>(&ThisType::extractCDFBooleanFromNode,
                                       std::placeholders::_1,
                                       std::ref(cdf_specified) ) ) ) );
                           
    this->fromPropertyTreeImpl( node, unused_children, data_extractors );
    
    // Verify that the values are valid
    try{
      this->verifyValidValues( bin_boundaries, bin_values, cdf_specified );
    }
    EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                Utility::PropertyTreeConversionException,
                                "The histogram distribution could not be "
                                "constructed because the bin boundaries and/or"
                                " values are not valid!" );

    // Initialize the distribution
    this->initializeDistribution( bin_boundaries, bin_values, cdf_specified );
  }
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
				  const std::vector<double>& bin_boundaries,
				 const std::vector<double>& bin_values,
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
    this->initializeDistributionFromCDF( bin_boundary_quantities,
					 bin_values );
  }
  else
  {
    // Convert the raw bin values to quantities
    std::vector<DepQuantity> bin_quantities;

    this->convertUnitlessValues( bin_values, bin_quantities );

    this->initializeDistribution( bin_boundary_quantities,
				  bin_quantities );
  }
}

// Initialize the distribution from a cdf
template<typename IndependentUnit, typename DependentUnit>
template<typename InputIndepQuantity>
void UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::initializeDistributionFromCDF(
		     const std::vector<InputIndepQuantity>& bin_boundaries,
		     const std::vector<double>& cdf_values )
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
  Utility::get<FIRST>(d_distribution[0]) = IndepQuantity( bin_boundaries[0] );
  setQuantity( Utility::get<THIRD>(d_distribution[0]), 0.0 );

    // Assign the distribution
    for( unsigned i = 1; i < bin_boundaries.size(); ++i )
    {
      Utility::get<FIRST>(d_distribution[i]) =
        IndepQuantity( bin_boundaries[i] );
      
      setQuantity( Utility::get<THIRD>(d_distribution[i]), cdf_values[i-1] );

      // Calculate the pdf from the cdf
      Utility::get<SECOND>(d_distribution[i-1]) =
        DepQuantity( (Utility::get<THIRD>(d_distribution[i]) -
                      Utility::get<THIRD>(d_distribution[i-1]))/
		     (Utility::get<FIRST>(d_distribution[i]) -
                      Utility::get<FIRST>(d_distribution[i-1])) );
    }

    // Last PDF value is unused and can be assigned to the second to last value
    Utility::get<SECOND>(d_distribution.back()) =
      Utility::get<SECOND>(d_distribution[d_distribution.size()-2]);

    // Set normalization constant
    d_norm_constant = 1.0/Utility::get<THIRD>(d_distribution.back());
}

// Initialize the distribution
template<typename IndependentUnit, typename DependentUnit>
template<typename InputIndepQuantity, typename InputDepQuantity>
void UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::initializeDistribution(
		      const std::vector<InputIndepQuantity>& bin_boundaries,
		      const std::vector<InputDepQuantity>& bin_values )
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
  for( unsigned i = 0; i < bin_boundaries.size(); ++i )
  {
    // Assign the min and max bin boundaries (respectively)
    Utility::get<FIRST>(d_distribution[i]) =
      IndepQuantity( bin_boundaries[i] );

    // Assign the bin PDF value
    if( i < bin_boundaries.size() - 1 )
      Utility::get<SECOND>(d_distribution[i]) = DepQuantity( bin_values[i] );
    else
      Utility::get<SECOND>(d_distribution[i]) = DepQuantity( bin_values[i-1] );

    // Assign the discrete CDF value
    if( i > 0 )
    {
      Utility::get<THIRD>(d_distribution[i]) =
        Utility::get<THIRD>(d_distribution[i-1]);

      Utility::get<THIRD>(d_distribution[i]) += DepQuantity( bin_values[i-1] )*
        IndepQuantity( Utility::get<FIRST>(d_distribution[i]) -
                       Utility::get<FIRST>(d_distribution[i-1]) );
    }
    else
      setQuantity( Utility::get<THIRD>(d_distribution[i]), 0.0 );
  }

  // Assign the normalization constant
  d_norm_constant = 1.0/Utility::get<THIRD>(d_distribution.back());
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
  
  for( unsigned i = 0u; i < d_distribution.size(); ++i )
  {
    bin_boundaries[i] = Utility::get<FIRST>(d_distribution[i]);

    if( i < d_distribution.size() - 1 )
      bin_values[i] = Utility::get<SECOND>(d_distribution[i]);
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

  for( unsigned i = 0u; i < d_distribution.size(); ++i )
  {
    bin_boundaries[i] =
      getRawQuantity( Utility::get<FIRST>(d_distribution[i]) );

    if( i < d_distribution.size() - 1 )
    {
      bin_values[i] =
        getRawQuantity( Utility::get<SECOND>(d_distribution[i]) );
    }
  }
}

// Convert the unitless values to the correct units
template<typename IndependentUnit, typename DependentUnit>
template<typename Quantity>
void UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::convertUnitlessValues(
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
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::canDepVarBeZeroInIndepBounds() const
{
  bool possible_zero = false;
  
  for( size_t i = 0; i < d_distribution.size(); ++i )
  {
    if( Utility::get<SECOND>(d_distribution[i]) == DQT::zero() )
    {
      possible_zero = true;

      break;
    }
  }

  return possible_zero;
}

// Extract the values from a property tree
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::extractValuesFromNode(
                                      const Utility::PropertyTree& data,
                                      std::vector<double>& values )
{
  // Inline array
  if( data.size() == 0 )
    ThisType::extractValues( data.data(), values );

  // JSON array
  else
  {
    try{
      values = Utility::fromPropertyTree<std::vector<double> >( data );
    }
    EXCEPTION_CATCH_RETHROW( Utility::PropertyTreeConversionException,
                             "The histogram distribution cannot be "
                             "constructed because the values are not valid!" );
  }
}

// Extract the values 
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::extractValues(
                                            const Utility::Variant& data,
                                            std::vector<double>& values )
{
  try{
    values = Utility::variant_cast<std::vector<double> >( data );
  }
  EXCEPTION_CATCH_RETHROW( Utility::StringConversionException,
                           "The histogram distribution cannot be "
                           "constructed because the values are "
                           "not valid!" );
}

// Extract the cdf boolean from a property tree
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::extractCDFBooleanFromNode(
                                 const Utility::PropertyTree& cdf_boolean_data,
                                 bool& cdf_specified )
{
  // The data must be inlined in the node
  TEST_FOR_EXCEPTION( cdf_boolean_data.size() != 0,
                      Utility::PropertyTreeConversionException,
                      "Could not extract the cdf boolean value!" );

  ThisType::extractCDFBoolean( cdf_boolean_data.data(), cdf_specified );
}

// Extract the cdf boolean
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::extractCDFBoolean(
                                      const Utility::Variant& cdf_boolean_data,
                                      bool& cdf_specified )
{
  try{
    cdf_specified = Utility::variant_cast<bool>( cdf_boolean_data );
  }
  EXCEPTION_CATCH_RETHROW( Utility::StringConversionException,
                           "The histogram distribution cannot be "
                           "constructed because the cdf boolean value is "
                           "not valid!" );
}

// Verify that the values are valid
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::verifyValidValues(
                                 const std::vector<double>& bin_boundaries,
                                 const std::vector<double>& bin_values,
                                 const bool cdf_bin_values )
{
  TEST_FOR_EXCEPTION( bin_boundaries.size() <= 1,
                      Utility::StringConversionException,
                      "The histogram distribution cannot be constructed "
                      "because no full bins have been specified!" );
  
  TEST_FOR_EXCEPTION( !Sort::isSortedAscending( bin_boundaries.begin(),
						bin_boundaries.end() ),
		      Utility::StringConversionException,
		      "The histogram distribution cannot be "
		      "constructed because the bin boundaries "
		      << bin_boundaries << " are not sorted!" );

  TEST_FOR_EXCEPTION( QT::isnaninf( bin_boundaries.front() ),
                      Utility::StringConversionException,
                      "The histogram distribution cannot be constructed "
                      "because the first bin boundary is invalid!" );

  TEST_FOR_EXCEPTION( QT::isnaninf( bin_boundaries.back() ),
                      Utility::StringConversionException,
                      "The histogram distribution cannot be constructed "
                      "because the last bin boundary is invalid!" );

  TEST_FOR_EXCEPTION( bin_boundaries.size() != bin_values.size()+1,
		      Utility::StringConversionException,
		      "The histogram distribution cannot be constructed "
                      "because the number of bin boundaries ("
                      << bin_boundaries.size() << ") does not match the "
                      "number of bin values plus 1 ("
                      << bin_values.size() + 1 << ")!" );

  if( cdf_bin_values )
  {
    TEST_FOR_EXCEPTION( !Sort::isSortedAscending( bin_values.begin(),
                                                  bin_values.end() ),
                        Utility::StringConversionException,
                        "The histogram distribution cannot be "
                        "constructed because the bin cdf values "
                        << bin_values << " are not sorted!" );

    std::vector<double>::const_iterator repeat_bin_value =
      std::adjacent_find( bin_values.begin(), bin_values.end() );
    
    TEST_FOR_EXCEPTION( repeat_bin_value != bin_values.end(),
                        Utility::StringConversionException,
                        "The histogram distribution cannot be "
                        "constructed because there is a repeated bin cdf "
                        "value at index "
                        << std::distance( bin_values.begin(), repeat_bin_value ) <<
                        " (" << *repeat_bin_value << ")!" );
  }

  
  std::vector<double>::const_iterator bad_bin_value =
    std::find_if( bin_values.begin(),
                  bin_values.end(),
                  [](double element){ return QT::isnaninf( element ) || element <= 0.0; } );

  TEST_FOR_EXCEPTION(  bad_bin_value != bin_values.end(),
                       Utility::StringConversionException,
                       "The histogram distribution cannot be constructed "
                       "because the bin value at index "
                         << std::distance( bin_values.begin(), bad_bin_value ) <<
                       " (" << *bad_bin_value << ") is not valid!" );
}

} // end Utility namespace

// Explicit instantiation (extern declaration)
EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareHistogramDistribution<void,void> );

#endif // end UTILITY_HISTOGRAM_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_HistogramDistribution_def.hpp
//---------------------------------------------------------------------------//
