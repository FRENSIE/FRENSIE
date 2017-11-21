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
#include "Utility_ContractException.hpp"

BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT( UnitAwareDiscreteDistribution );

namespace Utility{

// Initialize static member data
template<typename IndependentUnit,typename DependentUnit>
const std::string UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::s_indep_values_key( "independent values" );

template<typename IndependentUnit,typename DependentUnit> 
const std::string UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::s_indep_values_min_match_string( "indep" );

template<typename IndependentUnit,typename DependentUnit> 
const std::string UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::s_dep_values_key( "dependent values" );

template<typename IndependentUnit,typename DependentUnit> 
const std::string UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::s_dep_values_min_match_string( "dep" );

// Default Constructor
template<typename IndependentUnit,typename DependentUnit>
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::UnitAwareDiscreteDistribution()
{ 
  BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Basic Constructor (potentiall dangerous)
/*! \details A precalculated CDF can be passed as the dependent values as
 * long as the interpret_dependent_values_as_cdf argument is true.
 */
template<typename IndependentUnit,typename DependentUnit>
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::UnitAwareDiscreteDistribution(
			      const std::vector<double>& independent_values,
			      const std::vector<double>& dependent_values,
			      const bool interpret_dependent_values_as_cdf )
  : d_distribution( independent_values.size() ),
    d_norm_constant()
{
  this->initializeDistribution( independent_values,
				dependent_values,
				interpret_dependent_values_as_cdf );

  BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// CDF Constructor (potentially dangerous)
template<typename IndependentUnit,typename DependentUnit>
template<typename InputIndepQuantity>
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::UnitAwareDiscreteDistribution(
	      const std::vector<InputIndepQuantity>& independent_quantities,
	      const std::vector<double>& dependent_values )
  : d_distribution( independent_quantities.size() ),
    d_norm_constant()
{
  this->initializeDistributionFromCDF( independent_quantities,
				       dependent_values );

  BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Constructor
template<typename IndependentUnit,typename DependentUnit>
template<typename InputIndepQuantity,typename InputDepQuantity>
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::UnitAwareDiscreteDistribution(
	      const std::vector<InputIndepQuantity>& independent_quantities,
	      const std::vector<InputDepQuantity>& dependent_values )
  : d_distribution( independent_quantities.size() ),
    d_norm_constant()
{
  this->initializeDistribution( independent_quantities,
				dependent_values );

  BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
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
    d_norm_constant()
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

  this->initializeDistribution( input_indep_quantities, input_dep_quantities );

  BOOST_DISTRIBUTION_CLASS_EXPORT_IMPLEMENT_FINALIZE( ThisType );
}

// Copy constructor (copying from unitless distribution only)
template<typename IndependentUnit,typename DependentUnit>
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::UnitAwareDiscreteDistribution(
  const UnitAwareDiscreteDistribution<void,void>& unitless_dist_instance, int )
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
  return getRawQuantity(this->evaluatePDF( indep_var_value ))*d_norm_constant;
}

// Evaluate the PDF
/*! \details It is acceptable for the same independent variable to appear
 * multiple times. When multiple occurances are found, the sum will be
 * returned.
 */
template<typename IndependentUnit,typename DependentUnit>
typename UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::evaluatePDF( const typename UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  double raw_pdf = 0.0;

  if( indep_var_value >= Utility::get<FIRST>(d_distribution.front()) &&
      indep_var_value <= Utility::get<FIRST>(d_distribution.back()) )
  {
    typename std::vector<std::pair<IndepQuantity,double> >::const_iterator bin =
      Search::binaryLowerBound<FIRST>( d_distribution.begin(),
				       d_distribution.end(),
				       indep_var_value );

    typename std::vector<std::pair<IndepQuantity,double> >::const_iterator
      prev_bin = bin;
    --prev_bin;

    // The same independent variable may appear multiple times
    while( Utility::get<FIRST>(*bin) == indep_var_value )
    {
      if( bin != d_distribution.begin() )
      {
	raw_pdf += Utility::get<SECOND>(*bin) -
          Utility::get<SECOND>(*prev_bin);

	--bin;
	--prev_bin;
      }
      else
      {
	raw_pdf += Utility::get<SECOND>(*bin);

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

  if( indep_var_value >= Utility::get<FIRST>(d_distribution.front()) &&
      indep_var_value <= Utility::get<FIRST>(d_distribution.back()) )
  {
    typename std::vector<std::pair<IndepQuantity,double> >::const_iterator bin =
      Search::binaryLowerBound<FIRST>( d_distribution.begin(),
				       d_distribution.end(),
				       indep_var_value );

    // The same independent variable may appear multiple times
    cdf = Utility::get<SECOND>(*bin);
  }
  else if( indep_var_value < Utility::get<FIRST>(d_distribution.front()) )
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

  unsigned dummy_index;

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
					    unsigned& sampled_bin_index ) const
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
  unsigned dummy_index;

  return this->sampleImplementation( random_number, dummy_index );
}

// Return a random sample from the corresponding CDF in a subrange
template<typename IndependentUnit,typename DependentUnit>
typename UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::sampleInSubrange( const typename UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::IndepQuantity max_indep_var ) const
{
  // Make sure the max independent variable is valid
  testPrecondition( max_indep_var >= Utility::get<FIRST>(d_distribution.front()) );

  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleWithRandomNumberInSubrange( random_number,
						 max_indep_var );
}

// Return a random sample using the random number and record the bin index
template<typename IndependentUnit,typename DependentUnit>
inline typename UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::sampleImplementation(
					    double random_number,
					    unsigned& sampled_bin_index ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );

  // Get the bin index sampled
  sampled_bin_index =
    Search::binaryUpperBoundIndex<SECOND>( d_distribution.begin(),
					   d_distribution.end(),
					   random_number );

  return Utility::get<FIRST>(d_distribution[sampled_bin_index]);
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
  testPrecondition( max_indep_var >= Utility::get<FIRST>(d_distribution.front()) );

  // Scale the random number to the cdf at the max indep var
  double scaled_random_number =
    random_number*this->evaluateCDF( max_indep_var );

  unsigned dummy_index;

  return this->sampleImplementation( scaled_random_number, dummy_index );
}

// Return the upper bound of the distribution independent variable
template<typename IndependentUnit,typename DependentUnit>
typename UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::getUpperBoundOfIndepVar() const
{
  return Utility::get<FIRST>(d_distribution.back());
}

// Return the lower bound of the independent variable
template<typename IndependentUnit,typename DependentUnit>
typename UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::getLowerBoundOfIndepVar() const
{
  return Utility::get<FIRST>(d_distribution.front());
}

// Return the distribution type
template<typename IndependentUnit,typename DependentUnit>
OneDDistributionType
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::getDistributionType() const
{
  return ThisType::distribution_type;
}

// Return the distribution type name
template<typename IndependentUnit, typename DependentUnit>
std::string UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::typeName(
                                                const bool verbose_name,
                                                const bool use_template_params,
                                                const std::string& delim )
{
  return BaseType::typeNameImpl( "Discrete",
                                 verbose_name,
                                 use_template_params,
                                 delim );
}

// Return the distribution type name
template<typename IndependentUnit, typename DependentUnit>
std::string UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::getDistributionTypeName(
                                                   const bool verbose_name,
                                                   const bool lowercase ) const
{
  std::string name = this->typeName( verbose_name, false, " " );

  if( lowercase )
    boost::algorithm::to_lower( name );

  return name;
}

// Test if the distribution is continuous
template<typename IndependentUnit,typename DependentUnit>
bool UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::isContinuous() const
{
  return false;
}

// Method for placing the object in an output stream
template<typename IndependentUnit,typename DependentUnit>
void UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::toStream( std::ostream& os ) const
{
  std::vector<double> independent_values, dependent_values;

  this->reconstructOriginalUnitlessDistribution( independent_values,
						 dependent_values );

  this->toStreamImpl( os, independent_values, dependent_values );
}

// Method for initializing the object from an input stream
template<typename IndependentUnit,typename DependentUnit>
void UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::fromStream(
                                                           std::istream& is,
                                                           const std::string& )
{
  VariantList distribution_data;

  this->fromStreamImpl( is, distribution_data );
  
  // Verify that the correct amount of distribution data is present
  TEST_FOR_EXCEPTION( distribution_data.size() < 2,
                      Utility::StringConversionException,
                      "The discrete distribution cannot be constructed "
                      "because the string representation is not valid!" );

  // Extract the independent values
  std::vector<double> independent_values;
  
  this->extractIndependentValues( distribution_data.front(),
                                  independent_values );

  distribution_data.pop_front();

  // Extract the dependent values
  std::vector<double> dependent_values;
  
  this->extractDependentValues( distribution_data.front(),
                                dependent_values );

  distribution_data.pop_front();

  // Verify that the values are valid
  this->verifyValidValues( independent_values, dependent_values );        

  this->initializeDistribution( independent_values, dependent_values, false );

  // Check if there is any superfluous data
  this->checkForUnusedStreamData( distribution_data );
}

// Method for converting the type to a property tree
template<typename IndependentUnit, typename DependentUnit>
Utility::PropertyTree UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::toPropertyTree(
                                                 const bool inline_data ) const
{
  if( inline_data )
    return this->toInlinedPropertyTreeImpl();
  else
  {
    std::vector<double> independent_values, dependent_values;

    this->reconstructOriginalUnitlessDistribution( independent_values,
                                                   dependent_values );

    return this->toPropertyTreeImpl(
                            std::tie( s_indep_values_key, independent_values ),
                            std::tie( s_dep_values_key, dependent_values ) );
  }
}

// Method for initializing the object from a property tree node
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::fromPropertyTree(
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
     std::make_pair( s_indep_values_key,
      std::make_tuple( s_indep_values_min_match_string, BaseType::REQUIRED_DATA,
                  std::bind<void>( &ThisType::extractIndependentValuesFromNode,
                                   std::placeholders::_1,
                                   std::ref(independent_values) ) ) ) );
    data_extractors.insert(
     std::make_pair( s_dep_values_key,
      std::make_tuple( s_dep_values_min_match_string, BaseType::REQUIRED_DATA,
                  std::bind<void>( &ThisType::extractDependentValuesFromNode,
                                   std::placeholders::_1,
                                   std::ref(dependent_values) ) ) ) );
    
    this->fromPropertyTreeImpl( node, unused_children, data_extractors );

    // Verify that the values are valid
    try{
      this->verifyValidValues( independent_values, dependent_values );
    }
    EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                Utility::PropertyTreeConversionException,
                                "Could not create the discrete "
                                "distribution!" );

    this->initializeDistribution(independent_values, dependent_values, false);
  }
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
			  const std::vector<double>& independent_values,
			  const std::vector<double>& dependent_values,
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
    this->initializeDistributionFromCDF( independent_quantities,
					 dependent_values );
  }
  else
  {
    // Convert the raw dependent values to quantities
    std::vector<DepQuantity> dependent_quantities;

    this->convertUnitlessValues( dependent_values, dependent_quantities );

    this->initializeDistribution( independent_quantities,
				  dependent_quantities );
  }
}

// Initialize the distribution from a cdf
template<typename IndependentUnit,typename DependentUnit>
template<typename InputIndepQuantity>
void UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::initializeDistributionFromCDF(
	      const std::vector<InputIndepQuantity>& independent_quantities,
	      const std::vector<double>& cdf_values )
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
  for( unsigned i = 0; i < cdf_values.size(); ++i )
  {
    Utility::get<FIRST>(d_distribution[i]) =
      IndepQuantity( independent_quantities[i] );

    Utility::get<SECOND>(d_distribution[i]) = cdf_values[i];
  }

  // Verify that the CDF is normalized (in event of round-off errors)
  if( cdf_values.back() != 1.0 )
  {
    for( unsigned i = 0; i < d_distribution.size(); ++i )
    {
      Utility::get<SECOND>(d_distribution[i]) /=
        Utility::get<SECOND>(d_distribution.back());
    }
  }

  // Set the normalization constant
  setQuantity( d_norm_constant, 1.0 );
}

// Initialize the distribution
template<typename IndependentUnit,typename DependentUnit>
template<typename InputIndepQuantity,typename InputDepQuantity>
void UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::initializeDistribution(
		  const std::vector<InputIndepQuantity>& independent_values,
		  const std::vector<InputDepQuantity>& dependent_values )
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
  for( unsigned i = 0; i < dependent_values.size(); ++i )
  {
    Utility::get<FIRST>(d_distribution[i]) =
      IndepQuantity( independent_values[i] );

    // Use an explicit cast to desired unit
    DepQuantity dep_quantity( dependent_values[i] );

    Utility::get<SECOND>(d_distribution[i]) = getRawQuantity( dep_quantity );

    d_norm_constant += dep_quantity;
  }

  // Create a CDF from the raw distribution data
  DataProcessor::calculateDiscreteCDF<SECOND,SECOND>( d_distribution );
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

  for( unsigned i = 0u; i < d_distribution.size(); ++i )
  {
    independent_quantities[i] = Utility::get<FIRST>(d_distribution[i]);

    if( i != 0u )
    {
      dependent_quantities[i] = d_norm_constant*
	(Utility::get<SECOND>(d_distribution[i]) -
         Utility::get<SECOND>(d_distribution[i-1]));
    }
    else
    {
      dependent_quantities[i] =
        d_norm_constant*Utility::get<SECOND>(d_distribution[i]);
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

  for( unsigned i = 0u; i < d_distribution.size(); ++i )
  {
    independent_values[i] =
      getRawQuantity( Utility::get<FIRST>(d_distribution[i]) );

    if( i != 0u )
    {
      dependent_values[i] = getRawQuantity( d_norm_constant )*
	(Utility::get<SECOND>(d_distribution[i]) -
         Utility::get<SECOND>(d_distribution[i-1]));
    }
    else
    {
      dependent_values[i] = Utility::get<SECOND>(d_distribution[i])*
        getRawQuantity( d_norm_constant );
    }
  }
}

// Convert the unitless values to the correct units
template<typename IndependentUnit,typename DependentUnit>
template<typename Quantity>
void UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::convertUnitlessValues(
		                 const std::vector<double>& unitless_values,
				 std::vector<Quantity>& quantities )
{
  // Resize the quantities array
  quantities.resize( unitless_values.size() );

  // Copy the values
  for( unsigned i = 0u; i < unitless_values.size(); ++i )
    setQuantity( quantities[i], unitless_values[i] );
}

// Test if the dependent variable can be zero within the indep bounds
template<typename IndependentUnit,typename DependentUnit>
bool UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::canDepVarBeZeroInIndepBounds() const
{
  return true;
}

// Set the independent values
template<typename IndependentUnit,typename DependentUnit>
void UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::extractIndependentValues(
                                      const Utility::Variant& indep_data,
                                      std::vector<double>& independent_values )
{
  try{
    independent_values =
      Utility::variant_cast<std::vector<double> >( indep_data );
  }
  EXCEPTION_CATCH_RETHROW( Utility::StringConversionException,
                           "The discrete distribution cannot be "
                           "constructed because the independent values are "
                           "not valid!" );
}

// Set the independent values
template<typename IndependentUnit,typename DependentUnit>
void UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::extractIndependentValuesFromNode(
                                      const Utility::PropertyTree& indep_data,
                                      std::vector<double>& independent_values )
{
  // Inline array
  if( indep_data.size() == 0 )
  {
    ThisType::extractIndependentValues( indep_data.data(),
                                        independent_values );
  }

  // JSON array
  else
  {
    try{
      independent_values =
        Utility::fromPropertyTree<std::vector<double> >( indep_data );
    }
    EXCEPTION_CATCH_RETHROW( Utility::PropertyTreeConversionException,
                             "The discrete distribution cannot be "
                             "constructed because the independent data "
                             "is invalid!" );
  }
}

// Set the dependent values
template<typename IndependentUnit,typename DependentUnit>
void UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::extractDependentValues(
                                        const Utility::Variant& dep_data,
                                        std::vector<double>& dependent_values )
{
  try{
    dependent_values = Utility::variant_cast<std::vector<double> >( dep_data );
  }
  EXCEPTION_CATCH_RETHROW( Utility::StringConversionException,
                           "The discrete distribution cannot be "
                           "constructed because the dependent values are "
                           "not valid!" );
}

// Set the dependent values
template<typename IndependentUnit,typename DependentUnit>
void UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::extractDependentValuesFromNode(
                                        const Utility::PropertyTree& dep_data,
                                        std::vector<double>& dependent_values )
{
  // Inline array
  if( dep_data.size() == 0 )
    ThisType::extractDependentValues( dep_data.data(), dependent_values );

  // JSON array
  else
  {
    try{
      dependent_values =
        Utility::fromPropertyTree<std::vector<double> >( dep_data );
    }
    EXCEPTION_CATCH_RETHROW( Utility::PropertyTreeConversionException,
                             "The discrete distribution cannot be "
                             "constructed because the dependent data "
                             "is invalid!" );
  }
}

// Verify that the values are valid
template<typename IndependentUnit,typename DependentUnit>
void UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::verifyValidValues(
                                 const std::vector<double>& independent_values,
                                 const std::vector<double>& dependent_values )
{
  TEST_FOR_EXCEPTION( independent_values.size() == 0,
                      Utility::StringConversionException,
                      "The discrete distribution cannot be constructed "
                      "because no independent values have been specified!" );
  
  TEST_FOR_EXCEPTION( !Sort::isSortedAscending( independent_values.begin(),
						independent_values.end() ),
		      Utility::StringConversionException,
		      "The discrete distribution cannot be constructed "
		      "because the independent values "
		      << independent_values << " are not sorted!" );

  TEST_FOR_EXCEPTION( QT::isnaninf( independent_values.front() ),
                      Utility::StringConversionException,
                      "The discrete distribution cannot be constructed "
                      "because the first independent value is invalid!" );

  TEST_FOR_EXCEPTION( QT::isnaninf( independent_values.back() ),
                      Utility::StringConversionException,
                      "The discrete distribution cannot be constructed "
                      "because the last independent value is invalid!" );
  
  TEST_FOR_EXCEPTION( independent_values.size() != dependent_values.size(),
		      Utility::StringConversionException,
		      "The discrete distribution cannot be constructed "
                      "because the number of independent values ("
                      << independent_values.size() << ") does not match the "
                      "number of dependent values ("
                      << dependent_values.size() << ")!" );

  std::vector<double>::const_iterator bad_dependent_value =
    std::find_if( dependent_values.begin(),
                  dependent_values.end(),
                  [](double element){ return QT::isnaninf( element ) || element <= 0.0; } );
    
  TEST_FOR_EXCEPTION(  bad_dependent_value != dependent_values.end(),
                       Utility::StringConversionException,
                      "The discrete distribution cannot be constructed "
                      "because the dependent value at index "
                       << std::distance( dependent_values.begin(), bad_dependent_value ) <<
                       " (" << *bad_dependent_value << ") is not valid!" );
}

} // end Utility namespace

EXTERN_EXPLICIT_DISTRIBUTION_INST( UnitAwareDiscreteDistribution<void,void> );

#endif // end UTILITY_DISCRETE_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_DiscreteDistribution_def.hpp
//---------------------------------------------------------------------------//
