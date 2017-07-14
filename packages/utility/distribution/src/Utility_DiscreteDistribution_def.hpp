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
#include <stdexcept>

// FRENSIE Includes
#include "Utility_DataProcessor.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Explicit instantiation (extern declaration)
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareDiscreteDistribution<void,void> );

// Default Constructor
template<typename IndependentUnit,typename DependentUnit>
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::UnitAwareDiscreteDistribution()
{ /* ... */ }

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
  return UnitAwareDiscreteDistribution::distribution_type;
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

  os << "{"
     << Utility::convertOneDDistributionTypeToString( UnitAwareDiscreteDistribution::distribution_type )
     << ", " << independent_values
     << ", " << dependent_values
     << "}";
}

// Method for initializing the object from an input stream
template<typename IndependentUnit,typename DependentUnit>
void UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::fromStream(
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
  TEST_FOR_EXCEPTION( distribution_data.size() != 3,
                      Utility::StringConversionException,
                      "The discrete distribution cannot be constructed "
                      "because the string representation is not valid!" );

  // Verify that the distribution type is discrete
  this->verifyDistributionType( distribution_data[0] );

  // Extract the independent values
  std::vector<double> independent_values;
  
  this->extractIndependentValues( distribution_data[1], independent_values );

  // Extract the dependent values
  std::vector<double> dependent_values;
  
  this->extractDependentValues( distribution_data[2], dependent_values );

  // Verify that the values are valid
  this->verifyValidValues( independent_values, dependent_values );

  this->initializeDistribution( independent_values, dependent_values, false );
}

// Method for converting the type to a property tree
template<typename IndependentUnit, typename DependentUnit>
Utility::PropertyTree UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::toPropertyTree(
                                                 const bool inline_data ) const
{
  Utility::PropertyTree ptree;
  
  if( inline_data )
    ptree.data().setValue( *this );
  else
  {
    ptree.put( "type", Utility::convertOneDDistributionTypeToString( UnitAwareDiscreteDistribution::distribution_type ) );

    std::vector<double> independent_values, dependent_values;

    this->reconstructOriginalUnitlessDistribution( independent_values,
                                                   dependent_values );
    
    ptree.put( "independent values", independent_values );
    ptree.put( "dependent values", dependent_values );
  }

  return ptree;
}

// Method for initializing the object from a property tree node
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::fromPropertyTree(
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
                                "Could not create the discrete "
                                "distribution!" );
  }
  // Initialize from child nodes
  else
  {
    Utility::PropertyTree::const_iterator node_it, node_end;
    node_it = node.begin();
    node_end = node.end();
    
    bool type_verified = false;
    bool independent_vals_extracted = false;
    bool dependent_vals_extracted = false;

    std::vector<double> independent_values, dependent_values;

    while( node_it != node_end )
    {
      std::string child_node_key =
        boost::algorithm::to_lower_copy( node_it->first );

      // Verify the distribution type
      if( child_node_key.find( "type" ) < child_node_key.size() )
      {
        try{
          this->verifyDistributionType( node_it->second.data() );
        }
        EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                    Utility::PropertyTreeConversionException,
                                    "Could not create the discrete "
                                    "distribution!" );

        type_verified = true;
      }

      // Extract the independent values
      else if( child_node_key.find( "indep" ) < child_node_key.size() )
      {
        try{
          this->extractIndependentValues( node_it->second.data(),
                                          independent_values );
        }
        EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                    Utility::PropertyTreeConversionException,
                                    "Could not create the discrete "
                                    "distribution!" );

        independent_vals_extracted = true;
      }

      // Extract the dependent values
      else if( child_node_key.find( "dep" ) < child_node_key.size() )
      {
        try{
          this->extractDependentValues( node_it->second.data(),
                                        dependent_values );
        }
        EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                    Utility::PropertyTreeConversionException,
                                    "Could not create the discrete "
                                    "distribution!" );

        dependent_vals_extracted = true;
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
                        "The discrete distribution could not be constructed "
                        "because the type could not be verified!" );

    // Make sure that the independent values were set
    TEST_FOR_EXCEPTION( !independent_vals_extracted,
                        Utility::PropertyTreeConversionException,
                        "The discrete distribution could not be constructed "
                        "because the independent values were not specified!" );

    // Make sure that the dependent values were set
    TEST_FOR_EXCEPTION( !dependent_vals_extracted,
                        Utility::PropertyTreeConversionException,
                        "The discrete distribution could not be constructed "
                        "because the dependent values were not specified!" );

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

// Verify that the distribution type is discrete
template<typename IndependentUnit,typename DependentUnit>
void UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::verifyDistributionType( const Utility::Variant& type_data )
{
  std::string distribution_type = type_data.toString();
  boost::algorithm::to_lower( distribution_type );

  TEST_FOR_EXCEPTION( distribution_type.find( "discrete" ) >=
                      distribution_type.size(),
                      Utility::StringConversionException,
                      "The discrete distribution cannot be constructed "
                      "because the distribution type ("
                      << distribution_type << ") does not match!" );
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

  TEST_FOR_EXCEPTION( !Sort::isSortedAscending( independent_values.begin(),
						independent_values.end() ),
		      Utility::StringConversionException,
		      "The discrete distribution cannot be constructed "
		      "because the independent values "
		      << indep_data.toString() << " are not sorted!" );
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

// Verify that the values are valid
template<typename IndependentUnit,typename DependentUnit>
void UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::verifyValidValues(
                                 const std::vector<double>& independent_values,
                                 const std::vector<double>& dependent_values )
{
  TEST_FOR_EXCEPTION( independent_values.size() != dependent_values.size(),
		      Utility::StringConversionException,
		      "The discrete distribution cannot be constructed "
                      "because the number of independent values ("
                      << independent_values.size() << ") does not match the "
                      "number of dependent values ("
                      << dependent_values.size() << ")!" );
  
  TEST_FOR_EXCEPTION( independent_values.size() == 0,
                      Utility::StringConversionException,
                      "The discrete distribution cannot be constructed "
                      "because no independent values have been specified!" );
}

} // end Utility namespace

#endif // end UTILITY_DISCRETE_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_DiscreteDistribution_def.hpp
//---------------------------------------------------------------------------//
