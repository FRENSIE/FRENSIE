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
#include <limits>

// FRENSIE Includes
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Explicit instantiation (extern declaration)
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareHistogramDistribution<void,void> );

// Default constructor
template<typename IndependentUnit, typename DependentUnit>
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::UnitAwareHistogramDistribution()
{ /* ... */ }

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
std::string UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::getDistributionTypeName(
                                                   const bool verbose_name,
                                                   const bool lowercase ) const
{
  std::string name = "Histogram";

  if( verbose_name )
    name += " Distribution";

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

  os << Utility::container_start_char
     << this->getDistributionTypeName( false, true )
     << Utility::next_container_element_char << " "
     << bin_boundaries
     << Utility::next_container_element_char << " "
     << bin_values
     << Utility::container_end_char;
}

// Method for initializing the object from an input stream
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::fromStream(
                                                           std::istream& is,
                                                           const std::string& )
{
  VariantVector distribution_data;

  try{
    Utility::fromStream( is, distribution_data );
  }
  EXCEPTION_CATCH_RETHROW( Utility::StringConversionException,
                           "Could not extract the distribution data from "
                           "the stream!" );

  // Verify that the correct amount of distribution data is present
  TEST_FOR_EXCEPTION( distribution_data.size() < 3 ||
                      distribution_data.size() > 4,
                      Utility::StringConversionException,
                      "The histogram distribution cannot be constructed "
                      "because the string representation is not valid!" );

  // Verify that the distribution type is histogram
  this->verifyDistributionType( distribution_data[0] );

  // Extract the independent values
  std::vector<double> bin_boundaries;

  this->extractIndependentValues( distribution_data[1], bin_boundaries );

  // Extract the dependent values
  std::vector<double> bin_values;

  this->extractDependentValues( distribution_data[2], bin_values );

  // Extract the value that determines if the bin values should be treated
  // as a CDF
  bool cdf_bin_values = false;
  
  if( distribution_data.size() == 4 )
    this->extractCDFBoolean( distribution_data[3], cdf_bin_values );

  // Verify that the values are valid
  this->verifyValidValues( bin_boundaries, bin_values, cdf_bin_values );

  this->initializeDistribution( bin_boundaries, bin_values, cdf_bin_values );
}

// Method for converting the type to a property tree
template<typename IndependentUnit, typename DependentUnit>
Utility::PropertyTree UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::toPropertyTree(
                                                 const bool inline_data ) const
{
  Utility::PropertyTree ptree;
  
  if( inline_data )
    ptree.put_value( *this );
  else
  {
    ptree.put( "type", this->getDistributionTypeName( false, true ) );

    std::vector<double> bin_boundaries, bin_values;

    this->reconstructOriginalUnitlessDistribution( bin_boundaries,
                                                   bin_values );
    
    ptree.put( "bin boundaries", bin_boundaries );
    ptree.put( "bin values", bin_values );
  }

  return ptree;
}

// Method for initializing the object from a property tree node
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::fromPropertyTree(
                                    const Utility::PropertyTree& node,
                                    std::vector<std::string>& unused_children )
{
  // Initialize from inline data
  if( node.size() == 0 )
  {
    std::istringstream iss( node.data().toString() );

    try{
      this->fromStream( iss );
    }
    EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                Utility::PropertyTreeConversionException,
                                "Could not create the histogram "
                                "distribution!" );
  }
  // Initialize from child nodes
  else
  {
    Utility::PropertyTree::const_iterator node_it, node_end;
    node_it = node.begin();
    node_end = node.end();
    
    bool type_verified = false;
    bool bin_boundary_vals_extracted = false;
    bool bin_vals_extracted = false;
    bool cdf_boolean_extracted = false;

    std::vector<double> bin_bounaries, bin_values;
    bool cdf_bin_values = false;

    while( node_it != node_end )
    {
      std::string child_node_key =
        boost::algorithm::to_lower_copy( node_it->first );

      // Verify the distribution type
      if( child_node_key.find( "type" ) < child_node_key.size() )
      {
        TEST_FOR_EXCEPTION( type_verified,
                            Utility::PropertyTreeConversionException,
                            "The histogram distribution cannot be created "
                            "because the distribution type is specified "
                            "multiple types (second occurance == \""
                            << node_it->first << "\")!" );
        try{
          this->verifyDistributionType( node_it->second.data() );
        }
        EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                    Utility::PropertyTreeConversionException,
                                    "Could not create the histogram "
                                    "distribution!" );

        type_verified = true;
      }

      // Extract the bin boundaries
      else if( child_node_key.find( "boundaries" ) < child_node_key.size() )
      {
        TEST_FOR_EXCEPTION( bin_boundary_vals_extracted,
                            Utility::PropertyTreeConversionException,
                            "The histogram distribution cannot be created "
                            "because the bin boundaries are specified "
                            "multiple times (second occurance == \""
                            << node_it->first << "\")!" );
        try{
          this->extractIndependentValues( node_it->second,
                                          bin_bounaries );
        }
        EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                    Utility::PropertyTreeConversionException,
                                    "Could not create the histogram "
                                    "distribution!" );

        bin_boundary_vals_extracted = true;
      }

      // Extract the bin values
      else if( child_node_key.find( "values" ) < child_node_key.size() )
      {
        TEST_FOR_EXCEPTION( bin_vals_extracted,
                            Utility::PropertyTreeConversionException,
                            "The histogram distribution cannot be created "
                            "because the bin values are specified multiple "
                            "times (second occurance == \""
                            << node_it->first << "\")!" );
        try{
          this->extractDependentValues( node_it->second, bin_values );
        }
        EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                    Utility::PropertyTreeConversionException,
                                    "Could not create the histogram "
                                    "distribution!" );

        bin_vals_extracted = true;
      }

      // Extract the cdf bin values
      else if( child_node_key.find( "cdf" ) < child_node_key.size() )
      {
        TEST_FOR_EXCEPTION( cdf_boolean_extracted,
                            Utility::PropertyTreeConversionException,
                            "The histogram distribution cannot be created "
                            "because the cdf attribute has been specified "
                            "multiple times (second occurance == \""
                            << node_it->first << "\")!" );
        try{
          this->extractCDFBoolean( node_it->second.data(), cdf_bin_values );
        }
        EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                    Utility::PropertyTreeConversionException,
                                    "Could not create the histogram "
                                    "distribution!" );

        cdf_boolean_extracted = true;
      }

      // This child node is unused (and is not a comment)
      else if( child_node_key.find( PTREE_COMMENT_NODE_KEY ) >=
               child_node_key.size() )
      {
        unused_children.push_back( node_it->first );
      }
      
      ++node_it;
    }

    // Make sure that the distribution type was verified
    TEST_FOR_EXCEPTION( !type_verified,
                        Utility::PropertyTreeConversionException,
                        "The histogram distribution could not be constructed "
                        "because the type could not be verified!" );

    // Make sure that the independent values were set
    TEST_FOR_EXCEPTION( !bin_boundary_vals_extracted,
                        Utility::PropertyTreeConversionException,
                        "The histogram distribution could not be constructed "
                        "because the bin boundaries were not specified!" );

    // Make sure that the dependent values were set
    TEST_FOR_EXCEPTION( !bin_vals_extracted,
                        Utility::PropertyTreeConversionException,
                        "The discrete distribution could not be constructed "
                        "because the bin values were not specified!" );

    // Verify that the values are valid
    try{
      this->verifyValidValues( bin_bounaries, bin_values, cdf_bin_values );
    }
    EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                Utility::PropertyTreeConversionException,
                                "Could not create the discrete "
                                "distribution!" );

    this->initializeDistribution( bin_bounaries, bin_values, cdf_bin_values );
  }
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
  bin_boundaries.resize( d_distribution.size() );
  bin_values.resize( d_distribution.size()-1 );

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
  bin_boundaries.resize( d_distribution.size() );
  bin_values.resize( d_distribution.size()-1 );

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

// Verify that the distribution type is discrete
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::verifyDistributionType( const Utility::Variant& type_data ) const
{
  // TEST_FOR_EXCEPTION( !this->doesTypeNameMatch( type_data.toString() ),
  //                     Utility::StringConversionException,
  //                     "The histogram distribution cannot be constructed "
  //                     "because the distribution type ("
  //                     << type_data.toString() << ") does not match!" );
}

// Set the independent values
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::extractIndependentValues(
                                      const Utility::Variant& indep_data,
                                      std::vector<double>& independent_values )
{
  try{
    independent_values =
      Utility::variant_cast<std::vector<double> >( indep_data );
  }
  EXCEPTION_CATCH_RETHROW( Utility::StringConversionException,
                           "The histogram distribution cannot be "
                           "constructed because the independent values are "
                           "not valid!" );
}

// Set the independent values
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::extractIndependentValues(
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
                             "The histogram distribution cannot be "
                             "constructed because the independent data "
                             "is invalid!" );
  }
}

// Set the dependent values
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::extractDependentValues(
                                        const Utility::Variant& dep_data,
                                        std::vector<double>& dependent_values )
{
  try{
    dependent_values =
      Utility::variant_cast<std::vector<double> >( dep_data );
  }
  EXCEPTION_CATCH_RETHROW( Utility::StringConversionException,
                           "The histogram distribution cannot be "
                           "constructed because the dependent values are "
                           "not valid!" );
}

// Set the dependent values
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::extractDependentValues(
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
                             "The histogram distribution cannot be "
                             "constructed because the dependent data "
                             "is invalid!" );
  }
}

// Set the cdf boolean
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::extractCDFBoolean(
                                      const Utility::Variant& cdf_boolean_data,
                                      bool& cdf_bin_values )
{
  try{
    cdf_bin_values =
      Utility::variant_cast<bool>( cdf_boolean_data );
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

#endif // end UTILITY_HISTOGRAM_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_HistogramDistribution_def.hpp
//---------------------------------------------------------------------------//
